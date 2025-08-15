#if !defined(AFX_SPCCMESSAGEDIALOG_H__F9AA3DE4_3F6B_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_SPCCMESSAGEDIALOG_H__F9AA3DE4_3F6B_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCMessageDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCMessageDialog dialog

class spcCMessageDialog : public CDialog
{
// Construction
public:
	void SetText(CString _text);
	 ~spcCMessageDialog();
	static spcCMessageDialog* dlg;
	spcCMessageDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(spcCMessageDialog)
	enum { IDD = IDD_MESSAGE_DLG };
	CListBox	ctrl_proplist;
	CString	m_text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCMessageDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCMessageDialog)
	virtual void OnOK();
	afx_msg void OnSelchangePropList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCMESSAGEDIALOG_H__F9AA3DE4_3F6B_11D2_8AB9_0080AD209698__INCLUDED_)
