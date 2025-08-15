/******************************************************************************** 
 
     $Workfile:: zviewprogressbar.cpp $                $Date:: 11.02.01 16:13   $
     $Revision:: 27                   $             $Modtime:: 11.02.01 14:23   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/zviewprogressbar.cpp $
 * 
 * 27    11.02.01 16:13 Speckels
 * 
 * 26    1.02.01 19:26 Speckels
 * 
 * 25    30.01.01 21:59 Speckels
 * 
 * 24    21.11.00 9:09 Moos
 * 
 * 23    12.09.00 22:28 Speckels
 * 
 * 22    30.08.00 13:47 Moos
 * 
 * 21    28.08.00 14:24 Speckels
 * 
 * 16    23.08.00 21:47 Admin
 * 
 * 18    23.08.00 18:41 Speckels
 * 
 * 17    23.08.00 18:25 Speckels
 * 
 * 16    21.08.00 18:26 Speckels
 * 
 * 14    16.08.00 12:32 Admin
 * 
 * 15    10.08.00 21:47 Speckels
 * 
 * 13    9.08.00 17:12 Admin
 * 
 * 14    21.07.00 15:17 Speckels
 * 
 * 13    9.05.00 20:58 Speckels
 * 
 * 12    8.05.00 20:37 Speckels
 * 
 * 10    8.05.00 19:07 Speckels
 * 
 * 9     8.05.00 17:49 Speckels
 * 
 * 8     8.05.00 17:32 Speckels
 * 
 * 7     8.05.00 15:15 Speckels
 * 
 * 6     8.05.00 12:19 Speckels
 * 
 * 5     8.05.00 12:11 Speckels
 * 
 * 4     7.05.00 14:02 Speckels
 * 
 * 3     5.05.00 13:46 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:24 Speckels
 * 
 * 6     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 5     2.12.99 22:51 Speckels
 * Output of percentage and time as spy-messages
 * 
 * 4     21.10.99 23:27 Speckels
 * New inherited progressbar-classes for
 * various types of progress-bars
 * 
 * 3     14.10.99 10:57 Speckels
 * Neue virtuelle Methode Draw()
 * Implementierung einiger
 * Beispiel-Progressbars
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 27 $ ($Modtime: 11.02.01 14:23 $)


#include "zcore.h"
#include "zviewprogressbar.h"
#include "zvideo_win32.h"
#include "zgrafix.h"

zCViewProgressBar::zCViewProgressBar(int x1,int y1,int x2,int y2,zTviewID itemid) : zCView(x1,y1,x2,y2,itemid)
{
	minStep	= 1;
	bar		= 0;
	percent	= 0;
	text	= zSTR_EMPTY;
};

zCViewProgressBar::~zCViewProgressBar()
{
    ResetRange(); // [Moos] Nochn Leakfix
    delete bar;   // [Moos] leakfix
};

void zCViewProgressBar::Init()
{
	minStep	= 1;
	bar		= 0;
	percent	= 0;
	text	= zSTR_EMPTY;
};

zREAL zCViewProgressBar::CalcPercentOf(zREAL percent, zREAL min, zREAL max)
{
	return ((percent*(max-min)) / 100) + min;
};

void zCViewProgressBar::SetPercent(int _percent, zSTRING _text)
{
	zClamp(_percent, 0,100);
	zREAL real_percent = zREAL(_percent);
	if (rangeList.GetNumInList()>0) 
	{
		zTProgressRange* ref_range = rangeList.Get(0);	
		real_percent = CalcPercentOf(real_percent,ref_range->min,ref_range->max);
	}	

	if ((percent!=0) && (percent!=100) && ( (real_percent-percent) < minStep)) return;

	percent = int(real_percent);
	zClamp(percent,0,100);

	zERR_MESSAGE(3,0,"B: ---------- "+zSTRING(percent)+"% ----------");	

	if (!_text.IsEmpty()) text = _text;
	
	HandleChange();	
};

void zCViewProgressBar::HandleChange()
{
	ClrPrintwin();
	Print(0,0,zSTRING(percent)+"%");
	Draw();
};

void zCViewProgressBar::Draw()
{		
	zrenderer->BeginFrame();
	// zrenderer->Vid_Clear(zCOLOR(0,0,0,255));
	screen->Render();

	zrenderer->EndFrame();

	zrenderer->Vid_Blit(FALSE); 
};

void zCViewProgressBar::SetRange(int min, int max)
{
	zREAL abs_min = zREAL(min);
	zREAL abs_max = zREAL(max);
	if (rangeList.GetNumInList()>0) 
	{
		zTProgressRange* ref_range = rangeList.Get(0);
		abs_min = CalcPercentOf(abs_min,ref_range->min, ref_range->max);
		abs_max = CalcPercentOf(abs_max,ref_range->min, ref_range->max);		
	}	

	zTProgressRange* range = zNEW(zTProgressRange);
	range->min = abs_min;
	range->max = abs_max;	
	range->iteration = rangeList.GetNumInList();
	rangeList.InsertFront(range);
};

void zCViewProgressBar::ResetRange()
{
	if (rangeList.GetNumInList()<=0) return;
	zTProgressRange* range = rangeList.Get(0);
	rangeList.Remove(range);
	delete range;	
};

