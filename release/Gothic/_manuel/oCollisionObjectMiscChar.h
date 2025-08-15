/******************************************************************************** 
 
     $Workfile:: oCollisionObjectMiscChar.h      $                $Date:: 6.02.01 11:43    $
     $Revision:: 6                               $             $Modtime:: 6.02.01 9:42     $
        Author:: Moos                                                           
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Character collision depentant on oCNpc
   created: 8.1.2001

 * $Log: /current_work/Gothic/_Manuel/oCollisionObjectMiscChar.h $
 * 
 * 6     6.02.01 11:43 Moos
 * 
 * 5     25.01.01 14:48 Moos
 * 
 * 4     22.01.01 20:01 Moos
 * 
 * 3     16.01.01 11:30 Moos
 * 
 * 2     15.01.01 17:22 Moos
 * 
 * 1     8.01.01 17:24 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 6.02.01 9:42 $)

#ifndef __OCOLLISIONOBJECT_H__
#define __OCOLLISIONOBJECT_H__

class oCCollObjectCharacter : public zCCollObjectCharacter {
public:
	static	zCCollisionObjectDef*	oCCollObjectCharacter::S_GetCollObjClass	(void)			{ return &(oCCollObjectCharacter::s_oCollObjClass); }; 
	virtual	zCCollisionObjectDef*	oCCollObjectCharacter::GetCollObjClass		(void) const	{ return &(zCCollObjectCharacter::s_oCollObjClass); };
private:
	static	zCCollisionObjectDef	oCCollObjectCharacter::s_oCollObjClass;		
	static	zCCollisionObject*		oCCollObjectCharacter::_CreateNewInstance	(void);			
//
public:
			 oCCollObjectCharacter();
	virtual ~oCCollObjectCharacter();

    virtual zCConvexPrimitive*		GetPrimitiveCC				() const;

    static void oCCollObjectCharacter::S_RegisterCollisionTestFuncs ();

    void    SetDontLetHimComeNearer(const zCVob *him, int timeout = 10){ mustNotComeNearer = him; comeNearerCounter = timeout; }
protected:    
    int          comeNearerCounter;
    const zCVob *mustNotComeNearer;

    virtual zREAL TurnSpeed             ()                  const;
    virtual void  PushAround            (const zVEC3 &v);
    virtual zBOOL IsDead                ()                  const;
    virtual zBOOL DontLetHimComeNearer  (const zCVob *him)  const;
};

#endif