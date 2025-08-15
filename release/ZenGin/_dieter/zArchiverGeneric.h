/******************************************************************************** 
 
     $Workfile:: zArchiverGeneric.h   $                $Date:: 15.03.01 18:52   $
     $Revision:: 6                    $             $Modtime:: 15.03.01 16:21   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Archiver implementation (OOP persistance system)
   created       : 1.4.99

 * $Log: /current_work/ZenGin/_Dieter/zArchiverGeneric.h $
 * 
 * 6     15.03.01 18:52 Hildebrandt
 * 
 * 5     8.02.01 1:32 Hildebrandt
 * 
 * 4     15.01.01 19:07 Hildebrandt
 * added public zCObject* GetParentObject()
 * 
 * 3     4.12.00 17:18 Hildebrandt
 * 
 * 2     21.08.00 17:18 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author Author: Hildebrandt 
/// @version $Revision: 6 $ ($Modtime: 15.03.01 16:21 $)

#ifndef __ZARCHIVER_GENERIC_H__
#define __ZARCHIVER_GENERIC_H__

#ifndef __ZARCHIVER_H__
#include <zArchiver.h>
#endif

#ifndef __ZSPARSEARRAY_H__
#include <zSparseArray.h>
#endif

// ===============================================================================================================
// zCArchiverGeneric
// common archiver implementation
// ===============================================================================================================

class zENGINE_API zCArchiverGeneric : public zCArchiver {
	zCLASS_DECLARATION	(zCArchiverGeneric)
public:
	zCArchiverGeneric();
	virtual ~zCArchiverGeneric();

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
	zBOOL		InBinaryMode		() const				{ return (mode==zARC_MODE_BINARY) || (mode==zARC_MODE_BINARY_SAFE);	  };

	//
	zCObject*	zCCFASTCALL		GetParentObject		();

	//typedef void (zTTestClassCallback)	(zCObject *object, int currentCtr, zCClassDef *classDef, int& numLoops);
	static void TestClassIntegrity		(zTTestClassCallback *callback=0);

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
	zCArchiverGeneric (const zCArchiver&);				// disabled
	zCArchiverGeneric& operator=(const zCArchiver&);	// disabled

	void		DebugMessage		(const zSTRING& m);

	zFILE*						file;
	zCBuffer*					cbuffer;
	zBOOL						owningMedium;
	zBOOL						inSaveGame;
	zBOOL						binaryMode;
	zTAccessMode				accessMode;
	zCArray<zTChunkRecord>		chunkStack;
	zCArray<zCObject*>			objectList;
	zDWORD						posNumObjects;
	zDWORD						posChecksum;
	zDWORD						posHeaderEnd;
	zBOOL						checksumEnabled;
//	zBOOL						headerExists;
//	zCChecksum					generalClassVersion;
	int							flags;
	zBOOL						debugMessagesOn;
	zBOOL						noReadSearchCycles;		// don't go back to beginning of chunk, if entry/chunk is not found
	zSTRING						tmpResultValue;
	zBOOL						deleteFileOnClose;

	//
	struct zTWriteObjectEntry {
		zCObject	*object;		// key
		int			objectIndex;
	};
	zCSparseArray<zCObject*,zTWriteObjectEntry>	writeObjectList;	// used for writing archives, efficient dataStructure for retrieving a written object's objectIndex, if there is any (in order to resolve refs to already written objects)

	//
	zBOOL						warnEntrysNotRead;		// debug-flags for "TestClassIntegrity", never cleared, only set in ascii/read
	zBOOL						warnEntryNotFound;
	zBOOL						warnWrongEntryOrder;

	//
	void						CheckObjectListSize		(int numRequired);
};

#endif