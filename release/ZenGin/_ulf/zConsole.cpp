/******************************************************************************** 
 
     $Workfile:: zConsole.cpp         $                $Date:: 15/11/00 15:25   $
     $Revision:: 20                   $             $Modtime:: 15/11/00 15:16   $
       $Author:: Luesebrink                                                     $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zConsole.cpp $
 * 
 * 20    15/11/00 15:25 Luesebrink
 * 
 * 19    7.11.00 23:41 Hildebrandt
 * 
 * 18    15.09.00 14:10 Wohlers
 * 
 * 17    14.09.00 14:46 Herget
 * 
 * 16    29.08.00 18:19 Moos
 * 
 * 15    22.08.00 19:33 Wohlers
 * 
 * 14    2.08.00 14:25 Wohlers
 * 
 * 13    28.07.00 15:37 Herget
 * 
 * 12    21.07.00 17:54 Herget
 * 
 * 11    21.07.00 15:35 Wohlers
 * 
 * 10    21.07.00 14:43 Wohlers
 * 
 * 9     20.07.00 20:10 Herget
 * 
 * 8     5.07.00 12:23 Wohlers
 * 
 * 7     22.05.00 18:44 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 6     5.05.00 23:36 Wohlers
 * Anpassung ZCView
 * 
 * 5     4.05.00 19:41 Wohlers
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 10    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 8     16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 7     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 6     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 4     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

// disable VC++ Warning: Zuweisung im bedingten Ausdruck


#include "zCore.h"

#include "zview.h"
#include "zOption.h"
#include "zConsole.h"
#include "zParser.h"
#include "zParser_Const.h"
#include "z3d.h"
#include "zInput.h"
#include "zInput_Win32.h"

#pragma warning( disable : 4706 ) 

zCList <zCConsole> zCConsole :: active_consoles;			// Liste der aktiven Konsolen [Moos] etwas nach oben verlegt
zCConsole zcon;

// CODECHANGE [STEFAN]
zCConDat :: zCConDat ( const zSTRING &h, const zSTRING &s, int t, void *a, int e )
// CODECHANGE [STEFAN] END
{
	hint	= h;
	name	= s;
	name.Upper();
	type	= t;
	adr		= a;
	ele		= e;
	// CODECHANGE [STEFAN]
	var		= TRUE;
	// CODECHANGE [STEFAN] END
	next	= NULL;
}

zCConDat :: zCConDat ( const zSTRING &h, const zSTRING &s, int param )
{
	hint	= h;
	name	= s;
	name.Upper();
	type	= param;
	adr		= NULL;
	// CODECHANGE [STEFAN]
	var		= FALSE;
	// CODECHANGE [STEFAN] END
	next	= NULL;
}

zCConsole* zCConsole		 :: cur_console = NULL;

zBOOL zCConsole :: HandleEvent( int key )
{
	if (!cur_console) return FALSE;
	
	zBOOL pressed	= FALSE;
	zBOOL character = TRUE;
	
	// if ((zinput->KeyPressed(KEY_LALT)) || (zinput->KeyPressed(KEY_RALT)) || (zinput->KeyPressed(KEY_LCTRL)) || (zinput->KeyPressed(KEY_RCTRL))) return FALSE;
	
	if ((key==KEY_ESC)	|| (key==KEY_BSLASH) || (key==KEY_F2) || (key==KEY_PGUP) || (key==KEY_PGDN)	|| (key==KEY_DEL)	|| (key==KEY_INS) )
	{
		pressed		= TRUE;
		character	= FALSE;
	}
	else
	{
		key = GetCharFromDIK(key,
			((zinput->KeyPressed(KEY_RSHIFT) || zinput->KeyPressed(KEY_LSHIFT))	? DIK_LSHIFT	: 0),
			(zinput->KeyPressed(KEY_RALT)										? DIK_RMENU		: 0));
		if((key >= 32) && (key <= 255))
			pressed = TRUE;
		if((key == 0x08) || (key == 0x0D))  // Backspace and Enter
		{
			pressed		= TRUE;
			character	= FALSE;
		}
	}

	if (pressed) cur_console -> AddChar ( key, character );
	return pressed;
}

zCConsole :: zCConsole ( )
{
	conview = NULL;
	dynsize = FALSE;
	for (int i=0; i<zCON_MAX_EVAL; i++) evalfunc[i] = NULL;
	skip	= 0;
	var		= FALSE;
	autocomplete = TRUE;
	evalcount	 = 0;
	changedfunc	= NULL;
	cparser	= NULL;
	skip = 0;
		
	active_consoles.Insert(this);
	Register("save infofile","save infofile with current console-commands");
	Register("help","list commands on spy");
}

zCConsole :: zCConsole ( int x, int y, const zSTRING &name )
{
	id		= name;
	px		= x;
	py		= y;
	lx		= 4000;
	ly		= 0;
	conview = NULL;
	dynsize	= TRUE;
	for (int i=0; i<zCON_MAX_EVAL; i++) evalfunc[i] = NULL;
	skip	= 0;
	var		= FALSE;
	autocomplete = TRUE;
	evalcount = 0;
	world	= NULL;
	changedfunc	= NULL;
	cparser	= NULL;
	skip = 0;
	lastCommandPos = 0;

	active_consoles.Insert(this);
};

zCConsole :: ~zCConsole ()
{
	Hide ();
	delete (conview); conview = NULL;
	list.Clear();

	active_consoles.Remove(this);
}

void zCConsole :: SetAutoCompletion(zBOOL f)
{
	autocomplete = f;
}

zBOOL zCConsole :: HasAutoCompletion()
{
	return autocomplete;
}

void zCConsole :: SetWorld		( zCWorld *wld )
{
	world = wld;
}

zCWorld* zCConsole :: GetWorld	( )
{
	return world;
}

void zCConsole :: SetParser		( zCParser *p )
{
	cparser = p;
}

zCParser* zCConsole :: GetParser( )
{
	return cparser;
}

void zCConsole :: AddChar ( int w, zBOOL character )
{
	if (character) {
		if ((w==0x20) && (instr.Length()==0)) return;
		instr += char(w); 
		if (autocomplete) AutoCompletion(instr);
		lastCommandPos = lastcommand.GetNum();

	}
	else switch (w) 
	{
		case  8	:	if (instr.Length()>0) 
					{ 
						instr.Delete(instr.Length()-1,1); 
					}
					lastCommandPos = lastcommand.GetNum();
					break;
		case 0x0D	:	
					instr.Upper();
					if (Evaluate(instr)) 
					{
						if (var) Update();
						if (instr!="") lastcommand.InsertEnd(instr);
						instr="";
					}
					lastCommandPos = lastcommand.GetNum();
					break;
		case KEY_INS	:	
						/*if (lastcommand.GetNum()>0)
						{
							instr = lastcommand[lastcommand.GetNum()-1];
							instr.Lower();
						}*/
						if (lastcommand.GetNum()>0)
						{
							if ((lastCommandPos-1>=0)) lastCommandPos--;
							else break;
							instr = lastcommand[lastCommandPos];
							instr.Lower();
						}
						break;
		case KEY_DEL	:
					instr="";
					lastCommandPos = lastcommand.GetNum();
					break;
		case KEY_ESC	:	case KEY_BSLASH	:	case KEY_F2	:
					Hide();
					SetChangedFunc(NULL);
					return;
		case KEY_PGUP	:
					AddSkip(-1);
					Update();
					break;
		case KEY_PGDN	:
					AddSkip(+1);
					Update();
					break;
		/*case KEY_POS1:
					if (lastcommand.GetNum()>0)
					{
						if ((lastCommandPos-1>=0)) lastCommandPos--;
						else break;
						instr = lastcommand[lastCommandPos];
						instr.Lower();
					}
					break;
		case KEY_END:
					if (lastcommand.GetNum()>0)
					{
						if ( lastCommandPos+1<=lastcommand.GetNum()-1 ) lastCommandPos++;
						else break;
						instr = lastcommand[lastCommandPos];
						instr.Lower();
					}
					break;
*/
	}
	
	ShowInput();
}

// CODECHANGE [STEFAN]
void zCConsole :: InsertVar ( const zSTRING& h, const zSTRING& s, int type, void *adr, int ele )
{
	var = TRUE;
	zCConDat *dat = zNEW( zCConDat(h, s,type,adr,ele));
	list.InsertLast(dat);
}
// CODECHANGE [STEFAN] END

void zCConsole :: Register ( const zSTRING& s, const zSTRING& h, int param)
{
	zCConDat *dat = zNEW( zCConDat(h,s,param) );
	list.InsertLast(dat);
}

void zCConsole :: Register ( const zSTRING& s, const zSTRING& h )
{
	zCConDat *dat = zNEW( zCConDat(h,s,0) );
	list.InsertLast(dat);
}

zBOOL zCConsole :: AutoCompletion ( zSTRING &s )
{
	zBOOL flag = FALSE;
	int found = 0;
	zSTRING founds,word,fword;
	zSTRING check, whole = s;
	whole.Upper();
	zSTRING out;
	zCConDat *f;
	zCConDat *dat = list.wurzel;
	// For any word
	int nr = 1;
	do {
		check  = whole.PickWord(nr," ");
		if (check=="") break;

		dat	   = list.wurzel;	
		while (dat) {
			// Alle vorherigen Woerter gleich ?
			for (int i=1; i<nr; i++) {
				zSTRING w1 = dat->name.PickWord(i," ");
				zSTRING w2 = whole.PickWord(i," ");
				if (w1!=w2) goto _nextdat;
			}
			
			// Anderes Autocomplete ?
			if ((!var) && (!dat->adr) && (dat->type==nr) && (cparser)) {
				flag = cparser->AutoCompletion(check);
				if (flag) {
					check.Lower();
					s = out + check + " ";
				}
				return flag;
			}

			word = dat->name.PickWord(nr," ");			
			if (word.Search(check)==0) {
				if (word!=fword) {
					found++;
					if (found>1) return FALSE;
					f		= dat;
					fword	= word;
				}
			}
_nextdat:
			dat = dat -> next;
		}

		if (found==1) {
			// genau ein Match
			fword.Lower();
			out	 += fword + " ";
			found = 0;
			flag  = TRUE;
			word  = "";
			nr ++;
		
		} else {
			flag  = FALSE;
			break;
		}
	
	} while (1);

	if (flag) {
		s = out;
	// CODECHANGE [STEFAN]
		if (var && f->ele == 1) s += "= ";
	// CODECHANGE [STEFAN] END
	}
	return flag;
}

void zCConsole :: SetFocus()
// Diese Konsole erhält alle Tastaturkommandos
{
	if (cur_console) {
		cur_console->SetEnableHandleEvent(FALSE);
		cur_console = NULL;
	}
	cur_console = this;
	cur_console->SetEnableHandleEvent(TRUE);
	cur_console->SetHandleEventTop();
}

void zCConsole :: RemoveFocus()
// Focus wird von dieser Konsole entfernt -> naechster Focus unbestimmt !
{
	if (cur_console) cur_console->SetEnableHandleEvent(FALSE);
	cur_console = NULL;
	// Suche nächste Konsole in der Liste
	zCConsole* nextcon;
	zCList <zCConsole> *ele = active_consoles.GetNextInList();
	while (ele) {
		nextcon = ele->GetData();
		if ((nextcon!=this) && (nextcon->IsVisible())) {
			nextcon->SetFocus();
			break;
		}
		ele = ele->GetNextInList();
	}
	if ((cur_console==NULL) && (zcon.IsVisible()))
		zcon.SetFocus();

	if (cur_console) cur_console->Update();
}

void zCConsole :: Show ( )
{
	skip	= 0;
	// CODECHANGE [STEFAN]
	showmax = (24 < list.Count()) ? 24 : list.Count();
	// CODECHANGE [STEFAN] END
	if (!conview) {
		int lines = 8192 / screen->FontY();
		// Create Desktop-Item
		if (dynsize) {
			if (showmax+3>lines) showmax = lines-3;
			ly  = screen -> FontY() * (showmax + 3);
		} else {
			if (lx<0) lx = 4000;
			if (ly<0) ly = 2000;
		}
		conview		=  zNEW( zCView		(px,py,px+lx,py+ly) );
		screen		-> InsertItem		(conview);
		conview		-> InsertBack		("CONSOLE.TGA");
		conview		-> ClrFlags			(VIEW_TXT_CENTER);
		conview		-> SetTransparency	(150);
		conview		-> SetAlphaBlendFunc(zRND_ALPHA_FUNC_BLEND);

	} else if (!conview->IsVisible()) {
		
		screen -> InsertItem ( conview );
	}

	SetFocus ();

	int fy		=  conview->FontY();
	conview		-> DefPrintwin(0,0,8191,8191-fy);
	Update();
}

void zCConsole :: Hide ( )
{
	if (conview && conview->IsVisible()) {
		cur_console = NULL;
		screen  -> RemoveItem		( conview );
		RemoveFocus					( );	
	}
}

void zCConsole :: Toggle( )
{
	if (!conview || !conview->IsVisible())
		Show();
	else
		Hide();
}

zBOOL zCConsole :: IsVisible( )
{
	return (conview && conview->IsVisible());
}

void zCConsole :: AddSkip(int dir)
{
	skip += dir;
	if (skip<0) skip = 0;
	if (skip+showmax>list.Count()) skip = list.Count()-showmax; 
}

void zCConsole :: Update ( )
{
	zSTRING**ssptr;
	zSTRING *sptr;
	if (list.Count()<=0) return;

	int x=0, y=0, fy = conview -> FontY();
	zSTRING h,s,res;
	// Redraw Complete Window
	if (!conview) return;

//	conview -> DrawBackground();
	if (id!="") {
//		conview -> Bar(0,0,8191,fy,GFX_BLUE);
		conview -> PrintCX(0,id);
		y += fy;
	}

	zCConDat *dat = list.wurzel;
	for (int i=0; i<skip; i++) if (dat) dat = dat->next;
	
	int c = 0;
	while (dat!=NULL) {
		if (dat->adr) {
			res = "";
			s	= dat->name;
			h	= dat->hint;
			switch (dat->type) {
			case zCON_TYPE_FLOAT	:	res = zSTRING( *(float *)dat->adr );
										break;
			case zCON_TYPE_INT		:	res = zSTRING( *(int *)dat->adr );
										break;
			case zCON_TYPE_STRING	:	sptr = (zSTRING*)dat->adr;
										if (sptr->Length()>0)  res = *(zSTRING *)dat->adr;
										break;
			case zCON_TYPE_STRINGP	:	ssptr = (zSTRING**)dat->adr;
										if (*ssptr!=NULL) res = *(zSTRING **)dat->adr;										
										break;
			}
			
			int xd = 0;
			if (h!="") {
				conview -> Print(x,y,h);
				xd = 4000;
			}
			conview -> Print(x+xd,y,s);
			// CODECHANGE [STEFAN]
			if (dat->ele > 1) {
				conview -> Print(x+6000,y,":  (" + zSTRING(dat->ele) + ")");
			} else {
				conview -> Print(x+6000,y,":  " + res);
			}
			// CODECHANGE [STEFAN] END
			y += fy;

			c++;
			if (c>=showmax) break;
		}
		dat = dat->next;
	}
	if (dynsize) {
//		conview -> SetFontColor		(GFX_YELLOW);
		conview	-> Print			(0,8191 - conview->FontY()*2,savemsg);
//		conview -> SetFontColor		(GFX_WHITE);
	}
	ShowInput();
}

void zCConsole :: ShowInput()
{
	int fy = conview -> FontY();
	zSTRING s = ": "+instr; if (cur_console==this) s+="|";
	conview -> Print	(0,8191-fy,s);
}

zCConDat* zCConsole :: Get ( const zSTRING& what )
{
	zCConDat *dat = list.wurzel;
	zSTRING s = what.PickWord(1," ");
	s.Upper();
	while (dat!=NULL) {
		if (s==dat->name) return dat;
		dat = dat->next;
	}
	return NULL;
}

zCConDat* zCConsole :: GetBestMatch ( const zSTRING& what )
{
	zSTRING h;
	zCConDat *dat = list.wurzel;
	zSTRING s = what;
	s.Upper();
	while (dat!=NULL) {
		h = dat->name.PickWord(1," ");
		if (h.Search(s)>=0) return dat;
		dat = dat->next;
	}
	return NULL;
}

void zCConsole :: Eval ( const zSTRING &s )
{
//	int wp;
	zSTRING w;
	zCConDat *dat = Get(s);
	if (!dat || s.IsEmpty()) return;
	
	int nr = 1;
	do {
		nr ++;
		w = s.PickWord(nr," =");
		if (w=="") return;
	} while (w!="=");

	if (dat->type >= zCON_TYPE_STRING) {
		const char *c = s.PickWordPos(3,"=");
		// Leerzeichen weg
		if (c) {
			while (*c==' ') c++;
			w = zSTRING(c);
		}
	
	} else
		w = s.PickWord(nr+1," =");

	switch (dat->type) {
		case zCON_TYPE_FLOAT	:	*(float *)	dat->adr = w.ToFloat(); 
									break;
		case zCON_TYPE_INT		:	*(int *)	dat->adr = w.ToInt(); 
									break;
		case zCON_TYPE_STRING	:	*(zSTRING *)dat->adr = w;
									break;
		case zCON_TYPE_STRINGP	:	**((zSTRING **)dat->adr) = w;
									break;
	}

	// Call ChangedFunc
	if (changedfunc) changedfunc(dat->name);
}

/* ----------------------------------------------------------------------
	
    zCConsole:: Evaluate()	

	29.08.2000	[Moos]	
                Leak beseitigt
	 7.11.2000	[HILDEBRANDT]
				Abfrage auf Schluesselwort "help":
				Eine Abfrage "ist enthalten in" reicht hier nicht: sonst duerfte 
				ja kein anderes Kommando das Wort "help" in sich tragen! Loesung:
				genauer Vgl.
   ---------------------------------------------------------------------- */


zBOOL zCConsole :: Evaluate ( const zSTRING &s )
{
	savemsg.Clear();

	if (s.IsEmpty()) return FALSE;

	zCConDat *dat;
	zSTRING msg;

	// CODECHANGE [STEFAN]
	if (var && (s.Search("=")>0) && (dat = Get(s)) && (dat->ele == 1)) {
	// CODECHANGE [STEFAN] END
		Eval(s);
		return TRUE;
	}
	
	// CODECHANGE [STEFAN]
	if (var && (dat = Get(s)) && (dat->ele > 1)) {
		void *adr = dat->adr;
		int type = dat->type;
		int ele = dat->ele;

		for (int j = list.Count(); j > 0; j--)
			if (list.Get(j) != NULL)
				if (list.Get(j)->var)
					list.Delete(list.Get(j)); // [Moos] (war Remove)

		// Register("close","close array view");

		zSTRING nix;
		int size;

		dynsize = TRUE;
		lx		= 4000;
		ly		= 0;
		// id		= sym->name + "(" + parent->name + ") - " + dat->name;
		
		switch (type) {
		case zCON_TYPE_INT: size = sizeof(int); break;
		case zCON_TYPE_FLOAT: size = sizeof(float); break;
		case zCON_TYPE_STRING: size = sizeof(zSTRING); break;
		}

		for (int i=0; i<ele; i++) {
			zSTRING s(i);
			InsertVar	(nix,s,type,(void *)((zBYTE *)adr + i * size));
		}

		Hide();
		Show();

		return TRUE;
	}

	if (evalfunc[0]) {
	// CODECHANGE [STEFAN] END
		msg = "";
		zBOOL f = FALSE;

		if (s.Search("SAVE INFOFILE")>=0) {
			// Save Info-File
			SaveInfoFile("Readme_Console.txt");
			msg = "File saved (DIR_CONFIG : Readme_Console.txt)";
		
		} else if ((s=="HELP") || (s=="HELP "))	// eine Abfrage "ist enthalten in" reicht hier nicht: sonst duerfte ja kein anderes Kommando das Wort "help" in sich tragen!!! [HILDEBRANDT]
		{
			ShowHelp();
		
		} else {
		
			// No Match. Calling EvalFunc 
			int nr = 0;
			do {
				f = (evalfunc[nr](s,msg));
				nr++;
			} while (!f && (nr<zCON_MAX_EVAL) && evalfunc[nr]);
		}
		
		if (msg!="") {
			if ((!dynsize && conview)) {
//				conview -> SetFontColor (GFX_YELLOW);
				conview -> Printwin(msg+"\n");
//				conview -> SetFontColor (GFX_WHITE);
			}
			savemsg = msg;
		}
		return TRUE;
	}			
	return TRUE;
}

void zCConsole :: SetPos (int x1,int y1)
{
	px = x1;
	py = y1;
}

void zCConsole :: SetDim (int sx,int sy)
{
	lx = sx;
	ly = sy;
	dynsize = FALSE;
}

void zCConsole :: SetFlags( int fl )
{
	conview -> Setflags(fl);
}

void zCConsole :: AddEvalFunc( zBOOL (*ev)(const zSTRING &s, zSTRING &msg) )
{
	if (evalcount+1 < zCON_MAX_EVAL) evalfunc[evalcount++] = ev;
}

void zCConsole :: SetChangedFunc( void (*cf)(const zSTRING &s) )
{
	changedfunc = cf;
}

void zCConsole :: ShowHelp()
{
	zERR_MESSAGE(0,0,"U:CON: console commands:");
	zCConDat *dat = list.wurzel;
	while (dat) {
		zERR_MESSAGE(0,0,"U:CON: "+dat->name+ "   : " + dat->hint);
		dat = dat -> next;
	}
}

void zCConsole :: SaveInfoFile(const zSTRING& s)
{
	int numtab;
	zSTRING tabs;
	zoptions->ChangeDir(DIR_SYSTEM);

	zFILE* f = zfactory->CreateZFile(s);
	f->Create();

	zCConDat *dat = list.wurzel;
	while (dat) {
		tabs = "";
		numtab = 3 - (dat->name.Length() / 8);
		for (int i=0; i<numtab;i++) tabs += char(9);
		f->Write(dat->name + tabs + ": " + dat->hint + "\n");
		dat = dat -> next;
	}
	f->Close();
	delete(f);
}

zBOOL zCConsole :: EditFunc(const zSTRING &s, zSTRING &mess)
// STATIC !
{
	if (!cur_console) return FALSE;
	zCParser *p = cur_console -> GetParser();
	zSTRING w1 = s.PickWord(1," ");	w1.Upper();
	if (w1=="SAVE") {
		if (p->SaveInstance(cur_console->edit_index,cur_console->edit_adr)) 
			mess="Saved,";
		else
			mess="Save failed.";
	}
	return TRUE;
}

zBOOL zCConsole :: EditInstance(const zSTRING &s, void* adr)
{
	zCParser *p = GetParser();
	if (!p) return FALSE;
	return EditInstance(p->GetIndex(s),adr);
}

zBOOL zCConsole :: EditInstance(int index, void* adr)
{
	if (!adr)	return FALSE;

	zCParser *p = GetParser();
	if (!p)		return FALSE;

	zSTRING nix;

	int t;
	zCPar_Symbol *parent, *var, *sym = p->GetSymbol(index);
	if ((!sym) || (sym->type!=zPAR_TYPE_INSTANCE)) return FALSE;

	// Get the BaseClass
	int base = p->GetBaseClass(index);
	parent	 = p->GetSymbol(base);
	var		 = parent;

	dynsize = TRUE;
	lx		= 4000;
	ly		= 0;
	id		= sym->name + "(" + parent->name + ")";
	
	edit_index = index; edit_adr = adr;
	for (int i=0; i<parent->ele; i++) {
		t = -1;
		var = p->GetSymbol(base + i + 1);
		switch (var->type) {
			case zPAR_TYPE_INT		:	t = zCON_TYPE_INT;		break;
			case zPAR_TYPE_FLOAT	:	t = zCON_TYPE_FLOAT;	break;
			case zPAR_TYPE_STRING	:	t = zCON_TYPE_STRING;	break;
		}
		if (t!=-1) {
			zSTRING s	= var->name;
			int p		= s.Search(".");
			if (p>0) s	= var->name.Copied(p+1,255);
			// CODECHANGE [STEFAN]
			InsertVar	(nix,s,t,(void *)((zBYTE *)adr + var->GetOffset()),var->ele);
			// CODECHANGE [STEFAN] END
		}
	}
	AddEvalFunc	( EditFunc );
	Show		();
	return TRUE;
}


#pragma warning( default : 4706 ) 
