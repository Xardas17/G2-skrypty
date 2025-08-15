#if !defined(AFX_spcCMatListbox_H__DE70E944_3870_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_spcCMatListbox_H__DE70E944_3870_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCMatListbox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spcCMatListbox window

#include "spcCDibSection.h"
#include "zcontainer.h"

class zCTexture;
class zCMaterial;

void ConvertTextureToDIB (zCTexture* sourceTexture, spcCDibSection* dib);


struct spcCTextureCacheItem
{
	spcCDibSection* dib;
	bool			inUse;

	spcCTextureCacheItem() { dib=0; inUse=false; };
};

class spcCTextureDibCache
{
public:
	spcCTextureDibCache();
	virtual ~spcCTextureDibCache();

	spcCDibSection*		GetDib(int index, bool& use);
	void				Reset();

protected:
	zCArray<spcCTextureCacheItem*>	list;	
};

class spcCMatListbox : public CListBox
{
public:
	
	spcCMatListbox();
	virtual ~spcCMatListbox();

	spcCTextureDibCache	dibCache;
	zCList<zCMaterial>	current_matlist;	


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCMatListbox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void		SelectMaterial(zCMaterial* mat);
	void		UpdateList();
	CString		filterName;	
	void		CreateList(CString filter);	
	void		RemoveSelected();	

	zCMaterial* selectedMaterial;

	// Generated message map functions
protected:
	int topLine;
	int selectedLine;
	//{{AFX_MSG(spcCMatListbox)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnSelchange();
	//}}AFX_MSG
	
	int num_columns;
	int num_pix_space;
	int num_pix_mat;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_spcCMatListbox_H__DE70E944_3870_11D2_8AB9_0080AD209698__INCLUDED_)
