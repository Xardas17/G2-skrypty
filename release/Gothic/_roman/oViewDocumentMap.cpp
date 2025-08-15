/******************************************************************************** 
 
     $Workfile:: oViewDocumentMap.cp $                $Date:: 13.02.01 11:38   $
     $Revision:: 8                    $             $Modtime:: 13.02.01 9:26    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDocumentMap.cpp $
 * 
 * 8     13.02.01 11:38 Moos
 * Warnung beseitigt
 * 
 * 7     16.01.01 17:22 Keskenti
 * 
 * 6     9.01.01 13:21 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 5     1.12.00 15:17 Keskenti
 * 
 * 4     24.11.00 13:47 Keskenti
 * 
 * 3     17.11.00 17:44 Keskenti
 * 
 * 2     25.10.00 17:45 Keskenti
 * 
 * 1     24.10.00 21:17 Keskenti
 * 
 * 5     24.10.00 20:54 Keskenti
 * 
 * 4     23.10.00 23:27 Keskenti
 * 
 * 3     21.10.00 1:14 Keskenti
 * 
 * 2     20.10.00 17:54 Keskenti
 * 
 * 1     20.10.00 17:38 Keskenti
 * 
 * 1     20.10.00 16:27 Keskenti
 * 
 * 3     19.10.00 19:14 Keskenti
 * 
 * 2     19.10.00 17:15 Keskenti
 * 
 * 1     19.10.00 15:25 Keskenti
 * 
 * 1     19.10.00 15:20 Keskenti
 * 
 * 3     18.10.00 1:08 Keskenti
 * 
 * 2     18.10.00 0:49 Keskenti
 * 
 * 1     18.10.00 0:48 Keskenti
 * 
 *********************************************************************************/

#include <zIncDialogs.h>
#include <oViewDocument.h>
#include <oViewDocumentMap.h>
#include <zInput_Win32.h>
#include <oGame.h>
#include <oNpc.h>
#include <oWorld.h>

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCViewDocumentMap::oCViewDocumentMap()
{
	this->ViewPageMap	= NULL;
	this->Level			= "INVALID.ZEN";
	this->LevelCoords[VX] = this->LevelCoords[VY] = this->LevelCoords[VZ] = this->LevelCoords[VW] = 0.0f;
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
oCViewDocumentMap::~oCViewDocumentMap()
{
}

//*********************************************************************************
//**																	    SetPage
//*********************************************************************************
//**
//*********************************************************************************
oCViewDocument* oCViewDocumentMap::SetPage( int nPage, zSTRING& strTexture, zBOOL bScale )
{
	oCViewDocument* pViewDoc = oCViewDocument::SetPage( nPage, strTexture, bScale );
	if ( nPage != 0 ) return pViewDoc;											

	//
	//	ARROW WILL ALWAYS BE PLACED ON FIRST PAGE
	//
	this->ViewArrow.Init(	pViewDoc						, 
							TRUE							,
							zCViewFX::zEViewFX::VIEW_FX_NONE, 
							zCViewFX::zEViewFX::VIEW_FX_NONE, 
							1.0f							, 
							1.0f							, 
							zSTRING( "" )	
						);


	return ( this->ViewPageMap = pViewDoc );
}

//*********************************************************************************
//**																	   SetLevel
//*********************************************************************************

void oCViewDocumentMap::SetLevel( const zSTRING& strLevel )
{
	this->Level = strLevel;
	this->Level.Upper();
}

//*********************************************************************************
//**																 SetLevelCoords
//*********************************************************************************

void oCViewDocumentMap::SetLevelCoords( int left, int top, int right, int bottom )
{
	this->LevelCoords[VX] = zREAL(left);
	this->LevelCoords[VY] = zREAL(top);
	this->LevelCoords[VZ] = zREAL(right);
	this->LevelCoords[VW] = zREAL(bottom);
}

//
//---------------------------------------------------------------------------------
//******************************     POSITIONING     ******************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																 UpdatePosition
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDocumentMap::UpdatePosition( void )
{
	oCWorld* pGameWorld = dynamic_cast<oCWorld*> (::ogame->GetWorld());	

	if ( ! this->ViewPageMap							 )	return;
	if ( ! pGameWorld									 )	return;
	if (   pGameWorld->GetWorldFilename() != this->Level ) 
	{ 
		this->ViewArrow.Close();
		return;
	}
	else
		this->ViewArrow.Open ();

	//
	//	GET INSTANCES
	//
	oCNpc*		pPlayer				 = ::ogame->GetSelfPlayerVob	();	if ( ! pPlayer	) return;
	zCWorld*	pWorld				 = pPlayer->GetHomeWorld		();	if ( ! pWorld	) return;
									
	//								
	//	GET 3D COORDS				
	//								
	zPOINT3		ptPlayer			 = pPlayer->GetPositionWorld	();
	
	//								
	//	GET 2D COORDS				
	//								
	zPOS		ptMapMin			 = this->ViewPageMap->GetPixelPosition	();
	zPOS		ptMapMax			 = this->ViewPageMap->GetPixelSize		();	
				ptMapMax		    += ptMapMin;

	//
	//	CALC 2D POSITION
	//

	zVEC2		vecWorldMin;  // left, bottom
	zVEC2		vecWorldMax;  // right, top
	if ( (this->LevelCoords[VX] == 0.0f) && (this->LevelCoords[VY] == 0.0f) &&
		 (this->LevelCoords[VZ] == 0.0f) && (this->LevelCoords[VW] == 0.0f)	   )
	{
		// old style (obsolete) - get bounds from static level mesh
		zTBBox3D boxWorld = pWorld ->GetBBox3DWorldStatic();

		vecWorldMin[VX] = boxWorld.mins[VX];  // left
		vecWorldMin[VY] = boxWorld.mins[VZ];  // bottom
		vecWorldMax[VX] = boxWorld.maxs[VX];  // right
		vecWorldMax[VY] = boxWorld.maxs[VZ];  // top
	}
	else
	{
		// previously set level coordinates
		vecWorldMin[VX] = this->LevelCoords[VX];  // left
		vecWorldMin[VY] = this->LevelCoords[VW];  // bottom
		vecWorldMax[VX] = this->LevelCoords[VZ];  // right
		vecWorldMax[VY] = this->LevelCoords[VY];  // top
	}

	zVEC2		vecMapMin			( (zREAL) ptMapMin.X	, (zREAL) ptMapMin.Y	);
	zVEC2		vecMapMax			( (zREAL) ptMapMax.X	, (zREAL) ptMapMax.Y	);

	zVEC2		vecMapDir			 = vecMapMax	- vecMapMin  ;
	zVEC2		vecWorldDir			 = vecWorldMax	- vecWorldMin;
	zVEC2		vecWorldToMap		 = vecMapDir;
				vecWorldToMap[ VX ] /= vecWorldDir[ VX ];
				vecWorldToMap[ VY ] /= vecWorldDir[ VY ];

	zVEC2		vecWorldPlayer		( ptPlayer[ VX ], ptPlayer[ VZ ] );
	zVEC2		vecMapPlayer		=   vecWorldPlayer - vecWorldMin;
				vecMapPlayer [ VX ]	*=  vecWorldToMap	[ VX ]; 
				vecMapPlayer [ VY ]	*=  vecWorldToMap	[ VY ]; 
				
				vecMapPlayer[VY]	=	vecMapDir[VY] - vecMapPlayer[VY];
				vecMapPlayer		+=	vecMapMin;

	zPOS		ptArrowSize			 = this->ViewArrow.GetPixelSize();
	zPOS		ptArrowPosition		 = zPOS( (int) vecMapPlayer[ VX ], (int) vecMapPlayer[ VY ] );
				ptArrowPosition.X	-= ptArrowSize.X / 2;
				ptArrowPosition.Y	-= ptArrowSize.X / 2;

	//
	//	CALC HEADING
	//
	zPOINT3		vecLookAt		 = pPlayer->GetAtVectorWorld();
	zVEC3		vecNorth		 = pPlayer->GetPositionWorld() + zVEC3( 0, 0, 1 ); 

	zREAL		fAzimuth	, 
				fElevation	;

	pPlayer->GetAngles( vecNorth, fAzimuth, fElevation );

	//
	//	CREATE HEADING STRING
	//
	zEHeading enuHeading = HEADING_NORTH;

	zREAL fDisplacement		=   45.0f * 0.5f;
	zREAL fBearingNorth		=    0.0f;
	zREAL fBearingNorthWest =   45.0f;
	zREAL fBearingWest		=   90.0f;
	zREAL fBearingSouthWest	=  135.0f;
//	zREAL fBearingSouth		=  180.0f;
	zREAL fBearingSouthEast	= -135.0f;
	zREAL fBearingEast		= - 90.0f;
	zREAL fBearingNorthEast = - 45.0f;

			if (	( fAzimuth  > fBearingNorth		- fDisplacement ) 
				&&	( fAzimuth <= fBearingNorth		+ fDisplacement )	)	enuHeading = HEADING_NORTH;

	else	if (	( fAzimuth  > fBearingNorthEast - fDisplacement ) 
				&&	( fAzimuth <= fBearingNorthEast + fDisplacement )	)	enuHeading = HEADING_NORTHEAST;

	else	if (	( fAzimuth  > fBearingEast		- fDisplacement ) 
				&&	( fAzimuth <= fBearingEast		+ fDisplacement )	)	enuHeading = HEADING_EAST;

	else	if (	( fAzimuth  > fBearingSouthEast - fDisplacement ) 
				&&	( fAzimuth <= fBearingSouthEast + fDisplacement )	)	enuHeading = HEADING_SOUTHEAST;

	else	if (	( fAzimuth  > fBearingSouthWest - fDisplacement ) 
				&&	( fAzimuth <= fBearingSouthWest + fDisplacement )	)	enuHeading = HEADING_SOUTHWEST;

	else	if (	( fAzimuth  > fBearingWest		- fDisplacement ) 
				&&	( fAzimuth <= fBearingWest		+ fDisplacement )	)	enuHeading = HEADING_WEST;

	else	if (	( fAzimuth  > fBearingNorthWest - fDisplacement ) 
				&&	( fAzimuth <= fBearingNorthWest + fDisplacement )	)	enuHeading = HEADING_NORTHWEST;

	else																	enuHeading = HEADING_SOUTH;

	zSTRING strHeading;

	switch( enuHeading )
	{
		case HEADING_NORTH		:	strHeading = "O"	;	break;
		case HEADING_NORTHEAST	:	strHeading = "RO"	;	break;
		case HEADING_EAST		:	strHeading = "R"	;	break;
		case HEADING_SOUTHEAST	:	strHeading = "RU"	;	break;
		case HEADING_SOUTH		:	strHeading = "U"	;	break;
		case HEADING_SOUTHWEST	:	strHeading = "LU"	;	break;
		case HEADING_WEST		:	strHeading = "L"	;	break;
		case HEADING_NORTHWEST	:	strHeading = "LO"	;	break;
	}

	strHeading += ".TGA";

	//
	//	UPDATE CHILD VIEW
	//
	this->ViewArrow.SetTexture		( strHeading, FALSE );
	this->ViewArrow.SetPixelPosition( ptArrowPosition	);
}
