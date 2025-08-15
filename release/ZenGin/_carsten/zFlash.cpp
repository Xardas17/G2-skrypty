/******************************************************************************** 
 
     $Workfile:: zFlash.cpp       $                 $Date:: 24.04.01 17:33      $
     $Revision:: 9                $                 $Modtime:: 19.04.01 0:57    $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Carsten/zFlash.cpp $
 * 
 * 9     24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 8     15.01.01 20:15 Moos
 * 
 * 7     12.10.00 16:17 Moos
 * 
 * 6     23.09.00 14:26 Simon
 * 
 * 5     22.09.00 20:10 Simon
 * 
 * 4     5.09.00 19:19 Simon
 * 
 * 3     29.08.00 14:45 Edenfeld
 * 
 * 1     29.08.0 13:05 Simon
 * ZenGin v0.92
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 9 $ ($Modtime: 19.04.01 0:57 $)

#include "zcore.h"
#include <zVob.h>
#include "zFlash.h"

//zCLASS_DEFINITION	(zCFlash, zCVisual,	0, 0)

//
//
//

zCFlash::zCFlash()
{
	timeAlive		= 0;
	LastUpdateTime	= 0;
	boltRoughness	= 0.65f;
	textureName		= zSTRING("flash_a0.TGA");
	recalcStep		= TRUE;

    splitBolt		= zNEW(zCBolt);
    rootBolt		= zNEW(zCBolt);
}

//
//
//

zCFlash::~zCFlash()
{
    zRELEASE(splitBolt);
    zRELEASE(rootBolt);
}

//
//
//

zBOOL zCFlash::GetVisualDied()
{
	if( timeAlive > 1 ) {
		return TRUE;
	}
	else
		return FALSE;
};

//
//
//

zCFlash::zCBolt::zCBolt()
{
	aniPhase=0;
}

//
//
//

zBOOL zCFlash::Render (zTRenderContext& renderContext) 
{
	Update(70);

	splitBolt->Render(renderContext);
	return rootBolt->Render(renderContext);
};

//
//
//

void zCFlash::SetVisualUsedBy (zCVob* vob) 
{ 
	vob->SetIgnoredByTraceRay	(TRUE);
	vob->SetCollDet				(FALSE);
};

//
//
//

void zCFlash::SetProjectionSphere (const zTBSphere3D& sphere) 
{
	rootBolt->SetProjectionSphere(sphere);
};

//
//
//

void zCFlash::zCBolt::SetProjectionSphere (const zTBSphere3D& sphere) 
{
	projectionSphere = sphere;

	if(!childList.IsEmpty())
	{
		for( int x = 0; x < childList.GetNum(); x++)
		{
			childList[x]->SetProjectionSphere(sphere);
		}
	}
};

//
//
//

void zCFlash::Generate ( zCBolt *bolt, const zPOINT3& startPos, const zPOINT3& endPos, zREAL roughness1 ) 
{
	bolt->FreeResources	();

	boltStartPos = startPos;
	boltEndPos   = endPos;

	bolt->SetGlobalAlpha  	( 255 );
//	bolt->SetAlphaFadeSpeed  ( 0.05F );

	bolt->isRootBolt     = TRUE;
	bolt->numberOfChilds = 2;
	bolt->roughness      = roughness1;
	bolt->boltIndex      = 0;

	bolt->SetWidth( 50 );
	
	bolt->Generate_R( boltStartPos, boltEndPos, 0 );

//

	splitBolt->FreeResources  ();

	splitBolt->SetGlobalAlpha  	( 255 );
//	bolt->SetAlphaFadeSpeed  ( 0.05F );

	splitBolt->isRootBolt     = TRUE;
	splitBolt->numberOfChilds = 2;
	splitBolt->roughness      = roughness1;
	splitBolt->boltIndex      = 0;

	splitBolt->SetWidth( 50 );

	zVEC3 startPos2 = rootBolt->GetCenterPointList  ()[rootBolt->GetNumSeg  ()-7];
	zVEC3 endPos2 =  endPos;	

	endPos2[VX] += (zRandF(40))-20;
	endPos2[VY] += (zRandF(40))-20;
	endPos2[VZ] += (zRandF(40))-20;

	zREAL len		= (endPos2-startPos2).LengthApprox();
	int numPoints	= int(len / (1000.0F) * 24.0F);

    // [Moos] Sicherheit
    if (numPoints > 1024)
        numPoints = 1024;

	numPoints		= zMakePowerOf2Lower(numPoints)+1;

	splitBolt->AllocateResources	(numPoints);

	zTBSphere3D sphere;
	zVEC3		startDir = zVEC3(0.0f,0.0f,1.0f);
	sphere.center = endPos2+zVEC3(100,-100,100);
	sphere.radius = (endPos2-startPos2).Length();
	startDir      = zVEC3(zRandF2(), zRandF2(), zRandF2());
	startDir.Normalize();

	splitBolt->SetCamAlign          ( zCPolyStrip::zCAM_ALIGN_STRIP            );
	splitBolt->GenerateCircle       ( sphere, startPos2, startDir              );
 	splitBolt->GenerateCPLightning0 ( startPos2, endPos2 , splitBolt->roughness );

/*
	splitBolt->FreeResources  ();

	splitBolt->SetGlobalAlpha  	( 255 );
//	bolt->SetAlphaFadeSpeed  ( 0.05F );

	splitBolt->isRootBolt     = TRUE;
	splitBolt->numberOfChilds = 2;
	splitBolt->roughness      = roughness1;
	splitBolt->boltIndex      = 0;

	splitBolt->SetWidth( 40 );

	zREAL len		= (endPos-startPos).LengthApprox();

 	zVEC3 splitStart = rootBolt->GetCenterPointList()[rootBolt->GetNumSeg()-2];
	zVEC3 splitEnd;

	splitEnd	  = zVEC3(zRandF2(), -(zRandF()*0.5F +0.5F), zRandF2());
	splitEnd.NormalizeApprox();
	splitEnd	  = splitStart + splitEnd * (zRandF()*0.3F + 0.3F) * (len/10);
	splitEnd[VX] += (zRand(300)-150);
	splitEnd[VY] += (zRand(300));
	splitEnd[VZ] += (zRand(300)-150);

	splitBolt->Generate_R( splitStart, splitEnd, 0, FALSE );
*/
};

//
//
//

void zCFlash::zCBolt::Generate_R ( const zPOINT3& startPos, const zPOINT3& endPos, zREAL depth, zBOOL addEnd ) 
{
	zREAL len		= (endPos-startPos).LengthApprox();
	int numPoints	= int(len / (1000.0F) * 8.0F);
	numPoints		= zMakePowerOf2Lower(numPoints)+1;

	AllocateResources	(numPoints);

	zTBSphere3D sphere;
	zVEC3		startDir = zVEC3(0.0f,0.0f,1.0f);
	sphere.center = endPos+zVEC3(100,-100,100);
	sphere.radius = (endPos-startPos).Length();
	startDir      = zVEC3(zRandF2(), zRandF2(), zRandF2());
	startDir.Normalize();

	SetCamAlign( zCPolyStrip::zCAM_ALIGN_STRIP );

	if( !isRootBolt ) {
		numberOfChilds-=1;
		
		if(numberOfChilds<=0) return;

		if( (20/(depth*3)) <= 3 )
			SetWidth(3);
		else
			SetWidth(20/(depth*3));

		SetGlobalAlpha     (165);
//		SetAlphaFadeSpeed  (1.0F/depth * 0.1f);
	}

	GenerateCircle( sphere, startPos, startDir );

	zPOINT3 endPosVar = endPos;
	endPosVar[VX] += (zRandF(200))-100;
	endPosVar[VY] += (zRandF(200))-100;
	endPosVar[VZ] += (zRandF(200))-100;


	GenerateCPLightning0(startPos, endPosVar ,roughness);

	int numChilds = 0;

	if( isRootBolt ) numChilds = numSeg-1;
	else numChilds = int(zRand(6));

	if (numChilds<=0) return;
	childList.AllocAbs (numChilds);

	for (int i=0; i<numChilds; i++) 
	{
		int		stitchIndex;
		zVEC3	childStartPos;
		zVEC3	childEndPos;

		zCBolt *bolt	= zNEW(zCBolt);
		bolt->isRootBolt = FALSE;
		bolt->isChildOne = TRUE;
		bolt->numberOfChilds = numberOfChilds;
		bolt->roughness = 0.4f;

		if( isRootBolt ) {
			
			boltIndex  += 1;
			if( boltIndex >= numSeg ) boltIndex = 0;
			stitchIndex=boltIndex;

		}
		else {
			stitchIndex		= (firstSeg + zRand(numSeg )) % numSeg;
		}

		childStartPos	= centerPointList[stitchIndex];

		childEndPos = childStartPos;

		zVEC3 dir = (endPos-startPos).Normalize();

		childEndPos += (dir*(len/15));

//		childEndPos		= zVEC3(zRandF2(), -(zRandF()*0.5F +0.5F), zRandF2());
//		childEndPos.NormalizeApprox();

//		childEndPos		 = childStartPos + childEndPos * (zRandF()*0.3F + 0.3F) * (len/10);
		childEndPos[VX] += (zRand(10)-5);
		childEndPos[VY]	+= (zRand(10)-5);
		childEndPos[VZ] += (zRand(10)-5);

		bolt->Generate_R	(childStartPos, childEndPos, depth+1);
		childList.Insert	(bolt);
	};
}; 

//
//
//

void zCFlash::zCBolt::FreeResources ()
{
	zCPolyStrip::FreeResources();
	for (int i=0; i<childList.GetNum(); i++) 
	{
		childList[i]->FreeResources ();
        zRELEASE(childList[i]);
	};
	childList.DeleteList();
};

//
//
//

zBOOL zCFlash::zCBolt::Render (zTRenderContext& renderContext) 
{
	zCPolyStrip::Render (renderContext);
	for (int i=0; i<childList.GetNum(); i++) 
	{
		zCBolt *strip = childList[i];
		strip->Render (renderContext);
	}
	return TRUE;
};

//
//
//

void zCFlash::SetTexture (const zSTRING& texName)
{
	textureName				= texName;
	rootBolt->SetTexture	( texName );
	splitBolt->SetTexture	( texName );
};

//
//
//

void zCFlash::zCBolt::SetTexture (const zSTRING& texName)
{
	material->SetTexture(zSTRING(texName));

	if(!childList.IsEmpty())
	{
		for( int x = 0; x < childList.GetNum(); x++)
		{
			childList[x]->SetTexture(texName);
		}
	}
};

//
//
//

void zCFlash::zCBolt::InterpolateTo( zCBolt *boltTo, zREAL ipolate )
{
	zBOOL thisHasMore = FALSE;
	zBOOL boltToHasMore = FALSE;
	zBOOL areEqual = FALSE;

	if( boltTo->GetNumAllocSegments() == numSeg ) {
		areEqual = TRUE;
	}
	else if( numSeg > boltTo->GetNumAllocSegments() ) {
		thisHasMore=TRUE;
	}
	else {
		boltToHasMore = TRUE;
	}

	if( areEqual ) 
	{
		for( int x = 0; x < numSeg; x++ ) 
		{
			zVEC3 length = centerPointList[x] - boltTo->GetCenterPointList()[x];
			zVEC3 dir = length.Normalize();

			zVEC3 step = dir*ipolate;

			
			centerPointList[x] +=step;
		} 
	}
}

//
//
//

void zCFlash::zCBolt::Copy( zCBolt *bolt )
{
	for( int x = 0; x < numSeg; x++ ) 
	{
		centerPointList[x] = bolt->GetCenterPointList()[x];
	}
}

//
// 
//

void zCFlash::Update( zREAL aniSpeed )
{
	timeAlive += (ztimer.GetFrameTimeF()/1000);

	if ( ( (ztimer.GetTotalTimeF()-LastUpdateTime) > aniSpeed ) )
	{

		// @TODO: Interpolate from one bolt to another for better animation...
		// @TODO: Build up tree in more than one frame... or make it visible in more then one more frame; through alpha fading for example

		LastUpdateTime=ztimer.GetTotalTimeF();
		Generate( rootBolt, boltStartPos, boltEndPos, boltRoughness );
		
		SetTexture(textureName);
	}
}
 
//
//
//

void zCFlash::Create( zPOINT3 startPos, zPOINT3 endPos, zREAL roughness )
{
	boltStartPos  = startPos;
	boltEndPos    = endPos;
	boltRoughness = roughness;

	Generate( rootBolt, boltStartPos, boltEndPos, boltRoughness );

	SetTexture            ( textureName );
	splitBolt->SetTexture  ( textureName );
/*
	if( startVob ) {	
		zCCamera::activeCam->GetVob()->GetHomeWorld()->RemoveVob(startVob);
		zRELEASE(startVob);
		startVob=NULL;
	}
	else if( startVob == NULL ) {
		 startVob  = zNEW(zCVob);
		 zCDecal *decal = zNEW(zCDecal);
	
		startVob->SetPositionWorld          (startPos);
		startVob->SetVisual					(decal);	  
		startVob->SetShowVisual				(TRUE);
		startVob->SetVobName				("Blitz-Flare-Vob");
		startVob->SetDrawBBox3D				(FALSE);
		startVob->SetSleeping				(FALSE);
		startVob->SetCollDetStat			(FALSE);
		startVob->SetCollDetDyn				(FALSE);

		zCCamera::activeCam->GetVob()->GetHomeWorld()->AddVob(startVob);
	
		decal->SetDecalDim  (200.0f,200.0f);
		decal->SetTexture   (zSTRING("lightning_origin_a0.tga"));
		decal->decalMaterial->SetAlphaBlendFunc(zRND_ALPHA_FUNC_ADD);
		decal->SetDecalOffset(0.0f,0.0f);

		decal->decalMaterial->texAniCtrl.SetAniFPS(12);
		decal->decalMaterial->texAniCtrl.SetOneShotAni(FALSE);
	}*/
}

//
//
//

// =======================================================================================================================
