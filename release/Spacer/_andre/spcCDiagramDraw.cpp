// Diagram Draw implementation

#include "stdafx.h"
#include "zengine.h"

#include "zccscutscene.h"
#include "spcCDiagramDraw.h"



spcCDiagramDraw :: spcCDiagramDraw()
	: clippingRectangle(), color(0), textHight(THSmall)
{
	brush[0].CreateSolidBrush(RGB(200,0,0));
	brush[1].CreateSolidBrush(RGB(0,200,0));
	brush[2].CreateSolidBrush(RGB(196,196,250));
	brush[3].CreateSolidBrush(RGB(0,200,200));
	brush[4].CreateSolidBrush(RGB(200,200,0));
	brush[5].CreateSolidBrush(RGB(200,0,200));
	brush[6].CreateSolidBrush(RGB(250,0,200));
	brush[7].CreateSolidBrush(RGB(100,0,200));
	brush[8].CreateSolidBrush(RGB(250,50,250));
	markBrush.CreateSolidBrush(RGB(250,0,0));
}

spcCDiagramDraw :: ~spcCDiagramDraw() {}
	
void spcCDiagramDraw::MoveWindow(RECT* clipRect)
{
	clippingRectangle.SetRect(clipRect->left,clipRect->top,clipRect->right,clipRect->bottom);
};

void spcCDiagramDraw :: SetTextHight(TSpcTextHight th)
{
	textHight = th;
}

void spcCDiagramDraw :: SetColor(int entry) { color = entry; }

///
// Draw-Methoden
//
// timeRect = Rechteck, das die Dauer des Events andeutet
// syncRect = Rechtweck, das die Verweildauer des Events im SyncBlock andeutet
///
void spcCDiagramDraw :: DrawBlockZero(CDC* dc, const CRect & block, const CString & text)
{		
	CRect syncRect(block.left,block.top,block.left+block.bottom-block.top,block.bottom);
	dc->SelectObject	(&brush[color]);
	dc->RoundRect		(syncRect,CPoint(8,8));	
	dc->SetBkMode		(TRANSPARENT);		
	dc->ExtTextOut		(syncRect.right+1,syncRect.top+1,ETO_CLIPPED,NULL,text,NULL);
}
void spcCDiagramDraw :: DrawBlockFix(CDC* dc, const CRect & block, const CString & text, zBOOL fireAndForget)
{		
	CRect syncRect(block.left+2,block.top,block.right-2,block.bottom);		
	CRect timeRect(block.left,block.top,block.right,block.bottom);		

	if (fireAndForget) syncRect.right = syncRect.left + (syncRect.bottom - syncRect.top);

	dc->Rectangle		(timeRect);
	dc->SelectObject	(&brush[color]);
	dc->Rectangle		(syncRect);		

	dc->SetBkMode		(TRANSPARENT);
	dc->ExtTextOut		(syncRect.left+3,syncRect.top+1,ETO_CLIPPED,0,text,NULL);	
}
void spcCDiagramDraw :: DrawBlockUnknown(CDC* dc, const CRect & block, const CString & text, zBOOL fireAndForget)
{	
	CPen newPen;newPen.CreatePen(PS_DOT,0,RGB(0,0,0));
	dc->SelectObject	(&newPen);	

	CRect syncRect(block);
	CRect timeRect(block);timeRect.right+=12;		

	if (fireAndForget) syncRect.right = syncRect.left + (syncRect.bottom - syncRect.top);

	dc->Rectangle		(timeRect);
	dc->SelectObject	(&brush[color]);
	dc->Rectangle		(syncRect);	
	dc->SetBkMode		(TRANSPARENT);	
	dc->ExtTextOut		(syncRect.left+3,syncRect.top+1,ETO_CLIPPED,0,text,NULL);		
}
void spcCDiagramDraw :: DrawBlockAssembled(CDC* dc, const CRect & block, const CString & text, zBOOL fireAndForget)
{				
	int len				= block.bottom-block.top;	
	CRect syncRect		(block.left,block.top,block.left+len,block.bottom);			
	dc->SelectObject	(&brush[color]);
	dc->Rectangle		(syncRect);		
	dc->MoveTo			(syncRect.left+4,syncRect.top + (len/2));
	dc->LineTo			(syncRect.right-4,syncRect.top + (len/2));
	dc->SetBkMode		(TRANSPARENT);
	dc->ExtTextOut		(syncRect.right+1,syncRect.top+1,ETO_CLIPPED,0,text,NULL);		
}


void spcCDiagramDraw :: DrawBlock(CDC* dc, const CRect & block, zCCSBlockBase* bl, bool selected)
{
	int font = (textHight==THSmall) ? ANSI_VAR_FONT : SYSTEM_FONT;	

	CBrush* oldBrush = dc->GetCurrentBrush();
	CPen*	oldPen   = dc->GetCurrentPen();

	zCEventMessage::zTTimeBehavior mType = bl->GetCommand()->MD_GetTimeBehavior();	
	
	zSTRING text			= bl->GetInfo();
	zBOOL	isJob			= bl->GetCommand()->IsJob();	
	zBOOL	synchronized	= !dynamic_cast<zCCSAtomicBlock*>(bl) || dynamic_cast<zCCSAtomicBlock*>(bl)->IsSynchronized();
	zBOOL	fireAndForget	= !synchronized || !isJob;
		
	dc->SelectStockObject(font);
	
	CString infotext(text.ToChar());
	switch (mType)
	{
		case zCEventMessage::TBZero:
			DrawBlockZero(dc,block,infotext);
			break;
		case zCEventMessage::TBFix:		
			DrawBlockFix(dc,block,infotext, fireAndForget);
			break;
		case zCEventMessage::TBUnknown:		
			DrawBlockUnknown(dc,block,infotext, fireAndForget);
			break;
		case zCEventMessage::TBAssembled:		
			DrawBlockAssembled(dc,block,infotext, fireAndForget);
			break;
	};


	if (!synchronized)
	{				
		dc->SelectStockObject(SYSTEM_FONT);			
		COLORREF oldColor = dc->SetTextColor(RGB(255,0,0));
		dc->TextOut(block.left-5,block.top,"!");
		dc->SetTextColor(oldColor);
		
	};
	
	if (selected) dc->InvertRect(&block);
	
	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);
}

void spcCDiagramDraw :: DrawDragBlock(CDC* dc, const CRect & block, zCEventMessage::zTTimeBehavior mType)
{
	dc->Rectangle(block);
}

void spcCDiagramDraw :: DrawScale(CDC* dc, int scale, int offset)
{
	// dc->FillSolidRect(0,0,clippingRectangle.right,8,RGB(255,255,255));

	// int breite = (clippingRectangle.Width() / scale);
	int x = 0;
	int sec10=0;
	while (x < clippingRectangle.Width())
	{			
		x = int (sec10 * float(scale/10.0) - offset + 10.0);
		if (x>=0 && x<clippingRectangle.Width())
		{
			dc->MoveTo(x,0);
			if (sec10%10==0)
			{
				dc->LineTo(x,8);
				if (scale>=30)	// Text anzeigen
				{
					CString s;
					s.Format("%i",sec10/10);
					dc->TextOut(x+2,2,s);
				}
			}
			else if (sec10%10==5)
			{
				dc->LineTo(x,5);
			}
			else if (scale>=50)
			{
				dc->LineTo(x,3);
			}						
		};		
		sec10++;						
	}
}