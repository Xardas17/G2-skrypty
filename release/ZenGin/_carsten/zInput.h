/******************************************************************************** 
 
     $Workfile:: zInput.h    $              $Date:: 9.02.01 16:30   $
     $Revision:: 13                  $             $Modtime:: 9.02.01 15:49  $
     $Author:: Speckels               $
	 Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description: abstrakte allgemeine Input Klasse für 
				analoge und digitale Eingabegeräte

 * $Log: /current_work/ZenGin/_Carsten/zInput.h $
 * 
 * 13    9.02.01 16:30 Speckels
 * 2.Paremeter von SetState (vorher zREAL) nach zBOOL geändert
 * 
 * 12    9.02.01 13:38 Speckels
 * 
 * 11    8.02.01 16:25 Speckels
 * 
 * 10    3.02.01 4:11 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 13 $ ($Modtime: 9.02.01 15:49 $)

// =======================================================================================================================

#ifndef __ZINPUT_H__
#define __ZINPUT_H__

#ifndef __ZCONTAINER_H__
#include "zContainer.h"
#endif

#ifndef __ZTYPES_H__
#include "zTypes.h"
#endif

#ifndef __ZINPUT_CONST_H__
#include "zInput_Const.h"
#endif

enum zTInputDevice {
	zINPUT_UNDEF,
	zINPUT_KEYBOARD,
	zINPUT_MOUSE,
	zINPUT_JOYSTICK1,
	zINPUT_JOYSTICK2,
	zINPUT_JOYSTICK3,
	zINPUT_JOYSTICK4
};

struct zSKeyMapping {
public:
	zWORD		   logicalID;
	zCArray<zWORD> controlValues;
	zBOOL		   set;
};

struct zSCtrlValue {
	zSTRING name;
	zWORD   value;
};

class zCInput {

public:


	static	zWORD	GetControlValueByName		(const zSTRING &name);
	static  zSTRING	GetNameByControlValue		(const zWORD controlValue);
	static  int		CompareKeyMaps				(const void *val1, const void *val2);

	zCInput();
	virtual ~zCInput();

	// allgemeine logische Methoden

	void	BindKeys							(int mode);
												
	void	Bind								(const zWORD logicalID, const zCArray <zWORD>&controlValueList);
	void	BindOption							(const zSTRING optionID,const zWORD logicalID, zCArray<zWORD>controlValueList );
	void	Unbind								(const zWORD logicalID);
	zBOOL	IsBinded							(const zWORD logicalID, const zWORD keyID);

	zBOOL	IsBindedToggled						(const zWORD logicalID, const zWORD keyID);

	zBOOL	GetBinding							(const zWORD logicalID, zCArray <zWORD>&controlValueList);

	zWORD	GetFirstBindedLogicalKey			(const zWORD keyID);

	virtual zREAL	GetState					(const zWORD logicalID)							{ return 0;	};
	virtual zBOOL	SetState					(const zWORD logicalID, zBOOL state)			{ return TRUE; };		// sets state for ONE frame
	virtual zBOOL	GetToggled					(const zWORD logicalID)							{ return TRUE; };
																								
	// device related																			
	virtual void	SetDeviceEnabled			(const zTInputDevice device, const zBOOL en)	{};
	virtual zBOOL	GetDeviceEnabled			(const zTInputDevice device)					{ return TRUE; };		// returns FALSE if not possible
	virtual zBOOL	GetDeviceConnected			(const zTInputDevice device)					{ return TRUE; };
																								
	// spezielle controller spezifische Methoden												
	// keyboard																					
	virtual zBOOL	KeyPressed					(const int keyID)								{ return FALSE; };		// checks if key is currently pressed down
	virtual zBOOL	KeyToggled					(const int keyID)								{ return FALSE;	};
	virtual zBOOL	AnyKeyPressed				()												{ return FALSE;	};		// checks if any key has been pressed
	virtual	void	ResetRepeatKey				(zBOOL resetLastKey=TRUE)						{};
	virtual zWORD	GetKey						(zBOOL repeat = TRUE, zBOOL delayed = TRUE)		{ return 0;		};		// returns oldest key in keyboard buffer (FIFO)
	virtual void	SetKey						(const int keyID,const zBOOL down)				{};
	virtual unsigned char GetChar				()												{ return 0;		};		// returns ASCII Code of last pressed character
	virtual void	ClearKeyBuffer				()												{};						// clears keyboard buffer
																								
	// joystick, easy interface																	
	virtual int		GetNumJoysConnected			()												{ return 0;		};
	virtual void	SetJoyDigitalEmu			(const zBOOL emu)								{};
	virtual void	SetJoyEnabled				(const zBOOL en )								{};
																								
	virtual zREAL	JoyState					(const int controlValue)						{ return 0;		};		// returns states of first available stick
																								
	// joystick, advanced interface (force feedback, etc.)										
	virtual zREAL	JoyState					(const int joynum, const int controlValue)		{ return 0;		};
	//ApplyForceFeedBack(joynum, forcetype, ???);												
																								
	// mouse																					
	virtual void	GetMousePos					(zREAL &x, zREAL &y, zREAL &zWheel)				{ };	// relative: positive/negative movement since last frame
	virtual zBOOL	GetMouseButtonPressedLeft	()												{ return FALSE; };
	virtual zBOOL	GetMouseButtonPressedMid	()												{ return FALSE; };
	virtual zBOOL	GetMouseButtonPressedRight	()												{ return FALSE; };
	virtual void	SetMouseSensitivity			(const zREAL sensX, const zREAL sensY)			{ };	// scaler, range: 0.. 1(default) .. oo
	virtual void	GetMouseSensitivity			(zREAL& sensX, zREAL& sensY)					{ };
	virtual zBOOL	GetMouseIdle				() const										{ return FALSE;	};
	virtual void	SetMouseFlipXY				(const zBOOL flipX, const zBOOL flipY)			{ };
	virtual void	GetMouseFlipXY				(zBOOL& flipX, zBOOL &flipY)					{ };

	//AddInputEventCallback()

	// call per frame:
	virtual void	ProcessInputEvents	()=0;

protected:
	zCArraySort<zSKeyMapping*> mapList;

private:
	static zCArray	<zSCtrlValue>   values;

	void			InitializeControlValues();
};



extern zCInput *zinput;



#endif