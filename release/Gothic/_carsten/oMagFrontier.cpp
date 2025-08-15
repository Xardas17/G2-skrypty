#include "zcore.h"
#include "zinput.h"
#include "zflash.h"
#include "zAccount.h"

#include "omagfrontier.h"
#include "onpc.h"
#include "ovisfx.h"
#include "oaihuman.h"
#include "ogame.h"
#include "ogamemanager.h"
#include "oworld.h"
#include "iostream"


#pragma warning( disable : 4244 )  
 
enum { DIST_WARNING		= 3000	};  // 30m - Warning (display in DevMode only)
enum { DIST_SHOOT		= 1500	};  // 15m - FishFood

static const zVEC3 s_sphereOrigin = zVEC3(0,0,0);

oCMagFrontier::oCMagFrontier()
{
	isWarning		= FALSE;	
	isShooting		= FALSE;	

	warningFX		= NULL; 
	shootFX			= NULL;
	npc				= NULL;
}

oCMagFrontier::~oCMagFrontier()
{
	if (shootFX)
	{
		shootFX->Stop();
        zRELEASE_ACCT(shootFX);
	}
	if (warningFX)
	{
		warningFX->Stop();
        zRELEASE_ACCT(warningFX);
	}
	npc				= NULL;
}

void oCMagFrontier::SetNPC(oCNpc *newnpc)
{
	npc = newnpc;
}

void oCMagFrontier::DoCheck()
{
	// [EDENFELD] Magische Barriere f�r 1.09 bzw. Gothic 2 deaktiviert
	// [BENDLIN] machen wir aus dem Blitz eben Fischfutter...
	// return;


	if (npc != oCNpc::player)
		return;
	if (!gameMan)
		return;
	if (!ogame)
		return;
	if (!ogame->GetGameWorld())
		return;
	if (zCCamera::activeCam->GetVob()->GetHomeWorld()->GetCutscenePlayer()->GetPlayingGlobalCutscene())
		return;

	bool isNewWorld = (ogame->GetGameWorld()->GetWorldName().CompareTo("NEWWORLD") == 0);
	bool isDragonIsland = false;
	if (!isNewWorld)
		isDragonIsland = (ogame->GetGameWorld()->GetWorldName().CompareTo("DRAGONISLAND") == 0);
	bool isAddonWorld = false;
	if (!isNewWorld && !isDragonIsland)
		isAddonWorld = (ogame->GetGameWorld()->GetWorldName().CompareTo("ADDONWORLD") == 0);

	if (isNewWorld || isDragonIsland || isAddonWorld)
	{
		zERR_ASSERT (npc);
		if (!npc)
			return;
		if (npc->GetAttribute(NPC_ATR_HITPOINTS) <= 0)
			return;
		zVEC3 playerProjPos = npc->GetPositionWorld();
		zVEC3 startPoint;
		zREAL distToBarriere=60000;
		
	    if (isNewWorld)
			GetDistanceNewWorld(playerProjPos, distToBarriere, startPoint);
	    if (isDragonIsland)
			GetDistanceDragonIsland(playerProjPos, distToBarriere, startPoint);
		else 
			GetDistanceAddonWorld(playerProjPos, distToBarriere, startPoint);

		if (ogame->GetGameWorld()->GetCutscenePlayer()->GetPlayingGlobalCutscene() == NULL)
		{
			enum { STATE_NONE, STATE_WARNING, STATE_SHOOT };
			static int lastState = STATE_NONE;
			static zCSoundFX* oceanWarn = 0;
			static zTSoundHandle oceanWarnHandle = 0;
			zBOOL devMode = (ogame && ogame->GetTextView() && ogame->IsInDevMode());

			if ((distToBarriere <= DIST_WARNING)  && (distToBarriere >= 0))
			{

				if((distToBarriere <= DIST_SHOOT) && (distToBarriere >= 0))
				{
					// fishfood
					if (devMode)
					{
						if (lastState != STATE_SHOOT)
							ogame->GetTextView()->Printwin("Piranhas crunching your boots.");
					}
					else
					{
						npc->SetAttribute(NPC_ATR_HITPOINTS, 0);
						npc->DoDie();
						gameMan->PlayVideoEx("FishFood.bik", 0, TRUE);
					}
					lastState = STATE_SHOOT;
				}
				else // warn
				{	
					if (lastState != STATE_WARNING)
					{
						// OCEAN_WARN
						if ((lastState == STATE_NONE) && !oceanWarn && zsound)
							oceanWarn = zsound->LoadSoundFXScript("OCEAN_WARN");
						if (oceanWarn) 
							oceanWarnHandle = zsound->PlaySound(oceanWarn);

						if (devMode)
							ogame->GetTextView()->Printwin("Piranhas are watching you.");
					}
					lastState = STATE_WARNING;
				}
			}
			else  // away 
			{
				if (lastState != STATE_NONE)
				{
					// OCEAN_WARN
					if (oceanWarn && zsound && zsound->IsSoundActive(oceanWarnHandle))
					{
						zsound->StopSound(oceanWarnHandle);
						oceanWarnHandle = 0;
					}

					if (devMode)
						ogame->GetTextView()->Printwin("Well, swim home to mommy.");
				}
				lastState = STATE_NONE;
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void GetNearestPointFromLineSegment2D(const zVEC2& a, const zVEC2& b, const zVEC2& c, zVEC2& nearest)
{
	int dotA, dotB;

	dotA = (c.n[VX] - a.n[VX]) * (b.n[VX] - a.n[VX]) + (c.n[VY] - a.n[VY]) * (b.n[VY] - a.n[VY]);
	if (dotA <= 0)
	{
		nearest.n[VX] = a.n[VX];
		nearest.n[VY] = a.n[VY];
		return;
	}
	dotB = (c.n[VX] - b.n[VX]) * (a.n[VX] - b.n[VX]) + (c.n[VY] - b.n[VY]) * (a.n[VY] - b.n[VY]);
	if (dotB <= 0)
	{
		nearest.n[VX] = b.n[VX];
		nearest.n[VY] = b.n[VY];
		return;
	}
	nearest[VX] = a.n[VX] + ((b.n[VX] - a.n[VX]) * dotA) / (dotA + dotB);
	nearest[VY] = a.n[VY] + ((b.n[VY] - a.n[VY]) * dotA) / (dotA + dotB);
}

static void DrawLineSegment2D(const zVEC2& a, const zVEC2& b, zREAL z, zCOLOR color)
{
	zCCamera* camera = ogame->GetCamera();
	if (camera)
	{
		zPOINT3 wsPoint1, wsPoint2, csPoint1, csPoint2;	// world/camera-space
		zPOINT2 ssPoint1, ssPoint2;						// screen-space X,Y
		wsPoint1 = zPOINT3(a.n[0], z, a.n[1]);
		wsPoint2 = zPOINT3(b.n[0], z, b.n[1]);
		csPoint1 = camera->Transform(wsPoint1);
		csPoint2 = camera->Transform(wsPoint2);
		Alg_ClipAtZ0(csPoint1, csPoint2);
		if (csPoint1[VZ] >=0)
		{
			camera->Project(&csPoint1, ssPoint1[VX], ssPoint1[VY]);
			if (csPoint2[VZ] >= 0)
			{
				camera->Project(&csPoint2, ssPoint2[VX], ssPoint2[VY]);
				int x1 = (int)ssPoint1[VX];
				int y1 = (int)ssPoint1[VY];
				int x2 = (int)ssPoint2[VX];
				int y2 = (int)ssPoint2[VY];
				if (screen->ClipLine(x1, y1, x2, y2))
					zrenderer->DrawLineZ(x1, y1, 1 / csPoint1[VZ], x2, y2, 1 / csPoint2[VZ], color);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define POINTS_NEWWORLD 16
static const zPOINT2 pointsNewWorld[POINTS_NEWWORLD] =
{
	zVEC2(  2239.80f, -26038.05f),  // 0
	zVEC2( -2414.90f, -29257.15f),  // 1
	zVEC2( -9273.81f, -42421.26f),  // 2
	zVEC2(-17719.90f, -35231.39f),  // 3
	zVEC2(-22401.22f, -20667.81f),  // 4
	zVEC2(-28248.86f, -11513.19f),  // 5
	zVEC2(-33772.49f,  -6360.24f),  // 6
	zVEC2(-34328.64f,   6643.39f),  // 7
	zVEC2(-29140.41f,  10423.14f),  // 8
	zVEC2(-25256.57f,  17571.10f),  // 9
	zVEC2(-18392.18f,  35872.64f),  // 10
	zVEC2( -8837.53f,  45658.92f),  // 11
	zVEC2(  2936.05f,  49561.97f),  // 12
	zVEC2( 14839.61f,  56497.82f),  // 13
	zVEC2( 23767.39f,  38923.98f),  // 14
	zVEC2( 28115.52f,  37965.91f),  // 15
};

zREAL oCMagFrontier::GetDistanceNewWorld( const zVEC3& pos, zREAL& dist, zVEC3& nearestPoint )
{
	// Draw lines in GodMode
	zBOOL showLineOfDeath = (ogame && oCNpc::godmode);
	
	// default (far away)
	dist = 10000000.00f;
	// Invalid player position (game init)
	if ((pos.n[0] == 0) && (pos.n[2] == 0))
		return (dist);
	// Position much above water
	if (!showLineOfDeath && (pos.n[1] > 200))
		return (dist);

	zVEC2 pos2d = zVEC2(pos.n[0], pos.n[2]);

	// Check points
	for (int x = 0; x < POINTS_NEWWORLD - 2; x++)
	{
		zVEC2 a = pointsNewWorld[x];
		zVEC2 b = pointsNewWorld[x + 1];
		zVEC2 nearest;
		GetNearestPointFromLineSegment2D(a, b, pos2d, nearest);
		
		// Draw lines in GodMode
		if (showLineOfDeath)
		{
			DrawLineSegment2D(a, b, -800.0f, (x & 1) ? GFX_BLUE : GFX_LBLUE);
			if (pos.n[1] > 200)
				continue;
		}

		zVEC2 temp = nearest - pos2d;
		zREAL dist2 = temp.Length();
		if (dist2 < dist)
			dist = dist2;
	}

	return (dist);
};

#define POINTS_DRAGONISLAND 7
static const zVEC2 pointsDragonIsland[POINTS_DRAGONISLAND] =
{
	zVEC2(-27690.03f, -24083.83f),  // 0
	zVEC2(-27581.32f, -34736.61f),  // 1
	zVEC2(-20461.35f, -40660.86f),  // 2
	zVEC2( -6982.32f, -41965.29f),  // 3
	zVEC2(  1550.78f, -39247.74f),  // 4
	zVEC2(  4322.67f, -31095.10f),  // 5
	zVEC2(  4811.83f, -25388.25f),  // 6
};

zREAL oCMagFrontier::GetDistanceDragonIsland( const zVEC3& pos, zREAL& dist, zVEC3& nearestPoint )
{
	// default (far away)
	dist = 10000000.00f;
	// Invalid player position (game init)
	if ((pos.n[0] == 0) && (pos.n[2] == 0))
		return (dist);

	zVEC2 pos2d = zVEC2(pos.n[0], pos.n[2]);

	// Draw lines in GodMode
	zBOOL showLineOfDeath = (ogame && oCNpc::godmode);
	
	// Check points
	for (int x = 0; x < POINTS_DRAGONISLAND - 2; x++)
	{
		zVEC2 a = pointsDragonIsland[x];
		zVEC2 b = pointsDragonIsland[x + 1];
		zVEC2 nearest;
		GetNearestPointFromLineSegment2D(a, b, pos2d, nearest);

		// Draw lines in GodMode
		if (showLineOfDeath)
			DrawLineSegment2D(a, b, -800.0f, (x & 1) ? GFX_BLUE : GFX_LBLUE);

		zVEC2 temp = nearest - pos2d;
		zREAL dist2 = temp.Length();
		if (dist2 < dist)
			dist = dist2;
	}

	return (dist);
};

#define POINTS_ADDONWORLD 7
static const zVEC2 pointsAddonWorld[POINTS_ADDONWORLD] =
{
	zVEC2(-25000.0f, 46000.0f),  // 0
	zVEC2(-34000.0f, 44000.0f),  // 1
	zVEC2(-41000.0f, 39000.0f),  // 2
	zVEC2(-46000.0f, 30000.0f),  // 3
	zVEC2(-50000.0f, 20000.0f),  // 4
	zVEC2(-51000.0f, 13000.0f),  // 5
	zVEC2(-51000.0f, 07000.0f),  // 6
};

zREAL oCMagFrontier::GetDistanceAddonWorld( const zVEC3& pos, zREAL& dist, zVEC3& nearestPoint )
{
	// default (far away)
	dist = 10000000.00f;
	// Invalid player position (game init)
	if ((pos.n[0] == 0) && (pos.n[2] == 0))
		return (dist);

	zVEC2 pos2d = zVEC2(pos.n[0], pos.n[2]);

	// Draw lines in GodMode
	zBOOL showLineOfDeath = (ogame && oCNpc::godmode);
	
	// Check points
	for (int x = 0; x < POINTS_ADDONWORLD - 2; x++)
	{
		zVEC2 a = pointsAddonWorld[x];
		zVEC2 b = pointsAddonWorld[x + 1];
		zVEC2 nearest;
		GetNearestPointFromLineSegment2D(a, b, pos2d, nearest);

		// Draw lines in GodMode
		if (showLineOfDeath)
			DrawLineSegment2D(a, b, -2100.0f, (x & 1) ? GFX_BLUE : GFX_LBLUE);

		zVEC2 temp = nearest - pos2d;
		zREAL dist2 = temp.Length();
		if (dist2 < dist)
			dist = dist2;
	}

	return (dist);
};

void oCMagFrontier::StartLightningAtPos(zPOINT3 &a, zPOINT3 &b)
{
	{
		zCVob	*vob					= zNEW(zCVob);
		zCFlash *lightning				= zNEW(zCFlash);

		lightning->Create				 ( a, b, 0.65f );
		lightning->SetTexture			 ( zSTRING("lightningNEU_big_a0.tga") );//flash_a0.TGA") );
		
		vob->SetVisual					(lightning);	  
		vob->SetShowVisual				(TRUE);
		vob->SetVobName					("Lightning-Vob");
		vob->SetDrawBBox3D				(FALSE);
		vob->SetPositionWorld			(a);
		vob->SetDontWriteIntoArchive	(TRUE);

		zCCamera::activeCam->GetVob()->GetHomeWorld()->AddVobRelease(vob);

		vob->SetSleeping				(FALSE);
		vob->SetCollDetStat				(FALSE);
		vob->SetCollDetDyn				(FALSE);

		zRELEASE(lightning); // [Moos] das Vob k�mmert sich nun darum
	};

	// add quadmark for collision point with world
	{
		zVEC3 startQuad = a;
		zVEC3 endQuad = b-a;

		endQuad.Normalize();
		endQuad*=10000;

		zCQuadMark *quady				= zNEW(zCQuadMark);
		zCVob      *vob2				= zNEW(zCVob);

		vob2->SetPositionWorld(a);
		vob2->SetVisual					(quady);	  
		vob2->SetShowVisual				(TRUE);
		vob2->SetVobName				("Blitz-Einschlag-Vob");
		vob2->SetDrawBBox3D				(FALSE);
		vob2->SetSleeping				(FALSE);
		vob2->SetCollDetStat			(FALSE);
		vob2->SetCollDetDyn				(FALSE);
		vob2->SetDontWriteIntoArchive	(TRUE);

		zCCamera::activeCam->GetVob()->GetHomeWorld()->AddVobRelease(vob2);

		zCMaterial *quadMat				= zNEW(zCMaterial);
		quadMat->SetTexture				( zSTRING("fireballquadmark.tga") );
		quadMat->SetAlphaBlendFunc		(zRND_ALPHA_FUNC_MUL );//ADD);

		zCQuadMark::zTEffectParams		 aniEffects;
		aniEffects.texAniType			= zCQuadMark::zTEXANI_NONE;
		aniEffects.texAniSpeed			= 0.0F;
		aniEffects.texAniScaleStart		= 0.0F;
		
		quady->CreateQuadMark  ( startQuad,
								 endQuad,
								 zVEC2(100.0f,100.0f),
								 quadMat,
								 NULL );//&aniEffects );

		zRELEASE(quady);     // [Moos] das Vob k�mmert sich nun darum
		zRELEASE(quadMat);
	}
};

void oCMagFrontier::DoWarningFX(const int level)
{
	if (isShooting) return;

	if (isWarning) 
	{
		warningFX->SetLevel(level);
		return;
	}
	else isWarning = TRUE;

	warningFX = zNEW(oCVisualFX);
	warningFX->SetByScript("BARRIERE_PC_WARNING");
	warningFX->SetPositionWorld(npc->GetPositionWorld());
	npc->GetHomeWorld()->AddVob(warningFX);
	warningFX->Init(npc);
	warningFX->SetLevel(1);

	// Camera FX ?
};

void oCMagFrontier::DisposeWarningFX()
{
	if( warningFX ) 
	{
		warningFX->Stop();
		zRELEASE_ACCT(warningFX);
	}

	isWarning  = FALSE;
};

void oCMagFrontier::DoShootFX( const zVEC3& startPoint )
{
	if (isShooting) {
		return;
	}
	else isShooting = TRUE;

	shootFX = zNEW(oCVisualFX);
	shootFX->SetByScript("BARRIERE_PC_SHOOT");
	shootFX->SetPositionWorld(npc->GetPositionWorld());
	npc->GetHomeWorld()->AddVob(shootFX);
	shootFX->Init(npc);
	shootFX->Cast();

//	zRELEASE(shootFX);

	zPOINT3 contactPoint		= npc->GetPositionWorld();
	zVEC3	sphereOriginHighY	(s_sphereOrigin[VX],10000,s_sphereOrigin[VZ]);
	zVEC3	pos					= npc->GetPositionWorld();
	zVEC3	flyDir				= (sphereOriginHighY-pos).Normalize();

	npc->GetEM()->OnDamage( npc, shootFX, 5, oEDamageType_Barrier | oEDamageType_Magic, flyDir );

	zVEC3 v = 1000 * (contactPoint - s_sphereOrigin).Normalize();
	v[VZ]	= 0;

	zPOINT3 spherePos = contactPoint + (1000 * zVEC3(0,1,0)) + v;
						
	StartLightningAtPos( spherePos, contactPoint );
};

void oCMagFrontier::DisposeShootFX()
{
	if( shootFX ) 
	{
		shootFX->Stop();
		zRELEASE_ACCT(shootFX);
	}

	isShooting=FALSE;
};

#pragma warning( default : 4244 )  
