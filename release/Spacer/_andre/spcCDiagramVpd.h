#if !defined(AFX_SPCCDIAGRAMVPD_H__BEE7E5A1_33A7_11D3_8A05_9385D0FB0649__INCLUDED_)
#define AFX_SPCCDIAGRAMVPD_H__BEE7E5A1_33A7_11D3_8A05_9385D0FB0649__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCDiagramVPD.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCDiagramVPD 

class spcCDiagramVPD : public CDialog
{
// Konstruktion
public:
	spcCDiagramVPD(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(spcCDiagramVPD)
	enum { IDD = IDD_DIAGRAM_VIEPORT };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCDiagramVPD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCDiagramVPD)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCDIAGRAMVPD_H__BEE7E5A1_33A7_11D3_8A05_9385D0FB0649__INCLUDED_
