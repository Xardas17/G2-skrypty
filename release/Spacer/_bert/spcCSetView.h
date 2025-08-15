#if !defined(AFX_SPCCSETVIEW_H__F7F40945_2D1E_11D2_88A8_0080AD209698__INCLUDED_)
#define AFX_SPCCSETVIEW_H__F7F40945_2D1E_11D2_88A8_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCSetView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCSetView dialog

class spcCSetView : public CDialog
{
// Construction
public:
	void GetVideo(int& device, int& resolution);
	void SetVideo(int device, int resolution);		
	
	spcCSetView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(spcCSetView)
	enum { IDD = IDD_SETTINGS_VIEW };
	CComboBox	ctrl_video_resolution;
	CComboBox	ctrl_video_device;	
	int		m_view_x;
	int		m_view_y;
	int		m_view_bpp;	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCSetView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spcCSetView)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeVideoDevice();
	afx_msg void OnSelchangeVideoResolution();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCSETVIEW_H__F7F40945_2D1E_11D2_88A8_0080AD209698__INCLUDED_)
