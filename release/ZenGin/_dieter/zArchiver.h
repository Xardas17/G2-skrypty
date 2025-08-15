/******************************************************************************** 
 
     $Workfile:: zArchiver.h          $                $Date:: 8.02.01 1:32     $
     $Revision:: 13                   $             $Modtime:: 7.02.01 22:49    $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Archiver (OOP persistance system)
   created       : 1.4.99

 * $Log: /current_work/zengin_work/_Dieter/zArchiver.h $
 * 
 * 13    8.02.01 1:32 Hildebrandt
 * 
 * 12    7.02.01 10:36 Moos
 * 
 * 11    15.01.01 19:07 Hildebrandt
 * added public zCObject* GetParentObject()
 * 
 * 10    4.12.00 17:49 Hildebrandt
 * 
 * 9     4.12.00 17:18 Hildebrandt
 * 
 * 8     22.08.00 15:18 Hildebrandt
 * 
 * 7     21.08.00 17:18 Hildebrandt
 * 
 * 6     16.08.00 21:41 Hoeller
 * 
 * 5     3.08.00 13:23 Hoeller
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 9     22.03.00 2:58 Hildebrandt
 * zenGin 088a
 * 
 * 8     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 6     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 5     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Hildebrandt 
/// @version $Revision: 13 $ ($Modtime: 7.02.01 22:49 $)

 
#ifndef __ZARCHIVER_H__
#define __ZARCHIVER_H__

#ifndef __ZSTRING_H__
#include <zString.h>
#endif

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

#ifndef __ZTYPES3D_H__
#include <zTypes3D.h>
#endif

#ifndef __ZALGEBRA_H__
#include <zAlgebra.h>
#endif

#ifndef __ZCONTAINER_H__
#include <zContainer.h>
#endif

#ifndef __ZOBJECT_H__
#include <zObject.h>
#endif

class zCBuffer;			// <zBuffer.h>
class zCObject;			// <zObject.h>
class zCClassDef;

class zCArchiver;

// ===============================================================================================================
// zCArchiverFactory
// (this class is REENTRANT/multithreading safe!)
// ===============================================================================================================

enum zTArchiveMode		{ zARC_MODE_BINARY,						// supported by zCArchiverGeneric
						  zARC_MODE_ASCII,						// supported by zCArchiverGeneric
						  zARC_MODE_ASCII_PROPS,				// supported by zCArchiverGeneric
						  zARC_MODE_BINARY_SAFE,				// supported by zCArchiverBinSafe

						  zARC_MODE_COUNT,
						};
enum zTArchiveFlags		{ zARC_FLAG_WRITE_BRIEF_HEADER	=	1,	// keeps archive header short (only neccessary infos)
						  zARC_FLAG_NO_SPY_MESSAGES		=   2	// silent, absolutely no spy output
						};

class zCArchiverFactory {
	// ATTENTION: no data members are allowed here (reentrant static global object)!
public:
	// Note: CreateArchiverXXX() can fail and return 0, if e.g. file cannot be opened
	// Note: CreateArchiverXXX() creates an archiver object and opens the created archive at the same time

	// Read
	virtual zCArchiver*		CreateArchiverRead		(zCBuffer*		buffer		, int arcFlags=0);
	virtual zCArchiver*		CreateArchiverRead		(zFILE*			fileRead	, int arcFlags=0);
	virtual zCArchiver*		CreateArchiverRead		(const zSTRING&	fileNameRead, int arcFlags=0);

	// Write
	virtual zCArchiver*		CreateArchiverWrite		(zCBuffer*		buffer		, zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0);
	virtual zCArchiver*		CreateArchiverWrite		(							  zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0);	// convenience, transient buffer created within archiver, for access must be readOut before archive is closed
	virtual zCArchiver*		CreateArchiverWrite		(zFILE*			fileWrite	, zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0);
	virtual zCArchiver*		CreateArchiverWrite		(const zSTRING&	fileNameWrite,zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0);

private:
	zCArchiver*				CreateArchiverFromMode	(zTArchiveMode arcMode);
	void					WriteLine				(const zSTRING& line, zCBuffer* buffer, zFILE* file);
	void					WriteLine				(const char* const line, zCBuffer* buffer, zFILE* file);
	void					WriteHeader				(zCArchiver *arc, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags, zCBuffer* buffer, zFILE* file);

	zBOOL					EndOfArchive			(zCBuffer* buffer, zFILE* file);
	void					ReadLine				(zSTRING& line, zCBuffer* buffer, zFILE* file);
	void					ReadLineArg				(zSTRING& line, zSTRING& arg, zCBuffer* buffer, zFILE* file);
	void					ReadHeader				(int			arcFlags,	// in
													 zCBuffer*		buffer,		// in
													 zFILE*			file,		// in
													 zCArchiver*	&arc,		// out
													 zTArchiveMode	&arcMode,	// out
													 zBOOL			&inSaveGame	// out	
													 );
};

extern zCArchiverFactory zarcFactory;

// ===============================================================================================================
// zCArchiver
// abstract base class / interface
// ===============================================================================================================

class zENGINE_API zCArchiver : public zCObject {
	zCLASS_DECLARATION	(zCArchiver)
public:
	zCArchiver() {};
	virtual ~zCArchiver() {};

	enum		zTArchiveMedium		{ zARC_MEDIUM_FILE, 
									  zARC_MEDIUM_BUFFER 
									};
	// Writing
	virtual void		zCCFASTCALL		WriteInt			(const char* entryName, const int		value)=0;
	virtual void		zCCFASTCALL		WriteByte			(const char* entryName, const zBYTE		value)=0;
	virtual void		zCCFASTCALL		WriteWord			(const char* entryName, const zWORD		value)=0;
	virtual void		zCCFASTCALL		WriteFloat			(const char* entryName, const float		value)=0;
	virtual void		zCCFASTCALL		WriteBool			(const char* entryName, const zBOOL		value)=0;
	virtual void		zCCFASTCALL		WriteString			(const char* entryName, const zSTRING&	value)=0;
	virtual void		zCCFASTCALL		WriteVec3			(const char* entryName, const zVEC3&	value)=0;
	virtual void		zCCFASTCALL		WriteColor			(const char* entryName, const zCOLOR&	value)=0;
	virtual void		zCCFASTCALL		WriteRaw			(const char* entryName, void* buffer, const zDWORD size)=0;
	virtual void		zCCFASTCALL		WriteRawFloat		(const char* entryName, void* buffer, const zDWORD size)=0;
	virtual void		zCCFASTCALL		WriteEnum			(const char* entryName, const char* enumChoices, const int value)=0;	// enumChoices: e.g. "NONE;YAW;FULL"
	virtual void		zCCFASTCALL		WriteObject			(zCObject* object)=0;								// UNSAFE ; NULL-PTRs are allowed, the same object ist written only once
	virtual void		zCCFASTCALL		WriteObject			(const char* chunkName, zCObject* object)=0;		// SAFE ; "
	virtual void		zCCFASTCALL		WriteChunkStart		(const char* chunkName, zWORD chunkVersion=0)=0;	// for explicit data-chunks (these have no corresponding classes!); recursion allowed
	virtual void		zCCFASTCALL		WriteChunkEnd		()=0;
	virtual void		zCCFASTCALL		WriteGroupBegin		(const char* groupName)=0;		// only for zARC_MODE_ASCII_PROPS, these are never read
	virtual void		zCCFASTCALL		WriteGroupEnd		(const char* groupName)=0;

	// Reading						

	// Safe Reading
	// (does not destroy existant value, if entry is not present)
	virtual void		zCCFASTCALL		ReadInt				(const char* entryName, int&		value)=0;
	virtual void		zCCFASTCALL		ReadByte			(const char* entryName, zBYTE&		value)=0;
	virtual void		zCCFASTCALL		ReadWord			(const char* entryName, zWORD&		value)=0;
	virtual void		zCCFASTCALL		ReadFloat			(const char* entryName, float&		value)=0;
	virtual void		zCCFASTCALL		ReadBool			(const char* entryName, zBOOL&		value)=0;
	virtual void		zCCFASTCALL		ReadString			(const char* entryName, zSTRING&	value)=0;
	virtual void		zCCFASTCALL		ReadVec3			(const char* entryName, zVEC3&		value)=0;
	virtual void		zCCFASTCALL		ReadColor			(const char* entryName, zCOLOR&		value)=0;
	virtual void		zCCFASTCALL		ReadEnum			(const char* entryName, int&		value)=0;
	virtual void		zCCFASTCALL		ReadRaw				(const char* entryName, void* buffer, const zDWORD size)=0;
	virtual void		zCCFASTCALL		ReadRawFloat		(const char* entryName, void* buffer, const zDWORD size)=0;

	virtual zCObject*	zCCFASTCALL		ReadObject			(zCObject* objectUseThis=0)=0;						// if 'objectUseThis!=0' fill this object, else: create new object; result can be NULL-PTR / UNSAFE
	virtual zCObject*	zCCFASTCALL		ReadObject			(const char* chunkName, zCObject* objectUseThis=0)=0;	// -""- SAFE

	virtual zCObject*	zCCFASTCALL		ReadObjectAccount	(const char *file, int line, zCObject* objectUseThis=0); // if 'objectUseThis!=0' fill this object, else: create new object; result can be NULL-PTR / UNSAFE
	virtual zCObject*	zCCFASTCALL		ReadObjectAccount	(const char *file, int line, const char* chunkName, zCObject* objectUseThis=0);	 // -""- SAFE

																						// searches for next object chunk with matching label 'chunkName' / SAFE
	virtual	zBOOL		zCCFASTCALL		ReadChunkStart		(zSTRING& chunkName, zWORD& chunkVersion)=0;			// open next available chunk, return info about that (does not change chunk-level)
	virtual zBOOL		zCCFASTCALL		ReadChunkStartNamed (const char* chunkName, zWORD& chunkVersion)=0;		// open next chunk with specified name
	virtual void		zCCFASTCALL		SkipOpenChunk		()=0;
	virtual zWORD		zCCFASTCALL		GetCurrentChunkVersion()=0;												// to query class archive version within Archive()/Unarchive()

	// Unsafe/easy Reading						
	virtual int			zCCFASTCALL		ReadInt				(const char* entryName)=0;
	virtual zBYTE		zCCFASTCALL		ReadByte			(const char* entryName)=0;
	virtual zWORD		zCCFASTCALL		ReadWord			(const char* entryName)=0;
	virtual float		zCCFASTCALL		ReadFloat			(const char* entryName)=0;
	virtual zBOOL		zCCFASTCALL		ReadBool			(const char* entryName)=0;
	virtual zSTRING		zCCFASTCALL		ReadString			(const char* entryName)=0;
	virtual zVEC3		zCCFASTCALL		ReadVec3			(const char* entryName)=0;
	virtual zCOLOR		zCCFASTCALL		ReadColor			(const char* entryName)=0;
	virtual int			zCCFASTCALL		ReadEnum			(const char* entryName)=0;

	// contents can only be accessed while not closed								
	virtual zFILE*		GetFile				() const=0;												// dirty access
	virtual void		zCCFASTCALL		GetBufferString		(zSTRING& result)=0;									// returns the archiver's contents as a string (assert: using buffer & ASCII-Mode)
	virtual zCBuffer*	zCCFASTCALL		GetBuffer			()=0;													// dirty access
	virtual zBOOL		zCCFASTCALL		EndOfArchive		()=0;

	//
	virtual void		Close				()=0;
									
	// misc
	virtual void		SetStringEOL		(const zSTRING& eol)=0;
	virtual zSTRING		GetStringEOL		() const=0;
	virtual zBOOL		IsStringValid		(const char* string)=0;	// valid string for entryName / entryValue ?
	virtual zBOOL		GetChecksumEnabled	() const=0;
	virtual void		SetChecksumEnabled	(const zBOOL b)=0;
	virtual void		SetNoReadSearchCycles(const zBOOL b)=0;
	virtual zBOOL		InProperties		() const=0;
	virtual zBOOL		InSaveGame			() const=0;
	virtual zBOOL		InBinaryMode		() const=0; 

	// should only be called within zCObject::Archive()/Unarchive(), returns ptr to parent object, can return 0
	virtual zCObject*	zCCFASTCALL		GetParentObject		()=0;

	typedef void (zTTestClassCallback)	(zCObject *object, int currentCtr, zCClassDef *classDef, int& numLoops);

protected:
	struct zTChunkRecord {
		zDWORD					startPos;		// writing
		zDWORD					size;			// reading
		zWORD					version;
		zDWORD					objectIndex;
		zSTRING					name;		
		zSTRING					className;
	};

	enum zTAccessMode 			{ zARC_CLOSED, zARC_READ, zARC_WRITE };

	//////////////////////////////////////////////////////////////////////////////////////////
	zTArchiveMedium				medium;
	zTArchiveMode				mode;
	//////////////////////////////////////////////////////////////////////////////////////////
	// static functions and vars
	static zSTRING		stringEOL;

	// Writing
	virtual zBOOL						OpenWriteBuffer		(zCBuffer*		buffer   , zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0, zBOOL arcOwnsMedium=FALSE)=0; // if arcOwnsMedium==TRUE then the medium will be deleted when the archive is closed
	virtual void						OpenWriteFile		(zFILE*			fileWrite, zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0, zBOOL arcOwnsMedium=FALSE)=0;

	virtual void		zCCFASTCALL		WriteChunkStart		(const char* chunkName, const char* className, zWORD classVersion, zDWORD objectIndex)=0;
	virtual void		zCCFASTCALL		WriteObject			(const char* chunkName, zCObject& object)=0;
	virtual void		zCCFASTCALL		WriteHeader			(const int arcFlags=0)=0;
	virtual void		zCCFASTCALL		WriteHeaderNumObj	()=0;
	virtual void		zCCFASTCALL		WriteASCIILine		(const char* entryName, const char* typeName, const zSTRING& value)=0;
	virtual void		zCCFASTCALL		StoreBuffer			(void* buffer, const zDWORD size)=0;
	virtual void		zCCFASTCALL		StoreString			(const char* string)=0;
	virtual void		zCCFASTCALL		StoreStringEOL		(const char* string)=0;
	virtual zDWORD		zCCFASTCALL		StoreGetPos			()=0;
	virtual void		zCCFASTCALL		StoreSeek			(const zDWORD newPos)=0;

	// Reading
	virtual	zBOOL						OpenReadBuffer		(zCBuffer&		buffer	, zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0)=0;
	virtual void						OpenReadFile		(zFILE*			fileRead, zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0, zBOOL deleteFileOnClose=FALSE)=0;

	virtual zCClassDef* zCCFASTCALL		GetClassDefByString (const zSTRING& className)=0;
	virtual zCObject*	zCCFASTCALL		CreateObject		(const zSTRING& className)=0;
	virtual void		zCCFASTCALL		SkipChunk			(const zBOOL removeFromChunkStack)=0;
	virtual zBOOL		zCCFASTCALL		ReadChunkStart		(const char* chunkName)=0;							// opened named chunk is now on chunkStack
	virtual void		zCCFASTCALL		ReadChunkStartASCII (const char* chunkName, zSTRING& resultLine)=0;	// searches for specific named chunk
	virtual void		zCCFASTCALL		ReadChunkEnd		()=0;
	virtual zBOOL		zCCFASTCALL		ReadEntryASCII		(const char* entryName, zSTRING& resultValue)=0;
	virtual void		zCCFASTCALL		ReadHeader			()=0;
	virtual void		zCCFASTCALL		RestoreBuffer		(void* buffer, const zDWORD size)=0;
	virtual void		zCCFASTCALL		RestoreStringEOL	(zSTRING& string)=0;
	virtual void		zCCFASTCALL		RestoreString0		(zSTRING& string)=0;
	virtual zDWORD		zCCFASTCALL		RestoreGetPos		()=0;
	virtual void		zCCFASTCALL		RestoreSeek			(const zDWORD newPos)=0;

	virtual void		zCCFASTCALL		DeleteBuffer		()=0;

	friend zCArchiverFactory;
};

// ===============================================================================================================

#endif