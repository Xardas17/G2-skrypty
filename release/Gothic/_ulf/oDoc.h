/******************************************************************************** 
 
     $Workfile:: oDoc.h               $                $Date:: 19.10.00 17:15   $
     $Revision:: 7                    $             $Modtime:: 19.10.00 17:14   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oDoc.h $
 * 
 * 7     19.10.00 17:15 Keskenti
 * 
 * 6     19.07.00 12:45 Wohlers
 * 0.88
 * 
 * 5     5.07.00 12:20 Wohlers
 * 
 * 4     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ODOC__
#define __ODOC__

#include "zViewBase.h"
#include "zView.h"

class oCDoc : public zCView
{
public:
	oCDoc								(const zSTRING& name);
	~oCDoc								();

	void			Show				();
	virtual zBOOL	HandleEvent			(int key);

	void			MapInitCoordinates	(zREAL gcox1, zREAL gcoy1, zREAL px1, zREAL py1, zREAL gcox2, zREAL goy2, zREAL px2, zREAL py2);
	void			MapDrawCoordinates	(zREAL gcox, zREAL gocy);

	void			SetLevelName		(const zSTRING& levelName);

private:

	zSTRING			levelName;
	zREAL			scalex,scaley;

	zREAL			map_gameCoPerPixelx;
	zREAL			map_gameStartx;		
	zREAL			map_gameCoPerPixely;
	zREAL			map_gameStarty;
	zREAL			pixelStartx;
	zREAL			pixelStarty;

	static zCView*	posView;
};

// Current Visible Document
extern oCDoc* document;

#endif
