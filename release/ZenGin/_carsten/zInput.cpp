/******************************************************************************** 
 
     $Workfile:: zInput.cpp   $              $Date:: 10.02.01 17:58  $
     $Revision:: 18                   $             $Modtime:: 10.02.01 17:48 $
     $Author:: Speckels               $
	 Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description: abstrakte allgemeine Input Klasse für 
				analoge und digitale Eingabegeräte

 * $Log: /current_work/ZenGin/_Carsten/zInput.cpp $
 * 
 * 18    10.02.01 17:58 Speckels
 * 
 * 17    9.02.01 13:38 Speckels
 * 
 * 16    6.02.01 20:35 Speckels
 * 
 * 15    6.02.01 20:18 Speckels
 * 
 * 14    6.02.01 15:26 Speckels
 * 
 * 13    6.02.01 15:25 Speckels
 * 
 * 12    6.02.01 2:28 Speckels
 * 
 * 11    6.02.01 0:44 Speckels
 * 
 * 10    5.02.01 23:18 Speckels
 * 
 * 9     5.02.01 22:20 Speckels
 * 
 * 8     3.02.01 4:11 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 18 $ ($Modtime: 10.02.01 17:48 $)

// =======================================================================================================================

#include "zcore.h"
#include "zinput.h"
#include "zoption_const.h"
#include "zoption.h"

zCInput *zinput = 0;

zCArray	<zSCtrlValue>  zCInput :: values;

zCInput::zCInput()
{
	mapList.SetCompare(CompareKeyMaps);
	InitializeControlValues();
};

// virtueller destruktor, wird dieser aufgerufen ??? [Moos->] Ja, das wird er.
zCInput::~zCInput()
{
    for(int i=mapList.GetNum()-1;i>=0;i--)
        delete mapList[i]; // [Moos]

	mapList.DeleteList();
};

// static compare func
int zCInput::CompareKeyMaps(const void *val1, const void *val2)
{
	return ( (*(zSKeyMapping**)val1)->logicalID - (*(zSKeyMapping**)val2)->logicalID);
};

void zCInput ::	Bind(const zWORD logicalID, const zCArray <zWORD>&controlValueList)
{
	zSKeyMapping *map = zNEW( zSKeyMapping );
	map->logicalID		= logicalID;
	map->controlValues	= controlValueList;
	map->set			= FALSE;
	mapList.InsertSort(map);
};

/* ----------------------------------------------------------------------
	
    zCInput::BindOption()

	28.08.2000	[Moos]	
                delete[] buffer; dazu


   ---------------------------------------------------------------------- */

void zCInput::BindOption(const zSTRING optionID, const zWORD logicalID, zCArray<zWORD>controlValueList )
{
	void*buffer=0;
	zDWORD bindSize;
	bindSize = zoptions->ReadRaw(zOPT_SEC_KEYS,optionID.ToChar(),buffer,controlValueList.GetArray(),controlValueList.GetNumInList()<<1);
	controlValueList.DeleteList();
	for (int i=0; i<bindSize>>1; i++)
		// [BENDLIN] Addon Patch2 - Empty Key Bindings
		if (((zWORD*)buffer)[i] != 0)
			controlValueList.Insert(((zWORD*)buffer)[i]);
	Unbind(logicalID);
	Bind(logicalID,controlValueList);
    delete[] buffer; // [Moos]
};

void zCInput ::	Unbind(const zWORD logicalID)
{
	zSKeyMapping map;
	map.logicalID = logicalID;
	int index = mapList.Search(&map);
	if (index != -1) {
		zSKeyMapping *map = mapList[index];
		mapList.RemoveOrderIndex(index);
		delete map;
	};
};



zBOOL zCInput :: IsBinded(const zWORD logicalID, const zWORD keyID)
{
	zSKeyMapping map;
	map.logicalID = logicalID;
	int index = mapList.Search(&map);
	if (index != -1) {
		for (int i=0; i<mapList[index]->controlValues.GetNumInList(); i++) {
			if (mapList[index]->controlValues[i] == keyID) return TRUE;
		}
	}
	return FALSE;
};

////////////////////////////////////////////////////////////////////////////////
//
//	zCInput::InitializeControlValues
//
//	2002-05-11	[BENDLIN] introduced
//
////////////////////////////////////////////////////////////////////////////////

zBOOL zCInput::IsBindedToggled(const zWORD logicalID, const zWORD keyID)
{
	return ( IsBinded(logicalID, keyID) && GetToggled(logicalID) );
}

zBOOL zCInput :: GetBinding(const zWORD logicalID, zCArray <zWORD>&controlValueList)
{
	zSKeyMapping map;
	map.logicalID = logicalID;
	int index = mapList.Search(&map);
	if (index != -1) {
		controlValueList = mapList[index]->controlValues;
		return TRUE;
	}
	return FALSE;
};

zWORD zCInput :: GetFirstBindedLogicalKey(const zWORD keyID)
{
	int mapIndex,controlValueIndex;

	for (mapIndex = 0; mapIndex < mapList.GetNum(); mapIndex++)
		for (controlValueIndex = 0; controlValueIndex < mapList[mapIndex]->controlValues.GetNum(); controlValueIndex++)
			if (mapList[mapIndex]->controlValues[controlValueIndex] == keyID)
				return mapList[mapIndex]->logicalID;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
//	zCInput::InitializeControlValues
//
//	2002-05-11	[BENDLIN]
//
//				Mouse buttons added
//				Mouse X-buttons added
//				Mouse button moved to the beginning of the list
//
////////////////////////////////////////////////////////////////////////////////

// TODO: order by estimated usage

// [BENDLIN] prepared for other keyboard layouts
void zCInput :: InitializeControlValues()
{
	// spannend: alle konstanten bezeichnen

	zSCtrlValue v;

	// get keyboard layout from ini
	// TODO: property of zinput
	bool german;
	{
		DWORD germanKeyboardLayout = 0x07040000;
		DWORD usintlKeyboardLayout = 0x09040200;
		
		static DWORD keyboardLayout = 0xFFFFFFFF;
		if (keyboardLayout == 0xFFFFFFFF)
		{
			void* buffer = 0;
#ifdef	LANG_ENU
			int size = zoptions->ReadRaw(zOPT_SEC_GAME, "keyboardLayout", buffer, &usintlKeyboardLayout, sizeof(usintlKeyboardLayout));
#else
			int size = zoptions->ReadRaw(zOPT_SEC_GAME, "keyboardLayout", buffer, &germanKeyboardLayout, sizeof(germanKeyboardLayout));
#endif
			if (buffer)
			{
				if (size == sizeof(keyboardLayout))
					keyboardLayout = (*(DWORD*)buffer);
				delete[] buffer;
			}
		}
		if ((keyboardLayout != germanKeyboardLayout) &&	// German
			(keyboardLayout != usintlKeyboardLayout))	// US-International
		{
#ifndef GOLDMASTER
			keyboardLayout = germanKeyboardLayout; // German is default
#else
	#ifdef	LANG_DEU
			keyboardLayout = germanKeyboardLayout; // German
	#elif	LANG_ENU
			keyboardLayout = usintlKeyboardLayout; // US-International
	#else
	#error	--- You have to specify the language for goldmasters! ---
	#endif
#endif
			zoptions->WriteRaw(zOPT_SEC_GAME, "keyboardLayout", &keyboardLayout, sizeof(keyboardLayout));
		}
		german = (keyboardLayout == germanKeyboardLayout);
	}

	////////////////////////////////////////////////////////////////
	//
	//	MOUSE
	//
	if (german)
	{
		// movement
		v.value = MOUSE_DX;				v.name="MAUS-X";		values.Insert(v);					
		v.value = MOUSE_DY;				v.name="MAUS-Y";		values.Insert(v);		
		v.value = MOUSE_WHEELUP;		v.name="MAUSRAD AUF";	values.Insert(v);
		v.value = MOUSE_WHEELDOWN;		v.name="MAUSRAD AB";	values.Insert(v);
		// buttons
		v.value = MOUSE_BUTTONLEFT;		v.name="MAUS LINKS";	values.Insert(v);
		v.value = MOUSE_BUTTONRIGHT;	v.name="MAUS RECHTS";	values.Insert(v);
		v.value = MOUSE_BUTTONMID;		v.name="MAUS MITTE";	values.Insert(v);
		v.value = MOUSE_XBUTTON1;		v.name="MAUS X1";		values.Insert(v);
		v.value = MOUSE_XBUTTON2;		v.name="MAUS X2";		values.Insert(v);
		v.value = MOUSE_XBUTTON3;		v.name="MAUS X3";		values.Insert(v);
		v.value = MOUSE_XBUTTON4;		v.name="MAUS X4";		values.Insert(v);
		v.value = MOUSE_XBUTTON5;		v.name="MAUS X5";		values.Insert(v);
	}
	else
	{
		// movement
		v.value = MOUSE_DX;				v.name="MOUSE-X";		values.Insert(v);					
		v.value = MOUSE_DY;				v.name="MOUSE-Y";		values.Insert(v);		
		v.value = MOUSE_WHEELUP;		v.name="WHEEL UP";		values.Insert(v);
		v.value = MOUSE_WHEELDOWN;		v.name="WHEEL DOWN";	values.Insert(v);
		// buttons
		v.value = MOUSE_BUTTONLEFT;		v.name="MOUSE LEFT";	values.Insert(v);
		v.value = MOUSE_BUTTONRIGHT;	v.name="MOUSE RIGHT";	values.Insert(v);
		v.value = MOUSE_BUTTONMID;		v.name="MOUSE MID";		values.Insert(v);
		v.value = MOUSE_XBUTTON1;		v.name="MOUSE X1";		values.Insert(v);
		v.value = MOUSE_XBUTTON2;		v.name="MOUSE X2";		values.Insert(v);
		v.value = MOUSE_XBUTTON3;		v.name="MOUSE X3";		values.Insert(v);
		v.value = MOUSE_XBUTTON4;		v.name="MOUSE X4";		values.Insert(v);
		v.value = MOUSE_XBUTTON5;		v.name="MOUSE X5";		values.Insert(v);
	}

	////////////////////////////////////////////////////////////////
	//
	//	KEYBOARD
	//
	{
		v.value = KEY_ESC;			v.name="ESC";			values.Insert(v);	// DIK_ESCAPE
		// function keys
		v.value = KEY_F1;			v.name="F1";			values.Insert(v);	// DIK_F1
		v.value = KEY_F2;			v.name="F2";			values.Insert(v);	// DIK_F2
		v.value = KEY_F3;			v.name="F3";			values.Insert(v);	// DIK_F3
		v.value = KEY_F4;			v.name="F4";			values.Insert(v);	// DIK_F4
		v.value = KEY_F5;			v.name="F5";			values.Insert(v);	// DIK_F5
		v.value = KEY_F6;			v.name="F6";			values.Insert(v);	// DIK_F6
		v.value = KEY_F7;			v.name="F7";			values.Insert(v);	// DIK_F7
		v.value = KEY_F8;			v.name="F8";			values.Insert(v);	// DIK_F8
		v.value = KEY_F9;			v.name="F9";			values.Insert(v);	// DIK_F9
		v.value = KEY_F10;			v.name="F10";			values.Insert(v);	// DIK_F10
		v.value = KEY_F11;			v.name="F11";			values.Insert(v);	// DIK_F11
		v.value = KEY_F12;			v.name="F12";			values.Insert(v);	// DIK_F12
		v.value = KEY_F13;			v.name="F13";			values.Insert(v);	// DIK_F13
		v.value = KEY_F14;			v.name="F14";			values.Insert(v);	// DIK_F14
		v.value = KEY_F15;			v.name="F15";			values.Insert(v);	// DIK_F15
	}
	if (german)
	{
		v.value = KEY_PRINT;		v.name="DRUCK";			values.Insert(v);	// DIK_SYSRQ
		v.value = KEY_SCROLLLOCK;	v.name="ROLLEN-FESTSTELL";	values.Insert(v);	// DIK_SCROLL
		v.value = KEY_PAUSE;		v.name="PAUSE";			values.Insert(v);	// DIK_PAUSE
		// arrow keypad
		v.value = KEY_INS;			v.name="EINFÜGEN";		values.Insert(v);	// DIK_INSERT
		v.value = KEY_HOME;			v.name="POS1";			values.Insert(v);	// DIK_HOME
		v.value = KEY_PGUP;			v.name="BILD-AUF";		values.Insert(v);	// DIK_PRIOR
		v.value = KEY_DEL;			v.name="ENTFERNEN";		values.Insert(v);	// DIK_DELETE
		v.value = KEY_END;			v.name="ENDE";			values.Insert(v);	// DIK_END
		v.value = KEY_PGDN;			v.name="BILD-AB";		values.Insert(v);	// DIK_NEXT
		v.value = KEY_UP;			v.name="NACH-OBEN";		values.Insert(v);	// DIK_UP
		v.value = KEY_LEFT;			v.name="NACH-LINKS";	values.Insert(v);	// DIK_LEFT
		v.value = KEY_DOWN;			v.name="NACH-UNTEN";	values.Insert(v);	// DIK_DOWN
		v.value = KEY_RIGHT;		v.name="NACH-RECHTS";	values.Insert(v);	// DIK_RIGHT
		// numeric keypad
		v.value = KEY_NUMLOCK;		v.name="NUM-FESTSTELL";	values.Insert(v);	// DIK_NUMLOCK
		v.value = KEY_PAD_DIV;		v.name="NUM DIV";		values.Insert(v);	// DIK_SLASH
		v.value = KEY_PAD_MUL;		v.name="NUM MUL";		values.Insert(v);	// DIK_MULTIPLY
		v.value = KEY_GREYMINUS;	v.name="NUM SUB";		values.Insert(v);	// DIK_SUBTRACT
		v.value = KEY_PAD_ENTER;	v.name="NUM ENTER";		values.Insert(v);	// DIK_NUMPADENTER
		v.value = KEY_PAD_DEL;		v.name="NUM ENTF";		values.Insert(v);	// DIK_DECIMAL
		v.value = KEY_PAD_INS;		v.name="NUM 0";			values.Insert(v);	// DIK_NUMPAD0
		v.value = KEY_PAD_END;		v.name="NUM 1";			values.Insert(v);	// DIK_NUMPAD1
		v.value = KEY_PAD_DOWN;		v.name="NUM 2";			values.Insert(v);	// DIK_NUMPAD2
		v.value = KEY_PAD_PGDN;		v.name="NUM 3";			values.Insert(v);	// DIK_NUMPAD3
		v.value = KEY_PAD_LEFT;		v.name="NUM 4";			values.Insert(v);	// DIK_NUMPAD4
		v.value = KEY_PAD_5;		v.name="NUM 5";			values.Insert(v);	// DIK_NUMPAD5
		v.value = KEY_PAD_RIGHT;	v.name="NUM 6";			values.Insert(v);	// DIK_NUMPAD6
		v.value = KEY_PAD_HOME;		v.name="NUM 7";			values.Insert(v);	// DIK_NUMPAD7
		v.value = KEY_PAD_UP;		v.name="NUM 8";			values.Insert(v);	// DIK_NUMPAD8
		v.value = KEY_PAD_PGUP;		v.name="NUM 9";			values.Insert(v);	// DIK_NUMPAD9
	}
	else
	{
		v.value = KEY_PRINT;		v.name="PRINT";			values.Insert(v);	// DIK_SYSRQ
		v.value = KEY_SCROLLLOCK;	v.name="SCROLLLOCK";	values.Insert(v);	// DIK_SCROLL
		v.value = KEY_PAUSE;		v.name="PAUSE";			values.Insert(v);	// DIK_PAUSE
		// arrow keypad
		v.value = KEY_INS;			v.name="INSERT";		values.Insert(v);	// DIK_INSERT
		v.value = KEY_HOME;			v.name="HOME";			values.Insert(v);	// DIK_HOME
		v.value = KEY_PGUP;			v.name="PAGE UP";		values.Insert(v);	// DIK_PRIOR
		v.value = KEY_DEL;			v.name="DELETE";		values.Insert(v);	// DIK_DELETE
		v.value = KEY_END;			v.name="END";			values.Insert(v);	// DIK_END
		v.value = KEY_PGDN;			v.name="PAGE DOWN";		values.Insert(v);	// DIK_NEXT
		v.value = KEY_UP;			v.name="CURSOR UP";		values.Insert(v);	// DIK_UP
		v.value = KEY_LEFT;			v.name="CURSOR LEFT";	values.Insert(v);	// DIK_LEFT
		v.value = KEY_DOWN;			v.name="CURSOR DOWN";	values.Insert(v);	// DIK_DOWN
		v.value = KEY_RIGHT;		v.name="CURSOR RIGHT";	values.Insert(v);	// DIK_RIGHT
		// numeric keypad
		v.value = KEY_NUMLOCK;		v.name="NUMLOCK";		values.Insert(v);	// DIK_NUMLOCK
		v.value = KEY_PAD_DIV;		v.name="NUM DIV";		values.Insert(v);	// DIK_SLASH
		v.value = KEY_PAD_MUL;		v.name="NUM MUL";		values.Insert(v);	// DIK_MULTIPLY
		v.value = KEY_GREYMINUS;	v.name="NUM SUB";		values.Insert(v);	// DIK_SUBTRACT
		v.value = KEY_PAD_ENTER;	v.name="NUM ENTER";		values.Insert(v);	// DIK_NUMPADENTER
		v.value = KEY_PAD_DEL;		v.name="NUM DEL";		values.Insert(v);	// DIK_DECIMAL
		v.value = KEY_PAD_INS;		v.name="NUM 0";			values.Insert(v);	// DIK_NUMPAD0
		v.value = KEY_PAD_END;		v.name="NUM 1";			values.Insert(v);	// DIK_NUMPAD1
		v.value = KEY_PAD_DOWN;		v.name="NUM 2";			values.Insert(v);	// DIK_NUMPAD2
		v.value = KEY_PAD_PGDN;		v.name="NUM 3";			values.Insert(v);	// DIK_NUMPAD3
		v.value = KEY_PAD_LEFT;		v.name="NUM 4";			values.Insert(v);	// DIK_NUMPAD4
		v.value = KEY_PAD_5;		v.name="NUM 5";			values.Insert(v);	// DIK_NUMPAD5
		v.value = KEY_PAD_RIGHT;	v.name="NUM 6";			values.Insert(v);	// DIK_NUMPAD6
		v.value = KEY_PAD_HOME;		v.name="NUM 7";			values.Insert(v);	// DIK_NUMPAD7
		v.value = KEY_PAD_UP;		v.name="NUM 8";			values.Insert(v);	// DIK_NUMPAD8
		v.value = KEY_PAD_PGUP;		v.name="NUM 9";			values.Insert(v);	// DIK_NUMPAD9
	}
	if (german)
	{
		v.value = KEY_BACKSPACE; 	v.name="RÜCK";			values.Insert(v);	// DIK_BACK
		v.value = KEY_TAB;			v.name="TABULATOR";		values.Insert(v);	// DIK_TAB
		v.value = KEY_ENTER; 		v.name="ENTER";			values.Insert(v);	// DIK_RETURN
		v.value = KEY_CAPSLOCK;		v.name="FESTSTELL";		values.Insert(v);	// DIK_CAPITAL
		v.value = KEY_LSHIFT;		v.name="UMSCHALT LINKS";	values.Insert(v);	// DIK_LSHIFT
		v.value = KEY_RSHIFT;		v.name="UMSCHALT RECHTS";	values.Insert(v);	// DIK_RSHIFT
		v.value = KEY_LCTRL;		v.name="STRG LINKS";	values.Insert(v);	// DIK_LCONTROL
		v.value = KEY_WIN_LWINKEY;	v.name="OS-LOGO LINKS";	values.Insert(v);	// DIK_LWIN
		v.value = KEY_LALT;			v.name="ALT";			values.Insert(v);	// DIK_LMENU
		v.value = KEY_SPACE;		v.name="LEERTASTE";		values.Insert(v);	// DIK_SPACE
		v.value = KEY_RALT;			v.name="ALT GR";		values.Insert(v);	// DIK_RMENU
		v.value = KEY_WIN_RWINKEY;	v.name="OS-LOGO RECHTS";values.Insert(v);	// DIK_RWIN
		v.value = KEY_WIN_CONTEXT;	v.name="KONTEXT";		values.Insert(v);	// 349
		v.value = KEY_RCTRL;		v.name="STRG RECHTS";	values.Insert(v);	// DIK_RCONTROL
		// first row
		v.value = KEY_OQUOTE;		v.name="ZIRKUMFLEX";	values.Insert(v);	// DIK_GRAVE
		v.value = KEY_1;			v.name="1";				values.Insert(v);	// DIK_1
		v.value = KEY_2;			v.name="2";				values.Insert(v);	// DIK_2
		v.value = KEY_3;			v.name="3";				values.Insert(v);	// DIK_3
		v.value = KEY_4;			v.name="4";				values.Insert(v);	// DIK_4
		v.value = KEY_5;			v.name="5";				values.Insert(v);	// DIK_5
		v.value = KEY_6;			v.name="6";				values.Insert(v);	// DIK_6
		v.value = KEY_7;			v.name="7";				values.Insert(v);	// DIK_7
		v.value = KEY_8;			v.name="8";				values.Insert(v);	// DIK_8
		v.value = KEY_9;			v.name="9";				values.Insert(v);	// DIK_9
		v.value = KEY_0;			v.name="0";				values.Insert(v);	// DIK_0
		v.value = KEY_DE_SHARPS;	v.name="ß";				values.Insert(v);	// DIK_MINUS
		v.value = KEY_DE_GRAVE;		v.name="AKZENT";		values.Insert(v);	// DIK_EQUALS
		// second row
		v.value = KEY_Q;			v.name="Q";				values.Insert(v);	// DIK_Q
		v.value = KEY_W;			v.name="W";				values.Insert(v);	// DIK_W
		v.value = KEY_E;			v.name="E";				values.Insert(v);	// DIK_E
		v.value = KEY_R;			v.name="R";				values.Insert(v);	// DIK_R
		v.value = KEY_T;			v.name="T";				values.Insert(v);	// DIK_T
		v.value = KEY_Y;			v.name="Z";				values.Insert(v);	// DIK_Y
		v.value = KEY_U;			v.name="U";				values.Insert(v);	// DIK_U
		v.value = KEY_I;			v.name="I";				values.Insert(v);	// DIK_I
		v.value = KEY_O;			v.name="O";				values.Insert(v);	// DIK_O
		v.value = KEY_P;			v.name="P";				values.Insert(v);	// DIK_P
		v.value = KEY_MINUS;		v.name="Ü";				values.Insert(v);	// DIK_LBRACKET
		v.value = KEY_PLUS;			v.name="PLUS";			values.Insert(v);	// DIK_RBRACKET
		// third row
		v.value = KEY_A;			v.name="A";				values.Insert(v);	// DIK_A
		v.value = KEY_S;			v.name="S";				values.Insert(v);	// DIK_S
		v.value = KEY_D;			v.name="D";				values.Insert(v);	// DIK_D
		v.value = KEY_F;			v.name="F";				values.Insert(v);	// DIK_F
		v.value = KEY_G;			v.name="G";				values.Insert(v);	// DIK_G
		v.value = KEY_H;			v.name="H";				values.Insert(v);	// DIK_H
		v.value = KEY_J;			v.name="J";				values.Insert(v);	// DIK_J
		v.value = KEY_K;			v.name="K";				values.Insert(v);	// DIK_K
		v.value = KEY_L;			v.name="L";				values.Insert(v);	// DIK_L
		v.value = KEY_SEMICOLON;	v.name="Ö";				values.Insert(v);	// DIK_SEMICOLON
		v.value = KEY_APOSTROPHE;	v.name="Ä";				values.Insert(v);	// DIK_APOSTROPHE
		v.value = KEY_BSLASH;		v.name="RAUTE";			values.Insert(v);	// DIK_BACKSLASH
		// fourth row
		v.value = KEY_OEM_102;		v.name="KLEINER-ALS";	values.Insert(v);	// DIK_OEM_102
		v.value = KEY_Z;			v.name="Y";				values.Insert(v);	// DIK_Z
		v.value = KEY_X;			v.name="X";				values.Insert(v);	// DIK_X
		v.value = KEY_C;			v.name="C";				values.Insert(v);	// DIK_C
		v.value = KEY_V;			v.name="V";				values.Insert(v);	// DIK_V
		v.value = KEY_B;			v.name="B";				values.Insert(v);	// DIK_B
		v.value = KEY_N;			v.name="N";				values.Insert(v);	// DIK_N
		v.value = KEY_M;			v.name="M";				values.Insert(v);	// DIK_M
		v.value = KEY_COMMA;		v.name="KOMMA";			values.Insert(v);	// DIK_COMMA
		v.value = KEY_DOT;			v.name="PUNKT";			values.Insert(v);	// DIK_PERIOD
		v.value = KEY_FSLASH;		v.name="MINUS";			values.Insert(v);	// DIK_SLASH
	}
	else
	{
		v.value = KEY_BACKSPACE; 	v.name="BACKSPACE";		values.Insert(v);	// DIK_BACK
		v.value = KEY_TAB;			v.name="TAB";			values.Insert(v);	// DIK_TAB
		v.value = KEY_ENTER; 		v.name="ENTER";			values.Insert(v);	// DIK_RETURN
		v.value = KEY_CAPSLOCK;		v.name="CAPS LOCK";		values.Insert(v);	// DIK_CAPITAL
		v.value = KEY_LSHIFT;		v.name="LEFT SHIFT";	values.Insert(v);	// DIK_LSHIFT
		v.value = KEY_RSHIFT;		v.name="RIGHT SHIFT";	values.Insert(v);	// DIK_RSHIFT
		v.value = KEY_LCTRL;		v.name="LEFT CTRL";		values.Insert(v);	// DIK_LCONTROL
		v.value = KEY_WIN_LWINKEY;	v.name="LEFT OS KEY";	values.Insert(v);	// DIK_LWIN
		v.value = KEY_LALT;			v.name="LEFT ALT";		values.Insert(v);	// DIK_LMENU
		v.value = KEY_SPACE;		v.name="SPACE";			values.Insert(v);	// DIK_SPACE
		v.value = KEY_RALT;			v.name="RIGHT ALT";		values.Insert(v);	// DIK_RMENU
		v.value = KEY_WIN_RWINKEY;	v.name="RIGHT OS KEY";	values.Insert(v);	// DIK_RWIN
		v.value = KEY_WIN_CONTEXT;	v.name="CONTEXT";		values.Insert(v);	// 349
		v.value = KEY_RCTRL;		v.name="RIGHT CTRL";	values.Insert(v);	// DIK_RCONTROL
		// first row
		v.value = KEY_OQUOTE;		v.name="GRAVE ACCENT";	values.Insert(v);	// DIK_GRAVE
		v.value = KEY_1;			v.name="1";				values.Insert(v);	// DIK_1
		v.value = KEY_2;			v.name="2";				values.Insert(v);	// DIK_2
		v.value = KEY_3;			v.name="3";				values.Insert(v);	// DIK_3
		v.value = KEY_4;			v.name="4";				values.Insert(v);	// DIK_4
		v.value = KEY_5;			v.name="5";				values.Insert(v);	// DIK_5
		v.value = KEY_6;			v.name="6";				values.Insert(v);	// DIK_6
		v.value = KEY_7;			v.name="7";				values.Insert(v);	// DIK_7
		v.value = KEY_8;			v.name="8";				values.Insert(v);	// DIK_8
		v.value = KEY_9;			v.name="9";				values.Insert(v);	// DIK_9
		v.value = KEY_0;			v.name="0";				values.Insert(v);	// DIK_0
		v.value = KEY_DE_SHARPS;	v.name="MINUS";			values.Insert(v);	// DIK_MINUS
		v.value = KEY_DE_GRAVE;		v.name="EQUALS";		values.Insert(v);	// DIK_EQUALS
		// second row
		v.value = KEY_Q;			v.name="Q";				values.Insert(v);	// DIK_Q
		v.value = KEY_W;			v.name="W";				values.Insert(v);	// DIK_W
		v.value = KEY_E;			v.name="E";				values.Insert(v);	// DIK_E
		v.value = KEY_R;			v.name="R";				values.Insert(v);	// DIK_R
		v.value = KEY_T;			v.name="T";				values.Insert(v);	// DIK_T
		v.value = KEY_Y;			v.name="Y";				values.Insert(v);	// DIK_Y
		v.value = KEY_U;			v.name="U";				values.Insert(v);	// DIK_U
		v.value = KEY_I;			v.name="I";				values.Insert(v);	// DIK_I
		v.value = KEY_O;			v.name="O";				values.Insert(v);	// DIK_O
		v.value = KEY_P;			v.name="P";				values.Insert(v);	// DIK_P
		v.value = KEY_MINUS;		v.name="LEFT BRACKET";	values.Insert(v);	// DIK_LBRACKET
		v.value = KEY_PLUS;			v.name="RIGHT BRACKET";	values.Insert(v);	// DIK_RBRACKET
		// third row
		v.value = KEY_A;			v.name="A";				values.Insert(v);	// DIK_A
		v.value = KEY_S;			v.name="S";				values.Insert(v);	// DIK_S
		v.value = KEY_D;			v.name="D";				values.Insert(v);	// DIK_D
		v.value = KEY_F;			v.name="F";				values.Insert(v);	// DIK_F
		v.value = KEY_G;			v.name="G";				values.Insert(v);	// DIK_G
		v.value = KEY_H;			v.name="H";				values.Insert(v);	// DIK_H
		v.value = KEY_J;			v.name="J";				values.Insert(v);	// DIK_J
		v.value = KEY_K;			v.name="K";				values.Insert(v);	// DIK_K
		v.value = KEY_L;			v.name="L";				values.Insert(v);	// DIK_L
		v.value = KEY_SEMICOLON;	v.name="SEMICOLON";		values.Insert(v);	// DIK_SEMICOLON
		v.value = KEY_APOSTROPHE;	v.name="APOSTROPHE";	values.Insert(v);	// DIK_APOSTROPHE
		v.value = KEY_BSLASH;		v.name="BACKSLASH";		values.Insert(v);	// DIK_BACKSLASH
		// fourth row
		v.value = KEY_OEM_102;		v.name="PIPE";			values.Insert(v);	// DIK_OEM_102	// English UK only
		v.value = KEY_Z;			v.name="Z";				values.Insert(v);	// DIK_Z		// [BENDLIN] Addon - KeybFix
		v.value = KEY_X;			v.name="X";				values.Insert(v);	// DIK_X
		v.value = KEY_C;			v.name="C";				values.Insert(v);	// DIK_C
		v.value = KEY_V;			v.name="V";				values.Insert(v);	// DIK_V
		v.value = KEY_B;			v.name="B";				values.Insert(v);	// DIK_B
		v.value = KEY_N;			v.name="N";				values.Insert(v);	// DIK_N
		v.value = KEY_M;			v.name="M";				values.Insert(v);	// DIK_M
		v.value = KEY_COMMA;		v.name="COMMA";			values.Insert(v);	// DIK_COMMA
		v.value = KEY_DOT;			v.name="PERIOD";		values.Insert(v);	// DIK_PERIOD
		v.value = KEY_FSLASH;		v.name="MINUS";			values.Insert(v);	// DIK_SLASH
	}

	////////////////////////////////////////////////////////////////
	//
	//	KEYBOARD
	//
	if (german)
	{
		// movement
		v.value = JOY_LEFT;			v.name="JOY-LINKS";		values.Insert(v);				
		v.value = JOY_RIGHT;		v.name="JOY-RECHTS";	values.Insert(v);	
		v.value = JOY_UP;			v.name="JOY-OBEN";		values.Insert(v);	
		v.value = JOY_DOWN;			v.name="JOY-UNTEN";		values.Insert(v);	
		v.value = THROTTLE_UP;		v.name="SCHUBREGLER AUF";	values.Insert(v);	
		v.value = THROTTLE_DOWN;	v.name="SCHUBREGLER AB";	values.Insert(v);	
		v.value = RUDDER_LEFT;		v.name="RUDER LINKS";	values.Insert(v);	
		v.value = RUDDER_RIGHT;		v.name="RUDER RECHTS";	values.Insert(v);	
	}
	else
	{
		// movement
		v.value = JOY_LEFT;			v.name="JOY LEFT";		values.Insert(v);				
		v.value = JOY_RIGHT;		v.name="JOY RIGHT";		values.Insert(v);	
		v.value = JOY_UP;			v.name="JOY UP";		values.Insert(v);	
		v.value = JOY_DOWN;			v.name="JOY DOWN";		values.Insert(v);	
		v.value = THROTTLE_UP;		v.name="THROTTLE UP";	values.Insert(v);	
		v.value = THROTTLE_DOWN;	v.name="THROTTLE DOWN";	values.Insert(v);	
		v.value = RUDDER_LEFT;		v.name="RUDDER LEFT";	values.Insert(v);	
		v.value = RUDDER_RIGHT;		v.name="RUDDER RIGHT";	values.Insert(v);	
	}
	if (german)
	{
		// buttons
		v.value = JOY_POV_LEFT;		v.name="POV-LINKS";		values.Insert(v);	
		v.value = JOY_POV_RIGHT;	v.name="POV-RECHTS";	values.Insert(v);	
		v.value = JOY_POV_UP;		v.name="POV-OBEN";		values.Insert(v);	
		v.value = JOY_POV_DOWN;		v.name="POV-UNTEN";		values.Insert(v);	
		v.value = JOY_BUTTON_1;		v.name="JOY BTN 1";		values.Insert(v);	
		v.value = JOY_BUTTON_2;		v.name="JOY BTN 2";		values.Insert(v);	
		v.value = JOY_BUTTON_3;		v.name="JOY BTN 3";		values.Insert(v);	
		v.value = JOY_BUTTON_4;		v.name="JOY BTN 4";		values.Insert(v);	
		v.value = JOY_BUTTON_5;		v.name="JOY BTN 5";		values.Insert(v);	
		v.value = JOY_BUTTON_6;		v.name="JOY BTN 6";		values.Insert(v);	
		v.value = JOY_BUTTON_7;		v.name="JOY BTN 7";		values.Insert(v);	
		v.value = JOY_BUTTON_8;		v.name="JOY BTN 8";		values.Insert(v);		
		v.value = JOY_BUTTON_9;		v.name="JOY BTN 9";		values.Insert(v);		
		v.value = JOY_BUTTON_10;	v.name="JOY BTN 10";	values.Insert(v);		
		v.value = JOY_BUTTON_11;	v.name="JOY BTN 11";	values.Insert(v);		
		v.value = JOY_BUTTON_12;	v.name="JOY BTN 12";	values.Insert(v);		
		v.value = JOY_BUTTON_13;	v.name="JOY BTN 13";	values.Insert(v);		
		v.value = JOY_BUTTON_14;	v.name="JOY BTN 14";	values.Insert(v);			
		v.value = JOY_BUTTON_15;	v.name="JOY BTN 15";	values.Insert(v);			
		v.value = JOY_BUTTON_16;	v.name="JOY BTN 16";	values.Insert(v);			
		v.value = JOY_BUTTON_17;	v.name="JOY BTN 17";	values.Insert(v);			
		v.value = JOY_BUTTON_18;	v.name="JOY BTN 18";	values.Insert(v);			
		v.value = JOY_BUTTON_19;	v.name="JOY BTN 19";	values.Insert(v);			
		v.value = JOY_BUTTON_20;	v.name="JOY BTN 20";	values.Insert(v);			
		v.value = JOY_BUTTON_21;	v.name="JOY BTN 21";	values.Insert(v);		
		v.value = JOY_BUTTON_22;	v.name="JOY BTN 22";	values.Insert(v);		
		v.value = JOY_BUTTON_23;	v.name="JOY BTN 23";	values.Insert(v);		
		v.value = JOY_BUTTON_24;	v.name="JOY BTN 24";	values.Insert(v);			
		v.value = JOY_BUTTON_25;	v.name="JOY BTN 25";	values.Insert(v);			
		v.value = JOY_BUTTON_26;	v.name="JOY BTN 26";	values.Insert(v);			
		v.value = JOY_BUTTON_27;	v.name="JOY BTN 27";	values.Insert(v);			
		v.value = JOY_BUTTON_28;	v.name="JOY BTN 28";	values.Insert(v);			
		v.value = JOY_BUTTON_29;	v.name="JOY BTN 29";	values.Insert(v);			
		v.value = JOY_BUTTON_30;	v.name="JOY BTN 30";	values.Insert(v);			
		v.value = JOY_BUTTON_31;	v.name="JOY BTN 31";	values.Insert(v);		
		v.value = JOY_BUTTON_32;	v.name="JOY BTN 32";	values.Insert(v);
	}
	else
	{
		// buttons
		v.value = JOY_POV_LEFT;		v.name="POV-LEFT";		values.Insert(v);	
		v.value = JOY_POV_RIGHT;	v.name="POV-RIGHT";		values.Insert(v);	
		v.value = JOY_POV_UP;		v.name="POV-UP";		values.Insert(v);	
		v.value = JOY_POV_DOWN;		v.name="POV-DOWN";		values.Insert(v);	
		v.value = JOY_BUTTON_1;		v.name="JOY BTN 1";		values.Insert(v);	
		v.value = JOY_BUTTON_2;		v.name="JOY BTN 2";		values.Insert(v);	
		v.value = JOY_BUTTON_3;		v.name="JOY BTN 3";		values.Insert(v);	
		v.value = JOY_BUTTON_4;		v.name="JOY BTN 4";		values.Insert(v);	
		v.value = JOY_BUTTON_5;		v.name="JOY BTN 5";		values.Insert(v);	
		v.value = JOY_BUTTON_6;		v.name="JOY BTN 6";		values.Insert(v);	
		v.value = JOY_BUTTON_7;		v.name="JOY BTN 7";		values.Insert(v);	
		v.value = JOY_BUTTON_8;		v.name="JOY BTN 8";		values.Insert(v);		
		v.value = JOY_BUTTON_9;		v.name="JOY BTN 9";		values.Insert(v);		
		v.value = JOY_BUTTON_10;	v.name="JOY BTN 10";	values.Insert(v);		
		v.value = JOY_BUTTON_11;	v.name="JOY BTN 11";	values.Insert(v);		
		v.value = JOY_BUTTON_12;	v.name="JOY BTN 12";	values.Insert(v);		
		v.value = JOY_BUTTON_13;	v.name="JOY BTN 13";	values.Insert(v);		
		v.value = JOY_BUTTON_14;	v.name="JOY BTN 14";	values.Insert(v);			
		v.value = JOY_BUTTON_15;	v.name="JOY BTN 15";	values.Insert(v);			
		v.value = JOY_BUTTON_16;	v.name="JOY BTN 16";	values.Insert(v);			
		v.value = JOY_BUTTON_17;	v.name="JOY BTN 17";	values.Insert(v);			
		v.value = JOY_BUTTON_18;	v.name="JOY BTN 18";	values.Insert(v);			
		v.value = JOY_BUTTON_19;	v.name="JOY BTN 19";	values.Insert(v);			
		v.value = JOY_BUTTON_20;	v.name="JOY BTN 20";	values.Insert(v);			
		v.value = JOY_BUTTON_21;	v.name="JOY BTN 21";	values.Insert(v);		
		v.value = JOY_BUTTON_22;	v.name="JOY BTN 22";	values.Insert(v);		
		v.value = JOY_BUTTON_23;	v.name="JOY BTN 23";	values.Insert(v);		
		v.value = JOY_BUTTON_24;	v.name="JOY BTN 24";	values.Insert(v);			
		v.value = JOY_BUTTON_25;	v.name="JOY BTN 25";	values.Insert(v);			
		v.value = JOY_BUTTON_26;	v.name="JOY BTN 26";	values.Insert(v);			
		v.value = JOY_BUTTON_27;	v.name="JOY BTN 27";	values.Insert(v);			
		v.value = JOY_BUTTON_28;	v.name="JOY BTN 28";	values.Insert(v);			
		v.value = JOY_BUTTON_29;	v.name="JOY BTN 29";	values.Insert(v);			
		v.value = JOY_BUTTON_30;	v.name="JOY BTN 30";	values.Insert(v);			
		v.value = JOY_BUTTON_31;	v.name="JOY BTN 31";	values.Insert(v);		
		v.value = JOY_BUTTON_32;	v.name="JOY BTN 32";	values.Insert(v);
	}

};

void _GetDefaultBinding(zINT mode, const zSTRING optionID, zCArray<zWORD>&controlValueList)
{
	void*buffer=0;
	zDWORD	bindSize = 0;
	if (mode==0) bindSize = zoptions->ReadRaw(zOPT_SEC_KEYS_DEFAULT0, optionID.ToChar(), buffer, controlValueList.GetArray(), controlValueList.GetNumInList()<<1);
	if (mode==1) bindSize = zoptions->ReadRaw(zOPT_SEC_KEYS_DEFAULT1, optionID.ToChar(), buffer, controlValueList.GetArray(), controlValueList.GetNumInList()<<1);
	if (bindSize > 0)
	{
		controlValueList.DeleteList();
		for (int i=0; i<bindSize>>1; i++)
			// [BENDLIN] Addon Patch2 - Empty Key Bindings
			if (((zWORD*)buffer)[i] != 0)
				controlValueList.Insert(((zWORD*)buffer)[i]);
	}
    delete[] buffer;
};

void zCInput::BindKeys(int mode)
{		
	zCArray<zWORD>ctrls;

	// Bewegung vor/zurueck
	ctrls.DeleteList();
	if (mode==0)	{ ctrls.Insert(KEY_UP);		ctrls.Insert(KEY_HOME);	}
	if (mode==1)	{ ctrls.Insert(KEY_UP);		ctrls.Insert(KEY_W);	}
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_UP, ctrls);
	BindOption(ZOPT_GAMEKEY_UP, GAME_UP, ctrls); 	

	ctrls.DeleteList();
	if (mode==0)	{ ctrls.Insert(KEY_DOWN);							}
	if (mode==1)	{ ctrls.Insert(KEY_DOWN);	ctrls.Insert(KEY_S);	}	
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_DOWN, ctrls);
	BindOption(ZOPT_GAMEKEY_DOWN, GAME_DOWN, ctrls); 

	// Drehen links/rechts
	ctrls.DeleteList();
	if (mode==0)	{ ctrls.Insert(KEY_INS);							}
	if (mode==1)	{ ctrls.Insert(KEY_LEFT);	ctrls.Insert(KEY_Q);	}	
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_LEFT, ctrls);
	BindOption(ZOPT_GAMEKEY_LEFT, GAME_LEFT, ctrls); 
		
	ctrls.DeleteList();
	if (mode==0)	{ ctrls.Insert(KEY_PGUP);							}
	if (mode==1)	{ ctrls.Insert(KEY_RIGHT);	ctrls.Insert(KEY_E);	}
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_RIGHT, ctrls);
	BindOption(ZOPT_GAMEKEY_RIGHT, GAME_RIGHT, ctrls); 

	// Strafen
	ctrls.DeleteList();
	if (mode==0)	{ ctrls.Insert(KEY_LEFT);							}
	if (mode==1)	{ ctrls.Insert(KEY_DEL);	ctrls.Insert(KEY_A);	}	
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_STRAFELEFT, ctrls);
	BindOption(ZOPT_GAMEKEY_STRAFELEFT, GAME_STRAFELEFT,ctrls);

	ctrls.DeleteList();
	if (mode==0)	{ ctrls.Insert(KEY_RIGHT);							}
	if (mode==1)	{ ctrls.Insert(KEY_PGDN);	ctrls.Insert(KEY_D);	}	
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_STRAFERIGHT, ctrls);
	BindOption(ZOPT_GAMEKEY_STRAFERIGHT, GAME_STRAFERIGHT,ctrls);	

	// Action
	ctrls.DeleteList();
	ctrls.Insert(KEY_LCTRL);	ctrls.Insert(MOUSE_BUTTONLEFT);
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_ACTION, ctrls);
	BindOption(ZOPT_GAMEKEY_ACTION, GAME_ACTION, ctrls); 
	
	// Slow-Move
	ctrls.DeleteList();
	ctrls.Insert(KEY_LSHIFT);
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_SLOW, ctrls);
	BindOption(ZOPT_GAMEKEY_SLOW, GAME_SLOW, ctrls); 
	
	// Strafe-Key (SMOVE)
	ctrls.DeleteList();
	ctrls.Insert(KEY_LALT);	ctrls.Insert(KEY_RALT);
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_SMOVE, ctrls);
	BindOption(ZOPT_GAMEKEY_SMOVE,GAME_SMOVE,ctrls); 
	
	// Waffe ziehen
	ctrls.DeleteList();	
	ctrls.Insert(KEY_SPACE);	
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_WEAPON, ctrls);
	BindOption(ZOPT_GAMEKEY_WEAPON, GAME_WEAPON, ctrls); 
		
	// Schleichen
	ctrls.DeleteList();
	if (mode==0)	{ ctrls.Insert(KEY_A);	ctrls.Insert(KEY_PAD_MUL);	}
	if (mode==1)	{ ctrls.Insert(KEY_X);	ctrls.Insert(KEY_PAD_MUL);	}	
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_SNEAK, ctrls);
	BindOption(ZOPT_GAMEKEY_SNEAK,GAME_SNEAK,ctrls);

	// Umschauen/Umschauen FirstPerson (FP)
	ctrls.DeleteList();
	ctrls.Insert(KEY_PAD_INS);ctrls.Insert(KEY_R);
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_LOOK, ctrls);
	BindOption(ZOPT_GAMEKEY_LOOK,GAME_LOOK,ctrls);
	
	ctrls.DeleteList();
	ctrls.Insert(KEY_PAD_DEL);ctrls.Insert(KEY_F);
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_LOOK_FP, ctrls);
	BindOption(ZOPT_GAMEKEY_LOOK_FP,GAME_LOOK_FP,ctrls);

	// Abbrechen (end/escape)
	ctrls.DeleteList();
	ctrls.Insert(KEY_ESC);
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_END, ctrls);
	BindOption(ZOPT_GAMEKEY_END, GAME_END,ctrls);
	
	// Inventory
	ctrls.DeleteList();
	ctrls.Insert(KEY_TAB);ctrls.Insert(KEY_BACKSPACE);	
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_INVENTORY, ctrls);
	BindOption(ZOPT_GAMEKEY_INVENTORY, GAME_INVENTORY, ctrls); 	

	// Status-Keys
	ctrls.DeleteList();
	if (mode==0)	{ ctrls.Insert(KEY_S);ctrls.Insert(KEY_B); }
	if (mode==1)	{ ctrls.Insert(KEY_B); }	
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_SCREEN_STATUS, ctrls);
	BindOption(ZOPT_GAMEKEY_SCREEN_STATUS, GAME_SCREEN_STATUS, ctrls); 

	// Log-Keys
	ctrls.DeleteList();
	if (mode==0)	{ ctrls.Insert(KEY_L);ctrls.Insert(KEY_N); }
	if (mode==1)	{ ctrls.Insert(KEY_N); }	
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_SCREEN_LOG, ctrls);
	BindOption(ZOPT_GAMEKEY_SCREEN_LOG, GAME_SCREEN_LOG, ctrls); 

	// Map-Keys
	ctrls.DeleteList();
	ctrls.Insert(KEY_M);
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_SCREEN_MAP, ctrls);
	BindOption(ZOPT_GAMEKEY_SCREEN_MAP, GAME_SCREEN_MAP, ctrls); 

	ctrls.DeleteList();
	ctrls.Insert(KEY_DEL);  ctrls.Insert(KEY_DOT); 
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_ACTIONLEFT, ctrls);
	BindOption(ZOPT_GAMEKEY_ACTIONLEFT, GAME_ACTIONLEFT, ctrls); 

	ctrls.DeleteList();
	ctrls.Insert(KEY_PGDN); ctrls.Insert(KEY_MINUS); 
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_ACTIONRIGHT, ctrls);
	BindOption(ZOPT_GAMEKEY_ACTIONRIGHT, GAME_ACTIONRIGHT, ctrls); 

	ctrls.DeleteList();
	ctrls.Insert(MOUSE_BUTTONRIGHT); ctrls.Insert(KEY_END); 
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_PARADE, ctrls);
	BindOption(ZOPT_GAMEKEY_PARADE, GAME_PARADE, ctrls); 

	ctrls.DeleteList();
	ctrls.Insert(KEY_ENTER);  ctrls.Insert(KEY_Y); 
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_LOCK_TARGET, ctrls);
	BindOption(ZOPT_GAMEKEY_LOCK_TARGET, GAME_LOCK_TARGET, ctrls); 

	ctrls.DeleteList();
	ctrls.Insert(KEY_P);
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_LAME_POTION, ctrls);
	BindOption(ZOPT_GAMEKEY_LAME_POTION, GAME_LAME_POTION, ctrls); 

	ctrls.DeleteList();
	ctrls.Insert(KEY_H);
	_GetDefaultBinding(mode, ZOPT_GAMEKEY_LAME_HEAL, ctrls);
	BindOption(ZOPT_GAMEKEY_LAME_HEAL, GAME_LAME_HEAL, ctrls);
	
};


// is zwar brute force, aber kommt eh nicht auf geschw. an
zWORD zCInput :: GetControlValueByName(const zSTRING &name)
{
	for (int i=0; i<values.GetNumInList(); i++) {
		if (values[i].name == name) return values[i].value;
	}
	return 0;
};

zSTRING	zCInput :: GetNameByControlValue(const zWORD controlValue)
{
	for (int i=0; i<values.GetNumInList(); i++) {
		if (values[i].value == controlValue) return values[i].name;
	}
	return "";
};



