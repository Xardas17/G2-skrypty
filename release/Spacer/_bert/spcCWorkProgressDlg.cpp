// spcCWorkProgressDlg.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCWorkProgressDlg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCWorkProgressDlg dialog


spcCWorkProgressDlg::spcCWorkProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCWorkProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCWorkProgressDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void spcCWorkProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCWorkProgressDlg)
	DDX_Control(pDX, IDC_WORKPROGRESS, m_progression);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCWorkProgressDlg, CDialog)
	//{{AFX_MSG_MAP(spcCWorkProgressDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCWorkProgressDlg message handlers


void spcCWorkProgressDlg::Step(int rel)
{
	int pos = m_progression.GetPos();
	m_progression.SetPos(pos+rel);
};

void spcCWorkProgressDlg::SetPos(int pos)
{	
	m_progression.SetPos(pos);
};

void spcCWorkProgressDlg::Init(int min, int max)
{
	m_progression.SetRange32(min,max);
}

