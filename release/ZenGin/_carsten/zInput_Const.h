/******************************************************************************** 
 
	$Workfile:: zInput_Const.h		$             $Date:: 18.03.01 18:47	$
	$Revision:: 1					$             $Modtime:: 17.03.01 23:13 $
	$Author:: Edenfeld				$
	Subproject:: ZenGin
	Copyright:: 1998-2002, Piranha Bytes GmbH
 
	Description: Constants for general zCInput class (Win32/DirectX).
	created: 1998

 * $Log: /current_work/ZenGin/_Carsten/zInput_Const.h $
 *********************************************************************************/

#ifndef __ZINPUT_CONST__
#define __ZINPUT_CONST__

////////////////////////////////////////////////////////////////////////////////
//
//	GAME SPECIFIC !
//
////////////////////////////////////////////////////////////////////////////////

#define GAME_LEFT			1
#define GAME_RIGHT			2
#define GAME_UP				3
#define GAME_DOWN			4
#define GAME_ACTION			5
#define GAME_SLOW			6
#define GAME_ACTION2		7
#define GAME_WEAPON			8
#define GAME_SMOVE			11
#define GAME_SMOVE2			12
#define GAME_SHIFT			13
#define GAME_END			14
#define	GAME_INVENTORY		15
#define GAME_LOOK			16
#define GAME_SNEAK			17
#define GAME_STRAFELEFT		18
#define GAME_STRAFERIGHT	19
#define GAME_SCREEN_STATUS	20
#define GAME_SCREEN_LOG		21
#define GAME_SCREEN_MAP		22
#define GAME_LOOK_FP		23
#define GAME_LOCK_TARGET	24
#define GAME_PARADE			25
#define GAME_ACTIONLEFT		26
#define GAME_ACTIONRIGHT	27
#define GAME_LAME_POTION	28
#define GAME_LAME_HEAL		29

////////////////////////////////////////////////////////////////////////////////
//
//	DirectInput key-codes
//
////////////////////////////////////////////////////////////////////////////////

#define DIK_ESCAPE          0x01
#define DIK_1               0x02
#define DIK_2               0x03
#define DIK_3               0x04
#define DIK_4               0x05
#define DIK_5               0x06
#define DIK_6               0x07
#define DIK_7               0x08
#define DIK_8               0x09
#define DIK_9               0x0A
#define DIK_0               0x0B
#define DIK_MINUS           0x0C    /* - on main keyboard */
#define DIK_EQUALS          0x0D
#define DIK_BACK            0x0E    /* backspace */
#define DIK_TAB             0x0F
#define DIK_Q               0x10
#define DIK_W               0x11
#define DIK_E               0x12
#define DIK_R               0x13
#define DIK_T               0x14
#define DIK_Y               0x15
#define DIK_U               0x16
#define DIK_I               0x17
#define DIK_O               0x18
#define DIK_P               0x19
#define DIK_LBRACKET        0x1A
#define DIK_RBRACKET        0x1B
#define DIK_RETURN          0x1C    /* Enter on main keyboard */
#define DIK_LCONTROL        0x1D
#define DIK_A               0x1E
#define DIK_S               0x1F
#define DIK_D               0x20
#define DIK_F               0x21
#define DIK_G               0x22
#define DIK_H               0x23
#define DIK_J               0x24
#define DIK_K               0x25
#define DIK_L               0x26
#define DIK_SEMICOLON       0x27
#define DIK_APOSTROPHE      0x28
#define DIK_GRAVE           0x29    /* accent grave */
#define DIK_LSHIFT          0x2A
#define DIK_BACKSLASH       0x2B
#define DIK_Z               0x2C
#define DIK_X               0x2D
#define DIK_C               0x2E
#define DIK_V               0x2F
#define DIK_B               0x30
#define DIK_N               0x31
#define DIK_M               0x32
#define DIK_COMMA           0x33
#define DIK_PERIOD          0x34    /* . on main keyboard */
#define DIK_SLASH           0x35    /* / on main keyboard */
#define DIK_RSHIFT          0x36
#define DIK_MULTIPLY        0x37    /* * on numeric keypad */
#define DIK_LMENU           0x38    /* left Alt */
#define DIK_SPACE           0x39
#define DIK_CAPITAL         0x3A
#define DIK_F1              0x3B
#define DIK_F2              0x3C
#define DIK_F3              0x3D
#define DIK_F4              0x3E
#define DIK_F5              0x3F
#define DIK_F6              0x40
#define DIK_F7              0x41
#define DIK_F8              0x42
#define DIK_F9              0x43
#define DIK_F10             0x44
#define DIK_NUMLOCK         0x45
#define DIK_SCROLL          0x46    /* Scroll Lock */
#define DIK_NUMPAD7         0x47
#define DIK_NUMPAD8         0x48
#define DIK_NUMPAD9         0x49
#define DIK_SUBTRACT        0x4A    /* - on numeric keypad */
#define DIK_NUMPAD4         0x4B
#define DIK_NUMPAD5         0x4C
#define DIK_NUMPAD6         0x4D
#define DIK_ADD             0x4E    /* + on numeric keypad */
#define DIK_NUMPAD1         0x4F
#define DIK_NUMPAD2         0x50
#define DIK_NUMPAD3         0x51
#define DIK_NUMPAD0         0x52
#define DIK_DECIMAL         0x53    /* . on numeric keypad */
#define DIK_OEM_102         0x56    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
#define DIK_F11             0x57
#define DIK_F12             0x58
#define DIK_F13             0x64    /*                     (NEC PC98) */
#define DIK_F14             0x65    /*                     (NEC PC98) */
#define DIK_F15             0x66    /*                     (NEC PC98) */
#define DIK_KANA            0x70    /* (Japanese keyboard)            */
#define DIK_ABNT_C1         0x73    /* /? on Brazilian keyboard */
#define DIK_CONVERT         0x79    /* (Japanese keyboard)            */
#define DIK_NOCONVERT       0x7B    /* (Japanese keyboard)            */
#define DIK_YEN             0x7D    /* (Japanese keyboard)            */
#define DIK_ABNT_C2         0x7E    /* Numpad . on Brazilian keyboard */
#define DIK_NUMPADEQUALS    0x8D    /* = on numeric keypad (NEC PC98) */
#define DIK_PREVTRACK       0x90    /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
#define DIK_AT              0x91    /*                     (NEC PC98) */
#define DIK_COLON           0x92    /*                     (NEC PC98) */
#define DIK_UNDERLINE       0x93    /*                     (NEC PC98) */
#define DIK_KANJI           0x94    /* (Japanese keyboard)            */
#define DIK_STOP            0x95    /*                     (NEC PC98) */
#define DIK_AX              0x96    /*                     (Japan AX) */
#define DIK_UNLABELED       0x97    /*                        (J3100) */
#define DIK_NEXTTRACK       0x99    /* Next Track */
#define DIK_NUMPADENTER     0x9C    /* Enter on numeric keypad */
#define DIK_RCONTROL        0x9D
#define DIK_MUTE            0xA0    /* Mute */
#define DIK_CALCULATOR      0xA1    /* Calculator */
#define DIK_PLAYPAUSE       0xA2    /* Play / Pause */
#define DIK_MEDIASTOP       0xA4    /* Media Stop */
#define DIK_VOLUMEDOWN      0xAE    /* Volume - */
#define DIK_VOLUMEUP        0xB0    /* Volume + */
#define DIK_WEBHOME         0xB2    /* Web home */
#define DIK_NUMPADCOMMA     0xB3    /* , on numeric keypad (NEC PC98) */
#define DIK_DIVIDE          0xB5    /* / on numeric keypad */
#define DIK_SYSRQ           0xB7
#define DIK_RMENU           0xB8    /* right Alt */
#define DIK_PAUSE           0xC5    /* Pause */
#define DIK_HOME            0xC7    /* Home on arrow keypad */
#define DIK_UP              0xC8    /* UpArrow on arrow keypad */
#define DIK_PRIOR           0xC9    /* PgUp on arrow keypad */
#define DIK_LEFT            0xCB    /* LeftArrow on arrow keypad */
#define DIK_RIGHT           0xCD    /* RightArrow on arrow keypad */
#define DIK_END             0xCF    /* End on arrow keypad */
#define DIK_DOWN            0xD0    /* DownArrow on arrow keypad */
#define DIK_NEXT            0xD1    /* PgDn on arrow keypad */
#define DIK_INSERT          0xD2    /* Insert on arrow keypad */
#define DIK_DELETE          0xD3    /* Delete on arrow keypad */
#define DIK_LWIN            0xDB    /* Left Windows key */
#define DIK_RWIN            0xDC    /* Right Windows key */
#define DIK_APPS            0xDD    /* AppMenu key */
#define DIK_POWER           0xDE    /* System Power */
#define DIK_SLEEP           0xDF    /* System Sleep */
#define DIK_WAKE            0xE3    /* System Wake */
#define DIK_WEBSEARCH       0xE5    /* Web Search */
#define DIK_WEBFAVORITES    0xE6    /* Web Favorites */
#define DIK_WEBREFRESH      0xE7    /* Web Refresh */
#define DIK_WEBSTOP         0xE8    /* Web Stop */
#define DIK_WEBFORWARD      0xE9    /* Web Forward */
#define DIK_WEBBACK         0xEA    /* Web Back */
#define DIK_MYCOMPUTER      0xEB    /* My Computer */
#define DIK_MAIL            0xEC    /* Mail */
#define DIK_MEDIASELECT     0xED    /* Media Select */
// Alternate names for keys, to facilitate transition from DOS.
#define DIK_BACKSPACE       DIK_BACK            /* backspace */
#define DIK_NUMPADSTAR      DIK_MULTIPLY        /* * on numeric keypad */
#define DIK_LALT            DIK_LMENU           /* left Alt */
#define DIK_CAPSLOCK        DIK_CAPITAL         /* CapsLock */
#define DIK_NUMPADMINUS     DIK_SUBTRACT        /* - on numeric keypad */
#define DIK_NUMPADPLUS      DIK_ADD             /* + on numeric keypad */
#define DIK_NUMPADPERIOD    DIK_DECIMAL         /* . on numeric keypad */
#define DIK_NUMPADSLASH     DIK_DIVIDE          /* / on numeric keypad */
#define DIK_RALT            DIK_RMENU           /* right Alt */
#define DIK_UPARROW         DIK_UP              /* UpArrow on arrow keypad */
#define DIK_PGUP            DIK_PRIOR           /* PgUp on arrow keypad */
#define DIK_LEFTARROW       DIK_LEFT            /* LeftArrow on arrow keypad */
#define DIK_RIGHTARROW      DIK_RIGHT           /* RightArrow on arrow keypad */
#define DIK_DOWNARROW       DIK_DOWN            /* DownArrow on arrow keypad */
#define DIK_PGDN            DIK_NEXT            /* PgDn on arrow keypad */
// Alternate names for keys originally not used on US keyboards.
#define DIK_CIRCUMFLEX      DIK_PREVTRACK       /* Japanese keyboard */

////////////////////////////////////////////////////////////////////////////////
//
//	No key codes, but status codes
//
////////////////////////////////////////////////////////////////////////////////

#define KEY_CAPS_TOGGLE				512
#define KEY_NUM_TOGGLE				513
#define	KEY_SCROLL_TOGGLE			514

////////////////////////////////////////////////////////////////////////////////
//
//	Keyboard values
//
////////////////////////////////////////////////////////////////////////////////

#define MAX_KEYS					512
#define MAX_KEYS_AND_CODES			515
#define KEY_NOT_HERE				(MAX_KEYS_AND_CODES+1)
#define KEY_RELEASE					0x8000							// Release flag

// DOS32 Keyboard values
#define DOSKEY_PAD_MUL				106								// "*"		on Num-Keypad
#define DOSKEY_PAD_DIV				111								// "/"		on Num-Keypad
#define DOSKEY_ESC					27								// Escape
#define DOSKEY_PLUS					187 							// '+'
#define DOSKEY_MINUS 				189 							// '-'
#define DOSKEY_SPACE 				32								// ' ' (Blank space)
#define DOSKEY_OQUOTE				192 							// '`' (Open single quote)
#define DOSKEY_CQUOTE				222 							// ''' (Close single quote)
#define DOSKEY_LHOOK 				219 							// '[' (Left "hook")
#define DOSKEY_RHOOK 				221 							// ']' (Right "hook")
#define DOSKEY_BSLASH				220 							// '\' (Backslash)
#define DOSKEY_FSLASH				191 							// '/' (Forward Slash)
#define DOSKEY_SEMICOLON 			186 							// ';' (Semi-colon)
#define DOSKEY_COMMA 				188 							// ',' (Comma)
#define DOSKEY_DOT					190 							// '.' (Dot/Point)
#define DOSKEY_ENTER 				13								// Enter
#define DOSKEY_BACKSPACE 			8								// BackSpace
#define DOSKEY_TAB					9							   // Tab
#define DOSKEY_GREYPLUS				107 							// '+'		on Num-Keypad
#define DOSKEY_GREYMINUS 			109 							// '-'		on Num-Keypad
#define DOSKEY_PAD_ENTER 			13  							// Enter	on Num-Keypad
#define DOSKEY_PAD_LEFT				100								// Left 	on Num-Keypad
#define DOSKEY_PAD_RIGHT 			102								// Right	on Num-Keypad
#define DOSKEY_PAD_UP				104								// Up		on Num-Keypad
#define DOSKEY_PAD_DOWN				98								// Down 	on Num-Keypad
#define DOSKEY_PAD_HOME				103								// Home 	on Num-Keypad
#define DOSKEY_PAD_END				97								// End		on Num-Keypad
#define DOSKEY_PAD_PGDN				99								// PageUp	on Num-Keypad
#define DOSKEY_PAD_PGUP				105								// PageDown on Num-Keypad
#define DOSKEY_PAD_INS				96								// Ins		on Num-Keypad
#define DOSKEY_PAD_DEL				110								// Del		on Num-Keypad
#define DOSKEY_PAD_CENTER			101								// Center 	on Num-Keypad
#define DOSKEY_PAD_5				101								// "5"		on Num-Keypad ???76???
#define DOSKEY_LEFT					37 							// Left  arrow
#define DOSKEY_RIGHT 				39 							// Right arrow
#define DOSKEY_UP					38 							// Up	 arrow
#define DOSKEY_DOWN					40 							// Down  arrow
#define DOSKEY_HOME					36 							// Home
#define DOSKEY_END					35 							// End
#define DOSKEY_PGUP					33 							// PageUp
#define DOSKEY_PGDN					34 							// PageDown
#define DOSKEY_INS					45 							// Insert
#define DOSKEY_DEL					46 							// Delete
#define DOSKEY_CAPSLOCK				20								// Caps Lock
#define DOSKEY_PAUSE 				19								// *TOGGLE* Pause/Break
#define DOSKEY_LALT					18								// Left Alt
#define DOSKEY_RALT					274 							// Right Alt
#define DOSKEY_LCTRL 				17								// Left Control
#define DOSKEY_RCTRL 				273 							// Right Control
#define DOSKEY_LSHIFT				16								// Left Shift
// Das Betriebssystem scheint eh nicht zwischen
// Left und Right Shift zu unterscheiden (doch, aber nur unter WinNT - nico)
#define DOSKEY_RSHIFT				16								// Right Shift
#define DOSKEY_WIN_LWINKEY			347 							// Windows: Left windows logo
#define DOSKEY_WIN_RWINKEY			348 							// Windows: Right windows logo
#define DOSKEY_WIN_CONTEXT			349 							// Windows: Context menu

#define DOSKEY_F1					112
#define DOSKEY_F2					113
#define DOSKEY_F3					114
#define DOSKEY_F4					115
#define DOSKEY_F5					116
#define DOSKEY_F6					117
#define DOSKEY_F7					118
#define DOSKEY_F8					119
#define DOSKEY_F9					120
#define DOSKEY_F10					121
#define DOSKEY_F11					122
#define DOSKEY_F12					123
#define DOSKEY_1 					49
#define DOSKEY_2 					50
#define DOSKEY_3 					51
#define DOSKEY_4 					52
#define DOSKEY_5 					53
#define DOSKEY_6 					54
#define DOSKEY_7 					55
#define DOSKEY_8 					56
#define DOSKEY_9 					57
#define DOSKEY_0 					48
#define DOSKEY_A 					65
#define DOSKEY_B 					66
#define DOSKEY_C 					67
#define DOSKEY_D 					68
#define DOSKEY_E 					69
#define DOSKEY_F 					70
#define DOSKEY_G 					71
#define DOSKEY_H 					72
#define DOSKEY_I 					73
#define DOSKEY_J 					74
#define DOSKEY_K 					75
#define DOSKEY_L 					76
#define DOSKEY_M 					77
#define DOSKEY_N 					78
#define DOSKEY_O 					79
#define DOSKEY_P 					80
#define DOSKEY_Q 					81
#define DOSKEY_R 					82
#define DOSKEY_S 					83
#define DOSKEY_T 					84
#define DOSKEY_U 					85
#define DOSKEY_V 					86
#define DOSKEY_W 					87
#define DOSKEY_X 					88
#define DOSKEY_Y 					89
#define DOSKEY_Z 					90
#define DOSKEY_SCROLLLOCK			145								// Scroll lock
#define DOSKEY_NUMLOCK				400								// Num lock

// Win32 Keyboard values
#define KEY_ESC						DIK_ESCAPE						// Escape
#define KEY_PLUS					DIK_RBRACKET 							// '+'
#define KEY_MINUS 					DIK_LBRACKET 							// '-'
#define KEY_SPACE 					DIK_SPACE								// ' ' (Blank space)
#define KEY_OQUOTE					DIK_GRAVE 							// '`' (Open single quote)
#define KEY_CQUOTE					222 							// ''' (Close single quote)
#define KEY_LHOOK 					DIK_LBRACKET 							// '[' (Left "hook")
#define KEY_RHOOK 					DIK_RBRACKET 							// ']' (Right "hook")
#define KEY_BSLASH					DIK_BACKSLASH 							// '\' (Backslash)
#define KEY_FSLASH					DIK_SLASH 							// '/' (Forward Slash)
#define KEY_SEMICOLON 				DIK_SEMICOLON 							// ';' (Semi-colon)
#define KEY_APOSTROPHE				DIK_APOSTROPHE						// 'Ä' on german keybaord
#define KEY_COMMA 					DIK_COMMA 							// ',' (Comma)
#define KEY_DOT						DIK_PERIOD 							// '.' (Dot/Point)
#define KEY_ENTER 					DIK_RETURN								// Enter
#define KEY_BACKSPACE 				DIK_BACK							// BackSpace
#define KEY_TAB						DIK_TAB							   // Tab
#define KEY_GREYPLUS				DIK_ADD 							// '+'		on Num-Keypad
#define KEY_GREYMINUS 				DIK_SUBTRACT 							// '-'		on Num-Keypad
#define KEY_PAD_5					DIK_NUMPAD5								// "5"		on Num-Keypad
#define KEY_PAD_MUL					DIK_MULTIPLY								// "*"		on Num-Keypad
#define KEY_PAD_DIV					DIK_DIVIDE								// "/"		on Num-Keypad
#define KEY_PAD_ENTER 				DIK_NUMPADENTER 							// Enter	on Num-Keypad
#define KEY_PAD_LEFT				DIK_NUMPAD4								// Left 	on Num-Keypad
#define KEY_PAD_RIGHT 				DIK_NUMPAD6								// Right	on Num-Keypad
#define KEY_PAD_UP					DIK_NUMPAD8								// Up		on Num-Keypad
#define KEY_PAD_DOWN				DIK_NUMPAD2								// Down 	on Num-Keypad
#define KEY_PAD_HOME				DIK_NUMPAD7								// Home 	on Num-Keypad
#define KEY_PAD_END					DIK_NUMPAD1								// End		on Num-Keypad
#define KEY_PAD_PGDN				DIK_NUMPAD3								// PageUp	on Num-Keypad
#define KEY_PAD_PGUP				DIK_NUMPAD9								// PageDown on Num-Keypad
#define KEY_PAD_INS					DIK_NUMPAD0								// Ins		on Num-Keypad
#define KEY_PAD_DEL					DIK_DECIMAL								// Del		on Num-Keypad
#define KEY_LEFT					DIK_LEFT 							// Left  arrow
#define KEY_RIGHT 					DIK_RIGHT 							// Right arrow
#define KEY_UP						DIK_UP 							// Up	 arrow
#define KEY_DOWN					DIK_DOWN 							// Down  arrow
#define KEY_HOME					DIK_HOME 							// Home
#define KEY_END						DIK_END 							// End
#define KEY_PGUP					DIK_PRIOR 							// PageUp
#define KEY_PGDN					DIK_NEXT 							// PageDown
#define KEY_INS						DIK_INSERT 							// Insert
#define KEY_DEL						DIK_DELETE 							// Delete
#define KEY_CAPSLOCK				DIK_CAPITAL								// Caps lock
#define KEY_PRINT					DIK_SYSRQ								// Sys-Request (Print)
#define KEY_SCROLLLOCK				DIK_SCROLL								// Scroll lock
#define KEY_NUMLOCK					DIK_NUMLOCK								// Num lock
#define KEY_PAUSE 					DIK_PAUSE								// *TOGGLE* Pause/Break
#define KEY_LALT					DIK_LMENU								// Left Alt
#define KEY_RALT					DIK_RMENU 							// Right Alt
#define KEY_LCTRL 					DIK_LCONTROL								// Left Control
#define KEY_RCTRL 					DIK_RCONTROL 							// Right Control
#define KEY_LSHIFT					DIK_LSHIFT								// Left Shift
#define KEY_RSHIFT					DIK_RSHIFT								// Right Shift
#define KEY_WIN_LWINKEY				DIK_LWIN 							// Windows: Left windows logo
#define KEY_WIN_RWINKEY				DIK_RWIN 							// Windows: Right windows logo
#define KEY_WIN_CONTEXT				349 							// Windows: Context menu
#define KEY_DE_SHARPS				DIK_MINUS		// Sharp S on german keyboard
#define KEY_DE_GRAVE				DIK_EQUALS		// Accent Grave on german keyboard
#define KEY_OEM_102					DIK_OEM_102		// Less-Than on german keyboard
									
#define KEY_F1						DIK_F1
#define KEY_F2						DIK_F2
#define KEY_F3						DIK_F3
#define KEY_F4						DIK_F4
#define KEY_F5						DIK_F5
#define KEY_F6						DIK_F6
#define KEY_F7						DIK_F7
#define KEY_F8						DIK_F8
#define KEY_F9						DIK_F9
#define KEY_F10						DIK_F10
#define KEY_F11						DIK_F11
#define KEY_F12						DIK_F12
#define KEY_F13						DIK_F13
#define KEY_F14						DIK_F14
#define KEY_F15						DIK_F15
#define KEY_1 						DIK_1
#define KEY_2 						DIK_2
#define KEY_3 						DIK_3
#define KEY_4 						DIK_4
#define KEY_5 						DIK_5
#define KEY_6 						DIK_6
#define KEY_7 						DIK_7
#define KEY_8 						DIK_8
#define KEY_9 						DIK_9
#define KEY_0 						DIK_0
#define KEY_A 						DIK_A
#define KEY_B 						DIK_B
#define KEY_C 						DIK_C
#define KEY_D 						DIK_D
#define KEY_E 						DIK_E
#define KEY_F 						DIK_F
#define KEY_G 						DIK_G
#define KEY_H 						DIK_H
#define KEY_I 						DIK_I
#define KEY_J 						DIK_J
#define KEY_K 						DIK_K
#define KEY_L 						DIK_L
#define KEY_M 						DIK_M
#define KEY_N 						DIK_N
#define KEY_O 						DIK_O
#define KEY_P 						DIK_P
#define KEY_Q 						DIK_Q
#define KEY_R 						DIK_R
#define KEY_S 						DIK_S
#define KEY_T 						DIK_T
#define KEY_U 						DIK_U
#define KEY_V 						DIK_V
#define KEY_W 						DIK_W
#define KEY_X 						DIK_X
#define KEY_Y 						DIK_Y
#define KEY_Z 						DIK_Z

////////////////////////////////////////////////////////////////////////////////
//
//	Mouse constants
//
////////////////////////////////////////////////////////////////////////////////

#define MIN_MOUSE_BTNS_AND_CODES	(KEY_NOT_HERE)	// old value 2048

#define MOUSE_DX					(MIN_MOUSE_BTNS_AND_CODES +  0)
#define MOUSE_DY					(MIN_MOUSE_BTNS_AND_CODES +  1)
#define MOUSE_UP					(MIN_MOUSE_BTNS_AND_CODES +  2)
#define MOUSE_DOWN					(MIN_MOUSE_BTNS_AND_CODES +  3)
#define MOUSE_LEFT					(MIN_MOUSE_BTNS_AND_CODES +  4)
#define MOUSE_RIGHT					(MIN_MOUSE_BTNS_AND_CODES +  5)
#define MOUSE_WHEELUP				(MIN_MOUSE_BTNS_AND_CODES +  6)
#define MOUSE_WHEELDOWN				(MIN_MOUSE_BTNS_AND_CODES +  7)
#define MOUSE_BUTTONLEFT			(MIN_MOUSE_BTNS_AND_CODES +  8)
#define MOUSE_BUTTONRIGHT			(MIN_MOUSE_BTNS_AND_CODES +  9)
#define MOUSE_BUTTONMID				(MIN_MOUSE_BTNS_AND_CODES + 10)
#define MOUSE_XBUTTON1				(MIN_MOUSE_BTNS_AND_CODES + 11)
#define MOUSE_XBUTTON2				(MIN_MOUSE_BTNS_AND_CODES + 12)
#define MOUSE_XBUTTON3				(MIN_MOUSE_BTNS_AND_CODES + 13)
#define MOUSE_XBUTTON4				(MIN_MOUSE_BTNS_AND_CODES + 14)
#define MOUSE_XBUTTON5				(MIN_MOUSE_BTNS_AND_CODES + 15)

#define MAX_MOUSE_BTNS_AND_CODES	(MOUSE_XBUTTON5 + 1)

#define MIN_MOUSE_BTNS				(MOUSE_WHEELUP)	// Wheel UP/DOWN are interpreted as buttons
#define MAX_MOUSE_BTNS				(MOUSE_XBUTTON5 + 1)

////////////////////////////////////////////////////////////////////////////////
//
//	Joystick defines
//
////////////////////////////////////////////////////////////////////////////////

#define MIN_JOY_BTNS_AND_CODES		(MAX_MOUSE_BTNS_AND_CODES)	// old value 1024

#define JOY_LEFT					(MIN_JOY_BTNS_AND_CODES +  0)
#define	JOY_RIGHT					(MIN_JOY_BTNS_AND_CODES +  1)
#define JOY_UP						(MIN_JOY_BTNS_AND_CODES +  2)
#define JOY_DOWN					(MIN_JOY_BTNS_AND_CODES +  3)
#define THROTTLE_UP					(MIN_JOY_BTNS_AND_CODES +  4)
#define THROTTLE_DOWN				(MIN_JOY_BTNS_AND_CODES +  5)
#define RUDDER_LEFT					(MIN_JOY_BTNS_AND_CODES +  6)
#define RUDDER_RIGHT				(MIN_JOY_BTNS_AND_CODES +  7)
#define JOY_POV_LEFT				(MIN_JOY_BTNS_AND_CODES +  8)
#define JOY_POV_RIGHT				(MIN_JOY_BTNS_AND_CODES +  9)
#define JOY_POV_UP					(MIN_JOY_BTNS_AND_CODES + 10)
#define JOY_POV_DOWN				(MIN_JOY_BTNS_AND_CODES + 11)
#define JOY_BUTTON_1				(MIN_JOY_BTNS_AND_CODES + 12)
#define JOY_BUTTON_2				(MIN_JOY_BTNS_AND_CODES + 13)
#define JOY_BUTTON_3				(MIN_JOY_BTNS_AND_CODES + 14)
#define JOY_BUTTON_4				(MIN_JOY_BTNS_AND_CODES + 15)
#define JOY_BUTTON_5				(MIN_JOY_BTNS_AND_CODES + 16)
#define JOY_BUTTON_6				(MIN_JOY_BTNS_AND_CODES + 17)
#define JOY_BUTTON_7				(MIN_JOY_BTNS_AND_CODES + 18)
#define JOY_BUTTON_8				(MIN_JOY_BTNS_AND_CODES + 19)
#define JOY_BUTTON_9				(MIN_JOY_BTNS_AND_CODES + 20)
#define JOY_BUTTON_10				(MIN_JOY_BTNS_AND_CODES + 21)
#define JOY_BUTTON_11				(MIN_JOY_BTNS_AND_CODES + 22)
#define JOY_BUTTON_12				(MIN_JOY_BTNS_AND_CODES + 23)
#define JOY_BUTTON_13				(MIN_JOY_BTNS_AND_CODES + 24)
#define JOY_BUTTON_14				(MIN_JOY_BTNS_AND_CODES + 25)
#define JOY_BUTTON_15				(MIN_JOY_BTNS_AND_CODES + 26)
#define JOY_BUTTON_16				(MIN_JOY_BTNS_AND_CODES + 27)
#define JOY_BUTTON_17				(MIN_JOY_BTNS_AND_CODES + 28)
#define JOY_BUTTON_18				(MIN_JOY_BTNS_AND_CODES + 29)
#define JOY_BUTTON_19				(MIN_JOY_BTNS_AND_CODES + 30)
#define JOY_BUTTON_20				(MIN_JOY_BTNS_AND_CODES + 31)
#define JOY_BUTTON_21				(MIN_JOY_BTNS_AND_CODES + 32)
#define JOY_BUTTON_22				(MIN_JOY_BTNS_AND_CODES + 33)
#define JOY_BUTTON_23				(MIN_JOY_BTNS_AND_CODES + 34)
#define JOY_BUTTON_24				(MIN_JOY_BTNS_AND_CODES + 35)
#define JOY_BUTTON_25				(MIN_JOY_BTNS_AND_CODES + 36)
#define JOY_BUTTON_26				(MIN_JOY_BTNS_AND_CODES + 37)
#define JOY_BUTTON_27				(MIN_JOY_BTNS_AND_CODES + 38)
#define JOY_BUTTON_28				(MIN_JOY_BTNS_AND_CODES + 39)
#define JOY_BUTTON_29				(MIN_JOY_BTNS_AND_CODES + 40)
#define JOY_BUTTON_30				(MIN_JOY_BTNS_AND_CODES + 41)
#define JOY_BUTTON_31				(MIN_JOY_BTNS_AND_CODES + 42)
#define JOY_BUTTON_32				(MIN_JOY_BTNS_AND_CODES + 43)

#define MAX_JOY_BTNS_AND_CODES		(JOY_BUTTON_32 + 1)

#define MIN_JOY_BTNS				(JOY_LEFT)	// POV is interpreted as buttons
#define MAX_JOY_BTNS				(JOY_BUTTON_32 + 1)

////////////////////////////////////////////////////////////////////////////////
//
//	End of zInput(_Win32) key event table
//
////////////////////////////////////////////////////////////////////////////////

#ifdef DISABLE_JOYSTICK
	#define KEY_EVENT_TABLE_SIZE	(MAX_MOUSE_BTNS_AND_CODES)
#else
	#define KEY_EVENT_TABLE_SIZE	(MAX_JOY_BTNS_AND_CODES)
#endif


#endif
