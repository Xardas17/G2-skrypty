/******************************************************************************** 
 
     $Workfile:: osavegame.h          $                $Date:: 15.03.01 14:00   $
     $Revision:: 12                   $             $Modtime:: 14.03.01 21:30   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/osavegame.h $
 * 
 * 12    15.03.01 14:00 Speckels
 * 
 * 11    13.03.01 18:57 Speckels
 * 
 * 10    29.01.01 22:23 Speckels
 * 
 * 9     13.11.00 22:09 Speckels
 * 
 * 8     20.10.00 19:04 Speckels
 * 
 * 7     20.10.00 16:13 Speckels
 * 
 * 6     20.10.00 13:19 Speckels
 * 
 * 5     19.10.00 18:22 Speckels
 * 
 * 4     11.10.00 21:34 Speckels
 * 
 * 3     10.10.00 14:49 Speckels
 * 
 * 2     9.10.00 20:53 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 12 $ ($Modtime: 14.03.01 21:30 $)

#ifndef __OSAVEGAME_H__
#define __OSAVEGAME_H__

#include "zbuffer.h"

extern const int		SAVEGAME_SLOT_NONE;
extern const int		SAVEGAME_SLOT_NEW;
extern const int		SAVEGAME_SLOT_CURRENT;
extern const int		SAVEGAME_SLOT_QUICK;
extern const int		SAVEGAME_SLOT_MIN;
extern const int		SAVEGAME_SLOT_MAX;

extern const zSTRING	SAVEGAME_DIR;
extern const zSTRING	SAVEGAME_CURRENT_DIR;
extern const zSTRING	SAVEGAME_EXT;
extern const zSTRING	SAVEGAME_HEADER_FILE;
extern const zSTRING	SAVEGAME_GLOBAL_FILE;
extern const zSTRING	SAVEGAME_PIC_FILE;

class zCTexture;

class oCSavegameInfo : public zCObject	
{
	zCLASS_DECLARATION	(oCSavegameInfo)
public:
	oCSavegameInfo();
	oCSavegameInfo(int slotNr);
	virtual ~oCSavegameInfo();	

	void	ReloadResources	();
	void	CleanResources	();

	zBOOL	DoesSavegameExist();

	int		GetSlot			()						{ return m_SlotNr; };
	zSTRING GetName			()						{ return m_Name; };
	zSTRING	GetWorldName	()						{ return m_WorldName; };
	void	GetGameTime		(int& day, int& hour, int& min)	{ day=m_TimeDay;hour=m_TimeHour;min=m_TimeMin; };
	zSTRING	GetGameTime		();
	zSTRING	GetSaveTime		()						{ return m_SaveDate; };
	zSTRING	GetDir			()						{ return m_Dir; };	
	zCTexture* GetThumbPic	()						{ return m_ThumbTex; };
	void	UpdateThumbPic	(zCTextureConvert* texCvt);

	void	SetSlot			(int slotNr);
	void	SetName			(const zSTRING& _name)	{ m_Name=_name; };
	void	SetWorldName	(const zSTRING& _name)	{ m_WorldName=_name; };
	void	SetGameTime		(int day, int hour, int min) { m_TimeDay=day;m_TimeHour=hour;m_TimeMin=min; };
	void	SetDir			(zSTRING dir)			{ m_Dir = dir; };				
	
	// [BENDLIN] 1.30
	int		GetVersionMajor	()	{ return m_verMajor; };
	int		GetVersionMinor	()	{ return m_verMinor; };

	int		GetPlaytimeSeconds	()				{ return m_PlayTimeSeconds; };
	void	SetPlaytimeSeconds	(int sec)		{ m_PlayTimeSeconds = sec; };

	// [BENDLIN] 1.30
	int		GetVersionPoint	()	{ return m_verPoint; };
	int		GetVersionInt	()	{ return m_verInt; };
	zSTRING	GetVersionName	()	{ return m_verName; };

	zBOOL	IsCompatible	()	{ return !m_notCompatible; };

	virtual void Archive	(zCArchiver &arc);
	virtual void Unarchive	(zCArchiver &arc);

protected:

	void	Init			();

	zSTRING				m_Dir;
	zCTexture*			m_ThumbTex;

	// Un/Archive this:
	int			m_SlotNr;
	zSTRING		m_Name;	
	zSTRING		m_WorldName;
	int			m_TimeDay;
	int			m_TimeHour;
	int			m_TimeMin;	
	zSTRING		m_SaveDate;		
	
	// [BENDLIN] 1.30
	int			m_verMajor;
	int			m_verMinor;

	int			m_PlayTimeSeconds;

	// [BENDLIN] 1.30
	int			m_verPoint;
	int			m_verInt;
	zSTRING		m_verName;
	
	zBOOL		m_notCompatible;
};

class oCSavegameManager
{
public:		
	oCSavegameManager			();
	virtual ~oCSavegameManager	();

	void Init();
	void Reinit();
	void ResetThumbs();
	
	void			SetAndWriteSavegame	(int slotNr, oCSavegameInfo* info);
	oCSavegameInfo*	GetSavegame			(int slotNr);

	void	CopyToCurrent	(int slotNr);
	void	CopyFromCurrent	(int slotNr);
	void	ClearCurrent	();

	zSTRING	GetSlotDirName	(int slotNr);	

	void	CleanResources	();

protected:		

	zCArray<oCSavegameInfo*> infoList;	

	oCSavegameInfo* localInfo;

	bool initialized;
};

#endif
