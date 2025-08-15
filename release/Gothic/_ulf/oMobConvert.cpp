
#include "zVob.h"
#include "zModel.h"
#include "zArchiver.h"
#include "zAICamera.h"
#include "zObject.h"

#include "oMobInter.h"
#include "oGame.h"
#include "oWorld.h"

const int MAX_VISNAMES = 37; 

const zSTRING oldVisName[MAX_VISNAMES] = {
		
	"OC_COB_CHEST_CLOSED_SMALL.3DS",	
	"OC_COB_CRATE_CLOSED_SMALL.3DS",	
	"OC_LOB_BARREL_MOUNTED.3DS",	
	"OC_MOB_BARREL.3DS", 		
	"OC_MOB_BARREL2.3DS",		
	"OC_MOB_CHEST_CLOSED_BIG.3DS",	
	"OC_MOB_CHEST_LARGE.3DS",		
	"OC_MOB_CRATE_CLOSED_BIG.3DS",	
	"OC_MOB_CRATE_LARGE.3DS",		
	"OC_MOB_CRATE_LARGE_FISH.3DS",	
	"NC_COB_CHAIR.3DS",		
	"NC_COB_CHAIR2.3DS",		
	"NC_LOB_BED_SIMPLE.3DS",		
	"NC_LOB_BENCH_HALFTREE.3DS",	
	// 
	"OC_COB_CHAIR.3DS",		
	"OC_COB_CHAIR_BLOCK.3DS",		
	"OC_COB_CHAIR_ROUND.3DS",		
	"OC_COB_CHAIR_VARIATION.3DS",	
	"OC_COB_STOOL.3DS",		
	"OC_LOB_BED_SIMPLE.3DS",		
	"OC_LOB_BED_LUXUS.3DS",		
	"OC_LOB_BED_STRAW.3DS",		
	"OC_LOB_BENCH_BLOCKS.3DS",		
	"OC_LOB_BENCH_HALFTREE.3DS",	
	"OC_LOB_BENCH_STONES.3DS",		
	//
	"OC_MOB_COULDRON.3DS",
	// 
	"PC_COB_CHAIR.3DS",	
	"PC_COB_CHAIR2.3DS",	
	"PC_LOB_BED_GOOD.3DS",	
	"PC_LOB_BED_SIMPLE.3DS",	
	//
	"OC_LOB_GATECONTROL.3DS",
	//
	"OC_LOB_LEVER1.3DS",
	//
	"PC_LOB_SLEEPER1.3DS",
	"PC_LOB_SLEEPER2.3DS",
	"PC_LOB_SLEEPER3.3DS",
	"PC_LOB_SLEEPER4.3DS"
};

const zSTRING newVisName[MAX_VISNAMES] = {

	"CHESTSMALL_OC.MDS",	
	"CRATESMALL_OC.MDS",	
	"BARRELMOUNTED_OC.MDS",	
	"BARREL_1_OC.MDS",		
	"BARREL_2_OC.MDS",		
	"CHESTBIG_OC.MDS",		
	"CHESTLARGE_OC.MDS",	
	"CRATEBIG_OC.MDS",		
	"CRATELARGE_1_OC.MDS",	
	"CRATELARGE_2_OC.MDS",	
	"CHAIR_1_NC.MDS",		
	"CHAIR_2_NC.MDS",		
	"BEDLOW_NC.MDS",		
	"BENCH_1_NC.MDS",		
	//
	"CHAIR_1_OC.MDS",	
	"CHAIR_2_OC.MDS",	
	"CHAIR_3_OC.MDS",	
	"CHAIR_4_OC.MDS",	
	"CHAIR_5_OC.MDS",	
	"BEDHIGH_1_OC.MDS",
	"BEDHIGH_2_OC.MDS",
	"BEDLOW_OC.MDS",	
	"BENCH_1_OC.MDS",	
	"BENCH_2_OC.MDS",	
	"BENCH_3_OC.MDS",	
	//
	"COULDRON_OC.MDS",
	//
	"CHAIR_1_PC.MDS",	
	"CHAIR_2_PC.MDS",	
	"BEDHIGH_PC.MDS",	
	"BEDLOW_PC.MDS",	
	//
	"VWHEEL_1_OC.MDS",
	//
	"LEVER_1_OC.MDS",
	//
	"IDOL_SLEEPER1_PC.MDS",
	"IDOL_SLEEPER2_PC.MDS",
	"IDOL_SLEEPER3_PC.MDS",
	"IDOL_SLEEPER4_PC.MDS"
};

// *********************************************************************************
// Static : Konvertierung der alten Mobs ins neue Format
// *********************************************************************************
			
zCTree<zCVob>* ExchangeVobs (zCTree<zCVob>* node, zCVob* newvob)
// Tausche das im node enthaltene Mob gegen das newmob aus
{
	// Welt schnappen
	zCVob*		oldvob	= node	->GetData();
	zCWorld*	wld		= oldvob->GetHomeWorld();

	// Papa ermitteln
	zCTree<zCVob>* father = node->GetParent();

	// Kinder zählen
	zCList< zCTree<zCVob> > childnodes;
	zCTree< zCVob > *child = node->GetFirstChild();
	while (child) {
		// Childs aus Welt entfernen und merken
		wld -> RemoveVobSubtree(child);
		childnodes.Insert(child);
		child = child->GetNextChild();
	}
	
	// Transformation übernehmen
	zMATRIX4 trafo		= oldvob -> trafoObjToWorld;
	zBOOL	 coll		= oldvob -> GetCollDetDyn();
	zBOOL	 collstat	= oldvob -> GetCollDetStat();
	newvob -> SetCollDet		(FALSE);
	newvob -> SetPositionWorld	(0,0,0);	// Safety
	wld	   -> RemoveVob			(oldvob);	// Sollte ja reichen, weil keine Childs mehr.
	// So, jetzt den neuen Vob am Papa dranhängen
	node    = wld -> AddVobAsChild (newvob,father);
	newvob -> SetTrafoObjToWorld(trafo);
	newvob -> SetCollDetDyn		(TRUE);
	newvob -> SetCollDetStat	(TRUE);
	
	// Und alle Childs an den neuen Vob ran.
	zCList < zCTree<zCVob> > *cnode = childnodes.GetNextInList();
	while (cnode) {
		wld -> AddVobAsChild ( cnode->GetData()->GetData() ,newvob);
		cnode = cnode->GetNextInList();
	}

	// und altes Vob entfernen
	delete (oldvob);

	// Das wars, oder ?
	return node;
}

zCTree<zCVob>* ConvertzCVobToMob(zCTree <zCVob> *node)
{
	zCVob* oldmob = node->GetData();

	zerr.Warning("U:MOB:Converting zCVob to new oCMob : " + oldmob->GetVisual()->GetVisualName());

	oCMOB* newmob  = new oCMOB();
	newmob -> SetVisual			(oldmob->GetVisual());
	newmob -> SetShowVisual		(TRUE);
	node = ExchangeVobs(node,newmob);
	
	// den alten ganz löschen
	if (oCNpc::player) oCNpc::player->focus_vob = NULL;
	return node;
}

zCTree<zCVob>* ConvertOldMobToNewMob(zCTree<zCVob>* node)
{
	oCMob* oldmob = NULL;
	if (dynamic_cast<oCMob*>(node->GetData())) {
		oldmob = (oCMob*)node->GetData();
	}

	// *****************
	// Convert to Mover
	// *****************
	zSTRING visName = oldmob->GetVisual()->GetVisualName();
	if ((visName=="OC_LOB_GATE_BIG.3DS") || (visName=="OC_LOB_GATE_SMALL2.3DS")) {
		zerr.Warning("U:MOB:Converting old oCMob to zCMover : " + oldmob->GetVisual()->GetVisualName());
		zCMover* newvob = new zCMover();
		newvob -> SetVisual			(oldmob->GetVisual());
		newvob -> SetShowVisual		(TRUE);
		return ExchangeVobs			(node,newvob);		
	}

	oCMOB* newmob = (oCMOB*)zCObject::CreateNewInstance("oCMOB");

	if (oldmob && newmob) {
		
		zerr.Message("U:MOB:Converting old oCMob to new oCMOB : " + oldmob->GetVisual()->GetVisualName());

		// Was ist mit dem MeshNamen ?
		newmob -> SetVisual			(oldmob->GetVisual());
		newmob -> SetShowVisual		(TRUE);

		// Attribute übernehmen
		newmob -> name				= oldmob -> name;
		newmob -> hitp				= oldmob -> hp_max;
		newmob -> moveable			= oldmob -> HasFlag(OBJ_FLAG_MOVEABLE);
		newmob -> takeable			= oldmob -> HasFlag(OBJ_FLAG_TAKEABLE);
		newmob -> sndMat			= (oTSndMaterial) oldmob -> GetSoundMaterial();
		newmob -> visualDestroyed	= oldmob -> destroyed_mesh;
		newmob -> SetOwner			( oldmob -> owner , oldmob -> owner_guild);
		newmob -> isDestroyed		= oldmob -> destroyed;
		newmob -> SetCollDetDyn		( TRUE );
		newmob -> SetCollDetStat	( TRUE );

		// Lass uns tauschen...
		node = ExchangeVobs(node,newmob);
		
		// den alten ganz löschen
		if (oCNpc::player) oCNpc::player->focus_vob = NULL;
	}
	return node;
}

zBOOL FindVisName(zSTRING& visName)
{
	if (visName.IsEmpty()) return FALSE;
	if (visName.Search("DEFECT")>=0) return FALSE;
	// Sonderwünsche der Art Leute, immer gern genommen... Grr !!!!!
	for (int i=0; i<MAX_VISNAMES; i++) {
		if (visName==oldVisName[i]) {
			visName =newVisName[i];
			return TRUE;
		}
	}
	return FALSE;
}

void CopyValues (oCMOB* newmob, oCMOB* oldmob) 
{
	// Attribute übernehmen
	newmob -> name				= oldmob -> name;
	newmob -> hitp				= oldmob -> hitp;
	newmob -> moveable			= oldmob -> moveable;
	newmob -> takeable			= oldmob -> takeable;
	newmob -> sndMat			= oldmob -> sndMat;
	newmob -> visualDestroyed	= oldmob -> visualDestroyed;
	newmob -> SetOwner			( oldmob -> owner , oldmob -> ownerGuild);
	newmob -> isDestroyed		= oldmob -> isDestroyed;
	newmob -> SetCollDetDyn		( TRUE  );
	newmob -> SetCollDetStat	( TRUE );
}

oCMOB* ConvertMobTo(oCMOB* oldmob, const zSTRING& targetClass)
{
	int p;
	zSTRING mess;
	oCMOB* newmob = (oCMOB*)zCObject::CreateNewInstance(targetClass);
	if (newmob) {

		CopyValues(newmob, oldmob);
		zSTRING visName = mess = oldmob->GetVisual()->GetVisualName();
		if (dynamic_cast<oCMobInter*>(newmob)) {
			if ((p = visName.Search(".3DS")) >= 0) {
				// Wirf einen Blick in die Tabelle, oder konvertiere Stumpf
				if (!FindVisName(visName)) visName.Overwrite(p,".MDS");
			};
		}
		zerr.Message("U:MOB:Converting "+oldmob->GetClassName_()+" to "+newmob->GetClassName_()+" ("+mess+" to "+visName+")");
		newmob -> zCVob::SetVisual(visName);
		
	}
	return newmob;
};

/*
void Replace (oCMOB* newmob, oCMOB* oldmob)
{
	// Position setzen
	zMATRIX4 trafo	= oldmob -> trafoObjToWorld;
	zCWorld* wld	= oldmob -> GetHomeWorld();
	zBOOL coll		= oldmob -> GetCollDetDyn();
	zBOOL collstat	= oldmob -> GetCollDetStat();
	newmob -> SetCollDet		(FALSE);
	newmob -> SetPositionWorld	(0,0,0);	// Safety
	wld	   -> RemoveVob			(oldmob);
	wld	   -> AddVob			(newmob);
	newmob -> SetTrafoObjToWorld(trafo);
	newmob -> SetCollDetDyn		(coll);
	newmob -> SetCollDetDyn		(collstat);
	// und altes Mob entfernen
	delete (oldmob);
}
*/

zCTree<zCVob>* ConvertVobTo (zCTree <zCVob>* node)
{
	zCVob* vob = node->GetData();

	zSTRING name,old,className;
	
	// -1. Die Hides löschen
	if ((vob->GetVisual()) && (vob->GetVisual()->GetVisualName()=="OC_LOB_HIDE.3DS")) {
		zerr.Warning("U:MOB:Deleting "+vob->GetVisual()->GetVisualName());
		delete(vob);
		return NULL;
	}

	// 0. ein reiner zCVob ?
	if (vob->GetClassName_()=="zCVob") {
		// erstmal einen oCMob erzeugen
		if (vob->GetVisual()) old = name = vob->GetVisual()->GetVisualName();
		if (FindVisName(name)) {
			// Jawoll, relevant und Interactive Vob
			node = ConvertzCVobToMob(node);
		}
	}

	vob = node->GetData();
	// 1. Alter Vob ?
	if (dynamic_cast<oCMob*>(vob)) {
		// ***************************************
		// Alter Mob -> neuer Mob
		// ***************************************
		// erstmal zum normalen oCMob konvertieren
		node = ConvertOldMobToNewMob (node);
	} 

	vob = node->GetData();
	// 2. Neuer Mob -> noch weiter konvertieren ?
	if (dynamic_cast<oCMOB*>(vob)) {
		if (vob->GetVisual()) name = vob->GetVisual()->GetVisualName();
		
		// Nix defektes weiter konvertieren
		if (name.Search("DEFECT")>=0) return node;

		// *** oCMobBed ***			
		if (name.Search("BED")>=0) {
			if (!dynamic_cast<oCMobBed*>(vob))			className	= "oCMobBed";
		}

		// *** oCMobContainer ***
		if ((name.Search("CHEST")>=0) || (name.Search("CRATE")>=0)) {
			if (!dynamic_cast<oCMobContainer*>(vob))	className	= "oCMobContainer";
		} else
		
		// *** oCMobLever ***
		if (name.Search("LEVER")>=0) {
			if (!dynamic_cast<oCMobSwitch*>(vob))		className	= "oCMobSwitch";
		} else
		
		// *** oCMobLadder ***
		if (name.Search("LADDER")>=0) {
			if (!dynamic_cast<oCMobLadder*>(vob))		className	= "oCMobLadder";
		} else 

		// *** oCMobWheel ***
		if ((name.Search("WHEEL")>=0) || (name.Search("CONTROL")>=0)) {
			if (!dynamic_cast<oCMobWheel*>(vob))		className	= "oCMobWheel";
		} else 
		
		// *** Interact ***
		if ((name.Search("CHAIR")>=0)	|| (name.Search("BENCH")>=0)	|| (name.Search("STOOL")>=0)	||
			(name.Search("BARREL")>=0)	|| (name.Search("SLEEPER")>=0)	|| (name.Search("CAULDRON")>=0) || 
			(name.Search("GATECONTROL")>=0)) {
			
			if (!dynamic_cast<oCMobInter*>(vob))		className	= "oCMobInter";
		}

		if (!className.IsEmpty()) {
			oCMOB* newmob = ConvertMobTo ((oCMOB*)vob, className);
			node = ExchangeVobs (node,newmob);			
		}

	}
	return node;
}

void ConvertVobTree(zCTree <zCVob>* node)
{
	if (node == NULL) return;

	ConvertVobTree ( node->GetNextChild() );					

	node = ConvertVobTo (node);
	if (!node) return;

	ConvertVobTree ( node->GetFirstChild() );

}

void ConvertAllMobsInWorld()
{
	ConvertVobTree ( ogame->GetWorld()->globalVobTree.GetFirstChild() );
}
