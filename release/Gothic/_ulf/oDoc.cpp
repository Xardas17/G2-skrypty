/******************************************************************************** 
 
     $Workfile:: oDoc.cpp             $                $Date:: 6.10.00 15:51    $
     $Revision:: 14                   $             $Modtime:: 6.10.00 15:18    $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oDoc.cpp $
 * 
 * 14    6.10.00 15:51 Keskenti
 * 
 * 13    20.09.00 22:51 Wohlers
 * 
 * 12    19.09.00 17:11 Wohlers
 * 
 * 11    2.08.00 14:25 Wohlers
 * 
 * 10    21.07.00 15:34 Wohlers
 * 
 * 9     21.07.00 14:43 Wohlers
 * 
 * 8     19.07.00 12:45 Wohlers
 * 0.88
 * 
 * 7     5.07.00 12:20 Wohlers
 * 
 * 6     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 5     10.05.00 23:27 Wohlers
 * Gothic 0.81a
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 5     6.05.00 18:08 Wohlers
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 6     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 5     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 4     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "oDoc.h"
#include "oGame.h"
#include "oWorld.h"
#include "oNpc.h"

#include "zInput.h"
#include "zOption.h"

oCDoc*	document			= NULL;
zCView* oCDoc :: posView	= NULL;

oCDoc :: oCDoc (const zSTRING& name)
{
	int sizex	= 0;
	int sizey	= 0;
	
	SetAlphaBlendFunc(zRND_ALPHA_FUNC_BLEND);

	InsertBack	(name);
	zCTexture* back = GetBackTex();

	if (back) {
		// normale Größe holen und Skalierungaktor berechnen
		sizex = back->GetTextureInfo().refSizeX;
		sizey = back->GetTextureInfo().refSizeY;
		if ((sizex==0) || (sizey==0)) zERR_FAULT("U:DOC: Texture Error. Dimension is 0. "+name);

		// Skalierungsfaktor X berechnen
		if (sizex > zrenderer->vid_xdim) {
			scalex		= zREAL(zrenderer->vid_xdim) / sizex;
			sizex		= zrenderer->vid_xdim;
		} else {
			scalex		= 1.0;		
		}
		// Skalierungsfaktor Y berechnen
		if (sizey > zrenderer->vid_ydim) {
			scaley		= zREAL(zrenderer->vid_ydim) / sizey;
			sizey		= zrenderer->vid_ydim;
		} else {
			scaley		= 1.0;		
		}
	}

	// Centered
	int x1 = (VIEW_VXMAX - screen->anx(sizex)) / 2;
	int y1 = (VIEW_VYMAX - screen->any(sizey)) / 2;

	// Pos und resizen
	SetPos	(x1,y1);
	SetSize	(screen->anx(sizex),screen->any(sizey));
		
	DefPrintwin			(100,100,VIEW_VXMAX-100,VIEW_VYMAX-100);
	SetEnableHandleEvent(TRUE);
	SetHandleEventTop	();

	// Close inventory ?
	oCNpc* npc = ogame->GetSelfPlayerVob();
	if (npc && npc->inventory2.IsOpen()) npc->CloseInventory();

	// Disable Player Movements
	if (npc) npc->SetMovLock(TRUE);

	map_gameCoPerPixelx	= 0.0f;
	map_gameStartx		= 0.0f;	
	map_gameCoPerPixely = 0.0f;
	map_gameStarty		= 0.0f;
	pixelStartx			= 0.0f;
	pixelStarty			= 0.0f;
	
	Show();
}

oCDoc :: ~oCDoc()
{
	if (this==document) document = NULL;
	
	// Backgfx wird in ~zCView deleted
	oCNpc* npc = ogame->GetSelfPlayerVob();
	if (npc && !npc->inventory2.IsOpen()) npc->SetMovLock(FALSE);
	
	delete posView;
	posView = NULL;
}

void oCDoc :: Show()
{
	screen->InsertItem(this);
}

zBOOL oCDoc :: HandleEvent(int key)		
{ 
	if (zinput->KeyToggled(key)) delete(this); 
	
//	if ((key & KEY_RELEASE)==0) delete (this);
	return TRUE; 
};

// *********************************************************************
// Landkarte - Koordinaten anzeigen
// *********************************************************************

void oCDoc :: MapInitCoordinates(zREAL gcox1, zREAL gcoy1, zREAL px1, zREAL py1, zREAL gcox2, zREAL gcoy2, zREAL px2, zREAL py2)
{
	map_gameCoPerPixelx	= (gcox2 - gcox1) / (px2 - px1);
	map_gameStartx		= gcox1;
	pixelStartx			= px1;

	map_gameCoPerPixely	= (gcoy2 - gcoy1) / (py2 - py1);
	map_gameStarty		= gcoy1;
	pixelStarty			= py1;
}

void oCDoc :: MapDrawCoordinates(zREAL gcox, zREAL gcoy)
{
	// Levelname identisch ?
	if (ogame->GetGameWorld()->GetWorldName()!=levelName) return;
	if (!IsVisible()) return;
	
	if (!posView) {
		posView  = zNEW( zCView (0,0,8192,8192,VIEW_ITEM) );
		posView -> InsertBack ("MAPPOS.TGA");		
	}
	
	int px = int ((pixelStartx + (gcox - map_gameStartx) / map_gameCoPerPixelx) * scalex);
	int py = int ((pixelStarty + (gcoy - map_gameStarty) / map_gameCoPerPixely) * scaley);
	
	px = anx(px);
	py = any(py);

	// Grö0e der Textur ermitteln
	zCTexture* tex = posView->GetBackTex();
	if (tex) {
		int sizex = anx	(tex->GetTextureInfo().refSizeX);
		int sizey = any	(tex->GetTextureInfo().refSizeY);
		posView->Init	(px, py, px+sizex, py+sizey, VIEW_ITEM );
		InsertItem		(posView);
		posView->SetPos	(px-sizex/2,py-sizey/2);
	};
};

void oCDoc :: SetLevelName(const zSTRING& _levelName)
{
	levelName = _levelName;
	levelName.Upper();
	// Endung ignorieren
	int p = levelName.Search(".");
	if (p>=0) levelName.Delete(p);
};
