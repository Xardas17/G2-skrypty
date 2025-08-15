/******************************************************************************** 
 
     $Workfile:: zObject.cpp          $                $Date:: 24.04.01 17:33   $
     $Revision:: 31                   $             $Modtime:: 22.04.01 21:24   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zObject.cpp $
 * 
 * 31    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 30    9.02.01 13:24 Moos
 * 
 * 29    8.02.01 10:52 Moos
 * 
 * 28    8.02.01 10:46 Moos
 * 
 * 27    7.02.01 18:33 Moos
 * 
 * 26    6.02.01 18:33 Moos
 * 
 * 25    5.02.01 18:01 Moos
 * 
 * 24    22.01.01 21:37 Speckels
 * 
 * 23    17.01.01 18:31 Hildebrandt
 * 
 * 22    12.01.01 12:39 Moos
 * 
 * 21    11.01.01 18:45 Hildebrandt
 * 
 * 20    11.01.01 18:19 Hildebrandt
 * 
 * 19    14.12.00 22:42 Hildebrandt
 * 
 * 18    17.11.00 1:28 Hildebrandt
 * 
 * 17    26.10.00 16:24 Hildebrandt
 * 
 * 16    26.10.00 16:03 Hildebrandt
 * 
 * 15    11.09.00 19:40 Speckels
 * 
 * 14    31.08.00 17:04 Hildebrandt
 * 
 * 13    24.08.00 15:19 Moos
 * ein zNEW eingefügt
 * 
 * 12    23.08.00 17:31 Hildebrandt
 * zengin 0.92i
 * 
 * 11    21.08.00 17:18 Hildebrandt
 * 
 * 10    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 9     31.07.00 20:03 Speckels
 * 
 * 8     21.07.00 14:28 Hildebrandt
 *  
 * 7     18.07.00 18:13 Hildebrandt
 * 
 * 6     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 11    22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 10    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 8     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 7     10.12.99 17:15 Hildebrandt
 * added factory methods for zCWay and zCWaypoint
 * 
 * 6     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 31 $ ($Modtime: 22.04.01 21:24 $)


#include <zCore.h>
#include <zError.h>
#include <zTools.h>
#include <zArchiver.h>
#include <zBuffer.h>
#include <zccsmanager.h>
//#include <zObject.h>

#include <zAccount.h>

zCArraySort<zCClassDef*>	*zCClassDef::classDefList = 0;

/*
  Probs
  - bei Stack-Variablen wird new/delete nicht aufgerufen!
  - Im Object-Destructor/ObjectDeleted() sind member-Var Destruktoren bereits ausgefuehrt => objectName
  - zCObject-Mem Bedarf verringern ?
*/

// =================================================================================================================

zCLASS_DEFINITION_ABSTRACT	( zCObject			, NULL		, 0			)
zCLASS_DEFINITION			( zCObjectFactory	, zCObject	, 0,	0	)

/*
#ifdef _DEBUG
	#include <Crtdbg.h>
//	#include <malloc.h>
#endif
*/

zCObject::~zCObject()
{
	// Der Aufruf dieses dtor ist nur korrekt, wenn der refCtr zwischen '-1' und '0' ist
	zERR_ASSERTT_STRICT (refCtr<=0 , "D: OBJ: tried to delete zCObject with refCtr greater than 0 !");
	zERR_ASSERTT_STRICT (refCtr>=-1, "D: OBJ: deleting an already deleted zCObject ?!");
	refCtr = -999;

	#ifdef _DEBUG
/*
		int size = _msize_dbg (this, _NORMAL_BLOCK);
		assert (_CrtIsMemoryBlock(this, _msize_dbg (this, _NORMAL_BLOCK), 0,0,0));
//		assert (_CrtIsMemoryBlock(this, sizeof(*this), 0,0,0));
*/
	#endif

#ifdef ZACCOUNT
    zCAccount::Clear(this);
#endif
};

// statics

	// Ist subClass eine Unterklasse von baseClass?
	// Dynamic_Cast: Liegt die ObjektKlasse (subClass) unterhalb der TypKlasse (baseClass) ?
	// => von der ObjektKlasse von Basisklasse zu Basisklasse wandern und jeweils mit der TypKlasse
	// vergleichen.

	// zCVob *vob = dynamic_cast<zCVob*> (object)
	// CheckInheritance (zCVob, object)

zBOOL zCObject::CheckInheritance (const zCObject *baseObject, const zCObject *subObject) 
{
	if ((!baseObject) || (!subObject)) return FALSE;
	return CheckInheritance (baseObject->GetClassDef(), subObject->GetClassDef());
};

zBOOL zCObject::CheckInheritance (const zSTRING& baseClassName, const zSTRING& subClassName) 
{
	zCClassDef *baseClassDef	= GetClassDef (baseClassName);
	zCClassDef *subClassDef		= GetClassDef (subClassName);
	return CheckInheritance (baseClassDef, subClassDef);
};

zCObject* zCObject::CreateNewInstance	(const zSTRING& className) 
{
	zCClassDef* classDef = GetClassDef (className);
	if (!classDef) return 0;
	
	return classDef->CreateNewInstance();
};

zCObject* zCObject::CreateCopy () 
{
	// Copy Operator, stuetzt sich auf den Archiver ab
	zCObject*	object	= CreateNewInstance();
	if (object)
	{
		zCArchiver	*arcWrite	= zarcFactory.CreateArchiverWrite ((zCBuffer*)0, zARC_MODE_BINARY, zARC_FLAG_WRITE_BRIEF_HEADER);
		zCBuffer	*buffer		= 0;

		arcWrite->WriteObject			(this);
		buffer = arcWrite->GetBuffer	();
		if (buffer)
		{
			zCArchiver	*arcRead= zarcFactory.CreateArchiverRead  (buffer);
 			arcRead->ReadObject			(object);
			arcRead->Close				();
			arcRead->Release			();
			buffer->SetMode				(WRITE);
		};
		arcWrite->Close					();
		arcWrite->Release				();
	};

	return object;
};

void zCObject::PrintClassHierarchy (int indent, zCClassDef *parentClassDef, int numObjTotal, int numBytesTotal) 
{
	if (indent==0) {
		zERR_MESSAGE (1, 0, "D: *** Enumerating class Hierarchy (#"+zSTRING(zCClassDef::classDefList->GetNum())+") ***");
	};

	zSTRING baseName;
	zSTRING s;
	for (int i=0; i<zCClassDef::classDefList->GetNum(); i++) 
	{
		zCClassDef* classDef = (*zCClassDef::classDefList)[i];
		
		if (classDef->GetBaseClassDef()==parentClassDef) {

			zBOOL baseOK;
			if (classDef->GetBaseClassDef()) 
			{
				baseName= classDef->GetBaseClassDef()->GetClassName_();
				baseOK	= (baseName == classDef->GetBaseClassName());
			} else {
				baseOK	= (classDef->GetBaseClassName()==zSTRING("NULL"));
			};

			s = "D: "+Spaces(indent*4)+" - "+classDef->GetClassName_();
//			s += " [id "+zSTRING(i)+"]";
			if (classDef->GetNumLivingObjects()>0) 						s += " [objs "+zSTRING(classDef->GetNumLivingObjects())+"]";
			if (classDef->GetNumConstructorCalled()>0)					s += " [ctor "+zSTRING(classDef->GetNumConstructorCalled())+"]";
			if (classDef->GetNumLivingObjects()>0)
			if (classDef->GetClassFlags() & zCLASS_FLAG_SHARED_OBJECTS)	s += " [hash "+zSTRING(classDef->CalcHashTableSpread(),4)+"]";

			numObjTotal		+= classDef->GetNumLivingObjects();
			numBytesTotal	+= classDef->GetNumLivingObjects() * classDef->GetClassSize();
			
			if (!baseOK) {
				s += " (BASE_CLASS CORRUPT)";
				zERR_WARNING (s);
			} else {
				zERR_MESSAGE (1, 0, s);
			};
			PrintClassHierarchy (indent+1, classDef, numObjTotal, numBytesTotal);
		};
	};

	if (indent==0) {
		int numObjTotal;
		int numBytesTotal;
		GetMemStats (numObjTotal, numBytesTotal);
		zERR_MESSAGE (1, 0, "D: ***********************************");
		zERR_MESSAGE (1, 0, "D: numObjTotal: "+zSTRING(numObjTotal)+", numBytesTotal: "+zSTRING(numBytesTotal));
		zERR_MESSAGE (1, 0, "D: ***********************************");
	};
};

void zCObject::GetMemStats (int &numObjTotal, int &numBytesTotal, zCClassDef *parentClassDef)
{
	if (parentClassDef==0) {
		numObjTotal		= 0;
		numBytesTotal	= 0;
	};

	for (int i=0; i<zCClassDef::classDefList->GetNum(); i++) 
	{
		zCClassDef* classDef = (*zCClassDef::classDefList)[i];
		if (classDef->GetBaseClassDef()==parentClassDef) {
			numObjTotal		+= classDef->GetNumLivingObjects();
			numBytesTotal	+= classDef->GetNumLivingObjects() * classDef->GetClassSize();
			GetMemStats (numObjTotal, numBytesTotal, classDef);
		};
	};
};

//

const zSTRING& zCObject::GetObjectName () const 
{ 
	return objectName;	
};

#ifndef DEBUG_MOOS 

zBOOL zCObject::SetObjectName (const zSTRING& name)	
{ 
	zBOOL shared = (GetClassDef()->GetClassFlags() & zCLASS_FLAG_SHARED_OBJECTS);

	if (!shared) {
		objectName=name; 
		objectName.Upper();
	} 
	else 
	{
		// Name bereits vergeben ?
		if (GetClassDef()->SearchHashTable (name))	
		{
			// sollte in der Regel auf einen Appl. Fehler hinweisen
			zERR_WARNING ("D: OBJ: SetObjectName() on shared object class '"+GetClassName_()+"' failed: object with that name already exists! "+name);
			return FALSE;
		};

		zBOOL firstName = objectName.IsEmpty();

		// erster nicht-leerer Name der vergeben wird	=> in hashTable eintragen
		if (firstName && !name.IsEmpty())	{
			objectName = name; 
			objectName.Upper();
			GetClassDef()->InsertHashTable (this);	
		} else
		// objekt hatte namen, bekommt leeren Namen		=> aus hashTable entfernen
		if (!firstName && name.IsEmpty())	{
			objectName = name; 
			objectName.Upper();
			GetClassDef()->RemoveHashTable (this);	
		} else
		// objekt hatte namen, bekommt neuen Namen		=> move hashBin
		if (!firstName && !name.IsEmpty())	{
			GetClassDef()->RemoveHashTable (this);
			objectName	= name; 
			objectName.Upper();
			GetClassDef()->InsertHashTable (this);
		};
	};

	return TRUE;
};

#endif // DEBUG_MOOS

// =================================================================================================================

zBOOL				zCClassDef::startupFinished				= FALSE;
zCClassDef*			zCClassDef::classDefSearchDummy			= 0;
enum				{ zCLASSDEF_NUM_HASH = 1024 };							// muss pow2, niemals mehr als 16Bit

int zCClassDef::CompareClassDefNames (const void* em1, const void* em2) {
	return ((*(zCClassDef**)em1))->className.CompareTo(((*(zCClassDef**)em2))->className);
};

zCClassDef*	zCClassDef::GetClassDef (const zSTRING& className)
{
	classDefSearchDummy->className = className;
	int index = classDefList->Search (classDefSearchDummy);
	if (index<0)	return 0;
	return (*classDefList)[index];
};

zCClassDef*	zCClassDef::GetClassDefTypeInsensitive (const zSTRING& className)
{
	zSTRING name2;
	zSTRING name(className);
	name.Upper();
	for (int i=0; i<zCClassDef::classDefList->GetNum(); i++) {
		name2 = (*zCClassDef::classDefList)[i]->GetClassName_();
		name2.Upper();
		if (name2==name)	return (*zCClassDef::classDefList)[i];
	};
	return 0;
};

zCClassDef::zCClassDef() {
	Init();
};

#ifndef DEBUG_MOOS

void zCClassDef::Init() {
	className				.Clear();
	baseClassName			.Clear();
	scriptClassName			.Clear();
	baseClassDef			= 0;
	createNewInstance		= 0;
	createNewInstanceBackup	= 0;
	numLivingObjects		= 0;
	numCtorCalled			= 0;
	hashTable				= 0;
	archiveVersion			= 0;
	archiveVersionSum		= 0;
	classFlags				= 0;
	classSize				= 0;
}

#endif

// FIXME: destructor/constr private machen ??

zCClassDef::~zCClassDef()
{
	//
	ReportLeaks();

	//
	delete[] hashTable;	hashTable=0;

	// ptr auf 0 setzen
	baseClassDef			= 0;
	createNewInstance		= 0;
	createNewInstanceBackup	= 0;

	// 
	if (classDefList)
	{
		// noetig!
		classDefList->Remove (this);

		//
		if (classDefList->GetNum()<=0) {
			delete classDefList;		classDefList		= 0;
			delete classDefSearchDummy;	classDefSearchDummy	= 0;	// Achtung: 'rekursiver' Aufruf!
		};
	};

	// ACHTUNG: in Destruktoren duerfen keine zCObject-Services benutzt werden !
	
/*	// Check if any subclasses were initialized before their superclass
	zCClassDef *node;
	for (int i=0; i<classDefList->.GetNum(); i++) {
		node = classDefList->[i];
		if (node->baseClassDef==this)
		{
			node->baseClassDef = 0;
		}
	}
*/
};

void zCClassDef::EndStartup()
{
	if (!classDefList) return;
	classDefList->QuickSort();

	// ACHTUNG:
	// Die Archiver-Versions-Checksummen Berchnung ist leider in der vorliegenden Version ('A') buggy: die 
	// resultierenden Checksummen haengen von Anzahl/Art der vorhandenen Klassen ab. Das Hinzufuegen/Entfernen/Umbenennen
	// einer Klasse (per zCLASS_DEFxxx) kann die VerChecksums anderer Klassen aendern. Konkrete Folge im 
	// ArchiverGeneric/Binary: tatsaechlich noch kompatible Binaer-Archive werden als nicht lesbar abgewiesen, was derzeit
	// leider bei den SaveGames nicht akzeptabel ist. 
	// Ergo: Die eigentlich fehlerhafte Variante 'A' bleibt derzeit noch aktiv.

#if 1
	// Checksummen Berechnung 'A'
	for (int i=0; i<classDefList->GetNum(); i++) 
	{
		zCClassDef *node	= (*classDefList)[i];
		node->baseClassDef	= GetClassDef (node->GetBaseClassName());

		// Archive-Version Checksum berechnen
		zCClassDef*		classDef = node;
		zCChecksum16	csum; 
		csum.BeginChecksum();
		while (classDef) 
		{
			csum.CalcBufferChecksum ((zBYTE*)&classDef->archiveVersion, sizeof(classDef->archiveVersion));
			classDef			= classDef->GetBaseClassDef();
		};
		csum.EndChecksum();
		node->archiveVersionSum	= csum.GetChecksum();
	}
#else
	// Checksummen Berechnung 'B'
	// 1. Pass: Basisklassen eintragen
	for (int i=0; i<classDefList->GetNum(); i++) 
	{
		zCClassDef *node	= (*classDefList)[i];
		node->baseClassDef	= GetClassDef (node->GetBaseClassName());
	};
	// 2. Pass: Checksummen zur RootBaeClass hin berechnen
	for (    i=0; i<classDefList->GetNum(); i++) 
	{
		// Archive-Version Checksum berechnen
		zCClassDef		*node	= (*classDefList)[i];
		zCClassDef*		classDef= node;
		zCChecksum16	csum; 
		csum.BeginChecksum();
		while (classDef) 
		{
			csum.CalcBufferChecksum ((zBYTE*)&classDef->archiveVersion, sizeof(classDef->archiveVersion));
			classDef			= classDef->GetBaseClassDef();
		};
		csum.EndChecksum();
		node->archiveVersionSum	= csum.GetChecksum();
	}
#endif
	startupFinished = TRUE;
};
	

zCClassDef::zCClassDef (const zSTRING&	className, 
						const zSTRING&	baseClassName, 
						zCObject*		( *_CreateNewInstance )(), 
						const zDWORD	classSize,
						const zDWORD	classFlags, 
						const zWORD		arcVers, 
						const zSTRING&	scriptClassName )
{
	Init();

	if (classDefList==0) {
		classDefList				= zNEW(zCArraySort<zCClassDef*>) (180);	// letzte Messung: 163 Klassen (inkl Game)
		classDefList->SetCompare	(CompareClassDefNames);
		classDefSearchDummy			= zNEW(zCClassDef);
	};
//	zerr.Message ("D: "+className +", "+baseClassName + ", "+zSTRING(classDefList->GetNum()));
	this->className					= className;
	this->baseClassName				= baseClassName;
	this->createNewInstance			= _CreateNewInstance;
	this->createNewInstanceBackup	= _CreateNewInstance;
	this->baseClassDef				= zCObject::GetClassDef (baseClassName);
	this->archiveVersion			= arcVers;
	this->classSize					= classSize;
	this->classFlags				= classFlags;
	this->scriptClassName			= scriptClassName;
	this->numLivingObjects			= 0;
	if (this->GetClassFlags() & zCLASS_FLAG_SHARED_OBJECTS) 
	{
		this->hashTable				= zNEW(zCObject*) [zCLASSDEF_NUM_HASH];
		memset (this->hashTable, 0, sizeof(zCObject*)*zCLASSDEF_NUM_HASH);
	};

	// folgender Code sorgt fuer die Aufloesung des Base-Class Ptrs bei bereits eingetragenen Klassen
	// scheint aber a) nicht korrekt zu funktionieren und ist b) ueberfluessig geworden durch ::EndStartup()
/*	// Check if any subclasses were initialized before their superclass
	const zSTRING rootClassName("zCObject");						// darf nicht static ausserhalb dieser func => orderOfConstr..
	zCClassDef	*node;
	for (int i=0; i<classDefList->GetNum(); i++) {
		node = (*classDefList)[i];
		if ( (!node->baseClassDef) && (node->GetBaseClassName()==this->className) && (node->GetClassName_()!=rootClassName) )
			node->baseClassDef	= this;
	}
*/	
	// insert
	classDefList->Insert (this);
};

zCObject* zCClassDef::CreateNewInstance	() const { 
	if (createNewInstance) return createNewInstance();	
	zERR_FAULT("D: zObject(zCClassDef::CreateNewInstance): tried to create instance of abstrace class: "+GetClassName_());
	return 0;
};

void zCClassDef::OverwriteCreateNewInstance (zCClassDef* dominantClass) {
	if (IsAbstractClass() || dominantClass->IsAbstractClass()) return;

	createNewInstance = dominantClass->createNewInstance;
};

void zCClassDef::ResetCreateNewInstance ()
{
	if (IsAbstractClass()) return;
	createNewInstance = createNewInstanceBackup;
};

zTClassID zCClassDef::GetClassID () 
{
	return zTClassID(classDefList->Search(this));
};

zCObject* zCClassDef::CreateNewInstanceID (zTClassID id)
{
	int index = int(id);
	assert (index>=0);
	assert (index<classDefList->GetNum());
	return (*classDefList)[index]->CreateNewInstance();
};

// hash table

zDWORD zCClassDef::GetHashIndex (const zSTRING& name)
{
	return (zCChecksum::GetBufferCRC32 ((unsigned char*)name.ToChar(), name.Length())) & (zCLASSDEF_NUM_HASH-1);
};

zDWORD zCClassDef::GetHashIndex (zCObject *object)
{
	return (zCChecksum::GetBufferCRC32 ((unsigned char*)object->GetObjectName().ToChar(), object->GetObjectName().Length())) & (zCLASSDEF_NUM_HASH-1);
};

void zCClassDef::InsertHashTable (zCObject *object)
{
	const zDWORD hash	= GetHashIndex(object);
	zCObject*	next	= hashTable [hash];
	hashTable [hash]	= object;
	object->hashNext	= next;
	object->hashIndex	= zWORD(hash);
//	objectList.Insert	(object);
};

void zCClassDef::RemoveHashTable (zCObject *object)
{
//	const zDWORD hash = GetHashIndex(object);
	const zDWORD hash = object->hashIndex;
	for (zCObject** prevLink=&hashTable[hash]; *prevLink; prevLink=&(*prevLink)->hashNext)
	{
		if ((*prevLink)==object)
		{
			*prevLink			= (*prevLink)->hashNext;
			object->hashNext	= 0;
			object->hashIndex	= 0xFFFF;
//			objectList.Remove	(object);		// Achtung: O(n)..
			return;
		}
	}
};

zCObject* zCClassDef::SearchHashTable (const zSTRING& objectName)
{
	if (objectName.IsEmpty()) return 0;
	const zDWORD hash = GetHashIndex(objectName);
	for (zCObject* hashObject=hashTable[hash]; hashObject; hashObject=hashObject->hashNext )
	{
		if (hashObject->GetObjectName()==objectName)	return hashObject;
	}
	return 0;
};

float zCClassDef::CalcHashTableSpread () 
{
	if (!hashTable)	return 0;
	int num = 0;
	for (int i=0; i<zCLASSDEF_NUM_HASH; i++) {
		if (hashTable[i])	
			num++;
	}
	return (float(num) / zCLASSDEF_NUM_HASH);
};

// object new/delete registration

#ifndef DEBUG_MOOS

void zCClassDef::ObjectCreated (zCObject *object, zCClassDef *objClassDef)
{
	objClassDef->numLivingObjects++;
	objClassDef->numCtorCalled++;
	if (objClassDef->GetClassFlags() & zCLASS_FLAG_SHARED_OBJECTS)
		objClassDef->objectList.Insert (object);

	if (objClassDef==zCObject::GetStaticClassDef()) {
		zERR_FAULT ("D: created instance of abstract 'zCObject' ?! => missing zCLASS_DECLARATION ?");
	};
};

void zCClassDef::ObjectDeleted (zCObject *object, zCClassDef *objClassDef) 
{
	// ACHTUNG: der object->objectName ist hier nicht mehr verfuegbar, da bereits DELETED !
	objClassDef->numLivingObjects--;
	if (objClassDef->GetClassFlags() & zCLASS_FLAG_SHARED_OBJECTS)
		objClassDef->objectList.Remove (object);			// Achtung: O(n)..

	// aus HashTable entfernen ?
	if (objClassDef->GetClassFlags() & zCLASS_FLAG_SHARED_OBJECTS) 
//	if (!object->GetObjectName().IsEmpty())
	if (object->hashIndex!=0xFFFF)				// 
	{
		objClassDef->RemoveHashTable (object);
	};
};

#endif // DEBUG_MOOS

void zCClassDef::ObjectCreated (zCObject *object, int size, zCClassDef *objClassDef)
{
	int num = size / sizeof(*object);
	for (int i=0; i<num; i++) {
		ObjectCreated (object, objClassDef);
		object++;
	};
};

void zCClassDef::ObjectDeleted (zCObject *object, int size, zCClassDef *objClassDef)
{
	int num = size / sizeof(*object);
	for (int i=0; i<num; i++) {
		ObjectDeleted(object, objClassDef);
		object++;
	};
};



//#ifndef DEBUG_MOOS

void zCClassDef::ReportLeaks ()
{
	if (GetNumLivingObjects()>0) 
	{
#ifdef DEBUG_MOOS
		zERR_MESSAGE (0,0, "D: OBJ: " + GetClassName_() +  "[" + zSTRING(class_id) +  "]" + " leaks, num: "+zSTRING(GetNumLivingObjects()));
#else
		zERR_MESSAGE (0,0, "D: OBJ: " + GetClassName_() + " leaks, num: "+zSTRING(GetNumLivingObjects()));
#endif

		static zBOOL showedDialog=FALSE;
		if (!showedDialog)
		{

//#ifndef DEBUG_HILDEBRANDT
			zERR_WARNING("D: OBJ: Memory leaks found!");
//#endif

			showedDialog = TRUE;
        }
                

        int c=0;

    	for (int i=objectList.GetNum()-1;i>=0; i--){
            zCObject *o=objectList[i];

            if (c < 4 && o->refCtr)
            {
                zerr.Message ("D: OBJ: " + zSTRING(i) + 
#ifdef DEBUG_MOOS
                " ID= " + zSTRING(o->identification) + " : " +
#endif
                o->GetObjectName() + ", refs: " + zSTRING(o->GetRefCtr()));

#ifdef ZACCOUNT
                zCAccount::Sum(o);
#endif

            }

            c++;
        };
	};

};


//#endif // DEBUG_MOOS

void zCClassDef::GetLivingObjectsState (zCLivingObjectsState& loState)
{
	loState.numList.AllocAbs			((*classDefList).GetNum());
	loState.numList.MarkNumAllocUsed	();
	for (int i=0; i<(*classDefList).GetNum(); i++) {
		loState.numList[i] = (*classDefList)[i]->GetNumLivingObjects();
	};
};

void zCClassDef::CompareLivingObjectsState (const zCLivingObjectsState& loState) 
{
	if (loState.numList.GetNum()!=(*classDefList).GetNum()) return;
	zERR_MESSAGE (1, 0, "D: OBJ: Printing difference in numLivingObjects between two states..");
	for (int i=0; i<(*classDefList).GetNum(); i++) {
		zCClassDef *classDef= (*classDefList)[i];
		int numOld			= loState.numList[i];
		int numNow			= classDef->GetNumLivingObjects();
		if (numOld!=numNow)
			zERR_WARNING ("D: OBJ: "+classDef->GetClassName_()+", diff: "+zSTRING(numNow-numOld));
	};
};

// =================================================================================================================

// zCObjectFactory
#include <zSession.h>
#include <zCCSPlayer.h>
#include <zDisk.h>
#include <zNetVobControl.h>
#include <zWaynet.h>
// zVob.h fuer zCEventManager
#include <zEventMan.h>
//#include <zVob.h>
#ifdef _VDFS
	#include "zdisk_vdfs.h"
#endif

zCObjectFactory* zfactory = 0;

/* ----------------------------------------------------------------------
	
	zCObjectFactory :: CreateZFile()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

zFILE* zCObjectFactory::CreateZFile (const zSTRING& fileName) 
{ 
	#ifdef _VDFS
		return zNEW(zFILE_VDFS)(fileName);
	#else
		return zNEW(zFILE_FILE)(fileName);
	#endif
};

zCEventManager* zCObjectFactory::CreateEventManager	(zCVob* hostVob) 
{ 
	return zNEW(zCEventManager(hostVob));
}

zCNetVobControl* zCObjectFactory::CreateNetVobControl (zCVob* hostVob)
{ 
        zCNetVobControl* ctrl = zNEW(zCNetVobControl()); 
        ctrl->Init(hostVob);
        return ctrl;
};

zCWaypoint* zCObjectFactory::CreateWaypoint() 
{ 
		return zNEW(zCWaypoint()); 
};

zCWay* zCObjectFactory::CreateWay() 
{ 
        return zNEW(zCWay()); 
};

zCSession* zCObjectFactory::CreateSession () {
	return zNEW(zCSession());
};

zCCSManager* zCObjectFactory::CreateCSManager() 
{	
	return zNEW(zCCSManager());
};

zCWorld* zCObjectFactory::CreateWorld()
{	
	return zNEW(zCWorld);
};

// =================================================================================================================


#ifdef _DEBUG

zCObject* zCObject::AddRefDebug(const char* file, int line)
{
	zERR_MESSAGE(9,0,"B: REFCTR: ++ (\""+GetObjectName()+"\" "+zSTRING(GetRefCtr())+"->"+zSTRING(GetRefCtr()+1)+"),  file \""+zSTRING(file)+"\" line "+zSTRING(line));
	return AddRef();
};

int zCObject::ReleaseDebug(const char* file, int line)
{
	zERR_MESSAGE(9,0,"B: REFCTR: -- (\""+GetObjectName()+"\" "+zSTRING(GetRefCtr())+"->"+zSTRING(GetRefCtr()-1)+"),  file \""+zSTRING(file)+"\" line "+zSTRING(line));
	return Release();
};

#endif

