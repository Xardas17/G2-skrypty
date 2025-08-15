/******************************************************************************** 
 
     $Workfile:: zObject.h            $                $Date:: 8.02.01 10:46    $
     $Revision:: 24                   $             $Modtime:: 7.02.01 10:44    $
       $Author:: Moos                                                           $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Base object (runtime typeinfo, persistance interface)
   created       : 31.3.99

 * $Log: /current_work/ZenGin/_Dieter/zObject.h $
 * 
 * 24    8.02.01 10:46 Moos
 * 
 * 23    6.02.01 9:51 Moos
 * 
 * 22    22.01.01 21:37 Speckels
 * 
 * 21    15.01.01 11:33 Moos
 * 
 * 20    13.01.01 21:45 Hildebrandt
 * 
 * 19    12.01.01 12:39 Moos
 * 
 * 18    11.01.01 20:30 Keskenti
 * 
 * 17    11.01.01 18:45 Hildebrandt
 * 
 * 16    11.01.01 17:50 Keskenti
 * 
 * 15    11.01.01 15:44 Keskenti
 * 
 * 14    11.01.01 14:26 Keskenti
 * 
 * 13    4.12.00 17:18 Hildebrandt
 * 
 * 12    9.11.00 17:26 Hildebrandt
 * 
 * 11    7.09.00 20:41 Hildebrandt
 * 
 * 10    31.08.00 17:04 Hildebrandt
 * 
 * 9     29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 8     21.08.00 17:18 Hildebrandt
 * 
 * 7     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 6     31.07.00 20:03 Speckels
 * 
 * 5     18.07.00 18:13 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 13    22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 12    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 10    10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 9     10.12.99 17:15 Hildebrandt
 * added factory methods for zCWay and zCWaypoint
 * 
 * 8     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 24 $ ($Modtime: 7.02.01 10:44 $)


#ifndef __ZOBJECT_H__
#define __ZOBJECT_H__


#ifndef __ZCONTAINER_H__
#include <zContainer.h>
#endif

#ifndef __ZSTRING_H__
#include <zSTRING.h>
#endif

#ifndef __ZMEMORY_H__
#include <zMemory.h>
#endif

// ===============================================================================================================

class zCArchiver;		// <zArchiver.h>
class zFILE;			// <zDisk.h>
class zCEventManager;	// <zVob.h>
class zCVob;			// <zVob.h>

// forward declarations
class zCClassDef;
class zCObject;
class zCObjectFactory;

// ===============================================================================================================

// debugging class related to zCClassDef
class zCLivingObjectsState {
private:
	zCArray<int>	numList;
	friend class zCClassDef;
};

typedef unsigned short zTClassID;

enum zTClassFlags {
	zCLASS_FLAG_SHARED_OBJECTS		= 1<<0,				// Objects of this class have a unique name (or none), a refCtr and can be shared.
	zCLASS_FLAG_TRANSIENT			= 1<<1,				// This object type can't be saved; null it out at save time.
	zCLASS_FLAG_RESOURCE			= 1<<2,				// Objects of this class are resources. The inherit the zCResource interface and are cacheIn/cacheOut'able.
};

class zENGINE_API zCClassDef {
public:
	zCClassDef					(const zSTRING& className, const zSTRING& baseClassName, zCObject* ( *_CreateNewInstance )(), const zDWORD classSize, const zDWORD classFlags, const zWORD arcVers, const zSTRING& scriptClassName="" );
	~zCClassDef					();
								
	const zSTRING&				GetClassName_				() const	{ return className; 				};
	const zSTRING&				GetBaseClassName			() const	{ return baseClassName; 			};
	zCClassDef*					GetBaseClassDef				() const	{ return baseClassDef;				};
	zTClassID					GetClassID					();
	zCObject*					CreateNewInstance			() const;										
	zBOOL						IsAbstractClass				() const	{ return (createNewInstance==0);	};
	zWORD						GetArchiveVersion			() const	{ return archiveVersion;			};
	zWORD						GetArchiveVersionSum		() const	{ return archiveVersionSum;			};
	int							GetNumLivingObjects			() const	{ return numLivingObjects;			};
	int							GetNumConstructorCalled		() const	{ return numCtorCalled;				};
	zBOOL						IsScriptedClass				() const	{ return !scriptClassName.IsEmpty();};
	const zSTRING&				GetScriptClassName			() const	{ return scriptClassName;			};
	zDWORD						GetClassFlags				() const	{ return classFlags;				};
	zDWORD						GetClassSize				() const	{ return classSize;					};
									
	void						OverwriteCreateNewInstance	(zCClassDef* dominantClass);
	void						ResetCreateNewInstance		();
	static zCObject*			CreateNewInstanceID			(zTClassID id);

	// shared objects
	zCObject*					SearchObject				(const zSTRING& objectName)	{ return SearchHashTable(objectName);	};
	int							GetNumObjects				() const					{ return objectList.GetNum();			};
	zCObject*					GetObjectByIndex			(int i)						{ return objectList[i];					};
	int							GetIndexByObject			(zCObject* object)			{ return objectList.Search (object);	};
	
	// enumerating				
	static int					GetNum						()							{ return classDefList->GetNum();	};
	static zCClassDef*			GetClassDefByIndex			(int i)						{ return classDefList->GetSafe(i);	};
	static zCClassDef*			GetClassDef					(const zSTRING& className);
	static zCClassDef*			GetClassDefTypeInsensitive	(const zSTRING& className);
	static zCClassDef*			GetClassDefByID				(const zTClassID id)		{ return classDefList->GetSafe(int(id));	};

	// debugging
	static void					GetLivingObjectsState		(zCLivingObjectsState& loState);
	static void					CompareLivingObjectsState	(const zCLivingObjectsState& loState);

	// "private"
	static void					ObjectCreated				(zCObject *object, zCClassDef *objClassDef);
	static void					ObjectCreated				(zCObject *object, zCClassDef *objClassDef, const char *file, int line);
	static void					ObjectDeleted				(zCObject *object, zCClassDef *objClassDef);
	static void					ObjectCreated				(zCObject *object, int size, zCClassDef *objClassDef);
	static void					ObjectDeleted				(zCObject *object, int size, zCClassDef *objClassDef);
	static void					EndStartup					();

	void						ReportLeaks					();
protected:						
	zCClassDef					();
private:
	static zCArraySort<zCClassDef*>	*classDefList;
	static int					CompareClassDefNames		(const void* em1, const void* em2);
	static zCClassDef			*classDefSearchDummy;
	static zBOOL				startupFinished;

	void						Init						();   // called by ctors

	zDWORD						GetHashIndex				(const zSTRING& name);
	zDWORD						GetHashIndex				(zCObject *object);
	void						InsertHashTable				(zCObject *object);
	void						RemoveHashTable				(zCObject *object);
	zCObject*					SearchHashTable				(const zSTRING& objectName);
	float						CalcHashTableSpread			();
	
	zSTRING						className;
	zSTRING						baseClassName;
	zSTRING						scriptClassName;
	zCClassDef					*baseClassDef;
	zCObject*					( *createNewInstance )( void );
	zCObject*					( *createNewInstanceBackup )( void );
	zDWORD						classFlags;
	zDWORD						classSize;
	int							numLivingObjects;
	int							numCtorCalled;
	zCObject					**hashTable;
	zCArray<zCObject*>			objectList;			// a ptr to every object of this class is stored here (no objs of subclasses) [OLD: right now, only "named" objects are collected here (name-string!="")]
	zWORD						archiveVersion;
	zWORD						archiveVersionSum;

#ifdef DEBUG_MOOS // für meine Leak-Suche
    int                     class_id;       // Nummer der Klasse
    int                     next_object_id; // Nummer des Objekts in dieser Klasse, das als nächstes erzeugt werden soll
#endif // DEBUG_MOOS    
								
	friend zCObject;			
};								

// ===============================================================================================================

// macros for class declaration / definition

#define zCLASS_DECLARATION( className )		\
public: \
	static	zCClassDef*		className::GetStaticClassDef	(void)			{ return &(className::classDef); }; \
	void*					className::operator new			(size_t size)	{ void* ptr = ::operator new(size); zCClassDef::ObjectCreated ((zCObject*)ptr, &className::classDef);	return ptr; }; \
	void*					className::operator new			(unsigned int size, const char *classNAME, const char *file, int line) { void* ptr = ::operator new(size, classNAME, file, line); zCClassDef::ObjectCreated ((zCObject*)ptr, &className::classDef, file, line);	return ptr; }; \
	void					className::operator delete		(void* ptr)		{ zCClassDef::ObjectDeleted ((zCObject*)ptr, &className::classDef); ::operator delete(ptr); }; \
	void					className::operator delete		(void* ptr, const char *classNAME, const char *file, int line)		{ zCClassDef::ObjectDeleted ((zCObject*)ptr, &className::classDef); ::operator delete(ptr); }; \
	void*					className::operator new[]		(size_t size)															{ zerr.Fault("D: OBJ: illegal new[] on class: " #className); return 0; }; \
	void*					className::operator new[]		(unsigned int size, const char *classNAME, const char *file, int line)	{ zerr.Fault("D: OBJ: illegal new[] on class: " #className); return 0; }; \
	void					className::operator delete[]	(void* ptr)																{ zerr.Fault("D: OBJ: illegal delete[] on class: " #className); }; \
	void					className::operator delete[]	(void* ptr, const char *classNAME, const char *file, int line)			{ zerr.Fault("D: OBJ: illegal delete[] on class: " #className); }; \
private:									\
	static	zCClassDef		className::classDef;		\
	static	zCObject*		className::_CreateNewInstance	( void );			\
	virtual	zCClassDef*		className::_GetClassDef			( void ) const { return &(className::classDef); };


// abstract class, cannot be instantiated
#define zCLASS_DEFINITION_ABSTRACT( className, baseClassName, classFlags ) \
	zCClassDef				className::classDef				( #className, #baseClassName, 0, sizeof(className), classFlags, 0 ); 

// standard concrete class definition
// 'archiveVersion' must be increased every time the archive/unarchive methods change the format
#define zCLASS_DEFINITION( className, baseClassName, classFlags, archiveVersion ) \
	zCClassDef				className::classDef				( #className, #baseClassName, className::_CreateNewInstance, sizeof(className), classFlags, archiveVersion ); \
	zCObject*				className::_CreateNewInstance	( void )	{ return zNEW(className); }

// scripted class, instantiated objects hold D-scripted data
#define zCLASS_DEFINITION_SCRIPTED( className, baseClassName, classFlags, archiveVersion, scriptClassName ) \
	zCClassDef				className::classDef				( #className, #baseClassName, className::_CreateNewInstance, sizeof(className), classFlags, archiveVersion, #scriptClassName ); \
	zCObject*				className::_CreateNewInstance	( void )	{ return zNEW(className); }


// ===============================================================================================================

// - runtime type information
// - persistance
// - shared objects

class zENGINE_API zCObject {
	zCLASS_DECLARATION	(zCObject)
public:
	// runtime type information
	static inline zBOOL		CheckInheritance	(const zCClassDef *baseClass, const zCClassDef *subClass);
	static zBOOL			CheckInheritance	(const zCObject	*baseObject	, const zCObject   *subObject);
	static zBOOL			CheckInheritance	(const zSTRING& baseClassName, const zSTRING& subClassName);
	static zCObject*		CreateNewInstance	(const zSTRING& className);
	static const zSTRING&	GetBaseClassName	(const zSTRING& className);
	static zCClassDef*		GetClassDef			(const zSTRING& className) { return zCClassDef::GetClassDef(className); };
	static zCClassDef*		GetBaseClassDef		(const zSTRING& className);			// ?
	static void				PrintClassHierarchy (int indent=0, zCClassDef *parentClassDef=0, int numObjTotal=0, int numBytesTotal=0);	// debug
	static void				GetMemStats			(int &numObjTotal, int &numBytesTotal, zCClassDef *parentClassDef=0);	// debug
							
	//						
	zCObject*				CreateNewInstance	()	const { return _GetClassDef()->CreateNewInstance(); };
	zCObject*				CreateCopy			();			// creates copy via archive/unarchive
	const zSTRING&			GetBaseClassName	()	const { return _GetClassDef()->GetBaseClassName();	};
	zCClassDef*				GetClassDef			()	const { return _GetClassDef();						};
	const zSTRING&			GetClassName_		()	const { return _GetClassDef()->GetClassName_();		};
	zBOOL					IsKindOf			(const zCClassDef* baseClass) const	{ return zCObject::CheckInheritance (baseClass, GetClassDef()); };

	// shared objects
#ifdef DEBUG_MOOS // für meine Leak-Suche
	int						Release				();
	zCObject*				AddRef				();
#else // DEBUG_MOOS
	int						Release				() { 
														const int tmp=--refCtr;  if (tmp<=0) delete this; return tmp;	
	};
	zCObject*				AddRef				() { 
//														zERR_ASSERT (refCtr<=32760);	// guard against overflow (nicht mehr noetig)
														refCtr++; return this;											
	};
#endif // DEBUG_MOOS


#ifdef _DEBUG
	zCObject*				AddRefDebug			(const char* file, int line);
	int						ReleaseDebug		(const char* file, int line);
#endif

	int						GetRefCtr			() const { return refCtr; };

	const zSTRING&			GetObjectName		() const;
	zBOOL					SetObjectName		(const zSTRING& name);

	// persistance
	virtual void			Archive				(zCArchiver &arc) {};
	virtual void			Unarchive			(zCArchiver &arc) {};
//	virtual void			PostUnarchive		(zCArchiver &arc) {};	
//	virtual void			PreArchive			(zCArchiver &arc) {};
//	virtual void			PostArchive			(zCArchiver &arc) {};
	zWORD					GetArchiveVersion	()	const { return _GetClassDef()->GetArchiveVersion(); };
	zWORD					GetArchiveVersionSum()	const { return _GetClassDef()->GetArchiveVersionSum(); };
protected:
	virtual ~zCObject();

	zCObject() {
		refCtr		= 1;
		hashIndex	= 0xFFFF;
		hashNext	= 0;
		objectName.Clear();
		#ifdef _DEBUG
			if (!zCClassDef::startupFinished)
				zerr.Fatal ("D: zCClassDef: tried to create engine-object before engine was inited ("+GetClassName_()+")");
		#endif
	};		

	// disable..
	zCObject (const zCObject&) {};
	zCObject& operator=(const zCObject&) { return *this; };


#ifdef DEBUG_MOOS // für meine Leak-Suche
    int                     class_id;       // Nummer der Klasse
    int                     identification; // Nummer des Objekts in dieser Klasse
#endif // DEBUG_MOOS    

private:
	int						refCtr;				// 32bit !
	zWORD					hashIndex;			// 16bit !
	zCObject				*hashNext;			// next entry in hash bin
	zSTRING					objectName;	

	friend zCClassDef;
};

// zCObject inlines 

zBOOL zCObject::CheckInheritance (const zCClassDef *baseClass , const zCClassDef *subClass) 
{
	if (!subClass) return FALSE;
	const zCClassDef *classDef = subClass;
	do {
		if (classDef==baseClass) return TRUE;
		classDef = classDef->GetBaseClassDef();
	} while (classDef);
	return FALSE;
};

/*	------------------------------------------------------------------
	template zDYANMIC_CAST

	11.01.01	[Keskenti]
				Initial implementaton
				Used as a replacement for dynamic_cast 
				for zCObject-derived classes 
	------------------------------------------------------------------ */

template< class T > T* zDYNAMIC_CAST (const zCObject* pObject)
{
	#ifdef _DEBUG
		if ( pObject && ( ! dynamic_cast< const zCObject* > ( pObject ) ) )
		{
			zERR_FAULT( "R: zDYNAMIC_CAST called for non-zCObject-derived class !!!" );
			return NULL;
		}
	#endif
	return pObject 
		&& zCObject::CheckInheritance ( T::GetStaticClassDef(), pObject->GetClassDef() ) ? (T*) pObject : NULL;
}

/*	------------------------------------------------------------------
	template zIS_OF_CLASS

	13.01.2001	[HILDEBRANDT]
				Initial implementaton
				zCObject class hierarchy: is given object of specified class?
				(does NOT check inheritance!)
	------------------------------------------------------------------ */

template< class T > 
zBOOL zIS_OF_CLASS (const zCObject *pObject)
{
	return pObject->GetClassDef()==T::GetStaticClassDef();
};

#define zRELEASE(obj) { if (obj) { obj->Release(); obj=0; }; };
//#define zCREATE_REF(className) ((className*)((new className)->AddRef()))


// ===============================================================================================================

#ifdef _DEBUG
	#define zRELEASE_OBJ(obj)	if (obj) { (obj)->ReleaseDebug(__FILE__, __LINE__);obj=0; }
	#define zADDREF_OBJ(obj)	if (obj) (obj)->AddRefDebug(__FILE__, __LINE__)
#else
	#define zRELEASE_OBJ(obj)	if (obj) { (obj)->Release(); obj=0; };
	#define zADDREF_OBJ(obj)	if (obj) (obj)->AddRef()
#endif


template <class T> 
class zPTR {
public:
	 zPTR<T>()		{ object = 0;									};
	~zPTR<T>()		{ if (object) {	object->Release(); object =0; } };
	
	inline			zPTR<T>			(const zPTR<T>& theCopy)	{ object = theCopy.object; if (object) object->AddRef();	};
	inline			zPTR<T>			(T *theCopy)				{ object = theCopy;	if (object) object->AddRef();			};

	zBOOL			IsValid			() const					{ return (object!=0); };
																			
	T*				operator ->		()							{ assert(object); return object;	}
	T const*		operator ->		() const					{ assert(object); return object;	}
	T&				operator *		()							{ assert(object); return *object;	}
	T const&		operator *		() const					{ assert(object); return *object;	}

	zBOOL			operator ==		(zPTR<T>& ptr)				{ return object == ptr.object;		}
	zBOOL			operator !=		(zPTR<T>& ptr)				{ return object != ptr.object;		}
																									
	zBOOL			operator ==		(const zPTR<T>& ptr) const	{ return object == ptr.object;		}
	zBOOL			operator !=		(const zPTR<T>& ptr) const	{ return object != ptr.object;		}
																									
	zBOOL			operator ==		(T* ptr)					{ return object == ptr;				}
	zBOOL			operator !=		(T* ptr)					{ return object != ptr;				}
																									
	zBOOL			operator ==		(const T* ptr) const 		{ return object == ptr;				}
	zBOOL			operator !=		(const T* ptr) const 		{ return object != ptr;				}

					operator T*		()							{ return object;					}
					operator T*		() const					{ return object;					}
					operator int	()							{ return (int) object;				}

	inline zPTR<T>&	operator =		(const zPTR<T>& theCopy);
	inline zPTR<T>&	operator =		(T *theCopy);

private:
	T*				object;
};

template <class T>
inline zPTR<T>& zPTR<T>::operator=(const zPTR<T>& theCopy)
{
	if (object!=theCopy.object) {
		if (theCopy.object)	theCopy.object->AddRef	();
		if (object)			object->Release	();
		object = theCopy.object;
	}
	return *this;
}

template <class T>
inline zPTR<T>&	zPTR<T>::operator = (T *theCopy)
{
	if (object!=theCopy) {
		if (theCopy)	theCopy->AddRef	();
		if (object)		object->Release	();
		object = theCopy;
	}
	return *this;
}

// ===============================================================================================================

class zCSession;
class zCWorld;
class zCGameInfo;
class zCPlayerInfo;
class zCNetVobControl;
class zCWaypoint;
class zCWay;
class zCCSManager;
enum zTArchiverImplementation;

/*	------------------------------------------------------------------
	class zCObjectFactory

	26.07.00	[Speckels]
				Umbenennung: CreateCSPlayer in CreateCSManager
				CreateWorld mit zusaetzlichem Parameter (ownerSession) und ausimplementiert (lieferte vorher 0)
	------------------------------------------------------------------ */

class zENGINE_API zCObjectFactory : public zCObject 
{
	zCLASS_DECLARATION	(zCObjectFactory)
public:
	virtual zCEventManager*		CreateEventManager	(zCVob* hostVob);
	virtual zFILE*				CreateZFile			(const zSTRING& fileName);

	virtual zCSession*			CreateSession		();
	virtual zCCSManager*		CreateCSManager		();
	virtual zCNetVobControl*	CreateNetVobControl (zCVob* hostVob);
    virtual zCGameInfo*			CreateGameInfo		() { return 0; };
    virtual zCPlayerInfo*		CreatePlayerInfo    () { return 0; };
    virtual zCWorld*            CreateWorld			();
	virtual zCWaypoint*			CreateWaypoint		();
	virtual zCWay*				CreateWay			();
protected:
	virtual ~zCObjectFactory() {};
};

zENGINE_API extern zCObjectFactory* zfactory;


// ===============================================================================================================

#endif