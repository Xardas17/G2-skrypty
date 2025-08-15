/******************************************************************************** 
 
     $Workfile:: zqueue.h            $                 $Date:: 4.12.00 18:22    $
     $Revision:: 9                   $              $Modtime:: 4.12.00 18:03    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
    
 * $Log: /current_work/ZenGin/_Bert/zqueue.h $
 * 
 * 9     4.12.00 18:22 Moos
 * 
 * 8     28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 6     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 5     10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 4     21.07.00 15:17 Speckels
 * 
 * 3     5.05.00 13:46 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:24 Speckels
 * 
 * 4     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 3     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 2     24.09.99 20:40 Speckels
 * VSS-kompatiblen Header eingef�gt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 9 $ ($Modtime: 4.12.00 18:03 $)


#ifndef __ZQUEUE_H__
#define __ZQUEUE_H__

#ifndef __ZCORE_H__
#include "zcore.h"
#endif

#ifndef _INC_IOSTREAM
#include "iostream"
#endif

#ifndef __ZTYPES_H__
#include "ztypes.h"
#endif


////////////////////////////////////////
// storage-classes
////////////////////////////////////////



////////////////////////////////////////
// zQUEUE_ITEM
template<class T>
class zQUEUE_ITEM
{
public:
	zBOOL empty;
	T* data;
	zQUEUE_ITEM* next;
	zQUEUE_ITEM* prev;
public:
	zQUEUE_ITEM(zQUEUE_ITEM* parent)
	{		
		data = 0;
		empty = TRUE;
		if (parent) 
		{			
			if (parent->next) parent->next->prev=this;
			next = parent->next;
			prev = parent;
			parent->next = this;			
		}
		else prev=next=NULL;
	}

	zBOOL IsEmpty() { return empty; }

	void SetEmpty() 
	{ 
		empty = TRUE; 
		data = 0;
	}

	void SetValue(T* xData)
	{
		data = xData;
		empty = FALSE;
	}
	
	void SetPrev(zQUEUE_ITEM<T>* _prev)
	{
		prev = _prev;		
	}

	void SetNext(zQUEUE_ITEM<T>* _next)
	{
		next = _next;
	}

	~zQUEUE_ITEM() {}
};

	
////////////////////////////////////////
// zQUEUE - synchronizable
template<class T> 
class zQUEUE
{	
	// HANDLE eventHandle;	

	int count;
	zQUEUE_ITEM<T>* firstItem;
	zQUEUE_ITEM<T>* lastItem;		
public:
	zQUEUE() { 
		count = 0;
		firstItem = zNEW(zQUEUE_ITEM<T>(NULL));	
		firstItem->SetPrev(firstItem);
		firstItem->SetNext(firstItem);
		lastItem  = firstItem;
		//eventHandle = CreateEvent(0,TRUE,FALSE,0);
	}

	~zQUEUE() 
	{ 	
		zQUEUE_ITEM<T>* tmp;
		lastItem = firstItem->prev;
		while (firstItem != lastItem) 
		{			
			tmp = firstItem->next;
			delete firstItem;
			firstItem=tmp;
		}
		delete firstItem;
		firstItem = lastItem = 0;
	}
	
	T* PopLast()
	{		
		if (lastItem->IsEmpty()) return 0;
		T* data = lastItem->data;		
		lastItem->SetEmpty();
		count--;
		if (lastItem!=firstItem) lastItem = lastItem->prev;		
		//if (count<=0) ResetEvent(eventHandle);
		return data;
	}

	T* PopFirst()
	{		
		if (firstItem->IsEmpty()) return 0;
		T* data = firstItem->data;
		firstItem->SetEmpty();
		count--;
		if (firstItem!=lastItem) firstItem = firstItem->next;		
		//if (count<=0) ResetEvent(eventHandle);
		return data;
	}

	void Push(T* xData)   
	{		
		if (lastItem->next == firstItem)
		{			
			zQUEUE_ITEM<T>* new_item = lastItem;
			for (int i = 0;i<=10;i++) new_item = zNEW(zQUEUE_ITEM<T>(new_item));
		}		
		if (!lastItem->IsEmpty()) lastItem = lastItem->next;
		lastItem->SetValue(xData);		
		count ++;
		//if (count>0) SetEvent(eventHandle);
	}	

	/*
	bool WaitForData(int milliseconds = INFINITE) 
	{ 
		return (WaitForSingleObject(eventHandle, milliseconds)==WAIT_OBJECT_0);			
	}
	*/

	void  RemoveAll()   { while (!IsEmpty()) PopFirst();count=0;	}	
	int   GetCount()	{ return count;								}
	zBOOL IsEmpty()		{ return (firstItem->IsEmpty());			}

};


#endif
