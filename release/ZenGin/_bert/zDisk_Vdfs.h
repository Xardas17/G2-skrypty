/******************************************************************************** 
 
     $Workfile:: Zdisk_vdfs.h          $               $Date:: 6.02.01 17:09    $
     $Revision:: 12                    $            $Modtime:: 6.02.01 15:56    $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   File-Interface using the Virtual Disc File System (VDFS), read-only
 
 * $Log: /current_work/ZenGin/_Bert/Zdisk_vdfs.h $
 * 
 * 12    6.02.01 17:09 Speckels
 * 
 * 11    28.01.01 18:47 Speckels
 * 
 * 10    4.12.00 18:22 Moos
 * 
 * 9     3.11.00 15:04 Speckels
 * 
 * 8     28.08.00 14:24 Speckels
 * 
 * 17    23.08.00 21:47 Admin
 * 
 * 6     21.08.00 18:26 Speckels
 * 
 * 15    16.08.00 12:32 Admin
 * 
 * 5     10.08.00 21:47 Speckels
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     21.07.00 12:56 Speckels
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 5     4.05.00 17:54 Speckels
 * 
 * 4     4.05.00 17:38 Speckels
 * CriticalSection fuer DirectoryScans
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 6     17.04.00 17:13 Speckels
 * 
 * 4     27.03.00 21:46 Speckels
 * 
 * 1     7.02.00 12:02 Speckels
 * 
 * 7     2.12.99 22:49 Speckels
 * VDFS-Update November 1999
 * 
 * 6     21.10.99 23:29 Speckels
 * Work on error-handling and
 * item-interaction
 * 
 * 5     25.09.99 18:11 Speckels
 * 
 * 4     24.09.99 20:40 Speckels
 * VSS-kompatiblen Header eingefügt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 12 $ ($Modtime: 6.02.01 15:56 $)


#ifdef _VDFS

#ifndef __ZDISK_VDFS_H__
#define __ZDISK_VDFS_H__

#ifndef __ZDISK_H__
#include <zdisk.h>
#endif

#include <vdfs32g.h>

class zCCriticalSection;

class zFILE_VDFS : public zFILE_FILE
{

public:

	static bool					s_vdfsInitialized;
	// [BENDLIN] AddonMOD
	static bool					s_physical_first;

	static zCCriticalSection*	s_criticalSection;

	static bool InitFileSystem();
	static bool DeinitFileSystem();	

	static bool LockCriticalSection();
	static bool UnlockCriticalSection();

	//** Constructor/Destructor
	
	zFILE_VDFS();
	zFILE_VDFS(const zSTRING& path);
	virtual ~zFILE_VDFS();
	
	// void Backup(zPATH path, long amount = 5);
	
	//** Path
	
	virtual zSTRING		SetCurrentDir();   // set this path to the current dir (filenames will be lost)
	virtual zERROR_ID	ChangeDir(bool physical = false);		// change to the directory stored in this class (changes drive, too)	
	
	virtual zERROR_ID	SearchFile(const zSTRING& name, const zSTRING& searchDir, zBOOL rec=TRUE);

	//** File

	virtual zERROR_ID	Open(bool write = false);					// Explizit Open
	virtual bool		Exists();						// File Exists ?

	virtual zERROR_ID	Open(const zSTRING& s, bool write = false)	 { SetPath(s);return Open(write); };
	virtual bool		Exists(const zSTRING& s) { SetPath(s);return Exists(); };

	virtual zERROR_ID	Close();					// Explizit Close
	virtual zERROR_ID	Reset();					// Seek to Filestart
	virtual long		Size();						// Length of file in bytes
	virtual long		Pos();							// Position in File
	virtual void		Append();						// Goto End of File	
	virtual bool		Eof();							// End of File reached ?
	virtual zERROR_ID	Seek(long fpos);				// seek Position in File
	virtual zSTRING		SeekText(const zSTRING &s);

	virtual zERROR_ID	GetStats(zFILE_STATS& stats);	
	virtual zSTRING		GetFullPath();

	//** Read Data
	virtual long		Read (void *scr, long bytes);	
	virtual zERROR_ID	Read (char *s);
	virtual zERROR_ID	Read (zSTRING &s);		
	
	virtual bool		IsOpened();

	virtual bool		FindFirst(const zSTRING& _filter="*.*");
	virtual bool		FindNext();

protected:

	zERROR_ID HandleError(const zSTRING& where, const zSTRING& filename,zERROR_TYPE level = zERR_TYPE_FAULT);
	void Init (const zSTRING& s);		

private:

	char			read_buffer[1024*10];
	
	TVDFFINDDATA	find_filedata; 
	
	long		vdfHandle;
	long		vdfResult;
	bool		vdfEOF;	

	long		vdfFindHandle;
	zSTRING		vdfFindExt;

	zERROR_ID	error;

	#ifdef _DEBUG
	zBOOL		found_virtual;
	#endif
};





#endif

#endif