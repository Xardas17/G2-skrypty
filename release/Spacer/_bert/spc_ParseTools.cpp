
#include "stdafx.h"

#include "zengine.h"

#include "spacer.h"
#include "spc_ParseTools.h"
#include "spcCConfiguration.h"
#include "spcCWorkInfoDlg.h"

#include "zvob.h"
#include "z3d.h"

// #include "ogame.h"
// #include "zParserU.h"

const zSTRING PARSEINFO_FILE = "OUINFO.INF";

spcCParseInfo* parseinfo;
spcCWorkInfoDlg* msgdlg;

// Custom List

CParseList::CParseList()
{
	pos = NULL;
}

void CParseList::DeleteAll()
{
	list.RemoveAll();
}

void CParseList::Add(char type, CString name)
{
	CParseItem* item = new CParseItem;
	item->type = type;
	item->name = name;
	
	list.AddTail(item);
	pos = list.GetHeadPosition();
};

CParseItem* CParseList::GetFirst()
{
	pos = list.GetHeadPosition();
	if (pos==NULL) return NULL;
	return list.GetNext(pos);	
}

CParseItem* CParseList::GetNext()
{	
	if (pos==NULL) return NULL;
	return list.GetNext(pos);
}

enum TParseError { PE_NONE, PE_ERROR };
TParseError parseError = PE_NONE;

void ParserError(zSTRING msg)
{
	if (msgdlg)	msgdlg->AddMessage("> "+CString(msg.ToChar()));
	if (parser.Error()==TRUE) 
	{
		parseError = PE_ERROR;
	}
}

spcCParseInfo::spcCParseInfo()
{
}

void spcCParseInfo::PrepareParseInfo()
{			
	parseInfoList.DeleteListDatas();
	for (int i=0;i<spcConfig.OUFilterList.GetNumInList();i++)
	{
		if (spcConfig.OUFilterList[i]) parseInfoList.Insert(new zSTRING(spcConfig.OUFilterList[i]->GetName().GetBuffer(0)));
	};
	
	parser.SetInfoFile(&parseInfoList,PARSEINFO_FILE);
}

void spcCParseInfo::UpdateParseInfo()
{
	//parser.CreateAdditionalInfo(spcConfig.OUFilterList,zSTRING(PARSEINFO_FILE));	
	CreateClassInfo(CLASS_NPC);
	CreateClassInfo(CLASS_ITEM);
	CreateClassInfo(CLASS_MOB);
	zCParser* soundParser = new zCParser();
	soundParser->SetStopOnError(FALSE);
	zoptions->ChangeDir(DIR_SCRIPTS);

	// [BENDLIN] AddonMOD
	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString(zOPT_SEC_FILES, "SoundEffects");
	if (filename.IsEmpty())
		filename = "System\\Sfx";
	zERR_MESSAGE(4, 0, "N: SPC: Loading file " + filename + ".src or .dat");
	
	soundParser->Parse(filename + ".src");

	//CreatClassInfo
	names[CLASS_SOUNDS].DeleteAll();
	zSTRING classname = CLASSINFO[CLASS_SOUNDS].name;
	int pos,typ,anz,c,classindex;
	zSTRING s;
	CString f1,f2,f3;
	classindex = soundParser->GetIndex(classname);
	if (classindex!=-1)
	{
		// Get instances
		soundParser->GetSymbolInfo(classindex,typ,anz);
		pos = soundParser->GetInstance(classindex,0);			
		while (pos>=0)
		{
			s = soundParser->GetSymbolInfo(pos,typ,c);			
			names[CLASS_SOUNDS].Add('I',s.ToChar());
			pos = soundParser->GetInstance(classindex,pos+1);			
		}
	
	}
	
	parser.SetInfoFile(0);
};


/*
BOOL spcCParseInfo::Parse( CString xFilename, spcCWorkInfoDlg* dlg )
{		
	zPATH filepath(zSTRING(xFilename.GetBuffer(0)));	
	
	msgdlg = dlg;
	int range = 1;
		
	parser.SetMessageFunc(ParserError);
	// Parse file
	if (msgdlg) msgdlg->AddMessage("Parsing file "+xFilename);	

	xFilename.MakeUpper();

	zCList<zSTRING> ouFilterList;
	for (int i=0;i<spcConfig.OUFilterList.GetNumInList();i++)
	{
		if (spcConfig.OUFilterList[i]) ouFilterList.Insert(new zSTRING(spcConfig.OUFilterList[i]->GetName().GetBuffer(0)));
	};	

	if (xFilename.Find(".DAT")>=0)
	{
		parser.Reset();		

		parser.SetStopOnError(FALSE);
		parser.Parse( filepath.GetFilename()+".DAT" );

		if (parser.Error())
		{
			if (msgdlg) {
				msgdlg->AddMessage("Error while parsing DAT-file!!");
				msgdlg->AddMessage("Parsing SRC-file");
			}
			parser.Reset();
			parser.SetStopOnError(TRUE);
			// zusätzliche Informationen			

			parser.CreateAdditionalInfo(ouFilterList,zSTRING(PARSEINFO_FILE));

			parser.Parse( filepath.GetFilename()+".SRC" );	
		}

	}
	else if (xFilename.Find(".SRC")>=0)
	{
		parser.Reset();
		// oCGame::DefineExternals_Spacer(&parser);

		// zusätzliche Informationen
		parser.CreateAdditionalInfo(ouFilterList,zSTRING(PARSEINFO_FILE));
		parser.SetStopOnError(FALSE);
		parser.Parse( filepath.GetFilename()+".SRC" );	

		if (parser.Error())
		{
			if (msgdlg) {
				msgdlg->AddMessage("error while parsing SRC-file!!");
				msgdlg->AddMessage("Parsing old DAT-file");
			}
			parser.Reset();
			// oCGame::DefineExternals_Spacer(&parser);
			parser.SetStopOnError(FALSE);

			parser.Parse( filepath.GetFilename()+".DAT" );	
		}
	}
	else { AfxMessageBox("Wrong file-type");return FALSE; }	

	// extract needed informations
	
	if (msgdlg!=NULL) 
	{
		msgdlg->AddMessage("Finished parsing");
		msgdlg->AddMessage("Creating class-informations");
		msgdlg->AddMessage("> NPCs");CreateClassInfo(CLASS_NPC);
	}

	parser.AddClassOffset(zSTRING("C_NPC" ),sizeof(zCVob));
	if (msgdlg!=NULL) msgdlg->AddMessage("> Items");CreateClassInfo(CLASS_ITEM);
	parser.AddClassOffset(zSTRING("C_ITEM"),sizeof(zCVob));
	if (msgdlg!=NULL) msgdlg->AddMessage("> MOBs");CreateClassInfo(CLASS_MOB);
	parser.AddClassOffset(zSTRING("C_MOB" ),sizeof(zCVob));
	parser.CreatePCode();
	
	if (msgdlg!=NULL) msgdlg->AddMessage("> Sounds");
	
	zCParser* soundParser = new zCParser();
	soundParser->SetStopOnError(FALSE);
	zoptions->ChangeDir(DIR_SCRIPTS);

	// [BENDLIN] AddonMOD
	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString(zOPT_SEC_FILES, "SoundEffects");
	if (filename.IsEmpty())
		filename = "System\\Sfx";
	zERR_MESSAGE(4, 0, "N: SPC: Loading file " + filename + ".src or .dat");
	
	soundParser->Parse(filename + ".src");

	//CreatClassInfo
	names[CLASS_SOUNDS].DeleteAll();
	zSTRING classname = CLASSINFO[CLASS_SOUNDS].name;
	int pos,typ,anz,c,classindex;
	zSTRING s;
	CString f1,f2,f3;
	classindex = soundParser->GetIndex(classname);
	if (classindex!=-1)
	{
		// Get instances
		soundParser->GetSymbolInfo(classindex,typ,anz);
		pos = soundParser->GetInstance(classindex,0);			
		while (pos>=0)
		{
			s = soundParser->GetSymbolInfo(pos,typ,c);			
			names[CLASS_SOUNDS].Add('I',s.ToChar());
			pos = soundParser->GetInstance(classindex,pos+1);			
		}
	
	}
	
	if (msgdlg!=NULL) msgdlg->AddMessage("Finished");

	msgdlg = NULL;		
		
	return parseError==PE_NONE;	
}
*/
spcCParseInfo::~spcCParseInfo()
{		
	parser.Reset();
}

CString spcCParseInfo::CreateExtendedName(CParseItem* item)
{
	CString name;
	name = name + item->name;
	return name;
}


CString spcCParseInfo::GetClassValue(T_CLASS ci, CString xObjectname, CString xVarname)
{

	void *data = malloc(65535);
	memset(data,0,65535);		
	zSTRING classname = CLASSINFO[ci].name;
	zSTRING objectname = xObjectname.GetBuffer(0);
	zSTRING varname = xVarname.GetBuffer(0);
	if (objectname.Search(PROTOTYPE_MARKER)>=0) 
		objectname.Delete(PROTOTYPE_MARKER);	
	if (objectname.Search(INSTANCE_MARKER)>=0) 
		objectname.Delete(INSTANCE_MARKER);
	
	int classindex = parser.GetIndex(classname);
	if (classindex==-1) return "*error*";
	
	zBOOL ignore = zCVob::GetIgnoreVisuals();
	zCVob::SetIgnoreVisuals(TRUE);
	parser.CreateInstance(objectname,data);	
	zCVob::SetIgnoreVisuals(ignore);

	zSTRING value = parser.GetInstanceValue (varname, classindex, data, 0);
	free(data);
	return CString(value.ToChar());
}

void spcCParseInfo::CreateClassInfo(T_CLASS ci)
{
	names[ci].DeleteAll();
	zSTRING classname = CLASSINFO[ci].name;
	int pos,typ,anz,c,classindex;
	zSTRING s;
	CString f1,f2,f3;	
	classindex = parser.GetIndex(classname);
	if (classindex!=-1)
	{
		// Get instances
		parser.GetSymbolInfo(classindex,typ,anz);
		pos = parser.GetInstance(classindex,0);			
		while (pos>=0)
		{
			s = parser.GetSymbolInfo(pos,typ,c);			
			names[ci].Add('I',s.ToChar());
			pos = parser.GetInstance(classindex,pos+1);			
		}
	
	}
}

void spcCParseInfo::GetNameList(T_CLASS ci, CListBox* namelist, CString xFilter)
{	
	zSTRING filter = zSTRING(xFilter.GetBuffer(0));
	namelist->ResetContent();
	
	zSTRING classname = CLASSINFO[ci].name;
	CString text;
	void *data = 0;
	BOOL valid;
	if (filter!="") data = malloc(65535);	

	CParseItem* item = names[ci].GetFirst();
	while (item!=NULL)
	{				
		if (filter!="") 
		{
			memset(data,0,65535);
			int classindex = parser.GetIndex(classname);
			if (classindex==-1)
			{
				if (filter!="") free(data);
				return;
			}
			parser.CreateInstance(zSTRING(item->name.GetBuffer(0)),data);			
			valid = parser.IsValid(classname,data,filter);			
		} else valid=TRUE;
		
		if (valid) namelist->AddString(CreateExtendedName(item));		
		item = names[ci].GetNext();
	}
	if (filter!="") free(data);
}


