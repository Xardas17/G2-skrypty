// spcCConfiguration.h: interface for the spcCConfiguration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPCCCONFIGURATION_H__F7F40944_2D1E_11D2_88A8_0080AD209698__INCLUDED_)
#define AFX_SPCCCONFIGURATION_H__F7F40944_2D1E_11D2_88A8_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#ifndef __ZCONTAINER_H__
#include "zcontainer.h"
#endif

const CString NO_FILTER_FOLDER = "[TRASH]";

enum TStartUp { START_LOAD, START_PARSE};

class spcCOutputUnitFilter
{	
public:

	spcCOutputUnitFilter(CString _name, bool deletable) : name(_name), entries_deletable(deletable) {};

	CString		GetName() { return name; };
	bool		AreEntriesDeletable() { return entries_deletable; };
private:
	CString		name;
	bool		entries_deletable;
};

class spcCMatFilter
{
	bool isDirty;
public:
	
	enum TMatLibFlag {NullLib=0};

	CString name;
	int id;		

	spcCMatFilter();	
	spcCMatFilter(CString _name, int _id=-1) { Init(_name,_id); }

	~spcCMatFilter();

	void Init(CString _name, int _id=-1);
	void Deinit();

	void SetDirty(bool dirty = true) 
	{ 
		if (name.Find('[')<0) isDirty = dirty; 
	};

	bool IsDirty() 
	{ 
		return isDirty;
	};

	friend bool operator==(spcCMatFilter item1, spcCMatFilter item2);

	static zCArray<int>	freeMatFilterIDs;
	static zBYTE		nextMatFilterID;

};

struct spcTRegWindowPosition
{	
	bool	visible;
	POINT	pos;
	SIZE	size;
};

struct spcTRegWindowInfo
{	
	CString key;
	spcTRegWindowPosition position;
};

class spcCConfiguration  
{
public:		
	
	int Version;	
	int movespeed;
	int view_y;
	int view_x;
	int view_bpp;
	int useGrid,useGridTex;
	int moveGrid,moveGridTex;
	float rotGrid,rotGridTex;
	int camlight;	
	int fixedWindows;
	int interativeSave;	
	int compileLightRegion;
	int compileLightQuality;
	float farclipping;
	bool goldmastering;
			
	CString svmName;

	bool modeFogging;

	zCArray<spcCMatFilter*> matFilterList;

	float moveSpeedTex;	

public:
	int FindMatFilterIndexByName(CString name);
	int FindMatFilterIndexById(int id);	
	
	zCList<spcCOutputUnitFilter> OUFilterList;

	// temporary configurations
	HCURSOR MouseArrow;
	HCURSOR MouseCross;
	HCURSOR MouseWait;
	HCURSOR MouseUpArrow;
	
	// construct and destruct
	spcCConfiguration();
	virtual ~spcCConfiguration();

	// load and save
	void Load();
	void Load(CString fname);
	void Save();
	void Save(CString fname);
	
	POSITION GetWindowID(CString key, RECT* defRect = 0);
	bool KnowsWindowPosition(CString key);
	void GetWindowPosition(POSITION id, spcTRegWindowInfo& info);
	void SetWindowPosition(POSITION id, RECT rect);

protected:

	CList<spcTRegWindowInfo,spcTRegWindowInfo> windowList;

	void	RegCreatePath();
	void	RegWriteBinary(char *Key, void *Data, int Size);
	void	RegWriteInt(char *Key, int data);
	void	RegWriteFloat(char *Key, float data);
	void	RegWriteWindowPos(char* Key, spcTRegWindowPosition& data);

	zBOOL	RegGetBinary(char *Key, void *Data, int *Size);
	zBOOL	RegGetInt(char *Key, int& value);
	zBOOL	RegGetFloat(char *Key, float& value);
	zBOOL	RegGetWindowPos(char* Key, spcTRegWindowPosition& data);

	HKEY	spacerKey;
};

extern spcCConfiguration spcConfig;

#endif // !defined(AFX_SPCCCONFIGURATION_H__F7F40944_2D1E_11D2_88A8_0080AD209698__INCLUDED_)
