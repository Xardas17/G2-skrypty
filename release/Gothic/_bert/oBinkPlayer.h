/******************************************************************************** 
 
     $Workfile:: obinkplayer.h        $                $Date:: 14.03.01 18:40   $
     $Revision:: 6                    $             $Modtime:: 14.03.01 18:27   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
  
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 6 $ ($Modtime: 14.03.01 18:27 $)

#ifndef _OBINKPLAYER_H_
#define _OBINKPLAYER_H_

#include "zbinkplayer.h"
#include "zrenderer.h"

class oCBinkPlayer : public zCBinkPlayer
{
	zBOOL extendedKeys;
public:
	oCBinkPlayer				();
	virtual ~oCBinkPlayer		();
	

	virtual zBOOL	OpenVideo(zSTRING filename);
	virtual zBOOL	PlayInit	(int frameNr=0);
	virtual zBOOL	PlayFrame	();
	virtual zBOOL	PlayDeinit	();
	virtual zBOOL	PlayHandleEvents();

protected:
	zBOOL disallowInputHandling;
};

#endif

