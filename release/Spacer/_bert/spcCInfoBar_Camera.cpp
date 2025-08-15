// spcCInfoBar_Camera.cpp: Implementierungsdatei
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
#include "zCSCamera.h"
#include "zWorld.h"

#include "spcCInfoBar_Camera.h"
#include "spcCInfoBar.h"
#include "spcCInputDialog.h"

#ifdef _DEBUG
////#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCInfoBar_Camera 

const zSTRING NEW_CAMERA_PRESET = "CAMERASTART";


spcCInfoBar_Camera::spcCInfoBar_Camera(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInfoBar_Camera::IDD, pParent), cur_cam(0), editPreset(0),
		presets(0), selected(-1), presetEditMode(false), ccl("spcCCamSplineCtrl")
{
	lastPresetTime = 10;
	lastPresetAutoAddKF = FALSE;
	//{{AFX_DATA_INIT(spcCInfoBar_Camera)
	m_vobname = _T("");
	m_kf_pos = 0;	
	m_splineselect = 0;
	m_ref_cam = _T("");
	m_ref_target = _T("");	
	m_cam_play_duration = 5;	
	m_insert_at_current_pos = TRUE;
	//}}AFX_DATA_INIT
}


void spcCInfoBar_Camera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInfoBar_Camera)	
	DDX_Control(pDX, IDC_PRESET_LIST, ctrl_presetlist);
	DDX_Control(pDX, IDC_KF_EDIT, ctrl_kf_edit);
	DDX_Text(pDX, IDC_VOBNAME, m_vobname);
	DDX_Text(pDX, IDC_KF_EDIT, m_kf_pos);		
	DDX_Text(pDX, IDC_REF_CAM, m_ref_cam);
	DDX_Text(pDX, IDC_REF_TARGET, m_ref_target);	
	DDX_Text(pDX, IDC_CAM_PLAY_DURATION, m_cam_play_duration);	
	DDX_Check(pDX, IDC_INS_CURRENT_POS, m_insert_at_current_pos);
	DDX_Radio(pDX, IDC_SPLINE_CAM, m_splineselect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCInfoBar_Camera, CDialog)
	//{{AFX_MSG_MAP(spcCInfoBar_Camera)
	ON_EN_CHANGE(IDC_VOBNAME, OnChangeVobname)
	ON_EN_CHANGE(IDC_KF_EDIT, OnChangeKfEdit)
	ON_BN_CLICKED(IDC_KF_DEC, OnKfDec)
	ON_BN_CLICKED(IDC_KF_INC, OnKfInc)
	ON_LBN_SELCHANGE(IDC_PRESET_LIST, OnSelchangePresetList)
	ON_BN_CLICKED(IDC_SPLINE_CAM, OnSplineCam)
	ON_BN_CLICKED(IDC_SPLINE_TARGET, OnSplineTarget)
	ON_BN_CLICKED(IDC_CAM_PLAY, OnCamPlay)
	ON_BN_CLICKED(IDC_CAM_STOP, OnCamStop)
	ON_BN_CLICKED(IDC_CAM_KF_GOTO, OnCamKfGoto)	
	ON_BN_CLICKED(IDC_CREATE_PRESET, OnCreatePreset)
	ON_BN_CLICKED(IDC_REMOVE_PRESET, OnRemovePreset)
	ON_BN_CLICKED(IDC_INSERT_CAMERA, OnInsertCamera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// eigene Methoden

void spcCInfoBar_Camera::HandleVobRemove(zCVob* vob)
{
	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	if (!vob) return;
	zCCamTrj_KeyFrame* isKeyframe = dynamic_cast<zCCamTrj_KeyFrame*>(vob);

	if (vob == cur_cam)	
	{
		UpdateData(true);
		cur_cam=0;
		m_vobname	= "";		
		UpdateData(false);
	} 
	else if (isKeyframe && isKeyframe->GetParentCam()) 
	{
		isKeyframe->GetParentCam()->Refresh();
	}
};

void spcCInfoBar_Camera::HandleVobInsert(zCVob* vob, zCVob* parent)
{		
};

void spcCInfoBar_Camera::HandleVobSelect(zCVob* vob)
{		
	UpdateData(true);

	zCCSCamera*			isCamera = dynamic_cast<zCCSCamera*>(vob);
	zCCamTrj_KeyFrame*	keyframe = dynamic_cast<zCCamTrj_KeyFrame*>(vob);

	if (!isCamera && !keyframe) return;

	if (keyframe)	// ist ein Keyframe
	{	
		// Kameraobject suchen
		isCamera = keyframe->GetParentCam();
		if (!isCamera) return;

		// Splinetyp und Position ermitteln
		int posIndex	= isCamera->SearchCamKey(keyframe);
		int targetIndex	= isCamera->SearchTargetKey(keyframe);

		m_kf_pos		= (posIndex>=0) ? posIndex : targetIndex;
		m_splineselect	= (posIndex>=0) ? 0 : 1;		
	}

	cur_cam = isCamera;	
	if (cur_cam)
	{
		cur_cam->Refresh();	
		m_vobname	= cur_cam->GetVobName().ToChar();		
	}

	// Keyframe-Control aktivieren, falls keyframes vorhanden
	ctrl_kf_edit.EnableWindow(cur_cam && cur_cam->GetNumCamKeys()>0);

	UpdateData(false);
}

void spcCInfoBar_Camera::InitData()
{
//	CSpacerDoc* pDoc = CSpacerView::view->GetDocument();
//	ASSERT_VALID(pDoc);

	if (!CSpacerDoc::doc->GetWorld()) return;

	if (presets==0)
		presets = CMainFrame::mainframe->presetLib.GetNewView(zSTRING("zCCSCamera"));

	if (presets->GetNumInList()==0)
	{
		zCCSCamera* new_cam = new zCCSCamera();
		new_cam->SetVobName("CAMERASTART");
		
		new_cam->camKeysFOR			 = zCCSCamera::zCAMTRJ_KEY_FOR_WORLD;
		new_cam->targetKeysFOR		 = zCCSCamera::zCAMTRJ_KEY_FOR_WORLD;
		new_cam->adaptToSurroundings = FALSE;

		zSTRING name = new_cam->GetVobName();
		presets->AddPreset(new_cam,name);

		zRELEASE(new_cam);
	}
	
	UpdatePresetList();
}

void spcCInfoBar_Camera::UpdatePresetList()
{
	ctrl_presetlist.ResetContent();

// Presets einfügen...
	zCObjPreset* presetObj;	
	CString presetname;
	int count = presets->GetNumInList();
	for (int i=0;i<count;i++)
	{
		presetObj = (*presets)[i];
		if (presetObj)
		{
			presetname = CString(presetObj->presetName.ToChar());
			ctrl_presetlist.AddString(presetname);
		}
	};
}


void spcCInfoBar_Camera::UpdateKeyframe()
{
	if (cur_cam) cur_cam->Refresh();
}

void spcCInfoBar_Camera::SetToKeyPos()
{
	if (cur_cam)
	{
		if (m_splineselect==0)
		{
			if (cur_cam && (cur_cam->GetNumCamKeys()>m_kf_pos))
				CSpacerView::view->VobSelect(cur_cam->GetCamKey(m_kf_pos));
		}
		else
		{
			if (cur_cam && (cur_cam->GetNumTargetKeys()>m_kf_pos))
				CSpacerView::view->VobSelect(cur_cam->GetTargetKey(m_kf_pos));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCInfoBar_Camera 

void spcCInfoBar_Camera::OnOK() 
{
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
	// prevent that ENTER will close the dialog
	// CDialog::OnOK();
}

BOOL spcCInfoBar_Camera::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ctrl_kf_edit.EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void spcCInfoBar_Camera::OnChangeKfEdit() 
{	
	if (cur_cam==0) return;
	int oldFrame = m_kf_pos;

	UpdateData(true);

	if (	(m_splineselect==0 && m_kf_pos>=cur_cam->GetNumCamKeys()) ||
			(m_splineselect==1 && m_kf_pos>=cur_cam->GetNumTargetKeys())
		) m_kf_pos = oldFrame;
	SetToKeyPos();		
	
	UpdateData(false);
}

void spcCInfoBar_Camera::OnKfDec() 
{
	if (!cur_cam) { zERR_WARNING("B: SPC CS: No cutscene-camera defined.");return;}

	UpdateData(true);

	if (m_kf_pos>=1) m_kf_pos--;
	SetToKeyPos();		
	
	UpdateData(false);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();

}

void spcCInfoBar_Camera::OnSplineCam() 
{
	UpdateData(true);
	if (cur_cam) CSpacerView::view->VobSelect(cur_cam);
	m_kf_pos = 0;
	UpdateData(false);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Camera::OnSplineTarget() 
{
	UpdateData(true);
	if (cur_cam) CSpacerView::view->VobSelect(cur_cam);
	m_kf_pos = 0;
	UpdateData(false);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Camera::OnCamPlay()
{
	UpdateData(true);

	if (cur_cam==0) 
	{
		AfxMessageBox("Please select a camera!");
		return;
	}
//	CSpacerDoc* pDoc = CSpacerView::view->GetDocument();
//	ASSERT_VALID(pDoc);

	UpdateData(true);

	zCVob* v=0;

	// hier spezifizieren:
	// wenn preset FOR object und kein name angegeben: dann preset vob benutztn
	// wenn preset FOR object und name angegeben: angebenen vob benutzen
	// wenn preset FOR world und name angegeben: name ignorieren und welt CF
	// wenn preset FOR world und kein name angegeben: dito
	
	if (cur_cam->camKeysFOR == zCCSCamera::zCAMTRJ_KEY_FOR_OBJECT) 
	{
		// suche refCam, und setzt ihn
		zSTRING refCamVobName = zSTRING(m_ref_cam.GetBuffer(0));
		if (!refCamVobName.IsEmpty()) v = CSpacerDoc::doc->GetWorld()->SearchVobByName(refCamVobName);

		zCCSCamera_EventMsgActivate* msg_c = new zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETCAMREFERENCE);
		
		if (!v) msg_c->MD_SetVobParam(cur_cam);
		else	msg_c->MD_SetVobParam(v);

		cur_cam->OnMessage(msg_c,NULL);
	} 

	if (cur_cam->targetKeysFOR == zCCSCamera::zCAMTRJ_KEY_FOR_OBJECT) 
	{

		zSTRING refTargetVobName = zSTRING(m_ref_target.GetBuffer(0));
		if (!refTargetVobName.IsEmpty()) v = CSpacerDoc::doc->GetWorld()->SearchVobByName(refTargetVobName);
		else v= 0;

		zCCSCamera_EventMsgActivate* msg_t = new zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETTARGETREFERENCE);
		if (!v) msg_t->MD_SetVobParam(cur_cam);
		else	msg_t->MD_SetVobParam(v);

		if (cur_cam->GetNumTargetKeys() == 0) lastPresetAutoAddKF = TRUE;
		else								  lastPresetAutoAddKF = FALSE;

		cur_cam->OnMessage(msg_t,NULL);

	} 

	// hole EVManager
	// sende EV_Play
	zCCSCamera_EventMsg* msg = new zCCSCamera_EventMsg(zCCSCamera_EventMsg::EV_PLAY);
	lastPresetTime = cur_cam->GetDuration();
	msg->time = m_cam_play_duration;
	cur_cam->OnMessage(msg,NULL);	
}



void spcCInfoBar_Camera::OnCamStop()
{
	if (cur_cam==0) return;
	// hole EVManager
	// sende EV_Play
	zCCSCamera_EventMsgActivate* msg_t = new zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETTARGETREFERENCE);
	zCCSCamera_EventMsgActivate* msg_c = new zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETCAMREFERENCE);

	if (lastPresetAutoAddKF) msg_t->MD_SetVobParam(0);
	else					 msg_t->MD_SetVobParam(cur_cam);

	msg_c->MD_SetVobParam(cur_cam);

	if (cur_cam->GetNumTargetKeys()>0) cur_cam->OnMessage(msg_t,NULL);

	cur_cam->OnMessage(msg_c,NULL);
	cur_cam->OnMessage(msg_t,NULL);

	zCCSCamera_EventMsg* msg = new zCCSCamera_EventMsg(zCCSCamera_EventMsg::EV_STOP);
	cur_cam->OnMessage(msg,NULL);

	cur_cam->SetDuration(lastPresetTime);

	cur_cam->SetShowVisual(TRUE);
}



void spcCInfoBar_Camera::OnCamKfGoto() 
{

	UpdateData(true);

	if (cur_cam==0) 
	{
		AfxMessageBox("Please select a camera!");
		return;
	}
//	CSpacerDoc* pDoc = CSpacerView::view->GetDocument();
//	ASSERT_VALID(pDoc);

	UpdateData(true);

	zCVob* v=0;

	// hier spezifizieren:
	// wenn preset FOR object und kein name angegeben: dann preset vob benutztn
	// wenn preset FOR object und name angegeben: angebenen vob benutzen
	// wenn preset FOR world und name angegeben: name ignorieren und welt CF
	// wenn preset FOR world und kein name angegeben: dito
	
	if (cur_cam->camKeysFOR == zCCSCamera::zCAMTRJ_KEY_FOR_OBJECT) {
		// suche refCam, und setzt ihn
		zSTRING refCamVobName = zSTRING(m_ref_cam.GetBuffer(0));
		if (!refCamVobName.IsEmpty()) v = CSpacerDoc::doc->GetWorld()->SearchVobByName(refCamVobName);

		zCCSCamera_EventMsgActivate* msg_c = new zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETCAMREFERENCE);
		
		if (!v) msg_c->MD_SetVobParam(cur_cam);
		else	msg_c->MD_SetVobParam(v);

		cur_cam->OnMessage(msg_c,NULL);
	} 

	if (cur_cam->targetKeysFOR == zCCSCamera::zCAMTRJ_KEY_FOR_OBJECT) {

		zSTRING refTargetVobName = zSTRING(m_ref_target.GetBuffer(0));
		if (!refTargetVobName.IsEmpty()) v = CSpacerDoc::doc->GetWorld()->SearchVobByName(refTargetVobName);
		else v= 0;

		zCCSCamera_EventMsgActivate* msg_t = new zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETTARGETREFERENCE);
		if (!v) msg_t->MD_SetVobParam(cur_cam);
		else	msg_t->MD_SetVobParam(v);

		if (cur_cam->GetNumTargetKeys() == 0) lastPresetAutoAddKF = TRUE;
		else								  lastPresetAutoAddKF = FALSE;

		cur_cam->OnMessage(msg_t,NULL);

	} 


	// hole EVManager
	// sende EV_Play
	zCCSCamera_EventMsg* msg = new zCCSCamera_EventMsg(zCCSCamera_EventMsg::EV_GOTO_KEY);
	msg->time	= m_cam_play_duration;
	msg->key	= m_kf_pos;
	msg->kfType = (m_splineselect == 0) ? KF_CAM : KF_TARGET;
	cur_cam->OnMessage(msg,NULL);
	cur_cam->SetShowVisual(FALSE);
}


void spcCInfoBar_Camera::OnInsertCamera() 
{	
	UpdateData(true);

	if (!CMainFrame::mainframe) return;
	spcCInfoBar* info = CMainFrame::mainframe->GetInfoBar();
	if (!info) return;
	
	zCWorld* world		= info->GetActiveWorld();
	if (!world) return;	

	zCVob* selectedVob	= info->GetSelectedVob();

	// Und los: Wenn preset selektiert, dann Kameraobjekt erzeugen ...
	if (!editPreset) return;
	zCCSCamera* newcam = dynamic_cast<zCCSCamera*>(editPreset->CreateCopy());
	assert(newcam!=0);

	zMAT4 trafoPresetToWorld = newcam->trafoObjToWorld;

	newcam->SetVobPresetName(editPreset->GetVobPresetName());	
	newcam->SetPhysicsEnabled	(FALSE);
	newcam->SetSleepingMode		(zVOB_AWAKE_DOAI_ONLY);
	newcam->SetDrawEnabled		(true);
	newcam->SetCollDetStat		(FALSE); // to be able to mov	e the cam
	newcam->SetCollDetDyn		(FALSE);

	zCCSCamera_EventMsgActivate* msg_c = new zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETCAMREFERENCE);
	zCCSCamera_EventMsgActivate* msg_t = new zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETTARGETREFERENCE);

	msg_c->referenceVob = newcam;
	msg_t->referenceVob = newcam;

	newcam->OnMessage(msg_c,NULL);
	newcam->OnMessage(msg_t,NULL);
	
	if (!m_insert_at_current_pos) 
	{
		CSpacerDoc::doc->InsertVob(newcam,0,0, selectedVob);
		CSpacerView::view->VobGoto(newcam);
	}
	else 
	{	
		zPOINT3 pos;zPOINT3 dir;
		info->GetCurrentPosVector(pos);	
		info->GetCurrentAtVector (dir);
		pos = pos+dir*200;

		CSpacerDoc::doc->InsertVob(newcam,&pos,&dir,selectedVob);
	}

	// all keyframes as childs
	for (int pcount=0; pcount<newcam->GetNumCamKeys(); pcount++)
	{	
		if (m_insert_at_current_pos) {
			// Die Orientierung und Position der Keyframes ist in den Presets absolut abgespeichert
			// Um herauszufinden, wie diese jetzt im neuen Koordinatensystem liegen, brauchen wir die 
			// Koordinaten relativ zum Camera Koordinaten System im Preset
			zCCamTrj_KeyFrame* key = newcam->GetCamKey(pcount);
			zMAT4 trafoKeyToPreset = trafoPresetToWorld.InverseLinTrafo() * key->trafoObjToWorld;
			
			// neue Position und Orientierung:
			zMAT4 trafoKeyToWorld  = newcam->trafoObjToWorld * trafoKeyToPreset;

			zPOINT3 pos = trafoKeyToWorld.GetTranslation();
			zVEC3   dir = trafoKeyToWorld.GetAtVector	();

			CSpacerDoc::doc->InsertVob(key,&pos,&dir,newcam);		
		}
		else CSpacerDoc::doc->InsertVob(newcam->GetCamKey(pcount),0,0,newcam);		

		// newcam->GetCamKey(pcount)->SetVisual("invisible_keyframe.3ds");
	}
	for (int tcount=0; tcount<newcam->GetNumTargetKeys(); tcount++){
		
		if (m_insert_at_current_pos) {
			// Die Orientierung und Position der Keyframes ist in den Presets absolut abgespeichert
			// Um herauszufinden, wie diese jetzt im neuen Koordinatensystem liegen, brauchen wir die 
			// Koordinaten relativ zum Camera Koordinaten System im Preset
			zCCamTrj_KeyFrame* key = newcam->GetTargetKey(tcount);
			zMAT4 trafoKeyToPreset = trafoPresetToWorld.InverseLinTrafo() * key->trafoObjToWorld;
			
			// neue Position und Orientierung:
			zMAT4 trafoKeyToWorld  = newcam->trafoObjToWorld * trafoKeyToPreset;

			zPOINT3 pos = trafoKeyToWorld.GetTranslation();
			zVEC3   dir = trafoKeyToWorld.GetAtVector	();

			CSpacerDoc::doc->InsertVob(key,&pos,&dir,newcam);		

		} else CSpacerDoc::doc->InsertVob(newcam->GetTargetKey(tcount),0,0,newcam);		

		// newcam->GetTargetKey(tcount)->SetVisual("invisible_keyframe.3ds");
	}

	newcam->Refresh();
	
	newcam->SetDrawEnabled(TRUE);
	zRELEASE(newcam);
}

zCVob* spcCInfoBar_Camera::InsertVob(const zPOINT3& pos, const zPOINT3& dir, zCVob* parent)
{
	
	// 1. Nur noch Keyframe erzeugen
	// a) Ermitteln, ob Camera oder Keyframe als parent uebergeben wird
	// -> Dann dahinter neuen Einfuegen
	// b) Falls parent anderer Vobtyp
	// -> Neuen Keyframe hinten anfuegen

	if (!parent) return NULL;

	if (!cur_cam) 
	{
		AfxMessageBox("Select a camera to insert a keyframe");
		return 0;
	}

	// Ermitteln, von welchem Typ der Parentvob ist
	zCCamTrj_KeyFrame*	parentKeyframe= dynamic_cast<zCCamTrj_KeyFrame*>(parent);
	// zCCSCamera*			parentIsCamera	= dynamic_cast<zCCSCamera*>(parent);
	int foundPos = -1;

	if (parentKeyframe) 
	// angeklickten Keyframe analysieren (evtl. Kamera und/oder Splinetype wechseln)
	{						
		if (parentKeyframe->GetType()==KF_TARGET) 
		{
			foundPos = cur_cam->SearchTargetKey(parentKeyframe); 
		}
		else
		if (parentKeyframe->GetType()==KF_CAM) 	
		{
			foundPos = cur_cam->SearchCamKey(parentKeyframe); 
		}
		else 
		{
			AfxMessageBox("Unable to add keyframe behind a key of type KF_UNDEF");
			return 0;
		}

		if (foundPos == -1) 
		{
			// Keyframe gehört zu einer anderen Camera, suchen wir doch mal die richtige aus der Welt...
			zCArray<zCVob*> resultCam;
			CSpacerDoc::doc->GetWorld()->SearchVobListByClass(zCCSCamera::GetStaticClassDef(),resultCam);

			if( resultCam.GetNumInList()==0 ) 
			{
				AfxMessageBox("You can't add Keyframes as childs to manually inserted Keyframes");
				return 0;
			}
			
			for (int i=0; i<resultCam.GetNumInList(); i++)
			{
				zCCSCamera*cam = static_cast<zCCSCamera*>(resultCam[i]);

				if (parentKeyframe->GetType()==KF_TARGET) 
				{
					foundPos = cam->SearchTargetKey(parentKeyframe); 					
					m_splineselect	= 1;					
				}
				else
				{
					foundPos = cam->SearchCamKey(parentKeyframe); 
					m_splineselect	= 0;					
				}

				if (foundPos != -1) 
				{
					UpdateData(false); // Aenderung von m_splineselect uebernehmen
					HandleVobSelect(cam); // Camera selektieren
					break;
				}
			}			

		} 

		if (foundPos == -1) 
		{
			AfxMessageBox("This parent keyframe does not belong to a camera, therefore you can't add child keyframes to it!");
			return 0;
		}

		m_kf_pos = foundPos;
	};
	
	if (!cur_cam) 
	{
		AfxMessageBox("Select a camera to insert a keyframe");
		return 0;
	}

	zCCamTrj_KeyFrame* newkey = new zCCamTrj_KeyFrame();
	
	newkey->SetCollDetStat	(FALSE); // to be able to move the key
	newkey->SetCollDetDyn	(FALSE);

	zPOINT3 p = pos+dir*200;
	zPOINT3 v = dir;

	CSpacerDoc::doc->InsertVob(newkey,&p,&v,cur_cam);
	
	if (m_splineselect==0) 
	// Camera-Spline
	{
		if (cur_cam->GetNumCamKeys()==0) 
		{
			cur_cam->InsertCamKey(newkey); // am Ende einfugen
		}
		else 
		{
			// Mitten drin einfuegen
			if (parentKeyframe) cur_cam->InsertCamKeyAtPos(newkey,foundPos+1); 
			else				cur_cam->InsertCamKeyAtPos(newkey,cur_cam->GetNumCamKeys()); 
		}
	}		
	else 
	// Target-Spline
	{
		if (cur_cam->GetNumTargetKeys()==0) 
		{
			cur_cam->InsertTargetKey(newkey); // am Ende einfugen
		}
		else 
		{
			if (parentKeyframe) cur_cam->InsertTargetKeyAtPos(newkey,foundPos+1); 
			else				cur_cam->InsertTargetKeyAtPos(newkey,cur_cam->GetNumTargetKeys()); // Mitten drin einfuegen
		}
	}

	// Visual setzen
	// newkey->SetVisual(zSTRING("invisible_keyframe.3ds"));
	
	return newkey;	
}







void spcCInfoBar_Camera::OnKfInc() 
{
	if (!cur_cam) { zERR_WARNING("B: SPC CS: No cutscene-camera defined.");return;}

	UpdateData(true);

	if (	(m_splineselect==0 && m_kf_pos+1<cur_cam->GetNumCamKeys()) ||
			(m_splineselect==1 && m_kf_pos+1<cur_cam->GetNumTargetKeys())
		) m_kf_pos++;;
	SetToKeyPos();		
	
	UpdateData(false);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}




////////// CHANGED_BY_BERT ////////////////////////



void spcCInfoBar_Camera::OnCreatePreset() 
{
	if (cur_cam==0)
	{
		AfxMessageBox("Select a camera to create a preset");
	} 
	else 
	{
		::SetCursor(spcConfig.MouseWait);
		/*
		for (int z=0; z<cur_cam->GetNumCamKeys(); z++) cur_cam->GetCamKey(z)->SetVisual(NULL);
		for (z=0; z<cur_cam->GetNumTargetKeys(); z++)  cur_cam->GetTargetKey(z)->SetVisual(NULL);
		*/
		
		// Gibt es so einen Preset schon?
		zSTRING zpresetname = cur_cam->GetVobName();
		if (zpresetname!=NEW_CAMERA_PRESET) 
		{
					
			zCVob* camcopy = dynamic_cast<zCVob*>(cur_cam->CreateCopy());

			int index = presets->GetViewIndexByName(zpresetname);
			
			if (index<0)
				presets->AddPreset(camcopy,zpresetname);
			else 
				presets->ChangePreset(camcopy,index);

			presets->SetDirty();
			UpdatePresetList();

		}

		/*
		for (int pcount=0; pcount<cur_cam->GetNumCamKeys(); pcount++)
		{
			cur_cam->GetCamKey(pcount)->SetVisual("invisible_keyframe.3ds");
		}
		for (int tcount=0; tcount<cur_cam->GetNumTargetKeys(); tcount++)
		{
			cur_cam->GetTargetKey(tcount)->SetVisual("invisible_keyframe.3ds");
		}
		*/

		::SetCursor(spcConfig.MouseArrow);
	}
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Camera::OnRemovePreset() 
{	
	if (editPreset->GetVobName()!=NEW_CAMERA_PRESET) 
	{
		presets->RemovePreset(selected);
	}
	UpdatePresetList();
}

void spcCInfoBar_Camera::OnSelchangePresetList() 
{
	int index = ctrl_presetlist.GetCurSel();
	if (index<0) 
	{
		selected =-1;
		zERR_WARNING("B: SPC: No preset-entry selected.");
		return;
	}
	
	UpdateData(true);

	CString presetname;
	ctrl_presetlist.GetText(index,presetname);
	zSTRING zpresetname(presetname.GetBuffer(0));
			
	selected = presets->GetViewIndexByName(zpresetname);						
	if (selected<0)
	{
		selected=-1;
		zERR_WARNING("B: SPC: Index of Camera-Preset "+zpresetname+" not found");
		return;		
	};
	zCObjPreset* presetObj = dynamic_cast<zCObjPreset*>(presets->GetPresetByName(zpresetname));
	if (!presetObj)
	{
		selected=-1;
		zERR_WARNING("B: SPC: Camera-Preset not found: "+zpresetname);
		return;		
	};
	editPreset	= dynamic_cast<zCCSCamera*>(presetObj->obj);
	if (!editPreset) 
	{
		selected=-1;
		zERR_WARNING("B: SPC: Preset-Cameraobject not found: "+zpresetname);
		return;
	}

	m_vobname	= editPreset->GetVobName().ToChar();	
	
	ctrl_kf_edit.EnableWindow(false);
	
	UpdateData(false);	
	
	if (CSpacerView::view) CSpacerView::view->SetFocus();	
}

void spcCInfoBar_Camera::OnChangeVobname() 
{
	UpdateData(TRUE);
	if (cur_cam)
	{
		cur_cam->SetVobName(m_vobname.GetBuffer(0));
		cur_cam->SetVobPresetName(zSTRING(""));
	}
	// change name in voblist
	CMainFrame::mainframe->HandleObjChange(cur_cam);
}


////////// END: CHANGED_BY_BERT ////////////////////////