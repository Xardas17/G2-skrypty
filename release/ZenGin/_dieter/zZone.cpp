 /******************************************************************************** 
 
     $Workfile:: zZone.cpp            $                $Date:: 24.04.01 17:34   $
     $Revision:: 28                   $             $Modtime:: 17.04.01 19:51   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zZone.cpp $
 * 
 * 28    24.04.01 17:34 Edenfeld
 * Patch 1.08a
 * 
 * 27    29.01.01 17:25 Speckels
 * 
 * 26    29.01.01 15:24 Speckels
 * 
 * 25    8.11.00 18:15 Hildebrandt
 * 
 * 24    3.11.00 19:03 Hildebrandt
 * 
 * 23    3.10.00 15:18 Moos
 * 
 * 22    29.09.00 21:20 Moos
 * 
 * 21    28.09.00 19:19 Hildebrandt
 * 
 * 20    20.09.00 18:40 Hildebrandt
 * 
 * 19    19.09.00 18:20 Pelzer
 * 
 * 18    6.09.00 19:24 Pelzer
 * 
 * 17    1.09.00 18:01 Hildebrandt
 * 
 * 16    31.08.00 17:04 Hildebrandt
 * 
 * 15    29.08.00 18:22 Hildebrandt
 * zCZone::Process..() gets called even if there is just a default zone in
 * the world
 * 
 * 14    29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 13    22.08.00 19:47 Hildebrandt
 * 
 * 12    21.08.00 17:18 Hildebrandt
 * 
 * 11    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 10    6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:48 Hildebrandt
 * zenGin 089c
 * 
 * 9     15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 8     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 6     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 5     13.11.99 1:10 Hildebrandt
 * 
 * 4     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 28 $ ($Modtime: 17.04.01 19:51 $)


#include <zCore.h>
#include <zZone.h>
#include <zWorld.h>
#include <zSky.h>
#include <zArchiver.h>

/*

Problem:
- wie erfaehrt eine Liste von Zones von ihrer Default-Zone ?
	=> zur Zeit fragt die Liste die Welt nach der Default-Zone (lineare Listensuche pro Zone-Klasse)

- ZFog:
	- Planeten, Nebelfarbe bei sehr geringem Nebel daempfen !

- Spacer:
	x bei einem BBox-Update muss auch der zoneBBoxSorter der World geupdatet werden !
	? irgendwie verlieren Zones ihre BBoxen

- Music
	- Zone
		- Tag
			- Standard
			- Threat
		- Nacht
			- Standard
			- Threat
		- Fight
		- FightFast
  dayStandard
  dayThreat
  nightStandard
  nightThreat
  fight
  fightFast

*/

// ============================================================================================================

zCLASS_DEFINITION_ABSTRACT			(zCZone						, zCVob				, 0)
	zCLASS_DEFINITION				(zCZoneReverb				, zCZone			, 0, 0)
		zCLASS_DEFINITION			(zCZoneReverbDefault		, zCZoneReverb		, 0, 0)
	zCLASS_DEFINITION				(zCZoneVobFarPlane			, zCZone			, 0, 0)
		zCLASS_DEFINITION			(zCZoneVobFarPlaneDefault	, zCZoneVobFarPlane	, 0, 0)
	zCLASS_DEFINITION				(zCZoneMusic				, zCZone			, 0, 0)
	zCLASS_DEFINITION				(zCZoneZFog					, zCZone			, 0, 2)
		zCLASS_DEFINITION			(zCZoneZFogDefault			, zCZoneZFog		, 0, 0)
	zCLASS_DEFINITION				(zCVobSound					, zCZone			, 0, 4)
		zCLASS_DEFINITION			(zCVobSoundDaytime			, zCVobSound		, 0, 0)

// ============================================================================================================

///////////////////////////////////////////////////////////////////////////
//    zCBBox3DSorter
///////////////////////////////////////////////////////////////////////////

/* ----------------------------------------------------------------------
	
    zCBBox3DSorterBase::*

	29.09.2000	[Moos]	
                alle vom Template-Format auf dieses umgestellt,
                Verwaltung der Handles hinzugefügt und in zZone.cpp
                verschoben.

   ---------------------------------------------------------------------- */


zCBBox3DSorterBase        *zCBBox3DSorterBase::s_currentSorter;
int                        zCBBox3DSorterBase::s_currentDimension;

zCBBox3DSorterBase::zTBoxSortHandle::~zTBoxSortHandle(){
    if (mySorter)
        mySorter->RemoveHandle(*this);
}

zCBBox3DSorterBase::zCBBox3DSorterBase () {
	sorted = FALSE;
	for (int i=0; i<DIMENSION; i++) {
		nodeList[i].SetCompare (&ArrayCompare);
	};
};

zCBBox3DSorterBase::~zCBBox3DSorterBase () {
    if (s_currentSorter == this)
        s_currentSorter = NULL;
	Clear();
};

int zCBBox3DSorterBase::ArrayCompare (const void* ele1,const void* ele2) {
	typedef zCBBox3DSorterBase::zTNode** zTType;
	if ((*((zTType)ele1))->Value()<((*(zTType)ele2))->Value())	return -1;
	if ((*((zTType)ele1))->Value()>((*(zTType)ele2))->Value())	return +1;
	else													    return  0;
};

void zCBBox3DSorterBase::Clear () {
    int i;
	for (i=0; i<DIMENSION; i++) {
		for (int j=0; j<nodeList[i].GetNum(); j++) {
			delete nodeList[i].Get(j);
		};
		nodeList[i].DeleteList();
	};
	sorted = FALSE;

    for (i=handles.GetNum()-1;i>=0;i--) // [Moos] Clear handles
        handles[i]->ClearActive();
};

void zCBBox3DSorterBase::AllocAbs (int numAlloc) {
	for (int i=0; i<DIMENSION; i++) {
		nodeList[i].AllocAbs			(numAlloc);
//		nodeList[i].MarkNumAllocUsed	();
	};
};

void zCBBox3DSorterBase::Insert (void * inData) 
{
    int i;
	sorted = FALSE;
    zTNode *begin, *end;

	for (i=0; i<DIMENSION; i++) {
		begin	= zNEW(zTNode)(TRUE,inData);
		end		= zNEW(zTNode)(FALSE,inData);
		
		nodeList[i].Insert (begin);
		nodeList[i].Insert (end);
	};

    for (i = handles.GetNum()-1; i>=0;i--) // [Moos] update handles
        if (handles[i]->bbox3D.IsIntersecting(GetBBox(begin)))
            handles[i]->AddActive(inData);
};

void zCBBox3DSorterBase::Remove (void * inData) 
{
    int i;
	for (i=0; i<DIMENSION; i++) {
		int num=0;
		for (int j=0; j<nodeList[i].GetNum(); j++) {
            zTNode *rem=nodeList[i].Get(j); // [Moos]
			if (rem->data==inData) {
				nodeList[i].RemoveOrderIndex (j);
                delete rem;     // [Moos] Leakfix
				j--;
				num++;
				if (num>=2) break;	// begin, end
			};
		};
	};

    for (i = handles.GetNum()-1; i>=0;i--) // [Moos] update handles
        handles[i]->DelActive(inData);
};

void zCBBox3DSorterBase::GetActiveList (const zTBBox3D& bbox3D, zTBoxSortHandle& outHandle) 
{
    s_currentSorter = this; // [Moos]
    outHandle.bbox3D = bbox3D;
    zERR_ASSERT(handles.IsInList(&outHandle));

	if (!sorted)	Sort();

	zCArraySort<void *> workList;
	zCArraySort<void *> outActiveList;
	outHandle.ClearActive();

    int i;
	for (i=0; i<DIMENSION; i++) 
	{
        s_currentDimension = i; // [Moos]

		workList.EmptyList();
		outHandle.indexBegin[i] = nodeList[i].GetNum(); // [Moos] von 0
		outHandle.indexEnd	[i] = 0;
		for (int j=0; j<nodeList[i].GetNum(); j++)
		{
			zTNode* node = nodeList[i].Get(j);

			if (node->Value() > bbox3D.maxs[i])	{
				outHandle.indexEnd[i] = j; 
                break;
			};

			if (node->Value() < bbox3D.mins[i])	{
				outHandle.indexBegin[i] = j+1;  // [Moos] +1 dazu
			};

			if (node->isBegin)	{
				workList.Insert (node->data);
			} else				
			if (node->Value() < bbox3D.mins[i])	{
				workList.Remove (node->data);
			};
		};
		
		//
		if (i==0) {
			outActiveList = workList;
		} else {
			// outActiveList = outActiveList & workList
			for (int k=0; k<outActiveList.GetNum(); k++) {
				for (int l=0; l<workList.GetNum(); l++) {
					if (workList[l]==outActiveList[k]) {
						break;
					};
				};
				if (l>=workList.GetNum()) {
					// not found => remove
					outActiveList.RemoveIndex (k);
					k--;
				};
/*				if (!workList.IsInList (outActiveList[k])) {
					outActiveList.RemoveIndex (k);
					k--;
				};*/
			};
		};
		if (outActiveList.GetNum()<=0) return;
	};

    for (i=outActiveList.GetNum()-1; i>=0; i--){ // [Moos] Speichere die Dinger wirklich
        outHandle.AddActive(outActiveList[i]);
    }
};

void zCBBox3DSorterBase::UpdateActiveList (const zTBBox3D& bbox3D, zTBoxSortHandle& handle) 
{
    s_currentSorter = this; // [Moos]
    handle.bbox3D   = bbox3D;

	if (!sorted)	Sort();

	for (int i=0; i<DIMENSION; i++) 
	{
        s_currentDimension = i; // [Moos]

		for (int j=0; j<2; j++) 
		{
			int		*index;
			zREAL	compareValue;
			if (j==0) {
				 index			= &handle.indexBegin[i];
				 compareValue	= bbox3D.mins[i];
			} else {
				 index			= &handle.indexEnd[i];
				 compareValue	= bbox3D.maxs[i];
			};

			const zCArraySort<zTNode*>&	actList = nodeList[i];

			zBOOL movedRight=FALSE;

            if (*index < 0)  // [Moos] clamp
                index = 0;
            if (*index > actList.GetNum())
                *index = actList.GetNum();

			// rechts ?
//			while ((actList.GetNum()>*index+1) && (actList[*index+1]->value<compareValue)) {
			while ((*index)<actList.GetNum() && actList[*index]->Value()<compareValue) { // [Moos] Randtest wieder dazu
				// ungleiches begin/end ?
				if (j==actList[*index]->isBegin) {
					if (j==0)	handle.DelActive(actList[*index]->data); else
						if (bbox3D.IsIntersecting(GetBBox(actList[*index])))
						    handle.AddActive(actList[*index]->data);
				};
				(*index)++;

				movedRight = TRUE;
			};

			// links ?
//			while ((*index>0) && (actList[*index-1]->value>compareValue)) {
			if (!movedRight)
			while (*index > 0 && actList[*index-1]->Value()>compareValue) {  // [Moos] Randtest und -1-Verschiebung wieder dazu
				// ungleiches begin/end ?
				(*index)--;
				if (j==actList[*index]->isBegin) {
					if (j==1)	handle.DelActive(actList[*index]->data); else
						if (bbox3D.IsIntersecting(GetBBox(actList[*index])))
							handle.AddActive(actList[*index]->data);
				};
			};
		};
	};
};

void zCBBox3DSorterBase::InsertHandle (zTBoxSortHandle &handle){
    zERR_ASSERT(!handle.mySorter);
    handle.mySorter = this;

    handles.Insert(&handle);
    GetActiveList(handle.bbox3D, handle); 
}

void zCBBox3DSorterBase::RemoveHandle (zTBoxSortHandle &handle){
    zERR_ASSERT(handle.mySorter == this);
    handle.mySorter = NULL;

    handles.Remove(&handle);
    handle.ClearActive();
}


void zCBBox3DSorterBase::Sort () 
{
    s_currentSorter = this; // [Moos]
	sorted = TRUE;
	for (int i=0; i<DIMENSION; i++) {
        s_currentDimension = i; // [Moos] damit das neue ArrayCompare richtig funktionniert
		nodeList[i].QuickSort ();
	};
};

void zCBBox3DSorterBase::AdjustSorting (zCArraySort<zTNode*> &list, const int listIndex)
{
	// "insertion sort": sortiert in der Liste ein fast korrekt sortiertes Element durch verschieben neu
	const zREAL	sortValue	= list[listIndex]->Value();	
	int			newIndex	= listIndex;
	if ((newIndex>0) && (list[newIndex-1]->Value()>sortValue))
	{
		// Position links suchen
		do {
			zSwap (list[newIndex], list[newIndex-1]);
			--newIndex;
		} while ((newIndex>0) && (list[newIndex-1]->Value()>sortValue));
	} else 
	if ((newIndex<list.GetNum()-1) && (list[newIndex+1]->Value()<sortValue))
	{
		// Position rechts suchen
		do {
			zSwap (list[newIndex], list[newIndex+1]);
			++newIndex;
		} while ((newIndex<list.GetNum()-1) && (list[newIndex+1]->Value()<sortValue));
	};
};

void zCBBox3DSorterBase::Update (void *inData)
{
	// Methode erwartet eine sortierte Liste. Falls sie nicht bereits sortiert ist,
	// wird sie ggfs. erst noch sortiert (sollte allerdings SEHR selten/kaum vorkommen!).
	if (!sorted)	Sort();
    s_currentSorter = this; // [Moos]

	int i,num=0;
	// [EDENFELD] 1.09 NullPtr. Crash behoben (Spacer insert zCZoneFog Crash)
    zTNode *node=0;

	for (i=0; i<DIMENSION; i++) {
        s_currentDimension = i; // [Moos] damit Value() den richtigen Wert zurückgibt


		for (int j=0; j<nodeList[i].GetNum(); j++) 
		{
			node = nodeList[i].Get(j);
			if (node->data == inData) {
//				if (node->isBegin)	node->value = bbox3D.mins[i]; // [Moos] wird hier nicht mehr gebraucht
//				else				node->value = bbox3D.maxs[i];

				AdjustSorting (nodeList[i], j);
				num++;
				if (num==2) break;
			};
		};
	};

    // [Moos] Update auf die handles anwenen

	// [EDENFELD] 1.09 NullPtr. Crash behoben (Spacer insert zCZoneFog Crash)
	if (node != NULL)
    for (i = handles.GetNum()-1;i>=0; i--){
        if (GetBBox(node).IsIntersecting(handles[i]->bbox3D))
            handles[i]->AddActive(inData);
        else
            handles[i]->DelActive(inData);
    }
};


///////////////////////////////////////////////////////////////////////////
//    zCZone
///////////////////////////////////////////////////////////////////////////

zCZone::zCZone() 
{
	world			= 0;
	SetZoneVobFlags	();
};

zCZone::~zCZone() 
{
	// muss hier bereits geschehen, im ~zCVob ist die Klasse 'zCZone' nicht mehr ermittelbar
	// FIXME: uuhh... keine virtual Calls in Destruktoren!!!
	if (world)	world->RemoveVobFromLists(this);	
	world = 0;
};

void zCZone::ThisVobAddedToWorld	 (zCWorld *homeWorld) 
{
	zCVob::ThisVobAddedToWorld		(homeWorld);
	world = homeWorld;
};

void zCZone::ThisVobRemovedFromWorld (zCWorld *homeWorld) 
{
	zCVob::ThisVobRemovedFromWorld	(homeWorld);
	world = 0;
};

void zCZone::EndMovement (const zBOOL a_bHintTrafoChanged) 
{
	// Updates der Pos/Rot/Ausdehnung muessen registriert werden!
	zCVob::EndMovement(a_bHintTrafoChanged);
	if (world)	world->UpdateZone (this);
};

zREAL zCZone::GetCamPosWeight () 
{
	zERR_ASSERT (zCCamera::activeCam);
	zERR_ASSERT (zCCamera::activeCam->GetVob());
	const zTBBox3D&	box		= GetBBox3DWorld();
	const zPOINT3&	camPos	= zCCamera::activeCam->GetVob()->GetPositionWorld();
	zVEC3			rel		= camPos - box.GetCenter();

	zVEC3			scale	= (box.maxs-box.mins) * zREAL(0.5F);
	for (int i=0; i<3; i++) {
		if (scale[i]<=0) return 0;						// sollte eigentlich nicht passieren..
		scale[i]		= zREAL(1.0) / scale[i];
	};

	zREAL dist			= Alg_Prod	(rel, scale).LengthApprox();
//	zREAL dist			= Alg_Prod	(rel, scale).Length2();
	if (dist>1.0F) dist = 1.0F;
	return dist;
};

void zCZone::SetZoneVobFlags()
{
	SetCollDet				(FALSE);
	SetIgnoredByTraceRay	(TRUE);
};

void zCZone::Unarchive (zCArchiver& arc)
{
	zCVob::Unarchive	(arc);
	SetZoneVobFlags		();
};

zSTRING zCZone::GetDebugDescString ()
{
	return zSTRING("weight: ")+zSTRING(GetCamPosWeight(),2);
};

///////////////////////////////////////////////////////////////////////////
//    zCZoneZFog
///////////////////////////////////////////////////////////////////////////

zCZoneZFog::zCZoneZFog() {
	fogRangeCenter	= 3000.0F;
	innerRangePerc	= 0.7F;
	fogColor		= zCOLOR(120,120,120,255);
	bFadeOutSky		= FALSE;
	bOverrideColor	= FALSE;
};

zREAL zCZoneZFog::GetActiveRange (const zREAL fogRangeDefault) {
	zREAL dist = GetCamPosWeight();
	if (dist<innerRangePerc)	dist = 0;
	else						dist = (dist - innerRangePerc) / (1.0F - innerRangePerc);

	zREAL range	= fogRangeCenter + dist*(fogRangeDefault-fogRangeCenter);

	return range;
};


zREAL zCZoneZFog::GetSkyFadeWeight() 
{
	zREAL dist = GetCamPosWeight();
	if (dist<innerRangePerc)	dist = 0;
	else						dist = (dist - innerRangePerc) / (1.0F - innerRangePerc);
	return dist;
};


zCClassDef*	zCZoneZFog::GetDefaultZoneClass	() const { 
	return zCZoneZFogDefault::GetStaticClassDef();	
};

void zCZoneZFog::ProcessZoneList (const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld) 
{
	// es gibt nichts zu tun, falls es nur 1 Default-Zone exsitiert (this)
	if ((zoneList.GetNum()==0) && (zoneDeactivateList.GetNum()==0)) return;

	zREAL	fadeOutSkyWeight		= 0;
	zREAL	fadeOutColorWeight		= 0;
	zCOLOR	backGroundColor			= homeWorld->GetActiveSkyControler()->GetBackgroundColorDef();
	zREAL   dayWeight				= (backGroundColor.GetIntensityFloat()/255.0f)*3;
	zREAL	avgRed					= 0;
	zREAL	avgGreen				= 0;
	zREAL	avgBlue					= 0;

	int		numFogZonesModColor		= 0;			
	int     numFogZonesModSkyWeight = 0;

	// default Range ermitteln
	zCZone *zoneDefault		= homeWorld->SearchZoneDefaultByClass (zCZoneZFogDefault::GetStaticClassDef());
	zClamp(dayWeight, 0.1f, 1.0f);


	zREAL	def;
	if (zoneDefault)	def = ((zCZoneZFog*)zoneDefault)->fogRangeCenter;
	else				def = homeWorld->GetActiveSkyControler()->GetFarZ ();

	// aktuelle Range ermitteln
	zREAL range=0;
	if (zoneList.GetNum()<=0) {
		// Keine Zones vorhanden ? (nur evtl. deaktive zones..)
		range = def;
	} else {
		for (int i=0; i<zoneList.GetNum(); i++) {
			zCZoneZFog	*zone	= ((zCZoneZFog*)zoneList[i]);
			range				+= zone->GetActiveRange(def);
			zREAL zoneWeight	= zone->GetSkyFadeWeight();

			if (zone->GetFadeOutSky())
			{
				numFogZonesModSkyWeight ++;
				fadeOutSkyWeight	+= zoneWeight;
			}
			if (zone->GetFadeOutSkyColor())
			{
				numFogZonesModColor ++;
				zREAL zw = 1-zoneWeight;
				avgRed				+= zw * zREAL(zone->GetFogColor().GetRedByte  ());
				avgGreen			+= zw * zREAL(zone->GetFogColor().GetGreenByte());
				avgBlue				+= zw * zREAL(zone->GetFogColor().GetBlueByte ());
				fadeOutColorWeight	+= zw;
			};
		};
		range	/= zREAL(zoneList.GetNum());
	};

	// Range setzen
	homeWorld->GetActiveSkyControler()->SetFarZ (range);

	// override farbe setzen, falls nötig
	if (numFogZonesModColor>=1)
	{
		zVEC3 overrideColor((avgRed*dayWeight)/numFogZonesModColor, (avgGreen*dayWeight)/numFogZonesModColor, (avgBlue*dayWeight)/numFogZonesModColor);	
		zVEC3 origColor    (backGroundColor.GetRedByte(), backGroundColor.GetGreenByte(), backGroundColor.GetBlueByte());

		homeWorld->GetActiveSkyControler()->SetOverrideColor	(zLerp(zSinusEase(fadeOutColorWeight/numFogZonesModColor), origColor, overrideColor));
		homeWorld->GetActiveSkyControler()->SetOverrideColorFlag(TRUE);
	}
	else homeWorld->GetActiveSkyControler()->SetOverrideColorFlag(FALSE);

	// sky fading aktivieren falls gewünscht
	if (numFogZonesModSkyWeight==0)	homeWorld->GetActiveSkyControler()->SetGlobalSkyScale(1);
	else							homeWorld->GetActiveSkyControler()->SetGlobalSkyScale(zSinusEase(fadeOutSkyWeight/numFogZonesModSkyWeight));
};

void zCZoneZFog::Archive (zCArchiver& arc) {
	zCZone::Archive	(arc);

	//
	arc.WriteGroupBegin		("ZoneZFog");
	arc.WriteFloat			("fogRangeCenter"	,	fogRangeCenter);
	arc.WriteFloat			("innerRangePerc"	,	innerRangePerc);
	arc.WriteColor			("fogColor"			,	fogColor);
	arc.WriteBool			("fadeOutSky"		,	bFadeOutSky);
	arc.WriteBool			("overrideColor"	,	bOverrideColor);

	arc.WriteGroupEnd		("ZoneZFog");
};

void zCZoneZFog::Unarchive (zCArchiver& arc) {
	zCZone::Unarchive	(arc);

	//
	arc.ReadFloat			("fogRangeCenter"	,	fogRangeCenter);
	arc.ReadFloat			("innerRangePerc"	,	innerRangePerc);	zClamp01 (innerRangePerc);
	arc.ReadColor			("fogColor"			,	fogColor);
	arc.ReadBool			("fadeOutSky"		,	bFadeOutSky);
	arc.ReadBool			("overrideColor"	,	bOverrideColor);

	//fogColor = zCOLOR(200,0,0,255);

};

void zCZoneZFogDefault::ThisVobAddedToWorld	 (zCWorld *homeWorld) 
{
	zCZoneZFog ::ThisVobAddedToWorld	(homeWorld);

	// Einstellung vornehmen (falls nur ein Default, aber keine 'Modifier' vorhanden sind)
	homeWorld->GetActiveSkyControler()->SetFarZ  (fogRangeCenter);
};

void zCZoneZFogDefault::Unarchive (zCArchiver& arc) {
	zCZoneZFog::Unarchive	(arc);

	// Einstellung vornehmen (falls nur ein Default, aber keine 'Modifier' vorhanden sind)
	if (GetWorld())	GetWorld()->GetActiveSkyControler()->SetFarZ  (fogRangeCenter);
};

// ============================================================================================================


///////////////////////////////////////////////////////////////////////////
//    zCZoneVobFarPlane
///////////////////////////////////////////////////////////////////////////

zCZoneVobFarPlane::zCZoneVobFarPlane() {
	vobFarZ			= 3000.0F;
	innerRangePerc	= 0.7F;
};

zREAL zCZoneVobFarPlane::GetActiveFarZ (const zREAL vobFarZDefault) {
	zREAL dist = GetCamPosWeight();
	if (dist<innerRangePerc)	dist = 0;
	else						dist = (dist - innerRangePerc) / (1.0F - innerRangePerc);

	zREAL farz = vobFarZ + dist*(vobFarZDefault-vobFarZ);

	return farz;
};

zCClassDef*	zCZoneVobFarPlane::GetDefaultZoneClass	() const
{ 
	return zCZoneVobFarPlaneDefault::GetStaticClassDef();	
};

void zCZoneVobFarPlane::ProcessZoneList (const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld) 
{
	// es gibt nichts zu tun, falls es nur 1 Default-Zone exsitiert (this)
	if ((zoneList.GetNum()==0) && (zoneDeactivateList.GetNum()==0)) return;

	// default ermitteln
	zCZone *zoneDefault = homeWorld->SearchZoneDefaultByClass (zCZoneVobFarPlaneDefault::GetStaticClassDef());
	
	zREAL def;
	if (zoneDefault)		def = ((zCZoneVobFarPlane*)zoneDefault)->vobFarZ;
	else					def = vobFarZ;

	// aktuelles farz ermitteln
	zREAL farz=0;
	if (zoneList.GetNum()<=0) {
		farz = def;
	} else {
		for (int i=0; i<zoneList.GetNum(); i++) {
			zCZoneVobFarPlane *zone	= ((zCZoneVobFarPlane*)zoneList[i]);
			farz					+= zone->GetActiveFarZ(def);
		};
		farz /= zREAL(zoneList.GetNum());
	};

	// farz setzen
	homeWorld->SetVobFarClipZ	(farz);
};


void zCZoneVobFarPlane::Archive (zCArchiver& arc) {
	zCZone::Archive (arc);

	//
	arc.WriteGroupBegin		("ZoneVobFarPlane");
	arc.WriteFloat			("vobFarPlaneZ"		,	vobFarZ);
	arc.WriteFloat			("innerRangePerc"	,	innerRangePerc);
	arc.WriteGroupEnd		("ZoneVobFarPlane");
};

void zCZoneVobFarPlane::Unarchive (zCArchiver& arc) {
	zCZone::Unarchive (arc);

	//
	arc.ReadFloat			("vobFarPlaneZ"		,	vobFarZ);
	arc.ReadFloat			("innerRangePerc"	,	innerRangePerc);	zClamp01 (innerRangePerc);

	// kuenstliches Limit, um Grafiker Wahnsinn zu verhindern
	vobFarZ = zMin (vobFarZ, zREAL(20000.0F));

#ifdef ZENGINE_DEBUG
//	vobFarZ = 20000.0F;
#endif
};

void zCZoneVobFarPlaneDefault::ThisVobAddedToWorld	 (zCWorld *homeWorld)
{
	zCZoneVobFarPlane::ThisVobAddedToWorld	(homeWorld);
	// Einstellung vornehmen (falls nur ein Default, aber keine 'Modifier' vorhanden sind)
	homeWorld->SetVobFarClipZ	(vobFarZ);
//	zerr.Warning ("D: ADDING: "+zSTRING(vobFarZ));
};

void zCZoneVobFarPlaneDefault::Unarchive (zCArchiver& arc) {
	zCZoneVobFarPlane::Unarchive	(arc);

	// Einstellung vornehmen (falls nur ein Default, aber keine 'Modifier' vorhanden sind)
	if (GetWorld())	GetWorld()->SetVobFarClipZ	(vobFarZ);
};

// ============================================================================================================

///////////////////////////////////////////////////////////////////////////
//    zCVobSound:	VOB - SOUND
///////////////////////////////////////////////////////////////////////////
							
zCVobSound::zCVobSound() {
	SetVobType			(zVOB_TYPE_SOUND);
	SetShowVisual		(FALSE);

	// props
	soundName.Clear();
	soundMode			= SM_LOOPING;
//	soundMode			= SM_RANDOM;
	soundStartOn		= TRUE;
	soundRandDelay		= 5.0F;			// secs
	soundRandDelayVar	= 2.0F;
	soundVolume			= 100.0F;
	soundIsAmbient3D	= FALSE;
	soundHasObstruction	= FALSE;
	soundConeAngle		= 0;
	soundVolType		= SV_SPHERE;

	// internals
	sfx					= 0;
	sfxHandle			= 0;
	soundIsRunning		= FALSE;
	soundAllowedToRun	= soundStartOn;
	soundAutoStart		= soundAllowedToRun;
	soundRandTimer		= 0;
	obstruction0		= -1;
	obstruction1		= -1;
	obstructionFrameTime= -1;

	//
	SetSoundRadius		(1500.0F);
};

zCVobSound::~zCVobSound() 
{
	StopSound();
	zRELEASE (sfx);
};

zSTRING zCVobSound::GetDebugDescString ()
{
	return zCZone::GetDebugDescString() + ", "
		+(soundHasObstruction			? (zSTRING("obs: ")+zSTRING(obstruction1,2)) : zSTR_EMPTY) 
		+((soundVolType==SV_ELLIPSOID)	? (zSTRING(", ellRad: ")+zSTRING(CalcVolumeScale(),2)) : zSTR_EMPTY)
		;
};

void zCVobSound::EndMovement (const zBOOL a_bHintTrafoChanged)
{
	zCZone::EndMovement(a_bHintTrafoChanged);
	if (soundVolType==SV_ELLIPSOID)
		soundRadius			= GetBBox3DLocal().GetMaxExtent();
};

void zCVobSound::SetSound (const zSTRING& soundfileName) 
{
	// benutzt: soundVolume, soundMode
	//
	soundName		= soundfileName;
	soundIsRunning	= FALSE;

	zCSoundFX *sound= LoadSound (soundfileName);
	if (sfx)		sfx->Release();
	sfx				= sound;
};

zCSoundFX* zCVobSound::LoadSound (const zSTRING& soundfileName) 
{
	zCSoundFX *sound=0;

	if (zsound)		// safety
	{
		// .wav oder script ?
		if (soundfileName.Search(".")!=-1)	sound = zsound->LoadSoundFX			(soundfileName);
		else								sound = zsound->LoadSoundFXScript	(soundfileName);
		if (!sound) return 0;
		
		// sound->SetLooping	(soundMode==SM_LOOPING);	// wird nun ueber PlaySound3D / UpdateSound geregelt
		// sound->SetVolume		(soundVolume/100.0F);		// wird nun ueber PlaySound3D / UpdateSound geregelt
	};
	return sound;
};

void zCVobSound::SetSoundVolume(const zREAL vol)
{
	this->soundVolume = vol;
};

void zCVobSound::SetSoundRadius (const zREAL soundRadius) 
{
	// dies ist nur wirksam, wenn SoundVolumen kein Ellipsoid ist.
	this->soundRadius	= soundRadius;
	if (soundVolType!=SV_ELLIPSOID)
	{
		zTBBox3D box;
		box.mins			= zPOINT3 (-soundRadius,-soundRadius,-soundRadius); 
		box.maxs			= zPOINT3 (+soundRadius,+soundRadius,+soundRadius);
		SetBBox3DLocal		(box);

/*		zTBBox3D box;
		box.mins			= zPOINT3 (-soundRadius,-soundRadius,-soundRadius) + GetPositionWorld();
		box.maxs			= zPOINT3 (+soundRadius,+soundRadius,+soundRadius) + GetPositionWorld();
		SetBBox3DWorld		(box);*/
	};
};

zREAL zCVobSound::CalcObstruction ()
{
	if (!soundHasObstruction)										return 0;
	if ((!zCCamera::activeCam) || (!zCCamera::activeCam->GetVob()))	return 0;

	const zREAL zSND_OBSTR_TIMEDELTA = zREAL(1000.0F);		// Update Intervall: 1 Sekunde (fuer TraceRay)

	zREAL	resObstruction;
	if (obstructionFrameTime<=0)
	{
		obstructionFrameTime= zSND_OBSTR_TIMEDELTA;
		zVEC3	ray			= zCCamera::activeCam->GetVob()->GetPositionWorld() - GetPositionWorld();
		zBOOL hit			= this->GetWorld()->TraceRayNearestHit (GetPositionWorld(), ray, (zCVob*)0, zTRACERAY_VOB_IGNORE);
		obstruction0		= obstruction1;
		if (hit)	obstruction1	= 1.0F;
		else		obstruction1	= 0;
		if (obstruction0==-1) obstruction0 = obstruction1;
		resObstruction		= obstruction0;
	} else {
		resObstruction		= zLerp (obstructionFrameTime / zSND_OBSTR_TIMEDELTA, obstruction1, obstruction0);
		obstructionFrameTime-= ztimer.GetFrameTimeF();
	};
//	zerr.Message ("D: res: "+zSTRING(resObstruction,4));
	return resObstruction;
};

zREAL zCVobSound::CalcVolumeScale()
{
	zREAL soundVolPerc = soundVolume/zREAL(100.0F);
	if (soundVolType!=SV_ELLIPSOID)									return soundVolPerc;
	if ((!zCCamera::activeCam) || (!zCCamera::activeCam->GetVob()))	return soundVolPerc;	// kann vorkommen: z.B. Vob Einfuegen ausserhalb der RenderLoop
	if (soundRadius<=0)												return soundVolPerc;

	// Ellipsoid (durch BBox definiert) bestimmt den Radius
	const zTBBox3D&	box		= GetBBox3DWorld();
	const zPOINT3&	camPos	= zCCamera::activeCam->GetVob()->GetPositionWorld();
	zVEC3			rel		= camPos - box.GetCenter();
	zVEC3			scale	= (box.maxs-box.mins) * zREAL(0.5F);
//	zREAL			maxDim	= zMax (zMax (scale[0], scale[1]), scale[2]);

	for (int i=0; i<3; i++) {
		if (scale[i]<=0) return 1;						// sollte eigentlich nicht passieren..
		scale[i]	= zAbsApprox(zREAL(1.0) / scale[i]);
	};
	scale			= Alg_Prod	(rel, scale);
	zREAL dist		= 0;
	zREAL scaleSum	= zAbsApprox(scale[0]) + zAbsApprox(scale[1]) + zAbsApprox(scale[2]);
	if (scaleSum==0) return 1;
	scaleSum		= zREAL(1.0F) / scaleSum;
	for (i=0; i<3; i++)
	{
		scale[i]	= zAbsApprox(scale[i]) * scaleSum;
		dist		+= scale[i] * zREAL(0.5F) * (box.maxs[i] - box.mins[i]);
	};

//	zREAL DIST = dist;
	dist = dist / soundRadius;
//	zerr.Message ("D: vol: "+zSTRING(dist)+", dist: "+zSTRING(DIST ,4));
//	zerr.Message ("D: radius: "+zSTRING(dist)+", realDist: "+zSTRING(rel.Length(),4));
	return dist * soundVolPerc;
};

void zCVobSound::StartSound (zBOOL forceCacheIn) 
{
//	if (sfx) zerr.Message ("D: StartSound: "+sfx->GetName());
	soundIsRunning		= soundIsRunning && zsound->IsSoundActive (sfxHandle);
	if (soundIsRunning) return;

	if (!sfx)			return;
	if (!zsound)		return;		// safety

	// Resource-Caching Strategie
	if (forceCacheIn) {
		sfx->CacheIn(-1);
	} else {
		if (sfx->CacheIn()!=zRES_CACHED_IN)	return;
	};

	zCSoundSystem::zTSound3DParams	params;
	params.SetDefaults	();
	params.obstruction	= CalcObstruction	();
	params.radius		= soundRadius;
	params.loopType		= (soundMode==SM_LOOPING) ? zCSoundSystem::zSND_LOOPING_ENABLED : zCSoundSystem::zSND_LOOPING_DEFAULT;
	params.volume		= CalcVolumeScale	();
	params.coneAngleDeg	= soundConeAngle;
	params.isAmbient3D	= soundIsAmbient3D;

	sfxHandle			= zsound->PlaySound3D	(sfx, this, zSND_SLOT_NONE, &params); 

	soundIsRunning		= TRUE;
};

void zCVobSound::StopSound () 
{
//	if (sfx) zerr.Message ("D: StopSound: "+sfx->GetName());
	if (!soundIsRunning) return;
	if (zsound)									// hier sollte _eigentlich_ ein zsound Objekt vorliegen, in einem KundenCrashReport war zsound hier allerdings==0, wie kann sowas passieren?
		zsound->StopSound	(sfxHandle);
	sfxHandle			= 0;
	soundIsRunning		= FALSE;
};

void zCVobSound::DoSoundUpdate (zREAL volScale) 
{
	//
	if (soundMode==SM_LOOPING) 
	{
		if (!soundIsRunning)	StartSound();		// falls diese Zone jetzt gerade wieder aktiv wurde
	} else
	if (soundMode==SM_ONCE) {
		// nix zu tun..
	} else
	if (soundMode==SM_RANDOM) {
		if (ztimer.GetTotalTimeF()>=soundRandTimer) {
			StartSound (TRUE);							// force ?
			soundRandTimer = ztimer.GetTotalTimeF() + (soundRandDelay + zRandF2()*soundRandDelayVar) * 1000.0F;
		};
	};

/*	volScale = float(zSin(ztimer.GetTotalTimeF() / 5000.0F));
	volScale = (volScale+1) * 0.5F;
	zerr.Message ("D: "+zSTRING(volScale,4));
*/
	if (!soundIsRunning) return;

	//
	if (soundHasObstruction || (soundVolType==SV_ELLIPSOID) || (volScale<(1)))
	{
		// Obstruction und Radius updaten
		zCSoundSystem::zTSound3DParams soundParams;
		const zBOOL res = zsound->GetSound3DProps (sfxHandle, soundParams);
		if (res)
		{
			soundParams.obstruction = CalcObstruction();
			soundParams.radius		= soundRadius;
//			soundParams.loopType	= (soundMode==SM_LOOPING) ? zCSoundSystem::zSND_LOOPING_ENABLED : zCSoundSystem::zSND_LOOPING_DEFAULT;
			soundParams.volume		= CalcVolumeScale() * volScale;
			zsound->UpdateSound3D	(sfxHandle, &soundParams);
		} else {
			zsound->UpdateSound3D	(sfxHandle);
		};
	} else 
	{
		zsound->UpdateSound3D	(sfxHandle);
	};
};

void zCVobSound::OnTrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	soundAllowedToRun	= TRUE;
	StartSound			(TRUE);		// TRUE = forceCacheIn
};

void zCVobSound::OnUntrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	soundAllowedToRun	= FALSE;
	StopSound();
};

void zCVobSound::OnMessage (zCEventMessage *eventMessage, zCVob* sourceVob)
{
	// tut derzeit noch nichts..
};

void zCVobSound::Archive (zCArchiver &arc) 
{
	zCZone::Archive (arc);

	//
	arc.WriteGroupBegin	("Sound");
	arc.WriteFloat		("sndVolume",		soundVolume);
	arc.WriteEnum		("sndMode",			"LOOPING;ONCE;RANDOM", soundMode);
	arc.WriteFloat		("sndRandDelay",	soundRandDelay);
	arc.WriteFloat		("sndRandDelayVar",	soundRandDelayVar);
	arc.WriteBool		("sndStartOn",		soundStartOn);
	arc.WriteBool		("sndAmbient3D",	soundIsAmbient3D);
	arc.WriteBool		("sndObstruction",	soundHasObstruction);
	arc.WriteFloat		("sndConeAngle",	soundConeAngle);
	arc.WriteEnum		("sndVolType",		"SPHERE;ELLIPSOID", soundVolType);
	arc.WriteFloat		("sndRadius",		soundRadius);
	arc.WriteString		("sndName",			soundName);
	arc.WriteGroupEnd	("Sound");

	// 
	if (arc.InSaveGame()) {
		// Sound is trigger/untrigger-bar, der Zustand muss im SaveGame gespeichert werden
		arc.WriteBool	("soundIsRunning",		soundIsRunning);
		arc.WriteBool	("soundAllowedToRun",	soundAllowedToRun);
	};
#ifdef COMPILING_SPACER
	if (arc.InProperties())
	{
		StopSound();
		StartSound(TRUE);
	};
#endif
};

void zCVobSound::Unarchive (zCArchiver &arc) 
{
	zCZone::Unarchive (arc);

	//
	StopSound ();		// wichtig bei ParamAenderungen im Spacer

	//
	arc.ReadFloat		("sndVolume"		, soundVolume);
	soundMode			= zTSoundMode(arc.ReadEnum("sndMode"));
	arc.ReadFloat		("sndRandDelay"		, soundRandDelay);
	arc.ReadFloat		("sndRandDelayVar"	, soundRandDelayVar);
	soundStartOn		= arc.ReadBool		("sndStartOn");
	soundIsAmbient3D	= arc.ReadBool		("sndAmbient3D");
	soundHasObstruction	= arc.ReadBool		("sndObstruction");
	arc.ReadFloat		("sndConeAngle"		, soundConeAngle);
	soundVolType		= zTSoundVolType(arc.ReadEnum("sndVolType"));
	SetSoundRadius		( arc.ReadFloat		("sndRadius"));			// muss NACH ellipsoid
 	SetSound			 (arc.ReadString	("sndName"));			// muss NACH radius & volume

	//
	if (arc.InSaveGame()) {
		// Sound is trigger/untrigger-bar, der Zustand muss im SaveGame gespeichert werden
		zBOOL autoStart		= soundStartOn;
		arc.ReadBool		("soundIsRunning"	, autoStart);
		soundAutoStart		= autoStart;

		zBOOL allowedToRun	= TRUE;
		arc.ReadBool		("soundAllowedToRun", allowedToRun);
		soundAllowedToRun	= allowedToRun;
	} else 
	{
		soundAllowedToRun	= soundStartOn;
		soundAutoStart		= soundStartOn;
	};
#ifdef COMPILING_SPACER
	if (arc.InProperties())
	{
		StopSound();
		StartSound(TRUE);
	};
#endif

	
	//
//	soundRandTimer		= ztimer.GetTotalTimeF() + (soundRandDelay + zRandF2()*soundRandDelayVar) * 1000.0F;
};

void zCVobSound::ProcessZoneList (const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld) 
{
	// nur jeden x-ten Frame
/*	static int ctr=1;
	ctr++;
	if ((ctr & 2)!=2) 
*/
	// activate
	for (int i=0; i<zoneList.GetNum(); i++) 
	{
		zCVobSound *vobSound = ((zCVobSound*)zoneList[i]);

		// Darf Sound gespielt werden ? (falls nicht, wird auf ein freischaltendes OnTrigger gewartet)
		if (vobSound->soundAllowedToRun)
		{
			// set by 'soundStartOn'
			if (vobSound->soundAutoStart)
			{
				vobSound->soundAutoStart	= FALSE;
				vobSound->StartSound		(TRUE);			// forceCacheIn
			};
			vobSound->DoSoundUpdate();
		} else {
			// Laeuft Sound irrtuemlicherweise, obwohl er das nicht darf?
			if (vobSound->soundIsRunning)
				vobSound->StopSound();
		};
	};

	// deactivate
	// FIXME: aufgrund eines Bugs im Spacer (zCSoundVobDayTimes Sounds werden beim Moven manchmal beendet)
	// werden Sounds dort als Workaround nicht gestoppt -> Speicher Overhead noch unklar
#ifndef COMPILING_SPACER
	for (int j=0; j<zoneDeactivateList.GetNum(); j++) {
		zCVobSound *vobSound = (zCVobSound*)zoneDeactivateList[j];
		vobSound->StopSound();
	};
#endif
};

void zCVobSound::ThisVobAddedToWorld	 (zCWorld *homeWorld) 
{
	zCZone::ThisVobAddedToWorld	 (homeWorld);
	// folgendes nicht hier !!
//	if ((soundStartOn) && (!soundIsRunning))	StartSound();
};

void zCVobSound::ThisVobRemovedFromWorld (zCWorld *homeWorld) 
{
	// FIXME: wird evtl. nicht aufgerufen (virt in destr.)
	zCZone::ThisVobRemovedFromWorld (homeWorld);
	StopSound();
};

// ========================================================================================================

zCVobSoundDaytime::zCVobSoundDaytime()
{
	soundStartTime	= 0;
	soundEndTime	= 0;
	sfx2			= 0;
	activeSection	= 0;

//	soundIsAmbient3D	= TRUE;
//	soundHasObstruction	= TRUE;
};

zCVobSoundDaytime::~zCVobSoundDaytime()
{
	zRELEASE (sfx2);
};

zSTRING zCVobSoundDaytime::GetDebugDescString ()
{
	return zCVobSound::GetDebugDescString() + ", seg: "+zSTRING(activeSection);
};

void zCVobSoundDaytime::ActivateSection (int nr) 
{
	if (activeSection==nr)		return;
	if (soundName2.IsEmpty())	return;
	StopSound		();
	sfxHandle		= 0;
	activeSection	= nr;
	if (!sfx2)	sfx2= LoadSound (soundName2);
	zSwap (sfx, sfx2);
};

zBOOL zCVobSoundDaytime::CalcTimeFrac (zREAL start, zREAL end, zREAL time, zREAL &frac) 
{
	// berechnet die fraction von time zw. start und end, falls nicht im Intervall return==FALSE
	zREAL ta= start;
	zREAL tb= end;
	zREAL diff;
	zBOOL ok;

	if (ta>tb) {
		if (time<ta) time += 24.0F;
		tb		+= 24.0F;
	};

	diff	= (tb-ta);				if (diff==0) return FALSE;
	frac	= (time-ta) / diff;
	ok		= ((frac>=0) && (frac<=1));
	return ok;
};

void zCVobSoundDaytime::DoSoundUpdate (zREAL volScale) 
{
	//
	zERR_ASSERT (GetHomeWorld());
	if (!GetHomeWorld()->GetActiveSkyControler()) return;
	zREAL time	= GetHomeWorld()->GetActiveSkyControler()->GetTime()*24.0F + 12.0F;

#if 0
#ifdef ZENGINE_DEBUG
/*	static zREAL g=0.0F;
	g += ztimer.GetFrameTimeF() / 50000.0F;
	while (g>1.0F) g -= 1.0F;
	time = g *24.0F + 12.0F;*/
	zREAL t = GetHomeWorld()->GetActiveSkyControler()->GetTime();
	t += ztimer.GetFrameTimeF() / 50000.0F;
	GetHomeWorld()->GetActiveSkyControler()->SetTime(t);
#endif
#endif

	if (time>24.0F) time	-= 24.0F;

	int		section	= 0;
	zBOOL	ok		= TRUE;
	zREAL	frac;
	if (!CalcTimeFrac(soundStartTime, soundEndTime, time, frac)) 
	{
		if (!soundName2.IsEmpty())
		{
			ok		= CalcTimeFrac(soundEndTime, soundStartTime, time, frac);
			section	= 1;
		} else
			ok		= FALSE;
	};
	ActivateSection (section);

	zREAL volumeScaler = 1;
	if (ok) {
		const zREAL MIN_PERC = zREAL(0.1F);
		const zREAL MAX_PERC = 1.0F - MIN_PERC;
		const zREAL SCALE_UP = (1.0F / MIN_PERC);
		if (frac<MIN_PERC)		volumeScaler = SCALE_UP * frac; else
		if (frac>MAX_PERC)		volumeScaler = 1 - (SCALE_UP * (frac-MAX_PERC));
		
		if (!soundIsRunning)	StartSound();
	} else {
		if (soundIsRunning)		StopSound();
		return;
	};

	//
	zCVobSound::DoSoundUpdate(volumeScaler);
};

void zCVobSoundDaytime::Archive (zCArchiver &arc) 
{
	zCVobSound::Archive (arc);

	//
	arc.WriteGroupBegin	("SoundDaytime");
	arc.WriteFloat		("sndStartTime",		soundStartTime);
	arc.WriteFloat		("sndEndTime",			soundEndTime);
	arc.WriteString		("sndName2",			soundName2);
	arc.WriteGroupEnd	("SoundDaytime");
};

void zCVobSoundDaytime::Unarchive (zCArchiver &arc) 
{
	zCVobSound::Unarchive (arc);

	// Cleanup, wichtig bei ParamAenderungen im Spacer
	zRELEASE			(sfx2);
	activeSection		= 0;		// nach Initialisierung der Basisklasse muss von einer 'activeSection==0' ausgegangen werden, Aenderungen sind dazu dann im folgenden relativ

	//
	arc.ReadFloat		("sndStartTime",		soundStartTime);	zClamp (soundStartTime	, zREAL(0), zREAL(24));
	arc.ReadFloat		("sndEndTime",			soundEndTime);		zClamp (soundEndTime	, zREAL(0), zREAL(24));
	arc.ReadString		("sndName2",			soundName2);
};

// ============================================================================================================

enum { zREVERB_PRESET_DEFAULT=0 };

zCZoneReverb::zCZoneReverb()
{
	reverbPresetNr		= zREVERB_PRESET_DEFAULT;
	reverbPresetWeight	= 1;
	innerRangePerc		= 0;
};

zSTRING zCZoneReverb::GetDebugDescString ()
{
	return zCZone::GetDebugDescString() + ", "+zSTRING("prs: ")+(*zsound->GetReverbPresetName(reverbPresetNr));
};

zREAL zCZoneReverb::GetActiveWeight ()
{
	zREAL dist = GetCamPosWeight();
	if (dist<innerRangePerc)	dist = 0;
	else						dist = (dist - innerRangePerc) / (1.0F - innerRangePerc);

	return dist*reverbPresetWeight;
};

zCClassDef*	zCZoneReverb::GetDefaultZoneClass	() const 
{ 
	return zCZoneReverbDefault::GetStaticClassDef();	
};

void zCZoneReverb::ProcessZoneList (const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld)
{
	// es gibt nichts zu tun, falls es nur 1 Default-Zone exsitiert (this)
	if ((zoneList.GetNum()==0) && (zoneDeactivateList.GetNum()==0)) return;

	//
	int		activePresetNr		= zREVERB_PRESET_DEFAULT;
	zREAL	activePresetWeight	= 1.0F;
	
	zCZoneReverbDefault *zoneDefault = (zCZoneReverbDefault*)homeWorld->SearchZoneDefaultByClass (zCZoneReverbDefault::GetStaticClassDef());
	if (zoneDefault) 
	{
		activePresetNr		= zoneDefault->reverbPresetNr;
		activePresetWeight	= zoneDefault->reverbPresetWeight;
	};

	// aktuelles Preset und dessen Weight ermitteln
	if (zoneList.GetNum()>0) 
	{
		int		bestPresetNr= 0;
		zREAL	bestWeight	= 9999;
		for (int i=0; i<zoneList.GetNum(); i++) 
		{
			zCZoneReverb *zone	= ((zCZoneReverb*)zoneList[i]);
			zREAL weight		= zone->reverbPresetWeight * (1-zone->GetActiveWeight());
			if (weight<bestWeight) 
			{
				bestPresetNr	= zone->reverbPresetNr;
				bestWeight		= weight;
			};
		};
		activePresetNr		= bestPresetNr;
		activePresetWeight	= zMin (1.0F, bestWeight);
	};

//	zerr.Message ("D: "+zSTRING(activePresetNr)+", "+zSTRING(activePresetWeight,4));
	zsound->SetGlobalReverbPreset (activePresetNr, activePresetWeight);
};

void zCZoneReverb::Archive (zCArchiver &arc) 
{
	zCZone::Archive (arc);

	//
	arc.WriteGroupBegin	("ZoneReverb");
	if (arc.InProperties())
	{
		if (zsound->GetNumReverbPresets()>0)
		{
			zSTRING presetEnum;
			for (int i=0; i<zsound->GetNumReverbPresets(); i++)
				presetEnum += *(zsound->GetReverbPresetName(i)) + ";";
			arc.WriteEnum	("reverbPreset", presetEnum.ToChar(), reverbPresetNr);
		};
	} else {
		arc.WriteEnum	("reverbPreset", "", reverbPresetNr);
	};
	arc.WriteFloat		("reverbWeight", reverbPresetWeight);
	arc.WriteFloat		("innerRangePerc", innerRangePerc);
	arc.WriteGroupEnd	("ZoneReverb");
};

void zCZoneReverb::Unarchive (zCArchiver &arc) 
{
	zCZone::Unarchive (arc);

	//
	if (arc.InProperties())
	{
		if (zsound->GetNumReverbPresets()>0) 
		{
			reverbPresetNr	= arc.ReadEnum	("reverbPreset");
		};
	} else {
		reverbPresetNr = arc.ReadEnum ("reverbPreset");
	};

	arc.ReadFloat		("reverbWeight", reverbPresetWeight);
	arc.ReadFloat		("innerRangePerc", innerRangePerc);		zClamp01 (innerRangePerc);
};

void zCZoneReverbDefault::ThisVobAddedToWorld	 (zCWorld *homeWorld)
{
	zCZoneReverb::ThisVobAddedToWorld (homeWorld);

	// Einstellung vornehmen (falls nur ein Default, aber keine 'Modifier' vorhanden sind)
	zsound->SetGlobalReverbPreset (reverbPresetNr, reverbPresetWeight);
};

void zCZoneReverbDefault::Unarchive (zCArchiver& arc) {
	zCZoneReverb::Unarchive	(arc);

	// Einstellung vornehmen (falls nur ein Default, aber keine 'Modifier' vorhanden sind)
	zsound->SetGlobalReverbPreset (reverbPresetNr, reverbPresetWeight);
};

// ============================================================================================================

zBOOL zCZoneMusic::s_autochange = TRUE;
zBOOL zCZoneMusic::s_canruleautochange = FALSE;



/*--------------------------------------------------------------------------

    (static) void zCZoneMusic :: SetAutochange( const zBOOL a )

    22-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zBOOL zCZoneMusic::SetAutochange (const zBOOL a)
{
	s_autochange = a;
	if( s_autochange==TRUE )
	{
		return s_canruleautochange;
	}
	return TRUE;
}



/*--------------------------------------------------------------------------

    (static) void zCZoneMusic :: GetAutochange( zBOOL *a )

    22-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void zCZoneMusic::GetAutochange (zBOOL *a)
{
	*a = s_autochange;
}

// ============================================================================================================

/*

  x ReverbPresets bereits im zCSoundSystem

  - zCVobSound: 
	x ellipsoid
	? killSelfWhenDone
  - zCVobSoundDaytime:
	x Tag & Nacht (inkl. Fade)

*/
