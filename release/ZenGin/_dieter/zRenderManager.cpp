/******************************************************************************** 
 
     $Workfile:: zRenderManager.cpp   $                $Date:: 24.04.01 17:33   $
     $Revision:: 37                   $             $Modtime:: 23.04.01 20:05   $
        Author:: Hildebrandt
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Vertex Buffer
   created: 25.5.2000

 * $Log: /current_work/ZenGin/_Dieter/zRenderManager.cpp $
 * 
 * 37    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 36    17.03.01 3:23 Hildebrandt
 * 
 * 34    16.02.01 21:00 Hildebrandt
 * 
 * 33    16.02.01 7:10 Hildebrandt
 * 
 * 32    15.02.01 19:27 Hildebrandt
 * 
 * 31    15.02.01 18:50 Hildebrandt
 * 
 * 30    15.02.01 3:40 Hildebrandt
 * 
 * 29    15.02.01 1:49 Hildebrandt
 * 
 * 28    14.02.01 7:28 Hildebrandt
 * 
 * 27    13.02.01 1:08 Hildebrandt
 * 
 * 26    12.02.01 17:51 Hildebrandt
 * 
 * 25    5.02.01 19:13 Hildebrandt
 * 
 * 24    25.01.01 5:07 Hildebrandt
 * 
 * 23    17.01.01 22:30 Hildebrandt
 * 
 * 22    17.01.01 2:54 Hildebrandt
 * 
 * 21    20.12.00 3:03 Hildebrandt
 * 
 * 20    6.12.00 18:16 Hildebrandt
 * 
 * 19    4.12.00 18:23 Moos
 * 
 * 18    4.12.00 16:28 Hildebrandt
 * 
 * 17    22.11.00 17:45 Hildebrandt
 * 
 * 16    22.11.00 1:36 Hildebrandt
 * 
 * 15    15.11.00 19:44 Hildebrandt
 * 
 * 14    7.11.00 15:16 Hildebrandt
 * 
 * 13    3.11.00 21:22 Hildebrandt
 * 
 * 11    16.10.00 22:08 Hildebrandt
 * 
 * 10    12.10.00 18:02 Hildebrandt
 * 
 * 9     11.10.00 19:45 Hildebrandt
 * 
 * 8     22.09.00 19:18 Hildebrandt
 * 
 * 7     21.09.00 21:21 Hildebrandt
 * zenGin 0.94
 * 
 * 6     15.09.00 16:44 Hildebrandt
 * 
 * 5     31.08.00 17:04 Hildebrandt
 * 
 * 4     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 4     9.08.00 17:12 Admin
 * 
 * 3     21.07.00 14:28 Hildebrandt
 * 
 * 2     3.07.00 12:44 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revisio: 2 $ ($Modtime: 23.04.01 20:05 $)

// =======================================================================================================================

#include <zCore.h>
#include <zRenderManager.h>
#include <z3d.h>
#include <zVertexBuffer.h>
#include <zSky.h>
#include <zOption.h>

#ifdef DEBUG_HILDEBRANDT
//	#include <mm3dnow.h>
	#include <zInput.h>
#endif

#include <zInput.h>

// temp
//#include <zVob.h>
#include <zWorld.h>

// =======================================================================================================================

#define MulColor( /*zCOLOR*/ vertColor, /*int[3]*/ matColor ) \
  (((vertColor.GetRedByte	()*matColor[0])>>8)<<16)	\
 |(((vertColor.GetGreenByte ()*matColor[1])>>8)<<8)		\
 |(((vertColor.GetBlueByte	()*matColor[2])>>8))

// =======================================================================================================================
// =======================================================================================================================

// Shader 

zCShader::zCShader() 
{
	memset (this, 0, sizeof(*this));
};

zCShader::~zCShader()
{
};

void zCShader::InsertStage (int pos, zCShaderStage *stage)
{
	if (numStages>=MAX_STAGES) return;
	for (int i=numStages; i>=pos+1; i--) 
		stageList[i] = stageList[i-1];
	numStages++;
};

zCShaderStage::zCShaderStage()				{ 
//	memset (this, 0, sizeof(*this));		
	shaderFXMode			= zSHD_FX_NONE;
	texture					= 0;
	alphaFunc				= zRND_ALPHA_FUNC_NONE;
	colorFactor				= zCOLOR(0);
	avgTextureColor			= zCOLOR(0);

	alphaGen				= zSHD_ALPHAGEN_IDENTITY;
	rgbGen					= zSHD_RGBGEN_IDENTITY;
	tcGen					= zSHD_TCGEN_BASE;
	tcMod					= zSHD_TCMOD_NONE;
	tcModParams[0]			= 0;
	tcModParams[1]			= 0;
	multiTextureNext		= FALSE;
};

// =======================================================================================================================
// =======================================================================================================================

// AlphaSortObjects

class zCRndAlphaSortObject_WorldPoly : public zCRndAlphaSortObject {
public:
			 zCRndAlphaSortObject_WorldPoly() {};
	virtual ~zCRndAlphaSortObject_WorldPoly() {};

	virtual void							Draw					(int currentIndex);

	//
	static zCRndAlphaSortObject_WorldPoly*	GetFreeAlphaWorldPoly	();
	static void								ResetFreeList			();

	//
	void									SetZValueByPoly			(zCPolygon *poly, const zTPlane& camPlane);

protected:
	// Pool verfuegbarer WorldPoly Objekte
	enum									{ NUM_ALPHA_WORLD_POLY = 4096 };
	static zCRndAlphaSortObject_WorldPoly	s_alphaWorldPolyList[NUM_ALPHA_WORLD_POLY];
	static int								s_currentAlphaWorldPoly;

	static zCArray<zCPolygon*>				s_polyList;
	static int								s_lastPolyIndex;
	static zCShader*						s_lastShader;
	static int								s_polysRendered;

public:
	zCPolygon		*poly;
	zCShader		*shader;
};

// Implementation

zCRndAlphaSortObject_WorldPoly	zCRndAlphaSortObject_WorldPoly::s_alphaWorldPolyList	[NUM_ALPHA_WORLD_POLY];
int								zCRndAlphaSortObject_WorldPoly::s_currentAlphaWorldPoly	= 0;
zCArray<zCPolygon*>				zCRndAlphaSortObject_WorldPoly::s_polyList				= 0;
int								zCRndAlphaSortObject_WorldPoly::s_lastPolyIndex			= 0;
zCShader*						zCRndAlphaSortObject_WorldPoly::s_lastShader			= 0;
int								zCRndAlphaSortObject_WorldPoly::s_polysRendered			= 0;

zCRndAlphaSortObject_WorldPoly* zCRndAlphaSortObject_WorldPoly::GetFreeAlphaWorldPoly()
{
	if (s_currentAlphaWorldPoly>=NUM_ALPHA_WORLD_POLY)	
	{
		zERR_FAULT_ONCE ("D: RNDMAN: too many alphaWorldPolys!");
		s_currentAlphaWorldPoly=0;
	};
	return &(s_alphaWorldPolyList[s_currentAlphaWorldPoly++]);
};

void zCRndAlphaSortObject_WorldPoly::ResetFreeList () 
{ 
	s_currentAlphaWorldPoly	= 0; 
	s_lastPolyIndex			= 0;
	s_lastShader			= 0;
	s_polysRendered			= 0;
	s_polyList.EmptyList	();
};

void zCRndAlphaSortObject_WorldPoly::SetZValueByPoly (zCPolygon *poly, const zTPlane& camPlane)
{
	zREAL dist=0;
	for (int i=0; i<poly->polyNumVert; i++)
	{
		dist += camPlane.GetDistanceToPlane (poly->vertex[i]->position);
	};

//	SetZValue (dist / zREAL(poly->polyNumVert));
//	SetZValue ((dist / zREAL(poly->polyNumVert)) +1500.0F);		// WorldAlphaPolys 15m nach hinten offseten => Vobs/PFX sind so also meist 'vor' den WasserPolys
	SetZValue ((dist / zREAL(poly->polyNumVert)) +4000.0F);		// WorldAlphaPolys 15m nach hinten offseten => Vobs/PFX sind so also meist 'vor' den WasserPolys
};

void zCRndAlphaSortObject_WorldPoly::Draw (int currentIndex)
{
	// Hat dieses Poly denselben Shader wie das vorhergehende? => batchen
	if ((((this->shader==s_lastShader) && (currentIndex==s_lastPolyIndex+1))) || (s_polysRendered==0))
	{
	} else 
	{
		zCCamera::activeCam->Activate();
		zrenderer->SetZBias(DEFAULT_LEVEL_ZBIAS);
		zrenderMan.PackVB		(s_polyList, s_lastShader);
		s_polyList.EmptyList	();
	};
	s_polyList.Insert		(poly);				// in Liste aufnehmen, fruehestens beim naechsten mal rendern
	s_lastPolyIndex			= currentIndex;
	s_lastShader			= this->shader;

	// letztes zu renderndes Poly dieser Art? => gleich rendern
	++s_polysRendered;

	if (s_polysRendered>=s_currentAlphaWorldPoly)
	{
		zCCamera::activeCam->Activate();
		zrenderer->SetZBias(DEFAULT_LEVEL_ZBIAS);
		zrenderMan.PackVB		(s_polyList, this->shader);
		s_polyList.EmptyList	();
	};
};

// =======================================================================================================================
// =======================================================================================================================

// RenderManager

// Groesse der dynamischen VBs
enum { zRM_NUM_VBUFFER_VERT = 2048 };
//enum { zRM_NUM_VBUFFER_VERT = 2016 };

zCRenderManager zrenderMan;

zBOOL				zCRenderManager::s_useRendererTNL			= TRUE;
//#ifdef DEBUG_HILDEBRANDT
// [EDENFELD] 1.09 Detailtexturen aktiviert (unkritisch, wird nur benutzt, wenn für ein Material angegeben)
#if 1
	zBOOL			zCRenderManager::s_detailTexturesEnabled	= TRUE;
#else
	zBOOL			zCRenderManager::s_detailTexturesEnabled	= FALSE;
#endif

zCShader			zCRenderManager::s_shaderList				[zRENDERMAN_NUM_SHADER];
zCShaderStage		zCRenderManager::s_shaderStageList			[zRENDERMAN_NUM_SHADER_STAGES];
int					zCRenderManager::s_currentShader			= 0;
int					zCRenderManager::s_currentShaderStage		= 0;
zCVertexBufferDyn2* zCRenderManager::s_vertBufferDynTex1		= 0;
zCVertexBufferDyn2* zCRenderManager::s_vertBufferDynTex2		= 0;
zCVertexBufferDyn2* zCRenderManager::s_vertBufferDynTex2Normal	= 0;

zCRenderManager::zCRenderManager()
{
	frameCtr					= 0;
	rendererMaterialModified	= FALSE;
	overrideAlphaValue			= 255;
	overrideAlphaBlendFunc		= zRND_ALPHA_FUNC_NONE;
	hintLightning				= FALSE;
};

zCRenderManager::~zCRenderManager()
{
	CleanupRenderManager();
};

void zCRenderManager::InitRenderManager ()
{
	frameCtr					= 0;
	rendererMaterialModified	= FALSE;
	overrideAlphaValue			= 255;
	overrideAlphaBlendFunc		= zRND_ALPHA_FUNC_NONE;

	// Settings aus der .ini auslesen
	{ 
		this->S_SetDetailTexturesEnabled (zoptions->ReadBool ("ENGINE", "zDetailTexturesEnabled", TRUE));
	};
};

void zCRenderManager::CleanupRenderManager	()
{
	delete s_vertBufferDynTex1;			s_vertBufferDynTex1=0;
	delete s_vertBufferDynTex2;			s_vertBufferDynTex2=0;
	delete s_vertBufferDynTex2Normal;	s_vertBufferDynTex2Normal=0;
};

zCShader* zCRenderManager::GetFreeShader()
{
	if (s_currentShader>=zRENDERMAN_NUM_SHADER)
	{
		zERR_FAULT_ONCE ("D: RNDMAN: too many shaders!");
		s_currentShader=0;
	};
	return &(s_shaderList[s_currentShader++]);
};

zCShaderStage* zCRenderManager::GetFreeShaderStage()
{
	if (s_currentShaderStage>=zRENDERMAN_NUM_SHADER_STAGES)	
	{
		zERR_FAULT_ONCE ("D: RNDMAN: too many shaderStages!");
		s_currentShaderStage=0;
	};
	return &(s_shaderStageList[s_currentShaderStage++]);
};


void zCCFASTCALL zCRenderManager::AddPolyAlphaSimple(zCPolygon *poly)
{
	sceneSimpleAlphaPolyList.InsertEnd(poly);
};

void zCRenderManager::FlushSimpleAlphaPolys()
{
	const zTRnd_AlphaBlendSource	oldBlendSource	= zrenderer->GetAlphaBlendSource();
	const zTRnd_AlphaBlendFunc		oldBlendFunc	= zrenderer->GetAlphaBlendFunc	();
	//const zTRnd_PolyDrawMode		oldDrawMode  	= zrenderer->GetPolyDrawMode	();
	const zBOOL						oldCacheAP		= zrenderer->GetCacheAlphaPolys ();

	zrenderer->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND);
	zrenderer->SetAlphaBlendSource  (zRND_ALPHA_SOURCE_CONSTANT);
	//zrenderer->SetPolyDrawMode		(zRND_DRAW_WIRE);
	zrenderer->SetCacheAlphaPolys   (FALSE);

	for (int ap=0; ap<this->sceneSimpleAlphaPolyList.GetNum(); ap++)
	{
		zrenderer->DrawPoly(sceneSimpleAlphaPolyList[ap]);
	}

	zrenderer->SetAlphaBlendFunc	(oldBlendFunc  );
	zrenderer->SetAlphaBlendSource  (oldBlendSource);
	//zrenderer->SetPolyDrawMode		(oldDrawMode);
	zrenderer->SetCacheAlphaPolys   (oldCacheAP);

	sceneSimpleAlphaPolyList.EmptyList();
};


void zCRenderManager::Flush()
{
	frameCtr++;
	//
	zCRenderManager					::ResetFreeShaderList	();
	zCRndAlphaSortObject_WorldPoly	::ResetFreeList			();

	FlushSimpleAlphaPolys();

	// FIXME: hier vorher noch die Materialien nach deren SortKey sortieren...
	if ((zrenderer->HasCapability(zRND_CAP_TNL)) && (GetUseRendererTNL()))
	{
		zCCamera *cam = zCCamera::activeCam;
		zERR_ASSERT (cam);
		zERR_ASSERT (cam->GetVob());
		zTPlane camPlane;
		camPlane.normal		= cam->GetVob()->GetAtVectorWorld();
		camPlane.distance	= camPlane.normal * cam->GetVob()->GetPositionWorld();

		for (int i=0; i<sceneMaterialList.GetNum(); i++)
		{
			// Material mit AlphaBlend? => als AlphaSortObjects im zCRenderer cachen
			if (sceneMaterialList[i]->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE)
			{
				// MIT AlphaBlend
				// Shader bauen
				zCShader	*shader;
				BuildShader	(sceneMaterialList[i], 0, 0, FALSE, sceneMaterialList[i]->polyList[0]->GetSectorFlag(), shader);

				// Alle Polys der Reihe nach einfuegen
				for (int j=0; j<sceneMaterialList[i]->polyList.GetNum(); j++)
				{
					zCRndAlphaSortObject_WorldPoly	*alphaWorldPoly = zCRndAlphaSortObject_WorldPoly::GetFreeAlphaWorldPoly();
					alphaWorldPoly->poly			= sceneMaterialList[i]->polyList[j];
					alphaWorldPoly->shader			= shader;
					alphaWorldPoly->SetZValueByPoly	(alphaWorldPoly->poly, camPlane);
					zrenderer->AddAlphaSortObject	(alphaWorldPoly);
				};
			} else 
			{
				// OHNE AlphaBlend
				SortMaterialPolys	(sceneMaterialList[i]);
				PackVB				(sceneMaterialList[i]->polyList, 0);
			};

			// Material ist abgearbeitet
			sceneMaterialList[i]->ClearRenderPolyList ();
		};
	} else 
	{
		for (int i=0; i<sceneMaterialList.GetNum(); i++)
		{
			for (int j=0; j<sceneMaterialList[i]->polyList.GetNum(); j++)
				zrenderer->DrawPoly (sceneMaterialList[i]->polyList[j]);
			sceneMaterialList[i]->ClearRenderPolyList ();
		};
	};
	sceneMaterialList.EmptyList();
};

// =======================================================================================================================

static int SortMaterialPolysCompare(const void *arg1, const void *arg2) {
	const zCPolygon* p1 = (*((zCPolygon**)arg1));
	const zCPolygon* p2 = (*((zCPolygon**)arg2));
	// [EDENFELD] Addon: Hier muss nach Lightmap _TEXTUR_ sortiert werden (ansonsten statechange-overkill)
	return (zDWORD(p1->GetLightmap() ? p1->GetLightmap()->Texture() : 0)-zDWORD(p2->GetLightmap() ? p2->GetLightmap()->Texture() : 0));
};


#define MAXSIZE 24
#define d(i) (((char *)data)+(i)*size)

static void InsertionSort_Polys(void *data, size_t num, size_t size, int (__cdecl *compare)(const void *, const void *),bool falltoqs)
{
    char swapplace[MAXSIZE];

   // qsort(data,num,size,compare);
    
    if (size>MAXSIZE)
	{
        qsort(data,num,size,compare);
        return;
    }
     
    int swaps=0;
    for (int i=1;i<(int)num;i++)
	{
        void *lower=d(i);
        for (int j=i-1;j>=0;j--)
		{
            void *upper=lower;
            lower=d(j);
            if ((*compare)(upper,lower) < 0)
			{ 
				// ok. Ist im Moment BubbleSort. Was solls...
                swaps++;
                memcpy(&swapplace,upper,size);
                memcpy(upper,lower,size);
                memcpy(lower,&swapplace,size);
            }
            else
                j=0; // hier kann man die innere Schleife schon abbrechen.
        }
        if (falltoqs && swaps > 5*i+5)
		{
            qsort(data,num,size,compare);
            return;
        }
    }

}


void zCCFASTCALL zCRenderManager::SortMaterialPolys (zCMaterial *mat)
{
	// PolyListe wird so sortiert, das in linearer Abfolge die wenigsten Shader-Wechsel
	// gemacht werden muessen. 
	if (mat->polyListNeedsSort==FALSE) return;

	// Polys sind sortiert nach:
	//   Material | LM | DLM | Z	(Z wegen: Detail | normal | AlphaFadeout)

	// FIXME: schnelleren Sort als qsort benutzen? (STL/Template-Qsort?)
	// [EDENFELD] nun durch Insertion Sort ersetzt
	InsertionSort_Polys (mat->polyList.GetArray(), mat->polyList.GetNum(), sizeof(zCPolygon*), SortMaterialPolysCompare, TRUE);
};

// =======================================================================================================================

void zCCFASTCALL zCRenderManager::BuildShader (
								   zCMaterial		*mat,				// IN
								   zCTexture		*lightmap, 
								   zDWORD			dlightmap,
								   zBOOL			useScratchPadShader,
								   zBOOL			bInSector,
								   zCShader*		&shader				// OUT
								   )
{
	// Hier wird das Material und weitere geforderte Effekte analysiert, 
	// und daraus ein generischer Shader konstruiert.
	static zCShader			internShader;
	static zCShaderStage	internStage[8];
				

	//
	shader					= (useScratchPadShader) ? &internShader : shader = GetFreeShader ();
	shader->Clear			();

	//
	int stageNum			= 0;
	int rendererNumStages	= zrenderer->HasCapability (zRND_CAP_MAX_BLEND_STAGE_TEXTURES);
	int baseTexStageIndex	= 0;
	zCShaderStage *stage;

	//
	zCTexture *baseTex		= mat->GetAniTexture();
	shader->baseTexCachedIn	= (baseTex) ? (baseTex->CacheIn()==zRES_CACHED_IN) : 0;
	shader->hasLightmap		= (lightmap!=0);
	shader->inSector		= bInSector;
	
	if (lightmap)
	{
 		if (rendererNumStages<2)
		{
			//
			baseTexStageIndex				= stageNum;
			stage							= (useScratchPadShader) ? &(internStage[stageNum]) : GetFreeShaderStage();
			stage->Clear					();
			stage->shaderFXMode				= zSHD_FX_BASETEX;
			stage->texture					= baseTex;
			stage->avgTextureColor			= mat->GetColor();
			stage->alphaFunc				= zRND_ALPHA_FUNC_NONE;
			stage->colorFactor				= mat->GetColor();
			stage->tcGen					= zSHD_TCGEN_BASE;
			stage->rgbGen					= zSHD_RGBGEN_VERTEX;
			shader->AddStage				(stage);
			stageNum++;						

			stage							= (useScratchPadShader) ? &(internStage[stageNum]) : GetFreeShaderStage();
			stage->Clear					();
			stage->shaderFXMode				= zSHD_FX_LIGHTMAP;
			stage->texture					= lightmap;
			stage->alphaFunc				= zRND_ALPHA_FUNC_MUL;
			stage->tcGen					= zSHD_TCGEN_LIGHTMAP;
			stage->rgbGen					= zSHD_RGBGEN_VERTEX;
			shader->AddStage				(stage);
			stageNum++;						
		} 
		else 
		{							
			// 1 Pass: [LM+Vertex] * LM 
			stage							= (useScratchPadShader) ? &(internStage[stageNum]) : GetFreeShaderStage();
			stage->Clear					();
			stage->shaderFXMode				= zSHD_FX_LIGHTMAP;
			stage->texture					= lightmap;
			stage->alphaFunc				= zRND_ALPHA_FUNC_NONE;
			stage->tcGen					= zSHD_TCGEN_LIGHTMAP;
			stage->rgbGen					= zSHD_RGBGEN_VERTEX;
			stage->multiTextureNext			= TRUE;
			shader->AddStage				(stage);
			stageNum++;

			baseTexStageIndex				= stageNum;
			stage							= (useScratchPadShader) ? &(internStage[stageNum]) : GetFreeShaderStage();
			stage->Clear					();
			stage->shaderFXMode				= zSHD_FX_BASETEX;
			stage->texture					= baseTex;
			stage->avgTextureColor			= mat->GetColor();
			stage->alphaFunc				= zRND_ALPHA_FUNC_MUL;;
			stage->colorFactor				= mat->GetColor();
			stage->tcGen					= zSHD_TCGEN_BASE;
			stage->rgbGen					= zSHD_RGBGEN_IDENTITY;

			shader->AddStage				(stage);
			stageNum++;
		};
	} 
	else 
	{
		//
		baseTexStageIndex					= stageNum;
		stage								= (useScratchPadShader) ? &(internStage[stageNum]) : GetFreeShaderStage();
		stage->Clear						();
		stage->shaderFXMode					= zSHD_FX_BASETEX;
		stage->texture						= baseTex;
		stage->avgTextureColor				= mat->GetColor();
		stage->alphaFunc					= mat->GetAlphaBlendFunc();
		if (mat->GetMatGroup() == zMAT_GROUP_WATER) 
			stage->alphaGen					= zSHD_ALPHAGEN_WATER;
		else if (mat->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE)
			stage->alphaGen					= zSHD_ALPHAGEN_FACTOR;
		stage->colorFactor					= mat->GetColor();
		stage->tcGen						= zSHD_TCGEN_BASE;
		stage->rgbGen						= zSHD_RGBGEN_VERTEX;
		shader->AddStage					(stage);
		stageNum++;
	};

	// TexGen des Materials nachtragen, falls vorhanden
	if (mat->GetTexAniMapping()) 
	{
		shader->GetStage (baseTexStageIndex)->tcMod				= zSHD_TCMOD_SCROLL;
		shader->GetStage (baseTexStageIndex)->tcModParams[0]	= mat->GetTexAniMappingDir()[VX];
		shader->GetStage (baseTexStageIndex)->tcModParams[1]	= mat->GetTexAniMappingDir()[VY];
	};

	if (overrideAlphaValue<255)
	{
		shader->GetStage (baseTexStageIndex)->alphaFunc			= overrideAlphaBlendFunc;
		shader->GetStage (baseTexStageIndex)->colorFactor.alpha	= overrideAlphaValue;
		shader->GetStage (baseTexStageIndex)->alphaGen			= zSHD_ALPHAGEN_FACTOR;
		//shader->GetStage (baseTexStageIndex)->alphaGen			= zSHD_ALPHAGEN_IDENTITY;
	};


// .. Ab hier nur noch temporaerer TestCode .. 
// .. Ab hier nur noch temporaerer TestCode .. 

	if ((this->S_GetDetailTexturesEnabled()) && (mat) && (mat->GetDetailTexture()))
	{
		// supported der Renderer das benoetigte Feater blendDiffuseAlpha?
		if (!zrenderer->HasCapability (zRND_CAP_BLENDDIFFUSEALPHA))
		{
			this->S_SetDetailTexturesEnabled (FALSE);
		} else
		{
			zCTexture *detailTexture		= mat->GetDetailTexture();

			if (detailTexture->CacheIn()==zRES_CACHED_IN)
			{
				// Detail
				static zCTexture *tex=0;
				stage						= (useScratchPadShader) ? &(internStage[stageNum]) : GetFreeShaderStage();
				stage->Clear				();
				stage->shaderFXMode			= zSHD_FX_DETAIL;
				stage->texture				= detailTexture;
				stage->alphaFunc			= zRND_ALPHA_FUNC_MUL2;
				stage->alphaGen				= zSHD_ALPHAGEN_FACTOR;
//				stage->alphaFunc			= zRND_ALPHA_FUNC_ADD;
//				stage->colorFactor			= zCOLOR(127,127,127,255);
//				stage->colorFactor			= zCOLOR(255,255,255,255);
				stage->colorFactor			= zCOLOR(255,255,255,255);
				stage->rgbGen				= zSHD_RGBGEN_FACTOR;
				stage->tcGen				= zSHD_TCGEN_BASE;
				stage->tcMod				= zSHD_TCMOD_SCALE;
				stage->tcModParams[0]		= 
				stage->tcModParams[1]		= mat->GetDetailTextureScale();
				shader->AddStage			(stage);
				stageNum++;
			};
		};
	};

	if (mat->GetEnvMapEnabled() && zCWorld::S_GetEnvMappingEnabled())
	{
		// env
		static zCOLOR skyFogColor;
		static zCTexture		*tex=0;
		static zCMaterial		*waterMaterial = 0;
		static zCTexture		*waterTexture  = 0;

		if (!bInSector)	skyFogColor = zCSkyControler::GetActiveSkyControler()->GetBackgroundColor();
		else			skyFogColor.SetRGBA(100,100,100,255);

		if (!tex)
		{
			tex			= zCTexture::Load (zoptions->ReadString("ENGINE","zEnvMapTextureName", "zFlare1.tga"));
			waterTexture= zCTexture::Load (zoptions->ReadString("ENGINE","zWaterEnvMapTextureName", "CloudEnv_Bright.tga"));

			waterMaterial=zNEW(zCMaterial);
			waterMaterial->SetTexture(waterTexture);
			waterMaterial->texAniCtrl.SetAniFPS(zoptions->ReadReal("ENGINE","zWaterEnvMapAniFPS", 0));
		}

		stage					= (useScratchPadShader) ? &(internStage[stageNum]) : GetFreeShaderStage();
		stage->Clear			();

		stage->shaderFXMode		= zSHD_FX_BASETEX;
		const float ONE_OVER_255 = 1.0f/255.0f;

		if (mat->GetMatGroup() == zMAT_GROUP_WATER)	stage->texture			= waterMaterial->GetAniTexture();
		else										stage->texture			= tex;
		
		stage->alphaFunc		= zRND_ALPHA_FUNC_BLEND;
		stage->alphaGen			= zSHD_ALPHAGEN_FACTOR;
		stage->colorFactor		= zCOLOR(255,255,255,(zBYTE)(255.0f * mat->GetEnvMapStrength() * skyFogColor.GetIntensityFloat() * ONE_OVER_255));
		stage->tcGen			= zSHD_TCGEN_ENVIRONMENT_FLAT;
		
		if (mat->GetMatGroup() == zMAT_GROUP_WATER)
		{
			stage->tcMod			= zSHD_TCMOD_TURB;
			stage->alphaFunc		= zRND_ALPHA_FUNC_ADD;
			stage->alphaGen			= zSHD_ALPHAGEN_WATER;
		}
		else 
		{
			stage->tcMod			= zSHD_TCMOD_ENVIRONMENT;
		}

		shader->hasTcGenEnv		= TRUE;
		shader->AddStage		(stage);
	};
};

zCVertexBufferDyn2* zCCFASTCALL zCRenderManager::GetFreeDynVertexBuffer (zCShader *shader)
{
	// Hier wird passend zum angegebenen Shader ein dyn. VB herausgegeben.

	// VBs lazy erzeugen
	if (!s_vertBufferDynTex1)
	{ 
		zDWORD vertFormat;
		vertFormat			= zVBUFFER_VERTFORMAT_XYZ		|
							  zVBUFFER_VERTFORMAT_COLOR		|
							  zVBUFFER_VERTFORMAT_TEXUV1;
		s_vertBufferDynTex1	= zNEW(zCVertexBufferDyn2(vertFormat, zRM_NUM_VBUFFER_VERT));

		//
		vertFormat			= zVBUFFER_VERTFORMAT_XYZ		|
							  zVBUFFER_VERTFORMAT_COLOR		|
							  zVBUFFER_VERTFORMAT_TEXUV2;
		s_vertBufferDynTex2	= zNEW(zCVertexBufferDyn2(vertFormat, zRM_NUM_VBUFFER_VERT));

		//
		vertFormat			= zVBUFFER_VERTFORMAT_XYZ		|
							  zVBUFFER_VERTFORMAT_COLOR		|
							  zVBUFFER_VERTFORMAT_NORMAL	|
							  zVBUFFER_VERTFORMAT_TEXUV2;
		s_vertBufferDynTex2Normal= zNEW(zCVertexBufferDyn2(vertFormat, zRM_NUM_VBUFFER_VERT));
	};

	if (shader->hasTcGenEnv)
	{
		return s_vertBufferDynTex2Normal;
	} else 
	if (!shader->GetHasLightmap())
	{
		return s_vertBufferDynTex1;
	} else
	{
		return s_vertBufferDynTex2;
	};
};

// =======================================================================================================================

// State "Abstraktoren"


void zCCFASTCALL zCRenderManager::SetRGBA	(zCShaderStage *stage)
{
	// immer gueltiges setzen
	zrenderer->SetTextureStageState	(0, zRND_TSS_COLORARG1, zRND_TA_TEXTURE);
	zrenderer->SetTextureStageState	(0, zRND_TSS_COLORARG2, zRND_TA_DIFFUSE);

	// spezielle Abgaengigkeiten
	if (hintLightning) {
		zrenderer->SetTextureStageState	(0, zRND_TSS_COLOROP, zRND_TOP_ADDSMOOTH);
		return;
	}
	if (stage->tcGen==zSHD_TCGEN_LIGHTMAP)
	{
		zrenderer->SetTextureStageState	(0, zRND_TSS_COLOROP, zRND_TOP_ADD);
		return;
	} else
	if (stage->alphaGen==zSHD_ALPHAGEN_DETAILFADE)
	{
		zrenderer->SetTextureStageState	(0, zRND_TSS_COLOROP, zRND_TOP_BLENDDIFFUSEALPHA);
		return;
	};

	// den rgbGen fuer den Normalfall auswerten
	switch (stage->rgbGen)
	{
		case zSHD_RGBGEN_IDENTITY:
			zrenderer->SetTextureStageState		(0, zRND_TSS_COLOROP, zRND_TOP_SELECTARG1);
			break;
		case zSHD_RGBGEN_VERTEX:
			zrenderer->SetTextureStageState		(0, zRND_TSS_COLOROP, zRND_TOP_MODULATE);
			break;
		case zSHD_RGBGEN_FACTOR:
			zrenderer->SetTextureStageState		(0, zRND_TSS_COLOROP, zRND_TOP_MODULATE);
			zrenderer->SetRenderState			(zRND_RENDERSTATE_TEXTUREFACTOR, stage->colorFactor);
			break;
		case zSHD_RGBGEN_WAVE:
			zrenderer->SetTextureStageState		(0, zRND_TSS_COLOROP, zRND_TOP_MODULATE);
			/*
				hier wuerden auf einem writeable VB rgb's generiert werden
			*/
			break;
	};
};

void zCCFASTCALL zCRenderManager::SetStageColorOp (const zDWORD hardwareStageIndex, const zTRnd_AlphaBlendFunc alphaFunc)
{
	// evtl. eine LUT draus machen..
	switch (alphaFunc)
	{
	case zRND_ALPHA_FUNC_BLEND:
		zrenderer->SetTextureStageState		(hardwareStageIndex, zRND_TSS_COLOROP, zRND_TOP_BLENDDIFFUSEALPHA);
		break;
	case zRND_ALPHA_FUNC_ADD:
		zrenderer->SetTextureStageState		(hardwareStageIndex, zRND_TSS_COLOROP, zRND_TOP_ADD);
		break;
	case zRND_ALPHA_FUNC_MUL:
		zrenderer->SetTextureStageState		(hardwareStageIndex, zRND_TSS_COLOROP, zRND_TOP_MODULATE);
		break;
	case zRND_ALPHA_FUNC_MUL2:
		zrenderer->SetTextureStageState		(hardwareStageIndex, zRND_TSS_COLOROP, zRND_TOP_MODULATE2X);
		break;
	};
};

void zCCFASTCALL zCRenderManager::SetTextureStage0 (zCShader *shader, zDWORD stageIndex, zCVertexBuffer *vertexBuffer)
{
	zCShaderStage	*stage	= shader->stageList[stageIndex];
	zCTexture		*tex	= (shader->GetBaseTexCachedIn()) ? stage->texture : 0;

	// Basistextur noch nicht vorhanden und Renderer-Lighting aktiv?
	if ((!shader->GetBaseTexCachedIn()) && (vertexBuffer->GetVertexType()==zVBUFFER_VERTTYPE_UT_UL))
	{
		// Materialfarbe setzen, Textur ausschalten
		zCRenderer::zTMaterial		rndMaterial;
		zrenderer->GetMaterial		(rndMaterial);
		rndMaterial.diffuseRGBA[0]	= stage->avgTextureColor.GetRedFloat	();
		rndMaterial.diffuseRGBA[1]	= stage->avgTextureColor.GetGreenFloat	();
		rndMaterial.diffuseRGBA[2]	= stage->avgTextureColor.GetBlueFloat	();

		rndMaterial.ambientRGBA[0]	= rndMaterial.diffuseRGBA[0] * zREAL(0.1F);
		rndMaterial.ambientRGBA[1]	= rndMaterial.diffuseRGBA[1] * zREAL(0.1F);
		rndMaterial.ambientRGBA[2]	= rndMaterial.diffuseRGBA[2] * zREAL(0.1F);

		zrenderer->SetMaterial		(rndMaterial);
		rendererMaterialModified	= TRUE;
	} else
	if (rendererMaterialModified)
	{
		// Materialfarbe zuruecksetzen, Textur benutzen
		zCRenderer::zTMaterial		rndMaterial;
		zrenderer->GetMaterial		(rndMaterial);
		rndMaterial.diffuseRGBA[0]	= 
		rndMaterial.diffuseRGBA[1]	= 
		rndMaterial.diffuseRGBA[2]	=
		rndMaterial.ambientRGBA[0]	= 
		rndMaterial.ambientRGBA[1]	= 
		rndMaterial.ambientRGBA[2]	= 1;
		zrenderer->SetMaterial		(rndMaterial);
		rendererMaterialModified	= FALSE;
	};
	zrenderer->SetTexture		(0, tex);
};

void zCCFASTCALL zCRenderManager::SetTextureTransform(zCShader *shader, zDWORD shaderStageIndex, zDWORD hardwareStageIndex)
{
	/*
		D3DTSS_TEXTURETRANSFORMFLAGS
			D3DTTFF_DISABLE
			D3DTTFF_COUNT2
		D3DTSS_TEXCOORDINDEX
			D3DTSS_TCI_PASSTHRU 
			D3DTSS_TCI_CAMERASPACENORMAL 
			D3DTSS_TCI_CAMERASPACEPOSITION 
			D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR 
		- Matrix setzen
		- Quell-UVs: in Buffer, oder erzeugen
		- Dimension der erzeugten UVs (in der Regel 2)
	*/

	// FIXME: keine redundanten State-Changes!

	zCShaderStage *stage = shader->stageList[shaderStageIndex];
	switch (stage->tcGen)
	{
		case zSHD_TCGEN_BASE:
			zrenderer->SetTextureStageState	(hardwareStageIndex, zRND_TSS_TEXCOORDINDEX, zRND_TSS_TCI_PASSTHRU	| 0);
		break;
		case zSHD_TCGEN_LIGHTMAP:
			zrenderer->SetTextureStageState	(hardwareStageIndex, zRND_TSS_TEXCOORDINDEX, zRND_TSS_TCI_PASSTHRU	| 1);
		break;
		case zSHD_TCGEN_ENVIRONMENT:
			zrenderer->SetTextureStageState	(hardwareStageIndex, zRND_TSS_TEXCOORDINDEX, zRND_TSS_TCI_CAMERASPACENORMAL);
		break;
		case zSHD_TCGEN_ENVIRONMENT_FLAT:
			zrenderer->SetTextureStageState	(hardwareStageIndex, zRND_TSS_TEXCOORDINDEX, zRND_TSS_TCI_CAMERASPACEREFLECTIONVECTOR);
		break;
	};

	if (stage->tcMod==zSHD_TCMOD_NONE)
	{
		zrenderer->SetTextureStageState		(hardwareStageIndex, zRND_TSS_TEXTURETRANSFORMFLAGS	, zRND_TTF_DISABLE);
	} else 
	{
		zMAT4 matrix;
		switch (stage->tcMod)
		{
			case zSHD_TCMOD_SCROLL:
			{
				zVEC2 deltaUV	= zVEC2(stage->tcModParams[0] * ztimer.GetTotalTimeF(),
										stage->tcModParams[1] * ztimer.GetTotalTimeF());
				// damit die UVs im guenstigen Bereich um 0 +/- 1 liegen..
				deltaUV[0]		-= zFloor(deltaUV[0]);
				deltaUV[1]		-= zFloor(deltaUV[1]);
				matrix.MakeIdentity();
				matrix[2][0]	= deltaUV[0];
				matrix[2][1]	= deltaUV[1];
			}
			break;
			case zSHD_TCMOD_ENVIRONMENT:
			{
				matrix[0]	= zVEC4(0.5F, 0.0F, 0.0F, 0);
				matrix[1]	= zVEC4(0.0F, 0.5F, 0.0F, 0);
				matrix[2]	= zVEC4(0.5F, 0.5F, 1.0F, 0);
				matrix[3]	= zVEC4(0   , 0   , 0   , 0);
			};
			break;
			case zSHD_TCMOD_TURB:
				{
				/*matrix[0]	= zVEC4(0.5F, 0.0F, 0.0F, 0);
				matrix[1]	= zVEC4(0.0F, 0.5F, 0.0F, 0);
				matrix[2]	= zVEC4(0.5F, 0.5F, 1.0F, 0);
				matrix[3]	= zVEC4(0   , 0   , 0   , 0);*/

				matrix = zCCamera::activeCam->camMatrix; //* matrix;
				//zCSkyControler::GetActiveSkyControler()->GetGlobalWindVec(windVec,zVISUAL_ANIMODE_WIND);
				//matrix[0][0]+=windVec.Length()/1000;
				//matrix[1][1]+=windVec.Length()/850;
			break;
				}
			case zSHD_TCMOD_SCALE:
			{
				matrix.MakeIdentity();
				matrix[0][0]	= stage->tcModParams[0];
				matrix[1][1]	= stage->tcModParams[1];
			};
			break;
			default:
			break;
		};
		zrenderer->SetTextureStageState			(hardwareStageIndex, zRND_TSS_TEXTURETRANSFORMFLAGS	, zRND_TTF_COUNT2);
		if (hardwareStageIndex==0)
			zrenderer->SetTransform				(zRND_TRAFO_TEXTURE0, matrix);
		else
			zrenderer->SetTransform				(zRND_TRAFO_TEXTURE1, matrix);
	};
};

void zCCFASTCALL zCRenderManager::SetAlphaFunc (zCShader *shader, zDWORD shaderStageIndex, zDWORD hardwareStageIndex)
{
	zCShaderStage *stage = shader->stageList[shaderStageIndex];

	// Das Vorhandensein von Alpha in der Basistexture bestimmt den AlphaArg1 und den AlphaOP
	if ((stage->texture) && (stage->texture->HasAlpha()))
	{
		zrenderer->SetTextureStageState		(hardwareStageIndex, zRND_TSS_ALPHAARG1	, zRND_TA_TEXTURE);
		if (stage->alphaGen==zSHD_ALPHAGEN_IDENTITY)
		{
			// nur bei AlphaGen Ident darf AlphaTesting aktiviert werden (wuerde ansonsten evtl unter den TestRef Wert fallen).
			zrenderer->SetTextureStageState	(hardwareStageIndex, zRND_TSS_ALPHAOP	, zRND_TOP_SELECTARG1);
			stage->alphaFunc				= zRND_ALPHA_FUNC_TEST;
		} else
			zrenderer->SetTextureStageState	(hardwareStageIndex, zRND_TSS_ALPHAOP	, zRND_TOP_MODULATE);
	} else 
	{
		if (stage->alphaGen!=zSHD_ALPHAGEN_WATER) 
		{
			zrenderer->SetTextureStageState		(hardwareStageIndex, zRND_TSS_ALPHAOP	, zRND_TOP_SELECTARG2);
		}
		else
		{
			// ACHTUNG: ist das Wasserfar fading eingeschaltet, wird hier das ColorAlpha angehoben, damit
			// wasser polys potentiell auch komplett opak dargestellt werden können 
			if (zCWorld::GetFadeOutFarVertices() && 
				stage->alphaFunc==zRND_ALPHA_FUNC_BLEND) 
				stage->colorFactor.SetAlphaByte(MIN(255,stage->colorFactor.GetAlphaByte()+50));

			zrenderer->SetTextureStageState		(hardwareStageIndex, zRND_TSS_ALPHAOP	, zRND_TOP_MODULATE);
			zrenderer->SetRenderState			(zRND_RENDERSTATE_TEXTUREFACTOR			, stage->colorFactor);
			zrenderer->SetTextureStageState		(hardwareStageIndex, zRND_TSS_ALPHAARG1	, zRND_TA_TFACTOR);
		}
	};

	// VertexAlpha oder Factor-Alpha im AlphaArg2 ?
	switch (stage->alphaGen)
	{
		case zSHD_ALPHAGEN_IDENTITY:
			break;
		case zSHD_ALPHAGEN_VERTEX:
		case zSHD_ALPHAGEN_WATER:
			zrenderer->SetTextureStageState		(hardwareStageIndex, zRND_TSS_ALPHAARG2	, zRND_TA_DIFFUSE);
			break;
		case zSHD_ALPHAGEN_FACTOR:
			{
			zrenderer->SetRenderState			(zRND_RENDERSTATE_TEXTUREFACTOR			, stage->colorFactor);
			zrenderer->SetTextureStageState		(hardwareStageIndex, zRND_TSS_ALPHAARG2	, zRND_TA_TFACTOR);
			};
			break;
	};

	// zum Schluss die AlphaBlendFunc setzen
	zrenderer->SetAlphaBlendFuncImmed	(stage->alphaFunc);
};

// =======================================================================================================================

void zCCFASTCALL zCRenderManager::DrawVertexBuffer	(
										 zCVertexBuffer *vertexBufferIn,
										 int			firstVert, 
										 int			numVert, 
										 zWORD			*indexList,
										 zDWORD			numIndex,
										 zCMaterial		*material,
										 zBOOL			bInSector)
{
	zCShader			*shader=0;
	BuildShader			(material, 0, 0, TRUE, bInSector, shader);

	DrawVertexBuffer	(vertexBufferIn, firstVert, numVert, indexList, numIndex, shader);
};



void zCCFASTCALL zCRenderManager::DrawVertexBuffer	(
										 zCVertexBuffer *vertexBuffer, 
										 int			firstVert, 
										 int			numVert, 
										 zWORD			*indexList,
										 zDWORD			numIndex,
										 zCShader		*shader)
{
	//
	const zBOOL oldFogEnabled	= zrenderer->GetFog();
	zBOOL zbufferStateChanged		= FALSE;
	//static zBOOL lastTimeWasSector	= FALSE;
	
	//if (lastTimeWasSector != shader->inSector)
	{
		if (shader->inSector) zrenderer->SetFogColor(zCOLOR(0,0,0,255));
		else				  zrenderer->SetFogColor(zCSkyControler::GetActiveSkyControler()->GetActiveSkyControler()->GetBackgroundColor());
	//	lastTimeWasSector = shader->inSector;
	}

	int hintLightningBak = hintLightning;
	hintLightning &= !shader->inSector;


	for (int s=0; s<shader->GetNumStages(); s++) 
	{
		zCShaderStage	*stage	= shader->stageList[s];

		// ZBuffer
		if ((!zbufferStateChanged) && ((s>0) || (stage->alphaFunc!=zRND_ALPHA_FUNC_NONE)) )
		{
			zrenderer->SetZBufferCompare		(zRND_ZBUFFER_CMP_LESS_EQUAL);
			zrenderer->SetZBufferWriteEnabled	(FALSE);
			zbufferStateChanged					= TRUE;
		};

		//

		SetTextureStage0					(shader, s, vertexBuffer);

		
		SetTextureTransform					(shader, s, 0);

		//
		SetAlphaFunc						(shader, s, 0);

		//
		
		SetRGBA								(stage); 

		//
		if (stage->multiTextureNext)
		{
			s++;
			zrenderer->SetTexture				(1, shader->stageList[s]->texture);
			SetTextureTransform					(shader, s, 1);
//			SetAlphaFunc						(shader, s, 1);
			SetStageColorOp						(1, shader->stageList[s]->alphaFunc);

			zrenderer->DrawVertexBuffer			(vertexBuffer, firstVert, numVert, indexList, numIndex);
			zrenderer->SetTextureStageState		(1, zRND_TSS_COLOROP, zRND_TOP_DISABLE);
		} else 
		{
			if (stage->shaderFXMode!=zSHD_FX_DETAIL) 
			{
				zrenderer->DrawVertexBuffer		(vertexBuffer, firstVert, numVert, indexList, numIndex);
			}
			else
			{
//				if (lastVertDetailMap>0)
				// FIXME: konzeptionell gerade machen..
				zrenderer->SetFog				(FALSE);
				zrenderer->SetRenderState		(zRND_RENDERSTATE_TEXTUREFACTOR, zCOLOR(127,127,127,255));
				zrenderer->SetTextureStageState	(0, zRND_TSS_COLOROP	, zRND_TOP_BLENDDIFFUSEALPHA);
				zrenderer->SetTextureStageState	(0, zRND_TSS_COLORARG1	, zRND_TA_TEXTURE);
				zrenderer->SetTextureStageState	(0, zRND_TSS_COLORARG2	, zRND_TA_TFACTOR);
				zrenderer->SetTextureStageState (0, zRND_TSS_ALPHAOP	, zRND_TOP_DISABLE);
//					zrenderer->SetTextureStageState	(0, zRND_TSS_COLOROP, zRND_TOP_ADD);
//					zrenderer->DrawVertexBuffer		(vertexBuffer[bufferConfig.workBuffer], firstVert, lastVertDetailMap-firstVert);

				zrenderer->DrawVertexBuffer		(vertexBuffer, firstVert, numVert, indexList, numIndex);
			} 
		};
	};

	// ZBuffer Mode wiederherstellen, falls modifiziert 
	if (zbufferStateChanged) 
	{
		zrenderer->SetZBufferCompare		(zRND_ZBUFFER_CMP_LESS);
		zrenderer->SetZBufferWriteEnabled	(TRUE);
	}

	// Fog wiederherstellen, falls modifiziert
	if (zrenderer->GetFog()!=oldFogEnabled)
	{
		zrenderer->SetFog(oldFogEnabled);
	};

	hintLightning = hintLightningBak;
};




// schnelles DrawVertexbuffer mit einem Material. Assert: keine n-polys!
// lohnt nur bei meshes/pfx mit grösserer polyanzahl (aber nur einem mat!)
// fixme: man könnte hier auch einen statischen vb einsetzen, wenn man weiss das sich die
// vertices nicht ändern
void	zCCFASTCALL	zCRenderManager::DrawVertexBufferSingleMaterial(const zCArray<zCPolygon*>&polyList, zCShader* shaderIn)
{
	PackVB(polyList, shaderIn);
	return;

	if ( polyList.GetNum()<=0 )						return;

	zCMaterial *mat = polyList[0]->GetMaterial();
	if ( mat->GetTexture()==NULL )					return;

	//
	zCVertexBufferDyn2	*vertexBufferDyn	= 0;
	zCVertexBuffer		*vertexBuffer		= 0;
	enum				{ MAX_VERT_PER_POLY = 64 };
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
	

	zDWORD	startVertIndex;
	int		numVertVB	= 0;

	shaderIn->baseTexCachedIn		= (mat->GetTexture()->CacheIn(0.6F)==zRES_CACHED_IN);
	shaderIn->GetStage(0)->texture	= mat->GetTexture();

	if (shaderIn->baseTexCachedIn)
	{
		for (int i=0; i<polyList.GetNum(); i++)
		{
			zCPolygon *poly = polyList[i];
			// Passt das naechste Poly noch in den Buffer (bzw. ist der Buffer noch gar nicht erstellt worden) ?
			if ((!vertexBufferDyn) || (((vertexBufferDyn->GetNumVert() - (int(startVertIndex) + numVertVB))-int(MAX_VERT_PER_POLY))<3))
			{
				if (vertexBufferDyn)
				{
					vertexBufferDyn->Unlock			(numVertVB);
					zrenderMan.DrawVertexBuffer		(vertexBuffer, startVertIndex, numVertVB, 0, 0, shaderIn);
				} else 
				{
					vertexBufferDyn					= zrenderMan.GetFreeDynVertexBuffer (shaderIn);
					vertexBuffer					= vertexBufferDyn->GetVertexBuffer();
					vertexBuffer->SetPrimitiveType	(zVBUFFER_PT_TRIANGLELIST);
				};

				numVertVB							= 0;
				vertexBufferDyn->ReserveVerts		(MAX_VERT_PER_POLY);
				vertexBufferDyn->Lock				(startVertIndex);
													
				//
				vbStride			= vertexBuffer->arrayStride;
				vbBasePtr			= vertexBuffer->array.basePtr + (vertexBuffer->arrayStride * startVertIndex);
				vbOffsetXYZ			= zDWORD((zBYTE*)vertexBuffer->array.XYZPtr		- (zBYTE*)vertexBuffer->array.basePtr);
				vbOffsetColor		= zDWORD((zBYTE*)vertexBuffer->array.colorPtr	- (zBYTE*)vertexBuffer->array.basePtr);
				vbOffsetTexUV0		= zDWORD((zBYTE*)vertexBuffer->array.texUV0Ptr	- (zBYTE*)vertexBuffer->array.basePtr);
				vbOffsetTexUV1		= zDWORD((zBYTE*)vertexBuffer->array.texUV1Ptr	- (zBYTE*)vertexBuffer->array.basePtr);
			};

			// Verts packen
			
			PACK_VERTEX				(poly->vertex[0]->position	, poly->feature[0]->lightDyn, zVEC2(poly->feature[0]->texu, poly->feature[0]->texv));
			PACK_VERTEX				(poly->vertex[1]->position	, poly->feature[1]->lightDyn, zVEC2(poly->feature[1]->texu, poly->feature[1]->texv));
			PACK_VERTEX				(poly->vertex[2]->position	, poly->feature[2]->lightDyn, zVEC2(poly->feature[2]->texu, poly->feature[2]->texv));
			numVertVB				+= 3;
		};
	};
	if (vertexBufferDyn) vertexBufferDyn->Unlock		(numVertVB);
	if (numVertVB>0)
		zrenderMan.DrawVertexBuffer	(vertexBuffer, startVertIndex, numVertVB, 0, 0, shaderIn);
}

// =======================================================================================================================

inline float CalcAlphaFromDistToPlane (const zTPlane &camPlane, const zPOINT3& pos)
{
	// optimierung: ist die farclipping distanz diesselbe wie die im letzten call, so sparen wir uns eine division

	static float lastZ						= -1;
	static float DETAIL_MAX_DIST			= -1;
	static float ONE_OVER_DETAIL_MAX_DIST	= -1;
	
	if (zCCamera::activeCam->GetFarClipZ()-1000 != DETAIL_MAX_DIST)
	{
		DETAIL_MAX_DIST			= zCCamera::activeCam->GetFarClipZ()-1000;
		if (DETAIL_MAX_DIST<1000) DETAIL_MAX_DIST = 1000;
		ONE_OVER_DETAIL_MAX_DIST= 1.0f/DETAIL_MAX_DIST;
	};	

	zREAL dist		= camPlane.GetDistanceToPlane (pos);
	if (dist<DETAIL_MAX_DIST)
	{
		dist		= dist*2 - DETAIL_MAX_DIST;
		float alpha	= (dist<=0) ? 1 : zREAL(1.0F) - (dist * ONE_OVER_DETAIL_MAX_DIST);
		return alpha;
	} else 
	{
		return 0;
	};
};

// =======================================================================================================================


/* ----------------------------------------------------------------------
	
    zCRenderManager::PackVB()	

	 4.12.2000	[Moos]	
                An neue Lightmap-Datenstruktur angepasst


   ---------------------------------------------------------------------- */


#pragma optimize( "a", on )

void zCCFASTCALL zCRenderManager::PackVB (const zCArray<zCPolygon*> &polyList, zCShader *shaderIn)
{
	// Falls ein Shader ueber 'shaderIn' hereingegeben wird, wird dieser fuer alle Polys benutzt.
	// Falls hingegen 'shaderIn' Null ist, werden dyn. temporaere Shader in Abhaengigkeit der hereinkommenden Polys 
	// generiert (so z.B. auch fuer jeden LM-Wechsel einen neuen Shader).

	// Derzeit wird der statische Level noch komplett 2D/ohne VertexBuffer gerendert. Daher ist kein
	// Clipping durch den Renderer noetig, und wird hier explizit ausgeschaltet, um z.B. bei Karten, die
	// kein Hardware TNL unterstuetzen, schneller zu sein.
	// ZUSATZ: beim Rendern des Levels mit VBs wird hier ersteinmal pauschal das Clipping eingeschaltet. Beim
	// Rendern auf Devices ohne Hardware TNL muesste ueberlegt werden, ob man spaeter im zrenderMan ueber die gesammelten
	// Polys eine Aussage ueber Clipping noetig/nicht noetig machen kann und das Clipping dementsprechend setzt.
	// FALLS vobs ueber diese Methoden kommen wuerden, muessten clipflags reingereicht werden, die hier fuer diese Entscheidung noetig waeren!

	if (zrenderMan.GetUseRendererTNL())
		zrenderer->SetRenderState			(zRND_RENDERSTATE_CLIPPING, TRUE);
	else
		zrenderer->SetRenderState			(zRND_RENDERSTATE_CLIPPING, FALSE);
 
	//
	zERR_ASSERT (polyList.GetNum()>0);
	if (polyList.GetNum()<=0) return;
	zCMaterial *mat		= polyList[0]->GetMaterial();

	//
	int					numVertVB			= 0;
	zCTexture			*lightmapCurrentTex	= (zCTexture* )0x1;  // [Moos] Bei den lms sind nun textur und mapping getrennt. Alle
	zCLightMap			*lightmapCurrentMap	= (zCLightMap*)0x1;  //        Zeilen, die diese beiden Daten verwenden, wurden von mir angepasst.
	zDWORD				dlightmapCurrent	= 0;
	int					matColor[3]			= { mat->color.GetRedByte(), mat->color.GetGreenByte(), mat->color.GetBlueByte() };
//	lastVertDetailMap=0;			
									
	//								
	zBYTE				*vbBasePtr			= 0;
	zDWORD				vbOffsetXYZ			= 0;
	zDWORD				vbOffsetColor		= 0;
	zDWORD				vbOffsetTexUV0		= 0;
	zDWORD				vbOffsetTexUV1		= 0;
	zDWORD				vbStride			= 0;
	
	//
	zCVertexBuffer		*vertexBuffer		= 0;
	zCVertexBufferDyn2	*vertexBufferDyn	= 0;
	zCShader			*shader				= shaderIn;
	zDWORD				startVertIndex		= 2*zRM_NUM_VBUFFER_VERT;	// startIndex im aktuellen Buffer-Fill Run
	enum				{ MAX_VERT_PER_POLY = 64	};					// triangulated verts

	
	for (int i=0; i<polyList.GetNum(); i++)
	{
		zCPolygon	*poly	= polyList[i];
				
		//
		// .. hier der Prefetch-Versuchscode (unter der Methode ausgelagert)..

        // [Moos] Besorge jedenfalls das aktuelle Mapping und die Textur
		zCTexture *lmTex		= NULL;
		lightmapCurrentMap		= NULL;
		if (!shaderIn)
		{
			lightmapCurrentMap   = poly->GetLightmap();
			if (lightmapCurrentMap)
				lmTex = lightmapCurrentMap->Texture();			// hier crash auf bjoerns rechner, version 1.26f
		};

		// Neuen bzw. ersten Shader erstellen ?
		if (lmTex != lightmapCurrentTex /* || DLIGHTMAP */)
		{
			// Falls bereits Daten gepackt wurden: bisherigen Inhalt flushen
			if (vertexBufferDyn)
			{
				vertexBufferDyn->Unlock			(numVertVB);

				DrawVertexBuffer				(vertexBuffer, startVertIndex, numVertVB, 0, 0, shader);
				numVertVB						= 0;
//				lastVertDetailMap				= 0;
			};

			//
			if (shaderIn)
			{
				// Wenn von aussen ein Shader reingegeben wurde, wird dieser brav weiterbenutzt (LM Wechsel sind hier nicht moeglich)
				lightmapCurrentTex	= 0;
			} else 
			{
				lightmapCurrentTex  = lmTex;
				dlightmapCurrent	= 0;
				BuildShader			(mat, lightmapCurrentTex, dlightmapCurrent, TRUE, poly->GetSectorFlag() && !poly->GetPortal(), shader);
			};

			// .. bei einem geaendertem Shader brauchen wir ggfs. auch einen etwas anderen VB
			// (erzeugt keinen Overhead, wenn der VB derselbe bleibt!)
			if (vertexBufferDyn)
			{
				vertexBufferDyn					= GetFreeDynVertexBuffer (shader);
				vertexBuffer					= vertexBufferDyn->GetVertexBuffer();
				zERR_ASSERT						(vertexBuffer);
				if (!vertexBuffer) {			// emergency exit, wie kann soetwas passieren?
					return;
				};
				vertexBuffer->SetPrimitiveType	(zVBUFFER_PT_TRIANGLELIST);
				vertexBufferDyn->ReserveVerts	(MAX_VERT_PER_POLY);

				// .. und den Buffer wieder locken
				if (!vertexBufferDyn->Lock			(startVertIndex))
				{
					zERR_WARNING ( "C: zCRenderManager::PackVB()- vertex buffer lock failed." );
					return;
				};

				//
				zERR_ASSERT			(vertexBuffer->array.basePtr);
				if (!vertexBuffer->array.basePtr) 
				{		// emergency exit, wie kann soetwas passieren?
					vertexBufferDyn->Unlock	(numVertVB);	
					vertexBuffer->Unlock	();
					return;			
				};
				vbStride			= vertexBuffer->arrayStride;
				vbBasePtr			= vertexBuffer->array.basePtr + (vertexBuffer->arrayStride * startVertIndex);
				vbOffsetXYZ			= zDWORD((zBYTE*)vertexBuffer->array.XYZPtr		- (zBYTE*)vertexBuffer->array.basePtr);
				vbOffsetColor		= zDWORD((zBYTE*)vertexBuffer->array.colorPtr	- (zBYTE*)vertexBuffer->array.basePtr);
				vbOffsetTexUV0		= zDWORD((zBYTE*)vertexBuffer->array.texUV0Ptr	- (zBYTE*)vertexBuffer->array.basePtr);
				vbOffsetTexUV1		= zDWORD((zBYTE*)vertexBuffer->array.texUV1Ptr	- (zBYTE*)vertexBuffer->array.basePtr);
			};
		};

		const int vertsInPoly	= ((poly->polyNumVert-2)*3);

		// Passt das naechste Poly noch in den Buffer (bzw. ist der Buffer noch gar nicht erstellt worden) ?
		if (((zRM_NUM_VBUFFER_VERT - (int(startVertIndex) + numVertVB))-MAX_VERT_PER_POLY)<vertsInPoly)
		{
			if (vertexBufferDyn)
			{
				vertexBufferDyn->Unlock			(numVertVB);
				DrawVertexBuffer				(vertexBuffer, startVertIndex, numVertVB, 0, 0, shader);
				vertexBufferDyn->ReserveVerts	(MAX_VERT_PER_POLY);
				if (!vertexBufferDyn->Lock			(startVertIndex))
				{
					zERR_WARNING ( "C: zCRenderManager::PackVB()- vertex buffer lock failed." );
					return;
				};

				
				numVertVB					= 0;
//				lastVertDetailMap			= 0;
			} else 
			{
				vertexBufferDyn					= GetFreeDynVertexBuffer (shader);
				vertexBufferDyn->ReserveVerts	(MAX_VERT_PER_POLY);
			};

			vertexBuffer		= vertexBufferDyn->GetVertexBuffer();
			zERR_ASSERT			(vertexBuffer);
			if (!vertexBuffer) {			// emergency exit, wie kann soetwas passieren?
				return;
			};
			vertexBuffer		->SetPrimitiveType	(zVBUFFER_PT_TRIANGLELIST);
			if (!vertexBufferDyn->Lock(startVertIndex))
			{
				zERR_WARNING ( "C: zCRenderManager::PackVB()- vertex buffer lock failed." );
				return;
			};

			//
			zERR_ASSERT			(vertexBuffer->array.basePtr);
			if (!vertexBuffer->array.basePtr) 
			{			// emergency exit, wie kann soetwas passieren?
				vertexBufferDyn->Unlock	(numVertVB);	
				vertexBuffer->Unlock	();
				return;			
			};
			vbStride			= vertexBuffer->arrayStride;
			vbBasePtr			= vertexBuffer->array.basePtr + (vertexBuffer->arrayStride * startVertIndex);
			vbOffsetXYZ			= zDWORD((zBYTE*)vertexBuffer->array.XYZPtr		- (zBYTE*)vertexBuffer->array.basePtr);
			vbOffsetColor		= zDWORD((zBYTE*)vertexBuffer->array.colorPtr	- (zBYTE*)vertexBuffer->array.basePtr);
			vbOffsetTexUV0		= zDWORD((zBYTE*)vertexBuffer->array.texUV0Ptr	- (zBYTE*)vertexBuffer->array.basePtr);
			vbOffsetTexUV1		= zDWORD((zBYTE*)vertexBuffer->array.texUV1Ptr	- (zBYTE*)vertexBuffer->array.basePtr);
		}

		zERR_ASSERT				(vertexBufferDyn->GetVertexBuffer()==vertexBuffer);

//		int		numVertVBBefore		= numVertVB;
		zBYTE	*vbBasePtrBackup	= vbBasePtr;

		if (lightmapCurrentMap)		// if (lightmapCurrentTex) ?
		{
			
			// [EDENFELD] Patch 2 1.30 Crash Fix Versuch
/*			if (!(vertexBuffer->GetVertexFormat()&zVBUFFER_VERTFORMAT_TEXUV2) || int(vertexBuffer->array.texUV1Ptr)==0)
			{
				vertexBufferDyn->Unlock	(numVertVB);	
				vertexBuffer->Unlock	();
				return;			
			};
*/
			if (shader->baseTexCachedIn)
			{
				// baseTex und lightmap
				for (int j=1; j<poly->polyNumVert-1; j++)
				{
					int k=j+1;
					

					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [0]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= poly->feature[0]->lightDyn;
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[0]->texu);	
					// FIXME: hier crash bei 1.29 laut kundenreports. (lightmaps schrott??)
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV1))	= lightmapCurrentMap->GetLightmapTexCoords(poly->vertex [0]->position);	vbBasePtr += vbStride;

					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [j]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= poly->feature[j]->lightDyn;
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[j]->texu);
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV1))	= lightmapCurrentMap->GetLightmapTexCoords(poly->vertex [j]->position);	vbBasePtr += vbStride;

					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [k]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= poly->feature[k]->lightDyn;
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[k]->texu);
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV1))	= lightmapCurrentMap->GetLightmapTexCoords(poly->vertex [k]->position);	vbBasePtr += vbStride;
				};
			} else 
			{
				// baseTex, lightmap, Textur cachedOut
				for (int j=1; j<poly->polyNumVert-1; j++)
				{
					int k=j+1;
					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [0]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= MulColor (poly->feature[0]->lightDyn, matColor);
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[0]->texu);	
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV1))	= lightmapCurrentMap->GetLightmapTexCoords(poly->vertex [0]->position);	vbBasePtr += vbStride;
					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [j]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= MulColor (poly->feature[j]->lightDyn, matColor);
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[j]->texu);
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV1))	= lightmapCurrentMap->GetLightmapTexCoords(poly->vertex [j]->position);	vbBasePtr += vbStride;
					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [k]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= MulColor (poly->feature[k]->lightDyn, matColor);
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[k]->texu);
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV1))	= lightmapCurrentMap->GetLightmapTexCoords(poly->vertex [k]->position);	vbBasePtr += vbStride;
				};
			};
		} else 
		{
			if (shader->baseTexCachedIn)
			{
				// baseTex
				for (int j=1; j<poly->polyNumVert-1; j++)
				{
					int k=j+1;
					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [0]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= poly->feature[0]->lightDyn;
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[0]->texu);	vbBasePtr += vbStride;
					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [j]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= poly->feature[j]->lightDyn;
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[j]->texu);	vbBasePtr += vbStride;
					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [k]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= poly->feature[k]->lightDyn;
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[k]->texu);	vbBasePtr += vbStride;
				};
			} else
			{
				// baseTex, Textur cachedOut
				for (int j=1; j<poly->polyNumVert-1; j++)
				{
					int k=j+1;
					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [0]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= MulColor (poly->feature[0]->lightDyn, matColor);
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[0]->texu);	vbBasePtr += vbStride;
					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [j]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= MulColor (poly->feature[j]->lightDyn, matColor);
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[j]->texu);	vbBasePtr += vbStride;
					*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= poly->vertex [k]->position;
					*((zCOLOR* )(vbBasePtr + vbOffsetColor))	= MulColor (poly->feature[k]->lightDyn, matColor);
					*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= *(zVEC2*)(&poly->feature[k]->texu);	vbBasePtr += vbStride;
				};
			};
		};

		// VertexNormalen bei Bedarf nachtragen
		if (shader->hasTcGenEnv)
		{
			vbBasePtr				= vbBasePtrBackup;
			zDWORD vbOffsetNormal	= zDWORD((zBYTE*)vertexBuffer->array.normalPtr	- (zBYTE*)vertexBuffer->array.basePtr);

			if (mat->GetMatGroup()!=zMAT_GROUP_WATER)
			{
				for (int j=1; j<poly->polyNumVert-1; j++)
				{
					int k=j+1;
					*((zVEC3* )(vbBasePtr + vbOffsetNormal))	= poly->feature[0]->vertNormal;	vbBasePtr += vbStride;
					*((zVEC3* )(vbBasePtr + vbOffsetNormal))	= poly->feature[j]->vertNormal;	vbBasePtr += vbStride;
					*((zVEC3* )(vbBasePtr + vbOffsetNormal))	= poly->feature[k]->vertNormal;	vbBasePtr += vbStride;
				};
			}
			else
			{
				const zVEC3 vertNormal	= poly->GetNormal()[VY]>0 ? zVEC3(0,1,0) : zVEC3(0,-1,0);
				for (int j=1; j<poly->polyNumVert-1; j++)
				{
					*((zVEC3* )(vbBasePtr + vbOffsetNormal))	= vertNormal;	vbBasePtr += vbStride;
					*((zVEC3* )(vbBasePtr + vbOffsetNormal))	= vertNormal;	vbBasePtr += vbStride;
					*((zVEC3* )(vbBasePtr + vbOffsetNormal))	= vertNormal;	vbBasePtr += vbStride;
				};
			};
		};


		if (mat->GetMatGroup() == zMAT_GROUP_WATER && zCWorld::GetFadeOutFarVertices())
		{
			zTPlane camPlane;
			camPlane.normal		= zCCamera::activeCam->GetVob()->GetAtVectorWorld();
			camPlane.distance	= camPlane.normal * zCCamera::activeCam->GetVob()->GetPositionWorld();

			vbBasePtr				= vbBasePtrBackup;
			zDWORD vbOffsetColor	= zDWORD((zBYTE*)vertexBuffer->array.colorPtr - (zBYTE*)vertexBuffer->array.basePtr);
			zVEC3 view; 
			int newAlpha;

			for (int j=1; j<poly->polyNumVert-1; j++)
			{
				// alpha sightangle fade + farclipping fade
				int k=j+1;
				view = (zCCamera::activeCamPos - poly->vertex[0]->position).NormalizeApprox();
				newAlpha = zFloat2Int((Alg_Rad2Deg(Alg_AngleUnitRad (poly->feature[0]->vertNormal, view))/85.0f) * 255.0f);
				zClamp(newAlpha,90, 255);
				(*((zCOLOR* )(vbBasePtr + vbOffsetColor))).alpha	= zFloat2Int(newAlpha * CalcAlphaFromDistToPlane(camPlane, poly->vertex[0]->position));  vbBasePtr += vbStride;

				view = (zCCamera::activeCamPos-poly->vertex[j]->position).NormalizeApprox();
				newAlpha = zFloat2Int((Alg_Rad2Deg(Alg_AngleUnitRad (poly->feature[j]->vertNormal, view))/85.0f) * 255.0f); 
				zClamp(newAlpha,90, 255);
				(*((zCOLOR* )(vbBasePtr + vbOffsetColor))).alpha	= zFloat2Int(newAlpha * CalcAlphaFromDistToPlane(camPlane, poly->vertex[j]->position));  vbBasePtr += vbStride;

				view = (zCCamera::activeCamPos-poly->vertex[k]->position).NormalizeApprox();
				newAlpha = zFloat2Int((Alg_Rad2Deg(Alg_AngleUnitRad (poly->feature[k]->vertNormal, view))/85.0f) * 255.0f); 
				zClamp(newAlpha,90, 255);
				(*((zCOLOR* )(vbBasePtr + vbOffsetColor))).alpha	= zFloat2Int(newAlpha * CalcAlphaFromDistToPlane(camPlane, poly->vertex[k]->position)); vbBasePtr += vbStride;
			};
		}


		// alphaGen Distanzfade
#ifdef DEBUG_HILDEBRANDT
		if (zCWorld::GetFadeOutFarVertices())
		{
			vbBasePtr				= vbBasePtrBackup;
			zDWORD vbOffsetColor	= zDWORD((zBYTE*)vertexBuffer->array.colorPtr - (zBYTE*)vertexBuffer->array.basePtr);

			//
			zTPlane camPlane;
			camPlane.normal		= zCCamera::activeCam->GetVob()->GetAtVectorWorld();
			camPlane.distance	= camPlane.normal * zCCamera::activeCam->GetVob()->GetPositionWorld();

			//
			for (int j=1; j<poly->polyNumVert-1; j++)
			{
				int k=j+1;
				(*((zCOLOR* )(vbBasePtr + vbOffsetColor))).alpha	= CalcAlphaFromDistToPlane(camPlane, poly->vertex[0]->position);	vbBasePtr += vbStride;
				(*((zCOLOR* )(vbBasePtr + vbOffsetColor))).alpha	= CalcAlphaFromDistToPlane(camPlane, poly->vertex[j]->position);	vbBasePtr += vbStride;
				(*((zCOLOR* )(vbBasePtr + vbOffsetColor))).alpha	= CalcAlphaFromDistToPlane(camPlane, poly->vertex[k]->position);	vbBasePtr += vbStride;
			};
		};
#endif
		//
		numVertVB += vertsInPoly;
	};

	if (!vertexBufferDyn) return;

	vertexBufferDyn->Unlock		(numVertVB);	

	DrawVertexBuffer			(vertexBuffer, startVertIndex, numVertVB, 0, 0, shader);
	
};

#pragma optimize( "a", off )


// =======================================================================================================================

#include <zOption.h>

#pragma warning(disable : 4800) 

// STL
#include <map>
using namespace std;


typedef map<zSTRING,zCMapDetailTexture::zTMapDetailTextureEntry>	zTMapDetailTexture; 
typedef zTMapDetailTexture::value_type								zTMapDetailTextureVal;
typedef zTMapDetailTexture::iterator								zTMapDetailTextureIter;
static  zTMapDetailTexture											s_mapDetailTexture;			// 

void zCMapDetailTexture::S_Init ()
{
	const zSTRING& fileNameComplete = zoptions->GetDirString(DIR_PRESETS) + "detailTexturePresets.txt";
	zFILE *file = zfactory->CreateZFile	(fileNameComplete);

	if (file->Exists())
	{
		zSTRING line;
		zSTRING	objectName;

		file->Open();

		while (!file->Eof())
		{
			zTMapDetailTextureEntry		entry;
			file->Read					(line);

			objectName					= line.PickWord (1, zSTR_SKIP);	objectName.Upper();
			entry.detailTextureName		= line.PickWord (2, zSTR_SKIP); entry.detailTextureName.Upper();
			entry.detailTextureScale	= line.PickWord (3, zSTR_SKIP).ToFloat();

			s_mapDetailTexture.insert	(zTMapDetailTextureVal(objectName, entry));
		};
		file->Close();
	};
	delete file; file=0;
};

void zCMapDetailTexture::S_Cleanup ()
{
};

const zCMapDetailTexture::zTMapDetailTextureEntry*	zCMapDetailTexture::S_GetDetailTextureInfo	(const zSTRING& objectName)
{
	const zTMapDetailTextureIter pos = s_mapDetailTexture.find (objectName);
	if (pos!=s_mapDetailTexture.end())
	{
		// gefunden, aus der map kramen
		return &(s_mapDetailTexture[(*pos).first]);
	} else 
	{
		// nicht gefunden
		return 0;
	};
};

#pragma warning(default : 4800) 


/* netter overbright effekt. mal mit vertex alpha morph spielen

  			zrenderer->SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_ADD);			
			zrenderer->SetTextureStageState( 0, zRND_TSS_ALPHAOP, zRND_TOP_MODULATE);
			zrenderer->SetTextureStageState( 0, zRND_TSS_ALPHAARG1, zRND_TA_TEXTURE);
			zrenderer->SetTextureStageState( 0, zRND_TSS_ALPHAARG2, zRND_TA_DIFFUSE );
			zrenderer->SetTextureStageState( 0, zRND_TSS_COLORARG1, zRND_TA_TEXTURE );
			zrenderer->SetTextureStageState( 0, zRND_TSS_COLORARG2, zRND_TA_DIFFUSE );
*/


// =======================================================================================================================
