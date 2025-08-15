
// Implementation

#include "stdafx.h"

#include "zengine.h"

#include "spcCDiagramVP.h"
#include "spcCDiagramDraw.h"

#include "zCCSCutscene.h"

const int LEFT_BORDER = 10;

spcCDiagramVP :: spcCDiagramVP() 
			: spcCDiagramDraw(), lastPos(0,0), ghostRect(0,0,0,0)
{ 
	xoff			= 0;
	yoff			= 0;
	xdel			= 100;
	ydel			= 100;
	blockMovement	= false;
	timeScale		= 5;
	timeOffset		= 0;
	gUNIT			= 10;
}

spcCDiagramVP :: ~spcCDiagramVP() {}

/*
CPoint lastPick;		// letzte PickAktion für BlockMove merken

	bool blockMovement;		// wird ein Block bewegt
	CPoint lastPos;			// letzte Position des ghosts
	CRect ghostRect;		// Ausmaße des Blocks

  */

// zeigt die Daten der logische zeile <line> von der logischen Position <fromPos>
int spcCDiagramVP :: DrawData(CDC* dc, CTreeCtrl& tracks, 
							   zCArray<zCCSBlockBase*> &data, int fromPos,
							   int selected)
{
	int maxPos = 0;

	dc->IntersectClipRect	(xoff,yoff,xoff+xdel,yoff+ydel);
	dc->SetViewportOrg		(xoff,yoff);
	CRect rec(CPoint(0,0),CPoint(xdel,ydel));
	dc->Rectangle(rec);
	
	// den Baum durchlaufen, ermitteln, welche sichtbar sind
	int trackShade = 0;
	int trackCount = 0;
	
	zCCSBlockBase*	actBlock	= 0;
	// zCCSBlock*		actBlock2	= 0;
	int		scale			= gUNIT * timeScale;

	COLORREF bkcol = dc->GetBkColor();
	if (timeOffset<LEFT_BORDER)
	{
		dc->FillSolidRect(0,0,LEFT_BORDER-timeOffset,rec.bottom-rec.top,RGB(150,150,150));
		dc->MoveTo(LEFT_BORDER-timeOffset,0);
		dc->LineTo(LEFT_BORDER-timeOffset,rec.bottom-rec.top);
	};	
	dc->SetBkColor(bkcol);

	DrawScale(dc,scale, timeOffset);
	
	HTREEITEM track = tracks.GetFirstVisibleItem();
	while (track!=NULL)
	{
		// zugehörigen Block ermitteln
		int trackNum = tracks.GetItemData(track);
		if (trackNum>=0 && trackNum<data.GetNumInList()) 
		{
			// Jetzt den aktuellen Block zeichnen (oder auch nicht :-)
			actBlock = data[trackNum];						

			if (dynamic_cast<zCCSAtomicBlock*>(actBlock))  // das ist ein AI-Comm
			{				
				if (actBlock->GetDBFlag()) SetColor(2); else SetColor(1); // Gerade in Bearbeitung?				

				// Position und MinTime
				double pos			= data[1]->GetChildPos(trackNum-2)->position;								
				double focusMinTime	= data[2]->GetMinTime();
				if (focusMinTime<1.0F) focusMinTime = 1.0F;
				pos = pos * focusMinTime;

				zCSTIME lTime = actBlock->GetMinTime();				
				if (lTime<1) lTime = 1;
				
				double x = scale*pos - timeOffset + LEFT_BORDER;
				double x2= x + lTime*scale;
				double y = 1+16*trackCount;
				DrawBlock(dc,
					CRect(	int(x),
							int(y),				
							int(x2),
							int(y+15) 
						),											// Koordinaten (Rechteck)
					actBlock,
					trackNum==selected);							// selektiert?				

				if (maxPos < int(x2+timeOffset)) maxPos = int(x2+timeOffset);
			}
			else
			{
				trackShade++;				
			}

		}
		trackCount++;
		track = tracks.GetNextVisibleItem(track);
	}			

	return maxPos;
}



// löscht den Zeiger auf die Daten und den Viewport; nichts wird angezeigt
void spcCDiagramVP :: ClearData(CDC* dc)
{
	CRect rec(CPoint(xoff,yoff),CPoint(xoff+xdel,yoff+ydel));
	dc->Rectangle(rec);
}


bool spcCDiagramVP :: IsInMovement(CPoint mp) 
{
	return blockMovement; 
}


//
// Ermitteln ob an dem angegebenen Punkt im Viewport ein Block steht
//
int spcCDiagramVP :: PickData(CPoint mp, CTreeCtrl& tracks, zCArray<zCCSBlockBase*> &data, int fromPos)
{
	CPoint realPoint(mp.x-xoff,mp.y-yoff);

	zCCSBlockBase*	actBlock	= 0;	
	HTREEITEM		track		= tracks.GetFirstVisibleItem();	
	int				trackCount	= 0;
	int				scale		= gUNIT * timeScale;	
	double			offset		= timeOffset;

	while (track)
	{
		// zugehörigen Block ermitteln
		int trackNum = tracks.GetItemData(track);
		if (trackNum!=-1) 
		{
			actBlock = data[trackNum];
			if (dynamic_cast<zCCSAtomicBlock*>(actBlock))
			{
				SetColor(1);
				zCSTIME lTime = actBlock->GetMinTime();
				if (lTime<1) lTime = 1;
				// ueber Vater die Position holen
				double pos = data[1]->GetChildPos(trackNum-2)->position;
				// MinTime vom focus verrechnen
				double focusMinTime = data[2]->GetMinTime();
				if (focusMinTime<1.0F) focusMinTime = 1.0F;
				pos = pos*focusMinTime;


				double x = scale*pos - offset + LEFT_BORDER;
				double y = 1+16*trackCount;
				CRect lGho(
					int(x),
					int(y),
					int(x+lTime*scale),
					int(y+15)
				);
				ghostRect = lGho;
			
				if (lGho.PtInRect(realPoint)) 
				{
					lastPick = realPoint;
					return tracks.GetItemData(track);
				}
			}
		}
		trackCount++;
		track = tracks.GetNextVisibleItem(track);
	}
	lastPick	= CPoint(-1,-1);
	ghostRect	= CRect(0,0,0,0);
	return -1;
}


// liefert die logische Breite
int spcCDiagramVP :: GetWidth()
{
	return 0;  // TODO: Berechnung erweitern
}

void spcCDiagramVP :: BeginBlockMovement(CDC* dc, CPoint mp)
{
	if (blockMovement) return; else blockMovement = true;	

	dc->IntersectClipRect	(xoff,yoff,xoff+xdel,yoff+ydel);
	dc->SetViewportOrg		(xoff,yoff);
	dc->SetROP2(R2_NOT);

	lastPos = lastPick;
	CPoint realPoint(mp.x-xoff,mp.y-yoff);	

	CRect lRect = ghostRect;
	lRect.OffsetRect(realPoint.x-lastPick.x,0);
		
	dc->Rectangle(lRect);

	dc->MoveTo(lRect.left,0);
	dc->LineTo(lRect.left,ydel);

	dc->SetROP2(R2_COPYPEN);
}

void spcCDiagramVP :: BlockMove(CDC* dc, CPoint mp)
{
	if (!blockMovement) return;

	dc->IntersectClipRect	(xoff,yoff,xoff+xdel,yoff+ydel);
	dc->SetViewportOrg		(xoff,yoff);
	dc->SetROP2(R2_NOT);

	CPoint	realPoint(mp.x-xoff,mp.y-yoff);	
	CRect	lRect(ghostRect);
	lRect.OffsetRect(lastPos.x-lastPick.x,0);
		
	dc->MoveTo(lRect.left,0);
	dc->LineTo(lRect.left,ydel);
	// rubber wegmachen
	dc->Rectangle(lRect);	
	// rubber zeichnen
	lRect = ghostRect;
	lRect.OffsetRect(realPoint.x-lastPick.x,0);
	dc->Rectangle(lRect);
	lastPos = realPoint;

	dc->MoveTo(lRect.left,0);
	dc->LineTo(lRect.left,ydel);

	dc->SetROP2(R2_COPYPEN);
}
int spcCDiagramVP :: EndBlockMovement(CDC* dc, CPoint mp)
{	
	if (!blockMovement) return 0; else blockMovement = false;		
	
	dc->IntersectClipRect	(xoff,yoff,xoff+xdel,yoff+ydel);
	dc->SetViewportOrg		(xoff,yoff);
	dc->SetROP2				(R2_NOT);
	CPoint	realPoint		(mp.x-xoff,mp.y-yoff);	
	CRect	lRect(ghostRect);
	lRect.OffsetRect(lastPos.x-lastPick.x,0);
	
	dc->MoveTo(lRect.left,0);
	dc->LineTo(lRect.left,ydel);

	dc->Rectangle(lRect);
	dc->SetROP2(R2_COPYPEN);

	int result = realPoint.x-lastPick.x;	
	return result;
}

void spcCDiagramVP::MoveWindow(RECT* rect)
{	
	spcCDiagramDraw::MoveWindow(rect);

	xoff = rect->left;
	yoff = rect->top;
	xdel = rect->right-rect->left;
	ydel = rect->bottom-rect->top;
}

