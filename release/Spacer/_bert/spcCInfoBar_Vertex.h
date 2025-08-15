#if !defined(AFX_SPCCINFOBAR_VERTEX_H__15945982_8C5C_11D3_B355_004005A7C374__INCLUDED_)
#define AFX_SPCCINFOBAR_VERTEX_H__15945982_8C5C_11D3_B355_004005A7C374__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCInfoBar_Vertex.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCInfoBar_Vertex 

class spcCInfoBar_Vertex : public CDialog
{
// Konstruktion
public:
	spcCInfoBar_Vertex(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~spcCInfoBar_Vertex();
// Dialogfelddaten
	//{{AFX_DATA(spcCInfoBar_Vertex)
	enum { IDD = IDD_INFO_VERTEX };
	CSliderCtrl	ctrl_mv_speed;
	int		m_mv_speed;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCInfoBar_Vertex)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCInfoBar_Vertex)
	afx_msg void OnReleasedcaptureSpeedSlider(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void InitData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCINFOBAR_VERTEX_H__15945982_8C5C_11D3_B355_004005A7C374__INCLUDED_
