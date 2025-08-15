#ifndef __ZVIEWSTATUSBAR_H__
#define __ZVIEWSTATUSBAR_H__

#ifndef __ZVIEW_H__
#include "zview.h"
#endif

class zCViewStatusBar : public zCView
{
public:
	zCViewStatusBar();	
	zCViewStatusBar(int x1,int y1,int x2,int y2, zTviewID viewID = VIEW_ITEM);
	
	virtual ~zCViewStatusBar();
	
	void Init();

	virtual void SetMaxRange		(zVALUE _low, zVALUE _high);
	virtual void SetRange			(zVALUE _low, zVALUE _high);
	virtual void SetPreview			(zVALUE _value);	
	virtual void SetValue			(zVALUE _value);	

protected:

	zVALUE minLow, maxHigh;
	zVALUE low, high;
	zVALUE previewValue;
	zVALUE currentValue;
};

#endif