// spcCWindowResizeStyle.h: Schnittstelle für die Klasse spcCWindowResizeStyle.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPCCWINDOWRESIZESTYLE_H__1814FCE9_E851_11D3_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_SPCCWINDOWRESIZESTYLE_H__1814FCE9_E851_11D3_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum spcTWindowAlign { WIN_ALIGN_TOP, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_RIGHT };

class spcCWindowResizeStyle  
{
public:	
	spcCWindowResizeStyle();
	virtual ~spcCWindowResizeStyle();

	void Init(CWnd* wnd, CWnd* pnd, spcTWindowAlign left, spcTWindowAlign top, spcTWindowAlign right, spcTWindowAlign bottom, bool realChild = true);	
	bool UpdateSize();
	void Calculate();

protected:	

	bool isRealChild;
	CWnd* window;
	CWnd* parent;
	spcTWindowAlign align_top;
	spcTWindowAlign align_bottom;
	spcTWindowAlign align_left;
	spcTWindowAlign align_right;
	RECT rectDistances;
	RECT winRect;
};

#endif // !defined(AFX_SPCCWINDOWRESIZESTYLE_H__1814FCE9_E851_11D3_BA4F_0050DA339C1B__INCLUDED_)
