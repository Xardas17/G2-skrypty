#if !defined(AFX_SPCCNEWMATERIALDIALOG_H__993B7EA8_E08D_11D3_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_SPCCNEWMATERIALDIALOG_H__993B7EA8_E08D_11D3_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCNewMaterialDialog.h : Header-Datei
//

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCNewMaterialDialog 

class spcCNewMaterialDialog : public CDialog
{
// Konstruktion
	CList<CString, CString> list;
public:
	void AddFilter(CString filtername);
	int GetSelection(CString& sel_string);
	spcCNewMaterialDialog(CWnd* pParent = NULL);   // Standardkonstruktor

	enum { NONE, SELECT, NEW} selection;
// Dialogfelddaten
	//{{AFX_DATA(spcCNewMaterialDialog)
	enum { IDD = IDD_NEW_MATERIALS_DIALOG };
	CComboBox	ctrl_select_filter;
	CEdit	ctrl_new_filter;
	CString	m_new_filter;
	CString	m_select_filter;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCNewMaterialDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCNewMaterialDialog)
	afx_msg void OnSelFilter();
	afx_msg void OnSelNewFilter();
	afx_msg void OnSelNone();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCNEWMATERIALDIALOG_H__993B7EA8_E08D_11D3_BA4F_0050DA339C1B__INCLUDED_
