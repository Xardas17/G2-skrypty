// spcCWindowResizeStyle.cpp: Implementierung der Klasse spcCWindowResizeStyle.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "zengine.h"
#include "spcCWindowResizeStyle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

spcCWindowResizeStyle::spcCWindowResizeStyle()
{	
	Init(0,0,WIN_ALIGN_LEFT, WIN_ALIGN_TOP,WIN_ALIGN_LEFT,WIN_ALIGN_TOP);
}

void spcCWindowResizeStyle::Init(CWnd* wnd, CWnd* pnd, spcTWindowAlign left, spcTWindowAlign top, spcTWindowAlign right, spcTWindowAlign bottom, bool realChild)
{
	window = wnd;
	parent = pnd;	
	align_top = top;
	align_bottom = bottom;
	align_left = left;
	align_right = right;
	isRealChild = realChild;
	Calculate();
};

static void SwapLong(long& a, long& b)
{
	long bb=b;
	b=a;
	a=bb;
};

void spcCWindowResizeStyle::Calculate()
{
	if (!parent) return;
	if (!window) return;
	RECT rect;
	if (isRealChild) parent->GetClientRect(&rect);
	else parent->GetWindowRect(&rect);
	
	window->GetWindowRect(&winRect);		// get absolute koordinates	
	if (isRealChild) parent->ScreenToClient(&winRect);

	rectDistances = winRect;

	// calculate distances
	if (align_left	== WIN_ALIGN_RIGHT)		rectDistances.left	= winRect.left - rect.right; else rectDistances.left = winRect.left - rect.left;
	if (align_right	== WIN_ALIGN_RIGHT)		rectDistances.right	= winRect.right - rect.right; else rectDistances.right = winRect.right - rect.left;
	if (align_top	 == WIN_ALIGN_BOTTOM)	rectDistances.top    = winRect.top - rect.bottom; else rectDistances.top = winRect.top - rect.top;
	if (align_bottom == WIN_ALIGN_BOTTOM)	rectDistances.bottom = winRect.bottom - rect.bottom; else rectDistances.bottom = winRect.bottom - rect.top;
	
};

spcCWindowResizeStyle::~spcCWindowResizeStyle()
{

}


bool spcCWindowResizeStyle::UpdateSize()
{
	RECT rect;
	if (isRealChild) parent->GetClientRect(&rect);
	else parent->GetWindowRect(&rect);

	if (align_left == WIN_ALIGN_RIGHT)  winRect.left = rect.right+rectDistances.left; else winRect.left = rect.left+rectDistances.left;
	if (align_right== WIN_ALIGN_RIGHT)  winRect.right = rect.right+rectDistances.right; else winRect.right = rect.left+rectDistances.right;
	if (align_top	 == WIN_ALIGN_BOTTOM) winRect.top = rect.bottom+rectDistances.top; else winRect.top = rect.top+rectDistances.top;
	if (align_bottom == WIN_ALIGN_BOTTOM) winRect.bottom = rect.bottom+rectDistances.bottom; else winRect.bottom = rect.top+rectDistances.bottom;	
		
	//if (winRect.left>winRect.right) winRect.right = winRect.left;
	//if (winRect.top>winRect.bottom) winRect.bottom = winRect.top;

	window->MoveWindow(&winRect,TRUE);
	return true;
};
