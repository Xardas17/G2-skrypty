#if !defined(AFX_SPCCINFOBAR_SOUNDS_H__7E7B2263_384A_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_SPCCINFOBAR_SOUNDS_H__7E7B2263_384A_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCInfoBar_Sounds.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Sounds dialog

class zCVob;
class zCVobSound;

class spcCInfoBar_Sounds : public CDialog
{
// Construction
public:
	spcCInfoBar_Sounds(CWnd* pParent = NULL);   // standard constructor
	virtual ~spcCInfoBar_Sounds();

	virtual void HandleVobSelect(zCVob* vob);
	virtual void HandleVobInsert(zCVob* vob, zCVob* parentVob);
	virtual void HandleVobRemove(zCVob* vob);

	zCVobSound* playing_vob;

// Dialog Data
	//{{AFX_DATA(spcCInfoBar_Sounds)
	enum { IDD = IDD_INFO_SOUNDS };
	CListBox	ctrl_voblist;
	CString	m_playing_name;
	BOOL	m_playing;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCInfoBar_Sounds)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCInfoBar_Sounds)	
	virtual void OnOK();
	afx_msg void OnSelchangeVoblist();
	afx_msg void OnSndPlay();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void	SelectVob(zCVob* vob);
	zCVob*	CreateNewVob();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCINFOBAR_SOUNDS_H__7E7B2263_384A_11D2_8AB9_0080AD209698__INCLUDED_)
