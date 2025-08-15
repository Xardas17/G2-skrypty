// spcCDiagramVPD.cpp: Implementierungsdatei
//
#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCDiagramVPD.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCDiagramVPD 


spcCDiagramVPD::spcCDiagramVPD(CWnd* pParent /*=NULL*/)
	: CDialog(spcCDiagramVPD::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCDiagramVPD)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void spcCDiagramVPD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCDiagramVPD)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCDiagramVPD, CDialog)
	//{{AFX_MSG_MAP(spcCDiagramVPD)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCDiagramVPD 
