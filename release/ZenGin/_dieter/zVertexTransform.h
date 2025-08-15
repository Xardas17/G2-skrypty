/******************************************************************************** 
 
     $Workfile:: zVertexTransform.h      $                $Date:: 5.12.00 19:18    $
     $Revision:: 5                       $             $Modtime:: 5.12.00 17:30    $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Transformed Vertex Data
   created: 25.5.2000

 * $Log: /current_work/ZenGin/_dieter/zVertexTransform.h $
 * 
 * 5     5.12.00 19:18 Moos
 * 
 * 4     5.12.00 12:04 Moos
 * 
 * 3     4.12.00 18:22 Moos
 * 
 * 2     17.11.00 20:15 Moos
 * 
 * 1     21.09.00 18:51 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 5.12.00 17:30 $)

#ifndef __ZVERTEXTRANSFORM_H__
#define __ZVERTEXTRANSFORM_H__

class zCVertex;

class zCVertexTransform{
public:
    zCVertex   *untransformed;
	zPOINT3		vertCamSpace;			// working
	zVALUE		vertCamSpaceZInv;
	zVALUE		vertScrX, vertScrY;		// working

	// methods
	zCVertexTransform	() { untransformed = NULL; }
	~zCVertexTransform	() { if (untransformed) untransformed->transformedIndex = 0; untransformed = NULL;}
	void		Draw		(const zCOLOR&  col=zCOLOR(255,255,0,255), const zBOOL useZBuffer=FALSE);

    inline zPOINT3 &Position();
    inline int	    Index   ();

    zMEMPOOL_VOLATILE_DECLARATION(zCVertexTransform);
};


/* ----------------------------------------------------------------------
	
    zCVertex::ResetVertexTransform(zCVertexTransform *v)	

    Setzt die Daten von v und seinem Vertex auf den Ursprungszustand 
    (= keine Transformation) zurück

	15.11.2000	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */

inline void zCVertex::ResetVertexTransform(zCVertexTransform *v){
    if (v->untransformed)
        v->untransformed->transformedIndex = 0;
    v->untransformed = NULL;
}

inline void zCVertex::ResetVertexTransform(){
    if (transformedIndex)
        zCVertexTransform::PoolElement(transformedIndex).untransformed = NULL;

    transformedIndex = NULL;
}

inline zBOOL zCVertex::IsTransformed() const{
    return transformedIndex;
}

// use this function if you are sure the vertex has been transformed
inline zCVertexTransform *zCVertex::VertexTransform() const{
    zERR_ASSERT(transformedIndex);

    return &zCVertexTransform::PoolElement(transformedIndex);
}

inline int zCVertex::VertexTransformIndex() const{
    zERR_ASSERT(transformedIndex);

    return transformedIndex;
}

// automatically create the vertex if needed
inline zCVertexTransform* zCVertex::GetVertexTransform(){
    if (transformedIndex)
        return &zCVertexTransform::PoolElement(transformedIndex);
       
    return CreateVertexTransform();
}

inline zPOINT3 &zCVertexTransform::Position(){
    zERR_ASSERT(untransformed);

    return untransformed->position;
}

inline int zCVertexTransform::Index(){
    return PoolIndex(this);
}


/* *****************************************

   zCCamera

  ****************************************** */

inline void zCCamera::Project (zCVertexTransform* vert) const {
	vert->vertCamSpaceZInv	= (zVALUE(1)) / vert->vertCamSpace.n[VZ]; 
	vert->vertScrX			= (vpData.xcenter) + zVALUE((vert->vertCamSpace.n[VX] * zVALUE(viewDistanceX)) * vert->vertCamSpaceZInv);
	vert->vertScrY			= (vpData.ycenter) - zVALUE((vert->vertCamSpace.n[VY] * zVALUE(viewDistanceY)) * vert->vertCamSpaceZInv);
};
inline void zCCamera::ProjectClamp (zCVertexTransform* vert) const {
#ifdef _DEBUG
	if (vert->vertCamSpace.n[VZ]==0) vert->vertCamSpaceZInv = 1; else
#endif
	vert->vertCamSpaceZInv = (zVALUE(1)) / vert->vertCamSpace.n[VZ]; 
	vert->vertScrX = (vpData.xcenter) + zVALUE((vert->vertCamSpace.n[VX] * zVALUE(viewDistanceX)) * vert->vertCamSpaceZInv);
	vert->vertScrY = (vpData.ycenter) - zVALUE((vert->vertCamSpace.n[VY] * zVALUE(viewDistanceY)) * vert->vertCamSpaceZInv);
	zClamp (vert->vertScrX, zVALUE(vpData.xminFloat), zVALUE(vpData.xmaxFloat));
	zClamp (vert->vertScrY, zVALUE(vpData.yminFloat), zVALUE(vpData.ymaxFloat));
};
inline void zCCamera::ProjectClamp (zCVertexTransform* vert, const zVALUE zinv) const {
//		vert->vertCamSpaceZInv = zinv; 
	vert->vertScrX = (vpData.xcenter) + zVALUE((vert->vertCamSpace.n[VX] * zVALUE(viewDistanceX)) * zinv);
	vert->vertScrY = (vpData.ycenter) - zVALUE((vert->vertCamSpace.n[VY] * zVALUE(viewDistanceY)) * zinv);
	zClamp (vert->vertScrX, zVALUE(vpData.xminFloat), zVALUE(vpData.xmaxFloat));
	zClamp (vert->vertScrY, zVALUE(vpData.yminFloat), zVALUE(vpData.ymaxFloat));
};

#endif