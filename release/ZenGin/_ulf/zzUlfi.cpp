/******************************************************************************** 
 
     $Workfile:: ZzUlfi.cpp           $                $Date:: 2.08.00 14:25    $
     $Revision:: 7                    $             $Modtime:: 2.08.00 14:14    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/ZzUlfi.cpp $
 * 
 * 7     2.08.00 14:25 Wohlers
 * 
 * 6     21.07.00 15:35 Wohlers
 * 
 * 5     21.07.00 14:43 Wohlers
 * 
 * 4     22.05.00 18:46 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 6     29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 4     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 2     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/


#include "zCore.h"

#include "zzUlfi.h"

// alle Includes des Autors, die auch exportiert werden sollen

#include "zview.h"
#include "zParser.h"
#include "zConsole.h"
#include "zFonts.h"
#include "zOption.h"

void zUlfi_StartUp()
{
	// FontManager
#if COMPILING_SPACER
	if (!zfontman)
#endif
	zfontman = zNEW( zCFontMan	());
	// Console
	zcon.SetPos					(0,0);
	zcon.SetDim					(8191,1500);
	zcon.SetAutoCompletion		(TRUE);
	// Parser Init
	zCParser::SetEnableParsing	(zoptions->Parm("ZREPARSE"));
}

void zUlfi_ShutDown()
{
	delete zfontman;
};
