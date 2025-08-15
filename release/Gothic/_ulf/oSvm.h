/******************************************************************************** 
 
     $Workfile:: oSVM.h               $                $Date:: 22.05.00 18:43   $
     $Revision:: 4                    $             $Modtime:: 9.05.00 14:24    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oSVM.h $
 * 
 * 4     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

// *********************************
// Standard Voice Modul
// *********************************

#ifndef __OSVM__
#define __OSWM__

#include "zString.h"

class oCSVM;

class oCSVMManager {
public :
	oCSVMManager		( );
	~oCSVMManager		( );

	int			GetOU	( const zSTRING& name, int voicenr );
private :
	int			svm_max;

	oCSVM*		sv_module;
};

class oCSVM {
public:
	oCSVM						( );
	~oCSVM						( );

	void		InitByScript	( int i );
	int			GetOU			( const zSTRING& id );

private:
	int			number;
	int			classindex;
	zSTRING*	entry;
};

#endif
