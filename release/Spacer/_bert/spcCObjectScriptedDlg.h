#if !defined(AFX_SPCCOBJECTSCRIPTEDDLG_H__49FD3021_F061_11D3_A405_0080AD209698__INCLUDED_)
#define AFX_SPCCOBJECTSCRIPTEDDLG_H__49FD3021_F061_11D3_A405_0080AD209698__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCObjectScriptedDlg.h : Header-Datei
//

#include "zobject.h"
#include "zstring.h"
#include "zcontainer.h"
// #include "spcCLabel.h"

class zCView;
class zCWorld;
class zCVob;
class spcCDibSection;

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCObjectScriptedDlg 

class spcCObjectScriptedDlg : public CDialog
{
// Konstruktion
public:
	spcCObjectScriptedDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	~spcCObjectScriptedDlg();

	void	SetObjectClass(zSTRING _classname);
	zSTRING GetObjectInstance();
	zSTRING GetObjectName();	
	
// Dialogfelddaten
	//{{AFX_DATA(spcCObjectScriptedDlg)
	enum { IDD = IDD_OBJECT_SRIPTED_DLG };
	// DEACTIVATED: CStatic		ctrl_viewport;
	CListBox	ctrl_list;
	CEdit		ctrl_objecttype;
	CButton		ctrl_insert;	
	CString		m_object_name;
	CString		m_object_type;
	CString		m_selected_instance;
	//}}AFX_DATA

	SIZE		view_size;
	RECT		view_rect;
	zCView*		dtp_item;	
	// DEACTIVATED: zCWorld*	world;		
	spcCDibSection*		dib;	
	zCVob*		vob;
	bool		mouse_down;
	CPoint		lastpoint;
	
	zSTRING		classname;	
	zCClassDef*	classDef;
	zCList<zSTRING> instance_list;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCObjectScriptedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCObjectScriptedDlg)
	virtual void OnCancel();
	afx_msg void OnInsertObject();
	afx_msg void OnDblclkInstanceList();
	afx_msg void OnSelchangeInstanceList();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCOBJECTSCRIPTEDDLG_H__49FD3021_F061_11D3_A405_0080AD209698__INCLUDED_
