/******************************************************************************** 
 
     $Workfile:: oTrigger.h           $                $Date:: 28.08.00 15:15   $
     $Revision:: 7                    $             $Modtime:: 24.08.00 12:09   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/oTrigger.h $
 * 
 * 7     28.08.00 15:15 Speckels
 * 
 * 8     23.08.00 21:46 Admin
 * 
 * 5     21.08.00 18:47 Speckels
 * 
 * 6     16.08.00 12:32 Admin
 * 
 * 4     10.08.00 21:46 Speckels
 * 
 * 5     9.08.00 17:11 Admin
 * 
 * 3     19.07.00 20:51 Speckels
 * 
 * 2     7.07.00 17:28 Speckels
 * 
 * 1     6.07.00 12:30 Admin
 * 
 * 4     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 8     29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 7     16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 6     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 5     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 4     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __OCTRIGGER__
#define __OCTRIGGER__

#include "zVob.h"
#include "zVobMisc.h"
#include "zArchiver.h"


class oCTriggerChangeLevel : public zCTrigger {
	zCLASS_DECLARATION	(oCTriggerChangeLevel)
public:

	oCTriggerChangeLevel	();

	void					SetLevelName			(const zSTRING& level, const zSTRING& vobName);
	
	virtual void			TriggerTarget			(zCVob* vobInstigator);
	virtual void			UntriggerTarget			(zCVob* vobInstigator);

	virtual void			Archive					(zCArchiver& arc);
	virtual void			Unarchive				(zCArchiver& arc);

protected:

	virtual					~oCTriggerChangeLevel	();

	zSTRING					levelName;
	zSTRING					startVob;

};

class oCTriggerScript : public zCTrigger {
	zCLASS_DECLARATION	(oCTriggerScript)
public:

	oCTriggerScript			();

	void					SetScriptFunc			(const zSTRING& name, int calls = 1);

	virtual void			Archive					(zCArchiver& arc);
	virtual void			Unarchive				(zCArchiver& arc);

	virtual void			TriggerTarget			(zCVob* vobInstigator);
	virtual void			UntriggerTarget			(zCVob* vobInstigator);

protected:
	virtual					~oCTriggerScript		();
	
	zSTRING					scriptFunc;	
};

class oCObjectGenerator : public zCVob {
	// Deactivated in class-hierarchie:
	/* zCLASS_DECLARATION	(oCObjectGenerator)*/ 
public:

	oCObjectGenerator		();

	void					SetObjectName			(const zSTRING& objName);
	void					SetObjectSpeed			(zREAL speed);

	virtual void			OnTrigger				(zCVob* otherVob, zCVob* vobInstigator);
	
	virtual void			Archive					(zCArchiver& arc);
	virtual void			Unarchive				(zCArchiver& arc);

protected:

	virtual					~oCObjectGenerator		();

	zREAL					speed;
	zSTRING					objectName;
};


#endif