/******************************************************************************** 
 
     $Workfile:: zZone.h              $                $Date:: 29.01.01 15:24   $
     $Revision:: 26                   $             $Modtime:: 29.01.01 15:23   $
       $Author:: Speckels                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Zones
   created: 23.7.99

 * $Log: /current_work/ZenGin/_Dieter/zZone.h $
 * 
 * 26    29.01.01 15:24 Speckels
 * 
 * 25    4.12.00 18:23 Moos
 * 
 * 24    5.10.00 17:20 Moos
 * 
 * 23    29.09.00 21:20 Moos
 * 
 * 22    28.09.00 11:24 Moos
 * 
 * 21    20.09.00 18:40 Hildebrandt
 * 
 * 20    19.09.00 18:20 Pelzer
 * 
 * 19    8.09.00 10:55 Moos
 * 
 * 18    6.09.00 19:24 Pelzer
 * 
 * 17    6.09.00 17:31 Hildebrandt
 * 
 * 16    2.09.00 6:53 Hildebrandt
 * 
 * 15    1.09.00 18:01 Hildebrandt
 * 
 * 14    29.08.00 18:22 Hildebrandt
 * zCZone::Process..() gets called even if there is just a default zone in
 * the world
 * 
 * 13    29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 12    22.08.00 19:47 Hildebrandt
 * 
 * 11    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 10    21.07.00 14:29 Hildebrandt
 * 
 * 9     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:48 Hildebrandt
 * zenGin 089c
 * 
 * 6     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 4     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 3     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 26 $ ($Modtime: 29.01.01 15:23 $)


#ifndef __ZZONE_H__
#define __ZZONE_H__

#ifndef __ZVOB_H__
#include <zVob.h>
#endif

#ifndef __ZBVOLUME_H__
#include <zBVolume.h>
#endif

//struct zTBBox3D;

class zCWorld;

class zCBBox3DSorterBase {
public:
	class zTNode;
	friend class zTNode;

	enum { DIMENSION=3 };
	
	class zTNode {
    public:
	    zBOOL   isBegin;
	    void   *data;

	    zTNode(zBOOL isbeg, void *d):isBegin(isbeg),data(d){}

        zREAL   Value(){
            if (isBegin)
	            return zCBBox3DSorterBase::s_currentSorter->GetBBox(this).mins.n[zCBBox3DSorterBase::s_currentDimension];
            else
                return zCBBox3DSorterBase::s_currentSorter->GetBBox(this).maxs.n[zCBBox3DSorterBase::s_currentDimension];
	    }
	};
	
	class zTBoxSortHandle {
	public:
        zCBBox3DSorterBase *mySorter;

        zTBBox3D bbox3D;
        
        int		 indexBegin	[DIMENSION];
		int		 indexEnd	[DIMENSION];
		
		zTBoxSortHandle(){
            mySorter = NULL;

            bbox3D.mins = zVEC3(0,0,0);
            bbox3D.maxs = zVEC3(0,0,0);

		    for (int i=DIMENSION-1;i>=0;i--)
		        indexBegin[i] = indexEnd[i] = 0;
		}

		virtual ~zTBoxSortHandle();

		virtual void AddActive(void *data)=0;
		virtual void DelActive(void *data)=0;
		virtual void ClearActive(){};
	};

	zCBBox3DSorterBase();
	virtual ~zCBBox3DSorterBase();

	void				AllocAbs			(int numAlloc);
	void		        Clear				();
	void				Insert				(void * inData);
	void				Update				(void * inData);
	void				Remove				(void * inData);
	void				Sort				();
	zBOOL				IsSorted			() const { return sorted; };

	void				GetActiveList		(const zTBBox3D& bbox3D, zTBoxSortHandle& outHandle);
	void				UpdateActiveList	(const zTBBox3D& bbox3D, zTBoxSortHandle& handle);
	void                InsertHandle        (zTBoxSortHandle &handle);
	void                RemoveHandle        (zTBoxSortHandle &handle);

private:
	zCArray<zTBoxSortHandle *>        handles;
	static zCBBox3DSorterBase        *s_currentSorter;
	static int                        s_currentDimension;
	
	virtual const zTBBox3D& GetBBox(const zTNode *node)=0;

	zCArraySort<zTNode*> nodeList[DIMENSION];
	zBOOL				sorted;

	void				AdjustSorting		(zCArraySort<zTNode*> &list, const int listIndex);
	static int			ArrayCompare		(const void* ele1,const void* ele2);
};




template <class VOB> class zCVobBBox3DSorter: public zCBBox3DSorterBase{
public:

	class zTBoxSortHandle : public zCBBox3DSorterBase::zTBoxSortHandle{

    public:
	    virtual ~zTBoxSortHandle(){}

    	virtual void AddActive(void *data){
            if (!activeList.IsInList((VOB *) data))
	            activeList.Insert((VOB *) data);
	    }

	    virtual void DelActive(void *data){
    	    activeList.Remove((VOB *) data);
    	}

    	virtual void ClearActive(){
	        activeList.DeleteList();
	    }

        int GetNum(){
            return activeList.GetNum();
        }

        VOB * GetElement(int i){
            return activeList[i];
        }

    protected:
    	zCArray<VOB *> activeList;
	};

	virtual ~zCVobBBox3DSorter(){};

	void				Insert				(VOB * inData){
	  zCBBox3DSorterBase::Insert((void *)inData);
	}
	void				Update				(VOB * inData){
	  zCBBox3DSorterBase::Update((void *)inData);
	}
	void				Remove				(VOB * inData){
	  zCBBox3DSorterBase::Remove((void *)inData);
	}

	void				GetActiveList		(const zTBBox3D& bbox3D, zTBoxSortHandle& outHandle){
	  zCBBox3DSorterBase::GetActiveList(bbox3D, outHandle);
	}

	void				UpdateActiveList	(const zTBBox3D& bbox3D, zTBoxSortHandle& handle){
	  zCBBox3DSorterBase::GetActiveList(bbox3D, handle);
	}

	void				GetActiveList		(const zTBBox3D& bbox3D, zTBoxSortHandle& outHandle, zCArraySort<VOB *> &list){
	  zCBBox3DSorterBase::GetActiveList(bbox3D, outHandle);
      list.EmptyList();
      for (int i=outHandle.GetNum()-1; i>=0; i--)
        list.Insert(outHandle.GetElement(i));
	}

	void				UpdateActiveList	(const zTBBox3D& bbox3D, zTBoxSortHandle& handle, zCArraySort<VOB *> &list){
	  zCBBox3DSorterBase::UpdateActiveList(bbox3D, handle);
      list.EmptyList();
      for (int i=handle.GetNum()-1; i>=0; i--)
        list.Insert(handle.GetElement(i));
	}

private:
	virtual const zTBBox3D& GetBBox(const zTNode *node){
	  return ((VOB *)node->data)->GetBBox3DWorld();
	}
};








// ============================================================================================================

class zCZone : public zCVob {
	zCLASS_DECLARATION	(zCZone)
public:
	zCZone();

	// zCVob Interface
	virtual void		EndMovement				(const zBOOL a_bHintTrafoChanged=TRUE);
	virtual void		SetVisual				(zCVisual *v)					{};		// disable
	virtual void		SetVisual				(const zSTRING& visualFileName)	{};		// disable

	// zCZone Interface
	// "statics"
	virtual void		ProcessZoneList			(const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld) {};
	virtual void		ThisVobAddedToWorld		(zCWorld *homeWorld);						// called AFTER the actual addition
	virtual void		ThisVobRemovedFromWorld	(zCWorld *homeWorld);						// called BEFFORE the actual removal

	virtual zCClassDef*	GetZoneMotherClass		() const				{ return GetClassDef(); };
	virtual zCClassDef*	GetDefaultZoneClass		() const				{ return 0;				};
	virtual zSTRING		GetDebugDescString		();
	zBOOL				IsDefaultZone			() const				{ return (GetClassDef()==GetDefaultZoneClass());	};
												
protected:										
	virtual ~zCZone();							// use Release() instead!
	// Archive / Unarchive						
//	virtual void		Archive					(zCArchiver& arc);
	virtual void		Unarchive				(zCArchiver& arc);
												
	// tools for subclasses						
	zREAL				GetCamPosWeight			();
	zCWorld*			GetWorld				() const { return world; };			// the world that this zone resides in
	void				SetZoneVobFlags			();
private:
	zCWorld				*world;
};

// ============================================================================================================

class zCZoneZFog : public zCZone {
	zCLASS_DECLARATION	(zCZoneZFog)
public:
	zCZoneZFog();
	virtual void		ProcessZoneList		(const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld);
	virtual zCClassDef*	GetDefaultZoneClass	() const;

	void				SetFogRange			(const zREAL fogRange)	{ fogRangeCenter	= fogRange; };
	void				SetInnerRangePerc	(const zREAL inner)		{ innerRangePerc	= inner;	};
	zBOOL				GetFadeOutSky		() const				{ return bFadeOutSky;			};
	zBOOL				GetFadeOutSkyColor	() const				{ return bOverrideColor;		};
	zREAL				GetSkyFadeWeight    ();
	zCOLOR				GetFogColor			() const				{ return fogColor;				};
	


protected:
	// Archive / Unarchive
	virtual void		Archive				(zCArchiver& arc);
	virtual void		Unarchive			(zCArchiver& arc);

	zREAL				fogRangeCenter;
	zREAL				innerRangePerc;
	zCOLOR				fogColor;
	zBOOL				bFadeOutSky;
	zBOOL				bOverrideColor;

	zREAL				GetActiveRange		(const zREAL fogRangeDefault);
};

class zCZoneZFogDefault : public zCZoneZFog {
	zCLASS_DECLARATION	(zCZoneZFogDefault)
public:
	void				ThisVobAddedToWorld		(zCWorld *homeWorld);
protected:
	void				Unarchive			(zCArchiver& arc);
};

// ============================================================================================================

class zCZoneReverb : public zCZone {
	zCLASS_DECLARATION	(zCZoneReverb)
public:
	zCZoneReverb();

	// zCZone Interface
	virtual void		ProcessZoneList		(const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld);
	virtual zCClassDef*	GetDefaultZoneClass	() const;
	virtual zSTRING		GetDebugDescString	();

	// zCZoneReverb Interface
	void				SetReverbPresetNr	(const int nr)			{ reverbPresetNr=nr;			};
	void				SetReverbWeight		(const zREAL weight)	{ reverbPresetWeight=weight;	};

protected:
	int					reverbPresetNr;
	zREAL				reverbPresetWeight;
	zREAL				innerRangePerc;

	// Archive / Unarchive
	virtual void		Archive				(zCArchiver& arc);
	virtual void		Unarchive			(zCArchiver& arc);
private:
	zREAL				GetActiveWeight		();
};

class zCZoneReverbDefault : public zCZoneReverb {
	zCLASS_DECLARATION	(zCZoneReverbDefault)
public:
	// zCZone Interface
	virtual void		ProcessZoneList		(const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld) {};
	void				ThisVobAddedToWorld	(zCWorld *homeWorld);

protected:
	// Archive / Unarchive
//	virtual void		Archive				(zCArchiver& arc);
	virtual void		Unarchive			(zCArchiver& arc);
};

// ============================================================================================================

class zCZoneMusic : public zCZone {
	zCLASS_DECLARATION	(zCZoneMusic)
public:
	static	zBOOL			SetAutochange		( const zBOOL a );
	static	void			GetAutochange		( zBOOL *a );

protected:
	static	zBOOL			s_autochange;		//Autom. change of theme by ProcessZoneList()
	static	zBOOL			s_canruleautochange;
};

// ============================================================================================================

class zCZoneVobFarPlane : public zCZone {
	zCLASS_DECLARATION	(zCZoneVobFarPlane)
public:
	zCZoneVobFarPlane();
	virtual void		ProcessZoneList		(const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld);
	virtual zCClassDef*	GetDefaultZoneClass	() const;

	void				SetFarZ				(const zREAL z)			{ vobFarZ			= z; };

protected:
	// Archive / Unarchive
	virtual void		Archive				(zCArchiver& arc);
	virtual void		Unarchive			(zCArchiver& arc);

	zREAL				vobFarZ;
	zREAL				innerRangePerc;
private:
	zREAL				GetActiveFarZ		(const zREAL vobFarZDefault);
};

class zCZoneVobFarPlaneDefault : public zCZoneVobFarPlane {
	zCLASS_DECLARATION	(zCZoneVobFarPlaneDefault)
public:
	void				ThisVobAddedToWorld	(zCWorld *homeWorld);
protected:
	void				Unarchive			(zCArchiver& arc);
};

// ============================================================================================================

class zCVobSound : public zCZone {
	zCLASS_DECLARATION (zCVobSound)
public:
	zCVobSound();

	// Messages
	virtual	void			OnTrigger			(zCVob* otherVob, zCVob *vobInstigator); 
	virtual	void			OnUntrigger			(zCVob* otherVob, zCVob *vobInstigator); 
	virtual void			OnMessage			(zCEventMessage *eventMessage, zCVob* sourceVob);

	// zCVob Interface
	virtual void			EndMovement			(const zBOOL a_bHintTrafoChanged=TRUE);

	// zCZone Interface
	virtual void			ProcessZoneList		(const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld);
	virtual void			ThisVobAddedToWorld	(zCWorld *homeWorld);
	virtual void			ThisVobRemovedFromWorld(zCWorld *homeWorld);
	virtual zSTRING			GetDebugDescString	();

	// zCVobSound Interface
	enum zTSoundVolType		{	SV_SPHERE=0,
								SV_ELLIPSOID
							};	

	void					SetSound			(const zSTRING& soundfileName);
	void					SetSoundRadius		(const zREAL soundRadius);
	void					SetIsAmbient3D		(const zBOOL b)			{ soundIsAmbient3D		= b;		};
	void					SetHasObstruction	(const zBOOL b)			{ soundHasObstruction	= b;		};
	void					SetConeAngle		(const zREAL angleDeg)	{ soundConeAngle		= angleDeg; };
	void					SetVolType			(const zTSoundVolType v){ soundVolType			= v;		};
	void					StartSound			(zBOOL forceCacheIn=FALSE);
	void					StopSound			();

	// [SPECKELS] Einige Set und Get-Methoden fuer Volume und Range
	zREAL					GetSoundRadius		() { return soundRadius; };
	zREAL					GetSoundVolume		() { return soundVolume; };	
	zTSoundVolType			GetSoundVolType		() { return zTSoundVolType(soundVolType); };

	void					SetSoundVolume(const zREAL vol);	

protected:
	// props
	zSTRING					soundName;
	zREAL					soundRadius;
	enum zTSoundMode		{	SM_LOOPING,
								SM_ONCE,
								SM_RANDOM
							} soundMode;
	struct {
		zUINT8				soundStartOn		: 1;
		zUINT8				soundIsRunning		: 1;		// no props
		zUINT8				soundIsAmbient3D	: 1;
		zUINT8				soundHasObstruction	: 1;
		zUINT8				soundVolType		: 1;
		zUINT8				soundAllowedToRun	: 1;		// if this vobSound is not allowed to run, only OnTrigger() can make it run (default is TRUE)
		zUINT8				soundAutoStart		: 1;		// starts sound next time in 'process', set by 'soundStartOn'
	};
	zREAL					soundRandDelay;
	zREAL					soundRandDelayVar;
	zREAL					soundVolume;
	zREAL					soundConeAngle;
							
	// internal				
	zCSoundFX*				sfx;
	zTSoundHandle			sfxHandle;
	zREAL					soundRandTimer;
	zREAL					obstruction0;
	zREAL					obstruction1;
	zREAL					obstructionFrameTime;
							
	virtual ~zCVobSound();		// use Release() instead!
	// persistance			
	virtual void			Archive				(zCArchiver &arc);
	virtual void			Unarchive			(zCArchiver &arc);

	virtual void			DoSoundUpdate		(zREAL volScale=zREAL(1));
	zCSoundFX*				LoadSound			(const zSTRING& soundfileName);
private:
	zREAL					CalcObstruction		();
	zREAL					CalcVolumeScale		();
};

// ============================================================================================================

class zCVobSoundDaytime : public zCVobSound {
	zCLASS_DECLARATION (zCVobSoundDaytime)
public:
	zCVobSoundDaytime();

	// zCZone Interface
	virtual zCClassDef*		GetZoneMotherClass	() const				{ return zCVobSound::GetStaticClassDef(); };
	virtual zSTRING			GetDebugDescString	();

	//
	void					SetSound2			(const zSTRING& soundfileName) { soundName2 = soundfileName; };
protected:

	// props
	zREAL					soundStartTime;
	zREAL					soundEndTime;
	zSTRING					soundName2;
	zCSoundFX				*sfx2;
	int						activeSection;		// 0 or 1

	virtual ~zCVobSoundDaytime();	// use Release() instead!
	// persistance			
	virtual void			Archive				(zCArchiver &arc);
	virtual void			Unarchive			(zCArchiver &arc);

	virtual void			DoSoundUpdate		(zREAL volScale);
private:
	void					ActivateSection		(int nr);
	zBOOL					CalcTimeFrac		(zREAL start, zREAL end, zREAL time, zREAL &frac);
};

// ============================================================================================================




/* Alte Implementierung des BoxSorters als komplettes Template:


template <class T> 
class zCBBox3DSorter {
public:
	enum { DIMENSION=3 };
	struct zTBoxSortHandle {
		int		indexBegin	[DIMENSION];
		int		indexEnd	[DIMENSION];

        zTBoxSortHandle(){
            for (int i=DIMENSION-1;i>=0;i--)
                indexBegin[i] = indexEnd[i] = 0;
        }
	};

	 zCBBox3DSorter();
	~zCBBox3DSorter();
//	void				Update				(const T& inData, const zTBBox3D& bbox3D);

	void				AllocAbs			(int numAlloc);
	void				Clear				();
	void				Insert				(const T& inData, const zTBBox3D& bbox3D);
	void				Update				(const T& inData, const zTBBox3D& bbox3D);
	void				Remove				(const T& inData);
	void				Sort				();
	zBOOL				IsSorted			() const { return sorted; };

	void				GetActiveList		(const zTBBox3D& bbox3D, zTBoxSortHandle& outHandle	, zCArraySort<T>& outActiveList);
	void				UpdateActiveList	(const zTBBox3D& bbox3D, zTBoxSortHandle& handle	, zCArraySort<T>& activeList);

private:
	struct zTNode {
		zBOOL	isBegin;
		zREAL	value;
		T		data;
	};
	zCArraySort<zTNode*> nodeList[DIMENSION];
	zBOOL				sorted;

	void				AdjustSorting		(zCArraySort<zTNode*> &list, const int listIndex);
	static int			ArrayCompare		(const void* ele1,const void* ele2);
};

template<class T> 
zCBBox3DSorter<T>::zCBBox3DSorter () {
	sorted = FALSE;
	for (int i=0; i<DIMENSION; i++) {
		nodeList[i].SetCompare (&ArrayCompare);
	};
};

template<class T> 
zCBBox3DSorter<T>::~zCBBox3DSorter () {
	Clear();
};

template<class T> 
int zCBBox3DSorter<T>::ArrayCompare (const void* ele1,const void* ele2) {
	typedef zCBBox3DSorter<T>::zTNode** zTType;
	if ((*((zTType)ele1))->value<((*(zTType)ele2))->value)	return -1;
	if ((*((zTType)ele1))->value>((*(zTType)ele2))->value)	return +1;
	else													return  0;
};

template<class T> 
void zCBBox3DSorter<T>::Clear () {
	for (int i=0; i<DIMENSION; i++) {
		for (int j=0; j<nodeList[i].GetNum(); j++) {
			delete nodeList[i].Get(j);
		};
		nodeList[i].DeleteList();
	};
	sorted = FALSE;
};

template<class T> 
void zCBBox3DSorter<T>::AllocAbs (int numAlloc) {
	for (int i=0; i<DIMENSION; i++) {
		nodeList[i].AllocAbs			(numAlloc);
//		nodeList[i].MarkNumAllocUsed	();
	};
};

template<class T> 
void zCBBox3DSorter<T>::Insert (const T& inData, const zTBBox3D& bbox3D) 
{
	sorted = FALSE;
	for (int i=0; i<DIMENSION; i++) {
		zTNode* begin	= zNEW(zTNode);
		begin->isBegin	= TRUE;
		begin->value	= bbox3D.mins[i];
		begin->data		= inData;

		zTNode* end		= zNEW(zTNode);
		end->isBegin	= FALSE;
		end->value		= bbox3D.maxs[i];
		end->data		= inData;
		
		nodeList[i].Insert (begin);
		nodeList[i].Insert (end);
	};
};

template<class T> 
void zCBBox3DSorter<T>::Remove (const T& inData) 
{
	for (int i=0; i<DIMENSION; i++) {
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
};

template<class T> 
void zCBBox3DSorter<T>::GetActiveList (const zTBBox3D& bbox3D, zTBoxSortHandle& outHandle, zCArraySort<T>& outActiveList) 
{
	if (!sorted)	Sort();
	outActiveList.EmptyList();

	zCArraySort<T> workList;
	for (int i=0; i<DIMENSION; i++) 
	{
		workList.EmptyList();
		outHandle.indexBegin[i] = nodeList[i].GetNum(); // [Moos] von 0
		outHandle.indexEnd	[i] = 0;
		for (int j=0; j<nodeList[i].GetNum(); j++)
		{
			zTNode* node = nodeList[i].Get(j);

			if (node->value > bbox3D.maxs[i])	{
				outHandle.indexEnd[i] = j; 
                break;
			};

			if (node->value < bbox3D.mins[i])	{
				outHandle.indexBegin[i] = j+1;  // [Moos] +1 dazu
			};

			if (node->isBegin)	{
				workList.Insert (node->data);
			} else				
			if (node->value<bbox3D.mins[i])	{
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
//				if (!workList.IsInList (outActiveList[k])) {
//					outActiveList.RemoveIndex (k);
//					k--;
//				};
			};
		};
		if (outActiveList.GetNum()<=0) return;
	};
};

template<class T> 
void zCBBox3DSorter<T>::UpdateActiveList (const zTBBox3D& bbox3D, zTBoxSortHandle& handle, zCArraySort<T>& activeList) 
{
	if (!sorted)	Sort();

	for (int i=0; i<DIMENSION; i++) 
	{
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
			while ((*index)<actList.GetNum() && actList[*index]->value<compareValue) { // [Moos] Randtest wieder dazu
				// ungleiches begin/end ?
				if (j==actList[*index]->isBegin) {
					if (j==0)	activeList.Remove(actList[*index]->data); else
					{
						if (bbox3D.IsIntersecting(actList[*index]->data->bbox3D) && !activeList.IsInList (actList[*index]->data))
							activeList.Insert(actList[*index]->data);
					};
				};
				(*index)++;

				movedRight = TRUE;
			};

			// links ?
//			while ((*index>0) && (actList[*index-1]->value>compareValue)) {
			if (!movedRight)
			while (*index > 0 && actList[*index-1]->value>compareValue) {  // [Moos] Randtest und -1-Verschiebung wieder dazu
				// ungleiches begin/end ?
				(*index)--;
				if (j==actList[*index]->isBegin) {
					if (j==1)	activeList.Remove(actList[*index]->data); else
					{
						if (bbox3D.IsIntersecting(actList[*index]->data->bbox3D) && !activeList.IsInList (actList[*index]->data))
							activeList.Insert(actList[*index]->data);
					};
				};
			};
		};
	};
};

template<class T> 
void zCBBox3DSorter<T>::Sort () 
{
	sorted = TRUE;
	for (int i=0; i<DIMENSION; i++) {
		nodeList[i].QuickSort ();
	};
};

template<class T> 
void zCBBox3DSorter<T>::AdjustSorting (zCArraySort<zTNode*> &list, const int listIndex)
{
	// "insertion sort": sortiert in der Liste ein fast korrekt sortiertes Element durch verschieben neu
	const zREAL	sortValue	= list[listIndex]->value;	
	int			newIndex	= listIndex;
	if ((newIndex>0) && (list[newIndex-1]->value>sortValue))
	{
		// Position links suchen
		do {
			zSwap (list[newIndex], list[newIndex-1]);
			--newIndex;
		} while ((newIndex>0) && (list[newIndex-1]->value>sortValue));
	} else 
	if ((newIndex<list.GetNum()-1) && (list[newIndex+1]->value<sortValue))
	{
		// Position rechts suchen
		do {
			zSwap (list[newIndex], list[newIndex+1]);
			++newIndex;
		} while ((newIndex<list.GetNum()-1) && (list[newIndex+1]->value<sortValue));
	};
};

template<class T> 
void zCBBox3DSorter<T>::Update (const T& inData, const zTBBox3D& bbox3D)
{
	// Methode erwartet eine sortierte Liste. Falls sie nicht bereits sortiert ist,
	// wird sie ggfs. erst noch sortiert (sollte allerdings SEHR selten/kaum vorkommen!).
	if (!sorted)	Sort();

	int num=0;
	for (int i=0; i<DIMENSION; i++) {
		for (int j=0; j<nodeList[i].GetNum(); j++) 
		{
			zTNode *node = nodeList[i].Get(j);
			if (node->data == inData) {
				if (node->isBegin)	node->value = bbox3D.mins[i];
				else				node->value = bbox3D.maxs[i];
				AdjustSorting (nodeList[i], j);
				num++;
				if (num==2) break;
			};
		};
	};
};

*/

#endif
