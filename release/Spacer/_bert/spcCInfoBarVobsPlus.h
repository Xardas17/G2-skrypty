#if !defined(AFX_SPCCINFOBARVOBSPLUS_H__1EA72321_4B3B_11D3_8A05_EE3632F1305C__INCLUDED_)
#define AFX_SPCCINFOBARVOBSPLUS_H__1EA72321_4B3B_11D3_8A05_EE3632F1305C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCInfoBarVobsPlus.h : Header-Datei
//

#include "z3d.h"
#include "zVob.h"

#include "spcCObjPreset.h"


// #include "spcCDragVob.h"

class spcCInfoBar_VobsPlus : public CDialog
{
// Konstruktion
public:
	spcCInfoBar_VobsPlus(CWnd* pParent = NULL);   // Standardkonstruktor

	virtual void HandleVobSelect(zCVob* vob);
	virtual void HandleVobInsert(zCVob* vob, zCVob* parentVob);
	virtual void HandleVobRemove(zCVob* vob);

// my public
	void SelectVob(zCVob* pickedVob);
	zCVob* InsertVob(const zPOINT3& pos, const zPOINT3& dir, zCVob* vob);
	// void UpdateDragPosition(zCVob* dragVob);
	void InitData();
	void PreClose();

	zCVob* cur_vob;

	void SetToKeyPos();

	//spcCDragVob* dragBottom;
	//spcCDragVob* dragTop;

private:
	void OnChangeVisual(CString & visName);

	zCPresetView* presets;
	zCVob* editPreset;
	int selected;
	bool presetEditMode;
	void UpdatePresetList();

public:
// Dialogfelddaten
	//{{AFX_DATA(spcCInfoBar_VobsPlus)
	enum { IDD = IDD_INFO_VOBSPLUS };
	CButton	ctrl_restore;
	CButton	ctrl_testevent;
	CButton	ctrl_sendevent;
	CButton	ctrl_presetreload;
	CButton	ctrl_presetremove;
	CButton	ctrl_from_current;
	CButton	ctrl_to_current;
	CListBox	ctrl_presetlist;
	//CButton	ctrl_editbbox;
	CComboBox	ctrl_visualname;
	CString	m_classname;
	CString	m_vobname;
	CString	m_visualname;
	BOOL	m_sel_cd_dyn;
	BOOL	m_sel_cd_stat;
	BOOL	m_sel_staticvob;
	//BOOL	m_editbbox;
	BOOL	m_evtrigger;
	BOOL	m_evuntrigger;
	BOOL	m_enable_presets;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCInfoBar_VobsPlus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCInfoBar_VobsPlus)
	afx_msg void OnChangeVobname();
	afx_msg void OnSelchangeVisualname();
	afx_msg void OnVisualbutton();
	afx_msg void OnSelCdDyn();
	afx_msg void OnSelCdStat();
	afx_msg void OnSelStaticvob();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//afx_msg void OnEditbbox();
	afx_msg void OnSelchangePresetList();
	afx_msg void OnPresetFromCurrentT();
	afx_msg void OnPresetToCurrentT();
	afx_msg void OnPresetRemoveT();
	afx_msg void OnPresetReloadT();
	afx_msg void OnSendevent();
	afx_msg void OnTestevent();
	afx_msg void OnEventrestore();
	afx_msg void OnEnablePresets();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCINFOBARVOBSPLUS_H__1EA72321_4B3B_11D3_8A05_EE3632F1305C__INCLUDED_
