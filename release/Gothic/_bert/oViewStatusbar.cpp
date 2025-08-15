#include "zcore.h"
#include "oviewstatusbar.h"

// Urpsurngsdesign-Groesse
const int BAR_SCALEX = 800;	// [BENDLIN] 800x600, old = 640
const int BAR_SCALEY = 600;	// [BENDLIN] 800x600, old = 480

// Ausmasse einer StatusBar in Pixeln (Fuer obige Aufloesung )
const int BAR_SIZEX = 180;	// [BENDLIN] 800x600, 225???
const int BAR_SIZEY = 20;	// [BENDLIN] 800x600, 25???

// Breite des Randes zu Child-Views (in logischen Koordinaten)
const int BAR_FRAME_X = 350;
const int BAR_FRAME_Y = 1100;

static int bar_sizex;
static int bar_sizey;

static int bar_frame_x;
static int bar_frame_y;


// [EDENFELD] 1.09 Preview Bar hinzugefügt


static void CalculateNormalized(zCView* view, float scale)
{
	/*
	int xdim = zrenderer->vid_xdim;
	int ydim = zrenderer->vid_ydim;
		
	float xmult = scale * ((float)xdim/(float)BAR_SCALEX);
	float ymult = scale * ((float)ydim/(float)BAR_SCALEY);

	bar_sizex	= int(screen->anx(BAR_SIZEX) / xmult);
	bar_sizey	= int(screen->any(BAR_SIZEY) / ymult);

	*/
	// Rahmen fuer child-views
	bar_frame_x	= BAR_FRAME_X; //int(view->anx(BAR_FRAME_X) * xmult);
	bar_frame_y	= BAR_FRAME_Y; // int(view->any(BAR_FRAME_Y) * ymult);

	// Groesse des Elements	
	bar_sizex	= int(screen->anx(BAR_SIZEX));
	bar_sizey	= int(screen->any(BAR_SIZEY));
};


oCViewStatusBar::oCViewStatusBar()
{
	scale = 1.0f;
	value_bar=0;
	range_bar=0;
	//preview_bar = 0;
};

oCViewStatusBar::oCViewStatusBar(int x1,int y1,int x2,int y2, zTviewID viewID)
: zCViewStatusBar(x1,y1,x2,y2,viewID)
{
	scale = 1.0f;
	value_bar=0;
	range_bar=0;
	//preview_bar = 0;

};

void oCViewStatusBar::Init(int x, int y, float _scale)
{
	scale = _scale;

	CalculateNormalized(this, scale);	

	SetPos(x,y);
	SetSize(bar_sizex,bar_sizey);

	zCViewStatusBar::Init();
	
	if (!range_bar) range_bar = zNEW(zCView(0,0,4000,4000));
	InsertItem(range_bar);	

	//if (!preview_bar) preview_bar = zNEW(zCView(0, 0, 2000, 2000));
	//range_bar->InsertItem(preview_bar);		

	if (!value_bar) value_bar = zNEW(zCView(0,0,2000,2000));
	range_bar->InsertItem(value_bar);		

	SetMaxRange	(0,100);
	SetRange	(0,50);
	//SetPreview	(0);
	SetValue	(25);
};

/*	------------------------------------------------------------------
	oCViewStatusBar::SetTextures
	13.09.00	[Hildebrandt]	
				Methodenparameter werden nun per konst. Ref. statt by value uebergeben
	------------------------------------------------------------------ */

void oCViewStatusBar::SetTextures(const zSTRING& view, const zSTRING& rangebar, const zSTRING& valuebar, const zSTRING &previewBar)
{
	texView = view;
	texRange = rangebar;
	texValue = valuebar;
	// Hauptview
	InsertBack(texView);
	SetTransparency(255);
	SetAlphaBlendFunc(zRND_ALPHA_FUNC_BLEND);
	// TempRange-View
	range_bar->InsertBack(texRange);
	//range_bar->SetTransparency(255);
	//range_bar->SetAlphaBlendFunc(zRND_ALPHA_FUNC_BLEND);
	// Value-View
	value_bar->InsertBack(texValue);	

	// Preview-View
	//preview_bar->InsertBack(texPreview);	
	//preview_bar->SetTransparency(128);
	//preview_bar->SetAlphaBlendFunc(zRND_ALPHA_FUNC_BLEND);
};

oCViewStatusBar::~oCViewStatusBar()
{	
	delete value_bar;value_bar=0;
	delete range_bar;range_bar=0;	
	//delete preview_bar;preview_bar=0;	
};

void oCViewStatusBar::SetMaxRange(zVALUE _low, zVALUE _high)
{
	if (_high-_low<=0.0)
	{
		zERR_WARNING("B: SB: Wrong maximum range for statusbar");
	};

	zCViewStatusBar::SetMaxRange(_low,_high);

	SetRange(low,high);	
};

void oCViewStatusBar::SetRange(zVALUE _low, zVALUE _high)
{
	zCViewStatusBar::SetRange(_low,_high);	
		
	int maxSize	= 0;
	if (_high-_low>0)
	{
		float mult	= (maxHigh-minLow>0) ? float(high-low)/float(maxHigh-minLow) : 0;
		maxSize		= int( (8192 - (2.0*bar_frame_x) ) * mult);
	}

	range_bar->SetPos(bar_frame_x,bar_frame_y);	
	range_bar->SetSize(maxSize,int( 8192 - (2.0*bar_frame_y) ) );	

	SetPreview(previewValue);
	SetValue(currentValue);
};


void oCViewStatusBar::SetPreview(zVALUE _value)
{
	zCViewStatusBar::SetPreview(_value);
	
	int valSize = 0;
	if (high - low > 0.0)
	{
		float mult = float(previewValue) / float(high - low);
		valSize = int(8192 * mult);
	}

	//preview_bar->SetPos(0, 0);
	//preview_bar->SetSize(valSize, 8192);
};


void oCViewStatusBar::SetValue(zVALUE _value)
{
	zCViewStatusBar::SetValue(_value);
	
	int valSize=0;
	if (high-low>0.0)
	{
		float mult = float(currentValue)/float(high-low);
		valSize = int( 8192*mult ); // logische Breite fuer den Value-Balken
	}

	value_bar->SetPos(0,0);
	value_bar->SetSize(valSize,8192);
};

