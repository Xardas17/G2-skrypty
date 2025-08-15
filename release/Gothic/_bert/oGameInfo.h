/******************************************************************************** 
 
     $Workfile:: ogameinfo.h          $                $Date:: 28.08.00 14:31   $
     $Revision:: 6                    $             $Modtime:: 24.08.00 12:09   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/ogameinfo.h $
 * 
 * 6     28.08.00 14:31 Speckels
 * 
 * 17    23.08.00 21:46 Admin
 * 
 * 4     21.08.00 18:46 Speckels
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
 * 3     30.03.00 14:22 Speckels
 * 
 * 19    7.02.00 17:58 Speckels
 * 
 * 18    2.12.99 22:52 Speckels
 * release-candidate stage object-interaction
 * 
 * 17    21.10.99 23:41 Speckels
 * 
 * 16    27.09.99 16:29 Speckels
 * Aktualisierungen fuer SourceSafe
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 6 $ ($Modtime: 24.08.00 12:09 $)


#ifndef __OGAMEINFO_H__
#define __OGAMEINFO_H__


#include "zgameinfo.h"


class oCPlayerInfo;

class oCGameInfo : public zCGameInfo
{	
public:
	oCGameInfo			();
	virtual ~oCGameInfo	();

	virtual void Init	();

protected:
	
	virtual void Pack	(zCBuffer& buffer, zBYTE flag);
	virtual void Unpack	(zCBuffer& buffer);	
};


#endif
