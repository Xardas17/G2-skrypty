#include "zcore.h"
#include "zCCSLib.h"


zCLASS_DEFINITION	(zCCSLib,zCObject,0,0)



void zCCSLib::Archive(zCArchiver &arc)
{	
	zCObject::Archive(arc);

	int numInList = 0;
	for (int i=0;i<GetNumInLib();i++)
	{
		if (ouList[i]) numInList++;
	};

	arc.WriteInt("NumOfItems", numInList);

	zERR_MESSAGE(3,0,"B: CSLib: Number of items: "+zSTRING(numInList)+" (Arc)");

	for (int z=0; z<numInList; z++)
	{
		if (ouList[z]) arc.WriteObject(ouList[z]);
	}
	
	wasChanged=FALSE;
}

void zCCSLib::Unarchive(zCArchiver &arc)
{
	zERR_MESSAGE(3,zERR_BEGIN,"B: CSLib: loading library ...");

	zCObject::Unarchive(arc);

	int anz = arc.ReadInt("NumOfItems");

	zERR_MESSAGE(3,0,"B: CSLib: Number of items: "+zSTRING(anz)+" (UnArc)");

	zCCSBlock* bl;	

	ouList.AllocAbs(15000); // 15000 Elemente reservieren
	for (int z=0; z<anz; z++)
	{
		bl = dynamic_cast<zCCSBlock*>(arc.ReadObject());
		if (bl) 
		{
			ouList.Insert(bl);
			bl->AddRef();
		}
		zRELEASE(bl);
		if ( (z % 250) == 0 ) sysEvent();
	}
	

	zERR_MESSAGE(3,0,"B: CSLib: Sorting library ...");

	ouList.QuickSort();	

	loaded		= TRUE;
	wasChanged	= FALSE;

	zERR_MESSAGE(3,zERR_END,"B: CSLib: finished loading library");	
}

static int compareBlocks(const void* b1,const void* b2)
{
	zCCSBlock* block1 = dynamic_cast<zCCSBlock*>(*((zCCSBlock**)b1));
	zCCSBlock* block2 = dynamic_cast<zCCSBlock*>(*((zCCSBlock**)b2));
	if (!block1) return 1;
	if (!block2) return -1;
	return block1->GetRoleName().CompareTo(block2->GetRoleName());
};

zCCSLib::zCCSLib() 	
{
	loaded		= FALSE;
	wasChanged	= FALSE;	
	searchBlock = zNEW(zCCSBlock);
	ouList.SetCompare(compareBlocks);
};

zCCSLib::~zCCSLib()
{ 
	if (searchBlock) zRELEASE(searchBlock);
	DeleteLib(); 
}

void zCCSLib::DeleteLib()
{
	for (int z=0; z<GetNumInLib(); z++)
	{
		zRELEASE(ouList[z]);
		ouList[z]=0;
	}
	ouList.DeleteList();
	loaded		= FALSE;
	wasChanged	= FALSE;
}
/*
void zCCSLib::RemoveOrderIndexFromLib(const int index)
{
	zRELEASE(ouList[index]);
	ouList.RemoveOrderIndex(index);
}
*/
void zCCSLib::RemoveFromLib		(const int index, zBOOL removeNow)
{
	zRELEASE(ouList[index]);
	ouList[index]=0;
	if (removeNow) 
	{
		ouList.RemoveOrderIndex(index);
	}
}

int zCCSLib::ValidateToken	(zSTRING & tok)
{	
	searchBlock->SetRoleName(tok);
	return ouList.Search(searchBlock);
	/*
	for (int z=0; z<GetNumInLib();z++) 
	{
		if (ouList[z]->GetRoleName()==tok) 
			return z;
	}
	*/
	return -1;
}

zBOOL zCCSLib::IsLoaded()
{
	return loaded;
}
zBOOL zCCSLib::WasChanged()
{
	return wasChanged;
}

int	zCCSLib::NextFree()
{
	return GetNumInLib();
}

int zCCSLib::Add(zCCSBlock* bl)
{
	if (!loaded) return -1;	
	if (bl)
	{
		ouList.Insert(bl);
		bl->AddRef();
	};
	wasChanged = TRUE;
	return GetNumInLib()-1;
}

void zCCSLib::Change()
{
	wasChanged = TRUE;
}

zCCSBlock*	zCCSLib::GetOU(int index)
{
	return ouList[index];
};

void zCCSLib::CompactLib()
{
	int z=0;
	while (z<GetNumInLib())
	{
		if (!ouList[z]) RemoveFromLib(z);
		else z++;
	}
}