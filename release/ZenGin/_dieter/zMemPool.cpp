/******************************************************************************** 
 
     $Workfile:: zMemPool.cpp    $                $Date:: 30.01.01 15:36   $
     $Revision:: 17               $             $Modtime:: 30.01.01 10:20   $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Generic memory pooling classes
   created: 1.12.2000

 * $Log: /current_work/ZenGin/_Dieter/zMemPool.cpp $
 * 
 * 17    30.01.01 15:36 Moos
 * 
 * 16    29.01.01 20:17 Moos
 * 
 * 15    28.01.01 20:17 Moos
 * 
 * 14    28.01.01 12:30 Moos
 * 
 * 13    25.01.01 12:14 Moos
 * 
 * 12    10.01.01 9:28 Moos
 * 
 * 11    13.12.00 19:13 Moos
 * 
 * 10    13.12.00 10:22 Moos
 * 
 * 9     13.12.00 10:11 Moos
 * 
 * 8     12.12.00 9:09 Moos
 * 
 * 7     6.12.00 19:14 Moos
 * 
 * 6     6.12.00 18:06 Moos
 * 
 * 5     5.12.00 19:18 Moos
 * 
 * 4     5.12.00 16:50 Moos
 * 
 * 3     5.12.00 12:04 Moos
 * 
 * 2     4.12.00 18:22 Moos
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 30.01.01 10:20 $)

#include <zCore.h>
#include "zLocal.h"
#include "zError.h"
#include "zMemPool.h"
#include "zMemory.h"

/* *********************************************************************

                         zCVolatileMemoryBase

   ********************************************************************* */


 #define ELEMENT(i) ((void *)((char *)data + size*i))


/* ----------------------------------------------------------------------

    zCVolatileMemoryBase::zCVolatileMemoryBase(size, num, overflow)

    Erzeugt den Pool flüchtigen speichers für <num> Objekte der Grösse <size>.
    Überlauf des Speichers wird sanft abgefangen, wenn <overflow> gesetzt ist;
    sonst gibt es einen Fault.

	 5.12.2000	[Moos]	
                Erzeugt
    13.12.2000  [Moos]
                Neue overflow-Logik

   ---------------------------------------------------------------------- */

zCVolatileMemoryBase::zCVolatileMemoryBase(size_t s, size_t n,zTVolatileOverflowMode o)
:size(s), num(0), nextfree(0), maxAllocated(0), maxFill(80), overflowMode(o), overflow(FALSE), data(0)
{
    Init(n);
} 




/* ----------------------------------------------------------------------

    zCVolatileMemoryBase::zCVolatileMemoryBase(size, overflow)

    wie obiger Konstruktor, aber es wird noch kein Speicher allociert.

	 5.12.2000	[Moos]	
                Erzeugt
    13.12.2000  [Moos]
                Neue overflow-Logik

   ---------------------------------------------------------------------- */

zCVolatileMemoryBase::zCVolatileMemoryBase(size_t s, zTVolatileOverflowMode o)
:size(s), num(0), nextfree(0), maxAllocated(0), maxFill(80), overflowMode(o), overflow(FALSE), data(0){} 




/* ----------------------------------------------------------------------

    zCVolatileMemoryBase::~zCVolatileMemoryBase()
    
    löscht auch die allocierten Objekte.

	 5.12.2000	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */

zCVolatileMemoryBase::~zCVolatileMemoryBase(){
    Restore (num);           // entspricht Restore(0), vergrößert den Puffer aber nie

    delete[](char *)data;  data = NULL;
}



/* ----------------------------------------------------------------------

    zCVolatileMemoryBase::Init(num)

    Legt den Speicher für <num> Objekte an

	 5.12.2000	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */

void zCVolatileMemoryBase::Init(size_t n){
    zERR_ASSERT      (!data);

    num  = n;
    data = zNEW_ARRAY(char, num * size);

    zERR_ASSERT      (data);
}




/* ----------------------------------------------------------------------

    zCVolatileMemoryBase::Alloc()

    Erzeugt ein Objekt der vorher angegebenen Größe; eine entsprechende
    Free()-Funktion existiert in dieser Klasse nicht. Dafür sind Mark()
    und Restore() verantwortlich.

	 5.12.2000	[Moos]	
                Erzeugt
    13.12.2000  [Moos]
                Neue overflow-Logik

   ---------------------------------------------------------------------- */

void *zCVolatileMemoryBase::Alloc(){

    // Überlauf-Test
    if (nextfree >= num){


        switch (overflowMode)
        {
            case zVOLATILE_OVERFLOW_FORBID:
                zERR_FATAL("M: MemBlock allocation overflow.");

                break;

            case zVOLATILE_OVERFLOW_RESIZE:  // vergrößere den Pool gleich
                {
                void  *olddata = data;
                size_t oldnum  = num;

                data = 0;
                Init((num * 200) / maxFill);
                
                memcpy(data, olddata, oldnum * size);
                
                delete olddata; 
                }

                break;

            case zVOLATILE_OVERFLOW_WRAP:

                // Doppelter Overflow ist aber absolut verboten (ausser bei mir)
#ifndef DEBUG_MOOS
                zERR_ASSERT(!overflow);
#endif

                // Mach das Beste daraus: setze den Zähler zurück und hoffe... 
                nextfree  = 0;       
                overflow  = TRUE;

                break;
                         
        }
    }

    // gib einfach das nächste freie Element zurück.
    void *ret = ELEMENT(nextfree);
    nextfree++;

    // wenn es einen Überlauf gab, löschen wir lieber zuerst den alten Inhalt
    if (overflow)
        Destroyed(ret);

    return ret;
}




/* ----------------------------------------------------------------------

    zCVolatileMemoryBase::Mark()

    Markiert den aktuellen Stand der Allocation. Typische Anwendung:


    zCVolatileMemoryBase pool(...);

    void Funktion(){
        size_t markPos = pool.Mark();

        // jede Menge Zeilen wie
        void *mem = pool.Alloc();

        Restore(markPos);
        // damit werden alle hier erzeugten Objekte wieder vernichtet
    }


	 5.12.2000	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */

size_t zCVolatileMemoryBase::Mark   ()        {
    if (nextfree!=0)
        return nextfree;
    else
        return num;
}




/* ----------------------------------------------------------------------

    zCVolatileMemoryBase::Restore()	

    Gegenstück zu Mark()

	 5.12.2000	[Moos]	
                Erzeugt
     6.12.2000  [Moos]
                Automatisches Vergrößern des Puffers bei drohendem Überlauf

   ---------------------------------------------------------------------- */

void   zCVolatileMemoryBase::Restore(size_t m){ 

    // erhöhe eventuell maxAllocated
    int allocated = nextfree;
    if (overflow)
        allocated += num;
    if (allocated > maxAllocated)
        maxAllocated = allocated;

    // wenn der Puffer gefährlich voll war (und ein Full-Restore gemacht wurde), lasse ihn
    // am Ende dieser Funktion vergrössert neu anlegen
    zBOOL reallocate = FALSE;
    if (m == 0 && maxAllocated * 100 > num * maxFill){
        reallocate = TRUE;
    }

    if (m == num){
        m=0; 
    }

    zERR_ASSERT (m < num && 0 <= m);
    
    // nur, wenn es einen Überlauf gab, darf der Schritt "nach vorne" machen
    zERR_ASSERT (m <= nextfree || overflow);

    // gehe zurück bis zur markierten Position
    while (nextfree != m){
        if (nextfree <= 0)
        { 
            // Überlauf wurde wieder rückgängig gemacht
            nextfree = num-1;
            overflow = FALSE;
        }
        else
            nextfree--;

        // lösche das alte Ding
        Destroyed (ELEMENT(nextfree));
    }

    // falls nötig, lege den Puffer neu an (So, dass erst nach einer Verdoppelung des Datenaufkommens wieder vergrößert wird)
    if (reallocate){
        delete[] data;
        data=NULL;
        Init((maxAllocated * 200) / maxFill);
    }
}





/* ----------------------------------------------------------------------

    zCVolatileMemoryBase::MaxFillPercentage()	

    Setzt den maximalen Füllstand des Puffers bevor er vergrössert wird

     6.12.2000  [Moos]
                Erzeugt

   ---------------------------------------------------------------------- */

void   zCVolatileMemoryBase::MaxFillPercentage(int perc){
    zERR_ASSERT(perc < 100 && perc > 0);

    maxFill = perc;
}





/* *********************************************************************

                         zCMemPoolBase

   ********************************************************************* */

// helper Classes


// the list of free spaces to store objects; these objects themselves mark the free space.
class zCFreeBlock{
public:

    // inserts the block into the double linked list freeblocks    
    void Insert(zCFreeBlock *&freeblocks)  
    {
        next       =  freeblocks;
        anchor     = &freeblocks;
        freeblocks =  this;

        if (next)
            next->anchor = &next;
    }



    // removes the block from the list
    void Remove()                          
    {
        zERR_ASSERT(anchor);

        *anchor = next;
        if (next)
            next->anchor = anchor;
        
        next    = NULL;
        anchor  = NULL;
    }

private:
    zCFreeBlock *next;     // the next element in the double linked list
    zCFreeBlock**anchor;   // the pointer in the list that points to this element
};


// ***************************************************************************************************************************************

// the big blocks of allocated memory
class zCMemPoolBlock{
public:
    // allocate a block with <num> spaces of size <size> for mempool <pool> and link the free spaces to <freeblocks>.
    zCMemPoolBlock(zCMemPoolBase *pool, zCFreeBlock *&freeblocks, size_t size, size_t num=0){
        next         = pool->blocks;
        pool->blocks = this;                // insert the block into the blocklist

        if (size < sizeof(zCFreeBlock))      // minimum size of objects: the size of zCFreeBlock.
            size = sizeof(zCFreeBlock);

        if (num == 0)                       // default number of objects per block: stored in the pool
            num = pool->blocksize;


        // create the block of memory
        if (zCMemPoolBase::s_className)
        {
            data = new(zCMemPoolBase::s_className, zCMemPoolBase::s_fileName, zCMemPoolBase::s_line) char[size*num];  // with debug info
            zCMemPoolBase::s_className = NULL;
        }
        else
            data = zNEW_ARRAY(char, size * num);                                                          // or without
 
        zERR_ASSERT(data);

        // register the free slots
        pool->numFree      += num;
        for (int i = num-1; i>=0; i--)
            ((zCFreeBlock *) ((char *)data + (i*size)))->Insert(freeblocks);
    }

    zCMemPoolBlock(zCMemPoolBase *pool, zCFreeBlock *&freeblocks, size_t size, void * block, size_t num, zBOOL free = FALSE){
        next         = pool->blocks;
        pool->blocks = this;                // insert the block into the blocklist

        zERR_ASSERT_STRICT(size >= sizeof(zCFreeBlock));

        // simply take the given Block as memory
        data = block;
       
        zERR_ASSERT(data);

        if (free)
        {
            // register the free slots
            pool->numFree      += num;
            for (int i = num-1; i>=0; i--)
                ((zCFreeBlock *) ((char *)data + (i*size)))->Insert(freeblocks);
        }
    }

    // delete the data and the rest of the MemBlocks
    ~zCMemPoolBlock(){
        delete next;
        delete[] data;
    }

    void *operator new   (size_t s){return malloc(s);}
    void  operator delete(void *p ){free(p);}

private:
    zCMemPoolBlock *next;   // next memblock in list
    void           *data;   // block data

    friend class zCMemPoolBase;
};


// ***************************************************************************************************************************************


const char *zCMemPoolBase::s_className=NULL; // for memory debugging
const char *zCMemPoolBase::s_fileName=NULL;
int         zCMemPoolBase::s_line=0;

zBOOL       zCMemPoolBase::s_disablePools=TRUE;







/* ----------------------------------------------------------------------

    zCMemPoolBase::zCMemPoolBase(size)
    
    Bereitet den Pool für die Aufnahme von Objekten der	Größe <size> vor

	 5.12.2000	[Moos]	
                Erzeugt
    13.12.2000  [Moos]
                Konstruktor mit prealloc hinzugefügt

   ---------------------------------------------------------------------- */

zCMemPoolBase::zCMemPoolBase(size_t s):size(s), blocks(0), freeList(0), numFree(0), preallocate(0){
    blocksize = 4096*16/size;
}

zCMemPoolBase::zCMemPoolBase(size_t s, size_t bs, size_t pa):size(s), blocksize(bs), blocks(0), freeList(0), numFree(0), preallocate(pa){
    if (blocksize == 0)
        blocksize = 4096*16/size;
}


/* ----------------------------------------------------------------------

    zCMemPoolBase::~zCMemPoolBase()

    löscht den gesamten Speicher. Da keine nützlichen Informationen über 
    die Belegung gespeichert wurden, wird nicht bemerkt, wenn noch Objekte
    gespeichert waren => evtl. Crash.
    
	 5.12.2000	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */

zCMemPoolBase::~zCMemPoolBase(){
  //  zERR_ASSERT(numFree == 0);

    // eigentlich Blödsinn, aber räumen wir lieber trotzdem auf.
    while(freeList)
        freeList->Remove();

    // die Blocke löschen sich dann rekursiv
    delete blocks; blocks = 0;
}



/* ----------------------------------------------------------------------

    zCMemPoolBase::Alloc()

    erzeugt ein Objekt der vorher definierten Größe, das dann wieder mit
    Free() gelöscht werden muss. Wurde vorher DisablePools(TRUE) aufgerufen,
    kommen die Objekte vom normalen Heap.

	 5.12.2000	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */

void * zCMemPoolBase::Alloc(){

    // wenn gewünscht, verwende den normalen Heap.
    if (s_disablePools)
    {
         if (s_className)
         {
             void *ret=new(s_className, s_fileName, s_line) char[size];  // mit Debug-Infos
             s_className = NULL;
             return ret;
         }
         else
             return zNEW_ARRAY(char, size);                              // oder ohne.
    }


#ifdef _DEBUG
    // führe den preallocation-request aus; das machen wir im Debug-Modus hier, damit die MemDebug-Infos korrekt gesetzt werden.
    if (forcePrealloc)
        new zCMemPoolBlock(this, freeList, size, preallocate);
    if (preallocate > numFree)
        new zCMemPoolBlock(this, freeList, size, preallocate-numFree);
    preallocate = 0;
#endif


    // wenn nötig, erzeuge einen neuen Block
    if (!freeList)
    {
        new zCMemPoolBlock(this, freeList, size);
#ifdef DEBUG_MOOS
        zERR_WARNING("M: Mempool-Objekt ohne PreAlloc erzeugt; das ist nicht Sinn der Sache.");
#endif
    }
    zERR_ASSERT(freeList);    

    // finde und registriere unser frisch gebackenes Objekt
    numFree--;
    void* ret = (void*) freeList;
    freeList->Remove();
    
    return ret;
}





/* ----------------------------------------------------------------------

    zCMemPoolBase::Free()

    gibt mit Alloc() reservierten Speicher wieder frei

	 5.12.2000	[Moos]	
                Erzeugt
     10.1.2001  [Moos]
                Null-Pointer wird abgefangen

   ---------------------------------------------------------------------- */

void zCMemPoolBase::Free(void* p){
    if (!p)
        return;

    // fallback auf den normalen Heap
    if (s_disablePools)
    {
        delete[] p;
        return;
    }

    // füge das Ding einfach in unsere freeList ein
    ((zCFreeBlock *)p)->Insert(freeList);
    numFree++;
}



/* ----------------------------------------------------------------------

    zCMemPoolBase::PreAlloc(num, force)

    Sagt an, dass balt <num> Aufrufe von Alloc() kommen. Wird <force>
    gesetzt, landen diese garantiert am Stück im Speicher.

	 5.12.2000	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */

void zCMemPoolBase::PreAlloc(size_t num, zBOOL force){
    preallocate   += num;
    forcePrealloc |= force;

#ifndef _DEBUG
    if (forcePrealloc)
        new zCMemPoolBlock(this, freeList, size, preallocate);
    if (preallocate > numFree)
        new zCMemPoolBlock(this, freeList, size, preallocate-numFree);
    preallocate = 0;
#endif
}


void  zCMemPoolBase::PoolAdd (void *mem,int num_objects, zBOOL free){
    if (s_disablePools && free)
        delete[] mem;
    else
        new zCMemPoolBlock(this, freeList, size, mem, num_objects, free);
}


/* ----------------------------------------------------------------------

    zCMemPoolBase::SetMemDebug()

    Merkt sich die MemoryDebug-Strings

	 5.12.2000	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */

void zCMemPoolBase::SetMemDebug(const char *classname, const char *filename, int line){
    s_className = classname;
    s_fileName  = filename;
    s_line      = line;
}


/* ----------------------------------------------------------------------

    zCMemPoolBase::DisablePools(disable)

    wenn <disable> gesetzt ist, wird statt den MemPools der normale
    Heap verwendet.

	 5.12.2000	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */


void zCMemPoolBase::DisablePools(zBOOL disable){
    s_disablePools = disable;
}
