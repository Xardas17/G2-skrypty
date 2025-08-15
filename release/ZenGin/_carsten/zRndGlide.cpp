
/********************************************************************************
*																
* Project       : Phoenix
* File          : zRndGlide.cpp									
* Author        : Carsten Edenfeld 								
*********************************************************************************
- Bugs: 
*********************************************************************************
- TODO: ~2^24 Tasks
		- Defragmentation (evtl. Life time prediction )

Konvertierung fürs CC: Ausgangsfarbe RGB565 -> RGB888. Fehlende Bits von RGB565
bis 8 Bits von der linken Seite übernehmen.

- Color Combine Unit default:			Farben aus Vertices * Farbe aus Textur
  Tex   Combine Unit default:			Farbe  aus Textur
  Alpha Combine Unit default:			Alpha aus Vertices * Alpha aus Material
  oder									Alpha aus Vertices * Alpha aus Textur

		// a = vertex alpha * constant alpha (material) - default
		grAlphaCombine(GR_COMBINE_FUNCTION_SCALE_OTHER,	GR_COMBINE_FACTOR_LOCAL,
					   GR_COMBINE_LOCAL_CONSTANT,GR_COMBINE_OTHER_ITERATED, FXFALSE	);//	    grAlphaCombine(GR_COMBINE_FUNCTION_LOCAL,	GR_COMBINE_FACTOR_ONE,

		// a = vertex alpha * texture alpha
		grAlphaCombine(GR_COMBINE_FUNCTION_SCALE_OTHER,	GR_COMBINE_FACTOR_LOCAL,
					   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_TEXTURE, FXFALSE	);//	    grAlphaCombine(GR_COMBINE_FUNCTION_LOCAL,	GR_COMBINE_FACTOR_ONE,


  
- Alpha Blending :  c1 = (c0 * f0) + (c1 * f1)
					c0 = incoming pixel
					c1 = destination pixel
					f0 : blend factor 1 
					f1 : blend factor 2

					Normal blending:
					c1 = (c0 * a) + (c1 * (1-a))
					grAlphaBlendFunction(GR_BLEND_SRC_ALPHA, GR_BLEND_ONE_MINUS_SRC_ALPHA,  
										 GR_BLEND_ZERO,GR_BLEND_ZERO);            

					Additive blending:
					c1 = a * (c0 + c1)

				    grAlphaBlendFunction(GR_BLEND_SRC_ALPHA, GR_BLEND_SRC_ALPHA,  
										 GR_BLEND_ZERO,GR_BLEND_ZERO);         
										 
					blending without alpha: 
					c1 = (c0 + c1)

				    grAlphaBlendFunction(GR_BLEND_ONE, GR_BLEND_ONE,  
										 GR_BLEND_ZERO,GR_BLEND_ZERO);         

					
		
			// alpha beide mit vertex alpha included, also vertex*material oder vertex*texture
			typedef struct zTAlpha { zALPHA_MATERIAL, zALPHA_TEXTURE }
			
			typedef enum   zTAlphaBlending { zBLEND_DISABLE, zBLEND_NORMAL, zBLEND_ADDITIVE }
			
			more possible

			void SetAlphaSource( const zTAlpha &src );
			zTAlpha GetAlphaSource();
			SetAlphaBlending( ... );
			GetAlphaBlending();

 - 3d Karten, die kein Alpha Channel pro Textur beherrschen, müssen 
   zur Installation des Spieles den Alpha Channel in die Chromakey-Farbe wandeln.

 - Texture Cache static inline ?

 - Der Z-Buffer muss auf die maximale Genauigkeit skaliert werden [0..65535].
   Komischerweise zeigt das dann aber keine Veränderung bei den Mipmap Stufen ??
   Und gibt es Probs beim Textur-Mapping (Textur-Flimmern)
   Der Himmel hat z Werte grösser als die Entf. der Farclip Plane, darum werden
   die letzten Mipmap Stufen falsch dargestellt

  Voodoo 2: Wenn der Framebuffer gelockt ist, dürfen wirklich nur Pixel
  in dem jeweiligem gesetzt werden, keine state-changes, ansonsten Absturz !

  Bei dem Sortieren von Alpha Polys muss beachtet werden, dass nur ein simples
  Sortieren nach mittlerer Tiefe stattfindet. Wenn grosse Polygone (z.B. Wasserpolys)
  von kleineren Polys durchschnitten werden, ist die Darstellung oft nicht korrekt.
  

  FIXME: Beim Umschalten von DrawMode Tex -> Flat werden manchmal die Transp. Polys
         nicht mehr angezeigt. Scheint nur aufzutreten, wenn Alpha Texturen in
		 der Szene sind (oder nur dyn vob polys mit transparenz?)



  -	The mipmapping implementation within Voodoo Graphics computes a Level-Of-Detail (LOD) value per pixel. This LOD value is roughly the log (base 2) of
	the square root of the number of texels under the pixel. LOD represents the mipmap level to use when sampling the texture
	->!Mipmapstufen werden bei glide durch die Anzahl der Texel pro interpoliertem Pixel auf dem Polygon
	ermittelt, nicht durch die Tiefeninformation, 
    Darum:
    Pro Textur sollte einstellbar sein, welche mipmap-bias Werte, welche Mipmap-Stufen, welche
    Farbtiefe, welcher Filtermodus und welcher Mipmap-Modus genommen wird -> Editor für den Spacer,
    (siehe auch mipmap.c)

If your W coordinates do not span a large range of the fog table, a visual artifact called fog "bands" may be evident. Fog bands are basically Mach bands
which are an optical illusion caused by a sudden change in the first derivative of a slowly changing visible parameter such as color. Your eye perceives the
sudden change in the first derivative and interprets it as an "edge" and thus you see a banding effect. Since the fog table produces a piece-wise linear
approximation for an exponential curve, there is the potential for Mach bands. The solution is to make sure that you are using the entire fog table so that the
change in slope from one pair of entries to the the next pair of entries is as small as possible. For example, instead of implementing dense fog by varying the
table entries from 0 to 255 within the first 40 entries of the fog table, stretch things out and vary the entries from 0 to 255 over the entire fog table and then
multiply W by 64 (the value of world W for index=63 divided by world W for index=39). 
Note that you must scale W by 64 before computing xScreen=x/w, yScreen=y/w, sow=s/w, tow=t/w and oow=1/w. 

If your W coordinates span a range larger than the fog table, e.g. [1,128000], you can simply divide W by 2. Notice how the first quarter of the fog table is
devoted to W in the range [1,16]. If most of your scene is beyond W=16 you can divide W by 16 and adjust the fog table entries accordingly. This expands the
range of the fog table by 16. Fog table entry 0 is used for all pixels whose W<=1.0 (oow>= 1.0) and fog table entry 63 is used for all pixels whose
W>=52428 (oow<=.000019). 
Andrew wrote:
>I was looking at the specs for the Voodoo2 and Voodoo3 and both list
>bump-mapping as a supported hardware feature, yet I havn't found any
>documentation describing how to use this feature. I read through the
>information that comes with glide, but found no mention of bump mapping.
>
>If anyone has some infoCache on how to access this feature, glide or opengl,
>please let me know.

I can do the kind of bumb mapping you see in the donut demo. Create a
texture with an alpha channel, where the alpha values are the bumps. Select
this texture for rendering in both TMUs, and subtract them, but let one of
them be slightly offset relative to the other, and render the polygon with
alpha as "color", that is, discard the color and let alpha replace the color
value. This is it. If you only have one TMU, you'll have to do more passes,
but it's possible- I've done it. I've also done it in OpenGL. It is a bit
trickier, at least if GL_EXT_blend_subtract is not available. And I've
heard, but I haven't checked myself, that this kind of bumpmapping is
supported in DirectX6.

After rendering the bump-map, add a lightmap or a gouraud shaded triangle to
the image (a g-shaded triangle can be added in the same pass on a VooDoo2),
and then do a multiplicative blend with the base texture.


There is also another way to produce bumpmapping on 3dfx hardware, based on
palletized textures. You can create an 8-bit texture where you encode the
"bumps" as normal vectors encoded as 4 bit tilt in s & t direction respectively.
Then for each frame you calculate how the light will fall on all 256 such
vectors (16 tilt cases in s & t resp.) and update the pallette.

/mats


My engine will definately support bumpmapping!

oGrE wrote:
> 
> > > Also, is there a way to switch back to windows when I get a breakpoint in
> > > the debugger? Is this somehow related to the previous problem? I do have
> > > to monitors, even 2 computers (for remote debugging) but for simple apps
> > > (like rotating cube) I would rather avoid the hassle.
> > >
> >
> > The simple way is just to hit Ctrl-F9.
> 
> What does that do?

The end result of it is that it takes you back to windows.  However
i've only ever been able to get this to work when i'm running the
app through msvc++.....in which, it just so happens that the Ctrl-F9 
shortcut is assigned to DebugEnableBreakpoint. So i'm guessing that has 
something to do with it.  

The other thing that you could do (though I have never done it myself)
is process the BreakPointHit event inside msvc++ (look in the help under
BreakpointHit)...This lets you write an event handler that will always 
be called once the break point is hit..
You could just get this code to always disable the passthru or
something...


Instead of using sstWinClose or grFinish try grGlideShutdown and have
(FXU32)GetDesktopWindow() as your first parameter for sstWinOpen



Imron.
Mattias
BackProject


Himmelspolys müssen legale z Werte in den Vertices haben, sonst funzt das Mipmapping nicht
Mipmapping-Probs: Im Testlevel verschwindet die Wasser-Textur manchmal, genauso das Himmelspoly ??

*********************************************************************************

Rev: 
0.47c: zTRnd_Stats polysRendered/trisRendererd hinzugefügt,mul2 blending, mul blending modes mit iterated vertex alpha, chromakeying entfernt (ausser lfb)
0.45 : Vid_BlitGfx: Clipping implementiert
0.44f: implementation new Method: zCTex_RndGlide::HasAlphaChannel()
0.44d: implementation new Methods: ResetZTest, HasPassedZTest
0.44c: gamma range is now reasonable: 0..1
0.44b: gamma now defaults to 1.0 on all voodoos
0.43h: Spacer Draw Fix
0.43g: +2+ |AB-0032| Lightmaps: Compile mit Lightmaps bewirkt daß seltsame Farbeffekte generiert werden, aber keine Schatten
0.43f: Recompile failed fix. 
0.43e: dito
0.42b: VDFS Anpassung
0.42:  Cache Fix
0.41:  Angleich Ulfs Sourcen, Commandozeilen Parameter ENABLETASKSWITCH um Win95 Keys zuzulassen (Debug)
0.40:  Voodoo 3 support, Voodoo Banshee support(?), Texture Cache Fix, Vid_SetMode bis 1280x1024 )
0.39:  Fix zCTex_RndGlide::SetByArray
0.38c: Win95 Keys werden nur im Release Modus disabled. Ist wohl besser bei Breakpoints etc.
0.38b: 
  -Texturen die im Namen ein 16BIT enthalten werden auf jeden Fall in ein 16 Bit Format konvertiert
  -Dithering für Alpha geblendete Texturen ist ausgeschaltet
*********************************************************************************

  $Log:: /current_work/ZenGin/_Carsten/zRndGlide.cpp                            $
 * 
 * 15    21.07.00 18:29 Edenfeld
 * 
 * 14    21.07.00 17:04 Edenfeld
 * 
 * 13    21.07.00 15:34 Edenfeld
 * 
 * 12    14.07.00 13:44 Edenfeld
 * 
 * 11    3.07.00 12:30 Edenfeld
 * 
 * 10    9.06.00 13:46 Edenfeld
 * 
 * 9     24.05.00 19:22 Edenfeld
 * 
 * 8     22.05.00 15:27 Edenfeld
 * 
 * 7     9.05.00 21:32 Edenfeld
 * 
 * 6     7.05.00 20:41 Edenfeld
 * 
 * 5     2.05.00 17:41 Edenfeld
 * 
 * 4     2.05.00 15:50 Edenfeld
 * Get/SetTextureWrapEnabled()
 * 
 * 3     2.05.00 15:28 Edenfeld
 * DrawPolySimple
 * 
 * 2     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:15 Edenfeld
 * 
 * 30    19.04.00 13:10 Edenfeld
 * 
 * 29    12.04.00 18:29 Edenfeld
 * 
 * 28    21.03.00 12:52 Edenfeld
 * 
 * 27    16.03.00 21:57 Edenfeld
 * 
 * 26    16.03.00 13:50 Edenfeld
 * Anpassungen an Engine 0.88
 * 
 * 25    16.02.00 20:32 Edenfeld
 * 
 * 24    16.02.00 11:27 Edenfeld
 * 
 * 23    15.02.00 13:54 Edenfeld
 * 
 * 22    6.02.00 14:12 Edenfeld
 * 
 * 21    3.02.00 16:20 Edenfeld
 * zengin 0.86
 * 
 * 20    18.01.00 18:24 Edenfeld
 * HasAlphaChannel() aus zCTex_RndGlide entfernt
 * 
 * 19    11.01.00 14:58 Edenfeld
 * Texturverzerrer gefixed
 * 
 * 18    10.01.00 15:20 Edenfeld
 * zEngine 0.85 Anpassungen
 * 
 * 17    5.01.00 22:28 Edenfeld
 * 
 * 16    23.12.99 13:23 Edenfeld
 * 
 * 15    20.12.99 20:15 Edenfeld
 * 
 * 14    14.12.99 18:04 Edenfeld
 * 
 * 13    14.12.99 17:04 Edenfeld
 * zCTex_RndGlide::Draw Millenium Fix
 * 
 * 12    7.12.99 16:25 Edenfeld
 * 
 * 11    7.12.99 13:57 Edenfeld
 * 
 * 10    5.12.99 21:39 Edenfeld
 * 
 * 9     5.12.99 21:26 Edenfeld
 * Interface Änderungen (GetTextureInfo etc.)
 * 
 * 8     5.12.99 21:20 Edenfeld
 * 
 * 7     2.12.99 18:17 Edenf
 * 
 * 6     2.12.99 17:11 Edenf
 * GR048: Texturladen beschleunigt -> neue texconvert.lib nötig
*********************************************************************************/
#define GR_VERSION ("v0.50")

#include "zcore.h"
#include "zoption.h"
#include "zRndGlide.h"
#include "zRndGlide_Dib.h"
#include "zRndGlide_State.h"
#include "zRndGlide_Util.h"
#include "zRndGlide_Draw.h"
#include "zConsole.h"
#include "zDbgTools.h"
#include "zVideo_Win32.h"
#include "zWin32.h"
#include "zexceptionhandler.h"

#ifndef Lerp
#define Lerp(t, a, b) ( a + t * (b - a) ) 
#endif

#ifdef CHASE_DEBUG
	//#define _CHECK_TEXCACHE_
	#define _CDEB_HIGHREFRESH
#endif

#ifdef _CDEB_HIGHREFRESH
const GrScreenRefresh_t GR_DEFAULT_REFRESH_RATE = GR_REFRESH_120Hz;
#else
const GrScreenRefresh_t GR_DEFAULT_REFRESH_RATE = GR_REFRESH_60Hz;
#endif

// statics
static zBOOL Con_SetTexusVerboseLevel(const zSTRING &in, zSTRING &msg)
{
	zSTRING s = in;
	s.Upper();
	if ( s.PickWord(1, " ") == "TOGGLE" ) {
		if ( s.PickWord(2, " ") == "MIPALGO" ) {
			mipAlgo = !mipAlgo;
			if (mipAlgo) {
				msg = "Slow mipmapping algo enabled "; 
			} else {
				msg = "Fast and ugly mipmapping algo enabled"; 
			}
			return TRUE;
		} 
	}
	else if ( s.PickWord(1, " ") == "GRTEXSTAT" ) {
		zCTex_RndGlide::PrintCacheSlots();
		return TRUE;
	}
	return FALSE;
}

static void Exc_ReleaseRenderer()
{
	if (zrenderer) 
	{ 
		delete zrenderer; zrenderer = 0; 
	};
};


/********************************************************************************
 Constructor zCRnd_Glide
*********************************************************************************/

zCRnd_Glide :: zCRnd_Glide() 
{

	zERR_MESSAGE(5,zERR_BEGIN,zSTRING("C: 3dfx-glide Renderer Implementation ") + zSTRING(GR_VERSION));  

	zexhnd.AddUnhandledExceptionReleaseCallback   ( Exc_ReleaseRenderer ); 

	vidInit();														// Initialise video

	char version[80];

	fullRes				= actRes = GR_RESOLUTION_640x480;
	vid_xdim			= 640;
	vid_ydim			= 480;
	vid_bpp				= 16;
	nearZ				= 0;
	farZ				= 65535;
	scrMode				= zRND_SCRMODE_FULLSCREEN;
	fogType				= zRND_FOG_FALLOFF_LINEAR;
	rushBased			= FALSE;
	fogEnabled			= FALSE;
	waitRetrace			= TRUE;
	gamma				= 0.2F;
	frameBuf.size		= sizeof(GrLfbInfo_t);
	lfbLocked			= FALSE;
	cc					= FALSE;
	maxTimeDefragPartial= 0;
	dib					= 0;
	alphaSrc			= zRND_ALPHA_SOURCE_MATERIAL;
	alphaBlendFunc		= zRND_ALPHA_FUNC_MAT_DEFAULT;
	zBias				= 0;
	writeZBuffer		= TRUE;
	zBufCompareFunc		= zRND_ZBUFFER_CMP_LESS;
	polySortMode		= zRND_SORT_ZBUFFER;
	lightMapBilerpFilter= TRUE;
	bilerpFilter		= TRUE;
	wrapEnabled			= TRUE;
	usingTextureAlpha	= FALSE;
	pixelWriteEn		= TRUE;
	fullScreenOnly		= FALSE;
	polysRendered		= 0;
	trisRendered		= 0;
	lightMapsRendered	= 0;
	colorBuf			= 0;
	
	zSTRING s;
	if (zoptions->Parm("SHOWSPLASH")) s = zSTRING("FX_GLIDE_NO_SPLASH=1")+zSTRING(";"); 
	else s = zSTRING("FX_GLIDE_NO_SPLASH=")+zSTRING(";");

	_putenv( s.ToChar() );

	// disable possible gamma override via enviroment variables
	s = zSTRING("SST_RGAMMA=");
	_putenv( s.ToChar() );
	s = zSTRING("SST_GGAMMA=");
	_putenv( s.ToChar() );
	s = zSTRING("SST_BGAMMA=");
	_putenv( s.ToChar() );

	s = zSTRING("SSTH3_RGAMMA=");
	_putenv( s.ToChar() );
	s = zSTRING("SSTH3_GGAMMA=");
	_putenv( s.ToChar() );
	s = zSTRING("SSTH3_BGAMMA=");
	_putenv( s.ToChar() );
	
	s = zSTRING("SSTV2_RGAMMA=");
	_putenv( s.ToChar() );
	s = zSTRING("SSTV2_GGAMMA=");
	_putenv( s.ToChar() );
	s = zSTRING("SSTV2_BGAMMA=");
	_putenv( s.ToChar() );

	#ifdef _CDEB_HIGHREFRESH
	s = zSTRING("SST_SCREENREFRESH=120");
	_putenv( s.ToChar() );
	s = zSTRING("SSTV2_SCREENREFRESH=120");
	_putenv( s.ToChar() );
	s = zSTRING("SSTV2_REFRESH_640x480=120");
	_putenv( s.ToChar() );
	s = zSTRING("SSTV2_REFRESH_800x600=100");
	_putenv( s.ToChar() );
	#endif

	if (LoadGlideSymbols() == -1) zerr.Report(zERR_FATAL,8000,"C: zRndGlide.cpp(zCRndGlide::zCRndGlide): glide2x.dll not found");
	
	memset((void*)&hwconfig,0,sizeof(hwconfig)) ;
	grSstQueryBoards(&hwconfig);
	 
	if (hwconfig.num_sst > 0)
		zerr.Message("C: "+zSTRING(hwconfig.num_sst)+" Voodoo Board(s) detected");
	else
		zerr.Report (zERR_FATAL, 7000, "C:zRndGlide(zCRndGlide::zCRndGlide):No 3dfx-hardware present !\n");

	grGlideGetVersion(version);
	zerr.Message("C: Initializing glide version " + zSTRING(version) );
	grGlideInit();

	if (grSstQueryHardware(&hwconfig)) {
		grSstSelect(0);

		switch (hwconfig.SSTs[0].type) {
		case GR_SSTTYPE_SST96:
			zerr.Message("C: Voodoo Rush detected... ");
			deviceInfo.deviceName = "Voodoo Rush";
			cap.totalFrameBufferMem = hwconfig.SSTs[0].sstBoard.SST96Config.fbRam;
			cap.totalTextureMem		= hwconfig.SSTs[0].sstBoard.SST96Config.nTexelfx * hwconfig.SSTs[0].sstBoard.SST96Config.tmuConfig.tmuRam;
			cap.alphaBlendAddAvail		= TRUE;
			cap.alphaBlendMulAvail		= TRUE;
			cap.chromaAvail				= TRUE;
			cap.lfbAlphaBlendAvail		= FALSE;
			cap.lfbChromaAvail			= FALSE;
			cap.numTexPerPass			= 1;
			rushBased=TRUE;
			break;
		case GR_SSTTYPE_VOODOO:
			if ( hwconfig.SSTs[0].sstBoard.VoodooConfig.fbiRev < 0x100 ) {
				zerr.Message("C: Voodoo Graphics detected... ");
				deviceInfo.deviceName = "Voodoo Graphics";
				cap.numTexPerPass		= hwconfig.SSTs[0].sstBoard.VoodooConfig.nTexelfx;
				cap.totalFrameBufferMem = hwconfig.SSTs[0].sstBoard.VoodooConfig.fbRam;
				cap.totalTextureMem		= hwconfig.SSTs[0].sstBoard.VoodooConfig.nTexelfx * 
										  hwconfig.SSTs[0].sstBoard.VoodooConfig.tmuConfig[0].tmuRam;
			}
			else if ( hwconfig.SSTs[0].sstBoard.VoodooConfig.fbiRev & 0x1000 ) {
				zerr.Message("C: Voodoo Banshee/Voodoo 3 detected... ");
				deviceInfo.deviceName = "Voodoo Banshee/Voodoo 3";
				cap.numTexPerPass		= hwconfig.SSTs[0].sstBoard.VoodooConfig.nTexelfx;
				cap.totalFrameBufferMem = hwconfig.SSTs[0].sstBoard.VoodooConfig.fbRam;
				cap.totalTextureMem		= hwconfig.SSTs[0].sstBoard.VoodooConfig.nTexelfx * 
										  hwconfig.SSTs[0].sstBoard.VoodooConfig.tmuConfig[0].tmuRam;
				rushBased = TRUE;
				fullScreenOnly		= TRUE;
			}
			else if ( hwconfig.SSTs[0].sstBoard.VoodooConfig.fbiRev & 0x100 ) {
				zerr.Message("C: Voodoo 2 detected... Go for it!");
				deviceInfo.deviceName = "Voodoo 2";
				cap.numTexPerPass			= hwconfig.SSTs[0].sstBoard.Voodoo2Config.nTexelfx;
				cap.totalFrameBufferMem		= hwconfig.SSTs[0].sstBoard.Voodoo2Config.fbRam;  // nope: count each tmu's available ram
				cap.totalTextureMem			= hwconfig.SSTs[0].sstBoard.Voodoo2Config.nTexelfx * 
											  hwconfig.SSTs[0].sstBoard.Voodoo2Config.tmuConfig[0].tmuRam;
			}

			cap.alphaBlendAddAvail		= TRUE;
			cap.alphaBlendMulAvail		= TRUE;
			cap.chromaAvail				= TRUE;
			cap.lfbAlphaBlendAvail		= TRUE;
			cap.lfbChromaAvail			= TRUE;
			break;
		case GR_SSTTYPE_Voodoo2:
			zerr.Message("C: Voodoo 2 detected... Go for it!");
			deviceInfo.deviceName = "Voodoo 2";
			cap.numTexPerPass			= hwconfig.SSTs[0].sstBoard.Voodoo2Config.nTexelfx;
			cap.totalFrameBufferMem		= hwconfig.SSTs[0].sstBoard.Voodoo2Config.fbRam;  // nope: count each tmu's available ram
			cap.totalTextureMem			= hwconfig.SSTs[0].sstBoard.Voodoo2Config.nTexelfx * 
										  hwconfig.SSTs[0].sstBoard.Voodoo2Config.tmuConfig[0].tmuRam;
			cap.alphaBlendAddAvail		= TRUE;
			cap.alphaBlendMulAvail		= TRUE;
			cap.chromaAvail				= TRUE;
			cap.lfbAlphaBlendAvail		= TRUE;
			cap.lfbChromaAvail			= TRUE;
 
			break;
		case GR_SSTTYPE_AT3D:
			zerr.Message("C: Voodoo AT3D detected... ");
			deviceInfo.deviceName = "Voodoo AT3D";
			cap.numTexPerPass			= 1;
			cap.totalFrameBufferMem		= 2;
			cap.totalTextureMem			= 2;										  
			cap.alphaBlendAddAvail		= TRUE;
			cap.alphaBlendMulAvail		= TRUE;
			cap.chromaAvail				= TRUE;
			cap.lfbAlphaBlendAvail		= FALSE;
			cap.lfbChromaAvail			= FALSE;
			rushBased=TRUE;
			break;
		default:
			zerr.Report(zERR_WARN,8000,"C: Unknown Voodoo detected... switching to compatibility mode!");
			deviceInfo.deviceName = "Unknown Voodoo";
			cap.numTexPerPass			= 1;
			cap.totalFrameBufferMem		= 2;
			cap.totalTextureMem			= 2;										  
			cap.alphaBlendAddAvail		= TRUE;
			cap.alphaBlendMulAvail		= TRUE;
			cap.chromaAvail				= TRUE;
			cap.lfbAlphaBlendAvail		= FALSE;
			cap.lfbChromaAvail			= FALSE;
			rushBased=TRUE;
			break;
		}
	}
	else zerr.Report (zERR_FATAL, 7000, "C:zRndGlide(zCRndGlide::zCRndGlide):No Voodoo Graphics System found !\n");

	zerr.Message("C: Total Framebuffer memory: " + zSTRING(cap.totalFrameBufferMem));
	zerr.Message("C: Total Texture     memory: " + zSTRING(cap.totalTextureMem)    );
	
	if (cap.totalFrameBufferMem < 4) maxTableRes = 3; 
	else if (cap.totalFrameBufferMem < 5 ) maxTableRes = 4;
	else if (cap.totalFrameBufferMem < 9 ) maxTableRes = 5;
	else if (cap.totalFrameBufferMem < 13 ) maxTableRes = 6;


	// Fill primitive vertices for 2d-drawing
	for (int i=0; i<4; i++) {
		p[i].oow=NEAREST_OOW;
		p[i].tmuvtx[GR_TMU0].sow = NEAREST_OOW;
		p[i].tmuvtx[GR_TMU0].tow = NEAREST_OOW;
		p[i].a  =MAX_ALPHA;

	}
	zCTex_RndGlide :: InitCache();

	memPerTMU = cap.totalTextureMem / cap.numTexPerPass ;

	zerr.Message("C: Total Texture memory available:" +  zSTRING(memPerTMU));

	zERR_MESSAGE(5,zERR_END,"C: Glide Init ok.");

	zcon.Register( "TOGGLE TEXUSDEBUG", "Toggles texus debugging output messages while converting textures" );
	zcon.AddEvalFunc( Con_SetTexusVerboseLevel );

	if (zoptions->Parm("MIPRANGE")) {
		zSTRING s = zoptions->ParmValue("MIPRANGE");
		mipRange	= s.PickWord(1," ").ToFloat();
		mipRangeInv	= 1/mipRange;
	}


}


/********************************************************************************
 Destructor zCRnd_Glide
********************************************************************************/

zCRnd_Glide :: ~zCRnd_Glide() 
{
	// in case of a crash in this destructor, avoid an endless loop
	zexhnd.RemoveUnhandledExceptionReleaseCallback(Exc_ReleaseRenderer);

	zERR_MESSAGE(5,0,"C: Shutting down glide ...");

	zCTex_RndGlide::ReleaseCache();

	grGlideShutdown();
	FreeGlideSymbols();

	EnableTaskSwitch();

	vidExit();														// Close video system
}

void zCRnd_Glide :: SetAlphaBlendFactor( const float &percentage )
{
	
	alphaF	  = percentage;
	actAlpha  = zFloat2Int(percentage * 255);
	grConstantColorValue( actAlpha );
	// Vorsicht: wenn irgendwo grConstantColorValue nicht nur die Alpha-Komponente
	// benutzt, werden diese hier überschrieben!
}

void zCRnd_Glide :: EnableChromaKeying	() 
{ 
	cc = TRUE;
//	grChromakeyMode(GR_CHROMAKEY_ENABLE) ; 
};
void zCRnd_Glide :: DisableChromaKeying	() 
{ 
	cc = FALSE;
//	grChromakeyMode(GR_CHROMAKEY_DISABLE); 
};

void zCRnd_Glide :: SetChromaKeyColor	(const zCOLOR &col) 
{ 
	chromaColor=
		(GrColor_t) col.GetRedByte() << 24 | (GrColor_t) col.GetGreenByte() << 16 | 
		(GrColor_t) col.GetBlueByte() << 8;
//		grChromakeyValue(col);
};

int  zCRnd_Glide :: GetChromaKeyColor(void) 
{ 
	return chromaColor; 
}; 




/********************************************************************************
 FUNCTION: CreateTexture
*********************************************************************************/
zCTexture* zCRnd_Glide::CreateTexture() 
{
	return zNEW( zCTex_RndGlide );
};




int zCRnd_Glide::HasCapability (const zTRnd_Capability c) const
{
	switch (c) {
	case zRND_CAP_MULTITEXTURE: 
		return FALSE;
		//return cap.numTexPerPass>=2;
		break;
	case zRND_CAP_ZTEST: 
		return TRUE;
		break;
	}

	return FALSE;
}

/********************************************************************************
 FUNCTION: BeginFrame
*********************************************************************************/

void zCRnd_Glide ::	BeginFrame			() 
{
	//if (zCTex_RndGlide :: IsFragmentedTexMemHw()) 
	//	zCTex_RndGlide :: DefragPartial( maxTimeDefragPartial, MAX_FRAG ); 

    #ifdef _CHECK_TEXCACHE_
	if (!zCTex_RndGlide::CheckCacheConsistency()) zerr.Report(zERR_WARN,8000,zSTRING("C: zRndGlide(zCTex_RndGlide::Download): Texture Cache corrupt!"));
	#endif
	
	ResetStatistics();

	zCTex_RndGlide :: NewFrame();

	if (!renderCameraActive) {  // tmp, default fog needs far clipping plane at startup
		renderCameraActive = TRUE;
		SetFogRange(nearZ,farZ,fogType);
		SetFog	   (fogEnabled);
	}

	vidSetFrameReady();

	polysRendered	= 0;
	trisRendered	= 0;
	lightMapsRendered=0;

	float zMAXEngine = 65535;
	if (zCCamera::activeCam) zMAXEngine = zCCamera::activeCam->GetFarClipZ();
	float zMINEngine = 60.0F;

	for( int t = 0; t<GR_MAXBUCKETS; t++ ) alphaPolyBucket[t] = NULL; 
	grBucketSize = 1.0f/(GR_MAXBUCKETS-1)*zMAXEngine; 

	if( grBucketSize<=0.000001 ) { 
		zerr.Warning( "C: BeginFrame: Bucket-Size <= 0.000001 !" ); 
		grBucketSize = 1.0; 
	} 

};

void zCRnd_Glide ::	EndFrame			() 
{
	//zCTex_RndGlide::ShowTexCache();
} ;



/********************************************************************************
 FUNCTION: SetFog
 DESC    : Enables / disables fogging as set up with SetFogRange
*********************************************************************************/
void zCRnd_Glide :: SetFog              (const zBOOL foggy)
{
	/* zRND_FOG_FALLOFF_LINEAR, zRND_FOG_FALLOFF_EXP, zRND_FOG_FALLOFF_EXP2 */
	fogEnabled = foggy;

	if (!renderCameraActive) return;

	if (foggy) grFogMode(GR_FOG_WITH_TABLE);
	else grFogMode(GR_FOG_DISABLE);

}

void  zCRnd_Glide :: SetFogRange(const float nearz, const float farz, const zTRnd_FogMode type) 
{
	nearZ = nearz;
	farZ  = farz;
	fogType=type;
	if (!renderCameraActive) return;

	guFogGenerateLinear(fog,nearZ,farZ);
	grFogTable(fog);
};


// =zCTex_RndGlide===============================================================

zCTex_RndGlide::zCTex_RndGlide () 
{
	reqLargeLOD		= GR_LOD_0;
	addrTexHw		= 0;
	age				= 0;
	sizeMipsCurrent = 0;
	file			= 0;
	next			= NULL;
	chromaTex		= FALSE;
	alphaTex		= FALSE;
	infoCache.data		= NULL;
	infoCache.largeLod	= GR_LOD_0;
	maxDetailTex    = FALSE;
	locked			= FALSE;
	lockedMode		= 0;
	palette			= NULL;
	importance		= 0;
	scaleX			= 0;
	scaleY			= 0;
	memset((void*)&infoSrc,0,sizeof(infoSrc));

};

zCTex_RndGlide::~zCTex_RndGlide () 
{
	CacheOut();
	ReleaseData();	
};

zBOOL zCRnd_Glide::SupportsTextureFormat(const zTRnd_TextureFormat texFormat)
{
	switch (texFormat) {
	case zRND_TEX_FORMAT_ARGB_4444:	
	case zRND_TEX_FORMAT_ARGB_1555: 
	case zRND_TEX_FORMAT_RGB_565:
	case zRND_TEX_FORMAT_PAL_8:
		return TRUE;
	default:
		return FALSE;
	}

	return FALSE;
};

void zCTex_RndGlide :: ConvertPaletteToGlideFormat()
{
	zERR_ASSERT(palette);
	zBYTE *pal = (zBYTE*)palette;
	for (int i=0; i<256; i++) {
		int j = i*3;
		infoSrc.table.palette.data[i] = pal[j+2]<<16 | pal[j+1]<<8 | pal[j+0]<<0;
	}

};		

// accessing contents (read, write, readOnly, writeOnly)
zBOOL	zCTex_RndGlide::Lock(int lockMode)      
{ 
	if (locked && lockedMode == lockMode) {
		zERR_WARNING("C: zCTex_RndGlide::Lock(): Texture already locked!");
		return TRUE;
	}

	if (lockMode & zTEX_LOCK_READ) CacheIn(-1);

	lockedMode = lockMode;
	locked     = TRUE;
	return TRUE;
}; 

zBOOL   zCTex_RndGlide::Unlock()                                                                      
{ 
	if (!locked) {
		zERR_WARNING("C: zCTex_RndGlide::Unlock(): Texture already unlocked!");
		return TRUE;
	}
	locked     = FALSE;

	if ( (lockedMode & zTEX_LOCK_WRITE) && (infoTex.texFormat == zRND_TEX_FORMAT_PAL_8) ) {
		// palette has been possible modified -> Update internal 3dfx palette
		ConvertPaletteToGlideFormat();
	}

	this->SetCacheState(zRES_CACHED_IN);
	return TRUE;
};
//

zBOOL    zCTex_RndGlide::SetTextureInfo(const zCTextureInfo& texInfo)          
{ 
	zERR_ASSERT(locked && (lockedMode & zTEX_LOCK_WRITE));
	infoTex = texInfo;
	// alte texturdaten entfernen
	ReleaseResourceData();
	memset(&infoSrc,0,sizeof(infoSrc));
	
	if (texInfo.sizeX == 0 || texInfo.sizeY == 0) {
		zerr.Warning("C: zCTex_RndGlide::SetTextureInfo: Dimensions of texture are 0");
		return FALSE;
	}

	// fill in infoCache structure 
	int largerDim;
	if ( texInfo.sizeX == texInfo.sizeY ) {
		scaleX = scaleY = 256.0F; 
		infoSrc.header.aspect_ratio = GR_ASPECT_1x1; 
		largerDim		 = texInfo.sizeX ;
	}
	else if ( texInfo.sizeY > texInfo.sizeX ){
		scaleY = 256.0F;
		scaleX = (float)(texInfo.sizeX * 256.0F)  / texInfo.sizeY;
		if ( texInfo.sizeY>>1 == texInfo.sizeX) infoSrc.header.aspect_ratio = GR_ASPECT_1x2; else
		if ( texInfo.sizeY>>2 == texInfo.sizeX) infoSrc.header.aspect_ratio = GR_ASPECT_1x4; else
		if ( texInfo.sizeY>>3 == texInfo.sizeX) infoSrc.header.aspect_ratio = GR_ASPECT_1x8; 
		largerDim = texInfo.sizeY;
	}
	else {
		scaleX = 256.0F;
		scaleY = (float) (texInfo.sizeY * 256.0F) / texInfo.sizeX;
		if ( texInfo.sizeX>>1 == texInfo.sizeY) infoSrc.header.aspect_ratio = GR_ASPECT_2x1; else
		if ( texInfo.sizeX>>2 == texInfo.sizeY) infoSrc.header.aspect_ratio = GR_ASPECT_4x1; else
		if ( texInfo.sizeX>>3 == texInfo.sizeY) infoSrc.header.aspect_ratio = GR_ASPECT_8x1; 
		largerDim = texInfo.sizeX;
	}

	switch (largerDim) {
		case 256:  infoSrc.header.large_lod = GR_LOD_256; break;
		case 128:  infoSrc.header.large_lod = GR_LOD_128; break;
		case  64:  infoSrc.header.large_lod = GR_LOD_64 ; break;
		case  32:  infoSrc.header.large_lod = GR_LOD_32 ; break;
		case  16:  infoSrc.header.large_lod = GR_LOD_16 ; break;
		case   8:  infoSrc.header.large_lod = GR_LOD_8  ; break;
		case   4:  infoSrc.header.large_lod = GR_LOD_4  ; break;
		case   2:  infoSrc.header.large_lod = GR_LOD_2  ; break;
		case   1:  infoSrc.header.large_lod = GR_LOD_1  ; break;
		default :  zerr.Report(zERR_FATAL, 8000, "C: zCTex_RndGlide :: SetTextureInfo(): Dimensions of texture are not base of 2"); break;
	}

	infoSrc.header.small_lod= infoSrc.header.large_lod+texInfo.numMipMap-1;  

	// FIXME: chromaTex fehlt noch!
	switch(texInfo.texFormat) {
	case zRND_TEX_FORMAT_ARGB_4444:		infoSrc.header.format=GR_TEXFMT_ARGB_4444; alphaTex = TRUE; break;
	case zRND_TEX_FORMAT_ARGB_1555:		infoSrc.header.format=GR_TEXFMT_ARGB_1555; alphaTex = TRUE; break;
	case zRND_TEX_FORMAT_RGB_565:		infoSrc.header.format=GR_TEXFMT_RGB_565	 ; break;
	case zRND_TEX_FORMAT_PAL_8:			infoSrc.header.format=GR_TEXFMT_P_8;	   break;
	default:							zERR_FATAL("C: zCTex_RndGlide::SetTextureInfo(): Format not supported!");
	}

	infoSrc.mem_required = grTexCalcMemRequired(infoSrc.header.small_lod,infoSrc.header.large_lod,infoSrc.header.aspect_ratio,infoSrc.header.format);
	infoSrc.data				   = malloc(infoSrc.mem_required);;
	
	// reserve mem for engine format palette buffer -> memory order RGB
	if (palette == NULL) {
		if (texInfo.texFormat == zRND_TEX_FORMAT_PAL_8) {
			palette= malloc(3*256);			
			memset(palette,255,3*256);
		}
	}

	if (infoSrc.data==NULL) zerr.Report (zERR_FATAL, 7001, "C: zCTex_RndGlide::SetTextureInfo(): Not enough memory ");

	infoSrc.header.height		   = texInfo.sizeY;
	infoSrc.header.width		   = texInfo.sizeX;

	// fill in dynamic cache infoCache struct
	infoCache.smallLod				   = infoSrc.header.small_lod;
	infoCache.aspectRatio			   = infoSrc.header.aspect_ratio;
	infoCache.format					   = infoSrc.header.format;

	return TRUE;
}

void*    zCTex_RndGlide::GetPaletteBuffer        ()                                      
{ 
	if (infoSrc.header.format != GR_TEXFMT_P_8) return NULL;
	zERR_ASSERT(locked && (lockedMode != 0));
	return palette;
};

int zCTex_RndGlide::GetMipSize(int mipMapNr) 
{
	zERR_ASSERT(infoSrc.header.large_lod+mipMapNr <= infoSrc.header.small_lod);
	int lod = infoSrc.header.large_lod+mipMapNr;
	return grTexCalcMemRequired(lod,lod,infoCache.aspectRatio,infoCache.format);
};

zBOOL	zCTex_RndGlide::GetTextureBuffer	(int mipMapNr, void* &buffer, int &pitchXBytes)
{ 
	zERR_ASSERT(locked && (lockedMode != 0));
	zERR_ASSERT(infoSrc.header.large_lod+mipMapNr <= infoSrc.header.small_lod);
	int size = grTexCalcMemRequired(infoSrc.header.small_lod,infoSrc.header.large_lod+mipMapNr,infoCache.aspectRatio,infoCache.format);
	buffer = (zBYTE*)infoSrc.data + (infoSrc.mem_required - size);
	pitchXBytes = (infoTex.sizeX >> mipMapNr) * zFloat2Int(zrenderer->GetTexFormatInfo (infoTex.texFormat).bytesPerPixel);

	return TRUE;
};
// 
zCTextureInfo   zCTex_RndGlide::GetTextureInfo()                                      
{ 
	CacheIn(-1);
	return infoTex;
};

zBOOL  zCTex_RndGlide::CopyPaletteDataTo(void* destBuffer)                      
{ 
	if (infoSrc.header.format != GR_TEXFMT_P_8) return FALSE;
	zERR_ASSERT(locked && (lockedMode & zTEX_LOCK_READ));
	memcpy(destBuffer,palette,3*256);
	return TRUE; 
}

zBOOL  zCTex_RndGlide::CopyTextureDataTo   (int mipMapNr, void* destBuffer, int destPitchXBytes)
{
	zERR_ASSERT(destBuffer);
	zERR_ASSERT(locked && (lockedMode & zTEX_LOCK_READ));
	zERR_ASSERT(infoSrc.header.large_lod+mipMapNr <= infoSrc.header.small_lod);

	void *srcBuffer; int srcPitch;
	GetTextureBuffer(mipMapNr,srcBuffer,srcPitch);

	// hmm, hier weiss man leider nicht, ob die textur, aus die der destBuffer stammt auch gelockt ist...
	if (destPitchXBytes == srcPitch) {
		memcpy(destBuffer,srcBuffer,GetMipSize(mipMapNr)); 
	}
	else {
        // Copy a texture from src to dst, dst has a pitch != dstWidth
		zBYTE *dst = (zBYTE *)destBuffer;
		zBYTE *src = (zBYTE *)srcBuffer;

		int height = infoSrc.header.height>>mipMapNr;

		while (height--) {
			memcpy((void*)dst,(void*)src,srcPitch);
            dst += destPitchXBytes;
            src += srcPitch;
        }
	}

	return TRUE; 
};



/***********************************************************
  Video Related 
***********************************************************/
extern HWND winHandle;

static zDWORD oldVidX	= 640;
static zDWORD oldVidY	= 480;
static zDWORD oldBpp	= 16;
static zBOOL  firstTime = TRUE;

static GrScreenResolution_t oldRes = GR_RESOLUTION_640x480;


/********************************************************************************
 FUNCTION: zCRnd_Glide :: Vid_FullScreen
 DESC    : Switchs to fullscreen/windowed mode. Uses windows emulation for normal
		   3dfx-cards
 PARAM   : screen Mode
*********************************************************************************/

void zCRnd_Glide :: Vid_SetScreenMode(zTRnd_ScreenMode mode) 
{
	if (mode == scrMode) return;
	if (mode == zRND_SCRMODE_FULLSCREEN) zerr.Message("C: Switching to fullscreen mode ..."); else
	if (mode == zRND_SCRMODE_HIDE) zerr.Message("C: Disabling 3d display         ..."); else
							   zerr.Message("C: Switching to windowed mode   ..."); 	


	switch( mode ) {

	case zRND_SCRMODE_HIDE:
		CloseWin(); 
		grSstControl(GR_CONTROL_DEACTIVATE);
		EnableTaskSwitch();

		break;
	case zRND_SCRMODE_WINDOWED:

		if (scrMode == zRND_SCRMODE_FULLSCREEN || scrMode == zRND_SCRMODE_HIDE) {

			float x,y;
			tlGetDimsByConst(actRes,&x,&y);
			if (!CreateWin((int)x,(int)y,16)) {
				zerr.Report(zERR_WARN,8000,"C: Window mode not supported by Grade");
				return;
			}

			if (rushBased) {  // Voodoo Rush/Banshee/Voodoo3

				GrState state;
				grGlideGetState(&state);
				grSstWinClose();
				if (!grSstWinOpen((FxU32)winHandle,GR_RESOLUTION_NONE,GR_DEFAULT_REFRESH_RATE,GR_COLORFORMAT_RGBA,GR_ORIGIN_UPPER_LEFT,2,1) ) {
					zerr.Report (zERR_WARN, 7000, "C: zRndGlide(zCRnd_Glide::Vid_FullScreen) : Mode not supported");
					grSstWinOpen((FxU32)winHandle,actRes,GR_DEFAULT_REFRESH_RATE,GR_COLORFORMAT_RGBA,GR_ORIGIN_UPPER_LEFT,2,1);
					grGlideSetState(&state);
					return;
				}
			
				grGlideSetState(&state);
			}
			else  // normal Voodoo
			{
				// deactivate 3d-display
				grSstControl(GR_CONTROL_DEACTIVATE);

			}

		}
		EnableTaskSwitch();
		break;

	case  zRND_SCRMODE_FULLSCREEN:
			
		if (rushBased) {  // Voodoo Rush

			GrState state;
			grGlideGetState(&state);
			grSstWinClose();
			if (!grSstWinOpen((FxU32)winHandle,actRes,GR_DEFAULT_REFRESH_RATE,GR_COLORFORMAT_RGBA,GR_ORIGIN_UPPER_LEFT,2,1))
				zerr.Report (zERR_FATAL, 7000, "C: zRndGlide(zCRnd_Glide::Vid_FullScreen) : Could not open screen !\n");
			
			grGlideSetState(&state);

		}
		else  // normal Voodoo
		{
			CloseWin();
			// activate 3d-display
			grSstControl(GR_CONTROL_ACTIVATE);
		}
		DisableTaskSwitch();

		break;
	}

	scrMode = mode;

}

zBOOL zCRnd_Glide :: Vid_ScreenDump(const zSTRING &fileName)
{
	zoptions->ChangeDir(DIR_ROOT);
	zBOOL flag = ScreenDumpTGA( fileName.ToChar(), vid_xdim, vid_ydim );
	if (!flag) zerr.Report(zERR_WARN,8000,zSTRING("C: zRndGlide (zCRnd_Glide::ScreenDump) : Could not dump screen to :")+ fileName);
	else zerr.Message( zSTRING("C: Dumping screen to ") + fileName );

	return flag;

}


int	zCRnd_Glide :: Vid_GetNumDevices()
{
	if (hwconfig.num_sst > 0) return 1; else return 0;
};


zBOOL zCRnd_Glide :: Vid_SetDevice			(int deviceNr)
{
	return TRUE;
};

zBOOL zCRnd_Glide ::  Vid_GetDeviceInfo		(zTRnd_DeviceInfo& deviceInfo, int deviceNr)
{
	deviceInfo = this->deviceInfo;
	return TRUE;
};


int	 zCRnd_Glide ::	Vid_GetNumModes			()
{
	return maxTableRes;
};

zBOOL zCRnd_Glide :: Vid_GetModeInfo			(zTRnd_VidModeInfo& modeInfo, int modeNr)
{
	modeInfo.bpp = 16;
	modeInfo.fullscreenOnly = fullScreenOnly;
	modeInfo.xdim= (int)resTable[modeNr].width;
	modeInfo.ydim= (int)resTable[modeNr].height;
	return TRUE;
};

int	zCRnd_Glide :: Vid_GetActiveModeNr		()
{
	return tlGetTableSlotByConst(actRes);
};

zBOOL zCRnd_Glide :: Vid_SetMode				(int modeNr, HWND *winHandle)
{
	return SetMode((int)resTable[modeNr].width,(int)resTable[modeNr].height,16);
};

zBOOL zCRnd_Glide :: SetMode(int x,int y,int bpp)
{

	GrScreenResolution_t res= actRes;
	zBOOL changed			= FALSE;

	oldVidX = vid_xdim;
	oldVidY = vid_ydim;
	oldBpp  = vid_bpp;
	oldRes  = actRes;

	tlGetConstByDims( &res, &x, &y );
	
	if (res != actRes || firstTime) {
		
		if (scrMode == zRND_SCRMODE_WINDOWED) {

			if (rushBased) {
				if (CreateWin(x,y,bpp) && grSstWinOpen((FxU32)winHandle,GR_RESOLUTION_NONE,GR_DEFAULT_REFRESH_RATE,GR_COLORFORMAT_RGBA,GR_ORIGIN_UPPER_LEFT,2,1)) 
					changed = TRUE;

			} 
			else {

				if ( grSstWinOpen(0,res,GR_DEFAULT_REFRESH_RATE,GR_COLORFORMAT_RGBA,GR_ORIGIN_UPPER_LEFT,2,1 ))
				if ( CreateWin(x,y,bpp) ) {

					grSstControl(GR_CONTROL_DEACTIVATE);
					changed = TRUE;
				}

			}

		} 
		else { // fullScreen

			CreateWin(0,0,16);
			if (!rushBased) {
				CloseWin();
				if (grSstWinOpen(0,res,GR_DEFAULT_REFRESH_RATE,GR_COLORFORMAT_RGBA,GR_ORIGIN_UPPER_LEFT,2,1)) changed = TRUE;

			} 
			else {
				if (grSstWinOpen((FxU32)winHandle,res,GR_DEFAULT_REFRESH_RATE,GR_COLORFORMAT_RGBA,GR_ORIGIN_UPPER_LEFT,2,1)) changed = TRUE;
			}

		}

		if (scrMode == zRND_SCRMODE_HIDE) {
			CloseWin();
			grSstControl(GR_CONTROL_DEACTIVATE);
		}

		if (!changed) {
			zerr.Report (zERR_WARN, 7000, "C: zRndGlide(zCRnd_Glide::Vid_SetMode) : Mode not supported");
			CreateWin(oldVidX,oldVidY,oldBpp);
			FxU32 handle; GrScreenResolution_t resolution;
			resolution  = actRes;
			actTableRes = tlGetTableSlotByConst(actRes);
			if (rushBased) {
				handle = (FxU32)winHandle ; 
				if (scrMode == zRND_SCRMODE_WINDOWED) resolution = GR_RESOLUTION_NONE;
			} else handle = 0;
			grSstWinOpen(handle,resolution,GR_DEFAULT_REFRESH_RATE,GR_COLORFORMAT_RGBA,GR_ORIGIN_UPPER_LEFT,2,1);
		} 
		else {
			actRes = res;
			actTableRes = tlGetTableSlotByConst(actRes);
		}

		// Initialize the Combine Units 

		if (firstTime) { 
			firstTime			= FALSE; 
			polyDrawMode		= zRND_DRAW_MATERIAL;
			pDrawMode			= zRND_DRAW_MATERIAL;
			gamma				= 0.2F;
			nearZ				= 450.0F;
			farZ				= 1450.0F;
			fogType				= zRND_FOG_FALLOFF_LINEAR;
			fogEnabled			= TRUE;
			waitRetrace			= TRUE;
			zBias				= 0;
			writeZBuffer		= TRUE;

			GetFrameProfileValues(); 
			SetRenderMode		 (zRND_MODE_1_PASS_VERT_LIGHT);
		}

		SetPolyDrawMode (polyDrawMode);  // Color Combine
		SetPolySortMode (polySortMode);
		SetZBias( zBias );
		SetZBufferWriteEnabled( writeZBuffer );
		SetZBufferCompare( zBufCompareFunc );
		SetAlphaFunc	(alphaFunc,TRUE);
		SetAlphaSource	(usingTextureAlpha,TRUE);
		SetDrawMode		(zCAM_DRAW_TEX,TRUE);
		SetBilerpFilterEnabled(bilerpFilter);

		switch (pDrawMode) {
			case zRND_DRAW_FLAT:
			case zRND_DRAW_WIRE:
			grColorCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
						GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_NONE,FXFALSE);
			break;
		case zRND_DRAW_MATERIAL:
			grColorCombine(GR_COMBINE_FUNCTION_SCALE_OTHER,GR_COMBINE_FACTOR_LOCAL,
 						GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_TEXTURE,FXFALSE);
			break;
		}
		
		
		SetPixelWriteEnabled(pixelWriteEn);

		grTexCombine( GR_TMU0,GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
					  GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
					  FXFALSE,FXFALSE );

		// Set texture related topics 
		grTexMipMapMode(GR_TMU0,GR_MIPMAP_NEAREST_DITHER,FXFALSE);
		grTexFilterMode(GR_TMU0,GR_TEXTUREFILTER_BILINEAR,GR_TEXTUREFILTER_BILINEAR);
		grTexNCCTable(GR_TMU0,GR_TEXTABLE_NCC0);
		SetTextureWrapEnabled(GetTextureWrapEnabled());
		grTexLodBiasValue(GR_TMU0,-0.4F);
		Vid_SetGammaCorrection	(gamma);

		// Init depth buffer 
		grDepthBufferMode(GR_DEPTHBUFFER_WBUFFER);
		grDepthBufferFunction(GR_CMP_LESS);
		grDepthMask(FXTRUE);   // Enable depth-buffering

		grLfbConstantDepth(GR_WDEPTHVALUE_NEAREST);	

		// clear screen
		zCOLOR bCol; bCol.SetRGB(0,0,0);
		Vid_Clear(bCol);
		Vid_Blit();

		SetFogRange(nearZ,farZ,fogType);
		grFogColorValue(BACKGROUND_COL);
		SetFog(fogEnabled);
	}

	vid_xdim = x;
	vid_ydim = y;

	if (scrMode == zRND_SCRMODE_FULLSCREEN) DisableTaskSwitch();

	if (!changed) return FALSE;
	return TRUE;

}


void	zCRnd_Glide :: Vid_Clear(zCOLOR &col, int clearTarget)
{
	GrColor_t grColor=
		(GrColor_t) col.GetRedByte() << 24 | (GrColor_t) col.GetGreenByte() << 16 | 
		(GrColor_t) col.GetBlueByte() << 8;

	if (clearTarget & zRND_CLEAR_ZBUFFER) {
		grDepthMask(FXTRUE); 
	}
	else grDepthMask(FXFALSE);

	if (clearTarget & zRND_CLEAR_FRAMEBUFFER) {
		grColorMask(FXTRUE,FXFALSE); 
	}
	else grColorMask(FXFALSE,FXFALSE); 

	grBufferClear(grColor ,0,GR_WDEPTHVALUE_FARTHEST); 

	grDepthMask(writeZBuffer);
	grColorMask(pixelWriteEn,FXFALSE);
};
/********************************************************************************
 FUNCTION: Vid_Blit
 DESC    : swaps front-/backbuffer, blits Backbuffer to window in windowed mode 
*********************************************************************************/

void zCRnd_Glide :: Vid_Blit(int xofs, int yofs)
{
	if (scrMode == zRND_SCRMODE_FULLSCREEN || scrMode == zRND_SCRMODE_HIDE || rushBased) {
		grBufferSwap(waitRetrace); 
	}
	else
	{
		short *data = (short *)dib->GetBuffer();	// Get the framebuffer for our DIB

		if (data) {
			GetRect((zBYTE*)dib->GetBuffer(),dib->GetWidth(),dib->GetHeight(),dib->GetWidth()*2,0,0);	
			dib->Update();
		}
	}

}

void zCRnd_Glide ::	Vid_SetLfbAlphaFunc		(const zTRnd_AlphaBlendFunc &func) 
{
	SetAlphaFunc(func);
}


/********************************************************************************
 FUNCTION: Vid_BlitRect
 DESC    : Blits Rectangle to backbuffer
*********************************************************************************/
void zCRnd_Glide :: Vid_BlitRect(zBYTE *data, int width, int height, int xd, int yd,int opacity) 
{
	if (cc) {
		grChromakeyMode(GR_CHROMAKEY_ENABLE);
		grChromakeyValue(chromaColor);
	}
	zBOOL locked = lfbLocked;
	zWORD *src = (zWORD *)data;

	// ************
	// Los Clippos
	// ************
	
	int xwidth = width;
	int yheight= height;
	if (xd<0) {
		src   -= xd;
		xwidth += xd;
		xd     = 0;
	}
	if (yd<0) {
		src   -= yd*xwidth;
		yheight+= yd;
		yd     = 0;
	}

	if (yd+yheight>vid_ydim) {
		yheight = zMax(int(0),int(vid_ydim - yd));
	}

	if (xd+xwidth>vid_xdim) { 
		xwidth = zMax(int(0),int(vid_xdim - xd));
	}

	if ( (opacity == 255 || cap.lfbAlphaBlendAvail==FALSE)) { // no alpha blending 
		// FIXME: blend func kann auch additiv sein...

		Vid_Unlock();

		if (!grLfbWriteRegion( GR_BUFFER_BACKBUFFER, xd, yd, GR_LFB_SRC_FMT_565, 
								xwidth, yheight, width<<1 ,src) )
			zerr.Report(zERR_WARN,7000,"C:zRndGlide(zCRnd_Glide::Vid_BlitGfx):BlitRect failed.");

		if (locked) Vid_Lock();

	}
	else {

		grConstantColorValue(opacity);

		Vid_Lock();

        // Copy a rectangular region from src to dst, each with different strides.
		int	 dstStride = vid_pitch>>1;
        int  srcStride = width;

		zWORD *dst = (zWORD *)colorBuf + (vid_pitch*yd>>1) + xd;

		while (yheight--) {
            int i;
			for (i=0; i<xwidth; i++) dst[i] = src[i];
            dst += dstStride;
            src += srcStride;
        }
		
		if (!locked) Vid_Unlock();
	} 	

	if (cc) grChromakeyMode(GR_CHROMAKEY_DISABLE);
}



/********************************************************************************
 FUNCTION: GetRect
 DESC    : Copies Rectangle from backbuffer to dest. buffer
*********************************************************************************/
void zCRnd_Glide :: GetRect	(zBYTE *dest, int width, int height, int pitch, int xd, int yd) 
{
	if (!grLfbReadRegion( GR_BUFFER_BACKBUFFER, xd, yd, width, height, pitch,(void *)dest )) 
		zerr.Report(zERR_WARN,7000,"C:zRndGlide(zCRnd_Glide::Vid_GetRect):GetRect failed.");

};

/********************************************************************************
 FUNCTION: Vid_BeginLfbAccess
 DESC    : Call after Renderoperations & before LfbOperations to enable
		   textures & alpha during lfb access
*********************************************************************************/

void zCRnd_Glide :: Vid_BeginLfbAccess() // Call for beginning of Lfb-Access after all render operations
{
	return;			// obsolete

	if (lfbLoop) return; else lfbLoop = TRUE;
	if (lfbLocked) {
		zerr.Report(zERR_WARN,8000,"C: zRndGlide (zCRnd_Glide::Vid_BeginLfbAccess) : Framebuffer locked !");
		Vid_Unlock();
	}

	grGlideGetState(&lfbState);

	grDisableAllEffects();

	grColorCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
				   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_NONE,FXFALSE);

	grAlphaCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
				   GR_COMBINE_LOCAL_CONSTANT,GR_COMBINE_OTHER_NONE,FXFALSE );

	grAlphaBlendFunction(GR_BLEND_SRC_ALPHA, GR_BLEND_ONE_MINUS_SRC_ALPHA,  
						 GR_BLEND_ZERO,GR_BLEND_ZERO);            

	grLfbConstantAlpha(255);
	grConstantColorValue(255);


}


void zCRnd_Glide :: Vid_EndLfbAccess		()
{
	return;
	if (!lfbLoop) return; else lfbLoop = FALSE;
	grGlideSetState(&lfbState); 
}


/********************************************************************************
 FUNCTION: Vid_Lock
 DESC    : Locks the backbuffer for direct access
*********************************************************************************/
void  zCRnd_Glide :: Vid_Lock				()
{ 
	if (lfbLocked) return;

	if (cap.lfbChromaAvail) {

		if (!grLfbLock(GR_LFB_WRITE_ONLY , GR_BUFFER_BACKBUFFER, GR_LFBWRITEMODE_565,
					   GR_ORIGIN_UPPER_LEFT, GR_LFBBYPASS_ENABLE, &frameBuf )) {
			
			zerr.Report (zERR_WARN, 8001, "C: zCRnd_Glide::grLfbLock with pixel pipeline enabled failed. No transparency! ");
		
			if (!grLfbLock(GR_LFB_WRITE_ONLY , GR_BUFFER_BACKBUFFER, GR_LFBWRITEMODE_565,
						   GR_ORIGIN_UPPER_LEFT, GR_LFBBYPASS_DISABLE, &frameBuf )) {					
				zerr.Report (zERR_WARN, 8001, "C: zCRnd_Glide::grLfbLock failed");
				vid_pitch = 0;
				colorBuf  = NULL;
				return;
			}

		}
	}
	else {  // Rush cannot enable pixel-pipeline
		if (!grLfbLock(GR_LFB_WRITE_ONLY , GR_BUFFER_BACKBUFFER, GR_LFBWRITEMODE_565,
					   GR_ORIGIN_UPPER_LEFT, GR_LFBBYPASS_DISABLE, &frameBuf )) {					
			zerr.Report (zERR_WARN, 8001, "C: zCRnd_Glide::grLfbLock failed");
			vid_pitch = 0;
			colorBuf  = NULL;
			return;
		}
	}

	vid_pitch	= frameBuf.strideInBytes;
	colorBuf	= (zBYTE *)frameBuf.lfbPtr;
	lfbLocked	= TRUE;

};


/********************************************************************************
 FUNCTION: Vid_Unlock
 DESC    : Unlocks the previous locked buffer
*********************************************************************************/

void zCRnd_Glide ::	Vid_Unlock				() 
{ 
	if (!lfbLocked) return;
	grLfbUnlock(GR_LFB_WRITE_ONLY, GR_BUFFER_BACKBUFFER); 
	lfbLocked=FALSE;

};

void zCRnd_Glide :: Vid_SetGammaCorrection	(float value) 
{ 
	gamma = value; 
	zerr.Message("C: gamma: " + zSTRING(Lerp(value,0.75F,2)));
	grGammaCorrectionValue(Lerp(value,0.75F,2));
}


/********************************************************************************
 FUNCTION: static CreateWindow
 DESC    : Called to preopen a window 
*********************************************************************************/
zBOOL zCRnd_Glide :: CreateWin(const int x, const int y, const int bpp)
{
	zBOOL res;

    VIDMODE NewMode;
	vid_xdim	= x;
	vid_ydim	= y;
	vid_bpp		= bpp;
    
    // Set Values
    memcpy(&NewMode,&VideoModeCur,sizeof(VIDMODE));
    NewMode.si.Width        = x;
    NewMode.si.Height       = y;
    NewMode.si.BPP          = bpp;
    NewMode.hwModeType      = VIDMODE_DIB;
    
    if (!vidSetMode  (&NewMode)) {
		res = FALSE; 
		zerr.Report(zERR_WARN,7000,"failed to open window with x: " + zSTRING(x) + " y: "+ zSTRING(y));
	} else {
		res = TRUE;
		zERR_MESSAGE(10,0,"opened window with x: " + zSTRING(x) + " y: "+ zSTRING(y));
	}

	VIDEO_INFO vidInfo;
	// Prepare video config (set up callbacks, etc.)
	memZero(&vidInfo, sizeof(vidInfo));				// Wipe out structure
	vidInfo.bHideMenu			= TRUE;
	vidInfo.bDisableMenuKeys	= TRUE;				// Disable menu keys
	vidInfo.bOnlyFullScreen		= FALSE;			// Only operate on fullscreen
	vidInfo.bDisableAltEnter	= TRUE;	
	vidInfo.bDisableCtrlAltDel	= TRUE;
	vidInfo.dwShowBitDepths		= 1 | 2 | 8;		// Show 8, 16 and 32 bit color depths
	vidInfo.dwEnableBitDepths	= 1 | 2 | 8;		// Enable 8 and 32 bit color depths
	vidInfo.dwStretch			= VIDSTRETCH_USER;	// Variable size
	vidInfo.fnCheckVMode		= 0;	// -> Callback to Check modes to add
	vidInfo.fnSetVideoMode		= 0;		// -> Callback for Video mode	*/
	vidSetModeEx(&vidInfo);							// Set video mode caps

	sysSetFocus();  //OLD
	winHandle = GetActiveWindow();

	if (dib) { delete dib; dib =0; };

	if (!rushBased) {
		RECT rect;
		GetClientRect(winHandle, &rect);
		RECT r = {0,0,vid_xdim,vid_ydim};	// Create the DIB the size of the video mode
		dib = zNEW( CDIBSection16(winHandle,&r) );	// Create a 16bpp DIB section
	}

	return res;

};

void	zCRnd_Glide :: CloseWin()
{

    VIDMODE NewMode;
    
    // Set Values
    memcpy(&NewMode,&VideoModeCur,sizeof(VIDMODE));
    NewMode.si.Width        = 0;
    NewMode.si.Height       = 0;
    NewMode.si.BPP          = 16;
    NewMode.hwModeType      = VIDMODE_ANYWINDOWED;
    
    vidSetMode  (&NewMode);

	VIDEO_INFO vidInfo;
	// Prepare video config (set up callbacks, etc.)
	memZero(&vidInfo, sizeof(vidInfo));				// Wipe out structure
	vidInfo.bHideMenu			= TRUE;
	vidInfo.bDisableMenuKeys	= TRUE;				// Disable menu keys
	vidInfo.bOnlyFullScreen		= FALSE;			// Only operate on fullscreen
	vidInfo.bDisableAltEnter	= TRUE;	
	vidInfo.bDisableCtrlAltDel	= TRUE;
	vidInfo.dwShowBitDepths		= 1 | 2 | 8;		// Show 8, 16 and 32 bit color depths
	vidInfo.dwEnableBitDepths	= 1 | 2 | 8;		// Enable 8 and 32 bit color depths
	vidInfo.dwStretch			= VIDSTRETCH_USER;	// Variable size
	vidInfo.fnCheckVMode		= 0;	// -> Callback to Check modes to add
	vidInfo.fnSetVideoMode		= 0;		// -> Callback for Video mode	*/
	vidSetModeEx(&vidInfo);							// Set video mode caps

	if (dib) { delete dib; dib =0; };
	winHandle = GetActiveWindow();
	SetFocus(winHandle);
};
