/******************************************************************************** 
 
     $Workfile:: zBVolume.cpp         $                $Date:: 27.01.01 19:42   $
     $Revision:: 22                   $             $Modtime:: 27.01.01 15:32   $
       $Author:: Moos                                                           $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created:

 * $Log: /current_work/ZenGin/_Dieter/zBVolume.cpp $
 * 
 * 22    27.01.01 19:42 Moos
 * 
 * 21    18.01.01 2:02 Hildebrandt
 * 
 * 20    20.12.00 20:21 Moos
 * 
 * 19    14.12.00 19:19 Moos
 * 
 * 18    12.12.00 22:41 Hildebrandt
 * 
 * 17    18.11.00 2:28 Hildebrandt
 * 
 * 16    17.11.00 19:29 Moos
 * 
 * 15    10.11.00 17:34 Hildebrandt
 * 
 * 14    8.11.00 16:38 Hildebrandt
 * 
 * 13    31.10.00 14:47 Moos
 * 
 * 12    31.10.00 14:00 Hildebrandt
 * 
 * 11    24.10.00 18:26 Hildebrandt
 * 
 * 10    22.09.00 15:57 Hoeller
 * 
 * 9     21.08.00 17:18 Hildebrandt
 * 
 * 8     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 7     21.07.00 14:28 Hildebrandt
 * 
 * 6     6.07.00 13:33 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 9     22.03.00 2:58 Hildebrandt
 * zenGin 088a
 * 
 * 8     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 6     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 5     18.11.99 22:18 Hildebrandt
 * 
 * 4     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 22 $ ($Modtime: 27.01.01 15:32 $)


#include <zCore.h>
#include <z3d.h> 
#include <zVisual.h> 
#include <zBVolume.h>
#include <zEigen.h>
#include <zFile3d.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

/*

TODO:
- OBB: Eberly hat seinen OBB-Code optimiert => einbauen !
- OBB: schnellere Trafos ala Rapid ?
- BB/BB Intersection-Test in Assembler ohne Branch testen (news: bounding.txt)
- Alle Sqrt Varianten profilen
- Schneller Poly/BBox3D Test: Arnfold2: File "aabbIntersection.cpp"

*/

// -----------------------------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////
//     BCylinder3D: Bounding Cylinder in 3D
///////////////////////////////////////////////////////////////////////////


zBOOL zTBCylinder3D::IsIntersecting	(const zTBCylinder3D& cylinder) const 
{
	// a) überlagern sich die Hoehen ? (Y-dim)
	if ((cylinder.center[VY]+cylinder.heightY) <  (center[VY]-heightY) ||
		(cylinder.center[VY]-cylinder.heightY) >  (center[VY]+heightY)) return FALSE;

	// b) überlagen sich die 2D-Kreise ? (X/Z-dim)
	zVALUE	dx= center[VX] - cylinder.center[VX];
	zVALUE	dz= center[VZ] - cylinder.center[VZ];
	zVALUE	r = radius + cylinder.radius;
	if ((dx*dx + dz*dz) > (r*r)) return FALSE;

	return TRUE;
};

void zTBCylinder3D::Draw (const zCOLOR& color) const 
{
	zTBBox3D	box;
	box.mins = box.maxs = center;
	box.mins[VY] = center[VY] - heightY;
	box.maxs[VY] = center[VY] + heightY;
	box.mins[VX] = center[VX] - radius;
	box.mins[VZ] = center[VZ] - radius;
	box.maxs[VX] = center[VX] + radius;
	box.maxs[VZ] = center[VZ] + radius;

	box.Draw (color);

	zTBSphere3D	sphere;
	sphere.center = center;
	sphere.radius = radius;
	sphere.Draw (color);
};

void zTBCylinder3D::SetByBBox3D (const zTBBox3D box) {
	center	= box.GetCenter();
	heightY = (box.maxs[VY] - box.mins[VY]) * zREAL(0.5F);

	zTBSphere3D sphere;
	sphere	= box.GetSphere3D ();
	radius	= sphere.radius;	
};

///////////////////////////////////////////////////////////////////////////
//     BSphere3D: Bounding Sphere in 3D
///////////////////////////////////////////////////////////////////////////
/*
zBOOL zTBSphere3D::IsIntersecting (const zPOINT3& rayOrg, const zVEC3& ray) const {
	// src: "interactive comp. graphics", burger/gillies, page 355
	// d IST UNIT !

	// schneller BBox-Test vorneweg... weil die SQRT unten so teuer ist..
	zPOINT3 rayEnd = rayOrg + ray;
	for (int i=0; i<3; i++) {
		if (((rayOrg[i]<center[i]-radius) && (rayEnd[i]<center[i]-radius)) || 
			((rayOrg[i]>center[i]+radius) && (rayEnd[i]>center[i]+radius))) return FALSE;
	};

	// FIXME: SQRT !!!!!!!
	zVALUE	len		= ray.Length();		if (len==0) return FALSE;
	zVEC3	d		= ray / len;
	zVALUE	alpha	= (center - rayOrg) * d; 
	if ((alpha<0) || (alpha>len)) return FALSE;								// Sphere behind ray
	zVEC3	v		= (rayOrg - center);
	return ((v * v - alpha*alpha)<=radius*radius);
};*/

zBOOL zTBSphere3D::IsIntersecting (const zPOINT3& rayOrg, const zVEC3& ray) const {
	// src: Dave Eberly, Distance-section
	// Weitere Quellen: news.collision.txt(Gino), Foley, burger/gillies, bourke
	// Kuerzeste Distanz Center/Line suchen, dann diese gegen den Radius checken.
	// Find t so that the point rayOrg+t*ray on the line segment (0 <= t <= 1)
	// is closest to point p.

	zVEC3	diff= center - rayOrg;
	zVALUE	t	= ray * diff;
	if (t>0) { 
        zVALUE mDotm = ray * ray;
        if (t<mDotm) {
			if (mDotm==0) return FALSE;			// hat Ray Laenge 0 ?
			diff	-= (t/mDotm)*ray; 
		} else
			diff	-= ray;			// t=1
    };
	return ((diff*diff)<=(radius*radius));
};

zBOOL zTBSphere3D::IsIntersecting (const zTBSphere3D& sphere) const 
{
	return (this->center+sphere.center).LengthApprox() <= (sphere.radius)+(this->radius);
};


int zTBSphere3D::ClassifyPlane (const zTPlane plane) const {
	zVALUE distCenter = center * plane.normal - plane.distance;

	if (distCenter < -radius)	return zCAM_CLIP_TRIV_OUT;
	if (distCenter >  radius)	return zCAM_CLIP_TRIV_IN;

//	zPOINT3 planeHit = center + (-plane.normal*distCenter);
//	zlineCache.Line3D (planeHit, center);

    return zCAM_CLIP_CROSSING;
};

void zTBSphere3D::Draw (const zCOLOR& color) const {
	zREAL	xc, yc, xup, yup, xright, yright;
	zREAL	xdim, ydim;
	zPOINT3 centerCS, upCS, rightCS;

	zCCamera *cam = zCCamera::activeCam;
	if (!cam) return;
	cam->Activate();

	centerCS= cam->camMatrix * center; if (centerCS[VZ]<=0) return; else cam->Project ( &centerCS, xc, yc);
	rightCS	= centerCS + zVEC3(1,0,0)*radius;
	upCS	= centerCS + zVEC3(0,1,0)*radius;
	cam->Project ( &rightCS	, xright, yright);
	cam->Project ( &upCS	, xup   , yup);

	xdim = (xright-xc);
	ydim = (yup   -yc);

	// draw ellipse, quick & dirty
	// src: "interactive comp. graphics", burger/gillies, page 96

	zREAL maxDim		= zMax (xdim, ydim);
	zREAL NUM_LINE_SEG  = maxDim * 0.5;
		  NUM_LINE_SEG	= zMax (NUM_LINE_SEG, 12.0F);
	zREAL cosPhi, sinPhi;
	zREAL x0, y0, x1, y1;
	zREAL A, B, C, D;
	zREAL inc;
	zREAL phi = 0;

	cosPhi = cos (phi);
	sinPhi = sin (phi);
	A	   = xdim * cosPhi; B = ydim * sinPhi;
	C	   = xdim * sinPhi; D = ydim * cosPhi;

	x0	   = A + xc;
	y0	   = C + yc;

	inc = Alg_Deg2Rad (360) / NUM_LINE_SEG;
	for (int j=0; j<NUM_LINE_SEG; j++) {
		phi			= phi + inc;
		cosPhi		= cos (phi);
		sinPhi		= sin (phi);
		x1			= xc + A * cosPhi - B * sinPhi;
		y1			= yc + C * cosPhi + D * sinPhi;
		zlineCache.Line (x0, y0, x1, y1, color);
		x0			= x1;
		y0			= y1;
	};

};

///////////////////////////////////////////////////////////////////////////
//     BBox3D: Axis Aligned Bounding-Box 3D
///////////////////////////////////////////////////////////////////////////


void zTBBox3D::SetMaximumBox() {
//	mins[0]=mins[1]=mins[2]= -30000000000.0F;
//	maxs[0]=maxs[1]=maxs[2]=  30000000000.0F;
	mins[0]=mins[1]=mins[2]= -3.40282e+038F; // zVALUE_MIN;
	maxs[0]=maxs[1]=maxs[2]=  3.40282e+038F;	// zVALUE_MAX;
//	mins[0]=mins[1]=mins[2]= -3.40282e+038F; // zVALUE_MIN;
//	maxs[0]=maxs[1]=maxs[2]=  3.40282e+038F;	// zVALUE_MAX;
//	mins[0]=mins[1]=mins[2]= MINMIN;
//	maxs[0]=maxs[1]=maxs[2]= MAXMAX;
};

zVALUE zTBBox3D::GetVolume () const {
	return (maxs.n[0]-mins.n[0])*(maxs.n[1]-mins.n[1])*(maxs.n[2]-mins.n[2]);
};

// aus this und bbox wird die groessere BBox berechnet
void zTBBox3D::CalcGreaterBBox3D (const zTBBox3D& bbox3D) {
	for (int j=0; j<3; j++) {
		mins.n[j] = zMin (bbox3D.mins.n[j], mins.n[j]);
		maxs.n[j] = zMax (bbox3D.maxs.n[j], maxs.n[j]);
	};
};

void zTBBox3D::ClipToBBox3D (const zTBBox3D& cullBox3D) {
	// clipped 'this' an der cullbox2d
	// 'schnittmengen-operation', Ergebnis ist undefiniert, wenn Boxen sich nicht schneiden !
	
	// portalBBox2D.ClipToBBox2D (cullBox2D);
	if (cullBox3D.mins[VX]>mins[VX]) mins[VX] = cullBox3D.mins[VX];
	if (cullBox3D.maxs[VX]<maxs[VX]) maxs[VX] = cullBox3D.maxs[VX];
	if (cullBox3D.mins[VY]>mins[VY]) mins[VY] = cullBox3D.mins[VY];
	if (cullBox3D.maxs[VY]<maxs[VY]) maxs[VY] = cullBox3D.maxs[VY];
	if (cullBox3D.mins[VZ]>mins[VZ]) mins[VZ] = cullBox3D.mins[VZ];
	if (cullBox3D.maxs[VZ]<maxs[VZ]) maxs[VZ] = cullBox3D.maxs[VZ];

//	assert (!(mins[VX]>maxs[VX]));
//	assert (!(mins[VY]>maxs[VY]));
//	if ((mins[VX]>maxs[VX]) || (mins[VY]>maxs[VY])) zerr.Report (zERR_WARN, 1000, "Illegal 2DBox !!!!!!!!");
};

zSTRING zTBBox3D::GetDescription () const {
	const int MAX = 8;
	return zSTRING(
		zSTRING(mins[0],MAX) + " " + zSTRING(mins[1],MAX) + " " + zSTRING(mins[2],MAX) + " " + 
		zSTRING(maxs[0],MAX) + " " + zSTRING(maxs[1],MAX) + " " + zSTRING(maxs[2],MAX));
};

void zTBBox3D::SetByDescription (zSTRING& desc) {
	mins[0] = desc.PickWord_Old (1,"").ToFloat();
	mins[1] = desc.PickWord_Old (2,"").ToFloat();
	mins[2] = desc.PickWord_Old (3,"").ToFloat();
	maxs[0] = desc.PickWord_Old (4,"").ToFloat();
	maxs[1] = desc.PickWord_Old (5,"").ToFloat();
	maxs[2] = desc.PickWord_Old (6,"").ToFloat();
};

/*
void zTBBox3D::Transform (const zMATRIX4& trafo, zTBBox3D& bbox3D) const {
	// FIXME: geht das nicht effizienter ??
	// => siehe Diplomarbeit von ... Gabriel Zachmann., oder Zhuang, oder Gems, oder so..
	zPOINT3 point[8];
	point[0] = trafo * zPOINT3(mins.n[VX], mins.n[VY], mins.n[VZ]);
	point[1] = trafo * zPOINT3(maxs.n[VX], maxs.n[VY], maxs.n[VZ]);
	point[2] = trafo * zPOINT3(mins.n[VX], mins.n[VY], maxs.n[VZ]);
	point[3] = trafo * zPOINT3(mins.n[VX], maxs.n[VY], mins.n[VZ]);
	point[4] = trafo * zPOINT3(mins.n[VX], maxs.n[VY], maxs.n[VZ]);
	point[5] = trafo * zPOINT3(maxs.n[VX], mins.n[VY], mins.n[VZ]);
	point[6] = trafo * zPOINT3(maxs.n[VX], mins.n[VY], maxs.n[VZ]);
	point[7] = trafo * zPOINT3(maxs.n[VX], maxs.n[VY], mins.n[VZ]);
	bbox3D.Init();
	for (int i=0; i<8; i++) {
		for (int j=0; j<3; j++) {
			bbox3D.mins[j] = zMin (bbox3D.mins[j], point[i].n[j]);
			bbox3D.maxs[j] = zMax (bbox3D.maxs[j], point[i].n[j]);
		};
	};
};
*/


void zTBBox3D::Transform (const zMATRIX4& trafo, zTBBox3D& bbox3D) const 
{
	// src: Gems1, transBox.c ; Zachmann
	// Transforms a 3D axis-aligned box via a 3x3 matrix and a translation
	// vector and returns an axis-aligned box enclosing the result. 
    zREAL	a, b;

    // Copy box A into a min array and a max array for easy reference.
	// ACHTUNG: diese Kopie ist hier NOETIG, da der Aufrufer folgendes machen koennte:
	// zTBBox3D box; box.Transform (trafo, box);
	const zVEC3 Amin = mins;
	const zVEC3 Amax = maxs;

    // Take care of translation by beginning at T. 
	bbox3D.mins = bbox3D.maxs = trafo.GetTranslation();

    // Now find the extreme points by considering the product of the 
    // min and max with each component of M.  
    for( int i = 0; i < 3; i++ )
	{
		for( int j = 0; j < 3; j++ )
		{
			a = trafo[i][j] * Amin[j];
			b = trafo[i][j] * Amax[j];
			if( a < b ) { 
				bbox3D.mins[i] += a; 
				bbox3D.maxs[i] += b;
			} else { 
				bbox3D.mins[i] += b; 
				bbox3D.maxs[i] += a;
			}
		}
	};
};



/* ----------------------------------------------------------------------
	
	zTBBox::Untransform

	31.10.2000	[Moos]	
                erzeugt


   ---------------------------------------------------------------------- */

void zTBBox3D::UnTransform (const zMATRIX4& trafo, zTBBox3D& bbox3D) const {
    int i,j;

    zERR_ASSERT(trafo.IsUpper3x3Orthonormal());

    zMAT3    rot_transposed(trafo.GetRightVector(),trafo.GetUpVector(),trafo.GetAtVector());
    zMAT3    rot           (rot_transposed.Transpose());
    zVEC3    trans         (trafo.GetTranslation());

    // beim Berechnen der Transformierten einer bounding box zähnen nur die Absolutwerte in der Rotationsmatrix. Also:
    for (i=2;i>=0;i--)
        for (j=2;j>=0;j--)
            rot[i][j] = zAbs(rot[i][j]);

    zREAL det = ( rot.GetAtVector() ^ rot.GetRightVector() ) * rot.GetUpVector();
    if (zAbs(det) > .001){                                                       // nur, wenn Rot gut invertierbar ist, klappt das hier.
        if (zAbs(det) < .9 || zAbs(det) > 1.1)
            i =0;

        // die UnTransformation geht leichter in der Center/Extension Darstellung der box
        zVEC3    mycenter    = .5 * (mins + maxs);
        zVEC3    myextension = .5 * (maxs - mins);

        zMAT3 rotinv = rot.Inverse();

        zVEC3 untransformed_center    = trafo.Inverse() *  mycenter;    // das Zentrum der Bounding Box transformiert sich ganz normal; FIXME: das geht schneller, ohne Inverse...
        zVEC3 untransformed_extension = rotinv          *  myextension;
        
        // Trick: bei einer Transformation verändert sich die Ausdehnung der Bounding box so:
        //        new_ext = rot * ext;
        // wobei rot die Rotationsmatrix der Transformation ist, nachdem alle Einträge durch ihre absolutwerte ersetzt wurden.
        // also ist die inverse Transformation 
        // ext = rotinv * new_ext.
        

        // Mache die Daten gültig: (Kann eventuell entfernt werden)
        for (i=2;i>=0;i--)
            if (untransformed_extension[i] < 0)
                untransformed_extension[i] = 0;

        // gehe wieder auf die normale Darstellung zurück
        bbox3D.mins = untransformed_center - untransformed_extension;
        bbox3D.maxs = untransformed_center + untransformed_extension;
    }
    else
        Transform(trafo.Inverse(), bbox3D);           // Notfall. Das macht die box grösser.

#ifdef _DEBUG
    zTBBox3D test;
    bbox3D.Transform(trafo, test);
    zREAL scale = (test.mins.Length() + test.maxs.Length() + 1) * .1f;
    test.mins -= scale * zVEC3(.1f,.1f,.1f);
    test.maxs += scale * zVEC3(.1f,.1f,.1f);
    zERR_ASSERT(test.IsTrivIn(*this));
#endif
};


zBOOL zTBBox3D::IsIntersecting(const zPOINT3& rayOrigin, const zVEC3& rayDirection, zREAL& scaleMin, zREAL& scaleMax ) const
{
	// Allgemeiner Intersection-Test für Box mit Strahl/Gerade/Strecke
	// Verwendung z.Z. nur in zCRayTurbo::TraverseTree

	zREAL minScale[3], maxScale[3];
	zREAL absRayDirection[3];

	absRayDirection[0] = zAbs( rayDirection[0] );
	absRayDirection[1] = zAbs( rayDirection[1] );
	absRayDirection[2] = zAbs( rayDirection[2] );

	// Ermittle die Intersection-Bereiche fuer alle drei Koordinaten
	for( int i = 0; i<3; i++ )
	{
		// Falls Ray parallel zu einer der Koordinaten-Ebenen (i-te Koordinate ~0)
		if( absRayDirection[i]<zREAL(.0001F) )
		{
			// Teste ob der Ray-Ursprung auf gleicher 'Höhe' mit der Box liegt, falls nicht => Intersection unmöglich!
			if( mins[i]>rayOrigin[i] || rayOrigin[i]>maxs[i] )
				return FALSE;

			// Intersection-Intervall erhält maximale Ausdehnung
			minScale[i] = zREAL_MIN;
			maxScale[i] = zREAL_MAX;
		}
		else 
		{
			// Ermittle die Intersection-Grenzen
			// minScale[i] mit rayOrigin[i] + minScale[i]*rayDirection[i] = mins[i]
			// maxScale[i] mit rayOrigin[i] + maxScale[i]*rayDirection[i] = maxs[i]
			minScale[i] = ( mins[i] - rayOrigin[i] ) / rayDirection[i];
			maxScale[i] = ( maxs[i] - rayOrigin[i] ) / rayDirection[i];

			// Konstruiere Intersection-Intervall: Vertausche gegebenenfalls beide Werte
			if( maxScale[i]<minScale[i] )
			{
				zREAL t		= maxScale[i];
				maxScale[i] = minScale[i];
				minScale[i] = t;
			}
		}
	}

	// Ermitteln die Schnittmenge der Intersection-Bereiche für alle drei Koordinaten
	// mittels größtem Minimum und kleinstem Maximum als Intervall [scaleMin,scaleMax]
	scaleMin = zMax( minScale[0], zMax( minScale[1], minScale[2] ) );
	scaleMax = zMin( maxScale[0], zMin( maxScale[1], maxScale[2] ) );

	// Falls kein gültiges Intervall (also 'Leere Menge') => keine Intersection!
	if( scaleMin>scaleMax )
		return FALSE;

	// Ansonsten:
	// Erfolgreicher Intersectiontest!
	//
	// [scaleMin,scaleMax] gibt den Schnittbereich des Rays als Parameter-Intervall zurück;
	// tatsächlicher Schnittbereich: rayOrigin + t * rayDirection mit t aus dem Intervall

    return TRUE;
}


zBOOL zTBBox3D::IsIntersectingSweep(const zVEC3&    thisTransEnd,
                				    const zTBBox3D& box2,
				                    zREAL &time) const
{
    zREAL tenterleave[3][2];
    int  swap  [3];
    int i;

    time = 2;

    for (i = 2; i>=0; i--)
    {
    	if (thisTransEnd[i] == 0) // exception
	    {
	        if (box2.mins[i] > maxs[i] || box2.maxs[i] < mins[i])
	            return FALSE; // no collision possible
	        else
	        {
		        tenterleave[i][0] = -1;
		        tenterleave[i][1] = 2;
		        swap       [i]    = 0;
	        }
	    }
	    else
	    {   // when do min and max of different boxes meet?
	        tenterleave[i][0] = (box2.mins[i] - maxs[i]) / thisTransEnd[i];
	        tenterleave[i][1] = (box2.maxs[i] - mins[i]) / thisTransEnd[i];
	        swap       [i]    = (tenterleave[i][0] > tenterleave[i][1] ? 1 : 0);
	    }
    }
    

    zREAL maxenter=-1, minleave =2;
    #define TENTER(i) tenterleave[i][  swap[i]]
    #define TLEAVE(i) tenterleave[i][1-swap[i]]

    for (i = 2; i>=0; i--)
    {

    /*
	    zREAL enter = TENTER(i);
	    zREAL leave = TLEAVE(i);
	    // calculate new maxenter/minleafe. Since Branches are EVIL, this construct is faster than any if()-clause by a factor of about 8 even on older CPUs.
	    zREAL ediff = enter-maxenter;
	    zREAL ldiff = minleave-leave;
	
	    maxenter += (ediff + fabs(ediff))*.5F;
	    minleave -= (ldiff + fabs(ldiff))*.5F;

        // Na gut, das galt nur für meinen Pentium MMX. Auf dem Athlon ist tatsächlich das naive zMax schneller
        // TODO: test auf P2
    */

        maxenter = zMax ( maxenter, TENTER(i));
        minleave = zMin ( minleave, TLEAVE(i));

    	//maxenter = (maxenter > enter ? maxenter : enter);
    	//minleave = (minleave < leave ? minleave : leave);
    }

    if (maxenter < minleave && minleave >= 0 && maxenter <= 1)
    {
	    time = maxenter;

        if (time < 0)
            time = 0;

	    return TRUE;
    }
    
    return FALSE;
}


zBOOL zTBBox3D::IsIntersectingSweep (const zTBBox3D& thisTransEnd, const zTBBox3D& box2, const zTBBox3D& box2TransEnd, zREAL &time) const
{
    // erstmal nähern...
    return IsIntersectingSweep(thisTransEnd.mins-mins, box2, box2TransEnd.mins-box2.mins, time);
}


zBOOL zTBBox3D::IsTrivIn (const zTBBox3D& bbox3D) const {
	// 'bbox3d' wird relativ zu 'this' klassifiziert
	// ist bbox trivIn This
	return ((bbox3D.maxs.n[VX]<maxs.n[VX]) && (bbox3D.mins.n[VX]>mins.n[VX]) &&
			(bbox3D.maxs.n[VZ]<maxs.n[VZ]) && (bbox3D.mins.n[VZ]>mins.n[VZ]) &&
			(bbox3D.maxs.n[VY]<maxs.n[VY]) && (bbox3D.mins.n[VY]>mins.n[VY]) 
		   );
};

/*
inline bool intersect(const BBox& a, const BBox& b) {
  return abs(a.center[X] - b.center[X]) <= a.extent[X] + b.extent[X] &&
         abs(a.center[Y] - b.center[Y]) <= a.extent[Y] + b.extent[Y] &&
         abs(a.center[Z] - b.center[Z]) <= a.extent[Z] + b.extent[Z];
}
*/

zBOOL zTBBox3D::IsTrivInLine (const zPOINT3& point1, const zPOINT3& point2) const {
	return ((point1[VX]>=mins[VX]) && (point1[VX]<=maxs[VX]) &&
			(point1[VY]>=mins[VY]) && (point1[VY]<=maxs[VY]) &&
			(point1[VZ]>=mins[VZ]) && (point1[VZ]<=maxs[VZ]) &&
			(point2[VX]>=mins[VX]) && (point2[VX]<=maxs[VX]) &&
			(point2[VY]>=mins[VY]) && (point2[VY]<=maxs[VY]) &&
			(point2[VZ]>=mins[VZ]) && (point2[VZ]<=maxs[VZ]));
};


int zTBBox3D::Classify (const zTBBox3D& bbox3D) const {
	// 'bbox3d' wird relativ zu 'this' klassifiziert
	if ((bbox3D.maxs.n[VX]<mins.n[VX]) || (bbox3D.mins.n[VX]>maxs.n[VX]) ||
		(bbox3D.maxs.n[VZ]<mins.n[VZ]) || (bbox3D.mins.n[VZ]>maxs.n[VZ]) ||
		(bbox3D.maxs.n[VY]<mins.n[VY]) || (bbox3D.mins.n[VY]>maxs.n[VY])) return zCAM_CLIP_TRIV_OUT;

    if ((bbox3D.maxs.n[VX]<maxs.n[VX]) && (bbox3D.mins.n[VX]>mins.n[VX]) &&
		(bbox3D.maxs.n[VZ]<maxs.n[VZ]) && (bbox3D.mins.n[VZ]>mins.n[VZ]) &&
		(bbox3D.maxs.n[VY]<maxs.n[VY]) && (bbox3D.mins.n[VY]>mins.n[VY])) return zCAM_CLIP_TRIV_IN;

	return zCAM_CLIP_CROSSING;
};

zPOINT3 zTBBox3D::GetNearestPoint (const zTPlane* const plane) const {
	// Hier werden einfach die Entfernungen aller 8 Ecken der BBox zur Plane berrechnet.
	// FIXME: genauere Tests sind moeglich (Edge, Face,..) => Eberlys MinTriangleTriangle Func !
	// FIXME: den BBox/Frustum-Code verwenden !!
	zVALUE	dist;
	zVALUE	bestDist=zVALUE_MAX;
	zPOINT3	bestPoint, point;
	const zVEC3&  normal		= plane->normal;
	const zVALUE& planeDist		= plane->distance;

	point	= zPOINT3(mins.n[VX], mins.n[VX], mins.n[VX]);
	dist	= zAbs(point * normal - planeDist); if (dist<bestDist) { bestDist=dist; bestPoint=point; };

	point	= zPOINT3(maxs.n[VX], maxs.n[VY], maxs.n[VZ]);
	dist	= zAbs(point * normal - planeDist); if (dist<bestDist) { bestDist=dist; bestPoint=point; };

	point	= zPOINT3(mins.n[VX], mins.n[VY], maxs.n[VZ]);
	dist	= zAbs(point * normal - planeDist); if (dist<bestDist) { bestDist=dist; bestPoint=point; };

	point	= zPOINT3(mins.n[VX], maxs.n[VY], mins.n[VZ]);
	dist	= zAbs(point * normal - planeDist); if (dist<bestDist) { bestDist=dist; bestPoint=point; };

	point	= zPOINT3(mins.n[VX], maxs.n[VY], maxs.n[VZ]);
	dist	= zAbs(point * normal - planeDist); if (dist<bestDist) { bestDist=dist; bestPoint=point; };

	point	= zPOINT3(maxs.n[VX], mins.n[VY], mins.n[VZ]);
	dist	= zAbs(point * normal - planeDist); if (dist<bestDist) { bestDist=dist; bestPoint=point; };

	point	= zPOINT3(maxs.n[VX], mins.n[VY], maxs.n[VZ]);
	dist	= zAbs(point * normal - planeDist); if (dist<bestDist) { bestDist=dist; bestPoint=point; };

	point	= zPOINT3(maxs.n[VX], maxs.n[VY], mins.n[VZ]);
	dist	= zAbs(point * normal - planeDist); if (dist<bestDist) { bestDist=dist; bestPoint=point; };

	return bestPoint;
};

void zTBBox3D::Scale (const zREAL scaleFac) {
	for (int i=0; i<3; i++) {
		zREAL center= (maxs[i]+mins[i]) * zREAL(0.5F);
		zREAL offs	= ((maxs[i] - mins[i]) * scaleFac) * zREAL(0.5F);
		maxs[i]		= center+offs;
		mins[i]		= center-offs;
	};
};

void zTBBox3D::Scale (const zVEC3& scale) {
	for (int i=0; i<3; i++) {
		zREAL center= (maxs[i]+mins[i]) * zREAL(0.5F);
		zREAL offs	= ((maxs[i] - mins[i]) * scale[i]) * zREAL(0.5F);
		maxs[i]		= center+offs;
		mins[i]		= center-offs;
	};
};
/*
zVALUE zTBBox3D::GetMaxExtent () const {
	zVALUE max = -1;
	for (int i=0; i<3; i++) {
		zVALUE dim = maxs[i] - mins[i];
		if (dim>max) max = dim;
	};
	return max / 2;
};
*/
zVALUE zTBBox3D::GetMinExtent () const {
	zVALUE min = zVALUE_MAX;
	for (int i=0; i<3; i++) {
		zVALUE dim = maxs[i] - mins[i];
		if (dim<min) min = dim; 
	};
	return min / 2;
};

zTBSphere3D zTBBox3D::GetSphere3D () const {
	zTBSphere3D sphere;
	sphere.center = GetCenter();
	// FIXME: Fuer Collision-Detection (Cylinder Model/Model) muss das hier 'MIN' sein
	//        Allerdings fuer die Vob-ScreenBBox2D (=>outdoor portal-Engine) muss es 'MAX'
	//        sein, oder ?
	sphere.radius = GetMinExtent();					
//	sphere.radius = GetMaxExtent();
//	sphere.radius = GetMaxExtent();
//	sphere.radius = GetMaxExtent() * sqrt(2);
	return sphere;
}; 

/*
Ray/Box Slabs-Technik
aus: http://www.education.siggraph.org/materials/hypgraph/raytrace/rtinter3.htm

Ray - Box Intersection

We can use a box both as an object and a bounding volume. Kay and Kayjia developed a method based on "slabs" where a slab is the space
between two parallel planes. So the intersection of a set of slabs defines a bounding volume or a box.
The method looks at the intersection of each pair of slabs by the ray. It finds tfar and tnear for each pair of slabs. If the overall largest tnear value
i.e,. intersection with the near slab, is greater than the smallest tfar value (intersection with far slab) then the ray misses the box, else it hits the
box. We can use as the simplest bounding volume the intersection of the sets of two parallel planes where each set has normals along the X, Y,
or Z axes.
We will define the box by two coordinates: the box's minimum extent Bl = [ Xl Yl Zl ] and the box's maximum extent Bh = [ Xh Yh Zh ]
The Ray is defined as before in terms of Ro, Rd Then the algorithm is as follows:

set Tnear = - infinity, Tfar = infinity

For each pair of planes P associated with X, Y, and Z do:
(example using X planes)
if direction Xd = 0 then the ray is parallel to the X planes, so
if origin Xo is not between the slabs ( Xo < Xl or Xo > Xh) then return false
else, if the ray is not parallel to the plane then
begin
compute the intersection distance of the planes
T1 = (Xl - Xo) / Xd
T2 = (Xh - Xo) / Xd
If T1 > T2 swap (T1, T2) // since T1 intersection with near plane 
If T1 > Tnear set Tnear =T1 // want largest Tnear 
If T2 < Tfar set Tfar="T2" // want smallest Tfar 
If Tnear > Tfar box is missed so return false
If Tfar < 0 box is behind ray return false end


end of for loop If Box survived all above tests, return true with intersection point Tnear and exit point Tfar.

Example: Figure (left) 


set  tnear =  -infinity,   tfar = infinity
For  X planes
Ray not  parallel
Compute intersection T1 <- Tx1, T2 <- Tx2  

T2 > T1 so no swap
T1 > Tnear so Tnear <-- T1 (Tx1)
T2 < T far  so Tfar <-- Tx2
Tnear < Tfar and  Tfar > 0   so do Y planes
        
Y planes
Ray not  parallel
Compute intersection  T1 <-- Ty1,  T2 <-- Ty2
T1 < Ty2  so  no  swap
T1  not > Tnear so no change
T2 < Tfar, so Tfar = T2(Ty2)
Tnear > Tfar -> therefore return false and done
                                                                         
Second example from figure (right)

     set tnear =  -infinity,   tfar = infinity

        X planes
        not parallel
         t1 <- tx1, t2 <- tx2 
        If t1 < t2 so no swap;       
        t1 > tnear so tnear <- t1 ;
        t2 < tfar so tfar <- t2;
        If tnear < tfar   so OK;
        If tfar <  0   so OK;

        now do Y planes
        not parallel

        t1 <- ty1,  t2 <- ty2

         t1 < t2 so no swap;
         t1 < tnear so no change;
         t2 < tfar  so tfar <- t2;
         tnear > tfar  ? no
         tfar < 0      ?  no 

   Thus, return true with intersection point = tnear = tx1;

*/

/*
zBOOL zTBBox3D::TraceRay (const zPOINT3& rayOrg, const zVEC3& ray, zPOINT3& inters) const 
{
	zVEC3 theMin, theMax;
	
	for(int i=0; i<3; i++)
	{
		if( zAbs(ray[i]) < zREAL(.0001F) )		// .01F
		{
			if( mins[i] < rayOrg[i] && rayOrg[i] < maxs[i] ) {
				theMax[i] = zREAL_MAX;
				theMin[i] = zREAL_MIN;
//				theMax[i] = zREAL( 1e+20);
//				theMin[i] = zREAL(-1e+20);
			} else 
				return FALSE;
		} else {
			zREAL rayInv= zREAL(1.0F) / ray[i];
			zREAL t1	= ( mins[i] - rayOrg[i] ) * rayInv;
			zREAL t2	= ( maxs[i] - rayOrg[i] ) * rayInv;

			
			if (t1<t2)  {
				theMin[i] = t1;
				theMax[i] = t2;
			} else {
				theMin[i] = t2;
				theMax[i] = t1;
			}
			if( theMax[i] < 0			) return FALSE;
		}
	}
	
	zREAL tmin	= zMax (theMin[0], zMax (theMin[1], theMin[2]) );
	zREAL tmax	= zMin (theMax[0], zMin (theMax[1], theMax[2]) );
	
	if ( tmax<tmin)	return FALSE;
	
	zREAL t;
	if ( tmin<0	)	t=tmax;
	else 			t=tmin;
	
	inters = rayOrg + t*ray;
	return TRUE;
}
*/

zBOOL zTBBox3D::TraceRay (const zPOINT3& rayOrg, const zVEC3& ray, zPOINT3& inters) const 
{
	// 't' ist normalisiert (0..1) !
	// FIXME: falls derselbe Ray _sehr_ oft getestet werden soll, kann (1/ray) einmal pro Ray berechnet werden !

	zREAL tmin = zREAL_MIN;
	zREAL tmax = zREAL_MAX;
	
	int i=0;
	do
	{
		// Ray parallel ?
		if( zAbs(ray[i]) < zREAL(.0001F) )		// .01F
		{
			// Ray nicht im Slab ?
			if( mins[i] > rayOrg[i] || rayOrg[i] > maxs[i] )	return FALSE;
		} else 
		{
			zREAL rayInv= zREAL(1.0F) / ray[i];
			zREAL t1	= ( mins[i] - rayOrg[i] ) * rayInv;
			zREAL t2	= ( maxs[i] - rayOrg[i] ) * rayInv;

			if (t1<t2)  {
				if (t1 > tmin)	tmin = t1;
				if (t2 < tmax)	tmax = t2;
			} else {
				if (t2 > tmin)	tmin = t2;
				if (t1 < tmax)	tmax = t1;
			}
			if (tmin>tmax)	return FALSE;
			if (tmax<0)		return FALSE;
		}
		i++;
	} while (i<3);
	
	zREAL t;
	if ( tmin<0	)	t = tmax;
	else 			t = tmin;
	
	if (t>1) return FALSE;

	inters = rayOrg + t*ray;
	return TRUE;
}


/*
zBOOL zTBBox3D::TraceRay (const zPOINT3& rayOrg, const zVEC3& ray, zPOINT3& inters) const {

	// FIXME: Gems1, RayBox.c sieht schneller aus..

	// FIXME: evtl. nochmals checken, ob der Algo aus PapersMisc/intersec.PS schneller ist!!
	//        (slabs => wird er wohl..)

	// Achtung: Es gibt auch keinen 'hit', wenn der Ray komplett innerhalb der Box liegt !

	const zPOINT3& rayEnd = rayOrg + ray;
	int i; 

	// 1a) Check, ob alle Verts auf einer der 6 Seite der BBox liegen
	//     Early rejection
	//     => es koennen aber trotzdem noch Polys durchkommen, die zwar nicht die BBox 
	//        schneiden, aber ausserhalb 2 Planes der BBox schneiden

	for (i=0; i<3; i++) {
		if (rayOrg[i]>=mins[i]) goto testFailed; 
		if (rayEnd[i]>=mins[i]) goto testFailed; 
		return FALSE;
testFailed:;
		if (rayOrg[i]<=maxs[i]) goto testFailed2; 
		if (rayEnd[i]<=maxs[i]) goto testFailed2; 
		return FALSE;
testFailed2:;
	};

	// An dieser Stelle MUSS sichergestellt sein:
	// - KEINE Verts befinden sich IN der BBox !
	// - die polyPlane SCHNEIDET die BBox

	// 2) Check, ob eine Poly-Kante eine der 6 Seite der BBox durchdringt
	//    FIXME: noch optimierbar ??
	int dim2, dim3;
	dim2 = 0;
	dim3 = 1;
	for (i=0; i<3; i++) {
		zVALUE	dn, alpha, intersDIM2, intersDIM3;
		dim2++; if (dim2==3) dim2=0;
		dim3++; if (dim3==3) dim3=0;

		zVALUE planeNormal, planeDistance;
		// Mins
		planeNormal		=-1;
		planeDistance	=-mins[i];
		for (int k=0; k<2; k++) {
			dn = ray[i]*planeNormal;
			if (dn!=0) {							// parallel ?
				alpha	= (planeDistance - (planeNormal * rayOrg[i])) / dn;
				if ((alpha>=0) && (alpha<=1)) {
					// Plane auch im Bereich der BBox getroffen ?
					intersDIM2		= rayOrg[dim2] + alpha*ray[dim2]; 
					if ((intersDIM2>= mins[dim2]) && (intersDIM2<= maxs[dim2])) {
						intersDIM3	= rayOrg[dim3] + alpha*ray[dim3];
						if ((intersDIM3>=mins[dim3]) && (intersDIM3<=maxs[dim3])) {
							inters[i]	= planeDistance * planeNormal;
							inters[dim2]= intersDIM2;
							inters[dim3]= intersDIM3;
							return TRUE;
						};
					};
				};
			};
			// Maxs
			planeNormal		=+1; 
			planeDistance	= maxs[i];
		};
	};
	return FALSE;
};
*/

void zTBBox3D::Draw (const zCOLOR &color) const {
	// projecting 8 edge-vertices from bbox3D
//	int xscr[8], yscr[8];
	zPOINT3 point;
	zCCamera *cam = zCCamera::activeCam;
	if (!cam) return;

	zPOINT3 point0 = cam->camMatrix * zPOINT3(mins.n[VX], mins.n[VY], mins.n[VZ]);
	zPOINT3 point1 = cam->camMatrix * zPOINT3(maxs.n[VX], maxs.n[VY], maxs.n[VZ]);
	zPOINT3 point2 = cam->camMatrix * zPOINT3(mins.n[VX], mins.n[VY], maxs.n[VZ]);
	zPOINT3 point3 = cam->camMatrix * zPOINT3(mins.n[VX], maxs.n[VY], mins.n[VZ]);
	zPOINT3 point4 = cam->camMatrix * zPOINT3(mins.n[VX], maxs.n[VY], maxs.n[VZ]);
	zPOINT3 point5 = cam->camMatrix * zPOINT3(maxs.n[VX], mins.n[VY], mins.n[VZ]);
	zPOINT3 point6 = cam->camMatrix * zPOINT3(maxs.n[VX], mins.n[VY], maxs.n[VZ]);
	zPOINT3 point7 = cam->camMatrix * zPOINT3(maxs.n[VX], maxs.n[VY], mins.n[VZ]);
	// 0: 000
	zlineCache.LineCS3D (point0, point2, color);
	zlineCache.LineCS3D (point0, point3, color);
	zlineCache.LineCS3D (point0, point5, color);
	// 1: 111
	zlineCache.LineCS3D (point1, point4, color);
	zlineCache.LineCS3D (point1, point6, color);
	zlineCache.LineCS3D (point1, point7, color);
	// 2: 001
	zlineCache.LineCS3D (point2, point4, color);
	zlineCache.LineCS3D (point2, point6, color);
	// 3: 010
	zlineCache.LineCS3D (point3, point4, color);
	zlineCache.LineCS3D (point3, point7, color);
	// 4: 011
	// 5: 100
	zlineCache.LineCS3D (point5, point6, color);
	zlineCache.LineCS3D (point5, point7, color);
	// 6: 101
	// 7: 110

/*	point = cam->camMatrix * zPOINT3(mins.n[VX], mins.n[VY], mins.n[VZ]); if (point.n[VZ]<=0) return; else cam->Project ( &point, xscr[0], yscr[0]);
	point = cam->camMatrix * zPOINT3(maxs.n[VX], maxs.n[VY], maxs.n[VZ]); if (point.n[VZ]<=0) return; else cam->Project ( &point, xscr[1], yscr[1]);
	point = cam->camMatrix * zPOINT3(mins.n[VX], mins.n[VY], maxs.n[VZ]); if (point.n[VZ]<=0) return; else cam->Project ( &point, xscr[2], yscr[2]);
	point = cam->camMatrix * zPOINT3(mins.n[VX], maxs.n[VY], mins.n[VZ]); if (point.n[VZ]<=0) return; else cam->Project ( &point, xscr[3], yscr[3]);
	point = cam->camMatrix * zPOINT3(mins.n[VX], maxs.n[VY], maxs.n[VZ]); if (point.n[VZ]<=0) return; else cam->Project ( &point, xscr[4], yscr[4]);
	point = cam->camMatrix * zPOINT3(maxs.n[VX], mins.n[VY], mins.n[VZ]); if (point.n[VZ]<=0) return; else cam->Project ( &point, xscr[5], yscr[5]);
	point = cam->camMatrix * zPOINT3(maxs.n[VX], mins.n[VY], maxs.n[VZ]); if (point.n[VZ]<=0) return; else cam->Project ( &point, xscr[6], yscr[6]);
	point = cam->camMatrix * zPOINT3(maxs.n[VX], maxs.n[VY], mins.n[VZ]); if (point.n[VZ]<=0) return; else cam->Project ( &point, xscr[7], yscr[7]);
	// 0: 000
	zlineCache.Line ((xscr[0]),(yscr[0]), (xscr[2]),(yscr[2]), color);
	zlineCache.Line ((xscr[0]),(yscr[0]), (xscr[3]),(yscr[3]), color);
	zlineCache.Line ((xscr[0]),(yscr[0]), (xscr[5]),(yscr[5]), color);
	// 1: 111
	zlineCache.Line ((xscr[1]),(yscr[1]), (xscr[4]),(yscr[4]), color);
	zlineCache.Line ((xscr[1]),(yscr[1]), (xscr[6]),(yscr[6]), color);
	zlineCache.Line ((xscr[1]),(yscr[1]), (xscr[7]),(yscr[7]), color);
	// 2: 001
	zlineCache.Line ((xscr[2]),(yscr[2]), (xscr[4]),(yscr[4]), color);
	zlineCache.Line ((xscr[2]),(yscr[2]), (xscr[6]),(yscr[6]), color);
	// 3: 010
	zlineCache.Line ((xscr[3]),(yscr[3]), (xscr[4]),(yscr[4]), color);
	zlineCache.Line ((xscr[3]),(yscr[3]), (xscr[7]),(yscr[7]), color);
	// 4: 011
	// 5: 100
	zlineCache.Line ((xscr[5]),(yscr[5]), (xscr[6]),(yscr[6]), color);
	zlineCache.Line ((xscr[5]),(yscr[5]), (xscr[7]),(yscr[7]), color);
	// 6: 101
	// 7: 110*/
/*	if (targetDtpItem==0) return;
	for (int i=0; i<8; i++) {
		for (int j=0; j<8; j++) {
			if (i==j) continue;
			targetDtpItem->Line (Gfx_anx(xscr[i]),Gfx_any(yscr[i]), Gfx_anx(xscr[j]),Gfx_any(yscr[j]), GFX_BLUE);
		};
	};
*/
};
 
void zTBBox3D::GetCornerPoints (zPOINT3* point) const {
	point[0] = zPOINT3(mins.n[VX], mins.n[VY], mins.n[VZ]);
	point[1] = zPOINT3(maxs.n[VX], maxs.n[VY], maxs.n[VZ]);
	point[2] = zPOINT3(mins.n[VX], mins.n[VY], maxs.n[VZ]);
	point[3] = zPOINT3(mins.n[VX], maxs.n[VY], mins.n[VZ]);
	point[4] = zPOINT3(mins.n[VX], maxs.n[VY], maxs.n[VZ]);
	point[5] = zPOINT3(maxs.n[VX], mins.n[VY], mins.n[VZ]);
	point[6] = zPOINT3(maxs.n[VX], mins.n[VY], maxs.n[VZ]);
	point[7] = zPOINT3(maxs.n[VX], maxs.n[VY], mins.n[VZ]);
};

zREAL zTBBox3D::GetScreenSize () const {
	// projecting 8 edge-vertices from bbox3D
//	int xscr[8], yscr[8];
	zCCamera *cam = zCCamera::activeCam;
	if (!cam) return zREAL_MAX;

	zVEC3		point[8];
	zREAL		xscr, yscr;
	zTBBox3D	boxCS; 
	Transform				(cam->camMatrix, boxCS);
	boxCS.GetCornerPoints	(point);

/*	point[0] = cam->camMatrix * zPOINT3(mins.n[VX], mins.n[VY], mins.n[VZ]);
	point[1] = cam->camMatrix * zPOINT3(maxs.n[VX], maxs.n[VY], maxs.n[VZ]);
	point[2] = cam->camMatrix * zPOINT3(mins.n[VX], mins.n[VY], maxs.n[VZ]);
	point[3] = cam->camMatrix * zPOINT3(mins.n[VX], maxs.n[VY], mins.n[VZ]);
	point[4] = cam->camMatrix * zPOINT3(mins.n[VX], maxs.n[VY], maxs.n[VZ]);
	point[5] = cam->camMatrix * zPOINT3(maxs.n[VX], mins.n[VY], mins.n[VZ]); 
	point[6] = cam->camMatrix * zPOINT3(maxs.n[VX], mins.n[VY], maxs.n[VZ]);
	point[7] = cam->camMatrix * zPOINT3(maxs.n[VX], maxs.n[VY], mins.n[VZ]);*/
	zREAL xmins = 999999;
	zREAL xmaxs =-999999;
	zREAL ymins = 999999;
	zREAL ymaxs =-999999;
	for (int i=0; i<8; i++) {
		if (point[i].n[VZ]<=0) return zREAL_MAX;
		cam->Project (&point[i], xscr, yscr);
		if (xscr>xmaxs)	xmaxs = xscr;
		if (xscr<xmins)	xmins = xscr;
		if (yscr>ymaxs)	ymaxs = yscr;
		if (yscr<ymins)	ymins = yscr;
	};
	return (xmaxs-xmins)*(ymaxs-ymins);
//	return zREAL(0.00001F)*(xmaxs-xmins)*(ymaxs-ymins);
};

//zTPlaneClass	ClassifyToPlane		(const zTPlane& plane);	
//	zTPlaneClass	ClassifyToPlane		(const zTPlane& plane, int signBits);	
zTPlaneClass zTBBox3D::ClassifyToPlane (const zTPlane& plane) const {	

	const zPOINT3* const minMax[ 2 ] = { &(mins), &(maxs) };
	int	ix = ( plane.normal[VX] >= 0 ) ?  1 : 0;
	int	iy = ( plane.normal[VY] >= 0 ) ?  1 : 0;
	int	iz = ( plane.normal[VZ] >= 0 ) ?  1 : 0;
	
	zVALUE decision;
	decision  = minMax[ ix ]->n[VX] * plane.normal.n[VX];	// dot
	decision += minMax[ iy ]->n[VY] * plane.normal.n[VY];
	decision += minMax[ iz ]->n[VZ] * plane.normal.n[VZ];
	
	if( decision < plane.distance) {
		// BBox ist komplett links(out) der Plane => nur einen Sohn pruefen
		return zPLANE_BEHIND;
	};
	
	decision  = minMax[ 1 - ix ]->n[VX] * plane.normal.n[VX];
	decision += minMax[ 1 - iy ]->n[VY] * plane.normal.n[VY];
	decision += minMax[ 1 - iz ]->n[VZ] * plane.normal.n[VZ];
	if( decision < plane.distance) {
		// BBox wird durch die Plane gesplittet => beide Soehne pruefen
		return zPLANE_SPANNING;
	};
	// BBox ist komplett rechts(in) der Plane => nur einen Sohn pruefen
	return zPLANE_INFRONT;
};

zTPlaneClass zTBBox3D::ClassifyToPlane (const zTPlane& plane, const int signbits) const {
	// 0=-, 1=+
	zREAL dist;
	switch (signbits) {
	case 0:	// 000, ZYX
		dist = mins.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_BEHIND;
		dist = maxs.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_SPANNING;
		return zPLANE_INFRONT;
		break;
	case 1:	// 001
		dist = maxs.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_BEHIND;
		dist = mins.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_SPANNING;
		return zPLANE_INFRONT;
		break;
	case 2:	// 010
		dist = mins.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_BEHIND;
		dist = maxs.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_SPANNING;
		return zPLANE_INFRONT;
		break;
	case 3:	// 011
		dist = maxs.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_BEHIND;
		dist = mins.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_SPANNING;
		return zPLANE_INFRONT;
		break;
	case 4:	// 100
		dist = mins.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_BEHIND;
		dist = maxs.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_SPANNING;
		return zPLANE_INFRONT;
		break;
	case 5:	// 101
		dist = maxs.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_BEHIND;
		dist = mins.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_SPANNING;
		return zPLANE_INFRONT;
		break;
	case 6:	// 110
		dist = mins.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_BEHIND;
		dist = maxs.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_SPANNING;
		return zPLANE_INFRONT;
		break;
	case 7:	// 111
		dist = maxs.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_BEHIND;
		dist = mins.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zPLANE_SPANNING;
		break;
	};
	return zPLANE_INFRONT;
};

int zTBBox3D::ClassifyToPlaneSides (const zTPlane &plane) const {
	zREAL	dist;
	zVEC3	corners[2];

	for (int i=0 ; i<3 ; i++) {
		if (plane.normal[i] < 0) {
			corners[0][i] = mins[i];
			corners[1][i] = maxs[i];
		} else {
			corners[1][i] = mins[i];
			corners[0][i] = maxs[i];
		}
	}
	dist = plane.normal * corners[0] - plane.distance;	if (dist<0) { return 2; } // back
	dist = plane.normal * corners[1] - plane.distance;	if (dist<0) { return 3; } // split
	return 1;	// front
/*		dist1 = node->plane.normal * corners[0] - node->plane.distance;
	dist2 = node->plane.normal * corners[1] - node->plane.distance;
	sides = 0;
	if (dist1 >= 0)	sides = 1;		// front
	if (dist2 < 0)	sides |= 2;*/
//			if (dist1 >= 0)	if (node->front) node->front->AddVobToLeafs (vob);
//			if (dist2 < 0)	if (node->back ) node->back ->AddVobToLeafs (vob);
};

int zTBBox3D::ClassifyToPlaneSides (const zTPlane& plane, const int signbits) const {
	// 0=-, 1=+
	zREAL dist;
	switch (signbits) {
	case 0:	// 000, ZYX
		dist = mins.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 2;
		dist = maxs.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 3;
		return 1;
		break;
	case 1:	// 001
		dist = maxs.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 2;
		dist = mins.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 3;
		return 1;
		break;
	case 2:	// 010
		dist = mins.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 2;
		dist = maxs.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 3;
		return 1;
		break;
	case 3:	// 011
		dist = maxs.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 2;
		dist = mins.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 3;
		return 1;
		break;
	case 4:	// 100
		dist = mins.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 2;
		dist = maxs.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 3;
		return 1;
		break;
	case 5:	// 101
		dist = maxs.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 2;
		dist = mins.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 3;
		return 1;
		break;
	case 6:	// 110
		dist = mins.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 2;
		dist = maxs.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 3;
		return 1;
		break;
	case 7:	// 111
		dist = maxs.n[VX]*plane.normal.n[VX] + maxs.n[VY]*plane.normal.n[VY] + maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 2;
		dist = mins.n[VX]*plane.normal.n[VX] + mins.n[VY]*plane.normal.n[VY] + mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return 3;
	};
	return 1;
};

/*

  Quelle: Sin-Source 101
// this is the slow, general version
int BoxOnPlaneSide2 (vec3_t emins, vec3_t emaxs, struct cplane_s *p)
{
	int		i;
	float	dist1, dist2;
	int		sides;
	vec3_t	corners[2];

	for (i=0 ; i<3 ; i++)
	{
		if (p->normal[i] < 0)
		{
			corners[0][i] = emins[i];
			corners[1][i] = emaxs[i];
		}
		else
		{
			corners[1][i] = emins[i];
			corners[0][i] = emaxs[i];
		}
	}
	dist1 = DotProduct (p->normal, corners[0]) - p->dist;
	dist2 = DotProduct (p->normal, corners[1]) - p->dist;
	sides = 0;
	if (dist1 >= 0)
		sides = 1;
	if (dist2 < 0)
		sides |= 2;

	return sides;
}


//==================
//BoxOnPlaneSide
//
//Returns 1, 2, or 1 + 2
//==================

#if !id386 || defined __linux__ 
int BoxOnPlaneSide (vec3_t emins, vec3_t emaxs, struct cplane_s *p)
{
	float	dist1, dist2;
	int		sides;

// fast axial cases
	if (p->type < 3)
	{
		if (p->dist <= emins[p->type])
			return 1;
		if (p->dist >= emaxs[p->type])
			return 2;
		return 3;
	}
	
// general case
	switch (p->signbits)
	{
	case 0:
		dist1 = p->normal[0]*emaxs[0] + p->normal[1]*emaxs[1] + p->normal[2]*emaxs[2];
		dist2 = p->normal[0]*emins[0] + p->normal[1]*emins[1] + p->normal[2]*emins[2];
		break;
	case 1:
		dist1 = p->normal[0]*emins[0] + p->normal[1]*emaxs[1] + p->normal[2]*emaxs[2];
		dist2 = p->normal[0]*emaxs[0] + p->normal[1]*emins[1] + p->normal[2]*emins[2];
		break;
	case 2:
		dist1 = p->normal[0]*emaxs[0] + p->normal[1]*emins[1] + p->normal[2]*emaxs[2];
		dist2 = p->normal[0]*emins[0] + p->normal[1]*emaxs[1] + p->normal[2]*emins[2];
		break;
	case 3:
		dist1 = p->normal[0]*emins[0] + p->normal[1]*emins[1] + p->normal[2]*emaxs[2];
		dist2 = p->normal[0]*emaxs[0] + p->normal[1]*emaxs[1] + p->normal[2]*emins[2];
		break;
	case 4:
		dist1 = p->normal[0]*emaxs[0] + p->normal[1]*emaxs[1] + p->normal[2]*emins[2];
		dist2 = p->normal[0]*emins[0] + p->normal[1]*emins[1] + p->normal[2]*emaxs[2];
		break;
	case 5:
		dist1 = p->normal[0]*emins[0] + p->normal[1]*emaxs[1] + p->normal[2]*emins[2];
		dist2 = p->normal[0]*emaxs[0] + p->normal[1]*emins[1] + p->normal[2]*emaxs[2];
		break;
	case 6:
		dist1 = p->normal[0]*emaxs[0] + p->normal[1]*emins[1] + p->normal[2]*emins[2];
		dist2 = p->normal[0]*emins[0] + p->normal[1]*emaxs[1] + p->normal[2]*emaxs[2];
		break;
	case 7:
		dist1 = p->normal[0]*emins[0] + p->normal[1]*emins[1] + p->normal[2]*emins[2];
		dist2 = p->normal[0]*emaxs[0] + p->normal[1]*emaxs[1] + p->normal[2]*emaxs[2];
		break;
	default:
		dist1 = dist2 = 0;		// shut up compiler
#ifdef SIN
		// assert( 1 ) doesn't do jack shit
		assert( 0 );
#else
		assert( 1 );
#endif
		break;
	}

	sides = 0;
	if (dist1 >= p->dist)
		sides = 1;
	if (dist2 < p->dist)
		sides |= 2;

	assert( sides != 0 );

	return sides;
}
#else
#pragma warning( disable: 4035 )

__declspec( naked ) int BoxOnPlaneSide (vec3_t emins, vec3_t emaxs, struct cplane_s *p)
{
	static int bops_initialized;
	static int Ljmptab[8];

	__asm {

		push ebx
			
		cmp bops_initialized, 1
		je  initialized
		mov bops_initialized, 1
		
		mov Ljmptab[0*4], offset Lcase0
		mov Ljmptab[1*4], offset Lcase1
		mov Ljmptab[2*4], offset Lcase2
		mov Ljmptab[3*4], offset Lcase3
		mov Ljmptab[4*4], offset Lcase4
		mov Ljmptab[5*4], offset Lcase5
		mov Ljmptab[6*4], offset Lcase6
		mov Ljmptab[7*4], offset Lcase7
			
initialized:

		mov edx,ds:dword ptr[4+12+esp]
		mov ecx,ds:dword ptr[4+4+esp]
		xor eax,eax
		mov ebx,ds:dword ptr[4+8+esp]
		mov al,ds:byte ptr[17+edx]
		cmp al,8
		jge Lerror
		fld ds:dword ptr[0+edx]
		fld st(0)
		jmp dword ptr[Ljmptab+eax*4]
Lcase0:
		fmul ds:dword ptr[ebx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ebx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase1:
		fmul ds:dword ptr[ecx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ebx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase2:
		fmul ds:dword ptr[ebx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ecx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase3:
		fmul ds:dword ptr[ecx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ecx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase4:
		fmul ds:dword ptr[ebx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ebx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase5:
		fmul ds:dword ptr[ecx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ebx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase6:
		fmul ds:dword ptr[ebx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ecx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase7:
		fmul ds:dword ptr[ecx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ecx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
LSetSides:
		faddp st(2),st(0)
		fcomp ds:dword ptr[12+edx]
		xor ecx,ecx
		fnstsw ax
		fcomp ds:dword ptr[12+edx]
		and ah,1
		xor ah,1
		add cl,ah
		fnstsw ax
		and ah,1
		add ah,ah
		add cl,ah
		pop ebx
		mov eax,ecx
		ret
Lerror:
		int 3
	}
}
#pragma warning( default: 4035 )
#endif

*/

void zTBBox3D::SaveBIN (zCFileBIN &file) {
	file.BinWrite	(this , sizeof(*this));
};

void zTBBox3D::LoadBIN (zCFileBIN &file) {
	file.BinRead	(this , sizeof(*this));
};


///////////////////////////////////////////////////////////////////////////
//     BBox2D: Axis Aligned Bounding-Box 2D
///////////////////////////////////////////////////////////////////////////

int zTBBox2D::Classify (const zTBBox2D& bbox2D) const {
	// 'bbox2d' wird relativ zu 'this' klassifiziert
	// if (cullBox2D.Classify (portalBBox2D)!=zCAM_CLIP_TRIV_OUT)  
	if (bbox2D.maxs[VX]<mins[VX]) return zCAM_CLIP_TRIV_OUT;
	if (bbox2D.mins[VX]>maxs[VX]) return zCAM_CLIP_TRIV_OUT;
	if (bbox2D.maxs[VY]<mins[VY]) return zCAM_CLIP_TRIV_OUT;
	if (bbox2D.mins[VY]>maxs[VY]) return zCAM_CLIP_TRIV_OUT;

    if ((bbox2D.maxs[VX]<=maxs[VX]) && (bbox2D.mins[VX]>=mins[VX]) &&
		(bbox2D.maxs[VY]<=maxs[VY]) && (bbox2D.mins[VY]>=mins[VY])) return zCAM_CLIP_TRIV_IN;

	return zCAM_CLIP_CROSSING;
};

void zTBBox2D::ClipToBBox2D (const zTBBox2D& cullBox2D) {
	// clipped 'this' an der cullbox2d
	// 'schnittmengen-operation', Ergebnis ist undefiniert, wenn Boxen sich nicht schneiden !
	
	// portalBBox2D.ClipToBBox2D (cullBox2D);
	if (cullBox2D.mins[VX]>mins[VX]) mins[VX] = cullBox2D.mins[VX];
	if (cullBox2D.maxs[VX]<maxs[VX]) maxs[VX] = cullBox2D.maxs[VX];
	if (cullBox2D.mins[VY]>mins[VY]) mins[VY] = cullBox2D.mins[VY];
	if (cullBox2D.maxs[VY]<maxs[VY]) maxs[VY] = cullBox2D.maxs[VY];

	assert (!(mins[VX]>maxs[VX]));
	assert (!(mins[VY]>maxs[VY]));
//	if ((mins[VX]>maxs[VX]) || (mins[VY]>maxs[VY])) zerr.Report (zERR_WARN, 1000, "Illegal 2DBox !!!!!!!!");
};

void zTBBox2D::Draw () const {
	zCOLOR col(128,42,42,255);
	zlineCache.Line ((mins[VX]), (mins[VY]), (maxs[VX]), (mins[VY]), col);
	zlineCache.Line ((maxs[VX]), (mins[VY]), (maxs[VX]), (maxs[VY]), col);
	zlineCache.Line ((maxs[VX]), (maxs[VY]), (mins[VX]), (maxs[VY]), col);
	zlineCache.Line ((mins[VX]), (maxs[VY]), (mins[VX]), (mins[VY]), col);
};


///////////////////////////////////////////////////////////////////////////
//     OBBox3D: Oriented Bounding-Box 3D
///////////////////////////////////////////////////////////////////////////

zCOBBox3D::~zCOBBox3D() {
	zCList<zCOBBox3D> *obb = childs.GetNextInList();
	while (obb) {
		delete obb->GetData();
		obb = obb->GetNextInList();
	};
};

void zCOBBox3D::Draw (int depth, zCOLOR color) {
//	return; 
	// projecting 8 edge-vertices from bbox3D
//	int xscr[8], yscr[8];
	zPOINT3 point0, point1, point2, point3, point4, point5, point6, point7;
	zCCamera *cam = zCCamera::activeCam;
	if (!cam) return;

	point0 = cam->camMatrix * (center - axis[0]*extent[0] - axis[1]*extent[1] - axis[2]*extent[2]); //if (point0.n[VZ]<=0) goto next1; else cam->Project ( &point0, xscr[0], yscr[0]);
	point1 = cam->camMatrix * (center + axis[0]*extent[0] + axis[1]*extent[1] + axis[2]*extent[2]); //if (point1.n[VZ]<=0) goto next1; else cam->Project ( &point1, xscr[1], yscr[1]);
	point2 = cam->camMatrix * (center - axis[0]*extent[0] - axis[1]*extent[1] + axis[2]*extent[2]); //if (point2.n[VZ]<=0) goto next1; else cam->Project ( &point2, xscr[2], yscr[2]);
	point3 = cam->camMatrix * (center - axis[0]*extent[0] + axis[1]*extent[1] - axis[2]*extent[2]); //if (point3.n[VZ]<=0) goto next1; else cam->Project ( &point3, xscr[3], yscr[3]);
	point4 = cam->camMatrix * (center - axis[0]*extent[0] + axis[1]*extent[1] + axis[2]*extent[2]); //if (point4.n[VZ]<=0) goto next1; else cam->Project ( &point4, xscr[4], yscr[4]);
	point5 = cam->camMatrix * (center + axis[0]*extent[0] - axis[1]*extent[1] - axis[2]*extent[2]); //if (point5.n[VZ]<=0) goto next1; else cam->Project ( &point5, xscr[5], yscr[5]);
	point6 = cam->camMatrix * (center + axis[0]*extent[0] - axis[1]*extent[1] + axis[2]*extent[2]); //if (point6.n[VZ]<=0) goto next1; else cam->Project ( &point6, xscr[6], yscr[6]);
	point7 = cam->camMatrix * (center + axis[0]*extent[0] + axis[1]*extent[1] - axis[2]*extent[2]); //if (point7.n[VZ]<=0) goto next1; else cam->Project ( &point7, xscr[7], yscr[7]);

	zPOINT3 pointx0, pointx1, pointx2, pointx3;
	pointx0 = cam->camMatrix * (center);					//if (point.n[VZ]<=0) goto next2; else cam->Project ( &point, xscr[0], yscr[0]);
	pointx1 = cam->camMatrix * (center + axis[0]*30);	//if (point.n[VZ]<=0) goto next2; else cam->Project ( &point, xscr[1], yscr[1]);
	pointx2 = cam->camMatrix * (center + axis[1]*30);	//if (point.n[VZ]<=0) goto next2; else cam->Project ( &point, xscr[2], yscr[2]);
	pointx3 = cam->camMatrix * (center + axis[2]*30);	//if (point.n[VZ]<=0) goto next2; else cam->Project ( &point, xscr[3], yscr[3]);

	zMATRIX4 camMatBackup = cam->camMatrix;

/*	// 0: 000
	zlineCache.Line ((xscr[0]),(yscr[0]), (xscr[2]),(yscr[2]), color);
	zlineCache.Line ((xscr[0]),(yscr[0]), (xscr[3]),(yscr[3]), color);
	zlineCache.Line ((xscr[0]),(yscr[0]), (xscr[5]),(yscr[5]), color);
	// 1: 111
	zlineCache.Line ((xscr[1]),(yscr[1]), (xscr[4]),(yscr[4]), color);
	zlineCache.Line ((xscr[1]),(yscr[1]), (xscr[6]),(yscr[6]), color);
	zlineCache.Line ((xscr[1]),(yscr[1]), (xscr[7]),(yscr[7]), color);
	// 2: 001
	zlineCache.Line ((xscr[2]),(yscr[2]), (xscr[4]),(yscr[4]), color);
	zlineCache.Line ((xscr[2]),(yscr[2]), (xscr[6]),(yscr[6]), color);
	// 3: 010
	zlineCache.Line ((xscr[3]),(yscr[3]), (xscr[4]),(yscr[4]), color);
	zlineCache.Line ((xscr[3]),(yscr[3]), (xscr[7]),(yscr[7]), color);
	// 4: 011
	// 5: 100
	zlineCache.Line ((xscr[5]),(yscr[5]), (xscr[6]),(yscr[6]), color);
	zlineCache.Line ((xscr[5]),(yscr[5]), (xscr[7]),(yscr[7]), color);
	// 6: 101
	// 7: 110
*/
	zlineCache.LineCS3D (point0, point2, color);
	zlineCache.LineCS3D (point0, point3, color);
	zlineCache.LineCS3D (point0, point5, color);
	// 1: 111
	zlineCache.LineCS3D (point1, point4, color);
	zlineCache.LineCS3D (point1, point6, color);
	zlineCache.LineCS3D (point1, point7, color);
	// 2: 001
	zlineCache.LineCS3D (point2, point4, color);
	zlineCache.LineCS3D (point2, point6, color);
	// 3: 010
	zlineCache.LineCS3D (point3, point4, color);
	zlineCache.LineCS3D (point3, point7, color);
	// 4: 011
	// 5: 100
	zlineCache.LineCS3D (point5, point6, color);
	zlineCache.LineCS3D (point5, point7, color);
	// 6: 101
	// 7: 110

	// Axis at Center
	zlineCache.LineCS3D (pointx0, pointx1, color);
	zlineCache.LineCS3D (pointx0, pointx2, color);
	zlineCache.LineCS3D (pointx0, pointx3, color);
/*	zlineCache.Line ((xscr[0]),(yscr[0]), (xscr[1]),(yscr[1]), color);
	zlineCache.Line ((xscr[0]),(yscr[0]), (xscr[2]),(yscr[2]), color);
	zlineCache.Line ((xscr[0]),(yscr[0]), (xscr[3]),(yscr[3]), color);*/

	cam->camMatrix = camMatBackup;

	depth--;
	if (depth==0) return;
/*	const int MAX_COL = 5;
	int drawCol[MAX_COL] = {
		GFX_BLUE, 
		GFX_GREEN, 
		GFX_GOLD, 
		GFX_GREY, 
		GFX_LGREY, 
	};*/
//	color = depth;
//	if (color>=MAX_COL) color = MAX_COL-1;
//	color = drawCol[color];
	zCList<zCOBBox3D> *obb = childs.GetNextInList();
	while (obb) {
//		obb->GetData()->Draw (depth, color);
//		obb->GetData()->Draw (depth, color+(1 + (1<<5) + (1<<11)));
//		obb->GetData()->Draw (depth, color+(1 + 32 + 512));
		obb->GetData()->Draw (depth, color);
		obb = obb->GetNextInList();
	};
};
/*
void zCOBBox3D::BuildOBBFromPoly (zCPolygon *poly) {
	// For a single poly, orientation is easily determined.
	// The major axis is parallel to the longest edge.
	// The minor axis is normal to the triangle.
	// The in-between axis is determine by these two.

};
*/

void zCOBBox3D::BuildOBB (int numPoly, zCPolygon**polyList, const zBOOL bboxCenter) 
{ 
	// output: center, axis, extent

	// FIXME: better build-func		=> RAPID
	// FIXME: better build-func ?	=> Eberly, minbox3.cpp
	int i;
	int n=0;
/*
	if (numPoly==1) {
		BuildOBBFromPoly (polyList[0]);
		return;
	};
*/
	// vertices aus den Polys holen und in einer Liste sammeln
	for (i=0; i<numPoly; i++)	
		n += polyList[i]->polyNumVert;
	zCVertex **vert		= zNEW(zCVertex*) [n];
	zCVertex **pvert	= vert;
	zCVertex **pvert2;
	n=0;
	for (i=0; i<numPoly; i++)
	{
		// Polys, die nicht an CollDet teilnehmen sollen werden rausgefilter

		// ATT: ab Gothic 1.11i werden Polys, dessen Materialien das noCollDet
		// Flag gesetzt haben, nicht mehr vom Zusammembauen der BBoxes ausgeschlossen
//		if ((polyList[i]->GetMaterial()) && (polyList[i]->GetMaterial()->GetNoCollDet()))
//			continue;
		for (int j=0; j<polyList[i]->polyNumVert; j++) {
			(*pvert) = polyList[i]->GetVertexPtr(j);
			for (pvert2=vert; pvert2<pvert; pvert2++) {
				if ((*pvert)==(*pvert2)) goto foundVert;
			};
			pvert++;
			n++;
foundVert:;
		};
	};


	// compute mean of points
	zVEC3 mean(0,0,0);
	for (i=0; i<n; i++) 
		mean+= vert[i]->position;

	if (n==0)
	{
		delete[] vert;
		return;
	}

	mean /= n;

	// Center=?
	// a) mean				(schlechtes fitting)
	// b) center of bbox3d	(probs beim recSubdivide => newCenter=oldCenter)
	// Ist beides problematisch. Evtl: b) beim ersten mal, sonst immer a)

	// compute center
	if (bboxCenter) {
		// obb center is the center of BBox3D
		zTBBox3D	polyListBBox;
		polyListBBox.Init();
		for (i=0; i<n; i++) 
			polyListBBox.AddPoint (vert[i]->position);
		center = polyListBBox.GetCenter();

		axis[0]	= zVEC3(1,0,0);		extent[0] = (polyListBBox.maxs[0] - polyListBBox.mins[0]) * zREAL(0.5F);
		axis[1]	= zVEC3(0,1,0);		extent[1] = (polyListBBox.maxs[1] - polyListBBox.mins[1]) * zREAL(0.5F);
		axis[2]	= zVEC3(0,0,1);		extent[2] = (polyListBBox.maxs[2] - polyListBBox.mins[2]) * zREAL(0.5F);
		goto finished;
	} else {
		// box center is the mean of the distribution
		center = mean;
	//	center = 0.5F * (center+mean);
	};

	{
		// compute covariances of points
		double xxsum = 0.0, xysum = 0.0, xzsum = 0.0;
		double yysum = 0.0, yzsum = 0.0, zzsum = 0.0;
		for (i = 0; i < n; i++)
		{
			double dx = vert[i]->position[VX] - mean[VX];
			double dy = vert[i]->position[VY] - mean[VY];
			double dz = vert[i]->position[VZ] - mean[VZ];
			xxsum += dx*dx;
			xysum += dx*dy;
			xzsum += dx*dz;
			yysum += dy*dy;
			yzsum += dy*dz;
			zzsum += dz*dz;
		}
		double xxcov = xxsum/n;
		double xycov = xysum/n;
		double xzcov = xzsum/n;
		double yycov = yysum/n;
		double yzcov = yzsum/n;
		double zzcov = zzsum/n;
		
		// compute eigenvectors for covariance matrix
		zCMgcEigenD eig(3);
		eig.Matrix(0,0) = xxcov;
		eig.Matrix(0,1) = xycov;
		eig.Matrix(0,2) = xzcov;
		eig.Matrix(1,0) = xycov;
		eig.Matrix(1,1) = yycov;
		eig.Matrix(1,2) = yzcov;
		eig.Matrix(2,0) = xzcov;
		eig.Matrix(2,1) = yzcov;
		eig.Matrix(2,2) = zzcov;
		eig.EigenStuff3();
		zVEC3 U = zVEC3 (	eig.Eigenvector(0,0),
							eig.Eigenvector(1,0),
							eig.Eigenvector(2,0));
		zVEC3 V = zVEC3 (	eig.Eigenvector(0,1),
							eig.Eigenvector(1,1),
							eig.Eigenvector(2,1));
		zVEC3 W = zVEC3 (	eig.Eigenvector(0,2),
							eig.Eigenvector(1,2),
							eig.Eigenvector(2,2));
		
		// Box axes are the eigenvectors of the covariance matrix with
		// adjusted lengths to enclose the points.  If U, V, and W are the
		// eigenvectors, C is the center of the box, and X is a point in
		// the input list, then X = C + a*U + b*V + c*W.  The box extent is
		// determined by max|a|, max|b|, and max|c|.  The box axes are then
		// defined to be (max|a|)*U and (max|b|)*V.  Note that since U and V
		// are unit length and orthogonal, a = Dot(U,X-C), b = Dot(V,X-C),
		// and c = Dot(W,X-C).
		U.Normalize();
		V.Normalize();
		W.Normalize();
		double amax = 0.0, bmax = 0.0, cmax = 0.0;
		for (i = 0; i < n; i++)
		{
			double dx		= vert[i]->position[VX] - center[VX];
			double dy		= vert[i]->position[VY] - center[VY];
			double dz		= vert[i]->position[VZ] - center[VZ];
			double absdot;
			absdot = fabs(U[VX]*dx + U[VY]*dy + U[VZ]*dz); if ( absdot > amax ) amax = absdot;
			absdot = fabs(V[VX]*dx + V[VY]*dy + V[VZ]*dz); if ( absdot > bmax ) bmax = absdot;
			absdot = fabs(W[VX]*dx + W[VY]*dy + W[VZ]*dz); if ( absdot > cmax ) cmax = absdot;
		}
	//	axis[0]		= U.Normalize();
	//	axis[1]		= V.Normalize();
	//	axis[2]		= W.Normalize();
		axis[0]		= U;
		axis[1]		= V;
		axis[2]		= W;
		U			= amax * U;			// beachte: a,b,cmax dims koennten 0 sein !
		V			= bmax * V;
		W			= cmax * W;
		extent[VX]	= U.Length();
		extent[VY]	= V.Length();
		extent[VZ]	= W.Length();
	};

finished:;
	// Axen so tauschen, dass die erste die mit der groessten Ausdehnung ist (order preserved)
//	axis[1] = -axis[1];		// noetig, damit die Achsen eine Rot-Trafo bilden 
//	axis[2] = -axis[2];		// noetig, damit die Achsen eine Rot-Trafo bilden 
	int bestBasis=0;
	if (extent[1]> extent[bestBasis]) { bestBasis=1; };
	if (extent[2]> extent[bestBasis]) { bestBasis=2; };
	if (bestBasis==1) {
		zSwap (axis	 [0], axis	[1]);
		zSwap (extent[0], extent[1]);
		zSwap (axis	 [1], axis	[2]);
		zSwap (extent[1], extent[2]);
	} else
	if (bestBasis==2) {
		zSwap (axis	 [0], axis	[2]);
		zSwap (extent[0], extent[2]);
		zSwap (axis	 [1], axis	[2]);
		zSwap (extent[1], extent[2]);
	};

	// cleanup
	delete[] vert;
};

static zBOOL buildRecFirstTime = TRUE;

void zCOBBox3D::BuildRec (int numPoly, zCPolygon** polyList, int depthToGo) {
	// build from mesh-structure
	// maxtree-depth
	// max Verts per obb

	if (numPoly<1) return;

	// aktuellen OBB bauen
	BuildOBB (numPoly, polyList, buildRecFirstTime);
	buildRecFirstTime = FALSE;
	depthToGo--;

	if (depthToGo<=0)	return;

	// Axe mit der groessten Ausdehnung ist die erste Axe !

	// entlang der laengsten Axe splitten
	// => die uebrigen beiden Axen bilden ein Ebene, die das Object splittet
	zCPolygon	**leftPoly	= zNEW(zCPolygon*) [numPoly];
	zCPolygon	**rightPoly	= zNEW(zCPolygon*) [numPoly];
	int			numLeft		= 0;
	int			numRight	= 0;
	zTPlane		splitPlane;
	splitPlane.Calc (center, center+axis[1], center+axis[2]);

	for (int i=0; i<numPoly; i++) 
	{
		// Polys, die nicht an CollDet teilnehmen sollen werden rausgefilter

		// ATT: ab Gothic 1.11i werden Polys, dessen Materialien das noCollDet
		// Flag gesetzt haben, nicht mehr vom Zusammembauen der BBoxes ausgeschlossen
//		if ((polyList[i]->GetMaterial()) && (polyList[i]->GetMaterial()->GetNoCollDet()))
//			continue;
		switch (polyList[i]->ClassifyPlane (splitPlane)) {
		case zPLANE_INFRONT:
		case zPLANE_ONPLANE:
			leftPoly [numLeft ++] = polyList[i];
			break;
		case zPLANE_BEHIND:
			rightPoly[numRight++] = polyList[i];
			break;
		case zPLANE_SPANNING:
			if (splitPlane.ClassifyPoint (polyList[i]->GetCenter())==zPLANE_INFRONT) 
				leftPoly [numLeft ++] = polyList[i]; else
				rightPoly[numRight++] = polyList[i];
			break;
		};
	};

//	zerr.Message ("- left: "+zSTRING(numLeft)+", right: "+zSTRING(numRight));
	if ((numLeft>=1) && (numRight>=1)) {
		zCOBBox3D	*left		= zNEW(zCOBBox3D);
		zCOBBox3D	*right		= zNEW(zCOBBox3D);
		childs.Insert	(left);
		childs.Insert	(right);
		left ->BuildRec	(numLeft , leftPoly , depthToGo);
		right->BuildRec	(numRight, rightPoly, depthToGo);
	};
	// cleanup
	goto cleanup;
cleanup:;
	delete[] leftPoly;
	delete[] rightPoly;
};

void zCOBBox3D::BuildOBBTree (zCMesh *mesh, int maxDepth) 
{
	buildRecFirstTime = TRUE;
	BuildRec (mesh->numPoly, mesh->PolyList(), maxDepth);
};

void zCOBBox3D::BuildOBBTree (int numPoly, zCPolygon** polyList, int maxDepth) 
{
	buildRecFirstTime = TRUE;
	BuildRec (numPoly, polyList, maxDepth);
};

/*-------------------------------------------------------------------------*/

int zCOBBox3D::TestIntersectionOBB (const zCOBBox3D* b2) const
{
    zREAL	d0, d1, d2;
    zREAL	r0, r1, r2;
    zMAT3	C;
	zVEC3	b1Axis[3];

	// center(trafo), axis(trafo), extent
	//- Normale/Ebenengleichung transformieren:	N'   = (M^-1)^T * N
	b1Axis[0]	= trafoB2ToThis.Rotate (b2->axis[0]);
	b1Axis[1]	= trafoB2ToThis.Rotate (b2->axis[1]); 
	b1Axis[2]	= trafoB2ToThis.Rotate (b2->axis[2]);

	zVEC3 D		= (trafoB2ToThis * b2->center) - center;

	// Schneller Sphere-Sphere Test vorneweg.. (src:news)
	// FIXME: scheint buggy zu sein, aber warum ??? die Formel stimmt doch ...
	//         D^2 > r^2
	// dx^2 + dy^2 > r^2 - dz^2



	// KANN es sein, dass es falsch ist, einfach das MAX-EXTENT zu nehmen ??

//	r1 = GetMaxExtent() + b2->GetMaxExtent();
//	if ((D[VX]*D[VX] + D[VY]*D[VY]) > (r1 + D[VZ])*(r1 - D[VZ])) return 0;

    /* L = A0 */
    C[0][0] = (axis[0] * b1Axis[0]);
    C[0][1] = (axis[0] * b1Axis[1]);
    C[0][2] = (axis[0] * b1Axis[2]);
    d0		= (D *  axis[0]);
    r0		= fabs(extent[0]);
    r1		= fabs(b2->extent[0]*C[0][0]) + fabs(b2->extent[1]*C[0][1]) + fabs(b2->extent[2]*C[0][2]);
    r2		= fabs(d0);
    if ( r2 > r0+r1 ) return 0;

    /* L = A1 */
    C[1][0] = (axis[1] * b1Axis[0]);
    C[1][1] = (axis[1] * b1Axis[1]);
    C[1][2] = (axis[1] * b1Axis[2]);
    d1		= (D * axis[1]);
    r0		= fabs(extent[1]);
    r1		= fabs(b2->extent[0]*C[1][0]) + fabs(b2->extent[1]*C[1][1])+fabs(b2->extent[2]*C[1][2]);
    r2		= fabs(d1);
    if ( r2 > r0+r1 ) return 0;

    /* L = A2 */
    C[2][0] = (axis[2] * b1Axis[0]);
    C[2][1] = (axis[2] * b1Axis[1]);
    C[2][2] = (axis[2] * b1Axis[2]);
    d2		= (D * axis[2]);
    r0		= fabs(extent[2]);
    r1		= fabs(b2->extent[0]*C[2][0]) + fabs(b2->extent[1]*C[2][1]) + fabs(b2->extent[2]*C[2][2]);
    r2		= fabs(d2);
    if ( r2 > r0+r1 ) return 0;

    /* L = B0 */
    r0 = fabs(extent[0]*C[0][0])+fabs(extent[1]*C[1][0])+fabs(extent[2]*C[2][0]);
    r1 = fabs(b2->extent[0]);
    r2 = fabs((D * b1Axis[0]));
    if ( r2 > r0+r1 ) return 0;

    /* L = B1 */
    r0 = fabs(extent[0]*C[0][1])+fabs(extent[1]*C[1][1])+fabs(extent[2]*C[2][1]);
    r1 = fabs(b2->extent[1]);
    r2 = fabs((D * b1Axis[1]));
    if ( r2 > r0+r1 ) return 0;

	/* L = B2 */
	r0 = fabs(extent[0]*C[0][2])+fabs(extent[1]*C[1][2])+fabs(extent[2]*C[2][2]);
	r1 = fabs(b2->extent[2]);
    r2 = fabs((D * b1Axis[2]));
	if ( r2 > r0+r1 ) return 0; 

    /* L = A0xB0 */
    r0 = fabs(extent[1]*C[2][0])+fabs(extent[2]*C[1][0]);
    r1 = fabs(b2->extent[1]*C[0][2])+fabs(b2->extent[2]*C[0][1]);
    r2 = fabs(d2*C[1][0]-d1*C[2][0]);
    if ( r2 > r0+r1 ) return 0;

    /* L = A0xB1 */
    r0 = fabs(extent[1]*C[2][1])+fabs(extent[2]*C[1][1]);
    r1 = fabs(b2->extent[0]*C[0][2])+fabs(b2->extent[2]*C[0][0]);
    r2 = fabs(d2*C[1][1]-d1*C[2][1]);
    if ( r2 > r0+r1 ) return 0;

    /* L = A0xB2 */
    r0 = fabs(extent[1]*C[2][2])+fabs(extent[2]*C[1][2]);
    r1 = fabs(b2->extent[0]*C[0][1])+fabs(b2->extent[1]*C[0][0]);
    r2 = fabs(d2*C[1][2]-d1*C[2][2]);
    if ( r2 > r0+r1 ) return 0;

    /* L = A1xB0 */
    r0 = fabs(extent[0]*C[2][0])+fabs(extent[2]*C[0][0]);
    r1 = fabs(b2->extent[1]*C[1][2])+fabs(b2->extent[2]*C[1][1]);
    r2 = fabs(d0*C[2][0]-d2*C[0][0]);
    if ( r2 > r0+r1 ) return 0;

    /* L = A1xB1 */
    r0 = fabs(extent[0]*C[2][1])+fabs(extent[2]*C[0][1]);
    r1 = fabs(b2->extent[0]*C[1][2])+fabs(b2->extent[2]*C[1][0]);
    r2 = fabs(d0*C[2][1]-d2*C[0][1]);
    if ( r2 > r0+r1 ) return 0;

    /* L = A1xB2 */
    r0 = fabs(extent[0]*C[2][2])+fabs(extent[2]*C[0][2]);
    r1 = fabs(b2->extent[0]*C[1][1])+fabs(b2->extent[1]*C[1][0]);
    r2 = fabs(d0*C[2][2]-d2*C[0][2]);
    if ( r2 > r0+r1 ) return 0;

    /* L = A2xB0 */
    r0 = fabs(extent[0]*C[1][0])+fabs(extent[1]*C[0][0]);
    r1 = fabs(b2->extent[1]*C[2][2])+fabs(b2->extent[2]*C[2][1]);
    r2 = fabs(d1*C[0][0]-d0*C[1][0]);
    if ( r2 > r0+r1 ) return 0;

    /* L = A2xB1 */
    r0 = fabs(extent[0]*C[1][1])+fabs(extent[1]*C[0][1]);
    r1 = fabs(b2->extent[0]*C[2][2])+fabs(b2->extent[2]*C[2][0]);
    r2 = fabs(d1*C[0][1]-d0*C[1][1]);
    if ( r2 > r0+r1 ) return 0;

    /* L = A2xB2 */
    r0 = fabs(extent[0]*C[1][2])+fabs(extent[1]*C[0][2]);
    r1 = fabs(b2->extent[0]*C[2][1])+fabs(b2->extent[1]*C[2][0]);
    r2 = fabs(d1*C[0][2]-d0*C[1][2]);
    if ( r2 > r0+r1 ) return 0;

    return 1;    
}

int zCOBBox3D::TestIntersectionTreeRec (const zCOBBox3D* b2) const
{
	zBOOL intersect = TestIntersectionOBB (b2);

	if (intersect) {
		if ((IsLeaf()) && (b2->IsLeaf())) {
			// if this.triangle overlaps b2.triangle then return true
			return TRUE;
		};

		if ((b2->IsLeaf()) || (!IsLeaf() && (GetMaxExtent() > b2->GetMaxExtent()))) {
			// Alle Childs von A gegen B testen
			zCList<zCOBBox3D> *child = childs.GetNextInList();
			while (child) {
				intersect = child->GetData()->TestIntersectionTreeRec (b2);
				if (intersect) return intersect;
				child = child->GetNextInList();
			};
		} else {
			// Alle Childs von B gegen A testen
			zCList<zCOBBox3D> *child = b2->childs.GetNextInList();
			while (child) {
				intersect = TestIntersectionTreeRec (child->GetData());
				if (intersect) return intersect;
				child = child->GetNextInList();
			};
		};
	};
	return FALSE;
};

zMATRIX4 zCOBBox3D::trafoB2ToThis;

int zCOBBox3D::TestIntersectionTree (const zCOBBox3D* b2, const zMATRIX4& _trafoB2ToThis) const
{
	trafoB2ToThis = _trafoB2ToThis;
	return TestIntersectionTreeRec (b2);
};

zBOOL zCOBBox3D::TraceRay (const zPOINT3& rayOrg, const zVEC3& ray, zPOINT3& inters) const
{
	// Strategie:
	// Ray ins OBB-Koordsyst. transformieren und dann einen axis-aligned BBox3D/Poly Check
	// im KS des OBB machen.
	zTBBox3D	bbox3D;
	zMATRIX4	trafo = Alg_Identity3D(); 

	trafo.SetRightVector	(axis[0]);		// x
	trafo.SetUpVector		(axis[1]);		// y
	trafo.SetAtVector		(axis[2]);		// z
	trafo.SetTranslation	(center);
	
	// trafo = trafoWorldToOBB
	trafo = trafo.InverseLinTrafo();

	bbox3D.mins = -extent;
	bbox3D.maxs =  extent;

	// Ray transformieren
	zVEC3	xrayOrg	= trafo * rayOrg;
	zVEC3	xray	= trafo.Rotate (ray);
	zBOOL	res		= bbox3D.TraceRay	(xrayOrg, xray, inters);
	return res;
};

/* ----------------------------------------------------------------------
	
   zCOBBox3D::CheckOBBPolyIntersection()	

	15.11.2000	[Moos]	
                Positionssicherungshack über VertCamSpace entfernt
	12.12.2000	[HILDEBRANDT]
				Argument trafoWorldToObj 'const' gemacht.

   ---------------------------------------------------------------------- */

zBOOL zCOBBox3D::CheckOBBPolyIntersection (zCPolygon *poly, const zMATRIX4& trafoWorldToObj) const 
{
	// Strategie:
	// Poly ins OBB-Koordsyst. transformieren und dann einen axis-aligned BBox3D/Poly Check
	// im KS des OBB machen.

	// FIXME:  axis[0]  BuildOBB
	// [EDENFELD] 1.19. Folgender Test ist vermutlich schneller als der alte und behebt ausserdem einen seltenen
	// Polyverzerrer Bug der sich in mit einigen Optimierungen öfters zeigte
	static zCPolygon testPoly;
	static zBOOL	 initDone = FALSE;
	if (!initDone)
	{
		initDone = TRUE;
		testPoly.AllocVerts(zMAX_POLY_VERTS);
		for (int i=0; i<zMAX_POLY_VERTS; i++)
		{
			testPoly.vertex[i] = zNEW(zCVertex);
		}
	}

	int			i;
	zTBBox3D	bbox3D;
	zMATRIX4	trafo = Alg_Identity3D(); 

	trafo.SetRightVector	(axis[0]);		// x
	trafo.SetUpVector		(axis[1]);		// y
	trafo.SetAtVector		(axis[2]);		// z
	trafo.SetTranslation	(center);
	
	trafo = trafo.InverseLinTrafo() * trafoWorldToObj;

	bbox3D.mins = -extent;
	bbox3D.maxs =  extent;

    zERR_ASSERT(poly->polyNumVert <= zMAX_POLY_VERTS);

	// Verts Backup & transformieren
	for (i=0; i<poly->polyNumVert; i++) 
	{
		testPoly.vertex[i]->position		= trafo * poly->GetVertexPtr(i)->position;
	};
	testPoly.polyNumVert = poly->polyNumVert;

	// Plane Backup & trafo
	//- Normale/Ebenengleichung transformieren:	N'   = (M^-1)^T * N
	testPoly.polyPlane.normal	= poly->polyPlane.normal * trafo.InverseLinTrafo(); 
	testPoly.polyPlane.distance = poly->polyPlane.normal * testPoly.GetVertexPtr(0)->position;

	return testPoly.CheckBBoxPolyIntersection (bbox3D);
};



zTBBox3D zCOBBox3D::GetBBox3D () const {
	static const int sign[8][3] =	{	-1, -1, -1,
										-1, -1, +1,
										-1, +1, -1,
										-1, +1, +1,
										+1, -1, -1,
										+1, -1, +1,
										+1, +1, -1,
										+1, +1, +1 };
	zTBBox3D bbox;
	bbox.Init();
	for (int y=0; y<8; y++) {
		zPOINT3 point = (center + sign[y][0]*axis[0]*extent[0] - sign[y][1]*axis[1]*extent[1] - sign[y][2]*axis[2]*extent[2]);
//		zerr.Message (zSTRING(sign[y][0])+", "+zSTRING(sign[y][1])+", "+zSTRING(sign[y][2]));
		bbox.AddPoint (point);
	};
	return bbox; 
};

//	zVEC3				center;			// center
//	zVEC3				axis[3];		// orthonormal basis
//	zVEC3				extent;			// extent along basis vectors, [0] is largest extent


void zCOBBox3D::SetByBBox3D (const zTBBox3D &bbox3D) 
{
	center	= bbox3D.GetCenter();
	axis[0]	= zVEC3(1,0,0);
	axis[1]	= zVEC3(0,1,0);
	axis[2]	= zVEC3(0,0,1);
	for (int i=0; i<3; i++)
		extent[i]	= (bbox3D.maxs[i]-bbox3D.mins[i])*0.5F;
};

void zCOBBox3D::Transform (const zMATRIX4& trafo) {
	axis[0]	= trafo.Rotate (axis[0]);
	axis[1]	= trafo.Rotate (axis[1]); 
	axis[2]	= trafo.Rotate (axis[2]);
	center	= trafo * center;
};

zCOBBox3D& zCOBBox3D::operator= (const zCOBBox3D& inOBB)
{
	// deep copy
	center	= inOBB.center;
	axis[0]	= inOBB.axis[0];
	axis[1]	= inOBB.axis[1];
	axis[2]	= inOBB.axis[2];
	extent	= inOBB.extent;

	zCList<zCOBBox3D> *obb = inOBB.childs.GetNextInList();
	while (obb) {
		zCOBBox3D *newOBB	= zNEW(zCOBBox3D);
		this->childs.Insert (newOBB);
		*newOBB				= *(obb->GetData());	// operator= !
		obb					= obb->GetNextInList();
	};
	return *this;
};

void zCOBBox3D::SaveBIN (zCFileBIN &file) 
{
	file.BinWrite (&center	, sizeof(center));
	file.BinWrite (&axis	, sizeof(axis));
	file.BinWrite (&extent	, sizeof(extent));
	zWORD	numChilds	= childs.GetNum();
	file.BinWriteWord	(numChilds);

	//
	zCList<zCOBBox3D> *obb = childs.GetNextInList();
	for (int i=0; i<numChilds; i++)
	{
		obb->GetData()->SaveBIN	(file);
		obb = obb->GetNextInList();
	};
};

void zCOBBox3D::LoadBIN (zCFileBIN &file) 
{
	file.BinRead	(&center	, sizeof(center));
	file.BinRead	(&axis		, sizeof(axis));
	file.BinRead	(&extent	, sizeof(extent));
	zWORD numChilds;
	file.BinReadWord(numChilds);

	if (numChilds>1000) 
	{
		zERR_WARNING("C: zCOBBox3D::LoadBIN(): really many child bboxes found. probable data corruption. try to delete all _compiled data instead converting on the fly!");
		numChilds = 0;
		return;
	}

	for (int i=0; i<numChilds; i++)
	{
		zCOBBox3D *newOBB	= zNEW(zCOBBox3D);
		this->childs.Insert (newOBB);
		newOBB->LoadBIN		(file);
	};
};


//#pragma optimize( "", on)

/*
  Ray / OBB Test:
	ray_int.pdf
*/

/*
A "Fast" Method for Culling of Oriented-Bounding 
                                   Boxes (OBBs) Against a Perspective Viewing Frustum 
                                             in Large "Walkthrough" Models

                                                       Kenny Hoff 
                                                        5/23/96



Given the following preconditions:

     We are given a camera system defined in the world coordinate system that includes the following: 
          camera coordinate axes (view-up, viewplane normal, "horizon") 
          camera origin in world coordinates (location of the camera) 
          center-of-projection (COP) defined in camera coordinates (must be able to accomodate "off-axis" COP for use in stereo displays) 
          near and far planes that are parallel to the viewing plane and are also defined in camera coordinates 
          viewplane window extents (left, right, top, bottom) defined on camera XY plane 
     We have a convex polyhedron, called the perspective viewing frustum, against which to cull the OBBs; this is formed from the pyramid with the COP
     at the tip and the far plane at its base by truncating the top with the near plane. The extents of the top and bottom of this truncated pyramid are
     determined from the intersections with the near and far planes of the projectors formed from the COP through the corners of the viewplane window.
     Since this frustum is a convex polyhedra we can simply represent it as a set of six planes in "point-normal" form. 
     We have a list of OBBs defined in world coordinates (OBB relative-transformation hierarchies must be decomposed so that all are in world coords).
     The OBBs are tight-fitting, arbitrarily oriented bounding boxes that are defined by an origin, a set of OBB-coordinate axes, and extents along these
     axes. 

We can perform a fast overlap test of the OBB and the viewing frustum by keeping a few simple guidelines in mind:

     If all vertices of the OBB are in the "outside" half-space of any of the frustum's planes, then the OBB is trivially REJECTED. 
     If any vertex of the OBB is determined to be inside the frustum (if tested to be in the "inside" half-space of each of the frustum's planes), then it is
     trivially ACCEPTED. 
     If we cannot trivially reject or accept, then all of the vertices are outside the frustum and only three possibilities remain: a corner of the frustum
     protrudes through a face of the OBB, the OBB surrounds the frustum, or the OBB does not overlap the frustum but happens to cross the "corner
     planes". 
     We are dealing specifically with the problem of speeding up "walkthrough" models that are composed of hundreds of thousands of polygons that
     surround the viewer at all times (the viewer is immersed into the model, not viewing it from the outside). Given this, we can expect, on average, that a
     larger number of OBBs will be trivially rejected rather than accepted; so, we should go for this test first. In other words, first we will test each vertex of
     the OBB against a single plane, rather than testing each vertex against every plane (trivial reject vs. trivial accept). 
     We should try to avoid any matrix transformations since they are too expensive. 

Now given a viewing-frustum (VF) and a single OBB here is the proposed implementation:

   1.Calculate the eight vertices of the OBB using the OBB axes and extents along these axes. 
   2.Create a "in-out" 6-bit sequence (LRTBNF for left, right, top, bottom, near, and far respectively) for each vertex that is used to determine the vertex's
     location with respect to the six planes of the viewing-frustum (a set bit means it is "outside" of that respective plane). Initialize this sequence to zero for
     each vertex. 
   3.Go for trivial rejection by repeating the following steps for each plane in the viewing frustum or until rejected. Process the planes in the following
     order: near, left, right, bottom, top, far (this order can be chosen arbitrarily, but we must try to eliminate OBBs as early as possible; it seems logical to
     proceed in this order for large models in which the viewer is totally immersed): 
        1."encode" the eight vertices (by properly setting the appropriate bit) as either "inside" or "outside" the current plane being tested. This simply
          involves the evaluation of the plane equation for each vertex (Ax+By+Cz+D : three multiplies and three adds), and we only need to know the
          sign of the result. 
        2.if the logical AND of all eight of the 6-bit sequences is not equal to zero, then it is trivially REJECTED. 
   4.By now, if the OBB was not trivially rejected, the 6-bit sequence should be properly encoded with respect to all six planes (remembering not to reset
     the sequence for each new plane being tested for in the trivial rejection tests). If ANY of the sequences equals zero, we can trivially ACCEPT (we
     must do so upon encountering the FIRST occurance). 
   5.Now we must handle the three special cases: 
        1.Test for frustum protrusion through an OBB face by checking each edge in the frustum (12 edges) for intersection with a polygonal face of the
          OBB. We can determine overlap upon the first occurance of an edge that intersects a single face of the OBB. So take each frustum edge in turn
          and check it against each face in the OBB. If all of the OBB faces miss the edge move on to the next frustum edge. It is possible to determine
          overlap, in best case, in one edge-face intersection test; and in worst case, 12 x 6 = 72 tests. 
        2.If the frustum protrusion fails, check for containment of the frustum inside the OBB by just checking if the origin of the frustum (assuming
          viewplane lies between near and far planes) is inside the OBB. If the frustum is inside the OBB, then they most definitely overlap (ACCEPT).
          This requires evaluation of the "in-out" test for each plane of the OBB (six plane equation evaluations). 
        3.If both of these test fail, REJECT the OBB because it does not overlap the viewing-frustum. 

The special cases are computationally expensive, but should only occur for a small number of OBBs compared to the amount trivally rejected and accepted.
The early, most frequent tests are VERY inexpensive requiring as little as 24 multiplies, 24 adds, and 7 logical operations (after computation of vertices) for
trivial rejection. One of the most attractive features of this method is the fact that the frustum and OBB are left in their world coordinate orientations, thus
eliminating the need for expensive transformations and projections.
*/
/*-------------------------------------------------------------------------*/

/*
"Steven J. Haggerty" wrote:
>         Anyone know if there is a fast way to test if any part of a an
> axis-aligned 3D bounding box falls within a 3D sphere?

This is what I came up with after a few moments thought. I haven't tested
this at all, so don't be surprised if you find silly errors in it. The
method is simply to find the closest point sphere's centre that lies
inside the bounding box, then test whether the distance between that point
and the sphere's centre is less than the sphere's radius.

These definitions are assumed:

typedef struct
{
    float x1, y1, z1;   // Coordinates of the lower-left-back vertex.
    float x2, y2, z2;   // Coordinates of the upper-right-top vertex.
} bbox;

where x1 <= x2, y1 <= y2 and z1 <= z2; and

typedef struct
{
    float x, y, z;  // Coordinates of the sphere's center.
    float rad;      // The radius of the sphere.
} sphere;

Here's the code:

bool intersect(const bbox& b, const sphere& s)
{
    float sqrdist;

    if (b.x1 > s.x) {
        if (b.x1 > (s.x + s.rad)) return false;
        else sqrdist = sqr(b.x1 - s.x);
    }
    else if (b.x2 < s.x) {
        if (b.x2 < (s.x - s.rad)) return false;
        else sqrdist = sqr(b.x2 - s.x);
    }
    else sqrdist = 0;

    if (b.y1 > s.y) {
        if (b.y1 > (s.y + s.rad)) return false;
        else sqrdist += sqr(b.y1 - s.y);
    }
    else if (b.y2 < s.y) {
        if (b.y2 < (s.y - s.rad)) return false;
        else sqrdist += sqr(b.y2 - s.y);
    }

    if (b.z1 > s.z) {
        if (b.z1 > (s.z + s.rad)) return false;
        else sqrdist += sqr(b.z1 - s.z);
    }
    else if (b.z2 < s.z) {
        if (b.z2 < (s.z - s.rad)) return false;
        else sqrdist += sqr(b.z2 - s.z);
    }

    return sqrdist < sqr(s.rad);
}

Hope that helps. Feel free to mail me any questions.
Vil.
*/


// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 
