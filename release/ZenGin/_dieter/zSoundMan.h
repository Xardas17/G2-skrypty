/******************************************************************************** 
 
     $Workfile:: zSoundMan.h          $                $Date:: 20.12.00 3:03    $
     $Revision:: 9                    $             $Modtime:: 17.12.00 3:14    $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Sound Manager
   Manages script sounds defined in sfx.d: collision, slide, destruction sounds 
   created       : 12.1.99

 * $Log: /current_work/zengin_work/_Dieter/zSoundMan.h $
 * 
 * 9     20.12.00 3:03 Hildebrandt
 * 
 * 8     4.12.00 17:32 Hildebrandt
 * 
 * 7     20.09.00 21:29 Rueve
 * typedef
 * 
 * 6     13.09.00 15:21 Moos
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 9 $ ($Modtime: 17.12.00 3:14 $)


#ifndef __ZSOUNDMAN_H__
#define __ZSOUNDMAN_H__


#ifndef __ZSOUND_H__
#include <zSound.h>
#endif

#ifndef __ZSTRING_H__
#include <zString.h>
#endif

#ifndef __ZCONTAINER_H__
#include <zContainer.h>
#endif

#ifndef __ZPARSER_CONST_H__
#include <zParser_Const.h>
#endif

#ifndef __ZPARTICLE_H__
#include <zParticle.h>
#endif

#ifndef __ZPARSER_H__
#include <zParser.h>
#endif

class zCCollisionReport;

class zCSoundManager {
public:
	
	// ===============================================================================

	struct zTScriptSoundData {
		zSTRING				file;				// sfx filename
		int					pitchOff;			// pitchoffset in semitones
		int					pitchVar;			// semitone-variance
		int					vol;				// 0..1
		int					loop;				// 0/1
		float				reverbLevel;		// 0..1
		zSTRING				pfxName;
	};
	static zTScriptSoundData	scriptSoundData;

	struct zCSoundEventData {
		zSTRING				name;
		zCSoundFX			*sound;
		zCParticleEmitter	*pfxEmitter;

		zCSoundEventData() {
			name.Clear	();
			sound		= 0;
			pfxEmitter	= 0;
		};


        ~zCSoundEventData() {
            zRELEASE(sound);     // [Moos] Aufräumen...
        }

		void GetData (const zSTRING& prefix, zCSoundFX* &sfx, zCParticleEmitter* &pfx) {
			if (!sound) {
				zSTRING fullName(prefix+name);
				sound		= zsound->LoadSoundFXScript (fullName);
				// Script-Instanz erzeugen, damit der Name des PFX ausgelesen werden kann
				if (sound) {
					zsound->GetSFXParser()->CreateInstance(fullName, &scriptSoundData);
					pfxEmitter	= zCParticleFX::SearchParticleEmitter (scriptSoundData.pfxName);
				};
			};
			sfx	= sound;
			pfx = pfxEmitter;
		};

		void GetData (zCSoundFX* &sfx, zCParticleEmitter* &pfx) {
			if (!sound) {
				sound		= zsound->LoadSoundFXScript (name);
				// Script-Instanz erzeugen, damit der Name des PFX ausgelesen werden kann
				if (sound) {
					zsound->GetSFXParser()->CreateInstance(name, &scriptSoundData);
					pfxEmitter	= zCParticleFX::SearchParticleEmitter (scriptSoundData.pfxName);
				};
			};
			sfx	= sound;
			pfx = pfxEmitter;
		};
/*		void GetSound (zCSoundFX* &sfx) {
			zCParticleEmitter *pfxDummy;
			GetData (sfx, pfxDummy);
		};
		void GetSound (const zSTRING& prefix) {
			if (sound) return sound;
			sound = zsound->LoadSoundFXScript (prefix+name);
			return sound;
		};*/
	};

	// ===============================================================================

	enum zTSndManMedium {
		zSND_MAN_MEDIUM_MODEL	=0,
		zSND_MAN_MEDIUM_ITEM	=1,
		zSND_MAN_MEDIUM_OBJECT	=2,
		zSND_MAN_MEDIUM_LEVEL	=3
	};

	class zCMediumType {
	public:
//		zSTRING					name;		// "MH", "AM", ..
		int						nameInt;
		zSTRING					contents;
	};
	zCArraySort<zCMediumType>	mediumTypeIDList;

	// ===============================================================================

/*	class zCSubTableEntry {
	public:
//		zSTRING						name;			// MAO_ "FL_FI"
		zCSoundEventData			soundEventData;
		void Init() {
			name.Clear();
		};
		zCSoundFX* GetSound () {
			if (sound) return sound;
			sound = zsound->LoadSoundFXScript (name);
			return sound;
		};
		zCSoundFX* GetSound (const zSTRING& prefix) {
			if (sound) return sound;
			sound = zsound->LoadSoundFXScript (prefix+name);
			return sound;
		};
	};
*/
	// ===============================================================================

	class zCTableEntry {
	public:
//		zSTRING							name;					// default-Sound Name, "CS_MHL"
//		zCSoundFX						*defaultSound;
		zCSoundEventData				defaultSoundEventData;
		zCArraySort<zCSoundEventData>	collSndSubTable;

		zCTableEntry();
		void Search (const zSTRING& prefix, const zSTRING& arg, zCSoundFX* &sfx, zCParticleEmitter* &pfx) {
			// prefix: "CS_MHL_", arg: "FL_ST"
			zCSoundEventData entry;
			entry.name = arg;
			int res = collSndSubTable.Search (entry);
			if (res!=-1) {
				collSndSubTable[res].GetData(prefix, sfx, pfx);
			} else {
/*				// default Sound nehmen
				if (defaultSound) return defaultSound;
				defaultSound= zsound->LoadSoundFXScript (name);*/
				defaultSoundEventData.GetData (sfx, pfx);
//				sfx			= defaultSound;
//				pfx			= 0;
			};
		};
		void InsertSub (const zSTRING& arg) {
			zCSoundEventData entry;
//			entry.Init();
			entry.name		= arg;
			collSndSubTable.Insert (entry);
		};
/*		zCSoundFX* GetSound() {
			if (defaultSound) return defaultSound;
			defaultSound= zsound->LoadSoundFXScript (name);
			return defaultSound;
		};*/
	};

	// ===============================================================================

private:
	static zSTRING	mediumIDList;
	static zSTRING	prefixProto;
	enum { zSND_MAN_NUM_COLL_SND= 17 };

	zCTableEntry					collSndTable[zSND_MAN_NUM_COLL_SND];
	zCArraySort<zCSoundEventData>	slideSndTable;
	zCArraySort<zCSoundEventData>	destSndTable;
/*
	DS_<OBJ_MAT>
	SS_<LVL_MAT>
*/

	void DebugMessage (const zSTRING& s);
public:
	zBOOL debugMessageEnabled;

	zCSoundManager() {
		Init();
	};
	void Init ();

	int String2Int (const zSTRING& arg) {
		int r =0;
		for (int i=0; i<arg.Length(); i++)
			r += int(arg[i]) << (i*8); 
		return r;
	};

	int Char2Int (const char c1, const char c2) {
		return int(c1) + (int(c2)<<8);
	};

	zSTRING			SearchMediumTypeIDList	(const int arg, int medType);
	int				GetMediumIndex			(const char arg);
	int				GetCollSndTableIndex	(const zSTRING& arg);

	void			StartHitSound			(zCVob *vobSndSource, zTSndManMedium med1, zTSndManMedium med2, int med1Type, int med2Type, const zCCollisionReport* collisionReport);
	void			StartAttackSound		(zCVob *vobSndSource, zTSndManMedium med1, zTSndManMedium med2, int med1Type, int med2Type);
	zTSoundHandle	StartSlideSound			(zCVob *vobSndSource, int levelType);
	void			StartDestructionSound	(zCVob *vobSndSource, int objectType);
};

extern zCSoundManager *zsndMan;

#endif