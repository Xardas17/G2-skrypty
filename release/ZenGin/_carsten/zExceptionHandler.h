/****************************************************************
*
* Exception Handler
* File          : zExceptionHandler.h 
* Projekt       : Phoenix
* Autor         : Carsten Edenfeld
* Version       : 
* last modified : 
* erstellt      : 
* Compiler OK   :
*
*****************************************************************
- known bugs:
*****************************************************************
- possible optimizations:
*****************************************************************
- missing features:
*****************************************************************
- comments:  
****************************************************************/


#ifndef __ZEXCEPTIONHANDLER_H__
#define __ZEXCEPTIONHANDLER_H__

#ifndef __ZERROR_H__
#include "zerror.h"
#endif

#ifndef __ZCONTAINER_H__
#include "zContainer.h"
#endif


class zSTRING;

const int MAX_CALLSTACK_DEPTH = 200;

typedef struct
{
	PEXCEPTION_POINTERS		exPtrs;
	char*					faultReason;
	char*					callStack[MAX_CALLSTACK_DEPTH];
	int						csDepth;
} EXCEPTION_INFO, *LPEXCEPTION_INFO;
	

const int MAX_ERRDESCR_LINES = 20;

typedef struct 
{
	char*	errDescr[MAX_ERRDESCR_LINES];
	int		numErr;
} EXCEPTION_DESCR, *LPEXCEPTION_DESCR;;

// exception callback type

typedef void (*EXCB_Info)	 (LPEXCEPTION_DESCR pExceptionDescr);
typedef void (*EXCB_Release) ();

class zCExceptionHandler
{
public:

	zCExceptionHandler();
	~zCExceptionHandler();
	
	static void		   SetLogFileName			( PTSTR pszLogFileName );

	static void		   SetIsActive				( const zBOOL en	   );
	static zBOOL	   GetIsActive				();
	static void		   WalkReleaseCallbacks		();

	static  LONG WINAPI AssertExceptionFilter			( PEXCEPTION_POINTERS pExceptionInfo,ASSERT_FAIL_INFO* afInfo,EXCEPTION_INFO* exInfo);
	static  LONG WINAPI BoundsExceptionFilter			( PEXCEPTION_POINTERS pExceptionInfo,ASSERT_FAIL_INFO* bfInfo,EXCEPTION_INFO* exInfo);

	static  void		AddUnhandledExceptionInfoCallback   ( EXCB_Info callBack ); 
	static  void		RemoveUnhandledExceptionInfoCallback( EXCB_Info callBack );

	static  void		AddUnhandledExceptionReleaseCallback   ( EXCB_Release callBack ); 
	static  void		RemoveUnhandledExceptionReleaseCallback( EXCB_Release callBack );

private:

	static zCArray<EXCB_Info>				ExceptionInfoCallbackList;
	static zCArray<EXCB_Release>			ExceptionReleaseCallbackList;

	static zBOOL							isActive;
	static TCHAR							m_szLogFileName[MAX_PATH];
	static HANDLE							m_hReportFile;
	static LPTOP_LEVEL_EXCEPTION_FILTER		m_previousFilter;

	static void			RecordModuleList		(HANDLE LogFile);
	// entry point where control comes on an unhandled exception
	static LONG WINAPI  UnhandledExceptionFilter( PEXCEPTION_POINTERS pExceptionInfo);
};

extern zCExceptionHandler zexhnd;	//  global instance of class

#endif
