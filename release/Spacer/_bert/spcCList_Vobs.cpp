// spcCListVobDlg.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "mainfrm.h"
#include "SpacerView.h"
#include "SpacerDoc.h"
#include "spcCInfoBar_Events.h"
#include "spcCInfoBar_Camera.h"
#include "spcCConfiguration.h"
#include "spcCList_Vobs.h"

// z-files
#include "z3d.h"
#include "zWaynet.h"
#include "zWorld.h"
#include "zCSCamera.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// spcCListVobDlg dialog

// some global variables (used inside recursive functions)
static zCTree<zCVob>	*gVobTree;


/////////////////////////////////////////////////////////////////////////////
// spcCListVobDlg

spcCListVobDlg::spcCListVobDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCListVobDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCListVobDlg)	
	m_sorted = FALSE;	
	//}}AFX_DATA_INIT
	current_world		= NULL;
	// current_vob		= NULL;
	CD_hItem			= NULL;	
	treeCtrlImageList	= 0;
	hItemMainVob		= 0;
	updateAll			= false;
	winID				= 0;
}

spcCListVobDlg::~spcCListVobDlg()
{
	// zRELEASE(current_vob);

	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing Voblist-Instance...");
	zERR_MESSAGE(7,zERR_END,"");
};

void spcCListVobDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCListVobDlg)	
	DDX_Control(pDX, IDC_SORTED, ctrl_sorted);
	DDX_Control(pDX, IDC_REFRESH, ctrl_refresh);
	DDX_Control(pDX, IDC_VOB_GOTO, ctrl_action);
	DDX_Control(pDX, IDC_PRINT_TO_FILE, ctrl_printbutton);	
	DDX_Control(pDX, IDC_VOB_LIST, ctrl_browse);	
	DDX_Check(pDX, IDC_SORTED, m_sorted);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCListVobDlg, CDialog)
	//{{AFX_MSG_MAP(spcCListVobDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_VOB_LIST, OnVoblistDblclk)
	ON_NOTIFY(TVN_DELETEITEM, IDC_VOB_LIST, OnVoblistDeleteitem)
	ON_NOTIFY(TVN_SELCHANGED, IDC_VOB_LIST, OnVoblistSelchanged)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)		
	ON_NOTIFY(NM_SETFOCUS, IDC_VOB_LIST, OnSetfocusVobList)
	ON_BN_CLICKED(IDC_PRINT_TO_FILE, OnPrintToFile)	
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_MOVE()
	ON_NOTIFY(NM_CLICK, IDC_VOB_LIST, OnClickVobList)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCListVobDlg message handlers


HTREEITEM spcCListVobDlg::GetHandleByVob(zCVob* vob)
{	
	return voblist.GetHandleByVob(vob);
}

HTREEITEM spcCListVobDlg::GetFolderByVob(zCVob* _vob, zCVob* folderVob)
{
	HTREEITEM hParent = voblist.GetHandleByVob(_vob);
	return GetFolder(folderVob, hParent);	
}



void spcCListVobDlg::OnVoblistDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(true);

	HTREEITEM hItem = ctrl_browse.GetSelectedItem();
	if (hItem==0) return;
		
	zCVob* vob = GetVobByHandle(hItem);		
	if (!vob) return;

	CSpacerView::view->VobGoto(vob);	

	// CSpacerView::view->SetFocus();		

	*pResult = 1;
}


void spcCListVobDlg::OnVoblistDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	*pResult = 0;
}

void spcCListVobDlg::OnVoblistSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	if (ctrl_browse.GetCount()<=0) return;

//	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;	

	HTREEITEM hItem = ctrl_browse.GetSelectedItem();
	if (hItem==0) return;

	zCVob* vob = GetVobByHandle(hItem);
	if (!vob) return;

	ctrl_printbutton.EnableWindow(true);

	SetWindowText(GetFolderName(vob) + " -> "+GetVobItemName(vob));	

	if (updateAll) CMainFrame::mainframe->ObjectSelection(vob,this,true);	
	
	updateAll = true;	
	UpdateData(FALSE);
	
	// CSpacerView::view->SetActiveWindow();
	// CSpacerView::view->SetFocus();
	*pResult = 0;
}


HTREEITEM spcCListVobDlg::VobInsert(zCVob* newvob, zCVob* parentvob)
{
	HTREEITEM hItemParent = TVI_ROOT;
	// find the parentvob in the tree
	if (parentvob)
	{
		if (parentvob->GetVobType()==zVOB_TYPE_LEVEL_COMPONENT)
		{
			hItemParent = GetFolderByVob(parentvob,newvob);
		}
		else
		{
			hItemParent = GetHandleByVob(parentvob);
			if (hItemParent==NULL) hItemParent = TVI_ROOT;
		}
	}
	// build item-structure	
	HTREEITEM TreeItemHandle = CreateVobTreeItem(newvob, hItemParent, ICON_VOB_NEW);
		
	spcCVobTreeItem* vobTreeItem = new spcCVobTreeItem(TreeItemHandle,newvob);
	voblist.AddTail(vobTreeItem);	

	// insert recursive
	HTREEITEM hItemChild = TreeItemHandle;
	zCTree<zCVob>* tree = 0;
	if (newvob->globalVobTreeNode) tree = newvob->globalVobTreeNode->GetFirstChild();	
	while (tree)
	{		
		CreateVobTree(tree,hItemChild);
		tree = tree->GetNextChild();
	}

	if (hItemParent && (hItemParent!=TVI_ROOT)) ctrl_browse.EnsureVisible(hItemParent);
		
	return TreeItemHandle;
}

// recursive version 
void spcCListVobDlg::VobDeleteRec(zCVob * vob)
{
	if (!vob) return ;
	HTREEITEM hItemToKill = NULL;

	// test the vob of beeing a parent
	hItemToKill = GetHandleByVob(vob);
	if (hItemToKill==NULL) return ; // TODO: please throw an acception
	if (ctrl_browse.ItemHasChildren(hItemToKill))
	{
		HTREEITEM hChildToKill = ctrl_browse.GetChildItem(hItemToKill);
		while (hChildToKill!=NULL)
		{	
			zCVob* cVob = GetVobByHandle(hChildToKill);
			VobDelete(cVob);			
			hChildToKill = ctrl_browse.GetChildItem(hItemToKill);
		}
	}

	ctrl_browse.DeleteItem(hItemToKill);
	voblist.DeleteHandleVobRef(vob);
}

// in this version, only rootVobs may be deleted. Childs are deleted recursively
// special procedure for levelcomponents is implemented here
// all vobs had been deleted from world yet
void spcCListVobDlg::VobDelete(zCVob * vob)
{
	if (!vob) return ;
	UpdateData(TRUE);
	HTREEITEM hItemToKill = NULL;

	if (vob->GetVobType()==zVOB_TYPE_LEVEL_COMPONENT)
	{
		OnRefresh(); // refresh all
		return;
	}

	// handle ermitteln
	hItemToKill = GetHandleByVob(vob);
	if (hItemToKill==NULL) return ;

	// Untersuchen, ob der Vob childs besitzt: dann auch diese entfernen
	if (ctrl_browse.ItemHasChildren(hItemToKill))
	{
		HTREEITEM hChildToKill = ctrl_browse.GetChildItem(hItemToKill);
		while (hChildToKill!=NULL)
		{	
			zCVob* cVob = GetVobByHandle(hChildToKill);
			VobDeleteRec(cVob);
			hChildToKill = ctrl_browse.GetChildItem(hItemToKill);
		}
	}

	ctrl_browse.SelectItem(NULL);

	ctrl_browse.DeleteItem(hItemToKill);

	voblist.DeleteHandleVobRef(vob);

	UpdateData(FALSE);	
	RedrawWindow();
	// ctrl_browse.RedrawWindow();	
}

void spcCListVobDlg::VobSelect(zCVob * vob)
{
	zERR_MESSAGE(8,0,"B: SPC: spcCListVobDlg::VobSelect");

	UpdateData(TRUE);	
	
	HTREEITEM TreeItemHandle = (vob ? GetHandleByVob(vob) : 0);
	
	updateAll = false;
	ctrl_browse.SelectItem(TreeItemHandle);
	ctrl_browse.EnsureVisible(TreeItemHandle);

	// CMainFrame::mainframe->ActivateFrame();
}

zCVob* spcCListVobDlg::GetVobByHandle(HTREEITEM hItem)
{	
	TV_ITEM item;
	item.hItem = hItem;
	item.mask = TVIF_HANDLE;
	item.cchTextMax = 0;
	if (ctrl_browse.GetItem(&item))	return (zCVob*)item.lParam; else return NULL;
}


// global functions

void spcCListVobDlg::CreateVobTree(zCTree<zCVob>* node, HTREEITEM parent)
{		
	HTREEITEM TreeItemHandle = CreateVobTreeItem(node->GetData(), parent, ICON_VOB);

	spcCVobTreeItem* vobTreeItem = new spcCVobTreeItem(TreeItemHandle,node->GetData());
	voblist.AddTail(vobTreeItem);	

	node = node->GetFirstChild();
	while (node!=NULL)
	{	
		CreateVobTree(node,TreeItemHandle);
		node = node->GetNextChild();
	}	
}
void spcCListVobDlg::CreateBaseVobTree(zCTree<zCVob>* node, HTREEITEM parent)
{
	zCVob* vob = node->GetData();
//	if (dynamic_cast<spcCDragVob*>(gVob)) return;
//	if (dynamic_cast<zCCSCamera*>(gVob)) return;
//	if (gVob->GetVobType()==zVOB_TYPE_CAMERA) return;

	// build item-structure	

	int image = ICON_VOB_ROOT;
	if (vob->GetVobType()==zVOB_TYPE_LEVEL_COMPONENT) image = ICON_LEVCOMP;

	HTREEITEM HItem = CreateVobTreeItem(vob,parent,image);
	
	zSTRING className;

	if (vob->GetVobType()==zVOB_TYPE_LEVEL_COMPONENT)
	{
		hItemMainVob  = HItem;

		spcCVobTreeDrawer* VobItem = new spcCVobTreeDrawer(HItem,vob);
		voblist.AddTail(VobItem);
		HTREEITEM ToItem = HItem;
		node = node->GetFirstChild();

		while (node!=NULL)
		{				
			ToItem = GetFolder(node->GetData(),HItem);			
						
			// create subtree
			CreateVobTree(node,ToItem);

			if (m_sorted) ctrl_browse.SortChildren(ToItem);
			node = node->GetNextChild();
		}		
	}
	else
	{
		spcCVobTreeItem* VobItem = new spcCVobTreeItem(HItem,vob);
		voblist.AddTail(VobItem);
		node = node->GetFirstChild();
		while (node!=NULL)
		{	
			CreateVobTree(node,HItem);
			node = node->GetNextChild();
		}		
	}

	if (m_sorted) ctrl_browse.SortChildren(HItem);	
 }

void spcCListVobDlg::BuildTree(zCWorld* world)
{	
	if (!world) return;
	UpdateData(TRUE);

	hItemMainVob = 0;
	current_world = world;	

	// zRELEASE(current_vob);
	
	voblist.RemoveAllTreeItems();
	folderList.RemoveAll();
	ctrl_browse.SelectItem(0);	
	ctrl_browse.DeleteAllItems();

	RedrawWindow();
	
	zCTree<zCVob>* tree = world->globalVobTree.GetFirstChild();	
	while (tree)
	{
		CreateBaseVobTree(tree,TVI_ROOT);
		tree = tree->GetNextChild();
	}
	if (m_sorted) ctrl_browse.SortChildren(TVI_ROOT);
		
	ctrl_browse.Expand(hItemMainVob, TVE_EXPAND);

	m_sorted = FALSE; // SOrted nach jedem Refresh zuruecksetzen
	UpdateData(FALSE);
	RedrawWindow();
}

void spcCListVobDlg::OnRefresh() 
{
	hItemMainVob = 0;	
	BuildTree(current_world);	
	CSpacerView::view->SetFocus();
}

void spcCListVobDlg::CDcreateTree()
{
	if (CD_hItem!=NULL) return;
	UpdateData(TRUE);
	// build item-structure	
	TV_INSERTSTRUCT insertItem;
    insertItem.hParent = TVI_ROOT;
    insertItem.hInsertAfter = TVI_FIRST;
    insertItem.item.mask = TVIF_TEXT;	
	insertItem.item.pszText = "colliding vobs";
	// insert root-item
	CD_hItem = ctrl_browse.InsertItem(&insertItem);
	// update window
	UpdateData(FALSE);
	ctrl_browse.RedrawWindow();
}

void spcCListVobDlg::CDaddVob(zCVob * vob)
{
	if (CD_hItem==NULL) CDcreateTree();

	if (!CD_hItem) return;
	UpdateData(TRUE);
	// build item-structure	
	TV_INSERTSTRUCT insertItem;
    insertItem.hParent = CD_hItem;
    insertItem.hInsertAfter = TVI_FIRST;
    insertItem.item.mask = TVIF_TEXT | TVIF_PARAM;	
	insertItem.item.lParam = (LPARAM)vob;

	// generate name of item
	CString str = GetVobItemName(vob);
	insertItem.item.pszText = str.GetBuffer(0);
	// insert root-item
	ctrl_browse.InsertItem(&insertItem);
	ctrl_browse.Expand( CD_hItem, TVE_EXPAND );
	// update window
	UpdateData(FALSE);
	ctrl_browse.RedrawWindow();
}

void spcCListVobDlg::CDremoveTree()
{
	if (!CD_hItem) return;
	UpdateData(TRUE);
	// remove tree
	ctrl_browse.DeleteItem(CD_hItem);
	CD_hItem=NULL;
	UpdateData(FALSE);
	ctrl_browse.RedrawWindow();
}



void spcCListVobDlg::OnSetfocusVobList(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	*pResult = 0;
}

zSTRING visualName;
const zSTRING CVS_SEPARATOR = "\t";

void WriteVobTreeToFile(zCTree<zCVob>* node, zFILE* file, int deepness=0)
{
	zCVob* vob = node->GetData();
	if (vob) 
	{
		zSTRING vob_description;
			
		// first the classname

		vob_description = vob_description + vob->GetClassDef()->GetClassName_();
		
		vob_description = vob_description + CVS_SEPARATOR;	// now the vobname

		if (!vob->GetVobName().IsEmpty()) vob_description = vob_description + vob->GetVobName();		

		vob_description = vob_description + CVS_SEPARATOR;	// next is the visual-name

		if (vob->GetVisual())
		{					
			visualName = vob->GetVisual()->GetVisualName();
			visualName.Lower();
			vob_description = vob_description + visualName;
		};
		
		vob_description = vob_description + CVS_SEPARATOR;	// collision

		if (vob->GetCollDetDyn()) vob_description = vob_description + "dyn";
		if (vob->GetCollDetDyn() && vob->GetCollDetStat()) vob_description = vob_description + ",";
		if (vob->GetCollDetStat()) vob_description = vob_description + "stat";

		vob_description = vob_description + CVS_SEPARATOR;	// trigger-targets

		const zSTRING* s;
		int i=0;
		do
		{
			s = vob->GetTriggerTarget(i);
			if (s) 
			{
				if (i>0) vob_description = vob_description + ",";
				vob_description = vob_description + s;
			}
			i++;
		} while(s);

		vob_description = vob_description + CVS_SEPARATOR;	// presetname

		vob_description = vob_description + vob->GetVobPresetName();

		float x,y,z;
		vob->GetPositionWorld(x,y,z);

		vob_description = vob_description + CVS_SEPARATOR;	// x-Koordinate

		vob_description = vob_description + zSTRING(x);

		vob_description = vob_description + CVS_SEPARATOR;	// y-Koordinate

		vob_description = vob_description + zSTRING(y);

		vob_description = vob_description + CVS_SEPARATOR;	// z-Koordinate

		vob_description = vob_description + zSTRING(z);
		
		// END
		
		file->Write(vob_description+"\n");
	}
	
	node = node->GetFirstChild();
	while (node!=NULL)
	{	
		WriteVobTreeToFile(node,file, deepness+1);
		node = node->GetNextChild();
	}	
}

void spcCListVobDlg::OnPrintToFile() 
{
	if (ctrl_browse.GetCount()<=0) return;
	if (!CSpacerDoc::doc->GetWorld()) return;

	//HTREEITEM hItem = ctrl_browse.GetSelectedItem();
	//if (hItem==0) return;
	
	// if (!ctrl_browse.ItemHasChildren(hItem)) return;

	zoptions->ChangeDir(DIR_WORLD);
	CString filter = "Textfile (*.csv)|*.csv||";
	CFileDialog* dlg = new CFileDialog(false,"csv","voblist.csv",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);
	
	zFILE::DirectFileAccess(true);
	int result = dlg->DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)	{
		CString fileName = dlg->GetPathName();
		delete (dlg);

		zFILE* file = zfactory->CreateZFile(zSTRING(fileName.GetBuffer(0)));
		file->Create();

		file->Write("Class"+CVS_SEPARATOR+"Vobname"+CVS_SEPARATOR+"Visualname"+CVS_SEPARATOR+"Collision"+CVS_SEPARATOR+"Triggertargets"+CVS_SEPARATOR+"Preset"+CVS_SEPARATOR+"x"+CVS_SEPARATOR+"y"+CVS_SEPARATOR+"z\n");
		WriteVobTreeToFile(&CSpacerDoc::doc->GetWorld()->globalVobTree,file);

		file->Close();
		delete file;
	}

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}



void spcCListVobDlg::Reset()
{
	UpdateData(TRUE);		

	current_world=0;	
		
	ctrl_browse.SelectItem(0);
	ctrl_browse.DeleteAllItems();
	voblist.RemoveAllTreeItems();


	UpdateData(FALSE);
	UpdateWindow();
}

CString spcCListVobDlg::GetVobItemName(zCVob * vob)
{
	CString str="";
	if (vob)
	{
		// generate the name of the item	
		if (!vob->GetVobName().IsEmpty())
		{
			str = CString("\"")+vob->GetVobName().ToChar()+CString("\"");		
		}
		else if (vob->GetVisual())
		{
			str = CString("'")+vob->GetVisual()->GetVisualName().ToChar()+CString("'");
		}			
		else
		{	
			str.Format("vob %i",vob->GetVobID());	
		}

		str = str+" ("+CString(vob->GetClassDef()->GetClassName_().ToChar())+")";
		#ifdef _DEBUG
			str = str+CString(" : ")+CString(zSTRING(vob->GetRefCtr()).ToChar());
		#endif
	}
	return str;
}

CString spcCListVobDlg::GetFolderName(zCVob *vob)
{
	CString name = "";
	if (vob) 
	{
		name = vob->GetClassDef()->GetClassName_().ToChar();	
		zCVisual* visual = vob->GetVisual();
		if (visual) name += CString(" (")+visual->GetClassDef()->GetClassName_().ToChar()+CString(")");	
	}
	return name;
}

HTREEITEM spcCListVobDlg::GetFolder(zCVob *vob, HTREEITEM parent)
{
	if (!vob) return 0;
	
	CString folderName = GetFolderName(vob);
	
	CString folderIndex;
	folderIndex.Format("%li_%s",(long int)parent,folderName);	

	HTREEITEM resultItem;
	void* foundItem;
	BOOL found = folderList.Lookup(folderIndex, foundItem);
	if (!found)
	{		
		resultItem = CreateVobTreeFolder(folderName, parent, ICON_FOLDER);		
		folderList[folderIndex] = resultItem;
	}
	else
	{
		resultItem = (HTREEITEM)foundItem;
	};
	
	return resultItem;
}

HTREEITEM spcCListVobDlg::CreateVobTreeItem(zCVob *vob, HTREEITEM parent, int icon_type)
{
	zERR_MESSAGE(9,0,"B: SPC: CreatingVobTreeItem for vob "+vob->GetClassName_()+"/"+vob->GetVobName());
	TVINSERTSTRUCT insertItem;
    insertItem.hParent = parent;
    insertItem.hInsertAfter = TVI_FIRST;
	insertItem.item.lParam = (LPARAM)vob;

	insertItem.item.mask = TVIF_PARAM | TVIF_TEXT;
	if (icon_type>=0) insertItem.item.mask = insertItem.item.mask | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	insertItem.item.iImage = icon_type;
	insertItem.item.iSelectedImage = icon_type;

	CString str;
	// generate the name of the item
	if (icon_type != ICON_LEVCOMP)
	{
		str = GetVobItemName(vob);
	}
	else
	{
		if (vob->GetVisual()) str = "Level \""+CString(vob->GetVisual()->GetVisualName().ToChar())+"\"";
		else str = "Level - unnamed";
	};
	insertItem.item.pszText = str.GetBuffer(0);
	// insert
	HTREEITEM resultItem = ctrl_browse.InsertItem(&insertItem);

	return resultItem;
}


HTREEITEM spcCListVobDlg::CreateVobTreeFolder(CString name, HTREEITEM parent, int icon_type)
{
	// build item-structure	
	TVINSERTSTRUCT insertItem;
    insertItem.hParent = parent;
    insertItem.hInsertAfter = TVI_LAST;

	insertItem.item.mask = TVIF_PARAM | TVIF_TEXT;
	if (icon_type>=0) insertItem.item.mask = insertItem.item.mask | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	insertItem.item.iImage = icon_type;
	insertItem.item.iSelectedImage = icon_type;

	insertItem.item.lParam = NULL; // is this ok?
	insertItem.item.pszText = name.GetBuffer(0);
	// insert
	return ctrl_browse.InsertItem(&insertItem);
}


BOOL spcCListVobDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	treeCtrlImageList = new CImageList;
	treeCtrlImageList->Create(IDR_ICONS_VOBLIST, 12, 4, RGB(255,255,255));
	ctrl_browse.SetImageList(treeCtrlImageList, TVSIL_NORMAL);	

	spcCWindowResizeStyle* style;

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_browse,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_refresh,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_action,this, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_sorted,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);	
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_printbutton,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
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
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void spcCListVobDlg::OnSize(UINT nType, int cx, int cy) 
{	
	CDialog::OnSize(nType, cx, cy);
	if (winID>0 && IsWindowVisible())
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


void spcCListVobDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

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
}

void spcCListVobDlg::OnMove(int x, int y) 
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

void spcCListVobDlg::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	// CDialog::OnOK();
}

void spcCListVobDlg::OnCancel() 
{
	ShowWindow(SW_MINIMIZE);
	
	// CDialog::OnCancel();
}


void spcCListVobDlg::OnClickVobList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CSpacerView::view->SetFocus();	
	*pResult = 0;
}


void spcCListVobDlg::HandleVobSelect(zCVob* vob)
{
	VobSelect(vob);
};

void spcCListVobDlg::HandleVobInsert(zCVob* vob, zCVob* parentVob)
{	
	VobInsert(vob,parentVob);
};

void spcCListVobDlg::HandleVobRemove(zCVob* vob)
{
	VobDelete(vob);
};

void spcCListVobDlg::HandleVobChange(zCVob* vob)
{
	HTREEITEM hRefresh = GetHandleByVob(vob);
	if (hRefresh!=NULL)
		ctrl_browse.SetItemText(hRefresh,GetVobItemName(vob).GetBuffer(0));
}

void spcCListVobDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CDialog::OnLButtonDblClk(nFlags, point);
}
