/******************************************************************************** 
 
     $Workfile:: oviewprogressbar.h  $                 $Date:: 28.08.00 14:31   $
     $Revision:: 8                   $              $Modtime:: 24.08.00 12:09   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH

   Description::
   a progress-bar-class supporting a variety of progress-bars with rercursive 
   percentage-control: You can say how much of the current algorithms has been 
   finished recursively and the progress-bar will show the hole percent until
   the master-progress is complete (100%).

 * $Log: /current_work/Gothic/_Bert/oviewprogressbar.h $
 * 
 * 8     28.08.00 14:31 Speckels
 * 
 * 14    23.08.00 21:46 Admin
 * 
 * 6     21.08.00 18:47 Speckels
 * 
 * 12    16.08.00 12:32 Admin
 * 
 * 5     10.08.00 21:46 Speckels
 * 
 * 11    9.08.00 17:11 Admin
 * 
 * 4     8.05.00 17:32 Speckels
 * 
 * 3     8.05.00 12:19 Speckels
 * 
 * 2     8.05.00 12:11 Speckels
 * 
 * 1     8.05.00 12:01 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 8 $ ($Modtime: 24.08.00 12:09 $)


#include "zviewprogressbar.h"



///
// Gothic
///

class oCViewGothicProgressBar : public zCViewProgressBar
{
public:
	oCViewGothicProgressBar(int x1,int y1,int x2,int y2,zTviewID itemid = VIEW_ITEM) : zCViewProgressBar(x1,y1,x2,y2,itemid) {  };
	virtual ~oCViewGothicProgressBar() {};

	virtual void Init();

	virtual void HandleChange();		
protected:
	int progressbar_sizex;
};
