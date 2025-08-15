#ifndef __OVISFX_MULTITARGET_H__
#define __OVISFX_MULTITARGET_H__


#include "ovisfx.h"

class oCVisFX_MultiTarget : public oCVisualFX
{
	zCLASS_DECLARATION (oCVisFX_MultiTarget)
public:

	oCVisFX_MultiTarget();
	virtual ~oCVisFX_MultiTarget();

	zCArray<oCVisualFX*> visList;

	// seperate virtual magic visual methods, common to all spells / magic visuals

	// init, inserts fx vobs into world, initializes AI Callbacks per frame etc.

	virtual void	Open			();											// fx if selected in spell book 
	virtual void	Init			( zCArray <zCVob *> trajectoryVobs		);  // adv. init, can be called more than once
	virtual void	InvestNext		()										 ;  // as information for visual spell
	virtual void	SetLevel		( int level )							 ;  // as information for visual spell
	virtual void	Cast			( const zBOOL killAfterDone = TRUE );		// shoot
	virtual void	Stop			( const zBOOL killAfterDone = TRUE );		// stop or destroy / delete 
	virtual void	Play			( const float keyCycleTime = 0,const zMAT4 *orgTrafo = 0, const zMAT4 *targetTrafo=0 )	{};
	virtual zBOOL	IsFinished		();
	virtual void	SetByScript		( const zSTRING &id );
	virtual void	Reset			();

	virtual	void	SetDamage		( const float dam     );
	virtual	void	SetDamageType	( const int   damType );

	virtual void	Archive			(zCArchiver &);
	virtual void	Unarchive		(zCArchiver &);
};


#endif