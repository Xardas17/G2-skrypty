/******************************************************************************** 
 
     $Workfile:: zModel.cpp           $                $Date:: 15.03.01 2:17    $
     $Revision:: 58                   $             $Modtime:: 14.03.01 21:14   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Animierte hierarchische 3D-Models (Instanzen, Ani-Player)
   (Segmented Heirarchy characters, Single Mesh Skeletal Deformation)
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zModel.cpp $
 * 
 * 58    15.03.01 2:17 Hildebrandt
 * 
 * 57    16.02.01 12:49 Moos
 * Eisgolem-Crashfix
 * 
 * 56    15.02.01 18:50 Hildebrandt
 * 
 * 55    15.02.01 3:38 Hildebrandt
 * 
 * 54    15.02.01 1:19 Hildebrandt
 * 
 * 53    13.02.01 19:34 Hildebrandt
 * 
 * 52    13.02.01 16:19 Hildebrandt
 * 
 * 51    10.02.01 4:11 Hildebrandt
 * 
 * 50    9.02.01 23:29 Hildebrandt
 * 
 * 49    9.02.01 2:35 Hildebrandt
 * 
 * 48    7.02.01 20:29 Hildebrandt
 * 
 * 47    5.02.01 19:13 Hildebrandt
 * 
 * 46    1.02.01 19:58 Moos
 * 
 * 45    30.01.01 5:16 Hildebrandt
 * 
 * 44    25.01.01 5:07 Hildebrandt
 * 
 * 43    23.01.01 22:49 Hildebrandt
 * 
 * 42    17.01.01 19:20 Hildebrandt
 *  
 * 41    17.01.01 18:17 Hildebrandt
 * 
 * 40    17.01.01 18:01 Hildebrandt
 * 
 * 39    15.01.01 3:54 Hildebrandt
 * 
 * 38    11.01.01 18:45 Hildebrandt
 * 
 * 37    9.01.01 22:24 Hildebrandt
 * 
 * 36    8.01.01 17:55 Hildebrandt
 * 
 * 35    21.12.00 3:14 Hildebrandt
 * 
 * 34    20.12.00 3:01 Hildebrandt
 * 
 * 32    13.12.00 22:31 Hildebrandt
 * 
 * 31    4.12.00 18:27 Hildebrandt
 * 
 * 30    4.12.00 18:23 Moos
 * 
 * 29    17.11.00 19:29 Moos
 * 
 * 28    17.11.00 1:29 Hildebrandt
 * 
 * 27    8.11.00 22:05 Hildebrandt
 * 
 * 26    3.11.00 19:02 Hildebrandt
 * 
 * 25    10.10.00 19:38 Moos
 * 
 * 24    9.10.00 21:03 Hildebrandt
 * 
 * 23    9.10.00 19:31 Moos
 * 
 * 22    5.10.00 16:22 Speckels
 * 
 * 21    21.09.00 21:20 Hildebrandt
 * zenGin 0.94
 * 
 * 20    13.09.00 21:24 Hildebrandt
 * 
 * 19    11.09.00 19:40 Speckels
 * 
 * 17    7.09.00 20:41 Hildebrandt
 * 
 * 16    5.09.00 21:45 Hildebrandt
 * 
 * 15    31.08.00 17:04 Hildebrandt
 * 
 * 14    29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 13    24.08.00 14:26 Hildebrandt
 * 
 * 12    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 11    21.07.00 15:11 Hildebrandt
 * 
 * 10    21.07.00 14:28 Hildebrandt
 * 
 * 9     6.07.00 13:45 Hildebrandt
 * 
 * 5     8.05.00 2:17 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 22    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 21    23.02.00 5:00 Hildebrandt
 * fixed AniCombine() memoverride (zCMobFire Crash)
 * 
 * 20    23.02.00 3:29 Hildebrandt
 * 
 * 19    23.02.00 1:19 Hildebrandt
 * 
 * 18    22.02.00 2:01 Hildebrandt
 * zenGin 087d
 * 
 * 17    18.02.00 1:39 Hildebrandt
 * 
 * 16    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 14    11.01.00 20:59 Hildebrandt
 * zenGin 085b
 * 
 * 13    10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 10    18.11.99 22:18 Hildebrandt
 * 
 * 9     16.11.99 19:49 Hildebrandt
 * 
 * 8     13.11.99 1:10 Hildebrandt
 * 
 * 7     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 58 $ ($Modtime: 14.03.01 21:14 $)

  
#define zMDL_BLEND_EASE

#ifdef ZENGINE_DEBUG
	#define zDEBUG_MDL_COLLECT_STATS
//	#define zDEBUG_MDL_DRAW_SKELETON
//	#define zDEBUG_MDL_DRAW_NODE_OBB
//	#define zDEBUG_MDL_SHOW_LERP
#endif

#include <zCore.h>

#include <zModel.h> 
#include <zWorld.h>
#include <zoption.h>
#include <zSound.h>
#include <zFile3d.h>
#include <zParticle.h>
#include <zMorphMesh.h>
#include <zBuffer.h>
#include <zGrafix.h>
#include <zView.h>
#include <zRenderLightContainer.h>
#include <zMemPool.h>
#include <zVertexTransform.h>

zCLASS_DEFINITION	(zCModel		, zCVisualAnimate	,	0,	0)
zCLASS_DEFINITION	(zCModelAni		, zCObject			,	0,	0)
//zCLASS_DEFINITION	(zCModelAni		, zCResource		,	zCLASS_FLAG_RESOURCE,	0)

/*
  - GlobalMemoryStatus
  - HOWTO: Overload New to Reduce Memory Fragmentation

  TODO:
  - einfache Models ohne Anis: .MDH und .MDM in einem File!	(eigentlich ja alle Models ohne 'DONT_USE_MESH'..)
  - ": einfache Angabe von '.ASC' sollte reichen! (kein .MDS)
	- 

  - Bugs:
	  - Turn(Layer20) und dabei cursorUp: warum bewegt sich Model hoch&runter ??
	  - 2 Anis auf 1 Layer Bug
	  x apply/remove HUMANS_SPRINT.MDS => "T_RUNR_RUN" (layer=0, numFrames=0), nextAni ? Crash nur im Release

*/

/*
 
  Problem: 
  Die Zeitverzoegerung zw. Tastendruck & Darstellung

  - Render

  *************************

  - AdvanceAnis
	- Calc this Frame
	- AdvanceAnis

  - DoAI => Tasten, StartAni

  *************************

  - Render
  
*/

/*

  - IDEE: 
    IDEE: 
   	BoundingBoxen nicht pro Frame, auch nicht komplett statisch, sondern pro ANIMATION (im voraus berechnen) !!
	(fuer die gesamte Ani ? fuer jeden Frame der Ani ? fuer das gesamte Model oder sogar jede Node ?)
  - OPTIMIERUNG:
	Statt OBB's fuer die Waffen/Limb Collision koennte man auch BBox3D's verwenden. OBB's und BBOX3D's naehern
	die Limbs fast gleich gut an (=> Limbs sind sinnvoll orientiert), BBOX3D's sind allerdings schneller.
	Sowohl fuer Node-Meshes als auch SoftSkin-Meshes.
	Das wuerde einen OBB-(Waffe => hier waere eine BBox3D zu grob) vs. BBox3D (Model-Nodes) noetig machen.


  - UpdateBBoxTree() : komplette Neuberechnung ist NICHT jeden Frame noetig !!
    Evtl so umstellen: Bei GetBBox3DNodeWorld() nur die erfragte Node-BBox berechnen & cachen, keine anderen..
  - nodeList: nach BreitenSuche sortieren => node-Tree durchläufe koennen ohne Rekursion auf der nodeList laufen !
*/

/*
*********************************************************************************************

  		// wrap
		m_frame -= (int)(m_frame / (pseqdesc->numframes - 1)) * (pseqdesc->numframes - 1);

*********************************************************************************************

NEU:

  body/head/hand-Mesh:
  - "Name_V1_C0.tga"	Variation, Color

  teeth
  - "teeth_v0.tga"

  - Jedes Mesh A hat einen Satz von Texture-Variationen, Textures eines Meshes B sollen nicht
    auf Mesh B verwendet werden.


Model Mesh/Texture-Kombinierbarkeit:
************************************

	void			SetModelTexture		(const int channel, const int varNr, 
										 const zSTRING& nodeNamePart	= "",
										 const zSTRING& skipNodeNamePart= "",
										 const zSTRING& texNamePart		= "",
										 zCTree<zCModelNodeInst>* node=0);
	void			SetModelMesh		(const zSTRING& s, const zBOOL delAllButSlotMeshes=FALSE);

- Bei Ruestungs-Wechsel muessen immer alle 3 ausgefuehrt werden: a), b), c) {i. oder ii.}.
  (Grund: es muessen erstmal alle Limbs geloescht werden, damit nicht Teile der alten Ruestung
   uebrig bleiben, wie z.B. 'Schulterklappen' o.Ä.).
- Beim Helm-Wechsel reicht die Ausfuehrung von c).
- Item-Ruestungen, die dasselbe ASC mit verschiedenen 'skin'-Nummern benutzen, muessen als 'visual'
  verschiedene 3DS-Meshes angegeben haben. Beispiel:
  1) item.visual		= "plateMailHaesslich.3ds"
     item.visual_worn	= "plateMail.ASC"
	 item.visual_skin	= 0;
  2) item.visual		= "plateMailSchick.3ds"
     item.visual_worn	= "plateMail.ASC"
	 item.visual_skin	= 1;
- ASC-Konventionen/Annahmen:
	- Der Kopf-Knoten		enthaelt das Wort "HEAD"
	- Der Helm/Haar-Knoten	enthaelt das Wort "HELMET"
	- Die Gesichts-Textur	enthaelt das Wort "FACE",
	  alle anderen Texturen des Kopfes enthalten dieses Wort NICHT.
	- Die Textur von Helm-Meshes wird nicht variiert.
- Hier die Mesh/Texture Setz-Aufrufe:  

	// a) Body==Armor/Skin
  	ani_model -> SetModelMesh		(visual_body, TRUE);
	ani_model -> SetModelTexture	(0, visual_bodySkin	, ""		, "", "");

	// b) Head/Face
  	ani_model -> SetModelMesh		(visual_head);
	ani_model -> SetModelTexture	(0, visual_faceNr	, "KOPF"	, "", "FACE");

	// c) Hair==Helmet/Hair-Cut
	// c.i)  Haare des Models, also kein Helm:
  	ani_model -> SetModelMesh		(visual_hair);				
	ani_model -> SetModelTexture	(0, visual_hairNr	, "HELMET"	, "", "");

	// c.ii) Model hat Helm, also keine Haare
	//		 achtung: beim Aufsetzen eines Helmes muss visual_hairNr=0 sein 
	//				  (Helme haben keine Texture-Variation, soweit ich weiss..)
  	ani_model -> SetModelMesh		(CItem.visual_worn);		// oder wie auch immer..
	ani_model -> SetModelTexture	(0, 0				, "HELMET"	, "", "");

- NEU: (30.5.99)

	- Script-Befehl im neuen Format:
		- Festlegung des Grundkoerpers oder "Nackt-Meshes":
			Mdl_SetVisualBody	(body_mesh_ASC_Name	, body_Tex_Var_Nr, body_Tex_Color_Nr, head_MMS_Name, head_Tex_Nr);
		- Ruestung:
			Mdl_SetArmor		(armor_ASC_Name		, armor_Tex_Var_Nr);

	// a) Body 
	model->SetModelMesh				(body_mesh_ASC_Name		, TRUE);			// mesh
	model->SetModelTexture			(0, body_Tex_Var_Nr		, "", "", "");		// skin variation
	model->SetModelTexture			(1, body_Tex_Color_Nr	, "", "", "");		// skin color

	// b) head
	// .. load mms, in model in richtige Node einfuegen..
	model->SetModelTexture			(0, head_Tex_Var_Nr		, "HEAD", "", "");	// head texture
	model->SetModelTexture			(1, body_Tex_Color_Nr	, "HEAD", "", "");	// head skin color

	// c) Helm
	// .. wie gehabt

	// d) Ruestungen 
	// (overlays, die ggfs. einzelne Teile des drunterliegenden Body-Meshes rauswerfen)
	// .. die Overlay-Code-Zahl des Ruestungs-ASC Files (z.B. "Hum_Armor_Leather_T19.ASC") wird 
	// in die Namen der einzelnen Koerper-Teile zerlegt. Diese Namen sind gleich den Material-Namen
	// der Polygone, die sich auf den entspr. Koerper-Regionen befinden. Per Angabe des Mat-Names
	// werden die entspr. Body-Polys als nicht zu rendern markiert.
	// Mehrere, aufeinanderfolgende Ruestungen werden akkumuliert und fuehren jeweils nicht dazu, dass 
	// bereits angelegte Ruestungen oder Teile davon rausgeworfen werden.

	model->SetModelMesh				(armor_ASC_Name			, FALSE);
	model->SetModelTexture			(0, armor_Tex_Var_Nr	, "", "", "");		// armor variation

===========================

	Anleitung (20.10.99):

	// a) Body/Armor
	// ASSERT: Texturen fuer den 'Body' enthalten den String "BODY", alle anderen nicht (analog fuer Ruestung/Armor)
	model->RemoveMeshLibAll			();										
	model->AppyMeshLib				(body_mesh_ASC_Name);										// mesh
	model->SetMeshLibTexture 		(body_mesh_ASC_Name	, 0, body_Tex_Var_Nr	, "BODY");		// skin tex variation
	model->SetMeshLibTexture 		(body_mesh_ASC_Name	, 1, body_Tex_Color_Nr	, "BODY");		// skin tex color
	model->SetMeshLibTexture 		(body_mesh_ASC_Name	, 0, armor_Tex_Var_Nr	, "ARMOR");		// armor tex variation

	// b) head
	// .. load mms, in model in richtige Node einfuegen..
	// ASSERT: Texturen fuer den 'Kopf' enthalten den String "HEAD", alle anderen nicht (analog fuer Zaehne/TEETH)
	headMesh->SetTextureVar			(0, head_Tex_Var_Nr		, "HEAD");		// head texture
	headMesh->SetTextureVar			(1, head_Tex_Color_Nr	, "HEAD");		// head skin color
	headMesh->SetTextureVar			(0, teeth_Tex_Var_Nr	, "TEETH");		// teeth texture

	// c) Helm
	// haben keine Textur-Variationen, einfach Helm in den entsprechenden Slot einsetzen

	// d) Ruestungen/Overlays	=> moeglich, aber nicht geplant
	// (overlays, werfen allerdings nichts drunterliegendes raus)
	model->AppyMeshLib				(overlay_mesh_ASC_Name);										// mesh
	model->SetMeshLibTexture 		(overlay_mesh_ASC_Name	, 0, overlay_Tex_Var_Nr	, "BODY");		// skin tex variation


    Nomenklatur:
	- Texturen auf Body/Armor-Mesh
		- Body-Texturen:		*BODY*_V0_C0.TGA			// keyword "body" muss enthalten sein   ("*" = wildcard)
		- Armor-Texturen:		*ARMOR*_V0.TGA				// keyword "armor" muss enthalten sein
	- Texturen auf Kopf:
		- Gesicht:				*HEAD*_V0_C0.TGA
		- Zaehne:				*TEETH*_V0.TGA
	- .MMS Namen fuer Koepfe:
		- hum_[KOPF_FORM]_[FRISUR].MMS						// beim Helm aufsetzen wird [FRISUR] durch "bald" ersetzt, andersrum analog

===========================
SHARING !

  - Ein MDM ist eine Einheit, in der beliebig viele NodeMeshes oder SoftSkins abgelegt sind. Der Name des
    MDM im Speicher und auf Platte ist gleich dem Namen des ASCs. MDMs koennen im Speicher geshared werden.
  - MeshLibs werfen Node-meshes raus, nicht aber SoftSkins
  - "halb schoen" geloest:
	- MDM Parsing benutzt das bestehende ModelProto => Proto muss dafuer von Meshes gesaeubert werden
	- Node-Mesh Handling/Textur Verwaltung dieser Meshes koennte ein wenig inkonsistent sein, wenn man 
	  ApplyMeshLib()/RemoveMeshLib() viel benutzt.

  wo stehen die TexVar Daten:
  - Nackt-Mesh		TexturVar in zCModelMeshLib (map<meshLib,zCModelTexAniState>)
  - Ruestung		TexturVar in zCModelMeshLib
  - Haende
  - Kopf			TexturVar in zCMorphMesh
  - Helm			TexturVar in Node

  - haben Helme Textur-Variationen ?

  algo:
  - zCModelMeshLib / zCModelTexAniState assoziativ in map speichern
  - vor dem Rendern die map durchlaufen und alle Texture Ani States setzen
  - nodeMeshes aus der Meshlib speichern ihren State in der map
  - einzelne nodeMeshes (durch SetNodeVisual gesetzt) speichern ihre States in den Nodes

  - HandWechsel 
	- Schwimmen/Tauchen, Neutral, 1H, 2H, PointAt
	- sind entweder an Anis gekoppelt oder werden vom Game fuer beliebige Zeitdauer eingestellt.
	- ueber NodeMeshes oder SoftSkin ?
	- nur ein Kanal ?

    - Ani-MeshLibs: werden einfach ueber AddMeshLib() und RemoveMeshLib() rein&rausgeworfen
	  - sollen Ani-MeshLibs 'layer' haben koennen ?
    - Haende ? zCModelMeshLib

Fazit:
  * HandWechsel unklar (nicht, ueber Mesh-Wechsel, ueber Bones ?) => a) Bones, b) Nicht
	=> "aniMeshLib" entfernen
  * Ruestungs-IDs NICHT

  => zCModel::meshLib entfernen, ::AddAniMeshLib() etc. obsolete ?

  Dann:
  - zCGame Klasse
  - zCWorld//zCVob
  
*********************************************************************************************

  Model-Beleuchtung:
  ******************

 
Subject: 
             RE: 3D Studio Max
 Resent-Date: 
             Mon, 30 Nov 1998 23:02:59 +0100 (CET)
 Resent-From: 
             crystal@spock.linux.it
        Date: 
             Mon, 30 Nov 1998 14:27:26 -0800
        From: 
             Alex Pfaffe <alexpf@microsoft.com>
          To: 
             "'crystal@spock.linux.it'" <crystal@spock.linux.it>
> VERTEX NORMALS
> 
> Another change to consider for the 3D sprite format:  
> Pre-calculated light
> normals, so you only have to multiply these normals by the sprite's
> transformation matrix to get the lighting normal (instead of 
> finding the
> normal of each adjacent triangle and averaging them in real time)
> 
> Quake MDLs have a light normal "index" which might hint at 
> some kind of
> shortcut regarding vertex based lighitng for 3D Sprites.
> 

Since Q1/Q2 models are always standing straight, ie they do not tumble but only
turn about the global Y axis (up/down).  (you could also use this technique
for static structures like walls etc, but it is unly useful on high polygon
count objects where you can assume the the polygons lighting would be approximately
the same if the polygon was as the centre of the object or at its true location).
You can precompute the normals of all vertices to fall into a normal group.
by mapping the vertices to one of the normal groups you only need an index.
You can use what ever mapping you want, but generally an Icosahedron or some
subdivided version of that would be easiest.  Since models can only turn about
one axis, you only need recalculate the lighting intensity for the icosahedron (12 vertices)
adjust it by the model's orientation about 1 axis, this could be done with ofsets maybe
and you're done, no cross products needed for 1400 polygons, only 12 or 24 depending on you
desired base model.
  You could also use a latitude/longitude method which may be easier to adjust for the model's
orientation, and there you might use 2 indeces, a lat/long which can be combined into a single 
integer again because you know the number of longitude groups. 
Eg.
Precompute the normals of all vertices on the model, find the lat/long class they fall into,
convert normal to angles to do this;  and then use

   iy = (lat+90)%20, ix = long%20, normalIndex = ix * 9 + iy, store normalIndex on the vertex

Then for each frame, compute the lighting that would affect the lat/long ball of 162 vertices.
The precomputed table could contain 18 long and 9 latitude groups which would be 162 entries,
the table can then be indexed using the precomputed table[(normalindex + (currYangle/20))%162].

What kind of values do the indexes have?  If we know that we may be able to deduce which scheme was used.

Alex
*********************************************************************************************
Model-Lighting:
Yeah, that one will be there. Perhaps you could use some sort of threshold
value, so that when the size of the object is small enough compared to the
distance to the light source (provided that the object is close enough to
actually recieve light), you'd just calculate the distance to the center of
the object
and use that value for every vertex. You still have to calculate the
dot-product, but
it would be some savings.

Also, perhaps I should try to group the vertexes somewhat with regards to
their
normal vector. Then I only have to calculate the light value for each group.
(I'm planning to display a 50 000 poly stormtrooper :)
*********************************************************************************************

  Interpolation 
  *************
     Having created your noise function, you will need to smooth out the values it returns. Again, you can choose any method you like, but some look
better than others. A standard interpolation function takes three inputs, a and b, the values to be interpolated between, and x which takes a value between 0
and 1. The Interpolation function returns a value between a and b based on the value x. When x equals 0, it returns a, and when x is 1, it returns b. When x
is between 0 and 1, it returns some value between a and b.

 Linear Interpolation: 
      Looks awful, like those cheap 'plasmas' that everyone uses to generate landscapes. It's a simple algorithm
 though, and I suppose would be excusable if you were trying to do perlin noise in realtime. 

      function Linear_Interpolate(a, b, x)
            return  a*(1-x) + b*x
      end of function
                                                                                                                    
 Cosine Interpolation: 
      This method gives a much smother curve than Linear Interpolation. It's clearly better and worth the effort if you
 can afford the very slight loss in speed. 

      function Cosine_Interpolate(a, b, x)
            ft = x * 3.1415927
            f = (1 - cos(ft)) * .5

            return  a*(1-f) + b*f
      end of function
                                                                                                                      
 Cubic Interpolation:
      This method gives very smooth results indeed, but you pay for it in speed. To be quite honest, I'm not sure if it
 would give noticeably better results than Cosine Interpolation, but here it is anyway if you want it. It's a little more
 complicated, so pay attention. Whereas before, the interpolation functions took three inputs, the cubic interpolation
 takes five. Instead of just a and b, you now need v0, v1, v2 and v3, along with x as before. These are: 
                         v0 = the point before a 
                         v1 = the point a 
                         v2 = the point b 
                         v3 = the point after b 

      function Cubic_Interpolate(v0, v1, v2, v3,x)
            P = (v3 - v2) - (v0 - v1)
            Q = (v0 - v1) - P
            R = v2 - v0
            S = v1

            return Px3 + Qx2 + Rx + S
      end of function
*********************************************************************************************

  x evtl. im zCModel eine lineare Liste alle Nodes: ein paar rec Funcs waeren schneller...
  x Vob-Rotation aus der Anis auslesen
  - Parameter im MDS: Trans-Ani erst am Ende/bei bestimmtem Prozent der aktuellen State-Ani starten ??
    .. und das mit blendIn!=0 !
  x Graph, Namenskonventionen
	- Transition-Anis
	- State-Anis
	- Occasional-Anis ?
	- Gesture-Anis ?
  x hierarchy	("player.asc")
	defaultMesh	("guard.asc")
  x Probleme:
	- Ober-/Unterkoerper Split
	- Verschlucken von events: *swapMesh
  x MDS: FPS-Override (playback, samples)
  x Response-Zeiten minimieren

*********************************************************************************************

hierarchy	("player.asc")
startMesh	("guard.asc")

0 = noBlend

ani			(1	STATE	.	"stand"			0.0	0.0	"walk.asc"	F	0 23	"stand"	)
ani			(1	TRANS	MR	"walk_start"	1.0	1.0	"walk.asc"	F	0 23	"walk"	)


ani			("S_stand"			1	"S_stand"	0.0	0.0	..	"stand.asc"			F	0 -1)
ani			("T_walk_start"		1	"S_walk"	1.0	0.0	M.	"walk.asc"			F	0 23)
ani			("T_walk_end"		1	"S_stand"	0.0	0.5	M.	"walk.asc"			F	0 23)
aniBlend	("T_walk_to_run"	1	"S_run")
aniSync		("T_walk_to_run"	1	"S_run"		[0.0])
aniAlias	("T_strafe_left"	1	"S_stand"	0.0	0.0	M.	"T_strafe_right"	R)
aniBatch	("T_walk_start"		1	"S_walk")
{
	*aniBatch	("T_1h_walk_start_top")
	*aniBatch	("T_1h_walk_start_bottom")
}

  - Wo/Wie Pausen-Anis definieren ? (Gilden, Individuell, Probs)

  - Trans-Anis:
	- a. i) normal	: Trans-Ani, die mit angegeb. blendIn/blendOut in folge-State ueberleitet
	- a.ii) "alias"	: eine bereits definierte Ani wird mehrfach-verwendet
						- blendIn=0	: Ani wird erst am Ende der aktuellen State-Ani gestartet (mit blendIn=0.01 ??)
						- blendIn>0	: Ani kann in akt. state-ani jederzeit mit angegeb. blendIn gestartet werden
	- b)	"blend"	: naechste State-Ani wird sofort mit dem dort definiertem blendIn gestartet
	- c)	"Sync"	: naechste State-Ani wird sofort mit dem dort definiertem blendIn gestartet,
					  ausserdem wird sie am Prozent-Punkt gestartet, an dem sich die old-state Ani befindet
	- d)	"Batch"	: mehrere Anis koennen gleichzeitig ausgefuehrt werden (z.B. getrennte Ober-/Unterkoerper)


	- MasterAni:
		- Diese Ani kontrolliert alle anderen Anis, solange sie Master-Ani ist & nicht im Fallen ist.
		- Wird eine andere Ani Master-Ani, dann wird das weightSpeed der alten Master-Ani auf 0 gesetzt. 
		  Die neue Master-Ani bekommt ein positives weightSpeed.
		- Soll eine Master-Ani ausgeblendet werden, dann bekommt sie ein negatives weightSpeed. Ausserdem
		  wird eine neue Master-Ani bestimmt, nach den Kriterien:
		  - Layer-Nr
		  - weightSpeed>=0
		- Nur solange weightSpeed>=0 (d.h. weight steigend, oder gleich 1)
		- 


	- dvanceAnis() 
		- Hole Trafos/Quats aus Anis
		- CalcNodeAniBlending()
			- CalcBlending() fuer jede Node
				- CalcWeights() 
					- Berechnet die Gewichte aller beteiligten Anis auf dieser Node. Dabei gibt es
					  eine diktierende Master-Ani
				- Berechnet aus den Gewichten und den Rotationen/Transl. der einzelnen Anis die
				  finale Trafo-Matrix, mit der dann die Verts transformiert werden.



*********************************************************************************************
  - astray, scorch, (guild)

  - Heads will Roll
  - Assassin
  - Enchanter
  - Lurking Beneath
  - Prayer
  - Demon Works
  - Vanguard
  - Fallen Isis
  - Paradise Lost
  - Shattered Dreams
  - Deadlock
  - Dark Ages
  - Carrion
  - Hell Awaits
  - Scaffold
  - Fenris
  - The Mad Scientist Chainsaw Massacre
  - Splitter
  - The Sentinel (=Sleeper)
  - Dead Man
  - Near Dark
  - Splinter
  - Neverland
  - Vigilantes
  - Broadsword
  - Malice
  - Twilight
  - Vault
  - Hellstar
  - Vigil
  - Exile
  - Innocent Exile
  - Jailhouse Rock
  - Mace
  - In Flames
  - Into the Pit

  FIXME/BUGS:
  ***********

  - a-dvanceAnis: Layer-Bug
  - SetModelMesh/Deleting model/Prototype, hier gibt es Fehler (refCtr) ?
  - FIXME: Mesh muss einen Namen bekommen: "protoTypeName;nodeName", damit diese Meshes
    auch richtig geshared werden.
    Allerdings: Mesh-Knoten koennen noch 'hochgezogen' werden..

  TODOS
  *****

was noch fehlt (intern/klein):
  x Koordinaten-System konvertieren
  x Scale aus Ani-Matrix entfernen & ins Mesh einrechnen
  * Integration der Models als Visuals innerhalb der Vobs (bbox3d)
  * meshTree optimieren (LOD-Level, Varis.)
! * Trafo-Reader
	* Teil-Koerper-Anis: Trafos falsch !? (Transl. ??)
	* warum muss in jedem Frame die Node-Transl. neu gesetzt werden ?????  (noe, scheinbar doch nicht)
  * Skript-Sprache
  * Tabs in Pickword & ASCII-Reader einbauen
  - Nodes locken & per Hand manipulieren


  NOTES:
  ******
  - ModelPrototype-Namen: "Player.mds", ohne Pfad mit Ext. !
  - Die Trafo-Matrix-Tabelle einer Ani ist so aufgebaut: x=Node, y=Frame

  interne Bin-Formate:
  ********************
  - .MDL
  - .MSH
  - .MAN
											int				refCtr;			// shared !!
											zSTRING			aniName;		

											int				layer;
															
											zCModelAni		*nextAni;
											zSTRING			nextAniName;

											int				numAniEvents;
											zCModelAniEvent *aniEvents;


											int				fpsRate;
															
											int				numFrames;		// y-Tabelle
											int				numNodes;		// x-Tabelle
															
										//	int				nodeIDList;		// enthält die nodeIDs aller animierten meshTree-Nodes
											zCModelNode		**nodeList;
											zMATRIX4		*trafoMatrix;	// x: nacheinander alle Mat3s eines frames, y: die frames nacheinander

Features:
  - Ptr auf Matrizen
  - Ani-Matrix-Liste optimieren..
  - => internes Binär-Format (.MDL, .ANI, .MSH)
  - PickVob, CheckRay auf Models
  - Anis als shared Objects
  - LOD-Level
  - Mesh-Ani (Bogen)
  - Sleeping Anis
  - MoveVob genauer
  x FPS-Override beim ASC-Import
  x Teil-Koerper-Anis: Limbs explizit angeben koennen (=> 3dsMax-Node-Namen)
  - Auto-Aiming (Waffe, pickUp)
  - Lerp: Zwischen den einzelnen Samples einer Animation interpolieren (rot,pos), falls stepDelta<1.0 ist !
    (allerdings nur fuer das Spieler-Model)

  - special Actions an best. Ani-Positionen (mehrere pro Ani => Footsteps ..)
	- SFX
	- Mesh an Knoten an-/abhaengen (drawSword, throw)
	- FPS-Override
	- prev/next - FollowUp Anis (mit Probabilities)
	- wait_n_frames
	- wait_for_ani_to_start/end "aniName"
	x Vob-Orientierung ändern (3 Winkel)
	- Texture-Ani-Frame eines Limb-Materials ändern 

  - bei jeder Knoten-Matrix in jedem Frame (world=>local):
    immer die aktuelle Parent-Ani-Trafo nehmen, und nicht die Konstante Node-Trafo !!
  - ACHTUNG: wenn Node-Names eingelesen werden, muessen immer die ARGs am Ende gecuttet werden !!

  Kombinierbarkeit
  ****************

  - pro Node
	- versch. Meshes (Ruestung, versch. Koerper)
		- LOD
  - pro Mesh
	- versch. Kleidungs-Texturen
		- ~4 Damage-Texturen

  - Item in der Welt => Mesh/Texture-Veränderung o. Mesh drangehaengt (Kleidung, Waffe)

  Figuren-Engine
  **************

x Anis rückwärts spielen (Sidestep, Knien hoch/runter,..)
- Texture-Damage-Level auch fuer Monster
- Rüstungs-Variationen unterhalb des Kopfes nur komplett (gehandelt in Skript-CItem)
- Player Gesichts-Textur

x Limbs abhacken koennen => limb to vob
x Anis muessen geshared werden !
- Ani-Info packen, wie ?
- Frames interpolieren ? (fuer weiche Übergänge zwischen versch. Animationen)
	- sind dazu Quaternions noetig ? (ja)
- wann duerfen Anis gestartet werden ? welche Abhängigkeiten von laufenden Anis ?
- bei überdeckenden Anis: welche Anis haben wo Priorität ?
- Nodes/Subtrees muessen 'manuell' kontrolliert werden koennen. Allerdings: maximale 
  Positionen/Winkel sind hierbei vonnoeten !
- pro Node: Meshes und Textures muessen austauschbar sein (auch: mehrere Zerstoerungsstufen)
	- Idee: Zerstoerungsstufen als animierte Textures !
	  aber auch allgemein: verschiedene Texture-Alternativen als ani-Textures !!
- Model-Ani-File:
	- Model-Beschreibung als Tree, Meshes, Texture-Infos etc.
	- Menge von Anis
- Sounds muessen an Ani-Frames bindbar sein ! [frameNr SoundName Wahrscheinlichkeit]

  Anis
  ****

- Ani-Typen:
	- Ganz-Koerper-Anis / Teil-Koerper-Anis
	- Cycle-Anis				(walk)				(Zustaende)
	- Transition-Anis			(start-Walking)
	- Interpolation-Transitions

- aniInter
	- nodeList
	- pro Node
		- actQuat
		- deltaQuat
	- ACHTUNG: ueber Scale und Transl muss extra Buch gefuehrt werden ....


*********************************************************************************************

- anis:
	- im Material oder im Texture ?
- Texture-Bitmaps
	- Chest_00_00_00.tga     (skin dam ani)
	- sind im 3ds-Max auf defs. gesetzt
- modelNode:
	- texAni Frames #skin #dam #ani
	- tex->SetAni (skin, dam, ani)
		=> jede zCModelNodeInst enthaelt eine Liste aller enthaltenen Textures
	- Rendern
- Kleidungswechsel:
	C_Item {
		Mdl_SetSkin		(skinNr)
		Mdl_SetDamage	(damNr)
			- Alle modifizierbaren Textures des Models werden in einer Liste gehalten.
			- Diese Liste wird nun durchlaufen und die erste Ani jedes Mats wird auf Frame 'skinNr' gesetzt.

		Mdl_SetLimbMesh	(ASCName_NodeName)		[.3ds, .msh]
		Mdl_SetLimbMesh	(ASCName)
	}


Model ("Player")
{
	aniEnum
	{																// Ani-Sammlung
		aniInter	(1 "stand2Oops"	"targetAni"		  timeSec)
		ani			(1 "strafeLeft"	"playerWalk.asc"  0 -1 "standing" F "standing" F fpsRate?)
		ani			(1 "standing"	"playerWalk.asc"  0 -1)
		{
			nodeSelAll		// default
			nodeSelNone
			nodeSel			("nodeName")
			nodeSelSub		("nodeName")
			nodeUnsel   	("nodeName")
			nodeUnselSub	("nodeName")

			aniPrev			(frameNr "aniName"		prob)
			aniSound		(frameNr "stepping.wav" prob)
			aniMoveMesh		(frameNr "sourceNode"	"targetNode")
			aniHeading		(frameNr dAlpha			dBeta dGamma)
			aniNext			(frameNr "aniName"		prob)
		}
	}
	minMaxRotAngles
	{
		minMaxAngles		("nodeName" min:max min:max min:max)
	}
}

  zm_Neck 'LOD-Level;Bis-Z-Distanz'	// (fuer jedes LOD-Mesh)

  zm_Neck '1;50'					// an Biped-Node drangehaengtes Mesh
  zs_Shield							// Slot fuer dranhaengbares

*********************************************************************************************

.ascMdl		.mds

.binMdl		.mdl
.binTre
.binAni		.ani
.binMsh		.msh

  geshared:
	- limb-meshes
	- limb-mesh-textures
	- anis (einzelnd)
	- 

vob.SetVisual ("player.mdl")
model.Load ("player.mdl")
	- ascMdl wird geparsed
	- anis schon vorhanden ?			=> bereits geladene Anis   sharen
	- limbMesh schon vorhanden ?		=> bereits geladene Meshes sharen ("fileName"+"Tree-Pos-Name")

*********************************************************************************************

// eine Ani, z.B. "walking". ~10k - 30k ?

- welches externe Import-Format ?
	x !! 3DS-MAX ASCII-Exporter !!
	- GAMUT: .AGT - hat das .AGT alles so wie ich es brauche ? (Hierarchie, Euler-Angles, Transl3D, Tex-Coords)
	- 3DS-R4 => .VUE - im 3ds4 testen, Alex noch mal testen lassen; woran liegts ? behebbar ? update ?
	- 3DS-MAX Plugin - Wie gross ist der Aufwand ? => SDK reinziehen
	- VRML			 - hat das VRML alles so wie ich es brauche ? Ist der Exporter ok ?
	- .X ?? 
	x 3DS-MAX v2.0  ASCII => unklar, ob es alle noetigen Daten hat.
*/


//#define DEBUG_EFFECTS

#ifdef DEBUG_EFFECTS
#include "zinput.h"
#endif


int	zCModel::s_iNumSoftSkinPoly[20];

const zSTRING	zMDL_NODE_NAME_BIP_PREFIX	= "BIP01";
const zSTRING	zMDL_NODE_NAME_R_HAND		= zMDL_NODE_NAME_BIP_PREFIX+" R HAND";
const zSTRING	zMDL_NODE_NAME_L_HAND		= zMDL_NODE_NAME_BIP_PREFIX+" L HAND";
const zSTRING	zMDL_NODE_NAME_R_FOOT		= zMDL_NODE_NAME_BIP_PREFIX+" R FOOT";
const zSTRING	zMDL_NODE_NAME_L_FOOT		= zMDL_NODE_NAME_BIP_PREFIX+" L FOOT";
const zSTRING	zMDL_NODE_NAME_HEAD			= zMDL_NODE_NAME_BIP_PREFIX+" HEAD";
const zSTRING	zMDL_NODE_NAME_FOOTSTEPS	= " FOOTSTEPS";





///////////////////////////////////////////////////////////////////////////
//     Model Ani (Instance)
///////////////////////////////////////////////////////////////////////////

zCModelAniActive::zCModelAniActive () {
	lastPos 					= thisPos		= zPOINT3(0,0,0);
	lastRotQuat					= thisRotQuat	= freezeRotQuat = zCQuat(0);
	rotFirstTime				= TRUE;

	// div. Felder
	nextAni						= 0;
	protoAni					= 0;
	actAniEvent					= 0;
	nextAniOverride				= 0;
	actFrame					= 0.0F;
	advanceDir					= 0;
	isFadingOut					= FALSE;
	isFirstTime					= TRUE;
	blendInOverride				= 0;
	blendOutOverride			= 0;
	combAniX = combAniY			= 0.5F;
	transWeight					= 0;
	aniAttachment				= 0;
	randAniTimer				= 0;

/*	// special-handling fuer bestimme Anis
	if (protoAni->GetAniType()==zMDL_ANI_TYPE_BLEND) {
		// ist noetig, damit alle aniEvents zu Beginn abgespielt werden
		actFrame	= 99999.0F;
		advanceDir	= +1;
	};
*/
};

zCModelAniActive::~zCModelAniActive()
{
	protoAni		= 0;
	nextAni			= 0;
	nextAniOverride	= 0;
	aniAttachment	= 0;
};

void zCModelAniActive::SetDirection (zTMdl_AniDir dir) {
	if (dir==zMDL_ANIDIR_ENDFASTEST) {
		// kuerzesten Weg zum Ani-Ende suchen 
		if (actFrame>=(protoAni->numFrames/2))	dir = zMDL_ANIDIR_FORWARD;
		else									dir = zMDL_ANIDIR_REVERSE;
	};

	if (dir==zMDL_ANIDIR_FORWARD) {
		advanceDir = +1;
	} else 
		advanceDir = -1;
};

zREAL zCModelAniActive::GetProgressPercent () const {
	if (advanceDir>=0)	return	  zREAL(actFrame) / zREAL(protoAni->numFrames);
	else				return 1-(zREAL(actFrame) / zREAL(protoAni->numFrames));
};

void zCModelAniActive::SetProgressPercent (const zREAL percent) {
	if (advanceDir>=0)	actFrame = percent		* zREAL(protoAni->numFrames-1);
	else				actFrame = (1-percent)	* zREAL(protoAni->numFrames-1);
};

void zCModelAniActive::SetActFrame (const zREAL newFrame)
{
	actFrame	= newFrame; 
	zClamp		(actFrame, zREAL(0), zREAL(protoAni->numFrames-1));
};

///////////////////////////////////////////////////////////////////////////
//     Model Tex Ani State
///////////////////////////////////////////////////////////////////////////


zCModelTexAniState::zCModelTexAniState() {
	memset (actAniFrames, 0, sizeof(*actAniFrames));
	nodeTexList	= 0;
	numNodeTex	= 0;
};

zCModelTexAniState::~zCModelTexAniState() {
	DeleteTexList();
};

void zCModelTexAniState::DeleteTexList() {
	delete[] nodeTexList;
	nodeTexList = 0;
	numNodeTex	= 0;
};

void zCModelTexAniState::UpdateTexList() {
	// zunaechst die richtigen Ani-Stufen der Materialien setzen !
	for (int i=0; i<numNodeTex; i++) { 
		zCTexture *tex = nodeTexList[i];
		assert (tex);
		for (int j=0; j<zMDL_MAX_ANI_CHANNELS; j++) {
			tex->SetActAniFrame (j, actAniFrames[j][i]);
		};
	};
};

void zCModelTexAniState::SetChannelVariation (const int channel, const int varNr, zSTRING* texNamePart) {
	assert (channel<zMDL_MAX_ANI_CHANNELS);
	if (channel>=zMDL_MAX_ANI_CHANNELS) return;
	for (int i=0; i<numNodeTex; i++) 
	{
		if ((!texNamePart) || (nodeTexList[i]->GetName().Search(*texNamePart)!=-1)) {
			actAniFrames[channel][i] = varNr;
		};
	};
};

void zCModelTexAniState::BuildTexListFromMeshLib (zCModelMeshLib *meshLib) 
{
	zCArray<zCTexture*>		texList;
	AddTexListFromMeshLib	(meshLib, texList);
	FinishTexList			(texList);
};

void zCModelTexAniState::BuildTexListFromMesh (zCMesh *mesh) 
{
	zCArray<zCTexture*>		texList;
	AddTexListFromMesh		(mesh, texList);
	FinishTexList			(texList);
};

void zCModelTexAniState::BuildTexListFromProgMesh (zCProgMeshProto *pmesh) 
{
	zCArray<zCTexture*>		texList;
	AddTexListFromProgMesh	(pmesh, texList);
	FinishTexList			(texList);
};

void zCModelTexAniState::AddTexListFromMeshLib (zCModelMeshLib *meshLib, zCArray<zCTexture*> &texList) 
{
	// erst alle Meshes einsammeln, dann von diesen die Texturen einsammeln

// FIXME: spaeter als ProgMeshes..
	// nodeVisuals
	{
		zCArray<zCMesh*> meshList;
		for (int i=0; i<meshLib->meshNodeList.GetNum(); i++) 
		{
			zCVisual *vis = meshLib->meshNodeList[i].visual;
//			if (dynamic_cast<zCMesh*>(vis))			meshList.Insert (dynamic_cast<zCMesh*>(vis)); else
//			if (dynamic_cast<zCMorphMesh*>(vis))	meshList.Insert (dynamic_cast<zCMorphMesh*>(vis)->GetMorphMesh());
			if (zDYNAMIC_CAST<zCMesh>(vis))			AddTexListFromMesh		(zDYNAMIC_CAST<zCMesh>(vis), texList); else
			if (zDYNAMIC_CAST<zCMorphMesh>(vis))	AddTexListFromProgMesh	(zDYNAMIC_CAST<zCMorphMesh>(vis)->GetMorphMesh(), texList);
		};
		//
		for (i=0; i<meshList.GetNum(); i++) 
			AddTexListFromMesh (meshList[i], texList);
	};

	// softSkins
	// alle Textures des SoftSkins einsammeln und in 'texList' sammeln, keine doppelten
	for (int i=0; i<meshLib->meshSoftSkinList.GetNum(); i++) 
		AddTexListFromProgMesh (meshLib->meshSoftSkinList[i], texList);
};

void zCModelTexAniState::AddTexListFromMesh (zCMesh *mesh, zCArray<zCTexture*> &texList)
{
	for (int i=0; i<mesh->numPoly; i++) 
	{
		zCMaterial *mat= mesh->SharePoly(i)->material;
		if (mat) {
			{
// FIXME: Quick-smoothing-hack !!
				mat->SetSmooth		(TRUE);
				mat->SetAmbient		(0.0F);
				mat->SetDiffuse		(0.6F);
//				mat->SetPreAmbient	(0.4F);
//				mat->SetSpecular	(0.0F);
			}
			zCTexture *tex = mat->GetTexture();
			if (tex) 
			if (!texList.IsInList(tex))
			{
				texList.Insert (tex);
			};
		};
	};
};

void zCModelTexAniState::AddTexListFromProgMesh (zCProgMeshProto *pmesh, zCArray<zCTexture*> &texList)
{
	for (int j=0; j<pmesh->GetNumMaterial(); j++) 
	{
		zCMaterial *mat= pmesh->GetMaterialByIndex(j);
		if (mat) {
			zCTexture *tex = mat->GetTexture();
			if (tex) 
			if (!texList.IsInList(tex))
			{
				texList.Insert (tex);
			};
		};
	};
};

void zCModelTexAniState::FinishTexList (zCArray<zCTexture*> &texList)
{
	//
	DeleteTexList();

	//
	if (texList.GetNum()>zMDL_MAX_TEX) {
		zERR_FATAL ("D: zModel(zCModelTexAniState::BuildTexListFromMesh): Too many textures in meshLib.. "+zSTRING(texList.GetNum()));
		while (texList.GetNum()>zMDL_MAX_TEX) texList.RemoveIndex (texList.GetNum()-1);
	};

	if (texList.GetNum()<=0) {
		numNodeTex	= 0;
		nodeTexList	= 0;
		return;
	};

	numNodeTex	= texList.GetNum();
	nodeTexList = zNEW(zCTexture*) [numNodeTex];
	memcpy (nodeTexList, texList.GetArray(), sizeof(zCTexture*)*numNodeTex );
};

///////////////////////////////////////////////////////////////////////////
//     Model - Node - Instance
///////////////////////////////////////////////////////////////////////////

zCModelNodeInst::zCModelNodeInst()
{
	Init			();
};

zCModelNodeInst::zCModelNodeInst (zCModelNode *mnode) {
	InitByModelProtoNode (mnode);
};

zCModelNodeInst::~zCModelNodeInst () {
	zRELEASE (nodeVisual);
	parentNode		= 0;
	protoNode		= 0;
};

void zCModelNodeInst::Init ()
{
	parentNode		= 0;
	nodeVisual		= 0;
	trafo			= trafoObjToCam = Alg_Identity3D();
	bbox3D.InitZero	();

	// Ani-Blending
	numNodeAnis		= 0;
	masterAni		=-1;
	masterAniSpeed	= 0;
	
	//
	protoNode		= 0;
};

void zCModelNodeInst::InitByModelProtoNode(zCModelNode *mnode)
{
	zERR_ASSERT(mnode);
	Init			();
	
	//
	protoNode		= mnode;
	SetNodeVisualS	(mnode->visual, TRUE);
	trafo			= mnode->trafo;
//	translation		= mnode->translation; 
};

void zCModelNodeInst::SetNodeVisualS (zCVisual *visual, zBOOL animated) {
	// FIXME: wenn halt nur an einem Slot was drangehaengt werden soll
	//		  kann mann sich das Texture-sammeln sparen, ja MUSS sogar !
	if (visual==nodeVisual)	return;

	texAniState.DeleteTexList ();

	if (nodeVisual) nodeVisual->Release();
	if (!visual) {
		nodeVisual = 0;
		return;
	};
	nodeVisual = (zCVisual*)(visual->AddRef());

	if (animated) {
		// alle verwendeten Textures sammeln
		if (visual->GetClassDef()==zCMesh::GetStaticClassDef())			texAniState.BuildTexListFromMesh	 (static_cast<zCMesh*>(visual)); else
		if (visual->GetClassDef()==zCMorphMesh::GetStaticClassDef())	texAniState.BuildTexListFromProgMesh (static_cast<zCMorphMesh*>(visual)->GetMorphMesh()); else
		if (visual->GetClassDef()==zCMeshSoftSkin::GetStaticClassDef())	texAniState.BuildTexListFromProgMesh (static_cast<zCMeshSoftSkin*>(visual));
	};
};

///////////////////////////////////////////////////////////////////////////
//     MODEL
///////////////////////////////////////////////////////////////////////////

zBOOL zCModel::s_drawSkeleton	= FALSE;
zBOOL zCModel::s_bSmoothRootNode= TRUE;

zCModel::~zCModel() 
{
	//
	for (int j=0; j<modelProtoList.GetNumInList(); j++) {
		modelProtoList[j]->Release();
	};
	modelProtoList.DeleteList();

	m_listOfVoiceHandles.DeleteList();

	// ACHTUNG: Meshes gehoeren immer den MeshLibs und muessen deshalb nicht extra released werden !
	RemoveMeshLibAll ();

	// SoftSkins
	for (int i=0; i<meshSoftSkinList.GetNum(); i++)
		meshSoftSkinList[i]->Release();
	meshSoftSkinList.DeleteList();

	// evtl. 'uebergebliebene' Meshes aus den Nodes entfernen
	for (i=0; i<nodeList.GetNum(); i++)
		nodeList[i]->SetNodeVisualS	(0);

	//
	RemoveAllAniAttachments ();

	// Nodes loeschen (am Ende)
	if (nodeList.GetNum()>0)
		delete[] (nodeList[0]);
	nodeList.DeleteList();

	//
	delete[] aniHistoryList; aniHistoryList=0;
	delete[] activeAniList; activeAniList=0;
	activeAniList			= 0;
	homeVob					= 0;
	numActiveAnis			= 0;
};

void zCModel::Init() 
{
	for (int i=0; i<zMDL_VELRING_SIZE; i++) modelVelRing[i] = 0;
	homeVob					= 0;
	numActiveAnis			= 0;
	activeAniList			= 0;
	lastTimeBBox3DTreeUpdate= 0;
	actVelRingPos			= 0;
	modelVelocity			= 0;
	nodeShadowEnabled		= FALSE;
	vobTrans				= 0;
	vobTransRing			= 0;
	relaxWeight				= 0.1F;
	newAniStarted			= TRUE;
	doVobRot				= 0;
	vobRot.Identity();
	aniHistoryList			= 0;

	aniAttachList.SetCompare	(AniAttachmentCompare);
	SetTimeScale			(1.0F);
	SetFatness				(0);
	SetModelScale			(zVEC3(1,1,1));
	SetIsFlying				(FALSE);
	SetIsVisible			(TRUE);
	SetLerp					(TRUE);
	SetAniTransScale		(zVEC3(1,1,1));
	SetRandAnisEnabled		(TRUE);
//	SetDynLightMode			(zMDL_DYNLIGHT_EXACT); 
	SetDynLightMode			(zMDL_DYNLIGHT_SCALEPRELIT); 

	bbox3D.mins				= bbox3D.maxs = zVEC3(0);
	bbox3DLocalFixed		= bbox3D;
	bbox3DCollDet			= bbox3D;

	modelDistanceToCam		= 0;
	rootPosLocal			= zVEC3(0); 
	m_bDrawHandVisualsOnly  = FALSE;
	m_bSmoothRootNode		= TRUE;
	n_bIsInMobInteraction	= FALSE;
};


zCModel::zCModel (zCModelPrototype* baseModelProto)	
{
	Init						();

	// inits die erst moeglich sind, seitdem das baseModelProto feststeht
	bbox3D						= baseModelProto->bbox3D;
	modelProtoList.Insert		(baseModelProto);

	// TEMP
	// SoftSkin Ptr kopieren (ADDREF!)
	meshSoftSkinList.AllocAbs	(baseModelProto->meshSoftSkinList.GetNum());
	for (int i=0; i<baseModelProto->meshSoftSkinList.GetNum(); i++)
		meshSoftSkinList.Insert ( (zCMeshSoftSkin*)(baseModelProto->meshSoftSkinList[i]->AddRef()) );

	// meshTree, nodeList kopieren
	CopyProtoNodeList			();


	// braucht eine fertige nodeList..
	SetModelScale				(zVEC3(1,1,1));
};

void zCModel::CopyProtoNodeList () 
{
	if ((modelProtoList.GetNum()<=0) || (!modelProtoList[0])) return;
	int num = modelProtoList[0]->nodeList.GetNum();
	
	// Alle ModelNodeInst werden in einem Block allokiert
	nodeList.AllocAbs				(num);
	zCModelNodeInst *nodeInstList	= zNEW(zCModelNodeInst) [num];

	for (int i=0; i<num; i++) 
	{
		zCModelNode		*protoNode	= modelProtoList[0]->nodeList[i];
		zCModelNodeInst	*instNode	= &(nodeInstList[i]);
		instNode->InitByModelProtoNode	(protoNode);
		// FIXME: 'ne haessliche Methode den Parent zu ermitteln..
		zCModelNode		*parent		= modelProtoList[0]->FindMeshTreeNode (protoNode->GetName())->GetParent()->GetData();
		if (parent) 
			instNode->parentNode	= SearchNode (parent->GetName());
		protoNode->lastInstNode		= instNode;
		nodeList.InsertEnd			(instNode);
	};
};

void zCModel::SetVisualUsedBy (zCVob* vob) { 
	homeVob = vob; 
	if (vob)	
	{
		vob->SetCastDynShadow	(zCVob::zDYN_SHADOW_TYPE_BLOB);
		vob->SetZBias			(0);
	}
};

// =====================================================================================

static const zSTRING modelFileExt[2] = { ".MDS", ".ASC" };

const zSTRING* zCModel::GetFileExtension (int i)
{
	if ((i<0) || (i>1))	return 0;
	return &(modelFileExt[i]);
};

zCVisual* zCModel::LoadVisualVirtual (const zSTRING& visualName) const
{
	zCModelPrototype *modelProto = zCModelPrototype::Load (visualName);
	if (!modelProto) return 0;
	return zNEW(zCModel (modelProto));
};


/* -------------------------------------------------------------------------
	zBOOL zCModel::ApplyModelProtoOverlay (const zSTRING& mdsFileName)

	05.10.2000	[SPECKELS]	Sicherheitsabfrage, ob proto ueberhaupt geladen wurden
							sprich: if (proto) ...

   ------------------------------------------------------------------------- */

zBOOL zCModel::ApplyModelProtoOverlay (const zSTRING& mdsFileName) 
{
	if (modelProtoList.GetNum()<=0)	return FALSE;
	zCModelPrototype *proto = zCModelPrototype::Load (mdsFileName, modelProtoList[0]);
	zBOOL res=FALSE;
	if (proto)
	{
		res	= ApplyModelProtoOverlay (proto);
		proto->Release();
	}
	return res;
};

zBOOL zCModel::ApplyModelProtoOverlay (zCModelPrototype* proto) 
{
	//
	if (!proto)											return FALSE;
	if (modelProtoList.IsInList (proto))				return FALSE;	// ??
	if (modelProtoList.GetNum()<=0)						return FALSE;
	if (proto->GetBaseModelProto()!=modelProtoList[0])	{
		zERR_WARNING ("D: MDL: tried to apply overlay to model: overlay- and model base-.mds do not match");
		return FALSE;
	};
//	if ((modelProtoList.GetNum()>0) && (modelProtoList[modelProtoList.GetNum()-1]==proto)) return;	// ??

	// zur Sicherheit muessen alle laufenden Anis entfernt werden
	StopAnisLayerRange (0, 99999);

	zERR_MESSAGE (5, 0, "D: MDL: Applying mds-overlay: "+proto->GetModelProtoName());
	// FIXME: ist das refCounting so ok ?

	// modelProto eintragen
	if (!modelProtoList.IsInList (proto)) {
		modelProtoList.InsertEnd (proto);
		// FIXME: ein AddRef ist hier nicht noetig (autom.) ??
		proto->AddRef();
	};

	// ACHTUNG: 
	// falls eine Anwendung sich ueber SearchAni Ptr auf Ani-Instanzen geholt hat, koennten einige davon
	// nun ungueltig sein => die Anwendung muss ihre Ptr-Referenzen komplette neu erstellen
	return TRUE;
};

zBOOL zCModel::HasAppliedModelProtoOverlay(zCModelPrototype	*proto) const
{
	for (int i=0; i<modelProtoList.GetNumInList(); i++) 
		if (modelProtoList[i]==proto) return TRUE;
	return FALSE;
};

zBOOL zCModel::HasAppliedModelProtoOverlay(const zSTRING& mdsFileName) const
{
	zPATH			tmp(mdsFileName);
	const zSTRING	protoName (tmp.GetFilename());

	for (int i=0; i<modelProtoList.GetNumInList(); i++) 
		if (modelProtoList[i]->GetModelProtoName()==protoName)	return TRUE;
	return FALSE;
};

void zCModel::RemoveModelProtoOverlay (const zSTRING& mdsFileName) {
	zPATH			tmp(mdsFileName);
	const zSTRING	protoName (tmp.GetFilename());

	for (int i=0; i<modelProtoList.GetNumInList(); i++) {
		if (modelProtoList[i]->GetModelProtoName()==protoName) {
			RemoveModelProtoOverlay (modelProtoList[i]);
			break;
		};
	};
};

void zCModel::RemoveModelProtoOverlay (zCModelPrototype* proto) 
{
	// zu entfernendes mds in der Liste der MDS suchen
	int pi	= modelProtoList.Search (proto);
	if (pi<=0) return;	// das Basis MDS auf 0 darf nicht entfernt werden

	zERR_MESSAGE (5, 0, "D: MDL: Removing mds-overlay: "+proto->GetModelProtoName());

	// zur Sicherheit muessen alle laufenden Anis entfernt werden
	StopAnisLayerRange (0, 99999);

	// ModelProto aus Liste entfernen
	modelProtoList.RemoveOrderIndex (pi);
	proto->Release();
};

// ======================================================================================

void zCModel::CalcNodeListBBoxWorld () 
{
	const zTFrameCtr masterCtr = homeVob->GetHomeWorld()->GetMasterFrameCtr();
	if (lastTimeBBox3DTreeUpdate==masterCtr) return;
	lastTimeBBox3DTreeUpdate = masterCtr;

	#ifdef zDEBUG_MDL_COLLECT_STATS
		zengineStats.numModelUpdateBBoxTree++;
	#endif
	// modelScale
	zMAT4 matObjToWorld;
//	if (modelScaleOn)	matObjToWorld = parentTrafoObjToWorld * Alg_Scaling3D(modelScale);
//	else				matObjToWorld = parentTrafoObjToWorld;

//	matObjToWorld = parentTrafoObjToWorld;
	matObjToWorld = homeVob->trafoObjToWorld;
	if (modelScaleOn)	matObjToWorld.PreScale (modelScale);

//	UpdateBBoxTree (matObjToWorld, &meshTree);

	// Mesh Node-BBox'en updaten
	for (int i=0; i<nodeList.GetNum(); i++) 
	{
		zCModelNodeInst	*node		= nodeList[i];
		zCModelNodeInst	*parentNode	= node->GetParentNode();
		// keine Node oder Node ohne Mesh => Rekursion abbrechen !
		if (parentNode)	node->trafoObjToCam	= parentNode->trafoObjToCam	* node->trafo;
		else			node->trafoObjToCam	= matObjToWorld				* node->trafo;
		if (node->nodeVisual) 
		{
			// BBox3D
			// FIXME: visual OS/WS ?
			node->nodeVisual->GetBBox3D().Transform (node->trafoObjToCam, node->bbox3D);
			node->bbox3D.Scale (0.8F);
//				mnode->bbox3D.mins[VY] *= 0.6F;
			// Model/Vob - BBox3D
//				this->bbox3D.CalcGreaterBBox3D (mnode->bbox3D);
		} else {
			// bbox3D besteht aus 1 Punkt
			node->bbox3D.mins = node->bbox3D.maxs = node->trafoObjToCam.GetTranslation();
		};
	};

	// FIXME: sollten SoftSkins Einfluss auf die BBoxen der Nodes haben .. ??

	// SoftSkin Node-BBoxen udpaten
/*	for (i=0; i<meshSoftSkinList.GetNumInList(); i++) {
		zCMeshSoftSkin	*mesh		= meshSoftSkinList[i];
		for (int j=0; j<mesh->nodeIndexList.GetNum(); j++) {
			zCModelNodeInst	*node	= nodeList			[mesh->nodeIndexList[j]];
			zCOBBox3D		*obb	= mesh->nodeOBBList	[mesh->nodeIndexList[j]];
			// FIXME: evtl. sollten die SoftSkins auch bbox3D's speichern
			// FIXME: evtl. sollte hier statt stumpfem ersetzen ein 'CalcGreater' stattfinden
			node->bbox3D = obb->GetBBox3D();
		};
	};
*/

};

zTBBox3D zCModel::GetBBox3DNodeWorld (zCModelNodeInst* mnode) {
	CalcNodeListBBoxWorld();
	return mnode->GetBBox3DNodeWorldS();
};

zPOINT3 zCModel::GetNodePositionWorld (zCModelNodeInst* mnode) {
	CalcNodeListBBoxWorld();
	return mnode->trafoObjToCam.GetTranslation();
};

void zCModel::CalcModelBBox3DWorld () 
{
	// Alle Anis besitzen eine eigene BBox. Die BBoxen aller laufenden Anis werden hier verrechnet und 
	// ergeben die local-BBox des Models.
	// Slot-Node-Meshes:
	// Die derzeitige Strategie ist es, beim Rendern jedes dieses Meshes einzelnd und komplett gegen das
	// Frustum zu testen. Das ist relativ schnell, produziert allerdings in seltenen Faellen optische 
	// Fehler, wenn ein NodeMesh aus der aktuellen AniBBox des Models herausragt und das NodeMesh sichtbar
	// ist, nicht aber die AniBBox des Models.

	zBOOL		found = FALSE;
	zTBBox3D	bbox3DResult;
	bbox3DResult.Init(); 

	for (int i=0; i<numActiveAnis; i++) 
	{
		const zTBBox3D& box = aniChannels[i]->GetAni()->aniBBox3DObjSpace;
		bbox3DResult.CalcGreaterBBox3D ( box );
		found = TRUE;
	};

/*	
	// modelScale
	zMAT4 matObjToWorld;
	matObjToWorld.MakeIdentity();
	if (modelScaleOn)	
		matObjToWorld.PreScale (modelScale);

	// Model BBox über Node-BBox'en updaten (node-bboxen bleiben const)
	for (int i=0; i<nodeList.GetNum(); i++) 
	{
		zCModelNodeInst	*node		= nodeList[i];
		zCModelNodeInst	*parentNode	= node->GetParentNode();
		// keine Node oder Node ohne Mesh => Rekursion abbrechen !
		if (parentNode)	node->trafoObjToCam	= parentNode->trafoObjToCam	* node->trafo;
		else			node->trafoObjToCam	= matObjToWorld				* node->trafo;
		if (node->nodeVisual) 
		{
			// Model/Vob - BBox3D
			// FIXME: visual OS/WS ?
			zTBBox3D box;
			node->nodeVisual->GetBBox3D().Transform (node->trafoObjToCam, box);
			this->bbox3D.CalcGreaterBBox3D (box);
			found = TRUE;
		};
	};
*/
	// gab es keine Meshes/Anis, anhand derer eine BBox haette berechnet werden koennen ?
	if (!found) 
	{
		if (modelProtoList.GetNum()>0)	bbox3DResult		= modelProtoList[0]->bbox3D;
		else							bbox3DResult.InitZero	();
	};

	// modelScale
	if (modelScaleOn)	
	{
		bbox3DResult.mins = Alg_Prod (bbox3DResult.mins, modelScale);
		bbox3DResult.maxs = Alg_Prod (bbox3DResult.maxs, modelScale);
	};

	// zuweisen
	this->bbox3D	= bbox3DResult;
};

void zCModel::SetNodeVisual (zCModelNodeInst* mnode, zCVisual *visual, zBOOL animated) {
	mnode->SetNodeVisualS (visual, animated);
	
	// Model-BBox neu berechnen
	CalcModelBBox3DWorld();
//	this->bbox3D = GetBBox3DLocalFixed();
//	for (int i=0; i<nodeList.GetNumInList(); i++) 
//		this->bbox3D.CalcGreaterBBox3D (nodeList[i]->bbox3D);
};

void zCModel::SetDynLightMode (const int mode) {
	dynLightMode = mode;
};




void zCCFASTCALL zCModel::SetupLowestLOD(zTRenderContext& renderContext) 
{
	zCArray<zMAT4*> nodeTrafoList;
	nodeTrafoList.AllocAbs			(nodeList.GetNum());
	nodeTrafoList.MarkNumAllocUsed	();

	if (homeVob && homeVob->GetHomeWorld() && zCCamera::activeCam && zCCamera::activeCam->GetVob()) 
	{

		zMAT4 trafoWorldToCam = zCCamera::activeCam->GetVob()->trafoObjToWorld.InverseLinTrafo();
		// ARGH
		// Mesh Node-BBox'en updaten
		for (int i=0; i<nodeList.GetNum(); i++) 
		{
			zCModelNodeInst	*node		= nodeList[i];
			zCModelNodeInst	*parentNode	= node->GetParentNode();
			// keine Node oder Node ohne Mesh => Rekursion abbrechen !
			if (parentNode)	node->trafoObjToCam	= parentNode->trafoObjToCam	* node->trafo;
			else			node->trafoObjToCam	= trafoWorldToCam * homeVob->trafoObjToWorld * node->trafo;
			nodeTrafoList[i]					= &node->trafoObjToCam;
		}
	}
	else return;

	zCProgMeshProto::InitSetupLowestLOD();

	for (int i=0; i<meshSoftSkinList.GetNum(); i++) 
		meshSoftSkinList[i]->SetupLowestLOD(renderContext, nodeTrafoList, GetFatness(),s_iNumSoftSkinPoly[i]); 

#ifdef DEBUG_EFFECTS
	if (zinput)
	if (zinput->KeyPressed(KEY_LSHIFT) && zinput->KeyPressed(KEY_LCTRL))
	{
		int numPoly = GetLowestLODNumPolys();
		zVEC3 v;
		zVEC3 *pv = &v;
		for (i=0; i<numPoly; i++) 
		{
			zVEC3* verts = GetLowestLODPoly(i, pv);
			if (homeVob) 
			{
				zPOINT3 a(verts[0]);
				zPOINT3 b(verts[1]);
				zPOINT3 c(verts[2]);
				a=homeVob->trafoObjToWorld*a;
				b=homeVob->trafoObjToWorld*b;
				c=homeVob->trafoObjToWorld*c;
				zlineCache.Line3D(a,b);
				zlineCache.Line3D(a,c);
				zlineCache.Line3D(b,c);
			}
		};
	}
#endif

};


int		zCModel::GetLowestLODNumPolys()
{
	int numPoly = 0;
	for (int i=0; i<meshSoftSkinList.GetNum(); i++) numPoly += s_iNumSoftSkinPoly[i];
	return numPoly;
}

zVEC3*	zCModel::GetLowestLODPoly(const int a_iPoly, zVEC3* &normal)
{
	
	if (meshSoftSkinList.GetNum()==0)		 return 0;
	if (meshSoftSkinList[0]->GetNumTri()==0) return 0;
	return meshSoftSkinList[0]->GetLowestLODPoly(a_iPoly, normal);		// FIXME: static machen. progmesh+softskin interface vereinheitlichen.
}

zCMaterial*	zCModel::GetMaterial(const int a_iIndex)
{
	if (meshSoftSkinList.GetNum()>1) return meshSoftSkinList[1]->GetMaterialByIndex(0); else
	if (meshSoftSkinList.GetNum()>0) return meshSoftSkinList[0]->GetMaterialByIndex(0);
	return 0;
}

int	zCModel::GetNumMaterials() const
{
	if (meshSoftSkinList.GetNum()>1) return meshSoftSkinList[1]->GetNumMaterial(); else
	if (meshSoftSkinList.GetNum()>0) return meshSoftSkinList[0]->GetNumMaterial();
	return 0;
}



////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


void zCCFASTCALL zCModel::RenderNodeList (
							  zTRenderContext				&renderContext, 
							  zCArray<zMAT4*>				&nodeTrafoList, 
							  zCRenderLightContainer		&renderLightCont, 
							  const zTPMLightingMode		lightingMode) 
{
	zTRenderContext tmpRenderContext= renderContext;

	// FIXME: aufgrund eines Bugs in der Modelbeleuchtung muss folgende Zeile rein, damit kein Beleuchtungsplöppen entsteht, wenn
	// nur der Kopf nicht gerendert werden muss
	zBOOL resetRenderLightCont		= renderContext.vob->GetCharacterClass()!=zCVob::zVOB_CHAR_CLASS_NONE ? TRUE : FALSE;

	for (int i=0; i<nodeList.GetNum(); i++) 
	{
		zCModelNodeInst	*mnode		= nodeList[i];

		zCModelNodeInst	*mnodeParent= mnode->GetParentNode();
		nodeTrafoList[i]			= &mnode->trafoObjToCam;

		// trafo berechnen
		if (mnodeParent)	mnode->trafoObjToCam = mnodeParent->trafoObjToCam		* mnode->trafo;
		else				mnode->trafoObjToCam = zCCamera::activeCam->camMatrix	* mnode->trafo;
		if (mnode->nodeVisual) 
		{
			if (GetDrawHandVisualsOnly())
			{								
				if (!mnode->GetProtoNode()->IsSlot()) continue;
				if ( mnode->GetProtoNode()->GetName()!="ZS_RIGHTHAND" && mnode->GetProtoNode()->GetName()!="ZS_LEFTHAND" ) continue;
			}

			// zunaechst die richtigen Ani-Stufen der Materialien setzen !
			mnode->texAniState.UpdateTexList ();
				
			// 1) camMatrix			(world(obj)Space => camSpace)
			zCCamera::activeCam->camMatrix    = mnode->trafoObjToCam;

			// Model-BBox schneidet das Frustum (clipFlags>0)
			// allerdings ist die Node-BBox kleiner als die Model-BBox, und es koennten deshalb ein
			// paar Frustum-Planes ausgeschaltet werden => ein weiterer BBox3DInFrustum()-Test

			// 2) camMatrixInv		(camSpace		 => world(obj)Space)
			if (modelScaleOn) zCCamera::activeCam->camMatrixInv = zCCamera::activeCam->camMatrix.Inverse();			// fuer frustum-planes
			else			  zCCamera::activeCam->camMatrixInv = zCCamera::activeCam->camMatrix.InverseLinTrafo(); // fuer frustum-planes
 			
			// 3) activeCamPos		(camSpace		 => objSpace)
			//    (fuer backface-culling, 3D-Clipping)
			//	  Im camSpace ist die activeCamPos ja immer (0,0,0) !
			//    camPos(inObjSpace) = camMatrixInv * (0,0,0);
			zCCamera::activeCam->camMatrixInv.GetTranslation( zCCamera::activeCamPos );	// fuer backfaceCulling

			int meshClipFlags = zCCamera::CLIP_FLAGS_FULL_WO_FAR;
//			int meshClipFlags = renderContext.clipFlags;
//			if (meshClipFlags>0) 
//			if (meshClipFlags!=zCCamera::CLIP_FLAGS_FULL_WO_FAR)
			{
				// FIXME: bei clipFlags=0 braucht man die gueltige activeCamPos, aber _nicht_ die komplette camMatrixInv...!
				zCCamera::activeCam->SetUpFrustum(); 

				// FIXME: bbox: OS/WS ?
				zTCam_ClipType meshClip = zCCamera::activeCam->BBox3DInFrustum (mnode->nodeVisual->GetBBox3D(), meshClipFlags);
				if (meshClip==zCAM_CLIP_TRIV_OUT) goto dontRenderNode;
			};

			{
				//
				tmpRenderContext.clipFlags		= meshClipFlags;
				tmpRenderContext.cam			= renderContext.cam;
				zBOOL visible					= FALSE;

				// FIXME!
				// MorphMesh ? (derzeit noetig um die Lighting Info nur 1x fuer alle Model-Fragmente zu berechnen)
				if (mnode->nodeVisual->GetClassDef()==zCMorphMesh::GetStaticClassDef())
				{
					zCMorphMesh *morphMesh = static_cast<zCMorphMesh*>(mnode->nodeVisual);
					if (morphMesh->GetMorphMesh()) {
						// lighting
//						zMAT4 trafoWorldToObj		= (mnode->trafoObjToCam * renderContext.cam->GetVob()->trafoObjToWorld).InverseLinTrafo();
//						renderLightCont.Activate	(trafoWorldToObj);

						// Fatness/Scale Parameter fuer Koepfe "hacken"
						zREAL fat	= GetFatness()*0.35F;			if (zIsNegative(fat)) fat=0;
						zREAL scale	= GetFatness()*0.02F + 1.0F;

						// Mit dieser Trafo werden Normalen des Meshes vom Object/VobSpace in den LightSpace (= CamSpace)
						// transformiert.
						renderLightCont.SetTrafoObjToCam			(mnode->trafoObjToCam);
						resetRenderLightCont						= TRUE;
						morphMesh->GetMorphMesh()->SetLightingMode	(lightingMode);

						// FIXME: manchmal werden Gesichter immer noch von der falschen Seite beleuchtet.
						// hauptsächlich Indoor beobachtet ?????
						/*						if (renderContext.vob->GetGroundPoly() && renderContext.vob->GetGroundPoly()->GetSectorFlag())
						{
							zVEC3 colorDiffuseBak = renderLightCont.lightList[renderLightCont.numLights-1].colorDiffuse;
							renderLightCont.lightList[renderLightCont.numLights-1].colorDiffuse *= 2.5f;
							visible = morphMesh->Render					(tmpRenderContext, &renderLightCont, fat, scale);
							renderLightCont.lightList[renderLightCont.numLights-1].colorDiffuse = colorDiffuseBak;
						}
						else
						{*/
							visible = morphMesh->Render					(tmpRenderContext, &renderLightCont, fat, scale);
						//};

					};
				} else
				if (mnode->nodeVisual->GetClassDef()==zCProgMeshProto::GetStaticClassDef())
				{
					// FIXME: die "cam->camMatrix" wird ueber diesen Weg neu gesetzt, da sie noch nicht zum
					//        Renderer durchgedrungen ist! => Neustrukturieren!!
					tmpRenderContext.cam->SetTransform	(zCAM_TRAFO_WORLDVIEW, tmpRenderContext.cam->camMatrix);
					zCProgMeshProto *pmesh	= static_cast<zCProgMeshProto*>(mnode->nodeVisual);

					pmesh->RenderProgMesh	(tmpRenderContext, zPM_RENDER_FLAG_DONT_SET_TRANSFROM, 0, &renderLightCont);
				} else { 
					visible		= mnode->nodeVisual->Render(tmpRenderContext);
				};
				SetIsVisible	(GetIsVisible() || visible);
			};
dontRenderNode:; 

#ifdef zDEBUG_MDL_DRAW_NODE_OBB
//			mnode->modelMesh->GetBBox3D().Draw();
			mnode->nodeVisual->GetOBBox3D()->Draw();
#endif
		};

		if (s_drawSkeleton) {
			if (mnodeParent) 
			{
				zlineCache.LineCS3D (mnodeParent->trafoObjToCam.GetTranslation(), mnode->trafoObjToCam.GetTranslation());
			}
			{ 
				if (mnode->trafoObjToCam.GetTranslation()[VZ]>0) {
					int		col		= GFX_RED;
					zSTRING name(mnode->protoNode->GetName());
					if (mnode->IsRootNode()) {
						col		= GFX_GREEN;
						name	= "root: >"+name+"<";
					};
	//				zlineCache.LineCS3D (mnode->trafoObjToCam.GetTranslation()-zVEC3(5,0,0), mnode->trafoObjToCam.GetTranslation()+zVEC3(5,0,0),col);
	//				zlineCache.LineCS3D (mnode->trafoObjToCam.GetTranslation()-zVEC3(0,5,0), mnode->trafoObjToCam.GetTranslation()+zVEC3(0,5,0),col);

					const zPOINT3& pos = mnode->trafoObjToCam.GetTranslation();
					zlineCache.LineCS3D (pos, pos+mnode->trafoObjToCam.GetUpVector		()*10,GFX_WHITE);
					zlineCache.LineCS3D (pos, pos+mnode->trafoObjToCam.GetAtVector		()*10,GFX_YELLOW);
					zlineCache.LineCS3D (pos, pos+mnode->trafoObjToCam.GetRightVector	()*10,GFX_ORANGE);

					zREAL dist = mnode->trafoObjToCam.GetTranslation().LengthApprox();
					if (dist<40) {
						const zPOINT3& pos = mnode->trafoObjToCam.GetTranslation();
						int xscr, yscr;
						zCCamera::activeCam->Project (&pos, xscr, yscr);
						screen->Print (screen->anx(xscr), screen->any(yscr), name);
					};
				};
			};
		};
	};

	// 
	if (resetRenderLightCont)
	{
		// FIXME: vob->trafoObjToWorld ist hier nicht ganz korrekt. Man sollte eigentlich die 
		// node trafo nehmen, da es anis gibt, die die trafo nicht auf den vob übertragen (bank, sessel, etc.)
		// ACHTUNG: nur während Human-Mobinteraktionen!!

		if (nodeList.GetNum()>=1 && n_bIsInMobInteraction)
		{
			zMAT4 rootTrafoToCam= Alg_Identity3D();
			zMAT4 rootTrafo     = nodeList[0]->GetTrafoObjToCam();
			zVEC3 oldUp			= rootTrafo.GetUpVector();
			zVEC3 oldAt			= rootTrafo.GetAtVector();
			zVEC3 oldRight		= rootTrafo.GetRightVector();
			rootTrafoToCam.SetTranslation(rootTrafo.GetTranslation());
			rootTrafoToCam.SetAtVector		(oldRight);
			rootTrafoToCam.SetUpVector		(oldAt);
			rootTrafoToCam.SetRightVector	(oldUp);
			renderLightCont.SetTrafoObjToCam(rootTrafoToCam);
		}
		else renderLightCont.SetTrafoObjToCam (renderContext.cam->GetTransform(zCAM_TRAFO_VIEW) * renderContext.vob->trafoObjToWorld);
	}

	// Distanz Model/Camera berechnen
	// nodeList[0] = RootNode !
/*	if (mnode->protoNode->rootNode) { 
		modelDistanceToCam = mnode->trafoObjToCam.GetTranslation().LengthApprox();
	};*/
	if (nodeList.GetNum()>=1)
		modelDistanceToCam = nodeList[0]->trafoObjToCam.GetTranslation().LengthApprox();
};

#if 0
void zCModel::CalcNodeShadowDim () 
{
	if (nodeShadowDim.GetNum()>0) return;

	//
	nodeShadowDim.AllocAbs			(nodeList.GetNum());
	nodeShadowDim.MarkNumAllocUsed	();
	
	zVEC3 dimRay;
	dimRay = homeVob->trafoObjToWorld.GetRightVector();

	{
		for (int j=0; j<nodeShadowDim.GetNum(); j++)
			nodeShadowDim[j] = 11.0F;
		for (int i=0; i<meshSoftSkinList.GetNum(); i++) 
		{
			zCMeshSoftSkin *mesh = meshSoftSkinList[i];
			for (int j=0; j<mesh->nodeOBBList.GetNum(); j++) 
			{
				int nodeIndex			= mesh->nodeIndexList[j];
				zCModelNodeInst *node	= nodeList[nodeIndex];
				nodeShadowDim[nodeIndex]	= mesh->nodeOBBList[j]->GetMaxExtent();

//					nodeShadowDim[nodeIndex]	= zMax (nodeShadowDim[nodeIndex], 10.0F);
//					nodeShadowDim[nodeIndex]	= zMin (nodeShadowDim[nodeIndex], 25.0F);

				//
				zMAT4 trafoNodeToWorld;
				trafoNodeToWorld = (zCCamera::activeCam->GetVob()->trafoObjToWorld) * node->trafoObjToCam;

				//
				if (!mesh->nodeOBBList[j]) continue;
				zCOBBox3D obb;
				obb = *(mesh->nodeOBBList[j]);
				obb.Transform (trafoNodeToWorld);
				zREAL dim = 0;
				dim = zMax(dim, zAbs(dimRay * (obb.extent[0] * obb.axis[0])));
				dim = zMax(dim, zAbs(dimRay * (obb.extent[1] * obb.axis[1])));
				dim = zMax(dim, zAbs(dimRay * (obb.extent[2] * obb.axis[2])));
				dim *= 1.0F; 
				nodeShadowDim[nodeIndex]	= dim;

//					nodeShadowDim[nodeIndex]	= zMax (nodeShadowDim[nodeIndex], 10.0F);
//					nodeShadowDim[nodeIndex]	= zMin (nodeShadowDim[nodeIndex], 40.0F);
				zClamp (nodeShadowDim[nodeIndex], 10.0F, 50.0F);
			};
		};
	};

};

static zCPolygon* nodePoly=0;
struct zTBoneHit {
	zVEC3		groundPos;
	zVEC3		normal;
};

/* ----------------------------------------------------------------------
	
    zCModel::RenderNodeShadow()	

	17.11.2000	[Moos]	
                auf neue Vertex-Klasse umgestellt

   ---------------------------------------------------------------------- */
void zCModel::RenderNodeShadow () 
{
	if (!nodeShadowEnabled) return;

	if (!nodePoly) {
		nodePoly			= zNEW(zCPolygon);
		zCPolygon	*poly	= nodePoly;
		zCVertex	*vert1	= zNEW(zCVertex);
		zCVertex	*vert2	= zNEW(zCVertex);
		zCVertex	*vert3	= zNEW(zCVertex);
		zCVertex	*vert4	= zNEW(zCVertex);
		zCMaterial	*mat	= zNEW(zCMaterial);
		mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_MUL);
		mat->SetTexture			(zSTRING("boneShadow2.TGA"));
		
		// Polys mit Vertices/Material verbinden
		poly->SetVertices	(vert1, vert2, vert3, vert4, FALSE);
		poly->SetMaterial	(mat);
		poly->feature[0]->texu	= 1.0F;		poly->feature[0]->texv	= 0.0F;
		poly->feature[1]->texu	= 0.0F;		poly->feature[1]->texv	= 0.0F;
		poly->feature[2]->texu	= 0.0F;		poly->feature[2]->texv	= 1.0F;
		poly->feature[3]->texu	= 1.0F;		poly->feature[3]->texv	= 1.0F;
		zCOLOR col(255,255,255,200);
		for (int k=0; k<4; k++) {
			col.alpha = 255;
			poly->feature[k]->lightStat = col; 
			poly->feature[k]->lightDyn	= col;
		};
	};

	//
	CalcNodeShadowDim();

	//
	zMAT4 trafoCamToWorld;
	trafoCamToWorld		= zCCamera::activeCam->GetVob()->trafoObjToWorld;

	zCArray<zTBoneHit>	groundPosList(nodeList.GetNum());
	zCWorld				*world	= zCCamera::activeCam->GetVob()->GetHomeWorld();
	zVEC3				rayDir	(-1,-1,0);
	rayDir.Normalize();
	rayDir *= 1000;

	groundPosList.MarkNumAllocUsed ();

	zCCamera::activeCam->Activate();

	for (int i=0; i<nodeList.GetNum(); i++) 
	{
		zCModelNodeInst	*node		= nodeList[i];
		zCModelNodeInst	*nodeParent	= node->GetParentNode();

		// slots skippen
		const zSTRING& nodeName = node->protoNode->GetName();
		if (nodeName.Length()>=2) {
			if (nodeName[0]=='Z')
			if (nodeName[1]=='S')	
			if (nodeName!="ZS_HELMET")
				continue;
		};

		zPOINT3 nodePos = node->trafoObjToCam.GetTranslation();
		nodePos			= trafoCamToWorld * nodePos;

		if (world->TraceRayNearestHit (nodePos, rayDir, (zCVob*)0, zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_VOB_IGNORE | zTRACERAY_STAT_POLY))
		if (world->traceRayReport.foundPoly)
		{
			groundPosList[i].groundPos	= (world->traceRayReport.foundIntersection);
			groundPosList[i].normal		= (world->traceRayReport.foundPoly->GetNormal());

			if (nodeParent) 
			{
				int pindex;
				for (int j=0; j<nodeList.GetNum(); j++) 
				{
					if (nodeList[j]==nodeParent) {
						pindex = j;
						break;
					};
				};

//					zlineCache.Line3D (groundPosList[i], groundPosList[pindex]);

				if ((groundPosList[i].normal * groundPosList[pindex].normal)<0.5) continue;

				// nodepoly verts
				zVEC3 up, at, right, rightParent;
				at			= groundPosList[pindex].groundPos - groundPosList[i].groundPos;
				up			= world->traceRayReport.foundPoly->GetNormal();
				zREAL len	= at.LengthApprox();
				zREAL boneLen = 4*(node->trafo.GetTranslation()).LengthApprox();
				if (len>boneLen) continue;
				at			/= len;
				len			*= 0.2F;
				right		= at ^ up;
/*				right		= 15 * right;
//				right		= len * right;
				rightParent	= right;*/
				rightParent	= right * nodeShadowDim[pindex]	* 2.0F;
				right		= right * nodeShadowDim[i]		* 2.0F;

				zVEC3 ofs	= up * 5.0F;

				zVEC3 start	= groundPosList[i].groundPos		- at*5;
				zVEC3 end	= groundPosList[pindex].groundPos	+ at*5;

				nodePoly->vertex[3]->position	= start	- right			+ ofs;
				nodePoly->vertex[2]->position	= start	+ right			+ ofs;
				nodePoly->vertex[1]->position	= end	+ rightParent	+ ofs;
				nodePoly->vertex[0]->position	= end	- rightParent	+ ofs;

				for (int k=0; k<4; k++)
					nodePoly->vertex[k]->ResetVertexTransform();
				// Bone rendern
				if (nodePoly->ClipToFrustum ()) { 
					if (nodePoly->TransformProjectLight ()) 
					{
						zrenderer->DrawPoly (nodePoly); 
					};
				};

			};
		};
	};
};
#endif


/*
  // Model-Bone-Glow

void zCModel::RenderNodeShadow () 
{

	if (!nodePoly) {
		nodePoly			= zNEW( zCPolygon;
		zCPolygon	*poly	= nodePoly;
		zCVertex	*vert1	= zNEW( zCVertex;
		zCVertex	*vert2	= zNEW( zCVertex;
		zCVertex	*vert3	= zNEW( zCVertex;
		zCVertex	*vert4	= zNEW( zCVertex;
		zCMaterial	*mat	= zNEW( zCMaterial;
		mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_ADD);
		mat->SetTexture			(zSTRING("boneGlow.TGA"));
//		mat->SetTexture			(zSTRING("zflare2.TGA"));
		mat->SetAlpha			(255);
		
		// Polys mit Vertices/Material verbinden
		poly->SetVertices	(vert1, vert2, vert3, vert4, FALSE);
		poly->SetMaterial	(mat);
		poly->feature[0]->texu	= 1.0F;		poly->feature[0]->texv	= 0.0F;
		poly->feature[1]->texu	= 0.0F;		poly->feature[1]->texv	= 0.0F;
		poly->feature[2]->texu	= 0.0F;		poly->feature[2]->texv	= 1.0F;
		poly->feature[3]->texu	= 1.0F;		poly->feature[3]->texv	= 1.0F;
		zCOLOR col(255,255,255,100);
		for (int k=0; k<4; k++) {
			col.alpha = 255;
			poly->feature[k]->lightStat = col; 
			poly->feature[k]->lightDyn	= col;
		};
	};


	//
	zMAT4 trafoCamToWorld;
	trafoCamToWorld		= zCCamera::activeCam->GetVob()->trafoObjToWorld;

	zCWorld				*world	= zCCamera::activeCam->GetVob()->GetHomeWorld();

//	zCCamera::activeCam->Activate();

	zCCamera::activeCam->camMatrix.ResetRotation	();
	zCCamera::activeCam->camMatrix.SetTranslation	(0);
	zCCamera::activeCam->camMatrixInv.ResetRotation	();
	zCCamera::activeCam->camMatrixInv.SetTranslation(0);

	zCCamera::activeCam->camMatrixInv.GetTranslation( zCCamera::activeCamPos );
	zCCamera::activeCam->SetUpFrustum				(); 

	for (int i=0; i<nodeList.GetNum(); i++) 
	{
		zCModelNodeInst	*node		= nodeList[i];
		zCModelNodeInst	*nodeParent	= node->GetParentNode();

		// slots skippen
		const zSTRING& nodeName = node->protoNode->GetName();
		if (nodeName.Length()>=2) {
			if (nodeName[0]=='Z')
			if (nodeName[1]=='S')	
			if (nodeName!="ZS_HELMET")
				continue;
		};

		{
			if (nodeParent) 
			{
				int pindex;
				for (int j=0; j<nodeList.GetNum(); j++) 
				{
					if (nodeList[j]==nodeParent) {
						pindex = j;
						break;
					};
				};

				//
				zPOINT3 nodePos			= node->		trafoObjToCam.GetTranslation();		// camSpace
				zPOINT3 nodeParentPos	= nodeParent->	trafoObjToCam.GetTranslation();		// camSpace

				zVEC3	dir		= (nodeParentPos-nodePos);
				zREAL	len		= dir.LengthApprox();
				dir				/= len;
				zVEC3	right	= dir ^ zVEC3(0,0,1);
				len = zMax (20.0F, len);
				right			*= len * 0.7F;

				nodePos			-= dir * (len * 0.2F);

				nodePoly->vertex[3]->position	= nodePos		- right;
				nodePoly->vertex[2]->position	= nodePos		+ right;
				nodePoly->vertex[1]->position	= nodeParentPos	+ right;
				nodePoly->vertex[0]->position	= nodeParentPos	- right;

				for (int k=0; k<4; k++) {
					nodePoly->vertex[k]->transformed = 0;
				};
				// Bone rendern
				if (nodePoly->ClipToFrustum ()) 
				{ 
//					for (int k=0; k<nodePoly->numClipVert; k++) {
//						zCCamera::activeCam->Project (nodePoly->clipVert[k]);
//					};

					if (nodePoly->TransformProjectLight ()) 
					{
						zrenderer->DrawPoly (nodePoly); 
					};
				};

			};
		};
	};
};
*/

zBOOL zCModel::Render (zTRenderContext& renderContext) 
{
	SetIsVisible	(FALSE);

	// Texture Einstellungen in die Textures eintragen
	UpdateMeshLibTexAniState();

	// Beleuchtung
	zCRenderLightContainer			renderLightCont; 
	zTPMLightingMode				lightingMode;

	// 1500.0F (distance CM) / 380435.0F (Volumen cm^3) = 0.00394285F
	const zREAL factor = zREAL(0.00394285F) * bbox3DLocalFixed.GetVolume();

	if ((renderContext.distVobToCam>factor) && (renderContext.vob->GetCharacterClass()!=zCVob::zVOB_CHAR_CLASS_NONE))
	{
		// nur Char-Classes PC und NPC bekommen exact Lighting, alle anderen nur Prelit
		// Beleuchtungs 'LOD': bei groesserer Distanz auf prelit schalten
		// FIXME: Volumen-abhaengig machen !!!
		lightingMode					= zPM_LIGHTING_MODE_PRELIT;
		renderLightCont.SetDoPrelight	(TRUE);
		renderLightCont.SetPreLightDist (factor);
		renderLightCont.CollectLights	(renderContext);
		
//		if (renderLightCont.GetSmoothPrelit())
//		{	
//			lightingMode					= zPM_LIGHTING_MODE_EXACT;
//			renderLightCont.SetDoPrelight	(FALSE);
//		}

		// Das Activate() hier sollte eigentlich noetig sein, steht aber aus Robustheitsgruenden hier.
		renderLightCont.Activate		(renderContext.cam->GetTransform (zCAM_TRAFO_VIEW));
	} else {
		lightingMode					= zPM_LIGHTING_MODE_EXACT;
		renderLightCont.SetDoPrelight	(FALSE);
		renderLightCont.CollectLights	(renderContext);
		renderLightCont.Activate		(renderContext.cam->GetTransform (zCAM_TRAFO_VIEW));
	};

	//
	if (modelScaleOn) 
	{
		zCCamera::activeCam->camMatrix.PreScale (modelScale);
	};

	//
	zCArray<zMAT4*> nodeTrafoList;
	nodeTrafoList.AllocAbs			(nodeList.GetNum());
	nodeTrafoList.MarkNumAllocUsed	();
	RenderNodeList					(renderContext, nodeTrafoList, renderLightCont, lightingMode);

	// FIXME: hier an dieser Stelle ? oder als Virtual in Vob::EndMovement ?
	// FIXME: Optimierungen:
	// - hier nur bei wirklichem Movement (rot/trans), jeden 2. Frame bei hoher Dist
	UpdateAttachedVobs();

	// SoftSkins
	if (!GetDrawHandVisualsOnly())
	if (meshSoftSkinList.GetNumInList()>0) 
	{
		// Die Trafos der Nodes sind im bereits: localSpace => camSpace,
		// also ist die renderTrafo einfach Identity
		zCCamera::activeCam->camMatrix.MakeIdentity();
		zCCamera::activeCam->camMatrixInv = zCCamera::activeCam->camMatrix;				// fuer frustum-planes
		zCCamera::activeCam->camMatrixInv.GetTranslation( zCCamera::activeCamPos );		// fuer backfaceCulling
		zCCamera::activeCam->SetUpFrustum(); 

		// folgende Zeile macht beim TNL-Renderer kein Sinn mehr..
//		if (renderContext.distVobToCam>1000)	renderContext.clipFlags= 0;	// clamp to Screen !!

		for (int i=0; i<meshSoftSkinList.GetNumInList(); i++) {
			meshSoftSkinList[i]->SetLightingMode	(lightingMode);
			meshSoftSkinList[i]->RenderSoftSkin		(renderContext, nodeTrafoList, &renderLightCont, GetFatness());
		};

		// FIXME:
		SetIsVisible(TRUE);
	};

	//
	//RenderNodeShadow();

//screen->Print (0,2000, zSTRING(aniMeshLibList.GetNumInList()));
	return GetIsVisible();
};

static zCList<zCModelNodeInst>	*nodeCollisionList;

void zCModel::CheckNodeCollisionList (const zCOBBox3D& obb, zMATRIX4& nodeCollisionMatrix) {
	for (int i=0; i<nodeList.GetNum(); i++)
	{
		zCModelNodeInst		*mnode				= nodeList[i]; 
		zCModelNodeInst		*mnodeParent		= mnode->GetParentNode();

		if (mnodeParent)	mnode->trafoObjToCam= mnodeParent->trafoObjToCam	* mnode->trafo;
		else				mnode->trafoObjToCam= nodeCollisionMatrix			* mnode->trafo;
		if (mnode->nodeVisual) 
		{
			// trafoThisToObb
			// trafoLimbToWeapon
			zCOBBox3D *nodeObb = mnode->nodeVisual->GetOBBox3D();
			if (nodeObb)
			if (obb.TestIntersectionTree (nodeObb, mnode->trafoObjToCam)) { 
				nodeCollisionList->Insert (mnode);
			};
		};
	};
};

void zCModel::CheckNodeCollision (zCModel					*model, 
								  zCModelNodeInst			*weapNode, 
								  zMATRIX4&					trafoThisToModel, 
								  zCList<zCModelNodeInst>&	resNodeList) 
{
	// this			= Test-Model gegen das die Waffe gecheckt wird
	// model-Param	= Waffen-Model
	if (!weapNode)				return;
	if (!weapNode->nodeVisual)	return;
	zMATRIX4			trafoWeapToModel		= model->GetTrafoNodeToModel(weapNode);
	zMATRIX4			trafoThisModelToWeapon;
	if (modelScaleOn)	trafoThisModelToWeapon	= trafoWeapToModel.Inverse		  () * trafoThisToModel;
	else				trafoThisModelToWeapon	= trafoWeapToModel.InverseLinTrafo() * trafoThisToModel;

//	trafoWorldToTest = (trafoModelToWorld * trafoNodeToModel).InverseLinTrafo();

	// nicht optimal ? 
	// - nodes werden evtl. mehrfach getestet
	// - einige nodes sind fuer CD voellig irrelevant

	zCOBBox3D* weapOBB = weapNode->nodeVisual->GetOBBox3D();
	if (!weapOBB) return;

	// Node-Meshes, trafos berechnen
	nodeCollisionList	= &resNodeList;
	CheckNodeCollisionList (*weapOBB, trafoThisModelToWeapon);

	// SoftSkin-Meshes
	for (int i=0; i<meshSoftSkinList.GetNum(); i++) 
	{
		zCMeshSoftSkin *mesh = meshSoftSkinList[i];
		for (int j=0; j<mesh->nodeOBBList.GetNum(); j++) 
		{
			zCModelNodeInst *mnode = nodeList[mesh->nodeIndexList[j]];
			if (weapOBB->TestIntersectionTree (mesh->nodeOBBList[j], mnode->trafoObjToCam)) { 
				nodeCollisionList->Insert (mnode);
			};
		};
	};
};

/*
zMATRIX4 zCModel::GetTrafoNodeToModel (zCTree<zCModelNodeInst>* node) {
	zMATRIX4 trafoObjToParent;
	zCModelNodeInst	*mnode = node->GetData();
	if (!mnode) return trafoObjToParent;
	trafoObjToParent= mnode->trafo;
	node			= node->GetParent();

	// modelScale
//	trafoObjToParent= trafoObjToParent * Alg_Scaling3D(modelScale);

	while (node) {
		zCModelNodeInst	*mnode = node->GetData();
		if (mnode) trafoObjToParent = mnode->trafo * trafoObjToParent;
		node = node->GetParent();
	};

	if (modelScaleOn) {
	//	return trafoObjToParent;
	//	return Alg_Scaling3D(modelScale) * trafoObjToParent;
	//	return trafoObjToParent * Alg_Scaling3D(modelScale);
		trafoObjToParent = Alg_Scaling3D(modelScale) * trafoObjToParent;
	//	trafoObjToParent.PreScale(modelScale);
		trafoObjToParent.MakeOrthonormal();		// FIXME: ????????
	};

	return trafoObjToParent;
};
*/

zMATRIX4 zCModel::GetTrafoNodeToModel (zCModelNodeInst* mnode) {
	zMATRIX4 trafoObjToParent;
	if (!mnode) return trafoObjToParent;
	trafoObjToParent= mnode->trafo;
	mnode			= mnode->GetParentNode();

	// modelScale
//	trafoObjToParent= trafoObjToParent * Alg_Scaling3D(modelScale);

	while (mnode) {
		trafoObjToParent= mnode->trafo * trafoObjToParent;
		mnode			= mnode->GetParentNode();
	};

	if (modelScaleOn) {
	//	return trafoObjToParent;
	//	return Alg_Scaling3D(modelScale) * trafoObjToParent;
	//	return trafoObjToParent * Alg_Scaling3D(modelScale);
		trafoObjToParent = Alg_Scaling3D(modelScale) * trafoObjToParent;
	//	trafoObjToParent.PreScale(modelScale);
		trafoObjToParent.MakeOrthonormal();		// FIXME: ????????
	};

	return trafoObjToParent;
};

// =============================================================================
// =============================================================================

// =============================================================================
// =============================================================================

void zCModel::SetRandAnisEnabled (const zBOOL b) {
	randAnisEnabled=b;		
	if (b) {
		// timer aller aktiven RandAnis reseten
		// FIXME: temp ?
		for (int i=0; i<numActiveAnis; i++) {
			zCModelAniActive *ani = aniChannels[i];
			if (ani->aniAttachment) {
				if (ani->aniAttachment->randAniList.GetNum()>0) {
					// start-delay fuer eventuelle RandAnis
					ani->randAniTimer	= ani->aniAttachment->randAniFreq * zREAL(1000) * zREAL(1);
				};
			};
		};
	};
};

zCModelAniActive* zCModel::GetActiveAni (zTModelAniID aniID) const
{
	for (int i=0; i<numActiveAnis; i++)
		if (aniChannels[i]->protoAni->GetAniID() == aniID)	return aniChannels[i];
	return 0;
};

zCModelAniActive* zCModel::GetActiveAni (zCModelAni* modelAni) const
{
	for (int i=0; i<numActiveAnis; i++)
		if (aniChannels[i]->protoAni == modelAni)	return aniChannels[i];
	return 0;
};

void zCModel::StopAni (zTModelAniID	aniID)
{
	StopAni (GetAniFromAniID (aniID));
};

void zCModel::StopAni (zCModelAni *modelAni) 
{
	if (!modelAni) return;

	StopAni (GetActiveAni (modelAni));
};

void zCModel::StopAni (zCModelAniActive *activeAni) 
{
	// idee:
	// diese ani wird nur komplett gestoppt, wenn
	// im nächsten frame (bzw, innerhalb eines kurzen zeitraums)
	// _kein_ startAni auf demselben layer stattfindet
	// ansonsten wird für diese ani die bald kommende ani als folge-ani
	// eingetragen
	// allerdings bedeutet das auch, das z.B. Turn-Anis immer noch
	// abrupt beendet werden würden (drache poppt auf boden nach beenden)
	// da diese sich auf einem höheren layer befinden
	if (!activeAni) return;

	// !delFromChannels => nur Node-Controll Einfluss korrigieren
	zCModelAni *protoAni = activeAni->protoAni;

//	int			actLayer = protoAni->layer;

	int			i;
	int			aniNr;

	// ani wird aus allen beteiligten nodes ausgetragen
	for (i=0; i<protoAni->numNodes; i++) {
//		modelAni->nodeList[i]->RemoveNodeAni (modelAni);
		nodeList[protoAni->nodeIndexList[i]]->RemoveNodeAni (activeAni);
	};

	// Ani aus den aniChannels loeschen
	for (aniNr=0; aniNr<numActiveAnis; aniNr++)
	{
		if (aniChannels[aniNr]==activeAni)
		{
			for (int j=aniNr; j<numActiveAnis-1; j++) {
				aniChannels[j] = aniChannels[j+1];
			};
			numActiveAnis--;
			break;
		};
	};

	// abhaengige Anis werden 'sanft' gestoppt: FadeOut
	if (activeAni->aniAttachment) {
		for (i=0; i<activeAni->aniAttachment->randAniList.GetNum(); i++) {
			FadeOutAni (activeAni->aniAttachment->randAniList[i].randAniProtoID);
		};
	};

	// durch diese Ani aktivierte MeshLibs werden entfernt
	// fuer ani meshLib (OBSOLETE)
/*	if (protoAni->meshLib) {
		RemoveAniMeshLib (activeAni); 
	};*/

	// uebrige AniEvents ausfuehren, diese duerfen nicht verschluckt werden !
	if (activeAni->advanceDir==+1)	activeAni->actFrame	= zREAL(protoAni->numFrames);
	else 							activeAni->actFrame	= 0;
	DoAniEvents (activeAni);

	//
	activeAni->MarkUnused();
};

const zSTRING* zCModel::GetAnyAnimation ()
{
	if ((modelProtoList.GetNum()<=0) || (modelProtoList[0]->protoAnis.GetNum()<=0))	return 0;
	return &(GetAniFromAniID(0)->GetAniName());
};

/* ----------------------------------------------------------------------
	
     zCModel::GetAniTransLerp()
     
     holt die Translationsinformationen aus der Animation und lerpt
     dabei zwischen zwei Frames.

	 15.12.2000	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */


zVEC3 zCModel::GetAniTransLerp  (zCModelAni* protoAni, zREAL progress, int nodeNumber) const
{
    int numFrames = protoAni->GetNumFrames();
    int frame     = (int)floor(progress * (numFrames-1));

    if (frame >= numFrames-1)
        frame = numFrames-2;

    zREAL a = progress * (numFrames-1) - frame;
    return zLerp(a, GetAniTrans(protoAni, frame, nodeNumber), GetAniTrans(protoAni, frame+1, nodeNumber));
}

void zCModel::StartAni (const zSTRING& aniName, const int startMode) 
{
	zCModelAni *modelAni = GetAniFromAniName(aniName);
	if (!modelAni) 
	{
		zERR_WARNING ("D: zModel.cpp(zCModel::StartAni): Ani not found: "+aniName);
		return;
	};
	StartAni (modelAni, startMode);
};

void zCModel::StartAni (zTModelAniID aniID, const int startMode)
{
	StartAni (GetAniFromAniID(aniID), startMode);
};

void zCModel::StartAni (zCModelAni* protoAni, const int startMode) 
{
	// falls neue Ani eine alte Ani überdeckt: diese raussuchen & den nextAni-Override eintragen

	// Regel:
	// Anis desselben Layers sind exklusiv, d.h. schmeissen sich gegenseitig raus.
	// Anis eines höheren Layers überdecken Nodes kleinerer Layer
	// Layer1 = Basis Layer, der einzige Layer, der die Pos/Rot des Vobs beeinflusst
	//

	// Wenn eine Ani durch eine andere Ani im selben Layer abgeloest wird, dann darf die alte Ani
	// nicht mehr geloopt werden, sondern muss auf dem letzten Frame bleiben, bis sie ganz ausgefadet
	// ist. => 'isFadingOut'
	
	if (!protoAni) return;

	// Den Ani-Typ der zu startenden Ani auswerten.
	zREAL			aniBlendOutOverride	= protoAni->GetBlendOutSpeed();
	zREAL			aniBlendInOverride	= protoAni->GetBlendInSpeed();
	zREAL			aniBlendOutStopped;

	zTMdl_AniType	aniType = protoAni->GetAniType();
	switch (aniType) {
	case zMDL_ANI_TYPE_BLEND:
		ShowAniListAdd		(protoAni);
// @@@
// aniEvents einer aniBlend werden alle auf 1mal zu Beginn gespielt
//protoAni->actAniEvent = 0;
//actFrame	= 99999.0F;
//advanceDir	= +1;
//DoAniEvents	(protoAni);
		aniBlendOutStopped	= aniBlendOutOverride;
		protoAni			= GetNextAni (protoAni);			if (!protoAni)	return;
		aniBlendOutOverride	= protoAni->GetBlendOutSpeed();
		break;
	case zMDL_ANI_TYPE_SYNC:
		ShowAniListAdd (protoAni);
		protoAni = GetNextAni (protoAni);
		break;
	case zMDL_ANI_TYPE_BATCH: {
		assert (protoAni->numAniEvents==1);
		const zCModelAniEvent& event = protoAni->aniEvents[0];
		for (int i=0; i<event.frameNr; i++) {
			// im Batch enthaltene Anis nacheinander rekursiv starten..
			StartAni (event.string[i]); 
		};
		// .. und raus hier.
		return;
		break;
		};
	case zMDL_ANI_TYPE_DISABLED:
		return;
		break;
	};
	assert (protoAni);

	// FIXME: opti
	zCModelAniActive *activeAni = GetActiveAni (protoAni);

	// diesselbe Ani läuft bereits => exit
	if (activeAni) {
		// in folgenden Faellen soll eine bereits laufende Ani restartet werden:
		// - START_FORCE
		// - ani fadet bereits aus
		if ((startMode!=zMDL_STARTANI_FORCE) && (!activeAni->IsFadingOut())) return;
		activeAni=0;
	};

	newAniStarted	= TRUE;

	// passenden Ani-Channel raussuchen (entw. alter Channel desselben Layers oder neuer Channel)
	int			actLayer = protoAni->layer;
	int			aniNr;
	zREAL		percent;

	for (aniNr=0; aniNr<numActiveAnis; aniNr++)
	{
//		if (aniChannels[aniNr]==modelAni) return;

		// andere Ani im selben Layer aktiv => diese andere Ani ausfaden/Ende abwarten
		if (aniChannels[aniNr]->protoAni->layer==actLayer)
		{
			if ((startMode==zMDL_STARTANI_FORCE) || (aniChannels[aniNr]->protoAni==protoAni)) {
				// alte Ani stoppen/loeschen
				StopAni (aniChannels[aniNr]);
				// und neue starten...
				aniNr = numActiveAnis;
				goto exitSearch;
			};
			// soll die neue Ani erst am Ende er aktuellen (state-) Ani gestartet werden ?
			// A) 'end-sync' ani wird das erste mal gestartet & eingetragen
			// B) 'end-sync' ani wird wiederholt gestartet, obwohl sie schon eingetragen ist 
			// C) 'end-sync' ani soll schliesslich als aniOverride gestartet werden
			if (aniChannels[aniNr]->nextAniOverride!=protoAni) {
				if (protoAni->FlagSyncWithEnd())
				{ 
					// a)
					// => als nextAniOverride eintragen
					aniChannels[aniNr]->nextAniOverride = protoAni;
					return;
				} else {
 					// .. sonst alte Ani ausfaden
					// Bei Ani-Blend: blendOutSpeed overriden !
					if (aniType==zMDL_ANI_TYPE_BLEND) {
						aniChannels[aniNr]->SetBlendOutOverride (aniBlendOutStopped);
					};
					// FIXME: blend0 Anis gleich stoppen !!
// @@@
					const zBOOL noFadeBlend =	(aniChannels[aniNr]	->GetBlendOutSpeed()== zMDL_ANI_BLEND_OUT_ZERO) && 
												(protoAni			->GetBlendInSpeed ()== zMDL_ANI_BLEND_IN_ZERO);
					if (noFadeBlend) {
						StopAni		(aniChannels[aniNr]);
					} else {
						FadeOutAni	(aniChannels[aniNr]);
					};
					aniNr = numActiveAnis;
					goto exitSearch;	// ???
				};
			} else {
				// b)
				if (startMode!=zMDL_STARTANI_ISNEXTANI) return;
				// c) ..
			};

			if (aniType==zMDL_ANI_TYPE_SYNC) percent = aniChannels[aniNr]->GetProgressPercent();
		};
	};

exitSearch:;

	// noch Platz fuer neue Ani ?
	if (aniNr>=zMDL_MAX_ANIS_PARALLEL) return;

	// naechste freie 'zCModelAniActive' ermitteln
	AssertActiveAniListAlloced ();
	for (int i=0; i<zMDL_MAX_ANIS_PARALLEL; i++) 
	{
		if (activeAniList[i].IsUnused()) {
			activeAni	= &activeAniList[i];
			break;
		};
	};
	if (!activeAni)	return;

	// Force / new
	// aniChannel fuellen
	aniChannels[aniNr]				= activeAni;
	activeAni->protoAni				= protoAni;
	activeAni->nextAni				= GetNextAni (protoAni);
	activeAni->nextAniOverride		= 0;
	activeAni->isFirstTime			= TRUE;
	activeAni->SetBlendInOverride	(aniBlendInOverride);		// evtl. durch eine aniBlend gesteuert
	activeAni->SetBlendOutOverride	(aniBlendOutOverride);		
	if (protoAni->aniDir== zMDL_ANIDIR_FORWARD) {
		activeAni->actFrame			= 0.0F;
		activeAni->advanceDir		= +1;
		activeAni->actAniEvent		= 0;
	} else {						
		activeAni->actFrame			= float(protoAni->numFrames-1) + 0.9999F;
		activeAni->advanceDir		= -1;
		activeAni->actAniEvent		= protoAni->numAniEvents-1;
	};
	if (aniType==zMDL_ANI_TYPE_SYNC) {
		activeAni->SetProgressPercent (percent);
	};
	activeAni->isFadingOut			= FALSE;
	activeAni->rotFirstTime			= TRUE;
	activeAni->combAniX				= activeAni->combAniY	= 0.5F;
	activeAni->aniAttachment		= SearchAniAttachList (protoAni->GetAniID());

	// aniAttachment
	if (activeAni->aniAttachment) {
		activeAni->randAniTimer		= activeAni->aniAttachment->randAniFreq * zREAL(1000) * zREAL(1);		// start-delay fuer eventuelle RandAnis
	};

	// ani wird in alle beteiligten nodes eingetragen
	for (i=0; i<protoAni->numNodes; i++) {
		nodeList[protoAni->nodeIndexList[i]]->AddNodeAni (activeAni);
	};

	if (aniNr>=numActiveAnis) numActiveAnis++;

	// Tools / temp
	ShowAniListAdd (protoAni);

	// Event gebundene Daten precachen, damit sie hoffentlich schon verfuegbar sind, wenn sie spaeter gebraucht werden
	protoAni->PrecacheAniEventData ();

	// Falls keine einzige Ani einen Root-Node enthaelt
	if (protoAni->FlagRotatesVob())		activeAni->lastRotQuat	= activeAni->thisRotQuat = zCQuat(0);
	if (protoAni->FlagMovesVob()) {
		if (protoAni->rootNodeIndex!=-1) { 
			activeAni->lastPos	= 
			activeAni->thisPos	= protoAni->GetTrans ((int)zFloor(activeAni->actFrame), protoAni->rootNodeIndex);
		} else {
			activeAni->thisPos	= activeAni->lastPos		= 0;
		};
	};

//	zERR_MESSAGE (5, 0, "D: MDL: StartAni: "+modelAni->protoAni->GetAniName()+" Dir: "+zSTRING(aniChannels[aniNr]->advanceDir)+" StartFrame: "+zSTRING(aniChannels[aniNr]->actFrame)+", Channel: "+zSTRING(aniNr));
};

void zCModel::HostVobRemovedFromWorld (zCVob* hostVob, zCWorld* hostWorld) 
{
	// abhaengige, loopende PFX entfernen
	// (Alternative: StopEmitterOutput+Release, aber dann als transient markieren, damit sie nicht in saveGames geraten)
	for (int i=0; i<startedVobFX.GetNum(); i++) 
	{
		zCVob *vobFX = startedVobFX[i].vob;
		zERR_ASSERT (vobFX);
		zERR_ASSERT (vobFX->GetVisualClass()==zCParticleFX::GetStaticClassDef());
		zERR_ASSERT (vobFX->GetRefCtr() >= (vobFX->GetHomeWorld() ? 2 : 1)); // [Moos] Wenn der Vob keine HomeWorld hat, muss man nicht so strikt sein.
		if (vobFX) 
		{
			hostWorld->RemoveVob	(vobFX);
			vobFX->Release			();
		};
	};
	startedVobFX.EmptyList();

	//
	RemoveAllChildVobsFromNode();
};

void zCModel::DoAniEvents (zCModelAniActive *ani) 
{
    if (!homeVob || !homeVob->GetHomeWorld())
        return; // [Moos] hat keinen Sinn, weiterzumachen.

	zCModelAni *protoAni = ani->protoAni;
 
	if (protoAni->numAniEvents>0) { 
		int actFrame = (int)ani->actFrame; 
		do {
			if ((ani->actAniEvent>=protoAni->numAniEvents) || (ani->actAniEvent<0)) break;
			if (ani->advanceDir==0)	break;		// @@@
			zCModelAniEvent* actEvent = &(protoAni->aniEvents[ani->actAniEvent]);

			if (ani->advanceDir==+1) { if (actEvent->frameNr>actFrame) break; }
			else 					 { if (actEvent->frameNr<actFrame) break; }

			// Event in Liste aufnehmen
			occuredAniEvents.Insert (actEvent);

			// Event ausfuehren
			switch (actEvent->aniEventType) {
			case zMDL_EVENT_SOUND: 
				{
					zCSoundFX *sound = actEvent->soundList[0];
					if (sound) 
					{
						if (homeVob->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_PC)
						{
							// sc-sounds bleiben immer im speicher (und damit auch alle human sounds)
							sound->SetCanBeCachedOut(FALSE);
						}

	//					zERR_MESSAGE (5, 0, "D: MDL: eventSound: "+actEvent->string[0]);
						int slot = (actEvent->value2==0) ? zSND_SLOT_NONE : 1;
						zCSoundSystem::zTSound3DParams	params;
						params.SetDefaults	();
						params.radius			= actEvent->value1;
						zTSoundHandle sndHandle = zsound->PlaySound3D (sound, homeVob, slot, &params);
						if (sndHandle >=0)  this->m_listOfVoiceHandles.Insert(sndHandle); 
					};
				};
				break;
			case zMDL_EVENT_SOUND_GRND:
				{
					if (homeVob) 
					{ 
						zCPolygon *poly = homeVob->GetGroundPoly();
						if (poly) {
							zCSoundFX *sound = actEvent->soundList[int(poly->GetMaterial()->GetMatGroup())];
//							zERR_MESSAGE (5, 0, "D: MDL: eventSFXGrnd: "+actEvent->string[0]);
							if (sound) 
							{
								if (homeVob->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_PC)
								{
									// sc-schritt sounds bleiben immer im speicher (und damit auch alle human schritte)
									sound->SetCanBeCachedOut(FALSE);
								}

								if (sound->CacheIn()==zRES_CACHED_IN)
								{
									int slot = (actEvent->value2==0) ? zSND_SLOT_NONE : 1;
									zCSoundSystem::zTSound3DParams	params;
									params.SetDefaults	();
									params.radius		= actEvent->value1;
									zsound->PlaySound3D (sound, homeVob, slot, &params); 
								};
							};
/*							{
								// Staub pro Fusstritt
								zCModelNodeInst *mnode;
								zREAL perc = ani->GetProgressPercent();
								if ((perc>0.25F) && (perc<0.75F))	mnode = this->SearchNode (zMDL_NODE_NAME_R_FOOT);
								else								mnode = this->SearchNode (zMDL_NODE_NAME_L_FOOT);
								if (mnode) {
									zPOINT3 feetPos = mnode->GetBBox3DWorld().GetCenter();
									feetPos[VY]		= mnode->GetBBox3DWorld().mins[VY];
									zCParticleFX	*partFXBlood	= zNEW(zCParticleFX);
									zCVob			*vobFXBlood		= zNEW(zCVob);

									partFXBlood->emitter.ModelLandDust(); 
									partFXBlood->StartParticleEffect();
									partFXBlood->emitter.polyXDim *= 0.5F;
									partFXBlood->emitter.polyYDim *= 0.5F;

									vobFXBlood->SetVisual			(partFXBlood);
									vobFXBlood->SetCollDet			(FALSE);
									vobFXBlood->SetIgnoredByTraceRay(TRUE);
									vobFXBlood->SetPositionWorld	(feetPos);  

									homeVob->GetHomeWorld()->AddVob		(vobFXBlood);
								};
							};
*/
						};
					};
				};
				break; 
			case zMDL_EVENT_PFX: 
				if (homeVob) 
				{
					// nicht-loop-PFX	:	- kein handle
					//						-      handle	illegal ?
					// loop-PFX			:	-[kein handle]	ILLEGAL: niemand stoppt diesen PFX !!!
					//						-      handle
					zCParticleEmitter*	emitter = actEvent->pfxEmitterList[0];
					zREAL				handle	= actEvent->value1;
					if (emitter) {
						if (emitter->ppsIsLooping)  
						if (handle==0) {
							zERR_FAULT ("D: (zCModel::DoAniEvents): no handle specified for looping pfx, pfx: "+emitter->particleFXName);
							break;
						};
						zCVob			*pfxVob		= zNEW(zCVob);
						zCParticleFX	*pfx		= zNEW(zCParticleFX);
						pfxVob->SetDontWriteIntoArchive	(TRUE);				// Effekt Vob, nicht ins Archive schreiben!
						pfxVob->SetCollDet				(FALSE);
						pfxVob->SetPositionWorld		(zVEC3(0));
						#ifdef ZENGINE_DEBUG
							pfxVob->SetVobName			(emitter->GetParticleFXName());
						//zERR_MESSAGE (5, 0, "D: PFX_START: "+pfxVob->GetVobName());
						#endif
						// Effekt an ModelNode haengen ?
						// FIXME: hier bereits den Ptr auf die Node haben !
						zCModelNodeInst *mnode = SearchNode (actEvent->string[0]);
						if (mnode) {
							if (actEvent->value2!=0) {
								// attach to node
								zCTree<zCVob> *vobNode			= homeVob->GetHomeWorld()->AddVobAsChild (pfxVob, homeVob);
								AttachChildVobToNode			(vobNode->GetData(), mnode);		// AddRef()!
								pfxVob	->SetVisual				(pfx);
								pfx		->SetAndStartEmitter	(emitter);
							} else {
								// dont attach, just take start Pos/Rot from node
								pfxVob	->SetTrafoObjToWorld	(homeVob->trafoObjToWorld * GetTrafoNodeToModel(mnode));
	 							pfxVob	->SetVisual				(pfx);
								pfx		->SetAndStartEmitter	(emitter);
								homeVob	->GetHomeWorld()->AddVob(pfxVob);
							};
						} else {
							pfxVob	->SetPositionWorld		(homeVob->GetPositionWorld());  
							pfxVob	->SetVisual				(pfx);
							pfx		->SetAndStartEmitter	(emitter);
							homeVob	->GetHomeWorld()->AddVob(pfxVob);
						};
//						if (pfxVob->GetPositionWorld()[VY]<0) zerr.Message ("D: y<0: "+pfxVob->GetPositionWorld().GetString());
//						pfx		->CreateParticles();
						if (handle>0) {
							if (emitter->IsOneShotFX()) { 
								zERR_FAULT ("D: (zCModel::DoAniEvents): tried to give a handle to a oneShot PFX, pfx: "+emitter->particleFXName);
							} else {
								// nur eintragen, falls noch nicht vorhanden
								for (int i=0; i<startedVobFX.GetNum(); i++) {
									if (startedVobFX[i].vobFXHandle==handle) goto skipThis;
								};
								zTMdl_StartedVobFX	entry;
								entry.vob			= pfxVob;
								entry.vobFXHandle	= handle;
								startedVobFX.Insert (entry);
								entry.vob->AddRef	();			// muessen auch ein AddRef() bekommen, da z.B. beim DisposeWorld()/HostVobRemoved..() der Effekt Vob wor dem Model-Vob geloescht werden koennte..
skipThis:;
							};
						};
						// Die Objekte werden in diesem Kontext nicht mehr benoetigt
						zRELEASE (pfxVob);
						zRELEASE (pfx);
					};
				};
				break;
			case zMDL_EVENT_PFX_STOP: 
				{
					zREAL handle = actEvent->value1;
					for (int i=0; i<startedVobFX.GetNum(); i++) 
					{
						if (startedVobFX[i].vobFXHandle==handle) {
							zCVob *vobFX = startedVobFX[i].vob;
							assert (vobFX);
							assert (vobFX->GetVisualClass()==zCParticleFX::GetStaticClassDef());
							assert (vobFX->GetRefCtr()>=1);
							if (vobFX) 
							if (vobFX->GetVisualClass()==zCParticleFX::GetStaticClassDef())
							{
//zerr.Message ("D: PFX_STOP: "+vobFX->GetVobName());
								static_cast<zCParticleFX*>(vobFX->GetVisual())->StopEmitterOutput(); 
							};
							RemoveChildVobFromNode	(vobFX);			// attached Vobs entfernen
							vobFX->Release			();
							startedVobFX.RemoveIndex(i);
							break;
						};
					};
				};
				break;
			case zMDL_EVENT_SWAPMESH:
				{
//					zerr.Message ("D: MDL: eventSwapMesh: "+actEvent->string[0]+", "+actEvent->string[1]);
					zCModelNodeInst *node1 = SearchNode (actEvent->string[0]);
					zCModelNodeInst *node2 = SearchNode (actEvent->string[1]);
					if ((node1) && (node2)) {
						zSwap (node1->nodeVisual, node2->nodeVisual);
					};
				};
				break;
/*			case zMDL_EVENT_SETMESH:
				if (!ani->isFadingOut)
				{
//					zerr.Message ("D: MDL: *eventSetMesh: "+actEvent->string[0]);
					zCModelMeshLib *meshLib = ani->protoAni->meshLib;
					if (!meshLib) {
						// load on demand 
//						meshLib = zNEW( zCModelMeshLib();
//						zCModelMeshLib::LoadMDM (actEvent->string[0]+".MDM", 0, this, meshLib);
//						ani->protoAni->meshLib = meshLib;
						zCModelMeshLib::LoadMDM (actEvent->string[0]+".MDM", 0, this, &ani->protoAni->meshLib);
					};
					// fuer ani meshLib (OBSOLETE)
//					AddAniMeshLib (ani, meshLib);
//					actEvent->meshLib->ApplyToModel (this);  
				};
				break;
*/
			case zMDL_EVENT_MM_STARTANI:
				zCModelNodeInst *node;
				if (actEvent->string[1].IsEmpty())	node = SearchNode (zMDL_NODE_NAME_HEAD);
				else								node = SearchNode (actEvent->string[1]);
				if (node) 
				{
					zCMorphMesh *morphMesh	= zDYNAMIC_CAST<zCMorphMesh>(node->GetNodeVisual());
					if (morphMesh) 
						morphMesh->StartAni	(actEvent->string[0], actEvent->value1, actEvent->value2);
				};
				break;
			case zMDL_EVENT_CAM_TREMOR:
				// *eventCamTremor	(frameNr radiusCM	durationMSec	strengthXZPlane	strengthYHeight)
				if (this->homeVob)
				{
					zCCamera::activeCam->AddTremor (this->homeVob->GetPositionWorld(), 
													actEvent->value1,		// radiusSquare
													actEvent->value2,		// timeMSec
													zVEC3(actEvent->value3,	// amplitude
														  actEvent->value4,
														  actEvent->value3)
													);		
				};
				break;
			};
			
			ani->actAniEvent += ani->advanceDir;
		} while (1);
	};
};

/*
	// fuer ani meshLib (OBSOLETE)

void zCModel::AddAniMeshLib (zCModelAniActive *aniActive, zCModelMeshLib *meshLib) {
//	zerr.Message ("D: Add Meshlib: "+ani->GetAniName());
	zTAniMeshLibEntry entry;
	entry.ani		= aniActive;
	entry.meshLib	= meshLib;

	int aniLayer	= aniActive->GetLayer();
	zBOOL inserted	= FALSE;
	for (int i=0;i<aniMeshLibList.GetNum(); i++) 
	{
		if (aniLayer>aniMeshLibList[i].ani->GetLayer()) continue;
		if (aniLayer<aniMeshLibList[i].ani->GetLayer()) {
			aniMeshLibList.InsertAtPos (entry, i);
		} else {
			aniMeshLibList[i] = entry;
		};
		inserted = TRUE;
		break;
	};
	if (!inserted) {
		aniMeshLibList.InsertEnd (entry);
	};

	ApplyAniMeshLibList();
};

void zCModel::RemoveAniMeshLib (zCModelAniActive *activeAni) {
//	zerr.Message ("D: Remove Meshlib: "+ani->GetAniName());
	for (int i=0;i<aniMeshLibList.GetNumInList(); i++) {
		if (activeAni==aniMeshLibList[i].ani) {
			aniMeshLibList.RemoveIndex (i);
			break;
		};
	};
	ApplyAniMeshLibList();
};

void zCModel::ApplyAniMeshLibList() {
	modelMeshLib.ApplyToModel(this);
	for (int i=0;i<aniMeshLibList.GetNumInList(); i++) {
		aniMeshLibList[i].meshLib->ApplyToModel (this);
	};
};
*/

void zCCFASTCALL zCModel::AdvanceAni (zCModelAniActive* ani, zBOOL& overflowed) 
{
	// - clip actFrame
	// - if overflowed: set thisPos/lastPos
	// - if overflowed: StartAni (next), StopAni (this)

	zCModelAni *protoAni = ani->protoAni;

	// die potent. naechste Ani raussuchen
	zCModelAni *nextAni;
	if (ani->nextAniOverride!=0)	 nextAni = ani->nextAniOverride; 
	else							 nextAni = ani->nextAni;

	// Ani letzten Frame erreicht ?
	// FORWARD
	const float numFrames = (float)protoAni->numFrames;

	if ((ani->actFrame)>=numFrames) {
		overflowed = TRUE;
		// restlichen Ani-Events ausfuehren, diese duerfen ja nicht verschluckt werden !
		DoAniEvents (ani);
		if (nextAni) {
			if (nextAni==protoAni) {
				// State-Cycle-Ani = looping Ani
				if (ani->isFadingOut) {
					// Ani wird stillgehalten, falls sie sowieso beendet werden soll
					ani->actFrame	= numFrames-0.0001F;		// vorher: -1
					ani->advanceDir = 0;
				} else {
					// FIXME: sauberer ist hier ein delta in die neue Ani hinein.. und aniFlags ?!
					do {
						ani->actFrame -= numFrames;
					} while (ani->actFrame>=numFrames) ;
					// Ani-Events 
					ani->actAniEvent= 0;	// 0, weil advanceDir=+1
//					ani->actFrame	= 0;
				};
			} else {
				// aktuelle Ani faden auf dem letzten Frame
				// NextAni nur starten, falls die aktuelle Ani nicht bereits am ausfaden ist
				// Weil: Wenn Ani am ausfaden ist, bedeutet dies i.A., dass im selben Layer ein Folgeani bereits
				// gestartet wurde, so dass die nextAni der aktuellen Ani hier nur stoeren wuerde/koennte
				// Beispiel: T_Stand_2_Walk => S_Slide => S_WALK => S_STAND, hier wird der Slide rausgebombt !!
				ani->actFrame	= numFrames-0.0001F;
				ani->advanceDir	= 0;
				if (!ani->IsFadingOut())  
				{
					// FIXME: das hier evtl. alles in der 'StartAni()' selbst erledigen, und dort auch dann einen
					//        Frame 'prestep' in eine neue Folge-Ani
					const zBOOL noFade =	(ani    ->GetBlendOutSpeed()== zMDL_ANI_BLEND_OUT_ZERO) && 
											(nextAni->GetBlendInSpeed ()== zMDL_ANI_BLEND_IN_ZERO);
					if (noFade)	{
//						StopAni			(ani);
						StartAni		(nextAni, zMDL_STARTANI_FORCE);				// evtl "_FORCE_STEP_INTO" => frameNr uebertragen
					} else {
						FadeOutAni		(ani);										// noetig ??
						StartAni		(nextAni, zMDL_STARTANI_ISNEXTANI);
					};
				}
			};
		} else {
			if (numActiveAnis>1) {
				ani->actFrame	= numFrames-0.0001F;
				ani->advanceDir	= 0;
				FadeOutAni (ani);
			} else {
				// StopCurrentAni
				StopAni (ani);
			};
		};
	} else
	// REVERSE 
	if (ani->actFrame<0.0F) {
		overflowed = TRUE;
		// restlichen Ani-Events ausfuehren
		DoAniEvents (ani);
		if (nextAni) { 
			if (nextAni==protoAni) { 
				// State-Cycle-Ani 
				if (ani->isFadingOut) {
					// Ani wird stillgehalten, falls sie sowieso beendet werden soll
					ani->actFrame	= 0;
					ani->advanceDir = 0;
				} else {
					do {
						ani->actFrame += numFrames;
					} while (ani->actFrame<0); 
					// Ani-Events 
					ani->actAniEvent= protoAni->numAniEvents-1;		// advanceDir=-1
//					ani->actFrame	= numFrames-1; 
				};
			} else { 
				// aktuelle Ani faden auf dem letzten Frame
				ani->actFrame	= 0;
				ani->advanceDir	= 0;
				if (!ani->IsFadingOut()) {
					const zBOOL noFade =	(ani    ->GetBlendOutSpeed()== zMDL_ANI_BLEND_OUT_ZERO) && 
											(nextAni->GetBlendInSpeed ()== zMDL_ANI_BLEND_IN_ZERO);
					if (noFade)	{
//						StopAni			(ani);
						StartAni		(nextAni, zMDL_STARTANI_FORCE);				// evtl "_FORCE_STEP_INTO" => frameNr uebertragen
					} else {
						FadeOutAni		(ani);										// noetig ??
						StartAni		(nextAni, zMDL_STARTANI_ISNEXTANI);
					};
				};
			};
		} else {
			if (numActiveAnis>1) {
				ani->actFrame	= 0;
				ani->advanceDir	= 0;
				FadeOutAni (ani);
			} else {
				// StopCurrentAni
				StopAni (ani); 
			};
		};
	} else {
		overflowed = FALSE;
	};

	// Hier wird bei loopenden Anis bei Sprung lastFrame/Firstframe dafuer Sorge getragen, dass die Translation, die 
	// auf das Objekt/Vob uebertragen wird auch korrekt berechnet wird. Falls die Ani das Objekt fortbewegt ist die Trans 
	// im lastFrame der Ani nicht mit der Trans des folgenden firstFrames verrechenbar (bei nicht-fortbegwegenden schon..).
	// Fuer diesen Fall wird hier die relevante Translation umgerechnet.
	if (overflowed)
	if (numFrames>1)
	if ( ani->protoAni)
	if (!ani->protoAni->FlagStaticCycle())
	if ( ani->protoAni->rootNodeIndex!=-1) {
		const zVEC3 lastDelta	= ani->thisPos - ani->lastPos;
		ani->lastPos			= ani->protoAni->GetTrans (zFloat2Int(zFloor(ani->actFrame)), ani->protoAni->rootNodeIndex);
		ani->thisPos			= ani->lastPos - lastDelta;		// minus, da "thisPos" bereits als "lastPos" des naechsten Frames vorbereitet wird
	};
};

/*
int quant[3];

zREAL eulerMax=-9999;
zREAL eulerMin=+9999;

static void QuantizeQuat (zCQuat &quat) 
{
	if (1)
	{
		zVEC3 euler;
		quat.QuatToEuler	(euler);
		for (int i=0; i<3; i++) {
	//		if ((euler[i]<0) || (euler[i]>M_2PI))
	//			zerr.Message ("D: "+zSTRING(euler[i]));

			eulerMax	= zMax (eulerMax, euler[i]);
			eulerMin	= zMin (eulerMin, euler[i]);

			while (euler[i]<0)		euler[i] += M_2PI;
			while (euler[i]>M_2PI)	euler[i] -= M_2PI;
			zClamp (euler[i], float(0), float(M_2PI));

			const zREAL RANGE = zREAL(1<<16)-1.0F;
			euler[i]	/= M_2PI;	// 0..1
			quant[i]	= int(euler[i]*RANGE);
			euler[i]	= (float(quant[i]) / RANGE) * M_2PI;
		};
		quat.EulerToQuat	(euler);
	};
};

zREAL transMax=-999999;
zREAL transMin=+999999;

static void QuantizeTrans (zVEC3 &trans) 
{
	if (1)
	{
		for (int i=0; i<3; i++) 
		{
			transMax	= zMax (transMax, trans[i]);
			transMin	= zMin (transMin, trans[i]);
			const zREAL RANGE		= 800.0F;				// Troll: -150 .. +850
			const zREAL RANGE_BIT	= zREAL(1<<16)-1.0F;

			zClamp (trans[i], float(-RANGE), float(RANGE));

			trans[i]	= (trans[i] + RANGE) / (2.0F * RANGE);	// 0..1
			quant[i]	= int(zWORD(trans[i]*RANGE_BIT));
			trans[i]	= (float(quant[i]) / RANGE_BIT) * (2.0F *RANGE) -RANGE;
		};
	}
};
*/

void zCModel::AdvanceAnis () 
{ 
	// Bewegungsvariablen zuruecksetzen, damit im pausierten Modus keine ungueltige Bewegung auf Vobs uebertragen wird
	doVobRot	= FALSE;
	vobTrans	= 0;			// reseten, falls z.B. nur 1 Ani laeuft, diese aber KEINE animierte RootNode hat, darf kein vobTrans stehen bleiben..

	// Spezielle Behandlung, wenn die Engine pausiert
	if (ztimer.GetFrameTime()<=0) 
	{
		return;		
	};

	// AniEvents-Liste loeschen !!
	occuredAniEvents.EmptyList();

	// Handle holen und entweder entfernen oder Sound updaten (alle 2 frames reicht)
	if ( homeVob && homeVob->GetHomeWorld() && homeVob->GetHomeWorld()->GetMasterFrameCtr() % 2 ) 
	{
		for (int i=0; i<m_listOfVoiceHandles.GetNum(); i++)
		{
			zTSoundHandle sndHandle = m_listOfVoiceHandles.GetSafe(i);	

			if (!zsound->IsSoundActive(sndHandle)) 
			{
				m_listOfVoiceHandles.RemoveIndex(i);
				i--;
			}
			else 
			{
				zsound->UpdateSound3D(sndHandle);		
			}
		}
	}

	int		i;
	zBOOL	doLerpModel;
	zBOOL	flys;
	zBOOL	rootPosLocalSet	= FALSE;

	// wenn nur eine entfernte idle-Ani laeuft braucht diese nicht animiert werden..
	if ((modelDistanceToCam>1000) && (numActiveAnis==1) && 
		( aniChannels[0]->protoAni->FlagIdle()) && 
		(!aniChannels[0]->isFirstTime)) 
	{
		SetIsFlying (FALSE);
		goto leave;
	};

	doLerpModel = GetIsVisible() && ( ((modelDistanceToCam<2000) && GetLerp()) || (homeVob && homeVob->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_PC) );
	flys		= FALSE;

	i=0;
	while (i<numActiveAnis)
	{
		// FIXME/ACHTUNG:
		// a) Noch Handling Bedarf wenn eine Ani in einem Step mehrere Frames ueber das Ende einer Ani
		//    hinaus laeuft.
		// b) Bei looping Anis, die den Vob bewegen ist beim Ubergang der Bewegung=0 => sollte nicht so sein.

		// ***************
		// ** INITS     ** 
		// ***************

		zCModelAniActive*ani		= aniChannels[i];
		zCModelAni		*protoAni	= ani->protoAni;
//		int				actLayer	= protoAni->layer;
		zBOOL			modifiesVob	= protoAni->FlagModifiesVob();
		zBOOL			advanceForw = (ani->advanceDir==+1);
		
		ani->isFirstTime			= FALSE;
		flys						= flys || protoAni->FlagFlying();

		float			frameDelta;
		zREAL			actFrameF	= ani->actFrame; 
		int				actFrame	= int(ani->actFrame); 
//		zBOOL			aniOvfl		= FALSE; 

		// ist so gemeint: im letzten Vorgang wurde bei einem Overflow der frameCtr auf 0/maxframe gesetzt
		// also wird hier abgefragt, ob im _letzten_ durchgang ein overfl stattfand !
		//if (advanceForw) { if (actFrame<=0) aniOvfl = TRUE; }  
		//else			 { if (actFrame>=protoAni->numFrames-1) aniOvfl = TRUE; };

		// ****************
		// ** RAND-ANIS  ** 
		// ****************

		if (GetRandAnisEnabled())
		if (ani->aniAttachment)
		{
			zTAniAttachment *attach = ani->aniAttachment;
			if (attach)
			if (attach->randAniList.GetNumInList()>0) 
			{
				if (ani->randAniTimer<=0) {
					int randSlot	= int(zRand()) % int(attach->randAniProbSum);
					int sum			= 0;
					for (int q=0; q<attach->randAniList.GetNumInList(); q++) {
						sum += attach->randAniList[q].prob;
						if (randSlot<sum) {
							StartAni (attach->randAniList[q].randAniProtoID); 
							break;
						};
					};
					// Zeitpunkt des naechsten RandAni-Starts
					zREAL rand			= zRandF()*2 -1;
					rand				= rand * (attach->randAniFreq  * zREAL(0.5F));
					ani->randAniTimer	= (rand + attach->randAniFreq) * zREAL(1000);
				} else {
					ani->randAniTimer	-= ztimer.GetFrameTime() * GetTimeScale();
				};
			};
		};


		// ****************
		// ** ANI-EVENTS ** 
		// ****************

		// Ani-Events
		// FIXME: nicht ganz optimal ! Wenn eine Ani ueber das Ende hinauslaeuft wird DoAniEvents 2x ausgefuehrt !
		DoAniEvents (ani);


		// ****************
		// ** NEXT FRAME ** 
		// ****************

		// FIXME: koennte wohl eigentlich _nach_ dieser Loop kommen, allerdings wird fuer das SampleLerp das frameDelta 
		//        gebraucht

		// Next Frame
		// FIXME: ersten, konstanten Teil der Berechnung nur _einmal_ berechnen
		frameDelta		= (float(ani->advanceDir)*(zREAL(protoAni->fpsRate) / 1000.0F)) * ztimer.GetFrameTimeF() * GetTimeScale();
		ani->actFrame	+= frameDelta;
		// zCCamera::activeCam->targetDtpItem->Print (0,2500, zSTRING(delta)+",   " + zSTRING(ani->actFrame));

// was: advanceAni

		{
			// *********************
			// ** DO SAMPLE-LERP? **
			// *********************

			ani->transWeight = 0;

			zCQuat			strafo_Quat,	strafoNext_Quat;
			zVEC3			strafo_Trans,	strafoNext_Trans;
			zTMdl_AniSample	*strafoNext		= 0;
			zTMdl_AniSample	*strafo			= protoAni->aniSampleMatrix + (actFrame *protoAni->numNodes);
			zBOOL			doLerp			= doLerpModel && (frameDelta<zREAL(1)) && (protoAni->numFrames>1);
			zBOOL			noLerpPosSample = FALSE;
			int				nextFrame		= -1;
			float			lerpFrac;

			if (doLerp) {
				if (advanceForw) {
					lerpFrac  = (actFrameF - zFloor (actFrameF));
					nextFrame = actFrame+1;
					if (nextFrame>=protoAni->numFrames) {
						nextFrame		= 0;							// WICHTIG: nextFrame muss gueltig bleiben!!
						if (ani->nextAni!=protoAni) {
							doLerp = FALSE;
							goto noLerp;
						};
						noLerpPosSample = TRUE;
					};
				} else if (ani->advanceDir==-1) {
					lerpFrac  = 1 - (actFrameF - zFloor (actFrameF));
					nextFrame = actFrame-1;
					if (nextFrame<0) {
						nextFrame		= protoAni->numFrames-1;		// WICHTIG: nextFrame muss gueltig bleiben!!
						if (ani->nextAni!=protoAni) {
							doLerp = FALSE;
							goto noLerp;
						};
						noLerpPosSample = TRUE;
					};
				} else {
					doLerp = FALSE;
					goto noLerp;
				};  
				strafoNext	= protoAni->aniSampleMatrix + (nextFrame*protoAni->numNodes);
				assert ( (lerpFrac>=0) && (lerpFrac<=1));
noLerp:;
			};

#ifdef zDEBUG_MDL_SHOW_LERP
			if (doLerp) screen->Print (0,6000, "LERP");
#endif
			// ******************
			// ** COMBINE-ANIS ** 
			// ******************

			if (protoAni->GetAniType()==zMDL_ANI_TYPE_COMB) {
				zERR_BOUNDS			(nextFrame, -1, protoAni->numFrames-1);
				ani->DoCombineAni	(this, actFrame, nextFrame);
			};

			// ******************
			// ** UPDATE-NODES ** 
			// ******************

			// prepare ani data unpacking
			protoAni->PrepareAniDataAccess(); 

			for (int node=0; node<protoAni->numNodes; node++)
			{
				// Unpack Animation Data
				strafo->Unpack		(strafo_Quat, strafo_Trans);
				if (doLerp)
				strafoNext->Unpack	(strafoNext_Quat, strafoNext_Trans);

				zCModelNodeInst *tnode	= nodeList[protoAni->nodeIndexList[node]];

				if (tnode->numNodeAnis==1) 
				{
					// nur ein Ani
					// Rotation
					if (doLerp) {
						// => lerps der Samples
						strafo_Quat.Slerp			(lerpFrac, strafo_Quat, strafoNext_Quat);
						strafo_Quat.QuatToMatrix4	(tnode->trafo);
					} else {
						// => keine Quats, kein Blending; gleich die Trafo-Matrix setzen
						strafo_Quat.QuatToMatrix4  (tnode->trafo);
//						tnode->trafo.SetTranslation (strafo->trans);	// wird weiter unten gemacht..
					};

					// Trans/Rot setzen
					if ((modifiesVob) && (tnode->IsRootNode())) 
					{
//						tnode->trafo.SetTranslation (strafo->GetTranslation());		// richtig
						tnode->trafo.SetTranslation (zVEC3(0,0,0));					// FIXME: muss nur 1x gemacht werden !!!!!!!!!

						// Translation

						// Probs:
						// - looping Anis: wenn wieder auf Frame 0/max geschaltet wird, wird Distanz 'verschluckt'
						// - noPosLerp bei geringen FPS: auch hier die 100% korrekten Werte mittels Lerp berechnen
						// - 1 Frame Anis

						if (doLerp) 
						{
							if (noLerpPosSample) {
								// Problem: 2tes Sample fuers Lerpen gibt es nicht ...
								//          workaround: Model wird genau wie im letzten Frame weiterbewegt (als approx)
								zVEC3 lastDelta = (ani->thisPos - ani->lastPos);
								ani->lastPos	= ani->thisPos;
								ani->thisPos	= ani->lastPos + lastDelta;
//								zerr.Message (zSTRING(lastDelta.Length(),4)+", "+zSTRING((int)aniOvfl));
							} else {
								ani->lastPos	= ani->thisPos;
								ani->thisPos	= strafo_Trans + lerpFrac * (strafoNext_Trans-strafo_Trans);
							};
//							zerr.Message (t.GetString()+"; "+nextPosSample.GetString());
						} else {
							// FIXME: Um absolut ruckelfreie Anis auch bei geringen FPS-Rates zu haben, muss 
							//        die _genaue_ vobTrans unter Beruecksichtigung des lerpFracs berechnet werden !!!
							ani->lastPos	= ani->thisPos;
							ani->thisPos	= strafo_Trans; 
						};
						ani->transWeight= 1;
 						rootPosLocal	= ani->thisPos;
						rootPosLocalSet	= TRUE;

 						// ani->thisPos[VY]=0;
//						if (aniOvfl)	ani->lastPos = ani->thisPos;					// FIXME !!!!!!!!
						if (protoAni->FlagMovesVob()) vobTrans = (ani->thisPos - ani->lastPos);

						// Rotation ('R'-flag)
						if (protoAni->FlagRotatesVob()) {
							ani->lastRotQuat	= ani->thisRotQuat;
							ani->thisRotQuat	= strafo_Quat;					// FIXME: koennte mann aus dem Slerp-Quat nehmen..
							if (!ani->rotFirstTime) {
								vobRot				= ani->lastRotQuat.InverseUnit() * ani->thisRotQuat;
								ani->freezeRotQuat.QuatToMatrix4 (tnode->trafo);
								doVobRot			= TRUE; 
							} else {
//								zerr.Message ("D: firsttime..");
								ani->freezeRotQuat	= ani->thisRotQuat;
								ani->rotFirstTime	= FALSE;
//								logFile << endl << "Firsttime..." << endl;
							};
						}; 
					} else {
//						tnode->trafo.SetTranslation (tnode->translation);					// richtig, warum gehts nich ??
//						tnode->trafo.SetTranslation (strafo->GetTranslation());				// scheint noetig => EXERCISE.MAX
						tnode->trafo.SetTranslation (strafo_Trans);				// scheint noetig => EXERCISE.MAX
					};
				} else {
					// n Anis: Blending mittels Quat-Slerps
					// Rotation
					int nodeListIndex = tnode->GetNodeAniListIndex (ani); 
					if (nodeListIndex==-1) goto nodeFAILS;
					if (doLerp) {
						// => lerps der Samples
						tnode->nodeAniList[nodeListIndex].quat.Slerp (lerpFrac, strafo_Quat, strafoNext_Quat);
					} else {
						tnode->nodeAniList[nodeListIndex].quat = strafo_Quat;
					};
	
					// Trans/Rot setzen
					if ((modifiesVob) && (tnode->IsRootNode())) {
						// Move-Knoten
						const zPOINT3& t	= strafo_Trans; 
						tnode->trafo.SetTranslation (zVEC3(0,0,0));		// FIXME: muss nur 1x gemacht werden !!!!!!!!!

						// Translation
						if (doLerp) 
						{
							if (noLerpPosSample) {
								zVEC3 lastDelta = (ani->thisPos - ani->lastPos);
								ani->lastPos	= ani->thisPos;
								ani->thisPos	= ani->lastPos + lastDelta;
							} else {
								ani->lastPos	= ani->thisPos;
								ani->thisPos	= t + lerpFrac * (strafoNext_Trans-t);
							};
						} else {
							ani->lastPos	= ani->thisPos;
							ani->thisPos	= t; 
						};

						ani->transWeight	= tnode->nodeAniList[nodeListIndex].weight;

						// Problem: derzeit wird als rootPosLocal der Wert _irgendeiner_ Ani genommen
						// das macht leider bei z.B. Land=>Wasseruebergaengen Probleme!
//						if (!ani->IsFadingOut())
//						if (ani->thisPos[VY]<rootPosLocal[VY])
						rootPosLocal	= ani->thisPos;
						rootPosLocalSet	= TRUE;

						// ani->thisPos[VY]=0;
//						if (aniOvfl)	ani->lastPos = ani->thisPos;

						// Rotation ('R'-flag)
						if (protoAni->FlagRotatesVob()) {
							ani->lastRotQuat = ani->thisRotQuat;
							ani->thisRotQuat = tnode->nodeAniList[nodeListIndex].quat;
							if (!ani->rotFirstTime) {
								tnode->nodeAniList[nodeListIndex].quat = ani->freezeRotQuat; 
								doVobRot			= TRUE;
							} else {
								ani->freezeRotQuat	= ani->thisRotQuat;
								ani->rotFirstTime	= FALSE;
							};
						};
					} else {
//						tnode->trafo.SetTranslation (tnode->translation);					// richtig, warum gehts nich ??
						tnode->trafo.SetTranslation (strafo_Trans);				// scheint noetig => EXERCISE.MAX
					};
nodeFAILS:;
				};

				strafo++;
				strafoNext++;		// fuer Lerps
			};
		};

		// was: advance-ani II.
//skip:;
		i++;
	};

	SetIsFlying (flys);

	CalcTransBlending();		// benutzt: numActiveAnis(+Liste), ani->this/last/Pos/Rot

	// Folgendes MUSS NACH CalcTransBlending(), weil:
	// advanceAni koennte Anis entfernen, CalcTransBlending aber benoetigt noch, die alte Ani-Liste _vor_ dem Advance.
	// z.B.: 2 Anis, doVobRot=TRUE (soll in " gemacht werden), StopAni => 1 Ani, " wird geskippt => falchses vobRot
	// FIXME: koennte es sein, dass so Probs gibt, falls also advanceAni NACH dem ganzen thisPos/lastPos..Rot kommt ???

	CalcNodeListAniBlending();									// ACHTUNG: hier gelegentliches 'StopAni()' !! 

	i=0;
	while (i<numActiveAnis)
	{
		// *****************
		// ** ADVANCE-ANI ** 
		// *****************
		zCModelAniActive	*ani		= aniChannels[i];
		zBOOL				overflowed;
		AdvanceAni (ani, overflowed);  
  
		// FIXME: sollte eigentlich nicht noetig sein !! 
		zCModelAni		*protoAni	= ani->protoAni; 
		if (protoAni)
		{
			if ((int)ani->actFrame>=protoAni->numFrames) {
				ani->actFrame	= zREAL(protoAni->numFrames) - 0.0001F;  
				zERR_WARNING ("D: MDL: ..warn.. actFrame beyond, ani: "+ani->protoAni->GetAniName());
			} else if (ani->actFrame<0) { 
				ani->actFrame	= 0;
				zERR_WARNING ("D: MDL: ..warn.. actFrame <0, ani: "+ani->protoAni->GetAniName());
			};
		};

		// Falls der aktuelle Channel veraendert wurde (delete, override) => channel nicht weiterschalten
		if (ani==aniChannels[i]) i++;
//		if (!resetCtr) i++;
	};

	// BBox updaten
	CalcModelBBox3DWorld();

	// Sicherheitsnetz: falls das Model Bodenkontakt haben soll, aber die rootPosLocal nicht durch eine laufende Animation
	// gesetzt worden ist, so wird hier die rootPosLocal auf den Wert der neutralen Pose gesetzt.
/*	// FIXME: machte leider andererorts Probleme (z.B. bei der Benutzung von Mobsis.. Schweben auf Betten etc.)
	if ((!GetIsFlying ()) && (!rootPosLocalSet))
	{
//		this->rootPosLocal = this->GetModelProto()->GetRootNodeTrans();
		this->rootPosLocal = zVEC3(0,-this->bbox3D.mins[VY],0);
	};*/

	// BBox Aenderung an den Vob weiterleiten
	if (this->homeVob)
	{
		this->homeVob->UpdateVisualDependencies();
	};

leave:;
	//
	modelDistanceToCam = 999999;		// reset, wird in zCModel::Render() wieder gesetzt

	//
	if (modelScaleOn) {
		rootPosLocal= Alg_Prod (rootPosLocal, modelScale);
		vobTrans	= Alg_Prod (vobTrans	, modelScale);
	};

	//
	vobTrans	= Alg_Prod (vobTrans, aniTransScale);

	if ( newAniStarted )
	{
		relaxWeight		= 0.1f;
		newAniStarted	= FALSE;
	}

	if ( (!this->GetSmoothRootNode()) || (!zCModel::S_GetSmoothRootNode()) || (ztimer.GetFrameTimeF() == 0) ) 
	{
		vobTransRing  = vobTrans;
	}
	else 
	{
		// HACK: neu 1.16c: Relax RootNode (vermeidet Ruckeln der Ani bei bestimmten FPS Raten)
		const zREAL averageFrameTime = .025F; // 40 FPS	Avg. Ringbuffer Emulation
		const zREAL RELAX_MAX		 = 2.5f;  // Relax
		const zREAL RELAX_MAX_TIME	 = 1.0f/0.8f;  // wie lange bis zum maximalen Relaxen
		zREAL frameTime = (ztimer.GetFrameTimeF()* GetTimeScale())/1000;
		zREAL dist2 = (vobTrans - vobTransRing).Length2() / 100000;
		relaxWeight+= frameTime*RELAX_MAX_TIME;
		if (relaxWeight>RELAX_MAX) relaxWeight = RELAX_MAX;

		zREAL frac = frameTime / (relaxWeight * averageFrameTime);
		frac      *= (1 + 4 * dist2) / (1 + dist2);

		vobTransRing += vobTrans * frac;
		vobTransRing /= (1 + frac);
	}

	vobTrans = vobTransRing;

	// Velocity
	if (vobTrans.Length2()>(10*10)) {
		modelVelocity = vobTrans;
	};
	actVelRingPos++;
	if (actVelRingPos>=zMDL_VELRING_SIZE) actVelRingPos=0;
	zREAL denom		= (ztimer.GetFrameTimeF() * GetTimeScale());
	if (denom<=0)	modelVelRing[actVelRingPos] = 0;
	else			modelVelRing[actVelRingPos] = vobTrans * 1000 * (1 / denom);		// v = s/t, [v] = cm/ms
};

void zCModel::SetModelScale (const zVEC3& scale) 
{
	modelScale		= scale;
	modelScaleOn	= !((modelScale[VX]==1) && (modelScale[VY]==1) && (modelScale[VZ]==1));
	if (modelProtoList.GetNumInList()>0) {
		// assert: box ist in XZ um 0 zentriert, und steht in Y auf der XZ Plane
		bbox3DLocalFixed			= modelProtoList[0]->bbox3D;
		bbox3DCollDet				= modelProtoList[0]->GetBBox3DCollDet();
		if (modelScaleOn) {
			bbox3DLocalFixed.mins	= Alg_Prod (bbox3DLocalFixed.mins, scale);
			bbox3DLocalFixed.maxs	= Alg_Prod (bbox3DLocalFixed.maxs, scale);
			bbox3DCollDet.mins		= Alg_Prod (bbox3DCollDet.mins, scale);
			bbox3DCollDet.maxs		= Alg_Prod (bbox3DCollDet.maxs, scale);
		};
	};
	// generelle local Model-BBox anpassen
	CalcModelBBox3DWorld();
};

zBOOL zCModel::IsStateActive (const zCModelAni *modelAni) const 
{
	// gdw. dieser state der einzige aktive state ist & keine transition aktiv ist (alles im selben Layer)
	if (!modelAni) return FALSE;
	// if (!modelAni->isRunning)       return FALSE;

	const int actLayer = modelAni->GetLayer();
	for (int i=0; i<numActiveAnis; i++) 
	{
		if (aniChannels[i]->GetLayer()==actLayer)
		{
			if (aniChannels[i]->protoAni==modelAni)
				return TRUE;
			if ((aniChannels[i]->IsStateAni()) || (aniChannels[i]->IsTransAni())) 
				return FALSE;
		};
	};
	return FALSE;
};

zTBBox3D zCModel::GetBBox3D () 
{
	return bbox3D;
};

zSTRING zCModel::GetVisualName () 
{
	if ((modelProtoList.GetNum()<=0) || (!modelProtoList[0]))	return zSTR_EMPTY;
	return (modelProtoList[0]->GetModelProtoFileName());
}; 

zCModelNodeInst* zCModel::SearchNode (const zSTRING& nodeName) 
{
	// FIXME: evtl. BinSearch
	for (int i=0; i<nodeList.GetNum(); i++) {
		if (nodeList[i]->protoNode->nodeName==nodeName) return nodeList[i];
	};
	return 0;
};


//////////////////////////////////////////////
// Mesh/Texture Kombinierbarkeit 
//////////////////////////////////////////////

zBOOL zCModel::SetNodeMeshTexture (const zSTRING& nodeName,
								   const int	  channel, 
								   const int	  varNr, 
								         zSTRING* texNamePart)
{
	// falls texNamePart!="" => nur Texturen werden beruecksichtigt, in deren Namen
	// 'texNamePart' enthalten ist ! (z.B. "hair" oder "face" waere denkbar)

	zCModelNodeInst *mnode = SearchNode(nodeName);
	if (mnode) 
	if (!mnode->protoNode->IsSlot())	// niemals Slots veraendern !
	{
		mnode->texAniState.SetChannelVariation (channel, varNr, texNamePart);
		return TRUE;
	};
	return FALSE;
};

static void StringUpperNoExt (const zSTRING& in, zSTRING& out)
{
	zPATH	path(in);
	out		= path.GetFilename();
	out.Upper();
};

zBOOL zCModel::SetMeshLibTexture (const zSTRING& meshLibName, 
								  const int		 channel, 
								  const int		 varNr,
								        zSTRING* texNamePart)
{   
	zSTRING name;
	StringUpperNoExt (meshLibName, name);
	zCModelMeshLib *meshLib = (zCModelMeshLib*)zCModelMeshLib::GetStaticClassDef()->SearchObject (name);
	if (!meshLib)	return FALSE;

	for (int i=0; i<meshLibList.GetNum(); i++) 
	{
		if (meshLibList[i]->meshLib==meshLib)	
		{
			meshLibList[i]->texAniState.SetChannelVariation (channel, varNr, texNamePart);
			return TRUE;
		};
	};
	return FALSE;
};

void zCModel::RemoveMeshLibAll () 
{
	for (int i=meshLibList.GetNum()-1; i>=0; i--) 
		RemoveMeshLib (meshLibList[i]->meshLib->GetObjectName());
};

zBOOL zCModel::RemoveMeshLib (const zSTRING& meshLibName) 
{
	zSTRING name;
	StringUpperNoExt (meshLibName, name);
	zCModelMeshLib *meshLib = (zCModelMeshLib*)zCModelMeshLib::GetStaticClassDef()->SearchObject (name);
	if (!meshLib)	return FALSE;

	for (int i=0; i<meshLibList.GetNum(); i++) 
	{ 
		if (meshLibList[i]->meshLib==meshLib)	
		{
			delete meshLibList[i];
			meshLibList.RemoveOrderIndex(i);
			meshLib->RemoveFromModel	(this);
			meshLib->Release			();
			return TRUE;
		};
	};
	return FALSE;
};	

zBOOL zCModel::ApplyMeshLib (const zSTRING& meshLibName)
{
	// s = "HUM_BODY_NAKED"
	if (meshLibName.Length()<=0) return FALSE;

	//
	zSTRING ascName;
	StringUpperNoExt (meshLibName, ascName);
 
	// MDM laden
	zCModelMeshLib *meshLib=0;
	zBOOL res = zCModelMeshLib::LoadMDM (ascName+".mdm", 0, this, &meshLib);
	if (!res) {
		// neu konvertieren
		zCModelAni *aniPtr		= 0;
		zSTRING		aniName;
		int			firstFrame, lastFrame;
		firstFrame = lastFrame	= 0;

		zERR_MESSAGE (5, 0, "D: MDL: Converting Mesh-ASC into .MDM: \""+ascName+"\"");
/*
		// "A"
		// legt neues modelProto an, kopiert nodeTree => klappt leider nicht, da der softSkin Reader die Trafos der Nodes in
		// gewissen Zustaenden erwartet....
		zCModelPrototype *modelProto	= zNEW(zCModelPrototype); 
		modelProto->SetModelProtoName	(ascName);
		modelProto->CopyNodeTreeFrom	(GetModelProto());		// der neue ModelProto muss denselben NodeTree haben, wie das baseModelProto
		modelProto->Load3DSMAXAsc		(aniPtr, ascName+".asc", aniName, firstFrame, lastFrame, FALSE, TRUE, FALSE);	// ani, mesh, tree
		meshLib = zNEW(zCModelMeshLib);
		meshLib->SetObjectName			(ascName);
		meshLib->BuildFromModel			(modelProto);
		meshLib->SaveMDM				(this->GetModelProto());
		modelProto->Release				();
		delete aniPtr;
*/

		// "B"
		// Das baseModelProto wird fuer das Laden der neuen MeshLib benutzt... FIXME: bleiben unerwuemschte Reste im modelProto zurueck ??
		zCModelPrototype *modelProto	= GetModelProto(); 
		modelProto->ReleaseMeshes		();						// modelproto von Meshes saeubern..
		modelProto->Load3DSMAXAsc		(aniPtr, ascName+".asc", aniName, firstFrame, lastFrame, zMDL_MAX_IMPORT_MESH);	// ani, mesh, tree
		meshLib							= zNEW(zCModelMeshLib);
		meshLib->BuildFromModel			(modelProto);
		meshLib->SetObjectName			(ascName);
		meshLib->SaveMDM				(modelProto);
		zRELEASE (aniPtr);
		meshLib->Release				();
		
		// .mdm hier neu laden, da sich die internen Referenzen der obigen meshLib auf ein modelProto beziehen, es aber
		// unten auf ein Model angewandt werden soll.
		zCModelMeshLib::LoadMDM (ascName+".mdm", 0, this, &meshLib);
	};

	//
	meshLib->ApplyToModel		(this);

	//
	zTMeshLibEntry *meshLibEntry= zNEW(zTMeshLibEntry);
	meshLibEntry->meshLib		= meshLib;
	meshLibEntry->texAniState.BuildTexListFromMeshLib (meshLib);
	meshLibList.InsertEnd		(meshLibEntry);

	// fuer ani meshLib (OBSOLETE)
	// Problem hier bei HeadMorphMesh: das ReleaseData() in der Methode loescht faelschlicherweise das MorphMesh..
//	modelMeshLib.BuildFromModel	(this);
	return TRUE;
};

void zCModel::UpdateMeshLibTexAniState () 
{
	for (int i=0; i<meshLibList.GetNum(); i++) 
		meshLibList[i]->texAniState.UpdateTexList();
};

// ==================================================================================================================

//
// Ani-Blending
//


void zCModelNodeInst::AddNodeAni (zCModelAniActive *modelAni) 
{
	if (numNodeAnis==zMDL_MAX_ANIS_PARALLEL) return;
	nodeAniList[numNodeAnis].modelAni = modelAni;
	// neue Ani ist neue Master-Ani, wenn:
	// - einzige Ani
	// - sonst keine Master-Ani vorhanden ist
	// - sie eine hoehere Layer-Nr hat, als die akt. master-ani
	if (numNodeAnis==0) {
		// erste/einzige Ani, gleich auf 100% setzen, blendIn sparen
		nodeAniList[0].weight		= 1;
		nodeAniList[0].weightSpeed	= 0;
		nodeAniList[0].blendState	= zMDL_BLEND_STATE_CONST;
		masterAni = 0;
	} else
	if ((masterAni==-1) || ((modelAni->protoAni->layer) >= (nodeAniList[masterAni].modelAni->protoAni->layer))) { 
		// neue Master-Ani, alte Master-Ani wird abgeloest
		if (masterAni!=-1) {
			if (nodeAniList[masterAni  ].blendState!=zMDL_BLEND_STATE_FADEOUT) {
				// neue Master-Ani im selben Layer wie die alte ? => die alte ausblenden
				// FIXME: sinnvoll ?
//				if (nodeAniList[masterAni].modelAni->protoAni->layer==modelAni->protoAni->layer) {
				if (nodeAniList[masterAni].modelAni->protoAni->layer>=modelAni->protoAni->layer) {
					nodeAniList[masterAni].weightSpeed= nodeAniList[masterAni].modelAni->GetBlendOutSpeed();
					nodeAniList[masterAni].blendState = zMDL_BLEND_STATE_FADEOUT;
				} else {
					// FIXME: richtig ?? sollte es nicht auf 'CONST' stehen ??
					nodeAniList[masterAni].weightSpeed= 0;
				};
			} else
				zERR_WARNING("D: masterAni beim Faden !");
		};
		nodeAniList[numNodeAnis].weight		= 0.0F;
		nodeAniList[numNodeAnis].weightSpeed= modelAni->GetBlendInSpeed();
		nodeAniList[numNodeAnis].blendState	= zMDL_BLEND_STATE_FADEIN;
		masterAni = numNodeAnis;
	} else {
		// eine neue Ani unter anderen
		nodeAniList[numNodeAnis].weight		= 0.0F;
		nodeAniList[numNodeAnis].weightSpeed= 0.0F;
		nodeAniList[numNodeAnis].blendState	= zMDL_BLEND_STATE_FADEIN;
	};
	numNodeAnis++;
};

void zCModelNodeInst::RemoveAllNodeAnis	() {
	numNodeAnis=0;
};

void zCModelNodeInst::RemoveNodeAni (zCModelAniActive *modelAni) {
	for (int i=0; i<numNodeAnis; i++) {
		if (nodeAniList[i].modelAni==modelAni) {
			// ani aus Liste loeschen
			for (int j=i; j<numNodeAnis-1; j++)
				nodeAniList[j] = nodeAniList[j+1];
			numNodeAnis--;
			// Master Ani entfernt ? => neue Master Ani ermitteln
			if (i==masterAni)	FindMasterAni (); else
			if (masterAni>i)	masterAni--		;		// wurde ja verschoben..
			break;
		};
	};
};

void zCModelNodeInst::FindMasterAni () {
	// Master Ani ermitteln, Kriterien:
	// - hoeherer/gleicher Layer
	// - weightSpeed>=0, d.h. keine Ani im FadeOut
	int actLayer,bestLayer;
	bestLayer = -1;
	masterAni = -1;
	// Suche Ani mit der hoechsten Layer-Nr
	for (int j=0; j<numNodeAnis; j++) {
		actLayer = nodeAniList[j].modelAni->protoAni->layer;
		if ((actLayer >= bestLayer) && (nodeAniList[j].blendState!=zMDL_BLEND_STATE_FADEOUT)) {
			masterAni = j;
			bestLayer = actLayer;
		};
	};
	if (masterAni!=-1) {
		nodeAniList[masterAni].weightSpeed = nodeAniList[masterAni].modelAni->GetBlendInSpeed();
	};
};

void zCModelNodeInst::FadeOutNodeAni (zCModelAniActive *activeAni) {
	for (int i=0; i<numNodeAnis; i++) {
		if (nodeAniList[i].modelAni==activeAni) {
			nodeAniList[i].weightSpeed	= activeAni->GetBlendOutSpeed();
			nodeAniList[i].blendState	= zMDL_BLEND_STATE_FADEOUT;
			// eine fallende Ani darf keine Master-Ani sein => neue raussuchen
			if (i==masterAni) FindMasterAni();
			return; 
		};
	};
};

void zCModel::FadeOutAni (zTModelAniID aniID)
{
	FadeOutAni (GetActiveAni ( GetAniFromAniID(aniID) ) );
};

void zCModel::FadeOutAni (zCModelAni *protoAni)
{
	FadeOutAni (GetActiveAni ( protoAni ) );
};

void zCModel::FadeOutAni (zCModelAniActive *activeAni) 
{
	if (!activeAni) return;
	if (activeAni->isFadingOut || (activeAni->IsUnused())) return;

	zCModelAni *protoAni = activeAni->protoAni;
	for (int i=0; i<activeAni->protoAni->numNodes; i++) {
//		modelAni->nodeList[i]->FadeOutNodeAni (modelAni);
		nodeList[protoAni->nodeIndexList[i]]->FadeOutNodeAni (activeAni);
	};
	activeAni->isFadingOut = TRUE;

	// abhaengige Anis werden 'sanft' gestoppt: FadeOut
	if (activeAni->aniAttachment) {
		for (i=0; i<activeAni->aniAttachment->randAniList.GetNum(); i++) {
			FadeOutAni (activeAni->aniAttachment->randAniList[i].randAniProtoID);
		};
	};
};

void zCModel::FadeOutAnisLayerRange (const int layerLow, const int layerHi) {
	for (int i=0; i<numActiveAnis; i++) {
		zCModelAniActive* ani = aniChannels[i];
		if ((ani->GetLayer()>=layerLow) && (ani->GetLayer()<=layerHi)) {
			FadeOutAni (ani);
			if (ani!=aniChannels[i]) i--;		// removed ?
		};
	};
};

void zCModel::StopAnisLayerRange (const int layerLow, const int layerHi) {
	for (int i=0; i<numActiveAnis; i++) {
		zCModelAniActive* ani = aniChannels[i];
		if ((ani->GetLayer()>=layerLow) && (ani->GetLayer()<=layerHi)) {
			StopAni (ani);
			if (ani!=aniChannels[i]) i--;		// removed ?
		};
	};
};

zREAL zCModel::GetProgressPercent (const zSTRING& aniName) const
{
	return GetActiveAni(GetAniFromAniName (aniName))->GetProgressPercent();
};

zREAL zCModel::GetProgressPercent (zTModelAniID	aniID) const
{
	return GetActiveAni(aniID)->GetProgressPercent();
};

void zCModel::SetCombineAniXY (zTModelAniID aniID, zREAL xc, zREAL yc) const
{
	zCModelAniActive *activeAni = GetActiveAni (aniID);
	if (activeAni)	activeAni->SetCombineAniXY (xc,yc);
};

zBOOL zCModel::GetCombineAniXY (zTModelAniID aniID, zREAL& xc, zREAL& yc) const
{
	zCModelAniActive *activeAni = GetActiveAni (aniID);
	if (activeAni)	{
		activeAni->GetCombineAniXY (xc,yc);
		return TRUE;
	} else {
		xc = yc = 0;
		return FALSE;
	};
};

void zCModelNodeInst::CalcWeights (zCModel *model) { 
	// Berechnet die Gewichte aller beteiligten Anis auf dieser Node. Dabei gibt es
	// eine diktierende Master-Ani
	if (numNodeAnis==0) return;
//	if (numNodeAnis==1) {
//		nodeAniList[0].weight		= 1.0F;
//		nodeAniList[0].weightSpeed	= 0.0F;
//		return;
//	};

	const zREAL localFrameTime = ztimer.GetFrameTimeF() * model->GetTimeScale();

	for (int i=0; i<numNodeAnis; i++) {
		zTNodeAni& actAni = nodeAniList[i];
		if (actAni.weightSpeed!=0) {
			zVALUE deltaThis, deltaOthers;
			// advance
			deltaThis		= (actAni.weightSpeed / 1000.0F) * localFrameTime;

			AddToNodeAniWeight (i, deltaThis);

			// betroffene abhaengige Anis zaehlen
			// = alle - this - zeroes - master
			int numOverZero = 0;
			int relevantNode [zMDL_MAX_ANIS_PARALLEL];
			for (int j=0; j<numNodeAnis; j++) {
				if ((i!=j) && (nodeAniList[j].weight>0) && (j!=masterAni)
					&& (nodeAniList[j].blendState!=zMDL_BLEND_STATE_FADEOUT)
					) {
					relevantNode[numOverZero] = j;
					numOverZero++;
				};
			}; 
			if (numOverZero>0) {
				deltaOthers = -(deltaThis / numOverZero);
				for (j=0; j<numOverZero; j++) {
					zTNodeAni& ani = nodeAniList [relevantNode[j]];
					AddToNodeAniWeight (relevantNode[j], deltaOthers); 
					// ani beim Fade-Out und weight==0 erreicht ? => Ani Beenden
					if ((ani.blendState==zMDL_BLEND_STATE_FADEOUT) && (ani.weight==0)) {
						// ani aus allen Nodes loeschen
						model->StopAni (ani.modelAni);
						if (relevantNode[j]<i) i--;
						j--;
					};
				};
			};
			// ani beim Fade-Out und weight==0 erreicht ? => Ani beenden
			if ((actAni.blendState==zMDL_BLEND_STATE_FADEOUT) && (actAni.weight==0)) {
				// ani aus allen Nodes loeschen
				model->StopAni (actAni.modelAni);
				i--;
			};
		};
	}; 
};

void zCModelNodeInst::AddToNodeAniWeight (const int i, const zVALUE delta) {
	nodeAniList[i].weight += delta;
	// clamp/stop curve
	if (nodeAniList[i].weight>1.0) {
		nodeAniList[i].weight		= 1.0;
		nodeAniList[i].weightSpeed	= 0;
		nodeAniList[i].blendState	= zMDL_BLEND_STATE_CONST;
//		zerr.Message ("one");
	} else
	if (nodeAniList[i].weight<0) {
		nodeAniList[i].weight		= 0;
		nodeAniList[i].weightSpeed	= 0;
	};
};

void zCModelNodeInst::CalcBlending (zCModel *model) {
	// Berechnet aus den Gewichten und den Rotationen/Transl. der einzelnen Anis die
	// finale Trafo-Matrix, mit der dann die Verts transformiert werden.
	// °

	struct zTAniTrafo {
		zCQuat			quat;
		zVALUE			weight;
	};

	if (numNodeAnis==0) return;

	CalcWeights(model);

	// schneller Special-Case: nur eine Ani aktiv
	if (numNodeAnis<=1) {
		// was wenn weight<1 ?
		return;
	};

	// >=2 Anis aktiv
	zTAniTrafo trafoList[zMDL_MAX_ANIS_PARALLEL];			// => max 16 Anis koennen paralell laufen & geblendet werden
	int numTrafos= numNodeAnis;
	int i; 

	// a) erstmal die Quats aller beteiligten Anis rauskramen
	for (i=0; i<numTrafos; i++) {
		trafoList[i].weight		= nodeAniList[i].weight;
		trafoList[i].quat		= nodeAniList[i].quat;
	};

	// b) 'Slerp' zwischen n Quats
	//    Das Ergebnis ist ein finaler Quat (mit weight==1)
	assert (numTrafos>1);
	// Anzahl ungerade => durch eine vorweg-Verknuepfung gerade machen
	// FIXME: vollenden ...
	// Anzahl ab hier gerade
	do {
		int num = numTrafos-1;
		int fill= 0;
		for (i=0; i<num; i+=2) {
			zVALUE t;
			zVALUE w1 = trafoList[i  ].weight;
			zVALUE w2 = trafoList[i+1].weight;
			zVALUE sum= w1+w2;
			if (sum!=0) t = w2 / sum;
			else		t = 0.5F;
			// Sinus ease-in/out
			#ifdef zMDL_BLEND_EASE
				t = float((zSin(t*float(M_PI) - float(M_PI)/2)+1)/2);
			#endif
			assert ((t>=0) && (t<=1));
			trafoList[fill].quat.Slerp (t, trafoList[i].quat, trafoList[i+1].quat);
			trafoList[fill].weight	= sum;
			--numTrafos;
			++fill;
		};
		// falls ungerade muss der uebrige Eintrag nachtraeglich verrutscht werden
		if (((num+1)&1)==1) {
			trafoList[fill] = trafoList[num];
		};

		// Anzahl halbiert sich
//		numTrafos = numTrafos >> 1;
	} while (numTrafos>1);

	// c) Ergebnis-Quat => Trafo
	trafoList[0].quat.QuatToMatrix4 (trafo);
};

void zCModel::CalcNodeListAniBlending () {
	for (int i=0; i<nodeList.GetNumInList(); i++) {
		nodeList[i]->CalcBlending (this);
	};
};

int zCModelNodeInst::GetNodeAniListIndex (const zCModelAniActive *activeAni) const {
	for (int i=0; i<numNodeAnis; i++)
		if (nodeAniList[i].modelAni==activeAni) return i;
	return -1;
};

void zCModel::CalcTransBlending () {

	struct zTAniTrafo {
		zVEC3			trans;
		zCQuat			rot;
		zVALUE			weight;
	};

	if (numActiveAnis<=1) return;

	// >=2 Anis aktiv
	zTAniTrafo trafoList[zMDL_MAX_ANIS_PARALLEL];			// => max x Anis koennen paralell laufen & geblendet werden
	int numTrafos=0;
	int i; 
 
	// a) erstmal die Trans aller relevanten Anis rauskramen
	for (i=0; i<numActiveAnis; i++) 
	{
		if (aniChannels[i]->transWeight<=0) continue;			// FIXME: ?????????????, scheint aber so ok..
//		if (aniChannels[i]->transWeight<0) continue;
		trafoList[numTrafos].weight = aniChannels[i]->transWeight;
		if (aniChannels[i]->protoAni->FlagMovesVob())	trafoList[numTrafos].trans = aniChannels[i]->thisPos - aniChannels[i]->lastPos;
		else											trafoList[numTrafos].trans = zVEC3 (0,0,0);
		if (doVobRot) {
		if (aniChannels[i]->protoAni->FlagRotatesVob())	trafoList[numTrafos].rot   = aniChannels[i]->lastRotQuat.Inverse() * aniChannels[i]->thisRotQuat;
		else											trafoList[numTrafos].rot.Identity();
		};
		numTrafos++;
	};

	if (numTrafos==0) return;
	if (numTrafos==1) {
		vobRot	 = trafoList[0].rot;
		vobTrans = trafoList[0].trans;
//	zerr.Message ("..vobRot_blend_1_.. "+zSTRING(vobRot.Length(),4));
//	vobRot.Identity();
		return;
	};

	// b) 'lerp' zwischen n Trans-Vektoren
	//    Das Ergebnis ist ein finaler Trans (mit weight==1)

	// Anzahl ungerade => durch eine vorweg-Verknuepfung gerade machen
	// FIXME: vollenden ...
	// Anzahl ab hier gerade
	do {
		int num = numTrafos-1;
		int fill= 0;
		for (i=0; i<num; i+=2) {
			zVALUE t;
			zVALUE w1 = trafoList[i  ].weight;
			zVALUE w2 = trafoList[i+1].weight;
			zVALUE sum= w1+w2;
			t = w2 / sum;
			// Sinus ease-in/out
			#ifdef zMDL_BLEND_EASE
				t = float((zSin(t*float(M_PI) - float(M_PI)/2)+1)/2);
			#endif
			assert ((t>=0) && (t<=1));
			trafoList[fill].weight	= sum;
			// Translation
			zVEC3 trans;
			const zVEC3& trans1 = trafoList[i  ].trans;
			const zVEC3& trans2 = trafoList[i+1].trans;
			if (trans1==zVEC3(0,0,0)) trans = trans2; else
			if (trans2==zVEC3(0,0,0)) trans = trans1; else
//									  trans = t*trans1 + (1-t)*trans2;
//									  trans = t*(trans2-trans1);
									  trans = trans1 + t*(trans2-trans1);
			trafoList[fill].trans = trans;
			// Rotation
			if (doVobRot) {
				// FIXME: es kommt selten vor, dass wirklich 2 R-Flag Anis gleichzeitig laufen, evtl. fast-special-case ?
				const zCQuat& q1 = trafoList[i  ].rot;
				const zCQuat& q2 = trafoList[i+1].rot;
				if (q1.IsIdentity())	trafoList[fill].rot = q2; else
				if (q2.IsIdentity())	trafoList[fill].rot = q1; else
										trafoList[fill].rot.Slerp (t, q1, q2);
//				trafoList[fill].rot.Slerp (t, trafoList[i].rot, trafoList[i+1].rot);
			};

			--numTrafos;
			++fill;
		};
		// falls ungerade muss der uebrige Eintrag nachtraeglich verrutscht werden
		if (((num+1)&1)==1) { 
			trafoList[fill] = trafoList[num];
		};

		// Anzahl halbiert sich
//		numTrafos = numTrafos >> 1;
	} while (numTrafos>1);

	// c) Ergebnis-Trans => Trafo
	vobTrans = trafoList[0].trans;
	if (doVobRot) 
	{
		vobRot	 = trafoList[0].rot; 
//	zerr.Message ("..vobRot_blend_n_.. "+zSTRING(vobRot.Length(),4)+", doVobRot: "+zSTRING((int)doVobRot));
//	vobRot.Identity();
	};
};

void zCModelAniActive::DoCombineAni (zCModel *hostModel, int frame, int nextFrame) {
	// Berechnet aus allen combAnis eine finale Ani
	// Was noch fehlt:
	// x Translation (wird noch stumpf/statisch aus der ersten Ani genommen)
	// x c_ Anis muessten auch animiert werden (was wenn ungleiche Laenge..?)
	// x Aufrufe der 'CombineAni' intern in 'AdvanceAnis' ?
	// - internes speichern & interpolieren der xc,yc ?
	// - hier werden 1/2 Ani-Frames gelerpt, einer davon wird im naechsten Game-Frame redundant nochmals bearbeitet !!!

	//     frame:	 0..numFrames-1
	// nextFrame:	-1..numFrames-1

	int numCombAnis = protoAni->combAniList.GetNumInList();
	assert (numCombAnis>=2);
	zREAL xc = combAniX;
	zREAL yc = combAniY;

	int			n0,n1,n2,n3;
	zCModelAni	*ani0, *ani1, *ani2, *ani3;

	if (numCombAnis==2) {
		n0 = 0; n1 = 1;
	} else
	if (numCombAnis==3) {
		if (yc<0.5)		{ n0=0; n1=1;				}
		else			{ n0=1; n1=2; yc -= 0.5F;	};
		yc *=2;
	} else
	if (numCombAnis==4) {
		n0 = 0; n1 = 1; n2 = 2; n3 = 3;
	} else
	if (numCombAnis==9) {
		// 0---1---2
		// |   |   |
		// 3---4---5
		// |   |   |
		// 6---7---8
		// Quadrant ermitteln
		if ((xc< 0.5) && (yc< 0.5)) { n0 = 0; n1 = 1; n2 = 3; n3 = 4;				} else
		if ((xc>=0.5) && (yc< 0.5)) { n0 = 1; n1 = 2; n2 = 4; n3 = 5; xc -= 0.5F;	} else
		if ((xc< 0.5) && (yc>=0.5)) { n0 = 3; n1 = 4; n2 = 6; n3 = 7; yc -= 0.5F;	} else
									{ n0 = 4; n1 = 5; n2 = 7; n3 = 8; xc -= 0.5F; yc -= 0.5F; };
		xc *= 2; 
		yc *= 2;
	} else {
		zERR_FATAL ("D: zModel(zCModelAniInst::CombineAni): illegal # of combineAnis: "+zSTRING(numCombAnis)+", Ani:"+protoAni->GetAniName());
	};
 
	if ((numCombAnis==2) || (numCombAnis==3)) {
		ani0 = protoAni->combAniList.Get(n0);
		ani1 = protoAni->combAniList.Get(n1);

		// Ani-Packing Konstanten fuer diese Ani aus einer der QuellAnis ziehen..
//		this->protoAni->samplePosRangeMin	= ani0->samplePosRangeMin;
//		this->protoAni->samplePosScaler		= ani0->samplePosScaler;

		zCQuat	quat1, quat2;
		zVEC3	trans1, trans2;
		zTMdl_AniSample *sample;
		for (int node=0; node<protoAni->numNodes; node++)
		{
//			zCModelNodeInst *tnode	= nodeList[node];
			zCModelNodeInst *tnode	= hostModel->nodeList[protoAni->nodeIndexList[node]];
			int frameNumber			= frame;
			int frameNext			= nextFrame;
			while (1) {
				assert (frameNumber<protoAni->numFrames);
				if (frameNumber>=protoAni->numFrames) break;		// SOLLTE NIE PASSIEREN
				// A=(02) 01
				quat1 = ani0->GetQuat	(frameNumber, node);
				quat2 = ani1->GetQuat	(frameNumber, node);
				quat1.Slerp				(yc, quat1, quat2);
				// Final-Matrix in PROTO-ANI speichern !
				sample			= (protoAni->aniSampleMatrix + (frameNumber*protoAni->numNodes) + node);
				{ this->protoAni->PrepareAniDataAccess(); sample->PackQuat(quat1); };
				// Translation lerpen => nur bei der RootNode (Optimierung)
				if (tnode->IsRootNode()) 
				{
					trans1 = ani0->GetTrans (frameNumber, node);
					trans2 = ani1->GetTrans	(frameNumber, node);
					{ this->protoAni->PrepareAniDataAccess(); sample->PackTrans (trans1 + yc * (trans2-trans1)); };
				}
				if (frameNext==-1) break;
				else {
					frameNumber	= nextFrame;
					frameNext	= -1;
				};
			};
		};
	} else {
		ani0 = protoAni->combAniList.Get(n0);
		ani1 = protoAni->combAniList.Get(n1);
		ani2 = protoAni->combAniList.Get(n2);
		ani3 = protoAni->combAniList.Get(n3); 

		// Ani-Packing Konstanten fuer diese Ani aus einer der QuellAnis ziehen..
//		this->protoAni->samplePosRangeMin	= ani0->samplePosRangeMin;
//		this->protoAni->samplePosScaler		= ani0->samplePosScaler;

		//	fuer alle nodes
		//		fuer alle anis

		zCQuat	quat1, quat2, quatA, quatB;
		zVEC3	trans1, trans2;
		zTMdl_AniSample *sample;
		for (int node=0; node<protoAni->numNodes; node++)
		{
//			zCModelNodeInst *tnode	= nodeList[node];
			zCModelNodeInst *tnode	= hostModel->nodeList[protoAni->nodeIndexList[node]];
			int frameNumber			= frame;
			int frameNext			= nextFrame;
			while (1) {
				// FIXME: kann mann wohl noch optimieren....
				// FIXME: Slerp oder Lerp ??
				// 0---1
				// |   |
				// 2---3 
				// A=(02) 01
				quat1 = ani0->GetQuat	(frameNumber, node);
				quat2 = ani2->GetQuat	(frameNumber, node);
				quatA.Slerp				(yc, quat1, quat2);
				// B=(13) 23
				quat1 = ani1->GetQuat	(frameNumber, node);
				quat2 = ani3->GetQuat	(frameNumber, node);
				quatB.Slerp				(yc, quat1, quat2);
				// (AB)
				quat1.Slerp				(xc, quatA, quatB);
				// Final-Matrix in PROTO-ANI speichern !!
				sample				= (protoAni->aniSampleMatrix + (frameNumber*protoAni->numNodes) + node);
				{ this->protoAni->PrepareAniDataAccess(); sample->PackQuat(quat1); };
				// Translation lerpen => nur bei der RootNode (Optimierung)
				if (tnode->IsRootNode()) {
					trans1 = ani0->GetTrans (frameNumber, node);
					trans2 = ani1->GetTrans	(frameNumber, node);
					{ this->protoAni->PrepareAniDataAccess(); sample->PackTrans (trans1 + yc * (trans2-trans1)); };
				}
				if (frameNext==-1) break;
				else {
					frameNumber	= nextFrame;
					frameNext	= -1;
				};
			};
		};
	};
};


////////////////////////////////////////
//	childVob / modelNode Attachments
//////////////////////////////////////////

void zCModel::AttachChildVobToNode (zCVob* childVob, zCModelNodeInst* modelNode) 
{
	if (!childVob)			return;
	if (!modelNode)			return;
	zTMdl_NodeVobAttachment attach;
	attach.vob				= childVob;
	attach.mnode			= modelNode;
	attachedVobList.Insert	(attach);
	childVob->AddRef		();
	childVob->SetTrafo		(GetTrafoNodeToModel(modelNode));
};

void zCModel::RemoveChildVobFromNode (zCVob* childVob)
{
	if (!childVob) return;
	for (int i=0; i<attachedVobList.GetNum(); i++) 
	{
		if (attachedVobList[i].vob==childVob) 
		{
			// attachment aus Liste loeschen
			attachedVobList[i].vob->Release();
			attachedVobList.RemoveIndex (i);
			return;
		};
	};
};


zCVob* zCModel::GetAttachedNodeVob(zCModelNodeInst* modelNode)
{
	// FIXME: mehrere vobs an einer node ???
	for (int i=0; i<attachedVobList.GetNum(); i++) 
	{
		if (attachedVobList[i].mnode==modelNode) 
		{
			return attachedVobList[i].vob;
		};
	};
	return 0;
};

void zCModel::RemoveAllChildVobsFromNode () 
{
	for (int i=0; i<attachedVobList.GetNum(); i++) 
		attachedVobList[i].vob->Release();
	attachedVobList.EmptyList();
};

void zCModel::UpdateAttachedVobs () 
{
	for (int i=0; i<attachedVobList.GetNum(); i++) 
	{
		zCVob *vob	= attachedVobList[i].vob;
		zERR_ASSERT (vob);
		// ist dieser childVob bereits 'gestorben' ?
		if ((!vob->GetVisual()) ||
		    (vob->GetVisual()->GetVisualDied()))
		{
			// attachment aus Liste loeschen
			attachedVobList.RemoveIndex (i);
			i--;
			RemoveStartedVobFX			(vob);		// ist dieser Vob ein VobFX ? dann aus dessen Liste entfernen
			vob->Release				();
		} else {
			// ok, gefunden: trafo Update
			attachedVobList[i].vob->SetTrafo(GetTrafoNodeToModel(attachedVobList[i].mnode));
		};
	};
};

void zCModel::RemoveStartedVobFX (zCVob* vobFX) 
{
	for (int i=0; i<startedVobFX.GetNum(); i++) {
		if (startedVobFX[i].vob==vobFX) {
			assert (vobFX->GetVisualClass()==zCParticleFX::GetStaticClassDef());
			assert (vobFX->GetRefCtr()>=1);
			if (vobFX) 
			if (vobFX->GetVisualClass()==zCParticleFX::GetStaticClassDef())
			{
				((zCParticleFX*)(vobFX->GetVisual()))->StopEmitterOutput(); 
			};
			startedVobFX.RemoveIndex(i);
			vobFX->Release			();
			return;
		};
	};
};

zVEC3 zCModel::GetVelocityRing () const 
{
	zVEC3 vel=0;
	for (int i=0; i<zMDL_VELRING_SIZE; i++) {
		vel += modelVelRing[i];
	};
	return vel * (zREAL( zREAL(1) / zREAL(zMDL_VELRING_SIZE)) );
};

void zCModel::ResetVelocity () 
{ 
	for (int i=0; i<zMDL_VELRING_SIZE; i++) modelVelRing[i]=0;
	modelVelocity=0;
};

void zCModel::GetAniMinMaxWeight (zCModelAniActive *modelAni, zVALUE& min, zVALUE& max) 
{
	min  = 2;
	max  =-2;

	for (int i=0; i<nodeList.GetNumInList(); i++) {
		if ((numActiveAnis==0) && (nodeList[i]->numNodeAnis>0))
			zERR_WARNING("D: ((numActiveAnis==0) && (mnode->numNodeAnis>0))");
		if ((numActiveAnis>0) && (nodeList[i]->numNodeAnis>0) && (nodeList[i]->masterAni>nodeList[i]->numNodeAnis-1))
			zERR_WARNING("D: masterAni: "+zSTRING(nodeList[i]->masterAni));
		int j = nodeList[i]->GetNodeAniListIndex (modelAni);
		if (j!=-1) {
			zVALUE w = nodeList[i]->nodeAniList[j].weight;
			min = zMin (min, w);
			max = zMax (max, w);
		};
	}; 
}; 

void zCModel::PrintStatus (int xpos, int ypos) 
{
	const int ADD = 250;
	const int TAB = 300;
	screen->Print (xpos + 0*TAB, ypos, "AniName");
	screen->Print (xpos + 6*TAB, ypos, "AscName");
	screen->Print (xpos +11*TAB, ypos, "Layer");
	screen->Print (xpos +13*TAB, ypos, "Frame");
	screen->Print (xpos +15*TAB, ypos, "dir");
	screen->Print (xpos +16*TAB, ypos, "fps");
	screen->Print (xpos +17*TAB, ypos, "(#anis: "+zSTRING(modelProtoList[0]->protoAnis.GetNumInList())+")");
	ypos += ADD;
	zSTRING ascName;
	for (int i=0; i<numActiveAnis; i++) {
		ascName = aniChannels[i]->protoAni->ascName;
		ascName.Delete (zSTRING("."), zSTR_FROM);
		zVALUE min, max;
//		GetAniMinMaxWeight (aniChannels[i], min, max); 
min = max = aniChannels[i]->transWeight;
		screen->Print (xpos + 0*TAB, ypos+i*ADD, aniChannels[i]->protoAni->aniName);
		screen->Print (xpos + 6*TAB, ypos+i*ADD, ascName);
		screen->Print (xpos +12*TAB, ypos+i*ADD, zSTRING(aniChannels[i]->protoAni->layer));
		screen->Print (xpos +13*TAB, ypos+i*ADD, zSTRING(aniChannels[i]->actFrame,1));
		screen->Print (xpos +14*TAB, ypos+i*ADD, ", "+zSTRING(aniChannels[i]->protoAni->numFrames));
		screen->Print (xpos +15*TAB, ypos+i*ADD, zSTRING(aniChannels[i]->advanceDir));  
		screen->Print (xpos +16*TAB, ypos+i*ADD, zSTRING(int(aniChannels[i]->protoAni->fpsRate)));  
		screen->Print (xpos +17*TAB, ypos+i*ADD, zSTRING(min,1));  
//		screen->Print (xpos +18*TAB, ypos+i*ADD, zSTRING(max,1));  
	};
};


zBOOL	zCModel::CorrectAniFreezer	()
{
	// keine zwei state anis auf demselben layer
	for (int i=0; i<numActiveAnis; i++) 
	{
		zCModelAniActive *ani = aniChannels[i];
		
		if ( ani->IsFadingOut() || ani->IsTransAni() ) continue;

		const int currentLayer = ani->protoAni->layer;
	
		for (int j=i+1; j<numActiveAnis; j++)
		{
			const zCModelAniActive *ani2 = aniChannels[j];
			
			if ( ani2->IsFadingOut() || ani2->IsTransAni() ) continue;

			if (ani2->protoAni->layer == currentLayer)
			{
				// BUG: zwei anis auf demselben layer
				// stoppe die erste und raus hier
				zERR_WARNING("C: fixed ani freezer for " + ani2->protoAni->aniName + " , killing ani: " + ani->protoAni->aniName);
				StopAni(ani);
				return TRUE;
			};
		};
	}
	return FALSE;
};

/*
	- 0 Ani: nix
	- 1 Ani idle:
		- ani-ID
		- nextAniOverride-ID ?
	- 1 Ani:
		- 2: ani-ID
		- 4: actFrame
		- 1: advanceDir
		- 2: nextAniOverride-ID 
	- n Anis:
		- 1: numActiveAnis
		- # Ani-Block (pro Ani)
			- 2: ani-ID
			- 4: actFrame
			- 1: advanceDir
			- 2: nextAniOverride-ID 
		- 1: numNodeAniCombis
		- # Node-Combi-Block (pro Node-Combi)
//			- # Falls 1 NodeAni:		(TODO, aber:selten)
//				- 2: ani-ID
			- # Falls n NodeAni:
				- # Node-Ani-Block		(pro Ani, die auf der Node sitzt)
					- 2: ani-ID			(Bit 15: Flag fuer MasterAni, Bit14: lastAni, TODO: 1Byte Index in den Ani-Block)
				- 2: masterAniSpeed		(approx)
				- # Node-Ani-Block		(pro Ani, die auf der Node sitzt, Reihenfolge wie oben)
					- 1: weight			(approx)
					- 2: weightSpeed	(approx)
					- 1: blendState

  - Der 1-Ani Standard-Fall ist wohl noch auf 5 (?) Bytes packbar.


  Ideen:
  - falls eine Looping Ani auch im letzten Frame uebertragen wurde, kann diese einfach so weiterlaufen..
  - bit-orientiertes Protokoll (mit spezieller Pack-Klasse)

*/

// level: 0 smallest, 1..

/*
static void psb_WriteString (zCBuffer& b, zSTRING& s) {
	b.WriteString (s);
};

static void psb_WriteAniName (zCBuffer& b, zCModelAni *ani) {
	zSTRING n (ani->GetAniName());
	psb_WriteString(b, n);
};

static void psb_ReadString (zCBuffer& b, zSTRING& s) {
	s = b.ReadString();
};
*/

void zCModel::psb_WriteAniBlock (zCBuffer& b, const int aniNr, const int level) const 
{
	zCModelAniActive*ani	= aniChannels[aniNr];
	zWORD			aniID	= ani->protoAni->GetAniID();
//	zWORD			aniID	= 0;
//psb_WriteAniName (b, ani->protoAni);

	// FIXME: pack: actFrame(float) => negativ => ein nextAniOv folgt, >8192 => advanceDir=-1
	if ((ani->protoAni->numAniEvents==0) && 
		(ani->isFadingOut			==0) && 
		(ani->nextAniOverride		==0)) 
	{
		b.WriteWord	( zWORD(aniID + (1<<15)) );
		if (ani->advanceDir==-1)	b.WriteFloat	(-ani->actFrame);
		else						b.WriteFloat	(ani->actFrame);
		goto nextLevel;
	};
	b.WriteWord	(aniID);

	// actFrame, aniDir, advanceDir
	{
		zVALUE actFrame = ani->actFrame;
		if (ani->nextAniOverride)	actFrame += 2048;
		if (ani->advanceDir==-1)	actFrame  = -actFrame;
		b.WriteFloat	(actFrame);					// packbar als 8.8 fixp.
		if (ani->nextAniOverride)	{
			b.WriteWord 	(ani->nextAniOverride->GetAniID());
//psb_WriteAniName (b, ani->nextAniOverride);
		};
	}
	b.WriteByte (ani->actAniEvent);

nextLevel:;
	if (level>=1) {
		b.WriteByte (ani->isFadingOut);
	};

	// FIXME: entweder	a) weiter packen, oder
	//					b) mit protoAni->GetMatrix4 die Matrix fuer die rootNode und den aktuellen Frame
	//					   organisieren, dann daraus die thisPos/thisRot holen !
	if (ani->protoAni->FlagMovesVob()) {
		b.WriteFloat (ani->thisPos[0]);
		b.WriteFloat (ani->thisPos[1]);
		b.WriteFloat (ani->thisPos[2]);
	};
	if (ani->protoAni->FlagRotatesVob()) {
		zVEC3 euler;
		ani->thisRotQuat.QuatToEuler (euler);
		b.WriteFloat (euler[0]);
		b.WriteFloat (euler[1]);
		b.WriteFloat (euler[2]);
	};
	if (ani->protoAni->GetAniType()==zMDL_ANI_TYPE_COMB) {
		b.WriteFloatPacked0_8 (ani->combAniX);
		b.WriteFloatPacked0_8 (ani->combAniY);
	};
};

void zCModel::psb_ReadAniBlock (zCBuffer& b, const int level, zCModelAniActive* ani) 
{
	//
	zWORD			aniID	= b.ReadWord();
	zCModelAni* protoAni	= GetAniFromAniID (aniID & ((1<<15)-1));
	ani->protoAni			= protoAni;
	ani->aniAttachment		= 0;
	ani->isFirstTime		= FALSE;
	ani->nextAni			= GetNextAni (protoAni);

	if (aniID>=(1<<15)) {
		ani->actAniEvent		= 0;
		ani->isFadingOut		= 0;
		ani->nextAniOverride	= 0;
		zVALUE actFrame			= b.ReadFloat(); 
		if (actFrame<0)	{ ani->advanceDir=-1; actFrame = -actFrame; }
		else			{ ani->advanceDir=+1; };
		ani->actFrame			= actFrame;
		goto nextLevel;
	};
	
	// actFrame, aniDir, advanceDir
	{
		zVALUE actFrame = b.ReadFloat();
		if (actFrame<0)		{ ani->advanceDir = -1; actFrame = -actFrame; }
		else				{ ani->advanceDir = +1; }; 
		if (actFrame>=2048) { 
			actFrame -= 2048;
			ani->nextAniOverride = GetAniFromAniID (b.ReadWord());
//			zSTRING aniName2;
//			psb_ReadString (b, aniName2);
//			ani->nextAniOverride = SearchAni (aniName2);
		};
		ani->actFrame			= actFrame;
	};
	
	// abhaengige Vars
	ani->actAniEvent		= b.ReadByte();
nextLevel:;
	if (level>=1) {
		ani->isFadingOut	= b.ReadByte();
	};

	if (ani->protoAni->FlagMovesVob()) {
		ani->thisPos[0]	= b.ReadFloat();
		ani->thisPos[1]	= b.ReadFloat();
		ani->thisPos[2]	= b.ReadFloat(); 
	};
	if (ani->protoAni->FlagRotatesVob()) {
		zVEC3 euler;
		euler[0]		= b.ReadFloat();
		euler[1]		= b.ReadFloat();
		euler[2]		= b.ReadFloat();
		ani->thisRotQuat.EulerToQuat (euler);
	};
	if (protoAni->GetAniType()==zMDL_ANI_TYPE_COMB) {
		ani->combAniX = b.ReadFloatPacked0_8();
		ani->combAniY = b.ReadFloatPacked0_8();
	};
};

// FIXME: actAniEvent !!!!!!!

 
void zCModel::PackStateBinary (zCBuffer& buffer)  
{
//	sizeWritten	= 0;
//	if (numActiveAnis==0) return;
//	if (numActiveAnis>1) return;

	buffer.SetMode (WRITE);

	// numActiveAnis als Header eintragen
	buffer.WriteByte (numActiveAnis); 
	if (numActiveAnis<=0) goto leave;

	//
	AssertActiveAniListAlloced ();

	if (numActiveAnis==1) {
		psb_WriteAniBlock (buffer, 0, 0);
	} else {
//		zerr.Message ("numAnis: "+zSTRING(numActiveAnis));
		// n Anis
		int i;

		// a) den Ani-Block schreiben
		for (i=0; i<numActiveAnis; i++)
			psb_WriteAniBlock (buffer, i, 1);

		// b) den Node-Combi-Block schreiben
		// alle moeglichen Ani-Kombinationen innerhalb der Nodes finden
		zCArray< zCModelNodeInst*> foundCombi(16);
		zBOOL oneOccured=FALSE;

		for (i=0; i<nodeList.GetNumInList(); i++) {
			int numNodeAnis = nodeList[i]->numNodeAnis;
			if (numNodeAnis>0) {
				// Gibt es bereits eine eingetragene NodeAniCombi mit genau diesen Anis ?
				int foundMatches=0;
				for (int j=0; j<foundCombi.GetNumInList(); j++) {
					// Die Node-Zahl muss gleich sein
					if (foundCombi[j]->numNodeAnis!=numNodeAnis) continue;
					foundMatches = 0;
					for (int k=0; k<numNodeAnis; k++) {
						for (int l=0; l<numNodeAnis; l++) {
							if (nodeList[i]->nodeAniList[l].modelAni==foundCombi[j]->nodeAniList[k].modelAni) foundMatches++;
						};
					};
					if (foundMatches==numNodeAnis) break;
				};
				if (foundMatches!=numNodeAnis) {
					// Diese Ani-Kombi ist so noch nicht vorhanden => eintragen
					foundCombi.Insert (nodeList[i]);
					if (numNodeAnis==1) oneOccured = TRUE;
				};
			};
		};

//		if (oneOccured) 
		{
			// Es muss immer sortiert werden ! Unpack erwartet die nodeCombis in fallende Reihenfolge !
			// BubbleSort
			for (int i=0; i<foundCombi.GetNumInList(); i++) {
				for (int j=foundCombi.GetNumInList()-1; j>=i; j--) {
					if (foundCombi[i]->numNodeAnis < foundCombi [j]->numNodeAnis) {
						zSwap (foundCombi[i], foundCombi[j]);
					};
				};
			};
		};
		
		// Nun die gefundenen Combis packen & schreiben
		buffer.WriteByte (foundCombi.GetNumInList());
		if (foundCombi.GetNumInList()>0) {

			for (i=0; i<foundCombi.GetNumInList(); i++) {
				// Hier wird jetzt eine spezielle aber typische Node abgepackt.
				zCModelNodeInst *node = foundCombi[i];
//				buffer.WriteByte (node->numNodeAnis);
				// FIXME: optimierbar, falls es nur -1- nodeAni gibt !
				for (int j=0; j<node->numNodeAnis; j++) {
					zWORD id = node->nodeAniList[j].modelAni->protoAni->GetAniID();
//zWORD id = 0;
//psb_WriteAniName (buffer, node->nodeAniList[j].modelAni->protoAni);

					if (j==node->masterAni)		id |= (1<<15);
					if (j==node->numNodeAnis-1)	id |= (1<<14);
					buffer.WriteWord (id);
				};
				buffer.WriteFloatPacked8_8		(node->masterAniSpeed);
				for (j=0; j<node->numNodeAnis; j++) {
					buffer.WriteFloatPacked0_8	(node->nodeAniList[j].weight);
					buffer.WriteFloatPacked8_8	(node->nodeAniList[j].weightSpeed);
//					buffer.WriteFloat			(node->nodeAniList[j].weightSpeed);
					buffer.WriteByte				(node->nodeAniList[j].blendState);
				};
			};
		};
	};

	// exit
leave:;
};


void zCModel::UnpackStateBinary (zCBuffer& buffer) { 

	// ??
	vobTrans	= 0;
//	vobRot		= zCQuat(0); 
	doVobRot	= FALSE;

	// FIXME: sollten die laufenden Anis nicht via ::StopAni() entfernt werden ?
	// aktive Anis deaktivieren
	for (int i=0; i<numActiveAnis; i++) {
		aniChannels[i]->MarkUnused();
	};

	buffer.SetMode (READ);

	// Header einlesen
	numActiveAnis = buffer.ReadByte ();
	if (numActiveAnis<=0) goto leave;

	//
	AssertActiveAniListAlloced ();

	if (numActiveAnis==1) 
	{
		aniChannels[0]			= &activeAniList[0];
		psb_ReadAniBlock (buffer, 0, aniChannels[0]);
		zCModelAniActive *ani	= aniChannels[0];

		if (!ani) { zERR_FAULT("D: UnpackStateBinary.1: ani==0"); numActiveAnis=0; goto leave; };

		// Nun alle Nodes durchgehen und einsetzen bzw. säubern
		// Achtung: nodes ohne ani saeubern, und nur AddNodeAni bei Nodes machen, die wirklich von der
		// Ani manipuliert werden !!!!!!
		// Erstmal _alle_ Nodes sauebern
		for (int i=0; i<nodeList.GetNumInList(); i++) {
			nodeList[i]->RemoveAllNodeAnis	();
		};
		for (i=0; i<ani->protoAni->numNodes; i++) {
//			ani->nodeList[i]->AddNodeAni	(ani);
			nodeList[ani->protoAni->nodeIndexList[i]]->AddNodeAni	(ani);
		};
	} else {
		// n Anis
		int i;
		// a) den Ani-Block lesen
		for (i=0; i<numActiveAnis; i++) {
			aniChannels[i] = &activeAniList[i];
			psb_ReadAniBlock (buffer, 1, aniChannels [i]);
			if (!aniChannels [i]) { zERR_FAULT("D: UnpackStateBinary.2: ani==0"); numActiveAnis=0; goto leave; };
		};

		// b) den Node-Combi-Block lesen
/*		- 1: numNodeAniCombis
		- # Node-Combi-Block (pro Node-Combi)
			- 1: numNodeAnis 

			- # Falls 1 NodeAni:
				- 2: ani-ID
			- # Falls n NodeAni:
				- # Node-Ani-Block (pro Ani, die auf der Node sitzt)
					- 2: ani-ID
				- 2: masterAni-ID
				- 2: masterAniSpeed
				- # Node-Ani-Block (pro Ani, die auf der Node sitzt, Reihenfolge wie oben)
					- 4: weight
					- 4: weightSpeed
					- 4: blendState    */
		int numNodeAniCombis = buffer.ReadByte ();														// READ														
		if (numNodeAniCombis>0) {				
			// Erstmal _alle_ Nodes sauebern
			for (int i=0; i<nodeList.GetNumInList(); i++) {
				nodeList[i]->RemoveAllNodeAnis	();
			};

			zCArray<zCModelNodeInst*> combiNodeList (nodeList.GetNumInList());
			for (i=0; i<numNodeAniCombis; i++) {
//				int numNodeAnis = buffer.ReadByte();														// READ
				int numNodeAnis = 0;
				zCModelAniActive* ani			[zMDL_MAX_ANIS_PARALLEL];
				zVALUE			aniWeight		[zMDL_MAX_ANIS_PARALLEL];
				zVALUE			aniWeightSpeed	[zMDL_MAX_ANIS_PARALLEL];
				int				aniBlendState	[zMDL_MAX_ANIS_PARALLEL];

				zCModelAniActive* masterAni		= 0;

				// welche Anis sind beteiligt ?
//zSTRING aniName;
				do {
//psb_ReadString (buffer, aniName);
					zWORD id			= buffer.ReadWord();
					zWORD id2			= zWORD(id & ((1<<14)-1));
					ani[numNodeAnis]	= GetActiveAni (id2);
//ani[numNodeAnis]->protoAni	= SearchAni (aniName);
//ani[numNodeAnis] = GetActiveAni (SearchAni (aniName));
if (!ani[numNodeAnis]) { zERR_FAULT("D: UnpackStateBinary.3: ani==0"); numActiveAnis=0; goto leave; };

					if ((id & (1<<15))!=0) masterAni = ani[numNodeAnis];
					numNodeAnis++;
					if ((id & (1<<14))!=0) break;
				} while (1);

/*

  oder mit gezogener waffe drehen ? das ist wichtig !! wann genau ?


numNodeAnis=3;
ani[0] = 0;
ani[1] = 0;
ani[2] != 0;

*/

				// 
				zVALUE masterAniSpeed	= buffer.ReadFloatPacked8_8	();

				// auf welchen Nodes sind ALLE beteiligten aktiv ?
				combiNodeList.EmptyList();
				if (numNodeAnis==1) {
					// Relevante Nodes sind nun die Nodes, die noch keinen Ani-Eintrag haben und eine Node dieser Ani sind
					// assert: numNodesAnis==1 kommen in der nodeAniCombi List am Ende
					for (int j=0; j<ani[0]->protoAni->numNodes; j++) {
//						if (ani[0]->nodeList[j]->numNodeAnis==0)	combiNodeList.Insert (ani[0]->nodeList[j]);
						zCModelAni *protoAni = ani[0]->protoAni;
						if (nodeList[protoAni->nodeIndexList[j]]->numNodeAnis==0)	combiNodeList.Insert (nodeList[protoAni->nodeIndexList[j]]);
					};
				} else {
					for (int j=0; j<ani[0]->protoAni->numNodes; j++) {
//						if (ani[0]->nodeList[j]->numNodeAnis<=0)	combiNodeList.Insert (ani[0]->nodeList[j]);
						zCModelAni *protoAni = ani[0]->protoAni;
						if (nodeList[protoAni->nodeIndexList[j]]->numNodeAnis<=0)	combiNodeList.Insert (nodeList[protoAni->nodeIndexList[j]]);
					};
					for (int k=1; k<numNodeAnis; k++) 
					{
						for (j=0; j<combiNodeList.GetNumInList(); j++) 
						{
							zBOOL found = FALSE;
							// ist eine Node der Ani 'k' nicht in der Liste ? => rauswerfen
							for (int l=0; l<ani[k]->protoAni->numNodes; l++) 
							{
//								if (ani[k]->nodeList[l]==combiNodeList[j]) { found = TRUE; break; };
								if (nodeList[ani[k]->protoAni->nodeIndexList[l]]==combiNodeList[j]) { found = TRUE; break; };
							};
							if (!found) {
								// ACHTUNG: setzt internes Verhalten des zCArray voraus !
								combiNodeList.RemoveIndex (j);
								j--;
							};
						};
					};
				};

				// Node-Ani-Block
				for (int j=0; j<numNodeAnis; j++) { 
					aniWeight		[j]	= buffer.ReadFloatPacked0_8	(); 
					aniWeightSpeed	[j]	= buffer.ReadFloatPacked8_8	();
//					aniWeightSpeed	[j]	= buffer.ReadFloat			();
					aniBlendState	[j]	= buffer.ReadByte			();
				};

				// Okay, jetzt haben wir endlich alle Infos zusammen => Nodes updaten !!!!
				for (j=0; j<combiNodeList.GetNumInList(); j++) {
					// Node wurde oben schon gesaeubert

					combiNodeList[j]->numNodeAnis	= numNodeAnis;
					combiNodeList[j]->masterAni		= -1;				// muss!
					for (int k=0; k<numNodeAnis; k++) {
						combiNodeList[j]->nodeAniList[k].modelAni		= ani			[k];
						combiNodeList[j]->nodeAniList[k].weight			= aniWeight		[k];
						combiNodeList[j]->nodeAniList[k].weightSpeed	= aniWeightSpeed[k];
						combiNodeList[j]->nodeAniList[k].blendState		= aniBlendState	[k];
						if (ani[k]==masterAni) combiNodeList[j]->masterAni = k;
					};

					// masterAni
					combiNodeList[j]->masterAniSpeed = masterAniSpeed;
				};
			};
		};
	};

	// aktive Anis aktivieren
//	for (i=0; i<numActiveAnis; i++)
//		aniChannels[i]->isRunning = TRUE;

 	// exit
leave:;
};

void zCModel::ShowAniListAdd (zCModelAni *ani) 
{
	if (!aniHistoryList) {
		aniHistoryList = zNEW(zCModelAni*) [MAX_ANIHISTORY];
		memset (aniHistoryList, 0, sizeof(aniHistoryList)*MAX_ANIHISTORY);
	};
	if (aniHistoryList[MAX_ANIHISTORY-1]==ani) return; 

	// Alle ein rauf
	for (int i=1; i<MAX_ANIHISTORY; i++) 
		aniHistoryList[i-1] = aniHistoryList[i];
	aniHistoryList[MAX_ANIHISTORY-1] = ani;
}

void zCModel::ShowAniList (int x) 
{
	if (!aniHistoryList) return;
	int y = 8191 - screen->FontY() * (MAX_ANIHISTORY+1);
	for (int n=0; n<MAX_ANIHISTORY; n++) {
		if (!aniHistoryList[n]) continue;
		screen          -> Print(x,y,aniHistoryList[n]->GetAniName());
		y += screen     -> FontY();
	}
}

zDWORD zCModel::GetRenderSortKey () const
{ 
	// while rendering vobs they are sorted by their visuals sort-key; 0xE is ored in order to keep all ProgMeshProtos/VB rendered in sequence
	if (modelProtoList.GetNum()>=1)	return zDWORD(modelProtoList[0]) | 0xE0000000;
	return zDWORD(this);
};	

zBOOL zCModel::TraceRay (	const zVEC3&		rayOrigin, 
							const zVEC3&		ray, 
							const int			traceFlags, 
							zTTraceRayReport	&report)
{
	// FIXME:
	// - es werden nur 'nodeVisuals' getestet, keine SoftSkins

	// Input-Ray		: objectSpace des Vobs
	// Output-Location	: objectSpace des Vobs

	// FIXME: temp HACK, damit NPCs im Spacer anklickbar sind

#ifdef COMPILING_SPACER
	if (meshSoftSkinList.GetNum()>0) 
	{
		report.Clear				();
		report.foundHit				= TRUE;
		return TRUE;
	};
#endif 

	// FIXME: temp HACK, damit Collision erstmal keinen Aerger macht
//	if (meshSoftSkinList.GetNum()>0) return TRUE;
	if (meshSoftSkinList.GetNum()>0) return FALSE;

	zTTraceRayReport	bestReport;	bestReport.Clear();
	zCModelNodeInst		*bestNode	= 0;
	zREAL				bestDist	= zREAL_MAX;

	zCArray<zVEC3>		xrayOrigin	(nodeList.GetNum());	xrayOrigin.MarkNumAllocUsed();
	zCArray<zVEC3>		xray		(nodeList.GetNum());	xray.MarkNumAllocUsed();

	// NodeTrafos berechnen, Ray in Node-Space transformieren
	// Ray gegen NodeVisuals testen
	{
		zTTraceRayReport	tmpReport;
		tmpReport.Clear();
		for (int i=0; i<nodeList.GetNum(); i++)
		{
			zCModelNodeInst *node = nodeList[i];
			if (node->GetParentNode())	node->trafoObjToCam	= node->GetParentNode()->trafoObjToCam	* node->trafo;
			else						node->trafoObjToCam = node->trafo;

			// sind Visuals an diese node gelinkt?
			zBOOL testNode	= node->GetNodeVisual() || (meshSoftSkinList.GetNum()>0);

			if (testNode)
			{
				// Ray ins KS der Node transformieren
				xrayOrigin[i]	= node->trafoObjToCam.InverseLinTrafo() * rayOrigin;
				xray[i]			= ray * node->trafoObjToCam;

				// Ray testen
				// Node-Visual ?
				if (node->GetNodeVisual()) 
				{
					zBOOL hit = node->GetNodeVisual()->TraceRay (xrayOrigin[i], xray[i], traceFlags, tmpReport);
					if (hit) 
					{
						// First Hit
						if ((traceFlags & zTRACERAY_FIRSTHIT)!=0) {
							bestReport	= tmpReport;
							bestDist	= 0;
							bestNode	= node;
							break;
						};

						// Nearest Hit
						zREAL dist = (xrayOrigin[i]-tmpReport.foundIntersection).Length2();
						if (dist<bestDist) {
							bestReport	= tmpReport;
							bestDist	= dist;
							bestNode	= node;
						};
					};
				};
			};
		};
	};

	// SoftSkins testen
	// (zu diesem Zeitpunkt sind alle NodeTrafos berechnet !)
	if (((traceFlags & zTRACERAY_FIRSTHIT)==0) || (bestDist<zREAL_MAX))
	{
		zBOOL	found = FALSE;
		zVEC3	inters;
		for (int i=0; i<meshSoftSkinList.GetNum(); i++)
		{
			zCMeshSoftSkin	*mesh = meshSoftSkinList[i];
			for (int j=0; j<mesh->nodeIndexList.GetNum(); j++) {
				int nodeIndex	= mesh->nodeIndexList[j];
// FIXME: Ray gegen die OBB und nicht die BBox testen..!
				zTBBox3D bbox	= mesh->nodeOBBList[j]->GetBBox3D();
				zBOOL hit		= bbox.TraceRay	(xrayOrigin[nodeIndex], xray[nodeIndex], inters);
				if (hit) {
					// First Hit
					if ((traceFlags & zTRACERAY_FIRSTHIT)!=0) {
						bestReport.foundHit			= TRUE;
						bestReport.foundIntersection= inters;
						bestReport.foundPolyNormal	= ray;					// FIXME: falsche Normale..
						bestReport.foundPolyNormal.NormalizeApprox();
						bestDist					= 0;
						bestNode					= nodeList[nodeIndex];
						found						= TRUE;
						break;
					};
					// Nearest Hit
					zREAL dist = (xrayOrigin[nodeIndex]-inters).Length2();
					if (dist<bestDist) {
						bestReport.foundHit			= TRUE;
						bestReport.foundIntersection= inters;
						bestReport.foundPolyNormal	= ray;					// FIXME: falsche Normale..
						bestReport.foundPolyNormal.NormalizeApprox();
						bestDist					= dist;
						bestNode					= nodeList[nodeIndex];
					};
				};
			};
			if (found) break;
		};
	};

	if (bestDist<zREAL_MAX)
	{
		report = bestReport;

		// Intersection & polyNormal nach parent vobSpace transformieren
		report.foundIntersection	= bestNode->trafoObjToCam * report.foundIntersection;
		if (traceFlags & zTRACERAY_POLY_NORMAL)
		{
			report.foundPolyNormal	= bestNode->trafoObjToCam.Rotate (report.foundPolyNormal);
		};

		return TRUE;
	};

	return FALSE;
};


//////////////////////////////////////////
//	Ani Attachments
//////////////////////////////////////////

static zTAniAttachment aniAttachSearchDummy;

int zCModel::AniAttachmentCompare	(const void* ele1,const void* ele2)
{
	if ((*((zTAniAttachment**)ele1))->aniID<((*(zTAniAttachment**)ele2))->aniID)	return -1;
	if ((*((zTAniAttachment**)ele1))->aniID>((*(zTAniAttachment**)ele2))->aniID)	return +1;
	else																			return  0;
};

zTAniAttachment* zCModel::SearchAniAttachList (zTModelAniID aniID) const
{
	aniAttachSearchDummy.aniID= aniID;
	int index = aniAttachList.Search	(&aniAttachSearchDummy);
	if (index>=0)	return aniAttachList[index];
	else			return 0;
};

void zCModel::RemoveAniAttachment (zTModelAniID aniID)
{
	zTAniAttachment* attach = SearchAniAttachList (aniID);	
	if (attach) {
		aniAttachList.RemoveOrder (attach);
		delete attach;
	};
};

void zCModel::RemoveAllAniAttachments ()
{
	for (int i=0; i<aniAttachList.GetNum(); i++)
	{
		zTAniAttachment* attach = aniAttachList[i];
		delete attach;
	};
	aniAttachList.EmptyList();
};

// [EDENFELD] 1.09 neu. Entfernt _alle_ aktuell laufenden PFX am Model
void zCModel::RemoveAllVobFX()
{
	zCVob* vobFX = NULL;
	
	for (int i = startedVobFX.GetNumInList()-1; i >= 0; i--)
	{
		vobFX = startedVobFX[i].vob;
		
		assert (vobFX->GetVisualClass()==zCParticleFX::GetStaticClassDef());
		assert (vobFX->GetRefCtr()>=1);
		
		if (vobFX) 
		if (vobFX->GetVisualClass()==zCParticleFX::GetStaticClassDef())
		{
			((zCParticleFX*)(vobFX->GetVisual()))->StopEmitterOutput(); 
		};
		startedVobFX.RemoveIndex(i);
		vobFX->Release			();
	}
}

zTAniAttachment* zCModel::GetCreateAniAttachment (zTModelAniID aniID)
{
	// attachment raussuchen / erzeugen
	zTAniAttachment* attach = SearchAniAttachList (aniID);	
	if (!attach) {
		attach					= zNEW(zTAniAttachment);
		attach->aniID			= aniID;
		attach->randAniFreq		= 1.0F;
		attach->randAniProbSum	= 0;
		aniAttachList.InsertSort(attach);
	};
	return attach;
};

	// random-anis
void zCModel::DeleteRandAniList	(zTModelAniID aniID)
{ 
	zTAniAttachment* attach = SearchAniAttachList (aniID);	
	if (!attach) return;
	attach->randAniList.EmptyList();	
};

void zCModel::InsertRandAni (zTModelAniID aniID, zTModelAniID insertAniID, const int prob)
{
	if (aniID==zMDL_ANI_ID_ILLEGAL)	return;
	zTAniAttachment* attach = GetCreateAniAttachment (aniID);	

	// einfuegen
	zTRandAni randAni;
	randAni.randAniProtoID	= insertAniID;
	randAni.prob			= prob;
	// bereits in Liste ?
//s	if (attach->randAniList.IsInList(randAni))	return;

	attach->randAniList.Insert	(randAni);
	attach->randAniProbSum	+=	prob;
};

zREAL zCModel::GetRandAniFreq (zTModelAniID aniID) const 
{ 
	const zTAniAttachment* attach = SearchAniAttachList (aniID);	
	if (!attach) return 0;
	return attach->randAniFreq;		
};

void zCModel::SetRandAniFreq (zTModelAniID aniID, const zREAL freq) 
{ 
	zTAniAttachment* attach = GetCreateAniAttachment (aniID);	
	attach->randAniFreq		= freq;
};

void zCCFASTCALL zCModel::RecalcRootPosLocal (const zBOOL selectHighestY)
{
	// evtl. ausfadende Anis nicht beruecksichtigen!
	this->rootPosLocal = zVEC3(0);
	for (int i=0; i<this->GetNumActiveAnis(); i++)
	{
		zCModelAniActive	*aniActive	= aniChannels[i];
		zCModelAni			*aniProto	= aniActive->protoAni;

		if (aniProto->rootNodeIndex>=0)
		{
			// Unpack Animation Data
			aniProto->PrepareAniDataAccess	(); 

			zVEC3			trans;
			zTMdl_AniSample	*strafo			= aniProto->aniSampleMatrix + (zFloat2IntFloor(aniActive->actFrame) * aniProto->numNodes) + aniProto->rootNodeIndex;
			strafo->UnpackTrans				(trans);
			if (selectHighestY)
			{
				if (trans[VY]>rootPosLocal[VY])		rootPosLocal = trans;
			} else 
			{
				if (trans[VY]<rootPosLocal[VY])		rootPosLocal = trans;
			};
		};
	};
	// Model-Scale einrechnen
	if (modelScaleOn) {
		rootPosLocal= Alg_Prod (rootPosLocal, modelScale);
	};
};
