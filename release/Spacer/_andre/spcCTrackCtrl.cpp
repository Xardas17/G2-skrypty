// spcCTrackCtrl.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCTrackCtrl.h"

#include "spcCCSSequencer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCTrackCtrl

spcCTrackCtrl::spcCTrackCtrl()
{
}

spcCTrackCtrl::~spcCTrackCtrl()
{
}


BEGIN_MESSAGE_MAP(spcCTrackCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(spcCTrackCtrl)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCTrackCtrl 

BOOL spcCTrackCtrl::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
{	
	BOOL result = CTreeCtrl::OnMouseWheel(nFlags,zDelta,pt);
	spcCCSSequencer* dv = dynamic_cast<spcCCSSequencer*>(GetParent());
	if (dv)	dv->ViewDrawIfNessesary();	
	return result;
};

void spcCTrackCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CTreeCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	spcCCSSequencer* dv = dynamic_cast<spcCCSSequencer*>(GetParent());
	if (dv)	dv->ViewDrawIfNessesary();
}

void spcCTrackCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	HTREEITEM hItem = HitTest(point);
	if (!hItem) return;

	SelectItem(hItem);
	
	CTreeCtrl::OnRButtonDown(nFlags,point);
};