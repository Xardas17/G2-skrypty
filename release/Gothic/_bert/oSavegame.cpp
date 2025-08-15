#include "zcore.h"
#include "zoption.h"
#include "zarchiver.h"
#include "zrenderer.h"
#include "ztexture.h"
#include "zwin32.h"

#include "time.h"

#include "osavegame.h"

extern int APP_VERSION_MAJOR;
extern int APP_VERSION_MINOR;
// [BENDLIN] 1.30
extern int APP_VERSION_POINT;
extern int APP_VERSION_INT;
extern char* APP_NAME;

const int		SAVEGAME_SLOT_NONE			= -3;
const int		SAVEGAME_SLOT_NEW			= -2;
const int		SAVEGAME_SLOT_CURRENT		= -1;
const int		SAVEGAME_SLOT_QUICK			= 0;
const int		SAVEGAME_SLOT_MIN			= 1;
const int		SAVEGAME_SLOT_MAX			= 20;

const zSTRING	SAVEGAME_DIR			= "savegame";
const zSTRING	SAVEGAME_CURRENT_DIR	= "current";
const zSTRING	SAVEGAME_QUICK_DIR		= "quicksave";
const zSTRING	SAVEGAME_EXT   			= "sav";
const zSTRING	SAVEGAME_HEADER_FILE	= "saveinfo.sav";
const zSTRING	SAVEGAME_GLOBAL_FILE	= "savedat.sav";
const zSTRING	SAVEGAME_PIC_FILE		= "savepic.sav";
const zSTRING	SAVEGAME_THUMB_FILE		= "thumb.sav";

zCLASS_DEFINITION	( oCSavegameInfo, zCObject	, 0,	0	)


oCSavegameInfo::oCSavegameInfo()
{
	Init();
}

oCSavegameInfo::oCSavegameInfo(int slotNr)
{	
	Init();
	SetSlot(slotNr);
}

void oCSavegameInfo::Init()
{
	m_SlotNr	= 0;	
	m_TimeDay	= -1;
	m_TimeHour	= 0;
	m_TimeMin	= 0;		
	m_SlotNr	= -1;			
	m_ThumbTex	= 0;
	m_notCompatible = FALSE;

	// [BENDLIN] 1.30
	m_verMajor			= APP_VERSION_MAJOR;
	m_verMinor			= APP_VERSION_MINOR;
	m_verPoint			= APP_VERSION_POINT;
	m_verInt			= APP_VERSION_INT;
	m_verName			= zSTRING(APP_NAME);
	m_PlayTimeSeconds	= 0;
};

zBOOL oCSavegameInfo::DoesSavegameExist()
{
	return m_TimeDay>=0;
};

void oCSavegameInfo::UpdateThumbPic(zCTextureConvert* texCvt)
{
	zERR_ASSERT(zrenderer);

	if (texCvt)
	{				
		// Screenshot konvertieren	
		zCTextureInfo texInfo = texCvt->GetTextureInfo();
		texInfo.texFormat	= zCTexture::CalcNextBestTexFormat(zRND_TEX_FORMAT_RGB_565);
		texInfo.numMipMap	= 1;			
		texInfo.sizeX		= 256;
		texInfo.sizeY		= 256;		
		texCvt->ConvertTextureFormat(texInfo);		

		zCTexture* tex = zrenderer->CreateTexture();		
		zCTextureExchange::CopyContents(texCvt,tex);	

		// Speicherung
				
		zFILE* file = zfactory->CreateZFile(zoptions->GetDirString(DIR_SAVEGAMES)+GetDir()+SAVEGAME_THUMB_FILE);
		if (file->Create()==zERR_NONE)
		{
			zCTextureFileFormatInternal* texFileFormat = zNEW(zCTextureFileFormatInternal);
			texFileFormat->SaveTexture(*file,tex);
			zRELEASE(texFileFormat);
			file->Close();
		};

		zRELEASE(tex);
	}	
};

void oCSavegameInfo::ReloadResources()
{
	zERR_ASSERT(zrenderer);

	zRELEASE(m_ThumbTex);	

	zFILE* file = zfactory->CreateZFile(zoptions->GetDirString(DIR_SAVEGAMES)+GetDir()+SAVEGAME_THUMB_FILE);
	if (file->Exists())
	{
		if (file->Open()==zERR_NONE)
		{			
			m_ThumbTex = zrenderer->CreateTexture();
			zCTextureFileFormatInternal* texFileFormat = zNEW(zCTextureFileFormatInternal);
			texFileFormat->LoadTexture(*file,m_ThumbTex);
			zRELEASE(texFileFormat);		
			file->Close();
		}	
	}
	delete file;file=0;
};	

void oCSavegameInfo::CleanResources()
{
	zRELEASE(m_ThumbTex);
};

void oCSavegameInfo::SetSlot(int slotNr)
{
	m_SlotNr			= slotNr; 
	m_Dir.Clear();
	m_notCompatible		= FALSE;
	m_PlayTimeSeconds	= 0;
	// [BENDLIN] 1.30
	m_verMajor			= APP_VERSION_MAJOR;
	m_verMinor			= APP_VERSION_MINOR;
	m_verPoint			= APP_VERSION_POINT;
	m_verInt			= APP_VERSION_INT;
	m_verName			= zSTRING(APP_NAME);

	// Verzeichnis setzen
	// [BENDLIN] quickload/quicksave
	if (slotNr==SAVEGAME_SLOT_QUICK) 
	{
		m_Dir	= SAVEGAME_QUICK_DIR+"\\";
	}
	else if ((m_SlotNr>=SAVEGAME_SLOT_MIN) && (m_SlotNr<=SAVEGAME_SLOT_MAX))
	{
		m_Dir	= SAVEGAME_DIR+zSTRING(m_SlotNr)+"\\";
	}
}

oCSavegameInfo::~oCSavegameInfo()
{	
	zRELEASE(m_ThumbTex);
}


void oCSavegameInfo::Archive	(zCArchiver &arc)
{
	zCObject::Archive(arc);
	
	SYSTEMTIME	st;
	GetLocalTime (&st);
    m_SaveDate =zSTRING(st.wDay )+"."+zSTRING(st.wMonth) +"."+zSTRING(st.wYear)+" - "+
				zSTRING(st.wHour)+":";
	if (st.wMinute<10) m_SaveDate+="0";
	m_SaveDate+=zSTRING(st.wMinute);

	arc.WriteString		("Title",			m_Name);
	arc.WriteString		("WorldName",		m_WorldName);	
	arc.WriteInt		("TimeDay",			m_TimeDay);
	arc.WriteInt		("TimeHour",		m_TimeHour);
	arc.WriteInt		("TimeMin",			m_TimeMin);		
	arc.WriteString		("SaveDate",		m_SaveDate);	
	arc.WriteInt		("VersionMajor",	APP_VERSION_MAJOR);
	arc.WriteInt		("VersionMinor",	APP_VERSION_MINOR);	

	arc.WriteInt		("PlayTimeSeconds",	m_PlayTimeSeconds);			

	// [BENDLIN] 1.30
	arc.WriteInt		("VersionPoint",	APP_VERSION_POINT);
	arc.WriteInt		("VersionInt",		APP_VERSION_INT);
	arc.WriteString		("VersionAppName",	zSTRING(APP_NAME));

	m_notCompatible = FALSE;
};


void oCSavegameInfo::Unarchive	(zCArchiver &arc)
{
	zCObject::Unarchive(arc);

	arc.ReadString		("Title",			m_Name);
	arc.ReadString		("WorldName",		m_WorldName);	
	arc.ReadInt			("TimeDay",			m_TimeDay);
	arc.ReadInt			("TimeHour",		m_TimeHour);
	arc.ReadInt			("TimeMin",			m_TimeMin);		
	arc.ReadString		("SaveDate",		m_SaveDate);
	arc.ReadInt			("VersionMajor",    m_verMajor);	
	arc.ReadInt   		("VersionMinor",	m_verMinor);
	arc.ReadInt  		("PlayTimeSeconds",	m_PlayTimeSeconds);	

	// [BENDLIN] 1.30
	m_verPoint = -1;
	m_verInt = -1;
	m_verName.Clear();
	if ((m_verMajor > 1) ||
		((m_verMajor == 1) && (m_verMinor >= 30)))
	{
		arc.ReadInt		("VersionPoint",	m_verPoint);
		arc.ReadInt		("VersionInt",		m_verInt);
		arc.ReadString	("VersionAppName",	m_verName);
	}

#ifndef COMPILING_SPACER
	m_notCompatible = FALSE;
	m_notCompatible |= ((m_verMajor==1)  &&  (m_verMinor<=27));	// bis 1.27 (vor dem Goldmaster)
		
	if (m_notCompatible)
	{
		zSTRING sVer = zSTRING(m_verMajor)+":"+zSTRING(m_verMinor);
		zSTRING gVer = zSTRING(APP_VERSION_MAJOR)+":"+zSTRING(APP_VERSION_MINOR);
		zERR_WARNING("B: VER: Version of savegame \""+m_Name+"\" ("+sVer+") is incompatible to current version ("+gVer+")");
	};

#endif
};

zSTRING	oCSavegameInfo::GetGameTime()
{
	zSTRING s="";
	if (m_TimeDay>=0)
	{
		s+=zSTRING(m_TimeDay);
		s+=" - ";
		s+=zSTRING(m_TimeHour)+":";
		if (m_TimeMin<10) s+="0";
		s+=zSTRING(m_TimeMin);
	}
	return s;
};



oCSavegameManager::oCSavegameManager()
{
	localInfo = zNEW(oCSavegameInfo(0));
	for (int i=0;i<SAVEGAME_SLOT_MAX+1;i++) 
	{
		oCSavegameInfo* newInfo = zNEW(oCSavegameInfo(i));
		infoList.InsertAtPos(newInfo,i);
	}
	initialized=false;
};

oCSavegameManager::~oCSavegameManager()
{
	zRELEASE(localInfo);
	oCSavegameInfo* info=0;
	for (int i=0;i<infoList.GetNumInList();i++) 
	{
		info = infoList[i];
		infoList[i]=0;
		zRELEASE(info);
	}
};

void oCSavegameManager::Init()
{
	// Analyse Savegame-Verzeichnis	
	if (!initialized)
	{
		zERR_MESSAGE(3,zERR_BEGIN,"B: SG: Initializing savegame-manager ...");

		zSTRING filename;
		zFILE*	file = 0;
		
		// [BENDLIN] Addon - Create DIR_SAVEGAMES and SAVEGAME_CURRENT_DIR
		filename = zoptions->GetDirString(DIR_SAVEGAMES);
		file = zfactory->CreateZFile(filename);
		if (file)
		{
			file->DirCreate();
			file->Close();
			delete file; file = 0;
		}
		filename = zoptions->GetDirString(DIR_SAVEGAMES) + SAVEGAME_CURRENT_DIR + "\\";
		file = zfactory->CreateZFile(filename);
		if (file)
		{
			file->DirCreate();
			file->Close();
			delete file; file = 0;
		}
		
		zoptions->ChangeDir(DIR_SAVEGAMES);

		for (int i=0;i<infoList.GetNumInList();i++)
		{			
			oCSavegameInfo* info = GetSavegame(i); 
			if (info)
			{				
				zBOOL found=FALSE;
				info->SetName("---");				
				info->UpdateThumbPic(0);

				// Info lesen
				filename	= zoptions->GetDirString(DIR_SAVEGAMES) + info->GetDir() + SAVEGAME_HEADER_FILE;
				file		= zfactory->CreateZFile(filename);
				if (file->Exists())
				{									
					file->Open();
					zCArchiver* arc = zarcFactory.CreateArchiverRead(file);
					if (arc)
					{
						arc->ReadObject(info);
						arc->Close();
						zRELEASE(arc);
					}
					file->Close();										

					found=TRUE;
					zERR_MESSAGE(5,0,"B: BS: Savegame "+zSTRING(i)+" found: \""+info->GetName()+"\"");
				}
				delete file;file=0;				
			}
		};
		initialized=true;
		zERR_MESSAGE(3,zERR_END,"");
	}	
};


void oCSavegameManager::Reinit() 
{ 	
	initialized=false;
	Init();
};

void oCSavegameManager::CleanResources()
{
	oCSavegameInfo* info = 0;
	for (int i=0;i<infoList.GetNumInList();i++)
	{
		info = GetSavegame(i);
		if (info) info->CleanResources();
	};
};



void oCSavegameManager::SetAndWriteSavegame(int slotNr, oCSavegameInfo* info)
{	
	// [BENDLIN] qicksave/quickload
	zERR_ASSERT(slotNr>=0);
	zERR_ASSERT(slotNr<infoList.GetNumInList());
	zERR_ASSERT(info);	

	oCSavegameInfo* oldInfo = infoList[slotNr];
	infoList[slotNr] = info;info->AddRef();
	zRELEASE(oldInfo);

	zSTRING	filename;
	zFILE*	file = 0;

	//
	// Schreibe Info-File fuer dieses Savegame
	//
	filename	= zoptions->GetDirString(DIR_SAVEGAMES) + info->GetDir();
	file		= zfactory->CreateZFile(filename);
	file->DirCreate();
	
		filename = filename + SAVEGAME_HEADER_FILE;		
		zCArchiver* arc = zarcFactory.CreateArchiverWrite(filename,zARC_MODE_ASCII);
		zERR_ASSERT(arc);
		arc->WriteObject(info);
		arc->Close();
		zRELEASE(arc);

	file->Close();
	delete file;file=0;	
};

oCSavegameInfo*	oCSavegameManager::GetSavegame(int slotNr)
{
	if (slotNr<0)
	{
		localInfo->SetSlot(slotNr);
		return localInfo;
	}
	else
	{
		return infoList[slotNr];
	}
};

void oCSavegameManager::CopyToCurrent(int slotNr)
{	
	// [BENDLIN] qicksave/quickload
	zERR_ASSERT(slotNr>=0);
	zERR_ASSERT(slotNr<infoList.GetNumInList());
	
	zERR_MESSAGE(4,0,"B: SG: Copying savegame to current-dir ...");	
			
	zSTRING	dirSlot			= infoList[slotNr]->GetDir();
	zSTRING dirSlotCurrent	= GetSlotDirName(SAVEGAME_SLOT_CURRENT);
	zoptions->ChangeDir(DIR_SAVEGAMES);
	Dir_Copy(dirSlot,dirSlotCurrent);
};


void oCSavegameManager::CopyFromCurrent(int slotNr)
{	
	// [BENDLIN] qicksave/quickload
	zERR_ASSERT(slotNr>=0);
	zERR_ASSERT(slotNr<infoList.GetNumInList());
	
	zERR_MESSAGE(4,0,"B: SG: Copying current-dir to savegame...");
			
	zSTRING	dirSlot			= infoList[slotNr]->GetDir();
	zSTRING dirSlotCurrent	= GetSlotDirName(SAVEGAME_SLOT_CURRENT);
	zoptions->ChangeDir(DIR_SAVEGAMES);
	Dir_Copy(dirSlotCurrent, dirSlot);
};



void oCSavegameManager::ClearCurrent()
{
	zoptions->ChangeDir(DIR_SAVEGAMES);
	Dir_Clear(SAVEGAME_CURRENT_DIR + "\\");
};

zSTRING	oCSavegameManager::GetSlotDirName(int slotNr)
{
	zSTRING s;	
	// [BENDLIN] qicksave/quickload
	if (slotNr==SAVEGAME_SLOT_QUICK) 
	{
		s += SAVEGAME_QUICK_DIR + "\\";
	}
	else if ((slotNr>=SAVEGAME_SLOT_MIN) && (slotNr<=SAVEGAME_SLOT_MAX)) 
	{
		s += SAVEGAME_DIR + zSTRING(slotNr) + "\\";
	}
	else if (slotNr==SAVEGAME_SLOT_CURRENT)	
	{
		s+=SAVEGAME_CURRENT_DIR + "\\";
	}

	return s;
};

