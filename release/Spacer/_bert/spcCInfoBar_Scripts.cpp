// spcCInfoBar_Scripts.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCInfoBar_Scripts.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Scripts dialog


spcCInfoBar_Scripts::spcCInfoBar_Scripts(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInfoBar_Scripts::IDD, pParent)
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Constructing Instance of ScriptsPage...");

	//{{AFX_DATA_INIT(spcCInfoBar_Scripts)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	zERR_MESSAGE(7,zERR_END,"");
}

spcCInfoBar_Scripts::~spcCInfoBar_Scripts()
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing ScriptPage-Instance...");
	zERR_MESSAGE(7,zERR_END,"");
};

void spcCInfoBar_Scripts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInfoBar_Scripts)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCInfoBar_Scripts, CDialog)
	//{{AFX_MSG_MAP(spcCInfoBar_Scripts)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Scripts message handlers
