
#ifndef _CPROPLIST_H_
#define _CPROPLIST_H_
// Helper class
#include "zAlgebra.h"
#include "zSTRING.h"
#include "zContainer.h"
#include "zTypes3d.h"
#include "zBuffer.h"
#include "zObject.h"


class spcCObjPropertyElement;

class spcCObjPropertyList : public zCArray<spcCObjPropertyElement*>
{
public:
	spcCObjPropertyList();
	virtual ~spcCObjPropertyList();

	spcCObjPropertyElement* SearchElementByTreeitem(HTREEITEM item);
};


////////////////////////////////////////////////////////////


class spcCObjPropertyElement : public zSTRING
{
public:
	enum TPropEditType {
		PETunknown, 
		PETbool, 
		PETenum, 
		PETint, 
		PETfloat, 
		PETstring,  
		PETvec3, 
		PETcolor, 
		PETraw, 
		PETclass, 
		PETgroup, 
		PETchunkend
	};
	spcCObjPropertyElement(const char* c);
	spcCObjPropertyElement ();

public:

	static CString PickValue(CString text);
	static CString PickName(CString text);
	
	TPropEditType	GetPropType	();
	CString			GetName		();
	CString			GetDescription();	
	int				GetIconID();
	HTREEITEM		GetTreeItem()					{ return treeItemHandle; };

	int				GetIntVal	();  // für bool integer float und enum
	float			GetFloatVal	();  // für float
	CString			GetStrVal	();	 // für string, raw
	zVEC3			GetVecVal	();  // für vec3
	CString			GetEnumVal	();  // für enum
	void			GetEnumList	(CComboBox& list);
	COLORREF		GetColor	();		

	void			ToggleBoolVal();
	void			ToggleEnumVal();

	void SetTreeItem(HTREEITEM item)	{ treeItemHandle=item; };

	void SetByInt	(int v);
	void SetByFloat	(float v);
	void SetByStr	(CString v);
	void SetByVec	(zVEC3 v);
	void SetByEnum	(CString v);
	void SetByColor	(COLORREF col);		

	void SetChecked (bool ch=true) { checked = ch; };
	bool IsChecked  () { return checked; };

private:	
	TPropEditType	ParseDataType(const zSTRING&);

	bool			checked;
	HTREEITEM		treeItemHandle;	
};

///////////////////////////////////////////////////////////////


#endif