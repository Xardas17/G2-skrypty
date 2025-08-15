/******************************************************************************** 
 
     $Workfile:: zMemory_Win32.cpp    $                $Date:: 10.10.00 15:46   $
     $Revision:: 15                   $             $Modtime:: 10.10.00 15:26   $
       $Author:: Speckels                                                 $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ memory management wrapper
   created       : 11.7.2000

 * $Log: /current_work/ZenGin/_Dieter/zMemory_Win32.cpp $
 * 
 * 15    10.10.00 15:46 Speckels
 * 
 * 14    8.09.00 20:31 Hildebrandt
 * 
 * 13    29.08.00 13:03 Hoeller
 * 
 * 12    25.08.00 18:38 Hoeller
 * 
 * 11    22.08.00 18:25 Hoeller
 * 
 * 10    22.08.00 15:20 Hoeller
 * 
 * 9     16.08.00 19:21 Hoeller
 * 
 * 8     8.08.00 17:35 Hoeller
 * 
 * 7     3.08.00 14:56 Hoeller
 * 
 * 6     3.08.00 13:37 Hoeller
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
/// @author $Author: Speckels $
/// @version $Revision: 15 $ ($Modtime: 10.10.00 15:26 $)

#include <zMemory.h>
#include <zMemory_Win32.h>
#include <zError.h>
#include <zString.h>

#include <zwin32.h>

#include "malloc.h"


//////////////////////////////////////////////////////////////////////////////////
// compatibility structures: interface sysmanager
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
// typedef of primitivetypes
typedef void*			GELPVoid;
typedef const void*		GELPCVoid;
typedef char*			GELPChar;
typedef const char*		GELPCChar;
typedef char			GEChar;
typedef unsigned char	GEU8;
typedef signed   char	GEI8;
typedef unsigned short	GEU16;
typedef signed   short	GEI16;
typedef signed   long	GEI32;
typedef unsigned long	GEU32;
typedef int				GEInt;
typedef signed __int64	GEI64;
typedef unsigned __int64 GEU64;
typedef bool			GEBool;
typedef float			GEFloat;
typedef double			GEDouble;
//////////////////////////////////////////////////////////////////////////////////
#define GETrue			true
#define GEFalse			false

#define NULL 0

//////////////////////////////////////////////////////////////////////////////////
// heapblock
struct GESHeapBlock
{
	GELPChar		Name;			// custom name of allocated block
	GELPChar		ObjName;		// name of object
	GELPChar		TypeName;		// Name of classtype
	GELPChar		File;			// File of allocated block
	GEU16			Line;			// line of code
	GEU16			Reallocs;		// reallocs per ptrentry
	size_t			Size;			// size of allocated block
	GELPVoid		Ptr;			// points to the block
	GEU32			TimeStamp;		// 32 bit timestamp of allocated or reallocated block
	GEU8			StrucType;		// type per c or c++ style allocation
};
//////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
// heapstatistics structure
struct GESHeapBlockStatistic
{
	GEInt	NumOfBlocks;			// current number of blocks allocated
	GEU32	AllocatedBytes;			// current allocated bytes in heapmanager
	GEInt	PeakNumOfBlocks;		// Peak of blocks
	GEU32	PeakAllocatedMemory;	// Peak of allocated memory
	GEInt	NumberOfAllocs;			// number of allocations since snapshot/startup
	GEInt	NumberOfFrees;			// number of frees since snapshot/startup
	GEU64	MemoryAllocated;		// memory allocated since snapshot/startup
	GEU64	MemoryFreed;			// memory freed since snapshot/startup
};
//////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
// GECheckMemPtr return values
enum GEECheckPtr_Error
{
	GEECheckPtr_OK = 0x00,					// memory status is ok
	GEECheckPtr_InvalidPtr = 0x01,			// this is an invalid ptr. Not registered in heapmanager
	GEECheckPtr_CorruptedArea = 0x02,		// this is a valid ptr, but the memory area was corrupted
	GEECheckPtr_NotActivated = 0x03,		// heapmanager is not activated
	GEECheckPtr_NullPtr = 0x04,				// this is a null ptr
	GEECheckPtr_ForceDWORD = 0x7fffffff		// compatibility
};
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
// HEAP INFO STRUC
struct GESHeapInfo
{
	GEU32		FixedMem;		// fixed used memory, could not moved
	GEU32		FreeMem;		// free memory, not used
	GEU32		Moveable;		// used memory, could be moved
};
////////////////////////////////////////////////////////////////////////////////////////////


#ifndef GE_SYSMAN_CALLAPI
	#define GE_SYSMAN_CALLAPI __stdcall
#endif
#define DllImport extern __declspec( dllimport )

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INITIALIZATION
// used to initialize heapprofiler
DllImport	void					GE_SYSMAN_CALLAPI GEInit(GEBool heapProfilerActivate, GEInt majorVersion, GEInt minorVersion, GEInt build);
DllImport	void					GE_SYSMAN_CALLAPI GEFinit();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get current starttime of APP
// not used for gothic ?
DllImport	GEU32					GE_SYSMAN_CALLAPI GEGetAppStartTime();
DllImport	void					GE_SYSMAN_CALLAPI GESetStartTime();
DllImport	GEU32					GE_SYSMAN_CALLAPI GEGetCurrentTime();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MEMORY
// memory support functions
DllImport	GELPVoid				GE_SYSMAN_CALLAPI GESysMalloc(const size_t size, GELPChar objType, GELPChar name, GELPChar file, GEInt line);
DllImport	GELPVoid				GE_SYSMAN_CALLAPI GESysCalloc(const size_t num, const size_t size, GELPChar objType, GELPChar name, GELPChar file, GEInt line);
DllImport	void					GE_SYSMAN_CALLAPI GEFree(GELPVoid block);
DllImport	GELPVoid				GE_SYSMAN_CALLAPI GESysRealloc(GELPVoid block, const size_t size, GELPChar objType, GELPChar name, GELPChar file, GEInt line);

DllImport	GELPVoid				GE_SYSMAN_CALLAPI GENew(const size_t size, GELPChar objMem, GELPChar objType, GELPChar name, GELPChar file, GEInt line);
DllImport	void					GE_SYSMAN_CALLAPI GEDelete(GELPVoid block);
DllImport	GELPVoid				GE_SYSMAN_CALLAPI GENewArray(const size_t size, GELPChar objMem, GELPChar objType, GELPChar name, GELPChar file, GEInt line);
DllImport	void					GE_SYSMAN_CALLAPI GEDeleteArray(GELPVoid block);

// HeapDump, not used in gothic ?
// DllImport	void					GE_SYSMAN_CALLAPI GEDumpHeap(GECBOutMessage msgOut, GEBool restrict);
// checks specified pointer if valid
DllImport	GEECheckPtr_Error		GE_SYSMAN_CALLAPI GECheckMemPtr(const GELPVoid block);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HEAPPROFILER
// show heapdialog
DllImport	void					GE_SYSMAN_CALLAPI GEShowHeapDialog();
// get heapblock *ptr = NULL starts enumeration
DllImport	GEBool					GE_SYSMAN_CALLAPI GEGetHeapBlock(GESHeapBlock **heapBlock);
// get statistics about running heap
DllImport	void					GE_SYSMAN_CALLAPI GEGetHeapStatistics(GESHeapBlockStatistic *heapBlockStatistics);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// memory snapshot functions
DllImport	GESHeapBlockStatistic*	GE_SYSMAN_CALLAPI GECreateHeapSnapshot();
// destroy snapshot heap
DllImport	GEBool					GE_SYSMAN_CALLAPI GEDestroyHeapSnapshot(GESHeapBlockStatistic *heapBlockStat);
// get heapsnapshot
DllImport	GESHeapBlockStatistic*	GE_SYSMAN_CALLAPI GEGetHeapSnapshot(GEU16 index);
// get count of snapshot
DllImport	GEU16					GE_SYSMAN_CALLAPI GEGetHeapSnapshotCount();
// get current heap
DllImport	GEBool					GE_SYSMAN_CALLAPI GEGetHeapMemory(GESHeapInfo *heapInfo);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// small Array template
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> class GETSmallArrayNative
{
private:
	GEU32		Entries;

	void Grow()
	{
		GEInt delta;
		if(Used>=Entries)
		{
			if (Entries > 64) delta = Entries / 4;
			else
			{
				if (Entries > 8) delta = 16;
				else delta = 4;
			}
			Entries += delta;
			T* newEntry = (T*)realloc(Entry, sizeof(T)*Entries);
			Entry = newEntry;
		}
	}

public:
	GEU32		Used;
	T			*Entry;

	GETSmallArrayNative()
	{
		Entries = 1;
		Entry=(T*)malloc(sizeof(T)*Entries);
		memset(Entry, 0, sizeof(T)*Entries);
		Used = 0;
	}
	GETSmallArrayNative(GEInt entries)
	{
		Entries = entries;
		Entry=(T*)malloc(sizeof(T)*Entries);
		memset(Entry, 0, sizeof(T)*Entries);
		Used = 0;
	}
	
	GETSmallArrayNative<T> &operator=(GETSmallArrayNative<T> &classItem)
	{
		if( Entries == classItem.GetAllocatedEntries() )
		{
			Used = classItem.Used;
			memcpy(&Entry[0], &classItem.Entry[0], sizeof(T)*classItem.Used);
		}
		else
		{
			Used = classItem.Used;
			free(Entry);
			Entry=(T*)malloc(sizeof(T)*(classItem.Used+1));
			memcpy(&Entry[0], &classItem.Entry[0], sizeof(T)*classItem.Used);
		}
		return *this;
	}

	GEU32 GetAllocatedEntries()
	{
		return Entries;
	}

	GEBool Reserve(GEU32 entries)
	{
		if(entries<Entries)
			return GEFalse;
		Entries = entries;
		T* newEntry = (T*)realloc(Entry, sizeof(T)*Entries);
		Entry = newEntry;
		return GETrue;
	}

	GEU32 Add(T &item)
	{
		Grow();
		Entry[Used] = item;
		Used++;
		return Used-1;
	}

	void Remove(GEU16 ref)
	{
		if (Used==0) return;
		GEU32 i = Used-(ref+1);
		memmove(&Entry[ref], &Entry[ref+1], i*sizeof(T));
		Used--;
	}

	~GETSmallArrayNative() { free(Entry); }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct zCHeapBlock
{
	GESHeapBlock	*HeapBlock;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void* zCMallocWin32Debug::Malloc (unsigned int size)
{
//DllImport	GELPVoid				GE_SYSMAN_CALLAPI GENew(const size_t size, GELPChar objMem, GELPChar objType, GELPChar name, GELPChar file, GEInt line);
	return (void*) GENew(size_t(size), NULL, NULL, NULL, NULL, 0);
};

void* zCMallocWin32Debug::Malloc (unsigned int size, const char *className, const char *file, int line)
{
	//return (void*) GESysMalloc(size_t(size), NULL, GELPChar(className), GELPChar(file), GEInt(line));
	return (void*) GENew(size_t(size), NULL, GELPChar(className), NULL, GELPChar(file), GEInt(line));
};

void* zCMallocWin32Debug::Realloc (void* ptr, unsigned int size)
{
	// should be disabled
	return (void*) GESysRealloc(GELPVoid(ptr), size_t(size), NULL, NULL, NULL, 0);
};

void zCMallocWin32Debug::Free (void* ptr)
{
	GEDelete(GELPVoid(ptr));
	//GEFree(GELPVoid(ptr));
};

zBOOL zCMallocWin32Debug::Init(zBOOL activateProfiler) 
{
	// initialize sysmanager (major/minor/build not neccessary here)
	//GEInit(GEBool(activateProfiler), 0, 0, 0);
	// set current time for startstamp
	//GESetStartTime();
	zERR_MESSAGE(2, 0, "zCMallocWin32Debug::Init - Sysmanager#heapprofiler activated.");
	return TRUE;
};

zBOOL zCMallocWin32Debug::Shutdown() 
{
	//MemSortBlockSize();
	//GEFinit();
	zERR_MESSAGE(2, 0, "zCMallocWin32Debug::Shutdown - Sysmanager#heapprofiler deactivated.");
	return TRUE;
};	


zBOOL	zCMallocWin32Debug::GetStats (zTMallocStats& mallocStats)
{
	GESHeapBlockStatistic heapBlockStat;
	
	// not really neccessary here
	memset(&heapBlockStat, 0, sizeof(GESHeapBlockStatistic));
	GEGetHeapStatistics(&heapBlockStat);
	
	// structures are compatible for now do a memcopy
	mallocStats.numBlocks				= heapBlockStat.NumOfBlocks;			// current number of blocks allocated
	mallocStats.numBytesAllocated		= heapBlockStat.AllocatedBytes;			// current allocated bytes in heapmanager
	mallocStats.numBlocksPeak			= heapBlockStat.PeakNumOfBlocks;		// Peak of blocks
	mallocStats.numBytesAllocatedPeak	= heapBlockStat.PeakAllocatedMemory;	// Peak of allocated memory
	mallocStats.numAllocs				= heapBlockStat.NumberOfAllocs;			// number of allocations since snapshot/startup
	mallocStats.numFrees				= heapBlockStat.NumberOfFrees;			// number of frees since snapshot/startup
	mallocStats.numBytesAllocatedTotal	= heapBlockStat.MemoryAllocated;		// memory allocated since snapshot/startup
	mallocStats.numBytesFreedTotal		= heapBlockStat.MemoryFreed;			// memory freed since snapshot/startup
	return TRUE;
}

void	zCMallocWin32Debug::InsertInSortList(void* _sortList)
{
	// do an typecast
	GETSmallArrayNative<GESHeapBlock*> *sortList = static_cast<GETSmallArrayNative<GESHeapBlock*>*>(_sortList);
	GESHeapBlock *heapBlock = NULL;
	
	// first read heaplist into an array
	// get heapstatistics to reserve enough space in array
	GESHeapBlockStatistic heapStat;
	GEGetHeapStatistics(&heapStat);
	sortList->Reserve(heapStat.NumOfBlocks);
	
	while(GEGetHeapBlock(&heapBlock))
	{
		// trivial check and add
		if(heapBlock)
		{
			if(heapBlock->File)
				sortList->Add(heapBlock);	
		}
	}
}

void	zCMallocWin32Debug::ShowzSpyMemHeader(char *typeName)
{
	char Buffer[400];
	zERR_MESSAGE(0, 0, "=================================================================");
	sprintf(Buffer, "Memory Profiler: %s", typeName);
	zERR_MESSAGE(0, 0, Buffer);
	GESHeapBlockStatistic heapStat;
	GEGetHeapStatistics(&heapStat);
	sprintf(Buffer, "Heapentries: %d, Memory allocated: %d", heapStat.NumOfBlocks, heapStat.AllocatedBytes);
	zERR_MESSAGE(0, 0, Buffer);
	zERR_MESSAGE(0, 0, "");
}

zBOOL	zCMallocWin32Debug::GetProcessStats	(zTMallocProcessStats& mallocProcessStats)
{
	GESHeapInfo heapInfo;
	
	// not really neccessary here
	memset(&heapInfo, 0, sizeof(GESHeapInfo));
	GEGetHeapMemory(&heapInfo);

	// structures are compatible for now do a memcopy
	memcpy(&mallocProcessStats, &heapInfo, sizeof(zTMallocProcessStats));

	return TRUE;
}

zBOOL	zCMallocWin32Debug::MemSortBytesPerLine()
{
	GESHeapBlock *heapBlock = NULL;
	
	// first read heaplist into an array
	GETSmallArrayNative<GESHeapBlock*> heapListPure;
	// do heapBlocks it into array
	InsertInSortList((void*)&heapListPure);
	return TRUE;
}

zBOOL	zCMallocWin32Debug::MemSortBlocksPerLine()
{
	GESHeapBlock *heapBlock = NULL;
	
	// first read heaplist into an array
	GETSmallArrayNative<GESHeapBlock*> heapListPure;
	// do heapBlocks it into array
	InsertInSortList((void*)&heapListPure);
	return TRUE;
}



//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
int funcMemSortClass(const void *arg1, const void *arg2)
{
	GESHeapBlock *heapBlock1 = *((GESHeapBlock**)arg1);
	GESHeapBlock *heapBlock2 = *((GESHeapBlock**)arg2);
	if(heapBlock1->Name==NULL) return -1;
	if(heapBlock2->Name==NULL) return -1;
	if(_strcmpi(heapBlock1->Name, heapBlock2->Name)>0) return 1;
	if(_strcmpi(heapBlock1->Name, heapBlock2->Name)<0) return -1;
	if(_strcmpi(heapBlock1->File, heapBlock2->File)>0) return 1;
	if(_strcmpi(heapBlock1->File, heapBlock2->File)<0) return -1;
	if(heapBlock1->Line > heapBlock2->Line) return 1;
	if(heapBlock1->Line < heapBlock2->Line) return -1;
	if(heapBlock1->Size > heapBlock2->Size) return 1;
	if(heapBlock1->Size < heapBlock2->Size) return -1;
	return 0;
}
zBOOL	zCMallocWin32Debug::MemSortClass()
{
	GESHeapBlock *heapBlock = NULL;
	char nameBuffer[300];
	memset(nameBuffer, 0, sizeof(char)*300);
	ShowzSpyMemHeader("ClassSort");
	// first read heaplist into an array
	GETSmallArrayNative<GESHeapBlock*> heapListPure;
	// do heapBlocks it into array
	InsertInSortList((void*)&heapListPure);
	qsort(heapListPure.Entry, heapListPure.Used, sizeof(GESHeapBlock*), funcMemSortClass);
	ShowNoFilename = FALSE;
	ShowNoName = TRUE;
	RuntimeResultMemSize = 0;
	RuntimeResultBlock = 0;
	for(GEU32 i=0;i<heapListPure.Used;i++)
	{
		if(heapListPure.Entry[i]->Name!=NULL)
		{
			if(_stricmp(nameBuffer, heapListPure.Entry[i]->Name)!=0)
			{
				ResetOutput();
				if(RuntimeResultBlock>0)
				{
					sprintf(Buffer, "Results: Mem:%d  NumOfBlocks: %d", RuntimeResultMemSize, RuntimeResultBlock);
					zERR_MESSAGE(0, 0, Buffer);
				}
				RuntimeResultMemSize = 0;
				RuntimeResultBlock = 0;
				zERR_MESSAGE(0, 0, "-------------------------------------------");
				sprintf(Buffer, "Class: %s", heapListPure.Entry[i]->Name);
				zERR_MESSAGE(0, 0, Buffer);
				strcpy(nameBuffer, heapListPure.Entry[i]->Name);
				PrintOutput((void*)heapListPure.Entry[i]);
			}
			else
				PrintOutput((void*)heapListPure.Entry[i]);
		}
	}
	PrintOutput(NULL);
	if(RuntimeResultBlock>0)
	{
		sprintf(Buffer, "Results: Mem:%d  NumOfBlocks: %d", RuntimeResultMemSize, RuntimeResultBlock);
		zERR_MESSAGE(0, 0, Buffer);
	}
	zERR_MESSAGE(0, 0, "=================================================================")	;
	return TRUE;
}
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
int funcMemSortBlockSize(const void *arg1, const void *arg2)
{
	GESHeapBlock *heapBlock1 = *((GESHeapBlock**)arg1);
	GESHeapBlock *heapBlock2 = *((GESHeapBlock**)arg2);
	if(heapBlock1->File==NULL) return -1;
	if(heapBlock2->File==NULL) return -1;
	if(_strcmpi(heapBlock1->File, heapBlock2->File)>0) return 1;
	if(_strcmpi(heapBlock1->File, heapBlock2->File)<0) return -1;

	if(heapBlock1->Line > heapBlock2->Line) return 1;
	if(heapBlock1->Line < heapBlock2->Line) return -1;

	if(heapBlock1->Size > heapBlock2->Size) return 1;
	if(heapBlock1->Size < heapBlock2->Size) return -1;
	return 0;
}
zBOOL	zCMallocWin32Debug::MemSortBlockSize()
{
	GESHeapBlock *heapBlock = NULL;
	char fileBuffer[MAX_PATH];
	memset(fileBuffer, 0, sizeof(char)*MAX_PATH);
	ShowzSpyMemHeader("BlockSort");
	// first read heaplist into an array
	GETSmallArrayNative<GESHeapBlock*> heapListPure;
	// do heapBlocks it into array
	InsertInSortList((void*)&heapListPure);
	qsort(heapListPure.Entry, heapListPure.Used, sizeof(GESHeapBlock*), funcMemSortBlockSize);
	ShowNoFilename = TRUE;
	ShowNoName = FALSE;
	RuntimeResultMemSize = 0;
	RuntimeResultBlock = 0;
	for(GEU32 i=0;i<heapListPure.Used;i++)
	{
		if(heapListPure.Entry[i]->File!=NULL)
		{
			if(_stricmp(fileBuffer, heapListPure.Entry[i]->File)!=0)
			{
				ResetOutput();
				if(RuntimeResultBlock>0)
				{
					sprintf(Buffer, "Results: Mem:%d   NumOfBlocks: %d", RuntimeResultMemSize, RuntimeResultBlock);
					zERR_MESSAGE(0, 0, Buffer);
				}
				RuntimeResultMemSize = 0;
				RuntimeResultBlock = 0;
				zERR_MESSAGE(0, 0, "-------------------------------------------");
				sprintf(Buffer, "Filename: %s", heapListPure.Entry[i]->File);
				zERR_MESSAGE(0, 0, Buffer);
				strcpy(fileBuffer, heapListPure.Entry[i]->File);
				PrintOutput((void*)heapListPure.Entry[i]);
			}
			else
				PrintOutput((void*)heapListPure.Entry[i]);
		}
	}
	PrintOutput(NULL);
	if(RuntimeResultBlock>0)
	{
		sprintf(Buffer, "Results: Mem:%d  NumOfBlocks: %d", RuntimeResultMemSize, RuntimeResultBlock);
		zERR_MESSAGE(0, 0, Buffer);
	}
	zERR_MESSAGE(0, 0, "=================================================================");
	return TRUE;
}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
int funcMemSortFile(const void *arg1, const void *arg2)
{
	GESHeapBlock *heapBlock1 = *((GESHeapBlock**)arg1);
	GESHeapBlock *heapBlock2 = *((GESHeapBlock**)arg2);
	if(heapBlock1->File==NULL) return -1;
	if(heapBlock2->File==NULL) return -1;
	if(_strcmpi(heapBlock1->File, heapBlock2->File)>0) return 1;
	if(_strcmpi(heapBlock1->File, heapBlock2->File)<0) return -1;

	if(heapBlock1->Line > heapBlock2->Line) return 1;
	if(heapBlock1->Line < heapBlock2->Line) return -1;

	if(heapBlock1->TimeStamp > heapBlock2->TimeStamp) return 1;
	if(heapBlock1->TimeStamp < heapBlock2->TimeStamp) return -1;
	return 0;
}
zBOOL	zCMallocWin32Debug::MemSortFile()
{
	GESHeapBlock *heapBlock = NULL;
	char fileBuffer[MAX_PATH];
	memset(fileBuffer, 0, sizeof(char)*MAX_PATH);
	ShowzSpyMemHeader("FileSort");
	// first read heaplist into an array
	GETSmallArrayNative<GESHeapBlock*> heapListPure;
	// do heapBlocks it into array
	InsertInSortList((void*)&heapListPure);
	qsort(heapListPure.Entry, heapListPure.Used, sizeof(GESHeapBlock*), funcMemSortFile);
	ShowNoFilename = TRUE;
	ShowNoName = FALSE;
	for(GEU32 i=0;i<heapListPure.Used;i++)
	{
		if(heapListPure.Entry[i]->File!=NULL)
		{
			if(_stricmp(fileBuffer, heapListPure.Entry[i]->File)!=0)
			{
				ResetOutput();
				if(RuntimeResultBlock>0)
				{
					sprintf(Buffer, "Results: Mem:%d   NumOfBlocks: %d", RuntimeResultMemSize, RuntimeResultBlock);
					zERR_MESSAGE(0, 0, Buffer);
				}
				RuntimeResultMemSize = 0;
				RuntimeResultBlock = 0;
				zERR_MESSAGE(0, 0, "-------------------------------------------");
				sprintf(Buffer, "Filename: %s", heapListPure.Entry[i]->File);
				zERR_MESSAGE(0, 0, Buffer);
				strcpy(fileBuffer, heapListPure.Entry[i]->File);
				PrintOutput((void*)heapListPure.Entry[i]);
			}
			else
				PrintOutput((void*)heapListPure.Entry[i]);
		}
	}
	PrintOutput(NULL);
	if(RuntimeResultBlock>0)
	{
		sprintf(Buffer, "Results: Mem:%d  NumOfBlocks: %d", RuntimeResultMemSize, RuntimeResultBlock);
		zERR_MESSAGE(0, 0, Buffer);
	}
	zERR_MESSAGE(0, 0, "=================================================================");
	return TRUE;
}
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
int funcMemSortTime(const void *arg1, const void *arg2)
{
	GESHeapBlock *heapBlock1 = *((GESHeapBlock**)arg1);
	GESHeapBlock *heapBlock2 = *((GESHeapBlock**)arg2);
	if(heapBlock1->TimeStamp > heapBlock2->TimeStamp) return 1;
	if(heapBlock1->TimeStamp < heapBlock2->TimeStamp) return -1;
	
	// only if equal
	if(heapBlock1->File==NULL) return -1;
	if(heapBlock2->File==NULL) return 1;
	if(_strcmpi(heapBlock1->File, heapBlock2->File)>0) return 1;
	if(_strcmpi(heapBlock1->File, heapBlock2->File)<0) return -1;
	if(heapBlock1->Line > heapBlock2->Line) return 1;
	if(heapBlock1->Line < heapBlock2->Line) return -1;
	return 0;
}
zBOOL	zCMallocWin32Debug::MemSortTime()
{
	GESHeapBlock *heapBlock = NULL;
	ShowzSpyMemHeader("TimeSort");
	// first read heaplist into an array
	GETSmallArrayNative<GESHeapBlock*> heapListPure;
	// put heapBlocks into array
	InsertInSortList((void*)&heapListPure);
	qsort(heapListPure.Entry, heapListPure.Used, sizeof(GESHeapBlock*), funcMemSortTime);
	GEU32 timeStamp = 0xffffffff;
	GEU32 memSize = 0;
	ShowNoFilename = FALSE;
	ShowNoName = FALSE;
	for(GEU32 i=0;i<heapListPure.Used;i++)
	{
		if(timeStamp!=heapListPure.Entry[i]->TimeStamp)
		{
			ResetOutput();
			if(RuntimeResultBlock>0)
			{
				sprintf(Buffer, "Results: Mem:%d   NumOfBlocks: %d", RuntimeResultMemSize, RuntimeResultBlock);
				zERR_MESSAGE(0, 0, Buffer);
			}
			RuntimeResultMemSize = 0;
			RuntimeResultBlock = 0;
			zERR_MESSAGE(0, 0, "-------------------------------------------");
			sprintf(Buffer, "TIMESTAMP: %.3f ", GEFloat((heapListPure.Entry[i]->TimeStamp-GEGetAppStartTime())/1000.0f));
			zERR_MESSAGE(0, 0, Buffer);
			timeStamp = heapListPure.Entry[i]->TimeStamp;
			PrintOutput((void*)heapListPure.Entry[i]);
		}
		else
			PrintOutput((void*)heapListPure.Entry[i]);
	}
	PrintOutput(NULL);
	if(RuntimeResultBlock>0)
	{
		sprintf(Buffer, "Results: Mem:%d  NumOfBlocks: %d", RuntimeResultMemSize, RuntimeResultBlock);
		zERR_MESSAGE(0, 0, Buffer);
	}
	zERR_MESSAGE(0, 0, "=================================================================");
	return TRUE;
}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void	zCMallocWin32Debug::ResetOutput()
{
	if(RuntimeBlocks>0)
	{
		if(ShowNoFilename==TRUE)
			sprintf(Buffer, "%s  Mem:%d  Blocks:%d  #%d", RuntimeName, RuntimeMemSize, RuntimeBlocks, RuntimeLine);
		else
		{
			sprintf(Buffer, "%s  Mem:%d  Blocks:%d  F:%s #%d", RuntimeName, RuntimeMemSize, RuntimeBlocks, RuntimeFilename, RuntimeLine);
			if(ShowNoName==TRUE)
				sprintf(Buffer, "Mem:%d  Blocks:%d  F:%s #%d", RuntimeMemSize, RuntimeBlocks, RuntimeFilename, RuntimeLine);
			else
				sprintf(Buffer, "%s  Mem:%d  Blocks:%d  F:%s #%d", RuntimeName, RuntimeMemSize, RuntimeBlocks, RuntimeFilename, RuntimeLine);
		}
		zERR_MESSAGE(0, 0, Buffer);
	}
	RuntimeMemSize = 0;
	RuntimeBlocks = 0;
	RuntimeLine = 0;
	memset(RuntimeFilename, 0, sizeof(char)*400);
	memset(RuntimeName, 0, sizeof(char)*400);
}

void	zCMallocWin32Debug::PrintOutput(void *_heapBlock)
{
	if(_heapBlock==NULL)
	{
		if(ShowNoFilename==TRUE)
			sprintf(Buffer, "%s  Mem:%d  Blocks:%d  #%d", RuntimeName, RuntimeMemSize, RuntimeBlocks, RuntimeLine);
		else
		{
			sprintf(Buffer, "%s  Mem:%d  Blocks:%d  F:%s #%d", RuntimeName, RuntimeMemSize, RuntimeBlocks, RuntimeFilename, RuntimeLine);

			if(ShowNoName==TRUE)
				sprintf(Buffer, "Mem:%d  Blocks:%d  F:%s #%d", RuntimeMemSize, RuntimeBlocks, RuntimeFilename, RuntimeLine);
			else	
				sprintf(Buffer, "%s  Mem:%d  Blocks:%d  F:%s #%d", RuntimeName, RuntimeMemSize, RuntimeBlocks, RuntimeFilename, RuntimeLine);
		}
		zERR_MESSAGE(0, 0, Buffer);
		return;
	}
	GESHeapBlock *heapBlock = (GESHeapBlock*) _heapBlock;
	zBOOL matched = FALSE;
	
	if((strlen(RuntimeFilename)==0)&&(heapBlock->File==NULL))
	{
		if(heapBlock->Line==RuntimeLine) 
			matched = TRUE;
	}
	else
		if(heapBlock->File)
			if(strcmp(heapBlock->File, RuntimeFilename)==0)
				if(heapBlock->Line==RuntimeLine) 
					matched = TRUE;

	if(RuntimeBlocks==0)
		matched = FALSE;
	if(matched==FALSE)
	{
		if(RuntimeBlocks!=0)
		{
			if(ShowNoFilename==TRUE)
				sprintf(Buffer, "%s  Mem:%d  Blocks:%d  #%d", RuntimeName, RuntimeMemSize, RuntimeBlocks, RuntimeLine);
			else
			{
				sprintf(Buffer, "%s  Mem:%d  Blocks:%d  F:%s #%d", RuntimeName, RuntimeMemSize, RuntimeBlocks, RuntimeFilename, RuntimeLine);
				if(ShowNoName==TRUE)
					sprintf(Buffer, "Mem:%d  Blocks:%d  F:%s #%d", RuntimeMemSize, RuntimeBlocks, RuntimeFilename, RuntimeLine);
				else
					sprintf(Buffer, "%s  Mem:%d  Blocks:%d  F:%s #%d", RuntimeName, RuntimeMemSize, RuntimeBlocks, RuntimeFilename, RuntimeLine);
			}
			zERR_MESSAGE(0, 0, Buffer);
		}
		if(heapBlock->File!=NULL)
			strcpy(RuntimeFilename, heapBlock->File);
		else
			RuntimeFilename[0] = 0;
		if(heapBlock->Name!=NULL)
			strcpy(RuntimeName, heapBlock->Name);
		else
			RuntimeName[0] = 0;
		RuntimeBlocks=0;
		RuntimeMemSize = 0;
		RuntimeLine = heapBlock->Line;
	}
	RuntimeMemSize += heapBlock->Size;
	RuntimeBlocks++;
	RuntimeResultMemSize += heapBlock->Size;
	RuntimeResultBlock++;
}

zBOOL	zCMallocWin32Debug::DumpHeap (zTMallocDumpHeapMode dumpHeapMode)
{
	zERR_MESSAGE(6, 0, "zCMallocWin32Debug::DumpHeap - memory dumped:");
	switch(dumpHeapMode)
	{
		case zMALLOC_SORT_BY_BYTES_PER_LINE:
			//MemSortBlockSize();
			GEShowHeapDialog();
			break;
		case zMALLOC_SORT_BY_BLOCKS_PER_LINE:
			//MemSortBlockSize();
			GEShowHeapDialog();
			break;
		case zMALLOC_SORT_BY_CLASS:
			MemSortClass();
			break;
		case zMALLOC_SORT_BY_BLOCK_SIZE:
			MemSortBlockSize();
			break;
		case zMALLOC_SORT_BY_FILE:
			MemSortFile();
			break;
		case zMALLOC_SORT_BY_TIME:
			MemSortTime();
			break;
	};
	return TRUE;
}

zBOOL	zCMallocWin32Debug::CheckHeap ()
{
	GESHeapBlock *heapBlock = NULL;
	GEChar charBuffer[550];
	while(GEGetHeapBlock(&heapBlock))
	{
		// trivial check
		if(heapBlock)
		{
			
			GEECheckPtr_Error checkError = GECheckMemPtr(GELPVoid(heapBlock->Ptr));
			switch (checkError)
			{
				case GEECheckPtr_OK:
					continue;
				case GEECheckPtr_InvalidPtr:
					{
						if(heapBlock->Name)
						{
							sprintf(charBuffer, "zCMallocWin32Debug::CheckHeap - GECheckMemPtr has an invalid ptr detected. Name:%s  File:%s #%d", heapBlock->Name, heapBlock->File, heapBlock->Line);
							zERR_FAULT(charBuffer);
						}
						else
						{
							zERR_FAULT("zCMallocWin32Debug::CheckHeap - illegal(invalid) memory pointer detected. (no information available)");
						}
					}
					continue;
				case GEECheckPtr_CorruptedArea:
					{
						if(heapBlock->Name)
						{
							sprintf(charBuffer, "zCMallocWin32Debug::CheckHeap - GECheckMemPtr has an invalid memoryarea detected. Name:%s  File:%s #%d ", heapBlock->Name, heapBlock->File, heapBlock->Line);
							zERR_FAULT(charBuffer);
						}
						else
						{
							zERR_FAULT("zCMallocWin32Debug::CheckHeap - illegal(invalid) memory area detected. (no information available)");
						}
					}
					continue;
			};

		}
	}

	zERR_MESSAGE(3, 0, "zCMallocWin32Debug::CheckHeap - checking heap for consistency: all ok");
	return TRUE;
}

zTMallocCheckPtrError	zCMallocWin32Debug::CheckPtr(void* ptr)
{
	switch (GECheckMemPtr(GELPVoid(ptr)))
	{
	case GEECheckPtr_OK:
		return zMALLOC_CHECK_PTR_OK;
	case GEECheckPtr_InvalidPtr:
		return zMALLOC_CHECK_PTR_INVALID_PTR;
	case GEECheckPtr_CorruptedArea:
		return zMALLOC_CHECK_PTR_CORRUPTED_MEM;
	case GEECheckPtr_NotActivated:
		return zMALLOC_CHECK_PTR_NOT_ACTIVATED;
	case GEECheckPtr_NullPtr:
		return zMALLOC_CHECK_PTR_NULL_PTR;
	default:
		return zMALLOC_CHECK_PTR_INVALID_PTR;
	};
}


void zCMallocWin32Debug::CheckRestOfHeap()
{
	GESHeapBlock *heapBlock = NULL;
//	GEChar charBuffer[550];
	int blocksNotUsed = 0;
	int memoryNotUsed = 0;
	char outBuffer[600];
	while(GEGetHeapBlock(&heapBlock))
	{
		// trivial check
		if(heapBlock)
		{
			if(heapBlock->File)
			{
				GEECheckPtr_Error checkError = GECheckMemPtr(GELPVoid(heapBlock->Ptr));
				if(checkError==GEECheckPtr_OK)
				{
					if(heapBlock->Size>=4)
					{
						GEInt i = 0;
						GEU32* ptrCheck = (GEU32*) heapBlock->Ptr;
						do
						{
							// -TODO-: how many deadfeeds should be allowed ?
							if(ptrCheck[i]==0xdeadfeed)
							{
								sprintf(outBuffer, "OH: zCMallocWin32Debug::CheckHeap - heapBlock is not used. File:%s %d", heapBlock->File, heapBlock->Line);
								zERR_MESSAGE(3, 0, outBuffer);
								blocksNotUsed++;
								memoryNotUsed += heapBlock->Size;
								break;
							}
						}
						while(i<(heapBlock->Size/4));
					}
				}

			}
			else
			{
				zERR_FAULT("OH: zCMallocWin32Debug::CheckRestOfHeap - check of pointer consistency was failed. Please do a checkHeap");
			}
		}

	}
	zERR_MESSAGE(3, 0, "OH: zCMallocWin32Debug::CheckHeap --------------------------------------------");
	sprintf(outBuffer, "OH: zCMallocWin32Debug::CheckHeap - Blocks unused: %d  Memory unused: %d", blocksNotUsed, memoryNotUsed);
	zERR_MESSAGE(3, 0, outBuffer);
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
// initialization of heapprofiler
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
class zCInitFirst
{
public:
	zCInitFirst()
	{
		// initialize sysmanager (major/minor/build not neccessary here)
		zSTRING str(GetCommandLine());
		str.Lower();
		if(str.Search("-zmemprofiler")!=-1)
			GEInit(GETrue, 0, 0, 0);
		else
			GEInit(GEFalse, 0, 0, 0);

		// set current time for startstamp
		GESetStartTime();
		// zSpy not activated
		// zERR_MESSAGE(2, 0, "zCMallocWin32Debug::Init - Sysmanager#heapprofiler activated.")	
	}
	~zCInitFirst()
	{
		// no output available here
		//MemSortBlockSize();
		GEFinit();
		// zSpy not activated
		// zERR_MESSAGE(2, 0, "zCMallocWin32Debug::Shutdown - Sysmanager#heapprofiler deactivated.")	
	}
};

// disable compiler reserved warning
#pragma warning(disable: 4074)
// do an init first
#pragma init_seg(compiler)
zCInitFirst	InitFirst;

