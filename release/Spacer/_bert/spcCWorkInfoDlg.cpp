// spcCWorkInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "zengine.h"
#include "Spacer.h"
#include "spcCWorkInfoDlg.h"

// z
#include "zstring.h"
#include "zerror.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCWorkInfoDlg dialog


spcCWorkInfoDlg::spcCWorkInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCWorkInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCWorkInfoDlg)
	text = _T("");
	//}}AFX_DATA_INIT
}


void spcCWorkInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCWorkInfoDlg)	
	DDX_Control(pDX, IDC_LOG, ctrl_log);
	DDX_Text(pDX, IDC_LOG, text);
	//}}AFX_DATA_MAP
}

spcCWorkInfoDlg::~spcCWorkInfoDlg()
{
	DestroyWindow();
};

BEGIN_MESSAGE_MAP(spcCWorkInfoDlg, CDialog)
	//{{AFX_MSG_MAP(spcCWorkInfoDlg)
	ON_WM_CLOSE()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCWorkInfoDlg message handlers

void spcCWorkInfoDlg::AddMessage(CString s)
{	
	UpdateData(TRUE);		
	if (text.GetLength()>5000) text.Delete(0,2500);
	text = text + "\r\n" + s;	
	UpdateData(FALSE);	
	ctrl_log.LineScroll(1000000);
}

void spcCWorkInfoDlg::Finished()
{	
	UpdateData(FALSE);
}

void spcCWorkInfoDlg::OnClose() 
{
	CDialog::OnClose();
	// DestroyWindow();
}

void spcCWorkInfoDlg::OnCancel() 
{

}

void spcCWorkInfoDlg::Init()
{	
	Create(IDD_WORK_INFO_DLG,NULL);	
	ShowWindow(SW_SHOWNORMAL);	
}

// [EDENFELD] neu 1.33 aus ModSource
const WINDOW_FRAME = 0;
BOOL spcCWorkInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	RECT systemRect;
	SystemParametersInfo(SPI_GETWORKAREA,0,&systemRect,0);

	RECT rect;
	GetWindowRect(&rect);
	int height = rect.bottom-rect.top;
	int width = rect.right-rect.left;
	SetWindowPos(&wndTopMost,systemRect.right - width - WINDOW_FRAME,systemRect.bottom-height-WINDOW_FRAME,width,height,0);
	// SetWindowPos(&wndTop,0,0,width,height,0);	
	
	return TRUE; 
}

void spcCWorkInfoDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
}
