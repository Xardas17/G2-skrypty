/******************************************************************************** 
 
     $Workfile:: zSky.cpp             $                $Date:: 24.04.01 17:34   $
     $Revision:: 68                   $             $Modtime:: 24.04.01 16:23   $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zSky.cpp $
 * 
 * 68    24.04.01 17:34 Edenfeld
 * Patch 1.08a
 * 
 * 67    19.03.01 21:29 Edenfeld
 * Demo Kastration einfacher/rückgängig gemacht. 
 * 
 * 66    18.03.01 18:49 Edenfeld
 * Demo Geschichten
 * 
 * 65    15.03.01 2:17 Hildebrandt
 * 
 * 63    16.02.01 23:51 Hildebrandt
 * 
 * 62    16.02.01 6:17 Hildebrandt
 * 
 * 61    15.02.01 18:23 Hildebrandt
 * 
 * 60    15.02.01 17:35 Hildebrandt
 * 
 * 59    15.02.01 3:40 Hildebrandt
 * 
 * 58    14.02.01 21:38 Hildebrandt
 * 
 * 57    14.02.01 7:28 Hildebrandt
 * 
 * 56    7.02.01 2:45 Hildebrandt
 * 
 * 55    1.02.01 19:58 Moos
 * 
 * 54    1.02.01 5:10 Hildebrandt
 * 
 * 53    29.01.01 17:51 Hildebrandt
 * 
 * 52    26.01.01 1:37 Hildebrandt
 * 
 * 51    26.01.01 0:44 Hildebrandt
 * 
 * 50    25.01.01 22:44 Hildebrandt
 * 
 * 49    25.01.01 5:08 Hildebrandt
 * 
 * 48    25.01.01 1:36 Hildebrandt
 * 
 * 47    25.01.01 1:21 Hildebrandt
 * 
 * 46    24.01.01 17:42 Hildebrandt
 * 
 * 45    23.01.01 23:14 Hildebrandt
 * 
 * 44    23.01.01 22:49 Hildebrandt
 * 
 * 43    23.01.01 21:00 Hildebrandt
 * 
 * 42    15.01.01 18:34 Hildebrandt
 * 
 * 41    15.01.01 3:55 Hildebrandt
 * 
 * 40    11.01.01 21:09 Hildebrandt
 * 
 * 39    11.01.01 18:46 Hildebrandt
 * 
 * 38    4.12.00 18:23 Moos
 * 
 * 37    23.11.00 12:18 Moos
 * 
 * 36    22.11.00 13:25 Moos
 * 
 * 35    17.11.00 19:29 Moos
 * 
 * 34    4.11.00 0:10 Hildebrandt
 * 
 * 33    3.11.00 16:49 Hildebrandt
 * 
 * 32    1.11.00 20:25 Speckels
 * 
 * 31    26.10.00 18:28 Hildebrandt
 * 
 * 30    25.10.00 15:07 Hildebrandt
 * 
 * 29    5.10.00 20:18 Hildebrandt
 * 
 * 28    21.09.00 22:02 Rueve
 * 
 * 27    21.09.00 3:45 Rueve
 * 
 * 26    11.09.00 10:30 Moos
 * 
 * 25    7.09.00 17:17 Hildebrandt
 * 
 * 24    6.09.00 15:27 Hildebrandt
 * 
 * 23    2.09.00 6:53 Hildebrandt
 * 
 * 22    1.09.00 21:49 Pelzer
 * 
 * 21    1.09.00 20:49 Pelzer
 * 
 * 20    1.09.00 13:39 Pelzer
 * 
 * 19    31.08.00 18:09 Rueve
 * farben
 * 
 * 18    31.08.00 16:35 Hildebrandt
 * 
 * 17    21.08.00 17:18 Hildebrandt
 * 
 * 16    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 17    9.08.00 17:12 Admin
 * 
 * 15    31.07.00 18:05 Rueve
 * Farbe abends (So-Untergang, Bug # 1310)
 * 
 * 14    21.07.00 14:28 Hildebrandt
 * 
 * 13    6.07.00 13:45 Hildebrandt
 * 
 * 8     10.05.00 3:55 Hildebrandt
 * 
 * 7     9.05.00 18:45 Hildebrandt
 * 
 * 6     8.05.00 5:29 Hildebrandt
 * zenGin 089g
 * 
 * 5     8.05.00 2:17 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 12    15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 10    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 8     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 7     16.11.99 19:49 Hildebrandt
 * 
 * 6     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 68 $ ($Modtime: 24.04.01 16:23 $)

/*

- hmm... Sonne 2x rendern ? 1) hinter clouds der Himmelskoerper 2) Corona drueber

http://freespace.virgin.net/hugo.elias/models/m_clouds.htm
http://www.flipcode.com/tutorials/tut_skydomes.shtml

  IDEEN:
  - Outdoor Controler verwaltet/rendert einen Höhen-Nebel (=> Screenshot "cloud_mtn6.jpg"). vielleicht sind es Decals, oder Meshes, oder
    Poly-Planes... Beim Näherkommen faden diese dann weg.
    Evtl. so einen gefakten Boden-Nebel ??
  - outdoor Volume-Fog (shots: Lithtech2, im fx-vz,..)
  - ambient Voegel in groesserer Hoehe => als 3D-Punkte/Decals vom SkyControler verwaltet ! (Lithtech2 shots, Drakan)
    a) einzelne Voegel kreisen am Himmel, b) ein Vogelschwarm / Flocking (Drakan)

 Monster-Engine Preview:
 Bei den Außenleveln konnte man Nebelschaden
 bewundern, die über rund geschwungene Hügel in die Täler flossen.
 Vorbeiziehende Wolken warfen ihren Schatten auf die Landschaft. Der
 Regen war nicht einfach nur auf den Bildschirm geklebt, sondern kam
 dreidimensional von oben.
*/

/*

####
	x Sternschnuppen (PFX)
	x Nebeltag / Fog-Ranges
		- Fog: depth-cue, Höhen-Nebel, Nebel-Zonen
	x Planets verfeinern
		- Mond mit Aura (ADD) versehen
		- Mondphasen
		- ..
	x externes (Ansteuerung, Basisklasse, indoor/outdoor)
	- zufaellige Abfolge (states auswechseln oder innerhalb eines states variieren??)
	- Licht: statisches Licht, Model-Beleuchtung ??

	- SkyBox support 
		x als 1 moeglicher Texture-Layer
		- rot um Y-Achse ?
		- Horizont-Blende
	x Sonne: Blend/Lensflare

########
	- Wolkenschatten: keine Sinus mehr => Bitmap
	- optimieren:
		- nicht jeden Frame (bei kleinen deltas/Tag/Nacht)
		- camMatrix-Handling
 

// *******************************************************************************************************************

// NachtHimmel:		UnrealTournament Level "?"
*/



/*
	- m_numFlyParticle ???
	- trennen: pool und activeList?

	x Bug beim VB packen: Poly-Blitzer
	x Impacts: werden in der Luft erzeugt, falsche Orientierung, selten Korrelation zu konkreten Raindrops, auf/unter Wasser?
	x Raindrops fallen gelegentlich 'etwas' unter den Boden (fuer Sektoren wichtig)
	x Nachzieher bei Bewegung/Beamen der Camera (evtl. Create-Box in Blickrichtung verschieben?)
	- VB packen muehsam
	- RainDrop Triangle Berechnung aufwendig (crossproduct) => lieber 2 Tris nehmen?	(ODER: die crossProds kuerzen/optimieren, Nuller/Einser)
	- Verwaltung der Partikel: slow, Fehleranfaellig?, 
	- lineare Partikel-Abarbeitung vs. skippen von inaktiven Elementen
	- Effekt nur Rendern, wenn aus Sektor heraus auch Outdoor sichtbar ist (den Update allerdings immer)
	- Polygone merken & cachen (TraceRays minimieren), oder einfacher: Pos/Normal direkt  cachen
	- Einfluss aus SoundLautstaerke:
		- weight des Effektes
		- In Sektor oder nicht
		- nach x Sekunden im Sektor ohne Sicht nach aussen: Effekt FadeOut einleiten
 
	- Fehlt:
		- dyn. Ein-/Ausfaden des gesamten Effektes
		- SoundEffekt (in Sektoren leiser)
		- Wolken-Layer einfaden
		- Sun/Flare ausfaden (falls vorhanden)
		- Nebel veraendern: Range naeher (insb. near), Farbe gegen Grau
		- schicke Texturen

		- sonst: Wetter Blitz (Polystrip, additiver Wolkenlayer, Terrain aufhellen, Soundeffekt)
*/



 
#include <zCore.h>
#include <zRenderManager.h>
#include <z3d.h>
#include <zWorld.h>
#include <zSky.h>
#include <zParticle.h>
#include <zView.h>
#include <zLensflare.h>
#include <zMemPool.h>
#include <zVertexTransform.h>
#include <zVertexBuffer.h>
#include <zArchiver.h>
#include <zOption.h>

#pragma warning( disable: 4244 ) 

#ifdef ZENGINE_DEBUG
	#include <zInput_Win32.h>

	#define zSKY_DEBUG
	#define zSKY_DEBUG_KEYS
#endif


zCLASS_DEFINITION_ABSTRACT		(zCSkyControler			, zCObject			, 0	  )
	zCLASS_DEFINITION_ABSTRACT	(zCSkyControler_Mid		, zCSkyControler	, 0   )
		zCLASS_DEFINITION		(zCSkyControler_Indoor	, zCSkyControler_Mid, 0, 0)



zCSkyControler*	zCSkyControler::s_activeSkyControler	= 0;
zBOOL			zCSkyControler::s_skyEffectsEnabled		= TRUE;

static zREAL s_fMaxScreenAlphaScale = -1;


// ===============================================================================================================

zCSkyControler::zCSkyControler() 
{ 
	fillBackground		= TRUE; 
	backgroundColor		= zCOLOR(0,0,0,255); 
	cloudShadowScale	= 0; 
	polyLightCLUTPtr	= 0; 
	backgroundTexture	= 0; 
	lastRelightTime		= 0;
	relightCtr			= 0;
	m_bColorChanged		= FALSE;

#ifndef COMPILING_SPACER
	m_fRelightTime		= 0.000018f;
#else
	m_fRelightTime		= 0;
#endif

	if (s_fMaxScreenAlphaScale == -1)
	{
		s_fMaxScreenAlphaScale = zoptions->ReadReal("ENGINE","zSunMaxScreenBlendScale",0.8f);
		cloudShadowScale       = zoptions->ReadReal("ENGINE","zCloudShadowScale",cloudShadowScale);
	}

	m_enuWeather	= zTWEATHER_RAIN;
};

zCSkyControler::~zCSkyControler()	
{
	zRELEASE(backgroundTexture);
};

void zCSkyControler::ClearBackground(zCOLOR color)
{
	//
	zERR_ASSERT (zCCamera::activeCam);
	zERR_ASSERT (zCCamera::activeCam->targetView);

	//
	int viewXMin, viewYMin;
	int viewXDim, viewYDim;
	zCCamera::activeCam->targetView->GetViewport(viewXMin, viewYMin, viewXDim, viewYDim);
	const zBOOL viewportIsFullscreen			= (viewXDim>=zrenderer->vid_xdim) && (viewYDim>=zrenderer->vid_ydim);
	
	//  GetFillBackground() => zbuffer & pixelbuffer loeschen
	// !GetFillBackground() => nur zbuffer loeschen
	if (viewportIsFullscreen)
	{
		if (GetFillBackground())	zrenderer->Vid_Clear	(color); 
		else						zrenderer->Vid_Clear	(color, zRND_CLEAR_ZBUFFER);
	} else {
		// Der Viewport belegt nur einen Teil des Screens
		const zVEC2						viewMin			= zVEC2(zREAL(viewXMin), zREAL(viewYMin));
		const zVEC2						viewMax			(viewMin[VX] + zREAL(viewXDim), viewMin[VY] + zREAL(viewYDim));
		const zTRnd_ZBufferCmp			zcompare		= zrenderer->GetZBufferCompare	();
		const zTRnd_AlphaBlendSource	oldBlendSource	= zrenderer->GetAlphaBlendSource();
		const zREAL						oldBlendFactor	= zrenderer->GetAlphaBlendFactor();
		const zTRnd_AlphaBlendFunc		oldBlendFunc	= zrenderer->GetAlphaBlendFunc	();
		if (!GetFillBackground()) {
			zrenderer->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND);
			zrenderer->SetAlphaBlendSource  (zRND_ALPHA_SOURCE_CONSTANT);
			zrenderer->SetAlphaBlendFactor  (0);
		}
		zrenderer->SetZBufferCompare	(zRND_ZBUFFER_CMP_ALWAYS);
		if (!backgroundTexture)
			backgroundTexture			= zCTexture::Load(zSTRING("DEFAULT.TGA"));		// FIXME: TMP!
		
		zrenderer->DrawTile				(backgroundTexture, viewMin, viewMax, zCCamera::activeCam->GetFarClipZ(), zVEC2(0), zVEC2(0), zCOLOR(0,0,0,0));

		//
		zrenderer->SetZBufferCompare	(zcompare);
		zrenderer->SetAlphaBlendSource  (oldBlendSource);
		zrenderer->SetAlphaBlendFactor  (oldBlendFactor);
		zrenderer->SetAlphaBlendFunc	(oldBlendFunc);
	};
};

// ===============================================================================================================

zCSkyControler_Mid::zCSkyControler_Mid()
{
	//
	underwaterFX		= FALSE;
	underwaterColor		= zCOLOR (0,50,50,255);  // 0,100,120,255 - letztes ist Alpha, scheint nix zu bewirken
	underwaterFarZ		= zREAL  (3500.0F);			// 3500.0f

	//
	vobUnderwaterPFX	= 0;

	//
	InitScreenBlend		();
};

void zCSkyControler_Mid::InitUnderwaterPFX () 
{
	zCUnderwaterPFX		*underwaterPFX;
	vobUnderwaterPFX	= zNEW(zCVob);
	underwaterPFX		= zNEW(zCUnderwaterPFX);
	vobUnderwaterPFX	->SetCollDet			(FALSE);
	vobUnderwaterPFX	->SetDontWriteIntoArchive(TRUE);
//	vobUnderwaterPFX	->RotateLocalY			(45);
//	vobUnderwaterPFX	->SetPositionWorld		(0,500,-1000); 
	vobUnderwaterPFX	->SetVisual				(underwaterPFX);
	underwaterPFX		->SetLODFarDistance		(zREAL_MAX);
	underwaterPFX		->SetLODNearFadeOutDistance (zREAL_MAX);
	underwaterPFX		->SetDontKillPFXWhenDone(TRUE); 
	underwaterPFX		->SetEmitter			("ZUNDERWATER");
	underwaterPFX		->CreateParticles		();
    zRELEASE(underwaterPFX); // [Moos] das Vob hat nun die Referenz darauf
};

zCSkyControler_Mid::~zCSkyControler_Mid()
{
	//
	zRELEASE	(vobUnderwaterPFX);
	zRELEASE	(scrPolyMesh);
};

void zCSkyControler_Mid::SetUnderwaterFX (const zBOOL b) {
	if (underwaterFX==b)	return;
	underwaterFX	= b;

	assert (zCCamera::activeCam);
	if (!zCCamera::activeCam) return;
	if (b) {
		// Effekt einschalten
		underwaterStartTime = ztimer.GetTotalTimeF();
		zCCamera::activeCam->GetFOV (oldFovX,oldFovY);
		zsound->SetGlobalOcclusion (0.9F);
	} else {
		// Effekt ausschalten
		zCCamera::activeCam->SetFOV (oldFovX,oldFovY);
		zsound->SetGlobalOcclusion (0.0F);
	};
};

zBOOL zCSkyControler_Mid::GetUnderwaterFX () const {
	return underwaterFX;
};

void zCSkyControler_Mid::RenderSkyPre () {

	if (GetUnderwaterFX ()) 
	{
		// FOV-Ani
		zCCamera *cam = zCCamera::activeCam;

		//
		zREAL timeDelta	= ztimer.GetTotalTimeF() - underwaterStartTime;
		zREAL t			= 1.0F - ((timeDelta) / 2000.0F);
		if (t<0) t=0;
		t = zSinusSlowStart(t);

		zREAL amp		= zREAL(5.00F) + t * zREAL(48.0F);
		zREAL speed		= zREAL(1.05F) + t * zREAL(1.0F);

		zREAL fovX		= oldFovX + zSin (speed * (timeDelta * 0.0010F + (M_PI * 1.0))) * (amp);
		zREAL fovY		= oldFovY + zSin (speed * (timeDelta * 0.0006F + (M_PI * 1.5))) * (amp * 0.75F);

		cam->SetFOV		(fovX, fovY);
		cam->Activate	();					// FIXME: ugly, => Die Camera muss FOV abh. internals setzen..
	};
};

void zCSkyControler_Mid::RenderSkyPost (const zBOOL b) {

	//
	if (GetUnderwaterFX ()) {
		//
		if (!vobUnderwaterPFX)
			InitUnderwaterPFX();

		zCUnderwaterPFX	*underwaterPFX = (zCUnderwaterPFX*)(vobUnderwaterPFX->GetVisual());
		{
			zTBBox3D	box;
			zREAL		radius		= underwaterPFX->GetEmitter()->shpCircleSphereRadius;
			zREAL		size		= radius * 1.4142F;
			const zPOINT3&	camPos	= zCCamera::activeCam->GetVob()->GetPositionWorld();
//			box.mins				= camPos - zVEC3(size,size,size);
//			box.maxs				= camPos + zVEC3(size,size,size);
//			vobUnderwaterPFX->SetBBox3DWorld	(box);

			vobUnderwaterPFX->SetPositionWorld	(camPos);

			box.mins = -zVEC3(size,size,size);
			box.maxs =  zVEC3(size,size,size);
			vobUnderwaterPFX->SetBBox3DLocal	(box);
		}

		//
		if (underwaterPFX->GetFirstParticle()==0) {
			underwaterPFX->CreateParticles	();
		};

		//
		zCCamera::activeCam->Activate();
		zTRenderContext renderContext;
		renderContext.Clear		();
		underwaterPFX->Render	(renderContext);
		zrenderer->FlushPolys	();			// vor dem ScreenBlend rendern !
	} else 
	if (vobUnderwaterPFX) {
		zCUnderwaterPFX	*underwaterPFX = (zCUnderwaterPFX*)(vobUnderwaterPFX->GetVisual());
		if (underwaterPFX->GetFirstParticle())
			underwaterPFX->FreeParticles();
	};

	//
	RenderScreenBlend();

#ifdef zSKY_DEBUG_KEYS
	if (zinput->KeyPressed(KEY_LCTRL)) {
		if (zinput->KeyPressed(KEY_DEL))		SetUnderwaterFX(!GetUnderwaterFX());
	};
#endif
};

/* ----------------------------------------------------------------------
	
    zCSkyControler_Mid::InitScreenBlend()	

	16.11.2000	[Moos]	
                Auf neue Vertex-Klasse umgestellt

   ---------------------------------------------------------------------- */

void zCSkyControler_Mid::InitScreenBlend () {
	scrPolyAlpha		= 0;
	scrPolyColor		= zCOLOR(200,200,200,255);
	scrPolyAlphaFunc	= zRND_ALPHA_FUNC_ADD;

	scrPolyMesh			= zCSkyLayer::CreateSkyPoly();
	scrPoly				= scrPolyMesh->SharePoly(0); 

	zCOLOR col;
	col.SetRGBA									(255,255,255, 255);
	scrPolyMesh->SetStaticLight					(col);
	scrPolyMesh->ResetLightDynToLightStat		();
	
	//
	zCVertexTransform  *vert;

	vert					= scrPoly->vertex [0]->GetVertexTransform();
	vert->vertScrX			= 0;
	vert->vertScrY			= 0;
	vert					= scrPoly->vertex[1]->GetVertexTransform();
	vert->vertScrY			= 0;
	vert					= scrPoly->vertex[2]->GetVertexTransform(); // [Moos] damit das initialisiert wird
	vert					= scrPoly->vertex[3]->GetVertexTransform(); 
	vert->vertScrX			= 0; 
	for (int i=0; i<4; i++) {
		scrPoly->vertex [i]->VertexTransform()->vertCamSpaceZInv	= zREAL(1.0F) / 0.0001F;
	};
};

/* ----------------------------------------------------------------------
	
	zCSkyControler_Mid::RenderScreenBlend ()

	16.11.2000	[Moos]	
                Auf neue Vertex-Klassen umgestellt
    
    22.11.2000  [Moos]
                FlushPolys() ganz nach vorne verlegt, weil es
                die VertexTransforms manchmal resetted

   ---------------------------------------------------------------------- */

void zCSkyControler_Mid::RenderScreenBlend () 
{
	// Ein von aussen programmierbarer Screen-Blend (1 Kanal).
	// Bei Bedarf wird diese eine Kanal aber fuer den Unterwasser Screen-Blend benutzt, und
	// der programmierte wird nicht beachtet.

	// die extern programmierten Werte nehmen
	int						alpha		= scrPolyAlpha;
	zCOLOR					color		= scrPolyColor;
	zTRnd_AlphaBlendFunc	alphaFunc	= scrPolyAlphaFunc;

	// Unterwasser ? => Werte überschreiben
	if (underwaterFX) {
		alpha		= 170;
		color		= underwaterColor;
		alphaFunc	= zRND_ALPHA_FUNC_BLEND;
	};

	// vernachlaessigbar ?
	if (alpha<10) return;

	// Werte setzen
	scrPoly->GetMaterial()->SetColor			(color);
	scrPoly->GetMaterial()->SetAlpha			(alpha);
	scrPoly->GetMaterial()->SetAlphaBlendFunc	(alphaFunc);

	// rendern!
	zCCamera          *cam = zCCamera::activeCam;
    zCVertexTransform *vert;

	zrenderer->FlushPolys				();

    vert                = scrPoly->vertex[0]->GetVertexTransform();
	vert->vertScrX		= cam->vpData.xminFloat;
	vert->vertScrY		= cam->vpData.yminFloat;

    vert                = scrPoly->vertex[1]->GetVertexTransform();
	vert->vertScrX		= cam->vpData.xmaxFloat;
	vert->vertScrY		= cam->vpData.yminFloat;

    vert                = scrPoly->vertex[2]->GetVertexTransform();
	vert->vertScrX		= cam->vpData.xmaxFloat;
	vert->vertScrY		= cam->vpData.ymaxFloat;

    vert                = scrPoly->vertex[3]->GetVertexTransform();
	vert->vertScrX		= cam->vpData.xminFloat;
	vert->vertScrY		= cam->vpData.ymaxFloat;

	for (int i=0; i<4; i++) {
		scrPoly->vertex [i]->VertexTransform()->vertCamSpaceZInv	= zREAL(1.0F) / 0.0001F;
	};

	//
	scrPoly->Unclip(); 

	zrenderer->SetPolySortMode			(zRND_SORT_NONE);
	zrenderer->SetZBufferWriteEnabled	(FALSE);
	
	zrenderer->DrawPoly					(scrPoly);
	zrenderer->FlushPolys				();

	zrenderer->SetPolySortMode			(zRND_SORT_ZBUFFER);
	zrenderer->SetZBufferWriteEnabled	(TRUE);
};

void zCSkyControler_Mid::SetScreenBlendAlpha (int s) 
{
	scrPolyAlpha = s * s_fMaxScreenAlphaScale;
};

void zCSkyControler_Mid::SetScreenBlendColor (const zCOLOR& col) 
{
	scrPolyColor = col;
};

void zCSkyControler_Mid::SetScreenBlendAlphaFunc (const zTRnd_AlphaBlendFunc alphaFunc) 
{
	scrPolyAlphaFunc = alphaFunc;
};

// ===============================================================================================================


zCSkyControler_Indoor::zCSkyControler_Indoor() 
{
	userFarZ				= 5000.0F;
	userFarZScalability		= 1;
	time					= 0;
	backgroundColor.SetRGBA (0,0,0,255);
};

void zCSkyControler_Indoor::SetTime (const zREAL _time)	{ 
	this->time=_time; 
	while (time>1) { time -= 1.0F; };
	while (time<0) { time += 1.0F; };

	if (zAbs(lastRelightTime-this->time)>m_fRelightTime)
//	if (lastRelightTime!=masterTime)
	{
		relightCtr++;
		lastRelightTime = time;
	};

};


void zCSkyControler_Indoor::SetFarZ (const zREAL z) {
	userFarZ = z;
};

zREAL zCSkyControler_Indoor::GetFarZ () const { 
	return userFarZ;
};

void zCSkyControler_Indoor::SetFarZScalability (const zREAL zscale)
{
	userFarZScalability	= zscale;
	zClamp (userFarZScalability, zREAL(0), zREAL(4));
};

zREAL zCSkyControler_Indoor::GetFarZScalability () const
{
	return userFarZScalability;
};

void zCSkyControler_Indoor::SetBackgroundColor (const zCOLOR col) {
	backgroundColor = col;
};

zCOLOR zCSkyControler_Indoor::GetBackgroundColor () const {
	return backgroundColor;
};

zCOLOR zCSkyControler_Indoor::GetBackgroundColorDef () const {
	return backgroundColor;
};

void zCSkyControler_Indoor::RenderSkyPre () 
{
	zCSkyControler_Mid::RenderSkyPre	();

	zCOLOR	color	= backgroundColor;
	zREAL	nearz	= userFarZScalability * userFarZ * 0.25F;
	zREAL	farz	= userFarZScalability * userFarZ;

	if (GetUnderwaterFX()) {
		color	= GetUnderwaterColor();
		farz	= GetUnderwaterFarZ();
		nearz	= 0;
	};

	zCCamera::activeCam->SetFarClipZ	(farz);
	zrenderer->SetFogRange				(nearz, farz-500, zRND_FOG_FALLOFF_LINEAR);
	zrenderer->SetFogColor				(color);
	ClearBackground						(color);
};

void zCSkyControler_Indoor::RenderSkyPost (const zBOOL b) {
	zCSkyControler_Mid::RenderSkyPost	(b);
};




// zCUnderwaterPFX
zBOOL zCUnderwaterPFX::Render (zTRenderContext& renderContext) 
{
	ProcessParticles			();
	return zCParticleFX::Render	(renderContext);
};

void zCUnderwaterPFX::ProcessParticles	() 
{
	zTParticle*		p;
	zREAL			radius		= GetEmitter()->shpCircleSphereRadius;
	zREAL			radiusInv	= (radius==0) ? 1 : (zREAL(1.0F) / radius);
	zPOINT3			camPos		= zCCamera::activeCam->GetVob()->GetPositionWorld();
	zVEC3			camMove		= camPos - camPosLastFrame;
	camMove.NormalizeApprox();

	// 'zufällige' Sinus Bewegung der Partikel
	const int		NUM_SIN		= 4;
	const zREAL		time		= (ztimer.GetTotalTimeF() / 7000.0F);
	zVEC3			sinOffs[NUM_SIN];
	zREAL			ifloat		= 0;
	for (int i=0; i<NUM_SIN; i++, ifloat +=1.0F ) 
	{
		const zREAL S		= zREAL(0.1F);
		sinOffs[i].n[VX]	= S * zSin(time + ifloat);
		sinOffs[i].n[VY]	= S * zSin(time + ifloat + 1.0F);
		sinOffs[i].n[VZ]	= S * zSin(time + ifloat + 2.0F);
	};

	for (p = firstPart ; p ; p=p->next) 
	{
		p->position	+= sinOffs[zFloat2Int(p->size[0]) & (NUM_SIN-1)];
		zVEC3 dir	= (p->position - camPos);
		zREAL dist	= dir.LengthApprox();
		p->alpha	= (1.0F - (dist * radiusInv)) * 255.0F;
		if (p->alpha<0) {
			p->alpha = 10;
			
			zREAL moveDist	= zAbs(camMove*dir);
			p->position		+= (1.94F * moveDist) * camMove;

			// hat das Partikel (fehlerhafterweise) die Sphere verlassen ?
			dir		= (p->position - camPos);
			dist	= dir.LengthApprox();
			if (dist>radius)
				p->position = camPos + radius*(dir / dist);
		};
	};

	camPosLastFrame = camPos;
};

void zCUnderwaterPFX::CreateParticles () 
{
	assert (zCCamera::activeCam);
	assert (zCCamera::activeCam->GetVob());

	zCParticleFX::CreateParticles	();
	camPosLastFrame	= zCCamera::activeCam->GetVob()->GetPositionWorld();

	// Partikel 'diversifizieren'
	// => Größe und Texture-Frame
	zTParticle*		p;

	zREAL numTexFrames = 0;
	if (emitter->visTexture)
		numTexFrames = zREAL(emitter->visTexture->GetNumAniFrames(0)-1);

	for (p = firstPart ; p ; p=p->next) 
	{
		p->size			+= (zRandF2() * zREAL(0.5F)) * p->size;
		//p->texAniFrame	= zRandF() * numTexFrames;
	};

};





// *******************************************************************************************************************

#pragma warning( default: 4244 ) 

