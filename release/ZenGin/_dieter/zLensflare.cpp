/******************************************************************************** 
 
     $Workfile:: zLensflare.cpp       $                $Date:: 27.01.01 19:42   $
     $Revision:: 3                    $             $Modtime:: 27.01.01 14:11   $
        Author:: Hildebrandt                                                    
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   2D lensflare screen effect
   created: 29.5.2000

 * $Log: /current_work/ZenGin/_Dieter/zLensflare.cpp $
 * 
 * 3     27.01.01 19:42 Moos
 * 
 * 2     20.10.00 0:52 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revisio: 2 $ ($Modtime: 27.01.01 14:11 $)

// =======================================================================================================================

#include <zCore.h>
#include <z3d.h>
#include <zAlgebra.h>
#include <zTypes3D.h>
#include <zVisual.h>
#include <zOption.h>
#include <zArchiver.h>
#include <zMaterial.h>
#include <z3d.h>
#include <zWorld.h>
#include <zLensflare.h>

// =======================================================================================================================

zCLASS_DEFINITION ( zCLensFlareFX		, zCObject		,	zCLASS_FLAG_SHARED_OBJECTS,	2)

///////////////////////////////////////////////////////////////////////////
//    LENSFLARE-FX
///////////////////////////////////////////////////////////////////////////

zCMesh*		zCLensFlareFX::s_lensFlareMesh	= 0;
zCMesh*		zCLensFlareFX::s_coronaMesh		= 0;
zCMesh*		zCLensFlareFX::s_glowMesh		= 0;

void zCLensFlareFX::LoadLensFlareScript () 
{
	// reset/safety
	ReleaseLensFlareScript();
	
	// Mesh Setup
	s_lensFlareMesh	= zCMesh::CreateQuadMesh (FALSE);
	s_coronaMesh	= zCMesh::CreateQuadMesh (FALSE);
	s_glowMesh		= zCMesh::CreateQuadMesh (FALSE);

	zCOLOR col;
	col.SetRGBA (255, 255);
	s_coronaMesh	->SetStaticLight			(col);
	s_coronaMesh	->ResetLightDynToLightStat	();
	s_lensFlareMesh	->SetStaticLight			(col);
	s_lensFlareMesh	->ResetLightDynToLightStat	();
	s_glowMesh		->SetStaticLight			(col);
	s_glowMesh		->ResetLightDynToLightStat	();

	// fx-script laden
	zSTRING	fileName	("lensflare.zen");
	zoptions->ChangeDir	(DIR_PRESETS);
	zCArchiver *arc		= zarcFactory.CreateArchiverRead (fileName);
	if (arc)
	{
		zSTRING chunkName;
		zWORD	chunkVers;
		arc->ReadChunkStart			(chunkName	, chunkVers);
		arc->SetNoReadSearchCycles	(TRUE);
		zCObject *object;
		do {
			object = arc->ReadObject ();
		} while (object);
		zerr.Message ("D: Loading lensflare-script 'lensflare.zen' ("+zSTRING(zCLensFlareFX::GetStaticClassDef()->GetNumObjects())+" fx).");

		// cleanup
		arc->Close  ();
		zRELEASE	(arc);
	};

};

void zCLensFlareFX::ReleaseLensFlareScript()
{
	// Meshes releasen
	zRELEASE (s_lensFlareMesh);
	zRELEASE (s_coronaMesh);
	zRELEASE (s_glowMesh);

	//
	while (GetStaticClassDef()->GetNumObjects()>0)
	{
		zCObject *object = GetStaticClassDef()->GetObjectByIndex (0);
		if (object)	object->Release();
	};
};

zCLensFlareFX::~zCLensFlareFX()
{
	for (int i=0; i<lensFlareList.GetNum(); i++)
	{
		zRELEASE (lensFlareList[i].lensFlareMaterial);
	};
};

#define zFLARE_SIZE_CONST (250.0F)

void zCLensFlareFX::Archive (zCArchiver &arc) 
{
	//
	zCObject::Archive (arc);

	//
	arc.WriteString		("name",		GetObjectName());
	arc.WriteInt		("numFlares",	lensFlareList.GetNum());
	for (int i=0; i<lensFlareList.GetNum(); i++)
	{
		const zTVobLightLensFlare& flare = lensFlareList[i];
		zREAL size;
		if (flare.flareType==zTVobLightLensFlare::FT_GLOW)	size = flare.size / zREAL(100.0F);
		else												size = flare.size / zFLARE_SIZE_CONST;

		arc.WriteChunkStart			(0,0);
		arc.WriteString				("texName"		, flare.lensFlareMaterial->GetTextureName());
		arc.WriteEnum				("type"			, "FT_CORONA;FT_GLOW;FT_FLARE", flare.flareType); 
		arc.WriteFloat				("size"			, size);
		arc.WriteFloat				("alpha"		, flare.alpha);
		arc.WriteFloat				("rangeMin"		, flare.rangeMin);
		arc.WriteFloat				("rangeMax"		, flare.rangeMax);
		arc.WriteFloat				("posScale"		, flare.posScale);
		arc.WriteFloat				("fadeScale"	, flare.fadeScale);
		arc.WriteChunkEnd			();
	};
	arc.WriteFloat					("fadeScale"	, fadeScale);
};

void zCLensFlareFX::Unarchive (zCArchiver &arc) 
{
	//
	zCObject::Unarchive (arc);

	//
	SetObjectName					(arc.ReadString	("name"));
	int numFlares = arc.ReadInt		("numFlares");
	lensFlareList.EmptyList			();
	lensFlareList.AllocAbs			(numFlares);
//	lensFlareList.MarkNumAllocUsed	();

	zSTRING texName;
	zSTRING	chunkName;
	zWORD	chunkVers;
	zBOOL	hasGlow		= FALSE;
	zBOOL	hasNoneGlow	= FALSE;
	for (int i=0; i<numFlares; i++)
	{
		zTVobLightLensFlare flare;
		zBOOL res = arc.ReadChunkStart(chunkName		, chunkVers);
		if (!res) continue;
		arc.ReadString				("texName"		, texName);
		flare.flareType				= zTVobLightLensFlare::zTFlareType(arc.ReadEnum ("type"));
		arc.ReadFloat				("size"			, flare.size);
		arc.ReadFloat				("alpha"		, flare.alpha);
		arc.ReadFloat				("rangeMin"		, flare.rangeMin);
		arc.ReadFloat				("rangeMax"		, flare.rangeMax);
		arc.ReadFloat				("posScale"		, flare.posScale);
		arc.ReadFloat				("fadeScale"	, flare.fadeScale);
		arc.SkipOpenChunk			();

		if (flare.flareType==zTVobLightLensFlare::FT_GLOW) {
			flare.size = flare.size * zREAL(100.0F);
		} else 
			flare.size	= zFLARE_SIZE_CONST / flare.size;

		// Material setup
		flare.lensFlareMaterial						= zNEW(zCMaterial());
		flare.lensFlareMaterial->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_ADD);
		flare.lensFlareMaterial->SetTexture			(texName);
		flare.lensFlareMaterial->SetAlpha			(int(flare.alpha));
		flare.lensFlareMaterial->SetColor			(255,255,255);
	
		//
		lensFlareList.InsertEnd		(flare);
		hasGlow		= hasGlow		|| (flare.flareType==zTVobLightLensFlare::FT_GLOW);
		hasNoneGlow	= hasNoneGlow	|| (flare.flareType!=zTVobLightLensFlare::FT_GLOW);
	};
	
	arc.ReadFloat				("fadeScale"	, fadeScale);

	if (hasGlow &&  hasNoneGlow)	flareMix = FM_MIXED;		else
	if (hasGlow && !hasNoneGlow)	flareMix = FM_GLOW_ONLY;	else
									flareMix = FM_NO_GLOW;		
};

void zCLensFlareFX::RenderLensFlares (zCVob *sourceVob) 
{
	// Lensflare-Effekte rendern
	// ASSERT: zCCamera::activeCam->Activate() muss vorher aufgerufen worden sein, d.h. die camMatrix muss relativ
	//         zum camVob aktuell sein!

	const float fadeTime = 5.0f/1000.0f;

	zERR_ASSERT (sourceVob);
	zERR_ASSERT (zCCamera::activeCam);
	zERR_ASSERT (zCCamera::activeCam->GetVob());
	zERR_ASSERT (zCCamera::activeCam->GetVob()->GetHomeWorld());

	{
		// hier pruefen ob Sichtlinie zum Light besteht 
		// FIXME: a) alle 1/n secs?
		//        b) bei zBuffer: an Light-Scr-Pos: if (zWert== Light-Pos-Z) light visible;
		zCCamera	*cam	= zCCamera::activeCam;

		//
		zBOOL pointVisible = TRUE;

		//
		{ 
			// spezielle Behandlung fuer 0.0 (=Corona-Flare) ??
			// - Groesse von Distanz zu Licht abhaengig ?
			// - alpha von Distanz abhaengig
			// - schneller Implementation fuer diesen spezial-Fall

			// LensFlares rendern
			{

				// trafo
				// FIXME: noetig ?
				zCCamera::activeCam->Activate();
				zREAL	farClipZ	= zMin (cam->GetVob()->GetHomeWorld()->GetVobFarClipZ(), zREAL(10000.0F)); // 100m;
				zPOINT3 lightPosCS	= cam->camMatrix * sourceVob->GetPositionWorld(); 
				if ((lightPosCS[VZ]>0) && (lightPosCS[VZ]<farClipZ)) { 
					// project
					zPOINT2 scrLightPos;
					zCCamera::activeCam->Project (&lightPosCS, scrLightPos[0], scrLightPos[1]);

					if ((flareMix!=FM_GLOW_ONLY) && (pointVisible))
					{
						// Test 1
						// Haupt-Flare muss im Viewport sein .. 
						pointVisible = (zCCamera::activeCam->InViewport (scrLightPos));
						if ((!pointVisible) && (flareMix==FM_NO_GLOW))	return;

						// Test 2
						// TraceRay
						if (pointVisible)
						{
							zVEC3		rayOrg	= cam->GetVob()->GetPositionWorld();
							zVEC3		ray		= (sourceVob->GetPositionWorld() - rayOrg)*0.98F;					// FIXME: HACK !

							zCArray<zCVob*> vobList(3);
							vobList.Insert (sourceVob);
							vobList.Insert (cam->GetVob());
							if (sourceVob->globalVobTreeNode->GetParent())
							if (sourceVob->globalVobTreeNode->GetParent()->GetData())
								vobList.Insert (sourceVob->globalVobTreeNode->GetParent()->GetData()); 

							//
							pointVisible = !(cam->GetVob()->GetHomeWorld()->TraceRayFirstHit (rayOrg, ray, &vobList, zTRACERAY_VOB_IGNORE_CHARACTER));
							if ((!pointVisible) && (flareMix==FM_NO_GLOW))	return;
						};
					};

					// FIXME: moeglichst alle LensFlares batchen, damit dieser StateChange nur 1x pro Frame noetig ist!
					zBOOL foggy = zrenderer ->GetFog();
					if (foggy) zrenderer->SetFog (FALSE);
					{
						zVEC2 vector = cam->GetScreenCenter() - scrLightPos;

						// corona-color
						zCOLOR coronaCol(255,255,255,255);
						if (sourceVob->GetVobType()==zVOB_TYPE_LIGHT) 
							coronaCol = ((zCVobLight*)sourceVob)->GetColor();

						//
						for (int i=0; i<lensFlareList.GetNum(); i++) 
						{
							/*const*/ zTVobLightLensFlare& flare = lensFlareList[i]; 

							// Rendern unterdruecken, falls Textur noch nicht eingecacht
							if (flare.lensFlareMaterial->GetTexture()->CacheIn()!=zRES_CACHED_IN) continue;

							zPOINT2 flarePos;
							if ((flare.flareType==zTVobLightLensFlare::FT_CORONA) ||
							    (flare.flareType==zTVobLightLensFlare::FT_GLOW))
							{
								// Corona/Glow Flare

								// Alpha-Fading
								// Params:	
								zREAL	dist = lightPosCS[VZ];
								if (dist< flare.rangeMin) continue;
								if (dist>=flare.rangeMax) continue;

								// das Alpha ergibt sich aus sinus-Skalierung zw. "rangeMin" und "farClipZ"
								const zREAL	range2	= (flare.rangeMax>0) ? flare.rangeMax : farClipZ;
								const zREAL	range0	= flare.rangeMin;
								zREAL		alpha	= zREAL(2.0F) * zREAL(zSin(((dist-range0) / (range2-range0)) * zREAL(M_PI)));	// FIXME: sin beschleunigen
								int			newAlpha= zFloat2Int(flare.alpha * alpha);
								if (newAlpha>255) newAlpha=255;

								// Glow oder Corona ?
								zBOOL	renderOnTop;
								zREAL	flareZ;
								zCMesh	*mesh;
								if (flare.flareType==zTVobLightLensFlare::FT_CORONA) 
								{
									if (!pointVisible) continue;
									renderOnTop	= TRUE;
									flareZ		= flare.size;
									mesh		= s_coronaMesh;
								} else {
									// Screen-Groesse wird durch flare.size bestimmt
									// Scene-Z wird durch die 'lightPosCS[VZ]' bestimmt.
									renderOnTop	= FALSE;
									// FIXME: evtl. diesen ZBias als Funktion der Distanz zur Camera ?
									flareZ		= lightPosCS[VZ] - zREAL(40.0F);	// zbias
									mesh		= s_glowMesh;
									zREAL size	= flare.size;
									mesh->Vertex(0)->position	= zPOINT3(-size,+size,0);
									mesh->Vertex(1)->position	= zPOINT3(+size,+size,0);
									mesh->Vertex(2)->position	= zPOINT3(+size,-size,0);
									mesh->Vertex(3)->position	= zPOINT3(-size,-size,0);
									// Die BBox ist fuer das clipping/culling noetig
									mesh->bbox3D.mins	= zVEC3(-size, -size, -size);
									mesh->bbox3D.maxs	= zVEC3(+size, +size, +size);
								};

								// rendern
								mesh->SetLightDyn					(coronaCol);

								if (!pointVisible)
								{
									// ist der punkt nicht sichtbar, wird das zu rendernde alpha erst mal so lange kleiner, bis 
									// es auf null ist. das ist dann das echte zu rendernde alpha
									if (flare.fadeScale == 0) continue;

									flare.fadeScale -= fadeTime * (ztimer.GetFrameTimeF());
									if (flare.fadeScale<0) flare.fadeScale = 0;
								}
								else 
								{
									// ist der punkt sichtbar, wird das zu rendernde alpha so lange grösser bis der endalpha
									// wert erreicht ist
									flare.fadeScale += fadeTime * (ztimer.GetFrameTimeF());
									if (flare.fadeScale>1) flare.fadeScale = 1;
								}

								flare.lensFlareMaterial->SetAlpha	(zBYTE(newAlpha * flare.fadeScale));
								mesh->Poly(0)->SetMaterial			(flare.lensFlareMaterial); 
								mesh->RenderDecal					(scrLightPos[VX], scrLightPos[VY], flareZ, renderOnTop); 
							} else {

								if (!pointVisible)
								{
									// ist der punkt nicht sichtbar, wird das zu rendernde alpha erst mal so lange kleiner, bis 
									// es auf null ist. das ist dann das echte zu rendernde alpha
									if (fadeScale == 0) continue;

									fadeScale -= fadeTime * (ztimer.GetFrameTimeF());
									if (fadeScale<0) fadeScale = 0;
								}
								else 
								{
									// ist der punkt sichtbar, wird das zu rendernde alpha so lange grösser bis der endalpha
									// wert erreicht ist
									fadeScale += fadeTime * (ztimer.GetFrameTimeF());
									if (fadeScale>1) fadeScale = 1;
								}


								// LensFlare
								zREAL alphaBackup = flare.lensFlareMaterial->GetAlpha();
								flare.lensFlareMaterial->SetAlpha(zBYTE(alphaBackup * fadeScale));
								zCLensFlareFX::s_lensFlareMesh->Poly(0)->SetMaterial(flare.lensFlareMaterial); 
								flarePos = scrLightPos + (vector * flare.posScale);
								zCLensFlareFX::s_lensFlareMesh->RenderDecal				(flarePos[VX], flarePos[VY], flare.size, TRUE); 
								flare.lensFlareMaterial->SetAlpha(zBYTE(alphaBackup));
							};
						};
					};
					if (foggy) zrenderer->SetFog (TRUE);
				};
			};
		};  
	};
};

void zCLensFlareFX::RenderLensFlares (zPOINT2& scrLightPos) { 
	// Haupt-Flare muss im Viewport sein .. 
	if (zCCamera::activeCam->InViewport (scrLightPos)) 
	{
		const zVEC2 vector = zCCamera::activeCam->GetScreenCenter() - scrLightPos;
		for (int i=0; i<lensFlareList.GetNum(); i++) 
		{
			const zTVobLightLensFlare& flare = lensFlareList[i]; 

			// Rendern unterdruecken, falls Textur noch nicht eingecacht
			if (flare.lensFlareMaterial->GetTexture()->CacheIn()!=zRES_CACHED_IN) continue;

			zPOINT2 flarePos;
			zCLensFlareFX::s_lensFlareMesh->Poly(0)->SetMaterial(flare.lensFlareMaterial); 
			flarePos = scrLightPos + (vector * flare.posScale);
			zCLensFlareFX::s_lensFlareMesh->RenderDecal				(flarePos[VX], flarePos[VY], flare.size, TRUE); 
		};
};
};

void zCLensFlareFX::SetAlpha (int alpha) 
{
	for (int i=0; i<lensFlareList.GetNum(); i++) 
	{
		const zTVobLightLensFlare& flare = lensFlareList[i]; 
		flare.lensFlareMaterial->SetAlpha (alpha);
	};
};

