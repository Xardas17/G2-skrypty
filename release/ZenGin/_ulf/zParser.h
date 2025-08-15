/******************************************************************************** 
 
     $Workfile:: zParser.h            $                $Date:: 31.01.01 20:19   $
     $Revision:: 17                   $             $Modtime:: 31.01.01 19:29   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zParser.h $
 * 
 * 17    31.01.01 20:19 Wohlers
 * 
 * 16    9.01.01 17:09 Wohlers
 * 
 * 15    8.01.01 21:16 Wohlers
 * 
 * 14    8.01.01 14:55 Wohlers
 * 
 * 13    4.12.00 18:23 Moos
 * 
 * 12    24.11.00 15:46 Wohlers
 * 
 * 11    16.11.00 14:08 Wohlers
 * 
 * 10    15.11.00 13:13 Wohlers
 * 
 * 9     8.11.00 17:47 Speckels
 * 
 * 8     25.08.00 0:33 Wohlers
 * 
 * 7     23.08.00 13:29 Herget
 * 
 * 6     5.07.00 12:23 Wohlers
 * 
 * 5     22.05.00 18:45 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 4     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 6     29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 4     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 3     11.01.00 23:36 Wohlers
 * 
 * 2     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef _ZPARSER_H_
#define _ZPARSER_H_

#ifndef __ZPARSER_SYMBOL_H__
#include "zParser_Symbol.h"
#endif

#ifndef __ZDISK_H__
#include "zDisk.h"
#endif

#include "zContainer.h"

const int zPAR_INDEX_UNDEF = -1;		// No Instance found.

class zFILE;
class zDATE;
class zCView;
class zCViewProgressBar;
class zCConsole;

class zCPar_TreeNode {
public:
	zCPar_TreeNode								();
	zCPar_TreeNode								(int tok, int val);
	zCPar_TreeNode								(int tok, zSTRING &n, int array=0);
	~zCPar_TreeNode								();
	
	void					SetLeft				(zCPar_TreeNode* l); 
	void					SetRight			(zCPar_TreeNode* r);
	void					SetNext				(zCPar_TreeNode* n);
	
	// Statics
	static zCPar_TreeNode*	MakeDyadicNode		(zCPar_TreeNode *r, int o, zCPar_TreeNode *l);
	static zCPar_TreeNode*	MakeMonadicNode		(int o, zCPar_TreeNode *l);
	static zCPar_TreeNode*	SeekEndTree			(zCPar_TreeNode *n);

	zSTRING					name;
	zBYTE					token;
	union {
		int					value;
		float				fvalue;
	};
	int						info;
	zCPar_TreeNode*			left;
	zCPar_TreeNode*			right;
	zCPar_TreeNode*			next;

private:
	// TMP
	int cNr;
};

class zCPar_File {
	
public :
	zCPar_File									();
	~zCPar_File									();

	zSTRING					GetName				();

	int						Load				(zSTRING &s, zCPar_SymbolTable &symtab, zDATE& modifyDate);
	void					SetFileNumber		(int nr);
	int						GetFileNumber		();

	char*					GetStartAddress		();
	char*					GetEndAddress		();

	void					Dispose				();

	void					SetTree				(zCPar_TreeNode *tree);
	zCPar_TreeNode*			GetTree				();
	
	void					SaveTreeNode		(zFILE *f, zCPar_TreeNode *node);
	void					SaveTree			(int c, zCPar_Symbol *s, zDATE& modifyDate);

	zCPar_TreeNode*			LoadTreeNode		(zFILE *f);
	zBOOL					LoadTree			(zFILE_STATS &dfile_date, zCPar_SymbolTable &symtab);

	void					DeleteTree			();

	void					SetLabelCount		(int anz);
	int						GetLabelCount		();

	void					EnableTreeLoad		(zBOOL on);

private :	
	zBOOL					IsNewerDate			(zDATE &a,zDATE &b);
	zBOOL					IsExactDate			(zDATE &a,zDATE &b);
	
	int						fileid;				// FileNumber
	zSTRING					name;				// Filename
	char*					begin_adr;			// Startadresse der Filedaten 
	int						size;				// Size of File in Bytes
	int						labels;				// Anzahl der Labels in diesem File
	zBOOL					treeload;			// Treeload activated
	zCPar_TreeNode*			tree;
};

class zCParser {
public:
	zCParser									( int nr = 100 );
	~zCParser									( );

	// Fileparsing
	int						Parse				( zSTRING  s );	// Parse a ".SRC" or ".D" - File
	int						ParseSource			( zSTRING &s );
	int						ParseFile			( zSTRING &s );

	// Save / Load Dat-Files
	int						LoadDat				( zSTRING &s );
	int						SaveDat				( zSTRING &s );

	// Special Mode : Merging Files
	int						MergeFile			( zSTRING &s );

	// Error / MessageHandling
	void					SetStopOnError		( zBOOL stop );
	void					SetMessageFunc		( void (*m)(zSTRING s) );
	void					ShowPCodeSpy		( zSTRING &s );
	
	// Debugging
	void					CreatePCode			();
	void					ShowSymbols			();

	void					DefineExternal		( const zSTRING &s, zBOOL (*Proc)(), int type, int param... );
	void					DefineExternalVar	( const zSTRING &s, void *adr, int type, int ele );
	void					GetParameter		( int	&value );
	void					GetParameter		( float &value );
	void					GetParameter		( zSTRING &s );
	void*					GetInstance			( );
	void*					GetInstanceAndIndex ( int&  a_index );
	void					SetReturn			( int   value );
	void					SetReturn			( float value );
	void					SetReturn			( void* adr	);
	void					SetReturn			( zSTRING &s );

	// Execute Pseudo-Code
	void*					CallFunc			( const zSTRING &s );
	void*					CallFunc			( int index, ...   );
	int						GetCurrentFunc		( );

	// Instanzen und Prototypes
	zBOOL					CreateInstance		( zSTRING &s, void *adr );
	zBOOL					CreateInstance		( int index,  void *adr );
	zBOOL					CreatePrototype		( zSTRING &s, void *adr );
	zBOOL					CreatePrototype		( int index,  void *adr );

	// *************************************************************************
	// Info - Functions -> (mostly... Urgh :) Compatible to old Parser Version
	// *************************************************************************

	void					EnableTreeLoad		( zBOOL f );		// Soll nach aktuellen .TRE-Files gesucht werden ? ( Nur bei ".src" )
	void					EnableTreeSave		( zBOOL f );		// Sollen TRE - Files erzeugt werden ?
	void					EnableDatSave		( zBOOL f );		// Soll ein DAT - File geschrieben werden ?

	zBOOL					Error				( );

	int						GetIndex			( const zSTRING &s );
	int						GetBase				( int nr	 );
	int						GetBaseClass		( int nr	 );
	int						GetBaseClass		( zCPar_Symbol *sym );
	int						GetPrototype		( int classid, int pos );
	int						GetInstance			( int classid, int pos );

	zBOOL					MatchClass			( int symbol, const zSTRING &classname );

	zSTRING					GetText				( zSTRING &id,int array = 0 );			// Get a Text of Symbol
	zSTRING					GetText				( int nr,	  int array = 0 );		
	int						GetInt				( int index,  int array = 0 );

	zSTRING					GetInstanceValue	( int  cindex, int nr, void* adr, int array=0 );
	zSTRING					GetInstanceValue	( zSTRING &ci, int nr, void* adr, int array=0 );

	zBOOL					IsValid				( zSTRING &cl, void* adr, zSTRING &p );
	void					Reset				( );
	
	zSTRING					GetSymbolInfo		(int nr,int &typ,int &ele);		// Get Infos of Symbol
	zCPar_Symbol*			GetSymbolInfo		(int nr);
	zCPar_Symbol*			GetSymbol			(int nr);
	zCPar_Symbol*			GetSymbol			(const zSTRING &s);
	zSTRING					GetClassVarInfo		(int c, int nr, int &typ, int &ele);
	void					GetClassVarInfo		(int c, zSTRING &s, int &typ, int &ele);

	zBOOL					CheckClassSize		(  int index, int size );
	zBOOL					CheckClassSize		( zSTRING &s, int size );
	void					AddClassOffset		( zSTRING &s, int size );

	zBOOL					SetInstance			( const zSTRING &s, void* adr );
	zBOOL					SetInstance			( int  index, void* adr );

	// ********************************
	// Percentage
	// ********************************
	
	void					SetProgressBar		(zCViewProgressBar* _progressBar) { progressBar = _progressBar; };
	void					SetPercentDone		(int percent);

	// *************************************************************************
	// File - Info ( Functions for Spacer )
	// *************************************************************************
	
	int						GetNumFiles			();
	zSTRING					GetFileName			(int nr);
	int						GetLastErrorLine	();
	zBOOL					IsStackFull			();
	void					Reparse				(zSTRING &s);
	int						GetNumSymbols		()				{ return symtab.GetNumInList(); };

	void					SetInfoFile			(zCList <zSTRING>* funclist, const zSTRING& infoFileName = "");
	
//	void					CreateAdditionalInfo(zCList <zSTRING> &funclist, zSTRING &f);
	zBOOL					IsInAdditionalInfo	(const zSTRING &s );
	zBOOL					WriteAdditionalInfo (zSTRING &call, int zeile, int filepos);

	zBOOL					AutoCompletion		(zSTRING &s);
	zBOOL					SaveInstance		(zSTRING &s, void* adr);
	zBOOL					SaveInstance		(int index,  void* adr);

	zBOOL					ClearAllInstanceRefs();
	zBOOL					ClearInstanceRefs	(void* instancePtr);
	zBOOL					ResetGlobalVars		();
	zBOOL					SaveGlobalVars		(zCArchiver& arc);
	zBOOL					LoadGlobalVars		(zCArchiver& arc);

	void					CreateVarReferenceList		(const zSTRING& className, zCArray<int>& refList);
	void					ResetWithVarReferenceList	(zCArray<int>& refList, void* ptr);

	// *************************************************************************
	// Statics
	// *************************************************************************
	static void				SetEnableParsing	( zBOOL enable ) { enableParsing = enable;	};
	static zBOOL			GetEnableParsing	( )				 { return enableParsing;	};
	
	static zCParser*		GetParser			( );
	static void				SetVersion			( zBYTE v );
	static zBYTE			GetVersion			( );

	// *************************************************************************
	// Debug
	// *************************************************************************
	void					CloseViews			( );
	void					ShowCode			( int index );

	// *************************************************************************
	// Additional (Spacer + Views)
	// *************************************************************************
	void					SaveInfoFile				( zSTRING s );

private :

	// ********************************
	// Parsing 
	// ********************************
	void					DeclareVar					( zBOOL con );			// Definition of a Var ( Const )
	void					DeclareClass				( );
	void					DeclareInstance				( );
	void					DeclarePrototype			( );
	void					DeclareFunc					( );
	void					DeclareReturn				( );
	void					DeclareAssign				( zSTRING &s );
	void					DeclareAssignFunc			( zSTRING &s );
	void					DeclareFuncCall				( zSTRING &name, int typematch=0 );
	void					DeclareIf					( );
	void					ParseBlock					( );
	
	// ********************************
	// Expressions
	// ********************************
	int						GetNextToken				( );
	zCPar_TreeNode*			ParseExpression				( );
	zCPar_TreeNode*			ParseExpressionEx			( zSTRING &s );
	zCPar_TreeNode*			Parse_Expression			( int &token, int lp = -1 );
	zCPar_TreeNode*			Parse_Expression_Primary	( int &token );
	int						EvalLeaf					( zCPar_TreeNode *node, int lastop = 0 );
	zCPar_TreeNode*			CreateLeaf					( int token, zCPar_TreeNode *in );
	zCPar_TreeNode*			CreateStringLeaf			( );
	zCPar_TreeNode*			CreateFloatLeaf				( );

	int						ReadVarType					( );
	int						ReadFuncType				( );
	int						ReadInt						( );
	float					ReadFloat					( );
	void					ReadString					( zSTRING &s );
	int						ReadArray					( );

	// ********************************
	// Lexer / Scanner
	// ********************************
	void					ReadWord					( zSTRING &w );
	void					PrevWord					( );
	void					Match						( zSTRING &m );
	void					FindNext					( char *ch );

	int						FindIndex					( zSTRING &s );
	int						FindInstanceVar				( zSTRING &s ); 
	int						GetLastInstance				( );
	void					CreateHelpers				( );
	
	// ********************************
	// PseudoCode - Execution
	// ********************************
	int						PopDataValue				( );
	float					PopFloatValue				( );
	int*					PopVarAddress				( );
	zSTRING*				PopString					( );
	void					PushTree					( zCPar_TreeNode* node );
	zCPar_TreeNode*			PushOnStack					( zCPar_TreeNode* node );
	void					DoStack						( int pos );
	void					SolveLabels					( zCPar_TreeNode* node );
	
	// ********************************
	// Error / MessageHandling
	// ********************************
	void					(*msgfunc)					( zSTRING  s );	// Messages from Parser
	void					Error						( zSTRING &s, int l = 0 );
	void					Message						( zSTRING &m );
	
	// ********************************
	// Debugging
	// ********************************
	void					GetNextCommand				(zSTRING &s);
	void					ShowPCode					(int adr, zCView* win, zBOOL red=FALSE);
	void					GetOperatorString			(int token, zSTRING &s); 
	zCPar_Symbol*			SearchFuncWithStartAddress	(int startAddress);
	
	// *** Vars ***
	zCArray <zCPar_File *>	file;						// Liste von eingebundenen Files
	zCPar_SymbolTable		symtab;						// Symboltable 
	zCPar_StringTable		stringtab;					// Alle Strings
	zCPar_Stack				stack;						// Pseudo-Code-Stack
	zCPar_DataStack			datastack;					// ExpressionStack
	zCPar_Symbol*			self;
	zSTRING					fname;						// Current Parsing - Files

	zSTRING					mainfile;
	zBOOL					compiled;
	zBOOL					treesave;
	zBOOL					datsave;		
	zBOOL					parse_changed;				// Wurden einzelne D-Files reparsed ?
	zBOOL					treeload;					// Treeload activated ?
	zBOOL					mergemode;
	int						linkingnr;					// Welches File wird gelinkt ?
	// ********************************
	// Parsing / Counter
	// ********************************
	int						linec;						// Aktuelle Zeile
	int						line_start;					// Filepos der letzten Zeile
	zBOOL					ext_parse;					// Anderer Parsemode : 2 Adr ueberschreibt 1.
	char*					pc_start;					// StartAdresse
	char*					pc,*oldpc;					// Aktuelle Fileposition ( Adresse )
	char*					pc_stop,*oldpc_stop;		// End Of File

	zBOOL					params;						// Parameterleiste abarbeiten
	int						in_funcnr;
	int						in_classnr;
	int						stringcount;				// Anzahl "loser" Strings (ab 10000)
	zCPar_Symbol*			in_func;					// Aktuelle Funktion
	zCPar_Symbol*			in_class;					// Aktuelle Klasse

	// ********************************
	// Error / MessageHandling
	// ********************************
	zBOOL					error;
	zBOOL					stop_on_error;
	int						errorline;

	// ********************************
	// Lexer / Scanner
	// ********************************
	char*					prevword_index[16];
	int						prevline_index[16];
	int						prevword_nr;
	zSTRING					aword;
	int						instance;
	int						instance_help;				// Wird benutzt, um Instanzen zu uebergeben

	// ********************************
	// Percentage
	// ********************************

	zCViewProgressBar*		progressBar;	

	// ********************************
	// Expressions
	// ********************************
	zCPar_TreeNode*			tree;
	zCPar_TreeNode*			treenode;

	// ********************************
	// Debugging
	// ********************************
	zCView*					win_code;
	zBOOL					debugmode;
	int						curfuncnr;		// Aktuelle Funktion	

	// ********************************
	// PseudoCode - Execution
	// ********************************
	int						labelcount;
	int*					labelpos;

	// *************************************************************************
	// Additional Vars -> Desktop - Items
	// *************************************************************************
	zCList <zSTRING>*		add_funclist;
	zSTRING					add_filename;
	zBOOL					add_created;

	// Statics
	static zBOOL			enableParsing;
	static zCParser*		cur_parser;
};

extern zCParser parser;

#endif
