// spcCListMaterialDlg.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
// spacer
#include "spcCList_Materials.h"
#include "SpacerView.h"
#include "MainFrm.h"
// spc
#include "spcCConfiguration.h"
#include "spcCList_Materials.h"
// #include "spcCMatConCheck.h"
#include "spcCWorkInfoDlg.h"
#include "spcCInputDialog.h"
// z-files
#include "zerror.h"
#include "zdisk.h"
#include "zArchiver.h"
#include "zmaterial.h"

// other
#include "spcCDibSection.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const zSTRING MATLIBFILE_EXT = ".pml";

/////////////////////////////////////////////////////////////////////////////
// spcCListMaterialDlg dialog


spcCListMaterialDlg::spcCListMaterialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCListMaterialDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCListMaterialDlg)
	m_filter = _T("");
	//}}AFX_DATA_INIT
	winID = 0;
	materialLoaded = false;
}

spcCListMaterialDlg::~spcCListMaterialDlg()
{	
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing MaterialList-Instance ...");	
	zERR_MESSAGE(7,zERR_END,"");
}

void spcCListMaterialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCListMaterialDlg)	
	DDX_Control(pDX, IDC_NEW_FILTER, ctrl_filter_new);
	DDX_Control(pDX, IDC_DEL_FILTER, ctrl_filter_del);
	DDX_Control(pDX, IDC_FILTER, ctrl_filter);
	DDX_Control(pDX, IDC_MATLIST, ctrl_mat_list);
	DDX_CBString(pDX, IDC_FILTER, m_filter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCListMaterialDlg, CDialog)
	//{{AFX_MSG_MAP(spcCListMaterialDlg)
	ON_CBN_SELCHANGE(IDC_FILTER, OnSelchangeFilter)
	ON_LBN_SELCHANGE(IDC_MATLIST, OnSelchangeMatlist)
	ON_LBN_DBLCLK(IDC_MATLIST, OnDblclkMatlist)	
	ON_WM_RBUTTONDOWN()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_NEW_FILTER, OnNewFilter)
	ON_BN_CLICKED(IDC_DEL_FILTER, OnDelFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCListMaterialDlg message handlers

void spcCListMaterialDlg::LoadMatlib()
{
	zSTRING filter;
	// for every MatFilter do Load it
	for (int z=0; z<spcConfig.matFilterList.GetNumInList(); z++)								
		if (spcConfig.matFilterList[z]->id!=spcCMatFilter::NullLib)
		{
			filter = spcConfig.matFilterList[z]->name;			
			if (workingDlg) workingDlg->AddMessage(CString("Loading mat-filter ")+filter.ToChar());
			LoadMatlib(filter.ToChar(), false); // auf keinen fall mit Check ausführen
		}
	materialLoaded = true;

	ctrl_filter.SelectString(0,NO_FILTER_FOLDER);	
	OnSelchangeFilter();
}

void spcCListMaterialDlg::LoadMatlib(CString fname, bool performCheck)
{	
	zoptions->ChangeDir(DIR_TOOLS_DATA);
	zSTRING matfilename = fname.GetBuffer(0);
	matfilename = matfilename+MATLIBFILE_EXT;
	zFILE* file = zfactory->CreateZFile(matfilename);	
	if (!file->Exists()) { delete file;zerr.Message("B: SPC: File of Material-Lib not found: "+matfilename);return; }
	
	zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Loading mat-filter "+matfilename);

	file->Open();
	file->Reset();
			
	// Filteritem ermitteln
	spcCMatFilter* item;
	int filterIndex = spcConfig.FindMatFilterIndexByName(fname);
	if (filterIndex>=0)
	{
		zERR_MESSAGE(5,0,"B: SPC: MatFilter-Item "+matfilename+" found. Updating ...");
		item = spcConfig.matFilterList[filterIndex];
	}
	else
	{
		zERR_MESSAGE(5,0,"B: SPC: Creating new MatFilter-Item "+matfilename+". Loading ...");
		item = new spcCMatFilter;
		item->Init(fname);
		spcConfig.matFilterList.InsertEnd(item);
	};	

	::SetCursor(spcConfig.MouseWait);

	zCArchiver* arch = zarcFactory.CreateArchiverRead(file);	

	zSTRING cn, matName;
	zWORD cv;	
	zCMaterial* mat=0;	
	long	pos;
	int		numLoaded = 0;
	while (file->Pos()+3<file->Size())
	{		
		pos = file->Pos();
		arch->ReadChunkStart(cn,cv);		
		matName = arch->ReadString("name");
		file->Seek(pos);
		mat = zCMaterial::SearchName (matName);

		if (!mat) mat = dynamic_cast<zCMaterial*>(arch->ReadObject());
		else	  
		{
			if (mat->GetLibFlag()==item->id)
				zERR_WARNING("B: SPC: Duplicate material "+mat->GetName()+" with same libFlag: "+zSTRING(item->id));
			else
				zERR_WARNING("B: SPC: Duplicate material "+mat->GetName()+" with different libFlag: "+zSTRING(mat->GetLibFlag())+"/"+zSTRING(item->id));
			dynamic_cast<zCMaterial*>(arch->ReadObject());
			mat->SetLibFlag(item->id);
			numLoaded++;
		}
		
		if (mat)
		{
			mat->AddRef();
			mat->SetUsage(zCMaterial::zMAT_USAGE_LEVEL);
			mat->SetLibFlag(item->id);			
			numLoaded++;
		}					
	
	}
	zERR_MESSAGE(4,0,"B: SPC: Num of materials found: "+zSTRING(numLoaded));

	arch->Close();		
	zRELEASE(arch);
	
	file->Close();delete file;	

	m_filter = fname;

	item->SetDirty(false);

	::SetCursor(spcConfig.MouseArrow);
	UpdateData(false);

	zERR_MESSAGE(4,zERR_END,"");
}

void spcCListMaterialDlg::SaveMatlib(CString filterName)
{
	filterName.MakeUpper();
	if (filterName.Find(NO_FILTER_FOLDER)>=0) return;

	spcCMatFilter* item;
	int filterIndex = spcConfig.FindMatFilterIndexByName(filterName);
	if (filterIndex<0) { AfxMessageBox("Sorry, could not find filter with name "+filterName);return; };
	item = spcConfig.matFilterList[filterIndex];

	zoptions->ChangeDir(DIR_TOOLS_DATA);
	zSTRING matname = filterName.GetBuffer(0);
	matname = matname+MATLIBFILE_EXT;	
	zerr.Message("B: (Spacer)  Saving Material-File \""+matname+"\"");
	
	zFILE* file = zfactory->CreateZFile(matname);
	if (file->Create() == zERR_NONE)
	{
			
		zCArchiver* arch = zarcFactory.CreateArchiverWrite(file,zARC_MODE_ASCII);		

		zCMaterial *mat = 0;
		zCClassDef* matDef = zCMaterial::GetStaticClassDef();
		for (int matz=0; matz<matDef->GetNumObjects(); matz++)
		{
			mat = dynamic_cast<zCMaterial*>(matDef->GetObjectByIndex(matz));
			if (
				(mat->GetLibFlag()==item->id)
				&&
				(mat->GetUsage() == zCMaterial::zMAT_USAGE_LEVEL)
				) 
				arch->WriteObject(mat);
		}

		arch->Close();
		zRELEASE(arch);

		file->Close();
	};
	delete file;file=0;

	spcConfig.matFilterList[filterIndex]->SetDirty(false);
}

BOOL spcCListMaterialDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	

	spcCWindowResizeStyle* style;
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_mat_list,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_filter_new,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_filter_del,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_filter,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);

	winID = spcConfig.GetWindowID("winObjectList");
	spcTRegWindowInfo winInfo;
	spcConfig.GetWindowPosition(winID,winInfo);
	
	MoveWindow(
		winInfo.position.pos.x,
		winInfo.position.pos.y,
		winInfo.position.size.cx,
		winInfo.position.size.cy,
		TRUE);

	InitData();

	return TRUE; 
}


void spcCListMaterialDlg::OnSelchangeFilter() 
{
	UpdateData(true); 

	int index = ctrl_filter.GetCurSel();
	if (index != CB_ERR) ctrl_filter.GetLBText(index, m_filter);	

	ctrl_mat_list.ResetContent();
	ctrl_mat_list.CreateList(m_filter);
	UpdateData(FALSE);
	RedrawWindow();

	// CSpacerView::view->SetActiveWindow();
	//CSpacerView::view->SetFocus();
}

void spcCListMaterialDlg::OnSelchangeMatlist() 
{
	//CSpacerView::view->SetActiveWindow();
	//CSpacerView::view->SetFocus();
}

void spcCListMaterialDlg::OnDblclkMatlist() 
{
	//CSpacerView::view->SetActiveWindow();
	//CSpacerView::view->SetFocus();
}

void spcCListMaterialDlg::InitData()
{
	UpdateFilterList();	

	// init selection		
	ctrl_filter.SelectString(0,NO_FILTER_FOLDER);	
	OnSelchangeFilter();
}

void spcCListMaterialDlg::UpdateMaterialList(const zSTRING& filterName)
{
	UpdateData(true);
	
	if (!filterName.IsEmpty()) m_filter = filterName.ToChar();

	if (!m_filter.IsEmpty()) 
	{
		ctrl_mat_list.CreateList(m_filter);	
		RedrawWindow();
	}

	UpdateData(false);	
}

void spcCListMaterialDlg::UpdateFilterList()
{
	UpdateData(true);
	ctrl_filter.ResetContent();
	for (int z=0; z<spcConfig.matFilterList.GetNumInList(); z++)
	{
		ctrl_filter.AddString(spcConfig.matFilterList[z]->name);	
	}
	UpdateData(false);
}


void spcCListMaterialDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CDialog::OnRButtonDown(nFlags, point);
}

void spcCListMaterialDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	// Muss noch die Material-Bibliothek geladen werden?
	if (!materialLoaded)
	{
		bool workingDlgOpened = false;
		if (!workingDlg)
		{
			workingDlgOpened = true;
			workingDlg = new spcCWorkInfoDlg();
			workingDlg->Init();
		}

		workingDlg->AddMessage("Loading materials...");		

		LoadMatlib();

		if (workingDlgOpened)
		{
			workingDlg->CloseWindow();
			workingDlg->DestroyWindow();
			//delete workingDlg;
			workingDlg = 0;
		}	
	};

	if (winID>0)
	{
		if (bShow)
		{
			spcTRegWindowInfo winInfo;
			spcConfig.GetWindowPosition(winID,winInfo);		
			MoveWindow(
				winInfo.position.pos.x,
				winInfo.position.pos.y,
				winInfo.position.size.cx,
				winInfo.position.size.cy,
				TRUE);		
		}
	}		

	CDialog::OnShowWindow(bShow, nStatus);
}

void spcCListMaterialDlg::Reset()
{
	UpdateData(TRUE);

	ctrl_mat_list.ResetContent();

	UpdateData(FALSE);
	UpdateWindow();
}

void spcCListMaterialDlg::SetDirty(bool dirty)
{
	isDirty = dirty;
}

void spcCListMaterialDlg::PreExit()
{
	spcCMatFilter* item;
	for (int z=0; z<spcConfig.matFilterList.GetNumInList(); z++)
	{
		item = spcConfig.matFilterList[z];
		if (item && item->IsDirty())
		{
			int result = AfxMessageBox ("Materialfilter "+item->name+" should be saved. Save id?", MB_YESNO);
			if (result == IDYES)
			{
				SaveMatlib(item->name);
			};
		};
	}
}
void spcCListMaterialDlg::OnSize(UINT nType, int cx, int cy) 
{	
	CDialog::OnSize(nType, cx, cy);
	if (winID>0  && IsWindowVisible())
	{
		RECT rect;
		GetWindowRect(&rect);
		spcConfig.SetWindowPosition(winID,rect);
		if (CMainFrame::mainframe) CMainFrame::mainframe->OnMoveChild();
	}

	bool result;
	spcCWindowResizeStyle* style;
	POSITION pos = childResizeList.GetHeadPosition();
	while (pos)
	{
		style = childResizeList.GetNext(pos);
		result = style->UpdateSize();		
		if (!result) return;
	};
		
}

void spcCListMaterialDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	if (winID>0 && IsWindowVisible())
	{
		RECT rect;
		GetWindowRect(&rect);
		spcConfig.SetWindowPosition(winID,rect);
		if (CMainFrame::mainframe) CMainFrame::mainframe->OnMoveChild();
	}
	
}

void spcCListMaterialDlg::OnCancel() 
{
	ShowWindow(SW_MINIMIZE);
	// CDialog::OnCancel();
}

void spcCListMaterialDlg::OnOK() 
{
	// CDialog::OnOK();
}

void spcCListMaterialDlg::OnNewFilter() 
{
	spcCInputDialog dlg;
	dlg.m_text="Type name of new filter:";	
	CString name;
	int result;
	bool ready = false;
	do
	{
		result = dlg.DoModal();
		ready = (result==IDOK);
		if (ready)
		{
			name = dlg.GetInput();	
			int filterIndex = spcConfig.FindMatFilterIndexByName(name);
			if (filterIndex>=0) ready = false;			
		};		
		
	} while (!ready);

	if (result==IDOK)
	{		
		ctrl_filter.AddString(name);
		
		spcCMatFilter* item = new spcCMatFilter;
		item->Init(name);
		item->SetDirty(true);
		spcConfig.matFilterList.Insert(item);

		if (CMainFrame::mainframe) CMainFrame::mainframe->UpdateMatFilterList();
						
		ctrl_filter.SelectString(0,name);	
		OnSelchangeFilter();		
	}
}

void spcCListMaterialDlg::OnDelFilter() 
{
	UpdateData(true);	
	int index = ctrl_filter.GetCurSel();
	if (index==LB_ERR) return;
	ctrl_filter.GetLBText(index,m_filter);

	CString filter = m_filter;
	CString filter2 = CString(NO_FILTER_FOLDER);
	filter.MakeLower();
	filter2.MakeLower();
	if (filter==filter2) return;

	int filterIndex = spcConfig.FindMatFilterIndexByName(m_filter);	
	if (filterIndex<0) return;

	int result = MessageBox("Do you really wanna delete the filter: \""+m_filter+"\" ?","Remove a filter",MB_ICONQUESTION | MB_YESNO);
	if (result == IDNO) return;
	
	int filterID = spcConfig.matFilterList[filterIndex]->id;

	zERR_MESSAGE(6,0,"B: SPC: Removing Filter \""+zSTRING(m_filter.GetBuffer(0))+"\" (id "+zSTRING(filterID)+")");

	// LibFlag aller Materialien entfernen
	zCClassDef*		classDef = zCMaterial::GetStaticClassDef();	
	int	numOfMats	= classDef->GetNumObjects();
	
	zCMaterial*	mat				= 0;
	for (int i=0;i<numOfMats;i++)
	{
		mat	= dynamic_cast<zCMaterial*>(classDef->GetObjectByIndex(i));
		if (mat && (mat->GetLibFlag() == filterID))
		{
			mat->SetLibFlag(spcCMatFilter::NullLib);
		};
	};
	
	// Entfernen des Filtes		
	spcConfig.matFilterList[filterIndex]->Deinit();
	spcConfig.matFilterList.RemoveOrderIndex(filterIndex);	

	UpdateData(false);	

	UpdateFilterList();

	ctrl_filter.SelectString(0,NO_FILTER_FOLDER);

	OnSelchangeFilter();
}


void spcCListMaterialDlg::SelectMaterial(zCMaterial *mat)
{
	if (!mat) return;
	int filterID = mat->GetLibFlag();
	int filterIndex = spcConfig.FindMatFilterIndexById(filterID);
	if (filterIndex<0) return;
	UpdateMaterialList(spcConfig.matFilterList[filterIndex]->name.GetBuffer(0));	
	ctrl_mat_list.SelectMaterial(mat);
}
