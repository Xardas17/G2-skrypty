// spcCCompileLightDlg.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "mainfrm.h"
#include "spcCCompileLightDlg.h"
#include "spcCHelpDlg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCCompileLightDlg dialog


spcCCompileLightDlg::spcCCompileLightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCCompileLightDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCCompileLightDlg)
	m_light_quality = -1;
	m_region_compile = FALSE;
	m_region_value = 0;
	//}}AFX_DATA_INIT
}


void spcCCompileLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCCompileLightDlg)
	DDX_Control(pDX, IDC_REGION, ctrl_region);
	DDX_Control(pDX, IDC_REGION_VALUE, ctrl_region_value);
	DDX_Radio(pDX, IDC_LIGHT1, m_light_quality);
	DDX_Check(pDX, IDC_REGION, m_region_compile);
	DDX_Text(pDX, IDC_REGION_VALUE, m_region_value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCCompileLightDlg, CDialog)
	//{{AFX_MSG_MAP(spcCCompileLightDlg)
	ON_BN_CLICKED(IDC_REGION, OnRegion)
	ON_BN_CLICKED(IDC_LIGHT1, OnLight1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCCompileLightDlg message handlers

BOOL spcCCompileLightDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (CMainFrame::mainframe)
	{
		CMainFrame::mainframe->GetHelpWindow()->SetHelpTopic(HELP_TOPIC_WINDOW,"Compile Light");
	};
		
	ctrl_region_value.EnableWindow(m_region_compile);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void spcCCompileLightDlg::OnRegion() 
{
	UpdateData(true);	
	ctrl_region_value.EnableWindow(m_region_compile);	
}

void spcCCompileLightDlg::OnLight1() 
{
		
}
