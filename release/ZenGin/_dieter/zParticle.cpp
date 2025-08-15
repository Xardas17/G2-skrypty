/******************************************************************************** 
 
     $Workfile:: zParticle.cpp        $                $Date:: 13.02.01 18:59   $
     $Revision:: 44                   $             $Modtime:: 13.02.01 18:57   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:
 
 * $Log: /current_work/ZenGin/_Dieter/zParticle.cpp $
 * 
 * 44    13.02.01 18:59 Moos
 * VertexTransform-Fix für die Wasserringe
 * 
 * 43    13.02.01 1:05 Hildebrandt
 * 
 * 42    1.02.01 19:58 Moos
 * 
 * 41    1.02.01 16:05 Moos
 * 
 * 40    27.01.01 19:42 Moos
 * 
 * 39    25.01.01 5:07 Hildebrandt
 * 
 * 38    17.01.01 2:54 Hildebrandt
 * 
 * 37    8.01.01 17:55 Hildebrandt
 * 
 * 36    4.12.00 18:23 Moos
 * 
 * 35    23.11.00 12:56 Moos
 * 
 * 34    17.11.00 19:29 Moos
 * 
 * 33    15.11.00 2:36 Hildebrandt
 * 
 * 32    8.11.00 18:07 Hildebrandt
 * 
 * 31    31.10.00 13:44 Hildebrandt
 * 
 * 30    26.10.00 2:23 Hildebrandt
 * 
 * 29    25.10.00 17:00 Hildebrandt
 * 
 * 28    11.10.00 21:41 Hildebrandt
 * 
 * 27    11.10.00 19:44 Hildebrandt
 * 
 * 26    6.10.00 19:50 Speckels
 * 
 * 25    4.10.00 17:08 Hildebrandt
 * 
 * 24    22.09.00 19:18 Hildebrandt
 * 
 * 23    22.09.00 15:58 Hoeller
 * 
 * 22    20.09.00 1:47 Rueve
 * 
 * 21    19.09.00 21:33 Hildebrandt
 * 
 * 20    13.09.00 21:24 Hildebrandt
 * 
 * 19    31.08.00 17:04 Hildebrandt
 * 
 * 18    29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 17    23.08.00 17:56 Hildebrandt
 * zengin 0.92i
 * 
 * 16    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 17    9.08.00 17:12 Admin
 * 
 * 15    21.07.00 19:55 Hildebrandt
 * 
 * 14    21.07.00 15:11 Hildebrandt
 * 
 * 13    21.07.00 14:28 Hildebrandt
 * 
 * 12    6.07.00 13:45 Hildebrandt
 * 
 * 7     10.05.00 23:27 Hildebrandt
 * zenGin 089i
 * 
 * 6     8.05.00 18:17 Hildebrandt
 * zenGin 089g
 * 
 * 5     8.05.00 5:29 Hildebrandt
 * zenGin 089g
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 19    22.03.00 21:07 Hildebrandt
 * 
 * 18    22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 17    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 16    22.02.00 2:01 Hildebrandt
 * zenGin 087d
 *  
 * 15    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 13    11.01.00 23:46 Hildebrandt
 * 
 * 12    11.01.00 23:43 Hildebrandt
 * shpMesh bugfix
 * 
 * 11    11.01.00 20:59 Hildebrandt
 * zenGin 085b
 * 
 * 10    10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 8     18.11.99 22:18 Hildebrandt
 * 
 * 7     16.11.99 19:49 Hildebrandt
 * 
 * 6     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 44 $ ($Modtime: 13.02.01 18:57 $)

// ======================================================================================================================

#include <zCore.h>
#include <zParticle.h>
#include <zWorld.h>
#include <z3d.h>
#include <zParser.h>
#include <zPolyStrip.h>
#include <zoption.h>
#include <zView.h>
#include <zMemPool.h>
#include <zVertexTransform.h>
#include <zSky.h>

// ======================================================================================================================

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

#ifdef ZENGINE_DEBUG
	//#define zDEBUG_PFX_DONT_LOAD
#endif

// ======================================================================================================================

zCLASS_DEFINITION (zCParticleFX, zCVisual, 0,0)

enum { zPARTICLE_MAX_GLOBAL = 10000 };

/*

- Optmierung: statt die BBox eines PFX regelmaessig neu zu berechnen, koennte man diese auch anhand der 
  Emitter-Einstellungen vorausberechnen. Diese vorausberechnete BBox waere dann die maximale, die der PFX 
  jemals haben koennte. (- manchmal ueberschaetzt, + keine Updates noetig).

- PolyStrips: Liste preallokierter PolyStrips fuehren => aehnlich wie bei Partikeln, SCHNELLER!

- Idee: "alpha" koennte einfach ein Wert sein, der immer von 0 nach 255 lerpt und dann als index in eine 255-Tabelle
  dient, wo dann das wirklich alpha steht (=> beliebige Kurve, sin, lin, const, ect.)

- Optimierungs-Idee: statt vieler if's oder switch/case Funktions-Ptr Tabelle !
- Partikel koennen nach bestimmter Zeit / wenn sie sterben neue Emitter erzeugen, oder: QuadMarks erzeugen !
- neue	visOrientation: spinning (rotierende Polys, rotSpeed ?)
x neuer visOrientation: "XZ-Plane": fuer Explosions-Ausdehner, Wasser-Effekte
x einfache Kollision Detection/Response fuer Partikel => TraceRay

- neuere, undokumentierte Features:
	x CollDet Modes
	x Polystrips
	x quadMarks

--------------------------------------------

aus: http://www.education.siggraph.org/materials/hypgraph/animation/particle.htm

   1.initial position 
   2.initial velocity (size and direction) 
   3.initial size 
   4.initial color 
   5.initial transparency 
   6.shape 
   7.lifetime 

Particle Generation 

Particles are generated using stochastic methods. Two ways to do this are shown below. In the first method the designer controls the mean number of particles
generated per frame and the variance. So the number of particles generated at frame F is: 
	NpartsF = MeanPartsF + Rand() X VariancePartsF with -1.0 <= Rand() <= 1.0 , a uniformly distributed random number 
A second method generates a certain number of particles per screen area. So MeanParts and VarianceParts refer to a number per unit screen area: 
	NpartsF = (MeanPartsSAF + Rand() X VariancePartsSAF) X ScreenArea 
This method is good for controlling the level of detail required. Note: SAF means per screen area for frame F. 
The designer may want to change the number of particles generated as time changes and can do this by a simple linear function: 
	MeanPartsF = InitialMeanParts + DeltaMeanParts X (F-F0) 
The designer could do this by some function other than linear if needed or desired. So the designer must specify the initial parameters for the above equations and
then everything is automatic. 

A particle system has several parameters that control the initial position of the particles: 
   1.X, Y, Z (the particle system origin) 
   2.Two angles of rotation that give its orientation 
!! 3.A generation shape which defines the region around the origin in which new particles are placed, e.g., a sphere of radius R. These shapes can be simple
     or quite complicated. 

--------

Partikel sollten auch andere als nur lineare Bahnen haben koennen (swirl..)
*/

// FIXME: sollte inne Klasse rein, LAZY
static zREAL uniformValue;
static zREAL uniformDelta;

int								zCParticleFX::s_globNumPart			= 0;
zTParticle*						zCParticleFX::s_globPartList		= 0; 
zTParticle*						zCParticleFX::s_globFreePart		= 0; 
zBOOL							zCParticleFX::s_bAmbientPFXEnabled	= TRUE;
zCMesh*							zCParticleFX::s_partMeshTri			= 0;
zCMesh*							zCParticleFX::s_partMeshQuad		= 0;
zCArraySort<zCParticleEmitter*>	zCParticleFX::s_emitterPresetList	(16);
zCParser*						zCParticleFX::s_pfxParser			= 0;
zCParticleEmitter				zCParticleFX::s_emitterDummyDefault;
zCParticleFX::zCStaticPfxList	zCParticleFX::s_pfxList;
zBOOL							zCParticleFX::s_showDebugInfo		= FALSE;

static int CompareEmitterNames (const void* em1, const void* em2) {
	return ((*(zCParticleEmitter**)em1))->particleFXName.CompareTo(((*(zCParticleEmitter**)em2))->particleFXName);
};

void zCParticleFX::ParseParticleFXScript () {
#ifdef zDEBUG_PFX_DONT_LOAD
	return;
#endif

	if (zoptions->Parm("ZNOPFX"))
		return;

	// [BENDLIN] AddonMOD
	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString(zOPT_SEC_FILES, "ParticleEffects");
	if (filename.IsEmpty())
		filename = "System\\ParticleFx";
	zERR_MESSAGE(3, zERR_BEGIN, "D: PFX: Loading file " + filename + ".src or .dat");

	// FIXME: wann parser loeschen, wann nicht ????

	// Symbole: klassen, klassenVar, instance, protos, funcs, globvars
	if (!s_pfxParser)	s_pfxParser = zNEW(zCParser());
	else				s_pfxParser->Reset();
	const int dscriptClassSize	= int(&(s_emitterDummyDefault.endOfDScriptPart)) - int(&s_emitterDummyDefault);
	s_pfxParser->Parse			(filename + ".src");
	s_pfxParser->CreatePCode	();
	s_pfxParser->CheckClassSize	(zSTRING("C_PARTICLEFX"), dscriptClassSize);
	
	// eine evtl. vorher schon vorhandene Emitter-Preset-List loeschen
	for (int i=0; i<s_emitterPresetList.GetNumInList(); i++)
		delete s_emitterPresetList[i];
	s_emitterPresetList.EmptyList();

	// Alle C_ParticleFX Instanzen aus den Scripten holen & als Presets initialisieren
	zSTRING instanceName;
	int		cindex	= s_pfxParser->GetIndex(zSTRING("C_PARTICLEFX"));
	int		pos		= 0;
	while (pos>=0) {
		pos					= s_pfxParser->GetInstance(cindex,pos+1);
		zCPar_Symbol *sym	= s_pfxParser->GetSymbol(pos);
		if (sym) {
			instanceName	= sym -> name;
			zCParticleEmitter *emitter = zNEW(zCParticleEmitter);
			s_pfxParser->CreateInstance	(instanceName, emitter);
//			emitter->UpdateInternals	();
			emitter->particleFXName		= instanceName;
			s_emitterPresetList.Insert	(emitter);
//			zerr.Message ("D: PFX: "+instanceName);
		};
	};
	s_emitterPresetList.QuickSort();
	// UpdateInternals() darf erst erfolgen, wenn alle Presets da, sind, damit
	// interne Referenzen aufgeloest werden koennen
	for (i=0; i<s_emitterPresetList.GetNumInList(); i++) {
		s_emitterPresetList[i]->UpdateInternals();
	};

	//
//	delete pfxParser;
	zERR_MESSAGE (3, zERR_END, "D: PFX: Num ParticleFX: "+zSTRING(s_emitterPresetList.GetNumInList()));
};

void zCParticleFX::InitParticleFX() 
{
	// globale Partikel-Liste
	if (s_globPartList) delete[] s_globPartList;
	s_globPartList		= zNEW(zTParticle) [zPARTICLE_MAX_GLOBAL];
	s_globNumPart		= zPARTICLE_MAX_GLOBAL;
	for (int i=0; i<s_globNumPart; i++) {	
		s_globPartList[i].next = &s_globPartList[i+1];
	};
	s_globPartList[s_globNumPart-1].next= 0;
	s_globFreePart						= &s_globPartList[0];

	// Particle-Mesh
	if (s_partMeshTri==0) {
		zCOLOR col;
		col.SetRGBA (255,255,255, 255);
		zCMaterial *partMat;

		// Tri-Mesh
		s_partMeshTri	= zCMesh::CreateTriMesh ();
		partMat			= zNEW(zCMaterial("Z_PART_TRI"));
		s_partMeshTri	->SetMaterial				(partMat); 
		s_partMeshTri	->SetStaticLight			(col);
		s_partMeshTri	->ResetLightDynToLightStat	();
		partMat			->SetAlphaBlendFunc			(zRND_ALPHA_FUNC_BLEND);
		partMat			->SetAlpha					(255);
		partMat			->SetColor					(col);
		partMat->Release();		// dieser Kontext braucht das Material nicht mehr

		// Quad-Mesh
		s_partMeshQuad	= zCMesh::CreateQuadMesh	(FALSE);
		partMat			= zNEW(zCMaterial("Z_PART_QUAD"));
		col.SetRGBA		(255,255,255, 255);
		s_partMeshQuad->SetMaterial				(partMat); 
		s_partMeshQuad->SetStaticLight			(col);
		s_partMeshQuad->ResetLightDynToLightStat	();
		partMat			->SetAlphaBlendFunc			(zRND_ALPHA_FUNC_BLEND);
		partMat			->SetAlpha					(255);
		partMat			->SetColor					(col);
		partMat->Release();		// dieser Kontext braucht das Material nicht mehr
	};

	// Preset-List
	s_emitterPresetList.SetCompare (CompareEmitterNames);
	ParseParticleFXScript();
};
 
void zCParticleFX::CleanupParticleFX() {
	zRELEASE (s_partMeshTri);
	zRELEASE (s_partMeshQuad);
	delete[] s_globPartList;	s_globPartList=0;
	delete   s_pfxParser;		s_pfxParser=0;
	for (int i=0; i<s_emitterPresetList.GetNumInList(); i++) {
		delete s_emitterPresetList[i];
	};
};

zCParticleFX::zCParticleFX() {
	firstPart				= 0;
	bbox3DWorld.mins		= zVEC3 (-10,-10,-10);
	bbox3DWorld.maxs		= zVEC3 ( 10, 10, 10);

	connectedVob			= 0;
	dead					= FALSE;
	bboxUpdateCtr			= 0;
	dontKillPFXWhenDone		= FALSE;
	forceEveryFrameUpdate	= FALSE;
	renderUnderWaterOnly	= FALSE;

	emitter					= &s_emitterDummyDefault;
	emitterIsOwned			= FALSE;
	isOneShotFX				= FALSE;

	nextPfx	= prevPfx		= 0;
	privateTotalTime		= 0;
	lastTimeRendered		= 0;

	quadMark				= 0;
	quadMarkBBox3DWorld.InitZero();

	timeScale				= zREAL(1);
	localFrameTimeF			= 0;
	//shpMeshScaleState		= 1;
	InitEmitterVars			();

#ifdef COMPILING_SPACER
	// im Spacer duerfen Objekte niemals geloescht werden, im Game hingegen schon
	SetDontKillPFXWhenDone	(TRUE);
#endif
	// Zusätzliches Flag, das vermeidet das Vobs mit PFX in der Welt jemals gelöscht werden dürfen (Workaround 1.27)
	m_bVisualNeverDies		= FALSE;


	// moeglichst hier *kein* emitter.Reset() => unnuetzer (aber safer) init ...
//	emitter.numTotal= 0;
};


/* ----------------------------------------------------------------------
	
    zCParticleFX::~zCParticleFx()

	23.11.2000	[Moos]	
                emitterIsOwned wird nun verwendet                

   ---------------------------------------------------------------------- */

zCParticleFX::~zCParticleFX() {
	// noch belegte Partikel freigeben..
    RemoveEmitter           ();       // [Moos]
	FreeParticles			();
	zRELEASE				(quadMark);
	emitter					= 0;
	connectedVob			= 0;
	s_pfxList.RemovePfx		(this);
};

// ======================================================================================================================

class zCPFXPerFrameCallback : public zCWorldPerFrameCallback {
public:
	virtual void DoWorldPerFrameCallback (zCWorld *world, zCCamera *camera) 
	{
		zCParticleFX::s_pfxList.ProcessList();
	};
};
static zCPFXPerFrameCallback s_pfxPerFrameCallback;

void zCParticleFX::HostVobAddedToWorld (zCVob* hostVob, zCWorld* hostWorld)
{
	hostWorld->RegisterPerFrameCallback (&s_pfxPerFrameCallback);
};

void zCParticleFX::HostVobRemovedFromWorld (zCVob* hostVob, zCWorld* hostWorld)
{
};

void zCParticleFX::zCStaticPfxList::InsertPfxHead (zCParticleFX *pfx)
{
	zERR_ASSERT (pfx->prevPfx==0);
	zERR_ASSERT (pfx->nextPfx==0);
	// inserts at head of list
	pfx->prevPfx			= 0;
	pfx->nextPfx			= pfxListHead;
	if (!pfxListTail)
		pfxListTail			= pfx;
	if (pfxListHead)
		pfxListHead->prevPfx= pfx;
	pfxListHead				= pfx;

	// stats
	++numInList;
};
		
void zCParticleFX::zCStaticPfxList::RemovePfx (zCParticleFX *pfx)
{
	// gar nicht in Liste eingetragen?
	if (!IsInList(pfx))	return;

	// removes from list
	if (pfx==pfxListTail) pfxListTail		= pfx->prevPfx;
	if (pfx==pfxListHead) pfxListHead		= pfx->nextPfx; else
	if (pfx->prevPfx) pfx->prevPfx->nextPfx	= pfx->nextPfx;
	if (pfx->nextPfx) pfx->nextPfx->prevPfx	= pfx->prevPfx;
	pfx->nextPfx = pfx->prevPfx= 0;

	// stats
	zERR_ASSERT (numInList>0);
	--numInList;
};

void zCParticleFX::zCStaticPfxList::TouchPfx (zCParticleFX *pfx)
{
	// noch gar nicht in Liste?
	if (!IsInList(pfx))
	{
		InsertPfxHead (pfx);
	} else
	{
		// Wenn Resource einen Vorgaenger hat und dessen Zeitpunkt der letzten Beruehrung juenger ist
		// muss die Resource an den ListenKopf verschoben werden.
		//	if ((pfx->prevRes) && (pfx->prevRes->GetTimeStamp()<pfx->GetTimeStamp()))
		{
			// spezielle, etwas schnellere Routine, als ueber "RemoveRes (pfx); InsertRes (pfx);"..
			if (pfx!=pfxListHead) 
			{
				// removes from list
				if (pfx==pfxListTail) pfxListTail		= pfx->prevPfx;
				if (pfx->prevPfx) pfx->prevPfx->nextPfx	= pfx->nextPfx;
				if (pfx->nextPfx) pfx->nextPfx->prevPfx	= pfx->prevPfx;

				// inserts at head of list
				pfx->prevPfx				= 0;
				pfx->nextPfx				= pfxListHead;
				if (!pfxListTail)
					pfxListTail				= pfx;
				if (pfxListHead)
					pfxListHead->prevPfx	= pfx;
				pfxListHead					= pfx;
			};
		};
	};

//	pfx->lastTimeRendered = connectedVob->GetHomeWorld()->GetTotalTimeF();
	pfx->lastTimeRendered = ztimer.GetTotalTimeF();
};

void zCParticleFX::zCStaticPfxList::ProcessList ()
{
	// Pro globalem Zeitschritt darf dieses Updaten von nicht sichtbaren pfx nur 1x passieren.
	// Da allerdings diese Methode pro globalem Zeitschritt von mehreren Welten aufgerufen werden kann,
	// muss man hier faelschliche Mehrfach-Updates verhindern.
	static int lastTimeProcessed=0;
	if (lastTimeProcessed==ztimer.GetTotalTime()) return;
	lastTimeProcessed=ztimer.GetTotalTime();

	// Liste von hinten nach vorne durchlaufen
	int				numFreezing	= 0;
	int				numUpdated	= 0;
	zCParticleFX	*pfx		= pfxListTail;
	while (pfx)
	{
		zCParticleFX *prevPfx = pfx->prevPfx;

		// soll pfx 'plattgemacht' werden?  (wenn er keinen Vob/World hat)
		if ((!pfx->connectedVob) || (!pfx->connectedVob->GetHomeWorld()))
		{
			RemovePfx (pfx);
		} else
		{
			// wurde pfx bereits diesen Frame gerendert? => Abbruch der Listenbearbeitung
			if (pfx->IsAmbientPFX() && !zCParticleFX::S_GetAmbientPFXEnabled())
				goto nextPFX;			// hier war vorher ein break -> logisch falsch

			if (pfx->lastTimeRendered==ztimer.GetTotalTimeF())
				goto nextPFX;			// hier war vorher ein break -> logisch falsch

			// freezt dieser pfx?
			if ((pfx->emitter->ppsIsLooping) && (!pfx->GetForceEveryFrameUpdate()))
			{
				// darf dieser freezende pfx entleert werden?
				// (Zeit ausserhalb ueberschritten, oder zu weit weg..)
				enum { zPFX_MAX_TIME = 10000		};	// nach welcher Zeit geben freezende pfx ihre Partikel frei und werden deaktiv? [msec]
				enum { zPFX_MAX_DIST2= (5000*5000)	};	// ab welcher Raumdistanz zur Kamera wird ein freezender pfx .. ? [square cm]
				zBOOL tooFarAway = FALSE;
				if ((zCCamera::activeCam) && (zCCamera::activeCam->GetVob()))
					tooFarAway = (pfx->connectedVob->GetPositionWorld() - zCCamera::activeCam->GetVob()->GetPositionWorld()).Length2()>zREAL(zPFX_MAX_DIST2);
				float timeDelta	= (ztimer.GetTotalTimeF() - pfx->lastTimeRendered);
				if ((tooFarAway) || (timeDelta>zREAL(zPFX_MAX_TIME)))
				{
					pfx->FreeParticles	();
					RemovePfx			(pfx);
//					zerr.Message		("D: pfx: plattgemacht..");
				};
				++numFreezing;
			} else
			{	
				// pfx udpaten
				zBOOL tooFarAway = FALSE;
				enum { zVFX_MAX_DIST2= (6000*6000)	};

				if (pfx->GetForceEveryFrameUpdate())
				{
					zBOOL tooFarAway = FALSE;
					if ((zCCamera::activeCam) && (zCCamera::activeCam->GetVob()))
						tooFarAway = (pfx->connectedVob->GetPositionWorld() - zCCamera::activeCam->GetVob()->GetPositionWorld()).Length2()>zREAL(zVFX_MAX_DIST2);
				}

				if (!tooFarAway) pfx->UpdateParticleFX();
				else ++numUpdated;
//				zerr.Message			("D: pfx: update..");
			};
		};
nextPFX:
		// naechster pfx
		pfx = prevPfx;
	};

	if (zCParticleFX::GetShowDebugInfo())
	{
		// Zahl freier Partikel zaehlen
		zTParticle *p = zCParticleFX::s_globFreePart;
		int numParticle	= 0;
		while (p)
		{
			++numParticle;
			p = p->next;
		};
		
		screen->Print (0,3000,	"numPFX: "	   +zSTRING(zCParticleFX::GetStaticClassDef()->GetNumLivingObjects()));
		screen->Print (0,3200,	"numRendered: "+zSTRING(numInList-(numUpdated+numFreezing)));
		screen->Print (0,3400,	"numUpdated: " +zSTRING(numUpdated));
		screen->Print (0,3600,	"numFreezing: "+zSTRING(numFreezing));
		screen->Print (0,3800,	"numInactive: "+zSTRING(zCParticleFX::GetStaticClassDef()->GetNumLivingObjects()-numInList));
		screen->Print (0,4000,	"numParticle: "+zSTRING(zPARTICLE_MAX_GLOBAL-numParticle)+" of "+zSTRING(zPARTICLE_MAX_GLOBAL));
	};
};

// ======================================================================================================================


const zSTRING* zCParticleFX::GetFileExtension (int i)
{
	if (i!=0) return 0;
	static const zSTRING ext(".PFX");
	return &ext;
};

zCVisual* zCParticleFX::LoadVisualVirtual (const zSTRING& visualName) const
{
	return zCParticleFX::Load (visualName);		
};

void zCParticleFX::InitEmitterVars () {
	memset (&emitterVars, 0, sizeof(emitterVars));  
};

void zCParticleFX::FreeParticles () {
	zTParticle *kill;
	for ( ;; ) 
	{
		kill = firstPart;
		if (kill)
		{
			//
			if (kill->polyStrip) kill->polyStrip->Release();

			firstPart		= kill->next;
			kill->next		= s_globFreePart;
			s_globFreePart	= kill;
			continue;
		}
		break;
	}
};

void zCParticleFX::SetVisualUsedBy (zCVob* vob) 
{ 
	vob->SetIgnoredByTraceRay (TRUE);
	connectedVob	= vob;
	bbox3DWorld.mins= connectedVob->GetPositionWorld()	- zVEC3 (1,1,1);
	bbox3DWorld.maxs= bbox3DWorld.mins					+ zVEC3 (2,2,2);		
};

zSTRING zCParticleFX::GetVisualName () 
{ 
	if (emitter->particleFXName.Length()>0)	return emitter->particleFXName + ".pfx";
	else									return ""; 
};

zCParticleEmitter* zCParticleFX::SearchParticleEmitter (const zSTRING& emitterName) 
{
	zCParticleEmitter tmpEmitter;

	tmpEmitter.particleFXName = emitterName;
	int index = s_emitterPresetList.Search(&tmpEmitter);
	if (index<=-1)	return 0; 
	else			return s_emitterPresetList[index];
};

void zCParticleFX::RemoveEmitter () 
{
	if (emitterIsOwned) {
		delete emitter;
	};
//	emitter			= 0;
	emitter			= &s_emitterDummyDefault;
	emitterIsOwned	= FALSE;
};

/* ----------------------------------------------------------------------
	
    zCParticleFX::SetEmitter()

	23.11.2000	[Moos]	
                emitterIsOwned wird nun verwendet                

   ---------------------------------------------------------------------- */

zBOOL zCParticleFX::SetEmitter (zCParticleEmitter* em, const zBOOL createCopy) 
{
	if (!em) return FALSE;
	RemoveEmitter();
	if (createCopy)	{
		emitter		= zNEW(zCParticleEmitter(*em));
//		*emitter	= *(em); 
		emitter->AddCompoundReferences();			// zaehlt Referenzen auf zCObjects hoch, sollte eigentlich ein operator= uebernehemn. Allerdings waere eine dessen Implementation zu fehleranfaellig und aufendwig und unperformant.
        emitterIsOwned = TRUE;                      // [Moos] 23.11.
	} else {
		emitter		= em;
        emitterIsOwned = FALSE;                     // [Moos] 23.11.
	};
	InitEmitterVars();
	// AUSNAHME (wird teilw. benutzt, um den NeuAusstoss von Partikel zu blockieren
	isOneShotFX		= !(emitter->ppsIsLooping || (emitter->ppsScaleKeys.GetNum()>0));

	// in die Update-Liste aufnehmen
	s_pfxList.TouchPfx (this);
	return TRUE;
};

zBOOL zCParticleFX::SetEmitter (const zSTRING& emitterName, const zBOOL createCopy) 
{
	// Preset-List dursuchen
	zSTRING name(emitterName);
	name.Delete (".", zSTR_FROM);									// ".pfx" loeschen
	name.Upper	();

	//
	return SetEmitter (SearchParticleEmitter(name), createCopy);
};

zBOOL zCParticleFX::SetAndStartEmitter (const zSTRING& emitterName, const zBOOL createCopy)	
{ 
	zBOOL res = SetEmitter	(emitterName,createCopy); 
	CreateParticles			(); 
	return res;
};

zBOOL zCParticleFX::SetAndStartEmitter (zCParticleEmitter* em, const zBOOL createCopy)
{ 
	zBOOL res = SetEmitter	(em,createCopy);			
	CreateParticles			(); 
	return res;
};

void zCParticleFX::StopEmitterOutput () {
	isOneShotFX = TRUE;
};

void zCParticleFX::RestoreEmitterOutput () {
	isOneShotFX = !(emitter->ppsIsLooping || (emitter->ppsScaleKeys.GetNum()>0));
	InitEmitterVars ();
};

zCParticleFX* zCParticleFX::Load (const zSTRING& partFXName) 
{
	zCParticleFX* partFX= zNEW(zCParticleFX);
	zBOOL success		= partFX->SetAndStartEmitter (partFXName); 
	if (!success)
	{
		zRELEASE (partFX);
	};
	return partFX;
};

/*	------------------------------------------------------------------
	zTBBox3D zCParticleFX::GetBBox3D () 
	 9.11.00	[HILDEBRANDT]	
				Bei der BBox Berechnung wird nun auch die 'Dicke' der einzelnen Partikel beruecksichtigt und 
				die WS-BBox effektiv groesser. Dadurch werden die Frustum-Clip Fehler behoben (Pfx-Polys ausserhalb der BBox).
	------------------------------------------------------------------ */

zTBBox3D zCParticleFX::GetBBox3D () 
{
#if 1
	// FIXME: evtl. die BBox cachen und diese Berechnungen nur bei Aenderung durchfuehren
	zTBBox3D tmpBox = bbox3DWorld;

	// die 'dicke' der einzelnen Partikel beruecksichtigen, das vergroessert effektiv die BBox (konservativ)
	zREAL addSize	= zREAL(0.5F) * (emitter->visSizeStart[VX] + emitter->visSizeStart[VY]) * zMax (1.0F, emitter->visSizeEndScale * zREAL(0.8F));
	tmpBox.mins		-= zVEC3(addSize);
	tmpBox.maxs		+= zVEC3(addSize);

	if (!quadMark)	return tmpBox;

	// ein vorhander QuadMark vergroessert die BBox entsprechend
	tmpBox.CalcGreaterBBox3D (quadMarkBBox3DWorld);
	return tmpBox;
#else
	zTBBox3D boxWS = bbox3DWorld;
	if (quadMark)	boxWS.CalcGreaterBBox3D (quadMarkBBox3DWorld);
	if (this->GetConnectedVob())
	{
		zTBBox3D boxOS;
		boxWS.Transform (this->GetConnectedVob()->trafoObjToWorld.InverseLinTrafo(), boxOS);
		return boxOS;
	} else 
	{
		return boxWS;
	};
#endif
};

zBOOL zCParticleFX::CalcIsDead () {
/*	return  
	   ((firstPart==0) &&
	   ((!emitter->ppsIsLooping) ||
		((emitter->ppsIsLooping) && (zFloat2Int(emitterVars.ppsScaleKeysActFrame)>=emitter->ppsScaleKeys.GetNumInList()))) 
		&&
		((!quadMark) || (quadMark->GetNumActive()<=0))		// entweder kein QuadMark, oder ein leerer QuadMark
		);*/	
//	int ppsActFrame = zFloat2Int(emitterVars.ppsScaleKeysActFrame);	// DEBUG [SPECKELS]
//	int ppsNumKey	= emitter->ppsScaleKeys.GetNumInList();			// DEBUG [SPECKELS]
	if (GetVisualNeverDies()) return FALSE;

	zBOOL result = 
		(	(firstPart==0) &&
			(
				(isOneShotFX) ||
				(!emitter->ppsIsLooping) ||
				// [SPECKELS]
				// Aeh: Dies hier macht das Sinn? 
				// -> Sorgt fuer das Entfernen von loopenden Partikeleffekten
				// wenn sie wieder ins Blickfeld geraten [SPECKELS]
				( (emitter->ppsIsLooping) && (zFloat2Int(emitterVars.ppsScaleKeysActFrame)>=emitter->ppsScaleKeys.GetNumInList()) )
			) &&
			((!quadMark) || (quadMark->GetNumActive()<=0))		// entweder kein QuadMark, oder ein leerer QuadMark
		);
	return result;
};

zVALUE zCParticleFX::PartRand () {
	return zRandF2();
};

void zCParticleFX::UpdateParticleFX () 
{
	// 1) filtert tote Partikel heraus
	// 2) animiert die noch lebenden Partikel
	// 3) erzeugt neue Partikel

	// 1) filtert tote Partikel heraus
//	const zREAL		totalTime	= ztimer.GetTotalTimeF();

	if (GetEmitter()->m_endTime>=25)
	{
		// spezialfall für sonnenwinkel geschichten
		GetEmitter()->UpdateVelocity();
	};


	zTParticle*		p;
	zTParticle*		kill;
	for ( ;; ) {
		kill = firstPart;
		if (kill && (kill->lifeSpan < privateTotalTime)) {
			// Polystrip ?
			if (kill->polyStrip)	kill->polyStrip->Release();

			//
			firstPart		= kill->next;
			kill->next		= s_globFreePart;
			s_globFreePart	= kill;
			continue;
		}
		break;
	}
	for (p = firstPart ; p ; p=p->next) 
	{
		// Partikel tot ?
		for ( ;; ) {
			kill = p->next;
			if (kill && (kill->lifeSpan < privateTotalTime )) {
				// Polystrip ?
				if (kill->polyStrip) kill->polyStrip->Release();

				p->next			= kill->next;
				kill->next		= s_globFreePart;
				s_globFreePart	= kill;
				continue;
			}
			break;
		};
		// 2) animiert die noch lebenden Partikel
		UpdateParticle (p);
	};

	// 3) erzeugt neue Partikel
	CreateParticlesUpdateDependencies();

	//
	if (GetVisualDied()) 
	if (this->GetConnectedVob())
	{
		// Vob wird released und aus Welt entfernt
		// (wird auch deleted, falls keine weiteren Referenzen auf das Objekt bestehen)
		this->GetConnectedVob()->GetHomeWorld()->RemoveVob (this->GetConnectedVob());
		// ACHTUNG: AB HIER KANN 'THIS' NICHT MEHR GUELTIG SEIN.
	};
};

void zCParticleFX::CreateParticlesUpdateDependencies()
{
	// erzeugt ggfs. neue Partikel
	// udpated die BBox
	// setzt das dead-flag

	// Effekt zuende ?
	if (!isOneShotFX)
	{
		CreateParticles();
	};

	// Beendungs-Bedingung
	if (CalcIsDead())
	{ 
		if (!GetDontKillPFXWhenDone()) 
		{
			dead = TRUE;
		}
		else {
			if (quadMark) {
				bbox3DWorld = quadMark->GetBBox3D();
			} else {
				bbox3DWorld.mins = connectedVob->GetPositionWorld() + zVEC3(-1,-1,-1);
				bbox3DWorld.maxs = connectedVob->GetPositionWorld() + zVEC3(+1,+1,+1);
			};
			connectedVob->UpdateVisualDependencies(FALSE); 
		};
	} else 
	{
		// Vob-BBox updaten
		if (connectedVob) {
			if (firstPart==0) {
				if (quadMark) {
					bbox3DWorld = quadMark->GetBBox3D();
				} else {
					bbox3DWorld.mins = connectedVob->GetPositionWorld() + zVEC3(-1,-1,-1);
					bbox3DWorld.maxs = connectedVob->GetPositionWorld() + zVEC3(+1,+1,+1);
				};
				connectedVob->UpdateVisualDependencies(); 
			} else {
				if (emitter->visOrientation==zPFX_EMITTER_VISORIENT_VOB_XZPLANE) {
					// jeden Frame BBox updaten
					connectedVob->UpdateVisualDependencies(FALSE); 
				} else 
				{
					if (bboxUpdateCtr==0) {
						connectedVob->UpdateVisualDependencies(FALSE); 
						bboxUpdateCtr=8;
					} else
						bboxUpdateCtr--;
				};
			};
		};
	};

#if 0
	// hier wird noch die position der pfx-bbox korrigiert, falls nötig
	//if (zDYNAMIC_CAST<zCParticleFX>(this->GetVisual()))
	if (connectedVob)
	{
		zPOINT3 bboxcenter = bbox3DWorld.GetCenter();
		zPOINT3 vobcenter  = connectedVob->GetPositionWorld();
		zVEC3   cd		   = vobcenter-bboxcenter;
		if (cd.Length2()!=0)
		{
			// vob center und bbox center sind irgendwie durcheinandergeraten, wird nun hier korrigiert
			this->bbox3DWorld.Translate(cd);
		};
	};
#endif


	// private Uhr weiterzaehlen
	privateTotalTime += ztimer.GetFrameTimeF();
};

static inline float zSinusEaseSmooth(const float tIn)
{
	if (tIn<0.5f) return zSinusEase(tIn*2);
	else		  return 1-zSinusEase((tIn-0.5f)*2);
}

void zCParticleFX::UpdateParticle (zTParticle *p) 
{
	// ASSERT:
	// - localFrameTimeF gesetzt

	// Parameter-Updates
	// - position
	// - velocity
	// - alpha

	if (emitter->dirFOR==zPFX_FOR_OBJECT_EACH_FRAME) 
	{
		p->vel	= connectedVob->trafoObjToWorld.Rotate (p->vel);
	};

	// einige flocking fx werden auf p->position addiert andere auf p->positionWS
	// pre transform (OS) flocking
	if (emitter->m_flockMode != zPFX_FLOCK_NONE)
	{
		if (zCVob::GetAnimationsEnabled())
		{
			switch (emitter->m_flockMode)
			{
				case zPFX_FLOCK_WIND:
				{
					zVEC3 windVec;
					if (zCSkyControler::GetActiveSkyControler()->GetGlobalWindVec(windVec,zVISUAL_ANIMODE_WIND))
					{
						p->position += (emitter->m_fFlockWeight * windVec);
					}
					break;
				}
				default: break;
			}
		}
	}

	// nur jeden nten Frame einen Collision-Test, dafuer dann aber ab einer frueher (grob geschaetzten) Position
	// FIXME: warum werden trotzdem so viele Coll. nicht erkannt ?
	//        beachte: wenn numPart durch 4 teilbar ist, bekommt nur jeder 4. Partikel CollDet..
	static int collDetToggle = zRand();
	collDetToggle++;

	zBOOL doFlyCollDet= emitter->flyCollDet_B>0;		// FIXME: precalc

	if ((!doFlyCollDet) || ((collDetToggle&4)))
	{
		p->position	+= p->vel		* localFrameTimeF;

		if (!emitter->m_bSlowLocalFOR)	 p->positionWS = p->position;
		else							 
		{
			zMAT4 matObjToWorld		= connectedVob->trafoObjToWorld;
			if (emitter->shpFOR==zPFX_FOR_OBJECT) 
			{
				const zVEC3& offset	= connectedVob->trafoObjToWorld.Rotate (emitter->shpOffsetVec);
				matObjToWorld.Translate (offset);
			}
			p->positionWS = matObjToWorld * p->position;

		}
	} else 
	{
		// Partikel Collision Detection & Response 
		// (wenn CollDet/Resp immer sooo einfach waere..<seufz>)
		// FIXME: evtl. nur alle n Frames machen, dann aber die letzte sicher gueltige Position per Partikel speichern
		// ACHTUNG: eventuellen lokalen PFX ins WS Koordinatensystem transformieren, dann testen (arschlahm)
		// !!! Am langsamsten ist also Coll + Lokal FOR !!!

		if (!emitter->m_bSlowLocalFOR)	 p->positionWS = p->position;
		else							 
		{
			zMAT4 matObjToWorld		= connectedVob->trafoObjToWorld;
			if (emitter->shpFOR==zPFX_FOR_OBJECT) 
			{
				const zVEC3& offset	= connectedVob->trafoObjToWorld.Rotate (emitter->shpOffsetVec);
				matObjToWorld.Translate (offset);
			}
			p->positionWS = matObjToWorld * p->position;

		}

		const zPOINT3& delta		= p->vel * localFrameTimeF;
		const zPOINT3& startPos		= p->positionWS - delta;
		zPOINT3			newPos		= p->position   + delta;
		zCWorld			*homeWorld	= connectedVob->GetHomeWorld();	

		zERR_ASSERT(homeWorld);
		if ((homeWorld->TraceRayFirstHit (startPos, 2*delta, (zCVob*)0, zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE)) &&
			(homeWorld->traceRayReport.foundPoly))
		{
			// Collision Response
			if (emitter->flyCollDet_B==1) {
				// 1 = reflect, damp
				p->vel  = -p->vel;
				p->vel	= zREAL(0.6F) * p->vel.Reflect (connectedVob->GetHomeWorld()->traceRayReport.foundPoly->GetNormal());
			} else
			if (emitter->flyCollDet_B==2) {
				// 2 = reflect, accel
				p->vel  = -p->vel;
				p->vel	= zREAL(1.6F) * p->vel.Reflect (connectedVob->GetHomeWorld()->traceRayReport.foundPoly->GetNormal());
			} else
			if (emitter->flyCollDet_B==3) {
				// 3 = freeze
				p->vel	= 0;
			} else {
				// 4 = remove
				p->lifeSpan = 0;
			};
			
			// QuadMark
			if (emitter->mrkTexture) 
			if (p->vel.LengthApprox()>0.1F)		// nur, wenn part schnell genug
			{
				if (!quadMark) 
				{
					quadMark = zNEW(zCQuadMark);
					quadMark->SetVisualUsedBy				(connectedVob);
					quadMark->SetTexture					(emitter->mrkTexture);
					quadMark->SetAlphaFadeSpeed				(emitter->mrkFadeSpeed);					
					quadMark->SetDontRepositionConnectedVob	(TRUE);
					quadMark->GetDefaultMaterial().SetAlphaBlendFunc(emitter->visAlphaFunc);
					quadMarkBBox3DWorld.Init();
				};
				quadMarkBBox3DWorld.AddPoint (p->positionWS);

				quadMark->CreateQuadMark (homeWorld->traceRayReport.foundPoly, 
										  homeWorld->traceRayReport.foundIntersection, 
										  emitter->mrkSize * (p->alpha*zREAL(0.001953125F) + zREAL(0.5F)));	// scale to [0.5;1.0]
			};
		} else
		{
			p->position	= newPos;

			if (!emitter->m_bSlowLocalFOR)	 p->positionWS = p->position;
			else							 
			{
				zMAT4 matObjToWorld		= connectedVob->trafoObjToWorld;
				if (emitter->shpFOR==zPFX_FOR_OBJECT) 
				{
					const zVEC3& offset	= connectedVob->trafoObjToWorld.Rotate (emitter->shpOffsetVec);
					matObjToWorld.Translate (offset);
				}
				p->positionWS = matObjToWorld * p->position;

			}
		}
	};

	// post transform (WS) flocking
	if (emitter->m_flockMode != zPFX_FLOCK_NONE)
	{
		if (zCVob::GetAnimationsEnabled())
		{
			switch (emitter->m_flockMode)
			{
				case zPFX_FLOCK_WIND_PLANTS:
				{
					zVEC3 windVec;
					if (zCSkyControler::GetActiveSkyControler()->GetGlobalWindVec(windVec,zVISUAL_ANIMODE_WIND))
					{
						float easeIn = (p->positionWS[VY]-GetBBox3D().mins[VY]) * m_BboxYRangeInv;
						easeIn      += 0.2F;
						zClamp01(easeIn);
						p->positionWS += emitter->m_fFlockWeight * zSinusSlowStart( easeIn ) * windVec;
					}
					break;
				}
			}
		}
	}


	//
	p->vel			+= emitter->flyGravity	* localFrameTimeF;
	p->alpha		+= p->alphaVel			* localFrameTimeF; 
	p->size			+= p->sizeVel			* localFrameTimeF;
	p->color		+= p->colorVel			* localFrameTimeF;

	
	// folgende zeilen nicht mehr möglich, materialsortierung bei FlushPolys() verhindert seperate tex-frames pro partikel
	//const zREAL		texAniAdd	= (emitter->visTexAniFPS / 1000.0F) * localFrameTimeF;
	//p->texAniFrame	+= texAniAdd;

	// bbox3D updaten
	if (bboxUpdateCtr==0)
	{
		bbox3DWorld.AddPoint (p->positionWS);
	};

	// Polystrips updaten
	if (p->polyStrip) 
	{
		// Update
		p->polyStrip->SetNewSegmentAlpha	(p->alpha);
		const zREAL		d = (p->alpha * (0.003921568627451F)) * emitter->trlWidth;	// / 255.0
		const zVEC3		dim(d,d,d);
		// if (ztimer.GetFrameTimeF()>0)
		p->polyStrip->AddSegmentSmart		(p->positionWS-dim, p->positionWS+dim);
	};

};


/* ----------------------------------------------------------------------
	
    zCParticleFX::Render()	

	15.11.2000	[Moos]	
                Auf neue Vertexklassen umgestellt


   ---------------------------------------------------------------------- */

static inline zBOOL ShouldRender(const zSParticle *s)
{
	const int is = (int)s;
	const int r  = (is&0xf) + ((is&0xf0)>>4) + ((is&0xf00)>>8) + ((is&0xf000)>>12);
	return ((r&2)==0);
};

zBOOL zCParticleFX::Render (zTRenderContext& renderContext) 
{
	zBOOL visible = TRUE;

	if (this->IsAmbientPFX()			&& !zCParticleFX::S_GetAmbientPFXEnabled())						return FALSE;
	if (this->GetRenderUnderwaterOnly() && !zCSkyControler::GetActiveSkyControler()->GetUnderwaterFX()) return FALSE;

    size_t mark = zCVertexTransform::PoolMark();

	// Mesh rendern
	if (emitter->shpType==zPFX_EMITTER_SHAPE_MESH) 
	{
		if (!emitter->shpMesh && !emitter->shpProgMesh && !emitter->shpModel) return TRUE;

		if (emitter->shpModel) 
		{
			if (!emitter->shpModel->GetHomeVob())		// kein vob mit model verknüpft ? -> benutze vob des pfx
				emitter->shpModel->SetVisualUsedBy(this->connectedVob);

			emitter->shpModel->SetupLowestLOD(renderContext);
		}
		
		// ist es ein progressive mesh ?
		if (emitter->shpMeshRender_B)
		{
			if (emitter->shpProgMesh)
			{
				if (emitter->shpMeshRender_B==2) emitter->shpProgMesh->GetMaterialByIndex(0)->SetAlphaBlendFunc(zRND_ALPHA_FUNC_ADD); else
				if (emitter->shpMeshRender_B==3) emitter->shpProgMesh->GetMaterialByIndex(0)->SetAlphaBlendFunc(zRND_ALPHA_FUNC_MUL); else
				if (emitter->shpMeshRender_B==4) emitter->shpProgMesh->GetMaterialByIndex(0)->SetAlphaBlendFunc(zRND_ALPHA_FUNC_BLEND); 

				emitter->shpProgMesh->Render (renderContext);
				emitter->shpProgMesh->GetMaterialByIndex(0)->SetAlphaBlendFunc(zRND_ALPHA_FUNC_MAT_DEFAULT);
			} 
			else if (emitter->shpMesh && emitter->shpMesh->numPoly>0 && emitter->shpMesh->Poly(0)->GetMaterial() )
			{

				if (emitter->shpMeshRender_B==2)  emitter->shpMesh->Poly(0)->GetMaterial()->SetAlphaBlendFunc(zRND_ALPHA_FUNC_ADD); else
				if (emitter->shpMeshRender_B==3)  emitter->shpMesh->Poly(0)->GetMaterial()->SetAlphaBlendFunc(zRND_ALPHA_FUNC_MUL); else
				if (emitter->shpMeshRender_B==4)  emitter->shpMesh->Poly(0)->GetMaterial()->SetAlphaBlendFunc(zRND_ALPHA_FUNC_BLEND);

				emitter->shpMesh->Render (renderContext);
				emitter->shpMesh->Poly(0)->GetMaterial()->SetAlphaBlendFunc(zRND_ALPHA_FUNC_MAT_DEFAULT);
			}
			else if (emitter->shpModel)
			{
				if (emitter->shpModel->GetNumMaterials()>0)
				{
					if (emitter->shpMeshRender_B==2) emitter->shpModel->GetMaterial(0)->SetAlphaBlendFunc(zRND_ALPHA_FUNC_ADD); else
					if (emitter->shpMeshRender_B==3) emitter->shpModel->GetMaterial(0)->SetAlphaBlendFunc(zRND_ALPHA_FUNC_MUL); else
					if (emitter->shpMeshRender_B==4) emitter->shpModel->GetMaterial(0)->SetAlphaBlendFunc(zRND_ALPHA_FUNC_BLEND); 
				}
	
				emitter->shpModel->Render (renderContext);
				if (emitter->shpModel->GetNumMaterials()>0) 
				{
					emitter->shpModel->GetMaterial(0)->SetAlphaBlendFunc(zRND_ALPHA_FUNC_MAT_DEFAULT);
				}
			}
		}
	};

	// QuadMark rendern
	if (quadMark)	quadMark->Render (renderContext);

	//
	int backup = playerLightInt;
	renderContext.cam->SetCamLightRange (0);

	//
	localFrameTimeF = timeScale * ztimer.GetFrameTimeF();

	// abhaengigen PFX erzeugen ?
	CheckDependentEmitter();

	// wenn keine Partikel zu rendern sind kann ein ganzer Block geskippt werden
	if (firstPart) 
	{
//		const zVEC3&	grav		= emitter->flyGravity * localFrameTimeF;

		if (emitter->m_flockMode == zPFX_FLOCK_WIND_PLANTS)
		{
			m_BboxYRangeInv = 1.0f/zAbs(bbox3DWorld.maxs[VY]-bbox3DWorld.mins[VY]);
		}

		// (noetig, um z.B. Sternschnuppen zu rendern..)
		zBOOL			doFlyCollDet;
		zMAT4			matTrafo;
		if (connectedVob->GetHomeWorld())	{
			doFlyCollDet= emitter->flyCollDet_B>0;
			matTrafo	= zCCamera::activeCam->GetVob()->trafoObjToWorld.InverseLinTrafo();	// WS => WS
		} else {
			doFlyCollDet= FALSE;
			matTrafo	= zCCamera::activeCam->camMatrix;
		};

//		const zREAL		totalTime	= ztimer.GetTotalTimeF();
//		const zREAL		texAniAdd	= (emitter->visTexAniFPS / 1000.0F) * localFrameTimeF;
		zCMesh			*partMesh;
		zCMaterial		*partMat;
		if (emitter->visTexIsQuadPoly)	partMesh	= s_partMeshQuad;
		else							partMesh	= s_partMeshTri;

		if (!emitter->visTexture)	{
			visible = FALSE;
			goto leaveFunc;
		};
		partMat						= partMesh->Poly(0)->GetMaterial(); 
		partMat->texture			= emitter->visTexture;			// muss nach Benutzung wieder auf gesetzt werden (wegen dem Release()..)

		partMat->SetAlphaBlendFunc			(emitter->visAlphaFunc); 
		partMat->texAniCtrl.SetAniFPS		(emitter->visTexAniFPS);
		partMat->texAniCtrl.SetOneShotAni	(!emitter->visTexAniIsLooping);
		partMat->texAniCtrl.SetAniChannel	(0);

		zREAL numTexFrames			= zREAL(emitter->visTexture->GetNumAniFrames(0));

		// Texture-ResCache Precache Strategie:
		if (numTexFrames>0)
		{
			const zTResourceCacheState texCacheStateOld = emitter->visTexture->GetCacheState();
			const zTResourceCacheState texCacheStateNew	= emitter->visTexture->CacheIn(0.2F);
			if (texCacheStateOld==zRES_CACHED_OUT) 
			{
				emitter->visTexture->PrecacheTexAniFrames(0.2F);
				visible = FALSE;
				goto leaveFunc;
			} 
			else if (texCacheStateNew!=zRES_CACHED_IN) 
			{
				visible = FALSE;
				goto leaveFunc;
			};
		}
		else 
		{
			if (emitter->visTexture->CacheIn(0.2F)!=zRES_CACHED_IN) 
			{
				visible = FALSE;
				goto leaveFunc;
			};
		};

		// Set Trafo-Pipeline (fuers Rendern)
		// bbox Init
		if (emitter->visOrientation==zPFX_EMITTER_VISORIENT_VOB_XZPLANE) 
		{
			bbox3DWorld.Init();
			zCCamera::activeCam->Activate();
		} 
		else 
		{
			if (bboxUpdateCtr==0)	bbox3DWorld.Init();
			zCCamera::activeCam->camMatrix.ResetRotation	();
			zCCamera::activeCam->camMatrix.SetTranslation	(0);
			zCCamera::activeCam->camMatrixInv.ResetRotation	();
			zCCamera::activeCam->camMatrixInv.SetTranslation(0);

			zCCamera::activeCam->camMatrixInv.GetTranslation( zCCamera::activeCamPos );
			zCCamera::activeCam->SetUpFrustum				(); 
		};

		zTParticle*		kill;
		zTParticle*		p;

		for ( ;; ) 
		{
			kill = firstPart;
			if (kill && (kill->lifeSpan < privateTotalTime)) 
			{
				// Polystrip ?
				if (kill->polyStrip)	kill->polyStrip->Release();

				//
				firstPart		= kill->next;
				kill->next		= s_globFreePart;
				s_globFreePart	= kill;
				continue;
			}
			break;
		}

		for (p = firstPart ; p ; p=p->next) 
		{
			// Partikel tot ?
			for ( ;; ) 
			{
				kill = p->next;
				if (kill && (kill->lifeSpan < privateTotalTime )) 
				{
					// Polystrip ?
					if (kill->polyStrip) kill->polyStrip->Release();

					p->next			= kill->next;
					kill->next		= s_globFreePart;
					s_globFreePart	= kill;
					continue;
				}
				break;
			}

			if (zrenderer->GetAlphaLimitReached() && (!ShouldRender(p))) 
			{
				UpdateParticle (p);
				continue;		// wird bald das alpha limit erreicht, wird nur jeder partikel an geraden addressen gerendert
			}


			// - 1) Poly Werte setzen
			// - 2) Poly konstruieren
			// - 3) Poly rendern
			// - 4) Zustand updaten (pos, alpha, color, tex)
			// - 5) Neue Partikel erzeugen

			// *****************************
			// 1) Poly Werte setzen
			// *****************************

			// color 
			zCOLOR col (p->color[0], p->color[1], p->color[2], p->alpha);
			partMesh->SetLightDyn (col);

			//if (p->texAniFrame>=numTexFrames) 
			//{
			//	if (emitter->visTexAniIsLooping)	p->texAniFrame -= numTexFrames;
			//	else								p->texAniFrame = numTexFrames-1;
			//};


//			partMat->texAniCtrl.SetActFrame(zFloat2Int(p->texAniFrame));

//			emitter->visTexture->SetActAniFrame		(0, zFloat2Int(p->texAniFrame));

			if (emitter->visTexAniIsLooping != 2)
			{
				partMat->SetAlpha						(p->alpha);
			}
			else
			{
				// smoothe die alpha werte für den spezialfall: ppsIsLooping == 2
				partMat->SetAlpha( zSinusEaseSmooth(zAbs((p->alpha-emitter->visAlphaStart)*emitter->m_ooAlphaDist)) * p->alpha );
			}
			
			partMat->SetColor						(p->color[0], p->color[1], p->color[2]);


			// *****************************
			// 2) Poly konstruieren
			// *****************************

			if (emitter->visOrientation==zPFX_EMITTER_VISORIENT_VOB_XZPLANE) 
			{
				zVEC3 center	= p->positionWS;
				//zVEC3 center	= p->position;
				zVEC3 xoff		= p->size[VX] * connectedVob->trafoObjToWorld.GetRightVector();
				zVEC3 zoff		= p->size[VY] * connectedVob->trafoObjToWorld.GetAtVector();
				partMesh->Vertex (0)->position	= center - xoff + zoff;
				partMesh->Vertex (1)->position	= center + xoff + zoff;
				partMesh->Vertex (2)->position	= center + xoff - zoff;
				partMesh->Vertex (3)->position	= center - xoff - zoff;
				for (int i=0; i<4; i++) {
					partMesh->Vertex (i)->ResetVertexTransform(); 
					// BBox exakt updaten !
					bbox3DWorld.AddPoint (partMesh->Vertex (i)->position);
				};

				//
				zCPolygon *poly = partMesh->Poly(0);

				zBOOL visible = TRUE;
				
				if (renderContext.clipFlags>0) {
					if (!poly->ClipToFrustum(renderContext.clipFlags)) visible = FALSE;
				} else poly->Unclip();

				if (visible) {
					poly->TransformProjectLight();
					zrenderer->DrawPoly (poly);
				};
			}
			else
			{
				// position CamSpace
				const zVEC3& position = matTrafo * (p->positionWS);										// OS => CS
				//const zVEC3& position = matTrafo * (p->position);										// OS => CS

				// FIXME/TODO: hier könnte der Nearclip Wert über ein Menusetting skaliert werden
				if (position[VZ]>35.0F)		// x cm NearClip
				{
					//
					zVALUE xdim = p->size[VX];
					zVALUE ydim = p->size[VY];
					
					if (emitter->visOrientation==zPFX_EMITTER_VISORIENT_VELO_ALIGNED) 
					{
						// FIXME: zVEC2 statt zVEC3
						zVEC3 velYPos			= matTrafo.Rotate(p->vel);
						velYPos.NormalizeApprox();
						const zVEC3& velXPos	= zVEC3(-velYPos[VY], velYPos[VX], velYPos[VZ]);
						const zVEC3& xdimv		= velXPos * xdim;
						const zVEC3& ydimv		= velYPos * ydim;

						// Quad
						partMesh->Vertex (0)->position[VX] = position[VX] - xdimv[VX] + ydimv[VX];
						partMesh->Vertex (0)->position[VY] = position[VY] - xdimv[VY] + ydimv[VY];
						partMesh->Vertex (0)->position[VZ] = position[VZ];

						partMesh->Vertex (1)->position[VX] = position[VX] + xdimv[VX] + ydimv[VX];
						partMesh->Vertex (1)->position[VY] = position[VY] + xdimv[VY] + ydimv[VY];
						partMesh->Vertex (1)->position[VZ] = position[VZ];

						if (emitter->visTexIsQuadPoly) {
							partMesh->Vertex (2)->position[VX] = position[VX] + xdimv[VX] - ydimv[VX];
							partMesh->Vertex (2)->position[VY] = position[VY] + xdimv[VY] - ydimv[VY];
							partMesh->Vertex (2)->position[VZ] = position[VZ];

							partMesh->Vertex (3)->position[VX] = position[VX] - xdimv[VX] - ydimv[VX];
							partMesh->Vertex (3)->position[VY] = position[VY] - xdimv[VY] - ydimv[VY];
							partMesh->Vertex (3)->position[VZ] = position[VZ];
						} else {
							partMesh->Vertex (2)->position[VX] = position[VX] - xdimv[VX] - ydimv[VX];
							partMesh->Vertex (2)->position[VY] = position[VY] - xdimv[VY] - ydimv[VY];
							partMesh->Vertex (2)->position[VZ] = position[VZ];
						};
						zCCamera::activeCamPos = zVEC3(0,0,-position[VZ]);
						partMesh->RenderDecal (renderContext, FALSE);

					} 
					else if (emitter->visOrientation==zPFX_EMITTER_VISORIENT_VELO_ALIGNED3D) 
					{
						// Velo-aligned 'richtig' 3D
						zVEC3 velYPos			= matTrafo.Rotate(p->vel);
						velYPos.NormalizeApprox	();
						zVEC3 stripRight		= zVEC3(-velYPos[VY], velYPos[VX], 0);	// == zVEC3(0,0,1) ^ velYPos;
						stripRight.NormalizeApprox();

						// zlineCache.Line3D (p->position, p->position+p->vel*zREAL(50.0F));
						// Quad
						partMesh->Vertex (0)->position		= position - xdim*stripRight + ydim*velYPos;
						partMesh->Vertex (1)->position		= position + xdim*stripRight + ydim*velYPos;

						if (emitter->visTexIsQuadPoly) 
						{
							partMesh->Vertex (2)->position	= position + xdim*stripRight - ydim*velYPos;

							partMesh->Vertex (3)->position	= position - xdim*stripRight - ydim*velYPos;
						} 
						else 
						{
							partMesh->Vertex (2)->position	= position - xdim*stripRight - ydim*velYPos;
						};
						zCCamera::activeCamPos = zVEC3(0,0,-position[VZ]);
						partMesh->Render (renderContext, 0);
					} 
					else 
					{
						partMesh->Vertex (0)->position[VX] = -xdim + position[VX];
						partMesh->Vertex (0)->position[VY] = +ydim + position[VY];
						partMesh->Vertex (0)->position[VZ] =		   position[VZ];

						partMesh->Vertex (1)->position[VX] = +xdim + position[VX];
						partMesh->Vertex (1)->position[VY] = +ydim + position[VY];
						partMesh->Vertex (1)->position[VZ] =		   position[VZ];

						if (emitter->visTexIsQuadPoly) 
						{
							// Quad
							partMesh->Vertex (2)->position[VX] = +xdim + position[VX];
							partMesh->Vertex (2)->position[VY] = -ydim + position[VY];
							partMesh->Vertex (2)->position[VZ] =		   position[VZ];

							partMesh->Vertex (3)->position[VX] = -xdim + position[VX];
							partMesh->Vertex (3)->position[VY] = -ydim + position[VY];
							partMesh->Vertex (3)->position[VZ] =		   position[VZ];  
						} 
						else 
						{
							// TRI
							partMesh->Vertex (2)->position[VX] = -xdim + position[VX];
							partMesh->Vertex (2)->position[VY] = -ydim + position[VY];
							partMesh->Vertex (2)->position[VZ] =		   position[VZ];  

							xdim *= 0.5F;
							ydim *=-0.5F;
							partMesh->Vertex (0)->position[VX] += xdim;
							partMesh->Vertex (0)->position[VY] += ydim;
							partMesh->Vertex (1)->position[VX] += xdim;
							partMesh->Vertex (1)->position[VY] += ydim;
							partMesh->Vertex (2)->position[VX] += xdim;
							partMesh->Vertex (2)->position[VY] += ydim;
						};
						zCCamera::activeCamPos = zVEC3(0,0,-position[VZ]);
						partMesh->RenderDecal (renderContext, FALSE);
					};
				};
			};

			// *****************************
			// 4) Zustand updaten
			// *****************************

			UpdateParticle (p);
		};

		// Polystrips rendern
	//	if (emitter->trlFadeSpeed>0) 
		p = firstPart;
		if (p)
		if (p->polyStrip) 
		{
			for (; p ; p=p->next) 
			{
				// rendern
				if (!p->polyStrip)	continue;
				p->polyStrip->Render (renderContext);
			};
		};

		// cleanup
		zERR_ASSERT (partMat);
		partMat->texture = 0;
	};

	// *****************************
	// 5) Neue Particle erzeugen
	// *****************************

	//
	CreateParticlesUpdateDependencies();

	// 
	s_pfxList.TouchPfx (this);

leaveFunc:;
	// Cleanup
	renderContext.cam->SetCamLightRange (backup);

    zCVertexTransform::PoolRestore(mark);

	return visible;
};

zREAL zCParticleFX::GetShapeScaleThisFrame ()
{
	/*
		zSTRING					shpScaleKeys;				//	"[1.0] [0.8 0.9 0.2] [1.0]"
		int						shpScaleIsLooping;
		int						shpScaleIsSmooth;
		float					shpScaleFPS;
	*/
	zREAL scale;
	if (emitter->shpScaleFPS>0) 
	{
		const int numFrames = emitter->shpScaleKeys.GetNumInList();
		if (numFrames>0) 
		{
			// neue range bestimmen
			zVALUE	floor		= zFloor		(emitterVars.shpScaleKeysActFrame);
			int		actFrame	= zFloat2Int	(floor);

			// FIXME: Workaround für fehlerhaften Array-Zugriff
			if (emitter->shpScaleKeys.GetNum()<actFrame) return 1;

			scale		= emitter->shpScaleKeys	[actFrame];
			
			if (emitter->shpScaleIsSmooth) 
			{
				zVALUE	frac		= emitterVars.shpScaleKeysActFrame - floor;
				int		nextFrame	= actFrame+1;
				if (nextFrame>=numFrames) nextFrame=0;
				scale = scale + frac * ((emitter->shpScaleKeys [nextFrame])- scale);
			};

			// frame weiterzaehlen
			emitterVars.shpScaleKeysActFrame += (emitter->shpScaleFPS / 1000.0F) * localFrameTimeF;  
			if (zFloor(emitterVars.shpScaleKeysActFrame)>=numFrames) 
			{
				if (emitter->shpScaleIsLooping) 
				{
					emitterVars.shpScaleKeysActFrame -= numFrames;
					while (zFloor(emitterVars.shpScaleKeysActFrame)>=numFrames) 
						emitterVars.shpScaleKeysActFrame -= numFrames;
				} else {
					emitterVars.shpScaleKeysActFrame = numFrames-1;
				};
			};
		} else
			scale = 1.0F;
	} else {
		scale = 1.0F;
	}; 

	return scale;
};

int zCParticleFX::GetNumParticlesThisFrame () { 
	/*
		zSTRING					ppsScaleKeys_S;
		float					ppsValue;
		int						ppsIsLooping;
		int						ppsIsSmooth;
		float					ppsFPS;
	*/
	zREAL ppsResult;
	const int numFrames = emitter->ppsScaleKeys.GetNumInList();
	if ((emitter->ppsFPS>0) && (numFrames>0)) {
		{
			// neue range bestimmen
			zVALUE	floor		= zFloor				(emitterVars.ppsScaleKeysActFrame);
			int		actFrame	= zFloat2Int			(floor);
			zVALUE	scale		= emitter->ppsScaleKeys	[actFrame];
			if (emitter->ppsIsSmooth) {
				zVALUE	frac		= emitterVars.ppsScaleKeysActFrame - floor;
				int		nextFrame	= actFrame+1;
				if (nextFrame>=numFrames) nextFrame=0;
				scale = scale + frac * ((emitter->ppsScaleKeys [nextFrame])- scale);
			};
			ppsResult = scale * emitter->ppsValue;

			// frame weiterzaehlen
			emitterVars.ppsScaleKeysActFrame += (emitter->ppsFPS / 1000)* localFrameTimeF;  
			if (zFloor(emitterVars.ppsScaleKeysActFrame)>=numFrames) {
				if (emitter->ppsIsLooping) {
					emitterVars.ppsScaleKeysActFrame -= numFrames;
					while (zFloor(emitterVars.ppsScaleKeysActFrame)>=numFrames) 
						emitterVars.ppsScaleKeysActFrame -= numFrames;
				} else {
					// loopt nicht => Effekt ist hier zuende (TIMESPAN)
					emitterVars.ppsScaleKeysActFrame = numFrames-1;
					isOneShotFX=TRUE;
				};
			};
		};
	} else {
		// in diesem Fall: kein ist es kein PartPerSec, sondern ParticlesAtOnce & nur dieses eine mal !
		if (isOneShotFX) return emitter->ppsValue;
		ppsResult = emitter->ppsValue;
	};

	// Falls diesen Frame noch nicht mal ein "ganzer" Partikel erzeugt werden soll, wird die Fraction
	// fuer den naechsten Frame gemerkt und dort an dieser Stelle aufaddiert.
	zREAL	numFloat		= ((ppsResult / 1000.0F) * localFrameTimeF) + emitterVars.ppsNumParticlesFraction;
	int		numInt			= zFloat2IntFloor(numFloat);
	emitterVars.ppsNumParticlesFraction = numFloat - zFloor(numFloat); 
	return numInt;
};

void zCParticleFX::CheckDependentEmitter () 
{
	if (emitter->ppsCreateEmitter)  
	if (!emitterVars.ppsDependentEmitterCreated)
	{
		emitterVars.ppsTotalLifeTime += localFrameTimeF;
		if (emitterVars.ppsTotalLifeTime>=emitter->ppsCreateEmDelay) 
		if (connectedVob->GetHomeWorld())
		{
			zCParticleFX	*partFX	= zNEW(zCParticleFX);
			zCVob			*vobFX	= zNEW(zCVob);

			vobFX	->SetCollDet				(FALSE);
			vobFX	->SetPositionWorld			(connectedVob->GetPositionWorld()); 
			vobFX	->SetVisual					(partFX);
			vobFX	->SetDontWriteIntoArchive	(TRUE);
		//	partFX	->SetAndStartEmitter		(emitter->ppsCreateEmitter);
			partFX	->SetEmitter				(emitter->ppsCreateEmitter);
			
			connectedVob->GetHomeWorld()->AddVob(vobFX);
			partFX	->CreateParticles			();

            zRELEASE(partFX);
            zRELEASE(vobFX);

			emitterVars.ppsDependentEmitterCreated = TRUE;
		};	
	};
};

void zCParticleFX::CreateParticles () 
{
	if (!connectedVob)				   return;

	if (emitter->m_endTime!=-1)
	{
		// falls der pfx tageszeitabhängig getriggert werden soll, so wird hier getestet, ob überhaupt
		// partikel ausgestossen werden sollen
		if (connectedVob->GetHomeWorld()) 
		if (connectedVob->GetHomeWorld()->GetActiveSkyControler()) 
		{
			zREAL time	= connectedVob->GetHomeWorld()->GetActiveSkyControler()->GetTime()*24.0F + 12.0F;
			zREAL ta	= emitter->m_startTime;
			zREAL tb	= emitter->m_endTime;
			zREAL diff, frac;

			if (ta>tb) 
			{
				if (time<ta) time += 24.0F;
				tb		+= 24.0F;
			};

			diff	= (tb-ta);				
			if (diff==0) return;
			frac	= (time-emitter->m_startTime) / diff;
			if (!((frac>=0) && (frac<=1)))		return;
		}
	}

	if (connectedVob->GetIsInWater()) return;

	// FIXME: noch buggy: falls der letzte Particle *ausserhalb* des Screens stirbt, wird so nicht die
	//        bbox geupdated..

	localFrameTimeF = timeScale * ztimer.GetFrameTimeF();

	if (localFrameTimeF<=0) return;		// ok ?

	// abhaengigen PFX erzeugen ?
	CheckDependentEmitter();

	int numTotal = GetNumParticlesThisFrame();
	if (numTotal>=2 && zrenderer->GetAlphaLimitReached())
	{
		numTotal*=0.5F;
	}

	if (numTotal<=0) return;

	//
	if (firstPart==0) {
		bboxUpdateCtr	= 0;
		bbox3DWorld.mins= connectedVob->GetPositionWorld()	- zVEC3 (1,1,1);
		bbox3DWorld.maxs= bbox3DWorld.mins					+ zVEC3 (2,2,2);		
	};

	const zREAL shapeScale	= GetShapeScaleThisFrame();

	// ShapeDistribution
	if (emitter->shpDistribType==zPFX_EMITTER_DISTRIBTYPE_RAND) {
	} else 
	if (emitter->shpDistribType==zPFX_EMITTER_DISTRIBTYPE_UNIFORM) {
		emitterVars.uniformValue	= 0;
		emitterVars.uniformDelta	= zREAL(1.0F) / zREAL(numTotal);
		uniformValue	= emitterVars.uniformValue;
		uniformDelta	= emitterVars.uniformDelta;
	} else {
		// WALK
		zREAL delta = emitter->shpDistribWalkSpeed * localFrameTimeF;
		emitterVars.uniformValue	+= delta;
		if (emitterVars.uniformValue>1) emitterVars.uniformValue -= zFloor(emitterVars.uniformValue);
		emitterVars.uniformDelta	= delta / zREAL(numTotal);
		uniformValue	= emitterVars.uniformValue;
		uniformDelta	= emitterVars.uniformDelta;
	};

	zMATRIX4 matObjToWorld;
	if (emitter->shpFOR==zPFX_FOR_OBJECT) 
	{
		const zVEC3& offset	= connectedVob->trafoObjToWorld.Rotate (emitter->shpOffsetVec);
		matObjToWorld		= connectedVob->trafoObjToWorld;
		matObjToWorld.Translate (offset);
	};

	const zBOOL	colorAni	= (emitter->visTexColorRGBAEnd!=emitter->visTexColorRGBAStart); 
	const zBOOL	sizeAni		= (emitter->visSizeEndScale!=1.0F);

	zTParticle	*p;
	for (int i=0 ; i<numTotal; i++)
	{
		if (!s_globFreePart) goto leave;
		p				= s_globFreePart;
		s_globFreePart	= p->next;
		p->next			= firstPart;
		firstPart		= p;

		// - position
		// - velocity (dir, vel)
		// - alpha
		// - size
		// - color 

		// position

		p->position			 = shapeScale * emitter->GetPosition();

		if (!emitter->m_bSlowLocalFOR)
		{
			if (emitter->shpFOR==zPFX_FOR_OBJECT)	p->position = matObjToWorld * p->position;
			else									p->position+= connectedVob->GetPositionWorld() + emitter->shpOffsetVec;
			p->positionWS = p->position;
		}
		else
		{
			if (emitter->shpFOR==zPFX_FOR_OBJECT)	
			{
				p->positionWS = matObjToWorld * p->position;
			}
			else p->positionWS= p->position + connectedVob->GetPositionWorld() + emitter->shpOffsetVec;

		}


		// direction & velocity
		p->vel = emitter->GetVelocity (p, this);

		if (emitter->dirFOR>=zPFX_FOR_OBJECT) {
			p->vel	= connectedVob->trafoObjToWorld.Rotate (p->vel);
		};

		// lifespan
		zREAL timeDelta		= emitter->lspPartAvg + PartRand() * emitter->lspPartVar;
		p->lifeSpan			= privateTotalTime + timeDelta;

		timeDelta			+= 5;
		zREAL timeDeltaInv	= zREAL(1.0F) / timeDelta;
 
		// alpha
		p->alpha			= emitter->visAlphaStart;
		p->alphaVel			= (emitter->visAlphaEnd - emitter->visAlphaStart) * timeDeltaInv;

		// texture ani
		//p->texAniFrame		= 0;

		// size
		p->size				= emitter->visSizeStart;
		if (sizeAni) 
		{
			p->sizeVel[VX]	= (emitter->visSizeStart[VX] * emitter->visSizeEndScale - emitter->visSizeStart[VX]) * timeDeltaInv;
			p->sizeVel[VY]	= (emitter->visSizeStart[VY] * emitter->visSizeEndScale - emitter->visSizeStart[VY]) * timeDeltaInv;
		} else {
			p->sizeVel[VX]	= p->sizeVel[VY] = 0.0F;
		};

		// color
		p->color			= emitter->visTexColorRGBAStart;
		if (colorAni) {
			p->colorVel		= (emitter->visTexColorRGBAEnd - emitter->visTexColorRGBAStart) * timeDeltaInv;
		} else {
			p->colorVel.n[0]= p->colorVel.n[1]= p->colorVel.n[2]= 0.0F;
		};

		// PolyStrip
		p->polyStrip		= 0;
		if (emitter->trlFadeSpeed>0) {
			p->polyStrip						= zNEW(zCPolyStrip);
			p->polyStrip->material->SetTexture	(emitter->trlTexture);
			p->polyStrip->AllocateResources		(32);
			p->polyStrip->SetAlphaFadeSpeed		(emitter->trlFadeSpeed);
			zVEC3 dim(0.577350F,0.577350F,0.577350F);	// (1,1,1).Normalize()
			dim *= emitter->trlWidth;
			p->polyStrip->AddSegment			(p->positionWS-dim, p->positionWS+dim);
		};

		// bbox3D updaten
		// Macht hier nicht viel Sinn, oder ?? => schliesslich starten alle Partikel auf 0,0,0 !
//		bbox3DWorld.AddPoint (p->position);
	}

	bbox3DWorld.AddPoint (p->positionWS);

	// Vob-BBox updaten
//	if (connectedVob) {
//		if (bboxUpdateCtr==0) connectedVob->UpdateVisualDependencies(); 
//	};
leave:;
	connectedVob->UpdateVisualDependencies(FALSE); 
};

// ======================================================================================================================

zCParticleEmitter::zCParticleEmitter() {
	// wirklich ??
	Reset			();
	visTexture		= 0;
	trlTexture		= 0;
	mrkTexture		= 0;
	shpMesh			= 0;
	shpMeshLastPolyNormal	= 0;
	shpProgMesh		= 0;
	shpModel		= 0;
};

zCParticleEmitter::~zCParticleEmitter() { 
	// release meshes, textures, ..
	zRELEASE (visTexture);
	zRELEASE (shpMesh);
	zRELEASE (shpProgMesh);
	zRELEASE (shpModel);
	zRELEASE (trlTexture);
	zRELEASE (mrkTexture);
	shpMeshLastPolyNormal	= 0;
};

void zCParticleEmitter::UpdateVelocity()
{
/*	static zREAL alphaStartDayTime[24] = 
	{
		//0  1    2	   3    4  5  6  7  8  9    10   11
		180, 180, 180, 100, 0, 0, 0, 0, 0, 100, 120, 140, 
		//12 13   14   15   16   17   18  19  20  21   22   23
		160, 180, 160, 140, 120, 100, 80, 85, 90, 100, 180, 180
	};

	static zREAL dirAngleElevDayTime[24] = 
	{
		//0 1   2	3    4  5  6  7  8  9    10   11
		80, 80, 80, 100, 0, 0, 0, 0, 0, 100, 120, 140, 
		//12 13   14   15   16   17   18  19  20  21   22   23
		160, 180, 160, 140, 120, 100, 80, 85, 90, 100, 180, 180
	};

	zREAL time	= connectedVob->GetHomeWorld()->GetActiveSkyControler()->GetTime()*24.0F + 12.0F;
	zREAL ta	= emitter->m_startTime;
	zREAL tb	= emitter->m_endTime;
	zREAL diff, frac;

	if (ta>tb) 
	{
		if (time<ta) time += 24.0F;
		tb		+= 24.0F;
	};

	diff	= (tb-ta);				
	if (diff==0) return;
	frac	= (time-emitter->m_startTime) / diff;
	if (!((frac>=0) && (frac<=1)))		return;




	this->dirAngleElev = blubb;
	this->visAlphaStart= bla;

	
	if (this->visAlphaEnd-this->visAlphaStart != 0) 	m_ooAlphaDist = 1.0f/(this->visAlphaEnd-this->visAlphaStart);
	else												m_ooAlphaDist = 1;*/

};



void zCParticleEmitter::AddCompoundReferences ()
{	
	// adds ref to contained zCObject objects
	if (visTexture)		visTexture->AddRef();
	if (shpMesh)		shpMesh->AddRef();
	if (shpProgMesh)	shpProgMesh->AddRef();
	if (shpModel)		shpModel->AddRef();
	if (trlTexture)		trlTexture->AddRef();
	if (mrkTexture)		mrkTexture->AddRef();
	shpMeshLastPolyNormal		= 0;
};

void zCParticleEmitter::ResetStrings() { 
	ppsScaleKeys_S		.Clear();
	ppsCreateEm_S		.Clear();
	shpType_S			.Clear();		
	shpFOR_S			.Clear();
	shpOffsetVec_S		.Clear();
	shpDistribType_S	.Clear();
	shpDim_S			.Clear();		
	shpMesh_S			.Clear();
	shpScaleKeys_S		.Clear();		 
	dirMode_S			.Clear();				
	dirFOR_S			.Clear();				
	dirModeTargetFOR_S	.Clear();
	dirModeTargetPos_S	.Clear();		
	flyGravity_S		.Clear();
	visName_S			.Clear();				
	visOrientation_S	.Clear();
	visSizeStart_S		.Clear();
	visTexColorStart_S	.Clear();
	visTexColorEnd_S	.Clear();
	visAlphaFunc_S		.Clear();
	trlTexture_S		.Clear();
	mrkTexture_S		.Clear();
	m_flockMode_S		.Clear();
	m_timeStartEnd_S	.Clear();
};

void zCParticleEmitter::Reset() { 
	memset (this, 0, sizeof(*this));  
	ResetStrings();
};

zVEC3 zCParticleEmitter::String2Vec3 (const zSTRING& s) {
	zVEC3 v;
	v[0] = s.PickWord (1, " ", " ").ToFloat();
	v[1] = s.PickWord (2, " ", " ").ToFloat();
	v[2] = s.PickWord (3, " ", " ").ToFloat();
	return v;
};

zVEC2 zCParticleEmitter::String2Vec2 (const zSTRING& s) {
	zVEC2 v;
	v[0] = s.PickWord (1, " ", " ").ToFloat();
	v[1] = s.PickWord (2, " ", " ").ToFloat();
	return v;
};

void zCParticleEmitter::UpdateInternals() { 
	// Strings => C++ Types
	zSTRING s;
	int		i;

	// 1) time
	ppsScaleKeys.EmptyList();
	i=1;
	while (1) {
		s = ppsScaleKeys_S.PickWord (i, " ", " ");
		if (s.Length()<=0) break;
		ppsScaleKeys.Insert (s.ToFloat());
		i++;
	};
	ppsCreateEm_S.Upper();
	ppsCreateEmitter = zCParticleFX::SearchParticleEmitter (ppsCreateEm_S);

	// 2) shape
	shpScaleKeys.EmptyList();
	i=1;
	while (1) 
	{
		s = shpScaleKeys_S.PickWord (i, " ", " ");
		if (s.Length()<=0) break;
		shpScaleKeys.Insert (s.ToFloat());
		i++;
	};
	if ((shpFOR_S[0]=='o') || (shpFOR_S[0]=='O'))	shpFOR	= zPFX_FOR_OBJECT;
	else											shpFOR	= zPFX_FOR_WORLD;
	shpType_S.Upper();
	if (shpType_S.Search("POINT")!=-1)				shpType	= zPFX_EMITTER_SHAPE_POINT;		else
	if (shpType_S.Search("LINE")!=-1)				shpType	= zPFX_EMITTER_SHAPE_LINE;		else
	if (shpType_S.Search("BOX")!=-1)				shpType	= zPFX_EMITTER_SHAPE_BOX;		else
	if (shpType_S.Search("CIRCLE")!=-1)				shpType	= zPFX_EMITTER_SHAPE_CIRCLE;	else
	if (shpType_S.Search("SPHERE")!=-1)				shpType	= zPFX_EMITTER_SHAPE_SPHERE;	else
	if (shpType_S.Search("MESH")!=-1)				shpType	= zPFX_EMITTER_SHAPE_MESH;		else
													shpType	= zPFX_EMITTER_SHAPE_POINT;
	shpCircleSphereRadius	= shpDim_S.ToFloat();
	shpLineBoxDim			= String2Vec3 (shpDim_S);
	zRELEASE (shpMesh);
	zRELEASE (shpProgMesh);
	zRELEASE (shpModel);

	if (shpMesh_S.Length()>0) 
	{
		shpMesh_S.Upper();

		if (shpMesh_S.Search(".3DS")!=-1)
		{
			shpMesh		= zCMesh::Load (shpMesh_S);
		}
		else if (shpMesh_S.Search(".ASC")!=-1)
		{
			shpProgMesh = zDYNAMIC_CAST<zCProgMeshProto>(zCProgMeshProto::Load(shpMesh_S));
		}
		else if (shpMesh_S.Search(".MDS")!=-1)
		{
			shpModel = zDYNAMIC_CAST<zCModel>(zCModel::LoadVisual(shpMesh_S));
			if (shpModel) shpModel->ApplyMeshLib(m_flockMode_S);
		}

		// Datenfehler ? leeres Mesh ?
		if (shpMesh) 
		{
			shpMesh->DynLightScalePrelit (zCOLOR (200,200,200,255));
			
			if ((shpMesh->numPoly==0) || (shpMesh->numVert)==0) 
			{
				zRELEASE (shpMesh);
			};
		} 
		else if (shpProgMesh) 
		{		
			if ( (shpProgMesh->GetNumTri()==0) || (shpProgMesh->GetNumVert()==0) ) 
			{
				zRELEASE (shpProgMesh);
			};
		}
		/*else if (shpModel)			
		{		
			if (shpModel->GetLowestLODNumPolys()==0) 
			{
				zRELEASE (shpModel);
			};
		};*/ // auskommentiert, da die models hier noch nicht die anzahl der polys kennen können (wird OTF in Render() berechnet)


	};

	shpOffsetVec = String2Vec3 (shpOffsetVec_S);
	
	shpDistribType_S.Upper();
	if (shpDistribType_S.Search("RAND")!=-1)		shpDistribType= zPFX_EMITTER_DISTRIBTYPE_RAND;		else
	if (shpDistribType_S.Search("UNI")!=-1)			shpDistribType= zPFX_EMITTER_DISTRIBTYPE_UNIFORM;	else
	if (shpDistribType_S.Search("WALK")!=-1)		shpDistribType= zPFX_EMITTER_DISTRIBTYPE_WALK;		else
													shpDistribType= zPFX_EMITTER_DISTRIBTYPE_RAND;		

	// 3) dir/vel
	if ((dirFOR_S[0]=='o') || (dirFOR_S[0]=='O'))	dirFOR	= zPFX_FOR_OBJECT;
	else if ((dirFOR_S[0]=='f') || (dirFOR_S[0]=='F'))	dirFOR = zPFX_FOR_OBJECT_EACH_FRAME;
	else											dirFOR	= zPFX_FOR_WORLD;
	dirMode_S.Upper();
	if (dirMode_S.Search("DIR")!=-1)				dirMode	= zPFX_EMITTER_DIRMODE_DIR;		else
	if (dirMode_S.Search("TARGET")!=-1)				dirMode	= zPFX_EMITTER_DIRMODE_TARGET;	else
	if ((dirMode_S.Search("MESH")!=-1) && (shpType==zPFX_EMITTER_SHAPE_MESH)) dirMode	= zPFX_EMITTER_DIRMODE_MESH; else
													dirMode	= zPFX_EMITTER_DIRMODE_NONE;

	if ((dirModeTargetFOR_S[0]=='o') || (dirModeTargetFOR_S[0]=='O'))	dirModeTargetFOR= zPFX_FOR_OBJECT;
	else																dirModeTargetFOR= zPFX_FOR_WORLD;
	dirModeTargetPos = String2Vec3 (dirModeTargetPos_S);

	dirAngleHeadVarRad	= Alg_Deg2Rad (dirAngleHeadVar);
	dirAngleElevVarRad	= Alg_Deg2Rad (dirAngleElevVar);
	ConvertAnglesIntoBox();

	// 4) lifespan

	// 5) flight-props
	flyGravity = String2Vec3 (flyGravity_S);

	// 6) visual
	// FIXME: Tex/Mesh Release !!!
	visName_S.Upper(); 
	zRELEASE (visTexture);
	if (visName_S.Search(".TGA")!=-1)	visTexture	= zCTexture::Load (visName_S);		
	else								visTexture	= zCTexture::Load (zCTexture::zTEX_DEFAULT_TEXTURE_FILE);

	visSizeStart		= String2Vec2 (visSizeStart_S);
	visTexColorRGBAStart= String2Vec3 (visTexColorStart_S);
	visTexColorRGBAEnd	= String2Vec3 (visTexColorEnd_S);
	visAlphaFunc_S.Upper();
	visAlphaFunc = zRND_ALPHA_FUNC_NONE;
	visAlphaFunc = zrenderer->AlphaBlendFuncStringToType (visAlphaFunc_S);

	visOrientation_S.Upper();
	if (visOrientation_S.Search("NONE")!=-1)	visOrientation	= zPFX_EMITTER_VISORIENT_NONE;			else
	if (visOrientation_S.Search("VELO3D")!=-1)	visOrientation	= zPFX_EMITTER_VISORIENT_VELO_ALIGNED3D;else
	if (visOrientation_S.Search("VEL")!=-1)		visOrientation	= zPFX_EMITTER_VISORIENT_VELO_ALIGNED;	else
	if (visOrientation_S.Search("VOB")!=-1)		visOrientation	= zPFX_EMITTER_VISORIENT_VOB_XZPLANE;	else
												visOrientation	= zPFX_EMITTER_VISORIENT_NONE;			
	// lazy
	if (visOrientation==zPFX_EMITTER_VISORIENT_VOB_XZPLANE)
		visTexIsQuadPoly=TRUE;

	// 7) misc effects
	// polyStrip
	zRELEASE (trlTexture);
	if (trlFadeSpeed>0) 
	if (trlTexture_S.Length()>1)
		trlTexture	= zCTexture::Load (trlTexture_S);
	// quadMark
	zRELEASE (mrkTexture);
	if (mrkFadeSpeed>0) 
	if (mrkTexture_S.Length()>1)
		mrkTexture	= zCTexture::Load (mrkTexture_S);

	// flocking
	m_flockMode_S.Upper();
	if (m_flockMode_S.Search("NONE")!=-1)		m_flockMode	= zPFX_FLOCK_NONE;
	if (m_flockMode_S.Search("WIND")!=-1)		m_flockMode	= zPFX_FLOCK_WIND;
	if (m_flockMode_S.Search("PLANTS")!=-1)		m_flockMode	= zPFX_FLOCK_WIND_PLANTS;

	// AUSNAHME
	isOneShotFX = !(ppsIsLooping || (ppsScaleKeys.GetNum()>0));

	if (this->visAlphaEnd-this->visAlphaStart != 0) 	m_ooAlphaDist = 1.0f/(this->visAlphaEnd-this->visAlphaStart);
	else												m_ooAlphaDist = 1;

	if (!m_timeStartEnd_S.IsEmpty())
	{
		m_startTime = m_timeStartEnd_S.PickWord(1," ").ToFloat();
		m_endTime   = m_timeStartEnd_S.PickWord(2," ").ToFloat();
	}	

	if ( (m_endTime == 0) && (m_startTime==0) )
	{
		m_endTime	= -1;
		m_startTime = -1;
	}

};

/*--------------------------------------------------------------------------
    zCParticleEmitter::SetOutputDir()

    19-Sep-00       [Michael]
                      zSinCos eingeführt
--------------------------------------------------------------------------*/ 
void zCParticleEmitter::SetOutputDir (const zVEC3& dir) {
	zREAL	head[2], elev[2];
	int		headNum,elevNum;
	zREAL	h,e;
	zREAL	sin_h,sin_e,cos_h,cos_e;
	zVEC3	vec;
	dirAngleBox.mins = dirAngleBox.maxs = dir;

	if (dirAngleHeadVar!=0) {
		head[0]	= Alg_Deg2Rad(dirAngleHead) + dirAngleHeadVarRad;
		head[1]	= Alg_Deg2Rad(dirAngleHead) - dirAngleHeadVarRad;
		headNum	= 2;
	} else {
		if (dirAngleElevVar==0) return;
		head[0]	= Alg_Deg2Rad(dirAngleHead);
		headNum	= 1;
	};
	if (dirAngleElevVar!=0) {
		elev[0]	= Alg_Deg2Rad(dirAngleElev) + dirAngleElevVarRad;
		elev[1]	= Alg_Deg2Rad(dirAngleElev) - dirAngleElevVarRad;
		elevNum	= 2;
	} else {
		elev[0]	= Alg_Deg2Rad(dirAngleElev);
		elevNum	= 1;
	};

	for (int i=0; i<headNum; i++) {
		for (int j=0; j<elevNum; j++) {
			h	= head[i];
			e	= elev[j];
			
			zSinCos(h, sin_h, cos_h);
			zSinCos(e, sin_e, cos_e);
			vec.n[VX] = -sin_h*cos_e;
			vec.n[VY] = sin_e;
			vec.n[VZ] = cos_e*cos_h;

			dirAngleBox.mins[VX] = zMin (dirAngleBox.mins[VX], vec[VX]);
			dirAngleBox.mins[VY] = zMin (dirAngleBox.mins[VY], vec[VY]);
			dirAngleBox.mins[VZ] = zMin (dirAngleBox.mins[VZ], vec[VZ]);
			dirAngleBox.maxs[VX] = zMax (dirAngleBox.maxs[VX], vec[VX]);
			dirAngleBox.maxs[VY] = zMax (dirAngleBox.maxs[VY], vec[VY]);
			dirAngleBox.maxs[VZ] = zMax (dirAngleBox.maxs[VZ], vec[VZ]);
		};
	};
	dirAngleBoxDim = dirAngleBox.maxs - dirAngleBox.mins;
};

/*--------------------------------------------------------------------------
    zCParticleEmitter::ConvertAnglesIntoBox()

    19-Sep-00       [Michael]
                      zSinCos eingeführt
--------------------------------------------------------------------------*/ 
void zCParticleEmitter::ConvertAnglesIntoBox () {
	zREAL   sin_h, sin_e, cos_h, cos_e;
	zSinCos(Alg_Deg2Rad(dirAngleHead), sin_h, cos_h);
	zSinCos(Alg_Deg2Rad(dirAngleElev), sin_e, cos_e);

	SetOutputDir (zVEC3(-sin_h*cos_e, sin_e, cos_e*cos_h));
};

/*--------------------------------------------------------------------------
    zCParticleEmitter::GetPositon()
	output: 
		lokales Koordinatensystem, bis auf zPFX_EMITTER_SHAPE_MESH (-> WS)

    19-Sep-00       [Michael]
                      zSinCos eingeführt
--------------------------------------------------------------------------*/ 
zVEC3 zCParticleEmitter::GetPosition() 
{
	switch (shpType) {
	case zPFX_EMITTER_SHAPE_POINT:
		return zVEC3(0,0,0);
		break;
	case zPFX_EMITTER_SHAPE_LINE: {
//		pos = zVEC3 ( 0, 0, zCParticleFX::PartRand()*shpLineBoxDim[VX]);
		zREAL t;
		if (shpDistribType==zPFX_EMITTER_DISTRIBTYPE_RAND)	{ 
			t = zCParticleFX::PartRand();
		} else {
			t = uniformValue*2 - 1;
			uniformValue += uniformDelta;
		};
//		return zVEC3 ( 0, 0, t*shpLineBoxDim[VX]);
		return zVEC3 ( 0, t*shpLineBoxDim[VX], 0);
		};
		break;
	case zPFX_EMITTER_SHAPE_BOX: {
		zREAL rand1	= zCParticleFX::PartRand();  
		zREAL rand2	= zCParticleFX::PartRand();  
		zREAL rand3	= zCParticleFX::PartRand();  
		return zVEC3 ( rand1*shpLineBoxDim[VX], rand2*shpLineBoxDim[VY], rand3*shpLineBoxDim[VZ]);
		};								 
		break;
	case zPFX_EMITTER_SHAPE_CIRCLE: {  
		zREAL yaw;
		if (shpDistribType==zPFX_EMITTER_DISTRIBTYPE_RAND)	{ 
			yaw = zRandF()		* 2 * M_PI;
		} else {
			yaw = uniformValue	* 2 * M_PI;
			uniformValue += uniformDelta;
		};
//		zVEC3 pos = zVEC3 (	(zREAL)(-zSin(yaw) ),
//							(zREAL)0,
//							(zREAL)(zCos(yaw)));
//		if (shpIsVolume)	pos *= shpCircleSphereRadius * zRandF();
//		else				pos *= shpCircleSphereRadius;
		if (shpIsVolume)	{ 
			const zREAL f = shpCircleSphereRadius * zRandF(); 
			zREAL ysin, ycos;
			zSinCos(yaw, ysin, ycos);

			return zVEC3(-f*ysin, zREAL(0), f*ycos);	
		}
		else				{ 
			const zREAL f = shpCircleSphereRadius	; 
			zREAL ysin, ycos;
			zSinCos(yaw, ysin, ycos);

			return zVEC3(-f*ysin, zREAL(0), f*ycos);	
		};
		};
		break;
	case zPFX_EMITTER_SHAPE_SPHERE: {
		zVEC3 pos = zVEC3 (zCParticleFX::PartRand(), zCParticleFX::PartRand(), zCParticleFX::PartRand());
		pos.NormalizeApprox();
/*		zREAL yaw	= zRandF() * 2 * M_PI;
		zREAL pitch = zRandF() * 2 * M_PI;
		pos = zVEC3 (	(zREAL)(-zSin(yaw) * zCos(pitch)),
						(zREAL)zSin(pitch),
						(zREAL)(zCos(pitch) * zCos(yaw)));*/
		if (shpIsVolume)	pos *= shpCircleSphereRadius * zRandF();
		else				pos *= shpCircleSphereRadius;
		return pos;
		};
		break;
	case zPFX_EMITTER_SHAPE_MESH: 
		if (shpMesh)
		{
			int polyInd		= zRand() % shpMesh->numPoly; 
			zCPolygon *poly = shpMesh->Poly(polyInd);
			int i0			= zRand() % poly->polyNumVert;
			int i1			= i0+1; if (i1>=poly->polyNumVert) i1=0;
			int i2			= i1+1; if (i2>=poly->polyNumVert) i2=0;
			const zVEC3& a	= poly->GetVertexPtr(i0)->position - poly->GetVertexPtr(i1)->position;
			const zVEC3& b	= poly->GetVertexPtr(i2)->position - poly->GetVertexPtr(i1)->position;
			shpMeshLastPolyNormal = (zVEC3*)&poly->GetPlane().normal;
			return	(poly->GetVertexPtr(i1)->position + zRandF()*a + zRandF()*b); 
		} 
		else if (shpProgMesh)
		{
			// hier muss man die aktuellsten transformierten coords des gewünschten progmesh haben
			int polyInd		= zRand() % shpProgMesh->GetLowestLODNumPolys(); 
			int i0			= zRand() % 3;
			int i1			= i0+1; if (i1>=3) i1=0;
			int i2			= i1+1; if (i2>=3) i2=0;
			zVEC3* pVerts   = shpProgMesh->GetLowestLODPoly(polyInd, shpMeshLastPolyNormal);
			const zVEC3& a	= pVerts[i0] - pVerts[i1];
			const zVEC3& b	= pVerts[i2] - pVerts[i1];
			const zVEC3& c	= b-a;
			float  r1		= ::Alg_SqrtApprox(zRandF());		// FIXME: Wurzel nicht immer nötig (sieht aber besser aus)

			return (pVerts[i1] + (r1*a) + (((r1)*zRandF()*c)));
		}
		else if (shpModel)
		{
			int numPolys = shpModel->GetLowestLODNumPolys();
			if (numPolys>0)
			{
				// hier muss man die aktuellsten transformierten coords des gewünschten models haben
				int polyInd		= zRand() % numPolys; 
				int i0			= zRand() % 3;
				int i1			= i0+1; if (i1>=3) i1=0;
				int i2			= i1+1; if (i2>=3) i2=0;
				zVEC3* pVerts   = shpModel->GetLowestLODPoly(polyInd, shpMeshLastPolyNormal);
				const zVEC3& a	= pVerts[i0] - pVerts[i1];
				const zVEC3& b	= pVerts[i2] - pVerts[i1];
				const zVEC3& c	= b-a;
				float  r1		= ::Alg_SqrtApprox(zRandF());

				return (pVerts[i1] + (r1*a) + (((r1)*zRandF()*c)));
			}
		}

		return zVEC3(0,0,0);
		break;
	default:
		return zVEC3(0,0,0);
		break;
	};
};

zVEC3 zCCFASTCALL zCParticleEmitter::GetVelocity (zTParticle* particle, zCParticleFX* partFX) {
	const zVALUE&	rand1	= zCParticleFX::PartRand();
	zVEC3			dir;
	
	switch (dirMode) {
	case zPFX_EMITTER_DIRMODE_DIR: 
		{
		dir[VX]				= dirAngleBox.mins[VX] + zRandF() * dirAngleBoxDim[VX];
		dir[VY]				= dirAngleBox.mins[VY] + zRandF() * dirAngleBoxDim[VY];
		dir[VZ]				= dirAngleBox.mins[VZ] + zRandF() * dirAngleBoxDim[VZ];
 		dir.NormalizeApprox(); 
/*		zREAL yaw	= Alg_Deg2Rad(dirAngleHead);
		zREAL pitch	= Alg_Deg2Rad(dirAngleElev);
		yaw			+= rand8 * Alg_Deg2Rad(dirAngleHeadVar);
		pitch		+= rand9 * Alg_Deg2Rad(dirAngleElevVar);
		dir	= zVEC3 (	(zREAL)(-zSin(yaw) * zCos(pitch)),
						(zREAL)zSin(pitch),
						(zREAL)(zCos(pitch) * zCos(yaw)));
*/		
		};
		break;
	case zPFX_EMITTER_DIRMODE_NONE: 
		dir = zVEC3(zCParticleFX::PartRand(),zCParticleFX::PartRand(),zCParticleFX::PartRand());
		dir.NormalizeApprox();
		break;
	case zPFX_EMITTER_DIRMODE_TARGET: 
		if (dirModeTargetFOR==zPFX_FOR_WORLD) {
			dir = dirModeTargetPos - particle->position;
		} else {
			dir = (partFX->GetConnectedVob()->trafoObjToWorld * dirModeTargetPos) - particle->position;
		};
		dir.NormalizeApprox();
		break;
	case zPFX_EMITTER_DIRMODE_MESH:
		dir = shpMeshLastPolyNormal ? *shpMeshLastPolyNormal : zVEC3(0,0,0);
		break;
	};

	return dir * (velAvg + rand1 * velVar);
};


/*
=============================================================================================

	x particleFX stirbt => auch der Vob muss sterben
	. Groessenaenderung des Effekts/Vobs

  Probs:
	- BBox/Updating/InView: evtl. ParticleFX auch ausserhalb des Frustums updaten ??
	- noch zu lahm: spezielle Poly-Render Pipeline implementieren (2D-clip ?)

=============================================================================================

	Weitere Idee:
	- als Partikel-Visuals:
		- Tri/Texture
		- Quad/Texture (evtl. ani)
		- Mesh
	- Verwendungszwecke:
		- Wasserfontaene (Heretic2-Shot)
		- Explos/Steam-Pipes (Messiah)
	- Partikel-Luft-Reibung ?
	- Rotations-Bewegungen (swirl)
	- Size-Animation (Rocket-Trail-Smoke wird transparenter & groesser, auch: alienVSPredator Shot..)
	- texAniFPS in Abhaengigkeit des lifeSpans setzen.. (aehnlich dem Alpha)

=============================================================================================

	Emitter-Params:
	x emit
		- once #pieces
		- # per frame (avg), optional: maximum-pieces
		- puffs
	x emitt position (evtl.)	[VAR]
	x emitt dir					[VAR] 
	x lifespan					[VAR]
	x Gravity-Const
	- vis:
		- startColor / EndColor	[VAR]
		- alphaAni (evtl. start/end), in Sync mit lifeSpan
		- texture
			- tri/quad ?
			- texAni
				- texture-fps	[VAR]
				- oneShotAni?	=> wenn ja, dann stirbt Partikel bei Ani-Ende
				- => jedes Partikel braucht eigenen TexAniCtrl
		- Mesh ????? (inkl. SelfRot)

 x- animate:
	x size  (Shogo Rauch)
	x color (Messiah Flames)
=============================================================================================

  - Weitere Ideen:
	- versch. Gravity bei Partikeln
	- air-Friction
	- force-field, wind, swirl
	- vary 'emitsPerFrame' in a cycle over time => puffing smoke effect
	- fuer jeden Partikel-Ani Parameter mehr als 2 Keyframes (start, end)
	- Neues Partikel-System erzeugen, wenn Partikel stirbt
	- Partikel prallen von imaginaerem Boundary-Volumen ab (box, sphere,..)
	- Partikel bewegen sich auf Kreis/Kugel Bahn (Heretic2)

=============================================================================================

  - erzeugen
  - Parameter animieren
  - rendern

- 1) zeitliches  Austoss-Verhalten (zPARTICLEFX_EMIT_)
	- ONCE 
		- ppsScaleAni	= "";
		- ppsValue		= 40;
		- ppsIsLooping	= 0;
		- ppsIsSmooth	= 0;
		- ppsFps		= 0;
	- NONSTOP 
		- ppsAniScale	= "";
		- ppsValue		= 40;
		- ppsIsLooping	= 1;
		- ppsIsSmooth	= 0;
		- ppsFps		= 0;
	- TIMESPAN
		- ppsAniScale	= "1.0";
		- ppsValue		= 40;
		- ppsIsLooping	= 0;
		- ppsIsSmooth	= 0;
		- ppsFps		= 0;
	- PUFFS
		- PPSAniScale	= "1.0 0 0 0 1.0 1.0 0 0 0";
		- ppsValue		= 40;
		- ppsIsLooping	= 1;
		- ppsIsSmooth	= 0;
		- ppsFps		= 1;
	- bPPSLooping = 0;	=> Partikel-Effekt loescht sich am Ende selbst 

- 2) raeumliches Austoss-Verhalten
	- locMedium				"point, line, box, circle, sphere, mesh"
	? locDistribution		"UNIFORM, RAND"		(UNIFORM= exakt gleichm.)
	- locVolume				(0=boundary, 1=volume)
	- locMedSphereRad
	- locMedLineBoxDim		"10 20 30"	line: nur 1 Dimension !=0
	- locMedMeshName		"cross.3ds"
	- locFOR				"object,world"
	- locMedScaleAni		"[1.0] [0.8 0.9 0.2] [1.0]"
	- locMedScaleIsLooping
	- locMedScaleIsSmooth
	- locMedScaleFPS

	- Ort der Partikel-Generierung: (dyn. skalierbar, Rand oder Volumen)
		- Frame-of-Reference (FOR): wählbar OS/WS
		- Medien (gleichmaessige Verteilung):
			- Kreis		Radius
			- Kugel		Radius
			- Box		(schnell)
			- Punkt		(schnell)
			- Mesh		(Oberflaeche)	FOR
		- animierte Skalierung wie beim Licht? 3D

- 3) Partikel-Richtung/Speed:
	- dirFOR				"OBJECT, WORLD"
	- dirAngleHead
	- dirAngleHeadVar
	- dirAngleElev
	- dirAngleElevVar
	- dirMode				"DIR, TARGET, MESH_POLY"
	- dirModeTargetFOR
	- dirModeTargetPos		"30 23 67"
		- zVEC3 dirModeTargetPos
	- velMin, velMax
	? velScaleAni			"[1.0] [0.8 0.9 0.2] [1.0]"
	? velScaleIsLooping
	? velScaleIsSmooth
	? velScaleFPS

	- Richtungs-Angabe: wählbar object/world-Space
	  (Umrechnung von Winkel nach Box Ort/Varianz)
		- Dir/Varianz Schema
			- Richtung		: 2 Winkel
			- RichtungVar	: 2 Varianz-Winkel
		- Zielort fuer alle gleich				
		  (Ort in OS/WS wählbar, meist OS 0..,mit Winkel-Varianz?, lifeTime-Kopplung?)
		- Emit from Mesh-Poly
	- Geschwindigkeit:
		- Speed			: cm/msec
		- SpeedVar		: ???

- 4) Lebensdauer (Partikel)
	- lspParticleMin, lspParticleMax

- 5) Partikel Flugverhalten (gravity, nicht-linear?, mesh-selfRot?,..)
	? flyMode				"LINEAR, .."		??
	- flyGravity
	- flyMeshSelfRotSpeedMin, flyMeshSelfRotSpeedMax

- 6) Visualisierung
	- Typ
		- visName			"NAME_V0_A0.TGA/.3DS"	(Variation, Animation)
		- Mesh				(variiert/animiert, ueber Namen, "NAME_V0_A0.3DS")
		- Texture			(variiert/animiert, ueber Namen, "NAME_V0_A0.TGA")
			- visTexQuadPoly				0=triMesh, 1=quadMesh
			- visTexAniFPS
			- visTexAniLooping				0=oneShot, 1=looping
			- size-ani	(nur Tex, lifeSpan-Sync)
				- visTexSizeStart (XY), visTexSizeEnd (XY)
			- color		(nur Tex, lifeSpan-Sync)			
				- visTexColorStart, visTexSizeEnd
	- dyn. Verhalten (alle Visualisierungen)
		- alpha	(lifeSpan-Sync)
			- visAlphaFunc
			- visAlphaStart, visAlphaEnd

=============================================================================================
*/

/*
=============================================================================================

  x MDS: StartPFX, StopPFX (keine Parts mehr generieren; self-delete, wenn letztes Part weg)
  x PartikelFX-Methode: Freeze, slowMotion
  - Schnittstelle, mit der andere ProgrammTeile manuell Partikel *generieren* koennen
  - Distanz-LOD

  - bbox-Problem/UpdateVisDpen (local/world)
  - ..
  zCModel::AttachVobToNode (zCVob* vob, zCModelNodeInst* mnode)
   - wie erfaehrt das Model, dass das Vob (z.B. autom) geloescht wurde ?

=============================================================================================
  Carsten:
  - Alpha-Optimierungen (Renderer-Hints)
	- partikel
	- level-wasser
	- vobs/decals
	- lensflares
	- coronas
  - chroma-color
  - transp: tex merken

=============================================================================================

  TODO / IDEEN:
  *************
  - spezieller visOrientation-Mode: "2-sided Poly in XZ Plane"
	=> sich ausdehnende Ringe (shogo-explo, tr3/heretic2 Wasser Ringe)
  - shpMesh: a) nur onEdges, b) Gewichtung je nach Poly-Flaeche
  - visuals: mesh als visual, versch. Alternativen
  - Texture fuer das Emitter-Zentrum, dass bei numNewParticles=0 alpha-fadet

  dmgColl
  dmgAmount
  dmgType

  damageColl	none;box;point
  damage
  damageType	edge;fire

=====================================

// Symbole: klassen, klassenVar, instance, protos, funcs, globvars

zCParser *parser = new zCParser();
parser->Parse("particle.src");
//	parser->Parse("particle.dat");
zCParticleEmitter emitter;
parser->CreateInstance	("Script_Instanz-Name", &emitter);
parser->EditInstance	("Script_Instanz-Name", &emitter, [changed-Func]);
parser->Reset();

*/


// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 



/*
Partikelsystem:
================
-2- |KR-0132|	Erweiterung: Es gibt bereits die Möglichkeit, für einen Partikeleffekt mehrere Textures zu importieren (name_a0.tga bis name_an.tga). Diese werden dann als Animationsframes interpretiert. Es gibt aber noch ein weiteres Anwendungsgebiet, wofür sich diese Nomenklatur hervorragend eignen würde: Verschiedene Texturen für die einzelnen Partikel. Umsetzung: Man benennt die Texturen wie oben beschrieben und setzt im Partikelsystem ein Flag (z.B. "MultipleFrameFunc") anstatt auf "ANI" auf "VARIANT", und schon werden alle Partikel per Zufall mit einer der verfürbaren Texturen tapeziert.
Anwendungsbeispiel: Zerstörungs-PFX

-3- |KR-0123|	Erweiterung: Partikelrotation in 2 Variationen. 
1. Rotation während des Fluges ("Drehen" der Partikel, z.B. 	Rauchschwaden, Magieeffekte) um X Grad/MSec.
2. Einmalige "Ausrichtung" der Teilchen an der Flugbahn. 	Anwendungsbeispiel: Bei konzentrischen Wellen im Wasser müssen die Texturen so gedreht werden, daß die Welle auch optisch vom Emmiter wegzeigt.
	
LOD: -4- |KR-0125|	Erweiterung: Ein weiteres Flag für Partikeleffekte könnte eine "Priorität" sein. Wenn die Framerate sinkt,
 könnte die Engine z.B. automatisch auf die "Funken" im Feuer verzichten, wodurch wieder viele Kollisionsabfragen und 
 Blendings wegfallen...
  => Auto-"Prioritaet" emitteln, params: numPart, size, volume,..
*/
