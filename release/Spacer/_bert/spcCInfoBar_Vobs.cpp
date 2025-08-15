// spcCInfoBar_Vobs.cpp: Implementierungsdatei
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
#include "zvobmisc.h"
#include "zdisk.h"

#include "spcCInfoBar_Vobs.h"
#include "spcCInputDialog.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCInfoBar_Vobs


spcCInfoBar_Vobs::spcCInfoBar_Vobs(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInfoBar_Vobs::IDD, pParent), cur_vob(0),
		presets(), selected(-1), presetEditMode(false), editPreset(0),
		presetClassName(), pLibExplicit(), actPView(0)
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Constructing Instance of VobsPage...");

	//{{AFX_DATA_INIT(spcCInfoBar_Vobs)
	m_classname = _T("");
	m_vobname = _T("");
	m_visualname = _T("");
	m_sel_cd_dyn = FALSE;
	m_sel_cd_stat = FALSE;
	m_sel_staticvob = FALSE;
	m_insertmode = 0;
	m_2sided = FALSE;
	m_camalign = -1;
	m_alphablend = -1;
	m_fps = 0;
	m_presetclass = -1;
	m_evtrigger = FALSE;
	m_evuntrigger = FALSE;
	m_enable_presets = FALSE;
	//}}AFX_DATA_INIT

	zERR_MESSAGE(7,zERR_END,"");
}

spcCInfoBar_Vobs::~spcCInfoBar_Vobs()
{
	zRELEASE(cur_vob);

	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing VobPage-Instance...");
	zERR_MESSAGE(7,zERR_END,"");
};


void spcCInfoBar_Vobs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInfoBar_Vobs)
	DDX_Control(pDX, IDC_EVENTRESTORE, ctrl_restore);
	DDX_Control(pDX, IDC_TESTEVENT, ctrl_testevent);
	DDX_Control(pDX, IDC_SENDEVENT, ctrl_sendevent);
	DDX_Control(pDX, IDC_PRESET_CLASS, ctrl_presetclass);
	DDX_Control(pDX, IDC_CAM_ALIGN2, ctrl_camalign);
	DDX_Control(pDX, IDC_ANI_FPS, ctrl_fps);
	DDX_Control(pDX, IDC_ALPHA_BLEND2, ctrl_alphablend);
	DDX_Control(pDX, IDC_2SIDED, ctrl_2sided);
	DDX_Control(pDX, IDC_PRESET_RELOAD_T, ctrl_presetreload);
	DDX_Control(pDX, IDC_PRESET_REMOVE_T, ctrl_presetremove);
	DDX_Control(pDX, IDC_PRESET_FROM_CURRENT_T, ctrl_from_current);
	DDX_Control(pDX, IDC_PRESET_TO_CURRENT_T, ctrl_to_current);
	DDX_Control(pDX, IDC_PRESET_LIST, ctrl_presetlist);
	DDX_Control(pDX, IDC_VISUALNAME, ctrl_visualname);
	DDX_Text(pDX, IDC_CLASSNAME, m_classname);
	DDX_Text(pDX, IDC_VOBNAME, m_vobname);
	DDX_CBString(pDX, IDC_VISUALNAME, m_visualname);
	DDX_Check(pDX, IDC_SEL_CD_DYN, m_sel_cd_dyn);
	DDX_Check(pDX, IDC_SEL_CD_STAT, m_sel_cd_stat);
	DDX_Check(pDX, IDC_SEL_STATICVOB, m_sel_staticvob);
	DDX_Check(pDX, IDC_2SIDED, m_2sided);
	DDX_Text(pDX, IDC_CAM_ALIGN2, m_camalign);
	DDX_Text(pDX, IDC_ALPHA_BLEND2, m_alphablend);
	DDX_Text(pDX, IDC_ANI_FPS, m_fps);
	DDX_CBString(pDX, IDC_PRESET_CLASS, m_presetclass);
	DDX_Check(pDX, IDC_EVTRIGER, m_evtrigger);
	DDX_Check(pDX, IDC_EVUNTRIGER, m_evuntrigger);
	DDX_Check(pDX, IDC_ENABLE_PRESETS, m_enable_presets);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCInfoBar_Vobs, CDialog)
	//{{AFX_MSG_MAP(spcCInfoBar_Vobs)
	ON_EN_CHANGE(IDC_VOBNAME, OnChangeVobname)
	ON_CBN_SELCHANGE(IDC_VISUALNAME, OnSelchangeVisualname)
	ON_BN_CLICKED(IDC_VISUALBUTTON, OnVisualbutton)
	ON_BN_CLICKED(IDC_SEL_CD_DYN, OnSelCdDyn)
	ON_BN_CLICKED(IDC_SEL_CD_STAT, OnSelCdStat)
	ON_BN_CLICKED(IDC_SEL_STATICVOB, OnSelStaticvob)
	ON_LBN_SELCHANGE(IDC_PRESET_LIST, OnSelchangePresetList)
	ON_BN_CLICKED(IDC_PRESET_FROM_CURRENT_T, OnPresetFromCurrentT)
	ON_BN_CLICKED(IDC_PRESET_TO_CURRENT_T, OnPresetToCurrentT)
	ON_BN_CLICKED(IDC_PRESET_REMOVE_T, OnPresetRemoveT)
	ON_BN_CLICKED(IDC_PRESET_RELOAD_T, OnPresetReloadT)
	ON_BN_CLICKED(IDC_2SIDED, On2sided)
	ON_EN_CHANGE(IDC_ANI_FPS, OnChangeAniFps)
	ON_CBN_SELCHANGE(IDC_ALPHA_BLEND2, OnSelchangeAlphaBlend)
	ON_CBN_SELCHANGE(IDC_CAM_ALIGN2, OnSelchangeCamAlign)
	ON_CBN_SELCHANGE(IDC_PRESET_CLASS, OnSelchangePresetClass)
	ON_BN_CLICKED(IDC_SENDEVENT, OnSendevent)
	ON_BN_CLICKED(IDC_TESTEVENT, OnTestevent)
	ON_BN_CLICKED(IDC_EVENTRESTORE, OnEventrestore)
	ON_BN_CLICKED(IDC_ENABLE_PRESETS, OnEnablePresets)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void spcCInfoBar_Vobs::HandleVobSelect(zCVob* vob)
{
};

void spcCInfoBar_Vobs::HandleVobInsert(zCVob* vob, zCVob* parentVob)
{
};

void spcCInfoBar_Vobs::HandleVobRemove(zCVob* vob)
{
};


/////////////////////////////////////////////////////////////////////////////
// eigene Methoden

void spcCInfoBar_Vobs::SelectVob(zCVob* pickedVob)
{
	bool enableDecal = false;
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
		m_sel_staticvob = cur_vob->GetStaticVob();

		ctrl_from_current.EnableWindow(true);
		ctrl_to_current.EnableWindow(false /*selected>=0*/);

		if (dynamic_cast<zCDecal*>(pickedVob))
		{
			enableDecal=true;
			zCDecal* decal = dynamic_cast<zCDecal*>(cur_vob->GetVisual());
			if (!decal) return;

			// Decalwerte
			m_2sided=decal->GetDecal2Sided();
			m_fps = (int)(decal->decalMaterial->texAniCtrl.GetAniFPS());

			CString s = "FULL";
			switch (cur_vob->GetVisualCamAlign())
			{
				case zVISUAL_CAMALIGN_NONE	: s="NONE";break;
				case zVISUAL_CAMALIGN_YAW	: s="YAW";break;
				case zVISUAL_CAMALIGN_FULL	: s="FULL";break;
			};
			m_camalign = s;
			ctrl_camalign.SelectString(-1,m_camalign);
	
			m_alphablend = CString(zrenderer->AlphaBlendFuncTypeToString(decal->decalMaterial->GetAlphaBlendFunc()).ToChar());
			ctrl_alphablend.SelectString(-1, m_alphablend);			
		}
		presetEditMode=false;

		ctrl_testevent.EnableWindow();
		m_evtrigger=true;
		m_evuntrigger=false;

		UpdateData(false);
	}
	else
	{
		if (presetEditMode) return;

		zRELEASE(cur_vob);
		cur_vob=NULL;
		m_vobname = "";
		m_classname = "";
		m_visualname = "";
		m_sel_cd_dyn = FALSE;
		m_sel_cd_stat = FALSE;
		m_sel_staticvob = FALSE;
		ctrl_from_current.EnableWindow(false);
		ctrl_to_current.EnableWindow(false /*selected>=0*/);
		ctrl_testevent.EnableWindow(false);
		ctrl_sendevent.EnableWindow(false);
		ctrl_restore.EnableWindow(false);
		UpdateData(false);
	}
	
	ctrl_2sided.EnableWindow(enableDecal);
	ctrl_alphablend.EnableWindow(enableDecal);
	ctrl_camalign.EnableWindow(enableDecal);
	ctrl_fps.EnableWindow(enableDecal);
}

zCVob* spcCInfoBar_Vobs::CreateNewVob()
{
	if (selected<0 || editPreset==0) return NULL;

	zCVob* newvob = dynamic_cast<zCVob*>(editPreset->CreateCopy());	
	newvob->SetVobPresetName((*actPView)[selected]->presetName);

	return newvob;
}
void spcCInfoBar_Vobs::OnChangeVisual(CString & visName)
{
	if (presetEditMode)
	{
		if (!editPreset) return;
		editPreset->SetVisual(zSTRING(visName.GetBuffer(0)));
		actPView->SetDirty();
	} else
	{
		if (!cur_vob) return;
		cur_vob->SetVisual(zSTRING(visName.GetBuffer(0)));
		cur_vob->SetVobPresetName(zSTRING(""));
	}
	if (dynamic_cast<zCDecal*>(cur_vob))
	{
		ctrl_2sided.EnableWindow(true);
		ctrl_alphablend.EnableWindow(true);
		ctrl_camalign.EnableWindow(true);
		ctrl_fps.EnableWindow(true);
		zCDecal* decal = dynamic_cast<zCDecal*>(cur_vob->GetVisual());
			// Decalwerte
		m_2sided=decal->GetDecal2Sided();
		m_fps = (int)decal->decalMaterial->texAniCtrl.GetAniFPS();
		
		CString s = "FULL";
		switch (cur_vob->GetVisualCamAlign())
		{
			case zVISUAL_CAMALIGN_NONE	: s="NONE";break;
			case zVISUAL_CAMALIGN_YAW	: s="YAW";break;
			case zVISUAL_CAMALIGN_FULL	: s="FULL";break;
		};
		m_camalign = s;
		
		ctrl_camalign.SelectString(-1,m_camalign);

		m_alphablend = CString(zrenderer->AlphaBlendFuncTypeToString(decal->decalMaterial->GetAlphaBlendFunc()).ToChar());
		ctrl_alphablend.SelectString(-1, m_alphablend);
	} else {
		ctrl_2sided.EnableWindow(false);
		ctrl_alphablend.EnableWindow(false);
		ctrl_camalign.EnableWindow(false);
		ctrl_fps.EnableWindow(false);
	}
	m_visualname = visName;
	UpdateData(false);
}

void spcCInfoBar_Vobs::InitData()
{
	CSpacerDoc* pDoc = CSpacerView::view->GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->GetWorld()) return;

	if (presets.GetNumInList()==1 && presets[0]==0)
	{
		WINDOWPLACEMENT wpl;
		ctrl_presetlist.GetWindowPlacement(&wpl);
		wpl.rcNormalPosition.top = wpl.rcNormalPosition.top-20;
		ctrl_presetlist.SetWindowPlacement(&wpl);
		ctrl_presetclass.ShowWindow(SW_HIDE);
	}
	
	ctrl_presetclass.ResetContent();

	/*
	for (int pc=0; pc<presets.GetNumInList(); pc++)
	{
		if (presets[pc]==0)
		{			
			presets[pc] = CMainFrame::mainframe->presetLib.GetNewView( presetClassName[pc] );
			ctrl_presetclass.AddString(presetClassName[pc].ToChar());			
		}
		else
		{
			ctrl_presetclass.AddString(presetClassName[pc].ToChar());
		}
	}
	*/
	ctrl_presetclass.AddString(zCEffect::GetStaticClassDef()->GetClassName_().ToChar());	

	if (presets.GetNumInList()>0)
	{
		actPView = presets[0];
		ctrl_presetclass.SelectString(-1,presetClassName[0].ToChar());
	}
	else actPView = NULL;
	
	UpdatePresetList();
}

void spcCInfoBar_Vobs::UpdatePresetList()
{
	ctrl_presetlist.ResetContent();
	selected=0;
	presetEditMode=false;
	editPreset=NULL;
	
	if (!actPView || (actPView->GetNumInList()<=0)) return;

	for (int z=0; z<actPView->GetNumInList(); z++)
	{
		zCObjPreset* preset = (*actPView)[z];
		if (preset) ctrl_presetlist.AddString(preset->presetName.ToChar());
	}
	UpdateData(false);
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCInfoBar_Vobs 

void spcCInfoBar_Vobs::OnOK() 
{
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
	// prevent that ENTER will close the dialog
	// CDialog::OnOK();
}

void spcCInfoBar_Vobs::OnChangeVobname() 
{
	UpdateData(TRUE);

	if (presetEditMode)
	{
		if (editPreset)
			editPreset->SetVobName(m_vobname.GetBuffer(0));
		actPView->SetDirty();
	} 
	else
	{
		if (cur_vob) 
		{
			cur_vob->SetVobName(m_vobname.GetBuffer(0));
			cur_vob->SetVobPresetName(zSTRING(""));
			// change name in voblist
			CMainFrame::mainframe->HandleObjChange(cur_vob);
		}
	}
}

void spcCInfoBar_Vobs::OnSelchangeVisualname() 
{
	OnChangeVisual(m_visualname);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Vobs::OnVisualbutton() 
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

void spcCInfoBar_Vobs::OnSelCdDyn() 
{
	UpdateData(TRUE);
	if (presetEditMode)
	{
		if (editPreset) editPreset->SetCollDetDyn(m_sel_cd_dyn);
		actPView->SetDirty();
	}
	else
	{
		if (cur_vob) 
		{
			cur_vob->SetCollDetDyn(m_sel_cd_dyn);
			cur_vob->SetVobPresetName(zSTRING(""));
		}
	}

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Vobs::OnSelCdStat() 
{
	UpdateData(TRUE);
	if (presetEditMode)
	{
		if (editPreset) editPreset->SetCollDetStat(m_sel_cd_stat);
		actPView->SetDirty();
	}
	else
	{
		if (cur_vob) 
		{
			cur_vob->SetCollDetStat(m_sel_cd_stat);
			cur_vob->SetVobPresetName(zSTRING(""));
		}
	}
	
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Vobs::OnSelStaticvob() 
{
	UpdateData(TRUE);
	if (presetEditMode)
	{
		if (editPreset) editPreset->SetStaticVob(m_sel_staticvob);
		actPView->SetDirty();
	}
	else
	{
		if (cur_vob) 
		{
			cur_vob->SetStaticVob(m_sel_staticvob);
			cur_vob->SetVobPresetName(zSTRING(""));
		}
	}

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

BOOL spcCInfoBar_Vobs::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void spcCInfoBar_Vobs::OnSelchangePresetList() 
{
	int index = ctrl_presetlist.GetCurSel();
	if (index==CB_ERR) selected =-1;
	
	if (index>=0)
	{
		CString s;
		ctrl_presetlist.GetText(index,s);
		int z=0;
		zSTRING search(s.GetBuffer(0));
		while (z<actPView->GetNumInList() && 
			(*actPView)[z]->presetName!=search)
			z++;
		selected=z;  // kann normalerweise nicht _NICHT gefunden sein!!!
		editPreset=dynamic_cast<zCVob*>((*actPView)[z]->obj);
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
		
		UpdateData(false);
		presetEditMode=true;
	}
	else presetEditMode=false;

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Vobs::OnPresetFromCurrentT() 
{
	if (presetEditMode) return;
	if (cur_vob==0) return;
	::SetCursor(spcConfig.MouseWait);
	actPView->AddPreset(cur_vob,(zSTRING)cur_vob->GetVobName());
	cur_vob->SetVobPresetName((zSTRING)cur_vob->GetVobName());
	UpdatePresetList();
	::SetCursor(spcConfig.MouseArrow);
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Vobs::OnPresetToCurrentT() 
{
	// TODO: 
}

void spcCInfoBar_Vobs::OnPresetRemoveT() 
{
	if (presetEditMode)
	{
		actPView->RemovePreset(selected);
		UpdatePresetList();
	}
}

void spcCInfoBar_Vobs::OnPresetReloadT() 
{
	// TODO: 	
}

void spcCInfoBar_Vobs::On2sided() 
{
	if (!editPreset) return;

	UpdateData(TRUE);	
	
	zCDecal* lDec=dynamic_cast<zCDecal*>(editPreset->GetVisual());
	if (lDec)
		if (presetEditMode)
		{		
			if (editPreset)
			{
				lDec->SetDecal2Sided(m_2sided);
				actPView->SetDirty();
			}
		} 
		else 
		{
			if (cur_vob)
			{
				lDec->SetDecal2Sided(m_2sided);
				cur_vob->SetVobPresetName(zSTRING(""));
			} 
		}

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Vobs::OnChangeAniFps() 
{
	if	(!editPreset) return;
	UpdateData(TRUE);
	zCDecal* lDec = dynamic_cast<zCDecal*>(cur_vob->GetVisual());
	if (lDec)
		if (presetEditMode)
		{
			if (editPreset)
			{
				lDec->decalMaterial->texAniCtrl.SetAniFPS((float)m_fps);
				actPView->SetDirty();
			}
		} 
		else
		{
			if (cur_vob)
			{
				lDec->decalMaterial->texAniCtrl.SetAniFPS((float)m_fps);
				cur_vob->SetVobPresetName(zSTRING(""));			
			}
		}
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Vobs::OnSelchangeAlphaBlend() 
{
	// decal->decalMaterial.SetAlphaBlendFunc(
	//		zrenderer->AlphaBlendFuncStringToType(zSTRING(m_alpha_blend.GetBuffer(0)))
	//	);
	UpdateData(TRUE);
	zCDecal* lDec=dynamic_cast<zCDecal*>(editPreset->GetVisual());
	if (lDec)
		if (presetEditMode)
		{
			if (editPreset)
			{
				lDec->decalMaterial->SetAlphaBlendFunc(zrenderer->AlphaBlendFuncStringToType(zSTRING(m_alphablend.GetBuffer(0))));
				actPView->SetDirty();
			}
		}
		else 
		{
			if (cur_vob)
			{
				lDec->decalMaterial->SetAlphaBlendFunc(zrenderer->AlphaBlendFuncStringToType(zSTRING(m_alphablend.GetBuffer(0))));
				cur_vob->SetVobPresetName(zSTRING(""));
			} 
		}

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Vobs::OnSelchangeCamAlign() 
{
	//vob->SetVisualCamAlignByString(zSTRING(m_cam_align.GetBuffer(0)));
	UpdateData(TRUE);

	if (presetEditMode)
	{
		if (editPreset)
		{
			if (m_camalign=="FULL") editPreset->SetVisualCamAlign(zVISUAL_CAMALIGN_FULL);
			else if (m_camalign=="YAW") editPreset->SetVisualCamAlign(zVISUAL_CAMALIGN_YAW);
			else if (m_camalign=="NONE") editPreset->SetVisualCamAlign(zVISUAL_CAMALIGN_NONE);
			else editPreset->SetVisualCamAlign(zVISUAL_CAMALIGN_FULL);			
		}
		actPView->SetDirty();
	}
	else 
	{
		if (cur_vob) 
		{ 			
			if (m_camalign=="FULL") editPreset->SetVisualCamAlign(zVISUAL_CAMALIGN_FULL);
			else if (m_camalign=="YAW") editPreset->SetVisualCamAlign(zVISUAL_CAMALIGN_YAW);
			else if (m_camalign=="NONE") editPreset->SetVisualCamAlign(zVISUAL_CAMALIGN_NONE);
			else editPreset->SetVisualCamAlign(zVISUAL_CAMALIGN_FULL);			
			
			cur_vob->SetVobPresetName(zSTRING(""));
		}
	}
	
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Vobs::OnSelchangePresetClass() 
{
	int selected = ctrl_presetclass.GetCurSel();
	actPView = presets[selected];
	ctrl_presetclass.GetLBText(selected,m_presetclass);
	UpdatePresetList();

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Vobs::OnSendevent() 
{
	// send
	if (!cur_vob) return;
	UpdateData(true);
	if (m_evtrigger) 
	{
		cur_vob->GetEventManager()->OnTrigger(0,0);
		m_evuntrigger=true;
		m_evtrigger=false;
	} 
	else 
	{
		cur_vob->GetEventManager()->OnUntrigger(0,0);
		m_evtrigger=true;
		m_evuntrigger=false;
	}
	UpdateData(false);
}

void spcCInfoBar_Vobs::OnTestevent() 
{
	// save world in temp-file
	CSpacerDoc* pDoc = CSpacerView::view->GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnQuickSave();
	ctrl_sendevent.EnableWindow();
	ctrl_restore.EnableWindow();
}

void spcCInfoBar_Vobs::OnEventrestore() 
{
	CSpacerDoc* pDoc = CSpacerView::view->GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnQuickOpen();

	m_evtrigger=true;
	m_evuntrigger=false;
}

void spcCInfoBar_Vobs::OnEnablePresets() 
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
