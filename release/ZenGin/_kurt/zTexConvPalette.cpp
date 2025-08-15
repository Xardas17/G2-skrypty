//
// zTexConvPalette.cpp
//
//   palettenkonvertierungtool.
//   extra-file. der uebersichtlichkeit halber
//

#include "zcore.h" 
#include "zTexConvert.h"


typedef struct {	
	unsigned char b;
	unsigned char g;
	unsigned char r;
} tcPAL;

typedef struct {	
	float r;
	float g;
	float b;
} tcFPAL;

//
// eine palette generieren.
// (size wird in "zahl der pixel" angegeben)
#define maxPALSIZE 65536

//
// hier wird eine bitmap komplett an eine palette
// angepasst...
//
typedef struct {
	int c[3];
	float	v;
	float A;
} errTAB;

void tcConvertTexture(RGBPIXEL *src,unsigned char *dest,unsigned char *pal,int size)
{	
	int		t,r;
	int		palsize = 256;	// palettengroesse...
	float	minw,A,B;
	int		er,eg,eb;
	int		min,rr,gg,bb;
	tcPAL*	D = (tcPAL*) pal;
	errTAB	eT[256];
	//
	zERR_MESSAGE(10,0,"C: Convert RGB to Palette:"+zSTRING(size));

	B = 1.0f / 255.0f;

	for(t=0;t<256;t++){	
		eT[t].c[0] = (D[t].r>>2);
		eT[t].c[1] = (D[t].g>>2);
		eT[t].c[2] = (D[t].b>>2);
	}


	for(t=0;t<size;t++){	
		minw = 1000000;
		min = 0;
		//
		// und jetzt den farbfehler zu jedem paletteneintrag rechen, und
		// an der entsprechenden stelle speichern
		//
		rr = (src->r)>>2;
		gg = (src->g)>>2;
		bb = (src->b)>>2;
		for(r=0;r<palsize;r++) 	{	
			// 1. helligkeit rechnen
			er = (unsigned int)eT[r].c[0] - (unsigned int)rr;
			eg = (unsigned int)eT[r].c[1] - (unsigned int)gg;
			eb = (unsigned int)eT[r].c[2] - (unsigned int)bb;
			A = (float)(er*er)+(float)(eg*eg)+(float)(eb*eb);
			if(A <= minw){	
				minw = A;
				min = r;			// palettenfarbe auswaehlen...
			};
		}
		dest[t] = min;
		src++;						// naechsten kunden holen....
	}
}

#define MAXCOLOR	256
#define RED     	2
#define	GREEN		1
#define BLUE		0

struct box {
    int             r0;         /* min value, exclusive */
    int             r1;         /* max value, inclusive */
    int             g0;
    int             g1;
    int             b0;
    int             b1;
    int             vol;
};

/* Histogram is in elements 1..HISTSIZE along each axis,
  element 0 is for base or marginal value.
  NB: these must start out 0!	*/
#define BOX   33

zDWORD  wt[BOX][BOX][BOX],
		mr[BOX][BOX][BOX],
		mg[BOX][BOX][BOX],
		mb[BOX][BOX][BOX];

zREAL   m2[BOX][BOX][BOX];

int             ImageSize;           /* image size */
int             PalSize;             /* color look-up table size */

zWORD *Qadd;          // *must* be unsigned?
zBYTE *TrueColorPic;

/* build 3-D color histogram of counts, r/g/b, c^2 */
static void Hist3d(zDWORD  *vwt, zDWORD *vmr, zDWORD *vmg, zDWORD *vmb, zREAL *m_2)
{
    int		ind,r,g,b;
    int		inr,ing,inb,table[256];
    zDWORD  i;

    for (i = 0; i < 256; ++i) table[i] = i * i;

    for (i = 0; i < ImageSize; ++i) 
	{
		r = TrueColorPic[i*3  ];
		g = TrueColorPic[i*3+1];
		b = TrueColorPic[i*3+2];

		inr = (r >> 3) + 1;
		ing = (g >> 3) + 1;
		inb = (b >> 3) + 1;
		Qadd[i] = ind = (inr << 10) + (inr << 6) + inr + (ing << 5) + ing + inb;
		/* [inr][ing][inb] */
		++vwt[ind];
		vmr[ind] += r;
		vmg[ind] += g;
		vmb[ind] += b;
		m_2[ind] += (zREAL) (table[r] + table[g] + table[b]);
    }
}

/* We now convert histogram into moments so that we can rapidly calculate
   the sums of the above quantities over any desired box. */
static void Momt3d(zDWORD *vwt, zDWORD *vmr, zDWORD *vmg, zDWORD *vmb, zREAL *m_2)
{
    zWORD	ind1, ind2;
    zBYTE	i,r,g,b;
    zDWORD	line, line_r, line_g, line_b, area[BOX], area_r[BOX], area_g[BOX], area_b[BOX];
    zREAL	line2, area2[BOX];

    for (r = 1; r <= 32; ++r) 
	{
		for (i = 0; i <= 32; ++i)  area2[i] = 0.0F;
		for (i = 0; i <= 32; ++i)  area[i]  = area_r[i] = area_g[i] = area_b[i] = 0;

		for (g = 1; g <= 32; ++g) {

			line2 = 0.0F;
			line  = line_r = line_g = line_b = 0;

			for (b = 1; b <= 32; ++b) 
			{
				ind1 = (r << 10) + (r << 6) + r + (g << 5) + g + b;
				/* [r][g][b] */
				line		+= vwt[ind1];
				line_r		+= vmr[ind1];
				line_g		+= vmg[ind1];
				line_b		+= vmb[ind1];
				line2		+= m_2[ind1];
				area[b]		+= line;
				area_r[b]	+= line_r;
				area_g[b]	+= line_g;
				area_b[b]	+= line_b;
				area2[b]	+= line2;

				ind2 = ind1 - 1089; /* [r-1][g][b] */

				vwt[ind1] = vwt[ind2] + area[b];
				vmr[ind1] = vmr[ind2] + area_r[b];
				vmg[ind1] = vmg[ind2] + area_g[b];
				vmb[ind1] = vmb[ind2] + area_b[b];
				m_2[ind1] = m_2[ind2] + area2[b];
			}
		}
    }
}

static zDWORD Vol(struct box * cube, zDWORD mmt[BOX][BOX][BOX])
{
    return (mmt[cube->r1][cube->g1][cube->b1]
	    - mmt[cube->r1][cube->g1][cube->b0]
	    - mmt[cube->r1][cube->g0][cube->b1]
	    + mmt[cube->r1][cube->g0][cube->b0]
	    - mmt[cube->r0][cube->g1][cube->b1]
	    + mmt[cube->r0][cube->g1][cube->b0]
	    + mmt[cube->r0][cube->g0][cube->b1]
	    - mmt[cube->r0][cube->g0][cube->b0]);
}

static zDWORD Bottom(struct box * cube, zBYTE dir, zDWORD mmt[BOX][BOX][BOX])
{
    switch (dir) {
		case RED:
		return (-mmt[cube->r0][cube->g1][cube->b1]
			+ mmt[cube->r0][cube->g1][cube->b0]
			+ mmt[cube->r0][cube->g0][cube->b1]
			- mmt[cube->r0][cube->g0][cube->b0]);
		case GREEN:
		return (-mmt[cube->r1][cube->g0][cube->b1]
			+ mmt[cube->r1][cube->g0][cube->b0]
			+ mmt[cube->r0][cube->g0][cube->b1]
			- mmt[cube->r0][cube->g0][cube->b0]);
		case BLUE:
		return (-mmt[cube->r1][cube->g1][cube->b0]
			+ mmt[cube->r1][cube->g0][cube->b0]
			+ mmt[cube->r0][cube->g1][cube->b0]
			- mmt[cube->r0][cube->g0][cube->b0]);
    }
    zERR_FATAL("C: error in Bottom()");
    return 0;
}

static zDWORD Top(struct box * cube, zBYTE dir, int pos, zDWORD mmt[BOX][BOX][BOX])
{
    switch (dir) {
		case RED:
		return (mmt[pos][cube->g1][cube->b1]
			- mmt[pos][cube->g1][cube->b0]
			- mmt[pos][cube->g0][cube->b1]
			+ mmt[pos][cube->g0][cube->b0]);
		case GREEN:
		return (mmt[cube->r1][pos][cube->b1]
			- mmt[cube->r1][pos][cube->b0]
			- mmt[cube->r0][pos][cube->b1]
			+ mmt[cube->r0][pos][cube->b0]);
		case BLUE:
		return (mmt[cube->r1][cube->g1][pos]
			- mmt[cube->r1][cube->g0][pos]
			- mmt[cube->r0][cube->g1][pos]
			+ mmt[cube->r0][cube->g0][pos]);
    }
    zERR_FATAL("C: Top: error in Top()");
    return 0;
}


static zREAL Var(struct box * cube)
{
    zREAL dr,dg,db,xx;

    dr = zREAL( Vol(cube, mr) );
    dg = zREAL( Vol(cube, mg) );
    db = zREAL( Vol(cube, mb) );

    xx =  m2[cube->r1][cube->g1][cube->b1]
		- m2[cube->r1][cube->g1][cube->b0]
		- m2[cube->r1][cube->g0][cube->b1]
		+ m2[cube->r1][cube->g0][cube->b0]
		- m2[cube->r0][cube->g1][cube->b1]
		+ m2[cube->r0][cube->g1][cube->b0]
		+ m2[cube->r0][cube->g0][cube->b1]
		- m2[cube->r0][cube->g0][cube->b0];

    return (xx - (dr * dr + dg * dg + db * db) / (zREAL) Vol(cube, wt));
}

static zREAL Maximize(struct box* cube,	zBYTE dir,int first,int last, int*cut, zDWORD whole_r, zDWORD whole_g, zDWORD  whole_b, zDWORD whole_w)
{
    zDWORD half_r,half_g, half_b, half_w;
    zDWORD base_r,base_g, base_b, base_w;
    int    i;
    zREAL  temp,    max;

    base_r = Bottom(cube, dir, mr);
    base_g = Bottom(cube, dir, mg);
    base_b = Bottom(cube, dir, mb);
    base_w = Bottom(cube, dir, wt);
    max = 0.0;
    *cut = -1;
    for (i = first; i < last; ++i) 
	{
		half_r = base_r + Top(cube, dir, i, mr);
        half_g = base_g + Top(cube, dir, i, mg);
        half_b = base_b + Top(cube, dir, i, mb);
        half_w = base_w + Top(cube, dir, i, wt);
        // now half_x is sum over lower half of box, if split at i 
        if  (half_w == 0) continue; // subbox could be empty of pixels!  never split into an empty box 
        else temp = ((float) half_r * half_r + (float) half_g * half_g + (float) half_b * half_b) / half_w;

		half_r = whole_r - half_r;
        half_g = whole_g - half_g;
		half_b = whole_b - half_b;
        half_w = whole_w - half_w;
        if (half_w == 0) continue; // subbox could be empty of pixels! never split into an empty box
        else temp += ((float) half_r * half_r + (float) half_g * half_g + (float) half_b * half_b) / half_w;

        if (temp > max) 
		{
            max		= temp;
			*cut	= i;
		}
    }
    return (max);
}

static int Cut(struct box * set1, struct box * set2)
{
    zBYTE	dir;
    int		cutr,cutg,cutb;
	zREAL	maxr,maxg,maxb;
	zDWORD	whole_r, whole_g, whole_b, whole_w;

    whole_r = Vol(set1, mr);
    whole_g = Vol(set1, mg);
    whole_b = Vol(set1, mb);
    whole_w = Vol(set1, wt);

    maxr = Maximize(set1, RED,   set1->r0 + 1, set1->r1, &cutr, whole_r, whole_g, whole_b, whole_w);
    maxg = Maximize(set1, GREEN, set1->g0 + 1, set1->g1, &cutg, whole_r, whole_g, whole_b, whole_w);
    maxb = Maximize(set1, BLUE,  set1->b0 + 1, set1->b1, &cutb, whole_r, whole_g, whole_b, whole_w);

    if ((maxr >= maxg) && (maxr >= maxb)) 
	{
		dir = RED;
        if (cutr < 0) return 0;           /* can't split the box */
    } 
	else if ((maxg >= maxr) && (maxg >= maxb)) dir = GREEN;
    else dir = BLUE;

    set2->r1 = set1->r1;
    set2->g1 = set1->g1;
    set2->b1 = set1->b1;

    switch (dir) {
		case RED:
			set2->r0 = set1->r1 = cutr;
		set2->g0 = set1->g0;
			set2->b0 = set1->b0;
			break;
		case GREEN:
			set2->g0 = set1->g1 = cutg;
		set2->r0 = set1->r0;
			set2->b0 = set1->b0;
			break;
		case BLUE:
		set2->b0 = set1->b1 = cutb;
			set2->r0 = set1->r0;
			set2->g0 = set1->g0;
		break;
    }

    set1->vol = (set1->r1 - set1->r0) * (set1->g1 - set1->g0) * (set1->b1 - set1->b0);
    set2->vol = (set2->r1 - set2->r0) * (set2->g1 - set2->g0) * (set2->b1 - set2->b0);
    return 1;
}

static void  Mark(struct box * cube, int label, zBYTE *tag)
{
    int    r, g, b;
    for (r = cube->r0 + 1; r <= cube->r1; ++r)
	{
		for (g = cube->g0 + 1; g <= cube->g1; ++g)
		{
			for (b = cube->b0 + 1; b <= cube->b1; ++b)
			{
				tag[(r << 10) + (r << 6) + r + (g << 5) + g + b] = label;
			}
		}
	}
}

/* ----------------------------------------------------------------------
	
	tcCreatePalette()

	25.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void tcCreatePalette(RGBPIXEL *src,zBYTE *pal,int size)
{	

    struct box  cube[MAXCOLOR];
    zBYTE*		tag = 0;
    zREAL		vv[MAXCOLOR], temp = 0.0F;
    zDWORD		i = 0,  weight = 0;
    int			next = 0;
    int    		j = 0,k = 0,l = 0;

    // input R,G,B components into TrueColorPic;
    //   set ImageSize to width*height 
    TrueColorPic	= (zBYTE*)src;
    ImageSize		= size;
    PalSize			= 256;

    for (j=0;j<BOX;j++)
	{
		for (k=0;k<BOX;k++)
		{
			for (l=0;l<BOX;l++) {
				wt[j][k][l] = 0;
				mr[j][k][l] = 0;
				mg[j][k][l] = 0;
				mb[j][k][l] = 0;
				m2[j][k][l] = 0.;
			}
		}
	}

//    Qadd = (zWORD*)malloc(ImageSize * sizeof(zWORD));
    Qadd = zNEW_ARRAY(zWORD,ImageSize);
    
	if (!Qadd)	zERR_FATAL("C: tcCreatePalette: Not enough mem for *Qadd");

    Hist3d((zDWORD *)&wt, (zDWORD *)&mr, (zDWORD *)&mg, (zDWORD *)&mb, (zREAL *)&m2);
    Momt3d((zDWORD *)&wt, (zDWORD *)&mr, (zDWORD *)&mg, (zDWORD *)&mb, (zREAL *)&m2);

    cube[0].r0 = cube[0].g0 = cube[0].b0 = 0;
    cube[0].r1 = cube[0].g1 = cube[0].b1 = 32;
    next = 0;

    for (i = 1; i < PalSize; ++i) 
	{
		if (Cut(&cube[next], &cube[i])) 
		{
			vv[next] = (cube[next].vol > 1) ? Var(&cube[next]) : 0.0F;
			vv[i] = (cube[i].vol > 1) ? Var(&cube[i]) : 0.0F;
		} else {
			vv[next] = 0.0;
			i--;
		}
		next = 0;
		temp = vv[0];
		for (k = 1; k <= i; ++k)
		{
			if (vv[k] > temp) 
			{
				temp = vv[k];
				next = k;
			}
			if (temp <= 0.0) {
				PalSize = i + 1;
				break;
			}
		}
    }

    //tag = (zBYTE*)malloc(BOX * BOX * BOX);
    tag = zNEW_ARRAY(zBYTE,BOX * BOX * BOX);
    if (!tag)	zERR_FATAL("C: Not enough mem for *tag");

    for (k = 0; k < PalSize; ++k) 
	{
		Mark(&cube[k], k, tag);
		weight = Vol(&cube[k], wt);
		if (weight) 
		{
			pal[k*3+0] = (zBYTE) (Vol(&cube[k], mr) / weight) ;
			pal[k*3+2] = (zBYTE) (Vol(&cube[k], mb) / weight) ;
			pal[k*3+1] = (zBYTE) (Vol(&cube[k], mg) / weight) ;
		}
		else 
		{
			pal[k*3+0] =	pal[k*3+1] = pal[k*3+2] = 0;
		}
    }

	zERR_MESSAGE(10,0,"C: convert : ImageSize = %i\n" + zSTRING(ImageSize));

    //free(tag);
    //free(Qadd);
    delete[] tag;
    delete[] Qadd;
}

