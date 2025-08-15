// spcCCSSequencers.cpp : implementation file
//


#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "MainFrm.h"
#include "SpacerView.h"
#include "SpacerDoc.h"
#include "spcCConfiguration.h"
#include "spcCCSSequencer.h"
#include "spcCObjectSheet.h"
#include "spcCInfoBar.h"
#include "spcCDiagramVP.h"
#include "spcCInputDialog.h"

#ifdef COMPILING_GOTHIC
	#include "onpc.h"
	#include "ofocus.h"
	#include "oaihuman.h"
	#include "ocsmanager.h"
#endif

// z-files
#include "zVob.h"
#include "zplayerinfo.h"

#ifdef _DEBUG 
////#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const CString CS_BUTTON_START  = "Start";
const CString CS_BUTTON_STOP   = "Stop";

const CString CS_BUTTON_NEXT   = "Next";
const CString CS_BUTTON_PAUSE  = "Pause";
const CString CS_BUTTON_RESUME = "Resume";

const zSTRING NEW_CUTSCENE_FILENAME = "NewCS.cs";

/////////////////////////////////////////////////////////////////////////////
// spcCCSSequencers dialog


spcCCSSequencer::spcCCSSequencer(CWnd* pParent /*=NULL*/)
	: CDialog(spcCCSSequencer::IDD, pParent), 
	  flatData(), roleNameList(), selected(-1), dataState(-1), workMode(workOU),
	  m_timepos(0), lastFileName(""), propmode(false), DB_RoleBuffer(0),
	  lastFirstItem(0), stepPlay(false)
{
	//{{AFX_DATA_INIT(spcCCSSequencer)
	m_seltext = _T("");
	m_syncBlock = 0;
	m_simulate = FALSE;
	m_viewport_scrollpos = 0;
	m_grid = FALSE;
	//}}AFX_DATA_INIT
	winID			= 0;
	current_context	= 0;
	viewPort		= new spcCDiagramVP;
}


void spcCCSSequencer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCCSSequencer)			
	DDX_Control(pDX, IDC_GRID, ctrl_grid);
	DDX_Control(pDX, IDC_VIEWPORT_SCROLLBAR, ctrl_viewport_scrollbar);	
	DDX_Control(pDX, IDC_ROLE_DEL, ctrl_role_del);
	DDX_Control(pDX, IDC_ROLE_ADD, ctrl_role_add);
	DDX_Control(pDX, IDC_TIME_VALUE, ctrl_time_value);
	DDX_Control(pDX, IDC_SYNCBLOCK_INS, ctrl_sync_ins);
	DDX_Control(pDX, IDC_SYNCBLOCK_DEL, ctrl_sync_del);
	DDX_Control(pDX, IDC_SYNCBLOCK_ADD, ctrl_sync_add);
	DDX_Control(pDX, IDC_SIMULATE, ctrl_simulate);
	DDX_Control(pDX, IDC_TIMESCROLL_R, ctrl_button_sync_inc);
	DDX_Control(pDX, IDC_TIMESCROLL_L, ctrl_button_sync_dec);
	DDX_Control(pDX, IDC_TIMEINC, ctrl_button_timeinc);
	DDX_Control(pDX, IDC_TIMEDEC, ctrl_button_timedec);
	DDX_Control(pDX, IDC_CS_START, ctrl_button_start);
	DDX_Control(pDX, IDC_EDIT_SYNCBLOCK, ctrl_edit_syncblock);
	DDX_Control(pDX, IDC_VIEWPORT_PLACEHOLDER, ctrl_viewport_placeholder);
	DDX_Control(pDX, IDC_TRACKTREE, ctrl_tracktree);
	DDX_Control(pDX, IDC_OUTEXT, ctrl_seltext);
	DDX_Text(pDX, IDC_OUTEXT, m_seltext);
	DDX_Text(pDX, IDC_EDIT_SYNCBLOCK, m_syncBlock);
	DDX_Check(pDX, IDC_SIMULATE, m_simulate);		
	DDX_Check(pDX, IDC_GRID, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCCSSequencer, CDialog)
	//{{AFX_MSG_MAP(spcCCSSequencer)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TRACKTREE, OnItemexpandedTracktree)
	ON_NOTIFY(NM_CLICK, IDC_TRACKTREE, OnClickTracktree)
	ON_BN_CLICKED(IDC_TIMEDEC, OnTimedec)
	ON_BN_CLICKED(IDC_TIMEINC, OnTimeinc)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_EN_CHANGE(IDC_OUTEXT, OnChangeText)
	ON_WM_RBUTTONDOWN()	
	ON_COMMAND(ID_CSOPEN, OnCsopen)
	ON_COMMAND(ID_ADDTRACK_ANI, OnAddtrackAni)
	ON_COMMAND(ID_ADDTRACKSND, OnAddtracksnd)
	ON_COMMAND(ID_ADDTRACKTURN, OnAddtrackturn)
	ON_BN_CLICKED(IDC_TIMESCROLL_L, OnTimescrollL)
	ON_BN_CLICKED(IDC_TIMESCROLL_R, OnTimescrollR)
	ON_COMMAND(ID_CSNEW, OnCSnew)
	ON_COMMAND(ID_CSSAVE_AS, OnCSsaveAs)
	ON_COMMAND(ID_ADDTRACK_00, OnAddTrack_00) // 0
	ON_COMMAND(ID_ADDTRACK_01, OnAddTrack_01) // 1
	ON_COMMAND(ID_ADDTRACK_02, OnAddTrack_02) // 2
	ON_COMMAND(ID_ADDTRACK_03, OnAddTrack_03) // 3
	ON_COMMAND(ID_ADDTRACK_04, OnAddTrack_04) // 4
	ON_COMMAND(ID_ADDTRACK_05, OnAddTrack_05) // 5
	ON_COMMAND(ID_ADDTRACK_06, OnAddTrack_06) // 6
	ON_COMMAND(ID_ADDTRACK_07, OnAddTrack_07) // 7
	ON_COMMAND(ID_ADDTRACK_08, OnAddTrack_08) // 8
	ON_COMMAND(ID_ADDTRACK_09, OnAddTrack_09) // 9
	ON_COMMAND(ID_ADDTRACK_0A, OnAddTrack_0A) // 10
	ON_COMMAND(ID_ADDTRACK_0B, OnAddTrack_0B) // 11
	ON_COMMAND(ID_ADDTRACK_0C, OnAddTrack_0C) // 12
	ON_COMMAND(ID_ADDTRACK_0D, OnAddTrack_0D) // 13
	ON_COMMAND(ID_ADDTRACK_0E, OnAddTrack_0E) // 14
	ON_COMMAND(ID_ADDTRACK_0F, OnAddTrack_0F) // 15
	ON_COMMAND(ID_ADDTRACK_10, OnAddTrack_10) // 16
	ON_COMMAND(ID_ADDTRACK_11, OnAddTrack_11) // 17
	ON_COMMAND(ID_ADDTRACK_12, OnAddTrack_12) // 18
	ON_COMMAND(ID_ADDTRACK_13, OnAddTrack_13) // 19
	ON_COMMAND(ID_ADDTRACK_14, OnAddTrack_14) // 20
	ON_COMMAND(ID_ADDTRACK_15, OnAddTrack_15) // 21
	ON_COMMAND(ID_ADDTRACK_16, OnAddTrack_16) // 22
	ON_COMMAND(ID_ADDTRACK_17, OnAddTrack_17) // 23
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_REMOVEBLOCK, OnRemoveblock)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TRACKTREE, OnEndlabeleditTracktree)
	ON_COMMAND(ID_ADDROLE, OnAddrole)
	ON_COMMAND(ID_ADDSYNCBLOCK, OnAddsyncblock)
	ON_COMMAND(ID_REMOVEROLE, OnRemoveRole)
	ON_UPDATE_COMMAND_UI(ID_ADDROLE, OnUpdateEdit)
	ON_COMMAND(ID_INSERTSYNCBLOCK, OnInsertsyncblock)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_SHOW_PROP, OnShowProp)
	ON_COMMAND(ID_ADDGENTRACK, OnAddgentrack)
	ON_COMMAND(ID_CSPROPS, OnCsprops)
	ON_COMMAND(ID_REMOVESYNC, OnRemovesync)
	ON_COMMAND(ID_ROLEPROPS, OnRoleprops)	
	ON_BN_CLICKED(IDC_CS_START, OnCsStart)	
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_SHOWWINDOW()	
	ON_COMMAND(ID_EDIT_ADDROLE_MAIN, OnEditAddroleMain)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADDROLE_MAIN, OnUpdateEditAddroleMain)
	ON_COMMAND(ID_EDIT_ADDSPECIALROLE_THEPLAYER, OnEditAddspecialroleTheplayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADDSPECIALROLE_THEPLAYER, OnUpdateEditAddspecialroleTheplayer)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_NOTIFY(TVN_KEYDOWN, IDC_TRACKTREE, OnKeydownTracktree)
	ON_UPDATE_COMMAND_UI(ID_INSERTSYNCBLOCK, OnUpdateInsertsyncblock)
	ON_UPDATE_COMMAND_UI(ID_REMOVEROLE, OnUpdateRemoverole)
	ON_UPDATE_COMMAND_UI(ID_REMOVEBLOCK, OnUpdateRemoveblock)
	ON_UPDATE_COMMAND_UI(ID_REMOVESYNC, OnUpdateRemovesync)
	ON_UPDATE_COMMAND_UI(ID_ADDSYNCBLOCK, OnUpdateAddsyncblock)
	ON_UPDATE_COMMAND_UI(ID_ADDGENTRACK, OnUpdateAddgentrack)
	ON_UPDATE_COMMAND_UI(ID_ROLEPROPS, OnUpdateRoleprops)
	ON_UPDATE_COMMAND_UI(ID_CSSAVE, OnUpdateCssave)
	ON_UPDATE_COMMAND_UI(ID_CSSAVE_AS, OnUpdateCssaveAs)
	ON_UPDATE_COMMAND_UI(ID_CSPROPS, OnUpdateCsprops)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TRACKTREE, OnSelchangedTracktree)
	ON_COMMAND(ID_CSSAVE, OnCssave)
	ON_BN_CLICKED(IDC_SYNCBLOCK_DEL, OnSyncblockDelByButton)
	ON_BN_CLICKED(IDC_SYNCBLOCK_ADD, OnSyncblockAddByButton)
	ON_BN_CLICKED(IDC_SYNCBLOCK_INS, OnSyncblockInsByButton)	
	ON_BN_CLICKED(IDC_ROLE_ADD, OnRoleAddByButton)
	ON_BN_CLICKED(IDC_ROLE_DEL, OnRoleDelByButton)				
	ON_WM_HSCROLL()
	ON_COMMAND(ID_CUTSCENES_MOVETOBEGIN, OnCutscenesMovetobegin)	
	ON_COMMAND(ID_CUTSCENES_SYNCHRONOUS, OnCutscenesSynchronous)
	ON_UPDATE_COMMAND_UI(ID_CUTSCENES_SYNCHRONOUS, OnUpdateCutscenesSynchronous)
	ON_COMMAND(ID_CUTSCENES_REMOVE, OnCutscenesRemove)
	ON_BN_CLICKED(IDC_GRID, OnGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////
// Destructor

spcCCSSequencer::~spcCCSSequencer()
{
	zCCutscene* lcs = GetCutsceneFromFlatData();
	delete viewPort;viewPort=0;
	zRELEASE(lcs);
}

/////////////////////////////////////////////////////////////////////////////
// spcCCSSequencer message handlers

void spcCCSSequencer::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	/*
	lastFirstItem = ctrl_tracktree.GetFirstVisibleItem();	
		
	int pos = ctrl_viewport_scrollbar.GetScrollPos();				
	viewPort->SetTimeOffset(pos);

	SCROLLINFO info;
	info.cbSize		= sizeof(SCROLLINFO);     
    info.fMask		= SIF_ALL;     
    info.nMin		= 0;     
    info.nMax		= viewPort->DrawData(&dc,ctrl_tracktree,flatData,0,selected); 
    info.nPage		= viewPort->GetWinWidth();
    info.nPos		= pos;
    info.nTrackPos	= pos;   	
	ctrl_viewport_scrollbar.SetScrollInfo(&info);
	*/
	DrawIt();
}

////////////////////////////////////////////////////////////////////////////
// spcCCSSequencer methods

// private ones

void spcCCSSequencer::DrawIt()
{	
	CClientDC dc(this);
	if (flatData.GetNumInList()>2)
	{			
		SCROLLINFO info;
		ctrl_viewport_scrollbar.GetScrollInfo(&info);
		viewPort->SetTimeOffset(info.nPos);
		info.fMask		= SIF_ALL;     
		info.nMin		= 0;     
		info.nMax		= viewPort->DrawData(&dc,ctrl_tracktree,flatData,0,selected)+10; 		
		info.nPage		= viewPort->GetWinWidth()-15;
		if (info.nPage<=2) info.nPage=2;		
		ctrl_viewport_scrollbar.SetScrollInfo(&info);
		
		lastFirstItem = ctrl_tracktree.GetFirstVisibleItem();
	}
	else
	{
		viewPort->ClearData(&dc);
		ctrl_viewport_scrollbar.SetScrollRange(0,0);
	}
}

void spcCCSSequencer::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{		
	SCROLLINFO info;
	pScrollBar->GetScrollInfo(&info);
	switch (nSBCode)
	{
		case SB_LINERIGHT:		info.nPos += 5;break;
		case SB_LINELEFT:		info.nPos -= 5;break;
		case SB_PAGERIGHT:		info.nPos += info.nPage;break;
		case SB_PAGELEFT:		info.nPos -= info.nPage;break;
		default:				return;
	}
	if (info.nPos>=info.nMax)	info.nPos = info.nMax - info.nPage;
	if (info.nPos<info.nMin)	info.nPos = info.nMin;

	info.nTrackPos = 0;
	pScrollBar->SetScrollInfo(&info);

	DrawIt();	
}

void spcCCSSequencer::ViewRefresh()
{
	if (selected>=0)
	{
		zCCSAtomicBlock* bl = dynamic_cast<zCCSAtomicBlock*>(flatData[selected]);
		if (bl && selectedSubType!=bl->GetCommand()->GetSubType())
		{
			BuildData(GetCutsceneFromFlatData());
		}
	}
	
	int remember = selected;
	selected=-1;
	DrawIt();
	selected=remember;
	DrawIt();
}


void spcCCSSequencer::ViewDrawIfNessesary()
{
	if (ctrl_tracktree.GetFirstVisibleItem()!=lastFirstItem)
	{
		DrawIt();
		lastFirstItem = ctrl_tracktree.GetFirstVisibleItem();
	}
}
zCCutscene* spcCCSSequencer::GetCutsceneFromFlatData()
{
	if (flatData.GetNumInList()>0) return dynamic_cast<zCCutscene*>(flatData[0]);
	else return NULL;
}


void spcCCSSequencer::FlatnCutscene(zCCutscene* cs)
{	
	HTREEITEM parent = TVI_ROOT;
	HTREEITEM thisITEM;
	if (cs->GetChild(0))
	{
		thisITEM = ctrl_tracktree.InsertItem("Block",parent);
	} 
	else 
	{
		zCEventMessage* msg = cs->GetCommand();
		thisITEM = ctrl_tracktree.InsertItem(msg->MD_GetSubTypeString(msg->GetSubType()).ToChar(),parent);
	}
	ctrl_tracktree.SetItemData(	thisITEM,flatData.GetNumInList());
	flatData.Insert(cs);
	int z=0;
	zCCSBlockBase* lBl = cs->GetChild(z);
	while (lBl) 
	{		
		FlatnBlock(lBl, thisITEM);
		z++;
		lBl = cs->GetChild(z);
	}	
}

void spcCCSSequencer::FlatnBlock(zCCSBlockBase* bl, HTREEITEM parent)
{	
	HTREEITEM thisITEM;
	if (bl->GetChild(0))
	{
		zSTRING BLName = bl->GetRoleName();
		if ( BLName.IsEmpty() )
			thisITEM = ctrl_tracktree.InsertItem("Block",parent);
		else 
			thisITEM = ctrl_tracktree.InsertItem(BLName.ToChar(),parent);
	} else {
		zCEventMessage* msg = bl->GetCommand();
		thisITEM = ctrl_tracktree.InsertItem(
			msg->MD_GetSubTypeString(msg->GetSubType()).ToChar(),
			parent);
	}
	ctrl_tracktree.SetItemData(	thisITEM,flatData.GetNumInList());
	flatData.Insert(bl);
	int z=0;
	zCCSBlockBase* lBl = bl->GetChild(z);
	while (lBl) 
	{		
		FlatnBlock(lBl, thisITEM);
		z++;
		lBl = bl->GetChild(z);
	}
}

void spcCCSSequencer::BuildData(zCCutscene* cs)
{
	if (!cs) return;	
	
	flatData.EmptyList();	
	
	int pos = ctrl_tracktree.GetScrollPos(SB_VERT);
	ctrl_tracktree.ShowWindow(SW_HIDE);	
	ctrl_tracktree.DeleteAllItems();	

	if (workMode==workCS) 
	{
		flatData.Insert(cs);  // zur referenz
		createTrack_Roles();
		createTrackBlockRef(m_timepos);
		m_syncBlock = m_timepos;
	}
	else 
	{
		flatData.Insert(cs);
		FlatnCutscene(cs);
	}
			
	HTREEITEM ITEM = ctrl_tracktree.GetFirstVisibleItem();
	while (ITEM != 0)
	{
		ctrl_tracktree.Expand(ITEM,TVE_EXPAND);
		ITEM = ctrl_tracktree.GetNextSiblingItem(ITEM);
	}	
	ctrl_tracktree.ShowWindow	(SW_SHOW);			
	ctrl_tracktree.SetScrollPos	(SB_VERT,pos);	

	SetFocus();

	selected = -1;
	DrawIt();

	UpdateWindow();	
	//RedrawWindow();	
}

void spcCCSSequencer::BuildAfterBlockCorrection()
{
	zCCutscene* cs = GetCutsceneFromFlatData();
	if (!cs) return;
	flatData.EmptyList();

	if (workMode==workCS) 
	{
		flatData.Insert(cs);
		createTrackBlockRef(m_timepos);
		m_syncBlock = m_timepos;
	} 
	else 
	{
		flatData.Insert(cs);
		FlatnCutscene(cs);
	}
}



void spcCCSSequencer::HandleObjChange(zCObject* obj)
{
	if (dynamic_cast<zCCSAtomicBlock*>(obj)) ViewRefresh();
};


int spcCCSSequencer::FindFocus(int n)
{
	if (flatData.GetNumInList()<=n) return 0;
	int z=n;
	while (z>0 && flatData[z-1]->GetChild(0)==0) z--;
	return z;
}


// Deise Methode baut den TrackTree auf
// Zugriff auf 
// ++ ctrl_tracktree, der gefüllt wird 
// ++ flatData[0], in dem ein Zeiger auf die Cutscene erwartet wird
// ++ workMode muß workCS sein

void spcCCSSequencer::createTrack_Roles	()
{
	if (workMode!=workCS || flatData.GetNumInList()==0) return;
	
	roleNameList.EmptyList();
	zCCutscene* lcs = dynamic_cast<zCCutscene*>(GetCutsceneFromFlatData());//(zCCutscene*)flatData[0];
	if (lcs==0) return;
	for (int i=0; i<lcs->GetNumOfRoles(); i++)
	{
		roleNameList.Insert(CString(lcs->GetRoleName(i).ToChar()));
	}
	
	HTREEITEM roleITEM;
	for (int rz=0; rz<roleNameList.GetNumInList(); rz++)
	{
		roleITEM = ctrl_tracktree.InsertItem(roleNameList[rz],TVI_ROOT);		
		// erzeuge Tracks
		createTrack_AICom(roleITEM,rz);
	}
}

void spcCCSSequencer::createTrack_AICom	(HTREEITEM roleITEM, int roleNumber)
{
	int i=0;
	zCCSBlockBase* sBl = 0;
	if (GetCutsceneFromFlatData()) sBl = GetCutsceneFromFlatData()->GetChild(i);
	while (sBl)
	{
		// ITEMDATAS loeschen
		HTREEITEM childITEM = ctrl_tracktree.GetChildItem(roleITEM);
		while (childITEM!=NULL)
		{
			ctrl_tracktree.SetItemData(childITEM,0);
			childITEM = ctrl_tracktree.GetNextSiblingItem(childITEM);
		}

		int numChilds = sBl->GetNumOfChilds();
		zCCSBlockBase* chBl = 0;
		for (int z=0; z<numChilds; z++)
		{
			// lBl-Childs durchgehen
			chBl = sBl->GetChild(z);
			if (sBl->GetRoleNumOfChild(z)==roleNumber)
			{
			// * suche in tracktree das ITEM, das passt, und nicht ausgeXt ist
				CString aiName;
				zCEventMessage* msg = chBl->GetCommand();
				if (msg)
					aiName = msg->MD_GetSubTypeString(msg->GetSubType()).ToChar();		
				else
					aiName = "UNKNOWN";

				childITEM = ctrl_tracktree.GetChildItem(roleITEM);
				bool found = false;
				while (	childITEM!=NULL && !found) 
				{
					if (ctrl_tracktree.GetItemText(childITEM)==aiName &&
						ctrl_tracktree.GetItemData(childITEM)==0) found =true;
					else
						childITEM = ctrl_tracktree.GetNextSiblingItem(childITEM);
				}
			// * - nicht	: neues Item erzeugen und ausXen
				if (!found) 
					childITEM= ctrl_tracktree.InsertItem(aiName,roleITEM);
			// * - gefunden : ausXen
				ctrl_tracktree.SetItemData(childITEM,1);
			}
		}
		i++;
		sBl = flatData[0]->GetChild(i);
	}
}


// der Tracktree ist mit rollen ind AI_commands gefüllt,
// flatData enthält nur den ersten Eintrag
void spcCCSSequencer::createTrackBlockRef(int num)
{
	if (	workMode!=workCS || 
			flatData.GetNumInList()==0) return;

	zCCSBlockBase* sBl = flatData[0]->GetChild(num);
	if (sBl==0) return;
	flatData.Insert(sBl);
		
	// alle TrackItems demarkieren
	HTREEITEM roleITEM = ctrl_tracktree.GetChildItem(TVI_ROOT);//GetFirstVisibleItem();

	while (roleITEM !=0) 
	{			
		HTREEITEM childITEM = ctrl_tracktree.GetChildItem(roleITEM);
		while (childITEM!=NULL)
		{
			ctrl_tracktree.SetItemData(childITEM,-1);
			childITEM = ctrl_tracktree.GetNextSiblingItem(childITEM);
		}
		roleITEM = ctrl_tracktree.GetNextSiblingItem(roleITEM);
	}
	
	// alle Childs durchgehen und den RollenItems zuordnen
	int ch = 0;
	zCCSBlockBase* chBl = sBl->GetChild(ch);
	while (chBl)
	{
	// * suche in tracktree das ITEM, das passt, und nicht ausgeXt ist
		CString aiName;
		zCEventMessage* msg = chBl->GetCommand();
		if (msg)
			aiName = msg->MD_GetSubTypeString(msg->GetSubType()).ToChar();
		
		else
			aiName = "UNKNOWN";

		roleITEM = ctrl_tracktree.GetChildItem(TVI_ROOT);
		int rNum = sBl->GetRoleNumOfChild(ch);
		int rc=0;
		while (rc!=rNum) 
		{ roleITEM = ctrl_tracktree.GetNextSiblingItem(roleITEM); rc++; }
		
		HTREEITEM childITEM = ctrl_tracktree.GetChildItem(roleITEM);
		bool found = false;
		while (	childITEM!=NULL && !found) {
			if (ctrl_tracktree.GetItemText(childITEM)==aiName &&
				ctrl_tracktree.GetItemData(childITEM)==-1) found =true;
			else
				childITEM = ctrl_tracktree.GetNextSiblingItem(childITEM);
		}
		if (found){
			// gefunden, flatdata erzeugen 
			flatData.Insert(chBl);
			//und itemdata setzen
			ctrl_tracktree.SetItemData(childITEM,flatData.GetNumInList()-1);
		}
				
		ch++;
		chBl = sBl->GetChild(ch);
	}	
}

void spcCCSSequencer::BuildMenu()
{		
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	zCCSManager* csmanager	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();		
	if (!csmanager) return;

	CMenu* menubar = GetMenu();
	ASSERT(menubar != NULL);
	CMenu* menu = menubar->GetSubMenu(1);
	ASSERT(menu != NULL);
		
	CMenu* aimenu = menu->GetSubMenu(0);
	ASSERT(aimenu != NULL);
	
	if (aimenu->GetMenuItemCount()==1)
	{
		aimenu->RemoveMenu(0,MF_BYPOSITION);

		// neu füllen
		int messageCounter =0;
		for (int z=0; z<csmanager->GetNumOfShortCom(); z++)
		{
			if (csmanager->GetShortCom(z) != zMENU_SEPARATOR)
			{
				aimenu->AppendMenu(MF_STRING,ID_ADDTRACK_00+messageCounter,csmanager->GetShortCom(z).ToChar());
			}
			else
			{
				aimenu->AppendMenu(MF_SEPARATOR,0);
			};
			message_mapper[messageCounter]=z;
			messageCounter++;
		}	
	}
}

// public ones

void spcCCSSequencer::AssignCutscene(zCCutscene* cs)
{	
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	//zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	//if (!csplayer) { zerr.Report(zERR_WARN,9000,zSTRING("A: (DiagramView: no player availeble!")); return; };

	flatData.EmptyList();
	roleNameList.EmptyList();
	FlatnCutscene(cs);
	ChangeDataState(0); // data valid and not changed
	
	selected = -1;
	DrawIt();

	BuildMenu();
}

void spcCCSSequencer::AssignOutputUnit	(zCCutscene* cs)
{
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	//zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	//if (!csplayer) { zerr.Warning("A: (DiagramView: no player availeble!"); return; };

	OnCssave();
	ChangeDataState(0); // data valid and not changed	
	workMode = workOU;
	
	BuildData(cs);	
	DrawIt();

	BuildMenu();
}

int spcCCSSequencer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	//blockEdit.Create(IDD_INFO_DYNDLG,this);
	
	return 0;
}

void spcCCSSequencer::OnOK()
{}

void spcCCSSequencer::OnClose() 
{
	OnCssave();

	CMainFrame::mainframe->DeactivateCS();	
	//CDialog::OnClose(); not cause of non-modal
}

void spcCCSSequencer::OnItemexpandedTracktree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (ctrl_tracktree.IsWindowVisible()) 
	{
		// NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
		DrawIt();
	}
	
	*pResult = 0;
}

void spcCCSSequencer::OnClickTracktree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	selected = -1;
	DrawIt();
	
	*pResult = 0;
}

void spcCCSSequencer::OnTimedec() 
{
	if (viewPort->GetTimeScale()>1)
	{
		viewPort->DecTimeScale();
		CString s;s.Format("%i",viewPort->GetTimeScale());
		ctrl_time_value.SetWindowText(s);
		DrawIt();
	}
}

void spcCCSSequencer::OnTimeinc() 
{
	if (viewPort->GetTimeScale()<20)
	{
		viewPort->IncTimeScale();
		CString s;s.Format("%i",viewPort->GetTimeScale());
		ctrl_time_value.SetWindowText(s);
		DrawIt();
	}
}

void spcCCSSequencer::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int newSelected = viewPort->PickData(point,ctrl_tracktree,flatData,0);
//	if (newSelected!=selected) 
		selected = newSelected;
//	else selected = -1;

	if (selected>=0)
	{
		// ctrl_tracktree.SelectItem(NULL);
		m_seltext = flatData[selected]->GetInfo().ToChar();
		zCCSAtomicBlock* bl = dynamic_cast<zCCSAtomicBlock*>(flatData[selected]);
		if (bl)
		{
			// CMainFrame::mainframe->ObjectSelection(bl->GetCommand(),FALSE);
			CMainFrame::mainframe->ObjectSelection(bl,FALSE);
			selectedSubType = bl->GetCommand()->GetSubType();
		}
		DrawIt();
	} 
	else m_seltext = "";
	UpdateData(false);
	CDialog::OnLButtonDown(nFlags, point);

	SetFocus();
}


void spcCCSSequencer::OnLButtonUp(UINT nFlags, CPoint point) 
{	
	CClientDC dc(this); // device context for painting
	if (viewPort->IsInMovement(point))
	{
		int delta = viewPort->EndBlockMovement(&dc,point);
		int focus = FindFocus(selected);
		int parent = focus-1;
		if (focus>0)
		{
			// Soviel sekunden wurde der Block verschoben:
			double sec				= double(delta) * viewPort->GetPixelTimeValue();
			zCCSBlockPosition* bp	= flatData[parent]->GetChildPos(selected-parent-1);

			assert(bp->block==flatData[selected]);

			if (flatData[focus]->GetMinTime()!=0)
					bp->position += (float)(sec/flatData[focus]->GetMinTime());
			else 
					bp->position += (float)sec;
			
			if (bp->position<0) bp->position=0;
			
			/*
			if (m_grid)
			{
				bp->position+=0;
			};
			*/

			if (sec!=0) ChangeDataState(1);

			flatData[parent]->BlockCorrection();			
			BlockPositionCheck(flatData[parent],false);
			
			ChangeDataState				(1); // data valid and changed
			BuildAfterBlockCorrection	();
			DrawIt						();
		}
	}
	else
		if (selected<0)
		{
			m_seltext = "";
			DrawIt();
			UpdateData(false);
		}

	CDialog::OnLButtonUp(nFlags, point);
}

void spcCCSSequencer::OnMouseMove(UINT nFlags, CPoint point) 
{
	static int xPos=-1;

	int xoff,yoff;
	viewPort->GetWinOffset(xoff,yoff);xoff=point.x;	

	CClientDC dc(this); // device context for painting

	if (xPos>=0)
	{				
		CRect rect(xPos-1, yoff, xPos+1, yoff+10);
		dc.InvertRect(&rect);		
	};
	xPos = xoff;
	CRect rect(xoff-1, yoff, xoff+1, yoff+10);
	dc.InvertRect(&rect);		
	
	if ((nFlags & MK_LBUTTON)==MK_LBUTTON)
	{						
		if (!viewPort->IsInMovement(point)) 
		{
			CPoint lastPoint = viewPort->GetLastPick();
			CRect rect(lastPoint.x-4,lastPoint.y-4,lastPoint.x+4,lastPoint.y+4); // Toleranzbereich
			if (!rect.PtInRect(point))
			{
				viewPort->BeginBlockMovement(&dc,point);
				viewPort->BlockMove(&dc,point);
			}
		} 
		else	
		{			
			viewPort->BlockMove(&dc,point);			
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

void spcCCSSequencer::OnRButtonDown(UINT nFlags, CPoint point) 
{			
	int newSelected = viewPort->PickData(point,ctrl_tracktree,flatData,0);
	selected = newSelected;
	
	if (selected>=0)
	{
		m_seltext = flatData[selected]->GetInfo().ToChar();
		zCCSAtomicBlock* bl = dynamic_cast<zCCSAtomicBlock*>(flatData[selected]);
		if (bl)
		{
			CMainFrame::mainframe->ObjectSelection(bl,FALSE);
			selectedSubType = bl->GetCommand()->GetSubType();
		}
		DrawIt();
	} 
	else m_seltext = "";
	UpdateData(false);	

	SetFocus();

	CDialog::OnRButtonDown(nFlags, point);

	if (selected>=0)
	{
		CMenu mainmenu;		
		VERIFY(mainmenu.LoadMenu(IDR_POPUPS));
		CMenu* menu = NULL;			
		menu = mainmenu.GetSubMenu(3);
		ASSERT(menu != NULL);		
		
		//int x=0;
		//int y=0;
		RECT rect;
		GetWindowRect(&rect);
		menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rect.left+point.x+10, rect.top+point.y, this);
	}
}

void spcCCSSequencer::OnChangeText() 
{	
	if (selected<0) return;
	UpdateData(true);
	flatData[selected]->SetInfo(zSTRING(m_seltext.GetBuffer(0)));
	// ChangeDataState(1);
	DrawIt();
}

void spcCCSSequencer::AssignParameter(zSTRING & p)
{
	if (selected<0) return;
	m_seltext = p.ToChar();
	flatData[selected]->SetInfo(p);
	ChangeDataState(1);
	DrawIt();
	UpdateData(false);
}

zCVob* spcCCSSequencer::RegetIntegratedRole()
{			
	zCCutscene* cs = dynamic_cast<zCCutscene*>(GetCutsceneFromFlatData());
	if (!cs) return 0;
	
	HTREEITEM hitem = ctrl_tracktree.GetSelectedItem();
	if (!hitem) return 0;

	CString itemtext = ctrl_tracktree.GetItemText(hitem);
	zSTRING zitemtext(itemtext.GetBuffer(0));

	for (int i=0;i<cs->roleList.GetNumInList();i++)
	{
		if (cs->roleList[i] == zitemtext)
		{
			zCVob* rolevob = dynamic_cast<zCVob*>(cs->roleList[i]->GetRoleVob());
			if (!rolevob) return 0;	
			zCVob* vob = dynamic_cast<zCVob*>(rolevob->CreateCopy());				
			return vob;
		};
	}
	return 0;	
};

bool spcCCSSequencer::AssignIntegratedRole(zCVob* irole)
{	
	if (!irole) return false;
	if (flatData.GetNumInList==0) return false;

	zCCutscene* lcs = static_cast<zCCutscene*>(GetCutsceneFromFlatData());
	if (!lcs) return false;

	if (irole->GetVobName().IsEmpty()) 
	{
		MessageBox("Vob has no name.\r\nPlease set the property 'vobName'!","No VobName",MB_ICONASTERISK | MB_OK);
		return false;
	};

	zCVob * cscopy = dynamic_cast<zCVob*>(irole->CreateCopy());		
	if (cscopy==0) return false;
	zSTRING newRoleName = cscopy->GetVobName();
	
	bool found = false;
	int z=0;
	while (z<lcs->roleList.GetNumInList() && !found)
	{
		// found = found || (lcs->roleList[z]->GetRoleVob() && (lcs->roleList[z]->GetRoleVob()->GetVobName()==newRoleName));
		found = found || (lcs->roleList[z]==newRoleName);
		if (!found) z++;		
	}
	if (z==lcs->roleList.GetNumInList()) 
	{	
		lcs->roleList.Insert(new zCCSRole(newRoleName));
	}
	else 
	{
		if (AfxMessageBox("Replace existing role?",MB_YESNO)!=IDYES)
		{
			zRELEASE(cscopy);
			return false;			
		}
		else 
		{
			zCVob* vob = lcs->roleList[z]->GetRoleVob();
			zRELEASE(vob);
		}
	}
	lcs->roleList[z]->SetRoleVob(cscopy); // the copy gets member of the role
	
	ChangeDataState(1);
	BuildData(GetCutsceneFromFlatData());
	DrawIt();
	
	HTREEITEM item = FindTreeItem(lcs->roleList[z]);
	if (item) ctrl_tracktree.SelectItem(item);

	UpdateData(false);
	
	return true;
}

void spcCCSSequencer::ChangeDataState(int newState)
{
	dataState = newState;
	// modify menu
	CMenu* menubar = GetMenu();
	if (!menubar) return;

	//CMenu* menu = menubar->GetSubMenu(0);
	//ASSERT(menu != NULL);
	if (dataState==1) 
	{
		selected=-1;
//		menu->EnableMenuItem(ID_CSSAVE, MF_BYCOMMAND | MF_ENABLED);
//		menu->EnableMenuItem(ID_CSSAVE_AS, MF_BYCOMMAND | MF_ENABLED);
	}
	else
	{
//		menu->EnableMenuItem(ID_CSSAVE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
//		menu->EnableMenuItem(ID_CSSAVE_AS, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}
}
void spcCCSSequencer::OnAddgentrack() 
{
	if (dataState == -1) return;

	if (workMode==workCS)
	{
		HTREEITEM rItem = ctrl_tracktree.GetSelectedItem();
		if (rItem==0) return;

		CString rName = ctrl_tracktree.GetItemText(rItem);
		int z=0;
		while (	z<roleNameList.GetNumInList() && roleNameList[z]!=rName) z++;

		// zCEventMessage* msg = blockEdit.Insert();
		zCObject* obj = CMainFrame::mainframe->GetObjectWindow()->CreateNewObject();
		zCEventMessage* msg = dynamic_cast<zCEventMessage*>(obj);

		if (flatData[1] && msg)
		{
			zCCSAtomicBlock* aBl = new zCCSAtomicBlock();
			aBl->SetCommand(msg);
			if (z<roleNameList.GetNumInList())
				flatData[1]->InsertBlock(aBl,z);
		}
		else return;
	}
		
	ChangeDataState(1); // data valid and changed
	BuildData(GetCutsceneFromFlatData());
}
void spcCCSSequencer::AddTrack(int nr) 
{
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	//zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	zCCSManager* csmanager	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();		
	//if (!csplayer)	return;	
	if (!csmanager) return;

	if (dataState == -1) return;

	if (workMode==workOU)
	{
		// TODO: insert new block
		return;
	}
	else 
	{
		HTREEITEM rItem = ctrl_tracktree.GetSelectedItem();
		if (rItem==0) return;

		if (flatData.GetNumInList()<=1) 
		{
			zERR_FAULT("B: CS: flatData has missing elements (SynBlock-Error?)");
			return;
		};

		CString rName = ctrl_tracktree.GetItemText(rItem);
		int z=0;
		while (	z<roleNameList.GetNumInList() && roleNameList[z]!=rName) z++;

		if (flatData[1])
		{		
			if (z<roleNameList.GetNumInList())
			{
				zCCSAtomicBlock* aBl = new zCCSAtomicBlock();
				aBl->SetCommand(csmanager->CreateMessage(nr));
				flatData[1]->InsertBlock(aBl,z);
			}
		}
		else return;
	}
		
	ChangeDataState(1); // data valid and changed
	BuildData(GetCutsceneFromFlatData());
}

void spcCCSSequencer::OnCsopen() 
{
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	//zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	//if (!csplayer) return;

	zoptions->ChangeDir(DIR_CUTSCENES);

	if (lastFileName.IsEmpty()) lastFileName = CString(zoptions->GetDirString(DIR_CUTSCENES).ToChar());
	zFILE* file = zfactory->CreateZFile(lastFileName.GetBuffer(0));	
	file = zfactory->CreateZFile(lastFileName.GetBuffer(0));			
	CString fileName = file->GetFilename().ToChar();	
			
	zFILE::DirectFileAccess(true);
		CString filter = "Cutscene (*.cs)|*.cs|All Files(*.*)|*.*||";
		CFileDialog dlg(TRUE,"cs",fileName,OFN_HIDEREADONLY | OFN_ENABLESIZING | OFN_OVERWRITEPROMPT,filter);			
		zSTRING s = file->GetFullPath();
		dlg.m_ofn.lpstrInitialDir = s.ToChar();
		int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{				
		csName = dlg.GetPathName().GetBuffer(0);		

		m_timepos = 0;	
		UpdateData(false);
		OnChangeTimePos();

		zCCutscene* cs = GetCutsceneFromFlatData();
		zRELEASE(cs);

		zoptions->ChangeDir(DIR_CUTSCENES);

		zCCutscene* lcs=0;
		
		delete file;file = zfactory->CreateZFile(csName);
		csName = file->GetPath();
		lastFileName = csName.ToChar();

		// load
		if (file->Exists(csName))
		{
			if (file->Open(csName)==zERR_NONE)
			{					
				zCArchiver* arch = zarcFactory.CreateArchiverRead(file);				
				if (arch)
				{
					lcs = static_cast<zCCutscene*>(arch->ReadObject());
					arch->Close();
					zRELEASE(arch);
				
					// if (lcs) lcs->SetOwnerPlayer(csplayer);

					file->Close();

					BlockPositionCheck(lcs,true);

					ChangeDataState	(0);
					roleNameList	.EmptyList();
					workMode		= workCS;
					BuildData		(lcs);
					
					cs = GetCutsceneFromFlatData();
					if (cs) lcs->AddRef();
					BuildMenu();
					SetWindowText(csName.ToChar());

					CMainFrame::mainframe->ObjectSelection(lcs->properties,FALSE);				

					SetFocus();
					selected=-1;
					DrawIt();
				}
			}
		}		
	}	

	delete file;file=0;		
}

void spcCCSSequencer::OnAddtrackAni() 
{
	AddTrack(3);
}

void spcCCSSequencer::OnAddtracksnd() 
{
	AddTrack(2);	
}

void spcCCSSequencer::OnAddtrackturn() 
{
	AddTrack(7);
}

void spcCCSSequencer::OnChangeTimePos() 
{
	UpdateData(true);
//	BuildData(GetCutsceneFromFlatData());
	if (workMode==workCS) {
		zCCSBlockBase* cs = flatData[0];
		flatData.EmptyList();
		flatData.Insert(cs);  // zur referenz
		createTrackBlockRef(m_timepos);
		m_syncBlock = m_timepos;
	}
	selected = -1;
	m_seltext = "";
	UpdateData(false);
	DrawIt();
}

void spcCCSSequencer::OnTimescrollL() 
{
	if (m_timepos>0 && workMode==workCS)
	{ m_timepos--; OnChangeTimePos(); };
}

void spcCCSSequencer::OnTimescrollR() 
{
	if (flatData.GetNumInList()==0) return;
	if (m_timepos<GetCutsceneFromFlatData()->GetNumOfChilds()-1 && workMode==workCS)
	{ m_timepos++; OnChangeTimePos(); };
}

void spcCCSSequencer::OnCSnew() 
{
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	zCCSManager*  csmanager = CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();
	if (!csmanager) return;

	m_timepos = 0;	
	UpdateData(false);
	OnChangeTimePos();

	zCCutscene* lcs = new zCCutscene();		
	// lcs->SetOwnerPlayer(csplayer);
	lcs->NewCS(csmanager);

	ChangeDataState(1); // data valid and changed	
	csName = NEW_CUTSCENE_FILENAME;
	lastFileName = csName.ToChar();

	roleNameList.EmptyList();
	workMode = workCS;

	BuildData(lcs);  // pointer control switches to flatData
	DrawIt();

	BuildMenu();

	SetWindowText(csName.ToChar());	

	CMainFrame::mainframe->ObjectSelection(lcs->properties,FALSE);	
}

void spcCCSSequencer::OnCSsaveAs() 
{
	zoptions->ChangeDir(DIR_CUTSCENES);
	
	if (lastFileName.IsEmpty()) lastFileName = CString(zoptions->GetDirString(DIR_CUTSCENES).ToChar());
	zFILE* file = zfactory->CreateZFile(lastFileName.GetBuffer(0));	
	file = zfactory->CreateZFile(lastFileName.GetBuffer(0));			
	CString fileName = file->GetFilename().ToChar();
	
	zFILE::DirectFileAccess(true);
		CString filter = "|Cutscene(*.cs)|*.cs||";		
		CFileDialog dlg(false,"cs",fileName,OFN_HIDEREADONLY | OFN_ENABLESIZING | OFN_OVERWRITEPROMPT,filter);	
		zSTRING s = file->GetFullPath();
		dlg.m_ofn.lpstrInitialDir = s.ToChar();
		int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)	
	{
		csName = dlg.GetPathName().GetBuffer(0);				

		zoptions->ChangeDir(DIR_CUTSCENES);
	
		delete file;file = zfactory->CreateZFile(csName);

		csName			= file->GetPath();							
		lastFileName	= csName.ToChar();

		if (file->Create(csName)==zERR_NONE)
		{									
			zCArchiver* arch = zarcFactory.CreateArchiverWrite(file,zARC_MODE_ASCII);			
			arch->WriteObject	(flatData[0]);
			arch->Close			();			
			zRELEASE(arch);

			file->Close			();												

			ChangeDataState(0); // data valid and not changed		
			SetWindowText(lastFileName);
		}					
	} 
	
	delete file;file=0;
}

void spcCCSSequencer::OnAddTrack_00(){ AddTrack(message_mapper[0]); }
void spcCCSSequencer::OnAddTrack_01(){ AddTrack(message_mapper[1]); }
void spcCCSSequencer::OnAddTrack_02(){ AddTrack(message_mapper[2]); }
void spcCCSSequencer::OnAddTrack_03(){ AddTrack(message_mapper[3]); }
void spcCCSSequencer::OnAddTrack_04(){ AddTrack(message_mapper[4]); }
void spcCCSSequencer::OnAddTrack_05(){ AddTrack(message_mapper[5]); }
void spcCCSSequencer::OnAddTrack_06(){ AddTrack(message_mapper[6]); }
void spcCCSSequencer::OnAddTrack_07(){ AddTrack(message_mapper[7]); }
void spcCCSSequencer::OnAddTrack_08(){ AddTrack(message_mapper[8]); }
void spcCCSSequencer::OnAddTrack_09(){ AddTrack(message_mapper[9]); }
void spcCCSSequencer::OnAddTrack_0A(){ AddTrack(message_mapper[10]); }
void spcCCSSequencer::OnAddTrack_0B(){ AddTrack(message_mapper[11]); }
void spcCCSSequencer::OnAddTrack_0C(){ AddTrack(message_mapper[12]); }
void spcCCSSequencer::OnAddTrack_0D(){ AddTrack(message_mapper[13]); }
void spcCCSSequencer::OnAddTrack_0E(){ AddTrack(message_mapper[14]); }
void spcCCSSequencer::OnAddTrack_0F(){ AddTrack(message_mapper[15]); }
void spcCCSSequencer::OnAddTrack_10(){ AddTrack(message_mapper[16]); }
void spcCCSSequencer::OnAddTrack_11(){ AddTrack(message_mapper[17]); }
void spcCCSSequencer::OnAddTrack_12(){ AddTrack(message_mapper[18]); }
void spcCCSSequencer::OnAddTrack_13(){ AddTrack(message_mapper[19]); }
void spcCCSSequencer::OnAddTrack_14(){ AddTrack(message_mapper[20]); }
void spcCCSSequencer::OnAddTrack_15(){ AddTrack(message_mapper[21]); }
void spcCCSSequencer::OnAddTrack_16(){ AddTrack(message_mapper[22]); }
void spcCCSSequencer::OnAddTrack_17(){ AddTrack(message_mapper[23]); }

void spcCCSSequencer::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (dataState == -1) return;

	//zCCSBlockBase* lBlock = flatData[0];  // das ist immer der erste Block;
	
/*	if (nChar==KEY_DEL && selected>=0)
	{
		int focus = findFocus(selected);
		int parent = focus-1;
		if (focus>0)
		{
			int child = selected-parent-1;
			assert(flatData[parent]->GetChild(child)==flatData[selected]);
			flatData[parent]->DeleteChild(child);
		selected = -1;
		ChangeDataState(1); // data valid and changed
		BuildData(flatData[0]);
		}
	}*/
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void spcCCSSequencer::OnRemoveblock() 
{
	if (dataState == -1) return;

	if (selected>=0)
	{
		int focus = FindFocus(selected);
		int parent = focus-1;
		if (focus>0)
		{
			int child = selected-parent-1;
			assert(flatData[parent]->GetChild(child)==flatData[selected]);
			flatData[parent]->DeleteChild(child);
			ChangeDataState(1); // data valid and changed
			BuildData(GetCutsceneFromFlatData());			
		}
	}
}

void spcCCSSequencer::OnEndlabeleditTracktree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	zCCutscene* cs = dynamic_cast<zCCutscene*>(GetCutsceneFromFlatData());
	if (!cs) return;

	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	HTREEITEM lItem = pTVDispInfo->item.hItem;

	// int flatEntry = ctrl_tracktree.GetItemData(lItem);
	CString oldRoleName(ctrl_tracktree.GetItemText(lItem));
	
	int sc=0;	
	while (	sc<roleNameList.GetNumInList() && roleNameList[sc]!=oldRoleName) sc++;

	CEdit* lEdit = ctrl_tracktree.GetEditControl();
	if (roleNameList.GetNumInList()==sc) return;
	int lc = lEdit->GetLineCount();
	if (lc>0)
	{
		TCHAR str[100];
		lEdit->GetLine(0,str,60);
		cs->roleList[sc]->assign(str);

		ctrl_tracktree.SetItemText(lItem,str);
	}	
	ChangeDataState(1); // data valid and changed
	ctrl_tracktree.DeleteAllItems();
	BuildData(cs);

	*pResult = 0;
}



void spcCCSSequencer::OnAddrole() 
{
	zCCutscene *lcs = dynamic_cast<zCCutscene*>(GetCutsceneFromFlatData());		
	if (!lcs) return;

	spcCInputDialog	dlg;
	dlg.m_text = "Rolename";
	dlg.m_edit = "NEW_ROLE";
	dlg.DoModal();

	lcs->NewRole(zSTRING(dlg.m_edit.GetBuffer(0)));
		
	ChangeDataState(1); // data valid and changed
	BuildData(GetCutsceneFromFlatData());
}

void spcCCSSequencer::OnEditAddroleMain() 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();		
	if (!lcs) return;
	lcs->NewRole(zSTRING(CS_MAIN_ROLENAME));
		
	ChangeDataState(1); // data valid and changed
	BuildData(GetCutsceneFromFlatData());	
}

void spcCCSSequencer::OnUpdateEditAddroleMain(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(FALSE);
}

void spcCCSSequencer::OnEditAddspecialroleTheplayer() 
{
	zCCutscene *lcs = dynamic_cast<zCCutscene*>(GetCutsceneFromFlatData());		
	if (!lcs) return;
	lcs->NewRole(zSTRING(CS_PLAYER_ROLENAME));
	
	ChangeDataState(1); // data valid and changed
	BuildData(GetCutsceneFromFlatData());		
}

void spcCCSSequencer::OnUpdateEditAddspecialroleTheplayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(FALSE);
}

void spcCCSSequencer::OnAddsyncblock() 
{
	if (flatData.GetNumInList()==0) return;

	zCCutscene *lcs = dynamic_cast<zCCutscene*>(GetCutsceneFromFlatData());		
	if (!lcs) return;
	lcs->NewBlock(-1, GetCutsceneFromFlatData()->GetNumOfChilds());
		
	ChangeDataState(1); // data valid and changed
	BuildData(GetCutsceneFromFlatData());

	m_timepos = GetCutsceneFromFlatData()->GetNumOfChilds()-1;
	OnChangeTimePos(); 	
	
}

void spcCCSSequencer::OnInsertsyncblock() 
{
	if (flatData.GetNumInList()==0) return;

	zCCutscene *lcs = GetCutsceneFromFlatData();
	if (!lcs) return;
	lcs->NewBlock(-1, m_timepos);
	
	ChangeDataState(1); // data valid and changed
	BuildData(GetCutsceneFromFlatData());
	
	DrawIt();
}


void spcCCSSequencer::OnRemoveRole() 
{
	if (workMode!=workCS || !GetCutsceneFromFlatData()) return;

	HTREEITEM rItem = ctrl_tracktree.GetSelectedItem();
	if (rItem==0) return;
	
	CString rName = ctrl_tracktree.GetItemText(rItem);

	int z=0;
	while (	z<roleNameList.GetNumInList() && roleNameList[z]!=rName) z++;

	if (z<roleNameList.GetNumInList())
	{
		GetCutsceneFromFlatData()->DeleteRole(z);
	
		ChangeDataState(1); // data valid and changed
		ctrl_tracktree.DeleteAllItems();
		BuildData(GetCutsceneFromFlatData());
	}

	CMainFrame::mainframe->ObjectSelection(0,FALSE);
	DrawIt();
}

void spcCCSSequencer::OnUpdateEdit(CCmdUI* pCmdUI) 
{
	BuildMenu();
}

void spcCCSSequencer::OnShowProp()
{
	/*
	WINDOWPLACEMENT wpl;	
	if (propmode)
	{
		GetWindowPlacement(&wpl);
		wpl.rcNormalPosition.bottom -= 250;
		SetWindowPlacement(&wpl);
		blockEdit.GetWindowPlacement(&wpl);
		wpl.rcNormalPosition.top -= 400;
		wpl.rcNormalPosition.bottom -= 400;
		blockEdit.SetWindowPlacement(&wpl);
		blockEdit.ShowWindow(SW_HIDE);
		ctrl_seltext.ShowWindow(SW_SHOW);
	} else {
		GetWindowPlacement(&wpl);
		wpl.rcNormalPosition.bottom += 250;
		SetWindowPlacement(&wpl);
		blockEdit.GetWindowPlacement(&wpl);
		wpl.rcNormalPosition.top += 400;
		wpl.rcNormalPosition.bottom += 400;
		blockEdit.SetWindowPlacement(&wpl);
		blockEdit.ShowWindow(SW_SHOW);
		ctrl_seltext.ShowWindow(SW_HIDE);
	}	
	propmode = !propmode;
	*/
}

void spcCCSSequencer::OnCsprops() 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();
	if (lcs)
	{
		if(!propmode) OnShowProp();
		// blockEdit.Select(lcs->properties);		
		CMainFrame::mainframe->ObjectSelection(lcs->properties,FALSE);
	}
}

void spcCCSSequencer::OnRoleprops() 
{
	if (workMode!=workCS) return;	
	zCCutscene *lcs = GetCutsceneFromFlatData();
	if (!lcs) return;	

	HTREEITEM rItem = ctrl_tracktree.GetSelectedItem();
	if (rItem==0) return;
	
	CString rName = ctrl_tracktree.GetItemText(rItem);
	if (rName.IsEmpty()) return;

	int z=0;
	while (	z<lcs->roleList.GetNumInList() && lcs->roleList[z]!=rName) z++;
	
	if (z<lcs->roleList.GetNumInList())
	{
		if(!propmode) OnShowProp();
		// blockEdit.Select((lcs->roleList[z]));
		CMainFrame::mainframe->ObjectSelection(lcs->roleList[z],FALSE);
	}
}

void spcCCSSequencer::OnRemovesync() 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();
	if (!lcs) return;
	if (lcs->GetNumOfChilds()<=1) return;
	if (m_syncBlock>=lcs->GetNumOfChilds()) return;
	
	if (AfxMessageBox("Do you really want to remove this syncblock?",MB_YESNO)==IDYES)
	{		
		// ctrl_tracktree.DeleteAllItems();
		lcs->DeleteChild(m_syncBlock);
		if (m_syncBlock>=lcs->GetNumOfChilds()) m_syncBlock = lcs->GetNumOfChilds()-1;		
		ChangeDataState(1); // data valid and changed		
		BuildData(lcs);
	}

	if (m_timepos>=lcs->GetNumOfChilds()) 
	{
		m_timepos = lcs->GetNumOfChilds()-1;
		OnChangeTimePos();
	}	

	DrawIt();	
}

void spcCCSSequencer::OnSyncblockDelByButton() 
{
	OnRemovesync();
}

void spcCCSSequencer::OnSyncblockAddByButton() 
{
	OnAddsyncblock();
}

void spcCCSSequencer::OnSyncblockInsByButton() 
{
	OnInsertsyncblock();
}



BOOL spcCCSSequencer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	spcCWindowResizeStyle* style;

	// Buttonleiste rechts 

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_button_start,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_simulate,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);
	
	// Syncblock-Counter mit Pfeiltasten links und rechts

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_button_sync_dec,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_button_sync_inc,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_edit_syncblock,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);	
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_sync_del,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_sync_add,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_sync_ins,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
		

	// Skalierung

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_button_timedec,this, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_time_value,this, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_button_timeinc,this, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_grid,this, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	// Infozeile, Listen und View

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_seltext,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_tracktree,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_viewport_placeholder,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	// Slider

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_viewport_scrollbar,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);
	ctrl_viewport_scrollbar.SetScrollRange(0,100);			

	winID = spcConfig.GetWindowID("winCutsceneSequencer");
	spcTRegWindowInfo winInfo;
	spcConfig.GetWindowPosition(winID,winInfo);
	
	MoveWindow(
		winInfo.position.pos.x,
		winInfo.position.pos.y,
		winInfo.position.size.cx,
		winInfo.position.size.cy,
		TRUE);	

	CString s;s.Format("%i",viewPort->GetTimeScale());
	ctrl_time_value.SetWindowText(s);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void spcCCSSequencer::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if (winID>0)
	{
		RECT rect;
		GetWindowRect(&rect);
		spcConfig.SetWindowPosition(winID,rect);

		bool result;
		spcCWindowResizeStyle* style;
		POSITION pos = childResizeList.GetHeadPosition();
		while (pos)
		{
			style = childResizeList.GetNext(pos);
			result = style->UpdateSize();		
			if (!result) return;
		};

		// Die Viewport-Position und -Größe updaten		
		ctrl_viewport_placeholder.GetWindowRect(&rect);
		ScreenToClient(&rect);
		viewPort->MoveWindow(&rect);

		RedrawWindow();
	}	
}

void spcCCSSequencer::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	if (winID>0)
	{
		RECT rect;
		GetWindowRect(&rect);
		spcConfig.SetWindowPosition(winID,rect);
	}
}

void spcCCSSequencer::OnShowWindow(BOOL bShow, UINT nStatus) 
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

HTREEITEM spcCCSSequencer::FindTreeItem(const zSTRING& name, HTREEITEM item)
{
	if (!item) item = ctrl_tracktree.GetRootItem();

	CString text;
	while (item)
	{
		text = ctrl_tracktree.GetItemText(item);
		if (text == name.ToChar()) return item;
		
		if (ctrl_tracktree.ItemHasChildren(item))
		{
			FindTreeItem(name,ctrl_tracktree.GetChildItem(item));
		};

		item = ctrl_tracktree.GetNextItem(item,TVGN_NEXT);
	}
	
	return 0;
};

zCVob* spcCCSSequencer::InitCutsceneBeforeRunning(zCCutscene* cs)
{
	zCVob* pickedVob		= CMainFrame::mainframe->GetInfoBar()->GetSelectedVob();
	zCWorld* world			= CMainFrame::mainframe->GetInfoBar()->GetActiveWorld();
	if (!world) return 0;

	if (!CMainFrame::mainframe->GetInfoBar()) return 0;
	zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	if (!csplayer) return 0;

	zCPlayerInfo*	activePlayer	= zCPlayerInfo::GetActivePlayer();
	zCVob*			activePlayerVob	= (activePlayer) ? activePlayerVob = activePlayer->GetPlayerVob() : 0;	

	// Rollen vorbereiten und Hauptrolle suchen

	// int mainRoleIndex=-1;

	zCVob* mainRoleVob = 0;	
	zSTRING roleName;
	zCVob* vob;
	for (int i=0; i<cs->GetNumOfRoles(); i++)
	{
		vob=0;
		roleName = cs->GetRoleName(i); 
		if (roleName==CS_PLAYER_ROLENAME)	vob = activePlayerVob;
		if (roleName==CS_MAIN_ROLENAME)		vob = pickedVob;
		if (!vob) vob = world->SearchVobByName(roleName);			
		
		if (pickedVob == vob) mainRoleVob=pickedVob;
		
		if (vob) InitRoleVob(vob);
	}	

	/*
	#ifdef COMPILING_GOTHIC
		// Rollen vorbereiten							
		if (!oCNpc::player) 
		{			
			oCNpc::player = new oCNpc();
			oCNpc::player->InitByScript(parser.GetIndex(zSTRING("PC_HERO")));	
			if (!oCNpcFocus::focus) oCNpcFocus :: InitFocusModes();
		}
		if (!oCNpc::player->GetAnictrl()) { MessageBox("Player-NSC has no AniControler!");return FALSE; }

	#endif
	*/

	return mainRoleVob;
	
}

zBOOL spcCCSSequencer::InitRoleVob(zCVob *vob)
{	
	// return TRUE;

	#ifdef COMPILING_GOTHIC		
		oCNpc* npc = dynamic_cast<oCNpc*>(vob);
		if (npc)
		{
			zERR_MESSAGE(4,0,"B: CS: InitRoleVobs "+npc->GetName(TRUE)+": Setting HumanAI");
			oCAIHuman* ai = zNEW(oCAIHuman);
			ai->Init(npc);
			npc->SetAI(ai);
			npc->SetAICallback(ai);
			npc->ResetToHumanAI();
		}
	#endif
		return TRUE;
}


zCVob* spcCCSSequencer::DeinitCutsceneAfterRunning(zCCutscene* cs)
{	
	zCWorld* world			= CMainFrame::mainframe->GetInfoBar()->GetActiveWorld();
	if (!world) return 0;

	if (!CMainFrame::mainframe->GetInfoBar()) return 0;
	zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	if (!csplayer) return 0;

	zCPlayerInfo*	activePlayer	= zCPlayerInfo::GetActivePlayer();
	zCVob*			activePlayerVob	= (activePlayer) ? activePlayerVob = activePlayer->GetPlayerVob() : 0;	

	// Rollen vorbereiten und Hauptrolle suchen

	// int mainRoleIndex=-1;

	zCVob* mainRoleVob = 0;	
	zSTRING roleName;
	zCVob* vob;
	for (int i=0; i<cs->GetNumOfRoles(); i++)
	{
		vob=0;
		roleName = cs->GetRoleName(i); 
		if (roleName==CS_PLAYER_ROLENAME)	vob = activePlayerVob;		
		if (!vob) vob = world->SearchVobByName(roleName);		
		DeinitRoleVob(vob);
	}	

	DeinitRoleVob(cs->GetMainRole());
	return mainRoleVob;
	
}

zBOOL spcCCSSequencer::DeinitRoleVob(zCVob *vob)
{	
	// return TRUE;

	#ifdef COMPILING_GOTHIC		
		oCNpc* npc = dynamic_cast<oCNpc*>(vob);
		if (npc)
		{
			zERR_MESSAGE(4,0,"B: CS: DeinitRoleVobs "+npc->GetName(TRUE)+": Resetting HumanAI");
			//oCAIHuman* ai = zNEW(oCAIHuman);
			npc->UseStandAI();
		}
	#endif
		return TRUE;
}


void spcCCSSequencer::OnCsStart() 
{
	UpdateData(true);
	CString buttonText;
	ctrl_button_start.GetWindowText(buttonText);
	
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	dbplayer = csplayer;
	if (!csplayer) return;

	csplayer->deb = this;

	if (workMode==workCS) 
	{
		// Existiert ein Context? Dann beenden!
		if (current_context)
		{
			StopRunningCutscene();		
			return;
		}
		// sonst starten
		else		
		{	
			zCCSCutsceneContext::DisablePlayCutscenes(FALSE);

			#ifdef COMPILING_GOTHIC

				// Cutscene holen
				zCCutscene* cs = GetCutsceneFromFlatData();
				if (!cs) return;

				cs->SetOwnerPlayer(csplayer);
			
				// Cutscene initialisieren und Hauptrolle ermitteln
				oCNpc* roleVob = dynamic_cast<oCNpc*>(InitCutsceneBeforeRunning(cs));
				if (!roleVob) { MessageBox("Please select the main-role!");return; }										
	
				// Cutscene starten ....
				if (m_simulate)
				{
					zERR_MESSAGE(6,0,"B: SEQ: Simulating cutscene "+csName);					
					current_context = csplayer->StartCutscene(cs,roleVob,csName);					
				}
				else
				{
					zERR_MESSAGE(6,0,"B: SEQ: Testing cutscene "+csName);					
					current_context = csplayer->StartCutscene(cs,roleVob);					
				};

				// Ein AddRef auf den CutsceneContext ausfuehren
				if (current_context) current_context->AddRef();								
			
			#endif
			
			ctrl_button_start.SetWindowText(CS_BUTTON_STOP);			
			
			OnUpdate();

			// Per Timer schaut der Sequencer regelmaessig nach, obs der Cutscene noch gut geht (sieh noch laeuft etc...)			
			StartTimer();			
			return;
		}
	}
}


UINT timer=0;

void spcCCSSequencer::StartTimer() 
{
	// Alle 1,5 Sekunden
   timer = SetTimer(1, 1000, 0);
   // zCCSCutsceneContext::DisablePlayCutscenes(FALSE);
}

void spcCCSSequencer::StopTimer() 
{
   if (timer>0)
   {
	   KillTimer(timer);   
	   // zCCSCutsceneContext::DisablePlayCutscenes(TRUE);
   }
}

void spcCCSSequencer::OnTimer(UINT nIDEvent) 
{
   if (current_context)
   {
	   if (current_context->IsFinished())
	   {
			StopRunningCutscene();
	   };
   };
}


void spcCCSSequencer::StopRunningCutscene()
{
	zERR_MESSAGE(5,0,"spcCCSSequencer::StopRunningCutscene (StopTimer)");
	StopTimer();
	
	if (current_context)
	{	
		DeinitCutsceneAfterRunning(current_context);
		if (!current_context->IsFinished())
		{
			zERR_MESSAGE(5,0,"spcCCSSequencer::StopRunningCutscene (Stop Cutscene)");
			current_context->Stop(); // Um die Freigabe (Free/Release) kuemmert sich das Game			
		}		
		zERR_MESSAGE(5,0,"spcCCSSequencer::StopRunningCutscene (Release Cutscene)");
		zRELEASE(current_context); // Eigenes AddRef aufloesen
	}				

	zERR_MESSAGE(5,0,"spcCCSSequencer::StopRunningCutscene (OnUpdate)");
	OnUpdate();	
}

void spcCCSSequencer::OnUpdate()
{	
	CString buttonText;
	ctrl_button_start.GetWindowText(buttonText);	

	bool still_running = current_context && !current_context->IsFinished();
	
	if (still_running) 
	{
		ctrl_button_start.SetWindowText(CS_BUTTON_STOP);		
	}
	else 
	{
		ctrl_button_start.SetWindowText(CS_BUTTON_START);		
	}
}

void spcCCSSequencer::Reset()
{
	StopRunningCutscene();	
};


void spcCCSSequencer::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);	
}

void spcCCSSequencer::OnSetFocus(CWnd* pOldWnd) 
{
	CDialog::OnSetFocus(pOldWnd);			
}

void spcCCSSequencer::OnKeydownTracktree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;

	switch (pTVKeyDown->wVKey)
	{	
	case 46:
		if (MessageBox("Do you really want to remove this?","Remove",MB_YESNO) == IDYES)
		{
			OnRemoveRole();			
		}
		break;
	}

	*pResult = 0;
}

void spcCCSSequencer::OnUpdateInsertsyncblock(CCmdUI* pCmdUI) 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();	
	pCmdUI->Enable(lcs!=0);
}

void spcCCSSequencer::OnUpdateRemoverole(CCmdUI* pCmdUI) 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();	
	pCmdUI->Enable(lcs!=0);
}

void spcCCSSequencer::OnUpdateRemoveblock(CCmdUI* pCmdUI) 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();	
	pCmdUI->Enable(lcs!=0);
}

void spcCCSSequencer::OnUpdateRemovesync(CCmdUI* pCmdUI) 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();	
	pCmdUI->Enable( (lcs!=0) && (lcs->GetNumOfChilds()>1) );
}

void spcCCSSequencer::OnUpdateAddsyncblock(CCmdUI* pCmdUI) 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();	
	pCmdUI->Enable(lcs!=0);
}

void spcCCSSequencer::OnUpdateAddgentrack(CCmdUI* pCmdUI) 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();	
	pCmdUI->Enable(lcs!=0);
}

void spcCCSSequencer::OnUpdateRoleprops(CCmdUI* pCmdUI) 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();	
	pCmdUI->Enable(lcs!=0);
}

void spcCCSSequencer::OnUpdateCssave(CCmdUI* pCmdUI) 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();	
	pCmdUI->Enable(lcs!=0);
}

void spcCCSSequencer::OnUpdateCssaveAs(CCmdUI* pCmdUI) 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();	
	pCmdUI->Enable(lcs!=0);
}

void spcCCSSequencer::OnUpdateCsprops(CCmdUI* pCmdUI) 
{
	zCCutscene *lcs = GetCutsceneFromFlatData();	
	pCmdUI->Enable(lcs!=0);
}

void spcCCSSequencer::OnSelchangedTracktree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// OnRoleprops();
	SetFocus();

	*pResult = 0;
}

void spcCCSSequencer::OnCssave() 
{	
	if (workMode==workOU)
	{
		CMainFrame::mainframe->CSUpdate();
		ChangeDataState(0); // data valid and not changed			
	} 
	else 		
	{
		if (lastFileName==NEW_CUTSCENE_FILENAME)
		{
			OnCSsaveAs();
			return;
		};
		
		zoptions->ChangeDir(DIR_CUTSCENES);
		zCArchiver* arch = zarcFactory.CreateArchiverWrite(zSTRING(lastFileName.GetBuffer(0)),zARC_MODE_ASCII);		
		arch->WriteObject(flatData[0]);
		arch->Close();
		zRELEASE(arch);

		ChangeDataState(0); // data valid and not changed			
	}
}



void spcCCSSequencer::OnRoleAddByButton() 
{
	OnAddrole();
}

void spcCCSSequencer::OnRoleDelByButton() 
{
	OnRemoveRole();
}

#define TIME_THRESHOLD 80.0F   //alles über dieser Sekundenzahl wird als inkonsistent betrachtet

void spcCCSSequencer::BlockPositionCheck(zCCSBlockBase* blockToCheck, bool setToZero)
{
	if (!blockToCheck) return;
	if (blockToCheck->GetNumOfChilds()==0) return; // keine Childs, keine Fehler...
	
	zCSTIME lt = blockToCheck->GetChild(0)->GetMinTime(); //Dauer des Fokus ist
	for (int z=1; z<blockToCheck->GetNumOfChilds(); z++)
	{
		zCCSBlockBase* block = blockToCheck->GetChild(z);
		zCCSBlockPosition* lp = blockToCheck->GetChildPos(z);
		if (lp->position*lt>TIME_THRESHOLD)
		{			
			CString s;			
			s.Format(
				"Illegal block found: %s\r\n\r\n"
				"position is %i sec.\r\n",				
				block->GetInfo().ToChar(), int(lp->position*lt)
			);			
						
			// Korrektur (Art der Korrektur kann gewählt werden
			if (setToZero)
			//diese K. setzt die Pos auf Null
			{
				lp->position = 0.0F;
				s = s + "\r\nRessetted to position 0.";
			}
			else
			// diese K. setzt die Pos so, daß der Block vollständig unter der threshold liegt
			{
				lp->position = TIME_THRESHOLD - 1 - lp->block->GetMinTime();
				s = s + "\r\nRessetted to maximum possible position.";
			}
			MessageBox(s);			
		}

		BlockPositionCheck(dynamic_cast<zCCSBlock*>(blockToCheck->GetChild(z)),setToZero);
	}
}



spcCCSViewportScrollbar::spcCCSViewportScrollbar()
{
}
spcCCSViewportScrollbar::~spcCCSViewportScrollbar()
{};


void spcCCSViewportScrollbar::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
};


void spcCCSSequencer::OnCutscenesMovetobegin() 
{
	if (selected<0) return;

	zCCSAtomicBlock* bl = dynamic_cast<zCCSAtomicBlock*>(flatData[selected]);
	if (!bl) return;

	int focus = FindFocus(selected);
	int parent = focus-1;
	if (focus<=0) return;

	zCCSBlockPosition* bp = flatData[parent]->GetChildPos(selected-parent-1);
	if (!bp) return;
	bp->position=0;	

	ChangeDataState(1);

	flatData[parent]->BlockCorrection();			
	BlockPositionCheck(flatData[parent],false);	
	ChangeDataState				(1); // data valid and changed
	BuildAfterBlockCorrection	();
	DrawIt						();
}


void spcCCSSequencer::OnCutscenesSynchronous() 
{	
	if (selected>=0)
	{
		zCCSAtomicBlock* bl = dynamic_cast<zCCSAtomicBlock*>(flatData[selected]);
		if (bl) 
		{
			bl->SetSynchronized(!bl->IsSynchronized());
			selected = -1;
			DrawIt();
		}
	}
}

void spcCCSSequencer::OnUpdateCutscenesSynchronous(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(selected>=0);
	if (selected>=0)
	{
		zCCSAtomicBlock* bl = dynamic_cast<zCCSAtomicBlock*>(flatData[selected]);
		if (!bl) pCmdUI->Enable(false);
		else pCmdUI->SetCheck(bl->IsSynchronized());
	}
}

void spcCCSSequencer::OnCutscenesRemove() 
{
	OnRemoveblock();
}

void spcCCSSequencer::OnGrid() 
{
	UpdateData(true);
	m_grid = m_grid;
	UpdateData(false);
}
