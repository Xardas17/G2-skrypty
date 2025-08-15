// spcCConsoleDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCConsoleDialog.h"
#include "zconsole.h"
#include "zstring.h"
#include "zerror.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCConsoleDialog 


spcCConsoleDialog::spcCConsoleDialog(CWnd* pParent /*=NULL*/)
	: CDialog(spcCConsoleDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCConsoleDialog)
	m_input = _T("");
	m_output = _T("");
	m_autocomplete = TRUE;
	//}}AFX_DATA_INIT
}


void spcCConsoleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCConsoleDialog)
	DDX_Control(pDX, IDC_INPUT, ctrl_input);
	DDX_Text(pDX, IDC_INPUT, m_input);
	DDX_Text(pDX, IDC_OUTPUT, m_output);
	DDX_Check(pDX, IDC_AUTOCOMPLETE, m_autocomplete);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCConsoleDialog, CDialog)
	//{{AFX_MSG_MAP(spcCConsoleDialog)
	ON_EN_UPDATE(IDC_INPUT, OnUpdateInput)
	ON_BN_CLICKED(ID_CLOSEDLG, OnClosedlg)
	ON_EN_CHANGE(IDC_INPUT, OnChangeInput)
	ON_BN_CLICKED(IDC_AUTOCOMPLETE, OnAutocomplete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCConsoleDialog 

void spcCConsoleDialog::OnUpdateInput() 
{	
}

void spcCConsoleDialog::OnClosedlg() 
{
	CDialog::OnOK();
}

void spcCConsoleDialog::OnOK() 
{
	UpdateData(TRUE);	
	zSTRING coninput  = zSTRING(m_input.GetBuffer(0));	
	coninput.Upper();
	zBOOL bCouldExecute = zcon.Evaluate(coninput);
	zSTRING conoutput = zcon.GetLastResult();

	if (!bCouldExecute && (conoutput=="OK" || conoutput=="ok" || conoutput.IsEmpty()) ) 
		conoutput = "unknown command";
	
	CString s = "Command: \""+m_input + "\": " + CString(conoutput.ToChar());
	
	m_output = s + "\r\n"+m_output;
	
	m_input = "";
	UpdateData(FALSE);	
	ctrl_input.SetFocus();
}

void spcCConsoleDialog::OnChangeInput() 
{	
	if (m_autocomplete)
	{
		UpdateData(TRUE);
		zSTRING s = zSTRING(m_input.GetBuffer(0));
		zcon.AutoCompletion(s);
		m_input = CString(s.ToChar());		
		UpdateData(FALSE);	
		POINT pt;pt.x = 10000; pt.y=10000;
		ctrl_input.SendMessage(WM_KEYDOWN,VK_END,0);
		ctrl_input.SendMessage(WM_KEYUP,VK_END,0);		
	}	
}

void spcCConsoleDialog::OnAutocomplete() 
{
	UpdateData(TRUE);	
	zcon.SetAutoCompletion(m_autocomplete);	
	ctrl_input.SetFocus();
	UpdateData(FALSE);	
}

BOOL spcCConsoleDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ctrl_input.SetFocus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
