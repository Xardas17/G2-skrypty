/******************************************************************************** 
 
     $Workfile:: zview.cpp            $                $Date:: 11.02.01 19:17   $
     $Revision:: 100                  $             $Modtime:: 11.02.01 19:07   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zview.cpp $
 * 
 * 100   11.02.01 19:17 Speckels
 * 
 * 99    11.02.01 13:35 Speckels
 * 
 * 98    10.02.01 23:19 Speckels
 * 
 * 97    5.02.01 22:25 Wohlers
 * 
 * 96    5.02.01 20:19 Wohlers
 * 
 * 95    1.02.01 14:48 Speckels
 * 
 * 94    1.02.01 13:12 Speckels
 * 
 * 93    26.01.01 15:57 Speckels
 * 
 * 92    18.01.01 0:39 Speckels
 * 
 * 91    17.01.01 18:25 Hildebrandt
 * 
 * 90    16.01.01 22:53 Speckels
 * 
 * 89    11.01.01 21:09 Hildebrandt
 * 
 * 88    11.01.01 20:41 Speckels
 * 
 * 87    11.01.01 18:39 Speckels
 * 
 * 86    20.12.00 17:54 Speckels
 * 
 * 85    18.12.00 17:38 Speckels
 * 
 * 84    7.12.00 20:27 Speckels
 * 
 * 83    6.12.00 12:11 Speckels
 * 
 * 82    1.12.00 16:58 Speckels
 * 
 * 81    1.12.00 3:08 Speckels
 * 
 * 80    29.11.00 22:57 Wohlers
 * 
 * 79    29.11.00 12:53 Speckels
 * 
 * 78    23.11.00 16:21 Wohlers
 * 
 * 77    16.11.00 13:57 Speckels
 * 
 * 76    16/11/00 10:30 Luesebrink
 * 
 * 75    15/11/00 15:25 Luesebrink
 * 
 * 74    9.11.00 18:19 Wohlers
 * 
 * 73    8.11.00 21:51 Hildebrandt
 * 
 * 72    2.11.00 16:14 Speckels
 * 
 * 71    2.11.00 16:03 Hildebrandt
 * 
 * 70    19.10.00 20:06 Speckels
 * 
 * 69    19.10.00 20:02 Speckels
 * 
 * 68    19.10.00 17:15 Keskenti
 * 
 * 67    11.10.00 16:56 Keskenti
 * 
 * 66    4.10.00 19:59 Speckels
 * 
 * 65    4.10.00 15:16 Speckels
 * 
 *********************************************************************************/

/*****************************************************************
- Kommentare:
	- Vor dem Zugriff auf ein Desktop-Item dieses ab sofort immer 
	  erst in den Vater einfпїЅgen : z.B. screen->Insert(View). 
	  Erst danach Grafikzugriffe auf "View" durchfпїЅhren.
	  Damit sieht eibe korrekte Definition eine DItems z.B. wie 
	  folgt aus :
			zCView *View(0,0,4096,4096);
			screen->Insert(View);
				screen->Setflags(VIEW_MOVEABLE);		
			View->InsertBack(GFX_BLUE);
			View->Line(0,0,8191,8191,GFX_RED);
			// Eventhandler einfuegen
			View->InsertHandleEvent(IA_ViewEvents);
			
	  Ein EventHandler sollte folgenden Aufbau haben

			zBOOL IA_ViewEvents(int key)
			{
				switch (key) {
				case KEY_A		: View->Printwin("Taste A gedrueckt !");
								  break;
				case KEYSC_MLEFT: View->Printwin("Linke Maustaste gedrueckt !");
								  break;
				default			: return FALSE;
				}
				return TRUE;
			}
	  
	  Wurde die aktuelle Taste vom Eventhandler abgearbeitet, muпїЅ TRUE 
	  zurпїЅckgeliefert werden (da sonst die Taste an evt. weitere Handler 
	  "durchgereicht" wird), ansonsten FALSE.
	
	- Auf vielfachen Wunsch sind alle Print-Befehle jetzt 
	  "printf"-kompatibel.
	  Bislang unterstпїЅtzt :	"%d" -> integer
							"%s" -> char *
							"%S" -> zSTRING *

****************************************************************/

#include "zCore.h"
#include "z3d.h"
#include "zGrafix.h"
#include "zViewBase.h"
#include "zView.h"
#include "zDisk.h"
#include "zOption.h"
#include "zFonts.h"
#include "zRenderer.h"
#include "zTexture.h"
#include "zInput_Win32.h"
#include "zVideo_Win32.h"
#include "zWin32.h"

#pragma warning ( disable:4244 )
#pragma warning ( disable:4706 )

const zSTRING VIEW_FONT_DEFAULT = "font_default.tga";

// **********************************************************************
// zCInputCallback
// **********************************************************************

// statics
zCList <zCInputCallback> zCInputCallback :: inputList;

zCInputCallback :: zCInputCallback ()
{
}

zCInputCallback :: ~zCInputCallback ()
{
	if (inputList.IsInList(this)) inputList.Remove(this);
}

void zCInputCallback :: SetHandleEventTop()
{
	inputList.Remove(this);
	inputList.Insert(this);
}

void zCInputCallback :: SetEnableHandleEvent(zBOOL f)
{ 
	if (f && !inputList.IsInList(this)) inputList.Insert(this);
	else if (!f)						inputList.Remove(this);
};

zBOOL zCInputCallback :: GetEnableHandleEvent()
{
	return inputList.IsInList(this);
}

zBOOL zCInputCallback :: DoEvents(int key)
{
	// Liste durchlaufen....
	zCList <zCInputCallback>* node = inputList.GetNextInList();
	zCInputCallback* ic;

	node = inputList.GetNextInList();
	while (node) {
		ic		= node -> GetData();
		node	= node -> GetNextInList();
		if (ic->HandleEvent(key)) return TRUE;
	}
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
//	zCInputCallback::GetInput
//
//	2002-05-11	[BENDLIN]
//
//				Special mouse handling removed (now handled in zInput)
//
////////////////////////////////////////////////////////////////////////////////

void zCInputCallback :: GetInput()
{
	int k = zinput->GetKey();
	if (k!=0) {
		DoEvents(k);
	}
	
	zinput->ProcessInputEvents();
}

/*
zWORD zCInput_Win32::GetKey()
{
	const	zREAL	KEY_REPEAT_TIME		= 200.0f;			// 500ms
	static	zREAL	keyRepeatCounter	= KEY_REPEAT_TIME;
	static	int		lastKey				= 0;

	if(!lpDIKeyboard)return 0;
	if( focusWinHandle != GetFocus() )return 0;

	int keyNr = 0;
	lpDIKeyboard->Poll();
	DIDEVICEOBJECTDATA key_pressed;
	memset(&key_pressed,0,sizeof(DIDEVICEOBJECTDATA));
	DWORD dwItems = 1;
	HRESULT res = lpDIKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &key_pressed, &dwItems, DIGDD_PEEK );
	if( res == DI_OK &&	dwItems > 0 && ((key_pressed.dwData & 0x80) ? 1 : 0) ) {
		keyNr = key_pressed.dwOfs; 
	}

	// [Ulf] : Simulate Auto-Repeat....
	if ((keyNr==0) && (lastKey!=0) && KeyPressed(lastKey)) {
		// Key - Repeat - Delay - Time
		keyRepeatCounter -= ztimer.GetFrameTimeF();
		if (keyRepeatCounter<=0) {
			keyRepeatCounter+=KEY_REPEAT_TIME;
			return lastKey;
		}
	} else {
		lastKey = keyNr;
		keyRepeatCounter = KEY_REPEAT_TIME;
	}
	return keyNr;
};
*/

// **********************************************************************
// zCView
// **********************************************************************


// [Moos] : statische AufrпїЅumfunktion fпїЅr obige Pointer
//          Kein toller Stil und abhпїЅngig vom Compiler, aber auch unkritisch.
extern zCView * screen;

class zCPlayerCleanup{
public:
    ~zCPlayerCleanup(){
        delete screen;
        screen = NULL;
/*        delete zCView::stdoutput;
        zCView::stdoutput = NULL;
        delete zCView::modal;
        zCView::modal = NULL; */
    }    
};

static zCPlayerCleanup clean;

// [Moos] Ende


zCView*	screen						= NULL;
zCView*	zCView :: stdoutput			= NULL;
zCView*	zCView :: modal				= NULL;
zBOOL	zCView :: showDebug			= FALSE;
zREAL	zCView :: s_fViewTimePerChar= 100.0f;



// **********************************************************************
// Klassen Methoden
// **********************************************************************

zCView :: zCView()
{
	Init();
};

zCView :: zCView(int x1,int y1,int x2,int y2,zTviewID id)
{
	Init();
	Init(x1,y1,x2,y2,id);
}

zCView :: ~zCView()
// Destructor 1
{
	// Fixme : Alle Childs lпїЅschen ?
	if (owner) owner->RemoveItem(this);

	font	= NULL;
	owner	= NULL;
	next	= NULL;

	zRELEASE(backTex);
	// delete Text
	textLines.DeleteListDatas();
}

/*--------------------------------------------------------------------------

    zCView::Init()

 

    ??-???-00       [Roman Keskenti]

                      Added initialization for open/close fx


--------------------------------------------------------------------------*/ 
void zCView :: Init()
{	
	viewID			= VIEW_ITEM;
	flags			= 0;
	intflags		= 0;
	ondesk			= FALSE;
	alpha			= 255;
	alphafunc		= zRND_ALPHA_FUNC_NONE;
	owner			= NULL;
	
	vposx			= 0;
	vposy			= 0;
	vsizex			= 0;
	vsizey			= 0;
	pposx			= 0;
	pposy			= 0;
	psizex			= 0;
	psizey			= 0;
	
	font			= NULL;
	px1				= 0;
	py1				= 0;
	px2				= 0;
	py2				= 0;
	winx			= 0;
	winy			= 0;
	scrollMaxTime	= 0.0f;
	scrollTimer		= 0.0f;	

	next			= NULL;
	backTex			= NULL;
	color			= GFX_WHITE;
	fontColor		= GFX_WHITE;

	//
	//	CODECHANGE [ROMAN]
	//
	fxOpen			 = zTViewFX :: VIEW_FX_ZOOM	;
	fxClose			 = zTViewFX :: VIEW_FX_ZOOM	;
	isOpen			 = TRUE						;
	isClosed		 = FALSE					;
	continueOpen	 = FALSE					;
	continueClose	 = FALSE					;
	removeOnClose	 = FALSE					;
	resizeOnOpen	 = FALSE					;
	maxTextLength	 = 0						;
	textMaxLength	 = ""						;
	timeOpen		 = 0.0f						;
	timeClose		 = 0.0f						;
	timeDialog		 = 0.0f						;
	speedOpen		 = 0.003f					;
	speedClose		 = 0.003f					;
	m_bFillZ		 = FALSE;
	//
	//	CODECHANGE [ROMAN] END
	//
}

/*--------------------------------------------------------------------------

    zCView::Init()

 

    06-Oct-00       [Roman Keskenti]

						Removed Init() call for oCDoc relied on this
						method not modifying any members.

						Stefan: Call Init() externally

--------------------------------------------------------------------------*/ 
void zCView :: Init(int x1,int y1,int x2,int y2,zTviewID id)
{
	//
	// CODECHANGE [ROMAN]
	//

	// CODECHANGE [STEFAN]
	// Init();
	// CODECHANGE [STEFAN] END

	//
	// CODECHANGE [ROMAN] END
	//

	viewID		= id;
	px1			= 0; 
	py1			= 0; 
	px2			= VIEW_VXMAX-1; 
	py2			= VIEW_VYMAX-1;

	if (id==VIEW_SCREEN) {
		vposx	= 0;
		vposy	= 0;
		vsizex	= x2-x1+1;
		vsizey	= y2-y1+1;
		pposx	= 0;
		pposy	= 0;
		psizex	= zrenderer->vid_xdim;
		psizey	= zrenderer->vid_ydim;
	} else {
		zCView* ownerBackup = GetOwner();
		if (!ownerBackup) SetOwner	(screen);
		SetPos		(x1,y1);
		SetSize		(x2-x1+1,y2-y1+1);
		if (!ownerBackup) SetOwner	(NULL);
	}

	// Font Init
	if (zfontman)	font = zfontman->GetFont(0);
	else			font = NULL;

	Setflags		(VIEW_TXT_CENTER);
}

void zCView :: Init(int x,int y,const zSTRING& s,zTviewID id)
{
	// CODECHANGE [STEFAN]
	/*
	Init	();
	viewID	= id;
	flags	= VIEW_TXT_AUTO;
	SetPos		(x,y);
	CreateText	(x,y,s);
	*/

	Init	();
	viewID	= id;
	flags	= VIEW_TXT_AUTO;

	if (id==VIEW_SCREEN) {
		vposx	= 0;
		vposy	= 0;
		pposx	= 0;
		pposy	= 0;
	} else {		
		zCView* ownerBackup = GetOwner();
		if (!ownerBackup) SetOwner	(screen);
		SetPos		(x,y);
		if (!ownerBackup) SetOwner	(NULL);		
	}

	CreateText	(x,y,s);

	// CODECHANGE [STEFAN] END
}

// **********************************************************************
//						  Koordinates
// **********************************************************************

int rnd2(float x)
{
	if (x>0) return (int) (x+0.5);
        else return (int) (x-0.5);
}

int zCView :: nax(int x) 
{ return rnd2 ((float) (x * psizex) / VIEW_VXMAX); }

int zCView :: nay(int y)
{ return rnd2 ((float) (y * psizey) / VIEW_VYMAX ); }

int zCView :: anx(int x)
{ return rnd2 ((float) (x * VIEW_VXMAX) / psizex ); }

int zCView :: any(int y)
{ return rnd2 ((float) (y * VIEW_VXMAX) / psizey ); }

// **********************************************************************
// Desktop-Item Member Methods
// **********************************************************************

void zCView :: StdPrintwin (const zSTRING &s)
{
	if (stdoutput) stdoutput->Printwin(s);
}

void zCView :: SetAutoScroll(zREAL time)
// Automatisches Scrolling, nachdem laengere Zeit kein Update mehr erfolgt ist.
// Soll und wenn ja, nach wieveil Zeit eine Zeile nach oben gescrollt werden ?
// time in ms;
{
	if (time<=0) {
		flags &=		(~VIEW_AUTOSCROLL);
	} else {
		flags			|= VIEW_AUTOSCROLL;
		scrollMaxTime	 = time;
		scrollTimer	 = 0;
	}
}

void zCView :: CheckAutoScroll()
{
	if (flags & VIEW_AUTOSCROLL) {
		scrollTimer += ztimer.GetFrameTime()/ztimer.GetMotionFactor();
		if (scrollTimer >= scrollMaxTime) {
			Printwin("\n");
			scrollTimer -= scrollMaxTime;
		}
	}
}

void zCView :: SetTransparency (int a)
{
	alpha		= a;
}

void zCView :: SetAlphaBlendFunc ( const zTRnd_AlphaBlendFunc &mode )
{
	alphafunc	= mode;
}

void zCView :: SetColor (const zCOLOR& _color)
{
	color		= _color;
}

zCOLOR zCView :: GetColor ()
{
	return color;
}

void zCView :: Setflags (int f)
// Set flags of item
{
	flags |= f;
}

void zCView :: ClrFlags (int f)
{
	flags &= ~f;
}

zBOOL zCView :: HasFlag(int flagNr)
{
	return ((flags & flagNr)>0);
}

void zCView :: InsertBack(zCTexture* tex)
{
	zRELEASE(backTex);
	backTex = tex;
	if (backTex) backTex->AddRef();
};

void zCView :: InsertBack(const zSTRING &s)
// Insert a GFX-Background
{
	zCTexture* tex = zCTexture::Load((zSTRING)s,zTEX_LOAD_FLAG_TILE);

	InsertBack(tex);

	zRELEASE(tex);	
}

void zCView::InitPrintwin()
{
	textLines.DeleteListDatas();
	intflags |= VIEW_I_TEXT;
}

/*--------------------------------------------------------------------------

    zCView::BlitText()

 

    ??-???-00       [Roman Keskenti]

                      Added timed text support
					  Added colored text support
					  Keeps text from being blitted until window has opend up


--------------------------------------------------------------------------*/ 
void zCView :: BlitText()
// Show Text on screen
{
	CheckAutoScroll();

	//
	//	CODECHANGE [ROMAN]
	//
	CheckTimedText ();			// remove "decayed" text lines
	if ( ! isOpen ) return;		// do not blit text until window has finished opening process
	//
	//	CODECHANGE [ROMAN] END
	//

	int x,y;
	zCList <zCViewText>*	textNode	= textLines.GetNextInList();
	zCViewText*				text		= NULL;
	while (textNode) {
		
		text		= textNode -> GetData();
		textNode	= textNode -> GetNextInList();

		x			= pposx + nax(text->posx);
		y			= pposy + nay(text->posy);
		
		SetFont		(text->font);

		//
		//	CODECHANGE [ROMAN]
		//
		if ( text->colored )
		{
			SetFontColor( text->color );
		}
		//
		//	CODECHANGE [ROMAN] END
		//

		PrintChars	(x,y,text->text);		
	}
};

/*--------------------------------------------------------------------------

    zCView::Blit()

 

    ??-???-00       [Roman Keskenti]

                      Added open / close fx

--------------------------------------------------------------------------*/ 

void zCView :: Blit()
{
	if (this==screen)				return;
	if (GetViewID()==VIEW_VIEWPORT) return;

	// z-Buffer 
	zBOOL				oldzWrite		= zrenderer->GetZBufferWriteEnabled();
	if (!m_bFillZ) zrenderer->SetZBufferWriteEnabled	(FALSE);
	else		   zrenderer->SetZBufferWriteEnabled	(TRUE);
	zTRnd_ZBufferCmp	oldCmp			= zrenderer->GetZBufferCompare();
	zrenderer->SetZBufferCompare		(zRND_ZBUFFER_CMP_ALWAYS);
	zTRnd_AlphaBlendFunc oldBlendFunc;
	zREAL dimx, dimy;

	// Set Viewport
	zVEC2 pos1,pos2;
	GetPixelExtends(pos1[0],pos1[1],pos2[0],pos2[1]);

	//
	//	CODECHANGE [ROMAN]
	//
	ApplyOpenClose( pos1, pos2 );		// modifiy background textures coords according to open/close fx 
	//
	//	CODECHANGE [ROMAN] END
	//

	// pos1/pos2 duerfen nicht geaendert werden, weil sonst TextureCoords falsch berechnet werden
	zREAL startx = pos1[VX];
	zREAL starty = pos1[VY];
	zREAL endx	 = pos2[VX];
	zREAL endy	 = pos2[VY];
	
	// Ecke Links oben
	if (pos1[VX] < 0)						startx = 0;
	if (pos1[VX] > zrenderer->vid_xdim-1)	return;
	if (pos1[VY] < 0)						starty = 0;
	if (pos1[VY] > zrenderer->vid_ydim-1)	return;
	// Ecke rechst unten
	if (pos2[VX] < 0)						return;
	if (pos2[VX] > zrenderer->vid_xdim-1)	endx = zrenderer->vid_xdim-1;
	if (pos2[VY] < 0)						return;
	if (pos2[VY] > zrenderer->vid_ydim-1)	endy = zrenderer->vid_ydim-1;

	dimx = endx - startx;
	dimy = endy - starty;
	
	if ((dimx<=0) || (dimy<=0)) return;
	zrenderer->SetViewport(startx,starty,dimx,dimy);

	oldBlendFunc = zrenderer->GetAlphaBlendFunc();
	zrenderer -> SetAlphaBlendFunc (alphafunc);
	color.SetAlphaByte (alpha);

	// Screen - Coords
	if (backTex) {
	
		// Texture Coords
		zVEC2 texuv1(0.0f,0.0f);
		zVEC2 texuv2(1.0f,1.0f);

		zBOOL filter = zrenderer->GetBilerpFilterEnabled();
		zrenderer -> SetBilerpFilterEnabled	(TRUE);
		zREAL farZ;
		if (m_bFillZ)
		{
			if (zCCamera::activeCam) farZ = zCCamera::activeCam->GetFarClipZ()-1;
			else					 farZ = 65534;
		}
		else 
		{
			if (zCCamera::activeCam) farZ = zCCamera::activeCam->GetNearClipZ()+1;
			else					 farZ = 1;
		}
		zrenderer -> DrawTile				(backTex,pos1,pos2,farZ,texuv1,texuv2,color);

		zrenderer -> SetBilerpFilterEnabled	(filter);

			
	}

	// Safety... Anscheinend kann hier die AlphaFunc auf zRND_ALPHA_FUNC_MAT_DEFAULT sein/werden...?
	zrenderer -> SetAlphaBlendFunc (alphafunc);
	BlitText();

	// Alte Modis wiederherstellen.
	zrenderer->SetAlphaBlendFunc		(oldBlendFunc);
	zrenderer->SetZBufferWriteEnabled	(oldzWrite);
	zrenderer->SetZBufferCompare		(oldCmp);
}

void zCView :: DrawItems()
{
	Blit();

	zCView* child = childs.wurzel;
	while (child) 
	{
		child -> DrawItems();
		child  = child -> next;
	}

	zrenderer->SetViewport(0,0,zrenderer->vid_xdim,zrenderer->vid_ydim);
}

void zCView :: Top(void)
{
	if ((owner!=NULL) && ((flags & VIEW_GROUNDED)==0) && (viewID!=VIEW_VIEWPORT)) {

		zCView* myOwner = owner;
		myOwner->RemoveItem(this);
		myOwner->InsertItem(this);		
		myOwner->Top();	// ???
	}
}

//
//	CODECHANGE [ROMAN]
//

// *****************************
// OPEN/CLOSE FX
// *****************************

void zCView :: Create( const zSTRING&	strTexture		, 
							 zTViewFX	enuOpen			,
							 zTViewFX	enuClose		,
							 zREAL		fScrollTime		,
							 zBOOL		bResizeOnOpen	)
{
	SetOpenFX		( enuOpen		);
	SetCloseFX		( enuClose		);
	SetResizeOnOpen	( bResizeOnOpen	);

	if ( strTexture  != ""	  )	InsertBack		( strTexture  );
	if ( fScrollTime != -2.0f ) SetAutoScroll	( fScrollTime );

	Close			();

	this->SetAlphaBlendFunc( zRND_ALPHA_FUNC_BLEND );
}

void zCView :: ForceOpen()
{
	if ( continueClose ) 
	{
		zERR_WARNING( "U: VIE: Window was still closing while trying to open ..." );
	}

	//
	//	OPEN
	//
	this->textMaxLength = "";																// reset size for width-calculation
	this->maxTextLength = 0;																// ... whenever someone even tries to open this view up

//	if ( timeOpen  > 0.0f ) return;															// leave if already opening or open
//	if ( timeClose > 0.0f ) return;															// leave if already closing or closed 
																							
	timeOpen		= 0.0f;																	// not yet opening
	timeClose		= 0.0f;																	// not yet closing
																							
	isOpen			= FALSE;																// the window is not yet open	
	isClosed		= FALSE;																// the window is not yet closed
	continueOpen	= TRUE ;																// continue opening until timeOpen reaches 1.0
	continueClose	= FALSE;																// meanwhile, do not try to close 
																							
	DefPrintwin( 50, 50, VIEW_VXMAX-50, VIEW_VYMAX-50 );									// define margins for text-output
	::screen->InsertItem( this );															// register with screen
}

void zCView :: Open()
{																					
	this->textMaxLength = "";																// reset size for width-calculation
	this->maxTextLength = 0;																// ... whenever someone even tries to open this view up

	if ( timeOpen  > 0.0f ) return;															// leave if already opening or open
	if ( timeClose > 0.0f ) return;															// leave if already closing or closed 
																							
	timeOpen		= 0.0f;																	// not yet opening
	timeClose		= 0.0f;																	// not yet closing
																							
	isOpen			= FALSE;																// the window is not yet open	
	isClosed		= FALSE;																// the window is not yet closed
	continueOpen	= TRUE ;																// continue opening until timeOpen reaches 1.0
	continueClose	= FALSE;																// meanwhile, do not try to close 
																							
	DefPrintwin( 50, 50, VIEW_VXMAX-50, VIEW_VYMAX-50 );									// define margins for text-output
	::screen->InsertItem( this );															// register with screen
}																							
																							
void zCView :: Close()																		
{			
	this->textMaxLength = "";																// reset size for width-calculation
	this->maxTextLength = 0;																// ... no matter whether the close wil actually happen

	if ( timeClose > 0.0f ) return;															// already closing or closed 
	if ( continueOpen )																		// already opening or open
	{
		timeClose = 1.0f - timeOpen;
		timeOpen  = 0.0f;																	// not yet opening
	}															
	else																					
	{
		timeOpen  = 0.0f;																	// not yet opening
		timeClose = 0.0f;																	// not yet closing
	}
																							
	isOpen			= FALSE;																// the window is not yet open	
	isClosed		= FALSE;																// the window is not yet closed
	continueOpen	= FALSE;																// meanwhile, do not try to open
	continueClose	= TRUE ;																// continue closing until timeClose reaches 1.0
}																							
																							
void zCView :: ApplyOpenClose( zVEC2& pos1, zVEC2& pos2	)									
{																							
	if ( timeDialog > 0.0f )																// is the view in dialog mode (e.g. auto-closing) ?
	{																						
		timeDialog -= ztimer.GetFrameTime()/ztimer.GetMotionFactor();						// subtract frame time from remaining dialog time
		if ( timeDialog <= 0.0f )															// time reached ?
		{																					
			timeDialog = 0.0f;																// do not check the time anymore
			Close();																		// launch close-fx
		}																					
	}																						
																							
	if ( (! continueOpen) && (! continueClose) ) return;									// leave if the view is not currently opening/closing
																							
	posCurrent[0] = pos1;																	// store opened view's top/left		-coordinates  
	posCurrent[1] = pos2;																	// store opened view's bottom/right	-coordinates  
																							
	if		( continueOpen  )	UpdateOpen ();												// modify coordinates depending on opening-fx
	else if ( continueClose )	UpdateClose();												// modify coordinates depending on closing-fx
																							
	pos1 = posOpenClose[0];																	// write back top/left		-coordinates
	pos2 = posOpenClose[1];																	// write back bottom/right	-coordinates
}																							
																							
void zCView :: UpdateOpen()																	
{																							
	if ( timeOpen >= 1.0f )																	// has the view finished opening up?
	{																						
		timeOpen	 = 0.0f;																// reset opening timer
		continueOpen = FALSE;																// do not continue opening 
		isOpen		 = TRUE;																// view is open
		isClosed	 = FALSE;																// view is not closed
		return;																				// nothing left to do -> leave
	}																						
																							
	switch ( fxOpen )																		// jump to appropriate open-fx coords-calculation-routine
	{
		default:
		case zTViewFX :: VIEW_FX_NONE	: timeOpen = 2.0f;		break;
		case zTViewFX :: VIEW_FX_ZOOM	: UpdateOpenZoom();		break;
	}
}

void zCView :: UpdateClose()
{
	if ( timeClose >= 1.0f )																// has the view finished opening up?
	{																						
		timeClose	  = 0.0f ;																// reset opening timer
		continueClose = FALSE;																// do not continue opening 
		isOpen		  = FALSE;																// view is open
		isClosed	  = TRUE ;																// view is not closed
		/*if ( removeOnClose )*/															
		::screen->RemoveItem( this );														// de-register this view with the screen
		return;																				// nothing left to do -> leave
	}																						
																							
	switch ( fxClose )																		// jump to appropriate close-fx coords-calculation-routine
	{																						
		default:																			
		case zTViewFX :: VIEW_FX_NONE	: timeClose = 2.0f;		break;						
		case zTViewFX :: VIEW_FX_ZOOM	: UpdateCloseZoom();	break;						
	}																						
}																							
																							
void zCView :: UpdateOpenZoom()																
{																							
	zVEC2	posCenter,																		// opened view's center
			posDistance;																	// distances (x/y) from center to border
																							
	posCenter		[0]	= ( posCurrent[1][0] + posCurrent [0][0] ) * 0.5f;					//	x-center	= ( x-end + x-start ) / 2
	posCenter		[1]	= ( posCurrent[1][1] + posCurrent [0][1] ) * 0.5f;					//	y-center	= ( y-end + y-start ) / 2
	posDistance		[0]	= ( posCenter	 [0] - posCurrent [0][0] );							//	x-distance	=  x-center - x-start
	posDistance		[1]	= ( posCenter	 [1] - posCurrent [0][1] );							//	y-distance	=  y-center - y-start
	posOpenClose [0][0]	=	posCenter	 [0] - posDistance	 [0] * timeOpen;				//	x-start		= x-center - factor * x-distance
	posOpenClose [0][1]	=	posCenter	 [1] - posDistance	 [1] * timeOpen;				//	y-start		= y-center - factor * y-distance
	posOpenClose [1][0]	=	posCenter	 [0] + posDistance	 [0] * timeOpen;				//	x-end		= x-center + factor * x-distance
	posOpenClose [1][1]	=	posCenter	 [1] + posDistance	 [1] * timeOpen;				//	y-end		= y-center + factor * y-distance

	zREAL timeElapsed = (ztimer.GetFrameTime()/ztimer.GetMotionFactor()) * speedOpen;
	if	( ((timeOpen < 1.0) && (timeOpen + timeElapsed > 1.0f)) || timeOpen == 1.0f )	timeOpen  = 1.0f;
	else																				timeOpen += timeElapsed;
}

void zCView :: UpdateCloseZoom()
{
	zVEC2	posCenter,																		// opened view's center
			posDistance;																	// distances (x/y) from center to border
																							
	posCenter		[0]	= ( posCurrent[1][0] + posCurrent [0][0] ) * 0.5f;					//	x-center	= ( x-end + x-start ) / 2
	posCenter		[1]	= ( posCurrent[1][1] + posCurrent [0][1] ) * 0.5f;					//	y-center	= ( y-end + y-start ) / 2
	posDistance		[0]	= ( posCenter	 [0] - posCurrent [0][0] );							//	x-distance	=  x-center - x-start
	posDistance		[1]	= ( posCenter	 [1] - posCurrent [0][1] );							//	y-distance	=  y-center - y-start
	posOpenClose [0][0]	=	posCenter	 [0] - posDistance	 [0] * ( 1.0f - timeClose );	//	x-start		= x-center - factor * x-distance
	posOpenClose [0][1]	=	posCenter	 [1] - posDistance	 [1] * ( 1.0f - timeClose );	//	y-start		= y-center - factor * y-distance
	posOpenClose [1][0]	=	posCenter	 [0] + posDistance	 [0] * ( 1.0f - timeClose );	//	x-end		= x-center + factor * x-distance
	posOpenClose [1][1]	=	posCenter	 [1] + posDistance	 [1] * ( 1.0f - timeClose );	//	y-end		= y-center + factor * y-distance

	zREAL timeElapsed = (ztimer.GetFrameTime()/ztimer.GetMotionFactor()) * speedClose;
	if	( ((timeClose < 1.0) && (timeClose + timeElapsed > 1.0f)) || timeClose == 1.0f )	timeClose  = 1.0f;
	else																					timeClose += timeElapsed;
}

//
//	CODECHANGE [ROMAN] END
//

// *****************************
// NEW
// *****************************

void zCView::RecalcChildsSize()
{
	zCView* child = childs.wurzel;
	while (child) 
	{
		child->SetSize(child->vsizex,child->vsizey);
		child->RecalcChildsSize();		
		child = child -> next;
	}
};

void zCView :: RecalcChildsPos()
{
	// Und die Childs mitbewegen
	// nue neue Berechnung der PixelPositionen nпїЅtig
	zCView* child = childs.wurzel;
	while (child) 
	{
		child -> pposx = 0;
		child -> pposy = 0;
		child -> CalcPixelPos		(child->pposx,child->pposy);
		child -> RecalcChildsPos	();
		child = child -> next;
	}
}

void zCView :: SetPos (int vx, int vy)
{
	vposx = vx;
	vposy = vy;
	pposx = 0;
	pposy = 0;
	CalcPixelPos	(pposx,pposy);
	RecalcChildsPos	();
}

void zCView :: GetPos (int &vx, int &vy)
{
	vx = vposx;
	vy = vposy;
}

void zCView :: CalcPixelPos(int& ppx, int &ppy)
{
	if (!owner) return;
	ppx += owner->nax(vposx);
	ppy += owner->nay(vposy);
	owner->CalcPixelPos(ppx,ppy);
};

void zCView :: GetPixelPos(int& ppx, int &ppy)
{
	ppx = pposx;
	ppy = pposy;
};

void zCView :: Move(int vx, int vy)
{
	SetPos(vposx+vx,vposy+vy);
};

void zCView :: SetSize(int vx, int vy)
{
	vsizex = vx; if (vsizex<=0) vsizex = 1;
	vsizey = vy; if (vsizey<=0) vsizey = 1;
	psizex = 0;
	psizey = 0;
	GetPixelSize(psizex,psizey);
	if (psizex<=0) psizex = 1;
	if (psizey<=0) psizey = 1;
};

void zCView :: GetSize(int &vx, int &vy)
{
	vx = vsizex; 
	vy = vsizey;
}

void zCView :: GetPixelSize(int &px, int &py)
{
	if (!owner) return;
	px = owner->nax(vsizex);
	py = owner->nay(vsizey);
};

void zCView :: GetExtends(int &vx1, int &vy1, int &vx2, int &vy2)
// Ausdehnung virtuelle Koordinaten
{
	vx1 = vposx;
	vy1 = vposy;
	vx2 = vposx + vsizex - 1;
	vy2 = vposy + vsizey - 1;
}

void zCView :: GetScreenExtends(int &vx1, int &vy1, int &vx2, int &vy2)
// Ausdehnung virtuelle Koordinaten in Bezug auf den "screen"
{
	if (!screen) return;
	vx1 = screen->anx(pposx);
	vy1 = screen->any(pposy);
	vx2 = vx1 + screen->anx(psizex-1);
	vy2 = vy1 + screen->any(psizey-1);
};

void zCView :: GetPixelExtends(float &vx1, float &vy1, float &vx2, float &vy2)
{
	vx1 = (float)pposx;
	vy1 = (float)pposy;
	vx2 = (float)(pposx + psizex - 1);
	vy2 = (float)(pposy + psizey - 1);
}

zBOOL zCView :: IsIn(int vx,int vy)
// check if these virtual screen-Koords are in Objekt
{
	int x1,y1,x2,y2;

	GetScreenExtends(x1,y1,x2,y2);
	return ((vx>=x1) && (vy>=y1) && (vx<=x2) && (vy<=y2));
}

zCView *zCView :: GetItem(int vx,int vy)
// Liefert Item an Pos x/y zurпїЅck
{
	int x1,y1,x2,y2;

	// Zuerst die Childs 
	zCView*	found	= NULL;
	zCView* child	= childs.wurzel;
	while (child) {
		found	= child -> GetItem(vx,vy);
		child	= child -> next;
		if (found)	return found;
	}

	// this checken
	GetScreenExtends(x1,y1,x2,y2);
	if ((vx>=x1) && (vx<=x2) && (vy>=y1) && (vy<=y2)) return this;
	
	return NULL;
}

// **********************************************************************
//								Print
// **********************************************************************

//
//	CODECHANGE [ROMAN]
//

/*--------------------------------------------------------------------------

    zCView::BlitText()

 

    ??-???-00       [Roman Keskenti]

						Overloaded to reflect the change to zCViewText (see header file)

--------------------------------------------------------------------------*/ 
zCViewText* zCView :: CreateText(int x,int y,const zSTRING &s, zREAL t, zCOLOR &c, zBOOL timed, zBOOL colored )
{
	zCList<zCViewText>* textNode = textLines.GetNextInList();
	zCViewText* textData = NULL;
	while (textNode) {
		textData = textNode->GetData();
		textNode = textNode->GetNextInList();
		if ((textData->posx == x) && (textData->posy == y)) {
			textData->Create( x, y, s, t, c, timed, colored );
			textData->font = GetFont();
			return textData;
		}
	}

	if ( s.Length() > maxTextLength ) 
	{
		maxTextLength = s.Length();
		textMaxLength = s;																	// store text width maximum length for resize
	}

	zCViewText* text	= zNEW( zCViewText( x, y, s, t, c, timed, colored ) );
	text->font			= GetFont();
	textLines.Insert(text);

	return text;
}

// *****************************
// TIMED TEXT
// *****************************
void zCView :: CheckTimedText()
{
	zCList <zCViewText>*	textNode	= textLines.GetNextInList();						// get root node for text lines
	zCViewText*				text		= NULL;												// invalidate text pointer

	while ( textNode )																		// for each text-line
	{
		text		= textNode -> GetData();												// get the actual text			(if any)
		textNode	= textNode -> GetNextInList();											// get the next text line node	(if any)

		if ( text )																			// text valid ?
		{																					
			if ( text->timed )																// timed text ?
			{																				
				text->timer -= ztimer.GetFrameTime()/ztimer.GetMotionFactor();				// advance by frame time
																							
				if ( text->timer <= 0.0f )													// time limit reached ? 
				{
					textLines.Remove( text );												// remove the text line
					delete text;
				}
			}
		}
	}
}

//
//	fTime Values :	>=  0.0f	close after specified time
//					== -1.0f	close after char-count * VIEW_CHAR_TIME
//					== -2.0f	will be closed manually
//

//
//	PrintTimed() handles only ONE line of text !!!
//

void zCView :: PrintTimed( int nPosX, int nPosY, const zSTRING& strMessage, zREAL fTime, zCOLOR* col )
{
	if ( fTime == -1.0f )	fTime = s_fViewTimePerChar * strMessage.Length();
	CreateText( nPosX, nPosY, strMessage, fTime, col ? *col : zCOLOR( 0, 0, 0, 0 ), fTime == -2.0f ? FALSE : TRUE, (col) ? TRUE : FALSE );
}

void zCView :: PrintTimedCX( int nPosY, const zSTRING& strMessage, zREAL fTime, zCOLOR* col )
{
	int x = (VIEW_VXMAX - FontSize((zSTRING)strMessage) ) / 2;
	PrintTimed( x, nPosY, strMessage, fTime, col );
}

void zCView :: PrintTimedCY( int nPosX, const zSTRING& strMessage, zREAL fTime, zCOLOR* col )
{
	int y = (VIEW_VYMAX - FontY()) / 2;
	PrintTimed( nPosX, y, strMessage, fTime, col );
}

void zCView :: PrintTimedCXY( const zSTRING& strMessage, zREAL fTime, zCOLOR* col )
{
	int x = (VIEW_VXMAX - FontSize((zSTRING)strMessage) ) / 2;
	int y = (VIEW_VYMAX - FontY()) / 2;
	PrintTimed( x, y, strMessage, fTime, col );
}

//
//	PrintMessage() handles multi-line-strings !!!
//

void zCView :: PrintMessage( const zSTRING& strNPC, const zSTRING& strMessage, zREAL fTime, zCOLOR& col )
{
	//
	//	CREATE TEXT LINES
	//
	//zSTRING symbols(" -_#+*~`пїЅ=/&%$пїЅ\"{[]})\\\n");
	zSTRING symbols(" #+*~`пїЅ=/&\\\n\t"); // [SPECKELS] Satzzeichen nicht als einzelnes Wort

	zSTRING wordstr,atext;
	int		wordc = 1;
	int		xlen;
	int		nLines = 0;	

	int maxlines = 0;
	if (FontY()>0)	maxlines = (py2-py1) / FontY();
	else			return;

	//
	// NPC-Name anzeigen (in einzelner Zeile ueber dem Text)
	//
	if (!strNPC.IsEmpty())
	{
		Nextline( strNPC, fTime, &zCOLOR(255,255,255,255));
	};

	do {
		wordstr = strMessage.PickWord(wordc,symbols,"");
		if (wordstr=="\t") wordstr=" ";
		if (wordstr=="\n") {			
			atext.TrimLeft();
			Nextline( atext, fTime, &col );
			nLines++;

		} else if (wordstr.Length()>0) {
			
			// Wort schreiben
			// wordstr += " ";
			xlen = FontSize(wordstr);
			// Passt Wort in Zeile ?
			if (winx+xlen>=px2) {
				atext.TrimLeft();				
				Nextline( atext, fTime, &col );
				nLines++;
				atext.Clear();				
			}
			atext += wordstr;
			winx  += xlen;
		}
		wordc++;

	} while ((wordstr.Length()>0) && (nLines < maxlines));
}

void zCView :: PrintMessageCXY( const zSTRING& strNPC, const zSTRING& strMessage, zREAL fTime, zCOLOR& col )
{
	int nLines = 0;

	int maxlines = 0;
	if (FontY()>0)	maxlines = (py2-py1) / FontY();
	else			return;

	int frameX = anx(20);
	winx  = px1 + frameX;

	ClrPrintwin();
	//
	{
		//
		//	CREATE TEXT LINES
		//
		
		// zSTRING symbols(" -_#+*~`пїЅ=/&%$пїЅ\"{[]})\\\n");
		zSTRING symbols(" #+*~`пїЅ=/&\\\n\t"); // [SPECKELS] Satzzeichen nicht als einzelnes Wort
		zSTRING wordstr,atext;
		int		wordc = 1;
		int		xlen;

		do {
			wordstr = strMessage.PickWord(wordc,symbols,"");
			if (wordstr=="\t") wordstr=" ";
			if (wordstr=="\n") {
			
				atext.TrimLeft();
				Nextline( atext, fTime, &col );
				nLines++;

			} else if (wordstr.Length()>0) {
				
				// Wort schreiben
				// wordstr += " ";
				xlen = FontSize(wordstr);
				// Passt Wort in Zeile ?
				if (winx+xlen+frameX>=px2) {
					atext.TrimLeft();
					Nextline( atext, fTime, &col );
					nLines++;
					atext.Clear();
					winx  = px1 + frameX;
				}
				atext += wordstr;
				winx  += xlen;
			}
			wordc++;

		} while ((wordstr.Length()>0) && (nLines < maxlines));
	}

	if (!strNPC.IsEmpty()) nLines++;
	
	//
	float	fPadding = (nLines - maxlines) / 2.0f;		// center		
			fPadding *= FontY();
			fPadding -= (FontY() / 2.0f);
	int		nPadding = (int) fPadding;
	
	nLines   = 0;

	ClrPrintwin();

	//
	// NPC-Name anzeigen (in einzelner Zeile ueber dem Text)
	//
	if (!strNPC.IsEmpty())
	{
		Nextline( strNPC, fTime, &zCOLOR(255,255,255,255), &nPadding );		
	};
	
	//
	// Text anzeigen
	//
	{
		// zSTRING symbols(" -_#+*~`пїЅ=/&%$пїЅ\"{[]})\\\n");
		zSTRING symbols(" #+*~`пїЅ=/&\\\n\t"); // [SPECKELS] Satzzeichen nicht als einzelnes Wort
		zSTRING wordstr,atext;
		int		wordc = 1;
		int		xlen;
		winx  = px1 + frameX;

		do {
			wordstr = strMessage.PickWord(wordc,symbols,"");
			if (wordstr=="\t") wordstr=" ";
			if (wordstr=="\n") {
			
				atext.TrimLeft();
				Nextline( atext, fTime, &col, &nPadding );
				nLines++;

			} else if (wordstr.Length()>0) {
				
				// Wort schreiben
				// wordstr += " ";
				xlen = FontSize(wordstr);
				// Passt Wort in Zeile ?
				if (winx+xlen+frameX>=px2) {
					atext.TrimLeft();
					Nextline( atext, fTime, &col, &nPadding );					
					nLines++;
					atext.Clear();
					winx  = px1 + frameX;					
				}
				atext += wordstr;
				winx  += xlen;
			}
			wordc++;

		} while ((wordstr.Length()>0) && (nLines < maxlines));
	}
}

void zCView :: PrintSelection( const zSTRING& strYes, const zSTRING& strNo, zCOLOR& colYes, zCOLOR& colNo )
{
	int yYes = VIEW_VYMAX / 2 - FontY()	;/// 2 - FontY() / 4;
	int yNo  = VIEW_VYMAX / 2	;//			+ FontY() / 4;

	ClrPrintwin();
	PrintTimedCX( yYes, strYes, -2.0f, &colYes );
	PrintTimedCX( yNo , strNo , -2.0f, &colNo  );
}

// open, output, close

//
//	fTime Values :	>=  0.0f	close after specified time
//					== -1.0f	close after char-count * VIEW_CHAR_TIME
//					== -2.0f	will be closed manually
//

void zCView :: Dialog( int nPosX, int nPosY, const zSTRING& strMessage, zREAL fTime, zCOLOR* col )
{
	this->ForceOpen();
//	if ( ! isOpen )	Open();

	if ( fTime == -1.0f )	timeDialog = s_fViewTimePerChar * strMessage.Length();
	else					timeDialog = fTime;

	PrintTimed( nPosX, nPosY, strMessage, fTime, col );
}

void zCView :: DialogCX( int nPosY, const zSTRING& strMessage, zREAL fTime, zCOLOR* col )
{
	this->ForceOpen();
//	if ( ! isOpen )	Open();

	if ( fTime == -1.0f )	timeDialog = s_fViewTimePerChar * strMessage.Length();
	else					timeDialog = fTime;

	PrintTimedCX( nPosY, strMessage, fTime, col );
}

void zCView :: DialogCY( int nPosX, const zSTRING& strMessage, zREAL fTime, zCOLOR* col )
{
	this->ForceOpen();
//	if ( ! isOpen )	Open();

	if ( fTime == -1.0f )	timeDialog = s_fViewTimePerChar * strMessage.Length();
	else					timeDialog = fTime;

	PrintTimedCY( nPosX, strMessage, fTime, col );
}

void zCView :: DialogCXY( const zSTRING& strMessage, zREAL fTime, zCOLOR* col )
{
	this->ForceOpen();
//	if ( ! isOpen )	Open();

	if ( fTime == -1.0f )	timeDialog = s_fViewTimePerChar * strMessage.Length();
	else					timeDialog = fTime;

	PrintTimedCXY( strMessage, fTime, col );
}

void zCView :: DialogMessage( const zSTRING& strNPC, const zSTRING& strMessage, zREAL fTime, zCOLOR& col )
{
	//
	//	OPEN THE DIALOG IF NECCESSARY
	//
	this->ForceOpen();

	if ( fTime == -1.0f )	timeDialog = s_fViewTimePerChar * strMessage.Length();
	else					timeDialog = fTime;

	if ( resizeOnOpen )
	{
		int nWidth, nHeight;
		int nPosX , nPosY  ;

		//
		//	CALC MOST LENGTHY TEXT
		//
		if ( strMessage.Length() > textMaxLength.Length() )
		{
			this->textMaxLength = strMessage;
			this->maxTextLength = strMessage.Length();

			//
			//	DO NOT ALLOW MORE THAN 40 CHARS PER LINE
			//
			if ( maxTextLength > 40 ) maxTextLength = 40;
		}

		//
		//	GET SIZE & POS
		//
		GetSize( nWidth, nHeight );
		GetPos ( nPosX , nPosY	 );

		//
		//	CALC WINDOW SIZE & POS
		//
		nWidth = ::screen->FontSize( textMaxLength );
		if ( nWidth > 6144 ) nWidth = 6144;
		nPosX  = ( VIEW_VXMAX - nWidth ) / 2;
		nWidth += FontSize( zSTRING("    ") );

		//
		//	UPDATE SIZE & POS
		//
		SetSize( nWidth, nHeight );
		SetPos ( nPosX , nPosY	 );
	}

	PrintMessage( strNPC, strMessage, -1.0f, col );
}

void zCView :: DialogMessageCXY( const zSTRING& strNPC, const zSTRING& strMessage, zREAL fTime, zCOLOR& col )
{
	//
	//	OPEN THE DIALOG IF NECCESSARY
	//
	this->ForceOpen();

	if ( fTime == -1.0f )	timeDialog = s_fViewTimePerChar * strMessage.Length();
	else					timeDialog = fTime;

	if ( resizeOnOpen )
	{
		int nWidth, nHeight;
		int nPosX , nPosY  ;

		//
		//	CALC MOST LENGTHY TEXT
		//
		if ( strMessage.Length() > textMaxLength.Length() )
		{
			this->textMaxLength = strMessage;
			this->maxTextLength = strMessage.Length();

			//
			//	DO NOT ALLOW MORE THAN 40 CHARS PER LINE
			//
			if ( maxTextLength > 40 ) maxTextLength = 40;
		}

		//
		//	GET SIZE & POS
		//
		GetSize( nWidth, nHeight );
		GetPos ( nPosX , nPosY	 );

		//
		//	CALC WINDOW SIZE & POS
		//
		nWidth = ::screen->FontSize( textMaxLength );
		nWidth += FontSize( zSTRING("    ") );
		if ( nWidth > 6144 ) nWidth = 6144;
		nPosX  = ( VIEW_VXMAX - nWidth ) / 2;

		//
		//	UPDATE SIZE & POS
		//
		SetSize( nWidth, nHeight );
		SetPos ( nPosX , nPosY	 );
	}

	PrintMessageCXY( strNPC, strMessage, -1.0f, col );
}

void zCView :: DialogSelection( const zSTRING& strYes, const zSTRING& strNo, zCOLOR& colYes, zCOLOR& colNo, zREAL fTime )
{
	if ( resizeOnOpen )
	{
		if ( fTime == -1.0f )	timeDialog = zMax( s_fViewTimePerChar * strYes.Length(), s_fViewTimePerChar * strNo.Length() );
		else					timeDialog = fTime;

		int nWidth, nHeight;
		int nPosX , nPosY  ;

		//
		//	CALC MOST LENGTHY TEXT
		//
		if ( strYes.Length() > textMaxLength.Length() )
		{
			this->textMaxLength = strYes;
			this->maxTextLength = strYes.Length();
		}

		if ( strNo.Length() > textMaxLength.Length() )
		{
			this->textMaxLength = strNo;
			this->maxTextLength = strNo.Length();
		}

		//
		//	GET SIZE & POS
		//
		GetSize( nWidth, nHeight );
		GetPos ( nPosX , nPosY	 );

		//
		//	CALC WINDOW SIZE & POS
		//
		nWidth = ::screen->FontSize( textMaxLength+"    " );
		nPosX  = ( VIEW_VXMAX - nWidth ) / 2;
		nWidth = nWidth > ( VIEW_VXMAX - 1024 ) ? ( VIEW_VXMAX - 1024 ) : nWidth;

		//
		//	UPDATE SIZE & POS
		//
		SetSize( nWidth, nHeight );
		SetPos ( nPosX , nPosY	 );

		//
		//	OPEN THE DIALOG IF NECCESSARY
		//
	//	this->ForceOpen();
		if ( ! isOpen )	Open();
		PrintSelection( strYes, strNo, colYes, colNo );
	}
	else
	{
	//	this->ForceOpen();
		if ( ! isOpen )	Open();
		if ( fTime == -1.0f )	timeDialog = zMax( s_fViewTimePerChar * strYes.Length(), s_fViewTimePerChar * strNo.Length() );
		else					timeDialog = fTime;

		PrintSelection( strYes, strNo, colYes, colNo );
	}
}
//
//	CODECHANGE [ROMAN] END
//

void zCView :: SetFont (zCFont* f)
// Set Font nr
{	
	if (!f) font = zfontman->GetFont(0);
	else	font = f;
}	

void zCView :: SetFontColor	(const zCOLOR& color)
{	
	fontColor = color; 
};

void zCView :: SetFont	(const zSTRING& name)
{
	if (zfontman) font = zfontman -> GetFont( zfontman->Load(name) );
}

zCFont* zCView :: GetFont	()
{	
	return font;
}

zSTRING zCView :: GetFontName ()
{
	if (font)	return font->GetFontName();
	else		return "";
}

int zCView :: FontY()
// Liefert max.HпїЅhe des aktuellen Fonts
{
	if (font)	return any(font->GetFontY()-1);
	else		return 0;
}

int zCView :: FontSize(zSTRING &s)
// Liefert LпїЅnge des Strings in virtuellen Koords
{
	if (font) 
		return anx(font->GetFontX(s));
	else
		return 0;
}

void zCView :: Print (int x, int y, const zSTRING &s)
{
	if (!font) return;
	
	// Auto-Scroll ?
	scrollTimer = 0;

	// Sofort blitten, oder speichern ?
	if ((GetViewID()==VIEW_VIEWPORT) || (this==screen)) {
		// gпїЅltigen Blend-Modi ermitteln
		zTRnd_AlphaBlendFunc oldBlendFunc = zrenderer->GetAlphaBlendFunc();
		if ((alphafunc!=zRND_ALPHA_FUNC_BLEND) && (alphafunc!=zRND_ALPHA_FUNC_ADD)) {
			zrenderer -> SetAlphaBlendFunc (zRND_ALPHA_FUNC_BLEND);
		} else {
			zrenderer -> SetAlphaBlendFunc (alphafunc);			
		}
		// Koordinaten auf Pixel umrechnen
		PrintChars (nax(x),nay(y),s);
		zrenderer -> SetAlphaBlendFunc (oldBlendFunc);		
	
	} else {
		CreateText(x,y,s);
	}
}

void zCView :: PrintChars	(int x, int y, const zSTRING &s)
{
	if (!font) return;
	
	zBOOL	filter			=	zrenderer->GetBilerpFilterEnabled();
								zrenderer->SetBilerpFilterEnabled	(TRUE);
	zBOOL	oldzWrite		=	zrenderer->GetZBufferWriteEnabled();
								zrenderer->SetZBufferWriteEnabled	(FALSE);
	zTRnd_ZBufferCmp oldCmp	=	zrenderer->GetZBufferCompare();
								zrenderer->SetZBufferCompare		(zRND_ZBUFFER_CMP_ALWAYS);
	zTRnd_AlphaBlendFunc 
			oldBlendFunc	=	zrenderer->GetAlphaBlendFunc();

	// x/y sind bereits Pixelkoordinaten !!!!
	if (!font) zERR_FAULT("U: PrintChars: Font not set (font==NULL)");
	int fontWidth	= 0;
	int fontHeight	= font->GetFontY();
	zCTexture* ftex = font->GetFontTexture();

	int clipx1 = pposx;
	int clipx2 = pposx + psizex - 1;

	zVEC2 pos1,pos2,texuv1,texuv2;

	//GetPixelExtends						(pos1[0],pos1[1],pos2[0],pos2[1]);
	//zrenderer->SetViewport				(pos1[0],pos1[1],pos2[0]-pos1[0],pos2[1]-pos1[1]);

	if ((oldBlendFunc!=zRND_ALPHA_FUNC_ADD) && (oldBlendFunc!=zRND_ALPHA_FUNC_BLEND)) 
		zrenderer->SetAlphaBlendFunc(zRND_ALPHA_FUNC_BLEND);

	int letterDist = font->GetLetterDistance();
	int spaceWidth = font->GetWidth(' ');

	zREAL farZ;
	if (zCCamera::activeCam) farZ = zCCamera::activeCam->GetNearClipZ()+1;
	else					 farZ = 1;

	for (int i=0; i<s.Length(); i++) {
		
		if (zBYTE(s[i])>32) {
			
			font -> GetFontData(s[i],fontWidth,texuv1,texuv2);

			pos1[0] = x;
			pos1[1] = y;
			pos2[0] = x + fontWidth - 1;
			pos2[1]	= y + fontHeight - 1;
			
			// Beenden - Clipping rechts
			if (pos2[0]> clipx2) break;
			// Clipping links ?

			if (pos1[0]>=clipx1) zrenderer->DrawTile	(ftex,pos1,pos2,farZ,texuv1,texuv2,fontColor);
			
			x += fontWidth + letterDist;

		} 
		else if (s[i]==32) 
		{			
			x += spaceWidth;
		};
	}
	
	zrenderer->SetBilerpFilterEnabled	(filter);
	zrenderer->SetZBufferWriteEnabled	(oldzWrite);
	zrenderer->SetZBufferCompare		(oldCmp);
	return;
}

void zCView :: PrintCX (int y,const zSTRING& s)
// PrintCenter
{
	int x = (VIEW_VXMAX - FontSize((zSTRING)s) ) / 2;
	Print(x,y,s);
}

void zCView :: PrintCY(int x,const zSTRING& s)
{
	int y = (VIEW_VYMAX - FontSize((zSTRING)s) ) / 2;
	Print(x,y,s);
};

void zCView :: PrintCXY (const zSTRING &s)
{
	int y,x;
	x = (VIEW_VXMAX - FontSize((zSTRING)s))	/ 2;
	y = (VIEW_VYMAX - FontY())				/ 2;
	Print(x,y,s);
}

/*--------------------------------------------------------------------------

    zCView::ClrPrintwin()

 

    ??-???-00       [Roman Keskenti]

						Added initialization for text length recognition

--------------------------------------------------------------------------*/ 
void zCView :: ClrPrintwin(void)
{
	if ((intflags & VIEW_I_TEXT)==0) InitPrintwin();
	
	textLines.DeleteListDatas();
	winx  = px1; winy = py1; 

	//
	//	CODECHANGE [ROMAN]
	//
	maxTextLength = 0;
	textMaxLength = "";
	//
	//	CODECHANGE [ROMAN]	END
	//
}

/*--------------------------------------------------------------------------

    zCView::CreateText()

 

    ??-???-00       [Roman Keskenti]

						Added text length recognition

--------------------------------------------------------------------------*/ 
zCViewText* zCView :: CreateText(int x,int y,const zSTRING &s)
{
	zCOLOR colFont = GetFontColor();	//if ( colFont.alpha == 0x00 ) colFont.alpha = 0xff;

	// Gibts diesen Eintrag schon, oder neuen erzeugen ?
	zCList<zCViewText>* textNode = textLines.GetNextInList();
	zCViewText* textData = NULL;
	while (textNode) {
		textData = textNode->GetData();
		textNode = textNode->GetNextInList();
		if ((textData->posx == x) && (textData->posy == y)) {
			textData->font		= GetFont();
			textData->color		= colFont;
			textData->colored	= FALSE;
			textData->text		= s;
			return textData;
		}
	}

	//
	//	CODECHANGE [ROMAN]
	//
	if ( s.Length() > maxTextLength ) 
	{
		maxTextLength = s.Length();
		textMaxLength = s;															// store text width maximum length for resize
	}
	//
	//	CODECHANGE [ROMAN] END
	//

	zREAL dummy = 0.0f;
	zCViewText* text = zNEW( zCViewText(x,y,s,dummy,colFont, FALSE, TRUE) );
	text->font = GetFont();
	textLines.Insert(text);
	return text;
}

zSTRING zCView :: GetFirstText()
{
	// Gibts diesen Eintrag schon, oder neuen erzeugen ?
	zCList<zCViewText>* textNode = textLines.GetNextInList();
	zCViewText* textData = NULL;
	while (textNode) {
		textData = textNode->GetData();
		textNode = textNode->GetNextInList();
		if (!textNode) return textData->text;
	}
	return zSTR_EMPTY;
}

//
//	CODECHANGE [ROMAN]
//

/*--------------------------------------------------------------------------

    zCView::Nextline()

 

    ??-???-00       [Roman Keskenti]

						Modified to reflect the changed made to zCViewText
							...	these are mainly timing and color issues

--------------------------------------------------------------------------*/ 
void zCView :: Nextline(const zSTRING& s, zREAL fTime, zCOLOR* col, int* offsetY )
{
	if (HasFlag(VIEW_TXT_CENTER)) 
	{
		winx = (VIEW_VXMAX/2) - (FontSize((zSTRING)s)/2);
	} 
	else 
	{
		winx  = px1;
	}

	// Noch Platz da ?
	if (winy + FontY() > py2) 
	{
		// Nein, alles eine Zeile hoch !
		zCList<zCViewText>* textNode = textLines.GetNextInList();
		zCViewText* textData = NULL;
		while (textNode) 
		{
			textData		= textNode->GetData();
			textNode		= textNode->GetNextInList();
			if (textData->inPrintWin) 
			{
				textData->posy -= FontY();
				// Falls schon unter 0, dann ganz lпїЅschen.....
				if (textData->posy < py1) 
				{
					textLines.Remove(textData);
					delete textData;
				}
			}
		}
		winy -= FontY();
	} 
	// In Liste Speichern	

	//
	//	CODECHANGE [ROMAN]
	//
	zCViewText* tD = 
		CreateText( winx, 
					winy - ( (offsetY) ? *offsetY : 0 ),  
					s, 
					(fTime > 0.0f)	? fTime : 0.0f,
					(col)			? *col  : zCOLOR( 0xFF, 0xFF, 0xFF, 0xFF ), 
					(fTime > 0.0f)	? TRUE  : FALSE, 
					(col)			? TRUE  : FALSE );
	//
	//	CODECHANGE [ROMAN]
	//

	if (tD) tD->inPrintWin = TRUE;
	// naechste Zeile
	winy += FontY();

	scrollTimer = 0.0f;
}
//
//	CODECHANGE [ROMAN]
//

void zCView :: DefPrintwin (int x1,int y1,int x2,int y2)
{
	px1	 = x1; py1	= y1; px2 = x2; py2 = y2;
	winx = x1; winy = y1;
	ClrPrintwin();
}

void zCView :: Printwin (const zSTRING &s)
{
	zSTRING p = s;
	// Sonderzeichen \n umwandeln ("\\n" => '\n')
	int index;
	do { index = p.Search("\\n");p.Delete("\\n");p.Insert(index,"\n"); }	
	while(index>=0);

	if ((intflags & VIEW_I_TEXT)==0) InitPrintwin();

	// zSTRING symbols(" ,;.:-_#+*~`пїЅ?=)(/&%$пїЅ\"!{[]})\\\n");
	zSTRING symbols(" #+*~`пїЅ=/&\\\n\t"); // [SPECKELS] Satzzeichen nicht als einzelnes Wort
	zSTRING wordstr,atext;
	int		wordc = 1;
	int		xlen;

	int maxlines = 0;
	if (FontY()>0)	maxlines = (py2-py1) / FontY();
	else			return;

	do {
		wordstr = p.PickWord(wordc,symbols,"");
		if (wordstr=="\t") wordstr=" ";
		if (wordstr=="\n") 
		{
			atext.TrimLeft();
			Nextline(atext);
			atext.Clear();
		} 
		else if (wordstr.Length()>0) 
		{			
			// Wort schreiben
			// wordstr += " ";
			xlen = FontSize(wordstr);
			// Passt Wort in Zeile ?
			if (winx+xlen>=px2) 
			{
				atext.TrimLeft();
				Nextline(atext);
				atext.Clear();
			}
			atext += wordstr;
			winx  += xlen;
		}
		wordc++;

	} while (wordstr.Length()>0);
}

zSTRING zCView :: Input(int len)
// Read a user input
// len = maximale Anzahl der Zeichen
{
	zSTRING s;
	return Input(len,s);
}

zSTRING zCView :: Input(int len, zSTRING &ls)
// Read a user input
// len = maximale Anzahl der Zeichen
{
	zSTRING s = ls,c;
	int key,l=s.Length();

	PrintCXY(s + "|");
	do {
		sysEvent	();
		sysIdle		(10);
		DrawItems	();

		if ((key = zinput->GetKey())!=0) {
			if ((key & KEY_RELEASE)) continue;
			if (key==13) break;
			if (key==8) {
				if (l>0) { s.Delete(s.Length()-1,1); l--; }
			} else if ((l<len) && (key>=32)) {
				if ((key>=KEY_A) && (key<=KEY_Z) && (!zinput->KeyPressed(KEY_LSHIFT))) key+=32;
				if ((key==KEY_0) && (zinput->KeyPressed(KEY_LSHIFT) || zinput->KeyPressed(KEY_RSHIFT))) key = 61;
				if (key==KEY_MINUS && (!zinput->KeyPressed(KEY_LSHIFT) && !zinput->KeyPressed(KEY_RSHIFT))) key= 45;
				if (key==KEY_DOT) key = 46;
				if (key==KEY_MINUS && (zinput->KeyPressed(KEY_LSHIFT) || zinput->KeyPressed(KEY_RSHIFT))) key = 95;
				if (key==KEY_8 && (zinput->KeyPressed(KEY_LSHIFT) || zinput->KeyPressed(KEY_RSHIFT))) key = 40;
				if (key==KEY_9 && (zinput->KeyPressed(KEY_LSHIFT) || zinput->KeyPressed(KEY_RSHIFT))) key = 41;
				s += (char *)(&key);
				l++;
			}
			s += "|";
			ClrPrintwin();
			PrintCXY(s);
			s.Delete(s.Length()-1,1);
		}

	} while (key!=13);
	
	ClrPrintwin();
	PrintCXY(s);
	return s;
}

zSTRING zCView :: Input (int x,int y, int len, zSTRING &s)
{
	unsigned char w;
	int l = s.Length();

	do
	{
		sysEvent();
		sysIdle	(10);

		ClrPrintwin();
		Print	 (x, y, s + "|");
		screen	 ->DrawItems();
		
		w = zinput->GetChar();
		switch (w)
		{
			case 0:
				break;
			case 13:
				break;
			case 8:
				if (l > 0)
				{
					s.Delete(s.Length() - 1, 1);
					l--;
				}
				break;
			default:
				if ((w >= 32) && (w <= 255))
				{
					s += (char)(w);
					l++;
				}
				break;
		}

	}
	while (w != 13);
	
	while (zinput->GetKey()!=0) {};

	return s;
}

int zCView :: InputNumber(int wert,int len)
// Read a user input
// len = maximale Anzahl der Zeichen
{
	zSTRING s(""),c("");
	int key,l;

	ClrPrintwin();
	s = wert; 
	l = s.Length();
	s+="|";
	PrintCXY(s.ToChar());
	s.Delete(s.Length()-1,1);
	do {
		sysEvent();
		DrawItems();

		if ((key = zinput->GetKey())!=0) {
			if (key==13) break;
			if (key==8) {
				if (l>0) { s.Delete(s.Length()-1,1); l--; }
			} else if ((l<len) && (key>=KEY_0) && (key<=KEY_9)) {
				s += (char *) (&key);
				l++;
			}

			s+="|";
			ClrPrintwin();
			PrintCXY(s);
			s.Delete(s.Length()-1,1);
		}

	} while (key!=13);

	ClrPrintwin();
	PrintCXY(s);	
	return s.ToInt();
}

void zCView :: PrintDebug(const zSTRING &s)
{
	if (showDebug) StdPrintwin(s);
};

void zCView :: SetShowDebug (zBOOL on)
{
	showDebug = on;
}

zBOOL zCView :: GetShowDebug ()
{
	return showDebug;
}

// **********************************************************************
//								Insert
// **********************************************************************
void zCView :: InsertItem(zCView *child, zBOOL stayOnTop)
{	
	if (!child)					return;
	if (child->IsVisible())		return;
	
	if (child->HasFlag(VIEW_MODAL)) stayOnTop=TRUE;
	
	child -> ondesk = TRUE;
	
	// Restore Position and Size
	int vpx,vpy;
	int vsx,vsy;
	child -> GetPos		(vpx,vpy);
	child -> GetSize	(vsx,vsy);
	child -> SetOwner	(this);
	child -> SetPos		(vpx,vpy);
	child -> SetSize	(vsx,vsy);
	if (stayOnTop) child->Setflags(VIEW_STAYONTOP);

	if (child -> HasFlag(VIEW_TXT_AUTO)) 
	{
		// Hier erstmal Werte festlegen
		// Tolles Text-Auto-Size Feature !
		zCFont* childfont	= child->font;
		zCFont* oldfont		= font;
		SetFont				(childfont);
		int fx = FontSize	(child->GetFirstText());
		int fy = FontY		();
//		int f  = child->flags;
		int px,py;
		child	-> GetPos	(px,py);
		child	-> Init		(px,py,px+fx,py+fy,child->GetViewID());
		child	-> Setflags	(flags);
		child	-> SetFont	(childfont);
		SetFont				(oldfont);
	}
	
	if (child->HasFlag(VIEW_MODAL)) modal = child;
	
	zCView* aView=0;
	if (!stayOnTop && childs.Count()>0)
	{		
		int i=childs.Count();
		while ((i>=0) && (aView = childs.Get(i)))
		{		
			if (!aView->HasFlag(VIEW_STAYONTOP)) break;
			i--;
		};		
	}
	if (aView)
	{		
		childs.InsertAsNext(aView,child);
	}
	else
	{
		childs.InsertLast(child);
	};	
}

void zCView :: RemoveItem(zCView *ele)
// Element aus Child-Liste entfernen
{
	if (childs.IsIn(ele)) {
		childs.Remove(ele);
		ele->SetOwner(NULL);
		ele->ondesk	= FALSE;
		ele->SetEnableHandleEvent(FALSE);
		if (ele->HasFlag(VIEW_MODAL)) modal = NULL;
	}
	else // Fuer den Fall, dass der Owner faelschlicherweise gesetzt ist
	{
		if (ele->GetOwner() == this) ele->SetOwner(NULL);
	};
}

// **********************************************************************
// Special Stuff, graphics mode change							
// **********************************************************************

void zCView :: ChangeMode(void)
{
	
}

void zCView :: SetNextMode()
{
	// 1.Change Items 2.Change Screen -> Reihenfolge wichtig !
	ChangeMode();
}

/*--------------------------------------------------------------------------

    zCView::SetMode()

     ??-???-00      [Roman Keskenti]
					Keeps the window from maximizing in window mode
	28-Sep-00		[HILDEBRANDT]
					added initContextHandle (aka HWND for zCRenderer)
--------------------------------------------------------------------------*/ 

void zCView :: SetMode(int x,int y,int bpp, zTSystemContextHandle* initContextHandle)
{

	// Switch mode	
	zrenderer->Vid_SetMode(x,y,bpp, initContextHandle);
		
	if (!screen) {
		// Init Screen
		screen =  zNEW( zCView	(0,0,VIEW_VXMAX-1,VIEW_VYMAX-1,VIEW_SCREEN) );
		screen -> SetFont		(VIEW_FONT_DEFAULT);
		screen -> ondesk = TRUE;
		screen -> psizex = x;
		screen -> psizey = y;		
	} else {
		zCView :: ChangeMode	();
		screen -> psizex = x;
		screen -> psizey = y;		
		// screen -> SetPos		(0,0);
		// screen -> SetSize	(VIEW_VXMAX,VIEW_VYMAX);
	}
	screen->RecalcChildsSize();
	screen->RecalcChildsPos();	
}



// ****************************************************************
// Line - Helpers 
// ****************************************************************

void zCView :: Line(int x1, int y1, int x2, int y2, const zCOLOR& color)
// Virtual Coords !!!!!
{
	x1 = screen->nax(x1);
	y1 = screen->nay(y1);
	x2 = screen->nax(x2);
	y2 = screen->nay(y2);
	if (ClipLine(x1,y1,x2,y2)) {
		zrenderer->DrawLine	((float)x1,(float)y1,(float)x2,(float)y2,color);
	}
}

int zCView :: GetCode(int x,int y)
{
	int all;
	if (y>psizey-1) all=8; else
	if (y<0)		all=4; else all=0;
	if (x>psizex-1) all=all | 2; else
	if (x<0)		all=all | 1;
	return (all);
};

int zCView :: ClipLine(int &x0,int &y0,int &x1,int &y1)
{
	int code1,code2,outcode,x,y;
	int cx1 = 0,		cy1 = 0;
	int cx2 = psizex-1,	cy2 = psizey-1;
	
	code1 = GetCode(x0,y0);
	code2 = GetCode(x1,y1);
	do {
		if ((code1==0) && (code2==0)) return 1; else
		if ((code1 & code2)!=0)		  return 0; else
		{
			if (code1!=0) outcode=code1; else outcode=code2;
			if ((outcode & 8)==8) {
				x = x0+((x1-x0)*(cy2-y0)) / (y1-y0);
				y = cy2;
			} else if ((outcode & 4)==4) {
				x = x0+((x1-x0)*(cy1-y0)) / (y1-y0);
				y = cy1;
			} else if ((outcode & 2)==2) {
				y = y0+((y1-y0)*(cx2-x0)) / (x1-x0);
				x = cx2;
			} else if ((outcode & 1)==1) {
				y = y0+((y1-y0)*(cx1-x0)) / (x1-x0);
				x = cx1;
			} 
			if (outcode==code1) {
				x0 = x; y0 = y;
				code1 = GetCode(x0,y0);
			} else {
				x1 = x; y1 = y;
				code2 = GetCode(x1,y1);
			}     
       	}
	} while (1);
};

void zCView :: Render ()
{
	DrawItems();
}

// **********************************************************************
//							zCViewText
// **********************************************************************

//
//	CODECHANGE [ROMAN]
//

/*--------------------------------------------------------------------------

    zCViewText::zCViewText()

 

    ??-???-00       [Roman Keskenti]

						Added initialization for timing and color purposes

    29-Aug-00       [Roman Keskenti]

						Adapted to use Create() 

--------------------------------------------------------------------------*/ 
zCViewText :: zCViewText ( int x, int y, const zSTRING &s )
{
	zREAL fTime = 0.0f;
	this->Create( x, y, s, fTime, zCOLOR( 0xFF, 0xFF, 0xFF, 0xFF ), FALSE, FALSE );
}

/*--------------------------------------------------------------------------

    zCViewText::zCViewText()

 

    ??-???-00       [Roman Keskenti]

						New overloaded method that reflects the changes made to zCViewText
						Added initialization for timing and color purposes

    29-Aug-00       [Roman Keskenti]

						Adapted to use Create() 

--------------------------------------------------------------------------*/ 
zCViewText :: zCViewText ( int x, int y, const zSTRING &s, zREAL &t, zCOLOR &c, zBOOL bT, zBOOL bC )
{
	this->Create( x, y, s, t, c, bT, bC );
}

/*--------------------------------------------------------------------------

    zCViewText::Create()

 

    29-Aug-00       [Roman Keskenti]

						Initial implementation

--------------------------------------------------------------------------*/ 
void zCViewText :: Create ( int x, int y, const zSTRING &s, zREAL &t, zCOLOR &c, zBOOL bT, zBOOL bC )
{
	posx		= x;
	posy		= y;
	text		= s;
	timer		= t;
	timed		= bT;
	color		= c;			
	colored		= bC;
	font		= NULL;
	inPrintWin	= FALSE;
}

//
//	CODECHANGE [ROMAN] END
//

zCViewText :: ~zCViewText ()
{
	font	= NULL;
}

#ifdef COMPILING_SPACER

// **********************************************************************
//							MFC - Specific
// **********************************************************************

void zCView :: MFC_CreateScreen(void *adr,int x,int y,int bpp)
// Setting up values for "Screen-Bitmap" for MFC
{
	//MFC_ViewInit();
	zrenderer->vid_xdim		= x;
	zrenderer->vid_ydim		= y;
	zrenderer->vid_bpp		= bpp;
	zrenderer->vid_pitch	= x * (bpp>>3);
	// Set Up screen
	screen =  zNEW( zCView	(0,0,VIEW_VXMAX-1,VIEW_VYMAX-1,VIEW_SCREEN) );
	screen -> SetFont		(VIEW_FONT_DEFAULT);
	// FIXME : Umpftata - Hack, das ist Karnevalverdaechtig !!!!
	//screen -> gfx = new zCGfx	(1,1);
	//screen -> GetImageGfx() -> data -> scr = (zBYTE *) adr;
	//Video  =  (zBYTE *) adr;
}

void View_SetScreenSize (int x,int y,int bpp)
{
	zrenderer->vid_xdim		= x;
	zrenderer->vid_ydim		= y;
	zrenderer->vid_bpp		= bpp;
	zrenderer->vid_pitch	= x * (bpp>>3);
}

void zCView :: MFC_KeyDown(int k)
{	
	// im spacer muss hier die DIK DInput Konstante in den "richtigen" Spacer
	// Code gewandelt werden
	zinput->SetKey( zCInput_Win32::GetWin32CodeFromDos32Code(k) ,TRUE );
	//kbMask[k] = TRUE;
};

void zCView :: MFC_KeyUp(int k)
{
	zinput->SetKey( zCInput_Win32::GetWin32CodeFromDos32Code(k) ,FALSE );
	//kbMask[k] = FALSE;
}

#endif

// **********************************************************************
// Colors
// **********************************************************************
/*
zCOLOR	GFX_WHITE		(255,255,255,255),
		// Yellows
		GFX_YELLOW		(255,255,0,255),
		GFX_LYELLOW		(255,255,224,255),
		GFX_GOLD		(255,215,0,255),
		// Orange
		GFX_ORANGE		(255,128,0,255),
		GFX_DORANGE		(255,140,0,255),
		GFX_CARROT		(237,145,33,255),
		// Reds
		GFX_RED			(255,0,0,255),
		GFX_DRED		(255,99,71,255),
		GFX_PINK		(255,192,203,255),
		GFX_LPINK		(255,182,193,255),
		GFX_DPINK		(255,20,147,255),
		// Magentas
		GFX_MAGENTA		(255,0,255,255),
		GFX_ORCHID		(218,112,214,255),
		GFX_PURPLE		(160,32,240,255),
		GFX_VIOLET		(143,94,153,255),
		// Cyans
		GFX_CYAN		(0,255,255,255),
		GFX_AQUA		(127,255,212,255),
		// Greens
		GFX_GREEN		(0,255,0,255),
		GFX_DGREEN		(0,100,0,255),
		GFX_PALEGREEN	(152,251,152,255),
		GFX_OLIVE		(59,94,43,255),
		// Blues
		GFX_BLUE		(0,0,255,255),
		GFX_LBLUE		(173,216,230,255),
		GFX_MBLUE		(0,0,205,255),
		GFX_INDIGO		(8,46,84,255),
		GFX_DBLUE		(0,0,128,255),
		GFX_SKY			(135,206,235,255),
		GFX_STEEL		(70,130,180,255),
		// Browns
		GFX_BROWN		(128,42,42,255),
		GFX_OCHRE		(135,66,31,255),
		GFX_DOCHRE		(115,61,26,255),
		GFX_BEIGE		(163,148,128,255),
		GFX_FLESH		(255,125,64,255),
		GFX_KHAKI		(240,230,140,255),
		// Greys
		GFX_GREY		(192,192,192,255),
		GFX_LGREY		(211,211,211,255),
		GFX_COLDGREY	(128,138,135,255),
		GFX_WARMGREY	(128,128,105,255),
		// Blacks
		GFX_BLACK		(0,0,0,255),
		GFX_IVORY		(41,36,33,255);
*/

zSTRING zCView::PatchMenuItemPrintwin()
{
	return GetFirstText();
}

#pragma warning ( default:4244 )
#pragma warning ( default:4706 )
