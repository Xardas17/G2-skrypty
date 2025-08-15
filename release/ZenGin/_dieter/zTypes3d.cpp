
#include <zTypes3D.h>

/*
>Does anyone know a way of adding 8bit packed RGB values together FAST,
>clipping the overflow for calculation of additive gouarud shade vertex
>values?

I believe there is a MMX instruction that will allow you to add packed
numbers with overflow clipping.  I don't know what it is.

If you're not using MMX, you can do this:

long int color1;
long int color2;
long int result;

result  = ((color1 & 0x00FF00FF) + (color2 & 0x00FF00FF)) & 0x00FF00FF;
result += ((color1 & 0xFF00FF00) + (color2 & 0xFF00FF00)) & 0xFF00FF00;
*/

/*
:     grayshade = (30% of red + 59% of green + 11% of blue).
:
: Use this instead of just averaging the r,g,b values.
: - Satish satishkumr@mailcity.com

Those numbers are no longer correct. They correspond to older CRT color
standards and don't look quite right on current monitors/TVs. I read a few
color FAQs and some other papers on the topic - I can give them to you if
you want to educate yourself (they are fairly technical, though; I
didn't bother to read everything). 

grey = 
  (pixel.red   * 0.2125) +
  (pixel.green * 0.7154) +
  (pixel.blue  * 0.0721);

Daniel
*/


// Script

zSTRING zCOLOR::GetDescription () const {
	return zSTRING(zSTRING(int(r)) + " " + 
				   zSTRING(int(g)) + " " +
				   zSTRING(int(b)) + " " +
				   zSTRING(int(alpha)));
};

void zCOLOR::SetByDescription (const zSTRING& desc) {
	r		= int(desc.PickWord_Old (1,"").ToInt());
	g		= int(desc.PickWord_Old (2,"").ToInt());
	b		= int(desc.PickWord_Old (3,"").ToInt());
	alpha	= int(desc.PickWord_Old (4,"").ToInt());
};

zSTRING zCOLOR::GetDescriptionRGB () const {
	return zSTRING(zSTRING(int(r)) + " " + 
				   zSTRING(int(g)) + " " +
				   zSTRING(int(b)));
};

// ====================================================================================================


int zTPlane::ClassifyPointBSPBuild (const zPOINT3& p) const {
//	const zDOUBLE ON_EPSILON = zDOUBLE(0.05F);
	const zDOUBLE ON_EPSILON = zDOUBLE(0.5F);
//	const zDOUBLE ON_EPSILON = zDOUBLE(0.25F);
	zDOUBLE dist = zDOUBLE(normal.n[VA])*zDOUBLE(p.n[VX]) + 
				   zDOUBLE(normal.n[VB])*zDOUBLE(p.n[VY]) + 
				   zDOUBLE(normal.n[VC])*zDOUBLE(p.n[VZ]) - zDOUBLE(distance);
 
	if(dist > ON_EPSILON)	return zPLANE_INFRONT; else  
	if(dist <-ON_EPSILON)	return zPLANE_BEHIND ; else 
							return zPLANE_ONPLANE;
};

zSTRING zTPlane::Print () const {
	zSTRING s = "("+
		zSTRING (normal.n[VX]) + " ; " +
		zSTRING (normal.n[VY]) + " ; " +
		zSTRING (normal.n[VZ]) + " ; " +
		zSTRING (distance)+")";
	return s;
};

void zTPlane::Calc (const zPOINT3& a, const zPOINT3& b, const zPOINT3& c) {
#ifdef _DEBUG
	if ( a==zVEC3(0,0,0) && b==zVEC3(0,0,0) && c==zVEC3(0,0,0) ) 
	{
		return;
	}
#endif

	zVEC4 p		= Alg_FindPlaneCoeff (a,b,c);
	normal		= zVEC3(p[0], p[1], p[2]);
	distance	= p[3];
};

void zTPlane::GetOriginUpRight (zPOINT3& vorigin, zPOINT3& vup, zPOINT3& vright) const {
	const zREAL BOGUS_RANGE= 18000; 
	int			i, x;
	zREAL		max, v;
	
	// find the major axis
	max = -BOGUS_RANGE;
	x	= -1;
	for (i=0 ; i<3; i++) {
		v = zAbs(normal.n[i]);
		if (v > max) {
			x   = i;
			max = v;
		}
	}
//	if (x==-1) zerr.Report (zERR_WARN,1000,"D: z3d(zTPlane::GetUpRight): no axis found");
		
	vup = zPOINT3 (0,0,0);
	switch (x) 	{
	case 0:
	case 1:
		vup[2] = 1;
		break;		
	case 2:
		vup[0] = 1;
		break;		
	};

	v		= vup * normal;						// v = DotProduct (vup, p->normal);
	vup		= vup + (-v * normal);				// VectorMA (vup, -v, p->normal, vup);, 
	vup.Normalize();							// VectorNormalize (vup);
	vright	= vup ^ normal;						// CrossProduct (vup, p->normal, vright);
	vright.Normalize();
	
	// meine Erweiterung ...
	// (FIXME: evtl. gibt die 'Major Axis' (x) Aussagen uber das folgende ....)
	// HILFE !!

/*	zREAL dot = normal*(zPOINT3(0,0,1));
	if ((dot)==0) {
		dot = normal*(zPOINT3(1,0,0));
		if ((dot)==0) {
			dot = normal*(zPOINT3(0,1,0));
			if ((dot)<=0.0) vright = -vright;
			else	        vup	   = -vup;
		} else {
			if ((dot)>=0.0) vright = -vright;
			else	       vup	   = -vup;
		};
	} else {
		if ((dot)<=0.0) vright = -vright;
		else			vup	   = -vup;
	};
*/

	/*
	zREAL dot;
	{
		dot = normal*(zPOINT3(0,0,1));
		if ((dot)<=0.0) vright = -vright;
		else			vup	   = -vup;
	};
	{
		dot = normal*(zPOINT3(0,1,0));
		if ((dot)>=0.0) vright = -vright;
		else	        vup	   = -vup;
	};
	{
		dot = normal*(zPOINT3(1,0,0));
		if ((dot)>=0.0) vright = -vright;
		else	       vup	   = -vup;
	};
*/
	vorigin	= distance * normal;
}; 

