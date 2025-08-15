#if !defined(AFX_SPCCInfoBar_Camera_H__5F2AE0E1_1F1B_11D3_8A05_D6880B9AF548__INCLUDED_)
#define AFX_SPCCInfoBar_Camera_H__5F2AE0E1_1F1B_11D3_8A05_D6880B9AF548__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCInfoBar_Camera.h : Header-Datei
//

#include "z3d.h"
#include "zVob.h"
#include "zCSCamera.h"

#include "resource.h"
#include <spcCObjPreset.h>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCInfoBar_Camera 

class spcCInfoBar_Camera : public CDialog
{
// Konstruktion
public:
	spcCInfoBar_Camera(CWnd* pParent = NULL);   // Standardkonstruktor

// my public
	void HandleVobRemove(zCVob* vob);
	void HandleVobInsert(zCVob* vob,zCVob* parent);
	void HandleVobSelect(zCVob* vob);

	zCVob* InsertVob(const zPOINT3& pos, const zPOINT3& dir, zCVob* vob);

	void UpdateKeyframe();
	void InitData();
	void PreClose();

	zCVob*		cur_vob;
	zCCSCamera* cur_cam;
	float		lastPresetTime;
	zBOOL		lastPresetAutoAddKF;

	void SetToKeyPos();


private:
	zSTRING ccl;
	zCPresetView* presets;
	zCCSCamera* editPreset;
	int selected;
	bool presetEditMode;
	void UpdatePresetList();

public:
// Dialogfelddaten
	//{{AFX_DATA(spcCInfoBar_Camera)
	enum { IDD = IDD_INFO_CAMERA };
	CButton	ctrl_presetremove;
	CListBox	ctrl_presetlist;
	CEdit	ctrl_kf_edit;
	CString	m_vobname;
	int		m_kf_pos;	
	int		m_splineselect;
	CString	m_ref_cam;
	CString	m_ref_target;	
	float	m_cam_play_duration;	
	BOOL	m_insert_at_current_pos;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCInfoBar_Camera)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCInfoBar_Camera)
	afx_msg void OnChangeVobname();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeKfEdit();
	virtual void OnOK();
	afx_msg void OnKfDec();
	afx_msg void OnKfInc();
	afx_msg void OnSelchangePresetList();
	afx_msg void OnSplineCam();
	afx_msg void OnSplineTarget();
	afx_msg void OnCamPlay();
	afx_msg void OnCamStop();	
	afx_msg void OnCamKfGoto();	
	afx_msg void OnCreatePreset();
	afx_msg void OnRemovePreset();
	afx_msg void OnInsertCamera();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCInfoBar_Camera_H__5F2AE0E1_1F1B_11D3_8A05_D6880B9AF548__INCLUDED_
