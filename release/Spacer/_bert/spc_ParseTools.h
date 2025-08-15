#include "afxtempl.h"
#include "zparser.h"
#include "zstring.h"
#include "zcontainer.h"

#ifndef _PARSETOOLS_H_
#define _PARSETOOLS_H_

const char INSTANCE_MARKER[] = "I: ";
const char PROTOTYPE_MARKER[] = "P: ";

struct T_CLASSINFO
{
	char name[12];
};

const int CLASSNUM = 7;
enum T_CLASS { CLASS_INFO, CLASS_MISSION, CLASS_SOUNDS, CLASS_NPC, CLASS_ITEM, CLASS_GUILD, CLASS_MOB };
const T_CLASSINFO CLASSINFO[CLASSNUM] = 
	{
		{"C_Info"},
		{"C_Mission"},
		{"C_SFX"},
		{"C_NPC"},
		{"C_Item"},
		{"C_Guilds"},
		{"C_MOB"}
	};
        
// Parse-Info-List-Class

class CParseItem
{
public:
	char		type;		// 'P'rototype, 'I'nstance, 'F'unction, 'C'onstant, 'V'ariable ...
	CString		name;		// unique name of Prototype, Instance, Function ...	
};


class CParseList
{	
	CTypedPtrList<CPtrList, CParseItem*> list;
	POSITION pos;

public:

	CParseList();

	void			DeleteAll();	
	void			Add(char type, CString name);
	CParseItem*		GetFirst();
	CParseItem*		GetNext();
};


// Parse-Info-Class

class spcCWorkingDlg;

class spcCParseInfo
{		
	CPropertyPage* pWnd;
	CString* message;
public:
	// general informations
	CString filename;			// name of parse-file
	
	// instances and prototypes	
	CParseList names[CLASSNUM];
	zCList<zSTRING> parseInfoList;

	// CParser parser;
public:
	spcCParseInfo();	
	virtual ~spcCParseInfo();

	// BOOL		Parse( CString xFilename, spcCWorkingDlg* msgdlg );
	
	CString		CreateExtendedName(CParseItem* item);

	void		CreateClassInfo(T_CLASS ci);

	void		GetNameList(T_CLASS ci, CListBox* namelist, CString xFilter = "");
	CString		GetClassValue(T_CLASS ci, CString objectname, CString varname);	

	void		PrepareParseInfo();
	void		UpdateParseInfo();
};


extern spcCParseInfo* parseinfo;


#endif