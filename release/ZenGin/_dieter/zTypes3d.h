/******************************************************************************** 
 
     $Workfile:: zTypes3D.h           $                $Date:: 25.01.01 1:27    $
     $Revision:: 11                   $             $Modtime:: 25.01.01 1:01    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Common Types for 3D Render-Engine
   created       : 16.12.96

 * $Log: /current_work/zengin_work/_Dieter/zTypes3D.h $
 * 
 * 11    25.01.01 1:27 Hildebrandt
 * 
 * 10    4.12.00 16:49 Hildebrandt
 * 
 * 9     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 8     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 10    15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 8     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 6     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 5     16.11.99 19:50 Hildebrandt
 * 
 * 4     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 11 $ ($Modtime: 25.01.01 1:01 $)

#ifndef __ZTYPES3D_H__
#define __ZTYPES3D_H__

#ifndef __ZALGEBRA_H__
#include <zAlgebra.h>
#endif

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

///////////////////////
// 3D/Render specific
///////////////////////

// zVALUE: numeric-type for rendering-core
// noetig, um sich nicht von vorneherein völlig auf Fix/Floating-Point 
// festzulegen.
typedef double	zDOUBLE;
typedef zREAL	zVALUE;		// oder zCFIX, zFIX
typedef zVEC2	zPOINT2;
typedef zVEC3	zPOINT3;	
typedef zVEC4	zPOINT4;
typedef zMAT4	zMATRIX4;
typedef zREAL	zTIME;		// e.g. seconds, 1/18 secs, etc.

const zVALUE zVALUE_MIN = zREAL_MIN;
const zVALUE zVALUE_MAX = zREAL_MAX;

///////////////////////////////////////////////////////////////////////////
//     COLOR
///////////////////////////////////////////////////////////////////////////

struct zCOLOR { 
	union
	{
		struct
		{
			zBYTE	b,g,r,alpha;
		};
		zDWORD		dword;
	};

	zCOLOR ()										{};
	zCOLOR (zBYTE rr,zBYTE gg,zBYTE bb,zBYTE aa)	{ r=rr; g=gg; b=bb; alpha=aa;	};
	zCOLOR (zDWORD color)							{ dword = zDWORD(color);		};
	zCOLOR (int color)								{ dword = int(color);			};
//	zCOLOR (const zVEC3 &color)	/* range 0..255 */	{ r=zBYTE(zFloat2Int(color[0])); g=zBYTE(zFloat2Int(color[1])); b=zBYTE(zFloat2Int(color[2])); alpha=255; };

	void			Reset				()	{ r=g=b=0; alpha = 255;			};
	void			ResetToMax			()	{ r=g=b=alpha = 255;			};
	void			InvertRGB			()	{ r=255-r; g=255-g; b=255-b;	};
										
	void			SetRGB				(const zBYTE c)										{ r=g=b=c; };
	void			SetRGB				(const zBYTE rr , const zBYTE gg, const zBYTE bb)	{ r=rr; g=gg; b=bb; };
	void			SetRGBA				(const zBYTE rgb, const zBYTE a)					{ r=g=b=rgb; alpha=a; };
	void			SetRGBA				(const zBYTE rr , const zBYTE gg, const zBYTE bb, const zBYTE a) { r=rr; g=gg; b=bb; alpha=a; };
	void			SetRGB				(const zVEC3& col)									{ r=zBYTE(zFloat2Int(col[0])); g=zBYTE(zFloat2Int(col[1])); b=zBYTE(zFloat2Int(col[2])); };
										
	zBYTE			GetRedByte			() const			{ return r; };
	zBYTE			GetGreenByte		() const			{ return g; };
	zBYTE			GetBlueByte			() const			{ return b; };
	zBYTE			GetAlphaByte		() const			{ return alpha; };
															
	void			SetRedByte			(const zBYTE f)		{ r = f; };
	void			SetGreenByte		(const zBYTE f)		{ g = f; };
	void			SetBlueByte			(const zBYTE f)		{ b = f; };
	void			SetAlphaByte		(const zBYTE f)		{ alpha = f; };
										
	zREAL			GetRedFloat			() const			{ return (float(r) / 255 ); };
	zREAL			GetGreenFloat		() const			{ return (float(g) / 255 ); };
	zREAL			GetBlueFloat		() const			{ return (float(b) / 255 ); };
	zREAL			GetAlphaFloat		() const			{ return (float(alpha) / 255 ); };
										
	void			SetRedFloat			(const zREAL f)	{ r		= zBYTE(zFloat2Int(f*zREAL(255.0F))); };
	void			SetGreenFloat		(const zREAL f)	{ g		= zBYTE(zFloat2Int(f*zREAL(255.0F))); };
	void			SetBlueFloat		(const zREAL f)	{ b		= zBYTE(zFloat2Int(f*zREAL(255.0F))); };
	void			SetAlphaFloat		(const zREAL f)	{ alpha = zBYTE(zFloat2Int(f*zREAL(255.0F))); };
					
	zREAL			GetIntensityFloat	() const			{ return (0.299F)*float(r)+(0.587F)*float(g)+(0.114F)*float(b); };
	zBYTE			GetIntensityByte	() const			{ return ((77)*(r)+(150)*(g)+(29)*(b)) >> 8; };

	inline	zDWORD	GetPackedDWord		() const			{ return dword;			};
	inline  zVEC3	GetVEC3				() const			{ return zVEC3(r,g,b);	};	/* range 0..255 */

					operator int		()					{ return int(dword);	};
					operator zDWORD		()					{ return dword;			};

	inline void		LerpRGB				(const int intScale, const zCOLOR col1, const zCOLOR col2);		// intScale = 0..255
	inline void		LerpRGBA			(const int intScale, const zCOLOR col1, const zCOLOR col2);
	inline void		AddRGB				(const zCOLOR& p);
	inline void		AddRGB				(const int pr, const int pg, const int pb);
	inline void		AddRGBApprox		(const zCOLOR& p);
	inline void		AddRGBAApprox		(const zCOLOR& p);
	inline void		MulRGB				(const zCOLOR& a);

	// Script
	zSTRING			GetDescription		() const;
	void			SetByDescription	(const zSTRING& desc);
	zSTRING			GetDescriptionRGB	() const;

	// friends
	friend zCOLOR operator + (const zCOLOR& a, const zCOLOR& b);
	friend zCOLOR operator - (const zCOLOR& a, const zCOLOR& b);
	friend zCOLOR operator * (const zCOLOR& a, const zCOLOR& b);	// 128*128=64, (0.5*0.5=0.25)
	friend zCOLOR operator * (const zCOLOR& a, const int val);		// 128*128=64, (0.5*0.5=0.25)

	zCOLOR operator + (const zCOLOR& add) {
		int rr = int (r) + int (add.r); if (rr>255) rr=255;
		int gg = int (g) + int (add.g); if (gg>255) gg=255;
		int bb = int (b) + int (add.b); if (bb>255) bb=255;
		int aa = int (alpha) + int (add.alpha); if (aa>255) aa=255;
		return zCOLOR(rr,gg,bb,aa); 
	};

	zCOLOR operator - (const zCOLOR& minus) {
		return zCOLOR(r-minus.r, g-minus.g, b-minus.b, alpha-minus.alpha); 
	};

	zCOLOR operator * (const int val) {
		return zCOLOR( zBYTE((int(r)	*val)>>8),
					   zBYTE((int(g)	*val)>>8),
					   zBYTE((int(b)	*val)>>8),
					   zBYTE((int(alpha)*val)>>8));
	};

	zCOLOR operator * (const zCOLOR& mul) {
		return zCOLOR( zBYTE((int(mul.r)		* int(r))>>8),
					   zBYTE((int(mul.g)		* int(g))>>8),
					   zBYTE((int(mul.b)		* int(b))>>8),
					   zBYTE((int(mul.alpha)	* int(alpha))>>8));
};


};


// inlines

void zCOLOR::LerpRGB (const int intScale, const zCOLOR col1, const zCOLOR col2) {
	// intScale = 0..255
	r = int(col1.r) + (((int(col2.r) - int(col1.r)) * intScale) >> 8);
	g = int(col1.g) + (((int(col2.g) - int(col1.g)) * intScale) >> 8);
	b = int(col1.b) + (((int(col2.b) - int(col1.b)) * intScale) >> 8);
};

void zCOLOR::LerpRGBA (const int intScale, const zCOLOR col1, const zCOLOR col2) {
	// intScale = 0..255
	r		= int(col1.r		) + (((int(col2.r		) - int(col1.r		)) * intScale) >> 8);
	g		= int(col1.g		) + (((int(col2.g		) - int(col1.g		)) * intScale) >> 8);
	b		= int(col1.b		) + (((int(col2.b		) - int(col1.b		)) * intScale) >> 8);
	alpha	= int(col1.alpha	) + (((int(col2.alpha	) - int(col1.alpha	)) * intScale) >> 8);
};

void zCOLOR::AddRGB (const zCOLOR& p) {
	int rr = int (r) + int (p.r); if (rr>255) r=255; else r = rr;
	int gg = int (g) + int (p.g); if (gg>255) g=255; else g = gg;
	int bb = int (b) + int (p.b); if (bb>255) b=255; else b = bb;
};

void zCOLOR::AddRGB	(const int pr, const int pg, const int pb) {
	int rr = int (r) + int (pr); if (rr>255) r=255; else r = rr;
	int gg = int (g) + int (pg); if (gg>255) g=255; else g = gg;
	int bb = int (b) + int (pb); if (bb>255) b=255; else b = bb;
};

void zCOLOR::AddRGBApprox (const zCOLOR& p) {
		  zDWORD* const c1	= (zDWORD*)this;
	const zDWORD* const c2	= (zDWORD*)(&p);
	zDWORD res, overflow;
	res			= ((*c1)&0xFEFEFF) + ((*c2)&0xFEFEFF);
	overflow	= res&0x1010100;
	overflow	= overflow-(overflow>>8);	
	*c1			= res | overflow;
};

void zCOLOR::AddRGBAApprox (const zCOLOR& p) {
	// FIXME, ATT: MSDEV dependent
	__int64 c1	= (__int64)this;
	__int64 c2	= (__int64)&p;
	__int64 res, overflow;
	res			= ((c1)&0xFEFEFEFF) + ((c2)&0xFEFEFEFF);
	overflow	= res&0x1001010100;
	overflow	= overflow-(overflow>>8);	
	*((zDWORD*)this)= zDWORD(res | overflow);
};

void zCOLOR::MulRGB (const zCOLOR& a) {
	r	= zBYTE((int(r) * int(a.r))>>8);
	g	= zBYTE((int(g) * int(a.g))>>8);
	b	= zBYTE((int(b) * int(a.b))>>8);
};


///////////////////////////////////////////////////////////////////////////
//     PLANE
///////////////////////////////////////////////////////////////////////////

enum zTPlaneClass { zPLANE_INFRONT, zPLANE_BEHIND, zPLANE_ONPLANE, zPLANE_SPANNING };
const zDOUBLE zEPSILON = zDOUBLE(0.001);

struct zTPlane 
{
	zREAL		distance;
	zPOINT3		normal;
	
	int					ClassifyPointBSPBuild	(const zPOINT3& p) const;
	inline zPOINT3		ProjectOntoPlane		(const zPOINT3& p) const	{ return p - ((p*normal - distance) * normal);	};
	inline zREAL		GetDistanceToPlane		(const zPOINT3& p) const	{ return (p*normal - distance);					};
	zSTRING				Print					() const;
	void				GetOriginUpRight		(zPOINT3& vorigin, zPOINT3& vup, zPOINT3& vright) const;
	void				Calc					(const zPOINT3& a, const zPOINT3& b, const zPOINT3& c);

	inline int CalcSignbits () const 
	{
		int r;
		r  = int((normal[VX]<0) ? 0:1);
		r += int((normal[VY]<0) ? 0:1)<<1;
		r += int((normal[VZ]<0) ? 0:1)<<2;
		return r;
	};

	inline zBOOL EqualTo (const zTPlane& p2, const zREAL tolerance) const 
	{
		return ((zAbs((distance)-(p2.distance))				<= tolerance) && 
				(zAbs(((normal) -(p2.normal)).Length2())	<= tolerance));
	};

	int operator == (const zTPlane& p2) const {
		return ((distance==p2.distance) && (normal==p2.normal));
	};

	int Opposite (const zTPlane& p2) const 
	{
		zREAL dot = (normal * p2.normal);
		return (dot<=zREAL(0.0F));
	};

	int ClassifyPoint (const zPOINT3& p) const 
	{
		const zDOUBLE ON_EPSILON = zDOUBLE(0.001F);
		zDOUBLE dist = zDOUBLE(normal.n[VA])*zDOUBLE(p.n[VX]) + 
					   zDOUBLE(normal.n[VB])*zDOUBLE(p.n[VY]) + 
					   zDOUBLE(normal.n[VC])*zDOUBLE(p.n[VZ]) - zDOUBLE(distance);
 
		if(dist > ON_EPSILON)	return zPLANE_INFRONT; else  
		if(dist <-ON_EPSILON)	return zPLANE_BEHIND ; else 
								return zPLANE_ONPLANE;
	};

	zBOOL Intersection (const zPOINT3& rayOrg, const zPOINT3& ray, zPOINT3& inters) const 
	{
		zREAL dn, alpha;
		dn		= ray*normal;
		if (dn==0) return FALSE;													// parallel ?
		// Achtung: dn ist hier NICHT negativ !
		// FIXME: division durch dn erst *nach* dem alpha-test
		alpha	= (distance - (normal * rayOrg)) / dn;
		if ((alpha<0) || (alpha>1)) return FALSE;									// vor/hinter Betrachter ?
		inters	= rayOrg + alpha*ray;
		return TRUE;
	};


	/*zBOOL Intersection (const zPOINT3& rayOrg, const zPOINT3& ray, zPOINT3& inters) const 
	{
		zREAL dn, alpha;
		dn		= ray*normal;
		if (dn==0) return FALSE;													// parallel ?
		// Achtung: dn ist hier NICHT negativ !

		alpha	= (distance - (normal * rayOrg));
		if ((alpha<0) || (alpha>dn)) return FALSE;									// vor/hinter Betrachter ?
		alpha = alpha/dn;
		inters	= rayOrg + alpha*ray;
		return TRUE;
	};*/

	zBOOL IntersectionFront (const zPOINT3& rayOrg, const zPOINT3& ray, zPOINT3& inters) const 
	{
		// Erledigt auf der Plane ein implizites Backface-Culling
		// => Ein Ray kann die Plane nur von vorne durchdringen !
		zREAL dn, alpha;
		dn		= ray*normal;
		if (dn>=0) return FALSE;													// parallel oder backface ? 
		// FIXME: division durch dn erst *nach* dem alpha-test
	//	alpha	= (distance - (normal * rayOrg)) / dn;
	//	if ((alpha<0) || (alpha>1)) return FALSE;									// vor/hinter Betrachter ?
		alpha	= (distance - (normal * rayOrg));
		if ((alpha>0) || (alpha<dn)) return FALSE;									// vor/hinter Betrachter ?
		alpha	= alpha / dn;
		inters	= rayOrg + alpha*ray;
		return TRUE;
	};

};



#endif