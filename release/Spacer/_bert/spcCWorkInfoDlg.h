#if !defined(AFX_spcCWorkInfoDlg_H__57642FE3_2E0A_11D2_88A8_0080AD209698__INCLUDED_)
#define AFX_spcCWorkInfoDlg_H__57642FE3_2E0A_11D2_88A8_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCWorkInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCWorkInfoDlg dialog

class spcCWorkInfoDlg : public CDialog
{
// Construction
public:
	void Init();
	void Finished();
	void AddMessage(CString s);
	spcCWorkInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~spcCWorkInfoDlg();

// Dialog Data
	//{{AFX_DATA(spcCWorkInfoDlg)
	enum { IDD = IDD_WORK_INFO_DLG };	
	CEdit	ctrl_log;
	CString	text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCWorkInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCWorkInfoDlg)
	afx_msg void OnClose();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_spcCWorkInfoDlg_H__57642FE3_2E0A_11D2_88A8_0080AD209698__INCLUDED_)
