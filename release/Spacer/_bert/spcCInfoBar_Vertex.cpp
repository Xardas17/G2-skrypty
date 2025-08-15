// spcCInfoBar_Vertex.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "SpacerView.h"
#include "spcCInfoBar_Vertex.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCInfoBar_Vertex 


spcCInfoBar_Vertex::spcCInfoBar_Vertex(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInfoBar_Vertex::IDD, pParent)
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Constructing Instance of VertexPage...");

	//{{AFX_DATA_INIT(spcCInfoBar_Vertex)
	m_mv_speed = 0;
	//}}AFX_DATA_INIT

	zERR_MESSAGE(7,zERR_END,"");
}

spcCInfoBar_Vertex::~spcCInfoBar_Vertex()
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing VertexPage-Instance...");
	zERR_MESSAGE(7,zERR_END,"");
};


void spcCInfoBar_Vertex::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInfoBar_Vertex)
	DDX_Control(pDX, IDC_SPEED_SLIDER, ctrl_mv_speed);
	DDX_Slider(pDX, IDC_SPEED_SLIDER, m_mv_speed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCInfoBar_Vertex, CDialog)
	//{{AFX_MSG_MAP(spcCInfoBar_Vertex)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SPEED_SLIDER, OnReleasedcaptureSpeedSlider)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCInfoBar_Vertex 

void spcCInfoBar_Vertex::InitData()
{
	ctrl_mv_speed.SetRange(1,10,true);
	m_mv_speed = 1;
	UpdateData(false);
}

void spcCInfoBar_Vertex::OnReleasedcaptureSpeedSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();

	*pResult = 0;
}
