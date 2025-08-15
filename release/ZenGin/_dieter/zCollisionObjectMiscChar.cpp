/******************************************************************************** 
 
     $Workfile:: zCollisionObjectMiscChar.cpp $                $Date:: 13.02.01 17:05   $
     $Revision:: 36                   $             $Modtime:: 13.02.01 16:51   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   Collection of zCCollsionObject subclasses, implementation for character stuff
   created       : 8.12.2000

 * $Log: /current_work/ZenGin/_Dieter/zCollisionObjectMiscChar.cpp $
 * 
 * 36    13.02.01 17:05 Moos
 * Diego-Bewegt-Sich-Im-OC-keinen-Millimeter-wegen-Höhenangst-Fix
 * 
 * 35    12.02.01 18:40 Hildebrandt
 * 
 * 34    6.02.01 11:43 Moos
 * 
 * 33    5.02.01 18:01 Moos
 * 
 * 32    3.02.01 2:19 Hildebrandt
 * 
 * 31    1.02.01 19:58 Moos
 * 
 * 30    1.02.01 15:32 Moos
 * 
 * 28    1.02.01 10:58 Moos
 * 
 * 27    31.01.01 14:56 Moos
 * 
 * 26    30.01.01 20:23 Moos
 * 
 * 25    29.01.01 17:31 Hildebrandt
 * 
 * 24    28.01.01 20:17 Moos
 * 
 * 23    26.01.01 15:02 Moos
 * 
 * 22    26.01.01 13:08 Moos
 * 
 * 21    22.01.01 20:01 Moos
 * 
 * 20    19.01.01 21:20 Moos
 * 
 * 19    19.01.01 11:42 Moos
 * 
 * 18    17.01.01 1:46 Hildebrandt
 * 
 * 17    16.01.01 18:18 Moos
 * 
 * 16    16.01.01 3:31 Hildebrandt
 * 
 * 15    15.01.01 20:26 Hildebrandt
 * 
 * 14    15.01.01 20:15 Moos
 * 
 * 13    15.01.01 3:55 Hildebrandt
 * 
 * 12    14.01.01 16:36 Hildebrandt
 * 
 * 11    12.01.01 15:28 Moos
 * 
 * 10    12.01.01 12:39 Moos
 * 
 * 9     12.01.01 3:23 Hildebrandt
 * 
 * 8     11.01.01 19:11 Moos
 * 
 * 7     11.01.01 18:45 Hildebrandt
 * 
 * 6     22.12.00 0:29 Hildebrandt
 * 
 * 5     22.12.00 0:23 Hildebrandt
 * illegale includes von o*.h Files entfernt
 * 
 * 4     21.12.00 21:24 Moos
 * 
 * 3     21.12.00 16:07 Moos
 * 
 * 2     20.12.00 21:15 Moos
 * 
 * 1     20.12.00 19:19 Hildebrandt
 * 
 * 1     20.12.00 19:11 Hildebrandt
 * 
 * 7     20.12.00 3:03 Hildebrandt
 * 
 * 6     15.12.00 3:55 Hildebrandt
 * 
 * 5     14.12.00 20:56 Hildebrandt
 * 
 * 4     14.12.00 20:43 Hildebrandt
 * 
 * 3     13.12.00 3:24 Hildebrandt
 * 
 * 2     9.12.00 6:31 Hildebrandt
 * 
 * 1     8.12.00 21:29 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 36 $ ($Modtime: 13.02.01 16:51 $)

// ============================================================================================================

#include <zCore.h>
#include <zBVolume.h>
#include <zVob.h>
#include <zGrafix.h>
#include <zModel.h>
#include <zWorld.h>
#include <zVobMisc.h>

#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

// ============================================================================================================

#include <zConvexCollision.h>
#include <zPhysics.h>

// ============================================================================================================

// Debug Outputs

#ifdef DEBUG_HILDEBRANDT
//	#define zMV_DEBUG
#endif

#ifdef zMV_DEBUG
#include <zView.h>
	static inline void Print		(const zSTRING& s) 							{ zerr.Message		("D: COLL_OBJ_CHAR: "+s);	};
	static inline void Line3D		(const zVEC3& a, const zVEC3& b, int col) 	{ zlineCache.Line3D (a,b,col);					};
	static inline void PrintScreen	(int xscr, int yscr, zSTRING s) 			{ screen->Print		(xscr, yscr, s);			};
#else
	static inline void Print		(const zSTRING& s) 							{ };
	static inline void Line3D		(const zVEC3& a, const zVEC3& b, int col) 	{ };
	static inline void PrintScreen	(int xscr, int yscr, zSTRING s) 			{ };
#endif

// ============================================================================================================

#define zMV_UP							(zVEC3(0,+100000,0))
#define zMV_DOWN						(zVEC3(0,-100000,0))
#define zMV_GROUND_OFFSET				(zREAL(0.5F))
#define zMV_WALLSLIDE_ANGLE				(zREAL(25))
#define zMV_WALLSLIDE_TURN_VELOCITY		(zREAL(0.14F))

// ============================================================================================================


zCCollObjectCharacter::zCCollObjectCharacter() : 
	m_poPrimitiveCC		(NULL), 
	m_fWallSlideTimer	(0),
	m_fWallSlideRotDir	(0),
	m_oWallSlideRotAxis	(0),
	m_fFeetYLocal		(0),
	m_fHeadYLocal		(0)

{
	m_oInterferenceReport.Clear	();
	memset						(&m_oConfig			, 0, sizeof(m_oConfig));
	memset						(&m_oSpatialState	, 0, sizeof(m_oSpatialState));

    m_oSpatialState.m_bIsUninited = TRUE;  // [Moos] mache den SpatialState explizit ungültig

	m_oConfig.m_bUseSpacingRays	= TRUE;
};


zCCollObjectCharacter::~zCCollObjectCharacter() 
{
    delete m_poPrimitiveCC; m_poPrimitiveCC = NULL;
}


// ============================================================================================================
// *** START ***
// CollDetection und CollResponse fuer: 
//		zCCollObjectCharacter <=> zCCollObjectCharacter
// ============================================================================================================

/* ----------------------------------------------------------------------
	
	zCCollObjectCharacter::GetPrimitiveCC()

     beschafft die gültige Kollisionsprimitive. Wenn noch keine da
     ist, wird sie erzeugt.

	 19.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

zCConvexPrimitive  *zCCollObjectCharacter::GetPrimitiveCC () const
{
    if (m_poPrimitiveCC)
        return m_poPrimitiveCC;

    zCVob *vob = GetVob();
	zERR_ASSERT (vob);

	// Complex aus dem Vob/Visual herausziehen
	zCModel *model	= static_cast<zCModel*>(vob->GetVisual());

	// das Visual muuss ein Model sein
	zERR_ASSERT ( model && model->GetClassDef()==zCModel::GetStaticClassDef() );

    // bastle ein Ellipsoid aus der statischen BBox
    ((zCCollObjectCharacter *)this)->m_poPrimitiveCC = zNEW (zCConvexPrimitiveEllipsoid(model->GetBBox3DCollDet(), TRUE) );

    zERR_ASSERT(m_poPrimitiveCC);

    // vergrößere das Ding, wenn angegeben
    zCConvexPrimitiveScaleTrans *p = dynamic_cast<zCConvexPrimitiveScaleTrans*>(m_poPrimitiveCC);
    if (p)
        p->Scale(this->S_GetSourceBBoxScaler());

    m_poPrimitiveCC->UpdateBBox();

    return m_poPrimitiveCC;
}


/* ----------------------------------------------------------------------
	
     zCCollisionObjectCharakter::GetFallbackTrafoCC()

     von der zurückgegebenen Matrix aus kann die Kollisionsauflösung
     ausgehen. Rotationen werden nur um die Symetrieachsen des
     Objekts erlaubt.

     Parameter:
     trafoBeforeCollision: die garantiert gute trafo vor der Kollision
     trafoNow            : so sollte die trafo eigentlich aussehen, wenn
                           es keine Kollision gegeben hätte
     evadeAt             : vermeidet diesen Vektor als At-Vektor der zurückgegebenen
                           Matrix
     rotateFree          : erlaube freie Rotation um die Y-Achse; sonst nur um Symetrieachsen

	 19.12.2000	[Moos]	
                erzeugt
	 6.1.2001	[HILDEBRANDT]	
                effizientere Rueckgabe der Ergebnis Matrix

   ---------------------------------------------------------------------- */


void zCCollObjectCharacter::GetFallbackTrafoCC(	const zMAT4 &trafoBeforeCollision,	// IN
												const zMAT4 &trafoNow, 
												const zVEC3 &evadeAt, 
												const zBOOL	rotateFree,
												zMAT4		&ret					// OUT
												) const
{
    GetPrimitiveCC();			// danach ist m_poPrimitiveCC auf einem gültigen Wert
    
    zVEC3 axis(0,1,0);			// default: Y-Achse

    if (m_poPrimitiveCC->SymetrySphere())
    {                                                   // nur die verschiebung muss weggeworfen werden
        ret = trafoNow;
        ret.SetTranslation(trafoBeforeCollision.GetTranslation());  
    }

    else if (m_poPrimitiveCC->SymetryRotation(axis) || rotateFree)
    {   // kompliziert: die Rotation um axis darf behalten werden

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
// [HILDEBRANDT]
			qaxis += evade_dir * axis * ztimer.GetFrameTimeF() * TurnSpeed();
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
}


/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::Slide()

     Berechnet den besten Ausweichvektor anhand der Kollisionsnormalen
     <lastNormal>, der maximal in dieser Richtung zu gehenden Strecke
     <lastDistance> und der gewünschten Bewegung <wishMove>. Die Daten
     landen in <report>, wo sie später von CollisionResponse() ausgewertet
     werden.

	 19.12.2000	[Moos]	

   ---------------------------------------------------------------------- */

zVEC3 zCCollObjectCharacter::S_SlideCC (const zVEC3 &lastNormal, zREAL lastDistance, const zVEC3 &wishMove)
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
//            zERR_MESSAGE(2,0,"M: CHARACTER COLLISION: cutting length.");
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
//            zERR_MESSAGE(2,0,"M: CHARACTER COLLISION: cutting length.");
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

    return move;
}


/* ----------------------------------------------------------------------
	
    TestStatic_Char_Char()

    Char-Char-Kollision mittels Ellipsoiden

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


    if (objChar0->IsDead() || objChar1->IsDead())
        return FALSE;

    zREAL dist2     = (trafoObj0.GetTranslation()               - trafoObj1.GetTranslation()).Length2();
    zREAL lastDist2 = (objChar0->GetTrafoOld().GetTranslation() - trafoObj1.GetTranslation()).Length2();

    if (dist2 < .1)  // AAAARRRGH! Notfall! Die kerle kleben aneinander.
    {
        if ( dist2 > lastDist2 )
             return TRUE;

#ifdef _DEBUG
		// nimm doch einfach FAULT_ONCE ;)
		zERR_FAULT_ONCE ("zwei NPCs hängen direkt aneinander!");
#endif
    
	    (*ppoCollReport)					= zCCollisionDetector::S_GetNextFreeCollReport();

		// Report ausfuellen
		(*ppoCollReport)->m_fTimeStamp		=  timeStamp;
        (*ppoCollReport)->m_oCollNormal0    =  zVEC3(0,1,0);
        (*ppoCollReport)->m_oCollNormal1    =  zVEC3(0,-1,0);
        (*ppoCollReport)->m_oContactPoint   =  trafoObj1.GetTranslation();

    	return TRUE; 
    }


    if (dist2 < lastDist2 && objChar1->DontLetHimComeNearer( objChar0->GetVob() ) )
    {
//        char1 verbietet char2 das Näherkommen. Also gut...
	    (*ppoCollReport)					= zCCollisionDetector::S_GetNextFreeCollReport();

		// Report ausfuellen
		(*ppoCollReport)->m_fTimeStamp		=  timeStamp;
        (*ppoCollReport)->m_oCollNormal0    =  trafoObj0.GetTranslation() - trafoObj1.GetTranslation();
        (*ppoCollReport)->m_oCollNormal0   *=  -zREAL(1/sqrt(dist2));
        (*ppoCollReport)->m_oCollNormal1    =  -(*ppoCollReport)->m_oCollNormal0;
        (*ppoCollReport)->m_oContactPoint   =  (trafoObj0.GetTranslation() - trafoObj1.GetTranslation())*.5F;

    	return TRUE; 
    }

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
        zCConvexPrimitive &e0 = *objChar0->GetPrimitiveCC();
        zCConvexPrimitive &e1 = *objChar1->GetPrimitiveCC();
        
        zREAL distance;
        zVEC3 normal, point;

        // hole dir den Cache und sichere die Normale daraus
        zCConvexCollisionCache *cache = zCConvexPrimitive::GetCache(objChar0->GetVob(), objChar1->GetVob());
        zVEC3              lastNormal = cache->planeNormal;

        if (lastNormal.Length2() < .8) // Hole eine default-Normale
        {
            lastNormal = trafoObj1.GetTranslation() - trafoObj0.GetTranslation();
            lastNormal.NormalizeSafe();
        }

        const zMAT4 &trafoOld = objChar0->GetTrafoOld();
        zVEC3 posOld          = trafoOld.GetTranslation();

#ifdef _DEBUG
#ifdef DEBUG_MOOS
        static zVEC3 normalSave;

        if (lastNormal.Length2() > .1)
        {
            zREAL testdist = zCConvexPrimitive::Distance(&e0       , &e1               ,
                                                         trafoOld  , trafoObj1         ,
                                                         lastNormal, point, normal);
            if (testdist < 0)
			{
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

#ifdef DEBUG_MOOS
#ifdef _DEBUG        
        zCOLOR color = col ? GFX_RED : GFX_YELLOW;
        e0.Draw(trafoObj0, color);
        e0.Draw(trafoObj0, color);
#endif
#endif

		if (col)
		{
            // besser als im letzten Frame? akzeptiere es.
            if (normal * (posOld - trafoObj0.GetTranslation()) > 0)
                return FALSE;

			if (ppoCollReport)
			{
    			// Report besorgen (den generischen)
	    		(*ppoCollReport)					= zCCollisionDetector::S_GetNextFreeCollReport();

		    	// Report ausfuellen
			    (*ppoCollReport)->m_fTimeStamp		=  timeStamp;
                (*ppoCollReport)->m_oCollNormal0    =  lastNormal;
                (*ppoCollReport)->m_oCollNormal1    = -lastNormal;
                (*ppoCollReport)->m_oContactPoint   =  point;

                // restauriere die alte Normale; bei Kollision ist die im Cache nämlich potentiell Müll.        
                if (lastNormal.Length2() >.1)
                    cache->planeNormal = lastNormal;
                else
                    lastNormal = cache->planeNormal;

    			return TRUE;
            };
		};
	};
	return FALSE;
};

// ============================================================================================================
// *** ENDE ***
// CollDetection und CollResponse fuer: 
//		zCCollObjectCharacter <=> zCCollObjectCharacter
// ============================================================================================================

/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::GetCollisionPoleYDims()

	 6.1.2001	[HILDEBRANDT]	
				erstellt

   ---------------------------------------------------------------------- */

void zCCFASTCALL zCCollObjectCharacter::GetCollisionPoleYDims (zREAL &miny, zREAL &maxy) const
{
	zCModel *model				= static_cast<zCModel*>(GetVob()->GetVisual());
	#ifdef _DEBUG
		zERR_ASSERT				(GetVob());
		model					= zDYNAMIC_CAST<zCModel>(GetVob()->GetVisual());
		zERR_ASSERT				(model);
	#endif
	const zTBBox3D& protoBBox3D = model->GetBBox3DLocalFixed();
	miny						= protoBBox3D.mins[VY];
	maxy						= protoBBox3D.maxs[VY];
};

/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::CalcSlideVector 

	 10.1.2001	[HILDEBRANDT]	
				erstellt

   ---------------------------------------------------------------------- */

zBOOL zCCFASTCALL zCCollObjectCharacter::CalcSlideVector   (const zVEC3		&transDelta,			// IN
															const zVEC3		&collNormal, 
															zVEC3			&slideVectorOut,		// OUT
															zVEC3			&slideRotAxisOut,
															zREAL			&slideRotDirOut)
{ 
	// Methode ist von folgenden Objekt-Zustaenden abhaengig:
	//	GetConfig().m_eState

	// Wall-Slides werden NICHT als Collisions an die AI gemeldet !

	// Wall-Sliding
	if (GetConfig().m_eState==zCONFIG_STATE_DIVE)
	{ 
		// zCONFIG_STATE_DIVE
		// 
		zVEC3		heading				=-transDelta;		heading.NormalizeApprox(); 
		const zREAL	angle				= Alg_Rad2Deg		(Alg_AngleUnitRad (heading, collNormal));

		// Relativ-Winkel des Hindernises gegenueber der Heading-Richtung testen
		if ((angle>zMV_WALLSLIDE_ANGLE) && (angle<140)) 
		{
			// Projektion des vel-Vectors auf die collNormal
			slideVectorOut				= ((-transDelta)^collNormal)^collNormal;
			slideVectorOut				+= 1.0*collNormal;

			// Rotations-Axis
			const zVEC3& rotAxis		= collNormal^slideVectorOut;
			const zREAL& rotLen			= rotAxis.Length();
			if (rotLen==0)				return FALSE;

			slideRotAxisOut				= (rotAxis / rotLen);

			// Rotate
			// Muss das Model nach links oder rechts ausweichen ?
			const zREAL dot				= (slideRotAxisOut^collNormal) * -heading;	// FIXME: geht schneller !!
			slideRotDirOut				= dot;

			return TRUE;
		};
	} else 
	{
		// zMV_STATE_SWIM, zMV_STATE_STAND, zMV_STATE_FLY
		zVEC3 cdNormal = collNormal;
		if (cdNormal[VY]!=0) {
			cdNormal[VY] = 0;
			cdNormal.NormalizeApprox();	
		};

		zVEC3		heading				=-transDelta;		heading[VY]=0; heading.NormalizeApprox(); 
		const zREAL angle				= Alg_Rad2Deg (Alg_AngleUnitRad (heading, cdNormal));

		// Relativ-Winkel des Hindernises gegenueber der Heading-Richtung testen
		if ((angle>zMV_WALLSLIDE_ANGLE) && (angle<140)) 
		{
			// Projektion des vel-Vectors auf die collNormal
			zVEC3 vel					=-transDelta;
			vel[VY]						= 0;
			slideVectorOut				= (vel^cdNormal)^cdNormal;
			slideVectorOut				+= 1.0*cdNormal;

			// Rotate
 			// Muss das Model nach links oder rechts ausweichen ?
			// zREAL	dot				= (zVEC3(0,1,0)^cdNormal) * -heading;		
			zREAL		dot				= (heading[VZ]*cdNormal.n[VX] - cdNormal.n[VZ]*heading[VX]);
			slideRotAxisOut				= zVEC3(0,1,0);
			slideRotDirOut				= dot;

			return TRUE;
		};
	};
	return FALSE;						
};

/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::DoWallSlidingLatentRotation()

	 10.1.2001	[HILDEBRANDT]	
				erstellt

   ---------------------------------------------------------------------- */

void zCCFASTCALL zCCollObjectCharacter::DoWallSlidingLatentRotation (zMATRIX4 &trafoIn)
{
	// WallSliding: ROTATION
	if (m_fWallSlideTimer>0) 
	{
		zREAL rotAngle			= zMV_WALLSLIDE_TURN_VELOCITY * ztimer.GetFrameTimeF();
		if (m_fWallSlideRotDir>=0)	rotAngle = -rotAngle;

		//
		const zVEC3& oldTrans	= trafoIn.GetTranslation();
		trafoIn.SetTranslation	(0);														// FIXME: RotateY (rotVal) ?
		trafoIn					= Alg_Rotation3DN (m_oWallSlideRotAxis, rotAngle) * trafoIn;	// FIXME: optmierbar (nur der 3x3 Rot-Teil wird modifiziert...)
		trafoIn.SetTranslation	(oldTrans);

		//
		m_fWallSlideTimer		-= ztimer.GetFrameTimeF();
	};
};

/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::FindFloorWaterCeiling()

	 6.1.2001	[HILDEBRANDT]	
				erstellt

   ---------------------------------------------------------------------- */

void zCCFASTCALL zCCollObjectCharacter::FindFloorWaterCeiling	(const zPOINT3&		testLocation,	// IN
																 zTSpatialState&	spatialState)	// OUT
{
	// berechnet zTSpatialState: 
	// m_fFloorY, m_fWaterY, m_fCeilingY, m_fLastFloorY, m_poFloorPoly, m_poWaterPoly

	// Variablen: floorY - waterY - ceilingY
	// floorY	: ist immer der feste Boden
	// waterY	: falls vorhanden die einzige Wasseroberflaeche zw. floor & ceiling
	//			  falls kein Wasser: waterY=floorY
	// ceilingY	: ist immer die feste Decke, nur beim Tauchen ist ceilingY=waterY

    spatialState.m_bIsUninited  = FALSE;

	zCVob		*thisVob		= GetVob();
	zCWorld		*world			= thisVob->GetHomeWorld();

	spatialState.m_poCeilingPoly= 0;
	spatialState.m_poWaterPoly	= 0;

	// Floor messen
	// [EDENFELD] Addon: Projektile (Pfeile und Magiesprüche) dürfen hier _nicht_ bei der Floor/Ceiling
	// Findung berücksichtigt werden, da ansonsten die Bodenhöhe aus dem Projektil bei Aufprall falsch berechnet
	// wird (Bloodfly poppt nach oben bei Treffer Bug)
	world->TraceRayNearestHitCache(testLocation, zMV_DOWN, thisVob, zTRACERAY_STAT_POLY				| 
										 							zTRACERAY_VOB_IGNORE_CHARACTER	| 
																	zTRACERAY_VOB_IGNORE_NO_CD_DYN	| 
																	zTRACERAY_VOB_IGNORE_PROJECTILES|
																	zTRACERAY_POLY_TEST_WATER,		
																	&m_oDownRayCache);
	
	if (!world->traceRayReport.foundHit) 
	{
		spatialState.m_fFloorY		= spatialState.m_fLastFloorY;
		spatialState.m_fCeilingY	= zREAL_MAX;
		spatialState.m_poFloorPoly	= 0;
	} else 
	{
		const zVEC3& rayIntersection= world->traceRayReport.foundIntersection;
		spatialState.m_fLastFloorY	= spatialState.m_fFloorY;
		spatialState.m_fFloorY		= rayIntersection[VY] + zMV_GROUND_OFFSET;
		spatialState.m_fWaterY		= spatialState.m_fFloorY;
		spatialState.m_poFloorPoly	= world->traceRayReport.foundPoly; 
		spatialState.m_bFloorIsStair= (world->traceRayReport.foundVob!=0) && 
									  (world->traceRayReport.foundVob->GetClassDef()==zCVobStair::GetStaticClassDef());
		Line3D						(testLocation, rayIntersection, GFX_YELLOW);
		// Wasser-Boden ?
		if ((spatialState.m_poFloorPoly)												&&
			(spatialState.m_poFloorPoly->GetMaterial())									&&
			(spatialState.m_poFloorPoly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER)&&
			(!GetConfig().m_bTreatWaterAsSolid)								// Wasser komplett ignorieren?
		   )
		{
			// ja, Boden ist ein Wasser-Poly
			// Wassertiefe messen
			// FIXME: floor messen & WasserTiefe koennte mann mit _1_ spezial TrayRay Route messen !
			
			spatialState.m_poWaterPoly	= spatialState.m_poFloorPoly;
			spatialState.m_fWaterY		= rayIntersection[VY];
			world->TraceRayNearestHitCache (testLocation, zMV_DOWN,thisVob,	zTRACERAY_STAT_POLY | 
																			zTRACERAY_VOB_IGNORE_CHARACTER |
																			zTRACERAY_VOB_IGNORE_NO_CD_DYN |
																			zTRACERAY_VOB_IGNORE_PROJECTILES,
																			&m_oDownRayCache);

			const zVEC3& rayIntersection= world->traceRayReport.foundIntersection;
			if (!world->traceRayReport.foundHit) 
			{
				Print ("A. no under-water-floor");
			};
			Line3D (zVEC3(testLocation[VX], spatialState.m_fWaterY, testLocation[VZ]) , rayIntersection, GFX_ORANGE);
			spatialState.m_fFloorY			= rayIntersection[VY];
			spatialState.m_poFloorPoly		= world->traceRayReport.foundPoly; 
		};
		spatialState.m_bFloorIsVob			= (world->traceRayReport.foundVob!=0);

		// Auto-Link: ist Boden ein Mover und soll Character daran gelinkt werden ?
		if (spatialState.m_bFloorIsVob) {
			zCVob::CheckAutoLink (thisVob, world->traceRayReport.foundVob);
		};
	}

	// Ceiling messen
	{
		{
			world->TraceRayNearestHitCache	(testLocation, zMV_UP, thisVob,	zTRACERAY_STAT_POLY				| 
									    									zTRACERAY_VOB_IGNORE_CHARACTER	| 
										    								zTRACERAY_VOB_IGNORE_NO_CD_DYN	|
											    							zTRACERAY_POLY_TEST_WATER		|
																			zTRACERAY_VOB_IGNORE_PROJECTILES,
																			&m_oUpRayCache);
		};
		if (!world->traceRayReport.foundHit) 
		{
			spatialState.m_fCeilingY	= zREAL(1000000.0F);
			spatialState.m_poCeilingPoly= 0;
		} else 
		{
			const zVEC3& rayIntersection= world->traceRayReport.foundIntersection;
			spatialState.m_fCeilingY	= rayIntersection[VY] -zMV_GROUND_OFFSET;
			spatialState.m_poCeilingPoly= world->traceRayReport.foundPoly; 
			if (spatialState.m_poCeilingPoly || world->traceRayReport.foundVob) 
			{
				// Wasser-Decke ?
				if ((spatialState.m_poCeilingPoly && spatialState.m_poCeilingPoly->GetMaterial())
					&& (spatialState.m_poCeilingPoly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER) 
					&& (!GetConfig().m_bTreatWaterAsSolid))					// Wasser komplett ignorieren?
				{
					// ja, Decke ist ein Wasser-Poly
					// Wassertiefe messen
					spatialState.m_poWaterPoly	= spatialState.m_poCeilingPoly;
					spatialState.m_fWaterY	
                    	= spatialState.m_fCeilingY;

					// wirkliches ceilingY ermitteln
					world->TraceRayNearestHitCache (testLocation, zMV_UP,thisVob,	zTRACERAY_VOB_IGNORE_CHARACTER | 
																					zTRACERAY_VOB_IGNORE_NO_CD_DYN | 
																					zTRACERAY_VOB_IGNORE_PROJECTILES,
																					&m_oUpRayCache);
					spatialState.m_fCeilingY	= (world->traceRayReport.foundHit) ? world->traceRayReport.foundIntersection[VY] : zREAL_MAX;
				} else
				{
					// Wasser-Tunnel? => waterY auf einen Wert oberhalb der Decke setzen
					if ((spatialState.m_fWaterY==spatialState.m_fFloorY) && (this->GetConfig().m_eState==zCONFIG_STATE_DIVE))
					{
						spatialState.m_fWaterY	= spatialState.m_fCeilingY + zREAL (100000);
					};

				};
			};
		};
	}; 
};

/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::MarkSpatialStateAsUnitited()

     Sorgt dafür, dass der SpatialState bei nächster Gelegenheit
     (bei parameter TRUE: sofort) neu berechnet wird.

	 13.2.2001	[Moos]
				erstellt

   ---------------------------------------------------------------------- */

void zCCollObjectCharacter:: MarkSpatialStateAsUninited(zBOOL createImmediately){
    m_oSpatialState.m_bIsUninited = TRUE;

    if (createImmediately)
        FindFloorWaterCeiling	(GetVob()->GetPositionWorld(), m_oSpatialState);
}

/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::TestHardCollisions()

	 6.1.2001	[HILDEBRANDT]	
				erstellt

   ---------------------------------------------------------------------- */

zBOOL zCCFASTCALL zCCollObjectCharacter::TestHardCollisions (	const zVEC3&	transOld,			// IN
																const zVEC3&	transNew,
																zVEC3&			transOut,			// OUT
																zTSpatialState&	spatialStateOut,
																zVEC3&			collisionNormalOut)	
{
	// return value: TRUE= Collision, (resetToOld!), FALSE= couldMove

	// 1) Ray von A nach B casten,										fail?=> anhand des Alphas neues B berechnen
	// 2) Boden/Deckenhoehe bei B analysieren, auf genug Y Platz testen,fail?=> B ungueltig, A gueltig, fertig (evtl. wallSlide als Response)
	// 3) Neigung des Bodenpolys					(=> slide, bounce, reject[Poly hier wie senkrechte Wand behandeln])
	// 4) ueberwundener Hoehenunterschied zu groß? (nachoben)		(macht ggfs. gesamte Bewegung ungueltig)
	// 5) ueberwundener Hoehenunterschied zu groß? (nach unten) ?	(z.B. Abgrund)
	// 6) Hoehenkorrektur wg. Bodenhaftung			

	//
	zCVob	*thisVob	= GetVob();
	zCWorld *world		= thisVob->GetHomeWorld();
	transOut			= transNew;

	// 1) Ray von Old nach New casten
	{
		const zVEC3& ray = (transNew - transOld);
		if (world->TraceRayNearestHit (transOld, ray, thisVob,	zTRACERAY_STAT_POLY		| 
																zTRACERAY_POLY_NORMAL	| 
																zTRACERAY_VOB_IGNORE_NO_CD_DYN))
		{
			zREAL rayLen2	= ray.Length2();
			if (rayLen2!=0)
			{
				zREAL alpha	= (world->traceRayReport.foundIntersection - transOld).Length2() / rayLen2;
				alpha		*= zREAL(0.95F);			// etwas vom Kollisionsort wegruecken
				transOut	= transOld + alpha*ray;
				Print		("HC: vobCenter hits solidPoly");
				m_oInterferenceReport.blocking.centerRayCollided	= TRUE; 
                collisionNormalOut = world->traceRayReport.foundPolyNormal;
			};
		};
	};

	// 2) Boden/Deckenhoehe bei B analysieren, auf genug Y Platz testen
	{
		FindFloorWaterCeiling	(transOut, spatialStateOut);
		// genug Platz fuer Character zwischen Boden und Decke?
		const zREAL freeHeight	= spatialStateOut.m_fCeilingY-spatialStateOut.m_fFloorY;
		if (freeHeight <= GetCollisionPoleYHeight())
		{
			Print					("HC: ceiling too low: "+zSTRING((spatialStateOut.m_fCeilingY - spatialStateOut.m_fFloorY),4)+" / "+zSTRING(GetCollisionPoleYHeight(),4));
			transOut				= transOld;

            collisionNormalOut = zVEC3(0,0,0);
			if (spatialStateOut.m_poCeilingPoly)	collisionNormalOut	   += spatialStateOut.m_poCeilingPoly->GetNormal();
			if (spatialStateOut.m_poFloorPoly)	    collisionNormalOut	   += spatialStateOut.m_poFloorPoly->GetNormal();
			if (collisionNormalOut.Length2()<.01)   collisionNormalOut		= (transOut-transOld);

			collisionNormalOut[VY]	= 0;
			collisionNormalOut.NormalizeApprox();
			m_oInterferenceReport.blocking.lowCeiling	= TRUE; 
			return TRUE;
		};
	};

	// Moegliche Config States: STAND, FLY, SLIDE, SWIM, DIVE

	// 3) Neigung des Bodenpolys analysieren
	//    (nur noetig, falls Bodenkontakt besteht)		STAND
	if (GetConfig().m_eState==zCONFIG_STATE_STAND)
	{
		if (spatialStateOut.m_poFloorPoly)
		{
			const zREAL slopeRad = S_CalcFloorSlopeRad (spatialStateOut.m_poFloorPoly->GetNormal()[VY]);
			if (slopeRad<M_PI)							// scheint noetig..
			if (slopeRad>m_oConfig.m_fMaxGroundAngleWalk) 
			{ 
				// Situation: Char will auf ein geneigtes BodenPoly, das so steil ist, dass er 
				// nicht drauf gehen kann. 
				// Nun muss ermittelt werden, ob mann die Schraege von oben oder unten betritt..
				zBOOL goingUp = FALSE;
				{
					const zVEC3& vel		= transOut - transOld;
					goingUp					= ((spatialStateOut.m_poFloorPoly->GetNormal()*vel)<0);
				}; 
				if (goingUp) 
				{
					// Schraege aufwaerts
					Print						("HC: slope too high (up): "+zSTRING(Alg_Rad2Deg(slopeRad),4));
					transOut					= transOld;
					collisionNormalOut			= spatialStateOut.m_poFloorPoly->GetNormal();
					collisionNormalOut[VY]		= 0;
					collisionNormalOut.NormalizeApprox();
					m_oInterferenceReport.blocking.floorTooSteepUp	= TRUE; 
					return TRUE;
				} else 
				{
					// Schraege abwaerts
					if (GetConfig().m_bFloorTooLowIsHardCollision)
					{
						Print						("HC: slope too high (down): "+zSTRING(Alg_Rad2Deg(slopeRad),4));
						transOut					= transOld;
						collisionNormalOut			= -spatialStateOut.m_poFloorPoly->GetNormal();
						collisionNormalOut[VY]		= 0;
						collisionNormalOut.NormalizeApprox();
						m_oInterferenceReport.blocking.floorTooSteepDown= TRUE; 
						return TRUE;
					};
				};
			};
		};
	};

	if ((GetConfig().m_eState==zCONFIG_STATE_STAND) || 
		(GetConfig().m_eState==zCONFIG_STATE_SLIDE) ||
		(GetConfig().m_eState==zCONFIG_STATE_SWIM))
	{
		zREAL	poleMiny, poleMaxy;
		GetCollisionPoleYDims		(poleMiny, poleMaxy);
		zREAL	feetY				= (transOut[VY] - (-poleMiny));
		zREAL	aboveFloor			= (feetY		- spatialStateOut.m_fFloorY);

		zREAL	feetYLastFrame		= (GetTrafoOld().GetTranslation()[VY] - (-poleMiny));
		zREAL	aboveFloorLastFrame	= (feetYLastFrame - this->m_oSpatialState.m_fFloorY);

		if (GetConfig().m_eState==zCONFIG_STATE_STAND)
		{
			// 4) ueberwundener Hoehenunterschied zu groß (nach oben) ?	(z.B. zu hohe Treppenstufe)
			//    (macht ggfs. gesamte Bewegung ungueltig)		// STAND
			{
				// Die neue Position nur als illegal Werten, wenn die HoehenDiffererenz jetzt gerade zu gross ist,
				// aber letzten Frame ok war. (noetig, damit ein Char, der beim spawnen halb im Level steckt auch
				// durch folgende Hoehenkorrektur korrigiert werden kann)
				if ((aboveFloor<-GetConfig().m_fStepHeight) && (aboveFloorLastFrame>=-GetConfig().m_fStepHeight))
				{
					// Character muesste an neuer Position um xx cm nach oben 'poppen'. Da das ist zuviel ist,
					// ist eine Bewegung an den Zielort B nicht moeglich.
					transOut	= transOld; 
					m_oInterferenceReport.blocking.floorTooHigh	= TRUE; 
					return TRUE;
				};
			};

			// 5) ueberwundener Hoehenunterschied zu groß (nach unten) ? (z.B. Abgrund)
			//	  (macht ggfs. gesamte Bewegung ungueltig)		// STAND

			// [EDENFELD] folgendes Problem tritt hier bei den Harpien und allem was fliegt auf:
			// Für die Wegsuche wird im InterferenceReport eingetragen, ob die Distanz der Füsse zum Boden zu hoch ist (damit die Wegsuche ggfs. einen Sprung initiieren kann). 
			// Ist dies der Fall, wird der Bodenkontakt im nächsten Code-Block nicht mehr hergestellt, da 
			// zCAIPlayer::CheckPhysics() dafür verantwortlich ist, die Physik in diesem Falle anzuwerfen um die Distanz zum Boden
			// wieder zu verringern.
			// Dies schlägt dort aber fehl.
			// Vermutliche Ursache: Height Correction Code weiter unten
			{
                zREAL lastFloorY = GetSpatialState().m_fFloorY;
                if (feetY < lastFloorY)
                    lastFloorY = feetY; // [Moos] Fix gegen Höhenangst, wenn der alte SpatialState noch Müll enthalten sollte

				if ((GetConfig().m_bFloorTooLowIsHardCollision) &&
					(lastFloorY  - spatialStateOut.m_fFloorY >GetConfig().m_fStepHeight))  // [Moos] Betrachte nur den wirklichen Schritt nach unten
//					(aboveFloor>GetConfig().m_fStepHeight))
				{
					transOut	= transOld; 
					m_oInterferenceReport.blocking.floorTooLow = TRUE; 
					return TRUE;
				};
			};
		};

		// 6) Hoehenkorrektur wg. Bodenhaftung			
		//	  (optional, nicht bei physicsOn)				// STAND, SLIDE, SWIM
		{
			if (GetConfig().m_eDoHeightCorrection)
			{
				const zREAL oldTransOutY		= transOut[VY];
				if ((GetConfig().m_eState==zCONFIG_STATE_STAND) || ((GetConfig().m_eState==zCONFIG_STATE_SLIDE)))
				{
					if (aboveFloor<=GetConfig().m_fStepHeight)
					{
    					// transOut[VY]			= spatialStateOut.m_fFloorY + (-this->m_fFeetYLocal);		// ..ungenau
    					zCModel *model			= static_cast<zCModel*>(GetVob()->GetVisual());
	    				zREAL modelFloorWorld	= transOut[VY] - model->GetRootPosLocal()[VY];

                        if ((GetConfig().m_bUseSpacingRays) && (GetConfig().m_eDoHeightCorrectionSmooth))
                        {
                            zVEC3 testPos;
							zVEC3 v				= GetVob()->GetVelocity();
                            zREAL vl            = v.Length2();

                            zREAL T				= .1F;
                            zREAL eps			= 1/T;
                            zREAL dt, dh;
							zREAL aheadFloorY	= spatialStateOut.m_fFloorY;

                            if (vl < 1000)
                                goto ploeppen;

                            // smooth update

                            dt      = (float)fabs((transOld - transNew)*v)/vl;

                            testPos = transNew + v * T + zVEC3(0,GetConfig().m_fStepHeight*.5F,0);
                            
	                        world->TraceRayNearestHit(  testPos,
                                                        zVEC3(0, spatialStateOut.m_fFloorY - transNew[VY] - GetConfig().m_fStepHeight*1.5F , 0) ,
                                                        thisVob,
                                                        zTRACERAY_STAT_POLY				| 
										 				zTRACERAY_VOB_IGNORE_CHARACTER	| 
														zTRACERAY_VOB_IGNORE_NO_CD_DYN   |
                                                        zTRACERAY_POLY_NORMAL);	                    


	                        if (!world->traceRayReport.foundHit || world->traceRayReport.foundPolyNormal[VY] < zSin(m_oConfig.m_fMaxGroundAngleWalk)) 
                                goto ploeppen;

                            aheadFloorY = world->traceRayReport.foundIntersection[VY];

                            if (fabs(aheadFloorY - GetSpatialState().m_fFloorY) > GetConfig().m_fStepHeight) // big step
                                goto ploeppen;

                            dh              = aheadFloorY - modelFloorWorld;
                        
                            transOut[VY]   += (dh * dt * eps)/(1 + dt * eps);

                            goto ende;
                        }
ploeppen:;
						// [EDENFELD] Hier ist ein Fehler bei den Bloodflies/Harpien
						// transout erhält illegal hohe Werte, die den Vob
						// über die Step Height hebt
						// danach bewegt sich der Vob gar nicht mehr (siehe Kommentar zum Block oben)
						
						// Update: Der Fehler der hier auftritt hat die Ursache an zwei Stellen: 
						// a) oCAniCtrl::CorrectFightPosition(): Es wird illegalerweise die Höhendifferenz von zwei 
						// kämpfenden NSCs in die Erhöhung der NSC-NSC-Distanz mit einberechnet (gefixt)
						// b) Beim Aufprall eines Projektils ermittelt zCCollObjectCharacter::FindFloorWaterCeiling()
						// das Projektil als Boden	(gefixt)
						

		    		    //transOut[VY]   -= MAX(0,modelFloorWorld - spatialStateOut.m_fFloorY);		// so gehts nicht mehr den berg hoch, runter aber alles ok
						transOut[VY]   -= modelFloorWorld - spatialStateOut.m_fFloorY;
ende:;
					};
				} else
				if (GetConfig().m_eState==zCONFIG_STATE_SWIM)
				{
					zCModel *model			= static_cast<zCModel*>(GetVob()->GetVisual());
					zREAL modelFloorWorld	= transOut[VY] - model->GetRootPosLocal()[VY];
					transOut[VY]			-= (modelFloorWorld - spatialStateOut.m_fWaterY);
					//Print					("correct SWIM: "+zSTRING(model->GetRootPosLocal()[VY]));
				};

				// Sicherheitsnetz: sicherstellen, dass diese Korrektur den Character nicht doch irgendwie 
				// ausserhalb des Levels bewegt
				if (transOut[VY]<=spatialStateOut.m_fFloorY)	transOut[VY] = oldTransOutY; else
				if (transOut[VY]>=spatialStateOut.m_fCeilingY)	transOut[VY] = oldTransOutY;
			};
		};
	};

	return FALSE;
};

/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::CalcAvgNormalVariance()

	 10.1.2001	[HILDEBRANDT]	
				erstellt

   ---------------------------------------------------------------------- */

zBOOL zCCFASTCALL zCCollObjectCharacter::S_CalcAvgNormalVariance (const zTTraceRayReport	(&rayHitReport)[4],
																  zVEC3						&collNormal, 
																  zREAL						&collNormalVariance)
{
	// Collision-Normal
	int numHits = 0;
	collNormal	= zVEC3(0);
	for (int i=0; i<4; i++) 
	{
		if (rayHitReport[i].foundHit) 
		{
			numHits++;
			collNormal += rayHitReport[i].foundPolyNormal;
		};
	};
	if (numHits>0) 
	{
		if (numHits<=1) 
		{
			collNormalVariance = 1;
		} else 
		{ 
			const zREAL collNormalLen = collNormal.LengthApprox();
			if (collNormalLen<=0) 
			{
				// Falls bei der Normalen-Durchschnittsbildung ein 0-Vektor herauskommt, wird auf dieses
				// Kollisionsereignis nicht weiter (mit Wallsliding) reagiert
				numHits				= 0;
			} else 
			{
				collNormal			/= collNormalLen;
				// Collision-Normal Varianz
				// (max. Normal-Variance zur Durchschnitts-Poly-Normal, Bereich: 0..2 (90° ~ 0.707F))
				zREAL varianceMin	= 100;
				for (i=0; i<4; i++) {
					if (rayHitReport[i].foundHit) 
					{
						collNormalVariance = (collNormal * rayHitReport[i].foundPolyNormal);
						if (collNormalVariance<varianceMin) varianceMin = collNormalVariance;	// 1..0..-1 (MAX VARIANCE)
					};
				};
				collNormalVariance	= (varianceMin);	// 1..-1 (MAX VARIANCE)
			};
		};
		return (numHits>0);
	};

	return FALSE;
};

/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::GetSurfaceAlignScanOrigin()

	 11.1.2001	[HILDEBRANDT]	
				erstellt

   ---------------------------------------------------------------------- */

zPOINT3 zCCFASTCALL zCCollObjectCharacter::GetSurfaceAlignScanOrigin (const zPOINT3& testLocation)
{
	// Sucht einen freien Ort etwas ueber der testLocation. Wie hoch drueber ist durch
	// die Groesse der CollisionPole bestimmt.

	// Abhaengigkeiten:
	//	trafoNew (UpVector)

	if (GetConfig().m_bLiftSpacingRayStart)
	{
		const zREAL scanOriginYOffset = GetCollisionPoleYHeight() * zREAL(0.65F);
		if (scanOriginYOffset!=0) 
		{
			enum { rayFlags =	zTRACERAY_STAT_POLY				| zTRACERAY_POLY_NORMAL | 
								zTRACERAY_VOB_IGNORE_NO_CD_DYN	| zTRACERAY_VOB_IGNORE_CHARACTER };

			zCVob			*thisVob	= GetVob();
			zCWorld			*world		= thisVob->GetHomeWorld();
			const zVEC3&	offs		= scanOriginYOffset * this->GetTrafoNew().GetUpVector();		// ATT: das ist eine Vereinfachung! korrekt waere es hier, wenn mann von oben den aktuellen UpVector reinreichen wuerde..
			if (world->TraceRayNearestHitCache (testLocation, offs, thisVob, rayFlags, &m_oUpRayCache)) 
			{
				return testLocation + zREAL(0.8F) * (world->traceRayReport.foundIntersection - testLocation);
			} else
				return testLocation + offs;
		};
	};

	return testLocation;
};


/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::TestSoftCollisions()

	 6.1.2001	[HILDEBRANDT]	
				erstellt

   ---------------------------------------------------------------------- */

zBOOL zCCFASTCALL zCCollObjectCharacter::TestSoftCollisions (const zPOINT3& transOld,		// IN
															 const zPOINT3& transNew,		//		this is the actual testLocation
															 zVEC3&			deltaTransOut,	// OUT
															 zVEC3&			collisionNormalOut)	
{
	// return value: TRUE= have to make deltaMove, FALSE= no Collision
	// OUT:
	// - deltaTransOut: bei return TRUE der Ausweichvektor fuer die CollisionResponse
	// - bei einer Kollision, die mit WallSliding behandelt werden soll, wird hier bereits
	//	 AUF DEM VOB eine ausweichende Rotation ausgefuehrt! (nicht so sauber... sollte nur die Infos hochreichen und dort alles andere machen lassen!)

	// Spacing Rays
	// - Abstandhalter-Laengen
	// - DetectWalkStopChasm
	// - Surface-Align (Crawler)
	// - Meatbug-Walk
	// - als 'centerPos' Vob-Origin mit Y-Offset verwenden (=> Meatbug)
	// ? Wallsliding auch fuer rueckwaerts-moves
	// ? forceModelHalt bei nicht-slide collisions

    // Benutzung von 'state' zur Verkuerzung der Abstandshalter
    zREAL checkWaterCollBodyLen=0;

	// Collision-Test LOD
	// FIXME: hier noch pfiffiger werden ?
	// vielleicht auch: wenn diesen Frame Collision (ueber Rays), dann auch die naechsten n Frames die rayTests machen !
	// - cam-Distanz
	// - movement-velocity
	// - pc/npc
	// FIXME: Rotation ebenfalls beruecksichtigen !!
	/*	if (velocityLen2<(30*30))
		if (oldState==zMV_STATE_STAND) {
			doRayTests = FALSE;
		} else */

    zVEC3 collisionNormal(0,0,0);

	//
	if (GetConfig().m_bUseSpacingRays)
	{

		// Assert: collObject hat Vob, dass ein zCModel als Visual hat
		zCModel	*model		= static_cast<zCModel*>(GetVob()->GetVisual());
		zCVob	*thisVob	= GetVob();
		zCWorld	*world		= GetVob()->GetHomeWorld();

		//
		enum {
			FRONT	= 0, 
			BACK	= 1,
			RIGHT	= 2,
			LEFT	= 3
		};

		// Laenge der Abstandshalter ermitteln
		// (aus der aktuellen objectSpace Model-BBox holen!)
		const zTBBox3D&	protoBox	= model->GetBBox3DLocalFixed();
		zVEC3			scanAt		= thisVob->GetAtVectorWorld();

		zREAL			bodyLenFront;
		zREAL			bodyLenBack;
		zREAL			bodyLenSides; 

		// BodyLen: Closest Axis finden (src: solid) (Achse, mit groesstem Abs-Wert)
		{
			const zTBBox3D& box		= model->GetBBox3D();				// im object Space des Models

			bodyLenFront			= zREAL(+1.0F) * box.maxs[VZ];
			bodyLenBack				= zREAL(-0.9F) * box.mins[VZ];
			bodyLenSides			= (protoBox.maxs[VX] - protoBox.mins[VX]) * 0.4F;

			checkWaterCollBodyLen	= bodyLenFront * 1.2F;				// uuhhh...dirty
		};

		// KollisionsVolumen Skalierer aus den Animationen auslesen und einrechnen
		{
			zREAL collisionVolumeScaler = zREAL(1.0F);
			for (int i=0; i<model->GetNumActiveAnis(); i++)
			{
				collisionVolumeScaler = zMin (collisionVolumeScaler, model->aniChannels[i]->GetAni()->GetCollisionVolumeScale());
			};
			bodyLenFront	*= collisionVolumeScaler;
			bodyLenBack		*= collisionVolumeScaler;
			bodyLenSides	*= collisionVolumeScaler;
		};

		// [HILDEBRANDT] Arghh: was fuer ein schlampiger Zugriff!!!
        if (!static_cast<zCModel *>(GetVob()->GetVisual())->GetIsFlying() && GetConfig().m_fMaxGroundAngleWalk > .001)
		{
            zREAL maxLen = (transNew[VY] - m_oSpatialState.m_fFloorY + 1) / (zREAL)tan(GetConfig().m_fMaxGroundAngleWalk);

            if (maxLen < 0) // invalid length
                maxLen = 10000000;

            if (bodyLenFront > maxLen)
                bodyLenFront = maxLen;

            if (bodyLenBack > maxLen)
                bodyLenBack = maxLen;

            if (bodyLenSides > maxLen)
                bodyLenSides = maxLen;
        }

		///////////////////////////
		//  Abstandshalter-Tests
		///////////////////////////

		enum { rayFlags =	zTRACERAY_STAT_POLY				| zTRACERAY_POLY_NORMAL | 
							zTRACERAY_VOB_IGNORE_NO_CD_DYN	| zTRACERAY_VOB_IGNORE_CHARACTER };

		// Y-Offset ? => ist noetig um Models, deren Origin sehr niedrig liegt, über Schrägen gehen zu lassen
		// (z.B. fuer Meatbug, Swampshark)
		const zPOINT3 &scanOrigin	= GetSurfaceAlignScanOrigin(transNew);

		// Start
		zTTraceRayReport	rayHitReport[4];
		for (int j=0; j<4; j++)	rayHitReport[j].foundHit = FALSE;

		{
			// Die Richtungen, die der Bewegungsrichtung fast gegenueberliegen, brauchen nicht getestet werden
			const zREAL	DIR_THRESH		= zREAL(-0.85F);		// ~30° (vorher: -0.95)
			zVEC3		velocityUnit	= (transNew-transOld);
			velocityUnit.NormalizeApprox();				// FIXME: besser irgendwo genau 1x machen !

			//
			for (int j=0; j<4; j++)
				  rayHitReport[j].foundHit = FALSE;
			
			{
				int numHits=0;
				scanAt	= thisVob->GetAtVectorWorld();

				Line3D (scanOrigin, scanOrigin + scanAt*bodyLenFront, GFX_RED); 
				Line3D (scanOrigin, scanOrigin - scanAt*bodyLenBack , GFX_RED);

				zBOOL	front	= FALSE;
				zBOOL	back	= FALSE;
				zBOOL	left	= FALSE;
				zBOOL	right	= FALSE;
				zVEC3	moveLeft;
				zVEC3	moveRight;
				zVEC3	moveFront;
				zVEC3	moveBack;

				// Ein per Ray getroffenes Objekt/Poly ist nur Hindernis, wenn die gesamplete PolyNormal im "begehbaren" Bereich
				// liegt. Das loest die Probleme: "hackeliges" den Hang hochlaufen, "Rutschfahrt der Toten", SwampShark/Meatbug an Steigungen.
				// Neues Problem: ein Hindernis in Hueft-Hoehe wird ggfs. nicht als solches erkannt.
				// (moeglich Loesung: den Winkeltest nur machen, wenn sich die Huefte im Vergleich zur NeutralPose stark gesenkt hat?)
				// ATT: erstmal disabled, da sonst beim Tauchen z.B. nicht gegen die Boeden getestet wurde..

				// vorne
				if ((velocityUnit*scanAt>DIR_THRESH) &&
					(world->TraceRayNearestHitCache (scanOrigin, scanAt*bodyLenFront, thisVob, rayFlags, &m_oFrontRayCache))
		//			&& (S_CalcFloorSlopeRad(world->traceRayReport.foundPolyNormal[VY])>m_oConfig.m_fMaxGroundAngleWalk)
					)
				{
					// FIXME: [EDENFELD] zIS_OF_CLASS ist im Intel Compiler (und laut Manuel sowieso)
					// buggy. Wird hier durch zDYNAMIC_CAST ersetzt
					// Treppen werden ignoriert
					if ((world->traceRayReport.foundVob) &&
//						(zIS_OF_CLASS<zCVobStair> (world->traceRayReport.foundVob))
						(zDYNAMIC_CAST<zCVobStair> (world->traceRayReport.foundVob))
						)
					{} else
					{
						numHits++;
						front			= TRUE;
						rayHitReport[0]	= world->traceRayReport;
						const zREAL len	= -(bodyLenFront-(world->traceRayReport.foundIntersection - scanOrigin).LengthApprox());
						moveFront		= scanAt * len;
						m_oInterferenceReport.spacingRayFrontVob			= world->traceRayReport.foundVob;
						m_oInterferenceReport.spacingRayFrontPoly			= world->traceRayReport.foundPoly;
						m_oInterferenceReport.correction.spacingRayFront	= TRUE;

                        collisionNormal                                    += world->traceRayReport.foundPolyNormal * (bodyLenFront- len);
					};
				};

				// hinten
				scanAt = -scanAt;
				if ((velocityUnit*scanAt>DIR_THRESH) &&
					(world->TraceRayNearestHitCache (scanOrigin, scanAt*bodyLenBack, thisVob, rayFlags, &m_oBackRayCache))
		//			&& (S_CalcFloorSlopeRad(world->traceRayReport.foundPolyNormal[VY])>m_oConfig.m_fMaxGroundAngleWalk)
					)
				{
					numHits++;
					back			= TRUE;
					rayHitReport[1]	= world->traceRayReport;
					const zREAL len	= -(bodyLenBack-(world->traceRayReport.foundIntersection - scanOrigin).LengthApprox());
					moveBack		= scanAt * len;
					m_oInterferenceReport.spacingRayBackVob			= world->traceRayReport.foundVob;
					m_oInterferenceReport.spacingRayBackPoly		= world->traceRayReport.foundPoly;
					m_oInterferenceReport.correction.spacingRayBack	= TRUE;

                    collisionNormal                                    += world->traceRayReport.foundPolyNormal * (bodyLenBack- len);
				};

				// Seiten
				scanAt = thisVob->GetRightVectorWorld();
				Line3D (scanOrigin, scanOrigin + scanAt*bodyLenSides, GFX_RED); 
				Line3D (scanOrigin, scanOrigin - scanAt*bodyLenSides, GFX_RED);

				// rechts
				if ((velocityUnit*scanAt>DIR_THRESH) &&
					(world->TraceRayNearestHitCache (scanOrigin, scanAt*bodyLenSides, thisVob, rayFlags, &m_oRightRayCache)) 
		//			&& (S_CalcFloorSlopeRad(world->traceRayReport.foundPolyNormal[VY])>m_oConfig.m_fMaxGroundAngleWalk)
					)
				{
					numHits++;
					right			= TRUE;
					rayHitReport[2]	= world->traceRayReport;
					const zREAL len	= -(bodyLenSides-(world->traceRayReport.foundIntersection - scanOrigin).LengthApprox());
					moveRight		= scanAt * len;
					m_oInterferenceReport.spacingRayRightVob			= world->traceRayReport.foundVob;
					m_oInterferenceReport.spacingRayRightPoly			= world->traceRayReport.foundPoly;
					m_oInterferenceReport.correction.spacingRayRight	= TRUE;

                    collisionNormal                                    += world->traceRayReport.foundPolyNormal * (bodyLenSides- len);
				};

				// links
				scanAt = -scanAt;
				if ((velocityUnit*scanAt>DIR_THRESH) &&
					(world->TraceRayNearestHitCache (scanOrigin, scanAt*bodyLenSides, thisVob, rayFlags, &m_oLeftRayCache)) 
		//			&& (S_CalcFloorSlopeRad(world->traceRayReport.foundPolyNormal[VY])>m_oConfig.m_fMaxGroundAngleWalk)
					)
				{
					numHits++;
					left			= TRUE;
					rayHitReport[3]	= world->traceRayReport;
					const zREAL len	= -(bodyLenSides-(world->traceRayReport.foundIntersection - scanOrigin).LengthApprox());
					moveLeft		= scanAt * len;
					m_oInterferenceReport.spacingRayLeftVob			= world->traceRayReport.foundVob;
					m_oInterferenceReport.spacingRayLeftPoly		= world->traceRayReport.foundPoly;
					m_oInterferenceReport.correction.spacingRayLeft	= TRUE;

                    collisionNormal                                += world->traceRayReport.foundPolyNormal * (bodyLenSides- len);
				};

				// Korrektur-Vector berechnen (fuer die Collision Response)

				// wenn vorne oder hinten UND
				// wenn nicht (Links&Rechts gleichzeitig UND (nur vorne ODER hinten))
				if ((thisVob->GetCollDetStat()) &&
					(numHits>0) )
				{
					deltaTransOut	= zVEC3(0);
					if (back || front)
					if (!((left && right) && (!(back && front))))
					{
						if (back && front)	deltaTransOut += (moveBack + moveFront) * 0.5F;	else 
						if (back)			deltaTransOut += moveBack;						else
											deltaTransOut += moveFront;
						if (front) PrintScreen (0,5000, "F"); if (back) PrintScreen (100,5000, "B");
					};

					if (left || right)
					if (!((back && front ) && (!(left && right))))
					{
						if (left && right)	deltaTransOut += (moveRight + moveLeft) * 0.5F;	else
						if (left)			deltaTransOut += moveLeft;						else
											deltaTransOut += moveRight;
						if (left) PrintScreen (200,5000, "L");	if (right)	PrintScreen (300,5000, "R");
					};

					// Auswertung der Rays: ggfs. WallSliding initiieren
					if (GetConfig().m_bDoWallSliding)
					{
						// CollisionNormal und Variance aus den 4 Samples errechnen
						zREAL	collNormalVariance;
						zBOOL	ok		= S_CalcAvgNormalVariance (rayHitReport, collisionNormalOut, collNormalVariance);

						if ((ok) && (collNormalVariance>=0.8F))
						{
							// Einen gewuenschten WallSlide nach oben melden
							m_oInterferenceReport.correction.spacingRayWallSlide	= TRUE;
						};
					};

                    collisionNormalOut     = collisionNormal;    
                    collisionNormalOut[VY] = 0;
                    collisionNormalOut.NormalizeSafe();

					return TRUE;
				};
			};
		};
	};

	return FALSE;
};

/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::DetectCollisionsSelf()

	 6.1.2001	[HILDEBRANDT]	
				rewrite

   ---------------------------------------------------------------------- */

void zCCFASTCALL zCCollObjectCharacter::DetectCollisionsSelf(const zCArray<zCCollisionObject*>& otherCollObjectList,	// IN
																   zCArray<zCCollisionReport*>&	collReportList)			// OUT
{
	// arbeitet nur, falls das Visual des Vobs vorhanden und ein zCModel ist
	if (!GetVob()->GetVisual())							return;
	// FIXME: [EDENFELD] zIS_OF_CLASS ist im Intel Compiler (und laut Manuel sowieso)
	// buggy. Wird hier durch zDYNAMIC_CAST ersetzt
	// Treppen werden ignoriert
	if (!zDYNAMIC_CAST<zCModel>(GetVob()->GetVisual()))	return;

	// Debug Infos
	#ifdef zMV_DEBUG
		PrintDebugInfos();
	#endif

	// TODO: mehrere Iterationen? collReport ausfuellen?

	// WallSlide Rotation
	this->DoWallSlidingLatentRotation(this->GetTrafoNew());

	// Interference Report loeschen 
	// (Wird in TestSoftCollisions() und TestHardCollisions() ausgefuellt. Da dieser als 'fluechtig' gilt, muss er nicht
	//  im spatialState enthalten sein.)
	m_oInterferenceReport.Clear		();

	// Ergebnis Position
	const zPOINT3&	transOld			= this->GetTrafoOld().GetTranslation();
	zPOINT3			transOut			= this->GetTrafoNew().GetTranslation();
	zPOINT3			transOutFinal;
	zBOOL			tryAgain;
	int				tryAgainCtr			= 0;
	zBOOL			doWallSlideRotate	= FALSE;


    // [Moos] Wenn der aktuelle SpatialState ungültig ist: besorge den richtigen.
    if (GetSpatialState().m_bIsUninited)
        FindFloorWaterCeiling	(transOld, m_oSpatialState);


	do
	{
		tryAgain					= FALSE;
		doWallSlideRotate			= FALSE;

		// Test Soft Collisions (Spacing Rays)
		// ===================================
		{
			zVEC3						deltaTransOut;
//			zVEC3						collisionNormal;
			zBOOL haveToEvadeSoftColl	= this->TestSoftCollisions	(transOld,			// IN
																	 transOut, 			
																	 deltaTransOut,		// OUT
																	 m_oInterferenceReport.collisionNormal);
			if (haveToEvadeSoftColl)
			{
				// WallSlide erwuenscht ?
				if (m_oInterferenceReport.correction.spacingRayWallSlide)
				{
					// Slide Vektor berechnen
					zVEC3	slideVectorOut;
					if (CalcSlideVector (	(transOut-transOld),
											 m_oInterferenceReport.collisionNormal, 
											 slideVectorOut,			// OUT
											 m_oWallSlideRotAxis,
											 m_fWallSlideRotDir))
					{
						transOut							+= slideVectorOut;
						m_fWallSlideTimer					= 100 + 100.0F * (1-zAbsApprox(m_fWallSlideRotDir)); 
						doWallSlideRotate					= TRUE;
					} else
						m_oInterferenceReport.correction.spacingRayWallSlide	= FALSE;
				};

				// SpacingRay Korrektur einrechnen 
				// (aber erst _nach_ der Berechnung des SlideVektors, da dieser sonst verfaelscht werden koennte)
				transOut				+= deltaTransOut;
			};
			// => transOut
		};

		// Test Hard Collisions & berechne aktuellen spatialState
		// ======================================================
		{
        	zTSpatialState				spatialStateOut;
			zVEC3						collisionNormal;
			zBOOL resetToOldHardColl	= this->TestHardCollisions	(transOld,			// IN
																	 transOut,
																	 transOutFinal,		// OUT
																	 spatialStateOut,
																	 collisionNormal);
			// SpatialState uebernehmen, falls neue Position gueltig ist
			if (!resetToOldHardColl)
			{
				// Neue Position ist gueltig
				this->m_oSpatialState	= spatialStateOut;
			} else 
			{
                // eventuell von den SoftCollisions eingetragene collisionNormal überschreiben; die hier ist wichtiger [Moos]
                m_oInterferenceReport.collisionNormal = collisionNormal;

				// Neue Position ist NICHT gueltig (resetToOld + response, transOutFinal NICHT gueltig!)
				// Der neue Zustand (transOutFinal) bleibt der alte Zustand (transOld), ggfs. weitere Responses initiieren
				// (in diesem Fall kehrt TestHardCollisions() mit transOutFinal=transOut zurueck).
				if (GetConfig().m_bDoWallSliding && 
					((this->GetInterferenceReport().blocking.floorTooSteepUp)   ||
					 (this->GetInterferenceReport().blocking.floorTooSteepDown) ||
					 (this->GetInterferenceReport().blocking.lowCeiling)))
				{
					// Collision Response
					// Slide Vektor berechnen
					zVEC3	slideVectorOut;
					if (CalcSlideVector (	(transOut-transOld),
											 collisionNormal, 
											 slideVectorOut,		// OUT
											 m_oWallSlideRotAxis,
											 m_fWallSlideRotDir))
					{
						// Hier wird eine neue Zielposition errechnet. Eine weitere Iteration ist noetig, um
						// sicherzustellen, dass diese neue Position auch den TestHardCollisions() Test besteht.
						transOut							= transOld + slideVectorOut;	// transOutFinal wird hier nicht verwendet!
						transOutFinal						= transOut;
						m_fWallSlideTimer					= 100 + 100.0F * (1-zAbsApprox(m_fWallSlideRotDir)); 
						m_oInterferenceReport.blocking.blockingWallSlide	= TRUE;
						doWallSlideRotate					= TRUE;
						tryAgain							= TRUE;
					};
				};
			};
			// => transOutFinal
		};
		++tryAgainCtr;

		if ((tryAgain) && (tryAgainCtr>=2))
		{
			// Suche nach der 2ten Iteration abbrechen, erfolglos aufgeben (hey, hoert sich schlechter an, als es ist :))
			transOutFinal		= transOld;					// auf die Ursprungsposition zuruecksetzen
			m_fWallSlideTimer	= 0;						// weitere WallSlides unterbinden
			doWallSlideRotate	= FALSE;
			tryAgain			= FALSE;					// Abbruch!

            // [Moos] und übernimm in diesem Fall den SpatialState der aktuellen Position.
            FindFloorWaterCeiling	(transOld, m_oSpatialState);
		};
	} while (tryAgain);

	//
	if (doWallSlideRotate)
		this->DoWallSlidingLatentRotation	(this->GetTrafoNew());

	// Ergebnis uebernehmen
	this->GetTrafoNew().SetTranslation	(transOutFinal);
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


void zCCFASTCALL zCCollObjectCharacter::CollisionResponse	(const zCArray<zCCollisionReport*>& collReportList, zBOOL& simulateFurther)
{
	if (!HasMoved()) return;

    zCCollisionReport *report               = collReportList[0];

    zCCollObjectCharacter *objChar0         = (zCCollObjectCharacter *)report->m_poCollObject0;

    const zMAT4 &trafoObj0Begin             = objChar0->GetTrafoOld();
    const zMAT4 &trafoObj0End               = objChar0->GetTrafoNew();
    const zVEC3 &normal                     = report->m_oCollNormal0;

    zERR_ASSERT(normal.Length2() > .9 && normal.Length2() < 1.1);

    // Hole die Ausweichtrafo (zu ihr versuchen wir, zurückzukehren). Wenn es nur eine Kollision gibt, dürfen wir frei rotieren.
    zBOOL rotateFree                        = collReportList.GetNumInList()<=1;
    zMAT4 trafoEvade;
    objChar0->GetFallbackTrafoCC			(trafoObj0Begin, trafoObj0End, normal, rotateFree, trafoEvade);

    // in diese Richtung wollen wir das Objekt bewegen:
	zVEC3 wishMove                          = trafoObj0End.GetTranslation() - trafoObj0Begin.GetTranslation();

    // und so weit können wir dabei gehen
    zREAL distance=0;
    
    // werfen wir mal einen Blick auf das zweite Objekt, falls es auch ein Char ist:
    if (report->m_poCollObject1->GetCollObjClass() == zCCollObjectCharacter::S_GetCollObjClass())
    {
        zCCollObjectCharacter *objChar1 = (zCCollObjectCharacter *)(report->m_poCollObject1);

        zVEC3 point, connection; // nur dummy-Variablen

        // prima! Wir können einen besseren Distanzcheck machen.
        distance = zCConvexPrimitive::Distance(objChar0->GetPrimitiveCC()	, objChar1->GetPrimitiveCC(),
                                               trafoEvade                   , objChar1->GetTrafoNew() ,
                                               normal, point, connection);
    }

    // so. Jetzt können wir sliden.
    zVEC3 slide = S_SlideCC	(normal, distance, wishMove);
    trafoEvade.Translate	(slide);
    SetTrafoNew				(trafoEvade);

    // aktiviere die Physik, wenn wir im Sprung sind
    zCModel *model = zDYNAMIC_CAST<zCModel>(GetVob()->GetVisual());
    if (model && model->GetIsFlying())
        GetVob()->SetPhysicsEnabled(TRUE);

    // mache eine schöne elastische Kollision
    if (GetVob()->GetPhysicsEnabled())
	{
        zCVob *vob0 = GetVob();
        zCVob *vob1 = NULL;

        zVEC3 v0    = vob0->GetVelocity();
        zVEC3 v1    = zVEC3(0, 0, 0);

        zREAL m0    = vob0->GetRigidBody()->GetMass();
        zREAL m1    = m0 * 10000;
        
        //zCCollObjectCharacter *oc = NULL;
        //if (collReportList[0]->m_poCollObject1 && (collReportList[0]->m_poCollObject1->GetCollObjClass() == S_GetCollObjClass()))
        zCCollObjectCharacter *oc   = dynamic_cast<zCCollObjectCharacter*>(collReportList[0]->m_poCollObject1);
        if (oc)
        {
            //oc   = static_cast<zCCollObjectCharacter *>(collReportList[0]->m_poCollObject1);
            vob1 = oc->GetVob();
            v1   = vob1->GetVelocity();
            m1   = vob1->GetRigidBody()->GetMass();
        }

        m1 *= 100; // FIXME: Wenn ich rausfinde, wie man vob1 schubsen kann, kann das weg,

        zVEC3 vdiff = v0 - v1;

        zREAL refl = normal*vdiff;
        
        // schleudere ihn mit einer gewissen mindestkraft zurück
        if (refl < 100)
        {
            if (refl > -300) // übertreibe es aber nicht
                refl = 100;
            else
                refl = 0;
        }

        v0 -= 1.5 * normal * refl * m1/(m0 + m1);
        v1 += 1.5 * normal * refl * m0/(m0 + m1);
        
        vob0->GetRigidBody()->SetVelocity(v0);

        if (oc)
            oc->PushAround(v1);
    }

	simulateFurther = TRUE;
};


/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::GetLargestBBox3DLocal()


	 17.12.2000	[Moos]	
                Holt die BBox nun aus der Primitiven

   ---------------------------------------------------------------------- */

void zCCFASTCALL zCCollObjectCharacter::GetLargestBBox3DLocal(zTBBox3D &bbox3DLocalOut)
{
    bbox3DLocalOut = GetPrimitiveCC()->GetBBox3DLocal();
};

/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::GetAdaptiveStepSize ()	

   ---------------------------------------------------------------------- */

zREAL zCCFASTCALL zCCollObjectCharacter::GetAdaptiveStepSize ()	
{ 
	// Model aus dem Vob/Visual herausziehen
	zERR_ASSERT (GetVob()->GetVisual()->GetClassDef()==zCModel::GetStaticClassDef());
	zCModel *model = static_cast<zCModel*>(GetVob()->GetVisual());
	if (!model)	return 0;

	return zMax (zREAL(0.1F), 
		S_GetSourceBBoxScaler() * model->GetBBox3DCollDet().GetMinExtent() * 0.9F);
};

/* ----------------------------------------------------------------------
	
     zCCollObjectCharacter::PrintDebugInfos ()

	 9.1.2001	[HILDEBRANDT]	
                erstellt

   ---------------------------------------------------------------------- */

void zCCFASTCALL zCCollObjectCharacter::PrintDebugInfos ()	
{
	#ifdef zMV_DEBUG
	return;
		int x	= 0;
		int y	= 3000;
		screen->Print (x,y+(0*screen->FontY()), "Y (fl,wt,ceil): "	+zSTRING(m_oSpatialState.m_fFloorY,3)+", "
																	+zSTRING(m_oSpatialState.m_fWaterY,3)+", "
																	+zSTRING(m_oSpatialState.m_fCeilingY,3));
//		screen->Print (x,y+(1*screen->FontY()), "Y (fe,ct,hd): "	+zSTRING(feetY,5)+", "
//																	+zSTRING(centerPos[VY],5)+", "
//																	+zSTRING(headY,5)); 
//		screen->Print (x,y+(2*screen->FontY()), "waterLvl: "+zSTRING(waterLevel)+", state: "+zSTRING(oldState)+
//			", aiCD: "+zSTRING(aiDetectedCollision)+", selfDet: "+zSTRING(selfDetectedCollision));
	#endif
};
