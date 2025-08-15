/******************************************************************************** 
 
     $Workfile:: zArchiver2.cpp        $                $Date:: 22.05.01 18:45   $
     $Revision:: 32                   $             $Modtime:: 30.05.01 0:07    $
       $Author:: Edenfeld                                                   $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Archiver (persistance system)
   created       : 2.7.00

 * $Log: /current_work/ZenGin/_Dieter/zArchiver2.cpp $
 * 
 * 32    22.05.01 18:45 Edenfeld
 * 
 * 30    14.02.01 20:58 Hildebrandt
 * 
 * 29    14.02.01 20:57 Hildebrandt
 * fixed load saveGame crash (falsely opening unnamed chunk)
 * 
 * 28    14.02.01 2:41 Hildebrandt
 * 
 * 27    8.02.01 14:53 Moos
 * 
 * 26    7.02.01 18:33 Moos
 * 
 * 25    6.02.01 17:56 Moos
 * 
 * 24    6.02.01 12:40 Moos
 * 
 * 23    5.02.01 18:01 Moos
 * 
 * 22    30.01.01 15:36 Moos
 * 
 * 21    25.01.01 13:21 Moos
 * 
 * 20    25.01.01 12:14 Moos
 * 
 * 19    24.01.01 1:14 Hildebrandt
 * unbenutzten statischen 5k Buffer entfernt
 * 
 * 18    22.01.01 21:37 Speckels
 * 
 * 17    18.01.01 17:53 Speckels
 * 
 * 16    18.01.01 14:27 Speckels
 * 
 * 15    17.01.01 20:24 Speckels
 * 
 * 14    16.01.01 16:35 Hildebrandt
 * 
 * 13    15.01.01 20:56 Hildebrandt
 * fixed static memory overrun (upped bufferSize, added asserts)
 * 
 * 12    15.01.01 19:07 Hildebrandt
 * added public zCObject* GetParentObject()
 * 
 * 11    16.11.00 16:23 Hoeller
 * 
 * 10    9.11.00 20:07 Hoeller
 * 
 * 9     9.11.00 14:53 Hoeller
 * 
 * 8     7.11.00 15:40 Speckels
 * 
 * 7     26.10.00 21:31 Speckels
 * 
 * 6     24.10.00 20:18 Speckels
 * 
 * 5     20.10.00 18:43 Hoeller
 * 
 * 4     28.09.00 18:14 Hoeller
 * 
 * 3     21.09.00 0:36 Hildebrandt
 * 
 * 2     19.09.00 17:56 Hoeller
 * 
 * 1     15.09.00 16:03 Hoeller
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 32 $ ($Modtime: 30.05.01 0:07 $)

#include <zCore.h>
#include <zArchiver2.h>

#include <zArchiver.h>
#include <zDisk.h>
#include <zoption.h>
#include <zObject.h>
#include <zBuffer.h>
#include <zAccount.h>

#include <windows.h>
#include <tchar.h>
#include <CrtDbg.h>

#include <zArchive2container.h>

zCLASS_DEFINITION		( zCArchiverBinSafe	, zCArchiver, 0,	0	)


////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
// ENGINE MODULE
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

static const zSTRING SEPARATE_STRING_BRACKET_LEFT	(" ["); 
static const zSTRING SEPARATE_STRING_BRACKET_RIGHT	(" ]"); 

#pragma pack(push, 1)
struct zTArc2TypeChunk
{
protected:
	zBYTE				archiveTypeID;
	//int					nextTypePos;
public:
	void				zCCFASTCALL	Write(zCBuffer *buffer) {buffer->Write(this, sizeof(zTArc2TypeChunk));}
	void				zCCFASTCALL	Write(zFILE *file) {file->Write(this, sizeof(zTArc2TypeChunk));}
	void				zCCFASTCALL	Read(zCBuffer *buffer) {buffer->Read(this, sizeof(zTArc2TypeChunk));}
	void				zCCFASTCALL	Read(zFILE *file) {file->Read(this, sizeof(zTArc2TypeChunk));}
	zBYTE				zCCFASTCALL	GetTypeID() {return archiveTypeID;}
	void				zCCFASTCALL	SetTypeID(zBYTE typeID) {archiveTypeID = typeID;}
};
// default pragma pack
#pragma pack(pop)


////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
struct zCArc2SectionItem
{
protected:
	int			absFilePosition;
	GEU32		linearValue;
public:
	void				zCCFASTCALL	Write(zCBuffer *buffer) {buffer->Write(this, sizeof(zCArc2SectionItem));}
	void				zCCFASTCALL	Write(zFILE *file) {file->Write(this, sizeof(zCArc2SectionItem));}
	void				zCCFASTCALL	Read(zCBuffer *buffer) {buffer->Read(this, sizeof(zCArc2SectionItem));}
	void				zCCFASTCALL	Read(zFILE *file) {file->Read(this, sizeof(zCArc2SectionItem));}
	int					zCCFASTCALL	GetAbsFilePosition() {return absFilePosition;}
	zDWORD				zCCFASTCALL	GetLinearValue() {return linearValue;}
	void				zCCFASTCALL	SetAbsFilePosition(int filePos) {absFilePosition = filePos;}
	void				zCCFASTCALL	SetLinearValue(GEU32 lValue) {linearValue = lValue;}
};

class zCArc2Section
{
protected:
	struct	zTArc2Numeric
	{
		int				absFilePosition;
		int				chunkLength;
		int				version;
		int				index;
	};
	GECString*									chunkName;
	GECString*									className;
	zTArc2Numeric								Data;
	GETSmallArrayNative<zCArc2SectionItem>*		items;
	GETSmallArrayNative<zCArc2Section*>*		subSections;
	zCArc2Section*								Parent;
	zCArc2Section*								Root;
	int											Index;
public:
	/////////////////////////////////////////////////////////////////////
	zCArc2Section()
	{
		chunkName = NULL;
		className = NULL;
		Data.absFilePosition = -1;
		Data.index = -1;
		Data.version = 0;
		Data.chunkLength = 0;
		items = NULL;
		subSections = NULL;
		Parent = NULL;
		Root = this;
		Index = -1;
	}

	~zCArc2Section()
	{
		delete chunkName;
		delete className;
		chunkName = NULL;
		className = NULL;
		ClearItems();
		ClearSubSections();
		delete items;
		items = NULL;
		delete subSections;
		subSections = NULL;
		Parent = NULL;
	}
	/////////////////////////////////////////////////////////////////////

	void				zCCFASTCALL		ClearItems()
	{
		if(items==NULL) return;
		items->Used = 0;
	}
	// add a new item 
	int					zCCFASTCALL		AddItem(zCArc2SectionItem &item)
	{
		if(items==NULL)
			items = zNEW(GETSmallArrayNative<zCArc2SectionItem>);
		return items->Add(item);
	}
	// delete a subsection
	zBOOL				zCCFASTCALL		DelItem(int index)
	{
		if((index<0)||(index>items->Used)) return FALSE;
		items->Remove(GEU32(index));
		return TRUE;
	}
	zBOOL				zCCFASTCALL		DelItem(zCArc2SectionItem *item)
	{
		GEU32 i = items->Used;
		if(i>0) while(i--)
		{
			if(&items->Entry[i]==item) 
				return DelItem(int(i));
		}
		return FALSE;
	}
	zCArc2SectionItem&	zCCFASTCALL		GetItem(int index) {return items->Entry[GEU32(index)];}	
	zCArc2Section*		zCCFASTCALL		GetSubSection(int index) {return subSections->Entry[GEU32(index)];}
	zCArc2SectionItem*	zCCFASTCALL		LookupLinearValue(GEU32 linearValue)
	{
		if(items==NULL) 
			return NULL;
		GEU32 i = items->Used;
		if(i>0) while(i--)
		{
			if(items->Entry[i].GetLinearValue()==linearValue)
				return &items->Entry[i];
		}
		return NULL;
	}
	/////////////////////////////////////////////////////////////////////
	// clear all subsections
	void	ClearSubSections()
	{
		if(subSections==NULL) return;
		GEU32 i = subSections->Used;
		if(i>0) while(i--)
		{
			delete subSections->Entry[i];
			subSections->Entry[i] = NULL;
		}
		subSections->Used = 0;
	}

	// find a specific subsection in section (chunkname)
	zCArc2Section*	zCCFASTCALL		FindSectionPerChunkName(const char* chunkName, zCArc2Section* lastSubSection=NULL, BOOL firstEntry=TRUE)	
	{
		// search in children
		if((GetChunkName()!=NULL)&&(chunkName!=NULL))
			if(strcmp(chunkName, GetChunkName())==0)
				return this;
		int indexThreshold = 0;

		if(lastSubSection!=NULL)
			if(lastSubSection->Parent==this)
				indexThreshold = lastSubSection->Index + 1; 
		
		for(int i=indexThreshold;i<GetSubSectionCount();i++)
		{
			zCArc2Section* nextSection;
			zCArc2Section* section = GetSubSection(i);
			if(section!=NULL)
			{
				if(chunkName==NULL)
					return section;
				if(chunkName[0]==0)
					return section;
				if(section->GetChunkName()!=NULL)
					if(strcmp(chunkName, section->GetChunkName())==0)
						return section;
				//else
				//	return section;
				nextSection = section->FindSectionPerChunkName(chunkName, NULL, FALSE);
			}
			if(nextSection!=NULL) 
				return nextSection;
		}
		if(IsRoot())
			return NULL;	
		//if(firstEntry==TRUE)
			return Parent->FindSectionPerChunkName(chunkName, this, FALSE);
		//else
		//	return NULL;
	}


	// add a new subsection 
	int				zCCFASTCALL		AddSubSection(zCArc2Section *subSection)
	{
		if(subSections==NULL)
			subSections = zNEW(GETSmallArrayNative<zCArc2Section*>);  
		subSection->Parent = this;
		subSection->Index = subSections->Add(subSection);
		subSection->Root = Root;

		return subSection->Index;
	}
	
	int				zCCFASTCALL		GetSubSectionCount()
	{
		if(subSections==NULL) return 0;
		return subSections->Used;
	}
	/////////////////////////////////////////////////////////////////////
	int				zCCFASTCALL	GetIndex()
	{
		return Index;
	}

	char*			zCCFASTCALL	GetChunkName()
	{
		if(chunkName==NULL) return NULL;
		return chunkName->GetText();
	}

	void			zCCFASTCALL	SetChunkName(char* chunk)
	{
		if(chunk==NULL) return;
		delete chunkName;
		chunkName = zNEW(GECString(chunk));
	}

	char*			zCCFASTCALL	GetClassName()
	{
		if(className==NULL) return NULL;
		return className->GetText();
	}

	void			zCCFASTCALL	SetClassName(char* _className)
	{
		if(_className==NULL) return;
		delete className;
		className = zNEW(GECString(_className));
	}
	zTArc2Numeric&	zCCFASTCALL	GetData() {return Data;}

	zBOOL			zCCFASTCALL	IsRoot() {return (Parent==NULL);}

	zCArc2Section*	zCCFASTCALL	GetParent() {return Parent;}
	/////////////////////////////////////////////////////////////////////
	void			zCCFASTCALL	Write(zCBuffer *buffer)
	{
		// write version flag
		GEU16 ver = 1;
		buffer->Write(&ver, sizeof(GEU16));

		GEU32 temp;
		if(chunkName==NULL)
			temp = 0;
		else
			temp = chunkName->GetLength();
		buffer->Write(&temp, sizeof(GEU32));
		if(temp>0)
			buffer->Write(chunkName->GetText(), temp);
		buffer->Write(&Data, sizeof(zTArc2Numeric));
		
		if(className==NULL)
			temp = 0;
		else
			temp = className->GetLength();
		buffer->Write(&temp, sizeof(GEU32));
		if(temp>0)
			buffer->Write(className->GetText(), temp);
		
		// first write items
		GEU32 cn = 0;
		if(items!=NULL)
			cn = items->Used;

		buffer->Write(&cn, sizeof(GEU32));
		for(GEU32 i = 0;i<cn;i++)
			items->Entry[i].Write(buffer);
		
		// now do an recursive loop of subsections
		cn = 0;
		if(subSections!=NULL)
			cn = subSections->Used;
		buffer->Write(&cn, sizeof(GEU32));
		//if(cn>0) while(cn--)
		for(i = 0;i<cn;i++)
			subSections->Entry[i]->Write(buffer);
	}

	void			zCCFASTCALL		Read(zCBuffer *buffer)
	{
		// write version flag
		
		GEU16 ver;
		buffer->Read(&ver, sizeof(GEU16));
		if(ver!=1)
			zERR_FAULT("oh: zCArc2Section::Read - illegal version detected.");

		GEU32 temp;

 		buffer->Read(&temp, sizeof(GEU32));
		if(temp>0)
		{
			if(chunkName)
				chunkName->Reserve(temp+1);
			else
			{
				chunkName = zNEW(GECString);
				chunkName->Reserve(temp+1);
			}
			buffer->Read(chunkName->GetText(), temp);
			chunkName->GetText()[temp] = 0;
		}
		else
		{
			delete chunkName;
			chunkName = NULL;
		}

		

		buffer->Read(&Data, sizeof(zTArc2Numeric));

		buffer->Read(&temp, sizeof(GEU32));
		if(temp>0)
		{
			if(className)
				className->Reserve(temp+1);
			else
			{
				className = zNEW(GECString);
				className->Reserve(temp+1);
			}
			buffer->Read(className->GetText(), temp);
			className->GetText()[temp] = 0;
		}
		else
		{
			delete className;
			className = NULL;
		}
		
		ClearItems();
		ClearSubSections();
		// first write items
		GEU32 cn;

		buffer->Read(&cn, sizeof(GEU32));
		if(cn>0) 
		{
			/*static*/ zCArc2SectionItem item;
			while (cn--)
			{
				item.Read(buffer);
				AddItem(item);
			}
		};

		// now do an recursive loop of subsections
		buffer->Read(&cn, sizeof(GEU32));
		if(cn>0) while(cn--)
		{
			zCArc2Section *section = zNEW(zCArc2Section);
			AddSubSection(section);
			section->Read(buffer);
		}
	}

	void			zCCFASTCALL	Write(zFILE *buffer)
	{
		// write version flag
		GEU16 ver = 1;
		buffer->Write(&ver, sizeof(GEU16));

		GEU32 temp;
		if(chunkName==NULL)
			temp = 0;
		else
			temp = chunkName->GetLength();
		buffer->Write(&temp, sizeof(GEU32));
		if(temp>0)
			buffer->Write(chunkName->GetText(), temp);
		buffer->Write(&Data, sizeof(zTArc2Numeric));
		
		if(className==NULL)
			temp = 0;
		else
			temp = className->GetLength();
		buffer->Write(&temp, sizeof(GEU32));
		if(temp>0)
			buffer->Write(className->GetText(), temp);
		
		// first write items
		GEU32 cn = 0;
		if(items!=NULL)
			cn = items->Used;

		buffer->Write(&cn, sizeof(GEU32));
		for(GEU32 i = 0;i<cn;i++)
			items->Entry[i].Write(buffer);
		
		// now do an recursive loop of subsections
		cn = 0;
		if(subSections!=NULL)
			cn = subSections->Used;
		buffer->Write(&cn, sizeof(GEU32));
		//if(cn>0) while(cn--)
		for(i = 0;i<cn;i++)
			subSections->Entry[i]->Write(buffer);
	}

	void			zCCFASTCALL		Read(zFILE *buffer)
	{
		// write version flag
		
		GEU16 ver;
		buffer->Read(&ver, sizeof(GEU16));
		if(ver!=1)
			zERR_FAULT("oh: zCArc2Section::Read - illegal version detected.");

		GEU32 temp;

 		buffer->Read(&temp, sizeof(GEU32));
		if(temp>0)
		{
			if(chunkName)
				chunkName->Reserve(temp+1);
			else
			{
				chunkName = zNEW(GECString);
				chunkName->Reserve(temp+1);
			}
			buffer->Read(chunkName->GetText(), temp);
			chunkName->GetText()[temp] = 0;
		}
		else
		{
			delete chunkName;
			chunkName = NULL;
		}
		
		buffer->Read(&Data, sizeof(zTArc2Numeric));

		buffer->Read(&temp, sizeof(GEU32));
		if(temp>0)
		{
			if(className)
				className->Reserve(temp+1);
			else
			{
				className = zNEW(GECString);
				className->Reserve(temp+1);
			}
			buffer->Read(className->GetText(), temp);
			className->GetText()[temp] = 0;
		}
		else
		{
			delete className;
			className = NULL;
		}
		
		ClearItems();
		ClearSubSections();
		// first write items
		GEU32 cn;

		buffer->Read(&cn, sizeof(GEU32));
		if(cn>0) 
		{
			/*static*/ zCArc2SectionItem item;
			while(cn--)
			{
				item.Read	(buffer);
				AddItem		(item);
			}
		};

		// now do an recursive loop of subsections
		buffer->Read(&cn, sizeof(GEU32));
		if(cn>0) while(cn--)
		{
			zCArc2Section *section = zNEW(zCArc2Section);
			AddSubSection(section);
			section->Read(buffer);
		}
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void zCArchiverBinSafe::RestoreString(zSTRING &string)
{
	assert (accessMode==zARC_READ);
	ReadType(zARC2_ID_STRING, &string, 0);
}

void zCArchiverBinSafe::WriteType(zTArchiveTypeID archiveTypeID, void* ptr, zDWORD size)
{
	zERR_ASSERT (accessMode==zARC_WRITE);

	zTArc2TypeChunk		typeChunk;
	typeChunk.SetTypeID	(archiveTypeID);
	StoreBuffer			((void*)&typeChunk, sizeof(zTArc2TypeChunk));

	zWORD sWord;
	switch (archiveTypeID)
	{
		case zARC2_ID_STRING:
			sWord = (zWORD)size;
			StoreBuffer(&sWord, sizeof(zWORD));
			StoreBuffer(ptr, size);
			break;
			// do default
		case zARC2_ID_RAW:
			sWord = (zWORD)size;
			StoreBuffer(&sWord, sizeof(zWORD));
			StoreBuffer(ptr, size);
			break;
		case zARC2_ID_RAWFLOAT:
			sWord = (zWORD)size;
			StoreBuffer(&sWord, sizeof(zWORD));
			StoreBuffer(ptr, size);
			break;
		default:
			StoreBuffer(ptr, size);
			break;
	};
}

zBOOL	zCArchiverBinSafe::ReadType(zTArchiveTypeID archiveTypeID, void* ptr, zDWORD size)
{
	zERR_ASSERT (accessMode==zARC_READ);

	zTArc2TypeChunk		typeChunk;
	RestoreBuffer		((void*)&typeChunk, sizeof(zTArc2TypeChunk));

	if (typeChunk.GetTypeID()!=archiveTypeID)
	{
		// zERR_WARNING("B: ARC2: zCArchiverBinSafe::ReadType: illegal archiveType here. Entry ignored");

		zWORD  sSize;
		switch (typeChunk.GetTypeID())
		{
			case zARC2_ID_STRING:						
				RestoreBuffer		(&sSize, sizeof(zWORD));
				zERR_ASSERT_STRICT	(sSize<READ_BUFFER_SIZE);
				RestoreBuffer		(m_readTextBuffer, sSize);
				m_readTextBuffer	[sSize] = 0;
				break;
			case zARC2_ID_HASH:
				zDWORD dummyVal;
				RestoreBuffer		(&dummyVal, sizeof(zDWORD));
				break;
			case zARC2_ID_RAW:
				RestoreBuffer		(&sSize, sizeof(zWORD));
				zERR_ASSERT_STRICT	(sSize<READ_BUFFER_SIZE);
				RestoreBuffer		(m_readTextBuffer, sSize);
				break;
			case zARC2_ID_RAWFLOAT:
				RestoreBuffer		(&sSize, sizeof(zWORD));
				zERR_ASSERT_STRICT	(sSize<READ_BUFFER_SIZE);
				RestoreBuffer		(m_readTextBuffer, sSize);
				break;
			case zARC2_ID_INTEGER:
				RestoreBuffer		(&m_readTextBuffer, sizeof(int));
				break;				
			case zARC2_ID_FLOAT:	
				RestoreBuffer		(&m_readTextBuffer, sizeof(float));
				break;				
			case zARC2_ID_BYTE:		
				RestoreBuffer		(&m_readTextBuffer, sizeof(zBYTE));
				break;				
			case zARC2_ID_WORD:		
				RestoreBuffer		(&m_readTextBuffer, sizeof(zWORD));
				break;				
			case zARC2_ID_BOOL:		
				RestoreBuffer		(&m_readTextBuffer, sizeof(zBOOL));
				break;				
			case zARC2_ID_VEC3:		
				RestoreBuffer		(&m_readTextBuffer, sizeof(zVEC3));
				break;				
			case zARC2_ID_COLOR:	
				RestoreBuffer		(&m_readTextBuffer, sizeof(zCOLOR));
				break;				
			case zARC2_ID_ENUM:		
				RestoreBuffer		(&m_readTextBuffer, sizeof(int));
				break;
		};
		return FALSE;
	}

	switch (archiveTypeID)
	{
		case zARC2_ID_STRING:
			{
			// assert(_CrtCheckMemory());
			zSTRING				*str;
			zWORD				sSize;		
			RestoreBuffer		(&sSize, sizeof(zWORD));
			
			// zERR_MESSAGE(7,0,"B: ARC2: Read String: size "+zSTRING(sSize));

			zERR_ASSERT_STRICT	(sSize<READ_BUFFER_SIZE);
			if (sSize>0)		RestoreBuffer(m_readTextBuffer, sSize); // [SPECKELS] 0-read abfangen		
			m_readTextBuffer	[sSize] = 0;
			str					= (zSTRING*) ptr;
			*str				= m_readTextBuffer;
			};
			break;
			// do default
		case zARC2_ID_RAW:
			zWORD				sSize;		
			RestoreBuffer		(&sSize, sizeof(zWORD));
			zERR_ASSERT_STRICT	(sSize<READ_BUFFER_SIZE);
			RestoreBuffer		(ptr, sSize);
			break;
		case zARC2_ID_RAWFLOAT:
			RestoreBuffer		(&sSize, sizeof(zWORD));
			zERR_ASSERT_STRICT	(sSize<READ_BUFFER_SIZE);
			RestoreBuffer		(ptr, sSize);
			break;
		default:		
			RestoreBuffer		(ptr, size);		
			break;
	};
	return TRUE;
}

void	zCArchiverBinSafe::ClearChunkList()
{
	GETStringMap<GEU32>* hashMap = (GETStringMap<GEU32>*) stringHashMap;
	hashMap->RemoveAll(GEFalse);		
	delete hashMap;
}

zDWORD	zCArchiverBinSafe::InsertChunkInList(const char* entryName)
{
	GETStringMap<GEU32>* hashMap = (GETStringMap<GEU32>*) stringHashMap;
	GEU32 *dVal;
	GEU32 linearVal = hashMap->Lookup(entryName, dVal);
	if(linearVal!=0xffffffff)
		return (zDWORD)linearVal;
	// insert only a dummy value
	linearVal = hashMap->SetAt((GELPChar)entryName, &dummyVal);
	return (zDWORD)linearVal;
}

zDWORD	zCArchiverBinSafe::ResolveAndPosEntry(const char* entryName)
{
	//if(currentSection==NULL) 
	//	return FALSE;
	// search for linearvalue
	GETStringMap<GEU32>* hashMap = (GETStringMap<GEU32>*) stringHashMap;
	GEU32* ptrDummyVal = &dummyVal;
	GEU32 linearValue = hashMap->Lookup(entryName, ptrDummyVal);
	//zCArc2SectionItem *item = currentSection->LookupLinearValue(linearValue);
	//if(item==NULL)
	//	return 0xffffffff;
	// @TODO: -> set here absolute seekvalue -> must be optimized !!!!
	//RestoreSeek(item->GetAbsFilePosition());
	return linearValue;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////


static const zSTRING s_arcModeNames[zARC_MODE_COUNT] = 
{
	zSTRING("BINARY"),
	zSTRING("ASCII"),
	zSTRING("ASCII_PROPS"),
	zSTRING("BIN_SAFE")
};

////////////////////////////////////
//	COMMON
////////////////////////////////////

zCArchiverBinSafe::zCArchiverBinSafe() {
	file				= 0;
	cbuffer				= 0;
	owningMedium		= FALSE;
	medium				= zARC_MEDIUM_FILE;
	mode				= zARC_MODE_BINARY;
	inSaveGame			= FALSE;
	accessMode			= zARC_CLOSED;
	posNumObjects		= 0;
	posChecksum			= 0;
	posHeaderEnd		= 0;
	checksumEnabled		= FALSE;
	flags				= 0;
	debugMessagesOn		= TRUE;
	warnEntrysNotRead	= FALSE;
	warnEntryNotFound	= FALSE;
	warnWrongEntryOrder	= FALSE;

	GETStringMap<GEU32>* hashMap = NULL;
	// dummy template value
	hashMap = zNEW(GETStringMap<GEU32>);
	// dirty typecast
	stringHashMap = (void*) hashMap;
	//
	SetNoReadSearchCycles	(FALSE);
};

zCArchiverBinSafe::~zCArchiverBinSafe	() 
{
	ClearChunkList();
	Close		();
	file		= 0;
	cbuffer		= 0;
};

void zCArchiverBinSafe::DebugMessage (const zSTRING& m) 
{
	if (!debugMessagesOn)					return;
	if (flags & zARC_FLAG_NO_SPY_MESSAGES)	return;
	zerr.Message (m);
};

void zCArchiverBinSafe::WriteHeaderNumObj () 
{
	if (accessMode!=zARC_WRITE) return;

	if ((medium==zARC_MEDIUM_FILE) && (!file->IsOpened())) return;

	zDWORD oldPos =	 StoreGetPos();
	StoreSeek		(posNumObjects);
	int objNum = objectList.GetNum();
	
	StoreBuffer(&objNum, sizeof(int));
	StoreSeek		(oldPos);

};

void zCArchiverBinSafe::Close () 
{
	if (accessMode==zARC_CLOSED) return;

	// hat Archive einen eigenen Header ?	(FIXME: dirty Abfrage..)
	// Read/Write spezifisches
	if (accessMode==zARC_WRITE) 
	{
		zDWORD oldPos =	 StoreGetPos();
	
		StoreSeek		(posChunkList);
		// store now chunklistposition
		StoreBuffer(&oldPos, sizeof(zDWORD));
		// restore old position
		StoreSeek		(oldPos);
		// next: chunklist itself

		GETStringMap<GEU32>* hashMap = (GETStringMap<GEU32>*) stringHashMap;
		GECString hashStr;
		GEU32 linearValue;
		GEU32 *dVal;
		GEU32 nHash;
		GEU32 nCount = hashMap->GetCount();
		StoreBuffer(&nCount, sizeof(GEU32));
		GESStringMapStorage strMapStorage;
		if(hashMap->GetFirstElement(linearValue, hashStr, dVal, nHash)==GETrue)
		{
			do
			{
				// first write linear value
				strMapStorage.HashMapStringLen = (GEU16)hashStr.GetLength();
				strMapStorage.LinearValue = (GEU16)linearValue;
				strMapStorage.HashValue = nHash;
				StoreBuffer(&strMapStorage, sizeof(GESStringMapStorage));
				StoreBuffer(hashStr.GetText(), strMapStorage.HashMapStringLen);
		
			}
			while(hashMap->GetNextElement(linearValue, hashStr, dVal, nHash));
		}

		//oldPos =	 StoreGetPos();
		WriteHeaderNumObj();

		hashMap->RemoveAll();	
	}

	// Medium schliessen
	if (owningMedium) 
	{
		//
		DebugMessage ("D: ARC: .. Closing ("+zSTRING(objectList.GetNum())+" objects)");

		//
		if (medium==zARC_MEDIUM_FILE) 
		{
			if (file) 
			{
				if (file->IsOpened()) file->Close();
				if (owningMedium)	delete file;	file=0;
			}
		} 
		else 
		{
			DeleteBuffer();
		}
	}

	// cleanup
    for (int i = objectList.GetNumInList()-1; i>=0; i--)
        zRELEASE_NOACCT(objectList[i]);

	objectList.EmptyList();
	chunkStack.EmptyList();
	file			= 0;
	cbuffer			= 0;
	accessMode		= zARC_CLOSED;
};

zBOOL zCArchiverBinSafe::EndOfArchive () {
	// FIXME: hack
	if (medium==zARC_MEDIUM_FILE)	return file->Eof() || file->Pos()+3>file->Size();
	else							return (int(cbuffer->GetSize()) - int(cbuffer->GetPos()))<0;
};

void zCArchiverBinSafe::DeleteBuffer () {
	if (owningMedium) delete cbuffer;
	cbuffer = 0;
};

void zCArchiverBinSafe::GetBufferString (zSTRING& result) {
	result.Clear(); 
	if (!cbuffer) return;

	// nur im ASCII-Mode sinnvoll
	if (mode==zARC_MODE_BINARY) return;

	// den Header gueltig machen (im Laufenden Betrieb, vor dem ::Close())
	WriteHeaderNumObj();

	//
	cbuffer->Write			("\0", 1);
	cbuffer->SetPosBegin	();
	result = zSTRING((char*)cbuffer->GetCursor());
};

zCBuffer* zCArchiverBinSafe::GetBuffer () {
	// den Header gueltig machen (im Laufenden Betrieb, vor dem ::Close())
	WriteHeaderNumObj();

	return cbuffer;
};

// =======================================================================================================================

////////////////////////////////////
//	WRITE:	medium dependent
////////////////////////////////////
zBOOL zCArchiverBinSafe::OpenWriteBuffer (zCBuffer* buffer, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags, zBOOL arcOwnsMedium)
{
	zERR_ASSERT (buffer);
	Close();

	this->medium		= zARC_MEDIUM_BUFFER;
	this->mode			= arcMode;
	this->inSaveGame	= saveGame;
	this->accessMode	= zARC_WRITE;
	this->owningMedium	= arcOwnsMedium;
	this->flags			= arcFlags;
	this->debugMessagesOn= (mode!=zARC_MODE_ASCII_PROPS);
	this->cbuffer		= buffer;

	cbuffer->SetMode	(WRITE);
	
	//
	DebugMessage		("D: ARC: Writing archive buffer ("+zSTRING(s_arcModeNames[arcMode])+") ..");
	
	//
	WriteHeader			(arcFlags);
	return TRUE;
};

void zCArchiverBinSafe::OpenWriteFile (zFILE* fileWrite, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags, zBOOL arcOwnsMedium) {
	if (!fileWrite) return;
	Close();

	this->medium			= zARC_MEDIUM_FILE;
	this->mode				= arcMode;
	this->inSaveGame		= saveGame;
	this->accessMode		= zARC_WRITE;
	this->owningMedium		= arcOwnsMedium;
	this->file				= fileWrite;
	this->flags				= arcFlags;
	this->debugMessagesOn	= (mode!=zARC_MODE_ASCII_PROPS);

	//
	WriteHeader			(arcFlags);
};

void zCArchiverBinSafe::StoreBuffer (void* buffer, const zDWORD size) 
{
	zERR_ASSERT (accessMode==zARC_WRITE);
	if (size<=0) return;
	if (medium==zARC_MEDIUM_FILE)	file->Write		(buffer, size);
	else							cbuffer->Write	(buffer, size);
};

void zCArchiverBinSafe::StoreString (const char* string) 
{
	zERR_ASSERT (accessMode==zARC_WRITE);
	// schreibt KEINE Null am Ende !!
	const int strLen = strlen(string);
	if (strLen<=0) return;

	WriteType(zARC2_ID_STRING, (void*)string, strLen);
	//if (medium==zARC_MEDIUM_FILE)	file->Write(string, strLen);
	//else							cbuffer->Write((void*)string, strLen);
};

zDWORD zCArchiverBinSafe::StoreGetPos () 
{
	zERR_ASSERT (accessMode==zARC_WRITE);
	if (medium==zARC_MEDIUM_FILE)	return file->Pos();
	else							return cbuffer->GetPos();
};

void zCArchiverBinSafe::StoreSeek (const zDWORD newPos) 
{
	zERR_ASSERT (accessMode==zARC_WRITE);
	if (medium==zARC_MEDIUM_FILE)	file->Seek		(newPos);
	else							cbuffer->SetPos	(newPos);
};

void zCArchiverBinSafe::StoreStringEOL (const char* string) {
	assert (accessMode==zARC_WRITE);
	StoreString		(string);
	//StoreString		(stringEOL.ToChar());
};

// ========================================================================

////////////////////////////////////
//	WRITE:	high level
////////////////////////////////////

void zCArchiverBinSafe::WriteHeader (const int arcFlags) 
{
	int ver = 2;
	StoreBuffer(&ver, sizeof(int));

	posNumObjects	= StoreGetPos();

	int objCount = 0;
	
	StoreBuffer(&objCount, sizeof(int));

	// #2: chunklist
	posChunkList	= StoreGetPos();
	StoreBuffer(&objCount, sizeof(int));

	posHeaderEnd	= StoreGetPos();
};

zBOOL zCArchiverBinSafe::IsStringValid (const char* string) 
{
	// valid string for entryName / entryValue ?
	const char* ptr = string;
	while (*ptr) {
		if (
//			(*ptr==sep0[0]) || 
//			(*ptr==sep1[0]) ||		// FIXME: beisst sich zur Zeit leider mit den MatNames: "P:_ARENA" !!!!
			(*ptr=='%') ||
			(*ptr=='§') ||
			(*ptr=='[') ||
			(*ptr==']')
			) return FALSE;
		ptr++;
	};
	return TRUE;
};


void zCArchiverBinSafe::WriteASCIILine (const char* entryName, const char* typeName, const zSTRING& value) 
{
	if (!IsStringValid (entryName) ) 
	{
		zERR_FAULT("D: zArchiver(zCArchiverBinSafe::WriteASCIILine): string contains illegal characters: \""+
			zSTRING(entryName)+" / "+value);
	};
	
	zDWORD mapValue = InsertChunkInList(entryName);
	if(mapValue==0xffffffff) return;
	WriteType(zTArchiveTypeID(zARC2_ID_HASH), (void*)&mapValue, sizeof(int));
};

void zCArchiverBinSafe::WriteInt (const char* entryName, const int value) 
{
	WriteASCIILine	(entryName, "int", "");
	WriteType(zTArchiveTypeID(zARC2_ID_INTEGER), (void*)&value, sizeof(int));
};

void zCArchiverBinSafe::WriteByte (const char* entryName, const zBYTE value) 
{
	WriteASCIILine	(entryName, "int", "");
	WriteType(zTArchiveTypeID(zARC2_ID_BYTE), (void*)&value, sizeof(zBYTE));
};

void zCArchiverBinSafe::WriteWord (const char* entryName, const zWORD value) 
{
	WriteASCIILine	(entryName, "int", "");
	WriteType(zTArchiveTypeID(zARC2_ID_WORD), (void*)&value, sizeof(zWORD));
};

void zCArchiverBinSafe::WriteFloat (const char* entryName, const float value) 
{
	WriteASCIILine	(entryName, "float", "");
	WriteType(zTArchiveTypeID(zARC2_ID_FLOAT), (void*)&value, sizeof(float));
};

void zCArchiverBinSafe::WriteBool (const char* entryName, const zBOOL value) 
{
	WriteASCIILine	(entryName, "bool", "");
	WriteType(zTArchiveTypeID(zARC2_ID_BOOL), (void*)&value, sizeof(zBOOL));
};

void zCArchiverBinSafe::WriteString (const char* entryName, const zSTRING& value) 
{
	WriteASCIILine	(entryName, "string", "");
	WriteType(zTArchiveTypeID(zARC2_ID_STRING), (void*)value.ToChar(), strlen(value.ToChar()));
};

void zCArchiverBinSafe::WriteVec3 (const char* entryName, const zVEC3& value) 
{
	WriteASCIILine	(entryName, "vec3", zSTRING(value[0])+" "+zSTRING(value[1])+" "+zSTRING(value[2]));
	WriteType(zTArchiveTypeID(zARC2_ID_VEC3), (void*)&value, sizeof(zVEC3));
};

void zCArchiverBinSafe::WriteColor (const char* entryName, const zCOLOR& value) 
{
	WriteASCIILine	(entryName, "color", "");
	WriteType(zTArchiveTypeID(zARC2_ID_COLOR), (void*)&value, sizeof(zCOLOR));
};

void zCArchiverBinSafe::WriteRaw (const char* entryName, void* buffer, const zDWORD size) 
{
	WriteASCIILine	(entryName, "raw", "");
	WriteType(zTArchiveTypeID(zARC2_ID_RAW), buffer, size);
};

void zCArchiverBinSafe::WriteRawFloat (const char* entryName, void* buffer, const zDWORD size) 
{
	if ((size%4)!=0) 
	{
		zERR_FATAL("D: zArchiver(zCArchiverBinSafe::WriteRawFloat): raw float buffer has illegal size (mod4!=0): "+zSTRING(size));
	};

	WriteASCIILine	(entryName, "rawFloat", "");
	WriteType(zTArchiveTypeID(zARC2_ID_RAWFLOAT), buffer, size);
};

void zCArchiverBinSafe::WriteEnum (const char* entryName, const char* enumChoices, const int value) 
{
	if (InProperties()) 
	{
		const zSTRING s = "enum;"+zSTRING(enumChoices);
		WriteASCIILine	(entryName, s.ToChar(), "");
	} 
	else 
	{
		// Keine Enum-Choices schreiben, wenn nicht in Props (Optimierung)
		WriteASCIILine	(entryName, "enum", "");
	};
	WriteType(zTArchiveTypeID(zARC2_ID_ENUM), (void*)&value, 4);
}; 

void	zCArchiverBinSafe::WriteGroupBegin	(const char* groupName)
{
	// disabled for archiver2
	//WriteType(zTArchiveTypeID(zARC2_ID_GROUPBEGIN), (void*)groupName, strlen(groupName), 0xffffffff);
}

void	zCArchiverBinSafe::WriteGroupEnd		(const char* groupName)
{
	// disabled for archiver2
	//WriteType(zTArchiveTypeID(zARC2_ID_GROUPEND), (void*)groupName, strlen(groupName), 0xffffffff);
}

void zCArchiverBinSafe::WriteChunkStart (const char* chunkName, const char* className, zWORD classVersion, zDWORD objectIndex) {
	zTChunkRecord	chunk;

	// Format: [chunkName class:baseClass VERS INDEX]
	// indents schreiben (nur ASCII)
	//StoreBuffer		(spaces, chunkStack.GetNum());
	zSTRING chunkNameString(chunkName);		if (chunkNameString.IsEmpty()) chunkNameString= "%";
	zSTRING classNameString(className);		if (classNameString.IsEmpty()) classNameString= "%";
	const zSTRING& s= "["+chunkNameString+" "+classNameString+" "+zSTRING(classVersion)+" "+zSTRING(objectIndex)+"]";
	StoreStringEOL	(s.ToChar());

	// chunk auf den Stack packen
	chunkStack.InsertEnd(chunk);
};

void zCArchiverBinSafe::WriteChunkStart (const char* chunkName, zWORD chunkVersion) {
	WriteChunkStart (chunkName, "", chunkVersion, 0);
};

void zCArchiverBinSafe::WriteChunkEnd () {

	if (chunkStack.GetNum()==0) {
		zERR_FATAL("D: zArchiver(zCArchiverBinSafe::WriteChunkEnd): write chunk end with no open chunk !");
	};

	// chunk vom Stack holen
	zTChunkRecord		chunk;
	chunk				= chunkStack[chunkStack.GetNum()-1];
	chunkStack.RemoveOrderIndex (chunkStack.GetNum()-1);

	// Endmarkierung schreiben
	// indents schreiben (nur ASCII)
	//StoreBuffer		(spaces, chunkStack.GetNum());
	StoreStringEOL	("[]");
};

void zCArchiverBinSafe::WriteObject (const char* chunkName, zCObject& object) {
	// intern
	// Klassen-Namen und Vererbungs-Liste ermitteln 
	// abstrakte Klassen werden ausgelassen

	// transientes Objekt ? => NullPtr
	if (object.GetClassDef()->GetClassFlags() & zCLASS_FLAG_TRANSIENT)	{
		WriteObject (chunkName, 0);
		return;
	};

	zCClassDef		*classDef	= object.GetClassDef();
	if (!classDef)	zerr.Fatal ("D: zArchiver(zCArchiverBinSafe::WriteObject): zCObject without ClassDef, zCLASS_.. macros missing");
	zSTRING			className	( classDef->GetClassName_() );
					classDef	= classDef->GetBaseClassDef();

	while (classDef) {
		// abstrakte KlassenNamen 
		// ascii : werden geschrieben, damit ein 'ReadObject' sich darauf beziehen kann
		// binary: brauchen nicht geschrieben werden, da ein 'ReadObjectNamed' in diesem Mode aus Perf.Gruenden den KlassenNamen ignoriert
//		if ((!binaryMode) || (!classDef->IsAbstractClass()))
		if (!classDef->IsAbstractClass())
			className	+= ":"+classDef->GetClassName_();
		classDef	= classDef->GetBaseClassDef();
	};

	//
	const zDWORD objectIndex = objectList.GetNum();
    zADDREF_NOACCT       (&object);
	objectList.InsertEnd (&object);

	// schreiben
	WriteChunkStart		(chunkName, className.ToChar(), object.GetArchiveVersionSum(), objectIndex);
	object.Archive		(*this);
	WriteChunkEnd		();
};

void zCArchiverBinSafe::WriteObject (const char* chunkName, zCObject* object) {
	// interface
	// NUR HIER: NullPtr, Objekt-Referenzen

	// transientes Objekt ? => NullPtr
	if (object)
	if (object->GetClassDef()->GetClassFlags() & zCLASS_FLAG_TRANSIENT)	object=0;

	if (!object) {
		// Null-Ptr
		WriteChunkStart		(chunkName, "%", 0, 0);
		WriteChunkEnd		();
	} else {
		// wurde Objekt bereits geschrieben ?
		int objectIndex = objectList.Search(object);
		if (objectIndex>=0) 
		{
			// ja, also: nur eine Referenz auf Objekt schreiben
			WriteChunkStart		(chunkName, "§", 0, objectIndex);
			WriteChunkEnd		();
		}  else {
			WriteObject			(chunkName, *object);
		};
	};
};

void zCArchiverBinSafe::WriteObject (zCObject* object) 
{
	WriteObject ("", object);
};

// =======================================================================================================================

////////////////////////////////////
//	READ:	medium dependent
////////////////////////////////////

// hier Unterschied zFILE/zCBuffer
zBOOL zCArchiverBinSafe::OpenReadBuffer (zCBuffer& buffer, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags) {
	// setzt 'medium'
	Close();
	// mode, binaryMode konnen erst im ReadHeader() gesetzt werden
	this->medium		= zARC_MEDIUM_BUFFER;
	this->accessMode	= zARC_READ;
	this->inSaveGame	= saveGame;
	this->owningMedium	= FALSE;
	this->flags			= arcFlags;
	this->mode			= arcMode;

	cbuffer				= &buffer;
	cbuffer->SetMode	(READ);
	if (EndOfArchive()) {
		Close();
		return FALSE;
	};

	//
	ReadHeader			();

	//
	this->debugMessagesOn= (mode!=zARC_MODE_ASCII_PROPS);
	DebugMessage ("D: ARC: Reading archive buffer ("+zSTRING(s_arcModeNames[arcMode])+") ..");
	return TRUE;
};

void zCArchiverBinSafe::OpenReadFile (zFILE* fileRead, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags, zBOOL arcOwnsMedium) {
	if (!fileRead) return;
	Close();
	// mode, binaryMode konnen erst im ReadHeader() gesetzt werden
	this->medium			= zARC_MEDIUM_FILE;
	this->accessMode		= zARC_READ;
	this->inSaveGame		= saveGame;
	this->owningMedium		= arcOwnsMedium;
	this->file				= fileRead;
	this->mode				= arcMode;

	ReadHeader				();
	this->debugMessagesOn	= (mode!=zARC_MODE_ASCII_PROPS);
};

void zCArchiverBinSafe::RestoreBuffer (void* buffer, const zDWORD size) {
	assert (accessMode==zARC_READ);
	if (medium==zARC_MEDIUM_FILE)	file->   Read (buffer, size);
	else							cbuffer->Read(buffer, size);
};


void zCArchiverBinSafe::RestoreStringEOL (zSTRING& string) 
{
	assert (accessMode==zARC_READ);
 	RestoreString		(string);
};

 
void zCArchiverBinSafe::RestoreString0 (zSTRING& string) 
{
	assert (accessMode==zARC_READ);
	// Ende-Markierung: \0
	RestoreStringEOL (string);
};

zDWORD zCArchiverBinSafe::RestoreGetPos () 
{
	assert (accessMode==zARC_READ);
	if (medium==zARC_MEDIUM_FILE)	return file->Pos();
	else							return cbuffer->GetPos();
};

void zCArchiverBinSafe::RestoreSeek (const zDWORD newPos) 
{
	// FIXME: nicht seeken, falls newPos==actPos ???
	assert (accessMode==zARC_READ);
	if (newPos==RestoreGetPos()) return;
	if (medium==zARC_MEDIUM_FILE)	file->Seek		(newPos);
	else							cbuffer->SetPos	(newPos);
};

// ========================================================================

////////////////////////////////////
//	READ:	high level
////////////////////////////////////

void zCArchiverBinSafe::ReadHeader () 
{

	int ver;
	RestoreBuffer(&ver, sizeof(int));
	if(ver<2)
	{
		zERR_FATAL("OH: ReadHeader - old and defect version of ArchiverBinSafe found. This version is no longer supported. V" + zSTRING(ver));
		return;
	}
	
	int objCount				= 0;
	RestoreBuffer				(&objCount, sizeof(int));
	CheckObjectListSize			(objCount);

	int chunkPos				= 0;
	RestoreBuffer				(&chunkPos, sizeof(int));
	
	GEU32 posSeek				= RestoreGetPos();

	// read chunklist
	GEU32 nCount;
	RestoreSeek					(chunkPos);
	RestoreBuffer				(&nCount, sizeof(GEU32));

	// read string chunks
	GETStringMap<GEU32>* hashMap= (GETStringMap<GEU32>*) stringHashMap;
	hashMap->RemoveAll			(GEFalse);
	GESStringMapStorage			strMapStorage;

	char textBuffer[READ_BUFFER_SIZE];

	for(GEU32 i=0;i<nCount;i++)
	{
		RestoreBuffer			(&strMapStorage, sizeof(GESStringMapStorage));
		zDWORD readSize			= strMapStorage.HashMapStringLen;

		zERR_ASSERT_STRICT		(readSize<READ_BUFFER_SIZE);

		RestoreBuffer			(textBuffer, readSize);

		textBuffer				[strMapStorage.HashMapStringLen] = 0;

		hashMap->SetAtForce		(textBuffer, &dummyVal, strMapStorage.HashValue, strMapStorage.LinearValue);
	}

	RestoreSeek			(posSeek);
	posHeaderEnd		= RestoreGetPos();
};

void zCArchiverBinSafe::CheckObjectListSize (int numRequired) 
{
	int numOld = objectList.GetNum();
	if (numRequired<=numOld)	return;

	// etwas mehr Platz in der Liste bereitstellen, neue Plaetze mit 0 fuellen
	objectList		.AllocAbs			(numRequired + (numRequired/2));
	objectList		.MarkNumAllocUsed	();
	for (int i=numOld; i<objectList.GetNum(); i++)
		objectList[i] = 0;
};

zCObject* zCArchiverBinSafe::CreateObject (const zSTRING& className) 
{
	// Ein WriteObjectPtr auf ein NULL-Object liefert einen Klassen Chunk mit dem className '%'
	zCClassDef *classDef = GetClassDefByString (className);
	if (!classDef) return 0;

	zCObject *object = classDef->CreateNewInstance();
	if (!object)
		zERR_FAULT("D: zArchiver(zCArchiverBinSafe::CreateObject): could not create object for: "+className);
	return object;
};

zCClassDef* zCArchiverBinSafe::GetClassDefByString (const zSTRING& className) 
{
	// Ein WriteObjectPtr auf ein NULL-Object liefert einen Klassen Chunk mit dem className '%'
	zSTRING		name;
	zCClassDef	*classDef;
	int			i=1;	
	do {
		name	= className.PickWord	(i, ":", ":");
		classDef= zCObject::GetClassDef (name);
		i++;
	} while ((!classDef) && (name.Length()>0));

	return classDef;
};

void zCArchiverBinSafe::ReadChunkStartASCII (const char* chunkName, zSTRING& resultLine) 
{
	// intern
	// Ein Chunk mit angegebenen Teil-Namen wird gesucht
	// chunkName=="" => der naechste Chunk wird gesucht
	// "[chunkName ..]"
	resultLine.Clear();
	zSTRING			line, name;
	const zSTRING	chunkNameString(chunkName);
	zDWORD			lastSafePos	= RestoreGetPos();
	int				numCycles	= noReadSearchCycles ? 1 : 0;

	do {
		line.Clear();
		RestoreStringEOL	(line);
		// einen ChunkStart/End am Wickel ?
		if (line[0]=='[') 
		{
			if (line[1]!=']') 
			{
				// ChunkStart
				name = line.PickWord(1, SEPARATE_STRING_BRACKET_LEFT, SEPARATE_STRING_BRACKET_LEFT);
				// ATT: hier gab es einen Bug: und zwar wurde ein gefundene Chunk ohne Namen immer als zu oeffnender
				//      Chunk akzeptiert. Das gab Fehler, da Chunks gefoeffnet wurden, die man nicht oeffnen wollte.
				// if ((chunkNameString.IsEmpty()) || (name[0]=='%') || (name==chunkNameString)) 
				if ((chunkNameString.IsEmpty()) || (name==chunkNameString)) 
				{ 
					// gefunden
					resultLine = line;
					break;
				};

				SkipChunk (FALSE);		// NICHTs vom chunkStack entfernen
			} 
			else 
			{
				// ChunkEnd
				// bereits einmal den Chunk komplett durchsucht ?
				if ((numCycles==1) || (chunkStack.GetNum()==0)) 
				{
					RestoreSeek (lastSafePos);
					break;
				}

				// an den Chunk-Anfang zurueck
				RestoreSeek (chunkStack[chunkStack.GetNum()-1].startPos);

				// den Chunk von vorne durchsuchen
				numCycles++;
			};
		};
	} 
	while (!EndOfArchive());
};

zBOOL zCArchiverBinSafe::ReadChunkStart (const char* chunkName) {
	// intern
	// Ein Chunk mit spez. Namen wird gesucht und geoeffnet
	// gelesener Chunk liegt danach auf dem chunkStack
	zTChunkRecord	chunk;

	zSTRING line;
	ReadChunkStartASCII (chunkName, line);
	if (line.IsEmpty()) return FALSE;
	// FIXME: sscanf benutzen
	chunk.startPos		= RestoreGetPos();
	chunk.name			= line.PickWord(1, SEPARATE_STRING_BRACKET_LEFT, SEPARATE_STRING_BRACKET_LEFT);
	chunk.className		= line.PickWord(2, " " , " ");
	chunk.version		= zWORD(line.PickWord(3, " " , " " ).ToInt());
	chunk.objectIndex	= line.PickWord(4, SEPARATE_STRING_BRACKET_RIGHT, SEPARATE_STRING_BRACKET_RIGHT).ToInt();
	chunk.size			= 0;
	chunkStack.InsertEnd (chunk);
	return TRUE;
};

zBOOL zCArchiverBinSafe::ReadChunkStart (zSTRING& chunkName, zWORD& chunkVersion) {
	// interface
	zBOOL found = ReadChunkStart ("");
	if (!found) {
		chunkName.Clear();
	} else {
		chunkName		= chunkStack[chunkStack.GetNum()-1].name;
		chunkVersion	= chunkStack[chunkStack.GetNum()-1].version;
	};
	return found;
};

zBOOL zCArchiverBinSafe::ReadChunkStartNamed (const char* chunkName, zWORD& chunkVersion) {
	// interface
	zBOOL found		= ReadChunkStart (chunkName);
	if (found) {
		chunkVersion	= chunkStack[chunkStack.GetNum()-1].version;
	};
	return found;
};

zWORD zCArchiverBinSafe::GetCurrentChunkVersion()
{
	// to query class archive version within Archive()/Unarchive()
	if (chunkStack.GetNum()<=0)	return 0;
	return chunkStack[chunkStack.GetNum()-1].version;
};

void zCArchiverBinSafe::ReadChunkEnd () {
	// Falls ein Objekt nicht alle Daten des Chunks liest (z.B. weil es den Chunk einer
	// eigentlich abgeleiteten Klasse liest, die aber nicht erzeugt werden konnte), muss
	// der Rest hier übersprungen werden.
	SkipChunk (TRUE);
};

zCObject* zCArchiverBinSafe::ReadObject (const char* chunkName, zCObject* objectUseThis) 
{
	zCObject *object=0;

	//
	// Das Nichtfinden eines Chunks braucht kein Fehler sein, falls ein Objekt alls NULL-Ptr gespeichert wurde
	zBOOL found = ReadChunkStart (chunkName);
	if (!found) return objectUseThis;

	//
	const char	classNamePrefix = chunkStack[chunkStack.GetNum()-1].className[0];
	zBOOL		skipChunk		= FALSE;

	//
	if (classNamePrefix=='%') 
	{
		// Ein Null-Ptr ?
		object		= 0;
		skipChunk	= TRUE;
	} else
	if (classNamePrefix=='§') 
	{
		// Eine Objekt-Referenz ?
		// Referenz aufloesen: ein Objekt muss geschrieben worden sein, bevor
		// es referenziert wird
		zDWORD index = chunkStack[chunkStack.GetNum()-1].objectIndex;
		if (index>=objectList.GetNum())		zERR_FATAL ("D: zArchiver(::ReadObject): objRef, illegal object index: "+zSTRING(index));
		if (!objectList[index])				zERR_FATAL ("D: zArchiver(::ReadObject): objRef, referenced object has not been read, object index: "+zSTRING(index));

		object	= objectList[index];

		//
		if ((objectUseThis) && (object!=objectUseThis)) 
		{
			// FIXME: hier gibt's potentiell noch ein kleines Problemchen.... mit den Visuals...
			zERR_WARNING	("D: zArchiver(::ReadObject): found an objectPtr in file, tried to write thisto an 'objectUseThis'");

			// v1.08
			// Wenn diese Fehlermeldung auftritt befindet sich im Archive eine Referenz auf ein Objekt, wobei dem Archiver
			// explizit ein Objekt zum Fuellen uebergeben worden ist. Mit dieser Situation kann der Archiver natuerlich 
			// nicht korrekt umgehen: der Aufrufer moechte sein spezifisches Objekt gefuellt haben, waehrend das 
			// Archive ein Sharing des Objektes vorgibt.
			// Soetwas darf eigentlich gar nicht passieren, tut es aber in 1.06 bis 1.07 scheinbar (Kunden-Reports). Als
			// ein Workaround-Fix wird in diesem Fall die Referenz unbeachtet gelassen und der Aufrufer bekommt sein
			// hineingegebenes 'objectUseThis' zurueck.
			object			= objectUseThis;
		}

        if (!objectUseThis){ // [Moos] wenn schon ein Objekt da ist, brauchen wir kein Addref.
    	    zADDREF_NOACCT(object); 
        }

		skipChunk	= TRUE;
	} 
	else 
	{
		// Eine Objekt-Definition
		// Neu Erschaffen oder vorhandenes Objekt nutzen & fuellen (dann kein AddRef!)?
		if (objectUseThis)	
		{
			// ist das übergebene Objekt auch von demselben Typ, wie das aus dem File ?
			// Falls die Klasse aus dem File von der Klasse von objectUseThis abgeleitet ist:
			//		- es befinden sich zuviele Infos im Archiv (mehr als verarbeitet werden koennen), diese werden autom. geskippt (am ChunkEnde)
			// Falls die Klasse von objectUseThis von der Klasse aus dem File abgeleitet ist:
			//		- es befinden sich zuwenige Infos im Archiv, die Objekt-Unarchiv Methoden koennen darueber allerdings
			//		  nicht in Kenntnis gesetzt werden. In diesem Fall wird das Laden des Chunks trotzdem erlaubt (mit Warning),
			//		  wobei allerdings Unarchive() Methoden der Klassen darauf zu achten haben, dass sie "Default-sicher" sind.
			//		  D.h.: innerhalb eines Unarchive()::ReadXXX() koennte der Entry nicht gefunden werden, das Objekt sollte die
			//		  zu fuellende Variable als Referenz uebergeben, die bereits mit einem Default initialisert wurde, und in den
			//		  Fall des nicht-findens unberuehrt bleibt.
			//		  Im Binaer-Modus muss der Chunk allerdings komplett geskippt werden, da hier ueberhaupt kein Entry-Name-Matching 
			//		  stattfindet und so ueber den Chunk hinausgelesen wuerde (Checks auf Erreichen des Ende des Chunks pro
			//		  ReadXXX() waeren wohl moeglich, aber wohl auch zu teuer?).
			zCClassDef	*classDef = GetClassDefByString (chunkStack[chunkStack.GetNum()-1].className);
			if (objectUseThis->GetClassDef() != classDef) 
//			if (!objectUseThis->IsKindOf (classDef))	// nur diesen Weg abzufangen macht keinen Sinn... 3 Faelle sind moeglich: A->B, B->A, A/ \B
			{
				// der Binary Mode ist hier strikter: skipChunk noetig
				zERR_FAULT ("D: zArchiver(::ReadObject): skipping object-chunk, class from file does not match class from 'objectUseThis', file: "+((classDef) ? classDef->GetClassName_() : "%")+", obj: "+objectUseThis->GetClassName_());
				skipChunk = TRUE;
				
				// das 'objectUseThis' wird dennoch in die objectList eingetragen, damit spaetere Referenzen 
				// auf dieses Objekt aufgeloest werden koennen
				zDWORD index			= chunkStack[chunkStack.GetNum()-1].objectIndex;
				CheckObjectListSize		(index+1);

                zERR_ASSERTT_STRICT(!objectList[index], "Archiver tried to overwrite object in its list. Did you try to load an incompatible savegame?");
				objectList[index]		= objectUseThis;
                zADDREF_NOACCT           (objectUseThis);
			};
			object = objectUseThis;
		} else {
			object = CreateObject (chunkStack[chunkStack.GetNum()-1].className);
			// hier kein Addref..
		};
		if (!object) skipChunk = TRUE;
	};

	// Chunk-Inhalt bearbeiten (skippen oder lesen)
	if (skipChunk) {
		SkipChunk				(TRUE);		// entfernt vom chunkstack
	} 
	else 
	{
		// Versions-Check
		//if (object->GetArchiveVersionSum()!=chunkStack[chunkStack.GetNum()-1].version) 
		//{
		//};

		// In Liste unarchived Objekte eintragen
		zDWORD index			= chunkStack[chunkStack.GetNum()-1].objectIndex;
		CheckObjectListSize		(index+1);


        zERR_ASSERTT_STRICT(!objectList[index], "Archiver tried to overwrite object in its list. Did you try to load an incompatible savegame?");
        zADDREF_NOACCT           (object);
		objectList[index]		= object;
		object->Unarchive		(*this);
		ReadChunkEnd			();		// entfernt vom chunkstack
	};

	return object;
};

zCObject* zCArchiverBinSafe::ReadObject (zCObject* objectUseThis) {
	return ReadObject ("", objectUseThis);
};

void zCArchiverBinSafe::SkipChunk (const zBOOL removeFromChunkStack) {
	// skipt einen Chunk, dessen Header bereits gelesen wurde, und dessen Eintrag auf dem ChunkStack liegt
	if (chunkStack.GetNum()<=0) return;

	zSTRING line;
	int		level	= 1;
	int		ctr		= 0;
	do 
	{
		line.Clear();
		RestoreStringEOL	(line);
		if (line.Length()>0)
		if (line[0]=='[') 
		{
			if (line[1]!=']')	
				level++;		// ChunkStart
			else				
				level--;		// ChunkEnd
		};
		ctr++;
	} 
	
	while (level>0);
	if (ctr>1)
		warnEntrysNotRead	= TRUE;
	
	//
	if (removeFromChunkStack)
		chunkStack.RemoveOrderIndex (chunkStack.GetNum()-1);
};

zBOOL zCArchiverBinSafe::ReadEntryASCII (const char* entryName, zSTRING& resultValue) 
{
	// "name=type:value"
	zSTRING			line;
	zSTRING			name;
	int				numCycles	= noReadSearchCycles ? 1 : 0;

	zDWORD			hashRef = ResolveAndPosEntry(entryName);
	
	if(hashRef==0xffffffff)
	{
#ifndef ZDONT_WARN_ENTRY_NOT_FOUND
		zERR_WARNING ("OH: zCArchiverBinSafe::SkipChunk - expected entry not found: "+zSTRING(entryName));

        static int s_warnCount = 0;
        if (zSTRING(entryName) != zSTRING("pack")) s_warnCount ++;
        if (s_warnCount == 100)
            zERR_FAULT("M: really many entries not found! The archive is probably outdated.");
#endif
		return FALSE;
	}

	int hashValue	= 0xffffffff;
	zBOOL			isSection;
	zTArc2TypeChunk typeChunk;
	do {
		//RestoreStringEOL	(line);
		// opt: no typerescan and postread. Do it himself 
		zWORD			sSize;
		RestoreBuffer	((void*)&typeChunk, sizeof(zTArc2TypeChunk));
		isSection		= FALSE;
		switch (typeChunk.GetTypeID())
		{
			case zARC2_ID_STRING:
				RestoreBuffer	(&sSize, sizeof(zWORD));
				zERR_ASSERT		(sSize<READ_BUFFER_SIZE);
				if (sSize>0)
    				RestoreBuffer	(m_readTextBuffer, sSize);
				m_readTextBuffer[sSize] = 0;
				line			= m_readTextBuffer;
				isSection		= TRUE;
				break;
			case zARC2_ID_HASH:
				RestoreBuffer	(&hashValue, sizeof(zDWORD));
				break;
			case zARC2_ID_RAW:
				RestoreBuffer	(&sSize, sizeof(zWORD));
				zERR_ASSERT		(sSize<READ_BUFFER_SIZE);
				if (sSize>0)
    				RestoreBuffer	(m_readTextBuffer, sSize);
				break;
			case zARC2_ID_RAWFLOAT:
				RestoreBuffer	(&sSize, sizeof(zWORD));
				zERR_ASSERT		(sSize<READ_BUFFER_SIZE);
				if (sSize>0)
    				RestoreBuffer	(m_readTextBuffer, sSize);
				break;
			case zARC2_ID_INTEGER:
				RestoreBuffer	(&m_readTextBuffer, sizeof(int));
				break;
			case zARC2_ID_FLOAT:
				RestoreBuffer	(&m_readTextBuffer, sizeof(float));
				break;
			case zARC2_ID_BYTE:
				RestoreBuffer	(&m_readTextBuffer, sizeof(zBYTE));
				break;
			case zARC2_ID_WORD:
				RestoreBuffer	(&m_readTextBuffer, sizeof(zWORD));
				break;
			case zARC2_ID_BOOL:
				RestoreBuffer	(&m_readTextBuffer, sizeof(zBOOL));
				break;
			case zARC2_ID_VEC3:
				RestoreBuffer	(&m_readTextBuffer, sizeof(zVEC3));
				break;
			case zARC2_ID_COLOR:
				RestoreBuffer	(&m_readTextBuffer, sizeof(zCOLOR));
				break;
			case zARC2_ID_ENUM:
				RestoreBuffer	(&m_readTextBuffer, sizeof(int));
				break;
		};

		// einen ChunkStart/End am Wickel ?
		if (isSection==TRUE)
		{
			if (line[0]=='[') 
			{
				if (line[1]!=']')	
				{
					// ChunkStart
					SkipChunk (FALSE);		// NICHT vom ChunkStack entfernen
				} 
				else 
				{
					// ChunkEnd
					// zunaechst an den Anfang des Chunks zurueck
					// [EDENFELD] Patch 2 (1.30) Savegameladen sicherer gemacht
					if ( chunkStack.GetNum()-1<0 ) 
					{
						zERR_WARNING ("OH: zCArchiverBinSafe::SkipChunk - corrupt savegame ? stack underflow. ignoring...");
						return FALSE;
					}
					RestoreSeek			(chunkStack[chunkStack.GetNum()-1].startPos);
				
					// bereits einmal den Chunk komplett durchsucht ?
					if (numCycles==1) 
					{
						//resultValue.Clear();
						warnEntryNotFound = TRUE;
#ifndef ZDONT_WARN_ENTRY_NOT_FOUND
						zERR_WARNING ("OH: zCArchiverBinSafe::SkipChunk - (numCycles==1)expected entry not found: "+zSTRING(entryName));
#endif
						return FALSE;
					};
				
					// den Chunk von vorne durchsuchen
					numCycles++;
				}
				hashValue = 0xffffffff;
			} 
		}
 		else
		{
			if(hashRef==hashValue)
			{
				break;
			}
			continue;
		}
/*
		else 
		{
			if (line.IsEmpty()) continue;
			// den passenden Entry gefunden ?
			name = line.PickWord (1, trenn, trenn);
			if (strcmp(name.ToChar(), entryName)==0) 
			{
				// alles nach dem ersten ':' ist das Ergebnis
				break;
			} 
			else 
			{
				warnWrongEntryOrder	= TRUE;
			};
		};
		*/
	} 
	while(1);
	return TRUE;
};

float zCArchiverBinSafe::ReadFloat (const char* entryName) {
	float value;
	ReadFloat (entryName, value);
	return value;
};

zVEC3 zCArchiverBinSafe::ReadVec3 (const char* entryName) {
	zVEC3 value;
	ReadVec3 (entryName, value);
	return value;
};

int zCArchiverBinSafe::ReadInt (const char* entryName) {
	int value;
	ReadInt (entryName, value);
	return value;
};

zBYTE zCArchiverBinSafe::ReadByte (const char* entryName) {
	zBYTE value;
	ReadByte (entryName, value);
	return value;
};

zWORD zCArchiverBinSafe::ReadWord (const char* entryName) {
	zWORD value;
	ReadWord (entryName, value);
	return value;
};

zBOOL zCArchiverBinSafe::ReadBool (const char* entryName) 
{
	zBOOL value;
	ReadBool (entryName, value);
	return value;
};

zSTRING zCArchiverBinSafe::ReadString (const char* entryName) 
{
	zSTRING s;
	ReadString (entryName, s);
	return s;
};

zCOLOR zCArchiverBinSafe::ReadColor (const char* entryName) 
{
	zCOLOR value;
	ReadColor (entryName, value);
	return value;
};

int zCArchiverBinSafe::ReadEnum (const char* entryName) 
{
	int value;
	ReadEnum (entryName, value);
	return value;
}

void zCArchiverBinSafe::ReadRaw (const char* entryName, void* buffer, const zDWORD size) 
{
	if(ReadEntryASCII	(entryName, tmpResultValue))
		ReadType(zTArchiveTypeID(zARC2_ID_RAW), buffer, size);
}

void zCArchiverBinSafe::ReadRawFloat (const char* entryName, void* buffer, const zDWORD size) 
{
	if(ReadEntryASCII	(entryName, tmpResultValue))
		ReadType(zTArchiveTypeID(zARC2_ID_RAWFLOAT), buffer, size);
}

void zCArchiverBinSafe::ReadFloat (const char* entryName, float& value) 
{
	if (ReadEntryASCII (entryName, tmpResultValue))
		ReadType(zTArchiveTypeID(zARC2_ID_FLOAT), (void*)&value, sizeof(float));
};

void zCArchiverBinSafe::ReadVec3 (const char* entryName, zVEC3& value) 
{
	if (ReadEntryASCII	(entryName, tmpResultValue))
		ReadType(zTArchiveTypeID(zARC2_ID_VEC3), (void*)&value, sizeof(zVEC3));
};

void zCArchiverBinSafe::ReadInt (const char* entryName, int& value) 
{
	if (ReadEntryASCII	(entryName, tmpResultValue))
		ReadType(zTArchiveTypeID(zARC2_ID_INTEGER), (void*)&value, sizeof(int));
};

void zCArchiverBinSafe::ReadByte (const char* entryName, zBYTE& value) 
{
	if (ReadEntryASCII	(entryName, tmpResultValue))
		ReadType(zTArchiveTypeID(zARC2_ID_BYTE), (void*)&value, sizeof(zBYTE));
};

void zCArchiverBinSafe::ReadWord (const char* entryName, zWORD& value) 
{
	if (ReadEntryASCII	(entryName, tmpResultValue))
		ReadType(zTArchiveTypeID(zARC2_ID_WORD), (void*)&value, sizeof(zWORD));
};

void zCArchiverBinSafe::ReadBool (const char* entryName, zBOOL& value) 
{
	if (ReadEntryASCII	(entryName, tmpResultValue))
		ReadType(zTArchiveTypeID(zARC2_ID_BOOL), (void*)&value, sizeof(zBOOL));
};

void zCArchiverBinSafe::ReadString (const char* entryName, zSTRING& value) 
{
	if (ReadEntryASCII	(entryName, tmpResultValue))
		ReadType(zTArchiveTypeID(zARC2_ID_STRING), (void*)&value, 0);
};

void zCArchiverBinSafe::ReadColor (const char* entryName, zCOLOR& value) 
{
	if (ReadEntryASCII	(entryName, tmpResultValue))
		ReadType(zTArchiveTypeID(zARC2_ID_COLOR), (void*)&value, sizeof(zCOLOR));
};

void zCArchiverBinSafe::ReadEnum (const char* entryName, int& value) {
	if (ReadEntryASCII	(entryName, tmpResultValue))
		ReadType(zTArchiveTypeID(zARC2_ID_ENUM), (void*)&value, sizeof(int));
};

// =======================================================================================================================

#if 0
void zCArchiverBinSafe::TestClassIntegrity (zTTestClassCallback *callback) 
{
	zCClassDef *classDef;
	for (int i=0; i<zCClassDef::GetNum(); i++) 
	{
		classDef			= zCClassDef::GetClassDefByIndex(i);
		if (classDef->IsAbstractClass()) continue;

		//
		int		arcFlags	= zARC_FLAG_NO_SPY_MESSAGES;
		int		numLoops	= 1;

		if (callback)	
			(*callback)(0, 0, classDef, numLoops);

		if (numLoops>0)
			zerr.Message ("D: ARC: >>> Testing class: "+classDef->GetClassName_());

		for (int ctr=0; ctr<numLoops; ctr++)
		{
			for (int j=0; j<4; j++)
			{
				zCObject*			object			= classDef->CreateNewInstance();
				zCObject*			object2			= classDef->CreateNewInstance();
				zCBuffer*			buffer			= 0;
				zCArchiver			*arcWrite		= 0;

				zBOOL warnEntryNotFound		= FALSE;
				zBOOL warnEntrysNotRead		= FALSE;
				zBOOL warnWrongEntryOrder	= FALSE;

				{
					switch (j)
					{
						case 0:	arcWrite = zarcFactory.CreateArchiverWrite (zARC_MODE_BINARY, FALSE, arcFlags);	break;
						case 1:	arcWrite = zarcFactory.CreateArchiverWrite (zARC_MODE_ASCII , FALSE, arcFlags);	break;
						case 2:	arcWrite = zarcFactory.CreateArchiverWrite (zARC_MODE_BINARY, TRUE , arcFlags);	break;
						case 3:	arcWrite = zarcFactory.CreateArchiverWrite (zARC_MODE_ASCII , TRUE , arcFlags);	break;
	//					case 2:	arcWrite->OpenWriteBuffer	(zCArchiverBinSafe::zARC_MODE_ASCII_PROPS);break;	// FIXME: macht wegen den "groupBegin/End" noch Ärger..
					};
					zERR_ASSERT_STRICT (arcWrite);

					int dummy;
					if (callback)	(*callback)(object, ctr, 0, dummy);
					{
						arcWrite->WriteObject			(object);
						buffer = arcWrite->GetBuffer		();
						{
							// Objekt1
							zCArchiver			*arcRead	= zarcFactory.CreateArchiverRead (buffer, arcFlags);
							zCArchiverBinSafe	*arcReadGen	= dynamic_cast<zCArchiverBinSafe*>(arcRead);
							zERR_ASSERT_STRICT				(arcReadGen);
							arcReadGen->warnEntrysNotRead	= FALSE;
							arcReadGen->warnEntryNotFound	= FALSE;
							arcReadGen->warnWrongEntryOrder	= FALSE;
							arcRead->ReadObject				(object);
							warnEntryNotFound				= warnEntryNotFound   || arcReadGen->warnEntryNotFound;
							warnEntrysNotRead				= warnEntrysNotRead	  || arcReadGen->warnEntrysNotRead;
							warnWrongEntryOrder				= warnWrongEntryOrder || arcReadGen->warnWrongEntryOrder;
							arcRead->Close					();
							zRELEASE						(arcRead);
						};
						{
							// Objekt 2
							zCArchiver			*arcRead	= zarcFactory.CreateArchiverRead (buffer, arcFlags);
							zCArchiverBinSafe	*arcReadGen	= dynamic_cast<zCArchiverBinSafe*>(arcRead);
							zERR_ASSERT_STRICT (arcReadGen);
							arcReadGen->warnEntrysNotRead	= FALSE;
							arcReadGen->warnEntryNotFound	= FALSE;
							arcReadGen->warnWrongEntryOrder	= FALSE;
							arcRead->ReadObject				(object2);
							warnEntryNotFound				= warnEntryNotFound   || arcReadGen->warnEntryNotFound;
							warnEntrysNotRead				= warnEntrysNotRead	  || arcReadGen->warnEntrysNotRead;
							warnWrongEntryOrder				= warnWrongEntryOrder || arcReadGen->warnWrongEntryOrder;
							arcRead->Close					();
							zRELEASE						(arcRead);
						};
						buffer->SetMode					(WRITE);
						arcWrite->Close					();
					};
					zRELEASE (arcWrite);
				};
				object ->Release();
				object2->Release();
				if (warnEntryNotFound)		zERR_FAULT ("D: ARC: expected entry not found !");
				if (warnEntrysNotRead)		zERR_FAULT ("D: ARC: entry was not read !");
				if (warnWrongEntryOrder)	zERR_FAULT ("D: ARC: order differs: reading/writing entrys !");
			};
		};
	};
};
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////


zCObject*	zCCFASTCALL zCArchiverBinSafe::GetParentObject() 
{
	// das zCObject des ersten Chunks von unten zuruecklierfern, dass kein klassenloser Chunk ist
	int i = chunkStack.GetNum()-2;
	while (i>=0)
	{
		if ((!chunkStack[i].className.IsEmpty()) &&
			( chunkStack[i].className[0]!='%'))
		{
			return this->objectList[chunkStack[i].objectIndex];
		};
		--i;
	};
	return 0;
};
