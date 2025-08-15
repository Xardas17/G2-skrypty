/******************************************************************************** 
 
     $Workfile:: zAccount.h       $                $Date:: 14.03.01 2:35    $
     $Revision:: 8                $             $Modtime:: 14.03.01 2:35    $
        Author:: Moos                                                           
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   RefCtr Accounting
   created: 5.2.2000

 * $Log: /current_work/ZenGin/_Manuel/zAccount.h $
 * 
 * 8     14.03.01 2:35 Hildebrandt
 * 
 * 7     9.02.01 10:36 Moos
 * 
 * 6     8.02.01 14:53 Moos
 * 
 * 5     7.02.01 12:53 Moos
 * 
 * 4     6.02.01 17:56 Moos
 * 
 * 3     5.02.01 18:01 Moos
 * 
 *********************************************************************************/

// DOC++
/// @author Author: Moos 
/// @version $Revisio: 1 $ ($Modtime: 14.03.01 2:35 $)

#ifdef _DEBUG
	#ifndef ZACCOUNT
		#define ZACCOUNT
	#endif
#endif

class zCAccount{
    friend class zCObject;

    static int s_actCounter;
public:
    static void  Begin();
    static void  End();
    static void  Add  (const void *object, const char *filename, int line, int num);
    static void  Sum  (const void *object);
    static void  Clear(const void *object);
    static zBOOL IsActive();
};

#ifdef ZACCOUNT
	#define zADDREF_ACCT(obj)         {zCAccount::Begin(); (obj)->AddRef();             zCAccount::Add  ((obj), __FILE__, __LINE__,  1);}
	#define zRELEASE_ACCT(obj)        {if (obj) { zCAccount::Begin(); (obj)->Release(); zCAccount::Add  ((obj), __FILE__, __LINE__, -1); obj = NULL;  } }
	#define zRELEASE_ACCT_NONULL(obj) {if (obj) { zCAccount::Begin(); (obj)->Release(); zCAccount::Add  ((obj), __FILE__, __LINE__, -1);              } }

	#define zADDREF_NOACCT(obj)         {zCAccount::Begin(); (obj)->AddRef();             zCAccount::End();}
	#define zRELEASE_NOACCT(obj)        {if (obj) { zCAccount::Begin(); (obj)->Release(); zCAccount::End(); obj = NULL;  } }
	#define zRELEASE_NOACCT_NONULL(obj) {if (obj) { zCAccount::Begin(); (obj)->Release(); zCAccount::End()               } }

	#undef  zRELEASE
	#define zRELEASE(obj)			 zRELEASE_ACCT(obj)

	#define ReadObject0()            ReadObjectAccount(__FILE__, __LINE__)
	#define ReadObject1(name)        ReadObjectAccount(__FILE__, __LINE__, (name))
	#define ReadObject2(name, obj)   ReadObjectAccount(__FILE__, __LINE__, (name), (obj))

	#undef zNEW
	#undef zNEW_ARRAY

	#define zNEW( className )					new(#className, __FILE__, __LINE__) className 
	#define zNEW_ARRAY( className, count )		new(#className, __FILE__, __LINE__) className [count]

#else
	#define zADDREF_ACCT(obj)			{(obj)->AddRef(); }
	#define zRELEASE_ACCT(obj)			zRELEASE(obj)
	#define zRELEASE_ACCT_NONULL(obj)	{(obj)->Release(); }

	#define zADDREF_NOACCT(obj)			{(obj)->AddRef(); }
	#define zRELEASE_NOACCT(obj)        zRELEASE(obj)
	#define zRELEASE_NOACCT_NONULL(obj) {(obj)->Release(); }

	#define ReadObject0()				ReadObject()
	#define ReadObject1(name)			ReadObject((name))
	#define ReadObject2(name, obj)		ReadObject((name), (obj))
#endif