#if !defined(AFX_SPCCINFOBAR_SPECIALS_H__7E7B2264_384A_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_SPCCINFOBAR_SPECIALS_H__7E7B2264_384A_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCInfoBar_Specials.h : header file
//

#include "z3d.h"

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Specials dialog

class spcCInfoBar_Specials : public CDialog
{
// Construction
public:
	spcCInfoBar_Specials(CWnd* pParent = NULL);   // standard constructor
	virtual ~spcCInfoBar_Specials();

	virtual void HandleVobSelect(zCVob* vob);
	virtual void HandleVobInsert(zCVob* vob, zCVob* parentVob);
	virtual void HandleVobRemove(zCVob* vob);

	void	SelectVob(zCVob* vob);
	zCVob*	CreateNewVob();

	void OnModeChanged();
	void showParticlePanel(bool quest=true);

// Dialog Data
	//{{AFX_DATA(spcCInfoBar_Specials)
	enum { IDD = IDD_INFO_SPECIALS };
	//CButton	ctrl_part_edit;
	//CButton	crtl_part_new;
	CListBox	ctrl_list;
	BOOL	m_particle;
	BOOL	m_spot;
	BOOL	m_waypoint;	
	BOOL	m_decal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCInfoBar_Specials)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CString m_list;
	zCVob* cur_vob;

	// Generated message map functions
	//{{AFX_MSG(spcCInfoBar_Specials)
	afx_msg void OnParticles();
	afx_msg void OnSpots();
	afx_msg void OnWaypoints();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList();
	virtual void OnOK();
	//afx_msg void OnPartEdit();
	//afx_msg void OnPartNew();
	afx_msg void OnDecal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCINFOBAR_SPECIALS_H__7E7B2264_384A_11D2_8AB9_0080AD209698__INCLUDED_)
