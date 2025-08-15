/******************************************************************************** 
 
     $Workfile:: zRenderLightContaine $                $Date:: 15.02.01 18:50   $
     $Revision:: 6                    $             $Modtime:: 15.02.01 18:43   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Render Light Container
   created: 31.10.99

 * $Log: /current_work/zengin_work/_Dieter/zRenderLightContainer.h $
 * 
 * 6     15.02.01 18:50 Hildebrandt
 * 
 * 5     15.02.01 3:40 Hildebrandt
 * 
 * 4     12.02.01 23:24 Hildebrandt
 * 
 * 3     8.02.01 6:53 Hildebrandt
 * 
 * 2     8.02.01 0:49 Hildebrandt
 *********************************************************************************/

// DOC++ 
/// @author   Author: Hildebrandt
/// @version $Revision: 6 $ ($Modtime: 15.02.01 18:43 $)

// =======================================================================================================================

#ifndef __ZRENDERLIGHTCONTAINER_H__
#define __ZRENDERLIGHTCONTAINER_H__


#ifndef __ZRENDERER_H__
#include <zRenderer.h>
#endif

// =======================================================================================================================

struct zTRenderContext;
struct zTBBox3D;
class  zCVobLight;

// =======================================================================================================================

class zCRenderLightContainer {
public:
	zCRenderLightContainer	() { Clear(); };
	~zCRenderLightContainer	() { Clear(); };

	void					Clear					() { numLights	= 0; doPrelight=FALSE; m_fPreLightDist = 0.0f;  m_bSmoothPrelit = FALSE; };
	void					CreatePrelightConfig	(const zTBBox3D &bbox);
	void	zCCFASTCALL		CollectLights			(const zTRenderContext& renderContext);
	zVEC3					LightVertex				(const zPOINT3& position, const zVEC3& normal) const;
	const zMAT4&			GetTrafoObjToCam		() const { return trafoObjToCam; };
	void					SetTrafoObjToCam		(const zMAT4& matrix)	{ trafoObjToCam = matrix;				};
	zBOOL					GetDoPrelight			() const 				{ return doPrelight;					};
	zBOOL					GetSmoothPrelit			() const 				{ return m_bSmoothPrelit;					};
	void					SetDoPrelight			(const zBOOL b)			{ doPrelight = b;						};
	void					SetPreLightDist			(const zREAL a_dist)	{ m_fPreLightDist  = a_dist;			};
	void					SetupRendererLights		();			// transferes the contained lights into the renderer (zCRenderer::SetLight())

	void	zCCFASTCALL		Activate				(const zMAT4 &trafoWorldToObj);

	// RenderlightContainers cache refs to voblights, this frees them
	static void				S_ReleaseVobLightRefs	();

	enum					{ zRENDERLIGHT_LIGHT_MAX = 8 };
	zCRenderLight			lightList[zRENDERLIGHT_LIGHT_MAX];
	int						numLights;

private:
	
	zBOOL					doPrelight;
	zBOOL					m_bSmoothPrelit;
	zREAL					m_fPreLightDist;
	zMAT4					trafoObjToCam;

	struct zTLightScore {
		int		index;
		zREAL	score;
	};
	static int				CompareLightScore		( const void *arg1, const void *arg2 );
	zVEC3					CalcStatLightDir		(const zTRenderContext&	renderContext);
	zBOOL	zCCFASTCALL		CollectLights_FastPath	(const zTRenderContext& renderContext);
	void	zCCFASTCALL		CollectLights_DynLights (const zTRenderContext& renderContext);
	void	zCCFASTCALL		CollectLights_StatLights(const zTRenderContext& renderContext);

	friend class zCDynVobLightCacheElement;
};

// =======================================================================================================================

#endif