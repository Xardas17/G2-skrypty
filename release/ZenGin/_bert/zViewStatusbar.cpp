#include "zcore.h"
#include "zviewstatusbar.h"


zCViewStatusBar::zCViewStatusBar()
{
	Init();
};

zCViewStatusBar::zCViewStatusBar(int x1,int y1,int x2,int y2, zTviewID viewID)
: zCView(x1,y1,x2,y2,viewID)
{
	Init();
};

void zCViewStatusBar::Init()
{
	minLow = 0;
	maxHigh = 100;
	low=0;
	high=100;
	previewValue = 0;
	currentValue = 50;
};

zCViewStatusBar::~zCViewStatusBar()
{
};

void zCViewStatusBar::SetMaxRange(zVALUE _low, zVALUE _high)
{
	if (_low<0) _low=0;
	if (_high<0) _high=0;
	if (_low>_high) zSwap(_low,_high);
	minLow = _low;
	maxHigh= _high;
	if (high>maxHigh) high = maxHigh;
	if (low <minLow)  low  = minLow;
};

void zCViewStatusBar::SetRange(zVALUE _low, zVALUE _high)
{
	if (_low<0) _low=0;
	if (_high<0) _high=0;
	if (_low>_high) zSwap(_low,_high);
	if (_low<minLow) _low = minLow;	
	if (_high>maxHigh) _high = maxHigh;
	low = _low;
	high = _high;
};

void zCViewStatusBar::SetPreview(zVALUE _value)
{
	if (_value<minLow) _value = minLow;
	if (_value>maxHigh) _value = maxHigh;
	previewValue = _value;
};



void zCViewStatusBar::SetValue(zVALUE _value)
{
	if (_value<minLow) _value = minLow;
	if (_value>maxHigh) _value = maxHigh;
	currentValue = _value;
};
