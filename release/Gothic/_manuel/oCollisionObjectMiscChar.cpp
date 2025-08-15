/******************************************************************************** 
 
     $Workfile:: oCollisionObjectMiscChar.cpp      $                $Date:: 6.02.01 11:43    $
     $Revision:: 8                                 $             $Modtime:: 6.02.01 10:31    $
        Author:: Moos                                                           
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Character collision depentant on oCNpc
   created: 8.1.2001

 * $Log: /current_work/Gothic/_Manuel/oCollisionObjectMiscChar.cpp $
 * 
 * 8     6.02.01 11:43 Moos
 * 
 * 7     26.01.01 15:02 Moos
 * 
 * 6     25.01.01 14:48 Moos
 * 
 * 5     22.01.01 20:01 Moos
 * 
 * 4     16.01.01 11:30 Moos
 * 
 * 3     15.01.01 17:22 Moos
 * 
 * 2     12.01.01 12:38 Moos
 * 
 * 1     8.01.01 17:24 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 6.02.01 10:31 $)



#include <zCore.h>
#include <z3d.h>
#include <zPhysics.h>

#include <zCollisionDetector.h>
#include <zCollisionObject.h>

#include <zCollisionObjectMisc.h>

#include <oCollisionObjectMiscChar.h>
#include <oNpc.h>


zCOLLISION_OBJECT_DEFINITION (oCCollObjectCharacter		, FALSE)

oCCollObjectCharacter::oCCollObjectCharacter() 
:comeNearerCounter(-1), mustNotComeNearer(NULL)
{
};

oCCollObjectCharacter::~oCCollObjectCharacter() 
{
};




zREAL oCCollObjectCharacter::TurnSpeed() const{
    oCNpc *npc = zDYNAMIC_CAST<oCNpc>(GetVob());
    if (npc)
        return Alg_Deg2Rad(npc->GetTurnSpeed());
    else
        return 1;
}

zBOOL oCCollObjectCharacter::IsDead() const{
    oCNpc *npc = zDYNAMIC_CAST<oCNpc>(GetVob());
    if (npc)
        return npc->IsDead();
    else
        return FALSE;
}


void  oCCollObjectCharacter::PushAround(const zVEC3 &velocity){
    return;

    zCVob *vob = GetVob();
    
    if (vob){
        vob->SetPhysicsEnabled(TRUE);
    	vob->GetRigidBody()->SetMode(zPHY_RBMODE_SLIDE);
        vob->GetRigidBody()->SetVelocity(velocity);
        if (vob->GetGroundPoly())
            vob->GetRigidBody()->SetSliding(vob->GetGroundPoly()->GetNormal());
   //     static_cast<oCNpc *>(vob)->SetBodyState	(BS_STUMBLE);

        zCModel *model = zDYNAMIC_CAST<oCNpc>(vob)->GetModel();

        if (model)
            model->StartAni ("S_SLIDE");
    }
}


zBOOL oCCollObjectCharacter::DontLetHimComeNearer  (const zCVob *him) const{
    if (him == mustNotComeNearer)
        return ((int &)comeNearerCounter) -- > 0;
    else
        return FALSE;
}

zCConvexPrimitive  *oCCollObjectCharacter::GetPrimitiveCC () const
{
//    if (m_poPrimitiveCC)
//        return m_poPrimitiveCC;

    oCNpc* npc = zDYNAMIC_CAST<oCNpc>(GetVob());

	// ARGHHH: Die Get Methode GetModel garantiert das das Modelvisual auch eingeladen wird -> dirty
	if (npc) npc->GetModel();

    return zCCollObjectCharacter::GetPrimitiveCC();
}

// die Tests aus zCCollisionObjectMisc;
extern  zBOOL TestDynamic_Projectile_Char( zCCollisionObject*  collObject0,
	        							   zCCollisionObject*  collObject1,
			        					   zCCollisionReport** ppoCollReport);

extern  zBOOL TestDynamic_XXX_BoxPassThrough	(zCCollisionObject*  collObject0,	// in Bewegung
		        								 zCCollisionObject*  collObject1,	// statisch
				        						 zCCollisionReport** ppoCollReport);

extern zBOOL TestStatic_Char_Char	(zREAL timeStamp, 
									 zCCollisionObject*  collObject0, const zMAT4& trafoObj0,
									 zCCollisionObject*  collObject1, const zMAT4& trafoObj1,
									 zCCollisionReport** ppoCollReport);



void oCCollObjectCharacter::S_RegisterCollisionTestFuncs ()
{
    static zBOOL registered = FALSE;
    if (registered)
        return;
    registered = TRUE;
    
    zCCollisionDetector* collisionDetector = zCVob::S_GetCollisionDetector();
	zERR_ASSERT(collisionDetector);

	#define REG_STATIC_TEST(  classA, classB, testFunc) collisionDetector->RegisterStaticIntersectionTest  (classA::S_GetCollObjClass(), classB::S_GetCollObjClass(), testFunc)
	#define REG_DYNAMIC_TEST( classA, classB, testFunc) collisionDetector->RegisterDynamicIntersectionTest (classA::S_GetCollObjClass(), classB::S_GetCollObjClass(), testFunc)

	// static tests
	REG_STATIC_TEST (oCCollObjectCharacter	, oCCollObjectCharacter		, TestStatic_Char_Char);

	// dynamic tests
	REG_DYNAMIC_TEST(oCCollObjectCharacter	, zCCollObjectBoxPassThrough, TestDynamic_XXX_BoxPassThrough);
	REG_DYNAMIC_TEST(zCCollObjectProjectile	, oCCollObjectCharacter		, TestDynamic_Projectile_Char);
		
	#undef REG_STATIC_TEST
	#undef REG_DYNAMIC_TEST
};
