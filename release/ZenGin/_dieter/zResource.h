/******************************************************************************** 
 
     $Workfile:: zResource.h          $                $Date:: 17.03.01 2:10    $
     $Revision:: 11                   $             $Modtime:: 17.03.01 0:13    $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ abstract class for resources
   created       : 31.3.99

 * $Log: /current_work/ZenGin/_Dieter/zResource.h $
 * 
 * 11    17.03.01 2:10 Hildebrandt
 * 
 * 10    4.12.00 17:46 Hildebrandt
 * 
 * 9     4.12.00 17:46 Hildebrandt
 * 
 * 8     14.08.00 21:56 Pelzer
 * 
 * 7     17.07.00 18:52 Hildebrandt
 * 
 * 6     11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 5     8.05.00 5:29 Hildebrandt
 * zenGin 089g
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 3     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 1     10.01.00 15:14 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 11 $ ($Modtime: 17.03.01 0:13 $)

// ===============================================================================================================

#ifndef __ZRESOURCE_H__
#define __ZRESOURCE_H__

#ifndef __ZOBJECT_H__
#include <zObject.h>
#endif

#ifndef __ZTHREAD_H__
#include <zThread.h>
#endif

// forward declarations
class zCResource;
class zCResourceManager;

// ===============================================================================================================

// CacheIn priority:
// - ranges: [0;1] and -1
// - "-1" indicates instant cacheIn, the process blocks until the resource is in memory
// - 0.5 is the default/normal cacheIn priority, use higher or lower values if needed

enum zTResourceCacheState {
	zRES_FAILURE	=-1,
	zRES_CACHED_OUT	= 0,
	zRES_QUEUED		= 1,
	zRES_LOADING	= 2,
	zRES_CACHED_IN	= 3
};

class zENGINE_API zCResourceManager : public zCThread {
public:
	zCResourceManager();
	virtual ~zCResourceManager();

	//
	void					DoFrameActivity		();
	void					PurgeCaches			(zCClassDef *resClassDef=0);	// specify the resource-type to purge, "0" purges all caches
	void					SetThreadingEnabled	(const zBOOL b);
	zBOOL					GetThreadingEnabled	() const;
	void					SetCacheInImmediately(const zREAL timeMsec)	{ cacheInImmediatelyMsec=timeMsec;	};// is active for the active rendering frame and caches in all resources immediately, regardless of specified prios
	zBOOL					GetCacheInImmediately() const				{ return cacheInImmediatelyMsec>0;	};
	void					SetShowDebugInfo	(const zBOOL b)			{ showDebugInfo = b;				};
	zBOOL					GetShowDebugInfo	() const				{ return showDebugInfo;				};

protected:
	zTResourceCacheState	CacheIn				(zCResource *res, zREAL priority);		// resource is ordered to cache itself in, this can take some time, current state of res is returned, if instantly neede, prio "-1", values: [0;1], -1
	void					CacheOut			(zCResource *res);						// resource is ordered to cache itself out, after execution the res is guaranteed to be cachedOut (no delay)
	void					TouchTimeStamp		(zCResource *res);
	int						GetClassCacheIndex	(zCClassDef *resClassDef);
	void					Evict				();										// scan cachedIn resources for candidates and evict them (done 1 per frame)
	void					LoadResource		(zCResource *res);
	void					PrintStatusDebug	();
	zDWORD					GetCurrentTimeStamp	() const { return currentTimeStamp; };

	//
	void					QueueProcess_Start	();
	void					QueueProcess_Suspend();
	void					QueueProcess_Resume	();

	// zCThread interface
	virtual zDWORD			ThreadProc			();		// this is the thread's mainproc

private:
	
	class zCClassCache {
	public:
		zCClassCache();
		~zCClassCache();
		zCClassDef			*resClassDef;
		zCResource			*resListHead;		// this list is sorted on the resources timeStamp
		zCResource			*resListTail;
		zDWORD				numRes;
		int					cacheSizeBytes;
		int					cacheSizeMaxBytes;
		zDWORD				cacheOutTimeMSec;

		void				InsertRes			(zCResource *res);		// inserts at head of list
		void				RemoveRes			(zCResource *res);
		void				TouchRes			(zCResource *res);
	};
	zCArray<zCClassCache>	classCacheList;
	zCResource				*cacheInQueueHead;
	zCResource				*cacheInQueueTail;
	zDWORD					currentTimeStamp;
	zBOOL					threadingEnabled;
	zCCriticalSection		cacheInQueueGuard;
	int						numQueued;
	int						numResCachedInThisFrame;	// counts number of resources cachedIn this frame
	zBOOL					showDebugInfo;
	zREAL					cacheInImmediatelyMsec;
	// [BENDLIN] 2002-05-17, avoid compiler optimizations on reading/writing, multithreaded access
	volatile zBOOL			goToSuspend;

	void					InitClassCache		();
	zCClassCache*			GetClassCache		(zCResource *res);
	zCResource*				RemoveCacheInQueue	(zCResource *res);
	zCResource*				GetNextCacheInQueue ();
	void					InsertCacheInQueue	(zCResource* resz, zREAL priority);
	void					LockCacheInQueue	();
	void					UnlockCacheInQueue	();
	zBOOL					WaitForCacheIn		(zCResource *res);		// waits until a queued or loading resource is cachedIn

	friend class zCResource;
};								

extern zCResourceManager *zresMan;

// ===============================================================================================================

class zENGINE_API zCResource : public zCObject {
	zCLASS_DECLARATION (zCResource)
public:
	zCResource();
	virtual ~zCResource();

	//
	inline zTResourceCacheState	CacheIn				(zREAL priority=0.5F);		// use prio '-1' if instantly needed
	void						CacheOut			();
	inline zTResourceCacheState	GetCacheState		() const				{ return zTResourceCacheState (cacheState); };
	inline void					SetCacheOutLock		(const zBOOL locked)	{ cacheOutLock	= locked;	};
	inline zBOOL				GetCacheOutLock		() const				{ return cacheOutLock;		};
	inline zBOOL				GetCanBeCachedOut	() const				{ return canBeCachedOut;	};
	inline void					SetCanBeCachedOut   (const zBOOL a_bCanBeCachedOut)	{ canBeCachedOut = a_bCanBeCachedOut;		};
	inline zDWORD				GetTimeStamp		() const				{ return timeStamp; };
	void						SetCacheInPriority	(const zREAL prio);					// range [0;1]
	inline zDWORD				GetCacheInPriority	() const				{ return cacheInPriority; };
	// virtual interface
	// Only override this methods if the derived class needs is a real resource and 
	// needs the zCResource/zCResourceManager services. zCClassDef zCLASS_FLAG_RESOURCE should be set for these classes.
	virtual zBOOL				LoadResourceData	();
	virtual zBOOL				ReleaseResourceData	();
	virtual zDWORD				GetResSizeBytes		();		// size of cachedIn resource, doesn't need to be exact but should calculate fast, for zCResourceManager cacheLimit calculations
								
	// "virtual statics"		
	virtual void				GetCacheConfig		(zDWORD &cacheOutTimeMSec, zDWORD &cacheSizeMaxBytes);

	void						LockStateChange		(); // Lock des Resource-Status[PELZER]
	void						UnlockStateChange	(); // Unlock des Resource-Status[PELZER]
								
protected:						
	void						SetCacheState		(const zTResourceCacheState state) { cacheState = state; };
								
private:						
	zCResource					*nextRes;
	zCResource					*prevRes;
	zDWORD						timeStamp;						// last time the resource was used/touched
	zCCriticalSection			stateChangeGuard;				// Critical Section zwecks syncronisierter Änderungen am Resource-Status[PELZER]
	struct {					
		zUINT8					cacheState		: 2;			// zTResourceCacheState
		zUINT8					cacheOutLock	: 1;
		zUINT8					cacheClassIndex	: 8;
		zUINT8					managedByResMan	: 1;			// this bit indicates if the resource was cachedIn by the resMan and is therefor managed by it
		zUINT16					cacheInPriority	: 16;			// (FIXME: 8 would suffice..)
		zUINT8					canBeCachedOut	: 1;
	};
	enum { zMAX_CACHE_IN_PRIO	= 65535 };

	void						TouchTimeStamp		();			// refreshes timeStamp if resource is currently cached in, calls resMan to update accordingly
	void						TouchTimeStampLocal	();			// same as TouchTimeStamp(), but does not call resMan for updates
	
	friend class zCResourceManager;
	friend class zCResourceManager::zCClassCache;
};								

// zCResource inlines..

inline zTResourceCacheState zCResource::CacheIn (zREAL priority)
{
	if (GetCacheState()==zRES_CACHED_IN)
	{
		TouchTimeStamp		();					// make this inline, too ?
	} else 
	{
		TouchTimeStampLocal	();
		zresMan->CacheIn	(this, priority);
	};
	return GetCacheState();
};

// ===============================================================================================================

#endif