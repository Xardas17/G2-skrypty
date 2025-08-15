#if !defined(AFX_SPCCINFOBAR_SCRIPTS_H__279ABC41_9019_11D2_A902_DD27DBE4DE08__INCLUDED_)
#define AFX_SPCCINFOBAR_SCRIPTS_H__279ABC41_9019_11D2_A902_DD27DBE4DE08__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCInfoBar_Scripts.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Scripts dialog

class spcCInfoBar_Scripts : public CDialog
{
// Construction
public:
	spcCInfoBar_Scripts(CWnd* pParent = NULL);   // standard constructor
	virtual ~spcCInfoBar_Scripts();

// Dialog Data
	//{{AFX_DATA(spcCInfoBar_Scripts)
	enum { IDD = IDD_INFO_SCRIPTS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCInfoBar_Scripts)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCInfoBar_Scripts)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCINFOBAR_SCRIPTS_H__279ABC41_9019_11D2_A902_DD27DBE4DE08__INCLUDED_)
