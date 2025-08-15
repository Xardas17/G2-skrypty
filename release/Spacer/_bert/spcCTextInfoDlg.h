#if !defined(AFX_spcCTextInfoDlg_H__7A79B040_C37D_11D3_B00C_0080AD209698__INCLUDED_)
#define AFX_spcCTextInfoDlg_H__7A79B040_C37D_11D3_B00C_0080AD209698__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCTextInfoDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCTextInfoDlg 

class spcCTextInfoDlg : public CDialog
{
// Konstruktion
public:
	spcCTextInfoDlg(CWnd* pParent = NULL);   // Standardkonstruktor

	void SetTitle(CString s) { m_title = s;};

// Dialogfelddaten
	//{{AFX_DATA(spcCTextInfoDlg)
	enum { IDD = IDD_TEXTINFO_DLG };
	CString	m_contents;
	CString	m_title;
	//}}AFX_DATA

	virtual int	DoModal();

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCTextInfoDlg)	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung	
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCTextInfoDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_spcCTextInfoDlg_H__7A79B040_C37D_11D3_B00C_0080AD209698__INCLUDED_
