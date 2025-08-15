/////////////////////////////////////////////////////////////////////////////
// HilfsKlasse

#ifndef _SPCCDRAGVOB_H_
#define _SPCCDRAGVOB_H_

#include "zVob.h"
class zCCSCamera;


class spcCDragVobCtrl
{
	zCVob* dragVobTop;
	zCVob* dragVobBot;
	zCVob* targetVob;
public:
	zCVob* GetTargetVob();
	spcCDragVobCtrl();
	virtual ~spcCDragVobCtrl();

	void	StartDragging	(zCVob* target);
	void	StopDragging	();
	zBOOL	IsDragging		() { return (targetVob!=0); };
	void	Process			();
};
/*
class spcCDragVob : public zCVob
{	

	zCLASS_DECLARATION(spcCDragVob)
public:
	enum spcDrag {dragTOP, dragBOT};
	spcDrag dragType;

	spcCDragVob();
	spcCDragVob( spcDrag _type );
	virtual ~spcCDragVob();

	void ShowYourself(zPOINT3 pos);
	void HideYourself();

};

*/

#endif