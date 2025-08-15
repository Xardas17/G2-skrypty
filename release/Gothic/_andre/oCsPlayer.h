

#ifndef _OCSPLAYER_H_
#define _OCSPLAYER_H_

#include "zCCSPlayer.h"
  
class zCVob;

///
// CutscenePlayer
///

class zCEventMessage;
class zCCSProps;
class zCCSBlockBase;
class zCWorld;

class oCCSPlayer : public zCCSPlayer 
{
zCLASS_DECLARATION	(oCCSPlayer)

public:
	oCCSPlayer				();
	virtual ~oCCSPlayer		();	

	//virtual zCCSProps* CreateProperties();

protected:
	virtual void ProcessCutscene(zCCSCutsceneContext* cs, const zPOINT3& pos);
};


#endif