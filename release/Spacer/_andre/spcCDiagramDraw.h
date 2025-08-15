// Block draw klasse

// Anforderungen

/*
- Zeichnen von offenen Blöcken mit Text (s.o.)
- selbständiges/intelligentes Clippen (symbolik soll erhalten bleiben)
- selektierte Blöcke bekommen autogenerierte Farbe
  */


#ifndef _SPCCDIAGRAMDRAW_H_
#define _SPCCDIAGRAMDRAW_H_

#ifndef _ZENGINE_H_
	#include "afxwin.h"
#endif
// #include "zengine.h"
#include "zVob.h"

class zCCSBlockBase;

class spcCDiagramDraw
{
public:
	enum TSpcTextHight { THBig, THSmall };

private:
	int				color;				// usedColor;
	CRect			clippingRectangle;	// evtl nicht nötig
	CBrush			brush[9];			// palette
	CBrush			markBrush;
	TSpcTextHight	textHight;

	void DrawBlockZero			(CDC* dc, const CRect & block, const CString & text);
	void DrawBlockFix			(CDC* dc, const CRect & block, const CString & text, zBOOL fireAndForget=FALSE);
	void DrawBlockUnknown		(CDC* dc, const CRect & block, const CString & text, zBOOL fireAndForget=FALSE);
	void DrawBlockAssembled		(CDC* dc, const CRect & block, const CString & text, zBOOL fireAndForget=FALSE);
	
public:
	spcCDiagramDraw			();
	virtual ~spcCDiagramDraw();

	void MoveWindow			(RECT* clipRect);
	
	void SetTextHight		(TSpcTextHight th);
	void SetColor			(int entry);
	void DrawBlock			(CDC* dc, const CRect & block, zCCSBlockBase* bl, bool selected=false);
	void DrawDragBlock		(CDC* dc, const CRect & block, zCEventMessage::zTTimeBehavior mType);
	void DrawScale			(CDC* dc, int scale, int offset);
};

#endif
