#ifndef _OVIEWSTATUSBAR_H_
#define _OVIEWSTATUSBAR_H_

#include "zviewstatusbar.h"

class oCViewStatusBar : public zCViewStatusBar
{
public:
	oCViewStatusBar();	
	oCViewStatusBar(int x1,int y1,int x2,int y2, zTviewID viewID = VIEW_ITEM);
	virtual ~oCViewStatusBar();
	void Init(int x, int y, float _scale = 1.0f);

	void SetTextures(const zSTRING& view, const zSTRING& rangebar, const zSTRING& valuebar,const zSTRING &previewBar = zSTR_EMPTY);

	virtual void SetMaxRange(zVALUE _low, zVALUE _high);
	virtual void SetRange(zVALUE _low, zVALUE _high);
	virtual void SetPreview(zVALUE _value);	
	virtual void SetValue(zVALUE _value);	

protected:
	float scale;
	zCView* range_bar;
	zCView* value_bar;
	//zCView* preview_bar;			// muss raus, crash beim runterfahren mit "znofastexit"

	zSTRING texView;
	zSTRING texRange;
	//zSTRING texPreview;
	zSTRING texValue;
};


#endif