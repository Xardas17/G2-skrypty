#if !defined(AFX_spcCVobLogicalDialog_H__FA0E3021_F2B2_11D2_A902_DD27DBE4DE08__INCLUDED_)
#define AFX_spcCVobLogicalDialog_H__FA0E3021_F2B2_11D2_A902_DD27DBE4DE08__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCVobLogicalDialog.h : header file
//


class zCVob;

#include "spcCObjPropList.h"
#include "zString.h"	// Hinzugefügt von der Klassenansicht


/////////////////////////////////////////////////////////////////////////////
// spcCVobLogicalDialog dialog

class spcCVobLogicalDialog : public CDialog
{
// Construction
public:
	spcCVobLogicalDialog(CWnd* pParent = NULL);   // standard constructor

	void SelectVob(zCVob* pickedVob);
	zCVob* InsertVob(const zPOINT3& pos, const zPOINT3& dir, zCVob* vob);

// Dialog Data
	//{{AFX_DATA(spcCVobLogicalDialog)
	enum { IDD = IDD_INFO_LOGICAL };
	CComboBox	ctrl_action_type;
	CButton	ctrl_new_old;
	CProgressCtrl	ctrl_progress;
	CComboBox	ctrl_classselector_nc;
	CComboBox	ctrl_classselector;
	CButton	ctrl_editcolor;
	CButton	ctrl_applybutton;
	CEdit	ctrl_vec3;
	CEdit	ctrl_vec2;
	CEdit	ctrl_vec1;
	CTreeCtrl	ctrl_proptree;
	CEdit	ctrl_value;
	CEdit	ctrl_string;
	CComboBox	ctrl_enum;
	CButton	ctrl_bool;
	BOOL	m_bool;
	CString	m_enum;
	CString	m_string;
	CString	m_value;
	CString	m_vec1;
	CString	m_vec2;
	CString	m_vec3;	
	CString m_replace_zen_file;
	BOOL	m_mode_new;
	BOOL	m_delete_vobs;
	CString	m_classname_nc;
	BOOL	m_effect_derived;
	CString	m_progress_found;			
	//}}AFX_DATA
private:
	COLORREF m_color;
	bool b_color;

private:
	zCVob* cur_vob;
	zCVob* new_vob;
	zSTRING lastClass;
	bool HandleVob		(zCVob*& vob);
	bool HandleVobExt	(zCVob*& vob);

	void SwapObject		(zCVob* vob,zCVob* new_vob);

private:
	spcCObjPropertyList propList;
	spcCObjPropertyList propListNew;
	void createPropTree();
	void createPropTree(int& n, HTREEITEM parent);
	void updatePropTree(HTREEITEM item);
	int selected;
	HTREEITEM selectedProp;
	int startPos;

	void deactivateAll();
	void activateBool(bool v);
	void activateValue(float v);
	void activateEnum(int v);
	void activateString(CString v);
	void activateRaw(CString v);
	void activateVector(zVEC3 v);
	void activateColor(COLORREF col);

	void buildClassHierarchy(zCClassDef *parentClassDef, int depth=1, bool useNCCtrl=false);
	void buildClassHierarchy();

	void UpdateDialogItems();

public:
	zSTRING PickClassname(zSTRING classname);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCVobLogicalDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCVobLogicalDialog)
	afx_msg void OnSelchangedProptree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkProptree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	afx_msg void OnValChange();
	afx_msg void OnDynApply();
	afx_msg void OnEditcolor();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeClassselector();
	afx_msg void OnLogicnewOld();
	afx_msg void OnChangeDyvalue();
	afx_msg void OnChangeDystring();
	afx_msg void OnChangeDyvector1();
	afx_msg void OnChangeDyvector2();
	afx_msg void OnChangeDyvector3();
	virtual BOOL OnInitDialog();
	afx_msg void OnReset();
	afx_msg void OnClickProptree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeActionType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual void OnOK();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCINFOPROPDLG_H__FA0E3021_F2B2_11D2_A902_DD27DBE4DE08__INCLUDED_)
