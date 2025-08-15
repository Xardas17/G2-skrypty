/******************************************************************************** 
 
     $Workfile:: ogameinfo.cpp        $                $Date:: 26.01.01 15:57   $
     $Revision:: 10                   $             $Modtime:: 26.01.01 13:45   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/ogameinfo.cpp $
 * 
 * 10    26.01.01 15:57 Speckels
 * 
 * 9     28.08.00 14:31 Speckels
 * 
 * 17    23.08.00 21:46 Admin
 * 
 * 7     21.08.00 18:46 Speckels
 * 
 * 15    16.08.00 12:32 Admin
 * 
 * 6     10.08.00 21:46 Speckels
 * 
 * 14    9.08.00 17:11 Admin
 * 
 * 5     21.07.00 15:16 Speckels
 * 
 * 4     18.05.00 12:19 Speckels
 * 
 * 3     18.05.00 12:18 Speckels
 * 
 * 2     26.04.00 11:28 Admin
 * 
 * 2     19.04.00 18:36 Speckels
 * 
 * 3     30.03.00 14:22 Speckels
 * 
 * 4     7.02.00 17:58 Speckels
 * 
 * 3     21.10.99 23:42 Speckels
 * Changes for item-interaction and error-handling
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 10 $ ($Modtime: 26.01.01 13:45 $)


#include "zcore.h"
#include "ogameinfo.h"
#include "zoption.h"


oCGameInfo::oCGameInfo()
{	
};

oCGameInfo::~oCGameInfo() 
{		
}

void oCGameInfo::Init()
{ 
	zCGameInfo::Init();
	
	SetName("");
};

void oCGameInfo::Pack(zCBuffer& buffer, zBYTE flag)
{
	zCGameInfo::Pack(buffer,flag);
};

void oCGameInfo::Unpack(zCBuffer& buffer)
{
	zCGameInfo::Unpack(buffer);
};
