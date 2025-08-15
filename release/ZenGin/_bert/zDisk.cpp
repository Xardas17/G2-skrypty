/******************************************************************************** 
 
     $Workfile:: Zdisk.cpp            $                $Date:: 26.04.01 15:35   $
     $Revision:: 44                   $             $Modtime:: 25.04.01 15:56   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/zengin/_Bert/Zdisk.cpp $
 * 
 * 44    26.04.01 15:35 Edenfeld
 * Soundprovider Checks sicherer gemacht,
 * AIPlayer Sprunghänger Bug gefixt
 * 
 * 43    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 41    6.02.01 17:08 Speckels
 * 
 * 40    1.02.01 22:32 Speckels
 * 
 * 39    1.02.01 22:18 Speckels
 * 
 * 38    31.01.01 0:30 Speckels
 * 
 * 37    30.01.01 18:59 Speckels
 * 
 * 36    28.01.01 19:35 Speckels
 * 
 * 35    9.01.01 18:13 Speckels
 * 
 * 34    6.11.00 14:35 Speckels
 * 
 * 33    3.11.00 15:03 Speckels
 * 
 * 32    30.10.00 16:58 Speckels
 * 
 * 31    26.10.00 21:31 Speckels
 * 
 * 30    26.10.00 14:36 Speckels
 * 
 * 29    24.10.00 16:01 Hildebrandt
 * 
 * 28    20.10.00 20:58 Speckels
 * 
 * 27    17.10.00 17:58 Speckels
 * 
 * 26    17.10.00 17:27 Speckels
 * 
 * 25    16.10.00 21:45 Edenfeld
 * 
 * 24    16.10.00 19:18 Hoeller
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 44 $ ($Modtime: 25.04.01 15:56 $)

#include "zcore.h"
#include "zDisk.h"
#include "zthread.h"
#include "zbuffer.h"

#include <stdio.h>
#include <direct.h>
#include <time.h>
#include <sys/stat.h>

//
// Root, virtuelles und physikalisches Verzeichnis:
// - Root-Verzeichnis: "c:\gothic\"
// - Virtuelles Verzeichnis: "\data\textures\"
// - Physikalisches Verzeichnis: "c:\gothic\data\textures\"
//



//
// Konstanten
//

const	char	DIR_SEPARATOR			= '\\';
const	int		zFILE_MAXCHARS			= 1024;

const	int		zFILE_BUFFER_SIZE		= 1024 * 100;		// Lesebuffer

//
// Static-Member
//

// Verzeichnisse
zSTRING	zFILE::s_rootDirString	= "";			// basic directory for writing to files and direct file-access
zFILE*	zFILE::s_virtPath = zNEW(zFILE_FILE);   // currently virtual path as a file-object
zSTRING	zFILE::s_virtPathString	= "";			// currently virtual path as a string
zSTRING	zFILE::s_physPathString	= "";			// currently physical path (complete path) as a string

zCBuffer* zFILE::bufferList[zFILE_MAX_OPEN];
int		  zFILE::bufferFlag[zFILE_MAX_OPEN];

zCCriticalSection* zFILE::s_dirscanCiticalSection = 0;

// Statistische Daten
int		zFILE::s_numFilesOpen = 0;
int		zFILE::s_maxFilesOpen = 0;

// Filesystem
bool	zFILE::s_initialized = false;

// Root-Verzeichnis setzen
zSTRING zFILE::SetRootDirectory(zSTRING s)
{
	s_rootDirString = s;
	if (s_rootDirString.GetLastChar()==DIR_SEPARATOR) s_rootDirString.DeleteRight(1);
	s_rootDirString.Upper();
	return s_rootDirString;
}

// Dateipfad zu komplettem physikalischem Pfad ergänzen, falls nötig
void zFILE::DirectFileConvert(zSTRING& filename)
{
	if ((filename.Length()>0) && (filename[0]==DIR_SEPARATOR)) 
		filename = s_rootDirString + filename;		

};

//
// Direkten Dateizugriff an- bzw. abmelden
//
void zFILE::DirectFileAccess(bool direct)
{
	static int counter=0;	// zaehlt Call-Tiefe dieser Methode

	if (direct)
	{				
		if (_chdir(s_physPathString.ToChar())) 
		{
			zERR_WARNING("B: (DirectFileAccess) Couldn't change to directory: "+s_physPathString);
		}
		counter++;
	}
	else
	{
		counter--;
		if (counter==0) _chdir(s_rootDirString.ToChar());
		else if (counter<0)
		{
			zERR_WARNING("B: zDSK: Unexpected DirectFileAccess(false)");
			counter=0;
		};
	};	
};


long int zFILE::GetFreeDiskSpace() // in kb
{
#ifndef _WIN32
	return 1024 * 100; // not yet implemented: return 100 MB
#else
	return 1024 * 100; // not yet implemented: 
#endif;
}

//
// Thread-Sicherheit
//
zBOOL zFILE::LockDirScan()
{
	if (!s_dirscanCiticalSection) return FALSE;
	s_dirscanCiticalSection->Lock();
	return TRUE;
};

zBOOL zFILE::UnlockDirScan()
{
	if (!s_dirscanCiticalSection) return FALSE;
	s_dirscanCiticalSection->Unlock();
	return TRUE;
};


// 
// Directer Dateizugriff ...
//
void zFILE::DirectFileAccess(bool direct, zSTRING& filename)
{
	DirectFileConvert(filename);
	DirectFileAccess(direct);	
};

//
// Operatoren für zDATE
//

int operator == (const zDATE& a, const zDATE& b) 
{
	zDWORD date1, date2;
	date1 = (zDWORD(a.day)<<24) + (zDWORD(a.hour)<<16) + (zDWORD(a.minute)<<8) + zDWORD(a.second);
	date2 = (zDWORD(b.day)<<24) + (zDWORD(b.hour)<<16) + (zDWORD(b.minute)<<8) + zDWORD(b.second);
	if (date1!=date2) return 0;
	date1 = (zDWORD(a.year)<<8) + zDWORD(a.month);
	date2 = (zDWORD(b.year)<<8) + zDWORD(b.month);
	return (date1==date2);
};

int operator < (const zDATE& a, const zDATE& b)  
{ 
	zDWORD date1, date2;
	date1 = (zDWORD(a.day)<<24) + (zDWORD(a.hour)<<16) + (zDWORD(a.minute)<<8) + zDWORD(a.second);
	date2 = (zDWORD(b.day)<<24) + (zDWORD(b.hour)<<16) + (zDWORD(b.minute)<<8) + zDWORD(b.second);
	if (date1>=date2) return 0;
	date1 = (zDWORD(a.year)<<8) + zDWORD(a.month);
	date2 = (zDWORD(b.year)<<8) + zDWORD(b.month);
	return (date1<date2);
};


zDATE& zDATE::operator=(time_t time)
{
	tm* _tm = localtime(&time);	
	second	= _tm->tm_sec;
    minute	= _tm->tm_min;
    hour	= _tm->tm_hour; 
    day		= _tm->tm_mday;  
    month	= _tm->tm_mon+1;
    year	= _tm->tm_year+1900;	
	return *this;
}

/*--------------------------------------------------------------------------
    zDATE::ToTime_t()

    19-Sep-00       [Michael]
                      neu
--------------------------------------------------------------------------*/ 
time_t zDATE::ToTime_t(void)
{
	tm _tm;
	
	_tm.tm_sec   = second;
	_tm.tm_min   = minute;
	_tm.tm_hour  = hour;
	_tm.tm_mday  = day;
	_tm.tm_mon   = month-1;
	_tm.tm_year  = year-1900;

	return mktime(&_tm);
}

zSTRING zDATE::ToString(zTDATE_CONVERT conv)
{
	char buffer[100];	
	if ((conv==zDATE_ALL) || (conv==zDATE_DATE))
	{
		sprintf(buffer,"%i.%i.%i",day,month,year);
	}
	if ((conv==zDATE_ALL) || (conv==zDATE_TIME))
	{
		if (hour + minute + second != 0)
			sprintf(buffer+strlen(buffer),"  %i:%i:%i",hour,minute,second);
	}
	zSTRING datestring(buffer);
	return datestring;
}





// *****************************************************************
// *****************************************************************
//
// Tools (lokale Funktionen
//
// *****************************************************************
// *****************************************************************



static int SearchTree(const zSTRING& filespec, zFILE_INFO* rep, zBOOL rec)
{	
	long find_handle=0;

	// Gibt es die Datei im aktuellen Verzeichnis?	
	_finddata_t		fileinfo;
	char			search_buffer[_MAX_PATH];

	if( (find_handle = _findfirst( filespec.ToChar(), &fileinfo )) != -1L)
	{	
		if (_getcwd(search_buffer, _MAX_PATH)!=0)
		{
			rep->Set(zSTRING(search_buffer)+DIR_SEPARATOR,zSTRING(fileinfo.name));			
		}
		_findclose(find_handle);find_handle=0;
		return 1;
	}	

	_findclose(find_handle);find_handle=0;

	// wenn nicht rekursiv: ENDE
	if (!rec) return 0; 
	
	// Nun die Unterverzeichnisse ...
	if( (find_handle = _findfirst( "*.*", &fileinfo )) != -1L ) 
	{
		do 
		{				
			if ((fileinfo.attrib & _A_SUBDIR) && (fileinfo.name[0]!='.'))			
			{	
				chdir(fileinfo.name);						
				if ( SearchTree(filespec,rep, rec) ) { _findclose( find_handle );return 1; }
				chdir("..");
			}

		} while (_findnext( find_handle, &fileinfo ) == 0);
	}
	
	// close handle
    _findclose( find_handle );
	
	return 0;
}



//
// Error-Handling
//


zERROR_ID zFILE_FILE::HandleError(const zSTRING& method, const zSTRING& filename, zERROR_TYPE level)
{
	zSTRING s;
	zERROR_ID id;
	switch (errno)
	{
	case EACCES : id = zERR_DSK_SHARE;  s = "Permission denied. (EACCES)";break;
	case EEXIST : id = zERR_DSK_EXISTS; s = "Filename already exists. (EEXIST)";break;
	case EINVAL : id = zERR_DSK_INVAL;  s = "??? Invalid flag or pmode argument. (EINVAL)";break;
	case EBADF  : id = zERR_DSK_HANDLE; s = "Bad file number. Possibly the file handle is not valid. (EBADF)";break;
	case EMFILE : id = zERR_DSK_TOOMANY;s = "Too many open files. No more file handles are available. (EMFILE)";break;
	case ENOENT : id = zERR_DSK_NOFILE; s = "No such file or directory. (ENOENT)";break;
	case ENOEXEC: id = zERR_DSK_EXEC;   s = "File is not executable. (ENOEXEC)";break;
	case ENOSPC : id = zERR_DSK_FULL;   s = "No space left on device. Maybe your disk is full. (ENOSPC)";break;
	case EXDEV  : id = zERR_DSK_MOVE;   s = "Cross-device link. An attempt was made to move a file to a different device. (EXDEV)";break;
	// own error-codes
	case zERR_DSK_NEWFILE : id = zERR_DSK_NEWFILE;s = "Don't set new filename while file is opened.";break;
	// default: unknown error
	default:	  id = zERR_DSK_UNKNOWN;s = "Unknown file-error! ";break;
	}	
	s = "B: zDSK: "+ s + " in "+method;
	if (!filename.IsEmpty()) s = s + " -> \"" + filename + "\"";

	switch (level)
	{
		case zERR_INFO:		zERR_MESSAGE(8,0,s);	break; 
		case zERR_WARN:		zERR_WARNING(s);		break;
		case zERR_FAULT:	zERR_FAULT(s);			break;	
		case zERR_FATAL:	zERR_FATAL(s);			break;
	};
	
	return id;
}




// *****************************************************************
// *****************************************************************
//
// zFILE
//
// *****************************************************************
// *****************************************************************




zFILE::zFILE()
{
	buffering	= FALSE;
	write		= FALSE;
};

zFILE::zFILE(const zSTRING& path)
{
	buffering	= FALSE;
	write		= FALSE;
};

zFILE::~zFILE()
{
};




// *****************************************************************
// *****************************************************************
//
// zFILE_FILE
//
// *****************************************************************
// *****************************************************************



////////// Construct and Destruct //////////////////////////////////



void zFILE_FILE::Init (const zSTRING& s)
{	
	SetPath(s);	
	file_handle	= 0;
	find_handle = 0;	
	buffer		= 0;
	error = zERR_NONE;			
		
	// SetBuffering(TRUE);
	SetBuffering(FALSE);	
}


zFILE_FILE::zFILE_FILE() 
{ 
	Init(""); 
};


zFILE_FILE::zFILE_FILE(const zSTRING& path)
{
	Init(path);
};


zFILE_FILE::~zFILE_FILE ()
{
	if (zFILE_FILE::IsOpened()) zFILE_FILE::Close();	
	file_handle	= 0;
	buffer=0;
}



bool zFILE_FILE::Exists()
{
	#ifdef _DEBUG
	if (file_handle) { zERR_FAULT("B: zDSK: File is still opened");return false; }
	#endif
	
	return file_handle || (_access(zFILE_FILE::GetFullPath().ToChar(),0) == 0);
}
	




zERROR_ID zFILE_FILE::GetStats(zFILE_STATS& stats)
{
	if (!Exists()) return zERR_DSK_EXISTS;

    struct _stat	buf;
            
    if(_stat(zFILE_FILE::GetFullPath().ToChar(),&buf) != 0) return zERR_DSK_EXISTS;

	// Time of last access of file.
	stats.createDate	= buf.st_ctime;
    stats.accessDate	= buf.st_atime;	
	stats.modifyDate	= buf.st_mtime;
	stats.size			= buf.st_size;

   	return zERR_NONE;
}




long zFILE_FILE::Size()
{	
	if (!file_handle) { zERR_FAULT("B: zDSK: File not open: "+GetFile());return -1;}
	
	// len is the position of the cursor at the end of the file:
	
	long file_pos	= Pos();				// remember position	
	fseek(file_handle,0,SEEK_END);			// set to end of file
	long len		= ftell(file_handle);	// get position of the files end (its length)
	fseek(file_handle,file_pos,SEEK_SET);	// reset position

	return len;
}



////////// Create, Open and Closefiles ////////////////////////////////


zERROR_ID zFILE_FILE::Create()
{
	#ifdef _DEBUG
	if (file_handle) zERR_FATAL("B: (zFILE_FILE:Create) File is still opened");
	#endif

	if (complete_path.IsEmpty()) { zERR_WARNING("B: zDSK: No Filename specified.");return zERR_UNKNOWN; }
			
	// try to open file in write-mode (create it)					
	file_handle = fopen(zFILE_FILE::GetFullPath().ToChar(),"w+b");	
	if (file_handle>0) // if successful ...
	{	
		zERR_MESSAGE(10,0,"B: zDSK: Created file "+GetFile());
		write = true;

		if (buffering)
		{
			buffer = GetFreeBuffer();
		};


		#ifdef _DEBUG
			if (s_maxFilesOpen < ++s_numFilesOpen)	s_maxFilesOpen = s_numFilesOpen;
			if (s_numFilesOpen > zFILE_MAX_OPEN)	zERR_FATAL("B: zDSK: Too many opened files!!!");		
		#endif
		return zERR_NONE;
	}
	else // otherwiese return an error-code
	{	
		return HandleError("Create",complete_path,zERR_TYPE_FAULT);	
	}	
}


zERROR_ID zFILE_FILE::Open(bool writeMode)
{		
	if (file_handle) { zERR_WARNING("B: zDSK: File is still opened");return zERR_NONE; };	
	if (complete_path.IsEmpty()) { zERR_WARNING("B: zDSK: There is no file specified to be opened.");return zERR_UNKNOWN; }
	
	write = writeMode;

	if (write && buffering)
	{
		buffer = GetFreeBuffer();
	};

	char mode[5];
	strcpy(mode,"r");		
	if (write) strcat(mode,"+");
	strcat(mode,"b");

	file_handle = fopen(zFILE_FILE::GetFullPath().ToChar(),mode);	
	if (file_handle)
	{
		zERR_MESSAGE(10,0,"B: zDSK: Opened file "+GetFile());

		#ifdef _DEBUG
		if (s_maxFilesOpen < ++s_numFilesOpen)	s_maxFilesOpen = s_numFilesOpen;
		if (s_numFilesOpen > zFILE_MAX_OPEN)	zERR_FATAL("B: zDSK: Too many opened files!!!");		
		#endif
		
		return zERR_NONE;
	}		
	else // otherwise return an error
	{
		return HandleError("Open",complete_path,zERR_TYPE_FAULT);
	}	
}


long zFILE_FILE::FlushBuffer()
{
	long count=0;
	if (buffer && buffer->GetSize()>=0)
	{
		/*

		zBOOL oldBufferMode = IsBuffering();
		SetBuffering(FALSE);
		Write(buffer.GetBuffer(),buffer.GetSize());		
		SetBuffering(oldBufferMode);
		*/

		// zERR_MESSAGE(4,0,"B: DSK: Flushing buffer to file "+filename);
		count = fwrite(buffer->GetBuffer(),buffer->GetSize(),1,file_handle);
		buffer->Reset();
	};
	return count;
};

zERROR_ID zFILE_FILE::Close()
{	
	#ifdef _DEBUG
	// if (!file_handle) zerr.Warn("B: zDSK: File is not open");
	#endif

	if (!file_handle) return zERR_NONE;

	if (buffer) 
	{
		FlushBuffer();
		ReleaseBuffer(buffer);
	}
	// [BENDLIN] 1.30 - flush closed files to disk
	fflush(file_handle);

	if (fclose(file_handle) == 0)  // if successfull ...
	{
		file_handle=0;
		
		#ifdef _DEBUG
			s_numFilesOpen--;
		#endif			

		zERR_MESSAGE(10,0,"B: zDSK: Closed file "+GetFile());
		return zERR_NONE;
	}
	else  // otherwise return an error
	{
		return HandleError("Close",complete_path);			
	}		
}







////////// Position of File-Pointer /////////////////////////////////////


zERROR_ID zFILE_FILE::Reset()
{	
	// seek to beginning of file
	return Seek(0);		
}




void zFILE_FILE::Append(void)
{
	#ifdef _DEBUG
	if (!file_handle) {zERR_FATAL("B: zDSK: File is not open!");return; }
	#endif
	
	// seek to end of file
	fseek(file_handle,0,SEEK_END);	
}




bool zFILE_FILE::Eof()
{
	#ifdef _DEBUG
	if (!file_handle) { zERR_FATAL("B: zDSK: File is not open!"); return false; }
	#endif

	return (feof(file_handle) != 0);
}





long zFILE_FILE::Pos()
{
	#ifdef _DEBUG
	if (!file_handle) 
		{ zERR_FATAL("B: zDSK: File not open: "+GetFile());return -1; }
	#endif
	
	return ftell(file_handle);
}




zERROR_ID zFILE_FILE::Seek(long fpos)
{
	#ifdef _DEBUG
	if (!file_handle) { zERR_FATAL("B: zDSK: File not open: "+GetFile()); return zERR_DSK_HANDLE; }
	#endif

	fseek(file_handle,fpos,SEEK_SET);	
	return zERR_NONE;
}





////////// Write some data ////////////////////////////////////////////





zERROR_ID zFILE_FILE::Write(const char *s)
{	
	zERR_ASSERTT(write,"B: (zFILE_FILE) File has not been opened for write-operations: "+GetFullPath());
	zERR_ASSERTT(file_handle,"B: zDSK: File is not open!");		
	
	zDWORD bytes = strlen(s);
	if (IsBuffering() && buffer && (bytes < buffer->GetMaxSize()))
	//
	// Buffering
	//	
	{
		if (bytes+buffer->GetSize() >= buffer->GetMaxSize()) 
			FlushBuffer();
		buffer->Write(s,bytes);
	}
	else
	{
		// write string to file
		if (fputs(s,file_handle)<0) return HandleError("Write",complete_path);	
		fflush(file_handle);
	}

	return zERR_NONE;
}





zERROR_ID zFILE_FILE::Write(const zSTRING &s)
{	
	return Write(s.ToChar());
}




long zFILE_FILE::Write(const void *scr,long bytes)
{			
	zERR_ASSERTT(write,"B: (zFILE_FILE) File has not been opened for write-operations: "+GetFullPath());
	zERR_ASSERTT(file_handle,"B: zDSK: File is not open!");		

	if (bytes == 0) 
	{ 
		zERR_WARNING("MR: zDSK: Write: 0 bytes to be written?!");return 0; 
	}
	
	long count = 0;
	if (IsBuffering() && buffer && (bytes < buffer->GetMaxSize()))
	//
	// Buffering
	//	
	{
		if (bytes+buffer->GetSize() >= buffer->GetMaxSize()) 
			FlushBuffer();
		buffer->Write(scr,bytes);
		count = 1;
	}
	else
	//
	// Direktes Schreiben
	//	
	{
		count = fwrite(scr,bytes,1,file_handle);
	};		
	


	if (count<=0) HandleError("Write",complete_path);			
	
	return count*bytes;
}





////////// Read some data ////////////////////////////////////////////




zERROR_ID zFILE_FILE::ReadChar (char& ch)
{
	#ifdef _DEBUG
	if (!file_handle) return zERR_FATAL("B: zDSK: File is not open!");
	#endif

	if ( Read((void*)&ch,1)!=1 ) return zERR_UNKNOWN;

	return zERR_NONE;	
};




zERROR_ID zFILE_FILE::Read(char *s)
{
	#ifdef _DEBUG
	if (!file_handle) return zERR_FATAL("B: zDSK: File is not open!");
	#endif
	
	if (fgets(s,zFILE_MAXCHARS,file_handle)<0) 
	{
		return HandleError("Read",complete_path, zERR_TYPE_WARN);
	}
	
	return zERR_NONE;
}

zERROR_ID zFILE_FILE::Read(zSTRING &s)
{	
	#ifdef _DEBUG
	if (!file_handle) return zERR_FATAL("B: zDSK: File is not open!");
	#endif

	char file_buffer[zFILE_MAXCHARS+1];
	long len;
	bool finished=false;	
	s.Clear();

	// read from file until CR found
	do	
	{
		if (fgets(file_buffer,zFILE_MAXCHARS,file_handle)==NULL) finished=true;
		else
		{
			len = strlen(file_buffer);			
			s += zSTRING(file_buffer);
			// delete CR and LF
			while (s.Length()>0 && (s.GetLastChar()=='\n' || s.GetLastChar()=='\r'))
			{ 
				if (s.GetLastChar()=='\n') finished=true;
				s.DeleteRight(1);			
			}
		}
	} while (!finished);

	return zERR_NONE;
}







long zFILE_FILE::Read(void *scr, long bytes)
{		
	#ifdef _DEBUG
	if (!file_handle) { zERR_FATAL("B: zDSK: File is not open!"); return -1; }
	if (!scr) 
	{ 
		zERR_WARNING("B: zDSK: Read: buffer is NULL");return 0; 
	}
	if (bytes == 0) 
	{ 
		zERR_WARNING("MR: zDSK: Read: 0 bytes to be read");return 0; 
	}
	#endif
	long count;
	
	// read data
	// MR: 2. und 3. Param getauscht wegen Performance
	count = fread(scr,bytes,1,file_handle);

	// check result
	if (count<0) HandleError("Read",complete_path, zERR_TYPE_WARN);
	#ifdef _DEBUG
	if (count == 0) 
	{ 		
		zERR_MESSAGE(8,0,"MR: zDSK: *** ATTENTION *** Short read: "+zSTRING(bytes)+" bytes to be read **********");
	}
	#endif	
	
	return count*bytes;
}



////////// Some othermethods ////////////////////////////////////////////




zSTRING zFILE_FILE::SeekText(const zSTRING &s)
{	
	#ifdef _DEBUG
	if (!file_handle) return zERR_FATAL("B: zDSK: File "+GetFile()+" is not open!");
	#endif

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


zERROR_ID zFILE_FILE::ReadCodeline(zSTRING &s)
{	
	#ifdef _DEBUG
	if (!IsOpened()) return zERR_FATAL("B: zDSK: File is not open!");
	#endif

	long p;
	long result;
	
	zSTRING line;
	s.Clear();	
	if (Eof()==0) 
	{
		result = Read(line);		
		s = line;
		p = s.Search("//"); 

		if (p>=0) s.Delete(p);		
		else if (s.GetLastChar()=='\n') s.DeleteRight(1);
		
		if (Pos() == -1) return HandleError("ReadCodeline",complete_path);

	} 
	else s = "<EOF>";

	return zERR_NONE;
}


zERROR_ID zFILE_FILE::ReadLines(zSTRING& str, long lines)
{	
	#ifdef _DEBUG
	if (!IsOpened()) return zERR_FATAL("B: zDSK: File is not open!");
	#endif

	zSTRING s;	
	for (long i=0;i<lines;i++)
	{
		Read(s);
		str += (s + "\n");
	}
	return zERR_NONE;
}

zSTRING zFILE_FILE::ReadBlock(long pos, long len)
{
	zSTRING s;
	Seek(pos);
	ReadLines(s,len);
	return s;
}


zERROR_ID zFILE_FILE::UpdateBlock(const zSTRING& s, long pos, long oldlen)
{	
	zSTRING s2 = s;

	zFILE* targetfile	= zfactory->CreateZFile(complete_path);	
	zFILE* bakfile		= zfactory->CreateZFile(complete_path);	
	bakfile->SetExt("bak");
	
	// Backup-Datei erstellen
	FileCopy(bakfile);

/*
	zSTRING bak_filename	= bakfile->GetPath();
	zSTRING target_filename	= targetfile->GetPath();

	DirectFileAccess(true);
		DirectFileConvert(bak_filename);
		DirectFileConvert(target_filename);
		remove(bak_filename.ToChar());
		rename(target_filename.ToChar(),bak_filename.ToChar());
	DirectFileAccess(false);
*/	
	
	// Dateien öffnen
	bakfile->Open();	
	Create();
	
	long max_buffer = bakfile->Size() + 1;
	zERR_MESSAGE(4, 0, "B: zDSK: Updating Source ("+zSTRING(double(max_buffer)/1024,3)+"kb)");
	char* buffer = zNEW(char)[max_buffer];
	
	// bis zum Blockanfang lesen und schreiben
	long count = bakfile->Read(buffer,pos);
	Write(buffer,count);		

	// Block schreiben
	Write(s2.ToChar());			
	bakfile->ReadBlock(pos,oldlen); // skip block

	// Rest lesen und schreiben
	count = bakfile->Read(buffer,bakfile->Size() - bakfile->Pos());
	Write(buffer,count);

	// Dateien schliessen
	bakfile->Close();
	Close();
	
	delete bakfile;bakfile=0;
	delete targetfile;targetfile=0;

	delete[] buffer;buffer=0;

	return zERR_NONE;
}



/*
zERROR_ID zFILE_FILE::DeleteBlock(long pos, long len)
{
	long file_pos = Pos();
	zSTRING s;
	// updating existing object
	zPATH targetpath = complete_path;
	zPATH bakpath(targetpath.GetPath());bakpath.SetExt("bak");
	rename(targetpath.GetPath().ToChar(),bakpath.GetPath().ToChar());
	zFILE_FILE bakfile(bakpath.GetPath());
		
	Create();

	long count;
	long max_buffer = 8192;
	void* buffer = malloc(max_buffer);	

	// read and write head	
	count = bakfile.Read(buffer,file_pos);
	
	zERR_ASSERTT(pos!=bakfile.Pos(), "B: zDSK: Different positions (Delete)");

	Write(buffer,count);
	// read and write tail
	bakfile.ReadBlock(file_pos,len);	
	count = bakfile.Read(buffer,max_buffer);
	
	Write(buffer,count);
	
	delete buffer;	

	return zERR_NONE;
};
*/





////////// Path-Manipulation ////////////////////////////////////////////////




void zFILE_FILE::SetCompletePath()
{
	complete_path.Clear();
	complete_directory.Clear();
	
	// Laufwerk
	if (!drive.IsEmpty()) complete_path = drive+":";

	// Verzeichnis
	if (!dir.IsEmpty())			
	{
		if (dir.GetLastChar()!=DIR_SEPARATOR) dir += DIR_SEPARATOR;
		complete_path += dir;	
	}

	complete_directory = complete_path;

	// Datei
	if (!filename.IsEmpty()) 
	{
		complete_path += filename;
		if (!ext.IsEmpty()) complete_path += "." + ext;
	}	
};




void zFILE_FILE::SetPath(zSTRING s)
{	
	drive.Clear();dir.Clear();filename.Clear();ext.Clear();
	s.Upper();
	SlashConvert(s);	

	long pos;
	long base_pos = s_rootDirString.Search(":");
	
	//** setting drive (e.g. "C")

	pos = s.Search(":");
	if (pos>=0) 
	{ 
		drive = s.Copied(0,pos);
		if (drive == s_rootDirString.Copied(0,base_pos)) drive.Clear();
		s.Delete(0,pos+1);
	}
	
	//** setting extension (i.e. "exe")
	
	pos = s.SearchRev(".");	
	if (pos>s.SearchRev(DIR_SEPARATOR))
	{
		if (pos>=0) 
		{
			ext = s.Copied(pos+1);
			s.Delete(pos);
		}
	}
	
	//** setting filename (without extension)
	
	pos = s.SearchRev(DIR_SEPARATOR);
	if (pos>=0) 
	{
		filename = s.Copied(pos+1);
		s.Delete(pos+1);
	}
	else // complete string is filename
	{ 
		filename = s;
		s.Clear();
	}

	//** setting Directory and truncating '\' at the end

	zSTRING base_dir = s_rootDirString.Copied(base_pos+1);
	dir = s;
	dir.Delete(base_dir);
	
	SetCompletePath(); 
}

void zFILE_FILE::SetDrive(zSTRING xDrive)       
{ 
	SlashConvert(xDrive);
	drive=xDrive;
	drive.Upper();
	SetCompletePath(); 
}

void zFILE_FILE::SetDir(zSTRING xDir)           
{ 
	SlashConvert(xDir);
	if (xDir.GetLastChar()!=DIR_SEPARATOR) xDir = xDir + DIR_SEPARATOR;
	dir = xDir;
	dir.Upper();
	SetCompletePath(); 
}

void zFILE_FILE::SetFilename(zSTRING xFilename) 
{ 
	SlashConvert(xFilename);
	filename=xFilename;
	filename.Upper();
	SetCompletePath(); 
}

void zFILE_FILE::SetExt(zSTRING xExt)           
{ 
	SlashConvert(xExt);
	ext=xExt;
	ext.Upper();
	SetCompletePath(); 
}	

void zFILE_FILE::SetFile(zSTRING xfilename)
{
	xfilename.Upper();
	long pos = xfilename.Search(".");
	if (pos==-1) 
	{ 
		filename=xfilename;ext.Clear();
	}
	else
	{
		filename = xfilename.Copied(0,pos);
		ext = xfilename.Copied(pos+1,xfilename.Length()-pos);
	}	
	SetCompletePath(); 
}

zSTRING zFILE_FILE::GetFullPath()
{
	zSTRING s = GetPath();

	if (!s.IsEmpty() && s[0]==DIR_SEPARATOR) 
		return s_rootDirString + s;

	else if (s.Length()>1 && s[1]==':') 
		return s;
 
	else 
		return s_rootDirString + s_virtPathString + s;
};

zSTRING& zFILE_FILE::SlashConvert(zSTRING& s)
{
	for (long i=0; i<s.Length(); i++) if (s[i]=='/') s[i]=DIR_SEPARATOR;
	return s;
};

zSTRING zFILE_FILE::SetCurrentDir()
{
	SetPath(s_virtPathString);
	return GetPath();
}


zERROR_ID zFILE_FILE::ChangeDir(bool physical)
{				
	if (complete_directory != s_virtPathString) 
	// Auswertung des Pfades und aktualisierung von "current_directory"	
	{		
		if (!drive.IsEmpty()) 
			s_virtPath->SetDrive(drive);
		if (!dir.IsEmpty())
		{
			if (dir[0]==DIR_SEPARATOR) s_virtPath->SetDir(dir);
			else s_virtPath->SetDir(s_virtPath->GetDir()+dir );
		};			
		// Aktuellen Pfad-String merken
		s_virtPathString = s_virtPath->GetPath();
		s_physPathString = s_rootDirString + s_virtPath->GetPath();
	}

	return zERR_NONE;
}





///////////// Searching a file /////////////////////////////////////////////

/*
zERROR_ID zFILE_FILE::SearchFile(const zSTRING& fname, const zSTRING& searchDir, zBOOL rec)
{		
	
	zERR_MESSAGE(10,0,"B: (zFILE_FILE::SearchFile) fileName: " + fname);
	if (fname.IsEmpty()) return zERR_PATH_NOTFOUND;
	if (zFILE::LockDirScan()) // threadsafe
	{
		zFILE_FILE path;path.SetCurrentDir();

		zFILE_FILE searchPath;searchPath.SetPath(searchDir);
		searchPath.ChangeDir();

		DirectFileAccess(true);

			if (Exists(fname)) 
			{
				SetPath(fname);			
				if (GetDir().IsEmpty()) SetDir(searchDir);
				error = zERR_NONE;			
			}
			else
			{
				zSTRING filename = fname;
				if (filename[0]==DIR_SEPARATOR) filename = s_rootDirString + filename;

				zFILE_INFO* rep = zNEW(zFILE_INFO());
				if (SearchTree(&filename,rep, rec)) 
				{					
					rep->path.Delete(s_rootDirString);
					SetPath(rep->path);
					SetFile(rep->name);		
					delete rep;		
					error = zERR_NONE; 
				}
				else 	
				{		
					delete rep;		
					error = zERR_PATH_NOTFOUND;
				}
			}

		DirectFileAccess(false);

		path.ChangeDir();

		zFILE::UnlockDirScan();
	}
	zERR_MESSAGE(10,0,"B: (zFILE_FILE::SearchFile) END" );

	return error;
}
*/


zSTRING	zFILE_FILE::DirStepInto(zSTRING dirname)
{
	if (dirname=="..")
	{
		int index = dir.SearchRev(DIR_SEPARATOR,2);
		if (index>=0) dir.Delete(index+1);		
	}
	else if (dirname!=".")
	{
		dir = dir + dirname + DIR_SEPARATOR;
	};	
	SetCompletePath();
	return dir;
};


static int SearchTreeWithoutDirchange(zFILE_FILE& searchPath, zSTRING root, zBOOL rec)
{	
	long find_handle=0;

	//
	// Gibt es die Datei im aktuellen Verzeichnis?	
	//	

	// zERR_MESSAGE(8,0,"B: DSK: Search file in \""+searchPath.GetFullPath()+"\"");

	_finddata_t	fileinfo;
	find_handle = _findfirst( searchPath.GetFullPath().ToChar(), &fileinfo);
	if (find_handle!=-1L)
	{					
		_findclose(find_handle);		
		return 1;
	}
	// _findclose(find_handle);	
	
	if (!rec) return 0; // wenn nicht rekursiv: ENDE
	
	//
	// Nun die Unterverzeichnisse ...
	//

	zSTRING searchMask = root + searchPath.GetDir() + "*.*";
	find_handle = _findfirst( searchMask.ToChar(), &fileinfo );
	if(find_handle!=-1L) 
	{
		do
		{							
			if ((fileinfo.attrib & _A_SUBDIR) && (fileinfo.name[0]!='.'))	// Unterverzeichnisse ...
			{	
				searchPath.DirStepInto(fileinfo.name);
				if ( SearchTreeWithoutDirchange(searchPath,root,rec) )		// ... durchsuchen.
				{ 					
					_findclose( find_handle );
					return 1;
				}
				searchPath.DirStepInto("..");								// zurueck zum letzten Verzeichnis
			}

		} while (_findnext( find_handle, &fileinfo ) == 0);

		_findclose( find_handle );
	}		    

	return 0;
}

zERROR_ID zFILE_FILE::SearchFile(const zSTRING& fname, const zSTRING& searchDir, zBOOL rec)
{		
	if (fname.IsEmpty()) // wenn der Dateiname leer ist, dann gibt es das file wohl auch nicht :)
		return zERR_PATH_NOTFOUND;

	// zERR_MESSAGE(8,zERR_BEGIN,"B: DSK: Search file \""+zSTRING(fname)+"\" in \""+searchDir+"\"");
	
	//
	// SuchPfad vorbereiten
	//	
	zFILE_FILE searchPath(fname);	
	if (searchPath.Exists() && searchPath.GetDir().Search(searchDir)>=0)
	{
		SetDir		(searchPath.GetDir());
		SetFilename	(searchPath.GetFilename());
		SetExt		(searchPath.GetExt());	
		return zERR_NONE;
	};

	searchPath.SetPath(searchDir);	// Pfad setzen
	searchPath.SetFile(fname);		// Dateiname setzen (auto*.bat)

	//
	// Gibt es die Datei vielleicht genau im angegebenen Verzeichnis?
	//	
	if (
			searchPath.Exists() 
			|| 
			SearchTreeWithoutDirchange(searchPath,s_rootDirString, rec)
	   ) 
	{	
		SetDir		(searchPath.GetDir());
		SetFilename	(searchPath.GetFilename());
		SetExt		(searchPath.GetExt());	
		return zERR_NONE;
	}
	else return zERR_PATH_NOTFOUND; 		
}

bool zFILE_FILE::FindFirst(const zSTRING& _filter)
{	
	if (find_handle)
	{
		_findclose(find_handle);
		find_handle=0;
	}

	find_handle = _findfirst((s_physPathString+_filter).ToChar(),&find_fileinfo);
	if (find_handle>=0)
	{
		if (find_fileinfo.attrib & _A_SUBDIR) 
		{
			zSTRING dir = find_fileinfo.name;
			SetPath(dir+DIR_SEPARATOR);
		}
		else
		{
			SetPath(find_fileinfo.name);
		}
	};
	return (find_handle>=0);
};

bool zFILE_FILE::DirCreate()
{
	DirectFileAccess(TRUE);
	zSTRING s = s_rootDirString+GetDirectoryPath();
	s.Lower();
	int result = mkdir(s.ToChar());
	DirectFileAccess(FALSE);
	return result==0;
};

bool zFILE_FILE::DirRemove()
{
	DirectFileAccess(TRUE);
	int result = rmdir(zSTRING(s_rootDirString+GetDirectoryPath()).ToChar());
	DirectFileAccess(FALSE);
	return result==0;
};

bool zFILE_FILE::DirExists()
{	
	DirectFileAccess(TRUE);
	bool result=false;
	char dir[MAX_PATH];
	int drive;
	_getcwd(dir,MAX_PATH);
	drive = _getdrive();
	
	if (_chdir(GetDirectoryPath().ToChar())==0)
	{
		result = true;
	};
	
	_chdrive(drive);
	_chdir(dir);
	DirectFileAccess(FALSE);
	return result;
};


bool zFILE_FILE::FileMove(zSTRING path, bool follow)
{
	bool result;
	zFILE_FILE new_file;
	new_file.SetPath(path);
	result = FileMove(&new_file);
	if (result && follow)
	{
		SetPath(new_file.GetFullPath());
	};
	return result;
};

bool zFILE_FILE::FileCopy(zSTRING path, bool follow)
{	
	bool result;
	zFILE_FILE new_file;
	new_file.SetPath(path);
	result = FileCopy(&new_file);
	if (result && follow)
	{
		SetPath(new_file.GetFullPath());
	};
	return result;		// patch 1.08, war vorher immer false
};

bool zFILE_FILE::FileDelete()
{
	if (IsOpened()) Close();	
	return (0==remove(GetFullPath().ToChar()));
};

bool zFILE_FILE::FileMove(zFILE* new_file)
{
	if (IsOpened()) Close();
	if (new_file->IsOpened()) new_file->Close();
	DirectFileAccess(TRUE);
	int result = rename(GetFullPath().ToChar(),new_file->GetFullPath().ToChar());
	DirectFileAccess(FALSE);
	return result==0;
};

bool zFILE_FILE::FileCopy(zFILE* new_file)
{		

	zERR_ASSERT(!IsOpened());
	zERR_ASSERT(!new_file->IsOpened());	

	//return CopyFile(GetFullPath().ToChar(), new_file->GetFullPath().ToChar(), FALSE);
	
	const int	max_size = zFILE_BUFFER_SIZE-1;
	char		buffer[max_size];	

	Open();	
	
	if (new_file->Create()!=zERR_NONE) return false;

	Reset();
	new_file->Reset();

	long filesize = Size();
	long read_size;
	while (filesize>0)
	{
		read_size = (filesize>max_size) ? max_size : filesize;
		read_size = Read(&buffer,read_size);
		filesize -= read_size;
		zERR_MESSAGE(9,0,"B: Filesize = "+zSTRING(filesize));
		zERR_ASSERT(filesize>=0);

		new_file->Write(buffer,read_size);		
	};

	new_file->Close();	

	Close();

	return true;
};


bool zFILE_FILE::FindNext()
{
	if (!find_handle) return false;

	int result = _findnext(find_handle, &find_fileinfo);
	if (result==0)
	{		
		if (find_fileinfo.attrib & _A_SUBDIR) 
		{
			zSTRING d = find_fileinfo.name;
			SetPath(d+DIR_SEPARATOR);
		}
		else
		{
			SetPath(find_fileinfo.name);
		}
	}
	else 
	{
		_findclose(find_handle);
		find_handle=0;
	}
	return (result==0);
};


zPATH::zPATH()
{ 
	path = zfactory->CreateZFile("");
};

zPATH::zPATH(zSTRING s)	
{ 
	path = zfactory->CreateZFile(s);
};

zCBuffer* zFILE::GetFreeBuffer()
{
	for (int i=0;i<zFILE_MAX_OPEN;i++)
	{
		if (bufferFlag[i] == 0) 
		{
			bufferFlag[i] = 1;			

			if (!bufferList[i])
			{
				zERR_MESSAGE(4,0,"B: DSK: Create new file-buffer: "+zSTRING(i));
				bufferList[i] = zNEW(zCBuffer);
				bufferList[i]->Resize(zFILE_BUFFER_SIZE);
			}
			else
			{
				bufferList[i]->Reset();
			};
			return bufferList[i];
		};		
	}	
	zERR_FATAL("B: DISK: Too many files ("+zSTRING(zFILE_MAX_OPEN)+") are open.");
	return 0;
};

void zFILE::ReleaseBuffer(zCBuffer* buffer)
{
	if (!buffer) return;

	for (int i=0;i<zFILE_MAX_OPEN;i++)
	{
		if (bufferList[i] == buffer)
		{
			bufferList[i]->Reset();
			bufferFlag[i] = 0;
		}
	}	
};


bool zFILE::InitFileSystem()
{
	zERR_MESSAGE(2, 0, "B: zDSK: InitFileSystem");
#ifdef COMPILING_SPACER
	if (s_initialized) return true;
#else
	zERR_ASSERTT(!s_initialized,"B: zDSK: filesystem is already initialized");	
#endif

	s_dirscanCiticalSection = zNEW(zCCriticalSection());
	s_numFilesOpen = 0;
	s_maxFilesOpen = 0;

	s_initialized = true;

	for (int i=0;i<zFILE_MAX_OPEN;i++)
	{
		bufferList[i] = 0; // Wird erst bei Bedarf erzeugt			
		bufferFlag[i] = 0; // 0 means free
	}

	return true;
};

bool zFILE::DeinitFileSystem()
{
	//zERR_MESSAGE(2, 0, "B: zDSK: DeinitFileSystem");
	zERR_ASSERTT(s_initialized,"B: zDSK: Filesystem is not initialized");

	delete s_dirscanCiticalSection;
	s_dirscanCiticalSection = 0;

	//zERR_MESSAGE(2,0,"B: zDSK: "+zSTRING(zFILE::s_maxFilesOpen)+" files were simultanously open!");
	if (zFILE::s_numFilesOpen>0)
	{
		zERR_WARNING("B: zDSK: "+zSTRING(zFILE::s_numFilesOpen)+" files are still open!");
	};	

	s_initialized = false;	
	
	for (int i=0;i<zFILE_MAX_OPEN;i++)
	{
		if (bufferList[i])
		{
			//zERR_MESSAGE(4,0,"B: DSK: Release file-buffer "+zSTRING(i));
			delete bufferList[i];
			bufferList[i]=0;
		}
	}

	return true;
};

/* ----------------------------------------------------------------------
	
    Init/DeinitFileSystem

	30.08.2000	[Moos]	
                Initialisierung und Aufräumen von s_virhPath hierher verlegt


   ---------------------------------------------------------------------- */


bool zFILE_FILE::InitFileSystem()
{	
    if (!s_virtPath)	
        s_virtPath=zNEW(zFILE_FILE); // [Moos] init

	return zFILE::InitFileSystem();	
};


bool zFILE_FILE::DeinitFileSystem()
{			
    delete s_virtPath; // [Moos]
    s_virtPath=NULL;
    
	return zFILE::DeinitFileSystem();		
};




void Dir_Clear (const zSTRING &dir, const zSTRING& mask)
// Lösche Inhalt des angegebenen Directory
{
	zFILE::DirectFileAccess(TRUE);	
	int res = _mkdir(dir.ToChar());
	if ((res==0) || ((res==-1) && (errno==EEXIST))) 
	{
		// Wurde erzeugt, oder existiert schon	
		int handle,w;
		_finddata_t found;

		zSTRING seek = dir + mask;
		
		handle = _findfirst(seek.ToChar(),&found);
		w = handle;
		while (w!=-1) 
		{
			if ((found.attrib & 0x10)==0) 
			{				
				zSTRING fileName = dir + found.name;
				chmod	( fileName.ToChar(), _S_IWRITE );
				remove (fileName.ToChar());
			}
			w = _findnext(handle,&found);
		}
	}
	zFILE::DirectFileAccess(FALSE);
}

void Dir_Copy (const zSTRING &source, const zSTRING &target)
{	
	Dir_Clear(target);

	zFILE::DirectFileAccess(TRUE);
	
	int res = _mkdir(source.ToChar());
	zFILE::DirectFileAccess(FALSE);

	if ((res==0) || ((res==-1) && (errno==EEXIST))) 
	{
		// Wurde erzeugt, oder existiert schon	
		int handle,w;
		_finddata_t found;

		zSTRING seek = source + "*.*";
		// Dann die einzelnen Files löschen

		zFILE::DirectFileAccess(TRUE);
		handle = _findfirst(seek.ToChar(),&found);
		zFILE::DirectFileAccess(FALSE);
		
		w = handle;
		// Allocate 64KB
		zBYTE* buffer = zNEW(zBYTE)[64000];
		
		while (w!=-1) 
		{
			
			if ((found.attrib & 0x10)==0) 
			{
				zFILE *fsrc = zfactory -> CreateZFile(source + found.name);
			
				fsrc->FileCopy(target + found.name);
				delete(fsrc);				
			}

			w = _findnext(handle,&found);
		}

		delete[] buffer;
	}	
}

