// spcCColorListbox.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCColorListbox.h"
#include "zstring.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCColorListbox

spcCColorListbox::spcCColorListbox()
{
}

spcCColorListbox::~spcCColorListbox()
{
}


BEGIN_MESSAGE_MAP(spcCColorListbox, CListBox)
	//{{AFX_MSG_MAP(spcCColorListbox)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCColorListbox message handlers
/////////////////////////////////////////////////////////////////////////////
// spcCColorListbox message handlers

void spcCColorListbox::AddColor(int r, int g, int b)
{
	CString s = zSTRING(zSTRING(r)+","+zSTRING(g)+","+zSTRING(b)+",").ToChar();
	AddString(s);	
}

void spcCColorListbox::InsertColor(int index, int r, int g, int b)
{
	CString s = zSTRING(zSTRING(r)+","+zSTRING(g)+","+zSTRING(b)+",").ToChar();
	InsertString(index,s);	
}


void spcCColorListbox::GetCurColor(int& r,int& g,int& b)
{
	int index = GetCurSel();
	if (index==LB_ERR) return;
	CString color;
	GetText(index,color);  // leerer String -> Crash
	zSTRING zcolor = color.GetBuffer(0);
	zSTRING zs;
	zs = zcolor.PickWord(1,",",",");r = zs.ToInt();
	zs = zcolor.PickWord(2,",",",");g = zs.ToInt();
	zs = zcolor.PickWord(3,",",",");b = zs.ToInt();	
}

void spcCColorListbox::GetColor(int index, int& r,int& g,int& b)
{
	if (index==LB_ERR) return;
	CString color;
	GetText(index,color); // leerer String -> Crash
	zSTRING zcolor = color.GetBuffer(0);
	zSTRING zs;
	zs = zcolor.PickWord(1,",",",");r = zs.ToInt();
	zs = zcolor.PickWord(2,",",",");g = zs.ToInt();
	zs = zcolor.PickWord(3,",",",");b = zs.ToInt();	
}


void spcCColorListbox::OnLButtonDblClk(UINT nFlags, CPoint point) 
{	
	BOOL bOutside;
	UINT index = ItemFromPoint( point, bOutside );
	COLORREF color;
	if (index>=0 && (index<GetCount()))
	{
		CString cstr;
		GetText(index,cstr);
		zSTRING zcolor = cstr.GetBuffer(0);
		zSTRING zs;
		int r,g,b;
		zs = zcolor.PickWord(1,",",",");r = zs.ToInt();
		zs = zcolor.PickWord(2,",",",");g = zs.ToInt();
		zs = zcolor.PickWord(3,",",",");b = zs.ToInt();	
		CColorDialog dlg(RGB(r,g,b));
		if (dlg.DoModal()==IDOK)
		{
			color = dlg.GetColor();
			DeleteString(index);
			cstr = zSTRING(zSTRING(GetRValue(color))+","+zSTRING(GetGValue(color))+","+zSTRING(GetBValue(color))+",").ToChar();
			InsertString(index,cstr);
		};
	}
	CListBox::OnLButtonDblClk(nFlags, point);
}

void spcCColorListbox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	// Zeichenbereich holen (CDC=class of device-context objects)
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

	// Zeichenrechteck bestimmen 
	RECT rc = lpDIS->rcItem;
	// x/y = Texturposition oben links
	//int x = rc.left;
	//int y = rc.top;
	// cx/cy = maximale groesse mitsamt Informationsbereich
	//int cx = rc.right-rc.left;
	//int cy = rc.bottom-rc.top;	
		
	CString color;
	if ((signed long)lpDIS->itemID>=0) GetText((signed long)lpDIS->itemID,color); else return;	
	zSTRING zcolor = color.GetBuffer(0);
	int r,g,b;
	zSTRING zs;
	zs = zcolor.PickWord(1,",",",");r = zs.ToInt();
	zs = zcolor.PickWord(2,",",",");g = zs.ToInt();
	zs = zcolor.PickWord(3,",",",");b = zs.ToInt();
	pDC->FillSolidRect( &rc, RGB(r,g,b) );

	if (lpDIS->itemState & ODS_SELECTED)
	{	
		CBrush brush( RGB(255,0,0) );
		pDC->FrameRect( &rc , &brush );
	}
	else
	{
		CBrush brush( RGB(0,0,0) );
		pDC->FrameRect( &rc , &brush);
	}

}

void spcCColorListbox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS) 
{
	lpMIS->itemHeight=16;
}
