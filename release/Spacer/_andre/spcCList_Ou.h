#if !defined(AFX_spcCListCutsceneDlg_H__6D0E8221_952D_11D2_A902_DD27DBE4DE08__INCLUDED_)
#define AFX_spcCListCutsceneDlg_H__6D0E8221_952D_11D2_A902_DD27DBE4DE08__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCListCutsceneDlg.h : header file
//


#include "spcCWindowResizeStyle.h"


/////////////////////////////////////////////////////////////////////////////
// behelfsklasse

class zCCSBlock;
class zCCSBlockBase;

class COutputUnit
{
public:
	int type;
	zSTRING file;
	zSTRING bez;
	int lEntry;
	zSTRING rem;
	zCCSBlock* block;
};



/////////////////////////////////////////////////////////////////////////////
// spcCListCutsceneDlg dialog

class spcCListCutsceneDlg : public CDialog
{
private:
	zCArray<COutputUnit> ous;  // alle OUs einer Sprache
	int selected;				// selected in ctrl_ou_list
	
	bool changesOnCheck;

// Construction
public:
	void UpdateList();
	spcCListCutsceneDlg(CWnd* pParent = NULL);   // standard constructor
	
// my
	void InitData		();
	void Extracttext	();
	void Importtext		( CString & importFile );
	void UpdateSelected	();
	void OUHack			();
	void CheckWithScripts();
	void UpdateWithScripts();

	void ConstructList	();
	void UpdateChanges	();

	zSTRING LanguageGrammalog(int nr);

	zCCSBlockBase* GetSelected();

// Dialog Data
	//{{AFX_DATA(spcCListCutsceneDlg)
	enum { IDD = IDD_LIST_OUS };
	CButton	ctrl_button_load;
	CButton	ctrl_button_test;
	CButton	ctrl_update_ou;	
	CButton	ctrl_button_save;
	CButton	ctrl_button_refresh;
	CButton	ctrl_button_delete;	
	CEdit			ctrl_search_edit;	
	CComboBox	ctrl_language_list;
	CListBox	ctrl_ou_list;
	// CComboBox	ctrl_ou_filter;
	// CString	m_ou_filter;
	int		m_language;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCListCutsceneDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	POSITION winID;

	CList<spcCWindowResizeStyle*,spcCWindowResizeStyle*> childResizeList;
	
	// Generated message map functions
	//{{AFX_MSG(spcCListCutsceneDlg)
	afx_msg void OnSelchangeOuFilter();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeOuLanguage();
	afx_msg void OnOuRefresh();
	afx_msg void OnSelchangeOuList();
	afx_msg void OnDblclkOuList();
	afx_msg void OnDeleteOu();
	afx_msg void OnNewOu();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSave();
	afx_msg void OnOuStart();
	afx_msg void OnChangeSearch();
	afx_msg void OnCutsceneUpdateOU();
	afx_msg void OnTest();
	afx_msg void OnLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_spcCListCutsceneDlg_H__6D0E8221_952D_11D2_A902_DD27DBE4DE08__INCLUDED_)
