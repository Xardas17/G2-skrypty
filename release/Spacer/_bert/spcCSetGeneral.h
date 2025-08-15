#if !defined(AFX_SPCCSETGENERAL_H__E316B1A4_3230_11D2_88A8_0080AD209698__INCLUDED_)
#define AFX_SPCCSETGENERAL_H__E316B1A4_3230_11D2_88A8_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCSetGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCSetGeneral dialog

class spcCSetGeneral : public CDialog
{
// Construction
public:
	spcCSetGeneral(CWnd* pParent = NULL);   // standard constructor

	int m_movespeed;

	void SetMovespeed(int value);
	int  GetMovespeed();

// Dialog Data
	//{{AFX_DATA(spcCSetGeneral)
	enum { IDD = IDD_SETTINGS_GENERAL };
	CButton	ctrl_use_tex_grid;
	CSliderCtrl		ctrl_movespeed;
	BOOL	m_use_grid;
	float	m_rot_grid;
	int		m_move_grid;
	int		m_tex_move_grid;
	BOOL	m_tex_use_grid;
	float	m_tex_rot_grid;
	BOOL	m_interative_save;
	BOOL	m_goldmaster;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCSetGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCSetGeneral)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnUseTexGrid();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCSETGENERAL_H__E316B1A4_3230_11D2_88A8_0080AD209698__INCLUDED_)
