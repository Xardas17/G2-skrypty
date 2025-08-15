// spcCTextInfoDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCTextInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCTextInfoDlg 


spcCTextInfoDlg::spcCTextInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCTextInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCTextInfoDlg)
	m_contents = _T("");
	//}}AFX_DATA_INIT
}


void spcCTextInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCTextInfoDlg)
	DDX_Text(pDX, IDC_CONTENTS, m_contents);
	//}}AFX_DATA_MAP
}

int	spcCTextInfoDlg::DoModal()
{	
	return CDialog::DoModal();
};

BEGIN_MESSAGE_MAP(spcCTextInfoDlg, CDialog)
	//{{AFX_MSG_MAP(spcCTextInfoDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCTextInfoDlg 

