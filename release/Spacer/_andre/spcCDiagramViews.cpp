// spcCDiagramViews.cpp : implementation file
//


#include "stdafx.h"
#include "Spacer.h"
#include "MainFrm.h"
#include "SpacerView.h"
#include "spcCConfiguration.h"
#include "spcCDiagramViews.h"

// z-files
#include "zConfig.h"
#include "zVob.h"

#ifdef _DEBUG
////#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// spcCDiagramViews dialog


spcCDiagramView::spcCDiagramView(CWnd* pParent /*=NULL*/)
	: CDialog(spcCDiagramView::IDD, pParent), viewPort(170,0,590,372),
	  flatData(), roleNames(), selected(-1), dataState(-1), workMode(workOU),
	  m_timepos(0), lastFileName(""), propmode(false), DB_RoleBuffer(0),
	  lastFirstItem(0), stepPlay(false)
{
	//{{AFX_DATA_INIT(spcCDiagramView)
	m_seltext = _T("");
	m_syncBlock = 0;
	//}}AFX_DATA_INIT
	//for (int z=0; z<16; z++) message_mapper[z]=0;
}


void spcCDiagramView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCDiagramView)
	DDX_Control(pDX, IDC_CS_START, ctrl_cs_start);
	DDX_Control(pDX, IDC_TRACKTREE, ctrl_tracktree);
	DDX_Control(pDX, IDC_OUTEXT, ctrl_seltext);
	DDX_Text(pDX, IDC_OUTEXT, m_seltext);
	DDX_Text(pDX, IDC_EDIT_SYNCBLOCK, m_syncBlock);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCDiagramView, CDialog)
	//{{AFX_MSG_MAP(spcCDiagramView)
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
	ON_COMMAND(ID_CSSAVE, OnCSSave)
	ON_COMMAND(ID_CSOPEN, OnCsopen)
	ON_COMMAND(ID_ADDTRACK_ANI, OnAddtrackAni)
	ON_COMMAND(ID_ADDTRACKSND, OnAddtracksnd)
	ON_COMMAND(ID_ADDTRACKTURN, OnAddtrackturn)
	ON_BN_CLICKED(IDC_TIMESCROLL_L, OnTimescrollL)
	ON_BN_CLICKED(IDC_TIMESCROLL_R, OnTimescrollR)
	ON_COMMAND(ID_CSNEW, OnCSnew)
	ON_COMMAND(ID_CSSAVE_AS, OnCSsaveAs)
	ON_COMMAND(ID_ADDTRACK_00, OnAddTrack_00)
	ON_COMMAND(ID_ADDTRACK_01, OnAddTrack_01)
	ON_COMMAND(ID_ADDTRACK_02, OnAddTrack_02)
	ON_COMMAND(ID_ADDTRACK_03, OnAddTrack_03)
	ON_COMMAND(ID_ADDTRACK_04, OnAddTrack_04)
	ON_COMMAND(ID_ADDTRACK_05, OnAddTrack_05)
	ON_COMMAND(ID_ADDTRACK_06, OnAddTrack_06)
	ON_COMMAND(ID_ADDTRACK_07, OnAddTrack_07)
	ON_COMMAND(ID_ADDTRACK_08, OnAddTrack_08)
	ON_COMMAND(ID_ADDTRACK_09, OnAddTrack_09)
	ON_COMMAND(ID_ADDTRACK_0A, OnAddTrack_0A)
	ON_COMMAND(ID_ADDTRACK_0B, OnAddTrack_0B)
	ON_COMMAND(ID_ADDTRACK_0C, OnAddTrack_0C)
	ON_COMMAND(ID_ADDTRACK_0D, OnAddTrack_0D)
	ON_COMMAND(ID_ADDTRACK_0E, OnAddTrack_0E)
	ON_COMMAND(ID_ADDTRACK_0F, OnAddTrack_0F)
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
	ON_BN_CLICKED(IDC_CS_REPEAT, OnCsRepeat)
	ON_BN_CLICKED(IDC_CS_START, OnCsStart)
	ON_BN_CLICKED(IDC_CS_STOP, OnCsStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////
// Destructor

spcCDiagramView::~spcCDiagramView()
{
	zCCSBlockBase* lcs = GetFlatData0();
	if (lcs) zRELEASE(lcs);
}

/////////////////////////////////////////////////////////////////////////////
// spcCDiagramView message handlers

void spcCDiagramView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// Do not call CDialog::OnPaint() for painting messages
	lastFirstItem = ctrl_tracktree.GetFirstVisibleItem();
	viewPort.DrawData(&dc,ctrl_tracktree,flatData,0,selected);
}

////////////////////////////////////////////////////////////////////////////
// spcCDiagramView methods

// private ones

void spcCDiagramView::drawIt()
{
	CClientDC dc(this); // device context for painting
	// Do not call CDialog::OnPaint() for painting messages
	if (flatData.GetNumInList()>2)
	{
		viewPort.DrawData(&dc,ctrl_tracktree,flatData,0,selected);
		lastFirstItem = ctrl_tracktree.GetFirstVisibleItem();
	}
	else
		viewPort.ClearData(&dc);
}
void spcCDiagramView::ViewRefresh()
{
	drawIt();
}
void spcCDiagramView::ViewDrawIfNessesary()
{
	if (ctrl_tracktree.GetFirstVisibleItem()!=lastFirstItem)
	{
		drawIt();
		lastFirstItem = ctrl_tracktree.GetFirstVisibleItem();
	}
}
zCCSBlockBase* spcCDiagramView::GetFlatData0()
{
	if (flatData.GetNumInList()>0) return flatData[0];
	else return NULL;
}

void spcCDiagramView::flatn(zCCSBlockBase* bl, HTREEITEM parent)
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
		flatn(lBl, thisITEM);
		z++;
		lBl = bl->GetChild(z);
	}
	
}

void spcCDiagramView::buildData(zCCSBlockBase* cs)
{
	if (!cs) return;
	flatData.EmptyList();
	ctrl_tracktree.DeleteAllItems();

	if (workMode==workCS) {
		flatData.Insert(cs);  // zur referenz
		createTrack_Roles();
		createTrackBlockRef(m_timepos);
		m_syncBlock = m_timepos;
	} else {
		flatData.Insert(cs);
		flatn(cs, TVI_ROOT);
	}

	HTREEITEM ITEM = ctrl_tracktree.GetFirstVisibleItem();
	while (ITEM != 0)
	{
		ctrl_tracktree.Expand(ITEM,TVE_EXPAND);
		ITEM = ctrl_tracktree.GetNextSiblingItem(ITEM);
	}
}

void spcCDiagramView::buildAfterBlockCorrection()
{
	zCCSBlockBase* cs = flatData[0];
	if (!cs) return;
	flatData.EmptyList();

	if (workMode==workCS) {
		flatData.Insert(cs);
//		createTrack_Roles();

		createTrackBlockRef(m_timepos);
		m_syncBlock = m_timepos;
	} else {
		flatData.Insert(cs);
		flatn(cs, TVI_ROOT);
	}
}

int spcCDiagramView::findFocus(int n)
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

void spcCDiagramView::createTrack_Roles	()
{
	if (	workMode!=workCS || 
			flatData.GetNumInList()==0) return;
	
	roleNames.EmptyList();
	zCCutscene* lcs = dynamic_cast<zCCutscene*>(GetFlatData0());//(zCCutscene*)flatData[0];
	if (lcs==0) return;
	for (int i=0; i<lcs->GetNumOfRoles(); i++)
		roleNames.Insert(CString(lcs->RoleName(i).ToChar()));
	
	HTREEITEM roleITEM;
	for (int rz=0; rz<roleNames.GetNumInList(); rz++)
	{
		roleITEM = ctrl_tracktree.InsertItem(roleNames[rz],TVI_ROOT);
		// erzeuge Tracks
		createTrack_AICom(roleITEM,rz);
	}
}

void spcCDiagramView::createTrack_AICom	(HTREEITEM roleITEM, int roleNumber)
{
	int i=0;
	zCCSBlockBase* sBl = 0;
	if (GetFlatData0()) sBl = GetFlatData0()->GetChild(i);
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
void spcCDiagramView::createTrackBlockRef(int num)
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

void spcCDiagramView::BuildMenu()
{
	if (!csplayer) return;

	CMenu* menubar = GetMenu();
	ASSERT(menubar != NULL);
	CMenu* menu = menubar->GetSubMenu(1);
	ASSERT(menu != NULL);
	
	if (workMode==workCS) {
		menu->EnableMenuItem(ID_ADDROLE,MF_ENABLED);
		menu->EnableMenuItem(ID_ADDSYNCBLOCK,MF_ENABLED);
		menu->EnableMenuItem(ID_INSERTSYNCBLOCK,MF_ENABLED);
	} else {
		menu->EnableMenuItem(ID_ADDROLE,MF_GRAYED);
		menu->EnableMenuItem(ID_ADDSYNCBLOCK,MF_GRAYED);
		menu->EnableMenuItem(ID_INSERTSYNCBLOCK,MF_GRAYED);
	}
//	if (selected>=0)
		menu->EnableMenuItem(ID_REMOVEBLOCK,MF_ENABLED);
//	else menu->EnableMenuItem(ID_REMOVEBLOCK,MF_GRAYED);

	menu->EnableMenuItem(ID_REMOVETRACK,MF_ENABLED);
	menu->EnableMenuItem(ID_REMOVEROLE,MF_ENABLED);
	CMenu* aimenu = menu->GetSubMenu(0);
	ASSERT(aimenu != NULL);

	//alles löschen
	for (int c=0; c<16; c++)
		aimenu->RemoveMenu(ID_ADDTRACK_00+c,0);
	// neu füllen
	int messageCounter =0;
	for (int z=0; z<csplayer->GetNumOfShortCom(); z++)
	{
		aimenu->AppendMenu(0,ID_ADDTRACK_00+messageCounter,csplayer->GetShortCom(z).ToChar());
		message_mapper[messageCounter]=z;
		messageCounter++;
	}
}

// public ones

void spcCDiagramView::AssignCutscene(zCCSBlockBase* cs)
{
	if (!csplayer) { zerr.Report(zERR_WARN,9000,zSTRING("A: (DiagramView: no player availeble!")); return; };
	flatData.EmptyList();
	roleNames.EmptyList();
	flatn(cs, TVI_ROOT);
	ChangeDataState(0); // data valid and not changed
	selected = 0;

	drawIt();

	BuildMenu();
}

void spcCDiagramView::AssignOutputUnit	(zCCSBlockBase* cs)
{
	if (!csplayer) { zerr.Warning("A: (DiagramView: no player availeble!"); return; };
	OnCSSave();
	ChangeDataState(0); // data valid and not changed
	selected = 0;
	workMode = workOU;

	buildData(cs);
	
	drawIt();

	BuildMenu();
}

int spcCDiagramView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	blockEdit.Create(IDD_INFO_DYNDLG,this);
	
	return 0;
}

void spcCDiagramView::OnOK()
{}

void spcCDiagramView::OnClose() 
{
	OnCSSave();
	blockEdit.CloseWindow();
	blockEdit.DestroyWindow();
	DestroyWindow();
	CMainFrame::mainframe->DeactivateCS();	
	//CDialog::OnClose(); not cause of non-modal
}

void spcCDiagramView::OnItemexpandedTracktree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	drawIt();
	
	*pResult = 0;
}

void spcCDiagramView::OnClickTracktree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	selected = -1;
	drawIt();
	
	*pResult = 0;
}

void spcCDiagramView::OnTimedec() 
{
	if (viewPort.timeScale>1)
	{
		viewPort.timeScale--;
		drawIt();
	}
}

void spcCDiagramView::OnTimeinc() 
{
	if (viewPort.timeScale<20)
	{
		viewPort.timeScale++;
		drawIt();
	}
}

void spcCDiagramView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int newSelected = viewPort.PickData(point,ctrl_tracktree,flatData,0);
//	if (newSelected!=selected) 
		selected = newSelected;
//	else selected = -1;

	if (selected>-1)
	{
		ctrl_tracktree.SelectItem(NULL);
		m_seltext = flatData[selected]->GetInfo().ToChar();
		zCCSAtomicBlock* bl = dynamic_cast<zCCSAtomicBlock*>(flatData[selected]);
		if (bl) blockEdit.Select(bl->GetCommand());
		drawIt();
	} 
	else m_seltext = "";
	UpdateData(false);
	CDialog::OnLButtonDown(nFlags, point);
}

void spcCDiagramView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CClientDC dc(this); // device context for painting
	if (viewPort.IsInMovement(point))
	{
		int delta = viewPort.EndBlockMovement(&dc,point);
		int focus = findFocus(selected);
		int parent = focus-1;
		if (focus>0)
		{
			double sec = double(delta)*viewPort.GetPixelTimeValue(); // soviel sekunden wurde der Block verschoben
			zCCSBlockPosition* bp = flatData[parent]->GetChildPos(selected-parent-1);
			assert(bp->block==flatData[selected]);
			if (flatData[focus]->GetMinTime()!=0)
				bp->position += (float)(sec/flatData[focus]->GetMinTime());
			else bp->position += (float)sec;
			if (sec!=0) ChangeDataState(1);
			flatData[parent]->BlockCorrection();
			selected = -1;
			ChangeDataState(1); // data valid and changed
			buildAfterBlockCorrection();
			drawIt();
		}
	}
	else
		if (selected==-1)
		{
			m_seltext = "";
			drawIt();
			UpdateData(false);
		}

	CDialog::OnLButtonUp(nFlags, point);
}

void spcCDiagramView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ((nFlags & MK_LBUTTON)==MK_LBUTTON)
	{
		CClientDC dc(this); // device context for painting
		if (!viewPort.IsInMovement(point)) 
		{
			if (viewPort.GetLastPick()!=point)
			{
				viewPort.BeginBlockMovement(&dc,point);
				viewPort.BlockMove(&dc,point);
			}
		} else	viewPort.BlockMove(&dc,point);
	}
	CDialog::OnMouseMove(nFlags, point);
}

void spcCDiagramView::OnRButtonDown(UINT nFlags, CPoint point) 
{	
	CDialog::OnRButtonDown(nFlags, point);
}

void spcCDiagramView::OnChangeText() 
{	
	if (selected<0) return;
	UpdateData(true);
	flatData[selected]->SetInfo(zSTRING(m_seltext.GetBuffer(0)));
	ChangeDataState(1);
	drawIt();
}

void spcCDiagramView::AssignParameter(zSTRING & p)
{
	if (selected<0) return;
	m_seltext = p.ToChar();
	flatData[selected]->SetInfo(p);
	ChangeDataState(1);
	drawIt();
	UpdateData(false);
}

void spcCDiagramView::AssignIntegratedRole(zCVob* irole)
{
	if (flatData.GetNumInList==0) return;

	zCVob * cscopy = dynamic_cast<zCVob*>(irole->CreateCopy());
	if (cscopy==0) return;

	zCCutscene* lcs = static_cast<zCCutscene*>(GetFlatData0());
	if (!lcs) return;
	bool found = false;
	int z=0;
	while (z<lcs->roleNames.GetNumInList() && !found)
	{
		if (lcs->roleNames[z]->GetRoleVob() &&
			lcs->roleNames[z]->GetRoleVob()->GetVobName()==cscopy->GetVobName())
			found = true;
		else z++;
	}
	if (z==lcs->roleNames.GetNumInList()) lcs->roleNames.Insert(new zCCSRole());
	else 
	{
		if (AfxMessageBox("Replace existing vob?",MB_YESNO)==IDYES)
			lcs->roleNames[z]->GetRoleVob()->Release();  // delete old von
		else return;
	}
	lcs->roleNames[z]->SetRoleVob(cscopy); // the copy gets member of the role
	
	ChangeDataState(1);
	buildData(GetFlatData0());
	drawIt();
	UpdateData(false);
}

void spcCDiagramView::ChangeDataState(int newState)
{
	dataState = newState;
	// modify menu
	CMenu* menubar = GetMenu();
	ASSERT(menubar != NULL);
	CMenu* menu = menubar->GetSubMenu(0);
	ASSERT(menu != NULL);
	if (dataState==1) {
		menu->EnableMenuItem(ID_CSSAVE, MF_BYCOMMAND | MF_ENABLED);
//		menu->EnableMenuItem(ID_CSSAVE_AS, MF_BYCOMMAND | MF_ENABLED);
	}
	else
	{
		menu->EnableMenuItem(ID_CSSAVE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
//		menu->EnableMenuItem(ID_CSSAVE_AS, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}
}
void spcCDiagramView::OnAddgentrack() 
{
if (dataState == -1) return;

	if (workMode==workCS)
	{
		HTREEITEM rItem = ctrl_tracktree.GetSelectedItem();
		if (rItem==0) return;

		CString rName = ctrl_tracktree.GetItemText(rItem);
		int z=0;
		while (	z<roleNames.GetNumInList() && 
				roleNames[z]!=rName) z++;
		zCEventMessage* msg = blockEdit.Insert();
		if (flatData[1] && msg)
		{
			zCCSAtomicBlock* aBl = new zCCSAtomicBlock();
			aBl->SetCommand(msg);
			if (z<roleNames.GetNumInList())
				flatData[1]->InsertBlock(aBl,z);
		}
		else return;
	}
	
	selected = -1;
	ChangeDataState(1); // data valid and changed
	buildData(GetFlatData0());
}
void spcCDiagramView::addTrack(int nr) 
{
	if (dataState == -1) return;
	zCCSBlockBase* lBlock =0;

	if (workMode==workOU)
	{
		// TODO: insert new block
		return;
	}
	else 
	{
		HTREEITEM rItem = ctrl_tracktree.GetSelectedItem();
		if (rItem==0) return;

		CString rName = ctrl_tracktree.GetItemText(rItem);
		int z=0;
		while (	z<roleNames.GetNumInList() && 
				roleNames[z]!=rName) z++;
		if (flatData[1])
		{		
			if (z<roleNames.GetNumInList())
			{
				zCCSAtomicBlock* aBl = new zCCSAtomicBlock();
				aBl->SetCommand(csplayer->MessageConstructor(nr));
				flatData[1]->InsertBlock(aBl,z);
			}
		}
		else return;
	}
	
	selected = -1;
	ChangeDataState(1); // data valid and changed
	buildData(GetFlatData0());
}

void spcCDiagramView::OnCSSave() 
{
if (dataState==1)
	if (workMode==workOU)
	{
		if (AfxMessageBox("Data has changed!\r\nDo you want to store it?",MB_YESNO)==IDYES)
		{
			csplayer->LibStore();
			CMainFrame::mainframe->CSUpdate();
			ChangeDataState(0); // data valid and not changed
		}
	} else {
		CString info = "Data has changed!\r\nDo you want to store "+lastFileName+" ?";
		if (AfxMessageBox(info,MB_YESNO)==IDYES)
		{
			zcfg.ChangeDir(DIR_CUTSCENES);
			zCArchiver arch;
			arch.OpenWriteFile(zSTRING(lastFileName.GetBuffer(0)),zCArchiver::zARC_MODE_ASCII);
			arch.WriteObject(flatData[0]);
			arch.Close();
			ChangeDataState(0); // data valid and not changed
		}
	}
}

void spcCDiagramView::OnCsopen() 
{
	// fileselect
	zcfg.ChangeDir(DIR_CUTSCENES);

	CString filter = "Cutscene (*.cs)|*.cs|All Files(*.*)|*.*||";
	CFileDialog* dlg = new CFileDialog(TRUE,"cs","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);

	zFILE::DirectFileAccess(true);
	int result = dlg->DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{				
		CString fileName= dlg->GetFileName();
		delete (dlg);
		// load
		zCArchiver arch;
		arch.OpenReadFile(zSTRING(fileName.GetBuffer(0)));
		zCCutscene *lcs = static_cast<zCCutscene*>(arch.ReadObject());
		arch.Close();		
		
		// build
		ChangeDataState(0); // data valid and not changed
		selected = 0;
		lastFileName = fileName;

		roleNames.EmptyList(); // new roles expected
		workMode = workCS;

		buildData(lcs); // Pointer coltrol is switched to flatdata
		drawIt();
		BuildMenu();
	} else delete (dlg);
}

void spcCDiagramView::OnAddtrackAni() 
{
	addTrack(3);
}

void spcCDiagramView::OnAddtracksnd() 
{
	addTrack(2);	
}

void spcCDiagramView::OnAddtrackturn() 
{
	addTrack(7);
}

void spcCDiagramView::OnChangeTimePos() 
{
	UpdateData(true);
//	buildData(GetFlatData0());
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
	drawIt();
}

void spcCDiagramView::OnTimescrollL() 
{
	if (m_timepos>0 && workMode==workCS)
	{ m_timepos--; OnChangeTimePos(); };
}

void spcCDiagramView::OnTimescrollR() 
{
	if (flatData.GetNumInList()==0) return;
	if (m_timepos<GetFlatData0()->GetNumOfChilds()-1 && workMode==workCS)
	{ m_timepos++; OnChangeTimePos(); };
}

void spcCDiagramView::OnCSnew() 
{
	zCCutscene* lcs = new zCCutscene();
	
	lcs->NewCS();

	ChangeDataState(1); // data valid and changed
	selected = 0;
	lastFileName = "NewCS.cs";

	roleNames.EmptyList();
	workMode = workCS;

	buildData(lcs);  // pointer control switches to flatData
	drawIt();

	BuildMenu();
}

void spcCDiagramView::OnCSsaveAs() 
{
	zcfg.ChangeDir(DIR_CUTSCENES);

	CString filter = "|Cutscene(*.cs)|*.cs||";
	CFileDialog* dlg = new CFileDialog(false,"cs",lastFileName,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);
	
	zFILE::DirectFileAccess(true);
	int result = dlg->DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)	{
		lastFileName = dlg->GetFileName();
		delete (dlg);

		zcfg.ChangeDir(DIR_CUTSCENES);
		zCArchiver arch;
		arch.OpenWriteFile(zSTRING(lastFileName.GetBuffer(0)),zCArchiver::zARC_MODE_ASCII);
		arch.WriteObject(flatData[0]);
		arch.Close();

		ChangeDataState(0); // data valid and not changed		
	} else delete (dlg);
}

void spcCDiagramView::OnAddTrack_00(){ addTrack(message_mapper[0]); }
void spcCDiagramView::OnAddTrack_01(){ addTrack(message_mapper[1]); }
void spcCDiagramView::OnAddTrack_02(){ addTrack(message_mapper[2]); }
void spcCDiagramView::OnAddTrack_03(){ addTrack(message_mapper[3]); }
void spcCDiagramView::OnAddTrack_04(){ addTrack(message_mapper[4]); }
void spcCDiagramView::OnAddTrack_05(){ addTrack(message_mapper[5]); }
void spcCDiagramView::OnAddTrack_06(){ addTrack(message_mapper[6]); }
void spcCDiagramView::OnAddTrack_07(){ addTrack(message_mapper[7]); }
void spcCDiagramView::OnAddTrack_08(){ addTrack(message_mapper[8]); }
void spcCDiagramView::OnAddTrack_09(){ addTrack(message_mapper[9]); }
void spcCDiagramView::OnAddTrack_0A(){ addTrack(message_mapper[10]); }
void spcCDiagramView::OnAddTrack_0B(){ addTrack(message_mapper[11]); }
void spcCDiagramView::OnAddTrack_0C(){ addTrack(message_mapper[12]); }
void spcCDiagramView::OnAddTrack_0D(){ addTrack(message_mapper[13]); }
void spcCDiagramView::OnAddTrack_0E(){ addTrack(message_mapper[14]); }
void spcCDiagramView::OnAddTrack_0F(){ addTrack(message_mapper[15]); }

void spcCDiagramView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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
		buildData(flatData[0]);
		}
	}*/
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void spcCDiagramView::OnRemoveblock() 
{
	if (dataState == -1) return;

	if (selected>=0)
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
			buildData(GetFlatData0());
		}
	}
}

void spcCDiagramView::OnEndlabeleditTracktree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	HTREEITEM lItem = pTVDispInfo->item.hItem;

	int flatEntry = ctrl_tracktree.GetItemData(lItem);
	CString oldRoleName(ctrl_tracktree.GetItemText(lItem));
	int sc=0;
	while (	sc<roleNames.GetNumInList() &&
			roleNames[sc]!=oldRoleName) sc++;
	CEdit* lEdit = ctrl_tracktree.GetEditControl();
	if (roleNames.GetNumInList()==sc) return;
	int lc = lEdit->GetLineCount();
	if (lc>0)
	{
		TCHAR str[100];
		lEdit->GetLine(0,str,60);
		if (GetFlatData0())
			((zCCutscene*)GetFlatData0())->roleNames[sc]->assign(str);

		ctrl_tracktree.SetItemText(lItem,str);
	}
	selected = -1;
	ChangeDataState(1); // data valid and changed
	ctrl_tracktree.DeleteAllItems();
	buildData(GetFlatData0());

	*pResult = 0;
}

void spcCDiagramView::OnAddrole() 
{
	((zCCutscene*)GetFlatData0())->NewRole(zSTRING("NEW_ROLE"));
	
	selected = -1;
	ChangeDataState(1); // data valid and changed
	buildData(GetFlatData0());
}

void spcCDiagramView::OnAddsyncblock() 
{
	if (flatData.GetNumInList()==0) return;

	GetFlatData0()->NewBlock(-1, GetFlatData0()->GetNumOfChilds());
	
	selected = -1;
	ChangeDataState(1); // data valid and changed
	buildData(GetFlatData0());
}

void spcCDiagramView::OnInsertsyncblock() 
{
	if (flatData.GetNumInList()==0) return;

	GetFlatData0()->NewBlock(-1, m_timepos);
	
	selected = -1;
	ChangeDataState(1); // data valid and changed
	buildData(GetFlatData0());
}

void spcCDiagramView::OnRemoveRole() 
{

	if (workMode!=workCS || !GetFlatData0()) return;

	HTREEITEM rItem = ctrl_tracktree.GetSelectedItem();
	if (rItem==0) return;
	
	CString rName = ctrl_tracktree.GetItemText(rItem);

	int z=0;
	while (	z<roleNames.GetNumInList() && 
			roleNames[z]!=rName) z++;
	if (z<roleNames.GetNumInList())
	{
		((zCCutscene*)GetFlatData0())->DeleteRole(z);
	
		selected = -1;
		ChangeDataState(1); // data valid and changed
		ctrl_tracktree.DeleteAllItems();
		buildData(GetFlatData0());
	}
}

void spcCDiagramView::OnUpdateEdit(CCmdUI* pCmdUI) 
{
	BuildMenu();
}

void spcCDiagramView::OnShowProp()
{
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
}

void spcCDiagramView::OnCsprops() 
{
	zCCutscene *lcs = dynamic_cast<zCCutscene*>(GetFlatData0());
	if (lcs)
	{
		if(!propmode) OnShowProp();
		blockEdit.Select(lcs->properties);
	}
}

void spcCDiagramView::OnRoleprops() 
{
	if (workMode!=workCS || !GetFlatData0()) return;

	HTREEITEM rItem = ctrl_tracktree.GetSelectedItem();
	if (rItem==0) return;
	
	CString rName = ctrl_tracktree.GetItemText(rItem);

	int z=0;
	while (	z<roleNames.GetNumInList() && 
			roleNames[z]!=rName) z++;
	zCCutscene *lcs = dynamic_cast<zCCutscene*>(GetFlatData0());
	if (z<roleNames.GetNumInList() && lcs)
	{
		if(!propmode) OnShowProp();
		blockEdit.Select((lcs->roleNames[z]));
	}
}

void spcCDiagramView::OnRemovesync() 
{
	zCCutscene *lcs = dynamic_cast<zCCutscene*>(GetFlatData0());
	if (!lcs) return;
	if (lcs->GetNumOfChilds()<2)
	{
		AfxMessageBox("Just one syncblock left!");
		return;
	}
	if (AfxMessageBox("Do you realy want to remove this syncblock?",MB_YESNO)==IDYES)
	{
		lcs->DeleteChild(m_syncBlock);
		if (m_syncBlock==lcs->GetNumOfChilds()) m_syncBlock--;
		selected = -1;
		ChangeDataState(1); // data valid and changed
		ctrl_tracktree.DeleteAllItems();
		buildData(GetFlatData0());
	}
}

void spcCDiagramView::OnCsRepeat() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}

void spcCDiagramView::OnCsStart() 
{
	if (workMode==workCS) {
		stepPlay=true;
		CSpacerView::view->VobDoCS(GetFlatData0());
		ctrl_cs_start.SetWindowText("next");
	}
}

void spcCDiagramView::OnCsStop() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}
