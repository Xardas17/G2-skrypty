#if !defined(AFX_SPCCBBOXDEFINEDLG_H__973B49A0_AAB3_11D4_AEBA_0050DA339C1B__INCLUDED_)
#define AFX_SPCCBBOXDEFINEDLG_H__973B49A0_AAB3_11D4_AEBA_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCBBoxDefineDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCBBoxDefineDlg 

class spcCBBoxDefineDlg : public CDialog
{
// Konstruktion
public:
	spcCBBoxDefineDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(spcCBBoxDefineDlg)
	enum { IDD = IDD_BBOX_DEFINE };
	float	m_dx;
	float	m_dy;
	float	m_dz;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCBBoxDefineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCBBoxDefineDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCBBOXDEFINEDLG_H__973B49A0_AAB3_11D4_AEBA_0050DA339C1B__INCLUDED_
