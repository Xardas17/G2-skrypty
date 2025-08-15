/******************************************************************************** 
 
     $Workfile:: znetversion.cpp      $                $Date:: 25.01.01 10:40   $
     $Revision:: 8                    $             $Modtime:: 25.01.01 10:40   $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log:: /current_work/ZenGin/_Bert/znetve $
 * 
 * 8     25.01.01 10:40 Moos
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
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 8 $ ($Modtime: 25.01.01 10:40 $)


#include "zcore.h"
#include "znetversion.h"
#include "zbuffer.h"
#include "zerror.h"



zCNetVersion::zCNetVersion()
{
	version		=	zNET_VERSION;
	checksum	=	0;
};	


zCNetVersion::~zCNetVersion()
{

};




zINT32 zCNetVersion::GetVersionNumber() const
{
	return version;
};



zINT32 zCNetVersion::GetChecksum() const
{
	return checksum;
};

zINT32 zCNetVersion::CreateChecksum()
{
	checksum = GetVersionNumber();
	return checksum;
};


zSTRING zCNetVersion::GetVersionString() const
{
	return zSTRING(version);
};


void zCNetVersion::Pack(zCBuffer& buffer) const
{
	buffer.Write((void*)&version,sizeof(version));
	buffer.Write((void*)&checksum,sizeof(checksum));
};


void zCNetVersion::Unpack(zCBuffer& buffer)
{
	buffer.Read(&version,sizeof(version));
	buffer.Read(&checksum,sizeof(checksum));
};

int operator==(const zCNetVersion& v1, const zCNetVersion& v2)
{
	zERR_MESSAGE(4,0,"B: VERSION: Checksums: "+zSTRING(v1.checksum)+" / "+zSTRING(v2.checksum));
	zERR_MESSAGE(4,0,"B: VERSION: zVersions: "+zSTRING(v1.version)+" / "+zSTRING(v2.version));
	return (v1.checksum == v2.checksum) && (v1.version == v2.version);	
};
