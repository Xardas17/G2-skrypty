/******************************************************************************** 
 
     $Workfile:: oviewprogressbar.cpp $                $Date:: 16.02.01 13:12   $
     $Revision:: 20                   $             $Modtime:: 15.02.01 21:40   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/oviewprogressbar.cpp $
 * 
 * 20    16.02.01 13:12 Speckels
 * 
 * 19    15.02.01 2:46 Speckels
 * 
 * 18    16.11.00 15:41 Speckels
 * 
 * 17    18.09.00 21:32 Speckels
 * 
 * 16    28.08.00 14:31 Speckels
 * 
 * 14    23.08.00 21:46 Admin
 * 
 * 14    21.08.00 18:47 Speckels
 * 
 * 12    16.08.00 12:32 Admin
 * 
 * 13    10.08.00 21:46 Speckels
 * 
 * 11    9.08.00 17:11 Admin
 * 
 * 12    21.07.00 15:16 Speckels
 * 
 * 11    18.07.00 12:58 Speckels
 * 
 * 10    10.07.00 15:53 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 20 $ ($Modtime: 15.02.01 21:40 $)


#include "zcore.h"
#include "oviewprogressbar.h"
#include "zinput.h"


const zSTRING TEX_PROGRESS		= "PROGRESS.TGA";
const zSTRING TEX_PROGRESS_BAR	= "PROGRESS_BAR.TGA";

const int PROGRESS_DX		= 1200;	// in virtuellen Koordinaten (0 bis 8192)
const int PROGRESS_DY		= 1200; // in virtuellen Koordinaten (0 bis 8192)
// const int PROGRESS_SIZEY	= 2500; // in virtuellen Koordinaten (0 bis 8192)


///
// Gothic-Progressbar
///


void oCViewGothicProgressBar::Init()
{	
	zCViewProgressBar::Init();

	InsertBack(TEX_PROGRESS);	
	SetAlphaBlendFunc(zRND_ALPHA_FUNC_BLEND);
	SetTransparency(255);			
};

void oCViewGothicProgressBar::HandleChange()
{			
	int sizex = 8192 - PROGRESS_DX*2;
	int sizey = 8192 - PROGRESS_DY*2;
	sizex = int(sizex * (percent/100.0));
	
	if (!bar) 
	{
		bar = zNEW(zCView(0,0,1000,1000));	
		InsertItem(bar);
		bar->InsertBack(TEX_PROGRESS_BAR);	
		bar->SetPos(PROGRESS_DX,PROGRESS_DY);
	}	

	bar->SetSize(sizex, sizey);		

	bar->ClrPrintwin();

#ifdef _DEBUG
	
	//if (percent<98)
	bar->PrintCXY(zSTRING(percent)+"%");
#endif
	/*
	if (percent>=98)
	{
		bar->PrintCXY("entering world...");
	}*/

	Draw();

	// sysEvent();
	// if (zinput) zinput->ProcessInputEvents();
};


