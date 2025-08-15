/********************************************************************************

  Various Tools

 Project : Gothic
 File    : oDBGTools.h
 Author  : Carsten Edenfeld
 Version : 0.00
 Created : 27.04.98 02:12:02
 Last Mod: 27.04.98 02:12:02
 
*********************************************************************************/
//#define _USE_TOOLS

#ifndef __ZDBGTOOLS_H__
#define __ZDBGTOOLS_H__

#ifndef __ZD3D_H__
#include "z3d.h"
#endif

#ifndef __ZGRAFIX_H__
#include "zGrafix.h"
#endif

extern zBOOL showDebug;

enum TDebug { D_SPY,D_SCREEN,D_WIN };

void D_Reset();
void D_Print(const zPOINT3 &p,const zSTRING &msg=zSTRING(""),const TDebug mode = D_WIN);
void D_Print(const float &f,const zSTRING &msg=zSTRING(""),const TDebug mode = D_WIN);
void D_Print(zSTRING &ds,const TDebug mode = D_WIN);
void D_Print(char *ds,const TDebug mode = D_WIN);
void D_Print(char *ds, const int x, const int y);
void D_PrintA(char *ds,const int x, const int y) ;
void D_Print3D( const zPOINT3 &coord, zSTRING &s , const zCOLOR &col=GFX_RED );
void D_DrawPolyWire( const zCPolygon &poly, const zCOLOR &col=GFX_WHITE );
void D_ClrWin();

#endif