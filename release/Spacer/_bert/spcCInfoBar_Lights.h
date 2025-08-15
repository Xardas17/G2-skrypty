#if !defined(AFX_SPCCINFOBAR_LIGHTS_H__806CF205_3823_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_SPCCINFOBAR_LIGHTS_H__806CF205_3823_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCInfoBar_Lights.h : header file
//

#include "ztypes3d.h"
#include "spcCColorListbox.h"
/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Lights dialog

class zCVob;
class zCVobLight;
class zCVobLightData;
class zCVobLightPreset;


class spcCInfoBar_Lights : public CDialog
{
// Construction
public:	
	
	spcCInfoBar_Lights							(CWnd* pParent = NULL);
	~spcCInfoBar_Lights							();
												
	zCVob*			CreateNewVob				();	
	void			SelectVob					(zCVob* vob);	
												
	virtual void	HandleVobSelect				(zCVob* vob);	
	virtual void	HandleVobRemove				(zCVob* vob);
	virtual void	HandleVobInsert				(zCVob* vob, zCVob* parent=0);
												
	void			UpdateVobByData				(zCVobLight* vob);
	void			UpdateVobByPreset			(zCVobLight* vob);
	void			UpdatePresetByData			(zCVobLightPreset* preset);
												
	void			SetDataByLightData			(zCVobLightData* data);
	void			SetDataByPreset				(zCVobLightPreset* preset);
	void			SetDataByVob				(zCVob* vob);
												
	void			ConnectionTo				(zCVob* vob);		

	void			CreatePresetList			();		
	zBOOL			GetShowLightsWireFramed		()												{ return this->m_bShowWireFrame;			};
	void			SetShowLightsWireFramed		( const zBOOL a_bShowWire )						{ this->m_bShowWireFrame = a_bShowWire;		};
	void			CheckWireFrameLight			(zCVob* a_pVobLight);
		
	zCVobLight*			cur_vob;
	zCVobLight*			m_pLastVobLight;
	zCVobLightPreset*	selPreset;
	zCVobLightPreset*	vobPreset;	
	CString				m_preset_name;
	zBOOL				m_bShowWireFrame;
	zBOOL				m_bLightDynCompile;
	
// Dialog Data
	//{{AFX_DATA(spcCInfoBar_Lights)
	enum { IDD = IDD_INFO_LIGHT };
	CButton	ctrl_reapply;
	CButton	ctrl_button_apply;
	CButton	ctrl_select_static;
	CButton	ctrl_select_dynamic;
	CEdit	ctrl_name;
	CButton	ctrl_color_smooth;
	CButton	ctrl_range_smooth;
	CButton	ctrl_range_del;
	CEdit	ctrl_range_chps;
	CButton	ctrl_range_add;
	CButton	ctrl_color_del;
	CEdit	ctrl_color_chps;
	CButton	ctrl_color_add;
	CButton	ctrl_button_update_preset;
	CButton	ctrl_button_update_light;
	CButton	ctrl_color_down;
	CButton	ctrl_color_up;	
	CButton	ctrl_prop_group;
	spcCColorListbox	ctrl_color_list;
	CListBox	ctrl_range_list;
	CListBox	ctrl_preset_list;
	CComboBox	ctrl_light_dyn_quality;
	float	m_color_chps;
	BOOL	m_color_smooth;
	BOOL	m_light_dyn;
	BOOL	m_range_smooth;
	BOOL	m_light_static;
	float	m_range_chps;
	CString	m_name;
	CString	text_tovob;
	CString	text_label;	
	CString	m_curvob_preset_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCInfoBar_Lights)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateLightData();
	void ResetVobLighting(zCVob* vob);

	// Generated message map functions
	//{{AFX_MSG(spcCInfoBar_Lights)
	afx_msg void OnFilterButton();
	afx_msg void OnColorAdd();
	afx_msg void OnColorDel();
	afx_msg void OnSelchangeColorList();
	afx_msg void OnRangeAdd();
	afx_msg void OnRangeDel();
	afx_msg void OnSelchangeRangeList();
	afx_msg void OnPresetNew();	
	afx_msg void OnDblclkColorList();
	afx_msg void OnDblclkRangeList();
	afx_msg void OnDynamicLight();
	afx_msg void OnStaticLight();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangePresetList();
	afx_msg void OnDblclkPresetList();
	afx_msg void OnPresetRemove();
	afx_msg void OnChangeColorChps();
	afx_msg void OnColorSmooth();
	afx_msg void OnSelchangeLightDynQuality();
	afx_msg void OnChangeRangeChps();
	afx_msg void OnRangeSmooth();
	afx_msg void OnChangeName();
	virtual void OnOK();	
	afx_msg void OnColorDown();
	afx_msg void OnColorUp();	
	afx_msg void OnUpdatePresetByVob();
	afx_msg void OnUpdateVobByPreset();
	afx_msg void OnApply();
	afx_msg void OnPresetReapply();
	afx_msg void OnLightShowranges();
	afx_msg void OnLightDynamicCompile();
	afx_msg void OnReleasedcaptureSliderInstantCompileFrameskip(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCINFOBAR_LIGHTS_H__806CF205_3823_11D2_8AB9_0080AD209698__INCLUDED_)
