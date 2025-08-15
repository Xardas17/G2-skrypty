#if !defined(AFX_SPCCOBJECTMODIFYPAGE_H__0BF2E1C8_E987_11D3_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_SPCCOBJECTMODIFYPAGE_H__0BF2E1C8_E987_11D3_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCObjectModifyPage.h : Header-Datei
//

#include <afxtempl.h>
#include "zstring.h"
#include "spcCObjPropList.h"

class CImageList;
class spcCWindowResizeStyle;
class spcCObjPropertyElement;

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCObjectModifyPage 

class spcCObjectModifyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(spcCObjectModifyPage)

// Konstruktion
public:	
	bool isEnabled;
	void ClearContents();
	void Enable(bool enabled = true);
	void StopEditBoundingBox();
	void StartEditBoundingBox();
	spcCObjectModifyPage();
	~spcCObjectModifyPage();

	void SetProperties(zSTRING& propString);
	void GetProperties(zSTRING& propString);


// Dialogfelddaten
	//{{AFX_DATA(spcCObjectModifyPage)
	enum { IDD = IDD_OBJECT_MODIFY_PAGE };
		CSpinButtonCtrl	ctrl_dynvalue_spin;

	CStatic	ctrl_edit_area;
	
	CButton		ctrl_editbox;
	CButton		ctrl_string_fileopen;	
	CStatic		ctrl_colorview;
	CButton		ctrl_editcolor;		
	CEdit		ctrl_raw;
	CEdit		ctrl_vec3;
	CEdit		ctrl_vec2;
	CEdit		ctrl_vec1;	
	CEdit		ctrl_value;
	CEdit		ctrl_string;
	CComboBox	ctrl_enum;
	CButton		ctrl_bool;
	CTreeCtrl	ctrl_proptree;
	
	BOOL	m_bool;
	CString	m_enum;
	CString	m_raw;
	CString	m_string;
	CString	m_value;
	CString	m_vec1;
	CString	m_vec2;
	CString	m_vec3;
	
	BOOL	m_edit_bbox;
	//}}AFX_DATA
private:
	COLORREF	m_color;
	bool		b_color;	

private:

	CList<spcCWindowResizeStyle*,spcCWindowResizeStyle*> childResizeList;

	CImageList*			treeCtrlImageList;
	spcCObjPropertyList	propList;
	
	zSTRING		lastClass;		
	zSTRING		objTypeDescriptor;

private:

	void		CreatePropTree();
	void		CreatePropTree(int& n, HTREEITEM parent);	
	HTREEITEM	CreatePropTreeItem(spcCObjPropertyElement* ele, HTREEITEM parent, int nr);
	void		UpdatePropTree(HTREEITEM item);	

	int			selected;
	HTREEITEM	selectTreeItem;
	int			startPos;	

	void		deactivateAll();

	void		activateBool(bool v);
	void		activateValue(float v);
	void		activateEnum(int v);
	void		activateString(CString v);
	void		activateRaw(CString v);
	void		activateVector(zVEC3 v);
	void		activateColor(COLORREF col);

// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCObjectModifyPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:	
	bool CheckStringValue(CString& s);
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCObjectModifyPage)
	afx_msg void OnSelchangedProptree(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnClose();
	virtual void OnCancel();
	afx_msg void OnValChange();	
	afx_msg void OnEditcolor();
	afx_msg void OnPaint();
	afx_msg void OnHelpButton();	
	afx_msg void OnChangeDystring();
	afx_msg void OnChangeDyraw();
	afx_msg void OnChangeDyvalue();
	afx_msg void OnChangeDyvector1();
	afx_msg void OnChangeDyvector2();
	afx_msg void OnChangeDyvector3();
	afx_msg void OnDeltaposDyvalueSpin(NMHDR* pNMHDR, LRESULT* pResult);		
	afx_msg void OnStringFile();
	afx_msg void OnEndlabeleditProptree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditProptree(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnRclickProptree(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnDblclkProptree(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();	
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnEditBbox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCOBJECTMODIFYPAGE_H__0BF2E1C8_E987_11D3_BA4F_0050DA339C1B__INCLUDED_
