/******************************************************************************** 
 
     $Workfile:: zParser_Const.h      $                $Date:: 4.12.00 18:23    $
     $Revision:: 6                    $             $Modtime:: 4.12.00 17:16    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zParser_Const.h $
 * 
 * 6     4.12.00 18:23 Moos
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
 * 3     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 2     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ZPARSER_CONST__
#define __ZPARSER_CONST__

// *************************************************************************
// Parser - Typenkennungen
// *************************************************************************

// [Moos] Warnung: bei Änderungen hier muss die Breite der Bitfelder in zParser_Symbol.h angepasst werden.

enum {	zPAR_TYPE_VOID,		zPAR_TYPE_FLOAT,		zPAR_TYPE_INT, 
		zPAR_TYPE_STRING,	zPAR_TYPE_CLASS,		zPAR_TYPE_FUNC,		
		zPAR_TYPE_PROTOTYPE,zPAR_TYPE_INSTANCE	};
		// Achtung : zPar_Type_Instance muss letzter Eintrag sein

enum {	zPAR_FLAG_CONST		= 1,zPAR_FLAG_RETURN = 2,	zPAR_FLAG_CLASSVAR=4,
		zPAR_FLAG_EXTERNAL	= 8,zPAR_FLAG_MERGED =16 };

// ******************************************************************************
// Operatoren ID's
// ******************************************************************************

enum { // * Operator Length = 1 *
		zPAR_OP_PLUS = 0,	zPAR_OP_MINUS = 1,		zPAR_OP_MUL		= 2,
		zPAR_OP_DIV	 = 3,	zPAR_OP_MOD	  = 4,		zPAR_OP_OR		= 5,	
		zPAR_OP_AND  = 6,	zPAR_OP_LOWER = 7,		zPAR_OP_HIGHER	= 8, 
		zPAR_OP_IS	 = 9,
		// * Operator Length = 2 *
		zPAR_OP_LOG_OR		= 11,		// "||"
		zPAR_OP_LOG_AND		= 12,		// "&&"
		zPAR_OP_SHIFTL		= 13,		// "<<"
		zPAR_OP_SHIFTR		= 14,		// ">>"
		zPAR_OP_LOWER_EQ	= 15,		// "<="
		zPAR_OP_EQUAL		= 16,		// "=="
		zPAR_OP_NOTEQUAL	= 17,		// "!="
		zPAR_OP_HIGHER_EQ	= 18,		// ">="
		zPAR_OP_ISPLUS		= 19,		// "+="
		zPAR_OP_ISMINUS		= 20,		// "-="
		zPAR_OP_ISMUL		= 21,		// "*="
		zPAR_OP_ISDIV		= 22,		// "/="
		// * Unary Operators *
		zPAR_OP_UNARY		= 30,		// ***************************
		zPAR_OP_UN_PLUS		= 30,		
		zPAR_OP_UN_MINUS	= 31,		
		zPAR_OP_UN_NOT		= 32,		// "!"
		zPAR_OP_UN_NEG		= 33,		// "~"
		zPAR_OP_MAX			= 33,			
		// * Weitere Tokens *
		zPAR_TOK_BRACKETON  = 40,
		zPAR_TOK_BRACKETOFF = 41,	
		zPAR_TOK_SEMIKOLON	= 42,
		zPAR_TOK_KOMMA		= 43,
		zPAR_TOK_SCHWEIF	= 44,
		zPAR_TOK_NONE		= 45,
		
		// * Weitere Tokens *
		zPAR_TOK_FLOAT		= 51,
		zPAR_TOK_VAR		= 52,			
		zPAR_TOK_OPERATOR	= 53,
		
		// * Befehls - Tokens *
		zPAR_TOK_RET		= 60,
		zPAR_TOK_CALL		= 61,
		zPAR_TOK_CALLEXTERN	= 62,
		zPAR_TOK_POPINT		= 63,
		zPAR_TOK_PUSHINT	= 64,
		zPAR_TOK_PUSHVAR	= 65,
		zPAR_TOK_PUSHSTR	= 66,
		zPAR_TOK_PUSHINST	= 67,
		zPAR_TOK_PUSHINDEX	= 68,
		zPAR_TOK_POPVAR		= 69,
		zPAR_TOK_ASSIGNSTR	= 70,
		zPAR_TOK_ASSIGNSTRP	= 71,
		zPAR_TOK_ASSIGNFUNC	= 72,
		zPAR_TOK_ASSIGNFLOAT= 73,
		zPAR_TOK_ASSIGNINST = 74,
		zPAR_TOK_JUMP		= 75,
		zPAR_TOK_JUMPF		= 76,
		
		zPAR_TOK_SETINSTANCE= 80,

		// * Parse - Tree - Tokens *
		zPAR_TOK_SKIP		= 90,
		zPAR_TOK_LABEL		= 91,
		zPAR_TOK_FUNC		= 92,
		zPAR_TOK_FUNCEND	= 93,
		zPAR_TOK_CLASS		= 94,
		zPAR_TOK_CLASSEND	= 95,
		zPAR_TOK_INSTANCE	= 96,
		zPAR_TOK_INSTANCEEND= 97,
		zPAR_TOK_NEWSTRING	= 98,

		// !!! Auf jeden Fall unter 128 halten !!!
		zPAR_TOK_FLAGARRAY	= zPAR_TOK_VAR + 128
};

#endif