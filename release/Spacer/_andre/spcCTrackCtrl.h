#if !defined(AFX_SPCCTRACKCTRL_H__880214F7_D8BE_11D3_8A05_A45453FD695E__INCLUDED_)
#define AFX_SPCCTRACKCTRL_H__880214F7_D8BE_11D3_8A05_A45453FD695E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCTrackCtrl.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster spcCTrackCtrl 

class spcCTrackCtrl : public CTreeCtrl
{
// Konstruktion
public:
	spcCTrackCtrl();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCTrackCtrl)
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~spcCTrackCtrl();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(spcCTrackCtrl)
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCTRACKCTRL_H__880214F7_D8BE_11D3_8A05_A45453FD695E__INCLUDED_
