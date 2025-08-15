#include "zcore.h"

#include "zCCSProps.h"
#include "zCCSPool.h"
#include "zCCSManager.h"
#include "zCCSPlayer.h"

#include "zoption.h"
#include "zccslib.h"
#include "zccscontext.h"


zCLASS_DEFINITION (zCCSManager, zCObject, 0, 1)

zSTRING	zCCSManager::LibGetSvmModuleName(int n)
{
	zCCSBlock* block = LibGet(n);		
	if (!block) return "";	
	if (block->GetRoleName().PickWord(1,"_","_")=="SVM") 
		return block->GetRoleName().PickWord(3,"_","_");
	else 
		return "";
};

zBOOL zCCSManager::LibIsSvmModuleRunning(int n)
{	
	zSTRING s = LibGetSvmModuleName(n);
	if (s.IsEmpty()) return FALSE;
	return libSvmModuleList.IsInList(s);
};

zBOOL zCCSManager::LibSvmModuleStart	(int n)
{
	zSTRING s = LibGetSvmModuleName(n);
	if (s.IsEmpty())					return TRUE;
	if (libSvmModuleList.IsInList(s))	return FALSE;
	libSvmModuleList.Insert(s);
	return TRUE;
};

zBOOL zCCSManager::LibSvmModuleStop 	(int n)
{
	zSTRING s = LibGetSvmModuleName(n);
	if (s.IsEmpty())					return TRUE;
	if (!libSvmModuleList.IsInList(s))	return FALSE;
	libSvmModuleList.Remove(s);
	return TRUE;
};

	zCArray<zSTRING>	libSvmModuleList;

zCCSManager::zCCSManager() 
			: commandStrings(), csPool(), csPlayerList()
{	
	#ifdef COMPILING_SPACER
		iteration = 0;
		src_lib = 0;
	#endif

	library = zNEW(zCCSLib());
		
	zCCSCutsceneContext::playDisabled = zoptions->ReadBool(zOPT_SEC_INTERNAL,"cutscenesDisabled",FALSE);	
}

zCCSManager::~zCCSManager()
{	

	// Pool leeren
	for (int i=0;i<csPool.GetNumInList();i++)
	{
		zRELEASE(csPool[i]);
	}
	csPool		.EmptyList();

	// PlayerList leeren
	for (i=0;i<csPlayerList.GetNumInList();i++)
	{
		zRELEASE(csPlayerList[i]);
	}
	csPlayerList.EmptyList();	
	
	zRELEASE(library);

	#ifdef COMPILING_SPACER
		zRELEASE(iteration);
		zRELEASE(src_lib);
	#endif
}



zCCSPlayer* zCCSManager::CreateCutscenePlayer(zCWorld* ownerWorld)
{
	zCCSPlayer* player			= zNEW(zCCSPlayer);
	player->SetOwnerWorld		(ownerWorld);	
	InsertPlayerInList			(player);
	return player;
};

void zCCSManager::RemoveCutscenePlayer(zCCSPlayer* csplayer)
{
	RemovePlayerFromList(csplayer);
}

void zCCSManager::InsertPlayerInList(zCCSPlayer* csplayer)
{
	csplayer->SetOwnerManager	(this);
	csPlayerList.Insert			(csplayer);
	csplayer->AddRef			();
};

void zCCSManager::RemovePlayerFromList(zCCSPlayer* csplayer)
{
	csplayer->SetOwnerManager	(0);
	csPlayerList.Remove			(csplayer);
	zRELEASE					(csplayer);
};

	

// [Andre]
// Pool-Methoden
///
zCCSCutsceneContext* zCCSManager::InitiateCSwithContext(zCCSCutsceneContext* context)
{
	zCCSPoolItem* poolItem = PoolFindItem(context->GetCSName());
	if (poolItem)
	{
		if (!poolItem->IsAllowedToPlay())	return context;		
		if (poolItem->IsDeactivated())		return context;

		context->allowedToPlay=poolItem->IsAllowedToPlay();
	}
	else
	{
		poolItem = zNEW(zCCSPoolItem(context));
		int val;
		poolItem->SetRunBehaviour(context->properties->GetRunBehaviour(val),val);
		PoolInsertItem(poolItem);			
	} 

	context->SetPoolItem(poolItem);

	return context;
}
zCCSCutsceneContext* zCCSManager::InitiateOUwithContext(zCCSCutsceneContext* context)
{
	// Die Aufgabe dieser Methode ist eine OU mit neuen Daten zu versehen
	int ref = context->GetOUReference();
	if (ref>=0)
		context->UseThisSubBlock(LibGet(ref));

	return context;
}

zCCSCutsceneContext* zCCSManager::CreateNewCutscene(zSTRING & csname)
{
	zCCSPoolItem* poolItem = PoolFindItem(csname);
	if (poolItem)
	{
		if (!poolItem->IsAllowedToPlay())			return 0;
		if (poolItem && poolItem->IsDeactivated())	return 0;
	}

	zCCSCutsceneContext* newContext = zNEW(zCCSCutsceneContext(csname));
		
	if (!poolItem)
	{
		poolItem = zNEW(zCCSPoolItem(newContext));
		int val;
		poolItem->SetRunBehaviour(newContext->properties->GetRunBehaviour(val),val);
		PoolInsertItem(poolItem);			
	} 
	else
	{
		newContext->allowedToPlay=poolItem->IsAllowedToPlay();
	}
	
	newContext->SetPoolItem(poolItem);

	return newContext;
}
zCCSCutsceneContext* zCCSManager::CreateNewOutputUnit(int ref)
{
	if (LibValidateOU(ref)==FALSE) return 0;
	zCCSBlock* lbl = LibGet(ref);
	zCCSCutsceneContext* newContext = zNEW(zCCSCutsceneContext(lbl,ref,TRUE)); // asUnit
	//kein Poolitem erzeugen!!!
	return newContext;
}

zBOOL zCCSManager::IsDeactivated(zSTRING & csname)
{
	zCCSPoolItem* item = PoolFindItem(csname);
	if (item) return item->IsDeactivated();
	else return FALSE;
}

void zCCSManager::PoolCountStart(zSTRING & csname)
{
	zCCSPoolItem* item = PoolFindItem(csname);
	if (item) item->IncNumPlayed();
}

void zCCSManager::PoolCountStop(zSTRING & csname)
{
	zCCSPoolItem* item = PoolFindItem(csname);
	if (item) item->TestedDeactivation();
}

zBOOL zCCSManager::PoolHasFlags(zSTRING & csname, int flags)
{
	zCCSPoolItem* item = PoolFindItem(csname);
	return item?item->HasFlags(flags) : FALSE;
};

void zCCSManager::PoolClrFlags(zSTRING & csname, int flags)
{
	zCCSPoolItem* item = PoolFindItem(csname);
	if (item) item->ClrFlags(flags);
};

void zCCSManager::PoolSetFlags(zSTRING & csname, int flags)
{
	zCCSPoolItem* item = PoolFindItem(csname);
	if (item) item->SetFlags(flags);
};


int	zCCSManager::PoolNumPlayed(zSTRING & csname)
{
	zCCSPoolItem* item = PoolFindItem(csname);
	return item ? item->GetPlayCounter() : 0;
};

int zCCSManager::PoolAllowedToStart(zSTRING & csname)
// 1==ja, 0==nein und -1==cs giebs nicht
{	
	zCCSPoolItem* item = PoolFindItem(csname);
	if (item)
	{
		if (item->IsAllowedToPlay()) return 1;
		else return 0;
	} else return -1;
}

void zCCSManager::PoolInsertItem(zCCSPoolItem* item)
{
	csPool.Insert(item);
/*	int z=0;
	while(i<csPool.GetNumInList() && *item>=*(csPool[i])) )
		i++;
	if (i<csPool.GetNumInList())
		csPool.InsertAtPos(item,i);
	else csPool.InsertEnd(item);*/
}

zCCSPoolItem* zCCSManager::PoolFindItem(zSTRING & csname)
{
	if (csname.Search(".")<=0) csname+=".CS";
	csname.Upper();
	int z=0;
	while(z<csPool.GetNumInList() && csname!=*(csPool[z]))  z++;

	if (z<csPool.GetNumInList()) 
	{
		return csPool[z];
	}
	else 
	{
		return 0;
	}
}

void zCCSManager::PoolResetAll()
{
	for (int z=0; z<csPool.GetNumInList(); z++)
	{
		csPool[z]->ResetNumPlayed();
	}
}
void zCCSManager::PoolResetByHour()
{
	for (int z=0; z<csPool.GetNumInList(); z++)
	{
		if (csPool[z]->GetRunBehaviour()==zCCSProps::RUN_PERHOUR)
			csPool[z]->ResetNumPlayed();
	}
}
void zCCSManager::PoolResetByDay()
{
	for (int z=0; z<csPool.GetNumInList(); z++)
	{
		if (csPool[z]->GetRunBehaviour()==zCCSProps::RUN_PERDAY)
			csPool[z]->ResetNumPlayed();
	}
}


void zCCSManager::AddCommand(zSTRING & comm)
{
	commandStrings.Insert(comm);
}

int	zCCSManager::GetNumOfShortCom()
{
	return commandStrings.GetNumInList();
}

zSTRING zCCSManager::GetShortCom(int z)
{
	if (z>=0 && z<commandStrings.GetNumInList())
		return commandStrings[z];
	else
	{
		zERR_WARNING("A: (zCCSManager::GetShortCom)");
		return zSTRING("NO");
	}
}

void zCCSManager::Archive(zCArchiver &arc)
{
	zCObject::Archive(arc);

	if (!arc.InSaveGame()) return;

	// Pool speichern	
	arc.WriteInt("poolCount", csPool.GetNumInList());
	zSTRING itemChunkName("poolItem");
	for (int z=0; z<csPool.GetNumInList(); z++)
	{
		arc.WriteObject(zSTRING(itemChunkName+zSTRING(z)).ToChar(),csPool[z]);
	}

}

void zCCSManager::Unarchive(zCArchiver &arc)
{
	zCObject::Unarchive(arc);

	if (!arc.InSaveGame()) return;

	// Aktuellen Pool entfernen
	for (int z=0; z<csPool.GetNumInList(); z++)
	{
		zRELEASE(csPool[z]);
	}
	csPool.EmptyList();
	
	// Pool laden	
	int pAnz = 0;
	arc.ReadInt("poolCount",pAnz);
	zSTRING itemChunkName="poolItem";
	z = 0;
	while (z<pAnz)
	{
		csPool.InsertEnd(dynamic_cast<zCCSPoolItem*>(arc.ReadObject(zSTRING(itemChunkName+zSTRING(z)).ToChar())));
		z++;
	}
}

void zCCSManager::LibLoad(int flags)
{
	if (!library) return;
	
	library->DeleteLib();

	zBOOL loaded = FALSE;
	zBOOL binTried = FALSE;

	// [BENDLIN] AddonMOD
	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString(zOPT_SEC_FILES, "OutputUnits");
	if (filename.IsEmpty())
		filename = "OU";
	
	// Soll versucht werden, die Binaerdatei zu laden?
	if ((flags & zLIB_LOAD_BIN)!=0) 		
	{		
		binTried = TRUE;

		zFILE* libFile = zfactory->CreateZFile(zoptions->GetDirString(DIR_OUTPUTUNITS) + filename + ".bin");
		zBOOL binisda = libFile->Exists();		
		if (binisda)
		{
			zERR_MESSAGE(5,0,"B: SPC: Loading binary output-library "+libFile->GetFile()+"...");

			libFile->Open();
			
			zCArchiver* arch = zarcFactory.CreateArchiverRead(libFile);							
			if (arch)
			{
				arch->ReadObject(library);
				arch->Close();
				zRELEASE(arch);
			}
			
			libFile->Close();
			loaded = TRUE; // mit Erfolg
		}
		delete libFile;
		libFile=0;
	}

	// Falls noch nicht binaer geladen: ASCII-Version laden?
	if (!loaded && (flags & zLIB_LOAD_ASCII)!=0)
	{		
		zFILE* libFile = zfactory->CreateZFile(zoptions->GetDirString(DIR_OUTPUTUNITS) + filename + ".csl");
		
		zBOOL isda = libFile->Exists();
		if (isda)
		{
			zERR_MESSAGE(5,0,"B: SPC: Loading ascii output-library "+libFile->GetFile()+"...");		
						
			libFile->Open();			

			zCArchiver* arch = zarcFactory.CreateArchiverRead(libFile);
			if (arch)
			{
				arch->ReadObject(library);
				arch->Close();
				zRELEASE(arch);
			
			}
			libFile->Close();
			loaded = TRUE; // mit Erfolg		

			// Falls ASCII statt BINAER geladen, dann aktuelle Version binaer speichern
			// damit sie beim naechsten Mal als Binaerdatei gefunden wird
			if (binTried) LibStore(zLIB_STORE_BIN); 
		} 
		
		delete libFile;
		libFile=0;						
	}		
	
	// NIx geladen: Dann leere Lib erzeugen:
	if (!loaded)
	{
		library->New();
#ifndef COMPILING_SPACER
		zerr.Fault("N: CS: File for output-units not found: " + filename + ".bin or " + filename + ".csl");
#endif
	}
};

// cutsceneLib functions
void zCCSManager::LibCheckLoaded(int flags)
{		
	if (!library->IsLoaded()) LibLoad(flags);		
}

zCCSBlock* zCCSManager::LibGetFirst()
{
	LibCheckLoaded();
	iterator =0;
	while (iterator<library->GetNumInLib() && library->GetOU(iterator)==NULL) iterator++;
	if (iterator<library->GetNumInLib()) return library->GetOU(iterator);
	else return 0;
}

zCCSBlock* zCCSManager::LibGetNext()
{
	if (!library->IsLoaded()) return NULL;
	iterator++;
	while (iterator<library->GetNumInLib() && library->GetOU(iterator)==NULL) iterator++;
	if (iterator<library->GetNumInLib()) return library->GetOU(iterator);
	else return 0;
}

zCCSBlock* zCCSManager::LibGetFirst(int & n)
{
	LibCheckLoaded();
	iterator =0;
	while (iterator<library->GetNumInLib() && library->GetOU(iterator)==NULL) iterator++;
	if (iterator<library->GetNumInLib()) { n=iterator; return library->GetOU(iterator); } 
	else return 0;
}

zCCSBlock* zCCSManager::LibGetNext(int & n)
{
	if (!library->IsLoaded()) return NULL;
	iterator++;
	while (iterator<library->GetNumInLib() && library->GetOU(iterator)==NULL) iterator++;
	if (iterator<library->GetNumInLib()) { n=iterator; return library->GetOU(iterator); } 
	else return 0;
}

zCCSBlock* zCCSManager::LibGet(int n)
{
	LibCheckLoaded();
	iterator = n;
	if (iterator<library->GetNumInLib()) return library->GetOU(iterator); 
	else return 0;
}


int	zCCSManager::LibAddOU(zCCSBlock* bl)
{
	LibCheckLoaded();
	return library->Add(bl);
}

void zCCSManager::LibDelOU(int n)
{
	LibCheckLoaded();
	library->RemoveFromLib(n);
	// LibStore();  // save
}
void zCCSManager::LibNullOU(int n)
{
	LibCheckLoaded();		
	library->RemoveFromLib(n,FALSE);
}

// store is force to save
void zCCSManager::LibStore	(int flags)
{
	// [BENDLIN] AddonMOD
	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString(zOPT_SEC_FILES, "OutputUnits");
	if (filename.IsEmpty())
		filename = "OU";
	
	if (library->IsLoaded())
	{		
		zSTRING path = zoptions->GetDirString(DIR_OUTPUTUNITS);		

		if ( (flags & zLIB_STORE_ASCII) != 0)
		{
			zERR_MESSAGE(4,0,"B: CSL: Writing ascii version of Cutscene-Library (OutputUnits) to " + filename + ".csl ...");
			// ASCII-Version speichern
			zCArchiver* arch = zarcFactory.CreateArchiverWrite(path + filename + ".csl", zARC_MODE_ASCII);
			if (arch)
			{
				arch->WriteObject(library);
				arch->Close();
				zRELEASE(arch);
			}
		}

		if ( (flags & zLIB_STORE_BIN) != 0)
		{
			zERR_MESSAGE(4,0,"B: CSL: Writing binary version of Cutscene-Library (OutputUnits) to " + filename + ".bin ...");
			// Binaere Version speichern			
			zCArchiver* arch = zarcFactory.CreateArchiverWrite(path + filename + ".bin", zARC_MODE_BINARY_SAFE);
			if (arch)
			{
				arch->WriteObject(library);
				arch->Close();
				zRELEASE(arch);
			}
		}
	}
#ifdef COMPILING_SPACER
	if (src_lib)
		zRELEASE(src_lib);
#endif
}


zBOOL zCCSManager::LibValidateOU( int ref )
{
	LibCheckLoaded();
	return (library->GetNumInLib()>ref && library->GetOU(ref)!=NULL);
}

int zCCSManager::LibValidateOU( zSTRING & token )
{
	LibCheckLoaded();
	return library->ValidateToken(token);
}

/*
zCCSPoolItem* zCCSManager::PoolGetItem(zSTRING& cs)
{
	zSTRING s1, s2(cs);
	s2.Upper();
	for (int i=0; i<csPool.GetNumInList(); i++)
	{
		s1 = csPool[i];		
		s1.Upper();		
		if (s1==s2) return csPool[i];
	}
	return 0;
};
*/

void zCCSManager::LibForceToLoad()
{ 
	LibCheckLoaded(); 
};

zBOOL zCCSManager::LibIsLoaded()
{ 
	return library->IsLoaded(); 
};
	
zCCSProps* zCCSManager::CreateProperties()
{
	return zNEW(zCCSProps);
};

#ifdef COMPILING_SPACER

	void zCCSManager::OpenCSForIteration(zSTRING & scene)
	{	
		zFILE* f = zfactory->CreateZFile(zoptions->GetDirString(DIR_CUTSCENES) + scene + zSTRING(".CS"));
		if (f->Exists())
		{
			f->Open();

			zCArchiver* arch = zarcFactory.CreateArchiverRead(f);						
			iteration = dynamic_cast<zCCutscene*>(arch->ReadObject());
			arch->Close();
			zRELEASE(arch);

			f->Close();		
		}	
		else
		{
			zERR_WARNING("B: CS \""+scene+"\": file not found ("+f->GetFilename()+")");
		}
			
		delete f;f=0;
		iterA = 0;
		iterB = 0;
		iter = 0; //iteration->GetChild(0);
	}

	void zCCSManager::SaveCSForIteration(zSTRING & scene)
	{	
		zCArchiver* arch = zarcFactory.CreateArchiverWrite(zoptions->GetDirString(DIR_CUTSCENES) + scene+zSTRING(".CS"),zARC_MODE_ASCII);		
		arch->WriteObject(iteration);
		arch->Close();
		zRELEASE(arch);
	}

	void zCCSManager::CloseIteration()
	{
		iter=0;
		if (iteration) zRELEASE(iteration);
	}

	zBOOL zCCSManager::Next(zSTRING & Token, zSTRING & Text)
	{
		if (!iteration) return FALSE;
		if (iteration->GetChild(iterA))
		{
			iter = iteration->GetChild(iterA)->GetChild(iterB);
			while (iter==0 && iteration->GetChild(iterA))
			{
				iterA++;
				iterB=0;
				if (iteration->GetChild(iterA))
					iter = iteration->GetChild(iterA)->GetChild(iterB);
			}
			iterB++;
		} 
		return (iter!=0);
	}

	zCCSBlockBase* zCCSManager::BlockLocalize(zCCSBlockBase* block, zSTRING & Text)
	{
		assert(0);
		return 0;
	}

	zBOOL zCCSManager::Localize(zSTRING & Token, zSTRING & Text)
	{	
		if (!src_lib) 
		{
			// [BENDLIN] AddonMOD
			zSTRING filename = "";
			if (zgameoptions)
				filename = zgameoptions->ReadString(zOPT_SEC_FILES, "OutputUnits");
			if (filename.IsEmpty())
				filename = "OU";

			src_lib = zNEW(zCCSLib());
			zFILE *libFile = zfactory->CreateZFile(zoptions->GetDirString(DIR_OUTPUTUNITS) + filename + ".csl");
			zBOOL isda = libFile->Exists();		
			if (isda)
			{
				libFile->Open();

				zCArchiver* arch = zarcFactory.CreateArchiverRead(libFile);	
				if (arch)
				{
					arch->ReadObject(src_lib);
					arch->Close();
					zRELEASE(arch);
				}
				libFile->Close();
			}
			delete libFile;
			libFile=0;
		}
		if (!src_lib) return FALSE;
		
		int entry = src_lib->ValidateToken(Token);
		if (entry>0) 
		{
			BlockLocalize((src_lib->GetOU(entry))->GetChild(0),Text);
			library->Add(src_lib->GetOU(entry));			
			src_lib->RemoveFromLib(entry, FALSE);
			return TRUE;
		}
		return FALSE;
	}

	void zCCSManager::LibCompact()
	{
		LibCheckLoaded();
		library->CompactLib();
	}

#endif

