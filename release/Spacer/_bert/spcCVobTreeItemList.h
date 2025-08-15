#if !defined(AFX_SPCCITEMLIST_VOBS_H__7E7B2267_384A_11D2_8AB9_0080AD209698__INCLUDED_)
#define AFX_SPCCITEMLIST_VOBS_H__7E7B2267_384A_11D2_8AB9_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCList_Vobs.h : header file
//


#include <afxext.h>
#include <afxtempl.h>

class zCVob;
class zCWorld;


// flobal function

class spcCVobTreeItem
{
public:
	spcCVobTreeItem(HTREEITEM _hItem, zCVob* _vob);
	virtual ~spcCVobTreeItem();
	virtual HTREEITEM GetVobFolder(zCVob* _vob);
	virtual HTREEITEM CheckFolders();
	HTREEITEM  hItem;
	zCVob*     vob;
};

class spcCVobTreeDrawer : public spcCVobTreeItem
{
public:
	spcCVobTreeDrawer(HTREEITEM _hItem, zCVob* _vob);
	HTREEITEM GetVobFolder(zCVob* folderVob);
	HTREEITEM CheckFolders();
	HTREEITEM itemFolder;
	HTREEITEM mobFolder;
	HTREEITEM npcFolder;
	HTREEITEM lightFolder;
	HTREEITEM decalFolder;
	HTREEITEM specialFolder;
	HTREEITEM soundFolder;
	HTREEITEM waypointFolder;
	HTREEITEM levelFolder;
	HTREEITEM eventFolder;
	HTREEITEM zoneFolder;
};

class spcCVobTreeItemList : public CList<spcCVobTreeItem*,spcCVobTreeItem*>
{
public:
	
	HTREEITEM			GetHandleByVob(zCVob* _vob);
	HTREEITEM			GetFolderByVob(zCVob* _vob, zCVob* folderVob);
	spcCVobTreeItem*	GetItemByVob(zCVob* _vob);
	spcCVobTreeItem*	GetItemByHandle(HTREEITEM hItem);

	void				DeleteHandleVobRef(zCVob* _vob);	
	void				RemoveAllTreeItems();
};

#endif