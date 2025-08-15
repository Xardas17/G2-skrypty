/******************************************************************************** 
 
     $Workfile:: zvobidentifier.h     $                $Date:: 5.05.00 13:46    $
     $Revision:: 3                    $             $Modtime:: 24.03.00 14:52   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/zvobidentifier.h $
 * 
 * 3     5.05.00 13:46 Speckels
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 6     19.04.00 17:12 Speckels
 * 
 * 2     24.03.00 14:47 Edenfeld
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 3 $ ($Modtime: 24.03.00 14:52 $)


#ifndef __ZVOBIDENTIFIER_H__
#define __ZVOBIDENTIFIER_H__

#include "ztypes.h"
#include "zcontainer.h"

class zCVob;

const zDWORD zVOB_ID_UNDEFINED = 0;

typedef zDWORD zTVobID;

class zCVobIdentifier
{	
public:
	zCVobIdentifier				( );
	virtual ~zCVobIdentifier	( );

	zTVobID GetID				( );
	zTVobID SetID				( zCVob* vob, zTVobID new_id	);
	zTVobID CreateDistinctID	( zCVob* vob					);
private:	
	zTVobID id;

	static zDWORD id_counter;
	static zCArraySort<zCVob*>* vobList;
	static zCVob* SearchVobByID(zTVobID id);
};


#endif