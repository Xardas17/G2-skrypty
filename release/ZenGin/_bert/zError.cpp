/******************************************************************************** 
 
     $Workfile:: zError.cpp           $                $Date:: 15.02.01 21:17   $
     $Revision:: 28                   $             $Modtime:: 15.02.01 18:44   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/zError.cpp $
 * 
 * 28    15.02.01 21:17 Speckels
 * 
 * 27    7.12.00 17:40 Moos
 * 
 * 26    21.11.00 17:35 Speckels
 * 
 * 25    21.11.00 15:22 Speckels
 * 
 * 24    3.11.00 15:04 Speckels
 * 
 * 23    2.11.00 16:14 Speckels
 * 
 * 22    28.09.00 19:52 Hildebrandt
 * 
 * 21    11.09.00 20:51 Speckels
 * 
 * 20    6.09.00 21:04 Speckels
 * 
 * 19    6.09.00 18:22 Speckels
 * 
 * 18    1.09.00 16:05 Rueve
 * 
 * 17    28.08.00 14:24 Speckels
 * 
 * 19    24.08.00 17:11 Speckels
 * 
 * 18    23.08.00 21:47 Admin
 * 
 * 15    21.08.00 18:26 Speckels
 * 
 * 16    16.08.00 12:32 Admin
 * 
 * 14    10.08.00 21:47 Speckels
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 13    21.07.00 15:16 Speckels
 * 
 * 12    19.07.00 17:43 Speckels
 * 
 * 11    12.07.00 13:16 Speckels
 * 
 * 10    12.07.00 13:09 Speckels
 * 
 * 9     12.07.00 13:06 Speckels
 * 
 * 8     10.07.00 15:24 Speckels
 * 
 * 4     9.05.00 20:20 Speckels
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 4     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 3     20.04.00 17:51 Speckels
 * zSpy renamed to [zSpy]
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 7     17.04.00 17:13 Speckels
 * 
 * 6     12.04.00 16:06 Speckels
 * Threadsafe Errorclass (first try)
 * 
 * 5     30.03.00 14:23 Speckels
 * 
 * 11    7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 8     4.12.99 20:49 Speckels
 * more implementation of the central networkmanager
 * 
 * 7     3.12.99 12:49 Speckels
 * fixed small bug in message-report
 * 
 * 6     3.12.99 12:23 Speckels
 * using UDP-communication only of parameter -zloghost:HOSTNAME found
 * 
 * 5     2.12.99 22:49 Speckels
 * UDP-Kommunikation mit dem Spy
 * 
 * 4     16.11.99 11:42 Speckels
 * Item/MOB-Interaktion, Pre-Release Netzwerk
 * 
 * 3     21.10.99 23:26 Speckels
 * New macros and message-format
 * 
 * 
 ***********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 28 $ ($Modtime: 15.02.01 18:44 $)

#include "zcore.h"
#include "zerror.h"

#include <iostream>
#include <conio.h>

#include <windows.h>

#include <time.h>

#include "zdisk.h"
#include "zview.h"
#include "zoption.h"
#include "zspytypes.h"
#include "zqueue.h"
#include "zthread.h"

static zQUEUE<zSTRING> zErrBlockStack;

unsigned int WM_LOGMSG;
unsigned int WM_LOGCOMMAND;

zTErrorMessage	msg;

void default_exit()
{
	exit(1);
}
 
// [EDENFELD] neu 1.33 aus Spacer ModSource: FATAL Errors sind immer TopMost
void ErrorBox(zSTRING s)
{
	s = "\n" + s + "\n";
	int i = s.Search(")");
	if (i>=0) s.Insert(i+1,"\n\n");
	if (s[i+3]==' ') s.Delete(i+3,1);

	// static zSTRING lastErrorMessage;
	// long timedif = 0;

#ifndef COMPILING_SPACER
	if (zrenderer) zrenderer->Vid_SetScreenMode(zRND_SCRMODE_WINDOWED);
#endif

	// if ((lastErrorMessage != s) || (timedif>10000)) // andere Meldung oder mehr als 10 Sek vergangen?
	{
		MessageBox(::GetFocus(),s.ToChar(), "Error-Message", MB_OK | MB_TOPMOST | MB_APPLMODAL);
	//	lastErrorMessage = s;
	}
}

void MessageWindow(zSTRING s)
{
	// cout << s << "\n";
	// cout.flush(); 
}

static time_t start_time;

SOCKET sendSock;

void GetDiffTime(zSTRING& s)
{
	time_t ltime;time( &ltime );
	double time = difftime(ltime,start_time);
	s = zSTRING(int(time/60)) + zSTRING(":") + zSTRING((int)time%60);	
}


zERROR::zERROR()
{
	spyMutex = zNEW(zCMutex);
	
	SearchForSpy();
	if (spyHandle) ::SetForegroundWindowEx(spyHandle);

	filter_authors.Clear();			
	filter_authors  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	filter_level	= -1;
	filter_flag		= 0;
	target			= zERR_TARGET_SPY;
	
	log_file		= NULL;
	indent_depth	= 0;

	ack_type		= zERR_TYPE_FAULT;

	// Window-Messages
	WM_LOGMSG		= RegisterWindowMessage("WM_LOGMSG");
	WM_LOGCOMMAND	= RegisterWindowMessage("WM_LOGCOMMAND");	
	
	// Exit-Function
	onexit = &default_exit;		
	
	char zeit[9];_strtime(zeit);	
	
	time( &start_time );
}

void zERROR::Init(zSTRING parmlist)
{		
	// check if zlog-Parameter is given
	//	format:  -zlog:##,SFG,A-Z
	//	example: -zlog:10,SF,UDB
	parmlist.Upper();

	if (parmlist.Search("-ZLOG:")>=0)
	{
		zSTRING zlogValue = parmlist;
		zlogValue.Delete("-ZLOG:",zSTR_TO);
		zlogValue.Delete(" ",zSTR_FROM);
				
		zSTRING levelStr  = zlogValue.PickWord(1,",",",");
		zSTRING targetStr = zlogValue.PickWord(2,",",",");
		zSTRING authorStr = zlogValue.PickWord(3,",",",");		
		
		// target
		if (!targetStr.IsEmpty())
		{		
			int target = 0;
			if (targetStr.Search("S")>=0) target = target | zERR_TARGET_SPY;
			if (targetStr.Search("F")>=0) target = target | zERR_TARGET_FILE;
			SetTarget(target);
		}
		else SetTarget(0);
		
		// level
		if (!levelStr.IsEmpty()) 
			SetFilterLevel(levelStr.ToInt());
		else 
			SetFilterLevel(-1);
				
		// author
		if (!authorStr.IsEmpty()) 
			SetFilterAuthors(authorStr);
		else 
			SetFilterAuthors("ABCDEFGHIJKLMNOPQRSTUVWXYZ");						
	};	

	SearchForSpy();

	zSTRING str("START");
	ATOM atom = GlobalAddAtom(str.ToChar());
	SendMessage(HWND_BROADCAST,WM_LOGCOMMAND,0,(LPARAM)atom );
	while (GlobalDeleteAtom(atom));

	ack_type = zERR_TYPE_FATAL;

	if (filter_level>0)
	{	
		ShowSpy(TRUE);	

		ack_type = zERR_TYPE_FAULT;
	}

};

zERROR::~zERROR()
{		
	Separator();
	ShowSpy(FALSE);		

	if (log_file)
	{
		if (log_file->IsOpened()) log_file->Close();
		delete log_file;
		log_file = 0;
	};	

	delete spyMutex;
	spyMutex = 0;

    // [Moos] 12.7.00 Leakfix; poppe den Stack ganz und gar.
    while (indent_depth>0 &&  !zErrBlockStack.IsEmpty())
        delete zErrBlockStack.PopLast();
}


void zERROR::SendToSpy(zSTRING& s)
{	
	/*
	ATOM atom = GlobalAddAtom(s.ToChar());
	SendMessage(HWND_BROADCAST,WM_LOGMSG,0,(LPARAM)atom );
	while (GlobalDeleteAtom(atom));
	*/		

	if (spyHandle && spyMutex)
	{
		COPYDATASTRUCT data;	
		data.lpData = s.ToChar();
		data.cbData = strlen( (char*) data.lpData) + 1;

		spyMutex->Lock();
			
		SendMessage(spyHandle,WM_COPYDATA,(WPARAM)0,(LPARAM)&data);
			
		spyMutex->Unlock();
	}
};


zERROR_ID zERROR::Report(zERROR_LEVEL _type,zERROR_ID xId,const zSTRING& str_text, signed char levelPrio, unsigned int flag, int line, char* file, char* function)
{
	return Report((zERROR_TYPE)_type, xId, str_text, levelPrio, flag, line, file, function);
};

zERROR_ID zERROR::Report(zERROR_TYPE type,zERROR_ID id,const zSTRING& str_text, signed char levelPrio, unsigned int flag, int line, char* file, char* function)
{			
 	if ((filter_level<0) && (type!=zERR_FATAL)) return id;

	// 	
	// Autoren filtern ...
	//
	
	zBOOL isAuthor = (str_text.Length()>=2) && (str_text[1]==':');	
	
	if (
				(type!=zERR_TYPE_INFO)			
			||	(isAuthor && (levelPrio<=filter_level) && (filter_authors.Search(str_text[0])>=0))
		)			
	{

		zSTRING str="";
		
		//
		// message-type auswerten
		// 
		switch (type)
		{
			case zERR_TYPE_INFO:	str += "Info: ";break;
			case zERR_TYPE_WARN:	str += "Warn: ";break;
			case zERR_TYPE_FAULT:	str += "Fault:";break;
			case zERR_TYPE_FATAL:	str += "Fatal:";break;
			default:				str += "?????:";break;
		}			
				
		//
		// level-priority and indent
		//
		str += zSTRING(levelPrio).Align(zSTR_RIGHT,2);			
		str += " ";
		str += str_text.Inserted(2,Characters(' ',indent_depth*2));					
		
		//
		// fileinfo	
		//
		// if ((type!=zERR_TYPE_INFO) && (file))
		if (file)
		{			
			str += " .... ";
			zSTRING str_fileinfo = file;
			str_fileinfo.Delete(0,str_fileinfo.SearchRev("\\")+1);
			str_fileinfo = "<"+str_fileinfo+",#"+zSTRING(line);
			if (function) str_fileinfo = ","+str_fileinfo+","+function;
			str_fileinfo = str_fileinfo+">";			
			str+=str_fileinfo;
		}
		
		//
		// Message an die Targets ausgeben ...
		//

		if (target & zERR_TARGET_SPY)	SendToSpy(str);			
		if (target & zERR_TARGET_FILE)	if (log_file) log_file->Write(str+"\n");
		
		//
		// Fehler als Dialog anzeigen? (Acknowledgement)
		//
		if (type>=ack_type)
		{
			if (zrenderer)	zrenderer->Vid_SetScreenMode(zRND_SCRMODE_HIDE);						
			ErrorBox(str_text);
		}
	};

	//
	// Spiel verlassen?
	//
	if (type==zERR_TYPE_FATAL)				
	{
		onexit();	
	}
	
	//
	// Block-Begin und -Ende 
	//
	if ( (flag & zERR_BEGIN)	== zERR_BEGIN)	BlockBegin	(file, line);				
	if ( (flag & zERR_END)		== zERR_END)	BlockEnd	(file, line);
		
	return id;
}

void zERROR::BlockBegin(char* file, int line)
{
	if (indent_depth<255) 
	{	
		zSTRING* filename = zNEW(zSTRING(file));
		zErrBlockStack.Push(filename);
		indent_depth++;		
	}
	else 
	{
		zERR_WARNING("B: ERR: indent-depth out of bound (>255).");
	}	
};

void zERROR::BlockEnd(char* file, int line)
{
	zSTRING* filename;
	if (indent_depth<=0 || zErrBlockStack.IsEmpty())
	{
		zERR_WARNING("B: ERR: BLOCK-END unexpected: "+zSTRING(file)+" line "+zSTRING(line));
		return;
	};
	filename = zErrBlockStack.PopLast();
	if (strcmp(filename->ToChar(),file)!=0)
	{
		zERR_WARNING("B: ERR: BLOCK-END in "+(*filename)+" missed: at BLOCK-END in "+zSTRING(file)+" line "+zSTRING(line) );
		delete filename;filename = 0;
		return;
	};
	delete filename;filename=0;
	indent_depth--;			
};

void zERROR::Separator(zSTRING titel)
{
	if (filter_level<=0) return;

	zSTRING str = "---------------";

	SendToSpy(str);
	
	if (!titel.IsEmpty())
	{
		zERR_MESSAGE(zERR_LV_SECTION,0,"          "+titel);		
		Separator();
	};
}

void zERROR::ShowSpy(BOOL show)
{
	if (filter_level<=0) return;

	zSTRING str;
	if (show) str="SHOW"; else str="HIDE";
	
	ATOM atom = GlobalAddAtom(str.ToChar());
	SendMessage(HWND_BROADCAST,WM_LOGCOMMAND,0,(LPARAM)atom );
	while (GlobalDeleteAtom(atom));	
}

zERROR_ID zERROR::Message(const zSTRING& str)
{	
#ifndef GOLDMASTER
	return zERR_MESSAGE(5,zERR_NONE,str);
#else
	return TRUE;
#endif
}

zERROR_ID zERROR::Warning(const zSTRING& str)
{
#ifndef GOLDMASTER
	return zERR_WARNING(str);	
#else
	return TRUE;
#endif

};

zERROR_ID zERROR::Fatal(const zSTRING& str)
{	
	return zERR_FATAL(str);	
};

zERROR_ID zERROR::Fault(const zSTRING& str)
{	
	return zERR_FAULT(str);	
};




void zERROR::SetFilterFlags(zDWORD flag)
{
	filter_flag = flag;
	zERR_MESSAGE(0,0,"B: ERR: SetFilterFlags   "+GetFilterFlagDescription());
};

void zERROR::SetFilterAuthors(zSTRING authors)
{
	filter_authors = authors;
	filter_authors = filter_authors;
	zERR_MESSAGE(0,0,"B: ERR: SetFilterAuthors "+zSTRING(filter_authors));
};

/*	------------------------------------------------------------------
	void zERROR::SetFilterLevel(int max_level)

	29.09.00	[HILDEBRANDT]	
				Level der zERR_MESSAGE drastisch reduziert
	------------------------------------------------------------------ */

void zERROR::SetFilterLevel(int max_level)
{	
	filter_level = max_level;
	zERR_MESSAGE(10,0,"B: ERR: SetFilterLevel   "+zSTRING((int)filter_level));
};

void zERROR::SetTarget(int _target)
{	
	target = _target;
	
	if (target & zERR_TARGET_FILE)
	{		
		if (!log_file) 
		{
			char name[200];
			unsigned long nameSize = sizeof(name);
			GetUserName(name,&nameSize);
			zSTRING username = zSTRING(name);username.Lower();
			
			log_file = zNEW(zFILE_FILE("c:\\errorlog_by_"+username+".txt"));
			log_file->Create();		
		}
		
	};
	
	zERR_MESSAGE(0,0,"B: ERR: SetTarget        "+GetTargetDescription());
};

zSTRING zERROR::GetTargetDescription()
{
	zSTRING targetStr="[";
	if (target & zERR_TARGET_SPY) targetStr+="SPY ";
	if (target & zERR_TARGET_FILE) targetStr+="FILE ";
	targetStr+="]";
	return targetStr;
};

zSTRING zERROR::GetFilterFlagDescription()
{
	zSTRING flagStr="[";
	
	flagStr+=zSTRING((int)filter_flag);
	flagStr+="]";
	return flagStr;
};

zSTRING zERROR::GetFilterAuthors()
{
	return filter_authors;
};

bool zERROR::SearchForSpy()
{	
	spyHandle = ::FindWindow(0,"[zSpy]");
	if (spyHandle)
	{
		this->Message("B: ZERR: Spy found.");		
	};

	/*
	#if !defined(FINAL_RELEASE) || defined(DEBUG_SPECKELS)
		if (!spyHandle && (filter_level>0))
		{		
			MessageBox(NULL,"zSpy not found.\r\n\r\nPlease start zSpy now, then click OK ...","Searching zSpy", MB_OK);
			spyHandle = ::FindWindow(0,"[zSpy]");
		};
	#endif
	*/

	return (spyHandle != NULL);
};
