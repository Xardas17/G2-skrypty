// spcCInfoBar_Materials.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "SpacerView.h"
#include "MainFrm.h"
#include "spcCConfiguration.h"
#include "spcCInfoBar_Materials.h"
#include "spcCInputDialog.h"
#include "spcCNewMaterialDialog.h"
#include "spcCMatListbox.h"
// z-files
#include "z3d.h"
#include "zArchiver.h"
#include "zbuffer.h"
#include "zdisk.h"
// others
#include "spcCDibSection.h"

#ifdef _DEBUG
////#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Materials dialog


spcCInfoBar_Materials::spcCInfoBar_Materials(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInfoBar_Materials::IDD, pParent)
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Constructing Instance of MaterialPage...");

	//{{AFX_DATA_INIT(spcCInfoBar_Materials)
	// [EDENFELD] neu 1.33 Default Mapping auf 1 gesetzt
	m_mapping_x = 1.0f;
	m_mapping_y = 1.0f;

	m_filter = _T("");
	m_group = _T("");
	m_name = _T("");
	m_tex_info = _T("");
	m_tex_name = _T("");
	m_check_mapping = FALSE;	
	m_tex_movement = spcConfig.moveSpeedTex;
	m_quickslot = _T("");	
	m_filter_comment = _T("");
	m_color_alpha = 0;
	//}}AFX_DATA_INIT
	m_filter_fix = FALSE;
	dib = NULL;
	cur_mat = NULL;	

	for (int i=0;i<10;i++)
	{
		quickMatList.InsertEnd(0);
	}

	zERR_MESSAGE(7,zERR_END,"");
}


spcCInfoBar_Materials::~spcCInfoBar_Materials()
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing MaterialPage-Instance ...");	
	if (dib) delete dib;
	dib = NULL;
	zERR_MESSAGE(7,zERR_END,"");

	for (int i=0;i<10;i++)
	{
		zRELEASE(quickMatList[i]);
	}

}


void spcCInfoBar_Materials::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInfoBar_Materials)
	DDX_Control(pDX, IDC_FILTER_FIX, ctrl_filter_fix);
	DDX_Control(pDX, IDC_TEX_MOVE_SPIN, ctrl_tex_move_spin);	
	DDX_Control(pDX, IDC_MAT_MULTINEW, ctrl_multinew);
	DDX_Control(pDX, IDC_SELECT_TEXTURE, ctrl_select_tex);
	DDX_Control(pDX, IDC_REMOVE_TEXTURE, ctrl_remove_tex);
	DDX_Control(pDX, IDC_SET_MAPPING, ctrl_set_mapping);
	DDX_Control(pDX, IDC_MAP_Y, ctrl_mapping_y);
	DDX_Control(pDX, IDC_MAP_X, ctrl_mapping_x);
	DDX_Control(pDX, IDC_MAT_NAME, ctrl_matname);	
	DDX_Control(pDX, IDC_MAT_FILTER, ctrl_filter);
	DDX_Control(pDX, IDC_MAT_GROUP, ctrl_group);
	DDX_Control(pDX, IDC_TEX_PREVIEW, ctrl_preview);
	DDX_Text(pDX, IDC_MAP_X, m_mapping_x);
	DDX_Text(pDX, IDC_MAP_Y, m_mapping_y);
	DDX_CBString(pDX, IDC_MAT_FILTER, m_filter);
	DDX_CBString(pDX, IDC_MAT_GROUP, m_group);
	DDX_Text(pDX, IDC_MAT_NAME, m_name);
	DDX_Text(pDX, IDC_TEX_INFO, m_tex_info);
	DDX_Text(pDX, IDC_TEX_NAME, m_tex_name);
	DDX_Check(pDX, IDC_CHECKMAP, m_check_mapping);	
	DDX_Text(pDX, IDC_TEX_MOVEMENT, m_tex_movement);
	DDX_Text(pDX, IDC_QUICKSLOT, m_quickslot);	
	DDX_Text(pDX, IDC_FILTER_COMMENT, m_filter_comment);
	DDX_Text(pDX, IDC_COLOR_ALPHA, m_color_alpha);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCInfoBar_Materials, CDialog)
	//{{AFX_MSG_MAP(spcCInfoBar_Materials)
	ON_BN_CLICKED(IDC_SELECT_TEXTURE, OnButton_SelectTexture)
	ON_BN_CLICKED(IDC_MAT_COLORBTN, OnButton_Color)
	ON_CBN_SELCHANGE(IDC_MAT_FILTER, OnSelchangeMatFilter)
	ON_CBN_SELCHANGE(IDC_MAT_GROUP, OnSelchangeMatGroup)
	ON_BN_CLICKED(IDC_REMOVE_TEXTURE, OnButton_RemoveTexture)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SET_MAPPING, OnSetMapping)
	ON_BN_CLICKED(IDC_MAT_NEW_WO, OnMatNewPureMaterial)	
	ON_EN_CHANGE(IDC_MAT_NAME, OnChangeMatName)
	ON_EN_CHANGE(IDC_MAP_X, OnChangeMapX)
	ON_EN_CHANGE(IDC_MAP_Y, OnChangeMapY)
	ON_BN_CLICKED(IDC_MAT_AVCOLORBTN, OnMatAvcolorbtn)
	ON_BN_CLICKED(IDC_CHECKMAP, OnCheckmap)	
	ON_BN_CLICKED(IDC_MAT_MULTINEW, OnMatAddMaterials)
	ON_BN_CLICKED(IDC_MAT_UPDATE, OnMatUpdate)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TEX_MOVE_SPIN, OnDeltaposTexMoveSpin)
	ON_EN_CHANGE(IDC_TEX_MOVEMENT, OnChangeTexMovement)
	ON_EN_KILLFOCUS(IDC_TEX_MOVEMENT, OnKillfocusTexMovement)
	ON_EN_CHANGE(IDC_QUICKSLOT, OnChangeQuickslot)
	ON_BN_CLICKED(IDC_ASSIGN_QUICKSLOT, OnAssignQuickslot)
	ON_BN_CLICKED(IDC_FILTER_FIX, OnFilterFix)		
	ON_EN_CHANGE(IDC_COLOR_ALPHA, OnChangeColorAlpha)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Materials message handlers

void spcCInfoBar_Materials::OnButton_SelectTexture() 
{
	if (!cur_mat) return;
	UpdateData(true);

	zoptions->ChangeDir(DIR_TEX);	
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ,"Textures (*.tga)|*.tga||");

	zFILE::DirectFileAccess(true);
	int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{
		m_tex_name = dlg.GetFileName();
		m_tex_name.MakeLower();
		cur_mat->SetTexture(zSTRING(m_tex_name.GetBuffer(0)));
		CMainFrame::mainframe->UpdateMaterialList();
		// correct the mappingcoordinates of all polys with that material
		if (m_check_mapping) {
			if (m_mapping_x<=0 || m_mapping_y<=0)		// [EDENFELD] neu 1.33 aus ModSource: Mapping wird anders berechnet
				CSpacerView::view->WorldPolyApplyMapping(3,3,cur_mat);
			else
				CSpacerView::view->WorldPolyApplyMapping(m_mapping_x,m_mapping_y,cur_mat);
		}
	}	
	UpdateData(false);	
	MaterialModified();
	EditMaterial(cur_mat);	
}

void spcCInfoBar_Materials::OnButton_Color() 
{
	if (!cur_mat) return;
	UpdateData(true);
	CColorDialog dlg(RGB(cur_mat->GetColorR(),cur_mat->GetColorG(),cur_mat->GetColorB()));	
	// set dlg-values
	if (dlg.DoModal()) 
	{
		COLORREF cref;
		cref = dlg.GetColor();

		zCOLOR color = cur_mat->GetColor();
		color.r = GetRValue(cref);
		color.g = GetGValue(cref);
		color.b = GetBValue(cref);
		cur_mat->SetColor(color);
		MaterialModified();
	}
	UpdateData(false);
	
	OnPaint();
}

void spcCInfoBar_Materials::OnSelchangeMatFilter() 
{	
	if (m_filter_fix) 
	{
		UpdateData(false);
		return;
	}

	if (!cur_mat)  return;

	// Alter filter
	int filterIndexOld = spcConfig.FindMatFilterIndexByName(m_filter);	

	UpdateData(true);
	
	int index = ctrl_filter.GetCurSel();
	if (index>=0) ctrl_filter.GetLBText(index, m_filter);	

	spcCMatFilter* item;
	int filterIndex = spcConfig.FindMatFilterIndexByName(m_filter);
	if (filterIndex<0) 
	{ 
		filterIndex = filterIndexOld;
		UpdateData(false);
		return;
	}

	item = spcConfig.matFilterList[filterIndex];
	if (item->id>255)	item->id = spcCMatFilter::NullLib;
	if (item->id<0)		item->id = spcCMatFilter::NullLib;

	cur_mat->SetLibFlag(item->id);
	EnableCTRL(item->id!=0);
	
	if (filterIndexOld>=0)	spcConfig.matFilterList[filterIndexOld]->SetDirty();
	if (filterIndex>=0)		spcConfig.matFilterList[filterIndex]->SetDirty();

	CMainFrame::mainframe->UpdateMaterialList();

	UpdateData(false);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Materials::OnSelchangeMatGroup() 
{
	UpdateData(true);
	if (cur_mat) 
		cur_mat->SetMatGroupByString(zSTRING(m_group.GetBuffer(0)));
	
	MaterialModified();
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}


void spcCInfoBar_Materials::OnButton_RemoveTexture() 
{
	if (cur_mat) cur_mat->RemoveTexture();	
	m_tex_name = "";
	UpdateData(false);

	MaterialModified();
	EditMaterial(cur_mat);	
}

void spcCInfoBar_Materials::EnableCTRL(bool m)
{
	ctrl_matname.EnableWindow(m);
	ctrl_set_mapping.EnableWindow(m);
	ctrl_remove_tex.EnableWindow(m);
	ctrl_select_tex.EnableWindow(m);
	UpdateData(false);
}

void spcCInfoBar_Materials::EditMaterial(zCMaterial * mat)
{	
	UpdateData(true);
	if (mat!=cur_mat) 
	{		
		InitData();
		cur_mat = mat;				
	}
	if (!mat) { UpdateData(false);return; }
	
	int x,y;
	CString s;
	zCTexture* tex = cur_mat->GetTexture();
	zPOINT2 dir = cur_mat->GetTexAniMappingDir();
	m_filter = "";
	m_group = CString(cur_mat->GetMatGroupString().ToChar());
	m_mapping_x = cur_mat->GetDefaultMapping().n[0];
	m_mapping_y = cur_mat->GetDefaultMapping().n[1];
	m_name = CString(mat->GetName().ToChar());
	m_tex_name = "";
	m_tex_info = "";
	m_color_alpha = cur_mat->GetAlpha();	
	if (tex)
	{
		m_tex_name = CString(tex->GetName().ToChar());
		tex->GetPixelSize(x,y);
		s.Format("Size: %ix%i",x,y);
		m_tex_info = s;
	}
	
	m_tex_name.MakeLower();
	m_name.MakeLower();

	if (m_filter_fix && m_filter_fix_index>=0 && m_filter_fix_index<spcConfig.matFilterList.GetNumInList()) 
	{		
		int oldIndex = spcConfig.FindMatFilterIndexById(mat->GetLibFlag());		
		if (oldIndex != m_filter_fix_index) 
		{
			spcCMatFilter* newItem = spcConfig.matFilterList[m_filter_fix_index];
			spcCMatFilter* oldItem = spcConfig.matFilterList[oldIndex];
			mat->SetLibFlag(newItem->id);
			m_filter_comment = "changed";
			CMainFrame::mainframe->UpdateMaterialList();

			newItem->SetDirty();
			oldItem->SetDirty();
		}		
	}
	else m_filter_comment = "";
	
	spcCMatFilter item;
	int pos = spcConfig.FindMatFilterIndexById(mat->GetLibFlag());
	if (pos>=0) 
	{		
		int index = ctrl_filter.SelectString(0,spcConfig.matFilterList[pos]->name);
		m_filter = spcConfig.matFilterList[pos]->name;
		ctrl_filter.SetCurSel(index);
	}

	m_quickslot = "";
	for (int i=0;i<10;i++)
	{
		if (quickMatList[i] == cur_mat)
		{
			m_quickslot.Format("%i",i);
		};
	};

	EnableCTRL(mat->GetLibFlag()!=spcCMatFilter::NullLib);
	UpdateData(false);
	OnPaint();
}

void spcCInfoBar_Materials::InitData()
{		
	m_filter = "";
	m_group = "";
	m_mapping_x = 3;
	m_mapping_y = 3;
	m_name = "<none>";
	m_tex_name = "";
	m_tex_info = "";
	m_tex_name = "";
	// fill group-listbox with groups
	ctrl_group.ResetContent();	

	for (int i=0;i<zMAT_NUM_MAT_GROUP;i++)	
	{
		ctrl_group.AddString(zCMaterial::GetMatGroupString((zTMat_Group)i).ToChar());
	}

	// fill material-filterlist
	UpdateFilterList();
}

int dib_height, dib_width;

BOOL spcCInfoBar_Materials::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	if (!dib)
	{
		RECT rc;
		ctrl_preview.GetClientRect(&rc);
		dib_width  = 128;
		dib_height = 128;

		dib = new spcCDibSection;
		dib->Create(dib_width,dib_height,16);
	}

	m_filter_fix_index = -1;

	UpdateFilterList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void spcCInfoBar_Materials::OnPaint() 
{	
	//if (zrenderer) zrenderer->SetPolyDrawMode(zRND_DRAW_MATERIAL);
	
	CPaintDC dc(this);
	CDialog::OnPaint();

	CDC* pDC = ctrl_preview.GetDC();
	RECT rc;
	ctrl_preview.GetClientRect(&rc);

	zCTexture* tex  = NULL;
	pDC->FillSolidRect( &rc, RGB(0,0,0) );
	if (cur_mat)
	{		
		pDC->FillSolidRect(&rc,RGB(cur_mat->GetColorR(),cur_mat->GetColorG(),cur_mat->GetColorB()));
		tex = cur_mat->GetTexture();
		if (tex)
		{
			ConvertTextureToDIB(tex,dib);

			// tex->Draw((unsigned char*)dib->GetDataPtr(), dib->GetWidth(), dib->GetHeight(), 16, VideoPitch,FALSE);
			dib->Blit(pDC,4,4);
		}		
	}	
}

zCMaterial* spcCInfoBar_Materials::GetMaterial()
{
	return cur_mat;
}

void spcCInfoBar_Materials::UpdateFilterList()
{	
	ctrl_filter.ResetContent();
	CString s;
	for (int pos =0; pos<spcConfig.matFilterList.GetNumInList(); pos++)
	{
		ctrl_filter.AddString(spcConfig.matFilterList[pos]->name);
	}

	if (cur_mat)
	{
	// refresh the prev. selection		
		int pos2 = spcConfig.FindMatFilterIndexById(cur_mat->GetLibFlag());		
		if (pos2>0) 
		{
			spcCMatFilter* item2 = spcConfig.matFilterList[pos2];
			int index = ctrl_filter.SelectString(0,item2->name);	
			ctrl_filter.SetCurSel(index);
		}
	}
	
	UpdateData(false);
}

void spcCInfoBar_Materials::GetMaterialMapping(float & x, float & y)
{
	UpdateData(true);
	x = m_mapping_x;
	y = m_mapping_y;
}

void spcCInfoBar_Materials::OnSetMapping() 
{
	UpdateData(true);
	if (!cur_mat) return;
	cur_mat->SetDefaultMapping( zPOINT2((zREAL)m_mapping_x,(zREAL)m_mapping_y));
	MaterialModified();
}


void spcCInfoBar_Materials::OnOK() 
{
	// prevent that ENTER will close the dialog
	// CDialog::OnOK();
}

void spcCInfoBar_Materials::OnChangeMatName() 
{
	UpdateData(true);
	cur_mat->SetName(zSTRING(m_name.GetBuffer(0)));
	UpdateData(false);
	
	MaterialModified();
	CMainFrame::mainframe->UpdateMaterialList();	
}

void spcCInfoBar_Materials::OnChangeColorAlpha() 
{
	UpdateData(true);
	zCOLOR color = cur_mat->GetColor();
	color.alpha = m_color_alpha;
	cur_mat->SetColor(color);		
	MaterialModified();		
	UpdateData(false);
}

void spcCInfoBar_Materials::OnChangeMapX() 
{
	OnSetMapping();	
}

void spcCInfoBar_Materials::OnChangeMapY() 
{
	OnSetMapping();	
}

void spcCInfoBar_Materials::OnMatAvcolorbtn()
{
	if (!cur_mat) return;
	if (!cur_mat->GetTexture()) return;
	UpdateData(true);
	
	zCOLOR color = cur_mat->GetColor();
	zBYTE alpha = color.alpha;
	color = cur_mat->GetTexture()->GetTextureInfo().averageColor;
	color.alpha = alpha;
	cur_mat->SetColor(color);

	MaterialModified();

	UpdateData(false);
	OnPaint();
}

void spcCInfoBar_Materials::OnCheckmap() 
{
	// TODO: Add your control notification handler code here
	
}

int spcCInfoBar_Materials::SelectMaterialFilter()
{
	// Neues-Material Dialog anzeigen
	spcCNewMaterialDialog newMatDlg;				
	spcCMatFilter* item;		
	for (int i=0; i<spcConfig.matFilterList.GetNumInList(); i++)
	{
		item = spcConfig.matFilterList[i];
		newMatDlg.AddFilter(item->name);
	}	
	int result = newMatDlg.DoModal();
	if (result==IDCANCEL) return -1;

	// FilterID auswaehlen
	CString selString;
	int selection = newMatDlg.GetSelection(selString);
	int filterID = spcCMatFilter::NullLib;
	switch (selection)
	{
	case spcCNewMaterialDialog::NEW:
		{
			int index = spcConfig.FindMatFilterIndexByName(selString);
			if (index>=0) 
			{
				spcCMatFilter* item = spcConfig.matFilterList[index];
				item->SetDirty();
				filterID = item->id;
				AfxMessageBox("Filter already exists. Using it ...");
			}
			else
			{
				spcCMatFilter* item = new spcCMatFilter();
				item->Init(selString);
				item->SetDirty();
				spcConfig.matFilterList.Insert(item);			
				filterID = item->id;
				CMainFrame::mainframe->UpdateMatFilterList();
			};
		}	break;
		
	case spcCNewMaterialDialog::SELECT:		
		{
			int index = spcConfig.FindMatFilterIndexByName(selString);			
			spcCMatFilter* item = spcConfig.matFilterList[index];
			if (item)
			{
				item->SetDirty();
				filterID = item->id;						
			}
		}	break;
	}	
	return filterID;
}

void spcCInfoBar_Materials::OnMatAddMaterials() 
{
	// OnButton_SelectTexture();		
	UpdateData(true);
	
	zoptions->ChangeDir(DIR_DATA);
	zFILE::DirectFileAccess(true);
		int flags = OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_LONGNAMES;
		CFileDialog dlg(TRUE,"","",flags,"Textures (*.tga)|*.tga|All files (*.*)|*.*||");
		dlg.m_ofn.nMaxFile = 2048;
		dlg.m_ofn.lpstrFile = new char[2048];
		memset(dlg.m_ofn.lpstrFile,0,2048);			
		int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	zoptions->ChangeDir(DIR_TEX);
	
	if (result == IDOK)
	{		
				
		int filterID = SelectMaterialFilter();
		if (filterID>=0)
		{

			zFILE* matFile = zfactory->CreateZFile("");
			CString pathname;
			POSITION pos = dlg.GetStartPosition();
			while (pos)
			{
				pathname = dlg.GetNextPathName(pos);

				matFile->SetPath(pathname.GetBuffer(0));

				m_name = matFile->GetFilename().ToChar();
				m_mapping_x=1;
				m_mapping_y=1;			

				zSTRING filename = matFile->GetFilename();
				cur_mat = zCMaterial::SearchName(filename);
				if (!cur_mat) cur_mat = new zCMaterial;
				cur_mat->AddRef();
				cur_mat->SetUsage(zCMaterial::zMAT_USAGE_LEVEL);
				cur_mat->SetLibFlag(filterID);			
				cur_mat->SetTexture(matFile->GetPath());			
				cur_mat->SetName(matFile->GetFilename());
				cur_mat->SetDefaultMapping( zPOINT2((zREAL)m_mapping_x,(zREAL)m_mapping_y));			
		
			}
			delete matFile;
			matFile=0;

			int filterIndex = spcConfig.FindMatFilterIndexById(filterID);
			spcCMatFilter* item = spcConfig.matFilterList[filterIndex];
			item->SetDirty();
			CMainFrame::mainframe->UpdateMaterialList(item->name.GetBuffer(0));
		}
	}	
	UpdateData(false);	
}



void spcCInfoBar_Materials::OnMatNewPureMaterial() 
{	
	spcCInputDialog dlg;	
	dlg.SetInput("[name]");
	if (dlg.DoModal()==IDOK)
	{		
		int filterID = SelectMaterialFilter();
		if (filterID>=0) 
		{
			zCMaterial* mat = new zCMaterial(zSTRING(dlg.GetUpperInput().GetBuffer(0)));
 			mat->AddRef();
			mat->SetUsage(zCMaterial::zMAT_USAGE_LEVEL);
			mat->SetLibFlag(filterID);
			UpdateData(false);
			EditMaterial(mat);
		}
		
		MaterialModified();

		int filterIndex = spcConfig.FindMatFilterIndexById(filterID);
		spcCMatFilter* item = spcConfig.matFilterList[filterIndex];				
		CMainFrame::mainframe->UpdateMaterialList(item->name.GetBuffer(0));		
	}		
}

void spcCInfoBar_Materials::OnMatUpdate() 
{
	UpdateData(true);

	if (!cur_mat) return;	
	
	zCTexture* tex = cur_mat->GetTexture();
	if (!tex) return;

	tex->ForceConvertAndReloadTexture();
	
	UpdateData(false);
	OnPaint();
}

void spcCInfoBar_Materials::OnDeltaposTexMoveSpin(NMHDR* pNMHDR, LRESULT* pResult) 	
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	UpdateData(true);

	if (pNMUpDown->iDelta<0) 
	{
		if (m_tex_movement<0.095)		m_tex_movement = m_tex_movement + 0.010;
		else if (m_tex_movement<1.95)	m_tex_movement = m_tex_movement + 0.10;
		else if (m_tex_movement<9.95)	m_tex_movement = m_tex_movement + 1.0;
	}
	if (pNMUpDown->iDelta>0) 
	{
		if (m_tex_movement>2.05)		m_tex_movement = m_tex_movement - 1.0;
		else if (m_tex_movement>0.105)	m_tex_movement = m_tex_movement - 0.10;
		else if (m_tex_movement>0.0105)	m_tex_movement = m_tex_movement - 0.010;
	}

	if (m_tex_movement>10.0) m_tex_movement = 10.0;
	if (m_tex_movement<0.01) m_tex_movement = 0.010;
	
	CString s;s.Format("%.2f",m_tex_movement);
	m_tex_movement = atof(s.GetBuffer(0));

	spcConfig.moveSpeedTex = (float)m_tex_movement;

	UpdateData(false);

	*pResult = 1;
}

void spcCInfoBar_Materials::OnChangeTexMovement() 
{
	/*
	UpdateData(true);
	// m_tex_movement = float( int(m_tex_movement*100.0f) / 100.0f );

	spcConfig.moveSpeedTex = m_tex_movement;

	UpdateData(false);
	*/
}

void spcCInfoBar_Materials::OnKillfocusTexMovement() 
{
	UpdateData(true);
	if (m_tex_movement>9.95) m_tex_movement = 10.0;
	if (m_tex_movement<0.0105) m_tex_movement = 0.010;
	
	spcConfig.moveSpeedTex = (float)m_tex_movement;
	UpdateData(false);
}

void spcCInfoBar_Materials::OnChangeQuickslot() 
{

	
}

void spcCInfoBar_Materials::OnAssignQuickslot() 
{
	UpdateData(true);	
	if (m_quickslot.IsEmpty()) return;
	int value = zSTRING(m_quickslot.GetBuffer(0)).ToInt();
	m_quickslot="";
	if (value>0 || value<=9) 
	{
		zRELEASE(quickMatList[value]);
		m_quickslot.Format("%i",value);	
		quickMatList[value] = cur_mat;
		if (quickMatList[value]) 
		{
			quickMatList[value]->AddRef();
			Beep(20000,100);
		}
	}
	UpdateData(false);
}

void spcCInfoBar_Materials::OnFilterFix() 
{			
	if (!m_filter_fix)
	{
		int index = ctrl_filter.GetCurSel();
		if (index<0) return;
		
		CString filterName;
		ctrl_filter.GetLBText(index, filterName);					
		int filterIndex = spcConfig.FindMatFilterIndexByName(filterName);
		if (filterIndex<0)  return;
		
		m_filter_fix = true;
		m_filter_fix_index	= filterIndex;
		
	}
	else 
	{
		m_filter_fix = false;			
	}	

	ctrl_filter.EnableWindow(!m_filter_fix);
	ctrl_filter_fix.SetCheck(m_filter_fix);
	m_filter_comment = "";
	UpdateData(false);
}

bool spcCInfoBar_Materials::ActivateQuickSlot(int nr)
{
	if (nr<=0 || nr>9) return false;
	if (quickMatList[nr])
	{
		EditMaterial(quickMatList[nr]);
		Beep(20000,100);
		return true;
	};
	return false;
}


void spcCInfoBar_Materials::MaterialModified()
{
	if (!cur_mat) return;
	int filterID = cur_mat->GetLibFlag();
	int filterIndex = spcConfig.FindMatFilterIndexById(filterID);
	spcCMatFilter* item = spcConfig.matFilterList[filterIndex];
	item->SetDirty();	
	if (CMainFrame::mainframe) 
	{			
		CMainFrame::mainframe->HandleObjChange(cur_mat);
	}
}
