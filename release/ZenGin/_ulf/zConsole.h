/******************************************************************************** 
 
     $Workfile:: zConsole.h           $                $Date:: 4.12.00 18:23    $
     $Revision:: 7                    $             $Modtime:: 4.12.00 17:25    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zConsole.h $
 * 
 * 7     4.12.00 18:23 Moos
 * 
 * 6     19.10.00 17:15 Keskenti
 * 
 * 5     20.07.00 20:10 Herget
 * 
 * 4     22.05.00 18:44 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 9     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 8     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 6     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 5     21.12.99 20:07 Wohlers
 * 
 * 4     21.12.99 13:57 Wohlers
 * Konsole : GetLastResult
 * 
 * 3     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ZCONSOLE_H__
#define __ZCONSOLE_H__

#ifndef __ZCONTAINER_H__
#include "zContainer.h"
#endif

#ifndef __ZLIST_H__
#include "zList.h"
#endif

#ifndef __ZVIEWBASE_H__
#include "zViewBase.h"
#endif

#ifndef __ZVIEW_H__
#include "zView.h"
#endif

class zCWorld;
class zCParser;
class zCView;

enum { zCON_TYPE_INT, zCON_TYPE_FLOAT, zCON_TYPE_STRING, zCON_TYPE_STRINGP };

const int zCON_MAX_EVAL = 15;

class zCConDat {
public:
	// CODECHANGE [STEFAN]
	zCConDat						(const zSTRING &h, const zSTRING &s, int t, void *adr, int ele = 1);
	// CODECHANGE [STEFAN] END
	zCConDat						(const zSTRING &h, const zSTRING &s, int param);
	
	zSTRING hint;
	zSTRING name;
	int		type;
	void*	adr;
	// CODECHANGE [STEFAN]
	int		ele;
	zBOOL	var;
	// CODECHANGE [STEFAN] END
public:
	zCConDat *next;
};

class zCConsole : public zCInputCallback {
public:

	zCConsole						( );
	zCConsole						( int x, int y, const zSTRING &id );
	~zCConsole						( );

	// CODECHANGE [STEFAN]
	void		InsertVar			( const zSTRING &h, const zSTRING &s, int type, void *adr, int ele = 1 );
	// CODECHANGE [STEFAN] END
	void		Register			( const zSTRING &s, const zSTRING &h, int param );
	void		Register			( const zSTRING &s, const zSTRING &h );	

	void		Hide				( );
	void		Show				( );
	void		Update				( );
	zBOOL		Evaluate			( const zSTRING &s );
	zSTRING		GetLastResult		( ) { return savemsg; };
	zBOOL		AutoCompletion		( zSTRING& s );
	void		Toggle				( );
	zBOOL		IsVisible			( );
	void		SetFocus			( );		// Eingaben explizit zu dieser Konsole leiten.
	void		RemoveFocus			( );		// Eingaben werden nicht mehr an diese Konsole geschickt.

	void		SetPos				( int x1, int y1 );
	void		SetDim				( int sx, int sy );
	void		SetFlags			( int f );
	
	void		AddEvalFunc			( zBOOL (*ev)(const zSTRING &s, zSTRING &msg) );

	void		SetChangedFunc		( void (*cf)(const zSTRING &s) );

	zBOOL		HasAutoCompletion	( );
	void		SetAutoCompletion	( zBOOL f );
	void		SaveInfoFile		( const zSTRING& s );
	void		ShowHelp			( );

	void		SetWorld			( zCWorld *wld );
	zCWorld*	GetWorld			( );

	// Parser spezifische Sachen
	void		SetParser			( zCParser *p );
	zCParser*	GetParser			( );

	zBOOL		EditInstance		(int  index, void* adr);
	zBOOL		EditInstance		(const zSTRING &s, void* adr);

	virtual zBOOL	HandleEvent		(int key);

private :
	static  zCList		<zCConsole> active_consoles;		// Liste der aktiven Konsolen
	static	zCConsole*	cur_console;
	static	zBOOL		EditFunc	(const zSTRING& command, zSTRING& returnMessage);
	
	zSTRING id;
	zSTRING instr;
	zSTRING savemsg;
	zCArray<zSTRING> lastcommand;
	int	    lastCommandPos;

	int px,py;
	int lx,ly;
	int showmax,skip;
	zBOOL dynsize,var;
	zBOOL autocomplete;

	zList <zCConDat>	list;
	zCView *			conview;

	zCConDat*	Get					( const zSTRING& s );
	zCConDat*	GetBestMatch		( const zSTRING& s );

	int			evalcount;
	zBOOL		(*evalfunc[zCON_MAX_EVAL])	( const zSTRING &s, zSTRING &msg );
	void		(*changedfunc)				( const zSTRING &s );
	
	void		AddSkip				( int dir );
	void		AddChar				( int w, zBOOL character=TRUE );
	void		Eval				( const zSTRING &s );

	void		ShowInput			( );

	zCWorld*	world;
	zCParser*	cparser;
	int			edit_index;
	void*		edit_adr;
};

extern zCConsole zcon;

#endif