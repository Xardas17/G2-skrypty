// spcCInfoBarVobsPlus.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "SpacerView.h"
#include "SpacerDoc.h"
#include "MainFrm.h"

#include "zoption.h"

#include "z3d.h"
#include "zEventMan.h"
#include "zVob.h"
#include "zWorld.h"
#include "zdisk.h"

#include "spcCInputDialog.h"
#include "spcCInfoBarVobsPlus.h"

#ifdef _DEBUG
////#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCInfoBar_VobsPlus 


spcCInfoBar_VobsPlus::spcCInfoBar_VobsPlus(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInfoBar_VobsPlus::IDD, pParent), cur_vob(0), 
		presets(0), selected(-1), presetEditMode(false), editPreset(0)
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Constructing Instance of VobsPlusPage...");

	//{{AFX_DATA_INIT(spcCInfoBar_VobsPlus)
	m_classname = _T("");
	m_vobname = _T("");
	m_visualname = _T("");
	m_sel_cd_dyn = FALSE;
	m_sel_cd_stat = FALSE;
	m_sel_staticvob = FALSE;
	//m_editbbox = FALSE;
	m_evtrigger = FALSE;
	m_evuntrigger = FALSE;
	m_enable_presets = FALSE;
	//}}AFX_DATA_INIT

	zERR_MESSAGE(7,zERR_END,"");
}


void spcCInfoBar_VobsPlus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInfoBar_VobsPlus)
	DDX_Control(pDX, IDC_EVENTRESTORE, ctrl_restore);
	DDX_Control(pDX, IDC_TESTEVENT, ctrl_testevent);
	DDX_Control(pDX, IDC_SENDEVENT, ctrl_sendevent);
	DDX_Control(pDX, IDC_PRESET_RELOAD_T, ctrl_presetreload);
	DDX_Control(pDX, IDC_PRESET_REMOVE_T, ctrl_presetremove);
	DDX_Control(pDX, IDC_PRESET_FROM_CURRENT_T, ctrl_from_current);
	DDX_Control(pDX, IDC_PRESET_TO_CURRENT_T, ctrl_to_current);
	DDX_Control(pDX, IDC_PRESET_LIST, ctrl_presetlist);
	//DDX_Control(pDX, IDC_EDITBBOX, ctrl_editbbox);
	DDX_Control(pDX, IDC_VISUALNAME, ctrl_visualname);
	DDX_Text(pDX, IDC_CLASSNAME, m_classname);
	DDX_Text(pDX, IDC_VOBNAME, m_vobname);
	DDX_CBString(pDX, IDC_VISUALNAME, m_visualname);
	DDX_Check(pDX, IDC_SEL_CD_DYN, m_sel_cd_dyn);
	DDX_Check(pDX, IDC_SEL_CD_STAT, m_sel_cd_stat);
	DDX_Check(pDX, IDC_SEL_STATICVOB, m_sel_staticvob);
	//DDX_Check(pDX, IDC_EDITBBOX, m_editbbox);
	DDX_Check(pDX, IDC_EVTRIGER, m_evtrigger);
	DDX_Check(pDX, IDC_EVUNTRIGER, m_evuntrigger);
	DDX_Check(pDX, IDC_ENABLE_PRESETS, m_enable_presets);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCInfoBar_VobsPlus, CDialog)
	//{{AFX_MSG_MAP(spcCInfoBar_VobsPlus)
	ON_EN_CHANGE(IDC_VOBNAME, OnChangeVobname)
	ON_CBN_SELCHANGE(IDC_VISUALNAME, OnSelchangeVisualname)
	ON_BN_CLICKED(IDC_VISUALBUTTON, OnVisualbutton)
	ON_BN_CLICKED(IDC_SEL_CD_DYN, OnSelCdDyn)
	ON_BN_CLICKED(IDC_SEL_CD_STAT, OnSelCdStat)
	ON_BN_CLICKED(IDC_SEL_STATICVOB, OnSelStaticvob)
	//ON_BN_CLICKED(IDC_EDITBBOX, OnEditbbox)
	ON_LBN_SELCHANGE(IDC_PRESET_LIST, OnSelchangePresetList)
	ON_BN_CLICKED(IDC_PRESET_FROM_CURRENT_T, OnPresetFromCurrentT)
	ON_BN_CLICKED(IDC_PRESET_TO_CURRENT_T, OnPresetToCurrentT)
	ON_BN_CLICKED(IDC_PRESET_REMOVE_T, OnPresetRemoveT)
	ON_BN_CLICKED(IDC_PRESET_RELOAD_T, OnPresetReloadT)
	ON_BN_CLICKED(IDC_SENDEVENT, OnSendevent)
	ON_BN_CLICKED(IDC_TESTEVENT, OnTestevent)
	ON_BN_CLICKED(IDC_EVENTRESTORE, OnEventrestore)
	ON_BN_CLICKED(IDC_ENABLE_PRESETS, OnEnablePresets)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// eigene Methoden

void spcCInfoBar_VobsPlus::SelectVob(zCVob* pickedVob)
{
	if (pickedVob)
	{
		cur_vob = pickedVob;
		m_vobname = cur_vob->GetVobName().ToChar();
		m_classname = cur_vob->GetClassName_().ToChar();
		zCVisual* vis = cur_vob->GetVisual();
		if (vis)
			m_visualname = vis->GetVisualName().ToChar();
		else m_visualname = "kein Visual";
		// collFlags
		m_sel_cd_dyn = cur_vob->GetCollDetDyn();
		m_sel_cd_stat = cur_vob->GetCollDetStat();
		m_sel_staticvob = cur_vob->GetStaticVob();

		ctrl_from_current.EnableWindow(true);
		ctrl_to_current.EnableWindow(false /*selected>=0*/);
		/*
		ctrl_editbbox.EnableWindow(true);
		
		if (m_editbbox)
		{
			int old_bbox_mode = m_editbbox;
			m_editbbox = (NULL != dynamic_cast<spcCDragVob*>(pickedVob));
			if (old_bbox_mode != m_editbbox) 
			{
				UpdateData(false);
				OnEditbbox();
			};
		}
		*/
		ctrl_testevent.EnableWindow();
		m_evtrigger=true;
		m_evuntrigger=false;
		presetEditMode=false;

		UpdateData(false);
	}
	else
	{
		if (presetEditMode) return;

		cur_vob=NULL;
		m_vobname = "";
		m_classname = "";
		m_visualname = "";
		m_sel_cd_dyn = FALSE;
		m_sel_cd_stat = FALSE;
		m_sel_staticvob = FALSE;
		/*
		if (dragBottom && dragTop) 
		{
			dragBottom->HideYourself();
			dragTop->HideYourself();
		}
		*/
		ctrl_from_current.EnableWindow(false);
		ctrl_to_current.EnableWindow(false /*selected>=0*/);
		/*
		if (m_editbbox)
		{
			int old_bbox_mode = m_editbbox;
			m_editbbox = (NULL != dynamic_cast<spcCDragVob*>(pickedVob));
			if (old_bbox_mode != m_editbbox) 
			{
				UpdateData(false);
				OnEditbbox();
			};
		}
		*/
		ctrl_testevent.EnableWindow(false);
		ctrl_sendevent.EnableWindow(false);
		ctrl_restore.EnableWindow(false);
		UpdateData(false);
	}
}
zCVob* spcCInfoBar_VobsPlus::InsertVob(const zPOINT3& pos, const zPOINT3& dir, zCVob* vob)
{
	if (selected<0 || editPreset==0)	return 0;
	if (!CSpacerDoc::doc->GetWorld())	return 0;

	zCVob* newvob = dynamic_cast<zCVob*>(editPreset->CreateCopy());
	
	if (vob)	CSpacerDoc::doc->GetWorld()->AddVobAsChild(newvob,vob);
	else		CSpacerDoc::doc->GetWorld()->AddVob(newvob);	

	zBOOL saveStat = newvob->GetCollDetStat();
	newvob->SetCollDetStat(FALSE); // to be able to move the trigger
	zBOOL saveDyn = newvob->GetCollDetDyn();
	newvob->SetCollDetDyn(FALSE);
	newvob->SetPositionWorld(pos+dir*200);
	newvob->SetHeadingWorld(pos+dir*400);
	newvob->SetCollDetStat(saveStat);
	newvob->SetCollDetDyn(saveDyn);
	newvob->SetVobPresetName((*presets)[selected]->presetName);
	return newvob;
}

/*
void spcCInfoBar_VobsPlus::UpdateDragPosition(zCVob* dragVob)
{
	if (!cur_vob) return;
	if (dragVob==NULL) return;
	zTBBox3D bbox;// = cur_vob->GetBBox3DWorld();
	//if (dynamic_cast<spcCDragVob*>(dragVob)->dragType==spcCDragVob::dragBOT)
		bbox.mins=dragBottom->GetPositionWorld();
		bbox.maxs=dragTop->GetPositionWorld();
	// evtl korrectur
	for (int d=0; d<3; d++)
	{
		if (bbox.mins[d]>bbox.maxs[d])
		{
			zREAL tmp = bbox.mins[d];
			bbox.mins[d]=bbox.maxs[d];
			bbox.maxs[d]=tmp;
		}
	}
	cur_vob->SetDrawBBox3D(FALSE);
	cur_vob->SetBBox3DWorld(bbox);
	cur_vob->SetDrawBBox3D(TRUE);
}
*/

void spcCInfoBar_VobsPlus::OnChangeVisual(CString & visName)
{
if (presetEditMode)
{
	if (!editPreset) return;
	editPreset->SetVisual(zSTRING(visName.GetBuffer(0)));
	presets->SetDirty();
} else
{
	if (!cur_vob) return;
	cur_vob->SetVisual(zSTRING(visName.GetBuffer(0)));
	cur_vob->SetVobPresetName(zSTRING(""));
}
	m_visualname = visName;
	UpdateData(false);
}

void spcCInfoBar_VobsPlus::InitData()
{
	CSpacerDoc* pDoc = CSpacerView::view->GetDocument();
	ASSERT_VALID(pDoc);
	
	//dragBottom = 0;
	//dragTop = 0;

	if (!pDoc->GetWorld()) return;

	/*
	dragBottom = new spcCDragVob(spcCDragVob::dragBOT);	
	pDoc->GetWorld()->AddVob(dragBottom);

	dragTop = new spcCDragVob(spcCDragVob::dragTOP);
	pDoc->GetWorld()->AddVob(dragTop);
	*/

	if (presets==0)
		presets = CMainFrame::mainframe->presetLib.GetNewView(zSTRING("zCZone"));

	UpdatePresetList();
}

void spcCInfoBar_VobsPlus::PreClose()
{
	//dragBottom = 0;
	//dragTop = 0;

}
void spcCInfoBar_VobsPlus::UpdatePresetList()
{
	ctrl_presetlist.ResetContent();
	selected=0;
	presetEditMode=false;
	editPreset=NULL;
	if (presets->GetNumInList()<=0) return;
	for (int z=0; z<presets->GetNumInList(); z++)
	{
		//zCObjPreset = (*presets)[z];
		ctrl_presetlist.AddString((*presets)[z]->presetName.ToChar());
	}
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCInfoBar_VobsPlus 

void spcCInfoBar_VobsPlus::OnOK() 
{
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
	// prevent that ENTER will close the dialog
	// CDialog::OnOK();
}

void spcCInfoBar_VobsPlus::OnChangeVobname() 
{
	UpdateData(TRUE);
	if (presetEditMode)
	{
		if (editPreset)
			editPreset->SetVobName(m_vobname.GetBuffer(0));
		presets->SetDirty();
	} else
	{
		if (cur_vob) {
			cur_vob->SetVobName(m_vobname.GetBuffer(0));
			cur_vob->SetVobPresetName(zSTRING(""));
			// change name in voblist
			CMainFrame::mainframe->HandleObjChange(cur_vob);
		}
	}
}

void spcCInfoBar_VobsPlus::OnSelchangeVisualname() 
{
	OnChangeVisual(m_visualname);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_VobsPlus::OnVisualbutton() 
{
	CString filter = "Visual-Files (mds;msh;3ds;asc)|*.mds;*.msh;*.3ds;*.asc|3DS-File (*.3ds)|*.3ds|Textur (*.tga)|*.tga|Model (*.msh)|*.msh|Model (*.mds)|*.mds|ASC-Files|*.asc|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE,"3ds","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);
	
	zoptions->ChangeDir(DIR_DATA);
	zFILE::DirectFileAccess(true);
	int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)	{				
		OnChangeVisual(dlg.GetFileName());
	}

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_VobsPlus::OnSelCdDyn() 
{
	UpdateData(TRUE);
	if (presetEditMode){
		if (editPreset)
			editPreset->SetCollDetDyn(m_sel_cd_dyn);
		presets->SetDirty();
	}
	else{
		if (cur_vob) {cur_vob->SetCollDetDyn(m_sel_cd_dyn);
		cur_vob->SetVobPresetName(zSTRING(""));}
	}

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_VobsPlus::OnSelCdStat() 
{
	UpdateData(TRUE);
	if (presetEditMode){
		if (editPreset)
			editPreset->SetCollDetStat(m_sel_cd_stat);
		presets->SetDirty();
	}
	else{
		if (cur_vob) {cur_vob->SetCollDetStat(m_sel_cd_stat);
		cur_vob->SetVobPresetName(zSTRING(""));}
	}
	
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_VobsPlus::OnSelStaticvob() 
{
	UpdateData(TRUE);
	if (presetEditMode){
		if (editPreset)
			editPreset->SetStaticVob(m_sel_staticvob);
		presets->SetDirty();
	}
	else{
		if (cur_vob) {cur_vob->SetStaticVob(m_sel_staticvob);
		cur_vob->SetVobPresetName(zSTRING(""));}
	}

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

BOOL spcCInfoBar_VobsPlus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

/*
void spcCInfoBar_VobsPlus::OnEditbbox() 
{
	if(cur_vob==0) return;
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

void spcCInfoBar_VobsPlus::OnSelchangePresetList() 
{
	int index = ctrl_presetlist.GetCurSel();
	if (index==CB_ERR) selected =-1;
	
	if (index>=0)
	{
		CString s;
		ctrl_presetlist.GetText(index,s);
		int z=0;
		zSTRING search(s.GetBuffer(0));
		while (z<presets->GetNumInList() && 
			(*presets)[z]->presetName!=search)
			z++;
		selected=z;  // kann normalerweise nicht _NICHT gefunden sein!!!
		editPreset=dynamic_cast<zCVob*>((*presets)[z]->obj);
		m_vobname = editPreset->GetVobName().ToChar();
		m_classname = editPreset->GetClassName_().ToChar();
		zCVisual* vis = editPreset->GetVisual();
		if (vis)
			m_visualname = vis->GetVisualName().ToChar();
		else m_visualname = "kein Visual";
		// collFlags
		m_sel_cd_dyn = editPreset->GetCollDetDyn();
		m_sel_cd_stat = editPreset->GetCollDetStat();
		m_sel_staticvob = editPreset->GetStaticVob();
		
		ctrl_from_current.EnableWindow(false);
		ctrl_to_current.EnableWindow(true);
		//ctrl_editbbox.EnableWindow(false);
		
		UpdateData(false);
		presetEditMode=true;
	}
	else presetEditMode=false;

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_VobsPlus::OnPresetFromCurrentT() 
{
	if (presetEditMode) return;
	if (cur_vob==0) return;
	if (!dynamic_cast<zCZone*>(cur_vob)) return;
	::SetCursor(spcConfig.MouseWait);
	presets->AddPreset(cur_vob,(zSTRING)cur_vob->GetVobName());
	cur_vob->SetVobPresetName((zSTRING)cur_vob->GetVobName());
	UpdatePresetList();
	::SetCursor(spcConfig.MouseArrow);
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_VobsPlus::OnPresetToCurrentT() 
{
	// TODO: 
}

void spcCInfoBar_VobsPlus::OnPresetRemoveT() 
{
	if (presetEditMode)
	{
		presets->RemovePreset(selected);
		UpdatePresetList();
	}
}

void spcCInfoBar_VobsPlus::OnPresetReloadT() 
{
	// TODO: 	
}

void spcCInfoBar_VobsPlus::OnSendevent() 
{
	// send
	if (!cur_vob) return;
	UpdateData(true);
	if (m_evtrigger) {
		cur_vob->GetEventManager()->OnTrigger(0,0);
		m_evuntrigger=true;
		m_evtrigger=false;
	} else {
		cur_vob->GetEventManager()->OnUntrigger(0,0);
		m_evtrigger=true;
		m_evuntrigger=false;
	}
	UpdateData(false);
}

void spcCInfoBar_VobsPlus::OnTestevent() 
{
	// save world in temp-file
	CSpacerDoc* pDoc = CSpacerView::view->GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnQuickSave();
	ctrl_sendevent.EnableWindow();
	ctrl_restore.EnableWindow();
}

void spcCInfoBar_VobsPlus::OnEventrestore() 
{
	CSpacerDoc* pDoc = CSpacerView::view->GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnQuickOpen();

	m_evtrigger=true;
	m_evuntrigger=false;
}

void spcCInfoBar_VobsPlus::OnEnablePresets() 
{
	UpdateData(TRUE);		
	if (!m_enable_presets) m_enable_presets = TRUE; // nur das Einschalten erlauben
	else
	{
		// Presets muessen nun geladen werden
		// ...
	};	
	UpdateData(FALSE);	
}


void spcCInfoBar_VobsPlus::HandleVobSelect(zCVob* vob)
{
};

void spcCInfoBar_VobsPlus::HandleVobInsert(zCVob* vob, zCVob* parentVob)
{
};


void spcCInfoBar_VobsPlus::HandleVobRemove(zCVob* vob)
{
};


