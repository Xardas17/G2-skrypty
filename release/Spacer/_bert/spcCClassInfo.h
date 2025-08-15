

#ifndef _SPCCCLASSINFO_H_
#define _SPCCCLASSINFO_H_

#include <zContainer.h>

class spcCCIItem : public zSTRING
{
public:
	int fileRef;

	spcCCIItem() : zSTRING(), fileRef(-1) {};
	spcCCIItem(zSTRING & cn, int fr) : zSTRING(cn), fileRef(fr) {};

};

class spcCClassInfo
{
	// static section
private:
	static zCArray<zSTRING> files;
	static zCArray<spcCCIItem> classes;

public:
	static void Init();

	// nonstatic section
private:
	zBOOL parse(zSTRING & filename);

public:
	spcCClassInfo();
	spcCClassInfo(zSTRING & className);
	virtual ~spcCClassInfo();



};


#endif