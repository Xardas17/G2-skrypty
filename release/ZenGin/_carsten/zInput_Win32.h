/******************************************************************************** 
 
     $Workfile:: zInput_Win32.h       $                $Date:: 9.02.01 16:30    $
     $Revision:: 17                   $             $Modtime:: 9.02.01 15:48    $
       $Author:: Speckels                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   Implemention of general zCInput class (Win32/DirectX).
   created: 31.10.99

 * $Log: /current_work/ZenGin/_Carsten/zInput_Win32.h $
 * 
 * 17    9.02.01 16:30 Speckels
 * 2.Paremeter von SetState (vorher zREAL) nach zBOOL geändert
 * 
 * 16    8.02.01 16:25 Speckels
 * 
 * 15    7.02.01 18:02 Speckels
 * 
 * 14    6.02.01 23:25 Speckels
 * 
 * 13    3.02.01 4:11 Hildebrandt
 * 
 * 12    2.02.01 19:29 Hildebrandt
 * 
 * 11    2.02.01 5:23 Hildebrandt
 * 
 * 10    8.12.00 14:25 Speckels
 * 
 * 9     4.12.00 18:23 Moos
 * 
 * 8     1.12.00 16:53 Wohlers
 * 
 * 7     22.11.00 20:41 Wohlers
 * 
 * 6     18.11.00 19:04 Speckels
 * 
 * 5     16.11.00 13:57 Speckels
 * 
 * 4     16/11/00 11:39 Luesebrink
 * 
 * 3     15.11.00 21:00 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revisio: 2 $ ($Modtime: 9.02.01 15:48 $)

// =======================================================================================================================

#ifndef __ZINPUT_WIN32_H__
#define __ZINPUT_WIN32_H__

#ifndef __ZINPUT_H__
#include "zInput.h"
#endif

#ifndef __ZINPUT_CONST_H__
#include "zInput_const.h"
#endif
	
unsigned char GetCharFromDIK(int dik1, int dik2, int dik3);

class zCInput_Win32 : public zCInput 
{
public:
	zCInput_Win32(zTSystemContextHandle* initContextHandle);
	~zCInput_Win32();

#ifdef COMPILING_SPACER
	static DWORD    GetWin32CodeFromDos32Code	(const DWORD m_dwDos32Code);
#endif

	// allgemeine logische Methoden

	zREAL			GetState			(const zWORD logicalID);
	zBOOL			SetState			(const zWORD logicalID, zBOOL state);
										
	zBOOL			GetToggled			(const zWORD logicalID);

	// device related
	void			SetDeviceEnabled	(const zTInputDevice device, const zBOOL en);
	zBOOL			GetDeviceEnabled	(const zTInputDevice device);
	zBOOL			GetDeviceConnected	(const zTInputDevice device);

	// spezielle controller spezifische Methoden
	// keyboard
	zBOOL			KeyPressed			(const int keyID);
	zBOOL			KeyToggled			(const int keyID);
	zBOOL			AnyKeyPressed		();
	virtual	void	ResetRepeatKey		(zBOOL resetLastKey=TRUE);
	virtual	zWORD	GetKey				(zBOOL repeat = TRUE, zBOOL delayed = TRUE);
	virtual	void	SetKey				(const int keyID,const zBOOL down);

	// Key Repeat 
	void	SetAutoRepeatDelayRate		(zREAL delayms, zREAL firstms);
	zREAL	GetAutoRepeatDelayRate		();

	void	SetFocusWindow				(HWND focusWnd);
										
	unsigned char	GetChar				();
	void			ClearKeyBuffer		();
										
	// joystick, easy interface			
	//	void	SetJoyEnabled			(const zBOOL en );
	//	zREAL	JoyState				(const int controlValue);
	//	int		GetNumJoysConnected		();
	//	void	SetJoyDigitalEmu		(const zBOOL emu);

	// mouse

	//AddInputEventCallback()
	//ApplyForceFeedBack(joynum, forcetype, ???);

	// call per frame:
	void	ProcessInputEvents			();

	// Mouse
	void	GetMousePos					(zREAL &x, zREAL &y, zREAL &zWheel);
	zBOOL	GetMouseButtonPressedLeft	();
	zBOOL	GetMouseButtonPressedMid	();
	zBOOL	GetMouseButtonPressedRight	();
	void	SetMouseSensitivity			(const zREAL sensX, const zREAL sensY);
	void	GetMouseSensitivity			(zREAL& sensX, zREAL& sensY);
	void	SetMouseFlipXY				(const zBOOL flipX, const zBOOL flipY);
	void	GetMouseFlipXY				(zBOOL& flipX, zBOOL &flipY);	
	zBOOL	GetMouseIdle				() const							{ return m_bMouseIdle;	};
	void	SetMouseIdle				(const zBOOL a_bIdle)				{ m_bMouseIdle = a_bIdle;};

private :

	zCTimer	m_kbdTimer;
	zREAL	m_fKeyRepeatDelay;			// TimeDelta -> First Time keyPress is simulated
	zREAL	m_fKeyRepeatTime;			// TimeDelta -> keyPress is simulated (after first one is already generated)
	zREAL	m_fKeyRepeatTimeMod;
	zREAL	m_fKeyRepeatCounter;		// Current TimeCounter
	zREAL	m_fKeyRepeatCounterDelay;	
	zBOOL   m_bMouseIdle;
	zWORD	m_iLastKey;

};

extern char* GetTypedText();

#endif