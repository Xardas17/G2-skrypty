#include "stdafx.h"

#include "zengine.h"

#include "spacer.h"
#include "zVob.h"

#include "spcCObjPropList.h"


const CString NAME_VALUE_SEPARATOR = ':';

int spcCObjPropertyElement::GetIconID()
{
	return (int)GetPropType();	
};

spcCObjPropertyElement::spcCObjPropertyElement(const char* c)
	: zSTRING(c)
{
	treeItemHandle = 0;
	checked = false;
}

spcCObjPropertyElement::spcCObjPropertyElement()
	: zSTRING()
{
	treeItemHandle = 0;
	checked = false;
}

spcCObjPropertyElement::TPropEditType spcCObjPropertyElement::ParseDataType(const zSTRING & dtw)
{
	if (dtw.Search("enum")>=0) return PETenum;
	else if (dtw.Search("bool")>=0) return PETbool;
	else if (dtw.Search("string")>=0) return PETstring;
	else if (dtw.Search("int")>=0) return PETint;
	else if (dtw.Search("float")>=0) return PETfloat;
	else if (dtw.Search("raw")>=0) return PETraw;
	else if (dtw.Search("vec3")>=0) return PETvec3;
	else if (dtw.Search("color")>=0) return PETcolor;
	return PETint;
}

spcCObjPropertyElement::TPropEditType spcCObjPropertyElement::GetPropType()
{
	if (Search("[")!=-1) 
	{
		if (Search("[]")!=-1) return PETchunkend;
		else return PETclass;
	}
	else
	{
		zSTRING secWord = PickWord(2,"=","=");
		if (secWord.Search("groupBegin")!=-1 || 
			secWord.Search("groupEnd")!=-1) 
		{
			if (Search("End")!=-1) return PETchunkend;
			else return PETgroup;
		}
		else
		{
			zSTRING thirdWord = PickWord(2,":",":");
			return ParseDataType(secWord);
		}
	}
	return PETint;
}
CString spcCObjPropertyElement::GetName()
{
	if (GetPropType()==PETclass)
	{
		zSTRING lStr = PickWord(1," %[]"," %[]");
		// lStr.Upper();
		return CString(lStr.ToChar());
	}
	else
		return CString(PickWord(1,"=","=").ToChar());
}

CString spcCObjPropertyElement::GetDescription()
{
	CString description = GetName()+NAME_VALUE_SEPARATOR;
	TPropEditType type = GetPropType();
	if (type!=spcCObjPropertyElement::PETclass &&
		type!=spcCObjPropertyElement::PETgroup )
	{
		if (type==spcCObjPropertyElement::PETenum)
		{
			description += GetEnumVal();
		}
		else 
		if (type==spcCObjPropertyElement::PETbool && GetIntVal()==0)
		{
			description += CString("FALSE");
		}
		else 
		if (type==spcCObjPropertyElement::PETbool && GetIntVal()==1)
		{
			description += CString("TRUE");
		}
		else
		{
			description += GetStrVal();
		}
	}

	return description;
}

int spcCObjPropertyElement::GetIntVal ()  // für bool integer float und enum
{
	return PickWord(2,":",":").ToInt();
}
float spcCObjPropertyElement::GetFloatVal ()  // für float
{
	return PickWord(2,":",":").ToFloat();
}
CString spcCObjPropertyElement::GetStrVal ()	 // für string, raw
{
	int index = this->Search(":");
	if (index>=0) 
		return CString( Copied(index+1).ToChar() );	// Kopiere vom index bis zum Ende
	else
		return "";
}
zVEC3 spcCObjPropertyElement::GetVecVal ()  // für vec3
{
	zSTRING v = PickWord(2,":",":");
	return zVEC3(	v.PickWord(1," "," ").ToFloat(),
					v.PickWord(2," "," ").ToFloat(),
					v.PickWord(3," "," ").ToFloat());
}
CString	spcCObjPropertyElement::GetEnumVal()
{
	zSTRING v = PickWord(2,"=:","=:");
	return CString(v.PickWord(GetIntVal()+2,";",";").ToChar());
}
void spcCObjPropertyElement::GetEnumList(CComboBox& list)
{
	list.ResetContent();
	zSTRING v = PickWord(2,"=:","=:");
	int z=2;
	zSTRING w = v.PickWord(z,";",";");
	while (!w.IsEmpty())
	{ 
		list.AddString(w.ToChar());
		z++;
		w = v.PickWord(z,";",";");
	}
}
COLORREF spcCObjPropertyElement::GetColor()
{
	return RGB(100,200,0);
}

void spcCObjPropertyElement::SetByInt(int v)
{	
	assign(zSTRING(PickWord(1,":",":")+zSTRING(":")+zSTRING(v)).ToChar());
}
void spcCObjPropertyElement::SetByFloat(float v)
{
	assign(PickWord(1,":",":").ToChar());
}
void spcCObjPropertyElement::SetByStr(CString v)
{
	assign(zSTRING(PickWord(1,":",":")+zSTRING(":")+zSTRING(v.GetBuffer(0))).ToChar());
}
void spcCObjPropertyElement::SetByVec(zVEC3 v)
{
	assign(zSTRING(PickWord(1,":",":")+zSTRING(":")+
		zSTRING(v[0])+zSTRING(" ")+zSTRING(v[1])+zSTRING(" ")+zSTRING(v[2])).ToChar());
}


void spcCObjPropertyElement::SetByColor(COLORREF col)
{
	assign
	(
		zSTRING(
			PickWord(1,":",":")
			+ ":"
			+ zSTRING(GetRValue(col))+" "
			+ zSTRING(GetGValue(col))+" "
			+ zSTRING(GetBValue(col))+" 255"
		).ToChar()
	);
}

CString spcCObjPropertyElement::PickValue(CString text)
{
	int index = text.Find(NAME_VALUE_SEPARATOR,0);
	text.Delete(0,index+1);
	text.TrimLeft(' ');text.TrimRight(' ');
	return text;
};

CString spcCObjPropertyElement::PickName(CString text)
{
	int index = text.Find(NAME_VALUE_SEPARATOR,0);
	text.Delete(index,text.GetLength()-index);
	text.TrimLeft(' ');text.TrimRight(' ');
	return text;
};

void spcCObjPropertyElement::ToggleBoolVal()
{
	SetByInt(1-GetIntVal());
};

void spcCObjPropertyElement::SetByEnum(CString v)
{		
	zSTRING text = PickWord(2,"=:","=:");
	int wortNr=2;
	int count=0;
	zSTRING w = text.PickWord(wortNr++,";",";");		
	while (!w.IsEmpty())
	{ 
		if (v == CString(w.ToChar())) 
		{
			SetByInt(count);
			return;
		};
		w = text.PickWord(wortNr++,";",";");
		count++;
	}
};

void spcCObjPropertyElement::ToggleEnumVal()
{
	CString current =  GetEnumVal();
	zSTRING v = PickWord(2,"=:","=:");
	int wortNr=2;
	zSTRING first = v.PickWord(wortNr++,";",";");
	zSTRING next = first;
	bool pickNext=false;
	while (!next.IsEmpty())
	{ 
		if (current == CString(next.ToChar())) pickNext = true;
		next = v.PickWord(wortNr++,";",";");
		if (pickNext && !next.IsEmpty()) 
		{
			SetByEnum(next.ToChar());
			return;
		}
	}
	SetByEnum(first.ToChar());
};


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

spcCObjPropertyList::spcCObjPropertyList()
{
};

spcCObjPropertyList::~spcCObjPropertyList()
{
};

spcCObjPropertyElement* spcCObjPropertyList::SearchElementByTreeitem(HTREEITEM item)
{
	int i=0;
	while (i<GetNumInList())
	{
		if (GetSafe(i)->GetTreeItem() == item) return GetSafe(i);
		i++;
	};

	return 0;
};
