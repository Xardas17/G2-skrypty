/******************************************************************************** 
 
     $Workfile:: zError.h              $               $Date:: 4.12.00 18:22    $
     $Revision:: 13                    $            $Modtime:: 4.12.00 18:17    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Fundamental error-class sending spy-messages and showing error-dialogs
 
 * $Log: /current_work/ZenGin/_Bert/zError.h $
 * 
 * 13    4.12.00 18:22 Moos
 * 
 * 12    21.11.00 17:35 Speckels
 * 
 * 11    10.10.00 15:47 Speckels
 * 
 * 10    28.09.00 19:16 Hildebrandt
 * 
 * 9     11.09.00 20:51 Speckels
 * 
 * 8     8.09.00 17:37 Hildebrandt
 * fixed minor compiler warnings
 * 
 * 7     28.08.00 15:15 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 5     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 4     10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 6     17.04.00 17:13 Speckels
 * 
 * 5     30.03.00 14:23 Speckels
 * 
 * 7     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 6     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 5     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 4     21.10.99 23:26 Speckels
 * New macros and message-format
 * 
 * 3     25.09.99 18:11 Speckels
 * 
 * 2     24.09.99 20:40 Speckels
 * VSS-kompatiblen Header eingef�gt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 13 $ ($Modtime: 4.12.00 18:17 $)

#ifndef __ZERROR_H__
#define __ZERROR_H__

#ifndef _INC_FSTREAM
#include <fstream>
#endif

#ifndef __ZSTRING_H__
#include <zstring.h>
#endif

#ifndef _INC_ERRNO
#include <errno.h>
#endif

#ifndef __ZTYPES_H__
#include <ztypes.h>
#endif

#ifndef __ZWIN32_H__
#include "zWin32.h"
#endif

class zFILE;
class zCMutex;

typedef int zERROR_ID;

const zERROR_ID zERR_NONE    = 0; // equals FALSE = NO ERROR
const zERROR_ID zERR_NO      = 1; // equals FALSE = NO ERROR
const zERROR_ID zERR_UNKNOWN = 2; // equals TRUE  = YES, THERE IS AN ERROR


/*

  Parameter:
  - zlog:level,target,authors
    
*/

enum zERROR_TYPE { zERR_TYPE_OK, zERR_TYPE_INFO, zERR_TYPE_WARN, zERR_TYPE_FAULT, zERR_TYPE_FATAL };

// Temp: Nur noch zu Kompatibilit�tszwecken
enum zERROR_LEVEL { zERR_OK, zERR_INFO, zERR_WARN, zERR_FAULT, zERR_FATAL };

// Target-Flags

enum
{
	zERR_TARGET_SPY			= 1<<0,
	zERR_TARGET_FILE		= 1<<1
};


// Flags
enum
{	
	zERR_BEGIN		= 1<<0,
	zERR_END		= 1<<1
};


// Standard Levels

const int	zERR_LV_NONE			= -1;

// separating complex processes
const int	zERR_LV_SECTION			=  1;	
const int	zERR_LV_SUBSECTION		=  3;
									
// loading files					
const int	zERR_LV_LOADSECTION		=  2;
const int	zERR_LV_LOADFILE1		=  3;	// important
const int	zERR_LV_LOADFILE2		=  4;	// less important
const int	zERR_LV_LOADFILE3		=  5;	// the least imporant

// some routine-levels (messages inside some routines)
const int	zERR_LV_ROUTINE1		=  4;	// important
const int	zERR_LV_ROUTINE2		=  5;	// less important
const int	zERR_LV_ROUTINE3		=  6;	// the least imporant

// function-calls and more
const int	zERR_LV_NEWOBJECT		=  8;	// calling the constructor of an object (creating it)
const int	zERR_LV_FUNCENTER		=  9;	// calling a function
const int	zERR_LV_FUNCLEAVE		= 10;	// leaving a function

// other priorrities:
const int	zERR_LV_DETAIL			= 10;	// very deteiled informations
const int	zERR_LV_IMPORTANT		=  1;	// very important information


const int	zERR_LV_DEFAULT			=  5;	


typedef struct
{
	char*	HeaderText;
	char*	AssertText;
	char*	File;
	zDWORD	Line;
	char*	Reason;
	void*	extInfo;
} ASSERT_FAIL_INFO, *LPASSERT_FAIL_INFO;




// message-makros (similar to methods of the error-class)

#ifdef GOLDMASTER_NOZSPY
#define zERR_MESSAGE(level, flag, text)		
#define zERR_WARNING(text)					
#else
#define zERR_MESSAGE(level, flag, text)		((level)<=zerr.GetFilterLevel()) ? zerr.Report(zERR_TYPE_INFO,  0, text, level, flag, __LINE__,  __FILE__, 0 ) : zERR_NONE
#define zERR_WARNING(text)					zerr.Report(zERR_TYPE_WARN,  0, text, 0, 0, __LINE__,  __FILE__, 0 )
#endif

#define zERR_FAULT(text)					zerr.Report(zERR_TYPE_FAULT, 0, text, 0, 0, __LINE__,  __FILE__, 0 )
#define zERR_FATAL(text)					zerr.Report(zERR_TYPE_FATAL, 0, text, -1, 0, __LINE__,  __FILE__, 0 )

#define zERR_FAULT_ONCE(text)				{static bool ignore=false;if (!ignore) zerr.Report(zERR_TYPE_FAULT, 0, text, 0, 0, __LINE__,  __FILE__, 0 );ignore=true; };

#define zERR_BLOCK_BEGIN();
#define zERR_BLOCK_END();

///
// asserts
///

#define zERR_ASSERT_STRICT(e)			if (!(e)) { DEBUG_BREAK(); ASSERT_FAIL(#e, __FILE__, __LINE__, NULL); }
#define zERR_ASSERTT_STRICT(e,t)		if (!(e)) { DEBUG_BREAK(); ASSERT_FAIL(#e, __FILE__, __LINE__, (t)); }
#define zERR_BOUNDS_STRICT(var,l,h)		if (((var)<(l)) || ((var)>(h))) { DEBUG_BREAK(); BOUNDS_FAIL(#var, var, l, h, __FILE__, __LINE__, NULL); }
#define zERR_BOUNDST_STRICT(var,l,h,t)  if (((var)<(l)) || ((var)>(h))) { DEBUG_BREAK(); BOUNDS_FAIL(#var, var, l, h, __FILE__, __LINE__, (t)); }

// compile-time assert (produces no runtime-code!)  [HILDEBRANDT]
#define zERR_CASSERT(expn)				typedef char __C_ASSERT__[(expn)?1:-1]

#ifdef _DEBUG	
	#define zERR_ASSERT(e)				zERR_ASSERT_STRICT(e)
	#define zERR_ASSERTT(e,t)			zERR_ASSERTT_STRICT(e,t)
	#define zERR_BOUNDS(var,l,h)		zERR_BOUNDS_STRICT(var,l,h)
	#define zERR_BOUNDST(var,l,h,t)		zERR_BOUNDST_STRICT(var,l,h,t)
	#define zERR_ASSERTT_ONCE(e,t)			{ static bool ignore=false;if (!ignore) zERR_ASSERTT_STRICT(e,t);ignore=true;};
	#define zERR_BOUNDST_ONCE(var,l,h,t)	{ static bool ignore=false;if (!ignore) zERR_BOUNDST_STRICT(var,l,h,t);ignore=true;};
#else 
	#define zERR_ASSERT(e)					((void)(0))
	#define zERR_ASSERTT(e,t)				((void)(0))
	#define zERR_BOUNDS(var,l,h)			((void)(0))
	#define zERR_BOUNDST(var,l,h,t)			((void)(0))
	#define zERR_ASSERTT_ONCE(e,t)			((void)(0))
	#define zERR_BOUNDST_ONCE(var,l,h,t)	((void)(0))
#endif

///
// bounds-checking
///


// functionscalls (entering and leaving function)

#define zERR_FUNC_ENTER(level,funcname) zERR_MESSAGE(level, zERR_LV_FUNCENTER, funcname)
#define zERR_FUNC_LEAVE(level,funcname) zERR_MESSAGE(level, zERR_LV_FUNCLEAVE, funcname)

///
// Error-Class
///
class zERROR
{
		
public:
		zERROR();
		virtual ~zERROR();

		void Init(zSTRING parmlist);

		zERROR_ID Report(zERROR_LEVEL xLevel,zERROR_ID xId,const zSTRING& xMessage, signed char level=5, unsigned int flag=0, int line =0, char* file=0, char* function=0);
		zERROR_ID Report(zERROR_TYPE xLevel,zERROR_ID xId,const zSTRING& xMessage, signed char level=5, unsigned int flag=0, int line =0, char* file=0, char* function=0);
		
		zERROR_ID Message(const zSTRING& str);	// old method for reporting informations
		zERROR_ID Warning(const zSTRING& str);	// old method for reporting warnings
		zERROR_ID Fatal(const zSTRING& str);	// old method for reporting fatals
		zERROR_ID Fault(const zSTRING& str);	// old method for reporting faults

		// Setting parameters for reporting messages

		void SetTarget(int target_flag);
		void SetFilterFlags(zDWORD flag=0);
		void SetFilterAuthors(zSTRING authors="ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		void SetFilterLevel(int max_level=zERR_LV_NONE);

		// Getting parameters for reporting messages

		zSTRING GetTargetDescription();
		zSTRING GetFilterFlagDescription();
		zSTRING GetFilterAuthors();
		int		GetFilterLevel()		{ return filter_level;};

		// Spy

		void Separator(zSTRING titel="");
		void ShowSpy(BOOL show);		


		bool SearchForSpy();
		void SendToSpy(zSTRING& s);

		// Acknowledge errors with a windows-dialog

		zERROR_TYPE		GetAck ()							{ return ack_type;		}
		zERROR_TYPE		SetAck (zERROR_TYPE _ack_type)		{ zERROR_TYPE old = ack_type;ack_type = _ack_type;return old; }
		
		void			SetExitFunction(void (*func)())		{ onexit = func;		}
				
private:				
	
		void	BlockBegin(char* file, int line);
		void	BlockEnd(char* file, int line);

		void (*onexit)();
			
		zSTRING			filter_authors;
		unsigned int	filter_flag;
		signed char	filter_level;
		int				target;

		zERROR_TYPE		ack_type;

		zFILE*			log_file;
		
		zBYTE			indent_depth;

		HWND			spyHandle;
		zCMutex*		spyMutex;
};

extern zERROR zerr;


#endif
