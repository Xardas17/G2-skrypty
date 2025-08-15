/******************************************************************************** 
 
     $Workfile:: Phoenix.cpp          $                $Date:: 7.02.01 18:00    $
     $Revision:: 10                   $             $Modtime:: 7.02.01 14:21    $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/Phoenix.cpp $
 * 
 * 10    7.02.01 18:00 Speckels
 * 
 * 9     28.09.00 21:08 Speckels
 * 
 * 8     1.09.00 17:50 Rueve
 * 
 * 7     24.08.00 11:30 Moos
 * new durch zNEW ersetzt
 * 
 * 6     21.07.00 15:35 Wohlers
 * 
 * 5     22.05.00 18:44 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 7     29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 4     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 3     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 2     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

// Engine
#include "zCore.h"

#include "zEngine.h"
#include "zRenderer.h"
#include "zFonts.h"
#include "zInput_Win32.h"
#include "zwin32_internal.h"
// Game
#include "oGameManager.h"

#pragma warning ( disable:4244 )

/* ----------------------------------------------------------------------
	
	TestFont()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void TestFont()
{
	do {
		zCOLOR bCol; bCol.SetRGB(255,0,0);
		zrenderer	-> Vid_Clear(bCol);
//		font		-> Print(0, 0,"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
//		font		-> Print(0,30,"abcdefghijklmnopqrstuvwxyz");
//		font		-> Print(0,60,"Das ist ein erster Test ! Scheint zu klappen...");
		zrenderer	-> Vid_Blit				();
		sysEvent();
	} while (!zinput->KeyPressed(KEY_ENTER));
	
	do {
		zCOLOR bCol; bCol.SetRGB(255,0,0);
		zrenderer	-> Vid_Clear(bCol);

		screen		-> SetFont	(0);
		screen		-> Print	(0,   0,"Guten Tach !");
		screen		-> SetFont	(1);
		screen		-> Print	(0,1000,"Guten Tach !");

		zrenderer	-> Vid_Blit				();
		sysEvent();
	} while (!zinput->KeyPressed(KEY_ENTER));
}	

extern int __cdecl MainProg()
{
	sysEvent();

	CGameManager gameMan;
	gameMan.Init(zTSystemContextHandle(hWndApp));
	gameMan.Run();
	gameMan.Done();

//	sysExit();
	return 0;
}

#pragma warning ( default:4244 )

