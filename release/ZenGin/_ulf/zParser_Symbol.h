/******************************************************************************** 
 
     $Workfile:: zParser_Symbol.h     $                $Date:: 15.03.01 2:17    $
     $Revision:: 9                    $             $Modtime:: 14.03.01 21:01   $
       $Author:: Hildebrandt                                                    $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zParser_Symbol.h $
 * 
 * 9     15.03.01 2:17 Hildebrandt
 * 
 * 8     4.12.00 18:23 Moos
 * 
 * 7     14.11.00 10:02 Moos
 * 
 * 6     31.10.00 15:11 Moos
 * 
 * 5     11.10.00 10:41 Moos
 * 
 * 4     22.05.00 18:45 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 5     4.04.00 20:06 Wohlers
 * Parser-Class-Offset-Check
 * 
 * 4     29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 3     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 2     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ZPARSER_SYMBOL__
#define __ZPARSER_SYMBOL__

#ifndef __ZCONTAINER_H__
#include "zContainer.h"
#endif

#ifndef __ZLIST_H__
#include "zList.h"
#endif

#ifndef __ZSTRING_H__
#include "zString.h"
#endif

class zFILE;

class zCPar_StringTable {
private :
	zCArray <zSTRING *> array;
public :
	
	zCPar_StringTable							(int nr = 0);
	~zCPar_StringTable							();
	
	zSTRING*					Insert			(zSTRING &s);
	zSTRING*					GetString		(int nr);
	void						Save			(zSTRING &s);
	void						Load			(zSTRING &s);
	void						Show			();
	void						Clear			();
	void						ShrinkToFit		();
	int							GetLastEntry	();
};

class zCPar_Symbol {
public:
	// Methods
	zCPar_Symbol								();
	~zCPar_Symbol								();

	void					SetFlag				(int flag);
	zBOOL					HasFlag				(int flag);
	
	void					SetParent			(zCPar_Symbol *p);
	zCPar_Symbol*			GetParent			();
	zCPar_Symbol*			GetNext				();

	zBOOL					ArrayCheck			(int nr);

	void					SetValue			(int    val, int nr = 0);
	void					SetValue			(float  val, int nr = 0);
	void					SetValue			(zSTRING &s, int nr = 0);
	void					GetValue			(int   &val, int nr = 0);
	void					GetValue			(float &val, int nr = 0);
	void					GetValue			(zSTRING &s, int nr = 0);

	void*					GetDataAdr			(int nr=0);
	void					SetDataAdr			(void *adr);

	void					SetStackPos			(int  val, int nr = 0 );
	void					GetStackPos			(int &val, int nr = 0 );

	void					AllocSpace			();
	
	int						GetOffset			();
	void					SetOffset			(int v);
	void*					GetInstanceAdr		();

	void					Save				(zFILE *f);
	void					Load				(zFILE *f);

	void					SaveFull			(zFILE *f);
	void					LoadFull			(zFILE *f);

	// Only valid for Classes
	int						GetClassOffset		();
	void					SetClassOffset		(int offset);

	// Debug Data
	void					SetLineData			(int  l1, int  l2, int  lpos1, int  lpos2);
	void					GetLineData			(int &l1, int &l2, int &lpos1, int &lpos2);

	void					SetFileNr			(int nr);
	int						GetFileNr			()			{ return filenr; };

	// Static
	static void				SetUseInstance		(zCPar_Symbol *sym);
	static void*			GetUseInstance		();
	static void				SetUseInstanceAdr	(void* adr);

public:
	
	// Members
	zSTRING					name;				// Name of Symbol

	zCPar_Symbol*			next;				// Naechtes Symbol in Einfuege-Reihenfolge

private :
	
	union {
		void*				adr;				// Datenwerte fuer jeweilige Variable
		int*				intdata;
		float*				floatdata;
		zSTRING*			stringdata;
        
        int                 single_intdata;
        float               single_floatdata;
	};

	int						offset;				// Offset bei KlassenVars 
												// Data-Adresse bei Instances												// Return type bei Functions

    // hoffentlich können die folgenden Elemente etwas gepackt werden

public:
	unsigned int    		ele:12;				// Number of Elements
	unsigned int			type:4;				// Type of Elements
	unsigned int			flags:6;			// flags ( CONSTANTS )
	// Temps Debuggen
	zBOOL					space:1;
private:

	// Line and File-Positions
	unsigned int			filenr:19;			// Filenummer
	unsigned int			line:19;			// Linenummer
	unsigned int			line_anz:19;		// Wieviele Zeilen ?
	unsigned int			pos_beg:24;			// Anfangsposition	(Datei -> Bytes)
	unsigned int			pos_anz:24;

	zCPar_Symbol*			parent;				// Parent-Verweis

	static zCPar_Symbol*	instance_sym;
	static void*			instance_adr;
};

class zCPar_SymbolTable {
public :
	zCPar_SymbolTable							(int nr=0);
	~zCPar_SymbolTable							();

	zBOOL					Insert				(zCPar_Symbol *);
	void					InsertEnd			(zCPar_Symbol *);

	int						GetIndex			(zCPar_Symbol *);
	int						GetIndex			(const zSTRING &s);
	int						GetIndex			(const zSTRING &s, int index);
	zBOOL					IsIn				(zCPar_Symbol *);
	zBOOL					IsIn				(const zSTRING &s);

	zCPar_Symbol*			GetSymbol			(const zSTRING &s);
	zCPar_Symbol*			GetSymbol			(int index);

	void					ShrinkToFit			();
	void					Show				();
	
	zCPar_Symbol*			GetLastSymbol		();
	zCPar_Symbol*			GetFirstSymbol		();
	int 					GetNumInList		();

	void					Clear				();
	void					SetSize				(int n);

	void					Save				(zFILE *f);
	void					Load				(zFILE *f);

private :
    // preallocated symbols (Memory Pool)
    zCPar_Symbol           *preAllocatedSymbols;
    int                     nextPreAllocated;
    zCPar_Symbol           *AllocSymbol();    
    void                    PreAlloc(int num);

	int	zCCFASTCALL 		Search				(const zSTRING &s, int ind_low, int ind_high);
	static int				Compare				(const void *a, const void *b);

	zCArray<zCPar_Symbol*>	table;
	zCArraySort<int>		tablesort;
	zCPar_Symbol*			lastsym;
	zCPar_Symbol*			firstsym;

	static zCPar_SymbolTable* cur_table;
};

class zCPar_Stack {
public:
	zCPar_Stack						(int size = 64000);
	~zCPar_Stack					();

	int				GetPopPos		();
	void			SetPopPos		(int p);

	void			PushByte		(zBYTE v);
	void			PushWord		(zWORD w);
	void			PushInt			(int   w);
	void			PushString		(zSTRING &s);

	zBYTE			PopByte			();
	zWORD			PopWord			();
	int				PopInt			();
	void			PopString		(zSTRING &s);

	void			Set				(int pos, int val);

	int				GetDynSize		();
	int				GetStatSize		();

	zBOOL			ReachedEnd		();

	void			Clear			();

	void			Save			(zFILE *f);
	void			Load			(zFILE *f);
private:

	void			CheckOverflow	(int d);

	zBYTE*			stack;						// Stackbeginn
	union {
		zBYTE*		stackptr;					// Aktuelle Pos auf Stack	( Pop  / Read  )
		zWORD*		stackptr_w;
		int*		stackptr_i;
	};
	union {
		zBYTE*		stacklast;					// Aktuelles Ende des Stack	( Push / Write )
		zWORD*		stacklast_w;
		int*		stacklast_i;
	};
	int				stacksize;					// Stackgroesse in Bytes
};

class zCPar_DataStack {
public:
	// [BENDLIN] Addon Patch2 - ParserSymbol DataStack
	enum			{ zMAX_SYM_DATASTACK = 2048 };

public:
	zCPar_DataStack					();
	~zCPar_DataStack				();

	void			Push			(int value);
	int				Pop				();
	float			PopFloat		();
	zBOOL			IsEmpty			();
	void			Clear			();
private:
	int				stack[zMAX_SYM_DATASTACK];
	int				sptr;
};

#endif