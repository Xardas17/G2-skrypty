
#include <zCore.h>
#include <z3d.h>
#include <zTypes.h>
#include <zVisual.h>
#include <zMaterial.h>
#include <zCore.h>
#include <z3d.h>
#include <zWorld.h>
#include <zSky.h>
#include <zParticle.h>
#include <zView.h>
#include <zPolyStrip.h>
#include <zVob.h>
#include <oGame.h>
#include <oWorld.h>
#include <ovisfx.h>
#include <zSound.h>

#include <oBarrier.h>

#include <time.h>

#define UV_SCALER			zREAL(1.0F)
#define MAX_BARRIER_OPACITY	int(120)

/* ================================================================================================================ */ 

myThunder::~myThunder()
{
	zRELEASE(polyStrip);
}

/* ================================================================================================================ */ 

oCBarrier::oCBarrier( void )
{
	bFadeInOut							= FALSE;
	fadeState							= 0;
	fadeIn								= TRUE;
	fadeOut								= FALSE;

	thunderStartDecal					= NULL;

	thunderStartDecal					= zNEW(zCDecal);
//	thunderStartDecal->SetTexture		(zSTRING("thunderDecal_a0.tga"));
	thunderStartDecal->SetTexture		(zSTRING("unsun5.tga"));
	thunderStartDecal->SetDecalDim		(4000.0f,4000.0f);
//	thunderStartDecal->SetDecalDim		(50000.0f,50000.0f);
	thunderStartDecal->SetDecalOffset	(0.0f,0.0f);
	thunderStartDecal->decalMaterial->SetAlpha (100);
	thunderStartDecal->decalMaterial->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_ADD);
			
	sfx1								= NULL;
	sfxHandle1							= NULL;
	sfx2								= NULL;
	sfxHandle2							= NULL;
	sfx3								= NULL;
	sfxHandle3							= NULL;
	sfx4								= NULL;
	sfxHandle4							= NULL;

	activeThunder_Sector1				= FALSE;
	activeThunder_Sector2				= FALSE;
	activeThunder_Sector3				= FALSE;
	activeThunder_Sector4				= FALSE;

	/* init random generator */ 
	srand( (unsigned)time( NULL ) );

	myVertList							= NULL;
	myPolyList							= NULL;
	myThunderList						= NULL;
	skySphereMesh						= NULL;
	originalTexUVList					= NULL;	
	bFlashing							= FALSE;
	fFlashTime							= 0.0f;

}

/* ================================================================================================================ */ 

oCBarrier::~oCBarrier()
{
	zRELEASE(skySphereMesh);		skySphereMesh	= NULL;
	delete[] myVertList;			myVertList		= NULL;
	delete[] myPolyList;			myPolyList		= NULL;

	if( myThunderList )
	{
		for( int x = 0; x < 20; x++ ) //numMyThunders; x++ )
		{
			RemoveThunder(&myThunderList[x]);
		}

		numMyThunders=0;

		delete[] myThunderList;
		myThunderList = NULL;
	}

	zRELEASE(thunderStartDecal);	thunderStartDecal = NULL;

	if(sfx1)
	{
		// Destruktor/OnStopDonner
		zsound->StopSound(sfxHandle1);
		zRELEASE(sfx1);
	}

	if(sfx2)
	{
		// Destruktor/OnStopDonner
		zsound->StopSound(sfxHandle2);
		zRELEASE(sfx2);
	}

	if(sfx3)
	{
		// Destruktor/OnStopDonner
		zsound->StopSound(sfxHandle3);
		zRELEASE(sfx3);
	}

	if(sfx4)
	{
		// Destruktor/OnStopDonner
		zsound->StopSound(sfxHandle4);
		zRELEASE(sfx4);
	}

	delete[] originalTexUVList;	originalTexUVList=0;
}

/* ================================================================================================================ */ 


void oCBarrier::Init()
{
	//zCSkyControler_Outdoor * skyOut = zDYNAMIC_CAST<zCSkyControler_Outdoor>(zCSkyControler::GetActiveSkyControler());
	
	//if (skyOut) skySphereMesh = skyOut->GetSkyDomeMesh();

	originalTexUVList	= 0;

	skySphereMesh = zCMesh::Load("magicfrontier_out.3ds",TRUE);

	if (skySphereMesh)
	{
		int startPointsTemp[40];
		int numStartPointsTemp;
		int texUVListCtr	= 0;

		const int numTexUVs				= skySphereMesh->numPoly*3;
		originalTexUVList				= zNEW( zVEC2 [numTexUVs] );
		//const zREAL maxSkyY				= skySphereMesh->GetBBox3D().maxs[VY];
		//const zREAL minSkyY				= skySphereMesh->GetBBox3D().mins[VY];

		for (int i=0; i<skySphereMesh->numPoly; i++) 
		{
			zCPolygon *poly = skySphereMesh->Poly(i);
			
			// es duerfen nur Tris in dem Mesh vorliegen!
			zERR_ASSERT_STRICT (poly->polyNumVert==3);

			for (int j=0; j<poly->polyNumVert; j++) 
			{ 
				//
				originalTexUVList	[texUVListCtr++]	= zVEC2(poly->feature[j]->texu, poly->feature[j]->texv) * UV_SCALER;
				/*

				const zREAL vertY						= poly->vertex[j]->position[VY];

				// Alpha bestimmen, am unteren Rand ausfaden lassen
				int alpha;
				if (vertY>minSkyY)
				{
					// Alpha oben
					alpha								= zFloat2Int (zREAL(255.0F) * (maxSkyY - vertY) / (maxSkyY - minSkyY));
					zClamp								(alpha, 0, 255);
				} else
				{
					// Alpha unten
					const zREAL D						= 8000.0F;
					alpha								= zFloat2Int (zREAL(255.0F) * (vertY / D));
					zClamp								(alpha, 0, 255);
				};

				//
	 			poly->feature[j]->lightStat				= 
				poly->feature[j]->lightDyn				= zCOLOR(255,255,255,alpha);*/
			}
		};
		zERR_ASSERT_STRICT (numTexUVs==texUVListCtr);

		numMyVerts	= skySphereMesh->numVert;
		numMyPolys	= skySphereMesh->numPoly;

		myVertList	= zNEW_ARRAY( myVert, numMyVerts );
		memset		(myVertList,0,(sizeof(myVert)*numMyVerts));

		/* create dependency list */ 
		zBOOL goOn = TRUE;
		for( int x = 0; x <	skySphereMesh->numVert; x++ )
		{
			myVertList[x].vertIndex = x;

			for( int z = 0; z < skySphereMesh->numPoly; z++ )
			{
				int save_index = -1;
				zCPolygon *poly = skySphereMesh->Poly(z);

				for( int f = 0; f < poly->polyNumVert; f++ )
				{
					if( skySphereMesh->Vertex(x) == poly->vertex[f] )
					{
						save_index = f;
					}
				}

				int k = 0;
				if( save_index != -1 )
				{
					for( int h = 0; h < poly->polyNumVert; h++ )
					{
						if( h!=save_index )
						{
							for( k = 0; k < skySphereMesh->numVert; k++ )
							{
								if( skySphereMesh->Vertex(k) == (poly->vertex[h]) )
								{
									int n = 0;
									for( n=0; n < myVertList[x].numNeighbours; n++ )
									{
										if( myVertList[x].vertNeighbours[n] == k )
											goOn=FALSE;
									}

									zBOOL addPolyIndex=TRUE;
									for( int xx = 0; xx < myVertList[x].numPolyIndices; xx++ )
									{
										if( z ==  myVertList[x].polyIndices[xx] )
										{
											addPolyIndex=FALSE;
										}
									}

									if( addPolyIndex ) {
										myVertList[x].polyIndices[myVertList[x].numPolyIndices] = z;
										myVertList[x].numPolyIndices++;
									}
										
									if( goOn )
									{
										myVertList[x].vertNeighbours[myVertList[x].numNeighbours] = k;
										myVertList[x].numNeighbours++;
									}
									goOn=TRUE;
								}								
							}
						}
					}
				}
			}
		}

		/* create thunder start point list */ 
		numStartPoints1	=	0;
		numStartPoints2	=	0;
		numStartPoints3	=	0;
		numStartPoints4	=	0;
		topestPoint		=	0;

//		zREAL height1	= 2000.0f;
//		zREAL height2	= 3000.0f;
		zREAL height2	= 35000.0f;
		int count = 0;
		for( int k = 0; k < numMyVerts; k++ )
		{
//			if( (skySphereMesh->Vertex(k]->position.n[1] >= height1 ) && (skySphereMesh->Vertex(k]->position.n[1] <= height2 ) )
			if( (skySphereMesh->Vertex(k)->position.n[1] > height2 ) ) // && (skySphereMesh->Vertex(k]->position.n[1] <= height2 ) )
			{
				startPointsTemp[count]=k;
				count++;
			}
		}

		numStartPointsTemp=count;

		for( int l = 0; l < numStartPointsTemp; l++ )
		{
			zCVertex* vec = skySphereMesh->Vertex(startPointsTemp[l]);

			if( ( vec->position.n[0] <= -5008.4f ) && ( vec->position.n[2] < -5597.02f ) )
			{
				// sector 1
				startPointList1[numStartPoints1] = startPointsTemp[l];
				numStartPoints1++;
			}

			if( ( vec->position.n[0] > -5008.4f ) && ( vec->position.n[2] <= -5597.02f ) )
			{
				// sector 2
				startPointList2[numStartPoints2] = startPointsTemp[l];
				numStartPoints2++;
			}

			if( ( vec->position.n[0] > -5008.4f ) && ( vec->position.n[2] > -5597.02f ) )
			{
				// sector 3
				startPointList3[numStartPoints3] = startPointsTemp[l];
				numStartPoints3++;
			}

			if( ( vec->position.n[0] < -5008.4f ) && ( vec->position.n[2] > -5597.02f ) )
			{
				// sector 4
				startPointList4[numStartPoints4] = startPointsTemp[l];
				numStartPoints4++;
			}

			if( ( vec->position.n[0] == -5008.4f ) && ( vec->position.n[2] == -5597.02f ) )
			{
				topestPoint = startPointsTemp[l];
			}
		}

		/* basic init for thunder list */ 
		Initialise(20);
	}
	else
	{
		zERR_WARNING("zBarriere - NO SKYSPHERE MESH DETECTED" );
	}

};

void oCBarrier::Initialise( int newNumMaxThunders )
{
	delete[] myThunderList;	myThunderList = NULL;

	myThunderList  = zNEW_ARRAY( myThunder, newNumMaxThunders );
	numMaxThunders = newNumMaxThunders;
	numMyThunders  = 0;

	for( int x = 0; x < numMaxThunders; x++ )
	{
		InitThunder( &myThunderList[x] );
	}
}

/* ================================================================================================================ */ 


static zBOOL showThunders			= TRUE;

static zREAL delayTimeSector1		= 4000.0f;			
static zREAL delayTimeSector2		= 200.0f;
static zREAL delayTimeSector3		= 6000.0f;
static zREAL delayTimeSector4		= 10000.0f;

void oCBarrier::AddTremor (zTRenderContext& renderContext)
{
/*	renderContext.cam->AddTremor	(	renderContext.cam->GetVob()->GetPositionWorld(), 
										(4000.0F*4000.0F), 
										3000.0F, 
										zVEC3(0.8F, 1.5F, 0.8F)
									);*/
};
 
void oCBarrier::RenderLayer (zTRenderContext& rndContext, int layerNumber, zBOOL &addNewThunder)
{
	zTPlane camPlane;
	camPlane.normal			= rndContext.cam->GetVob()->GetAtVectorWorld();
	camPlane.distance		= camPlane.normal * rndContext.cam->GetVob()->GetPositionWorld();

	const zREAL	modifier	= (layerNumber>0) ? 1.5F : 1.0F;
	const zVEC3	p			= zVEC3(0.15F, 0.6F, 1.4F) * (modifier * zREAL(0.7F));
	const zREAL	time		= ztimer.GetTotalTimeF() / 1000.0F;
	zREAL		scrollDelta	= (ztimer.GetTotalTimeF() * zREAL(0.00015F));
	scrollDelta				-= zFloor(scrollDelta);		// damit die UVs im guenstigen Bereich um 0 +/- 1 liegen..

	int			texUVListCtr= 0;
	for( int i = 0; i < skySphereMesh->numPoly; i++ ) 
	{
		zCPolygon *poly		= skySphereMesh->Poly(i);

		// 	if (myPolyList[i].Alpha <= 1)									continue;

		// grobes FrustumCulling
		if (camPlane.GetDistanceToPlane (poly->vertex[0]->position) <0)	
		{
			texUVListCtr	+= 3;
			continue;
		};

		addNewThunder=FALSE;

		for (int j=0; j<poly->polyNumVert; j++) 
		{ 
			{
				const zVEC3& v			= poly->vertex[j]->position;
				zVEC2 texUV				= originalTexUVList	[texUVListCtr];
				texUV[0]				+= (zSin( (v[0]+v[2]) * 0.1f * p[2] + time + p[1]) * p[0]) + modifier + scrollDelta;
				texUV[1]				+= (zSin( (v[1]     ) * 0.1f * p[2] + time + p[1]) * p[0]) + modifier;

	 			poly->feature[j]->texu	= texUV[0];
	 			poly->feature[j]->texv	= texUV[1];

				int alpha				= zFloat2Int (((zSin ((v[0]+v[2]) + time)) + zREAL(1.0F)) * zREAL(0.5F) * zREAL(255.0F));
//				int alpha				= zFloat2Int (((zSin ((-v[1]*0.001F) + time*1.0F)) + zREAL(1.0F)) * zREAL(0.5F) * zREAL(255.0F));
				alpha					= (int(poly->feature[j]->lightStat.GetAlphaByte()) * alpha) >> 8;
				poly->feature[j]->lightDyn.SetAlphaByte (alpha);

				++texUVListCtr;
			};

		};
	};
	skySphereMesh->Render				( rndContext, NULL );
//	skySphereMesh->Render				( rndContext );
};

zBOOL oCBarrier::Render( zTRenderContext& rndContext, zBOOL fadeInOut, zBOOL alwaysVisible=FALSE )
{
	if( skySphereMesh )
	{


//		zBOOL addNewThunder=TRUE;

		/* save old fog state and activate fog */ 
		zBOOL	zBufferWriteEnabled	= zrenderer->GetZBufferWriteEnabled();
		zVALUE	zFarClip			= zCCamera::activeCam->GetFarClipZ();

		{
			zrenderer->SetZBufferWriteEnabled	(FALSE);
			zCCamera::activeCam->SetFarClipZ	(2000000.0F);
		//	rndContext.cam->SetTransform		(zCAM_TRAFO_VIEW, rndContext.cam->GetVob()->trafoObjToWorld.InverseLinTrafo() );
			
			/* render barrier */ 
		//	RenderLayer							(rndContext, 0, addNewThunder);
		//	RenderLayer							(rndContext, 1, addNewThunder);

		//	zrenderer->FlushPolys				();
		};


		if( showThunders )
		{
			int playSound=FALSE;
			zCSkyControler_Outdoor *sky = zDYNAMIC_CAST<zCSkyControler_Outdoor>(zCSkyControler::GetActiveSkyControler());
			zREAL volScale				= sky ? sky->GetEffectVolume() : 1;

			if( !activeThunder_Sector1 )
			{
				if( !zsound->IsSoundActive(sfxHandle1) && (ztimer.GetTotalTimeF()-delayTimeSector1) > 16000 && zRandF()>0.999f)	// 8000 
				{
					int ind					= startPointList1[rand()&(numStartPoints1-1)];
					AddThunder				( ind, 11, 0.0f, zTThunderSector_1 );		
					activeThunder_Sector1	= TRUE;
					delayTimeSector1		= ztimer.GetTotalTimeF();
					playSound=TRUE;

					if(!sfx1) sfx1 = zsound->LoadSoundFXScript("MFX_Barriere_Shoot");// BARRIERE_BLITZ");
					zCSoundSystem::zTSound3DParams sound3DParams;
					sound3DParams.SetDefaults();
					if (zRandF()<0.2f) sound3DParams.volume = 0; else  sound3DParams.volume	  = zRandF()*0.4f;
					sound3DParams.obstruction = zRandF()*0.8f;
					if (sound3DParams.volume>0.2f) playSound = 2;
					sound3DParams.volume	 *= volScale;
					//sound3DParams.isAmbient3D = TRUE;

					AddTremor (rndContext);
					sfxHandle1 = zsound->PlaySound3D( sfx1, zCCamera::activeCam->GetVob(), zSND_SLOT_NONE, &sound3DParams );
				}
			}

			if( !activeThunder_Sector2 )
			{
				if( !zsound->IsSoundActive(sfxHandle2) && (ztimer.GetTotalTimeF()-delayTimeSector2) > 12000 && zRandF()>0.999f) // 6000 
				{
					int ind					= startPointList2[rand()&(numStartPoints2-1)];
					AddThunder				( ind, 11, 0.0f, zTThunderSector_2 );		
					activeThunder_Sector2	= TRUE;
					delayTimeSector2		= ztimer.GetTotalTimeF();
					playSound=TRUE;

					if(!sfx2) sfx2 = zsound->LoadSoundFXScript("MFX_Barriere_Shoot");// BARRIERE_BLITZ");
					zCSoundSystem::zTSound3DParams sound3DParams;
					sound3DParams.SetDefaults();
					if (zRandF()<0.2f) sound3DParams.volume = 0; else  sound3DParams.volume	  = zRandF()*0.4f;
					sound3DParams.obstruction = zRandF()*0.8f;
					if (sound3DParams.volume>0.2f) playSound = 2;
					sound3DParams.volume	 *= volScale;
					//sound3DParams.isAmbient3D = TRUE;
	
					AddTremor (rndContext);
					sfxHandle2 = zsound->PlaySound3D( sfx2, zCCamera::activeCam->GetVob(), zSND_SLOT_NONE, &sound3DParams );

				}
			}

			if( !activeThunder_Sector3 )
			{
				if( !zsound->IsSoundActive(sfxHandle3) && (ztimer.GetTotalTimeF()-delayTimeSector3) > 28000 && zRandF()>0.999f ) // 14000 
				{
					int ind = startPointList3[rand()&(numStartPoints3-1)];
					AddThunder( ind, 11, 0.0f, zTThunderSector_3 );		
					activeThunder_Sector3 = TRUE;
					delayTimeSector3=ztimer.GetTotalTimeF();
					playSound=TRUE;

					if(!sfx3) sfx3 = zsound->LoadSoundFXScript("MFX_Barriere_Shoot");// BARRIERE_BLITZ");

					zCSoundSystem::zTSound3DParams sound3DParams;
					sound3DParams.SetDefaults();
					if (zRandF()<0.2f) sound3DParams.volume = 0; else  sound3DParams.volume	  = zRandF()*0.4f;
					sound3DParams.obstruction = zRandF()*0.8f;
					if (sound3DParams.volume>0.2f) playSound = 2;
					sound3DParams.volume	 *= volScale;

					//	sound3DParams.isAmbient3D = TRUE;
	
					AddTremor (rndContext);
					sfxHandle3 = zsound->PlaySound3D( sfx3, zCCamera::activeCam->GetVob(), zSND_SLOT_NONE, &sound3DParams );
				}
			}

			if( !activeThunder_Sector4 )
			{
				if( !zsound->IsSoundActive(sfxHandle4) && (ztimer.GetTotalTimeF()-delayTimeSector4) > 4000 && zRandF()>0.999f) // 2000 
				{
					if( numStartPoints4 > 0 )
					{
						int ind = startPointList4[rand()&(numStartPoints4-1)];
						AddThunder( ind, 11, 0.0f, zTThunderSector_4 );		
						activeThunder_Sector4 = TRUE;
						delayTimeSector4=ztimer.GetTotalTimeF();
						playSound=TRUE;

						if(!sfx4) sfx4 = zsound->LoadSoundFXScript("MFX_Barriere_Shoot");// BARRIERE_BLITZ");

						zCSoundSystem::zTSound3DParams sound3DParams;
						sound3DParams.SetDefaults();
						if (zRandF()<0.2f) sound3DParams.volume = 0; else  sound3DParams.volume	  = zRandF()*0.4f;
						sound3DParams.obstruction = zRandF()*0.8f;
						if (sound3DParams.volume>0.2f) playSound = 2;
						sound3DParams.volume	 *= volScale;
						//	sound3DParams.isAmbient3D = TRUE;
		
						AddTremor (rndContext);
						sfxHandle4 = zsound->PlaySound3D( sfx4, zCCamera::activeCam->GetVob(), zSND_SLOT_NONE, &sound3DParams );
					}
				}
			}

			/* render valid thunders */ 
			RenderThunderList(rndContext);

			zrenderer->FlushPolys();

			if (playSound)
			{
				// neuer blitz gestartet.
				// mit einer gewissen wahrscheinlichkeit nun den lichteffekt starten
				if ((playSound==2))
				{
					if (!bFlashing)
					{
						bFlashing = TRUE;
						fFlashTime= 250;
					}
				};

			};

			//
			if(sfx1)	zsound->UpdateSound3D(sfxHandle1);
			if(sfx2)	zsound->UpdateSound3D(sfxHandle2);
			if(sfx3)	zsound->UpdateSound3D(sfxHandle3);
			if(sfx4)	zsound->UpdateSound3D(sfxHandle4);

			if (bFlashing)
			{
				zrenderMan.SetHintLightning(TRUE);
				fFlashTime-=ztimer.GetFrameTime();
				if (fFlashTime<100 && zRandF()<0.2f)  
					zrenderMan.SetHintLightning(FALSE);

				if (fFlashTime<=0) bFlashing = FALSE;
			}
			else zrenderMan.SetHintLightning(FALSE);
		}
		else zrenderMan.SetHintLightning(FALSE);

		zrenderer->SetZBufferWriteEnabled	(zBufferWriteEnabled);
		zCCamera::activeCam->SetFarClipZ	(zFarClip);
	}

	return bFadeInOut;
}

/* ================================================================================================================ */ 

void oCBarrier::InitThunder( myThunder* thunder )
{
	thunder->polyStrip  = NULL;
	thunder->sector     = zTThunderSector_None;
	thunder->t0         = 0.0f;
	thunder->t1         = 0.0f;
	thunder->numSplits  = 0;
	thunder->valid      = FALSE;
	thunder->dead       = FALSE;
	thunder->numChilds  = 0;
	thunder->childs     = NULL;
	thunder->dead       = FALSE;
	thunder->isChild    = FALSE;
}

/* =============================================================================================================== */ 

void oCBarrier::RemoveThunder( myThunder* thunder )
{
	zRELEASE( thunder->polyStrip );	thunder->polyStrip = NULL;

	if( thunder->childs )
	{
		for( int x = 0; x < thunder->numChilds; x++ )
		{
			RemoveThunder(&thunder->childs[x]);
		}

		delete[] thunder->childs;
		thunder->childs = NULL;
	}

	InitThunder( thunder );
}

/* =============================================================================================================== */ 

/* =============================================================================================================== */ 

/* =============================================================================================================== */ 


int oCBarrier::AddThunderSub( myThunder* rootThunder, int startIndex, int startNexIntex, int length, int numSplits )
{
	myThunder *thunder = &(rootThunder->childs[rootThunder->numChilds]);

	if( thunder == NULL ) return -1;
	
	if( numSplits > 1 )
		return -1;

	InitThunder(&rootThunder->childs[rootThunder->numChilds]);

	thunder->isChild=TRUE;

	zRELEASE(thunder->polyStrip);
	thunder->polyStrip = zNEW( zCPolyStrip );
	thunder->polyStrip->AllocateResources(length);
	thunder->numSegs=length;

//	int texIndex22 = rand()&(3);
	thunder->polyStrip->material->SetTexture (zSTRING("thunder_a0.tga"));//  L_Philipp[texIndex22]);
	
	thunder->polyStrip->SetCamAlign          ( zCPolyStrip::zCAM_ALIGN_POLY);//STRIP);	
	thunder->polyStrip->SetAlphaFadeSpeed    ( 0.25f                         );	// 0.5
	thunder->polyStrip->SetWidth             ( 1000.0f                      );
	
	thunder->polyStrip->AddSegment( skySphereMesh->Vertex(startIndex)->position    );
	thunder->polyStrip->AddSegment( skySphereMesh->Vertex(startNexIntex)->position );

	int prevIndex = startIndex;
	int neighbourIndices[2];
	neighbourIndices[0]=-1;
	neighbourIndices[1]=-1;
	zREAL maxDist = 0;
	int vertIndex = startNexIntex;

	for( int x = 0; x < length-2; x++ )
	{
		neighbourIndices[0]=-1;
		neighbourIndices[1]=-1;
		maxDist = 0;

		neighbourIndices[0]=startPointList1[0];
		neighbourIndices[1]=startPointList1[0];

		for( int l = 0; l < myVertList[vertIndex].numNeighbours; l++ )
		{
			if( skySphereMesh->Vertex(myVertList[vertIndex].vertNeighbours[l])->position.n[1] < skySphereMesh->Vertex(neighbourIndices[0])->position.n[1] )
			{
				neighbourIndices[1] = neighbourIndices[0];
				neighbourIndices[0] = myVertList[vertIndex].vertNeighbours[l];
			}
			else if( skySphereMesh->Vertex(myVertList[vertIndex].vertNeighbours[l])->position.n[1] < skySphereMesh->Vertex(neighbourIndices[1])->position.n[1] )
			{
				neighbourIndices[1] = myVertList[vertIndex].vertNeighbours[l];;	
			}
		}
		
		int t = rand()&1;
		int neighbourIndex = neighbourIndices[t]; 

		zVEC3 midPoint = zVEC3( -5008.4f, -10500.0f, -5597.02f );
		zVEC3 vec1 = midPoint-(skySphereMesh->Vertex(neighbourIndex)->position);
		vec1.Normalize();

		zPOINT3 addSeg = (skySphereMesh->Vertex(neighbourIndex)->position)+(vec1*4000);

		//zPOINT3 addSeg = skySphereMesh->Vertex(neighbourIndex]->position;
//		addSeg.n[1] -= 1000.0f;

		thunder->polyStrip->AddSegment(addSeg);

		thunder->valid = TRUE;
		thunder->numChilds=0;
		
		prevIndex = vertIndex;
		vertIndex = neighbourIndex;
	}

	thunder->valid = TRUE;

	return 11;
}

/* =============================================================================================================== */ 

int oCBarrier::AddThunder( int startIndex, int length, zREAL random, zTThunderSector sector )
{
	int thunderIndex = -1;

	for( int y = 0; y < numMaxThunders; y++ )
	{
		if( !(myThunderList[y].valid) )
		{
			thunderIndex=y;
			break;
		}
	}

	if( thunderIndex == -1 )
		return -1;

	if( myThunderList[thunderIndex].polyStrip ) {
		RemoveThunder(&myThunderList[thunderIndex]);
	}

	InitThunder(&myThunderList[thunderIndex]);

	myThunderList[thunderIndex].numSegs   = length;
	myThunderList[thunderIndex].isChild   = FALSE;
	myThunderList[thunderIndex].sector    = sector;
	myThunderList[thunderIndex].polyStrip = zNEW( zCPolyStrip );
	myThunderList[thunderIndex].polyStrip->AllocateResources(length);

//	int texIndex22 = rand()&(3);
	myThunderList[thunderIndex].polyStrip->material->SetTexture (zSTRING("thunder_a0.tga"));//  L_Philipp[texIndex22]);

	myThunderList[thunderIndex].polyStrip->SetCamAlign(zCPolyStrip::zCAM_ALIGN_POLY);//STRIP);
	myThunderList[thunderIndex].polyStrip->SetAlphaFadeSpeed(0.25f);		// 0.5
	myThunderList[thunderIndex].polyStrip->SetWidth(1000.0f);	// 3000
	
	myThunderList[thunderIndex].polyStrip->AddSegment( skySphereMesh->Vertex(startIndex)->position );

	
	zVEC3 midPoint = zVEC3( -5008.4f, -10500.0f, -5597.02f );
	zVEC3 vec1 = midPoint-(skySphereMesh->Vertex(startIndex)->position);
	vec1.Normalize();
	zVEC3 oVec = (skySphereMesh->Vertex(startIndex)->position)+(vec1*4000);

	myThunderList[thunderIndex].originVec = oVec;

	int prevIndex = startIndex;
	int neighbourIndices[2];
	neighbourIndices[0]=-1;
	neighbourIndices[1]=-1;
	zREAL maxDist = 0;
	int vertIndex = startIndex;

	for( int x = 0; x < length-1; x++ )
	{
		neighbourIndices[0]=startPointList1[0];
		neighbourIndices[1]=startPointList1[0];
		maxDist = 0;

		if( x == 0 )
		{	

			int savedIndex2 = startPointList1[0];
			for( int l = 0; l < myVertList[vertIndex].numNeighbours; l++ )
			{
				if( skySphereMesh->Vertex(myVertList[vertIndex].vertNeighbours[l])->position.n[1] < skySphereMesh->Vertex(savedIndex2)->position.n[1] )
				{
					savedIndex2 = myVertList[vertIndex].vertNeighbours[l];
				}

				neighbourIndices[0] = savedIndex2;
				neighbourIndices[1] = neighbourIndices[0];
			}
		}
		else
		{
			neighbourIndices[0]=startPointList1[0];
			neighbourIndices[1]=startPointList1[0];

			for( int l = 0; l < myVertList[vertIndex].numNeighbours; l++ )
			{
				if( skySphereMesh->Vertex(myVertList[vertIndex].vertNeighbours[l])->position.n[1] < skySphereMesh->Vertex(neighbourIndices[0])->position.n[1] )
				{
					neighbourIndices[1] = neighbourIndices[0];
					neighbourIndices[0] = myVertList[vertIndex].vertNeighbours[l];
				}
				else if( skySphereMesh->Vertex(myVertList[vertIndex].vertNeighbours[l])->position.n[1] < skySphereMesh->Vertex(neighbourIndices[1])->position.n[1] )
				{
					neighbourIndices[1] = myVertList[vertIndex].vertNeighbours[l];;	
				}
			}
		}
		
		int t = rand()&1;
		int neighbourIndex = neighbourIndices[t]; 

		if( neighbourIndices[0] != neighbourIndices[1] )
		{
			int randomBool = rand()&3;

			if( ( randomBool == 0 ) && ( myThunderList[thunderIndex].numChilds<3 ) )
			{
				if( myThunderList[thunderIndex].childs == NULL )
				{
					myThunderList[thunderIndex].childs = zNEW_ARRAY(myThunder,3);
					InitThunder( &myThunderList[thunderIndex].childs[0]);
					InitThunder( &myThunderList[thunderIndex].childs[1]);
					InitThunder( &myThunderList[thunderIndex].childs[2]);
//					InitThunder( &myThunderList[thunderIndex].childs[3]);
//					InitThunder( &myThunderList[thunderIndex].childs[4]);
				}

				zREAL startTime =  ((1.0f/(myThunderList[thunderIndex].numSegs))*(x));
				int startIndex =  prevIndex;
				int nextIndex = -1;

				if( t == 0 )
					nextIndex = neighbourIndices[1];	
				else
					nextIndex = neighbourIndices[0];

				myThunderList[thunderIndex].childs[myThunderList[thunderIndex].numChilds].t0=0.0f;
				myThunderList[thunderIndex].childs[myThunderList[thunderIndex].numChilds].t1=0.0f;

				int numSplits = myThunderList[thunderIndex].childs[myThunderList[thunderIndex].numChilds].numSplits = myThunderList[thunderIndex].numSplits+1;				
				int rV = AddThunderSub( &(myThunderList[thunderIndex]), startIndex, nextIndex, 11, numSplits );						

				if( rV != -1 )
				{
					myThunderList[thunderIndex].startTime[myThunderList[thunderIndex].numChilds] = startTime;
					myThunderList[thunderIndex].numChilds++;
				}
			}
		}

//		zPOINT3 addSeg = skySphereMesh->Vertex(neighbourIndex]->position;

		zVEC3 midPoint = zVEC3( -5008.4f, -10500.0f, -5597.02f );
		zVEC3 vec1 = midPoint-(skySphereMesh->Vertex(neighbourIndex)->position);
		vec1.Normalize();

		zPOINT3 addSeg = (skySphereMesh->Vertex(neighbourIndex)->position)+(vec1*4000);

		myThunderList[thunderIndex].polyStrip->AddSegment(addSeg);
		myThunderList[thunderIndex].valid = TRUE;
		prevIndex = vertIndex;
		vertIndex = neighbourIndex;
	}

	myThunderList[thunderIndex].valid = TRUE;

	numMyThunders++;

	return thunderIndex;
}

/* =============================================================================================================== */ 

/* =============================================================================================================== */ 

zBOOL oCBarrier::RenderThunder( myThunder* thunder, zTRenderContext& rndContext )
{
	if( thunder->valid ) 
	{

	//	if( thunder->t1 >= 0.90f )
	//		thunder->t0 = 0.90f;//  += ztimer.GetFrameTimeF() / 500.0F;

		thunder->t1 += ztimer.GetFrameTimeF() / 200.0F;		

		const zREAL lowerBound = 0.90f;

		if( thunder->t0 >= lowerBound ) thunder->t0 = lowerBound;
		if( thunder->t1 >= lowerBound ) thunder->t1 = lowerBound;

		if( thunder->polyStrip->GetNumVisibleSegments() <= 2 )
			thunder->t0 = lowerBound;	

		if( ( thunder->t0 >= lowerBound ) && ( thunder->t1 >= lowerBound ) && ( thunder->numChilds<=0) ) 
		{
			if( !thunder->isChild )
			{
				if( thunder->sector == zTThunderSector_1 )
					activeThunder_Sector1=FALSE;

				if( thunder->sector == zTThunderSector_2 )
					activeThunder_Sector2=FALSE;

				if( thunder->sector == zTThunderSector_3 )
					activeThunder_Sector3=FALSE;

				if( thunder->sector == zTThunderSector_4 )
					activeThunder_Sector4=FALSE;

				numMyThunders--;
			}

			RemoveThunder(thunder);
			thunder->valid=FALSE;
			return FALSE;
		}

		if( ( thunder->t0 != thunder->t1 ) )
		{
			thunder->polyStrip->SetVisibleSegments( thunder->t0, thunder->t1 );
			thunder->polyStrip->SetHeightCheckEnabled(TRUE);
			thunder->polyStrip->SetHeightBound(-2000.0f);
			thunder->polyStrip->Render( rndContext );
		}

	 	for( int x = 0; x < thunder->numChilds; x++ )
		{
			if( thunder->startTime[x] <= (thunder->t1) )
			{
				zBOOL alive = RenderThunder( &(thunder->childs[x]), rndContext );

				if( alive == FALSE )
				{					
					thunder->numChilds--;
				}
			}
		}

		if( !thunder->isChild )
		{
			zMATRIX4 matTemp;
			zMATRIX4 matTemp2;
			zMATRIX4 mat;
			matTemp.MakeIdentity();
			mat.MakeIdentity();
			
			mat = rndContext.cam->GetTransform( zCAM_TRAFO_VIEW );

			mat.v[0].n[2] *= -1;
			mat.v[1].n[2] *= -1;
			mat.v[2].n[2] *= -1;

			mat.v[0].n[3] = thunder->originVec.n[0];
			mat.v[1].n[3] = thunder->originVec.n[1];
			mat.v[2].n[3] = thunder->originVec.n[2];

			matTemp2 = rndContext.cam->GetTransform( zCAM_TRAFO_WORLD );

			rndContext.cam->SetTransform( zCAM_TRAFO_WORLD, mat );

			//thunderStartDecal->decalMaterial->SetAlpha(thunder->polyStrip->GetGlobalAlpha());
			thunderStartDecal->Render(rndContext);
			
			rndContext.cam->SetTransform( zCAM_TRAFO_WORLD, matTemp2 );
		}

		return TRUE;
	}

	return FALSE;
}

/* =============================================================================================================== */ 

void oCBarrier::RenderThunderList( zTRenderContext& rndContext )
{
	for( int x = 0; x < numMaxThunders; x++ ) 
	{
		RenderThunder( &myThunderList[x], rndContext );
	}
}

/* =============================================================================================================== */ 
/*
void oCBarrier::SetAlphaRecursive ( int index, int addAlpha, int rec_step, int max_rec )
{
	if( rec_step>max_rec)
		return;

	for( int m = 0; m < myVertList[index].numPolyIndices; m++ )
	{
		zCPolygon *poly = skySphereMesh->Poly(myVertList[index].polyIndices[m]);

		myPolyList[myVertList[index].polyIndices[m]].Alpha += addAlpha;
				
		zCOLOR col(255,255,255,myPolyList[myVertList[index].polyIndices[m]].Alpha);
		for (int j=0; j<poly->polyNumVert; j++) 
		{ 
			zVEC3 lightRay = zVEC3(1,1,0);
			lightRay.Normalize();

			zREAL dot = poly->GetNormal() * lightRay * 255.0F;
			if( dot < 0.0f )
			{
				dot *= (-1.0f);
			}

			if (dot>255.0F) dot=255.0F;
			col.SetRGB (zVEC3(dot,dot,dot));
			
			poly->feature[j]->lightStat	= col;
			poly->feature[j]->lightDyn	= col;
		};
	}

	rec_step++;

	for( int x = 0; x < myVertList[index].numNeighbours; x++ )
	{
		SetAlphaRecursive( myVertList[index].vertNeighbours[x], addAlpha/rec_step, rec_step, max_rec );
	}
}*/

/* =============================================================================================================== */ 
/* =============================================================================================================== */ 
/* =============================================================================================================== */ 


oCSkyControler_Barrier::oCSkyControler_Barrier() : zCSkyControler_Outdoor(TRUE)
{
	barrier		= zNEW(oCBarrier);
	bFadeInOut	= TRUE;
}

/* =============================================================================================================== */ 

oCSkyControler_Barrier::~oCSkyControler_Barrier()
{
	delete barrier;
	barrier = NULL;
}

/* =============================================================================================================== */ 

// FIXME: 'nextActivation' sollte eigentlich Member der Klasse oCSkyControler_Barrier und persistent sein. Es ist
//		  derzeit ein wenig unschoen, dass bei jedem Neustart von Gothic und dem Laden eines SaveGames immer zuerst
//		  die Barriere erscheint (andererseits will man natuerlich aber auch, dass direkt zu Spielstart, bei dem Dialog
//		  mit Diego die Barriere sichtbar ist).
//		  Persistent machen ist derzeit (v108) nicht moeglich, da wegen zCObjectBug (falsche ClassCheckSum Berechnung)
//		  keine zCLASS_xxx hinzugefuegt werden koennen.
static zREAL nextActivation	= 8000;	// msec,	8 Sekunden Startverzoegerung

#include "zinput.h"

void oCSkyControler_Barrier::RenderSkyPre()
{
	zCSkyControler_Outdoor::RenderSkyPre();

	// Dieser Effekt ist per Options-Menu abschaltbar
	// [EDENFELD] Magische Barriere Effekte für 1.09 bzw. Gothic 2 deaktiviert

	static zBOOL meshLoaded = FALSE;

	if (!meshLoaded) 
	{
		meshLoaded = TRUE;
		barrier->Init();
	}

	if ( zCSkyControler_Outdoor *sky = zDYNAMIC_CAST<zCSkyControler_Outdoor>(zCSkyControler::GetActiveSkyControler()) )
	{
		if (GetSkyEffectsEnabled() && sky->GetRainFXWeight()>0.5F && sky->GetRenderLightning() && sky->GetWeatherType()!=zTWEATHER_SNOW)
		{
			zTRenderContext			renderContext;
			renderContext.Clear		();
			renderContext.cam		= zCCamera::activeCam;
			renderContext.world     = zCCamera::activeCam->GetVob()->GetHomeWorld();
			renderContext.vob       = zCCamera::activeCam->GetVob();

			barrier->Render( renderContext, FALSE, FALSE );
		}
		else zrenderMan.SetHintLightning(FALSE);
	}

#if 0

	// alter gothic 1 code

	if (GetSkyEffectsEnabled())
	{
		nextActivation				-= ztimer.GetFrameTimeF();
		if (nextActivation<0)
		{
			// derzeit: 1 Spieltag	= 1h Realzeit
			// 1 Stunde im Spiel	= 250 secs Realzeit
			// 	(24.0 * 250000.0)	= 6000000 msec	(ein Spieltag)
			// 	.. / 3				= 1200000		(ca. 3x am Tag, alle 20min Realzeit)
			
			nextActivation			= zREAL(1200000.0F) + 
									  (zRandF() * zREAL((5.0F /* minute*/ * 60.0F * 1000.0F)));	// .. 3x pro Spieltag, 5min Varianz
	//		nextActivation			= zREAL(60000.0F);	// .. jede Real-Minute
			bFadeInOut				= TRUE;
		};

		if (bFadeInOut)
		{
			zTRenderContext			renderContext;
			renderContext.Clear		();
			renderContext.cam		= zCCamera::activeCam;
			renderContext.world     = zCCamera::activeCam->GetVob()->GetHomeWorld();
			renderContext.vob       = zCCamera::activeCam->GetVob();

			zBOOL isFading			= barrier->Render( renderContext, bFadeInOut, FALSE );

			if (!isFading) {
				bFadeInOut = FALSE;
			}
		}
	};
#endif
}


/* =============================================================================================================== */ 