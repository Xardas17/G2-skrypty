/******************************************************************************** 
 
     $Workfile:: omenu_tools.h        $                $Date:: 1.02.01 15:09    $
     $Revision:: 5                    $             $Modtime:: 1.02.01 13:55    $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/omenu_tools.h $
 * 
 * 5     1.02.01 15:09 Speckels
 * 
 * 4     30.01.01 16:16 Speckels
 * 
 * 3     15.01.01 23:29 Speckels
 * 
 * 2     11.01.01 18:39 Speckels
 * 
 * 1     11.01.01 18:19 Speckels
 * 
 * 1     11.01.01 18:07 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 5 $ ($Modtime: 1.02.01 13:55 $)


#ifndef __OOPTIONS_H__
#define __OOPTIONS_H__

#include "ztypes.h"

extern zBOOL Apply_Options_Video();
extern zBOOL Apply_Options_Audio();
extern zBOOL Apply_Options_Game();
extern zBOOL Apply_Options_Controls();
extern zBOOL Apply_Options_Performance();

extern zBOOL Update_ChoiceBox();

extern zBOOL ChangeMusicEnabled			(zCOptionValue &newValue);

extern zBOOL VidIsResolutionValid(int x, int y, int bpp);

extern zBOOL DefineMenuScriptFunctions();
#endif
