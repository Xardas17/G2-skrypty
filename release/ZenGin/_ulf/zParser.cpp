/******************************************************************************** 
 
     $Workfile:: zParser.cpp          $                $Date:: 13.03.01 18:37   $
     $Revision:: 33                   $             $Modtime:: 18.02.01 22:02   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zParser.cpp $
 * 
 * 33    13.03.01 18:37 Wohlers
 * 
 * 32    31.01.01 20:19 Wohlers
 * 
 * 31    9.01.01 17:09 Wohlers
 * 
 * 30    8.01.01 21:16 Wohlers
 * 
 * 29    8.01.01 14:55 Wohlers
 * 
 * 28    24.11.00 15:46 Wohlers
 * 
 * 27    15.11.00 13:13 Wohlers
 * 
 * 26    8.11.00 18:00 Speckels
 * 
 * 25    8.11.00 17:47 Speckels
 * 
 * 24    7.11.00 2:45 Speckels
 * 
 * 23    3.11.00 14:46 Wohlers
 * 
 * 22    3.11.00 14:26 Wohlers
 * 
 * 21    19.10.00 21:49 Wohlers
 * 
 * 20    12.10.00 19:03 Wohlers
 * 
 * 19    22.09.00 18:33 Wohlers
 * 
 * 18    11.09.00 20:52 Speckels
 * 
 * 17    6.09.00 15:24 Rueve
 * cleanup - unused vars
 * 
 * 16    25.08.00 0:33 Wohlers
 * 
 * 15    24.08.00 16:50 Moos
 * malloc durch zNEW ersetzt
 * 
 * 
 * 14    18.08.00 15:44 Wohlers
 * 
 * 13    2.08.00 14:25 Wohlers
 * 
 * 12    27.07.00 16:34 Rueve
 * Fix: Liest ein Byte zuviel aus Datei
 * 
 * 11    21.07.00 15:35 Wohlers
 * 
 * 10    21.07.00 14:43 Wohlers
 * 
 * 9     20.07.00 21:35 Wohlers
 * 
 * 8     5.07.00 12:23 Wohlers
 * 
 * 7     5.06.00 22:37 Wohlers
 * uSrc 05.06.00
 * 
 * 6     22.05.00 18:45 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:10 Edenfeld
 * 
 * 5     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 4     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 17    4.04.00 20:06 Wohlers
 * Parser-Class-Offset-Check
 * 
 * 16    3.04.00 18:31 Wohlers
 * uSrc 0.76b
 * 
 * 15    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 13    16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 12    9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 11    22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 10    6.02.00 18:40 Wohlers
 * Konsolen-Instanzen speichern gefixed
 * 
 * 9     4.02.00 15:39 Wohlers
 * Umlaut-Bugfix
 * 
 * 7     11.01.00 23:36 Wohlers
 * 
 * 6     9.12.99 22:33 Wohlers
 * 
 * 5     7.12.99 22:09 Wohlers
 * NOFUNC als Keyword
 * 
 * 4     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include <conio.h>
#include <io.h>
#include <stdarg.h>

#include "zCore.h"

#include "zParser.h"
#include "zParser_Const.h"
#include "zDisk.h"
#include "zOption.h"
#include "zConsole.h"
#include "zview.h"
#include "zRenderer.h"
#include "zViewProgressBar.h"

#include "zArchiver.h"

#include "zWin32.h"
#include "zInput_Win32.h"

#pragma warning ( disable:4244 )

// ****************************************************************************************
// MAIN PARSER
// ****************************************************************************************

zCParser parser(1000);

// ****************************************************************************************
// ERROR MESSAGES
// ****************************************************************************************

extern zSTRING ParErr_SyntaxError;
extern zSTRING ParErr_Redefined;
extern zSTRING ParErr_UnknownVar;
extern zSTRING ParErr_UndefinedFunction;
extern zSTRING ParErr_NoValidClass;
extern zSTRING ParErr_Expected;

zSTRING Semikolon	(";");

// ****************************************************************************************
// VERSION NUMBER FOR TREFILES
// ****************************************************************************************

zBYTE	tree_version = 50;

void	zCParser :: SetVersion (zBYTE v)	{ tree_version = v; };
zBYTE	zCParser :: GetVersion ()			{ return tree_version; };
zBOOL	zCParser :: enableParsing			=	FALSE;

// ****************************************************************************************
// FILE - CONSTRUCTOR / DESTRUCTOR
// ***************************************************************************************

zCPar_File :: zCPar_File ()
{
	fileid		= 0;							// FileNumber
	begin_adr	= NULL;							// Startadresse der Filedaten 
	size		= 0;							// Size of File in Bytes
	labels		= 0;							// Anzahl der Labels in diesem File
	treeload	= FALSE;						// Treeload activated
	tree		= NULL;

	EnableTreeLoad(FALSE);	
}

zCPar_File :: ~zCPar_File()
{
	Dispose();
	DeleteTree();
	begin_adr	= NULL;
	tree		= NULL;
}

// ****************************************************************************************
// FILE - MEMBERS
// ****************************************************************************************

zBOOL zCPar_File :: IsNewerDate(zDATE &a,zDATE &b)
// a > b
{
	zDWORD date1 = (zDWORD(a.year)<<8) + zDWORD(a.month);
	zDWORD date2 = (zDWORD(b.year)<<8) + zDWORD(b.month);
	if (date1>date2) return TRUE;
	if (date1<date2) return FALSE;
	// Gleicher Jahr/Monat etc.... Jetzt Stunden und Minuten
    date1 = (zDWORD(a.day)<<24) + (zDWORD(a.hour)<<16) + (zDWORD(a.minute)<<8) + zDWORD(a.second);
    date2 = (zDWORD(b.day)<<24) + (zDWORD(b.hour)<<16) + (zDWORD(b.minute)<<8) + zDWORD(b.second);
	return (date1>date2);
}

zBOOL zCPar_File :: IsExactDate(zDATE &a,zDATE &b)
{
	zDWORD date1 = (zDWORD(a.year)<<8) + zDWORD(a.month);
	zDWORD date2 = (zDWORD(b.year)<<8) + zDWORD(b.month);
	if (date1!=date2) return FALSE;
	// Gleicher Jahr/Monat etc.... Jetzt Stunden und Minuten
    date1 = (zDWORD(a.day)<<24) + (zDWORD(a.hour)<<16) + (zDWORD(a.minute)<<8) + zDWORD(a.second);
    date2 = (zDWORD(b.day)<<24) + (zDWORD(b.hour)<<16) + (zDWORD(b.minute)<<8) + zDWORD(b.second);
	return (date1==date2);
}

void zCPar_File :: SetFileNumber (int nr)
{
	fileid = nr;
}

int zCPar_File :: GetFileNumber ()
{
	return fileid;
}

zSTRING zCPar_File :: GetName()
{
	return name;
}

void zCPar_File :: EnableTreeLoad(zBOOL on)
{
	treeload = on;
}


/* ----------------------------------------------------------------------
	
	zCPar_File::Load()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */


int zCPar_File :: Load (zSTRING &s, zCPar_SymbolTable &symtab, zDATE& modifyDate)
// -1 : Error, File not found
//  0 : OK, but reparse
//  1 : OK, complete Tree loaded
{
	zFILE *f = zfactory->CreateZFile(s);
	if (f->Exists()==FALSE) {
		delete(f);
		return -1;
	};
	
	// Delete Tree data
	if (tree) delete(tree);
	tree = NULL;

	name = s;

	if (treeload) {
		zFILE_STATS dfile_date;
		f->GetStats (dfile_date);
		modifyDate = dfile_date.modifyDate;
		if (LoadTree(dfile_date,symtab)) return 1;
	}

	// ***************
	// Read Full File
	// ***************
	f->Open();
	// Get Size in Bytes	
	size = f->Size() + 1;
	// Allocate memory
	begin_adr = zNEW_ARRAY(char,size);
	if (!begin_adr) return -2;
	// Read File
	f->Reset();
	f->Read (begin_adr,size-1);
	f->Close();
	delete(f);
	// End of File = 0
	*(begin_adr + size - 1) = 0;

	return 0;
}

char* zCPar_File :: GetStartAddress()
{
	return begin_adr;
}

char* zCPar_File :: GetEndAddress()
{
	return (char *)(begin_adr + size - 1);
}


/* ----------------------------------------------------------------------
	
	zCPar_File::Dispose()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void zCPar_File :: Dispose ()
// releases File-Inhalt
{
    delete[] begin_adr;
	begin_adr = NULL;
}

void zCPar_File :: SetTree(zCPar_TreeNode *t)
{
	if (tree) delete(tree);
	tree = t;
}

zCPar_TreeNode* zCPar_File :: GetTree()
{
	return tree;
}

void zCPar_File :: SetLabelCount(int anz)
{
	labels = anz;
}

int  zCPar_File :: GetLabelCount()
{
	return labels;
}

void zCPar_File :: SaveTree( int c, zCPar_Symbol *s, zDATE& modifyDate )
{
	// Save Symbols + ParseTree
	zoptions->ChangeDir(DIR_SCRIPTS);

	int p = name.Search(".");
	zSTRING treename = name.Copied(0,p) + ".tre";
		
	zFILE *f = zfactory->CreateZFile(treename);
	f->SetDir("_work");
	f->Create();

	// Save Modify-Date of D-File
	f->Write(&modifyDate,sizeof(modifyDate));
	
	// Write Version-Number
	f->Write(&tree_version,sizeof(tree_version));

	// Labelcount
	f->Write(&labels,sizeof(labels));

	// Save SymbolTable
	zCPar_Symbol *par, *sym = s;
	f->Write(&c,sizeof(c));
	for (int i=0; i<c;i++) {
		sym		-> Save(f);
		// Parent ?
		par		=  sym -> GetParent();
		zBOOL l  =  (par!=NULL);
		f->Write(&l,sizeof(l));
		if (par) f->Write(par->name+"\n");

		sym=sym	-> GetNext();
	}

	// Save ParseTree
	SaveTreeNode(f,tree);
	f->Close();
	delete(f);
}

void zCPar_File :: SaveTreeNode(zFILE *f, zCPar_TreeNode *node)
{
	if (node==NULL) return;
	
	zBOOL l = (node->name.Length()>0);
	f->Write(&l,sizeof(l));
	if (l) f->Write(node->name+"\n");

	f->Write(&node->token,sizeof(node->token));
	f->Write(&node->value,sizeof(node->value));
	f->Write(&node->info ,sizeof(node->info));
	f->Write(&node->left ,sizeof(node->left));
	f->Write(&node->right,sizeof(node->right));
	f->Write(&node->next ,sizeof(node->next));

	if (node-> left)	SaveTreeNode(f,node->left);
	if (node->right)	SaveTreeNode(f,node->right);
	if (node-> next)	SaveTreeNode(f,node->next);
}

zCPar_TreeNode* errorNode = NULL;

zCPar_TreeNode* zCPar_File :: LoadTreeNode(zFILE *f)
{
	zCPar_TreeNode* node = zNEW( zCPar_TreeNode() );
	
	zBOOL l;
	f->Read(&l,sizeof(l));
	if (l) f->Read(node->name);

	f->Read(&node->token,sizeof(node->token));
	f->Read(&node->value,sizeof(node->value));
	f->Read(&node->info ,sizeof(node->info));
	f->Read(&node->left ,sizeof(node->left));
	f->Read(&node->right,sizeof(node->right));
	f->Read(&node->next ,sizeof(node->next));

	if (node->left)		node->left	= LoadTreeNode(f);
	if (node->right)	node->right = LoadTreeNode(f);
	if (node->next)		node->next	= LoadTreeNode(f);	

	return node;
}

zBOOL zCPar_File :: LoadTree(zFILE_STATS &dfile_date, zCPar_SymbolTable &symtab)
{
	// Check .tre 
	int	p = name.Search(".");
	zSTRING stre = name.Copied(0,p) +".tre";
	
	zFILE *ftre = zfactory->CreateZFile (stre);
	ftre->SetDir("_work");
	if (ftre->Exists()) {
		// Read date
		ftre->Open();
		zDATE trefile_date;
		ftre->Read(&trefile_date,sizeof(trefile_date));
		// ********************************************************
		// Wenn TreeFile neuer ist als das D-File, dann Tree laden
		// ********************************************************
//		if (!IsNewerDate(trefile_date.modifyDate,dfile_date.modifyDate)) {
		if (!IsExactDate(trefile_date,dfile_date.modifyDate)) {
			// Nicht geladen, Datum nicht identisch mit Datum des "D-Files"
			ftre->Close();
			delete(ftre);
			return FALSE;
		}
	
	} else {
		// Tre-File gibt's noch nicht.
		delete(ftre);
		return FALSE;
	}

	DeleteTree();
	
	// ********************************************************
	// Wenn Versionsnummer != aktuelle -> kein Tree laden
	// ********************************************************
	zBYTE version;
	ftre->Read(&version,sizeof(version));
	if (version!=tree_version) {
		ftre->Close();
		delete(ftre);
		return FALSE;
	}
	
	// Labelcount
	ftre->Read(&labels,sizeof(labels));
	
	// Load SymbolTable
	int c;
	zCPar_Symbol *sym;
	ftre->Read(&c,sizeof(c));
	for (int i=0; i<c;i++) {
		sym		=  zNEW( zCPar_Symbol() );
		sym		-> Load(ftre);
		// Parent ?
		zBOOL l;
		ftre->Read(&l,sizeof(l));
		if (l) {
			zSTRING s;
			ftre->Read(s);
			sym -> SetParent ( symtab.GetSymbol(s) );
		}
		symtab.Insert(sym);
		sym -> SetFileNr(fileid);
	}
	
	// Load ParseTree
	tree = LoadTreeNode(ftre);
	ftre->Close();
	delete(ftre);
	return TRUE;
}

void zCPar_File :: DeleteTree()
{
	if (tree) {
		delete tree;
		tree = NULL;
	}
}

// ****************************************************************************************
// PARSER - STATICS
// ****************************************************************************************

zCParser* zCParser :: cur_parser = NULL;

zCParser* zCParser :: GetParser ()
{
	return cur_parser;
};

// ****************************************************************************************
// PARSER - CONSTRUCTOR / DESTRUCTOR
// ****************************************************************************************

zCParser :: zCParser (int n)
{
	if (n>0) symtab.SetSize(n);
	add_funclist = NULL;
	Reset();
}

zCParser :: ~zCParser()
{
	// Remove Files from List
	for (int i=0; i<file.GetNumInList(); i++) delete file[i];
	// Clear Rest
	symtab   .Clear();
	stringtab.Clear();
	stack	 .Clear();
	datastack.Clear();
	
	add_funclist= NULL;
	self		= NULL;
	pc_start	= NULL;					
	pc			= NULL;
	oldpc		= NULL;					
	pc_stop		= NULL;
	oldpc_stop	= NULL;					
	in_func		= NULL;					
	in_class	= NULL;					
	tree		= NULL;
	treenode	= NULL;
	win_code	= NULL;
	labelpos	= NULL;
	msgfunc		= NULL;
}

// ****************************************************************************************
// ERROR - HANDLING
// ****************************************************************************************

void zCParser :: SetMessageFunc	( void (*m)(zSTRING s) )
{
	msgfunc = m;
}

void zCParser :: SetStopOnError ( zBOOL stop )
{
	stop_on_error = stop;
}

void zCParser :: Error (zSTRING &e, int line)
{
	zSTRING l;
	zSTRING add = "U:PAR: ";
	error		= TRUE;
	if (linkingnr>=0) {
		// Fehler während des Linkens
		l = GetFileName(linkingnr)+": " + e;
		errorline = line;
	} else if (line>=0) {
		// Fehler während des Parsens
		l = e + " ( line "+zSTRING(linec)+" )";
		errorline = linec;
	} else {
		l = e;
	}
	if (msgfunc!=NULL) msgfunc(l);
	if (stop_on_error) {
		// Als fatal Error an zSpy
		zERR_FATAL(add + l);
		// FIXME : zENGINE Close !!!!
		sysExit();
	} else {
		zerr.Message(add + l);
	}
}

void zCParser :: Message (zSTRING &m)
{
	zSTRING add = "U:PAR: ";
	if (msgfunc!=NULL) msgfunc(m);
	zerr.Message(add + m);
}

zBOOL zCParser :: Error()
{
	return error;
}

// ****************************************************************************************
// SAVE / LOAD Dat-Files
// ****************************************************************************************

int zCParser :: SaveDat (zSTRING &s)
{
	if (!datsave) return 0;
	Message("Saving "+s);
	zoptions->ChangeDir(DIR_COMPILED_SCRIPTS);
	zFILE *f = zfactory->CreateZFile(s);
	f->Create();
	// Saving Version
	f->Write(&tree_version,sizeof(tree_version));
	// Saving Symboltable
	symtab.Save(f);
	stack .Save(f);
	f->Close();
	delete(f);
	return 0;
}

int zCParser :: LoadDat (zSTRING &s)
{
	zoptions->ChangeDir(DIR_COMPILED_SCRIPTS);
	Message("Loading "+s);
	zFILE *f = zfactory->CreateZFile(s);
	f->Open();
	// Load version
	zBYTE version;
	f->Read(&version,sizeof(version));
	if (version!=tree_version) {
		f->Close();
		delete(f);
		Error(zSTRING("Dat-File is not compatible. Please use the \"SRC\"-File."),0);
		return -1;
	}
	// Loading Symboltable
	symtab.Load(f);
	stack .Load(f);
	f->Close();
	delete(f);
	instance_help = symtab.GetIndex(char(255)+zSTRING("INSTANCE_HELP"));
	return 0;
}

// ****************************************************************************************
// PARSING
// ****************************************************************************************

int zCParser :: Parse (zSTRING s)
{
	s.Upper();
	mainfile = s;
	compiled = FALSE;

	int p	 = s.Search(".SRC");

	if (enableParsing) {
		if (p>0) {
			return ParseSource(s);
		} else if (s.Search(".D")>0) {
			return ParseFile(s);
		}
	} 
	
	// Default : Loading Dat-File
	if (p>0) s.Overwrite(p,".DAT");
	if (s.Search(".DAT")>0) {
		compiled = TRUE;
		zPATH pp(s);
		return LoadDat(pp.GetFilename()+".DAT");
	} 

	return -1;	
}

int zCParser :: ParseSource(zSTRING &s)
{
	int w,pos;
	zBOOL wildcard;
	_finddata_t found;
	zSTRING str,path,pathsrc,fname;
	
	zoptions->ChangeDir(DIR_SCRIPTS);

	// Create Path Angaben for Source-File
	zPATH   argh(s);
	
	zSTRING cdir	= argh.GetDir();
	zSTRING drive	= argh.GetDrive();
	if (drive!="") cdir = drive + ":" + cdir;
	
	// Init File
	zFILE *source = zfactory->CreateZFile(s);
	
	// Open Source File
	if (source->Exists()==FALSE) {
		Error("Source-File "+s+" not found.");	
		return -1;
	}
	
	source->Open();
	source->Reset();
	do {
		path = "";
		wildcard = FALSE;
		source->Read(str);
		if (source->Eof()!=0) break;
		str.Upper();

		// Check for Wildcards !
		if ((str.Search("*")>0) || (str.Search("?")>0)) {
			pos = str.Length();
			do {
				pos--;
				if (str[pos]=='\\') 
					path = str.Copied(0,pos+1);
			} while ((str[pos]!='\\') && (pos>0));	
			
			wildcard = TRUE;
			zSTRING seek = cdir + str;

			zFILE::DirectFileAccess(true,seek);
			w = _findfirst(seek.ToChar(),&found);
			zFILE::DirectFileAccess(false);

			if (w<0) {
				Error("Found no matching File : "+str);
				break;
			}
			str = path + found.name;
			str.Upper();
		}
		
		do {
			// File (s) starten
			if (str.Search(".SRC")>=0) {
				ParseSource(cdir + str); 
			} else 
			if (str.Search(".D"  )>=0) 
				ParseFile  (cdir + str);
			if (wildcard) {
				if (_findnext(w,&found)>=0) {
					zSTRING tmp = path + found.name;	tmp.Upper();
					if (tmp==str) {
						zERR_WARNING("U:PAR:Parser found 2 files with same filename.");
						str="";
					} else {
						str = tmp;
					}
				} else
					wildcard = FALSE;
			}
		} while (wildcard);
	} while (TRUE);
	source->Close();
	delete(source);
	return 0;
}

int zCParser :: ParseFile(zSTRING &s)
{
	// Already Parsed ?
	for (int i=0; i<file.GetNumInList(); i++) {
		if (s == file[i]->GetName() ) {
			zERR_WARNING("U:PAR: Ignoring "+s+" ( File already parsed )");
			return 0;
		};
	}

	zSTRING w;
	zDATE	modifyDate;

	fname = s;

	labelcount		= 0;
	treenode = tree = zNEW( zCPar_TreeNode() );
	tree -> token   = zPAR_TOK_SKIP;
	
	// Insert File to global-list
	zCPar_File* f = zNEW( zCPar_File() );
	file.Insert(f);
	f->SetFileNumber(file.GetNumInList()-1);

	f->EnableTreeLoad(treeload);
	int res	= f->Load(s,symtab,modifyDate);
	if (res==-1) {
		// File not found
		Error("File "+s+" not found.");
		file.Remove(f);
		delete(f);
		return -1;
	} 


	if (res==0) {

		parse_changed = TRUE;

		Message(s + " : Parse...");

		int oldnuminlist		= symtab.GetNumInList();
		zCPar_Symbol *lastsym	= symtab.GetLastSymbol();

		linec	= 1; line_start = 0;
		pc_start= pc = f->GetStartAddress();
		pc_stop = f->GetEndAddress();

		// Parsing....
		do {
			ReadWord(w);
		//		printf("%s ",aword.ToChar());
			if (w=="CONST")		DeclareVar(TRUE);	else 
			if (w=="VAR")		DeclareVar(FALSE);	else	
			if (w=="FUNC")		DeclareFunc();		else		
			if (w=="CLASS")		DeclareClass();		else 
			if (w=="INSTANCE")	DeclareInstance();	else
			if (w=="PROTOTYPE")	DeclarePrototype();	else
			if (w=="")			break;				else
								Error(ParErr_SyntaxError+w);

			Match(zSTRING(";"));
		} while (pc < pc_stop);	

		// delete File itself from memory
		f -> Dispose		();

		// Save the created Tree
		f -> SetLabelCount	(labelcount);
		f -> SetTree		(tree);
		if (treesave) {
			if (lastsym) f -> SaveTree (symtab.GetNumInList()-oldnuminlist,	lastsym->GetNext(),modifyDate);
			else		 f -> SaveTree (symtab.GetNumInList(),				symtab.GetFirstSymbol(),modifyDate);
		}

	} else {
		Message(s + " : Load...");
		labelcount = f->GetLabelCount();
	}
	
	return 0;
}

void zCParser :: ParseBlock()
{
	// Parsing....
	zSTRING w;
	Match(zSTRING("{"));
	while (pc < pc_stop) {
		ReadWord(w);
		if (w=="CONST")	DeclareVar(TRUE);		else
		if (w=="VAR")	DeclareVar(FALSE);		else
		if (w=="RETURN")DeclareReturn();		else
		if (w=="IF")	DeclareIf();			else
		if (w=="}")		return;					
		else {
			// Has to be an Expression
			DeclareAssign(w);
		}
		Match(zSTRING(";"));
	}
}

// *************************************************************************************
// STACK - CREATION
// *************************************************************************************

void zCParser :: CreatePCode()
{
	int i;
	float time1 = 0.0f;
	error = FALSE;
	
	if (compiled) {
		Message(zSTRING("Linking skipped."));
		goto __skiplink;
	}
	
	Message(zSTRING("Linking ..."));
	time1 = sysGetTime();	

	// Alloc Space for Label solving
	for (i=0; i<file.GetNumInList(); i++) {
		
		if (file[i]->GetTree()) {

//			zERR_MESSAGE(8,0,"U:PAR: Creating Labels :"+file[i]->GetName());
			linkingnr	= i;
			labelcount	= file[i]->GetLabelCount();
			labelpos	= zNEW(int)[labelcount];
			memset		(labelpos,0,sizeof(int)*labelcount);
			
//			zERR_MESSAGE(8,0,"U:PAR: Pushing Tree:"+file[i]->GetName());
			PushTree	(file[i]->GetTree());
			
//			zERR_MESSAGE(8,0,"U:PAR: Solving Labels :"+file[i]->GetName());
			SolveLabels	(file[i]->GetTree());
			
//			zERR_MESSAGE(8,0,"U:PAR: Deleting Tree:"+file[i]->GetName());
			file[i]		-> DeleteTree();
			
//			zERR_MESSAGE(8,0,"U:PAR: Deleting Labels:"+file[i]->GetName());
			delete[]	labelpos;
		}
	};

	time1 = sysGetTime() - time1;

__skiplink:

	linkingnr = -1;

	if (error)
		Message(zSTRING("Linking failed."));
	else {
		Message("Symbols   : " + zSTRING(symtab.GetNumInList()));
		Message("Code Size : " + zSTRING(stack.GetDynSize()) + " bytes.");
		Message("Linking ok (" + zSTRING(time1/1000,2) + "s).");
	}

	if ((!compiled) && (parse_changed)) {
		zPATH p(mainfile);
		SaveDat(p.GetFilename()+".DAT");	
	}

	compiled	= TRUE;
	self		= GetSymbol("SELF");
}

void zCParser :: ShowSymbols()
{
	symtab.Show();
}

zCPar_TreeNode* lastNode = NULL;

void zCParser :: PushTree(zCPar_TreeNode *tree)
{
	zCPar_TreeNode* node = tree;
	while (node) {
		node = PushOnStack(node);
	}
}

zCPar_TreeNode* zCParser :: PushOnStack(zCPar_TreeNode* node)
// Hier sind die Indizes verbindlich. Es duerfen danach keine 
// Aenderungen an der Symboltabelle vorgenommen werden.
{
	static numcount = 0;

	zCPar_Symbol *sym;
	int index,pos;

	lastNode = node;	// Letzter Node ohne Fehler

	numcount++;
	if (node->right)	PushTree(node->right);
	if (node->left)		PushTree(node->left);
	if (node->token<=zPAR_OP_MAX) 
		stack.PushByte	(node->token);
	else if (node->token==zPAR_TOK_FLOAT) { 
		stack.PushByte	(zPAR_TOK_PUSHINT);
		stack.PushInt	(node->value);

	} else if (node->token==zPAR_TOK_VAR) {
		// Get Var Index
		index = FindIndex(node->name);
		if (index<0) {
			Error(ParErr_UnknownVar + node->name);
			return NULL;
		}
		sym   = symtab.GetSymbol(index);
		if ((sym->HasFlag(zPAR_FLAG_CLASSVAR)) && (in_class!=sym->GetParent())) {
			// Instance Var !!!			
			// -> Security, nur wenn in_classnr != angewaehlter Class ist
			stack.PushByte(zPAR_TOK_SETINSTANCE);
			stack.PushInt (GetLastInstance());
		}
		// Types OK ?
		sym = symtab.GetSymbol(index);
		// **********************************************************************
		// Sonderfall I : Instanzen werden als INT ( deren Index ) interpretiert
		// **********************************************************************
		if ((node->info==zPAR_TYPE_INT) && ( (sym->type==zPAR_TYPE_INSTANCE) || (sym->type==zPAR_TYPE_PROTOTYPE))) {
			stack.PushByte(zPAR_TOK_PUSHINT);
			stack.PushInt (index);
		
		// ********************************************************************************
		// Sonderfall II : Funktionsreferenzen koennen auch Prototypes oder Instances sein
		// ********************************************************************************
		} else if ((node->info==zPAR_TYPE_FUNC) && 
				   ( (sym->type==zPAR_TYPE_PROTOTYPE) || (sym->type==zPAR_TYPE_INSTANCE)) ) {
			stack.PushByte(zPAR_TOK_PUSHVAR);
			stack.PushInt (index);
			//stack.PushByte(0);

		} else if (sym->type!=node->info) {
			Error("Wrong type : "+node->name);
			return NULL;
		} else {
			// FIXME : Later Adress not Index ?!?!?!?!?!
			if (node->value>0)	stack.PushByte(zPAR_TOK_PUSHVAR + zPAR_TOK_FLAGARRAY);
			else				stack.PushByte(zPAR_TOK_PUSHVAR);
			stack.PushInt (index);
			// Array out of Range
			if ((node->value<0) || (node->value>=sym->ele)) {
				Error("Buuuuhhhh, Pfiffe, Unmut : Array-Index out of Range : "+sym->name+"[ "+zSTRING(node->value)+" ]");
			}
			if (node->value>0)  stack.PushByte(node->value);
		}

	// ******************************************************************************
	// Help Tokens
	// ******************************************************************************

	} else if (node->token==zPAR_TOK_FUNC) {
		in_funcnr	=  symtab.GetIndex (node->name);
		if (in_funcnr<0) Error(ParErr_UnknownVar + node->name);
		in_func		=  symtab.GetSymbol	(in_funcnr);

		// Position im Stack setzen, wenns keine External-Func ist.
		if (!in_func->HasFlag(zPAR_FLAG_EXTERNAL)) 
			in_func		-> SetStackPos		(stack.GetDynSize());

	} else if (node->token==zPAR_TOK_FUNCEND) {
		in_funcnr	= 0;
		in_func		= NULL;
		stack.PushByte(zPAR_TOK_RET);

	} else if (node->token==zPAR_TOK_INSTANCE) {
		// Instance is a Func
		in_funcnr	=  symtab.GetIndex (node->name);
		if (in_funcnr<0) Error(ParErr_UnknownVar + node->name);
		in_func		=  symtab.GetSymbol(in_funcnr);

		// Get old Position for merging
		int oldpos;
		in_func		-> GetStackPos(oldpos);
		in_func		-> SetStackPos(stack.GetDynSize());
		// Get Parent (that's the class or the prototype)
		in_class	=  in_func->GetParent();
		// MergeMode ?
		if ((mergemode) && (oldpos>0)) {
			// Create a Call to old Instance
			stack.PushByte		 (zPAR_TOK_CALL);
			stack.PushInt		 (oldpos);
			if (in_class->type==zPAR_TYPE_PROTOTYPE) in_class = in_class->GetParent();

		} else if (in_class->type==zPAR_TYPE_PROTOTYPE) {
			// Von einem Prototype abgeleitet, give it a jump to him
			stack.PushByte		 (zPAR_TOK_CALL);
			in_class->GetStackPos(pos);
			stack.PushInt		 (pos);
			// Und die richtige Klasse schnappen
			in_class = in_class->GetParent();
		}

	} else if (node->token==zPAR_TOK_INSTANCEEND) {
		in_funcnr	= 0;
		in_func		= NULL;
		in_classnr	= 0;
		in_class	= NULL;
//		stack.PushByte(zPAR_TOK_RET);

	} else if (node->token==zPAR_TOK_CALL) {
		index				= symtab.GetIndex (node->name);
		zCPar_Symbol* sym	= symtab.GetSymbol(index);
		if (!sym) {
			Error(ParErr_UndefinedFunction+node->name);
			return NULL;
			//Message( "Warning : " + ParErr_UndefinedFunction + node->name + " -> Using default-function");
			//stack.PushByte		(zPAR_TOK_CALLEXTERN);
			//stack.PushInt		((int)&DefaultExternal);	
			//goto __goleave;
		}
		if ((sym->type==zPAR_TYPE_FUNC) && (sym->HasFlag(zPAR_FLAG_EXTERNAL))) {
			stack.PushByte		(zPAR_TOK_CALLEXTERN);
			stack.PushInt		(index);
		} else {
			stack.PushByte		(zPAR_TOK_CALL);
			sym -> GetStackPos	(pos);
			stack.PushInt		(pos);
		}
	
	} else if (node->token==zPAR_TOK_PUSHINDEX) {
		stack.PushByte			(zPAR_TOK_PUSHINT);
		index = FindIndex		(node->name); 
		sym   = symtab.GetSymbol(index);
		if (!sym) {
			Error(ParErr_UnknownVar + node->name);
			return NULL;
		}
		if ((sym->type!=zPAR_TYPE_FUNC) && (sym->type!=zPAR_TYPE_INSTANCE) && (sym->type!=zPAR_TYPE_PROTOTYPE))  {
			Error("Wrong type : "+node->name);
			return NULL;
		}
		stack.PushInt(index);

	} else if (node->token==zPAR_TOK_PUSHINST) {
		
		stack.PushByte (node->token);

		// NULL ist erlaubt.
		if (node->name=="NULL") {
			stack.PushInt(0x0000);
			return (node->next);
		}
		
		index = FindIndex(node->name); 
		sym   = symtab.GetSymbol(index);
		if (!sym) {
			Error(ParErr_UnknownVar + node->name);
			return NULL;
		}

		if (sym->type!=node->info) {
			Error("Wrong type : "+node->name);
			return NULL;
		}

		// Matching Base-Class ? 
		if ((node->value>0) && (GetBaseClass(index) != node->value)) {

			// unused   int clnr = GetBaseClass(index);
			// unused   zCPar_Symbol* baseClass = GetSymbol(clnr);
			zCPar_Symbol *cl = symtab.GetSymbol(node->value);
			zSTRING er = "Wrong type "+node->name;
			if (cl) er += " - Expected "+cl->name;
			Error(er);
			return NULL;
		}

		stack.PushInt(index);

	} else if (node->token==zPAR_TOK_ASSIGNSTR) {
		stack.PushByte(node->token);

	} else if (node->token==zPAR_TOK_ASSIGNSTRP) {
		stack.PushByte(node->token);

	} else if (node->token==zPAR_TOK_ASSIGNFLOAT) {
		stack.PushByte(node->token);
	
	} else if (node->token==zPAR_TOK_ASSIGNINST) {
		stack.PushByte(node->token);

	} else if (node->token==zPAR_TOK_NEWSTRING) {
		// Create StringConstant on Stack
		// Put it as lastentry in Symboltable
		zCPar_Symbol *sym = zNEW( zCPar_Symbol() );
		sym->type = zPAR_TYPE_STRING;
		sym->ele  = 1;
		sym->name = zSTRING(char(255)) + zSTRING(stringcount++);
		sym->SetFlag	(zPAR_FLAG_CONST);
		symtab.InsertEnd(sym);
		if (node->name.Length()>0) sym->SetValue (node->name);
		// Und PCode
		stack.PushByte(zPAR_TOK_PUSHVAR);
		stack.PushInt (symtab.GetNumInList()-1);
		//stack.PushByte(0);
	
	} else if (node->token==zPAR_TOK_ASSIGNFUNC) {
		stack.PushByte(node->token);

	} else if ((node->token==zPAR_TOK_JUMPF) || (node->token==zPAR_TOK_JUMP)) {
		stack.PushByte(node->token);
		// But save the stack Position for later label solving
		node -> info = stack.GetDynSize();
		stack.PushInt (0);			

	} else if (node->token==zPAR_TOK_LABEL) {
		assert(node->value<labelcount);
		labelpos[node->value] = stack.GetDynSize();

	} else if (node->token==zPAR_TOK_RET) {
		stack.PushByte(node->token);

	} else if (node->token==zPAR_TOK_SKIP) {
		// Just do nothing....

	} else {
		Error(zSTRING("Error : Push on Stack."));
	}

	return (node->next);
	//if (node->next) PushOnStack(node->next);
}

void zCParser :: SolveLabels(zCPar_TreeNode *node)
{
	if ((node->token==zPAR_TOK_JUMP) || (node->token==zPAR_TOK_JUMPF)) {
		// node -> info	 : Position des Jump-Befehles
		// node -> value : Labelnummer		
		assert (node->value<=labelcount);
		assert (node->info <=stack.GetDynSize());
		assert (labelpos[node->value]<=stack.GetDynSize());
		stack.Set(node->info,labelpos[node->value]);
	}
	if (errorNode && ((int)errorNode->left==0x0c7A)) {
		;
	};
	if (node->right) SolveLabels(node->right);
	if (node->left ) SolveLabels(node->left);
	if (node->next ) SolveLabels(node->next);
}

int zCParser :: MergeFile (zSTRING &s)
{
	int pos;
	zCPar_Symbol *sym;
	mergemode	= TRUE;
	error		= FALSE;
	
	EnableTreeSave(FALSE);
	Parse(s);
	
	if (!error) {
		CreatePCode();
		// Now check for merged Instances
		for (int i=0; i<symtab.GetNumInList(); i++) {
			sym = GetSymbol(i);
			if ((sym) && (sym->type==zPAR_TYPE_INSTANCE) && (sym->HasFlag(zPAR_FLAG_MERGED))) {
				// Gültige Instanz
				if (sym->GetOffset()!=NULL) {
					// Instanz existiert, neue Werte mergen
					// Get Stack - Address
					sym->GetStackPos(pos);				
					// Now skip first Jump of Stack ( 5 Bytes ) -
					// die alten Werte der Instanz sollen erhalten bleiben
					pos += 5;
					zCPar_Symbol :: SetUseInstance(sym);
					DoStack	 (pos);
					// Merged Instance found.
					Message("Instance "+sym->name+" merged.");
				}
			}
		}
	}	

	EnableTreeSave(FALSE);
	mergemode	= FALSE;
	return error;
}


// *************************************************************************************
// PSEUDO CODE - RUNNING
// *************************************************************************************


int zCParser :: PopDataValue()
{
	int t = datastack.Pop();
	if (t==zPAR_TOK_PUSHINT) {
		return datastack.Pop();
	} else if (t==zPAR_TOK_PUSHVAR) {
		return *(int *)datastack.Pop();
	} else
		return 0;
}

float zCParser :: PopFloatValue()
{
	int t = datastack.Pop();
	if (t==zPAR_TOK_PUSHINT) {
		return datastack.PopFloat();
	} else if (t==zPAR_TOK_PUSHVAR) {
		return *(float *)datastack.Pop();
	} else
		return 0;
}

int* zCParser :: PopVarAddress()
{
	int t = datastack.Pop();
	if (t==zPAR_TOK_PUSHVAR) {
		return (int *)datastack.Pop();
	} else {
		t = datastack.Pop();
		return NULL;
	}
}

zSTRING* zCParser :: PopString()
{
	// FIXME : Pop hier nicht noetig !
	datastack.Pop();
//	if (t==zPAR_TOK_NEWSTRING) {
//		return stack.PopString();
//	} else {
		return (zSTRING *)datastack.Pop();
//	}
}

void zCParser :: DoStack(int pos)
{
	zBOOL olddebug;
	zSTRING *s = NULL, **ss = NULL;
	zCPar_Symbol *sym = NULL, *sym2 = NULL;
	zBOOL (*proc_cpp)();
	int token,index,oldpos,*adr = NULL;
	float *fadr = NULL;
	stack.SetPopPos(pos);
	int res1,res2;
	zBOOL stepInto = FALSE;

	do {
		if (debugmode) {
			ShowPCode(stack.GetPopPos(),win_code, TRUE);
			zrenderer ->Vid_Clear(zCOLOR(0,0,0,0));
			screen	  -> DrawItems();
			zrenderer -> Vid_Blit();
			if (zinput->KeyPressed(KEY_F5)) {
				debugmode = FALSE;
				CloseViews();
			} else {
				// a) Warten bis beide Keys losgelassen wurden
				while (zinput->KeyPressed(KEY_F10) || zinput->KeyPressed(KEY_F11)) { sysEvent(); };
				// b) Warten bis einer der beiden Keys gedrueckt wurde.
				do {
					sysEvent();
					stepInto = zinput->KeyPressed(KEY_F11);
				} while (!zinput->KeyPressed(KEY_F10) && !zinput->KeyPressed(KEY_F11));

//				while (zinput->KeyPressed(KEY_F10))		{ sysEvent(); };
//				while (!zinput->KeyPressed(KEY_F10))	{ sysEvent(); };
				
			}			
		}
		token = stack.PopByte();
		switch (token) {
			case zPAR_TOK_PUSHINT	:	datastack.Push(stack.PopInt());							
										datastack.Push(zPAR_TOK_PUSHINT);
										break;
			case zPAR_TOK_PUSHVAR	:	// Push Adr on Stack
										index	= stack.PopInt();
										sym		= symtab.GetSymbol(index);
										adr		= (int *)sym -> GetDataAdr();
										datastack.Push((int)adr);
										datastack.Push(zPAR_TOK_PUSHVAR);
										break;
			case zPAR_TOK_PUSHVAR + zPAR_TOK_FLAGARRAY	:
										index	= stack.PopInt();
										sym		= symtab.GetSymbol(index);
										adr		= (int *)sym -> GetDataAdr(stack.PopByte());
										datastack.Push((int)adr);
										datastack.Push(zPAR_TOK_PUSHVAR);
										break;										

			case zPAR_OP_IS			:	adr		= PopVarAddress();
										*adr	= PopDataValue();
										break;
			case zPAR_OP_ISPLUS		:	adr		= PopVarAddress();
										*adr   += PopDataValue();
										break;
			case zPAR_OP_ISMINUS	:	adr		= PopVarAddress();
										*adr   -= PopDataValue();
										break;
			case zPAR_OP_ISMUL		:	adr		= PopVarAddress();
										*adr   *= PopDataValue();
										break;
			case zPAR_OP_ISDIV		:	adr		= PopVarAddress();
										*adr   /= PopDataValue();
										break;

			case zPAR_OP_PLUS		:	datastack.Push(PopDataValue()  + PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_MINUS		:	datastack.Push(PopDataValue()  - PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_MUL		:	datastack.Push(PopDataValue()  * PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_DIV		:	datastack.Push(PopDataValue()  / PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_MOD		:	datastack.Push(PopDataValue()  % PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_OR			:	datastack.Push(PopDataValue()  | PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_AND		:	datastack.Push(PopDataValue()  & PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_LOWER		:	datastack.Push(PopDataValue()  < PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_HIGHER		:	datastack.Push(PopDataValue()  > PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_LOG_OR		:	res1 = PopDataValue();	res2 = PopDataValue();
										datastack.Push(res1 || res2); datastack.Push(zPAR_TOK_PUSHINT); break;
			case zPAR_OP_LOG_AND	:	res1 = PopDataValue();	res2 = PopDataValue();
										datastack.Push(res1 && res2); datastack.Push(zPAR_TOK_PUSHINT); break;
			case zPAR_OP_SHIFTL		:	datastack.Push(PopDataValue() << PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_SHIFTR		:	datastack.Push(PopDataValue() >> PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_LOWER_EQ	:	datastack.Push(PopDataValue() <= PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_EQUAL		:	datastack.Push(PopDataValue() == PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_NOTEQUAL	:	datastack.Push(PopDataValue() != PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			case zPAR_OP_HIGHER_EQ	:	datastack.Push(PopDataValue() >= PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 	break;
			
			case zPAR_OP_UN_MINUS	:	datastack.Push(-PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 		break;
			case zPAR_OP_UN_PLUS	:	datastack.Push(+PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 		break;
			case zPAR_OP_UN_NOT		:	datastack.Push(!PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 		break;
			case zPAR_OP_UN_NEG		:	datastack.Push(~PopDataValue()); datastack.Push(zPAR_TOK_PUSHINT); 		break;

			case zPAR_TOK_CALL		:	olddebug  = debugmode;
										debugmode = stepInto;
						
										pos		= stack.PopInt();
										oldpos	= stack.GetPopPos();
										DoStack(pos); 
										stack.SetPopPos(oldpos);

										debugmode = olddebug;
										break;
			case zPAR_TOK_CALLEXTERN:	olddebug  = debugmode;
										debugmode = FALSE;
										
										cur_parser	= this;
										symtab.GetSymbol(stack.PopInt())->GetStackPos(pos);
										proc_cpp	= (zBOOL (__cdecl *)()) pos;

										// Save Instance Adr, 'cos you never know 
										// what happened in the External !
										//iadr = zCPar_Symbol :: instance_adr;
										sym			= (zCPar_Symbol*)zCPar_Symbol::GetUseInstance();
										
										oldpos		= stack.GetPopPos();
										proc_cpp ();
										stack.SetPopPos(oldpos);

										zCPar_Symbol ::  SetUseInstance(sym);
										
										debugmode = olddebug;
										
										break;
			case zPAR_TOK_RET		:	break;

			case zPAR_TOK_JUMP		:	stack.SetPopPos(stack.PopInt());
										break;

			case zPAR_TOK_JUMPF		:	pos = stack.PopInt();
										if (PopDataValue()==0) stack.SetPopPos(pos);
										break;
			
			case zPAR_TOK_SETINSTANCE:	zCPar_Symbol :: SetUseInstance(symtab.GetSymbol(stack.PopInt()));
										break;

			// ****************************************************************
			// STRINGS
			// ****************************************************************

			case zPAR_TOK_ASSIGNSTR	:	s  = (zSTRING *)PopVarAddress();
										*s = PopString();
										break;				
			case zPAR_TOK_ASSIGNSTRP:	ss  = (zSTRING **)PopVarAddress();
										*ss = PopString();
										break;				
			case zPAR_TOK_ASSIGNFUNC:	// Fixme -> Kann spaeter durch OP_IS ersetzt werden.
										adr		= PopVarAddress();
										*adr	= PopDataValue();
										break;				
			case zPAR_TOK_ASSIGNFLOAT:	fadr	= (float *)PopVarAddress();
										*fadr	= PopFloatValue();
										break;
			case zPAR_TOK_PUSHINST	:	datastack.Push(stack.PopInt());
										break;
			case zPAR_TOK_ASSIGNINST:	// Indexes der beiden Instances holen
										sym		= symtab.GetSymbol(datastack.Pop());
										sym2	= symtab.GetSymbol(datastack.Pop());
										sym	   -> SetOffset( sym2->GetOffset() );
										break;

			default					:	Error(zSTRING("Error DoStack."));
										break;
		}
	} while (token!=zPAR_TOK_RET);
}

// *******************************************************************************************
// PCODE - EXECUTION -> PUBLIC
// *******************************************************************************************

void* zCParser :: CallFunc (const zSTRING &s)
{
	// Variable Params disabled, machte Aerger, funktioniert nur noch bei CallFunc(index)
	return CallFunc(symtab.GetIndex(s));
}

void* zCParser :: CallFunc (int index, ...)
{
	static int retval = 0;

	int* adr;
	int v,i,pos;
	float f;
	zSTRING s;
	va_list args;

	retval = 0;
	zCPar_Symbol *par,*sym = symtab.GetSymbol(index);
	if ((!sym) || (sym->type!=zPAR_TYPE_FUNC)) {
		Message(zSTRING("Warning : Engine calls an undefined function. (index : ")+zSTRING(index)+" )");
		return &retval;
	}
	
	// Get Parameters
	par = sym;

	datastack.Clear();

	va_start(args,index);
	for (i=0; i<sym->ele; i++) {
		//par = sym->GetNext();
		par = GetSymbol(index+i+1);
		switch (par->type) {
			case zPAR_TYPE_INT		:	v = va_arg(args,int);
										par -> SetValue(v);
										datastack.Push(v);
										datastack.Push(zPAR_TOK_PUSHINT);
										break;
			case zPAR_TYPE_FLOAT	:	f = va_arg(args,float);
										par -> SetValue(f);
										datastack.Push(f);
										datastack.Push(zPAR_TOK_PUSHINT);
										break;
			case zPAR_TYPE_STRING	:	s = (zSTRING) va_arg(args,zSTRING);
										par -> SetValue(s);
										adr	= (int *)sym -> GetDataAdr(0);
										datastack.Push((int)adr);
										datastack.Push(zPAR_TOK_PUSHVAR);
										break;
//			case zPAR_TYPE_INSTANCE :	v = va_arg(args,int);
//										datastack.Push(v);
//										datastack.Push(zPAR_TOK_PUSHINT);
//										break;
			default					:	Error(zSTRING("Function type not supported. ("+sym->name+")"));
										break;
		}
	}
	va_end(args);
	
	curfuncnr		= index;

	sym->GetStackPos(pos);
	DoStack(pos);
	// Return Value
	if (sym->HasFlag(zPAR_FLAG_RETURN)) {
		// Expect an Int
		// Use the offset Var as return type -> sym -> SetOffset(type);
		if (sym->GetOffset()==zPAR_TYPE_INT) {
			retval = PopDataValue();
		} else if (sym->GetOffset()==zPAR_TYPE_FLOAT) {
			retval = PopDataValue();
		}
	}

	curfuncnr = -1;
	return &retval;
}

int zCParser :: GetCurrentFunc()
{	
	return curfuncnr;
}

zBOOL zCParser :: CreateInstance (zSTRING &s, void* adr)
{
	s.Upper();
	return CreateInstance(symtab.GetIndex(s),adr);
}

zBOOL zCParser :: CreateInstance (int index, void* adr)
{
	int pos;
	zCPar_Symbol* sym = symtab.GetSymbol(index);
	if ((!sym) || (sym->type!=zPAR_TYPE_INSTANCE)) return FALSE;

	// Init Offset
	sym	-> SetOffset(int(adr));
	zCPar_Symbol :: SetUseInstance(sym);
	sym -> GetStackPos (pos);
	DoStack	 (pos);
	return TRUE;
}

zBOOL zCParser :: CreatePrototype (zSTRING &s, void* adr)
{
	return CreatePrototype(symtab.GetIndex(s),adr);
}

zBOOL zCParser :: CreatePrototype (int index, void* adr)
{
	int pos;
	zCPar_Symbol* sym = symtab.GetSymbol(index);
	if ((!sym) || (sym->type!=zPAR_TYPE_PROTOTYPE)) return FALSE;

	sym	-> SetOffset(int(adr));
	zCPar_Symbol :: SetUseInstance(sym);
	sym -> GetStackPos (pos);
	DoStack	 (pos);
	return TRUE;
}

// *******************************************************************************************
// HELPER & INFORMATION METHODS
// *******************************************************************************************

void zCParser :: Reset()
{
	self			= NULL;
	compiled		= FALSE;
	datsave			= TRUE;
	parse_changed	= FALSE;				// Wurden einzelne D-Files reparsed ?
	mergemode		= FALSE;
	linkingnr		= -1;					// Welches File wird gelinkt ?
	linec			= 0;					// Aktuelle Zeile
	line_start		= 0;					// Filepos der letzten Zeile
	ext_parse		= FALSE;				// Anderer Parsemode : 2 Adr ueberschreibt 1.
	pc_start		= NULL;					// StartAdresse
	pc				= NULL;
	oldpc			= NULL;					// Aktuelle Fileposition ( Adresse )
	pc_stop			= NULL;
	oldpc_stop		= NULL;					// End Of File
	params			= FALSE;				// Parameterleiste abarbeiten
	in_funcnr		= -1;
	in_classnr		= -1;
	stringcount		= 10000;				// Anzahl "loser" Strings (ab 10000)
	in_func			= NULL;					// Aktuelle Funktion
	in_class		= NULL;					// Aktuelle Klasse
	error			= FALSE;
	stop_on_error	= TRUE;
	errorline		= 0;
	prevword_nr		= 0;
	instance		= -1;
	instance_help	= -1;					// Wird benutzt, um Instanzen zu uebergeben
	tree			= NULL;
	treenode		= NULL;
	win_code		= NULL;
	debugmode		= FALSE;
	curfuncnr		= -1;					// Aktuelle Funktion	
	labelcount		= 0;
	labelpos		= NULL;
	add_created		= FALSE;
	msgfunc			= NULL;

	memset	(prevword_index,0,sizeof(prevword_index));
	memset	(prevline_index,0,sizeof(prevline_index));

	// Remove Files from List
	for		(int i=0; i<file.GetNumInList(); i++) delete file[i];
	file.EmptyList();

	symtab   .Clear	();
	stringtab.Clear	();
	stack	 .Clear	();
	datastack.Clear	();
	
	SetProgressBar	(0);
	EnableTreeLoad	(FALSE);
	EnableTreeSave	(FALSE);
	CreateHelpers	();
}

void zCParser::SetPercentDone(int percent)
{
	if (progressBar) progressBar->SetPercent(percent);
};

void zCParser :: CreateHelpers()
// Erzeuge die INSTANCE_HELP, die benutzt wird um Instanzen 
// aus Externals als Rueckgabewert zu uebergeben
{
	// Insert INSTANCE_HELP
	zCPar_Symbol *sym = zNEW( zCPar_Symbol() );
	sym -> name = char(255)+zSTRING("INSTANCE_HELP");
	sym -> type = zPAR_TYPE_INSTANCE;
	sym -> ele  = 1;
	symtab.Insert(sym);
	instance_help = symtab.GetIndex(sym);
}

void zCParser :: EnableTreeSave(zBOOL f)
{
	treesave = f;
}

void zCParser :: EnableDatSave(zBOOL f)
{
	datsave = f;
}

void zCParser :: EnableTreeLoad(zBOOL on)
{
	treeload = on;
}

int zCParser :: GetIndex ( const zSTRING &s )
{
	zSTRING s2 = s;
	s2.Upper();
	return symtab.GetIndex(s2);
}

zBOOL zCParser :: MatchClass (int symbol, const zSTRING &name)
{
	int cindex	= GetIndex	  (name);
	int index	= GetBaseClass(symbol);
	return ((cindex>=0) && (cindex==index));
}

int zCParser :: GetBaseClass (zCPar_Symbol *sym)
// Ermittelt Klasse des angegebenen Objektes
{
	if (!sym) return -1;
	if (sym->type==zPAR_TYPE_INSTANCE)	sym  = sym -> GetParent();
	if ((sym) && (sym->type==zPAR_TYPE_PROTOTYPE)) sym  = sym -> GetParent();
	
	if (sym) return symtab.GetIndex(sym->name);
	else	 return -1;	
}

int zCParser :: GetBaseClass (int nr)
// Ermittelt Klasse des angegebenen Objektes
{
	zCPar_Symbol *sym = GetSymbol(nr);
	if (!sym) return -1;
	if (sym->type==zPAR_TYPE_INSTANCE)	sym  = sym -> GetParent();
	if (sym->type==zPAR_TYPE_PROTOTYPE) sym  = sym -> GetParent();
	
	if (sym) return symtab.GetIndex(sym->name);
	else	 return -1;	
}

int zCParser :: GetBase	 ( int nr )
{
	zCPar_Symbol *sym = symtab.GetSymbol(nr);
	if (!sym) return -1;
	if ((sym->type==zPAR_TYPE_PROTOTYPE) || (sym->type==zPAR_TYPE_INSTANCE)) {
		sym  = sym -> GetParent();
		return symtab.GetIndex(sym->name);
	}
	return -1;
}

int zCParser :: GetPrototype ( int classid, int pos )
{
	zCPar_Symbol *sym, *par = symtab.GetSymbol(classid);
	if (!par) return -1;

	for (int i=pos; i<symtab.GetNumInList(); i++) {
		sym = symtab.GetSymbol(i);
		if ((sym->type==zPAR_TYPE_PROTOTYPE) && (sym->GetParent()==par)) return(i);
	}
	return -1;
}

int zCParser :: GetInstance ( int classid, int pos )
{
	zCPar_Symbol *sym, *par = symtab.GetSymbol(classid);
	if (!par) return -1;

	for (int i=pos; i<symtab.GetNumInList(); i++) {
		sym = symtab.GetSymbol(i);
		if ((sym->type==zPAR_TYPE_INSTANCE) && (sym->HasFlag(zPAR_FLAG_CONST))) {
			if (sym->name.Search(".")>=0) continue;
			
			// Bei Prototype -> Den weiteren Parent ersetzen
			zCPar_Symbol *p2 = sym->GetParent();
			if (!p2) continue;	// INSTANCE_HELP 
			if (p2->type == zPAR_TYPE_PROTOTYPE) p2 = p2 -> GetParent();
			if (p2==par) return(i);
		}
	}
	return -1;
}

zSTRING zCParser :: GetSymbolInfo ( int nr, int &typ, int &ele )
{
	zCPar_Symbol *sym = symtab.GetSymbol(nr);
	if (!sym) {
		typ = zPAR_TYPE_VOID;
		ele = -1;
		return "";
	}
	typ = sym->type;
	ele = sym->ele;
	return (sym->name);
}

zCPar_Symbol* zCParser :: GetSymbolInfo ( int nr )
{
	return (symtab.GetSymbol(nr));
}

zCPar_Symbol* zCParser :: GetSymbol ( int nr )
{
	return (symtab.GetSymbol(nr));
}

zCPar_Symbol* zCParser :: GetSymbol ( const zSTRING &s )
{
	zSTRING s2 = s;
	s2.Upper();
	return (symtab.GetSymbol(s2));
}

zSTRING zCParser :: GetClassVarInfo ( int cli, int nr, int &typ, int &ele)
{
	zSTRING s;
	zCPar_Symbol *var,*cl = symtab.GetSymbol(cli);

	typ = -1;
	ele	= -1;

	if ((!cl) || (cl->type!=zPAR_TYPE_CLASS)) return s;
	
	var = cl;
	for (int i=0; i<nr; i++) {
		if (var) var = var -> GetNext();
	}
	
	if ((var) && (var->HasFlag(zPAR_FLAG_CLASSVAR))) {
		typ = var->type;
		ele = var->ele;
		s   = var->name;
		int p = s.Search(".");
		s   = s.Copied(p+1,255);
	}
	return s;
}

void zCParser :: GetClassVarInfo ( int cli, zSTRING &s, int &typ, int &ele)
{
	s.Upper();
	zSTRING n;
	zCPar_Symbol *var,*cl = symtab.GetSymbol(cli);
	typ = -1;	ele	= -1;
	if ((!cl) || (cl->type!=zPAR_TYPE_CLASS)) return;
	
	n = cl->name + "." + s;
	var = symtab.GetSymbol(n);

	if ((var) && (var->HasFlag(zPAR_FLAG_CLASSVAR))) {
		typ = var->type;
		ele = var->ele;
	}
}

zSTRING zCParser :: GetText	(zSTRING &id,int array)
// Get a Text of Symbol
{
	return GetText (symtab.GetIndex(id,array));
}

zSTRING zCParser :: GetText	(int nr,int array)		
{
	zSTRING s;
	zCPar_Symbol *sym = symtab.GetSymbol(nr);
	if ((sym) && (sym->type==zPAR_TYPE_STRING)) sym->GetValue(s,array);
	return s;
}

int zCParser :: GetInt (int nr, int array)
{
	int v = 0;
	zCPar_Symbol *sym = symtab.GetSymbol(nr);
	if ((sym) && (sym->type==zPAR_TYPE_INT)) sym->GetValue(v,array);
	return v;
}

zSTRING zCParser :: GetInstanceValue( zSTRING &cl, int nr, void* adr, int array)
{
	int cindex = GetIndex(cl);
	return GetInstanceValue(cindex,nr,adr,array);
}

zSTRING zCParser :: GetInstanceValue( int cindex, int nr, void* a, int array)
{
	zBYTE* adr = (zBYTE*) a;
	zSTRING s;
	zCPar_Symbol *sym,*var,*parent = symtab.GetSymbol(cindex);
	if ((!parent) || (parent->type!=zPAR_TYPE_CLASS)) return s;
	if (nr>=parent->ele) return s;

	var = parent;
	for (int i=0; i<parent->ele; i++) {
		var = var->GetNext();
		switch (var->type) {
			case zPAR_TYPE_INT		:	return (zSTRING( *(int *)(adr + var->GetOffset()) ));
										break;
			case zPAR_TYPE_FLOAT	:	return (zSTRING( *(float *)(adr + var->GetOffset()) ));
										break;
			case zPAR_TYPE_STRING	:	return ("\"" + *(zSTRING  *)(adr + var->GetOffset()) + "\"" );
										break;
			case zPAR_TYPE_FUNC		:	nr  = *(int *)(adr + var->GetOffset());
										sym = symtab.GetSymbol(nr);
										if (sym) return sym->name;
										break;
		}

	}
	return s;
}

zBOOL zCParser :: IsValid ( zSTRING &cla, void *data, zSTRING &p )
{
	int w = 0;
	zSTRING e = p + ";";
	cla.Upper();
	zCPar_Symbol *cl = symtab.GetSymbol(cla);
	if ((!cl) || (cl->type!=zPAR_TYPE_CLASS)) return FALSE;
	
	error = FALSE;
	
	zCPar_Symbol :: SetUseInstanceAdr (data);

	in_class = cl;
	pc		 = e.ToChar();
	pc_stop  = pc + e.Length() + 1;

	zCPar_TreeNode *tree = NULL;
	tree = ParseExpression();
	if ((tree) && (!error)) {
		w = EvalLeaf(tree);
	}
	return (w>0);
}


zBOOL zCParser :: CheckClassSize (zSTRING &s, int size)
{
	return CheckClassSize(GetIndex(s),size);
}

zBOOL zCParser :: CheckClassSize (int index, int size)
{
	zCPar_Symbol *sym = symtab.GetSymbol(index);
	if ((!sym) || (sym->type!=zPAR_TYPE_CLASS)) return FALSE;
	if (sym->GetOffset()!=size) {
		zSTRING s = "Class - size not compatible : "+sym->name +"\n";
		s += "CPP - size : " + zSTRING(size) + "\n";
		s += "Script - size : " + zSTRING(sym->GetOffset());
		Error(s,-1);
	}
	return (sym->GetOffset()==size);
}

void zCParser :: AddClassOffset (zSTRING &s, int newOffset)
{
	zCPar_Symbol *sym = symtab.GetSymbol(s);
	if ((!sym) || (sym->type!=zPAR_TYPE_CLASS)) return;

	if (compiled) {
		// Überprüfen, ob sich der Klassenoffset geaendert hat 
		// -> nicht die Größe der Parserdaten (CheckClassSize)
		if (sym->GetClassOffset() != newOffset) {
			Error(zSTRING("Dat-File is not compatible (Classoffset changed) ! Please reparse !"),-1);
		}
		return;
	}

	// Set New ClassOffset
	sym->SetClassOffset(newOffset);

	int ele = sym->ele;
	for (int i=0; i<ele; i++) {
		sym = sym -> GetNext();
		if (sym->HasFlag(zPAR_FLAG_CLASSVAR)) {
			sym->SetOffset(sym->GetOffset() + newOffset);
		}
	}
}

static zCPar_Symbol* s_heroSym = 0;
zBOOL zCParser :: SetInstance (const zSTRING &s, void* adr)
{
	zCPar_Symbol* sym = GetSymbol(s);

	if (s=="HERO" && s_heroSym==0) 
	{
		s_heroSym = sym;
	}

	if ((!sym) || (sym->type!=zPAR_TYPE_INSTANCE)) return FALSE;
	sym	-> SetOffset(int(adr));
	return TRUE;	
}

zBOOL zCParser :: SetInstance (int index, void* adr)
{
	zCPar_Symbol* sym = symtab.GetSymbol(index);
	if ((!sym) || (sym->type!=zPAR_TYPE_INSTANCE)) return FALSE;
	sym	-> SetOffset(int(adr));
	return TRUE;	
}

/*
// Auto completion for symbolnames
zBOOL zCParser :: AutoCompletion ( zSTRING &s )
{
        zBOOL found = FALSE;  // was there another matching symbol?
        int pos = -1;
        int z = 0;
        while (z<symtab.GetNumInList())
        {
                // accept the symbol
                zCPar_Symbol* actualSymbol = symtab.GetSymbol(z);
                zBOOL accept = TRUE;
                if (actualSymbol->type != zPAR_TYPE_INSTANCE) accept = FALSE;
                else if (s.Length()>actualSymbol->name.Length()) accept = FALSE;
                else
                {
                        int z_acc = 0;
                        while (z_acc<s.Length() && accept==TRUE)
                        {
                                if (s[z_acc]!=actualSymbol->name[z_acc]) accept=FALSE; // trivial unaccept
                                z_acc++;
                        }
                }

                if (accept)
                {
                        if(!found)  // first match .. try more
                        {
                                found = TRUE;
                                pos = z;
//                                z++;
                        }
                        else return FALSE; // second match -> no completion
                }
				z++;
		} // while

        if (!found) return FALSE;  // no Match at all
        else 
        {
                s = symtab.GetSymbol(pos)->name;
                return TRUE;
        }
}
*/ 

zBOOL zCParser :: AutoCompletion( zSTRING &s )
{
	int found = 0;
	zSTRING founds;
	zCPar_Symbol *sym;
	for (int i=0; i<symtab.GetNumInList(); i++) {
		sym = GetSymbol(i);
		if ((sym) && (sym->type==zPAR_TYPE_INSTANCE)) {
			if (sym->name.Search(s)==0) {
				found++;
				founds = sym->name;
				if (found>1) return FALSE;
			}
		}
		// Da sortiert, abbrechen
		// if (sym->name[0]>s[0]) break;
	}
	if (found==1) s = founds;
	return (found==1);
}

// *******************************************************************************************
// FILE - INFO
// *******************************************************************************************

int zCParser :: GetNumFiles ()
{
	return file.GetNumInList();
}

zSTRING zCParser :: GetFileName (int nr)
{
	if (nr < GetNumFiles()) {
		return file[nr]->GetName();
	}
	return "";
}

zBOOL zCParser :: IsStackFull()
{
	return stack.ReachedEnd();
}

int zCParser :: GetLastErrorLine()
{
	return errorline;
}

void zCParser :: Reparse (zSTRING &s)
{
	for (int i=0; i<GetNumFiles(); i++) {
		if (s==GetFileName(i)) {
			file[i]->EnableTreeLoad(FALSE);
			// Found, parse it
			ParseFile(s);
			file[i]->EnableTreeLoad(FALSE);
			return;
		}
	}
}

// *******************************************************************************************
// CONSOLEN - KRAM
// *******************************************************************************************

zBOOL zCParser :: SaveInstance(zSTRING &s, void* adr)
{
	s.Upper();
	return SaveInstance(symtab.GetIndex(s),adr);
}

zBOOL zCParser :: SaveInstance(int index, void* adr)
{
	// Check, if Parse-Data available
	if (file.GetNumInList()<=0) return FALSE;
	
	zSTRING newLine = zSTRING(char(0x0d)) + zSTRING(char(0x0a));

	zBOOL dowr;
	int val;
	float fval;
	zBYTE *ptr;
	zSTRING s,res,hlp;
	zCPar_Symbol *ref, *proto = NULL, *var, *sym = symtab.GetSymbol(index);
	if ((!sym) || (sym->type!=zPAR_TYPE_INSTANCE)) return FALSE;

	// Get the BaseClass
	int base = GetBase(index);
	zCPar_Symbol *parent = symtab.GetSymbol(base);
	if (parent->type==zPAR_TYPE_PROTOTYPE) {
		proto  = symtab.GetSymbol( base );
		parent = symtab.GetSymbol( GetBase(base) );
	}
	var = parent;

	// FIXME : Korrektes File schnappen
	zoptions->ChangeDir(DIR_SCRIPTS);
	
	// Blocklaenge ermitteln
	int l1,l2,fpos,flen;
	sym -> GetLineData(l1,l2,fpos,flen);
	if ((fpos<0) || (flen<=0)) return FALSE;

	s = "INSTANCE "+sym->name+" (";
	if (proto)	s+=proto->name;
	else		s+=parent->name;
	s+=")"+newLine+"{"+newLine;

	int lines = 2;
	// Jetzt FileVars
	for (int i=0; i<parent->ele; i++) {
		var = var -> GetNext();
		// Ptr auf naechte Daten
		ptr	= ((zBYTE *)adr + var->GetOffset());
		// Varname holen
		zSTRING  name	= var->name;
		int p			= name.Search(".");
		if (p>0) name	= var->name.Copied(p+1,255);
		name.Lower();

		for (int n=0; n<var->ele; n++) {
			res = "     " + name;
			if (var->ele>1) res +="["+zSTRING(n)+"]";
			res += " = ";
			switch (var->type) {
				case zPAR_TYPE_INT		:	val  = *(int *)ptr;
											res += zSTRING(val);		
											ptr += sizeof(int);
											dowr = (val!=0);
											break;
				case zPAR_TYPE_FLOAT	:	fval = *(float *)ptr;
											res += zSTRING(fval);
											dowr = (fval!=0);
											ptr += sizeof(float);
											break;
				case zPAR_TYPE_STRING	:	hlp = *(zSTRING *)ptr;
											res += "\"" + hlp + "\"";
											dowr = (hlp!="");
											ptr += sizeof(zSTRING);
											break;
				case zPAR_TYPE_FUNC		:	val  = *(int *)ptr;
											ref  = symtab.GetSymbol(val);
											if ((val>0) && (ref))	res += ref->name;
											dowr = ((val>0) && (ref));
											ptr += sizeof(int);
											break;			
			}
			res += ";"+newLine;
			if (dowr) {
				s += res;
				lines++;
			}
		}
	}
	s +="};"+newLine;
	lines++;

	int fnr = sym->GetFileNr();
	if ((fnr>=file.GetNumInList()) || (fnr<0)) return FALSE;

	zoptions->ChangeDir(DIR_SCRIPTS);
	zFILE *f = zfactory->CreateZFile(file[fnr]->GetName());
	f->UpdateBlock(s,fpos,l2);
	f->Close();
	delete(f);
	
	// Deltas ermitteln
	int delta_line	= lines - l2;
	int delta_pos	= (s.Length() - flen);
	//zERR_MESSAGE(0,0,"U:PAR: Offset :"+zSTRING(delta_pos));

	// Die Laenge des geaenderten Symboles setzen ( LineAnzahl + Filepos )
	sym -> SetLineData(l1,lines,fpos,flen + delta_pos);
	
	// Bei allen folgenden Symbolen muss korrigiert werden :
	// a) die Line
	// b) die Filepos

	// Deltas auf alle weiteren Positionen addieren
	int ls1,ls2,lp1,lp2;
	int cur_fpos	= fpos;
	i = index+1;
	do {
		sym = GetSymbol(i);
		if (sym) {
			sym -> GetLineData(ls1,ls2,lp1,lp2);
			if (lp1 > cur_fpos) {
				// Noch grösser, also valid
				sym -> SetLineData(ls1 + delta_line, ls2, lp1 + delta_pos, lp2);
				cur_fpos = lp1;
			} else
				break;
		} else
			break;
		i++;
	} while (1);
	return TRUE;
}

void zCParser :: CloseViews ()
{
	if (win_code!=NULL) screen->RemoveItem(win_code);
	debugmode = FALSE;
}

void zCParser :: ShowCode( int index )
{
	int adr = 0;
	zCPar_Symbol *sym = symtab.GetSymbol(index);
	if (sym) {
		switch (sym->type) {
			case zPAR_TYPE_INSTANCE		:	sym -> GetStackPos(adr);	break;
			case zPAR_TYPE_FUNC			:	sym -> GetStackPos(adr);	break;
		}
	}
	int zeilen = screen->FontY()*10;
	int y	   = screen->FontY()*6;
	if (!win_code) {
		win_code =  zNEW( zCView	(0000,y,8191,y+zeilen+screen->FontY()*2));
		screen   -> InsertItem		(win_code);
		win_code -> ClrFlags		(VIEW_TXT_CENTER);
	}
	if (!win_code -> IsVisible()) screen->InsertItem(win_code); 
//	win_code -> Clear(GFX_BLACK);
//	win_code -> InsertHandleEvent(IA_ShowCode);
//	win_code -> Top();
	debugmode = TRUE;
	ShowPCode(adr,win_code);
}

void zCParser :: SaveInfoFile(zSTRING name)
{
	zSTRING s;
	zFILE *f = zfactory->CreateZFile(name);
	f->Create();
	f->Write(zSTRING("// ***  Externals  ***\n\n"));

	zCPar_Symbol *sym,*var;
	// Durchsuche Symbole nach Externals
	for (int i=0; i<symtab.GetNumInList(); i++) {
		sym = GetSymbol(i);
		if (sym->HasFlag(zPAR_FLAG_EXTERNAL)) {
			
			s	= "FUNC ";
			// Return Symbol
			if (sym->HasFlag(zPAR_FLAG_RETURN)) {
				int rettype = sym->GetOffset();
				switch (rettype) {
					case zPAR_TYPE_INT		:	s += "INT";			break;
					case zPAR_TYPE_FLOAT	:	s += "FLOAT";		break;
					case zPAR_TYPE_STRING	:	s += "STRING";		break;
					case zPAR_TYPE_INSTANCE	:	s += "INSTANCE";	break;
				}
			} else s += "VOID";
			s += " " + sym->name + " ( ";

			var = sym;
			for (int n=0; n<sym->ele; n++) {
				var = GetSymbol(i+n+1);;
				switch (var->type) {
					case zPAR_TYPE_INT		:	s += "VAR INT i";		break;
					case zPAR_TYPE_FLOAT	:	s += "VAR FLOAT r";		break;
					case zPAR_TYPE_STRING	:	s += "VAR STRING s";	break;
					case zPAR_TYPE_FUNC		:	s += "VAR FUNC f";		break;
					case zPAR_TYPE_INSTANCE	:	s += "VAR INSTANCE n";	break;				
				}
				s+=zSTRING(n);
				if (n+1<sym->ele)	s += ", ";
			}
			s += " ) { ";
			if (sym->HasFlag(zPAR_FLAG_RETURN)) s+="return 0; ";
			s+="};";
			f->Write(s+"\n");
		}
	}
	
	f->Close();
	delete(f);
}

// ************************ Create Additional Info for Spacer *********************

void zCParser :: SetInfoFile ( zCList <zSTRING>* funclist, const zSTRING &f )
{
	add_funclist	= funclist;
	add_filename	= f;
	add_created		= FALSE;
}

zBOOL zCParser :: IsInAdditionalInfo ( const zSTRING &s )
{
	if (!add_funclist) return FALSE;

	zSTRING cmp;
	zCList <zSTRING> *ele = add_funclist->GetNextInList();
	while (ele) {
		cmp = ele -> GetData();
		cmp.Upper();
		if (cmp==s) return TRUE;
		ele = ele -> GetNextInList();
	}
	return FALSE;
}

zBOOL zCParser :: WriteAdditionalInfo ( zSTRING &call, int zeile, int filepos)
{
	// Aktuelles Directory merken
	zFILE_FILE	olddir;
	zSTRING tmp		= olddir.SetCurrentDir();
	zoptions->ChangeDir (DIR_COMPILED_SCRIPTS);
	zFILE*	f		= zfactory->CreateZFile(add_filename);
	
	if (!add_created) {
		// Create File
		f -> Create();
		add_created = TRUE;
	} else {
		f -> SetBuffering(FALSE);
		f -> Open(TRUE);
		f -> Append();
	}
	
	f->Write ("FILE   { "+fname+" }\n");
	f->Write ("SYMBOL { "+call+" }\n");
	f->Write ("LINE   { "+zSTRING(zeile)+" }\n");
	f->Write ("FILEPOS{ "+zSTRING(filepos)+" }\n\n");
	f->Close ();
	delete(f);
	olddir.ChangeDir ();
	return TRUE;
}

zBOOL zCParser :: ClearAllInstanceRefs()
{
	zCPar_Symbol* sym = NULL;
	for (int i=0; i<symtab.GetNumInList(); i++) {
		sym = symtab.GetSymbol(i);
		if (sym && (sym->type==zPAR_TYPE_INSTANCE)) {
			SetInstance(i,NULL);
		}
	}
	return TRUE;
}

zBOOL zCParser :: ClearInstanceRefs(void* instancePtr)
{
	zCPar_Symbol* sym = NULL;
	for (int i=0; i<symtab.GetNumInList(); i++) {
		sym = symtab.GetSymbol(i);
		if (sym && (sym->type==zPAR_TYPE_INSTANCE) && (sym->GetInstanceAdr()==instancePtr)) {
			SetInstance(i,NULL);
		}
	}
	return TRUE;
}

zBOOL zCParser :: ResetGlobalVars()
{
	zCPar_Symbol* sym = NULL;
	for (int i=0; i<symtab.GetNumInList(); i++) {
		sym = symtab.GetSymbol(i);
		if (sym && (sym->type==zPAR_TYPE_INT) && (sym->flags==0) && (sym->ele>0)) {
			// Reinit Vars with zero.
			// [EDENFELD] 1.17: alle globalen felder des int arrays reseten, und nicht nur das erste element
			for (int k=0; k<sym->ele; k++) sym->SetValue(0,k);
		}
	}
	return TRUE;
}

void zCParser :: CreateVarReferenceList(const zSTRING& className, zCArray<int>& refList)
{
	int classIndex = parser.GetIndex(className);
	if (classIndex<0) return;

	zCPar_Symbol* sym = NULL;
	for (int i=0; i<symtab.GetNumInList(); i++) {
		sym = symtab.GetSymbol(i);
		if (sym && (sym->type==zPAR_TYPE_INSTANCE) && (GetBaseClass(sym)==classIndex)) {
			
			refList.Insert(i);
		
		}
	}
};

void zCParser :: ResetWithVarReferenceList	(zCArray<int>& refList, void* ptr)
{
	zCPar_Symbol* sym = NULL;
	for (int i=0; i<refList.GetNumInList(); i++) {
		sym = GetSymbol(refList[i]);
		if (sym && (sym->type==zPAR_TYPE_INSTANCE) && (sym->GetInstanceAdr()==ptr)) {
			SetInstance(refList[i],NULL);
		}
	}
};

zBOOL zCParser :: SaveGlobalVars(zCArchiver& arc)
{
	int				numSymbols	= 0;
	zCPar_Symbol*	sym			= NULL;

	for (int i=0; i<symtab.GetNumInList(); i++) {
		sym = symtab.GetSymbol(i);
		if (sym && (sym->type==zPAR_TYPE_INT) && (sym->flags==0) && (sym->ele>0)) {
			numSymbols++;
		}
	}
	
	zSTRING symValue, symName;
	int				value	= 0;
	int				curNr	= 0;
	arc.WriteInt("numSymbols",numSymbols);
	for (i=0; i<symtab.GetNumInList(); i++) {
		sym = symtab.GetSymbol(i);
		if (sym && (sym->type==zPAR_TYPE_INT) && (sym->flags==0) && (sym->ele>0)) {
			// Name
			symName		= "symName"+zSTRING(curNr);
			arc.WriteString(symName.ToChar(),sym->name);
			arc.WriteInt(zSTRING(symName+"cnt").ToChar(),sym->ele);
			// Value
			for (int k=0; k<sym->ele; k++)
			{
				sym -> GetValue(value,k);
				// [EDENFELD] 1.17: alle globalen felder des int arrays speichern, und nicht nur das erste element

				symValue	= "symValue"+zSTRING(curNr) + zSTRING("_") + zSTRING(k);
				arc.WriteInt(symValue.ToChar(),value);
			}
			curNr++;
			//zERR_WARNING("U:PAR: SG: Writing :"+sym->name+" = "+zSTRING(value));
		}
	}
	return TRUE;
};

zBOOL zCParser :: LoadGlobalVars(zCArchiver& arc)
{
	int numSymbols	= 0;
	arc.ReadInt("numSymbols",numSymbols);
	
	zCPar_Symbol* sym = NULL;
	zSTRING symNameStr,symName;
	// In Gedenken an den kuerzlich verstobenen Ping-Programmierer Mike Muuss
	// benenne ich die Variable fuer die Werte der einzelnen Parser-Symbole nach ihm.
	int	mike_Muuss;			

	for (int i=0; i<numSymbols; i++) 
	{	
		mike_Muuss	= 0;
		symNameStr	= "symName"+zSTRING(i);
		arc.ReadString(symNameStr.ToChar(),symName);
		sym			= GetSymbol(symName);

		if (sym && (sym->type==zPAR_TYPE_INT) && (sym->flags==0) && (sym->ele>0)) 
		{
			int numEle  = 0;
			arc.ReadInt   (zSTRING(symNameStr+"cnt").ToChar(),numEle);

			for (int k=0; k<numEle; k++)
			{
				symNameStr	= "symValue"+zSTRING(i)+zSTRING("_")+zSTRING(k);
				arc.ReadInt(symNameStr.ToChar(),mike_Muuss);
				sym->SetValue(mike_Muuss,k);
			}
			
			//zERR_WARNING("U:PAR: SG: Reading :"+sym->name+" = "+zSTRING(mike_Muuss));
		}
		else
		{
			symNameStr	= "symValue"+zSTRING(i);
			arc.ReadInt(symNameStr.ToChar(),mike_Muuss);
		}
	}
	return TRUE;
};

#pragma warning ( default:4244 )
