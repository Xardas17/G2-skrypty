/******************************************************************************** 
 
     $Workfile:: zViewBase.cpp        $                $Date:: 9.01.01 13:21    $
     $Revision:: 12                   $             $Modtime:: 9.01.01 13:19    $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewBase.cpp $
 * 
 * 12    9.01.01 13:21 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 11    19.10.00 19:16 Keskenti
 * 
 * 10    19.10.00 18:54 Keskenti
 * 
 * 8     19.10.00 18:27 Keskenti
 * 
 * 7     19.10.00 17:15 Keskenti
 * 
 * 6     17.10.00 22:38 Keskenti
 * 
 * 5     16.10.00 19:34 Keskenti
 * 
 * 4     16.10.00 18:59 Keskenti
 * 
 * 3     16.10.00 18:27 Keskenti
 * 
 * 2     13.10.00 21:35 Keskenti
 * 
 *********************************************************************************/

#include <zCore.h>
#include <zTypes.h>
#include <z3d.h>
#include <zList.h>

#include <zViewBase.h>

//
//---------------------------------------------------------------------------------
//*******************************     CONSTANTS     *******************************
//---------------------------------------------------------------------------------
//

const zUINT16 zCViewBase::ViewVirtualWidth  = 8192;
const zUINT16 zCViewBase::ViewVirtualHeight = 8192;

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
zCViewBase::zCViewBase()
{
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewBase::~zCViewBase()
{
}

// Utility - intended to fill the z-buffer with proper value
// to make sure the 3D objects in the view (HUD) are rendered
// in front of the world ( mainly for the inventory/trdaing )
// [EDENFELD]	initial implementation
// [BENDLIN]	moved from oCItem::RenderItem to zCViewBase
void zCViewBase::FillZBuffer( void )
{
	static zCTexture *BackgroundTexture = NULL;
	if ( !BackgroundTexture )
		BackgroundTexture = zCTexture::Load(zSTRING("default.tga"));

	int	Left, Top, Width, Height;
	this->GetViewport(Left, Top, Width, Height);
	
	zPOINT2	TopLeft = zVEC2(float(Left), float(Top));
	zPOINT2	BottomRight = zVEC2(float(Left + Width), float(Top + Height));

	zTRnd_ZBufferCmp		OldZBufferCompare	= ::zrenderer->GetZBufferCompare();
	zTRnd_AlphaBlendSource	OldAlphaBlendSource	= ::zrenderer->GetAlphaBlendSource();
	zTRnd_AlphaBlendFunc	OldAlphaBlendFunc	= ::zrenderer->GetAlphaBlendFunc();
	zREAL					OldAlphaBlendFactor	= ::zrenderer->GetAlphaBlendFactor();
	zBOOL					OldZBufferWrite		= ::zrenderer->GetZBufferWriteEnabled();
	{
		// z werte werden immer geschrieben
		::zrenderer->SetZBufferCompare		(zRND_ZBUFFER_CMP_ALWAYS);
		::zrenderer->SetZBufferWriteEnabled	(TRUE);

		// keine pixel kommen durch
		::zrenderer->SetAlphaBlendFunc		(zRND_ALPHA_FUNC_BLEND);
		::zrenderer->SetAlphaBlendSource	(zRND_ALPHA_SOURCE_CONSTANT);
		::zrenderer->SetAlphaBlendFactor	(0);

		zrenderer->DrawTile(BackgroundTexture, TopLeft, BottomRight, zCCamera::activeCam ? zCCamera::activeCam->GetFarClipZ()-1 : 65534, zVEC2(0.0f, 0.0f), zVEC2(1.0f, 1.0f), zCOLOR(0, 0, 0, 0));
	}
	::zrenderer->SetZBufferCompare		(OldZBufferCompare);
	::zrenderer->SetZBufferWriteEnabled	(OldZBufferWrite);
	::zrenderer->SetAlphaBlendSource	(OldAlphaBlendSource);
	::zrenderer->SetAlphaBlendFactor	(OldAlphaBlendFactor);
	::zrenderer->SetAlphaBlendFunc		(OldAlphaBlendFunc);
}

