#if !defined(AFX_SPCCOBJECTBAR_H__36343BE1_36F4_11D4_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_SPCCOBJECTBAR_H__36343BE1_36F4_11D4_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCObjectBar.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCObjectBar 

class spcCObjectBar : public CDialog
{
// Konstruktion
public:
	spcCObjectBar(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(spcCObjectBar)
	enum { IDD = IDD_INFO_EMPTY };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCObjectBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	POSITION winID;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCObjectBar)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCOBJECTBAR_H__36343BE1_36F4_11D4_BA4F_0050DA339C1B__INCLUDED_
