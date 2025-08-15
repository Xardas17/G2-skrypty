
/*****************************************************************************************

  TODO: Console Commando Print um alle Optionen aufzulisten...

*****************************************************************************************/


#include "zcore.h"
#include "zdisk.h"
#include "zoption.h"
#include "zbuffer.h"
#include "zparser.h"
#include "zoption_const.h"

#include "direct.h"
#include "winbase.h"
#include <windows.h>
static char* DIR_STRUCTURE_FILE = "paths.d";

const zSTRING zOPT_SEC_INTERNAL		= "INTERNAL";
const zSTRING zOPT_SEC_GAME			= "GAME";
const zSTRING zOPT_SEC_VIDEO		= "VIDEO";
const zSTRING zOPT_SEC_SOUND		= "SOUND";
const zSTRING zOPT_SEC_MUSIC		= "MUSIC";
const zSTRING zOPT_SEC_KEYS			= "KEYS";
const zSTRING zOPT_SEC_KEYS_DEFAULT0= "KEYSDEFAULT0";
const zSTRING zOPT_SEC_KEYS_DEFAULT1= "KEYSDEFAULT1";
const zSTRING zOPT_SEC_PERFORMANCE	= "PERFORMANCE";
// [BENDLIN] AddonMOD
const zSTRING zOPT_SEC_INFO			= "INFO";
const zSTRING zOPT_SEC_FILES		= "FILES";
const zSTRING zOPT_SEC_SETTINGS		= "SETTINGS";
const zSTRING zOPT_SEC_OPTIONS		= "OPTIONS";

const zSTRING zOPTION_PATHNAMES[NUM_ENTRIES] =  
{
	// main-directories
	"DIR_SYSTEM",
	"DIR_WEB",
	"DIR_SAVEGAMES",
	// data-directories
	"DIR_DATA",				// must be first!
	"DIR_ANIMS",
	"DIR_CUTSCENES",	
	"DIR_OUTPUTUNITS",
	"DIR_MESHES",
	"DIR_SCRIPTS",
	"DIR_SOUND",
	"DIR_VIDEO",
	"DIR_MUSIC",
	"DIR_TEX",
	"DIR_TEX_DESKTOP",
	"DIR_WORLD",
	"DIR_PRESETS",
	"DIR_TOOLS_DATA",
	// compiled
	"DIR_COMPILED_ANIMS",
	"DIR_COMPILED_MESHES",
	"DIR_COMPILED_SCRIPTS",
	"DIR_COMPILED_TEXTURES",
	// other
	"DIR_TOOLS_CONFIG",
	// sub-directories
	"SUBDIR_INTERN",

	"",
	"DIR_ROOT",
	"DIR_EXECUTABLE"
};

const int ENTRY_DONT_SAVE = 1;

const zSTRING ZOPT_LANGUAGE				=	zSTRING("gameLanguage");
const zSTRING ZOPT_DEF_LANGUAGE			=	zSTRING("ENG");
const zSTRING ZOPT_SND_SFX_VOL			=	zSTRING("soundVolume");
const zSTRING ZOPT_SND_SPEECH_VOL		=	zSTRING("soundVolume");
const zSTRING ZOPT_SND_3DPROV			=   zSTRING("soundProvider");
const zSTRING ZOPT_SND_SPEAKERTYPE		=   zSTRING("soundSpeakerType");
const zSTRING ZOPT_SND_SAMPLERATE		=	zSTRING("soundSampleRate");
const zSTRING ZOPT_SND_USEREVERB		=   zSTRING("soundUseReverb");
const zSTRING ZOPT_SND_MUSIC_VOL		=	zSTRING("musicVolume");

const zSTRING ZOPT_VID_GAMMA			=   zSTRING("zVidGamma");
const zSTRING ZOPT_VID_RES				=   zSTRING("vidResIndex");
const zSTRING ZOPT_JOY_ENABLE			=	zSTRING("gameJoyEnabled");
const zSTRING ZOPT_GAMEKEY_UP			=	zSTRING("keyUp");
const zSTRING ZOPT_GAMEKEY_DOWN			=	zSTRING("keyDown");
const zSTRING ZOPT_GAMEKEY_LEFT			=	zSTRING("keyLeft");
const zSTRING ZOPT_GAMEKEY_RIGHT		=	zSTRING("keyRight");
const zSTRING ZOPT_GAMEKEY_ACTION		=   zSTRING("keyAction");
const zSTRING ZOPT_GAMEKEY_SLOW			=	zSTRING("keySlow");
const zSTRING ZOPT_GAMEKEY_SMOVE		=	zSTRING("keySMove");
const zSTRING ZOPT_GAMEKEY_WEAPON		=	zSTRING("keyWeapon");
const zSTRING ZOPT_GAMEKEY_SNEAK		=	zSTRING("keySneak");
const zSTRING ZOPT_GAMEKEY_LOOK			=	zSTRING("keyLook");
const zSTRING ZOPT_GAMEKEY_LOOK_FP		=	zSTRING("keyLookFP");
const zSTRING ZOPT_GAMEKEY_END			=	zSTRING("keyEnd");
const zSTRING ZOPT_GAMEKEY_STRAFELEFT	=	zSTRING("keyStrafeLeft");
const zSTRING ZOPT_GAMEKEY_STRAFERIGHT	=	zSTRING("keyStrafeRight");

const zSTRING ZOPT_GAMEKEY_INVENTORY	=	zSTRING("keyInventory");

const zSTRING ZOPT_GAMEKEY_SCREEN_STATUS=	zSTRING("keyShowStatus");
const zSTRING ZOPT_GAMEKEY_SCREEN_LOG	=	zSTRING("keyShowLog");
const zSTRING ZOPT_GAMEKEY_SCREEN_MAP	=	zSTRING("keyShowMap");
const zSTRING ZOPT_GAMEKEY_LOCK_TARGET  =	zSTRING("keyLockTarget");
const zSTRING ZOPT_GAMEKEY_PARADE		=	zSTRING("keyParade");
const zSTRING ZOPT_GAMEKEY_ACTIONLEFT	=	zSTRING("keyActionLeft");
const zSTRING ZOPT_GAMEKEY_ACTIONRIGHT  =	zSTRING("keyActionRight");
const zSTRING ZOPT_GAMEKEY_LAME_POTION	=	zSTRING("keyPotion");
const zSTRING ZOPT_GAMEKEY_LAME_HEAL	=	zSTRING("keyHeal");

//////////////////////////////////////////////////////////////////////

const char INI_CHAR_SECTION_LEFT	= '[';
const char INI_CHAR_SECTION_RIGHT	= ']';
const char INI_CHAR_COMMENT			= ';';
const zSTRING INI_STR_ASSIGN		= "=";
const zSTRING INI_STR_HEADSECTION   = "HEAD";

zCOption *zoptions = 0;
// [BENDLIN] AddonMOD
zCOption *zgameoptions = 0;

 
zCOptionEntry::zCOptionEntry(const zSTRING& _name, const zSTRING& _value) 
{ 
	/*	
	zSTRING n = _name;
	n.Upper();
	if (_name == n)
	{
		zERR_FATAL("B: TUNTENALARM: Variablennamen ("+_name+") dürfen nicht nur Grossbuchstaben enthalten!!!");
	};
	*/
	
	varName = _name; 
	varName.TrimLeft();
	varName.TrimRight();
	varValue = _value; 
	varValue.TrimLeft();
	varValue.TrimRight();
	varValueTemp = varValue;
	changed = FALSE; 	
	varFlag = 0;
};

zCOptionSection::zCOptionSection(const zSTRING& _name) 
{ 
	secName = _name; 	
	secName.TrimLeft();
	secName.TrimRight();
	secName.TrimLeft(INI_CHAR_SECTION_LEFT);
	secName.TrimRight(INI_CHAR_SECTION_RIGHT);
	secName.Upper();
};

/* ----------------------------------------------------------------------
	
    zCOptionSection::~zCOptionSection()

	28.08.2000	[Moos]	
                leak gefixt


   ---------------------------------------------------------------------- */

zCOptionSection::~zCOptionSection()
{ 
    for (int i=entryList.GetNum()-1;i>=0;i--)
        delete entryList[i];

	entryList.DeleteList();
};

zCOption::zCOption()
{
	//gameinfo = 0;

	m_bReadTemp = TRUE;
	commandline.Clear();		

	for (int i=0;i<NUM_ENTRIES;i++) 
	{
		directory[i] = zNEW(zFILE_FILE());
		dir_string[i].Clear();
	}	
}
/* ----------------------------------------------------------------------
	
    zCOption::~zCOption()

	28.08.2000	[Moos]	
                leak gefixt


   ---------------------------------------------------------------------- */

zCOption::~zCOption()
{
    int i;
    for (i=sectionList.GetNum()-1;i>=0;i--)
        delete sectionList[i];

	sectionList.DeleteList();

	for (i=0;i<NUM_ENTRIES;i++) 
	{
		delete directory[i];
		directory[i] = 0;
	}	
};

/* ----------------------------------------------------------------------
	
    zCOption::Load()

	28.08.2000	[Moos]	
                leak gefixt: file wird gelöscht


   ---------------------------------------------------------------------- */


// Load/Save Options to filename. 
zBOOL zCOption::Load(zSTRING fileName)
{
	zERR_MESSAGE(8,zERR_BEGIN,"B: INI: Loading "+fileName+" ...");

	fileName.Lower();

	sectionList.DeleteList();
	ChangeDir(DIR_SYSTEM);
	zFILE* file = zNEW(zFILE_FILE(fileName)); // keine factory benutzen, da niemals VDFS gefragt ist und die factory moeglicherweise noch nicht existiert
	if (!file) return FALSE;

	if (!file->Exists())
	{
		zERR_WARNING("B: INI: File \""+fileName+"\" not found.");
        delete file;file=0;
		return FALSE;
	};
	file->Open();	

	zSTRING line;
	zSTRING trashstring;

	zCOptionSection* section;
	zCOptionEntry* entry;

	section = zNEW(zCOptionSection(INI_STR_HEADSECTION));
	sectionList.InsertEnd(section);
	zERR_MESSAGE(8,zERR_BEGIN,"B: INI: Section: "+section->secName);

	while (!file->Eof())
	{
		file->Read(line);
		line.TrimLeft();
		line.TrimRight();		
		if (line.Length()==0 || (line[0]==INI_CHAR_COMMENT))
		// trashstring erweitern
		{						
			trashstring = trashstring + line;
			if (!file->Eof()) trashstring = trashstring + "\r\n";
		}
		else
		{
			// trashstring schreiben
			if (!trashstring.IsEmpty())
			{
				entry = zNEW(zCOptionEntry("",trashstring));
				section->entryList.InsertEnd(entry);
				zERR_MESSAGE(9,0,"B: INI: Trash: "+trashstring);
			};
			trashstring.Clear(); // trash ist zuende

			// eine neue Section
			if (line[0]==INI_CHAR_SECTION_LEFT)
			{
				zERR_MESSAGE(8,zERR_END,"");

				line.TrimLeft(INI_CHAR_SECTION_LEFT);
				line.TrimRight(INI_CHAR_SECTION_RIGHT);

				section = GetSectionByName(line);
				if (section)
				{										
					zERR_MESSAGE(8,zERR_BEGIN,"B: INI: Section(cont): "+section->secName);
				}
				else
				{
					section = zNEW(zCOptionSection(line));
					sectionList.InsertEnd(section);				
					zERR_MESSAGE(8,zERR_BEGIN,"B: INI: Section: "+section->secName);
				}
			}
			else if (line.Search(INI_STR_ASSIGN)>0)
			// ein neuer Entry
			{
				zSTRING valuestring = line.Deleted(INI_STR_ASSIGN,zSTR_TO);				
				line.Delete(INI_STR_ASSIGN,zSTR_FROM);
				entry = zNEW(zCOptionEntry(line,valuestring));
				section->entryList.InsertEnd(entry);

				zERR_MESSAGE(9,0,"B: INI: Entry: "+entry->GetName() + INI_STR_ASSIGN + entry->GetValueString(FALSE));
			}
			else
			{
				zERR_WARNING("B: INI: Unknown line: "+line);
			};
		};
	};

	// trashstring schreiben
	if (!trashstring.IsEmpty())
	{
		entry = zNEW(zCOptionEntry("",trashstring));
		section->entryList.InsertEnd(entry);
		zERR_MESSAGE(9,0,"B: INI: Trash: "+trashstring);
	};
	trashstring.Clear(); // trash ist zuende

	file->Close();

	// System-Informations		
	char			buffer[MAX_COMPUTERNAME_LENGTH + 1];
	unsigned long	maxSize = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerName (buffer,&maxSize);
	WriteString		(zOPT_SEC_INTERNAL,"idComputerName",buffer);
	
	maxSize = MAX_COMPUTERNAME_LENGTH + 1;
	GetUserName		(buffer,&maxSize);
	WriteString		(zOPT_SEC_INTERNAL,"idUserName",buffer);
	
	/*
	HW_PROFILE_INFO HwProfInfo;
	if (GetCurrentHwProfile(&HwProfInfo)) 
	{      		
		WriteString(zOPT_SEC_INTERNAL,"idProfileGuid", zSTRING(HwProfInfo.szHwProfileGuid));
		WriteString(zOPT_SEC_INTERNAL,"idFriendlyName", zSTRING(HwProfInfo.szHwProfileName));
	}
	*/


	zERR_MESSAGE(8,zERR_END,""); // last Section
	zERR_MESSAGE(8,zERR_END,""); // INI-File

    delete file;file=0;

	return TRUE;
};


/* ----------------------------------------------------------------------
	
    zCOption::Save()	

	30.08.2000	[Moos]	
                file aufgeräumt


   ---------------------------------------------------------------------- */

zBOOL zCOption::Save(zSTRING fileName)
{	
	zCOptionSection* section;
	zCOptionEntry* entry;

	zFILE* file = zfactory->CreateZFile(fileName);
	if (!file) return FALSE;


	zERR_MESSAGE(6,zERR_BEGIN,"B: INI: Saving "+fileName+" ...");

	fileName.Lower();

	ChangeDir(DIR_SYSTEM);
	file->Create(fileName);	

	int secAnz = sectionList.GetNumInList();
	for (int sec=0;sec<secAnz;sec++)
	{	
		section = sectionList.GetSafe(sec);		
		if (section->secName != INI_STR_HEADSECTION)
		{
			file->Write( zSTRING(INI_CHAR_SECTION_LEFT)+section->secName+zSTRING(INI_CHAR_SECTION_RIGHT)+"\r\n" );
		};

		zERR_MESSAGE(8,zERR_BEGIN,"B: INI: Section: "+section->secName);

		int entryAnz = section->entryList.GetNumInList();
		for (int nr=0;nr<entryAnz;nr++)
		{	
			entry = section->entryList.GetSafe(nr);
			if (!entry->HasFlag(ENTRY_DONT_SAVE))
				if (entry->GetName().IsEmpty())
				{
					file->Write(entry->GetValueString(FALSE));
				}
				else
				{
					file->Write( entry->GetName() + INI_STR_ASSIGN + entry->GetValueString(FALSE) + "\r\n");
				}
		}		

		zERR_MESSAGE(8,zERR_END,"");
	};

	file->Close();
    delete file;file=0;

	zERR_MESSAGE(6,zERR_END,"");
	return TRUE;
};


// Write the value of an entry (creates a new entry if it not exists)
zBOOL zCOption::WriteBool(const zSTRING& secName, const char* name, zBOOL value, zBOOL temp)
{	
	if (value) 
		return WriteString(secName, name, "1", temp);
	else
		return WriteString(secName, name, "0", temp);
};

zBOOL zCOption::WriteInt(const zSTRING& secName, const char* name, int value, zBOOL temp)
{
	return WriteString(secName, name, zSTRING(value), temp);
};

zBOOL zCOption::WriteDWord(const zSTRING& secName, const char* name, zDWORD value, zBOOL temp)
{
	return WriteString(secName, name, zSTRING(value), temp);
};

zBOOL zCOption::WriteReal(const zSTRING& secName, const char* name, zREAL value, zBOOL temp)
{
	return WriteString(secName, name, zSTRING(value), temp);
};


zBOOL zCOption::WriteString(const zSTRING& secName, const char* name, zSTRING	value, zBOOL temp)
{
	zCOptionSection*	section	= GetSectionByName(secName);	
	zCOptionEntry*		entry	= GetEntryByName(section,name);		
	
	zBOOL changed = (entry->GetValueString(temp) != value);

	entry->SetValue(value,temp);
	
	if (changed)
		for (int i=0; i<entry->ccbList.GetNumInList(); i++) 
		{
			if ( entry->ccbList[i](*entry) == TRUE ) break;
		}


	return TRUE;
};


 

// Read the value of an entry (creates a new entry if it not exists)
zBOOL zCOption::ReadBool(const zSTRING& secName, const char* name, zBOOL value)
{
	zSTRING result;
	if (value)	result = ReadString(secName,name,"1");
	else		result = ReadString(secName,name,"0");

	if (result=="1")		return TRUE;
	if (result=="0")		return FALSE;
	result.Upper();
	if (result=="TRUE")		return TRUE;
	if (result=="FALSE")	return FALSE;
	return FALSE;
};

int zCOption::ReadInt(const zSTRING& secName, const char* name, int defaultVal)
{
	zSTRING defVal = zSTRING(defaultVal);
	return (int)(ReadString(secName,name,defVal.ToChar()).ToInt());
};

zDWORD zCOption::ReadDWord(const zSTRING& secName, const char* name, zDWORD defaultVal)
{
	zSTRING defVal = zSTRING(defaultVal);
	return (zDWORD)(ReadString(secName,name,defVal.ToChar()).ToInt());
};

zREAL zCOption::ReadReal(const zSTRING& secName, const char* name, zREAL defaultVal)
{
	zSTRING defVal = zSTRING(defaultVal);
	return (zREAL)(ReadString(secName,name,defVal.ToChar()).ToDouble());
};

zSTRING zCOption::ReadString(const zSTRING& secName, const char* name, const char* defaultVal)
{	
	zCOptionSection*	section	= GetSectionByName(secName);
	zCOptionEntry*		entry	= GetEntryByName(section,name);	

	zBOOL assigned = !entry->GetValueString(TRUE).IsEmpty();

	if (!assigned && defaultVal) entry->SetValue(defaultVal,FALSE);
	
	return entry->GetValueString(m_bReadTemp);	
};


// Query and handle entries of given section

zBOOL zCOption::EntryExists(const zSTRING& secName, const char* name)
{
	zCOptionSection*	section	= GetSectionByName(secName, FALSE);	
	if (!section) return FALSE;
	zCOptionEntry*		entry	= GetEntryByName(section, name, FALSE);	
	return (entry!=0);
};

zWORD zCOption::GetNumEntries(zCOptionSection* section)
{	
	if (!section) return 0;
	return section->entryList.GetNumInList();
};

zCOptionEntry* zCOption::GetEntry(zCOptionSection* section, const int nr)
{
	if (!section) return 0;
	if (nr<0 || nr>=section->entryList.GetNumInList()) return 0;
	
	return section->entryList.GetSafe(nr);	
};

zBOOL zCOption::RemoveEntry(const zSTRING& secName, const char* name)
{
	zCOptionSection*	section	= GetSectionByName(secName);			
	zCOptionEntry*		entry	= GetEntryByName(section,name);
	section->entryList.Remove(entry);	
	delete entry;entry=0;
	return TRUE;
};

void zCOption::SetFlag(const zSTRING& secName, const char* name,int flag)
{
	zCOptionSection*	section	= GetSectionByName(secName);			
	zCOptionEntry*		entry	= GetEntryByName(section,name);
	entry->SetFlag(flag);
};


// Query and handle existing section

zCOptionEntry* zCOption::GetEntryByName(zCOptionSection* section, const zSTRING& name, zBOOL create)
{
	if (!section) return 0;	
		
	zCOptionEntry* entry = 0;
	int anz = section->entryList.GetNumInList();
	for(int i=0;i<anz;i++)
	{
		entry = section->entryList.GetSafe(i);
		if (entry && (entry->GetName() == name)) return entry;
	};	

	entry = 0;
	if (create)
	{
		entry = zNEW(zCOptionEntry(name, ""));

		int i = section->entryList.GetNumInList();		
		
		while 
		( 
			(--i) >= 0
			&&
			section->entryList[i]->GetName().IsEmpty()
		); // Leerer Body, da die "Bedingung" schon alles macht, was noetig ist!!

		section->entryList.InsertAtPos(entry,i+1);
	}
	return entry;
}

zCOptionSection* zCOption::GetSectionByName(const zSTRING& secName, zBOOL create)
{
	zSTRING secName2 = secName;
	secName2.TrimLeft(INI_CHAR_SECTION_LEFT);
	secName2.TrimRight(INI_CHAR_SECTION_RIGHT);
	secName2.Upper();

	zCOptionSection* section;
	int secAnz = sectionList.GetNumInList();
	for (int sec=0;sec<secAnz;sec++)
	{	
		section = sectionList.GetSafe(sec);		
		if (section && (section->secName == secName2)) return section;
	};

	section =0;
	if (create)
	{
		section = zNEW(zCOptionSection(secName));
		sectionList.InsertEnd(section);
	}
	return section;
};

zBOOL zCOption::SectionExists(const zSTRING& secName)
{		
	return (GetSectionByName(secName) != 0);
};

zWORD zCOption::GetNumSections()
{
	return sectionList.GetNumInList();
};

zCOptionSection* zCOption::GetSection(const int nr)
{
	if (nr<0 || nr>=GetNumSections()) return 0;
	return sectionList.GetSafe(nr);
};

zBOOL zCOption::RemoveSection(const zSTRING& secName)
{		
	zCOptionSection* section = GetSectionByName(secName);
	if (section)
	{
		sectionList.Remove(section);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
};


void zCOption::InsertChangeHandler(const zSTRING& secName, const char* name,zBOOL (*ccb)( zCOptionEntry &newValue) )
{	
	zCOptionSection*	section	= GetSectionByName(secName);
	zCOptionEntry*		entry	= GetEntryByName(section,name);	

	entry->ccbList.InsertEnd(ccb);	
};

zBOOL zCOption::WriteRaw(const zSTRING& secName, const char* name, void* buffer, int size, zBOOL temp)
{
	zSTRING rawString;
	char buf[32];
	int value;
	for (int i=0;i<size;i++)
	{		
		value = int( ((zBYTE*)buffer)[i] );
		sprintf (buf, "%02x", value);
		value = int(((char*)buffer)[i]);						
		rawString = rawString + zSTRING(buf);		
	};
	WriteString(secName,name,rawString, temp);
	return TRUE;
};

#include <CrtDbg.h>

int zCOption::ReadRaw(const zSTRING& secName, const char* name, void*& buffer, void* defBuffer, const int defSize )
{	
	// assert(_CrtCheckMemory());

	if (!EntryExists(secName,name) && defBuffer)
	{
		WriteRaw(secName,name,defBuffer,defSize);		
	};

	zSTRING rawString = ReadString(secName, name);
	int bufsize = int(rawString.Length() / 2);
	char* charbuf = zNEW(char)[bufsize];

	long	strLen	= rawString.Length();
	int		value	= 0;

	int bufCtr=0;
	for (int i=0; i<strLen; i+=2) 
	{
		if (bufCtr>bufsize) 
		{
			buffer = charbuf;
			return bufCtr;
		}		
		sscanf(&rawString[i], "%2x", &value);
		charbuf[bufCtr] = (char)value;
		bufCtr++;		
	};
	
	buffer = charbuf;

	// assert(_CrtCheckMemory());

	return bufCtr;
};





zBOOL zCOption::WriteBool   (const zSTRING& secName, const zSTRING& name, zBOOL value, zBOOL temp)
{ return WriteBool(secName,(char*)name.ToChar(),value,temp);};

zBOOL zCOption::WriteInt	(const zSTRING& secName, const zSTRING& name, int value, zBOOL temp)
{ return WriteInt(secName,(char*)name.ToChar(),value,temp);};

zBOOL zCOption::WriteDWord	(const zSTRING& secName, const zSTRING& name, zDWORD value, zBOOL temp)
{ return WriteDWord(secName,(char*)name.ToChar(),value,temp); };

zBOOL zCOption::WriteReal	(const zSTRING& secName, const zSTRING& name, zREAL value, zBOOL temp)
{ return WriteReal(secName,(char*)name.ToChar(),value,temp); };

zBOOL zCOption::WriteString	(const zSTRING& secName, const zSTRING& name, zSTRING	value, zBOOL temp)
{ return WriteString(secName,(char*)name.ToChar(),value,temp); };

zBOOL zCOption::WriteRaw	(const zSTRING& secName, const zSTRING& name, void* buffer, int size, zBOOL temp)
{ return WriteRaw(secName,(char*)name.ToChar(),buffer,size,temp); };

zBOOL	zCOption::ReadBool  (const zSTRING& secName, const zSTRING& name, zBOOL defaultVal)
{ return ReadBool(secName,(char*)name.ToChar(),defaultVal); };

int	zCOption::ReadInt	(const zSTRING& secName, const zSTRING& name, int defaultVal)
{ return ReadInt(secName,(char*)name.ToChar(),defaultVal); };

zDWORD	zCOption::ReadDWord	(const zSTRING& secName, const zSTRING& name, zDWORD defaultVal)
{ return ReadDWord(secName,(char*)name.ToChar(),defaultVal); };

zREAL	zCOption::ReadReal	(const zSTRING& secName, const zSTRING& name, zREAL defaultVal)
{ return ReadReal(secName,(char*)name.ToChar(),defaultVal); };

zSTRING zCOption::ReadString(const zSTRING& secName, const zSTRING& name, const char* defaultVal)
{ return ReadString(secName,(char*)name.ToChar(),defaultVal); };

int zCOption::ReadRaw(const zSTRING& secName, const zSTRING& name, void* buffer, const int max_size)
{ return ReadRaw(secName,(char*)name.ToChar(),buffer,0,max_size); };



// [BENDLIN] AddonMOD
zERROR_ID zCOption::AddParameters(zSTRING parmlist)
{
	commandline = parmlist + " " + commandline;
	commandline.Upper();
	return zERR_NONE;
};

zERROR_ID zCOption::Init(zSTRING parmlist, bool additional_info)
{			
	// [BENDLIN] AddonMOD
	if (!additional_info)
		return zERR_NONE;

	zERR_MESSAGE(2,zERR_BEGIN,"B: zOPT: Initialize configurations ");	
		
	AddParameters(parmlist);

	char buffer[255];

	// ins EXE-Verzeichnis wechseln
	zSTRING exe_path;
	GetModuleFileName(NULL, buffer, sizeof(buffer));
	exe_path = zSTRING(buffer);	
	exe_path.Delete(exe_path.SearchRev("\\"));
	chdir(exe_path.ToChar());

	// Pfad-Konfigurationen suchen
	
	zERROR_ID	result = zERR_NONE;
	//  int			count=0;
	int			index=0;
	zSTRING		value;		
		
	getcwd(buffer,254);
	if (access(DIR_STRUCTURE_FILE,0)==-1) 
	{
		zERR_FATAL("B: zOPT: Could not find file "+zSTRING(DIR_STRUCTURE_FILE));
		return zERR_NONE;
	}
	
	zERR_MESSAGE(3, 0, "B: zOPT: Found file "+zSTRING(DIR_STRUCTURE_FILE));

	// Pfad-Konfigurationsdatei parsen

	zERR_MESSAGE(5, 0, "B: zOPT: Initialising Parser");
	parser.Reset();

	zERR_MESSAGE(5, 0, "B: zOPT: Parsing "+zSTRING(DIR_STRUCTURE_FILE)+" ...");
	parser.ParseFile(zSTRING(DIR_STRUCTURE_FILE));
	
	zERR_MESSAGE(5, 0, "B: zOPT: Analysing "+zSTRING(DIR_STRUCTURE_FILE)+" ...");

	// Root-Verzeichnis ermitteln	
	index = parser.GetIndex( zOPTION_PATHNAMES[DIR_ROOT] );		
	if (index<0) zERR_FATAL("B: zOPT: Entry missed in "+zSTRING(DIR_STRUCTURE_FILE)+": "+zOPTION_PATHNAMES[DIR_ROOT]);
	
	value = parser.GetText(index,0); 
	chdir(value.ToChar());
	getcwd(buffer,254);
	
	dir_string[DIR_ROOT] = zFILE::SetRootDirectory(buffer);	
	zERR_MESSAGE(6,0,"B: zOPT: Set root-directory to \""+dir_string[DIR_ROOT]+"\"");	

	zFILE_FILE	checkDir;
	zSTRING		checkDirString;
	int			checkResult;
	// Alle anderen Eintraege auslesen	
	for (int i=0;i<NUM_PATHS;i++)
	{
		// [BENDLIN] Addon - FIXME: Strings mit Integern zu vergleichen ist relativ sinnlos...
		if (zOPTION_PATHNAMES[i]==DIR_ROOT)
			continue;
		
		index = parser.GetIndex(zOPTION_PATHNAMES[i]);
		if (index>=0) 
		{
			value = parser.GetText(index,0);

			// [BENDLIN] AddonMOD
			if ((i == DIR_SAVEGAMES) && !value.IsEmpty())
			{
				zSTRING	filename;
				zFILE*	file = 0;
				filename = zoptions->ParmValue("game");
				if (!filename.IsEmpty())
				{
					file = zfactory->CreateZFile(filename);
					if (file)
					{
						zSTRING	modname = file->GetFilename();
						modname.Lower();
						if (!modname.IsEmpty() && modname.CompareTo("gothicgame"))
						{
							while ((value.GetLastChar() == '\\') && (value.Length() > 1))
								value.DeleteRight(1);
							value += "_" + modname + "\\";
							value.Lower();
						}
						file->Close();
						delete file; file = 0;
					}
				}
			}
		}
		else
		{			
			zERR_FATAL("B: zOPT: Entry missed in "+zSTRING(DIR_STRUCTURE_FILE)+": "+zOPTION_PATHNAMES[i]);
		}

		value.Upper();
		
		if (value.Search("$DATA$")>=0)
		{
			index = value.Search("$DATA$");
			value.Delete("$DATA$");
			value.Insert(index,dir_string[DIR_DATA]);
			index = value.Search("\\\\");
			if (index>=0) value.Delete(index,1);			
		};
		directory[i]->SetPath(value);
		dir_string[i] = value;

		zERR_MESSAGE(6,0,"B: zOPT: "+zOPTION_PATHNAMES[i]+" = "+dir_string[i]);	

		// check if directory exists				
		if (value.Search("DIR_")==0) // pruefe nur Verzeichnisse mit vorangestelltem "DIR_"
		{
			checkDir.SetPath(value);
			checkDirString = checkDir.GetFullPath();		
			checkResult = _access(checkDirString.ToChar(),0);
			if (checkResult!=0)
			{
				zERR_FAULT("B: zOPT: The value of <"+zOPTION_PATHNAMES[i]+"> in file \""+zSTRING(DIR_STRUCTURE_FILE)+"\" is wrong:\r\n Directory \""+checkDirString+"\" does not exist.");
			};
		}
		
		//checkResult = checkDir.ChangeDir();		
	}

	exe_path.Delete(dir_string[DIR_ROOT]);
	dir_string[DIR_EXECUTABLE] = exe_path+"\\";
	directory[DIR_EXECUTABLE]->SetPath(dir_string[DIR_EXECUTABLE]);	
	zERR_MESSAGE(6,0,"B: zOPT: DIR_EXECUTABLE = "+dir_string[DIR_EXECUTABLE]);	
	
	parser.Reset();		
	
	zERR_MESSAGE(3, zERR_END, "");	

	return result; 
}


void zCOption::ChangeDir(zTOptionPaths id)
{		
	if (directory[id]) directory[id]->ChangeDir();
	else zERR_FAULT("B: (zCOption::ChangeDir) directory-entry not defined!");
}

zFILE* zCOption::GetDir(zTOptionPaths id)
{		
	return directory[id];
}


zSTRING& zCOption::GetDirString(zTOptionPaths id)
{		
	return dir_string[id];
}


zBOOL zCOption::Parm(const zSTRING& parmname)
{
	zSTRING s = "-"+parmname;
	s.Upper();
	commandline.Upper();
	if (commandline.Search(s)>=0) return TRUE; else return FALSE;
}

zSTRING zCOption::ParmValue (const zSTRING& parmname)
{
	zSTRING s = "-"+parmname+":";
	s.Upper();
	int index = commandline.Search(s);
	if (index<0) return "";
	index += s.Length();
	int index_end = index;
	while ((commandline[index_end]!=0) && (commandline[index_end]!=32)) index_end++;
	
	zSTRING result = commandline.Copied(index,index_end-index);	
	return result;
}

zSTRING zCOption::ParmValueRaw (const zSTRING& parmname)
{
	zSTRING s = "-"+parmname+":";
	s.Upper();	
	int index = commandline.Search(s);
	if (index<0) return "";
	index += s.Length();
	int index_end = index;
	while ((commandline[index_end]!=0) && (commandline[index_end]!=32)) index_end++;
	
	zSTRING result = commandline.Copied(index,index_end-index);	
	return result;
}

int zCOption::ParmValueInt (const zSTRING& parmname)
{	
	zSTRING s = "-"+parmname+":";
	s.Upper();
	int index = commandline.Search(s);
	if (index<0) return -1;
	index += s.Length();
	int index_end = index;
	while ((commandline[index_end]!=0) && (commandline[index_end]!=32)) index_end++;
	
	zSTRING result = commandline.Copied(index,index_end-index);	
	return result.ToInt();
}

float	zCOption::ParmValueFloat	(const zSTRING& parmname)
{
	zSTRING s = "-"+parmname+":";
	s.Upper();
	int index = commandline.Search(s);
	if (index<0) return -1;
	index += s.Length();
	int index_end = index;
	while ((commandline[index_end]!=0) && (commandline[index_end]!=32)) index_end++;
	
	zSTRING result = commandline.Copied(index,index_end-index);	
	return result.ToFloat();
}


//#pragma optimize( "", on )
