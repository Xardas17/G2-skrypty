

#ifndef _OCSMANAGER_H_
#define _OCSMANAGER_H_

#include "zCCSManager.h"
  
///
// mögliche Reaktionen des Spielers auf CutsceneVobs
///

#define SCR_NULL		0x00000000

/*
// negative
#define SCR_SIGHT		1<<0  // der Spieler darf nicht sichtbar sein
#define SCR_HEAR		1<<1  // der Spieler darf nicht gehört werden
#define SCR_STEAL		1<<2 // der Spieler darf NPC nicht stehlen
#define SCR_TALK		1<<3 // der Spieler darf NPC nicht ansprechen

// sofort ende 
#define SCR_AIM			1<<10 // das darf der Spieler erst recht nicht...
#define SCR_THREATEN	1<<11
#define SCR_DAMAGE		1<<12

// weitere Zustaende
#define SCR_ISDEAD		1<<15
*/

#define CS_NOT_ALLOWED_AS_ROLE	1<<0


extern const zSTRING zMENU_SEPARATOR;

class zCVob;

///
// Cutscene-Manager
/// 
class oCCSManager : public zCCSManager 
{
zCLASS_DECLARATION	(oCCSManager)
public:	
	oCCSManager();
	virtual ~oCCSManager();

	///
	// Create-Methods
	///

	virtual zCEventMessage* CreateMessage(int z);
	virtual zCEventMessage* CreateOuMessage(); // Constructs PLAYANISOUND by default	
	virtual zCCSProps*		CreateProperties();
	virtual	zCCSPlayer*		CreateCutscenePlayer(zCWorld* ownerWorld);

#ifdef COMPILING_SPACER
	virtual zBOOL			Next			(zSTRING & Token, zSTRING & Text);
	virtual zBOOL			Localize		(zSTRING & Token, zSTRING & Text);
	virtual	zCCSBlockBase*	BlockLocalize	(zCCSBlockBase* block, zSTRING & Text);
#endif

};

#endif