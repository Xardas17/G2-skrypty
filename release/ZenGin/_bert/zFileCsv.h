/******************************************************************************** 
 
     $Workfile:: zfilecsv.h           $                $Date:: 4.12.00 18:38    $
     $Revision:: 11                   $             $Modtime:: 4.12.00 18:37    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
 
 * $Log: /current_work/zengin_work/_Bert/zfilecsv.h $
 * 
 * 11    4.12.00 18:38 Hildebrandt
 * 
 * 9     4.12.00 18:22 Moos
 * 
 * 8     28.08.00 15:15 Speckels
 * 
 * 13    23.08.00 21:47 Admin
 * 
 * 6     21.08.00 18:26 Speckels
 * 
 * 11    16.08.00 12:32 Admin
 * 
 * 5     10.08.00 21:47 Speckels
 * 
 * 10    9.08.00 17:12 Admin
 * 
 * 4     21.07.00 12:56 Speckels
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:23 Speckels
 * 
 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 11 $ ($Modtime: 4.12.00 18:37 $)

#ifndef __ZFILECSV_H__
#define __ZFILECSV_H__

#ifndef __ZDISK_H__
#include "zdisk.h"
#endif

#ifndef __ZCONTAINER_H__
#include "zcontainer.h"
#endif

class zCFileCSV : public zFILE_FILE
{
public:
	zCFileCSV();	
	zCFileCSV(const zSTRING& path);
	virtual ~zCFileCSV();

	void	InitCSV();

	void	AddNextHeader(const zSTRING& s);
	void	AddNextField(const zSTRING& s);	
	zSTRING GetNextField (const zSTRING& s="");

	zBOOL	WriteHeader();
	zBOOL	WriteSet();
	zBOOL	ReadSet();
	zBOOL	ReadHeader();

	void	SetFormat(bool hasHeader, const zSTRING& delimiter=";", const zSTRING& frame="\"");

protected:	

	zCArray<zSTRING> columnList;
	
	bool	headerProcessed;
	zSTRING current_set;

	bool	csvHasHeader;
	zSTRING csvFieldDelimiter;
	zSTRING csvFieldFrame;	
	zSTRING csvCompleteDelimiter;

	int column;
};

#endif