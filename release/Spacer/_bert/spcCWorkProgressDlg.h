#if !defined(AFX_spcCWorkProgressDlg_H__CDAC0BE1_DDFB_11D2_A902_DD27DBE4DE08__INCLUDED_)
#define AFX_spcCWorkProgressDlg_H__CDAC0BE1_DDFB_11D2_A902_DD27DBE4DE08__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCWorkProgressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCWorkProgressDlg dialog

class spcCWorkProgressDlg : public CDialog
{
// Construction
public:
	spcCWorkProgressDlg(CWnd* pParent = NULL);   // standard constructor

	void SetPos(int pos);
	void Step(int rel);
	void Init(int min, int max);

// Dialog Data
	//{{AFX_DATA(spcCWorkProgressDlg)
	enum { IDD = IDD_WORK_PROGRESS_DLG };
	CProgressCtrl	m_progression;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCWorkProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCWorkProgressDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_spcCWorkProgressDlg_H__CDAC0BE1_DDFB_11D2_A902_DD27DBE4DE08__INCLUDED_)
