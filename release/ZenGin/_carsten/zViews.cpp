//

#include "zcore.h"
#include "zviews.h"
zCViewWindow::zCViewWindow(int x1,int y1,int x2,int y2,zTviewID itemid) 
	: zCView(x1,y1,x2,y2,itemid)
{
	ClrFlags	(VIEW_TXT_CENTER);
	//SetFontColor(GFX_WHITE);	
};
zCViewWindow::~zCViewWindow()
{
};
