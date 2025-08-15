
//#include <windows.h>
//#include <stdio.h>
//#include <tchar.h>
//#include "special.h"

SVKP_ENCRYPTED_BLOCK_TYPE1_START
				TCHAR SVKP_EventName[10] = {_T('E'), _T('V'), _T('_')};
				_itot(6666, &SVKP_EventName[3], 10);
				HANDLE SVKP_hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, SVKP_EventName);
				if ((NULL == SVKP_hEvent) || (WAIT_OBJECT_0 != WaitForSingleObject(SVKP_hEvent, 0)))
				{
