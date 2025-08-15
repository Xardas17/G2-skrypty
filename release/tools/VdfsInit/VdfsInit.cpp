// optimize filesize (VC6)
#pragma comment(linker, "/FIXED")
#pragma comment(linker, "/FILEALIGN:0x200")
#pragma comment(linker, "/MERGE:.data=.foo")
#pragma comment(linker, "/MERGE:.rdata=.foo")
#pragma comment(linker, "/MERGE:.text=.foo")
#pragma comment(linker, "/SECTION:.foo,EWR")
#pragma comment(linker, "/IGNORE:4078")

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>

#ifdef LANG_ENU
	#include "inc/Vdfs32e.h"
#else
	#include "inc/Vdfs32g.h"
#endif
#include "res/resource.h"


bool ErrorHandled = false;

void HandleError(UINT code, LPCTSTR text)
{
	ErrorHandled = true;
	if (code)
		MessageBox(NULL, text, TEXT("VDFS Init Tool"), MB_ICONERROR | MB_TASKMODAL| MB_OK);
	::ExitProcess(code);
}

// Init VDFS
DWORD WINAPI InitFileSystem(LPVOID lpThreadParameter)
{
 	UNREFERENCED_PARAMETER(lpThreadParameter);

	long NumDisks = 0;
	long CDsFound = 0;
	long NumFound = 0;
	char CDROM[100]; lstrcpyA(CDROM, "G2ADDON1");
	// [BENDLIN] Addon Patch2
	long initResult = vdf_initall(NumDisks, CDROM, &CDsFound, &NumFound);
	if (initResult == 0)
	{
//		Sleep(500);
//		Sleep(500);
		vdf_exitall();
//		Sleep(500);
//		Sleep(500);
		HandleError(0, NULL);
	}
	else
	{
		// "Err: -1: Can't start VDF-System (NoFiles)"
		if (initResult == -1)
			HandleError(0, NULL);
		else
		{
			char message[1024];
#ifdef LANG_ENU
			lstrcpy(message, "Error on initializing the virtual file system!\n\n");
#else
			lstrcpy(message, "Fehler bei der Initialisierung des virtuellen Dateisystems!\n\n");
#endif
			char lasterror[512];
			vdf_getlasterror(lasterror);
			lstrcat(message, lasterror);

			HandleError(7, message);
		}
	}

	return 0;
};

HINSTANCE hInst = NULL;
WPARAM ProgressPos = 0;
bool DlgMoved = false;
bool TimerSet = false;

// Progess Dialog (faked)
BOOL CALLBACK ProgressDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hDlg);
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	HWND ProgressBar;
	RECT DlgRect;

	switch (uMsg)
	{
	case WM_INITDIALOG:

		::SetClassLong(hDlg, GCL_STYLE,
			::GetClassLong(hDlg, GCL_STYLE) | CS_NOCLOSE);

		ProgressBar = ::GetDlgItem(hDlg, IDC_PROGRESS);
		if (ProgressBar)
		{
			::SendMessage(ProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 1023));
			::SendMessage(ProgressBar, PBM_SETPOS, 0, 0);
		};

		if (ErrorHandled)
		{
			::DestroyWindow(hDlg);
			return TRUE;
		}

		::SetTimer(hDlg, 1, 5000, NULL);

		return TRUE;

	case WM_TIMER:

		if (ErrorHandled)
		{
			::DestroyWindow(hDlg);
			return FALSE;
		}

		if (!TimerSet)
		{
			TimerSet = true;
			::KillTimer(hDlg, 1);
			::SetTimer(hDlg, 1, 100, NULL);
		}

		if (!DlgMoved && ::GetWindowRect(hDlg, &DlgRect))
		{
			DlgMoved = true;
			::MoveWindow(hDlg, DlgRect.left, DlgRect.top + 200, DlgRect.right - DlgRect.left, DlgRect.bottom - DlgRect.top, TRUE);
		}

		ProgressPos += 10;
		if (ProgressPos > 1000)
			ProgressPos = 0;

		::SetWindowPos(hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		ProgressBar = ::GetDlgItem(hDlg, IDC_PROGRESS);
		if (ProgressBar)
			::SendMessage(ProgressBar, PBM_SETPOS, ProgressPos, 0);

		return FALSE;
	};

	return FALSE;
};

int ReadFileLine(HANDLE file, LPSTR buf, DWORD size)
{
	LPSTR pos = buf;
	CHAR chr;
	DWORD num;

	if (size == 0)
		return 0;

	while (::ReadFile(file, &chr, sizeof(chr), &num, NULL) && (num == sizeof(chr)))
	{
		if ((DWORD)(pos - buf) < (size - 1))
		{
			if (chr == 0x09)
				chr = 0x20;
			if ((chr == 0x20) && ((pos == buf) || (pos[-1] == 0x20)))
				continue;
			pos[0] = chr;
			pos++;
		}
		if ((chr == 0x0A) || (chr == 0x0D))
			break;
	}
	pos[0] = '\0';

	return ::lstrlenA(buf);
}

// Entry Point
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	static MEMORY_BASIC_INFORMATION mbi;
	::VirtualQuery(&mbi, &mbi, sizeof(mbi));
	hInstance = (HINSTANCE)mbi.AllocationBase;

	::InitCommonControls();

	// get own module filename
	TCHAR OwnFilename[MAX_PATH];
	::GetModuleFileName(NULL, OwnFilename, sizeof(OwnFilename) / sizeof(OwnFilename[0]));
	::GetLongPathName(OwnFilename, OwnFilename, sizeof(OwnFilename) / sizeof(OwnFilename[0]));
	// get own module filepath
	TCHAR OwnFilepath[MAX_PATH];
	::lstrcpy(OwnFilepath, OwnFilename);
	LPTSTR OwnFilenamePos = &OwnFilepath[lstrlen(OwnFilepath) - 1];
	while ((OwnFilenamePos >= OwnFilepath) && (OwnFilenamePos[0] != TCHAR('\\')) && (OwnFilenamePos[0] != TCHAR('/')))
	{
		OwnFilenamePos[0] = TCHAR('\0');
		OwnFilenamePos--;
	}
	if ((OwnFilenamePos >= OwnFilepath) && ((OwnFilenamePos[0] == TCHAR('\\')) || (OwnFilenamePos[0] == TCHAR('/'))))
		OwnFilenamePos[0] = TCHAR('\0');

	// [BENDLIN] Addon Patch2
	CharUpper(OwnFilepath);

	// set our filepath to current working directory
	if (!::SetCurrentDirectory(OwnFilepath))
#ifdef LANG_ENU
		HandleError(2, TEXT("Error on setting current directory!"));
#else
		HandleError(2, TEXT("Fehler beim Setzen des aktuellen Verzeichnisses!"));
#endif

	// get root dir from paths.d
	TCHAR RootDir[MAX_PATH];
	RootDir[0] = TCHAR('\0');
	bool RootFound = false;
	TCHAR OptFilename[MAX_PATH];
	::lstrcpy(OptFilename, OwnFilepath);
	::lstrcat(OptFilename, TEXT("\\Paths.d"));
	HANDLE OptFile = ::CreateFile(OptFilename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0);
	if (OptFile == INVALID_HANDLE_VALUE)
	{
		TCHAR msg[4096];
		::lstrcpy(msg, OptFilename);
#ifdef LANG_ENU
		::lstrcat(msg, TEXT(" cannot be opened for read access!"));
#else
		::lstrcat(msg, TEXT(" konnte nicht zum Lesen geöffnet werden!"));
#endif
		HandleError(3, const_cast<LPCTSTR>(msg));
	}
	else
	{
		int BytesRead;
		do
		{
			CHAR CurrentLine[4096];
			BytesRead = ReadFileLine(OptFile, CurrentLine, sizeof(CurrentLine));
			// search for 'CONST STRING DIR_ROOT="";'
			if (BytesRead >= 25)
			{
				CHAR Command[50];
				lstrcpynA(Command, CurrentLine, 22);
				if (::lstrcmpiA(Command, "CONST STRING DIR_ROOT") == 0)
				{
					LPSTR StartPos = &CurrentLine[21];
					if (StartPos[0] == 0x20)
						StartPos++;
					if (StartPos[0] != '=')
						continue;
					StartPos++;
					if (StartPos[0] == 0x20)
						StartPos++;
					if (StartPos[0] != '"')
						continue;
					StartPos++;

					LPSTR EndPos = &StartPos[1];
					while (EndPos != '\0')
					{
						if (EndPos[0] == '"')
						{
							EndPos[0] = '\0';
							EndPos++;
							if (EndPos[0] == 0x20)
								EndPos++;
							if (EndPos[0] != ';')
								break;

							::lstrcpyA(RootDir, StartPos);
							RootFound = true;
						}
						EndPos++;
					}
					if (RootFound)
						break;
				}
			}
		}
		while (BytesRead > 0);

		if (!RootFound)
#ifdef LANG_ENU
			HandleError(4, TEXT("ROOT_DIR not found in Paths.d!"));
#else
			HandleError(4, TEXT("ROOT_DIR wurde nicht in Paths.d gefunden!"));
#endif

		::CloseHandle(OptFile);
	}

	// [BENDLIN] Addon Patch2
	CharUpper(RootDir);

	// change working directory (cdup)
	if (!::SetCurrentDirectory(RootDir))
#ifdef LANG_ENU
		HandleError(5, TEXT("Error on setting ROOT_DIR as current directory!"));
#else
		HandleError(5, TEXT("Fehler beim Wechsel ins ROOT_DIR-Verzeichnis!"));
#endif

	// change working directory (cdup)
	if (::GetFileAttributes(TEXT("VDFS.CFG")) == DWORD(-1))
#ifdef LANG_ENU
		HandleError(6, TEXT("VDFS.CFG not found in root directory!"));
#else
		HandleError(6, TEXT("Im Wurzelverzeichnis wurde keine VDFS.CFG gefunden!"));
#endif

	// Init VDFS
	DWORD ThreadId = 0;
	HANDLE InitThread = ::CreateThread(NULL, 0, InitFileSystem, NULL, 0, &ThreadId);

	// Show Dialog
	HWND ProgressDlg = ::CreateDialog(hInstance, MAKEINTRESOURCE(IDD_PROGRESS), NULL, ProgressDlgProc);
	if (ProgressDlg)
	{
		MSG Msg;
		while (::GetMessage(&Msg, ProgressDlg, NULL, NULL))
		{
			if (!::IsDialogMessage(ProgressDlg, &Msg))
			{
				::TranslateMessage(&Msg);
				::DispatchMessage(&Msg);
			}
		}
	}
	// [BENDLIN] Addon Patch2
/** /
	else
	{
		LPVOID lpMsgBuf;
		::FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
		::MessageBox(NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION);
		LocalFree(lpMsgBuf);
	}
/**/

	// Wait if someone closes the dialog
	::WaitForSingleObject(InitThread, INFINITE);

	HandleError(0, NULL);
	return 0;
}
