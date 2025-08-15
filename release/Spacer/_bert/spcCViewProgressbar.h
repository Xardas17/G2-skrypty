/******************************************************************************** 
 
     $Workfile:: spcCviewprogressbar $                 $Date:: 28.08.00 13:24   $
     $Revision:: 5                   $              $Modtime:: 24.08.00 12:09   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH

   Description::
   a progress-bar-class supporting a variety of progress-bars with rercursive 
   percentage-control: You can say how much of the current algorithms has been 
   finished recursively and the progress-bar will show the hole percent until
   the master-progress is complete (100%).

 * $Log: /current_work/Spacer/_Bert/spcCviewprogressbar.h $
 * 
 * 5     28.08.00 13:24 Speckels
 * 
 * 10    23.08.00 21:47 Admin
 * 
 * 3     21.08.00 21:13 Speckels
 * 
 * 8     16.08.00 12:32 Admin
 * 
 * 2     10.08.00 21:47 Speckels
 * 
 * 7     9.08.00 17:12 Admin
 * 
 * 1     26.05.00 11:52 Admin
 * 
 * 2     21.05.00 18:32 Speckels
 * 
 * 1     20.05.00 13:21 Speckels
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
/// @version $Revision: 5 $ ($Modtime: 24.08.00 12:09 $)


#include "zviewprogressbar.h"

class spcCWorkProgressDlg;
class CWnd;

///
// Gothic
///

class spcCViewProgressBar : public zCViewProgressBar
{
public:
	spcCViewProgressBar(int x1,int y1,int x2,int y2,zTviewID itemid = VIEW_ITEM) : zCViewProgressBar(0,0,0,0,itemid) { ctrl_progress=0; };
	virtual ~spcCViewProgressBar();

	virtual void Init(CWnd* parent);

	virtual void HandleChange();		
protected:

	spcCWorkProgressDlg* ctrl_progress;


};
