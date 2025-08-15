// spcCWorldAnalyseDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "SpacerView.h"
#include "SpacerDoc.h"
#include "spcCWorldAnalyseDlg.h"
#include "spcCInputDialog.h"

#ifdef _DEBUG
// #define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Zerror.h"
#include "zvob.h"
#include "zvobmisc.h"
#include "zwaynet.h"
#include "zvisual.h"
#include "zdisk.h"

#ifdef COMPILING_GOTHIC
#include "omobinter.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCWorldAnalyseDlg 


spcCWorldAnalyseDlg::spcCWorldAnalyseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCWorldAnalyseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCWorldAnalyseDlg)	
	//}}AFX_DATA_INIT
	world=0;
}


void spcCWorldAnalyseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCWorldAnalyseDlg)
	DDX_Control(pDX, IDC_PROGRESS, ctrl_progress);
	DDX_Control(pDX, IDC_LIST, ctrl_list);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCWorldAnalyseDlg, CDialog)
	//{{AFX_MSG_MAP(spcCWorldAnalyseDlg)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_BN_CLICKED(IDC_FIX, OnFix)
	ON_BN_CLICKED(IDC_GOTO_VOB, OnGotoVob)
	ON_BN_CLICKED(IDC_ANALYSE, OnAnalyse)
	ON_BN_CLICKED(IDC_TIDY_VOBS, OnTidyVobs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCWorldAnalyseDlg 

void spcCWorldAnalyseDlg::OnSelchangeList() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}

void spcCWorldAnalyseDlg::OnDblclkList() 
{
	OnFix();
}


spcCVobAnalyseCallback::spcCVobAnalyseCallback() 
{ 
	Init(0,0);
};

spcCVobAnalyseCallback::~spcCVobAnalyseCallback() 
{ 
	vobList.DeleteListDatas();
	vobList.DeleteList();
};

void spcCVobAnalyseCallback::RemoveResult(spcTAnalysedVob* item) 
{ 
	int num = GetNumResults();
	for (int i=0;i<num;i++)	
	{
		if (GetResult(i) == item)
		{
			vobList.Remove(item);
		};
	}
};

spcTAnalysedVob* spcCVobAnalyseCallback::GetResult(int i) 
{ 
	if (i>=0 && i<vobList.GetNumInList()) 
		return vobList.Get(i); 
	else 
		return 0; 
};


int	spcCVobAnalyseCallback::GetNumResults()	
{ 
	return vobList.GetNumInList(); 
};	

	
void spcCVobAnalyseCallback::Init(zCWorld* w, CProgressCtrl* progress)
{ 
	world				= w;
	ctrl_progress		= progress;
	num_vobs			= 0;	// vob-counter
	num_vobs_with_names	= 0;	// vobs with unexpected names
	size_of_vob			= 0;	// size of all vobs
	size_of_vobnames	= 0;	// size of all vobnames
	length_of_vobnames	= 0;	// length of all vobnames
	vobList.DeleteListDatas();
	vobList.DeleteList();
};

void spcCVobAnalyseCallback::InsertInfo(zSTRING msg)
{
	spcTAnalysedVob* item = new spcTAnalysedVob(0);
	item->type = spcTAnalysedVob::INFO;
	item->info = "_ Info: "+msg;
	vobList.Insert(item);
};

void spcCVobAnalyseCallback::InsertWarning(zSTRING msg)
{
	spcTAnalysedVob* item = new spcTAnalysedVob(0);
	item->type = spcTAnalysedVob::INFO;
	item->info = "0 Warning: "+msg;
	vobList.Insert(item);
};

void spcCVobAnalyseCallback::HandleVob(zCVob* vob, void *callbackData)
{			
	// Visual analysieren
	zSTRING visualName;
	if (vob->GetVisual()) visualName= vob->GetVisual()->GetVisualName();	

	zSTRING vobDescr = vob->GetClassName_()+":"+vob->GetVobName();
	if (dynamic_cast<zCVobLevelCompo*>(vob) && visualName.IsEmpty())
	{
		spcTAnalysedVob* item = new spcTAnalysedVob(vob);
		item->type = spcTAnalysedVob::NO_VISUAL;
		item->info = "2: No visual for \"" + vobDescr + "\". Use [FIX] to select one.";
		vobList.Insert(item);
	}		
	else if (!visualName.IsEmpty() && visualName[0]=='#')
	{
		spcTAnalysedVob* item = new spcTAnalysedVob(vob);
		item->type = spcTAnalysedVob::BAD_VISUAL;
		item->info = "1: Bad visual \""+visualName+"\" for \"" + vobDescr+"\". Use [FIX] to select another.";
		vobList.Insert(item);
	}		
	// Folgende Klassen benötigen einen eindeutigen VobNamen
	if (
		dynamic_cast<zCVobWaypoint*>(vob) ||
		dynamic_cast<zCVobSpot*>(vob)
		)
	{		
		if (vob->GetVobName().IsEmpty())
		{
			spcTAnalysedVob* item = new spcTAnalysedVob(vob);
			item->type = spcTAnalysedVob::NO_DISTINCT_VOBNAME;
			item->info = "3: Vobname for \"" + vobDescr + "\" expected. Use [FIX] to type one.";
			vobList.Insert(item);		
		}
		else
		{
			zCArray<zCVob*> resultList;
			world->SearchVobListByName(vob->GetVobName(),resultList);
			if (resultList.GetNumInList()>1)
			{
				spcTAnalysedVob* item = new spcTAnalysedVob(vob);
				item->type = spcTAnalysedVob::NO_DISTINCT_VOBNAME;
				item->info = "3: Distinct vobname expected for \""+vobDescr+"\". Use [FIX] to type another name.";
				vobList.Insert(item);
			}

			zCVobWaypoint* wpvob = dynamic_cast<zCVobWaypoint*>(vob);
			if (wpvob)
			{
				zCWayNet* waynet = world->GetWayNet();
				if (waynet)
				{
					zCWaypoint* wp = waynet->SearchWaypoint(wpvob);
					if (!wp)
					{
						spcTAnalysedVob* item = new spcTAnalysedVob(vob);
						item->type = spcTAnalysedVob::NO_WAYPOINT_CONNECTED;
						item->info = "1: Waypoint-Vob \"" + vobDescr + "\" is not connected to a waypoint. Use [FIX] to remove it.";
						vobList.Insert(item);
					};
				};
			};
		};		
	};

	// Folgende Klassen benötigen keinen VobNamen
	if (vob->GetClassName_()==zCVob::GetStaticClassDef()->GetClassName_())
	{		
		if (!vob->GetVobName().IsEmpty() && vob->GetVobName() != VOBNAME_SPACER_CAMERA)
		{			
			num_vobs_with_names++;	
			/*
			spcTAnalysedVob* item = new spcTAnalysedVob(vob);
			item->type = spcTAnalysedVob::HAS_VOBNAME;
			item->info = "6: Vobname not expected for \"" + vobDescr + "\". Use [FIX] to remove it.";
			vobList.Insert(item);		
			*/
		}
	};

	// Folgende Klassen benötigen einen VobNamen
	if (
			vob->GetVobName().IsEmpty() && 
			(
				dynamic_cast<zCTrigger*>(vob)
#ifdef COMPILING_GOTHIC
				|| dynamic_cast<oCMOB*>(vob)
#endif
			)
		)
	{
		spcTAnalysedVob* item = new spcTAnalysedVob(vob);
		item->type = spcTAnalysedVob::NO_VOBNAME;
		item->info = "6: Vobname expected for \"" + vobDescr + "\". Use [FIX] to type a name.";
		vobList.Insert(item);				
	};

	num_vobs++;
	size_of_vob			+=sizeof(*vob);
	size_of_vobnames	+=sizeof(vob->GetVobName());
	length_of_vobnames	+=vob->GetVobName().Length();

	if (ctrl_progress) ctrl_progress->StepIt();
};

void spcCWorldAnalyseDlg::AnalyseWorld(zCWorld* w)
{	
	world = w;
	if (!world) return;	
	callback.Init(world);	
	tidyCallback.Init(world);	
}

BOOL spcCWorldAnalyseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (!world) return FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void spcCWorldAnalyseDlg::OnFix() 
{
	int index = ctrl_list.GetCurSel();
	if (index<0) return;

	spcTAnalysedVob* item = static_cast<spcTAnalysedVob*>(ctrl_list.GetItemDataPtr(index));
	if (!item)								return;
	if (!item->vob)							return;
	if (item->type==spcTAnalysedVob::INFO)	return;

	bool fixed=false;

	switch (item->type)
	{
	case spcTAnalysedVob::NO_VISUAL:
	case spcTAnalysedVob::BAD_VISUAL:
		{
			zCVob* vob = item->vob;
			zoptions->ChangeDir(DIR_MESHES);				

			CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ,"All Files (*.*)|*.*||");			
			zFILE::DirectFileAccess(true);
			int result = dlg.DoModal();
			zFILE::DirectFileAccess(false);

			if (result == IDOK)	
			{
				CString visualName = dlg.GetFileName();				
				vob->SetVisual(zSTRING(visualName.GetBuffer(0)));				
				fixed=true;
			}
		};
		break;
	
	case spcTAnalysedVob::NO_DISTINCT_VOBNAME:
		{
			int result;			
			zCVob* vob = item->vob;
			spcCInputDialog dlg;
			do
			{				
				result = dlg.DoModal();
				if (result==IDOK)
				{
					zSTRING name(dlg.GetUpperInput().GetBuffer(0));
					zCArray<zCVob*> resultList;
					world->SearchVobListByName(name,resultList);
					if (resultList.GetNumInList()==0) 
					{
						vob->SetVobName(name);					
						fixed=true;
					}
				}

			} while (result==IDOK && !fixed);
		};
		break;
	case spcTAnalysedVob::NO_VOBNAME:
		{
			zCVob* vob = item->vob;
			spcCInputDialog dlg;
			int result = dlg.DoModal();
			if (result==IDOK)
			{
				vob->SetVobName(dlg.GetInput().GetBuffer(0));
				fixed=true;
			}
		};
		break;

	case spcTAnalysedVob::HAS_VOBNAME:
		{
			zCVob* vob = item->vob;
			vob->SetVobName("");
			fixed=true;
		};
		break;

	case spcTAnalysedVob::MORE_THAN_ONE_INSTANCE:
	case spcTAnalysedVob::NO_WAYPOINT_CONNECTED:
		{
			zCVob* vob = item->vob;
			CSpacerDoc::doc->RemoveVob(vob);
			item->vob = 0;
			fixed=true;
		}
		break;
	};	

	if (fixed)
	{
		callback.RemoveResult(item);
		ctrl_list.DeleteString(index);								
		ctrl_list.SetCurSel(index);
	};
}

void spcCWorldAnalyseDlg::OnGotoVob() 
{
	int index = ctrl_list.GetCurSel();
	if (index<0) return;

	spcTAnalysedVob* item = static_cast<spcTAnalysedVob*>(ctrl_list.GetItemDataPtr(index));
	if (!item)			return;
	if (!item->vob)		return;

	CSpacerView::view->VobGoto(item->vob);
	CSpacerView::view->RedrawWindow();
}

void spcCWorldAnalyseDlg::OnAnalyse() 
{
	if (!world) return;
			
	//
	// Alle Vobs einzeln untersuchen
	//	

	int numVobs = world->globalVobTree.CountNodes();
	ctrl_progress.SetRange(0,numVobs);
	ctrl_progress.SetStep(1);	

	zERR_MESSAGE(4,0,"B: WA: Analysing vobs in world ...");
	callback.Init(world, &ctrl_progress);
	world->TraverseVobTree(callback);	

	//
	// Ergebnisse abfragen und weitere checks vornehmen
	//

	zERR_MESSAGE(4,0,"B: WA: Analysing resulting values ...");
	zSTRING message;


	// Anzahl der Vobs
	message = zSTRING(callback.num_vobs)+" vobs.";	
	callback.InsertInfo(message);

	// Speicherplatz und Laenge der Vobnamen
	message = "Vobnames with "+zSTRING(callback.length_of_vobnames/1024.0f,2)+" KB length need "+zSTRING(callback.size_of_vobnames/1024.0f,2)+" KB";
	callback.InsertInfo(message);

	// Unnoetige Vobnamen?
	if (callback.num_vobs_with_names>0)
	{
		message = zSTRING(callback.num_vobs_with_names)+" vobs with unexpected vobname.";
		callback.InsertWarning(message);
	}
			
	zERR_MESSAGE(4,0,"B: WA: Analysing default-vobs ...");

	// Default-FogZone?
	{
		zCArray<zCVob*> resultList;
		world->SearchVobListByClass(zCZoneZFogDefault::GetStaticClassDef(),resultList);
		if (resultList.GetNumInList()!=1) 
		{
			message = "Wrong number of Default-FogZones: "+zSTRING(resultList.GetNumInList());
			callback.InsertWarning(message);
		}
		else callback.InsertInfo("Default-FogZone found");		
	}

	// Default-VobFarPlaneZone?
	{
		zCArray<zCVob*> resultList;
		world->SearchVobListByClass(zCZoneVobFarPlaneDefault::GetStaticClassDef(),resultList);
		if (resultList.GetNumInList()!=1) 
		{
			message = "Wrong number of Default-VobFarPlaneZones: "+zSTRING(resultList.GetNumInList());
			callback.InsertWarning(message);
		}
		else callback.InsertInfo("Default-VobFarPlaneZones found");

	}

	zERR_MESSAGE(4,0,"B: WA: Finished");

	//
	// Eintragen der gefundenen Punkte in die Listbox
	//
	ctrl_list.ResetContent();
	int index;
	for (int i=0;i<callback.GetNumResults();i++)
	{
		spcTAnalysedVob* item = callback.GetResult(i);
		if (item) 
		{
			index = ctrl_list.AddString(item->info.ToChar());						
			if (index>=0) ctrl_list.SetItemDataPtr(index,item);
		};
	};
	ctrl_progress.SetPos(numVobs);

}

void spcCWorldAnalyseDlg::OnTidyVobs() 
{
	// 
	// Goldmaster?
	//

	int numVobs = world->globalVobTree.CountNodes();
	ctrl_progress.SetRange(0,numVobs);
	ctrl_progress.SetStep(1);	

	tidyCallback.Init(world, &ctrl_progress);
	world->TraverseVobTree(callback);		
}






//
// Tidy-Callback
//


spcCVobTidyCallback::spcCVobTidyCallback() 
{ 
	Init(0,0);
};

spcCVobTidyCallback::~spcCVobTidyCallback() 
{ 	
};

	
void spcCVobTidyCallback::Init(zCWorld* w, CProgressCtrl* progress)
{ 
	world				= w;
	ctrl_progress		= progress;	
};

void spcCVobTidyCallback::HandleVob(zCVob* vob, void *callbackData)
{			
	zBOOL removeVobname = FALSE;
	
	// ein zCVob?!
	if (removeVobname)
	{
		removeVobname = vob->GetClassDef()==zCVob::GetStaticClassDef();
	}
	
	if (removeVobname)
	{
		zERR_MESSAGE(5,0,"B: TIDY: Removing vobname from vob \""+vob->GetVobName());
		vob->SetObjectName("");
	};
	
	if (ctrl_progress) ctrl_progress->StepIt();
};