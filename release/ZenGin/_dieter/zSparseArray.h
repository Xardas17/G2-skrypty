/******************************************************************************** 
 
     $Workfile:: zSparseArray.h      $                $Date:: 16.02.01 11:36   $
     $Revision:: 12                  $             $Modtime:: 16.02.01 9:28    $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   efficient associative arrays
   created: 8.12.2000

 * $Log: /current_work/ZenGin/_Dieter/zSparseArray.h $
 * 
 * 12    16.02.01 11:36 Moos
 * zCCacheBase::S_ClearCashes() implementiert
 * 
 * 11    12.02.01 16:28 Moos
 * 
 * 10    9.02.01 13:24 Moos
 * 
 * 9     24.01.01 14:57 Moos
 * 
 * 8     18.01.01 15:08 Moos
 * 
 * 7     15.01.01 14:28 Moos
 * 
 * 6     15.01.01 12:51 Moos
 * 
 * 5     20.12.00 9:46 Moos
 * 
 * 4     15.12.00 18:32 Moos
 * 
 * 3     13.12.00 18:27 Hildebrandt
 * added #ifndef __ZTYPES_H__
 * 
 * 2     13.12.00 17:40 Moos
 * 
 * 1     12.12.00 9:09 Moos
 * 
 * 1     21.09.00 18:51 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 16.02.01 9:28 $)

#ifndef __ZSPARSEARRAY_H__
#define __ZSPARSEARRAY_H__

#ifndef __ZTYPES_H__
#include "zTypes.h"
#endif

#include "new.h"


// Here we define sparse arrays; they are used exactly like
// normal arrays, but are optimized for the case when most
// elements are unused. As array index, every class that can be compared
// my memcmp can be used. 

// the current implementation uses double hash tables; the benefits are small
// memory usage and good (O(1)) practical per operation cpu load. Worst case cpu
// load is O(N), however.


// ****************************************************
// ****************************************************
//        zCSparseArrayBase: Basic functionality
// ****************************************************
// ****************************************************



// Management Data
class zCSparseArrayManDat{
public:
    int   refCtr  :31;
    zBOOL occupied:1;
};

class zCSparseArrayBase{
    friend class zCSparseArrayIterator;

public:
    zCSparseArrayBase(zUINT32 size=1031);
    virtual ~zCSparseArrayBase();

    // Index "Operator"; C; does not modify internal order, does not create new elements. Returns NULL if index is not used.
    void *Element(const void *index) const;

    // inserts new element at given Index. Return Value: pointer to new data
    void *Insert (const void *index);

    // delete the element at index
    void Delete  (const void *index);

    // deletes the complete array
    void Clear   ();
protected:
    zCSparseArrayBase (const zCSparseArrayBase &c);

	// [EDENFELD] Typ des Operators genauer spezifiziert (ist sonst automatisch INT je nach Compiler)
    zCSparseArrayBase& operator =        (const zCSparseArrayBase &c);

    zUINT32                 numberOfIterators; // the number of iterators currently active in this array
    zUINT32                 size;              // table´s size; guaranteed to be a prime number.
    zUINT32                 min_size;          // table´s minimal size
    void                   *table;             // the table itself
    zUINT32                 used;              // the number of spaces used
    zUINT32                 maxRefCtr;         // maximum value of refCtr before Array is resized
    zBOOL                   requestResize;     // put this to TRUE if the space gets too small


    virtual zUINT32 SizeIndex() const = 0;
    virtual zUINT32 SizeData () const = 0;
    virtual zUINT32 SizeAll  () const   {return SizeIndex() + SizeData() + sizeof(zCSparseArrayManDat);}


    virtual void                 *IndexPtr (zUINT32 i) const  {return ((char *)table) + SizeAll() * i;}
    virtual void                 *DataPtr  (zUINT32 i) const  {return (char *)IndexPtr(i) + SizeIndex();} 
    virtual zCSparseArrayManDat  *ManDatPtr(zUINT32 i) const  {return (zCSparseArrayManDat *) ( (char *)DataPtr(i) + SizeData() );}

    void                 *IndexPtr (zUINT32 i, void *table) const  {return ((char *)table) + SizeAll() * i;}
    void                 *DataPtr  (zUINT32 i, void *table) const  {return (char *)IndexPtr(i,table) + SizeIndex();} 
    zCSparseArrayManDat  *ManDatPtr(zUINT32 i, void *table) const  {return (zCSparseArrayManDat *) ( (char *)DataPtr(i,table) + SizeData() );}

    virtual zBOOL                 IndexIsEqual  (const void *i1,    const void *i2)   const;
    virtual void                  CopyIndex     (      void *idest, const void *isrc) const;
    virtual void                  DestructIndex (      void *index)                   const{};

    virtual void                  Hash          (const void *index, zUINT32 &hasha, zUINT32 &hashb) const;

    virtual void                  ConstructData (      void *data) const {};
    virtual void                  DestructData  (      void *data) const {};

    void AddRef (zCSparseArrayManDat *md) const;
    void Release(zCSparseArrayManDat *md) const;

    void CheckResize() const; // make the array larger

    void    Create  (zUINT32 size);
    void    Resize  (zUINT32 newsize);
    void    Destroy ();

private:
    zUINT32 Find    (const void *index)  const; // return value >=p if index not found.

    friend class zCSparseArrayIterator;
};









// ****************************************************
// ****************************************************
//              zCSparseArrayIterator
// ****************************************************
// ****************************************************


// iterator for the array; usable to step through all elements.
// usage: step through all used elements of an SparseArray <array> with
//
// for (zCParseArrayIterator i(array); i; i.Next())
//     do_something_with(array[i]);
//
// It is not advisable to add elements to the array while stepping through it, since
// neccesarry resizes can't be done during that phase. Deleting however is safe.


class zCSparseArrayIterator{
public:
    operator           zBOOL()                                      {if (count >= 0) return TRUE; else DeRegister(); return FALSE;}                // is the counter still still valid?
    void               Next ()                                      {do count--; while (operator zBOOL() && !array->ManDatPtr(count)->occupied);}  // go to the next element
    void               Reset()                                      {count = array->size; Next(); Register();}                                             // reset the counter to the start
    void               Reset(zCSparseArrayBase &array)              {this->array = &array; Reset();}                                               // reset the counter to the start of Array <array>
    int                Index()                                const {return count;}                                                                // get the internal position we're at
    zCSparseArrayBase *Array()                                const {return array;}                                                                // get the Array we are running through
    zBOOL              CheckArray(const zCSparseArrayBase *a) const {return array == a;}                                                           // check if we are running through Array <array>

    zCSparseArrayIterator(zCSparseArrayBase &array):array(0), registered(false) {Reset(array);}
    ~zCSparseArrayIterator()                                                    {DeRegister();}

private:
    int                count;
    zCSparseArrayBase *array;
    zBOOL              registered;

    void Register   ()  {if  (registered) return; registered = TRUE ; array->numberOfIterators++;}
    void DeRegister ()  {if (!registered) return; registered = FALSE; array->numberOfIterators--;}
};






// ****************************************************
// ****************************************************
//                 Template Hash Function
// ****************************************************
// ****************************************************


// overload this hash generation if your Index class has elements that are irrelevant for comparation (refCtrs, ....)
// condition on the return values: 0 <= hasha < p and 1 <= hashb <= p

// algorithm used by default: interpret index as very long integer, express it as index = hasha + p * (hashb - 1 + x (p-1)).

template <class Index> inline void Hash(const Index *index, zUINT32 p, zUINT32 &hasha, zUINT32 &hashb);
                              void Hash(const void  *index, zUINT32 p, zUINT32 &hasha, zUINT32 &hashb, zUINT32 size);


// ****************************************************
// ****************************************************
//      zCSparseArray Template: the real thing
// ****************************************************
// ****************************************************


// Template class for the real associative array. Both index and data class will be moved around with memcpy(..); the index class will
// be copied with its copy constructor and compared with the == operator.

template <class Index, class Data> class zCSparseArray: public zCSparseArrayBase{
public:
    zCSparseArray(zUINT32 size=1031):zCSparseArrayBase(0){if (size > 0) Create(size);}
    virtual ~zCSparseArray(){Destroy();}

    // Don't store the return values of these functions.
    Data *operator[]  (const Index& index) const  {return (Data *)Element(&index);}                     // non-modifying array subscriptor
    Data *Insert      (const Index& index)        {return (Data *)zCSparseArrayBase::Insert (&index);}  // modifying array subscriptor
    void Delete       (const Index& index)        {zCSparseArrayBase::Delete(&index);}                  // delete Element at Index <index>

    Data  *operator[]    (const zCSparseArrayIterator& iterator) const  {zERR_ASSERT(iterator.CheckArray(this)); return  (Data *)  DataPtr(iterator.Index()) ;} // get the various elements of tha array
    Data  *IteratorData  (const zCSparseArrayIterator& iterator) const  {zERR_ASSERT(iterator.CheckArray(this)); return  (Data *)  DataPtr(iterator.Index()) ;}
    Index *IteratorIndex (const zCSparseArrayIterator& iterator) const  {zERR_ASSERT(iterator.CheckArray(this)); return  (Index *)IndexPtr(iterator.Index()) ;} // and the indices
    void  Delete         (const zCSparseArrayIterator& iterator)        {zERR_ASSERT(iterator.CheckArray(this)); Delete(*(Index *)IndexPtr(iterator.Index()));}

protected:
    virtual zUINT32 SizeIndex() const                                                {return sizeof(Index);}
    virtual zUINT32 SizeData () const                                                {return sizeof(Data);}
    virtual zUINT32 SizeAll  () const                                                {return sizeof(Index) + sizeof(Data) + sizeof(zCSparseArrayManDat);}

    virtual void                 *IndexPtr (zUINT32 i)  const                        {return ((char *)table) + (sizeof(Index) + sizeof(Data) + sizeof(zCSparseArrayManDat)) * i;}
    virtual void                 *DataPtr  (zUINT32 i)  const                        {return (char *)IndexPtr(i) + sizeof(Index);} 
    virtual zCSparseArrayManDat  *ManDatPtr(zUINT32 i)  const                        {return (zCSparseArrayManDat *) ( (char *)DataPtr(i) + sizeof(Data) );}

    virtual zBOOL                 IndexIsEqual  (const void *i1,    const void *i2)   const {return (*(Index *)i1) == (*(Index *)i2);}
    virtual void                  CopyIndex     (      void *idest, const void *isrc) const {new (idest) Index(*((Index *)isrc));}
    virtual void                  DestructIndex (      void *index)                   const {((Index *)index)->~Index();}

    virtual void                  Hash          (const void *index, zUINT32 &hasha, zUINT32 &hashb) const    {::Hash<Index>((Index *)index, size, hasha, hashb);}

    virtual void                  ConstructData (      void *data) const              {new(data) Data();}
    virtual void                  DestructData  (      void *data) const              {((Data*)data)->~Data();}
};




// ****************************************************
// ****************************************************
//  zCCacheBase: Base class for the following template
// ****************************************************
// ****************************************************


/*

Usage: create an object like  

zCCache<Index, Data> cache;

to create a mapping from <Index> to <Data *>. To get the object of type <Data> belonging to <Index> index, just call

cache[index];

It will return a pointer to a newly created <Data>-Object. Subsequent calls of cache[index] within the timeout period
adjustable by cache.SetTimeout() (ault: 100 Frames) will return the same object. 
After the timeout period, the <Data>-Object will be deleted.

withc

Requirement:
The <Data> class neds a constructor of the form Data(const Index&).

*/



class zCCacheBase{
public:
    zCCacheBase                 ();
    virtual ~zCCacheBase        ();

    virtual void PurgeCache     ()=0;           // deletes all old data in this cache
    virtual void ClearCache     ()=0;           // deletes ALL     data in this cache

    static void S_PurgeCaches   ();             // delete all old data in all caches
    static void S_ClearCaches   ();             // delete ALL     data in all caches

    void SetTimeout             (int to)                {timeout=to;}
    int  GetTimeout             ()       const          {return timeout;}

    static int S_GetCurrentFrame()                      {return s_currentFrame;}
protected:
    int                    timeout;        // a cache element is considered old if it was not used for this number of frames

    static int             s_currentFrame;
    static zCCacheBase    *s_anchor;       // data for double linked list
    static zCCacheBase    *s_run;          // the cache that was purged last frame
    zCCacheBase           *next;
    zCCacheBase          **anchor;
};


// *****************************************************
// *****************************************************
//  zCCache: SparseArray that deletes its unused entries
// *****************************************************
// *****************************************************


template <class Index, class Data> class zCCacheData{
    Data    *data;
    int      lastFrameUsed;

public:
    zCCacheData()                               :data(NULL), lastFrameUsed(zCCacheBase::S_GetCurrentFrame()){}
    ~zCCacheData()                              {Clear();}

    void  Clear()                               {delete data; data=NULL;}
    Data *GetDataDangerous()                    {                                                                                       return data;}
    Data *GetData(const Index &index)           {if (!data) data = zNEW(Data)(index); lastFrameUsed = zCCacheBase::S_GetCurrentFrame(); return data;}
    zBOOL Purge(int timeout)                    {if (zCCacheBase::S_GetCurrentFrame() - lastFrameUsed > timeout) { Clear(); return TRUE; } return FALSE;}

    Data *GetData(const Index &index,zBOOL &neu){neu = FALSE; if (!data) { data = zNEW(Data)(index); neu = TRUE; } lastFrameUsed = zCCacheBase::S_GetCurrentFrame(); return data;}
};



template <class Index, class Data> class zCCache: public zCCacheBase, protected zCSparseArray<Index, zCCacheData<Index,Data> >{
public:
    zCCache                 (zUINT32 size=13, zUINT32 timeout= 100)                 :zCSparseArray<Index,zCCacheData<Index,Data> > (size)   {SetTimeout(timeout);}
    ~zCCache                ()                                                      {ClearCache();}

    Data *operator[]        (const Index &index)                                    { zCCacheData<Index,Data> *r=zCSparseArray<Index,zCCacheData<Index,Data> >::Insert(index);     zCSparseArrayIterator i(*this); return  r->GetData(index);          }
    Data *GetData           (const Index &index, zBOOL &neu)                        { zCCacheData<Index,Data> *r=zCSparseArray<Index,zCCacheData<Index,Data> >::Insert(index);     zCSparseArrayIterator i(*this); return  r->GetData(index, neu);     }
    Data *GetDataDangerous  (const Index &index)                                    { zCCacheData<Index,Data> *r=zCSparseArray<Index,zCCacheData<Index,Data> >::operator[](index); zCSparseArrayIterator i(*this); if (r) return r->GetDataDangerous(); else return NULL;     }
    void  Delete            (const Index &index)                                    { zCCacheData<Index,Data> *r=zCSparseArray<Index,zCCacheData<Index,Data> >::operator[](index); zCSparseArrayIterator i(*this); if (r) { r->Clear(); zCSparseArray<Index,zCCacheData<Index,Data> >::Delete(index); }  }

    virtual void  ClearCache()  {
        for(zCSparseArrayIterator i(*this); i; i.Next())
        {
            zCSparseArray<Index,zCCacheData<Index,Data> >::operator[](i)->Clear();
            zCSparseArray<Index,zCCacheData<Index,Data> >::Delete(i);
        }
    }

    virtual void PurgeCache()   {
        for(zCSparseArrayIterator i(*this); i; i.Next())
            if (zCSparseArray<Index,zCCacheData<Index,Data> >::operator[](i)->Purge(timeout))
                zCSparseArray<Index,zCCacheData<Index,Data> >::Delete(i);
    }
};

// like cache; but before a cache-element is deleted, the Data´s member-function DontDelete() is checked.
template <class Index, class Data> class zCCacheAsk: public zCCache<Index, Data>{
public:
    zCCacheAsk                 (zUINT32 size=13, zUINT32 timeout= 100)              :zCCache<Index, Data> (size, timeout)   {}
    ~zCCacheAsk                ()                                                   {}

    virtual void PurgeCache()   {
        for(zCSparseArrayIterator i(*this); i; i.Next())
            if (!zCSparseArray<Index,zCCacheData<Index,Data> >::operator[](i)->GetDataDangerous()->DontDelete() && 
                 zCSparseArray<Index,zCCacheData<Index,Data> >::operator[](i)->Purge(timeout))
                zCSparseArray<Index,zCCacheData<Index,Data> >::Delete(i);
    }
};

// *****************************************************************
//                     Implementation
// *****************************************************************

template <class Index> inline void Hash(const Index *index, zUINT32 p, zUINT32 &hasha, zUINT32 &hashb){
    ::Hash(index, p, hasha, hashb, sizeof(Index));
};

#endif // __ZSPARSEARRAY_H__
