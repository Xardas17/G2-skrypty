/******************************************************************************** 
 
     $Workfile:: Zdisk.h              $                $Date:: 24.04.01 17:33   $
     $Revision:: 20                   $             $Modtime:: 18.04.01 18:48   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Classes used to access files and directories: 
   Open, Create; Read, Write; Remove, Rename and more

   Attention: 
   Using drives is not useful if using a root-directory, 
   cause all paths are relative to that root. "\" is the defined root, not
   the lowest physical directory.
   See also static method SetRootDirectory()


 * $Log: /current_work/ZenGin/_Bert/Zdisk.h $
 * 
 * 20    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 18    4.12.00 18:22 Moos
 * 
 * 17    6.11.00 14:35 Speckels
 * 
 * 16    3.11.00 15:04 Speckels
 * 
 * 15    20.10.00 20:58 Speckels
 * 
 * 14    17.10.00 16:12 Speckels
 * 
 * 13    9.10.00 20:53 Speckels
 * 
 * 12    20.09.00 1:00 Rueve
 * 
 * 11    8.09.00 17:37 Hildebrandt
 * fixed minor compiler warnings
 * 
 * 10    28.08.00 15:15 Speckels
 * 
 * 19    23.08.00 21:47 Admin
 * 
 * 8     21.08.00 18:26 Speckels
 * 
 * 17    16.08.00 12:32 Admin
 * 
 * 7     10.08.00 21:47 Speckels
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 6     21.07.00 12:56 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 20 $ ($Modtime: 18.04.01 18:48 $)



//
// TODO:
// Ermittlung von zur Verfuegung stehendem Speicherplatz (GetFreeDiskSpace)
//
//

#ifndef __ZDISK_H__
#define __ZDISK_H__

#ifndef __ZSTRING_H__
#include <zString.h>
#endif

#ifndef __ZERROR_H__
#include <zError.h>
#endif

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

#ifndef _INC_IO
#include <io.h>
#endif

// Forward-Declarations:

class zCCriticalSection;
class zCBuffer;


// Typen

enum PATH_ERROR_ID     // ab 5000
{
	zERR_PATH_UNKNOWN = 5000,
	zERR_PATH_CHANGEDIR,
	zERR_PATH_MAKEDIR,	
	zERR_PATH_NOTFOUND,
	zERR_PATHDLG_OK,
	zERR_PATHDLG_CANCEL,
	zERR_PATHDLG_ERROR

};

enum DSK_ERROR_ID      // ab 5100
{
	zERR_DSK_UNKNOWN = 5100,
	zERR_DSK_SHARE,
	zERR_DSK_EXISTS,
	zERR_DSK_INVAL,
	zERR_DSK_HANDLE,
	zERR_DSK_TOOMANY,
	zERR_DSK_NOFILE,
	zERR_DSK_EXEC,
	zERR_DSK_FULL,
	zERR_DSK_MOVE,
	zERR_DSK_NEWFILE
};

enum zTDATE_CONVERT { zDATE_ALL, zDATE_DATE, zDATE_TIME };


//
// öffentliche Konstanten
//

extern const char	DIR_SEPARATOR;

const int	zFILE_MAX_OPEN = 6;



// ********************************************************************
// ********************************************************************
//
// DATE-class for File-Informations
//
// ********************************************************************
// ********************************************************************



class zDATE
{
public:
	unsigned int	year;
	unsigned short	month;
	unsigned short	day;	
	unsigned short	hour;
	unsigned short	minute;
	unsigned short	second;

public:
	void	SetDate(unsigned short d, unsigned short m, unsigned short y) { day = d;month=m;year=y; }
	void	SetTime(unsigned short h, unsigned short m, unsigned short s) { hour=h;minute=m;second=s; } 
	time_t  zDATE::ToTime_t(void);
	zSTRING	ToString(zTDATE_CONVERT conv);
	
	// operators:

    friend int	operator ==	(const zDATE& a, const zDATE& b);
	friend int	operator <	(const zDATE& a, const zDATE& b);

    friend int	operator !=	(const zDATE& a, const zDATE& b)	{ return !(a==b); };    
    friend int	operator >	(const zDATE& a, const zDATE& b)	{ return ((a!=b) && (!(a<b))); };
    friend int	operator <=	(const zDATE& a, const zDATE& b)	{ return ((a==b) || (a<b)); }; 
    friend int	operator >=	(const zDATE& a, const zDATE& b)	{ return ((a==b) || (a>b)); }; 
	zDATE&		operator =	(time_t time);
};




// ********************************************************************
// ********************************************************************
//
// File-Statistics
//
// ********************************************************************
// ********************************************************************


class zFILE_STATS
{
public:
	zDATE			accessDate;		// Time of last access of file.
	zDATE			createDate;		// Time of creation of file.	
	zDATE			modifyDate;		// Time of last modification of file.	
	unsigned int	size;    // size of file
};





// ********************************************************************
// ********************************************************************
//
// File-Statistics
//
// ********************************************************************
// ********************************************************************




class zFILE_INFO
{
public: 
	zSTRING path;
	zSTRING name;

public:
	zFILE_INFO() 
	{ 
		name.Clear(); path.Clear(); 
	};
		
	zFILE_INFO(zSTRING& _path, zSTRING& _name)
	{
		Set(_path,_name);
	};

	void Set(zSTRING& _path, zSTRING& _name)
	{
		path = _path.Upper();		
		name = _name.Upper();		
	};

protected:
	
	zFILE_INFO(zFILE_INFO&);
	zFILE_INFO& operator=(zFILE_INFO&);
};





// ********************************************************************
// ********************************************************************
//
// File-Interface (abstract class)
//
// ********************************************************************
// ********************************************************************




/** This abstract class declares an interface for accessing files and directories.
 * file-objects (instances of derived classes) store a complete path 
 * (separated into drive, directory, filename and extension) to allow various operations: 
 * - change to the directories
 * - check the existance of files and directories
 * - create and open files for reading and writing 
 * 
 * Different derived classes may implement physical or virtual file-access.
 *
 * Using virtual paths with a root-directory is implemented in derived classes but 
 * considered in the base-class as well.
 **/

class zFILE
{
public:	

	// Set the root-directory.
	// All path- and file-action will be relativ to this path. 
	// 
	// Example: A ChangeDir() for "\data\textures\"
	// will not change to "DRIVE:\data\textures\"
	// but to "ROOT_DIRECTORY\data\textures\"
	//
	// Attention: Drives are not allowed if a root-directory is defined
	static zSTRING	SetRootDirectory(zSTRING s);		

	///
	// Direct File-Access
	// Starts a direct fileaccess or deactivates the last
	///
	
	// These Methods will change the virtual directory physically (true)
	// or change back physically to the root-directory (false)
	// If a 2nd String-Parameter is given, this filename will be converted 
	// to the complete path including the root-directory

	static void		DirectFileAccess(bool direct);
	static void		DirectFileAccess(bool direct, zSTRING& filename);		

	// Methods for thread-save operations on files and directories
	static zBOOL	LockDirScan();
	static zBOOL	UnlockDirScan();

	// Return the current virtual directory as a string
	static const zSTRING& GetCurrentDir() { return s_virtPathString; };

	///
	// Initialize the file-system
	///
	static bool		InitFileSystem();
	static bool		DeinitFileSystem();
	
//*********************************************************
// Constructor/Destructor
//*********************************************************
		
	zFILE();					// construct a file without specified path to a file (must be specified in Open or Create)	
	zFILE(const zSTRING& path); // construct a file with specified path to a file		
	virtual ~zFILE();			// destruct the file (will close it if still open)

//*********************************************************
// Setting ...
//*********************************************************
	
	// getting and setting some flags for various modes (for use in derived classes)
	virtual void SetMode(long modeflags) = 0;
	virtual long GetMode() = 0;
	
	///
	// Manipulating the file-path
	///

	// setting a (new) path to a file or directory
	// ! examples: "SAVEGAMES\", "SAVEGAMES\CURRENT\SURFACE.SAV"
	// ! This methods splits the path and stores it in the members drive, directory, filename, extension	
	// ! all not mentioned parts of a path will be set to zero 	
	virtual void SetPath(zSTRING xPath) = 0;			

	// setting the drive of the path
	// ! example: "C", without a colon (":")
	// ! all other parts of the path will be left as they are
	virtual void SetDrive(zSTRING xDrive) = 0;			
	
	// setting the directory  of the path. 
	// ! example "\SAVEGAMES\CURRENT\", last character must be a "\"	
	// ! all other parts of the path will be left as they are
	virtual void SetDir(zSTRING xDir) = 0;

	// setting both, filename and extension
	// ! example: "surface.sav"
	// ! This methods splits the filename and stores filename and extension
	// ! all other parts of the path will be left as they are
	virtual void SetFile(zSTRING xfilename) = 0;		

	// setting the filename-part of the path without its extension (see SetFile)	
	// ! example: "surface"	
	// ! all other parts of the path will be left as they are
	virtual void SetFilename(zSTRING xFilename) = 0;	
	
	// setting the extension-part of the path
	// ! example: "sav"	
	// ! all other parts of the path will be left as they are
	virtual void SetExt(zSTRING xExt) = 0;

	virtual FILE* GetFileHandle() = 0;


//*********************************************************
// ... and Getting
//*********************************************************
	


	// GetFullPath(): retrieving the full path including current virtual directory	and root-directory
	
	// example: if root-directory is "e:\dev\gothic\" 
	// and current virtual directory is "\data\worlds\"
	// and stored path "testlevel\testlevel_mobis.zen"
	// then this method will return "e:\dev\gothic\data\worlds\testlevel\testlevel_mobsi.zen"
	
	// if the current path has a leading slash "\data\textures\test.tga"
	// the current virtual directory will be ignored:
	// result ""e:\dev\gothic\data\textures\test.tga"	
	// Use this for direct access of files. 
	virtual zSTRING GetFullPath() = 0;


	// retrieving the full path stored in here (without root and virtual directory)	
	// example: "\data\textures\test.tga"	
	virtual zSTRING GetPath() = 0;	
		

	// retrieving the directory without filename and drive	
	// example: "c:\windows\system\"
	// Attention: See warning about virtual paths at beginning of this file
	virtual zSTRING GetDirectoryPath() = 0;
	
	///
	// Retriveing single informations from this class
	///
	/// Attention: See warning about virtual paths at beginning of this file

	virtual zSTRING GetDrive() = 0;						// getting the drive ("C")	
	virtual zSTRING GetDir() = 0;						// getting the drive ("\WINDOWS\DESKTOP\")
	virtual zSTRING GetFile() = 0;						// getting the filename with extension ("autoexec.bat")
	virtual zSTRING GetFilename() = 0;					// getting the filename ("autoexec") without extension
	virtual zSTRING GetExt() = 0;						// getting the files extension ("bat")		

//*********************************************************
// directory services
//*********************************************************
	
	// set the current directory as the new directory (filename and extension will be untouched)	
	// returns the new directory 
	virtual zSTRING SetCurrentDir() = 0;				
	
	// change to the stored path (ignoring filename and extension)
	// if parameter physical is set TRUE this metzhod will not change
	// only virtually but physically, too.
	virtual zERROR_ID ChangeDir(bool physical=false)=0;	
	
	// search for a given file (filename and extension)
	// The result will be stored in this file-object.
	virtual zERROR_ID SearchFile(const zSTRING& name, const zSTRING& searchDir, zBOOL rec = TRUE) = 0;	


	// Files and directory-operations (Search, Create,  Move, Delete ...)
	virtual bool FindFirst(const zSTRING& _filter="*.*") = 0;	// start searching for files in the current directory	
	virtual bool FindNext() = 0;

	virtual bool DirCreate() = 0;
	virtual bool DirRemove() = 0;
	virtual bool DirExists() = 0;

	virtual bool FileMove(zSTRING path, bool follow = false) = 0;
	virtual bool FileCopy(zSTRING path, bool follow = false) = 0;

	virtual bool FileMove(zFILE* new_file) = 0;
	virtual bool FileCopy(zFILE* new_file) = 0;
	virtual bool FileDelete() = 0;


//*********************************************************
// file services
//*********************************************************	
	

	// open, create and close ...

	virtual bool		IsOpened() = 0;					// question if the file is opened	
	
	virtual zERROR_ID	Create() = 0;					// create a new file using the stored path	
	virtual zERROR_ID	Create(const zSTRING& s) = 0;	// create a new file using the given path	
	
	virtual zERROR_ID	Open(bool writeMode = false) = 0;				// open an existing file using the stored path	
	virtual zERROR_ID	Open(const zSTRING& s, bool writeMode = false) = 0;	// open an existing file using the given path	
	
	virtual bool		Exists() = 0;					// check if the the stored path points to an existing file	
	virtual bool		Exists(const zSTRING& s) = 0;	// check if the the given path points to an existing file	
	
	virtual zERROR_ID	Close() = 0;					// close the file (no effect if already closed)
	
	// size and cursor-positioning ...

	virtual zERROR_ID	Reset() = 0;					// reset file (file-cursor is set to the beginning of the file)	
	virtual void		Append() = 0;					// sets the cursor to the end of file to append some data	
	virtual long		Size() = 0;						// retrieve the file's size in bytes	
	virtual long		Pos() = 0;						// get the current position of the file-cursor	
	virtual zERROR_ID	Seek(long fpos) = 0;			// set the cursor to the given absolut position	
	virtual bool		Eof() = 0;						// check if the cursor is at the end of the file (no more data can be read)
	
	// file-information ... 

	virtual zERROR_ID	GetStats(zFILE_STATS& stats) = 0;		// retrieve some stasticts of the file
		
	// writing and reading ...

	virtual zERROR_ID	Write(const char *s) = 0;				// write the given string to the file	
	virtual zERROR_ID	Write(const zSTRING &s) = 0;			// write the given string to the file	
	virtual long		Write(const void *scr, long bytes) = 0;	// write the given buffer to the file	

	virtual long		Read (void *scr, long bytes) = 0;		// read [bytes] bytes from the file and store the data in the buffer [scr].	
	virtual zERROR_ID	Read (char *s) = 0;						// read the next line from the file (CR and LF will be truncated)	
	virtual zERROR_ID	Read (zSTRING &s) = 0;					// read the next line from the file (CR and LF will be truncated)	
	virtual zERROR_ID	ReadChar (char& ch) = 0;				// read one character from the file

	// special highlevel-functions
	virtual zSTRING		SeekText(const zSTRING &s) = 0;
	virtual zSTRING		ReadBlock(long pos, long oldlen) = 0;
	virtual zERROR_ID	UpdateBlock(const zSTRING& s, long pos, long oldlen) = 0;
	//virtual zERROR_ID	DeleteBlock(long pos, long len) = 0;

	virtual long int    GetFreeDiskSpace();	
	
	void				SetBuffering(zBOOL bufferOn)	{ buffering=bufferOn; };
	zBOOL				IsBuffering	()					{ return buffering; };
	virtual long		FlushBuffer	() = 0;

protected:		
		
	static void		DirectFileConvert(zSTRING& filename);

	static int		s_numFilesOpen;
	static int		s_maxFilesOpen;

	static zCCriticalSection* s_dirscanCiticalSection;

	static zFILE*	s_virtPath;	
	static zSTRING	s_virtPathString;
	static zSTRING	s_physPathString;
	static zSTRING	s_rootDirString;

	static bool		s_initialized;

	static zCBuffer*	bufferList[zFILE_MAX_OPEN];
	static int			bufferFlag[zFILE_MAX_OPEN];

	bool write;

	// Buffering
	zBOOL				buffering;
	zCBuffer*			buffer;	
	
	zCBuffer*			GetBuffer()		{ return buffer; };

	static zCBuffer*	GetFreeBuffer();
	static void			ReleaseBuffer(zCBuffer* buffer);

private:

	zFILE(zFILE&);
	zFILE& operator=(zFILE&);

};


class zFILE_FILE : public zFILE
///
// comments for methods see base-class!
///
{

public:

	static bool s_initialized;

	static bool InitFileSystem();
	static bool DeinitFileSystem();	

	//** Constructor/Destructor
	
			zFILE_FILE();
			zFILE_FILE(const zSTRING& path);
	virtual ~zFILE_FILE();
	
	virtual void SetMode(long modeflags) { file_mode = modeflags; };
	virtual long GetMode() { return file_mode; }

	//** Path

	virtual void	SetPath(zSTRING xPath);
	virtual void	SetDrive(zSTRING xDrive);
	virtual void	SetDir(zSTRING xDir);
	virtual void	SetFilename(zSTRING xFilename);
	virtual void	SetExt(zSTRING xExt);
	virtual void	SetFile(zSTRING xfilename);
		
	virtual FILE* GetFileHandle() { return file_handle; };

	virtual zSTRING	GetFullPath();
	virtual zSTRING	GetPath() { return complete_path; };
	virtual zSTRING	GetDirectoryPath() { return complete_directory; };
	virtual zSTRING	GetDrive() { return drive; }
	virtual zSTRING	GetDir() { return dir; }
	virtual zSTRING	GetFilename() { return filename; }	
	virtual zSTRING	GetFile() { return filename+"."+ext; }	
	virtual zSTRING	GetExt() { return ext; }

	virtual zSTRING		SetCurrentDir();   // set this path to the current dir (filenames will be lost)
	virtual zERROR_ID	ChangeDir(bool physical = false);		// change to the directory stored in this class (changes drive, too)	
	virtual zERROR_ID	SearchFile(const zSTRING& name, const zSTRING& searchDir, zBOOL rec = TRUE);

	//** File

	virtual bool		IsOpened() {  return (file_handle!=0); };

	virtual zERROR_ID	Create();						// Create or Clear File	
	virtual zERROR_ID	Open(bool writeMode = false);					// Explizit Open
	virtual bool		Exists();						// File Exists ?

	virtual zERROR_ID	Create(const zSTRING& s) { SetPath(s);return Create(); };
	virtual zERROR_ID	Open(const zSTRING& s, bool writeMode = false)	 { SetPath(s);return Open(writeMode); };
	virtual bool		Exists(const zSTRING& s) { SetPath(s);return Exists(); };

	virtual zERROR_ID	Close();					// Explizit Close
	virtual zERROR_ID	Reset();					// Seek to Filestart
	virtual long		Size();						// Length of file in bytes
	virtual long		Pos();						// Position in File
	virtual void		Append();					// Goto End of File	
	virtual bool		Eof();						// End of File reached ?
	virtual zERROR_ID	Seek(long fpos);			// seek Position in File

	virtual zERROR_ID	GetStats(zFILE_STATS& stats);	

	//** Write Data
	virtual zERROR_ID	Write (const char *s);	
	virtual zERROR_ID	Write (const zSTRING &s);
	virtual long		Write (const void *scr, long bytes);

	virtual long		FlushBuffer();

	//** Read Data
	virtual long		Read (void *scr, long bytes);
	virtual zERROR_ID	Read (char *s);
	virtual zERROR_ID	Read (zSTRING &s);		
	virtual zERROR_ID	ReadChar (char& ch);
	virtual zERROR_ID	ReadCodeline(zSTRING &s);				// Read String and cut REMS	
	virtual zERROR_ID	ReadLines(zSTRING& str, long lines);
	
	//** Extended Read
	virtual zSTRING		SeekText(const zSTRING &s);
	
	virtual zSTRING		ReadBlock(long pos, long oldlen);

	virtual zERROR_ID	UpdateBlock(const zSTRING& s, long pos, long oldlen);
	//virtual zERROR_ID	DeleteBlock(long pos, long len);	

	virtual bool		FindFirst(const zSTRING& _filter="*.*");
	virtual bool		FindNext();	

	virtual bool		DirCreate();
	virtual bool		DirRemove();
	virtual bool		DirExists();
	virtual zSTRING		DirStepInto(zSTRING dirname);

	virtual bool		FileMove(zSTRING path, bool follow = false);
	virtual bool		FileCopy(zSTRING path, bool follow = false);

	virtual bool		FileMove(zFILE* new_file);
	virtual bool		FileCopy(zFILE* new_file);

	virtual bool		FileDelete();

protected:
	
	// not allowed constructor and operator
	zFILE_FILE(zFILE_FILE&);
	zFILE_FILE& operator=(zFILE_FILE&);	

	zERROR_ID	HandleError(const zSTRING& where, const zSTRING& filename,zERROR_TYPE type = zERR_TYPE_FAULT);

	void		Init (const zSTRING& s);		
	
	zSTRING&	SlashConvert(zSTRING& s);
	void		SetCompletePath();	
	
private:

	zSTRING		dir;
	zSTRING		drive;
	zSTRING		filename;
	zSTRING		ext;
	zSTRING		complete_path;					// complete path of the file
	zSTRING		complete_directory;				// complete directory of the file

	zERROR_ID	error;
	FILE*		file_handle;					// File Handle;	
	long		file_mode;

	_finddata_t	find_fileinfo;
	long		find_handle;

};





///
// This class existis only for backward-compatibility
// Use zFILE_FILE instead
///
class zPATH
{	

public:
	enum zCOLLECT_MODE { CURRENT_ONLY, RECURSIVE };


public:	
	
	zPATH();				
	zPATH(zSTRING s);
	virtual ~zPATH()				{ delete path; path=0;  };	
	
	zSTRING GetDirectoryPath()		{ return path->GetDirectoryPath(); };
	zSTRING GetPath()				{ return path->GetPath(); };
	zSTRING GetDrive()				{ return path->GetDrive(); };
	zSTRING GetDir()				{ return path->GetDir(); };
	zSTRING GetFilename()			{ return path->GetFilename(); }	
	zSTRING GetFile()				{ return path->GetFile(); }	
	zSTRING GetExt()				{ return path->GetExt(); }	

	void SetPath(zSTRING s)			{ path->SetPath(s); };	
	void SetDrive(zSTRING s)		{ path->SetDrive(s); };	
	void SetDir(zSTRING s)			{ path->SetDir(s); };	
	void SetFilename(zSTRING s)		{ path->SetFilename(s); }
	void SetExt(zSTRING s)		    { path->SetExt(s); }
	void SetFile(zSTRING s)			{ path->SetFile(s); }
	

	// these methods will delete filename and extension-informations:	

	zSTRING		SetCurrentDir()			{ return path->SetCurrentDir(); };
	zERROR_ID	ChangeDir(bool physical = false)	{ return path->ChangeDir(physical); }
	zERROR_ID	SearchFile(const zSTRING& s, const zSTRING& searchDir, zBOOL rec = TRUE){ return path->SearchFile(s, searchDir, rec); };	

	// GUI
	zERROR_ID Dialog(char* filter);	

protected:
	
	zPATH(zPATH&);	
	zPATH& operator=(zPATH&);

private:
	zFILE* path;

};


extern void Dir_Clear	(const zSTRING &dir, const zSTRING& mask="*.*");
extern void Dir_Copy	(const zSTRING &source, const zSTRING &target);



#endif

