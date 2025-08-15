/******************************************************************************** 
 
     $Workfile:: zContainer.h         $                $Date:: 25.01.01 12:14   $
     $Revision:: 13                   $             $Modtime:: 25.01.01 10:21   $
       $Author:: Moos                                                           $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ container templates
   created       : 7.9.97

 * $Log: /current_work/ZenGin/_Dieter/zContainer.h $
 * 
 * 13    25.01.01 12:14 Moos
 * 
 * 12    24.01.01 14:57 Moos
 * 
 * 11    4.12.00 16:49 Hildebrandt
 * 
 * 10    2.11.00 1:41 Hildebrandt
 * 
 * 9     20.09.00 18:19 Hildebrandt
 * 
 * 8     31.08.00 21:22 Moos
 * 
 * 7     31.08.00 13:40 Moos
 * 
 * 6     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 5     21.07.00 14:28 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 7     18.02.00 1:39 Hildebrandt
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
/// @author $Author: Moos $
/// @version $Revision: 13 $ ($Modtime: 25.01.01 10:21 $)

#ifndef __ZCONTAINER_H__
#define __ZCONTAINER_H__

#include <assert.h>

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

#ifndef __ZERROR_H__
#include <zError.h>
#endif

#ifndef __ZMEMORY_H__
#include <zMemory.h>
#endif

#ifndef __ZMEMPOOL_H__
#include <zMemPool.h>
#endif


// ============================================================================================================
//														zCTree
// ============================================================================================================

zMEMPOOL_DECLARATION_TEMPLATE_EXTRA(zCTree, s_TreePool);

template <class T> class zCTree {
protected:
    zMEMPOOL_DECLARATION_TEMPLATE(zCTree, s_TreePool)

	zCTree* parent;
	zCTree* firstChild;
	zCTree* next;
	zCTree* prev;
	T*		data;

	void RemoveChild () {
		if (firstChild) {
			// subtree vorhanden !!
		};
		if (prev) prev->next	= next;
		if (next) next->prev	= prev;
		if (parent)
		if (this==parent->firstChild) {
			parent->firstChild = next;
		};
	};

public:
	zCTree() {
		// after creation a new node never has childs
		// wirklich alles nötig ??
		firstChild	= parent = next = prev = 0;
		data = 0;
	};

	~zCTree() {
		data=0;					// safety
		while (firstChild) { delete firstChild; } // [Moos] : weg mit firstChild=0; }; 
		RemoveChild();
	};

	void DeleteDataSubtree () {
		if (data) {
			delete data;
			data = 0;
		};
		// recursive traversal
		zCTree* child = GetFirstChild(); 
		while (child) {
			child->DeleteDataSubtree ();
			child = child->GetNextChild();
		};
	};
	void DeleteChilds() {
		while (firstChild) { delete firstChild; } // [Moos] wie oben firstChild=0; };
		RemoveChild();
	};
	
	T**  GetPtrToData	() const 	{ return &data; };
	T*   GetData		() const	{ return data; };
	void SetData		(T* d)		{ data = d; };

	zCTree* AddChild (T* d) {
		zCTree* newNode		= zNEW(zCTree);
		newNode->parent		= this;
		newNode->prev		= 0;
		newNode->next		= firstChild;
		newNode->data		= d;
		firstChild			= newNode;
		if (newNode->next!=0)
		newNode->next->prev	= newNode;
		return newNode;
	};

	zCTree* AddChild (zCTree* node) {
		node->parent		= this;
		node->prev			= 0;
		node->next			= firstChild;
		firstChild			= node;
		if (node->next!=0)
		node->next->prev	= node;
		return node;
	};

	// functions to traverse tree manualy
	zCTree* GetParent	  () { return parent; };
	zCTree* GetFirstChild () { return firstChild; };
	zCTree* GetNextChild  () { return next; };
	zCTree* GetPrevChild  () { return prev; };
	int		GetNumChilds  () {
		int num=0;
		zCTree* child = GetFirstChild();
		while (child!=0) {
			num++;
			child=child->GetNextChild();
		};
		return num;
	};

	// Search for ptr to specific data
	zCTree* Search (T* d) {
		// recursive search
		if (data==d) return this;
		zCTree* child = GetFirstChild();
		while (child!=0) {
			zCTree* res = child->Search (d);
			if (res!=0) return res;
			child = child->GetNextChild();
		};
		return 0;								// nothing found
	};

	// Search for specific Node
	int Search (const zCTree* node) {
		// recursive search
		if (this==node) return 1;
		zCTree* child = GetFirstChild();
		while (child!=0) {
			if (child->Search (node)) return 1;
			child = child->GetNextChild();
		};
		return 0;								// nothing found
	};

	// gives the total number of nodes in the tree, starting from (this)
	int CountNodes () {
		// recursive depth-traversal
		int a,b;
		a=b=0;
		if (firstChild!=0)	a = firstChild->CountNodes ();
		if (next!=0)		b = next->CountNodes ();
		return a+b+1;
	};

	// cuts the subtree from the tree it is part of
	void RemoveSubtree () {
		// [EDENFELD] 1.09d: Null Ptr Crash abgefangen. HOTFIX only. FIXME: Unklar, warum das zustande kommen kann
		if (parent && parent->firstChild==this) {
			parent->firstChild = next;
		};
		
		if (prev!=0) prev->next	= next;
		if (next!=0) next->prev	= prev;
		prev=next=0;
	};

	// Moves Subtree from the tree/position it is part of to a new parent-node
	void MoveSubtreeTo (zCTree* destParent) {
		RemoveSubtree();
		if (destParent) destParent->AddChild (this);
		else			parent=0;
	};
};

/*
- AddChild		(node)
- RemoveNode	(node)
- RemoveSubtree	(node)
- MoveSubtree	(node)
- Search		(T)
- Search
- GetFirstChild
- GetNextCild
*/


// ============================================================================================================
//														zCList2
// ============================================================================================================

zMEMPOOL_DECLARATION_TEMPLATE_EXTRA(zCList2, s_ListPool);

template <class T> class zCList2
{
protected:
    zMEMPOOL_DECLARATION_TEMPLATE(zCList2, s_ListPool);

//	int (*Compare)(T *ele1,T *ele2);
	int count;
public:
	T *wurzel;

	// Init It.
	zCList2 () 
	{ 
		wurzel = 0; 
		count  = 0;
	}

	// Setze Sortierroutine
/*	void SetCompare( int (*Cmp)(T *ele1,T *ele2) )
	{
		Compare = Cmp;
	}
*/
	// Delete the complete list
	void DeleteList() 
	{
		T *item,*help;
		item = wurzel;
		while (item!=0) {
			help = item;
			item  = item->next;
			delete(help);
		}
		wurzel = 0;
		count  = 0;
	};
	
	// Insert an Item
	void Insert ( T *ins ) 
	{
		ins -> next = wurzel;
		wurzel      = ins;
		count++;
	}

	// Insert an Item (sorting)
/*	void InsertSort (T *ins)
	{
		T *item;
		
		if ((wurzel==0) || (Compare(ins,wurzel)<0)) {
			// Erstes Element
			ins->next = wurzel;
			wurzel    = ins;
			count++;
		} else {
			item = wurzel;
			while (item->next != 0) {
				if (Compare(ins,item->next)<=0) {
					// Mittendrin, statt nur dabei
					ins->next = item->next;
					item->next = ins;
					count++;
					return;
				}
				item = item->next;
			}
			// Letztes Element
			item -> next = ins;
			ins -> next = 0;
			count++;
		}
	}
*/
	// Remove Item
	void Remove( T *rem )
	{
		T *item = wurzel;
		
		if (item==0) return;
		if (item==rem) {
			wurzel = item->next;
			count--;
		} else {
			while (item->next!=0) {
				if (item->next==rem) {
					item->next = rem->next;
					count--;
					return;
				}
				item = item->next;
			}
		}
	}
		
	// Delete Item	
	void Delete( T *rem )
	{
		T *item = wurzel;
		
		if (item==0) return;
		if (item==rem) {
			wurzel = item->next;
			delete(item);
			count--;
		} else {
			while (item->next!=0) {
				if (item->next==rem) {
					item->next = rem->next;
					delete(rem);
					count--;
					return;
				}
				item = item->next;
			}
		}
	}

	// Get Item
	// Indizierung von 0..n-1
	T* Get ( int nr ) const {
		T *item = wurzel;
		int c = 0;

		while (item!=0) {
			//c++;
			if (c==nr) return(item);
			item = item->next;
			c++;
		}
		return 0;
	};

	// Check, if Item is in list
	zBOOL InList (T *ele2) const
	{
		T *item = wurzel;

		while (item!=0) {
			if (item==ele2) return TRUE;
			item = item->next;
		}
		return FALSE;
	}
	
	// Return Counter ( Number of elements in list )
	int GetNumInList() const
	{
		return count;
	}
};


// ============================================================================================================
//													zCList
// ============================================================================================================


// - einfach verkettet
// - erzeugt Container-Objekte (=> Elemente können in mehreren Listen vom Typ zCList enthalten sein)

zMEMPOOL_DECLARATION_TEMPLATE_EXTRA(zCList, s_ListPool);

template <class T> class zCList {
protected:
    zMEMPOOL_DECLARATION_TEMPLATE(zCList, s_ListPool);

	T			*data;
	zCList		*next;
public:

	// Init It.
	zCList ()  { 
		next	= 0; 
		data	= 0;
	}

	~zCList () { 
//		DeleteList();
		// recursion !
		if (next) {
			delete next;
			next = 0;
		};
		data=0;
	};

	// Delete complete list
	void DeleteList()  {
		if (next) {
			// der Rest loescht sich rekursiv !
			delete next;
			next = 0;
		};
	};

	// Delete all List Datas from 'this' on, recursivley
	void DeleteListDatas()  {
		if (data) {
			delete data;
			data = 0;
		};
		// der Rest loescht sich rekursiv !
		if (next) {
			next->DeleteListDatas();
            delete next; // [Moos] leakfix
			next = 0;
		};
	};

	void Replace ( T *ins ) { data  = ins; };

	// Insert an Item 
	void Insert ( T *ins ) {
		zCList *newItem  = zNEW(zCList);
		newItem->data	 = ins;
		newItem->next	 = next;
		next			 = newItem;
	};

	void InsertFront ( T *ins ) {
		zCList *newItem  = zNEW(zCList);
		newItem->data	 = ins;
		newItem->next	 = next;
		next			 = newItem;
	};

	// Remove Item
	void Remove( T *rem ) {
		zCList *item = this;
		
		while (item->next!=0) {
			if (item->next->data==rem) {
				zCList *tmp	= item->next;
				item->next	= item->next->next;
				tmp ->next	= 0;
				delete tmp;
				return;
			}
			item = item->next;
		}
	}
		
	// Delete Item	
/*	void Delete( T *rem ) {
		T *item = wurzel;
		
		if (item==0) return;
		if (item==rem) {
			wurzel = item->next;
			delete(item);
			count--;
		} else {
			while (item->next!=0) {
				if (item->next==rem) {
					item->next = rem->next;
					delete(rem);
					count--;
					return;
				}
				item = item->next;
			}
		}
	}
*/
	// Get Item
	// Indizierung von 0..n-1
	T* Get (const int nr) const {
		zCList *item	= next;
		int		c		= 0;
		while (item) {
			if (c==nr) return item->data;
			item = item->next;
			c++;
		}
		return 0;
	};

	T* operator [] (const int nr) const { return Get (nr);	};

	zCList*		GetNextInList	() const { return next; };
	T*			GetData			() const { return data; };

	// Check, if Item is in list
	zBOOL InList (T *data) const {
		zCList *item = next;
		while (item!=0) {
			if (item->data==data) return TRUE;
			item = item->next;
		}
		return FALSE;
	}
	zBOOL IsInList (T *data) const {
		zCList *item = next;
		while (item!=0) {
			if (item->data==data) return TRUE;
			item = item->next;
		}
		return FALSE;
	}
	
	// Return Counter ( Number of elements in list )
	int GetNumInList() const { 
		int count = 0;
		zCList *item = next;
		while (item!=0) {
			count++;
			item = item->next;
		}
		return count;
	};
	int GetNum() const { return GetNumInList(); };
};


// ============================================================================================================
//													zCArray
// ============================================================================================================

const int zARRAY_START_ALLOC = 16;

template <class T> class zCArray {
protected:
	T		*array;
	int		numAlloc;
	int		numInArray;
public:
	zCArray() {
		numInArray	= 0;
		numAlloc	= 0;
		array		= 0;
	};
	zCArray(const int startSize) {
		numInArray	= 0;
		numAlloc	= startSize;
		array		= 0;
		if (startSize>0)
		array		= zNEW(T) [startSize];
	};
	zCArray (const zCArray<T>& array2) {
		// copy-constructor
		numInArray	= 0;
		numAlloc	= 0;
		array		= 0;
		AllocDelta	(array2.GetNumInList());
		numInArray	= array2.numInArray;
		for (int i=0; i<array2.GetNumInList(); i++)
			array[i]	= array2.array[i];
	};
	~zCArray() {
		delete[] array;
		array=0; // safety
	};
	T*	 GetArray	() const	{ return array; };
	void ZeroFill	()			{ if (array) memset (array, 0, sizeof (T)*numAlloc); };
	void AllocDelta (const int numDelta) {
		if (numDelta<=0) return;
		T *newArray = zNEW(T) [numAlloc+numDelta];
		if (numInArray>0) {
			for (int i=0; i<numInArray; i++)
				newArray[i] = array[i];		// safer, bei einem memcpy werden z.B. nur ptr auf zSTRINGs kopiert, der folgende delete[] killt diese Dann.. ARGH!
//			memcpy (newArray, array, sizeof(T)*numInArray);
		};
		delete[] array;
		array		=  newArray;
		numAlloc	+= numDelta;
	};
	void AllocAbs (const int size) {
		if (numAlloc>=size) return;
		AllocDelta (size-numAlloc);
	};
	void MarkNumAllocUsed () {
		numInArray = numAlloc;
	};
	void ShrinkToFit () {
		if (numInArray<=0) { DeleteList(); return; };
		if (numAlloc>numInArray) {
			T *newArray = zNEW(T) [numInArray];
			for (int i=0; i<numInArray; i++)
				newArray[i] = array[i];		// safer, bei einem memcpy werden z.B. nur ptr auf zSTRINGs kopiert, der folgende delete[] killt diese Dann.. ARGH!
    //			memcpy (newArray, array, sizeof(T)*numInArray);	// FIXME mempy
			delete[] array;
			array		= newArray;
			numAlloc	= numInArray;
		};
	};
	void operator = (const zCArray<T>& array2) {
		EmptyList	();
		AllocAbs	(array2.GetNumInList());
		numInArray	= array2.numInArray;
		for (int i=0; i<array2.GetNumInList(); i++)
			array[i]	= array2.array[i];
	};
	const T& operator [] (const int nr) const {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};
	T& operator [] (const int nr) {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};
/*	T  operator [] (const int nr) const {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};*/
	T& GetSafe (int nr) const {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		if (numInArray <=0)	zerr.Fatal ("D: zTree(zCArray::GetSafe): numInArray<=0");
		if (numAlloc   <=0)	zerr.Fatal ("D: zTree(zCArray::GetSafe): numAlloc  <=0");
		if (nr<0          ) nr = 0; else
		if (nr>=numInArray) nr = numInArray-1;
		return array[nr];
	};
	// inserts at the END
	void InsertEnd (const T& ins ) {
		if (numAlloc<numInArray+1) {
			if (numAlloc<zARRAY_START_ALLOC)	AllocDelta (zARRAY_START_ALLOC);
			else								AllocDelta (numAlloc / 2);
		};
		array[numInArray++] = ins;
	};
	/// inserts FRONT
	void InsertFront	(const T& ins )		{	InsertAtPos (ins, 0);	};
	/// inserts 'somewhere', fastest (no order guaranteed)
	void Insert			(const T& ins )		{	InsertEnd (ins);		};
	// inserts at position 
	void InsertAtPos	(const T& ins, int pos) {
		if (numAlloc<numInArray+1) {
			if (numAlloc<zARRAY_START_ALLOC)	AllocDelta (zARRAY_START_ALLOC);
			else								AllocDelta (numAlloc / 2);
		};
		// Alle nachfolgenden Elemente um eins nach hinten verschieben
		memmove(&array[pos+1],&array[pos],sizeof(T) * (numInArray - pos));
		array[pos] = ins;
		numInArray++;
	};
	// does NOT preserve order
	void Remove (const T& rem) {
		if (numInArray==0) return;
		for (int i=0; i<numInArray; i++) {
			if (array[i]==rem) {
				numInArray--;
				if (i!=numInArray) array[i] = array[numInArray];
				return;
			};
		};
	}
	// does NOT preserve order
	void RemoveIndex (const int index) {
		if (numInArray<=0) return;
		numInArray--;
		if (index!=numInArray) array[index] = array[numInArray];
	}
	// DOES preserve order
	void RemoveOrder (const T& rem) {
		for (int i=0; i<numInArray; i++) {
			if (array[i]==rem) {
				RemoveOrderIndex (i);
				return;
			};
		};
	};
	// DOES preserve order
	void RemoveOrderIndex (const int index) {
		if (index>=numInArray) return;
		if (index!=numInArray-1) 
			for (int j=index; j<numInArray-1; j++) array[j] = array[j+1];
		numInArray--;
		return;
	};
	void DeleteList() {
		delete[] array;
		array		= 0;
		numAlloc	= 0;
		numInArray	= 0;
	};
	void EmptyList () { numInArray = 0; };
	int  Search (const T& data)	const { 
		if (numInArray>0) {
			for (int i=0; i<numInArray; i++) if (array[i]==data) return i;
		};
		return -1;
	};
	int IsInList (const T& data) const {
		if (numInArray>0) {
			for (int i=0; i<numInArray; i++) if (array[i]==data) return TRUE;
		};
		return FALSE;
	};
	int GetNumInList() const { return numInArray; };
	int GetNum		() const { return numInArray; };
	zBOOL IsEmpty	() const { return (numInArray<=0); };
	// inserts another ARRAY at the END
	void InsertArray	(const zCArray<T>& other) {
		AllocAbs (other.GetNumInList()+GetNumInList());
		for (int i=0; i<other.GetNumInList(); i++)
			array[numInArray++] = other[i];
	};
	zBOOL CheckDoubles () {
		for (int i=0; i<GetNumInList()-1; i++)
			for (int j=i+1; j<GetNumInList(); j++)
				if (array[i]==array[j]) return TRUE;
		return FALSE;
	};
	void RemoveDoubles () {
		for (int i=0; i<GetNumInList()-1; i++)
			for (int j=i+1; j<GetNumInList(); j++)
				if (array[i]==array[j]) {
					array[j]=array[numInArray-1];
					numInArray--;
					j--;
				};
		return FALSE;
	};
};



// ============================================================================================================
//													zCArraySort
// ============================================================================================================

// FIXME: sollte wahrscheinlich besser von zCArray abgeleitet werden ...

// Sortierfunktion analog zu qsort, ideal für fast sortierte Listen.
// fallbacktoqs gibt an, ob auf qsort zurückgegriffen werden soll,
// wenn die Liste zu unsortiert ist.

void insertionsort(void *data, size_t num, size_t size, int (__cdecl *compare)(const void *, const void *),
                    bool fallbacktoqs);

extern int zArraySortDefaultCompare (const void* ele1,const void* ele2);

template <class T> class zCArraySort {
protected:
	T		*array;
	int		numAlloc;
	int		numInArray;
	// Vergleichsfunktion
	int		(*Compare)(const void* ele1,const void* ele2);
public:
	zCArraySort ( ) {
		numInArray	= 0;
		numAlloc	= 0;
		array		= 0;
		SetCompare (zArraySortDefaultCompare);
	};
	zCArraySort(const int startSize) {
		numInArray	= 0;
		numAlloc	= startSize;
		array		= 0;
		if (startSize>0)
		array		= zNEW(T) [startSize];
		SetCompare (zArraySortDefaultCompare);
	};
	zCArraySort (const zCArraySort<T>& array2) {
		// copy-constructor
		numInArray	= 0;
		numAlloc	= 0;
		array		= 0;
		AllocDelta	(array2.GetNumInList());
		numInArray	= array2.numInArray;
		for (int i=0; i<array2.GetNumInList(); i++)
			array[i]	= array2.array[i];
		SetCompare	(array2.Compare);
	};
	~zCArraySort() {
		delete[] array;
		array=0; // safety
	};
	T* GetArray() const { return array; };
	// Setze Sortierroutine
	void SetCompare ( int (*Cmp)(const void* ele1, const void* ele2) )	{ Compare = Cmp; };
	void AllocDelta (const int numDelta) {
		if (numDelta<=0) return;
		T *newArray = zNEW(T) [numAlloc+numDelta];
		if (numInArray>0)
		{
			for (int i=0; i<numInArray; i++)
				newArray[i] = array[i];		// safer, bei einem memcpy werden z.B. nur ptr auf zSTRINGs kopiert, der folgende delete[] killt diese Dann.. ARGH!
//			memcpy (newArray, array, sizeof(T)*numInArray);		// FIXME mempy
		};
		delete[] array;
		array		=  newArray;
		numAlloc	+= numDelta;
	};
	void AllocAbs (const int size) {
		if (numAlloc>=size) return;
		AllocDelta (size-numAlloc);
	};
	void ShrinkToFit () {
		if (numInArray<=0) { DeleteList(); return; };
		if (numAlloc>numInArray) {
			T *newArray = zNEW(T) [numInArray];
			for (int i=0; i<numInArray; i++)
				newArray[i] = array[i];		// safer, bei einem memcpy werden z.B. nur ptr auf zSTRINGs kopiert, der folgende delete[] killt diese Dann.. ARGH!
//			memcpy (newArray, array, sizeof(T)*numInArray);		// FIXME mempy
			delete[] array;
			array		= newArray;
			numAlloc	= numInArray;
		};
	};
	void operator = (const zCArraySort<T>& array2) {
		EmptyList	();
		AllocAbs	(array2.GetNumInList());
		numInArray	= array2.numInArray;
		for (int i=0; i<array2.GetNumInList(); i++)
			array[i]	= array2.array[i];
	};
	const T& operator [] (const int nr) const {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};
	T& operator [] (const int nr) {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};
/*	T  operator [] (const int nr) const {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};*/
	T& GetSafe (int nr) const {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		if (numInArray <=0)	zerr.Fatal ("D: zTree(zCArraySort::GetSafe): numInArray<=0");
		if (numAlloc   <=0)	zerr.Fatal ("D: zTree(zCArraySort::GetSafe): numAlloc  <=0");
		if (nr<0          ) nr = 0; else
		if (nr>=numInArray) nr = numInArray-1;
		return array[nr];
	};
	T& Get (const int nr) const {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};
	// inserts at the END
	void InsertEnd (const T& ins ) {
		if (numAlloc<numInArray+1) {
			if (numAlloc<zARRAY_START_ALLOC)	AllocDelta (zARRAY_START_ALLOC);
			else								AllocDelta (numAlloc / 2);
		};
		array[numInArray++] = ins;
	};

	void Insert (const T& ins )		{ InsertEnd (ins);	};
	// inserts at position 
	void InsertAtPos (const T& ins, int pos) {
		if (numAlloc<numInArray+1) {
			if (numAlloc<zARRAY_START_ALLOC)	AllocDelta (zARRAY_START_ALLOC);
			else								AllocDelta (numAlloc / 2);
		};
		// Alle nachfolgenden Elemente um eins nach hinten verschieben
		memmove(&array[pos+1],&array[pos],sizeof(T) * (numInArray - pos));
		array[pos] = ins;
		numInArray++;
	};
	// Insert sorted
	void InsertSort (const T& ins ) {
		if (numAlloc<numInArray+1) {
			if (numAlloc<zARRAY_START_ALLOC)	AllocDelta (zARRAY_START_ALLOC);
			else								AllocDelta (numAlloc / 2);
		};

		// Binary Search	
		int ind_low	= 0;
		int ind_high= numInArray-1;
		int index	= ( ind_low + ind_high ) / 2;
		int erg;

		do {
			if (ind_high <= ind_low) {

				if (index >= numInArray) {
					array[index] = ins;
					numInArray++;
					return;
				} else {
					erg = Compare ( &ins, &(array[index]) );
					if (erg > 0) index++; 
				};
				
				// Alle nachfolgenden Elemente um eins nach hinten verschieben
				memmove(&array[index+1],&array[index],sizeof(T) * (numInArray - index));
				array[index] = ins;
				numInArray++;
				return;
			}
	
			erg = Compare ( &ins, &(array[index]) );
		
			if (erg>0) 	ind_low	= index + 1; 
			else		ind_high= index - 1; 
			
			index = ( ind_low + ind_high ) / 2;
		} while ( 1 ); //ind_low <= ind_high );
	};

	int Search (const T& ins ) const {
		if (numInArray<=0) return -1;
		// Binary Search	
		// return value= found index, -1=not found
		int ind_low	= 0;
		int ind_high= numInArray-1;
		int index	= ( ind_low + ind_high ) / 2;
		int erg;

		do {
			erg = Compare ( &ins, &(array[index]) );
			if (ind_high <= ind_low) {
				if (erg==0) return index;
				return -1;
			}
	
			if (erg>0) 	ind_low	= index + 1; else
			if (erg<0)  ind_high= index - 1; else
			return index;

			index = ( ind_low + ind_high ) / 2;
		} while (1);
	};

	// does NOT preserve order
	void RemoveIndex (const int index) {
		if (numInArray<=0) return;
		numInArray--;
		if (index!=numInArray) array[index] = array[numInArray];
	}
	// does NOT preserve order
	void Remove (const T& rem) {
		if (numInArray==0) return;
		for (int i=0; i<numInArray; i++) {
			if (array[i]==rem) {
				numInArray--;
				if (i!=numInArray) array[i] = array[numInArray];
				return;
			};
		};
	}
	// DOES preserve order
	void RemoveOrder (const T& rem) {
		int i = Search (rem);
		if (i!=-1) RemoveOrderIndex (i);
/*		for (int i=0; i<numInArray; i++) {
			if (array[i]==rem) {
				RemoveOrderIndex (i);
				return;
			};
		};*/
	};
	// DOES preserve order
	void RemoveOrderIndex (const int index) {
		if (index>=numInArray) return;
		if (index!=numInArray-1) 
			for (int j=index; j<numInArray-1; j++) array[j] = array[j+1];
		numInArray--;
		return;
	};
	void DeleteList() {
		delete[] array;
		array		= 0;
		numAlloc	= 0;
		numInArray	= 0;
	};
	void EmptyList () { numInArray = 0; };
	// return = 
	int	IsInList (const T& data) const {
		// ACHTUNG: 0==FALSE ist eine gueltige Listen-Position => diese Func darf nur BOOLS rauswerfen
		int i = Search (data);
		if (i==-1)	return FALSE;
		else		return TRUE;
/*		if (numInArray<=0) return FALSE;
		for (int i=0; i<numInArray; i++) if (array[i]==data) return TRUE;
		return FALSE;*/
	};
	void MarkNumAllocUsed () {
		numInArray = numAlloc;
	};
	int	  GetNumInList	() const	{ return numInArray; };
	int	  GetNum		() const	{ return numInArray; };
	zBOOL IsEmpty		() const	{ return (numInArray<=0); };
	void  QuickSort		()			{ qsort (array, GetNumInList(), sizeof(T), Compare);	};
	void  InsertionSort ()			{ insertionsort (array, GetNumInList(), sizeof(T), Compare,false);	};
	void  BestSort      ()			{ insertionsort (array, GetNumInList(), sizeof(T), Compare,true);	};
};

// =======================================================================================================================

// This array does not own the memory it works on.
// A chunk of memory is given to work on, that is not allocated or freed.

template <class T> class zCArrayAdapt {
protected:
	T		*array;
	int		numInArray;
public:
	 zCArrayAdapt()									{ numInArray= 0; array = 0;	};
	~zCArrayAdapt()									{ array=0;					};
	T*		GetArray		() const				{ return array;				};
	zDWORD	GetSizeBytes	() const				{ return sizeof(T)*numInArray; };
	zDWORD	SetArray		(void* ptr, const int num){ array=(T*)ptr; numInArray=num; return sizeof(T)*numInArray; };
	void	SetNumInArray	(const int num)			{ numInArray=num;			};
	void	EmptyList		()						{ numInArray = 0;			};
	int		GetNum			() const				{ return numInArray;		};
	zBOOL	IsEmpty			() const				{ return (numInArray<=0);	};
	const T& operator [] (const int nr) const {
		assert (numInArray>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};
	T& operator [] (const int nr) {
		assert (numInArray>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};
/*	T  operator [] (const int nr) const {
		assert (numInArray>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};*/
	T& GetSafe (int nr) const {
		assert (numInArray>0);
		assert ((nr>=0) && (nr<numInArray));
		if (numInArray <=0)	zERR_FATAL ("D: (zCArrayAdapt::GetSafe): numInArray<=0");
		if (nr<0          ) nr = 0; else
		if (nr>=numInArray) nr = numInArray-1;
		return array[nr];
	};
	// inserts at the END
	void InsertEnd (const T& ins )			{	array[numInArray++] = ins;	};
	/// inserts FRONT
	void InsertFront	(const T& ins )		{	InsertAtPos (ins, 0);	};
	/// inserts 'somewhere', fastest (no order guaranteed)
	void Insert			(const T& ins )		{	InsertEnd (ins);		};
	// inserts at position 
	void InsertAtPos	(const T& ins, int pos) {
		// Alle nachfolgenden Elemente um eins nach hinten verschieben
		memmove(&array[pos+1],&array[pos],sizeof(T) * (numInArray - pos));
		array[pos] = ins;
		numInArray++;
	};
	// does NOT preserve order
	void Remove (const T& rem) {
		if (numInArray==0) return;
		for (int i=0; i<numInArray; i++) {
			if (array[i]==rem) {
				numInArray--;
				if (i!=numInArray) array[i] = array[numInArray];
				return;
			};
		};
	}
	// does NOT preserve order
	void RemoveIndex (const int index) {
		if (numInArray<=0) return;
		numInArray--;
		if (index!=numInArray) array[index] = array[numInArray];
	}
	// DOES preserve order
	void RemoveOrder (const T& rem) {
		for (int i=0; i<numInArray; i++) {
			if (array[i]==rem) {
				RemoveOrderIndex (i);
				return;
			};
		};
	};
	// DOES preserve order
	void RemoveOrderIndex (const int index) {
		if (index>=numInArray)		return;
		if (index!=numInArray-1)	for (int j=index; j<numInArray-1; j++) array[j] = array[j+1];
		numInArray--;
		return;
	};
	int  Search (const T& data)	const { 
		if (numInArray>0)	for (int i=0; i<numInArray; i++) if (array[i]==data) return i;
		return -1;
	};
	int IsInList (const T& data) const {
		if (numInArray>0)	for (int i=0; i<numInArray; i++) if (array[i]==data) return TRUE;
		return FALSE;
	};
};

// =======================================================================================================================

#endif
