/******************************************************************************** 
 
     $Workfile:: zDecal.cpp     $                $Date:: 27.01.01 19:42   $
     $Revision:: 10                   $             $Modtime:: 27.01.01 14:10   $
       $Author:: Moos                                                           $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Decal
   created: 26.5.2000

 * $Log: /current_work/ZenGin/_Dieter/zDecal.cpp $
 * 
 * 10    27.01.01 19:42 Moos
 * 
 * 9     25.01.01 1:50 Hildebrandt
 * 
 * 8     4.10.00 23:36 Hildebrandt
 * 
 * 7     31.08.00 17:04 Hildebrandt
 * 
 * 6     21.08.00 17:18 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 5     9.08.00 17:12 Admin
 * 
 * 4     21.07.00 14:28 Hildebrandt
 * 
 * 3     11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 2     3.07.00 12:44 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 10 $ ($Modtime: 27.01.01 14:10 $)

// =======================================================================================================================

#include <zCore.h>
#include <z3d.h>
#include <zVisual.h>
#include <zMaterial.h>
#include <zVob.h>
#include <z3d.h>
#include <zArchiver.h>

// =======================================================================================================================

#ifdef ZENGINE_DEBUG
#endif

zCLASS_DEFINITION			( zCDecal			, zCVisual, 0,1)

///////////////////////////////////////////////////////////////////////////
//    Visual : zCDecal
///////////////////////////////////////////////////////////////////////////

zCMesh* zCDecal::decalMesh1Sided = 0;
zCMesh* zCDecal::decalMesh2Sided = 0;

zCDecal::zCDecal() {
	SetDecalDim				(25, 25);
	SetDecal2Sided			(FALSE);
	SetDecalOffset			(0,0);
	
	decalMaterial			= zNEW(zCMaterial());
	ignoreDayLight			= FALSE;
	m_bOnTop				= FALSE;

//	decalMaterial.SetRef	(999999);		// damit das Material nicht zufaellig released wird!
//	decalMaterial.AddRef	();				// damit das Material nicht zufaellig released wird!
//	decalMaterial.SetName	("Z_DECAL"+zSTRING(int(this)));
};

zCDecal::~zCDecal() 
{
	zRELEASE (decalMaterial);
//	zerr.Message ("D: DECAL: numRefs: "+zSTRING(decalMaterial.GetRefCtr()));
//	decalMaterial.SubRef();
//	decalMaterial.SetRef(0);		// damit das Material deleted wird	FIXME: ?????
};

void zCDecal::CleanupDecals () {
	decalMesh2Sided->Poly(0)->material = 0; 
	decalMesh2Sided->Poly(1)->material = 0; 
	decalMesh1Sided->Poly(0)->material = 0; 
	zRELEASE (decalMesh1Sided);
	zRELEASE (decalMesh2Sided);
};

void zCDecal::CreateDecalMeshes () {
	decalMesh1Sided = zCMesh::CreateQuadMesh (FALSE);
	decalMesh2Sided = zCMesh::CreateQuadMesh (TRUE);
	zCOLOR col(255,255,255,255);
	decalMesh1Sided->SetStaticLight	(col);
	decalMesh1Sided->SetLightDyn	(col);
	decalMesh2Sided->SetStaticLight	(col);
	decalMesh2Sided->SetLightDyn	(col);
};

const zSTRING* zCDecal::GetFileExtension (int i)
{
	if (i!=0) return 0;
	static const zSTRING ext(".TGA");
	return &ext;
};

zCVisual* zCDecal::LoadVisualVirtual (const zSTRING& visualName) const
{
	zCDecal *newDecal = zNEW(zCDecal);
	zSTRING s(visualName);
	newDecal->SetTexture (s);
	return newDecal;
};

zDWORD zCDecal::GetRenderSortKey	() const { 
	zERR_ASSERT (decalMaterial);
	return zDWORD(decalMaterial->GetTexture()); 
};	// while rendering vobs they are sorted by their visuals sort-key

// =====================================================================================

void zCDecal::SetTexture (zSTRING& texName) {
	decalMaterial->SetTexture (texName);
};

void zCDecal::SetTexture (zCTexture *texture) {
	decalMaterial->SetTexture (texture);
};

void zCDecal::SetDecalDim (zVALUE xd, zVALUE yd) {
	xdim = xd;
	ydim = yd;
};

// --------------

zBOOL zCDecal::Render (zTRenderContext& renderContext) 
{
	if (decalMaterial->GetTexture()) 
	{
		// Texture-ResCache Precache Strategie
		// Das Rendern von Decals wird solange unterdrueckt, bis die Textur tatsaechlich komplett eingeladen ist
		if (decalMaterial->GetTexture()->CacheIn()!=zRES_CACHED_IN) 
		{
			if (decalMaterial->GetTexture()->GetNumAniFrames(0)>0)
				decalMaterial->GetTexture()->PrecacheTexAniFrames(0.2F);
			return FALSE;
		};
	};
 
	//
	zCMesh *decalMesh;

	if (GetDecal2Sided()) {
		decalMesh = decalMesh2Sided;
		decalMesh->Poly (0)->material = decalMaterial; 
		decalMesh->Poly (1)->material = decalMaterial; 
	} else {
		decalMesh = decalMesh1Sided;
		decalMesh->Poly (0)->material = decalMaterial; 
	};

	// Mesh scalieren
	decalMesh->Vertex (0)->position[VX] = -xdim + xoffset;
	decalMesh->Vertex (0)->position[VY] = +ydim + yoffset;
	decalMesh->Vertex (1)->position[VX] = +xdim + xoffset;
	decalMesh->Vertex (1)->position[VY] = +ydim + yoffset;
	decalMesh->Vertex (2)->position[VX] = +xdim + xoffset;
	decalMesh->Vertex (2)->position[VY] = -ydim + yoffset;
	decalMesh->Vertex (3)->position[VX] = -xdim + xoffset;
	decalMesh->Vertex (3)->position[VY] = -ydim + yoffset;

	// FIXME: RENDER_DECAL !!!!!
	if (renderContext.visualCamAlign==zVISUAL_CAMALIGN_FULL) {
		decalMesh->RenderDecal	(renderContext, m_bOnTop);
		return TRUE;
	} else 
	{
		if (!ignoreDayLight) 
		{
			if (renderContext.vob && renderContext.vob->GetGroundPoly() && renderContext.vob->GetGroundPoly()->GetSectorFlag())
			{
				zCOLOR dayLightCol(100,100,100,255);
				return decalMesh->Render(renderContext, &dayLightCol);
			};
			return decalMesh->Render(renderContext);
		}
		else	
		{
			zCOLOR dayLightCol(255,255,255,255);
			return decalMesh->Render(renderContext, &dayLightCol);
		}
	}
};

/*
int zCDecal::Release () {
	delete this;
	return 0;
};

zCObject* zCDecal::AddRef () {
	return (zCVisual*)this;
};
*/
void zCDecal::SetVisualUsedBy (zCVob* vob) {
	vob->SetIgnoredByTraceRay(TRUE);
};

zTBBox3D zCDecal::GetBBox3D () {
//	zCMesh *decalMesh = GetDecalMesh();
//	zTBBox3D bbox3D = decalMesh->GetBBox3D(); 
	zTBBox3D bbox3D;

	bbox3D.mins[VX] =-xdim + xoffset;
	bbox3D.maxs[VX] = xdim + xoffset;
	bbox3D.mins[VY] =-ydim + yoffset;
	bbox3D.maxs[VY] = ydim + yoffset;
	bbox3D.mins[VZ] = bbox3D.maxs[VZ] = 0;

	return bbox3D;
};

zSTRING zCDecal::GetVisualName () {
	return decalMaterial->GetTextureName();
};


zBOOL	zCDecal::GetAlphaTestingEnabled		()	const						// ATT: evtl. implizites CacheIn()
{ 
	if (!decalMaterial) return FALSE;
	if (decalMaterial->GetAlphaBlendFunc()>zRND_ALPHA_FUNC_BLEND && decalMaterial->GetAlphaBlendFunc()<zRND_ALPHA_FUNC_TEST) return FALSE;
	
	if ( (decalMaterial->GetAlphaBlendFunc()==zRND_ALPHA_FUNC_TEST) ) return TRUE;

	if ( decalMaterial->GetTexture() )
	{
		// implizites CacheIn()
		decalMaterial->GetTexture()->CacheIn(-1);
		if (decalMaterial->GetTexture()->HasAlpha()) return TRUE;
	}

	return FALSE;
};


void zCDecal::DynLightVisual (const zCArray<zCVobLight*>& vobLightList, zMATRIX4 *trafoObjToWorld) { 
//	zCPolygon::LightPolyList (vobLightList, polyList, numPoly, trafoWorldToObj);
	zCOLOR col;
	if (vobLightList.GetNum()==0) {
		col.Reset	();
	} else {
		zPOINT3 posWS;
		if (trafoObjToWorld)	posWS = trafoObjToWorld->GetTranslation();
		else					posWS = 0;
		col = zCVobLight::SumLightsAtPositionWS (vobLightList, posWS);
	};  

// FIXME: HACK 
col.SetRGBA (200,200,200, 255);
	// FIXME: evtl. abh. von der groesse des Decals die die Vertices getrennt beleuchten..

	zCMesh* decalMesh = GetDecalMesh();

	for (int i=0; i<decalMesh->numPoly; i++) {
		zCPolygon *poly = decalMesh->Poly(i);
		poly->feature[0]->lightDyn	= col;
		poly->feature[1]->lightDyn	= col;
		poly->feature[2]->lightDyn	= col;
		poly->feature[3]->lightDyn	= col;
	};
};

void zCDecal::Archive (zCArchiver &arc) {
	zCVisual::Archive (arc);

	//
	arc.WriteString		("name",			decalMaterial->GetTexture() ? decalMaterial->GetTexture()->GetName() : zSTR_EMPTY);
	zVEC2 dim(xdim, ydim);
	zVEC2 ofs(xoffset, yoffset);
	arc.WriteRawFloat	("decalDim"	,		&dim , sizeof(dim));
	arc.WriteRawFloat	("decalOffset",		&ofs, sizeof(ofs));
	arc.WriteBool		("decal2Sided",		GetDecal2Sided());
	arc.WriteEnum		("decalAlphaFunc",	"MAT_DEFAULT;NONE;BLEND;ADD;SUB;MUL;MUL2", int(decalMaterial->GetAlphaBlendFunc()));
	arc.WriteFloat		("decalTexAniFPS",	decalMaterial->texAniCtrl.GetAniFPS());
	arc.WriteByte		("decalAlphaWeight",decalMaterial->GetAlpha());
	arc.WriteBool		("ignoreDayLight",  ignoreDayLight);
};

void zCDecal::Unarchive (zCArchiver &arc) {
	zCVisual::Unarchive (arc);

	//
	zSTRING decalTexName;
	arc.ReadString				("name", decalTexName);
//	decalMaterial.SetTexture	(decalTexName);

	zVEC2 dim,offs;
	arc.ReadRawFloat	("decalDim"	,		&dim, sizeof(dim));
	arc.ReadRawFloat	("decalOffset",		&offs, sizeof(offs));
	xdim	= dim [0]; ydim		= dim [1];
	xoffset	= offs[0]; yoffset	= offs[1];

	SetDecal2Sided		(arc.ReadBool ("decal2Sided"));

	zTRnd_AlphaBlendFunc alphaFunc = zTRnd_AlphaBlendFunc(arc.ReadEnum ("decalAlphaFunc"));
	if (alphaFunc == zRND_ALPHA_FUNC_SUB)
	{
		zERR_WARNING("C: zCDecal::Unarchive(): decal with texname" + decalTexName + "has subtractive alpha, which is not supported, setting to normal blend mode");
		alphaFunc = zRND_ALPHA_FUNC_BLEND;
	}
	decalMaterial->SetAlphaBlendFunc		(alphaFunc);
	decalMaterial->texAniCtrl.SetAniFPS	(arc.ReadFloat ("decalTexAniFPS"));
	zBYTE alpha = 255;
	arc.ReadByte("decalAlphaWeight", alpha);
	decalMaterial->SetAlpha(alpha);
	arc.ReadBool("ignoreDayLight", ignoreDayLight);

};
