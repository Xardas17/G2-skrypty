// spcCCompileAction.h: interface for the spcCCompileAction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPCCCOMPILEAKTION_H__F7F40944_2D1E_11D2_88A8_0080AD209698__INCLUDED_)
#define AFX_SPCCCOMPILEAKTION_H__F7F40944_2D1E_11D2_88A8_0080AD209698__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class spcCCompileWorldAction
{
public:
	BOOL valid;  // are the options valid?

	BOOL detectLeaks;
	BOOL polycheck;
	BOOL editormode;
	int inout;
	BOOL quick;

	BOOL force;  // force to compile with this options?

	spcCCompileWorldAction() { valid=false;force=false; };
};

class spcCCompileLightAction
{
public:
	BOOL vertex_only;
	BOOL region;
	BOOL dynCompile;
	int region_value;
	int  lightmap_level;


	spcCCompileLightAction() 
	{ 
		region		= false;
		dynCompile	= false;
		region_value = 15;
		lightmap_level=1; 
		vertex_only = false; 
	};
};

#endif