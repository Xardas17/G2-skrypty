/******************************************************************************** 
 
     $Workfile:: zArchiver2.h          $                $Date:: 24.04.01 17:33   $
     $Revision:: 8                    $             $Modtime:: 22.04.01 15:55   $
       $Author:: Edenfeld                                                   $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Archiver (persistance system)
   created       : 2.7.00

 * $Log: /current_work/ZenGin/_Dieter/zArchiver2.h $
 * 
 * 8     24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 7     8.02.01 1:32 Hildebrandt
 * 
 * 6     15.01.01 19:07 Hildebrandt
 * added public zCObject* GetParentObject()
 * 
 * 5     4.12.00 17:18 Hildebrandt
 * 
 * 4     9.11.00 14:53 Hoeller
 * 
 * 3     20.10.00 18:43 Hoeller
 * 
 * 2     4.10.00 19:41 Hildebrandt
 * 
 * 1     15.09.00 16:03 Hoeller
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 8 $ ($Modtime: 22.04.01 15:55 $)

#ifndef __ZARCHIVER2_H__
#define __ZARCHIVER2_H__


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

#ifndef __ZARCHIVER_H__
#include <zArchiver.h>
#endif


enum zTArchiveTypeID
{
	zARC2_ID_STRING		= 0x1,
	zARC2_ID_INTEGER	= 0x2,
	zARC2_ID_FLOAT		= 0x3,
	zARC2_ID_HASH		= 0x12,
	zARC2_ID_BYTE		= 0x4,
	zARC2_ID_WORD		= 0x5,
	zARC2_ID_BOOL		= 0x6,
	zARC2_ID_VEC3		= 0x7,
	zARC2_ID_COLOR		= 0x8,
	zARC2_ID_RAW		= 0x9,
	zARC2_ID_RAWFLOAT	= 0x10,
	zARC2_ID_ENUM		= 0x11,
	//zARC2_ID_GROUPBEGIN = 0x1000,
	//zARC2_ID_GROUPEND	= 0x2000
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ABSTRACT BASE CLASS
class zCBuffer;			// <zBuffer.h>
class zCObject;			// <zObject.h>
class zCClassDef;
class zCArc2Section;

class zENGINE_API zCArchiverBinSafe : public zCArchiver {
	zCLASS_DECLARATION	(zCArchiverBinSafe)
public:
	zCArchiverBinSafe();
	virtual ~zCArchiverBinSafe();

	// "entryName"s are type-sensitive
	// Writing
	void		zCCFASTCALL		WriteInt			(const char* entryName, const int		value);
	void		zCCFASTCALL		WriteByte			(const char* entryName, const zBYTE		value);
	void		zCCFASTCALL		WriteWord			(const char* entryName, const zWORD		value);
	void		zCCFASTCALL		WriteFloat			(const char* entryName, const float		value);
	void		zCCFASTCALL		WriteBool			(const char* entryName, const zBOOL		value);
	void		zCCFASTCALL		WriteString			(const char* entryName, const zSTRING&	value);
	void		zCCFASTCALL		WriteVec3			(const char* entryName, const zVEC3&	value);
	void		zCCFASTCALL		WriteColor			(const char* entryName, const zCOLOR&	value);
	void		zCCFASTCALL		WriteRaw			(const char* entryName, void* buffer, const zDWORD size);
	void		zCCFASTCALL		WriteRawFloat		(const char* entryName, void* buffer, const zDWORD size);
	void		zCCFASTCALL		WriteEnum			(const char* entryName, const char* enumChoices, const int value);	// enumChoices: e.g. "NONE;YAW;FULL"
	void		zCCFASTCALL		WriteObject			(zCObject* object);								// UNSAFE ; NULL-PTRs are allowed, the same object ist written only once
	void		zCCFASTCALL		WriteObject			(const char* chunkName, zCObject* object);		// SAFE ; "
	void		zCCFASTCALL		WriteChunkStart		(const char* chunkName, zWORD chunkVersion=0);	// for explicit data-chunks (these have no corresponding classes!); recursion allowed
	void		zCCFASTCALL		WriteChunkEnd		();
	void		zCCFASTCALL		WriteGroupBegin		(const char* groupName);		// only for zARC_MODE_ASCII_PROPS, these are never read
	void		zCCFASTCALL		WriteGroupEnd		(const char* groupName);
									
	// Reading						

	// Safe Reading
	// (does not destroy existant value, if entry is not present)
	void		zCCFASTCALL		ReadInt				(const char* entryName, int&		value);
	void		zCCFASTCALL		ReadByte			(const char* entryName, zBYTE&		value);
	void		zCCFASTCALL		ReadWord			(const char* entryName, zWORD&		value);
	void		zCCFASTCALL		ReadFloat			(const char* entryName, float&		value);
	void		zCCFASTCALL		ReadBool			(const char* entryName, zBOOL&		value);
	void		zCCFASTCALL		ReadString			(const char* entryName, zSTRING&	value);
	void		zCCFASTCALL		ReadVec3			(const char* entryName, zVEC3&		value);
	void		zCCFASTCALL		ReadColor			(const char* entryName, zCOLOR&		value);
	void		zCCFASTCALL		ReadEnum			(const char* entryName, int&		value);
	void		zCCFASTCALL		ReadRaw				(const char* entryName, void* buffer, const zDWORD size);
	void		zCCFASTCALL		ReadRawFloat		(const char* entryName, void* buffer, const zDWORD size);
	zCObject*	zCCFASTCALL		ReadObject			(zCObject* objectUseThis=0);						// if 'objectUseThis!=0' fill this object, else: create new object; result can be NULL-PTR / UNSAFE
	zCObject*	zCCFASTCALL		ReadObject			(const char* chunkName, zCObject* objectUseThis=0);	// -""- SAFE
																						// searches for next object chunk with matching label 'chunkName' / SAFE
	zBOOL		zCCFASTCALL		ReadChunkStart		(zSTRING& chunkName, zWORD& chunkVersion);			// open next available chunk, return info about that (does not change chunk-level)
	zBOOL		zCCFASTCALL		ReadChunkStartNamed (const char* chunkName, zWORD& chunkVersion);		// open next chunk with specified name
	void		zCCFASTCALL		SkipOpenChunk		() { SkipChunk(TRUE); };
	zWORD		zCCFASTCALL		GetCurrentChunkVersion();												// to query class archive version within Archive()/Unarchive()

	// Unsafe/easy Reading						
	int			zCCFASTCALL		ReadInt				(const char* entryName);
	zBYTE		zCCFASTCALL		ReadByte			(const char* entryName);
	zWORD		zCCFASTCALL		ReadWord			(const char* entryName);
	float		zCCFASTCALL		ReadFloat			(const char* entryName);
	zBOOL		zCCFASTCALL		ReadBool			(const char* entryName);
	zSTRING		zCCFASTCALL		ReadString			(const char* entryName);
	zVEC3		zCCFASTCALL		ReadVec3			(const char* entryName);
	zCOLOR		zCCFASTCALL		ReadColor			(const char* entryName);
	int			zCCFASTCALL		ReadEnum			(const char* entryName);

	// contents can only be accessed while not closed								
	zFILE*		GetFile				() const				{ return file; };			// dirty access
	void		zCCFASTCALL		GetBufferString		(zSTRING& result);									// returns the archiver's contents as a string (assert: using buffer & ASCII-Mode)
	zCBuffer*	zCCFASTCALL		GetBuffer			();													// dirty access
	zBOOL		zCCFASTCALL		EndOfArchive		();

	//
	void		Close				();
									
	// misc
	void		SetStringEOL		(const zSTRING& eol)	{ stringEOL = eol;			};
	zSTRING		GetStringEOL		() const				{ return stringEOL;			};
	zBOOL		IsStringValid		(const char* string);	// valid string for entryName / entryValue ?
	zBOOL		GetChecksumEnabled	() const				{ return checksumEnabled;	};
	void		SetChecksumEnabled	(const zBOOL b)			{ checksumEnabled = b;		};
	void		SetNoReadSearchCycles(const zBOOL b)		{ noReadSearchCycles = b;	};
	zBOOL		InProperties		() const				{ return mode==zARC_MODE_ASCII_PROPS; };
	zBOOL		InSaveGame			() const				{ return inSaveGame; };					
	zBOOL		InBinaryMode		() const				{ return TRUE;	  };	// dieser Archiver ist IMMER binary
//	zBOOL		InBinaryMode		() const				{ return (mode==zARC_MODE_BINARY) || (mode==zARC_MODE_BINARY_SAFE);	  };

	// should only be called within zCObject::Archive()/Unarchive(), returns ptr to parent object, can return 0
	zCObject*	zCCFASTCALL		GetParentObject		();

protected:

	// Writing
	zBOOL						OpenWriteBuffer		(zCBuffer*		buffer   , zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0, zBOOL arcOwnsMedium=FALSE);
	void						OpenWriteFile		(zFILE*			fileWrite, zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0, zBOOL arcOwnsMedium=FALSE);

	void		zCCFASTCALL		WriteChunkStart		(const char* chunkName, const char* className, zWORD classVersion, zDWORD objectIndex);
	void		zCCFASTCALL		WriteObject			(const char* chunkName, zCObject& object);
	void		zCCFASTCALL		WriteHeader			(const int arcFlags=0);
	void		zCCFASTCALL		WriteHeaderNumObj	();
	void		zCCFASTCALL		WriteASCIILine		(const char* entryName, const char* typeName, const zSTRING& value);
	void		zCCFASTCALL		StoreBuffer			(void* buffer, const zDWORD size);
	void		zCCFASTCALL		StoreString			(const char* string);
	void		zCCFASTCALL		StoreStringEOL		(const char* string);
	zDWORD		zCCFASTCALL		StoreGetPos			();
	void		zCCFASTCALL		StoreSeek			(const zDWORD newPos);

	// Reading
	zBOOL						OpenReadBuffer		(zCBuffer&		buffer	, zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0);
	void						OpenReadFile		(zFILE*			fileRead, zTArchiveMode arcMode, zBOOL saveGame=FALSE, int arcFlags=0, zBOOL deleteFileOnClose=FALSE);

	zCClassDef* zCCFASTCALL		GetClassDefByString (const zSTRING& className);
	zCObject*	zCCFASTCALL		CreateObject		(const zSTRING& className);
	void		zCCFASTCALL		SkipChunk			(const zBOOL removeFromChunkStack);
	zBOOL		zCCFASTCALL		ReadChunkStart		(const char* chunkName);							// opened named chunk is now on chunkStack
	void		zCCFASTCALL		ReadChunkStartASCII (const char* chunkName, zSTRING& resultLine);	// searches for specific named chunk
	void		zCCFASTCALL		ReadChunkEnd		();
	zBOOL		zCCFASTCALL		ReadEntryASCII		(const char* entryName, zSTRING& resultValue);
	void		zCCFASTCALL		ReadHeader			();
	void		zCCFASTCALL		RestoreBuffer		(void* buffer, const zDWORD size);
	void		zCCFASTCALL		RestoreStringEOL	(zSTRING& string);
	void		zCCFASTCALL		RestoreString0		(zSTRING& string);
	zDWORD		zCCFASTCALL		RestoreGetPos		();
	void		zCCFASTCALL		RestoreSeek			(const zDWORD newPos);

	void		zCCFASTCALL		DeleteBuffer		();

private:
	zCArchiverBinSafe (const zCArchiver&);				// disabled
	zCArchiverBinSafe& operator=(const zCArchiver&);	// disabled

	void		DebugMessage		(const zSTRING& m);

	zFILE*						file;
	zCBuffer*					cbuffer;
	zBOOL						owningMedium;
	zBOOL						inSaveGame;
	zTAccessMode				accessMode;
	zCArray<zTChunkRecord>		chunkStack;
	zCArray<zCObject*>			objectList;
	zDWORD						posNumObjects;
	zDWORD						posChecksum;
	zDWORD						posHeaderEnd;
	zBOOL						checksumEnabled;
	int							flags;
	zBOOL						debugMessagesOn;
	zBOOL						noReadSearchCycles;		// don't go back to beginning of chunk, if entry/chunk is not found
	zSTRING						tmpResultValue;
	zBOOL						deleteFileOnClose;

	//
	zBOOL						warnEntrysNotRead;		// debug-flags for "TestClassIntegrity", never cleared, only set in ascii/read
	zBOOL						warnEntryNotFound;
	zBOOL						warnWrongEntryOrder;
	void*						stringHashMap;
	zDWORD						dummyVal;
	zDWORD						posChunkList;

	enum						{ READ_BUFFER_SIZE = 1024*8 };
	char						m_readTextBuffer[READ_BUFFER_SIZE];

	//
	void						CheckObjectListSize		(int numRequired);

	void		zCCFASTCALL		RestoreString(zSTRING &string);
	void		zCCFASTCALL		WriteType(zTArchiveTypeID archiveTypeID, void* ptr, zDWORD size);
	zBOOL		zCCFASTCALL		ReadType(zTArchiveTypeID archiveTypeID, void* ptr, zDWORD size);
	void		zCCFASTCALL		ClearChunkList();
	zDWORD		zCCFASTCALL		InsertChunkInList(const char* entryName);
	zDWORD		zCCFASTCALL		ResolveAndPosEntry(const char* entryName);
};
#endif