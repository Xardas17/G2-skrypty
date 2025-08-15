// spcCCSSettingDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Spacer.h"
#include "spcCCSSettingDlg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCCSSettingDlg 


spcCCSSettingDlg::spcCCSSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCCSSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCCSSettingDlg)
	m_loopable = FALSE;
	//}}AFX_DATA_INIT
}


void spcCCSSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCCSSettingDlg)
	DDX_Check(pDX, IDC_LOOPABLE, m_loopable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCCSSettingDlg, CDialog)
	//{{AFX_MSG_MAP(spcCCSSettingDlg)
	ON_COMMAND(ID_CSPROPS, OnCsprops)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCCSSettingDlg 

void spcCCSSettingDlg::OnCsprops() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	
}
