// spccvobcontainer.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zcore.h"
#include "zvob.h"
#include "zoption.h"
#include "zarchiver.h"

#include "spacer.h"
#include "spacerdoc.h"
#include "spacerview.h"
#include "mainfrm.h"
#include "spccvobcontainer.h"
#include "spcCConfiguration.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCVobContainer 


spcCVobContainer::spcCVobContainer(CWnd* pParent /*=NULL*/)
	: CDialog(spcCVobContainer::IDD, pParent)
{
	winID = 0;
	//{{AFX_DATA_INIT(spcCVobContainer)
	m_bFastUpdate = FALSE;
	//}}AFX_DATA_INIT

	m_bVobCollect_All			= TRUE;
	m_bVobCollect_Lights		= FALSE;
	m_bVobCollect_zCVobs		= FALSE;
	m_bVobCollect_Waypoints		= FALSE;
	m_bVobCollect_Sounds		= FALSE;
	m_bVobCollect_Lights		= FALSE;
	m_bVobCollect_Mobs			= FALSE;
	m_bVobCollect_Items			= FALSE;
	m_bVobCollect_Npcs			= FALSE;
	m_bVobCollect_Illegal		= FALSE;
}


void spcCVobContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCVobContainer)
	DDX_Control(pDX, IDC_VC_ACTIONS, ctrl_actions);
	DDX_Control(pDX, IDC_VOBLIST, ctrl_voblist);
	DDX_Control(pDX, IDC_VC_MODUS, ctrl_modus);
	DDX_Check(pDX, IDC_FASTUPDATE, m_bFastUpdate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCVobContainer, CDialog)
	//{{AFX_MSG_MAP(spcCVobContainer)
	ON_BN_CLICKED(IDC_VC_MODUS, OnVcModus)
	ON_COMMAND(ID_VC_CUSTOM, OnVcCustom)
	ON_COMMAND(ID_VC_COLLECT, OnVcCollect)	
	ON_BN_CLICKED(IDC_VC_ACTIONS, OnVcActions)	
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_KEYDOWN()
	ON_NOTIFY(NM_DBLCLK, IDC_VOBLIST, OnDblclkVoblist)
	ON_NOTIFY(NM_CLICK, IDC_VOBLIST, OnClickVoblist)
	ON_COMMAND(ID_VOBCONTAINERACTIONS_REMOVEFROMWORLD, OnVobcontaineractionsRemovefromworld)
	ON_COMMAND(ID_VOBCONTAINERACTIONS_LOADVOBLIST, OnVobcontaineractionsLoadvoblist)
	ON_COMMAND(ID_VOBCONTAINERACTIONS_CLEARVOBLIST, OnVobcontaineractionsClearvoblist)
	ON_COMMAND(ID_VOBCONTAINERACTIONS_SAVEVOBLIST, OnVobcontaineractionsSavevoblist)
	ON_COMMAND(ID_VOBCONTAINERACTIONS_CONVERTTODETAILEDVOB, OnVobcontaineractionsConvertToDetailedVob)
	ON_COMMAND(ID_VOBCONTAINERACTIONS_CLEARSELECTED, OnVobcontaineractionsClearselected)
	ON_COMMAND(ID_VC_COLLECT10M, OnVcCollect10m)
	ON_COMMAND(ID_VC_COLLECT100M, OnVcCollect100m)
	ON_BN_CLICKED(IDC_FASTUPDATE, OnFastupdate)
	ON_COMMAND(ID_VC_COLLECT20M, OnVcCollect20m)
	ON_COMMAND(ID_VC_COLLECT30M, OnVcCollect30m)
	ON_COMMAND(ID_VC_COLLECT_ALL, OnVcCollectAll)
	ON_UPDATE_COMMAND_UI(ID_VC_VOBTYPES_ALL, OnUpdateVcVobtypesAll)
	ON_UPDATE_COMMAND_UI(ID_VC_VOBTYPES_ITEMS, OnUpdateVcVobtypesItems)
	ON_UPDATE_COMMAND_UI(ID_VC_VOBTYPES_LIGHTS, OnUpdateVcVobtypesLights)
	ON_UPDATE_COMMAND_UI(ID_VC_VOBTYPES_MOBS, OnUpdateVcVobtypesMobs)
	ON_UPDATE_COMMAND_UI(ID_VC_VOBTYPES_NPCS, OnUpdateVcVobtypesNpcs)
	ON_UPDATE_COMMAND_UI(ID_VC_VOBTYPES_SOUNDS, OnUpdateVcVobtypesSounds)
	ON_UPDATE_COMMAND_UI(ID_VC_VOBTYPES_VOBS, OnUpdateVcVobtypesVobs)
	ON_UPDATE_COMMAND_UI(ID_VC_VOBTYPES_WAYPOINTS, OnUpdateVcVobtypesWaypoints)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCVobContainer 



void spcCVobContainer::OnDblclkVoblist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = ctrl_voblist.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = ctrl_voblist.GetNextSelectedItem(pos);		
		zCVob* vob = (zCVob*)ctrl_voblist.GetItemData(index);
		if (vob)
		{
			zERR_MESSAGE(4,0,"B: SPC: Jumping to vob "+vob->GetClassDef()->GetClassName_()+":"+vob->GetVobName());
			CSpacerView::view->VobGoto(vob);
		}
	};
}

void spcCVobContainer::OnClickVoblist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = ctrl_voblist.GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = ctrl_voblist.GetNextSelectedItem(pos);		
		zCVob* vob = (zCVob*)ctrl_voblist.GetItemData(index);
		if (vob)
		{
			zERR_MESSAGE(4,0,"B: SPC: Selecting vob "+vob->GetClassDef()->GetClassName_()+":"+vob->GetVobName());
			CSpacerView::view->VobSelect(vob);
		}
	};
}


int spcCVobContainer::FindVob(zCVob *vob)
{
	if (!vob) return -1;

	LVFINDINFO info;	
	info.flags	= LVFI_PARAM;
	info.lParam	= (LPARAM)vob;
	
	int index=ctrl_voblist.FindItem(&info);

	return index;	
}


void spcCVobContainer::AddVob(zCVob *vob)
{
	if (!vob) return;
	if (dynamic_cast<zCVobLevelCompo*>(vob))	return;
	if (vob == CSpacerDoc::doc->camera_vob)		return;

	int index = FindVob(vob);
	if (index<0)
	{
		zSTRING str = vob->GetClassDef()->GetClassName_();
		if (!vob->GetVobName().IsEmpty())
		{
			str = str + ":\""+vob->GetVobName()+ "\"";
		}
		else if (vob->GetVisual())
		{
			str = str + ":'"+vob->GetVisual()->GetVisualName()+ "'";
		};

		CString s(str.ToChar());
		index = ctrl_voblist.InsertItem
				( 
					LVIF_TEXT|LVIF_PARAM, 
					0, 
					s, 
					0, 
					0, 
					0, 
					(LPARAM)vob
				);
		if (index>=0) vob->AddRef();
	}
}

void spcCVobContainer::ClearVoblist()
{	
	for (int i=0;i<ctrl_voblist.GetItemCount();i++)
	{
		zCVob* vob = (zCVob*)ctrl_voblist.GetItemData(i);
		zRELEASE(vob);		
	};
	ctrl_voblist.DeleteAllItems();
}

void spcCVobContainer::RemoveVob(zCVob *vob)
{		
	if (!vob) return;

	int itemIndex = FindVob(vob);
	if (itemIndex>=0) 
	{
		if (ctrl_voblist.DeleteItem(itemIndex)) zRELEASE(vob);
	}
}

void spcCVobContainer::OnVcModus() 
{
	CMenu mainmenu;
	VERIFY(mainmenu.LoadMenu(IDR_POPUPS));
	CMenu* menu = NULL;			
	menu = mainmenu.GetSubMenu(4);
	ASSERT(menu != NULL);	
	PopupUpdate(menu);	
		
//	int x=0;
//	int y=0;
	RECT rect;
	GetWindowRect(&rect);
	menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rect.left, rect.top, this);	
}

void spcCVobContainer::SetMode(spcTVcMode _mode)
{
	mode = _mode;

	switch (mode)
	{
		case VC_CUSTOM:
			ctrl_modus.SetWindowText("Custom");
			break;
		case VC_COLLECT:
			ctrl_modus.SetWindowText("Collect");
			break;
		case VC_COLLECT_10M:
			ctrl_modus.SetWindowText("Collect 10m");
			break;
		case VC_COLLECT_20M:
			ctrl_modus.SetWindowText("Collect 20m");
			break;
		case VC_COLLECT_30M:
			ctrl_modus.SetWindowText("Collect 30m");
			break;
		case VC_COLLECT_100M:
			ctrl_modus.SetWindowText("Collect 100m");
			break;
		case VC_COLLECT_ALL_VOBS:
			ctrl_modus.SetWindowText("Collect all");
			break;

	};
}

void spcCVobContainer::OnVcCustom() 
{
	SetMode(VC_CUSTOM);
}


void spcCVobContainer::OnVcCollect() 
{
	SetMode(VC_COLLECT);
}

void spcCVobContainer::OnVcCollect10m() 
{
	SetMode(VC_COLLECT_10M);
}

void spcCVobContainer::OnVcCollect100m() 
{
	SetMode(VC_COLLECT_100M);
	
}

void spcCVobContainer::OnVcCollect20m() 
{
	SetMode(VC_COLLECT_20M);
}

void spcCVobContainer::OnVcCollect30m() 
{
	SetMode(VC_COLLECT_30M);
}

void spcCVobContainer::OnVcCollectAll() 
{
	SetMode(VC_COLLECT_ALL_VOBS);
}



BOOL spcCVobContainer::OnInitDialog() 
{
	CDialog::OnInitDialog();
			
	spcCWindowResizeStyle* style;

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_voblist,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_actions,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_modus,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_LEFT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);
	
	winID = spcConfig.GetWindowID("winVobContainer");
	spcTRegWindowInfo winInfo;
	spcConfig.GetWindowPosition(winID,winInfo);
	
	MoveWindow(
		winInfo.position.pos.x,
		winInfo.position.pos.y,
		winInfo.position.size.cx,
		winInfo.position.size.cy,
		TRUE);
	
	SetMode(VC_CUSTOM);

	return TRUE;  
}


void spcCVobContainer::OnVcActions() 
{
	CMenu mainmenu;		
	VERIFY(mainmenu.LoadMenu(IDR_POPUPS));
	CMenu* menu = NULL;			
	menu = mainmenu.GetSubMenu(5);
	ASSERT(menu != NULL);		

//	int x=0;
//	int y=0;
	RECT rect;
	GetWindowRect(&rect);
	menu->TrackPopupMenu(TPM_RIGHTALIGN | TPM_LEFTBUTTON, rect.right, rect.top, this);	
}


void spcCVobContainer::OnVobcontaineractionsClearvoblist() 
{
	ClearVoblist();
}

void spcCVobContainer::OnVobcontaineractionsRemovefromworld() 
{
	if (MessageBox("Do you really wan't to remove all vobs in this container from the world?","Remove vobs",MB_YESNO)==IDYES)
	{
		for (int i=0;i<ctrl_voblist.GetItemCount();i++)
		{
			zCVob* vob = (zCVob*)ctrl_voblist.GetItemData(i);
			if (dynamic_cast<zCVobLevelCompo*>(vob)) continue;
			if (vob->GetHomeWorld()) CSpacerDoc::doc->RemoveVob(vob,FALSE); // FALSE = keine Sicherheitsabfragen
		};
		ClearVoblist();
	}
}

void spcCVobContainer::OnVobcontaineractionsLoadvoblist() 
{
	/*if (ctrl_voblist.GetItemCount()!=0) 
	{
		MessageBox("VobContainer must be empty to load list of vobs");
		return;
	};*/
	zSTRING filename = zoptions->GetDirString(DIR_DATA)+"\\voblist.zen";	
	zCArchiver* arch = zarcFactory.CreateArchiverRead(filename);		

	zCVob* vob;
	int count = arch->ReadInt("vobCount");
	zERR_MESSAGE(4,0,"B: SPC: "+zSTRING(count)+" objects in file");
	for (int i=0;i<count;i++)
	{		
		vob = dynamic_cast<zCVob*>(arch->ReadObject());
		if (vob) AddVob(vob);
	}
		
	arch->Close();

	zRELEASE(arch);
}
void spcCVobContainer::OnVobcontaineractionsSavevoblist() 
{
	zSTRING filename = zoptions->GetDirString(DIR_DATA)+"\\voblist.zen";	
	zCArchiver* arch = zarcFactory.CreateArchiverWrite(filename,zARC_MODE_BINARY, FALSE);		

	int count = ctrl_voblist.GetItemCount();

	arch->WriteInt("vobCount",count);
	for (int i=0;i<count;i++)
	{
		zCVob* vob = (zCVob*)ctrl_voblist.GetItemData(i);
		arch->WriteObject(vob);		
	};
		
	arch->Close();

	zRELEASE(arch);
}

void spcCVobContainer::OnVobcontaineractionsConvertToDetailedVob() 
{
	MessageBox("Not yet implemented");
}

void spcCVobContainer::OnSize(UINT nType, int cx, int cy) 
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

void spcCVobContainer::OnMove(int x, int y) 
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

void spcCVobContainer::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
	case DELETE:	OnVobcontaineractionsClearselected();break;
	};
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void spcCVobContainer::OnVobcontaineractionsClearselected() 
{
	LVITEM item;
	item.state = LVIF_PARAM | LVIF_STATE;

	POSITION pos = ctrl_voblist.GetFirstSelectedItemPosition();
	if (pos) do
	{
		int index = ctrl_voblist.GetNextSelectedItem(pos);		
		if (index>=0)
		{
			zCVob* vob = (zCVob*)ctrl_voblist.GetItemData(index);
			if (vob)
			{
				zERR_MESSAGE(4,0,"B: SPC: Removing vob "+vob->GetClassDef()->GetClassName_()+":"+vob->GetVobName()+" from vob-container");
				RemoveVob(vob);
			}
		}
		pos = ctrl_voblist.GetFirstSelectedItemPosition();  // [BENDLIN] Addon Patch2
	} while (pos);
} 

void spcCVobContainer::OnFastupdate() 
{	
	m_bFastUpdate = !m_bFastUpdate;
}


void spcCVobContainer::OnUpdateVcVobtypesAll(CCmdUI* pCmdUI) 
{
	m_bVobCollect_All  =  !m_bVobCollect_All;
}

void spcCVobContainer::OnUpdateVcVobtypesItems(CCmdUI* pCmdUI) 
{
	m_bVobCollect_Items =  !m_bVobCollect_Items;
}

void spcCVobContainer::OnUpdateVcVobtypesLights(CCmdUI* pCmdUI) 
{
	m_bVobCollect_Lights  =  !m_bVobCollect_Lights;
}	

void spcCVobContainer::OnUpdateVcVobtypesMobs(CCmdUI* pCmdUI) 
{
	m_bVobCollect_Mobs  =  !m_bVobCollect_Mobs;
}

void spcCVobContainer::OnUpdateVcVobtypesNpcs(CCmdUI* pCmdUI) 
{
	m_bVobCollect_Npcs =  !m_bVobCollect_Npcs;
}

void spcCVobContainer::OnUpdateVcVobtypesSounds(CCmdUI* pCmdUI) 
{
	m_bVobCollect_Sounds  =  !m_bVobCollect_Sounds;
}

void spcCVobContainer::OnUpdateVcVobtypesVobs(CCmdUI* pCmdUI) 
{
	m_bVobCollect_zCVobs =  !m_bVobCollect_zCVobs;
}

void spcCVobContainer::OnUpdateVcVobtypesWaypoints(CCmdUI* pCmdUI) 
{
	m_bVobCollect_Waypoints  =  !m_bVobCollect_Waypoints;
}


void spcCVobContainer::PopupUpdate(CMenu* menu)
{
	CMenu* popup = NULL;			
	popup = menu->GetSubMenu(9);

	ASSERT(popup);

	if (!m_bVobCollect_All)			popup->CheckMenuItem(ID_VC_VOBTYPES_ALL, MF_UNCHECKED );
	else							popup->CheckMenuItem(ID_VC_VOBTYPES_ALL, MF_CHECKED   );
									
	if (!m_bVobCollect_Items)		popup->CheckMenuItem(ID_VC_VOBTYPES_ITEMS, MF_UNCHECKED );
	else							popup->CheckMenuItem(ID_VC_VOBTYPES_ITEMS, MF_CHECKED   );
									
	if (!m_bVobCollect_Lights)		popup->CheckMenuItem(ID_VC_VOBTYPES_LIGHTS, MF_UNCHECKED );
	else							popup->CheckMenuItem(ID_VC_VOBTYPES_LIGHTS, MF_CHECKED   );
									
	if (!m_bVobCollect_Mobs)		popup->CheckMenuItem(ID_VC_VOBTYPES_MOBS, MF_UNCHECKED );
	else							popup->CheckMenuItem(ID_VC_VOBTYPES_MOBS, MF_CHECKED   );
									
	if (!m_bVobCollect_Npcs)		popup->CheckMenuItem(ID_VC_VOBTYPES_NPCS, MF_UNCHECKED );
	else							popup->CheckMenuItem(ID_VC_VOBTYPES_NPCS, MF_CHECKED   );
									
	if (!m_bVobCollect_Sounds)		popup->CheckMenuItem(ID_VC_VOBTYPES_SOUNDS, MF_UNCHECKED );
	else							popup->CheckMenuItem(ID_VC_VOBTYPES_SOUNDS, MF_CHECKED   );
									
	if (!m_bVobCollect_zCVobs)		popup->CheckMenuItem(ID_VC_VOBTYPES_VOBS, MF_UNCHECKED );
	else							popup->CheckMenuItem(ID_VC_VOBTYPES_VOBS, MF_CHECKED   );

	if (!m_bVobCollect_Waypoints)	popup->CheckMenuItem(ID_VC_VOBTYPES_WAYPOINTS, MF_UNCHECKED );
	else							popup->CheckMenuItem(ID_VC_VOBTYPES_WAYPOINTS, MF_CHECKED   );

};
