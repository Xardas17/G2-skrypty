#if !defined(AFX_SPCCOBJECTSOUNDDIALOG_H__898E83E0_F5F8_11D4_AEBA_0050DA339C1B__INCLUDED_)
#define AFX_SPCCOBJECTSOUNDDIALOG_H__898E83E0_F5F8_11D4_AEBA_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCObjectSoundDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCObjectSoundDialog 

class spcCObjectSoundDialog : public CDialog
{
// Konstruktion
public:
	spcCObjectSoundDialog(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(spcCObjectSoundDialog)
	enum { IDD = IDD_MANIPULATE_SOUNDS };
	double	m_mult_ranges;
	double	m_mult_volumes;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCObjectSoundDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCObjectSoundDialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCOBJECTSOUNDDIALOG_H__898E83E0_F5F8_11D4_AEBA_0050DA339C1B__INCLUDED_
