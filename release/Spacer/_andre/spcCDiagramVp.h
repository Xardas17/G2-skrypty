// spcCDiagramVP
// Viewport auf einem CDC, auf dem Diagramme (Cutscenes) dargestellt werden sollen

#ifndef _SPCCDIAGRAMVIEWPORT_H_
#define _SPCCDIAGRAMVIEWPORT_H_

#include "spcCDiagramDraw.h"
#include "zcontainer.h"

class zCCSBlockBase;

class spcCDiagramVP : public spcCDiagramDraw {
private:
	// workingConstants
	int gUNIT;

private:
	int xoff,yoff;			// position auf dem CDC
	int xdel,ydel;			// breite und höhe des ports
	CPoint lastPick;		// letzte PickAktion für BlockMove merken

	bool blockMovement;		// wird ein Block bewegt
	CPoint lastPos;			// letzte Position des ghosts
	CRect ghostRect;		// Ausmaße des Blocks

	int timeScale;
	int timeOffset;

public:
	spcCDiagramVP			();	
	virtual ~spcCDiagramVP	();

	virtual void MoveWindow	(RECT* rect);

	int		GetTimeOffset	()					{ return timeOffset; };	
	void	SetTimeOffset	(int _offset)		{ timeOffset = _offset; };	
	
	void	SetTimeScale	(int _scale)		{ timeScale = _scale; };
	int		GetTimeScale	()					{ return timeScale; };
	int		IncTimeScale	()					{ return ++timeScale; };
	int		DecTimeScale	()					{ return --timeScale; };

	int		GetWinWidth		() { return xdel; };
	void	GetWinOffset	(int& x, int& y)	{ x=xoff;y=yoff; };

	// Skalierung der Zeitachse	
	double GetPixelTimeValue() { return 1/double(timeScale*gUNIT); };

	// zeigt die Daten der logische zeile <line> von der logischen Position <fromPos>
	int	DrawData		(CDC* dc, CTreeCtrl& tracks, zCArray<zCCSBlockBase*> &data, int fromPos, int selected = -1);

	// löscht den Zeiger auf die Daten und den Viewport; nichts wird angezeigt
	void	ClearData		(CDC* dc);

	// ermittelt den Block, der an dieser stelle dargestellt wird
	int		PickData		(CPoint mp, CTreeCtrl& tracks, zCArray<zCCSBlockBase*> &data, int fromPos);

	CPoint	GetLastPick()	{ return CPoint(lastPick.x+xoff,lastPick.y+yoff); };

	// BlockBewegungs-Methoden
	void BeginBlockMovement	(CDC* dc, CPoint mp);
	void BlockMove			(CDC* dc, CPoint mp);
	// gibt die relative Bewegungsweite zurück
	int  EndBlockMovement	(CDC* dc, CPoint mp);
	bool IsInMovement		(CPoint mp) ;	

	// liefert die logische Breite
	int GetWidth	();

};

#endif