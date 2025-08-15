#if !defined(AFX_SPCCVOBLISTDIALOG_H__DC7DD6C7_E66B_11D3_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_SPCCVOBLISTDIALOG_H__DC7DD6C7_E66B_11D3_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCVobListDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCVobListDialog 

class spcCVobListDialog : public CDialog
{
// Konstruktion
public:
	spcCVobListDialog(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(spcCVobListDialog)
	enum { IDD = IDD_VOB_LIST_DLG };
	CTreeCtrl	ctrl_vob_list;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCVobListDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCVobListDialog)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCVOBLISTDIALOG_H__DC7DD6C7_E66B_11D3_BA4F_0050DA339C1B__INCLUDED_
