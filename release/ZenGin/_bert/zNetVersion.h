/******************************************************************************** 
 
     $Workfile:: znetversion.h        $                $Date:: 4.12.00 18:22    $
     $Revision:: 8                    $             $Modtime:: 4.12.00 18:06    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log:: /current_work/ZenGin/_Bert/znetve $
 * 
 * 8     4.12.00 18:22 Moos
 * 
 * 7     28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 5     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 4     10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:24 Speckels
 * 
 * 2     2.12.99 22:50 Speckels
 * Neue Versionskontrolle im
 * Multiplayer-Menue
 * 
 * 1     23.11.99 16:29 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 8 $ ($Modtime: 4.12.00 18:06 $)

#ifndef __ZNETVERSION_H__
#define __ZNETVERSION_H__


#ifndef __ZSTRING_H__
#include "zstring.h"
#endif

#ifndef __ZTYPES_H__
#include "ztypes.h"
#endif

///////////////////////////////////////////////////////////////
const zINT16 zNET_VERSION = 1;
///////////////////////////////////////////////////////////////

class zCBuffer;

class zCNetVersion
{
public:

	zCNetVersion();
	virtual ~zCNetVersion();
	
	virtual zSTRING	GetVersionString()	const;
	virtual zINT32	GetVersionNumber()	const;
	virtual zINT32	GetChecksum()		const;

	virtual zINT32	CreateChecksum();		

	friend int operator==(const zCNetVersion& v1, const zCNetVersion& v2);
	
	virtual void Pack	(zCBuffer& buffer) const;
	virtual void Unpack	(zCBuffer& buffer);

protected:
	
	zINT32 checksum;
	zINT32 version;

};


#endif