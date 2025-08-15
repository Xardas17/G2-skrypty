
//#include <windows.h>
//#include <stdio.h>
//#include <tchar.h>
//#include "special.h"
//#include "crc32.h"

////////////////////////////////////////////////////////////////////////////////
// INIT

#if		defined(JOWOOD_ENGLISH) || defined(JOWOOD_FRENCH) || defined(JOWOOD_GERMAN)
#error	Don't define JOWOOD_ENGLISH, JOWOOD_FRENCH, or JOWOOD_GERMAN (used locally)!
#endif
#if		defined(LANG_ENU)
#define	JOWOOD_ENGLISH
#elif	defined(LANG_FRA)
#define	JOWOOD_FRENCH
#elif	defined(LANG_DEU)
#define	JOWOOD_GERMAN
#else
#error	Please specify an target language for protected builds!
#endif

////////////////////////////////////////////////////////////////////////////////
// CHCK

SVKP_ENCRYPTED_BLOCK_TYPE2_START
{
	// Search for CDROM medium by volume name

	TCHAR SVKP_ret = _T('\0');
	while(_T('\0') == SVKP_ret)
	{
		TCHAR SVKP_dlist[(_MAX_DRIVE+1) * 26 + 1];
		GetLogicalDriveStrings((_MAX_DRIVE+1) * 26, SVKP_dlist);
		int SVKP_i;
		for (SVKP_i = 0; SVKP_i < (_MAX_DRIVE+1) * 26; SVKP_i += _MAX_DRIVE+1)
		{
			TCHAR SVKP_drive[_MAX_DRIVE+1];
			_tcsncpy(SVKP_drive, &SVKP_dlist[SVKP_i], _MAX_DRIVE+1);
			if (DRIVE_CDROM == GetDriveType(SVKP_drive))
			{
			    TCHAR SVKP_vname[_MAX_PATH+1];
			    DWORD SVKP_vsn, SVKP_mcl, SVKP_fsf;
				GetVolumeInformation(SVKP_drive, SVKP_vname, _MAX_PATH+1,
					&SVKP_vsn, &SVKP_mcl, &SVKP_fsf, NULL, 0);
				if (0 == _tcsicmp(SVKP_vname, _T("G2ADDON1")))
				{	
					SVKP_ret = SVKP_drive[0];
					break;
				}
			}
		}
		if (_T('\0') == SVKP_ret)
		{
#ifdef	JOWOOD_ENGLISH
			//FIXME: Translation
			if (IDRETRY != MessageBox(NULL,
				_T("Please insert the original CD into your CD/DVD-drive."),
				_T("Gothic II"),
				MB_RETRYCANCEL | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST))
#endif
#ifdef	JOWOOD_FRENCH
			//FIXME: Translation
			if (IDRETRY != MessageBox(NULL,
				_T("Insérez le CD original dans votre lecteur de CD-ROM ou de DVD-ROM."),
				_T("Gothic II"),
				MB_RETRYCANCEL | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST))
#endif
#ifdef	JOWOOD_GERMAN
			if (IDRETRY != MessageBox(NULL,
				_T("Bitte legen sie die Original-CD \"Gothic II - Die Nacht des Raben\" ein."),
				_T("Gothic II - Die Nacht des Raben"),
				MB_RETRYCANCEL | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST))
#endif
				TerminateProcess(GetCurrentProcess(), 1);
		}
	}

	// Open AR.EXE

	TCHAR SVKP_FileName[_MAX_PATH] = {SVKP_ret, _T('\0')};
/** /
	_tcscat(SVKP_FileName, _T(":\\data\\ar.exe"));
/**/
	HMODULE SVKP_ownModule = GetModuleHandle(NULL);
	GetModuleFileName(SVKP_ownModule, SVKP_FileName, _MAX_PATH);
	TCHAR SVKP_drive[_MAX_DRIVE+1];
	TCHAR SVKP_dir[_MAX_PATH+1];
	_tsplitpath(SVKP_FileName, SVKP_drive, SVKP_dir, NULL, NULL);
	_stprintf(SVKP_FileName, _T("%s%sar.exe"), SVKP_drive, SVKP_dir);
/**/

	HANDLE SVKP_hFileCrc = CreateFile(SVKP_FileName, GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == SVKP_hFileCrc)
	{
#ifdef JOWOOD_ENGLISH
		//FIXME: Translation
		MessageBox(NULL,
			_T("Please insert the original CD into your CD/DVD-drive."),
			_T("Gothic II"),
			MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST);
#endif
#ifdef JOWOOD_FRENCH
		//FIXME: Translation
		MessageBox(NULL,
			_T("Insérez le CD original dans votre lecteur de CD-ROM ou de DVD-ROM."),
			_T("Gothic II"),
			MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST);
#endif
#ifdef JOWOOD_GERMAN
		MessageBox(NULL,
			_T("Bitte legen sie die Original-CD \"Gothic II - Die Nacht des Raben\" ein."),
			_T("Gothic II - Die Nacht des Raben"),
			MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST);
#endif
		TerminateProcess(GetCurrentProcess(), 1);
	}

	// Allocate read buffer

	DWORD SVKP_filesize = GetFileSize(SVKP_hFileCrc, NULL);
	if (SVKP_filesize > 4000000)
		SVKP_filesize = 4000000;
	LPVOID SVKP_filedata = malloc(65536 + 2);
	if(!SVKP_filedata)
	{
		CloseHandle(SVKP_hFileCrc);
		MessageBox(NULL, _T("Error #124"), _T("Gothic II"),
			MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST);
		TerminateProcess(GetCurrentProcess(), 1);
	}

	// Caculate CRC value of AR.EXE

	DWORD SVKP_crc = crc32(0, NULL, 0);
	DWORD SVKP_size = 0;
	DWORD SVKP_block = 65536;
	do
	{
		SVKP_size += 65536;
		if ((SVKP_filesize - SVKP_size) < SVKP_block)
			SVKP_block = SVKP_filesize - SVKP_size;
		DWORD SVKP_read = 0;
		ReadFile(SVKP_hFileCrc, SVKP_filedata, SVKP_block, &SVKP_read, NULL);
		SVKP_crc = crc32(SVKP_crc, (unsigned char *)SVKP_filedata, SVKP_block);
	}
	while(SVKP_size < SVKP_filesize);
	free(SVKP_filedata);
	CloseHandle(SVKP_hFileCrc);

#ifdef JOWOOD_ENGLISH
	if (0x8D83BE07 != SVKP_crc)
	{
		//FIXME: Translation
		MessageBox(NULL,
			_T("Please insert the original CD into your CD/DVD-drive."),
			_T("Gothic II"),
			MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST);
		TerminateProcess(GetCurrentProcess(), 2);
	}
#endif
#ifdef JOWOOD_FRENCH
	if (0x8C75C93D != SVKP_crc)
	{
		//FIXME: Translation
		MessageBox(NULL,
			_T("Insérez le CD original dans votre lecteur de CD-ROM ou de DVD-ROM."),
			_T("Gothic II"),
			MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST);
		TerminateProcess(GetCurrentProcess(), 2);
	}
#endif
#ifdef JOWOOD_GERMAN
	if (0xBDE888AD != SVKP_crc)
	{
		MessageBox(NULL,
			_T("Integritätsfehler. Bitte überprüfen Sie das System mit einer aktuellen Antivirensoftware."),
			_T("Gothic II - Die Nacht des Raben"),
			MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST);
		TerminateProcess(GetCurrentProcess(), 2);
	}
#endif

	// Create Event

	TCHAR SVKP_EventName[10] = {_T('E'), _T('V'), _T('_')};
	_itot(6666, &SVKP_EventName[3], 10);
	SECURITY_ATTRIBUTES SVKP_saAttr = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	HANDLE SVKP_hEvent = CreateEvent(&SVKP_saAttr, TRUE, FALSE, SVKP_EventName);

	// Run AR.EXE

	STARTUPINFO SVKP_si;
	PROCESS_INFORMATION SVKP_pi;
	memset(&SVKP_si, 0, sizeof(STARTUPINFO));
	SVKP_si.cb = sizeof(STARTUPINFO);
	SVKP_si.dwFlags = STARTF_USESHOWWINDOW;
	SVKP_si.wShowWindow = SW_SHOWDEFAULT;
	if (!CreateProcess(SVKP_FileName, NULL, NULL, NULL, TRUE, 0, NULL, NULL,
		&SVKP_si, &SVKP_pi))
	{
		TerminateProcess(GetCurrentProcess(), 3);
	}
	else
	{
		WaitForSingleObject(SVKP_pi.hProcess, 240000);  // 4 min
		DWORD SVKP_lpExitCode = 0;
		GetExitCodeProcess(SVKP_pi.hProcess, &SVKP_lpExitCode);
		if (8181 != SVKP_lpExitCode)
		{
#ifdef JOWOOD_ENGLISH
			//FIXME: Translation
			MessageBox(NULL,
				_T("Please insert the original CD into your CD/DVD-drive."),
				_T("Gothic II"),
				MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST);
#endif
#ifdef JOWOOD_FRENCH
			//FIXME: Translation
			MessageBox(NULL,
				_T("Insérez le CD original dans votre lecteur de CD-ROM ou de DVD-ROM."),
				_T("Gothic II"),
				MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST);
#endif
#ifdef JOWOOD_GERMAN
			MessageBox(NULL,
				_T("Bitte legen sie die Original-CD \"Gothic II - Die Nacht des Raben\" ein."),
				_T("Gothic II - Die Nacht des Raben"),
				MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST);
#endif
			TerminateProcess(GetCurrentProcess(), 4);
		}
		CloseHandle(SVKP_pi.hThread);
		CloseHandle(SVKP_pi.hProcess);
	}

	// Check Event (state set by AR.EXE)

	if (!SVKP_hEvent || (WAIT_OBJECT_0 != WaitForSingleObject(SVKP_hEvent, 0)))
	{
		MessageBox(NULL,
			_T("Error #126"),
			_T("Gothic II"),
			MB_OK | MB_ICONINFORMATION | MB_TASKMODAL | MB_TOPMOST);
		TerminateProcess(GetCurrentProcess(), 4);
	}
}
SVKP_ENCRYPTED_BLOCK_TYPE2_END

////////////////////////////////////////////////////////////////////////////////
// EXIT

#ifdef JOWOOD_ENGLISH
#undef JOWOOD_ENGLISH
#endif
#ifdef JOWOOD_GERMAN
#undef JOWOOD_GERMAN
#endif
#ifdef JOWOOD_FRENCH
#undef JOWOOD_FRENCH
#endif

////////////////////////////////////////////////////////////////////////////////

