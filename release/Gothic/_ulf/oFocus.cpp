/******************************************************************************** 
 
     $Workfile:: oFocus.cpp           $                $Date:: 2.11.00 22:07    $
     $Revision:: 11                   $             $Modtime:: 2.11.00 20:09    $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oFocus.cpp $
 * 
 * 11    2.11.00 22:07 Edenfeld
 * 
 * 10    13.10.00 15:35 Wohlers
 * 
 * 9     11/10/00 15:28 Luesebrink
 * 
 * 8     22/09/00 16:50 Luesebrink
 * 
 * 7     26.08.00 14:20 Moos
 * kleines Leck mit der focuslist gefixt
 * 
 * 6     2.08.00 14:25 Wohlers
 * 
 * 5     21.07.00 15:34 Wohlers
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
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "oFocus.h"

#include "zParser.h"
#include "z3d.h"
#include "zVob.h"
#include "ovisfx.h"

#pragma warning ( disable:4244 )

// *********************
// STATICS
// *********************

zSTRING focusnames[FOCUS_MAX] = {
	"Focus_Normal",
	"Focus_Melee",
	"Focus_Ranged",
	"Focus_Throw_Item",
	"Focus_Throw_Mob",
	"Focus_Magic"
};

oCNpcFocus* oCNpcFocus :: focuslist	[FOCUS_MAX];
oCNpcFocus* oCNpcFocus :: focus					  = NULL;
int			oCNpcFocus :: s_iHightlightMeleeFocus = 0;
zBOOL		oCNpcFocus :: s_bHighlightInteractFocus= TRUE;
oCVisualFX*	oCNpcFocus :: highLightFX			  = NULL;
zBOOL		oCNpcFocus::  isHighLighted			  = FALSE;

void oCNpcFocus :: InitFocusModes()
{
	for (int i=0; i<FOCUS_MAX; i++) {
		focuslist[i] =  zNEW( oCNpcFocus() );
		focuslist[i] -> Init (focusnames[i]);
	}
	SetFocusMode(FOCUS_NORMAL);
}

/* ----------------------------------------------------------------------
	
    oCNpcFocus :: ExitFocusModes()	

	26.08.2000	[Moos]	
                Neu erzeugt

   ---------------------------------------------------------------------- */

void oCNpcFocus :: ExitFocusModes()
{
    focus = NULL;
	for (int i=0; i<FOCUS_MAX; i++) {
		delete focuslist[i];
        focuslist[i] = NULL;
	}
}

void oCNpcFocus :: SetFocusMode(int fm)
{
	if (fm < FOCUS_MAX) focus = focuslist[fm];
	zERR_MESSAGE(9,0,"U:FCS:Focus-Mode set to "+ focusnames[fm]);
}

zSTRING oCNpcFocus :: GetFocusName()
{
	for (int i=0; i<FOCUS_MAX; i++) {
		if (focuslist[i]==focus) return focusnames[i];
	}
	return zSTRING("no focus");
}

// *********************
// MEMBER
// *********************

oCNpcFocus :: oCNpcFocus()
{
	memset(this,0,sizeof(oCNpcFocus));
}

oCNpcFocus :: ~oCNpcFocus()
{	
	if (highLightFX) 
	{
		highLightFX->Stop();
		zRELEASE(highLightFX);
	};
	isHighLighted = FALSE;
}

void oCNpcFocus:: Init (zSTRING &s)
{
	s.Upper();
	Init (parser.GetIndex(s));
}

void oCNpcFocus :: Init (int index)
{
	parser.CreateInstance(index,this);
	// Get Maximum Range
	max_range = n_range2;
	if (max_range < i_range2) max_range = i_range2;
	if (max_range < m_range2) max_range = m_range2;
	if (max_range < n_range3) max_range = n_range3;
	
	// Set Length to Length2
	n_range1 *= n_range1;
	n_range2 *= n_range2;
	n_range3 *= n_range3;
	i_range1 *= i_range1;
	i_range2 *= i_range2;
	m_range1 *= m_range1;
	m_range2 *= m_range2;
}

BOOL oCNpcFocus :: IsValid( int type )
{
	if (type==zVOB_TYPE_NSC)	return (n_prio>=0);	else
	if (type==zVOB_TYPE_ITEM)	return (i_prio>=0); else
	if (type==zVOB_TYPE_MOB)	return (m_prio>=0);	else
	return FALSE;
}

zREAL oCNpcFocus :: GetMaxRange()
{
	return max_range;
}

zREAL oCNpcFocus :: GetRange2()
// return range2
{
	return n_range2;
}

zREAL oCNpcFocus :: GetItemThrowRange()
{
	return i_range2;
}

zREAL oCNpcFocus :: GetMobThrowRange()
{
	return m_range2;
}

BOOL oCNpcFocus :: HasLowerPriority(int type1, int type2)
{
	return (GetPriority(type1) < GetPriority(type2));
}

int  oCNpcFocus :: GetPriority(int type)
{
	if (type==zVOB_TYPE_NSC)	return n_prio;	else
	if (type==zVOB_TYPE_ITEM)	return i_prio;	else
	if (type==zVOB_TYPE_MOB)	return m_prio;
	return (-1);
}

BOOL oCNpcFocus :: IsInRange(int type, zREAL dist)
{
	if (type==zVOB_TYPE_NSC)	return IsNpcInRange (dist);	else
	if (type==zVOB_TYPE_ITEM)	return IsItemInRange(dist); else
	if (type==zVOB_TYPE_MOB)	return IsMobInRange (dist);	else
	return FALSE;
}

BOOL oCNpcFocus :: IsInAngle(int type, zREAL azi, zREAL elev)
{
	if (type==zVOB_TYPE_NSC)	return IsNpcInAngle (azi,elev);	else
	if (type==zVOB_TYPE_ITEM)	return IsItemInAngle(azi,elev); else
	if (type==zVOB_TYPE_MOB)	return IsMobInAngle (azi,elev);	else
	return FALSE;
}

BOOL oCNpcFocus :: IsNpcInRange(zREAL dist) 
{
	zREAL rmax = zMax(n_range2,n_range3);
	return ((n_range1<=dist) && (dist<=rmax));
}

BOOL oCNpcFocus :: IsNpcInAngle(zREAL azi,zREAL elev)
{
	return ((abs(azi)<=n_azi) && (n_elev1<=elev) && (elev<=n_elev2));
}

BOOL oCNpcFocus :: IsItemInRange(zREAL dist) 
{
	return ((i_range1<=dist) && (dist<=i_range2));
}

BOOL oCNpcFocus :: IsItemInAngle(zREAL azi,zREAL elev)
{
	return ((abs(azi)<=i_azi) && (i_elev1<=elev) && (elev<=i_elev2));
}

BOOL oCNpcFocus :: IsMobInRange(zREAL dist) 
{
	return ((m_range1<=dist) && (dist<=m_range2));
}

BOOL oCNpcFocus :: IsMobInAngle(zREAL azi,zREAL elev)
{
	return ((abs(azi)<=m_azi) && (m_elev1<=elev) && (elev<=m_elev2));
}

/* ----------------------------------------------------------------------

	22.09.2000	[Dennis]	

				Azimuth holen

   ---------------------------------------------------------------------- */
zREAL oCNpcFocus :: GetAzi()
{
	return n_azi;
}


void  oCNpcFocus :: StartHighlightningFX (oCNpc* a_npc)
{
	if (highLightFX && highLightFX->GetOrigin()==a_npc) return;

	if (highLightFX) 
	{
		highLightFX->Stop();
		zRELEASE(highLightFX);
	};
	if ( (oCNpcFocus::GetHighlightMeleeFocus()==1) || (oCNpcFocus::GetHighlightMeleeFocus()==3) )
	highLightFX = oCVisualFX::CreateAndPlay("FOCUS_HIGHLIGHT",a_npc, a_npc);
	isHighLighted=TRUE;
};

void  oCNpcFocus :: StopHighlightningFX ()
{
	if (highLightFX) 
	{
		highLightFX->Stop();
		zRELEASE(highLightFX);
	};
	isHighLighted = FALSE;
};


#pragma warning ( default:4244 )