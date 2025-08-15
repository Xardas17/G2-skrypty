// spcCObjectSoundDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "spacer.h"
#include "spcCObjectSoundDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCObjectSoundDialog 


spcCObjectSoundDialog::spcCObjectSoundDialog(CWnd* pParent /*=NULL*/)
	: CDialog(spcCObjectSoundDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCObjectSoundDialog)
	m_mult_ranges = 0.0;
	m_mult_volumes = 0.0;
	//}}AFX_DATA_INIT
}


void spcCObjectSoundDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCObjectSoundDialog)
	DDX_Text(pDX, IDC_MULT_RANGES, m_mult_ranges);
	DDX_Text(pDX, IDC_MULT_VOLUMES, m_mult_volumes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCObjectSoundDialog, CDialog)
	//{{AFX_MSG_MAP(spcCObjectSoundDialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCObjectSoundDialog 
