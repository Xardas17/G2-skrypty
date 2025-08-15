/******************************************************************************** 
 
     $Workfile:: zSparseArray.cpp      $                $Date:: 16.02.01 11:36   $
     $Revision:: 12                    $             $Modtime:: 16.02.01 10:58   $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   efficient associative arrays
   created: 8.12.2000

 * $Log: /current_work/ZenGin/_Dieter/zSparseArray.cpp $
 * 
 * 12    16.02.01 11:36 Moos
 * zCCacheBase::S_ClearCashes() implementiert
 * 
 * 11    13.02.01 11:38 Moos
 * Sicherheitsfix in Insert()
 * 
 * 10    9.02.01 13:24 Moos
 * 
 * 9     8.02.01 12:10 Speckels
 * 
 * 8     25.01.01 18:08 Moos
 * 
 * 7     24.01.01 14:57 Moos
 * 
 * 6     19.01.01 10:04 Moos
 * 
 * 5     18.01.01 15:08 Moos
 * 
 * 4     15.01.01 12:51 Moos
 * 
 * 3     13.12.00 17:40 Moos
 * 
 * 2     13.12.00 15:54 Moos
 * 
 * 1     12.12.00 9:09 Moos
 * 
 * 1     21.09.00 18:51 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 16.02.01 10:58 $)

#include "zCore.h"
#include "zSparseArray.h"
#include "zPrime.h"
#include "zError.h"
#include "zMemory.h"




/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::zCSparseArrayBase()

    Erzeugt das Array und reserviert Platz für die angegebene Anzahl
    an Elementen

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

zCSparseArrayBase::zCSparseArrayBase(zUINT32 s)
:size(0), min_size(s), table(0), used(0),
 maxRefCtr(10), requestResize(FALSE), numberOfIterators(0)
{
    if (s > 0)
        Create(s);
}




/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::~zCSparseArrayBase()

    WICHTIG: JEDER Destruktor, auch der von abgeleiteten Klassen, muss
             Destroy() aufrufen, da sonst die benötigten virtuellen
             Funktionen nicht zur Verfügung stehen.

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

zCSparseArrayBase::~zCSparseArrayBase(){
    Destroy();
}




/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::Destroy()	

    Vernichtet das Array und alle darin gespeicherten Daten.
    Destruktoren der Elemente werden korrekt ausgeführt.

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void zCSparseArrayBase::Destroy(){
    zERR_ASSERTT_STRICT(numberOfIterators == 0, "No iterators may be active on a deleted SparseArray");

    if (!table)
        return;

    for (int i = size-1; i>=0; i--)
    {
        
        zCSparseArrayManDat *manDat = ManDatPtr(i);

        if (manDat->occupied)
        {
            DestructIndex(IndexPtr(i));  // rufe die korrekten Destruktoren aus
            DestructData (DataPtr (i));  
        }
    }
    
    delete[] table;    
    table = 0;
}





/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::Element()
    
    gibt das mit Index <index> gespeicherte Datenelement zurück. Verschiebt
    das Element an einen schneller erreichtbaren Ort, falls möglich 
    (das aufgerufene Find macht das)

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void *zCSparseArrayBase::Element(const void *index) const{
    CheckResize();

    zUINT32 found = Find(index);
    if (found >= size)
        return NULL;
    else
        return DataPtr(found);
}







/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::Insert()
    
    Wie Element(); erzeugt allerdings einen neuen Eintrag, wenn er noch
    nicht existiert. Prinzip: die erste freie Position der form
    hash1 + k * hash2 wird genommen.

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void *zCSparseArrayBase::Insert (const void *index){

    zERR_ASSERT(used < size);

#ifdef _DEBUG
    if (numberOfIterators > 0)
        zERR_FAULT_ONCE("Inserted in zCSparseArray with active Iterators; dangerous! No resize possible."); 
#endif


    // Suche erst auf dem normalen Weg.
    zUINT32 found = Find(index);
    if (found < size)
        return DataPtr(found);

#ifndef _DEBUG
    if (numberOfIterators > 0)
        zERR_FAULT_ONCE("Inserted in zCSparseArray with active Iterators; dangerous! No resize possible."); 
#endif


    CheckResize();

    // Kein Erfolg. Hole die Hashwerte:           // FIXME: das wird dann doppelt gemacht! Einmal in Find(), und dann hier.
    zUINT32 hash1, hash2;
    Hash(index, hash1, hash2);
    zERR_ASSERT(0 <= hash1 && hash1 < size && 0 < hash2 && hash2 < size);

    // find the first fitting or free position of the form hash1 + k*hash2
    found = hash1;

    while (ManDatPtr(found)->occupied)
    {
        AddRef(ManDatPtr(found));          // markiere alle übersprungenen Elemente

        found = (found + hash2) % size;  
    }

    AddRef(ManDatPtr(found));
    ManDatPtr(found)->occupied = TRUE;     // und besetze das gefundenen freie.

    CopyIndex    (IndexPtr(found), index); // kopiere den Index dahin
    ConstructData(DataPtr (found));        // und erzeuge ein neues Datum.

    return DataPtr(found);
}






/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::Delete()

    Löscht den unter <index> gespeicherten Eintrag aus dem Array.

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void zCSparseArrayBase::Delete  (const void *index){

    // finde das Ding erstmal; mache nichts, wenn es nicht da ist.
    zUINT32 found = Find(index);
    if (found >= size)
        return;


    // hole wieder die hash-werte                  // nochmal FIXME: doppelte Arbeit
    zUINT32 hash1, hash2;
    Hash(index, hash1, hash2);
    zERR_ASSERT(0 <= hash1 && hash1 < size && 0 < hash2 && hash2 < size);

    ManDatPtr(found)->occupied = FALSE;            // gebe den Ort frei

    DestructIndex(IndexPtr(found));                // zerstöre das Element
    DestructData (DataPtr (found));
    
    while (found != hash1)                         // und release alle Elemente, die Insert reserviert hat.
    {
        Release(ManDatPtr(found));
        found = (found + size - hash2) % size;
    }

    Release(ManDatPtr(hash1));
}



void zCSparseArrayBase::Clear(){
    while(used)
    {
        for(int i=size-1; i>=0; i--)
            if (ManDatPtr(i)->occupied)
                Delete(IndexPtr(i));
    }
}


/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::IndexIsEqual()

    Vergleicht die an <i1> und <i2> gespeicherten Indices.
    Rückgabe: TRUE wenn gleich.

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

zBOOL zCSparseArrayBase::IndexIsEqual  (const void *i1,    const void *i2) const{
    return memcmp(i1, i2, SizeIndex()) == 0;
}



/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::CopyIndex()

    kopiert den Index auf <isrsc> nach <idest>

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void  zCSparseArrayBase::CopyIndex     (      void *idest, const void *isrc) const{
    memcpy (idest, isrc, SizeIndex());
}




/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::Hash()

    Berechnet die Hashfunktionen; Bedingungen:
    0 <= hasha < size und 
    1 <= hashb < size

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void  zCSparseArrayBase::Hash (const void *index, zUINT32 &hasha, zUINT32 &hashb) const{
    ::Hash(index, size, hasha, hashb, SizeIndex());
}




/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::Find()

    findet die interne Position des Eintrags mit Index <index>.

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

zUINT32 zCSparseArrayBase::Find (const void *index) const{
    // calculate hash values: 
    zUINT32 hash1, hash2;
    Hash(index, hash1, hash2);
    zERR_ASSERT(0 <= hash1 && hash1 < size && 0 < hash2 && hash2 < size);

    // find the first fitting or free position of the form hash1 + k*hash2
    zUINT32 found    = hash1;
    zUINT32 lastFree = size;

    while (ManDatPtr(found)->refCtr > 0)
    {
        if (ManDatPtr(found)->occupied)
        {
            if (IndexIsEqual(IndexPtr(found), index))
                break;
        }
        else
            lastFree = found;

        found = (found + hash2) % size;  
    }

    if (ManDatPtr(found)->refCtr > 0)
    {
        if (lastFree < size)  // es gibt eine bessere Position! Bewege dich zu ihr zurück und release alles unterwegs.
        {
            int    oldfound = found;

            while (found != lastFree)
            {
                Release(ManDatPtr(found));
                found = (found + size - hash2) % size;
            }
    
            // Kopiere die Daten an ihren neuen Platz
            memcpy(IndexPtr(found), IndexPtr(oldfound), SizeIndex() + SizeData());
            ManDatPtr(found)   ->occupied = TRUE;
            ManDatPtr(oldfound)->occupied = FALSE;
        }

        return found;
    }
    else
        return size;
}




/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::Create()

    erzeugt die Arraydatenstruktur im leeren Zustand mit <newsize>
    möglichen Einträgen neu.

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void    zCSparseArrayBase::Create  (zUINT32 newsize){
    zERR_ASSERT(!table);

    size  = zCPrime::NextPrime(newsize);
    used  = 0;
    table = zNEW_ARRAY(zBYTE , size * SizeAll());

    for (int i = size-1; i>= 0; i--)
    {
        ManDatPtr(i)->refCtr   = 0;
        ManDatPtr(i)->occupied = FALSE;
    }

    requestResize = FALSE;
//    lastAccessed  = 0;
}





/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::Resize()

    baut das Array mit der neuen Grösse <newsize> auf, ohne dass
    Daten verlorengehen.

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void    zCSparseArrayBase::Resize  (zUINT32 newsize){
    // safety
    if (newsize <= used+10)
        newsize = used+10;

    if (numberOfIterators > 0)
    {
        static zBOOL done=FALSE;
        if (!done)
            zERR_FATAL("zCSparseArray resized, but there were Iterators active."); 
        done=TRUE;
    }

    // save our old settings 
    zUINT32 oldsize   = size;

    newsize = zCPrime::NextPrime(newsize);
    if (newsize == oldsize)
        newsize = zCPrime::NextPrime(newsize+1);

    void    *oldtable = table;
    table             = NULL;

    // create new structure
    Create(newsize);

    zERR_MESSAGE(9, 0, "M: Resizing SparseArray from " +  zSTRING(oldsize) + " to " +zSTRING(size) + " entries.");

    // transfer data into new structure ; abuse oldsize as counter
    while(oldsize>0)
    {
        oldsize--;

        zCSparseArrayManDat *manDat = ManDatPtr(oldsize, oldtable);
        if (manDat->occupied)
        {
            void *index   = IndexPtr(oldsize, oldtable);
            void *newData = Insert  (index);
            DestructIndex           (index);
            
            memcpy(newData, DataPtr(oldsize, oldtable), SizeData());
        }
    }

    // delete old data
    delete[] oldtable;
}




/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::AddRef()

    markiert den gegebenen ManDat-Eintrag als verwendet, damit Find() u.a.
    beim Suchen nicht an dieser Stelle aufgeben, wenn der Eintrag leer ist.
    Wenn das Array zu voll wird, wird ein Vergrößerungsantrag gestellt,
    der dann möglichst bald (vor dem nächsten Insert() oder Element()...)
    ausgeführt wird.

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void zCSparseArrayBase::AddRef (zCSparseArrayManDat *md) const{
    if (!md->refCtr)
    {
        ((zCSparseArrayBase *)this)->used++;

        if ((used+2) * 3 > size * 2)
            ((zCSparseArrayBase *)this)->requestResize = TRUE;
    }

    if (md->refCtr > maxRefCtr)
    {
        ((zCSparseArrayBase *)this)->requestResize  = TRUE;
        ((zCSparseArrayBase *)this)->maxRefCtr     += maxRefCtr >> 1;
    }

    md->refCtr++;

    zERR_ASSERT(md->refCtr < 2000000);
}




/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::Release()

    Gegenstück zu AddRef()

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void zCSparseArrayBase::Release(zCSparseArrayManDat *md) const{
    zERR_ASSERT(md->refCtr > 0);

    if ( --md->refCtr == 0)
    {
        zERR_ASSERT(used > 0);
        ((zCSparseArrayBase *)this)->used--;

        if ((used+2) * 6 < size && size > min_size)
            ((zCSparseArrayBase *)this)->requestResize = TRUE;
    }
}




/* ----------------------------------------------------------------------
	
    zCSparseArrayBase::CheckResize()

    Führt die von AddRef() gestellten Vergrößerungsanträge aus.

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void zCSparseArrayBase::CheckResize() const{
    if (requestResize && numberOfIterators == 0){
        zUINT32 newsize = used * 3;
        if (newsize < min_size)
            newsize = min_size;
//        zUINT32 minsize = size+1;
//        if (newsize < minsize)
//            newsize = minsize;

        ((zCSparseArrayBase *)this)->Resize(newsize);
       
    }
}




/* ----------------------------------------------------------------------
	
    Hash()

    Basis-Hash-Funktion. stellt die an <index> stehende Binärzahl mit
    der länge <size> als 
    
    index = hasha + p * ( hashb - 1 + X * (p-1))

    mit den Grenzen 0 <= hasha < p und 1 <= hashb < p dar.

	 12.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void Hash(const void *index, zUINT32 p, zUINT32 &hasha, zUINT32 &hashb, zUINT32 size){
    zERR_ASSERT(p < (1<<24));

    zUINT32 rest1=1, rest2=0, d=0;
    hasha = hashb = 0;

    zUINT16* run = (zUINT16*)(void *)index;
    for(int i=size/2-1; i>=0; i--){
        hasha += (*run) * rest1;
        hashb += (*run) * rest2;

        d      = hasha/p;
        hasha -= d*p;
        hashb += d;
        hashb %= p-1;
    
        rest1 <<= 16;
        rest2 <<= 16;

        d      = rest1/p;
        rest1 -= d*p;
        rest2 += d;
        rest2 %= p-1;

        run++;
    }

    hashb++; // hashb must not be zero.
};


















zCCacheBase::zCCacheBase                 (){
    next = s_anchor;
    if (next) next->anchor = &next;

    s_anchor = this;
    anchor   = &s_anchor;

    timeout = 100;
}


zCCacheBase::~zCCacheBase        (){
    if (next) next->anchor = anchor;
    *anchor = next;

    next   = NULL;
    anchor = NULL;

    if (s_run == this)
        s_run = NULL;
}

void zCCacheBase::S_PurgeCaches   (){
    if (!s_run)
        s_run = s_anchor;

    s_run->PurgeCache();
    s_run = s_run->next;

    s_currentFrame++;
}

void zCCacheBase::S_ClearCaches   (){
    s_run = s_anchor;

    while (s_run)
    {
        s_run->ClearCache();
        s_run = s_run->next;
    }
}


int             zCCacheBase::s_currentFrame=0;
zCCacheBase    *zCCacheBase::s_anchor=NULL;       // data for double linked list
zCCacheBase    *zCCacheBase::s_run=NULL;













































// **************************************************************************************
// **************************************************************************************
// **************************************************************************************
// **************************************************************************************

#ifdef DEBUG_MOOS

// test code

zCSparseArray<int, int> test(2);

#define RUNS    1000000
#define SAMPLES 10000
#define STEPS   5

zBOOL Test(int run, int sample){
    return zCPrime::IsPrime(SAMPLES * run + 1 + sample * STEPS);
}


void TestSparseArray(){
    for (int run = 0; run < RUNS; run ++)
    {
        int count = 0, sample;

        if ((run+1) % 100 == 0)
            zERR_MESSAGE(4, 0, "M: SparseArray test run " +  zSTRING(run+1) + " of " +zSTRING(RUNS) + " started.");
        

        for (sample = 0; sample < SAMPLES; sample ++)
        {
            if (Test(run, sample))
                *(test.Insert(sample)) = count++;
            else
                test.Delete(sample);
        }

        count = 0;

        for (sample = 0; sample < SAMPLES; sample ++)
        {
            int *x = test[sample];
            if (Test(run, sample))
            {
                zERR_ASSERT_STRICT(x && *x == count);
                count ++;
            }
            else
                zERR_ASSERT_STRICT(!x);
        }
    }
}


#endif