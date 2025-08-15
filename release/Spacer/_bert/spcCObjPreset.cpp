
#include "zengine.h"

#include "spcCObjPreset.h"

#include "zArchiver.h"
#include "zdisk.h"

CONST int DELETED_PRESET = -1;

/////////////////////////////////////////////////

const zSTRING PRESET_SUBDIR = "objpresets\\";

zCLASS_DEFINITION ( zCObjPreset,	zCObject, 0 ,1)

zCObjPreset::~zCObjPreset() 
{
	obj=NULL;
}
void zCObjPreset::Archive(zCArchiver &arc)
{
	zCObject::Archive(arc);
	arc.WriteString("presetName"	,presetName);
	arc.WriteObject("preset"		,obj);
}
void zCObjPreset::Unarchive(zCArchiver &arc)
{
	zCObject::Unarchive (arc);
	presetName = arc.ReadString("presetName");
	obj	= arc.ReadObject("preset");
}

/////////////////////////////////////////////////


/* ----------------------------------------------------------------------
	
    zCObjPresetLib::~zCObjPresetLib()

	29.11.2000	[Moos]	
                Aufgeräumt

   ---------------------------------------------------------------------- */

zCObjPresetLib::~zCObjPresetLib()
{
    Dispose();

	for (int z=0; z<viewPointer.GetNumInList(); z++)
		delete viewPointer[z];
}

/* ----------------------------------------------------------------------
	
    zCObjPresetLib::Dispose()

	29.11.2000	[Moos]	
                Leak beseitigt

   ---------------------------------------------------------------------- */

void zCObjPresetLib::Dispose()
{
	for (int z=0; z<GetNumInList(); z++)
    {
		if(array[z]->obj) zRELEASE(array[z]->obj);
        zRELEASE(array[z]);
    }
	this->DeleteList();
}
int zCObjPresetLib::Load()
{
	int result =0;
	DeleteList();
	zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Loading ObjectPresets ...");
	
	zoptions->ChangeDir(DIR_TOOLS_DATA);
	zFILE_FILE subdir(PRESET_SUBDIR);
	subdir.ChangeDir();
	
	// Alle OPF-Dateien (sprich: "Views") suchen...
	zFILE_FILE presetFile;
	bool go = presetFile.FindFirst(zSTRING("*.opf"));
	while (go) 
	{		
		result = Load(presetFile.GetFile());
		go = presetFile.FindNext();
	}

	zERR_MESSAGE(4,zERR_END,"");
	return result;
}

int zCObjPresetLib::Load(zSTRING& filename)
{
	//DeleteList();
	zoptions->ChangeDir(DIR_TOOLS_DATA);
	zFILE_FILE subdir(PRESET_SUBDIR);
	subdir.ChangeDir();

	zCObjPreset* preset;
	zCArchiver* arch = zarcFactory.CreateArchiverRead(filename);
	if (!arch) return 1;
	
	zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Read ObjectPresets \""+filename+"\"");
	while (!arch->EndOfArchive())
	{
		// preset = new zCObjPreset();		
		preset = dynamic_cast<zCObjPreset*>(arch->ReadObject());		
		if (preset)
		{
			if (!GetObjectByName(preset->presetName))
			{
				Insert(preset);
				zERR_MESSAGE(10,0,"B: SPC: Inserted preset "+preset->presetName);
			}
			else
			{
				zERR_WARNING("B: SPC: Preset already exists: "+preset->presetName);
				zRELEASE(preset);
			};
		}		
	}
	zERR_MESSAGE(4,zERR_END,"");
	arch->Close();
	zRELEASE(arch);
	return 0;
}

int zCObjPresetLib::Save()
{
	zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Saving presets ..");

	if (!IsDirty()) 
	{
		zERR_MESSAGE(4,zERR_END,"B: SPC: ObjectPresets did not change. ");
		return 0;
	}	
	zoptions->ChangeDir(DIR_TOOLS_DATA);
	zFILE_FILE subdir(PRESET_SUBDIR);
	subdir.ChangeDir();

	zSTRING filename;	
	int num_presets_in_view = 0;
	int num_presets_in_lib = viewPointer.GetNumInList();
	for ( int vc=0; vc<num_presets_in_lib; vc++)
	{		
		num_presets_in_view = viewPointer[vc]->GetNumInList();
		if (num_presets_in_view>0)
		{
			filename = viewPointer[vc]->GetViewName()+zSTRING(".opf");
			
			zERR_MESSAGE(4,0,"B: SPC: Write ObjectPresets \""+viewPointer[vc]->GetViewName()+".OPF\"");
						
			zCArchiver* arch = zarcFactory.CreateArchiverWrite(filename,zARC_MODE_ASCII);
			if (arch)
			{
				for (int z=0;z<num_presets_in_view;z++)
				{
					int lib_index = viewPointer[vc]->GetSafe(z);				
					// nur schreiben, wenn das Object auch noch existiert.
					if (lib_index!=DELETED_PRESET 
						&& array[lib_index]->obj 
						&& !array[lib_index]->presetName.IsEmpty())
					{
						arch->WriteObject(array[lib_index]);
					}
				}		
				arch->Close();
				zRELEASE(arch);
			}
		}
	}
	zERR_MESSAGE(4,zERR_END,"");
	SetDirty(FALSE);
	return 0;
}
zCObject* zCObjPresetLib::GetObjectByName(zSTRING& pName)
{
	int z=0;
	while (z<GetNumInList() && array[z]->presetName!=pName) z++;
	if (z<GetNumInList()) return array[z]->obj;
	else return 0;
}

int zCObjPresetLib::GetIndexByName(const zSTRING& name)
{
	int z=0;
	int num_in_list = GetNumInList();
	while 
		(
			z<num_in_list 
			&& 
			(array[z]->presetName!=name)
		)
	{
		z++;
	}

	if (z>=num_in_list) return -2;
	return z;
}

zCPresetView* zCObjPresetLib::GetNewView(zSTRING& className)
{
	// Mal schaun, ob es ein solches View schon gibt ...
	int sc=0;
	while (	sc<viewPointer.GetNumInList() && 
			viewPointer[sc]->GetViewName()!=className) sc++;
	
	zCPresetView* newview;
	if (sc==viewPointer.GetNumInList())
		// noe...
	{
		newview = new zCPresetView(this, className);
	}
	else
	{
		// existiert schon ...
		newview = viewPointer[sc];
	}

	// View entsprechend seines (Klassen)Namens mit Inhalt fuellen
	newview->EmptyList();
	for (int z=0; z<GetNumInList(); z++)
	{
		if (array[z]->obj)
		{
			if	(array[z]->obj->GetClassName_()==className)
			{
				newview->Insert(z);
			}
		}
	}

	// Und nun das View in die Viewliste einfuegen
	if (sc==viewPointer.GetNumInList())
	{
		viewPointer.Insert(newview);
	}

	return newview;
}

zBOOL zCObjPresetLib::AddPreset(zCObject* obj, zSTRING& name)
{
	if (name.IsEmpty()) return FALSE;

	// Existiert ein solches Preset schon?
	int z=0;
	while ( z<GetNumInList() 
			&&			
			 (
				array[z]->presetName!=name 
				|| 
				array[z]->GetClassName_()!=obj->GetClassName_()
			 )
		  ) 
	{
		z++;
	}
	if (z<GetNumInList()) return FALSE;	// na, dann wieder raus!

	SetDirty();

	// preset erzeugen und einfuegen	
	zCObjPreset* preset =  new zCObjPreset(0,name);
	preset->obj = obj->CreateCopy();
	Insert(preset);		

	return TRUE;
}

zBOOL zCObjPresetLib::RemovePreset(int lib_index)
{
	// Preset aus allen Views austragen	
	for (int z=0; z<viewPointer.GetNumInList(); z++)
	{
		viewPointer[z]->RemoveFromViewByIndex(lib_index);
	}	

	// Nun preset als geloescht markieren
	zRELEASE(array[lib_index]->obj);
	array[lib_index]->obj=NULL;
	array[lib_index]->presetName.Clear();	

	SetDirty();

	return TRUE;
}

/////////////////////////////////////////////////


void zCPresetView::AddToView(zSTRING& pName)
{
	int z=0;
	while (z<lib->GetNumInList() && (*lib)[z]->presetName!=pName) z++;

	if (z<lib->GetNumInList())
	{
		Insert(z);
	}
}

void zCPresetView::RemoveFromView(int view_index)
{
	array[view_index] = DELETED_PRESET;
}

void zCPresetView::RemoveFromViewByIndex(int lib_index)
{
	int view_index = Search(lib_index);
	if (view_index>=0) array[view_index] = DELETED_PRESET;
};

void zCPresetView::AddPreset(zCObject* obj, zSTRING& name)
{
	bool result = bool(lib->AddPreset(obj,name) == TRUE);
	if (result) 
	{		
		int index = lib->GetIndexByName(name);
		if (index>=0) Insert(index);
	}
}

void zCPresetView::ChangePreset(zCObject* obj,int view_index)
{
	assert (numAlloc>0);
	assert ((view_index>=0) && (view_index<numInArray));

	if (array[view_index]==DELETED_PRESET) return;	
	(*lib)[array[view_index]]->obj = obj;	
}

zSTRING zCPresetView::GetViewName()const
{
	return viewName;
}


void zCPresetView::RemovePreset(int view_index)
{
	if (array[view_index]==DELETED_PRESET) return;
	lib->RemovePreset(array[view_index]);	
}

void zCPresetView::RemovePresetByName(zSTRING name)
{	
	int z=GetViewIndexByName(name);		
	if (z>=0 && z<GetNumInList() && (array[z]!=DELETED_PRESET)) 
	{
		RemovePreset(z);		
	}
}

zCObjPreset* zCPresetView::GetPresetByName(zSTRING name)
{	
	int z=GetViewIndexByName(name);	
	if (z>=0 && z<GetNumInList() && (array[z]!=DELETED_PRESET)) 
	{
		return (*lib)[array[z]];
	}
	return 0;	
}

zCObjPreset* zCPresetView::operator [] (int view_index) const 
{
	assert (numInArray>0);
	assert (numAlloc>0);
	assert ((view_index>=0) && (view_index<numInArray));
	if (array[view_index]==DELETED_PRESET) return 0;
	return (*lib)[array[view_index]];
};

int zCPresetView::GetViewIndexByName(zSTRING name)
{
	int z=0;
	int num_in_list = GetNumInList();
	while 
		(
			z<num_in_list 
			&& 
			(
				(array[z]==DELETED_PRESET) 
				|| 
				((*lib)[array[z]]->presetName!=name)
			)
		)
	{
		z++;
	}

	if (z>=num_in_list) return -2;	
	return z;
}
