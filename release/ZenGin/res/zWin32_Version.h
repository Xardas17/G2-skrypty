#pragma once

// used for code / resources

#ifndef COMPILING_SPACER
	#define _APP_NAME			"Gothic II"
#else
	#define _APP_NAME			"Spacer II"
#endif

#define	_APP_VERSION_MAJOR	2
#define _APP_VERSION_MINOR	6
#define _APP_VERSION_POINT	0		// 0 - public, x - intern
#define _APP_VERSION_STR	"2.6"
// 0 - german, 1 - english, 2 - demo german, 3 - demo english
#ifdef LANG_ENU
	#define _APP_VERSION_INT	1
#else
	#define _APP_VERSION_INT	0
#endif

#define __APP_FULLNAME(a, v)	\
	a							\
	" - "						\
	v
#if defined(_DEBUG)
	#define __APP_VERSION(v)	\
		v						\
		" (dbg)"
#elif defined(GOTHIC_DEMO)
	#define __APP_VERSION(v)	\
		v						\
		" (demo)"
#elif defined(GOTHIC_MODKIT)
	#define __APP_VERSION(v)	\
		v						\
		" (mod)"
#elif defined(GOLDMASTER) || defined(COMPILING_SPACER)
	#define __APP_VERSION(v)	\
		v
#else
	#define __APP_VERSION(v)	\
		v						\
		" (dev)"
#endif


#define _APP_VERSION	__APP_VERSION(_APP_VERSION_STR)
#define _APP_FULLNAME	__APP_FULLNAME(_APP_NAME, _APP_VERSION)
#define _APP_PROGRAM	"Gothic II"
#define _APP_COMPANY	"Piranha Bytes"
#define _APP_COPYRIGHT	"Copyright © 2002,2003 Pluto 13 GmbH"


// used for registry

#ifndef COMPILING_SPACER
	#define _REG_COMPANY	"Piranha Bytes"
	#define _REG_PROGRAM	"Gothic II"
	#define _REG_VERSION	_APP_VERSION
#else
	#define _REG_COMPANY	"Piranha Bytes"
	#define _REG_PROGRAM	"Spacer II"
	#define _REG_VERSION	_APP_VERSION
#endif


// used for resources

#define _APP_RCVERSION	_APP_VERSION_MAJOR,_APP_VERSION_MINOR,_APP_VERSION_POINT,_APP_VERSION_INT
