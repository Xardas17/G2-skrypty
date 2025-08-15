#if !defined(AFX_SPCCINPUTDIALOG_H__6914A9A1_3E85_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_SPCCINPUTDIALOG_H__6914A9A1_3E85_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCInputDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCInputDialog dialog

class spcCInputDialog : public CDialog
{
// Construction
public:
	spcCInputDialog(CWnd* pParent = NULL);   // standard constructor

	void SetInput(CString input);
	CString GetInput();
	CString GetUpperInput();

// Dialog Data
	//{{AFX_DATA(spcCInputDialog)
	enum { IDD = IDD_INPUT_DLG };
	//}}AFX_DATA

	CString	m_edit;
	CString	m_text;
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCInputDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCInputDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCINPUTDIALOG_H__6914A9A1_3E85_11D2_8AB9_0080AD209698__INCLUDED_)
