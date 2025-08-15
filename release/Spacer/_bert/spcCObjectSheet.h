#if !defined(AFX_SPCCOBJECTSHEET_H__CBD18C63_E911_11D3_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_SPCCOBJECTSHEET_H__CBD18C63_E911_11D3_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCObjectSheet.h : Header-Datei
//

#include "spcCObjectModifyPage.h"
#include "spcCObjectCreationPage.h"
#include "spcCObjectManipulatePage.h"

#include "spcCDragVob.h"

extern const char* BUTTON_TEXT_EMPTY;
extern const char* BUTTON_TEXT_CREATE_ACTIVATE;
extern const char* BUTTON_TEXT_MODIFY_APPLY;

/////////////////////////////////////////////////////////////////////////////
// spcCObjectSheet

class spcCObjectSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(spcCObjectSheet)

// Konstruktion
public:
	spcCObjectSheet();
	spcCObjectSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~spcCObjectSheet();
	
	virtual void HandleVobInsert(zCVob* vob, zCVob* parentVob);
	virtual void HandleVobRemove(zCVob* vob);
	virtual void HandleObjSelect(zCObject* obj);
	virtual void HandleObjChange(zCObject* obj);

	void		Init(CString title, CWnd* parentWin);

	void		SelectObject(zCObject* object, zBOOL show = TRUE);	

	void		SetBaseClass(zSTRING class_name);
	zSTRING		GetBaseClass() { return baseClass; };

	void		StopEditBoundingBox();
	void		StartEditBoundingBox();	
	zCVob*		IsEditingBoundingBox();
	void		UpdateEditingBoundingBox();

	void		SetActionButtonText(CString text);		

	zCObject*	CreateNewObject();
	bool		CreateNewObjectCheck(CString& classname);		
	zCObject*	UpdateObjectFromPreset(zCObject* obj);

	zCVob*		GetSelectedVob() { return dynamic_cast<zCVob*>(current_object); };
	zBOOL		GetBoundingbox(zTBBox3D& box);
	zBOOL		SetBoundingbox(zTBBox3D& box);


// Operationen
public:
	void DisableCreationPage(bool disable=true);

	spcCObjectModifyPage		modifyPage;
	spcCObjectCreationPage		creationPage;
	spcCObjectManipulatePage	manipulatePage;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCObjectSheet)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);	
	//}}AFX_VIRTUAL

protected:

	void AddPages();

	//{{AFX_MSG(spcCObjectSheet)
	afx_msg void	OnSize(UINT nType, int cx, int cy);	
	afx_msg void	OnMove(int x, int y);
	afx_msg void	OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnActionButton();		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	CList<spcCWindowResizeStyle*,spcCWindowResizeStyle*> childResizeList;

	POSITION		winID;	
	CButton*		actionButton;
	zCObject*		current_object;
	spcCDragVobCtrl	dragVobCtrl;	
	zSTRING			baseClass;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCOBJECTSHEET_H__CBD18C63_E911_11D3_BA4F_0050DA339C1B__INCLUDED_
