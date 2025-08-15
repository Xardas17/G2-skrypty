/******************************************************************************** 
 
     $Workfile:: zProgMeshBuild.cpp   $                $Date:: 8.02.01 12:05    $
     $Revision:: 27                   $             $Modtime:: 7.02.01 3:28     $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Progressive Mesh Builder
   created: 9.11.99

 * $Log: /current_work/zengin_work/_Dieter/zProgMeshBuild.cpp $
 * 
 * 27    8.02.01 12:05 Hildebrandt
 * 
 * 26    2.02.01 20:20 Hildebrandt
 * 
 * 25    31.01.01 5:47 Hildebrandt
 * 
 * 24    30.01.01 5:16 Hildebrandt
 * 
 * 23    27.01.01 19:42 Moos
 * 
 * 22    11.01.01 18:45 Moos
 * 
 * 21    17.11.00 19:29 Moos
 * 
 * 20    11.10.00 19:45 Hildebrandt
 * 
 * 19    28.09.00 19:20 Hildebrandt
 * 
 * 18    22.09.00 2:37 Hildebrandt
 * 
 * 17    22.09.00 0:41 Hildebrandt
 * fix for zCProgMeshProto lockup when dealing with degenerated meshes
 * 
 * 16    21.09.00 22:20 Hildebrandt
 * 
 * 15    21.09.00 21:21 Hildebrandt
 * zenGin 0.94
 * 
 * 14    31.08.00 17:04 Hildebrandt
 * 
 * 12    21.08.00 17:18 Hildebrandt
 * 
 * 11    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 10    21.07.00 14:28 Hildebrandt
 * 
 * 9     10.07.00 14:55 Hildebrandt
 * 
 * 8     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 7     15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 6     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 4     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 3     16.11.99 19:49 Hildebrandt
 * 
 * 2     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 27 $ ($Modtime: 7.02.01 3:28 $)

#include <zCore.h>
#include <zProgMesh.h>
#include <zAlgebra.h>
#include <z3d.h>
#include <zRenderLightContainer.h>
#include <zVertexTransform.h>

// =======================================================================================================================

//#define zPM_USE_QUADRICS

/*
*  For the polygon reduction algorithm we use data structures
*  that contain a little bit more information than the usual
*  indexed face set type of data structure.
*  From a vertex we wish to be able to quickly get the
*  neighboring faces and vertices.
*/

class Triangle;
class Vertex;

class Triangle {
public:
	int					id;											// place of tri in original list
	zTPMWedge*			wedge [3];
	Vertex*				vertex[3];									// the 3 points that make this tri
	zVEC2				texUV [3];		// nur anfangs benutzt
	zVEC3				normal[3];		// nur anfangs benutzt
	zVEC3				triNormal;									// unit vector othogonal to this face
	int					matIndex;
	
	Triangle (	Vertex *v0,Vertex *v1,Vertex *v2, 
				const zVEC2& texUV0	, const zVEC2& texUV1 , const zVEC2& texUV2,
				const zVEC3& normal0, const zVEC3& normal1, const zVEC3& normal2,
				int matIndex,
				int _id);
	~Triangle();
	zBOOL				ComputeNormal	();
	void				ReplaceVertex	(Vertex *vold,Vertex *vnew);
	int					HasVertex		(Vertex *v);
	int					HasVertexIndex	(Vertex *v);
	float				GetArea			();
};

class Vertex {
public:
	int					id;											// place of vertex in original list
	zPOINT3				position;									// location of point in euclidean space
	zCArray<Vertex*>	adjVertList;								// adjacent vertices
	zCArray<Triangle*>	adjTriList;									// adjacent triangles
	float				cost;										// cached cost of collapsing edge
	Vertex*				collapse;									// candidate vertex for collapse
	zMAT4				quadric;
	
	 Vertex(const zPOINT3& v,int _id);
	~Vertex();
	void				RemoveIfNotAdjacent	(Vertex *n);
	int					IsBorder			();
	void				CalcQuadric			();
};

struct zTWedgeColl {
	zTPMWedge			*wedgeFrom;
	zTPMWedge			*wedgeTo;
};

static zCArray<Vertex*>				vertList;						// die aktuelle VertList, wird beim Collapsen laufend modifiziert
static zCArray<Triangle*>			triangleList;					// analog die TriangleList
									
static zCArray<zTPMWedge*>			wedgeList;						// enthaelt alle Wedges des Meshes, wird anfangs mit den Start-Wedges gefuellt, spaeter beim Collapsen koennen neue Wedges entstehen, die auch hier abgelegt werden
static zCArray<zTWedgeColl>			wedgeCollapseList;				// hier werden die Wedge-Collapses gesammelt (pro Vert-Collapse mehrere moeglich)
static zCArray<zTPMVertexUpdate>	vertexUpdateList;				// pro Vert-Vert Collapse kommt ein VertexUpdate dazu

static zCArray<int>					triPermutation;					// enthaelt fuer jedes triangle in Original-Reihenfolge dessen neue Position
static zCArray<int>					vertPermutation;				// das gleiche fuer verts (= position)

// for pmProto Construction
static zCProgMeshProto*				pmProto;
static zCArray<zTPMTriangle>		pmTriList;						// zu Beginn gemachte Kopien (noetig, da der Reduktions-Vorgang destruktiv auf den vertList/triLists arbeitet)
static zCArray<zPMINDEX>			pmTriMatIndexList;				// fuer jedes Tri dessen MatIndex, zu Beginn gemachte Kopien (noetig, da der Reduktions-Vorgang destruktiv auf den vertList/triLists arbeitet)
static zCArray<zVEC3>				pmPosList;
static zCArray<zCMaterial*>			pmMatList;


// =======================================================================================================================

Vertex::Vertex(const zPOINT3&v,int _id) {
	position	= v;
	id			= _id;
	collapse	= 0;
	vertList.Insert(this);
}

Vertex::~Vertex(){
//	assert(face.GetNum()==0);
	if (adjTriList.GetNum()>0) {
//		static int count=0;
//		zerr.Warning ("D: PM: "+zSTRING(count++)+": vertex still has faces: "+zSTRING(adjTriList.GetNum()));
		// Achtung: ist erlaubt, wenn fuer das Mesh kein LOD gebaut werden soll
	};
	for (int i=0; i<adjVertList.GetNum(); i++) 
	{
		adjVertList[i]->adjVertList.RemoveOrder	(this);
	};
	adjVertList.EmptyList	();
	vertList.RemoveOrder	(this);
}

void Vertex::CalcQuadric() {
#ifdef zPM_USE_QUADRICS
	quadric.v[0]	= zVEC4(0,0,0,0);
	quadric.v[1]	= zVEC4(0,0,0,0);
	quadric.v[2]	= zVEC4(0,0,0,0);
	quadric.v[3]	= zVEC4(0,0,0,0);
	
	for (int i=0; i<adjTriList.GetNum(); i++)
	{
		zVEC3 p1	= adjTriList[i]->vertex[0]->position;
		zVEC3 p2	= adjTriList[i]->vertex[1]->position;
		zVEC3 p3	= adjTriList[i]->vertex[2]->position;
		zVEC4 p		= Alg_FindPlaneCoeff (p1,p2,p3);
		p[3] = -p[3];
		float t		= p[0]*position[VX] + p[1]*position[VY] + p[2]*position[VZ] + p[3];
		zMAT4 mat;
		mat.v[0]	= zVEC4( p[0]*p[0],	p[0]*p[1],	p[0]*p[2],	p[0]*p[3]);
		mat.v[1]	= zVEC4( p[0]*p[1],	p[1]*p[1],	p[1]*p[2],	p[1]*p[3]);
		mat.v[2]	= zVEC4( p[0]*p[2],	p[1]*p[2],	p[2]*p[2],	p[2]*p[3]);
		mat.v[3]	= zVEC4( p[0]*p[3],	p[1]*p[3],	p[2]*p[3],	p[3]*p[3]);
		
		mat			= adjTriList[i]->GetArea() * mat;		// weight by area
		quadric		= quadric + mat;
		//		break;
	};
#endif
};

int Vertex::IsBorder() 
{
	int i,j;
	// alle von this ausgehenden Edges durchgehen
	for (i=0; i<adjVertList.GetNum(); i++) 
	{
		int count=0;
		// Anzahl Faces, die an dieser Edge beteiligt sind..
		Triangle	*lastTri= 0;
		for (j=0; j<adjTriList.GetNum(); j++) 
		{
			if(adjTriList[j]->HasVertex(adjVertList[i])) 
			{
				// Edge koplanarer Tris? => gilt auch als Border
				if ((lastTri) && ((adjTriList[j]->triNormal * lastTri->triNormal)<-0.95F))
					return TRUE;
				count ++;
				lastTri = adjTriList[j];
			}
		}
		assert(count > 0);
		if(count==1) {
			return TRUE;
		}
	}
	return FALSE;
};

void Vertex::RemoveIfNotAdjacent (Vertex *n) 
{
	// removes n from adjVertList list if n isn't a neighbor.
	if (!adjVertList.IsInList(n)) return;
	for (int i=0;i<adjTriList.GetNum();i++) 
	{
		if(adjTriList[i]->HasVertex(n)) return;
	}
	adjVertList.RemoveOrder(n);
}

// =======================================================================================================================

Triangle::Triangle (Vertex *v0,Vertex *v1,Vertex *v2, 
					const zVEC2& texUV0	, const zVEC2& texUV1 , const zVEC2& texUV2,
					const zVEC3& normal0, const zVEC3& normal1, const zVEC3& normal2,
					int matIndex,
					int _id
					) 
{
//	assert(v0!=v1 && v1!=v2 && v2!=v0);
	if (!(v0!=v1 && v1!=v2 && v2!=v0))
		zERR_WARNING ("D: PM: degenerate triangle at: "+zSTRING(v0->position.GetString()));
	vertex	[0]		= v0;
	vertex	[1]		= v1;
	vertex	[2]		= v2;
	texUV	[0]		= texUV0;
	texUV	[1]		= texUV1;
	texUV	[2]		= texUV2;
	normal	[0]		= normal0;
	normal	[1]		= normal1;
	normal	[2]		= normal2;
	wedge	[0]		= wedge	[1] = wedge	[2] = 0;
	this->matIndex	= matIndex;
	this->id		= _id;
	ComputeNormal		();
	triangleList.Insert	(this);
	for(int i=0;i<3;i++) 
	{
		vertex[i]->adjTriList.Insert	(this);
		for(int j=0; j<3; j++) 
		{
			if(i!=j) {
				if (!vertex[i]->adjVertList.IsInList (vertex[j]))
					vertex[i]->adjVertList.Insert (vertex[j]);
			}
		}
	}
}

Triangle::~Triangle() 
{
	// Ort in der Collapse-Order eintragen
	if (triPermutation.GetNum()>0)
		triPermutation[id] = triangleList.GetNum()-1;

	//
	int i;
	zERR_ASSERT (triangleList.IsInList (this));
	triangleList.RemoveOrder (this);
	for (i=0;i<3;i++) {
		if (vertex[i]) vertex[i]->adjTriList.RemoveOrder (this);
	}
	for (i=0;i<3;i++) {
		int i2 = (i+1)%3;
		if (!vertex[i] || !vertex[i2]) continue;
		vertex[i ]->RemoveIfNotAdjacent(vertex[i2]);
		vertex[i2]->RemoveIfNotAdjacent(vertex[i ]);
	}
}

int Triangle::HasVertex(Vertex *v) {
	return (v==vertex[0] || v==vertex[1] || v==vertex[2]);
}

int Triangle::HasVertexIndex (Vertex *v) {
	if (v==vertex[0]) return 0;
	if (v==vertex[1]) return 1;
	if (v==vertex[2]) return 2;
	return -1;
}

zBOOL Triangle::ComputeNormal()
{
	zPOINT3 v0=vertex[0]->position;
	zPOINT3 v1=vertex[1]->position;
	zPOINT3 v2=vertex[2]->position;
	triNormal = (v1-v0)^(v2-v1);
	if(triNormal.Length()==0) return FALSE;
	triNormal.Normalize();
	return TRUE;
}

float Triangle::GetArea() {
	zVEC3 sum(0,0,0);
	for (int i=0; i<3; i++) {
		int j		= (i+1)%3;
		sum			+= vertex[i]->position ^ vertex[j]->position;
	}; 
	return float(0.5F) * float(fabs (triNormal * sum));
};

void Triangle::ReplaceVertex (Vertex *vold,Vertex *vnew) {
	assert(vold && vnew);
	assert(vold==vertex[0] || vold==vertex[1] || vold==vertex[2]);
	assert(vnew!=vertex[0] && vnew!=vertex[1] && vnew!=vertex[2]);
	
	//
	if (vold==vertex[0])	vertex[0]=vnew; else
	if (vold==vertex[1])	vertex[1]=vnew; else 
	{
		assert(vold==vertex[2]);
		vertex[2]=vnew;
	}

	int i;
	assert(vold->adjTriList.IsInList	(this));
	vold->adjTriList.RemoveOrder		(this);
	assert(!vnew->adjTriList.IsInList	(this));
	vnew->adjTriList.Insert				(this);

	for(i=0;i<3;i++) 
	{
		vold->RemoveIfNotAdjacent		(vertex[i]);
		vertex[i]->RemoveIfNotAdjacent	(vold);
	}
	for(i=0;i<3;i++) {
		{
			// ASSERT
			assert (vertex[i]->adjTriList.IsInList (this));
			int count=0;
			for (int k=0; k<vertex[i]->adjTriList.GetNum(); k++) 
				if (vertex[i]->adjTriList[k]==this) count++;
			assert (count==1);
		};
		for(int j=0;j<3;j++) if(i!=j) {
			if (!vertex[i]->adjVertList.IsInList(vertex[j]))
				vertex[i]->adjVertList.Insert (vertex[j]);
		}
	}
	ComputeNormal();
}

// =======================================================================================================================

static float ComputeEdgeCollapseCost(Vertex *u,Vertex *v) 
{
	// if we collapse edge uv by moving u to v then how 
	// much different will the model change, i.e. how much "error".
	// Texture, vertex normal, and border vertex code was removed
	// to keep this demo as simple as possible.
	// The method of determining cost was designed in order 
	// to exploit small and coplanar regions for
	// effective polygon reduction.
	// Is is possible to add some checks here to see if "folds"
	// would be generated.  i.e. normal of a remaining face gets
	// flipped.  I never seemed to run into this problem and
	// therefore never added code to detect this case.
	int i;
	float edgelength = (v->position - u->position).Length();
	float curvature=0;

	// find the "sides" triangles that are on the edge uv
	zCArray<Triangle*> sides;
	for (i=0; i<u->adjTriList.GetNum(); i++) 
	{
		if (u->adjTriList[i]->HasVertex(v)){
			sides.Insert (u->adjTriList[i]);
		}
	}
	
	// use the triangle facing most away from the sides 
	// to determine our curvature term
	for (i=0;i<u->adjTriList.GetNum();i++) 
	{
		float mincurv=1;									// curve for face i and closer side to it
		for (int j=0;j<sides.GetNum();j++) 
		{
			// use dot product of face normals. '^' defined in vector
			// FIXME: hier waere ein 'weight by area' moeglich
			float dotprod	= u->adjTriList[i]->triNormal * sides[j]->triNormal;
			mincurv			= zMin(mincurv,(1-dotprod)/2.0f);
		}
		curvature = zMax(curvature,mincurv);
	}

	// deutet ein numSides==2 auf koplanar-Edge hin?
//	if (sides.GetNum()>2)
//		curvature = zMin (1.0F, curvature+0.5F);
	
    // the more coplanar the lower the curvature term 
	// but ignore curvature if u is on a border but v isn't
	if(u->IsBorder() && (sides.GetNum()> 1)) {
		curvature=1;
	};
	
#ifdef zPM_USE_QUADRICS
	// Quadric
	// u=>v
	//	const zMAT4	q	= u->quadric + v->quadric;		// laut Garland
	const zMAT4	q	= u->quadric;					// sollte equivalent sein, da Distanz von v zu QuadricV=0 sein sollte!
	//	zVEC4	destPos	= zVEC3(v->postion.x, v->postion.y, v->postion.z, 1.0F);
	//	float	eror	= destPos * resQuadric * destPos;
	
	float	x		= v->position[VX];
	float	y		= v->position[VY];
	float	z		= v->position[VZ];
	float	error	= q.v[0].n[0]*x*x + 2*q.v[0].n[1]*x*y + 2*q.v[0].n[2]*x*z + 2*q.v[0].n[3]*x 
		+   q.v[1].n[1]*y*y + 2*q.v[1].n[2]*y*z + 2*q.v[1].n[3]*y	
		+   q.v[2].n[2]*z*z + 2*q.v[2].n[3]*z	
		+   q.v[3].n[3];
#endif
//	return error;
//	return error*edgelength*curvature;
	
	// kleiner ist besser
	
	// the more coplanar the lower the curvature term   
	return edgelength * curvature;
	//	return curvature;
	//	return edgelength;
}

static void ComputeEdgeCostAtVertex(Vertex *v) 
{
	// compute the edge collapse cost for all edges that start
	// from vertex v.  Since we are only interested in reducing
	// the object by selecting the min cost edge at each step, we
	// only cache the cost of the least cost edge at this vertex
	// (in member variable collapse) as well as the value of the 
	// cost (in member variable cost).
	if (v->adjVertList.GetNum()==0) {
		// v doesn't have neighbors so it costs nothing to collapse
		v->collapse	= 0;
		v->cost		= -0.01f;
		return;
	}
	v->cost		= zREAL_MAX;
	v->collapse	= 0;
	// search all neighboring edges for "least cost" edge
	for (int i=0;i<v->adjVertList.GetNum();i++) 
	{
		float dist;
		dist = ComputeEdgeCollapseCost(v,v->adjVertList[i]);
		if (dist<v->cost) 
		{
			v->collapse	= v->adjVertList[i];  // candidate for edge collapse
			v->cost		= dist;             // cost of the collapse
		}
	}
}

static zBOOL IsEqualTexUV (zVEC2 texUV1, zVEC2 texUV2) 
{
	const zREAL EPS = zREAL (0.01F);
	zBOOL equal;
	equal=	((zAbs(zREAL(texUV1[0]-texUV2[0])) < EPS) &&
			 (zAbs(zREAL(texUV1[1]-texUV2[1])) < EPS));
	if (equal)	return TRUE;

	// wrap-around
	for (int i=0; i<2; i++) {
		if (texUV1[i]<texUV2[i])	texUV1[i] += zREAL(1.0F); 
		else						texUV2[i] += zREAL(1.0F); 
	};
	equal=	((zAbs(zREAL(texUV1[0]-texUV2[0])) < EPS) &&
			 (zAbs(zREAL(texUV1[1]-texUV2[1])) < EPS));
	return equal;
};

static void CreateWedges (Vertex *vert) 
{
	// erzeugt in den Triangels an diesem Vertex die evtl. nocht nicht vorhanden wedges (inkl. sharing)
	if (!vert)	return;

	// Wedges, die an dieser Position geshared werden koennen, starten an diesem Index
	int actWedgeIndex = wedgeList.GetNum();
	for (int i=0; i<vert->adjTriList.GetNum(); i++)
	{
		for (int j=0; j<3; j++)
		{
			Triangle *tri = vert->adjTriList[i];
			if (tri->vertex[j]	== vert)
			if (tri->wedge[j]	== 0)
			{
				// neue Wedge erzeugen, oder bereits vorhandene sharen ?
				{
					for (int k=actWedgeIndex; k<wedgeList.GetNum(); k++)
					{
						if (IsEqualTexUV (wedgeList[k]->texUV, tri->texUV [j]))
						if (wedgeList[k]->normal.IsEqualEps	(tri->normal[j]))
						{
							// sharing wedge
							assert (wedgeList[k]->position==tri->vertex[j]->id);
							tri->wedge[j] = wedgeList[k];
							break;
						};
					};
					if (tri->wedge[j])	break;	// next tri
				};

				// neue Wedge erzeugen
				zTPMWedge *wedge= zNEW(zTPMWedge);
				wedge->texUV	= tri->texUV [j];
				wedge->normal	= tri->normal[j];
				wedge->position	= tri->vertex[j]->id;
				tri->wedge[j]	= wedge;
				wedgeList.Insert (wedge);
			};
		};
	};
};

static void CreateAllWedges () 
{
	// FIXME: die triList und nicht die vertList durchlaufen!!!
	for (int i=0; i<vertList.GetNum(); i++)
		CreateWedges (vertList[i]);
	zERR_MESSAGE (5, 0, "D: PM: num startWedges: "+zSTRING(wedgeList.GetNum()));
};

static void CalcNewTexUV (Triangle *tri, int vertInd, Vertex *destVert)
{
#if 1
	// ok, wie gehabt (evtl. besseres ueber Quadrics errechnen)
	tri->wedge[vertInd]->texUV	= tri->texUV [vertInd];		
#else
	// FIXME: klappt nicht auf anhieb oder einfach schlechte Ergebnisse..
	// Zielposition auf alte Triangle-Ebene projezieren
	zPOINT3	newPos	= destVert->position;
	newPos			-= (newPos*tri->triNormal) * tri->triNormal;	// BUG: Plane distance fehlt in der Formel..

	//
	int		i		= (vertInd+1)%3;
	int		j		= (vertInd+2)%3; 
	zVEC3	q		= newPos - tri->vertex[vertInd]->position;

	float	x,y;
	zPOINT3 a,b;
	float	ab,bb,qb;

	b				= tri->vertex[i]->position - tri->vertex[vertInd]->position;
	a				= tri->vertex[j]->position - tri->vertex[vertInd]->position;
	ab				= (a*b);
	bb				= (b*b);
	qb				= (q*b);

	x				= ((bb) * (q*a) - (ab) * (qb)) / ((a*a)*(bb) - ((ab)*(ab)));
	y				= ((qb) - x*(ab)) / (bb);

	zVEC2 delta1	= tri->wedge[i]->texUV - tri->wedge[vertInd]->texUV;
	zVEC2 delta0	= tri->wedge[j]->texUV - tri->wedge[vertInd]->texUV;

	tri->wedge[vertInd]->texUV	= tri->wedge[vertInd]->texUV + y*delta0 + x*delta1;
#endif
};

static void LogWedgeCollapse (Vertex *u,Vertex *v)
{
	if (!u)	return;

	// find the "sides" triangles that are on the edge uv
	// finde die kollabierenden wedge-Paare
	zCArray<Triangle*>	sides;
	zCArray<zTPMWedge*> wedgeFromList;		// from u
	zCArray<zTPMWedge*> wedgeToList;		// to v
	for (int i=0;i<u->adjTriList.GetNum();i++) 
	{
		Triangle *tri	= u->adjTriList[i];
		int vind		= tri->HasVertexIndex(v);
		if (vind>=0)
		{
			int uind = tri->HasVertexIndex(u);
			wedgeFromList.Insert	(tri->wedge[uind]);			// mehrfach Eintragungen moeglich, aber nicht so wichtig..
			wedgeToList.Insert		(tri->wedge[vind]);
			sides.Insert			(tri);
		};
	};

	// hier werden die wedgeCollapseList-Eintraege erzeugt
	// Alle Tris um den zu loeschenden Vertex abgehen.
	// Zu den dort liegenden Wedges werden 'ziel-wedges' gesucht, auf die collapsed wird 
	// (entweder gibt es sie bereits, dann werden sie geshared, oder sie werden neu erzeugt).

	// FIXME: einige kollabierende wedges der 'sides' koennten so noch vergessen werden...

	int actWedgeCollIndex = wedgeCollapseList.GetNum();
	for (i=0; i<u->adjTriList.GetNum(); i++)
	{
		Triangle *tri	= u->adjTriList[i];
//		if (sides.IsInList(tri))	continue;

		//
		int uind		= tri->HasVertexIndex(u);
		assert (uind>=0);

		//
		zTWedgeColl wedgeColl;
		int wedgeFromIndex = wedgeFromList.Search (tri->wedge[uind]);
		if (wedgeFromIndex>=0)
		{
			// ein matchendes wedge to/from Paar gefunden (gut)
			// hier wird nur nochmal geguckt, ob dieser WedgeColl bereits in der wedgeCollapseList eingetragen worden ist
			zBOOL newCollapse = TRUE;
			for (int j=actWedgeCollIndex; j<wedgeCollapseList.GetNum(); j++)
			{
				if (wedgeCollapseList[j].wedgeFrom==wedgeFromList	[wedgeFromIndex])
//				if (wedgeCollapseList[j].wedgeTo  ==wedgeToList		[wedgeFromIndex])
				{
					newCollapse = FALSE;
					break;
				};
			};
			if (newCollapse)
			{
				wedgeColl.wedgeFrom = wedgeFromList	[wedgeFromIndex];
				wedgeColl.wedgeTo	= wedgeToList	[wedgeFromIndex];
				assert (wedgeColl.wedgeFrom->position!=wedgeColl.wedgeTo->position);
				wedgeCollapseList.Insert (wedgeColl);
			};
			tri->wedge[uind] = wedgeToList	[wedgeFromIndex];
		} 
		else 
		{
			if (!v)
			{
				// ein einzelner Vert wird entfernt
				// collapse eintragen
				wedgeColl.wedgeFrom = tri->wedge[uind];
				wedgeColl.wedgeTo	= 0;
				wedgeCollapseList.Insert (wedgeColl);
				tri->wedge[uind]	= 0;
			} else {
				// kein Match, neue Wedge am Zielort 'v' erzeugen
				zTPMWedge *wedge	= zNEW(zTPMWedge);

				// so wird diese wedge beim naechsten Durchgang 'share-bar'
				wedgeFromList.Insert(tri->wedge[uind]);
				wedgeToList.Insert	(wedge);

				// collapse eintragen
				wedgeColl.wedgeFrom = tri->wedge[uind];
				wedgeColl.wedgeTo	= wedge;
				wedgeCollapseList.Insert (wedgeColl);

				// neue Wedge mit Daten fuellen
//				*wedge				= *(tri->wedge[uind]);		// erstmal die alten Daten rueberkopieren
//				tri->wedge[uind]	= wedge;
//				CalcNewTexUV		(tri, uind, v);
				wedge->texUV		= tri->texUV [uind];		// ok, wie gehabt (evtl. besseres ueber Quadrics errechnen)
				wedge->normal		= tri->normal[uind];		// FIXME
				wedge->position		= v->id;
				wedgeList.Insert	(wedge);
				tri->wedge[uind]	= wedge;

				assert (wedgeColl.wedgeFrom->position!=wedgeColl.wedgeTo->position);
			};
		};
	};
};

static void Collapse (Vertex *u,Vertex *v) {
	// u => v

	//
//	CreateWedges (u);
//	CreateWedges (v);

	LogWedgeCollapse (u, v);

	// Collapse the edge uv by moving vertex u onto v
	// Actually remove tris on uv, then update tris that
	// have u to have v, and then remove u.
	if (!v) {
		// u is a vertex all by itself so just delete it
		delete u; u=0;
	} else
	{
		assert (u!=v);

#ifdef zPM_USE_QUADRICS
		// Quadric
		// u=>v
		v->quadric = v->quadric + u->quadric;
#endif		
		int i;
		zCArray<Vertex*> tmp;

		// make tmp a list of all the neighbors of u
		tmp = u->adjVertList; 

		// delete triangles on edge uv:
		for (i=u->adjTriList.GetNum()-1;i>=0;i--) 
		{
			if (u->adjTriList[i]->HasVertex(v)) {
				delete (u->adjTriList[i]);
			}
		} 

		// update remaining triangles to have v instead of u
		for(i=u->adjTriList.GetNum()-1;i>=0;i--) {
			u->adjTriList[i]->ReplaceVertex(u,v);
		}
		delete u; u=0;

		// recompute the edge collapse costs for neighboring vertices
		for(i=0;i<tmp.GetNum();i++) {
			ComputeEdgeCostAtVertex(tmp[i]);
		}
	};

	// FIXME
	zTPMVertexUpdate update;
	update.numNewTri			= triangleList.GetNum();
	update.numNewWedge			= wedgeCollapseList.GetNum();	// wird spaeter richtig berechnet
//	update.numTrisModified		= 0;
//	update.firstTriModifiedIndex= 0;
	vertexUpdateList.Insert (update);
}

static void ComputeAllEdgeCollapseCosts() { 
	// For all the edges, compute the difference it would make
	// to the model if it was collapsed.  The least of these
	// per vertex is cached in each vertex object.
	int i;
#ifdef zPM_USE_QUADRICS
	for(i=0;i<vertList.GetNum(); i++) {
		// Quadric
		vertList[i]->CalcQuadric();
	};
#endif
	
	for(i=0;i<vertList.GetNum(); i++) {
		ComputeEdgeCostAtVertex(vertList[i]);
	}
}

/* ----------------------------------------------------------------------
	
    AddVertices(), AddTriangles()

	16.11.2000	[Moos]	
                Hack verordentlicht


   ---------------------------------------------------------------------- */

static void AddVertices (zCMesh *mesh) {
//    zERR_ASSERT_STRICT(mesh->numVert < 65000);

	for (int i=0; i<mesh->numVert; i++)
	{
//		Vertex *v = zNEW(Vertex(mesh->vertList[i]->position,i));
		zNEW(Vertex(mesh->Vertex(i)->position,i));		// fuegt sich im ctor in Liste ein!
        mesh->Vertex(i)->ResetVertexTransform();
		mesh->Vertex(i)->hackData = i;				        
	};
}

// [Moos] macht den Numerierungshack vom oben rückgängig
static void UnHack (zCMesh *mesh){
	for (int i=0; i<mesh->numVert; i++)
        mesh->Vertex(i)->hackData = 0;
}

static void AddTriangles (zCMesh *mesh) {
	for(int i=0;i<mesh->numPoly; i++) 
	{
		zCPolygon	*poly	= mesh->Poly(i);
		zBOOL		hasTex	= poly->GetMaterial()->GetTexture()!=0;
		
		// Material eintragen
		int matIndex = pmMatList.Search (poly->GetMaterial());
		if (matIndex<0) {
			if (poly->GetMaterial()->GetAlphaBlendFunc()==zRND_ALPHA_FUNC_TEST)
			{
				mesh->SetAlphaTestingEnabled(TRUE);
			}
			else if (hasTex)
			{
				poly->GetMaterial()->GetTexture()->CacheIn(-1); // muss, ansonsten ist hier der alphakanal status noch unbekannt
				
				if (poly->GetMaterial()->GetTexture()->HasAlpha())
				{
					mesh->SetAlphaTestingEnabled(TRUE);
				}
			}

			matIndex = pmMatList.GetNum();
			pmMatList.Insert (poly->GetMaterial());
			poly->GetMaterial()->AddRef();
		};

		zERR_ASSERT (poly->polyNumVert==3);
		// fuegt sich im ctor in Liste ein!
//		Triangle *t=new Triangle(
		new Triangle(
			vertList[int(poly->vertex[0]->hackData)],
			vertList[int(poly->vertex[1]->hackData)],
			vertList[int(poly->vertex[2]->hackData)],
			hasTex ? zVEC2(poly->feature[0]->texu, poly->feature[0]->texv) : zVEC2(0.0F),
			hasTex ? zVEC2(poly->feature[1]->texu, poly->feature[1]->texv) : zVEC2(0.0F),
			hasTex ? zVEC2(poly->feature[2]->texu, poly->feature[2]->texv) : zVEC2(0.0F),
			poly->feature[0]->vertNormal,
			poly->feature[1]->vertNormal,
			poly->feature[2]->vertNormal,
			matIndex,
			i
		);
	}
}

static Vertex *MinimumCostEdge(){
	// Find the edge that when collapsed will affect model the least.
	// This funtion actually returns a Vertex, the second vertex
	// of the edge (collapse candidate) is stored in the vertex data.
	// Serious optimization opportunity here: this function currently
	// does a sequential search through an unsorted list :-(
	// Our algorithm could be O(n*lg(n)) instead of O(n*n)
	Vertex *mn=vertList[0];
	for(int i=0;i<vertList.GetNum(); i++) {
		if(vertList[i]->cost < mn->cost) {
			mn = vertList[i];
		}
	}
	return mn;
}

// =======================================================================================================================

template <class T>
static inline zDWORD CalcArraySize (zCArray<T> array) {
	return sizeof(T) * array.GetNum();
}

struct zTLazyMesh {
	zCArray<int>				wedgePermut;			// x nur fullMesh
	zCArray<int>				wedgeParent;			// x nur fullMesh
	zCArray<zPMINDEX>			triMatIndexList;		// x nur fullMesh
	zCArray<zPOINT3>			posList;				// x nur fullMesh, SIZE
	zCArray<zVEC3>				posNormalList;			//   nur fullMesh, SIZE

	zCArray<zCMaterial*>		matList;
	zCArray<zTPMTriangle>		triList;				// x, SIZE
	zCArray<zTPMWedge>			wedgeList;				// x, SIZE
	zCArray<zREAL>				colorList;				// x, SIZE
	zCArray<zPMINDEX>			wedgeMap;				// x, SIZE
	zCArray<zTPMVertexUpdate>	vertexUpdates;			// x, SIZE
	zCArray<zPMINDEX>			triPlaneIndexList;		// x, SIZE
	zCArray<zTPlane>			triPlaneList;			// x, SIZE
	zCArray<zTPMTriangleEdges>	triEdgeList;			//  , SIZE
	zCArray<zTPMEdge>			edgeList;				//  , SIZE
	zCArray<zREAL>				edgeScoreList;			//  , SIZE

	zDWORD CalcSizeBytesFullMeshPart()
	{
		zDWORD size=0;
		size += CalcArraySize (posList);
		size += CalcArraySize (posNormalList);
		return size;
	};
	zDWORD CalcSizeBytes()
	{
		zDWORD size=0;
		size += CalcArraySize (triList);
		size += CalcArraySize (wedgeList);
		size += CalcArraySize (colorList);
		size += CalcArraySize (wedgeMap);
		size += CalcArraySize (vertexUpdates);
		size += CalcArraySize (triPlaneIndexList);
		size += CalcArraySize (triPlaneList);
		size += CalcArraySize (triEdgeList);
		size += CalcArraySize (edgeList);
		size += CalcArraySize (edgeScoreList);
		return size;
	};
};

void zCProgMeshBuilder::CreatePMTriPosList ()
{
	//
	CreateAllWedges				();

	//
	zREAL areaSum=0;
	pmTriList.AllocAbs			(triangleList.GetNum());		pmTriList.MarkNumAllocUsed	();
	pmTriMatIndexList.AllocAbs	(triangleList.GetNum());		pmTriMatIndexList.MarkNumAllocUsed	();
	for (int i=0; i<triangleList.GetNum(); i++)
	{
		for (int j=0; j<3; j++) 
		{
			pmTriList[i].wedge[j] = wedgeList.Search (triangleList[i]->wedge[j]);		// index
		};
		pmTriMatIndexList[i]	= triangleList[i]->matIndex;

		areaSum += triangleList[i]->GetArea();
	};
//	pmProto->avgTriArea	= (areaSum / float(triangleList.GetNum())) / pmProto->bbox3D.GetVolume();
//	pmProto->avgTriArea	= pmProto->bbox3D.GetVolume() / (areaSum / float(triangleList.GetNum()));
//	pmProto->avgTriArea	= areaSum / float(triangleList.GetNum());
	zREAL boxVolume		= pmProto->bbox3D.GetVolume();
	pmProto->avgTriArea	= (boxVolume==0) ? 0 : float(triangleList.GetNum()) / boxVolume;
	zerr.Message ("D: PM: avgArea: "+zSTRING(pmProto->avgTriArea,5));

	//
	pmPosList.AllocAbs			(vertList.GetNum());
	pmPosList.MarkNumAllocUsed	();
	for (i=0; i<vertList.GetNum(); i++)
	{
		pmPosList[i] = vertList[i]->position;
	};

	// start-state
	zTPMVertexUpdate update;
	update.numNewTri			= triangleList.GetNum();
	update.numNewWedge			= 0;
//	update.numTrisModified		= 0;
//	update.firstTriModifiedIndex= 0;
	vertexUpdateList.Insert (update);
};

void zCProgMeshBuilder::CalcPrelight (zTLazyMesh &fullMesh, zTLazyMesh &subMesh) 
{
	// assert: wedgeList wurde vorher konstruiert
	// Die WedgeList muss ausserdem schon in der richtigen Reihenfolge vorliegen
	zERR_ASSERT (subMesh.wedgeList.GetNum()>0);

	subMesh.colorList.AllocAbs (subMesh.wedgeList.GetNum());		subMesh.colorList.MarkNumAllocUsed();
	
	//
	const zMAT4&	trafoWorldToObj			= Alg_Identity3D();
	zCRenderLightContainer renderLightCont;
	renderLightCont.CreatePrelightConfig	(pmProto->bbox3D);
	renderLightCont.Activate				(trafoWorldToObj);

	zVEC3 color;
	for (int i=0; i<subMesh.wedgeList.GetNum(); i++)
	{
		color					= renderLightCont.LightVertex	(fullMesh.posList[subMesh.wedgeList[i].position], subMesh.wedgeList[i].normal);
		zREAL res				= (((0.299F)*color[0] + (0.587F)*color[1] + (0.114F)*color[2])) / (255.0F);
//		res						+= 0.2F;
		zClamp01				(res);
		subMesh.colorList[i]	= res;
//		pmColorList[i]	= wedgeList[i]->normal;
	};
};

void zCProgMeshBuilder::CalcPosNormals (zTLazyMesh &fullMesh) 
{
	// assert: wedgeList wurde vorher konstruiert
	// Die WedgeList muss ausserdem schon in der richtigen Reihenfolge vorliegen
	zERR_ASSERT (fullMesh.wedgeList.GetNum()>0);
	zERR_ASSERT (fullMesh.posList.GetNum()>0);

	fullMesh.posNormalList.AllocAbs (fullMesh.posList.GetNum());	fullMesh.posNormalList.MarkNumAllocUsed();

	for (int i=0; i<fullMesh.wedgeList.GetNum(); i++)
	{
		int		posIndex				= fullMesh.wedgeList[i].position;
		zVEC3	normal					= fullMesh.wedgeList[i].normal;
		zREAL	len						= normal.Length();
		if ((len<=0.98F) || (len>1.02F))  { normal = zVEC3(0,0,0); fullMesh.wedgeList[i].normal = zVEC3(-1,-1,0).Normalize(); };
		fullMesh.posNormalList[posIndex]= normal;
	};
};

void zCProgMeshBuilder::CalcTriPlaneList (const zTLazyMesh &fullMesh, zTLazyMesh &subMesh)
{
	#define EPSILON_PLANE_DISTANCE		zREAL(0.1F)
	#define EPSILON_PLANE_NORMAL		zREAL(0.95F)

	int numPlanes=0;
	subMesh.triPlaneIndexList.AllocAbs	(subMesh.triList.GetNum());		subMesh.triPlaneIndexList.MarkNumAllocUsed();
	subMesh.triPlaneList.AllocAbs		(subMesh.triList.GetNum());

	for (int i=0; i<subMesh.triList.GetNum(); i++) 
	{
		zTPlane			plane;
		zTPMTriangle&	tri					= subMesh.triList[i];
		const zPOINT3&	pos0				= fullMesh.posList[subMesh.wedgeList[tri.wedge[0]].position];
		const zPOINT3&	pos1				= fullMesh.posList[subMesh.wedgeList[tri.wedge[1]].position];
		const zPOINT3&	pos2				= fullMesh.posList[subMesh.wedgeList[tri.wedge[2]].position];

		if (Alg_IsColinear (pos0, pos1, pos2)) {
			plane.normal			= -pos0;
			plane.normal.Normalize	();
			plane.distance			= 0;
			subMesh.triPlaneList.Insert (plane);
			subMesh.triPlaneIndexList[i] = numPlanes;
			numPlanes++;
		} else {
			zVEC4 planeVec			= Alg_FindPlaneCoeff (pos0, pos1, pos2);
			plane.normal			= zVEC3(planeVec[0], planeVec[1], planeVec[2]);
			plane.distance			= planeVec[3];

			// kam dieselbe Plane bereits vor ? => sharen
			zBOOL found = FALSE;
			for (int j=0; j<numPlanes; j++) 
			{
				const zTPlane& plane2 = subMesh.triPlaneList[j];
				if ((zAbs((plane.distance)-(plane2.distance))	<= EPSILON_PLANE_DISTANCE) && 
					(    (((plane.normal) *(plane2.normal)))	>= EPSILON_PLANE_NORMAL))
				{
					found = TRUE;
					break;
				}; 
			};
			if (!found)
			{
				subMesh.triPlaneList.Insert (plane);
				subMesh.triPlaneIndexList[i]= numPlanes;
				numPlanes++;
			} else
				subMesh.triPlaneIndexList[i]= j;
		};
		zERR_ASSERT_STRICT (numPlanes<=subMesh.triPlaneList.GetNum());
	};
};

// Das Template benoetigt dies ausserhalb der Methode..
struct zTEdgeScore {
	int		edgeIndex;
	zREAL	score;
};

static int CompareEdgeScores (const void *arg1, const void *arg2) {
	zTEdgeScore* edgeScore1	= ((zTEdgeScore*)arg1); 
	zTEdgeScore* edgeScore2	= ((zTEdgeScore*)arg2);
	if (edgeScore1->score<edgeScore2->score)	return -1;
	else										return +1;
};

void zCProgMeshBuilder::CalcSubdivData (const zTLazyMesh &fullMesh, zTLazyMesh &subMesh)
{
	// triEdgeList, edgeList, edgeScoreList
	subMesh.triEdgeList.AllocAbs	(subMesh.triList.GetNum());	subMesh.triEdgeList.MarkNumAllocUsed();
	zCArray<zTPMEdge> localEdgeList	(subMesh.triList.GetNum());	// approx
	
	// Tris ablaufen
	for (int i=0; i<subMesh.triList.GetNum(); i++)
	{
		// Edges des Tris abgehen
		for (int j=0; j<3; j++)
		{
			int jnext=j+1; if (jnext==3) jnext=0;
			// Edge bereits registriert ?
			zBOOL found = FALSE;
			for (int k=0; k<localEdgeList.GetNum(); k++)
			{
				if (((localEdgeList[k].wedge[0]==subMesh.triList[i].wedge[j]) && (localEdgeList[k].wedge[1]==subMesh.triList[i].wedge[jnext])) ||
				    ((localEdgeList[k].wedge[1]==subMesh.triList[i].wedge[j]) && (localEdgeList[k].wedge[0]==subMesh.triList[i].wedge[jnext])))
				{
					found = TRUE;
					break;
				};
			};
			if (!found)
			{
				zTPMEdge edge;
				edge.wedge[0]			= subMesh.triList[i].wedge[j];
				edge.wedge[1]			= subMesh.triList[i].wedge[jnext];
				localEdgeList.InsertEnd	(edge);
			};
			subMesh.triEdgeList[i].edge[j]	= k;
		};
	};

	// edgeScoreList berechnen
	zCArraySort<zTEdgeScore> edgeScoreList(localEdgeList.GetNum());		edgeScoreList.MarkNumAllocUsed();
	edgeScoreList.SetCompare (CompareEdgeScores);
	for (i=0; i<edgeScoreList.GetNum(); i++)
	{
		int wedgeIndex0				= localEdgeList[i].wedge[0];
		int wedgeIndex1				= localEdgeList[i].wedge[1];
		int posIndex0				= subMesh.wedgeList[wedgeIndex0].position;
		int posIndex1				= subMesh.wedgeList[wedgeIndex1].position;
		zREAL score					= 0;
/*		{
			zREAL edgeLen			= (fullMesh.posList[posIndex0]-fullMesh.posList[posIndex1]).Length();
			zREAL dot				= fullMesh.posNormalList[posIndex0] * fullMesh.posNormalList[posIndex1];
			if (dot<-0.2F)	dot		= 1;
			zClamp01				(dot);
			dot						= 1.0F - dot;
			score					= (0.2F * edgeLen * dot);
		};
*/
		{
			const zREAL		edgeLen = (fullMesh.posList[posIndex0]-fullMesh.posList[posIndex1]).Length();
			const zVEC3&	normal0	= fullMesh.posNormalList[posIndex0];
			const zVEC3&	normal1	= fullMesh.posNormalList[posIndex1];
			zVEC3&	edgeVec			= (fullMesh.posList[posIndex1]-fullMesh.posList[posIndex0]);
			if (edgeVec.Length()>0)
			{
				edgeVec.Normalize		();
				zREAL dot				= ((normal0*edgeVec)		  * (normal1*edgeVec)) + 
										  ((normal0^edgeVec).Length() * (normal1^edgeVec).Length());
				//			Keine Subdiv, wenn VertNormal zu sehr von edgeVec abweicht..
				//			if ((edgeVec*normal0)<..
				if (dot<-0.1F)	dot		= 1;
				zClamp01				(dot);
				dot						= 1.0F - dot;
				score					= (0.2F * edgeLen * dot);
			};
		};

		edgeScoreList[i].edgeIndex	= i;
		edgeScoreList[i].score		= score;
	};
//	edgeScoreList.QuickSort		();

	// EdgeScores
	subMesh.edgeScoreList.AllocAbs	(localEdgeList.GetNum());	subMesh.edgeScoreList.MarkNumAllocUsed();
	for (i=0; i<localEdgeList.GetNum(); i++)
	{
		subMesh.edgeScoreList[i]	= edgeScoreList[i].score;
	};

	// EdgeListe in korrekter Reihenfolge erzeugen/umsortieren
	subMesh.edgeList.AllocAbs		(localEdgeList.GetNum());	subMesh.edgeList.MarkNumAllocUsed();
	for (i=0; i<subMesh.edgeList.GetNum(); i++)
	{
		subMesh.edgeList[i]			= localEdgeList[edgeScoreList[i].edgeIndex];
	};

	// Tris ablaufen
	for (i=0; i<subMesh.triList.GetNum(); i++)
	{
		// Edges des Tris abgehen 
		for (int j=0; j<3; j++)
		{
			int oldEdgeIndex				= subMesh.triEdgeList[i].edge[j];
			subMesh.triEdgeList[i].edge[j]	= edgeScoreList[oldEdgeIndex].edgeIndex;
		};
	};
};

void zCProgMeshBuilder::CreateLazySubMesh (int buildFlags, zTLazyMesh& fullMesh, zTLazyMesh& subMesh)
{
	// 
	int i;
	zCArray<int>	mapWedgeIndexFullToSub(fullMesh.wedgeList.GetNum());		mapWedgeIndexFullToSub.MarkNumAllocUsed();
//	mapWedgeIndexFullToSub.ZeroFill	();
	for (i=0; i<mapWedgeIndexFullToSub.GetNum(); i++)
		mapWedgeIndexFullToSub[i]=-1;

	int numTriSubMesh=0;
	// Alle direkt benutzten Wedges des FullMesh markieren
	for (i=0; i<fullMesh.triList.GetNum(); i++)
	{
		if (fullMesh.matList[fullMesh.triMatIndexList[i]]==subMesh.matList[0])
		{
			++numTriSubMesh;
			for (int j=0; j<3; j++)
				mapWedgeIndexFullToSub[fullMesh.triList[i].wedge[j]]	= -2;
		};
	};

	// Alle per Collapse benutzten Wedges markieren
	// (nicht noetig, falls gar kein LOD vorliegt)
	if (!(buildFlags & zPM_BUILD_FLAG_NO_LOD)) 
	{
		for (i=0; i<mapWedgeIndexFullToSub.GetNum(); i++)
		{
			if (mapWedgeIndexFullToSub[i]==-2)
			{
				int wedgeIndex = i;
				while ((wedgeIndex>0) && (wedgeIndex!=zPMINDEX_NONE)) {
					mapWedgeIndexFullToSub[wedgeIndex]	= -2;
					wedgeIndex							= fullMesh.wedgeMap[wedgeIndex];
					if (wedgeIndex==zPMINDEX_NONE)				break;
					if (mapWedgeIndexFullToSub[wedgeIndex]==-2)	break;	// bereits dagewesen?
				};
			};
		};
	};
	
	// wedgeList uebertragen
	int numWedgeSubMesh=0;
	for (i=0; i<mapWedgeIndexFullToSub.GetNum(); i++)
		if (mapWedgeIndexFullToSub[i]==-2) numWedgeSubMesh++;
	zCArray<int>	mapWedgeIndexSubToFull;
	mapWedgeIndexSubToFull.AllocAbs (numWedgeSubMesh);	mapWedgeIndexSubToFull.MarkNumAllocUsed();
	subMesh.wedgeList.AllocAbs		(numWedgeSubMesh);	subMesh.wedgeList.MarkNumAllocUsed();
	{ 
		int num=0;
		for (i=0; i<mapWedgeIndexFullToSub.GetNum(); i++)
		{
			if (mapWedgeIndexFullToSub[i]==-2)
			{
				subMesh.wedgeList[num]		= fullMesh.wedgeList[i];
				mapWedgeIndexSubToFull[num]	= i;
				mapWedgeIndexFullToSub[i]	= num++;
			};
		};
	};

	// triList uebertragen
	subMesh.triList.AllocAbs (numTriSubMesh);		subMesh.triList.MarkNumAllocUsed();
	{
		int num=0;
		for (i=0; i<fullMesh.triList.GetNum(); i++)
		{
			if (fullMesh.matList[fullMesh.triMatIndexList[i]]==subMesh.matList[0])
			{
				for (int j=0; j<3; j++)
				{
//					zERR_ASSERT (mapWedgeIndexFullToSub[fullMesh.triList[i].wedge[j]]>0);
					// WedgeIndex des FullMesh wird auf den WedgeIndex des SubMesh gemaped
					subMesh.triList[num].wedge[j]	= mapWedgeIndexFullToSub[fullMesh.triList[i].wedge[j]];
				};
				++num;
			};
		};
	};

	// wedgeMap
	if (!(buildFlags & zPM_BUILD_FLAG_NO_LOD)) 
	{
		subMesh.wedgeMap.AllocAbs (subMesh.wedgeList.GetNum());		subMesh.wedgeMap.MarkNumAllocUsed();
		for (i=0; i<subMesh.wedgeMap.GetNum(); i++)
		{
			// ein subWedgeIndex 'i' wird in den fullWedgeIndex umgewandelt
			// .. dessen Collapse-Ziel wird ueber die fullWedgeMap ermittelt
			// .. und wieder in ein subWedgeIndex umgewandelt
			int fullWedgeIndex		= mapWedgeIndexSubToFull[i];
			int fullWedgeDestIndex	= fullMesh.wedgeMap[fullWedgeIndex];
			subMesh.wedgeMap[i]		= fullWedgeDestIndex==zPMINDEX_NONE  ? fullWedgeDestIndex : mapWedgeIndexFullToSub[fullWedgeDestIndex];
		};
	};

	// vertexUpdates
	if (!(buildFlags & zPM_BUILD_FLAG_NO_LOD)) 
	{
		// LOD
		subMesh.vertexUpdates	= fullMesh.vertexUpdates;
		int numTri				= subMesh.triList.GetNum();
		int numWedge			= subMesh.wedgeList.GetNum();
		for (i=subMesh.vertexUpdates.GetNum()-1; i>=0; i--)
		{
			subMesh.vertexUpdates[i].numNewTri	= numTri;
			subMesh.vertexUpdates[i].numNewWedge= numWedge;
			if (i>0)
			{
				int fullTriDelta	= fullMesh.vertexUpdates[i].numNewTri  - subMesh.vertexUpdates[i-1].numNewTri;
				int fullWedgeDelta	= fullMesh.vertexUpdates[i].numNewWedge- subMesh.vertexUpdates[i-1].numNewWedge;
				int fullNumTri		= fullMesh.vertexUpdates[i].numNewTri;
				int fullNumWedge	= fullMesh.vertexUpdates[i].numNewWedge;
				for (int j=fullNumTri-1; j>=fullNumTri-fullTriDelta; j--)
				{
					if (fullMesh.matList[fullMesh.triMatIndexList[j]]==subMesh.matList[0])
						--numTri;
				};
				for (j=fullNumWedge-1; j>=fullNumWedge-fullWedgeDelta; j--)
				{
					if (mapWedgeIndexFullToSub[j]>0)
						--numWedge;
				};
			};
		};
	} else {
		// kein LOD
		subMesh.vertexUpdates.AllocAbs(1);		  subMesh.vertexUpdates.MarkNumAllocUsed();
		subMesh.vertexUpdates[0].numNewTri		= subMesh.triList.GetNum();
		subMesh.vertexUpdates[0].numNewWedge	= subMesh.wedgeList.GetNum();
	};

	// TriPlane List
	if (!(buildFlags & zPM_BUILD_FLAG_NO_TRIPLANES))
		CalcTriPlaneList (fullMesh, subMesh);

	// Subdiv Data
	if ((buildFlags & zPM_BUILD_FLAG_CREATE_SUBDIV_DATA))
		CalcSubdivData  (fullMesh, subMesh);

	// Prelight (am Ende)
	// => derzeit deaktiviert, wird von der RenderEngine nicht genutzt!
//	CalcPrelight (fullMesh, subMesh);
	
	//
/*	{
		for (i=0; i<subMesh.triList.GetNum(); i++)
		{
			zERR_MESSAGE (0,0,"D: tri "+zSTRING(i)+": "+zSTRING(subMesh.triList[i].wedge[0])+","+zSTRING(subMesh.triList[i].wedge[1])+","+zSTRING(subMesh.triList[i].wedge[2]));
		};
	};*/
};

template <class T>
static inline void SetAndCopyArrayAdapt (zBYTE* &dataWalk, zCArrayAdapt<T> &arrayDest, const zCArray<T> &arraySrc) 
{
	dataWalk	+= arrayDest.SetArray (dataWalk, arraySrc.GetNum());
	memcpy		(arrayDest.GetArray(), arraySrc.GetArray(), sizeof(T) * arrayDest.GetNum());
};

void zCProgMeshBuilder::CopySubMeshData (zBYTE* &dataWalk, const zTLazyMesh& lazyMesh, zCProgMeshProto::zCSubMesh *subMesh)
{
/*	zCArray<zCMaterial*>		matList;
	zCArray<zTPMTriangle>		triList;				// x, SIZE
	zCArray<zTPMWedge>			wedgeList;				// x, SIZE
	zCArray<zREAL>				colorList;				// x, SIZE
	zCArray<zPMINDEX>			wedgeMap;				// x, SIZE
	zCArray<zTPMVertexUpdate>	vertexUpdates;			// x, SIZE
	zCArray<zPMINDEX>			triPlaneIndexList;		//  , SIZE
	zCArray<zTPlane>			triPlaneList;			//  , SIZE
*/
	// WICHTIG: Dieser Code legt das Speicher Layout fest!!!

	SetAndCopyArrayAdapt (dataWalk, subMesh->triList			, lazyMesh.triList);
	SetAndCopyArrayAdapt (dataWalk, subMesh->wedgeList			, lazyMesh.wedgeList);
	SetAndCopyArrayAdapt (dataWalk, subMesh->wedgeMap			, lazyMesh.wedgeMap);
	SetAndCopyArrayAdapt (dataWalk, subMesh->colorList			, lazyMesh.colorList);
	SetAndCopyArrayAdapt (dataWalk, subMesh->vertexUpdates		, lazyMesh.vertexUpdates);
	SetAndCopyArrayAdapt (dataWalk, subMesh->triPlaneIndexList	, lazyMesh.triPlaneIndexList);
	SetAndCopyArrayAdapt (dataWalk, subMesh->triPlaneList		, lazyMesh.triPlaneList);
	SetAndCopyArrayAdapt (dataWalk, subMesh->triEdgeList		, lazyMesh.triEdgeList);
	SetAndCopyArrayAdapt (dataWalk, subMesh->edgeList			, lazyMesh.edgeList);
	SetAndCopyArrayAdapt (dataWalk, subMesh->edgeScoreList		, lazyMesh.edgeScoreList);
};

void zCProgMeshBuilder::CreateFinalPMData (int buildFlags)
{
	// 
	int i;
	zBOOL hasJustOneMaterial = pmMatList.GetNum()==1;
//	zBOOL hasJustOneMaterial = FALSE;

	zTLazyMesh fullMesh;

	// Wedge Permutation berechnen
	// (erst nach dem kompletten Reduktions-Vorgang sind alle Wedges und damit die Permutations-Liste bekannt)
	fullMesh.wedgePermut.AllocAbs	(wedgeList.GetNum());	fullMesh.wedgePermut.MarkNumAllocUsed();
	fullMesh.wedgeParent.AllocAbs	(wedgeList.GetNum());	fullMesh.wedgeParent.MarkNumAllocUsed();
	int wedgeFrontCtr=0;
	for (i=0; i<wedgeList.GetNum(); i++)
	{
		fullMesh.wedgePermut[i] = -1;
		fullMesh.wedgeParent[i] = zPMINDEX_NONE;
		for (int j=0; j<wedgeCollapseList.GetNum(); j++)
		{
			if (wedgeCollapseList[j].wedgeFrom==wedgeList[i])
			{
				fullMesh.wedgePermut[i] = (wedgeList.GetNum()-1)-j;
				fullMesh.wedgeParent[i] = wedgeList.Search (wedgeCollapseList[j].wedgeTo);
				assert (fullMesh.wedgeParent[i]>=0);
				break;
			};
		};
		// nicht kollabierte Wedges vorne eintragen
		if (fullMesh.wedgePermut[i]<0)	
			fullMesh.wedgePermut[i] = wedgeFrontCtr++;
	};

//	for (i=0; i<triPermutation.GetNum(); i++)			triPermutation[i] = i;
//	for (i=0; i<vertPermutation.GetNum(); i++)			vertPermutation[i] = i;
//	for (i=0; i<fullMesh.wedgePermut.GetNum(); i++)		fullMesh.wedgePermut[i] = i;

	// matList
	fullMesh.matList			= pmMatList;

	// posList
	fullMesh.posList.AllocAbs (pmPosList.GetNum());	fullMesh.posList.MarkNumAllocUsed();
	for (i=0; i<vertPermutation.GetNum(); i++)
	{
		fullMesh.posList[vertPermutation[i]]= pmPosList[i];
	};

	// wedgeList, wedgeMap
	fullMesh.wedgeList.AllocAbs		(wedgeList.GetNum());	fullMesh.wedgeList.MarkNumAllocUsed();
	if (!(buildFlags & zPM_BUILD_FLAG_NO_LOD)) {
		fullMesh.wedgeMap.AllocAbs	(wedgeList.GetNum());	fullMesh.wedgeMap.MarkNumAllocUsed();
	};
	for (i=0; i<wedgeList.GetNum(); i++)
	{
		int destIndex = fullMesh.wedgePermut[i];
		fullMesh.wedgeList[destIndex]			= *(wedgeList	 [i]);
		fullMesh.wedgeList[destIndex].position	= vertPermutation[fullMesh.wedgeList[destIndex].position];
		if (!(buildFlags & zPM_BUILD_FLAG_NO_LOD)) {
			fullMesh.wedgeMap [destIndex]		= fullMesh.wedgeParent	 [i]!=zPMINDEX_NONE ? fullMesh.wedgePermut [fullMesh.wedgeParent[i]] : zPMINDEX_NONE;
		}
	};

	// triList
	// triMatIndexList (fuer jedes Tri dessen Material-Index)
	// (nicht kollabierte Tris werden unsortiert am Anfang der Liste eingetragen, kollabierte in ihrer Reihenfolge am Ende)
	int triFrontCtr=0;
	fullMesh.triList.AllocAbs			(pmTriList.GetNum());			fullMesh.triList.MarkNumAllocUsed();
	fullMesh.triMatIndexList.AllocAbs	(fullMesh.triList.GetNum());	fullMesh.triMatIndexList.MarkNumAllocUsed();
	for (i=0; i<pmTriList.GetNum(); i++)
	{
		if (triPermutation[i]<0)	{ 
			fullMesh.triList		[triFrontCtr  ]		= pmTriList[i];	
			fullMesh.triMatIndexList[triFrontCtr++]		= pmTriMatIndexList[i];	
		} else
		{ 
			fullMesh.triList		[triPermutation[i]]	= pmTriList[i];	
			fullMesh.triMatIndexList[triPermutation[i]]	= pmTriMatIndexList[i];	
		};
	};

	// wedge Indizes laut Permutation korrigieren
	for (i=0; i<pmTriList.GetNum(); i++)
	{
		for (int j=0; j<3; j++)
			fullMesh.triList[i].wedge[j] = fullMesh.wedgePermut[fullMesh.triList[i].wedge[j]];
	};

	// vertexUpdateList
	fullMesh.vertexUpdates.AllocAbs (vertexUpdateList.GetNum());	fullMesh.vertexUpdates.MarkNumAllocUsed();
	for (i=0; i<vertexUpdateList.GetNum(); i++)
	{
		int j = vertexUpdateList.GetNum()-1-i;
		fullMesh.vertexUpdates[j]				= vertexUpdateList[i];
		fullMesh.vertexUpdates[j].numNewWedge	= wedgeList.GetNum() - vertexUpdateList[i].numNewWedge;
	};

	//
	if (!(buildFlags & zPM_BUILD_FLAG_NO_POSNORMALS))
		CalcPosNormals(fullMesh);

	// (hier eigentlich nur noetig, wenn das Mesh nur 1 Material hat!)
	if (hasJustOneMaterial)
	{
		// TriPlane List 
		if (!(buildFlags & zPM_BUILD_FLAG_NO_TRIPLANES))
			CalcTriPlaneList (fullMesh, fullMesh);

		// Subdiv Data
		if ((buildFlags & zPM_BUILD_FLAG_CREATE_SUBDIV_DATA))
			CalcSubdivData  (fullMesh, fullMesh);
	};
	
	// ============================================================================================================

	// Lazy SubMeshes konstruieren & fuellen
	zCArray<zTLazyMesh> lazySubMeshList(fullMesh.matList.GetNum());		lazySubMeshList.MarkNumAllocUsed();

	if (!hasJustOneMaterial)
	{
		for (i=0; i<fullMesh.matList.GetNum(); i++)
		{
			lazySubMeshList[i].matList.Insert	(fullMesh.matList[i]);
			CreateLazySubMesh					(buildFlags, fullMesh, lazySubMeshList[i]);
		};
	};

	// ============================================================================================================

	// zCProgMeshProto fuellen

	// Speicherbedarf berechnen
	zDWORD dataSize		= fullMesh.CalcSizeBytesFullMeshPart ();
	if (!hasJustOneMaterial)
	{
		for (i=0; i<lazySubMeshList.GetNum(); i++)
			dataSize	+= lazySubMeshList[i].CalcSizeBytes();
	} else {
		dataSize		+= fullMesh.CalcSizeBytes();
	};

	// DataPool Speicher allokieren
	pmProto->dataSize	= dataSize;
	pmProto->dataPool	= zNEW(zBYTE) [dataSize];
	zBYTE* dataWalk		= pmProto->dataPool;

	// FullMesh Anteile kopieren
	SetAndCopyArrayAdapt (dataWalk, pmProto->posList		, fullMesh.posList);
	SetAndCopyArrayAdapt (dataWalk, pmProto->posNormalList	, fullMesh.posNormalList);

	// SubMeshes konstruieren & fuellen
	pmProto->numSubMeshes	= pmMatList.GetNum();
	pmProto->subMeshList	= zNEW(zCProgMeshProto::zCSubMesh) [pmProto->numSubMeshes];

	// nur ein Material im Mesh ? => shortCut: im FullMesh ist bereits alles enthalten
	if (!hasJustOneMaterial)
	{
		for (i=0; i<pmProto->numSubMeshes; i++)
		{
			zCProgMeshProto::zCSubMesh *subMesh = &(pmProto->subMeshList[i]);
			subMesh->material					= pmMatList[i];
			CopySubMeshData						(dataWalk, lazySubMeshList[i], subMesh);
		};
	} else 
	{
		zCProgMeshProto::zCSubMesh *subMesh		= &(pmProto->subMeshList[0]);
		subMesh->material						= pmMatList[0];
		CopySubMeshData							(dataWalk, fullMesh, subMesh);
	};
};


// =======================================================================================================================

void zCProgMeshBuilder::Clear ()
{
	int i;
	// erst die TriangleList, dann die VertList (Tris referenzieren im dtor die verts)
	for (i=0; i<triangleList.GetNum(); i++)	delete triangleList[i];
	triangleList.DeleteList		();
	for (i=0; i<vertList.GetNum(); i++)		delete vertList[i];
	vertList.DeleteList			();
	
	for (i=0; i<wedgeList.GetNum(); i++)	delete wedgeList[i];
	wedgeList.DeleteList		();
	wedgeCollapseList.DeleteList();
	vertexUpdateList.DeleteList	();

	triPermutation.DeleteList	();
	vertPermutation.DeleteList	();

	// for pmProto Construction
	pmProto						=0;
	pmTriList.DeleteList		();
	pmTriMatIndexList.DeleteList();
	pmPosList.DeleteList		();
	pmMatList.DeleteList		();
};

zBOOL zCProgMeshBuilder::BuildProgMeshProto (zCMesh *sourceMesh, zCProgMeshProto *destProgMesh, zCArray<int> *posListRemap, int buildFlags)
{
	zERR_ASSERT (sourceMesh);
	zERR_ASSERT (destProgMesh);
	zERR_MESSAGE					(3, zERR_BEGIN, "D: PM: Building ProgMesh... (" + ((buildFlags & zPM_BUILD_FLAG_NO_LOD) ? zSTRING("no LOD)") : zSTRING("LOD)")));
	int i;
	Clear							();
 
	// hohe FPU Precision sicherstellen
	const zDWORD fpuControlWord	= zfpuControler.GetCurrentControlWord();
	zfpuControler.SetPrecision_53();

	// Quell-Mesh ersteinmal saeubern
	if (!(buildFlags & zPM_BUILD_FLAG_DONT_REMOVE_DEGEN_POLYS))
		sourceMesh->RemoveDegeneratePolys();

	//
	if ((buildFlags & zPM_BUILD_FLAG_FORCE_SMOOTH_NORMALS))	sourceMesh->CalcVertexNormals	(zCMesh::zMSH_VERTNORMAL_SMOOTH); 
	else													sourceMesh->CalcVertexNormals	(zCMesh::zMSH_VERTNORMAL_MAT); 
	pmProto							= destProgMesh;
	pmProto->bbox3D					= sourceMesh->bbox3D;
	pmProto->obbox3D				= sourceMesh->obbox3D;

	AddVertices						(sourceMesh);				// put input data into our data structures
	AddTriangles					(sourceMesh);
	CreatePMTriPosList				();

	//
	triPermutation.AllocAbs			(triangleList.GetNum());
	triPermutation.MarkNumAllocUsed	();
	vertPermutation.AllocAbs		(vertList.GetNum());		// allocate space
	vertPermutation.MarkNumAllocUsed();
	if (posListRemap) {
		posListRemap->EmptyList			();
		posListRemap->AllocAbs			(vertList.GetNum());		// allocate space
		posListRemap->MarkNumAllocUsed	();
	};

	//
	if (buildFlags & zPM_BUILD_FLAG_NO_LOD)
	{
		// kein LOD errechnen
		for (i=0; i<vertList.GetNum(); i++) {
			vertPermutation	[i]	= i;
			if (posListRemap)
				(*posListRemap)	[i] = i;						// reorder, keep track of this vertex, i.e. the collapse ordering
		};
		for (i=0; i<triangleList.GetNum(); i++) {
			triPermutation	[i]	= i;
		};
	} else 
	{
		// LOD errechnen
		ComputeAllEdgeCollapseCosts		();						// cache all edge collapse costs
		vertexUpdateList.AllocAbs		(vertList.GetNum());
										
		//
		for (i=0; i<triPermutation.GetNum(); i++) triPermutation[i] = -1;

		// reduce the object down to nothing
		while (vertList.GetNum()>0) 
		{
			Vertex *mn						= MinimumCostEdge();					// get the next vertex to collapse
			vertPermutation[mn->id]			= vertList.GetNum()-1;					// reorder, keep track of this vertex, i.e. the collapse ordering
			if (posListRemap)
				(*posListRemap)[vertList.GetNum()-1]= mn->id;								// reorder, keep track of this vertex, i.e. the collapse ordering
			Collapse						(mn,mn->collapse);						// Collapse this edge
		}
		//	posListRemap = vertPermutation;
	};

	// The caller of this function should reorder their vertices
	// according to the returned "vertPermutation" / posListRemap.

	CreateFinalPMData (buildFlags);

	zERR_MESSAGE (5, 0, "D: PM: num verts: "		+zSTRING(sourceMesh->numVert));
	zERR_MESSAGE (5, 0, "D: PM: num tris: "			+zSTRING(sourceMesh->numPoly));
	zERR_MESSAGE (5, 0, "D: PM: num wedges: "		+zSTRING(wedgeList.GetNum()));
	zERR_MESSAGE (5, 0, "D: PM: num wedgeColl: "	+zSTRING(wedgeCollapseList.GetNum()));
	zERR_MESSAGE (5, 0, "D: PM: num vertUpdates: "	+zSTRING(vertexUpdateList.GetNum()));
//	zERR_MESSAGE (5, 0, "D: PM: num triPlanes: "	+zSTRING(destProgMesh->triPlaneList.GetNum()));

	zERR_MESSAGE (3, zERR_END, "");
	Clear();

	//
	zfpuControler.SetControlWord	(fpuControlWord);

	//
	destProgMesh->SetAlphaTestingEnabled(sourceMesh->GetAlphaTestingEnabled());

    // [Moos] 11.1.01: Mache den Hack wieder gut
	UnHack(sourceMesh);

	return TRUE;
};

/*
x	zBYTE						*dataPool;				// zCArrayAdapt memory pool
x	zCArray<zCMaterial*>		materialList;

	// mesh definition
x	zCArrayAdapt<zTPMTriangle>		triList;
x	zCArrayAdapt<zTPMWedge>		wedgeList;
x	zCArrayAdapt<zPOINT3>			posList;
	zCArrayAdapt<zVEC3>			colorList;				// prelit, indexed the same as wedgeList
	zCArrayAdapt<zTPlane>			triPlaneList;			// can be empty!
	
	// progressive mesh			
x	zCArrayAdapt<zPMINDEX>			wedgeMap;				// genausoviele Eintraege wie verts, vertex auf den kollabiert wird
	zCArrayAdapt<zTPMVertexUpdate>	vertexUpdates;			// numVert entries
	zCArrayAdapt<zPMINDEX>			triModifiedList;		// referenced by vertexUpdates, tris modified per collapse

<<<<<<<< < <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

*/

/*
TODO:

  zCProgMeshBuilder:
  - beim Kollapse werden manche Wedges der 'sides' nicht in die wedgeCollList eingetragen
  - evtl. besser TexUV Generierung, bei nicht matchendem wedge-Paar
  - aus der vertList eine sortierte priority queue machen (dann mit quicksort/mergesort)
  - Error-Metrik verbessern:
	- sind Quadrics nuetzlich ?
	- bei curvate/edgeLen mit der Tri Flaeche gewichten
	- Penalties vergeben fuer: sharp-edges (Hoppe), ..
	- evtl. nicht verbundene verts mergen?
	- bei Sven nach Params schauen

  - triPlane List
  - colorList
*/

