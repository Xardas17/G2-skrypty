#if !defined(AFX_SPCCCOLORLISTBOX_H__2AA235E0_3F46_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_SPCCCOLORLISTBOX_H__2AA235E0_3F46_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCColorListbox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCColorListbox window

class spcCColorListbox : public CListBox
{
// Construction
public:
	spcCColorListbox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCColorListbox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~spcCColorListbox();
	void GetCurColor(int& r,int& g,int& b);
	void GetColor(int index, int& r,int& g,int& b);
	void AddColor(int r,int g,int b);
	void InsertColor(int index, int r, int g, int b);

	// Generated message map functions
protected:
	//{{AFX_MSG(spcCColorListbox)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCCOLORLISTBOX_H__2AA235E0_3F46_11D2_8AB9_0080AD209698__INCLUDED_)
