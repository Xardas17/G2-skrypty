#if !defined(AFX_SPCCOBJECTMANIPULATEPAGE_H__23A1DF81_EE03_11D3_A405_0080AD209698__INCLUDED_)
#define AFX_SPCCOBJECTMANIPULATEPAGE_H__23A1DF81_EE03_11D3_A405_0080AD209698__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCObjectManipulatePage.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCObjectManipulatePage 


#include <afxtempl.h>



class spcCWindowResizeStyle;
class zCVob;

class spcCObjectManipulatePage : public CPropertyPage
{
	DECLARE_DYNCREATE(spcCObjectManipulatePage)

// Konstruktion
public:
	bool isEnabled;
	void Enable(bool enabled = true);
	void ActivateEditBoundingBox(zCVob* vob);
	spcCObjectManipulatePage();
	~spcCObjectManipulatePage();

// Dialogfelddaten
	//{{AFX_DATA(spcCObjectManipulatePage)
	enum { IDD = IDD_OBJECT_MANIPULATE_PAGE };
	CEdit	ctrl_information;
	CButton	ctrl_action_right;
	CButton	ctrl_action_left;
	CButton	ctrl_action_center;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCObjectManipulatePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	void DoAction(CString name);

	CList<spcCWindowResizeStyle*,spcCWindowResizeStyle*> childResizeList;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCObjectManipulatePage)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnActionCenter();
	afx_msg void OnActionLeft();
	afx_msg void OnActionRight();
	afx_msg void OnActionDefine();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCOBJECTMANIPULATEPAGE_H__23A1DF81_EE03_11D3_A405_0080AD209698__INCLUDED_
