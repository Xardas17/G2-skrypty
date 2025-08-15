#include "zcore.h"
#include "zDbgTools.h"
#include "zViewBase.h"
#include "zView.h"


zCView *messages;
zBOOL showDebug = FALSE;
	
//#define CHASE_DEBUG
#ifdef CHASE_DEBUG

int row = 900;

void D_Reset()
{
	static zBOOL beenHere = FALSE;

	if (!beenHere) {
		 messages = zNEW( zCView(5200,0,8191,8191) );	screen  -> InsertItem(messages);
	 	 //messages -> Setflags(VIEW_TRANS | VIEW_NOCLIP);
		 //messages -> InsertBack	(GFX_BLACK);
		 //messages -> SetChromaKey (GFX_BLACK);
		 screen   -> InsertItem(messages);
		 beenHere = TRUE;
	}
	
	row = 900;
	messages->ClrPrintwin();

}


void D_Print(const zPOINT3 &p,const zSTRING &msg,const TDebug mode)
{

	zSTRING ds = msg + zSTRING(" x: ") + zSTRING (p[VX]) + zSTRING(" y: ") + zSTRING (p[VY]) + zSTRING(" z: ") + zSTRING (p[VZ]);

	switch (mode) {
	case D_SPY:
		zERR_MESSAGE(4,0,"C: DBG:" + ds );
		break;
	case D_SCREEN:
		screen -> Print(0,row,(ds + zSTRING("\n")).ToChar()); 
		row += 300;
		break;
	case D_WIN:
		if (showDebug) messages->Printwin( ds + zSTRING("\n"));
		break;
	}
}
void D_Print(const float &f,const zSTRING &msg,const TDebug mode)
{

	zSTRING ds = msg + zSTRING (f);

	switch (mode) {
	case D_SPY:
		zERR_MESSAGE(4,0, "C: DBG:"+ ds );
		break;
	case D_SCREEN:
		screen -> Print(0,row,(ds+ zSTRING("\n")).ToChar());
		row += 300;
		break;
	case D_WIN:
		if (showDebug) messages->Printwin( ds + zSTRING("\n") );
		break;
	}
}

void D_Print(zSTRING &ds,const TDebug mode)
{

	switch (mode) {
	case D_SPY:
		zERR_MESSAGE(4,0, "C: DBG:"+ ds );
		break;
	case D_SCREEN:
		screen -> Print(0,row,(ds+ zSTRING("\n")).ToChar());
		row += 300;
		break;
	case D_WIN:
		if (showDebug) messages->Printwin( ds + zSTRING("\n") );
		break;
	}
}

void D_Print(char *ds,const int x, const int y)
{
	if (!showDebug) return;
	screen -> Print(x,y,(zSTRING(ds)+ zSTRING("\n")).ToChar());
}

void D_PrintA(char *ds,const int x, const int y)
{
	screen -> Print(x,y,(zSTRING(ds)+ zSTRING("\n")).ToChar());
}

void D_Print(char *ds,const TDebug mode)
{
	D_Print(zSTRING(ds),mode);
}

			   

void D_Print3D( const zPOINT3 &coord, zSTRING &s, const zCOLOR &col )
{
	zPOINT3 pt = zCCamera::activeCam->Transform( coord );
	float x,y;
	zCCamera::activeCam->Project( &pt, x,y );
//	zCOLOR color = screen->GetFontColor();
//	screen->SetFontColor(col);

	if (pt[VZ] > 1) {
		screen->Print( int(x*8191/zrenderer->vid_xdim), int(y*8191/zrenderer->vid_ydim), s + zSTRING("\n"));
//		screen->SetFontColor(color);
	}

}



void D_DrawPolyWire( const zCPolygon &poly, const zCOLOR &col ) 
{

/*	if (&poly==NULL) return;
	zrenderer->SetPolyDrawMode(zRND_DRAW_WIRE);
	grDepthBufferMode(GR_DEPTHBUFFER_DISABLE);
	GrVertex v[zMAX_POLY_CLIP_VERTS];

	float r=(float) ((col>>11) & 0x1f ) * 255.0F / 31.0F;
	float g=(float) ((col>>5)  & 0x3f ) * 255.0F / 63.0F;
	float b=(float) ( col		 & 0x1f ) * 255.0F / 31.0F;


	for (int i=0; i<poly.numClipVert; i++) {

		v[i].oow = (poly.clipVert[i]->vertCamSpaceZInv);
		

		v[i].x	 = poly.clipVert[i]->vertScrX ; 
		v[i].y	 = poly.clipVert[i]->vertScrY ; 
		v[i].r	 = r;
		v[i].g	 = g;
		v[i].b	 = b;
		v[i].a	 = 100;
		
		if ( v[i].x > zrenderer->vid_xdim || v[i].y > zrenderer->vid_ydim ||
			 v[i].x < 0 || v[i].y < 0 ) {
			zerr.Report(zERR_WARN, 8000,"C: ctools ( DrawPolyWire ) : coords out of clipping range ");
			grDepthBufferMode(GR_DEPTHBUFFER_WBUFFER);
	
			// Nicht vollständig
			zrenderer->SetPolyDrawMode(zRND_DRAW_MATERIAL);
			return;
		}

		v[i].x	+= SNAPCONST ; 
		v[i].y	+= SNAPCONST ; 
	}

	for (i=0; i<poly.numClipVert-1; i++) grAADrawLine(&v[i], &v[i+1]);
	grAADrawLine(&v[poly.numClipVert-1],&v[0]);
	
	grDepthBufferMode(GR_DEPTHBUFFER_WBUFFER);
	
	// Nicht vollständig
	zrenderer->SetPolyDrawMode(zRND_DRAW_MATERIAL);
*/
}

void D_ClrWin()
{
	messages->ClrPrintwin(); 
}

#else

void D_Reset() {};
void D_Print(const zPOINT3 &p,const zSTRING &msg,const TDebug mode ) {};
void D_Print(const float &f,const zSTRING &msg,const TDebug mode) {};
void D_Print(zSTRING &ds,const TDebug mode) {};
void D_Print(char *ds,const TDebug mode) {};
void D_Print(char *ds,const int x, const int y) {};
void D_PrintA(char *ds,const int x, const int y) {};
void D_Print3D( const zPOINT3 &coord, zSTRING &s , const zCOLOR  &col){};
void D_DrawPolyWire( const zCPolygon &poly, const zCOLOR &col){};
void D_ClrWin(){};

#endif

