/******************************************************************************** 
 
     $Workfile:: zThread.h     $                $Date:: 4.12.00 17:18    $
     $Revision:: 15                   $             $Modtime:: 4.12.00 16:39    $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Thread base class and wrapper
   Created    :  24.3.2000

 * $Log: /current_work/zengin_work/_Dieter/zThread.h $
 * 
 * 15    4.12.00 17:18 Hildebrandt
 * 
 * 14    28.09.00 20:17 Pelzer
 * 
 * 13    28.09.00 20:14 Pelzer
 * 
 * 12    28.09.00 20:13 Pelzer
 * 
 * 11    28.09.00 20:04 Pelzer
 * 
 * 10    28.09.00 20:02 Pelzer
 * 
 * 9     28.09.00 18:50 Pelzer
 * 
 * 8     8.09.00 20:26 Hildebrandt
 * 
 * 7     8.09.00 20:00 Hildebrandt
 * 
 * 6     29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 1     24.03.00 23:09 Hildebrandt
  *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 15 $ ($Modtime: 4.12.00 16:39 $)


#ifndef __ZTHREAD_H__
#define __ZTHREAD_H__

#include <windows.h>

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

// ===============================================================================================================

class zCThread {
public:
	enum zTThread_Prio		{	zTHREAD_PRIORITY_TIME_CRITICAL	= THREAD_PRIORITY_TIME_CRITICAL,
								zTHREAD_PRIORITY_HIGHEST		= THREAD_PRIORITY_HIGHEST,
								zTHREAD_PRIORITY_ABOVE_NORMAL	= THREAD_PRIORITY_ABOVE_NORMAL,
								zTHREAD_PRIORITY_NORMAL			= THREAD_PRIORITY_NORMAL,
								zTHREAD_PRIORITY_BELOW_NORMAL	= THREAD_PRIORITY_BELOW_NORMAL,
								zTHREAD_PRIORITY_LOWEST			= THREAD_PRIORITY_LOWEST,
								zTHREAD_PRIORITY_IDLE			= THREAD_PRIORITY_IDLE
							};

	zCThread();
	virtual ~zCThread();
	
	virtual void	BeginThread				();
	virtual void	EndThread				();
	virtual zBOOL	IsThreadRunning			() { return isThreadRunning; };

	zTThread_Prio	GetThreadPrio			() { return (zTThread_Prio)GetThreadPriority(threadHandle); }; // [PELZER]: Neu/wieder eingefügt
	BOOL			SetThreadPrio			(zTThread_Prio nPriority) { return SetThreadPriority( threadHandle, (int)nPriority ); }; // [PELZER]: Neu/wieder eingefügt

	virtual zBOOL	SuspendThread			();
	virtual zBOOL	ResumeThread			();
	zDWORD			IsSuspended				() { return suspendCount; };	// values greater 0 indicate supsended mode
	void			SleepThread				(zDWORD msec);	// 0 = give up timeslice

	virtual zBOOL	GetTerminationRequested	() const		{ return terminationRequested;	};
	virtual void	SetTerminationRequested	(const zBOOL b) { terminationRequested=b;		};

	// zCThread Interface
	virtual zDWORD	ThreadProc				();				// this is the thread's mainproc

private:
	HANDLE			threadHandle;
//	zDWORD			threadID;
	unsigned int	threadID;
	int				suspendCount;
	zBOOL			isThreadRunning;
	zBOOL			terminationRequested;
};

extern zDWORD WINAPI zThreadProc (zCThread *pthis);

// ===============================================================================================================

// synchronization objects 

// base class for all synchronization objects 
class zCSyncObject {
public:
	virtual ~zCSyncObject() {};
	enum { 
		zTIME_OUT_INFINITE = INFINITE			// "INFINITE" is a WIN32 constant..
	};
	virtual zBOOL		Lock					(zDWORD timeOutMSec=zTIME_OUT_INFINITE)=0;
	virtual zBOOL		Unlock					()=0;
};

class zCCriticalSection : public zCSyncObject {
public:
	zCCriticalSection();
	virtual ~zCCriticalSection();
	virtual zBOOL		Lock					(zDWORD timeOutMSec=zTIME_OUT_INFINITE);	// "timeOutMSec" is ignored, call is always blocking
	virtual zBOOL		Unlock					();

private:
	CRITICAL_SECTION	criticalSection;
};

class zCMutex : public zCSyncObject {
public:
	zCMutex();
	virtual ~zCMutex();
	virtual zBOOL		Lock					(zDWORD timeOutMSec=zTIME_OUT_INFINITE);
	virtual zBOOL		Unlock					();

private:
	HANDLE				mutex;
};

// ===============================================================================================================


#endif