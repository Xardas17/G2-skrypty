/******************************************************************************** 
 
     $Workfile:: Zdisk_vdfs.cpp       $                $Date:: 24.04.01 17:33   $
     $Revision:: 30                   $             $Modtime:: 18.04.01 21:42   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/Zdisk_vdfs.cpp $
 * 
 * 30    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 29    16.03.01 15:45 Speckels
 * 
 * 28    14.03.01 18:01 Speckels
 * 
 * 27    15.02.01 18:39 Speckels
 * 
 * 26    14.02.01 23:12 Speckels
 * 
 * 25    14.02.01 23:08 Speckels
 * 
 * 24    14.02.01 21:04 Speckels
 * 
 * 23    14.02.01 17:12 Speckels
 * 
 * 22    14.02.01 15:51 Speckels
 * 
 * 21    8.02.01 16:25 Speckels
 * 
 * 20    6.02.01 17:08 Speckels
 * 
 * 19    28.01.01 18:47 Speckels
 * 
 * 18    3.11.00 15:04 Speckels
 * 
 * 17    11.10.00 12:10 Moos
 * 
 * 16    3.10.00 18:39 Herget
 * 
 * 15    1.09.00 16:00 Rueve
 * 
 * 14    28.08.00 14:24 Speckels
 * 
 * 19    23.08.00 21:47 Admin
 * 
 * 12    21.08.00 18:26 Speckels
 * 
 * 17    16.08.00 12:32 Admin
 * 
 * 11    10.08.00 21:47 Speckels
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 10    21.07.00 15:16 Speckels
 * 
 * 9     21.07.00 12:56 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 30 $ ($Modtime: 18.04.01 21:42 $)


#ifdef _VDFS

#include "zcore.h"
#include "zthread.h"
#include <zDisk_vdfs.h>
#include <ztools.h>

/*
// Statistische Daten
int		zFILE::s_numFilesOpenVdfs = 0;
int		zFILE::s_maxFilesOpenVdfs = 0;
*/

bool zFILE_VDFS::s_vdfsInitialized = false;
// [BENDLIN] AddonMOD
bool zFILE_VDFS::s_physical_first  = false;

void zFILE_VDFS::Init (const zSTRING& s)
{				
	vdfFindHandle	=	+0;
	vdfHandle	=	-1;
	vdfResult	=	-1;
	vdfEOF		=	false;
	// [BENDLIN] AddonMOD
	if (s_physical_first)
	{
	    SetMode(VDF_VIRTUAL | VDF_PHYSICAL | VDF_PHYSICALFIRST);
	}
	else
	{
		SetMode(VDF_VIRTUAL | VDF_PHYSICAL);
	}
}

zFILE_VDFS::zFILE_VDFS()
{ 	
	Init("");	
};

zFILE_VDFS::zFILE_VDFS(const zSTRING& path) : zFILE_FILE(path)
{	
	Init(path);
};

zFILE_VDFS::~zFILE_VDFS ()
{	
	if (zFILE_VDFS::IsOpened()) zFILE_VDFS::Close();
 	vdfHandle=-1;
	vdfResult=-1;	
	vdfEOF = false;
}

bool zFILE_VDFS::IsOpened()
{  
	if (!s_vdfsInitialized || write)	
	{
		return zFILE_FILE::IsOpened();
	}
	else
	{
		return (vdfHandle>=0);
	}
};

bool zFILE_VDFS::Exists()
{			
	if (!s_vdfsInitialized) return zFILE_FILE::Exists();

	LockCriticalSection();
		zSTRING s = GetFullPath();
		vdfResult = vdf_fexists(s.ToChar(), GetMode());
	UnlockCriticalSection();
	
	return vdfResult>0;
}
	

zERROR_ID zFILE_VDFS::HandleError(const zSTRING& method, const zSTRING& filename, zERROR_TYPE type)
{
	return zFILE_FILE::HandleError(method, filename, type);
}

zERROR_ID zFILE_VDFS::Open(bool writeMode)
{		
	if (!s_vdfsInitialized || writeMode) return zFILE_FILE::Open(writeMode);

	if (vdfHandle>=0) 
	{
		zERR_WARNING("B: VFILE: File is still opened. "+GetFilename());
		return zERR_NONE;
	}	

	zERROR_ID error_id = zERR_NONE;

	LockCriticalSection();	
		vdfHandle = vdf_fopen(GetFullPath().ToChar(),GetMode());		
			
		if (vdfHandle<0)
		{
			char buffer[250];
			vdf_getlasterror(buffer);
			zERR_FATAL("B: VFILE: "+zSTRING(buffer));			
			error_id = zERR_DSK_UNKNOWN;
		}
		#ifdef _DEBUG
		else
		{			
			if (s_maxFilesOpen<++s_numFilesOpen) s_maxFilesOpen = s_numFilesOpen;
			if (s_numFilesOpen>6)	zERR_WARNING("B: VFILE: Too many opened files !!!");
			if (vdfHandle>9)		zERR_WARNING("B: VFILE: Reached VDFS-limit of free file-handles!");			
		}	
		#endif	
	UnlockCriticalSection();

	return error_id;
}

zERROR_ID zFILE_VDFS::Close()
{	
	zFILE_FILE::Close();	
	
	if (!s_vdfsInitialized || (vdfHandle<0)) return zERR_NONE;
		
	LockCriticalSection();
		vdfResult = vdf_fclose(vdfHandle);	
		vdfHandle = -1;
	UnlockCriticalSection();

	zERR_ASSERTT(vdfResult>=0, "B: (zFILE_VDFS::Close) Error while closing file");
		
	#ifdef _DEBUG
	s_numFilesOpen--;
	#endif	
	
	return zERR_NONE;
}

zERROR_ID zFILE_VDFS::Reset()
{	
	return Seek(0);	
}

long zFILE_VDFS::Size()
{		
	if (!s_vdfsInitialized || (vdfHandle<0)) return zFILE_FILE::Size();
	
	LockCriticalSection();
		vdfResult = vdf_ffilesize(vdfHandle);
	UnlockCriticalSection();

	return vdfResult;
}

bool zFILE_VDFS::Eof()
{
	if (!s_vdfsInitialized || (vdfHandle<0)) return zFILE_FILE::Eof();
	return vdfEOF;
}



zERROR_ID zFILE_VDFS::Seek(long fpos)
{	
	if (!s_vdfsInitialized || (vdfHandle<0)) return zFILE_FILE::Seek(fpos);
	
/*
	#ifdef _DEBUG
	if ((Pos()>fpos) && (fpos>0) && found_virtual)
	{
		zERR_WARNING("B: VFILE: Backward seek-operation for virtual file "+GetFile()+" ("+zSTRING(Pos())+"->"+zSTRING(fpos)+")");			
		vdfResult = vdf_fseek(vdfHandle,0);			
	}	
	#endif 
*/
	
	LockCriticalSection();
		vdfResult = vdf_fseek(vdfHandle, fpos);	
		
		if (vdfResult>=0)  
		{
			vdfEOF = false;
		}
		else 
		{
			zERR_WARNING("B: VFILE: Seek "+zSTRING(fpos)+" on file "+GetFile()+" failed. Current position is "+zSTRING(Pos())+". Filesize is "+zSTRING(vdf_ffilesize(vdfHandle)));
		}
	UnlockCriticalSection();
	

	return zERR_NONE;
}

zSTRING zFILE_VDFS::SeekText(const zSTRING &s)
{	
	if (!s_vdfsInitialized || (vdfHandle<0)) return zFILE_FILE::SeekText(s);

	zSTRING line;
	zSTRING line2;

	do 
	{
		Read(line);
		line2 = line;
		if (line2.Search(s)>=0) return line;
	}
	while (!Eof());
		
	line.Clear();
	return line;
}

long zFILE_VDFS::Pos()
{
	if (!s_vdfsInitialized || (vdfHandle<0)) return zFILE_FILE::Pos();
	
	LockCriticalSection();
		vdfResult = vdf_ftell(vdfHandle);
	UnlockCriticalSection();
	
	return vdfResult;
}



void zFILE_VDFS::Append(void)
{
	Seek(Size());
}


zSTRING zFILE_VDFS::SetCurrentDir()
{
	char curpath[MAX_PATH];
	
	LockCriticalSection();	
		vdfResult = vdf_getdir(curpath);
	UnlockCriticalSection();
	
	strcat(curpath,zSTRING(DIR_SEPARATOR).ToChar());
	zSTRING fn = GetFilename();
	zSTRING fe = GetExt();
	SetPath(curpath);
	SetFilename(fn);
	SetExt(fe);	
	return GetPath();
}


zSTRING zFILE_VDFS::GetFullPath()
{
	zSTRING s = GetPath();

	if (!s.IsEmpty() && s[0]==DIR_SEPARATOR)	return s;
	else										return s_virtPathString + s;
};

zERROR_ID zFILE_VDFS::ChangeDir(bool physical)
{
	zFILE_FILE::ChangeDir();
	return zERR_NONE;
} 

zERROR_ID zFILE_VDFS::SearchFile(const zSTRING& fname, const zSTRING& searchDir, zBOOL rec)
{		
	zERR_ASSERT(this);
	vdfResult = -1;
	if (s_vdfsInitialized)
	{						
		char foundlist[1024];

		zFILE_FILE path;path.SetCurrentDir();
		zFILE_FILE searchPath;searchPath.SetPath(searchDir);
		searchPath.ChangeDir();

		LockCriticalSection();
			zERR_ASSERT(this);
			vdfResult = vdf_searchfile(fname.ToChar(), (char*)&foundlist);
		UnlockCriticalSection();
		
		if (vdfResult>0)
		{
			zSTRING filename = DIR_SEPARATOR+zSTRING(foundlist) + "|";
			filename.Delete("|",zSTR_FROM);	
			SetPath(filename);
		};

		path.ChangeDir();
		
	}	

	if (!s_vdfsInitialized || (vdfResult<=0)) 
	{
		return zFILE_FILE::SearchFile(fname, searchDir, rec);
	}
	else
	{
		return zERR_NONE;
	}
}

zERROR_ID zFILE_VDFS::GetStats(zFILE_STATS& stats) 
{
   	return zFILE_FILE::GetStats(stats);
}


bool zFILE_VDFS::FindFirst(const zSTRING& _filter)
{
	if (vdfFindHandle!=0)
	{
		LockCriticalSection();	
			vdf_findclose(vdfFindHandle);
		UnlockCriticalSection();
	
		vdfFindHandle=0;
	}

	// analyse filter (*.* and *.xxx are allowed)	
	if (_filter.SearchRev(".")>=0)
	{
		vdfFindExt = _filter.Copied(_filter.SearchRev("."));	
		vdfFindExt = vdfFindExt+"|";
	}
	if (vdfFindExt==".*|") vdfFindExt.Clear();
	vdfFindExt.Upper();	

	LockCriticalSection();
		vdfFindHandle = vdf_findopen((s_virtPathString+_filter).ToChar(), GetMode());
	UnlockCriticalSection();

	if (vdfFindHandle>0)
	{
		return FindNext();
	};

	return (vdfFindHandle>0);	
};

bool zFILE_VDFS::FindNext()
{	
	if (vdfFindHandle==0) return false;
	
	while (TRUE)
	{
		LockCriticalSection();	
			long result = vdf_findnext(vdfFindHandle, &find_filedata);
		UnlockCriticalSection();
	
		vdfHandle = -1;
		
		if (result>=0)
		{		
			if (find_filedata.attr & _A_SUBDIR) 
			{
				zSTRING dir = find_filedata.name;
				dir += "|";
				if (vdfFindExt.IsEmpty() || dir.Search(vdfFindExt)>=0) 
				{					
					SetPath(zSTRING(find_filedata.name)+DIR_SEPARATOR);				
					return true;
				}				
			}
			else
			{
				zSTRING name = find_filedata.name;
				name += "|";
				name.Upper();
				if (vdfFindExt.IsEmpty() || name.Search(vdfFindExt)>=0) 
				{
					SetPath(find_filedata.name);
					return true;
				}				
			}
		}
		else return false;
	}
	
	return false;

};



///
// READ-Methoden
///


zERROR_ID zFILE_VDFS::Read(char *s)
{	
	if (!s_vdfsInitialized) return zFILE_FILE::Read(s);

	zERR_ASSERTT(vdfHandle>=0, "B: (zFILE_VDFS::Read) File "+GetFile()+" not open");	

	strcpy(s,"");
	char ch;
	long readsize;		
	do 
	{
		LockCriticalSection();
			readsize = vdf_fread(vdfHandle,(char*)&ch,1);
		UnlockCriticalSection();
		
		if (readsize<0) 
			zERR_WARNING("B: VFILE: Error while reading a string from file "+GetFile());

		else if (readsize<1) 
			vdfEOF = true;

		else 
			strncat(s,&ch,1);
	}
	while (!vdfEOF && ch!='\n');
	
	return zERR_NONE;
}

zERROR_ID zFILE_VDFS::Read(zSTRING &s)
{	
	if (!s_vdfsInitialized) return zFILE_FILE::Read(s);

	zERR_ASSERTT(vdfHandle>=0,"B: (zFILE_VDFS::Read) File not open");	
		
	Read((char*)&read_buffer);
	s = read_buffer;
	
	// delete CR and LF
	while (s.Length()>0 && (s.GetLastChar()=='\n' || s.GetLastChar()=='\r'))	
		s.DeleteRight(1);			
	

	return zERR_NONE;
}

long zFILE_VDFS::Read(void *scr, long bytes)
{
	if (!s_vdfsInitialized) return zFILE_FILE::Read(scr,bytes);

	zERR_ASSERTT(vdfHandle>=0,"B: (zFILE_VDFS::Read) File not open");	
	
	LockCriticalSection();
		vdfResult = vdf_fread(vdfHandle, (char*)scr,bytes);
	UnlockCriticalSection();
	
	if (vdfResult<0)
		zERR_WARNING("B: VFILE: Error while reading from file "+GetFile());
	
	else if (vdfResult<bytes) 
		vdfEOF=true;

	return vdfResult;
}




///
//Initialisierung des Files-Systems
///

#include "direct.h"
#include "zwin32.h"

// #define _CHECKCD_

bool zFILE_VDFS::InitFileSystem()
{	
	zERR_MESSAGE(1,0,"B: VFILE: Initializing filesystem (VDFS)");
	zERR_ASSERTT(!s_vdfsInitialized, "B:VFILE: VDFS is already initialized");
	
	zFILE_FILE::InitFileSystem();


	// [BENDLIN] 1.30 VDFS-Initialisierung wird visualisiert
	// Die 'doppelte' Initialisierung fällt nicht ins Gewicht.
	// Dafür gibt es das Feedback, warum es so lange dauert.
	// (setzt Vdfs32g.exe im System-Verzeichnis voraus)
	{
		TCHAR Filename[MAX_PATH] = { 0 };
		TCHAR Filepath[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, Filename, MAX_PATH);
		LPTSTR Filebase = &Filename[lstrlen(Filename)-1];
		while ((Filebase >= Filename) && (Filebase[0] != '\\') && (Filebase[0] != '/'))
		{
			Filebase[0] = '\0';
			Filebase--;
		};
		lstrcpy(Filepath, Filename);
		Filebase = &Filepath[lstrlen(Filepath)-1];
		if ((Filebase[0] == '\\') || (Filebase[0] == '/'))
			Filebase[0] = '\0';
#ifdef LANG_ENU
		lstrcat(Filename, TEXT("Vdfs32e.exe"));
#else
		lstrcat(Filename, TEXT("Vdfs32g.exe"));
#endif
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		memset(&si, 0, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOW;
		if (CreateProcess(Filename, NULL, NULL, NULL, FALSE, 0, NULL, Filepath, &si, &pi))
		{
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
		}
	}
	
	s_criticalSection = zNEW(zCCriticalSection());

	// [BENDLIN] Addon Patch2 - VDFS-Init ohne CD-Volumes und mit besserer Fehlerbehandlung
	long numdisks = 0;
	long cddrives = 0;
	long numfound = 0;
	char cdid[100];
	strcpy(cdid, "G2ADDON1");				

	sysEvent();
	long result = vdf_initall(numdisks, cdid, &cddrives,&numfound);		
	sysEvent();
	
	if (result == 0)
	{
		s_vdfsInitialized = true;
		zERR_MESSAGE(2,0,"B: VFILE: VDFS successfully initialized: "+zSTRING(cddrives)+" drives, "+zSTRING(numfound)+" found.");

		//  ungenutzt long max_files = 10;
		//  ungenutzt long max_buffer = 1024;	// in kb
	}	
	else if (result == -1)
	{
		zERR_WARNING("B: VFILE: VDFS not initialized (-1: No Files)");	
	}
	else 
	{
		char buffer[250];
		vdf_getlasterror(buffer);
		zERR_WARNING("B: VFILE: VDFS not initialized (" + zSTRING(buffer) + ")");
	}
	
	return s_vdfsInitialized;
};


bool zFILE_VDFS::DeinitFileSystem()
{	
	zERR_MESSAGE(1,0,"B: VFILE: Deinitializing filesystem (VDFS)");

	if (s_vdfsInitialized) 
	{
		vdf_exitall();	

		zERR_MESSAGE(2,0,"B: zDSK: "+zSTRING(zFILE::s_maxFilesOpen)+" files were simultanously open!");
		if (s_numFilesOpen>0)
		{
			zERR_WARNING("B: zDSK: "+zSTRING(zFILE::s_numFilesOpen)+" files are still open!");
		};	

		s_vdfsInitialized = false;	
	}
	else
	{
		zERR_WARNING("B: VFILE: VDFS not initialized");						
	};

	
	delete s_criticalSection;s_criticalSection = 0;

	return zFILE_FILE::DeinitFileSystem();	
};


zCCriticalSection* zFILE_VDFS::s_criticalSection = 0;

bool zFILE_VDFS::LockCriticalSection()
{
	if (!s_criticalSection) return FALSE;
	s_criticalSection->Lock();
	return TRUE;
};

bool zFILE_VDFS::UnlockCriticalSection()
{
	if (!s_criticalSection) return FALSE;
	s_criticalSection->Unlock();
	return TRUE;	
}

#endif