/******************************************************************************** 
 
     $Workfile:: zVobLight.cpp        $                $Date:: 10.01.01 17:37   $
     $Revision:: 3                    $             $Modtime:: 10.01.01 17:23   $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   zCVoblight: basic class for light objects (stat/dyn)
   Created:

 * $Log: /current_work/zengin_work/_Dieter/zVobLight.cpp $
 * 
 * 3     10.01.01 17:37 Hildebrandt
 * 
 * 2     3.11.00 19:04 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 3 $ ($Modtime: 10.01.01 17:23 $)

// ============================================================================================================

#include <zCore.h>
#include <zVob.h>
#include <zWorld.h>
#include <zOption.h>
#include <zArchiver.h>
#include <zLensflare.h>
#include <zCollisionObject.h>

// ============================================================================================================

// vob classes, that are explicitly known to the engine
zCLASS_DEFINITION			( zCVobLight		, zCVob			,	0,	5)


// ============================================================================================================

///////////////////////////////////////////////////////////////////////////
//    zCVobLight:	VOB - LIGHT
///////////////////////////////////////////////////////////////////////////

zCArray<zCVobLightPreset*>	zCVobLight::lightPresetList;
#ifdef COMPILING_SPACER
	zBOOL					zCVobLight::renderLightVisuals	= TRUE;		// Spacer: render lightVisuals is default, needed for editing them
	zCMesh*					zCVobLight::s_pLightSphereMesh	= NULL;
#else
	zBOOL					zCVobLight::renderLightVisuals	= FALSE;	// Game: no need to render lightVisuals
#endif

zCVobLight::zCVobLight() {
	// base-class
	SetVobType		(zVOB_TYPE_LIGHT);
	SetCollDetStat	(FALSE);
	SetCollDetDyn	(FALSE);
	SetShowVisual	(TRUE);

	// lightData..

#ifdef COMPILING_SPACER
	m_bShowLightSphere	= FALSE;
#endif
};

zCVobLight::~zCVobLight() 
{
//	RemoveVobFromWorld(); 
	this->affectedPolyMap.RemoveAll();
};

void zCVobLight::CleanupVobLight () 
{
	for (int i=0; i<lightPresetList.GetNum(); i++)
		lightPresetList[i]->Release();
	lightPresetList.DeleteList();
};

void zCVobLight::OnTrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	// turns dynamic light on
	if (GetIsStatic())			return;
	if (lightData.isTurnedOn)	return;
	SetRange					(GetRangeFixed(), FALSE);		// KEIN backup
	lightData.isTurnedOn		= TRUE;
};

void zCVobLight::OnUntrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	// turns dynamic light off
	if (GetIsStatic())			return;
	if (!lightData.isTurnedOn)	return;
	SetRange					(0, FALSE);						// KEIN backup
	lightData.isTurnedOn		= FALSE;
};

void zCVobLight::DoAnimation () 
{
	// a) rangeAni
/*
	if (lightData.rangeAniFPS>0) {
		int numFrames = lightData.rangeAniScaleList.GetNumInList();
		if (numFrames>0) {
			// neue range bestimmen
			zVALUE	floor		= zFloor			(lightData.rangeAniActFrame);
			int		actFrame	= zFloat2Int		(floor);
			zVALUE	scale		= lightData.rangeAniScaleList [actFrame];
			if (lightData.rangeAniSmooth) {
				zVALUE	frac		= lightData.rangeAniActFrame - floor;
				int		nextFrame	= actFrame+1;
				if (nextFrame>=numFrames) nextFrame=0;
				scale = scale + frac * ((lightData.rangeAniScaleList [nextFrame])- scale);
			};
			SetRange (GetRangeFixed() * scale, FALSE);			// KEIN backup

			// frame weiterzaehlen
			lightData.rangeAniActFrame += (lightData.rangeAniFPS) * (ztimer.GetFrameTimeF ());  
			while (zFloor(lightData.rangeAniActFrame)>=numFrames) 
				lightData.rangeAniActFrame -= numFrames;
		};
	};*/
	// b) colorAni 
	if (lightData.colorAniFPS>0) {
		int numFrames = lightData.colorAniList.GetNumInList();
		if (numFrames>0) {
			// neue range bestimmen
			zVALUE	floor		= zFloor		(lightData.colorAniActFrame);
			int		actFrame	= zFloat2Int	(floor);
			zCOLOR	color		= lightData.colorAniList	[actFrame];
			if (lightData.colorAniSmooth) {
				int		intFrac			= zFloat2Int ((lightData.colorAniActFrame - floor)*255.0F);
				int		nextFrame		= actFrame+1;
				if (nextFrame>=numFrames) nextFrame=0;
				zCOLOR	colorNext		= lightData.colorAniList [nextFrame];
				color.LerpRGB (intFrac, color, colorNext);
			};
			SetColor (color);

			// frame weiterzaehlen
			lightData.colorAniActFrame += (lightData.colorAniFPS) * (ztimer.GetFrameTimeF ());  
			while (zFloor(lightData.colorAniActFrame)>=numFrames) 
				lightData.colorAniActFrame -= numFrames;
		};
	};
};

void zCVobLight::SetRange (const zVALUE r, const zBOOL doBackup) 
{
	lightData.SetRange (r, doBackup);
/*	lightData.range = zMax (0.0F,r);
	if (lightData.range>0)	lightData.rangeInv = zVALUE(1.0F) / lightData.range;
	else					lightData.rangeInv = zVALUE_MAX;
*/	
//	zVALUE d = range * 1.4142F;
//	zVALUE d = range * 0.7071F;
	zTBBox3D		bbox3d;
	const zVALUE d	= lightData.range;
	bbox3d.mins		= zPOINT3 (-d,-d,-d); 
	bbox3d.maxs		= zPOINT3 (+d,+d,+d);
	SetBBox3DLocal	(bbox3d); 
	// 
	if (doBackup) {
		// doBackup => 'offizielles' SetRange, nicht aus der DoAni heraus !
//		if (bspTreeNode) bspTreeNode->AdjustVob (this);
		if (GetHomeWorld()) GetHomeWorld()->GetBspTree()->AdjustVob (this);
	};
};

zCOLOR zCVobLight::SumLightsAtPositionWS (const zCArray<zCVobLight*>& vobLightList, const zPOINT3& position, const zBOOL checkOcclusion)
{ 
	if (vobLightList.GetNum()<=0) return zCOLOR(0,0,0,255);

	int	r = 0;
	int	g = 0;
	int	b = 0;

	zCWorld *world	= (checkOcclusion) ? vobLightList[0]->GetHomeWorld() : 0;

	for (int i=0; i<vobLightList.GetNumInList(); i++) {
		zCVobLight *light = vobLightList[i];

		///////////////////////////
		// 1. Distance-Falloff A //
		///////////////////////////

		zVEC3	view	= position - light->GetPositionWorld();
		zVALUE	len		= view.LengthApprox();
		if (len>light->GetRange()) goto dontLightVert;

		// Occlusion testen?
		if (world)
		{
			view = view * zREAL(0.85F);	// den Ray etwas kuerzer machen, um Vobs, die im Level haengen grosszuegiger zu erwischen
			if (world->TraceRayFirstHit (light->GetPositionWorld(), view, (zCArray<zCVob*>*)0, zTRACERAY_VOB_IGNORE))
				continue;
		};

		len = 1-(len * light->GetRangeInv());
		// Farbe des Lichtes durch die Intensitaet skalieren
		{
//			int	intens = int(len*255.0F);
			int	intens = zFloat2Int(len*255.0F);
			r += (((int)light->GetColorR() * intens) >> 8);
			g += (((int)light->GetColorG() * intens) >> 8);
			b += (((int)light->GetColorB() * intens) >> 8);
		};

dontLightVert:;
	};

	// Farbe des Lichtes durch die Intensitaet skalieren
	if (r>255) r = 255;
	if (g>255) g = 255;
	if (b>255) b = 255;

	return zCOLOR(r,g,b,255);
};

void zCVobLight::LoadLightPresets	() 
{
	//
	zoptions->ChangeDir	(DIR_PRESETS);
	zCArchiver *arc = zarcFactory.CreateArchiverRead ("lightPresets.zen");

	if (arc)
	{
		int num = arc->ReadWord ("numVobLightPresets");
		lightPresetList.DeleteList		();
		lightPresetList.AllocAbs		(num);
		lightPresetList.MarkNumAllocUsed();

		for (int i=0; i<lightPresetList.GetNum(); i++) {
			lightPresetList[i]	= static_cast<zCVobLightPreset*>(arc->ReadObject ());
		};

		arc->Close	();
		zRELEASE	(arc);
	};
};

void zCVobLight::SaveLightPresets	() 
{
	zoptions->ChangeDir	(DIR_PRESETS);
	zCArchiver *arc = zarcFactory.CreateArchiverWrite ("lightPresets.zen", zARC_MODE_ASCII);
	if (arc)
	{
		arc->WriteWord ("numVobLightPresets", lightPresetList.GetNumInList());
		for (int i=0; i<lightPresetList.GetNum(); i++) {
			arc->WriteObject (lightPresetList[i]);
		};

		arc->Close	();
		zRELEASE	(arc);
	};
};

void zCVobLight::AddThisToPresetList	(const zSTRING& newPresetName) const 
{
	if (newPresetName.IsEmpty()) return;
	// FIXME: binSearch/Sort ??
	zCVobLightPreset *preset= zNEW(zCVobLightPreset);
	preset->presetName		= newPresetName;
	preset->presetName.Upper();
	preset->lightData		= lightData;

	// replace
	for (int i=0; i<lightPresetList.GetNum(); i++) {
		if (lightPresetList[i]->presetName == preset->presetName) {
			lightPresetList[i]->Release();
			lightPresetList[i] = preset;
			return;
		};
	};
 
	// add
	lightPresetList.Insert	(preset);
};

zBOOL zCVobLight::SetByPreset	(const zSTRING& presetName) {
	if (presetName.IsEmpty()) return FALSE;
	// FIXME: binSearch/Sort ??
	for (int i=0; i<lightPresetList.GetNumInList(); i++) {
		if (lightPresetList[i]->presetName == presetName) {
			lightData			= lightPresetList[i]->lightData;
			lightPresetInUse	= lightPresetList[i]->GetName();
			return TRUE;
		};
	};
	return FALSE;
};

zBOOL zCVobLight::SetByPresetInUse () {
	return SetByPreset (lightPresetInUse);
};

void zCVobLight::Archive (zCArchiver &arc) {
	zCVob::Archive (arc);

	//
	arc.WriteGroupBegin	("VobLight");
	arc.WriteString		("lightPresetInUse",	lightPresetInUse);
	lightData.Archive (arc);
	arc.WriteGroupEnd	("VobLight");
};

void zCVobLight::Unarchive (zCArchiver &arc) {
	zCVob::Unarchive (arc);

	//
	lightPresetInUse	= arc.ReadString		("lightPresetInUse");
	lightData.Unarchive (arc);
};

void zCVobLight::EndMovement(const zBOOL a_bHintTrafoChanged)
{
	// Updates der Pos/Rot/Ausdehnung muessen registriert werden!
	
	if (!GetIsStatic()) 
	{
		if (GetCollisionObject()->HasMoved() && a_bHintTrafoChanged)
		{
			this->affectedPolyMap.RemoveAll();

			for (int i=0; i<this->vobLeafList.GetNum(); i++)
			{
				// teste alle polygone aller leafs in denen sich dieses Licht befindet und trage sie
				// als potentielle kandidaten in die affectedPolyLitList ein
				zCBspLeaf *bspLeaf = vobLeafList[i];

				if (bspLeaf->numPolys<=0) continue;
				
				for (int p=0; p<bspLeaf->numPolys; p++)
				{
					zCPolygon *pPoly= bspLeaf->polyList[p];

					for (int v=0; v<pPoly->polyNumVert; v++)
					{
						if (!zIsGreaterPositive((GetPositionWorld() - pPoly->vertex[v]->position).LengthApprox(), this->GetRange())) 
						{
							int dummyInt = 0;
							this->affectedPolyMap.SetAt(pPoly,dummyInt);
							break;
						}
					};
				}
			};
		};
	};

	zCVob::EndMovement(a_bHintTrafoChanged);
};


void zCVobLight::ThisVobAddedToWorld(zCWorld *homeWorld)
{
	// Updates der Pos/Rot/Ausdehnung muessen registriert werden!
	
	if (!GetIsStatic()) 
	{
		this->affectedPolyMap.RemoveAll();

		for (int i=0; i<this->vobLeafList.GetNum(); i++)
		{
			// teste alle polygone aller leafs in denen sich dieses Licht befindet und trage sie
			// als potentielle kandidaten in die affectedPolyLitList ein
			zCBspLeaf *bspLeaf = vobLeafList[i];

			if (bspLeaf->numPolys<=0) continue;
			
			for (int p=0; p<bspLeaf->numPolys; p++)
			{
				zCPolygon *pPoly= bspLeaf->polyList[p];

				for (int v=0; v<pPoly->polyNumVert; v++)
				{
					if (!zIsGreaterPositive((GetPositionWorld() - pPoly->vertex[v]->position).LengthApprox(), this->GetRange())) 
					{
						int dummyInt = 0;
						this->affectedPolyMap.SetAt(pPoly,dummyInt);
						break;
					}
				};
			}
		};
	};

	zCVob::ThisVobAddedToWorld(homeWorld);
};




void zCVobLightPreset::Archive (zCArchiver &arc) {
	zCObject::Archive		(arc);

	arc.WriteString			("presetName", presetName);
	lightData.Archive		(arc);
};

void zCVobLightPreset::Unarchive (zCArchiver &arc) {
	zCObject::Unarchive			(arc);

	presetName = arc.ReadString	("presetName");
	lightData.Unarchive			(arc);
};

zBOOL zCVobLightData::SetLensFlareFXByName (const zSTRING& lensFlareFXName)
{
	if (lensFlareFXName.Length()<=0)	return TRUE;
	zSTRING name(lensFlareFXName);
	name.Upper();
	zCClassDef *lensClass	= zCLensFlareFX::GetStaticClassDef();
	lensFlareFX				= (zCLensFlareFX*)(lensClass->SearchObject (name));
	lensFlareFXNo			= lensClass->GetIndexByObject (lensFlareFX);
	return (lensFlareFX!=0);
};

const zSTRING& zCVobLightData::GetLensFlareFXName () const
{
	if (lensFlareFX)	return lensFlareFX->GetObjectName();
	else				return zSTR_EMPTY; 
};

void zCVobLightData::Archive (zCArchiver &arc) 
{
	arc.WriteEnum		("lightType"		, "POINT;SPOT;_RES_;_RES_", (int)GetLightType());
	arc.WriteFloat		("range"			, GetRangeFixed());
	arc.WriteColor		("color"			, GetColor());
	arc.WriteFloat		("spotConeAngle"	, GetSpotConeAngle());
	arc.WriteBool		("lightStatic"		, GetIsStatic());
	arc.WriteEnum		("lightQuality"		, "HIGH;MEDIUM;LOW_FASTEST", (int)GetLightQuality());
	arc.WriteString		("lensflareFX"		, GetLensFlareFXName());

	const zBOOL showLightAniProps	= arc.InProperties() || (!GetIsStatic());

	if (showLightAniProps) 
	{
		arc.WriteGroupBegin	("Dynamic Light");

		// DynLight turned on or off ?
		arc.WriteBool		("turnedOn"			, isTurnedOn);

		// rangeani
		zSTRING s;
		for (int i=0; i<rangeAniScaleList.GetNumInList(); i++)
			s += zSTRING(rangeAniScaleList[i],2)+" ";
		arc.WriteString		("rangeAniScale"	, s);
		arc.WriteFloat		("rangeAniFPS"		, GetRangeAniFPS());
		arc.WriteBool		("rangeAniSmooth"	, GetRangeAniSmooth());

		// colorani
		s.Clear();
		for (i=0; i<colorAniList.GetNumInList(); i++) {
			zCOLOR col = colorAniList[i];
			if ((col.r==col.g) && (col.r==col.b))	s += zSTRING(col.r)+" ";
			else									s += "(" + col.GetDescriptionRGB()+ ") ";
		};  
		arc.WriteString		("colorAniList"		, s);
		arc.WriteFloat		("colorAniFPS"		, GetColorAniFPS());
		arc.WriteBool		("colorAniSmooth"	, GetColorAniSmooth());
		arc.WriteBool		("canMove"			, GetCanMove());
		//
		arc.WriteGroupEnd	("Dynamic Light");
	};
};

void zCVobLightData::Unarchive (zCArchiver &arc) 
{
	int					newLightType = int(GetLightType());
	arc.ReadEnum		("lightType", newLightType);
	SetLightType		(zTVobLightType(newLightType));
	SetRange			(arc.ReadFloat		("range"), TRUE);			// ALS BACKUP setzen
	SetColor			(arc.ReadColor		("color"));
	SetSpotConeAngle	(arc.ReadFloat		("spotConeAngle"));
	SetIsStatic			(arc.ReadBool		("lightStatic"));
	SetLightQuality		(zTVobLightQuality(arc.ReadEnum		("lightQuality")));
//	SetLensFlareFXByName(arc.ReadString		("lensflareFXNo"));
	SetLensFlareFXByName(arc.ReadString		("lensflareFX"));

//	SetLensFlareFXByName(zSTRING("GLOW0"));

	const zBOOL readLightAniProps	= arc.InProperties() || (!GetIsStatic());

	if (readLightAniProps)
	{
		// DynLight turned on or off ?
		zBOOL turnedOn	= isTurnedOn;		// default benutzen, falls nicht im archive enthalten
		arc.ReadBool	("turnedOn"			, turnedOn);
		isTurnedOn		= turnedOn;

		// rangeani
		zSTRING arg, n;
		arg					=arc.ReadString		("rangeAniScale");
		rangeAniScaleList.EmptyList();
		if (!arg.IsEmpty())
		{
			int num=-1;
			do {
				n = arg.PickWord (num+2," "," ");
				num++;
			} while (!n.IsEmpty());
			if (num>0) {
				int i=1;
				rangeAniScaleList.AllocAbs (num);
				do {
					n = arg.PickWord (i," "," ");
					if (!n.IsEmpty()) { rangeAniScaleList.Insert (n.ToFloat()); break; };
					i++;
				} while (1);
			};
		} 
		SetRangeAniFPS		(arc.ReadFloat		("rangeAniFPS"));
		SetRangeAniSmooth	(arc.ReadBool		("rangeAniSmooth"));

		// colorani
		arg					=arc.ReadString		("colorAniList");
		colorAniList.EmptyList();
		if (!arg.IsEmpty())
		{
			zCOLOR	col;
			int		i=1;
			do {
				col.Reset();
				n.Clear();
				n = arg.PickWord (i," "," ");
				if (n.Search("(")!=-1) {
					n.Delete			("(", zTSTR_KIND(zSTR_TO));
					col.SetRedByte		(zBYTE(n.ToInt()));	
					col.SetGreenByte	(zBYTE(arg.PickWord (++i," "," ").ToInt()));
					col.SetBlueByte		(zBYTE(arg.PickWord (++i,") ",") ").ToInt()));
					colorAniList.Insert (col);
	//				zerr.Message (col.GetDescription());
				} else 
				if (!n.IsEmpty()) {
					if ((n[0]>='0' && (n[0]<='9')) || (n[0]=='.')) {
						col.SetRGB			(zBYTE(n.ToInt()));
						colorAniList.Insert (col);
					};
				} else
					break;
				i++; 
			} while (1);
		} 
		SetColorAniFPS		(arc.ReadFloat		("colorAniFPS"));
		SetColorAniSmooth	(arc.ReadBool		("colorAniSmooth"));

		// FIXME: optimize!
		zBOOL lightCanMove = GetCanMove();
		arc.ReadBool		("canMove", lightCanMove);
		SetCanMove(lightCanMove);
	};
};

// ----------------------
//  zCVobLight => DATA
// ----------------------

zCVobLightData::zCVobLightData() {
	lightColor.alpha= 255;
	isTurnedOn		= TRUE;

	// Lensflare
	lensFlareFXNo	= -1;
	lensFlareFX		= 0;

	// light-animation
	rangeAniActFrame= 0;
	rangeAniFPS		= 0;
	rangeAniSmooth	= TRUE;
	rangeAniLoop	= FALSE;

	// b) colorAni
	colorAniActFrame= 0;
	colorAniFPS		= 0;
	colorAniSmooth	= TRUE;
	colorAniLoop	= FALSE;
	m_bCanMove		= FALSE;

	// 
	SetWhiteLight	(255);
	SetRange		(0, TRUE);		// 'SetRangeFixed()'
	SetIsStatic		(TRUE);

	SetLightQuality	(zVOBLIGHT_QUAL_HI);
	SetLightType	(zVOBLIGHT_TYPE_POINT);
	SetSpotConeAngle(0);
};

zCVobLightData::~zCVobLightData()
{
	lensFlareFX		= 0;
};

void zCVobLightData::SetRange (const zVALUE r, const zBOOL doBackup) 
{
	range = zMax (0.0F,r);
	if (range>0)	rangeInv = zVALUE(1.0F) / range;
	else			rangeInv = zVALUE_MAX;
	if (doBackup) rangeBackup = range;
};

