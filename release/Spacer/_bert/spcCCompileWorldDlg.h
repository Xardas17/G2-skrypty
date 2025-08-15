#if !defined(AFX_spcCCompileWorldDlg_H__84F4C9A1_3108_11D2_88A8_0080AD209698__INCLUDED_)
#define AFX_spcCCompileWorldDlg_H__84F4C9A1_3108_11D2_88A8_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCCompileWorldDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCCompileWorldDlg dialog

class spcCCompileWorldDlg : public CDialog
{
// Construction
public:
	spcCCompileWorldDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(spcCCompileWorldDlg)
	enum { IDD = IDD_COMPILE_WORLD_DLG };
	BOOL	m_quick_compile;
	BOOL	m_detect_leaks;
	int		m_inout_door;
	BOOL	m_editormode;
	BOOL	m_polycheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCCompileWorldDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCCompileWorldDlg)
	afx_msg void OnCompile();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_spcCCompileWorldDlg_H__84F4C9A1_3108_11D2_88A8_0080AD209698__INCLUDED_)
