 /******************************************************************************** 
 
     $Workfile:: zMaterial.cpp        $                $Date:: 14.02.01 7:28    $
     $Revision:: 22                   $             $Modtime:: 14.02.01 4:29    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/zengin_work/_Dieter/zMaterial.cpp $
 * 
 * 22    14.02.01 7:28 Hildebrandt
 * 
 * 21    12.02.01 17:51 Hildebrandt
 * 
 * 20    8.02.01 21:39 Hildebrandt
 * 
 * 19    22.01.01 20:01 Moos
 * 
 * 18    17.01.01 19:20 Hildebrandt
 * 
 * 17    10.01.01 17:33 Hildebrandt
 * 
 * 16    3.11.00 18:38 Hildebrandt
 * 
 * 15    11.10.00 19:45 Hildebrandt
 * 
 * 14    22.09.00 15:57 Hoeller
 * 
 * 13    1.09.00 18:01 Hildebrandt
 * 
 * 12    21.08.00 17:18 Hildebrandt
 * 
 * 11    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 18    9.08.00 17:12 Admin
 * 
 * 10    21.07.00 15:11 Hildebrandt
 * 
 * 9     6.07.00 13:45 Hildebrandt
 * 
 * 5     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 16    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 14    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 12    10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 11    12/08/99 7:49p Hildebrandt
 * new commandline param: "-zNoTex" => no textures are loaded
 * 
 * 9     12.11.99 22:06 Hildebrandt
 * 
 * 8     12.11.99 21:41 Hildebrandt
 * bugfix for loading multichannel textures
 * 
 * 7     12.11.99 18:42 Hildebrandt
 * 
 * 6     12.11.99 16:57 Hildebrandt
 * 
 * 5     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 22 $ ($Modtime: 14.02.01 4:29 $)

 
/*

Material-Eigenschaften:
	x Material-Gruppe (undef, Holz, Metal, Stein, Erde, Wasser, .. ?)			// was bei Wasser ohne Boden-Grund ?
	  => resultiert in versch. Sounds
		- undef, Holz, Metal, Stein, Erde, Wasser, Glas, Feuer, Rauch,..
	x Sounds (?)
	x Wasser
	x durchsichtig (=alpha)
	- Flag: 'silent'
	- durchgehbar
	- Stroemung (= texMapAni)
*/ 

#include <zCore.h>
#include <zMaterial.h>
#include <zoption.h>
#include <z3d.h>
#include <zArchiver.h>
#include <zRenderManager.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

#ifdef COMPILING_SPACER
	extern zBOOL g_bIsPlayingGame;
#endif

zCLASS_DEFINITION (zCMaterial , zCObject, zCLASS_FLAG_SHARED_OBJECTS, 9)

///////////////////////////////////////////////////////////////////////////
//     Material
///////////////////////////////////////////////////////////////////////////

// static element defs
zBYTE		zCMaterial::s_matUsageDefault	= zCMaterial::zMAT_USAGE_OTHER;

zCMaterial::zCMaterial() {
	InitValues();
};

zCMaterial::zCMaterial(const zSTRING& name) {
	InitValues();
	SetName (name);
};

zCMaterial::zCMaterial(const zCMaterial& sourceMaterial)
{
	InitThisByMaterial(sourceMaterial);
};

zCMaterial& zCMaterial::operator=(const zCMaterial& sourceMaterial)
{
	InitThisByMaterial(sourceMaterial);
	return *this;
};

zCMaterial::~zCMaterial() 
{
	zRELEASE (texture);
	zRELEASE (detailTexture);
	delete	detailObjectVisualName; detailObjectVisualName=0;

	// ptr auf 0
	bspSectorFront		= 0;
	bspSectorBack		= 0;
};

void zCMaterial::InitThisByMaterial (const zCMaterial& sourceMaterial)
{
	InitValues();

	// Der Name darf NICHT kopiert werden, da es sich hier um shared-resource class handelt, bei der
	// alle ObjektNamen eindeutig sein muessen.

	//this->SetName				(sourceMaterial.GetName());
	this->SetTexture			(sourceMaterial.GetTexture());		// inkl. AddRef()
	this->SetColor				(sourceMaterial.GetColor());
	this->SetSmooth				(sourceMaterial.GetSmooth());
	this->SetSmoothAngle		(sourceMaterial.GetSmoothAngle());
	this->SetMatGroup			(sourceMaterial.GetMatGroup());
	this->SetAlphaBlendFunc		(sourceMaterial.GetAlphaBlendFunc());
	this->SetDontUseLightmaps	(sourceMaterial.GetDontUseLightmaps());
	this->SetLODDontCollapse	(sourceMaterial.GetLODDontCollapse());
	this->SetNoCollDet			(sourceMaterial.GetNoCollDet(TRUE));
	
	// [EDENFELD] neu 1.09
	this->SetOccluder			(sourceMaterial.GetOccluder());

	this->SetTexAniMapping		(sourceMaterial.GetTexAniMapping());
	this->SetTexAniMappingDir	(sourceMaterial.GetTexAniMappingDir());
//	this->SetTexScale			(sourceMaterial.GetTexScale());
	this->SetUsage				(sourceMaterial.GetUsage());
	this->SetEnvMapEnabled		(sourceMaterial.GetEnvMapEnabled());
	this->SetEnvMapStrength		(sourceMaterial.GetEnvMapStrength());
	this->SetWaveAniMode		(sourceMaterial.GetWaveAniMode());
	this->SetWaveAniSpeed		(sourceMaterial.GetWaveAniSpeed());
	this->SetWaveGridSize		(sourceMaterial.GetWaveGridSize());
	this->SetWaveMaxAmplitude	(sourceMaterial.GetWaveMaxAmplitude());
	this->SetIgnoreSunLight		(sourceMaterial.GetIgnoreSunLight());
};

void zCMaterial::InitValues () 
{
	// kprea + kd + ks = 1
	kambient				= 0.0F;
	kdiffuse				= 0.9F;
/*	kspecular				= 0.0F;
	kspecularPower			= 1.0F;
	kpreAmbient				= 0.1F;
*/							
	//						
	texture					= 0;
	smooth					= TRUE;
	smoothAngle				= 60.0F;
	libFlag					= 0;
	matUsage				= 0;
	default_mapping			= zVEC2(2.34375,2.34375); 
	texScale				= zPOINT2(1.0F,1.0F);			//  GetTexScale() geht von diesem Default aus..
	bspSectorFront			= 0;
	bspSectorBack			= 0;
	texAniMap				= FALSE;
	texAniMapDelta			= zPOINT2 (0.0F, 0.0F);
	lodDontCollapse			= FALSE;
	noCollDet				= FALSE;
	rndAlphaBlendFunc		= zRND_ALPHA_FUNC_NONE;
	polyListTimeStamp		= 0xFFFFFFFF;
	polyListNeedsSort		= FALSE;
//	sceneMaterialIndex		= 0;
	detailObjectVisualName	= 0;
	detailTexture			= 0;

	// [EDENFELD] neu 1.09
	forceOccluder			= FALSE;
	detailTextureScale		= 1;

	// [EDENFELD] neu 1.11
	m_bEnvironmentalMapping				= FALSE;
	m_bEnvironmentalMappingStrength		= 1.0f;

	// [EDENFELD] neu 1.13
	m_bIgnoreSun						= FALSE;
	
	m_enuWaveMode						= zWAVEANI_NONE;
	m_enuWaveSpeed						= zTFFT_NORMAL;
	m_fWaveMaxAmplitude					= 30;
	m_fWaveGridSize						= 100;


	//
	color.SetRGBA			(150,150,150,255);
	SetUsageFromDefault		();
	SetMatGroup				(zMAT_GROUP_UNDEF);
	SetDontUseLightmaps		(FALSE);
};

void zCMaterial::SetDetailObjectVisual(const zSTRING& name)
{ 
	if (!name.IsEmpty()) 
	{
		if (!detailObjectVisualName)	{
			detailObjectVisualName	= zNEW(zSTRING(name));
		} else {
			(*detailObjectVisualName)= name;	
		};
	}
	else
	{
		delete detailObjectVisualName;
		this->SetDetailTexture		(NULL);
	};
};

const zSTRING& zCMaterial::GetDetailObjectVisual() const
{ 
	if (!detailObjectVisualName)	return zSTR_EMPTY;
	else							return (*detailObjectVisualName);
};

void zCMaterial::ApplyTexAniMapping (zCPolygon *poly) 
{
	if (!texAniMap) return; 

	zREAL	time=  ztimer.GetTotalTimeF();
	zPOINT2 d	= texAniMapDelta * time;
	// damit die UVs im guenstigen Bereich um 0 +/- 1 liegen..
	d[0]		-= zFloor (d[0]);
	d[1]		-= zFloor (d[1]);
	for (int i=0; i<poly->numClipVert; i++) {
		zCVertFeature *feat =  poly->clipFeat[i];
		feat->texu			+= d.n[VX];
		feat->texv			+= d.n[VY];
	};

	// Rotation
/*	zMAT3 mat = Alg_Identity2D();
	mat = Alg_Rotation2D(zVEC2(0.0F,0.0F), 1.0F);
	for (int i=0; i<poly->polyNumVert; i++) {
		zCVertFeature *feat = poly->feature[i];
		zVEC2 v (feat->texu, feat->texv);
		v = mat * v;
		feat->texu = v[VX];
		feat->texv = v[VY];
	};*/
};

/*
If I may generalize your problem a bit, lets assume that your texture has its
origin at some point O with U and V vectors along the unit u and v axes.  So the
texel at (u,v) would be at P = O + u*U + v*V in 3-space.  Now, to determine O,
U, and V from known locations of texels we will need three such points.  So,
suppose we know that (x_i, y_i, z_i) corresponds to the texel (u_i, v_i) for
i=1,2,3.   Then, the equations involving the x-coordinate would be:
    x_i = O_x + u_i*U_x + v_i*V_x  for i=1,2,3.
Three equations and three unknowns.  For your convenience, here is the matrix
form:
[x_1]   [1 u_1 v_1]   [O_x]
[x_2] = [1 u_2 v_2] * [U_x]
[x_3]   [1 u_3 v_3]   [V_x]
Equations in the other coordinates are analogous.
*/

zVEC3 zCMaterial::GetTexAniVector (zCPolygon *poly) 
{
	// Diese Routine berechnet einen Vektor im Koordinatensystem des Polys, der der eingestellten
	// UV-Texture Animation entspricht (z.B. fuer fliessendes Wasser).

	if (!this->GetTexAniMapping()) return zVEC3(0,0,0);

	// FIXME: koennte noch etwas optimiert werden 
	zBOOL	colinear;
	int		n=2;
	do {
		// make sure that the 3 chosen points are not colinear
		colinear = (poly->polyNumVert>3) && 
					Alg_IsColinear (poly->GetVertexPtr(0)->position, 
			  						poly->GetVertexPtr(1)->position,
								    poly->GetVertexPtr(n)->position);
		if (!colinear) break;
		n++;
	} while (n<poly->polyNumVert);
	
	if (n==poly->polyNumVert) return zVEC3(0);

	zVEC3 U,V;
	zVEC3 v, res;
	zMAT3 mat;

	mat[0][0]	= 1;
	mat[1][0]	= 1;
	mat[2][0]	= 1;
	mat[0][1]	= poly->feature[0]->texu;
	mat[1][1]	= poly->feature[1]->texu;
	mat[2][1]	= poly->feature[n]->texu;
	mat[0][2]	= poly->feature[0]->texv;
	mat[1][2]	= poly->feature[1]->texv;
	mat[2][2]	= poly->feature[n]->texv;

    zREAL det;
	mat			= mat.Inverse(&det);

    // [Moos] noch ein Notausgang
    if (det == 0)
        return zVEC3(0);

	for (int i=0; i<3; i++) {
		v		= zVEC3(poly->GetVertexPtr(0)->position[i], poly->GetVertexPtr(1)->position[i], poly->GetVertexPtr(n)->position[i]);
		res		= mat * v;
		U[i]	= res[1];
		V[i]	= res[2];
	};

	//
	res = (-texAniMapDelta[VX]) * U + (-texAniMapDelta[VY]) * V;

/*	if (poly) 
	{
		zPOINT3 center = poly->GetCenter();
		U.Normalize();
		V.Normalize();
		zlineCache.Line3D (center, center + U*50);
		zlineCache.Line3D (center, center + V*50);
	};*/

	return res;
};

zBOOL zCMaterial::IsPortalMaterial () const {
	// "P:" oder "PN:" oder "PI:"

	if (GetName().Length()>=2) 
	if (GetName()[0]=='P')
	{
		 if (GetName()[1]==':') return TRUE;
		 if (GetName().Length()>=3)
		 if ((GetName()[1]=='N') || (GetName()[1]=='I'))
		 if (GetName()[2]==':')
			 return TRUE;
	};
	return FALSE;
};

void zCMaterial::SetTexAniMappingDir (const zPOINT2& dir) {
	texAniMapDelta = dir;
};

void zCMaterial::SetTexture (zSTRING& texName) 
{
	// ** temp ** 
	texName.Upper(); 
	if (texture) {
		if (texName==texture->GetObjectName()) return;
		zRELEASE (texture);
	};
	zCTexture *tex	= zCTexture::Load (texName);	// implicit AddRef()
	SetTexture		(tex);							// implicit AddRef()
	if (tex)
		tex->Release();
};

// { const zBOOL res = SetObjectName (name);	AutoAssignDetailTexture(); return res; };

void zCMaterial::SetTexture (zCTexture *tex) 
{
	if (texture==tex) return;

	// 
	zRELEASE (texture);

	texture = tex;
	if (texture)
	{
		texture->AddRef			();
		AutoAssignDetailTexture	();
	};
};

void zCMaterial::SetDetailTexture	(zSTRING& detailTexName)
{
	if (detailTexture) {
		if (detailTexName==detailTexture->GetObjectName()) return;
		zRELEASE (detailTexture);
	};

	if (detailTexName.IsEmpty()) return;

	zCTexture *tex		= zCTexture::Load (detailTexName);	// implicit AddRef()
	SetDetailTexture	(tex);								// implicit AddRef()
	if (tex)
		tex->Release();
};

void zCMaterial::SetDetailTexture	(zCTexture *detailTex)
{
	if (detailTexture==detailTex) return;

	// 
	zRELEASE (detailTexture);

	detailTexture = detailTex;
	if (detailTexture)
		detailTexture->AddRef	();
};

void zCMaterial::AutoAssignDetailTexture()
{
	// ordnet diesem Material anhand einer Script-Tabelle eine DetailTexture samt Scaling zu 
	if ((this->GetTexture()) && (!this->GetTexture()->GetName().IsEmpty()))
	{
		zCMapDetailTexture::zTMapDetailTextureEntry *objectDetailTexEntry = 0;
		objectDetailTexEntry = const_cast<zCMapDetailTexture::zTMapDetailTextureEntry *>(zCMapDetailTexture::S_GetDetailTextureInfo (this->GetTexture()->GetName()));
		if (objectDetailTexEntry)
		{
			this->SetDetailTexture		(objectDetailTexEntry->detailTextureName);
			this->SetDetailTextureScale	(objectDetailTexEntry->detailTextureScale);
		}
		else if ( NULL != this->detailObjectVisualName )
		{
			this->SetDetailTexture		(*detailObjectVisualName);
			this->SetDetailTextureScale	(detailTextureScale);
		};
	};
};

zPOINT2 zCMaterial::GetTexScale () 
{ 
	if (texture) 
	if (texScale.n[0]==zREAL(1.0F))			// noch uninitialisiert
	{
		// initialisieren
		int xdim, ydim;
		texture->GetPixelSize (xdim, ydim);	// implizites zCTexture::zCResource::CacheIn(-1)
		texScale.n[0] = zREAL(xdim);
		texScale.n[1] = zREAL(ydim);		// FIXME: ???
	};

	return texScale;			
};

void zCMaterial::SetTexScale (const zPOINT2 s) 
{ 
	texScale = s;				
};

void zCMaterial::RemoveTexture () {
	zRELEASE (texture);
};


static const zSTRING s_MatGroupStrings[zMAT_NUM_MAT_GROUP] = 
{
	zSTRING("UNDEF"),
	zSTRING("METAL"),
	zSTRING("STONE"),
	zSTRING("WOOD"),
	zSTRING("EARTH"),
	zSTRING("WATER"),
	zSTRING("SNOW"),
};

const zSTRING&	zCMaterial::GetMatGroupString (const zTMat_Group group) 
{
	switch (group) {
		case zMAT_GROUP_METAL:	return s_MatGroupStrings[zMAT_GROUP_METAL]; break;
		case zMAT_GROUP_STONE:	return s_MatGroupStrings[zMAT_GROUP_STONE]; break;
		case zMAT_GROUP_WOOD:	return s_MatGroupStrings[zMAT_GROUP_WOOD];	break;
		case zMAT_GROUP_EARTH:	return s_MatGroupStrings[zMAT_GROUP_EARTH]; break;
		case zMAT_GROUP_WATER:	return s_MatGroupStrings[zMAT_GROUP_WATER]; break;
		case zMAT_GROUP_SNOW:	return s_MatGroupStrings[zMAT_GROUP_SNOW]; break;
		default:				return s_MatGroupStrings[zMAT_GROUP_UNDEF]; break;
	};
};

const zSTRING& zCMaterial::GetMatGroupString () const {
	return GetMatGroupString(matGroup);
};

void zCMaterial::SetMatGroupByString (const zSTRING& s) 
{
	if (s==s_MatGroupStrings[zMAT_GROUP_METAL])		matGroup = zMAT_GROUP_METAL; else
	if (s==s_MatGroupStrings[zMAT_GROUP_STONE])		matGroup = zMAT_GROUP_STONE; else
	if (s==s_MatGroupStrings[zMAT_GROUP_WOOD])		matGroup = zMAT_GROUP_WOOD ; else
	if (s==s_MatGroupStrings[zMAT_GROUP_EARTH])		matGroup = zMAT_GROUP_EARTH; else
	if (s==s_MatGroupStrings[zMAT_GROUP_WATER])		matGroup = zMAT_GROUP_WATER; else
	if (s==s_MatGroupStrings[zMAT_GROUP_SNOW])		matGroup = zMAT_GROUP_SNOW; else
													matGroup = zMAT_GROUP_UNDEF;
};




void zCMaterial::RefreshAvgColorFromTexture()
{
	if (GetTexture()) 
	{
		zBOOL wasCachedOut	= (GetTexture()->GetCacheState()==zRES_CACHED_OUT);
		// hier wird die AverageColor der Textur als MaterialColor eingetragen
//		zCOLOR col			= tex->GetAverageColor(); 
		zCOLOR col			= GetTexture()->GetTextureInfo().averageColor;		// (implizites CacheIn(-1))
		col.SetAlphaByte	(color.GetAlphaByte());		// alpha retten 
		SetColor			(col);
		if (wasCachedOut)	GetTexture()->CacheOut();
	};
};

void zCMaterial::Archive (zCArchiver &arc) 
{
	zCObject::Archive (arc);
	
	RefreshAvgColorFromTexture();

// FIXME: Strings rauswerfen und Namen kuerzer machen !!!

	//
	arc.WriteString		("name"				, GetName());
	arc.WriteEnum		("matGroup"			, "UNDEF;METAL;STONE;WOOD;EARTH;WATER;SNOW", int(GetMatGroup()));
	arc.WriteColor		("color"			, GetColor());
	arc.WriteFloat		("smoothAngle"		, smoothAngle);
	arc.WriteString		("texture"			, GetTextureName());
	arc.WriteString		("texScale"			, GetTexScale().GetDescription());
	arc.WriteFloat		("texAniFPS"		, texAniCtrl.GetAniFPS());
	arc.WriteEnum		("texAniMapMode"	, "NONE;LINEAR", int(GetTexAniMapping()));
	arc.WriteString		("texAniMapDir"		, GetTexAniMappingDir().GetDescription());
	arc.WriteBool		("noCollDet"		, GetNoCollDet(TRUE));
	arc.WriteBool		("noLightmap"		, GetDontUseLightmaps());
	arc.WriteBool		("lodDontCollapse"	, GetLODDontCollapse());
	arc.WriteString		("detailObject",	  GetDetailObjectVisual());
	arc.WriteFloat		("detailObjectScale", this->detailTextureScale);
	
	arc.WriteBool		("forceOccluder",	  this->forceOccluder);
	arc.WriteBool		("environmentalMapping", this->m_bEnvironmentalMapping);
	arc.WriteFloat		("environmentalMappingStrength", this->m_bEnvironmentalMappingStrength);
	arc.WriteEnum		("waveMode"			 ,"NONE;AMBIENT_GROUND;GROUND;AMBIENT_WALL;WALL;ENV;AMBIENT_WIND;WIND", int(this->m_enuWaveMode));
	arc.WriteEnum		("waveSpeed"		 ,"NONE;SLOW;NORMAL;FAST", int(this->m_enuWaveSpeed));
	arc.WriteFloat		("waveMaxAmplitude"	 ,this->m_fWaveMaxAmplitude);
	arc.WriteFloat		("waveGridSize"		 ,this->m_fWaveGridSize);
	arc.WriteBool		("ignoreSunLight"	 ,this->m_bIgnoreSun);
	arc.WriteEnum		("alphaFunc",		"MAT_DEFAULT;NONE;BLEND;ADD;SUB;MUL;MUL2", int(GetAlphaBlendFunc()));

	arc.WriteGroupBegin	("Internals");
//	arc.WriteByte		("libFlag"			, GetLibFlag());
	arc.WriteRawFloat	("defaultMapping"	, &default_mapping, sizeof(default_mapping));
	arc.WriteGroupEnd	("Internals");
};


void zCMaterial::Unarchive (zCArchiver &arc) {
	zCObject::Unarchive (arc);

	//
	SetName				(arc.ReadString		("name"));
	SetMatGroup			((zTMat_Group)arc.ReadEnum		("matGroup"));
	SetColor			(arc.ReadColor		("color"));
	smoothAngle			=arc.ReadFloat		("smoothAngle");	
	SetSmooth			(smoothAngle>0);
	SetTexture			(arc.ReadString		("texture"));
	texScale			.SetByDescription	(arc.ReadString ("texScale"));
	texAniCtrl.SetAniFPS(arc.ReadFloat		("texAniFPS"));
	SetTexAniMapping	(zBOOL(arc.ReadEnum	("texAniMapMode")));

	//
	zPOINT2 dir; 
	dir.SetByDescription(arc.ReadString		("texAniMapDir"));
	SetTexAniMappingDir (dir);
	
	//
	zBOOL b = FALSE;
	arc.ReadBool		("noCollDet"		, b);	SetNoCollDet		(b);
	arc.ReadBool		("noLightmap"		, b);	SetDontUseLightmaps	(b);

	//
	SetLODDontCollapse					  (arc.ReadBool		("lodDontCollapse"));
	SetDetailObjectVisual				  (arc.ReadString	("detailObject"));
	this->detailTextureScale			 = arc.ReadFloat	("detailObjectScale");

	forceOccluder = arc.ReadBool	("forceOccluder");

	m_bEnvironmentalMapping				 = arc.ReadBool	("environmentalMapping");

	m_bEnvironmentalMappingStrength		 = arc.ReadFloat	("environmentalMappingStrength"	);
	
	m_enuWaveMode = (zTWaveAniMode(arc.ReadEnum	("waveMode")));
	if (int(m_enuWaveMode)>int(zWAVEANI_WIND)) m_enuWaveMode= zWAVEANI_NONE;

	m_enuWaveSpeed						 = zTFFT(arc.ReadEnum	("waveSpeed"));

	arc.ReadFloat   ("waveMaxAmplitude"				, m_fWaveMaxAmplitude				   );
	arc.ReadFloat	("waveGridSize"					, m_fWaveGridSize					   );

	m_bIgnoreSun  = arc.ReadBool	("ignoreSunLight");

	zTRnd_AlphaBlendFunc alphaFunc = zTRnd_AlphaBlendFunc(arc.ReadEnum ("alphaFunc"));
	if (alphaFunc == zRND_ALPHA_FUNC_SUB)
	{
		zERR_WARNING("C: zCMaterial::Unarchive(): material with name" + GetName() + "has subtractive alpha, which is not supported, setting to normal blend mode");
		alphaFunc = zRND_ALPHA_FUNC_BLEND;
	}

	SetAlphaBlendFunc		(alphaFunc);
	
	if (detailTextureScale<0) detailTextureScale = 1;
	
	if ( detailObjectVisualName != NULL  )
	{
		this->SetDetailTexture(*detailObjectVisualName);
	};

	arc.ReadRawFloat	("defaultMapping"	, &default_mapping, sizeof(default_mapping));

	//
	if (color.GetAlphaByte()<255 && GetAlphaBlendFunc() == zRND_ALPHA_FUNC_NONE)
	{
		SetAlphaBlendFunc (zRND_ALPHA_FUNC_BLEND);
	}
};

///////////////////////////////////////////////////////////////////////////
//     Texture-Animation Controller
///////////////////////////////////////////////////////////////////////////

zDWORD zCTexAniCtrl::masterFrameCtr=0;

zCTexAniCtrl::zCTexAniCtrl() {
	aniChannel		= 0;
	actFrame		= aniFPS = 0;
	frameCtr		= -1;
//	SetAniFPS		(0.5); 
//	SetAniChannel	(1);
	SetOneShotAni	(FALSE);
};

void zCTexAniCtrl::AdvanceAni (zCTexture *tex) 
{
	if (aniFPS<=0.0F) return;

	if (frameCtr==masterFrameCtr) return;
	frameCtr = masterFrameCtr;

	// Precaching Strategie
	if (tex->GetCacheState()==zRES_CACHED_OUT)
	{
		tex->PrecacheTexAniFrames();
		actFrame=0;
	} else 
	{
		int numFrames = tex->GetNumAniFrames (aniChannel);

		// FIXME: tritt dieser Fall auf ?? Hey, Leute, sagt mir Bescheid, walls folgendes Assert zutrifft !!
		zERR_ASSERT (numFrames>0);		
		if (numFrames<=0) return;	

		actFrame += aniFPS * ztimer.GetFrameTimeF ();
		if (GetOneShotAni()) {
			if (int(actFrame)>numFrames-1) actFrame = numFrames-1;
		} else {
			while (int(actFrame)>numFrames-1) actFrame -= (numFrames);
		};
	};

	tex->SetActAniFrame (aniChannel, zFloor(actFrame));
};



zCMaterial*	zCMaterial::SearchName (zSTRING& name) 
{
	name.Upper();					// safe
	return (zCMaterial*)GetStaticClassDef()->SearchObject (name);
};


// ============================================================================================================


// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 )