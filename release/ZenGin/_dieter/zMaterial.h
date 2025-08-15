/******************************************************************************** 
 
     $Workfile:: zMaterial.h          $                $Date:: 14.02.01 7:28    $
     $Revision:: 18                   $             $Modtime:: 14.02.01 3:46    $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Material and Texture classes, used by Polygons
   created       : 30.7.97

 * $Log: /current_work/zengin_work/_Dieter/zMaterial.h $
 * 
 * 18    14.02.01 7:28 Hildebrandt
 * 
 * 17    12.02.01 17:51 Hildebrandt
 * 
 * 16    8.02.01 21:39 Hildebrandt
 * 
 * 15    17.01.01 19:20 Hildebrandt
 * 
 * 14    10.01.01 17:33 Hildebrandt
 * 
 * 13    4.12.00 17:44 Hildebrandt
 * 
 * 12    3.11.00 18:38 Hildebrandt
 * 
 * 11    11.10.00 19:45 Hildebrandt
 * 
 * 10    21.08.00 17:18 Hildebrandt
 * 
 * 9     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 8     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 10    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 8     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 7     12/09/99 10:02p Hildebrandt
 * temporary: made zCTexture cacheIn/Out virtual
 * 
 * 6     12/08/99 7:49p Hildebrandt
 * new commandline param: "-zNoTex" => no textures are loaded
 * 
 * 4     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 18 $ ($Modtime: 14.02.01 3:46 $)

// =======================================================================================================================

#ifndef __ZMATERIAL_H__
#define __ZMATERIAL_H__


#ifndef __ZOBJECT_H__
#include <zObject.h>
#endif

#ifndef __ZTYPES3D_H__
#include <zTypes3D.h>
#endif

#ifndef __ZSTRING_H__
#include <zString.h>
#endif

#ifndef __ZRENDERER_H__
#include <zRenderer.h>
#endif

#ifndef __ZTEXTURE_H__
#include <zTexture.h>
#endif

#ifndef __ZFFT_H__
#include <zFFT.H>
#endif

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4305 ) 

#ifdef COMPILING_SPACER
extern zBOOL g_bIsPlayingGame;
#endif

// =======================================================================================================================

class zCPolygon;		// z3d.h
class zCBspSector;		// zbsp.h

///////////////////////////////////////////////////////////////////////////
//     Texture Ani Controler
///////////////////////////////////////////////////////////////////////////

class zENGINE_API zCTexAniCtrl {
private:
	//	v = s / t
	//	s = v * t
	static zDWORD masterFrameCtr;
	int			aniChannel;
	zREAL		actFrame;
	zREAL		aniFPS;
	zDWORD		frameCtr;
	zBOOL		bOneShotAni;

public:
	zCTexAniCtrl();
	void		SetAniFPS			(const zREAL fps)	{ aniFPS = fps / 1000.0F;	};
	zREAL		GetAniFPS			() const			{ return aniFPS * 1000.0F;	};
	zREAL		GetActFrame			() const			{ return actFrame;			};
	void		SetActFrame			(const zREAL f)	{ actFrame=f;				};
	void		SetAniChannel		(const int c)		{ aniChannel = c;			};
	int			GetAniChannel		() const			{ return aniChannel;		};
	void		SetOneShotAni		(const zBOOL b)		{ bOneShotAni=b;			};
	zBOOL		GetOneShotAni		() const			{ return bOneShotAni;		};
	void		AdvanceAni			(zCTexture *tex);
	static void IncMasterFrameCtr	()					{ masterFrameCtr++;			};
};


///////////////////////////////////////////////////////////////////////////
//     Material
///////////////////////////////////////////////////////////////////////////

enum zTMat_Group {	zMAT_GROUP_UNDEF	= 0	, 
					zMAT_GROUP_METAL		, 
					zMAT_GROUP_STONE		, 
					zMAT_GROUP_WOOD			, 
					zMAT_GROUP_EARTH		, 
					zMAT_GROUP_WATER		,
					zMAT_GROUP_SNOW			,
					zMAT_NUM_MAT_GROUP
}; // ATT: s_MatGroupStrings in zMaterial.cpp has to be kept in sync

enum zTWaveAniMode
{
	zWAVEANI_NONE = 0,
	zWAVEANI_GROUND_AMBIENT,
	zWAVEANI_GROUND,
	zWAVEANI_WALL_AMBIENT,
	zWAVEANI_WALL,
	zWAVEANI_ENV,
	zWAVEANI_WIND_AMBIENT,
	zWAVEANI_WIND
};

class zENGINE_API zCMaterial : public zCObject {
	zCLASS_DECLARATION (zCMaterial)
public:
	// methods
	zCMaterial();
	zCMaterial(const zSTRING& name);

	zCMaterial(const zCMaterial&);					// copy-ctor
	zCMaterial& operator=(const zCMaterial&);		// 
	
	zCBspSector*			GetBspSectorFront	() const					{ return bspSectorFront;	};
	void					SetBspSectorFront	(zCBspSector *sector)		{ bspSectorFront = sector;	};
	zCBspSector*			GetBspSectorBack	() const					{ return bspSectorBack;		};
	void					SetBspSectorBack	(zCBspSector *sector)		{ bspSectorBack = sector;	};
	// for tools			
	zPOINT2					GetTexScale			();
	void					SetTexScale			(const zPOINT2 s);
	void					SetLibFlag			(const zBYTE flag)			{ libFlag=flag;				};
	zBYTE					GetLibFlag			() const					{ return libFlag;			};
	enum					{ zMAT_USAGE_LEVEL, zMAT_USAGE_OTHER };
	void					SetUsage			(const zBYTE usage)			{ matUsage = usage;			};
	void					SetUsageFromDefault	()							{ matUsage = s_matUsageDefault; };
	zBYTE					GetUsage			() const					{ return matUsage;			};
	static void				SetUsageDefault		(const zBYTE usage)			{ s_matUsageDefault = usage;};
	static zBYTE			GetUsageDefault		()							{ return s_matUsageDefault; };
	zTMat_Group				GetMatGroup			() const					{ return matGroup;			};
	void					SetMatGroup			(const zTMat_Group group)	{ matGroup = group;			};
	const zSTRING&			GetMatGroupString	() const;
	void					SetMatGroupByString	(const zSTRING& s);
	static const zSTRING&	GetMatGroupString	(const zTMat_Group group); 

	// environmental mapping
	void					SetEnvMapStrength   (const zREAL a_bEnvMapStr)	{ m_bEnvironmentalMappingStrength = a_bEnvMapStr;};
	zREAL					GetEnvMapStrength   ()	const					{ return m_bEnvironmentalMappingStrength;};
	zBOOL					GetEnvMapEnabled	() const					{ return m_bEnvironmentalMapping;		 };
	void					SetEnvMapEnabled	(const zBOOL a_bEnEnvMap)	{ m_bEnvironmentalMapping = a_bEnEnvMap; };

	// fft transform
	void					SetWaveMaxAmplitude (const float a_fWaveMaxAmp)	{ m_fWaveMaxAmplitude= a_fWaveMaxAmp;	 };
	float					GetWaveMaxAmplitude ()	const					{ return m_fWaveMaxAmplitude;			 };
	void					SetWaveGridSize		(const float a_fWaveSize)	{ m_fWaveGridSize = a_fWaveSize;		 };
	float					GetWaveGridSize		()	const					{ return m_fWaveGridSize ;				 };
	zTWaveAniMode			GetWaveAniMode		()  const					{ return m_enuWaveMode;					 };
	void					SetWaveAniMode		(const zTWaveAniMode a_enuWaveMode)	{ m_enuWaveMode = a_enuWaveMode; };
	zTFFT					GetWaveAniSpeed()   const						{ return m_enuWaveSpeed;				 };
	void					SetWaveAniSpeed     (const zTFFT a_enuWaveSpeed){ m_enuWaveSpeed = a_enuWaveSpeed; };

	// sunlight ignore
	zBOOL					GetIgnoreSunLight	() const					{ return m_bIgnoreSun;					 };
	void					SetIgnoreSunLight	(const zBOOL a_bIgnoreSun)	{ m_bIgnoreSun = a_bIgnoreSun;			 };

	// Phong-Reflection
	void					SetAmbient			(const zREAL v)			{ kambient		= v;		};
	void					SetDiffuse			(const zREAL v)			{ kdiffuse		= v;		};
/*	void					SetPreAmbient		(const zREAL v)			{ kpreAmbient	= v;		};
	void					SetSpecular			(const zREAL v)			{ kspecular		= v;		};
*/
	// rendering properties
	void					SetAlphaBlendFunc	(const zTRnd_AlphaBlendFunc	a)		{ rndAlphaBlendFunc = a;		};
	zTRnd_AlphaBlendFunc	GetAlphaBlendFunc	() const							{ return rndAlphaBlendFunc;		};

	//
	void					SetDontUseLightmaps (const zBOOL b)				{ dontUseLightmaps=b;		};
	zBOOL					GetDontUseLightmaps () const					{ return dontUseLightmaps;	};

	//
	const zSTRING&			GetName				() const					{ return GetObjectName();		};
	zBOOL					SetName				(const zSTRING& name)		{ return SetObjectName (name);	};
	void					SetColor			(zBYTE r, zBYTE g, zBYTE b) { color.r = r; color.g = g; color.b = b;};
	void					SetColor			(zCOLOR col)				{ color = col;						};
	zCOLOR					GetColor			() const					{ return color;						};
	zBYTE					GetColorR			() const					{ return color.r;					};
	zBYTE					GetColorG			() const					{ return color.g;					};
	zBYTE					GetColorB			() const					{ return color.b;					};
	void					SetAlpha			(const zBYTE a)				{ color.alpha = a;					};
	zBYTE					GetAlpha			() const					{ return color.alpha;				};
	void					RefreshAvgColorFromTexture();	// if mat has texture: get's textures' avgColor and puts it into mat's diffuse color

	//
	zBOOL					IsPortalMaterial	() const;
	void					SetDetailObjectVisual(const zSTRING& name);
	const zSTRING&			GetDetailObjectVisual() const;

	// Texture
	void					SetTexture			(zSTRING& texName);			// does upper on texName
	void					SetTexture			(zCTexture *tex);
	void					RemoveTexture		();
	zCTexture*				GetTexture			() const					{ return texture; };
	void					SetDetailTexture	(zSTRING& texName);
	void					SetDetailTexture	(zCTexture *detailTex);
	zCTexture*				GetDetailTexture	() const					{ return detailTexture;			}
	void					SetDetailTextureScale(const zREAL scale )		{ detailTextureScale = scale;	}
	zREAL					GetDetailTextureScale() const					{ return detailTextureScale;	}

	// Texture-Animation
	inline zCTexture*		GetAniTexture		();
	void					ApplyTexAniMapping	(zCPolygon *poly);
	void					SetTexAniMapping	(zBOOL b)					{ texAniMap = b; };
	zBOOL					GetTexAniMapping	() const					{ return texAniMap; };
	void					SetTexAniMappingDir	(const zREAL angle, const zREAL len);
	void					SetTexAniMappingDir	(const zPOINT2& dir);
	zPOINT2					GetTexAniMappingDir	() const					{ return texAniMapDelta; };
	zVEC3					GetTexAniVector		(zCPolygon *poly);

																			
	zBOOL					GetSmooth			() const					{ return smooth;		};
	void					SetSmooth			(const zBOOL b)				{ smooth = b;			};
	zREAL					GetSmoothAngle		() const					{ return smoothAngle;	};
	void					SetSmoothAngle		(const zREAL a)				{ smoothAngle = a;		};

	zBOOL					GetLODDontCollapse	() const					{ return lodDontCollapse;	};
	void					SetLODDontCollapse	(const zBOOL b)				{ lodDontCollapse=b;		};

	zBOOL					GetNoCollDet		(const zBOOL a_bIgnoreOverrides = FALSE) const					
	{ 
		// skip polys with this material in collision detection ?
		#ifdef COMPILING_SPACER
		if (a_bIgnoreOverrides || g_bIsPlayingGame)		  return noCollDet;
		else											  return FALSE;
		#else
		return noCollDet;
		#endif
	};	

	const zSTRING&			GetTextureName () 
	{
		if (texture==0) return zSTR_EMPTY;
		else			return texture->GetObjectName();
	};

	void					SetNoCollDet		(const zBOOL b)				{ noCollDet=b;				};

	// [EDENFELD] 1.09: neue Material Eigenschaft: "forceOcclusion" eingeführt
	zBOOL					GetOccluder			() const					{ return forceOccluder;		};	
	void					SetOccluder			(const zBOOL b)				{ forceOccluder=b;			};

	void					SetDefaultMapping	(const zVEC2& defMap)		{ default_mapping=defMap;	};
	zVEC2					GetDefaultMapping	() const					{ return default_mapping;	};
	
	// List Iterators => zCClassDef (zCMaterial::GetStaticClassDef())
	static zCMaterial*		SearchName			(zSTRING& name);
	static zCMaterial*		Load				(zSTRING& name);

	// persistance
	virtual void			Archive				(zCArchiver &arc);
	virtual void			Unarchive			(zCArchiver &arc);
							
	// these fields are used for material-sorted rendering (zCRenderManager)
	zCArray<zCPolygon*>		polyList;
	zDWORD					polyListTimeStamp;
//	zBOOL					polyListNeedsSort;
//	zDWORD					sceneMaterialIndex;		// FIXME: still in use?
	void					ClearRenderPolyList	() { polyList.EmptyList(); polyListTimeStamp = 0xFFFFFFFF; polyListNeedsSort = FALSE; };

public:						
	zCTexture				*texture;
	zCOLOR					color;								// includes R,G,B, Alpha
	zREAL					smoothAngle;
	zTMat_Group				matGroup;
	zCBspSector				*bspSectorFront;					// for bsp-outdoor rendering
	zCBspSector				*bspSectorBack;						// for bsp-outdoor rendering
	zCTexAniCtrl			texAniCtrl; 
	zSTRING					*detailObjectVisualName;

	// phong reflection model
	zREAL					kambient;
	zREAL					kdiffuse;
/*	zREAL					kpreAmbient;
	zREAL					kspecular;
	zREAL					kspecularPower;
*/

	zREAL					m_bEnvironmentalMappingStrength;

	struct {
		zUINT8				smooth					: 1;
		zUINT8				dontUseLightmaps		: 1;
		zUINT8				texAniMap				: 1;
		zUINT8				lodDontCollapse			: 1;
		zUINT8				noCollDet				: 1;
		zUINT8				forceOccluder			: 1;
		zUINT8				m_bEnvironmentalMapping	: 1;
		zUINT8				polyListNeedsSort		: 1;
		zUINT8				matUsage				: 8;
		zUINT8				libFlag					: 8;
		zTRnd_AlphaBlendFunc rndAlphaBlendFunc		: 8;		// special rendering properties
		zUINT8				m_bIgnoreSun			: 1;
	};

	zTWaveAniMode			m_enuWaveMode;
	zTFFT					m_enuWaveSpeed;
	float					m_fWaveMaxAmplitude;
	float					m_fWaveGridSize;

protected:
	virtual ~zCMaterial();			// use Release() instead !

private:
	static zBYTE			s_matUsageDefault;
	void					InitValues			();
	void					InitThisByMaterial	(const zCMaterial& sourceMaterial);
	void					AutoAssignDetailTexture();

	zCTexture				*detailTexture;
	zREAL					detailTextureScale;
	zPOINT2					texAniMapDelta;

	// for external Tools (Spacer)
	zPOINT2					default_mapping;		// needed by Editor
	zPOINT2					texScale;
};

// inlines


zCTexture*	zCMaterial::GetAniTexture () { 
	if (texture) {
		if (texture->IsAnimated()) { 
			texAniCtrl.AdvanceAni(texture); 
			return texture->GetAniTexture();
		} else
			return texture;
	} else return 0;
};

// ==========================================================================================================


// ==========================================================================================================

// enable VC++ Warning: double to float conversion
#pragma warning( default: 4305 ) 

#endif