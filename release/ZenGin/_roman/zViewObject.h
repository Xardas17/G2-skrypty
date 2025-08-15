/******************************************************************************** 
 
     $Workfile:: zViewObject.h          $                $Date:: 11.01.01 21:09   $
     $Revision:: 10                   $             $Modtime:: 11.01.01 20:56   $
       $Author:: Hildebrandt                                                    $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/zengin_work/_Roman/zViewObject.h $
 * 
 * 10    11.01.01 21:09 Hildebrandt
 * 
 * 9     28.11.00 12:37 Keskenti
 * 
 * 8     23.10.00 23:27 Keskenti
 * 
 * 7     20.10.00 16:18 Keskenti
 * 
 * 6     19.10.00 19:14 Keskenti
 * 
 * 5     19.10.00 18:54 Keskenti
 * 
 * 4     19.10.00 18:27 Keskenti
 * 
 * 3     19.10.00 17:48 Keskenti
 * 
 * 2     19.10.00 17:15 Keskenti
 * 
 * 1     19.10.00 16:31 Keskenti
 * 
 * 7     17.10.00 22:38 Keskenti
 * 
 * 6     16.10.00 19:34 Keskenti
 * 
 * 5     16.10.00 18:59 Keskenti
 * 
 * 4     16.10.00 18:27 Keskenti
 * 
 * 3     13.10.00 21:35 Keskenti
 * 
 *********************************************************************************/

#ifndef __ZVIEWOBJECT_H__
#define __ZVIEWOBJECT_H__

//
//	LIST
//
class zCViewObject;
typedef zCListSort< zCViewObject > zCListViewObject;

//
//	POSITION
//
typedef
class zCPosition
{
public:
	zINT32 X;
	zINT32 Y;

	zCPosition()						{ X = 0l; Y = 0l ; } 
	zCPosition( zUINT32 x, zUINT32 y )	{ X = x ; Y = y  ; } 

	zCPosition& operator += ( zCPosition& ptOther ) { X += ptOther.X ; Y += ptOther.Y; return (*this); }
	zCPosition& operator -= ( zCPosition& ptOther ) { X -= ptOther.X ; Y -= ptOther.Y; return (*this); }
}
zPOS;

//
//	VIEW
//
class zCViewObject : public zCObject, public zCViewBase
{
	zCLASS_DECLARATION	(zCViewObject)
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:							
	zPOS				VirtualPosition		;
	zPOS				VirtualSize			;
	zPOS				PixelPosition		;
	zPOS				PixelSize			;
	zUINT32				ID					;
									
	zCViewObject*		ViewParent			;
	zCListViewObject	ListChildren		;
													
	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	static	zBOOL			__cdecl		Compare							( zCViewObject* pViewFirst, zCViewObject* pViewSecond	)			{ return	pViewFirst < pViewSecond				; }
																		
	//																														
	//	HIERARCHY																											
	//																														
public:																														
	void					zCCFASTCALL	SetID							( zUINT32 nID											)			{			this->ID			= nID				; }
	void					zCCFASTCALL	SetParent						( zCViewObject* pView									)			{			this->ViewParent	= pView				; }
																																			
	const zCListViewObject&	zCCFASTCALL	GetChildren						( void													)			{ return	this->ListChildren						; }
	const zCViewObject*		zCCFASTCALL	GetParent						( void													)			{ return	this->ViewParent						; }
	zUINT32 				zCCFASTCALL	GetID							( void													)			{ return	this->ID								; }
	const zCViewObject*		zCCFASTCALL	GetChild						( zUINT32 nID											)	;
																																	
	void					zCCFASTCALL	AddChildren						( zCListViewObject& listChildren						)	;
	void					zCCFASTCALL	AddChild						( zCViewObject* pView									)	;
	void					zCCFASTCALL	AddChild						( zCViewObject&  view									)	;
																																	
	void					zCCFASTCALL	RemoveChild						( zCViewObject* pView									)	;
	void					zCCFASTCALL	RemoveChild						( zCViewObject&  view									)	;
	void					zCCFASTCALL	RemoveAllChildren				( void													)	;

protected:
	void					zCCFASTCALL	UpdateChildren					( void													)	;
																																	
	//																																
	//	POSITION																													
	//																																
public:																																
	void					zCCFASTCALL	SetVirtualPosition				( zPOS& ptPosition										)	;
	void					zCCFASTCALL	SetVirtualSize					( zPOS& ptSize											)	;
																																	
	void					zCCFASTCALL	SetPixelPosition				( zPOS& ptPosition										)	;
	void					zCCFASTCALL	SetPixelSize					( zPOS& ptSize											)	;
																																	
	void					zCCFASTCALL	SetPosition						( zPOS& ptPosition										)			{			this->SetVirtualPosition( ptPosition )	; }
	void					zCCFASTCALL	SetSize							( zPOS& ptSize											)			{			this->SetVirtualSize	( ptSize )		; }
																																	
	const zPOS&				zCCFASTCALL	GetVirtualPosition				( void													)	const	{ return	this->VirtualPosition					; }
	const zPOS&				zCCFASTCALL	GetVirtualSize					( void													)			{ return	this->VirtualSize						; }
																																				
	const zPOS&				zCCFASTCALL	GetPixelPosition				( void													)	const	{ return	this->PixelPosition						; }
	const zPOS&				zCCFASTCALL	GetPixelSize					( void													)			{ return	this->PixelSize							; }
																																				
	const zPOS&				zCCFASTCALL	GetPosition						( void													)	const	{ return	this->GetVirtualPosition()				; }
	const zPOS&				zCCFASTCALL	GetSize							( void													)			{ return	this->GetVirtualSize	()				; }
																																	
	//																																
	//	DERIVATIONS																													
	//																																
	virtual int							anx								( int x													)	;
	virtual int							any								( int y													)	;
	virtual int							nax								( int x													)	;
	virtual int							nay								( int y													)	;
																																	
	virtual int							ClipLine						( int &x0, int &y0, int &x1, int &y1					)	;
	virtual void						Line							( int  x1, int  y1, int  x2, int  y2, const zCOLOR& c	)	;
	virtual void	zCCFASTCALL			GetViewport						( int &xmin, int &ymin , int &xdim, int &ydim)				; // [HILDEBRANDT] removed legacy values

protected:																															
	virtual int							GetCode							( int x, int y											)	;
																																	
	void					zCCFASTCALL	UpdatePixelDimensionsChildren	( void													)	;
	void					zCCFASTCALL	UpdatePixelPositionChildren		( void													)	;
	void					zCCFASTCALL	UpdatePixelSizeChildren			( void													)	;
																																		
	void					zCCFASTCALL	UpdatePixelPosition				( void													)	;
	void					zCCFASTCALL	UpdatePixelSize					( void													)	;
																																	
	void					zCCFASTCALL	EvaluatePixelPosition			( zPOS& ptPosition										)	;
	void					zCCFASTCALL	EvaluatePixelSize				( zPOS& ptSize											)	;
																																	
	zPOS					zCCFASTCALL	ConvertPositionPixelToVirtual	( zPOS& ptPosition										)	;
	zPOS					zCCFASTCALL	ConvertSizePixelToVirtual		( zPOS& ptPosition										)	;
	zPOS					zCCFASTCALL	ConvertPositionVirtualToPixel	( zPOS& ptPosition										)	;
	zPOS					zCCFASTCALL	ConvertSizeVirtualToPixel		( zPOS& ptPosition										)	;
																																	
	zPOS					zCCFASTCALL	ConvertToVirtualLocal			( zPOS& ptPosition										)	;
	zPOS					zCCFASTCALL	ConvertToPixelLocal				( zPOS& ptPosition										)	;
	zPOS					zCCFASTCALL	ConvertToPixel					( zPOS& ptPosition										)	;
																																	
	//																																
	//	CON-/DESTRUCTION
	//
protected:
			 zCViewObject();
	virtual ~zCViewObject();
};

typedef zCViewObject	*LPCViewObject,	*LPCVIEWOBJECT;

#endif	//__ZVIEWOBJECT_H__