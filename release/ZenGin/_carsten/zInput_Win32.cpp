/******************************************************************************** 
 
     $Workfile:: zInput_Win32.cpp     $                $Date:: 18.03.01 18:47   $
     $Revision:: 52                   $             $Modtime:: 17.03.01 23:13   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   Implemention of general zCInput class (Win32/DirectX).
   created: 31.10.99

 * $Log: /current_work/ZenGin/_Carsten/zInput_Win32.cpp $
 * 
 * 52    18.03.01 18:47 Edenfeld
 * "User32.dll::BindKeys()" not found Bugfix unter Win95 gefixt
 * 
 * 51    15.02.01 0:29 Wohlers
 * 
 * 50    14.02.01 1:54 Edenfeld
 * 
 * 49    14.02.01 1:53 Edenfeld
 * 
 * 48    10.02.01 15:34 Wohlers
 * 
 * 47    10.02.01 15:25 Speckels
 * 
 * 46    9.02.01 19:20 Speckels
 * 
 * 45    9.02.01 16:31 Speckels
 * 2. Parameter von SetState beruecksichtigt
 * ProcessInput löscht jetzt keine Elemente aus der mapList mehr
 * Mouse-Button-Events korrigiert (logicalKeys mit SetState gesetzt bzw.
 * auch gelöscht)
 * 
 * 44    9.02.01 15:52 Wohlers
 * 
 * 43    8.02.01 21:58 Speckels
 * 
 * 42    8.02.01 17:53 Speckels
 * 
 * 41    8.02.01 16:25 Speckels
 * 
 * 40    7.02.01 0:37 Hildebrandt
 * 
 * 39    3.02.01 4:11 Hildebrandt
 * 
 * 38    2.02.01 19:29 Hildebrandt
 * 
 * 37    2.02.01 5:23 Hildebrandt
 * 
 * 36    28.01.01 18:01 Speckels
 * 
 * 35    15.01.01 20:44 Speckels
 * 
 * 34    11.01.01 19:53 Speckels
 * 
 * 33    11.01.01 12:33 Pankratz
 * 
 * 32    10.01.01 18:56 Speckels
 * 
 * 31    9.01.01 22:06 Speckels
 * 
 * 29    8.01.01 18:13 Speckels
 * 
 * 28    8.01.01 18:12 Speckels
 * 
 * 27    20.12.00 15:14 Speckels
 * 
 * 26    20.12.00 14:08 Speckels
 * 
 * 25    19.12.00 16:48 Speckels
 * 
 * 24    19.12.00 16:00 Speckels
 * 
 * 23    18.12.00 17:38 Speckels
 * 
 * 22    8.12.00 14:25 Speckels
 * 
 * 21    5.12.00 18:58 Speckels
 * 
 * 20    1.12.00 16:53 Wohlers
 * 
 * 19    29.11.00 18:16 Keskenti
 * 
 * 18    29.11.00 15:03 Keskenti
 * 
 * 17    23.11.00 17:10 Wohlers
 * 
 * 16    23.11.00 16:21 Wohlers
 * 
 * 15    22.11.00 20:41 Wohlers
 * 
 * 14    20.11.00 15:03 Speckels
 * 
 * 13    18.11.00 19:04 Speckels
 * 
 * 12    17/11/00 12:17 Luesebrink
 * 
 * 11    16/11/00 19:24 Luesebrink
 * 
 * 10    16.11.00 13:57 Speckels
 * 
 * 9     16/11/00 11:39 Luesebrink
 * 
 * 8     16/11/00 10:30 Luesebrink
 * 
 * 7     15.11.00 21:00 Hildebrandt
 * 
 * 3     15.11.00 21:00 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revisio: 2 $ ($Modtime: 17.03.01 23:13 $)

// =======================================================================================================================

#include "zcore.h"
#include "zInput_Win32.h"
#include "zWin32.h"
#include "zWin32_Internal.h"
#include "mmsystem.h"
#include "zexceptionhandler.h"
#include "zoption.h"
#include "ztools.h"


// FIXME: HARDCORE EVIL -> lazy + goldmaster
#include "ogame.h"			

#define DIRECTINPUT_VERSION 0x0700
#include "dinput.h"
#include "winable.h"


// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 )


// ======================================================================================================================

// #define DISABLE_MOUSE

// #define DEBUG_REPORT_KEYS

// ======================================================================================================================

// Keyboard
#define KEYBOARD_BUFFER_SIZE (16)
static	zSKeyMapping			*helpMap		= NULL;
static	zBOOL					keyboardEnabled	= TRUE; 
		LPDIRECTINPUT7			lpDInput		= NULL;	
		LPDIRECTINPUTDEVICE7	lpDIKeyboard	= NULL;	
		bool					keyevent		[KEY_EVENT_TABLE_SIZE];			
		bool					keytoggle		[KEY_EVENT_TABLE_SIZE];
		bool					keyRepeatEnabled[KEY_EVENT_TABLE_SIZE];
		zCArray<int>			keybuffer;	

// ======================================================================================================================

// Mouse
#define MOUSE_BUFFER_SIZE (16)
struct zTMouseState {
		int						xpos;				// relative, centered at 0
		int						ypos;				// relative
		int						zpos;				// relative (mouse wheel)
		zBOOL					buttonPressedLeft;
		zBOOL					buttonPressedMid;	// (mouse wheel)
		zBOOL					buttonPressedRight;
};
static	zBOOL					mouseAvailable		= FALSE;	
static	zBOOL					mouseEnabled		= FALSE;
static	LPDIRECTINPUTDEVICE7	lpDIMouse			= NULL;	
static	HANDLE                  g_hMouseEvent		= NULL;
static	zTMouseState			mouseState;
static	zREAL					mouseSensitivityX	= 1.0F;
static	zREAL					mouseSensitivityY	= 1.0F;
static	zBOOL					mouseFlipX			= FALSE;
static	zBOOL					mouseFlipY			= FALSE;
static	void	UpdateMouse();

// ======================================================================================================================

// Joystick
#define JOYSTICK_BUFFER_SIZE (16)
static	zBOOL					joystickAvailable	= FALSE;	
static	zBOOL					joystickEnabled		= FALSE;
static	LPDIRECTINPUTDEVICE7	lpDIJoystick		= NULL;	
static	void	UpdateJoystick();

// ======================================================================================================================

static	HWND					focusWinHandle  = NULL;

// [BENDLIN] prepared for other keyboard layouts
unsigned char GetCharFromDIK(int dik1, int dik2, int dik3)
{
	// [BENDLIN] 1.30 Nur die Tastatureingaben generieren Buchstaben
	if (dik1 >= MAX_KEYS)
		dik1 = 0;
	if (dik2 >= MAX_KEYS)
		dik2 = 0;
	if (dik3 >= MAX_KEYS)
		dik3 = 0;

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

	// key value
	unsigned char key = 0;
	if ((dik1 != DIK_LSHIFT) && (dik1 != DIK_RSHIFT) && (dik1 != DIK_RMENU))
		key = dik1;
	else if ((dik2 != DIK_LSHIFT) && (dik2 != DIK_RSHIFT) && (dik2 != DIK_RMENU))
		key = dik2;
	else if ((dik3 != DIK_LSHIFT) && (dik3 != DIK_RSHIFT) && (dik3 != DIK_RMENU))
		key = dik3;
	// no given key
	if (key == 0)
		return 0;


	// ALTGR state
	bool altr = 0;
	if ((dik1 == DIK_RMENU) || (dik2 == DIK_RMENU) || (dik3 == DIK_RMENU))
		altr = true;
	// SHIFT state
	bool shft = false;
	if ((dik1 == DIK_LSHIFT) || (dik1 == DIK_RSHIFT) || (dik2 == DIK_LSHIFT) || (dik2 == DIK_RSHIFT) || (dik3 == DIK_LSHIFT) || (dik3 == DIK_RSHIFT))
		shft = true;
	// CAPS LOCK state
	bool caps = false;
	BYTE keyState[256];
	if (GetKeyboardState((PBYTE)(&keyState)))
		caps = (keyState[VK_CAPITAL] & 1);


	////////////////////////////////
	//
	//	Scancode-Char mappings
	//
	////////////////////////////////

	// keys without alternations
	switch(key)
	{
	case DIK_BACK:			return 0x08;  // Backspace
	case DIK_TAB:			return 0x09;  // Tabulator
	case DIK_RETURN:		return 0x0D;  // Enter on main keyboard
	case DIK_SPACE:			return 0x20;  // Space
#ifndef COMPILING_SPACER
	// numeric keypad
	case DIK_NUMPADENTER:	return 0x0D;
	case DIK_NUMPAD0:		return 0x30;
	case DIK_NUMPAD1:		return 0x31;
	case DIK_NUMPAD2:		return 0x32;
	case DIK_NUMPAD3:		return 0x33;
	case DIK_NUMPAD4:		return 0x34;
	case DIK_NUMPAD5:		return 0x35;
	case DIK_NUMPAD6:		return 0x36;
	case DIK_NUMPAD7:		return 0x37;
	case DIK_NUMPAD8:		return 0x38;
	case DIK_NUMPAD9:		return 0x39;
#endif
	}

	// [ALTGR + SHIFT + key]
	if ((altr) && (shft))
	{
		if (german)
		{
			// German
			// (no chars generated)
		}
		else
		{
			// US-International (default)
			switch(key)
			{
			case DIK_1:				return (        0xB9       );  // '¹'     Superscript One
			case DIK_4:				return (        0xA3       );  // '£'     Pound Sign
			case DIK_EQUALS:		return (        0xF7       );  // '÷'     Division Sign
			case DIK_Q:				return (!caps ? 0xC4 : 0xE4);  // 'Ä' 'ä' Latin Letter A With Diaeresis
			case DIK_W:				return (!caps ? 0xC5 : 0xE5);  // 'Å' 'å' Latin Letter A With Ring Above
			case DIK_E:				return (!caps ? 0xC9 : 0xE9);  // 'É' 'é' Latin Letter E With Acute
			case DIK_T:				return (!caps ? 0xDE : 0xFE);  // 'Þ' 'þ' Latin Letter Thorn
			case DIK_Y:				return (!caps ? 0xDC : 0xFC);  // 'Ü' 'ü' Latin Letter U With Diaeresis
			case DIK_U:				return (!caps ? 0xDA : 0xFA);  // 'Ú' 'ú' Latin Letter U With Acute
			case DIK_I:				return (!caps ? 0xCD : 0xED);  // 'Í' 'í' Latin Letter I With Acute
			case DIK_O:				return (!caps ? 0xD3 : 0xF3);  // 'Ó' 'ó' Latin Letter O With Acute
			case DIK_P:				return (!caps ? 0xD6 : 0xF6);  // 'Ö' 'ö' Latin Letter O With Diaeresis
			case DIK_A:				return (!caps ? 0xC1 : 0xE1);  // 'Á' 'á' Latin Letter A With Acute
			case DIK_S:				return (        0xA7       );  // '§'     Section Sign
			case DIK_D:				return (!caps ? 0xD0 : 0xF0);  // 'Ð' 'ð' Latin Letter Eth
			case DIK_L:				return (!caps ? 0xD8 : 0xF8);  // 'Ø' 'ø' Latin Letter O With Stroke
			case DIK_SEMICOLON:		return (        0xB0       );  // '°'     Degree Sign
			case DIK_APOSTROPHE:	return (        0xA8       );  // '¨'     Diaeresis
			case DIK_BACKSLASH:		return (        0xA6       );  // '¦'     Broken Bar
			case DIK_Z:				return (!caps ? 0xC6 : 0xE6);  // 'Æ' 'æ' Latin Letter Ae
			case DIK_C:				return (        0xA2       );  // '¢'     Cent Sign
			case DIK_N:				return (!caps ? 0xD1 : 0xF1);  // 'Ñ' 'ñ' Latin Letter N With Tilde
			case DIK_COMMA:			return (!caps ? 0xC7 : 0xE7);  // 'Ç' 'ç' Latin Letter C With Cedilla
			}
		}
	}

	// [ALTGR + key]
	else if (altr)
	{
		if (german)
		{
			// German
			switch(key)
			{
			case DIK_2:				return (0xB2);  // '²' Superscript Two
			case DIK_3:				return (0xB3);  // '³' Superscript Three
			case DIK_7:				return (0x7B);  // '{' Left Curly Bracket
			case DIK_8:				return (0x5B);  // '[' Left Square Bracket
			case DIK_9:				return (0x5D);  // ']' Right Square Bracket
			case DIK_0:				return (0x7D);  // '}' Right Curly Bracket
			case DIK_MINUS:			return (0x5C);  // '\' Reverse Solidus
			case DIK_Q:				return (0x40);  // '@' Commercial At
			case DIK_E:				return (0x80);  // '€' Euro Sign (0x20AC)
			case DIK_RBRACKET:		return (0x7E);  // '~' Tilde
			case DIK_OEM_102:		return (0x7C);  // '|' Vertical Line
			case DIK_M:				return (0xB5);  // 'µ' Micro Sign
			}
		}
		else
		{
			// US-International (default)
			switch(key)
			{
			case DIK_1:				return (        0xA1       );  // '¡'     Inverted Exclamation Mark
			case DIK_2:				return (        0xB2       );  // '²'     Superscript Two
			case DIK_3:				return (        0xB3       );  // '³'     Superscript Three
			case DIK_4:				return (        0xA4       );  // '¤'     Currency Sign
			case DIK_5:				return ( 0x80 /* 0x20AC */ );  // '€'     Euro Sign
			case DIK_6:				return (        0xBC       );  // '¼'     Vulgar Fraction One Quarter
			case DIK_7:				return (        0xBD       );  // '½'     Vulgar Fraction One Half
			case DIK_8:				return (        0xBE       );  // '¾'     Vulgar Fraction Three Quarters
			case DIK_9:				return ( 0x91 /* 0x2018 */ );  // '‘'     Left Single Quotation Mark
			case DIK_0:				return ( 0x92 /* 0x2019 */ );  // '’'     Right Single Quotation Mark
			case DIK_MINUS:			return (        0xA5       );  // '¥'     Yen Sign
			case DIK_EQUALS:		return (        0xD7       );  // '×'     Multiplication Sign
			case DIK_Q:				return (!caps ? 0xE4 : 0xC4);  // 'ä' 'Ä' Latin Letter A With Diaeresis
			case DIK_W:				return (!caps ? 0xE5 : 0xC5);  // 'å' 'Å' Latin Letter A With Ring Above
			case DIK_E:				return (!caps ? 0xE9 : 0xC9);  // 'é' 'É' Latin Letter E With Acute
			case DIK_R:				return (        0xAE       );  // '®'     Registered Sign
			case DIK_T:				return (!caps ? 0xFE : 0xDE);  // 'þ' 'Þ' Latin Letter Thorn
			case DIK_Y:				return (!caps ? 0xFC : 0xDC);  // 'ü' 'Ü' Latin Letter U With Diaeresis
			case DIK_U:				return (!caps ? 0xFA : 0xDA);  // 'ú' 'Ú' Latin Letter U With Acute
			case DIK_I:				return (!caps ? 0xED : 0xCD);  // 'í' 'Í' Latin Letter I With Acute
			case DIK_O:				return (!caps ? 0xF3 : 0xD3);  // 'ó' 'Ó' Latin Letter O With Acute
			case DIK_P:				return (!caps ? 0xF6 : 0xD6);  // 'ö' 'Ö' Latin Letter O With Diaeresis
			case DIK_LBRACKET:		return (        0xAB       );  // '«'     Left-Pointing Double Angle Quotation Mark
			case DIK_RBRACKET:		return (        0xBB       );  // '»'     Right-Pointing Double Angle Quotation Mark
			case DIK_A:				return (!caps ? 0xE1 : 0xC1);  // 'á' 'Á' Letter A With Acute
			case DIK_S:				return (        0xDF       );  // 'ß'     Latin Small Letter Sharp S
			case DIK_D:				return (!caps ? 0xF0 : 0xD0);  // 'ð' 'Ð' Latin Letter Eth
			case DIK_L:				return (!caps ? 0xF8 : 0xD8);  // 'ø' 'Ø' Latin Letter O With Stroke
			case DIK_SEMICOLON:		return (        0xB6       );  // '¶'     Pilcrow Sign
			case DIK_APOSTROPHE:	return (        0xB4       );  // '´'     Acute Accent
			case DIK_BACKSLASH:		return (        0xAC       );  // '¬'     Not Sign
			case DIK_Z:				return (!caps ? 0xE6 : 0xC6);  // 'æ' 'Æ' Latin Letter Ae
			case DIK_C:				return (        0xA9       );  // '©'     Copyright Sign
			case DIK_N:				return (!caps ? 0xF1 : 0xD1);  // 'ñ' 'Ñ' Latin Letter N With Tilde
			case DIK_M:				return (        0xB5       );  // 'µ'     Micro Sign
			case DIK_COMMA:			return (!caps ? 0xE7 : 0xC7);  // 'ç' 'Ç' Latin Letter C With Cedilla
			case DIK_SLASH:			return (        0xBF       );  // '¿'     Inverted Question Mark
			}
		}
	}

	// [key] or [[SHIFT] + [CAPS] + key]
	else 
	{
		bool conv = (shft ^ caps);
		unsigned char convertupper = conv ? 0x20 : 0;

		if (german)
		{
			// German
			switch(key)
			{
			case DIK_GRAVE:			return (!shft ? 0x5E : 0xB0);  // '^' '°' Circumflex Accent / Degree Sign
			case DIK_1:				return (!conv ? 0x31 : 0x21);  // '1' '!' Digit One / Exclamation Mark
			case DIK_2:				return (!conv ? 0x32 : 0x22);  // '2' '"' Digit Two / Quotation Mark
			case DIK_3:				return (!conv ? 0x33 : 0xA7);  // '3' '§' Digit Three / Section Sign
			case DIK_4:				return (!conv ? 0x34 : 0x24);  // '4' '$' Digit Four / Dollar Sign
			case DIK_5:				return (!conv ? 0x35 : 0x25);  // '5' '%' Digit Five / Percent Sign
			case DIK_6:				return (!conv ? 0x36 : 0x26);  // '6' '&' Digit Six / Ampersand
			case DIK_7:				return (!conv ? 0x37 : 0x2F);  // '7' '/' Digit Seven / Solidus
			case DIK_8:				return (!conv ? 0x38 : 0x28);  // '8' '(' Digit Eight / Left Parenthesis
			case DIK_9:				return (!conv ? 0x39 : 0x29);  // '9' ')' Digit Nine / Right Parenthesis
			case DIK_0:				return (!conv ? 0x30 : 0x3D);  // '0' '=' Digit Zero / Equals Sign
			case DIK_MINUS:			return (!conv ? 0xDF : 0x3F);  // 'ß' '?' Latin Small Letter Sharp S / Question Mark
			case DIK_EQUALS:		return (!shft ? 0xB4 : 0x60);  // '´' '`' Acute Accent / Grave Accent
			case DIK_Q:				return (0x71 - convertupper);  // 'q' 'Q' Latin Letter Q
			case DIK_W:				return (0x77 - convertupper);  // 'w' 'W' Latin Letter W
			case DIK_E:				return (0x65 - convertupper);  // 'e' 'E' Latin Letter E
			case DIK_R:				return (0x72 - convertupper);  // 'r' 'R' Latin Letter R
			case DIK_T:				return (0x74 - convertupper);  // 't' 'T' Latin Letter T
			case DIK_Y:				return (0x7A - convertupper);  // 'z' 'Z' Latin Letter Z
			case DIK_U:				return (0x75 - convertupper);  // 'u' 'U' Latin Letter U
			case DIK_I:				return (0x69 - convertupper);  // 'i' 'I' Latin Letter I
			case DIK_O:				return (0x6F - convertupper);  // 'o' 'O' Latin Letter O
			case DIK_P:				return (0x70 - convertupper);  // 'p' 'P' Latin Letter P
			case DIK_LBRACKET:		return (!conv ? 0xFC : 0xDC);  // 'ü' 'Ü' Latin Letter U with Diaeresis
			case DIK_RBRACKET:		return (!conv ? 0x2B : 0x2A);  // '+' '*' Plus Sign / Asterisk
			case DIK_A:				return (0x61 - convertupper);  // 'a' 'A' Latin Letter A
			case DIK_S:				return (0x73 - convertupper);  // 's' 'S' Latin Letter S
			case DIK_D:				return (0x64 - convertupper);  // 'd' 'D' Latin Letter D
			case DIK_F:				return (0x66 - convertupper);  // 'f' 'F' Latin Letter F
			case DIK_G:				return (0x67 - convertupper);  // 'g' 'G' Latin Letter G
			case DIK_H:				return (0x68 - convertupper);  // 'h' 'H' Latin Letter H
			case DIK_J:				return (0x6A - convertupper);  // 'j' 'J' Latin Letter J
			case DIK_K:				return (0x6B - convertupper);  // 'k' 'K' Latin Letter K
			case DIK_L:				return (0x6C - convertupper);  // 'l' 'L' Latin Letter L
			case DIK_SEMICOLON:		return (!conv ? 0xF6 : 0xD6);  // 'ö' 'Ö' Latin Letter O with Diaeresis
			case DIK_APOSTROPHE:	return (!conv ? 0xE4 : 0xC4);  // 'ä' 'Ä' Latin Letter A with Diaeresis
			case DIK_BACKSLASH:		return (!conv ? 0x23 : 0x27);  // '#' ''' Number Sign / Apostrophe
			case DIK_OEM_102:		return (!shft ? 0x3C : 0x3E);  // '<' '>' Less-Than Sign / Greater-Than Sign
			case DIK_Z:				return (0x79 - convertupper);  // 'y' 'Y' Latin Letter Z
			case DIK_X:				return (0x78 - convertupper);  // 'x' 'X' Latin Letter X
			case DIK_C:				return (0x63 - convertupper);  // 'c' 'C' Latin Letter C
			case DIK_V:				return (0x76 - convertupper);  // 'v' 'V' Latin Letter V
			case DIK_B:				return (0x62 - convertupper);  // 'b' 'B' Latin Letter B
			case DIK_N:				return (0x6E - convertupper);  // 'n' 'N' Latin Letter N
			case DIK_M:				return (0x6D - convertupper);  // 'm' 'M' Latin Letter M
			case DIK_COMMA:			return (!conv ? 0x2C : 0x3B);  // ',' ';' Comma / Semicolon
			case DIK_PERIOD:		return (!conv ? 0x2E : 0x3A);  // '.' ':' Full Stop / Greater-Than Sign
			case DIK_SLASH:			return (!shft ? 0x2D : 0x5F);  // '-' '_' Hyphen-Minus / Low Line
			}
		}
		else
		{
			// US-International (CAPS LOCK toggles letters only)
			switch(key)
			{
			case DIK_GRAVE:			return (!shft ? 0x60 : 0x7E);  // '`' '~' Grave Accent / Tilde
			case DIK_1:				return (!shft ? 0x31 : 0x21);  // '1' '!' Digit One / Exclamation Mark
			case DIK_2:				return (!shft ? 0x32 : 0x40);  // '2' '@' Digit Two / Commercial At
			case DIK_3:				return (!shft ? 0x33 : 0x23);  // '3' '#' Digit Three / Number Sign
			case DIK_4:				return (!shft ? 0x34 : 0x24);  // '4' '$' Digit Four / Dollar Sign
			case DIK_5:				return (!shft ? 0x35 : 0x25);  // '5' '%' Digit Five / Percent Sign
			case DIK_6:				return (!shft ? 0x36 : 0x5E);  // '6' '^' Digit Six / Circumflex Accent
			case DIK_7:				return (!shft ? 0x37 : 0x26);  // '7' '&' Digit Seven / Ampersand
			case DIK_8:				return (!shft ? 0x38 : 0x2A);  // '8' '*' Digit Eight / Asterisk
			case DIK_9:				return (!shft ? 0x39 : 0x28);  // '9' '(' Digit Nine / Left Parenthesis
			case DIK_0:				return (!shft ? 0x30 : 0x29);  // '0' ')' Digit Zero / Right Parenthesis
			case DIK_MINUS:			return (!shft ? 0x2D : 0x5F);  // '-' '_' Hyphen-Minus / Low Line
			case DIK_EQUALS:		return (!shft ? 0x3D : 0x2B);  // '=' '+' Equals Sign / Plus Sign
			case DIK_Q:				return (0x71 - convertupper);  // 'q' 'Q' Latin Letter Q
			case DIK_W:				return (0x77 - convertupper);  // 'w' 'W' Latin Letter W
			case DIK_E:				return (0x65 - convertupper);  // 'e' 'E' Latin Letter E
			case DIK_R:				return (0x72 - convertupper);  // 'r' 'R' Latin Letter R
			case DIK_T:				return (0x74 - convertupper);  // 't' 'T' Latin Letter T
			case DIK_Y:				return (0x79 - convertupper);  // 'y' 'Y' Latin Letter Y
			case DIK_U:				return (0x75 - convertupper);  // 'u' 'U' Latin Letter U
			case DIK_I:				return (0x69 - convertupper);  // 'i' 'I' Latin Letter I
			case DIK_O:				return (0x6F - convertupper);  // 'o' 'O' Latin Letter O
			case DIK_P:				return (0x70 - convertupper);  // 'p' 'P' Latin Letter P
			case DIK_LBRACKET:		return (!shft ? 0x5B : 0x7B);  // '[' '{' Left Square Bracket / Left Curly Bracket
			case DIK_RBRACKET:		return (!shft ? 0x5D : 0x7D);  // ']' '}' Right Square Bracket / Right Curly Bracket
			case DIK_A:				return (0x61 - convertupper);  // 'a' 'A' Latin Letter A
			case DIK_S:				return (0x73 - convertupper);  // 's' 'S' Latin Letter S
			case DIK_D:				return (0x64 - convertupper);  // 'd' 'D' Latin Letter D
			case DIK_F:				return (0x66 - convertupper);  // 'f' 'F' Latin Letter F
			case DIK_G:				return (0x67 - convertupper);  // 'g' 'G' Latin Letter G
			case DIK_H:				return (0x68 - convertupper);  // 'h' 'H' Latin Letter H
			case DIK_J:				return (0x6A - convertupper);  // 'j' 'J' Latin Letter J
			case DIK_K:				return (0x6B - convertupper);  // 'k' 'K' Latin Letter K
			case DIK_L:				return (0x6C - convertupper);  // 'l' 'L' Latin Letter L
			case DIK_SEMICOLON:		return (!shft ? 0x3B : 0x3A);  // ';' ':' Semicolon / Colon
			case DIK_APOSTROPHE:	return (!shft ? 0x27 : 0x22);  // ''' '"' Apostrophe / Quotation Mark
			case DIK_BACKSLASH:		return (!shft ? 0x5C : 0x7C);  // '\' '|' Reverse Solidus / Vertical Line
			case DIK_Z:				return (0x7A - convertupper);  // 'z' 'Z' Latin Letter Z
			case DIK_X:				return (0x78 - convertupper);  // 'x' 'X' Latin Letter X
			case DIK_C:				return (0x63 - convertupper);  // 'c' 'C' Latin Letter C
			case DIK_V:				return (0x76 - convertupper);  // 'v' 'V' Latin Letter V
			case DIK_B:				return (0x62 - convertupper);  // 'b' 'B' Latin Letter B
			case DIK_N:				return (0x6E - convertupper);  // 'n' 'N' Latin Letter N
			case DIK_M:				return (0x6D - convertupper);  // 'm' 'M' Latin Letter M
			case DIK_COMMA:			return (!shft ? 0x2C : 0x3C);  // ',' '<' Comma / Less-Than Sign
			case DIK_PERIOD:		return (!shft ? 0x2E : 0x3E);  // '.' '>' Full Stop / Greater-Than Sign
			case DIK_SLASH:			return (!shft ? 0x2F : 0x3F);  // '/' '?' Solidus / Question Mark
			}
		}
	}

	// not found
	return 0;
}

#ifdef COMPILING_SPACER

DWORD zCInput_Win32::GetWin32CodeFromDos32Code(const DWORD a_dwDos32Code)
{
	switch (a_dwDos32Code)
	{
		 case DOSKEY_ESC					:     return DIK_ESCAPE				;      break;			
		 case DOSKEY_PLUS					:     return DIK_RBRACKET 			;      break;		
		 case DOSKEY_MINUS 					:     return DIK_LBRACKET 			;      break;		
		 case DOSKEY_SPACE 					:     return DIK_SPACE				;      break;		
		 case DOSKEY_OQUOTE					:     return DIK_GRAVE 				;      break;			
		 case DOSKEY_CQUOTE					:	  return 222 					;      break;		
		 case DOSKEY_LHOOK 					:     return DIK_LBRACKET 			;      break;		
		 case DOSKEY_RHOOK 					:     return DIK_RBRACKET 			;      break;		
		 case DOSKEY_BSLASH					:     return DIK_BACKSLASH 			;      break;			
		 case DOSKEY_FSLASH					:     return DIK_SLASH 				;      break;			
		 case DOSKEY_SEMICOLON 				:     return DIK_SEMICOLON 			;      break;			
		 case DOSKEY_COMMA 					:     return DIK_COMMA 				;      break;			
		 case DOSKEY_DOT					:     return DIK_PERIOD 			;      break;			
		 case DOSKEY_ENTER 					:     return DIK_RETURN				;      break;			
		 case DOSKEY_BACKSPACE 				:     return DIK_BACK				;      break;		
		 case DOSKEY_TAB					:     return DIK_TAB				;      break;			
		 case DOSKEY_GREYPLUS				:     return DIK_ADD 				;      break;		
		 case DOSKEY_GREYMINUS 				:     return DIK_SUBTRACT 			;      break;		
		 case DOSKEY_PAD_5					:     return DIK_NUMPAD5			;      break;			
		 case DOSKEY_PAD_MUL				:     return DIK_MULTIPLY			;      break;		
		 case DOSKEY_PAD_DIV				:     return DIK_SLASH				;      break;		
		 case DOSKEY_PAD_LEFT				:     return DIK_NUMPAD4			;      break;			
		 case DOSKEY_PAD_RIGHT 				:     return DIK_NUMPAD6			;      break;			
		 case DOSKEY_PAD_UP					:     return DIK_NUMPAD8			;      break;			
		 case DOSKEY_PAD_DOWN				:     return DIK_NUMPAD2			;      break;			
		 case DOSKEY_PAD_HOME				:     return DIK_NUMPAD7			;      break;			
		 case DOSKEY_PAD_END				:     return DIK_NUMPAD1			;      break;			
		 case DOSKEY_PAD_PGDN				:     return DIK_NUMPAD3			;      break;			
		 case DOSKEY_PAD_PGUP				:     return DIK_NUMPAD9			;      break;			
		 case DOSKEY_PAD_INS				:     return DIK_NUMPAD0			;      break;			
		 case DOSKEY_PAD_DEL				:     return DIK_DECIMAL			;      break;			
		 case DOSKEY_LEFT					:     return DIK_LEFT 				;      break;		
		 case DOSKEY_RIGHT 					:     return DIK_RIGHT 				;      break;			
		 case DOSKEY_UP						:     return DIK_UP 				;      break;			
		 case DOSKEY_DOWN					:     return DIK_DOWN 				;      break;		
		 case DOSKEY_HOME					:     return DIK_HOME 				;      break;		
		 case DOSKEY_END					:     return DIK_END 				;      break;		
		 case DOSKEY_PGUP					:     return DIK_PRIOR 				;      break;			
		 case DOSKEY_PGDN					:     return DIK_NEXT 				;      break;		
		 case DOSKEY_INS					:     return DIK_INSERT 			;      break;			
		 case DOSKEY_DEL					:     return DIK_DELETE 			;      break;			
		 case DOSKEY_CAPSLOCK				:     return DIK_CAPITAL			;      break;			
		 case DOSKEY_SCROLLLOCK				:     return DIK_SCROLL				;      break;			
		 case DOSKEY_NUMLOCK				:     return DIK_NUMLOCK			;      break;			
		 case DOSKEY_PAUSE 					:     return DIK_PAUSE				;      break;		
		 case DOSKEY_LALT					:     return DIK_LMENU				;      break;		
		 case DOSKEY_RALT					:     return DIK_RMENU 				;      break;			
		 case DOSKEY_LCTRL 					:     return DIK_LCONTROL			;      break;		
		 case DOSKEY_RCTRL 					:     return DIK_RCONTROL 			;      break;		
		 case DOSKEY_LSHIFT					:     return DIK_LSHIFT				;      break;			
		 case DOSKEY_WIN_LWINKEY			:     return DIK_LWIN 				;      break;		
		 case DOSKEY_WIN_RWINKEY			:     return DIK_RWIN 				;      break;		
		 case DOSKEY_WIN_CONTEXT			:	  return 349 					;      break;	
		 case DOSKEY_F1						:     return DIK_F1					;      break;
		 case DOSKEY_F2						:     return DIK_F2					;      break;
		 case DOSKEY_F3						:     return DIK_F3					;      break;
		 case DOSKEY_F4						:     return DIK_F4					;      break;
		 case DOSKEY_F5						:     return DIK_F5					;      break;
		 case DOSKEY_F6						:     return DIK_F6					;      break;
		 case DOSKEY_F7						:     return DIK_F7					;      break;
		 case DOSKEY_F8						:     return DIK_F8					;      break;
		 case DOSKEY_F9						:     return DIK_F9					;      break;
		 case DOSKEY_F10					:     return DIK_F10				;      break;
		 case DOSKEY_F11					:     return DIK_F11				;      break;
		 case DOSKEY_F12					:     return DIK_F12				;      break;
		 case DOSKEY_1 						:     return DIK_1					;      break;
		 case DOSKEY_2 						:     return DIK_2					;      break;
		 case DOSKEY_3 						:     return DIK_3					;      break;
		 case DOSKEY_4 						:     return DIK_4					;      break;
		 case DOSKEY_5 						:     return DIK_5					;      break;
		 case DOSKEY_6 						:     return DIK_6					;      break;
		 case DOSKEY_7 						:     return DIK_7					;      break;
		 case DOSKEY_8 						:     return DIK_8					;      break;
		 case DOSKEY_9 						:     return DIK_9					;      break;
		 case DOSKEY_0 						:     return DIK_0					;      break;
		 case DOSKEY_A 						:     return DIK_A					;      break;
		 case DOSKEY_B 						:     return DIK_B					;      break;
		 case DOSKEY_C 						:     return DIK_C					;      break;
		 case DOSKEY_D 						:     return DIK_D					;      break;
		 case DOSKEY_E 						:     return DIK_E					;      break;
		 case DOSKEY_F 						:     return DIK_F					;      break;
		 case DOSKEY_G 						:     return DIK_G					;      break;
		 case DOSKEY_H 						:     return DIK_H					;      break;
		 case DOSKEY_I 						:     return DIK_I					;      break;
		 case DOSKEY_J 						:     return DIK_J					;      break;
		 case DOSKEY_K 						:     return DIK_K					;      break;
		 case DOSKEY_L 						:     return DIK_L					;      break;
		 case DOSKEY_M 						:     return DIK_M					;      break;
		 case DOSKEY_N 						:     return DIK_N					;      break;
		 case DOSKEY_O 						:     return DIK_O					;      break;
		 case DOSKEY_P 						:     return DIK_P					;      break;
		 case DOSKEY_Q 						:     return DIK_Q					;      break;
		 case DOSKEY_R 						:     return DIK_R					;      break;
		 case DOSKEY_S 						:     return DIK_S					;      break;
		 case DOSKEY_T 						:     return DIK_T					;      break;
		 case DOSKEY_U 						:     return DIK_U					;      break;
		 case DOSKEY_V 						:     return DIK_V					;      break;
		 case DOSKEY_W 						:     return DIK_W					;      break;
		 case DOSKEY_X 						:     return DIK_X					;      break;
// [BENDLIN] Addon - KeybFix
#ifdef LANG_ENU
		 case DOSKEY_Y 						:     return DIK_Y					;      break;
		 case DOSKEY_Z 						:     return DIK_Z					;	   break;
#else//LANG_DEU
		 case DOSKEY_Y 						:     return DIK_Z					;      break;
		 case DOSKEY_Z 						:     return DIK_Y					;	   break;
#endif
		 default							:	  return -1						;	   break;
	};
};

#endif

////////////////////////////////////////////////////////////////////////////////
//
//	InitDInput_Keyboard
//
//	2002-05-11	[BENDLIN]
//
//				KEY_ESC and KEY_ENTER auto-repeat enabled!
//				(currently for Gothic only, to avoid side effects in Spacer)
//
////////////////////////////////////////////////////////////////////////////////

static zBOOL InitDInput_Keyboard (HWND hWnd, HINSTANCE hInstance)
{
	if (lpDInput->CreateDeviceEx(GUID_SysKeyboard, IID_IDirectInputDevice7, (void**)&lpDIKeyboard, NULL) != DI_OK)
		MessageBox(NULL,"DirectInput(Keyboard): CreateDevice failed","CreateDevice",MB_OK);

	if (lpDIKeyboard->SetDataFormat(&c_dfDIKeyboard) != DI_OK)
		MessageBox(NULL,"DirectInput(Keyboard): SetDataFormat failed","SetDataFormat",MB_OK);

	/*
	if (lpDIKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND ) != DI_OK)
		MessageBox(NULL,"DirectInput(Keyboard): SetCooperativeLevel failed","SetCooperativeLevel",MB_OK);
	*/
	
	#ifdef COMPILING_SPACER
		if (lpDIKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK)
			MessageBox(NULL,"DirectInput(Keyboard): SetCooperativeLevel failed","SetCooperativeLevel",MB_OK);
	#else
		if (lpDIKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY) != DI_OK)
			MessageBox(NULL,"DirectInput(Keyboard): SetCooperativeLevel failed","SetCooperativeLevel",MB_OK);
	#endif	

	{
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = KEYBOARD_BUFFER_SIZE;
		if (lpDIKeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph) != DI_OK) 
			MessageBox(NULL,"DirectInput(Keyboard): SetProperty failed","SetProperty",MB_OK);
	};

	for (int i = 0 ; i < MAX_KEYS_AND_CODES; i++)
	{
		keyevent[i] = false;
		keytoggle[i] = false;
		keyRepeatEnabled[i] = true;
	}
	#ifdef COMPILING_SPACER
		keyRepeatEnabled[KEY_ESC]	= false;
		keyRepeatEnabled[KEY_ENTER]	= false;
	#endif	

	return TRUE;
};

////////////////////////////////////////////////////////////////////////////////
//
//	InitDInput_Mouse
//
//	2002-05-11	[BENDLIN]
//
//				Init of mouse buttons added (mapped to key events!).
//				Mouse init changed (up to 8 buttons - DirectInput7 and above)
//
////////////////////////////////////////////////////////////////////////////////

static zBOOL InitDInput_Mouse (HWND hWnd, HINSTANCE hInstance)
{
	mouseAvailable	= FALSE;
	mouseEnabled	= FALSE;
	memset			(&mouseState, 0, sizeof(mouseState));

	for (int i = MIN_MOUSE_BTNS_AND_CODES; i < MAX_MOUSE_BTNS_AND_CODES; i++)
	{
		keyevent[i] = false;
		keytoggle[i] = false;
		keyRepeatEnabled[i] = ( (i >= MIN_MOUSE_BTNS) && (i < MAX_MOUSE_BTNS) ); // enable auto-repeat for buttons
	}

	#ifdef COMPILING_SPACER
		return FALSE;
	#endif
	#ifdef DISABLE_MOUSE
		return FALSE;
	#endif

	{
		//
	    HRESULT hr;
		if (lpDInput->CreateDeviceEx(	GUID_SysMouse, 
										IID_IDirectInputDevice7, 
										(void**)&lpDIMouse, 
										NULL) != DI_OK)
		{
			MessageBox(NULL,"DirectInput(Mouse): CreateDevice failed","CreateDevice",MB_OK);
			return FALSE;
		}

		// [BENDLIN] changed to c_dfDIMouse2 (up to 8 mouse buttons)
		hr = lpDIMouse->SetDataFormat( &c_dfDIMouse2 );
		if ( FAILED(hr) ) 
		{
			MessageBox(NULL,"DirectInput(Mouse): SetDataFromat failed","SetDataFromat",MB_OK);
			return FALSE;
		}

		// Im debug sollte der Mode 'nonexclusive' sein, damit man z.B. breakpoints im devstudio bearbeiten kann
#ifdef _DEBUG
		// hr = lpDIMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		hr = lpDIMouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
#else
		hr = lpDIMouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
#endif
 		if (FAILED(hr)) {
			MessageBox(NULL,"DirectInput(Mouse): SetCooperativeLevel failed","SetCooperativeLevel",MB_OK);
			return FALSE;
		}

		// create a win32 event which is signaled when mouse data is availible
		// (FIXME: noetig?)
		{
			g_hMouseEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
			if (NULL == g_hMouseEvent) return FALSE;

			// give the event to the mouse device
			hr = lpDIMouse->SetEventNotification( g_hMouseEvent );
			if (FAILED(hr)) return FALSE;
		};

		// setup the buffer size for the mouse data
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize		= sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj		= 0;
		dipdw.diph.dwHow		= DIPH_DEVICE;
		dipdw.dwData			= MOUSE_BUFFER_SIZE;

		hr = lpDIMouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
		if ( FAILED(hr) ) 
			return FALSE;

		/* if (lpDIMouse->Acquire() != DI_OK) 
		{
			MessageBox(NULL,"DirectInput(Mouse): Acquire failed","Acquire",MB_OK);
		}*/
	};
	mouseAvailable = TRUE;
	return mouseAvailable;
};

////////////////////////////////////////////////////////////////////////////////
//
//	InitDInput_Joystick
//
//	2002-05-15	[BENDLIN] introduced
//
////////////////////////////////////////////////////////////////////////////////

// [BENDLIN] get first Joystick
BOOL CALLBACK _EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
    HRESULT hr;

    // Obtain an interface to the enumerated joystick.
    hr = lpDInput->CreateDeviceEx(pdidInstance->guidInstance,
								  IID_IDirectInputDevice7,
								  (void**)&lpDIJoystick,
								  NULL);
    if(FAILED(hr)) 
        return DIENUM_CONTINUE;

    return DIENUM_STOP;
}

// [BENDLIN] set range for all axis
BOOL CALLBACK _EnumJoystickObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext)
{
	LPDIRECTINPUTDEVICE7 pdi = (LPDIRECTINPUTDEVICE7)(pContext);

	// For axes that are returned, set the DIPROP_RANGE property for the
	// enumerated axis in order to scale min/max values.
	if ( (pdi) && (pdidoi->dwType & DIDFT_AXIS) )
	{
		DIPROPRANGE diprg; 
		diprg.diph.dwSize		= sizeof(DIPROPRANGE); 
		diprg.diph.dwHeaderSize	= sizeof(DIPROPHEADER); 
		diprg.diph.dwHow		= DIPH_BYID; 
		diprg.diph.dwObj		= pdidoi->dwType; // Specify the enumerated axis
		diprg.lMin				= -1000; 
		diprg.lMax				= +1000; 

		// Set the range for the axis
		if ( FAILED(pdi->SetProperty(DIPROP_RANGE, &diprg.diph)) ) 
            return DIENUM_STOP;
    }
    return DIENUM_CONTINUE;
}

static zBOOL InitDInput_Joystick (HWND hWnd, HINSTANCE hInstance)
{
	joystickAvailable	= FALSE;
	joystickEnabled		= FALSE;

	for (int i = MIN_JOY_BTNS_AND_CODES; i < MAX_JOY_BTNS_AND_CODES; i++)
	{
		keyevent[i] = false;
		keytoggle[i] = false;
		keyRepeatEnabled[i] = ( (i >= MIN_JOY_BTNS) && (i < MAX_JOY_BTNS) ); // enable auto-repeat for buttons
	}

	#ifdef COMPILING_SPACER
		return FALSE;
	#endif
	#ifdef DISABLE_JOYSTICK
		return FALSE;
	#endif

	lpDInput->EnumDevices(DIDEVTYPE_JOYSTICK, _EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);
	if ( lpDIJoystick )
	{
		if ( FAILED(lpDIJoystick->SetDataFormat(&c_dfDIJoystick)) ) 
		{
			MessageBox(NULL, "DirectInput(Joystick): SetDataFromat failed", "SetDataFromat", MB_OK);
			return FALSE;
		}

 		if ( FAILED(lpDIJoystick->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)) )
		{
			MessageBox(NULL, "DirectInput(Joystick): SetCooperativeLevel failed", "SetCooperativeLevel", MB_OK);
			return FALSE;
		}

		if (FAILED(lpDIJoystick->EnumObjects(_EnumJoystickObjectsCallback, (VOID*)lpDIJoystick, DIDFT_AXIS)) )
		{
			MessageBox(NULL, "DirectInput(Joystick): EnumObjects (scaling axis) failed", "EnumObjects", MB_OK);
			return FALSE;
		}

		// setup the buffer size for the joystick data
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize		= sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj		= 0;
		dipdw.diph.dwHow		= DIPH_DEVICE;
		dipdw.dwData			= JOYSTICK_BUFFER_SIZE;

		if ( FAILED(lpDIJoystick->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)) ) 
			return FALSE;
	};

	joystickAvailable = TRUE;
	return joystickAvailable;
};

int InitDInput(HWND hWnd, HINSTANCE hInstance)
{
	zERR_MESSAGE(4, zERR_BEGIN,"D: INPUT: Initializing DirectInput ..");

	focusWinHandle = hWnd;

	// Direct-Input
	if (DirectInputCreateEx(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput7, (void**)&lpDInput, NULL) != DI_OK)
		MessageBox(NULL,"DirectInput: DirectInputCreate failed","DirectInputCreate",MB_OK);

	// Keyboard
	{
		zBOOL res = InitDInput_Keyboard	(hWnd, hInstance);
		if (res)	zERR_MESSAGE(4, 0, "D: INPUT: keyboard initialized");
		else		zERR_WARNING(	   "D: INPUT: keyboard NOT initialized ..");	
	}

	// Mouse 
	{
		zBOOL res = InitDInput_Mouse	(hWnd, hInstance);
		if (res)	zERR_MESSAGE(4, 0, "D: INPUT: mouse initialized.");	
		else		zERR_WARNING(	   "D: INPUT: mouse NOT initialized.");	
	}

	// Joystick
	{
		zBOOL res = InitDInput_Joystick	(hWnd, hInstance);
		if (res)	zERR_MESSAGE(4, 0, "D: INPUT: joystick initialized.");	
		else		zERR_WARNING(	   "D: INPUT: joystick NOT initialized.");	
	};

	zERR_MESSAGE(4, zERR_END, "");

	return(0);
}

int UpdateDInput()
{			
	HRESULT result = lpDIKeyboard->Acquire();
	if (SUCCEEDED(result))
	{
		result = lpDIKeyboard->Poll();

		if(!lpDIKeyboard)	return 0;	
		
		DIDEVICEOBJECTDATA key_pressed[KEYBOARD_BUFFER_SIZE]; 
		DWORD dwItems = KEYBOARD_BUFFER_SIZE;

		memset(&keytoggle,0,sizeof(keytoggle));	

		result = lpDIKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), key_pressed, &dwItems, 0);
		if (SUCCEEDED(result))
		{
			switch (result)
			{
			case DI_BUFFEROVERFLOW:
				zERR_MESSAGE(4,0,"B: KBD: DInput: Buffer overflow");
				break;
			default:
				if (SUCCEEDED(result)) 
				{		
					for( int i = 0; i < dwItems; i++ ) // Keybuffer auswerten
					{
						int  keyId			= key_pressed[i].dwOfs;
						bool keyEventBefore	= keyevent[keyId];					

						keyevent[keyId]		= ((key_pressed[i].dwData & 0x80) == 0x80);												
						if (keyevent[keyId]) 
						{
							keybuffer.InsertEnd(keyId);				
							keytoggle[keyId]= !keyEventBefore;
							//if (keytoggle[keyId]) zERR_MESSAGE(4,0,"B: KBD: DInput: Key "+zSTRING(keyId)+" toggled");
						}							
					}			
				} 
				else 
				{
					zERR_MESSAGE(4,0,"B: KBD: DInput: Unknown error");
				}
			}
		}
	}

	if (!SUCCEEDED(result))	
	{
		memset(&keyevent,0,sizeof(keyevent));
		memset(&keytoggle,0,sizeof(keytoggle));
	}

	// Mouse
	UpdateMouse();

	// Joystick
	UpdateJoystick();

	// FIXME: HARDCORE EVIL -> lazy + goldmaster
	if (!oCGame::GetUseOldControls())
	{
		if ( (NULL == lpDIMouse) || !mouseEnabled)
		{
			static zREAL noKeyRotateTimer	= 0;

			if ( (!zinput->GetState(GAME_LEFT)) && (!zinput->GetState(GAME_RIGHT)) )
			{
				noKeyRotateTimer += ztimer.GetFrameTimeF()/ztimer.GetMotionFactor()/1000;
				if (noKeyRotateTimer>0.5F) ((zCInput_Win32*)zinput)->SetMouseIdle(TRUE);
			}
			else 
			{
				((zCInput_Win32*)zinput)->SetMouseIdle(FALSE);
				noKeyRotateTimer = 0;
			}	

		};
	};

	return(0);
}

//-----------------------------------------------------------------------------
// Function: SetAcquire
//
// Description: 
//      Acquire or unacquire the mouse, depending on if the app is active
//       Input device must be acquired before the GetDeviceState is called
//
//-----------------------------------------------------------------------------

zBOOL SetAcquireMouse()
{
    // nothing to do if lpDIMouse is NULL
    if (NULL == lpDIMouse)
		return FALSE;

	if (mouseEnabled)	lpDIMouse->Acquire();
	else				lpDIMouse->Unacquire();

    return TRUE;
}

zBOOL SetAcquireJoystick()
{
    // nothing to do if lpDIJoystick is NULL
    if (NULL == lpDIJoystick)
		return FALSE;

	if (joystickEnabled)	lpDIJoystick->Acquire();
	else					lpDIJoystick->Unacquire();

    return TRUE;
}

// [BENDLIN] 2002-05-11, introduced
static void SetMouseKeyStateAndInsert(int keyId, DWORD dwData)
{
	bool keyEventBefore = keyevent[keyId];
	keyevent[keyId] = ((dwData & 0x80) == 0x80);
	if ( keyevent[keyId] )
	{
		keybuffer.InsertEnd(keyId);
		keytoggle[keyId] = !keyEventBefore;
	}							
}

////////////////////////////////////////////////////////////////////////////////
//
//	UpdateMouse
//
//	2002-05-11	[BENDLIN]
//
//				Hack removed (mapping of mouse buttons to game keys)
//
////////////////////////////////////////////////////////////////////////////////

static void UpdateMouse()
{
	if (!mouseEnabled) return;

	#ifdef DISABLE_MOUSE
		return;
	#endif

	mouseState.xpos	= 0;
	mouseState.ypos	= 0;
	mouseState.zpos	= 0;
	// Mouse wheel does _NOT_ trigger 'key up'!
	keyevent[MOUSE_WHEELUP]		= false;
	keyevent[MOUSE_WHEELDOWN]	= false;

	if (lpDIMouse)
	{
		// untoggle all mouse buttons
		// for ( int i = MIN_MOUSE_BTNS_AND_CODES; i < MAX_MOUSE_BTNS_AND_CODES; i++ ) keytoggle[i] = false;

		SetAcquireMouse();

		// zTMouseState oldMouseState	= mouseState;

		BOOL                bDone;
		DIDEVICEOBJECTDATA  od;
		DWORD               dwElements;
		HRESULT             hr;

		// Attempt to read one data element.  Continue as long as
		// device data is available.
		lpDIMouse->Poll		();
		bDone				= FALSE;

		/*// Im Debug die Maus im Window zentrieren, damit Klicks moeglichst nie ausserhalb gelangen (noetig beim nonexcl. mode der Maus)
		#ifdef _DEBUG
				if (mouseEnabled)
					SetCursorPos(320,200);	// winAPI
		#endif*/

		while ( !bDone ) 
		{
			dwElements = 1;
			hr = lpDIMouse->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), 
											&od,
											&dwElements, 
											0 );

			if (hr == DIERR_INPUTLOST) 
			{
				SetAcquireMouse();
				break;
			}

			// Unable to read data or no data available
			if ( FAILED(hr) || dwElements == 0) 
			{
				break;
			}

			// look at the element to see what happened
			switch (od.dwOfs) 
			{     
				case DIMOFS_X:       // Mouse horizontal motion 
					mouseState.xpos	= int(od.dwData);
					break;

				case DIMOFS_Y:       // Mouse vertical motion 
					mouseState.ypos	= int(od.dwData);
					break;
				case DIMOFS_Z:       // Mouse wheel motion 
					{
						mouseState.zpos	= int(od.dwData);
						
						int keyId = 0;
						if ( mouseState.zpos > 0 ) keyId = MOUSE_WHEELUP;	else
						if ( mouseState.zpos < 0 ) keyId = MOUSE_WHEELDOWN;
						if ( keyId != 0 )
						{
							keyevent[keyId] = true;
							keytoggle[keyId] = true;
							keybuffer.InsertEnd(keyId);
						}
					};
					break;
				case DIMOFS_BUTTON0: // Left button pressed or released 
					{
						mouseState.buttonPressedLeft = ( (od.dwData & 0x80) == 0x80 );		
						SetMouseKeyStateAndInsert(MOUSE_BUTTONLEFT, od.dwData);
					};
					break;
				case DIMOFS_BUTTON1: // Right button pressed or released 
					{
						mouseState.buttonPressedRight = ( (od.dwData & 0x80) == 0x80 );		
						SetMouseKeyStateAndInsert(MOUSE_BUTTONRIGHT, od.dwData);
					};
					break;
				case DIMOFS_BUTTON2: // Mid button pressed or released 
					{
						mouseState.buttonPressedMid = ( (od.dwData & 0x80) == 0x80 );		
						SetMouseKeyStateAndInsert(MOUSE_BUTTONMID, od.dwData);
					};
					break;
				case DIMOFS_BUTTON3: // X1 mouse button (mostly: on left side, used for "back/previous")
					SetMouseKeyStateAndInsert(MOUSE_XBUTTON1, od.dwData);
					break;
				case DIMOFS_BUTTON4: // X2 mouse button (mostly: on right side, used for "next")
					SetMouseKeyStateAndInsert(MOUSE_XBUTTON2, od.dwData);
					break;
				case DIMOFS_BUTTON5: // X3 mouse button
					SetMouseKeyStateAndInsert(MOUSE_XBUTTON3, od.dwData);
					break;
				case DIMOFS_BUTTON6: // X4 mouse button
					SetMouseKeyStateAndInsert(MOUSE_XBUTTON4, od.dwData);
					break;
				case DIMOFS_BUTTON7: // X5 mouse button
					SetMouseKeyStateAndInsert(MOUSE_XBUTTON5, od.dwData);
					break;
			}
		}

		// wenn die maus sich längere zeit nicht in x richtung bewegt hat, wird das automatische zum gegner ausrichten aktiv
		// kleiner maus ring buffer, um hakeliges rotieren zu vermeiden

		// ( muss das hier sein?! - nico ) 
		// nö das muss nicht hier sein, sollte man evtl. auch in der ini abschaltbar machen 
		// weiteres prob: ringbuffer arbeiten fps abhängig, d.h. bei niedriger fps rate hat man eine trägere
		// bewegung

		// [EDENFELD] 1.20 was vielleicht gar nicht mal so schlecht ist (wenns ruckelt, möchte man vielleicht keine
		// sprunghaften bewegungen)
		// leider muss der Code zusätzlich auch sein, da ansonsten die PC-Turn Anis nicht korrekt abgespielt werden
		// wenn Dir was bessereres einfällt -> ich bin ganz Ohr

		// [EDENFELD] so nun ist der Kram durch ein Relaxaxon ersetz. Irgendwann mal wird sich trotzdem jemand über die statischen
		// üblen Sachen ärgern
		// da es aber eh nicht mehr schlimmer kommen kann in dieser Datei und es mal wieder kurz vor Goldmaster ist, spar ich mir
		// von meiner Unfähigkeit abzulenken

		static zCValueSmooth xpos;
		static zBOOL smoothInit		= FALSE;
		static zREAL noXMoveTimer	= 0;

		if (!smoothInit)
		{
			xpos.Set	   (mouseState.xpos);
			float inertia = zoptions->ReadReal("ENGINE", "zSmoothMouse", 3.0f);
			if (inertia==0) xpos.SetIsSmooth(FALSE);
			xpos.SetInertia(inertia);
			smoothInit = TRUE;
		}
		else
		{
			zREAL newX = mouseState.xpos;
			xpos.Smooth(newX);
			mouseState.xpos=newX;

		}

		if (zAbs(mouseState.xpos)<=0.0f)
		{
			noXMoveTimer += ztimer.GetFrameTimeF()/ztimer.GetMotionFactor()/1000;
			if (noXMoveTimer>0.5F) ((zCInput_Win32*)zinput)->SetMouseIdle(TRUE);
		}
		else 
		{
			((zCInput_Win32*)zinput)->SetMouseIdle(FALSE);
			noXMoveTimer	 = 0;
		}	
		
	};
};

////////////////////////////////////////////////////////////////////////////////
//
//	UpdateJoystick
//
//	2002-05-15	[BENDLIN] introduces
//
////////////////////////////////////////////////////////////////////////////////

static void SetJoystickKeyStateAndInsert(int keyId, DWORD dwData)
{
	bool keyEventBefore = keyevent[keyId];
	keyevent[keyId] = ((dwData & 0x80) == 0x80);
	if ( keyevent[keyId] )
	{
		keybuffer.InsertEnd(keyId);
		keytoggle[keyId] = !keyEventBefore;
	}							
}

static void UpdateJoystick()
{
	if (!joystickEnabled) return;

	#ifdef DISABLE_JOYSTICK
		return;
	#endif

	if ( lpDIJoystick )
	{
		// untoggle all joystick buttons
		// for ( int i = MIN_JOY_BTNS_AND_CODES; i < MAX_JOY_BTNS_AND_CODES; i++ ) keytoggle[i] = false;

		SetAcquireJoystick();

		BOOL                bDone;
		DIDEVICEOBJECTDATA  od;
		DWORD               dwElements;
		HRESULT             hr;

		// Attempt to read one data element.  Continue as long as
		// device data is available.
		lpDIJoystick->Poll();
		bDone = FALSE;

		while ( !bDone ) 
		{
			dwElements = 1;
			hr = lpDIJoystick->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &od, &dwElements, 0);

			if (hr == DIERR_INPUTLOST) 
			{
				SetAcquireJoystick();
				break;
			}

			// Unable to read data or no data available
			if ( FAILED(hr) || dwElements == 0) 
			{
				break;
			}

			// look at the element to see what happened
			switch (od.dwOfs) 
			{     
				case DIJOFS_X:	// x-axis
					{
						int keyId = 0;
						if ((int)(od.dwData) < -500)	keyId = JOY_LEFT;	else
						if ((int)(od.dwData) > 500)		keyId = JOY_RIGHT;

						if ( (keyId != 0) /*&& !keyevent[keyId]*/ )
						{
							bool keyEventBefore = keyevent[keyId];
							keyevent[keyId] = true;
							keytoggle[keyId] = !keyEventBefore;
							keybuffer.InsertEnd(keyId);
						}
						else
						{
							keyevent[JOY_LEFT]	= false;
							keyevent[JOY_RIGHT]	= false;
						}
					}
					break;
				case DIJOFS_Y:	// y-axis
					{
						int keyId = 0;
						if ((int)(od.dwData) < -500)	keyId = JOY_UP;	else
						if ((int)(od.dwData) > 500)		keyId = JOY_DOWN;

						if ( (keyId != 0) /*&& !keyevent[keyId]*/ )
						{
							bool keyEventBefore = keyevent[keyId];
							keyevent[keyId] = true;
							keytoggle[keyId] = !keyEventBefore;
							keybuffer.InsertEnd(keyId);
						}
						else
						{
							keyevent[JOY_UP]	= false;
							keyevent[JOY_DOWN]	= false;
						}
					}
					break;
				case DIJOFS_Z:			// z-axis (mostly throttle)
				case DIJOFS_SLIDER(0):	// u-axis (alternative throttle)
					{
						int keyId = 0;
						if ((int)(od.dwData) < -500)	keyId = THROTTLE_UP;	else
						if ((int)(od.dwData) > 500)		keyId = THROTTLE_DOWN;

						if ( (keyId != 0) /*&& !keyevent[keyId]*/ )
						{
							bool keyEventBefore = keyevent[keyId];
							keyevent[keyId] = true;
							keytoggle[keyId] = !keyEventBefore;
							keybuffer.InsertEnd(keyId);
						}
						else
						{
							keyevent[THROTTLE_UP]	= false;
							keyevent[THROTTLE_DOWN]	= false;
						}
					}
					break;
				case DIJOFS_RZ:			// z-axis-rotation (mostly rudder)
				case DIJOFS_SLIDER(1):	// v-axis (alternative rudder)
					{
						int keyId = 0;
						if ((int)(od.dwData) < -500)	keyId = RUDDER_LEFT;	else
						if ((int)(od.dwData) > 500)		keyId = RUDDER_RIGHT;

						if ( (keyId != 0) /*&& !keyevent[keyId]*/ )
						{
							bool keyEventBefore = keyevent[keyId];
							keyevent[keyId] = true;
							keytoggle[keyId] = !keyEventBefore;
							keybuffer.InsertEnd(keyId);
						}
						else
						{
							keyevent[RUDDER_LEFT]	= false;
							keyevent[RUDDER_RIGHT]	= false;
						}
					}
					break;
				// POVs
				case DIJOFS_POV(0):
				case DIJOFS_POV(1):
				case DIJOFS_POV(2):
				case DIJOFS_POV(3):
					{
						int keyId;
						if ((od.dwData > 36000) || (od.dwData < 0))			keyId = 0;				else
						if ((od.dwData >= 31500) || (od.dwData <= 4500))	keyId = JOY_POV_UP;		else
						if ((od.dwData > 4500) && (od.dwData < 13500))		keyId = JOY_POV_RIGHT;	else
						if ((od.dwData >= 13500) && (od.dwData <= 22500))	keyId = JOY_POV_DOWN;	else
						if ((od.dwData > 22500) && (od.dwData < 31500))		keyId = JOY_POV_LEFT;

						keyevent[JOY_POV_LEFT]	= false;
						keyevent[JOY_POV_RIGHT]	= false;
						keyevent[JOY_POV_UP]	= false;
						keyevent[JOY_POV_DOWN]	= false;
						if ( keyId != 0 )
						{
							bool keyEventBefore = keyevent[keyId];
							keyevent[keyId] = true;
							keytoggle[keyId] = !keyEventBefore;
							keybuffer.InsertEnd(keyId);
						}
					}
					break;
				// Buttons
				case DIJOFS_BUTTON0:
				case DIJOFS_BUTTON1:
				case DIJOFS_BUTTON2:
				case DIJOFS_BUTTON3:
				case DIJOFS_BUTTON4:
				case DIJOFS_BUTTON5:
				case DIJOFS_BUTTON6:
				case DIJOFS_BUTTON7:
				case DIJOFS_BUTTON8:
				case DIJOFS_BUTTON9:
				case DIJOFS_BUTTON10:
				case DIJOFS_BUTTON11:
				case DIJOFS_BUTTON12:
				case DIJOFS_BUTTON13:
				case DIJOFS_BUTTON14:
				case DIJOFS_BUTTON15:
				case DIJOFS_BUTTON16:
				case DIJOFS_BUTTON17:
				case DIJOFS_BUTTON18:
				case DIJOFS_BUTTON19:
				case DIJOFS_BUTTON20:
				case DIJOFS_BUTTON21:
				case DIJOFS_BUTTON22:
				case DIJOFS_BUTTON23:
				case DIJOFS_BUTTON24:
				case DIJOFS_BUTTON25:
				case DIJOFS_BUTTON26:
				case DIJOFS_BUTTON27:
				case DIJOFS_BUTTON28:
				case DIJOFS_BUTTON29:
				case DIJOFS_BUTTON30:
				case DIJOFS_BUTTON31:
					SetMouseKeyStateAndInsert(JOY_BUTTON_1 + (od.dwOfs - DIJOFS_BUTTON0), od.dwData);
					break;
			}
		}
	};
};

int ReleaseDInput()
{
	if (lpDIKeyboard != NULL)
	{
		lpDIKeyboard->Unacquire();
		lpDIKeyboard->Release();
		lpDIKeyboard = NULL;
	}

	if (lpDIMouse != NULL)
	{
		lpDIMouse->Unacquire();
		lpDIMouse->Release();
		lpDIMouse = NULL;
	}

	if (lpDIJoystick != NULL)
	{
		lpDIJoystick->Unacquire();
		lpDIJoystick->Release();
		lpDIJoystick = NULL;
	}

	if (lpDInput != NULL)
	{
		lpDInput->Release();
		lpDInput = NULL;
	}

    // Close Mouse event handle
    if ( NULL != g_hMouseEvent )
    {
        CloseHandle		( g_hMouseEvent );
        g_hMouseEvent	= NULL;
    }

	return(0);
}

static void Exc_ReleaseInput()
{
	if(zinput) delete zinput; zinput = 0; 
}

void zCInput_Win32::SetFocusWindow	(HWND focusWnd)
{
	focusWinHandle = focusWnd;
};

////////////////////////////////////////////////////////////////////////////////
//
//	zCInput_Win32::zCInput_Win32
//
//	2002-05-11	[BENDLIN]
//
//				Added option for key delay-rate in Gothic.ini
//				( [GAME] "keyDelayRate" in ms, default 110 )
//
////////////////////////////////////////////////////////////////////////////////

zCInput_Win32::zCInput_Win32(zTSystemContextHandle* initContextHandle)
{
	// Initializing DirectInput with Mainwindow-Handle
	InitDInput(hWndApp,hInstApp);
	
	if (!helpMap) helpMap = zNEW( zSKeyMapping );
	
	// Key Repeat [Ulf]
	m_iLastKey				= 0;
	m_fKeyRepeatTimeMod		= 0,
	m_bMouseIdle			= TRUE;

	// Better : ask Windows about delay-Rate and use this.... if possible...
	// [BENDLIN] read it from Gothic.ini
	zREAL delayRate = zoptions->ReadReal("GAME", "keyDelayRate", 0); 
	if ( delayRate <= 0 ) 
	{
		delayRate = 150;
		zoptions->WriteReal("GAME", "keyDelayRate", delayRate, FALSE);
	}
	zREAL delayFirst = zoptions->ReadReal("GAME", "keyDelayFirst", -1); 
	if ( delayFirst < 0 ) 
	{
		delayFirst = 0;
		zoptions->WriteReal("GAME", "keyDelayFirst", delayFirst, FALSE);
	}
	SetAutoRepeatDelayRate(delayRate, delayFirst);
};

zCInput_Win32::~zCInput_Win32()
{
#if	0
	BlockInput(FALSE);					// wenn Einkommentiert macht Starten unter Win95 unmöglich									// darum: raus damit.
#endif
	ReleaseDInput();
	/* [SPECKELS] Besser ein Leak, als ein Crash :(
	delete helpMap;	
	*/
	helpMap = 0;
};

////////////////////////////////////////////////////////////////////////////////
//
//	zCInput_Win32::GetState
//
//	2002-05-11	[BENDLIN] small bugfix
//
////////////////////////////////////////////////////////////////////////////////

zREAL zCInput_Win32::GetState(const zWORD logicalID)
{
	if(!lpDIKeyboard)return 0;
	helpMap->logicalID = logicalID;
	int index = mapList.Search(helpMap);
	if ( index != -1 ) 
	{
		// Wurde die Logische Taste auf TRUE gesetzt?
		if (mapList[index]->set) return 1;

		// Ansonsten mal schauen, ob die verknüpften Tasten gedrückt sind ...
		for (int i=0; i<mapList[index]->controlValues.GetNumInList(); i++) 
		{
			zWORD cv = mapList[index]->controlValues[i];
			// if (cv<1024) if (KeyPressed(cv)) return 1; 			
			if ( (cv < KEY_EVENT_TABLE_SIZE) )
			if ( KeyPressed(cv) ) return 1;
		}
	}
	return 0;
};


zBOOL zCInput_Win32::SetState(const zWORD logicalID, zBOOL state)
{
	if(!lpDIKeyboard || (focusWinHandle != GetFocus()))return 0;
	helpMap->logicalID = logicalID;
	int index = mapList.Search(helpMap);
	if (index != -1) 
	{
		mapList[index]->set = state;
		return TRUE;
	}

	// not found in mapList yet, create manual mapping this frame
	zSKeyMapping *map = zNEW( zSKeyMapping );
	map->logicalID		= logicalID;
	map->set			= state;
	mapList.InsertSort(map);
	return TRUE;
};

////////////////////////////////////////////////////////////////////////////////
//
//	zCInput_Win32::GetToggled
//
//	2002-05-11	[BENDLIN]
//
//				small bugfix, Hack removed
//
////////////////////////////////////////////////////////////////////////////////

zBOOL zCInput_Win32::GetToggled(const zWORD logicalID)
{
	if(!lpDIKeyboard)return 0;
	helpMap->logicalID = logicalID;
	int index = mapList.Search(helpMap);
	if ( index != -1 ) 
	{
		if (mapList[index]->set) return TRUE;
		for (int i=0; i<mapList[index]->controlValues.GetNumInList(); i++) 
		{
			zWORD cv = mapList[index]->controlValues[i];
			// if (cv<1024) 
			if ( (cv < KEY_EVENT_TABLE_SIZE) )
			if ( KeyPressed(cv) )
			if ( KeyToggled(cv) ) return TRUE;
		}
	}
	return FALSE;
};

void zCInput_Win32::SetDeviceEnabled(const zTInputDevice device, const zBOOL en)
{
	// FIXME: nur enablen, wenn connected?
	switch(device) 
	{
		case zINPUT_KEYBOARD:	keyboardEnabled	= en;	break;
		case zINPUT_MOUSE:		mouseEnabled	= en;	break;
		case zINPUT_JOYSTICK1:	joystickEnabled	= en;	break; 
	}
	for (int i=0; i<mapList.GetNumInList(); i++) 
	{
		mapList[i]->set = FALSE;		
	}
};

zBOOL zCInput_Win32::GetDeviceEnabled(const zTInputDevice device)
{
	switch(device) 
	{
		case zINPUT_KEYBOARD:	return keyboardEnabled;
		case zINPUT_MOUSE:		return mouseEnabled;
		case zINPUT_JOYSTICK1:	return joystickEnabled;
	}
	return FALSE;
};

zBOOL zCInput_Win32::GetDeviceConnected(const zTInputDevice device)
{
	switch(device) 
	{
		case zINPUT_KEYBOARD:	return TRUE;
		case zINPUT_MOUSE:		return mouseAvailable;
		case zINPUT_JOYSTICK1:	return joystickAvailable;
	}
	return FALSE;
};

zBOOL zCInput_Win32::KeyPressed(const int keyID)
{
	return keyevent[keyID];
};

zBOOL zCInput_Win32::KeyToggled(const int keyID)
{
	zBOOL res		= keytoggle[keyID];
	keytoggle[keyID]= false;
	return res;
};

////////////////////////////////////////////////////////////////////////////////
//
//	zCInput_Win32::AnyKeyPressed
//
//	2002-05-11	[BENDLIN]
//
//				extended for mouse buttons und codes
//
////////////////////////////////////////////////////////////////////////////////

zBOOL zCInput_Win32::AnyKeyPressed()
{
	zWORD i, *pKMask=(zWORD *)keyevent;
	
	for (i=0; i<MAX_KEYS; i+=64, pKMask+=16)
	{
		zWORD p1, p2;
		p1=pKMask[0] | pKMask[2] | pKMask[4] | pKMask[6] | pKMask[8] | pKMask[10] | pKMask[12] | pKMask[14];
		p2=pKMask[1] | pKMask[3] | pKMask[5] | pKMask[7] | pKMask[9] | pKMask[11] | pKMask[13] | pKMask[15];
		if (p1 | p2) return TRUE;
	}
	for ( i = MIN_MOUSE_BTNS_AND_CODES; i < MAX_MOUSE_BTNS_AND_CODES; i += 64, pKMask += 16)
	{
		zWORD p3, p4;
		p3 = pKMask[0] | pKMask[2] | pKMask[4] | pKMask[6] | pKMask[8] | pKMask[10] | pKMask[12] | pKMask[14];
		p4 = pKMask[1] | pKMask[3] | pKMask[5] | pKMask[7] | pKMask[9] | pKMask[11] | pKMask[13] | pKMask[15];
		if ( p3 | p4 ) return TRUE;
	}
	for ( i = MIN_JOY_BTNS_AND_CODES; i < MAX_JOY_BTNS_AND_CODES; i += 64, pKMask += 16)
	{
		zWORD p3, p4;
		p3 = pKMask[0] | pKMask[2] | pKMask[4] | pKMask[6] | pKMask[8] | pKMask[10] | pKMask[12] | pKMask[14];
		p4 = pKMask[1] | pKMask[3] | pKMask[5] | pKMask[7] | pKMask[9] | pKMask[11] | pKMask[13] | pKMask[15];
		if ( p3 | p4 ) return TRUE;
	}
	
	return FALSE;
};

void zCInput_Win32::SetAutoRepeatDelayRate(zREAL delayms, zREAL firstms)
// [Ulf]
// >= 0 : Use this time (ms) for key auto repeat
// <  0 : disable key auto repeat
{
	m_fKeyRepeatTime		= delayms;
	m_fKeyRepeatDelay		= delayms + firstms;	// zusaetzliche Wartezeit
	m_fKeyRepeatCounter		= m_fKeyRepeatTime;
	m_fKeyRepeatCounterDelay= m_fKeyRepeatDelay;	// Beim ersten mal dauerts etwas laenger.
}

zREAL zCInput_Win32::GetAutoRepeatDelayRate()
// [Ulf]
{
	return m_fKeyRepeatTime;
};


static zBOOL s_clearKeyEventsOnNextRepeat = FALSE;

void zCInput_Win32::ResetRepeatKey(zBOOL resetLastKey)
{
	if (resetLastKey)
	{
		m_iLastKey = 0;
	}
	else
	{
		s_clearKeyEventsOnNextRepeat = TRUE;
	};
	m_fKeyRepeatTimeMod			= 0;
	m_fKeyRepeatCounter			= 0;	
	m_fKeyRepeatCounterDelay	= m_fKeyRepeatDelay; 
};

zWORD zCInput_Win32::GetKey(zBOOL repeat, zBOOL delayed)
{
	if( !lpDIKeyboard )					return 0;
	if( focusWinHandle != GetFocus() )	return 0;

	int	keyNr	= 0;

	keyNr = (keybuffer.GetNumInList()>0) ? keybuffer.GetSafe(0) : 0;
	if (keyNr!=0) keybuffer.RemoveOrderIndex(0);
	
	if(keyNr>0)
	//
	// Neuer Tastendruck
	//	
	{				
		// [BENDLIN] testing: avoid locking!
		m_kbdTimer.ResetTimer();
		
		#ifdef DEBUG_REPORT_KEYS
		zERR_MESSAGE(4,0,"B: KBD: Key pressed ["+zSTRING(keyNr)+"]");
		#endif

		m_iLastKey				= keyNr;
		m_fKeyRepeatCounter		= 0;
		m_fKeyRepeatTimeMod		= 0;
		s_clearKeyEventsOnNextRepeat = FALSE;
		if (delayed) m_fKeyRepeatCounterDelay = m_fKeyRepeatDelay; 
	}	
	else
	//
	// Kein neuer Tastendruck: Auto-Repeat mit evtl. Delay
	//
	{		
		if (repeat && (m_fKeyRepeatTime>=0.0f))
		{		
			if (	
					m_iLastKey!=0			&&	// Vorheriger Tastendruck
					KeyPressed(m_iLastKey)	&&	// ... ist weiter aktiv
					keyRepeatEnabled[m_iLastKey]
				)
			{						
				m_fKeyRepeatCounter += m_kbdTimer.GetFrameTimeF();			
				if ( m_fKeyRepeatCounter > (m_fKeyRepeatTime+m_fKeyRepeatCounterDelay) ) 
				{
					if (!s_clearKeyEventsOnNextRepeat)					
					{
						// [BENDLIN] testing: no increment
						// if (m_fKeyRepeatTimeMod<m_fKeyRepeatTime) m_fKeyRepeatTimeMod++;
						m_fKeyRepeatCounter			= m_fKeyRepeatTimeMod;
						m_fKeyRepeatCounterDelay	= 0;
						keyNr						= m_iLastKey;
						#ifdef DEBUG_REPORT_KEYS
						zERR_MESSAGE(4,0,"B: KBD: Repeat last key ["+zSTRING(m_iLastKey)+"]");
						#endif
					}
					else
					{				
						keyevent[m_iLastKey] = true;
						keytoggle[m_iLastKey]= true;
						m_fKeyRepeatCounterDelay = 0;
						s_clearKeyEventsOnNextRepeat = FALSE;
						return 0;
					}
				}
				m_kbdTimer.ResetTimer();
			} 			
		}		
	}	
	return keyNr;
};

/* old Implementation (Dennis)
zWORD zCInput_Win32::GetKey()
{
	if(!lpDIKeyboard)return 0;
	if( focusWinHandle != GetFocus() )return 0;
	lpDIKeyboard->Poll();
	DIDEVICEOBJECTDATA key_pressed;
	memset(&key_pressed,0,sizeof(DIDEVICEOBJECTDATA));
	DWORD dwItems = 1;
	HRESULT res = lpDIKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &key_pressed, &dwItems, DIGDD_PEEK );
	if( res == DI_OK &&	dwItems > 0 && ((key_pressed.dwData & 0x80) ? 1 : 0) ) return key_pressed.dwOfs;
	return 0;
};
*/

void zCInput_Win32::SetKey(const int keyID,const zBOOL down)
{		
	HWND focusWnd = GetFocus();	
	if( focusWinHandle != focusWnd )return;
	zBOOL lastEvent		= keyevent[keyID];
	keyevent[keyID]		= (down ? true : false);
	keytoggle[keyID]	= (lastEvent != down);
};

unsigned char zCInput_Win32::GetChar()
{
	if(!lpDIKeyboard)return 0;
	DIDEVICEOBJECTDATA key_pressed[3];
	memset(&key_pressed,0,sizeof(DIDEVICEOBJECTDATA));
	DWORD dwItems = 3;
	lpDIKeyboard->Acquire();
	lpDIKeyboard->Poll();
	lpDIKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), key_pressed, &dwItems, DIGDD_PEEK );
	switch (dwItems)
	{
	case 1:		return GetCharFromDIK(key_pressed[0].dwOfs, 0, 0);
	case 2:		return GetCharFromDIK(key_pressed[0].dwOfs, key_pressed[1].dwOfs, 0);
	case 3:		return GetCharFromDIK(key_pressed[0].dwOfs, key_pressed[1].dwOfs, key_pressed[2].dwOfs);
	default:	return 0;
	}
};

////////////////////////////////////////////////////////////////////////////////
//
//	zCInput_Win32::ClearKeyBuffer
//
//	2002-05-11	[BENDLIN]
//
//				Clear the internal mouse buffer too
//				and reset mouse movent/buttons
//
////////////////////////////////////////////////////////////////////////////////

void zCInput_Win32::ClearKeyBuffer() // @HOME
{
	// Internen DInput-Buffer loeschen
	if(lpDIKeyboard)
	{	
		DIDEVICEOBJECTDATA key_pressed[KEYBOARD_BUFFER_SIZE];
		memset(&key_pressed,0,sizeof(DIDEVICEOBJECTDATA));
		DWORD dwItems = KEYBOARD_BUFFER_SIZE;
		lpDIKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), key_pressed, &dwItems, NULL);
	}
	// [BENDLIN] clear internal DInput buffer (mouse)
	if (lpDIMouse)
	{	
		DIDEVICEOBJECTDATA btn_pressed[MOUSE_BUFFER_SIZE];
		memset(&btn_pressed, 0, sizeof(DIDEVICEOBJECTDATA));
		DWORD dwCount = MOUSE_BUFFER_SIZE;
		lpDIMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), btn_pressed, &dwCount, NULL);
	}
	// [BENDLIN] clear internal DInput buffer (joystick)
	if (lpDIJoystick)
	{	
		DIDEVICEOBJECTDATA joy_pressed[JOYSTICK_BUFFER_SIZE];
		memset(&joy_pressed, 0, sizeof(DIDEVICEOBJECTDATA));
		DWORD dwCount = JOYSTICK_BUFFER_SIZE;
		lpDIJoystick->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), joy_pressed, &dwCount, NULL);
	}

	// Externen KeyBuffer löschen	
	keybuffer.DeleteList();
	
	// Arrays loeschen
	for (int i=0; i<KEY_EVENT_TABLE_SIZE; i++)
	{
		keyevent[i] = false;
		keytoggle[i]= false;
	};

	// mapList loeschen
	for (i=0; i<mapList.GetNumInList(); i++) 
	{
		mapList[i]->set = FALSE;		
	}

	// some mouse-states
	mouseState.xpos	= 0;
	mouseState.ypos = 0;
	mouseState.zpos = 0;
	mouseState.buttonPressedLeft	= FALSE;		
	mouseState.buttonPressedRight	= FALSE;
	mouseState.buttonPressedMid		= FALSE;
	
};
#include "zoption.h"

////////////////////////////////////////////////////////////////////////////////
//
//	zCInput_Win32::ClearKeyBuffer
//
//	2002-05-11	[BENDLIN]
//
//				controversial handling removed
//
////////////////////////////////////////////////////////////////////////////////

void zCInput_Win32::ProcessInputEvents()
{
	// Listen leeren

/*
	if (!zoptions->Parm("OLDMOUSE")) 
	{
		s_actionPressedBefore = zinput->GetState(GAME_ACTION);
		s_upPressedBefore	  = zinput->GetState(GAME_UP);
		s_downPressedBefore	  = zinput->GetState(GAME_DOWN);
	}
	else
	{
		s_actionPressedBefore = TRUE;
		s_upPressedBefore     = TRUE;
		s_downPressedBefore	  = TRUE;
	}
*/
	for (int i=0; i<mapList.GetNumInList(); i++) 
	{
		mapList[i]->set = FALSE;
	}	

	UpdateDInput();			

};

void zCInput_Win32::GetMousePos (zREAL &x, zREAL &y, zREAL &zWheel)
{
	x		= zREAL(mouseState.xpos) * mouseSensitivityX;
	y		= zREAL(mouseState.ypos) * mouseSensitivityY;
	zWheel	= zREAL(mouseState.zpos);
	if (mouseFlipX)	x = -x;
	if (mouseFlipY)	y = -y;
};

zBOOL zCInput_Win32::GetMouseButtonPressedLeft	()
{
	return mouseState.buttonPressedLeft;
};

zBOOL zCInput_Win32::GetMouseButtonPressedMid	()
{
	return mouseState.buttonPressedMid;
};

zBOOL zCInput_Win32::GetMouseButtonPressedRight	()
{
	return mouseState.buttonPressedRight;
};

void zCInput_Win32::SetMouseSensitivity (const zREAL sensX, const zREAL sensY)
{
	mouseSensitivityX	= sensX;
	mouseSensitivityY	= sensY;
	if (mouseSensitivityX<=0)	mouseSensitivityX = zREAL(0.0001F);
	if (mouseSensitivityY<=0)	mouseSensitivityY = zREAL(0.0001F);
};

void zCInput_Win32::GetMouseSensitivity (zREAL& sensX, zREAL& sensY)
{
	sensX = mouseSensitivityX;
	sensY = mouseSensitivityY;
};

void zCInput_Win32::SetMouseFlipXY (const zBOOL flipX, const zBOOL flipY)
{
	mouseFlipX	= flipX;
	mouseFlipY	= flipY;
};

void zCInput_Win32::GetMouseFlipXY (zBOOL& flipX, zBOOL &flipY)
{
	flipX = mouseFlipX;
	flipY = mouseFlipY;
};

/*
	- ButtonLeft => LCTRL, ButtonRight => LALT
	- Flip X/Y
	- Sensitivity
*/

// disable VC++ Warning: double to float conversion
#pragma warning( default : 4244 )
