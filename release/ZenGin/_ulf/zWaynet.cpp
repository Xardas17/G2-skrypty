/******************************************************************************** 
 
     $Workfile:: zWaynet.cpp          $                $Date:: 15.03.01 2:17    $
     $Revision:: 38                   $             $Modtime:: 14.03.01 20:36   $
       $Author:: Hildebrandt                                                    $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zWaynet.cpp $
 * 
 * 38    15.03.01 2:17 Hildebrandt
 * 
 * 37    25.01.01 13:14 Moos
 * 
 * 36    18.01.01 2:00 Wohlers
 * 
 * 35    16.01.01 14:18 Wohlers
 * 
 * 34    9.01.01 22:02 Wohlers
 * 
 * 33    20.12.00 19:31 Hildebrandt
 * 
 * 32    20.12.00 17:13 Moos
 * 
 * 31    18.12.00 20:22 Wohlers
 * 
 * 30    14.12.00 20:45 Wohlers
 * 
 * 29    22.11.00 18:18 Wohlers
 * 
 * 28    16.11.00 19:23 Wohlers
 * 
 * 27    16.11.00 15:13 Speckels
 * 
 * 26    16.11.00 14:59 Speckels
 * 
 * 25    8.11.00 14:59 Speckels
 * 
 * 24    2.11.00 16:04 Speckels
 * 
 * 23    20.10.00 16:49 Wohlers
 * 
 * 22    19.10.00 21:49 Wohlers
 * 
 * 21    19.10.00 19:38 Speckels
 * 
 * 19    18.10.00 17:02 Wohlers
 * 
 * 18    12.09.00 20:36 Wohlers
 * 
 * 17    12.09.00 19:13 Wohlers
 * 
 * 16    12.09.00 19:11 Wohlers
 * 
 * 15    11.09.00 20:52 Speckels
 * 
 * 14    6.09.00 20:19 Rueve
 * warning cleanup
 * 
 * 13    28.08.00 15:42 Rueve
 * zRndGlide.h ging nach Hause
 * 
 * 12    17.08.00 16:23 Wohlers
 * 
 * 11    2.08.00 14:25 Wohlers
 * 
 * 10    1.08.00 15:14 Wohlers
 * 
 * 9     21.07.00 15:35 Wohlers
 * 
 * 8     21.07.00 14:43 Wohlers
 * 
 * 7     14.06.00 18:14 Wohlers
 * Gothic 0.85a
 * 
 * 6     5.06.00 22:37 Wohlers
 * uSrc 05.06.00
 * 
 * 5     22.05.00 18:46 Wohlers
 * Gothic 0.82
 * 
 * 5     10.05.00 23:28 Wohlers
 * Gothic 0.81a
 * 
 * 4     8.05.00 23:10 Edenfeld
 * 
 * 4     8.05.00 15:02 Wohlers
 * Waynet CheckConsistency
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 17    30.03.00 20:36 Wohlers
 * Bugfixes ( Wegnetz, TAs etc. )
 * 
 * 16    29.03.00 15:32 Wohlers
 * Various Bugfixes ( Waynet, Klettern )
 * 
 * 14    16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 13    23.02.00 3:47 Wohlers
 * Fixes
 * 
 * 12    22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 11    6.02.00 18:42 Wohlers
 * Various Fixes
 * 
 * 10    3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 9     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 8     20.12.99 17:45 Wohlers
 * uSrc V0.70
 * AI_UseItem / AniComb TakeItem etc...
 * 
 * 7     9.12.99 22:33 Wohlers
 * 
 * 6     7.12.99 22:09 Wohlers
 * Trade Module
 * AssessGivenItem 
 * 
 * 5     6.12.99 16:06 Wohlers
 * Waynet Erweiterungen
 * 
 * 4     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "zWaynet.h"
#include "zoption.h"
#include "zWorld.h"
#include "zArchiver.h"
#include "zView.h"
#include "zTools.h"

#pragma warning ( disable:4244 )

// ********* Waypoint - Vob **********

zCVobWaypoint :: zCVobWaypoint ()
{	
	SetVobType(zVOB_TYPE_WAYPOINT);
}

zCVobWaypoint :: ~zCVobWaypoint()
{
}

// ********* WayNet **********

zCWayNet :: zCWayNet ( )
{
	world		= NULL;
	routeCtr	= 0;
	openList.SetCompare(SortOpenList);
}

zCWayNet :: zCWayNet ( zCWorld *w3d )
{
	world		= w3d;
	routeCtr	= 0;
	openList.SetCompare(SortOpenList);
	wplist	.SetCompare(SortWpList);
}

zCWayNet :: ~zCWayNet ()
{
	wplist	.DeleteListDatas();
	waylist	.DeleteListDatas();
	
	// delete all Waypoints + Ways
/*	zCListSort <zCWaypoint>* wnode = wplist.GetNextInList();
	zCWaypoint* wp = NULL;

	while (wnode) {
		wp		= wnode->GetData();
		wnode	= wnode->GetNextInList();
		DeleteWaypoint (wp);
	}
*/
	world	= NULL;
}

zCWaypoint* zCWayNet :: HasWaypoint ( float x, float y, float z )
{
	zCWaypoint* wp;
	zCListSort <zCWaypoint>* wnode = wplist.GetNextInList();
	while (wnode) {
		wp			= wnode->GetData();	
		wnode		= wnode->GetNextInList();
		zVEC3 pos	= wp -> GetPositionWorld ();
		if ((pos[VX]==x) && (pos[VY]==y) && (pos[VZ]==z)) return wp;
	}
	return NULL;
}


zBOOL zCWayNet :: HasWaypoint ( zCWaypoint *w )
{
	zCListSort <zCWaypoint>* wnode = wplist.GetNextInList();
	while (wnode) {
		if (wnode->GetData()==w) return TRUE;
		wnode = wnode->GetNextInList();
	}
	return FALSE;
}

zCWaypoint* zCWayNet :: HasWaypoint ( zVEC3& pos )
{
	zCListSort <zCWaypoint>* wnode = wplist.GetNextInList();
	while (wnode) {
		if (wnode->GetData()->GetPositionWorld()==pos) return wnode->GetData();
		wnode = wnode->GetNextInList();
	}
	return FALSE;
}

zCWaypoint* zCWayNet :: InsertWaypoint ( float x,float y,float z )
{
	zCWaypoint *way = HasWaypoint(x,y,z);
	// Already in List ?
	if ( way ) 
		return way;

	zCWaypoint *wp = zfactory->CreateWaypoint();
	wp->Init(x,y,z);
	InsertWaypoint (wp);
	return wp;
}

void zCWayNet :: InsertWaypoint ( zCWaypoint *wp )
{
	if (!HasWaypoint(wp)) {
		wplist.InsertSort(wp);
	}
}

void zCWayNet :: InsertWaypoint	( zCWaypoint *wp1, zCWaypoint *wp2, zCWaypoint *wp3 )
// Sonderfall : 
// wp2 wird zwischen die beiden Waypoints wp1 und wp2 gesetzt
// Gibt es noch keine Verbindung dieser Waypoints, wird diese hergestellt
// Sind einige Waypoints noch nicht im Netz, werden diese eingefuegt
{
	// Nix doppelt !
	if ((wp1==wp2) || (wp2==wp3) || (wp1==wp3)) return;
	// Alle einfuegen
	if (!HasWaypoint(wp1)) InsertWaypoint(wp1);
	if (!HasWaypoint(wp2)) InsertWaypoint(wp2);
	if (!HasWaypoint(wp3)) InsertWaypoint(wp3);
	// Evt.Vorhandene Strecke aufloesen
	DeleteWay(wp1,wp3);
	// Und zwei neue Strecken einfuegen
	CreateWay(wp1,wp2);
	CreateWay(wp2,wp3);
}

void zCWayNet :: DeleteWaypoint ( zCWaypoint *wp )
{
	if (HasWaypoint(wp)) {
		// remove all Routes with this Waypoint from globallist
		zCWay* way;
		zCList<zCWay>* waynode = waylist.GetNextInList();
		while (waynode) {
			way		= waynode->GetData();
			waynode = waynode->GetNextInList();			
			if ((way->GetLeftWaypoint()==wp) || (way->GetRightWaypoint()==wp)) {
				waylist.Remove(way);
				way->Free();
				delete way;
			}
		}
		// remove Waypoint from list -> will delete the "ways"
		wplist.Remove(wp);
		wp->Free();
		zRELEASE(wp);
	}
}

void zCWayNet :: CreateWay ( zCWaypoint *w1, zCWaypoint *w2 )
{
	if (w1==w2) return;
	// Check, ob beide Waypoints im Netz
	if (!HasWaypoint(w1)) InsertWaypoint(w1);
	if (!HasWaypoint(w2)) InsertWaypoint(w2);
	// Check, ob Verbindung bereits besteht 
	if (!w1->HasWay(w2)) {
		// Verbindung herstellen
		zCWay* way = zfactory->CreateWay();
		way -> Init (w1,w2);
		waylist.Insert ( way );
	}
}

void zCWayNet :: DeleteWay ( zCWaypoint *w1, zCWaypoint *w2 )
{
	zCWay *way = w1 -> HasWay(w2);
	if (way!=NULL) {
		w1 -> RemoveWay ( way );
		w2 -> RemoveWay ( way );
		waylist.Remove	( way );
		way->Free();
		delete (way);
	}
}

zCWaypoint* zCCFASTCALL zCWayNet :: GetNearestWaypoint ( const zVEC3 &pos2 )
{
	zREAL dist;
	zREAL maxdist		= zREAL_MAX;		// 0xFFFFFFFF;
	
	zCListSort <zCWaypoint>* wpnode = wplist.GetNextInList();
	zCWaypoint *wp, *nwp = NULL;
	while (wpnode) 
	{
		wp				= wpnode->GetData();
		wpnode			= wpnode->GetNextInList();

		const zVEC3& pos= wp->GetPositionWorld ();
		dist			= zAbsApprox(pos[VX]-pos2[VX]) + zAbsApprox(pos[VY]-pos2[VY]) + zAbsApprox(pos[VZ]-pos2[VZ]);
		if (dist < maxdist) 
		{
			nwp		= wp;
			maxdist = dist;
		}
	}

	return nwp;
}

zCWaypoint* zCWayNet :: GetSecNearestWaypoint ( zVEC3& pos2 )
{
	zVEC3 pos;
	zDWORD dist = 0, max1dist = 0xFFFFFFFF, max2dist = 0xFFFFFFFF;
	
	zCWaypoint *wp, *max1wp	= NULL, *max2wp = NULL;
	zCListSort <zCWaypoint>* wpnode = wplist.GetNextInList();

	while (wpnode) {
		wp		= wpnode->GetData();
		wpnode	= wpnode->GetNextInList();
		
		pos		= wp->GetPositionWorld ();
		dist	= abs(pos[VX]-pos2[VX]) + abs(pos[VY]-pos2[VY]) + abs(pos[VZ]-pos2[VZ]);
		
		// Maximale Distanz ?
		if (dist < max1dist) {
			// Anderen Nachziehen
			max2wp	= max1wp;
			max2dist= max1dist;
			// Und den am nahesten neu setzen
			max1wp	= wp;
			max1dist= dist;
		} else if (dist < max2dist) {
			// neuer 2.weitesten WP gefunden
			max2wp	= wp;
			max2dist= dist;			
		}
	}
	return max2wp;
}

void zCWayNet :: CorrectHeight()
{
	zCListSort <zCWaypoint>* wpnode = wplist.GetNextInList();
	zCWaypoint *wp;

	while (wpnode) {
		wp		= wpnode->GetData();
		wpnode	= wpnode->GetNextInList();
		wp	   -> CorrectHeight(world);
	}
}

void zCWayNet :: Draw ( zCCamera *camera )
{
	// Zuerst die Strecken
	zCList <zCWay>* waynode = waylist.GetNextInList();
	zCWay *way;
	camera->Activate();
	while (waynode) {
		way		= waynode->GetData();
		waynode = waynode->GetNextInList();
		way    -> Draw( camera );
	}
}

/*	------------------------------------------------------------------
	void zCWayNet :: UpdateVobDependencies()
	20.12.00	[HILDEBRANDT]	
				unbenutzte Variable wld entfernt
	------------------------------------------------------------------ */

void zCWayNet :: UpdateVobDependencies()
// Die WaypointVobs werden aus der Welt entfernt
// Alle Verweise auf dise Vobs werden (und müssen) gelöscht werden
{

	zERR_MESSAGE(5,zERR_BEGIN,"U: WAYNET: Updating VobDependencies...");

	// Zuerst einzelne Waypoints oder Waypoint mit Eigenschaften
	zCListSort <zCWaypoint>* wpnode = wplist.GetNextInList();
	zCWaypoint*	wp; 
	while (wpnode) {
		wp			= wpnode->GetData();
		wpnode		= wpnode->GetNextInList();
		// Werte und Ausrichtung neu uebernehmen...
		wp->UpdatePositionWorld();
	}

	zERR_MESSAGE(5,zERR_END,"");
}

void zCWayNet :: ClearVobDependencies()
// Die WaypointVobs werden aus der Welt entfernt
// Alle Verweise auf dise Vobs werden (und müssen) gelöscht werden
{

	zERR_MESSAGE(5,zERR_BEGIN,"U: WAYNET: Clearing VobDependencies...");

	// Zuerst einzelne Waypoints oder Waypoint mit Eigenschaften
	zCListSort <zCWaypoint>* wpnode = wplist.GetNextInList();
	zCWorld*	wld = NULL;
	zCWaypoint*	wp;
	while (wpnode) {
		wp			= wpnode->GetData();
		wpnode		= wpnode->GetNextInList();
		if (wp->wpvob) {
			wld = wp->wpvob->GetHomeWorld();
			if (wld) wld->RemoveVob(wp->wpvob);
			zRELEASE(wp->wpvob);
		}
	}

	zERR_MESSAGE(5,zERR_END,"");
}

void zCWayNet :: CreateVobDependencies(zCWorld* wld)
// Zu allen zCWaypoints werden passende zCVobWaypoints erzeugt und diese
// befinden sich dann als Vobs in der Welt. Zwecks editieren im Spacer
{
	if (!wld) return;

	zERR_MESSAGE(5,zERR_BEGIN,"U: WAYNET: Creating VobDependencies");

	// Zuerst einzelne Waypoints oder Waypoint mit Eigenschaften
	zCListSort <zCWaypoint>* wpnode = wplist.GetNextInList();
	zSTRING wpName;
	zCWaypoint*	wp;

	while (wpnode) {
		wp			= wpnode->GetData();
		wpnode		= wpnode->GetNextInList();
		if (!wp->wpvob) {
			wpName		=  wp->GetName();
			wp -> wpvob	=  zNEW( zCVobWaypoint() );
			wp -> wpvob -> SetVobName						(wpName);
			wp -> wpvob -> SetPositionWorld					(wp->GetPositionWorld());
			wld-> AddVob (wp->wpvob);
			wp -> wpvob -> SetHeadingAtWorld				(wp->GetAtVectorWorld()); // [Moos] 20.12.00 Anpassung an Vob-Änderung
		}
	}

	zERR_MESSAGE(5,zERR_END,"");
}

zSTRING zCWayNet :: MergeWaypoints ()
{
	// Zuerst einzelne Waypoints oder Waypoint mit Eigenschaften
	zCListSort <zCWaypoint>* wpnode1 = wplist.GetNextInList();
	zCListSort <zCWaypoint>* wpnode2 = NULL;
	zSTRING wpName;
	zSTRING foundWps;
	zCWaypoint *wp1,*wp2;

	while (wpnode1) 
	{
		wp1		= wpnode1->GetData();
		wpnode2 = wpnode1->GetNextInList();
		
		while (wpnode2) 
		{			
			wp2		= wpnode2->GetData();
			wpnode2 = wpnode2->GetNextInList();

			if (wp1->GetName()==wp2->GetName()) 
			{	
				zERR_WARNING("U: WAYNET: Two Waypoints with same name detected. Merging them : "+wp1->GetName());
				
				if (!foundWps.IsEmpty()) foundWps+=", ";
				foundWps += wp1->GetName();

				AddWays					(wp1,wp2);	// WP1 bekommt die Wege von WP2 verpasst
				DeleteWaypoint			(wp2);
				
			}
		}			
		wpnode1	= wpnode1->GetNextInList();	
	}
	return foundWps;
};

zSTRING zCWayNet :: CheckConsistency( zBOOL isFault )
// Check ob zwei zCWaypoints auf ein zCVobWaypoint referenzieren.
// FIXME : noch weitere Checks.... Doppelte Waypointnamen
{
	zBOOL error = FALSE;

	zERR_MESSAGE(5,zERR_BEGIN,"U: WAYNET: Checking consistency ...");

	// Zuerst einzelne Waypoints oder Waypoint mit Eigenschaften
	zCListSort <zCWaypoint>* wpnode1 = wplist.GetNextInList();
	zCListSort <zCWaypoint>* wpnode2 = NULL;
	zSTRING wpName;
	zSTRING foundWps;
	zCWaypoint *wp1,*wp2;

	while (wpnode1) 
	{
		wp1		= wpnode1->GetData();
		wpnode2 = wpnode1->GetNextInList();
		
		while (wpnode2) 
		{			
			wp2		= wpnode2->GetData();
			wpnode2 = wpnode2->GetNextInList();

			if (wp1->GetName()==wp2->GetName()) 
			{	
				zERR_WARNING("U: WAYNET: Two Waypoints with same name detected : "+wp1->GetName());
				if (!foundWps.IsEmpty()) foundWps+=", ";
				foundWps += wp1->GetName();
				error = TRUE;
			}
		}			
		wpnode1	= wpnode1->GetNextInList();	
	}

	if (error) 
	{
		if (isFault) {
			zERR_FAULT	("U: WAYNET: Waynet consistency check failed. Check zSpy-Messages.");
		} else {
			zERR_MESSAGE(5,0,"U: WAYNET: Waynet consistency check failed. Check zSpy-Messages.");
		}
	} 
	else 
	{
		zERR_MESSAGE(5,0,"U: WAYNET: Consistency check ok.");
	}

	zERR_MESSAGE(5,zERR_END,"");

	return foundWps;
}

void zCWayNet :: AddWays(zCWaypoint* wp1, zCWaypoint* wp2)
{
	// WP1 übernimmt die Wege von WP2
	zCList <zCWay>* way			= wp2->GetWayList().GetNextInList();
	zCWay*			waydata		= NULL;
	zCWaypoint*		targetwp	= NULL;

	while (way) {

		waydata	= way -> GetData();
		way		= way -> GetNextInList();
		
		// Zeil WP ermitteln (darf nicht wp2 sein);
		targetwp = waydata->GetRightWaypoint();
		if (targetwp == wp2) targetwp = waydata->GetLeftWaypoint();

		CreateWay(wp1,targetwp);
	}
}

// ********* Way **********

zCWay :: zCWay ( )
{
	left		= NULL;
	right		= NULL;
	chasm		= FALSE;
	chasmDepth	= 0.0f;
	jump		= FALSE;

	// PathFinding
	usedCtr	= 0;
};

zCWay :: zCWay ( zCWaypoint *w1, zCWaypoint *w2 )
{
	Init (w1, w2);
}

void zCWay :: Init ( zCWaypoint *w1, zCWaypoint *w2 )
{
	left		= w1;
	right		= w2;
	chasm		= FALSE;
	chasmDepth	= 0.0f;
	jump		= FALSE;

	// PathFinding
	usedCtr	= 0;
	left	-> InsertWay ( this );
	right	-> InsertWay ( this );
	EstimateCost();
};

void zCWay :: Free()
{
	if (left)	left ->RemoveWay(this);
	if (right)	right->RemoveWay(this);
};

zCWay :: ~zCWay ( )
{
	left	= NULL;
	right	= NULL;
};


zCWaypoint* zCWay :: GetGoalWaypoint ( zCWaypoint *w1 )
{
	if (left!=w1) 
		return left;
	else 
		return right;
}

void zCWay :: EstimateCost()
{
	// Manhattan Distance
	zVEC3 pos1 = left ->GetPositionWorld();
	zVEC3 pos2 = right->GetPositionWorld();
	cost = abs(pos1[VX]-pos2[VX]) + abs(pos1[VY]-pos2[VY]) + abs(pos1[VZ]-pos2[VZ]);
}

zREAL zCWay :: GetLength()
{
	// Berücksichtigt alle 3 Dims
	return (left->GetPositionWorld() - right->GetPositionWorld()).LengthApprox();
}

zREAL zCWay :: GetJumpDistance()
// Angenähert auf 2 Dimensionen (Y-Komponente bleibt nicht berücksichtigt)
// FIXME : einmal berechnen speichern
{
	zVEC3 pos1 = left	->GetPositionWorld();	pos1[VY] = 0;
	zVEC3 pos2 = right	->GetPositionWorld();	pos2[VY] = 0;
	return (pos1-pos2).LengthApprox() * 0.8;
}

zVEC3 zCWay :: GetDistancePos(zREAL xcm, zCWaypoint* wp1)
{
	zVEC3 pos1	= wp1->GetPositionWorld();
	zVEC3 pos2	= GetGoalWaypoint(wp1)->GetPositionWorld();
	zREAL len	= GetLength();
	// Steigung errechnen
	zVEC3 st	= (pos2 - pos1) / len;
	// und jetzt Position 
	return pos1 + (xcm * st);
}

zBOOL zCWay :: CanBeUsed (const zCVob* vob)
{
	return TRUE;
}

#define FUNKY_VC7_COMPILER_BUG

void zCWay :: Draw ( zCCamera *camera )
{

	zPOINT3 wsPoint1, wsPoint2, csPoint1, csPoint2;	// world/camera-space
	zPOINT2 ssPoint1, ssPoint2;						// screen-space X,Y

	wsPoint1 = left		-> GetPositionWorld();
	wsPoint2 = right	-> GetPositionWorld();

	csPoint1 = camera->Transform (wsPoint1);
	csPoint2 = camera->Transform (wsPoint2);
	Alg_ClipAtZ0(csPoint1,csPoint2);

	if (csPoint1[VZ]>=0) {
		camera->Project (&csPoint1, ssPoint1[VX], ssPoint1[VY]);
	} else return;
	
	if (csPoint2[VZ]>=0) {
		camera->Project (&csPoint2, ssPoint2[VX], ssPoint2[VY]);
	} else return;

	int x1 = (int)ssPoint1[VX];

#ifdef FUNKY_VC7_COMPILER_BUG
	int y1 = (int)2*ssPoint1[VY] - ssPoint1[VY];
#else
	int y1 = (int)2*ssPoint1[VY];
#endif

	int x2 = (int)ssPoint2[VX];
	int y2 = (int)ssPoint2[VY];	
	if (!screen->ClipLine(x1,y1,x2,y2)) return;
	
	zrenderer -> DrawLineZ	(x1,y1,1/csPoint1[VZ],x2,y2,1/csPoint2[VZ],GFX_RED);

	// Wayprop :
	zSTRING wayProp;
	if (chasmDepth != 0)	wayProp = "C";
	if (jump)				wayProp = "J";
	if (!wayProp.IsEmpty()) wayProp = "  ["+wayProp+"]";

	if (csPoint1[VZ]<1000)
		screen -> Print(screen->anx(ssPoint1[VX]),screen->any(ssPoint1[VY]),left	->GetName() + wayProp);
		
	if (csPoint2[VZ]<1000) 
		screen -> Print(screen->anx(ssPoint2[VX]),screen->any(ssPoint2[VY]),right	->GetName() + wayProp);
	
}

zVEC3 zCWay :: GetFloor (zCWorld* wld, const zVEC3& pos)
{
	const zREAL RAY_RANGE = 1000;			// 10 m

	zVEC3 dir (0,-RAY_RANGE,0);
	// Von derzeitiger Position einen Ray nach unten casten....
	if (wld->TraceRayNearestHit(pos,dir,(zCVob*)NULL,zTRACERAY_STAT_POLY)) {
		zCPolygon *poly	= wld->traceRayReport.foundPoly; 
		if (poly) return wld->traceRayReport.foundIntersection;
	} 
	zVEC3 floor = pos;
	floor[VY]  -= RAY_RANGE;
	return floor;
}

void zCWay :: CalcProperties (zCWorld* wld)
{
	const zREAL RAY_DISTANCE	= 20;			// 20 cm

	// Immer vom höchsten Waypoint aus
	zVEC3 spos,tmp,floor;
	zVEC3 pos1 = GetLeftWaypoint ()->GetPositionWorld();
	zVEC3 pos2 = GetRightWaypoint()->GetPositionWorld();
	if (pos2[VY] > pos1[VY]) {
		tmp	 = pos1;
		pos1 = pos2;
		pos2 = tmp;
	}
	spos = pos1;
	
	// gleiche Punkte ? Schmuh !
	if (pos1 == pos2) return;
	
	// Schrittdirection und weite ermitteln
	int steps	= (pos2 - pos1).Length() / RAY_DISTANCE;
	zVEC3 step	= (pos2 - pos1).Normalize() * RAY_DISTANCE;
	
	// Abgrund
	zREAL deltay1 = 0.0f;
	zREAL deltay2 = 0.0f;

	zREAL oldy = GetFloor(wld,pos1)[VY];

	// Und Schrittweise vorgehen
	for (int i=0; i<steps; i++) {
		
		pos1   += step;
		floor	= GetFloor(wld,pos1);
		// Steigungen auf jede Hälfte
		if (i<steps/2)	deltay1 += floor[VY] - oldy;
		else			deltay2 += floor[VY] - oldy;
		oldy	= floor[VY];
	}

	// Gefälle von mehr als 2m ?
	if (deltay1 < -200) {

		chasmDepth	= deltay1;

		// ja, also pot. Abgrund
		// Steigung mindesten wieder auf halbe Höhe ?
		if (deltay2 > (-deltay1 / 2)) {
			// Ja, Abgrund -> zu Überwinden durch Sprung
			jump = TRUE;
		}
	}
}

zREAL zCWay :: GetChasm()
{
	return -chasmDepth;
}

zBOOL zCWay :: CanJump()
{
	return jump;
}

// ********* Waypoints **********

int	zCWayNet :: SortWpList (zCWaypoint* w1, zCWaypoint* w2)
{
	if (w1->GetName() < w2->GetName()) 
		return -1;
	else
		return 1;
}

zCWaypoint :: zCWaypoint ( )
{
	wpvob		= NULL;
	pos			= zVEC3(0,0,0);
	dir			= zVEC3(1,0,0);
	// PathFinding
	routeCtr	= 0;
	curCost		= 0;
	estCost		= 0;
	score		= 0;
	curList		= 0;
	parent		= NULL;
	// Properties
	underWater	= FALSE;
	waterDepth	= 0.0f;
}

void zCWaypoint :: Init ( zVEC3& vec )
{
	wpvob		= NULL;
	pos			= vec;
	dir			= zVEC3(1,0,0);
}

void zCWaypoint :: Init ( float x, float y, float z )
{
	wpvob		= NULL;
	pos			= zVEC3(x,y,z);
	dir			= zVEC3(1,0,0);
}

void zCWaypoint :: Init ( zCVobWaypoint *vob )
{
	name		= vob->GetVobName();		name.Upper();
	wpvob		= vob;
	pos			= vob->GetPositionWorld();
	dir			= vob->GetAtVectorWorld();

	if (wpvob) wpvob->AddRef();
}

void zCWaypoint :: Free()
{
	// Delete all Routes with this Waypoint
	zCWay	 		*waydata;
	zCList <zCWay>	*way = wayList.GetNextInList();

	while (way) {
		waydata	= way -> GetData();		

		delete (waydata);		

		way		= wayList.GetNextInList();
	}
	parent	= NULL;
	if (wpvob && wpvob->GetHomeWorld()) wpvob->GetHomeWorld()->RemoveVob(wpvob);
	zRELEASE (wpvob);
};

zCWaypoint :: ~zCWaypoint ( )
{
//	assert (wayList.GetNumInlist()<=0);
//	wayList.EmptyList();

	wpvob	= NULL;
	parent	= NULL;
}

zVEC3& zCWaypoint :: GetPositionWorld ( )
{
	return pos;
}

void zCWaypoint :: UpdatePositionWorld ( )
{
	if (wpvob) {
		pos = wpvob -> GetPositionWorld();
		dir = wpvob -> GetAtVectorWorld();
	}
}

void zCWaypoint :: SetName ( zSTRING &s )
{
	name = s; name.Upper();
	if (wpvob) wpvob->SetVobName(s);
}

const zSTRING& zCWaypoint :: GetName ( )
{
	if (wpvob) {
		name = wpvob->GetVobName();
	}	
	return name;
}

zCVobWaypoint* zCWaypoint :: GetVob()
{
	return wpvob;
}

void zCWaypoint :: CalcProperties(zCWorld *wld)
{
	const zREAL MAX_WATERDEPTH = 1000;		// 10m
	// ********************
	// a) detect WaterLevel
	// ********************
	waterDepth		= 0.0f;
	zREAL groundDist= 0.0f;
	zVEC3 pos		= GetPositionWorld();
	
	zVEC3 dir (0,-MAX_WATERDEPTH,0);
	// Von derzeitiger Position einen Ray nach unten casten....
	if (wld->TraceRayNearestHit(pos,dir,wpvob,zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_VOB_IGNORE_NO_CD_DYN | zTRACERAY_POLY_TEST_WATER)) {
		zCPolygon *poly	= wld->traceRayReport.foundPoly; 
		if (poly) {
			groundDist = pos[VY] - wld->traceRayReport.foundIntersection[VY];
			if (poly->GetMaterial() && (poly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER)) {
				// ja, Boden ist ein Wasser-Poly
				// Schnittpunkt schnappen und Wassertiefe ermitteln
				pos = wld->traceRayReport.foundIntersection;
				if (wld->TraceRayNearestHit(pos,dir,wpvob,zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_VOB_IGNORE_NO_CD_DYN)) {
					poly = wld->traceRayReport.foundPoly; 
					if (poly) {
						waterDepth += pos[VY] - wld->traceRayReport.foundIntersection[VY];
					} else {
						zERR_WARNING ("U: WAY: Incorrect Waterdepth at WP "+GetName());
					}
				}
			}
		}
	}

	dir = zVEC3(0,MAX_WATERDEPTH,0);
	// Von derzeitiger Position einen Ray nach oben casten....
	if (wld->TraceRayNearestHit(pos,dir,wpvob,zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_VOB_IGNORE_NO_CD_DYN | zTRACERAY_POLY_TEST_WATER)) {
		zCPolygon *poly	= wld->traceRayReport.foundPoly; 
		if ((poly) && (poly->GetMaterial()) && (poly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER)) {
			// ja, Decke ist ein Wasser-Poly
			// Schnittpunkt schnappen und Wassertiefe ermitteln
			pos			= wld->traceRayReport.foundIntersection;
			waterDepth	= (pos[VY] - GetPositionWorld()[VY]) + groundDist;
			underWater	= TRUE;
		}
	}
};

void zCWaypoint :: CorrectHeight(zCWorld *wld)
{
//	if (HasSpecial(zWAY_FREE | zWAY_DIVE)) return;
	
//	if (!HasSpecial(zWAY_SWIM)) {
		zVEC3 dir(0,-1000,0);
		// Von derzeitiger Position einen Ray casten
		if (wld->TraceRayNearestHit(pos,dir,wpvob,zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE_NO_CD_DYN | zTRACERAY_VOB_IGNORE_CHARACTER)) {
			// Poly gefunden
			if (wld->traceRayReport.foundPoly || wld->traceRayReport.foundVob) {
				// Schnittpunkt schnappen und Position neu setzen
				zVEC3 newpos = wld->traceRayReport.foundIntersection + zVEC3(0,50,0);
				pos = newpos;
				if (wpvob) wpvob->SetPositionWorld(newpos);	
			}
		}
/*	} else {
		// Swim Waypoint -> auf Wasserhoehe setzen
		// Zuerst nach unten...
		zVEC3 dir(0,-1000,0);
		// Von derzeitiger Position einen Ray casten
		if (wld->TraceRayNearestHit(pos,dir,wpvob,zTRACERAY_STAT_POLY)) {
			zCPolygon *poly	= wld->traceRayReport.foundPoly; 
			if ((poly) && (poly->GetMaterial()) && (poly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER)) {
				// ja, Boden ist ein Wasser-Poly
				// Schnittpunkt schnappen und Position neu setzen
				zVEC3 newpos = wld->traceRayReport.foundIntersection;
				pos = newpos;
				if (wpvob) wpvob->SetPositionWorld(newpos);
				return;
			}
		} 
		// Dann nach oben...
		dir = zVEC3(0,+1000,0);
		// Von derzeitiger Position einen Ray casten
		if (wld->TraceRayNearestHit(pos,dir,wpvob,zTRACERAY_STAT_POLY)) {
			zCPolygon *poly	= wld->traceRayReport.foundPoly; 
			if ((poly) && (poly->GetMaterial()) && (poly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER)) {
				// ja, Boden ist ein Wasser-Poly
				// Schnittpunkt schnappen und Position neu setzen
				zVEC3 newpos = wld->traceRayReport.foundIntersection;
				pos = newpos;
				if (wpvob) wpvob->SetPositionWorld(newpos);
			}
		}
	} */
}

void zCWaypoint :: InsertWay ( zCWay *way )
{
	wayList.Insert(way);
}

void zCWaypoint :: RemoveWay ( zCWay *way )
{
	wayList.Remove(way);
}

zCWay* zCWaypoint :: HasWay ( zCWaypoint *wp )
{
	zCWaypoint	*goal;
	zCWay			*waydata;
	zCList <zCWay>	*way = wayList.GetNextInList();

	while (way!=NULL) {

		waydata	= way -> GetData();
		way		= way -> GetNextInList();
		
		goal	= waydata -> GetGoalWaypoint ( this );	
		if (goal==wp) return waydata;
	}

	return NULL;
}

int zCWaypoint :: GetNumberOfWays ()
{
	return wayList.GetNumInList();
}

zCList <zCWay>& zCWaypoint :: GetWayList()
{
	return wayList;
}

void zCWaypoint :: SetWaypointVob( zCVobWaypoint* vob )
// Release Vob, but dont remove from World !
{
	if (wpvob) {
		wpvob->Release();
		wpvob = NULL;
	} 
	wpvob = vob;
	if (wpvob) wpvob->AddRef();
}

void zCWaypoint :: Draw ()
{
}

void zCWaypoint :: Archive(zCArchiver &arc)
{
	arc.WriteString	("wpName"		,name);
	arc.WriteInt	("waterDepth"	,waterDepth);
	arc.WriteBool	("underWater"	,underWater);
	arc.WriteVec3	("position"		,pos);
	arc.WriteVec3	("direction"	,dir);	
};

void zCWaypoint :: Unarchive(zCArchiver &arc)
{
	arc.ReadString	("wpName"		,name);
	arc.ReadInt		("waterDepth"	,waterDepth);
	arc.ReadBool	("underWater"	,underWater);
	arc.ReadVec3	("position"		,pos);
	arc.ReadVec3	("direction"	,dir);
};

zCWaypoint* zCCFASTCALL zCWayNet :: GetWaypoint ( const zSTRING &s ) const
// Binary Search
{
	if (wplist.GetNumInList()<=0) return NULL;

	// Binary Search	
	// return value= found index, -1=not found
	int ind_low		= 0;
	int ind_high	= wplist.GetNumInList()-1;
	int index		= ( ind_low + ind_high ) / 2;
	int erg;

	do {
//		erg = strcmp(s.ToChar(), wplist[index]->GetName().ToChar());
		erg = s.CompareTo (wplist[index]->GetName());

		zERR_ASSERT (erg==strcmp(s.ToChar(), wplist[index]->GetName().ToChar()));
		if (ind_high <= ind_low) 
		{
			if (erg==0) return wplist[index];
			return NULL;
		}

		if (erg>0) 	ind_low	= index + 1; else
		if (erg<0)  ind_high= index - 1; else
					return wplist[index];

		index = ( ind_low + ind_high ) / 2;
	
	} while (1);
	
	return NULL;

/*	zCList <zCWaypoint>* wpnode = wplist.GetNextInList();
	zCWaypoint* wp;
	while (wpnode) {
		wp		= wpnode->GetData();
		wpnode	= wpnode->GetNextInList();
		if (wp->GetName()==s) return wp;
	}	
	return NULL;*/
}

zCWaypoint* zCWayNet :: SearchWaypoint ( zCVobWaypoint *w )
{
	zCListSort <zCWaypoint>* wpnode = wplist.GetNextInList();
	zCWaypoint* wp;
	while (wpnode) {
		wp		= wpnode->GetData();
		wpnode	= wpnode->GetNextInList();
		if (wp->wpvob==w) return wp;
	}	
	return NULL;
}

zCRoute* zCWayNet :: FindRoute ( const zVEC3 &from, const zVEC3	&to, const zCVob* vob )
{
	// ersten Waypoint holen
	// !!! FIXME :: sichtbar bzw. erreichbar ?
	zCWaypoint *wp1 = GetNearestWaypoint ((zVEC3)from);
	if (!wp1) return NULL;
	
	// letzten Waypoint holen
	zCWaypoint *wp2 = GetNearestWaypoint ((zVEC3)to);
	if (!wp2) return NULL;

	// Route bauen
	// r->AddPos(to);
	// FindRoute_Dykstra(wp1,wp2,r);
	// return r;
	if (AStar (wp1,wp2,vob)) {
#ifdef DEBUG_WOHLERS
		zERR_WARNING("U:WAY: Route found : "+wp1->GetName()+" - "+wp2->GetName());	
#endif
		return CreateRoute(wp2);
	}
	return NULL;
}

zCRoute* zCWayNet :: FindRoute ( const zVEC3 &from, zCWaypoint *to, const zCVob* vob )
{
	// ersten Waypoint holen
	zCWaypoint *wp1 = GetNearestWaypoint ((zVEC3)from);
	if (!wp1 || !to) return NULL;
	
	// Route bauen
	if (AStar (wp1,to,vob)) return CreateRoute(to);
	return NULL;
}

zCRoute* zCWayNet :: FindRoute ( const zVEC3 &from, const zSTRING &to, const zCVob* vob )
{
	// ersten Waypoint holen
	// !!! FIXME :: sichtbar bzw. erreichbar ?
	zCWaypoint *wp1 = GetNearestWaypoint ((zVEC3)from);
	if (!wp1)	return NULL;
	zCWaypoint *wp2 = GetWaypoint(to);
	if (!wp2)	return NULL;
	// Route bauen
	if (AStar (wp1,wp2,vob)) return CreateRoute(wp2);
	return NULL;
}

zCRoute* zCWayNet :: FindRoute ( zCWaypoint *from, zCWaypoint *to, const zCVob* vob )
{
	// Route bauen
	if (AStar (from,to,vob)) return CreateRoute(to);
	return NULL;
}

zCRoute* zCWayNet :: FindRoute ( const zSTRING &from, const zSTRING& to, const zCVob* vob )
{
	zCWaypoint* wp1 = GetWaypoint(from);
	zCWaypoint* wp2 = GetWaypoint(to);
	if (wp1 && wp2) {
		wp1 -> parent = NULL;
		wp2 -> parent = NULL;
		if (AStar (wp1,wp2,vob)) return CreateRoute(wp2);
	} 
	return NULL;
}

// ************** Pathfinding ****************
// ***************** Route *******************
// ************** A-Star-Search **************

int	zCWayNet :: SortOpenList (zCWaypoint* w1, zCWaypoint* w2)
{
	if (w1->score < w2->score) 
		return -1;
	else
		return 1;
}

void zCWayNet :: InsertInOpen(zCWaypoint* wp)
{
	// Priority Queue
	openList.InsertSort(wp);
	wp->curList		= WAY_LIST_OPEN;
	wp->routeCtr	= routeCtr;
}

zBOOL zCWayNet :: IsInOpen(zCWaypoint* wp)
{
	return (wp->routeCtr == routeCtr) && (wp->curList==WAY_LIST_OPEN);
}

void zCWayNet :: InsertInClosed(zCWaypoint* wp)
{
	wp->curList		= WAY_LIST_CLOSED;
	wp->routeCtr	= routeCtr;
}

void zCWayNet :: RemoveFromClosed(zCWaypoint* wp)
{
	wp->curList		= WAY_LIST_NONE;
}

zBOOL zCWayNet :: IsInClosed(zCWaypoint* wp)
{
	return (wp->routeCtr == routeCtr) && (wp->curList==WAY_LIST_CLOSED);
}

zBOOL zCWayNet :: IsInAnyList(zCWaypoint* wp)
{
	return (IsInOpen(wp) || IsInClosed(wp));
}

int zCWayNet :: EstimateCost(zCWaypoint* from, zCWaypoint* to)
{
	// Manhattan Distance
	zVEC3 pos1 = from->GetPositionWorld();
	zVEC3 pos2 = to->GetPositionWorld();
	return abs(pos1[VX]-pos2[VX]) + abs(pos1[VY]-pos2[VY]) + abs(pos1[VZ]-pos2[VZ]);
}

zCRoute* zCWayNet :: CreateRoute (zCWaypoint *to) 
{
	zCRoute* rt = zNEW( zCRoute() );	
	while (to) {
		if (to->parent) {
			rt-> wayList.Insert(to->parent);
			to = to->parent->GetGoalWaypoint(to);

		} else {
			rt-> SetStart(to);
			to = NULL;
		}
	}
	return rt;
}

zBOOL zCWayNet :: AStar (zCWaypoint* from, zCWaypoint* to, const zCVob* vob)
{
	int			newScore;
	zCWay		*way;
	zCWaypoint	*wp1, *wp2;
	zCList		<zCWay>		 *waynode;
	zCListSort	<zCWaypoint> *wpnode;

	routeCtr++;

	from->curCost	= 0;
	from->estCost	= EstimateCost(from,to);
	from->score		= from->curCost + from->estCost;
	from->parent	= NULL;

	openList.DeleteList();
	InsertInOpen (from);
	
	while (openList.GetNumInList()>0) {

		// Erstes Element aus Liste holen
		wpnode = openList.GetNextInList();	
		wp1	   = wpnode->GetData();
		openList.Remove(wp1);

		// Ziel erreicht ?
		if (wp1 == to) return TRUE;

		// Alle Wege abchecken
		waynode = wp1->wayList.GetNextInList();
		while (waynode) {
			way		= waynode -> GetData();
			waynode = waynode -> GetNextInList();

			// Weg schon einmal benutzt ?
			if (way -> usedCtr == routeCtr) continue;
			
			// Zielwegpunkt ok ?
			wp2	= way->GetGoalWaypoint(wp1);
			
			if (vob) {
				// Kann Waypoint benutzt werden ?
				if (!wp2 -> CanBeUsed(vob)) continue;
				// Kann Weg benutzt werden ?
				if (!way -> CanBeUsed(vob)) continue;
			}

			way -> usedCtr	= routeCtr;

			// Neuen Score berechnen
			newScore = wp1 -> curCost + way -> GetCost();

			if ((wp2->curCost <= newScore) && IsInAnyList(wp2)) {
				continue;
			}
			
			wp2 -> parent	= way;
			wp2 -> curCost	= newScore;
			wp2 -> estCost	= EstimateCost(wp2,to);
			wp2 -> score	= wp2 -> curCost + wp2 -> estCost;
			
			if (IsInClosed(wp2)) RemoveFromClosed(wp2);
			if (!IsInOpen (wp2)) InsertInOpen(wp2);
		}

		InsertInClosed(wp1);
	}
	return FALSE;
}

void zCWayNet :: GetWPList ( zCList <zVEC3> &wpl, zVEC3 &pos, zREAL mindist, zREAL maxdist )
{
	// Sammelt alle Waypoint-Pos innerhalb der dist in Liste
	zCListSort <zCWaypoint>* wpnode = wplist.GetNextInList();
	zCWaypoint* wp;
	while (wpnode) {
		wp		= wpnode->GetData();
		wpnode	= wpnode->GetNextInList();
		
//		if (!wp->HasSpecial(zWAY_SWIM) && !wp->HasSpecial(zWAY_DIVE)) {
			zVEC3 poswp = wp -> GetPositionWorld();
			zREAL d		= (poswp - pos).LengthApprox();
			if ((mindist<=d) && (d<=maxdist)) wpl.Insert( zNEW( zVEC3(poswp) ) );
//		}
	}
}

void zCWayNet :: CreateWPVobList(zCList <zCVobWaypoint> &resultlist, zCTree <zCVob> *node )
{
	if (node == NULL) return;

	if (node -> GetData() -> GetVobType() == zVOB_TYPE_WAYPOINT) {
		resultlist.Insert((zCVobWaypoint*)node->GetData());
	}

	CreateWPVobList ( resultlist, node->GetFirstChild());
	CreateWPVobList ( resultlist, node->GetNextChild());					
}

void zCWayNet :: RemoveUnusedWPVobs()
{
	if (!world) return;

	zCList <zCVobWaypoint> resultlist;
	CreateWPVobList (resultlist,world->globalVobTree.GetFirstChild());
	zCList <zCVobWaypoint>* node = resultlist.GetNextInList();
	while (node) {
		zCVobWaypoint* wp	= node -> GetData();
		node				= node -> GetNextInList();
		// Wurde Wegpunkt benutzt ?
		if (!SearchWaypoint(wp)) {
			// Aus der Welt entfernen geschieht hier automatisch ?!
			zRELEASE(wp);
		}
	}
	resultlist.DeleteList();
}

// *************************************
// Archive / Unarchive
// *************************************

void zCWayNet :: ArchiveOldFormat (zCArchiver &arc)
{
	zCObject :: Archive (arc);
	
	CheckConsistency(TRUE);

	// *** Write Single Waypoints or Waypoints with special properties ***
	int c = 0;
	// Zuerst einzelne Waypoints oder Waypoint mit Eigenschaften
	zCListSort <zCWaypoint>* wpnode = wplist.GetNextInList();
	zCWaypoint* wp;
	while (wpnode) {
		wp		= wpnode->GetData();
		wpnode	= wpnode->GetNextInList();
		if (wp -> GetNumberOfWays()==0) c++;						
	}
	arc.WriteInt("numWaypoints",c);
	
	// 2.Run : Write them
	c = 0;
	wpnode = wplist.GetNextInList();
	while (wpnode) {
		wp		= wpnode->GetData();
		wpnode	= wpnode->GetNextInList();

		if (wp -> GetNumberOfWays()==0) {
			zSTRING v = "waypoint"+zSTRING(c);
			arc.WriteString( v.ToChar(), wp->GetName() );
			c++;
		};
	}

	// *** Write Ways ***
	c = 0;
	arc.WriteInt("numWays",waylist.GetNumInList());
	zCList <zCWay>* waynode = waylist.GetNextInList();
	zCWay *way;
	while (waynode) {
		way		= waynode->GetData();
		waynode = waynode->GetNextInList();
		
		zSTRING v = "way"+zSTRING(c);
		arc.WriteString(v.ToChar(),way->GetLeftWaypoint()->GetName()+"/"+way->GetRightWaypoint()->GetName());
		c++;
	}	
};

void zCWayNet :: Archive (zCArchiver &arc)
{
	zCObject :: Archive (arc);
	
	zERR_MESSAGE(5,0,"U:WAY: Writing Waynet.");
	
	if (!arc.InSaveGame()) CheckConsistency(TRUE);

	int waynetVersion = 1;
	arc.WriteInt("waynetVersion",waynetVersion);

	// *** Write Single Waypoints or Waypoints with special properties ***
	int c = 0;
	// Zuerst einzelne Waypoints oder Waypoint mit Eigenschaften
	zCListSort <zCWaypoint>* wpnode = wplist.GetNextInList();
	zCWaypoint* wp;
	while (wpnode) {
		wp		= wpnode->GetData();
		wpnode	= wpnode->GetNextInList();
		if (wp -> GetNumberOfWays()==0) c++;						
	}
	arc.WriteInt("numWaypoints",c);
	
	// 2.Run : Write them
	c = 0;
	wpnode = wplist.GetNextInList();
	while (wpnode) {
		wp		= wpnode->GetData();
		wpnode	= wpnode->GetNextInList();

		if (wp -> GetNumberOfWays()==0) {
			zSTRING v = "waypoint"+zSTRING(c);
			arc.WriteObject( v.ToChar(), wp );
			c++;
		};
	}

	// *** Write Ways ***
	c = 0;
	zSTRING v;
	arc.WriteInt("numWays",waylist.GetNumInList());
	zCList <zCWay>* waynode = waylist.GetNextInList();
	zCWay *way;
	while (waynode) {
		way		= waynode->GetData();
		waynode = waynode->GetNextInList();
		
		v		= "wayl"+zSTRING(c);
		arc.WriteObject(v.ToChar(),way->GetLeftWaypoint());
		v		= "wayr"+zSTRING(c);
		arc.WriteObject(v.ToChar(),way->GetRightWaypoint());
		c++;
	}	

	zERR_MESSAGE(5,0,"U:WAY: Writing ok.");
};

void zCWayNet :: UnarchiveOldFormat (zCArchiver &arc)
{
	zERR_MESSAGE(5,0,"U:WAY: Reading Waynet (old format).");

//  Das ist zu diesem Zeitpunkt bereits passiert.
//	zCObject :: Unarchive (arc);

	zCVobWaypoint	*wp1, *wp2;
	zCWaypoint		*w1,  *w2;

	zSTRING s,prop;
	int w = arc.ReadInt("numWaypoints");
	for (int i=0; i<w; i++) {
		zSTRING v	= "waypoint" + zSTRING(i);
		s			= arc.ReadString(v.ToChar());
		prop		= s.Copied("[",zSTR_FROM);
		s.Delete("[",zSTR_FROM);		
		// wp already in World ?
		w1 = GetWaypoint(s);
		if (!w1) {
			wp1	= dynamic_cast<zCVobWaypoint*>(world -> SearchVobByName(s));
			if (!wp1) {				
				zERR_WARNING("U: WAY: Waypoint not found : " + s);
				continue;
			} 
			// Es gibt ihn noch nicht -> neu erzeugen
			w1	= zfactory->CreateWaypoint ();
			w1 -> Init(wp1);
			wplist.InsertSort(w1);
		}
	};

	zSTRING v1,v2;
	w = arc.ReadInt("numWays");
	for (i=0; i<w; i++) {
		zSTRING v	= "way"+zSTRING(i);
		s	= arc.ReadString(v.ToChar());
		v1 	= s.Copied("/",zSTR_BEFORE);
		v2	= s.Copied("/",zSTR_AFTER);

		// wp already in World ?
		w1 = GetWaypoint(v1);
		if (!w1) {
			wp1	= dynamic_cast<zCVobWaypoint*>(world -> SearchVobByName(v1));
			if (!wp1) {
				zERR_WARNING("U:WAY: Waypoint not found : " + v1);
				continue;
			} 
			// Es gibt ihn noch nicht -> neu erzeugen
			w1	= zfactory->CreateWaypoint ();
			w1 -> Init(wp1);
			wplist.InsertSort(w1);
		}

		// wp already in World ?
		w2 = GetWaypoint(v2);
		if (!w2) {
			wp2	= dynamic_cast<zCVobWaypoint*>(world -> SearchVobByName(v2));
			if (!wp2) {
				zERR_WARNING("U:WAY: Waypoint not found : " + v2);
				continue;
			} 
			// Es gibt ihn noch nicht -> neu erzeugen
			w2	= zfactory->CreateWaypoint ();
			w2 -> Init(wp2);
			wplist.InsertSort(w2);
		}
/*

		// zweiter Waypoint
		wp2 = dynamic_cast<zCVobWaypoint*>(world -> SearchVobByName(v2));
		if (!wp2) {
			zERR_WARNING("U:WAY: Waypoint not found : " + v2);
			continue;
		}
		w2	= GetWaypoint(v2);
		if (!w2) {
			w2 = zfactory->CreateWaypoint();
			w2 -> Init(wp2);
			wplist.InsertSort(w2);
		}*/
		
		// Verbindung herstellen
		zCWay* way = zfactory->CreateWay();
		way -> Init (w1,w2);
		waylist.Insert ( way );
	};
	// Altes Format : Die zugehoerigen zCVobWaypoints werden hier noch mitgespeichert.
	// Spacer       : so lassen, alles wunderbar.
	// Game         : Diese Vobs aus Welt entfernen, unnoetig....
#ifndef COMPILING_SPACER
	ClearVobDependencies();
#endif
	// Doesnt work if level not yet compiled...
	// CorrectHeight		();
	// CalcProperties		(world);
	zERR_MESSAGE(5,0,"U:WAY: Waynet ok (old format).");
};

void zCWayNet :: Unarchive (zCArchiver &arc)
{
	zERR_MESSAGE(5,0,"U:WAY: Reading Waynet.");
	
	zCObject :: Unarchive (arc);

	int waynetVersion = 0;
	arc.ReadInt("waynetVersion",waynetVersion);
	if (waynetVersion==0) {
		
		UnarchiveOldFormat(arc);
	
	} else {
	
		zCWaypoint		*w1,  *w2;

		zSTRING s,prop;
		int w = arc.ReadInt("numWaypoints");
		for (int i=0; i<w; i++) {
			zSTRING v	= "waypoint" + zSTRING(i);
			w1			= (zCWaypoint*)arc.ReadObject(v.ToChar());
			InsertWaypoint(w1);
		}		

		zSTRING v1,v2;
		zSTRING v;
		w = arc.ReadInt("numWays");
		for (i=0; i<w; i++) {
			
			v	= "wayl"+zSTRING(i);
			w1	= (zCWaypoint*)arc.ReadObject(v.ToChar());
			// Niemals grösser "1" werden lassen... Ist echt nicht noetig... [Moos] machen wir mal 2 draus; der Archiver hat auch eine Referenz. Was sind das hier eigentlich für Methoden???
			if (w1->GetRefCtr()>2) 	w1->Release();
			else					wplist.InsertSort(w1);

			v	= "wayr"+zSTRING(i);
			w2	= (zCWaypoint*)arc.ReadObject(v.ToChar());
			// Niemals grösser "1" werden lassen... Ist echt nicht noetig...
			if (w2->GetRefCtr()>2)	w2->Release();
			else					wplist.InsertSort(w2);
			
			// Verbindung herstellen
			zCWay* way = zfactory->CreateWay();
			way -> Init (w1,w2);
			assert(w1);
			assert(w2);
			waylist.Insert ( way );
		}		
	}

	// Neues Format : Es gibt keine passen zCVobWaypoints mehr.
	// Spacer       : diese muessen neu erzeugt werden, damit Editierung des Wegentzes moeglich
	// Game         : Alles so lassen, nichts anfassen.
#ifdef COMPILING_SPACER
	CreateVobDependencies(world);
#endif
	zERR_MESSAGE(5,0,"U:WAY: Waynet ok.");
};

// *********************************************************************************
// automatic determination of waynet properties
// *********************************************************************************

void zCWayNet :: CalcProperties(zCWorld* wld)
{
	// This may take a while...
	
	// ***********
	//  Waypoints 
	// ***********

	zCWaypoint* wp = NULL;
	zCListSort<zCWaypoint> *node = wplist.GetNextInList();
	while (node) {
		wp		= node->GetData();
		node	= node->GetNextInList();
		wp	   -> CalcProperties(wld);
	}

	// ***********
	// Ways
	// ***********
	zCWay* way = NULL;
	zCList <zCWay> *nodew = waylist.GetNextInList();
	while (nodew) {
		way		= nodew->GetData();
		nodew	= nodew->GetNextInList();
		way	   -> CalcProperties(wld);
	}

}

// *********************************************************************************
// zCRoute
// *********************************************************************************

zCRoute :: zCRoute( )
{
	target	= NULL;
	way		= NULL;
	waynode	= NULL;
	startwp	= NULL;
}

zCRoute :: ~zCRoute( )
{
	target	= NULL;
	way		= NULL;
	waynode	= NULL;
	startwp	= NULL;
}

void zCRoute :: SetStart (zCWaypoint* wp)
{
	startwp = target = wp;
}

zCWaypoint* zCRoute :: GetNextWP ()
{
	if (!waynode) {
		if (wayList.GetNumInList()>0) 
			waynode = wayList.GetNextInList();
		else {
			zCWaypoint* tmp = target = startwp;
			startwp = NULL;
			return tmp;
		}

	} else {
		waynode = waynode -> GetNextInList();
	}
	if (waynode) {
		way		= waynode->GetData();
		target	= way->GetGoalWaypoint(target);
		return target;
	}
	return NULL;
}

zCWaypoint* zCRoute :: GetTargetWP ()
{
	return target;
}

zCWay* zCRoute :: GetCurrentWay ()
{
	return way;
}

zSTRING zCRoute :: GetDesc ()
{
	zSTRING desc;
	if (!startwp) return desc;

	zCWaypoint* curwp = startwp;
	desc = startwp->GetName();

	zCList <zCWay>* wnode = wayList.GetNextInList();
	while (wnode) {
		way	  = wnode->GetData();
		wnode = wnode->GetNextInList();
		
		curwp = way->GetGoalWaypoint(curwp);
		desc += " - " + curwp->GetName();
	}
	return desc;
}

zSTRING zCRoute :: GetRemainingDesc ()
{
	zSTRING desc;
	if (!target) return desc;

	zCWaypoint* curwp = target;
	desc = target->GetName();

	zCList <zCWay>* wnode = wayList.GetNextInList();
	while (wnode) {
		way	  = wnode->GetData();
		wnode = wnode->GetNextInList();
		
		curwp = way->GetGoalWaypoint(curwp);
		desc += " - " + curwp->GetName();
	}
	return desc;
}

int zCRoute :: GetNumberOfWaypoints ()
{
	return wayList.GetNumInList() + 1;
}

zBOOL zCRoute :: IsEmpty()
{
	return (wayList.GetNumInList()<=0);
}

zBOOL zCRoute :: IsLastTarget()
{
	if (waynode) return (waynode->GetNextInList()==NULL);
	return TRUE;
}

zBOOL zCRoute :: GetInterpolatedPosition(zREAL kmperh, int passedMin, zVEC3& foundPos)
{	
	// Nur 1 Waypoint
	if ((wayList.GetNumInList()==0) && (startwp)) {
		foundPos = startwp->GetPositionWorld();
		return TRUE;
	}
	
	zREAL waydist;
	// cm / min
	zREAL cm		= kmperh * 1000 * 100;		// 1km = 1000m = 100000 cm
	zREAL cmpermin	= cm / 60.0f;				// 1h  = 60min
	zREAL walkedcm	= cmpermin * passedMin;		// Wieviele cm ist er in dieser Zeit gegangen ?
	// Liste der Wege durchlaufen und Zeit pro Weg berechnen
	zCList <zCWay>* waynode = wayList.GetNextInList();
	zCWaypoint* wp			= startwp;
	while (waynode) {
		way					= waynode	-> GetData();
		if (way) waydist	= way		-> GetLength();			// dist in cm
		waynode				= waynode	-> GetNextInList();
		if (!way) continue;
		// Distance überschritten ?
		walkedcm   -= waydist;
		if (walkedcm<=0) {
			// Der Punkt liegt auf diesem Weg
			// und zwar xcm cm vom Startwp entfernt
			zREAL xcm	= waydist + walkedcm;
			// Das ist die gesuchte Position
			foundPos	= way -> GetDistancePos (xcm, wp);
			return TRUE;
		}
		wp = way -> GetGoalWaypoint(wp);
	}
	if ((walkedcm>=0) && wp) {
		foundPos = wp->GetPositionWorld();
		return TRUE;		
	}
	return FALSE;
}

// ********************************************************************************
// Freepoints
// ********************************************************************************

zCVobSpot :: zCVobSpot()
{
	timerEnd	= 0.0f;
	inUseVob	= NULL;
};

zCVobSpot :: ~zCVobSpot()
{
	inUseVob	= NULL;
};

zBOOL zCVobSpot :: IsAvailable(zCVob* vob)
{
	const zREAL FPBOX_DIMENSION = 50;

	if (inUseVob && (inUseVob!=vob)) {
		// Zeit ok, oder hat sich da schon jemand angemeldet.
		zREAL nowTime = ztimer.GetTotalTimeF();
		if (nowTime < timerEnd) return FALSE;
	}	
	if (!GetHomeWorld()) return FALSE;

	// BBox checken
	zCVob* vobIn = NULL;
	zCArray<zCVob*> foundVob;
	zTBBox3D		foundbox;
	foundbox.maxs = foundbox.mins = GetPositionWorld();		
	foundbox.maxs[0] += FPBOX_DIMENSION; foundbox.maxs[1] += FPBOX_DIMENSION*2; foundbox.maxs[2] += FPBOX_DIMENSION;
	foundbox.mins[0] -= FPBOX_DIMENSION; foundbox.mins[1] -= FPBOX_DIMENSION*2; foundbox.mins[2] -= FPBOX_DIMENSION;
	GetHomeWorld() -> CollectVobsInBBox3D (foundVob, foundbox);
	for (int n=0; n<foundVob.GetNumInList (); n++) {	
		
		vobIn = foundVob[n];
		
		// angemeldeter NSC steht weiterhin in BBOX -> kein Abmelden erlaubt -> FP besetzt
		if (inUseVob == vobIn) return (inUseVob==vob);

		/*
		// General Check -> Any NSC blocks this Freepoint
		  if ((vobIn->GetVobType()==zVOB_TYPE_NSC) && (vobIn!=vob)) {
			// besetzt, dann raus
			return FALSE;
		}*/
	}
	// Its free for another Vob!!!!!
	inUseVob = NULL;
	return TRUE;
};

void zCVobSpot :: MarkAsUsed(zREAL timeDelta, zCVob* vob)
{
	// ab diesen zeitpunkt wieder frei
	timerEnd	= ztimer.GetTotalTimeF() + timeDelta;
	inUseVob	= vob;
}

zCLASS_DEFINITION ( zCVobWaypoint,	zCVob	, 0, 0 )
zCLASS_DEFINITION ( zCVobSpot,		zCVob	, 0, 0 )
zCLASS_DEFINITION ( zCVobStartpoint,zCVob	, 0, 0 )
zCLASS_DEFINITION ( zCWaypoint,		zCObject, 0, 0 )
//zCLASS_DEFINITION ( zCVobMarker,	zCVob, 0, 0 )

zCLASS_DEFINITION ( zCWayNet,		zCObject, 0, 0 )

#pragma warning ( default:4244 )
