/******************************************************************************** 
 
     $Workfile:: zList.h              $                $Date:: 25.01.01 12:14   $
     $Revision:: 10                   $             $Modtime:: 25.01.01 10:22   $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zList.h $
 * 
 * 10    25.01.01 12:14 Moos
 * 
 * 9     4.12.00 18:23 Moos
 * 
 * 8     4.10.00 15:16 Speckels
 * 
 * 7     29.09.00 15:24 Speckels
 * 
 * 6     7.09.00 19:16 Wohlers
 * 
 * 5     25.08.00 11:36 Moos
 * 
 * 4     22.05.00 18:45 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 4     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 3     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ZLIST_H__
#define __ZLIST_H__

#ifndef NULL
#define NULL	0
#endif

#ifndef __ZCONTAINER_H__
#include "zContainer.h"
#endif

#ifndef __ZOBJECT_H__
#include "zObject.h"
#endif


template <class obj> class zList
{
	int (*Compare)(obj *ele1,obj *ele2);
	int count;
	obj *last;
public:
	obj *wurzel;
	// Init It.
	zList () 
	{ 
		last   = 0;
		wurzel = NULL; 
		count  = 0;
	}

	// Setze Sortierroutine
	void SetCompare( int (*Cmp)(obj *ele1,obj *ele2) )
	{
		Compare = Cmp;
	}

	// Delete the complete list
	void Clear() 
	{
		obj *ele,*help;
		ele = wurzel;
		while (ele!=NULL) {
			help = ele;
			ele  = ele->next;
			delete(help);
		}
		last   = NULL;
		wurzel = NULL;
		count  = 0;
	};
	
	// Insert an Item
	void Insert( obj *ins ) 
	{
		if (IsIn(ins)) {
			return;
		}
		if (wurzel==NULL) last = ins;

		ins -> next = wurzel;
		wurzel      = ins;
		count++;
	}

	// Insert Item at end of Lisz
	void InsertLast ( obj *ins )
	{
		if (IsIn(ins)) {
			return;
		}
		count++;
		ins -> next = NULL;
		if (wurzel==NULL) {
			last   = ins;
			wurzel = ins;
		} else {
			last->next = ins;
			ins ->next = NULL;
			last	   = ins;
		}
	}		

	// Insert behind Element object
	zBOOL InsertAsNext (obj* object, obj* ins)
	{
		if (IsIn(ins)) {
			return FALSE;
		}

		if ((!object) || (!ins)) return FALSE;
		ins		-> next = object -> next;
		object	-> next = ins;

		count++;
		return TRUE;
	}

	// Insert before Element object
	zBOOL InsertAsPrevious (obj* ins, obj* object)
	{
		if (IsIn(ins)) {
			return FALSE;
		}

		if ((!object) || (!ins)) return FALSE;
		if (wurzel == object) {
			ins -> next = wurzel;
			wurzel		= ins;
			count++;
			return TRUE;
		}
		// Liste durchsuchen
		obj* ele = wurzel;
		while (ele!=NULL) {
			if (ele -> next == object) {
				ins -> next = object;
				ele -> next = ins;
				count++;
				return TRUE;
			}
			ele = ele->next;
		}
		return FALSE;
	}

	// Insert an Item (sorting)
	void InsertSort (obj *ins)
	{
		obj *ele;
	
		if (IsIn(ins)) {
			return;
		}

		if ((wurzel==NULL) || (Compare(ins,wurzel)<0)) {
			// Erstes Element
			ins->next = wurzel;
			wurzel    = ins;
			count++;
		} else {
			ele = wurzel;
			while (ele->next != NULL) {
				if (Compare(ins,ele->next)<=0) {
					// Mittendrin, statt nur dabei
					ins->next = ele->next;
					ele->next = ins;
					count++;
					return;
				}
				ele = ele->next;
			}
			// Letztes Element
			ele -> next = ins;
			ins -> next = NULL;
			last        = ins;
			count++;
		}
	}

	// Remove Item
	void Remove( obj *rem )
	{
		obj *ele = wurzel;
		
		if (ele==NULL) return;
		if (ele==rem) {
			wurzel = ele->next;
			if (wurzel==NULL) last = NULL;
			count--;
			if (count<0)
				zERR_FAULT("U: LIST: Count is less than 0");
		} else {
			while (ele->next!=NULL) {
				if (ele->next==rem) {
					if (rem->next==NULL) last = ele;
					ele->next = rem->next;
					count--;
					if (count<0)
						zERR_FAULT("U: LIST: Count is less than 0");
					return;
				}
				// Safety FIXME !
				if (ele==ele->next) ele->next = NULL;
				else ele = ele->next;
			}
		}
	}
		
	// Delete Item	
	void Delete( obj *rem )
	{
		obj *ele = wurzel;
		
		if (ele==NULL) return;
		if (ele==rem) {
			wurzel = ele->next;
			if (wurzel == NULL) last = NULL;
			delete(ele);
			count--;
			if (count<0)
				zERR_FAULT("U: LIST: Count is less than 0");
		} else {
			while (ele->next!=NULL) {
				if (ele->next==rem) {
					if (rem->next==NULL) last = ele;
					ele->next = rem->next;
					delete(rem);
					count--;
					if (count<0)
						zERR_FAULT("U: LIST: Count is less than 0");
					return;
				}
				ele = ele->next;
			}
		}
	}

	// Get Item
	obj* Get( int nr )
	{
		obj *ele = wurzel;
		int c = 0;

		while (ele!=NULL) {
			c++;
			if (c==nr) return(ele);
			ele = ele->next;
		}
		return NULL;
	}

	obj *GetLast()
	{
		return last;
	}

	// Check, if Item is in list
	BOOL IsIn(obj *ele2)
	{
		obj *ele = wurzel;

		while (ele!=NULL) {
			if (ele==ele2) return TRUE;
			ele = ele->next;
		}
		return FALSE;
	}
	
	// Return Counter ( Number of elements in list )
	int Count()
	{
		return count;
	}
};

// ***************************************************************************
// Priority Queue
// Based on Dieters zCArray
// ***************************************************************************

template <class T> class zCPQueue {
public:
	T		*array;
	int		numAlloc;
	int		numInArray;
	// Vergleichsfunktion
	int		(*Compare)(T ele1,T ele2);
	BOOL	allow_double_entrys;
public:
	zCPQueue ( ) {
		numInArray	= 0;
		numAlloc	= 0;
		array		= 0;
		allow_double_entrys = TRUE;
	};
	zCPQueue(int startSize) {
		numInArray	= 0;
		numAlloc	= startSize;
		array		= zNEW_ARRAY(T,startSize);
		allow_double_entrys = TRUE;
	};
	zCPQueue (const zCPQueue<T>& array2) {
		// copy-constructor
		numInArray	= 0;
		numAlloc	= 0;
		array		= 0;
		AllocDelta	(array2.GetNumInList());
		numInArray	= array2.numInArray;
		if (numInArray>0)
		memcpy		(array, array2.array, sizeof(T)*numInArray);
		allow_double_entrys = TRUE;
	};
	~zCPQueue() {
		delete[] array;
		array=0; // safety
	};

	void SetAllowDouble	( BOOL allow )
	{
		allow_double_entrys = allow;
	};
	// Setze Sortierroutine
	void SetCompare( int (*Cmp)(T ele1,T ele2) )
	{
		Compare = Cmp;
	};
	void AllocDelta (const int numDelta) {
		T *newArray = zNEW_ARRAY(T,numAlloc+numDelta);
		if (numInArray>0)
			memcpy (newArray, array, sizeof(T)*numInArray);
		delete[] array;
		array		=  newArray;
		numAlloc	+= numDelta;
	};
	void AllocAbs (const int size) {
		if (numAlloc>size) return;
		AllocDelta (size-numAlloc);
	};
	void ShrinkToFit () {
		if (numInArray==0) { DeleteList(); return; };
		if (numAlloc>numInArray) {
			T *newArray = zNEW_ARRAY(T,numInArray);
			memcpy (newArray, array, sizeof(T)*numInArray);
			delete[] array;
			array		= newArray;
			numAlloc	= numInArray;
		};
	};
	void operator = (const zCPQueue<T>& array2) {
		DeleteList	();
		AllocDelta	(array2.GetNumInList());
		numInArray	= array2.numInArray;
		if (numInArray>0)
		memcpy		(array, array2.array, sizeof(T)*numInArray);
	};
	T& operator [] (int nr) {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};
	T  operator [] (int nr) const {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		return array[nr];
	};
	T& GetSafe (int nr) const {
		assert (numInArray>0);
		assert (numAlloc>0);
		assert ((nr>=0) && (nr<numInArray));
		if (numInArray <=0)	zerr.Report (zERR_FATAL, 1000, "D: zTree(zCPQueue::GetSafe): numInArray<=0");
		if (numAlloc   <=0)	zerr.Report (zERR_FATAL, 1000, "D: zTree(zCPQueue::GetSafe): numAlloc  <=0");
		if (nr<0          ) nr = 0; else
		if (nr>=numInArray) nr = numInArray-1;
		return array[nr];
	};
	// inserts at the END
/*	void Insert (const T& ins ) {
		if (numAlloc<numInArray+1) {
			if (numAlloc==0) AllocDelta (16);
			else			 AllocDelta (numAlloc / 2);
		};
		array[numInArray++] = ins;
	};
*/	// inserts at the END
	void InsertEnd (const T& ins ) {
		if (numAlloc<numInArray+1) {
			if (numAlloc==0) AllocDelta (16);
			else			 AllocDelta (numAlloc / 2);
		};
		array[numInArray++] = ins;
	};

	// Insert sorted
	BOOL Insert (const T& ins ) {
		if (numAlloc<numInArray+1) {
			if (numAlloc==0) AllocDelta (16);
			else			 AllocDelta (numAlloc / 2);
		};

		// Binary Search	
		int ind_low	= 0;
		int ind_high= numInArray;
	
		int index	= ind_low + ( ind_low + ind_high ) / 2;
		int erg;

		do {
			if (ind_high <= ind_low) {

				if (index >= numInArray) {
					array[index] = ins;
					numInArray++;
					return TRUE;
				} else {
					erg = Compare ( ins, array[index] );
					if (erg > 0) index++;
					if ((erg==0) && (!allow_double_entrys)) return FALSE;
				};
				
				// Alle nachfolgenden Elemente um eins nach hinten verschieben
				memmove(&array[index+1],&array[index],sizeof(T) * (numInArray - index));
				array[index] = ins;
				numInArray++;
				return TRUE;
			}
			
			erg = Compare ( ins, array[index] );
		
			if (erg>0) 	
				ind_low	= index + 1;
			else		
				ind_high= index - 1;
			
			index = ind_low + ( ind_high - ind_low ) / 2;
	
		} while ( 1 ); //ind_low <= ind_high );
		
		return FALSE;
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
	// DOES preserves order
	void RemoveOrder (const T& rem) {
		for (int i=0; i<numInArray; i++) {
			if (array[i]==rem) {
				if (i!=numInArray-1) 
					for (int j=i; j<numInArray; j++) array[j] = array[j+1];
				numInArray--;
				return;
			};
		};
	};
	void DeleteList() {
		delete[] array;
		array		= 0;
		numAlloc	= 0;
		numInArray	= 0;
	};
	void EmptyList () { numInArray = 0; };
	BOOL IsInList (const T& data) const {
		if (numInArray==0) return FALSE;
//		for (int i=0; i<numInArray; i++) if (array[i]==data) return TRUE;
		return FALSE;
	};
	int GetNumInList() const { return numInArray; };
	BOOL IsEmpty() const { return (numInArray==0); };
};

// ***************************************************************************
// zCListSort
// Based on Dieters zCList
// ***************************************************************************

zMEMPOOL_DECLARATION_TEMPLATE_EXTRA(zCListSort, s_ListSortPool);

template <class T> class zCListSort {
public:
    zMEMPOOL_DECLARATION_TEMPLATE(zCListSort, s_ListSortPool);

	int (*Compare)(T *ele1,T *ele2);
	T			*data;
	zCListSort	*next;
public:

	// Init It.
	zCListSort ()  { 
		next	= 0; 
		data	= 0;
	}

	~zCListSort () { 
		// recursion !
		if (next) {
			delete next;
			next = 0;
		};
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
			data->Release();
			data = 0;
		};
		// der Rest loescht sich rekursiv !
		if (next) {
			next->DeleteListDatas();
			delete next;
			next = 0;
		};
	};

	void Replace		( T *ins ) { data  = ins; };

	// Insert an Item 
	void Insert			( T *ins ) {
		zCListSort *newItem = zNEW(zCListSort);
		newItem->data		= ins;
		newItem->next		= next;
		next				= newItem;
	}
	// InsertSorting
	void InsertSort		( T *ins ) {
 		zCListSort* newItem = zNEW(zCListSort);
		newItem->data		= ins;
		newItem->next		= next;
		// Now Sort it
		zCListSort* ele		= this;
		while (ele->next) {
			if (Compare(ins,ele->next->data)<0) {
				// Place it before the ele->next Element
				newItem -> next = ele->next;
				ele	-> next		= newItem;
				return;
			}
			ele = ele->next;
		}
		// Last Element
		newItem -> next = NULL;
		ele -> next		= newItem;
	};
	// Remove Item
	void Remove			( T *rem ) {
		zCListSort *item = this;
		
		while (item->next!=0) {
			if (item->next->data==rem) {
				zCListSort *tmp	= item->next;
				item->next	= item->next->next;
				tmp ->next	= 0;
				delete tmp;
				return;
			}
			item = item->next;
		}
	};
		
	// Get Item
	// Indizierung von 0..n-1
	T* Get (int nr) const {
		zCListSort *item = next;
		int c = 0;
		while (item!=0) {
			if (c==nr) return(item->data);
			item = item->next;
			c++;
		}
		return 0;
	};

	T* operator [] (int nr) const {
		return Get (nr);
	};

	zCListSort*	GetNextInList	() const { return next; };
	T*			GetData			() const { return data; };

	// Check, if Item is in list
	zBOOL InList (T *data) const {
		zCListSort *item = next;
		while (item!=0) {
			if (item->data==data) return TRUE;
			item = item->next;
		}
		return FALSE;
	}
	zBOOL IsInList (T *data) const {
		zCListSort *item = next;
		while (item!=0) {
			if (item->data==data) return TRUE;
			item = item->next;
		}
		return FALSE;
	}
	
	// Return Counter ( Number of elements in list )
	int GetNumInList() const { 
		int count = 0;
		zCListSort *item = next;
		while (item!=0) {
			count++;
			item = item->next;
		}
		return count;
	};

	// Setze Sortierroutine
	void SetCompare( int (*Cmp)(T *ele1,T *ele2) )
	{
		Compare = Cmp;
	};
};

#endif
