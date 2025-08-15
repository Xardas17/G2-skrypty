/******************************************************************************** 
 
     $Workfile:: zMemory.cpp          $                $Date:: 6.12.00 23:07    $
     $Revision:: 12                   $             $Modtime:: 6.12.00 19:21    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ memory management wrapper
   created       : 11.7.2000

 * $Log: /current_work/zengin_work/_Dieter/zMemory.cpp $
 * 
 * 12    6.12.00 23:07 Hildebrandt
 * 
 * 11    2.11.00 17:48 Hildebrandt
 * 
 * 10    2.09.00 1:41 Hildebrandt
 * 
 * 9     29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 8     21.08.00 17:18 Hildebrandt
 * 
 * 7     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 2     9.08.00 17:12 Admin
 * 
 * 6     21.07.00 14:06 Hildebrandt
 * 
 * 5     19.07.00 16:45 Hildebrandt
 * 
 * 4     19.07.00 15:56 Hildebrandt
 * 
 * 3     18.07.00 18:12 Hildebrandt
 * 
 * 2     18.07.00 17:01 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 12 $ ($Modtime: 6.12.00 19:21 $)

#include <zMemory.h>
#include <malloc.h>

// ===============================================================================================================

// FIXME: dieses COMPILING_SPACER ist hier TMP, bis die korrekte Loesung kommt...
#ifdef COMPILING_SPACER
	zCMallocGeneric			zmalloc;
#else
	#ifdef ZMEMORY_USE_ZMALLOC
		zCMallocWin32Debug	zmalloc;
	#else
		zCMallocGeneric		zmalloc;
	#endif
#endif

// ===============================================================================================================

#ifdef ZMEMORY_USE_ZMALLOC  
	void* operator new	(unsigned int size) {	
		return zmalloc.Malloc (size);
	};
	void  operator delete(void *ptr) {	
		zmalloc.Free(ptr);							 
	};
	void* operator new	(unsigned int size, const char *className, const char *file, int line)	{	
		return zmalloc.Malloc(size, className, file, line);	
	};
	void operator delete (void *ptr, const char *className, const char *file, int line) {
		zmalloc.Free(ptr);							
	};
	void* operator new[] (unsigned int size) {	
		return zmalloc.Malloc (size);
	}; 
	void  operator delete[] (void *ptr) {	
		zmalloc.Free(ptr);							 
	};
	void* operator new[] (unsigned int size, const char *className, const char *file, int line)	{	
		return zmalloc.Malloc(size, className, file, line);	
	};
	void operator delete[] (void *ptr, const char *className, const char *file, int line) {
		zmalloc.Free(ptr);							
	};
#else
	void* operator new	(unsigned int size) {	
		return malloc(size);
	};
	void  operator delete(void *ptr) {	
		free(ptr);
	};
	void* operator new[] (unsigned int size) {	
		return malloc(size);		
	}; 
	void  operator delete[] (void *ptr) {	
		free(ptr);
	};
	void* operator new	(unsigned int size, const char *className, const char *file, int line)	{	
		return malloc(size);
//		return ::operator new (size);				
	};
	void operator delete (void *ptr, const char *className, const char *file, int line) {
		free(ptr);
//		::operator delete ptr;
	};
	void* operator new[] (unsigned int size, const char *className, const char *file, int line)	{	
		return malloc(size);
//		return ::operator new (size);				
	};
	void operator delete[] (void *ptr, const char *className, const char *file, int line) {
		free(ptr);
//		::operator delete ptr;
	};
#endif

// ===============================================================================================================

/*
Infos
  - Mem Bedarf jetzt
  - Mem Bedarf Peak
  - lastFrame:	
	- num Malloc/Free
	- num Bytes Malloc/Free
  - Uebersicht (sorted), auf Spy:
	- alle HeapBloecke
	- alle Source Zeilen (sort: 1) Summe, 2) Location)
	- Chronologie


	zCVob *vob = new zCVob;
	zCVob *vob = zNEW(zCVob);

	zNEW(vob, zCVob);
	zCVob *vob;
	zNEW_ASSIGN(vob, zCVob, "vertex");

	95200 bytes, 20 blocks, 476 bpb, zCVob, zWorld.cpp (#1387)


	SORT_BY_BYTES_PER_LINE,
	SORT_BY_BLOCKS_PER_LINE,
	SORT_BY_BLOCK_SIZE,
	SORT_BY_CLASS,
	SORT_BY_FILE,

	zmem realtime

*/
