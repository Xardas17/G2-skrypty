/******************************************************************************** 
 
     $Workfile:: zViewObject.cpp      $                $Date:: 11.01.01 21:09   $
     $Revision:: 9                    $             $Modtime:: 11.01.01 20:56   $
       $Author:: Hildebrandt                                                    $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/zengin_work/_Roman/zViewObject.cpp $
 * 
 * 9     11.01.01 21:09 Hildebrandt
 * 
 * 8     9.01.01 13:21 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 7     28.11.00 12:37 Keskenti
 * 
 * 6     23.10.00 23:27 Keskenti
 * 
 * 5     19.10.00 18:54 Keskenti
 * 
 * 4     19.10.00 18:27 Keskenti
 * 
 * 3     19.10.00 17:48 Keskenti
 * 
 * 2     19.10.00 17:15 Keskenti
 * 
 * 1     19.10.00 16:32 Keskenti
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
#include <zViewObject.h>
#include <zView.h>

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

zCLASS_DEFINITION ( zCViewObject, zCObject, 0 ,0 )

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewObject::zCViewObject()
{
	this->ID				= 0;

	this->VirtualPosition	= zPOS( 0l, 0l );
	this->VirtualSize		= zPOS( 0l, 0l );
	this->PixelPosition		= zPOS( 0l, 0l );
	this->PixelSize			= zPOS( 0l, 0l );

	this->ViewParent		= NULL;
	this->ListChildren		.SetCompare( zCViewObject::Compare );
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewObject::~zCViewObject()
{
	this->RemoveAllChildren();
}

//
//---------------------------------------------------------------------------------
//*******************************     HIERARCHY     *******************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																	   AddChild
//*********************************************************************************
//**
//*********************************************************************************
void zCViewObject::AddChild( zCViewObject* pView )
{
	if ( pView ) this->AddChild( *pView );
}

//*********************************************************************************
//**																	   AddChild
//*********************************************************************************
//**
//*********************************************************************************
void zCViewObject::AddChild( zCViewObject& view )
{
	this->ListChildren.InsertSort( &view );
	view.SetParent( this );															// i'm the child's parent
	view.AddRef();																	// i did not create it 
}

//*********************************************************************************
//**																	AddChildren
//*********************************************************************************
//**
//*********************************************************************************
void zCViewObject::AddChildren( zCListViewObject& listChildren )	
{
	int		nViews =	listChildren.GetNumInList();
	while(  nViews )	this->AddChild( listChildren[ --nViews ] );
}

//*********************************************************************************
//**																	RemoveChild
//*********************************************************************************
//**
//*********************************************************************************
void zCViewObject::RemoveChild( zCViewObject* pView )
{
	if ( pView )
	{
		this->ListChildren.Remove( pView );
		pView->SetParent( NULL );													// i'm no longer its parent
		zRELEASE( pView );
	}
}

//*********************************************************************************
//**																	RemoveChild
//*********************************************************************************
//**
//*********************************************************************************
void zCViewObject::RemoveChild( zCViewObject& view )
{
	this->RemoveChild( &view );
}

//*********************************************************************************
//**															  RemoveAllChildren
//*********************************************************************************
//**
//*********************************************************************************
void zCViewObject::RemoveAllChildren( void )
{
	//
	//	RELEASE CHILDREN
	//
	zCViewObject*	pView	= NULL;
	int				nViews	= this->ListChildren.GetNumInList();

	while( nViews )
	{
		pView = this->ListChildren[ --nViews ];
		this->RemoveChild( pView );
	}

	//
	//	CLEAR LIST
	//
	this->ListChildren.DeleteList();
}

//*********************************************************************************
//**																	   GetChild
//*********************************************************************************
//**
//*********************************************************************************
const zCViewObject* zCViewObject::GetChild( zUINT32 nID )
{
	zCViewObject*	pView	= NULL;
	int				nViews	= this->ListChildren.GetNumInList();

	while( nViews )
	{
		pView = this->ListChildren[ --nViews ];
		if	( pView )
		if	( pView->GetID() == nID ) break;
		else  pView = NULL;
	}

	return pView;
}

//
//---------------------------------------------------------------------------------
//******************************     POSITIONING     ******************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**															 SetVirtualPosition
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject::SetVirtualPosition( zPOS& ptPosition )
{
	//
	//	APPLY VIRTUAL POSITION
	//
	this->VirtualPosition = ptPosition;

	//
	//	EVALUATE PIXEL POSITION
	//
	this->UpdatePixelPosition();
}

//*********************************************************************************
//**															   SetPixelPosition
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject::SetPixelPosition( zPOS& ptPosition )
{
	//
	//	APPLY PIXEL POSITION
	//
	this->PixelPosition = ptPosition;

	//
	//	UPDATE CHILDREN
	//
	this->UpdatePixelPositionChildren();
}

//*********************************************************************************
//**																 SetVirtualSize
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject::SetVirtualSize( zPOS& ptSize )
{
	//
	//	SET AND CHECK VIRTUAL SIZE
	//
	this->VirtualSize = ptSize;

	if ( this->VirtualSize.X <= 0 ) this->VirtualSize.X = 1;
	if ( this->VirtualSize.Y <= 0 ) this->VirtualSize.Y = 1;

	//
	//	GET AND CHECK PIXEL SIZE
	//
	this->EvaluatePixelSize( this->PixelSize );

	if ( this->PixelSize.X	 <= 0 ) this->PixelSize.X = 1;
	if ( this->PixelSize.Y	 <= 0 ) this->PixelSize.Y = 1;

	//
	//	UPDATE CHILDREN
	//
	this->UpdatePixelDimensionsChildren();
}

//*********************************************************************************
//**																   SetPixelSize
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject::SetPixelSize( zPOS& ptPosition )
{
	//
	//	APPLY PIXEL SIZE
	//
	this->PixelSize = ptPosition;

	//
	//	EVALUATE VIRTUAL SIZE
	//
	this->VirtualSize = this->ConvertSizePixelToVirtual( ptPosition );

	//
	//	UPDATE CHILDREN
	//
	this->UpdatePixelDimensionsChildren();
}

//*********************************************************************************
//**																	   Viewport
//*********************************************************************************
//** 
//*********************************************************************************

/*	------------------------------------------------------------------
	zCViewObject::GetViewport ()

	11.1.20010	[Hildebrandt]	
				removed legacy values (bpp, offset, dest)
	------------------------------------------------------------------ */

void zCCFASTCALL zCViewObject::GetViewport ( int &xmin, int &ymin , int &xdim, int &ydim)
{
	xmin	= this->PixelPosition.X	; 
	ymin	= this->PixelPosition.Y	;
	xdim	= this->PixelSize.X		;  
	ydim	= this->PixelSize.Y		;
};

//
//---------------------------------------------------------------------------------
//******************************     CONVERSION     *******************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**														  EvaluatePixelPosition
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject::EvaluatePixelPosition( zPOS& ptPosition )
{
	if ( ! this->ViewParent ) return;

	ptPosition +=	this->ViewParent->ConvertPositionVirtualToPixel	( this->VirtualPosition );	// convert my position
					this->ViewParent->EvaluatePixelPosition			( ptPosition			);	// apply parents' positions
}

//*********************************************************************************
//**															  EvaluatePixelSize
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject::EvaluatePixelSize( zPOS& ptSize )
{
	ptSize = zPOS( 0, 0 );

	if ( this->ViewParent )	
	{
		ptSize = this->VirtualSize;
		ptSize = this->ViewParent->ConvertSizeVirtualToPixel( ptSize );
	}
	else
	{
		ptSize = zPOS( zrenderer->vid_xdim,	zrenderer->vid_ydim );

		ptSize.X *= this->VirtualSize.X			 ;
		ptSize.X /= zCViewObject::ViewVirtualWidth ;
		ptSize.Y *= this->VirtualSize.Y			 ;
		ptSize.Y /= zCViewObject::ViewVirtualHeight;
	}
}

//*********************************************************************************
//**															UpdatePixelPosition
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject::UpdatePixelPosition( void )
{
	this->PixelPosition					= zPOS( 0, 0 );
	this->EvaluatePixelPosition			( this->PixelPosition );
	this->UpdatePixelPositionChildren	();
}

//*********************************************************************************
//**																UpdatePixelSize
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject::UpdatePixelSize( void )
{
	this->PixelSize						= zPOS( 0, 0 );
	this->EvaluatePixelSize				( this->PixelSize );
	this->UpdatePixelSizeChildren		();
}

//*********************************************************************************
//**													UpdatePixelPositionChildren
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject::UpdatePixelPositionChildren( void )
{
	zCViewObject* pViewChild = NULL;
	int			nViews	   = this->ListChildren.GetNumInList();

	while( nViews )	
	{
		pViewChild = this->ListChildren[ --nViews ];
		pViewChild->UpdatePixelPosition();
	}
}

//*********************************************************************************
//**														UpdatePixelSizeChildren
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject::UpdatePixelSizeChildren( void )
{
	zCViewObject* pViewChild = NULL;
	int			nViews	   = this->ListChildren.GetNumInList();

	while( nViews )	
	{
		pViewChild = this->ListChildren[ --nViews ];
		pViewChild->UpdatePixelSize();
	}
}

//*********************************************************************************
//**												  UpdatePixelDimensionsChildren
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject::UpdatePixelDimensionsChildren( void )
{
	this->UpdatePixelPositionChildren();
	this->UpdatePixelSizeChildren	 ();
}

//*********************************************************************************
//**												  ConvertPositionVirtualToPixel
//*********************************************************************************
//** 
//*********************************************************************************
zPOS zCViewObject::ConvertPositionVirtualToPixel( zPOS& ptPosition )
{
	zPOS ptResult = ptPosition;

	ptResult.X *= this->PixelSize.X;
	ptResult.X /= zCViewObject::ViewVirtualWidth;

	ptResult.Y *= this->PixelSize.Y;
	ptResult.Y /= zCViewObject::ViewVirtualHeight;

	return ptResult;
}

//*********************************************************************************
//**													  ConvertSizeVirtualToPixel
//*********************************************************************************
//** 
//*********************************************************************************
zPOS zCViewObject::ConvertSizeVirtualToPixel( zPOS& ptPosition )
{
	zPOS ptResult = ptPosition;

	ptResult.X *= this->PixelSize.X;
	ptResult.X /= zCViewObject::ViewVirtualWidth;

	ptResult.Y *= this->PixelSize.Y;
	ptResult.Y /= zCViewObject::ViewVirtualHeight;

	return ptResult;
}

//*********************************************************************************
//**													  ConvertSizePixelToVirtual
//*********************************************************************************
//** 
//*********************************************************************************
zPOS zCViewObject::ConvertPositionPixelToVirtual( zPOS& ptPosition )
{
	zPOS ptResult = ptPosition;

	if ( this->PixelSize.X )
	{
		ptResult.X *= zCViewObject::ViewVirtualWidth;
		ptResult.X /= this->PixelSize.X;
	}

	if ( this->PixelSize.Y )
	{
		ptResult.Y *= zCViewObject::ViewVirtualHeight;
		ptResult.Y /= this->PixelSize.Y;
	}

	return ptResult;
}

//*********************************************************************************
//**													  ConvertSizePixelToVirtual
//*********************************************************************************
//** 
//*********************************************************************************
zPOS zCViewObject::ConvertSizePixelToVirtual( zPOS& ptPosition )
{
	zPOS ptResult = ptPosition;

	if ( this->PixelSize.X )
	{
		ptResult.X *= zCViewObject::ViewVirtualWidth;
		ptResult.X /= this->PixelSize.X;
	}

	if ( this->PixelSize.Y )
	{
		ptResult.Y *= zCViewObject::ViewVirtualHeight;
		ptResult.Y /= this->PixelSize.Y;
	}

	return ptResult;
}

//*********************************************************************************
//**																 ConvertToPixel
//*********************************************************************************
//** 
//*********************************************************************************
zPOS zCViewObject::ConvertToPixel( zPOS& ptPosition )
{
	zPOS	ptPixel		 = this->ConvertToPixelLocal( ptPosition );					// convert the virtual position to a local pixel position
	zPOS	ptOwn		 = this->GetPixelPosition	()			  ;					// add own pixel position
			ptPixel		+= ptOwn;

	return	ptPixel;
}

//*********************************************************************************
//**															ConvertToPixelLocal
//*********************************************************************************
//** 
//*********************************************************************************
zPOS zCViewObject::ConvertToPixelLocal( zPOS& ptPosition )
{
	zPOS ptResult = ptPosition;

	ptResult.X *= this->PixelSize.X;
	ptResult.X /= zCViewObject::ViewVirtualWidth;

	ptResult.Y *= this->PixelSize.Y;
	ptResult.Y /= zCViewObject::ViewVirtualHeight;

	return ptResult;		
}

//*********************************************************************************
//**														 ConvertToVirtualLocal
//*********************************************************************************
//** 
//*********************************************************************************
zPOS zCViewObject::ConvertToVirtualLocal( zPOS& ptPosition )
{
	zPOS ptResult = ptPosition;

	if ( this->PixelSize.X )
	{
		ptResult.X *= zCViewObject::ViewVirtualWidth;
		ptResult.X /= this->PixelSize.X;
	}

	if ( this->PixelSize.Y )
	{
		ptResult.Y *= zCViewObject::ViewVirtualHeight;
		ptResult.Y /= this->PixelSize.Y;
	}

	return ptResult;
}

//*********************************************************************************
//**																			nax
//*********************************************************************************
//** 
//*********************************************************************************
int zCViewObject::nax( int x ) 
{ 
	return ( ( this->PixelSize.X * x ) / zCViewBase::ViewVirtualWidth );
}

//*********************************************************************************
//**																			nay
//*********************************************************************************
//** 
//*********************************************************************************
int zCViewObject::nay( int y )
{ 
	return ( ( this->PixelSize.Y * y ) / zCViewBase::ViewVirtualHeight );
}

//*********************************************************************************
//**																			anx
//*********************************************************************************
//** 
//*********************************************************************************
int zCViewObject::anx( int x )
{ 
	if ( this->PixelSize.X == 0 ) return 0;
	return ( ( zCViewBase::ViewVirtualWidth * x ) / this->PixelSize.X );
}

//*********************************************************************************
//**																			any
//*********************************************************************************
//** 
//*********************************************************************************
int zCViewObject::any( int y )
{ 
	if ( this->PixelSize.Y == 0 ) return 0;
	return ( ( zCViewBase::ViewVirtualHeight * y ) / this->PixelSize.Y );
}

//*********************************************************************************
//**																	   ClipLine
//*********************************************************************************
//** 
//*********************************************************************************
int zCViewObject :: ClipLine(int &x0,int &y0,int &x1,int &y1)
{
	int code1,code2,outcode,x,y;
	int cx1 = 0,		cy1 = 0;
	int cx2 = this->PixelSize.X-1,	cy2 = this->PixelSize.Y-1;
	
	code1 = GetCode( x0, y0 );
	code2 = GetCode( x1, y1 );
	do {
		if ((code1==0) && (code2==0)) return 1; else
		if ((code1 & code2)!=0)		  return 0; else
		{
			if (code1!=0) outcode=code1; else outcode=code2;
			if ((outcode & 8)==8) {
				x = x0+((x1-x0)*(cy2-y0)) / (y1-y0);
				y = cy2;
			} else if ((outcode & 4)==4) {
				x = x0+((x1-x0)*(cy1-y0)) / (y1-y0);
				y = cy1;
			} else if ((outcode & 2)==2) {
				y = y0+((y1-y0)*(cx2-x0)) / (x1-x0);
				x = cx2;
			} else if ((outcode & 1)==1) {
				y = y0+((y1-y0)*(cx1-x0)) / (x1-x0);
				x = cx1;
			} 
			if (outcode==code1) {
				x0 = x; y0 = y;
				code1 = GetCode(x0,y0);
			} else {
				x1 = x; y1 = y;
				code2 = GetCode(x1,y1);
			}     
       	}
	} while (1);
};

//*********************************************************************************
//**																		   Line
//*********************************************************************************
//** 
//*********************************************************************************
void zCViewObject :: Line( int x1, int y1, int x2, int y2, const zCOLOR& color )
{
	x1 = ::screen->nax( x1 );
	y1 = ::screen->nay( y1 );
	x2 = ::screen->nax( x2 );
	y2 = ::screen->nay( y2 );
	if ( this->ClipLine( x1, y1, x2, y2 ) )
	{
		zrenderer->DrawLine	( (float) x1, (float) y1, (float) x2, (float) y2, color );
	}
}

//*********************************************************************************
//**																		GetCode
//*********************************************************************************
//** 
//*********************************************************************************
int zCViewObject :: GetCode( int x, int y )
{
	int all;
	if (y>this->PixelSize.Y-1)	all=8; else
	if (y<0)					all=4; else all=0;
	if (x>this->PixelSize.X-1)	all=all | 2; else
	if (x<0)					all=all | 1;
	return (all);
}
