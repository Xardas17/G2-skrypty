/******************************************************************************** 
 
     $Workfile:: zRenderLightContaine $                $Date:: 24.04.01 17:33   $
     $Revision:: 25                   $             $Modtime:: 22.04.01 21:16   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Render Light Container
   created: 31.10.99

 * $Log: /current_work/ZenGin/_Dieter/zRenderLightContainer.cpp $
 * 
 * 25    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 24    15.02.01 18:50 Hildebrandt
 * 
 * 23    15.02.01 4:39 Hildebrandt
 * 
 * 22    15.02.01 3:40 Hildebrandt
 * 
 * 21    14.02.01 13:58 Moos
 * Cache-Aufräumen richtig gemacht
 * 
 * 20    13.02.01 1:08 Hildebrandt
 * 
 * 19    12.02.01 23:44 Hildebrandt
 * 
 * 18    12.02.01 23:24 Hildebrandt
 * 
 * 17    10.02.01 6:10 Hildebrandt
 * 
 * 16    10.02.01 4:11 Hildebrandt
 * 
 * 15    8.02.01 21:39 Hildebrandt
 * 
 * 14    8.02.01 6:53 Hildebrandt
 * 
 * 13    2.02.01 19:29 Hildebrandt
 * 
 * 12    2.02.01 5:23 Hildebrandt
 * 
 * 11    1.02.01 5:48 Hildebrandt
 * 
 * 10    30.01.01 5:16 Hildebrandt
 * 
 * 9     25.01.01 5:07 Hildebrandt
 * 
 * 8     16.01.01 3:31 Hildebrandt
 * 
 * 7     8.01.01 17:56 Hildebrandt
 * 
 * 6     20.12.00 3:03 Hildebrandt
 * 
 * 5     25.11.00 3:31 Hildebrandt
 * 
 * 4     26.10.00 18:07 Hildebrandt
 * 
 * 3     25.10.00 15:07 Hildebrandt
 * 
 * 2     21.09.00 21:21 Hildebrandt
 * zenGin 0.94
 *********************************************************************************/

// DOC++ 
/// @author   Author: Hildebrandt
/// @version $Revision: 25 $ ($Modtime: 22.04.01 21:16 $)

// =======================================================================================================================

#include <zCore.h>
#include <zRenderLightContainer.h>
#include <zVob.h>
#include <zWorld.h>
#include <zBsp.h>
#include <zSparseArray.h>
#include <zoption.h>

#ifdef DEBUG_HILDEBRANDT
	#define zRND_LIGHT_DEBUG

	#include <zView.h>
	#include <zInput.h>
#endif
	#include <zInput.h>

// =======================================================================================================================

// Light-Score, ab der aus einem PointLight ein DirLight gemacht wird
#define zPM_LIGHT_TREAT_POINT_AS_DIR_THRESH		zREAL(0.01F)

// Die wichtigsten n DynLights werden beruecksichtigt
#define zRENDERLIGHT_MAX_DYN_LIGHT				4

const float AMBIENTCOL_SCALE_EXACT = 0.40f;
const float AMBIENTCOL_SCALE_FAST  = 0.60f;
const float AMBIENTCOL_SCALE_EXACT_STATVOBLIGHT_INDOOR	= 0.15f;
const float AMBIENTCOL_SCALE_EXACT_STATVOBLIGHT_OUTDOOR			= 0.30f;
const float AMBIENTCOL_SCALE_EXACT_STATVOBLIGHT_OUTDOOR_NPCS	= 0.60f;

static zBOOL exactPointStatLight	= FALSE;

// =======================================================================================================================

int zCRenderLightContainer::CompareLightScore ( const void *arg1, const void *arg2 ) {
	const zTLightScore* const light1= (zTLightScore*)arg1; 
	const zTLightScore* const light2= (zTLightScore*)arg2;
//	return (light1->score - light2->score);
	if (light1->score<light2->score)	return -1;
	else								return +1;	// "gleich" gibt's nicht
};

void zCRenderLightContainer::CreatePrelightConfig (const zTBBox3D &bbox)
{
	Clear();

	zVEC3 center	= bbox.GetCenter();
	zVEC3 color		= zVEC3(255,255,255);

	// Light 1	- frontal
	{
		zCRenderLight	&pmLight		= lightList[numLights];
		pmLight.lightType				= zLIGHT_TYPE_DIR;
		pmLight.colorDiffuse			= color;
		pmLight.position				= center + zVEC3(300,0,300);		
		pmLight.direction				= (zVEC3(-1,-0.5F,-1).Normalize());
		pmLight.dir_approxFalloff		= 1.0F;
		numLights++;
	};

	// Light 2	- hinten
	{
		zCRenderLight	&pmLight		= lightList[numLights];
		pmLight.lightType				= zLIGHT_TYPE_DIR;
		pmLight.colorDiffuse			= color;
		pmLight.position				= center + zVEC3(300,0,300);
		pmLight.direction				= (zVEC3(0.1F,+0.1F,1).Normalize());
		pmLight.dir_approxFalloff		= 0.2F;
		numLights++;
	};
};

zBOOL  zCCFASTCALL zCRenderLightContainer::CollectLights_FastPath (const zTRenderContext& renderContext)
{
	// Prelight? (=> eigentlich nur reines ambient light)
	if (this->GetDoPrelight())
	{
		//
		this->numLights					= 1;
		zCRenderLight	&pmLight		= lightList[0];
		pmLight.lightType				= zLIGHT_TYPE_AMBIENT;

		// Prelit Farbe berechnen
		zCOLOR col						= renderContext.vob ? renderContext.vob->CalcLightSampleAtOrigin() : zCOLOR(255,255,255,255);
		pmLight.colorDiffuse			= AMBIENTCOL_SCALE_FAST * col.GetVEC3();

		// ggfs. CamLight einrechnen
		if (renderContext.cam->GetCamLightRange()>100.0F) 
		{
			zREAL d		= 255.0F * (1-(renderContext.distVobToCam / renderContext.cam->GetCamLightRange()));
			if (!zIsNegative(d)) 
			{
				pmLight.colorDiffuse	+= zVEC3(d);	// camLight
				for (int i=0; i<3; i++)
					if (pmLight.colorDiffuse[i]>zREAL(255.0F)) pmLight.colorDiffuse[i]=zREAL(255.0F);
			};
		};
		return TRUE;
	};

	// Lighting Hint Fullbright? => einfach ein weisses ambient Licht aktivieren
	// (wird vorwiegend aus Performance-Gruenden eingesetzt: es muessen keine Lichter eingesammelt werden)
	if (renderContext.hintLightingFullbright)
	{
		this->numLights					= 1;
		zCRenderLight	&pmLight		= lightList[0];
		pmLight.lightType				= zLIGHT_TYPE_DIR;
		pmLight.colorDiffuse			= zVEC3(255);
		pmLight.direction				= zVEC3(+0.4495F, -0.8660F, -0.2181F);
		return TRUE;
	};
	return FALSE;
};

class zCDynVobLightCacheElement 
{
public:
	zCDynVobLightCacheElement() 
	{ 
		memset			(&dynVobLightList, 0, sizeof(dynVobLightList)); 
	};
	zCDynVobLightCacheElement(const zCVob* vob) 
	{ 
		memset			(&dynVobLightList, 0, sizeof(dynVobLightList)); 
		UpdateContents	(vob);
	};
	~zCDynVobLightCacheElement() 
	{
		ReleaseLights	();
	}
	inline void ReleaseLights ()
	{
		// bestehende Refs freigeben
		for (int i=0; i<zRENDERLIGHT_MAX_DYN_LIGHT; i++)
		{
			zRELEASE (dynVobLightList[i]);
		};
	};

	void UpdateContents (const zCVob *vob)
	{
		// bestehende Refs freigeben
		ReleaseLights();

		// Cache Element updaten
		{
			// 'lightColorDynDirty' auf FALSE setzen
			(const_cast<zCVob*>(vob))->GetLightColorDyn			();

			zCArray<zCVobLight*>								vobDynLightList	(8);	
			zCArraySort<zCRenderLightContainer::zTLightScore>	dynLightScore	(8);
			dynLightScore.SetCompare							(zCRenderLightContainer::CompareLightScore);
			zTBSphere3D											lightSphere;

			//
			for (int i=0; i<vob->vobLeafList.GetNum(); i++) 
			{ 
				zCBspLeaf *leaf = vob->vobLeafList[i];
				for (int j=0; j<leaf->lightVobList.GetNum(); j++) 
				{
					zCVobLight *light	= leaf->lightVobList[j];
					if (!exactPointStatLight)
					if (light->GetIsStatic()) continue;

					lightSphere.center	= light->GetPositionWorld();
					lightSphere.radius	= light->GetRange();

					if (vob->GetBBox3DWorld().IsIntersecting (lightSphere))
					{
						// Wichtigkeit der Lichquelle berechnen
						zCRenderLightContainer::zTLightScore		lightScore;
						lightScore.score	= ((vob->GetPositionWorld()-light->GetPositionWorld()).LengthApprox()) * light->GetRangeInv();
						zClamp01			(lightScore.score);

						// lights nach stat und dyn sortieren
						// Die duerfen keine Lights aus den Leaflisten ausgelassen werden (also ist z.B. kein
						// Abbruch bei Erreichung der zRENDERLIGHT_MAX_DYN_LIGHT Grenze erlaubt!)
						if (!vobDynLightList.IsInList(light))	
						{
							lightScore.index		= dynLightScore.GetNum();
							dynLightScore.Insert	(lightScore);
							vobDynLightList.Insert	(light);
						};
					};
				};
			};

			// Sortierreihenfolge: kleiner...groesser
			dynLightScore.QuickSort();

			// CacheElement fuellen
			for (i=0; i<dynLightScore.GetNum(); i++)
			{
				zCVobLight		*light			= vobDynLightList[dynLightScore[i].index];
				this->dynVobLightList[i]		= light;
				light->AddRef					();
				if (i>=zRENDERLIGHT_MAX_DYN_LIGHT-1)	break;
			};
			#ifdef DEBUG_HILDEBRANDT
			//	zlineCache.Line3D (	vob->GetPositionWorld(), vob->GetPositionWorld()+zVEC3(0,20,0));
			#endif
		};
	};

	zCVobLight		*dynVobLightList[zRENDERLIGHT_MAX_DYN_LIGHT];
	zMEMPOOL_DECLARATION (zCDynVobLightCacheElement);
};

enum { zDYN_LIGHT_CACHE_NUM_ELEMENTS= 512 };
enum { zDYN_LIGHT_CACHE_BLOCKSIZE	= (zRENDERLIGHT_MAX_DYN_LIGHT*4) * zDYN_LIGHT_CACHE_NUM_ELEMENTS};

zMEMPOOL_DEFINITION_BS_PA (zCDynVobLightCacheElement, zDYN_LIGHT_CACHE_BLOCKSIZE, zDYN_LIGHT_CACHE_BLOCKSIZE);

static zCCache < const zCVob*, zCDynVobLightCacheElement > s_dynVobLightCache(zDYN_LIGHT_CACHE_NUM_ELEMENTS, 600);		// FXME: size, timeOut

void zCRenderLightContainer::S_ReleaseVobLightRefs ()
{
	s_dynVobLightCache.ClearCache();
};

/*
	- dynLights/cacheElement neu berechnen, falls:
		- wenn vob->dynLightDirty
		- wenn cacheElement ungueltig geworden ist (timeout?)

  - FIXME: man die Caches fuer statische und dyn. Infos zusammenlegen!
	- dyn Info : Liste von dynVobLights
	- stat Info: aktuelle 'lightDirectionStat' (derzeit im zCVob..)
*/

void zCCFASTCALL zCRenderLightContainer::CollectLights_DynLights (const zTRenderContext& renderContext)
{

	static zBOOL treatStatLightsAsDynLights = FALSE;

	if (!treatStatLightsAsDynLights)
	{
		treatStatLightsAsDynLights = TRUE;
		exactPointStatLight = zoptions->ReadBool("ENGINE","zVobPointLight" , TRUE);
	}

	zCDynVobLightCacheElement		*cacheElement;
	cacheElement					= s_dynVobLightCache[renderContext.vob];

	// Cache Element refreshen?
	if ((!cacheElement) || (renderContext.vob->GetLightColorDynDirty()))
	{
		cacheElement->UpdateContents (renderContext.vob);
	};

	// dynLights eintragen
	for (int i=0; i<zRENDERLIGHT_MAX_DYN_LIGHT; i++)
	{
 		zCVobLight		*light			= cacheElement->dynVobLightList[i];
		if (!light)	break;

		zERR_ASSERT (light->GetRefCtr()>=0);

		// Ein bereits aus Welt entferntes Licht koennte noch von diesem Cache referenziert werden.
		// Dieser Code gibt in diesem Fall die Referenz moeglichst schnell wieder frei.
		if ((light->GetHomeWorld()==0) || (light->GetRefCtr()<=1))
		{
			light->Release();
			for (int j=i; j<zRENDERLIGHT_MAX_DYN_LIGHT-1; j++)
				cacheElement->dynVobLightList[j]	= cacheElement->dynVobLightList[j+1];
			cacheElement->dynVobLightList[zRENDERLIGHT_MAX_DYN_LIGHT-1] = 0;
			--i;
			continue;
		};

		// RenderLight erzeugen
		zCRenderLight	&pmLight		= lightList[numLights];
		pmLight.lightType				= zLIGHT_TYPE_POINT;
		pmLight.range					= light->GetRange();
		pmLight.rangeInv				= light->GetRangeInv();
		pmLight.colorDiffuse			= light->GetColor().GetVEC3();
		if (exactPointStatLight && light->GetIsStatic()) pmLight.colorDiffuse *= 0.8f;

		pmLight.position				= light->GetPositionWorld();		// pos im CamSpace

		// FIXME:
		//	if (dynLightScore[i].score>zPM_LIGHT_TREAT_POINT_AS_DIR_THRESH)
		/* if (0)
		{
			pmLight.lightType				= zLIGHT_TYPE_DIR;
			pmLight.dir_approxLightToObjLS	= trafoObjToCam.GetTranslation() - pmLight.position;
			zREAL len						= pmLight.dir_approxLightToObjLS.LengthApprox();
			pmLight.dir_approxFalloff		= 1 - (len * pmLight.rangeInv);
			pmLight.dir_approxLightToObjLS	/= len;
		};*/

		#ifdef zRND_LIGHT_DEBUG
			zlineCache.Line3D (light->GetPositionWorld(), light->GetPositionWorld()+zVEC3(0,20,0));
		#endif
		numLights++;

		if (numLights>=zRENDERLIGHT_LIGHT_MAX)		break;
	};
};

void zCCFASTCALL zCRenderLightContainer::CollectLights_StatLights (const zTRenderContext& renderContext)
{
	static zREAL highLightScaler		= -1;

	if (highLightScaler == -1)
	{
		highLightScaler		= 0.0f;
		highLightScaler		= zoptions->ReadReal("ENGINE","zHighLightScale", highLightScaler);
	}

	// statLights eintragen
	// Strategie:
	// 
	// Alle statLights als eine Lichtquelle behandeln. Die Color ergibt sich aus dem FloorLight, die Direction/Pos des
	// "virtuellen" Lichtes aus der Kombination aller statischen Lichter an dem Ort.
	// Die Direction ist eine Gewichtung aus dem SunLight-Vektor und dem Vektor zu jeder Lichtquelle. In Abhaengigkeit
	// von der Score der einzelnen Lichter werden diese ineinander "gelerpt".


	// Sunlight / stat Light (kombiniert)
	zVEC3 floorLight;
	zREAL darkNessScaler;
	zBOOL outdoor = (!renderContext.vob->GetGroundPoly()) || (!renderContext.vob->GetGroundPoly()->GetSectorFlag()) || (renderContext.world->GetBspTree()->GetBspTreeMode()==zBSP_MODE_INDOOR);
	{
		floorLight						= renderContext.vob->GetLightColorStat().GetVEC3();

		if (outdoor)
		{
			darkNessScaler = (renderContext.vob->GetLightColorStatGroundPoly().GetIntensityFloat() * 1.111111f)/255.0f;
			if (darkNessScaler>1) darkNessScaler = 1;
				// dunkelste stelle: 0.7: hellste stelle: 1: d.h. ein Schatten verdunkelt einen vob maximal 30%

			zVEC3 statLightDir				= CalcStatLightDir(renderContext);

			// direction smoothing lerp

			{
				zREAL distTotal					= zREAL(2.0F) - ((statLightDir * renderContext.vob->GetLightDirectionStat()) + zREAL(1.0F));	// res: 0..2
				if (distTotal>0)
				{
					zREAL distCanLerp			= zREAL(0.0007F) * ztimer.GetFrameTimeF();	// lerpVelocity
					zREAL t						= distCanLerp / distTotal;
					zClamp01					(t);
					statLightDir				= zLerp (t, renderContext.vob->GetLightDirectionStat(), statLightDir);
					zREAL len					= statLightDir.LengthApprox();
					if (len>0)	statLightDir	/= len;
					else		statLightDir	= renderContext.vob->GetLightDirectionStat();
				};
				renderContext.vob->SetLightDirectionStat(statLightDir);
				//zlineCache.Line3D (renderContext.vob->GetPositionWorld(),  renderContext.vob->GetPositionWorld() + 30.0F * statLightDir);
			};

			// Direktionales Haupt-Licht
			//if (0)
			{
				zCRenderLight	&pmLight		= lightList[numLights];
				pmLight.lightType				= zLIGHT_TYPE_DIR;
				pmLight.colorDiffuse			= floorLight;

				if (renderContext.vob->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_NONE) pmLight.colorDiffuse *= (darkNessScaler * 0.8F);		// objekte sind i.A. noch dunkler als NSCs
				else																	 pmLight.colorDiffuse  = darkNessScaler * floorLight * AMBIENTCOL_SCALE_EXACT_STATVOBLIGHT_OUTDOOR_NPCS;

				pmLight.direction				= statLightDir;
				pmLight.dir_approxFalloff		= 1;
				numLights++;
			};
		}

		// Ambientes Licht
		zCRenderLight	&pmLight		= lightList[numLights];
		pmLight.lightType				= zLIGHT_TYPE_AMBIENT;

		if ( renderContext.hintLightingSwell  )
		{
			const zREAL distScale		= zMax (zREAL(0), zREAL(1) - (renderContext.distVobToCam / zREAL(3000.0F))); 
			zREAL colorIntensity		= ((0.299F)*floorLight[0] + (0.587F)*floorLight[1] + (0.114F)*floorLight[2]);
			colorIntensity				*= zREAL(0.7F);
			colorIntensity				= distScale * colorIntensity * ((zSinApprox (ztimer.GetTotalTimeF() / 250.0F) + 1.0F) * 0.5F);
			pmLight.colorDiffuse		= zVEC3(colorIntensity*highLightScaler);
		} 
		else if (renderContext.hintLightingHighlight)
		{
			/* zREAL strength			= zREAL(renderContext.hintLightingHighlightColor.GetAlphaByte()) / zREAL(255.0F);
			zREAL intens				= zREAL(0.40F) + strength * zREAL(0.60F);
			pmLight.colorDiffuse		= intens * zLerp (strength, floorLight, renderContext.hintLightingHighlightColor.GetVEC3());*/

			if (highLightScaler==-1)
			{
				const zREAL strength		= zREAL(renderContext.hintLightingHighlightColor.GetAlphaByte()) / zREAL(255.0F);
				zREAL colorIntensity		= ((0.299F)*floorLight[0] + (0.587F)*floorLight[1] + (0.114F)*floorLight[2]);
				colorIntensity				*= zREAL(0.7F);
				pmLight.colorDiffuse		= floorLight * zREAL(0.40F);	// 0,42, 0.22
				pmLight.colorDiffuse		+= colorIntensity * strength * ((zSinApprox (ztimer.GetTotalTimeF() / 250.0F) + 1.0F) * 0.5F);
				if (pmLight.colorDiffuse[0]>255) pmLight.colorDiffuse[0]=255;
				if (pmLight.colorDiffuse[1]>255) pmLight.colorDiffuse[1]=255;
				if (pmLight.colorDiffuse[2]>255) pmLight.colorDiffuse[2]=255;
			}
			else
			{
				const zREAL strength		= zREAL(renderContext.hintLightingHighlightColor.GetAlphaByte()) / zREAL(255.0F);
				const zREAL colorIntensity	= (((0.299F)*floorLight[0] + (0.587F)*floorLight[1] + (0.114F)*floorLight[2])) / zREAL(255.0F);
				if (renderContext.vob->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_NONE)
					pmLight.colorDiffuse		= floorLight * zREAL(0.40F);	// 0,42, 0.22
				else
					pmLight.colorDiffuse		= floorLight;	// 0,42, 0.22
				pmLight.colorDiffuse		+= highLightScaler * strength * colorIntensity * renderContext.hintLightingHighlightColor.GetVEC3();
				if (pmLight.colorDiffuse[0]>255) pmLight.colorDiffuse[0]=255;
				if (pmLight.colorDiffuse[1]>255) pmLight.colorDiffuse[1]=255;
				if (pmLight.colorDiffuse[2]>255) pmLight.colorDiffuse[2]=255;
			}
		} 
		else
		{
			if (exactPointStatLight)
			{
				if (!outdoor)
				{
					// vobs in indoor/outdoor sektoren werden hier nur etwas weniger ambient beleuchtet, da das statische licht
					// nun neuerdings mit verrechnet wird (t&l pointlight)
					pmLight.colorDiffuse		= floorLight * AMBIENTCOL_SCALE_EXACT_STATVOBLIGHT_INDOOR;	// 0,42, 0.22

				}
				else
				{
					if (renderContext.vob->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_NONE) pmLight.colorDiffuse		= /*darkNessScaler ***/ floorLight * AMBIENTCOL_SCALE_EXACT_STATVOBLIGHT_OUTDOOR;	// 0,42, 0.22
					else												  					 pmLight.colorDiffuse		= darkNessScaler * floorLight * AMBIENTCOL_SCALE_EXACT_STATVOBLIGHT_OUTDOOR_NPCS;
				};
			}
			else
			{
				pmLight.colorDiffuse		= floorLight * AMBIENTCOL_SCALE_EXACT;	// 0,42, 0.22
			}
			
		};

		numLights++;
	};
};

void zCCFASTCALL zCRenderLightContainer::CollectLights (const zTRenderContext& renderContext)
{
	// Aus allen Leafs in denen der Vob Fragmente hat werden alle Lights geholt
	// FIXME: diese Liste koennte z.B. auch gecacht werden und nur alle 2 Frames neu...

	const zREAL LIGHT_FADE_QUAL_DIST	 = 300.0f;  // 3 meter
	const zREAL LIGHT_FADE_QUAL_DIST_INV = 1.0f/LIGHT_FADE_QUAL_DIST;		

	zERR_ASSERT (renderContext.cam);
	zERR_ASSERT (renderContext.vob);

	// Der Container entleert sich bereits vorhandener Lichter.
	// ACHTUNG: an dieser Stelle darf KEIN Clear() aufgerufen werden, da dieses das prelight Flag zuruecksetzt!
	this->numLights					= 0;
	m_bSmoothPrelit					= FALSE;

	if (CollectLights_FastPath		(renderContext))	
	{		
		if (m_fPreLightDist != 0)
			m_bSmoothPrelit = (renderContext.distVobToCam >= m_fPreLightDist) && (renderContext.distVobToCam <= m_fPreLightDist+LIGHT_FADE_QUAL_DIST );
		
		if (!m_bSmoothPrelit) return;
	}
									
	// Trafo bauen					
	trafoObjToCam					= renderContext.cam->GetTransform(zCAM_TRAFO_VIEW) * renderContext.vob->trafoObjToWorld;
									
	// DynLights					
	CollectLights_DynLights			(renderContext);
									
	// StatLights					
	CollectLights_StatLights		(renderContext);

	// CamLight
	if (renderContext.cam->GetCamLightRange()>100.0F)
	{
		zCRenderLight	&pmLight	= lightList[numLights];
		pmLight.lightType			= zLIGHT_TYPE_POINT;
		pmLight.range				= renderContext.cam->GetCamLightRange();
		pmLight.rangeInv			= zREAL(1.0F) / pmLight.range;
		pmLight.colorDiffuse		= zVEC3(255,255,255);
		pmLight.position			= renderContext.cam->GetVob()->GetPositionWorld();
		pmLight.direction			= renderContext.cam->GetVob()->GetAtVectorWorld();
		numLights++;
	};


	if (m_bSmoothPrelit)
	{
		zREAL smoothFactor = (renderContext.distVobToCam-m_fPreLightDist) * LIGHT_FADE_QUAL_DIST_INV;	
		zClamp01(smoothFactor);

	//	screen->Print (0,0, zSTRING("smoothFactor: ") + zSTRING(smoothFactor));

		zCRenderLight	&light	= lightList[0];
		zVEC3 colAmbientExact   = lightList[numLights-1].colorDiffuse;
		zVEC3 colAmbientFast    = lightList[0].colorDiffuse;

		light.colorDiffuse	= zLerp(smoothFactor, colAmbientExact, colAmbientFast );
		numLights --;

		for (int i=1; i<numLights; i++)
		{
			zCRenderLight	&light	= lightList[i];
			light.colorDiffuse	= zLerp(smoothFactor, light.colorDiffuse, zVEC3(0,0,0));
		};
	}

#ifdef zRND_LIGHT_DEBUG
//#if 1 
	{
		zREAL	xscr, yscr;
//		zPOINT3	pos	= renderContext.cam->Transform	(renderContext.vob->GetPositionWorld());
		zPOINT3 pos = renderContext.cam->GetVob()->trafoObjToWorld.InverseLinTrafo() * renderContext.vob->GetPositionWorld();
		if (pos[VZ]>0)
		if (pos.Length()<1000.0F)
		{
			renderContext.cam->Project					(&pos, xscr, yscr);
			screen->Print (screen->anx(int(xscr)),screen->any(int(yscr)), "s,d,r: "+zSTRING(vobStatLightList.GetNum())+", "+zSTRING(vobDynLightList.GetNum())+", "+zSTRING(numLights));
			screen->Print (screen->anx(int(xscr))+200,screen->any(int(yscr))+200, 
				zSTRING((int)floorLight[0])+", "+zSTRING((int)floorLight[2])+", "+zSTRING((int)floorLight[2]));

			int yout=3000;
			for (i=0; i<dynLightScore.GetNum(); i++)
			{
				zCVobLight		*light			= vobDynLightList[dynLightScore[i].index];
				screen->Print (0,yout, "dyn "+zSTRING(i)+", "+light->GetVobName()+", ptr: "+zSTRING(int(light))+", r:"+zSTRING(light->GetRange(),3)+", score: "+zSTRING(dynLightScore[i].score,3));
				yout += screen->FontY();
			};
			for (i=0; i<statLightScore.GetNum(); i++)
			{
				zCVobLight		*light			= vobStatLightList[statLightScore[i].index];
				screen->Print (0,yout, "stat "+zSTRING(i)+", "+light->GetVobName()+", ptr: "+zSTRING(int(light))+", r:"+zSTRING(light->GetRange(),3)+", score: "+zSTRING(statLightScore[i].score,3));
				yout += screen->FontY();
			};
		};
	};
#endif
};
 
zVEC3 zCRenderLightContainer::CalcStatLightDir(	const zTRenderContext& renderContext)
{
	zERR_ASSERT (renderContext.world);

	// sun: zVEC3(+0.4495F, -0.8660F, -0.2181F);
	const zVEC3 defaultStatLightDir = zVEC3(+1,-0.5F,-1).NormalizeApprox();
	const zBOOL outdoor				= (renderContext.world->GetBspTree()->GetBspTreeMode()==zBSP_MODE_OUTDOOR);

	// Im Outdoor ausserhalb eines Sektors => einfach Richtung der Sonne nehmen
	if (outdoor)
	{
		if ((!renderContext.vob->GetGroundPoly()) ||
			(!renderContext.vob->GetGroundPoly()->GetSectorFlag()))
		{
			return defaultStatLightDir;
		};
	};

	// FIXME: FindLeaf(): geht das irgendwie schneller?
	zCBspLeaf *bspLeaf = renderContext.world->GetBspTree()->FindLeaf (renderContext.vob->GetPositionWorld());
	if (bspLeaf)
	{
		if (bspLeaf->lightPosition[0]== zREAL(zCBspLeaf::zBSP_LEAF_LIGHT_UNDEFINED))
		{
			return defaultStatLightDir;
		} else
		{
			zVEC3 statLightDir = renderContext.vob->GetPositionWorld() - bspLeaf->lightPosition;
			statLightDir.NormalizeApprox();
//			zlineCache.Line3D (bspLeaf->lightPosition, renderContext.vob->GetPositionWorld(), GFX_PINK);
			return statLightDir;
		};
	} else
	{
		return defaultStatLightDir;
	};
};

zVEC3 zCRenderLightContainer::LightVertex (const zPOINT3& position, const zVEC3& normal) const
{
	zVEC3	color(0,0,0);
	zREAL	i;
	for (int j=0; j<numLights; j++)
	{
		const zCRenderLight &light = lightList[j];
		if (light.lightType==zLIGHT_TYPE_POINT)
		{
			zVEC3	view		= position - light.positionLS;					// lightSpace, lightSpace
			
			// 1. Distance-Falloff
			zREAL	len			= view.LengthApprox();
			if (len>light.range) continue;
			zREAL	dist		= 1-(len * light.rangeInv);

			// 2. Diffuse
			// dot<0 => poly ist lq abgewandt
			// (zu beleuchtender Punkt) - (Ort der Lichtquelle)
			zREAL	dot			= -((view * normal) / len);
			if (dot<0) continue;
//			if (dot<0) dot = ((1.0F-(dot)) * 0.1F);
//			if (dot<0) dot = (     -(dot)  * 0.1F);
			i					= dot*dist;

/*			view.NormalizeApprox();
			zlineCache.LineCS3D (position, position+normalCS*10.0F);
			zlineCache.LineCS3D (position, position-view*10.0F, GFX_GREEN);
*/
		} else
		if (lightList[j].lightType==zLIGHT_TYPE_SPOT)
		{
		} else
		if (lightList[j].lightType==zLIGHT_TYPE_DIR)
		{
			// 2. Diffuse
			zREAL	dot			= -(light.directionLS * normal);
//			if (dot<0) continue;
			if (dot<0) dot = (     -(dot)  * 0.20F );
//			if (dot<0) dot = 0;

			i					= dot*light.dir_approxFalloff;
			i += 0.23F;
		};
		// Farbe des Lichtes durch die Intensitaet skalieren
		color += i * light.colorDiffuse;
	};

	// clamp maximum
	if (zIsGreaterPositive(color.n[0], zREAL(255.0F)))	color.n[0]=zREAL(255.0F);
	if (zIsGreaterPositive(color.n[1], zREAL(255.0F)))	color.n[1]=zREAL(255.0F);
	if (zIsGreaterPositive(color.n[2], zREAL(255.0F)))	color.n[2]=zREAL(255.0F);
	assert ((color.n[0]>=0) && (color.n[0]<=255.0F));
	assert ((color.n[1]>=0) && (color.n[1]<=255.0F));
	assert ((color.n[2]>=0) && (color.n[2]<=255.0F));
	return color;
};

void zCCFASTCALL zCRenderLightContainer::Activate (const zMAT4 &trafoWorldToObj)
{
	// trafoWorldToLS
	// LS ist entweder Vob-OS oder Bone-OS oder CS
	// Alle Lights in den 'Lighting Space' bringen
	for (int i=0; i<numLights; i++)
	{
		zCRenderLight &pmLight	= lightList[i];
		if (pmLight.lightType==zLIGHT_TYPE_POINT) {
			pmLight.positionLS		= trafoWorldToObj * pmLight.position;
		} else
		if (pmLight.lightType==zLIGHT_TYPE_DIR) 
		{
			pmLight.directionLS		= trafoWorldToObj.Rotate (pmLight.direction);	// [BC] BOUNDSCHECKER: Reading uninted memory: in Rotate(); wie kann es hier ueberhaupt etwas anderes als POINT im Indoor geben?
		};
	};
};

void zCRenderLightContainer::SetupRendererLights () 
{
	// FIXME: man koennte hier die bereits aktiven Lights vom letzten mal cachen & nur die geaenderten updaten!

	// Hier wird die globale Resource "Renderer-Lights" manipuliert.
	// kleine Optimierung, die nur Lights loescht, die beim letzten Set gesetzt wurden (geht davon aus, dass das hier der einzige Ort der Manipulierung von Renderer Lights ist)

	static int	s_numLightsSetLastTime	= 0;	
//	int			numLightsToSet			= zrenderer->HasCapability (zRND_CAP_TNL_MAXLIGHTS);
	int			numLightsToSet			= zMax (numLights, s_numLightsSetLastTime);
	for (int i=0; i<numLightsToSet; i++)
	{
		if (i<numLights)
		{
			zrenderer->SetLight		(i, &(lightList[i]));
		} else
			zrenderer->SetLight		(i, 0);
	};
	s_numLightsSetLastTime	= numLights;
};

// =======================================================================================================================


#if 0

  s = v*t
  current 
  newSample

  distTotal		= (newSample - currentSample).Length();
  distCanLerp	= lerpVelocity * ztimer.GetFrameTimeF();
  t				= distCanLerp / distTotal;
  current		= lerp (t, currentSample, newSample)

statCol
statDir

#endif
