/******************************************************************************** 
 
     $Workfile:: zResource.cpp        $                $Date:: 24.04.01 17:34   $
     $Revision:: 33                   $             $Modtime:: 22.04.01 22:02   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zResource.cpp $
 * 
 * 33    24.04.01 17:34 Edenfeld
 * Patch 1.08a
 * 
 * 32    17.03.01 2:10 Hildebrandt
 * 
 * 31    30.01.01 23:51 Hildebrandt
 * 
 * 30    27.11.00 10:35 Moos
 * 
 * 29    24.11.00 11:01 Moos
 * 
 * 28    21.11.00 11:11 Moos
 * 
 * 27    20.11.00 20:20 Moos
 * 
 * 26    26.10.00 17:06 Pelzer
 * 
 * 25    25.10.00 16:48 Pelzer
 * 
 * 24    10.10.00 18:27 Edenfeld
 * 
 * 23    10.10.00 18:20 Edenfeld
 * 
 * 22    4.10.00 23:46 Hildebrandt
 * 
 * 21    2.10.00 19:20 Pelzer
 * 
 * 20    29.09.00 19:56 Pelzer
 * 
 * 19    29.09.00 19:34 Pelzer
 * 
 * 18    29.09.00 12:58 Pelzer
 * 
 * 17    28.09.00 18:57 Pelzer
 * 
 * 16    12.09.00 21:49 Pelzer
 * 
 * 15    7.09.00 20:42 Hildebrandt
 * 
 * 14    31.08.00 17:04 Hildebrandt
 * 
 * 13    14.08.00 21:56 Pelzer
 * 
 * 12    17.07.00 18:52 Hildebrandt
 * 
 * 11    11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 10    6.07.00 13:45 Hildebrandt
 * 
 * 6     9.05.00 21:14 Hildebrandt
 * zenGin 089h
 * 
 * 5     8.05.00 5:29 Hildebrandt
 * zenGin 089g
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 3     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 1     10.01.00 15:15 Hildebrandt
 * zenGin 0.85a
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 33 $ ($Modtime: 22.04.01 22:02 $)
 
#include <zCore.h>
#include <zResource.h>

// debug..
#include <zView.h>
#include <zInput.h>

zCLASS_DEFINITION_ABSTRACT (zCResource, zCObject, 0)

/*
  zBOOL SetName (const zSTRING& objectName);
  class::CreateInstance (objectName);
  zCMesh::GetStaticClassDef()->RegisterFileFormat();
  fileFormat->Load (fileName, object);

  zCMesh *mesh = zCMesh::GetStaticClassDef()->LoadResource ("sword.3ds");
  zCMesh *mesh = zCMesh::GetStaticClassDef()->LoadResource (arc	, chunkName);
  zCMesh *mesh = zCMesh::GetStaticClassDef()->LoadResource (file);

  class::LoadResource (objectName, arc);
  - obj_sharing ? => suche interne liste durch, addref falls vorhanden & exit
    falls arc uebergeben worden ist: naechsten Object-Chunk oeffnen & skippen
  - new obj; new arc; arc.ReadObject (obj);

  - FileFormat Klassen, Loader/Saver ? generalisieren
*/

/*

  - Lightmaps:
    Werden ueber "spezielle" Pfade in zCTexture Objekten abgelegt (zCWorld LightCompile oder
	zCWorld Unarchive). Hierbei werden sie gleich als CachedIn und locked markiert und gelangen
	so nicht in die zCResourceManager cachedInList.
  - Ani-Textures:
    Anzahl Kanaele und Frames werden bereits direkt beim beim zCTexture::Load()/SetName() ermittelt.
	Beim Rendern wird dann die benoetigte Textur ueber zCMaterial::GetAniTexture() ermittelt und bei
	Bedarf cachedIn.
	IDEE: die jeweils ersten Frames von Ani-Seq. precachen ? oder beim CacheIn des ersten Frames auch
	bereits die naechsten precachen ?

  TODO:
  - wenn in beiden Threads (Main und resMan Thread) gleichzeitig geladen wird (LoadResource()), kann
    es scheinbar derzeit noch zu Problemen kommen. Beispiel: in beiden Threads sollen Texturen geladen
	werden, die aber noch nicht konvertiert wurden. Beide scannen dann mittels CRT-Funktionen die 
	Festplatte durch und stoeren sich gegenseitig (sollten die denn nicht thread-safe sein ???)
	=> scheint durch eine Critical Section im zCTexture entschaerft (in ..::ConvertTexture())..

*/

//const zCThread::zTThread_Prio WORKER_THREAD_PRIORITY = zCThread::zTHREAD_PRIORITY_BELOW_NORMAL;
const zCThread::zTThread_Prio WORKER_THREAD_PRIORITY = zCThread::zTHREAD_PRIORITY_NORMAL;

///////////////////////////////////////////////////////////////////////////
//    zCResource
///////////////////////////////////////////////////////////////////////////

zCResource::zCResource()
{
	nextRes			= 0;
	prevRes			= 0;
	timeStamp		= 0;
	cacheState		= zRES_CACHED_OUT;
	cacheOutLock	= FALSE;
	cacheClassIndex	= 255;
	managedByResMan	= FALSE;
	cacheInPriority	= (zMAX_CACHE_IN_PRIO >> 1);		// 0.5
	canBeCachedOut	= TRUE;
};

zCResource::~zCResource()
{
//	zresMan->CacheOut	(this);			// ??????
	nextRes			= 0;
	prevRes			= 0;
};

void zCResource::SetCacheInPriority	(const zREAL prio)
{
	cacheInPriority	= zFloat2Int (zREAL(zMAX_CACHE_IN_PRIO) * prio);
};

static void GiveFatal() {
	zERR_FATAL ("D: This method should be overriden! Illegal zCResource class setup!");
};

zBOOL zCResource::LoadResourceData () {
	GiveFatal();
	return FALSE;
};

zBOOL zCResource::ReleaseResourceData () {
	GiveFatal();
	return FALSE;
};

zDWORD zCResource::GetResSizeBytes () {
	GiveFatal();
	return 0;
};

void zCResource::GetCacheConfig (zDWORD &numMaxResources, zDWORD &cacheSizeMaxBytes) {
	GiveFatal();
};

void zCResource::CacheOut ()
{
	if (GetCacheOutLock()) return;
	zresMan->CacheOut (this);
};

void zCResource::TouchTimeStamp ()
{
	// refreshes timeStamp if resource is currently cached in
//	if (GetCacheState()!=zRES_CACHED_IN)					return;
	zERR_ASSERT (GetCacheState()==zRES_CACHED_IN);
	if (GetTimeStamp ()==zresMan->GetCurrentTimeStamp())	return;
	timeStamp = ztimer.GetTotalTime	();
	zresMan->TouchTimeStamp			(this);
};			

void zCResource::TouchTimeStampLocal ()
{
	timeStamp = ztimer.GetTotalTime	();
};

/*--------------------------------------------------------------------------
    zCResource::LockStateChange()

    14-Aug-00       [PELZER]
                      Lock des Resource-Status zwecks Syncronisierung beim Multithreading
--------------------------------------------------------------------------*/ 

void zCResource::LockStateChange ()
{
	stateChangeGuard.Lock();
};

/*--------------------------------------------------------------------------
    zCResource::UnlockStateChange()

    14-Aug-00       [PELZER]

                      Unlock des Resource-Status zwecks Syncronisierung beim Multithreading
--------------------------------------------------------------------------*/ 

void zCResource::UnlockStateChange () // Unlock des Resource-Status[PELZER] 
{
	stateChangeGuard.Unlock();
};

///////////////////////////////////////////////////////////////////////////
//    zCResourceManager
///////////////////////////////////////////////////////////////////////////

// wieviele Res duerfen pro Frame maximal geladen werden ? (noThreads)
//enum { zNUM_MAX_RES_CACHE_IN_PER_FRAME = 16 }; 
enum { zNUM_MAX_RES_CACHE_IN_PER_FRAME = 99999 }; 

zCResourceManager *zresMan=0;

zCResourceManager::zCResourceManager() 
{
	cacheInQueueHead		= 0;
	cacheInQueueTail		= 0;
//	threadingEnabled		= FALSE;
	threadingEnabled		= TRUE;
	numQueued				= 0;
	currentTimeStamp		= 0;
	numResCachedInThisFrame	= 0;
	cacheInImmediatelyMsec	= 0;
	goToSuspend				= FALSE;
#ifdef ZENGINE_DEBUG
	showDebugInfo			= FALSE;
#else						
	showDebugInfo			= FALSE;
#endif						
							
	InitClassCache			();
};

zCResourceManager::~zCResourceManager()
{
	PurgeCaches();
};

/*--------------------------------------------------------------------------

    zCResourceManager::PurgeCaches(zCClassDef *resClassDef)

    14-Aug-00       [PELZER]
                      Änderung: Nun wird der Worker-Thread zunächst schlafen geschickt
					  und erst dann die Queue geleert und die bereits eingecachten Resourcen
					  gelöscht

    20-Nov-00       Assertion-Failure weggemacht

--------------------------------------------------------------------------*/ 

void zCResourceManager::PurgeCaches(zCClassDef *resClassDef)
{
	// zunächst den Thread schlafen schicken ... [PELZER]
	goToSuspend = TRUE;
	// warten, bis alle gerade eingeladenen Resourcen da sind und der Thread wieder suspended ist
	while ((IsThreadRunning()) && (!IsSuspended()));
	// [BENDLIN] 2002-05-17, moved to the end of purging
	// goToSuspend = FALSE; // Nicht im ThreadProc auf FALSE zurückstellen

	// FIXME: hier werden bisher noch alle classCaches geloescht.. spezifische Erweiterung fehlt..
	// die Queue loeschen
	zCResource *res=GetNextCacheInQueue();
	while (res)
	{
		res->CacheOut();
		res = GetNextCacheInQueue();
	};
	numQueued=0;	// Korrektur, wurde fuer jede Resource 2x runtergezaehlt: 1x in GetNextCacheInQueue(), 1x in CacheOut()

	// jetzt die bereits eingecachten Resourcen loeschen
	// ASSERT: Die Queue ist leer und der Thread ist suspended
	for (int i=0; i<classCacheList.GetNum(); i++)
	{
		zCClassCache	*classCache			= &(classCacheList[i]);
//		zCResource		*res				= classCache->resListHead;
		if ((resClassDef==0) || (resClassDef==classCache->resClassDef))
		{
			zCResource *res= classCache->resListHead;
			while (res)
			{
				zERR_ASSERT_STRICT (res->GetRefCtr()>=1);	// sanity
                zCResource *nextRes = res->nextRes;
				// Resources mit CacheOutLock werden hier nicht ausgecachet..
				if (!res->GetCacheOutLock()) {
					res->CacheOut();
    				res = classCache->resListHead; // [Moos] fange lieber wieder von vorne an; denn nextRes kann schon rekursiv beseitigt worden sein.
				}
                else
                    res = nextRes;
			};
		};
	};
	// [BENDLIN] 2002-05-17, moved to the end of purging
	goToSuspend = FALSE;
};

void zCResourceManager::SetThreadingEnabled	(const zBOOL b) 
{ 
	threadingEnabled= b;		
};

zBOOL zCResourceManager::GetThreadingEnabled () const 
{ 
	return threadingEnabled;
};

void zCResourceManager::InitClassCache()
{
	zCClassDef* classDef;
	zCClassDef* classDefBase	= zCResource::GetStaticClassDef ();
	zCArray<zCClassDef*>	classDefList;
	for (int i=0; i<zCClassDef::GetNum(); i++) 
	{
		classDef = zCClassDef::GetClassDefByIndex (i);
		// Nur Klassen registrieren, die von zCResource abgeleitet sind und das zCLASS_FLAG_RESOURCE besitzen
		if (classDef->GetClassFlags() & zCLASS_FLAG_RESOURCE)
		{
			if (zCObject::CheckInheritance (classDefBase, classDef))
			{
				classDefList.Insert (classDef);
			} else
				zERR_FATAL ("D: Class has zCLASS_FLAG_RESOURCE but does not inherit zCResource!");
		};
	};

//	zERR_MESSAGE (3, 0, "D: RESMAN: Num classes registered: "+zSTRING(classDefList.GetNum()));
	classCacheList.AllocAbs			(classDefList.GetNum());
	classCacheList.MarkNumAllocUsed	();
	zSTRING s;
	for (i=0; i<classDefList.GetNum(); i++)
	{
		classCacheList[i].resClassDef	= classDefList[i];
		s += classDefList[i]->GetClassName_()+" ";
	};
	zERR_MESSAGE (3,0,"D: RESMAN: Classes registered: "+s);
};

/*--------------------------------------------------------------------------
    zCResourceManager::zCClassCache* zCResourceManager::GetClassCache (zCResource *res)

    7-Sep-00		[HILDEBRANDT]
					Falls eine von zCResource abgeleitete Klasse wiederum nur abstrakte Basisklasse und Interface 
					ist, von denen Implementationen abgeleitet sind, so hat nur die Interface Klasse das Class-RESOURCE
					Flag. Habe hier Code hinzugefuegt, der zu einer Implementationsklasse die dazugehoerige Resource
					Basisklasse heraussucht.
--------------------------------------------------------------------------*/ 

zCResourceManager::zCClassCache* zCResourceManager::GetClassCache (zCResource *res)
{
	zERR_ASSERT (res);
	if (res->cacheClassIndex>=255)
	{
		// Falls in einer Klassenhierarchie nicht die Klasse selbst eine 'Resource' ist, sondern
		// eine Basisklasse, so muss diese ersteinmal gesucht werden.
		zCClassDef *classDef = res->GetClassDef();
		while ((classDef) && (!(classDef->GetClassFlags() & zCLASS_FLAG_RESOURCE)))
		{
			classDef = classDef->GetBaseClassDef();
		};
		zERR_ASSERT (classDef);
		if (!classDef)	classDef = res->GetClassDef();

		res->cacheClassIndex	= GetClassCacheIndex (classDef);
		zERR_ASSERT (res->cacheClassIndex>=0);
	};
	return &(classCacheList[res->cacheClassIndex]);
};

int zCResourceManager::GetClassCacheIndex (zCClassDef *resClassDef)
{
	for (int i=0; i<classCacheList.GetNum(); i++)
		if (classCacheList[i].resClassDef==resClassDef) return i;
	return -1;
};

// ======================================================================================================

void zCResourceManager::LoadResource (zCResource *res)
{
	zERR_ASSERT (res);
	
	// bereits cached in ?
	zTResourceCacheState resCacheState = res->GetCacheState();
	if (resCacheState==zRES_CACHED_IN) {
		return;
	}
	if (resCacheState==zRES_LOADING) {
		return;
	}

	// Resource laden
	res->SetCacheState		(zRES_LOADING);
	res->LoadResourceData	();

	zCClassCache *classCache= GetClassCache (res);

	// .. und als cachedIn registrieren
	res->SetCacheState		(zRES_CACHED_IN);			// erst ganz am Ende auf "CACHED_IN" setzen, der andere Thread koennte auf dieses Signal warten
	//  Vorsicht! Die Resource ist hier als cached in markiert, aber noch nicht in der internen
	// liste gespeichert -> Bei einem Queraustieg z.B. könnten Memleaks entstehen, 
	// diese Vorgehensweise ist aber nötig, da bei einem CacheIn(-1) in einem GetResSizeBytes() ansonsten
	// zyklische nicht beendende Ruckler entstehen (Grund ?)

	classCache->InsertRes	(res);

	numResCachedInThisFrame++;
};

/*--------------------------------------------------------------------------

    zCResourceManager::CacheOut(zCResource *res)
    28-Sep-00       [PELZER]
                    Änderung: Sonderbehandlung von Immediate-Resourcen - Worker-Thread-Prio wird verändert
    03-Oct-00       [HILDEBRANDT]
                    Spy Meldung 'Immediate resource cached' von DEBUG_PELZER abhaengig gemacht.
--------------------------------------------------------------------------*/ 

zTResourceCacheState zCResourceManager::CacheIn (zCResource *res, zREAL priority)
{
	zERR_ASSERT (res);

	// Resource ohne gueltigen Namen abweisen
	if (res->GetObjectName().Length()<=0)	return zRES_FAILURE;

	//
	if (GetCacheInImmediately())	priority = -1; 

	// bereits cachedIn oder in Bearbeitung ?
	zTResourceCacheState resCacheState		= res->GetCacheState();
	if (resCacheState==zRES_CACHED_OUT)
	{
		res->AddRef					();						// der ResMan ist nun mit-Besitzer der Resource
		res->managedByResMan		= TRUE;
		// genau jetzt einladen oder queuen ?
		if (priority<0) {
			zBOOL workerThreadActive = FALSE;
			if( GetThreadingEnabled() )
				workerThreadActive = !IsSuspended();
			if( workerThreadActive )
			{
				goToSuspend = TRUE;
				// [BENDLIN] 2002-05-17, FIXME TEST
				// warten, bis alle gerade eingeladenen Resourcen da sind und der Thread wieder suspended ist
				while ((IsThreadRunning()) && (!IsSuspended()));
				LoadResource			(res);
				goToSuspend = FALSE;
				QueueProcess_Resume();
			}
			else
				LoadResource			(res);
#ifdef DEBUG_PELZER
			zerr.Message( "X: CacheIn: Immediate resource cached in via main thread: "+zSTRING(res->GetObjectName())+" !" );
#endif

		} else {
			InsertCacheInQueue		(res, priority);
		};

		// FIXME: in beiden Threads parallel zu laden scheint schlecht: der Plattenkopf wuerde immer hin&her springen..
		// FIXME: LoadResource() in beiden Threads gleichzeitig funzt leider noch nicht...
		// Wenn die Queue ueberlastet ist hier vom Anfang der Queue Jobs abtragen..
/*		while (numQueued>64) 
		{
			zCResource *nextRes		= GetNextCacheInQueue();
			LoadResource			(nextRes);
		};
*/
	} else
	if (resCacheState==zRES_CACHED_IN)
	{
		// nichts zu tun..
	} else
	if (priority<0) 
	{
		// zRES_QUEUED, zRES_LOADING..
		if( GetThreadingEnabled() )
		{
			SetThreadPrio( zTHREAD_PRIORITY_HIGHEST );
			WaitForCacheIn (res);
			SetThreadPrio( WORKER_THREAD_PRIORITY );
		}
		else
			WaitForCacheIn (res);
		zerr.Warning( "X: CacheIn: Immediate resource cached in via worker thread: "+zSTRING(res->GetObjectName())+" !" );
	};

	return res->GetCacheState();
};

/*--------------------------------------------------------------------------

    zCResourceManager::CacheOut(zCResource *res)
    14-Aug-00       [PELZER]
                      Änderung: Das potentielle Problem eines nicht syncronisierten CacheState-Wechsels
					  ist nun mittels Einfügen von res->LockStateChange() und res->UnlockStateChange()
					  behoben
--------------------------------------------------------------------------*/ 

void zCResourceManager::CacheOut (zCResource *res) 
{
	zERR_ASSERT (res);

	// Hier gibt es noch ein potentielles Problem: [Nun behoben !!!]
	// Diese Methode laeuft i.d.R. im Thread1/HauptThread und fragt den CacheState von Resourcen ab.
	// Der Thread2/WorkThread koennte aber zur selben Zeit den CacheState der hier betrachteten Resourcen
	// veraendern (von QUEUED=>LOADING=>CACHEDIN). Die CacheState Wechsel sind nicht synkronisiert.
	// Das ist hier aber nicht wirklich schlimm und wuerde wohl nur bei einer hier als QUEUED betrachteten
	// Resource falsche Ergebnisse liefern, die kurz nach GetCacheState() im Thread2 auf LOADING wechselt und 
	// damit hier nicht korrekt reagiert wird: die Resource wird als CACHED_OUT markiert, obwohl sie LOADING/CACHED_IN
	// ist.
	// Loesungsmoeglichkeit: CacheState Wechsel werden mit einer Critical Section belegt; jeder StateChange ist von
	// Lock/Unlock umgeben; diese CacheOut Methode hat ebenfalls teilweise das Lock/Unlock (z.B. nicht bei LOADING..)

	// bereits beim Laden ? => auf das Ende des Ladevorgangs warten und dann entfernen

	res->LockStateChange		(); // Hauptthread locked den Resource-Status[PELZER] 

	if (res->GetCacheState()==zRES_LOADING) 
	{
		WaitForCacheIn			(res);
		// res sollte jetzt 'cachedIn' sein
	};	// hier KEIN else, da der resCacheState sich hier aendern koennte
	zTResourceCacheState resCacheState		= res->GetCacheState();

	// bereits cached out ?
	if (resCacheState==zRES_CACHED_OUT) 
	{
		res->UnlockStateChange		(); // Hauptthread unlocked den Resource-Status[PELZER] 
		return;
	} else
	// queued ? => aus Queue entfernen
	if (resCacheState==zRES_QUEUED) 
	{
		RemoveCacheInQueue		(res);
	} else
	// cachedIn ?
	if (resCacheState==zRES_CACHED_IN) 
	{
		zCClassCache *classCache = GetClassCache (res);
		classCache->RemoveRes	(res);
		res->ReleaseResourceData();
	};

	//
	res->SetCacheState			(zRES_CACHED_OUT);

	res->UnlockStateChange		(); // Hauptthread unlocked den Resource-Status[PELZER] 

	// die Referenz wird wieder freigegeben, wenn die Resource von dem ResMan 
	// cachedIn wurde und das AddRef bekommen hat
	zBOOL wasLastInstance = res->GetRefCtr()==1;
	if (res->managedByResMan)
		res->Release		();
	if (!wasLastInstance)
		res->managedByResMan= FALSE;
};

void zCResourceManager::TouchTimeStamp (zCResource *res)
{
	zERR_ASSERT (res);
	zCClassCache *classCache = GetClassCache (res);
	classCache->TouchRes	(res);
};

void zCResourceManager::DoFrameActivity ()
{
	// 
	if (cacheInImmediatelyMsec>0)
	{
		cacheInImmediatelyMsec -= ztimer.GetFrameTimeF();
		if (cacheInImmediatelyMsec<0) cacheInImmediatelyMsec=0;
	};

	//
	currentTimeStamp		= ztimer.GetTotalTime();

	//
	QueueProcess_Start		();
	Evict					();

	//
	if (this->GetShowDebugInfo())
		PrintStatusDebug	();

	numResCachedInThisFrame	= 0;
};

/*--------------------------------------------------------------------------

    void zCResourceManager::Evict()

    12-Sep-00       [PELZER]
                      Änderung: Nun wird ein CacheOut einer Resource beim überschreiten der maximalen Resource-eigenen
					   Cachegrösse erst dann ausgelöst, wenn zusätzlich die erlaubte Gesamtgrösse des Caches überschritten
					   wird. (Cache-Pool)

    24-Nov-00       [Moos]
                    Seltenen, zufällig erscheinenden Crash mit animierten Texturen gekillt

    27-Nov-00       [Moos]
                    Den vom letzten fix erzeugten freezer beseitigt

--------------------------------------------------------------------------*/ 

void zCResourceManager::Evict()
{
	// Die Caches werden hier gesaeubert

	// Ermittle die erlaubte Gesamtgrösse des Caches und die aktuelle Auslastung [PELZER]
	zDWORD overallBytes		= 0;
	zDWORD overallMaxBytes	= 0;
	for (int i=0; i<classCacheList.GetNum(); i++)
	{
		overallBytes		+= classCacheList[i].cacheSizeBytes;
		overallMaxBytes		+= classCacheList[i].cacheSizeMaxBytes;
	}

	for (i=0; i<classCacheList.GetNum(); i++)
	{
		zCClassCache	*classCache			= &(classCacheList[i]);
		zCResource		*res				= classCache->resListTail;
		zDWORD			cacheOutTimeLimit	= 0;
		if (currentTimeStamp>classCache->cacheOutTimeMSec)
			cacheOutTimeLimit		= currentTimeStamp - classCache->cacheOutTimeMSec;
		while (res)
		{
			zCResource	*nextRes	= res->prevRes;
			// rauswerfen, wenn Resource zu alt..
			if (res->GetTimeStamp()<cacheOutTimeLimit && res->GetCanBeCachedOut()) 
			{
				res->CacheOut		();
                nextRes				= NULL;; // [Moos] 24.11. Fange sicherheitshalber wieder von vorne an 27.11. aber besser erst im nächsten Frame
			} else
			// rauswerfen, wenn der Resource-eigene Cache bereits seine Max-Groesse ueberschritten hat und die erlaubte
			// Gesamtgrösse für den Cache ebenfalls überschritten wurde .. [PELZER]
			if ((classCache->cacheSizeBytes>classCache->cacheSizeMaxBytes) && (overallBytes>overallMaxBytes)) 
			{
				overallBytes		-= res->GetResSizeBytes();
				res->CacheOut		();
                nextRes				= NULL;; // [Moos] 24.11. Fange sicherheitshalber wieder von vorne an 27.11. aber besser erst im nächsten Frame
			} else
			// Abbruch moeglich, sobald die obigen Kriterien nicht mehr zutreffen
				break;
			res = nextRes;
		};
	};
};

/*--------------------------------------------------------------------------

    zCResourceManager::ThreadProc()

    14-Aug-00       [PELZER]
                      Änderung: Das potentielle Problem eines nicht syncronisierten CacheState-Wechsels
					  ist nun mittels Einfügen von resource->LockStateChange() und 
					  ressource->UnlockStateChange() behoben (inkl. goto spd)
--------------------------------------------------------------------------*/ 

zDWORD zCResourceManager::ThreadProc ()
{
	zCResource *resource;
	if (GetThreadingEnabled()) 
		SetThreadPrio( WORKER_THREAD_PRIORITY );
	while (!GetTerminationRequested())
	{
		// Wenn kein Threading aktiv ist, kann die maximale Resource-Load-Anzahl
		// pro Frame beschraenkt werden
		if (!GetThreadingEnabled())
		{
			if (numResCachedInThisFrame>=zNUM_MAX_RES_CACHE_IN_PER_FRAME)
			{
				QueueProcess_Suspend();
				return 0;
			};
		};

		if( goToSuspend ) // Falls der Thread durch PurgeCaches() schlafen geschickt wird [PELZER]
			goto spd;
		resource = GetNextCacheInQueue ();
 		if (resource) 
		{
			resource->LockStateChange(); // Workthread locked den Resource-Status[PELZER] 
			LoadResource	(resource);
			resource->UnlockStateChange(); // Workthread unlocked den Resource-Status[PELZER]
		} else 
spd:	{
			// Thread schlafen legen, bis er mit gefuellter Queue wieder aufgeweckt wird
			QueueProcess_Suspend();
			if (!GetThreadingEnabled()) return 0;
		};
	};
	return 0;
};

zCResource* zCResourceManager::RemoveCacheInQueue (zCResource *res)
{
	// removes first queue element, if resource is not specified explicitly
	LockCacheInQueue();
	if (!res) 
		res = cacheInQueueHead;
	if (res)
	{
		// removes from list
		if (res==cacheInQueueTail) cacheInQueueTail	= res->prevRes;
		if (res==cacheInQueueHead) cacheInQueueHead	= res->nextRes; else
		if (res->prevRes) res->prevRes->nextRes		= res->nextRes;
		if (res->nextRes) res->nextRes->prevRes		= res->prevRes;
		res->nextRes = res->prevRes = 0;
		assert (res->GetCacheState()==zRES_QUEUED);
		numQueued--;
	};
	UnlockCacheInQueue				();

	return res;
};

zCResource* zCResourceManager::GetNextCacheInQueue ()
{
	return RemoveCacheInQueue (0);
};

void zCResourceManager::InsertCacheInQueue (zCResource* res, zREAL priority)
{
	res->SetCacheInPriority (priority);

	//
	LockCacheInQueue();

	// Einfuege Ort in der Queue suchen, am Ende anfangen und bei 
	zCResource *currentRes		= cacheInQueueTail;
	zCResource *currentResNext	= 0;
	while ((currentRes) && (currentRes->GetCacheInPriority()>res->GetCacheInPriority()))
	{
		currentResNext	= currentRes;
		currentRes		= currentRes->prevRes;
	};

	// Fuegt in die Queue ein, currentRes ist dabei der Vorgaenger
	res->prevRes								= currentRes;
	res->nextRes								= currentResNext;
	if (res->nextRes)	res->nextRes->prevRes	= res;
	else				cacheInQueueTail		= res;
	if (currentRes)		currentRes->nextRes		= res;
	else				cacheInQueueHead		= res;

/*	// inserts at tail of list
	res->prevRes					= cacheInQueueTail;
	res->nextRes					= 0;
	if (!cacheInQueueHead)
		cacheInQueueHead			= res;
	if (cacheInQueueTail)
		cacheInQueueTail->nextRes	= res;
	cacheInQueueTail				= res;
*/
	numQueued++;

	res->SetCacheState				(zRES_QUEUED);

	//
	QueueProcess_Resume				();		// muss noch innerhalb der Critical Section sein
	UnlockCacheInQueue				();
};

// ======================================================================================================

// Folgende Methoden kapseln das threading enabled/disabled Feature..

void zCResourceManager::LockCacheInQueue	()
{
	if (GetThreadingEnabled()) 
		cacheInQueueGuard.Lock();
};

void zCResourceManager::UnlockCacheInQueue	()
{
	if (GetThreadingEnabled()) 
		cacheInQueueGuard.Unlock();
};

zBOOL zCResourceManager::WaitForCacheIn (zCResource *res)
{
	// FIXME: wenn queued koennte man hier die Prio der Resource erhoehen, damit nicht so lange darauf gewartet werden braucht
	zERR_ASSERT (res);

	if (GetThreadingEnabled()) {
		while ((res->GetCacheState()==zRES_QUEUED) || (res->GetCacheState()==zRES_LOADING))
		{
			SleepThread( 0 );
		};
	} else {
		while ((res->GetCacheState()==zRES_QUEUED) || (res->GetCacheState()==zRES_LOADING))
		{
			ThreadProc();
		};
	};
	return (res->GetCacheState()==zRES_CACHED_IN);
};

void zCResourceManager::QueueProcess_Start	()
{
	if (GetThreadingEnabled()) {
		if (!IsThreadRunning()) 
		{
			BeginThread();
		};
	} else {
		// Work-Proc direkt aufrufen, falls es etwas zu tun gibt
		if (cacheInQueueHead)
		{
			ThreadProc();
		};
	};
};

void zCResourceManager::QueueProcess_Suspend()
{
	if (GetThreadingEnabled()) {
		SuspendThread	();
	} else {
		// nichts zu tun..
	};
};

void zCResourceManager::QueueProcess_Resume	()
{
	if (GetThreadingEnabled()) {
		if (IsSuspended())
			ResumeThread();
		else if (!IsThreadRunning()) 
			BeginThread();
	} else {
		// hier wird das QueueProcessing direkt aufgerufen, da es nicht ueber einen Thread laeuft
		ThreadProc();
	};
};

// ======================================================================================================

//#include <zSound.h>

void zCResourceManager::PrintStatusDebug ()
{
//	zDWORD	currentTimeStamp= ztimer.GetTotalTime();
	int		YPOS			= 1600;
	if (this->cacheInImmediatelyMsec>0)	screen->Print (0,YPOS, "cacheInImmedMsec: "+zSTRING(this->cacheInImmediatelyMsec,4));
	YPOS += screen->FontY();
	if (!this->GetThreadingEnabled())	screen->Print (0,YPOS, "threading DISABLED");
	YPOS += screen->FontY();
	if (numQueued>0)					screen->Print (0,YPOS, "queued: "+zSTRING(numQueued));
	YPOS += screen->FontY();
	if (numResCachedInThisFrame>0)		screen->Print (0,YPOS, "loaded: "+zSTRING(numResCachedInThisFrame));
	YPOS += screen->FontY();
	
	for (int i=0; i<classCacheList.GetNum(); i++)
	{
		zCClassCache *classCache = &(classCacheList[i]);
		//
		if (classCache->numRes>0)
		{
			//
			int numLocked = 0;
			zCResource *res = classCache->resListHead;
			while (res)
			{
				if (res->GetCacheOutLock()) numLocked++;
				res = res->nextRes;
			};
			screen->Print (0, YPOS,	classCache->resClassDef->GetClassName_()+
									": num: "+zSTRING(classCache->numRes)+
									", kb: "+zSTRING(classCache->cacheSizeBytes/1000)+"/"+zSTRING(classCache->cacheSizeMaxBytes/1000)
									+ ((numLocked>0) ? ", locked: "+zSTRING(numLocked) : "")
									);
		};
		YPOS += screen->FontY();
	};
	{
		LockCacheInQueue();
		zCResource *res = cacheInQueueHead;
		int	YPOS		= 4000;
		while (res)
		{
//			if (dynamic_cast<zCSoundFX*>(res))
			screen->Print (0, YPOS, res->GetClassName_() + ", " + zSTRING(float(res->GetCacheInPriority()) / float(zCResource::zMAX_CACHE_IN_PRIO),2)+", "+res->GetObjectName());
			res = res->nextRes;
			YPOS += 200;
			if (YPOS>=8192) break;
		};
		UnlockCacheInQueue();
	};

	//
	if (zinput->KeyToggled (KEY_8))
	{
		PurgeCaches	();
//		this->SetCacheInImmediately(1000.0F);
	};
};


///////////////////////////////////////////////////////////////////////////
//    zCResourceManager :: zCResClassCache
///////////////////////////////////////////////////////////////////////////

zCResourceManager::zCClassCache::zCClassCache() 
{
	resClassDef			= 0;
	resListHead			= 0;
	resListTail			= 0;
	numRes				= 0;
	cacheSizeBytes		= 0;
	cacheSizeMaxBytes	= 0;
	cacheOutTimeMSec	= 0;
};

zCResourceManager::zCClassCache::~zCClassCache() 
{
};

void zCResourceManager::zCClassCache::InsertRes (zCResource *res) 
{
	// CacheConfigs nachtragen ?
	if (cacheOutTimeMSec<=0)
	{
		res->GetCacheConfig	(cacheOutTimeMSec, *((zDWORD*)&cacheSizeMaxBytes));	// hier caste ich den int ein wenig haesslich auf ein unsigned int
		zERR_ASSERT (cacheOutTimeMSec>0);
		zERR_ASSERT (cacheSizeMaxBytes>0);
//		cacheOutTimeMSec=15000;
	};
	assert (res->prevRes==0);
	assert (res->nextRes==0);
	// inserts at head of list
	res->prevRes			= 0;
	res->nextRes			= resListHead;
	if (!resListTail)
		resListTail			= res;
	if (resListHead)
		resListHead->prevRes= res;
	resListHead				= res;

	// stats
	numRes++;
	cacheSizeBytes			+= res->GetResSizeBytes();
};
		
void zCResourceManager::zCClassCache::RemoveRes (zCResource *res)
{
	// Braucht nicht/kann gar nicht entfernt werden, wenn Resource nicht vom ResMan cachedIn und verwaltet wurde
	if (!res->managedByResMan) return;

	// removes from list
	if (res==resListTail) resListTail	= res->prevRes;
	if (res==resListHead) resListHead	= res->nextRes; else
	if (res->prevRes) res->prevRes->nextRes	= res->nextRes;
	if (res->nextRes) res->nextRes->prevRes	= res->prevRes;
	res->nextRes = res->prevRes = 0;

	// stats
	zERR_ASSERT (numRes>0);
	numRes--;

	cacheSizeBytes			-= res->GetResSizeBytes();

	// safety
	if (cacheSizeBytes<0)	cacheSizeBytes	= 0;
};

void zCResourceManager::zCClassCache::TouchRes (zCResource *res)
{
	// FIXME: evtl. spezielle Liste mit touchRes' merken und nur 1x pro Frame neu sortieren..

	// Wenn Resource einen Vorgaenger hat und dessen Zeitpunkt der letzten Beruehrung juenger ist
	// muss die Resource an den ListenKopf verschoben werden.
	if ((res->prevRes) && (res->prevRes->GetTimeStamp()<res->GetTimeStamp()))
	{
		// spezielle, etwas schnellere Routine, als ueber "RemoveRes (res); InsertRes (res);"..
		if (res!=resListHead) 
		{
			// removes from list
			if (res==resListTail) resListTail		= res->prevRes;
			if (res->prevRes) res->prevRes->nextRes	= res->nextRes;
			if (res->nextRes) res->nextRes->prevRes	= res->prevRes;

			// inserts at head of list
			res->prevRes			= 0;
			res->nextRes			= resListHead;
			if (!resListTail)
				resListTail			= res;
			if (resListHead)
				resListHead->prevRes= res;
			resListHead				= res;
		};
	};
};


// =================================================================================================================

/*

	- Thread1/HauptThread:
		- packe in cacheInQueue
		- hole aus classCacheList (bei PurgeCaches())
		- CacheIn(), CacheOut(), Evict(), PurgeCaches()
	  
	- Thread2/Worker:
		- hole aus cacheInQueue
		- LoadResource()
		- packe in classCacheList
		- LoadResource()
			- Set/GetCacheState(), classCacheList
			- SetCacheState()=> (QUEUED) => LOADING, CACHED_IN

	- geteilte Programm-Resourcen:
		- cacheInQueue				(hat CriticalSection Lock/Unlock)
		- classCacheList			(kein Lock/Unlock aus Performance Gruenden=>TouchRes)
		- der "cacheState" Zustand jeder behandelten Resource 
			(derzeit kein Lock()/Unlock(), koennte noetig werden; wuerde in jede CacheState veraenderen HiLevel zCResourceManager
			 Methode sitzen, also: CacheIn(), LoadResource() und CacheOut(); Vorsicht bei geschachtelten Calls aus demselben Thread)

	- Probs:
		- Default-Texturen erzeugen beim Runterfahren zCTexture Leaks
		- zCThread::ResumeThread()/SuspendThread()/suspendCount erzeugt manchmal Haenger? (beim Runterfahren)

*/
