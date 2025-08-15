// spcCInfoBar_Specials.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "Mainfrm.h"
#include "SpacerDoc.h"
#include "SpacerView.h"
#include "spcCInfoBar_Specials.h"

// include z-files
#include "zwaynet.h"
#include "z3d.h"
#include "zworld.h"
#include "zparticle.h"


#ifdef _DEBUG
////#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Specials dialog


spcCInfoBar_Specials::spcCInfoBar_Specials(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInfoBar_Specials::IDD, pParent)
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Constructing Instance of SpecialsPage...");

	//{{AFX_DATA_INIT(spcCInfoBar_Specials)
	m_particle	= TRUE;
	m_spot		= FALSE;
	m_waypoint	= FALSE;
	m_decal = FALSE;
	//}}AFX_DATA_INIT
	cur_vob = NULL;

	zERR_MESSAGE(7,zERR_END,"");
}

spcCInfoBar_Specials::~spcCInfoBar_Specials()
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing SpecialsPage-Instance...");
	zERR_MESSAGE(7,zERR_END,"");
};

void spcCInfoBar_Specials::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInfoBar_Specials)
	// DDX_Control(pDX, IDC_PART_EDIT, ctrl_part_edit);
	// DDX_Control(pDX, IDC_PART_NEW, crtl_part_new);
	DDX_Control(pDX, IDC_LIST, ctrl_list);
	DDX_Check(pDX, IDC_PARTICLES, m_particle);
	DDX_Check(pDX, IDC_SPOTS, m_spot);	
	DDX_Check(pDX, IDC_WAYPOINTS, m_waypoint);
	DDX_Check(pDX, IDC_DECAL, m_decal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCInfoBar_Specials, CDialog)
	//{{AFX_MSG_MAP(spcCInfoBar_Specials)
	ON_BN_CLICKED(IDC_PARTICLES, OnParticles)	
	ON_BN_CLICKED(IDC_SPOTS, OnSpots)
	ON_BN_CLICKED(IDC_WAYPOINTS, OnWaypoints)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)	
	//ON_BN_CLICKED(IDC_PART_EDIT, OnPartEdit)
	//ON_BN_CLICKED(IDC_PART_NEW, OnPartNew)
	ON_BN_CLICKED(IDC_DECAL, OnDecal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Specials message handlers

void spcCInfoBar_Specials::HandleVobSelect(zCVob* vob)
{
	if (!vob) return;

	if (dynamic_cast<zCVobSpot*>(vob)) OnSpots();
	else if (dynamic_cast<zCVobWaypoint*>(vob)) OnWaypoints();
	else if (dynamic_cast<zCParticleFX*>(vob->GetVisual())) OnParticles();	
};

void spcCInfoBar_Specials::HandleVobInsert(zCVob* vob, zCVob* parentVob)
{
};

void spcCInfoBar_Specials::HandleVobRemove(zCVob* vob)
{
};



zCVob* spcCInfoBar_Specials::CreateNewVob()
{
	UpdateData(TRUE);	
	
	zCVob* newvob			= 0;
	zCParticleFX* fxvisual	= 0;
	
	if (m_decal)
	{
		newvob = new zCVob;
		newvob->SetCollDet(FALSE);		
		newvob->SetVisual("default.tga");		
	}
	else if (m_waypoint)
	{		
		newvob = new zCVobWaypoint();
		newvob->SetCollDet(FALSE);
	}
	else if (m_particle)
	{
		if (m_list == "") return NULL;		
		newvob = new zCVob;
		fxvisual = new zCParticleFX();		
		newvob->SetVisual(fxvisual);
	}		
	else if (m_spot)
	{
		newvob = new zCVobSpot();
	}
	
	if (!newvob) return 0;	

	if (m_particle)
	{
		zERR_ASSERT(fxvisual);
		fxvisual->SetAndStartEmitter(zSTRING(m_list.GetBuffer(0)));		
	}		

	UpdateData(false);	

	return newvob;
}

void spcCInfoBar_Specials::OnModeChanged()
{
	showParticlePanel(bool(m_particle==TRUE));	
}

void spcCInfoBar_Specials::OnParticles() 
{
	UpdateData(TRUE);
	m_particle = true;
	m_decal = m_waypoint = m_spot = false;
	OnModeChanged();
	UpdateData(FALSE);
	UpdateWindow();

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}
	

void spcCInfoBar_Specials::OnDecal() 
{
	UpdateData(TRUE);
	m_decal = true;
	m_particle = m_spot = m_waypoint = false;
	UpdateData(FALSE);
}

void spcCInfoBar_Specials::OnWaypoints() 
{
	UpdateData(TRUE);
	m_waypoint = true;
	m_particle = m_spot = m_decal = false;
	OnModeChanged();	
	UpdateData(FALSE);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Specials::OnSpots() 
{
	UpdateData(TRUE);
	m_spot = true;
	m_waypoint = m_particle = m_decal = false;
	OnModeChanged();
	UpdateData(FALSE);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Specials::SelectVob(zCVob * vob)
{	
	cur_vob = vob;
	if (!vob)  return;
	
	m_decal		= vob->GetVisual() && dynamic_cast<zCDecal*>(vob->GetVisual());
	m_waypoint	= (NULL != dynamic_cast<zCWaypoint*>(vob));	
	m_spot		= (NULL != dynamic_cast<zCVobSpot*>(vob));
	m_particle	= (NULL != dynamic_cast<zCParticleFX*>(vob->GetVisual()));	

	OnModeChanged();
	UpdateData(FALSE);
}

BOOL spcCInfoBar_Specials::OnInitDialog() 
{
	CDialog::OnInitDialog();			

	OnModeChanged();

	for (int i=0;i<zCParticleFX::s_emitterPresetList.GetNumInList();i++)
	{
		ctrl_list.AddString(zCParticleFX::s_emitterPresetList.GetSafe(i)->GetParticleFXName().ToChar());
	}

	return TRUE;
}

void spcCInfoBar_Specials::OnSelchangeList() 
{
	UpdateData(TRUE);

	int index = ctrl_list.GetCurSel();
	if (index==LB_ERR) return;
	ctrl_list.GetText(index,m_list);
	
	UpdateData(FALSE);

	zSTRING lname = zSTRING(m_list.GetBuffer(0));
	CSpacerView::view->particleControl.SetPFXName(lname);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Specials::OnOK() 
{
	// prevent that ENTER will close the dialog
	// CDialog::OnOK();
}

/*
void spcCInfoBar_Specials::OnPartEdit() 
{
	CSpacerView::view->particleControl.BeginEditActive();
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCInfoBar_Specials::OnPartNew() 
{
	// TODO: Add your control notification handler code here
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}
*/

void spcCInfoBar_Specials::showParticlePanel(bool quest)
{
	if (quest) 
	{
		ctrl_list.EnableWindow(TRUE);		
		//ctrl_part_edit.EnableWindow(TRUE);
		//crtl_part_new.EnableWindow(TRUE);
				
		CSpacerView::view->UpdateParticleControl(true);
	}
	else
	{		
		ctrl_list.EnableWindow(FALSE);		
		//ctrl_part_edit.EnableWindow(FALSE);
		//crtl_part_new.EnableWindow(FALSE);
		CSpacerView::view->UpdateParticleControl(false);
	}
}

