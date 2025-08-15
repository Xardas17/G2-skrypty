// spcCInfoBar_Sounds.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

// Spacer-Files
#include "Spacer.h"
#include "SpacerView.h"
#include "SpacerDoc.h"

// spc-Files
#include "spcCInfoBar_Sounds.h"

// z-Files
#include "zVob.h"
#include "zZone.h"
#include "zWorld.h"
#include "zWorld.h"

#ifdef _DEBUG
////#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Sounds dialog


spcCInfoBar_Sounds::spcCInfoBar_Sounds(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInfoBar_Sounds::IDD, pParent)
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Constructing Instance of SoundsPage...");

	//{{AFX_DATA_INIT(spcCInfoBar_Sounds)
	m_playing_name = _T("");
	m_playing = FALSE;
	//}}AFX_DATA_INIT

	playing_vob = NULL;

	zERR_MESSAGE(7,zERR_END,"");
}


spcCInfoBar_Sounds::~spcCInfoBar_Sounds()
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing SoundPage-Instance ...");		
	if (playing_vob) 
	{
		if (playing_vob) playing_vob->StopSound();
		zRELEASE(playing_vob);
		playing_vob = NULL;
	}
	m_playing = FALSE;
	playing_vob = NULL;
	zERR_MESSAGE(7,zERR_END,"");

};


void spcCInfoBar_Sounds::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInfoBar_Sounds)
	DDX_Control(pDX, IDC_VOBLIST, ctrl_voblist);
	DDX_Text(pDX, IDC_SND_PLAYNAME, m_playing_name);
	DDX_Check(pDX, IDC_SND_PLAY, m_playing);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCInfoBar_Sounds, CDialog)
	//{{AFX_MSG_MAP(spcCInfoBar_Sounds)	
	ON_LBN_SELCHANGE(IDC_VOBLIST, OnSelchangeVoblist)
	ON_BN_CLICKED(IDC_SND_PLAY, OnSndPlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Sounds message handlers

void spcCInfoBar_Sounds::SelectVob(zCVob* vob)
{
	zCVob* avob = vob;
	vob = dynamic_cast<zCVobSound*>(avob);	
}

zCVob* spcCInfoBar_Sounds::CreateNewVob()
{
	int index = ctrl_voblist.GetCurSel();
	if (index==LB_ERR) return NULL;	

	UpdateData(true);

	CString soundInstance;
	ctrl_voblist.GetText(index,soundInstance);

	zCVobSound* newSound = new zCVobSound();	
	newSound->SetSound(zSTRING(soundInstance.GetBuffer(0)));			
	newSound->SetShowVisual(TRUE);
	newSound->SetVobName(zSTRING(soundInstance.GetBuffer(0)));
	newSound->StopSound();

	UpdateData(false);

	return (zCVob*)newSound;
}

void spcCInfoBar_Sounds::OnOK() 
{
	// prevent that ENTER will close the dialog
	// CDialog::OnOK();
}

void spcCInfoBar_Sounds::OnSelchangeVoblist() 
{
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Sounds::OnSndPlay() 
{
	UpdateData(TRUE);

	if (!m_playing || playing_vob)
	{
		if (playing_vob) playing_vob->StopSound();
		playing_vob = NULL;
		m_playing_name = "";
		m_playing = FALSE;
	}
	else
	{
		int index = ctrl_voblist.GetCurSel();
		if (index==LB_ERR) return;

		ctrl_voblist.GetText(index,m_playing_name);

		playing_vob = new zCVobSound();	
		playing_vob->SetSound(zSTRING(m_playing_name.GetBuffer(0)));				


		zCCamera* camera = CSpacerView::view->GetCamera();
		if (camera) 
		{
			zCVob* vob = camera->GetVob();
			if (vob) playing_vob->SetPositionWorld( vob->GetPositionWorld() );
		}
		
		
		playing_vob->StartSound();		
		
		m_playing = (playing_vob!=NULL);
	}

	UpdateData(FALSE);
}

void spcCInfoBar_Sounds::HandleVobSelect(zCVob* vob)
{
	SelectVob(vob);
};

void spcCInfoBar_Sounds::HandleVobInsert(zCVob* vob, zCVob* parentVob)
{	
};

void spcCInfoBar_Sounds::HandleVobRemove(zCVob* vob)
{
};

