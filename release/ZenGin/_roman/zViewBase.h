/******************************************************************************** 
 
     $Workfile:: zViewBase.h          $                $Date:: 11.01.01 21:09   $
     $Revision:: 16                   $             $Modtime:: 11.01.01 20:52   $
       $Author:: Hildebrandt                                                    $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/zengin_work/_Roman/zViewBase.h $
 * 
 * 16    11.01.01 21:09 Hildebrandt
 * 
 * 15    20.10.00 16:18 Keskenti
 * 
 * 14    19.10.00 19:37 Keskenti
 * 
 * 13    19.10.00 19:21 Keskenti
 * 
 * 12    19.10.00 18:54 Keskenti
 * 
 * 11    19.10.00 18:27 Keskenti
 * 
 * 10    19.10.00 18:03 Keskenti
 * 
 * 9     19.10.00 17:48 Keskenti
 * 
 * 8     19.10.00 17:15 Keskenti
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

#ifndef __ZVIEWBASE_H__
#define __ZVIEWBASE_H__

struct zCOLOR;
//
//	VIEW
//
class zCViewBase 
{
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
public:
	static const zUINT16		ViewVirtualWidth	;														
	static const zUINT16		ViewVirtualHeight	;
									
public:
	virtual int					anx			( int x )																	{ return 0; }
	virtual int					any			( int y )																	{ return 0; }
	virtual int					nax			( int x )																	{ return 0; }
	virtual int					nay			( int y )																	{ return 0; }
																														
	virtual int					ClipLine	( int &x0, int &y0, int &x1, int &y1 )										{ return 0; }
	virtual void				Line		( int  x1, int  y1, int  x2, int  y2, const zCOLOR& color )					{ ; }
	virtual void	zCCFASTCALL	GetViewport	( int &xmin, int &ymin , int &xdim, int &ydim)								{ ; };			// [HILDEBRANDT] removed legacy values

	virtual void				FillZBuffer	( void )																	;

protected:
	virtual int		GetCode		( int x, int y )															{ return 0; }

	//
	//	CON-/DESTRUCTION
	//
protected:
	 zCViewBase();
	~zCViewBase();
};

typedef zCViewBase	*LPCViewBase,	*LPCVIEWBASE;

#endif	//__ZVIEWBASE_H__

