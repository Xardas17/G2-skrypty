/******************************************************************************** 
 
     $Workfile:: zMemory_Base.h       $                $Date:: 4.12.00 16:49    $
     $Revision:: 6                    $             $Modtime:: 4.12.00 16:42    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ memory management wrapper
   created       : 11.7.2000

 * $Log: /current_work/zengin_work/_Dieter/zMemory_Base.h $
 * 
 * 6     4.12.00 16:49 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 2     9.08.00 17:12 Admin
 * 
 * 4     20.07.00 19:48 Hildebrandt
 * 
 * 3     19.07.00 15:56 Hildebrandt
 * 
 * 2     18.07.00 18:13 Hildebrandt
 * 
 * 2     18.07.00 17:01 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 6 $ ($Modtime: 4.12.00 16:42 $)

// ===============================================================================================================

#ifndef __ZMEMORY_BASE_H__
#define __ZMEMORY_BASE_H__

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

// ===============================================================================================================

// Memory allocator interface


struct zTMallocStats 
{
	// implementations set members to -1 if they cannot provide that information
	int			numBlocks;					// current number of blocks allocated
	int			numBlocksPeak;				// Peak of blocks
	int			numBytesAllocated;			// current allocated bytes in heapmanager
	int			numBytesAllocatedPeak;		// Peak of allocated memory
	int			numAllocs;					// number of allocations since snapshot/startup
	int			numFrees;					// number of frees since snapshot/startup
	zSQWORD		numBytesAllocatedTotal;		// memory allocated since snapshot/startup
	zSQWORD		numBytesFreedTotal;			// memory freed since snapshot/startup
};

struct zTMallocProcessStats
{
	zDWORD		fixedMem;					// fixed used memory, could not moved
	zDWORD		freeMem;					// free memory, not used
	zDWORD		moveable;					// used memory, could be moved
};

enum zTMallocDumpHeapMode
{
	zMALLOC_SORT_BY_BYTES_PER_LINE,
	zMALLOC_SORT_BY_BLOCKS_PER_LINE,
	zMALLOC_SORT_BY_CLASS,
	zMALLOC_SORT_BY_BLOCK_SIZE,
	zMALLOC_SORT_BY_FILE,
	zMALLOC_SORT_BY_TIME,
};

enum zTMallocCheckPtrError
{
	zMALLOC_CHECK_PTR_OK			=0,		// memory status is ok
	zMALLOC_CHECK_PTR_INVALID_PTR	,		// this is an invalid ptr. Not registered in heapmanager
	zMALLOC_CHECK_PTR_CORRUPTED_MEM	,		// this is a valid ptr, but the memory area was corrupted
	zMALLOC_CHECK_PTR_NOT_ACTIVATED	,		// heapmanager is not activated
	zMALLOC_CHECK_PTR_NULL_PTR		,		// this is a null ptr
};

class zCMalloc {
public:
			 zCMalloc() {};
	virtual ~zCMalloc() {};

	// alloc/free
	virtual void*					Malloc			(unsigned int size)=0;
	virtual void*					Malloc			(unsigned int size, const char *className, const char *file, int line)=0;
	virtual void*					Realloc			(void* ptr, unsigned int size)=0;
	virtual void					Free			(void* ptr)=0;

	// get information
	virtual zBOOL					GetStats		(zTMallocStats&			mallocStats)		{ return FALSE; };
	virtual zBOOL					GetProcessStats	(zTMallocProcessStats&	mallocProcessStats) { return FALSE; };
	virtual zBOOL					DumpHeap		(zTMallocDumpHeapMode	dumpHeapMode)		{ return FALSE; };

	// check consistency
	virtual zBOOL					CheckHeap		()			{ return TRUE; };	
	virtual zTMallocCheckPtrError	CheckPtr		(void* ptr) { return zMALLOC_CHECK_PTR_NOT_ACTIVATED; };

	// init/shutdown
	virtual zBOOL					Init			(zBOOL activateProfiler)=0;
	virtual zBOOL					Shutdown		()=0;	
};

// ===============================================================================================================

#endif