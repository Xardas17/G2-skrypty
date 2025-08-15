/******************************************************************************** 
 
     $Workfile:: zArchiverGeneric.cpp $                $Date:: 22.05.01 18:45   $
     $Revision:: 21                   $             $Modtime:: 30.05.01 0:07    $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created:

 * $Log: /current_work/ZenGin/_Dieter/zArchiverGeneric.cpp $
 * 
 * 21    22.05.01 18:45 Edenfeld
 * 
 * 19    15.03.01 18:52 Hildebrandt
 * 
 * 18    14.02.01 20:57 Hildebrandt
 * fixed load saveGame crash (falsely opening unnamed chunk)
 * 
 * 17    25.01.01 13:21 Moos
 * 
 * 16    25.01.01 12:38 Moos
 * 
 * 15    25.01.01 12:14 Moos
 * 
 * 14    16.01.01 16:35 Hildebrandt
 * 
 * 13    15.01.01 19:07 Hildebrandt
 * added public zCObject* GetParentObject()
 * 
 * 12    12.01.01 16:00 Speckels
 * 
 * 11    3.11.00 15:03 Speckels
 * 
 * 10    28.09.00 19:20 Hildebrandt
 * 
 * 9     11.09.00 19:40 Speckels
 * 
 * 8     8.09.00 19:59 Hildebrandt
 * 
 * 7     31.08.00 17:04 Hildebrandt
 * 
 * 6     22.08.00 16:22 Hildebrandt
 * 
 * 5     22.08.00 15:18 Hildebrandt
 * 
 * 4     21.08.00 21:48 Hildebrandt
 * 
 * 3     21.08.00 19:16 Hildebrandt
 * 
 * 2     21.08.00 17:18 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author  Author: Hildebrandt
/// @version $Revision: 21 $ ($Modtime: 30.05.01 0:07 $)
// =======================================================================================================================

#include <zCore.h>
#include <zBuffer.h>
#include <zArchiverGeneric.h>


// =======================================================================================================================

/*
	LESEN:
	- Text im 'TEXT'-VZ
	- MAX-SDK Doku: Loading and saving plugin-data, etc.

*/

/*
FIXME:
- WriteBuffer prueft noch nicht auf Buffer-Überlauf !!!
- EndOfArchive() buggy
- EOL Handling ist buggy
- openWrite: option auf smallHeader
- uhh: muss die Index-Nummer in jedem Object Header vorhanden sein ?
  (=> fuer Referenzen beim Einlesen, ginge auch ohne, ist dann aber unsicherer?)

###

- RefCounting ist noch falsch/uneinheitlich !!
- ein mit CreateBuffer() erzeugter eigener Buffer muss auf Overflow geprueft werden !
- "ReadFloat()" etc. sollte in einer Default-sicheren Variante vorhanden sein
- Soll der Archiver automatisch Script-Klassen packen/entpacken koennen ?

- Zugriffs-Arten
	- r/w file			(bebuffered ?)
	- r/w buffer		(=> props)
	- access r/w file	(dirty direct access, ohne Archiv-Header)
*/

// =======================================================================================================================

zCLASS_DEFINITION		( zCArchiverGeneric	, zCArchiver, 0,	0	)

zSTRING	zCArchiverGeneric::stringEOL			= "\n";		// default: for game/fileIO, for spacer: "\r\n";
static char* const sep0							= "=";		
static char* const sep1							= ":";		
static char* const spaces						= "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
static const zSTRING s_arcModeNames[zARC_MODE_COUNT] = 
{
	zSTRING("BINARY"),
	zSTRING("ASCII"),
	zSTRING("ASCII_PROPS"),
	zSTRING("BIN_SAFE")
};
static const zSTRING SEPARATE_STRING_BRACKET_LEFT	(" ["); 
static const zSTRING SEPARATE_STRING_BRACKET_RIGHT	(" ]"); 

////////////////////////////////////
//	COMMON
////////////////////////////////////

zCArchiverGeneric::zCArchiverGeneric() 
{
	file				= 0;
	cbuffer				= 0;
	owningMedium		= FALSE;
	medium				= zARC_MEDIUM_FILE;
	mode				= zARC_MODE_BINARY;
	inSaveGame			= FALSE;
	binaryMode			= FALSE;
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

	//
	SetNoReadSearchCycles	(FALSE);
};

zCArchiverGeneric::~zCArchiverGeneric	() 
{
	Close					();
	writeObjectList.Clear	();		// safety
	file					= 0;
	cbuffer					= 0;
};

void zCArchiverGeneric::DebugMessage (const zSTRING& m) 
{
	if (!debugMessagesOn)					return;
	if (flags & zARC_FLAG_NO_SPY_MESSAGES)	return;
	zerr.Message (m);
};

void zCArchiverGeneric::WriteHeaderNumObj () 
{
	if (accessMode!=zARC_WRITE) return;

	if ((medium==zARC_MEDIUM_FILE) && (!file->IsOpened())) return;

	// Num Objects
	zDWORD oldPos =	 StoreGetPos();
	StoreSeek		(posNumObjects);
	StoreString		(zSTRING(objectList.GetNum()).ToChar());
	StoreSeek		(oldPos);
};

void zCArchiverGeneric::Close () 
{
	if (accessMode==zARC_CLOSED) return;

	// hat Archive einen eigenen Header ?	(FIXME: dirty Abfrage..)
	{
		// Read/Write spezifisches
		if (accessMode==zARC_WRITE) 
		{
			WriteHeaderNumObj();

			// Checksum
			if (checksumEnabled) {
			};
		} else {
			// Checksum
			if (checksumEnabled) {
			};
		};
	};

	// Medium schliessen
	if (owningMedium) 
	{
		//
		DebugMessage ("D: ARC: .. Closing ("+zSTRING(objectList.GetNum())+" objects)");

		//
		if (medium==zARC_MEDIUM_FILE) {
			if (file) {
				if (file->IsOpened()) file->Close();
				if (owningMedium)	delete file;	file=0;
			};
		} else {
			DeleteBuffer();
		};
	};

	// cleanup
    for (int i=objectList.GetNumInList()-1; i>=0; i--)
        zRELEASE(objectList[i]);

	objectList.EmptyList		();
	chunkStack.EmptyList		();
	writeObjectList.Clear		();
	file						= 0;
	cbuffer						= 0;
	accessMode					= zARC_CLOSED;
};

zBOOL zCArchiverGeneric::EndOfArchive () 
{
	// FIXME: hack
	if (medium==zARC_MEDIUM_FILE)	return file->Eof() || file->Pos()+3>file->Size();
	else							return (int(cbuffer->GetSize()) - int(cbuffer->GetPos()))<0;
};

void zCArchiverGeneric::DeleteBuffer () 
{
	if (owningMedium) delete cbuffer;
	cbuffer = 0;
};

void zCArchiverGeneric::GetBufferString (zSTRING& result) 
{
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

zCBuffer* zCArchiverGeneric::GetBuffer () 
{
	// den Header gueltig machen (im Laufenden Betrieb, vor dem ::Close())
	WriteHeaderNumObj();

	return cbuffer;
};

// =======================================================================================================================

////////////////////////////////////
//	WRITE:	medium dependent
////////////////////////////////////

/*
zBOOL zCArchiverGeneric::OpenWriteFile2 (const zSTRING& fileName, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags) {
	Close();

	this->medium		= zARC_MEDIUM_FILE;
	this->mode			= arcMode;
	this->binaryMode	= (arcMode==zARC_MODE_BINARY);
	this->inSaveGame	= saveGame;
	this->accessMode	= zARC_WRITE;
	this->owningMedium	= TRUE;
	this->flags			= arcFlags;
	this->debugMessagesOn= (mode!=zARC_MODE_ASCII_PROPS);
	file = zfactory->CreateZFile (fileName);
	if (file->Create()!=zERR_NONE)	return FALSE;

	//
	DebugMessage ("D: ARC: Writing archive '"+fileName+"' (" +zSTRING(binaryMode ? arcHeaderBinary : arcHeaderASCII)+") ..");

	//
	WriteHeader			(arcFlags);
	return TRUE;
};
*/


/*	------------------------------------------------------------------
	zCArchiverGeneric::zCArchiverGeneric
	18.08.00	[Hildebrandt]	
				Benutzung von 's_arcModeNames', Methoden Argument arcOwnsMedium;
				Es wird auch optional kein zCBuffer mehr selbst erzeugt.
				Bugfix: this->cbuffer = buffer; fehlte
	------------------------------------------------------------------ */

zBOOL zCArchiverGeneric::OpenWriteBuffer (zCBuffer* buffer, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags, zBOOL arcOwnsMedium)
{
	zERR_ASSERT (buffer);
	Close();

	this->medium		= zARC_MEDIUM_BUFFER;
	this->mode			= arcMode;
	this->binaryMode	= (arcMode==zARC_MODE_BINARY);
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

/*	------------------------------------------------------------------
	zCArchiverGeneric::zCArchiverGeneric
	18.08.00	[Hildebrandt]
				Neues Methoden Argument 'arcOwnsMedium'
	------------------------------------------------------------------ */

void zCArchiverGeneric::OpenWriteFile (zFILE* fileWrite, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags, zBOOL arcOwnsMedium) {
	if (!fileWrite) return;
	Close();

	this->medium			= zARC_MEDIUM_FILE;
	this->mode				= arcMode;
	this->binaryMode		= (arcMode==zARC_MODE_BINARY);
	this->inSaveGame		= saveGame;
	this->accessMode		= zARC_WRITE;
	this->owningMedium		= arcOwnsMedium;
	this->file				= fileWrite;
	this->flags				= arcFlags;
	this->debugMessagesOn	= (mode!=zARC_MODE_ASCII_PROPS);

	//
	WriteHeader			(arcFlags);
};

/*	------------------------------------------------------------------
	zCArchiverGeneric::zCArchiverGeneric
	18.08.00	[Hildebrandt]
				Nichtschreiben von Buffers deren Len==0
	------------------------------------------------------------------ */

void zCArchiverGeneric::StoreBuffer (void* buffer, const zDWORD size) {
	assert (accessMode==zARC_WRITE);
	if (size<=0) return;
	if (medium==zARC_MEDIUM_FILE) {
		file->Write		(buffer, size);
	} else {
		cbuffer->Write	(buffer, size);
	};
};

/*	------------------------------------------------------------------
	zCArchiverGeneric::zCArchiverGeneric
	18.08.00	[Hildebrandt]
				Nichtschreiben von Strings deren Len==0
	------------------------------------------------------------------ */

void zCArchiverGeneric::StoreString (const char* string) 
{
	assert (accessMode==zARC_WRITE);
	// schreibt KEINE Null am Ende !!
	const int strLen = strlen(string);
	if (strLen<=0) return;

	if (medium==zARC_MEDIUM_FILE)	file->Write(string, strLen);
	else							cbuffer->Write((void*)string, strLen);
};

zDWORD zCArchiverGeneric::StoreGetPos () {
	assert (accessMode==zARC_WRITE);
	if (medium==zARC_MEDIUM_FILE)	return file->Pos();
	else							return cbuffer->GetPos();
};

void zCArchiverGeneric::StoreSeek (const zDWORD newPos) {
	assert (accessMode==zARC_WRITE);
	if (medium==zARC_MEDIUM_FILE)	file->Seek		(newPos);
	else							cbuffer->SetPos	(newPos);
};

void zCArchiverGeneric::StoreStringEOL (const char* string) {
	assert (accessMode==zARC_WRITE);
	StoreString		(string);
	StoreString		(stringEOL.ToChar());
};

// ========================================================================

////////////////////////////////////
//	WRITE:	high level
////////////////////////////////////

/*	------------------------------------------------------------------
	zCArchiverGeneric::zCArchiverGeneric
	18.08.00	[Hildebrandt]
				Anpassung an Benutzung des zCArchiverFactory, Ausduennung
	------------------------------------------------------------------ */

void zCArchiverGeneric::WriteHeader (const int arcFlags) {
/*	//
	StoreStringEOL	(arcHeader);

	// File-version	
	StoreStringEOL	("ver 0");							

	// mode
	if (mode==zARC_MODE_BINARY)	StoreStringEOL	(arcHeaderBinary);	else
	if (mode==zARC_MODE_ASCII)	StoreStringEOL	(arcHeaderASCII);	else
								StoreStringEOL	(arcHeaderASCII_PROPS);

	// saveGame
	StoreString   	("saveGame ");
	StoreStringEOL	(InSaveGame() ? "1" : "0");

	// ============================================================

	// weitere, nicht unbedingt notwendige Zusatzinfos schreiben
	if (!(arcFlags & zARC_FLAG_WRITE_BRIEF_HEADER)) {
		// date
		// FIXME: WINDOWS**WINDOWS**
		SYSTEMTIME	st;
		GetLocalTime (&st);
		const zSTRING date ("date "+
							zSTRING(st.wDay )+"."+zSTRING(st.wMonth) +"."+zSTRING(st.wYear)+" "+
							zSTRING(st.wHour)+":"+zSTRING(st.wMinute)+":"+zSTRING(st.wSecond));
		StoreStringEOL	(date.ToChar());

		// user
		// FIXME: WINDOWS**WINDOWS**
		char	userName[200];
		DWORD	userNameSize = sizeof(userName);
		if (GetUserName(userName, &userNameSize)) {
			StoreString		("user ");
			StoreStringEOL	(userName);
		};
	};
*/
	// num objects
	StoreString   	("objects ");
	posNumObjects	= StoreGetPos();
	StoreStringEOL	("0        ");
	
/*	// 32 BIT checksum, HEX
	StoreString   	("csum ");							
	posChecksum		= StoreGetPos();
	StoreStringEOL	("00000000");
*/
	//
	StoreStringEOL	("END");
	StoreString		(stringEOL.ToChar());
	posHeaderEnd	= StoreGetPos();
};

zBOOL zCArchiverGeneric::IsStringValid (const char* string) {
	// valid string for entryName / entryValue ?
	const char* ptr = string;
	while (*ptr) {
		if ((*ptr==sep0[0]) || 
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

void zCArchiverGeneric::WriteASCIILine (const char* entryName, const char* typeName, const zSTRING& value) {
	if (!IsStringValid (entryName) || !IsStringValid (value.ToChar())) {
		zERR_FAULT("D: zArchiver(zCArchiverGeneric::WriteASCIILine): string contains illegal characters: \""+
			zSTRING(entryName)+" / "+value);
	};
	StoreBuffer		(spaces, chunkStack.GetNum());
	StoreString		(entryName);
	StoreBuffer		(sep0, 1);
	StoreString		(typeName);
	StoreBuffer		(sep1, 1);
	StoreStringEOL	(value.ToChar());
};

void zCArchiverGeneric::WriteInt (const char* entryName, const int value) {
	if (binaryMode)	StoreBuffer		((void*)(&value), sizeof(value));
	else			WriteASCIILine	(entryName, "int", zSTRING(value));
};

void zCArchiverGeneric::WriteByte (const char* entryName, const zBYTE value) {
	if (binaryMode)	StoreBuffer		((void*)(&value), sizeof(value));
	else			WriteASCIILine	(entryName, "int", zSTRING(value));
};

void zCArchiverGeneric::WriteWord (const char* entryName, const zWORD value) {
	if (binaryMode)	StoreBuffer		((void*)(&value), sizeof(value));
	else			WriteASCIILine	(entryName, "int", zSTRING(value));
};

void zCArchiverGeneric::WriteFloat (const char* entryName, const float value) {
	if (binaryMode)	StoreBuffer		((void*)(&value), sizeof(value));
	else			WriteASCIILine	(entryName, "float", zSTRING(value));
};

void zCArchiverGeneric::WriteBool (const char* entryName, const zBOOL value) {
	if (binaryMode) {
		zBYTE v			= zBYTE(value);
		StoreBuffer		((void*)(&v), sizeof(v));
	} else {
		WriteASCIILine	(entryName, "bool", zSTRING(value));
	};
};

void zCArchiverGeneric::WriteString (const char* entryName, const zSTRING& value) {
	if (binaryMode) {
		StoreString		(value.ToChar());
		StoreBuffer		("\0", 1); 
	} else {
		WriteASCIILine	(entryName, "string", value);
	};
};

void zCArchiverGeneric::WriteVec3 (const char* entryName, const zVEC3& value) {
	if (binaryMode)	StoreBuffer		((void*)(&value), sizeof(value));
	else			WriteASCIILine	(entryName, "vec3", zSTRING(value[0])+" "+zSTRING(value[1])+" "+zSTRING(value[2]));
};

void zCArchiverGeneric::WriteColor (const char* entryName, const zCOLOR& value) {
	if (binaryMode)	StoreBuffer		((void*)(&value), sizeof(value));
	else			WriteASCIILine	(entryName, "color", zSTRING(value.r)+" "+zSTRING(value.g)+" "+zSTRING(value.b)+" "+zSTRING(value.alpha));
};

void zCArchiverGeneric::WriteRaw (const char* entryName, void* buffer, const zDWORD size) {
	if (binaryMode)	StoreBuffer		(buffer, size);
	else {
		zSTRING value;
		char	charBuffer[32];
		for (int i=0; i<size; i++) {
			// byte fuer byte
			sprintf (charBuffer, "%02x", int( ((zBYTE*)buffer)[i] ));
			value += charBuffer;
		};
		WriteASCIILine	(entryName, "raw", value);
	};
};

void zCArchiverGeneric::WriteRawFloat (const char* entryName, void* buffer, const zDWORD size) {
	if ((size%4)!=0) {
		zERR_FATAL("D: zArchiver(zCArchiverGeneric::WriteRawFloat): raw float buffer has illegal size (mod4!=0): "+zSTRING(size));
	};

	if (binaryMode)	StoreBuffer		(buffer, size);
	else {
		zSTRING value;
		int		numFloats	= size / sizeof(float);
		float	*floatBuffer= (float*)buffer;

		for (int i=0; i<numFloats; i++) {
			value += zSTRING(floatBuffer[i])+" ";
		};
		WriteASCIILine	(entryName, "rawFloat", value);
	};
};

void zCArchiverGeneric::WriteEnum (const char* entryName, const char* enumChoices, const int value) {
	if (binaryMode) {
		WriteByte (entryName, value);
	} else {
		if (InProperties()) {
			const zSTRING s = "enum;"+zSTRING(enumChoices);
			WriteASCIILine	(entryName, s.ToChar(), zSTRING(value));
		} else {
			// Keine Enum-Choices schreiben, wenn nicht in Props (Optimierung)
			WriteASCIILine	(entryName, "enum", zSTRING(value));
		};
	};
}; 

void zCArchiverGeneric::WriteChunkStart (const char* chunkName, const char* className, zWORD classVersion, zDWORD objectIndex) {
	zTChunkRecord	chunk;

	if (binaryMode) {
		// Format: zDWORD size, zWORD vers, zDWORD index, zSTRING chunk, /0, zSTRING class, /0
		chunk.startPos	= StoreGetPos();

		zDWORD size		= 0;
		StoreBuffer		(&size, sizeof(size));
		StoreBuffer		(&classVersion	, sizeof(classVersion));
		StoreBuffer		(&objectIndex	, sizeof(objectIndex));
		// leerer ChunkName ?
		if (chunkName[0]==0)	StoreString		("%");
		else					StoreString		(chunkName);
		StoreBuffer		("\0", 1); 
		StoreString		(className);
		StoreBuffer		("\0", 1); 
	} else {
		// Format: [chunkName class:baseClass VERS INDEX]
		// indents schreiben (nur ASCII)
		StoreBuffer		(spaces, chunkStack.GetNum());
		zSTRING chunkNameString(chunkName);		if (chunkNameString.IsEmpty()) chunkNameString= "%";
		zSTRING classNameString(className);		if (classNameString.IsEmpty()) classNameString= "%";
		const zSTRING& s= "["+chunkNameString+" "+classNameString+" "+zSTRING(classVersion)+" "+zSTRING(objectIndex)+"]";
		StoreStringEOL	(s.ToChar());
	};

	// chunk auf den Stack packen
	chunkStack.InsertEnd(chunk);
};

void zCArchiverGeneric::WriteChunkStart (const char* chunkName, zWORD chunkVersion) {
	WriteChunkStart (chunkName, "", chunkVersion, 0);
};

void zCArchiverGeneric::WriteChunkEnd () 
{
	if (chunkStack.GetNum()==0) {
		zERR_FATAL("D: zArchiver(zCArchiverGeneric::WriteChunkEnd): write chunk end with no open chunk !");
	};

	// chunk vom Stack holen
	zTChunkRecord		chunk;
	chunk				= chunkStack[chunkStack.GetNum()-1];
	chunkStack.RemoveOrderIndex (chunkStack.GetNum()-1);

	if (binaryMode) {
		// Chunk Laenge eintragen
		zDWORD len		= StoreGetPos()- chunk.startPos;
		zDWORD oldPos	= StoreGetPos();
		StoreSeek		(chunk.startPos);
		StoreBuffer		(&len, sizeof(len)); 
		StoreSeek		(oldPos);
	} else {
		// Endmarkierung schreiben
		// indents schreiben (nur ASCII)
		StoreBuffer		(spaces, chunkStack.GetNum());
		StoreStringEOL	("[]");
	};
};

void zCArchiverGeneric::WriteObject (const char* chunkName, zCObject& object) 
{
	// intern
	// Klassen-Namen und Vererbungs-Liste ermitteln 
	// abstrakte Klassen werden ausgelassen

	// transientes Objekt ? => NullPtr
	if (object.GetClassDef()->GetClassFlags() & zCLASS_FLAG_TRANSIENT)	{
		WriteObject (chunkName, 0);
		return;
	};

	zCClassDef		*classDef	= object.GetClassDef();
	if (!classDef)	zerr.Fatal ("D: zArchiver(zCArchiverGeneric::WriteObject): zCObject without ClassDef, zCLASS_.. macros missing");
	zSTRING			className	( classDef->GetClassName_() );
					classDef	= classDef->GetBaseClassDef();

	while (classDef) 
	{
		// abstrakte KlassenNamen 
		// ascii : werden geschrieben, damit ein 'ReadObject' sich darauf beziehen kann
		// binary: brauchen nicht geschrieben werden, da ein 'ReadObjectNamed' in diesem Mode aus Perf.Gruenden den KlassenNamen ignoriert
		if (!classDef->IsAbstractClass())
			className	+= ":"+classDef->GetClassName_();
		classDef	= classDef->GetBaseClassDef();
	};

	// in objectList eintragen (hat 'objectIndex' als key)
	const zDWORD objectIndex		= objectList.GetNum();
	objectList.InsertEnd			(object.AddRef());

#ifdef _DEBUG
	// PARANOID
	{
		zTWriteObjectEntry				*writeObjectEntry=0;
		writeObjectEntry				= writeObjectList[&object];
		zERR_ASSERT (writeObjectEntry==0);		// darf noch nicht da sein
	};
#endif

	// in writeObjectList eintragen (hat 'objectPtr' als key)
	{
		zTWriteObjectEntry				*writeObjectEntry;
		writeObjectEntry				= writeObjectList.Insert (&object);
		writeObjectEntry->object		= &object;
		writeObjectEntry->objectIndex	= objectIndex;
	};
#ifdef _DEBUG
	// PARANOID
	{
		zTWriteObjectEntry				*writeObjectEntry=0;
		writeObjectEntry				= writeObjectList[&object];
		zERR_ASSERT (writeObjectEntry->object==&object);			// muss jetzt da sein
		zERR_ASSERT (writeObjectEntry->objectIndex==objectIndex);
	};
#endif

	// schreiben
	WriteChunkStart					(chunkName, className.ToChar(), object.GetArchiveVersionSum(), objectIndex);
	object.Archive					(*this);
	WriteChunkEnd					();
};

void zCArchiverGeneric::WriteObject (const char* chunkName, zCObject* object) 
{
	// public interface
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
		// int objectIndex		= objectList.Search(object);

		// Die lineare Listensuche in 'objectList' war beim Speichern ein starker Bottleneck. Diese 
		// Operation ist nun durch einen separaten Container ersetzt, der effizienter nach dem ObjektPtr als
		// Schluessel zugreifen kann. Derzeit wird das SparseArray benutzt. Profiles zeigen immer noch diese
		// Funktion als Bottleneck ('Hash'), obwohl diesesmal wesentlich weniger stark. 
		// (TODO: waere die STL-Map schneller?)
		zTWriteObjectEntry	*writeObjectEntry;
		writeObjectEntry	= writeObjectList[object];

		if ((writeObjectEntry) && (writeObjectEntry->objectIndex>=0))
		{
			//
			int objectIndex		= writeObjectEntry->objectIndex;
			zERR_ASSERT (objectIndex==objectList.Search(object));

			// ja, also: nur eine Referenz auf Objekt schreiben
			WriteChunkStart		(chunkName, "§", 0, objectIndex);
			WriteChunkEnd		();
		}  else {
			WriteObject			(chunkName, *object);
		};
	};
};

void zCArchiverGeneric::WriteObject (zCObject* object) {
	WriteObject ("", object);
};

void zCArchiverGeneric::WriteGroupBegin (const char* groupName) {
	if (!InProperties()) return;
	WriteASCIILine	(groupName, "groupBegin", "");
};

void zCArchiverGeneric::WriteGroupEnd (const char* groupName) {
	if (!InProperties()) return;
	WriteASCIILine	(groupName, "groupEnd", "");
};

// =======================================================================================================================

////////////////////////////////////
//	READ:	medium dependent
////////////////////////////////////

/*	------------------------------------------------------------------
	zCArchiverGeneric::zCArchiverGeneric
	18.08.00	[Hildebrandt]
				Neue Methoden Argumente arcMode, saveGame
	------------------------------------------------------------------ */

zBOOL zCArchiverGeneric::OpenReadBuffer (zCBuffer& buffer, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags) {
	// setzt 'medium'
	Close();
	// mode, binaryMode konnen erst im ReadHeader() gesetzt werden
	this->medium		= zARC_MEDIUM_BUFFER;
	this->accessMode	= zARC_READ;
	this->inSaveGame	= saveGame;
	this->owningMedium	= FALSE;
	this->flags			= arcFlags;
	this->mode			= arcMode;
	this->binaryMode	= (arcMode==zARC_MODE_BINARY);

	cbuffer				= &buffer;
	cbuffer->SetMode	(READ);
	if (EndOfArchive()) {
		Close();
		return FALSE;
	};

	//
	ReadHeader			();
	this->binaryMode	= (arcMode==zARC_MODE_BINARY);

	//
	this->debugMessagesOn= (mode!=zARC_MODE_ASCII_PROPS);
	DebugMessage ("D: ARC: Reading archive buffer ("+zSTRING(s_arcModeNames[arcMode])+") ..");
	return TRUE;
};

/*	------------------------------------------------------------------
	zCArchiverGeneric::zCArchiverGeneric
	18.08.00	[Hildebrandt]
				Neues Methoden Argumente arcMode, saveGame, arcOwnsMedium
	29.08.00	[Hildebrandt]
				bugfix: "this->inSaveGame = saveGame;"
	------------------------------------------------------------------ */

void zCArchiverGeneric::OpenReadFile (zFILE* fileRead, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags, zBOOL arcOwnsMedium) {
	if (!fileRead) return;
	Close();
	// mode, binaryMode konnen erst im ReadHeader() gesetzt werden
	this->medium			= zARC_MEDIUM_FILE;
	this->accessMode		= zARC_READ;
	this->inSaveGame		= saveGame;
	this->owningMedium		= arcOwnsMedium;
	this->file				= fileRead;
	this->mode				= arcMode;
	this->binaryMode		= (arcMode==zARC_MODE_BINARY);

	ReadHeader				();
	this->binaryMode		= (arcMode==zARC_MODE_BINARY);
	this->debugMessagesOn	= (mode!=zARC_MODE_ASCII_PROPS);
};

void zCArchiverGeneric::RestoreBuffer (void* buffer, const zDWORD size) {
	assert (accessMode==zARC_READ);
	if (medium==zARC_MEDIUM_FILE)	file->   Read (buffer, size);
	else							cbuffer->Read (buffer, size);
};


void zCArchiverGeneric::RestoreStringEOL (zSTRING& string) {
	// MR  020800: Hier wurden in einem normalen Startvorgang zillionen (> 10Mio) Strings
	//				konstruiert und wieder beseitigt.
	//			   Optimierung durch Einführung eines Buffers und blockweisem Übertragen
	char buffer[5001];
	unsigned int Count = 0;

#define CHECK_RESET_COUNTER_AND_FLUSH_BUFFER { if (Count == 5000) \
												{ \
													buffer[Count] = '\0'; \
													string += buffer; \
													Count = 0; \
												} \
											}

	assert (accessMode==zARC_READ);

	// Ende-Markierung: 
	// ASCII :	EOL    (CR oder LF)
	// BINARY:	EOL	   (LF)			oder \0

	string.Clear();

	if (binaryMode) 
	// TABs werden nicht gefiltert
	{
		if (medium==zARC_MEDIUM_FILE) {
			file->Read (buffer+Count, sizeof(buffer[0]));
			while ((buffer[Count]!='\0') && (buffer[Count]!='\n')) {
				Count++;
				CHECK_RESET_COUNTER_AND_FLUSH_BUFFER;
				file->Read (buffer+Count, sizeof(buffer[0]));
			};
		} else {
			cbuffer->Read (buffer+Count, sizeof(buffer[0]));
			while ((buffer[Count]!='\0') && (buffer[Count]!='\n')) {
				Count++;
				CHECK_RESET_COUNTER_AND_FLUSH_BUFFER;
				cbuffer->Read (buffer+Count, sizeof(buffer[0]));
			};
		};
		buffer[Count] = '\0';
		string += buffer;
	} else 
	{
		// ASCII Mode - TABS werden gefiltert

		if (medium==zARC_MEDIUM_FILE) {
			file->Read (buffer+Count, sizeof(buffer[0]));
			while ((buffer[Count]!='\n') && (buffer[Count]!='\r')) {
				// tabs rausfiltern
				if (buffer[Count]!='\t')	
					Count++;
				CHECK_RESET_COUNTER_AND_FLUSH_BUFFER;
				file->Read (buffer+Count, sizeof(buffer[0]));
			};
		} else {
			cbuffer->Read (buffer+Count, sizeof(buffer[0]));
			while ((buffer[Count]!='\n') && (buffer[Count]!='\r')) {
				// tabs rausfiltern
				if (buffer[Count]!='\t')	
					Count++;
				CHECK_RESET_COUNTER_AND_FLUSH_BUFFER;
				cbuffer->Read (buffer+Count, sizeof(buffer[0]));
			};
		};
		buffer[Count] = '\0';
		string += buffer;
	};
};


 
void zCArchiverGeneric::RestoreString0 (zSTRING& string) {
	assert (accessMode==zARC_READ);
	// Ende-Markierung: \0
	RestoreStringEOL (string);
};

zDWORD zCArchiverGeneric::RestoreGetPos () {
	assert (accessMode==zARC_READ);
	if (medium==zARC_MEDIUM_FILE)	return file->Pos();
	else							return cbuffer->GetPos();
};

void zCArchiverGeneric::RestoreSeek (const zDWORD newPos) {
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

/*	------------------------------------------------------------------
	zCArchiverGeneric::zCArchiverGeneric
	18.08.00	[Hildebrandt]
				Anpassung an Benutzung des zCArchiverFactory
	03.11.00	[Speckels]
				Leerzeilen vor "objects"-Eintrag weren überlesen
	------------------------------------------------------------------ */

void zCArchiverGeneric::ReadHeader () 
{
	// setzt 'mode', 'binaryMode', 'inSaveGame'
	zSTRING s;

	// "objects"-Eintrag suchen [SPECKELS]-> Leerzeilen werden überlesen
	s.Clear();
	while (s.IsEmpty()) RestoreStringEOL(s);		
	
	zSTRING cmd = s.PickWord(1, " ", " ");
	zSTRING arg = s.PickWord(2, " ", " ");
	if (strcmp(cmd.ToChar(), "objects")==0) 
	{
		zDWORD numObj	= arg.ToInt();
		CheckObjectListSize (numObj);
	} 
	else	
	{
		zERR_FATAL ("D: zCArchiverGeneric: cannot read archive, 'objects' keyword expected");
	};


	// "end"
	RestoreStringEOL	(s);

	// EOL
	RestoreStringEOL	(s);
	posHeaderEnd		= RestoreGetPos();
};

void zCArchiverGeneric::CheckObjectListSize (int numRequired) 
{
	int numOld = objectList.GetNum();
	if (numRequired<=numOld)	return;

	// etwas mehr Platz in der Liste bereitstellen, neue Plaetze mit 0 fuellen
	objectList		.AllocAbs			(numRequired + (numRequired/2));
	objectList		.MarkNumAllocUsed	();
	for (int i=numOld; i<objectList.GetNum(); i++)
		objectList[i] = 0;
};

zCObject* zCArchiverGeneric::CreateObject (const zSTRING& className) 
{
	// Ein WriteObjectPtr auf ein NULL-Object liefert einen Klassen Chunk mit dem className '%'
	zCClassDef *classDef = GetClassDefByString (className);
	if (!classDef) return 0;

	zCObject *object = classDef->CreateNewInstance();
	if (!object)
		zERR_FAULT("D: zArchiver(zCArchiverGeneric::CreateObject): could not create object for: "+className);
	return object;
};

zCClassDef* zCArchiverGeneric::GetClassDefByString (const zSTRING& className) 
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

void zCArchiverGeneric::ReadChunkStartASCII (const char* chunkName, zSTRING& resultLine) 
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

zBOOL zCArchiverGeneric::ReadChunkStart (const char* chunkName) {
	// intern
	// Ein Chunk mit spez. Namen wird gesucht und geoeffnet
	// gelesener Chunk liegt danach auf dem chunkStack
	zTChunkRecord	chunk;

	if (binaryMode) {
		// binary: es wird davon ausgegangen, dass der gewuenschte Chunk 
		// der naechste ist (relat. unsicher, aber schnell)
		// FIXME: evtl. hier eine CHUNK_START Kennung einfuehren (z.B. 0x12345678, oder 0xDEADFACE (hihi))
		chunk.startPos		= RestoreGetPos();
							
		RestoreBuffer		(&chunk.size		, sizeof(chunk.size));
		RestoreBuffer		(&chunk.version		, sizeof(chunk.version));
		RestoreBuffer		(&chunk.objectIndex	, sizeof(chunk.objectIndex));
		RestoreString0		(chunk.name);
		RestoreString0		(chunk.className);

		if ((chunkName) && (chunkName[0]) && (chunk.name!=chunkName)) {
			RestoreSeek (chunk.startPos);
			return FALSE;
		};
	} else {
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
	};
	chunkStack.InsertEnd (chunk);
	return TRUE;
};

zBOOL zCArchiverGeneric::ReadChunkStart (zSTRING& chunkName, zWORD& chunkVersion) {
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

zBOOL zCArchiverGeneric::ReadChunkStartNamed (const char* chunkName, zWORD& chunkVersion) {
	// interface
	zBOOL found		= ReadChunkStart (chunkName);
	if (found) {
		chunkVersion	= chunkStack[chunkStack.GetNum()-1].version;
	};
	return found;
};

zWORD zCArchiverGeneric::GetCurrentChunkVersion()
{
	// to query class archive version within Archive()/Unarchive()
	if (chunkStack.GetNum()<=0)	return 0;
	return chunkStack[chunkStack.GetNum()-1].version;
};

void zCArchiverGeneric::ReadChunkEnd () {
	// Falls ein Objekt nicht alle Daten des Chunks liest (z.B. weil es den Chunk einer
	// eigentlich abgeleiteten Klasse liest, die aber nicht erzeugt werden konnte), muss
	// der Rest hier übersprungen werden.
	SkipChunk (TRUE);
};

zCObject* zCArchiverGeneric::ReadObject (const char* chunkName, zCObject* objectUseThis) 
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
			zERR_WARNING ("D: zArchiver(::ReadObject): found an objectPtr in file, tried to write this to an 'objectUseThis'");

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

        if (!objectUseThis) // [Moos] wenn das Objekt schon da war, dann brauchen wir kein AddRef mehr darauf.
			object->AddRef();

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
				if (!binaryMode)
				{
					// der robuste ASCII Modus erlaubt das Weiterlesen
					zERR_WARNING ("D: zArchiver(::ReadObject): class from file does not match class from 'objectUseThis', file: "+((classDef) ? classDef->GetClassName_() : "%")+", obj: "+objectUseThis->GetClassName_());
				} else 
				{
					// der Binary Mode ist hier strikter: skipChunk noetig
					zERR_FAULT ("D: zArchiver(::ReadObject): skipping object-chunk, class from file does not match class from 'objectUseThis', file: "+((classDef) ? classDef->GetClassName_() : "%")+", obj: "+objectUseThis->GetClassName_());
					skipChunk = TRUE;
					
					// das 'objectUseThis' wird dennoch in die objectList eingetragen, damit spaetere Referenzen 
					// auf dieses Objekt aufgeloest werden koennen
					zDWORD index			= chunkStack[chunkStack.GetNum()-1].objectIndex;
					CheckObjectListSize		(index+1);

                    zERR_ASSERTT_STRICT(!objectList[index], "Archiver tried to overwrite object in its list. Did you try to load an incompatible savegame?");
					objectList[index]		= objectUseThis->AddRef(); // [Moos] FIXME: vielleicht hier doch KEIN Addref???
				};
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
	} else 
	{
		// Versions-Check
		if (object->GetArchiveVersionSum()!=chunkStack[chunkStack.GetNum()-1].version) 
		{
			if (binaryMode) {
				zERR_WARNING ("D: Archiver(::ReadObject): skipping object-chunk, tried to read object-chunk with out-of-date version: "+chunkStack[chunkStack.GetNum()-1].className);
				SkipChunk (TRUE);
				if (!objectUseThis) object->Release();		// Objekt loeschen, falls es selbst erzeugt worden ist
				object = objectUseThis;
				return object;
			} else {
#ifndef ZDONT_WARN_OLD_VERSION
//				zerr.Warning ("D: Archiver(::ReadObject): tried to read object-chunk with out-of-date version: "+chunkStack[chunkStack.GetNum()-1].className);
#endif
			};
		};

		// In Liste unarchived Objekte eintragen
		zDWORD index			= chunkStack[chunkStack.GetNum()-1].objectIndex;
		CheckObjectListSize		(index+1);

        zERR_ASSERTT_STRICT(!objectList[index] || !index, "Archiver tried to overwrite object in its list. Did you try to load an incompatible savegame?");
        zRELEASE            (objectList[index]);
		objectList[index]		= object->AddRef();

		object->Unarchive		(*this);
		ReadChunkEnd			();		// entfernt vom chunkstack
	};

	return object;
};

zCObject* zCArchiverGeneric::ReadObject (zCObject* objectUseThis) {
	return ReadObject ("", objectUseThis);
}; 

void zCArchiverGeneric::SkipChunk (const zBOOL removeFromChunkStack) {
	// skipt einen Chunk, dessen Header bereits gelesen wurde, und dessen Eintrag auf dem ChunkStack liegt
	if (chunkStack.GetNum()<=0) return;
	if (binaryMode) 
	{
		const zDWORD newPos	= chunkStack[chunkStack.GetNum()-1].startPos + chunkStack[chunkStack.GetNum()-1].size;
		RestoreSeek		(newPos);
	} 
	else 
	{
		zSTRING line;
		int		level	= 1;
		int		ctr		= 0;
		do 
		{
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
			if (ctr>1) 
			{
				warnEntrysNotRead	= TRUE;
			};
		} 
		while (level>0);
		if (ctr>1)
			warnEntrysNotRead	= TRUE;
	};
	
	//
	if (removeFromChunkStack)
		chunkStack.RemoveOrderIndex (chunkStack.GetNum()-1);
};

zBOOL zCArchiverGeneric::ReadEntryASCII (const char* entryName, zSTRING& resultValue) {
	// "name=type:value"
	const zSTRING	trenn = " =\t";
	zSTRING			line;
	zSTRING			name;
	int				numCycles	= noReadSearchCycles ? 1 : 0;

	do {
		RestoreStringEOL	(line);

		// einen ChunkStart/End am Wickel ?
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
				RestoreSeek			(chunkStack[chunkStack.GetNum()-1].startPos);
				
				// bereits einmal den Chunk komplett durchsucht ?
				if (numCycles==1) 
				{
					resultValue.Clear();
					warnEntryNotFound = TRUE;
#ifndef ZDONT_WARN_ENTRY_NOT_FOUND
					zERR_WARNING ("D: expected entry not found: "+zSTRING(entryName));
                    static int s_warnCount=0;
                    if (zSTRING(entryName) != zSTRING("pack")) s_warnCount ++;
                    if (s_warnCount == 100)
                        zERR_FAULT("M: really many entries not found! The archive is probably outdated.");
#endif
					return FALSE;
				};
				
				// den Chunk von vorne durchsuchen
				numCycles++;
			};
		} 
		else 
		{
			if (line.IsEmpty()) continue;
			// den passenden Entry gefunden ?
			name = line.PickWord (1, trenn, trenn);
			if (strcmp(name.ToChar(), entryName)==0) 
			{
				// alles nach dem ersten ':' ist das Ergebnis
				for (int i=0; i<line.Length(); i++) 
				{
					if (line[i]==':') 
					{
						resultValue = line;
						resultValue.Copy (i+1, line.Length());
						break;
					};
				};
				break;
			} 
			else 
			{
				warnWrongEntryOrder	= TRUE;
			};
		};
	} 
	while(1);
	return TRUE;
};

float zCArchiverGeneric::ReadFloat (const char* entryName) {
	float value;
	ReadFloat (entryName, value);
	return value;
};

zVEC3 zCArchiverGeneric::ReadVec3 (const char* entryName) {
	zVEC3 value;
	ReadVec3 (entryName, value);
	return value;
};

int zCArchiverGeneric::ReadInt (const char* entryName) {
	int value;
	ReadInt (entryName, value);
	return value;
};

zBYTE zCArchiverGeneric::ReadByte (const char* entryName) {
	zBYTE value;
	ReadByte (entryName, value);
	return value;
};

zWORD zCArchiverGeneric::ReadWord (const char* entryName) {
	zWORD value;
	ReadWord (entryName, value);
	return value;
};

zBOOL zCArchiverGeneric::ReadBool (const char* entryName) 
{
	zBOOL value;
	ReadBool (entryName, value);
	return value;
};

zSTRING zCArchiverGeneric::ReadString (const char* entryName) 
{
	zSTRING s;
	ReadString (entryName, s);
	return s;
};

zCOLOR zCArchiverGeneric::ReadColor (const char* entryName) 
{
	zCOLOR value;
	ReadColor (entryName, value);
	return value;
};

int zCArchiverGeneric::ReadEnum (const char* entryName) 
{
	int value;
	ReadEnum (entryName, value);
	return value;
};

void zCArchiverGeneric::ReadRaw (const char* entryName, void* buffer, const zDWORD size) {
	if (binaryMode) 
	{
		RestoreBuffer	(buffer, size);
	} 
	else 
	{
		ReadEntryASCII	(entryName, tmpResultValue);

		int strLen		= tmpResultValue.Length() / 2; 
		if (strLen>0) 
		{
			if (size!=strLen) 
			{
				zERR_FAULT ("D: zArchiver(zCArchiverGeneric::ReadRaw): size of requested data does not equal size of available data: "+zSTRING(size)+"/"+zSTRING(strLen));
			};

			zBYTE*	destBuffer	= (zBYTE*)buffer;
			char*	charBuffer	= tmpResultValue.ToChar();
			int		val;

			for (int i=0; i<strLen; i++) 
			{
				sscanf		(charBuffer, "%2x", &val);
				*destBuffer	= zBYTE(val);
				charBuffer	+= 2;
				destBuffer++;
			};
		};
	};
};

void zCArchiverGeneric::ReadRawFloat (const char* entryName, void* buffer, const zDWORD size) {
	if (binaryMode) {
		RestoreBuffer	(buffer, size);
	} else {
		ReadEntryASCII	(entryName, tmpResultValue);

		int strLen		= size / sizeof(float);		// numFloats

		float*	destBuffer	= (float*)buffer;
		for (int i=1; i<=strLen; i++) {
			*destBuffer	= tmpResultValue.PickWord (i, " ", " ").ToFloat();
			destBuffer++;
		};
	};
};


// Safe Reading
// (does not destroy value, if entry is not present)

/*	------------------------------------------------------------------
	zCArchiverGeneric::ReadXXX
	29.09.00	[Hildebrandt]	
				Fixed incorrect behavior, now the refPar 'value' ist not overwritten
				if the entryName is not found within the chunk (ascii mode only)
	------------------------------------------------------------------ */

void zCArchiverGeneric::ReadFloat (const char* entryName, float& value) {
	if (binaryMode) {
		RestoreBuffer ((void*)(&value), sizeof(value));
	} else {
		if (ReadEntryASCII (entryName, tmpResultValue))
			value = tmpResultValue.ToFloat();
	};
};

void zCArchiverGeneric::ReadVec3 (const char* entryName, zVEC3& value) {
	if (binaryMode) {
		RestoreBuffer	((void*)(&value), sizeof(value));
	} else {
		if (ReadEntryASCII	(entryName, tmpResultValue))
			sscanf		(tmpResultValue.ToChar(), "%f %f %f", &value[0], &value[1], &value[2]);
	};
};

void zCArchiverGeneric::ReadInt (const char* entryName, int& value) {
	if (binaryMode) {
		RestoreBuffer ((void*)(&value), sizeof(value));
	} else {
		if (ReadEntryASCII	(entryName, tmpResultValue))
			value		= tmpResultValue.ToInt();
	};
};

void zCArchiverGeneric::ReadByte (const char* entryName, zBYTE& value) {
	if (binaryMode) {
		RestoreBuffer	((void*)(&value), sizeof(value));
	} else {
		if (ReadEntryASCII	(entryName, tmpResultValue))
			value		= zBYTE(tmpResultValue.ToInt());
	};
};

void zCArchiverGeneric::ReadWord (const char* entryName, zWORD& value) {
	if (binaryMode) {
		RestoreBuffer	((void*)(&value), sizeof(value));
	} else {
		if (ReadEntryASCII	(entryName, tmpResultValue))
			value		= zWORD(tmpResultValue.ToInt());
	};
};

void zCArchiverGeneric::ReadBool (const char* entryName, zBOOL& value) {
	if (binaryMode) {
		zBYTE b;
		RestoreBuffer ((void*)(&b), sizeof(b));
		value = zBOOL(b);
	} else {
		if (ReadEntryASCII	(entryName, tmpResultValue))
			value		= zBOOL(tmpResultValue.ToInt());
	};
};

void zCArchiverGeneric::ReadString (const char* entryName, zSTRING& value) {
	if (binaryMode)	RestoreString0	(value);
	else			ReadEntryASCII	(entryName, value);		// FIXME: nicht wert-erhaltend!
};

void zCArchiverGeneric::ReadColor (const char* entryName, zCOLOR& value) {
	if (binaryMode) {
		RestoreBuffer	((void*)(&value), sizeof(value));
	} else {
		if (ReadEntryASCII	(entryName, tmpResultValue))
		{
			int				color[4];
			sscanf			(tmpResultValue.ToChar(), "%d %d %d %d", &color[0], &color[1], &color[2], &color[3]);
			value.r			= zBYTE(color[0]);
			value.g			= zBYTE(color[1]);
			value.b			= zBYTE(color[2]);
			value.alpha		= zBYTE(color[3]);
		};
	};
};

void zCArchiverGeneric::ReadEnum (const char* entryName, int& value) {
	if (binaryMode) 
	{
		value = ReadByte	(entryName);		// Platz sparen im binaryMode
	} else {
		if (ReadEntryASCII	(entryName, tmpResultValue))
			value		= tmpResultValue.ToInt();
	};
};

// =======================================================================================================================

void zCArchiverGeneric::TestClassIntegrity (zTTestClassCallback *callback) 
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
	//					case 2:	arcWrite->OpenWriteBuffer	(zCArchiverGeneric::zARC_MODE_ASCII_PROPS);break;	// FIXME: macht wegen den "groupBegin/End" noch Ärger..
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
							zCArchiverGeneric	*arcReadGen	= dynamic_cast<zCArchiverGeneric*>(arcRead);
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
							zCArchiverGeneric	*arcReadGen	= dynamic_cast<zCArchiverGeneric*>(arcRead);
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

				if (warnEntryNotFound)		
					zERR_FAULT ("D: ARC: expected entry not found ! Class "+classDef->GetClassName_()+", Testmode "+zSTRING(j));
				if (warnEntrysNotRead)		
					zERR_FAULT ("D: ARC: entry was not read ! Class "+classDef->GetClassName_()+", Testmode "+zSTRING(j));
				if (warnWrongEntryOrder)	
					zERR_FAULT ("D: ARC: order differs: reading/writing entrys ! Class "+classDef->GetClassName_()+", Testmode "+zSTRING(j));
				
			};
		};
	};
	/*

	- in allen Modi testen, ascii, ascii_props (mit/ohne savedGame)

	- musste Entry skippen, um richtigen Eintrag zu finden
	- Entry nicht gefunden
	- am Ende des Lesen sind noch bytes übrig
	*/
};

zCObject*	zCCFASTCALL zCArchiverGeneric::GetParentObject() 
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
