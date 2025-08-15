/******************************************************************************** 
 
     $Workfile:: zConvexCollision.h     $                $Date:: 15.01.01 20:15   $
     $Revision:: 9                $             $Modtime:: 15.01.01 13:51   $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Collision objects given by a convex geometrical primitive
   created: 12.12.2000

 * $Log: /current_work/ZenGin/_Dieter/zConvexCollision.h $
 * 
 * 9     15.01.01 20:15 Moos
 * 
 * 8     21.12.00 16:07 Moos
 * 
 * 7     20.12.00 15:40 Moos
 * 
 * 6     20.12.00 9:46 Moos
 * 
 * 5     18.12.00 19:42 Moos
 * 
 * 4     15.12.00 18:32 Moos
 * 
 * 3     13.12.00 18:11 Moos
 * 
 * 2     13.12.00 15:54 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 15.01.01 13:51 $)

// dependencies: zMemPool.h, zAlgebra.h, z3d.h

class zCCacheIndex;

class zCConvexCollisionCache{
    zMEMPOOL_DECLARATION(zCConvexCollisionCache)
public:
    zVEC3   planeNormal;
    zBOOL   invert;

#ifdef DEBUG_MOOS
#ifdef _DEBUG
    zMAT4   lastGoodTrafo0, lastGoodTrafo1;
    zVEC3   lastGoodNormal;
#endif
#endif

    zCConvexCollisionCache(const zCCacheIndex &):planeNormal(0,0,0), invert(FALSE){}    
};


// ***************************************************************************************
// ***************************************************************************************
// zCConvexPrimitive: virtual base class for all convex primitives (sphere, ellipsoid,...)
// ***************************************************************************************
// ***************************************************************************************

class zCConvexPrimitive{
public:
    zCConvexPrimitive(){UpdateBBox();}
    virtual ~zCConvexPrimitive(){};

    // sets <point> so that it is inside the primitive with <point, planeNormal> maximal, all that in WORLD coordinates
    void PointNearestToPlane(zVEC3 &point, const zVEC3 &planeNormal, const zMAT4 &trafoObjToWorld, const zMAT3 &rotationWorldToObj) const;

    // the same whithout the additional argument
    void PointNearestToPlane(zVEC3 &point, const zVEC3 &planeNormal, const zMAT4 &trafoObjToWorld) const{
 //       zERR_ASSERT(trafoObjToWorld.IsUpper3x3Orthonormal());

        PointNearestToPlane(point, planeNormal, trafoObjToWorld, ((zMAT4 &)trafoObjToWorld).ExtractRotation().Transpose());
    }

    // test if a given point lies within the primitive
    zBOOL PointIsIn(const zVEC3 &point, const zMAT4 &trafoObjToWorld) const{
        return PointIsInLocal(trafoObjToWorld.InverseLinTrafo()*point);
    }


    // Do a collision check between <a> and <b> with trafos given by <aTrafo> and <bTrafo> a; return values:
    // direct return: was there a collision?
    // <point>      : collision point (or almost-collision point if there is no collision)
    // <distance>   : distance of the two objects; negative of the intrusion depth if there is a collision
    // <normal>     : collision axis; sliding should happen perpenticular to this.

    static zBOOL CheckCollision(const zCConvexPrimitive *a     ,const zCConvexPrimitive *b     , 
                                const zMAT4             &aTrafo,const zMAT4             &bTrafo,
                                const void              *aVob  ,const void              *bVob  ,
                                zVEC3 &point, zREAL &distance, zVEC3 &normal){
                                    return CheckCollision(a,b,aTrafo,bTrafo,GetCache(aVob,bVob), point, distance, normal);
                                }

    // the same, but with a cache element instead of pointers to the two colliding objects.
    static zBOOL CheckCollision(const zCConvexPrimitive *a     , const zCConvexPrimitive *b     ,
                                const zMAT4             &aTrafo, const zMAT4             &bTrafo,
                                zCConvexCollisionCache *cache,
                                zVEC3 &point, zREAL &distance, zVEC3 &normal);

    // get a pointer to the cache element belonging to two vobs
    static zCConvexCollisionCache *GetCache(const void *aVob ,const void *bVob);

    // sets <point> so that it is inside the primitive with <point, planeNormal> maximal, all that in OBJECT coordinates
    virtual void PointNearestToPlaneLocal(const zVEC3 &planeNormal, zVEC3 &point) const=0;

    // should return a point well inside the convex primitive
    virtual void GetCenterLocal          (zVEC3 &center) const                                          {center=zVEC3(0,0,0);}

    // test if a given point lies within the primitive (local coordinates)
    virtual zBOOL PointIsInLocal            (const zVEC3 &point)  const = 0;

    // symetry functions
    virtual zBOOL SymetrySphere             ()            const                                         {return FALSE;}
    virtual zBOOL SymetryRotation           (zVEC3 &axis) const                                         {return FALSE;}

    virtual void  UpdateBBox                ()                                                          {bbox3Dlocal.maxs=bbox3Dlocal.mins=zVEC3(0,0,0);}

    // get the thing on screen
    void Draw                               (const zMAT4 &trafo, const zCOLOR color=zCOLOR(255,255,255,255), const zCCamera *cam = 0) const;
    virtual void DrawVirtual                ()                                                                                        const;
    static  void DrawLine                   (const zVEC3 &a, const zVEC3 &b);
    static  void DrawLineStrip              (const zVEC3 &a);

    // calculate the distance, possible collision point and the connection vector (only used internally) if the separating plane is given by planeNormal
    static zREAL Distance(const zCConvexPrimitive *a     , const zCConvexPrimitive *b     ,
                          const zMAT4             &aTrafo, const zMAT4             &bTrafo,
                          const zVEC3 &planeNormal, 
                          zVEC3 &point, zVEC3 &connection);

    const zTBBox3D &GetBBox3DLocal          ()                                                    const {return bbox3Dlocal;}
protected:
    zTBBox3D     bbox3Dlocal;
};





// *************************
//     Special Primitives
// *************************

// a sphere with radius 1
class zCConvexPrimitiveUnitSphere: public zCConvexPrimitive{
public:
    zCConvexPrimitiveUnitSphere(){};
    virtual ~zCConvexPrimitiveUnitSphere(){};

    static zCConvexPrimitiveUnitSphere s_unitSphere;

    virtual void PointNearestToPlaneLocal(const zVEC3 &planeNormal, zVEC3 &point) const {point = planeNormal;}
    virtual void DrawVirtual             ()                                       const;

    virtual zBOOL PointIsInLocal         (const zVEC3 &point)                     const;

    virtual zBOOL SymetrySphere          ()                                       const {return TRUE;}
    virtual zBOOL SymetryRotation        (zVEC3 &axis)                            const {axis = zVEC3(0,0,0); return TRUE;}
    virtual void  UpdateBBox             ()                                             {bbox3Dlocal.maxs=zVEC3(1,1,1);bbox3Dlocal.mins=zVEC3(-1,-1,1);}

protected:
};


// a deformed variant  of another primitive: first, scale it by <scale>, then translate it by <trans>.
class zCConvexPrimitiveScaleTrans: public zCConvexPrimitive{
public:
    zCConvexPrimitiveScaleTrans          (zCConvexPrimitive *original, const zVEC3 &scale, const zVEC3 &trans);
    virtual ~zCConvexPrimitiveScaleTrans ();

    virtual void PointNearestToPlaneLocal(const zVEC3 &planeNormal, zVEC3 &point) const;
    virtual void GetCenterLocal          (zVEC3 &center)                          const;
    
    virtual void  UpdateBBox             ()                                            ;

    virtual void  DrawVirtual            ()                                       const;

    virtual zBOOL PointIsInLocal         (const zVEC3 &point)                     const;

    void          Scale                  (zREAL s)                                      {scale *= s; UpdateBBox();} 

    void          SetScale               (const zVEC3 &s)                               {scale = s; UpdateBBox();}
    const zVEC3 & GetScale               ()                                             {return scale;}

    void          SetTranslation         (const zVEC3 &t)                               {translation = t; UpdateBBox();}
    const zVEC3 & GetTranslation         ()                                             {return translation;}

protected:
    zVEC3              scale;
    zVEC3              translation;
    zCConvexPrimitive *original;
};


// axis aligned ellipsoid
class zCConvexPrimitiveEllipsoid: public zCConvexPrimitiveScaleTrans{
public:
    zCConvexPrimitiveEllipsoid           (const zVEC3 &axes, const zVEC3 &center)
        :zCConvexPrimitiveScaleTrans     (&zCConvexPrimitiveUnitSphere::s_unitSphere, axes, center), symetric(FALSE){}

    zCConvexPrimitiveEllipsoid           (const zTBBox3D &box, zBOOL snap = FALSE);

    virtual zBOOL SymetryRotation        (zVEC3 &axis)                            const {if (!symetric) return FALSE; axis = zVEC3(0,1,0); return TRUE;}

    virtual ~zCConvexPrimitiveEllipsoid  (){};

    void    Snap                         ();

private:
    zBOOL   symetric; // is it symmetric in the XZ-Plane?
};
