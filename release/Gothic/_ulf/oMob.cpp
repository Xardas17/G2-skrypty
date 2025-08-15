
/****************************************************************
*																*
* Phoenix Object-System	                						*
* Projekt       : Phoenix										*
* Datei         : oMob.h										*
* Autor         : Ulfi			   								*
* Version       : 0.01											*
* last modified : 26.09.97										*
* erstellt      : 26.09.97										*
*																*
*****************************************************************
- bekannte Bugs:
*****************************************************************
- moegliche Optimierungen:
*****************************************************************
- noch fehlende Funktionalitaeten:
*****************************************************************
- Kommentare:
****************************************************************/

#include "zConfig.h"
#include "zParticle.h"
#include "zSoundMan.h"
#include "zArchiver.h"

#include "oWorld.h"
#include "oGame.h"

// *****************************************
//				Statics
// *****************************************

oCWorld *oCMob :: world_3d = NULL;

zList <oCMob> oCMob :: MobList;

// *****************************************
//				Constructor
// *****************************************

oCMob :: oCMob ( )
{
	memset((zBYTE *)this + sizeof(zCVob),0,sizeof(oCMob)-sizeof(zCVob));
	SetVobType (zVOB_TYPE_MOB);
	SetCollType(zVOB_COLL_TYPE_BIG_OBJECT);
	instanz = -1;

	Init();
};

oCMob :: oCMob ( int instance )
{
	zSTRING f;
	memset((zBYTE *)this + sizeof(zCVob),0,sizeof(oCMob)-sizeof(zCVob));
	
	SetVobType (zVOB_TYPE_MOB);
	SetCollType(zVOB_COLL_TYPE_BIG_OBJECT);

	instanz = instance;
	InitByScript (instanz);

//	MobList.Insert(this);

	Init();
}

oCMob :: oCMob ( zSTRING instance )
{
	zSTRING f;
	memset((zBYTE *)this + sizeof(zCVob),0,sizeof(oCMob)-sizeof(zCVob));
	
	SetVobType (zVOB_TYPE_MOB);
	SetCollType(zVOB_COLL_TYPE_BIG_OBJECT);
	instanz = parser.GetIndex(instance);
	InitByScript(instanz);

	//MobList.Insert(this);
	Init();
}

void oCMob :: InitByScript ( int nr )
{
	// Check Class Size
	static int classindex = -1;
	if (classindex<0) {
		classindex = parser.GetIndex("C_MOB");
		parser.CheckClassSize (classindex,(int)&spotted - (int)&id);
	}

	instanz = nr;
	parser.CreateInstance ( nr, this );
	SetVobType(zVOB_TYPE_MOB);

	// Mesh init
	mesh.Upper();
	if (mesh.Search(".3DS")>0) {
		SetVisual(mesh);
	} else {
		SetVisual(zcfg.GetString(SUBDIR_INTERN) + "vobbox.3ds");
	}
}

void oCMob::Init()
{
	ogame->GetWorld()->InsertVobInList(this);
};

oCMob :: ~oCMob ()
{
	MobList.Remove(this);
}

BOOL oCMob :: HasFlag ( int f )
{
	return (flags & f)>0;
}

zSTRING oCMob :: GetName ( )
{
	return name;
};

zBOOL oCMob :: IsOwned (int instance, int guild)
{
	return (IsOwnedByNpc(instance) || IsOwnedByGuild(guild));	
}

zBOOL oCMob :: IsOwnedByNpc (int instance)
{
	return ((instance>0) && (instance==owner));
}

zBOOL oCMob :: IsOwnedByGuild (int guild)
{
	return ((guild>0) && (owner_guild==guild));
}

BOOL oCMob :: IA_ObjContainer (int key)
{
/*
	if ((key==KEYSC_MLEFT) || (key==KEYSC_MRIGHT)) {
		// Ermittle Mausposition
		int mx,my;
		screen->Getmouse(mx,my);
		// Check if it is a Container 
		oCItemContainer *ele = oCItemContainer :: contlist.wurzel;
		while (ele!=NULL) {
			if (ele->inhalt->IsIn(mx,my)) break;
			ele = ele->next;
		}

		if (ele == NULL) return FALSE;

		if (key==KEYSC_MLEFT) {
			// Zeige Item Daten an
			ele->ShowItemName();
			return TRUE;
		} else if (key==KEYSC_MRIGHT) {
			// Benutzen des Items
			int mx,my;
			ele->inhalt->Getmouse(mx,my);
			oCItem *item = ele->GetItem(mx,my);
			// Benutze das Item
			if (item!=NULL) {
				// Attribute neu zeigen
				ele    -> Remove(item);
				oCNpc :: player -> PutInInventory(item);
				if (oCNpc :: player -> inv_cont != NULL) 
					oCNpc :: player -> inv_cont -> Redraw_Inventory();
				ele    -> Redraw_Container();
			}
			return TRUE;
		}
	}
*/
	return FALSE;
}

void oCMob :: OnSpotted ( )
{
	spotted++;
	if (on_spotted>0) parser.CallFunc(on_spotted,spotted);
}

int	 oCMob :: AddManipulation()	
{ 
	const int MANIP_TIME = 60;		// 60 Minuten _SPIELZEIT_ !!!!!
	// Looki looki -> wann letzte Manipulation
	if (c_manipulation>0) {
		int delta = Wld_Timer -> GetPassedTime(last_manipulation);
		if (delta>60) {	
			// Ein Stunde ist vergangen -> Counter auf 0 
			c_manipulation = 0;
		}
	}
	last_manipulation = Wld_Timer -> GetFullTime();
	c_manipulation++; 
	return c_manipulation; 
};

// *****************************************
//			   Item Functions
// *****************************************
	
void oCMob :: InsertItem ( oCItem *item )
{
//	contains.Insert ( item );
};

void oCMob :: RemoveItem ( oCItem *item )
{
//	contains.Remove ( item );
};

oCItem *oCMob :: RemoveItem ( int nr )
{
//	oCItem *item = contains.Get ( nr );
//	contains.Remove ( item );
//	return item;
	return NULL;
}

zSTRING oCMob :: GetStatus  ( )
{
	switch ( status ) {
		case OBJ_STATUS_CLOSED : return ("geschlossen");
		case OBJ_STATUS_OPEN   : return ("geöffnet");
		case OBJ_STATUS_LOCKED : return ("verschlossen");
	}
	return ("?");
}

zSTRING oCMob :: DoAction ( )
{
	OnAction();
/*	if ((flags & OBJ_FLAG_CONTAINER)>0) {
		if (status == OBJ_STATUS_CLOSED) {
			status = OBJ_STATUS_OPEN;
			return (" oeffnen ");
		} else if (status == OBJ_STATUS_OPEN) {
			status = OBJ_STATUS_CLOSED;
			delete (cont);
			return (" schliessen ");
		} else if (status == OBJ_STATUS_LOCKED) {
			oCItem *key = oCNpc :: player->HasKey( key_hole );
			if (Unlock(key)) {
				if (key!=NULL) 
					return ("mit passendem Schlüssel aufgeschlossen");
				else
					return ("Schloß geknackt");
			}
			return ("oeffnen nicht moeglich -> Truhe ist abgeschlossen");
		}
	} else if (flags & OBJ_FLAG_SWITCH) {
		status = !status;
		return("Schalter betätigt.\n");
	}*/
	return ("?");
}

BOOL oCMob :: IsOpen	( )
{
	return (status==OBJ_STATUS_OPEN);
}

BOOL oCMob :: Unlock ( oCItem *key )
{
/*	if ((key!=NULL) && (key_hole == key->keyhole)) {
		// richtiger Schlüssel - paßt
		key -> Identify();
		switch ( status ) {
			case OBJ_STATUS_LOCKED : status = OBJ_STATUS_CLOSED; break;
			case OBJ_STATUS_OPEN   : status = OBJ_STATUS_LOCKED; break;
			case OBJ_STATUS_CLOSED : status = OBJ_STATUS_LOCKED; break;
		}
		return TRUE;
	} else if (oCNpc :: player->HasTalent(NPC_TAL_PICKLOCK)) {
		// Versuche es mit dem Öffnungsboni für andere Schlösser
		int w = oCNpc :: player->GetAttribute(NPC_ATR_THIEVERY) + key -> keyhole_bonus;
		if (w>key_level) {
			status = OBJ_STATUS_CLOSED;
			return TRUE;
		};
		return FALSE;
	}*/
	return FALSE;
}

void oCMob :: OnAction()
{
	action++;
	if (on_action>0) {
		parser.SetInstance(zSTRING("TARGET"),oCNpc :: player);
		parser.SetInstance(zSTRING("OBJECT"),this);
		parser.CallFunc(on_action,action);
	}
}

/*void oCMob :: Move (float xv,float yv, float zv)
{
	MoveLocal(xv,yv,zv);
}
*/
BOOL oCMob :: Carry (zCVob *vob)
{
	// Temp
	flags = flags | OBJ_FLAG_TAKEABLE;
	// Temp 
	if ((flags & OBJ_FLAG_TAKEABLE) == OBJ_FLAG_TAKEABLE) {
		// and Insert as Child of player
//		float x1,y1,z1,x2,y2,z2,relx,rely,relz;
//		oCNpc :: player -> GetPositionWorld (x1,y1,z1);
//		GetPositionWorld(x1,y1,z1);
//		GetPositionWorld(x2,y2,z2);
//		relx = x2 - x1;
//		rely = y2 - y1;
//		relz = z2 - z1;
//		RemoveFrom3D();
//		PutIn3D(relx,rely,relz);
//		PutIn3D(20,0,30);
		world_3d -> MoveVobSubtreeTo ( this, oCNpc :: player );
//		SetPosition(x1+relx,y1+rely,z1+relz);

//		GetPositionLocal (x1,y1,z1);
//		GetPositionWorld (x2,y2,z2);
		
		
		//		SetPosition(relx,rely,relz);
		//		SetPosition(relx,rely,relz);		
/*		
		zCTree <zCVob> *tree = world_3d -> globalVobTree.Search ( vob );
		if (tree != NULL) {
//			float x,y,z;
			//vob -> GetPosition(x,y,z);
			//PutIn3D(x,y,z);
//			trafo = vob->trafo;
			tree->AddChild (this);
			RotateWorld (0,1,0,-45);
//			MoveLocal(0,0,0);
*/
		return TRUE;
	}
	return FALSE;
}

BOOL oCMob :: Drop ( zCVob *vob )
{
/*	float x1,y1,z1;
	float x2,y2,z2;
*/
	world_3d -> MoveVobSubtreeToWorldSpace ( this );
	/*
	RemoveFrom3D();
	vob -> GetPosition(x1,y1,z1);
	GetPosition (x2,y2,z2);
	PutIn3D(x1+x2,y1+y2,z1+z2);	
*/
	return TRUE;
};	

void oCMob :: Hit ( int dam )
{
	if (flags & OBJ_FLAG_INVINCIBLE) return;
	if (dam > hp) Destroy();
}

zSTRING oCMob :: GetStatusHP ()
{
	int nr;
	zSTRING s;
	int z = ( hp * 100 / hp_max ) - 1;

	if (z>=100) nr = 9; else
	if (z<=0)   nr = 0; else
				nr = z / 10;
	s = parser.GetText ( oCText :: TXT_ATR_HP, nr );

	s += "(" + zSTRING(hp) + ")";
	return s;
}

void oCMob :: GetHitpoints ( int &hp1, int &hp2 )
{
	hp1 = hp;
	hp2 = hp_max;
}

void oCMob :: Destroy()
// Kaputtmesh und Partikeleffekt
{
	if (!destroyed) {
		// Destruction - Sound 
		zsndMan->StartDestructionSound (this,GetSoundMaterial());
		// Partikeleffect
		zCParticleFX	*partFX	= new zCParticleFX;
		zCVob			*vobFX	= new zCVob;
		vobFX	->SetCollDet				(FALSE);
		vobFX	->SetPositionWorld			(GetPositionWorld());  
		vobFX	->SetVisual					(partFX);
		partFX	->SetEmitter				("PFX_MOBDESTROY");
		partFX  ->emitter->shpMesh_S		= mesh;
		partFX  ->emitter->UpdateInternals	();
		partFX  ->CreateParticles			();
		GetHomeWorld()->AddVob				(vobFX);	
		// und Mesh ersetzen
		destroyed = TRUE;
		if (destroyed_mesh.Length()>0) {
			SetVisual(destroyed_mesh);	
			UpdateVisualDependencies();
		} else {
			RemoveFrom3D();
			delete this;
		}
	}
}

// *****************************************
//				3D Functions
// *****************************************

void oCMob :: PutIn3D (zVEC3& pos,zCVob *parent)
{
	PutIn3D(pos[VX],pos[VY],pos[VZ]);
}

void oCMob :: PutIn3D (float x,float y,float z,zCVob *parent)
{
	SetPositionWorld(0,0,0);
	if (parent==NULL) 
		world_3d -> AddVob( this );
	else 
		world_3d -> AddVobAsChild( this,parent );
	SetCollDet(FALSE);
	SetPositionWorld(x,y,z);
	MobList.Insert(this);	

	SetCollDet			(TRUE);
	SetSleeping			(FALSE);
	SetPhysicsEnabled	(TRUE);
};

BOOL oCMob :: RemoveFrom3D ()
{
	world_3d -> RemoveVob (this);	
	MobList.Remove(this);
	return TRUE;
}

// *********************************
//		Save / Load Functions
// *********************************

zSTRING oCMob :: GetInstanceName ()
{
	int typ,ele;
	return parser.GetSymbolInfo(instanz,typ,ele);
}

void oCMob :: RenderMob ( zCView *viewitem )
{
	zCCamera i_cam;
	zCWorld  i_wld;
	zCVob	 i_vob;

	SetPositionWorld ( 0,0,0 );
	i_wld.AddVob( this  );

	zTBBox3D box3d	= GetBBox3DWorld();
	//zVALUE volume	= box3d.GetVolume();

	float x,y,z;

	x = (box3d.maxs[0] + box3d.mins[0]) / 2;
	y = (box3d.maxs[1] + box3d.mins[1]) / 2;
	z = (box3d.maxs[2] + box3d.mins[2]) / 2;

	// Groesste Distanz ermitteln
	float dx,dy,dz;
	dx = box3d.maxs[0] - box3d.mins[0];
	dy = box3d.maxs[1] - box3d.mins[1];
	dz = box3d.maxs[2] - box3d.mins[2];
	if (dx<dy) dx = dy;
	if (dz<dy) dx = dz;

	i_cam.SetRenderTarget(viewitem);
	i_vob.SetPosition (x,y,-dx);			
	i_cam.SetVob(&i_vob);

	i_cam.SetFarClipZ (zVALUE_MAX);

//	i_wld.usingBspPortals = 0;
	i_wld.SetDrawVobBBox3D(FALSE);
//	i_cam.drawMode	= zCAM_DRAW_TEX_PER;
//	i_cam.shadeMode = zSHADE_GOURAUD;

	// Insert it in 3D
	i_wld.Render(i_cam);

	// Rewove from 3D
	i_wld.RemoveVob( this );
}

// *************************************
// Archive / Unarchive
// *************************************

void oCMob :: Archive (zCArchiver &arc)
{
	zCVob :: Archive(arc);

	// Write Instance Name
	zCPar_Symbol* sym = parser.GetSymbol(GetInstance());
	zSTRING s;
	if (!sym) {
		zerr.Warning("U:MOB:Save:Instance not found : "+GetInstanceName());
		s = "(Error)";
	} else
		s = sym->name;
	
	arc.WriteString("mobInstance",s);
};

void oCMob :: Unarchive	(zCArchiver &arc)
{
	zCVob :: Unarchive(arc);

	// Get Instance Name
	zSTRING name	= arc.ReadString	("mobInstance");
	int		index	= parser.GetIndex	(name);
	if (index >= 0) {
		InitByScript	(index);
		MobList.Insert	(this);				
	} else {
		zerr.Warning("U:MOB:Load:Instance not found : " + name);
	};
};

zCLASS_DEFINITION( oCMob , oCVob	, 0)
