/******************************************************************************** 
 
     $Workfile:: oFocus.h             $                $Date:: 2.11.00 22:07    $
     $Revision:: 7                    $             $Modtime:: 2.11.00 20:03    $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oFocus.h $
 * 
 * 7     2.11.00 22:07 Edenfeld
 * 
 * 6     22/09/00 16:50 Luesebrink
 * 
 * 5     26.08.00 14:18 Moos
 * 
 * 4     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 3     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __OFOCUS_H__
#define __OFOCUS_H__

#ifndef __ZTYPES_H__
#include "zTypes.h"
#endif

#ifndef  __ZSTRING_H__
#include "zString.h"
#endif

#ifndef  __ONPC_H__
#include "onpc.h"
#endif


// Verschiedene Focusmodi
const int FOCUS_MAX = 6;
enum	{ FOCUS_NORMAL = 0, FOCUS_MELEE = 1, FOCUS_RANGED = 2, FOCUS_THROW_ITEM = 3, FOCUS_THROW_MOB = 4, FOCUS_MAGIC = 5};

class oCNpcFocus {

public: 

	oCNpcFocus								();
	~oCNpcFocus								();

	static int			GetHighlightMeleeFocus()							{ return s_iHightlightMeleeFocus;	};
	static void			SetHighlightMeleeFocus(const int a_i)				{ s_iHightlightMeleeFocus = a_i;	};
	static int			GetHighlightInteractFocus()							{ return s_bHighlightInteractFocus; };
	static void			SetHighlightInteractFocus(const zBOOL a_b)			{ s_bHighlightInteractFocus = a_b;	};
	static void			StartHighlightningFX (oCNpc* a_npc);
	static void			StopHighlightningFX  ();
	static zBOOL		IsHighlightActive	 ()								{ return isHighLighted;				};

	void				Init				(zSTRING &s);
	void				Init				(int index);

	zBOOL				IsValid				(int type);
	
	zBOOL				HasLowerPriority	(int type1,int type2);
	int					GetPriority			(int type);

	zBOOL				IsInRange			(int type, zREAL dist);
	zBOOL				IsInAngle			(int type, zREAL azi, zREAL elev);

	zREAL				GetMaxRange			();
	zREAL				GetRange2			();
/* ----------------------------------------------------------------------

	22.09.2000	[Dennis]	

				Azimuth holen

   ---------------------------------------------------------------------- */
	zREAL				GetAzi				();

	zREAL				GetItemThrowRange	();
	zREAL				GetMobThrowRange	();

	// Statics
	static  void		InitFocusModes		();
	static  void		ExitFocusModes		(); // [Moos]
	static  void		SetFocusMode		(int fm);
	static  zSTRING		GetFocusName		();

	static	oCNpcFocus*	focus;

private :

	zBOOL				IsNpcInRange		(zREAL dist);
	zBOOL				IsNpcInAngle		(zREAL azi, zREAL elev);
	zBOOL				IsItemInRange		(zREAL dist);
	zBOOL				IsItemInAngle		(zREAL azi, zREAL elev);
	zBOOL				IsMobInRange		(zREAL dist);
	zBOOL				IsMobInAngle		(zREAL azi, zREAL elev);
	
	struct {	
		// PARSER ON
		zREAL	n_range3;						// NSC Zuruf-Distanz "20 m"
		// *** NSC ***
		zREAL	n_range1,n_range2;				// Valid Range for Object
		zREAL	n_azi;
		zREAL	n_elev1,n_elev2;				
		int		n_prio;							// Priority of Object
		// *** ITEM ***
		zREAL	i_range1,i_range2;				// Valid Range for Object
		zREAL	i_azi;
		zREAL	i_elev1,i_elev2;				
		int		i_prio;							// Priotity of Object
		// *** MOB ***
		zREAL	m_range1,m_range2;				// Valid Range for Object
		zREAL	m_azi;
		zREAL	m_elev1,m_elev2;				
		int		m_prio;							// Priotity of Object
		// PARSER OFF
		zREAL	max_range;
	};

	// static
	// Array of available Focus-Modi
	static  oCNpcFocus*	focuslist[FOCUS_MAX];
	static int			s_iHightlightMeleeFocus;
	static zBOOL		s_bHighlightInteractFocus;
	static oCVisualFX*	highLightFX;
	static zBOOL		isHighLighted;

};

#endif
