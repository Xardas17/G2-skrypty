/******************************************************************************** 
 
     $Workfile:: oobert.h             $                $Date:: 24.04.01 17:33   $
     $Revision:: 7                    $             $Modtime:: 17.04.01 17:28   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/oobert.h $
 * 
 * 7     24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 6     28.08.00 14:31 Speckels
 * 
 * 17    23.08.00 21:46 Admin
 * 
 * 4     21.08.00 18:47 Speckels
 * 
 * 15    16.08.00 12:32 Admin
 * 
 * 3     10.08.00 21:46 Speckels
 * 
 * 14    9.08.00 17:11 Admin
 * 
 * 2     26.04.00 11:28 Admin
 * 
 * 2     19.04.00 18:36 Speckels
 * 
 * 3     30.03.00 14:23 Speckels
 * 
 * 6     21.10.99 23:42 Speckels
 * Changes for item-interaction and error-handling
 * 
 * 5     27.09.99 16:29 Speckels
 * Aktualisierungen fuer SourceSafe
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 7 $ ($Modtime: 17.04.01 17:28 $)



#ifndef _OOBERT_H_
#define _OOBERT_H_


extern void ExitGame();
extern void ExitSession();
extern void oBert_StartUp();
extern void oBert_ShutDown();

class oCNpc;

extern zBOOL gLogStatistics;
extern void ClearLogStatistics();
extern bool LogStatistics(oCNpc* player);
extern bool LogStatisticsWrite(const zSTRING& path);
extern bool LogStatisticsRead(const zSTRING& path);

#endif
