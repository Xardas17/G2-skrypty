/******************************************************************************** 
 
     $Workfile:: zviewprogressbar.h  $                 $Date:: 4.12.00 18:22    $
     $Revision:: 15                  $              $Modtime:: 4.12.00 18:00    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH

   Description::
   a progress-bar-class supporting a variety of progress-bars with rercursive 
   percentage-control: You can say how much of the current algorithms has been 
   finished recursively and the progress-bar will show the hole percent until
   the master-progress is complete (100%).

 * $Log: /current_work/ZenGin/_Bert/zviewprogressbar.h $
 * 
 * 15    4.12.00 18:22 Moos
 * 
 * 14    28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 12    21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 11    10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 10    8.05.00 20:37 Speckels
 * 
 * 9     8.05.00 19:30 Speckels
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
 * 2     24.09.99 20:41 Speckels
 * VSS-kompatiblen Header eingefügt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 15 $ ($Modtime: 4.12.00 18:00 $)


#ifndef __ZVIEWPROGRESSBAR_H__
#define __ZVIEWPROGRESSBAR_H__

#ifndef _INC_TIME
#include "time.h"
#endif

#ifndef __ZVIEW_H__
#include "zview.h"
#endif


struct zTProgressRange
{
	int iteration;
	zREAL min;
	zREAL max;
};


class zCViewProgressBar : public zCView
{
public:
	zCViewProgressBar(int x1,int y1,int x2,int y2,zTviewID viewID = VIEW_ITEM);	
	virtual ~zCViewProgressBar();

	virtual void Init();
	
	void	SetText(zSTRING _text)		{ text = _text;HandleChange(); };	
	zSTRING	GetText()					{ return text; };	
	int	 GetPercent()	{ return percent; };
	void	SetRange(int min, int max);
	void	ResetRange();
	void	SetPercent(int percent, zSTRING _text=zSTR_EMPTY);	

	void	SetMinimumStep(int step) { minStep = (step>=1 && step<100)?step:1; };

	virtual void HandleChange();
	virtual void Draw();	

protected:

	zCView* bar;

	int		minStep;	
	int		percent;
	
	zSTRING	text;
	time_t 	start_time;
	

private:
	
	zREAL CalcPercentOf(zREAL percent, zREAL min, zREAL max);

	zCList<zTProgressRange> rangeList;
};



#endif