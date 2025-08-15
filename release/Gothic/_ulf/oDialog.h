/******************************************************************************** 
 
     $Workfile:: oDialog.h            $                $Date:: 22.05.00 18:42   $
     $Revision:: 4                    $             $Modtime:: 9.05.00 14:17    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oDialog.h $
 * 
 * 4     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:07 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 4     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ODIALOG_H__
#define __ODIALOG_H__

#include "zAI.h"

class oCNpc;

extern int daytime;

class oCAskBox : public zCAIBase
{
public:
				oCAskBox			();
	virtual		~oCAskBox			();			
				
	void		Init				(oCNpc* ask, oCNpc* answer);

	void		DoAI				(zCVob* inVob, zBOOL& vobDeleted);

	void		SetNeutral			();
	void		SetYes				();
	void		SetNo				();
	void		SetPosition			();

	void		Delete				();
	int			GetAnswer			()		{ return answer; };

private:
	zBOOL		fadeout;
	int			answer;
	int			alpha;
	zCVob*		askvob;
	oCNpc*		npc1;
	oCNpc*		npc2;
	zCDecal*	thumb[3];

};

#endif