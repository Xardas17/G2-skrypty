#if !defined(AFX_SPCCCSSETTINGDLG_H__AD435B61_498F_11D3_8A05_A0F495858A7B__INCLUDED_)
#define AFX_SPCCCSSETTINGDLG_H__AD435B61_498F_11D3_8A05_A0F495858A7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCCSSettingDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCCSSettingDlg 

class spcCCSSettingDlg : public CDialog
{
// Konstruktion
public:
	spcCCSSettingDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(spcCCSSettingDlg)
	enum { IDD = IDD_SETTINGS_CS };
	BOOL	m_loopable;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCCSSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCCSSettingDlg)
	afx_msg void OnCsprops();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCCSSETTINGDLG_H__AD435B61_498F_11D3_8A05_A0F495858A7B__INCLUDED_
