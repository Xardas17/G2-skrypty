/******************************************************************************** 
 
     $Workfile:: zCollisionMiscExtra.cpp     $                $Date:: 20.12.00 18:23   $
     $Revision:: 8                           $             $Modtime:: 20.12.00 18:23   $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:

    WARNUNG: NICHT INS PROJEKT EINFÜGEN!!!!
    Der Inhalt dieser Datei soll später in zCollisionObjectMisc.cpp und zAIPlayer.cpp integriert werden.

   created: 19.12.2000

 * $Log: /current_work/ZenGin/_Dieter/zCollisionMiscExtra.cpp $
 * 
 * 8     20.12.00 18:23 Moos
 * 
 * 7     20.12.00 17:50 Moos
 * 
 * 6     20.12.00 15:40 Moos
 * 
 * 5     20.12.00 10:12 Moos
 * 
 * 4     19.12.00 21:16 Moos
 * 
 * 3     19.12.00 17:08 Moos
 * 
 * 2     19.12.00 15:57 Moos
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 20.12.00 18:23 $)

#ifdef NEW_COLL

#include <zCore.h>
#include <zBVolume.h>
#include <zCollisionDetector.h>
#include <zCollisionObject.h>

#include <zCollisionObjectMisc.h>

#include <z3d.h>
#include <zVob.h>
#include <zPhysics.h>
#include <zWorld.h>
#include <zGrafix.h>
#include <zModel.h>

#include <zConvexCollision.h>
#include <zAIPlayer.h>

#include <oNpc.h>  // FIXME: DAS DARF in einer Engine-Datei nicht sein! Bewege die davon abhängigen Teile in o-Dateien.


/*

// Header-Änderungen:

// in zCollisionObjectMisc.h:


class zCConvexPrimitive;

class zCCollObjectCharacter : public zCCollisionObject {
	zCOLLISION_OBJECT_DECLARATION (zCCollObjectCharacter)
public:
			 zCCollObjectCharacter();
	virtual ~zCCollObjectCharacter();

	// zCCollisionObject interface
	void		zCCFASTCALL		DetectCollisionsSelf(const zCArray<zCCollisionObject*>& otherCollObjectList,	// IN
													       zCArray<zCCollisionReport*>&	collReportList);		// OUT
	void		zCCFASTCALL		CollisionResponse	(zCArray<zCCollisionReport*>& collReportList, zBOOL& simulateFurther);

    void                        FillResponse        (const zVEC3 &normal, zREAL maxdistance, const zVEC3& wishMove, zCCollisionReport* report) const;
    
    zCConvexPrimitive          *GetPrimitive        () const;


    const zMAT4                &GetFallbackTrafo    (const zMAT4 &trafoBeforeCollision, const zMAT4 &trafoNow, const zCCollisionReport *report, const zVEC3 &evadeAt) const;
    
    void                        ClearFallbackTrafo  ()                            {m_opFallbackTrafoBelongsToReport = NULL;}
    const zMAT4                &GetFallbackTrafo    (zCCollisionReport *report)   {zERR_ASSERT(report == m_opFallbackTrafoBelongsToReport); return m_oFallbackTrafo;}


	zCVob*						GetVob				() const	{ return static_cast<zCVob*>(this->GetClientData()); };

protected:
    zMAT4                       m_oFallbackTrafo;
    const zCCollisionReport    *m_opFallbackTrafoBelongsToReport;

    zCConvexPrimitive          *m_opPrimitive;
};




// in zCollisionDetector.h:

// baseClass
class zCCollisionReport {
public:
	zREAL					m_fTimeStamp;
	zPOINT3					m_oContactPoint;
	zVEC3					m_oCollNormal0;
    zVEC3                   m_oSlideVector0;
	zCCollisionObject*		m_poCollObject0;
	zCCollisionObject*		m_poCollObject1;

			 zCCollisionReport()	{ m_poCollObject0 = m_poCollObject1 = 0; };
	virtual ~zCCollisionReport()	{ m_poCollObject0 = m_poCollObject1 = 0; };
};

*/


/* ----------------------------------------------------------------------
	
     zCAIPlayer::CanStandAtPos()

     stellt fest, ob der Spieler an der Position <scanStart> prinzipiell
     stehen kann.

	 19.12.2000	[Moos]	
                aus CheckEnoughSpaceMoveDir() ausgelagert.

   ---------------------------------------------------------------------- */

// TODO: als member von zCAIPlayer eintragen und andere Tests (Platz) einbauen

zBOOL CanStandAtPos(zCAIPlayer *player, const zPOINT3 &scanStart, int commonRayFlags, zREAL &downHitY, zCPolygon*& poly)
{
    static const zVEC3	zMV_DOWN					= zVEC3(0,-100000,0);

	if (player->world->TraceRayNearestHit (scanStart, zMV_DOWN, player->vob, commonRayFlags | zTRACERAY_STAT_POLY | zTRACERAY_POLY_NORMAL | zTRACERAY_VOB_IGNORE))	// zTRACERAY_POLY_IGNORE_TRANSP 
	{
		downHitY				= player->world->traceRayReport.foundIntersection[VY];
		if (player->waterLevel==0) 
		{
			{
                poly                    = player->world->traceRayReport.foundPoly;
				const zVEC3& polyNormal = player->world->traceRayReport.foundPolyNormal;
				zREAL	slope			= polyNormal[VY]; zClamp (slope, zREAL(-1.0F), zREAL(+1.0F)); slope = zREAL(acos(slope)); 

#ifdef DEBUG_MOOS
                if (slope!=0)
                {
                    int x;
                    x = 1;
                }
#endif

				if (slope<M_PI)							// scheint noetig..
				if (slope>player->zMV_MAX_GROUND_ANGLE_WALK) 
				{ 
					// Falls ein statisches Poly mit entspr. Steigung gefunden wurde, wird noch geschaut, ob zwischen Model
					// und diesem Poly sich vielleicht ein Vob befindet, dass ein Gehen auf demselben zulassen wuerde.
					const zVEC3 rayDir = player->world->traceRayReport.foundIntersection - scanStart;
					if (!player->world->TraceRayNearestHit (scanStart, rayDir, player->vob, commonRayFlags | zTRACERAY_STAT_IGNORE)) 
					{
						// Poly gefunden, dass zum drauf gehen zu steil ist, nur .. geht es auf oder abwaerts ?
						// Nun muss ermittelt werden, ob mann die Schraege von oben oder unten betritt..
						// FIXME: hat zMV_GROUND_OFFSET Auswirkung ??
						if (player->floorY < player->world->traceRayReport.foundIntersection[VY]) {
							// Schraege aufwaerts
							return FALSE;
						} else {
							// Schraege abwaerts
							return FALSE;
						};
					};
				};
			};
		};
	};

    return TRUE;
}



zCCollObjectCharacter::zCCollObjectCharacter() : m_opPrimitive(NULL), m_opFallbackTrafoBelongsToReport(NULL)
{
};


zCCollObjectCharacter::~zCCollObjectCharacter() {
    delete m_opPrimitive; m_opPrimitive = NULL;
}


/* ----------------------------------------------------------------------
	
     zCCollisionObjectCharakter::GetPrimitive()

     beschafft die gültige Kollisionsprimitive. Wenn noch keine da
     ist, wird sie erzeugt.

	 19.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */


zCConvexPrimitive  *zCCollObjectCharacter::GetPrimitive () const{
    if (m_opPrimitive)
        return m_opPrimitive;

	zERR_ASSERT (GetVob());

	// Complex aus dem Vob/Visual herausziehen
	zCModel *model	= static_cast<zCModel*>(GetVob()->GetVisual());

	// Beide Visuals muessen Models sein
	zERR_ASSERT ( model->GetClassDef()==zCModel::GetStaticClassDef() );

    // bastle ein Ellipsoid aus der statischen BBox
    ((zCCollObjectCharacter *)this)->m_opPrimitive = zNEW (zCConvexPrimitiveEllipsoid(model->GetBBox3DCollDet(), TRUE) );

    zERR_ASSERT(m_opPrimitive);

    return m_opPrimitive;
}


/* ----------------------------------------------------------------------
	
     zCCollisionObjectCharakter::GetFallbackTrafo()

     von der zurückgegebenen Matrix aus kann die Kollisionsauflösung
     ausgehen. Rotationen werden nur um die Symetrieachsen des
     Objekts erlaubt.

     Parameter:
     trafoBeforeCollision: die garantiert gute trafo vor der Kollision
     trafoNow            : so sollte die trafo eigentlich aussehen, wenn
                           es keine Kollision gegeben hätte
     report              : der Report, zu dem die zurückgegebene m_oFallbackTrafo
                           gehören soll
     evadeAt             : vermeidet diesen Vektor als At-Vektor der zurückgegebenen
                           Matrix

	 19.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */


const zMAT4 &zCCollObjectCharacter::GetFallbackTrafo (const zMAT4 &trafoBeforeCollision, const zMAT4 &trafoNow, const zCCollisionReport *report, const zVEC3 &evadeAt) const
{
    // hoffentlich ist die m_oFallbackTrafo schon aktuell
    if (report == m_opFallbackTrafoBelongsToReport)
        return m_oFallbackTrafo;
    
    // Mist. Muss sie neu berechnen.
    zMAT4 &ret = (zMAT4 &)m_oFallbackTrafo;

    ((zCCollObjectCharacter *)this)->m_opFallbackTrafoBelongsToReport = report;

    GetPrimitive(); // danach ist m_opPrimitive auf einem gültigen Wert
    
    zVEC3 axis(0,0,0);

    if (m_opPrimitive->SymetrySphere())
    {                                                   // nur die verschiebung muss weggeworfen werden
        ret = trafoNow;
        ret.SetTranslation(trafoBeforeCollision.GetTranslation());  
    }

    else if (m_opPrimitive->SymetryRotation(axis))
    {                                                   // kompliziert: die Rotation um axis darf behalten werden

        // schnappe die inkrementelle Rotation
        zMAT3 rotBefore = ((zMAT4 &)trafoBeforeCollision).ExtractRotation();
        zMAT3 rotNow    = ((zMAT4 &)trafoNow            ).ExtractRotation();
        zMAT3 rotation  = rotNow * rotBefore.Transpose();
    
        // wandle das ding in ein Quat um
        zCQuat q;
        q.Matrix3ToQuat(rotation);
    
        // extrahiere die Rotationsachse daraus
        zVEC3 qaxis(q.qx, q.qy, q.qz);

        // und mache diese parallel zu axis
        zREAL qlen = axis * qaxis;
        //   qaxis -= axis * (qaxis * axis); [Moos] Hey! Das hat qaxis SENKRECHT zu axis gemacht.
        qaxis = qlen * axis;

        // versuche, evadeAt auszuweichen. evade_dir gibt die Richtung an und liegt zwischen -1 und 1.
        zREAL evade_dir = -(evadeAt ^ rotBefore.GetAtVector()) * (rotBefore * axis);
        
        if (evade_dir * qlen > -ztimer.GetFrameTimeF()*.00001) // korrigiere die Rotation nur, wenn nicht explizit gegengesteuert wird
        {
            // vermeide die Nullregion:
            if (evade_dir < 0 && evade_dir > -.5)
                evade_dir = -.5;

            if (evade_dir > 0 && evade_dir <  .5)
                evade_dir =  .5;

            zREAL turnSpeed = Alg_Deg2Rad(zDYNAMIC_CAST<oCNpc>(GetVob())->GetTurnSpeed());
            qaxis += evade_dir * axis * ztimer.GetFrameTimeF() * turnSpeed;
        }
    
        // stopfe sie zurück in das Qaternion. Damit beschreibt q eine Rotation um axis.
        q.qx = qaxis[VX]; q.qy = qaxis[VY]; q.qz = qaxis[VZ];

        // Sicherheit:
        if (qaxis.Length2() < .001)
            q.qw = 1;

        // mache das quat wieder normal
        q.Unit();

        // baue eine neue Matrix aus dem Quaternion und der bisherigen Trafo
        zMAT4 Q;
        Q.MakeIdentity();
        q.QuatToMatrix4(Q);
        
        ret = Q * trafoBeforeCollision;
        ret.SetTranslation(trafoBeforeCollision.GetTranslation());
    }
    else
        ret = trafoBeforeCollision;

    return m_oFallbackTrafo;
}



/* ----------------------------------------------------------------------
	
     zCCollisionObjectCharakter::FillResponse()

     Berechnet das beste Ausweichverhalten anhand der Kollisionsnormalen
     <lastNormal>, der maximal in dieser Richtung zu gehenden Strecke
     <lastDistance> und der gewünschten Bewegung <wishMove>. Die Daten
     landen in <report>, wo sie später von CollisionResponse() ausgewertet
     werden.

	 19.12.2000	[Moos]	

   ---------------------------------------------------------------------- */

void  zCCollObjectCharacter::FillResponse (const zVEC3 &lastNormal, zREAL lastDistance, const zVEC3 &wishMove, zCCollisionReport* report) const
{
#ifdef _DEBUG
    zREAL distance;
#endif
    // Sicherheit gegen Rundungsfehler:
    lastDistance -= 3;

    // zerlege die Bewegung in ihre Komponenten parralel und senkrecht zur trennebene
    zVEC3 wishMovePerp     = lastNormal * (lastNormal * wishMove);
    zVEC3 wishMoveParallel = wishMove - wishMovePerp;


    zREAL wishMoveParLen2 = wishMoveParallel.Length2();
    zREAL wishMoveLen2    = wishMove.Length2();

    // Sicherheit: mache die senkrecht zur Ebene zurückzulegende Strecke kürzer.
    if (lastDistance > 0)
    {
        lastDistance *=.5;

        if (wishMoveLen2 < lastDistance * lastDistance)
        {
            zERR_MESSAGE(2,0,"M: CHARACTER COLLISION: cutting length.");
            lastDistance = zREAL(sqrt(wishMoveLen2));
        }
    }

    // die senkrechte Komponente des evade-Vektors darf nicht durch die Ebene gehen.
    zVEC3 movePerp         = lastNormal * lastDistance;
    zVEC3 move;


    if (wishMoveParLen2 > wishMoveLen2 *.01)  // soll es überhaupt eine nennenswerte Bewegung parallel zur Kollisionsebene geben?
    {
        // berechne die Länge der parallelen Bewegung so, daß die Länge der Gesamtbewegung der gewünschten entspricht.
        zREAL moveParLen2      = wishMoveLen2 - lastDistance*lastDistance;
    
        if (moveParLen2 > 0)
        {
            zVEC3 moveParallel     = wishMoveParallel * zREAL(sqrt(moveParLen2/wishMoveParLen2));

            move             = movePerp + moveParallel;

            zERR_ASSERT((distance = move * lastNormal) <= lastDistance + 1 || lastDistance < 0);
        }
        else
        {
            zERR_MESSAGE(2,0,"M: CHARACTER COLLISION: cutting length.");
            move = movePerp;
        }
    }
    else
        move = movePerp;


    zERR_ASSERT((distance = move * lastNormal) <= lastDistance + 1 || lastDistance < 0);

    // so, Entlang move dürften wir uns nun bewegen. Aber: dabei wollen wir uns nicht in den Boden rammen!
    if (move[VY] < 0)
    {
        if (lastNormal[VY] > 0) // hoppla. wir müssen noch etwas mehr ausweichen
        {
            zVEC3 evade(lastNormal);
            evade[VY]= 0;
            zREAL le = evade.Length();
            if (le > .1)
            {
                evade   *= (1/le);
                move    += evade * ((1/(evade * lastNormal)) * move[VY] * lastNormal[VY]);
                move[VY] = 0;
            }
        }
        else
            move[VY] = 0;  // keine Gefahr.

        zERR_ASSERT((distance = move * lastNormal) <= lastDistance +1 || lastDistance < 0);

    }

    // fülle den Bericht aus.
	report->m_oCollNormal0  = lastNormal;
	report->m_oSlideVector0 = move;
}






/* ----------------------------------------------------------------------
	
    TestStatic_Char_Char()

    Npc-Npc-Kollision mittels Ellipsoiden

	 15.12.2000	[Moos]	
                Auf Ellipsoide umgebastelt

   ---------------------------------------------------------------------- */

zBOOL TestStatic_Char_Char	        (zREAL timeStamp, 
									 zCCollisionObject*  collObject0, const zMAT4& trafoObj0,
									 zCCollisionObject*  collObject1, const zMAT4& trafoObj1,
									 zCCollisionReport** ppoCollReport)
{
	const zCCollObjectCharacter*	objChar0	= static_cast<zCCollObjectCharacter*>(collObject0);
	const zCCollObjectCharacter*	objChar1	= static_cast<zCCollObjectCharacter*>(collObject1);

	zERR_ASSERT (objChar0->GetVob());
	zERR_ASSERT (objChar1->GetVob());

	// Complex aus dem Vob/Visual herausziehen
	zCModel *obj0Model	= static_cast<zCModel*>(objChar0->GetVob()->GetVisual());
	zCModel *obj1Model	= static_cast<zCModel*>(objChar1->GetVob()->GetVisual());
	if ((!obj0Model) || (!obj1Model))	return FALSE;

	// Beide Visuals muessen Models sein
	zERR_ASSERT (objChar0->GetVob()->GetVisual()->GetClassDef()==zCModel::GetStaticClassDef());
	zERR_ASSERT (objChar1->GetVob()->GetVisual()->GetClassDef()==zCModel::GetStaticClassDef());

	//
	{
        // bastle Ellipsoide aus den statischen Bounding-Boxen
        zCConvexPrimitive &e0 = *objChar0->GetPrimitive();
        zCConvexPrimitive &e1 = *objChar1->GetPrimitive();
        
        zREAL distance;
        zVEC3 normal, point;

        // hole dir den Cache und sichere die Normale daraus
        zCConvexCollisionCache *cache = zCConvexPrimitive::GetCache(objChar0->GetVob(), objChar1->GetVob());
        zVEC3              lastNormal = cache->planeNormal;

#ifdef _DEBUG
#ifdef DEBUG_MOOS
        static zVEC3 normalSave;

        if (lastNormal.Length2() > .1)
        {
            zMAT4 trafoOld = objChar0->GetTrafoOld();
            zREAL testdist = zCConvexPrimitive::Distance(&e0       , &e1               ,
                                                         trafoOld  , trafoObj1         ,
                                                         lastNormal, point, normal);

            if (testdist < 0){
                zMAT4 trafo0Diff = cache->lastGoodTrafo0.Inverse() * trafoOld;
                zMAT4 trafo1Diff = cache->lastGoodTrafo1.Inverse() * trafoObj1;
                zVEC3 normalDiff = cache->lastGoodNormal - lastNormal;

                static zBOOL reported=FALSE;
                if (reported)
                    zERR_MESSAGE(2,0,"M: Collision at initial position found!");
                else
                    zERR_FAULT("M: M: Collision at initial position found!");
                reported = TRUE;
            }
        }
#endif
#endif
        // Kollisionstest!
        zBOOL col = zCConvexPrimitive::CheckCollision(&e0               , &e1               ,
                                                      trafoObj0         , trafoObj1         ,
                                                      cache,
                                                      point, distance, normal);

#ifdef _DEBUG        
        zCOLOR color = col ? GFX_RED : GFX_YELLOW;
        e0.Draw(trafoObj0, color);
        e0.Draw(trafoObj0, color);
#endif

		if (col)
		{
			if (ppoCollReport)
			{
    			// Report besorgen (den generischen)
	    		(*ppoCollReport)					= zCCollisionDetector::S_GetNextFreeCollReport();
				// Sliding Normale berechnen
				// (muss wohl hier bereits berechnet werden, da in der CollResp einige noetige Infos nicht mehr vorliegen)
                objChar0->ClearFallbackTrafo(); // erzwinge die Neuberechnung
                const zMAT4 &trafoOld = objChar0->GetFallbackTrafo(objChar0->GetTrafoOld(), trafoObj0, *ppoCollReport, lastNormal);
				zVEC3 wishMove        = trafoObj0.GetTranslation() - trafoOld.GetTranslation();	      // wichtig: von dem movingObj muss dessen zuletzt gueltige Position genommen werden!

                // restauriere die alte Normale; bei Kollision ist die im Cache nämlich potentiell Müll.        
                if (lastNormal.Length2() >.1)
                    cache->planeNormal = lastNormal;
                else
                    lastNormal = cache->planeNormal;

                zVEC3 point, connection;
                zREAL lastDistance;

                // finde heraus, wie nahe wir dem anderen Objekt in richtung <lastNormal> noch kommen dürfen
                lastDistance = zCConvexPrimitive::Distance(&e0     , &e1      ,
                                                           trafoOld, trafoObj1,
                                                           lastNormal, point, connection);


/*                // finde heraus, wie nahe wir dem anderen Objekt in richtung <lastNormal> noch kommen dürfen
                zCConvexPrimitive::CheckCollision(&e0     , &e1      ,
                                                  trafoOld, trafoObj1,
                                                  cache,
                                                  dummy1, lastDistance, newNormal);
*/


		    	// Report ausfuellen
			    (*ppoCollReport)->m_fTimeStamp		= timeStamp;

/*
                zERR_ASSERT(lastDistance > -100); // es darf keine Kollision für die Urposition gemeldet werden
*/                  // FIXME: wir brauchen noch eine ordentliche Methode, eine anfängliche Kollision aufzulösen!

                // bereche das entsprechende Ausweichverhalten.
                objChar0->FillResponse(lastNormal, lastDistance, wishMove, *ppoCollReport);

                // teste, ob das gut ist:
                lastDistance -= (*ppoCollReport)->m_oSlideVector0 * lastNormal;

                if (lastDistance < 0){ // KLUDGE: Erlaube die Bewegung, wenn die die Kerle voneinander entfernt werden
                    static zBOOL reported=FALSE;
                    if (reported)
                        zERR_MESSAGE(2,0,"M: Trying desperately to resolve collision...");
                    else
                        zERR_FAULT("M: Trying desperately to resolve collision...");
                    reported = TRUE;

#ifndef DEBUG_MOOS
                    if (lastDistance < distance)
                    {
                        *ppoCollReport = NULL;
                        return FALSE;
                    }
#endif
                }


#ifdef _DEBUG
#ifdef DEBUG_MOOS
                normalSave = lastNormal;

                // Teste die neue Position
                zMAT4 trafoNew = objChar0->GetFallbackTrafo(*ppoCollReport);
           	    trafoNew.Translate((*ppoCollReport)->m_oSlideVector0);

                zREAL newDistance = zCConvexPrimitive::Distance(&e0, &e1,
                                                                trafoNew, trafoObj1,
                                                                lastNormal, point, connection);

                if (newDistance <= 0)
                {
                    // Finde heraus, was schieflief:
                    objChar0->ClearFallbackTrafo(); // erzwinge die Neuberechnung
                    const zMAT4 &newtrafoOld = objChar0->GetFallbackTrafo(objChar0->GetTrafoOld(), trafoObj0, *ppoCollReport, lastNormal);

                    lastDistance = zCConvexPrimitive::Distance(&e0     , &e1      ,
                                                               trafoOld, trafoObj1,
                                                               lastNormal, point, connection);

               	    zVEC3 oldslide =(*ppoCollReport)->m_oSlideVector0;
                    objChar0->FillResponse(lastNormal, lastDistance, wishMove, *ppoCollReport);
                }
#endif
#endif

    			return TRUE;
            };
		};
	};
	return FALSE;
};


/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::CollisionResponse()

     Weicht der Kollision so gut wie möglich aus; ohne Physik
     steht schon alles im Report. Mit Physik sollte eine
     schöne elastische Kollision gemacht werden.

	 17.12.2000	[Moos]	
                Erzeugt
     18.12.2000 [Moos]
                prinzipielle elastische Kollision dazu
     19.12.2000 [Moos]
                Drehungen bei der Kollisionsauflösung werden erlaubt,
                wenn Objekt symetrisch ist     

   ---------------------------------------------------------------------- */

// TODO: Echte elastische Kollision aktivieren


void zCCFASTCALL zCCollObjectCharacter::CollisionResponse	(zCArray<zCCollisionReport*>& collReportList, zBOOL& simulateFurther)
{
	if (!this->HasMoved()) return;

    // mache eine schöne elastische Kollision
    if (GetVob()->GetPhysicsEnabled()){
        zCVob *vob0 = GetVob();
        zCVob *vob1 = NULL;

        zVEC3 v0    = vob0->GetVelocity();
        zVEC3 v1    = zVEC3(0, 0, 0);

        zREAL m0    = vob0->GetRigidBody()->GetMass();
        zREAL m1    = m0 * 10000;
        
        zCCollObjectCharacter *oc = NULL;
        if (collReportList[0]->m_poCollObject1 && (collReportList[0]->m_poCollObject1->GetCollObjDef() == &s_oCollObjDef))
        {
            oc   = static_cast<zCCollObjectCharacter *>(collReportList[0]->m_poCollObject1);
            vob1 = oc->GetVob();
            v1   = vob1->GetVelocity();
            m1   = vob1->GetRigidBody()->GetMass();
        }

        m1 *= 100; // FIXME: Wenn ich rausfinde, wie man vob1 schubsen kann, kann das weg,

        zVEC3 n     = collReportList[0]->m_oCollNormal0;
        zVEC3 vdiff = v0 - v1;

        zREAL refl = n*vdiff;
        
        // schleudere ihn mit einer gewissen mindestkraft zurück
        if (refl < 100)
        {
            if (refl > -300) // übertreibe es aber nicht
                refl = 100;
            else
                refl = 0;
        }

        v0 -= 1.5 * n * refl * m1/(m0 + m1);
        v1 += 1.5 * n * refl * m0/(m0 + m1);
        
        vob0->GetRigidBody()->SetVelocity(v0);

        if (0 && vob1)
        {
            vob1->SetPhysicsEnabled(TRUE);
			vob1->GetRigidBody()->SetMode(zPHY_RBMODE_SLIDE);
            vob1->GetRigidBody()->SetVelocity(v1);
            zCModel *model = dynamic_cast<zCModel*>(vob1->GetVisual());
            static_cast<oCNpc *>(vob1)->SetBodyState	(BS_JUMP);
            if (model)
        		model->StartAni ("S_FALLDN");
        }
    }

    // hole dir die Fallback-Trafo
    SetTrafoNew(GetFallbackTrafo(GetTrafoOld(), GetTrafoNew(), collReportList[0], collReportList[0]->m_oCollNormal0));

    // und verschiebe sie noch um den Ausweich-Vector
	GetTrafoNew().Translate		(collReportList[0]->m_oSlideVector0);

	simulateFurther = TRUE;
};


/* ----------------------------------------------------------------------
	
    TestDynamic_Char_LevelPolys()

	 18.12.2000	[Moos]	
                von TestDynamic_Point_LevelPolys() geklaut, nur den 
                getesteten Punkt verschoben

     19.12.2000 [Moos]
                Test auf Bodenneigung eingebaut     

   ---------------------------------------------------------------------- */


    // TODO: Rating der position einbauen, dann Logik:
    //       von einer erlaubten Position darf man nie auf eine Verbotene
    //       von einer verbotenen Position darf man auf jede mit besserem Rating.

zBOOL TestDynamic_Char_LevelPolys(zCCollisionObject*  collObject0,
			     				  zCCollisionObject*  collObject1,
				  				  zCCollisionReport** ppoCollReport)
{
	const zCCollObjectCharacter*    objChar 	= static_cast<zCCollObjectCharacter *>(collObject0);
	const zCCollObjectLevelPolys*	objLevel	= static_cast<zCCollObjectLevelPolys*>(collObject1);

    zCAIPlayer *player = zDYNAMIC_CAST<zCAIPlayer>(objChar->GetVob()->GetAI());
    zERR_ASSERT(player);

	// Ray von old nach new gegen alle Polys testen
	const zPOINT3&	rayOrigin	= objChar->GetTrafoOld().GetTranslation();
	const zVEC3&	ray			= objChar->GetTrafoNew().GetTranslation() - objChar->GetTrafoOld().GetTranslation();

	//
	zVEC3 inters;
	zREAL alpha;
	for (int i=0; i<objLevel->m_aoPolyList.GetNum(); i++)
	{
		zCPolygon *poly = objLevel->m_aoPolyList[i];
		if (poly->CheckRayPolyIntersection (rayOrigin, ray, inters, alpha))
		{
			if (ppoCollReport)
			{
                // besorge für später schonmal die m_oFallbackTrafo
                //((zCCollObjectCharacter *)objChar)->GetFallbackTrafo(objChar->GetTrafoOld(), objChar->GetTrafoNew(), *ppoCollReport, poly->GetNormal() ,TRUE);
                ((zCCollObjectCharacter *)objChar)->ClearFallbackTrafo();

				// Report besorgen (den generischen)
				(*ppoCollReport)				= zCCollisionDetector::S_GetNextFreeCollReport();
				// Report ausfuellen
				(*ppoCollReport)->m_fTimeStamp	= alpha * zREAL(0.95F);			// etwas vom Kollisionsort wegruecken

				(*ppoCollReport)->m_oCollNormal0= poly->GetNormal();

                objChar->FillResponse(-poly->GetNormal(), 0, ray, *ppoCollReport);
			};
			return TRUE;
		};
	};

    
    // Test auf Bodenneigung. 
    
    zREAL      dummy;
    zCPolygon *groundPoly;
    if (CanStandAtPos(player, rayOrigin, 0, dummy, groundPoly) && !CanStandAtPos(player, rayOrigin+ray, 0, dummy, groundPoly))
    {
    	if (ppoCollReport)
		{
            zVEC3 normal;
            if (groundPoly)
                normal                       = groundPoly->GetNormal();
            else
                normal                       = ray;
        
            // behandle die Neigung genau wie eine senkrechte Wand.
            normal[VY]                       = 0;
            normal.                            Normalize();            

            // besorge für später schonmal die m_oFallbackTrafo
            // ((zCCollObjectCharacter *)objChar)->GetFallbackTrafo(objChar->GetTrafoOld(), objChar->GetTrafoNew(), *ppoCollReport, normal, TRUE);
            ((zCCollObjectCharacter *)objChar)->ClearFallbackTrafo();

			// Report besorgen (den generischen)
			(*ppoCollReport)     		     = zCCollisionDetector::S_GetNextFreeCollReport();
			// Report ausfuellen
			(*ppoCollReport)->m_fTimeStamp	 = 0;			// etwas vom Kollisionsort wegruecken
    
    		(*ppoCollReport)->m_oCollNormal0 = normal;
            objChar->FillResponse(-normal, 0, ray, *ppoCollReport);
		};
		return TRUE;

    }

	return FALSE;
};
#endif