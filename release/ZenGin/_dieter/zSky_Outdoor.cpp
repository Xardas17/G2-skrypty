#include <zCore.h>
#include <z3d.h>
#include <zWorld.h>
#include <zRenderManager.h>
#include <zSky.h>
#include <zParticle.h>
#include <zView.h>
#include <zLensflare.h>
#include <zMemPool.h>
#include <zVertexTransform.h>
#include <zVertexBuffer.h>
#include <zArchiver.h>
#include <zOption.h>
#include <zPlayerInfo.h>
#include <zWorldinfo.h>

//#define zSKY_DEBUG_KEYS
#include "zinput.h"

zCLASS_DEFINITION		(zCSkyControler_Outdoor	, zCSkyControler_Mid, 0, 1)

//	0		1		2		3		4		5		6		7
//	0		0.2		0.25	0.3		0.5		0.7		0.75	0.8
//	D1		D2		E		N0		N1		N2		D		D0
//					Evening							Dawn

const zREAL TIME_KEY_0	= zREAL(0.00F);		// 0
const zREAL TIME_KEY_1	= zREAL(0.25F);		// 0.2
const zREAL TIME_KEY_2	= zREAL(0.30F);		// 0.25
const zREAL TIME_KEY_3	= zREAL(0.35F);		// 0.3
const zREAL TIME_KEY_4	= zREAL(0.50F);		// 0.5
const zREAL TIME_KEY_5	= zREAL(0.65F);		// 0.7
const zREAL TIME_KEY_6	= zREAL(0.70F);		// 0.75
const zREAL TIME_KEY_7	= zREAL(0.75F);		// 0.8

const int   COLORSPHERE_ALPHA = 255;
const int   SKYDOME_ALPHA	  = 255;


static zVEC2	lensFlarePos;
static int		lensFlareAlpha;
static int		numDomeLayers = 1;
static int		noSky		  = FALSE;
static zREAL	s_fRainWinScale = 0.003f;
static zCMesh*  s_colorDomeMesh = 0;
static zREAL	s_fNearFogScale = 1.0f;
static zREAL	s_fFarFogScale  = 1.0f;

static zBOOL	planetParamsLoaded	= FALSE;
static zSTRING  moonName			= "moon.tga";
static int		moonSize			= 400;
static int		moonAlpha			= 255;
static zSTRING  sunName				= "unSun5.tga";
static int		sunSize				= 200;
static int		sunAlpha			= 230;
static zREAL	realCloudScale		= 0;
static zBOOL	cloudShadowTested   = FALSE;

static zVEC3 S_GetColorFromString(const zSTRING& s)
{
	return zVEC3(	(s.PickWord (1, zSTR_SKIP).ToFloat()),
					(s.PickWord (2, zSTR_SKIP).ToFloat()),
					(s.PickWord (3, zSTR_SKIP).ToFloat()));
};




zCOutdoorRainFX::zCOutdoorRainFX()
{
	m_effectWeight				= 0;
	m_numDestFlyParticle		= 0;
	m_camPosLastFrame			= zVEC3(0);
	m_numFlyParticle			= 0;
	m_numImpactParticle			= 0;
	m_positionUpdateVector		= zVEC3(0,-1,0);
	m_timeLen					= zREAL(1000.0F);	// 1000
	m_velocityLen				= (zREAL(zEFFECT_BOX_HEIGHT)+zREAL(zEFFECT_BOX_HEIGHT)) / m_timeLen;
	m_shader.AddStage			(&this->m_shaderStage);
	m_shaderStage.Clear			();
//	m_shaderStage.alphaFunc		= zRND_ALPHA_FUNC_NONE;
	m_shaderStage.alphaFunc		= zRND_ALPHA_FUNC_BLEND;
	m_shaderStage.alphaGen		= zSHD_ALPHAGEN_VERTEX;
	m_shaderStage.rgbGen		= zSHD_RGBGEN_VERTEX;
	m_soundEffect				= 0;
	m_soundActive				= 0;
	m_raindropTexture			= 0;
	m_rainTexture				= 0;
	m_rainMaterial				= 0;

	for (int i=0; i<zMAX_FLY_PARTICLE; i++)
	{
		m_flyParticleList[i].SetInactive();
	};

	// Cache Elemente invalid machen
	for (i=0; i<zCACHE_SIZE; i++)
	{
		m_cache[i].m_normal[VY]	= -1;
		m_cache[i].m_position	= zVEC3(9999999);		// jwd
	};
	m_currentCacheIndex			= 0;
	m_soundHandle				= 0;
	m_enuWeather				= zTWEATHER_RAIN;
	//m_enuWeather				= zTWEATHER_SNOW;

	SetWeatherType	(zTWEATHER_RAIN);
};

zCOutdoorRainFX::~zCOutdoorRainFX()
{
	zRELEASE (m_raindropTexture);
	zRELEASE (m_rainMaterial   );
	zRELEASE (m_rainTexture	   );
	zRELEASE (m_soundEffect);
};

void zCOutdoorRainFX::UpdateSound (const zREAL soundVolume)
{
	if (soundVolume>0)
	{
		// SoundEffekt erzeugen
		if (!m_soundEffect)
		{
			if (m_enuWeather == zTWEATHER_SNOW) m_soundEffect	  = zsound->LoadSoundFX ("snow_01.wav");
			else					 			m_soundEffect	  = zsound->LoadSoundFX ("rain_01.wav");
		};

		// nur mit dem Sound arbeiten, wenn er eingecacht ist (0.9 => hat Zeit..!)
		// Resource-Caching Strategie
		if (m_soundEffect->CacheIn(0.9F)==zRES_CACHED_IN)
		{
			// Sound erst noch starten, falls er nicht bereits laeuft
			if (!zsound->IsSoundActive (m_soundHandle))
			{
				m_soundHandle			= zsound->PlaySound (m_soundEffect, zSND_SLOT_NONE, zSND_FREQ_DEFAULT, soundVolume, zSND_PAN_DEFAULT);
				m_soundActive			= TRUE;
			};

			// Update Sound Volume
			int		freq;
			float	vol;
			float	pan;
			zsound->GetSoundProps		(m_soundHandle, freq, vol, pan);
			zsound->UpdateSoundProps	(m_soundHandle, freq, soundVolume, pan);
		};
	} else 
	{
		// bei soundVolume==0 einen evtl. laufenden Sound abbrechen
		if (m_soundEffect)
		{
			if (zsound->IsSoundActive (m_soundHandle))
			{
				zsound->StopSound		(m_soundHandle);
				m_soundActive			= FALSE;
			};
		};
	};
};


void zCOutdoorRainFX::SetWeatherType(const zTWeather		 a_weather)
{
	if (a_weather != m_enuWeather)
	{
		// das wetter hat sich geändert
		// alle sounds und texturen müssen neu geladen werden
		zRELEASE (m_raindropTexture);
		zRELEASE (m_rainTexture	   );
		zRELEASE (m_rainMaterial   );
		zRELEASE (m_soundEffect);

		if (a_weather == zTWEATHER_SNOW)
		{
			m_raindropTexture = zCTexture::Load		(zSTRING("SKYRAINSPLASH.TGA"));
			m_rainTexture	  = zCTexture::Load		(zSTRING("snow.TGA"));
			m_soundEffect	  = zsound->LoadSoundFX ("snow_01.wav");
			m_timeLen		  = zREAL(8000.0F);					
			m_velocityLen	  = (zREAL(zEFFECT_BOX_HEIGHT)+zREAL(zEFFECT_BOX_HEIGHT)) / m_timeLen;
			m_rainMaterial	  = zNEW(zCMaterial);
			m_rainMaterial->SetTexture				(m_rainTexture);
			m_rainMaterial->texAniCtrl.SetAniFPS	(1);
			m_rainMaterial->texAniCtrl.SetOneShotAni(TRUE);
		}
		else
		{
			m_raindropTexture = zCTexture::Load (zSTRING("SKYRAINSPLASH.TGA"));
			m_rainTexture	  = zCTexture::Load	(zSTRING("SKYRAIN.TGA"));
			m_soundEffect	  = zsound->LoadSoundFX ("rain_01.wav");
			m_timeLen		  = zREAL(1000.0F);					
			m_velocityLen	  = (zREAL(zEFFECT_BOX_HEIGHT)+zREAL(zEFFECT_BOX_HEIGHT)) / m_timeLen;
		}

		m_enuWeather = a_weather;
	}
};

void zCOutdoorRainFX::SetEffectWeight (const zREAL weight, const zREAL soundVolume)
{
	//
	zERR_ASSERT ((weight>=0) && (weight<=1));
	zERR_ASSERT ((soundVolume>=0) && (soundVolume<=1));

	//
	m_effectWeight				= weight;
	int oldNumDestFlyParticle	= m_numDestFlyParticle;
	m_numDestFlyParticle		= zFloat2Int(m_effectWeight * zREAL(zMAX_FLY_PARTICLE));

	m_numFlyParticle			= m_numDestFlyParticle;

//	int startIndex, endIndex;
//	if (oldNumDestFlyParticle<m_numDestFlyParticle)	{ startIndex = oldNumDestFlyParticle;	endIndex = m_numDestFlyParticle;	}
//	else											{ startIndex = m_numDestFlyParticle;	endIndex = oldNumDestFlyParticle;	};
//	for (int i=startIndex; i<endIndex; i++)
	for (int i=oldNumDestFlyParticle; i<m_numDestFlyParticle; i++)
	{
		if (!m_flyParticleList[i].IsInFreeList())
		{
			zERR_ASSERT							(!m_freeFlyParticleList.IsInList(&m_flyParticleList[i]));
			m_flyParticleList[i].SetInFreeList	();
			m_freeFlyParticleList.Insert		(&(m_flyParticleList[i]));
		};
	};

	#ifdef _DEBUG
		zERR_ASSERT (!m_freeFlyParticleList.CheckDoubles());
	#endif

	UpdateSound(soundVolume);
};

zBOOL zCOutdoorRainFX::CheckCameraBeam (const zVEC3& camPosDelta)
{
	if (camPosDelta.LengthApprox()>(zEFFECT_BOX_SIDES*zREAL(1.5F)))
	{
		// Alle Fly-Partikel freigeben
		for (int i=0; i<m_numDestFlyParticle; i++)
		{
			if (m_flyParticleList[i].IsActive())
			{
				zERR_ASSERT (!m_freeFlyParticleList.IsInList(&m_flyParticleList[i]));
				m_flyParticleList[i].SetInFreeList	();
				m_freeFlyParticleList.Insert		(&(m_flyParticleList[i]));
			};
		};
//		zerr.Message ("D: OUTDOOR_RAIN: cam beamed!");
		return TRUE;
	};
	return FALSE;
};

void zCOutdoorRainFX::CreateParticles (zTRenderContext &renderContext)
{
	if (m_numDestFlyParticle<=0)	return;
	if (ztimer.GetFrameTimeF()<=0)	return;			// keine Partikel erzeugen, wenn das Spiel pausiert

	
	if (s_fRainWinScale>0)
	if (zCSkyControler::GetActiveSkyControler()->GetGlobalWindVec(m_positionUpdateVector, zVISUAL_ANIMODE_WIND))
	{
		m_positionUpdateVector[VX]*= s_fRainWinScale;
		m_positionUpdateVector[VZ]*= s_fRainWinScale;
		m_positionUpdateVector[VY] = -1;
		m_positionUpdateVector.Normalize();
		m_positionUpdateVector *= 1.5F;
		
	}

	//
	zERR_ASSERT		(renderContext.cam);
	zERR_ASSERT		(renderContext.cam->GetVob());

	//
	const zPOINT3	camPos			= renderContext.cam->GetVob()->GetPositionWorld();
//	const zPOINT3	camPos			= zVEC3(0);
	const zVEC3		rayDirX			= (m_positionUpdateVector * zREAL(zEFFECT_BOX_HEIGHT) * zREAL(2.0F)) * zREAL(5.0F);
	const zVEC3		rayDirXX		= (m_positionUpdateVector * zREAL(zEFFECT_BOX_HEIGHT) * zREAL(2.0F)) * zREAL(7.0F);

	zPOINT3			generateCenter	= camPos;
	const zVEC3&	camPosDelta		= camPos - m_camPosLastFrame;
	m_camPosLastFrame				= camPos;

	//
	//	zREAL	particlesPerSecond	= m_numDestFlyParticle;
	const int	maxNumPart			= zFloat2Int((45.0F / 1024.0F) * zREAL(m_numDestFlyParticle));
	zVEC3		destNormal			(0,1,0);
	int			numFlyPartToCreate	= zMin (maxNumPart, m_freeFlyParticleList.GetNum());	// 40, 1024

	// Camera gebeamt?
	// => alle FlyPart freigeben, neu erzeugen und das killTotalTime auf Random 0..1 setzen
	const zBOOL		cameraBeamed	= CheckCameraBeam (camPosDelta);
	if (cameraBeamed)
	{
		numFlyPartToCreate			= zMin (m_numDestFlyParticle, m_freeFlyParticleList.GetNum());
	} else
	{
		generateCenter				+= zREAL(2.0F) * camPosDelta;
		generateCenter				+= renderContext.cam->GetVob()->GetAtVectorWorld() * (zEFFECT_BOX_SIDES * zREAL(0.5F));
	};

	// Loop
	for (int i=0; i<numFlyPartToCreate; i++)
	{
		//
		if (IsInEffectBox	(m_cache[m_currentCacheIndex].m_position-generateCenter))
		{
			// Cache Element wieder-verwertbar
			m_freeFlyParticleList[0]->m_killTotalTime	= 1;
			m_freeFlyParticleList[0]->m_destPosition	= m_cache[m_currentCacheIndex].m_position;
			m_freeFlyParticleList[0]->m_destNormal		= m_cache[m_currentCacheIndex].m_normal;
		} else
		{
			// Neues Ziel fuer Tropfen suchen
			// startPos
			zPOINT3 startPos	= zPOINT3(zRandF2(), 0, zRandF2());
			startPos			= generateCenter + (zREAL(zEFFECT_BOX_SIDES) * startPos);
			startPos[VY]		+= zREAL(zEFFECT_BOX_HEIGHT) * (zRandF() * zREAL(0.5F) + zREAL(0.5F));

			if (renderContext.world->TraceRayNearestHit	(startPos - rayDirX, rayDirXX, (zCVob*)0, zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE | zTRACERAY_POLY_NORMAL | zTRACERAY_POLY_TEST_WATER | zTRACERAY_STAT_PORTALS))
			{
				// zu weit oben bereits auf ein Hindernis getroffen?
				// if (renderContext.world->traceRayReport.foundIntersection[VY]<camPos[VY] + zREAL(zEFFECT_BOX_HEIGHT))
				// continue;
				m_freeFlyParticleList[0]->m_killTotalTime	= 1;
				m_freeFlyParticleList[0]->m_destPosition	= renderContext.world->traceRayReport.foundIntersection;
				m_freeFlyParticleList[0]->m_destNormal		= renderContext.world->traceRayReport.foundPolyNormal;
			} else 
			{
				m_freeFlyParticleList[0]->m_killTotalTime	= 1;
				m_freeFlyParticleList[0]->m_destPosition	= startPos;
				m_freeFlyParticleList[0]->m_destPosition[VY]-= zREAL(zEFFECT_BOX_HEIGHT);
				m_freeFlyParticleList[0]->m_destNormal[VY]	= -1;
			};
			// und in den Cache eintragen..
			m_cache[m_currentCacheIndex].m_position			= m_freeFlyParticleList[0]->m_destPosition;
			m_cache[m_currentCacheIndex].m_normal			= m_freeFlyParticleList[0]->m_destNormal;
		};
		m_currentCacheIndex	= (m_currentCacheIndex+1) & (zCACHE_SIZE-1);

		if (cameraBeamed)
		{
			m_freeFlyParticleList[0]->m_killTotalTime = zRandF();
		};
		//
		m_freeFlyParticleList.RemoveIndex(0);
	};
};

void zCOutdoorRainFX::UpdateParticles ()
{
	// Fly-Particles
	{
		zREAL timeUpdate		= ztimer.GetFrameTimeF() / m_timeLen;
		for (int i=0; i<m_numFlyParticle; i++)
		{
			if (m_flyParticleList[i].IsActive())
			{
				m_flyParticleList[i].m_killTotalTime	-= timeUpdate;
				if (m_flyParticleList[i].m_killTotalTime<0)
				{
					// Nur in FreeList eintragen, wenn Partikel im gueltigen Bereich liegt
					m_flyParticleList[i].SetInactive		();
					if (i<m_numDestFlyParticle)
					{
						zERR_ASSERT (!m_freeFlyParticleList.IsInList(&(m_flyParticleList[i])));
						m_freeFlyParticleList.Insert								(&(m_flyParticleList[i]));
						m_flyParticleList[i].SetInFreeList							();

						// Impact Partikel erzeugen
						if ((m_numImpactParticle<zMAX_IMPACT_PARTICLE) && (m_flyParticleList[i].m_destNormal[VY]>=0))
						{
							m_impactParticleList[m_numImpactParticle].m_killTotalTime	= 1;
							m_impactParticleList[m_numImpactParticle].m_destPosition	= m_flyParticleList[i].m_destPosition;
							m_impactParticleList[m_numImpactParticle].m_destNormal		= m_flyParticleList[i].m_destNormal;
							++m_numImpactParticle;
						};
					};
				};
			};
		};
	};

	// Impact-Particles
	{
		zREAL timeScale			= m_enuWeather == zTWEATHER_RAIN ? (1.0f/300.0f) : (1.0f/10000.0f);
		zREAL timeUpdate		= ztimer.GetFrameTimeF() * timeScale;

		for (int i=0; i<m_numImpactParticle; i++)
		{
			m_impactParticleList[i].m_killTotalTime -= timeUpdate;
			if (m_impactParticleList[i].m_killTotalTime<=0)
			{
				m_impactParticleList[i] = m_impactParticleList[m_numImpactParticle-1];
				--m_numImpactParticle;
				--i;
			};
		};
	};
};

void zCOutdoorRainFX::RenderParticles (zTRenderContext &renderContext, zCOLOR lightColor)
{
	if ((m_numImpactParticle<=0) && (m_numFlyParticle<=0))	return;

	//
	zCVertexBufferDyn2	*vertexBufferDyn	= 0;
	zCVertexBuffer		*vertexBuffer		= 0;
	enum				{ MAX_VERT_PER_POLY = 9 };
	zBYTE				*vbBasePtr			= 0;
	zDWORD				vbOffsetXYZ			= 0;
	zDWORD				vbOffsetColor		= 0;
	zDWORD				vbOffsetTexUV0		= 0;
	zDWORD				vbOffsetTexUV1		= 0;
	zDWORD				vbStride			= 0;

	#define PACK_VERTEX( pos3, color, texUV ) \
		*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= pos3; \
		*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= color; \
		*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= texUV;	vbBasePtr += vbStride;
	
	//
	const zPOINT3& camPos	= renderContext.cam->GetVob()->GetPositionWorld();
	zTPlane camPlane;
	camPlane.normal			= renderContext.cam->GetVob()->GetAtVectorWorld();
	camPlane.distance		= (camPlane.normal * renderContext.cam->GetVob()->GetPositionWorld()) + zREAL(15.0F); // 15cm offset, damit rainDrops SEHR nahe der Camera auch gecullt werden!

	// Fly-Particles
	{
		zREAL flyUp, flyRight;
		
		if (m_enuWeather==zTWEATHER_RAIN)
		{
			flyUp		= -230.0f;
			flyRight	= 08.0f;
		}
		else
		{
			flyUp		= -60.0f;
			flyRight	= 100.0f;
		}

		const zREAL	FLY_SIZE_UP		= flyUp;
		const zREAL	FLY_SIZE_RIGHT	= flyRight;

		zDWORD	startVertIndex;
		int		numVertVB	= 0;
		zVEC3	up			= m_positionUpdateVector * FLY_SIZE_UP;
		zVEC3	right;
		lightColor.SetAlphaByte	(255);

		if (m_raindropTexture==0)
		{
			if (m_enuWeather == zTWEATHER_SNOW) 
			{
				m_raindropTexture = zCTexture::Load		(zSTRING("SKYRAINSPLASH.TGA"));
				m_rainTexture	  = zCTexture::Load		(zSTRING("snow.TGA"));
				
				if (!m_rainMaterial)
				{
					m_rainMaterial	  = zNEW(zCMaterial);
					m_rainMaterial->SetTexture				(m_rainTexture);
					m_rainMaterial->texAniCtrl.SetAniFPS	(1);
					m_rainMaterial->texAniCtrl.SetOneShotAni(TRUE);
				}
			}
			else	
			{
				m_raindropTexture = zCTexture::Load (zSTRING("SKYRAINSPLASH.TGA"));
				m_rainTexture	  = zCTexture::Load	(zSTRING("skyrain.TGA"));
			}
		}
		m_shader.GetStage(0)->texture	= (m_enuWeather == zTWEATHER_SNOW) ? m_rainMaterial->GetAniTexture() : m_rainTexture;
		m_shader.baseTexCachedIn		= (m_shader.GetStage(0)->texture->CacheIn(0.6F)==zRES_CACHED_IN);
		m_shader.GetStage(0)->alphaGen	= zSHD_ALPHAGEN_IDENTITY;

		if (m_shader.baseTexCachedIn)
		{
			zPOINT3			position;
			const zVEC3&	particleVelocityRay	= (this->m_positionUpdateVector * this->m_velocityLen) * (-m_timeLen);

			for (int i=0; i<m_numFlyParticle; i++)
			{
				if (m_flyParticleList[i].IsActive())
				{
					// Passt das naechste Poly noch in den Buffer (bzw. ist der Buffer noch gar nicht erstellt worden) ?
					if ((!vertexBufferDyn) || (((vertexBufferDyn->GetNumVert() - (int(startVertIndex) + numVertVB))-int(MAX_VERT_PER_POLY))<3))
					{
						if (vertexBufferDyn)
						{
							vertexBufferDyn->Unlock			(numVertVB);
							zrenderMan.DrawVertexBuffer		(vertexBuffer, startVertIndex, numVertVB, 0, 0, &m_shader);
						} else 
						{
							vertexBufferDyn					= zrenderMan.GetFreeDynVertexBuffer (&m_shader);
							vertexBuffer					= vertexBufferDyn->GetVertexBuffer();
							vertexBuffer->SetPrimitiveType	(zVBUFFER_PT_TRIANGLELIST);
						};

						numVertVB							= 0;
						vertexBufferDyn->ReserveVerts		(MAX_VERT_PER_POLY);
						if (!vertexBufferDyn->Lock				(startVertIndex))
						{
							zERR_WARNING("C: zCOutdoorRainFX::RenderParticles(): could not lock vertex buffer");
							return;
						}
															
						//
						vbStride			= vertexBuffer->arrayStride;
						vbBasePtr			= vertexBuffer->array.basePtr + (vertexBuffer->arrayStride * startVertIndex);
						vbOffsetXYZ			= zDWORD((zBYTE*)vertexBuffer->array.XYZPtr		- (zBYTE*)vertexBuffer->array.basePtr);
						vbOffsetColor		= zDWORD((zBYTE*)vertexBuffer->array.colorPtr	- (zBYTE*)vertexBuffer->array.basePtr);
						vbOffsetTexUV0		= zDWORD((zBYTE*)vertexBuffer->array.texUV0Ptr	- (zBYTE*)vertexBuffer->array.basePtr);
						vbOffsetTexUV1		= zDWORD((zBYTE*)vertexBuffer->array.texUV1Ptr	- (zBYTE*)vertexBuffer->array.basePtr);
					};

					// Verts packen
					position				= m_flyParticleList[i].m_destPosition + (m_flyParticleList[i].m_killTotalTime * particleVelocityRay);

					if (camPlane.GetDistanceToPlane (position)>0)
					{
						right					= (position-camPos) ^ particleVelocityRay;
						right.NormalizeApprox	();
						right					*= FLY_SIZE_RIGHT;

						PACK_VERTEX				(position - right	, lightColor, zVEC2(0.00F, 1.0F));
						PACK_VERTEX				(position + up		, lightColor, zVEC2(0.5F , 0.0F));
						PACK_VERTEX				(position + right	, lightColor, zVEC2(1.0f , 1.0F));

	//					zlineCache.Line3D		(position, position+zVEC3(0,20,0), GFX_BLUE);
						numVertVB				+= 3;
					};
				};
			};
		};
		if (vertexBufferDyn)
			vertexBufferDyn->Unlock		(numVertVB);
		if (numVertVB>0)
			zrenderMan.DrawVertexBuffer	(vertexBuffer, startVertIndex, numVertVB, 0, 0, &this->m_shader);
	};

	// Impact-Particles
	m_shader.baseTexCachedIn		= (m_raindropTexture->CacheIn(0.6F)==zRES_CACHED_IN);
	m_shader.GetStage(0)->texture	= m_raindropTexture;

	if (m_shader.baseTexCachedIn)
	if (m_numImpactParticle>0)
	{
		vertexBufferDyn			= 0;
		vertexBuffer			= 0;
		zDWORD	startVertIndex	= 9999999;			// => VB neu locken
		int		numVertVB		= 0;
		zVEC3	right;
		zVEC3	at;

		//
		m_shader.GetStage(0)->alphaGen	= zSHD_ALPHAGEN_VERTEX;

		if (m_shader.baseTexCachedIn)
		{
			for (int i=0; i<m_numImpactParticle; i++)
			{
				{
					// Passt das naechste Poly noch in den Buffer (bzw. ist der Buffer noch gar nicht erstellt worden) ?
					if ((!vertexBufferDyn) || (((vertexBufferDyn->GetNumVert() - (int(startVertIndex) + numVertVB))-int(MAX_VERT_PER_POLY))<6))
					{
						if (vertexBufferDyn)
						{
							vertexBufferDyn->Unlock			(numVertVB);
							zrenderMan.DrawVertexBuffer		(vertexBuffer, startVertIndex, numVertVB, 0, 0, &m_shader);
						} else 
						{
							vertexBufferDyn					= zrenderMan.GetFreeDynVertexBuffer (&m_shader);
							vertexBuffer					= vertexBufferDyn->GetVertexBuffer();
							vertexBuffer->SetPrimitiveType	(zVBUFFER_PT_TRIANGLELIST);
						};

						numVertVB							= 0;
						vertexBufferDyn->ReserveVerts		(MAX_VERT_PER_POLY);
						if (!vertexBufferDyn->Lock				(startVertIndex))
						{
							zERR_WARNING("C: zCOutdoorRainFX::RenderParticles(): could not lock vertex buffer");
							return;
						}

															
						//
						vbStride			= vertexBuffer->arrayStride;
						vbBasePtr			= vertexBuffer->array.basePtr + (vertexBuffer->arrayStride * startVertIndex);
						vbOffsetXYZ			= zDWORD((zBYTE*)vertexBuffer->array.XYZPtr		- (zBYTE*)vertexBuffer->array.basePtr);
						vbOffsetColor		= zDWORD((zBYTE*)vertexBuffer->array.colorPtr	- (zBYTE*)vertexBuffer->array.basePtr);
						vbOffsetTexUV0		= zDWORD((zBYTE*)vertexBuffer->array.texUV0Ptr	- (zBYTE*)vertexBuffer->array.basePtr);
						vbOffsetTexUV1		= zDWORD((zBYTE*)vertexBuffer->array.texUV1Ptr	- (zBYTE*)vertexBuffer->array.basePtr);
					};

					// Verts packen
					const zPOINT3& position	= m_impactParticleList[i].m_destPosition + m_impactParticleList[i].m_destNormal;
					if (camPlane.GetDistanceToPlane (position)>0)
					{
						zERR_ASSERT ((m_impactParticleList[i].m_killTotalTime>=0) && (m_impactParticleList[i].m_killTotalTime<=1));
						const zREAL SIZE_MAX	= zREAL(25.0F);
						zREAL size				= (1.0F - m_impactParticleList[i].m_killTotalTime) * SIZE_MAX;
						right					= (m_impactParticleList[i].m_destNormal ^ zVEC3(1,0,0)) * size;	// FIXME: OPTIMIZE
						at						= (m_impactParticleList[i].m_destNormal ^ right);
//						zREAL alpha				= (m_impactParticleList[i].m_killTotalTime);
//						zREAL alpha				= 1.0F - (m_impactParticleList[i].m_killTotalTime);
//						alpha					= 1.0F - (alpha*alpha);
//						lightColor.SetAlphaByte	(zFloat2Int(alpha * zREAL(255.0F)));
						lightColor.SetAlphaByte	(zFloat2Int(m_impactParticleList[i].m_killTotalTime * zREAL(200.0F))+55);
						
						PACK_VERTEX				(position + right + at, lightColor, zVEC2(1.0F, 1.0F));
						PACK_VERTEX				(position + right - at, lightColor, zVEC2(1.0F, 0.0F));
						PACK_VERTEX				(position - right - at, lightColor, zVEC2(0.0f, 0.0F));

						PACK_VERTEX				(position + right + at, lightColor, zVEC2(1.0F, 1.0F));
						PACK_VERTEX				(position - right - at, lightColor, zVEC2(0.0F, 0.0F));
						PACK_VERTEX				(position - right + at, lightColor, zVEC2(0.0F, 1.0F));

						numVertVB				+= 6;
					};
				};
			};
		};
		if (vertexBufferDyn)
			vertexBufferDyn->Unlock			(numVertVB);
		if (numVertVB>0)
			zrenderMan.DrawVertexBuffer		(vertexBuffer, startVertIndex, numVertVB, 0, 0, &this->m_shader);
	};

//	screen->Print (0, 4000, "flyFreePart: "+zSTRING(this->m_freeFlyParticleList.GetNum()));
};



// =======================================================================

void zCSkyState::PresetDay0() 
{
	time						= TIME_KEY_7;
	polyColor					= zVEC3(255,250,235);
	fogColor					= zVEC3(120,140,180);
	domeColor1					= zVEC3(255,255,255);
//	domeColor0					= zVEC3(130,130,130);
	fogDist						= 0.2F;
	sunOn						= TRUE;
	
	layer[0].texName			= "SKYDAY_LAYER1_A0.TGA";
	layer[0].texAlpha			= 00;
	layer[1].texName			= "SKYDAY_LAYER0_A0.TGA";
	layer[1].texSpeed			*= 0.2F;
	layer[1].texAlpha			= 255;
//	cloudShadowOn				= TRUE;
	domeColor0=fogColor;
};

void zCSkyState::PresetDay1() 
{
	time						= TIME_KEY_0;
	polyColor					= zVEC3(255,250,235);
	fogColor					= zVEC3(120,140,180);
	domeColor1					= zVEC3(255,255,255);
//	domeColor0					= zVEC3(130,130,130);
	fogDist						= 0.05F;
	sunOn						= TRUE;
	layer[0].texName			= "SKYDAY_LAYER1_A0.TGA";
	layer[0].texAlpha			= 215;
	layer[1].texAlpha			= 255;
	domeColor0=fogColor;
};

void zCSkyState::PresetDay2() 
{
	time						= TIME_KEY_1;
	polyColor					= zVEC3(255,250,235);
	fogColor					= zVEC3(120,140,180);
	domeColor1					= zVEC3(255,255,255);
	//domeColor0					= zVEC3(130,130,130);
	fogDist						= 0.05F;
	sunOn						= TRUE;
	layer[0].texAlpha			= 0;
	layer[1].texAlpha			= 255;
	domeColor0=fogColor;
};

// =======================================================================

void zCSkyState::PresetEvening() 
{
	time						= TIME_KEY_2;
	polyColor					= zVEC3(255,185,170);
	fogColor					= zVEC3(170,70,50);
	domeColor1					= zVEC3(255,255,255);
	//domeColor0					= zVEC3(255,255,255);
	sunOn						= TRUE;
	layer[0].texAlpha			= 128;
	layer[1].texAlpha			= 128;
	fogDist						= 0.2f;
	domeColor0=fogColor;
};

// =======================================================================

void zCSkyState::PresetNight0() 
{
	time						= TIME_KEY_3;
	polyColor					= zVEC3(105,105,195);
	fogColor					= zVEC3(20,20,60);
	domeColor1					= zVEC3(55,55,155);
	//domeColor0					= zVEC3(0,0,0);
	sunOn						= FALSE;
	fogDist						= 0.1F;

//	layer[0].texName			= "snow2";
//	layer[0].skyMode			= zSKY_MODE_BOX;
	layer[0].texName			= "SKYNIGHT_LAYER0_A0.TGA";
	layer[0].texAlpha			= 255;
	layer[0].texScale			*= 4.0F;
	layer[0].texSpeed			= 0;
	layer[1].texName			= "SKYNIGHT_LAYER1_A0.TGA";
	layer[1].texAlpha			= 00;
	cloudShadowOn				= FALSE;
	domeColor0=fogColor;
};

void zCSkyState::PresetNight1() 
{
	time						= TIME_KEY_4;
	polyColor					= zVEC3(40,60,210);
	fogColor					= zVEC3(5,5,20);
	domeColor1					= zVEC3(55,55,155);
	//domeColor0					= zVEC3(55,55,155);
	fogDist						= 0.05F;
	sunOn						= FALSE;
	layer[0].texAlpha			= 255;
	layer[1].texName			= "SKYNIGHT_LAYER1_A0.TGA";
	layer[1].texAlpha			= 215;
	domeColor0=fogColor;
};

void zCSkyState::PresetNight2() 
{
	time						= TIME_KEY_5;
	polyColor					= zVEC3(40,60,210);
	fogColor					= zVEC3(5,5,20);
	domeColor1					= zVEC3(55,55,155);
	//domeColor0					= zVEC3(0,0,0);
	fogDist						= 0.2F;
	sunOn						= FALSE;
	layer[0].texAlpha			= 255;
	layer[1].texName			= "SKYDAY_LAYER0_A0.TGA";
	layer[1].texAlpha			= 000;
	domeColor0=fogColor;
};

// =======================================================================

void zCSkyState::PresetDawn() 
{
	time						= TIME_KEY_6;
	polyColor					= zVEC3(190,160,255);
	fogColor					= zVEC3(80,60,105);
	domeColor1					= zVEC3(255,255,255);
	//domeColor0					= zVEC3(255,255,255);
	fogDist						= 0.5F;
	sunOn						= TRUE; 
	layer[0].texAlpha			= 128;
	layer[1].texAlpha			= 128;
	domeColor0=fogColor;
};


// ***************************************************************************************************************
// ***************************************************************************************************************
//		SKY / HORIZONT		Deko-Meshes
// **********************


zCSkyLayerData::zCSkyLayerData() 
{
	tex			= 0;
	texAlpha	= 0;
	texScale	= zREAL (1.0F);
	texSpeed	= zVEC2 (1.0f, 0.0f);
//	skyMode		= zSKY_MODE_POLY;
	skyMode		= zoptions->ReadBool("SKY_OUTDOOR", "zSkyDome", TRUE) ? zSKY_MODE_BOX : zSKY_MODE_POLY;
};

zCSkyLayerData::~zCSkyLayerData() 
{
	zRELEASE (tex);
};

zCSkyState::zCSkyState() 
{
	cloudShadowOn	= FALSE;
	sunOn			= TRUE;
	fogDist			= 0;
};

zCSkyState::~zCSkyState() 
{
};



zCMesh* zCSkyLayer::CreateSkyPoly () 
{
	zCMesh *mesh	= zCMesh::CreateQuadMesh (FALSE);
	zCMaterial *mat = zNEW(zCMaterial);
	mesh->SharePoly(0)->SetMaterial(mat);
	mat->Release		();

	const zREAL DIMX = 50000;
	const zREAL DIMY = 1000;
	mesh->ShareVertex(3)->position	= zVEC3(-DIMX,DIMY,-DIMX);
	mesh->ShareVertex(2)->position	= zVEC3(-DIMX,DIMY,+DIMX);
	mesh->ShareVertex(1)->position	= zVEC3(+DIMX,DIMY,+DIMX);
	mesh->ShareVertex(0)->position	= zVEC3(+DIMX,DIMY,-DIMX);
	mesh->CalcNormals();

	return mesh;
};

zCSkyLayer::zCSkyLayer() 
{
	skyTexOffs	= zVEC2(0);
	skyPolyMesh	= CreateSkyPoly();
	skyDomeMesh	= 0;
	skyMode		= zSKY_MODE_POLY;
};

zCSkyLayer::~zCSkyLayer() 
{
	zRELEASE	(skyPolyMesh);
	zRELEASE	(skyDomeMesh);
	skyPoly		= 0;
	skyPolyMesh = 0;
	skyDomeMesh = 0;
};


zCMesh* zCSkyLayer::CreateSkyDomeMesh () 
{
#ifdef USE_SKYBOX
	zCMesh* boxMesh = zNEW(zCMesh);
	boxMesh->AllocVerts	(8);

	zREAL	DIM,YDIM;
	int		NUMPOLY;
	DIM		= YDIM = 300;
	NUMPOLY	= 5;

	const float HORIZON_Y_OFF = 100;

	zCVertex*	vert7	= boxMesh->AddVertex	(zPOINT3(-DIM, +YDIM,  DIM));
	zCVertex*	vert6	= boxMesh->AddVertex	(zPOINT3( DIM,  YDIM,  DIM));
	zCVertex*	vert5	= boxMesh->AddVertex	(zPOINT3(+DIM,  -HORIZON_Y_OFF,  DIM));
	zCVertex*	vert4	= boxMesh->AddVertex	(zPOINT3(-DIM,  -HORIZON_Y_OFF,  DIM));
	zCVertex*	vert3	= boxMesh->AddVertex	(zPOINT3(-DIM, +YDIM, -DIM));
	zCVertex*	vert2	= boxMesh->AddVertex	(zPOINT3( DIM,  YDIM, -DIM));
	zCVertex*	vert1	= boxMesh->AddVertex	(zPOINT3(+DIM,  -HORIZON_Y_OFF, -DIM));
	zCVertex*	vert0	= boxMesh->AddVertex	(zPOINT3(-DIM,  -HORIZON_Y_OFF, -DIM));
 
	boxMesh->AllocPolys	(NUMPOLY);
	zCPolygon*	poly[8];
	poly[0]	= boxMesh->AddPoly	(vert0,vert3,vert2,vert1);
	poly[1]	= boxMesh->AddPoly	(vert1,vert2,vert6,vert5);
	poly[2]	= boxMesh->AddPoly	(vert5,vert6,vert7,vert4);
	poly[3]	= boxMesh->AddPoly	(vert4,vert7,vert3,vert0);
	poly[4] = boxMesh->AddPoly	(vert3,vert7,vert6,vert2);	// up

	zCMaterial* mat=0;
	for (int i=0; i<NUMPOLY; i++) 
	{
		// 3012
		poly[i]->SetMapping (2, zVEC2(+0.00F,+0.000F));
		poly[i]->SetMapping (1, zVEC2(+1.00F,+0.000F));
		poly[i]->SetMapping (0, zVEC2(+1.00F, 1.000F));
		poly[i]->SetMapping (3, zVEC2(+0.00F, 1.000F));
		if ( i==4 ) 
		{
			poly[i]->SetMapping (1, zVEC2(+0.00F,+0.000F));
			poly[i]->SetMapping (0, zVEC2(+1.00F,+0.000F));
			poly[i]->SetMapping (3, zVEC2(+1.00F, 1.000F));
			poly[i]->SetMapping (2, zVEC2(+0.00F, 1.000F));
		};
		for (int j=0; j<poly[i]->polyNumVert; j++) 
		{
			if (poly[i]->vertex[j]->position[VY]<DIM)
				poly[i]->feature[j]->texv =0.5F;
		};

		mat = zNEW(zCMaterial(zSTRING("imp")+zSTRING(i)));
		mat->SetSmooth			(TRUE);
		poly[i]->SetMaterial	(mat);
		mat->Release			();
	};

	boxMesh->CalcBBox3D			();
	boxMesh->CalcVertexNormals	(zCMesh::zMSH_VERTNORMAL_SMOOTH); 
	zCOLOR col;
	col.SetRGBA (255, 255);
	boxMesh->SetStaticLight (col);
	boxMesh->ResetLightDynToLightStat();
	return boxMesh;
#else

	zCMesh*		  boxMesh= zCMesh::Load ("skyDome_layer" + zSTRING(numDomeLayers++) + ".3ds", TRUE);

	if (!boxMesh) return 0;

	// das skydome mesh muss die richtige grösse haben.
	const float DOME_RADIUS = 10.0f;
	float scaler = DOME_RADIUS/boxMesh->GetBBox3D().GetSphere3D().radius;
	boxMesh->Scale(scaler,scaler,scaler);

	
	if (zoptions->ReadBool ("SKY_OUTDOOR", "zColorizeSky", TRUE))
	if (!s_colorDomeMesh )  
	{
		s_colorDomeMesh = zCMesh::Load ("skyDome_colorlayer.3ds" , TRUE);
		if (s_colorDomeMesh) 
		{
			const float DOME_RADIUS = 10.0f;
			float scaler = DOME_RADIUS/s_colorDomeMesh->GetBBox3D().GetSphere3D().radius;
			s_colorDomeMesh->Scale(scaler,scaler,scaler);
			zCMaterial* newMat = zNEW(zCMaterial);
			newMat->SetSmooth(TRUE);
			newMat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_ADD);
			newMat->SetAlpha			(COLORSPHERE_ALPHA);
			s_colorDomeMesh->SetMaterial(newMat);
			zRELEASE(newMat);
			s_colorDomeMesh->CalcVertexNormals	(zCMesh::zMSH_VERTNORMAL_SMOOTH); 
			s_colorDomeMesh->TransformAllVerts (Alg_Translation3D(zVEC3(0,-5,0)), TRUE);
		}
	}


	// das Material des Meshes muss eindeutig sein, wird aber beim laden durch gleichen Materialnamen geshared.
	// Darum wird es jetzt durch ein neues Material ersetzt
	zCMaterial* newMat = zNEW(zCMaterial);
	newMat->SetSmooth(TRUE);
	boxMesh->SetMaterial(newMat);
	zRELEASE(newMat);

	zCOLOR col;
	col.SetRGBA (150, 255);
	boxMesh->SetStaticLight (col);
	boxMesh->ResetLightDynToLightStat();
	boxMesh->CalcVertexNormals	(zCMesh::zMSH_VERTNORMAL_SMOOTH); 

	
	// nun die kuppel unten mit vertex-alpha ausblenden
	// nun die kuppel unten mit vertex-alpha ausblenden
	zCVertex *v;
	float	highestVertYValue			= 0;
	float	lowestVertYValue			= FLT_MAX;

	for (int i=0; i<boxMesh->numVert; i++)
	{
		v = boxMesh->ShareVertex(i);
		if (v->position[VY] < lowestVertYValue)  
		{
			lowestVertYValue = v->position[VY];
		}
	}

	zCVertFeature*	f;
	zCPolygon*		p;
	float			yratio;
	const float DOME_VERTALPHAFADE_ADDOFF = 0;
	const float DOME_YDIST_INV			  = 1.0f/(highestVertYValue-lowestVertYValue);

	for (    i=0; i<boxMesh->numPoly; i++)
	{
		p = boxMesh->SharePoly(i);
		for (int j=0; j<p->polyNumVert; j++)
		{
			f		= p->feature[j];
			v		= p->GetVertexPtr(j);
			if (v->position[VY]>0) 
			{
				f->lightDyn.SetAlphaFloat(1);
				continue;
			}
			yratio	= 1 - ( (v->position[VY] - lowestVertYValue)*DOME_YDIST_INV ) + DOME_VERTALPHAFADE_ADDOFF;;
			zClamp01(yratio);

			f->lightDyn.SetAlphaFloat( 1 - zSinusSlowEnd(yratio) );
		}
	}

	// nun die color kuppel unten mit vertex-alpha ausblenden
	if (::s_colorDomeMesh)
	{
		highestVertYValue = s_colorDomeMesh->bbox3D.maxs[VY];
		lowestVertYValue  = s_colorDomeMesh->bbox3D.mins[VY];

		zCOLOR col;
		col.SetRGBA (150, 150);
		s_colorDomeMesh->SetStaticLight (col);
		s_colorDomeMesh->ResetLightDynToLightStat();

		const float DOME_VERTALPHAFADE_ADDOFF = 0;
		const float DOME_YDIST_INV			  = 1.0f/(highestVertYValue-lowestVertYValue);
		const float DOME_FADEOUT_OFF		  = 0.0001F;

		for (    i=0; i<s_colorDomeMesh->numPoly; i++)
		{
			p = s_colorDomeMesh->SharePoly(i);
			for (int j=0; j<p->polyNumVert; j++)
			{
				f		= p->feature[j];
				v		= p->GetVertexPtr(j);

				yratio	= ( (v->position[VY] - lowestVertYValue)*DOME_YDIST_INV ) + DOME_VERTALPHAFADE_ADDOFF;

				zClamp01(yratio);
				
				if (yratio<DOME_FADEOUT_OFF)
				{
					f->lightDyn.SetAlphaFloat( zLerp(zSinusSlowStart(yratio/DOME_FADEOUT_OFF), 0.0f, 0.8f ) );
				}
				else f->lightDyn.SetAlphaFloat( zLerp(zSinusSlowStart(yratio)-DOME_FADEOUT_OFF, 0.8f, 0.0f ) );
			}
		}
	}

	return boxMesh;
#endif
};


void zCSkyLayer::SetDomeMeshEnabled(const zBOOL m_bEnableSkyDome)
{
	if (m_bEnableSkyDome)
	{
		skyDomeMesh	= CreateSkyDomeMesh(); 
		skyMode		= zSKY_MODE_BOX;
		skyPoly		= skyDomeMesh->SharePoly(0);
	}
	else
	{
		zRELEASE(skyDomeMesh);
		skyMode = zSKY_MODE_POLY;
		skyPoly = skyPolyMesh->SharePoly(0);
	}
};

void zCSkyLayer::SetSkyDomeTexture (zCTexture *tex) 
{
	for (int i=0; i<skyDomeMesh->numPoly; i++)
		skyDomeMesh->SharePoly(i)->GetMaterial()->SetTexture (tex);
};

void zCSkyLayer::SetSkyPolyTexture (zCTexture* tex) 
{ 
	skyPoly->GetMaterial()->SetTexture(tex);	
};

void zCSkyLayer::RenderSkyLayer (zCSkyState* skyLayerState) 
{
	if (GetAlpha()==0) return;
	if (skyMode==zSKY_MODE_POLY)	RenderSkyPoly	(skyLayerState);
	else							RenderSkyDome	(skyLayerState);
};

/*--------------------------------------------------------------------------

    void zCSkyLayer::RenderSkyPoly (zCSkyState* skyLayerState)

	31-Aug-00       [PELZER]
                    Änderung: Hot-Fix zur ECTS-Demo eingebaut. Es wird damit verhindert,
					dass Sky-Triangles im Fog verschwinden. Stattdessen kommt es nun zu
					einer langsam einsetzenden Texturverzerrung in kritischen Camerapositionen.
	01-Sep-00       [PELZER]
                    Hot-Fix zur ECTS-Demo wieder herausgenommen.
	02-Sep-00       [HILDEBRANDT]
                    Komplett neu/anders geschrieben, keine Verzerrer mehr(hoffentlich)
					Ein wenig Cleanup folgt noch.. (z.B. das MemLeak etc.)
	06-Sep-00       [HILDEBRANDT]
					Leak gefixt und Initialisierung des SkyPolyMeshes in den ctor verlegt.

--------------------------------------------------------------------------*/ 

void zCSkyLayer::RenderSkyPoly (zCSkyState* skyLayerState) 
{
	zCCamera				*cam = zCCamera::activeCam;
	zCSkyControler_Outdoor	*sky = (zCSkyControler_Outdoor*)zCSkyControler::GetActiveSkyControler();

	zBOOL	night	= (this==&sky->skyLayer[0]) && (sky->masterTime>=TIME_KEY_1) && (sky->masterTime<=TIME_KEY_7);
	int		channel	= 0;
	if (this==&sky->skyLayer[1]) channel = 1;

	// Farbe des Himmels
	zVEC3 c0;
	if (night) {
		c0 = zVEC3(255,255,255);
	} else {
		c0 = sky->masterState.domeColor1;
	};

	if ((sky->masterTime>=TIME_KEY_3) && (sky->masterTime<=TIME_KEY_5) && (channel==1))
		c0 = 0.5F * (c0 + zVEC3(255,255,255));

	zCOLOR skyCol;
	skyCol.SetRGB		(c0);
	skyCol.SetAlphaByte	(255);

	//
	{
		zCMaterial *mat = skyPoly->GetMaterial();
		if (skyPoly->GetMaterial()->GetAlpha()>=255)	mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_NONE);
		else											mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND);

		zREAL	time=  ztimer.GetTotalTimeF();
		zVEC2	d;
		if (!night)	d	= skyLayerState->layer[channel].texSpeed * time * 0.00001F;
		else		d	= zVEC2(0.0F,0.0F);
		// damit die UVs im guenstigen Bereich um 0 +/- 1 liegen..
		d[0]			-= zFloor (d[0]);
		d[1]			-= zFloor (d[1]);
		const zREAL SCALE = 20.0F * skyLayerState->layer[channel].texScale;
		skyPolyMesh->SharePoly(0)->feature[0]->texu		= 0		+ d.n[VX];
		skyPolyMesh->SharePoly(0)->feature[0]->texv		= 0		+ d.n[VY];
		skyPolyMesh->SharePoly(0)->feature[0]->lightDyn	= skyCol;
		skyPolyMesh->SharePoly(0)->feature[1]->texu		= SCALE + d.n[VX];
		skyPolyMesh->SharePoly(0)->feature[1]->texv		= 0		+ d.n[VY];
		skyPolyMesh->SharePoly(0)->feature[1]->lightDyn	= skyCol;
		skyPolyMesh->SharePoly(0)->feature[2]->texu		= SCALE + d.n[VX];
		skyPolyMesh->SharePoly(0)->feature[2]->texv		= SCALE + d.n[VY];
		skyPolyMesh->SharePoly(0)->feature[2]->lightDyn	= skyCol;
		skyPolyMesh->SharePoly(0)->feature[3]->texu		= 0		+ d.n[VX];
		skyPolyMesh->SharePoly(0)->feature[3]->texv		= SCALE + d.n[VY];
		skyPolyMesh->SharePoly(0)->feature[3]->lightDyn	= skyCol;

//		if (night) 
		{
			cam->camMatrixInv.SetTranslation	(0);
			cam->camMatrix						= cam->camMatrixInv.InverseLinTrafo();
			cam->camMatrixInv.GetTranslation	( zCCamera::activeCamPos );
			cam->SetUpFrustum					(); 
		};

		zTRenderContext renderContext;
		renderContext.Clear					();
		renderContext.cam					= zCCamera::activeCam;
		skyPolyMesh->Render					(renderContext);
	};
};


void zCSkyLayer::RenderSkyDome(zCSkyState* skyLayerState) 
{
	if (noSky)			   return;
	
	// TODO: texturflimmern
	zCCamera				*cam = zCCamera::activeCam;
	zCSkyControler_Outdoor	*sky = (zCSkyControler_Outdoor*)zCSkyControler::GetActiveSkyControler();

	if (sky->GetGlobalSkyScale()==0) return;
	if (sky->GetUnderwaterFX())		 return;

	zBOOL	night	= (this==&sky->skyLayer[0]) && (sky->masterTime>=TIME_KEY_1) && (sky->masterTime<=TIME_KEY_7);
	int		channel	= 0;
	if (this==&sky->skyLayer[1]) channel = 1;

	// Farbe des Himmels
	zVEC3 c0;
	if (night) {
		c0 = zVEC3(255,255,255);
	} else {
		c0 = sky->masterState.domeColor1;
	};


	if ((sky->masterTime>=TIME_KEY_3) && (sky->masterTime<=TIME_KEY_5) && (channel==1))
		c0 = 0.5F * (c0 + zVEC3(255,255,255));

	zCOLOR skyCol;
	skyCol.SetRGB		(c0);

	zCMaterial *mat = skyDomeMesh->SharePoly(0)->GetMaterial();

	// FIXME: nur das letzte Segment des Domes sollte mit Alpha gerendert werden
	// müssen. Derzeit ein wenig langsam, da jedes Poly in eine Alpha Object Liste kommt
	/*if (mat->GetAlpha()>=255)	mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_NONE);
	else						*/
	mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND);
	mat->SetAlpha			(zFloat2Int(sky->GetGlobalSkyScale()*SKYDOME_ALPHA));

	zVEC2	d;

	zREAL dChannel  = (channel == 0) ? 0    : 0.1f;
	zREAL sChannel  = (channel == 0) ? 0.1f : 1.0f;

	if (!night)	d	= (skyLayerState->layer[channel].texSpeed+dChannel) * 0.00001f * sChannel;
	else		d	= zVEC2(0.0F,0.0F);

	mat->SetTexAniMapping   (!night);
	mat->SetTexAniMappingDir(d);

	ColorizeSkyDome();

	cam->camMatrixInv.SetTranslation (0);
	cam->camMatrix = cam->camMatrixInv.InverseLinTrafo();
	cam->camMatrixInv.GetTranslation( zCCamera::activeCamPos );
	cam->SetUpFrustum(); 

	zTRenderContext renderContext;
	renderContext.Clear		();
	renderContext.cam		= zCCamera::activeCam;
	renderContext.clipFlags	= zCCamera::CLIP_FLAGS_FULL_WO_FAR;

	// [EDENFELD] 1.17: Hoffentlich entschärft das sofortige Eincachen den Himmels-Texturbug
	// 1.19: jo, sieht so aus, allerdings ist das so ja nicht so schön. jetzt wissen wir das es ein multithreading problem ist :)
	mat->GetTexture()->CacheIn(-1);

	if (zCWorld::S_GetAlternateRenderOrder())
	{
		zTRnd_ZBufferCmp oldCompare = zrenderer->GetZBufferCompare();
		zBOOL			 oldZWrite	= zrenderer->GetZBufferWriteEnabled();

		zrenderer->SetZBufferCompare		(zRND_ZBUFFER_CMP_LESS);
		zrenderer->SetZBufferWriteEnabled	(FALSE/*channel == 1*/);

		
		skyDomeMesh->RenderHorizon(renderContext,zCCamera::activeCam->GetFarClipZ()-2+channel);

		if (s_colorDomeMesh && sky->GetFarZScalability()>0.75f)
		if (channel == 0)
		{
			//zrenderer->SetZBufferWriteEnabled	(FALSE);
			
			s_colorDomeMesh->RenderHorizon(renderContext,zCCamera::activeCam->GetFarClipZ()-3);
		}

		zrenderer->SetZBufferCompare(oldCompare);
		zrenderer->SetZBufferWriteEnabled(oldZWrite);
	}
	else
	{
		skyDomeMesh->Render		(renderContext,0);

		if (s_colorDomeMesh && sky->GetFarZScalability()>0.75f)
		if (channel == 0)
		{
			s_colorDomeMesh->Render(renderContext,0);
			zrenderer->FlushPolys();
		}
	}

};



void zCSkyLayer::ColorizeSkyDome() 
{

	zCSkyControler_Outdoor	*sky = (zCSkyControler_Outdoor*)zCSkyControler::GetActiveSkyControler();

	zBOOL	night	= (this==&sky->skyLayer[0]) && (sky->masterTime>=TIME_KEY_1) && (sky->masterTime<=TIME_KEY_7);
	int		channel	= 0;
	if (this==&sky->skyLayer[1]) channel = 1;

	// Farbe des Himmels
	zVEC3 c0;
	if (night) {
		c0 = zVEC3(255,255,255);
	} else {
		c0 = sky->masterState.domeColor1;
	};
	if ((sky->masterTime>=TIME_KEY_3) && (sky->masterTime<=TIME_KEY_5) && (channel==1))
		c0 = 0.5F * (c0 + zVEC3(255,255,255));
	zCOLOR skyCol;
	skyCol.SetRGB		(c0);

	if (sky->GetGlobalSkyScaleChanged() && s_colorDomeMesh && this==&sky->skyLayer[0]) 
	{
		s_colorDomeMesh->SharePoly(0)->GetMaterial()->SetAlpha(zFloat2Int(sky->GetGlobalSkyScale()*COLORSPHERE_ALPHA));
	};

	if (!sky->GetColorChanged() && !sky->GetGlobalSkyScaleChanged())	 return;
	if (sky->GetGlobalSkyScale()==0) return;

	zCPolygon*		nextPoly;
	zCVertFeature*	nextFeat;

	for (int i=0; i<skyDomeMesh->numPoly; i++)
	{
		nextPoly = skyDomeMesh->SharePoly(i);
		for (int j=0; j<nextPoly->polyNumVert; j++)
		{
			nextFeat = nextPoly->feature[j];	
			nextFeat->lightDyn.SetRGB(skyCol.GetRedByte(),skyCol.GetGreenByte(),skyCol.GetBlueByte());
		}
	}

	if (this==&sky->skyLayer[0] && s_colorDomeMesh)
	{
		zVEC3 col0,col1;
		zCOLOR myFogColor = zrenderer->GetFogColor();
		col1 = zVEC3(myFogColor.GetRedByte(), myFogColor.GetGreenByte(), myFogColor.GetBlueByte());

		col0	 = col1;
		col1[VX] = (col1[VX] * 0.4f) - 25;
		col1[VY] = (col1[VY] * 0.7f) - 25;
		col1[VZ] = (col1[VZ] * 0.9f) - 25;

		if (sky->masterTime>=TIME_KEY_1 && sky->masterTime<=TIME_KEY_2)
		{
			col0[VX] *=  20;
			col0[VY] *=  20;
			col0[VZ] *=  2;
		}
		else
		{
			col0[VX] *=  10;
			col0[VY] *=  10;
			col0[VZ] *=  8;
		}

		zClamp(col0[VX], 0.0f, 255.0f);
		zClamp(col0[VY], 0.0f, 255.0f);
		zClamp(col0[VZ], 0.0f, 255.0f);
		zClamp(col1[VX], 0.0f, 255.0f);
		zClamp(col1[VY], 0.0f, 255.0f);
		zClamp(col1[VZ], 0.0f, 255.0f);



		//zVEC3 c1 = ((zCSkyControler_Outdoor*)zCSkyControler::GetActiveSkyControler())->masterState.domeColor1;
		{
			zREAL maxy= s_colorDomeMesh->bbox3D.maxs[VY];
			zREAL miny= s_colorDomeMesh->bbox3D.mins[VY];
			zREAL dist= maxy-miny;
			for (int i=0; i<s_colorDomeMesh->numPoly; i++) 
			{
				zCPolygon *poly = s_colorDomeMesh->SharePoly(i);

				zCOLOR col(255,255,255,255);
				for (int j=0; j<poly->polyNumVert; j++) { 

					zPOINT3 pos	= poly->vertex[j]->position;
					zREAL t		= (1-((maxy-pos[VY]) / dist));

					zVEC3 res	= col0 + (zSinusSlowStart(t) * (col1-col0));
					col.r		= zBYTE(res[0]);
					col.g		= zBYTE(res[1]);
					col.b		= zBYTE(res[2]);
					poly->feature[j]->lightDyn.SetRGB(col.GetRedByte(),col.GetGreenByte(),col.GetBlueByte());
				};
			};
		}
	};

};


void zCSkyLayer::RenderRainCloudLayer (zCOLOR layerColor) 
{
	zCCamera *cam = zCCamera::activeCam;

	if (this->skyMode==zSKY_MODE_POLY)
	{
		zCMaterial *mat						= skyPolyMesh->SharePoly(0)->GetMaterial();
		skyPoly->GetMaterial()->SetAlpha	(layerColor.GetAlphaByte());
		if (skyPoly->GetMaterial()->GetAlpha()>=255)	mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_NONE);
		else											mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND);

		zVEC2	d		= zVEC2 (1.3f, 0.3f) * ztimer.GetTotalTimeF() * 0.00001F;
		// damit die UVs im guenstigen Bereich um 0 +/- 1 liegen..
		d[0]			-= zFloor (d[0]);
		d[1]			-= zFloor (d[1]);
		const zREAL SCALE = 30.0F * zREAL(1.0F);
		skyPolyMesh->SharePoly(0)->feature[0]->texu		= 0		+ d.n[VX];
		skyPolyMesh->SharePoly(0)->feature[0]->texv		= 0		+ d.n[VY];
		skyPolyMesh->SharePoly(0)->feature[0]->lightDyn	= layerColor;
		skyPolyMesh->SharePoly(0)->feature[1]->texu		= SCALE + d.n[VX];
		skyPolyMesh->SharePoly(0)->feature[1]->texv		= 0		+ d.n[VY];
		skyPolyMesh->SharePoly(0)->feature[1]->lightDyn	= layerColor;
		skyPolyMesh->SharePoly(0)->feature[2]->texu		= SCALE + d.n[VX];
		skyPolyMesh->SharePoly(0)->feature[2]->texv		= SCALE + d.n[VY];
		skyPolyMesh->SharePoly(0)->feature[2]->lightDyn	= layerColor;
		skyPolyMesh->SharePoly(0)->feature[3]->texu		= 0		+ d.n[VX];
		skyPolyMesh->SharePoly(0)->feature[3]->texv		= SCALE + d.n[VY];
		skyPolyMesh->SharePoly(0)->feature[3]->lightDyn	= layerColor;

//		if (night) 
		{
			cam->camMatrixInv.SetTranslation	(0);
			cam->camMatrix						= cam->camMatrixInv.InverseLinTrafo();
			cam->camMatrixInv.GetTranslation	( zCCamera::activeCamPos );
			cam->SetUpFrustum					(); 
		};

		zTRenderContext renderContext;
		renderContext.Clear					();
		renderContext.cam					= zCCamera::activeCam;
		skyPolyMesh->Render					(renderContext, &layerColor);
	}
	else
	{
		zCSkyControler_Outdoor	*sky = (zCSkyControler_Outdoor*)zCSkyControler::GetActiveSkyControler();

		zCMaterial *mat = skyDomeMesh->SharePoly(0)->GetMaterial();
		mat->SetAlpha(layerColor.GetAlphaByte());

		/*if (mat->GetAlpha()>=255)	mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_NONE);
		else						*/mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND);

		if (sky->GetGlobalSkyScaleChanged()) 
		{
			mat->SetAlpha(zFloat2Int(sky->GetGlobalSkyScale()*layerColor.GetAlphaByte()));
		};

		if (sky->GetGlobalSkyScale()==0) return;
		if (sky->GetUnderwaterFX())		 return;

		zVEC2	d(1.3f,0.3f);

		mat->SetTexAniMapping   (TRUE);
		mat->SetTexAniMappingDir(d * 0.00001f);

		zCPolygon*		nextPoly;
		for (int i=0; i<skyDomeMesh->numPoly; i++)
		{
			nextPoly = skyDomeMesh->SharePoly(i);
			for (int j=0; j<nextPoly->polyNumVert; j++)
			{
				nextPoly->feature[j]->lightDyn.SetRGB(layerColor.GetRedByte(),layerColor.GetGreenByte(),layerColor.GetBlueByte());
			}
		}

		cam->camMatrixInv.SetTranslation (0);
		cam->camMatrix = cam->camMatrixInv.InverseLinTrafo();
		cam->camMatrixInv.GetTranslation( zCCamera::activeCamPos );
		cam->SetUpFrustum(); 

		zTRenderContext renderContext;
		renderContext.Clear		();
		renderContext.cam		= zCCamera::activeCam;
		renderContext.clipFlags	= zCCamera::CLIP_FLAGS_FULL_WO_FAR;


		// [EDENFELD] 1.17: Hoffentlich entschärft das sofortige Eincachen den Himmels-Texturbug
		mat->GetTexture()->CacheIn(-1);

		if (zCWorld::S_GetAlternateRenderOrder())
		{
			zTRnd_ZBufferCmp oldCompare = zrenderer->GetZBufferCompare();
			zBOOL			 oldZWrite	= zrenderer->GetZBufferWriteEnabled();

			zrenderer->SetZBufferCompare		(zRND_ZBUFFER_CMP_LESS);
			zrenderer->SetZBufferWriteEnabled	(FALSE);

			
			skyDomeMesh->RenderHorizon(renderContext,zCCamera::activeCam->GetFarClipZ()-4);
			
			zrenderer->SetZBufferCompare(oldCompare);
			zrenderer->SetZBufferWriteEnabled(oldZWrite);
		}
		else
		{
			skyDomeMesh->Render		(renderContext,0);
		}

	};
};


// ***************************************************************************************************************
// ***************************************************************************************************************
//		zCSkyControler_Outdoor
// ***************************************************************************************************************
// ***************************************************************************************************************

zCSkyControler_Outdoor::zCSkyControler_Outdoor(zBOOL useDomeMesh) 
{
	initDone					= FALSE;
	//							
	masterTime					= 0;
	masterTimeLast				= 0;
	state0						= state1	= 0;
	resultFogScale				= 1;
	skyLayerState[0]			= skyLayerState[1] = 0;
	vobSkyPFX					= 0;
	resultFogScale				= 0;
	heightFogMinY				= 0;
	heightFogMaxY				= 0;
	userFogFar					= 0;
	resultFogNear				= 0;
	resultFogFar				= 0;
	resultFogSkyNear			= 0;
	resultFogSkyFar				= 0;
	resultFogColor				= 0;
	userFarZScalability			= 1;
	skyPFXTimer					= 0;
	polyLightCLUTPtr			= &polyLightCLUT[0];
	dayCounter					= 0;
	m_bIsMainControler			= useDomeMesh;
	//numDomeLayers				= 1;

	rainFX.outdoorRainFX		= zNEW(zCOutdoorRainFX);
	rainFX.camLocationHint		= zCAM_OUTSIDE_SECTOR;
	rainFX.outdoorRainFXWeight	= 0;
	rainFX.soundVolume			= 0;
	rainFX.timerInsideSectorCantSeeOutside	= 0;
	rainFX.timeStartRain		= 0.187F;	// 16.5h
	rainFX.timeStopRain			= 0.25F;	// 17.5h
	rainFX.renderLightning		= FALSE;	// 17.5h
	rainFX.m_bRaining			= FALSE;
	rainFX.m_iRainCtr			= 0;
	skyCloudLayerTex			= 0;

	SetFarZ						(60000);
	CreateDefault				();
	ReadFogColorsFromINI		();

	useDomeMesh = useDomeMesh && zoptions->ReadBool("SKY_OUTDOOR", "zSkyDome", TRUE);

	if (useDomeMesh) numDomeLayers = 1;

	this->skyLayer[0].SetDomeMeshEnabled		(useDomeMesh);
	this->skyLayer[1].SetDomeMeshEnabled		(useDomeMesh);
	this->skyLayerRainClouds.SetDomeMeshEnabled (useDomeMesh);
	m_bSunVisible		= TRUE;
	m_fFadeScale		= 0;
	m_fSkyScale			= 1;
	m_bSkyScaleChanged	= 0;

	{
		this->skyCloudLayerTex	= zCTexture::Load (zSTRING("SKYRAINCLOUDS.TGA"));
		skyLayerRainClouds.SetSkyPolyTexture (skyCloudLayerTex);
	};
	this->m_bOverrideColorFlag = FALSE;

	SetLevelChanged	(TRUE);
	SetDarkSky		(FALSE);
	SetDontRain		(FALSE);
};								

zCSkyControler_Outdoor::~zCSkyControler_Outdoor() 
{
	for (int i=0; i<stateList.GetNumInList(); i++)	delete stateList[i];
	stateList.EmptyList();

	polyLightCLUTPtr	= 0;

	state0				= state1	= 0;
	skyLayerState[0]	= skyLayerState[1] = 0;

	//
	delete rainFX.outdoorRainFX; rainFX.outdoorRainFX=0;

	//
	zRELEASE	(skyCloudLayerTex);
	zRELEASE	(vobSkyPFX);
};

void zCSkyControler_Outdoor::Init () 
{
	initDone = TRUE;

	// planets
	zCOLOR col;
	col.SetRGBA (255, 180);
	for (int i=0; i<NUM_PLANETS; i++) {
		zCMaterial *mat		= zNEW(zCMaterial("zskyplanet"+zSTRING(i)));
		planets[i].mesh		= zCMesh::CreateQuadMesh(FALSE); 
		planets[i].mesh->SharePoly(0)->SetMaterial	(mat);
		planets[i].mesh->SetStaticLight				(col);
		planets[i].mesh->ResetLightDynToLightStat	();
		mat->Release();
	};
	// Sonne
	planets[0].mesh->SharePoly(0)->GetMaterial()->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_ADD);
//	planets[0].mesh->SharePoly(0)->GetMaterial()->SetTexture			(zSTRING("zSun7.tga"));


	if (!planetParamsLoaded)
	{
		planetParamsLoaded = TRUE;
		sunName			= zoptions->ReadString	("SKY_OUTDOOR", "zSunName", sunName.ToChar());
		sunSize			= zoptions->ReadInt		("SKY_OUTDOOR", "zSunSize", sunSize);
		sunAlpha		= zoptions->ReadInt		("SKY_OUTDOOR", "zSunAlpha",sunAlpha);
		moonName		= zoptions->ReadString	("SKY_OUTDOOR", "zMoonName",moonName.ToChar());
		moonSize		= zoptions->ReadInt		("SKY_OUTDOOR", "zMoonSize",moonSize);
		moonAlpha		= zoptions->ReadInt		("SKY_OUTDOOR", "zMoonAlpha",moonAlpha);
		s_fRainWinScale = zoptions->ReadReal	("SKY_OUTDOOR", "zRainWindScale",s_fRainWinScale);
		s_fNearFogScale = zoptions->ReadReal	("SKY_OUTDOOR", "zNearFogScale",s_fNearFogScale);
		s_fFarFogScale  = zoptions->ReadReal	("SKY_OUTDOOR", "zFarFogScale",s_fFarFogScale);
	}

	planets[0].mesh->SharePoly(0)->GetMaterial()->SetTexture			(sunName);
	planets[0].mesh->SharePoly(0)->GetMaterial()->SetAlpha				(sunAlpha);
	planets[0].color1				= zVEC4(255,200,120, 255);
	planets[0].color0				= zVEC4(255,120,  0, 120);
	planets[0].size					= (float)sunSize;
	planets[0].pos					= zVEC3(-60,0,100);
	planets[0].rotAxis				= zVEC3(1,0,0); 
	planets[0].pos.Normalize();
	// Mond
	planets[1].mesh->SharePoly(0)->GetMaterial()->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_ADD);
	planets[1].mesh->SharePoly(0)->GetMaterial()->SetTexture		(moonName);
	planets[1].mesh->SharePoly(0)->GetMaterial()->SetAlpha			(moonAlpha);
	planets[1].color1				= zVEC4(255,255,255, 255);
	planets[1].color0				= zVEC4(255,000,000,-450);
	planets[1].size					= (float)moonSize;
	planets[1].pos					= zVEC3(-30,0,80);
	planets[1].rotAxis				= zVEC3(1,0,0);
	planets[1].pos.Normalize();

	Interpolate					();
	InitSkyPFX					();
	UpdateWorldDependencies		();
};

void  zCSkyControler_Outdoor::SetGlobalSkyScale		(const zREAL skyScale)
{
	/*if (GetFarZScalability()>1.5f) 
	{
		m_fSkyScale		   = 1;
		m_bSkyScaleChanged = TRUE;
		return;			// bei sichtweite über 150% bleibt alles so wie es ist
	}*/
		
	if (m_fSkyScale == skyScale)   return;
	m_fSkyScale		   = skyScale;
	m_bSkyScaleChanged = TRUE;
};


void zCSkyControler_Outdoor::UpdateWorldDependencies () 
{
	// FIXME: Die zCWorld auf eine saubere Art ermitteln !!
	if (!zCCamera::activeCam)							return;
	if (!zCCamera::activeCam->GetVob())					return;
	if (!zCCamera::activeCam->GetVob()->GetHomeWorld())	return;

	// HoehenNebel Grenzen aus Level ermitteln
	const zTBBox3D& box	= zCCamera::activeCam->GetVob()->GetHomeWorld()->GetBBox3DWorldStatic();
	zREAL ydim			= box.maxs[VY]-box.mins[VY];
	heightFogMinY		= box.mins[VY] + 0.5F * ydim;		// davor : 0.3 / 0.6
	heightFogMaxY		= box.mins[VY] + 0.7F * ydim;		// vorher: 0.5 / 0.7
};

int zCSkyControler_Outdoor::GetStateTextureSearch(int i, int channel, zBOOL forward) 
{
	int old = i;
	do {
		if (stateList[i]->layer[channel].texName.Length()>0)	return i;
		if (forward) {
			i++;
			if (i>7) i = 0;
		} else {
			i--;
			if (i<0) i = 7;
		};
		if (i==old) break;
	} while (1);
	return i;
};

void zCSkyControler_Outdoor::ApplyStateTexToLayer (int i, int channel) 
{
	zCTexture *tex;

	tex = stateList[i]->layer[channel].tex;
	if (GetLevelChanged())
	{
		for (int s=0; s<stateList.GetNum(); s++)
		{
			zRELEASE(stateList[s]->layer[0].tex);
			zRELEASE(stateList[s]->layer[1].tex);
		}
		tex = 0;
		SetLevelChanged(FALSE);
	};
	if (!tex) 
	{
		zSTRING worldTexName = stateList[i]->layer[channel].texName;
		worldTexName.Upper();
		zSTRING worldZenName = "_" + zCCamera::activeCam->GetVob()->GetHomeWorld()->GetName();
		worldZenName.Upper();
		
		worldTexName.Insert( worldTexName.Search("_"), worldZenName );

		if ( zCTexture::Exists( worldTexName.PickWord(1,".",".")) )
		{
			stateList[i]->layer[channel].tex= tex = zCTexture::Load (worldTexName);
		}
		else
		{
			zERR_WARNING("C: sky-texture " + worldTexName + " does not exists, trying default sky texture");
			stateList[i]->layer[channel].tex= tex = zCTexture::Load (stateList[i]->layer[channel].texName);
		}
	};
	// Textur-Variation anhand der laufenden TagesNummer einstellen. Die vorhandenen Variationen werden einfach
	// der Reihe nach durchlaufen und dann wiederholt.
	if (tex)
	{
		int texNr;
		int numTexAniFrames	= tex->GetNumAniFrames(0);
		if (numTexAniFrames<=0)	numTexAniFrames = 1;
		if ((stateList[i]->time>=TIME_KEY_3) && (stateList[i]->time<=TIME_KEY_5))
		{
			texNr			= int((this->dayCounter-1) + masterTime);			// NachtTexturen Variation
			texNr			= texNr % (numTexAniFrames);
		} else
		{
			texNr			= int((this->dayCounter-1) + masterTime + 0.50F);	// TagTexturen Variation
			texNr			= texNr % (numTexAniFrames);
			ApplyFogColorsFromINI	(texNr);
		};
		tex->SetActAniFrame		(0, texNr);
		tex	= tex->GetAniTexture();
	};

	// .. und Textur setzen!
	if (stateList[i]->layer[channel].skyMode==zSKY_MODE_POLY)	skyLayer[channel].SetSkyPolyTexture (tex);
	else														skyLayer[channel].SetSkyDomeTexture  (tex);
};

void zCSkyControler_Outdoor::RenderPlanets (const zREAL depth) 
{

	zCCamera	*cam		= zCCamera::activeCam;
	zREAL		xscr,yscr;
	zPOINT3		posWS, posCS;
	zREAL		a;
	zCOLOR		col;

	lensFlarePos[VX]=-1;
	SetScreenBlendAlpha (0);

	for (int i=0; i<NUM_PLANETS; i++) 
	{
		zBOOL dontRender = FALSE;
		zCSkyPlanet& planet = planets[i];
		if (i==0) {
			// 0.3	= Zeitpunkt, an dem der Planet am Horizont ist
			// 1.25 = (0.4/0.5), 0.4 = Laenge des Tages/Nacht, 0.5=halberKreis ;)
			// +0.5 = Verschiebung
			a	= (((masterTime-0.3F)*1.25F+0.5F) * 2.0F * Alg_Deg2Rad (180));		// Sonne
		} else {
			a	= (((masterTime-0.3F)*1.25F+0.0F) * 2.0F * Alg_Deg2Rad (180));		// Sonne
		};

		// camMatrix setzen
		cam->Activate();
		cam->camMatrixInv.SetTranslation (0);
		cam->camMatrix = cam->camMatrixInv.InverseLinTrafo();
		// cam->camMatrixInv.GetTranslation( zCCamera::activeCamPos );
		// cam->SetUpFrustum(); 
		posWS		= Alg_Rotation3DNRad(planet.rotAxis, -a) * planet.pos;
		zREAL dot	= posWS[VY];
		if (dot<-0.5) 
		{
			if (i==1) continue;
			else dontRender = TRUE;
		}
		posCS		= cam->camMatrix * posWS;
		if (posCS[VZ]>0) 
		{
			const zVEC4&	sun1= planet.color1;	
			const zVEC4&	sun0= planet.color0;
			zVEC4			res;

			const zREAL d1 = zREAL( 0.2F);
			const zREAL d0 = zREAL(-0.3F);
			if (dot<d0) 
			{
				if (i==0) dontRender = TRUE;
				else	  continue;
			}
			else if (dot>d1) res = sun1;
			else 
			{
				const	zREAL t	= 1-((d1-dot) / (d1-d0));
				res		= sun0 + t * (sun1 - sun0);
			};

			// Nebel-Tage: planets wegfaden
//			res[3] -= (1.0F-posWS[VY])* resultFogScale*255.0F*2.0F;
			res[3] -= (1.0F-dot)*resultFogScale*255.0F*1.0F;

			// Regen aktiv
			res[3]	*= zREAL(1.0F) - rainFX.outdoorRainFXWeight;

			if (res[3]<=0) 
			{
				if (i==0) dontRender = TRUE;
				else      continue;
			}

			if (!dontRender)
			{
				col.SetRGBA					(zFloat2Int(res[0]), zFloat2Int(res[1]), zFloat2Int(res[2]), zFloat2Int(res[3]));

				planet.mesh->SetLightDyn	(col);

				cam->Project				(&posCS, xscr,yscr);
 
				planet.mesh->SharePoly(0)->GetMaterial()->GetTexture()->CacheIn(-1);
				/*if (alternate)	planet.mesh->RenderDecalHorizon	(xscr,yscr, planet.size, depth);
				else	*/		planet.mesh->RenderDecal		(xscr,yscr, planet.size);
			}

			if (i==0) 
			{
			//	if (dot>0)
				{		
					// Lensflare, ScreenBlend
					const zVEC3& rayOrg	= cam->GetVob()->GetPositionWorld();
					const zVEC3& ray	= 50000.0F * posWS;
					
					m_bSunVisible = !cam->GetVob()->GetHomeWorld()->TraceRayNearestHit (rayOrg, ray, (zCVob*)0, zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_STAT_POLY);
					{
						// Lensflares nur, wenn die Sonne stark genug ist
						const zREAL D		= 0.6F;						// winkel-bereich D .. 1.0
						const zREAL DINV	= zREAL(1.0F / (1.0F-D));
						const zREAL S		= 0.8F;						// max
						zREAL camdot = (cam->GetVob()->GetAtVectorWorld() * posWS) - D;

						lensFlarePos[VX]= xscr;
						lensFlarePos[VY]= yscr;

						if (res[3]>50) 
						{
							lensFlarePos[VX]= xscr;
							lensFlarePos[VY]= yscr;
							lensFlareAlpha	= zFloat2Int(camdot*250.0F);
	//						zCLensFlareFX::SetAlpha (4, zFloat2Int(camdot*250.0F));
						};
						int dotInt = zFloat2Int ( camdot * DINV * (res[3] / 255.0F) * 255.0F * S);
						if (dotInt<0) dotInt = 0;

						static zREAL underHorizonTimer = 0.0f;
						if (dot<0) 
						{
							 underHorizonTimer += ztimer.GetFrameTimeF()/18000;
							 if (underHorizonTimer>1) underHorizonTimer = 1;
						}
						else 
						{
							 underHorizonTimer -= ztimer.GetFrameTimeF()/18000;
							 if (underHorizonTimer<0) underHorizonTimer = 0;
						}

						SetScreenBlendAlpha	(zBYTE(dotInt * (1-underHorizonTimer) * zLerp(m_fFadeScale,0.0f,1.0f)));
						SetScreenBlendColor	(col);
						
						//if (dontRender || (dot<=0) || (dotInt == 0)) m_bSunVisible = FALSE;

						//} else 
					};
				} 
			}
		} 
	};
};


void zCSkyControler_Outdoor::ReadFogColorsFromINI () 
{
	// Fog Farben aus der .ini auslesen (hotfix)
	fogColorDayVariations.AllocAbs (4);
	const char* sectionName	= "SKY_OUTDOOR";
	const char* defaultCol0	= "82 109 198";
	const char* defaultCol1	= "255 255 0";
	const char* defaultCol2	= "18 16 60";
	const char* defaultCol3	= "134 104 125";
	const char* zDayColor0_OW = "90 80 80";
	const char* zDayColor1_OW = "90 80 80";
	const char* zDayColor2_OW = "90 80 80";
	const char* zDayColor3_OW = "90 80 80";

	zVEC3 color;
	zSTRING s;
	s = zoptions->ReadString (sectionName, "zDayColor0", defaultCol0);	color = S_GetColorFromString(s); fogColorDayVariations.Insert (color);
	s = zoptions->ReadString (sectionName, "zDayColor1", defaultCol1);	color = S_GetColorFromString(s); fogColorDayVariations.Insert (color);
	s = zoptions->ReadString (sectionName, "zDayColor2", defaultCol2);	color = S_GetColorFromString(s); fogColorDayVariations.Insert (color);
	s = zoptions->ReadString (sectionName, "zDayColor3", defaultCol3);	color = S_GetColorFromString(s); fogColorDayVariations.Insert (color);

	s = zoptions->ReadString (sectionName, "zDayColor0_OW", zDayColor0_OW);	color = S_GetColorFromString(s); fogColorDayVariations2.Insert (color);
	s = zoptions->ReadString (sectionName, "zDayColor1_OW", zDayColor1_OW);	color = S_GetColorFromString(s); fogColorDayVariations2.Insert (color);
	s = zoptions->ReadString (sectionName, "zDayColor2_OW", zDayColor2_OW);	color = S_GetColorFromString(s); fogColorDayVariations2.Insert (color);
	s = zoptions->ReadString (sectionName, "zDayColor3_OW", zDayColor3_OW);	color = S_GetColorFromString(s); fogColorDayVariations2.Insert (color);

};

void zCCFASTCALL zCSkyControler_Outdoor::ApplyFogColorsFromINI (int varNr)
{
	if (varNr>=fogColorDayVariations.GetNum()) return;

	if (!GetDarkSky())
	{
		stateList[0]->fogColor	= fogColorDayVariations[varNr];
		stateList[1]->fogColor	= fogColorDayVariations[varNr];
		stateList[7]->fogColor	= fogColorDayVariations[varNr];
	}
	else
	{
		stateList[0]->fogColor	= fogColorDayVariations2[varNr];
		stateList[1]->fogColor	= fogColorDayVariations2[varNr];
		stateList[7]->fogColor	= fogColorDayVariations2[varNr];
	};
};

void zCSkyControler_Outdoor::CreateDefault () 
{
	//
	stateList.EmptyList();
	zCSkyState *state;

	// 0
	state = zNEW(zCSkyState	());
	state->PresetDay1		();
	stateList.InsertEnd		(state);

	// 0.2
	state = zNEW(zCSkyState	());
	state->PresetDay2		();
	stateList.InsertEnd		(state);

	// 0.25
	state = zNEW(zCSkyState	());
	state->PresetEvening	();
	stateList.InsertEnd		(state);

	// 0.3
	state = zNEW(zCSkyState	());
	state->PresetNight0		();
	stateList.InsertEnd		(state);

	// 0.5
	state = zNEW(zCSkyState	());
	state->PresetNight1		();
	stateList.InsertEnd		(state);

	// 0.7
	state = zNEW(zCSkyState	());
	state->PresetNight2		();
	stateList.InsertEnd		(state);

	// 0.75
	state = zNEW(zCSkyState	());
	state->PresetDawn		();
	stateList.InsertEnd		(state);

	// 0.8
	state = zNEW(zCSkyState	());
	state->PresetDay0		();
	stateList.InsertEnd		(state);
};

void zCSkyControler_Outdoor::Interpolate () 
{
	// die richtigen States heraussuchen, zwischen denen interpoliert werden soll
	int si0, si1;

	for (int i=0; i<stateList.GetNumInList(); i++) {
		if (masterTime<stateList[i]->time) break;
	};

	si0 = i-1;		if (si0>=stateList.GetNumInList()) si0 = 0; else if (si0<0) si0=stateList.GetNumInList()-1;
	si1 = si0+1;	if (si1>=stateList.GetNumInList()) si1 = 0;

	//
	zCSkyState *s0	= stateList[si0];	state0 = s0;
	zCSkyState *s1	= stateList[si1];	state1 = s1;
	zREAL		s1t	= s1->time;
	if (s1t<s0->time) s1t += zREAL(1.0F);
	zREAL		t	= (masterTime - s0->time) / (s1t - s0->time);
	
	// lerp

	masterState.polyColor	= s0->polyColor + t* (s1->polyColor - s0->polyColor);
	masterState.fogColor	= s0->fogColor	+ t* (s1->fogColor	- s0->fogColor);
	masterState.domeColor1	= s0->domeColor1+ t* (s1->domeColor1- s0->domeColor1);
	masterState.domeColor0	= s0->domeColor0+ t* (s1->domeColor0- s0->domeColor0);
	masterState.fogDist		= s0->fogDist	+ t* (s1->fogDist	- s0->fogDist);

	if (this->GetLevelChanged())
	{
		// wenn der level gewechselt wurde, müssen wir hier einige sachen klarstellen
		

		zSTRING worldZenName = "_" + zCCamera::activeCam->GetVob()->GetHomeWorld()->GetName();
		worldZenName.Upper();

		if (worldZenName.Search("DRAGONISLAND")!=-1)	SetDontRain(TRUE);
		else											SetDontRain(FALSE);

		if (worldZenName.Search("OLDWORLD")!=-1)		SetDarkSky(TRUE);
		else											SetDarkSky(FALSE);

		sunAlpha		= zoptions->ReadInt		("SKY_OUTDOOR", "zSunAlpha",sunAlpha);
		
		if (GetDarkSky())
		{
			planets[0].mesh->SharePoly(0)->GetMaterial()->SetAlpha				(50);
		}
		else
		{
			planets[0].mesh->SharePoly(0)->GetMaterial()->SetAlpha				(sunAlpha);
		}

		

		//SetLevelChanged(FALSE); // erst wenn alle texturen drin sind
	}

	if 	(s_colorDomeMesh) masterState.fogColor *= 0.8F;

	CalcPolyLightCLUT (zVEC3(0,0,0), masterState.polyColor);

	{
		// -1 = search back
		//  0 = take this
		// +1 = search forw
		static int l[2][8] = { 
			 0 , 1, 1, 0,-1,-1,-1, 0,
			 -1,-1,-1, 0, 0,+1,+1, 0 
		};

		int index[2];
		for (int layer=0; layer<2; layer++) 
		{
			switch (l[layer][si0]) {
			case -1:
				index[layer] = GetStateTextureSearch (si0, layer, 0);
				break;
			case  0:
				index[layer] = si0;
				break;
			case +1:
				index[layer] = GetStateTextureSearch (si0, layer, 1);
				break;
			};
		}; 

		skyLayerState[0]		= stateList[index[0]];
		skyLayerState[1]		= stateList[index[1]];
		ApplyStateTexToLayer	(index[0], 0);
		ApplyStateTexToLayer	(index[1], 1);
	};

	skyLayer[0].skyMode		= skyLayerState[0]->layer[0].skyMode;
	skyLayer[1].skyMode		= skyLayerState[1]->layer[1].skyMode;
//	skyLayer[0].SetTexture	(GetStateTexture (index[0], 0)); 
//	skyLayer[1].SetTexture	(GetStateTexture (index[1], 1));

	// Lerp: Texture-Layer Alpha
	zREAL alpha[2];
	for (i=0; i<2; i++) 
	{
		alpha[i] = 	(s0->layer[i].texAlpha + t* (s1->layer[i].texAlpha - s0->layer[i].texAlpha));
		skyLayer[i].SetAlpha(zFloat2Int(alpha[i]));
	};

	// cloudShadow
	/*
	if ((stateList[3]->cloudShadowOn) && (stateList[7]->cloudShadowOn)) {
		cloudShadowScale = 1.0F;
	} else 
	if ((!stateList[3]->cloudShadowOn) && (stateList[7]->cloudShadowOn)) {
		if ((si0<3) || (si0>=5))	cloudShadowScale = alpha[1] / 256.0F; 
		else						cloudShadowScale = 0;
	} else
	if ((stateList[3]->cloudShadowOn) && (!stateList[7]->cloudShadowOn)) {
		if ((si0<3) || (si0>=5))	cloudShadowScale = 0;
		else						cloudShadowScale = alpha[0] / 256.0F;
	} else
		cloudShadowScale = 0;*/

	

	if (!cloudShadowTested)
	{
		if (cloudShadowScale != 0) 
		{
			cloudShadowTested = TRUE;
			realCloudScale	= cloudShadowScale;
		}
	}

	cloudShadowScale = (this->m_enuWeather == zTWEATHER_SNOW) ? rainFX.outdoorRainFXWeight : (realCloudScale * rainFX.outdoorRainFXWeight);

	static zCOLOR lastColor(0,0,0,0);
	zCOLOR thisCol( zFloat2Int(masterState.fogColor[0]), zFloat2Int(masterState.fogColor[1]), zFloat2Int(masterState.fogColor[2]) ,0);
	// wenn sich die farbe nicht geändert hat, brauchen wir einige polys nicht neu zu beleuchten, dies sollte man hier abfragen können
	if (lastColor.GetRedByte  ()==thisCol.GetRedByte  ()				&&
		lastColor.GetGreenByte()==thisCol.GetGreenByte()				&&
		lastColor.GetBlueByte ()==thisCol.GetBlueByte ()	)
	{
		SetColorChanged(FALSE);
	}
	else 
	{
		SetColorChanged(TRUE);
		lastColor = thisCol;
	}

	if (this->GetLevelChanged()) SetColorChanged(TRUE);

	// wenn es regnet machen wir auch alle 2 frames die farbe gut
	if (cloudShadowScale>0)
	if (rainFX.camLocationHint!=zCAM_INSIDE_SECTOR_CANT_SEE_OUTSIDE && rainFX.outdoorRainFXWeight!=0)
	{
		if (zCCamera::activeCam								&& 
			zCCamera::activeCam->GetVob()					&& 
			zCCamera::activeCam->GetVob()->GetHomeWorld()	&&
			(zCCamera::activeCam->GetVob()->GetHomeWorld()->GetMasterFrameCtr() & 2) == 0)
		{
			SetColorChanged(TRUE);
		}
	}

};
	//	1=0		0.25	0.5		0.75	1=0
	//	Tag		Abend	Nacht	Morgen	Tag

void zCSkyControler_Outdoor::SetTime (const zREAL time) 
{
	masterTime = time;

	if (zAbs(lastRelightTime-masterTime)>m_fRelightTime)
//	if (lastRelightTime!=masterTime)
	{
		relightCtr++;
		lastRelightTime = masterTime;
	};
};

void zCSkyControler_Outdoor::ResetTime ()
{
	this->SetTime		(0);
	this->dayCounter	= 0;
};

zCOLOR zCSkyControler_Outdoor::GetDaylightColorFromIntensity(int intensity) 
{
	return polyLightCLUT[intensity];
};

void zCSkyControler_Outdoor::CalcPolyLightCLUT (const zVEC3& col0, const zVEC3& col1) 
{
	zCOLOR		col;
	int			cc[3];
	int			cdelta[3];
//	zREAL c		= col0;
	zVEC3 delta	= (col1-col0) / zREAL(256.0F);
	cc[0]		= zFloat2Int(col0[0]) << 16;
	cc[1]		= zFloat2Int(col0[1]) << 16;
	cc[2]		= zFloat2Int(col0[2]) << 16;
	cdelta[0]	= zFloat2Int(delta[0] * 65536);
	cdelta[1]	= zFloat2Int(delta[1] * 65536);
	cdelta[2]	= zFloat2Int(delta[2] * 65536);
	col.alpha	= 255;
	for (int i=0; i<256; i++) {
//		c		+= delta;
//		col.SetRGB (zBYTE(zFloat2Int(c[0])), zBYTE(zFloat2Int(c[1])), zBYTE(zFloat2Int(c[2])));
		cc[0]	+= cdelta[0];
		cc[1]	+= cdelta[1];
		cc[2]	+= cdelta[2];
		col.SetRGB (cc[0]>>16, cc[1]>>16, cc[2]>>16);
		polyLightCLUT[i] = col;
	};
};


void zCSkyControler_Outdoor::InitSkyPFX() 
{
	skyPFXTimer=0;
	zCParticleFX *partFX= zNEW(zCParticleFX());
	vobSkyPFX			= zNEW(zCVob());
	vobSkyPFX	->SetCollDet			(FALSE);
	vobSkyPFX	->RotateLocalY			(45);
	vobSkyPFX	->SetPositionWorld		(0,500,-1000); 
	vobSkyPFX	->SetVisual				(partFX);
	partFX		->SetDontKillPFXWhenDone(TRUE); 
	partFX		->SetEmitter			("ZSKYNIGHT1");
	partFX		->CreateParticles		();
	partFX->Release();
};

void zCSkyControler_Outdoor::CalcFog() 
{
	// Unterwasser ? => nicht lange rumrechnen..
	if (GetUnderwaterFX()) {
		resultFogColor			= GetUnderwaterColor();
		resultFogColorOverride  = resultFogColor;
		resultFogSkyFar	= 1000.0F;
		resultFogSkyNear= 0.0F;
		resultFogFar	= GetUnderwaterFarZ();
		resultFogNear	= 0.0F;
		return;
	};


	// ************************
	//		Fog-Range
	// ************************

	// Dynamik-Bereich ermitteln
	zREAL userFogMid	= userFogFar * 0.4F;
	//	if (userFogMid<20000) userFogMid=20000;
	zREAL userFogDelta	= userFogFar-userFogMid;

	// Tageszeitlicher Nebel
	zREAL fogTimeScale	= masterState.fogDist;
	
	// Höhen-Nebel
	zREAL ypos			= zCCamera::activeCam->GetVob()->GetPositionWorld()[VY];
	zREAL fogYScale;
	if ( heightFogMaxY-heightFogMinY != 0) fogYScale = (ypos - heightFogMinY) / (heightFogMaxY-heightFogMinY);
	else								   fogYScale = 0;
	zClamp01			(fogYScale);

	//
	zREAL resScale		= zMax (fogTimeScale, fogYScale);
	resultFogScale		= resScale;
	resScale			= 1.0F - resScale;
	//	resScale			= 1.0F-(fogTimeScale * fogYScale);

	// fog: terrain
	resultFogFar		= userFogMid + resScale * userFogDelta;
	resultFogFar		*= userFarZScalability;
	resultFogNear		= 0.3f * resultFogFar;  

	if (rainFX.outdoorRainFXWeight>0)
	{
		static zREAL nearestFog = -2500.0f;
		//static zREAL nearestFog = -2.0f;
		if (zinput->KeyPressed(KEY_LSHIFT) && zinput->KeyPressed(KEY_GREYPLUS))
		{
			nearestFog += 100;
			zERR_WARNING("C: nearestFog: " + zSTRING(nearestFog));
		}
		else if (zinput->KeyPressed(KEY_LSHIFT) && zinput->KeyPressed(KEY_GREYMINUS))
		{
			nearestFog -= 100;
			zERR_WARNING("C: nearestFog: " + zSTRING(nearestFog));
		}

		// Bei Regen: fogNear auf 0 ziehen, fogFar auf X m ziehen, falls es ueber X liegt
		resultFogNear				= zLerp(rainFX.outdoorRainFXWeight, resultFogNear, nearestFog);
		//const zREAL rainWeightInv	= zREAL(1.0F) - rainFX.outdoorRainFXWeight;
		//resultFogNear				*= rainWeightInv;
		
		// Ab 1.13 wird bei Regen die Fogfarclipping plane nicht mehr rangeholt
		/*const zREAL minFogFar		= zREAL(7500.0F);
		if (resultFogFar>minFogFar)
		{
			resultFogFar			= minFogFar + (resultFogFar - minFogFar) * rainWeightInv;
		};*/
	};

	// fog: sky
	zREAL skyUserFar	= zMin (40000.0F, resultFogFar	* 1.5F) * 0.5F;
	zREAL skyUserMid	= zMax (10000.0F, resultFogNear	* 1.5F) * 0.5F;
	resultFogSkyFar		= skyUserMid + resScale * (skyUserFar-skyUserMid);
	resultFogSkyNear	= 0.25F * resultFogSkyFar;
	
	if ((rainFX.outdoorRainFXWeight>0))
	{
		resultFogSkyNear	= 0.10F * resultFogSkyFar;
		resultFogSkyFar		*= zREAL(0.8F);
	};

	// ************************
	//		Fog-Color
	// ************************

	// je hoeher Nebel/geringer die Sichtweite, desto wenige 'krass' darf der Nebel sein,
	// besonders wichtig fuer Abend/Morgen (z.B. rosa/lila)
	// ACHTUNG: eigentlich sollten R/G/B Werte der fog farbe genommen werden, aber obs nun ein bug ist oder nicht,
	// nimmt man die Intensität nur aus dem R Wert, so sieht der Himmel besser aus, da er dann auch grauer wirkt
	
	zREAL intens		= (0.299F*masterState.fogColor[0] + 0.587F*masterState.fogColor[0] + 0.114F*masterState.fogColor[0]);
	if (intens>120)		intens=120;
	zVEC3 grey			= zVEC3(intens);
	zREAL s				= resultFogScale*0.5F;
	zVEC3 col			= (1.0F-s)*masterState.fogColor + (s)*grey;
	
	// vorhandener Regen faerbt den Nebel grau ein (Nachts natuerlich blau/schwarz)
	if (rainFX.outdoorRainFXWeight>0)
	{
		col				= zLerp (rainFX.outdoorRainFXWeight, col, grey);
	};

	resultFogColor.SetRGB (col);

	// so nun fehlt nur noch die override color farbe
	intens				= (0.299F*m_overrideColor[0] + 0.587F*m_overrideColor[1] + 0.114F*m_overrideColor[2]);
	if (intens>120)		intens=120;
	grey				= zVEC3(intens);
	col					= (1.0F-s)*m_overrideColor + (s)*grey;
	
	// vorhandener Regen faerbt den Nebel grau ein (Nachts natuerlich blau/schwarz)
	if (rainFX.outdoorRainFXWeight>0)
	{
		col				= zLerp (rainFX.outdoorRainFXWeight, col, grey);
	};

	resultFogColorOverride.SetRGB(col);
	

};

void zCSkyControler_Outdoor::SetFarZ (const zREAL z) 
{
	// FIXME: Fehlverhalten bei extrem grossen Z Werten
	userFogFar = z;
};

zREAL zCSkyControler_Outdoor::GetFarZ () const 
{
	return userFogFar;
};

void zCSkyControler_Outdoor::SetFarZScalability (const zREAL zscale)
{
	userFarZScalability	= zscale;
	zClamp (userFarZScalability, zREAL(0), zREAL(4));
};

zREAL zCSkyControler_Outdoor::GetFarZScalability () const
{
	return userFarZScalability;
};

void zCSkyControler_Outdoor::RenderSkyPFX() 
{
	// Sternschnuppen
	if ((masterTime<=TIME_KEY_2) || (masterTime>=TIME_KEY_5))	return;		// nur Nachts
	if (this->rainFX.outdoorRainFXWeight>zREAL(0.4F))			return;		// nicht bei Regen

	zCCamera		*cam	= zCCamera::activeCam;
	zCParticleFX	*partFX = (zCParticleFX*)(vobSkyPFX->GetVisual());
	
	if (partFX->GetFirstParticle()==0) {
		if (skyPFXTimer<=0) {
			skyPFXTimer		= zREAL(500.0F) + zRandF() * zREAL(2000.0F);
			zVEC3 at		= cam->GetVob()->GetAtVectorWorld();
			zVEC3 right		= cam->GetVob()->GetRightVectorWorld();
			zVEC3 pos;
			right[VY]=0; right.NormalizeApprox();
			at   [VY]=0; at   .NormalizeApprox();

			pos		= at;
			pos		+= (zRandF()*2.0F - 1.0F) * 0.5F * (at+right);	// nur x,z
			pos[VY] += 0.1F + zRandF();

			pos.NormalizeApprox();
			pos		*= 800.0F;

			vobSkyPFX	->SetPositionWorld(pos); 
			partFX		->CreateParticles ();
		} else {
			skyPFXTimer		-= ztimer.GetFrameTimeF();
			return;
		};
	};

	zCCamera::activeCam->Activate		();		// FIXME: geht effizienter

	cam->camMatrixInv.SetTranslation	(0);
	cam->camMatrix = cam->camMatrixInv.InverseLinTrafo();
	cam->camMatrixInv.GetTranslation	( zCCamera::activeCamPos );
	cam->SetUpFrustum					(); 

	zTRenderContext renderContext;
	renderContext.Clear					();
	vobSkyPFX->GetVisual				()->Render(renderContext);
};


void zCSkyControler_Outdoor::CalcGlobalWind()
{
	static zMAT4 windMat			= Alg_Identity3D();
	static zREAL windAngleVelo		= 0.9f;
	static zREAL windAngleVeloVar	= 0.8f;
	static zREAL windStrength		= 70;
	static zREAL windStrengthVar	= 40;
	static zREAL windCycleTime		= 4;			// sekunden, bis nächster Windstoss beginnt#
	static zREAL windCycleTimeVar	= 2;			// sekunden, bis nächster Windstoss beginnt#
	static zREAL actWindCycleTime	= windCycleTime;
	static zREAL actWindStrength	= windStrength;
	static zREAL actWindAngleVelo	= windAngleVelo;
	static zREAL windTime			= 0;
	static zREAL windSign			= 1;
	static zBOOL resetWind			= TRUE;
	static zBOOL firstTime			= TRUE;

	if (!this->m_bIsMainControler) return;
	if (ztimer.GetFrameTimeF()== 0) return;

	if (firstTime)
	{
		firstTime = FALSE;
		windCycleTime		= zoptions->ReadReal("ENGINE","zWindCycleTime",		windCycleTime);
		windCycleTimeVar	= zoptions->ReadReal("ENGINE","zWindCycleTimeVar",	windCycleTimeVar);
		windStrength		= zoptions->ReadReal("ENGINE","zWindStrength" ,		windStrength);
		windStrengthVar		= zoptions->ReadReal("ENGINE","zWindStrengthVar" ,	windStrengthVar);
		windAngleVelo		= zoptions->ReadReal("ENGINE","zWindAngleVelo",		windAngleVelo);
		windAngleVeloVar	= zoptions->ReadReal("ENGINE","zWindAngleVeloVar",	windAngleVeloVar);
		m_bIsMainControler  = zoptions->ReadBool("ENGINE","zWindEnabled",		m_bIsMainControler);
		if (!m_bIsMainControler) zCVob::SetAnimationsEnabled(FALSE);	// FIXME
	}

	if (resetWind)
	{
		actWindCycleTime= windCycleTime + (zRandF(windCycleTimeVar)-(windCycleTimeVar/2) );
		actWindStrength = windStrength  + (zRandF(windStrengthVar) -(windStrengthVar/2)  );
		actWindAngleVelo= windAngleVelo + (zRandF(windAngleVeloVar)-(windAngleVeloVar/2) );

		// windstille phase ?
		if ( zRandF()>0.7F )
		{
			actWindStrength  *= 0.35f;
			actWindAngleVelo *= 0.35f;
		}
		resetWind = FALSE;
	}

	// solange zur aktuellen windstärke interpolieren, bis
	// ende erreicht wurde

	zREAL  timeCorr = ztimer.GetFrameTimeF()/1000;

	windTime		 += windSign * timeCorr;
	if ( windTime>=actWindCycleTime ) 
	{
		windSign		= -1 * windSign;
		windTime		= actWindCycleTime;
	} 
	else if ( windTime<=0 )
	{   
		windSign		= -1 * windSign;
		windTime		= 0;
		resetWind		= TRUE;
	}

	windMat.PostRotateY(					zSinusEase(windTime/actWindCycleTime) * actWindAngleVelo  );
	m_bWindVec = windMat.GetAtVector()	*   zSinusEase(windTime/actWindCycleTime) * actWindStrength;
}


zBOOL zCSkyControler_Outdoor::GetGlobalWindVec(zVEC3 &resVec, const zTAnimationMode aniMode)
{
	if (!m_bIsMainControler) return FALSE;
	resVec = m_bWindVec;
	return TRUE;
}


zREAL	zCSkyControler_Outdoor::GetCloudShadowScale		() const
{
	return cloudShadowTested ? realCloudScale : cloudShadowScale;
};

void	zCSkyControler_Outdoor::SetCloudShadowScale		(const zREAL f)
{
	if (cloudShadowTested) realCloudScale = f;
	else 
	{
		realCloudScale  = f;
		cloudShadowScale= f;
		cloudShadowTested=TRUE;
	};
	this->SetColorChanged(TRUE);
};





void zCSkyControler_Outdoor::RenderSkyPre () 
{

	if (!initDone) Init();
	//
	zCSkyControler_Mid::RenderSkyPre ();

	// Globalen Wind berechnen
	CalcGlobalWind();

	//
	static int skyVari =0;

	#ifdef zSKY_DEBUG_KEYS
		static zBOOL timeAni = FALSE;
		{
			if (zinput->KeyPressed(KEY_LCTRL)) {
				const zREAL D = 0.01F;
				if (zinput->KeyPressed(KEY_UP))		masterTime	= masterTime+D;
				if (zinput->KeyPressed(KEY_DOWN))	masterTime	= masterTime-D;
				if (zinput->KeyToggled(KEY_HOME))	timeAni		= !timeAni;
				while (masterTime>=1.0F) { masterTime -= 1.0F; };
				while (masterTime<0.0F)  { masterTime += 1.0F; };
				//Interpolate		();
				zERR_MESSAGE(8,0,"D: dayTime: "+zSTRING(masterTime,2));
			} else
			if (zinput->KeyPressed(KEY_LALT)) {
				const zREAL D = 0.05F;
				if (zinput->KeyToggled(KEY_UP))		rainFX.outdoorRainFXWeight	= zMin (1.0F, rainFX.outdoorRainFXWeight+D);
				if (zinput->KeyToggled(KEY_DOWN))	rainFX.outdoorRainFXWeight	= zMax (0.0F, rainFX.outdoorRainFXWeight-D);
				zERR_MESSAGE(8,0,"D: outdoorRainFXWeight: "+zSTRING(rainFX.outdoorRainFXWeight,2));
			} 
			else if (zinput->KeyToggled(KEY_F10))
			{
				noSky = !noSky;
			}
			else
			{
				if (zinput->KeyToggled(KEY_F6)) skyVari	= (skyVari+1)%3;
			}

		};
		if (timeAni)
		{
			masterTime += ztimer.GetFrameTimeF() * 0.000001F;
			if (masterTime>1.0F) masterTime-= 1.0F;
		}
		SetTime (masterTime);
	#endif

	// Um 12h wird gewuerfelt, wann es am naechsten Tag regnet.
	// Ausserdem wird der DayCtr weitergezaehlt.
	if (((masterTimeLast-masterTime)>0.95F) && (masterTime<zREAL(0.02F)))
	{
		// 1h = 0.042
		const zREAL RAIN_MIN_LEN= zREAL(0.042F);

		// StartTime
		rainFX.timeStartRain	= zRandF();		
		if (rainFX.timeStartRain>zREAL(1.0F)-RAIN_MIN_LEN) rainFX.timeStartRain = zREAL(1.0F)-RAIN_MIN_LEN;

		// StopTime
		rainFX.timeStopRain		= rainFX.timeStartRain + 
								  (RAIN_MIN_LEN + zRandF() * zREAL(0.06F));	// 1.0h + rand*1.0h => [1.0h..2.5h]
		if (rainFX.timeStopRain>zREAL(1.0F))				rainFX.timeStopRain	= zREAL(1.0F);

		rainFX.renderLightning	= (rainFX.m_iRainCtr>3) && zRandF()>0.6f;			// die ersten drei spieltage regnet es nur, und dann blitzt es mit einer wahrscheinlichkeit von 40%

		//
		zERR_MESSAGE (5, 0, "D: SKY: RAIN: rolling dice.. "+zSTRING(rainFX.timeStartRain,2)+"/"+zSTRING(rainFX.timeStopRain,2));

		//
		this->dayCounter		+= 1;
	};

	// FIXME: noch weiter optimieren, am Tage nur alle 2 Frames ?
	if (masterTime!=masterTimeLast) {
		Interpolate();
	};

	// FOG
	zREAL			fogNear, fogFar;
	zTRnd_FogMode	fogMode;

	CalcFog								();
	RenderSetup							();

	zBOOL cacheAlphaPolys = zrenderer->GetCacheAlphaPolys();
	zrenderer->SetCacheAlphaPolys(FALSE);

	zrenderer->GetFogRange				(fogNear, fogFar, fogMode);

	// Nebel fuer Sky setzen
	zrenderer->SetFogRange				(resultFogSkyNear, resultFogSkyFar, zRND_FOG_FALLOFF_LINEAR);

	// Sky rendern
	if (!zCWorld::S_GetAlternateRenderOrder()) RenderSky();	

	// Sternschnuppen
	RenderSkyPFX						();
	RenderPlanets						(0);
	zrenderer->FlushPolys				();

	// Nebel fuer Terrain setzen
	zrenderer->SetFogRange				(s_fNearFogScale * resultFogNear, resultFogFar * s_fFarFogScale, fogMode);

	// IDEE: Der Terrain Nebel wird je weiter die Nearfog Plane rangeholt wird proportional zur Planedistanz heller dargestellt,
	// damit auf leistungsschwächeren Rechnern der Kontrast zum Himmel nicht mehr so start ist
	// (ACHTUNG: Nur wenn auch zColorizeSky in der INI eingetragen ist)

/*	zCOLOR terrainFogCol = this->resultFogColor;
	zREAL factor = 1;
	if (this->GetFarZScalability()<1) factor = zLerp( 1-this->GetFarZScalability() , 1.0f, 1.2f );

	terrainFogCol.SetRedFloat	( MIN(1,terrainFogCol.GetRedFloat()   * factor) );
	terrainFogCol.SetGreenFloat	( MIN(1,terrainFogCol.GetGreenFloat() * factor) );
	terrainFogCol.SetBlueFloat	( MIN(1,terrainFogCol.GetBlueFloat()  * factor) );
	zrenderer->SetFogColor				(terrainFogCol);*/

	zCCamera::activeCam->SetFarClipZ	(resultFogFar+500);

	//
	zrenderer->SetPolySortMode			(zRND_SORT_ZBUFFER);
	zrenderer->SetZBufferWriteEnabled	(TRUE);
	zrenderer->SetCacheAlphaPolys		(cacheAlphaPolys);

	//
	if (lensFlarePos[VX]!=-1) 
	{
		const float fadeTime = 5.0f/1000.0f;
		zCLensFlareFX *sunFlare = (zCLensFlareFX*)(zCLensFlareFX::GetStaticClassDef()->SearchObject("ZSUN_FLARE"));

		if (!m_bSunVisible)
		{
			// ist der punkt nicht sichtbar, wird das zu rendernde alpha erst mal so lange kleiner, bis 
			// es auf null ist. das ist dann das echte zu rendernde alpha
			if (m_fFadeScale == 0) goto dontRenderSun;

			m_fFadeScale -= fadeTime * (ztimer.GetFrameTimeF());
			if (m_fFadeScale <0) m_fFadeScale = 0;
		}
		else 
		{
			// ist der punkt sichtbar, wird das zu rendernde alpha so lange grösser bis der endalpha
			// wert erreicht ist
			m_fFadeScale  += fadeTime * (ztimer.GetFrameTimeF());
			if (m_fFadeScale >1) m_fFadeScale = 1;
		}

		// LensFlare
		if (sunFlare)
		{
			sunFlare->SetAlpha			(zBYTE(lensFlareAlpha * m_fFadeScale * (zREAL(1.0F) - rainFX.outdoorRainFXWeight)));
			sunFlare->RenderLensFlares	(lensFlarePos);
		};
	};

dontRenderSun:
	zCCamera::activeCam->Activate		();

	//
	masterTimeLast = masterTime;
//	relightCtr++;
};

void zCSkyControler_Outdoor::ProcessRainFX()  
{
#ifdef GOTHIC_DEMO1
	void* ptr   = 0;
	*(int*) ptr = 0;
#endif

	if ( (!GetSkyEffectsEnabled()) || GetDontRain())
	{
		rainFX.outdoorRainFXWeight	= 0;
	} 
	else
	{
		//#ifndef zSKY_DEBUG_KEYS
		#if 1
			// Staerke des Effekts bestimmen
			if ((masterTime>=rainFX.timeStartRain) && (masterTime<=rainFX.timeStopRain))
			{
				const zREAL FADE_PERC			= zREAL(0.2F);
				const zREAL FADE_PERC_END		= zREAL(0.8F);
				const zREAL fraction			= (masterTime-rainFX.timeStartRain) / (rainFX.timeStopRain-rainFX.timeStartRain);
				if (fraction<FADE_PERC)			rainFX.outdoorRainFXWeight	= fraction / FADE_PERC;				else	// 0.2 => 20% der Regenzeit am Anfang und Ende ein/ausfaden
				if (fraction>FADE_PERC_END)		rainFX.outdoorRainFXWeight	= (-(fraction - 1.0f)) / FADE_PERC;	else
												rainFX.outdoorRainFXWeight	= 1;
				zERR_ASSERT (rainFX.outdoorRainFXWeight>=0);
				zERR_ASSERT (rainFX.outdoorRainFXWeight<=1);
			} else
				rainFX.outdoorRainFXWeight	= 0;
		#endif

		if ((rainFX.outdoorRainFXWeight<=0) && (!rainFX.outdoorRainFX->AreParticlesActive()))
		{
			// Effekt inaktiv
			rainFX.m_bRaining	= FALSE;
		}
		else
		{
			if (!rainFX.m_bRaining) 
			{
				rainFX.m_iRainCtr++;
				rainFX.m_bRaining = TRUE;
			};

			// Effekt definitiv aktiv
			zTRenderContext renderContext;
			renderContext.Clear				();
			renderContext.cam				= zCCamera::activeCam;
			renderContext.vob				= zCCamera::activeCam->GetVob();
			renderContext.world				= zCCamera::activeCam->GetVob()->GetHomeWorld();
			renderContext.cam->Activate();

			// SoundVolumen errechnen
			zREAL soundVolumeDest			= rainFX.outdoorRainFXWeight;
			if ((rainFX.camLocationHint!=zCAM_OUTSIDE_SECTOR) || (this->GetUnderwaterFX()))	
			{
				soundVolumeDest				*= 0.25F;
			}
			if (rainFX.soundVolume<soundVolumeDest)			
			{
				rainFX.soundVolume			+= ztimer.GetFrameTimeF() * zREAL(0.0005F);
			} 
			else if (rainFX.soundVolume>soundVolumeDest)			
			{
				rainFX.soundVolume			-= ztimer.GetFrameTimeF() * zREAL(0.0005F);
			};
			zClamp01						(rainFX.soundVolume);

			if (rainFX.camLocationHint==zCAM_INSIDE_SECTOR_CANT_SEE_OUTSIDE)
			{
				rainFX.timerInsideSectorCantSeeOutside	+= ztimer.GetFrameTimeF();
				if (rainFX.timerInsideSectorCantSeeOutside>zREAL(1000.0F))
				{
				};
			} 
			else
			{
				// zCAM_INSIDE_SECTOR_CAN_SEE_OUTSIDE, zCAM_OUTSIDE_SECTOR
				rainFX.timerInsideSectorCantSeeOutside	= 0;
			};

			//
			rainFX.outdoorRainFX->SetEffectWeight	(rainFX.outdoorRainFXWeight, rainFX.soundVolume);
			rainFX.outdoorRainFX->UpdateParticles	();

			rainFX.outdoorRainFX->CreateParticles	(renderContext);
			if (rainFX.camLocationHint!=zCAM_INSIDE_SECTOR_CANT_SEE_OUTSIDE)
			{
				const zCOLOR	dayLight	= GetDaylightColorFromIntensity(255);
				const zBYTE		intens		= dayLight.GetIntensityByte();
				zCOLOR			col			= zCOLOR(intens, intens, intens, 255);
				col.LerpRGB		(110, col, dayLight);
				rainFX.outdoorRainFX->RenderParticles	(renderContext, col);
			};
		}
	}

};

void zCSkyControler_Outdoor::SetRainFXWeight (zREAL weight, zREAL duration)
{
	if ((!GetSkyEffectsEnabled()) || GetDontRain()) return;
	zClamp01 (weight);
	zClamp01 (duration);
	
	rainFX.timeStartRain	= masterTime - (duration * weight);
	rainFX.timeStopRain		= masterTime + (duration * (1.0F-weight));
	rainFX.renderLightning	= (m_enuWeather==zTWEATHER_RAIN) ? zRandF()>0.7f : FALSE;
	zClamp01 (rainFX.timeStartRain);
	zClamp01 (rainFX.timeStopRain);
};


void zCSkyControler_Outdoor::RenderSetup() 
{
	zCOLOR fogCol;
	if (this->m_bOverrideColorFlag) fogCol = resultFogColorOverride;
	else							fogCol = resultFogColor;
	
	zrenderer->SetFogColor				(fogCol);
	ClearBackground						(fogCol);

	zrenderer->SetPolySortMode			(zRND_SORT_NONE);
	zrenderer->SetZBufferWriteEnabled	(FALSE);
};

void zCSkyControler_Outdoor::RenderSky() 
{

	zBOOL oldFog = zrenderer->GetFog();
	zrenderer->SetFog(FALSE);

	zBOOL   alternate   = zCWorld::S_GetAlternateRenderOrder();
	
	zCCamera *cam = zCCamera::activeCam;
	cam->Activate();
	cam->camMatrixInv.SetTranslation (0);
	cam->camMatrix = cam->camMatrixInv.InverseLinTrafo();

	if (!alternate) zrenderer->FlushPolys	();

	int rainCloudAlpha	= 2*zFloat2Int(rainFX.outdoorRainFXWeight*255);
	if (rainCloudAlpha>255) rainCloudAlpha=255;

	{
		skyLayer[0].RenderSkyLayer	(skyLayerState[0]);
		skyLayer[1].RenderSkyLayer	(skyLayerState[1]);
	}

	// RainCloud Layer
	if (rainCloudAlpha>0)
	{
		if (!alternate) zrenderer->FlushPolys	();

		zCOLOR layerColor;
		layerColor.SetRGB								(masterState.domeColor1);
		layerColor.SetAlphaByte							(rainCloudAlpha);
		this->skyLayerRainClouds.RenderRainCloudLayer	(layerColor);
	};

	if (!alternate) zrenderer->FlushPolys	();

	zrenderer->SetFog(oldFog);

};


void zCSkyControler_Outdoor::RenderSkyPost (const zBOOL renderSky)  
{ 
	// hier sind bereits gerendert: vobs und level polys ohne alpha kanal
	// alpha vobs und level alpha polys sind bereits im renderer sortiert vorhanden

	ProcessRainFX						();


	if (zCWorld::S_GetAlternateRenderOrder() & renderSky)
	{
		// Nebel fuer Sky setzen
		zREAL fn, ff;	zTRnd_FogMode	 oldFogMode;

		zCCamera	*cam = zCCamera::activeCam;

		zREAL oldFarClipZ = cam->GetFarClipZ();

		zrenderer->GetFogRange(fn, ff, oldFogMode);

		zrenderer->SetFogRange				(resultFogSkyNear, resultFogSkyFar, zRND_FOG_FALLOFF_LINEAR);

/*		zMAT4 oldInvMat = cam->camMatrixInv;

		cam->Activate		();		// FIXME: geht effizienter
		cam->camMatrixInv.SetTranslation	(0);
		cam->camMatrix		= cam->camMatrixInv.InverseLinTrafo();
		cam->camMatrixInv.GetTranslation	( zCCamera::activeCamPos );
		cam->SetUpFrustum					(); */
		cam->SetFarClipZ					(131072.0F);

		// Sky rendern
		RenderSky();	

		/*cam->camMatrixInv = oldInvMat;
		cam->camMatrix		= cam->camMatrixInv.InverseLinTrafo();
		cam->SetUpFrustum					(); 
*/
		zrenderer->SetFogRange				(fn, ff, zRND_FOG_FALLOFF_LINEAR);
		cam->SetFarClipZ(oldFarClipZ);

		//zrenderer->SetRenderMode(oldRenderMode);

		zrenderer->FlushPolys				();
	}

	zCSkyControler_Mid::RenderSkyPost	(renderSky);

#ifdef zSKY_DEBUG
	zSTRING t1, t2;

	if (this->skyLayer[0].skyMode == zSKY_MODE_POLY)
	{
		if (skyLayer[0].skyPoly->material->texture) t1 = skyLayer[0].skyPoly->material->texture->GetName();
		if (skyLayer[1].skyPoly->material->texture) t2 = skyLayer[1].skyPoly->material->texture->GetName();
	}
	else
	{
		if (skyLayer[0].skyDomeMesh->SharePoly(0)->material->texture) t1 = skyLayer[0].skyDomeMesh->SharePoly(0)->material->texture->GetName();
		if (skyLayer[1].skyDomeMesh->SharePoly(0)->material->texture) t2 = skyLayer[1].skyDomeMesh->SharePoly(0)->material->texture->GetName();
	}

	const int X = 5500;
	zREAL clock = masterTime*24 + 12;
	if (clock>24) clock -= 24;
	screen->Print (X,00, "time: "+zSTRING(masterTime,3));
	screen->Print (X,200, "hour: "+zSTRING(clock,3)+", "+stateList.GetNumInList());
	screen->Print (X,400, "cloud: "+zSTRING(cloudShadowScale,2));

	if (this->skyLayer[0].skyMode == zSKY_MODE_POLY)
	{
		screen->Print (X,600, zSTRING((int)skyLayer[0].skyPoly->material->GetAlpha())+", "+t1);
		screen->Print (X,800, zSTRING((int)skyLayer[1].skyPoly->material->GetAlpha())+", "+t2);
	}
	else 
	{
		screen->Print (X,600, zSTRING((int)skyLayer[0].skyDomeMesh->SharePoly(0)->material->GetAlpha())+", "+t1);
		screen->Print (X,800, zSTRING((int)skyLayer[1].skyDomeMesh->SharePoly(0)->material->GetAlpha())+", "+t2);
	}

	screen->Print (X,1000, "userFogFar: "+  zSTRING(userFogFar,2));
	screen->Print (X,1200, "fogNear/Far: "+ zSTRING(resultFogNear,2)+" ,");
	screen->Print (X+1600,1200,				zSTRING(resultFogFar,2));
	screen->Print (X,1400, "skyNear/Far: "+ zSTRING(resultFogSkyNear,2)+" ,");
	screen->Print (X+1600,1400,				zSTRING(resultFogSkyFar,2));
	screen->Print (X,1600, "fogTimeSc: "+  zSTRING(masterState.fogDist,2));

	screen->Print (X,2000, "rainFXWeight: "+  zSTRING(rainFX.outdoorRainFXWeight,2));
	screen->Print (X,2200, "rainFXStart: "+  zSTRING(rainFX.timeStartRain,2));
	screen->Print (X,2400, "rainFXStop: "+  zSTRING(rainFX.timeStopRain,2)); 
	screen->Print (X,3000, "dayCtr: "+  zSTRING(this->dayCounter,2));
#endif 
	m_bSkyScaleChanged = FALSE;
};

void zCSkyControler_Outdoor::Archive (zCArchiver &arc)
{
	//
	zCSkyControler_Mid::Archive (arc);

	//
	if (arc.InSaveGame())
	{
		arc.WriteFloat			("masterTime",		this->masterTime);
		arc.WriteFloat			("rainWeight",		rainFX.outdoorRainFXWeight);
		arc.WriteFloat			("rainStart",		rainFX.timeStartRain);
		arc.WriteFloat			("rainStop",		rainFX.timeStopRain);
		arc.WriteFloat			("rainSctTimer",	rainFX.timerInsideSectorCantSeeOutside);
		arc.WriteFloat			("rainSndVol",		rainFX.soundVolume);
		arc.WriteFloat			("dayCtr",			dayCounter); 
		arc.WriteFloat			("fadeScale",		this->m_fFadeScale); 
		arc.WriteBool			("renderLightning",	rainFX.renderLightning); 
		arc.WriteBool			("isRaining		 ",	rainFX.m_bRaining); 
		arc.WriteInt			("rainCtr		 ",	rainFX.m_iRainCtr); 
	};
};

void zCSkyControler_Outdoor::Unarchive (zCArchiver &arc)
{
	//
	zCSkyControler_Mid::Unarchive (arc);

	//
	if (arc.InSaveGame())
	{
		arc.ReadFloat			("masterTime",		this->masterTime);
		arc.ReadFloat			("rainWeight",		rainFX.outdoorRainFXWeight);
		arc.ReadFloat			("rainStart",		rainFX.timeStartRain);
		arc.ReadFloat			("rainStop",		rainFX.timeStopRain);
		arc.ReadFloat			("rainSctTimer",	rainFX.timerInsideSectorCantSeeOutside);
		arc.ReadFloat			("rainSndVol",		rainFX.soundVolume);
		arc.ReadFloat			("dayCtr",			dayCounter); 
		arc.ReadFloat			("fadeScale",		this->m_fFadeScale); 
		arc.ReadBool			("renderLightning",	rainFX.renderLightning); 
		arc.ReadBool			("isRaining		 ",	rainFX.m_bRaining); 
		arc.ReadInt				("rainCtr		 ",	rainFX.m_iRainCtr); 
	};
};


void	zCSkyControler_Outdoor::SetWeatherType	(const zTWeather		 a_weather)
{
	if (a_weather==this->m_enuWeather) return;
	// das wetter soll sich ändern
	// regnet oder schneit es bereits ?
	if (rainFX.outdoorRainFXWeight>0)
	{
		// solange es bereits schneit oder regnet, kein wechsel des wetters
		return;
	}
	else
	{
		// nein es regnet/schneit noch nicht
		// soll es denn anfangen zu schneien ?
		if (a_weather == zTWEATHER_SNOW)
		{
			// ja, also dann
			this->SetRainFXWeight(0,0.1f);
		}
	}

	m_enuWeather = a_weather;

	rainFX.outdoorRainFX->SetWeatherType(m_enuWeather);

};

