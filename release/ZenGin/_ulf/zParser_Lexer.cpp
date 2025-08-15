/******************************************************************************** 
 
     $Workfile:: zParser_Lexer.cpp    $                $Date:: 9.01.01 20:22    $
     $Revision:: 19                   $             $Modtime:: 9.01.01 20:06    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zParser_Lexer.cpp $
 * 
 * 19    9.01.01 20:22 Wohlers
 * 
 * 18    29.11.00 18:15 Wohlers
 * 
 * 17    22.11.00 16:48 Wohlers
 * 
 * 16    15.11.00 13:13 Wohlers
 * 
 * 15    7.11.00 2:45 Speckels
 * 
 * 14    17.10.00 13:56 Wohlers
 * 
 * 13    11.10.00 10:41 Moos
 * 
 * 12    22.09.00 18:33 Wohlers
 * 
 * 11    20.09.00 17:21 Wohlers
 * 
 * 10    23.08.00 13:29 Herget
 * 
 * 9     2.08.00 14:25 Wohlers
 * 
 * 8     21.07.00 15:35 Wohlers
 * 
 * 7     21.07.00 14:43 Wohlers
 * 
 * 6     5.06.00 22:37 Wohlers
 * uSrc 05.06.00
 * 
 * 5     22.05.00 18:45 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 7     16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 6     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 5     6.02.00 18:40 Wohlers
 * Konsolen-Instanzen speichern gefixed
 * 
 * 4     4.02.00 15:39 Wohlers
 * Umlaut-Bugfix
 * 
 * 3     11.01.00 23:36 Wohlers
 * 
 * 2     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

#include "zCore.h"

#include "zOption.h"
#include "zParser.h"
#include "zParser_Const.h"
#include "zview.h"
#include "z3d.h"
#include "zVob.h"

/*

  To Do / Fix Me :
  - line_pos eines Objektes : nicht nur aus line_start berechnen, 
    sondern prevword_index nutzen
  * Array-Values nur dann auf den Stack packen, wenn diese > 0 
  - Wenn Konstanten geaendert werden, die dann in einem anderen File benutzt werden,
    werden diese Werte !!!nicht!!! geaendert, weil nur der Zahlenwert in diesem File
	vorhanden ist, nicht der Verweis auf die Konstantenvariable.
*/

// ***************************************************************************************
// PARSER - FEHLERMELDUNGEN
// ***************************************************************************************

zSTRING ParErr_SyntaxError			("Syntax error : ");
zSTRING ParErr_Redefined			("Redefined identifier : ");
zSTRING ParErr_UnknownVar			("Unknown identifier : ");
zSTRING ParErr_OutOfArray			("Array value out of range : ");
zSTRING ParErr_UndefinedFunction	("Undefined function : ");
zSTRING ParErr_NoValidClass			("Not a valid class or prototype name :");
zSTRING ParErr_Expected				("Expected ");

// ***************************************************************************************
// PARSER - OPERATOREN 
// ***************************************************************************************

// Operatoren
zSTRING Operators ("+-*/%|&<>=");							// Operators  1.Buchstaben

// Priorities aus : WATCOM C Language Referende Pg.93
int		Op_Prio 		[23] =								// Operatoren Prioritäten
		{ 10, 10, 11, 11, 11,  4,  6,  8,  8,  0,
		  -1,  2,  3,  9,  9,  8,  7,  7,  8,  0,
		   0,  0,  0 };

// ***********************************************************************
// PARSER - TreeNode - zCPAR_TREENODE
// ***********************************************************************

static int counter = 0;

zCPar_TreeNode :: zCPar_TreeNode	() 
{ 
	token	= 0;
	value	= 0;
	info	= 0;
	left	= NULL;
	right	= NULL;
	next	= NULL;
	cNr		= counter++;
};

zCPar_TreeNode :: zCPar_TreeNode (int tok, int val) 
{
	token	= tok;
	value	= val;
	info	= 0;
	left	= NULL;
	right	= NULL;
	next	= NULL;
	cNr		= counter++;
};

zCPar_TreeNode :: zCPar_TreeNode (int tok, zSTRING &n, int array) 
{
	token	= tok;
	value	= array;
	name	= n;
	info	= 0;
	left	= NULL;
	right	= NULL;
	next	= NULL;
	cNr		= counter++;
};

zCPar_TreeNode :: ~zCPar_TreeNode ()
// delete recursively
{
	delete	(right);	right	= NULL;
	delete	(left);		left	= NULL;
	delete	(next);		next	= NULL;
}

void zCPar_TreeNode :: SetLeft (zCPar_TreeNode* l) 
{ 
	left	= l; 
};

void zCPar_TreeNode :: SetRight (zCPar_TreeNode* r) 
{ 
	right	= r; 
};

void zCPar_TreeNode :: SetNext (zCPar_TreeNode* n)
{
	next	= n;
}

// Static 
zCPar_TreeNode* zCPar_TreeNode :: SeekEndTree	 (zCPar_TreeNode *n)
{
	if (n->next) 
		return SeekEndTree(n->next);
	else 
		return n;
}

zCPar_TreeNode* zCPar_TreeNode :: MakeDyadicNode (zCPar_TreeNode *l, int o, zCPar_TreeNode *r)
// Easy Way to create a Dyadic node out of left, operator, right
//   o
//  / \
// l   r
// returns "o"
{
	zCPar_TreeNode *onode = zNEW( zCPar_TreeNode(o,0) );
	onode->left  = l;
	onode->right = r;
	return onode;
}

// Static 
zCPar_TreeNode* zCPar_TreeNode :: MakeMonadicNode (int o, zCPar_TreeNode *r)
// Easy Way to create a Monadic node out of operator, right
//   o
//    \
//     r
// returns "o"
{
	zCPar_TreeNode *onode = zNEW( zCPar_TreeNode(o,0) );
	onode->right = r;
	return onode;
}

void zCParser :: GetOperatorString(int token, zSTRING &s) 
{
	switch (token) {
		case zPAR_OP_PLUS		: s=" +"; break;
		case zPAR_OP_MINUS		: s=" -"; break;
		case zPAR_OP_MUL		: s=" *"; break;
		case zPAR_OP_DIV		: s=" /"; break;
		case zPAR_OP_MOD		: s=" %"; break;
		case zPAR_OP_OR			: s=" |"; break;
		case zPAR_OP_AND		: s=" &"; break;
		case zPAR_OP_LOWER		: s=" <"; break;
		case zPAR_OP_HIGHER		: s=" >"; break;
		case zPAR_OP_LOG_OR		: s="||"; break;
		case zPAR_OP_LOG_AND	: s="&&"; break;
		case zPAR_OP_SHIFTL		: s="<<"; break;
		case zPAR_OP_SHIFTR		: s=">>"; break;
		case zPAR_OP_LOWER_EQ	: s="<="; break;
		case zPAR_OP_EQUAL		: s="=="; break;
		case zPAR_OP_NOTEQUAL	: s="!="; break;
		case zPAR_OP_HIGHER_EQ	: s=">="; break;
		case zPAR_OP_IS			: s=" ="; break;
		case zPAR_OP_ISPLUS		: s="+="; break;
		case zPAR_OP_ISMINUS	: s="-="; break;
		case zPAR_OP_ISMUL		: s="*="; break;
		case zPAR_OP_ISDIV		: s="/="; break;
		// Unary
		case zPAR_OP_UN_PLUS	: s=" +"; break;
		case zPAR_OP_UN_MINUS	: s=" -"; break;
		case zPAR_OP_UN_NOT		: s=" !"; break;
		case zPAR_OP_UN_NEG		: s=" ~"; break;
		default					: s="??"; break;
	}
} 

// ***************************************************************************************
// PARSER - LEXER FUNCTIONS
// ***************************************************************************************

void zCParser :: FindNext(char *ch)
{
	char *start		= pc;
	char newline	= '\n';
	
	prevword_nr++; prevword_nr &= 15;
	prevword_index[prevword_nr] = pc;
	prevline_index[prevword_nr] = linec;

	pc = strstr(pc,ch);
	// Check for New Lines
	if (pc==NULL) {
		Error(zSTRING("Unexpected End of File."));
		return;
	}
	do {
		start = strchr(start,newline);
		if ((start!=NULL) && (start<=pc)) {
			linec++; start++;
			line_start = (int)start - (int)pc_start;
		}
	} while ((start!=NULL) && (start<=pc));
}

void zCParser :: PrevWord()
{
	pc		= prevword_index[prevword_nr];
	linec	= prevline_index[prevword_nr];
	prevword_nr--; prevword_nr &= 15;
}

void zCParser :: ReadWord(zSTRING &w)
{
	static char trenn	[]		= ";,:=><*+-/?'%()/&!|{}[]\"~"; // [SPECKELS] '~' mit aufgenommen
	static char word	[200];

	unsigned char c;
	int count = 0;

	prevword_nr++; prevword_nr &= 15;
	prevword_index[prevword_nr] = pc;
	prevline_index[prevword_nr] = linec;

	while (pc < pc_stop) {
		c = *pc++;
		
		if (c<=32) {
			if (c=='\n') {
				linec++;
				line_start = (int)pc - (int)pc_start;
				if (count==0) {
					prevword_index[prevword_nr] = pc;
					prevline_index[prevword_nr] = linec;
				}
			}
			if (count>0) break;
		} else {
			if (strrchr(trenn,c)!=NULL) {
				// Trennzeichen
				if (count>0) {
					pc--;
				} else {
					word[count] = c;
					count++;
				}
				break;
			}
			word[count] = c;
			count++;		
		}

	}

	// Kein Wort eingelesen ?
	if ((count==0) && (ext_parse)) {
		ext_parse	= FALSE;
		pc			= oldpc;
		pc_stop		= oldpc_stop;
		ReadWord(w);
		return;
	}

	word[count] = 0;
	w = word;
	w.Upper();

	if (w=="/") {
		if (*pc=='/') {
			// Skip Remark Line
			pc++;
			FindNext("\n");
			pc++;
			ReadWord(w);
		} else if (*pc=='*') {
			// Skip Remark Block
			pc++;
			FindNext("*/");
			pc+=2;
			ReadWord(w);
		}
	}
}

void zCParser :: Match(zSTRING &m)
// The next word has to be matched with m
{
	zSTRING s;
	ReadWord(aword);
	if (aword!=m) Error(ParErr_Expected + "'" + m +"'");
}

// ***************************************************************************************
// PARSER - LEXER SPECIAL FUNCTIONS
// ***************************************************************************************

int zCParser :: ReadVarType()
{
	ReadWord(aword);
	if (aword=="INT")	
		return zPAR_TYPE_INT;	
	else if (aword=="FLOAT")	
		return zPAR_TYPE_FLOAT; 
	else if (aword=="STRING") 
		return zPAR_TYPE_STRING;
	else if (aword=="FUNC")
		return zPAR_TYPE_FUNC;
	else {
		// Search for matching class
		int index		  = symtab.GetIndex (aword);
		zCPar_Symbol *sym = symtab.GetSymbol(index);
		if ((!sym) || (sym->type!=zPAR_TYPE_CLASS)) {
			Error(ParErr_SyntaxError + aword);
			return -1;
		}
		return zPAR_TYPE_INSTANCE + index;
	}
}

int zCParser :: ReadFuncType()
{
	ReadWord(aword);
	if (aword=="VOID") 
		return zPAR_TYPE_VOID;
	else if (aword=="INT")	
		return zPAR_TYPE_INT;	
	else if (aword=="FLOAT")	
		return zPAR_TYPE_FLOAT; 
	else if (aword=="STRING") {
		return zPAR_TYPE_STRING;
	} else {
		// Check for Class !
		zCPar_Symbol *sym	= symtab.GetSymbol(aword);
		if ((sym) && (sym->type==zPAR_TYPE_CLASS)) {
			return zPAR_TYPE_INSTANCE;
		}
		Error(ParErr_SyntaxError + aword);
		return -1;
	}

}

int zCParser :: ReadInt()
// Gültige Int : Zahl
// FIXME :
// Auch zuvor definierte Konstanten
{
	int a;
	zBOOL minus = FALSE;
	ReadWord(aword);
	if ((aword=="-") || (aword=="+")) {
		if (aword=="-") minus = TRUE;
		ReadWord(aword);
	}
	
	if (isdigit(aword[0])) {
		for (int i=1; i<aword.Length(); i++) {
			if (!isdigit(aword[i])) {
				Error("Expected an Integer-Value :"+aword);
				return -1;
			}
		}
		a = aword.ToInt();
	} else {
		// Muss eine Konstante sein.
		int index = FindIndex(aword);
		zCPar_Symbol *sym = symtab.GetSymbol(index);
		if (!sym) {
			Error(ParErr_UnknownVar+aword);
			return -1;
		}
		if ((sym->type!=zPAR_TYPE_INT) || (!sym->HasFlag(zPAR_FLAG_CONST))) {
			Error("Expected integer constant : "+aword);
			return -1;
		}
		sym->GetValue(a);
	}

	if (minus) a = -a;
	return a;
}

float zCParser :: ReadFloat()
// FIXME :
// Auch zuvor definierte Konstanten
{
	float a;
	zSTRING res;
	zBOOL minus = FALSE, point = FALSE, ext = FALSE;	
	ReadWord(aword);
	if ((aword=="-") || (aword=="+")) {
		if (aword=="-") minus = TRUE;
		ReadWord(aword);
	}

	for (int i=0; i<aword.Length(); i++) {
		
		if (isdigit(aword[i])) {
			// Thats ok.
			// Do nothing
		} else if ((aword[i]=='.') && (!point)) {
			point = TRUE;
		} else if ((aword[i]=='E') && (!ext)) {
			ext   = TRUE;
			if (i!=aword.Length()-1) Error(ParErr_SyntaxError + aword);
			break;
		} else {
			Error(ParErr_SyntaxError + aword);
			return -1;
		}
	}
	res = aword;
	if (ext) 
		res += zSTRING(ReadInt());
	a	= res.ToFloat();
	if (minus) a = -a;
	return a;
}

void zCParser :: ReadString( zSTRING &s )
{
	s="";
	Match(zSTRING("\""));
	while (*pc!='\"') {
		s += *pc;
		if (pc < pc_stop) 
			pc++;
		else
			Error(zSTRING("Unexpected End of File."));
	}
	pc++;
}

int zCParser :: ReadArray()
{
	int x = 0;
	zSTRING w;
	ReadWord(w);
	if (w=="[") {
		x = ReadInt();
		Match(zSTRING("]"));
	} else {
		PrevWord();
	}
	return x;
}

// *************************************************************************************
// EXPRESSION - PARSING
// *************************************************************************************

zCPar_TreeNode* zCParser :: CreateLeaf(int token, zCPar_TreeNode *in)
{
	zCPar_TreeNode *node = zNEW( zCPar_TreeNode(token,0) );
	if (in) in->SetNext(node);
	return (node);
}

zCPar_TreeNode* zCParser :: CreateStringLeaf()
{
	zSTRING lookahead;
	zCPar_TreeNode *node = NULL;
	ReadWord(aword);
	if (aword!="\"") {					
		// Funktionsaufruf, oder andere Var ?
		ReadWord(lookahead);
		PrevWord();
		if (lookahead=="(") {
			// Funktionsaufruf
			zCPar_TreeNode* save = treenode;
			node     = treenode = CreateLeaf(zPAR_TOK_SKIP,0);
			DeclareFuncCall(aword,zPAR_TYPE_STRING);
			treenode = save;
		} else {
			node = CreateLeaf(zPAR_TOK_VAR,node);
			node -> name  = aword;
			node -> value = 0;
			node -> info  = zPAR_TYPE_STRING;
		}
	} else {
		PrevWord();
//		int linepos = linec;
//		int lineadr = line_start;

		zSTRING is;
		ReadString(is);
		// Put it as lastentry in Symboltable
//		zCPar_Symbol *sym = new zCPar_Symbol();
//		sym->type = zPAR_TYPE_STRING;
//		sym->ele  = 1;
//		sym->name = zSTRING(char(255)) + zSTRING(stringcount++);
//		sym->SetFlag(zPAR_FLAG_CONST);
		// Create Debug Data
		//sym -> SetLineData(linec,linec - linepos + 1,lineadr);
//		symtab.InsertEnd(sym);
//		sym->SetValue(is);

		//node	=  CreateLeaf(zPAR_TOK_VAR,node);
		//node	-> name  = sym->name;
		node	=  CreateLeaf(zPAR_TOK_NEWSTRING,node);
		node	-> name  = is;
		node	-> value = 0;
		node	-> info	 = zPAR_TYPE_STRING;
	}									
	return node;
}

zCPar_TreeNode* zCParser :: CreateFloatLeaf()
{
	zBOOL minus = FALSE;
	zCPar_TreeNode *node = NULL;
	ReadWord(aword);
	if (aword[0]=='-') {
		minus = TRUE;
		ReadWord(aword);
	} else if (aword[0]=='+') {
		ReadWord(aword);
	}

	if (!isdigit(aword[0])) {					
		if (minus) PrevWord();
		node = CreateLeaf(zPAR_TOK_VAR,node);
		node -> name  = aword;
		node -> value = 0;
		node -> info  = zPAR_TYPE_FLOAT;
	} else {
		if (minus) PrevWord();
		PrevWord();

		zREAL f = ReadFloat();

		node	=  CreateLeaf(zPAR_TOK_FLOAT,node);
		node	-> value = *(int *)&f;
		node	-> info	 = zPAR_TYPE_FLOAT;
	}									
	return node;
}


int zCParser :: GetNextToken ()
{
	int p1;
	zSTRING hlp;
	ReadWord(aword);
	char c = aword[0];

	if ( ((c>='A') && (c<='Z')) || (c=='_') || (c=='#') ) {
		// alpha = Variable / Func
		ReadWord(hlp);
		if (hlp=="(") {
			PrevWord();
			return zPAR_TOK_FUNC;
		}
/*		if ((hlp==".") && (ext_parse)) {
			aword += hlp;
			ReadWord(hlp);
			aword += hlp;
			return zPAR_TOK_VAR;
		}*/
		PrevWord();
		return zPAR_TOK_VAR;

	} else if ((c>='0') && (c<='9')) {
		// num = Zahl
		
		// check....
		for (int i=1; i<aword.Length(); i++) if (!isdigit(aword[i])) Error(ParErr_SyntaxError + aword);		
		return zPAR_TOK_FLOAT;
	}

	if ((p1 = Operators.Search(aword))>=0) {
		// Double Operators ?
		if ((c=='|') && (*pc=='|')) { pc++; return zPAR_OP_LOG_OR;	} 
		else if ((c=='&') && (*pc=='&')) { pc++; return zPAR_OP_LOG_AND; }
		else if (c=='<') {
			if (*pc=='<')	{ pc++; return zPAR_OP_SHIFTL;		};
			if (*pc=='=')	{ pc++; return zPAR_OP_LOWER_EQ;	};
		} else if (c=='>') {
			if (*pc=='>')	{ pc++; return zPAR_OP_SHIFTR;		};
			if (*pc=='=')	{ pc++; return zPAR_OP_HIGHER_EQ;	};
		} else if (*pc=='=') {
			if (c=='=')		{ pc++; return zPAR_OP_EQUAL;		};
			if (c=='+')		{ pc++; return zPAR_OP_ISPLUS;		};
			if (c=='-')		{ pc++; return zPAR_OP_ISMINUS;		};
			if (c=='*')		{ pc++; return zPAR_OP_ISMUL;		};
			if (c=='/')		{ pc++; return zPAR_OP_ISDIV;		};
		} 
		return p1;

	} else {
		// Unary Operators
		if (c=='!') {
			if (*pc=='=') {
				pc++; return zPAR_OP_NOTEQUAL;
			} else
				return zPAR_OP_UN_NOT;
		}
		if (c=='~') return zPAR_OP_UN_NEG;
		// Brackets ?
		if (c=='(') return zPAR_TOK_BRACKETON;
		if (c==')') return zPAR_TOK_BRACKETOFF;
		if (c==';') return zPAR_TOK_SEMIKOLON;
		if (c==',') return zPAR_TOK_KOMMA;
		if (c=='}') return zPAR_TOK_SCHWEIF;
		if (c=='{') return zPAR_TOK_SCHWEIF;
	}
	Error(zSTRING("Syntax Error."));
	return zPAR_TOK_NONE;
}

zCPar_TreeNode* zCParser :: Parse_Expression_Primary(int &token)
// Token is in & output-Symbol
{
	zSTRING name;
	zCPar_TreeNode *node = NULL;

	if (token==zPAR_TOK_FLOAT) {
		// *********************
		// Create Constant leaf
		// *********************
		node	= zNEW( zCPar_TreeNode(token,aword.ToInt()) );
		token	= GetNextToken();

	} else if (token==zPAR_TOK_VAR) {
		name	= aword;
		int array = 0;
		// *******************
		// Variable oder Func
		// *******************
		ReadWord(aword);
		if (aword=="(") { 
			// FUNC 
			ReadWord(aword);
			// FIXME :!!!!!!
		} else if (aword=="[") {
			// Var & Array
			array = ReadInt();
			Match(zSTRING("]"));

		} else
			PrevWord();

		// *********************
		// Create Constant leaf
		// *********************
		node	= zNEW( zCPar_TreeNode(token,name,array) );
		node   -> info = zPAR_TYPE_INT;					// Beim Linken : Test ob INT
		token	= GetNextToken();

	} else if (token==zPAR_TOK_FUNC) {
		// Use the offset Var as return type 
		zCPar_TreeNode* savetree	 = tree;
		zCPar_TreeNode* savetreenode = treenode;
		tree = treenode = zNEW( zCPar_TreeNode( zPAR_TOK_SKIP,0 ) );
		DeclareFuncCall(aword,zPAR_TYPE_INT);
		node	 = tree;
		treenode = savetreenode;
		tree	 = savetree;
		token	 = GetNextToken();

	} else {
		if (token==zPAR_TOK_BRACKETON) {
			// *********************
			// Klammer
			// *********************
			token = GetNextToken();
			node  = Parse_Expression(token);
			if (token!=zPAR_TOK_BRACKETOFF) 
				Error(zSTRING("Missing ')'"));
			else
				token = GetNextToken();
		} else if ((token==zPAR_OP_PLUS) || (token==zPAR_OP_MINUS)) {
			// *********************
			// Vorzeichen
			// *********************
			int op	= token + zPAR_OP_UNARY;		// Unary Version 
			token	= GetNextToken();
			zCPar_TreeNode *primnode = Parse_Expression_Primary(token);
			
			node	= zCPar_TreeNode :: MakeMonadicNode ( op, primnode );
		
		} else if ((token>=zPAR_OP_UNARY) && (token<=zPAR_OP_MAX)) {
			// *********************
			// Unäre Operatoren
			// *********************
			int op	= token;					 
			token	= GetNextToken();
			zCPar_TreeNode *primnode = Parse_Expression_Primary(token);
			
			node	= zCPar_TreeNode :: MakeMonadicNode ( op, primnode );

		} else {			
			// *********************
			// Kein gültiger Node
			// *********************
			Error(ParErr_SyntaxError+aword);
		}
	}
	return node;
}

zCPar_TreeNode* zCParser :: Parse_Expression(int &token, int last_priority)
{
	zCPar_TreeNode *rhs,*lhs;

	lhs	= Parse_Expression_Primary(token);
	
	if (lhs!=NULL) {
	
		zBOOL endexpression = FALSE;

		while ((token<=zPAR_OP_MAX) && (!endexpression)) {

			if (Op_Prio[token] > last_priority) {
				// Dieser Operator hat Vorrang 
				// Dessen Rechte Seite zuerst Parsen
				int op	= token;
				token	= GetNextToken();
				rhs		= Parse_Expression(token, Op_Prio[op]);

				// Bei Zuweisungen muss LeftValue ein gültiger LValue sein.
				if ((op == zPAR_OP_IS) || ((op >= zPAR_OP_ISPLUS) && (op<=zPAR_OP_ISDIV)) ) {
					if (lhs->token!=zPAR_TOK_VAR) {
						Error(zSTRING("Assignment : Left operand is not a lvalue"));
					};
				}

				lhs		= zCPar_TreeNode :: MakeDyadicNode (lhs,op,rhs);

			} else {
				
				endexpression = TRUE;
			}
		}
	}
	return lhs;
}

zCPar_TreeNode* zCParser :: ParseExpressionEx ( zSTRING &s )
{
	// Zuerst den String parsen
	oldpc		= pc;
	oldpc_stop	= pc_stop;
	pc			= s.ToChar();
	pc_stop		= pc + s.Length() + 1;
	ext_parse	= TRUE;

	int token	 = GetNextToken();
	
	// To evaluate 
	return Parse_Expression(token);
}

zCPar_TreeNode* zCParser :: ParseExpression ( )
// Build the Parse-Tree for this Expression
{	
	int token	 = GetNextToken();
	
	// To evaluate 
	return Parse_Expression(token);
}

int zCParser :: EvalLeaf (zCPar_TreeNode *node, int lastop)
{
	int w1,w2;

	if (node->token<=zPAR_OP_MAX) {
		// Unäre Operatoren benutzen nur das rechte Leaf
		if (node->token<zPAR_OP_UNARY) w1 = EvalLeaf(node->left,node->token);
		w2 = EvalLeaf(node->right);

	} else if (node->token==zPAR_TOK_FLOAT) {
		return node->value;
	
	} else if (node->token==zPAR_TOK_VAR) {
		int w;
		zCPar_Symbol *sym = symtab.GetSymbol(FindIndex(node->name));
		if (!sym) Error("Unknown Var '"+node->name+"'.");
		if ((lastop==zPAR_OP_IS) || ((lastop>=zPAR_OP_ISPLUS) && (lastop<=zPAR_OP_ISDIV))) {
			return ((int)sym->GetDataAdr(node->value));
		} else {
			if (sym->HasFlag(zPAR_FLAG_CLASSVAR))
				w = *(int *)sym->GetDataAdr(node->value);
			else
				sym->GetValue(w,node->value);
		}
		return w;

	} else {
		Error(zSTRING("Error in EvalLeaf."));
	}

	// Do Operation
	switch (node->token) {
		case zPAR_OP_PLUS		: w1 += w2; break;
		case zPAR_OP_MINUS		: w1 -= w2; break;
		case zPAR_OP_MUL		: w1 *= w2; break;
		case zPAR_OP_DIV		: w1 /=	w2; break;
		case zPAR_OP_MOD		: w1 %= w2; break;
		case zPAR_OP_OR			: w1 |= w2; break;
		case zPAR_OP_AND		: w1 &=	w2; break;
		case zPAR_OP_LOWER		: w1 =	w1	< w2; break;
		case zPAR_OP_HIGHER		: w1 =	w1	> w2; break;
		case zPAR_OP_LOG_OR		: w1 =	w1 || w2; break;
		case zPAR_OP_LOG_AND	: w1 =  w1 && w2; break;
		case zPAR_OP_SHIFTL		: w1 =  w1 << w2; break;
		case zPAR_OP_SHIFTR		: w1 =  w1 >> w2; break;
		case zPAR_OP_LOWER_EQ	: w1 =	w1 <= w2; break;
		case zPAR_OP_EQUAL		: w1 =	w1 == w2; break;
		case zPAR_OP_NOTEQUAL	: w1 =  w1 != w2; break;
		case zPAR_OP_HIGHER_EQ	: w1 =  w1 >= w2; break;
		case zPAR_OP_IS			: *(int*)w1  = w2; return(*(int*)w1); break;
		case zPAR_OP_ISPLUS		: *(int*)w1 += w2; return(*(int*)w1); break;
		case zPAR_OP_ISMINUS	: *(int*)w1 -= w2; return(*(int*)w1); break;
		case zPAR_OP_ISMUL		: *(int*)w1 *= w2; return(*(int*)w1); break;
		case zPAR_OP_ISDIV		: *(int*)w1 /= w2; return(*(int*)w1); break;

		// Unary
		case zPAR_OP_UN_PLUS	: w1 = +w2;		break;
		case zPAR_OP_UN_MINUS	: w1 = -w2;		break;
		case zPAR_OP_UN_NOT		: w1 = !w2;		break;
		case zPAR_OP_UN_NEG		: w1 = ~w2;		break;
		default					: Error(zSTRING("Code - Error in Tree-Expression !"));
	
	}
//	printf("Result : %d\n",w1);
	return w1;
}

// ****************************************************************************************
// PARSING - SYMBOLS
// ****************************************************************************************

void zCParser :: DeclareVar ( zBOOL con )
{
	zSTRING s;
	int class_index;
	zCPar_TreeNode *node,*node1,*node2;
	zCPar_TreeNode *pnode  = treenode;
	zCPar_Symbol   *parent = NULL;
	
	// Positionen
	int linepos, lineadr;

__nextdecl:
	
	//Read Type
	int type = ReadVarType();
	// Instance Var ?
	if (type>=zPAR_TYPE_INSTANCE) {
		class_index	= type - zPAR_TYPE_INSTANCE;
		parent		= symtab.GetSymbol(class_index);
		type		= zPAR_TYPE_INSTANCE;
	}

__nextvar:

	linepos = linec;
	lineadr	= line_start;
	
	// Read Name
	zSTRING name;
	ReadWord(name);

	// Array ?
	int ele = 1;
	ReadWord(aword);
	if (aword=="[") {
		ele = ReadInt();
        zERR_ASSERT_STRICT(ele < 4096); // [Moos] Element bound
		Match(zSTRING("]"));
	} else
		PrevWord();
	
	// Create Symbol
	zCPar_Symbol* sym = zNEW( zCPar_Symbol() );
	sym -> name = name;
	sym -> type = type;
	sym	-> ele  = ele;
	sym -> SetParent (parent);
	if (con) sym->SetFlag(zPAR_FLAG_CONST);

	// Add Name, if is Func or a Class
	if (in_func) {
		sym -> name = in_func->name + "." + sym -> name;
		if (params) {
			// Function Parameter
            zERR_ASSERT_STRICT(in_func->ele < 4095); // [Moos] Element bound
			in_func->ele ++;		
			// Create PCode - Var
			// "Verkehrtes" Poppen vom Stack
			if (sym->type == zPAR_TYPE_INT) {					
				node1 =  zNEW( zCPar_TreeNode(zPAR_TOK_VAR,0) );
				node1 -> name	= sym->name;
				node1 -> value	= 0;
				node1 -> info	= zPAR_TYPE_INT;
				node2 =  zNEW( zCPar_TreeNode(zPAR_OP_IS,0) );
				node1 -> SetNext(node2);
				node2 -> SetNext(pnode->next);
				pnode -> SetNext(node1);			
				if (in_func->ele==1) treenode = node2;
			
			} else if (sym->type == zPAR_TYPE_STRING) {
				node1 =  zNEW( zCPar_TreeNode(zPAR_TOK_VAR,0) );
				node1 -> name	= sym->name;
				node1 -> value	= 0;
				node1 -> info   = zPAR_TYPE_STRING;
				node2 =  zNEW( zCPar_TreeNode(zPAR_TOK_ASSIGNSTR,0) );
				node1 -> SetNext(node2);
				node2 -> SetNext(pnode->next);
				pnode -> SetNext(node1);			
				if (in_func->ele==1) treenode = node2;

			} else if (sym->type == zPAR_TYPE_INSTANCE) {
				node1 =  zNEW( zCPar_TreeNode(zPAR_TOK_PUSHINST,0) );
				node1 -> name	= sym->name;
				node1 -> value	= class_index;				// Class-Index of Instance
				node1 -> info   = zPAR_TYPE_INSTANCE;
				node2 =  zNEW( zCPar_TreeNode(zPAR_TOK_ASSIGNINST,0) );
				node1 -> SetNext(node2);
				node2 -> SetNext(pnode->next);
				pnode -> SetNext(node1);			
				if (in_func->ele==1) treenode = node2;
			
			} else if (sym->type == zPAR_TYPE_FLOAT) {					
				node1 =  zNEW( zCPar_TreeNode(zPAR_TOK_VAR,0) );
				node1 -> name	= sym->name;
				node1 -> value	= 0;
				node1 -> info	= zPAR_TYPE_FLOAT;
				node2 =  zNEW( zCPar_TreeNode(zPAR_TOK_ASSIGNFLOAT,0) );
				node1 -> SetNext(node2);
				node2 -> SetNext(pnode->next);
				pnode -> SetNext(node1);			
				if (in_func->ele==1) treenode = node2;

			} else if (sym->type == zPAR_TYPE_FUNC) {
				node1 =  zNEW( zCPar_TreeNode(zPAR_TOK_VAR,0) );
				node1 -> name  = sym->name;
				node1 -> value = 0;
				node1 -> info  = zPAR_TYPE_FUNC;
				
				node2 =  zNEW( zCPar_TreeNode(zPAR_TOK_ASSIGNFUNC,0) );
				node1 -> SetNext(node2);
				node2 -> SetNext(pnode->next);
				pnode -> SetNext(node1);			
				if (in_func->ele==1) treenode = node2;

			} else {
				Error(zSTRING("Parameters of this type are not supported."));
			}
		}

	} else if (in_class) {
		sym -> name = in_class->name + "." + sym -> name;
		if (params) {
			in_class -> ele++;
			sym		 -> SetParent(in_class);
			sym		 -> SetFlag	 (zPAR_FLAG_CLASSVAR);
		}
	}

	// Insert
	if (!symtab.Insert(sym)) Error(ParErr_Redefined + sym->name);

	// Konstante ?, dann hier definieren :
	if (con) {
		Match(zSTRING("="));
		if (ele>1) Match(zSTRING("{"));
		for (int i=0; i<ele; i++) {		
			switch (type) {
				case zPAR_TYPE_INT		:	node = ParseExpression();
											sym->SetValue(EvalLeaf(node),i);
											PrevWord();
											break;
				case zPAR_TYPE_FLOAT	:	sym->SetValue(ReadFloat(),i);
											break;
				case zPAR_TYPE_STRING	:	ReadString(s);
											// und die Symboltabelle
											sym -> SetValue(s,i);
											break;
				case zPAR_TYPE_FUNC		:	{
												ReadWord(aword);
												int funcIndex = GetIndex(aword);
												if (funcIndex<0) Error(ParErr_UnknownVar+aword);
												sym -> type = zPAR_TYPE_INT;
												sym -> SetValue(funcIndex,i);
												sym -> type = zPAR_TYPE_FUNC;
											}
											break;
			}
			// Kommas, wenn noch einer folgt
			if (i+1!=ele) Match(zSTRING(","));
		}
		if (ele>1) Match(zSTRING("}"));
		// Konstante Func-Vars werden als CONST INT weiterbehandelt.
		if (type == zPAR_TYPE_FUNC) sym->type = zPAR_TYPE_INT;
	}

	// Create Debug-Data
	sym -> SetLineData(linepos,linec - linepos + 1,lineadr,((int)pc - (int)pc_start) - lineadr + 3);
	sym -> SetFileNr  (file.GetNumInList()-1);

	// Kommt noch was ?
	ReadWord(aword);
	if (aword==",") {
		if (in_func) {
			Match(zSTRING("VAR"));
			goto __nextdecl;
		} else
			goto __nextvar;
	}
	PrevWord();
	//	if (aword!=";") Error(zSTRING("Expected : ';'"));
};



void zCParser :: DeclareClass ()
{

	int linepos = linec;
	int lineadr = line_start;

	//Read Name
	zSTRING name;
	ReadWord(name);

	params = TRUE;
	// Create Symbol
	in_class =  zNEW( zCPar_Symbol() );
	in_class -> name = name;
	in_class -> type = zPAR_TYPE_CLASS;
	in_class -> ele  = 0;	

	// Insert
	if (!symtab.Insert(in_class)) Error(ParErr_Redefined + in_class->name);
	
	ParseBlock();
	
	// Create Debug-Data
	// +3, weil ParseBlock nur bis zur geschlossenen Klammer berücksichtigt.
	// Dazu kommen noch : Semikolon + 0x0d + 0x0a
	in_class -> SetLineData(linepos,linec - linepos + 1,lineadr,((int)pc - (int)pc_start) - lineadr + 3);
	in_class -> SetFileNr  (file.GetNumInList()-1);
	
	in_class	= NULL;
	in_classnr	= 0;

	params		= FALSE;
}

void zCParser :: DeclareInstance()
{
	zCArray <zSTRING>		names;
	zCArray <zCPar_Symbol*>	syms;
	zCPar_Symbol *lastsym,*sym;

	int linepos = linec;
	int lineadr = line_start;

	//Read Name
	zSTRING name;

	do {
		ReadWord(name);
		if (isdigit(name[0])) Error(zSTRING("Syntax Error. First letter is a digit. Tnstancename : ")+name);
		names.Insert(name);

		ReadWord(aword);
	} while (aword==",");

	PrevWord();
	Match(zSTRING("("));

	// Read Class or Prototype
	ReadWord(aword);
	zCPar_Symbol *parent = symtab.GetSymbol(aword);
	if ((!parent) || ((parent->type!=zPAR_TYPE_CLASS) && (parent->type!=zPAR_TYPE_PROTOTYPE))) {
		Error(ParErr_NoValidClass + aword);
		return;
	}

	Match(zSTRING(")"));

	in_class		= parent;
	if (in_class->type == zPAR_TYPE_PROTOTYPE) 
		in_class = in_class -> GetParent();

	lastsym = symtab.GetLastSymbol();
	for (int i=0; i<names.GetNumInList(); i++) {
		// Create Symbol
		in_func			= zNEW( zCPar_Symbol() );
		in_func -> name	= names[i];
		in_func -> type	= zPAR_TYPE_INSTANCE;
		in_func -> ele	= 0;
		in_func -> SetParent(parent);
		//in_func -> SetFlag (zPAR_FLAG_CONST);
		// Insert
		if (!symtab.Insert(in_func)) {
			// Bereits vorhanden
			if (mergemode) {
				delete(in_func);
				in_func = symtab.GetSymbol(names[i]);
				if ((in_func) && (in_func->type==zPAR_TYPE_INSTANCE)) {
					in_func -> SetFlag(zPAR_FLAG_MERGED);
				} else {
					Error(ParErr_Redefined + in_func->name);
					return;
				}

			} else {
				Error(ParErr_Redefined + in_func->name);
				return;
			}
		}
	
		syms.Insert(in_func);
		treenode = CreateLeaf(zPAR_TOK_INSTANCE,treenode);
		treenode -> name = names[i];
	}

//	zCPar_TreeNode* oldnode = treenode;

	ReadWord(aword);
	PrevWord();
	if (aword!=";") {
		ParseBlock();
		in_func -> SetFlag(zPAR_FLAG_CONST);	
	}

	// Create Debug-Data
	for (i=0; i<syms.GetNumInList(); i++) {
		sym  = syms[i];
		sym -> SetLineData(linepos,linec - linepos + 1,lineadr, ((int)pc - (int)pc_start) - lineadr + 3);
		sym -> SetFileNr  (file.GetNumInList()-1);
	}

	in_func		= NULL;
	in_class	= NULL;
	in_classnr	= 0;	
	
	// FIXME : Return sparen, wenns nur eine Definition ist und kein PCODE erzeugt wurde
	treenode = CreateLeaf(zPAR_TOK_RET,treenode);
	treenode = CreateLeaf(zPAR_TOK_INSTANCEEND,treenode);
}

void zCParser :: DeclarePrototype()
{
	int linepos = linec;
	int lineadr = line_start;
	
	//Read Name
	zSTRING name;
	ReadWord(name);
	if (isdigit(name[0])) Error(zSTRING("Syntax Error. First letter is a digit in prototypename."));

	Match(zSTRING("("));

	// Read Class or Prototype
	// FIXME : Prototype Handling
	ReadWord(aword);
	zCPar_Symbol *parent = symtab.GetSymbol(aword);
	if ((!parent) || (parent->type!=zPAR_TYPE_CLASS)) {
		Error(ParErr_NoValidClass + aword);
		return;
	}

	// Create Symbol
	in_func			= zNEW( zCPar_Symbol() );
	in_func -> name	= name;
	in_func -> type	= zPAR_TYPE_PROTOTYPE;
	in_func -> ele	= 0;
	in_func -> SetParent(parent);	

	in_class		= parent;

	// Insert
	if (!symtab.Insert(in_func)) Error(ParErr_Redefined + in_func->name);
	
	Match(zSTRING(")"));

	treenode = CreateLeaf(zPAR_TOK_INSTANCE,treenode);
	treenode -> name = name;

	ParseBlock();
	
	// Create Debug-Data
	in_func -> SetLineData(linepos,linec - linepos + 1,lineadr, ((int)pc - (int)pc_start) - lineadr + 3);
	in_func -> SetFileNr  (file.GetNumInList()-1);

	in_func		= NULL;
	in_class	= NULL;
	in_classnr	= 0;	
	
	treenode = CreateLeaf(zPAR_TOK_RET,treenode);
	treenode = CreateLeaf(zPAR_TOK_INSTANCEEND,treenode);
}

void zCParser :: DeclareIf()
{
	int jumpoutlabel = -1;
	int lastif;

	do {
		treenode -> SetNext(ParseExpression());
		while (treenode->next) treenode = treenode -> next;
		treenode  = CreateLeaf(zPAR_TOK_JUMPF,treenode);
		treenode -> value = lastif = labelcount;
		labelcount++;
		
		PrevWord();
		ParseBlock();

		ReadWord(aword);
		if (aword=="ELSE") {
			if (jumpoutlabel<0) {
				jumpoutlabel = labelcount;
				labelcount++;
			}
			treenode = CreateLeaf(zPAR_TOK_JUMP,treenode);
			treenode -> value = jumpoutlabel;
			// Weiteres If ? oder nur ausklingendes else ?
			ReadWord(aword);
			if (aword=="{") {
				// Jump False Label fuer vorhergehendes if
				treenode  = CreateLeaf(zPAR_TOK_LABEL,treenode);
				treenode -> value = lastif;
				
				PrevWord();
				ParseBlock();
				ReadWord(aword);
				if (aword!=";") Error(ParErr_Expected + zSTRING("';'") );
				break;

			} else {
				PrevWord();
				Match(zSTRING("IF"));
			}
		}
		// Jump False Label fuer vorhergehendes if
		treenode  = CreateLeaf(zPAR_TOK_LABEL,treenode);
		treenode -> value = lastif;

	} while (aword!=";");
	//JumpOutLabel -> Nur noetig, wenn ein ELSE benutzt wurde
	if (jumpoutlabel>=0) {
		treenode  = CreateLeaf(zPAR_TOK_LABEL,treenode);
		treenode -> value = jumpoutlabel;
	}
	PrevWord();
}

void zCParser :: DeclareAssign(zSTRING &s)
{
	// Get Symbol
	zSTRING name = s;
	int index = FindIndex(s);
	if (index<0) {
		Error(ParErr_UnknownVar+s);
		return;
	}

	zCPar_Symbol *sym = symtab.GetSymbol(index);

	if (sym->type==zPAR_TYPE_INT) {
		PrevWord();
		// NEW
		treenode -> SetNext (ParseExpression());
		treenode  = treenode -> next;
		PrevWord();
		return;
	} else if (sym->type==zPAR_TYPE_FLOAT) {
		
		int array = ReadArray();
		Match(zSTRING("="));
		
		// Function Call ?
		ReadWord(aword);
		zCPar_Symbol* sym = GetSymbol(aword);

		// Is it a func ?
		if (sym && (sym->type==zPAR_TYPE_FUNC)) {
			DeclareFuncCall(aword,zPAR_TYPE_FLOAT);
			treenode  = CreateLeaf(zPAR_TOK_VAR,treenode);
			treenode -> name  = name;
			treenode -> value = array;
			treenode -> info  = zPAR_TYPE_FLOAT;
			treenode  = CreateLeaf(zPAR_TOK_ASSIGNFLOAT,treenode);			
		} else {

			PrevWord();
			//	Original - working
			treenode  = CreateLeaf(zPAR_TOK_FLOAT,treenode);
			treenode -> fvalue = ReadFloat();		
			treenode  = CreateLeaf(zPAR_TOK_VAR,treenode);
			treenode -> name  = name;
			treenode -> value = array;
			treenode -> info  = zPAR_TYPE_FLOAT;
			treenode  = CreateLeaf(zPAR_TOK_ASSIGNFLOAT,treenode);
		};
		return;

	} else if (sym->type==zPAR_TYPE_STRING) {
		// Assign String
		int array  = ReadArray();
		Match(zSTRING("="));
		
		treenode  -> SetNext( CreateStringLeaf() );
		while (treenode->next) treenode = treenode -> next;

		treenode	= CreateLeaf(zPAR_TOK_VAR,treenode);
		treenode   -> name  = name;
//		treenode   -> name  = s;
		treenode   -> value = array;
		treenode   -> info  = zPAR_TYPE_STRING;
		treenode	= CreateLeaf(zPAR_TOK_ASSIGNSTR,treenode);
		return;
	
	} else if (sym->type==zPAR_TYPE_FUNC) {
		
		if (sym->HasFlag(zPAR_FLAG_CONST))
			// Aufruf
			DeclareFuncCall(name);
		else {
			// Zuweisen
			DeclareAssignFunc(name);
		}
	
	} else if (sym->type==zPAR_TYPE_INSTANCE) {
		// Instanzen zuweisen
		// Nur aus Funktionen erlauben
		Match(zSTRING("="));
		ReadWord(aword);
		DeclareFuncCall(aword,zPAR_TYPE_INSTANCE);
		
		treenode	= CreateLeaf(zPAR_TOK_PUSHINST,treenode);
		treenode   -> name  = s;
		treenode   -> info  = zPAR_TYPE_INSTANCE;
		treenode	= CreateLeaf(zPAR_TOK_ASSIGNINST,treenode);
	}
}

void zCParser :: DeclareAssignFunc(zSTRING &s)
{
	// Assign String
	int array  = ReadArray();
	Match(zSTRING("="));

	ReadWord(aword);
	treenode	= CreateLeaf(zPAR_TOK_PUSHINDEX,treenode);
	treenode   -> name	= aword;
	//treenode   -> info	= zPAR_TYPE_FUNC;

	treenode	= CreateLeaf(zPAR_TOK_VAR,treenode);
	treenode   -> name  = s;
	treenode   -> value = array;
	treenode   -> info  = zPAR_TYPE_FUNC;
	
	treenode	= CreateLeaf(zPAR_TOK_ASSIGNFUNC,treenode);
	return;	
}

void zCParser :: DeclareFunc()
{
	int linepos = linec;
	int lineadr = line_start;
	
	// Get Return Typ
	int type = ReadFuncType();

	// Get Name
	zSTRING name;
	ReadWord(name);

	// Create Func-Symbol
	zCPar_Symbol* sym = zNEW( zCPar_Symbol() );
	sym -> name = name;
	sym -> type = zPAR_TYPE_FUNC;
	sym	-> ele  = 0;
	sym -> SetFlag (zPAR_FLAG_CONST);

	// Insert
	if (!symtab.Insert(sym)) Error(ParErr_Redefined + sym->name);
	in_func		= sym;
//	in_funcnr	= symtab.GetLastEntry();

	// Set Label in Parse - Tree
	treenode = CreateLeaf (zPAR_TOK_FUNC,treenode);
	treenode -> name = name;

	// Create Return-Symbol
	if (type!=zPAR_TYPE_VOID) {
		// Create Func-Symbol
		sym -> SetFlag(zPAR_FLAG_RETURN);
	}
	// Use the offset Var as return type 
	sym -> SetOffset(type);

	Match(zSTRING("("));
	
	// Any Parameter ?
	ReadWord(aword);
	if (aword=="VAR") {
		params = TRUE;
		DeclareVar(FALSE);
		params = FALSE;
		Match(zSTRING(")"));
	} else if (aword!=")") {
		Error(zSTRING("Expected ')'"));
		return;
	}

	ParseBlock();

	sym -> SetLineData(linepos,linec - linepos + 1,lineadr, ((int)pc - (int)pc_start) - lineadr + 3);
	sym -> SetFileNr  (file.GetNumInList()-1);

	in_func		= NULL;
	in_funcnr	= 0;
	// Set Label in Parse - Tree
	treenode = CreateLeaf (zPAR_TOK_FUNCEND,treenode);
}

void zCParser :: DeclareReturn ()
{
	if (!in_func) {
		Error(zSTRING("Unexpected 'return'"));
		return;
	}
		
	if (in_func->HasFlag(zPAR_FLAG_RETURN)) {
		switch (in_func->GetOffset()) {
			case zPAR_TYPE_INT	:	treenode -> SetNext( ParseExpression() );
									treenode =  zCPar_TreeNode :: SeekEndTree(treenode);					
									PrevWord();
									break;
			case zPAR_TYPE_STRING:	treenode -> SetNext( CreateStringLeaf() );
									while (treenode->next) treenode = treenode -> next;
									break;
		}
	}
	treenode = CreateLeaf(zPAR_TOK_RET,treenode);
}

void zCParser :: DeclareFuncCall(zSTRING &name, int typematch)
// FIXME : Forward Deklarations for Functions
// FIXME : Muss hier unbedingt das Symbol ermittelt werden ?
// FIXME : Arrays als Parameter enablen -> Init derselben
{
//	zCPar_TreeNode *firstnode = NULL,*node = NULL;	
	zCPar_Symbol *par;
	zCPar_Symbol *sym = symtab.GetSymbol(name);

	if (!sym) {
		Error(ParErr_UndefinedFunction + name);
		return;
	}

	// Type Matching ?
	if ((typematch>0) && (sym->GetOffset()!=typematch)) {
		zSTRING err = "Func does not return a";
		switch(typematch) {
			case zPAR_TYPE_INT		:	err+="n int";	break;
			case zPAR_TYPE_FLOAT	:	err+=" float";	break;
			case zPAR_TYPE_STRING	:	err+=" string";	break;
			case zPAR_TYPE_INSTANCE	:	err+="n instance"; break;
		}
		Error(err);
		return;	
	}			
	par = sym;

	// Für die AdditionalInfo (Spacer) hier Zeile merken
	zBOOL addinfo = FALSE;
	int  line_1,line_nr;
	if (IsInAdditionalInfo(sym->name)) {
		addinfo		= TRUE;
		line_1		= line_start;
		line_nr		= linec;
	};

	Match(zSTRING("("));
	zSTRING w;
	for (int i=0; i<sym->ele; i++) {
		// Naechsten Parameter holen
		par = par->GetNext();
		switch(par->type) {
			case zPAR_TYPE_INT	:	// Cut Name										
									treenode -> SetNext(ParseExpression());
									while (treenode->next) treenode = treenode -> next;
									PrevWord();
									break;
			case zPAR_TYPE_FLOAT:	treenode -> SetNext(CreateFloatLeaf());
									treenode = treenode->next;
									break;
			case zPAR_TYPE_STRING:	treenode -> SetNext(CreateStringLeaf());
									while (treenode->next) treenode = treenode -> next;
									break;
			case zPAR_TYPE_INSTANCE:ReadWord(aword);
									treenode = CreateLeaf(zPAR_TOK_PUSHINST,treenode);
									// FIXME : Error Checking
									if ((aword=="SELF") && (in_func->type==zPAR_TYPE_INSTANCE)) {
										treenode -> name	= in_func -> name;
										treenode -> value	= GetBaseClass(in_func);
									
									} else {
										treenode -> name	= aword;
										treenode -> value	= GetBaseClass(par);
									}
									treenode -> info  = zPAR_TYPE_INSTANCE;
									break;
			case zPAR_TYPE_FUNC	:	ReadWord(aword);
									if (aword=="NOFUNC") {
										// Leave Function Parameter Empty
										treenode =  CreateLeaf(zPAR_TOK_FLOAT,treenode);
										treenode -> value = -1;
									} else {					
										treenode	= CreateLeaf(zPAR_TOK_PUSHINDEX,treenode);
										treenode   -> name	= aword;
									}
									break;
			default				:	Error(zSTRING("Parameters of this type not currently supported."));
									return;
		}
		if (i+1!=sym->ele) Match(zSTRING(","));
	}
	Match(zSTRING(")"));
//	ReadWord(aword);
	
	treenode = CreateLeaf(zPAR_TOK_CALL,treenode);
	treenode -> name = sym->name;

	// Create AddInfo ? (Spacer)
	if (addinfo) {
		// pc+1 = lineend
		zSTRING s;
		char *i = pc_start + line_1;
		zBYTE c = zBYTE(*i);
		while ((c!='\n') && (i<pc_stop)) {
			// Nur Tabs durchlassen
			if ((c>=32) || (c==9)) {
				s += char(c);
			}
			i++;
			c = zBYTE(*i);
		}
		WriteAdditionalInfo(s,line_nr,line_1);
	};
}

zCPar_Symbol* zCParser :: SearchFuncWithStartAddress(int startAddress)
{
	zCPar_Symbol* sym = NULL;
	for (int i=0; i<symtab.GetNumInList(); i++) {
		sym = symtab.GetSymbol(i);
		if ((sym->type==zPAR_TYPE_FUNC) || (sym->type==zPAR_TYPE_PROTOTYPE)) {
			int pos = 0;
			sym->GetStackPos(pos);
			if (pos==startAddress) return sym;
		}
	}
	return NULL;
};

void zCParser :: GetNextCommand (zSTRING &s)
{
	s = "";

	zSTRING op;
	zCPar_Symbol* sym;
	int v,array;
	int adr = stack.GetPopPos();
	s += zSTRING(adr)+".";
	v = stack.PopByte();
	if (v<=zPAR_OP_MAX) {
		GetOperatorString(v,op);
		s+="Op " + op;

	} else if (v==zPAR_TOK_PUSHINT) {
		s+="Push " + zSTRING(stack.PopInt());
	
	} else if (v==(zPAR_TOK_PUSHVAR + zPAR_TOK_FLAGARRAY)) {
		sym   = symtab.GetSymbol(stack.PopInt());
		array = stack.PopByte();
		s+="Push " + sym->name + "[" + zSTRING(array) + "]";
	} else if (v==zPAR_TOK_PUSHVAR) {
		sym   = symtab.GetSymbol(stack.PopInt());
		s+="Push " + sym->name + "                 ";
		// Inhalt
		if (sym->type == zPAR_TYPE_INT) {
			int vInt = 0;
			sym->GetValue(vInt);
			s += "("+zSTRING(vInt)+")";
		} else if (sym->type == zPAR_TYPE_FLOAT) {
			zREAL vFloat = 0.0f;
			sym->GetValue(vFloat);
			s += "("+zSTRING(vFloat)+")";			
		} else if (sym->type == zPAR_TYPE_STRING) {
			zSTRING vString;
			if (sym->HasFlag(zPAR_FLAG_CLASSVAR))	vString = sym->name;
			else									sym->GetValue(vString);
			s += "("+vString+")";			
		}
	} else if (v==zPAR_TOK_RET) {			
		s+="Ret";
	} else if (v==zPAR_TOK_POPINT) {			
		s+="Pop";
	} else if (v==zPAR_TOK_CALLEXTERN) {			
//		s+="Call External " + zSTRING(stack.PopInt());
		s+="Call External "; // + zSTRING(stack.PopInt());
		int nr = stack.PopInt();
		zCPar_Symbol* sym = GetSymbol(nr);
		if (sym) s+=sym->name;

	} else if (v==zPAR_TOK_CALL) {			
		s+="Call ";
		int nr = stack.PopInt();
		zCPar_Symbol* sym = SearchFuncWithStartAddress(nr);
		if (sym) s+=sym->name;
		// + zSTRING(stack.PopInt());

	} else if (v==zPAR_TOK_ASSIGNSTR) {
		s+="String =";
	} else if (v==zPAR_TOK_ASSIGNSTRP) {
		s+="String =";
	} else if (v==zPAR_TOK_ASSIGNFUNC) {
		s+="Func =";
	} else if (v==zPAR_TOK_JUMP) {
		s+="Jump " + zSTRING(stack.PopInt());
	} else if (v==zPAR_TOK_JUMPF) {
		s+="Jumpf " + zSTRING(stack.PopInt());
	} else if (v==zPAR_TOK_SETINSTANCE) {
		sym		= symtab.GetSymbol(stack.PopInt());
		s+="Set In : " + sym->name;
	} else if (v==zPAR_TOK_PUSHINST) {
//		s+="Push Inst: " + zSTRING(stack.PopInt());
	
		s+="Push Inst: ";// + zSTRING(stack.PopInt());
		int nr = stack.PopInt();
		zCPar_Symbol* sym = GetSymbol(nr);
		if (sym) s+=sym->name;		
	
	} else if (v==zPAR_TOK_ASSIGNINST) {
		s+="Instance =";
	} else if (v==zPAR_TOK_ASSIGNFLOAT) {
		s+="Float =";
	} else {	
		s+="??";
	}	
}

void zCParser :: ShowPCodeSpy (zSTRING &s)
{
	int lines = 0, maxlines = 40;
	zCPar_Symbol *sym = GetSymbol(s);
	if (!sym) return;
	
	int adr;
	sym->GetStackPos(adr);
	stack.SetPopPos (adr);

	printf("U:PAR: * PSEUDO - CODE *");
	while (stack.GetPopPos() < stack.GetDynSize()) {
		GetNextCommand(s);
		zerr.Message("U:PAR: "+s);
		lines++;
		if (lines>=maxlines) break;
	}
}

void zCParser :: ShowPCode (int adr, zCView* win_code, zBOOL instack)
{
	zSTRING s;
//	int i = 0;
	int lines = 0;
	int maxlines = 8191 / win_code->FontY();
//	printf("\n* PSEUDO - CODE *\n");
//	printf("Size : %d Bytes\n",stack.GetDynSize());

	win_code -> ClrPrintwin();
//	win_code -> Clear(GFX_BLACK);
	if (instack) {
//		win_code -> Bar(0,0,8191,win_code->FontY(),GFX_RED);
	}
	
	stack.SetPopPos(adr);
	win_code->ClrPrintwin();
	zSTRING curFunc(":: ");
	if (in_func) curFunc += in_func->name;
	win_code->Printwin(curFunc+" ::\n");
	while (stack.GetPopPos() < stack.GetDynSize()) {
		GetNextCommand(s);
		win_code -> Printwin(s+"\n");
		lines++;
		if (lines>=maxlines) break;
	}
	stack.SetPopPos(adr);
}

// *******************************************************************************************
// EXTERNALS DEFINITION
// *******************************************************************************************

void zCParser :: DefineExternal (const zSTRING &s, zBOOL (*Proc)(), int type, int first...)
{
	zCPar_Symbol *par,*sym = zNEW( zCPar_Symbol() );
	
	sym -> name		= s;	
	sym -> name		. Upper();
	sym -> type		= zPAR_TYPE_FUNC;
	sym -> ele		= 0;
	sym -> SetFlag (zPAR_FLAG_CONST | zPAR_FLAG_EXTERNAL);

	// Type Defines if and what function returns
	// Create Return-Symbol
	if (type!=zPAR_TYPE_VOID) {
		// Create Func-Symbol
		sym -> SetFlag(zPAR_FLAG_RETURN);
	}
	// Use the offset Var as return type 
	sym -> SetOffset(type);

	if (!symtab.Insert(sym)) {
		if (!compiled) {
			Error(zSTRING("Redefined External . "+s));
			return;
		} else {
			zSTRING s = sym->name;
			delete(sym);
			sym = GetSymbol (s);
		}
	}

	sym -> SetStackPos((int)Proc);

	if (!compiled) {
		// Now initialize the Parameter list
		int		 partype = first;
		va_list	 marker;
		va_start (marker,first);
		while (partype!=zPAR_TYPE_VOID) {
			// New Parameter Type
			par  = zNEW( zCPar_Symbol() );
			par -> name = sym->name + ".PAR" + zSTRING((int)sym->ele);
			par -> type = partype;
			par -> SetParent(NULL);
			symtab.Insert(par);
			sym -> ele++;
			// Next Parameter
			partype = va_arg(marker, int);
		}
		va_end(marker);
	}
}
/*
void zCParser :: DefineExternalInstances ( int index, )
// Specify Instance - Types
{
}
*/
void zCParser :: DefineExternalVar (const zSTRING &s, void *adr, int type, int ele)
{
	zCPar_Symbol *sym = zNEW( zCPar_Symbol() );
	
	sym -> name		= s;	
	sym -> name		. Upper();
	sym -> type		= type;
	sym -> ele		= ele;
	sym -> SetFlag (zPAR_FLAG_CONST | zPAR_FLAG_EXTERNAL);
	sym -> space	= TRUE;

	if (!symtab.Insert(sym)) {
		if (!compiled) {
			Error(zSTRING("Redefined External Var. "+s));
			return;
		} else {
			zSTRING s = sym->name;
			delete(sym);
			sym = GetSymbol (s);
		}			
	}
	
	sym -> space	= FALSE;		// Damit kein Versuch unternommen wird, die Var zu deleten
	sym -> SetDataAdr (adr);
}

void zCParser :: GetParameter(int &value)
{
	value = PopDataValue();
}

void zCParser :: GetParameter(float &value)
{
	int t = datastack.Pop();
	if (t==zPAR_TOK_PUSHINT) {
		t	  = datastack.Pop();
		value = *(float*)(&t);
	} else {
		value = *(float*)datastack.Pop();
	}
}

void zCParser :: GetParameter(zSTRING &s)
{
	s = *PopString();
}

void* zCParser :: GetInstance()
{
	int index = datastack.Pop();
	void* adr = NULL;
	if (index>0) adr = (void*)symtab.GetSymbol(index)->GetOffset();
	return adr;
}

void* zCParser :: GetInstanceAndIndex( int&  a_index )
{
	int index = datastack.Pop();
	void* adr = NULL;
	if (index>0) adr = (void*)symtab.GetSymbol(index)->GetOffset();
	a_index = index;
	return adr;
}


void zCParser :: SetReturn(int value)
{
	datastack.Push(value);							
	datastack.Push(zPAR_TOK_PUSHINT);			
}

// CODECHANGE [STEFAN]
void zCParser :: SetReturn(float value)
{
	datastack.Push(*((int*)&value));
	datastack.Push(zPAR_TOK_PUSHINT);			
}
// CODECHANGE [STEFAN] END

void zCParser :: SetReturn(void* adr)
// Eine Instanz wird als rueckgabewert geliefert
{
	datastack.Push(instance_help);
//	datastack.Push(zPAR_TOK_PUSHINST);
	zCPar_Symbol *sym = symtab.GetSymbol(instance_help);
	if (sym) sym -> SetOffset((int)adr);
}

void zCParser :: SetReturn(zSTRING &s)
// Ein String wird als rueckgabewert geliefert
// "s" muss eine static value sein, weil die Adresse auf den Stack gepackt wird !
{
	datastack.Push((int)&s);
	datastack.Push(zPAR_TOK_PUSHSTR);
}

// *******************************************************************************************
// INDEX SEARCH - HELPERS
// *******************************************************************************************

int zCParser :: FindInstanceVar(zSTRING &s)
// Get the index : fighter.hitp
// a) Instanzname	b) ClassVar
{
	zCPar_Symbol *sym;
	int p = s.Search(".");
	if (p>0) {
		zSTRING in	= s.Copied(0,p);
		s.Delete(0,p+1);
		// Instanz ermitteln
		instance= FindIndex(in);
		sym		= symtab.GetSymbol(instance);
		if ((!sym) || (sym->type!=zPAR_TYPE_INSTANCE)) return -1;

		// Klasse ermitteln
		sym = sym -> GetParent();
		if (sym->type==zPAR_TYPE_PROTOTYPE) 
			sym = sym->GetParent();
		if (sym->type!=zPAR_TYPE_CLASS) return -1;
		s = sym->name + "." + s;
		return (symtab.GetIndex(s));
	}
	return -1;
}

int zCParser :: GetLastInstance()
// Paar zusammen mit FindInstanceVar
// Liefert den Instance-Index des letzten "FindInstanceVar" - Aufrufes
{
	return instance;
}

int zCParser :: FindIndex(zSTRING &s)
{
	int index = FindInstanceVar(s);

	if ((index<0) && (in_func))		index = symtab.GetIndex(in_func ->name+"."+s);
	if ((index<0) && (in_class))	index = symtab.GetIndex(in_class->name+"."+s);
	if (index<0)					index = symtab.GetIndex(s);	

	return index;
}


// *******************************************************************************************
// DEBUG SHOWS 
// *******************************************************************************************


