/****************************************************************
*																
* C++ zCList3 Implementation, based upon Dieters zCList
* File          : list2.h ()									
* Projekt       : Engine										
* Autor         : Carsten Edenfeld
* Version       : 0.00
* last modified : 06.09.98										
* erstellt      : 06.09.98
* Compiler OK   : 
*																
*****************************************************************
- known bugs:
*****************************************************************
- possible optimizations: 
*****************************************************************
- missing features:
*****************************************************************
- comments:
****************************************************************/

#ifndef __ZLIST2_H__
#define __ZLIST2_H__

#ifndef __ZCORE_H__
#include "zcore.h"
#endif

template <class T> class zCList3 {
	T			*data;
	zCList3		*next;
	int (*Compare)(const T *ele1,const T *ele2);
public:

	// Init It.
	zCList3 ()  { 
		next	= 0; 
		data	= 0;
	}

	~zCList3 () { 
		// recursion !
		if (next) {
			delete next;
			next = 0;
		};
	};

	// Setze Sortierroutine
	void SetCompare( int (*Cmp)(const T *ele1,const T *ele2) )
	{
		Compare = Cmp;
	}

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
			next = 0;
		};
	};

	inline void Replace ( const T *ins ) { data  = ins; };

	// Insert an Item 
	inline void Insert ( const T *ins ) {
		zCList3 *newItem  = zNEW( zCList3 );
		newItem->data	 = ins;
		newItem->next	 = next;
		next			 = newItem;
		count++;
	};
	// Insert an Item (sorting)
	inline void InsertSort (T *ins)
	{
		if ((data==NULL) || (Compare(ins,data)<0)) {
			// Erstes Element
			data = ins;
		} else {
			zCList3 *ele = this;
			while (ele->next != NULL) {
				if (Compare(ins,ele->next->data)<=0) {
					// Mittendrin, statt nur dabei
					zCList3 *newItem = zNEW (zCList3);
					newItem->data = ins;
					newItem->next = ele->next;
					newItem->next = ele->next;
					ele->next = newItem;
					return;
				}
				ele = ele->next;
			}
			// Letztes Element
			zCList3 *newItem = zNEW( zCList3 );
			ele		-> next = newItem;
			newItem -> next = NULL;
			newItem -> data = ins;
		}
	}

	inline void InsertFront ( const T *ins ) {
		zCList3 *newItem  = zNEW( zCList3 );
		newItem->data	 = ins;
		newItem->next	 = next;
		next			 = newItem;
	};

	// Remove Item
	inline void Remove( const T *rem ) {
		zCList3 *item = this;
		
		while (item->next!=0) {
			if (item->next->data==rem) {
				zCList3 *tmp	= item->next;
				item->next	= item->next->next;
				tmp ->next	= 0;
				delete tmp;
				return;
			}
			item = item->next;
		}
	}
		
	// Delete Item	
	inline void Delete( const T *rem ) {
		T *item = wurzel;
		
		if (item==0) return;
		if (item==rem) {
			wurzel = item->next;
			delete(item);
		} else {
			while (item->next!=0) {
				if (item->next==rem) {
					item->next = rem->next;
					delete(rem);
					return;
				}
				item = item->next;
			}
		}
	}

	// Get Item
	// Indizierung von 0..n-1
	T* Get (const int nr) const {
		zCList3 *item = next;
		int c = 0;
		while (item!=0) {
			if (c==nr) return(item->data);
			item = item->next;
			c++;
		}
		return 0;
	};

	inline T* operator [] (const int nr) const {
		return Get (nr);
	};

	inline zCList3*	GetNextInList	() const { return next; };
	inline T*		GetData			() const { return data; };

	// Check, if Item is in list
	inline zBOOL InList (const T *data) const {
		zCList3 *item = next;
		while (item!=0) {
			if (item->data==data) return TRUE;
			item = item->next;
		}
		return FALSE;
	}
	inline zBOOL IsInList (const T *data) const {
		zCList3 *item = next;
		while (item!=0) {
			if (item->data==data) return TRUE;
			item = item->next;
		}
		return FALSE;
	}
	
	// Return Counter ( Number of elements in list )
	inline int GetNumInList() const {	
		return T::numCached;
	};
};

#endif // __ZLIST2_H__