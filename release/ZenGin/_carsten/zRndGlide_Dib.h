/********************************************************************************
 
 Project : Phoenix
 File    : zRndGlide_Dib.h
 Author  : Carsten Edenfeld (partly orig. by Justin Frankel)
 Version : 0.00
 Created : 23.02.98
 Last Mod: 23.02.98
 
*********************************************************************************
 TODO : 
*********************************************************************************
 BUGS : 
*********************************************************************************
 NOTE : 
*********************************************************************************/


#ifndef __DIBSECTION_H__
#define __DIBSECTION_H__

#include <windows.h>

class CDIBSection16 
{
protected:
		RECT m_rect;
		HWND m_hwndParent;
		HPALETTE m_hpal;
		HDC m_hdc;
		HBITMAP m_hbm, m_oldhbm;

		struct
		{
			BITMAPINFO bmi;
			RGBQUAD more_bmiColors[256];
			LPVOID data;
		} m_bitmap;

		void m_Initialize(HWND hwnd, RECT *r);
		void m_DeInitialize();
		void m_PreRender(HDC hdc); 
		void m_SetupPalette();
public:
		void SetPalette(unsigned char *palette);
		void SetRect(RECT *r=NULL);
		void *GetBuffer() {  return m_bitmap.data; }
		void Update();
		void Paint(HDC hdc);
		int GetWidth() { return (m_rect.right-m_rect.left); }
		int GetPitch() { return (m_rect.right-m_rect.left+3)&~3; }
		int GetHeight() { return m_rect.bottom-m_rect.top; }
		CDIBSection16(HWND hwnd=NULL,RECT *r=NULL);
		~CDIBSection16();

};

extern CDIBSection16	 *dib;


#endif