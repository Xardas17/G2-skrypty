/******************************************************************************** 
 
     $Workfile:: zMemPool.h      $                $Date:: 8.02.01 10:46    $
     $Revision:: 8                       $             $Modtime:: 7.02.01 10:48    $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Generic memory pooling classes
   created: 1.12.2000

 * $Log: /current_work/ZenGin/_Dieter/zMemPool.h $
 * 
 * 8     8.02.01 10:46 Moos
 * 
 * 7     28.01.01 12:30 Moos
 * 
 * 6     25.01.01 12:14 Moos
 * 
 * 5     13.12.00 10:11 Moos
 * 
 * 4     6.12.00 18:06 Moos
 * 
 * 3     5.12.00 12:04 Moos
 * 
 * 2     4.12.00 18:22 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 7.02.01 10:48 $)

#ifndef __ZMEMPOOL_H__
#define __ZMEMPOOL_H__

#include <assert.h>

typedef enum { zVOLATILE_OVERFLOW_FORBID, zVOLATILE_OVERFLOW_WRAP, zVOLATILE_OVERFLOW_RESIZE } zTVolatileOverflowMode;

class zCMemPoolBlock;
class zCFreeBlock;

// This class is responsible for managing a single block of allocated memory, filled with small objects of size <size>.
// The contents MUST NOT be disposed by delete; they are automatically destroyed when the block gets deleted.

// If you don´t mind that allocated objects get overwritten in an emergency, set the <overflow> parameter of the constructors to zVOLATILE_OVERFLOW_WRAP.
// If you only store the objects returned by Alloc() by their Index, you can allow the Mempool to be resized when neccesarry
// by setting <overflow> to zVOLATILE_OVERFLOW_RESIZE.
// every time an object is destroyed, the virtual function Destroyed(void *mem) is called. It must work if called twice on the same
// adress, too.


class zCVolatileMemoryBase{
public:
    zCVolatileMemoryBase    (size_t size, size_t num, zTVolatileOverflowMode overflow=zVOLATILE_OVERFLOW_FORBID); // aloocate space for num objects. 
    zCVolatileMemoryBase    (size_t size,             zTVolatileOverflowMode overflow=zVOLATILE_OVERFLOW_FORBID); // Don't allocate the memory yet; let Init() handle thant 
    ~zCVolatileMemoryBase   ();                                                                                   // frees the memory allocated by this block

    void Init               (size_t num);      // allocates space for num objects
    void *Alloc             ();                // allocates one object in this block.

    size_t Mark             ();                // saves the current allocation status in the return value
    void   Restore          (size_t m=0);      // restores the state given by m, deleting all objects that were allocated since the
                                               // call of Mark() that returned it. The default argument deletes all objects.

    void   MaxFillPercentage(int perc);        // Inrease the buffer size if the fill ratio exceeds perc. (Default: 80%)
                                               // buffer is reallocated ONLY ON CALL of Restore(0).

protected:
    virtual void Destroyed  (void *ptr){};     // called every time an object was deleted

    size_t                 size, num, nextfree;// size of each object, total number of objects and index of next free object
    size_t                 maxAllocated;       // maximum value of nextfree
    int                    maxFill;            // if the percentage of allocated objects gets higher than this, the Block is enlaged.
    zTVolatileOverflowMode overflowMode;       // what should happen if overflow occurs
    zBOOL                  overflow;           // has an overflow happened
    void                  *data;               // the real data
};


template <class T> class zCVolatileMemory: public zCVolatileMemoryBase{
    virtual void Destroyed(void *ptr){
        ((T*) ptr)->~T();
    }
public:
    zCVolatileMemory(size_t num, zTVolatileOverflowMode overflow=zVOLATILE_OVERFLOW_FORBID)   :zCVolatileMemoryBase(sizeof(T), num, overflow){}
    zCVolatileMemory(            zTVolatileOverflowMode overflow=zVOLATILE_OVERFLOW_FORBID)   :zCVolatileMemoryBase(sizeof(T),      overflow){}

    T *CreateNew()                                              {return new(Alloc()) T;}                             // Creates a new object of type T in the pool
    T &Element(int i)                                           {assert(0<=i && i <num); return ((T*)data)[i];} // treats the pool as an array
    T &operator[](int i)                                        {return Element(i);}

    int LastAllocatedIndex()                                    {return nextfree-1;}                                 // the index of the object that was last allocated

    int Index(T *o)                                                                                                  // inverse of Element() 
    {
        int ret = ((int)o - (int)data) / sizeof(T);
        assert(0 <= ret && ret < num);

        return ret;
    }
};

/*
 if you want your class <CLASS> to be managed by a single object of above class, just write 
 zMEMPOOL_VOLATILE_DECLARATION(CLASS)
 in the class definition and in some .cpp-file
 zMEMPOOL_VOLATILE_DEFINITION(CLASS, number_of_objects, allow_overflow)
 and IN ALL CLASSES derived from CLASS.

 if you set allow_overflow to true, remember that the destructor ~CLASS may be called twice
 on the same object.

 Then, new and delete for that class will be owerridden with implementations that use a zCVolatileMemory.
 And you can use the static member fuctions PoolMark() and PoolRestore() just as Mark() and
 Restore() in zCVolatileMemory.
*/

#define zMEMPOOL_VOLATILE_DECLARATION( classname )                                                  \
private:                                                                                            \
    static zCVolatileMemory<classname> s_MemMan;                                                    \
public:                                                                                             \
    void *operator new     (size_t s){                                                              \
        assert(s == sizeof(classname));                                                        \
        return s_MemMan.Alloc();                                                                    \
    }                                                                                               \
                                                                                                    \
    void  operator delete  (void *p) {                                                              \
        zERR_FAULT(zSTRING("Can't delete an object of class ") +                                    \
                   zSTRING(#classname) + zSTRING("."));                                             \
    }                                                                                               \
                                                                                                    \
    void* operator new	   (unsigned int size,const char *classn,const char *file,int l){           \
        return operator new(size);                                                                  \
    }                                                                                               \
                                                                                                    \
    void  operator delete  (void *ptr,const char *classn,const char *file,int line){                \
        operator delete(ptr);                                                                       \
    }                                                                                               \
                                                                                                    \
    static size_t     PoolMark                ()             {return s_MemMan.Mark();}              \
    static void       PoolRestore             (size_t m=0)   {s_MemMan.Restore(m);}                 \
    static classname &PoolElement             (int i)        {return s_MemMan.Element(i);}          \
    static int        PoolIndex               (classname *o) {return s_MemMan.Index(o);}            \
    static int        PoolLastAllocatedIndex  ()             {return s_MemMan.LastAllocatedIndex();}

#define zMEMPOOL_VOLATILE_DEFINITION(classname,num)                  zCVolatileMemory<classname> classname::s_MemMan(num);
#define zMEMPOOL_VOLATILE_DEFINITION_OVERFLOW(classname,num,overfl)  zCVolatileMemory<classname> classname::s_MemMan(num, overfl);



/*  ***********************************************************************
    ***********************************************************************
    ***********************************************************************  */


// this class is more flexible and easier to handle (you can create and delete individual objects), but of course
// it does not have all the benefits of the simple block. Basically it´s a full memory manager with zero overhead
// (if your object has a size >= 8 bytes) that never returns memory to the system and can't report leaks.

// if you want to specify the number of elements in each memory block, use the second constructor.

class zCMemPoolBase{
public:
    zCMemPoolBase(size_t size);
    zCMemPoolBase(size_t size, size_t blocksize, size_t prealloc=0);
    ~zCMemPoolBase();

    void* Alloc();      // normal allocation and deletion; can ba called any time
    void Free(void* p);

    void        PreAlloc   (size_t num, zBOOL force_oneblock=FALSE); // the next num elements allocated by Alloc() should all reside inside one block

    static void SetMemDebug(const char *classname, const char *filename, int line);
    static void DisablePools(zBOOL disable);
    size_t      SizeOf      () const                                                  {return size;}
protected:
    size_t          size;          // site of each object
    size_t          blocksize;     // default number of elements in each block
    zCMemPoolBlock *blocks;        // the memblocks
    zCFreeBlock    *freeList;      // list of free places
    size_t          numFree;       // number of currently free places
    size_t          preallocate;   // number of objects to preallocate before the next Alloc
    zBOOL           forcePrealloc; // should these objects be forced to be in one block?

    static const char *s_className; // for memory debugging
    static const char *s_fileName;
    static int         s_line;

    static zBOOL       s_disablePools;

    friend class zCMemPoolBlock;

    void        PoolAdd    (void *mem,  int num_objects, zBOOL free = FALSE);
};



template <class T> class zCMemPool: public zCMemPoolBase{
public:
    zCMemPool()                                              :zCMemPoolBase(sizeof(T)){}
    zCMemPool(size_t blocksize, size_t prealloc=0)           :zCMemPoolBase(sizeof(T),blocksize, prealloc){}

    T *CreateNew()                                            {return new(Alloc()) T;}
    void Destroy(T *p)                                        {p->~T(); Free(p);}

    void PoolAdd(T *mem, int num_objects, zBOOL free = FALSE) {zCMemPoolBase::PoolAdd(mem, num_objects, free);}
};

/*
 if you want your class <CLASS> to be managed by a single MemPool memmanager, just write 
 zMEMPOOL_DEF(CLASS)
 in the class definition and in some .cpp-file
 MEMMPOOL_VOLATILE_DECL(CLASS)
 and IN ALL CLASSES derived from CLASS.
 
 Then, new and delete for that class will be owerridden with implementations that use a zCMemPool.

 if your class is derived from zCObject, you have to write
 zOBJECT_MEMPOOL_DEF(CLASS)
 instead of
 zCLASS_DECLARATION(CLASS)
 zMEMPOOL_DEF(CLASS)
*/

#define zMEMPOOL_DECLARATION( classname )                                                           \
private:                                                                                            \
    static zCMemPool<classname> s_MemPool;                                                          \
public:                                                                                             \
    void *operator new   (size_t s){                                                                \
        assert(s == sizeof(classname));                                                             \
        return s_MemPool.Alloc();                                                                   \
    }                                                                                               \
                                                                                                    \
    void  operator delete(void *p) { s_MemPool.Free(p);}                                            \
                                                                                                    \
    void* operator new	 (unsigned int size,const char *classn,const char *file,int l){             \
        zCMemPoolBase::SetMemDebug(classn,file,l);                                                  \
        return operator new(size);                                                                  \
    }                                                                                               \
                                                                                                    \
    void  operator delete(void *ptr,const char *classn,const char *file,int line){                  \
        operator delete(ptr);                                                                       \
    }                                                                                               \
                                                                                                    \
    static void PreAlloc(size_t num, zBOOL force_oneblock=FALSE){                                   \
        s_MemPool.PreAlloc(num,force_oneblock);                                                     \
    }                                                                                               \
                                                                                                    \
    static void PoolAdd(classname *mem, int num_objects, zBOOL free = FALSE) {                      \
        s_MemPool.PoolAdd(mem, num_objects, free);                                                  \
    }

#define zOBJECT_MEMPOOL_DECLARATION( classname )                                                    \
private:                                                                                            \
    static  zCMemPool<classname> s_MemPool;                                                         \
	static	zCClassDef		classname::classDef;		                                            \
	static	zCObject*		classname::_CreateNewInstance	( void );			                    \
	virtual	zCClassDef*		classname::_GetClassDef			( void ) const { return &(classname::classDef); }; \
public:                                                                                             \
	static	zCClassDef*		classname::GetStaticClassDef(void){ return &(classname::classDef); };   \
                                                                                                    \
    void *operator new   (size_t s){                                                                \
        assert(s == sizeof(classname));                                                        \
        void *ptr = s_MemPool.Alloc();                                                              \
        zCClassDef::ObjectCreated ((zCObject*)ptr, &classname::classDef);                           \
        return ptr;                                                                                 \
    }                                                                                               \
                                                                                                    \
    void  operator delete(void *p) {                                                                \
        zCClassDef::ObjectDeleted ((zCObject*)p, &classname::classDef);                             \
        s_MemPool.Free(p);                                                                          \
    }                                                                                               \
                                                                                                    \
    void* operator new	 (unsigned int size,const char *classn,const char *file,int l){             \
        zCMemPool::SetMemDebug(classn,file,l);                                                      \
        assert(s == sizeof(classname));                                                             \
        void *ptr = s_MemPool.Alloc();                                                              \
        zCClassDef::ObjectCreated ((zCObject*)ptr, &classname::classDef, file, l);                  \
        return ptr;                                                                                 \
    }                                                                                               \
                                                                                                    \
    void  operator delete(void *ptr,const char *classn,const char *file,int line){                  \
        operator delete(ptr);                                                                       \
    }                                                                                               \
                                                                                                    \
                                                                                                    \
	void*					classname::operator new[]		(size_t size)															{ zerr.Fault("D: OBJ: illegal new[] on class: " #classname); return 0; }; \
	void*					classname::operator new[]		(unsigned int size, const char *classNAME, const char *file, int line)	{ zerr.Fault("D: OBJ: illegal new[] on class: " #classname); return 0; }; \
	void					classname::operator delete[]	(void* ptr)																{ zerr.Fault("D: OBJ: illegal delete[] on class: " #classname); }; \
	void					classname::operator delete[]	(void* ptr, const char *classNAME, const char *file, int line)			{ zerr.Fault("D: OBJ: illegal delete[] on class: " #classname); }; \
                                                                                                    \
                                                                                                    \
    static void PreAlloc(size_t num, zBOOL force_oneblock=FALSE){                                   \
        s_MemPool.PreAlloc(num,force_oneblock);                                                     \
    }


// everything to default values (64k block allocations, no prealloc)
#define zMEMPOOL_DEFINITION(classname)               zCMemPool<classname> classname::s_MemPool;

// specify block size in elements
#define zMEMPOOL_DEFINITION_BS(classname, bs)        zCMemPool<classname> classname::s_MemPool(bs);

// specify block size and initial prealloc
#define zMEMPOOL_DEFINITION_BS_PA(classname, bs, pa) zCMemPool<classname> classname::s_MemPool(bs, pa);









// extra stuff for the containers in zContainer.h

// NOTE: this is only possible if ALL instances of the template class have the same size!


// for the header file. 

#define zMEMPOOL_DECLARATION_TEMPLATE( classname , poolname)                                        \
public:                                                                                             \
    void *operator new   (size_t s){                                                                \
        assert(s == poolname.SizeOf());                                                        \
        return poolname.Alloc();                                                                    \
    }                                                                                               \
                                                                                                    \
    void  operator delete(void *p) { poolname.Free(p);}                                             \
                                                                                                    \
    void* operator new	 (unsigned int size,const char *classn,const char *file,int l){             \
        zCMemPoolBase::SetMemDebug(classn,file,l);                                                  \
        return operator new(size);                                                                  \
    }                                                                                               \
                                                                                                    \
    void  operator delete(void *ptr,const char *classn,const char *file,int line){                  \
        operator delete(ptr);                                                                       \
    }                                                                                               \
                                                                                                    \
    static void PreAlloc(size_t num, zBOOL force_oneblock=FALSE){                                   \
        poolname.PreAlloc(num,force_oneblock);                                                      \
    }

// for the header, to be placed before the template declaration
#define zMEMPOOL_DECLARATION_TEMPLATE_EXTRA( classname, poolname )   extern zCMemPoolBase poolname;


// for the cpp-File

// everything to default values (64k block allocations, no prealloc)
#define zMEMPOOL_DEFINITION_TEMPLATE(classname, poolname)               zCMemPoolBase poolname(sizeof(classname));

// specify block size in elements
#define zMEMPOOL_DEFINITION_TEMPLATE_BS(classname, poolname, bs)        zCMemPoolBase poolname(sizeof(classname), bs);

// specify block size and initial prealloc
#define zMEMPOOL_DEFINITION_TEMPLATE_BS_PA(classname, poolname, bs, pa) zCMemPoolBase poolname(sizeof(classname), bs, pa);

#endif



