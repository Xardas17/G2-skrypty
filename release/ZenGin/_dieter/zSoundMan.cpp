/******************************************************************************** 
 
     $Workfile:: zSoundMan.cpp        $                $Date:: 20.12.00 3:03    $
     $Revision:: 10                   $             $Modtime:: 19.12.00 1:31    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/zengin_work/_Dieter/zSoundMan.cpp $
 * 
 * 10    20.12.00 3:03 Hildebrandt
 * 
 * 9     11.10.00 17:12 Hildebrandt
 * 
 * 8     20/09/00 18:05 Luesebrink
 * 
 * 7     21.08.00 17:18 Hildebrandt
 * 
 * 6     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 5     21.07.00 14:28 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 4     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 3     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 10 $ ($Modtime: 19.12.00 1:31 $)


#include <zCore.h>
#include <zTools.h>
#include <zSoundMan.h>
#include <zWorld.h>
#include <zVob.h>

#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

/*
FIXME:
- evtl. koennte man die String-Suchen in den SubTables durch int-Suchen ersetzen ("FL_FL"
  also in 1 Int gepackt

  attack: cs_
*/

static zREAL SND_RADIUS = zREAL(2500.0f);
//static int SND_RADIUS = zSND_RADIUS_DEFAULT;

zCSoundManager::zTScriptSoundData zCSoundManager::scriptSoundData;

void zCSoundManager::DebugMessage (const zSTRING& s) {
	if (!debugMessageEnabled) return;
	zerr.Message ("D: SoundMan: "+s);
};

static int CompareMediumType ( const void *arg1, const void *arg2 ) {
	zCSoundManager::zCMediumType* a = ((zCSoundManager::zCMediumType*)arg1);
	zCSoundManager::zCMediumType* b = ((zCSoundManager::zCMediumType*)arg2);
//	return a->nameInt > b->nameInt;
	if (a->nameInt<b->nameInt)	return -1; else
	if (a->nameInt>b->nameInt)	return +1; else
								return  0;
}; 

static int CompareSubTableEntry ( const void *arg1, const void *arg2 ) {
	zCSoundManager::zCSoundEventData* a = ((zCSoundManager::zCSoundEventData*)arg1);
	zCSoundManager::zCSoundEventData* b = ((zCSoundManager::zCSoundEventData*)arg2);
	return a->name.CompareTo (b->name);
};

zCSoundManager::zCTableEntry::zCTableEntry() {
//	name.Clear();;
//	defaultSound	= 0;
//	collSndSubTable.AllocAbs(256);
	collSndSubTable.SetCompare (CompareSubTableEntry);
};

zSTRING	zCSoundManager::mediumIDList= zSTRING("MIOL");
zSTRING	zCSoundManager::prefixProto	= zSTRING("CS_XXX_");

/*
	CONST STRING CS_HM = "FL ME DM";

	INSTANCE CS_MAO			(C_SFX_DEF) {file= "MAO;FI;FL.wav";								};
	INSTANCE CS_MAO_FI_FL	(C_SFX_DEF) {file= "MAO;FI;FL.wav";								};

	INSTANCE SS_WO			(C_SFX_DEF) {file= "MAO;FI;FL.wav";								};
	INSTANCE SS_SO			(C_SFX_DEF) {file= "MAO;FI;FL.wav";								};

	INSTANCE DS_WO			(C_SFX_DEF) {file= "MAO;FI;FL.wav";								};
	INSTANCE DS_SO			(C_SFX_DEF) {file= "MAO;FI;FL.wav";								};
*/

zSTRING zCSoundManager::SearchMediumTypeIDList (const int arg, int medType) {
	// "HM", 0 => "FL"
	zCMediumType entry;
	entry.nameInt = arg; 
	int res = mediumTypeIDList.Search (entry);
	if (res==-1) return zSTRING(""); 
	else {
		const zSTRING& cont = mediumTypeIDList[res].contents;
		medType = medType * 3;
		if (medType>=cont.Length()) return zSTRING("");
		return	zSTRING(cont[medType])+
				zSTRING(cont[medType+1]);
	};
};

int zCSoundManager::GetMediumIndex (const char arg) {
	for (int i=0; i<mediumIDList.Length(); i++) {
		if (mediumIDList[i]==arg) return i;
	};
	return 0;
};

int zCSoundManager::GetCollSndTableIndex (const zSTRING& arg) {
	int index;
	int med1 = GetMediumIndex (arg[0]);
	int med2 = GetMediumIndex (arg[2]);
	if (arg[1]=='H') {
		if (med1==zSND_MAN_MEDIUM_MODEL)	index = 0;	else
		if (med1==zSND_MAN_MEDIUM_ITEM)		index = 4-1; else
		if (med1==zSND_MAN_MEDIUM_OBJECT)	index = 7-2;
		index += med2;
	} else {
		if (med1==zSND_MAN_MEDIUM_MODEL)		index = 9;	else
		if (med1==zSND_MAN_MEDIUM_ITEM )		index = 13; else
												index = 13;
		index += med2;
	};
	return index;
};

// =======================================================================================================================

/*--------------------------------------------------------------------------
	
	void zCSoundManager::StartHitSound (..)

    20-Sep-00       [Dennis Luesebrink]
                    added velocity dependent volume
	17-Dec-00		[HILDEBRANDT]
					Replaced zTVobCollisionReport by zCCollisionReport.
--------------------------------------------------------------------------*/ 

void zCSoundManager::StartHitSound (zCVob *vobSndSource, zTSndManMedium med1, zTSndManMedium med2, int med1Type, int med2Type, const zCCollisionReport* collisionReport) 
{
	//
	if (!vobSndSource)					return;
	if (!vobSndSource->GetHomeWorld())	return;

	//
	int index=0; 
	if (med1>med2) {
		zSwap (med1		, med2);
		zSwap (med1Type	, med2Type);
	};
	if (med1==zSND_MAN_MEDIUM_ITEM)		index = 4-1; else
	if (med1==zSND_MAN_MEDIUM_OBJECT)	index = 7-2; 
	index += med2;

	//
	const  zSTRING s (SearchMediumTypeIDList (Char2Int(mediumIDList[med1],'H'), med1Type) + "_" +
					  SearchMediumTypeIDList (Char2Int('H',mediumIDList[med2]), med2Type));
	prefixProto[3] = char(mediumIDList[med1]);
	prefixProto[4] = char('H');
	prefixProto[5] = char(mediumIDList[med2]);

	zCSoundFX			*sound;
	zCParticleEmitter	*pfxEmitter;
	collSndTable[index].Search(prefixProto, s, sound, pfxEmitter);

	// 
	const zREAL MIN_VELO = (80.0F*80.0F);
	zTBBox3D	vobBox;
	zPOINT3		collPos;
	if (collisionReport) 
	{
		if (collisionReport->m_poCollObject1->GetCollObjClass()==zCCollObjectLevelPolys::S_GetCollObjClass())
		{
			// statische Collision (mit Level)
			if (vobSndSource->GetVelocity().Length2()<MIN_VELO) return;
			vobBox		= vobSndSource->GetBBox3DWorld();
			collPos		= vobBox.GetCenter();
			collPos[VY]	= vobBox.mins[VY];
		} 
		else 
		{
			// dynamische Collision (mit anderem Vob)
			zCVob *otherVob	= static_cast<zCVob*>(collisionReport->m_poCollObject1->GetClientData());
			if ((vobSndSource->GetVelocity().Length2()<MIN_VELO) &&
				(otherVob	 ->GetVelocity().Length2()<MIN_VELO))	return;

			collPos		= collisionReport->m_oContactPoint;
			if (otherVob->GetBBox3DWorld().GetVolume()<vobSndSource->GetBBox3DWorld().GetVolume())
				vobBox		= otherVob->GetBBox3DWorld();
			else
				vobBox		= vobSndSource->GetBBox3DWorld();
		};
	} else {
		vobBox	= vobSndSource->GetBBox3DWorld();
		collPos = vobSndSource->GetPositionWorld();
	};
	
	// Sound starten
	if (sound) 
	{
		sound->SetCanBeCachedOut(FALSE);
		zCSoundSystem::zTSound3DParams	params;
		params.SetDefaults	();
		params.radius		= SND_RADIUS;
		params.volume		= ((vobSndSource->GetVelocity()).LengthApprox()/200.0f);
		zClamp(params.volume, 0.6f, 1.0f);

		zsound->PlaySound3D (sound, vobSndSource, zSND_SLOT_MAX, &params); 
	};

	// PFX starten
	if (pfxEmitter)
	{ 
		zCParticleFX	*partFX	= zNEW(zCParticleFX);
		zCVob			*vobFX	= zNEW(zCVob);

		vobFX	->SetCollDet				(FALSE);
		vobFX	->SetPositionWorld			(collPos);
		vobFX	->SetVisual					(partFX);
		vobFX	->SetDontWriteIntoArchive	(TRUE);

		// Emitter-Groesse & Anzahl Partikel an BBox3D anpassen
		zVEC3& pfxDim		= pfxEmitter->shpLineBoxDim;
		pfxDim[VX]			= (vobBox.maxs[VX] - vobBox.mins[VX])*0.4F;
		pfxDim[VZ]			= (vobBox.maxs[VZ] - vobBox.mins[VZ])*0.4F;
		pfxEmitter->ppsValue= zMin (zREAL(64), zMax(zREAL(8), (pfxDim[VX]*pfxDim[VZ]) * 0.04F));
		//
		partFX	->SetEmitter				(pfxEmitter);
		partFX	->CreateParticles			();
											
		vobSndSource->GetHomeWorld()->AddVob(vobFX);
	};

	//
	DebugMessage ("startHitSound: "+prefixProto + ", "+s+ ", soundName: "+((sound) ? sound->GetName() : "%") + "("+zSTRING(med1Type)+","+zSTRING(med2Type)+")");
};

// =======================================================================================================================

void zCSoundManager::StartAttackSound (zCVob *vobSndSource, zTSndManMedium med1, zTSndManMedium med2, int med1Type, int med2Type) {
	int index=0;
	if (med1==zSND_MAN_MEDIUM_MODEL)		index = 9;	else
	if (med1==zSND_MAN_MEDIUM_ITEM )		index = 13; else
											return;
	index += med2;
	//
	const zSTRING  s	(SearchMediumTypeIDList (Char2Int(mediumIDList[med1],'A'), med1Type) + "_" +
						 SearchMediumTypeIDList (Char2Int('A',mediumIDList[med2]), med2Type));
	prefixProto[3] = char(mediumIDList[med1]);
	prefixProto[4] = char('A');
	prefixProto[5] = char(mediumIDList[med2]);

	zCSoundFX			*sound;
	zCParticleEmitter	*pfxEmitter;
	collSndTable[index].Search(prefixProto, s, sound, pfxEmitter);
	if (sound) 
	{
		sound->SetCanBeCachedOut(FALSE);
		zCSoundSystem::zTSound3DParams	params;
		params.SetDefaults	();
		params.radius		= SND_RADIUS;
		zsound->PlaySound3D (sound, vobSndSource, zSND_SLOT_MAX, &params); 
	};
	DebugMessage ("startAttackSound: "+prefixProto + ", "+s+ ", soundName: "+((sound) ? sound->GetName() : "%") + "("+zSTRING(med1Type)+","+zSTRING(med2Type)+")");
};

// =======================================================================================================================

zTSoundHandle zCSoundManager::StartSlideSound (zCVob *vobSndSource, int levelType) {
	zTSoundHandle sndHandle;
	zCSoundEventData entry;
	entry.name = "SS_"+SearchMediumTypeIDList (Char2Int('H','L'), levelType);
	int res = slideSndTable.Search (entry);
	if (res!=-1) {
		zCSoundFX			*sound;
		zCParticleEmitter	*pfxEmitter;
		slideSndTable[res].GetData(sound, pfxEmitter);

		// Sound starten
		if (sound)
		{
			sound->SetCanBeCachedOut(FALSE);
			zCSoundSystem::zTSound3DParams	params;
			params.SetDefaults	();
			params.radius		= SND_RADIUS;
			sndHandle = zsound->PlaySound3D (sound, vobSndSource, 7, &params); 
		};

	};
	return sndHandle;
};

// =======================================================================================================================

void zCSoundManager::StartDestructionSound (zCVob *vobSndSource, int objectType) {
	//
	if (!vobSndSource) return;

	//
	zCSoundEventData entry;
	entry.name = "DS_"+SearchMediumTypeIDList (Char2Int('H','O'), objectType);
	int res = destSndTable.Search (entry);
	if (res!=-1) {
		zCSoundFX			*sound;
		zCParticleEmitter	*pfxEmitter;
		destSndTable[res].GetData(sound, pfxEmitter);

		// Sound starten
		if (sound)
		{
			zCSoundSystem::zTSound3DParams	params;
			params.SetDefaults	();
			params.radius		= SND_RADIUS;
			zsound->PlaySound3D (sound, vobSndSource, 6, &params); 
		};

		// PFX starten
		if (pfxEmitter)
		{ 
			zCParticleFX	*partFX	= zNEW(zCParticleFX);
			zCVob			*vobFX	= zNEW(zCVob);

			vobFX	->SetCollDet				(FALSE);
			vobFX	->SetPositionWorld			(vobSndSource->GetPositionWorld());
			vobFX	->SetVisual					(partFX);
			vobFX	->SetDontWriteIntoArchive	(TRUE);
			partFX	->SetEmitter				(pfxEmitter);
			partFX	->CreateParticles			();
												
			vobSndSource->GetHomeWorld()->AddVob(vobFX);
		};
	};
};

// =======================================================================================================================

void zCSoundManager::Init() {
	//
	debugMessageEnabled = FALSE;

	//

#ifdef ZENGINE_DEBUG
/*	zCParser *sfxParser = zNEW(zCParser);
	sfxParser -> Parse("sfx.src");
	sfxParser -> CreatePCode();*/
	zCParser *sfxParser = zsound->GetSFXParser();
//	debugMessageEnabled = TRUE;
#else
	zCParser *sfxParser = zsound->GetSFXParser();
#endif

	if (!sfxParser) return;

	//
	mediumTypeIDList.SetCompare (CompareMediumType);
	slideSndTable.SetCompare	(CompareSubTableEntry);
	destSndTable.SetCompare		(CompareSubTableEntry);
	
	zSTRING name, nameID, nameArg;
	int numSnd	= 0;
	int max		= sfxParser->GetNumSymbols();
	for (int i=0; i<max; i++) {
		zCPar_Symbol *sym	= sfxParser->GetSymbol (i);
		name				= sym -> name;								// "CS_MAO_FL_WO"
//		nameID				= name.PickWord (2, "_", "_");
		nameID				= name;										// "MAO_FL_WO"
		nameID.Delete ("_", zSTR_TO);
//		if ((name[1]=='S') && (name[2]=='_'))	zerr.Message ("D: Sound: "+name);
		if (sym->type==zPAR_TYPE_STRING) {
			if (name.Search("CS_")!=-1) {
				// Collision Sounds
				if (name.Length()==5) {
					// CS_HM
					zCMediumType mediumType;
//					mediumType.name			= nameID;
					mediumType.nameInt		= String2Int(nameID);
					sym->GetValue			(mediumType.contents);
					mediumTypeIDList.Insert (mediumType);
				};
			};
		} else 
		if (sym->type==zPAR_TYPE_INSTANCE) {
			if (name.Search("CS_")!=-1) {
				int ind = GetCollSndTableIndex (nameID);
				// Collision Sounds
				if (name.Length()==6) {
					// CS_MAO
					collSndTable [ind].defaultSoundEventData.name = name;
				} else
				if (name.Length()==12) {
					// CS_MAO_FI_FL
					nameArg = nameID;
					nameArg.Delete ("_", zSTR_TO);
					collSndTable [ind].InsertSub (nameArg);
				};
				numSnd++;
			} else
			if (name.Search("SS_")!=-1) {
				// SlideSounds
				zCSoundEventData entry;
//				entry.Init();
				entry.name		= name;
				slideSndTable.Insert(entry);
				numSnd++;
			} else
			if (name.Search("DS_")!=-1) {
				// Destruction Sounds
				zCSoundEventData entry;
//				entry.Init();
				entry.name		= name;
				destSndTable.Insert(entry);
				numSnd++;
			};
		};
	};
	for (int j=0; j<zSND_MAN_NUM_COLL_SND; j++) {
		collSndTable[j].collSndSubTable.QuickSort();
	};
	mediumTypeIDList.QuickSort();
	slideSndTable	.QuickSort();
	destSndTable	.QuickSort();
	zerr.Message ("D: zCSoundManager: script sounds registered: "+zSTRING(numSnd));
};

zCSoundManager *zsndMan = 0;

/*
=======================================================================================================================

- Zerstörungs-SFX	: clay, bone,..
- Slide-Sounds		: MSL, ISL, OSL		(nur das Level-Material wird differenziert: MSL_WO, MSL_ST,..)
- Defaults			: fuer jede einzelne Tabelle "MAO", "IHO",..


· MODEL_HITS_MODEL		· ITEM_HITS_MODEL		· OBJECT_HITS_MODEL		· LEVEL_HITS_MODEL
· MODEL_HITS_ITEM		· ITEM_HITS_ITEM		· OBJECT_HITS_ITEM		· LEVEL_HITS_ITEM
· MODEL_HITS_OBJECT		· ITEM_HITS_OBJECT		· OBJECT_HITS_OBJECT	· LEVEL_HITS_OBJECT
· MODEL_HITS_LEVEL		· ITEM_HITS_LEVEL		· OBJECT_HITS_LEVEL		· LEVEL_HITS_LEVEL

17 Tabellen

A Trefferart			:			- treffer, abpraller, abpraller, abpraller
A Model-Waffenart		:			- Faust, Fuss, Maul, Schwanz
A Item-Waffenart		:			- dagger, 1hs, 1ha, 2hs, 2ha, shield, bow, cbow
- Model-Ruestungen		:			- leather, cloth, metal
- Level-Material		:			- metal, stone, wood, earth, water
- Item/Object-Material	:			- wood, metal, stone, flesh, leather

- Object: Material
- Item	: Material(5), ATTACK: Waffenart(8)
- Model	: Ruestung (=Material??), ATTACK: natuerliche Waffenart(4), Trefferart(4)

· MODEL_HITS_MODEL		 
· MODEL_HITS_ITEM		· ITEM_HITS_ITEM	4	 
· MODEL_HITS_OBJECT		· ITEM_HITS_OBJECT		· OBJECT_HITS_OBJECT	7
· MODEL_HITS_LEVEL		· ITEM_HITS_LEVEL		· OBJECT_HITS_LEVEL		

*nicht* symmetrisch:

· MODEL_ATTACKS_MODEL 9	· ITEM_ATTACKS_MODEL	
· MODEL_ATTACKS_ITEM	· ITEM_ATTACKS_ITEM	
· MODEL_ATTACKS_OBJECT	· ITEM_ATTACKS_OBJECT	
· MODEL_ATTACKS_LEVEL	· ITEM_ATTACKS_LEVEL	

=======================================================================================================================

StartAttackSound		( MODEL, OBJECT, int, int)
StartHitSound			( MODEL, OBJECT, int, int)
StartSlideSound
StartDestructionSound

DS_<OBJ_MAT>
SS_<LVL_MAT>

MH,IH,OH,HM,HI,HO,HL

MA,IA,AM,AI,AO,AL

CONST STRING CS_HM = "FL ME DM";

INSTANCE CS_MAO			(C_SFX_DEF) {file= "MAO;FI;FL.wav";								};
INSTANCE CS_MHL			(C_SFX_DEF) {file= "MAO;FI;FL.wav";								};
INSTANCE CS_MAO_FI_FL	(C_SFX_DEF) {file= "MAO;FI;FL.wav";								};
INSTANCE CS_MHL_FL_ST	(C_SFX_DEF) {file= "MHL;FI;ST.wav";								};
INSTANCE MHL_ME_ST		(C_SFX_DEF) {file= "MHL;ME;ST.wav";								};
INSTANCE MHL_FL_WA		(C_SFX_DEF) {file= "MHL;FI;WA.wav";								};
INSTANCE MAL_FI_ST		(C_SFX_DEF) {file= "MAL;FI;ST.wav";								};
INSTANCE MAL_FI_WO		(C_SFX_DEF) {file= "MAL;FI;WO.wav";								};
INSTANCE MAL_FI_WA		(C_SFX_DEF) {file= "MAL;FI;WA.wav";								};
INSTANCE MAL_FI_ME		(C_SFX_DEF) {file= "MAL;FI;ME.wav";								};
INSTANCE IHM_WO_FL		(C_SFX_DEF) {file= "IHM;WO;FL.wav";								};
INSTANCE IHM_WO_ME		(C_SFX_DEF) {file= "IHM;ST;ME.wav";								};
INSTANCE IHM_ST_ME		(C_SFX_DEF) {file= "IHM;ST;ME.wav";								};
INSTANCE IAM_BO_DM		(C_SFX_DEF) {file= "IAM;BO;DM.wav";								};
INSTANCE IAM_1H_DM		(C_SFX_DEF) {file= "IAM;1H;DM.wav";								};
INSTANCE IAM_2H_DM		(C_SFX_DEF) {file= "IAM;2H;DM.wav";								};

Startup:
- Die sfx.d wird nach Coll-Sounds durckaemmt. Diese werden in eine sortierte String-Liste eingetragen (inkl.
  Ptr auf ein zCSoundFX)

PlaySound:
- Die Params werden in Strings umgewandelt. Die "Materialen" werden auch per Skript konvertiert.
																									   
*/

/*
PFX - SFX Vorschläge, offene Fragen
===================================

CS - Collision
DS - Destruction	- pro Obj_Material
SS - Slide			- pro Level_Material
Untergrund

Untergrund-PFX, Destruction-PFX und Slide-PFX würden sich optimal zusammen mit den entsprechenden SFX ansteuern lassen 
indem man in der SFXINST.d den Sound-Instanzen einen PFX-Namen zuordnet.
- Wie werden die Slide-PFX der Modelgröße angepaßt?
- Slide-PFX sollten auch für rutschende Objekte und Items benutzt werden
- EventSFXGrnd-Events müssen auch Objektmaterialien berücksichtigen (z.B. Gehen auf einem Tisch)

Collision-PFX sollten ebenfalls den SFX-Instanzen zugeordnet werden, es könnte allerdings sinnvoll sein, die Form/Größe 
der an der Kollision beteiligten Items/Objekte/Models zu berücksichtigen und die PFX automatisch entsprechend zu 
modifizieren. Wenn man z.B. einen "Apfel" ins Wasser wirft sollte möglichst weniger Wasser spritzen, als bei einer 
Zweihand-Axt ;) 

Collision-SFX-Defaults:
Es wäre sehr zeitsparend und wesentlich übersichtlicher, wenn man "Wildcards" benutzen könnte. Vorschlag: Statt z.B. 
"CS_IHL", könnte als Default "CS_IHL_ALL_ALL" angegeben werden. Da eine solch globale Angabe aber meist nicht sinnvoll ist,
wäre es dann z.B. auch möglich "CS_IHL_ALL_WA" anzugeben (für jedes Item, egal welches Material, wird der gleiche Sound 
benutzt, wenn es ins Wasser fällt). Ein solcher Default wäre im Gegensatz zur jetzigen Lösung äußerst sinnvoll einsetzbar!
Insbesondere wenn noch weitere Level-Materialien hinzukommen, wird sonst die Anzahl der in der SFXINST.d aufzuführenden 
Kollisions-Kombinationen extrem hoch!

SFX-Vereinfachungen:
Die Fälle "... hits Item" (MHI; OHI; IHI) könnten wegfallen, da sie in der Praxis kaum sinnvoll einsetzbar sind.
Auch für "Model attacks Item" (MAI) gibt es sehr wahrscheinlich keine sinnvolle Anwendung.

Mindestgeschwindigkeit:
Alle Kollisions-SFX (X hits Y) dürfen nur dann ausgelöst werden, wenn die Kollision eine Mindeststärke hat 
(Aufprallgeschwindigkeit?).
Für Models sollte eventuell sogar nur dann ein Kollisions-Sound getriggert werden, wenn sie FALLEND auf ein Hindernis 
treffen, da es dann ein deutliches optisches Feedback gibt (SC liegt am Boden). Sollte auch das Rennen gegen ein Hindernis 
einen Sound auslösen, muß es ebenfalls dazu ebenfalls ein optisches Feedback (Oops) geben. Noch besser wäre es aber 
wahrscheinlich, wenn Models _nur_ fallend Kollisions-SFX auslösen.
! Zur Zeit werden manchmal unzählige collision sounds getriggert, wenn man ein objekt nur berührt!

Attack-SFX:
In der Kategorie "Item Attacks" fehlen noch Waffen wie "Arrow", "Bolt" und "Club".
Die Geschosse sind allerdings nur für "Item attacks Level" und "Item attacks Model" wichtig, da "Item attacks Item" immer 
eine Nahkampfhandlung ist!
- Die Kategorie "Attacks Item" sollte statt Materialbezeichnungen ebenfalls Waffenkategorien enthalten, so daß es ein 
  Unterschied ist ob ein Dolch mit einem Dolch kollidiert (IAI_DA_DA) oder mit einem Zweihänder (IAI_DA_2S).
- Die Attack-Sounds müssen nach regeltechnischen Gesichtspunkten angesteuert werden. Nicht eine tatsächliche Kollision 
  der Waffen sollte ausschlaggbend sein, sondern ob regeltechnisch eine Kollision stattgefunden hat (z.B. Parade).

Blut-Pfx:
- Sollten pro Spezies unterschiedlich sein ( Butfarbe, etc.) und zusätzlich je nach Schadenshöhe modifiziert werden. 
  Eine automatische Anpassung der Partikel-Flugrichtung an die Richtung des Schlages/Schusses wäre gut.
- Es sollte einen "Blut"-Switch geben, mit dem man alle Blut-Effekte zwischen internationaler und "zensierter" Version 
  toggeln kann


+1+ |AB-0876| Kollisions-Sfx: Wirft man ein Item in Wasser oder springt selbst hinein, wird kein Kollisions-Sound 
			  getriggert (Testlevel)
+1+ |AB-0933| Kollisions-SFX: Es ist nicht genau nachzuvollziehen, welcher Kollisions-Sound gerade gespielt wird. Könnte 
			  man das als DEBUG-Info (Togglebar?) anzeigen lassen? IAL-Kollisionen scheinen nicht zu funzen (mit einer
			  Waffe gegen die Wand schlagen). Ebenso alle Kollisions-SFX die mit Wasser zu tun haben. Es ist außerdem 
			  nicht klar, welche Sounds benutzt werden wenn im Nahkampf zwei Waffen aufeinandetreffen (IAI?). Es wird 
			  immer das gleiche Sample gespielt, obwohl in der SFXINST.d unterschiedliche angegeben sind.
+1+ |AB-0425| PFX: Verschiedene Blut-Effekte je nach Schadenshöhe und je nach Spezies. Wenn kein Schaden verursacht wird, 
			  darf auch kein Blut spritzen (aber vielleicht ein anderer dezenter PFX).
+1+ |AB-0945| Sound: beim "WARN Sound Identifier unknown" muß unbedingt der Name des betreffenden Identifiers ausgegeben 
			  werden, damit eine Fehlersuche möglich ist
+1+ |AB-0880| Collision-SFX-Defaults: Es wäre sehr zeitsparend und wesentlich übersichtlicher, wenn man "Wildcards" 
			  benutzen könnte. Vorschlag: Statt z.B. "CS_IHL", wird als Default "CS_IHL_ALL_ALL" angeben. Da eine solch 
			  globale Angabe aber meist nicht sinnvoll ist, könnte man z.B. auch "CS_IHL_ALL_WA" angeben (für jedes Item, 
			  egal welches Material, wird der gleiche Sound benutzt, wenn es ins Wasser fällt). Ein solcher Default wäre 
			  äußerst sinnvoll einsetzbar!


*/

/*
http://www.ln.com.ua/~zssoft/vital/
Physics and Sound

   The special attention was given to physical engine. Because it makes
an atmosphere of the "different" world. The level seems simply as a set
of triangles without it. Elevators/doors/buttons/sounds are the "heart" of
the game. Vital Engine ZL supports both DirectSound3D and A3D 1.0
(therefore all sound sources are 3D). Moreover, engine supports
ambient sound. We used the physical model similar to real one: each
body has mass, volume, friction factor, the surface type. So, more
packed objects sink in water meanwhile less packed objects float. If
you stand on wooden raft then it starts sink under the weight of your
body. The waves size depends on mass and volume of the fallen object.
There are some currents may exist under the water. The player can
push/roll objects. When object falls (f.e. barrel) the corresponding
sound is played, it depends on what surface object fell, from what
height and in what room (sounds under the water/in small/ in large/in
metal rooms are different). The foot-steps sounds on different surfaces
are different too. Aural range depends on the surface
(metal/wooden/...) we move and whether we walk or run. In Vital
Engine ZL you can break the objects and unlike Sin, for example,
broken lamp doesn't light.
*/