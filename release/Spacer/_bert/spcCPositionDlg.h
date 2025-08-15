#if !defined(AFX_SPCCPOSITIONDLG_H__784AE5A1_B946_11D3_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_SPCCPOSITIONDLG_H__784AE5A1_B946_11D3_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCPositionDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCPositionDlg 

class spcCPositionDlg : public CDialog
{
// Konstruktion
public:
	spcCPositionDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(spcCPositionDlg)
	enum { IDD = IDD_INPUT_DLG_POSITION };
	float	m_edit_x;
	float	m_edit_y;
	float	m_edit_z;
	CString	m_levelname;
	float	m_at_x;
	float	m_at_y;
	float	m_at_z;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCPositionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCPositionDlg)
	afx_msg void OnClipboard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCPOSITIONDLG_H__784AE5A1_B946_11D3_BA4F_0050DA339C1B__INCLUDED_
