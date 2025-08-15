/******************************************************************************** 
 
     $Workfile:: zvobidentifier.cpp   $                $Date:: 21.07.00 15:17   $
     $Revision:: 4                    $             $Modtime:: 21.07.00 15:14   $
       $Author:: Speckels                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/zvobidentifier.cpp $
 * 
 * 4     21.07.00 15:17 Speckels
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
/// @version $Revision: 4 $

#include "zvobidentifier.h"
#include "zvob.h"
#include "zerror.h"
#include "zstring.h"

// static members

zDWORD zCVobIdentifier::id_counter = zVOB_ID_UNDEFINED+1;

zCArraySort<zCVob*>* zCVobIdentifier::vobList = 0;


// Suche nach einem Vob mit der angegebenen id
zCVob* zCVobIdentifier::SearchVobByID(zTVobID id)
{	
	if ( (id!=zVOB_ID_UNDEFINED) && vobList && !vobList->IsEmpty() )
	{	
		zCVob* vob;
		int count = vobList->GetNumInList();
		for (int i=0;i<count;i++)
		{
			vob = vobList->Get(i);
			if (vob->GetVobID()==id) return vob;
		};
	}

	return 0;
};


// Veergleich der VOB-ID
// Comparemethode fuer das sortierte vobList-Array
static int CompareVobID(const void* v1, const void* v2)
{
	return ((zCVob*)v1)->GetVobID() - ((zCVob*)v2)->GetVobID();
};



// Constructor
// Setze die ID auf den Defaultwert
zCVobIdentifier::zCVobIdentifier()
{
	id=zVOB_ID_UNDEFINED;		
};




// Destructor
// Der Vob wird (so vorhanden) aus der Vobliste entfernt.
// Ist diese danach leer wird auch die Vobliste zerstoert.
zCVobIdentifier::~zCVobIdentifier()
{	
	if (id!=zVOB_ID_UNDEFINED) 	
	{		
		if (vobList) // Vob aus der Vobliste entfernen
		{
			zCVob* vob = SearchVobByID(id);
			vobList->RemoveOrder(vob);

			if (vobList->IsEmpty()) // voblist bei Bedarf wieder loeschen
			{
				delete vobList;
				vobList=0;
			}
		}
	}
};



// Liefert die aktuelle VobID zurueck
zDWORD zCVobIdentifier::GetID()
{
	return id;
};




// Erzeuge eine eindeutige VobID
// Nach Sicherheitsprüfungen wird die gewuenschte ID gesetzt und der Vob 
// in die Vobliste eingefuegt.
zDWORD zCVobIdentifier::SetID(zCVob* vob, zTVobID new_id)
{
	zERR_ASSERTT(id==zVOB_ID_UNDEFINED,"The vob has already the distinct id "+zSTRING(id));
	zERR_ASSERTT(!SearchVobByID(id),"There is already a vob with the id "+zSTRING(id));

	id = new_id;

	// voblist bei Bedarf erzeugen
	if (!vobList)
	{
		vobList = zNEW(zCArraySort<zCVob*>());
		vobList->SetCompare(CompareVobID);
	}

	// vob in die Vobliste eintragen
	vobList->InsertSort(vob);

	return id;
};



// Erzeuge eine eindeutige VobID und uebergibt diese der
// Methode SetID().
zDWORD zCVobIdentifier::CreateDistinctID(zCVob* vob)
{	
	zERR_ASSERT(id==zVOB_ID_UNDEFINED);

	return SetID(vob, id_counter++);	
};
