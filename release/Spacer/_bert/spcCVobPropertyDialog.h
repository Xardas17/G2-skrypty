#if !defined(AFX_SPCCVOBPROPERTYDIALOG_H__DC7DD6C1_E66B_11D3_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_SPCCVOBPROPERTYDIALOG_H__DC7DD6C1_E66B_11D3_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCVobPropertyDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCVobPropertyDialog 

class spcCVobPropertyDialog : public CDialog
{
// Konstruktion
public:
	spcCVobPropertyDialog(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(spcCVobPropertyDialog)
	enum { IDD = IDD_VOB_PROPERTY_DLG };	
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCVobPropertyDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCVobPropertyDialog)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCVOBPROPERTYDIALOG_H__DC7DD6C1_E66B_11D3_BA4F_0050DA339C1B__INCLUDED_
