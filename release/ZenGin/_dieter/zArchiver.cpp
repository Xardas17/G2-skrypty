/******************************************************************************** 
 
     $Workfile:: zArchiver.cpp        $                $Date:: 7.02.01 14:38    $
     $Revision:: 25                   $             $Modtime:: 7.02.01 12:40    $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created:

 * $Log: /current_work/ZenGin/_Dieter/zArchiver.cpp $
 * 
 * 25    7.02.01 14:38 Moos
 * 
 * 24    7.02.01 10:36 Moos
 * 
 * 23    25.01.01 12:14 Moos
 * 
 * 22    21.09.00 0:36 Hildebrandt
 * 
 * 21    21.09.00 0:32 Rueve
 * 
 * 20    15.09.00 16:31 Hildebrandt
 * 
 * 19    15.09.00 16:08 Hoeller
 * 
 * 18    22.08.00 15:18 Hildebrandt
 * 
 * 17    21.08.00 21:48 Hildebrandt
 * 
 * 16    21.08.00 19:42 Hildebrandt
 * 
 * 15    21.08.00 17:18 Hildebrandt
 * 
 * 14    16.08.00 21:41 Hoeller
 * 
 * 13    8.08.00 14:03 Hoeller
 * 
 * 12    7.08.00 16:42 Hoeller
 * 
 * 11    3.08.00 13:23 Hoeller
 * 
 * 10    21.07.00 15:10 Hildebrandt
 * 
 * 9     21.07.00 14:28 Hildebrandt
 * 
 * 8     6.07.00 13:33 Hildebrandt
 * 
 * 5     9.05.00 21:14 Hildebrandt
 * zenGin 089h
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 13    22.03.00 2:58 Hildebrandt
 * zenGin 088a
 * 
 * 12    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 11    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 9     14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 8     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 6     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
///  author   Author: Hildebrandt
/// @version $Revision: 25 $ ($Modtime: 7.02.01 12:40 $)

#include <zCore.h>
#include <zArchiver.h>
#include <zArchiverGeneric.h>
#include <zArchiver2.h>
#include <zBuffer.h>
#include <windows.h>

#include <zAccount.h>

#ifdef ZENGINE_DEBUG
	#define ZDONT_WARN_OLD_VERSION
	#define ZDONT_WARN_ENTRY_NOT_FOUND
#endif


zCLASS_DEFINITION_ABSTRACT	( zCArchiver		, zCObject	, 0			)


// =======================================================================================================================

static const zSTRING s_arcHeaderTag			= "ZenGin Archive";
static const zSTRING s_arcModeNames[zARC_MODE_COUNT] = 
{
	zSTRING("BINARY"),
	zSTRING("ASCII"),
	zSTRING("ASCII_PROPS"),
	zSTRING("BIN_SAFE"),
};


// =======================================================================================================================
// zCArchiverFactory
// =======================================================================================================================

zCArchiverFactory zarcFactory;

// ==============================
// Read
// ==============================

/*	------------------------------------------------------------------
	zCArchiverFactory::EndOfArchive
	21.09.00	[Hildebrandt]	
				Typecast auf int, damit der IntelCompiler nicht meckert: GetSize()-GetPos()
	------------------------------------------------------------------ */

zBOOL zCArchiverFactory::EndOfArchive(zCBuffer* buffer, zFILE* file)
{
	zERR_ASSERT (((buffer!=0) || (file!=0)) && !((buffer!=0) && (file!=0)));
	// FIXME: hack
	if (file)		return file->Eof() || file->Pos()+3>file->Size();
	else			return (int(buffer->GetSize()) - int(buffer->GetPos()))<0;
};

void zCArchiverFactory::ReadLine (zSTRING& line, zCBuffer* buffer, zFILE* file)
{
	zERR_ASSERT (((buffer!=0) || (file!=0)) && !((buffer!=0) && (file!=0)));
	if (buffer)		
	{
		enum	{ BUFFER_SIZE = 1024 };
		char	charBuffer[BUFFER_SIZE];
		int		count	= 0;
		buffer->Read (charBuffer + count, 1);
		while (charBuffer [count]!='\n') {
			if (count>=BUFFER_SIZE-1) {
				zERR_FAULT ("D: zCArchiverFactory: corrupt archive header, line too long");
				break;
			};
			++count;
			buffer->Read (charBuffer + count, 1);
		};
		charBuffer[count] = '\0';
		line	= charBuffer;
	} else {
		file->Read (line);				// terminates with 0x0a
	};
};

void zCArchiverFactory::ReadLineArg (zSTRING& line, zSTRING& arg, zCBuffer* buffer, zFILE* file)
{
	ReadLine (arg, buffer, file);
	line	= arg.PickWord	(1, " ", " ");
	arg		= arg.PickWord	(2, " ", " ");
};

void zCArchiverFactory::ReadHeader (int				arcFlags,	// in
									zCBuffer*		buffer,		// in
									zFILE*			file,		// in
									zCArchiver*		&arc,		// out
									zTArchiveMode	&arcMode,	// out
									zBOOL			&inSaveGame	// out
									)
{
	zERR_ASSERT (((buffer!=0) || (file!=0)) && !((buffer!=0) && (file!=0)));

	arc			= 0;
	arcMode		= zTArchiveMode(0);
	inSaveGame	= FALSE;
	int			formatVers=0;
	zSTRING		line, arg;

	// 1) Tag
	ReadLine		(line, buffer, file);
	if (line!=s_arcHeaderTag) {
		zERR_FAULT ("D: zCArchiverFactory(zCArchiverFactory::ReadHeader): file ist not a ZenGin Archive");
		return;
	};

	// 2) File-version	
	ReadLineArg		(line, arg, buffer, file);
	formatVers		= arg.ToInt();
	if (formatVers>0)
	{
		// 3) ClassName
		ReadLine		(line, buffer, file);
		zCClassDef		*classDef= zCObject::GetClassDef (line);
		if (!classDef)	{
			zERR_FAULT ("D: zCArchiverFactory(zCArchiverFactory::ReadHeader): could not create specified archiver");
			return;
		};
		arc = static_cast<zCArchiver*>(classDef->CreateNewInstance());
	} else
	{
		arc = zNEW(zCArchiverGeneric);
	};

	// 4) arcMode
	ReadLine		(line, buffer, file);
	for (int i=0; i<zARC_MODE_COUNT; i++)
	{
		if (line==s_arcModeNames[i]) {
			arcMode = zTArchiveMode(i);
			break;
		};
	};
	if (i>=zARC_MODE_COUNT) {
		zERR_FAULT ("D: zCArchiverFactory(zCArchiverFactory::ReadHeader): unknown arcMode");
		return;
	};

	// ============================================================

	// parsing Header
	zDWORD mediumPos;
	do {
		if (file)	mediumPos=file->Pos();
		else		mediumPos=buffer->GetPos();
		ReadLineArg		(line, arg, buffer, file);

		if (strcmp(line.ToChar(), "END")==0) break;	else
		if (strcmp(line.ToChar(), "saveGame")==0) 
		{
			// 5) saveGame
			inSaveGame = zBOOL(arg.ToInt());
		} else
		if (strcmp(line.ToChar(), "objects")==0) 
		{
			// Altes Format? 
			// => wieder auf den Anfang dieser Zeile zuruecksetzen, lesen Abbrechen & die abgl. Klasse weiterlesen lassen
			if (formatVers<=0) {
				if (file)	file->Seek		(mediumPos);
				else		buffer->SetPos	(mediumPos);
				return;	// !
			};
		};
	} while (!EndOfArchive(buffer, file));
};

zCArchiver* zCArchiverFactory::CreateArchiverRead (zCBuffer* buffer, int arcFlags)
{
	zERR_ASSERT			(buffer!=0);
	zCArchiver			*arc=0;
	zTArchiveMode		arcMode;
	zBOOL				inSaveGame=FALSE;
	// Buffer resetten
	buffer->SetMode		(READ);
	buffer->SetPos		(0);
	ReadHeader			(arcFlags, buffer, 0, arc, arcMode, inSaveGame);
	if (!arc)			return 0;
	arc->OpenReadBuffer	(*buffer, arcMode, inSaveGame, arcFlags);
	return arc;
};

zCArchiver* zCArchiverFactory::CreateArchiverRead (zFILE* fileRead, int arcFlags)
{
	zERR_ASSERT			(fileRead!=0);
	zCArchiver			*arc=0;
	zTArchiveMode		arcMode;
	zBOOL				inSaveGame=FALSE;
	ReadHeader			(arcFlags, 0, fileRead, arc, arcMode, inSaveGame);
	if (!arc)			return 0;
	arc->OpenReadFile	(fileRead, arcMode, inSaveGame, arcFlags);
	return arc;
};

zCArchiver* zCArchiverFactory::CreateArchiverRead (const zSTRING& fileNameRead, int arcFlags)
{
	zFILE *file = zfactory->CreateZFile (fileNameRead);
	if ((!file->Exists())			||
	    (file->Open()!=zERR_NONE)	||
		(EndOfArchive(0,file)))
	{ 
		zERR_WARNING ("D: zArchiver(::OpenFile): file does not exist: "+fileNameRead);
		delete file;
		return 0;
	};

	zCArchiver			*arc=0;
	zTArchiveMode		arcMode;
	zBOOL				inSaveGame=FALSE;
	ReadHeader			(arcFlags, 0, file, arc, arcMode, inSaveGame);
	if (!arc)			{
		delete file;
		return 0;
	};
	arc->OpenReadFile	(file, arcMode, inSaveGame, arcFlags, TRUE);
	return arc;
};


// ==============================
// Write
// ==============================

void zCArchiverFactory::WriteLine (const zSTRING& line, zCBuffer* buffer, zFILE* file)
{
	zERR_ASSERT (((buffer!=0) || (file!=0)) && !((buffer!=0) && (file!=0)));
	if (buffer)		{ buffer->Write	(line.ToChar(), line.Length());	buffer->WriteByte	('\n'); }
	else			{ file->Write	(line);							file->Write			('\n'); };
};

void zCArchiverFactory::WriteLine (const char* const line, zCBuffer* buffer, zFILE* file)
{
	zERR_ASSERT (((buffer!=0) || (file!=0)) && !((buffer!=0) && (file!=0)));
	if (buffer)		{ buffer->Write	((void*)line, strlen(line));	buffer->WriteByte	('\n'); }
	else			{ file->Write	(line, strlen(line));			file->Write			('\n'); };
};

void zCArchiverFactory::WriteHeader (zCArchiver *arc, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags, zCBuffer* buffer, zFILE* file)
{
	zERR_ASSERT (((buffer!=0) || (file!=0)) && !((buffer!=0) && (file!=0)));

	// 1) Tag
	WriteLine		(s_arcHeaderTag, buffer, file);
	// 2) File-version	
	WriteLine		("ver 1", buffer, file);
	// 3) ClassName
	WriteLine		(arc->GetClassName_(), buffer, file);
	// 4) arcMode
	WriteLine		(s_arcModeNames[arcMode], buffer, file);
	// 5) saveGame
	if (saveGame)	WriteLine		("saveGame 1", buffer, file);
	else			WriteLine		("saveGame 0", buffer, file);

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
		WriteLine (date, buffer, file);

		// user
		// FIXME: WINDOWS**WINDOWS**
		char	userName[200];
		DWORD	userNameSize = sizeof(userName);
		if (GetUserName(userName, &userNameSize)) {
			WriteLine		("user "+zSTRING(userName), buffer, file);
		};
	};
	WriteLine		("END", buffer, file);
};

zCArchiver* zCArchiverFactory::CreateArchiverFromMode	(zTArchiveMode arcMode)
{
	if (arcMode==zARC_MODE_BINARY_SAFE)		
		return zNEW(zCArchiverBinSafe);
	else									
		return zNEW(zCArchiverGeneric);
/*
	if (arcMode==zARC_MODE_BINARY_SAFE)		{ zERR_FAULT ("D: zCArchiverBinSafe not yet supported !"); return 0; }
	else									return zNEW(zCArchiverGeneric);
	*/
};

zCArchiver* zCArchiverFactory::CreateArchiverWrite (zCBuffer* buffer, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags)
{
	zBOOL arcOwnsMedium = (buffer==0);
	if (!buffer) buffer = zNEW(zCBuffer(65536));

	// Buffer resetten
	buffer->SetMode		(WRITE);
	buffer->SetPos		(0);

	zCArchiver *arc		= CreateArchiverFromMode(arcMode);
	WriteHeader			(arc, arcMode, saveGame, arcFlags, buffer, 0);
	arc->OpenWriteBuffer(buffer, arcMode, saveGame, arcFlags, arcOwnsMedium);
	return arc;
};

zCArchiver* zCArchiverFactory::CreateArchiverWrite (zTArchiveMode arcMode, zBOOL saveGame, int arcFlags)
{
	return CreateArchiverWrite ((zCBuffer*)0, arcMode, saveGame, arcFlags);
};

zCArchiver* zCArchiverFactory::CreateArchiverWrite (const zSTRING& fileNameWrite, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags)
{
	zFILE *fileWrite = zfactory->CreateZFile (fileNameWrite);
	if (fileWrite->Create()!=zERR_NONE)	{
		delete fileWrite;
		return 0;
	};

	zCArchiver *arc		= CreateArchiverFromMode(arcMode);
	WriteHeader			(arc, arcMode, saveGame, arcFlags, 0, fileWrite);
	arc->OpenWriteFile	(fileWrite, arcMode, saveGame, arcFlags, TRUE);
	return arc;
};

zCArchiver* zCArchiverFactory::CreateArchiverWrite (zFILE* fileWrite, zTArchiveMode arcMode, zBOOL saveGame, int arcFlags)
{
	zCArchiver *arc		= CreateArchiverFromMode(arcMode);
	WriteHeader			(arc, arcMode, saveGame, arcFlags, 0, fileWrite);
	arc->OpenWriteFile	(fileWrite, arcMode, saveGame, arcFlags);
	return arc;
};


zCObject*	zCCFASTCALL	zCArchiver :: ReadObjectAccount	(const char *file, int line, zCObject* objectUseThis){
    zCObject *ret = ReadObject(objectUseThis);
    zCAccount::Begin();
    zCAccount::Add(ret, file, line, 1);
    return ret;
}


zCObject*	zCCFASTCALL zCArchiver :: ReadObjectAccount	(const char *file, int line, const char* chunkName, zCObject* objectUseThis){
    zCObject *ret = ReadObject(chunkName, objectUseThis);
    zCAccount::Begin();
    zCAccount::Add(ret, file, line, 1);
    return ret;
}


// =======================================================================================================================
