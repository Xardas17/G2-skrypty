/******************************************************************************** 
 
     $Workfile:: oHelp.h              $                $Date:: 22.05.00 18:42   $
     $Revision:: 4                    $             $Modtime:: 9.05.00 14:23    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oHelp.h $
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

// oHelp -> Darstellung des Hilfe-Fensters

#ifndef __OHELP_H__
#define __OHELP_H__

class zCView;
class zCVob;

class oCHelp {
	
public :
	
	oCHelp						();
	oCHelp						(int x,int y);
	~oCHelp						();

	void		Update			();
	void		CalcPos			();
	void		Redraw			(zCVob* v = 0);
	void		Toggle			();

private:

	zCView*		win;

	int			dx,dy;
	int			sx,sy;
	int			x    [4]	,y[4];
	int			index[4];
	int			led  [2];
	int			ledx [2]	,ledy[2];

};

#endif