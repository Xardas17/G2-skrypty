
#ifndef _ZCCSLIB_H_
#define _ZCCSLIB_H_

#include "zContainer.h"

#include "zCCSCutscene.h"

class zCCSLib : public zCObject
{
zCLASS_DECLARATION	(zCCSLib)
public:
	zCCSLib					();
	~zCCSLib				();

	void	RemoveFromLib	(const int index, zBOOL removeNow = TRUE);
	void	DeleteLib		();

	virtual void Archive	(zCArchiver &arc);
	virtual void Unarchive	(zCArchiver &arc);

	zCCSBlock*	GetOU		(int index);

	void	CompactLib		();

	zBOOL	IsLoaded		();
	zBOOL	WasChanged		();

	int		ValidateToken	(zSTRING & tok);
	int		NextFree		();
	int		Add				(zCCSBlock* bl);
	void	Change			();
	void	New				() { loaded=TRUE; };

	int		GetNumInLib		()	{ return ouList.GetNumInList(); };

private:
	zBOOL loaded;
	zBOOL wasChanged;

	zCArraySort<zCCSBlock*> ouList;
	zCCSBlock*				searchBlock;

};

#endif 