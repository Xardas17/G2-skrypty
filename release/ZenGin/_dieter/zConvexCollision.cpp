/******************************************************************************** 
 
     $Workfile:: zConvexCollision.cpp     $                $Date:: 19.01.01 11:42   $
     $Revision:: 13               $             $Modtime:: 19.01.01 9:38    $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Collision objects given by a convex geometrical primitive
   created: 12.12.2000

 * $Log: /current_work/ZenGin/_Dieter/zConvexCollision.cpp $
 * 
 * 13    19.01.01 11:42 Moos
 * 
 * 12    15.01.01 20:15 Moos
 * 
 * 11    11.01.01 18:45 Moos
 * 
 * 10    21.12.00 16:07 Moos
 * 
 * 9     20.12.00 21:15 Moos
 * 
 * 8     20.12.00 15:40 Moos
 * 
 * 7     19.12.00 21:16 Moos
 * 
 * 6     18.12.00 19:42 Moos
 * 
 * 5     15.12.00 18:32 Moos
 * 
 * 4     13.12.00 19:13 Moos
 * 
 * 3     13.12.00 18:11 Moos
 * 
 * 2     13.12.00 15:54 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 19.01.01 9:38 $)

#include "zAlgebra.h"
#include "zMemPool.h"
#include "z3d.h"
#include "zError.h"
#include "zSparseArray.h"
#include "zConvexCollision.h"
#include "zBVolume.h"
#include "zTools.h"

zMEMPOOL_DEFINITION_BS_PA(zCConvexCollisionCache, 128, 128)



// Die Klasse, die im Cache-SparseArray als Index herhält

class zCCacheIndex{
public:
    zCVob *voba, *vobb;

    zCCacheIndex(zCVob *a, zCVob *b): voba(a), vobb(b){
        if (int(a) > int(b))
        {
            voba = b;
            vobb = a;
        }
    }

    // wieso der Vergleichsoperator überladen werden muss, ist mir schleierhaft.
    zBOOL operator==(const zCCacheIndex &x) const {return voba == x.voba && vobb == x.vobb;}
};


//static       zCSparseArray<zCCacheIndex, zCConvexCollisionCache*> s_collisionCache;
static       zCCache<zCCacheIndex, zCConvexCollisionCache>        s_collisionCache(13,2);
static       zUINT32                                              s_frameCtr    =0;
const static zUINT32                                              s_cacheTimeOut=10;

// *************************
//   zCConvexPrimitive
// *************************



/* ----------------------------------------------------------------------
	
    zCConvertPrimitive::PointNearestToPlane()

    findet im GLOBALEN Koordinatensystem den Punkt <point> der
    mit <trafoObjToWorld> transformierten Primitiven, der maximales
    Skalarprodukt point * planeNormal hat. Un die normale in
    das lokale Koordinatensystem zu bringen, wird die Matrix <rotateWorldToObj>
    verwendet.

	 13.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void zCConvexPrimitive::PointNearestToPlane(       zVEC3 &point, 
                                             const zVEC3 &planeNormal, 
                                             const zMAT4 &trafoObjToWorld,
                                             const zMAT3 &rotateWorldToObj) const
{
    zVEC3 pointLocal;

    PointNearestToPlaneLocal(rotateWorldToObj*planeNormal, pointLocal);

    point = trafoObjToWorld * pointLocal;

}



#define MAXTRIES 10
#define MINTRIES 0

/* ----------------------------------------------------------------------
	
    zCConvertPrimitive::CheckCollision()

   Do a collision check between <a> and <b> with trafos given by <aTrafo> and <bTrafo> a; return values:
   direct return: was there a collision?
   <point>      : collision point (or almost-collision point if there is no collision)
   <distance>   : distance of the two objects; negative of the intrusion depth if there is a collision
   <normal>     : collision axis; sliding should happen perpenticular to this.

   for better understanding:
   <connection> is allways an expression of the form A - B where A and B are points in a resp. b.

	 13.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */
   
// Statistik
static int s_nextstat=1024;
static int s_numcalls=0;
static int s_numtries=0;

zBOOL zCConvexPrimitive::CheckCollision(const zCConvexPrimitive *a     , const zCConvexPrimitive *b     ,
                                        const zMAT4             &aTrafo, const zMAT4             &bTrafo,
                                        zCConvexCollisionCache *cache,
                                        zVEC3 &point0, zREAL &distance0, zVEC3 &normal0)
{
    if (s_numcalls >= s_nextstat){
        s_nextstat *= 2;
        zREAL tr = zREAL(s_numtries)/s_numcalls;
        zERR_MESSAGE(4, 0, "M: Collision staticstics: number of calls: " + zSTRING(s_numcalls) + ", number of iterations: " +
                           zSTRING(s_numtries) + ", average: " + zSTRING(tr) + ".");
    }

    s_numcalls++;

    zERR_ASSERT(cache && a && b);

    zVEC3    connection0;

    zUINT32  tries        = 0;

    // get a vector from a to b:
    zVEC3    acenter, bcenter;

    a->GetCenterLocal(acenter);    
    b->GetCenterLocal(bcenter);

    zVEC3    atob     = bTrafo * bcenter  -  aTrafo * acenter;
    zVEC3    atobNormal;
    zREAL atobLength2 = atob.Length2();

    if (atobLength2 > .001)
        atobNormal  = atob * zREAL(1/sqrt(atobLength2)); // normalize
    else
        atobNormal  = zVEC3(0,1,0);

    // get the normal
    normal0   = cache->planeNormal; 

    // make sure the normal points in direction a->b
    zREAL prod = normal0 * atobNormal;
    if (prod < 0)
        normal0 -= prod * atobNormal;

    // Sanity checks and correct initialisation (cache->normal is set to 0 on construction)
    if (normal0.Length2() < .5)
        normal0 = cache->planeNormal = atobNormal;
    normal0.Normalize();

    // check if normal0 is already a good separating axis; if yes, quit early reporting a non-collision. If no, we have at least our first connection vector
    distance0   = Distance(a, b, aTrafo, bTrafo, normal0, point0, connection0);
    if (distance0 > 0)
        return false;

    do
    {
	    tries ++;

	    zVEC3 normal1 = connection0;
        zREAL len     = normal1.Length();
	    if (len > 0)  // [Moos] 11.01.01 Division durch 0 vermeiden....
            normal1 *= 1/len;
	    else 
            normal1 = atobNormal;

	    zVEC3 point1, connection1;

	    // get another connection vector
	    zREAL distance1 = Distance(a, b, aTrafo, bTrafo, normal1, point1, connection1);

	    // store it if it was better than the last (this part is NOT guaranteed)
	    if (distance1 > distance0)
	    {
	        distance0          = distance1;
    	    cache->planeNormal = normal0 = normal1;
	        point0             = point1;

#ifdef DEBUG_MOOS
#ifdef _DEBUG
            if (distance0 > 0)
            {
                cache->lastGoodTrafo0 = aTrafo;
                cache->lastGoodTrafo1 = bTrafo;
                cache->lastGoodNormal = normal0;
            }
#endif
#endif
	    }
	
	    // find the smallest (norm-wise) connection vector between connection0 and connection1. It is
	    // guaranteed to lie closer to the origin than connection0.

        zVEC3 dc    = connection0 - connection1;
        dc.           Normalize();

#ifdef _DEBUG
	    zREAL lastlength = connection0.Length2();
#endif

	    // the above guarantee expressed mathematically:
	    zERR_ASSERT(connection0 * dc > 0);
	
        zREAL place = -connection1 * dc;
	    if (place > 0)
	        connection0 = connection1 + dc * place;  // we can get better than connection1
	    else
            connection0 = connection1;               // connection1 is the best place on the line

	    // and again our guarantee in another form
	    zERR_ASSERT(connection0.Length2() < lastlength + 1);

    	// smallest vector is now found and is stored in connection0.



    	// reset if neccesary; TODO: better fallback
    	if (connection0 * atob < 0)
	        connection0 = atob;
    }
    while (connection0.Length2() > 0 && tries < MAXTRIES && (tries <= MINTRIES || distance0 < 0 || connection0.Length2() < atobLength2*.0001));

    s_numtries += tries;

    return (distance0 < 0);
}



/* ----------------------------------------------------------------------
	
    zCConvertPrimitive::Distance()

    Hilfsfunktion; berechnet die Distanz/Eindringtiefe, den möglichen
    Kollsisonspunkt <point> und den Verbindungsvektor <connection> der möglichen 
    Berührpunkte, der Kollision von <a> und <b>, falls <planeNormal>, die
    normale der Kollisions-/Trenn-Ebene ist.

	 13.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

zREAL zCConvexPrimitive::Distance(const zCConvexPrimitive *a     , const zCConvexPrimitive *b     ,
                                  const zMAT4             &aTrafo, const zMAT4             &bTrafo,
                                  const zVEC3 &planeNormal,
                                  zVEC3 &point, zVEC3 &connection)
{
    zERR_ASSERT(a && b);

    zVEC3 pointa, pointb;
    a->PointNearestToPlane(pointa, planeNormal, aTrafo);
    b->PointNearestToPlane(pointb,-planeNormal, bTrafo);

    connection =  pointb - pointa;
    point      = (pointa + pointb) * .5;
    
    return connection * planeNormal;
}



// for silly communication between the next two functions
static zUINT32 s_lastPurge=0;

/* ----------------------------------------------------------------------
	
    zCConvertPrimitive:GetCache()

    holt das für Kollision von <aVob> und <bVob> zuständige CacheElement.
    Bei Bedarf wird es erzeugt, geflippt oder es wird der Cache geleert.

	 13.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

zCConvexCollisionCache *zCConvexPrimitive::GetCache(const void *aVob ,const void *bVob){
    zERR_ASSERT(aVob && bVob);

    zCCacheIndex            index   ((zCVob *)aVob, (zCVob *)bVob);

    zCConvexCollisionCache *ret   = s_collisionCache[index];

    zERR_ASSERT_STRICT(ret);

    zBOOL inverted = (aVob != index.voba);
    if (inverted != ret->invert)       // the vobs were given the other way round last time; invert the separating plane's normal.
    {
        ret->invert       = inverted;
        ret->planeNormal *= -1;
    }
    
    return ret;
}




/* ----------------------------------------------------------------------
	
    zCConvertPrimitive::PurgeCaches()
    
    Loscht ale CacheElements, die seit s_cacheTimeOut Frames nicht
    mehr verwendet wurden.

	 13.12.2000	[Moos]	
                erzeugt
     15.01.2001 [Moos]
                wieder weggeworfen. Allgemeines Interface macht das nun.

   ---------------------------------------------------------------------- */

/*
void zCConvexPrimitive::PurgeCaches(){
    s_frameCtr++;

    s_lastPurge=s_frameCtr;

    for(zCSparseArrayIterator i(s_collisionCache); i; i.Next())
        if (s_frameCtr - (*s_collisionCache[i])->frameLastUsed > s_cacheTimeOut)
        {
            delete *s_collisionCache[i];
            *s_collisionCache[i] = NULL;
            s_collisionCache.Delete(i);
        }
}
*/


static zMAT4  s_trafo;
static zCOLOR s_color;
static zVEC3  s_lastPos;

void zCConvexPrimitive::Draw (const zMAT4 &trafo, const zCOLOR color, const zCCamera *cam) const{
    if (!cam)
        cam = zCCamera::activeCam;
    if (!cam)
        return;

    s_trafo = cam->camMatrix * trafo;
    s_color = color;

    s_lastPos = s_trafo * zVEC3(0,0,0);
    
    DrawVirtual();
}

void zCConvexPrimitive::DrawLine (const zVEC3 &a, const zVEC3 &b){
    s_lastPos = s_trafo * b;
    zlineCache.LineCS3D(s_trafo * a, s_lastPos, s_color);
}

void zCConvexPrimitive::DrawLineStrip (const zVEC3 &a){
    zVEC3 newPos = s_trafo * a;
    zlineCache.LineCS3D(s_lastPos, newPos, s_color);
    s_lastPos = newPos;
}


void zCConvexPrimitive::DrawVirtual() const{
    DrawLine(zVEC3(1,0,0), zVEC3(-1,0,0));
    DrawLine(zVEC3(0,1,0), zVEC3(0,-1,0));
    DrawLine(zVEC3(0,0,1), zVEC3(0,0,-1));
}


// *************************
// *************************
//     Special Primitives
// *************************
// *************************


// *************************
//        Unit Sphere
// *************************

zCConvexPrimitiveUnitSphere zCConvexPrimitiveUnitSphere::s_unitSphere;

#define SPIR 6
#define POINT 50

void zCConvexPrimitiveUnitSphere::DrawVirtual() const{
    for (int i=POINT; i>=0; i--)
    {
        zREAL a  = zREAL((float(i)/POINT) * 3.14159);
        zREAL b  = a * SPIR * 2;
        zREAL as = zSin(a);
        DrawLineStrip(zVEC3(as * zSin(b), zCos(a) , as * zCos(b)));
    }
}


zBOOL zCConvexPrimitiveUnitSphere::PointIsInLocal (const zVEC3 &point) const{
    return point.Length2() <= 1;
}


// *************************
//        ScaleTrans
// *************************



/* ----------------------------------------------------------------------
	
    zCConvertPrimitiveScaleTrans::zCVonvexPrimitiveScaleTrans()

	 13.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

zCConvexPrimitiveScaleTrans::zCConvexPrimitiveScaleTrans(zCConvexPrimitive *o, const zVEC3 &s, const zVEC3 &t)
:scale(s), translation(t), original(o)
{
    zERR_ASSERT(original);
}

zCConvexPrimitiveScaleTrans::~zCConvexPrimitiveScaleTrans(){}



/* ----------------------------------------------------------------------
	
    zCConvertPrimitiveScaleTrans::PointNearestToPlaneLocal()

	 13.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void zCConvexPrimitiveScaleTrans::PointNearestToPlaneLocal(const zVEC3 &planeNormal, zVEC3 &point) const{
    int i;
    zVEC3 normal;

    // transformiere die Normale
    for (i=2; i>=0; i--)
        normal[i] = planeNormal[i] * scale[i];
    normal.Normalize();

    // rufe den Originaltest aus
    original->PointNearestToPlaneLocal(normal, point);

    // und transformiere den zurückgegebenen Punkt
    for (i=2; i>=0; i--)
        point[i] = (point[i] * scale[i]) + translation[i];
}


zBOOL zCConvexPrimitiveScaleTrans::PointIsInLocal(const zVEC3 &point) const{
    zVEC3 p;

    // transformiere den Punkt zurück
    for (int i=2; i>=0; i--)
        p[i] = (point[i] - translation[i]) / scale[i];

    return original->PointIsInLocal(p);
}


/* ----------------------------------------------------------------------
	
    zCConvertPrimitiveScaleTrans::GetCenterLocal()

	 13.12.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void zCConvexPrimitiveScaleTrans::GetCenterLocal(zVEC3 &center) const{
    original->GetCenterLocal(center);

    for (int i=2; i>=0; i--)
        center[i] = (center[i] * scale[i]) + translation[i];
}

void zCConvexPrimitiveScaleTrans::UpdateBBox(){
    original->UpdateBBox();

    const zTBBox3D &origbb = original->GetBBox3DLocal();

    for (int i=2; i>=0; i--){
        bbox3Dlocal.mins[i] = (origbb.mins[i] * scale[i]) + translation[i];
        bbox3Dlocal.maxs[i] = (origbb.maxs[i] * scale[i]) + translation[i];
    }
}


void zCConvexPrimitiveScaleTrans::DrawVirtual() const{
    zMAT4 extra;
    extra.MakeIdentity();
    extra.SetAtVector   (zVEC3(0,0,scale[2]));
    extra.SetUpVector   (zVEC3(0,scale[1],0));
    extra.SetRightVector(zVEC3(scale[0],0,0));
    extra.SetTranslation(translation);

    s_trafo = s_trafo * extra;

    original->DrawVirtual();
}



zCConvexPrimitiveEllipsoid::zCConvexPrimitiveEllipsoid(const zTBBox3D &box, zBOOL snap)
:zCConvexPrimitiveScaleTrans(&zCConvexPrimitiveUnitSphere::s_unitSphere, .5F*(box.maxs - box.mins), .5F*(box.maxs + box.mins)),
symetric(FALSE){
    if (snap)
        Snap();
}


void    zCConvexPrimitiveEllipsoid::Snap (){
   if (zREAL(fabs(scale[VX] - scale[VZ])) < (scale[VX] + scale[VZ]) * .4){
        scale[VX] = scale[VZ] = zREAL((scale[VX] + scale[VZ]) * .5);
        UpdateBBox();
        symetric = TRUE;
    }
}


// *************************
//        Tests
// *************************

#ifdef DEBUG_MOOS

zCVob *a = (zCVob *) 1;
zCVob *b = (zCVob *) 2;
zCVob *c = (zCVob *) 3;

void TestConvexCollision(){
    zMAT4 A,B;

    A.MakeIdentity();
    B.MakeIdentity();

    B.SetAtVector(zVEC3(0,1,0));
    B.SetUpVector(zVEC3(0,0,1));

    zREAL z = 30;

    zCConvexPrimitiveEllipsoid e(zVEC3(1,1,.1F), zVEC3(0,0,0));

    zVEC3 point, normal;
    zREAL distance;

    do{
        z-=.01F;
        B.SetTranslation(zVEC3(0,1,z));
    }
    while(z > -10&& !zCConvexPrimitive::CheckCollision(&e, &e,
                                                          A,  B,
                                                          a,  b,
                                                          point, distance, normal));

    zCConvexPrimitive::CheckCollision(&e, &e, A,  B,  a,  b,
                                      point, distance, normal);

    do{
        z-=.01F;
        B.SetTranslation(zVEC3(0,1,z));
    }
    while(z > -100&&   zCConvexPrimitive::CheckCollision(&e, &e,
                                                          A,  B,
                                                          a,  b,
                                                          point, distance, normal));

    zCConvexPrimitive::CheckCollision(&e, &e, A,  B,  a,  b,
                                      point, distance, normal);
}


#endif

