/******************************************************************************** 
 
     $Workfile:: zSky.h               $                $Date:: 19.03.01 21:29   $
     $Revision:: 21                   $             $Modtime:: 19.03.01 21:19   $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Sky/Weather/Day/Night/Ambient effects
   created       : 28.1.99

 * $Log: /current_work/zengin/_Dieter/zSky.h $
 * 
 * 21    19.03.01 21:29 Edenfeld
 * Demo Kastration einfacher/rückgängig gemacht. 
 * 
 * 20    18.03.01 18:49 Edenfeld
 * Demo Geschichten
 * 
 * 19    13.03.01 18:04 Hildebrandt
 * 
 * 18    15.02.01 3:40 Hildebrandt
 * 
 * 17    14.02.01 7:28 Hildebrandt
 * 
 * 16    29.01.01 17:51 Hildebrandt
 * 
 * 15    25.01.01 1:21 Hildebrandt
 *  
 * 14    23.01.01 21:00 Hildebrandt
 * 
 * 13    11.01.01 18:46 Hildebrandt
 * 
 * 12    4.12.00 17:48 Hildebrandt
 * 
 * 11    3.11.00 16:49 Hildebrandt
 * 
 * 10    6.10.00 19:26 Hildebrandt
 * 
 * 9     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 8     6.07.00 13:45 Hildebrandt
 * 
 * 5     8.05.00 2:17 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 6     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 4     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 3     16.11.99 19:50 Hildebrandt
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 21 $ ($Modtime: 19.03.01 21:19 $)


#ifndef __ZSKY_H__
#define __ZSKY_H__


#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

#ifndef __ZPARTICLE_H__
#include <zParticle.h>
#endif

class zCSkyControler;
class zCSkyControler_Mid;
class zCSkyControler_Indoor;
class zCSkyControler_Outdoor;

// ===========================================================================================

class zCUnderwaterPFX : public zCParticleFX {
public:
	virtual zBOOL				Render				(zTRenderContext& renderContext);			// TRUE=visible, FALSE=not visible

	void						CreateParticles		();
private:
	zPOINT3						camPosLastFrame;

	void						ProcessParticles	();
	friend zCSkyControler_Mid;
};

// ===========================================================================================

enum zTWeather
{
	zTWEATHER_SNOW,
	zTWEATHER_RAIN
};



class zCSkyControler : public zCObject {
	zCLASS_DECLARATION	(zCSkyControler)
public:
	static void					SetSkyEffectsEnabled	(const zBOOL b)	{ s_skyEffectsEnabled = b;			};
	static zBOOL				GetSkyEffectsEnabled	() 				{ return s_skyEffectsEnabled;		};
	static zCSkyControler*		GetActiveSkyControler	()				{ return s_activeSkyControler;		};
	void						Activate				()				{ s_activeSkyControler = this;		};

			 zCSkyControler();
	virtual ~zCSkyControler();

	virtual void				SetTime					(const zREAL time)	=0;		// 0..1 (0=12h, 0.5=24h)
	virtual zREAL				GetTime					() const			=0;
	virtual void				ResetTime				()					=0;		// sets time/mastertime to zero internaly and clears up dependent internal states
	virtual void				SetFarZ					(const zREAL z)		=0;		// clipping plane and fog, data-driven, artists tune this for specific levels
	virtual zREAL				GetFarZ					() const			=0;
	virtual void				SetFarZScalability		(const zREAL zscale)=0;		// [0..1..2] clipping plane and fog, performance/scalability modificator (thru performance settings)
	virtual zREAL				GetFarZScalability		() const			=0;
	virtual void				SetBackgroundColor		(const zCOLOR col)	=0;		// == clear color == fog color
	virtual zCOLOR				GetBackgroundColor		() const			=0;
	virtual zCOLOR				GetBackgroundColorDef	() const			=0;
	virtual void				SetOverrideColor		(const zVEC3 col)	=0;		// == clear color == fog color
	virtual void				SetOverrideColorFlag	(const zBOOL b)		=0;
	virtual zREAL				GetCloudShadowScale		()const				{ return 0;	};
	virtual void				SetCloudShadowScale		(const zREAL f)		{};
	virtual void				SetFillBackground		(const zBOOL b)		{ fillBackground=b;			};	// true= fills background with fog-color/sky/backdrop whatever & initializes zbuffer, false= only zbuffer is initialized
	virtual zBOOL				GetFillBackground		() const			{ return fillBackground;	};
	virtual void				SetUnderwaterFX			(const zBOOL b)		=0;
	virtual zBOOL				GetUnderwaterFX			() const			=0;
	virtual void				UpdateWorldDependencies ()					=0;		// call, when the static world changes
	virtual void				SetLightDirty			()					{ relightCtr++; };
	virtual void				SetRelightTime			(const zREAL a_fLightPerfCtr)	{ m_fRelightTime = a_fLightPerfCtr; };

//	virtual void				LightClippedPoly		(zCPolygon* poly)	=0;

	virtual zTFrameCtr			GetRelightCtr			() { return relightCtr; };		// is incremented each time the world should update it's lighting 
	virtual zCOLOR				GetDaylightColorFromIntensity(int intensity) { return zCOLOR(intensity,intensity,intensity,255); };		// intensity 0..255
	virtual void				RenderSkyPre			()					=0;
	virtual void				RenderSkyPost			(const zBOOL renderSkyMesh)=0;
	virtual	zBOOL				GetGlobalWindVec		(zVEC3 &resVec, const zTAnimationMode a_aniMode ) { return FALSE; };
	virtual void				SetGlobalSkyScale		(const zREAL skyScale)				 {};
	virtual zREAL				GetGlobalSkyScale		() const							 { return 0;					};
	virtual zBOOL				GetGlobalSkyScaleChanged() const							 { return FALSE;				};

			zBOOL				GetColorChanged			()	const										  { return m_bColorChanged;	};
			void				SetColorChanged			(const zBOOL a_bChanged)						  { m_bColorChanged = a_bChanged; };
			
	//
	enum zTCamLocationHint {
		zCAM_OUTSIDE_SECTOR,
		zCAM_INSIDE_SECTOR_CANT_SEE_OUTSIDE,
		zCAM_INSIDE_SECTOR_CAN_SEE_OUTSIDE,
	};
	virtual void				SetCameraLocationHint	(const zTCamLocationHint camLocHint) {}
	virtual void				SetWeatherType			(const zTWeather		 a_weather)	 { m_enuWeather = a_weather;	};
	virtual zTWeather			GetWeatherType			()	const							 { return m_enuWeather ;		};


	// for daylight dependent outdoor poly lighting
	zCOLOR						*polyLightCLUTPtr;
	zREAL						cloudShadowScale;
	zBOOL						m_bColorChanged;
	zTWeather					m_enuWeather;

protected:
	static zCSkyControler*		s_activeSkyControler;
	static zBOOL				s_skyEffectsEnabled;
	zCOLOR						backgroundColor;
	zBOOL						fillBackground;
	zCTexture*					backgroundTexture;
	zTFrameCtr					relightCtr;
	zREAL						lastRelightTime;
	zREAL						m_fRelightTime;

	void						ClearBackground			(zCOLOR color);
};


// ===========================================================================================

// this class implements underwater effects

class zCSkyControler_Mid : public zCSkyControler {
	zCLASS_DECLARATION	(zCSkyControler_Mid)
public:
			 zCSkyControler_Mid();
	virtual ~zCSkyControler_Mid();

	void						SetUnderwaterFX			(const zBOOL b);
	zBOOL						GetUnderwaterFX			() const;
	virtual void				RenderSkyPre			();
	virtual void				RenderSkyPost			(const zBOOL b);

	//
	void						InitScreenBlend			();
	void						RenderScreenBlend		();
	void						SetScreenBlendAlpha		(int s);					// 0..255
	void						SetScreenBlendColor		(const zCOLOR& col);
	void						SetScreenBlendAlphaFunc (const zTRnd_AlphaBlendFunc alphaFunc);

	//
	zCOLOR						GetUnderwaterColor		() const			{ return underwaterColor;	};
	void						SetUnderwaterColor		(const zCOLOR col)	{ underwaterColor=col;		};
	zREAL						GetUnderwaterFarZ		() const			{ return underwaterFarZ;	};
	void						SetUnderwaterFarZ		(const zCOLOR col)	{ underwaterFarZ;			};

private:
	zBOOL						underwaterFX;
	zCOLOR						underwaterColor;
	zREAL						underwaterFarZ;

	zREAL						underwaterStartTime;
	zREAL						oldFovX;
	zREAL						oldFovY;

	// 
	zCVob						*vobUnderwaterPFX;

	zCPolygon					*scrPoly;
	zCMesh						*scrPolyMesh;
	int							scrPolyAlpha;
	zCOLOR						scrPolyColor;
	zTRnd_AlphaBlendFunc		scrPolyAlphaFunc;

	void						InitUnderwaterPFX		();

};

// ===========================================================================================

class zCSkyControler_Indoor : public zCSkyControler_Mid {
	zCLASS_DECLARATION	(zCSkyControler_Indoor)
public:
			 zCSkyControler_Indoor();
	virtual ~zCSkyControler_Indoor()	{};

	virtual void				SetTime					(const zREAL time);
	virtual zREAL				GetTime					() const			{ return time;			};
	virtual void				ResetTime				()					{ this->SetTime (0);	};
	virtual void				SetFarZ					(const zREAL z);
	virtual zREAL				GetFarZ					() const;
	virtual void				SetFarZScalability		(const zREAL zscale);		// clipping plane and fog, performance/scalability modificator (thru performance settings)
	virtual zREAL				GetFarZScalability		() const;
	virtual void				SetBackgroundColor		(const zCOLOR col);	
	virtual zCOLOR				GetBackgroundColor		() const;
	virtual	zCOLOR				GetBackgroundColorDef	() const;		
	virtual void				SetOverrideColor		(const zVEC3 col)	{};
	virtual void				SetOverrideColorFlag	(const zBOOL b)		{};
	virtual void				UpdateWorldDependencies ()					{};

//	virtual void				LightClippedPoly		(zCPolygon* poly)	{};

	virtual void				RenderSkyPre			();
	virtual void				RenderSkyPost			(const zBOOL b);
private:
	zREAL						userFarZ;
	zREAL						userFarZScalability;
	zREAL						time;
};


#ifndef __ZSKY_OUTDOOR_H__
#include <zSky_OutDoor.h>
#endif



// ===========================================================================================





// ===========================================================================================


#endif 