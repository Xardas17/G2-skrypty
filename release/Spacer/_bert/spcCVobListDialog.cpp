// spcCVobListDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCVobListDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCVobListDialog 


spcCVobListDialog::spcCVobListDialog(CWnd* pParent /*=NULL*/)
	: CDialog(spcCVobListDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCVobListDialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void spcCVobListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCVobListDialog)
	DDX_Control(pDX, IDC_VOB_LIST, ctrl_vob_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCVobListDialog, CDialog)
	//{{AFX_MSG_MAP(spcCVobListDialog)
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCVobListDialog 

void spcCVobListDialog::OnSize(UINT nType, int cx, int cy) 
{	
	CDialog::OnSize(nType, cx, cy);
	
	ctrl_vob_list.MoveWindow(0,0,cx,cy);
	
}

BOOL spcCVobListDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	HTREEITEM handleRoot = ctrl_vob_list.InsertItem("Root",0,0,TVI_ROOT);
	/*	HTREEITEM handleChild1*/ ctrl_vob_list.InsertItem("Child1",0,0,handleRoot);
		HTREEITEM handleChild2 = ctrl_vob_list.InsertItem("Child2",0,0,handleRoot);
		/*	HTREEITEM handleChild21*/ ctrl_vob_list.InsertItem("Child2.1",0,0,handleChild2);
		/*	HTREEITEM handleChild22*/ ctrl_vob_list.InsertItem("Child2.2",0,0,handleChild2);
		/*	HTREEITEM handleChild23*/ ctrl_vob_list.InsertItem("Child2.3",0,0,handleChild2);
	/*	HTREEITEM handleChild3*/ ctrl_vob_list.InsertItem("Child3",0,0,handleRoot);
		HTREEITEM handleChild4 = ctrl_vob_list.InsertItem("Child4",0,0,handleRoot);
		/*	HTREEITEM handleChild41*/ ctrl_vob_list.InsertItem("Child4.1",0,0,handleChild4);
		/*	HTREEITEM handleChild42*/ ctrl_vob_list.InsertItem("Child4.2",0,0,handleChild4);
		/*	HTREEITEM handleChild43*/ ctrl_vob_list.InsertItem("Child4.3",0,0,handleChild4);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void spcCVobListDialog::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CDialog::OnLButtonDblClk(nFlags, point);
}
