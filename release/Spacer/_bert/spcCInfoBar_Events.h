#if !defined(AFX_SPCCINFOBAR_EVENTS_H__5F2AE0E1_1F1B_11D3_8A05_D6880B9AF548__INCLUDED_)
#define AFX_SPCCINFOBAR_EVENTS_H__5F2AE0E1_1F1B_11D3_8A05_D6880B9AF548__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCInfoBar_Events.h : Header-Datei
//

#include "z3d.h"
#include "zVob.h"
#include "zVobMisc.h"


// #include "spcCDragVob.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCInfoBar_Events 

class spcCInfoBar_Events : public CDialog
{
// Konstruktion
public:
	spcCInfoBar_Events(CWnd* pParent = NULL);   // Standardkonstruktor
	~spcCInfoBar_Events();

	void SelectVob(zCVob* pickedVob);	
	void InitData();
	void PreClose();

	zCVob*		cur_vob;
	zCVob*		event_sourcevob;
	zCMover*	moverVob;

	void SetToKeyPos();

	virtual void HandleVobSelect(zCVob* vob);
	virtual void HandleVobInsert(zCVob* vob, zCVob* parentVob);
	virtual void HandleVobRemove(zCVob* vob);

private:
	void OnChangeVisual(CString & visName);

	int selected;
	
public:
	void RemoveVobsFromLists();

	zCList<zCVob>*	GetSourceVobList(zCVob*& refVob);
	zCList<zCVob>*	GetTargetVobList(zCVob*& refVob);	
	void			SetEventSourceVob(zCVob* vob);
	zCVob*			GetEventSourceVob() { return event_sourcevob; };

	void			CollectTriggerTargets();

// Dialogfelddaten
	//{{AFX_DATA(spcCInfoBar_Events)
	enum { IDD = IDD_INFO_EVENTS };
	CButton		ctrl_event_send;
	CListBox	ctrl_event_list;	
	CListCtrl	ctrl_list_targets;
	CListCtrl	ctrl_list_sources;
	CEdit		ctrl_kf_edit;
	CButton		ctrl_createkey;
	CButton		ctrl_deletebutton;
	// CComboBox	ctrl_visualname;
	CString	m_classname;
	CString	m_vobname;
	CString	m_visualname;
	BOOL	m_sel_cd_dyn;
	BOOL	m_sel_cd_stat;	
	int		m_kf_pos;
	int		m_insertmode;
	float	m_danage_value;
	CString	m_source_vob;
	//}}AFX_DATA
	
	zCList<zCVob> sourceVobList;
	zCList<zCVob> targetVobList;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCInfoBar_Events)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCInfoBar_Events)
	afx_msg void OnChangeVobname();
	// afx_msg void OnSelchangeVisualname();
	// afx_msg void OnVisualbutton();
	afx_msg void OnSelCdDyn();
	afx_msg void OnSelCdStat();	
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeKfEdit();
	afx_msg void OnCreatekey();
	virtual void OnOK();
	afx_msg void OnKfDec();
	afx_msg void OnKfInc();
	afx_msg void OnDeletekey();
	afx_msg void OnStoreState();
	afx_msg void OnRestoreState();
	afx_msg void OnEventListSelected();
	afx_msg void OnEventSend();
	afx_msg void OnCollect();
	afx_msg void OnDblclkListSources(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListTargets(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnUpdateViewvobVobInitevents(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCINFOBAR_EVENTS_H__5F2AE0E1_1F1B_11D3_8A05_D6880B9AF548__INCLUDED_
