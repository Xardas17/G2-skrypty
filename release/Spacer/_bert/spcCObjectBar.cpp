// spcCObjectBar.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "spacer.h"
#include "mainfrm.h"
#include "spcCObjectBar.h"
#include "spcCConfiguration.h"
// #include "spcCWindowResizeStyle.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCObjectBar 


spcCObjectBar::spcCObjectBar(CWnd* pParent /*=NULL*/)
	: CDialog(spcCObjectBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCObjectBar)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void spcCObjectBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCObjectBar)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCObjectBar, CDialog)
	//{{AFX_MSG_MAP(spcCObjectBar)
	ON_WM_SIZE()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCObjectBar 

BOOL spcCObjectBar::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Fensterposition ermitteln
	winID = spcConfig.GetWindowID("winObjectBar");
	spcTRegWindowInfo winInfo;
	spcConfig.GetWindowPosition(winID,winInfo);
	
	RECT rect;
	GetWindowRect(&rect);

	MoveWindow(
		winInfo.position.pos.x,
		winInfo.position.pos.y,	
		rect.right - rect.left,
		rect.bottom - rect.top,
		TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void spcCObjectBar::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
}

void spcCObjectBar::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	if (winID>0 && IsWindowVisible())
	{
		RECT rect;
		GetWindowRect(&rect);
		spcConfig.SetWindowPosition(winID,rect);
		if (CMainFrame::mainframe) CMainFrame::mainframe->OnMoveChild();
	}
}
