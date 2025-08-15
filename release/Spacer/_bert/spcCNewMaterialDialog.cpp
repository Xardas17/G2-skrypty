// spcCNewMaterialDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCNewMaterialDialog.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCNewMaterialDialog 


spcCNewMaterialDialog::spcCNewMaterialDialog(CWnd* pParent /*=NULL*/)
	: CDialog(spcCNewMaterialDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCNewMaterialDialog)
	m_new_filter = _T("");
	m_select_filter = _T("");
	//}}AFX_DATA_INIT
}


void spcCNewMaterialDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCNewMaterialDialog)
	DDX_Control(pDX, IDC_SELECT_FILTER, ctrl_select_filter);
	DDX_Control(pDX, IDC_NEW_FILTER, ctrl_new_filter);
	DDX_Text(pDX, IDC_NEW_FILTER, m_new_filter);
	DDX_CBString(pDX, IDC_SELECT_FILTER, m_select_filter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCNewMaterialDialog, CDialog)
	//{{AFX_MSG_MAP(spcCNewMaterialDialog)
	ON_BN_CLICKED(IDC_SEL_FILTER, OnSelFilter)
	ON_BN_CLICKED(IDC_SEL_NEW_FILTER, OnSelNewFilter)
	ON_BN_CLICKED(IDC_SEL_NONE, OnSelNone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCNewMaterialDialog 

void spcCNewMaterialDialog::OnSelFilter() 
{

	ctrl_new_filter.EnableWindow(false);
	ctrl_select_filter.EnableWindow(true);
	selection = SELECT;
}

void spcCNewMaterialDialog::OnSelNewFilter() 
{
	ctrl_new_filter.EnableWindow(true);
	ctrl_select_filter.EnableWindow(false);
	selection = NEW;
}

void spcCNewMaterialDialog::OnSelNone() 
{
	ctrl_new_filter.EnableWindow(false);
	ctrl_select_filter.EnableWindow(false);
	selection = NONE;
}

int spcCNewMaterialDialog::GetSelection(CString& sel_string)
{	
	sel_string = "";
	switch (selection)
	{
	case NEW:		sel_string = m_new_filter;break;
	case SELECT:	sel_string = m_select_filter;break;
	};
	return selection;
}

BOOL spcCNewMaterialDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	bool first = true;
	CString entry;
	POSITION pos = list.GetHeadPosition();
	while (pos)
	{
		entry = list.GetNext(pos);		
		ctrl_select_filter.AddString(entry);
		if (first) { ctrl_select_filter.SelectString(0,entry);first = false; }		
	};	

	ctrl_new_filter.EnableWindow(false);
	ctrl_select_filter.EnableWindow(false);
	selection = NONE;		

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void spcCNewMaterialDialog::AddFilter(CString filtername)
{	
	list.AddTail(filtername);
	// ctrl_select_filter.AddString(filtername);
}
