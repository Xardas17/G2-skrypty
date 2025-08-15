/******************************************************************************** 
 
     $Workfile:: zMemory_Win32.h      $                $Date:: 4.12.00 16:49    $
     $Revision:: 7                    $             $Modtime:: 4.12.00 16:43    $
       $Author:: Hildebrandt          $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ memory management wrapper
   created       : 11.7.2000

 * $Log: /current_work/zengin_work/_Dieter/zMemory_Win32.h $
 * 
 * 7     4.12.00 16:49 Hildebrandt
 * 
 * 6     25.08.00 18:38 Hoeller
 * 
 * 5     1.08.00 14:01 Hoeller
 * 
 * 4     28.07.00 19:52 Hoeller
 * 
 * 3     21.07.00 14:28 Hoeller
 * 
 * 2     20.07.00 19:49 Hoeller
 * 
 * 1     20.07.00 19:04 Hoeller
 * 
 * 2     18.07.00 17:01 Höller
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 7 $ ($Modtime: 4.12.00 16:43 $)

#ifndef __ZMEMORY_WIN32_H__
#define __ZMEMORY_WIN32_H__

//#include <malloc.h>
// forward declarations
#ifndef __ZMEMORY_BASE_H__
#include <zMemory_Base.h>
#endif

// ===============================================================================================================


class zCMallocWin32Debug : public zCMalloc {
public:
	void*	Malloc			(unsigned int size);
	void*	Malloc			(unsigned int size, const char *className, const char *file, int line);
	void*	Realloc			(void* ptr, unsigned int size);
	void	Free			(void* ptr);

	zBOOL	Init			(zBOOL activateProfiler);
	zBOOL	Shutdown		();	

	zBOOL					GetStats		(zTMallocStats&			mallocStats);
	zBOOL					GetProcessStats	(zTMallocProcessStats&	mallocProcessStats);
	zBOOL					DumpHeap		(zTMallocDumpHeapMode	dumpHeapMode);

	void					CheckRestOfHeap();
	// check consistency
	zBOOL					CheckHeap		();	
	zTMallocCheckPtrError	CheckPtr		(void* ptr);
protected:
	// protected sort methods described in enum zTMallocDumpHeapMode, Mem is only prefix for sort order
	zBOOL					MemSortBytesPerLine();
	zBOOL					MemSortBlocksPerLine();
	zBOOL					MemSortClass();
	zBOOL					MemSortBlockSize();
	zBOOL					MemSortFile();
	zBOOL					MemSortTime();
	// add heaplist into an array which will be arranged later via qsort
	void					InsertInSortList(void* _sortList);
	void					ShowzSpyMemHeader(char *typeName);
	void					PrintOutput(void *_heapBlock);
	void					ResetOutput();
private:
	unsigned int			RuntimeLine;
	unsigned int			RuntimeMemSize;
	unsigned int			RuntimeBlocks;
	unsigned int			RuntimeResultBlock;
	unsigned int			RuntimeResultMemSize;
	char					RuntimeFilename[400];
	char					RuntimeName[400];
	char					Buffer[400];
	zBOOL					ShowNoFilename;
	zBOOL					ShowNoName;
};

// ===============================================================================================================

#endif