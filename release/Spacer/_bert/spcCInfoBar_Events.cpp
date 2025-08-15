// spcCInfoBar_Events.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "SpacerView.h"
#include "SpacerDoc.h"
#include "MainFrm.h"

#include "z3d.h"
#include "zEventMan.h"
#include "zVob.h"
#include "zWorld.h"
#include "zdisk.h"

#include "spcCInfoBar_Events.h"
#include "spcCInputDialog.h"
#include "spcCWorkProgressDlg.h"

#ifdef _DEBUG
////#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCInfoBar_Events 


spcCInfoBar_Events::spcCInfoBar_Events(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInfoBar_Events::IDD, pParent), cur_vob(0), moverVob(0), 
		selected(-1)
{
	//{{AFX_DATA_INIT(spcCInfoBar_Events)
	m_classname = _T("");
	m_vobname = _T("");
	m_visualname = _T("");
	m_sel_cd_dyn = FALSE;
	m_sel_cd_stat = FALSE;	
	m_kf_pos = 0;
	m_insertmode = 0;
	m_danage_value = 0.0f;
	m_source_vob = _T("");
	//}}AFX_DATA_INIT
	event_sourcevob = 0;
}

spcCInfoBar_Events::~spcCInfoBar_Events()
{
	zRELEASE(event_sourcevob);
};


void spcCInfoBar_Events::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInfoBar_Events)
	DDX_Radio(pDX, IDC_KFC_AFTER, m_insertmode);	
	DDX_Control(pDX, IDC_LIST_TARGETS, ctrl_list_targets);
	DDX_Control(pDX, IDC_LIST_SOURCES, ctrl_list_sources);
	DDX_Control(pDX, IDC_EVENT_SEND, ctrl_event_send);
	DDX_Control(pDX, IDC_EVENT_LIST, ctrl_event_list);
	DDX_Control(pDX, IDC_KF_EDIT, ctrl_kf_edit);
	DDX_Control(pDX, IDC_DELETEKEY, ctrl_deletebutton);
	DDX_Control(pDX, IDC_CREATEKEY, ctrl_createkey);
	// DDX_Control(pDX, IDC_VISUALNAME, ctrl_visualname);
	DDX_Text(pDX, IDC_CLASSNAME, m_classname);
	DDX_Text(pDX, IDC_VOBNAME, m_vobname);
	// DDX_CBString(pDX, IDC_VISUALNAME, m_visualname);
	DDX_Check(pDX, IDC_SEL_CD_DYN, m_sel_cd_dyn);
	DDX_Check(pDX, IDC_SEL_CD_STAT, m_sel_cd_stat);
	DDX_Text(pDX, IDC_KF_EDIT, m_kf_pos);	
	DDX_Text(pDX, IDC_SOURCEVOB, m_source_vob);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCInfoBar_Events, CDialog)
	//{{AFX_MSG_MAP(spcCInfoBar_Events)
	ON_EN_CHANGE(IDC_VOBNAME, OnChangeVobname)
	//ON_CBN_SELCHANGE(IDC_VISUALNAME, OnSelchangeVisualname)
	//ON_BN_CLICKED(IDC_VISUALBUTTON, OnVisualbutton)
	ON_BN_CLICKED(IDC_SEL_CD_DYN, OnSelCdDyn)
	ON_BN_CLICKED(IDC_SEL_CD_STAT, OnSelCdStat)	
	ON_EN_CHANGE(IDC_KF_EDIT, OnChangeKfEdit)
	ON_BN_CLICKED(IDC_DELETEKEY, OnDeletekey)
	ON_BN_CLICKED(IDC_CREATEKEY, OnCreatekey)
	ON_BN_CLICKED(IDC_KF_DEC, OnKfDec)
	ON_BN_CLICKED(IDC_KF_INC, OnKfInc)
	ON_LBN_SELCHANGE(IDC_EVENT_LIST, OnEventListSelected)
	ON_BN_CLICKED(IDC_EVENT_SEND, OnEventSend)
	ON_BN_CLICKED(IDC_COLLECT, OnCollect)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SOURCES, OnDblclkListSources)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TARGETS, OnDblclkListTargets)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// eigene Methoden

void spcCInfoBar_Events::SelectVob(zCVob* pickedVob)
{
	RemoveVobsFromLists();	// Wichtig: Vobs immer wieder freigeben	

	// zCVob* vob = pickedVob;		

	if (pickedVob)
	{
		zRELEASE(cur_vob);
		cur_vob = pickedVob;
		cur_vob->AddRef();

		m_vobname = cur_vob->GetVobName().ToChar();
		m_classname = cur_vob->GetClassName_().ToChar();
		zCVisual* vis = cur_vob->GetVisual();
		if (vis)
			m_visualname = vis->GetVisualName().ToChar();
		else m_visualname = "kein Visual";
		// collFlags
		m_sel_cd_dyn = cur_vob->GetCollDetDyn();
		m_sel_cd_stat = cur_vob->GetCollDetStat();		
		// Keyframer
		moverVob = dynamic_cast<zCMover*>(cur_vob);
		bool isMover= (moverVob!=0);
		ctrl_createkey.EnableWindow(isMover);
		ctrl_deletebutton.EnableWindow(isMover);
		if (isMover)
		{
			if (moverVob->keyframeList.GetNumInList()>0)
			{
				ctrl_kf_edit.EnableWindow(true);
				m_kf_pos = moverVob->GetActKeyframe();
				SetToKeyPos();
			}
			else ctrl_kf_edit.EnableWindow(false);
		} else {
			ctrl_kf_edit.EnableWindow(false);
		}
		
		CollectTriggerTargets();

		UpdateData(false);
	}
	else
	{	
		zRELEASE(cur_vob);
		cur_vob=0;
		moverVob=0;
		m_vobname = "";
		m_classname = "";
		m_visualname = "";
		m_sel_cd_dyn = FALSE;
		m_sel_cd_stat = FALSE;		
		ctrl_createkey.EnableWindow(false);
		ctrl_kf_edit.EnableWindow(false);
		UpdateData(false);
	}
			
	UpdateWindow();
}

void spcCInfoBar_Events::OnChangeVisual(CString & visName)
{
	if (!cur_vob) return;
	cur_vob->SetVisual(zSTRING(visName.GetBuffer(0)));
	m_visualname = visName;
	UpdateData(false);
}

void spcCInfoBar_Events::InitData()
{	
	CSpacerDoc* pDoc = CSpacerView::view->GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->GetWorld()) return;
	
}
void spcCInfoBar_Events::PreClose()
{	
	RemoveVobsFromLists();
}


void spcCInfoBar_Events::SetToKeyPos()
{
	if (!moverVob) return;
	zREAL position((float)m_kf_pos);
	if (
		moverVob->keyframeList.GetNumInList()>0			&&	// keyframeliste nicht leer
		m_kf_pos<moverVob->keyframeList.GetNumInList()		// position innerhalb erlaubtem Bereich?
	   )
	{
		moverVob->SetToKeyframe(position,0);
	}
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCInfoBar_Events 

void spcCInfoBar_Events::OnOK() 
{
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
	// prevent that ENTER will close the dialog
	// CDialog::OnOK();
}

void spcCInfoBar_Events::OnChangeVobname() 
{
	UpdateData(TRUE);
	if (cur_vob) {
		cur_vob->SetVobName(m_vobname.GetBuffer(0));		
		// change name in voblist
		CMainFrame::mainframe->HandleObjChange(cur_vob);
	}
}

/*
void spcCInfoBar_Events::OnSelchangeVisualname() 
{
	OnChangeVisual(m_visualname);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Events::OnVisualbutton() 
{
	CString filter = "3DS-File (*.3ds)|*.3ds|Textur (*.tga)|*.tga|Model (*.msh)|*.msh|Model (*.mds)|*.mds|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE,"3ds","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);
	
	zoptions->ChangeDir(DIR_DATA);
	zFILE::DirectFileAccess(true);
	int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)	
	{				
		OnChangeVisual(dlg.GetFileName());
	}

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}
*/

void spcCInfoBar_Events::OnSelCdDyn() 
{
	UpdateData(TRUE);
	if (cur_vob) cur_vob->SetCollDetDyn(m_sel_cd_dyn);	
	
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Events::OnSelCdStat() 
{
	UpdateData(TRUE);
	if (cur_vob) cur_vob->SetCollDetStat(m_sel_cd_stat);	
	
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

BOOL spcCInfoBar_Events::OnInitDialog() 
{
	CDialog::OnInitDialog();

	ctrl_event_list.ResetContent();	
	zCEventCore* eventCore = new zCEventCore((zCEventCore::zTEventCoreSubType)0);
	int num_types = eventCore->MD_GetNumOfSubTypes();
	zSTRING s;
	for (int i=0;i<num_types;i++)
	{	
		s = eventCore->MD_GetSubTypeString(i);
		ctrl_event_list.AddString(s.ToChar());
	}

	zRELEASE(eventCore);

	ctrl_event_send.EnableWindow(FALSE);
	
	return TRUE; 
}

void spcCInfoBar_Events::OnChangeKfEdit() 
{		
	int oldFrame = m_kf_pos;
	UpdateData(true);
	if (m_kf_pos>=moverVob->keyframeList.GetNumInList())
		m_kf_pos = oldFrame;
	SetToKeyPos();		
	
	UpdateData(false);
}

void spcCInfoBar_Events::OnCreatekey() 
{
	if (moverVob)
	{
		UpdateData(true);
		if (moverVob->keyframeList.GetNumInList()==0)
			ctrl_kf_edit.EnableWindow(true);
		zCMover::zTMov_Keyframe KF = zCMover::GetKeyframe(moverVob);
		int numInList = moverVob->keyframeList.GetNumInList();
		// 
		// Dem Insert-Modus entsprechend bearbeiten
		//
		
		if (numInList==0) 
		{
			moverVob->keyframeList.Insert(KF);
		}
		else 
		{
			switch (m_insertmode)
			{
			case 0: // Insert After
				if(m_kf_pos+1==numInList)
					moverVob->keyframeList.Insert(KF);
				else
					moverVob->keyframeList.InsertAtPos(KF,m_kf_pos+1);
				m_kf_pos++;
				break;
			case 1: // Insert Before
				moverVob->keyframeList.InsertAtPos(KF,m_kf_pos);
				break;
			case 2: // Overwrite			
				moverVob->keyframeList[m_kf_pos]=KF;
				break;
			};
		}
		UpdateData(false);
	}

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Events::OnKfDec() 
{
	UpdateData(true);

	if (!moverVob) { zERR_WARNING("B: SPC EV: No Mover defined.");return;}

	if (m_kf_pos>=1) m_kf_pos--;

	SetToKeyPos();		
	
	UpdateData(false);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Events::OnKfInc() 
{
	UpdateData(true);

	if (!moverVob) { zERR_WARNING("B: SPC EV: No Mover defined.");return;}	

	if (m_kf_pos+1<moverVob->keyframeList.GetNumInList()) m_kf_pos++;	
	
	SetToKeyPos();		
	
	UpdateData(false);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

/*
void spcCInfoBar_Events::OnEditbbox() 
{
	if (!cur_vob) return;
	// BoundingBox
	UpdateData(TRUE);
	if (m_editbbox)
	{
		zTBBox3D bbox = cur_vob->GetBBox3DWorld();
		if (bbox.mins==bbox.maxs)
			bbox.maxs = bbox.mins + zVEC3(5.0,5.0,5.0);
		dragBottom->ShowYourself(bbox.mins);
		dragTop->ShowYourself(bbox.maxs);
	}
	else
	{
		dragBottom->HideYourself();
		dragTop->HideYourself();
		CSpacerView::view->VobModeMove(MV_NORMAL);
	}
	
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}
*/

void spcCInfoBar_Events::OnDeletekey() 
{
	if (moverVob->keyframeList.GetNumInList()==0) return;
	
	moverVob->keyframeList.RemoveOrderIndex(m_kf_pos);

	if (m_kf_pos>0) 
	{
		m_kf_pos--;
		SetToKeyPos();
	}

	if (moverVob->keyframeList.GetNumInList()==0)
			ctrl_kf_edit.EnableWindow(false);
	UpdateData(false);
}



void spcCInfoBar_Events::OnEventListSelected() 
{
	ctrl_event_send.EnableWindow(TRUE);
}

void spcCInfoBar_Events::OnEventSend() 
{	
	if (!event_sourcevob)
	{
		event_sourcevob = new zCVob;		
		event_sourcevob->SetVobName("Event-TestVob");
		event_sourcevob->SetCollDet(TRUE);
		event_sourcevob->SetPhysicsEnabled(TRUE);		
	};

	if (!cur_vob) return;
	
	int index = ctrl_event_list.GetCurSel();
	if (index<0) return;
	
	zCEventCore* eventCore = new zCEventCore((zCEventCore::zTEventCoreSubType)index, event_sourcevob, event_sourcevob, 10000.0f);	

	cur_vob->GetEventManager()->OnMessage(eventCore, event_sourcevob); 
	
	zCMover* mov = dynamic_cast<zCMover*>(cur_vob);
	if (mov)
	{
		m_kf_pos = mov->GetActKeyframe();
	}
	// SetToKeyPos(); // Raus?
	UpdateData(false);
}


struct spcTEventLists
{
	CListBox* sources;
	CListBox* targets;

	spcTEventLists()
	{
		sources=0;
		targets=0;
	};

};

class zCVobCallback_CollectEventList : public zCVobCallback 
{
	zCVob*					vob;	
	zCList<zCVob>*			sources;
	spcCWorkProgressDlg*	winProgressDlg;
public:	

	zCVobCallback_CollectEventList() { sources = 0;};
	virtual ~zCVobCallback_CollectEventList() { sources = 0; };

	void Init (zCList<zCVob>* _sources, zCVob* _vob, spcCWorkProgressDlg* ctrl)
	{
		vob		= _vob;
		sources = _sources;		
		winProgressDlg = ctrl;
	};

	
	virtual void HandleVob(zCVob* checkVob, void *callbackData) 
	{				
		if (!vob) return;

		winProgressDlg->Step(1);
		
		zSTRING triggerTarget = "";
		if (checkVob->GetTriggerTarget()) triggerTarget = checkVob->GetTriggerTarget()->ToChar();
		
		if (sources && !triggerTarget.IsEmpty() && triggerTarget == vob->GetVobName())
		{
			checkVob->AddRef();
			sources->Insert(checkVob);
		};
		/*
		if (targets && !vobTriggerTarget.IsEmpty() && vobTriggerTarget == checkVob->GetVobName())
		{			
			checkVob->AddRef();
			targets->Insert(checkVob);
		};
		*/
	};
};



void spcCInfoBar_Events::CollectTriggerTargets()
{
	RemoveVobsFromLists();

	zCWorld* world = CSpacerDoc::doc->GetWorld();
	if (!world) return;

	ctrl_list_targets.EnableWindow(true);

	zCVob* vob;
	LVITEM item;
	item.iItem = 0;
	item.iSubItem = 0;
	item.mask = LVIF_TEXT | LVIF_PARAM;	

	CString vobClassName, vobName, vobDescription;
	
	if (cur_vob->GetTriggerTarget())
	{
		zCArray<zCVob*> targetList;

		int ttz=0;
		while ( cur_vob->GetTriggerTarget(ttz) )
		{
			if (!cur_vob->GetTriggerTarget(ttz)->IsEmpty()) 
			{				
				targetList.EmptyList();				
				world->SearchVobListByName(*(cur_vob->GetTriggerTarget(ttz)),targetList);
				for (int i=0; i<targetList.GetNumInList(); i++) 
				{
					vob = targetList.GetSafe(i);
					if (vob) { vob->AddRef();targetVobList.Insert(vob); }
				}
			}
			ttz++;
		}
	}

	for (int i=0;i<targetVobList.GetNumInList();i++)
	{
		vob = targetVobList.Get(i);
		vobClassName = vob->GetClassDef()->GetClassName_().ToChar();
		vobName = vob->GetVobName().ToChar();
		vobName.MakeLower();
		vobDescription = vobClassName + ":" + vobName;
		item.pszText = vobDescription.GetBuffer(0);		
		item.cchTextMax = vobDescription.GetLength();
		item.lParam = (LPARAM)vob;		
		if (ctrl_list_targets.InsertItem(&item)>=0)
		{
			vob->AddRef();
		};
	};	

	UpdateData(false);
};


void spcCInfoBar_Events::OnCollect() 
{
	RemoveVobsFromLists();

	if (!cur_vob) return;
	
	CollectTriggerTargets();
	
	ctrl_list_sources.EnableWindow(true);

	if (!cur_vob) return;	

	zCWorld* world = CSpacerDoc::doc->GetWorld();
	if (!world) return;

	spcCWorkProgressDlg* dlg = new spcCWorkProgressDlg();
	dlg->Create(IDD_WORKING_INFO,this);
	dlg->ShowWindow(SW_SHOW);
	dlg->Init(0,world->globalVobTree.CountNodes());

	zCVobCallback_CollectEventList vobCallback;
	vobCallback.Init(&sourceVobList,cur_vob, dlg);
	world->TraverseVobTree(vobCallback, cur_vob);

	dlg->DestroyWindow();
	delete dlg;
	dlg=0;
	
	LVITEM item;
	item.iItem = 0;
	item.iSubItem = 0;
	item.mask = LVIF_TEXT | LVIF_PARAM;	

	CString vobDescription;
	CString vobClassName;
	CString vobName;

	zCVob* vob;
	for (int i=0;i<sourceVobList.GetNumInList();i++)
	{
		vob = sourceVobList.Get(i);
		vobClassName = vob->GetClassDef()->GetClassName_().ToChar();
		vobName = vob->GetVobName().ToChar();
		vobName.MakeLower();
		vobDescription = vobClassName + ":" + vobName;
		item.pszText = vobDescription.GetBuffer(0);		
		item.cchTextMax = vobDescription.GetLength();
		item.lParam = (LPARAM)vob;		
		if (ctrl_list_sources.InsertItem(&item)>=0)
		{
			vob->AddRef();
		};
	};	

	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Events::OnDblclkListSources(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UINT i, selectCount = ctrl_list_sources.GetSelectedCount();
	int  nItem = -1;

	if (selectCount > 0)
	{
	   for (i=0;i < selectCount;i++)
	   {
		  nItem = ctrl_list_sources.GetNextItem(nItem, LVNI_SELECTED);
		  DWORD vob_pointer_value = ctrl_list_sources.GetItemData(nItem);
		  zCVob* vob = dynamic_cast<zCVob*>((zCVob*)vob_pointer_value);
		  if (vob)
		  {
			  CMainFrame::mainframe->ObjectSelection(vob,this,FALSE);
			  CSpacerView::view->VobGoto(vob);
		  };
	   }
	}

	CSpacerView::view->SetFocus();

	*pResult = 0;
}

void spcCInfoBar_Events::OnDblclkListTargets(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UINT i, selectCount = ctrl_list_targets.GetSelectedCount();
	int  nItem = -1;
	DWORD vob_pointer_value;
	zCVob* vob = 0;

	if (selectCount > 0)
	{
	   for (i=0;i < selectCount;i++)
	   {
		  nItem = ctrl_list_targets.GetNextItem(nItem, LVNI_SELECTED);
		  vob_pointer_value = ctrl_list_targets.GetItemData(nItem);
		  vob = dynamic_cast<zCVob*>((zCVob*)vob_pointer_value);
		  if (vob)
		  {
			  CMainFrame::mainframe->ObjectSelection(vob,this,FALSE);
			  CSpacerView::view->VobGoto(vob);
		  };
	   }
	}

	CSpacerView::view->SetFocus();

	*pResult = 0;
}

void spcCInfoBar_Events::RemoveVobsFromLists()
{	
	int count;
	// int  nItem = -1;
	DWORD vob_pointer_value;
	zCVob* vob = 0;
	
	count = ctrl_list_sources.GetItemCount();
	for (int i=0;i<count;i++)
	{		
		vob_pointer_value = ctrl_list_sources.GetItemData(i);		
		vob = dynamic_cast<zCVob*>((zCVob*)vob_pointer_value);
		zRELEASE(vob);
	};

	for (i=0;i<sourceVobList.GetNumInList();i++)
	{
		vob = sourceVobList.Get(i);
		zRELEASE(vob);
	};
	sourceVobList.DeleteList();
	ctrl_list_sources.DeleteAllItems();
	ctrl_list_sources.EnableWindow(false);

	count = ctrl_list_targets.GetItemCount();
	for (i=0;i<count;i++)
	{		
		vob_pointer_value = ctrl_list_targets.GetItemData(i);
		vob = dynamic_cast<zCVob*>((zCVob*)vob_pointer_value);
		zRELEASE(vob);
	};		

	for (i=0;i<targetVobList.GetNumInList();i++)
	{
		vob = sourceVobList.Get(i);
		zRELEASE(vob);
	};
		
	targetVobList.DeleteList();
	ctrl_list_targets.DeleteAllItems();	
	ctrl_list_targets.EnableWindow(false);

}

zCList<zCVob>* spcCInfoBar_Events::GetTargetVobList(zCVob*& refVob)
{
	refVob=cur_vob;
	return &targetVobList;
}

zCList<zCVob>* spcCInfoBar_Events::GetSourceVobList(zCVob*& refVob)
{
	refVob=cur_vob;
	return &sourceVobList;
}

void spcCInfoBar_Events::SetEventSourceVob(zCVob* vob) 
{
	zRELEASE(event_sourcevob);
	event_sourcevob = vob;
	m_source_vob = "";
	if (event_sourcevob) 
	{
		event_sourcevob->AddRef();		
		m_source_vob = event_sourcevob->GetClassDef()->GetClassName_().ToChar();		
		CString vobName = event_sourcevob->GetVobName().ToChar();
		vobName.MakeLower();
		m_source_vob += ":" + vobName;
	}
	UpdateData(false);
}

void spcCInfoBar_Events::HandleVobSelect(zCVob* vob)
{
	SelectVob(vob);
};

void spcCInfoBar_Events::HandleVobInsert(zCVob* vob, zCVob* parentVob)
{

};

void spcCInfoBar_Events::HandleVobRemove(zCVob* vob)
{
	if (vob == cur_vob) HandleVobSelect(vob);
};

