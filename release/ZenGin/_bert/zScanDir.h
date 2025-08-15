
/******************************************************************************** 
 
     $Workfile:: zscandir.h           $                $Date:: 31.01.01 3:12    $
     $Revision:: 12                   $             $Modtime:: 31.01.01 3:11    $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:

   Register FileHandler to your scandir-object and call zCScanDir::Scan(directory)
   to scan all the files in the specified directory and its subdirectorys. 

   A FileHandler is an instance of zCScanDirFileHandler and registers some 
   Filetypes in its constructor i.e. RegisterFileType(".tga").

   zCScanDir::Scan(directory) will call zCScanDirFileHandler::HandleFile for every
   file it finds that matches your registered filetypes. Its parameters are
   the filename (in uppercase!) and the fileinfo-structure. 

   You can add messages about what you have done or what has to be said aboud the 
   file using the methods AddMessage(zSTRING).

   Return TRUE in zCScanDirFileHandler::HandleFile if you touched the file, 
   otherwise return FALSE.

 * $Log: /current_work/ZenGin/_Bert/zscandir.h $
 * 
 * 12    31.01.01 3:12 Speckels
 * 
 * 11    31.01.01 3:07 Speckels
 * 
 * 10    31.01.01 1:25 Speckels
 * 
 * 9     31.01.01 0:50 Speckels
 * 
 * 8     4.12.00 18:22 Moos
 * 
 * 7     28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 5     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 4     10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 3     21.07.00 12:56 Speckels
 * 
 * 2     5.05.00 13:46 Speckels
 * 
 * 3     4.05.00 23:11 Edenfeld
 * Release 0.79b
 * 
 * 1     4.05.00 13:36 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 12 $ ($Modtime: 31.01.01 3:11 $)


#ifndef __ZSCANDIR_H__
#define __ZSCANDIR_H__

#ifndef __ZTYPES_H__
#include "ztypes.h"
#endif

#ifndef __ZSTRING_H__
#include "zstring.h"
#endif

#ifndef __ZCONTAINER_H__
#include "zcontainer.h"
#endif

#ifndef __ZDISK_H__
#include "zdisk.h"
#endif

class zFILE;

class zCScanDirFileHandler
{
public: // overwritables

	zCScanDirFileHandler();
	virtual ~zCScanDirFileHandler();

	//
	// to be called by the filecheck-tool:
	//

	// clear all messages
	void	ClearMessages();

	// checking, if the class can handle this specified filetype
	zBOOL	CanHandleFile(zSTRING& filename);	
	
	// overwrite it to handle your own filetypes.
	virtual zBOOL HandleFile(const zSTRING& filename, const char* directory, _finddata_t fileinfo) = 0;

	// setting the name of your FilecheckerCallback
	// will be used by the FileCheckers register-method
	void SetName(const zSTRING& _name);

	zSTRING& GetName();

public: // methods
	
	int		GetNumMessages();
	zSTRING	GetMessage(int nr);

protected: // for internal use	
	
	// register a new filetype
	// call this method in your constructor for every filetype your derived class can handle	
	void	RegisterFileType(zSTRING extension);	

	// if you handle a file and have something to say about it
	// then insert a message for the 'user' with this method.
	void	AddMessage(zSTRING msg);
		

private:
	zCArray<zSTRING> msgList;
	zCArray<zSTRING> extList;
	zSTRING name;
};


///
// FileChecker
// Register different instances of FileCheckerCallbacks here
// and call CheckFiles() from the root-directory.
///
class zCScanDir
{
	zCList<zCScanDirFileHandler> cbList;
public:
	zCScanDir();
	virtual ~zCScanDir();

	virtual void RegisterFileHandler(zCScanDirFileHandler* callback, const zSTRING& name="");
	virtual void Scan(const zSTRING& rootDir);

private:
	void ScanX();

	int statFoundFiles;
	int statHandledFiles;
	int statTouchedFiles;
};

extern zCScanDir dirScanner;



#endif
