
/******************************************************************************** 
 
     $Workfile:: zspytypes.h          $                $Date:: 4.12.00 18:22    $
     $Revision:: 7                    $             $Modtime:: 4.12.00 18:01    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/zspytypes.h $
 * 
 * 7     4.12.00 18:22 Moos
 * 
 * 6     28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 4     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 3     10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 2     5.05.00 13:46 Speckels
 * 
 * 3     4.05.00 22:17 Speckels
 * 
 * 1     2.05.00 13:32 Speckels
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:24 Speckels
 * 
 * 2     2.12.99 22:50 Speckels
 * UDP-Kommunikationsstruktur mfuer Spy und Error-Klasse
 * 
 * 1     2.12.99 21:04 Speckels
 * 
 ***********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 7 $ ($Modtime: 4.12.00 18:01 $)



#ifndef __ZSPYTYPES_H__
#define __ZSPYTYPES_H__

struct zTErrorMessage
{
	char username[20];
	bool command;
	int  level;	
	char type[10];
	char message[255];
	char position[100];	
};

#endif