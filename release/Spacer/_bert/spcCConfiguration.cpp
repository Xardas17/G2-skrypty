// spcCConfiguration.cpp: implementation of the spcCConfiguration class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCConfiguration.h"

#include "zstring.h"
#include "zwin32.h"
#include "zdisk.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif

extern char* REG_COMPANY;

const zSTRING MATLIB_FILENAME = "matlib.ini";

spcCConfiguration spcConfig;

//
// Make sure we have a key in the requested topic
//
void spcCConfiguration::RegCreatePath()
{
	DWORD	cKey;													// Key disposition value

	HKEY baseKey=HKEY_CURRENT_USER;								// CURRENT_USER or LOCAL_MACHINE	

	char keyName[200];
	sprintf(keyName, "Software\\%s\\Spacer\\Settings", REG_COMPANY);		
	RegCreateKeyEx(baseKey, (char*)&keyName, 0, "", 0, KEY_ALL_ACCESS, NULL, &spacerKey, &cKey);


}


void spcCConfiguration::RegWriteBinary(char *Key, void *Data, int Size)
{	
	RegSetValueEx(spacerKey, Key, 0, REG_BINARY, (LPBYTE)Data, Size);   // Write data
}

zBOOL spcCConfiguration::RegGetBinary(char *Key, void *Data, int *Size)
{
	zDWORD ValueType;
	zBOOL result =  ((RegQueryValueEx(spacerKey, Key, 0, &ValueType, (unsigned char*)Data, (DWORD *)Size)==ERROR_SUCCESS) && (ValueType==REG_BINARY));
	if (!result) 
	{
		(*Size)=0;
	}
	return result;;
}

void  spcCConfiguration::RegWriteInt(char *Key, int data)		
{ 	
	RegWriteBinary(Key, &data, sizeof(data));
}

void  spcCConfiguration::RegWriteFloat(char *Key, float data)
{ 
	RegWriteBinary(Key, &data, sizeof(data));
}

zBOOL spcCConfiguration::RegGetInt(char *Key, int& value)
{
	int size = sizeof(value);
	return RegGetBinary(Key,&value,&size);	
}

zBOOL spcCConfiguration::RegGetFloat(char *Key, float& value)
{
	int size = sizeof(value);
	return RegGetBinary(Key,&value,&size);
}

void spcCConfiguration::RegWriteWindowPos(char* Key, spcTRegWindowPosition& data)
{	
	RegWriteBinary(Key, (void *)&data, sizeof(data));	
}


zBOOL spcCConfiguration::RegGetWindowPos(char* Key, spcTRegWindowPosition& data)
{
	int dataSize = sizeof(data);
	zBOOL result = RegGetBinary(Key, (void *)&data, &dataSize);	
	return result;
}

bool operator==(spcCMatFilter item1, spcCMatFilter item2)	
{
	return (item1.name == item2.name && item1.id == item2.id);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

spcCConfiguration::spcCConfiguration()
{
	RegCreatePath();

	Version				= 4; // Version-Constant to manage config-file-version-conflict
	view_x				= 640;
	view_y				= 480;
	view_bpp			= 16;
	movespeed			= 50;
	farclipping			= 1;
	useGrid				= 0;
	useGridTex			= 1;
	moveGrid			= 20;
	moveGridTex			= 10;
	rotGrid				= 11.25;
	rotGridTex			= 11.25;	
	camlight			= 8000;
	moveSpeedTex		= 0.5;	
	compileLightRegion	= 15;
	compileLightQuality = 0;	
	fixedWindows		= true;
	goldmastering		= false;
	interativeSave		= false;
	modeFogging			= false;
	// create default filterlist;
		
	matFilterList.EmptyList();
	spcCMatFilter* item = new spcCMatFilter;
	item->Init(NO_FILTER_FOLDER,spcCMatFilter::NullLib);
	matFilterList.Insert(item);

	OUFilterList.Insert(new spcCOutputUnitFilter("AI_Output",true));
	// OUFilterList.Insert(new spcCOutputUnitFilter("AI_Cutscene",false));

	// TODO: read it from file
	svmName = "SVM.D";

	// now create the registry-keys

}

spcCConfiguration::~spcCConfiguration()
{	
	for (int z=0; z<OUFilterList.GetNumInList(); z++)
		delete OUFilterList[z];	
}

void spcCConfiguration::Save()
{
	zERR_MESSAGE(4,zERR_BEGIN,"B: SPCCFG: Saving configurations ...");
	// schreibe Fensterpositionen
	spcTRegWindowInfo winInfo;
	POSITION pos = windowList.GetHeadPosition();	
	while (pos)
	{		
		winInfo = windowList.GetNext(pos);
		zERR_MESSAGE(5,0,"B: SPCCFG: Saving window-positions of "+zSTRING(winInfo.key.GetBuffer(0)));
		RegWriteWindowPos(winInfo.key.GetBuffer(0),winInfo.position);
	};		

	Save(CString("spcConfiguration.dat"));

	zERR_MESSAGE(4,zERR_END,"B: SPCCFG: Saving configurations ...");
}

void spcCConfiguration::Save(CString fname)
{
	zoptions->ChangeDir(DIR_TOOLS_DATA);	
	zFILE* f = zfactory->CreateZFile(MATLIB_FILENAME);
	if (f->Create()==zERR_NONE)
	{	
		spcCMatFilter* item=0;

		zSTRING line;
		f->Write("[MATERIALFILTER]\r\n");
		// save Matfilters used at this time
		for (int i=0; i<spcCMatFilter::nextMatFilterID; i++)
		{			
			if (i!=spcCMatFilter::NullLib)
			{
				int nr = 0;
				while (nr<matFilterList.GetNumInList())
				{
					item = matFilterList[nr];
					if (item && (item->id == i))
					{
						line = item->name + "=#"+zSTRING(item->id);
						f->Write(line+"\r\n");
						break;
					};
					nr++;
				};			
			}
		}
		// Endmark	
		f->Close();		
	}
	delete f;f=0;

	RegWriteFloat("rotGrid",rotGrid);
	RegWriteFloat("rotGridTex",rotGridTex);
	RegWriteFloat("farClipping",farclipping);
	RegWriteInt("modeFogging",(int)modeFogging);	
	RegWriteInt("moveSpeed",movespeed);
	RegWriteInt("view cx",view_x);
	RegWriteInt("view cy",view_y);	
	RegWriteInt("view bpp",view_bpp);	
	RegWriteInt("useGrid",useGrid);
	RegWriteInt("useGridTex",useGridTex);
	RegWriteInt("moveGrid",moveGrid);
	RegWriteInt("moveGridTex",moveGridTex);
	RegWriteInt("camLight",camlight);
	RegWriteInt("fixedWindows",fixedWindows);
	RegWriteInt("iterativeSave",interativeSave);
	RegWriteInt("compileLightRegion",compileLightRegion);
	RegWriteInt("compileLightQuality",compileLightQuality);
}

void spcCConfiguration::Load()
{

	Load(CString("spcConfiguration.dat"));

	MouseUpArrow = AfxGetApp()->LoadStandardCursor(IDC_UPARROW);
	MouseArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	MouseCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	MouseWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
}

void spcCConfiguration::Load(CString fname)
{	
	// Materialib.ini laden

	zoptions->ChangeDir(DIR_TOOLS_DATA);	
	zFILE* f = zfactory->CreateZFile(MATLIB_FILENAME);
	if (f->Exists())
	{
		zERR_MESSAGE(7,0,"B: SPC: Configuration: Loading file "+MATLIB_FILENAME);
		if (f->Open()==zERR_NONE)
		{				
			// Liste leeren
			matFilterList.EmptyList();
			
			// Trash-Filter erzuegen
			spcCMatFilter* item = new spcCMatFilter;								
			item->Init(NO_FILTER_FOLDER,spcCMatFilter::NullLib);
			matFilterList.Insert(item);
			
			// In der INI-Datei vorkommende Filter einfuegen
			zSTRING line;
			zSTRING matName;
			do
			{
				f->Read(line);

				if (line.Search("#")>0)
				{
					if (line.Search("\"")>=0) 
					{
						line.Delete("\"",zSTR_TO);
						matName = line.PickWord(1,"\"","\"");
					}
					else
					{						
						matName = line.PickWord(1,"=","=");
						matName.TrimLeft();
 						matName.TrimRight();
					};
					line.Delete("#",zSTR_TO);
					zSTRING idStr = line;

					zERR_MESSAGE(7,0,"B: SPC: Configuration: MaterialFilter "+item->name+", #"+zSTRING(item->id));
					item = new spcCMatFilter;
					item->Init(matName.ToChar(),idStr.ToInt());
					matFilterList.Insert(item);					
				}
			}
			while (!f->Eof());
			f->Close();
		}
		else
		{
			zERR_WARNING("B: SPC: Configuration: Loading file "+MATLIB_FILENAME+" failed.");
		};
		delete f;
		f=0;
	}
	else
	{
		zERR_WARNING("B: SPC: Configuration: Loading file "+MATLIB_FILENAME+" failed. Not found!");
	};
		
	if (!zoptions->Parm("nospacercfg")) 
	{
		//int size=200;
		int value;
		
		RegGetFloat("rotGrid",rotGrid);
		RegGetFloat("rotGridTex",rotGridTex);
		RegGetFloat("farClipping",farclipping);
		value = int(modeFogging);RegGetInt("modeFogging",value);modeFogging = bool(value>0);		
		RegGetInt("moveSpeed",movespeed);
		RegGetInt("view cx",view_x);
		RegGetInt("view cy",view_y);	
		RegGetInt("view bpp",view_bpp);	
		RegGetInt("useGrid",useGrid);
		RegGetInt("useGridTex",useGridTex);
		RegGetInt("moveGrid",moveGrid);
		RegGetInt("moveGridTex",moveGridTex);
		RegGetInt("camLight",camlight);
		RegGetInt("fixedWindows",fixedWindows);
		RegGetInt("iterativeSave",interativeSave);
		RegGetInt("compileLightRegion",compileLightRegion);
		RegGetInt("compileLightQuality",compileLightQuality);
	}	
}

int spcCConfiguration::FindMatFilterIndexByName(CString name)
{
	CString filtername;
	name.MakeLower();
	for (int z=0; z<matFilterList.GetNumInList(); z++)
	{
		filtername = matFilterList[z]->name;
		filtername.MakeLower();		
		if (filtername==name) return z;
	}
	return -1;
}
int spcCConfiguration::FindMatFilterIndexById(int id)
{
	for (int z=0; z<matFilterList.GetNumInList(); z++)
		if (matFilterList[z]->id==id) return z;

	return -1;
}

POSITION spcCConfiguration::GetWindowID(CString key, RECT* defRect)
{
	spcTRegWindowInfo winInfo;
	POSITION pos = windowList.GetHeadPosition();	
	POSITION prevPos;
	while (pos)
	{
		prevPos = pos;
		winInfo = windowList.GetNext(pos);
		if (winInfo.key == key) 
		{
			zERR_MESSAGE(5,0,"B: SPCCFG: Found window-informations in list: "+zSTRING(key.GetBuffer(0)));
			return prevPos;		
		}
	};
	
	zERR_MESSAGE(5,0,"B: SPCCFG: Read window-informations: "+zSTRING(key.GetBuffer(0)));
	winInfo.position.pos.x = 0;
	winInfo.position.pos.y = 0;
	winInfo.position.size.cx = 270;
	winInfo.position.size.cy = 400;

	if (defRect)
	{
		winInfo.position.pos.x = defRect->left;
		winInfo.position.pos.y = defRect->top;
		winInfo.position.size.cx = defRect->right-defRect->left;
		winInfo.position.size.cy = defRect->bottom - defRect->top;
	};

	winInfo.key=key;	
	
	if (!zoptions->Parm("nospacercfg")) RegGetWindowPos(key.GetBuffer(0),winInfo.position);
		
	winInfo.key = key;
	pos = windowList.AddTail(winInfo);
	return pos;
};

bool spcCConfiguration::KnowsWindowPosition(CString key)
{	
	spcTRegWindowInfo winInfo;
	POSITION pos = windowList.GetHeadPosition();	
	POSITION prevPos;
	while (pos)
	{		
		prevPos = pos;
		winInfo = windowList.GetNext(pos);
		if (winInfo.key == key) 
		{
			return true;
		}
	};

	return bool(RegGetWindowPos(key.GetBuffer(0),winInfo.position)==TRUE);
};

void spcCConfiguration::GetWindowPosition(POSITION id, spcTRegWindowInfo& info)
{
	info = windowList.GetAt(id);	
};

void spcCConfiguration::SetWindowPosition(POSITION id, RECT rect)
{
	spcTRegWindowInfo winData;
	winData = windowList.GetAt(id);
	winData.position.pos.x = rect.left;
	winData.position.pos.y = rect.top;
	winData.position.size.cx = rect.right-rect.left;
	winData.position.size.cy = rect.bottom-rect.top;
	windowList.SetAt(id,winData);
};


// Verwaltung von Spieler-IDs
zCArray<int>	spcCMatFilter::freeMatFilterIDs;
zBYTE			spcCMatFilter::nextMatFilterID=spcCMatFilter::NullLib+1;


void spcCMatFilter::Init(CString _name, int _id)
{	
	name = _name;
	if (_id>=0) 
	{		
		id = _id;

		zERR_MESSAGE(4,0,"B: SPCCFG: Defined Matfilter \""+zSTRING(_name.GetBuffer(0))+"\" with id "+zSTRING(id));
		if (id>=nextMatFilterID)
		{
			while (nextMatFilterID<id) 
			{
				freeMatFilterIDs.InsertEnd(nextMatFilterID);
				nextMatFilterID++;
			};
			nextMatFilterID++;
		};
		return;
	}

	if (freeMatFilterIDs.GetNumInList()>0)
	{		
		id = freeMatFilterIDs[0];
		freeMatFilterIDs.RemoveIndex(0);

		zERR_MESSAGE(4,0,"B: SPCCFG: Defined Matfilter \""+zSTRING(_name.GetBuffer(0))+"\" with id "+zSTRING(id)+" from freelist");
	}
	else 
	{		
		id = nextMatFilterID;
		nextMatFilterID++;

		zERR_MESSAGE(4,0,"B: SPCCFG: Defined Matfilter \""+zSTRING(_name.GetBuffer(0))+"\" with id "+zSTRING(id)+" from next free id");
	}	

	SetDirty(false);
}

void spcCMatFilter::Deinit()
{
	zERR_MESSAGE(4,0,"B: SPCCFG: Removed Matfilter \""+zSTRING(name.GetBuffer(0))+"\" with id "+zSTRING(id));
	freeMatFilterIDs.InsertEnd(id);
};

spcCMatFilter::~spcCMatFilter()
{	
}

spcCMatFilter::spcCMatFilter()
{	
	name = "";
	id = -1;
	SetDirty(false);
};