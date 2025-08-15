#if !defined(AFX_spcCListMaterialDlg_H__7E7B2266_384A_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_spcCListMaterialDlg_H__7E7B2266_384A_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCListMaterialDlg.h : header file
//

#include <afxtempl.h>
#include "spcCMatListbox.h"
#include "spcCWindowResizeStyle.h"

/////////////////////////////////////////////////////////////////////////////
// spcCListMaterialDlg dialog


class spcCListMaterialDlg : public CDialog
{
// Construction
public:
	void SelectMaterial(zCMaterial* mat);
	void UpdateFilterList();
	void PreExit();
	void SetDirty(bool dirty = true);
	void Reset();
	bool materialLoaded;
	void UpdateMaterialList(const zSTRING& filterName="");
	void InitData();

	void SaveMatlib(CString filterName);
	void LoadMatlib(CString fname, bool performCheck=false);
	void LoadMatlib();
	spcCListMaterialDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~spcCListMaterialDlg();

// Dialog Data
	//{{AFX_DATA(spcCListMaterialDlg)
	enum { IDD = IDD_LIST_MATS };
	CButton			ctrl_filter_new;
	CButton			ctrl_filter_del;	
	CComboBox		ctrl_filter;
	spcCMatListbox	ctrl_mat_list;
	CString			m_filter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCListMaterialDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	POSITION winID;

	CList<spcCWindowResizeStyle*,spcCWindowResizeStyle*> childResizeList;

	bool isDirty;

	// Generated message map functions
	//{{AFX_MSG(spcCListMaterialDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFilter();
	afx_msg void OnSelchangeMatlist();
	afx_msg void OnDblclkMatlist();	
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnNewFilter();
	afx_msg void OnDelFilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_spcCListMaterialDlg_H__7E7B2266_384A_11D2_8AB9_0080AD209698__INCLUDED_)
