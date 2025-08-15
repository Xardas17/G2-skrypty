// spcCBBoxDefineDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "spacer.h"
#include "spcCBBoxDefineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCBBoxDefineDlg 


spcCBBoxDefineDlg::spcCBBoxDefineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCBBoxDefineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCBBoxDefineDlg)
	m_dx = 0.0f;
	m_dy = 0.0f;
	m_dz = 0.0f;
	//}}AFX_DATA_INIT
}


void spcCBBoxDefineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCBBoxDefineDlg)
	DDX_Text(pDX, IDC_DX, m_dx);
	DDX_Text(pDX, IDC_DY, m_dy);
	DDX_Text(pDX, IDC_DZ, m_dz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCBBoxDefineDlg, CDialog)
	//{{AFX_MSG_MAP(spcCBBoxDefineDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCBBoxDefineDlg 
