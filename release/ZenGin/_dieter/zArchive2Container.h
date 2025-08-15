/******************************************************************************** 
 
     $Workfile:: zArchive2container.h $                $Date:: 4.12.00 17:18    $
     $Revision:: 5                    $             $Modtime:: 4.12.00 16:32    $
        Author:: Hoeller
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Archiver (OOP persistance system)
   created       : ?.8.2000

 * $Log: /current_work/zengin_work/_Dieter/zArchive2container.h $
 * 
 * 5     4.12.00 17:18 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author Author: Hoeller 
/// @version $Revision: 5 $ ($Modtime: 4.12.00 16:32 $)

#ifndef __ZARCHIVER2CONTAINER_H__
#define __ZARCHIVER2CONTAINER_H__

#ifndef __ZMEMORY_H__
#include "zMemory.h"
#endif
 
//////////////////////////////////////////////////////////////////////////////////
// typedef of primitivetypes
typedef void*			GELPVoid;
typedef const void*		GELPCVoid;
typedef char*			GELPChar;
typedef const char*		GELPCChar;
typedef char			GEChar;
typedef unsigned char	GEU8;
typedef signed   char	GEI8;
typedef unsigned short	GEU16;
typedef signed   short	GEI16;
typedef signed   long	GEI32;
typedef unsigned long	GEU32;
typedef int				GEInt;
typedef signed __int64	GEI64;
typedef unsigned __int64 GEU64;
typedef bool			GEBool;
typedef float			GEFloat;
typedef double			GEDouble;
//////////////////////////////////////////////////////////////////////////////////
#define GETrue			true
#define GEFalse			false

#define NULL 0

#ifndef GE_SYSMAN_CALLAPI
	#define GE_SYSMAN_CALLAPI __stdcall
#endif

/*
#define DllImport extern __declspec( dllimport )
DllImport	GELPVoid		GE_SYSMAN_CALLAPI GESysMalloc(const size_t size, GELPChar objType, GELPChar name, GELPChar file, GEInt line);
DllImport	GELPVoid		GE_SYSMAN_CALLAPI GESysCalloc(const size_t num, const size_t size, GELPChar objType, GELPChar name, GELPChar file, GEInt line);
DllImport	void			GE_SYSMAN_CALLAPI GEFree(GELPVoid block);
DllImport	GELPVoid		GE_SYSMAN_CALLAPI GESysRealloc(GELPVoid block, const size_t size, GELPChar objType, GELPChar name, GELPChar file, GEInt line);
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
class GECString
{
public:
	GECString()
	{
		Text = NULL;
	}
	GECString( GELPCChar source )
	{
		Text = NULL;
		if( source != NULL )
			Copy( source );
	}
	
	~GECString()
	{
		Free();
	}
	void Free()
	{
		if( Text != NULL ) 
		{
			delete[]Text;
			Text = NULL;
		}
	}
	void Copy( GELPCChar source )
	{
		Reserve( strlen( source ) + 1 );
		strcpy( Text, source );
	}
	
	void Reserve( GEU32 size )
	{
		if(Text)
			delete[] Text ;
		Text = zNEW(char)[size];
	}
	GECString &operator=( GELPCChar source )
	{
		Free();

		if( source != NULL )
			Copy( source );

		return *this;
	}

	GEInt Compare( const GECString &string ) const
	{

		if( Text == NULL && string.Text == NULL )
			return 0;

		if( Text == NULL || string.Text == NULL )
			return -1;

		return _tcscmp( Text, string.Text );
	}

	GEInt Compare( GELPCChar string ) const
	{
		if( Text == NULL && string == NULL )
			return 0;

		if( Text == NULL || string == NULL )
			return -1;

		return _tcscmp( Text, string );
	}
	
	friend GEBool operator==( const GECString &stringA, const GECString &stringB )
	{
		return( stringA.Compare( stringB ) == 0 );
	}

	friend GEBool operator==( const GECString &stringA, GELPCChar stringB )
	{
		return( stringA.Compare( stringB ) == 0 );
	}

	friend GEBool operator==( GELPCChar stringA, const GECString &stringB )
	{
		return( stringB.Compare( stringA ) == 0 );
	}

	void		Clear()
	{
		Free();
	}

	GEU32		GetLength()
	{
		if(Text==NULL) return 0;
		return strlen(Text);
	}

	char*		GetText()
	{
		return (char*)Text;
	}
protected:
	GELPChar	Text;
};


struct GESStringMapStorage
{
	GEU16	HashMapStringLen;
	GEU16	LinearValue;
	GEU32	HashValue;
};

template <class T> class GETStringMap
{
protected:
	struct GESNextEntry
	{
		GESNextEntry*	Next;
		GEU32			HashValue;		// needed for efficient iteration
		GEU32			LinearValue;	// needed for linear enumeration
		GECString*		Key;
		T*				Object;
		GESNextEntry()
		{
			Key = zNEW(GECString);
			Object = NULL;
		}
		~GESNextEntry()
		{
			delete Key;
			Key = NULL;
		}
	};
	
	GESNextEntry*	EnumElement;
	GESNextEntry**	HashTable;
	GEU32			HashTableSize;
	GEInt			NCount;

	void	InitHashTable(GEU32 hashSize, GEBool allocNow=GETrue);
	GEU32	HashKey(GELPCChar key) const;
	GEBool	LookupKey(GELPCChar key, GELPCChar& rKey) const;
	GESNextEntry* GetElement(GELPCChar key, GEU32& nHash, GEU32 linearValue) const;
public:	
	GETStringMap()
	{
		HashTable = NULL;
		HashTableSize = 97;  // default size
		NCount = 0;
		EnumElement = NULL;
	}
	
	~GETStringMap()
	{
		RemoveAll();
	}

	GEInt	GetCount() const;
	GEBool	IsEmpty() const;
	//T*&		operator[](GELPCChar key);
	GEU32	SetAt(GELPCChar key, T* newObject);
	GEU32	SetAtForce(GELPCChar key, T* newObject, GEU32 nHash, GEU32 linearValue);
	GEU32	GetHashTableSize() const;
	GEBool	RemoveKey(GELPCChar key);
	void	RemoveAll(GEBool deleteObject=GEFalse);
	GEU32	Lookup(GELPCChar key, T*& object, GEU32 linearValue=0xffffffff) const;
	GEBool	GetFirstElement(GEU32& linearValue, GECString& key, T*& object, GEU32& hashValue);
	GEBool	GetNextElement(GEU32& linearValue, GECString& key, T*& object, GEU32& hashValue);
};

template<class T>
inline void GETStringMap<T>::InitHashTable(GEU32 hashSize, GEBool allocNow)
{
	if(NCount!= 0) return;
	if(HashTableSize==0) return;
	if (HashTable != NULL)
		delete[] HashTable;
	if (allocNow)
	{
		HashTable = zNEW (GETStringMap::GESNextEntry*)[hashSize];
		//GE_ARR_NEW(HashTable, GETStringMap::GESNextEntry*, hashSize, "GETStringMap::HashTable");
		memset(HashTable, 0, sizeof(GETStringMap::GESNextEntry*) * hashSize);
	}
	HashTableSize = hashSize;
}

template<class T>
inline GEU32 GETStringMap<T>::HashKey(GELPCChar key) const
{
	GEU32 nHash = 0;
	while (*key)
		nHash = (nHash<<5) + nHash + *key++;
	return nHash;
}

template<class T>
inline GEInt GETStringMap<T>::GetCount() const
{ 
	return NCount; 
}

template<class T>
inline GEBool GETStringMap<T>::IsEmpty() const
{ 
	return NCount == 0; 
}

template<class T>
GEU32 GETStringMap<T>::SetAt(GELPCChar key, T* newObject)
{ 
	//(*this)[key] = newObject; 

	GEU32 nHash;
	GETStringMap::GESNextEntry* assoc = NULL;
	if ((assoc = GetElement(key, nHash, 0xffffffff)) == NULL)
	{
		if (HashTable == NULL)
			InitHashTable(HashTableSize);
		// it doesn't exist, add a new Association
		if(NCount < 0) return 0xffffffff;
		assoc = zNEW(GETStringMap::GESNextEntry);
		assoc->LinearValue = NCount;
		NCount++;
		//assoc->Key.Clear();
		assoc->HashValue = nHash;
		*assoc->Key = key;
		assoc->Object = newObject;
		// 'pAssoc->value' is a constructed object, nothing more
		// put into hash table
		assoc->Next = HashTable[nHash];
		HashTable[nHash] = assoc;
	}
	return assoc->LinearValue;  // return new linear counter
}

template<class T>
GEU32 GETStringMap<T>::SetAtForce(GELPCChar key, T* newObject, GEU32 nHash, GEU32 linearValue)
{ 
	//(*this)[key] = newObject; 

	GETStringMap::GESNextEntry* assoc = NULL;
	if (HashTable == NULL)
		InitHashTable(HashTableSize);
	// it doesn't exist, add a new Association
	if(NCount < 0) return 0xffffffff;
	assoc = zNEW(GETStringMap::GESNextEntry);
	assoc->LinearValue = linearValue;
	NCount++;
	assoc->HashValue = nHash;
	*assoc->Key = key;
	assoc->Object = newObject;
	// 'pAssoc->value' is a constructed object, nothing more
	// put into hash table
	assoc->Next = HashTable[nHash];
	HashTable[nHash] = assoc;
	return assoc->LinearValue;  // return new linear counter
}


template<class T>
inline GEU32 GETStringMap<T>::GetHashTableSize() const
{ 
	GE_ASSERT_THIS();
	return HashTableSize; 
}

template<class T>
inline GEU32 GETStringMap<T>::Lookup(GELPCChar key, T*& object, GEU32 linearValue) const
{
	GEU32 nHash;
	GETStringMap::GESNextEntry* assoc = GetElement(key, nHash, linearValue);
	if (assoc == NULL)
		return 0xffffffff;
	object = assoc->Object;
	return assoc->LinearValue;
}

template<class T>
inline GEBool GETStringMap<T>::LookupKey(GELPCChar key, GELPCChar& rKey) const
{
	GEU32 nHash;
	GETStringMap::GESNextEntry* assoc = GetElement(key, nHash);
	if (assoc == NULL)
		return GEFalse; 
	rKey = assoc->Key;
	return GETrue;
}

template<class T>
inline GETStringMap<T>::GESNextEntry* GETStringMap<T>::GetElement(GELPCChar key, GEU32& nHash, GEU32 linearValue) const
{
	nHash = HashKey(key) % HashTableSize;
	if (HashTable == NULL)
		return NULL;
	// see if it exists
	GETStringMap::GESNextEntry* assoc;
	for (assoc = HashTable[nHash]; assoc != NULL; assoc = assoc->Next)
	{
		if(linearValue==0xffffffff)
		{
			if (*assoc->Key==key)
				return assoc;
		}
		else
		{
			if (assoc->LinearValue==linearValue)
				return assoc;
		}
	}
	return NULL;
}

template<class T>
void GETStringMap<T>::RemoveAll(GEBool deleteObject)
{
	if (HashTable != NULL)
	{
		// destroy elements
		for (GEU32 nHash = 0; nHash < HashTableSize; nHash++)
		{
			GETStringMap::GESNextEntry* assoc;
			GETStringMap::GESNextEntry* lastAssoc = NULL;
			for (assoc = HashTable[nHash]; assoc != NULL; assoc = assoc->Next)
			{
				if(deleteObject==GETrue)
					if(assoc->Object)
						delete assoc->Object;
				//assoc->Key->Clear();
				delete lastAssoc;
				lastAssoc = assoc;
			}
			delete lastAssoc;
		}
		delete[]HashTable;
		HashTable = NULL;
	}
	NCount = 0;
}


template<class T>
GEBool GETStringMap<T>::GetFirstElement(GEU32& linearValue, GECString& key, T*& object, GEU32& hashValue)
{
	EnumElement = NULL;
	return GetNextElement(linearValue, key, object, hashValue);
}


template<class T>
GEBool GETStringMap<T>::GetNextElement(GEU32& linearValue, GECString& key, T*& object, GEU32& hashValue)
{
	if (NCount==0) return GEFalse;
	if(HashTable==NULL) return GEFalse;

	GETStringMap::GESNextEntry* startPoint;
	GEU32 nHash, lHash;
	if(EnumElement==NULL)
	{
		nHash = 0;
		lHash = -1;
	}
	else
	{
		nHash = EnumElement->HashValue;
		lHash = nHash;
	}

	GEBool nextMatch = GEFalse;
	for (; nHash < HashTableSize; nHash++)
	{
		GETStringMap::GESNextEntry* assoc;
		if(lHash == nHash)
			startPoint = EnumElement;
		else 
			startPoint = HashTable[nHash];
		
		for (assoc = startPoint; assoc != NULL; assoc = assoc->Next)
		{
			if((EnumElement==NULL)||(nextMatch==GETrue))
			{
				EnumElement = assoc;
				key = EnumElement->Key->GetText();
				linearValue = EnumElement->LinearValue;
				object = EnumElement->Object;
				hashValue = EnumElement->HashValue;
				return GETrue;
			}
			if(assoc==EnumElement) nextMatch = GETrue;
		}
	}
	return GEFalse;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> class GETSmallArrayNative
{
private:
	GEU32		Entries;

	void Grow()
	{
		GEInt delta;
		if(Used>=Entries)
		{
			if (Entries > 64) delta = Entries / 4;
			else
			{
				if (Entries > 8) delta = 16;
				else delta = 4;
			}
			Entries += delta;
			T* newEntry = (T*) zmalloc.Realloc(Entry, sizeof(T)*Entries);
			Entry = newEntry;
		}
	}

public:
	GEU32		Used;
	T			*Entry;

	GETSmallArrayNative()
	{
		Entries = 1;
		Entry = (T*) zmalloc.Malloc (sizeof(T)*Entries);
		memset(Entry, 0, sizeof(T)*Entries);
		Used = 0;
	}
	GETSmallArrayNative(GEInt entries)
	{
		Entries = entries;
		Entry = (T*) zmalloc.Malloc(sizeof(T)*Entries);
		memset(Entry, 0, sizeof(T)*Entries);
		Used = 0;
	}
	
	GETSmallArrayNative<T> &operator=(GETSmallArrayNative<T> &classItem)
	{
		if( Entries == classItem.GetAllocatedEntries() )
		{
			Used = classItem.Used;
			memcpy(&Entry[0], &classItem.Entry[0], sizeof(T)*classItem.Used);
		}
		else
		{
			Used = classItem.Used;
			zmalloc.Free(Entry);
			Entry = (T*) zmalloc.Malloc (sizeof(T) * (classItem.Used + 1));
			memcpy(&Entry[0], &classItem.Entry[0], sizeof(T)*classItem.Used);
		}
		return *this;
	}

	GEU32 GetAllocatedEntries()
	{
		return Entries;
	}

	GEBool Reserve(GEU32 entries)
	{
		if(entries<Entries)
			return GEFalse;
		Entries = entries;
		T* newEntry = (T*) zmalloc.Realloc(Entry, sizeof(T)*Entries);
		Entry = newEntry;
		return GETrue;
	}

	GEU32 Add(T &item)
	{
		Grow();
		Entry[Used] = item;
		Used++;
		return Used-1;
	}

	void Remove(GEU32 ref)
	{
		if (Used==0) return;
		GEU32 i = Used-(ref+1);
		memmove(&Entry[ref], &Entry[ref+1], i*sizeof(T));
		Used--;
	}

	~GETSmallArrayNative() 
	{ 
		zmalloc.Free(Entry); 
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif