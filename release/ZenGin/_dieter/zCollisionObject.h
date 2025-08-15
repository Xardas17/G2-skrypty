/******************************************************************************** 
 
     $Workfile:: zCollisionObject.h   $                $Date:: 11.01.01 18:45   $
     $Revision:: 7                    $             $Modtime:: 10.01.01 0:39    $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   Declares zCCollsionObject, a base class for logical collision types.
   created       : 8.12.2000

 * $Log: /current_work/zengin_work/_Dieter/zCollisionObject.h $
 * 
 * 7     11.01.01 18:45 Hildebrandt
 * 
 * 6     20.12.00 3:03 Hildebrandt
 * 
 * 5     15.12.00 3:55 Hildebrandt
 * 
 * 4     14.12.00 20:43 Hildebrandt
 * 
 * 3     13.12.00 3:24 Hildebrandt
 * 
 * 2     9.12.00 6:31 Hildebrandt
 * 
 * 1     8.12.00 21:29 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 7 $ ($Modtime: 10.01.01 0:39 $)

// ============================================================================================================

#ifndef __ZCOLLISIONOBJECT_H__
#define __ZCOLLISIONOBJECT_H__

struct zTBBox3D;

// ============================================================================================================

class zCCollisionObjectDef {
public:
	 zCCollisionObjectDef(const zBOOL isVolatile, zCCollisionObject* ( *_CreateNewInstance )());
	~zCCollisionObjectDef();

	//
	static int						S_GetNum				()			{ return s_aoCollObjClassList->GetNum();	};
	static zCCollisionObjectDef*	S_GetCollObjClassByIndex(int i)		{ return s_aoCollObjClassList->GetSafe(i);	};

	//
	zCCollisionObject*				CreateNewInstance		() const	{ return m_createNewInstance(); };
	zBOOL							IsVolatile				() const	{ return m_bIsVolatile; };
	int								GetIndex				() const	{ return m_iIndex; };

private:
	static zCArray<zCCollisionObjectDef*>*	s_aoCollObjClassList;
	zCCollisionObject*						( *m_createNewInstance )( void );
	zBOOL									m_bIsVolatile;
	int										m_iIndex;
};

//
#define zCOLLISION_OBJECT_DECLARATION( className )		\
public: \
	static	zCCollisionObjectDef*	className::S_GetCollObjClass	(void)			{ return &(className::s_oCollObjClass); }; \
	virtual	zCCollisionObjectDef*	className::GetCollObjClass		(void) const	{ return &(className::s_oCollObjClass); }; \
	static	zCCollisionObjectDef	className::s_oCollObjClass;						\
private: \
	static	zCCollisionObject*		className::_CreateNewInstance	(void);			

//
#define zCOLLISION_OBJECT_DEFINITION( className, isVolatile ) \
	zCCollisionObjectDef			className::s_oCollObjClass		(isVolatile, className::_CreateNewInstance);	\
	zCCollisionObject*				className::_CreateNewInstance	(void)			{ return zNEW(className); }


// ============================================================================================================

// defining logical Collisiontypes

class zCCollisionObject {
	zCOLLISION_OBJECT_DECLARATION (zCCollisionObject);
public:
	/*
		- Zustand t0
		- Zustand t1
		- Daten ueber das Kollisionsmedium (entweder direkt oder ptr auf gesharetes Objekt)
	*/

			 zCCollisionObject() : m_pvClientData(0), m_bHintTranslation(0), m_bHintRotation(0) {};
	virtual ~zCCollisionObject() {};

	// zCCollisionObject interface
	virtual void		zCCFASTCALL		DetectCollisionsSelf	(const zCArray<zCCollisionObject*>& otherCollObjectList,	// IN
																       zCArray<zCCollisionReport*>&	collReportList) {};		// OUT
	virtual void		zCCFASTCALL		CollisionResponse		(const zCArray<zCCollisionReport*>& collReportList, zBOOL& simulateFurther) {};
	virtual zREAL		zCCFASTCALL		GetAdaptiveStepSize		()							{ return 0; };
	virtual zBOOL		zCCFASTCALL		SuppressCollisionResponse()							{ return FALSE; };	// if TRUE and collisions are detected with this object, higher levels should NOT perform collResp
	virtual void		zCCFASTCALL		GetLargestBBox3DLocal	(zTBBox3D &bbox3DLocalOut);	// if collObject has several collision primitives, this is the local bbox of the union of the largest; is used to build the speedbox

	// accessors												
	void*								GetClientData			() const				{ return m_pvClientData;	};
	void								SetClientData			(void* dataPtr)			{ m_pvClientData = dataPtr;	};
	const zMAT4&						GetTrafoOld				() const				{ return m_oTrafoOld;		};
	zMAT4&								GetTrafoOld				()						{ return m_oTrafoOld;		};
	void								SetTrafoOld				(const zMAT4& inMat4)	{ m_oTrafoOld= inMat4;		};
	const zMAT4&						GetTrafoNew				() const				{ return m_oTrafoNew;		};
	zMAT4&								GetTrafoNew				()						{ return m_oTrafoNew;		};
	void								SetTrafoNew				(const zMAT4& inMat4)	{ m_oTrafoNew	= inMat4;	};

	// trafo hints
	void								SetTrafoHintTranslation	()						{ m_bHintTranslation= TRUE;	};
	void								SetTrafoHintRotation	()						{ m_bHintRotation	= TRUE;	};
	zBOOL								GetTrafoHintTranslation	() const				{ return m_bHintTranslation;};
	zBOOL								GetTrafoHintRotation	() const				{ return m_bHintRotation;	};
	zBOOL								HasMoved				() const				{ return (m_bHintTranslation || m_bHintRotation);	};
	void								ResetTrafoHints			()						{ m_bHintTranslation = m_bHintRotation = FALSE; };

	// helper
	void				zCCFASTCALL 	CalcIntermediateTrafo	(const zREAL time, zMAT4 &resultTrafo);		// time: [0;1], result = lerp (time, trafoOld, trafoNew)

protected:
	// explicity disable copy-contstructor and assignment-operator
	zCCollisionObject	(const zCCollisionObject&);
	zCCollisionObject&	operator=(const zCCollisionObject&);

private:
	zMAT4				m_oTrafoOld;
	zMAT4				m_oTrafoNew;
	void*				m_pvClientData;		// 'attachedVob'
	struct {
		zUINT8			m_bHintTranslation	: 1;
		zUINT8			m_bHintRotation		: 1;
	};
};

// =======================================================================================================================

#endif
