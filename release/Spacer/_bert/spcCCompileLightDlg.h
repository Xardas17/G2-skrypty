#if !defined(AFX_spcCCompileLightDlg_H__E5FEB9A0_4016_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_spcCCompileLightDlg_H__E5FEB9A0_4016_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCCompileLightDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCCompileLightDlg dialog

class spcCCompileLightDlg : public CDialog
{
// Construction
public:
	spcCCompileLightDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(spcCCompileLightDlg)
	enum { IDD = IDD_COMPILE_LIGHT_DLG };
	CButton	ctrl_region;
	CEdit	ctrl_region_value;
	int		m_light_quality;
	BOOL	m_region_compile;
	int		m_region_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCCompileLightDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCCompileLightDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRegion();
	afx_msg void OnLight1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_spcCCompileLightDlg_H__E5FEB9A0_4016_11D2_8AB9_0080AD209698__INCLUDED_)
