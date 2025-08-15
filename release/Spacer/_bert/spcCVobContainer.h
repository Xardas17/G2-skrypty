#if !defined(AFX_SPCCVOBCONTAINER_H__0F4E9FB7_DE51_41A4_B76D_57031C73EC19__INCLUDED_)
#define AFX_SPCCVOBCONTAINER_H__0F4E9FB7_DE51_41A4_B76D_57031C73EC19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spccvobcontainer.h : Header-Datei
//

#include <afxext.h>
#include <afxtempl.h>
#include "spcCWindowResizeStyle.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCVobContainer 

class spcCVobContainer : public CDialog
{
// Konstruktion
public:
	int FindVob(zCVob* vob);
	enum spcTVcMode { VC_COLLECT, VC_COLLECT_10M, VC_COLLECT_100M, VC_COLLECT_20M, VC_COLLECT_30M, VC_COLLECT_ALL_VOBS, VC_CUSTOM } mode;

	void SetMode		(spcTVcMode _mode);

	void RemoveVob		(zCVob* vob);
	void ClearVoblist	();
	void AddVob			(zCVob* vob);	
	void PopupUpdate	(CMenu* menu);

	spcCVobContainer(CWnd* pParent = NULL);   // Standardkonstruktor	

// Dialogfelddaten
	//{{AFX_DATA(spcCVobContainer)
	enum { IDD = IDD_VOB_CONTAINER };
	CButton	ctrl_actions;
	CListCtrl	ctrl_voblist;
	CButton	ctrl_modus;
	BOOL	m_bFastUpdate;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCVobContainer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

protected:	

	POSITION winID;

	CList<spcCWindowResizeStyle*,spcCWindowResizeStyle*> childResizeList;
	
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCVobContainer)
	afx_msg void OnVcModus();
	afx_msg void OnVcCustom();
	afx_msg void OnVcCollect();	
	afx_msg void OnVcActions();	
	virtual BOOL OnInitDialog();	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnKeyDown		(UINT nChar, UINT nRepCnt, UINT nFlags);	
	afx_msg void OnDblclkVoblist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickVoblist	(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnVobcontaineractionsRemovefromworld();
	afx_msg void OnVobcontaineractionsLoadvoblist();
	afx_msg void OnVobcontaineractionsClearvoblist();
	afx_msg void OnVobcontaineractionsSavevoblist();
	afx_msg void OnVobcontaineractionsConvertToDetailedVob();
	afx_msg void OnVobcontaineractionsClearselected();
	afx_msg void OnVcCollect10m();
	afx_msg void OnVcCollect100m();
	afx_msg void OnFastupdate();
	afx_msg void OnVcCollect20m();
	afx_msg void OnVcCollect30m();
	afx_msg void OnVcCollectAll();
	afx_msg void OnUpdateVcVobtypesAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVcVobtypesItems(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVcVobtypesLights(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVcVobtypesMobs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVcVobtypesNpcs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVcVobtypesSounds(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVcVobtypesVobs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVcVobtypesWaypoints(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	zBOOL	m_bVobCollect_All;
	zBOOL	m_bVobCollect_Lights;
	zBOOL	m_bVobCollect_zCVobs;
	zBOOL	m_bVobCollect_Waypoints;
	zBOOL	m_bVobCollect_Sounds;
	zBOOL	m_bVobCollect_Mobs;
	zBOOL	m_bVobCollect_Items;
	zBOOL	m_bVobCollect_Npcs;
	zBOOL	m_bVobCollect_Illegal;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCVOBCONTAINER_H__0F4E9FB7_DE51_41A4_B76D_57031C73EC19__INCLUDED_
