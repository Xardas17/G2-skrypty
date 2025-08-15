#include "zsky.h"

/******************************************************************************** 
 
     $Workfile:: zSky_Outdoor.h       $                $Date:: 19.03.01 21:29   $
     $Revision:: 21                   $             $Modtime:: 19.03.01 21:19   $
        Author:: EDENFELD
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Sky/Weather/Day/Night/Ambient effects
   created       : 28.1.99

 * $Log: /current_work/zengin/_Dieter/zSky.h $
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Edenfeld
/// @version $Revision: 21 $ ($Modtime: 19.03.01 21:19 $)


#ifndef __ZSKY_OUTDOOR_H__
#define __ZSKY_OUTDOOR_H__

#ifndef __ZRENDERMANAGER_H__
#include "zRenderManager.H"
#endif

#ifndef __ZSOUND_H__
#include "zSound.H"
#endif


class zCOutdoorRainFX;

// ===========================================================================================

enum zESkyLayerMode { zSKY_MODE_POLY, zSKY_MODE_BOX };

const int zSKY_NUM_LAYER = 2;

class zCSkyLayerData {
public:
	zESkyLayerMode	skyMode;
	zCTexture		*tex;
	zSTRING			texName;
	zREAL			texAlpha;
	zREAL			texScale;
	zVEC2			texSpeed;
	zCSkyLayerData();
	~zCSkyLayerData();
};

enum zTSkyStateEffect {
	zSKY_STATE_EFFECT_SUN,
	zSKY_STATE_EFFECT_CLOUDSHADOW,
};

class zCSkyState {
public:
	zREAL			time;
	zVEC3			polyColor;
	zVEC3			fogColor;
	zVEC3			domeColor1;
	zVEC3			domeColor0;
	zREAL			fogDist;
	zBOOL			sunOn;
	int				cloudShadowOn;
	zCSkyLayerData	layer[zSKY_NUM_LAYER];

	zCSkyState();
	~zCSkyState();
	void			PresetDay0			();
	void			PresetDay1			();
	void			PresetDay2			();
	void			PresetEvening		();
	void			PresetNight0		();
	void			PresetNight1		();
	void			PresetNight2		();
	void			PresetDawn			();
};

// ===========================================================================================

class zCSkyLayer {
public:
	zCMesh*			skyPolyMesh;
	zCPolygon*		skyPoly;
	zVEC2			skyTexOffs;
	zCMesh*			skyDomeMesh;
	zESkyLayerMode	skyMode;

	 zCSkyLayer();
	~zCSkyLayer();
	int				GetAlpha				()					{ return skyPoly->GetMaterial()->GetAlpha();};
	void			SetAlpha				(const int alpha)	{ skyPoly->GetMaterial()->SetAlpha	(alpha);};
	void			SetSkyPolyTexture		(zCTexture* tex);
	void			SetSkyDomeTexture		(zCTexture *tex);
	void			RenderSkyLayer			(zCSkyState* skyLayerState);
	void			RenderRainCloudLayer	(zCOLOR layerColor);
	void			SetDomeMeshEnabled		(const zBOOL m_bEnableSkyDome);
	
public:
	void			RenderSkyPoly			(zCSkyState* skyLayerState);
	void			RenderSkyDome			(zCSkyState* skyLayerState);

	static zCMesh*	CreateSkyDomeMesh       ();
	static zCMesh*	CreateSkyPoly			();

private:
	void			ColorizeSkyDome			();

};

// ===========================================================================================

class zCSkyPlanet {
public:
	zCMesh					*mesh;
	zVEC4					color0;
	zVEC4					color1;
	zREAL					size;
	zVEC3					pos;
	zVEC3					rotAxis;

	zCSkyPlanet() {
		mesh = 0;
	};
	~zCSkyPlanet() {
		zRELEASE (mesh);
	};
};



class zCSkyControler_Outdoor : public zCSkyControler_Mid {
	zCLASS_DECLARATION	(zCSkyControler_Outdoor)
public:

	// zCSkyControler Interface
			 zCSkyControler_Outdoor(zBOOL useDomeMesh = FALSE);
	virtual ~zCSkyControler_Outdoor();
	virtual void				SetTime					(const zREAL time);
	virtual zREAL				GetTime					() const			{ return masterTime; };
	virtual void				ResetTime				();
	virtual void				SetFarZ					(const zREAL z);
	virtual zREAL				GetFarZ					() const;
	virtual void				SetFarZScalability		(const zREAL zscale);		// clipping plane and fog, performance/scalability modificator (thru performance settings)
	virtual zREAL				GetFarZScalability		() const;
	virtual void				SetBackgroundColor		(const zCOLOR col)	{};		// == clear color == fog color
	virtual zCOLOR				GetBackgroundColor		() const			{ if (m_bOverrideColorFlag) return resultFogColorOverride; else return resultFogColor; };
	virtual zCOLOR				GetBackgroundColorDef	() const			{ return resultFogColor; };
	virtual void				SetOverrideColor		(const zVEC3 col)	{ m_overrideColor= col;	 };
	virtual void				SetOverrideColorFlag	(const zBOOL b)		{ m_bOverrideColorFlag = b; };
	virtual zREAL				GetCloudShadowScale		()const;
	virtual void				SetCloudShadowScale		(const zREAL f);
	virtual	zBOOL				GetGlobalWindVec		(zVEC3 &resVec, const zTAnimationMode a_aniMode );
	virtual void				UpdateWorldDependencies ();
	virtual void				SetWeatherType			(const zTWeather		 a_weather);
	virtual zBOOL				GetRenderLightning		() const			{ return rainFX.renderLightning;	};
								
//	void						LightClippedPoly		(zCPolygon* poly);

	zCOLOR						GetDaylightColorFromIntensity(int intensity);
	void						RenderSkyPre			();
	void						RenderSkyPost			(const zBOOL b);

	void						SetCameraLocationHint	(const zTCamLocationHint camLocHint) { rainFX.camLocationHint = camLocHint; };
	zTCamLocationHint			GetCameraLocationHint	() const							 { return rainFX.camLocationHint;		};
	zBOOL						GetCameraInsideSector	() const							 { return rainFX.camLocationHint != zCAM_OUTSIDE_SECTOR;	};
	void						SetRainFXWeight			(zREAL weight, zREAL duration);
	zREAL						GetRainFXWeight			() const							 { return rainFX.outdoorRainFXWeight;	};
	zCMesh*						GetSkyDomeMesh			() const							 { return skyLayer[1].skyDomeMesh;		};
	zREAL						GetEffectVolume			() const							 { return rainFX.soundVolume;			};
	void						SetGlobalSkyScale		(const zREAL skyScale);
	zREAL						GetGlobalSkyScale		() const							 { return m_fSkyScale;					};
	zBOOL						GetGlobalSkyScaleChanged() const							 { return m_bSkyScaleChanged;			};
	void						SetDontRain				(const zBOOL b)						 { m_bDontRain = b;						};
	zBOOL						GetDontRain				() const							 { return m_bDontRain;					};
	zBOOL						GetLevelChanged			() const							 { return m_bLevelChanged;				};
	void						SetLevelChanged			(const zBOOL b)						 { m_bLevelChanged = b;					};
	zBOOL						GetDarkSky				() const							 { return m_bDarkSky;					};
	void						SetDarkSky				(const zBOOL b)						 { m_bDarkSky = b;						};

	//							
	friend zCSkyLayer;			

protected:

	// zCObject Interface
	// persistance
	virtual void				Archive					(zCArchiver &arc);
	virtual void				Unarchive				(zCArchiver &arc);
	
private:						
	zBOOL						initDone;
	zREAL						masterTime;
	zREAL						masterTimeLast;
	zCSkyState					masterState;
	zCSkyState*					state0;
	zCSkyState*					state1;
	zCArray<zCSkyState*>		stateList;
	zCOLOR						polyLightCLUT[256];
	zREAL						dayCounter;				// is increased every wrapping from over 1 to zero
	zCArray<zVEC3>				fogColorDayVariations;
	zCArray<zVEC3>				fogColorDayVariations2;
	zREAL						m_fSkyScale;
	zBOOL						m_bSkyScaleChanged;
	zVEC3						m_overrideColor;
	zBOOL						m_bOverrideColorFlag;
	zBOOL						m_bDontRain;
	zBOOL						m_bLevelChanged;
	zBOOL						m_bDarkSky;	

								
	// fog/clip range			
	zREAL						resultFogScale;
	zREAL						heightFogMinY;
	zREAL						heightFogMaxY;
	zREAL						userFogFar;
	zREAL						resultFogNear;
	zREAL						resultFogFar;
	zREAL						resultFogSkyNear;
	zREAL						resultFogSkyFar;
	zCOLOR						resultFogColor;
	zCOLOR						resultFogColorOverride;
	zREAL						userFarZScalability;
								
	zCSkyState*					skyLayerState[2];
	zCSkyLayer					skyLayer[2];
	zCSkyLayer					skyLayerRainClouds;
	zCTexture*					skyCloudLayerTex;


	// planets
	enum { NUM_PLANETS = 2 };
	zCSkyPlanet					planets[NUM_PLANETS];
	zBOOL						m_bSunVisible;
	zREAL						m_fFadeScale;
								
	// sky-pfx					
	zCVob						*vobSkyPFX;
	zREAL						skyPFXTimer;

	// wind
	zBOOL						m_bIsMainControler;				// only one global instance has skydomes, wind etc.
	zVEC3						m_bWindVec;

	//
	struct zTRainFX {
		zCOutdoorRainFX			*outdoorRainFX;
		zTCamLocationHint		camLocationHint;
		zREAL					outdoorRainFXWeight;				// 0..1
		zREAL					soundVolume;						// 0..1
		zREAL					timerInsideSectorCantSeeOutside;	// msec
		zREAL					timeStartRain;
		zREAL					timeStopRain;
		zBOOL					renderLightning;
		zBOOL					m_bRaining;							// wird nur einmal zu regenstart auf true gesetzt
		int						m_iRainCtr;							// wie oft hat es bisher geregnet ?

	} rainFX;
								
	void						Init ();
								
	void						RenderPlanets			(const zREAL depth);
	void						RenderSetup				();
	void						RenderSky				();
	void						RenderSkyPFX			();
								
	void						InitSkyPFX				();
	void						CalcFog					();
								
	void						CalcPolyLightCLUT		(const zVEC3& col0, const zVEC3& col1);
	void						CloudShadowPoly			(zCPolygon* poly);
	void		 				CreateDefault			();
	void						Interpolate				();
//	zCTexture*					GetStateTexture			(int i, int channel);
	int							GetStateTextureSearch	(int i, int channel, zBOOL forward);
	void						ApplyStateTexToLayer	(int i, int channel);
	void						ProcessRainFX			();
	void						ReadFogColorsFromINI	();
	void	zCCFASTCALL			ApplyFogColorsFromINI	(int varNr);
	void						CalcGlobalWind			();
};


class zCOutdoorRainFX 
{
public:
	 zCOutdoorRainFX();
	~zCOutdoorRainFX();

	//
	void					SetEffectWeight			(const zREAL weight, const zREAL soundVolume);	// range: 0..1
	zREAL					GetEffectWeight			() const				{ return m_effectWeight; };

	void					SetWeatherType			(const zTWeather		 a_weather);
													
	//												
	void					CreateParticles			(zTRenderContext &renderContext);
	void					UpdateParticles			();
	void					RenderParticles			(zTRenderContext &renderContext, zCOLOR lightColor);

	zBOOL					AreParticlesActive		() const { return ((m_numImpactParticle>0) && (m_numFlyParticle<=0)); };

private:
	enum					{ zEFFECT_BOX_SIDES	= 2500	};
	enum					{ zEFFECT_BOX_HEIGHT	= 1000	};
	enum					{ zMAX_FLY_PARTICLE		= 1024	};
	enum					{ zMAX_IMPACT_PARTICLE	= 1024	};
	enum					{ zCACHE_SIZE			= 512	};		// POW2 !
	struct zSParticle		{
		zREAL				m_killTotalTime;		// 0..1, 99+++
		zPOINT3				m_destPosition;
		zVEC3				m_destNormal;

		zBOOL				IsActive				() const	{ return (m_killTotalTime<=1);	};
		void				SetInactive				()			{ m_killTotalTime=99;			};
		void				SetInFreeList			()			{ m_killTotalTime=100;			};
		zBOOL				IsInFreeList			() const	{ return (m_killTotalTime>=100);};
	};
	zSParticle				m_flyParticleList		[zMAX_FLY_PARTICLE];
	zSParticle				m_impactParticleList	[zMAX_IMPACT_PARTICLE];
	int						m_numFlyParticle;
	int						m_numImpactParticle;
	zCArray<zSParticle*>	m_freeFlyParticleList;

	zREAL					m_effectWeight;			// 0..1
	int						m_numDestFlyParticle;		
	zPOINT3					m_camPosLastFrame;
	zTWeather				m_enuWeather;

	//
	struct zSCacheElement
	{
		zPOINT3				m_position;
		zVEC3				m_normal;
	};
	zSCacheElement			m_cache[zCACHE_SIZE];
	int						m_currentCacheIndex;

	// render
	zCShader				m_shader;
	zCShaderStage			m_shaderStage;
	zCTexture*				m_raindropTexture;
	zCTexture*				m_rainTexture;
	zCMaterial*				m_rainMaterial;

	// sound
	zCSoundFX*				m_soundEffect;
	zTSoundHandle			m_soundHandle;
	zBOOL					m_soundActive;

	// const config
	zVEC3					m_positionUpdateVector;
	zREAL					m_velocityLen;
	zREAL					m_timeLen;

	void					UpdateSound				(const zREAL soundVolume);
	zBOOL					CheckCameraBeam			(const zVEC3& camPosDelta);
	inline zBOOL			IsInEffectBox			(const zPOINT3& posRel)
	{
		const zREAL zEFFECT_BOX_SIDES_SMALL		= zEFFECT_BOX_SIDES * zREAL(0.7F);
		const zREAL zEFFECT_BOX_HEIGHT_SMALL	= zEFFECT_BOX_HEIGHT* zREAL(0.8F);

		return ((posRel[VX]<= zEFFECT_BOX_SIDES_SMALL)	&&
				(posRel[VX]>=-zEFFECT_BOX_SIDES_SMALL)	&&
				(posRel[VY]<= zEFFECT_BOX_HEIGHT_SMALL)	&&
				(posRel[VY]>=-zEFFECT_BOX_HEIGHT_SMALL)	&&
				(posRel[VZ]<= zEFFECT_BOX_SIDES_SMALL)	&&
				(posRel[VZ]>=-zEFFECT_BOX_SIDES_SMALL));
	};
};

#endif