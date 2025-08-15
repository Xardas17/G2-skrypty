/******************************************************************************** 
 
     $Workfile:: Zzbert.h            $                 $Date:: 4.12.00 18:23    $
     $Revision:: 10                  $              $Modtime:: 4.12.00 17:58    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH

   Description::

 * $Log: /current_work/ZenGin/_Bert/Zzbert.h $
 * 
 * 10    4.12.00 18:23 Moos
 * 
 * 9     20.10.00 21:15 Speckels
 * 
 * 8     25.08.00 18:49 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 7     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 6     10.08.00 21:48 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 5     31.07.00 19:17 Speckels
 * 
 * 4     21.07.00 12:56 Speckels
 * 
 * 3     5.05.00 13:46 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:24 Speckels
 * 
 * 3     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 2     24.09.99 20:41 Speckels
 * VSS-kompatiblen Header eingefügt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 10 $ ($Modtime: 4.12.00 17:58 $)




#ifndef __ZZBERT_H__
#define __ZZBERT_H__

#ifndef __ZOPTION_H__
#include "zoption.h"
#endif

#ifndef __ZOBJECT_H__
#include "zobject.h"
#endif


extern zDWORD* tracePtr_Bert;

extern zBOOL BS_GPLUS;

/*
class zCObjectFactoryVDFS : public zCObjectFactory
{
public:
	zFILE* CreateZFile (const zSTRING& fileName);	
};
*/

extern void zInitOptions();
extern void zDeinitOptions();

// exit-function for fatal-errors
extern void zBert_StartUp();
extern void zBert_ShutDown();

#endif