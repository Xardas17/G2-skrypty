// spcCPositionDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCPositionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCPositionDlg 


spcCPositionDlg::spcCPositionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCPositionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCPositionDlg)
	m_edit_x = 0.0;
	m_edit_y = 0.0;
	m_edit_z = 0.0;
	m_levelname = _T("");
	m_at_x = 0.0;
	m_at_y = 0.0f;
	m_at_z = 0.0f;
	//}}AFX_DATA_INIT
}


void spcCPositionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCPositionDlg)
	DDX_Text(pDX, IDC_EDIT_X, m_edit_x);
	DDX_Text(pDX, IDC_EDIT_Y, m_edit_y);
	DDX_Text(pDX, IDC_EDIT_Z, m_edit_z);
	DDX_Text(pDX, IDC_LEVELNAME, m_levelname);
	DDX_Text(pDX, IDC_AT_X, m_at_x);
	DDX_Text(pDX, IDC_AT_Y, m_at_y);
	DDX_Text(pDX, IDC_AT_Z, m_at_z);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCPositionDlg, CDialog)
	//{{AFX_MSG_MAP(spcCPositionDlg)
	ON_BN_CLICKED(IDC_CLIPBOARD, OnClipboard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCPositionDlg 

void spcCPositionDlg::OnClipboard() 
{	
	UpdateData(false);
	CString s;
	s.Format("%s <%f, %f, %f> at <%f, %f, %f>",m_levelname,m_edit_x,m_edit_y,m_edit_z, m_at_x, m_at_y, m_at_z);

	LPTSTR  lptstrCopy;
	HGLOBAL hglbCopy;
    
	if (!AfxGetMainWnd()->OpenClipboard()) return; 
	EmptyClipboard();  
    
	// Allocate a global memory object for the text.  
    hglbCopy = GlobalAlloc(GMEM_DDESHARE, (s.GetLength()+1) * sizeof(TCHAR));
	if (hglbCopy == NULL) { CloseClipboard();return; }  
    // Lock the handle and copy the text to the buffer.  
    lptstrCopy = (LPTSTR)GlobalLock(hglbCopy); 
    memcpy(lptstrCopy, s.GetBuffer(0), s.GetLength() * sizeof(TCHAR)); 
    lptstrCopy[s.GetLength()] = (TCHAR) 0;    // null character 
    GlobalUnlock(hglbCopy);          // Place the handle on the clipboard.  
    SetClipboardData(CF_TEXT, hglbCopy); 
	CloseClipboard();
}
