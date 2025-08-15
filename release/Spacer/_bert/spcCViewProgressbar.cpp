/******************************************************************************** 
 
     $Workfile:: spcCViewProgressbar. $                $Date:: 28.08.00 13:24   $
     $Revision:: 6                    $             $Modtime:: 24.08.00 14:00   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Spacer/_Bert/spcCViewProgressbar.cpp $
 * 
 * 6     28.08.00 13:24 Speckels
 * 
 * 11    24.08.00 15:54 Speckels
 * 
 * 10    23.08.00 21:47 Admin
 * 
 * 4     22.08.00 15:51 Speckels
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
 * 8     10.05.00 23:34 Speckels
 * 
 * 7     8.05.00 20:51 Speckels
 * 
 * 6     8.05.00 20:39 Speckels
 * 
 * 5     8.05.00 17:48 Speckels
 * 
 * 4     8.05.00 17:32 Speckels
 * 
 * 3     8.05.00 12:19 Speckels
 * 
 * 2     8.05.00 12:11 Speckels
 * 
 * 1     8.05.00 12:01 Speckels
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
/// @version $Revision: 6 $ ($Modtime: 24.08.00 14:00 $)


#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spccviewprogressbar.h"
#include "spcCWorkProgressDlg.h"

///
// Gothic-Progressbar
///


spcCViewProgressBar::~spcCViewProgressBar()
{
	ctrl_progress->CloseWindow();
	ctrl_progress->DestroyWindow();
	 delete ctrl_progress;
	 ctrl_progress=0;
};

// [EDENFELD] neu 1.33 aus ModSource
static const int WINDOW_FRAME = 10;
void spcCViewProgressBar::Init(CWnd* parent)
{	
	zCViewProgressBar::Init();	
	
	ctrl_progress = new spcCWorkProgressDlg();	
	ctrl_progress->Create(IDD_WORK_PROGRESS_DLG,parent);
	ctrl_progress->ShowWindow(SW_SHOW);
	ctrl_progress->Init(0,100);		
	ctrl_progress->SetPos(0);

	RECT systemRect, rect;
	SystemParametersInfo(SPI_GETWORKAREA,0,&systemRect,0);	
	ctrl_progress->GetWindowRect(&rect);
	int height = rect.bottom-rect.top;
	int width = rect.right-rect.left;	

	ctrl_progress->SetWindowPos(&CWnd::wndTopMost,systemRect.right - width - WINDOW_FRAME,systemRect.bottom-height-WINDOW_FRAME,width,height,0);
};

void spcCViewProgressBar::HandleChange()
{	
	ctrl_progress->SetPos(percent);
	if (ctrl_progress->GetParentOwner()) ctrl_progress->GetParentOwner()->RedrawWindow();
};
