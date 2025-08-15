#if !defined(AFX_SPCCINFOBAR_MATERIALS_H__806CF204_3823_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_SPCCINFOBAR_MATERIALS_H__806CF204_3823_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCInfoBar_Materials.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Materials dialog

class zCMaterial;
class spcCDibSection;

class spcCInfoBar_Materials : public CDialog
{
private:	
	void EnableCTRL(bool m);

// Construction
public:
	void MaterialModified();
	bool ActivateQuickSlot(int nr);
	zCArray<zCMaterial*> quickMatList;

	int SelectMaterialFilter();	
	void GetMaterialMapping(float& x, float& y);
	zCMaterial* GetMaterial();
	 ~spcCInfoBar_Materials();
	spcCDibSection* dib;
	void InitData();
	void EditMaterial(zCMaterial* mat); // select Mat from outside
	void UpdateFilterList(); // if the config.matfilterlist possibly changed, update with this
	spcCInfoBar_Materials(CWnd* pParent = NULL);   // standard constructor

	int	m_filter_fix_index;
	BOOL	m_filter_fix;
	zCMaterial* cur_mat;	
// Dialog Data
	//{{AFX_DATA(spcCInfoBar_Materials)
	enum { IDD = IDD_INFO_MATERIALS };
	CButton	ctrl_filter_fix;
	CSpinButtonCtrl	ctrl_tex_move_spin;
	CButton	ctrl_multinew;	
	CButton	ctrl_select_tex;
	CButton	ctrl_remove_tex;
	CButton	ctrl_set_mapping;
	CEdit	ctrl_mapping_y;
	CEdit	ctrl_mapping_x;
	CEdit	ctrl_matname;	
	CComboBox	ctrl_filter;
	CComboBox	ctrl_group;
	CStatic	ctrl_preview;
	float	m_mapping_x;
	float	m_mapping_y;
	CString	m_filter;
	CString	m_group;
	CString	m_name;
	CString	m_tex_info;
	CString	m_tex_name;
	BOOL	m_check_mapping;	
	double	m_tex_movement;
	CString	m_quickslot;	
	CString	m_filter_comment;
	int		m_color_alpha;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCInfoBar_Materials)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCInfoBar_Materials)
	afx_msg void OnButton_SelectTexture();
	afx_msg void OnButton_Color();
	afx_msg void OnSelchangeMatFilter();
	afx_msg void OnSelchangeMatGroup();
	afx_msg void OnButton_RemoveTexture();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSetMapping();	
	afx_msg void OnMatNewPureMaterial();	
	virtual void OnOK();
	afx_msg void OnChangeMatName();
	afx_msg void OnChangeMapX();
	afx_msg void OnChangeMapY();
	afx_msg void OnMatAvcolorbtn();
	afx_msg void OnCheckmap();	
	afx_msg void OnMatAddMaterials();
	afx_msg void OnMatUpdate();
	afx_msg void OnDeltaposTexMoveSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeTexMovement();
	afx_msg void OnKillfocusTexMovement();
	afx_msg void OnChangeQuickslot();
	afx_msg void OnAssignQuickslot();
	afx_msg void OnFilterFix();		
	afx_msg void OnChangeColorAlpha();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCINFOBAR_MATERIALS_H__806CF204_3823_11D2_8AB9_0080AD209698__INCLUDED_)
