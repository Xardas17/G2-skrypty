/******************************************************************************** 
 
     $Workfile:: zParser_Symbol.cpp   $                $Date:: 24.04.01 17:34   $
     $Revision:: 18                   $             $Modtime:: 19.04.01 18:19   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zParser_Symbol.cpp $
 * 
 * 18    24.04.01 17:34 Edenfeld
 * Patch 1.08a
 * 
 * 17    15.03.01 2:17 Hildebrandt
 * 
 * 16    25.01.01 13:39 Moos
 * 
 * 15    9.01.01 20:22 Wohlers
 * 
 * 14    14.11.00 12:44 Moos
 * 
 * 13    31.10.00 15:11 Moos
 * 
 * 12    11.10.00 10:41 Moos
 * 
 * 11    11.09.00 20:52 Speckels
 * 
 * 10    1.09.00 16:32 Rueve
 * zerr cleanup
 * 
 * 9     31.08.00 18:15 Wohlers
 * 
 * 8     24.08.00 16:46 Moos
 * malloc durch zNEW ersetzt
 * 
 * 7     2.08.00 14:25 Wohlers
 * 
 * 6     31.07.00 22:04 Wohlers
 * 
 * 5     21.07.00 15:35 Wohlers
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
 * 8     4.04.00 20:06 Wohlers
 * Parser-Class-Offset-Check
 * 
 * 7     29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 6     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 5     24.02.00 23:32 Wohlers
 * Fixes
 * 
 * 4     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 2     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

// TO DO / OPTIMIZE
// -	Variablen auf festen DataSpace legen, nicht immer Speicher fuer neue Vars mit new[]
//		allokieren.

#include "zCore.h"

#include "zParser_Symbol.h"
#include "zParser_Const.h"

#include "zDisk.h"
#include "zList.h"

// *****************************************************************************************
// STRINGTABLE
// *****************************************************************************************

// *************************
// Constructor / Destructor
// *************************

zCPar_StringTable :: zCPar_StringTable (int nr)
{
	if (nr>0) array.AllocAbs(nr);
}

zCPar_StringTable :: ~zCPar_StringTable ()
{
	Clear();
}

void zCPar_StringTable :: Clear()
{
	int nr = array.GetNumInList();
	for (int i=0; i<nr; i++) {
		delete (array[i]);
	}
	array.EmptyList();
}

zSTRING* zCPar_StringTable :: Insert( zSTRING &s )
{
	zSTRING *sptr = zNEW( zSTRING(s) );
	array.Insert(sptr);
	return (sptr);
}

int zCPar_StringTable :: GetLastEntry()
{
	return (array.GetNumInList()-1);
}

zSTRING* zCPar_StringTable :: GetString ( int nr )
{
	if (nr<=array.GetNumInList()) 
		return array[nr];
	else
		return NULL;
}

void zCPar_StringTable :: Save (zSTRING &s)
{
	zFILE *f = zfactory->CreateZFile(s);
	f->Create();
	int nr = array.GetNumInList();
	for (int i=0; i<nr; i++) {
		f->Write(array[i]);
		f->Write("\n");
	}
	f->Close();
	delete(f);
};

void zCPar_StringTable :: Load (zSTRING &s)
{
	zSTRING dat;
	
	zFILE *f = zfactory->CreateZFile(s);
	f->Open();
	if (f->Exists()) {
		while (!f->Eof()) {
			f->Read(dat);
			if (!f->Eof()) Insert(dat);
		}
		f->Close();
	}
	delete (f);
};

void zCPar_StringTable :: ShrinkToFit ()
{
	array.ShrinkToFit();
}

void zCPar_StringTable :: Show ()
{
	int nr = array.GetNumInList();
	for (int i=0; i<nr; i++) {
		printf("%s\n",GetString(i)->ToChar());
	}
}

// *****************************************************************************************
// SYMBOL
// *****************************************************************************************

zCPar_Symbol*	zCPar_Symbol :: instance_sym = NULL;
void*			zCPar_Symbol :: instance_adr = NULL;

// Static
void zCPar_Symbol :: SetUseInstance(zCPar_Symbol *sym)
{
	//assert ((sym->type==zPAR_TYPE_INSTANCE) || (sym->type==zPAR_TYPE_PROTOTYPE));
	//assert (sym->offset!=0);
	if (!sym) {
		instance_adr = NULL;
		instance_sym = NULL;
		return;
	};
	
	if ((sym->type!=zPAR_TYPE_INSTANCE) && (sym->type!=zPAR_TYPE_PROTOTYPE)) {
		zerr.Warning("U:PAR:Object is not an instance :"+sym->name);
		instance_adr = NULL;
		instance_sym = NULL;
		return;
	} else if (sym->offset==0) {
		instance_adr = NULL;
		instance_sym = NULL;
		return;
	}
	instance_adr = (void*)sym->GetOffset();
	instance_sym = sym;
}

void zCPar_Symbol :: SetUseInstanceAdr(void* adr)
{
	instance_adr = adr;
}

void* zCPar_Symbol :: GetUseInstance()
{
	return instance_sym;
}

// *************************
// Constructor / Destructor
// *************************

zCPar_Symbol :: zCPar_Symbol()
{
	ele			= 0;				// Number of Elements
	type		= 0;				// Type of Elements
	flags		= 0;				// flags ( CONSTANTS )
	adr			= NULL;				// Datenwerte fuer jeweilige Variable
	offset		= 0;				// Offset bei KlassenVars 
	filenr		= 0;				// Filenummer
	line		= 0;				// Linenummer
	line_anz	= 0;				// Wieviele Zeilen ?
	pos_beg		= 0;				// Anfangsposition	(Datei -> Bytes)
	pos_anz		= 0;
	parent		= NULL;				// Parent-Verweis
	next		= NULL;				// Naechtes Symbol in Einfuege-Reihenfolge
	space		= FALSE;
}


/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: ~zCPar_Symbol()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */


zCPar_Symbol :: ~zCPar_Symbol()
{
	if ((adr!=NULL) && (!HasFlag(zPAR_FLAG_CLASSVAR)) && (space)) {
		switch (type) {
			case zPAR_TYPE_INT		:	if (ele>1) delete[] intdata;		                    break;
			case zPAR_TYPE_FLOAT	:	if (ele>1) delete[] floatdata;		                    break;
			case zPAR_TYPE_STRING	:	if (ele>1) delete[] stringdata; else delete stringdata;	break;
/*			case zPAR_TYPE_FUNC		:	delete	 intdata;		break;
			case zPAR_TYPE_PROTOTYPE:	delete	 intdata;		break;
			case zPAR_TYPE_INSTANCE	:	delete	 intdata;		break; */
		}
	}
	adr		= NULL;
	parent	= NULL;
	next	= NULL;
}

// *************************
// Members
// *************************

/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: AllocSpace()	

	14.11.2000	[Moos]	
                Daten der Grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: AllocSpace()
{
	if (space) return;
	if (!HasFlag(zPAR_FLAG_CLASSVAR)) {
		// Normale Variable
		switch (type) {
			case zPAR_TYPE_INT		:	if (ele>1) {
											intdata	= zNEW(int)[ele];		
											memset(intdata,0,sizeof(int)*ele);
										}
                                        else
                                            single_intdata = 0;
										break;

			case zPAR_TYPE_FLOAT	:	if (ele>1) {
											floatdata	= zNEW(float)[ele];		
											memset(intdata,0,sizeof(int)*ele);
										}
                                        else
                                            single_floatdata = 0;
										break;

			case zPAR_TYPE_STRING	:	if (ele>1)         stringdata  = zNEW(zSTRING)[ele];		
                                        else if (ele == 1) stringdata  = zNEW(zSTRING);
										break;
/*			case zPAR_TYPE_FUNC		:	intdata		= zNEW(int);	*intdata=0;	break;
			case zPAR_TYPE_PROTOTYPE:	intdata		= zNEW(int);	*intdata=0;	break;
			case zPAR_TYPE_INSTANCE	:	intdata		= zNEW(int);	*intdata=0;	break; */

			case zPAR_TYPE_FUNC		:
			case zPAR_TYPE_PROTOTYPE:
			case zPAR_TYPE_INSTANCE	:   //zERR_ASSERT(ele <= 1);
                	                    single_intdata		= 0;
                                        break;

			case zPAR_TYPE_CLASS	:	SetOffset(0);							break;
		}
	} else {
		if (ele<=0) {
			zERR_FAULT("U: SYM: Allocspace with no elements !");
		}
		// ClassVar
		int size = 0;
		switch (type) {
			case zPAR_TYPE_INT		:	size = sizeof(int)*ele;		break;
			case zPAR_TYPE_FLOAT	:	size = sizeof(float)*ele;	break;
			case zPAR_TYPE_STRING	:	size = sizeof(zSTRING)*ele;	break;
			case zPAR_TYPE_FUNC		:	size = sizeof(int)*ele;		break;
		}
		//assert				(parent!=NULL);
		if (parent) {
			SetOffset			(parent->GetOffset());
			parent->SetOffset	(parent->GetOffset()+size);
		}
	}
	space = TRUE;
}

/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: AllocSpace()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert
                Nie beobachteten Bug beim Holen der Adresse eines Stings
                in einem Array behoben

   ---------------------------------------------------------------------- */

void* zCPar_Symbol :: GetDataAdr (int nr)
{
	static int		nothing_int		= 0;
	static float	nothing_float	= 0.0f;
	static zSTRING	nothing_str		= "";
	static zSTRING*	nothing_strp	= &nothing_str;

//	assert((nr>=0) && (nr<ele));
	if (HasFlag(zPAR_FLAG_CLASSVAR)) {
		// **************************************************************
		// For safety, if adressing an instance which is not initialised.
		// **************************************************************
		if (!instance_adr) {
			zSTRING s;
			if (instance_sym) s = instance_sym->name + ": ";
			s += name;
			zERR_MESSAGE(zERR_WARN,0,"U:PAR: Adressing an empty Instance : " + s);
			
			switch (type) {
				case zPAR_TYPE_INT		:	nothing_int=0;		return &nothing_int;		
				case zPAR_TYPE_FLOAT	:	nothing_float=0;	return &nothing_float;	
				case zPAR_TYPE_STRING	:	nothing_str="";		return &nothing_str;
			}			
			nothing_int = 0;
			return &nothing_int;

		} else {
			// Instanz-Variable 
			if (type==zPAR_TYPE_STRING) 
				return ((zBYTE *)instance_adr) + GetOffset() + sizeof(zSTRING) * nr;
			else
				return ((zBYTE *)instance_adr) + GetOffset() + sizeof(int) * nr;
		}
	} else
    {
		switch (type)
        {
			case zPAR_TYPE_INT		:	if (ele>1)
                                            return intdata + nr;		
                                        else
                                            return &single_intdata;
                                        break;

			case zPAR_TYPE_FLOAT	:	if (ele>1)
                                            return floatdata + nr;	
                                        else
                                            return &single_floatdata;
                                        break;
                                        
			case zPAR_TYPE_STRING	:	return stringdata + nr;
                                        break;

			case zPAR_TYPE_FUNC		:
			case zPAR_TYPE_PROTOTYPE:
			case zPAR_TYPE_INSTANCE	:   zERR_ASSERT(nr == 0);
                                        return &intdata;
                                        break;
                            
	    }
    }			

    zERR_ASSERT(nr == 0); // [Moos] An dieser Stelle sind keine Arrays mehr erlaubt
	return intdata;
}

void zCPar_Symbol :: SetDataAdr (void *a)
{
	assert(a!=0);
	adr = a;
}

void zCPar_Symbol :: SetFlag (int f)
{
	flags |= f;
}

zBOOL zCPar_Symbol :: HasFlag (int f)
{
	return ((flags & f)>0);
}

void zCPar_Symbol :: SetParent (zCPar_Symbol *p)
{
	parent = p;
}

zCPar_Symbol* zCPar_Symbol :: GetParent ()
{
	return parent;
}

/*
void zCPar_Symbol :: SetSon (zCPar_Symbol *s)
{
	son = s;
}

zCPar_Symbol* zCPar_Symbol :: GetSon()
{
	return son;
}
*/
void* zCPar_Symbol :: GetInstanceAdr()
{
	assert (type==zPAR_TYPE_INSTANCE);
	return (void*)GetOffset();
}

zCPar_Symbol* zCPar_Symbol :: GetNext()
{
	return next;
}

zBOOL zCPar_Symbol :: ArrayCheck (int nr)
{
	return ((nr>=0) && (nr<ele));
}


/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: AllocSpace()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: GetStackPos (int &val, int nr)
{
	assert(type== zPAR_TYPE_INSTANCE || type== zPAR_TYPE_FUNC || type == zPAR_TYPE_PROTOTYPE);
//	assert(adr != NULL); [Moos] gilt nicht mehr
	assert(nr==0);

	val = single_intdata;
}

/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: AllocSpace()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: SetStackPos (int val, int nr)
{
	assert(type== zPAR_TYPE_INSTANCE || type == zPAR_TYPE_FUNC || type == zPAR_TYPE_PROTOTYPE);
//	assert(adr != NULL);
	assert(nr==0);

	single_intdata = val;
}

/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: SetValue()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: SetValue (int val, int nr)
{
	assert(type== zPAR_TYPE_INT);
	assert((nr>=0) && (nr<ele));
    
    if (ele>1)
    {
    	assert(adr != NULL);
	    intdata[nr] = val;
    }
    else
        single_intdata = val;
}

/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: SetValue()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: SetValue (float val, int nr)
{
	assert(type== zPAR_TYPE_FLOAT);
	assert((nr>=0) && (nr<ele));

    if (ele>1)
    {
    	assert(adr != NULL);
	    floatdata[nr] = val;
    }
    else
        single_floatdata = val;
}

void zCPar_Symbol :: SetValue (zSTRING &s, int nr)
{
	assert(type== zPAR_TYPE_STRING);
	assert(adr != NULL);
	assert((nr>=0) && (nr<ele));
	stringdata[nr] = s;
}

/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: GetValue()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: GetValue (int &val, int nr)
{
	assert((type== zPAR_TYPE_INT));
	assert((nr>=0) && (nr<ele));

    if (ele>1)
    {
    	assert(adr != NULL);
	    val = intdata[nr];
    }
    else
        val = single_intdata;
}

/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: GetValue()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: GetValue (float &val, int nr)
{
	assert(type== zPAR_TYPE_FLOAT);
	assert((nr>=0) && (nr<ele));

    if (ele>1)
    {
    	assert(adr != NULL);
	    val = floatdata[nr];
    }
    else
        val = single_floatdata;
}

void zCPar_Symbol :: GetValue (zSTRING &s, int nr)
{
	assert(type== zPAR_TYPE_STRING);
	assert(adr != NULL);
	assert((nr>=0) && (nr<ele));
	s = stringdata[nr];
}


void zCPar_Symbol :: SetLineData(int l1,int l2,int lpos1, int lpos2)
{
/*  if (l1 > maxline){ // [Moos] Alter code, der mir gesagt hat, wie sehr man die Elemente von zCPar_Symbol beschneiden darf
        maxline = l1;
        zERR_WARNING("Maxline " + zSTRING(maxline));
    }
    if (l2 > maxline){
        maxline = l2;
        zERR_WARNING("Maxline " + zSTRING(maxline));
    }

    if (lpos1 > maxpos){
        maxpos = lpos1;
        zERR_WARNING("Maxpos " + zSTRING(maxpos));
    }

    if (lpos2 > maxpos){
        maxpos = lpos2;
        zERR_WARNING("Maxpos " + zSTRING(maxpos));
    } */

    zERR_ASSERT_STRICT(0<= l1 && l1 < (1 << 19));
    zERR_ASSERT_STRICT(0<= l2 && l2 < (1 << 19));
    zERR_ASSERT_STRICT(0<= lpos1 && lpos1 < (1 << 24));
    zERR_ASSERT_STRICT(0<= lpos2 && lpos2 < (1 << 24));

	line	 = l1;
	line_anz = l2;
	pos_beg	 = lpos1;
	pos_anz	 = lpos2;
}


void zCPar_Symbol :: GetLineData(int &l1,int &l2,int &lpos1, int &lpos2)
{
	l1		= line;
	l2		= line_anz;
	lpos1	= pos_beg;
	lpos2	= pos_anz;
}

void zCPar_Symbol :: SetFileNr(int nr)
{ 
    zERR_ASSERT_STRICT(nr < (1<<19));

/*    if (nr > maxfile){
        maxfile = nr;
        zERR_WARNING("Maxfile " + zSTRING(maxfile));
    } */

    filenr = nr;   
};

/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: Save()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: Save (zFILE *f)
{
	zSTRING s;
    int     i;
	zBOOL l = (name.Length()>0);
	f->Write(&l,sizeof(l));
	if (l) f->Write(name+"\n");
	f->Write(&offset,(int)&parent-(int)&offset);

	if (HasFlag(zPAR_FLAG_CONST)) {
		// Write Constants
        switch (type)
        {
    		case zPAR_TYPE_INT      :   if (ele > 1)
                                        {
                                            zERR_ASSERT(intdata);
                                            f->Write(intdata,ele*sizeof(int));
                                        }
                                        else if (ele == 1)
                                            f->Write(&single_intdata,sizeof(int));
                                        break;
        
            case zPAR_TYPE_FLOAT    :   if (ele >1)
                                        {
                                            zERR_ASSERT(floatdata);
                                            f->Write(floatdata,ele*sizeof(float));
                                        }
                                        else if (ele == 1)
                                            f->Write(&single_floatdata,sizeof(float));
                                        break;

		    case zPAR_TYPE_STRING   :   for (i=0; i<ele; i++)
                                        {
    				                        GetValue(s,i);
				                            f->Write(s+"\n");
			                            }
                                        break;

		    case zPAR_TYPE_CLASS    :   int classOffset = GetClassOffset();
			                            f->Write(&classOffset,sizeof(classOffset));
                                        break;
		}
	}
}

/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: SaveFull()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: SaveFull (zFILE *f)
// Save mit aktuellen Variablenwerten
// und allen Verweisen auf PCode
// -> aktueller Parserstatus
{
	int i;
	zSTRING s;
	zBOOL l = (name.Length()>0);
	f->Write(&l,sizeof(l));
	if (l) f->Write(name+"\n");

	f->Write(&offset,(int)&parent-(int)&offset);
	
	if (!HasFlag(zPAR_FLAG_CLASSVAR)) 
    {
        switch (type)
        {
    		case zPAR_TYPE_INT      :   if (ele > 1)
                                        {
                                            zERR_ASSERT(intdata);
                                            f->Write(intdata,ele*sizeof(int));
                                        }
                                        else if (ele == 1)
                                            f->Write(&single_intdata,sizeof(int));
                                        break;
        
            case zPAR_TYPE_FLOAT    :   if (ele >1)
                                        {
                                            zERR_ASSERT(floatdata);
                                            f->Write(floatdata,ele*sizeof(float));
                                        }
                                        else if (ele == 1)
                                            f->Write(&single_floatdata,sizeof(float));
                                        break;

		    case zPAR_TYPE_STRING   :   for (i=0; i<ele; i++)
                                        {
    				                        GetValue(s,i);
				                            f->Write(s+"\n");
			                            }
                                        break;

		    case zPAR_TYPE_FUNC		:
		    case zPAR_TYPE_PROTOTYPE:
            case zPAR_TYPE_INSTANCE	:	
                                        f->Write(&single_intdata,sizeof(int));
                                        break;

		    case zPAR_TYPE_CLASS	:	i = GetClassOffset();
									    f->Write(&i,sizeof(i));				
                                        break;
	    }
    }
}

/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: LoadFull()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: LoadFull (zFILE *f)
// Load mit aktuellen Variablenwerten
// und allen Verweisen auf PCode
// -> aktueller Parserstatus
{
	zBOOL i,l;
	zSTRING s;
	f->Read(&l,sizeof(l));
	if (l) f->Read(name);
	
	f->Read(&offset,(int)&parent-(int)&offset);
	next = NULL;

	space = FALSE;
	if (type!=zPAR_TYPE_CLASS) AllocSpace();

	if (!HasFlag(zPAR_FLAG_CLASSVAR))
    {
    	switch (type)
        {
    		case zPAR_TYPE_INT      :   if (ele > 1)
                                        {
                                            zERR_ASSERT(intdata);
                                            f->Read(intdata,ele*sizeof(int));
                                        }
                                        else if (ele == 1)
                                            f->Read(&single_intdata,sizeof(int));
                                        break;
        
            case zPAR_TYPE_FLOAT    :   if (ele >1)
                                        {
                                            zERR_ASSERT(floatdata);
                                            f->Read(floatdata,ele*sizeof(float));
                                        }
                                        else if (ele == 1)
                                            f->Read(&single_floatdata,sizeof(float));
                                        break;

			case zPAR_TYPE_STRING	:	if (ele>0) {
											for (i=0; i<ele; i++) {
												f->Read(s);
												SetValue(s,i);
											}; 
										}; 
                                        break;

			case zPAR_TYPE_FUNC		:
			case zPAR_TYPE_PROTOTYPE:
			case zPAR_TYPE_INSTANCE :
                                    	f->Read(&single_intdata,sizeof(int));
                                        break;
                                        		
			case zPAR_TYPE_CLASS	:	{ 
										int classOffset;
										f->Read(&classOffset,sizeof(classOffset));		
										SetClassOffset(classOffset);
										};
										break;
		}
	}
}


/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: Load()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: Load (zFILE *f)
{
	zBOOL l;
    int i;
	zSTRING s;
	f->Read(&l,sizeof(l));
	if (l) f->Read(name);
	f->Read(&offset,(int)&parent-(int)&offset);
	next	= NULL;
	space	= FALSE;		// Noch kein Speicherplatz allokiert !
	if (HasFlag(zPAR_FLAG_CONST)) {
		AllocSpace();
		// Write Constants
    	switch (type)
        {
    		case zPAR_TYPE_INT      :   if (ele > 1)
                                        {
                                            zERR_ASSERT(intdata);
                                            f->Read(intdata,ele*sizeof(int));
                                        }
                                        else if (ele == 1)
                                            f->Read(&single_intdata,sizeof(int));
                                        break;
        
            case zPAR_TYPE_FLOAT    :   if (ele >1)
                                        {
                                            zERR_ASSERT(floatdata);
                                            f->Read(floatdata,ele*sizeof(float));
                                        }
                                        else if (ele == 1)
                                            f->Read(&single_floatdata,sizeof(float));
                                        break;

			case zPAR_TYPE_STRING	:	if (ele>0) {
											for (i=0; i<ele; i++) {
												f->Read(s);
												SetValue(s,i);
											}; 
										}; 
                                        break;

			case zPAR_TYPE_CLASS	:	{ 
										int classOffset;
										f->Read(&classOffset,sizeof(classOffset));		
										SetClassOffset(classOffset);
										};
										break;
		}

        /* [Moos] Alte version:
		if (type==zPAR_TYPE_INT)	f->Read(intdata,ele*sizeof(int));	else
		if (type==zPAR_TYPE_FLOAT)	f->Read(intdata,ele*sizeof(float));	else
		if (type==zPAR_TYPE_STRING)	{
			for (int i=0; i<ele; i++) {
				f->Read(s);
				SetValue(s,i);
			}
		} else if (type==zPAR_TYPE_CLASS) { 
			int classOffset;
			f->Read(&classOffset,sizeof(classOffset));		
			SetClassOffset(classOffset);
		};
        */ 
	}
}

void zCPar_Symbol :: SetOffset(int v)
{
	offset = v;
}

int  zCPar_Symbol :: GetOffset()
{
	return offset;
}

/* ----------------------------------------------------------------------
	
    zCPar_Symbol :: Set/GetClassOffset()	

	14.11.2000	[Moos]	
                Daten der grösse 4 werden nun direkt im Symbol gespeichert

   ---------------------------------------------------------------------- */

void zCPar_Symbol :: SetClassOffset(int v)
{
	assert(type== zPAR_TYPE_CLASS);
    single_intdata = v;
}


int  zCPar_Symbol :: GetClassOffset()
{
   	assert(type== zPAR_TYPE_CLASS);
	return single_intdata;
}


// *****************************************************************************************
// SYMBOLTABELLE
// *****************************************************************************************

zCPar_SymbolTable* zCPar_SymbolTable ::	cur_table;

// *************************
// Constructor / Destructor
// *************************

zCPar_SymbolTable :: zCPar_SymbolTable (int nr)
{
	firstsym	= NULL;
	lastsym		= NULL;

	if (nr>0) {
		table	 .AllocAbs(nr);
		tablesort.AllocAbs(nr);
	}
	
	tablesort.SetCompare(Compare);

    preAllocatedSymbols = NULL;
    nextPreAllocated    = -1;
}

zCPar_SymbolTable :: ~zCPar_SymbolTable ()
{
	Clear();
}

void zCPar_SymbolTable :: Clear()
{
    if (preAllocatedSymbols){
        delete[] preAllocatedSymbols;   // [Moos] lösche Memory-Pool
        preAllocatedSymbols = NULL;
        nextPreAllocated    = -1;
    }
    else{
    	int anz = table.GetNumInList();
    	for (int i=0; i<anz; i++) delete(table[i]);
    }
	table.EmptyList();
	tablesort.EmptyList();
	firstsym	= NULL;
	lastsym		= NULL;
}


inline zCPar_Symbol *zCPar_SymbolTable::AllocSymbol(){
    zERR_ASSERT(preAllocatedSymbols && nextPreAllocated >= 0);

    return preAllocatedSymbols + (nextPreAllocated--);
}

void zCPar_SymbolTable::PreAlloc(int num){
    zERR_ASSERT(!preAllocatedSymbols && num > 0);

    preAllocatedSymbols = zNEW_ARRAY(zCPar_Symbol, num);
    nextPreAllocated    = num -1;
}


int zCPar_SymbolTable :: Compare (const void *a, const void *b)
// Static function
{
	return (strcmp(cur_table->table[*(int*)a]->name.ToChar(),cur_table->table[*(int*)b]->name.ToChar()));
}

void zCPar_SymbolTable :: Save(zFILE *f)
{
	int nr = table.GetNumInList();
	f->Write(&nr,sizeof(nr));
	// Save Array of Indexes
	f->Write(tablesort.GetArray(),sizeof(int) * nr);
	// Save Symbols
	zCPar_Symbol *par,*sym;
	for (int i=0; i<nr; i++) {
		sym =  table[i];
		sym -> SaveFull(f);
		// Parent ?
		par		= sym -> GetParent();
		int c	= -1;
		if (par) c = GetIndex(par->name);
		f->Write (&c,sizeof(c));
	}
}

// Special Struct for Externals - Saving /Recovery
class zCParserExternals {
public:
	zCParserExternals (zSTRING &n, int a) { name = n; adr = a; next = NULL; };
	zSTRING name;
	int		adr;
	zCParserExternals *next;
};

void zCPar_SymbolTable :: Load(zFILE *f)
{	
	// Put External-Names in List
	int adr;
	zCPar_Symbol *sym;
	zList <zCParserExternals> externals;
	for (int i=0; i<table.GetNumInList(); i++) {
		sym = table[i];
		if (sym->HasFlag(zPAR_FLAG_EXTERNAL)) {
			if (sym->type==zPAR_TYPE_FUNC) 
				sym->GetStackPos(adr);
			else
				adr = (int)sym->GetDataAdr();

			externals.Insert(zNEW(zCParserExternals(sym->name, adr)));
		}
        if (!preAllocatedSymbols) // [Moos]
		    delete sym;
	}

    if (preAllocatedSymbols){
        delete[] preAllocatedSymbols;
        preAllocatedSymbols = NULL;
        nextPreAllocated    = -1;
    }

	// Empty Lists
	table.EmptyList();
	tablesort.EmptyList();
	int nr;
	f->Read(&nr,sizeof(nr));
	// Load Array of Indexes
	tablesort.AllocAbs(nr);
	table    .AllocAbs(nr);
    tablesort.MarkNumAllocUsed ();
    f->Read  (tablesort.GetArray(),sizeof(tablesort[0]) * nr);	
//	f->Read(tablesort.array,sizeof(int) * nr);
//	tablesort.numInArray = nr;
	// Load Symbols

    PreAlloc(nr); // [Moos] verwende den Mempool

	for (i=0; i<nr; i++) {
		sym = AllocSymbol(); // zNEW( zCPar_Symbol() ); // [Moos] Verwende den Mempool
		sym -> LoadFull(f);
		// Parent ?
		int c;
		f->Read(&c,sizeof(c));
		if (c>=0) sym -> SetParent ( GetSymbol(c) );
		table.InsertEnd(sym);
	}
	
	// Linking Externals (safety)
	zCParserExternals* ext = externals.wurzel;
	while (ext!=NULL) {
		sym = GetSymbol(ext->name);
		if ((sym) && (sym->HasFlag(zPAR_FLAG_EXTERNAL)))
			if (sym->type==zPAR_TYPE_FUNC)
				sym->SetStackPos(ext->adr);
			else
				sym->SetDataAdr((void*)ext->adr);
		else 
			zERR_WARNING("U: PAR: External "+ext->name+" not found.");
		ext = ext->next;
	}
	externals.Clear();
}

zBOOL zCPar_SymbolTable :: IsIn(zCPar_Symbol *s)
{
	return (GetIndex(s->name)>=0);
}

zBOOL zCPar_SymbolTable :: IsIn(const zSTRING &s)
{
	return (GetIndex(s)>=0);
}

int zCPar_SymbolTable :: GetIndex (zCPar_Symbol *s)
{
	return GetIndex(s->name);
}

int zCPar_SymbolTable :: GetIndex (const zSTRING &s)
{
	cur_table = this;
	return Search(s,0,table.GetNumInList()-1);	
};

int zCPar_SymbolTable :: GetIndex (const zSTRING &s, int index)
// Schneller : Beruecksichtigt Type und Length des Parent Symbols (index -> sofern bekannt )
{
	cur_table = this;
	int    ele = GetSymbol(index)->ele;
	return Search(s,index+1,index+1+ele);
}

int zCCFASTCALL zCPar_SymbolTable :: Search (const zSTRING &s, int ind_low, int ind_high)
{
	if (table.GetNumInList()<=0) return -1;
	// Binary Search	
	int index, erg;

	do {		
		index	= ind_low + ( ind_high - ind_low ) / 2;

//		zSTRING s2 = table[tablesort[index]]->name.ToChar();
//		erg		= strcmp (s.ToChar(), s2.ToChar() );

		erg		= s.CompareTo (table[tablesort[index]]->name);

#ifdef _DEBUG
		{
			zSTRING s2	= table[tablesort[index]]->name.ToChar();
			int erg2	= strcmp (s.ToChar(), s2.ToChar() );
			zERR_ASSERT (erg==erg2);
		};
#endif

		if (erg>0) 	
			ind_low	= index + 1;
		else if (erg<0)
			ind_high= index - 1;
		else 
			return tablesort[index];
	
	} while (ind_low <= ind_high);
	
	return -1;
}

zCPar_Symbol* zCPar_SymbolTable :: GetSymbol (const zSTRING &s)
{
	return GetSymbol(GetIndex(s));
}

zCPar_Symbol* zCPar_SymbolTable :: GetSymbol (int index)
{
	if ((index<0) || (index>=table.GetNumInList())) return NULL;
	return table[index];
}

zBOOL zCPar_SymbolTable :: Insert (zCPar_Symbol *sym)
{
	assert(sym);
	//zBOOL f = table.Insert(sym);
	zBOOL f = TRUE;
	
	// already in ?
	f = (GetIndex(sym->name)<0);
	
	if (f) {
		tablesort.GetNumInList();
		
		cur_table = this;
		table		.InsertEnd (sym);
		tablesort	.InsertSort(table.GetNumInList()-1);
		sym->AllocSpace();
		if (!firstsym) firstsym			= sym;
		if ( lastsym ) lastsym -> next	= sym;
		lastsym	= sym;
	
	}
	return f;
}

void zCPar_SymbolTable :: InsertEnd (zCPar_Symbol *sym)
{
	table		.InsertEnd(sym);
	tablesort	.InsertSort(table.GetNumInList()-1);
	sym->AllocSpace();
	if (!firstsym) firstsym			= sym;
	if ( lastsym ) lastsym -> next	= sym;
	lastsym	= sym;
}

void zCPar_SymbolTable :: ShrinkToFit ()
{
	table	 .ShrinkToFit();
	tablesort.ShrinkToFit();
}

void zCPar_SymbolTable :: SetSize(int n)
{
	table	 .AllocDelta(n);
	tablesort.AllocDelta(n);
}

int zCPar_SymbolTable :: GetNumInList ()
{
	return table.GetNumInList();
}

zCPar_Symbol* zCPar_SymbolTable :: GetLastSymbol()
{
	return lastsym;
}

zCPar_Symbol* zCPar_SymbolTable :: GetFirstSymbol()
{
	return firstsym;
}

void zCPar_SymbolTable :: Show ()
{
	zSTRING help,s;
	float fval;
	int ival;
	int anz = table.GetNumInList();
	for (int i=0; i<anz; i++) {
		s = table[i]->name;
		if (table[i]->ele>1) s += "[" + zSTRING((int)table[i]->ele) + "]";
		if (table[i]->HasFlag(zPAR_FLAG_CONST)) {
			if (table[i]->ele>1) 
				s += " = { ";
			else 
				s += " = ";
			for (int n=0; n<table[i]->ele; n++) {
				switch (table[i]->type) {
					case zPAR_TYPE_INT		:	table[i]->GetValue(ival,n);
												s+=zSTRING(ival);
												break;
					case zPAR_TYPE_FLOAT	:	table[i]->GetValue(fval,n);
												s+=zSTRING(fval);
												break;
					case zPAR_TYPE_STRING	:	table[i]->GetValue(help,n);
												s+="\""+help+"\"";
												break;
				}
				if (n+1!=table[i]->ele) s+=",";
			}
			if (table[i]->ele>1) s += " }";
		}
		s+=";";
		printf("%d. %s\n",i,s.ToChar());
	}
}

// *****************************************************************************************
// STACK
// *****************************************************************************************


/* ----------------------------------------------------------------------
	
	zCParStack :: zCPar_Stack()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

zCPar_Stack :: zCPar_Stack(int nr)
{
	stack		= zNEW_ARRAY(zBYTE,nr);
	stacksize	= nr;
	stackptr	= stack;
	stacklast	= stack;
}


/* ----------------------------------------------------------------------
	
	zCParStack :: ~zCParStack()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

zCPar_Stack :: ~zCPar_Stack()
{
	delete[] stack;
	stack		= NULL;
	stackptr	= NULL;
	stacklast	= NULL;
}

int zCPar_Stack :: GetPopPos()
{
	return (int)stackptr-(int)stack;
}

void zCPar_Stack :: SetPopPos(int nr)
{
	assert(nr<stacksize);
	stackptr = stack + nr;
}

int zCPar_Stack :: GetDynSize()
{
	return (int)stacklast-(int)stack;
}

int zCPar_Stack :: GetStatSize()
{
	return stacksize;
}

void zCPar_Stack :: PushByte(zBYTE w)
{
	CheckOverflow(1);
	*stacklast++ = w;
}

void zCPar_Stack :: PushWord(zWORD w)
{
	CheckOverflow(2);
	*stacklast_w++ = w;
}

void zCPar_Stack :: PushInt(int w)
{
	CheckOverflow(4);
	*stacklast_i++ = w;
}

void zCPar_Stack :: PushString(zSTRING &s)
{
	CheckOverflow(s.Length()+2);
	PushByte(s.Length()+1);
	memcpy(stacklast,s.ToChar(),s.Length()+1);
	stacklast += s.Length() + 1;
}

zBYTE zCPar_Stack :: PopByte()
{
	return *stackptr++;
}

zWORD zCPar_Stack :: PopWord()
{
	return *stackptr_w++;
}

int zCPar_Stack :: PopInt()
{
	return *stackptr_i++;
}

void zCPar_Stack :: PopString(zSTRING &s)
{
	zBYTE l = PopByte();
	s = zSTRING( (char*) stacklast );
	stacklast += l;
}


/* ----------------------------------------------------------------------
	
	zCPar_Stack :: CheckOverflov()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void zCPar_Stack :: CheckOverflow(int d)
{
	int cur_size = (stacklast + d) - stack;
	if (cur_size > stacksize) {
		// Double Stacksize
		int newsize = stacksize * 2;
		zBYTE* stack2 = zNEW_ARRAY(zBYTE,newsize);
		memcpy(stack2,stack,stacksize);
		// Calc Offsets
		stackptr	= (stackptr - stack)	+ stack2;
		stacklast	= (stacklast - stack)	+ stack2;
		stacksize	= newsize;
		delete[] stack;
		stack		= stack2;
		//zerr.Message("U:PAR:Doubled StackSize :"+zSTRING(stacksize));
	}
}

void zCPar_Stack :: Set(int pos, int val)
{
	*((int *)(stack + pos)) = val;
}

zBOOL zCPar_Stack :: ReachedEnd()
{
	return (stackptr >= stacklast);
}

void zCPar_Stack :: Clear()
{
	stacklast = stack;
}

void zCPar_Stack :: Save (zFILE *f)
{
	int nr = GetDynSize();
	f->Write(&nr  ,sizeof(nr));
	f->Write(stack,sizeof(zBYTE)*nr);
}


/* ----------------------------------------------------------------------
	
	zCPar_Stack :: Load()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */


void zCPar_Stack :: Load (zFILE *f)
{
	int nr;
	f->Read(&nr,sizeof(nr));
	// Create Space
	delete[] stack;
	stack = zNEW_ARRAY(zBYTE,nr);
	f->Read(stack,sizeof(zBYTE)*nr);
	stacksize	= nr;
	stackptr	= stack;
	stacklast	= stack + nr;
}

// *****************************************************************************************
// DATA - STACK
// *****************************************************************************************

zCPar_DataStack :: zCPar_DataStack()
{
	sptr = 0;
	memset(stack,0,sizeof(stack));
}

zCPar_DataStack :: ~zCPar_DataStack()
{
}

void zCPar_DataStack :: Push (int value)
{

#ifdef _DEBUG
	// [BENDLIN] Addon Patch2 - ParserSymbol DataStack
	static int MaxSymDataStack = zMAX_SYM_DATASTACK/2;
	if (sptr > MaxSymDataStack)
		MaxSymDataStack = sptr;
#endif

	// [BENDLIN] Addon Patch2 - ParserSymbol DataStack
	if(sptr >= zMAX_SYM_DATASTACK)
	{
		zERR_FATAL("C: zCPar_DataStack :: Push(): stack overflow!!!");
	}

	stack[sptr++] = value;
}

int zCPar_DataStack :: Pop ()
{
	// [BENDLIN] Addon Patch2 - ParserSymbol DataStack
	// sptr == 0 tritt normalerweise auf, wenn eine function int
	// ohne return beendet wird (FALSE ist dadurch Standardwert)

	if (sptr > 0)
		return stack[--sptr];

//	zERR_WARNING("C: zCPar_DataStack :: Pop(): stack underflow - return 0");
	return FALSE;
}

float zCPar_DataStack :: PopFloat()
{
	// [BENDLIN] Addon Patch2 - ParserSymbol DataStack
	// sptr = 0 tritt normalerweise auf, wenn eine function float
	// ohne return beendet wird (0.0f ist dadurch Standardwert)

	if (sptr > 0)
		return *(float *)&stack[--sptr];

	zERR_WARNING("C: zCPar_DataStack :: PopFloat(): stack underflow - return 0.0f");
	return 0.0f;
}

zBOOL zCPar_DataStack :: IsEmpty()
{
	return (sptr==0);
}

void zCPar_DataStack :: Clear()
{
	sptr = 0;
}
