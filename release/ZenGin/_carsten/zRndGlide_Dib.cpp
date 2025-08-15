// Justin's nifty DIBSection class for Win32. Feel free to use this in your programs.
// Just email justin@nullsoft.com if you like 'em.
// (And I don't want any bug reports! If you have bugfixes, though, send em my way) :)
// Copr. 1997-1998, Justin Frankel/Nullsoft, Inc.

#include "zcore.h"
#include <windows.h>
#include "zRndGlide_Dib.h"

CDIBSection16	 *dib = 0;	  

void CDIBSection16::SetRect(RECT *r)
{
	m_DeInitialize();
	m_Initialize(m_hwndParent,r);
}

void CDIBSection16::Update()
{
	HDC wndDC = ::GetDC(m_hwndParent);
	m_PreRender(wndDC);
	{
		RECT r;
		::GetWindowRect(m_hwndParent,&r);
		::BitBlt(wndDC,0,0,GetWidth(),GetHeight(),m_hdc,0,0,SRCCOPY);
	}
	::ReleaseDC(m_hwndParent,wndDC);
}

void CDIBSection16::Paint(HDC hdc)
{
	m_PreRender(hdc);
	::BitBlt(hdc,m_rect.left,m_rect.top,GetWidth(),GetHeight(),m_hdc,0,0,SRCCOPY);
}



/*
** 16BPP VERSION
*/

CDIBSection16::CDIBSection16(HWND hwnd,RECT *r)
{
	m_hpal = 0;
	RECT r2;
	if (!r) ::GetClientRect(hwnd,&r2);
	else r2 = *r;
	m_Initialize(hwnd,&r2);
}

CDIBSection16::~CDIBSection16()
{
	m_DeInitialize();
}

void CDIBSection16::m_Initialize(HWND hwndParent, RECT *r)
{	
	m_rect = *r;
	int width = m_rect.right-m_rect.left;
	int height = m_rect.bottom-m_rect.top;
	if (width & 3) width += 3;
	width &= ~3;
	m_hwndParent = hwndParent;
	m_bitmap.bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bitmap.bmi.bmiHeader.biPlanes = 1;
	m_bitmap.bmi.bmiHeader.biBitCount = 16;
	m_bitmap.bmi.bmiHeader.biCompression = BI_BITFIELDS;
	m_bitmap.bmi.bmiHeader.biSizeImage = 0;
	m_bitmap.bmi.bmiHeader.biClrUsed = 0;
	m_bitmap.bmi.bmiHeader.biClrImportant = 0;
	m_bitmap.bmi.bmiHeader.biWidth = width;
	m_bitmap.bmi.bmiHeader.biHeight = -height;
	m_bitmap.bmi.bmiHeader.biSizeImage = 0;
	unsigned int *a = (unsigned int *) m_bitmap.bmi.bmiColors;
	a[0] = 0xF800;
	a[1] = 0x7E0;
	a[2] = 0x1f;
	m_hdc = ::CreateCompatibleDC(NULL);
	m_hbm = ::CreateDIBSection(m_hdc,&m_bitmap.bmi,DIB_RGB_COLORS, &m_bitmap.data, NULL, 0);
    m_oldhbm = (HBITMAP) ::SelectObject(m_hdc, m_hbm);
	m_SetupPalette();
}

void CDIBSection16::m_SetupPalette()
{
	int c;
	struct 
	{
		LOGPALETTE logpal;
		PALETTEENTRY palentries[255];
	} palette;
	palette.logpal.palVersion = 0x300;
	palette.logpal.palNumEntries = 256;

	for (c = 0; c < 256; c ++) 
	{
		palette.logpal.palPalEntry[c].peRed = c;
		palette.logpal.palPalEntry[c].peGreen = c;
		palette.logpal.palPalEntry[c].peBlue = c;
		palette.logpal.palPalEntry[c].peFlags = 0;
	}
	if (m_hpal) ::DeleteObject(m_hpal);
	m_hpal = ::CreatePalette((LOGPALETTE *)&palette.logpal);
	HDC dc = ::GetDC(NULL);
	::SelectPalette(dc,m_hpal,FALSE);
	::RealizePalette(dc);
	::UpdateColors(dc);
	::ReleaseDC(NULL,dc);
}

void CDIBSection16::m_DeInitialize()
{
	if (m_hpal) ::DeleteObject(m_hpal);
	m_hpal = 0;
    if (m_hdc) {
		::SelectObject(m_hdc, m_oldhbm);
		::DeleteObject(m_hbm);
		::DeleteDC(m_hdc);
	}
	m_hdc = 0;
	m_hbm = 0;
}

void CDIBSection16::m_PreRender(HDC hdc)
{
	::SelectPalette(hdc,m_hpal,FALSE);
	::RealizePalette(hdc);
}
