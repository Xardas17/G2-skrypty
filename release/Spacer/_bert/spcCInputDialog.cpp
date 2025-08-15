// spcCInputDialog.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCInputDialog.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCInputDialog dialog


spcCInputDialog::spcCInputDialog(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInputDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCInputDialog)
	m_edit = _T("");
	m_text = _T("");
	//}}AFX_DATA_INIT
}


void spcCInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInputDialog)
	DDX_Text(pDX, IDC_EDIT, m_edit);
	DDX_Text(pDX, IDC_TEXT, m_text);
	//}}AFX_DATA_MAP
}

CString spcCInputDialog::GetInput()
{
	return m_edit;
};

CString spcCInputDialog::GetUpperInput()
{
	CString upperedit = m_edit;
	upperedit.MakeUpper();
	return upperedit;;
};

void spcCInputDialog::SetInput(CString input)
{
	m_edit = input;
};

BEGIN_MESSAGE_MAP(spcCInputDialog, CDialog)
	//{{AFX_MSG_MAP(spcCInputDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCInputDialog message handlers
