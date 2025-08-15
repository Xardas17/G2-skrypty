/******************************************************************************** 
 
     $Workfile:: zBVolume.h           $                $Date:: 18.01.01 2:02    $
     $Revision:: 17                   $             $Modtime:: 17.01.01 22:39   $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Bounding Volumes 2D/3D, collision/contact/penetration checks
   created       : 15.3.98

 * $Log: /current_work/zengin_work/_Dieter/zBVolume.h $
 * 
 * 17    18.01.01 2:02 Hildebrandt
 * 
 * 16    20.12.00 3:07 Hildebrandt
 * 
 * 15    14.12.00 19:19 Moos
 * 
 * 14    14.12.00 18:42 Hildebrandt
 * 
 * 13    14.12.00 3:13 Hildebrandt
 * 
 * 12    12.12.00 22:41 Hildebrandt
 * 
 * 11    4.12.00 17:41 Hildebrandt
 * 
 * 10    17.11.00 23:16 Hildebrandt
 * 
 * 9     8.11.00 17:10 Hildebrandt
 * 
 * 8     8.11.00 16:38 Hildebrandt
 * 
 * 7     31.10.00 14:47 Moos
 * 
 * 6     24.10.00 18:26 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 8     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 6     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 5     18.11.99 22:18 Hildebrandt
 * 
 * 4     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 17 $ ($Modtime: 17.01.01 22:39 $)


#ifndef __ZBVOLUME_H__
#define __ZBVOLUME_H__ 

#ifndef __ZALGEBRA_H__
#include <zAlgebra.h>
#endif

#ifndef __ZTYPES3D_H__
#include <zTypes3d.h>
#endif

#ifndef __ZCONTAINER_H__
#include <zContainer.h>
#endif

class	zCFileBIN;		// <zFile3d.h>
class	zCMesh;			// <z3d.h>
class	zCVertex;
class	zCPolygon;
struct	zTPlane;
struct	zTBBox3D;
enum	zTPlaneClass;
// -----------------------------------------------------------------------------------------------

// Bounding-Sphere in 3D
struct zTBCylinder3D {			
	zPOINT3		center;
	zVALUE		radius;	
	zVALUE		heightY;

	zBOOL		IsIntersecting	(const zTBCylinder3D& cylinder) const;
	void		Draw			(const zCOLOR& color=zCOLOR(255,255,0,255)) const;
	void		SetByBBox3D		(const zTBBox3D box);
	void		Translate		(const zVEC3& trans)	{ center += trans; };
};

// -----------------------------------------------------------------------------------------------

// Bounding-Sphere in 3D
struct zTBSphere3D {			
	zPOINT3		center;
	zVALUE		radius;				// evtl. auch/oder squared radius

	zBOOL		IsIntersecting	(const zTBSphere3D& sphere) const;
	zBOOL		IsIntersecting	(const zPOINT3& rayOrg, const zVEC3& ray) const;
	void		Draw			(const zCOLOR& color=zCOLOR(255,255,0,255)) const;
	int			ClassifyPlane	(const zTPlane plane) const;
};

// -----------------------------------------------------------------------------------------------

// Bounding-Box in 2D
struct zTBBox2D {
	zVEC2		mins;
	zVEC2		maxs;
	void Init() { 
		mins[0] = mins [1] = zVALUE_MAX;
		maxs[0] = maxs [1] = zVALUE_MIN;
	};
	void InitMax() { 
		mins[0] = mins [1] = zVALUE_MIN;
		maxs[0] = maxs [1] = zVALUE_MAX;
	};
	// aus this und bbox wird die groessere BBox berechnet
	void CalcGreaterBBox2D (const zTBBox2D& bbox2D) {
		for (int j=0; j<2; j++) {
			mins[j] = zMin (bbox2D.mins[j], mins[j]);
			maxs[j] = zMax (bbox2D.maxs[j], maxs[j]);
		};
	};
	int			Classify		(const zTBBox2D& bbox2D) const;
	void		ClipToBBox2D	(const zTBBox2D& cullBox2D);
	inline void AddPoint		(const zVEC2& p);
	void		Draw			() const;
};

// inlines

inline void zTBBox2D::AddPoint (const zVEC2& p) {
	if (p[0]>maxs[0]) maxs[0] = p[0];
	if (p[0]<mins[0]) mins[0] = p[0];
	if (p[1]>maxs[1]) maxs[1] = p[1];
	if (p[1]<mins[1]) mins[1] = p[1];
};

// -----------------------------------------------------------------------------------------------

// Bounding-Box in 3D
struct zTBBox3D {
	zPOINT3			mins;	
	zPOINT3			maxs;

	void			Init				();
	void			SetMaximumBox		();
	void			InitZero			() { mins=maxs=zVEC3(0); };
	// aus this und bbox wird die groessere BBox berechnet
	void			CalcGreaterBBox3D	(const zTBBox3D& bbox3D);
	void			Transform			(const zMATRIX4& trafo, zTBBox3D& bbox3D) const;
	void			UnTransform			(const zMATRIX4& trafo, zTBBox3D& bbox3D) const;
	void			Translate			(const zVEC3& trans) { mins += trans; maxs += trans; };
	int				Classify			(const zTBBox3D& bbox3D) const;
	inline zBOOL	IsIntersecting		(const zTBBox3D& bbox3D) const;
	inline zBOOL	IsIntersecting		(const zTBSphere3D& sphere) const;
	zBOOL			IsIntersecting		(const zPOINT3& rayOrigin, const zVEC3& rayDirection, zREAL& scaleMin, zREAL& scaleMax ) const;
    zBOOL           IsIntersectingSweep (const zVEC3&    thisTransEnd, const zTBBox3D& box2, const zVEC3& box2TransEnd,    zREAL &time) const { return IsIntersectingSweep(thisTransEnd-box2TransEnd, box2, time); }
    zBOOL           IsIntersectingSweep (const zVEC3&    thisTransEnd, const zTBBox3D& box2,                               zREAL &time) const ;
    zBOOL           IsIntersectingSweep (const zTBBox3D& thisTransEnd, const zTBBox3D& box2, const zTBBox3D& box2TransEnd, zREAL &time) const ;
    zBOOL           IsIntersectingSweep (const zTBBox3D& thisTransEnd, const zTBBox3D& box2,                               zREAL &time) const { return IsIntersectingSweep(thisTransEnd, box2, box2, time); }
	zBOOL			IsTrivIn			(const zTBBox3D& bbox3D) const;
	inline zBOOL	IsTrivIn			(const zPOINT3& point) const;
	zBOOL			IsTrivInLine		(const zPOINT3& point1, const zPOINT3& point2) const;
	zBOOL			TraceRay			(const zPOINT3& rayOrg, const zVEC3& ray, zPOINT3& inters) const;
	zPOINT3			GetNearestPoint		(const zTPlane* const plane) const;
	void			Draw				(const zCOLOR& color=zCOLOR(0,0,255,255)) const;
	void			ClipToBBox3D		(const zTBBox3D& cullBox3D);
	inline zPOINT3	GetCenter			() const { return zPOINT3((mins[0]+maxs[0])*zVALUE(0.5), (mins[1]+maxs[1])*zVALUE(0.5), (mins[2]+maxs[2])*zVALUE(0.5)); };
	inline zVEC3	GetCenterFloor		() const { return zPOINT3((mins[0]+maxs[0])*zVALUE(0.5), (mins[1]),						(mins[2]+maxs[2])*zVALUE(0.5)); };	// mid(X), min(Y), mid(Z)
	zVALUE			GetMinExtent		() const;
	inline zVALUE	GetMaxExtent		() const { return zREAL (0.5F) * zMax (zMax (maxs[0]-mins[0], maxs[1]-mins[1]), maxs[2]-mins[2]); };
	zVALUE			GetVolume			() const;
	zSTRING			GetDescription		() const;
	void			SetByDescription	(zSTRING& desc);
	void			Scale				(const zREAL scaleFac);
	void			Scale				(const zVEC3& scale);
	zTBSphere3D		GetSphere3D			() const;
	zREAL			GetScreenSize		() const;
	zTPlaneClass	ClassifyToPlane		(const zTPlane& plane) const;	
	zTPlaneClass	ClassifyToPlane		(const zTPlane& plane, const int signbits) const;
	int				ClassifyToPlaneSides(const zTPlane& plane) const;
	int				ClassifyToPlaneSides(const zTPlane& plane, const int signbits) const;
	inline int		ClassifyToPlane		(const zREAL planeDist, const int axis) const;	// axis=0,1,2 (=X,Y,Z)
	inline int		ClassifyToPlaneSides(const zREAL planeDist, const int axis) const;	
	void			GetCornerPoints		(zPOINT3* point) const;
	inline void		AddPoint			(const zVEC3& p);
	zREAL			GetFloorArea		() const { return (maxs[VX] - mins[VX]) * (maxs[VZ] - mins[VZ]); };

	void			LoadBIN				(zCFileBIN &file);
	void			SaveBIN				(zCFileBIN &file);

	friend int operator==(const zTBBox3D& box1, const zTBBox3D& box2) { return (box1.mins==box2.mins) && (box1.maxs==box2.maxs); };
};

// inlines

inline zBOOL zTBBox3D::IsIntersecting (const zTBBox3D& bbox3D) const {
	return ((bbox3D.maxs.n[VX]>=mins.n[VX]) && (bbox3D.mins.n[VX]<=maxs.n[VX]) &&
			(bbox3D.maxs.n[VZ]>=mins.n[VZ]) && (bbox3D.mins.n[VZ]<=maxs.n[VZ]) &&
			(bbox3D.maxs.n[VY]>=mins.n[VY]) && (bbox3D.mins.n[VY]<=maxs.n[VY]));
};

inline zBOOL zTBBox3D::IsIntersecting (const zTBSphere3D& sphere) const
{ 
	// Source: http://gamasutra.com/features/19991018/Gomez_4.htm
	// find the square of the distance from the sphere to the box
	zREAL s, d = 0; 
	for (int i=0; i<3; i++ ) 
	{ 
		if( sphere.center[i] < mins[i] )
		{
			s = sphere.center[i] - mins[i];
			d += s*s; 
		}
		else if( sphere.center[i] > maxs[i] )
		{ 
			s = sphere.center[i] - maxs[i];
			d += s*s; 
		}
	}
	return d <= (sphere.radius*sphere.radius);
}
inline zBOOL zTBBox3D::IsTrivIn (const zPOINT3& point) const { 
	return	zInRange (point[VX], mins[VX], maxs[VX]) &&
			zInRange (point[VY], mins[VY], maxs[VY]) &&
			zInRange (point[VZ], mins[VZ], maxs[VZ]);
};

inline void zTBBox3D::AddPoint (const zVEC3& p) {
	if (p[0]>maxs[0]) maxs[0] = p[0];
	if (p[0]<mins[0]) mins[0] = p[0];
	if (p[1]>maxs[1]) maxs[1] = p[1];
	if (p[1]<mins[1]) mins[1] = p[1];
	if (p[2]>maxs[2]) maxs[2] = p[2];
	if (p[2]<mins[2]) mins[2] = p[2];
};

inline int zTBBox3D::ClassifyToPlane (const zREAL planeDist, const int axis) const 
{
	zERR_ASSERT ((axis>=0) && (axis<=2));
	if (planeDist>=maxs[axis])	return zPLANE_BEHIND;	else
	if (planeDist<=mins[axis])	return zPLANE_INFRONT;	else
								return zPLANE_SPANNING;
};

inline int zTBBox3D::ClassifyToPlaneSides(const zREAL planeDist, const int axis) const 
{
	zERR_ASSERT ((axis>=0) && (axis<=2));
	if (planeDist>=maxs[axis])	return 2; else
	if (planeDist<=mins[axis])	return 1; else
								return 3;
};	

inline void zTBBox3D::Init() 
{
	mins[0]=mins[1]=mins[2]= zREAL_MAX;
	maxs[0]=maxs[1]=maxs[2]= zREAL_MIN;
};


// -----------------------------------------------------------------------------------------------

class zCOBBox3D {
public:
	zVEC3				center;			// center
	zVEC3				axis[3];		// orthonormal basis
	zVEC3				extent;			// extent along basis vectors, [0] is largest extent

	zCList<zCOBBox3D>	childs;

	static zMATRIX4		trafoB2ToThis;

	zCOBBox3D () { center = axis[0] = axis[1] = axis[2] = extent = zVEC3(0); };
	zCOBBox3D& operator=(const zCOBBox3D& inOBB);
	~zCOBBox3D();

	// methods
	void			Draw						(int depth=1, zCOLOR color=zCOLOR(0,0,255,255));
	zBOOL			IsLeaf						() const	{ return (childs.GetNumInList()==0); };
	zREAL			GetMaxExtent				() const	{ return extent[0]; };
	zREAL			GetMinExtent				() const	{ return zMin (extent[1], extent[2]); };
	void			BuildOBB					(int numPoly, zCPolygon**polyList, const zBOOL bboxCenter=TRUE);
	void			BuildRec					(int numPoly, zCPolygon** polyList, int depthToGo);
	void			BuildOBBTree				(int numPoly, zCPolygon** polyList, int maxDepth=1);
	void			BuildOBBTree				(zCMesh *mesh, int maxDepth=1);

	// Static Intersection tests
	int				TestIntersectionOBB			(const zCOBBox3D* b2) const;
	int				TestIntersectionTreeRec		(const zCOBBox3D* b2) const;
	int				TestIntersectionTree		(const zCOBBox3D* b2, const zMATRIX4& _trafoB2ToThis) const;
	zBOOL			CheckOBBPolyIntersection	(zCPolygon *poly, const zMATRIX4& trafoWorldToObj) const;
	zBOOL			TraceRay					(const zPOINT3& rayOrg, const zVEC3& ray, zPOINT3& inters) const;

	//
	void			Scale						(const zVEC3& scale)	{ extent = Alg_Prod(extent, scale); };
	void			Transform					(const zMATRIX4& trafo);

	// Misc
	void			LoadBIN						(zCFileBIN &file);
	void			SaveBIN						(zCFileBIN &file);
	zTBBox3D		GetBBox3D					() const;
	void			SetByBBox3D					(const zTBBox3D &bbox3D);

protected:
	zCOBBox3D(const zCOBBox3D&);				// disable
	static zVEC3	Dot							(const zVEC3& a, const zVEC3& b) { return a*b; };
};

#endif