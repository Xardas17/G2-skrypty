#if !defined(AFX_SPCCOBJECTCREATIONPAGE_H__0BF2E1C9_E987_11D3_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_SPCCOBJECTCREATIONPAGE_H__0BF2E1C9_E987_11D3_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCObjectCreationPage.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCObjectCreationPage 


#include <afxtempl.h>
#include "spcCObjPropList.h"


class zCClassDef;
class zCObject;
class spcCVobPropertyElement;
class zCPresetView;
class spcCWindowResizeStyle;
class zCObjPreset;

class spcCObjectCreationPage : public CPropertyPage
{
	DECLARE_DYNCREATE(spcCObjectCreationPage)

// Konstruktion
public:	
	bool isEnabled;
	spcCObjectCreationPage();
	~spcCObjectCreationPage();	

	void		Enable(bool enabled = true);	

	zCObject*	CreateNewObject();
	zCObject*	CreateNewObjectFromScript(CString presetname);
	zCObject*	CreateNewObjectFromPreset(CString presetname);
	zCObject*	UpdateObjectFromPreset(zCObject* obj);

	bool		SetBaseClass(zSTRING class_name);

	CString		GetSelectedClassName();
	CString		GetSelectedPresetName();
	
	void		DeletePreset(CString name);
	void		RenamePreset(CString oldname, CString newname);

// Dialogfelddaten
	//{{AFX_DATA(spcCObjectCreationPage)
	enum { IDD = IDD_OBJECT_CREATION_PAGE };
	CButton		ctrl_tools_del;
	CButton		ctrl_tools_export;
	CListCtrl	ctrl_presetlist;
	CTreeCtrl	ctrl_classtree;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCObjectCreationPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL


protected:	

	void		ShowPopupMenue(CPoint point);
	void		BuildClassHierarchy(HTREEITEM parent, zCClassDef *parentClassDef);
	void		BuildClassHierarchy();

	void		CreatePresetList(CString classname="");	

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCObjectCreationPage)
	afx_msg void OnSelchangedClasstree(NMHDR* pNMHDR, LRESULT* pResult);		
	afx_msg void OnClose();
	virtual void OnCancel();
	afx_msg void OnRclickClasstree(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnDblclkClasstree(NMHDR* pNMHDR, LRESULT* pResult);		
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	virtual BOOL OnInitDialog();	
	afx_msg void OnRclickPresetlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownPresetlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditPresetlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditPresetlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnExportPresets();
	afx_msg void OnDelPreset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	CList<spcCWindowResizeStyle*,spcCWindowResizeStyle*> childResizeList;
				
	zCPresetView*	presetView;
	zSTRING			base_class_name;
	CString			presetname_in_work;	

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCOBJECTCREATIONPAGE_H__0BF2E1C9_E987_11D3_BA4F_0050DA339C1B__INCLUDED_
