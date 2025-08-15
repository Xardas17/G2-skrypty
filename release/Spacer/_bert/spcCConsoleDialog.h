#if !defined(AFX_SPCCCONSOLEDIALOG_H__309E2861_B7A3_11D3_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_SPCCCONSOLEDIALOG_H__309E2861_B7A3_11D3_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCConsoleDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCConsoleDialog 

class spcCConsoleDialog : public CDialog
{
// Konstruktion
public:
	spcCConsoleDialog(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(spcCConsoleDialog)
	enum { IDD = IDD_CONSOLE_DLG };
	CEdit	ctrl_input;
	CString	m_input;
	CString	m_output;
	BOOL	m_autocomplete;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCConsoleDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCConsoleDialog)
	afx_msg void OnUpdateInput();
	afx_msg void OnClosedlg();
	virtual void OnOK();
	afx_msg void OnChangeInput();
	afx_msg void OnAutocomplete();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCCONSOLEDIALOG_H__309E2861_B7A3_11D3_BA4F_0050DA339C1B__INCLUDED_
