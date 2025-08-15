//==========================================
// Origin: Microsoft Systems Journal, April 1997
// FILE: zExceptionHandler.CPP

/*
  Folgende Massnahmen sind nötig, um das Ding zum laufen zu kriegen:
  - bugslayerutil.lib mit einbinden
  - zRes.rc			  mit einbinden
  - bugslayerutil.dll, msdbi.dll und imagehl2.dll mit ins exe Verzeichnis kopieren
  - Projekt mit Debug Informationen compilieren (auch im Release Build)
  - inkrementelles Linken deaktivieren
  - Keine Programmdatenbank verwenden (Symbole müssen im Exe vorhanden sein)
	!Etwas verwirrend: Projekt Einstellungen/C++/Allgemein/Debug-Info muss auf Programmdatenbank stehen,
	 und Projekt Einstellungen/Linker/Anpassen/Programmdatenbank deaktiviert sein 
  - die mitgelieferten include dateien basetsd.h, wincrpyt.h, imagehlp.h und wintrust.h in ein Verzeichnis kopieren,
    und die Projekteinstellungen so ändern, daß diese VOR den standard include Dateien (vom Developer Studio)
	geladen werden.
*/
//==========================================

#include "zcore.h"
#include <windows.h>
#include "zExHnd_Bugslayer.h"
#include <tchar.h>
#include "zExceptionHandler.h"
#include <wincrypt.h>
#include "zCPUSpecs.h"
#include "zWin32.h"
#include "zWin32_Internal.h"
#include "zWin32_Resource.h"
#include "direct.h"


//============================== Global Variables =============================

//
// Declare the static variables of the zCExceptionHandler class
//
TCHAR							zCExceptionHandler	::	m_szLogFileName[MAX_PATH];
LPTOP_LEVEL_EXCEPTION_FILTER	zCExceptionHandler	::	m_previousFilter;
HANDLE							zCExceptionHandler	::	m_hReportFile;
zBOOL							zCExceptionHandler	::	isActive					= FALSE;
zCArray<EXCB_Info>				zCExceptionHandler	::	ExceptionInfoCallbackList;
zCArray<EXCB_Release>			zCExceptionHandler	::	ExceptionReleaseCallbackList;

zCExceptionHandler g_zCExceptionHandler;  // Declare global instance of class


// Print the specified FILETIME to output in a human readable format,
// without using the C run time.

static void PrintTime(char *output, FILETIME TimeToPrint)
{
	WORD Date, Time;
	if (FileTimeToLocalFileTime(&TimeToPrint, &TimeToPrint) &&
				FileTimeToDosDateTime(&TimeToPrint, &Date, &Time))
	{
		// What a silly way to print out the file date/time. Oh well,
		// it works, and I'm not aware of a cleaner way to do it.
		wsprintf(output, "%d/%d/%d %02d:%02d:%02d",
					(Date / 32) & 15, Date & 31, (Date / 512) + 1980,
					(Time / 2048), (Time / 32) & 63, (Time & 31) * 2);
	}
	else
		output[0] = 0;
}
// Print information about a code module (DLL or EXE) such as its size,
// location, time stamp, etc.

static void hprintf(HANDLE LogFile, char* Format, ...)
{
	char buffer[2000];	// wvsprintf never prints more than one K.

	va_list arglist;
	va_start( arglist, Format);
	wvsprintf(buffer, Format, arglist);
	va_end( arglist);

	DWORD NumBytes;
	WriteFile(LogFile, buffer, lstrlen(buffer), &NumBytes, 0);
}

static void ShowModuleInfo(HANDLE LogFile, HINSTANCE ModuleHandle)
{
	char ModName[MAX_PATH];
	__try
	{
		if (GetModuleFileName(ModuleHandle, ModName, sizeof(ModName)) > 0)
		{
			// If GetModuleFileName returns greater than zero then this must
			// be a valid code module address. Therefore we can try to walk
			// our way through its structures to find the link time stamp.
			IMAGE_DOS_HEADER *DosHeader = (IMAGE_DOS_HEADER*)ModuleHandle;
		    if (IMAGE_DOS_SIGNATURE != DosHeader->e_magic)
	    	    return;
			IMAGE_NT_HEADERS *NTHeader = (IMAGE_NT_HEADERS*)((char *)DosHeader
						+ DosHeader->e_lfanew);
		    if (IMAGE_NT_SIGNATURE != NTHeader->Signature)
	    	    return;
			// Open the code module file so that we can get its file date
			// and size.
			HANDLE ModuleFile = CreateFile(ModName, GENERIC_READ,
						FILE_SHARE_READ, 0, OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL, 0);
			char TimeBuffer[100] = "";
			DWORD FileSize = 0;
			if (ModuleFile != INVALID_HANDLE_VALUE)
			{
				FileSize = GetFileSize(ModuleFile, 0);
				FILETIME	LastWriteTime;
				if (GetFileTime(ModuleFile, 0, 0, &LastWriteTime))
				{
					wsprintf(TimeBuffer, " - file date is ");
					PrintTime(TimeBuffer + lstrlen(TimeBuffer), LastWriteTime);
				}
				CloseHandle(ModuleFile);
			}
			hprintf(LogFile, "%s, loaded at 0x%08x - %d bytes - %08x%s\r\n",
						ModName, ModuleHandle, FileSize,
						NTHeader->FileHeader.TimeDateStamp, TimeBuffer);
		}
	}
	// Handle any exceptions by continuing from this point.
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}
}


//============================== Class Methods =============================

//=============
// Constructor 
//=============
zCExceptionHandler::zCExceptionHandler()
{
    //m_previousFilter = SetUnhandledExceptionFilter(UnhandledExceptionFilter);
}

//============
// Destructor 
//============
zCExceptionHandler::~zCExceptionHandler()
{
    SetUnhandledExceptionFilter( m_previousFilter );
}

void zCExceptionHandler :: SetIsActive(const zBOOL en) 
{
	if (en) {
		SetCrashHandlerFilter(UnhandledExceptionFilter);
	}
	else SetCrashHandlerFilter(0);

	isActive = en;
};

zBOOL zCExceptionHandler :: GetIsActive()
{
	return isActive;
};

//==============================================================
// Lets user change the name of the report file to be generated 
//==============================================================
void zCExceptionHandler::SetLogFileName( PTSTR pszLogFileName )
{
    _tcscpy( m_szLogFileName, pszLogFileName );
}

//===========================================================
// Entry point where control comes on an unhandled exception 
//===========================================================
LONG WINAPI zCExceptionHandler::UnhandledExceptionFilter(PEXCEPTION_POINTERS pExPtrs)
{
	static int BeenHere= false;
	static EXCEPTION_INFO exInfo;
	if (BeenHere)	// Going recursive! That must mean this routine crashed!
		return EXCEPTION_CONTINUE_SEARCH;
	BeenHere = true;

	WalkReleaseCallbacks();
	
	exInfo.csDepth = 0;
	exInfo.exPtrs  = pExPtrs;

	// [BENDLIN] Addon Patch2 - Crash-Log Dateiname sicherer
	char 	winAppEXEName[MAX_PATH];								// Executable name
	GetModuleFileName(NULL, winAppEXEName, sizeof(winAppEXEName));	// Get name of executable
	zSTRING mapName = zSTRING(winAppEXEName);
	int extPos = mapName.SearchRev(".");
	if ((extPos > 0) && (extPos > mapName.SearchRev("\\")))
		mapName.DeleteRight(mapName.Length() - extPos);
	mapName = mapName + ".rpt";
	SetLogFileName(mapName.ToChar());

	// TODO: delete first exception file

    m_hReportFile = CreateFile( m_szLogFileName,
                                GENERIC_WRITE,
                                0,
                                0,
                                OPEN_ALWAYS,
                                FILE_FLAG_WRITE_THROUGH,
                                0 );

    if ( m_hReportFile )
    {
        SetFilePointer( m_hReportFile, 0, 0, FILE_END );

	    // Start out with a banner
	    hprintf(m_hReportFile, _T("//======================UNHANDLED EXCEPTION======================\n") );
	    hprintf(m_hReportFile, _T("//======================UNHANDLED EXCEPTION======================\n") );

		exInfo.faultReason = (char *)GetFaultReason	  ( pExPtrs );

		hprintf(m_hReportFile, "%s\n" , exInfo.faultReason ) ;
		hprintf(m_hReportFile, "%s\n" , GetRegisterString ( pExPtrs ) ) ;

	    hprintf(m_hReportFile, _T("//=====================  INFOS =========================\n") );

		for (int i=0; i<ExceptionInfoCallbackList.GetNumInList(); i++) 
		{
			EXCEPTION_DESCR descr;
			descr.numErr = 0;
			ExceptionInfoCallbackList[i](&descr);
			
			for (int j=0; j<descr.numErr; j++) exInfo.callStack[exInfo.csDepth++] = descr.errDescr[j];
		}
					
		// now probably in exInfo are already additional infos set which could be included in the report file
		for (i=0; i<exInfo.csDepth; i++) {
			hprintf(m_hReportFile, "%s\n" , exInfo.callStack[i]) ;
		}

	    hprintf(m_hReportFile, _T("//====================== CALLSTACK ========================\n") );

		const char * szStart= "START";
		exInfo.callStack[exInfo.csDepth]  = (char*)malloc(strlen(szStart));
		strcpy(exInfo.callStack[exInfo.csDepth++],szStart);
		const char * szBuff = GetFirstStackTraceString ( GSTSO_PARAMS|GSTSO_MODULE|GSTSO_SYMBOL|GSTSO_SRCLINE,pExPtrs ) ;
		do
		{
			exInfo.callStack[exInfo.csDepth]  = (char*)malloc(strlen(szBuff));
			strcpy(exInfo.callStack[exInfo.csDepth++],szBuff);

			hprintf(m_hReportFile, "%s\n" , szBuff ) ;
			szBuff = GetNextStackTraceString ( GSTSO_PARAMS|GSTSO_MODULE|GSTSO_SYMBOL|GSTSO_SRCLINE, pExPtrs ) ;
		} while ( NULL != szBuff ) ;

		hprintf(m_hReportFile, _T("//=====================================================\n") );
		hprintf(m_hReportFile, _T("\n") );
		hprintf(m_hReportFile, _T("//===================== MODULES =======================\n") );

		RecordModuleList		(m_hReportFile);
		hprintf(m_hReportFile, _T("//=====================================================\n") );
        CloseHandle				( m_hReportFile );
        m_hReportFile = 0;

    }

	winDialogParamFinal(DIALOG_EXCEPTION, ExceptionDlgProc, (zDWORD)&exInfo);


    if ( m_previousFilter )
        return m_previousFilter( pExPtrs );
    else
		return EXCEPTION_EXECUTE_HANDLER  ;//      return EXCEPTION_CONTINUE_SEARCH;

}

void zCExceptionHandler::AddUnhandledExceptionReleaseCallback   ( EXCB_Release callBack )
{
	if (!ExceptionReleaseCallbackList.IsInList(callBack))	ExceptionReleaseCallbackList.InsertEnd(callBack);
};

void zCExceptionHandler::RemoveUnhandledExceptionReleaseCallback   ( EXCB_Release callBack )
{
	ExceptionReleaseCallbackList.RemoveOrder(callBack);
};

void  zCExceptionHandler::AddUnhandledExceptionInfoCallback   ( EXCB_Info callBack )
{
	if (!ExceptionInfoCallbackList.IsInList(callBack))	ExceptionInfoCallbackList.InsertEnd(callBack);
};

void  zCExceptionHandler::RemoveUnhandledExceptionInfoCallback( EXCB_Info callBack )
{
	ExceptionInfoCallbackList.RemoveOrder(callBack);
};

void  zCExceptionHandler::WalkReleaseCallbacks( )
{
	sysKillWindowsKeys(false);

	// alle zwingend zu releasende Module freigeben (in umgekehrter Reihenfolge
	for (int i=ExceptionReleaseCallbackList.GetNumInList()-1; i>=0; --i) 
	{
		ExceptionReleaseCallbackList[i]();
	}

	// dann alle Callbacks aus der Liste raus
	ExceptionReleaseCallbackList.DeleteList();
}


//===========================================================
// Entry point where control comes on an unhandled exception 
//===========================================================
LONG WINAPI zCExceptionHandler::AssertExceptionFilter(PEXCEPTION_POINTERS pExPtrs,ASSERT_FAIL_INFO* afInfo,EXCEPTION_INFO* exInfo )
{

	static int BeenHere= false;
	if (BeenHere)	// Going recursive! That must mean this routine crashed!
		return EXCEPTION_CONTINUE_SEARCH;

	BeenHere = true;

	WalkReleaseCallbacks();

	if (exInfo) exInfo->csDepth = 0;

	// [BENDLIN] Addon Patch2 - Crash-Log Dateiname sicherer
	char 	winAppEXEName[MAX_PATH];								// Executable name
	GetModuleFileName(NULL, winAppEXEName, sizeof(winAppEXEName));	// Get name of executable
	zSTRING mapName = zSTRING(winAppEXEName);
	int extPos = mapName.SearchRev(".");
	if ((extPos > 0) && (extPos > mapName.SearchRev("\\")))
		mapName.DeleteRight(mapName.Length() - extPos);
	mapName = mapName + ".rpt";
	SetLogFileName(mapName.ToChar());

	// TODO: delete first exception file

    m_hReportFile = CreateFile( m_szLogFileName,
                                GENERIC_WRITE,
                                0,
                                0,
                                OPEN_ALWAYS,
                                FILE_FLAG_WRITE_THROUGH,
                                0 );

    if ( m_hReportFile )
    {
        SetFilePointer( m_hReportFile, 0, 0, FILE_END );

	    // Start out with a banner
	    hprintf(m_hReportFile, _T("//======================ASSERTION FAILED======================\n") );
	    hprintf(m_hReportFile, _T("//======================ASSERTION FAILED======================\n") );
		
		exInfo->faultReason = (char *)GetFaultReason	  ( pExPtrs );

		hprintf(m_hReportFile, "Assertion failed: %s in file %s, Line: %i\n",afInfo->AssertText,afInfo->File,afInfo->Line) ;
		if (afInfo->Reason) {
			hprintf(m_hReportFile, "Reason: %s\n" , afInfo->Reason );
		}

		hprintf(m_hReportFile, "%s\n" , GetRegisterString ( pExPtrs ) ) ;

	    hprintf(m_hReportFile, _T("//=====================  INFOS =========================\n") );

		for (int i=0; i<ExceptionInfoCallbackList.GetNumInList(); i++) 
		{
			EXCEPTION_DESCR descr ;
			descr.numErr = 0;
			ExceptionInfoCallbackList[i](&descr);
			
			for (int j=0; j<descr.numErr; j++) exInfo->callStack[exInfo->csDepth++] = descr.errDescr[j];
		}

		// now probably in exInfo are already additional infos set which could be included in the report file
		for (i=0; i<exInfo->csDepth; i++) {
			hprintf(m_hReportFile, "%s\n" , exInfo->callStack[i]) ;
		}

	    hprintf(m_hReportFile, _T("//====================== CALLSTACK ========================\n") );
		const char * szStart= "START";
		exInfo->callStack[exInfo->csDepth]  = (char*)malloc(strlen(szStart));
		strcpy(exInfo->callStack[exInfo->csDepth++],szStart);

		const char * szBuff			= GetFirstStackTraceString ( GSTSO_PARAMS|GSTSO_MODULE|GSTSO_SYMBOL|GSTSO_SRCLINE,pExPtrs ) ;
		i = 0;
		do
		{
			exInfo->callStack[exInfo->csDepth]  = (char*)malloc(strlen(szBuff));
			strcpy(exInfo->callStack[exInfo->csDepth++],szBuff);
			if (i!=0) hprintf(m_hReportFile, "%s\n" , szBuff ) ;
			szBuff			= GetNextStackTraceString ( GSTSO_PARAMS|GSTSO_MODULE|GSTSO_SYMBOL|GSTSO_SRCLINE, pExPtrs ) ;
			i++;
		} while ( NULL != szBuff ) ;

		hprintf(m_hReportFile, _T("//=====================================================\n") );
		hprintf(m_hReportFile, _T("\n") );
		hprintf(m_hReportFile, _T("//===================== MODULES =======================\n") );

		RecordModuleList		(m_hReportFile);
        CloseHandle				( m_hReportFile );
        m_hReportFile = 0;
    }

    return EXCEPTION_EXECUTE_HANDLER;
}


//===========================================================
// Entry point where control comes on an unhandled exception 
//===========================================================
LONG WINAPI zCExceptionHandler::BoundsExceptionFilter(PEXCEPTION_POINTERS pExPtrs,ASSERT_FAIL_INFO* bfInfo,EXCEPTION_INFO* exInfo )
{
	static int BeenHere= false;
	if (BeenHere)	// Going recursive! That must mean this routine crashed!
		return EXCEPTION_CONTINUE_SEARCH;
	BeenHere = true;

	WalkReleaseCallbacks();

	// [BENDLIN] Addon Patch2 - Crash-Log Dateiname sicherer
	char 	winAppEXEName[MAX_PATH];								// Executable name
	GetModuleFileName(NULL, winAppEXEName, sizeof(winAppEXEName));	// Get name of executable
	zSTRING mapName = zSTRING(winAppEXEName);
	int extPos = mapName.SearchRev(".");
	if ((extPos > 0) && (extPos > mapName.SearchRev("\\")))
		mapName.DeleteRight(mapName.Length() - extPos);
	mapName = mapName + ".rpt";
	SetLogFileName(mapName.ToChar());

	exInfo->csDepth = 0;

	// TODO: delete first exception file

    m_hReportFile = CreateFile( m_szLogFileName,
                                GENERIC_WRITE,
                                0,
                                0,
                                OPEN_ALWAYS,
                                FILE_FLAG_WRITE_THROUGH,
                                0 );

    if ( m_hReportFile )
    {
        SetFilePointer( m_hReportFile, 0, 0, FILE_END );

	    // Start out with a banner
	    hprintf(m_hReportFile, _T("//======================BOUNDS CHECK FAILED======================\n") );
	    hprintf(m_hReportFile, _T("//======================BOUNDS CHECK FAILED======================\n") );

		exInfo->faultReason = (char *)GetFaultReason	  ( pExPtrs );

		hprintf(m_hReportFile, "Bounds check failed: %s in file %s, Line: %i\n",bfInfo->AssertText,bfInfo->File,bfInfo->Line) ;
		if (bfInfo->Reason) {
			hprintf(m_hReportFile, "Reason: %s\n" , bfInfo->Reason );
		}
		hprintf(m_hReportFile, "%s\n" , GetRegisterString ( pExPtrs ) ) ;

	    hprintf(m_hReportFile, _T("//=====================  INFOS =========================\n") );

		for (int i=0; i<ExceptionInfoCallbackList.GetNumInList(); i++) 
		{
			EXCEPTION_DESCR descr ;
			descr.numErr = 0;
			ExceptionInfoCallbackList[i](&descr);
			
			for (int j=0; j<descr.numErr; j++) exInfo->callStack[exInfo->csDepth++] = descr.errDescr[j];
		}

		// now probably in exInfo are already additional infos set which could be included in the report file
		for (i=0; i<exInfo->csDepth; i++) {
			hprintf(m_hReportFile, "%s\n" , exInfo->callStack[i]) ;
		}
	    hprintf(m_hReportFile, _T("//======================= CALLSTACK ==============================\n") );

		const char * szStart= "START";
		exInfo->callStack[exInfo->csDepth]  = (char*)malloc(strlen(szStart));
		strcpy(exInfo->callStack[exInfo->csDepth++],szStart);
		const char * szBuff = GetFirstStackTraceString ( GSTSO_PARAMS|GSTSO_MODULE|GSTSO_SYMBOL|GSTSO_SRCLINE,pExPtrs ) ;
		i = 0;
		do
		{
			exInfo->callStack[exInfo->csDepth]  = (char*)malloc(strlen(szBuff));
			strcpy(exInfo->callStack[exInfo->csDepth++],szBuff);
			if (i!=0) hprintf(m_hReportFile, "%s\n" , szBuff ) ;
			szBuff = GetNextStackTraceString ( GSTSO_PARAMS|GSTSO_MODULE|GSTSO_SYMBOL|GSTSO_SRCLINE, pExPtrs ) ;
			i++;
		} while ( NULL != szBuff ) ;

		hprintf(m_hReportFile, _T("//=====================================================\n") );
		hprintf(m_hReportFile, _T("\n") );
		hprintf(m_hReportFile, _T("//===================== MODULES =======================\n") );

		RecordModuleList		(m_hReportFile);
        CloseHandle				( m_hReportFile );
        m_hReportFile = 0;
    }

    return EXCEPTION_EXECUTE_HANDLER;
}


//======================================================================
// Scan memory looking for code modules (DLLs or EXEs). VirtualQuery is used
// to find all the blocks of address space that were reserved or committed,
// and ShowModuleInfo will display module information if they are code
// modules.
//======================================================================

void zCExceptionHandler::RecordModuleList(HANDLE LogFile)
{
	hprintf(LogFile, "\r\n"
					 "Module list: names, addresses, sizes, time stamps "
			"and file times:\r\n");
	SYSTEM_INFO	SystemInfo;
	GetSystemInfo(&SystemInfo);
	const size_t PageSize = SystemInfo.dwPageSize;
	// Set NumPages to the number of pages in the 4GByte address space,
	// while being careful to avoid overflowing ints.
	const size_t NumPages = 4 * size_t(ONEG / PageSize);
	size_t pageNum = 0;
	void *LastAllocationBase = 0;
	while (pageNum < NumPages)
	{
		MEMORY_BASIC_INFORMATION	MemInfo;
		if (VirtualQuery((void *)(pageNum * PageSize), &MemInfo,
					sizeof(MemInfo)))
		{
			if (MemInfo.RegionSize > 0)
			{
				// Adjust the page number to skip over this block of memory.
				pageNum += MemInfo.RegionSize / PageSize;
				if (MemInfo.State == MEM_COMMIT && MemInfo.AllocationBase >
							LastAllocationBase)
				{
					// Look for new blocks of committed memory, and try
					// recording their module names - this will fail
					// gracefully if they aren't code modules.
					LastAllocationBase = MemInfo.AllocationBase;
					ShowModuleInfo(LogFile, (HINSTANCE)LastAllocationBase);
				}
			}
			else
				pageNum += SIXTYFOURK / PageSize;
		}
		else
			pageNum += SIXTYFOURK / PageSize;
		// If VirtualQuery fails we advance by 64K because that is the
		// granularity of address space doled out by VirtualAlloc().
	}
}


