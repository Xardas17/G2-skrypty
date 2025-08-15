/****************************************************************
*																
* C++ Optionen Klassen
* File          : zoption.h ()								
* Author		: Carsten Edenfeld
* Projekt       : Gothic
* Version       : 0.00
* last modified : 
* erstellt      : 25.05.99
* Compiler OK   : 
*																
*****************************************************************
- known bugs:
*****************************************************************
- possible optimizations: 
*****************************************************************
- missing features:  
*****************************************************************
- comments:
*****************************************************************/

#ifndef __ZOPTION_H__
#define __ZOPTION_H__

#ifndef __ZSTRING_H__
#include "zstring.h"
#endif

#ifndef __ZCONTAINER_H__
#include "zcontainer.h"  
#endif

extern const zSTRING zOPT_SEC_INTERNAL;
extern const zSTRING zOPT_SEC_GAME;
extern const zSTRING zOPT_SEC_VIDEO;
extern const zSTRING zOPT_SEC_SOUND;
extern const zSTRING zOPT_SEC_MUSIC;
extern const zSTRING zOPT_SEC_KEYS;
extern const zSTRING zOPT_SEC_KEYS_DEFAULT0;
extern const zSTRING zOPT_SEC_KEYS_DEFAULT1;
extern const zSTRING zOPT_SEC_PERFORMANCE;
// [BENDLIN] AddonMOD
extern const zSTRING zOPT_SEC_INFO;
extern const zSTRING zOPT_SEC_FILES;
extern const zSTRING zOPT_SEC_SETTINGS;
extern const zSTRING zOPT_SEC_OPTIONS;


enum zTOptionPaths
{		
	// main-directories
	DIR_SYSTEM,
	DIR_WEB,
	DIR_SAVEGAMES,
	// data-directories
	DIR_DATA,				// must be first!
	DIR_ANIMS,
	DIR_CUTSCENES,
	DIR_OUTPUTUNITS,
	DIR_MESHES,
	DIR_SCRIPTS,	
	DIR_SOUND,
	DIR_VIDEO,
	DIR_MUSIC,
	DIR_TEX,
	DIR_TEX_DESKTOP,
	DIR_WORLD,	
	DIR_PRESETS,	
	DIR_TOOLS_DATA,	
	// compiled
	DIR_COMPILED_ANIMS,
	DIR_COMPILED_MESHES,
	DIR_COMPILED_SCRIPTS,
	DIR_COMPILED_TEXTURES,
	// other
	DIR_TOOLS_CONFIG,
	// sub-directories
	SUBDIR_INTERN,
	
	NUM_PATHS,		// finished with in paths.d configured directories

	DIR_ROOT,		// root of gothic (full path)
	DIR_EXECUTABLE,	// directory of executable

	NUM_ENTRIES		// last entry
};


extern const zSTRING zOPTION_PATHNAMES[NUM_ENTRIES];

extern const int ENTRY_DONT_SAVE;

class zCOptionEntry
{	
public:
	// Change-Callback
	typedef zBOOL (*EntryChangeHandler)( zCOptionEntry &newValue );	
	zBOOL changed;
	zCArray <EntryChangeHandler> ccbList;

	// Constructor
	zCOptionEntry(const zSTRING& _name, const zSTRING& _value);

	void		SetValue		(zSTRING s, zBOOL temp)	{ varValueTemp=s;if (!temp) varValue=s; };

	zSTRING&	GetName			()					{ return varName; };
	zSTRING&	GetValueString	(zBOOL temp=TRUE)	{ return (temp?varValueTemp:varValue); };
	float		GetValueFloat	(zBOOL temp=TRUE)	{ return (temp?varValueTemp.ToFloat():varValue.ToFloat()); };
	int			GetValueInt		(zBOOL temp=TRUE)	{ return (temp?varValueTemp.ToInt():varValue.ToInt()); };			

	void		SetFlag			(int flag)			{ varFlag |= flag; };
	void		ClrFlag			(int flag)			{ varFlag &= ~flag; };
	bool		HasFlag			(int flag)			{ return ((varFlag & flag) == flag); };

protected:
	// Variable-Data	
	zSTRING varName;
	zSTRING varValue;	
	zSTRING varValueTemp;
	int		varFlag;
};

class zCOptionSection
{	
public:
	// Section-Name
	zSTRING secName;	

	// Entry-List
	zCArray<zCOptionEntry*> entryList;

	// Constructor and Destructor
	zCOptionSection(const zSTRING& _name);
	~zCOptionSection();
};

typedef zCOptionEntry zCOptionValue; // for compatibility

class zCOption
{
public:
	// COnstructor and destructor
	zCOption();
	virtual ~zCOption();

	// [BENDLIN] AddonMOD
	zERROR_ID Init(zSTRING parmlist, bool additional_info = TRUE);
	zERROR_ID AddParameters(zSTRING parmlist);

	// Load/Save Options to filename. 
	zBOOL	Load(zSTRING fileName);
	zBOOL	Save(zSTRING fileName);

	zBOOL	SetReadTemp(zBOOL temp=TRUE) { zBOOL b = m_bReadTemp; m_bReadTemp = temp; return b; };

	// Write the value of an entry (creates a new entry if it not exists)
	// methods will return TRUE, if the entry was created, otherwise was updated
	zBOOL	WriteBool   (const zSTRING& secName, const char* name, zBOOL value, zBOOL temp=FALSE);
	zBOOL	WriteInt	(const zSTRING& secName, const char* name, int value, zBOOL temp=FALSE);
	zBOOL	WriteDWord	(const zSTRING& secName, const char* name, zDWORD value, zBOOL temp=FALSE);
	zBOOL	WriteReal	(const zSTRING& secName, const char* name, zREAL value, zBOOL temp=FALSE);
	zBOOL	WriteString	(const zSTRING& secName, const char* name, zSTRING	value, zBOOL temp=FALSE);	
	zBOOL   WriteRaw	(const zSTRING& secName, const char* name, void* buffer, int size, zBOOL temp=FALSE);
	
	zBOOL	WriteBool   (const zSTRING& secName, const zSTRING& name, zBOOL value, zBOOL temp=FALSE);
	zBOOL	WriteInt	(const zSTRING& secName, const zSTRING& name, int value, zBOOL temp=FALSE);
	zBOOL	WriteDWord	(const zSTRING& secName, const zSTRING& name, zDWORD value, zBOOL temp=FALSE);
	zBOOL	WriteReal	(const zSTRING& secName, const zSTRING& name, zREAL value, zBOOL temp=FALSE);
	zBOOL	WriteString	(const zSTRING& secName, const zSTRING& name, zSTRING	value, zBOOL temp=FALSE);	
	zBOOL   WriteRaw	(const zSTRING& secName, const zSTRING& name, void* buffer, int size, zBOOL temp=FALSE);
	
	// Read the value of an entry (creates a new entry if it not exists)
	// the methods return the value.
	zBOOL	ReadBool   	(const zSTRING& secName, const char* name, zBOOL value=FALSE);
	int		ReadInt		(const zSTRING& secName, const char* name, int defaultVal=0);
	zDWORD	ReadDWord	(const zSTRING& secName, const char* name, zDWORD defaultVal=0);
	zREAL	ReadReal	(const zSTRING& secName, const char* name, zREAL defaultVal=0);
	zSTRING ReadString	(const zSTRING& secName, const char* name, const char* defaultVal=0);

	// ReadRaw allocates the buffer. The calling method must destroy it after usage!
	int     ReadRaw		(const zSTRING& secName, const char* name, void*& buffer, void* defBuffer=0, const int defSize=0);

	zBOOL	ReadBool   	(const zSTRING& secName, const zSTRING& name, zBOOL defaultVal=FALSE);
	int		ReadInt		(const zSTRING& secName, const zSTRING& name, int defaultVal=0);
	zDWORD	ReadDWord	(const zSTRING& secName, const zSTRING& name, zDWORD defaultVal=0);
	zREAL	ReadReal	(const zSTRING& secName, const zSTRING& name, zREAL defaultVal=0);
	zSTRING ReadString	(const zSTRING& secName, const zSTRING& name, const char* defaultVal=0);
	int     ReadRaw		(const zSTRING& secName, const zSTRING& name, void* buffer, const int max_size);

	// remove and test entry
	zBOOL	RemoveEntry		(const zSTRING& secName, const char* name);
	zBOOL	EntryExists		(const zSTRING& secName, const char* name);
	
	// remove and test section
	zBOOL	RemoveSection	(const zSTRING& secName);
	zBOOL	SectionExists	(const zSTRING& secName);

	void	SetFlag(const zSTRING& secName, const char* name,int flag);

	// query sections
	zWORD				GetNumSections	();
	zCOptionSection*	GetSection		(const int nr);	
	zCOptionSection*	GetSectionByName(const zSTRING& secName, zBOOL create = TRUE);
	
	// query entries of a given section	
	zWORD				GetNumEntries	(zCOptionSection* section);		
	zCOptionValue*		GetEntry		(zCOptionSection* section, const int nr);
	zCOptionValue*		GetEntryByName	(zCOptionSection* section, const zSTRING& name, zBOOL create = TRUE);
	
	// registering a change-handler
	// the callback will be called if the specified variable has been changed
	void InsertChangeHandler(const zSTRING& section, const char* name,zBOOL (*ccb)( zCOptionValue &newValue) );	


	//
	// Commandline-Methods
	//	

	void		ChangeDir		(zTOptionPaths nr);
	zFILE*		GetDir			(zTOptionPaths nr);
	zSTRING&	GetDirString	(zTOptionPaths nr);		

	zBOOL		Parm			(const zSTRING& parmname);	
	zSTRING		ParmValue		(const zSTRING& parmname);
	zSTRING		ParmValueRaw	(const zSTRING& parmname);
	int			ParmValueInt	(const zSTRING& parmname);
	float		ParmValueFloat	(const zSTRING& parmname);	

	//
	// ToDo: Remove these methods: wrong time, wrong place
	//

//	zCGameInfo*	GetGameInfo() { return gameinfo; };
//	void		SetGameInfo(zCGameInfo* _gameinfo) { gameinfo = _gameinfo; };

private:
		
	zBOOL		m_bReadTemp;

	zCArray<zCOptionSection*> sectionList;
	
	zFILE*		(directory)[NUM_ENTRIES];
	zSTRING		dir_string[NUM_ENTRIES];
	zSTRING		commandline;
	
//	zCGameInfo* gameinfo; // ToDo: Remove these methods: wrong time, wrong place
};



extern zCOption *zoptions;
// [BENDLIN] AddonMOD
extern zCOption *zgameoptions;




#endif