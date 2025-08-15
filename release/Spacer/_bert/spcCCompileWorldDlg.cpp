// spcCCompileWorldDlg.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "mainfrm.h"
#include "spcCCompileWorldDlg.h"
#include "spcCHelpDlg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCCompileWorldDlg dialog


spcCCompileWorldDlg::spcCCompileWorldDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCCompileWorldDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCCompileWorldDlg)
	m_quick_compile = FALSE;
	m_detect_leaks = FALSE;
	m_inout_door = 0;
	m_editormode = FALSE;
	m_polycheck = FALSE;
	//}}AFX_DATA_INIT
}


void spcCCompileWorldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCCompileWorldDlg)
	DDX_Check(pDX, IDC_QUICKCOMPILE, m_quick_compile);
	DDX_Check(pDX, IDC_DETECT_LEAKS, m_detect_leaks);
	DDX_Radio(pDX, IDC_INDOOR, m_inout_door);
	DDX_Check(pDX, IDC_EDITORMODE, m_editormode);
	DDX_Check(pDX, IDC_POLYCHECK, m_polycheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCCompileWorldDlg, CDialog)
	//{{AFX_MSG_MAP(spcCCompileWorldDlg)
	ON_BN_CLICKED(IDC_COMPILE, OnCompile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCCompileWorldDlg message handlers

void spcCCompileWorldDlg::OnCompile() 
{
	CDialog::OnOK();	
}

BOOL spcCCompileWorldDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (CMainFrame::mainframe)
	{
		CMainFrame::mainframe->GetHelpWindow()->SetHelpTopic(HELP_TOPIC_WINDOW,"Compile World");
	};
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
