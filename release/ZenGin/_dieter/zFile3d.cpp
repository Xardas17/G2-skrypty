/******************************************************************************** 
 
     $Workfile:: zFile3d.cpp          $                $Date:: 31.01.01 5:42    $
     $Revision:: 19                   $             $Modtime:: 31.01.01 5:42    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:
 
 * $Log: /current_work/zengin_work/_Dieter/zFile3d.cpp $
 * 
 * 19    31.01.01 5:42 Hildebrandt
 * 
 * 18    27.01.01 19:42 Moos
 * 
 * 17    22.11.00 19:55 Speckels
 * 
 * 16    22.11.00 19:20 Speckels
 * 
 * 15    22.11.00 18:05 Speckels
 * 
 * 14    3.11.00 18:38 Hildebrandt
 * 
 * 13    21.09.00 15:45 Hoeller
 * 
 * 12    21.09.00 0:47 Rueve
 * inteldröhnung
 * 
 * 11    11.09.00 19:40 Speckels
 * 
 * 10    21.08.00 17:18 Hildebrandt
 * 
 * 9     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 8     21.07.00 14:28 Hildebrandt
 * 
 * 7     6.07.00 13:35 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 11    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 10    19.02.00 18:53 Hildebrandt
 * 
 * 9     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 7     14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 6     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 5     13.11.99 1:10 Hildebrandt
 * 
 * 4     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 19 $ ($Modtime: 31.01.01 5:42 $)


/*
- es werden ja doppelte vertices gesucht:
  wird dadurch eventuell mehr vereinfacht, als darf ??
*/

/*
- noch fehlende Funktionalitaeten:	
	- zCFileBin nested/rekursiv machen (aehnlich der 3DS Struktur)

- Kommentare:
	- Idee hinter der Klasse Cf3d_File:
	  Alle möglichen 3d-File Formate werden hier zusammengefasst und gekapselt.
	- mögliche zukünftige, zu unterstützende Formate:
	  - 3D-Studio
	  - Quake CSG-Format
	  - eigenes Binär-Format
	  - eigenes CSG-Format (Text?)
	-
		// 1. alle Objekte in 1 Mesh (test, 3dModel)
		// 2. pro Objekt neues Mesh  (3dModel)
		// 3. file=1 Objekt, als static Level in World einfügen ("mergen") (auf Meshes verteilen)
		//
		// wichtig: alle Loads in World/Mesh sind "Merge"-Operationen, 
		// => World/Mesh wird nicht initialisiert, aber auch nicht gelöscht/überschrieben
*/

/* --------------------------- 3DSRDR.C -------------------------------
    .3DS file format exerciser v1.2. Written by Javier Arevalo, AKA Jare/Iguana.

	Heavily based on info on the file 3DS_08.TXT by Jim Pitts
      (jp5@ukc.ac.uk)

    Basic material-related stuff digged up by Jare. 
    Track info stuff too.

    Thanks to the Egerter brothers of WGT fame and to Walken/Impact studios
        for extra info, Rex Deathstar for support. And definitely to
        Xanthome/Darkzone for you know why. And of course, respect to
        Avatar/Legend Design for being here before all of us.

    For a cool example of actual reading of 3DS files, look no
        further than 3DSCO20.ZIP by Mats Byggmastar aka. MRI. I
        personally prefer using a table-driven modification of this
        code, but both approaches are quite ok and his is much faster
        to write and follow.

    Now only lack is someone to explain how to make use of all this
        stuff i.e. how exactly is data stored, how spline interpolations
        are performed, what are those things called quaternions, etc. And
        also, maybe, dig the rest of the chunks until we are actually able
        to write 3DS files instead of just being bored reading. There's
        lots to do.

    If you decide to work on this further, please make your findings
        public like we have already done, ok? Upload it to
        x2ftp.oulu.fi, THE place for programming info, and/or to
        ftp.cdrom.com. But please PUBLISH it!

    - Change log -

    V 1.2:
        - Added change log to have some idea what's going on.
        - Added pivot point reading inside tracks stuff.
        - Info about spline flags on keyframes.
        - Added face edge visibility info.
        - Finally!! Those flags that mark when the texture is wrapping
          around inside a face. This happens when you apply spherical
          or cylindrical coordinates, the faces along the 0§ axis don't
          get proper mapping coords. Someone describe how to fix this?
        - Added -quiet parm, only displays minimal chunk info.
        - Object parent number is stored in CHUNK_TRACKOBJNAME.
          This makes reference to the node number in CHUNK_OBJNUMBER.
        - Object number changed to unsigned. Parent 65535 means none.
        - Added CHUNK_PRJ and CHUNK_MLI to allow inspecting .PRJ and
          .MLI files (they're basically the same chunks as .3DS).
        - Added banner to identify myself, and disclaimer for "just in
          case" possibilities.
        - Corrected possible bug when chunklen == 0 (it was not a
          chunk).
        - Added several name descriptions of chunks. Use diff to find
          all the new chunks.
*/

//
#include <zCore.h>
#include <zFile3d.h>
#include <zVisual.h>
#include <zoption.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

struct TVertex3ds {
	zPOINT3		position;
	zPOINT2		texCoord;
	zWORD		lastObjHasBeenWrittenTo;			// save: vert fuer dieses Objekt bereits geschrieben worden ?
	zWORD		remappedIndex;						// save: wenn Mesh in mehrere Objekte gesplittet werden muss, dann muessen auch die VertIndices remapped werden
	int			mappedIndex;
	int			leafIndex;
	TVertex3ds() {
		texCoord				= zVEC2(0);
		lastObjHasBeenWrittenTo = 0;
		remappedIndex			= 0;
		mappedIndex				= 0;
		leafIndex				= 0;
	};
};

struct TPoly3ds {
	int			vertIndex[3];
	zCMaterial	*material;
	zBOOL		wrapu;
	zBOOL		wrapv;
	zWORD		flags;
	void CheckForWrap ();
	TPoly3ds() {
		vertIndex[0]=vertIndex[1]=vertIndex[2]=0;
		material = 0;
	};
};

struct TColor {
	zBYTE		r,g,b;
};


static int Compare_Verts3DS(const void *arg1, const void *arg2) 
{
	const zVALUE	VERT_EPS				= zREAL(0.1F);
	const zVALUE	UV_EPS					= zREAL(0.001F);

	const zVEC3		p1						= (*((TVertex3ds*)arg1)).position;
	const zVEC3		p2						= (*((TVertex3ds*)arg2)).position;
	const zVEC2		uv1						= (*((TVertex3ds*)arg1)).texCoord;
	const zVEC2		uv2						= (*((TVertex3ds*)arg2)).texCoord;
	const int		leafIndex1				= (*((TVertex3ds*)arg1)).leafIndex;
	const int		leafIndex2				= (*((TVertex3ds*)arg2)).leafIndex;

	const zREAL		p1x						= p1.n[VX];
	const zREAL		p1y						= p1.n[VY];
	const zREAL		p1z						= p1.n[VZ]; 
	const zREAL		p2x						= p2.n[VX]; 
	const zREAL		p2y						= p2.n[VY]; 
	const zREAL		p2z						= p2.n[VZ]; 
	const zREAL		uv1x					= uv1.n[VX];
	const zREAL		uv1y					= uv1.n[VY];
	const zREAL		uv2x					= uv2.n[VX];
	const zREAL		uv2y					= uv2.n[VY];


	// erster test auf gleichheit
	if (leafIndex1 == leafIndex2)
	if ( ( zAbs(p1x-p2x)	< VERT_EPS	)		&&
		 ( zAbs(p1y-p2y)	< VERT_EPS	)		&&
		 ( zAbs(p1z-p2z)	< VERT_EPS	)		&&
		 ( zAbs(uv1x-uv2x)	< UV_EPS	)		&&
		 ( zAbs(uv1y-uv2y)	< UV_EPS	) )
	{
		return 0;
	}


	if		( (p1x-p2x) < 0 ) return -1;
	else if ( (p1x-p2x) > 0 ) return +1;
	else 
	{
		// die x koords sind gleich, dann die y coords vergleichen
		if		( (p1y-p2y) < 0 ) return -1;
		else if ( (p1y-p2y) > 0 ) return +1;
		else
		{
			// die x und die y coords sind gleich, z vergleichen
			if		( (p1z-p2z) < 0 ) return -1;
			else if ( (p1z-p2z) > 0 ) return +1;
			else
			{
				// alle koords gleich, uv mappings können aber unterschiedlich sein
				if		((uv1x-uv2x)<0) return -1;
				else if	((uv1x-uv2x)>0) return +1;
				else
				{
					// alle koords gleich, uv mappings können aber unterschiedlich sein
					if		((uv1y-uv2y)<0) return -1;
					else if	((uv1y-uv2y)>0) return +1;
				}
			}
		}
	}

	zERR_WARNING("C: Compare_Verts3DS: Bug! Should be never here!");
	// hier darf man niemals hinkommen
	return 0;
}




static zCMesh			*targetMesh;
static TVertex3ds		*vertList;
static TPoly3ds			*polyList;
static int				numVert;
static int				numPoly;

static zCMaterial		*actMat;
static zCOLOR			*actColor;
static zCOLOR			dummyCol;

static const float SCALE = 1.0;				// vert-scale, 16.0 sonst

static const int NNX = 0;		// 0,2,1 für original 3ds
static const int NNY = 2;		// 0,1,2 für z.B. Landscape
static const int NNZ = 1;

#if 0
	inline void Print (int ind, const zSTRING& s) {	zerr.Message (Spaces(ind)+s);	};
#else
	inline void Print (int ind, const zSTRING& s) {};
#endif

//zSTRING TEX_NAME("default.tga");

//-------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#ifndef PI
#define PI 3.141592687
#endif
 
typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

typedef signed char  sbyte;
typedef signed short sword; 
typedef signed long  sdword;

#pragma pack(push,2)

typedef struct {
    word    id;
    dword   len;
} TChunkHeader, *PChunkHeader;

#pragma pack(pop)

enum {
	CHUNK_M3DVERS	= 0x0002,
    CHUNK_RGBF      = 0x0010,
    CHUNK_RGBB      = 0x0011,
    CHUNK_RGBB2     = 0x0012,       // ?? NOT HLS.

    CHUNK_SHORTPERC = 0x0030,

    CHUNK_PRJ       = 0xC23D,
    CHUNK_MLI       = 0x3DAA,

    CHUNK_MAIN      = 0x4D4D,
        CHUNK_OBJMESH   = 0x3D3D,
            CHUNK_MESHVERS  = 0x3D3E,				// NEU
			// hier die Material-Enum
		    CHUNK_MSTRSCALE = 0x0100,				// NEU
            CHUNK_BKGCOLOR  = 0x1200,
            CHUNK_AMBCOLOR  = 0x2100,
            CHUNK_OBJBLOCK  = 0x4000,
                CHUNK_TRIMESH   = 0x4100,
                    CHUNK_VERTLIST  = 0x4110,
                    CHUNK_FACELIST  = 0x4120,
                    CHUNK_FACEMAT   = 0x4130,
                    CHUNK_MAPLIST   = 0x4140,
					CHUNK_TEXINFO	= 0x4170,
                    CHUNK_SMOOLIST  = 0x4150,
                    CHUNK_TRMATRIX  = 0x4160,
                CHUNK_LIGHT     = 0x4600,
                    CHUNK_SPOTLIGHT = 0x4610,
                CHUNK_CAMERA    = 0x4700,
                CHUNK_HIERARCHY = 0x4F00,
        CHUNK_VIEWPORT  = 0x7001,
        CHUNK_MATERIAL  = 0xAFFF,
            CHUNK_MATNAME   = 0xA000,
            CHUNK_AMBIENT   = 0xA010,
            CHUNK_DIFFUSE   = 0xA020,
            CHUNK_SPECULAR  = 0xA030,
            CHUNK_SHININESS = 0xA040,				// NEU
            CHUNK_SHIN2PCT	= 0xA041,				// NEU
            CHUNK_TRANSP	= 0xA050,				// NEU
            CHUNK_SHADING	= 0xA100,				// NEU
            CHUNK_TEXTURE   = 0xA200,
				// CHUNK_SHORTPERC					// TextureMap strength
	            CHUNK_MAPFILE   = 0xA300,			// 8+3
				CHUNK_MAPTILING	= 0xA351,
				CHUNK_MAPTEXBLUR= 0xA353,
            CHUNK_BUMPMAP   = 0xA230,

        CHUNK_KEYFRAMER = 0xB000,
            CHUNK_AMBIENTKEY    = 0xB001,
            CHUNK_TRACKINFO = 0xB002,
                CHUNK_TRACKOBJNAME  = 0xB010,
                CHUNK_TRACKPIVOT    = 0xB013,
                CHUNK_TRACKPOS      = 0xB020,
                CHUNK_TRACKROTATE   = 0xB021,
                CHUNK_TRACKSCALE    = 0xB022,
                CHUNK_OBJNUMBER     = 0xB030,
            CHUNK_TRACKCAMERA = 0xB003,
                CHUNK_TRACKFOV  = 0xB023,
                CHUNK_TRACKROLL = 0xB024,
            CHUNK_TRACKCAMTGT = 0xB004,
            CHUNK_TRACKLIGHT  = 0xB005,
            CHUNK_TRACKLIGTGT = 0xB006,
            CHUNK_TRACKSPOTL  = 0xB007,
            CHUNK_FRAMES    = 0xB008,
};

// ------------------------------------

void TPoly3ds :: CheckForWrap () {
	return;

	const int u=0;
	const int v=1;
	zPOINT2& tex0 = vertList[vertIndex[0]].texCoord;
	zPOINT2& tex1 = vertList[vertIndex[1]].texCoord;
	zPOINT2& tex2 = vertList[vertIndex[2]].texCoord;
	float d; 
//	wrapu=wrapv=TRUE;
	if (wrapu) { 
		float maxu,minu; 
		maxu = minu = tex0[u]; //tv[0].u; 
		
		if (tex1[u]>maxu) maxu = tex1[u]; else
		if (tex1[u]<minu) minu = tex1[u]; 
		if (tex2[u]>maxu) maxu = tex2[u]; else
		if (tex2[u]<minu) minu = tex2[u]; 
		if ((maxu-minu)>0.8) { 
			d = ceil(maxu-minu); 
			if (tex0[u]<.5) tex0[u] += d; 
			if (tex1[u]<.5) tex1[u] += d; 
			if (tex2[u]<.5) tex2[u] += d;
		} 
	} 
	if (wrapv) { 
		float maxv,minv; 
		maxv = minv = tex0[v]; 
		if (tex1[v]>maxv) maxv = tex1[v]; else 
		if (tex1[v]<minv) minv = tex1[v];
		if (tex2[v]>maxv) maxv = tex2[v]; else
		if (tex2[v]<minv) minv = tex2[v]; 
		if ((maxv-minv)>0.8) { 
			d = ceil(maxv-minv); 
			if (tex0[v]<.5) tex0[v] += d; 
			if (tex1[v]<.5) tex1[v] += d; 
			if (tex2[v]<.5) tex2[v] += d; 
		} 
	} 
};

// ------------------------------------

    // Forward declaration.
static void ChunkReader(zFILE *f, int ind, long p);

static void SkipReader(zFILE *f, int ind, long p) {
}

static void VersionReader (zFILE *f, int ind, long p) {
	long v;
	if (f->Read(&v, sizeof(v)) <=0) return;
//	Print ("%*sVersion: %d", ind, "", v);
	Print (ind, "Version: "+zSTRING(v));
}

static void RGBFReader (zFILE *f, int ind, long p) {
    float c[3];
    if (f->Read(&c, sizeof(c)) <=0) return;
    //printf("%*s    Red: %f, Green: %f, Blue: %f", ind, "", c[0], c[1], c[2]);
}

static void RGBBReader (zFILE *f, int ind, long p) {
    byte c[3];
    if (f->Read(&c, sizeof(c)) <=0) return;
//	Print ("%*s    Red: %d, Green: %d, Blue: %d", ind, "", c[0], c[1], c[2]);
	Print (ind, "RGB: "+zSTRING(c[0])+","+zSTRING(c[1])+","+zSTRING(c[2]));

	// ----------ENGINE---------------------------------- 
	actColor->r = c[0];
	actColor->g = c[1];
	actColor->b = c[2];
}

static zSTRING ASCIIZReader (zFILE *f, int ind, long p) {
    char	c;
	zSTRING s;
	s.Clear();

    // Read ASCIIZ name
    while ( (f->Read (&c, sizeof(c))>0) && c != '\0') 
//	while ( (f->Read (&c, sizeof(c))) != EOF && c != '\0')
//	while ( (c = fgetc(f)) != EOF && c != '\0')
	{ 
		s = s + zSTRING(char(c));
	};
	return s;
}

// ----------ENGINE---------------------------------- BEGIN
static void AmbColReader (zFILE *f, int ind, long p) {
	//actColor = &(actMat->color);
	actColor = &dummyCol;
    ChunkReader(f, ind, p);
}

static void DiffColReader (zFILE *f, int ind, long p) {
	actColor = &(actMat->color);
    ChunkReader(f, ind, p);
}

static void SpecColReader (zFILE *f, int ind, long p) {
	actColor = &dummyCol;
    ChunkReader(f, ind, p);
}

void FlushMeshBuffer();

// ----------ENGINE---------------------------------- END

static void ObjBlockReader (zFILE *f, int ind, long p) {
	// create New Object
	FlushMeshBuffer();

	// Read ASCIIZ object name
    zSTRING s = ASCIIZReader(f, ind, p);
//	Print ("%*sObject name \"%s\"", ind, "", s.ToChar());
	Print (ind, "Object name: "+s);
    // Read rest of chunks inside this one.
    ChunkReader(f, ind, p);
}

static void VertListReader (zFILE *f, int ind, long p) {
    word nv;
    float c[3];

    if (f->Read(&nv, sizeof(nv)) <=0) return;
//	Print ("%*sVertices: %d", ind, "", nv);
	Print (ind, "numVert:  "+zSTRING(nv));
	// ----------ENGINE----------------------------------
	numVert  = nv;
	vertList = zNEW(TVertex3ds) [numVert];
	nv		 = 0;
    while (nv < numVert) {
        if (f->Read(&c, sizeof(c)) <=0) return;
//		Print ("%*s    X: %f, Y: %f, Z: %f", ind, "", c[0], c[1], c[2]);
		vertList[nv].position.n[0]	= (zVALUE)(c[NNX]);
		vertList[nv].position.n[1]	= (zVALUE)(c[NNY]);
		vertList[nv].position.n[2]	= (zVALUE)(c[NNZ]);
		vertList[nv].texCoord		= zVEC2(0.0F,0.0F);
		nv++;
    }
}

static void FaceListReader (zFILE *f, int ind, long p) {
    word nv;
    word c[3];
    word flags;

    if (f->Read(&nv, sizeof(nv)) <=0) return;
//	Print ("%*sFaces: %d", ind, "", nv);
	Print (ind, "numTris: "+zSTRING(nv));
	// ----------ENGINE----------------------------------
	numPoly  = nv;
	polyList = zNEW(TPoly3ds) [numPoly];
	nv = 0;
    while (nv < numPoly) {
        if (f->Read(&c, sizeof(c)) <=0) return;
        if (f->Read(&flags, sizeof(flags)) <=0) return;
        //Print ("%*s  A %d, B %d, C %d, 0x%X:", ind, "", c[0], c[1], c[2], flags);
//        printf("%*s    AB: %d, BC: %d, CA: %d, UWrap %d, VWrap %d",
//               ind, "",
//        Print (" AB %d BC %d CA %d UWrap %d VWrap %d",
//               (flags & 0x04) != 0, (flags & 0x02) != 0, (flags & 0x01) != 0,
//               (flags & 0x08) != 0, (flags & 0x10) != 0);
		for (int i=0; i<3; i++) 
		{
			if (c[i]>=numVert)
			{
				zERR_FAULT ("D: zFile3DS(FaceListReader): FILE CORRUPT, face has index to non-existant vertex index: "+zSTRING(c[i])+", numVert: "+zSTRING(numVert));
				c[i]=0;
			};
		};

		polyList[nv].vertIndex[0] = c[0];
		polyList[nv].vertIndex[1] = c[1];
		polyList[nv].vertIndex[2] = c[2];
		polyList[nv].material	  = 0;
		polyList[nv].wrapu		  = (flags & 0x08) !=0;
		polyList[nv].wrapv		  = (flags & 0x10) !=0;
		nv++;
    }
    // Read rest of chunks inside this one.
    ChunkReader(f, ind, p);
}

static void FaceMatReader (zFILE *f, int ind, long p) {
    word n, nf;

	// ----------ENGINE----------------------------------

    // Read ASCIIZ material name
    zSTRING s = ASCIIZReader(f, ind, p);
//zerr.Message (" mat: "+s);
//	Print ("%*sMaterial name for faces: \"%s\"", ind, "", s.ToChar());
	Print (ind, "Material name for faces: "+s);
	s.Upper();
	actMat = zCMaterial :: SearchName (s);
	if (actMat==0) 
		zERR_FATAL ("D: File3d.FaceMatReader: ! noper !");

    if (f->Read(&n, sizeof(n)) <=0) return;
    // printf("%*sFaces with this material: %d", ind, "", n);
    while (n-- > 0) {
        if (f->Read(&nf, sizeof(nf)) <=0) return;
        // printf("%*s    Face %d", ind, "", nf);
		if (nf>=numPoly) {
			zERR_FAULT ("D: zFile3DS(FaceMatReader): FILE CORRUPT, material '"+s+"' is assigned to non-existant poly, index: "+zSTRING(nf));
		} else 
			polyList[nf].material = (zCMaterial*)actMat->AddRef();
    }
}

//index = 0
//num = 1

static void MapListReader (zFILE *f, int ind, long p) {
	// ----------ENGINE----------------------------------
    word nv;
    float c[2];

    if (f->Read(&nv, sizeof(nv)) <=0) return;
//	Print ("%*sVertices: %d", ind, "", nv);
	Print (ind, "numVert: "+zSTRING(nv));


	if (nv>numVert) {
		zERR_FAULT ("D: zFile3DS(MapListReader): FILE CORRUPT, texture-coords assign to non-existant vertex");
		nv = numVert;
	};
	
	word ctr = 0;
    while (ctr < nv) {
        if (f->Read(&c, sizeof(c)) <=0) return;
//		Print ("%*s    U: %f, V: %f", ind, "", c[0], c[1]);
		vertList[ctr].texCoord[VX] = c[0];
		vertList[ctr].texCoord[VY] =1.0F-c[1];					// invert V/Y Axis
		ctr++;
    }
}

static void SmooListReader (zFILE *f, int ind, long p) {
    dword s;
    int i;

    while (f->Pos()< p) 
	{
        if (f->Read(&s, sizeof(s)) <=0) return;
        //Print ("%*sSmoothing groups: ", ind, "");
        for (i = 0; i < 32; i++)
            if (s & (1 << i)) {
            //Print ("%d, ", i + 1);
			}
        //Print ("");
    }
}

static void TrMatrixReader(zFILE *f, int ind, long p) {
    float rot[9];
    float trans[3];
    if (f->Read(&rot, sizeof(rot)) <=0) return;
    //printf("%*sRotation matrix:", ind, "");
    //printf("%*s    %f, %f, %f", ind, "", rot[0], rot[1], rot[2]);
    //printf("%*s    %f, %f, %f", ind, "", rot[3], rot[4], rot[5]);
    //printf("%*s    %f, %f, %f", ind, "", rot[6], rot[7], rot[8]);
    if (f->Read(&trans, sizeof(trans)) <=0) return;
    //printf("%*sTranslation matrix: %f, %f, %f", ind, "", trans[0], trans[1], trans[2]);
}

static void LightReader(zFILE *f, int ind, long p) {
    float c[3];
    if (f->Read(&c, sizeof(c)) <=0) return;
    // printf("%*s    X: %f, Y: %f, Z: %f", ind, "", c[0], c[1], c[2]);
        // Read rest of chunks inside this one.
    ChunkReader(f, ind, p);
}

static void SpotLightReader(zFILE *f, int ind, long p) {
    float c[5];
    if (f->Read(&c, sizeof(c)) <=0) return;
    // printf("%*s    Target X: %f, Y: %f, Z: %f; Hotspot %f, Falloff %f", ind, "", c[0], c[1], c[2], c[3], c[4]);
}
 
static void CameraReader(zFILE *f, int ind, long p) {
    float c[8];
    if (f->Read(&c, sizeof(c)) <=0) return;
    //printf("%*s    Position: X: %f, Y: %f, Z: %f", ind, "", c[0], c[1], c[2]);
    //printf("%*s    Target: X: %f, Y: %f, Z: %f", ind, "", c[3], c[4], c[5]);
    //printf("%*s    Bank: %f, Lens: %f", ind, "", c[6], c[7]);
}

static void MatNameReader (zFILE *f, int ind, long p) {
    // Read ASCIIZ object name

	// ----------ENGINE----------------------------------
	// create new material
	zSTRING s = ASCIIZReader(f, ind, p);
//	Print ("%*sMaterial name \"%s\"", ind, "", s.ToChar());
	Print (ind, "Material name: "+s);
//zerr.Message (" newMat: "+s);
	s.Upper();
//	if (zCMaterial::GetUsageDefault	()!=zCMaterial::zMAT_USAGE_LEVEL) 
//		s += 

	actMat = zCMaterial::SearchName (s);
	if (!actMat) {
		actMat = zNEW(zCMaterial(s));
//		actMat->SubRef();				// ist ja noch nicht von Poly referenziert worden !
	};
}

static void MapFileReader(zFILE *f, int ind, long p) {
	// Read ASCIIZ filename
    zSTRING s = ASCIIZReader(f, ind, p);
//	Print ("%*sMap filename \"%s\"", ind, "", s.ToChar());
	Print (ind, "Texture name: "+s);
	// ----------ENGINE----------------------------------
	// Material bekommt ein Texture
	//zerr.Message (s);
	actMat->SetTexture (s);
}

static void FramesReader(zFILE *f, int ind, long p) {
    dword c[2];
    if (f->Read(&c, sizeof(c)) <=0) return;
    //printf("%*s    Start: %ld, End: %ld", ind, "", c[0], c[1]);
}

static void TrackObjNameReader(zFILE *f, int ind, long p) {
    word w[2];
    word parent;

        // Read ASCIIZ name
    //printf("%*sTrack object name \"", ind, "");
    ASCIIZReader(f, ind, p);
    if (f->Read(&w, sizeof(w)) <=0) return;
    if (f->Read(&parent, sizeof(parent)) <=0) return;
    //printf("%*sObject name data: Flags 0x%X, 0x%X, Parent %d", ind, "", w[0], w[1], parent);
}

static void PivotPointReader(zFILE *f, int ind, long p) {
    float pos[3];

    if (f->Read(&pos, sizeof(pos)) <=0) return;
    //printf("%*s  Pivot at X: %f, Y: %f, Z: %f", ind, "",pos[0], pos[1], pos[2]);
}

    // Key info flags for position, rotation and scaling:
    // Until I know the meaning of each bit in flags I assume all mean
    // a following float data.
    
        // NOTE THIS IS NOT A CHUNK, but A PART OF SEVERAL CHUNKS
static void SplineFlagsReader(zFILE *f, int ind, word flags) {
/*	int i;
    float dat;

    for (i = 0; i < 16; i++) {
        static const char *flagnames[] = {
            "Tension",
            "Continuity",
            "Bias",
            "Ease To",
            "Ease From",
        };
        if (flags & (1 << i)) {
            if (f->Read(&dat, sizeof(dat), 1, f) <=0) return;
            if (i < sizeof(flagnames)/sizeof(*flagnames)) {
                //printf("%*s             %-15s = %f", ind, "", flagnames[i], dat);
            } else {
                //printf("%*s             %-15s = %f", ind, "", "Unknown", dat);
			}
        }
    }*/
}

static void TrackPosReader(zFILE *f, int ind, long p) {
    word n, nf;
    float pos[3];
    word unkown;
    word flags;

	f->Seek (f->Pos()+10);									//	fseek(f, 10, SEEK_CUR);
    if (f->Read(&n, sizeof(n)) <=0) return;
    //printf("%*sPosition keys: %d", ind, "", n);
	f->Seek (f->Pos()+2);									//	fseek(f, 2, SEEK_CUR);
    while (n-- > 0) {
        if (f->Read(&nf, sizeof(nf)) <=0) return;
        if (f->Read(&unkown, sizeof(unkown)) <=0) return;
        if (f->Read(&flags, sizeof(flags)) <=0) return;
        //printf("%*s  Frame %3d: Flags 0x%X", ind, "", nf, flags);
        SplineFlagsReader(f, ind, flags);
        if (f->Read(&pos, sizeof(pos)) <=0) return;
        //printf("%*s             X: %f, Y: %f, Z: %f", ind, "", pos[0], pos[1], pos[2]);
    }
}

static void TrackRotReader(zFILE *f, int ind, long p) {
    word n, nf;
    float pos[4];
    word unkown;
    word flags;

	f->Seek (f->Pos()+10);									//	fseek(f, 10, SEEK_CUR);
    if (f->Read(&n, sizeof(n)) <=0) return;
    //printf("%*sRotation keys: %d", ind, "", n);
	f->Seek (f->Pos()+2);									//	fseek(f, 2, SEEK_CUR);
    while (n-- > 0) {
        if (f->Read(&nf, sizeof(nf)) <=0) return;
        if (f->Read(&unkown, sizeof(unkown)) <=0) return;
        if (f->Read(&flags, sizeof(flags)) <=0) return;
        //printf("%*s  Frame %3d: Flags 0x%X", ind, "", nf, flags);
        SplineFlagsReader(f, ind, flags);
        if (f->Read(&pos, sizeof(pos)) <=0) return;
        //printf("%*s             Angle: %f§, X: %f, Y: %f, Z: %f", ind, "", pos[0]*180.0/PI, pos[1], pos[2], pos[3]);
    }
}

static void TrackScaleReader(zFILE *f, int ind, long p) {
    word n, nf;
    float pos[3];
    word unkown;
    word flags;

	f->Seek (f->Pos()+10);									//	fseek(f, 2, SEEK_CUR);
    if (f->Read(&n, sizeof(n)) <=0) return;
    //printf("%*sScale keys: %d", ind, "", n);
	f->Seek (f->Pos()+2);									//	fseek(f, 2, SEEK_CUR);
    while (n-- > 0) {
        if (f->Read(&nf, sizeof(nf)) <=0) return;
        if (f->Read(&unkown, sizeof(unkown)) <=0) return;
        if (f->Read(&flags, sizeof(flags)) <=0) return;
        //printf("%*s  Frame %3d: Flags 0x%X", ind, "", nf, flags);
        SplineFlagsReader(f, ind, flags);
        if (f->Read(&pos, sizeof(pos)) <=0) return;
        //printf("%*s            X: %f, Y: %f, Z: %f", ind, "", pos[0], pos[1], pos[2]);
    }
}

static void ObjNumberReader(zFILE *f, int ind, long p) {
    word n;

    if (f->Read(&n, sizeof(n)) <=0) return;
    //printf("%*sObject number: %d", ind, "", n);
}


// ------------------------------------

static void SKIP (zFILE *f, int ind, long p) {
};

struct {
    word id;
    const char *name;
    void (*func)(zFILE *f, int ind, long p);
} ChunkNames[] = {
    {CHUNK_RGBF,        "RGB float",        RGBFReader},
    {CHUNK_RGBB,        "RGB byte",         RGBBReader},
    {CHUNK_RGBB2,       "RGB intern",       SKIP},

    {CHUNK_PRJ,         "Project",          NULL},
    {CHUNK_MLI,         "Material Library", NULL},

    {CHUNK_MAIN,        "Main",             NULL},
		{CHUNK_M3DVERS,     "3DS Version",      VersionReader},
		{CHUNK_OBJMESH,     "Object Mesh",      NULL},
			{CHUNK_MESHVERS,    "Mesh Version",		VersionReader},
			{CHUNK_MSTRSCALE,   "Master Scale",		SKIP},
			{CHUNK_BKGCOLOR,    "Background color", NULL},
			{CHUNK_AMBCOLOR,    "Ambient color",    NULL},
			{CHUNK_OBJBLOCK,    "Object Block",     ObjBlockReader},
				{CHUNK_TRIMESH,     "Tri-Mesh",         NULL},
					{CHUNK_VERTLIST,    "Vertex list",      VertListReader},
					{CHUNK_FACELIST,    "Face list",        FaceListReader},
					{CHUNK_FACEMAT,     "Face material",    FaceMatReader},
					{CHUNK_MAPLIST,     "Mappings list",    MapListReader},
					{CHUNK_TEXINFO,     "Mapping Icon",		SKIP},
					{CHUNK_SMOOLIST,    "Smoothings",       SmooListReader},
					{CHUNK_TRMATRIX,    "Matrix",           TrMatrixReader},
				{CHUNK_LIGHT,       "Light",            SKIP /*LightReader*/},
					{CHUNK_SPOTLIGHT,   "Spotlight",        SpotLightReader},
				{CHUNK_CAMERA,      "Camera",           SKIP /*CameraReader*/},
				{CHUNK_HIERARCHY,   "Hierarchy",        SKIP},

    {CHUNK_VIEWPORT,    "Viewport info",    SKIP},
    {CHUNK_MATERIAL,    "Material",         NULL},
		{CHUNK_MATNAME,     "Material name",    MatNameReader},
		{CHUNK_AMBIENT,     "Ambient color",    AmbColReader},
		{CHUNK_DIFFUSE,     "Diffuse color",    DiffColReader},
		{CHUNK_SPECULAR,    "Specular color",   SpecColReader},
		{CHUNK_SHININESS,   "Shininess",		SKIP},
		{CHUNK_SHIN2PCT,	"Shiny2 Perc",		SKIP},
		{CHUNK_TRANSP,		"Transparency",		SKIP},
		{CHUNK_SHADING,		"Shading",			SKIP},
		{CHUNK_TEXTURE,     "Texture map",      NULL},
			{CHUNK_MAPFILE,     "Map filename",     MapFileReader},
			{CHUNK_MAPTILING,   "Map tiling",		SKIP},
			{CHUNK_MAPTEXBLUR,  "Map textureblur",  SKIP},
		{CHUNK_BUMPMAP,     "Bump map",         NULL},
    {CHUNK_KEYFRAMER,   "Keyframer data",   SKIP},
		{CHUNK_AMBIENTKEY,  "Ambient key",      NULL},
		{CHUNK_TRACKINFO,   "Track info",       NULL},
		{CHUNK_FRAMES,      "Frames",           FramesReader},
		{CHUNK_TRACKOBJNAME,"Track Obj. Name",  TrackObjNameReader},
		{CHUNK_TRACKPIVOT,  "Pivot point",      PivotPointReader},
		{CHUNK_TRACKPOS,    "Position keys",    TrackPosReader},
		{CHUNK_TRACKROTATE, "Rotation keys",    TrackRotReader},
		{CHUNK_TRACKSCALE,  "Scale keys",       TrackScaleReader},
		{CHUNK_OBJNUMBER,   "Object number",    ObjNumberReader},

		{CHUNK_TRACKCAMERA, "Camera track",             NULL},
		{CHUNK_TRACKCAMTGT, "Camera target track",      NULL},
		{CHUNK_TRACKLIGHT,  "Pointlight track",         NULL},
		{CHUNK_TRACKLIGTGT, "Pointlight target track",  NULL},
		{CHUNK_TRACKSPOTL,  "Spotlight track",          NULL},
		{CHUNK_TRACKFOV,    "FOV track",                NULL},
		{CHUNK_TRACKROLL,   "Roll track",               NULL},
};

static int FindChunk(word id) {
    int i;
    for (i = 0; i < sizeof(ChunkNames)/sizeof(ChunkNames[0]); i++)
        if (id == ChunkNames[i].id)
            return i;
    return -1;
}

// ------------------------------------

// Der Chunk-Reader fuer Bloecke, denen nicht explizit eine 
// Auswertungs-Funktion zugeordnet ist.
//
// Bloecke, die von hier aus ausgewertet werden, haben Unter-Hierarchien.

static void ChunkReader(zFILE *f, int ind, long p) {
    TChunkHeader h;
    int n;
    long pc;

    while (f->Pos() < p) {
        pc = f->Pos();
        if (f->Read(&h, sizeof(h)) <=0) return;
        if (h.len == 0) return;
        n = FindChunk(h.id);
        if (n < 0) {
//			Print ("%*sUnknown chunk: 0x%04X, offset 0x%lX, size: %d bytes.", ind, "", h.id, pc, h.len);
			Print (ind, "unknown chunk: "+zSTRING(h.id)+", offset: "+zSTRING(pc)+", size: "+zSTRING(h.len));

			f->Seek (pc + h.len);
//			fseek(f, pc + h.len, SEEK_SET);
        } else {
//			Print ("%*sChunk type \"%s\", size %d bytes",ind, "", ChunkNames[n].name, h.len);
			Print (ind, "chunk type: "+zSTRING(ChunkNames[n].name)+", bytes: "+zSTRING(h.len));
            if (ChunkNames[n].func == SKIP) {
		        pc = pc + h.len;
				f->Seek (pc);
//	            fseek(f, pc, SEEK_SET);
			} else {
				if (ChunkNames[n].func == NULL) {
					//Print ("%*sChunk type \"%s\", offset 0x%lX, size %d bytes",ind, "", ChunkNames[n].name, pc, h.len);
					//Print ("%*sChunk type \"%s\", size %d bytes",ind, "", ChunkNames[n].name, h.len);
				};
				pc = pc + h.len;
				if (ChunkNames[n].func) ChunkNames[n].func	(f, ind + 2, pc);
				else					ChunkReader			(f, ind + 2, pc);
				f->Seek (pc);
//				fseek(f, pc, SEEK_SET);
			};
        }
//		if (ferror(f))	break;
    }
}

// ------------------------------------

static void Load3dsFile (const zSTRING& fileName) {
    long	p;
	zFILE	*f = zfactory->CreateZFile(fileName);

	//
	if (f->Exists()) 
	{
		f->Open();
		// Find file size.
		p = f->Size();

		// Go!
		ChunkReader(f, 0, p);
		f->Close();
	} else { 
        zERR_FATAL("D: zFile3d(::Load3dsFile): Can't open "+fileName);
	};

	//
	delete f;
}

//------------------------------------------------------------------------------------------

static void FlushMeshBuffer () {
	if (numPoly==0) return;

//	zerr.Message ("D: 1) Flushing MeshBuffer V: "+zSTRING(numVert)+" P: "+zSTRING(numPoly));
	// make it a mesh
	int i;
	
	// Vertices
	targetMesh->AllocVerts (numVert);
	zCVertex **newVertList = zNEW(zCVertex*) [numVert];	
	zERR_MESSAGE (3, zERR_BEGIN, "D: FlushMeshBuffer ("+zSTRING(numVert)+" verts)");
	
	for (i=0; i<numVert; i++) {
//		newVertList[i]= targetMesh->AddVertex (vertList[i].position);
		newVertList[i]= targetMesh->AddVertexSmart (vertList[i].position);
		if  ((i!=0) && ((i&4095)==0)) zERR_MESSAGE (3, 0, "D: ... still working ("+zSTRING(i)+" verts)");
	};
	zERR_MESSAGE (3, zERR_END, "");

	
	// Polys 
	targetMesh->AllocPolys (numPoly);
	zCPolygon *poly;
	for (i=0; i<numPoly; i++) {
		polyList[i].CheckForWrap();
		poly = 
		targetMesh->AddPoly (newVertList[ polyList[i].vertIndex[0] ], 
							 newVertList[ polyList[i].vertIndex[1] ], 
							 newVertList[ polyList[i].vertIndex[2] ]);
		// Tex-Coords setzen
		poly->SetMapping (0, vertList [ polyList[i].vertIndex[0] ].texCoord);
		poly->SetMapping (1, vertList [ polyList[i].vertIndex[1] ].texCoord);
		poly->SetMapping (2, vertList [ polyList[i].vertIndex[2] ].texCoord);
		// AddRef wurde oben bereits erledigt, hier lediglich umkopieren
		poly->material = polyList[i].material; 
		if (poly->material==0) {
			zERR_FATAL ("D: zFile3d(): Mesh has polys without material !");
//			poly->material = zNEW(zCMaterial());
		};

		// Jedes Material, dass hier durchkommt wird noch einmal mit dem DefaultUsage versehen.
		// Falls es in diesem Loader erzeugt worden ist, enthaelt es bereits die richtige Usage aus
		// dem Mat-Constructor. Nur falls es vorher bereits vorhanden war (Vob? Model?) wird es nochmals
		// nachtraeglich geflagt.
		if (poly->material) {
			poly->material->SetUsageFromDefault ();
//			poly->material->SetSmooth (FALSE);			// DARF NICHT !! Sonst wird ein .PMF ueberschrieben !!
		};

// nicht hier !! sonst funktioniert 'ConvertTrisToNPolys()' nicht korrekt !!
//poly->TexCorrectUV();


//	if (poly->material!=0) poly->material->texture = zCTexture :: Load(TEX_NAME);
//		poly->SetSmoothing (FALSE);
/*		poly->SetMapping (vertList [ polyList[i].vertIndex[0] ].texCoord, 
						  vertList [ polyList[i].vertIndex[1] ].texCoord,
						  vertList [ polyList[i].vertIndex[2] ].texCoord);*/
	};

	delete[] newVertList;
	delete[] polyList;
	delete[] vertList;
	polyList = 0;
	vertList = 0;
	numVert  = 0;
	numPoly  = 0;
};

void zCFile3DS::Load3DS (const zSTRING& fileName, zCMesh *tMesh) {
	// Debug-Output
	zERR_MESSAGE			(3, zERR_BEGIN, "D: Loading 3DS-File: \""+fileName+"\" ... ");

	// hohe FPU Precision sicherstellen
	const zDWORD fpuControlWord	= zfpuControler.GetCurrentControlWord();
	zfpuControler.SetPrecision_53();

	// init
	targetMesh				= tMesh;
	numVert					= 0;
	numPoly					= 0;
	actColor				= &dummyCol;

	// doit
	Load3dsFile				(fileName);

	// cleanup
	if (!zoptions->Parm("ZLOAD3DSOLDMETHOD"))
		zCMesh::S_InitVertexMergeCache(targetMesh);

	FlushMeshBuffer			();

	if (!zoptions->Parm("ZLOAD3DSOLDMETHOD"))
		zCMesh::S_DeleteVertexMergeCache();

	tMesh->CalcBBox3D		();
//	if (zCMaterial::GetUsageDefault	()!=zCMaterial::zMAT_USAGE_LEVEL) 
	{
		// Wenn man die VertNormals nicht setzt, sieht das frische Mesh
		// voellig wirr aus (Beleuchtungs-technisch)
		tMesh->CalcVertexNormals(zCMesh::zMSH_VERTNORMAL_FACET); 
//		tMesh->CalcVertexNormals(zCMesh::zMSH_VERTNORMAL_SMOOTH); 
	};

	// FIXME: hier/so ?? 
	tMesh->PrelightMesh ();

//	tMesh->SetDefaultPlanarMapping(1.0F,1.0F);
//	tMesh->FitPolyVertAlloc();
	//
	zPATH path (fileName);
	tMesh->SetMeshName (path.GetFilename()+"."+path.GetExt());


#ifdef COMPILING_SPACER
	// [EDENFELD] 1.09 Fix für den Spacer: falscher Speicherort des Level-3DS bei "Save ZEN"
	tMesh->pathToMesh = fileName;
#endif

	//
//	Print ("Finished. Verts: %d Polys: %d Mats: %d Textures: %d.",tMesh->numVert, tMesh->numPoly,zCMaterial :: NumInList(), zCTexture :: NumInList()); 

	//
//	zerr.Message ("D: ... Finished. Verts: "+zSTRING(tMesh->numVert) +
//		" Polys: "+zSTRING(tMesh->numPoly)
//		);
/*	zerr.Message ("D: ... Finished. Verts: "+zSTRING(tMesh->numVert) +
		" Polys: "+zSTRING(tMesh->numPoly) +
		" Mat: "+zSTRING(zCMaterial::NumInList()) +
		" Tex: "+zSTRING(zCTexture::NumInList())
		);*/
	zERR_MESSAGE (3, zERR_END, "");

	//
	zfpuControler.SetControlWord	(fpuControlWord);
};

// **********************************************************************************************************************
//
//			Save .3DS
//
// **********************************************************************************************************************

// Chunk-Len inkl. Header

static const long EXPORT_VERS = 3;

//static zCMesh		*mesh;
//static zCMaterial	**matList;
//static word			*matRef;
//static int			numMat;

static long StartChunk (zFILE& file, word id) {
	TChunkHeader	header;
	long			pos = file.Pos();
	header.id = id;
	file.Write (&header, sizeof(header));
	return pos;
};

static void WriteLen (zFILE& file, long pos, word id) {
	TChunkHeader header;
	header.id = id;
	long newpos;
	newpos		= file.Pos();
	header.len	= newpos-pos;
	file.Seek	(pos);
	file.Write	(&header, sizeof(header));
	file.Seek	(newpos);
};

static void	WriteString (zFILE& file, zSTRING s) {
	file.Write (s);
	const zBYTE zeroByte = 0;
	file.Write (&zeroByte, 1);
};

static void WriteShort (zFILE& file, short int s) { file.Write (&s, sizeof(short int)); };
static void WriteWord  (zFILE& file, word  w) { file.Write (&w, sizeof(word )); };
static void WriteLong  (zFILE& file, long  l) { file.Write (&l, sizeof(long )); };
static void WriteFloat (zFILE& file, float w) { file.Write (&w, sizeof(float)); };

static void	WriteCont_CHUNK_TRMATRIX (zFILE& file) {
	word id	 = CHUNK_TRMATRIX;
	long pos = StartChunk(file, id);
	
	// rot, 3x3
	zMAT3 mat3 = Alg_Identity2D();
	for (int x=0; x<3; x++) {
		for (int y=0; y<3; y++) {
			WriteFloat (file, mat3[y][x]);
		};
	};

	// trans,  3
	WriteFloat (file, 0.0F);
	WriteFloat (file, 0.0F);
	WriteFloat (file, 0.0F);

	WriteLen (file, pos, id);
};

// ==================================================================================================================

class zCMesh3DS {
public:
	zSTRING					meshName;		
	zCArray<int>			vertIndList3DS;	
	zCArray<int>			polyIndList3DS;	

	struct zTMatEntry {
		zCMaterial			*material;
		zCArray<int>		polyIndList;
	};
	zCArray<zTMatEntry*>	matList;

	~zCMesh3DS() {
		Clear();
	};
	void Clear() {
		meshName.Clear();;		
		vertIndList3DS.EmptyList();	
		polyIndList3DS.EmptyList();	
		for (int i=0; i<matList.GetNum(); i++)
			delete matList[i];
		matList.EmptyList();
	};
	zBOOL IsEmpty			() const { return vertIndList3DS.IsEmpty() || polyIndList3DS.IsEmpty(); };
};


class zCBinTree3DS;

static zCBinTree3DS  *binTree3DS=0;

struct zTBinTreeNode {
	zCArray<int>	vertIndList3DS;	
	zCArray<int>	polyIndList3DS;	
};

class zCBinTree3DS {
public:

	zCBinTree3DS();
	~zCBinTree3DS();
	void					CreateNodeList		(int numVert, int numPoly);
	int						GetVert3DSIndex		(const zVEC3& pos, const zVEC2& texUV);
	void					DropMesh			(zCMesh *mesh);
	int						CalcNum3DSObject	();
	void					BuildMesh3DS		(int objectNr, int numObject, zCMesh3DS *mesh3DS);
	void					GetMatListComplete	(zCArray<zCMaterial*> &matList);

	int						numVert3DS;
	int						numPoly3DS;
	zCArraySort<TVertex3ds> vertList3DS;
	//TVertex3ds				*vertList3DS;
	TPoly3ds				*polyList3DS;
	zBOOL					dumpTexCoords;

private:
	int						act3DSObject;
	zCArray<zTBinTreeNode>	nodeList;		// FIXME: eigentlich brauchen nur alle 'leafs' allokiert werden, nicht alle 'nodes'..
	zTBBox3D				bbox3D;

	zBOOL					IsLeaf					(int nodeIndex) const		{ return (nodeIndex*2)>=nodeList.GetNum();	};
	int						GetLeafIndex			(const zVEC3& pos);
	void					CalcNumPolyVertSubtree	(int nodeIndex, int& numVert, int& numPoly);
	void					GetPolyListFor3DSObj	(int objectNr, zCArray<int> &polyIndexList, zCArray<int> &vertIndList);
};

zCBinTree3DS::zCBinTree3DS()
{
	bbox3D.InitZero		();
	act3DSObject		= 0;
	numVert3DS			= 0;
	numPoly3DS			= 0;
	vertList3DS.SetCompare(Compare_Verts3DS);
	polyList3DS			= 0;
	dumpTexCoords		= FALSE;
};

zCBinTree3DS::~zCBinTree3DS()
{
	numVert3DS			= 0;
	numPoly3DS			= 0;
	vertList3DS.DeleteList();
	//delete[]	vertList3DS;
	delete[]	polyList3DS;
};

void zCBinTree3DS::GetMatListComplete (zCArray<zCMaterial*> &matList)
{
	// linear Search, zu langsam ?
	for (int i=0; i<numPoly3DS; i++)
	{
		if (polyList3DS[i].material)
		if (!matList.IsInList (polyList3DS[i].material))
			matList.Insert (polyList3DS[i].material);
	};
};

void zCBinTree3DS::CalcNumPolyVertSubtree (int nodeIndex, int& numVert, int& numPoly)
{
	if (IsLeaf (nodeIndex))	{
		numPoly += nodeList[nodeIndex].polyIndList3DS.GetNum();
		numVert += nodeList[nodeIndex].vertIndList3DS.GetNum();
	} else {
		CalcNumPolyVertSubtree (nodeIndex*2  , numVert, numPoly);
		CalcNumPolyVertSubtree (nodeIndex*2+1, numVert, numPoly);
	};
};

int zCBinTree3DS::CalcNum3DSObject	()
{
	// Breitensuche
	int index	= 1;
	do {
		int lastIndex	= (index*2-1);
		zBOOL	ok		= TRUE;
		for (int i=index; i<=lastIndex; i++)
		{
			int numVert		= 0;
			int numPoly		= 0;
			CalcNumPolyVertSubtree (i, numVert, numPoly);
			ok = ok && ((numVert<=65535) && (numPoly<=65535));		// 3DS Limits
//			ok = ok && ((numVert<=50) && (numPoly<=65535));			// 3DS Limits
			if (!ok) break;
		};
		if (ok)	break;
		index *= 2;
	} while (!IsLeaf(index));
	return index;
};

void zCBinTree3DS::GetPolyListFor3DSObj (int nodeIndex, zCArray<int> &polyIndexList, zCArray<int> &vertIndList)
{
	if (IsLeaf(nodeIndex))
	{
		for (int i=0; i<nodeList[nodeIndex].polyIndList3DS.GetNum(); i++)
		{
			// Poly eintragen
			polyIndexList.Insert (nodeList[nodeIndex].polyIndList3DS[i]);
			// Vertices eintragen
			int polyInd = nodeList[nodeIndex].polyIndList3DS[i];
			for (int j=0; j<3; j++)
			{
				int vertInd = polyList3DS[polyInd].vertIndex[j];
				if (vertList3DS[vertInd].lastObjHasBeenWrittenTo!=this->act3DSObject)
				{
					vertIndList.Insert (vertInd);
					vertList3DS[vertInd].remappedIndex			= vertIndList.GetNum()-1;
					vertList3DS[vertInd].lastObjHasBeenWrittenTo= this->act3DSObject;
				};
				polyList3DS[polyInd].vertIndex[j]	= vertList3DS[vertInd].remappedIndex;
			};
		};
	} else {
		GetPolyListFor3DSObj (nodeIndex*2  , polyIndexList, vertIndList);
		GetPolyListFor3DSObj (nodeIndex*2+1, polyIndexList, vertIndList);
	};
};

void zCBinTree3DS::BuildMesh3DS (int objectNr, int numObject, zCMesh3DS *mesh3DS)
{
	mesh3DS->Clear();
	mesh3DS->meshName = "zenGin"+zSTRING(objectNr);

	// Poly und Vert Listen
	int nodeIndex	= numObject + objectNr;
	act3DSObject	= objectNr+1;
	GetPolyListFor3DSObj (nodeIndex, mesh3DS->polyIndList3DS, mesh3DS->vertIndList3DS);

	// BuildUsedMatList
	// erstmal alle verwendeten Materials sammeln
	for (int i=0; i<mesh3DS->polyIndList3DS.GetNum(); i++) 
	{
		zCMaterial *mat = polyList3DS[mesh3DS->polyIndList3DS[i]].material;
		if (mat) {
			for (int j=0; j<mesh3DS->matList.GetNum(); j++) 
			{
				if (mesh3DS->matList[j]->material==mat) 
				{
//					mesh3DS->matList[j]->polyIndList.Insert (mesh3DS->polyIndList3DS[i]);
					mesh3DS->matList[j]->polyIndList.Insert (i);
					goto foundMat;
				};
			};
			{
				zCMesh3DS::zTMatEntry *matEntry = zNEW(zCMesh3DS::zTMatEntry);
				matEntry->material				= mat;
//				matEntry->polyIndList.Insert	(mesh3DS->polyIndList3DS[i]);
				matEntry->polyIndList.Insert	(i);							// bezieht sich auf Reihenfolge in 'Mesh3DS' und nicht BinTree3DS!!
				mesh3DS->matList.Insert			(matEntry);
			};
foundMat:;
		};
	};

};

void zCBinTree3DS::CreateNodeList (int numVert, int numPoly)
{
	// 15 verts pro Leaf im Schnitt
	int	numLeafs		= zMakePowerOf2Higher ( int (float(numVert) / 15.0F) );
	zClamp (numLeafs, 512, 8192);
	int	numNodes		= numLeafs*2;
//	int depth			= 10;
//	int numNodes		= int(pow (2, double(depth)));
	nodeList.DeleteList	();				// call constructors
	nodeList.AllocAbs	(numNodes);
	nodeList.MarkNumAllocUsed();
};

int zCBinTree3DS::GetLeafIndex (const zVEC3& pos)
{
	int			axisTable[3] = { 0, 2, 1 };		// erst in der XZ Eben splitten, dann erst Y
	int			oldIndex= 1;
	int			index	= 1;
	int			axis	= 0;
	zTBBox3D	box		= bbox3D;
	while (index<nodeList.GetNum())
	{
		int		realAxis= axisTable[axis];
		zREAL	boxMid	= (box.maxs[realAxis] + box.mins[realAxis]) * 0.5F;
		oldIndex		= index;
		if (pos[realAxis]<boxMid)
		{
			box.maxs[realAxis]	= boxMid;
			index				= 2*index;
		} else {
			box.mins[realAxis]	= boxMid;
			index				= 2*index+1;
		};
		realAxis = (realAxis+1) % 3;
	};
	return oldIndex;
};


#if 0
int zCBinTree3DS::GetVert3DSIndex (const zVEC3& pos, const zVEC2& texUV)
{
	static TVertex3ds searchVert3DS;
	searchVert3DS.position  = pos;
	searchVert3DS.texCoord  = texUV;
	
	int vert3DSIndex = vertList3DS.Search(searchVert3DS);
	int leafIndex	 = GetLeafIndex (pos);

	if (vert3DSIndex != -1)
	{
		return vert3DSIndex;
	}

	// Vertex nicht gefunden, neuen erzeugen
	TVertex3ds nextVert;

	nextVert.position		= pos;
	nextVert.texCoord		= texUV;
	vertList3DS.InsertSort(nextVert);
	

	int foundIndex = vertList3DS.Search(nextVert);

	//(&vertList3DS.GetArray()[foundIndex])->mappedIndex = foundIndex;

	numVert3DS++;

	//nodeList[GetLeafIndex (pos)].vertIndList3DS.Insert	(numVert3DS-1);
	nodeList[leafIndex].vertIndList3DS.Insert	(foundIndex);
	return foundIndex;
};
#else

int zCBinTree3DS::GetVert3DSIndex (const zVEC3& pos, const zVEC2& texUV)
{
	const zREAL	VERT_EPS	= zREAL(0.1F);
	const zREAL	UV_EPS		= zREAL(0.001F);

	//
	int leafIndex = GetLeafIndex (pos);
	for (int i=0; i<nodeList[leafIndex].vertIndList3DS.GetNum(); i++)
	{
		TVertex3ds	*vert3DS = &(vertList3DS[nodeList[leafIndex].vertIndList3DS[i]]);
		if ((zAbs(zREAL(pos.n[0]-vert3DS->position.n[0])) < VERT_EPS) &&
			(zAbs(zREAL(pos.n[1]-vert3DS->position.n[1])) < VERT_EPS) &&
			(zAbs(zREAL(pos.n[2]-vert3DS->position.n[2])) < VERT_EPS) &&
		    (zAbs(zREAL(texUV[0]-vert3DS->texCoord.n[0])) < UV_EPS)  &&
			(zAbs(zREAL(texUV[1]-vert3DS->texCoord.n[1])) < UV_EPS))
		{
			return nodeList[leafIndex].vertIndList3DS[i];
		};
	};
	// Vertex nicht gefunden, neuen erzeugen
	vertList3DS[numVert3DS].position		= pos;
	vertList3DS[numVert3DS].texCoord		= texUV;
	numVert3DS++;
	nodeList[leafIndex].vertIndList3DS.Insert	(numVert3DS-1);
	return numVert3DS-1;
};
#endif

void zCBinTree3DS::DropMesh (zCMesh *mesh)
{
	//
	int i,j;
	int numMaxVert	= 0;
	int numMaxPoly	= 0;
	numPoly3DS		= 0;
	numVert3DS		= 0;
	dumpTexCoords	= FALSE;
	for (i=0; i<mesh->numPoly; i++)  {
		numMaxVert += mesh->Poly(i)->polyNumVert;
		numMaxPoly += mesh->Poly(i)->polyNumVert-2;
	};
	//delete[] vertList3DS;

	vertList3DS.DeleteList();
	delete[] polyList3DS;
	vertList3DS.AllocAbs(numMaxVert);
	polyList3DS= zNEW(TPoly3ds)		[numMaxPoly];

	bbox3D	= mesh->GetBBox3D();

	CreateNodeList (mesh->numVert, mesh->numPoly);

	// Create:
	// vertList3DS, FACELIST
	// Achtung: wenn Verts mit verschiedenen Texture-Koordinaten vorkommen,
	// muessen diese Verts auch mehrfach rausgeschrieben werden !

	zBOOL meshHasNPolys=FALSE;		

	zERR_MESSAGE(3,zERR_BEGIN,"D: 3DS-EXP: Drop mesh \""+mesh->GetMeshName()+"\" ("+zSTRING(mesh->numPoly)+" polys) ...");
	int vertInd[256];
	for (i=0; i<mesh->numPoly; i++) {

		if ((i&1023)==0) zERR_MESSAGE(4,0,"D: 3DS-EXP: ... still working ("+zSTRING(i)+" polys)");

		zCPolygon *poly = mesh->Poly(i);
		
		// Verts in die VertList eintragen
		for (j=0; j<poly->polyNumVert; j++) 
		{
			if (poly->polyNumVert>3) meshHasNPolys=TRUE;
			zCVertex		*vert	= poly->GetVertexPtr(j);
			zCVertFeature	*feat	= (poly->feature) ? poly->feature[j]  : 0;
			// keine Texture ? UV auf 0 setzen!
			if (!poly->material->texture) {
				feat->texu=0;
				feat->texv=0;
			};
			vertInd[j]	= GetVert3DSIndex (vert->position, zVEC2(feat->texu, feat->texv));
		};		

		// FIXME: ACHTUNG, was bei degenerierten Polys ? (3 Verts kolinear)

		for (j=2; j<poly->polyNumVert; j++) {
			// Verts eintragen
			polyList3DS[numPoly3DS].vertIndex[0]	= vertInd[0];
			polyList3DS[numPoly3DS].vertIndex[1]	= vertInd[j-1];
			polyList3DS[numPoly3DS].vertIndex[2]	= vertInd[j];
			polyList3DS[numPoly3DS].material		= poly->material;
			polyList3DS[numPoly3DS].wrapu			= FALSE;				// FIXME: ????
			polyList3DS[numPoly3DS].wrapv			= FALSE;
			word flags = 0x02;										// BC
			if (j==2)					flags |= 0x01 | 0x02;		// AB BC
			if (j==poly->polyNumVert-1) flags |= 0x02 | 0x04;		// BC CA
			polyList3DS[numPoly3DS].flags			= flags;
			if (poly->material)
			if (poly->material->texture)
				dumpTexCoords = TRUE;
			// Poly in Baum einfuegen
			{
				int leafIndex = GetLeafIndex (poly->GetCenter());
				nodeList[leafIndex].polyIndList3DS.Insert (numPoly3DS);
			};
			numPoly3DS++;
		};
	};

	zERR_MESSAGE(3,zERR_END,"");
};

/*
  - BinTree aufbauen (gleichmaessig)
  - alle zCMesh Polys abgehen
	- bei jedem Vert pruefen, ob es bereits im 3DS Format vorliegt: 
	- in den BinTree droppen, 
		- bereits vorhanden ? => dann den Index darauf verwenden
		- sonst: neues 3DS Vert anlegen (im Leaf)
	- am Ende wird jedes 3DS Poly in ein Leaf abgelegt (entweder nach Schwerpunkt oder 1 bel. Vert-Pos)
  - dann wird der BinTree rekursiv top-down in 3DS-Objekte zerlegt (recursion, falls Zahlen über Limit)
*/

static void	WriteCont_CHUNK_TRIMESH (zFILE& file, zCMesh3DS *mesh3DS) {
/*  CHUNK_TRIMESH   = 0x4100,

x       CHUNK_VERTLIST  = 0x4110,
x       CHUNK_FACELIST  = 0x4120,
x       CHUNK_FACEMAT   = 0x4130,
x       CHUNK_MAPLIST   = 0x4140, 

        CHUNK_SMOOLIST  = 0x4150,
        CHUNK_TRMATRIX  = 0x4160, */

	// Write out Data-Chunks
	int i;
	word id;
	long pos;

	//
	// VERLIST
	//

	id	= CHUNK_VERTLIST;			// range: 1..65535
	pos = StartChunk (file, id);
	
	WriteWord (file, mesh3DS->vertIndList3DS.GetNum());
	for (i=0; i<mesh3DS->vertIndList3DS.GetNum(); i++) {
		TVertex3ds *vert3DS = &binTree3DS->vertList3DS[mesh3DS->vertIndList3DS[i]];
		WriteFloat (file, vert3DS->position[VX]); 
		WriteFloat (file, vert3DS->position[VZ]);		// swap y/z
		WriteFloat (file, vert3DS->position[VY]); 
	};
	WriteLen (file, pos, id);

	//
	// MAPLIST
	//

	if (binTree3DS->dumpTexCoords) {
		id	= CHUNK_MAPLIST;			// range: 1..65535
		pos = StartChunk (file, id);
		
		WriteWord (file, mesh3DS->vertIndList3DS.GetNum());
		for (i=0; i<mesh3DS->vertIndList3DS.GetNum(); i++) {
			TVertex3ds *vert3DS = &binTree3DS->vertList3DS[mesh3DS->vertIndList3DS[i]];
			WriteFloat (file, vert3DS->texCoord[VX]); 
			WriteFloat (file, 1.0F - vert3DS->texCoord[VY]);			// invert V/Y Axis
		};
		WriteLen (file, pos, id);
	};

	//
	// TRMATRIX
	//

	WriteCont_CHUNK_TRMATRIX (file);

	//
	// FACELIST
	//

	id	= CHUNK_FACELIST;				// range: 1..65535
	pos = StartChunk (file, id);
	
	WriteWord (file, mesh3DS->polyIndList3DS.GetNum());
	for (i=0; i<mesh3DS->polyIndList3DS.GetNum(); i++) {
		TPoly3ds *poly3DS = &binTree3DS->polyList3DS[mesh3DS->polyIndList3DS[i]];
		WriteWord (file, poly3DS->vertIndex[0]); 
		WriteWord (file, poly3DS->vertIndex[1]); 
		WriteWord (file, poly3DS->vertIndex[2]); 
		word flags = poly3DS->flags;
		// AB BC CA
//		flags += 0x01;
//		flags += 0x02;
//		flags += 0x04;
		// Wrap
		if (poly3DS->wrapu) flags += 0x08;
		if (poly3DS->wrapv) flags += 0x10;
		WriteWord (file, flags);							// FIXME: flags !!
	};

	{
		//
		// FACEMAT
		// 
		// (ist in FACELIST eingebettet)
		// fuer jedes verwendete Material ein eigener Block

		for (int m=0; m<mesh3DS->matList.GetNum(); m++) {
			word id	 = CHUNK_FACEMAT; 
			long pos = StartChunk (file, id);
			
			WriteString (file, mesh3DS->matList[m]->material->GetName());
			WriteWord   (file, mesh3DS->matList[m]->polyIndList.GetNum());
			for (i=0; i<mesh3DS->matList[m]->polyIndList.GetNum(); i++) {
				WriteWord (file, mesh3DS->matList[m]->polyIndList[i]);
			};
			WriteLen (file, pos, id);
		};
	};
	WriteLen (file, pos, id);

	//
	// TEXTURE MAPING ICON
	//
/*    MESH_TEXTURE_INFO
        short map_type;
        float x_tiling, y_tiling;
        float icon_x, icon_y, icon_z;
		float scaling;
        float matrix[4][3];
        float plan_icon_w, plan_icon_h, cyl_icon_h; 
*/
/*
	if (dumpTexCoords) {
		id	= CHUNK_TEXINFO;
		pos = StartChunk (file, id);
		
		// Map_Type:  0=planar, 1=cylindrical, 2=spherical
		WriteWord	(file, 0);
		// X-Tiling, Y-Tiling
		WriteFloat	(file, 1.0F);
		WriteFloat	(file, 1.0F);
		// Icon-Origin in World-Space
		WriteFloat	(file, 100.0F);
		WriteFloat	(file, 100.0F);
		WriteFloat	(file, 100.0F);
		// Scaling								// hier ? oder nach der Matrix ?
		WriteFloat	(file, 1.0F);
		// Icon-Origin in World-Space
		zMAT4 mat4 = Alg_Identity3D();
		for (int x=0; x<4; x++) {
			for (int y=0; y<3; y++) {
				WriteFloat (file, mat4[y][x]);
			};
		};
		// Planar-Icon Width/Height, Cylindrical-Icon Height
		WriteFloat	(file, 12.0F);
		WriteFloat	(file, 12.0F);
		WriteFloat	(file, 12.0F);
		WriteLen	(file, pos, id);
	};
*/
};

static void	WriteCont_CHUNK_OBJBLOCK (zFILE& file, zCMesh3DS *mesh3DS) {
	// FIXME: 
	// Namenslaenge 1-10
//	WriteString (file, mesh->GetMeshName());
	WriteString (file, mesh3DS->meshName);

	// jetzt die TRI-MESHES
	word id	 = CHUNK_TRIMESH;
	long pos = StartChunk	(file, id);
	WriteCont_CHUNK_TRIMESH (file, mesh3DS);
	WriteLen				(file, pos, id);
};

static void	WriteRGBB (zFILE& file, zCOLOR& col) {
	word id	 = CHUNK_RGBB;
	long pos = StartChunk(file, id);
	file.Write  (&(col.r), sizeof (col.r));
	file.Write  (&(col.g), sizeof (col.g));
	file.Write  (&(col.b), sizeof (col.b));
	WriteLen	(file, pos, id);
};

static void	Write_CHUNK_SHORTPERC (zFILE& file, short int p) {
	word id	 = CHUNK_SHORTPERC;
	long pos = StartChunk(file, id);
	file.Write  (&(p), sizeof (p));
	WriteLen	(file, pos, id);
};

static void	WriteCont_CHUNK_MATERIAL (zFILE& file, zCMaterial* mat) {
/*  CHUNK_MATERIAL  = 0xAFFF,
		CHUNK_MATNAME   = 0xA000,
		CHUNK_AMBIENT   = 0xA010,
		CHUNK_DIFFUSE   = 0xA020,
		CHUNK_SPECULAR  = 0xA030,
        CHUNK_TEXTURE   = 0xA200,
			// CHUNK_SHORTPERC
	        CHUNK_MAPFILE   = 0xA300,			// 8+3
			CHUNK_MAPTILING	= 0xA351,
			CHUNK_MAPTEXBLUR= 0xA353,
		CHUNK_BUMPMAP   = 0xA230, */
	word id;
	long pos;
	zSTRING name;

	//
	// Namenslaenge 1-16
	id	= CHUNK_MATNAME;
	pos = StartChunk(file, id);
	name = mat->GetName();
	if (name.Length()>16) {
//		zerr.Report (zERR_WARN, 1000, "D: 3DS-EXP: Material-Name with more than 16 chars encountered (preserved): "+name);
//		name.Delete (16, 100);
	};
	WriteString (file, name);
	WriteLen	(file, pos, id);

	// 
	id	= CHUNK_AMBIENT;
	pos = StartChunk(file, id);
	WriteRGBB	(file, mat->GetColor());
	WriteLen	(file, pos, id);

	// sicherstellen, dass das Material auch die AvgColor der Texture enthaelt
	mat->RefreshAvgColorFromTexture();

	// 
	id	= CHUNK_DIFFUSE;
	pos = StartChunk(file, id);
	WriteRGBB	(file, mat->GetColor());
	WriteLen	(file, pos, id);

	// 
	id	= CHUNK_SPECULAR;
	pos = StartChunk(file, id);
	WriteRGBB	(file, mat->GetColor());
	WriteLen	(file, pos, id);

	// 
	id	= CHUNK_SHININESS;
	pos = StartChunk(file, id);
	Write_CHUNK_SHORTPERC (file, 50);
	WriteLen	(file, pos, id);

	// 
	id	= CHUNK_SHIN2PCT;
	pos = StartChunk(file, id);
	Write_CHUNK_SHORTPERC (file, 50);
	WriteLen	(file, pos, id);

	// 
	id	= CHUNK_TRANSP;
	pos = StartChunk(file, id);
	Write_CHUNK_SHORTPERC (file, 0);
	WriteLen	(file, pos, id);

	// 
	id	= CHUNK_SHADING;
	pos = StartChunk(file, id);
	WriteShort (file, 2);						// 2 = Gouraud
	WriteLen   (file, pos, id);
/*
    CHUNK_TEXTURE   = 0xA200,
		// CHUNK_SHORTPERC
	    CHUNK_MAPFILE   = 0xA300,			// 8+3
		CHUNK_MAPTILING	= 0xA351,
		CHUNK_MAPTEXBLUR= 0xA353, */
	// 
	if (mat->texture) {
		id	= CHUNK_TEXTURE;
		pos = StartChunk(file, id);
		{
			word id;
			long pos;
			//
			Write_CHUNK_SHORTPERC (file, 100);

			//
			id	= CHUNK_MAPFILE;
			pos = StartChunk(file, id);
			name = mat->texture->GetName();
			if (name.Length()>12) {
//				zerr.Report (zERR_WARN, 1000, "D: 3DS-EXP: Texture-Name with more than 12 chars encountered (preserved): "+name);
//				name.Delete (12, 100);
			};
			WriteString (file, name);
			WriteLen    (file, pos, id);

			//
			id	= CHUNK_MAPTILING;
			pos = StartChunk(file, id);
			WriteWord  (file, 0);
			WriteLen   (file, pos, id);

			//
			id	= CHUNK_MAPTEXBLUR;
			pos = StartChunk(file, id);
			WriteFloat (file, 0.0F);
			WriteLen   (file, pos, id);
		};
		WriteLen   (file, pos, id);
	};
};

static void	WriteCont_CHUNK_OBJMESH (zFILE& file) {
	word id;
	long pos;

	// MESH-Version-Number (4 fuer Release 4)
	id	= CHUNK_MESHVERS;
	pos = StartChunk(file, id);
	WriteLong (file, EXPORT_VERS);
	WriteLen  (file, pos, id);

	// Write Materials
	// Nun alle Materials nacheinander schreiben
	{
		zCArray<zCMaterial*>	matList;
		binTree3DS->GetMatListComplete (matList);
		for (int m=0; m<matList.GetNum(); m++) {
			word id	 = CHUNK_MATERIAL;
			long pos = StartChunk		(file, id);
			WriteCont_CHUNK_MATERIAL	(file, matList[m]);
			WriteLen					(file, pos, id);
		};
	};

	// Mesh Master-Scale
	id	= CHUNK_MSTRSCALE;
	pos = StartChunk(file, id);
	WriteFloat (file, 1.0);
	WriteLen   (file, pos, id);

	// GOGOGOGO
	int numObj			= binTree3DS->CalcNum3DSObject();
	int realNumObj		= 0;
	zCMesh3DS *mesh3DS	= zNEW(zCMesh3DS);
//	numObj=1;
	for (int i=0; i<numObj; i++)
	{
		// Write CHUNK_OBJBLOCK
		id	= CHUNK_OBJBLOCK;
		pos = StartChunk			(file, id);
		binTree3DS->BuildMesh3DS	(i, numObj, mesh3DS);
		if (!mesh3DS->IsEmpty()) {
			WriteCont_CHUNK_OBJBLOCK(file, mesh3DS);
			realNumObj++;
		};
		WriteLen					(file, pos, id);
	};
	delete mesh3DS;
	zerr.Message ("D: 3DS-EXP: num Objects: "+zSTRING(realNumObj));
};

static void	WriteCont_CHUNK_MAIN (zFILE& file) {
	word id;
	long pos;

	id	= CHUNK_M3DVERS;
	pos = StartChunk(file, id);
	WriteLong (file, EXPORT_VERS);
	WriteLen (file, pos, id);

	id	= CHUNK_OBJMESH;
	pos = StartChunk(file, id);
	WriteCont_CHUNK_OBJMESH		(file);
	WriteLen					(file, pos, id);
};

void zCFile3DS::Save3DS (const zSTRING& fileName, zCMesh *sMesh) 
{
	zERR_MESSAGE(3,zERR_BEGIN,"D: 3DS-EXP: Saving 3DS-File: \""+fileName+"\" ... ");
	zCPolygon::S_ResetMorphedVerts();

		// hohe FPU Precision sicherstellen
		const zDWORD fpuControlWord	= zfpuControler.GetCurrentControlWord();
		zfpuControler.SetPrecision_53();

		//
		binTree3DS = zNEW(zCBinTree3DS);
		binTree3DS->DropMesh	(sMesh);

	zERR_MESSAGE(3,0,"D: 3DS-EXP: Writing to file: \""+fileName+"\" ... ");

		zFILE* file = zfactory->CreateZFile(fileName);

#ifdef COMPILING_SPACER
		// [EDENFELD] 1.09 Fix für den Spacer: falscher Speicherort des Level-3DS bei "Save ZEN"
		if (!sMesh->pathToMesh.IsEmpty())
		{
			file->SetPath(sMesh->pathToMesh);
		}
#endif
		
		file->Create();

		word id	 = CHUNK_MAIN;
		long pos = StartChunk	(*file, id);

		WriteCont_CHUNK_MAIN	(*file);
		WriteLen				(*file, pos, id);

		file->Close				();	

		delete file;file=0;		

		delete binTree3DS;	binTree3DS=0;

		//
		zfpuControler.SetControlWord	(fpuControlWord);

	zERR_MESSAGE(3,zERR_END,"D: 3DS-EXP: finished");
};


// disable VC++ Warning: double to float conversion
#pragma warning( default : 4244 ) 
