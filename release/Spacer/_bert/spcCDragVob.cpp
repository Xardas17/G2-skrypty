
#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "SpacerView.h"
#include "SpacerDoc.h"
#include "MainFrm.h"

#include "zCSCamera.h"
#include "spcCDragVob.h"



// zCLASS_DEFINITION ( spcCDragVob,	zCVob, 0 ,0)


spcCDragVobCtrl::spcCDragVobCtrl()
{
	dragVobTop	= 0;
	dragVobBot	= 0;
	targetVob	= 0;
};

spcCDragVobCtrl::~spcCDragVobCtrl()
{
	zRELEASE(dragVobTop);
	zRELEASE(dragVobBot);
	targetVob	= 0;
};
	
void spcCDragVobCtrl::StartDragging(zCVob* target)
{
	if (targetVob) StopDragging();

	targetVob=target;
	targetVob->AddRef();

	targetVob->SetDrawBBox3D(TRUE);
	// targetVob->SetShowVisual(FALSE);

	dragVobTop = new zCVob;
	dragVobBot = new zCVob;
	dragVobTop->SetVobName("DragVob 1");
	dragVobBot->SetVobName("DragVob 2");
	dragVobTop->SetVisual("invisible_dragvob.3ds");
	dragVobBot->SetVisual("invisible_dragvob.3ds");
	dragVobTop->SetShowVisual(TRUE);
	dragVobBot->SetShowVisual(TRUE);		
	dragVobTop->SetCollDet(FALSE);
	dragVobBot->SetCollDet(FALSE);

	zTBBox3D bbox = targetVob->GetBBox3DWorld();		
	if (bbox.mins==bbox.maxs) 
	{
		bbox.maxs = bbox.mins + zVEC3(5.0,5.0,5.0);		
	}
	if (CSpacerDoc::doc) 
	{
		CSpacerDoc::doc->InsertVob(dragVobTop,&bbox.maxs,0,targetVob);
		CSpacerDoc::doc->InsertVob(dragVobBot,&bbox.mins,0,targetVob);		
	}	

	//dragVobTop->SetPositionWorld(bbox.maxs);
	//dragVobBot->SetPositionWorld(bbox.mins);	
 
};

void spcCDragVobCtrl::StopDragging()
{
	if (!targetVob) return;
		
	CMainFrame::mainframe->HandleVobRemove(dragVobTop);
	CMainFrame::mainframe->HandleVobRemove(dragVobBot);

	dragVobTop->RemoveVobFromWorld();
	dragVobBot->RemoveVobFromWorld();	
	
	zRELEASE(dragVobTop);
	zRELEASE(dragVobBot);
	
	targetVob->SetDrawBBox3D (FALSE);
	zRELEASE(targetVob);
};

void spcCDragVobCtrl::Process()
{
	if (!targetVob) return;
	if (!dragVobTop) return;
	if (!dragVobBot) return;

	zTBBox3D bbox;
	bbox.mins=dragVobTop->GetPositionWorld();
	bbox.maxs=dragVobBot->GetPositionWorld();	
	// Korrektur	
	for (int d=0; d<3; d++)
	{
		if (bbox.mins[d]>bbox.maxs[d])
		{
			zREAL tmp = bbox.mins[d];
			bbox.mins[d]=bbox.maxs[d];
			bbox.maxs[d]=tmp;
		}
	}	

	targetVob->SetDrawBBox3D(FALSE);
	targetVob->SetBBox3DWorld(bbox);
	targetVob->SetDrawBBox3D(TRUE);
};


/*



spcCDragVob::spcCDragVob() : zCVob() 
{
	SetVisual("invisible_vobbox.3DS");
	SetShowVisual(FALSE);
	SetCollDetStat(FALSE);
}
spcCDragVob::spcCDragVob( spcDrag _type ) : zCVob(), dragType(_type)
{
	SetVisual("invisible_vobbox.3DS");
	SetShowVisual(FALSE);
	SetCollDetStat(FALSE);
}

spcCDragVob::~spcCDragVob()
{

};

void spcCDragVob::ShowYourself(zPOINT3 pos)
{	
	SetCollDetStat(FALSE);
	SetPositionWorld(pos);
	SetShowVisual(TRUE);
	SetCollDetStat(TRUE);
}
void spcCDragVob::HideYourself()
{
	SetDrawBBox3D(FALSE);
	SetShowVisual(FALSE);	
	SetCollDetStat(FALSE);
}


*/





/*

spcCCamVob::spcCCamVob(zCVob* v)
: camRef(dynamic_cast<zCCSCamera*>(v))
{
	SetShowVisual(true);
}
spcCCamVob::spcCCamVob()
: camRef(0)
{
	SetShowVisual(true);
}

  */

zCVob* spcCDragVobCtrl::GetTargetVob()
{
	return targetVob;
}
