// Implementation


#include "stdafx.h"

#include "zengine.h"

#include "spcCVobTreeItemList.h"
#include "spcCDragVob.h"
#include "spcCInfoBar_Camera.h"
// z-files
#include "z3d.h"
#include "zZone.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

spcCVobTreeItem::spcCVobTreeItem(HTREEITEM _hItem, zCVob* _vob) 
{ 
	hItem = _hItem;
	vob = _vob; 
	if (vob) vob->AddRef();
}

spcCVobTreeItem::~spcCVobTreeItem()
{
	zRELEASE(vob);
};

HTREEITEM spcCVobTreeItem::GetVobFolder(zCVob* _vob)
{ 
	return NULL; 
}


void spcCVobTreeItemList::DeleteHandleVobRef(zCVob* _vob)
{	
	spcCVobTreeItem* vobitem;
	POSITION pos = GetHeadPosition();
	if (pos==NULL) return; // list is empty
	
	while (pos!=NULL) 
	{
		vobitem = GetAt(pos);
		if (vobitem && (vobitem->vob==_vob)) 
		{
			RemoveAt(pos);
			delete vobitem;vobitem=0;
			return;
		}
		GetNext(pos);
	}
}


void spcCVobTreeItemList::RemoveAllTreeItems()
{	
	spcCVobTreeItem* vobitem;
	POSITION pos = GetHeadPosition();
	if (pos==NULL) return; // list is empty
	
	while (pos!=NULL) 
	{
		vobitem = GetAt(pos);
		if (vobitem) 
		{
			SetAt(pos,0);
			delete vobitem;vobitem=0;			
		}
		GetNext(pos);
	}
	RemoveAll();
}

spcCVobTreeDrawer::spcCVobTreeDrawer(HTREEITEM _hItem, zCVob* _vob) 
	: spcCVobTreeItem(_hItem,_vob) 
{ 
}


HTREEITEM spcCVobTreeItem::CheckFolders()
{ 
	return NULL; 
}

HTREEITEM spcCVobTreeDrawer::CheckFolders()
{	
	return NULL;
}

HTREEITEM spcCVobTreeDrawer::GetVobFolder(zCVob* folderVob)
{	
	return NULL;
}

spcCVobTreeItem* spcCVobTreeItemList::GetItemByVob(zCVob* _vob)
{
	spcCVobTreeItem* vobitem;
	POSITION pos = GetHeadPosition();
	if (pos==NULL) return NULL;

	do {
		vobitem = GetNext(pos);
		if (vobitem && (vobitem->vob==_vob)) return vobitem;
	} while (pos!=NULL);

	return NULL;
}

spcCVobTreeItem* spcCVobTreeItemList::GetItemByHandle(HTREEITEM hItem)
{
	spcCVobTreeItem* vobitem;
	POSITION pos = GetHeadPosition();
	if (pos==NULL) return NULL;
	
	do {
		vobitem = GetNext(pos);
		if (vobitem && (vobitem->hItem==hItem)) return vobitem;
	} while (pos!=NULL);

	return NULL;
}

HTREEITEM spcCVobTreeItemList::GetHandleByVob(zCVob* _vob)
{
	spcCVobTreeItem* vobitem;
	POSITION pos = GetHeadPosition();
	if (pos==NULL) return NULL;
	do {
		vobitem = GetNext(pos);
		if (vobitem && (vobitem->vob==_vob)) return vobitem->hItem;
	} while (pos!=NULL);
	return NULL;
}

HTREEITEM spcCVobTreeItemList::GetFolderByVob(zCVob* _vob, zCVob* folderVob)
{
	if (_vob->GetVobType()!=zVOB_TYPE_LEVEL_COMPONENT ||
		folderVob->GetVobType()==zVOB_TYPE_LEVEL_COMPONENT) return NULL;
	spcCVobTreeItem* vobitem;
	POSITION pos = GetHeadPosition();
	if (pos==NULL) return NULL;
	do {
		vobitem = GetNext(pos);
		if (vobitem && (vobitem->vob==_vob)) 
			return vobitem->GetVobFolder(folderVob);				
	} while (pos!=NULL);
	return NULL;
}
