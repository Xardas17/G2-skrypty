// spcCInfoBar.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCInfoBar.h"

#include "zworld.h"
#include "zobject.h"
#include "zarchiver.h"
#include "zvob.h"
#include "zbuffer.h"
#include "zcscamera.h"
#include "zccsplayer.h"
#include "zccsmanager.h"
#include "zsession.h"

#ifdef COMPILING_GOTHIC
	#include "omobinter.h"
	#include "oitem.h"
	#include "onpc.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Info-Class

spcCVobItem::spcCVobItem(zCVob* v)
{
	vob = v;
	parent = 0;
	if (v->globalVobTreeNode->GetParent()) parent = v->globalVobTreeNode->GetParent()->GetData();
	
};

class spcCVobRestoreCallback : public zCVobCallback
{
protected:
	zCArchiver*		archiver;
	spcCVobList*	list;
	zCWorld*		world;
	int				listPos;
public:
	spcCVobRestoreCallback() { listPos = 0;archiver=0;list=0;	};
	virtual void Init(zCWorld* w, zCArchiver* a, spcCVobList* l)	{ world = w;archiver = a; list=l; listPos=0; };
	virtual void HandleVob(zCVob* vob, void *callbackData)
	{
		if (dynamic_cast<zCCSCamera*>(vob)) return;
		if (!archiver) return;
		if (!world) return;
		if (!list) return;
				
		zBOOL found = FALSE;
		
		spcCVobList* listnode = list;
		while (!found && listnode)
		{
			found = listnode->GetData() && (listnode->GetData()->vob == vob);
			listnode = listnode->GetNextInList();
		};
		
		if (!found)
		{
			zERR_MESSAGE(6,0,"B: SPC: Restore ... ["+vob->GetClassDef()->GetClassName_()+"] has been inserted. Removing ...");
			vob->RemoveVobFromWorld();			
		};

	};
};


void spcCInfo::Store(zCArchiver* archiver, zCTree<zCVob>* vobNode)
{       
	if (!activeWorld) return;	

    if (!vobNode) vobNode = &(activeWorld->globalVobTree);
    
    zCVob* vob = vobNode->GetData();
	if (vob) StoreVob(archiver,vob);	

    zCTree<zCVob> *newchild;
    zCTree<zCVob> *child = vobNode->GetFirstChild();                
    while (child) 
    {
            newchild = child->GetNextChild();
            Store(archiver, child);
            child = newchild;
    };        
}


void spcCInfo::StoreVobStates()
{
	if (!activeWorld) return;
			
	ClearVobStates();

	storedVobBuffer = new zCBuffer(1024*4);	 // 4 MB

	zERR_MESSAGE(6,zERR_BEGIN,"B: SPC: Storing dynamic data ...");
	
	zCArchiver* vobArchiver = zarcFactory.CreateArchiverWrite(storedVobBuffer,zARC_MODE_BINARY);	
	
	Store(vobArchiver,0);

	zCWayNet* waynet = activeWorld->GetWayNet();
	vobArchiver->WriteObject((zCObject*)waynet);	

	vobArchiver->Close();	
	zRELEASE(vobArchiver);

	zERR_MESSAGE(6,zERR_END,"");
}


void spcCInfo::StoreVob(zCArchiver* arc, zCVob* vob)
{	
	if (dynamic_cast<zCCSCamera*>(vob)) return;

	spcCVobItem* item = new spcCVobItem(vob);
	//storedVobList.InsertFront(item);
	curStoredVobList->Insert(item);
	curStoredVobList = curStoredVobList->GetNextInList();

	vob->AddRef();	

	// Vob in den Archiver legen
	arc->WriteObject(vob);	

	zERR_MESSAGE(9,0,"B: SPC: Store: "+vob->GetClassName_()+":"+vob->GetVobName());
};


void spcCInfo::RestoreVobStates()
{
	if (!activeWorld) return;	
	if (!storedVobBuffer) return;
	
	zERR_MESSAGE(6,zERR_BEGIN,"B: SPC: Restoring dynamic data");

	// Zuerst einmal nach neuen Vobs suchen ...
	zCArchiver* vobArchiver = zarcFactory.CreateArchiverRead(storedVobBuffer);	

		spcCVobRestoreCallback callback;
		callback.Init(activeWorld, vobArchiver, &storedVobList);				
		activeWorld->TraverseVobTree(callback,0,0);	

		// Und nu den Rest restaurieren
		spcCVobItem* item;
				
		spcCVobList* listnode = &storedVobList;
		while (listnode)
		{
			item = listnode->GetData();
			if (item) RestoreVob(vobArchiver,item->vob, item->parent);
			listnode = listnode->GetNextInList();
		};		

	zCWayNet* waynet = activeWorld->GetWayNet();
	vobArchiver->ReadObject((zCObject*)waynet);	

	vobArchiver->Close();	
	zRELEASE(vobArchiver);

	zERR_MESSAGE(6,zERR_END,"");
	
}

void spcCInfo::RestoreVob(zCArchiver* arc, zCVob* vob, zCVob* parent)
{	
	if (dynamic_cast<zCCSCamera*>(vob)) return;

	zERR_MESSAGE(9,0,"B: SPC: Restore: "+vob->GetClassName_()+":"+vob->GetVobName());

	zCVob* refVob			= activeWorld->SearchVob(vob);
	zCVob* refParent = 0;
	zCVob* currentParent = 0;
	if (refVob)
	{
		refParent		= (parent!=0) ? activeWorld->SearchVob(parent) : 0;
		currentParent   =  (refVob->globalVobTreeNode && refVob->globalVobTreeNode->GetParent() ? refVob->globalVobTreeNode->GetParent()->GetData() : 0);
	}
				
	// Kein refVob gefunden oder refVob nicht in Welt
	if (!refVob || (refVob->GetHomeWorld()==0)) 
	{					
		zERR_MESSAGE(6,0,"B: SPC: Restore ... ["+vob->GetClassDef()->GetClassName_()+"] has been removed. Recreating ...");				

		if (parent) activeWorld->AddVobAsChild(vob,parent);
		else		activeWorld->AddVob(vob);

		refVob = vob;				
	}
	
	else // Parent-Check (evtl. vorhandener Parent wurde vorher restauriert)
	{				
		if (parent != currentParent) 
		{
			zERR_MESSAGE(6,0,"B: SPC: Restore ... ["+refVob->GetClassDef()->GetClassName_()+"] has wrong parent. Moving ...");
			activeWorld->MoveVobSubtreeTo(refVob, refParent);
		}						
	}
	
	// Update des Vobs	
	if (refVob != positionVob) 
	{		
		arc->ReadObject(refVob);
		if (dynamic_cast<zCCSCamera*>(refVob)) static_cast<zCCSCamera*>(refVob)->Refresh();
	}

	else arc->ReadObject();
};



void spcCInfo::ClearVobStates()
{		
	spcCVobItem* item;
	spcCVobList* listnode = &storedVobList;	
	spcCVobList* listnode2;
	while (listnode)	
	{		
		listnode2 = listnode->GetNextInList();		
		item = listnode->GetData();	
		if (item)
		{
			zRELEASE(item->vob);
			storedVobList.Remove(item);
			delete item;item=0;
		}
		listnode = listnode2;
	}
	delete storedVobBuffer;
	storedVobBuffer=0;

	curStoredVobList = &storedVobList;
}



spcCInfo::spcCInfo()
{
	activeWorld		= 0;
	selectedObject	= 0;	
	positionVob		= 0;		
	storedVobBuffer	= 0;
	session			= 0;
	curStoredVobList = &storedVobList;
};

spcCInfo::~spcCInfo()
{
	activeWorld		= 0;
	selectedObject	= 0;	
	positionVob		= 0;		
	
	ClearVobStates();
};
///
// SETTING ...
///

void spcCInfo::SetSession(zCSession* _session)
{
	session = _session;
};

void spcCInfo::SetSelectedObject(zCObject *obj)
{
	zRELEASE(selectedObject);
	selectedObject = obj;
	if (selectedObject) selectedObject->AddRef();

}

void spcCInfo::SetActiveWorld(zCWorld *world)
{
	// vobListe leeren
	ClearVobStates();
	activeWorld = world;		
}

void spcCInfo::SetPositionVob(zCVob* vob)
{
	if (positionVob)
	{
		zRELEASE(positionVob);
	};
	positionVob = vob;
	if (positionVob)
	{
		positionVob->AddRef();
	};
};


///
// Getting ...
///


zCObject* spcCInfo::GetSelectedObject()
{	
	return selectedObject;
}

zCVob* spcCInfo::GetSelectedVob()
{
	return dynamic_cast<zCVob*>(selectedObject);
}

zCWorld* spcCInfo::GetActiveWorld()
{
	return activeWorld;
}

zBOOL spcCInfo::GetCurrentPosVector(zPOINT3& pos)
{
	if (!positionVob) return FALSE;
	pos = positionVob->GetPositionWorld();
	return TRUE;
}

zBOOL spcCInfo::GetCurrentAtVector(zPOINT3& dir)
{
	if (!positionVob) return FALSE;
	dir = positionVob->GetAtVectorWorld();
	return TRUE;
}


zCCSManager* spcCInfo::GetCurrentCutsceneManager()
{
	// zCCSPlayer* csplayer = GetCurrentCutscenePlayer();
	// return (csplayer) ? csplayer->GetOwnerManager() : 0;
	if (!session) return 0;
	return session->GetCutsceneManager();
};

zCCSPlayer*	spcCInfo::GetCurrentCutscenePlayer()
{		
	return (GetActiveWorld()) ? GetActiveWorld()->GetCutscenePlayer() : 0;	
};





/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCInfoBar 



spcCInfoBar::spcCInfoBar(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInfoBar::IDD, pParent), spcCInfo()

{
	//{{AFX_DATA_INIT(spcCInfoBar)
	m_daytime = 0;	
	m_holdtime = FALSE;
	m_info = _T("");
	m_state = _T("empty");
	//}}AFX_DATA_INIT
}

spcCInfoBar::~spcCInfoBar()
{
};


void spcCInfoBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInfoBar)
	DDX_Control(pDX, IDC_STORE_PROGRESS, ctrl_progress);
	DDX_Control(pDX, IDC_WORLD_STORE_VOBSTATES, ctrl_store);
	DDX_Control(pDX, IDC_WORLD_RESTORE_VOBSTATES, ctrl_restore);
	DDX_Control(pDX, IDC_DAYTIME, ctrl_daytime);
	DDX_DateTimeCtrl(pDX, IDC_DAYTIME, m_daytime);	
	DDX_Check(pDX, IDC_HOLD_TIME, m_holdtime);
	DDX_Text(pDX, IDC_INFO, m_info);
	DDX_Text(pDX, IDC_STATE, m_state);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCInfoBar, CDialog)
	//{{AFX_MSG_MAP(spcCInfoBar)
	ON_BN_CLICKED(IDC_WORLD_STORE_VOBSTATES, OnWorldStoreVobstates)
	ON_BN_CLICKED(IDC_WORLD_RESTORE_VOBSTATES, OnWorldRestoreVobstates)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCInfoBar 

BOOL spcCInfoBar::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ctrl_daytime.SetFormat("HH:mm");
	ctrl_daytime.EnableWindow(activeWorld!=0);
	ctrl_restore.EnableWindow(storedVobList.GetNumInList()>0);
	ctrl_store.EnableWindow(activeWorld!=0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

bool spcCInfoBar::UpdateTime(int &_hour, int &_min)
{		
	UpdateData(true);
	if (m_holdtime)
	{				
		_hour = m_daytime.GetHour();
		_min = m_daytime.GetMinute();
		return true;
	}
	else
	{
		if (_hour>23) { _hour=23; _min=59;}
		if (_min>59) _min=59;	
		CTime time = CTime( 1972, 7, 5, _hour, _min, 0);
		ctrl_daytime.SetTime(&time);
	
		return false;
	};	
}


// UPDATING ...

void spcCInfoBar::UpdateInfo()
{	
	ctrl_daytime.EnableWindow(activeWorld!=0);
	ctrl_restore.EnableWindow(storedVobList.GetNumInList()>0);
	ctrl_store.EnableWindow(activeWorld!=0);
	
	m_info = "";
	if (selectedObject)	
	{
		m_info += "Selected Object: \r\n";
		m_info += "- class: "+CString(selectedObject->GetClassDef()->GetClassName_().ToChar())+" : "+CString(selectedObject->GetClassDef()->GetBaseClassName().ToChar())+"\r\n";
		m_info += "- refCtr: "+CString(zSTRING(selectedObject->GetRefCtr()).ToChar())+"\r\n";
		m_info += "- objectname: "+CString(selectedObject->GetObjectName().ToChar())+"\r\n";						
		
		zCVob* vob = GetSelectedVob();
		if (vob)
		{
			m_info += "- vobName: "+CString(vob->GetVobName().ToChar())+"\r\n";
		};		

#ifdef COMPILING_GOTHIC
		zSTRING schemeName;
		if (dynamic_cast<oCItem*>(vob)) schemeName = dynamic_cast<oCItem*>(vob)->GetSchemeName();
		if (dynamic_cast<oCMOB*>(vob)) schemeName = dynamic_cast<oCMOB*>(vob)->GetScemeName();		
		if (!schemeName.IsEmpty()) m_info += "- schemeName: "+CString(schemeName.ToChar())+"\r\n";

		if (dynamic_cast<oCNpc*>(vob)) 
		{
			zSTRING npcName = dynamic_cast<oCNpc*>(vob)->GetName()+" ("+dynamic_cast<oCNpc*>(vob)->GetName(TRUE)+")";
			m_info += "- npcName: "+CString(npcName.ToChar());
		}
#endif
	};
		
	UpdateData(false);
}


void spcCInfoBar::OnWorldStoreVobstates() 
{	
	StoreVobStates();
}

void spcCInfoBar::OnWorldRestoreVobstates() 
{
	RestoreVobStates();
}

void spcCInfoBar::StoreVobStates()
{
	m_state = "working ...";
	UpdateData(false);
	UpdateWindow();

	if (!activeWorld) return;
	int num = activeWorld->globalVobTree.CountNodes();
	ctrl_progress.SetRange(0,num);
	ctrl_progress.SetStep(1);	
	spcCInfo::StoreVobStates();	
	ctrl_progress.SetPos(num);
	UpdateInfo();

	m_state = "stored";
	UpdateData(false);
	UpdateWindow();
}


void spcCInfoBar::RestoreVobStates()
{
	m_state = "working ...";
	UpdateData(false);
	UpdateWindow();

	ctrl_progress.SetStep(1);	
	ctrl_progress.SetRange(0,storedVobList.GetNumInList());
	ctrl_progress.SetPos(0);
	spcCInfo::RestoreVobStates();	
	ctrl_progress.SetPos(storedVobList.GetNumInList());
	UpdateInfo();

	m_state = "stored";
	UpdateData(false);
	UpdateWindow();
}

void spcCInfoBar::SetSelectedObject(zCObject *obj)
{
	spcCInfo::SetSelectedObject(obj);
	UpdateInfo();
}

void spcCInfoBar::SetActiveWorld(zCWorld *world)

{	
	spcCInfo::SetActiveWorld(world);
	UpdateInfo();	

	ctrl_progress.SetPos(0);
	m_state = "empty";
	UpdateData(false);
	UpdateWindow();
}


void spcCInfoBar::StoreVob(zCArchiver* arc, zCVob* vob)
{
	ctrl_progress.StepIt();
	spcCInfo::StoreVob(arc, vob);
	
};

void spcCInfoBar::RestoreVob(zCArchiver* arc, zCVob* vob, zCVob* parent)
{
	ctrl_progress.StepIt();
	spcCInfo::RestoreVob(arc, vob, parent);

};

void spcCInfoBar::OnCancel() 
{
	ShowWindow(SW_MINIMIZE);
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	// CDialog::OnCancel();
}
