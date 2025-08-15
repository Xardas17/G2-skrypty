// spcCMessageDialog.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCMessageDialog.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCMessageDialog dialog


spcCMessageDialog* spcCMessageDialog::dlg = 0;


spcCMessageDialog::spcCMessageDialog(CWnd* pParent /*=NULL*/)
	: CDialog(spcCMessageDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCMessageDialog)
	m_text = _T("");
	//}}AFX_DATA_INIT
	if (!dlg) 
	{
		dlg = this;		
		Create(IDD,pParent);
	}	
}


void spcCMessageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCMessageDialog)
	DDX_Control(pDX, IDC_PROP_LIST, ctrl_proplist);
	DDX_Text(pDX, IDC_MESSAGE, m_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCMessageDialog, CDialog)
	//{{AFX_MSG_MAP(spcCMessageDialog)
	ON_LBN_SELCHANGE(IDC_PROP_LIST, OnSelchangePropList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCMessageDialog message handlers

void spcCMessageDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

spcCMessageDialog::~spcCMessageDialog()
{
	// DestroyWindow();
	dlg = NULL;
}

void spcCMessageDialog::SetText(CString _text)
{
	m_text = _text;
	UpdateData(FALSE);
}

void spcCMessageDialog::OnSelchangePropList() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}
