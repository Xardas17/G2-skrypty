/******************************************************************************** 
 
     $Workfile:: zThread.cpp          $                $Date:: 31.08.00 17:04   $
     $Revision:: 11                   $             $Modtime:: 29.08.00 19:05   $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Thread base class implementation
   Created    :  24.3.2000

 * $Log: /current_work/zengin_work/_Dieter/zThread.cpp $
 * 
 * 11    31.08.00 17:04 Hildebrandt
 * 
 * 10    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 9     21.07.00 14:28 Hildebrandt
 * 
 * 8     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 1     24.03.00 23:12 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 11 $ ($Modtime: 29.08.00 19:05 $)

// CRT
#include <process.h>

// engine
#include <zCore.h>
#include <zThread.h>


///////////////////////////////////////////////////////////////////////////
//    zCThread
///////////////////////////////////////////////////////////////////////////

zDWORD WINAPI zThreadProc (zCThread *pthis)
{
	return pthis->ThreadProc();
}

zCThread::zCThread()
{
	threadID			= 0;
	threadHandle		= NULL;
	isThreadRunning		= FALSE;
	terminationRequested= FALSE;
	suspendCount		= 0;
}

zCThread::~zCThread()
{
	EndThread();
}

void zCThread::BeginThread()
{
#if defined( _WIN32 ) && defined( _MT )
	if (threadHandle) {
		EndThread ();  // just to be safe.
	};
	
	// Start the thread.
/*	threadHandle = CreateThread(	NULL,
									0,
									(LPTHREAD_START_ROUTINE)zThreadProc,
									this,
									0,
									(LPDWORD)&threadID 
								);
*/
/*	HANDLE CreateThread(
	  LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
	  DWORD dwStackSize,                         // initial thread stack size
	  LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
	  LPVOID lpParameter,                        // argument for new thread
	  DWORD dwCreationFlags,                     // creation flags
	  LPDWORD lpThreadId                         // pointer to receive thread ID);
	  */
//	unsigned int threadID;
	threadHandle = (HANDLE)_beginthreadex(	NULL,								// pointer to security attributes
											0,									// initial thread stack size
											(unsigned (__stdcall *)(void *))zThreadProc,// pointer to thread function
											this,								// argument for new thread
											0,									// creation flags
											&threadID							// pointer to receive thread ID
										);

	if ((threadHandle==NULL) || (threadHandle<=0))
	{
		// Arrooga! Dive, dive!  And deal with the error, too!
		zERR_FATAL ("D: Could not create Thread!");
	}
	isThreadRunning = TRUE;
//::SetThreadPriority (threadHandle, 10);
//::SetThreadPriority (threadHandle, 15);
#endif
}

zDWORD zCThread::ThreadProc()
{
	// _endthreadex wird autom. beim Verlassen der Thread-Proc aufgerufen
	return 0;
}

void zCThread::EndThread()
{
#if defined( _WIN32 ) && defined( _MT )
	if (threadHandle!=NULL)
	{
		terminationRequested= TRUE;	// muss VOR dem ResumeThread, damit der Thread sich nicht gleich evtl. wieder schlafenlegt..
		ResumeThread		();
		WaitForSingleObject	(threadHandle, INFINITE);
		CloseHandle			(threadHandle);				// bei 'CreateThread' und '_beginthreadex' noetig!
		threadHandle		= NULL;
		threadID			= 0;
		isThreadRunning		= FALSE;
		terminationRequested= FALSE;
	}
#endif
}

zBOOL zCThread::SuspendThread ()
{
	if (suspendCount>0) return FALSE;
	suspendCount++;
	return (::SuspendThread (threadHandle)!=0xFFFFFFFF);
};

zBOOL zCThread::ResumeThread ()
{
	if (suspendCount<=0) return FALSE;
	suspendCount--;
	return (::ResumeThread (threadHandle)!=0xFFFFFFFF);
};

void zCThread::SleepThread (zDWORD msec)
{
	Sleep(msec);
};

///////////////////////////////////////////////////////////////////////////
//    zCCriticalSection
///////////////////////////////////////////////////////////////////////////


zCCriticalSection::zCCriticalSection() {
	InitializeCriticalSection (&criticalSection);
};

zCCriticalSection::~zCCriticalSection() {
	DeleteCriticalSection	(&criticalSection);
};

zBOOL zCCriticalSection::Lock (zDWORD timeOutMSec)
{
	EnterCriticalSection	(&criticalSection);
	return TRUE;
	// "TryEnterCriticalSection" ist leider erst in Win95/98 leider noch nicht supported...
	//	return TryEnterCriticalSection	(&criticalSection);
};

zBOOL zCCriticalSection::Unlock ()
{
	LeaveCriticalSection	(&criticalSection);
	return TRUE;
};


///////////////////////////////////////////////////////////////////////////
//    zCMutex
///////////////////////////////////////////////////////////////////////////


zCMutex::zCMutex() {
#if defined( _WIN32 ) && defined( _MT )
	mutex = CreateMutex( NULL, FALSE, NULL );
	if (mutex==NULL)
		zERR_FATAL ("D: ");
#endif
};

zCMutex::~zCMutex() {
#if defined( _WIN32 ) && defined( _MT )
	if (mutex!=NULL)
	{
		CloseHandle (mutex);
		mutex = NULL;
	}
#endif
};

zBOOL zCMutex::Lock (zDWORD timeOutMSec)
{
#if defined( _WIN32 ) && defined( _MT )
	WaitForSingleObject (mutex, timeOutMSec ); 
#endif
	return TRUE;
};

zBOOL zCMutex::Unlock ()
{
#if defined( _WIN32 ) && defined( _MT )
	ReleaseMutex (mutex);
#endif
	return TRUE;
};

// =====================================================================================================================

/*

// synchronization objects 
class zCSyncObject
	class zCCriticalSection
	class zCMutex
	class zCSemaphore
// synchronization access objects 
class zCSingleLock


THREAD_PRIORITY_LOWEST			Two levels below process   
THREAD_PRIORITY_BELOW_NORMAL	One level below process   
THREAD_PRIORITY_NORMAL			Same level as process   
THREAD_PRIORITY_ABOVE_NORMAL	One level above process   
THREAD_PRIORITY_HIGHEST			Two levels above process   
THREAD_PRIORITY_TIME_CRITICAL   Fifteen (in normal user processes)   
THREAD_PRIORITY_IDLE			One (in normal user processes)   

*/