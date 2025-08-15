#if !defined(AFX_spcCListVobDlg_H__7E7B2267_384A_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_spcCListVobDlg_H__7E7B2267_384A_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCListVobDlg.h : header file
//

#include <afxext.h>
#include <afxtempl.h>
#include "spcCWindowResizeStyle.h"
#include <spcCVobTreeItemList.h>


class zCVob;
class zCWorld;

/////////////////////////////////////////////////////////////////////////////
// spcCBrowseVobs window

// CTreeCtrl

/////////////////////////////////////////////////////////////////////////////
// spcCListVobDlg dialog


class spcCListVobDlg : public CDialog
{
// Construction
public:	
	CString GetFolderName(zCVob* vob);

	enum { ICON_FOLDER, ICON_VOB, ICON_VOB_NEW, ICON_VOB_ROOT, ICON_LEVCOMP, ICON_VOB_UNKNOWN };
	
	spcCListVobDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~spcCListVobDlg();

	
	virtual void HandleVobSelect(zCVob* vob);
	virtual void HandleVobInsert(zCVob* vob, zCVob* parentVob);
	virtual void HandleVobRemove(zCVob* vob);
	virtual void HandleVobChange(zCVob* vob);

	
	zCWorld*			current_world;
	
	HTREEITEM CD_hItem;
	HTREEITEM hItemMainVob;
	
	void Reset();
	void CDremoveTree();
	void CDaddVob(zCVob* vob);
	void CDcreateTree();
	void BuildTree(zCWorld* world);
	void VobSelect(zCVob* vob);
	void VobDelete(zCVob* vob);	
	void VobDeleteRec(zCVob * vob);
	
	HTREEITEM VobInsert(zCVob* newvob, zCVob* parentvob);

// Dialog Data
	//{{AFX_DATA(spcCListVobDlg)
	enum { IDD = IDD_LIST_VOBS };	
	CButton	ctrl_sorted;
	CButton	ctrl_refresh;
	CButton	ctrl_action;
	CButton	ctrl_printbutton;	
	CTreeCtrl	ctrl_browse;	
	BOOL	m_sorted;	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCListVobDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	POSITION winID;

	CList<spcCWindowResizeStyle*,spcCWindowResizeStyle*> childResizeList;
	
	bool updateAll;

protected:

	CString		GetVobItemName(zCVob* vob);
	
	HTREEITEM	GetFolder(zCVob* vob, HTREEITEM parent);
	HTREEITEM	CreateVobTreeItem  (zCVob* vob, HTREEITEM parent, int icon_type=-1);
	HTREEITEM	CreateVobTreeFolder(CString name, HTREEITEM parent, int icon_type=-1);

	HTREEITEM	GetHandleByVob(zCVob* vob);
	HTREEITEM	GetFolderByVob(zCVob* _vob, zCVob* folderVob);
	
	void		CreateBaseVobTree(zCTree<zCVob>* node, HTREEITEM parent);
	void		CreateVobTree(zCTree<zCVob>* node, HTREEITEM parent);
	
	zCVob*				GetVobByHandle(HTREEITEM hItem);
	
	// Generated message map functions
	//{{AFX_MSG(spcCListVobDlg)
	afx_msg void OnVoblistDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVoblistDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVoblistSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRefresh();		
	afx_msg void OnSetfocusVobList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPrintToFile();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnMove(int x, int y);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClickVobList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	CImageList*			treeCtrlImageList;
	spcCVobTreeItemList	voblist;
	CMapStringToPtr		folderList;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_spcCListVobDlg_H__7E7B2267_384A_11D2_8AB9_0080AD209698__INCLUDED_)
