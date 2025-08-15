#if !defined(AFX_spcCInfoBar_Vobs_H__5F2AE0E1_1F1B_11D3_8A05_D6880B9AF548__INCLUDED_)
#define AFX_spcCInfoBar_Vobs_H__5F2AE0E1_1F1B_11D3_8A05_D6880B9AF548__INCLUDED_


#include "z3d.h"
#include "zVob.h"

#include "spcCObjpreset.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCInfoBar_Vobs.h : Header-Datei
//



/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCInfoBar_Vobs

class spcCInfoBar_Vobs : public CDialog
{
// Konstruktion
public:
	spcCInfoBar_Vobs(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~spcCInfoBar_Vobs();

	virtual void HandleVobSelect(zCVob* vob);
	virtual void HandleVobInsert(zCVob* vob, zCVob* parentVob);
	virtual void HandleVobRemove(zCVob* vob);

// my public
	void SelectVob(zCVob* pickedVob);
	zCVob* CreateNewVob();
	zCVob* InsertVob(const zPOINT3& pos, const zPOINT3& dir, zCVob* vob);
	void UpdateDragPosition(zCVob* dragVob);
	void InitData();
	void PreClose();

	zCVob* cur_vob;

private:
	void OnChangeVisual(CString & visName);

	zCArray<zSTRING> presetClassName;
	zCArray<zCPresetView*> presets;
	zCArray<bool> pLibExplicit;
	zCPresetView* actPView;
	zCVob* editPreset;
	int selected;
	bool presetEditMode;
	void UpdatePresetList();

public:
	void AddPresetClass(zSTRING & cl, bool cexplicit=false) 
	{
		presetClassName.Insert(cl);
		presets.Insert(NULL);
		pLibExplicit.Insert(cexplicit);
	};

public:
// Dialogfelddaten
	//{{AFX_DATA(spcCInfoBar_Vobs)
	enum { IDD = IDD_INFO_VOBS };
	CButton	ctrl_restore;
	CButton	ctrl_testevent;
	CButton	ctrl_sendevent;
	CComboBox	ctrl_presetclass;
	CComboBox	ctrl_camalign;
	CEdit	ctrl_fps;
	CComboBox	ctrl_alphablend;
	CButton	ctrl_2sided;
	CButton	ctrl_presetreload;
	CButton	ctrl_presetremove;
	CButton	ctrl_from_current;
	CButton	ctrl_to_current;
	CListBox	ctrl_presetlist;
	CButton	ctrl_deletebutton;
	CComboBox	ctrl_visualname;
	CString	m_classname;
	CString	m_vobname;
	CString	m_visualname;
	BOOL	m_sel_cd_dyn;
	BOOL	m_sel_cd_stat;
	BOOL	m_sel_staticvob;
	int		m_insertmode;
	BOOL	m_2sided;
	CString	m_camalign;
	CString	m_alphablend;
	int		m_fps;
	CString	m_presetclass;
	BOOL	m_evtrigger;
	BOOL	m_evuntrigger;
	BOOL	m_enable_presets;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCInfoBar_Vobs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCInfoBar_Vobs)
	afx_msg void OnChangeVobname();
	afx_msg void OnSelchangeVisualname();
	afx_msg void OnVisualbutton();
	afx_msg void OnSelCdDyn();
	afx_msg void OnSelCdStat();
	afx_msg void OnSelStaticvob();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangePresetList();
	afx_msg void OnPresetFromCurrentT();
	afx_msg void OnPresetToCurrentT();
	afx_msg void OnPresetRemoveT();
	afx_msg void OnPresetReloadT();
	afx_msg void On2sided();
	afx_msg void OnChangeAniFps();
	afx_msg void OnSelchangeAlphaBlend();
	afx_msg void OnSelchangeCamAlign();
	afx_msg void OnSelchangePresetClass();
	afx_msg void OnSendevent();
	afx_msg void OnTestevent();
	afx_msg void OnEventrestore();
	afx_msg void OnEnablePresets();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif
