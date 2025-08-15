/******************************************************************************** 
 
     $Workfile:: zview.h              $                $Date:: 11.01.01 21:42   $
     $Revision:: 40                   $             $Modtime:: 11.01.01 21:05   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zview.h $
 * 
 * 40    11.01.01 21:42 Speckels
 * 
 * 39    11.01.01 21:09 Hildebrandt
 * 
 * 38    11.01.01 18:39 Speckels
 * 
 * 37    5.12.00 21:57 Speckels
 * 
 * 36    4.12.00 18:23 Moos
 * 
 * 35    1.12.00 16:54 Wohlers
 * 
 * 34    1.12.00 3:08 Speckels
 * 
 * 33    8.11.00 21:51 Hildebrandt
 * 
 * 32    2.11.00 16:14 Speckels
 * 
 * 31    19.10.00 20:02 Speckels
 * 
 * 30    19.10.00 18:53 Keskenti
 * 
 * 29    19.10.00 18:27 Keskenti
 * 
 * 28    19.10.00 17:48 Keskenti
 * 
 * 27    19.10.00 17:15 Keskenti
 * 
 * 26    4.10.00 15:16 Speckels
 * 
 * 25    28.09.00 19:20 Hildebrandt
 * 
 * 24    13.09.00 18:50 Wohlers
 * 
 * 23    8.09.00 19:59 Hildebrandt 
 * 
 * 22    8.09.00 15:46 Keskenti
 * 
 * 21    7.09.00 16:15 Keskenti
 * 
 * 20    2.09.00 1:02 Herget
 * 
 * 19    1.09.00 17:52 Herget
 * 
 * 18    30.08.00 20:03 Keskenti
 * 
 * 17    15.08.00 13:58 Keskenti
 * 
 * 16    15.08.00 13:56 Keskenti
 * 
 * 15    28.07.00 16:10 Keskenti
 * 
 * 14    27.07.00 22:06 Keskenti
 * 
 * 12    27.07.00 21:50 Keskenti
 * 
 * 11    27.07.00 20:59 Keskenti
 * 
 * 10    27.07.00 18:07 Keskenti
 * 
 * 10    27.07.00 12:24 Keskenti
 * Open/Close Funktionalitiaet
 * Text-Farbe und -Dauer 
 * 
 * 9     5.07.00 12:24 Wohlers
 * 
 * 8     4.07.00 12:29 Wohlers
 * FontMan Bugfix
 * 
 * 6     22.05.00 18:45 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 5     5.05.00 23:36 Wohlers
 * Anpassung ZCView
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 6     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 4     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ZVIEW_H__
#define __ZVIEW_H__

#ifndef __ZSTRING_H__
#include "zString.h"
#endif

#ifndef __ZGRAFIX_H__
#include "zGrafix.h"
#endif

#ifndef __ZDISK_H__
#include "zDisk.h"
#endif

#ifndef __ZLIST_H__
#include "zList.h"
#endif

#ifndef __ZRENDERER_H__
#include "zRenderer.h"
#endif

#ifndef __ZVIEWBASE_H__
#include "zViewBase.h"
#endif


// *******************************************************************************
// zCInputCallback
// *******************************************************************************

class zCInputCallback
{
public:
	zCInputCallback						();
	~zCInputCallback					();
	
	void			SetHandleEventTop	();
	void			SetEnableHandleEvent(zBOOL flag);
	zBOOL			GetEnableHandleEvent();

	virtual zBOOL	HandleEvent			(int key)		{ return FALSE; };

	// Statics
	static zBOOL	DoEvents			(int key);
	static void		GetInput			();

private:
	// Statics
	static zCList	<zCInputCallback> inputList;
};

// *******************************************************************************
// zCView
// *******************************************************************************

#define VIEW_VXMAX 8192
#define VIEW_VYMAX 8192

enum zTviewID { VIEW_SCREEN,VIEW_VIEWPORT,VIEW_ITEM };

class zCView;

extern zCView *screen;

// Constants Desktop-Itemflags
const int VIEW_GROUNDED		=    1<<3;	// Item cannot be on top.
const int VIEW_MODAL		=    1<<6;	// Item modal
const int VIEW_AUTOSCROLL	=    1<<8;
const int VIEW_TXT_CENTER	=    1<<9;
const int VIEW_TXT_AUTO		=	 1<<10;
const int VIEW_STAYONTOP	=	 1<<11;

const int VIEW_I_TEXT		= 1;		// Init as Textwindow 

class zCFont;

class zCViewText {
public:
	zCViewText			(int x, int y, const zSTRING &s);
	virtual ~zCViewText	();

	int					posx,posy;
	zSTRING				text;
	zCFont*				font;
	zREAL				timer;
	zBOOL				inPrintWin;

	//
	//	CODECHANGE [ROMAN]
	//
	zCViewText			(int x, int y, const zSTRING &s, zREAL &t, zCOLOR &c, zBOOL timed = TRUE, zBOOL colored = TRUE );
	void Create			(int x, int y, const zSTRING &s, zREAL &t, zCOLOR &c, zBOOL timed = TRUE, zBOOL colored = TRUE );

	zCOLOR				color;
	zBOOL				timed;
	zBOOL				colored;
	//
	//	CODECHANGE [ROMAN] END
	//
};

class zCView : public zCViewBase, public zCInputCallback {

public:
	//
	//	CODECHANGE [ROMAN]
	//
	typedef
	enum zEViewFX
	{
		VIEW_FX_NONE,
		VIEW_FX_ZOOM,
		VIEW_FX_MAX	
	}
	zTViewFX;
	//
	//	CODECHANGE [ROMAN] END
	//

	// Constructor
	zCView										();
	zCView										(int x1,int y1,int x2,int y2,	zTviewID viewID = VIEW_ITEM);
	// Destructor
	virtual ~zCView								();

	void					Init				();
	void					Init				(int x1,int y1,int x2,int y2,	zTviewID viewID = VIEW_ITEM);
	void					Init				(int  x,int  y,const zSTRING& s,zTviewID viewID = VIEW_ITEM);

	// Flags
	void					Setflags			(int f);
	void					ClrFlags			(int f);
	zBOOL					HasFlag				(int flagNr);
	zTviewID				GetViewID			()				{ return viewID;	};
	zBOOL					IsVisible			()				{ return ondesk;	};

	// Owner
	void					SetOwner			(zCView* own)	{ owner = own;		};
	zCView*					GetOwner			()				{ return owner;		};

	// Render options
	void					SetTransparency		(int a);
	void					GetTransparency		();
	void					SetAlphaBlendFunc	(const zTRnd_AlphaBlendFunc &mode);
	zTRnd_AlphaBlendFunc	GetAlphaBlendFunc	()				{ return alphafunc; };
	void					SetColor			(const zCOLOR& color);
	zCOLOR					GetColor			();

	// Primitives
	virtual void			Line				(int x1, int y1, int x2, int y2, const zCOLOR& color);
	virtual int				ClipLine			(int &x0,int &y0,int &x1,int &y1);

	// Place/remove
	void					InsertItem			(zCView *elem, zBOOL stayOnTop=FALSE);
	void					RemoveItem			(zCView *ele);
	void					InsertBack			(const zSTRING &s);
	void					InsertBack			(zCTexture* tex);
	zCTexture*				GetBackTex			() { return backTex; };

	// Koordinate Functions
	virtual int				anx					(int x);
	virtual int				any					(int y);
	virtual int				nax					(int x);
	virtual int				nay					(int y);

	// Methodes Fonts
	void					SetFont				(zCFont* f);			// Set Font per Pointer
	void					SetFont				(const zSTRING& name);	// Set Font per Name
	zCFont*					GetFont				();
	void					SetFontColor		(const zCOLOR& color);
	zCOLOR					GetFontColor		()						{ return fontColor; };
	zSTRING					GetFontName			();
	int						FontY				(void);
	int						FontSize			(zSTRING &s);

	// Prints
	void					Print				(int x,int y,const zSTRING &s);
	void					PrintCX				(int y,const zSTRING &s);
	void					PrintCY				(int x,const zSTRING &s);
	void					PrintCXY			(const zSTRING &s);
	void					Printwin			(const zSTRING &s);

	zSTRING					PatchMenuItemPrintwin();
	//
	//	CODECHANGE [ROMAN]
	//

	// text
public:
	zCViewText*				CreateText			( int x, int y, const zSTRING &s, zREAL t, zCOLOR &c, zBOOL timed = TRUE, zBOOL colored = TRUE );
	void					CheckTimedText		();

	// simply output the text for a certain amount of time
	void					PrintTimed			( int nPosX, int nPosY,  const zSTRING& strMessage, zREAL fTime, zCOLOR* col = NULL );
	void					PrintTimedCX		( int nPosY,			 const zSTRING& strMessage, zREAL fTime, zCOLOR* col = NULL );
	void					PrintTimedCY		( int nPosX,			 const zSTRING& strMessage, zREAL fTime, zCOLOR* col = NULL );
	void					PrintTimedCXY		(						 const zSTRING& strMessage, zREAL fTime, zCOLOR* col = NULL );
	void					PrintMessage		( const zSTRING& strNPC, const zSTRING& strMessage, zREAL fTime, zCOLOR& col );
	void					PrintMessageCXY		( const zSTRING& strNPC, const zSTRING& strMessage, zREAL fTime, zCOLOR& col );
	void					PrintSelection		( const zSTRING& strYes, const zSTRING& strNo, zCOLOR& colYes, zCOLOR& colNo );

	// open, output, close
	void					Dialog				( int nPosX, int nPosY, const zSTRING& strMessage, zREAL fTime, zCOLOR* col = NULL );
	void					DialogCX			( int nPosY,			const zSTRING& strMessage, zREAL fTime, zCOLOR* col = NULL );
	void					DialogCY			( int nPosX,			const zSTRING& strMessage, zREAL fTime, zCOLOR* col = NULL );
	void					DialogCXY			(						const zSTRING& strMessage, zREAL fTime, zCOLOR* col = NULL );
	void					DialogMessage		( const zSTRING& strNPC, const zSTRING& strMessage, zREAL fTime, zCOLOR& col );
	void					DialogMessageCXY	( const zSTRING& strNPC, const zSTRING& strMessage, zREAL fTime, zCOLOR& col );
	void					DialogSelection		( const zSTRING& strYes, const zSTRING& strNo, zCOLOR& colYes, zCOLOR& colNo, zREAL fTime );

	// open/close
	//Create( "dlg_conversation.tga", zCView :: zEViewFX :: VIEW_FX_ZOOM, zCView :: zEViewFX :: VIEW_FX_ZOOM,   -2.0f, FALSE );
	void					Create				( const zSTRING& strTexture		, 
														zTViewFX enuOpen		,
														zTViewFX enuClose		,
														zREAL	 fScrolltime	,
														zBOOL	 bResizeOnOpen	);
	void					SetResizeOnOpen		( zBOOL bResizeOnOpen  )	{ resizeOnOpen  = bResizeOnOpen ; }
	void					SetRemoveOnClose	( zBOOL bRemoveOnClose )	{ removeOnClose = bRemoveOnClose; }
	void					SetOpenFX			( zTViewFX enuFX )			{ fxOpen		= enuFX			; }
	void					SetCloseFX			( zTViewFX enuFX )			{ fxClose		= enuFX			; }
	void					SetOpenSpeed		( zREAL fSpeed )			{ speedOpen		= fSpeed		; }
	void					SetCloseSpeed		( zREAL fSpeed )			{ speedClose	= fSpeed		; }
	void					Open				();																//	BEWARE: if using resizeOnOpen, be sure to insert the text FIRST!
	void					Close				();
	void					ForceOpen			();
	zBOOL					GetFillZ			() const					{ return m_bFillZ;	};
	void					SetFillZ			(const zBOOL a_b)			{ m_bFillZ = a_b;	};
protected:
	void					ApplyOpenClose		( zVEC2& pos1, zVEC2& pos2 );
	void					UpdateOpen			();
	void					UpdateClose			();
	void					UpdateOpenZoom		();
	void					UpdateCloseZoom		();

	zBOOL					m_bFillZ;
public:
	//
	//	CODECHANGE [ROMAN] END
	//

	// Printwindow
	void					InitPrintwin		();
	void					DefPrintwin			(int x1,int y1,int x2,int y2);
	void					ClrPrintwin			();
	void					SetAutoScroll		(zREAL time);	

	void					RecalcChildsPos		();
	void					RecalcChildsSize	();


	// Inputs
	zSTRING					Input				(int len);
	zSTRING					Input				(int len, zSTRING &l);
	zSTRING					Input				(int x,int y,int len, zSTRING &s);
	int						InputNumber			(int wert,int len);

	// Position + Size
	void					GetPos				(int &vx,int &vy);					// Position of view in virtual screen-coords
	void					GetPixelPos			(int &px,int &py);
	void					SetPos				(int  vx,int  vy);
	void					GetSize				(int &vx,int &vy);					// Get size in virtual screen-coords
	void					GetPixelSize		(int &px,int &py);					// Get size in virtual screen-coords
	void					SetSize				(int  vx,int  vy);
	void					Move				(int vrx,int vry);	
	void					GetExtends			(int &vx1,int &vy1,int &vx2,int &vy2);	// Get Extends of view in virtual coords
	void					GetScreenExtends	(int &vx1,int &vy1,int &vx2,int &vy2);	// Get Extends of view in virtual screen-coords
	void					GetPixelExtends		(float &px1,float &py1,float &px2,float &py2);	// Get Extends of view in pixel-coords

	// Info
	void					Top					();									// Show View on Top
	zBOOL					IsIn				(int  x,int  y);					// check, if x/y (virtual screen-coords) are in view
	zCView*					GetItem				(int  x,int  y);
	virtual void zCCFASTCALL GetViewport		(int &xmin,int &ymin,int &xdim,int &ydim) {	xmin = pposx; ymin = pposy; xdim = psizex; ydim = psizey; }; // [HILDEBRANDT] removed legacy values
 
	// Per Frame	
	void					Render				();
	virtual void			Blit				();
	virtual void			DrawItems			();

	// Vars
	zCView*					next;

	// Statics
	static void				ClearKeyBuffer		();
	static void				StdPrintwin			(const zSTRING &s);

	static void				SetMode				(int x,int y,int bpp, zTSystemContextHandle* initContextHandle=0); // [HILDEBANDT] added initContextHandle
	static void				SetNextMode			();
	static void				ChangeMode			();
	
	static void				PrintDebug			(const zSTRING &s);
	static void				SetShowDebug		(zBOOL on);
	static zBOOL			GetShowDebug		();
	static zREAL			GetViewTimePerChar  ()											{ return s_fViewTimePerChar;		};
	static void				SetViewTimePerChar  (const zREAL a_fViewTime)					{ s_fViewTimePerChar = a_fViewTime;	};
	
	// Static vars
	static zCView*			stdoutput;
	static zCView*			modal;				// modales D-Item aktiv ?
	static zBOOL			showDebug;
	static zREAL			s_fViewTimePerChar;

	// ***************
	// MFC -Functions
	// ***************
#ifdef COMPILING_SPACER

	static void				MFC_CreateScreen	(void *adr,int x,int y,int bpp);
	static void				MFC_KeyDown			(int k);
	static void				MFC_KeyUp			(int k);
	static void				MFC_ViewInit		();

#endif

private :
	void					CalcPixelPos		(int& ppx, int &ppy);
	
	void					BlitText			();

	//
	//	CODECHANGE [ROMAN]
	//
	void					Nextline			(const zSTRING& s, zREAL fTime = 0.0f, zCOLOR* col = NULL, int* offsetY = NULL );
	//
	//	CODECHANGE [ROMAN]
	//

	void					CheckAutoScroll		();
	void					PrintChars			(int x,int y,const zSTRING& s);
	zCViewText*				CreateText			(int x,int y,const zSTRING &s);
	zSTRING					GetFirstText		();

	void					MoveAbs				(int x,int y);
	void					GetPosAbs			(int &x,int &y);
	virtual int				GetCode				(int x,int y);

private:	

	zTviewID				viewID;
	int						flags;				// Flags for item 
	int						intflags;			// Internal Flags : VIEW_I_TEXT, VIEW_I_FIXED
	zBOOL					ondesk;				// Flag if in list

	// Render options
	zTRnd_AlphaBlendFunc	alphafunc;
	zCOLOR					color;
	int						alpha;

	// Childs
	zList <zCView>			childs;
	zCView*					owner;
	zCTexture*				backTex;

	// Virtual Coordinates	
	int						vposx,vposy;
	int						vsizex,vsizey;
	// Pixel Coordinates
	int						pposx,pposy;
	int						psizex,psizey;

	// Fonts
	zCFont*					font;	
	zCOLOR					fontColor;
	
	// Printwin
	int						px1,py1,px2,py2;	// Text-Window-Size
	int						winx,winy;			// Position in Text-Win
	zCList <zCViewText>		textLines;			// Text im Textfenster
	zREAL					scrollMaxTime;		// Zeit in der gescrollt wird
	zREAL					scrollTimer;		// Zeitzaehler -> bei Update auf 0

	//
	//	CODECHANGE [ROMAN]
	//
	zTViewFX				fxOpen		 ;
	zTViewFX				fxClose		 ;
	zREAL					timeDialog	 ;		
	zREAL					timeOpen	 ;		// 0 = closed, 1 = open, rest opening or closing
	zREAL					timeClose	 ;
	zREAL					speedOpen	 ;
	zREAL					speedClose	 ;
	zBOOL					isOpen		 ;
	zBOOL					isClosed	 ;
	zBOOL					continueOpen ;
	zBOOL					continueClose;
	zBOOL					removeOnClose;
	zBOOL					resizeOnOpen ;
	int						maxTextLength;
	zSTRING					textMaxLength;
	zVEC2					posCurrent	 [2];
	zVEC2					posOpenClose [2];
	//
	//	CODECHANGE [ROMAN] END
	//
};

// **********************************************************************
// Colors
// **********************************************************************
/*
extern zCOLOR	GFX_WHITE,GFX_YELLOW,GFX_LYELLOW,GFX_GOLD,
				GFX_ORANGE,GFX_DORANGE,GFX_CARROT,
				GFX_RED,GFX_DRED,GFX_PINK,GFX_LPINK,GFX_DPINK,
				GFX_MAGENTA,GFX_ORCHID,GFX_PURPLE,GFX_VIOLET,
				GFX_CYAN,GFX_AQUA,GFX_GREEN,GFX_DGREEN,GFX_PALEGREEN,
				GFX_OLIVE,GFX_BLUE,GFX_LBLUE,GFX_MBLUE,GFX_INDIGO,
				GFX_DBLUE,GFX_SKY,GFX_STEEL,GFX_BROWN,GFX_OCHRE,
				GFX_DOCHRE,GFX_BEIGE,GFX_FLESH,GFX_KHAKI,GFX_GREY,
				GFX_LGREY,GFX_COLDGREY,GFX_WARMGREY,GFX_BLACK,GFX_IVORY;
*/
#ifdef COMPILING_SPACER

void View_Vidlock			();
void View_Vidunlock			();
void View_SetScreenSize		(int x,int y,int bpp);

#endif

#endif