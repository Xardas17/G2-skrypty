
#include "zengine.h"

#include <spcCClassInfo.h>
#include "zdisk.h"

// static section

zCArray<zSTRING> spcCClassInfo :: files;
zCArray<spcCCIItem> spcCClassInfo :: classes;

void spcCClassInfo :: Init()
{
	files.EmptyList();
	classes.EmptyList();

	return;  // hier könnte was schieflaufen
	zoptions->ChangeDir(DIR_SYSTEM);
	//zSTRING lfname = zSTRING("Tools\\Spacer\\");
	zFILE_FILE ciFile;
	int actEntry = 0;
	zerr.Message("a: (Spacer::Init()) Loading class-help-files");
	bool go = ciFile.FindFirst(zSTRING("*.cdf"));
	while (go) 
	{
		actEntry = files.GetNumInList();
		files.Insert(ciFile.GetFilename());
		zFILE* f = zfactory->CreateZFile(ciFile.GetFilename()+zSTRING(".cdf"));
		zSTRING line;
		if (f->Exists())
		{
			f->Open();
			while(!f->Eof()) {

			f->Read(line);
			if (line.PickWord(1," "," ")==zSTRING("class"))
				classes.Insert(spcCCIItem(line.PickWord(2," "," "),actEntry));

			}
			f->Close();
		}
		delete f;
		go = ciFile.FindNext();
	}
	
}

// nonstatic section

spcCClassInfo :: spcCClassInfo()
{}
spcCClassInfo :: spcCClassInfo(zSTRING & className)
{

}
spcCClassInfo :: ~spcCClassInfo()
{}