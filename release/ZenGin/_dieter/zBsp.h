/******************************************************************************** 
 
     $Workfile:: zBSP.h               $                $Date:: 24.04.01 17:33   $
     $Revision:: 28                   $             $Modtime:: 23.04.01 18:15   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ 3D-Binary Space Partitioning (BSP)
   created       : 1.8.97

 * $Log: /current_work/ZenGin/_Dieter/zBSP.h $
 * 
 * 28    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 27    9.02.01 18:41 Moos
 * AlphaVob-Leakfix
 * 
 * 26    8.02.01 21:39 Hildebrandt
 * 
 * 25    8.02.01 6:53 Hildebrandt
 * 
 * 24    30.01.01 4:00 Hildebrandt
 * 
 * 23    25.01.01 17:01 Hildebrandt
 * 
 * 22    20.12.00 3:05 Hildebrandt
 * 
 * 21    4.12.00 17:19 Hildebrandt
 * 
 * 20    17.11.00 23:16 Hildebrandt
 * 
 * 19    17.11.00 16:35 Hildebrandt
 * 
 * 18    7.11.00 17:23 Hildebrandt
 * 
 * 17    22.09.00 14:17 Moos
 * 
 * 16    21.09.00 20:58 Moos
 * 
 * 15    21.09.00 17:58 Hoeller
 * 
 * 14    29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 13    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 17    9.08.00 17:12 Admin
 * 
 * 12    21.07.00 14:28 Hildebrandt
 * 
 * 11    11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 10    6.07.00 13:33 Hildebrandt
 * 
 * 5     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 7     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 5     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 4     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 28 $ ($Modtime: 23.04.01 18:15 $)


#ifndef __ZBSP_H__
#define __ZBSP_H__

#ifndef __Z3D_H__
#include <z3d.h>
#endif

#ifndef __ZBVOLUME_H__
#include <zBVolume.h>
#endif





// forward declarations
class zCCBspTree;
class zCCBspNode;
class zCBspTree;
class zCBspNode;
class zCBspLeaf;
class zCPluecker;
class zCRayCache;

class zCBspSector;
class zCBuildPortal;

// externals

extern int bspFrameCtr;

///////////////////////////////////////////////////////////////////////////
//     BSP
///////////////////////////////////////////////////////////////////////////

//***************************************************************************
//	Determines the given element's has value
//***************************************************************************
template < class ELEMENT > 
inline 
unsigned long g_GetHashValue( const ELEMENT& a_Element )
{
	return ( (unsigned long) (void*) (unsigned long) a_Element ) >> 4;
}

//***************************************************************************
//	TEMPLATE zCRayTurboValMap
//	Value map tempate to store Rayturbo items
//***************************************************************************
template < class KEY, class ELEMENT >
class zTRayTurboValMap
{
protected:


	//																												
	//-----------------------------------------------------------------------										
	//***************************     STRUCTS     ***************************										
	//-----------------------------------------------------------------------										
	//																												
public:											
	struct zSNode									
	{												
		KEY				m_Key		;				
		ELEMENT			m_Element	;				
		unsigned long	m_u32Hash	;				
		zSNode*			m_pNext		;				
	};																														

protected:									
	//																														
	//-----------------------------------------------------------------------												
	//***************************     ATTRIBS     ***************************												
	//-----------------------------------------------------------------------												
	//																														
	zCArray<zSNode*>				m_arrNodes;

public:											
	//																																					
	//-----------------------------------------------------------------------																			
	//***************************     CHECKS     ****************************																			
	//-----------------------------------------------------------------------																			
	//																																					
	zBOOL						IsEmpty				( void	) const
	{
		return ( 0 == this->GetCount() );
	}
	
	zBOOL						IsValidKey			( const	KEY& a_Key	) const
	{
		unsigned long u32Hash;
		const zSNode* pNode	=	this->GetNode( a_Key, u32Hash );

		if (NULL == pNode)
			return FALSE;

		return TRUE;
	}

	zBOOL						Contains			( const ELEMENT& a_Element	) const
	{
		return ( -1 != this->GetIndex( a_Element ) );
	}

public:											
		
		
	void						Clear				( void	)
	{
		this->RemoveAll();
	}

public:											
	//																													
	//-----------------------------------------------------------------------											
	//************************     LIST ACCESS     **************************											
	//-----------------------------------------------------------------------											
	//																													
	const	zCArray<zSNode*>&	GetData				( void )	const
	{
		return this->m_arrNodes;
	}

protected:										
	//																												
	//-----------------------------------------------------------------------										
	//***********************     ELEMENT ACCESS     ************************										
	//-----------------------------------------------------------------------										
	//																												
	zSNode*						AccessNode			( const KEY& a_Key, unsigned long& a_u32Hash	)
	{
		a_u32Hash	=	::g_GetHashValue< KEY >(a_Key) % this->m_arrNodes.GetNum();
		int iIndex	=	static_cast< int > (a_u32Hash);

		if ( this->m_arrNodes.IsEmpty() )
			return NULL;

		zSNode* pNode	=	this->m_arrNodes[iIndex];

		while( NULL != pNode )
		{
			if ( a_Key == pNode->m_Key )
				return pNode;

			pNode = pNode->m_pNext;
		}
		return NULL;
	}

	const	zSNode*				GetNode				( const KEY& a_Key, unsigned long& a_u32Hash	) const
	{
		a_u32Hash	=	::g_GetHashValue< KEY >( a_Key ) % this->m_arrNodes.GetNum();
		int	iIndex	=	static_cast< int > (a_u32Hash);

		if ( this->m_arrNodes.IsEmpty() )
			return NULL;

		zSNode* pNode	=	this->m_arrNodes[ iIndex ];

		while( NULL != pNode )
		{
			if ( a_Key == pNode->m_Key )
				return pNode;

			pNode = pNode->m_pNext;
		}

		return NULL;
	}

public:											
	ELEMENT&					AccessAt			( const KEY& a_Key	)
	{
		unsigned long	 u32Hash;
		zSNode* pNode	=	this->AccessNode( a_Key, u32Hash );

		if ( NULL != pNode )
			return pNode->m_Element;

		pNode	=	new zSNode;

		pNode->m_Key		= a_Key ;
		pNode->m_u32Hash	= u32Hash;
		pNode->m_pNext		= this->m_arrNodes[ u32Hash ];

		this->m_arrNodes[ u32Hash ]		=	pNode;

		return pNode->m_Element;
	}

	
	const ELEMENT&				GetAt				( const KEY& a_Key	) const
	{
		unsigned long	u32Hash;
		const zSNode* pNode  =	this->GetNode( a_Key, u32Hash );

		return pNode->m_Element;
	}
	
	zBOOL						GetAt				( const KEY& a_Key, ELEMENT& a_Element ) const
	{
		unsigned long	 u32Hash;
		const zSNode* pNode  =	this->GetNode( a_Key, u32Hash );

		if ( NULL != pNode )
		{
			a_Element	=	pNode->m_Element;
			return TRUE;
		}

		return FALSE;
	}

	void						SetAt				( const KEY& a_Key, const ELEMENT& a_Element	)
	{
		this->AccessAt( a_Key )		=	a_Element;
	}

	zBOOL						RemoveAt			( const KEY& a_Key	)
	{
		unsigned long	u32Hash	=	::g_GetHashValue< KEY >( a_Key ) % this->m_arrNodes.GetNum();
		int				iIndex	=	static_cast< int > (u32Hash);

		if (TRUE == this->m_arrNodes.IsEmpty())
			return GEFalse;

		zSNode* pNode			=	this->m_arrNodes[ iIndex ];

		if ( a_Key == pNode->m_Key )
		{
			this->m_arrNodes[ iIndex ]	=	pNode->m_pNext;
			delete pNode;

			return TRUE;
		}

		while( NULL != pNode->m_pNext )
		{
			if ( a_Key == pNode->m_pNext->m_Key )
			{
				zSNode* pOldNode	=	pNode->m_pNext;
				pNode->m_pNext		=	pNode->m_pNext->m_pNext;

				delete pOldNode;
				return TRUE;
			}

			pNode = pNode->m_pNext;
		}

		return FALSE;
	}

	void						DeleteAll			( void	)
	{
		int iIndex = 0;
		for ( iIndex = 0; iIndex < this->m_arrNodes.GetNum(); iIndex++ )
		{
			zSNode* pNode	=	this->m_arrNodes[ iIndex ];
			zSNode* pNext	=	NULL;

			while( NULL != pNode )
			{
				pNext	=	pNode->m_pNext;
				delete pNode->m_Element;
				delete pNode;

				pNode	=	pNext;
			}
		}

		this->m_arrNodes.EmptyList();
		this->Init();
	}

	void						RemoveAll			( void	)
	{
		int iIndex = 0;
		for ( iIndex = 0; iIndex < this->m_arrNodes.GetNum(); iIndex++ )
		{
			zSNode* pNode	=	this->m_arrNodes[ iIndex ];
			zSNode* pNext	=	NULL;

			while( NULL != pNode )
			{
				pNext	=	pNode->m_pNext;
				delete pNode;
				pNode	=	pNext;
			}
		}

		this->m_arrNodes.EmptyList();
		this->Init();
	}

	//																							
	//-----------------------------------------------------------------------					
	//**************************     OPERATORS     **************************					
	//-----------------------------------------------------------------------					
	//																							
public:												
	const	ELEMENT&			operator []			( const KEY& a_Key ) const
	{
		return this->GetAt( a_Key );
	}
	
	ELEMENT&					operator []			( const KEY& a_Key )
	{
		return this->AccessAt( a_Key );
	}

	//																												
	//-----------------------------------------------------------------------										
	//**********************     CREATION/DELETION     **********************										
	//-----------------------------------------------------------------------										
	//																												
protected:											
	void						Init				( void )
	{
		this->InitHashTable ( 97 );
	}
public:																		
	void						InitHashTable		( unsigned long a_u32HashCount	)
	{
		//
		//	SET COUNT
		//
		this->m_arrNodes.DeleteList();
		this->m_arrNodes.AllocAbs  ( a_u32HashCount );

		//
		//	INVALIDATE POINTERS
		//
		for ( int iNode = 0; iNode < static_cast< int > (a_u32HashCount); iNode++ )
		{
			zSNode* pDummyNode	=	NULL;
			this->m_arrNodes.Insert( pDummyNode );
		}
	}

	//																															
	//-----------------------------------------------------------------------													
	//***********************     CON/DESTRUCTION     ***********************													
	//-----------------------------------------------------------------------													
	//																															
private:
	zTRayTurboValMap								( const zTRayTurboValMap< KEY, ELEMENT >&	a_Source	) {}
public:											
	 zTRayTurboValMap								( void	)
	 {
		this->Init();
	 }
	
	 ~zTRayTurboValMap								( void	)
	 {
		this->RemoveAll();
	 }

};

//*****************************************************************************
//** GECMeshOctreeNode
//*****************************************************************************

class zCMeshOctreeNode
{

public:
	//																															
	//-----------------------------------------------------------------------													
	//***********************         ATTRIBS         ***********************													
	//-----------------------------------------------------------------------													
	//																															

	typedef		zCPolygon**				zCArrPolygonList;
	typedef		zCArray<unsigned char>	zCArrPolyInside;	// @DEVNOTE: OPTIMIZE -> Bitfield
	typedef		zCArray<zCPolygon*>		zCArrPolys;
	
	// Child indices

	enum zEOctreeChild
	{
		zEOctreeChild_Min	=	0,
		zEOctreeChild_1		=	zEOctreeChild_Min,
		zEOctreeChild_2,
		zEOctreeChild_3,
		zEOctreeChild_4,
		zEOctreeChild_5,
		zEOctreeChild_6,
		zEOctreeChild_7,
		zEOctreeChild_8,
		zEOctreeChild_Max
	};

private:
	//																															
	//-----------------------------------------------------------------------													
	//***********************         MEMBERS         ***********************													
	//-----------------------------------------------------------------------													
	//																															

	// Node's children
	zCMeshOctreeNode*				m_parrChildren[8];

	// Node's "bounding" box
	zTBBox3D			m_Box;

	// Node's types
	unsigned char		m_bIsRoot		:	1;
	unsigned char		m_bIsNode		:	1;
	unsigned char		m_bIsLeaf		:	1;

	// Polys
	zCArrPolys				m_arrPolys;

private:
	//																															
	//-----------------------------------------------------------------------													
	//***********************      MODIFICATION      ***********************													
	//-----------------------------------------------------------------------													
	//																															
	// Enlarge node's "bounding" box
	void				EnlargeBox					( const zCArrPolys& a_arrPolyList	);

	void				CopyPolys					( const zCArrPolyInside& a_arrInsidePolygons,
													  const zCArrPolys& a_arrPolys,
													  int a_iCount,
												  	  zCArrPolys&	a_arrPolysDst	);
private:
	//																															
	//-----------------------------------------------------------------------													
	//***********************     CON/DESTRUCTION     ***********************													
	//-----------------------------------------------------------------------													
	//																															
	// Avoid automatic generation
	zCMeshOctreeNode								( const zCMeshOctreeNode& a_Other	)	{}
	zCMeshOctreeNode&	operator=					( const zCMeshOctreeNode& a_Other	)	{}
public:

	// Con-/Destruction
	zCMeshOctreeNode								( zBOOL a_bIsRoot = FALSE	);
	~zCMeshOctreeNode								( void	);

public:
	//																															
	//-----------------------------------------------------------------------													
	//***********************      MODIFICATION      ***********************													
	//-----------------------------------------------------------------------													
	//																															

	// Build octree
	void						Build				( const zCArrPolys& a_arrPolyList,
													  int a_iVertexLimit				);
	//																													
	//-----------------------------------------------------------------------											
	//************************         GET/SET     **************************											
	//-----------------------------------------------------------------------											
	//																													
	const zTBBox3D&				GetBox				( void	) const
	{
		return this->m_Box;
	}

	// Return node's types
	zBOOL						IsRoot				( void	) const
	{
		return this->m_bIsRoot;
	}

	zBOOL						IsNode				( void	) const
	{
		return m_bIsNode;
	}

	zBOOL						IsLeaf				( void	) const
	{
		return m_bIsLeaf;
	}

	// Return node's children
	const zCMeshOctreeNode*		GetChild			( zEOctreeChild a_Child	) const
	{
		return m_parrChildren[ a_Child ];
	}

	// Return polys inside this node
	const zCArrPolys&			GetPolys			( void	) const
	{
		return this->m_arrPolys;
	}

};

//
//------------------------------------------------------ FORWARD DECLARATIONS
//

class zCBspNode;

//***************************************************************************
//	CLASS zCRayTurbo
//	TurboRay Admin to manage rayturbo nodes
//***************************************************************************
class zCRayTurbo
{
	const				zCBspNode&						m_BspNode;
						zCMeshOctreeNode				m_MeshOctreeRoot;


private:
	//																															
	//-----------------------------------------------------------------------													
	//***********************     CON/DESTRUCTION     ***********************													
	//-----------------------------------------------------------------------													
	//																															
	zCRayTurbo											( const zCRayTurbo& a_Source	) : m_BspNode( a_Source.m_BspNode )	{}
	zCRayTurbo											( void	);
public:
	zCRayTurbo											( const zCBspNode& a_BSPNode	);
	~zCRayTurbo											( void	);


public:
	//																															
	//-----------------------------------------------------------------------													
	//***********************      MODIFICATION      ***********************													
	//-----------------------------------------------------------------------													
	//																															
	void				CalculateOptimizedPolyList		( zCMeshOctreeNode::zCArrPolys& a_arrMatchedPolys	);
protected:
	void				TraverseTree					( zCMeshOctreeNode::zCArrPolys& a_arrMatchedPolys, const zCMeshOctreeNode& a_OctreeNode	);
};



//***************************************************************************
//	CLASS zCRayTurboAdmin
//	TurboRay Admin to manage rayturbo nodes
//***************************************************************************
class zCRayTurboAdmin
{
protected:
	//																														
	//-----------------------------------------------------------------------												
	//***************************     ATTRIBS     ***************************												
	//-----------------------------------------------------------------------												
	//																														
	static	int													s_iPolyTreshold;
	zTRayTurboValMap<zCBspNode*, zCRayTurbo*>					m_mapRayTurbos;

public:
	enum	{ zEMaxPolyThreshold	=	500 };
public:
	//																													
	//-----------------------------------------------------------------------											
	//************************   GET/SET/CREATION  **************************											
	//-----------------------------------------------------------------------											
	//																											
	static int											GetPolyTreshold				();
	static void											SetPolyTreshold				( const int a_iPolyTreshold );
	zCRayTurbo*											GetOrCreate					( const zCBspNode* a_pNode	);

	zBOOL												CanHaveSpatialInfo			( const zCBspNode* a_pNode	);
protected:
	zCRayTurbo*											GetRayTurboItem				( const zCBspNode* a_pNode	)	const;
	zCRayTurbo*											CreateRayTurboItem			( const zCBspNode* a_pNode	);

public:
	const zTRayTurboValMap<zCBspNode*, zCRayTurbo*>&	AccessMap					( void	)	const
	{
		return this->m_mapRayTurbos;
	}

	void												ReleaseSpatialDatabase		( void	);
public:
	//																													
	//-----------------------------------------------------------------------											
	//************************       CREATION      **************************											
	//-----------------------------------------------------------------------											
	//																													
	static	zCRayTurboAdmin&							GetInstance					( void	);

protected:
	//																															
	//-----------------------------------------------------------------------													
	//***********************     CON/DESTRUCTION     ***********************													
	//-----------------------------------------------------------------------													
	//																															
	zCRayTurboAdmin												( void	);
public:
	~zCRayTurboAdmin											( void	);
};

//
// -----------------------------------------------------------------------------------
// ***********************************************************************************
// -----------------------------------------------------------------------------------
//

enum zTBspPolyCont { zBSP_CONT_NOTHING=0, zBSP_CONT_MESH=-1, zBSP_CONT_BSP=-2 };
enum zTBspNodeType { zBSP_LEAF=1, zBSP_NODE=0 };

class zENGINE_API zCBspBase {
	zCBspBase& operator=(const zCBspBase&);			// explicity disable copy-contstructor
public:
	zCBspNode				*parent;						// index, nötig ??
	zTBBox3D				bbox3D;							
	zCPolygon				**polyList;
	int						numPolys;						
	zTBspNodeType			nodeType;						// zTBspNodeType
//	zBOOL8					lightingDirty;
//	zTFrameCtr				lastTimeLighted;				// the last time that this node/leaf was lighted
							
	zBOOL					IsLeaf						() const { return nodeType==zBSP_LEAF; };
	zBOOL					IsNode						() const { return nodeType==zBSP_NODE; };
	zTBspNodeType			GetNodeType					() const { return nodeType; };
							
	int						GetNumPolys					() const { return numPolys; };
	zCPolygon**				GetPolyList					() const { return polyList; };
							
	//						
	void					CollectNodeLights			();
	
	// Vob-Handling
	// (attention: CollectVobs..() does not return lights or zones, results are added to the resVobList )
	void	zCCFASTCALL		CollectLightVobsSubtree		(zCArray<zCVob*>& resVobList) const;
	void	zCCFASTCALL		CollectVobsSubtree			(zCArray<zCVob*>& resVobList) const;
	void	zCCFASTCALL		CollectVobsInBBox3D			(zCArray<zCVob*>& resVobList, const zTBBox3D& inbbox3D) const;
	void	zCCFASTCALL		AddVobToLeafs				(zCVob* vob);
	void	zCCFASTCALL		AddVobLightToLeafs			(zCVobLight* vob);
	void	zCCFASTCALL		RemoveVobFromLeafs			(zCVob* vob);
		 					
	//						
	zBOOL	zCCFASTCALL		CollectPolysInBBox3D		(const zTBBox3D& testbbox3D, zCPolygon**& foundPolyList, int& foundPolyNum) const;
	zTBBox2D				GetScreenBBox2D				() const;
							
	//						
	zCBspBase*				FindRoot					();
	zCBspLeaf*				FindLeaf					(const zPOINT3& point); 
	void					DescribeTree				(int indent=0);				// debug
	int						CountNodes					();
	void					SaveBINRec					(zCFileBIN& file);
	void					LoadBINRec					(zCFileBIN& file);
												
    static void             ReleaseStaticReferences     (); // [Moos] löscht alle temporären Referenzen auf Vobs und so... (gegen NPC-Leaks)

protected:
	zCBspBase () { 
		parent			= 0;
		numPolys		= zBSP_CONT_NOTHING;
		polyList		= 0;
	};

	//
	void	zCCFASTCALL		RenderIndoor				(int clipFlags=zCCamera::CLIP_FLAGS_FULL);
	void					RenderTrivInIndoor			();
	static void	zCCFASTCALL RenderOutdoor				(zCBspBase* node, zTBBox3D bbox3DCell, int clipFlags=zCCamera::CLIP_FLAGS_FULL, zBOOL crossingVobFarPlane=TRUE);
	void					RenderTrivInOutdoot			();
	void	zCCFASTCALL		AddVobsToRenderListSubtree	(int clipFlags);
	void	zCCFASTCALL		RenderNodeOutdoor			(int clipFlags);
							
	zBOOL	zCCFASTCALL		CheckRayAgainstPolys		   (const zPOINT3& start, const zPOINT3& end, zPOINT3& inters, zCRayTurbo* a_pRayTurbo = NULL) const;
	zBOOL	zCCFASTCALL		CheckRayAgainstPolysNearestHit (const zPOINT3& start, const zPOINT3& end, zPOINT3& inters, zCRayTurbo* a_pRayTurbo = NULL) const;
	zBOOL	zCCFASTCALL		CheckRayAgainstPolysCache      (const zPOINT3& start, const zPOINT3& end, zPOINT3& inters) const;
							
	void	zCCFASTCALL		CollectVobsSubtree_I		(zCArray<zCVob*>& resVobList) const;
	void	zCCFASTCALL		CollectVobsInBBox3D_I		(zCArray<zCVob*>& resVobList, const zTBBox3D& inbbox3D) const;
	void	zCCFASTCALL		CollectLightVobsSubtree_I	(zCArray<zCVob*>& resVobList) const;
	zBOOL	zCCFASTCALL		RayIntersection				(const zPOINT3& start, const zPOINT3& end, zPOINT3& inters) const;
	
	void					CollectPolysInBBox3DRec		() const; // Portals are sorted out
	// Preprocessing							
	void					SortNodePolys				(zCBspTree *hostTree);		// solid < portal < sector

	friend zCBspTree;
};

// =====================================================================================================================

class zENGINE_API zCBspNode : public zCBspBase {
	zCBspNode(const zCBspNode&);					// explicity disable copy-contstructor and assignment-operator
	zCBspNode& operator=(const zCBspNode&);
public:
	zTPlane		plane;
	zCBspBase	*front;			
	zCBspBase	*back;		
	zCBspLeaf	*leafList;
	int			numLeafs;
	zBYTE		planeSignbits;

	zCBspNode() {
		nodeType		= zBSP_NODE;
		front			= back = 0;
		leafList		= 0;
		numLeafs		= 0;
	};
	void CalcPlaneSignbits (zCBspTree *hostBspTree);
};

// =====================================================================================================================

class zENGINE_API zCBspLeaf : public zCBspBase {
	zCBspLeaf(const zCBspLeaf&);					// explicitly disable copy-contstructor and assignment-operator
	zCBspLeaf& operator=(const zCBspLeaf&);
public:
	zTFrameCtr				lastTimeLighted;
	zCArray<zCVob*>			leafVobList;
	zCArray<zCVobLight*>	lightVobList;			// ordered list:	a) 3 stat Lights, b) 2 stat Lights mit Visual/Lensflare, c) 1 dyn  Lights mit Visual/Lensflare, d) 0 dyn  Lights
	zTFrameCtr				lastTimeActivated;		// last time activated by portal
	zWORD					sectorIndex;			// sector this leaf was activated by


	// traceRay accelerator
    zWORD                   polyPlueckerRefCtr;     // reference counter to pointer below
    zCPluecker             *polyPluecker;           // array containing the pluecker coordinates of the Polygons

	// static lighting info
	enum					{ zBSP_LEAF_LIGHT_UNDEFINED = -99 };
	zPOINT3					lightPosition;			// FIXME: pack this?
//	zCOLOR					cornerLightDirection[8];

	zCBspLeaf () { 
		lastTimeLighted		= -1;
		nodeType			= zBSP_LEAF;
//		lastTimeProcessed	= -1;
		lastTimeActivated	= -1;
		sectorIndex			= 0;
		lightPosition		= zVEC3(zREAL(zBSP_LEAF_LIGHT_UNDEFINED));

        polyPlueckerRefCtr  = 0;
        polyPluecker        = 0;
	};

    ~zCBspLeaf();
    void				PolyPlueckerAddRef			();  // dynamic creation/deletion mechanism
    void				PolyPlueckerRelease			();  // for the pluecker coordinates
						
	void zCCFASTCALL	RenderLeafIndoor			(int clipFlags);

	void zCCFASTCALL	AddVobsToRenderList			(zTBBox2D *sectorPortal2D=0);		// sectorPortal2D can be 0, if there is no portal to test against
	void				AddVobsToRenderListOutdoor	();									// if collecting vobs NOT from sectors
	void zCCFASTCALL	AddVobsToRenderListOutdoor	(zCBspSector* sector, const zTBBox2D& sectorPortal2D);	// for collecting vobs from sectors / through portals
	void zCCFASTCALL	TraceRayCollectVobs			(zCArray<zCVob*>& resVobList, const zTBBox3D& rayBBox, int traceFlags) const;
};

// =====================================================================================================================

enum zTBspTreeMode		{	zBSP_MODE_INDOOR,
							zBSP_MODE_OUTDOOR };

class zENGINE_API zCBspTree {
	zCBspTree(const zCBspTree&);					// explicity disable copy-contstructor and assignment-operator
	zCBspTree& operator=(const zCBspTree&);
public:
	// debug
	static zBOOL			GetShowPortals				()				{ return s_showPortals; };
	static void				SetShowPortals				(const zBOOL b) { s_showPortals=b;		};
	static zBOOL			S_GetRenderAllPortals		()				{ return s_renderAllPortals;		};
	static void				S_SetRenderAllPortals		(const zBOOL b)	{ s_renderAllPortals = b;			};


	//
	zCBspNode				*actNodePtr;			// load/build
	zCBspLeaf				*actLeafPtr;			// load/build
													
	zCBspBase				*bspRoot;				// points to treeRoot (node or leaf), but does not own the object
	zCMesh					*mesh;					// Poly/Vert Container-Mesh
	zCPolygon				**treePolyList;			// Ptr to mesh, bspTree or polyList
	zCBspNode				*nodeList;				
	zCBspLeaf				*leafList;				
	int						numNodes;				
	int						numLeafs;				
	int						numPolys;				
	zCArray<zCVob*>			renderVobList;			// list of vobs rendered the last frame
	zCArray<zCVobLight*>	renderLightList;		// list of lights in the last frame
													
	zCArray<zCBspSector*>	sectorList;				// for outdoor-rendering
	zCArray<zCPolygon*>		portalList;				// (for indoor-rendering), portals [i] and [i+1] have the same plane
													
	zTBspTreeMode			bspTreeMode;
	zTWld_RenderMode		worldRenderMode;

	zREAL					vobFarClipZ;
	zTPlane					vobFarPlane;
	int						vobFarPlaneSignbits;
							
	//						
	zBOOL					drawVobBBox3D;
							
	// stats				
	int						leafsRendered;
	int						vobsRendered;
							
	 zCBspTree ();			
	~zCBspTree ();			
	void					DisposeTree				();		// deletes everything within
	void					Render					();
	void					RenderPortal			();
	void					Build					(zCCBspTree* ctree);
	zCBspLeaf*				FindLeaf				(const zPOINT3& point)	{ return bspRoot->FindLeaf (point); };
	zCBspBase*				GetRoot					() const				{ return bspRoot; };
	zBOOL					TraceRay				(const zPOINT3& start, 
													 const zPOINT3& end, 
													 const int		traceFlags,
													 zPOINT3& inters, zCPolygon* &hitPoly, zCArray<zCVob*> *vobList) const;
    static void SetRayCache(zCRayCache *cache);     // set the ray cache to be used for the next call of TraceRay
	zCArray<zCVob*>*		GetLastRenderVobList	() { return &renderVobList; };
	zBOOL					FindLeaks				(zCArray<zCPolygon*>& leakPolyList);
	void					SetBspTreeMode			(const zTBspTreeMode& bspMode)	{ bspTreeMode = bspMode; };
	zTBspTreeMode			GetBspTreeMode			() const						{ return bspTreeMode; };
	void					MarkOccluderPolys		();
	zTBBox3D				CalcLeafRealBBox3D		(const zPOINT3& point);
	void					UpdateVertexDependencies(zCVertex *vert);			// call this, if vertex pos has changed, updates internals
	zBOOL					CollectPolysInBBox3D	(const zTBBox3D& testbbox3D, zCPolygon**& foundPolyList, int& foundPolyNum) const { return GetRoot()->CollectPolysInBBox3D(testbbox3D, foundPolyList, foundPolyNum); };	// the array is owned by this object, dont free it !
	zBOOL					CollectPolysInBBox3DAngle(const zTBBox3D&	testbbox3D, 
													  const zVEC3&		axis, 
													  const zREAL		angleMinDeg, 
													  const zREAL		angleMaxDeg, 
													  zCPolygon**&		foundPolyList,			// the caller doesn't own this mem, don't delete !
													  int&				foundPolyNum) const;	// filters polys with normals that differ from axis by min/max angleDeg
							
	// Bsp-Sectors			
	void					RenderActivatedSectors	();
	void					CreateBspSectors2		(zCCBspTree *ctree);
	zCBspSector*			GetBspSectorByName		(const zSTRING& name) const;
	void					ConnectMaterialsToSectors();		// Load
	const zSTRING*			GetSectorNameVobIsIn	(const zCVob *vob) const;		// returns the name of the sector (portal-enclosed), if vob is within a sector(determined by groundPoly); returns 0 if not in sector
	

	// Indoor Portals
	void					PreprocessIndoorPortals	(zCMesh *mesh, zCArray<zCBuildPortal*> &portalList);
	void					PostprocessIndoorPortals(zCArray<zCBuildPortal*> &portalList);
	
	// Vob-Handling			
	zBOOL					GetDrawVobBBox3D		() const	{ return drawVobBBox3D; };
	void					SetDrawVobBBox3D		(zBOOL b)	{ drawVobBBox3D = b; };
	void					AddVob					(zCVob* vob);
	void					RemoveVob				(zCVob* vob);
	void					AdjustVob				(zCVob* vob);
	void					OptimizeLight			();
													
	// Save/Load									
	static zWORD			GetFileVersion			();
	zBOOL					LoadBIN					(zCFileBIN& file, zBOOL skipThisChunk=FALSE);
	void					SaveBIN					(zCFileBIN& file);

	// static lighting
	void					CalcStaticLeafLightData ();
	zBOOL					GetRenderedFirstTime  ()										{ return m_bRenderedFirstTime;	};
	void					SetRenderedFirstTime  (const zBOOL a_bRenderedFirstTime)		{ m_bRenderedFirstTime = a_bRenderedFirstTime;};
	
private:
	zBOOL					m_bRenderedFirstTime;
	static	zBOOL			s_showPortals;
	static	zBOOL			s_renderAllPortals;
	zTFrameCtr				masterFrameCtr;
							
	zCPolygon				**actPolyPtr;			// load/build
	zBOOL					compiled;

	void					InitTree				();	
	zCBspBase*				BuildRecursive			(zCCBspNode *cnode);
	void					RenderVobList			();
	void					RenderLightList			();
	void					GetPolyNeighbours		(zCPolygon *sourcePoly, zCPolygon**& foundPolyList, int& foundPolyNum); //indoorPortals postprocessing
	zREAL					GetOccluderAreaRec		(const zCPolygon* rootPoly , zCArray<zCPolygon*>&nearOccluderPolys);
};

///////////////////////////////////////////////////////////////////////////
//     CONSTRUCTION/BUILD BSP
///////////////////////////////////////////////////////////////////////////

enum zTBspBuildType	{
	zBSP_TYPE_OCTREE,
	zBSP_TYPE_OCTREE_SOLID,
	zBSP_TYPE_LEAFY_BSP,
};

class zTPolyNode {
public:
	zCPolygon	*poly;
	zTPolyNode	*next;
	zBOOL		marked;								// for bsp-compiler/=has been used as splitter
	zBOOL8		isCompleteInside;					// for octree-compiler/adaptive refinement
	zTPolyNode() { marked = FALSE; isCompleteInside=TRUE; };
	zTPolyNode(zCPolygon *_poly, zBOOL _marked) { 
		poly	= _poly;
		marked	= _marked;
	};
};

class zCCBspNode {
	zCCBspNode(const zCCBspNode&);					// explicity disable copy-contstructor and assignment-operator
	zCCBspNode& operator=(const zCCBspNode&);
public:
	zTPlane				plane;
	zCCBspNode			*front,*back;
	zCCBspNode			*parent;
	zTBBox3D			bbox3D;			// bbox of contained polys			(bigger)
	zTBBox3D			bbox3DCell;		// bbox of the real cell-subspace	(smaller)
//	zCArray<zDWORD>		pvsLeafList;	// bit-string
	zCList2<zTPolyNode>	polyList;
	
	//

	// methods
	zCCBspNode() {
		front	= back = parent = 0;
		
	};
	zCCBspNode(zCCBspNode *node) {
		front	= back = 0;
		parent	= node;
		
	};
	~zCCBspNode() {
		polyList.DeleteList();	// delete all contained polyNodes, not the polys
		delete front;	front=0;
		delete back;	back =0;
		parent=0;
	};
	zBOOL IsLeaf	() const { return ((front==0) && (back==0)); };
	void PushPolyFront	(zTPolyNode *polyNode) {
		if (front==0) front = zNEW(zCCBspNode(this));
		polyList.Remove (polyNode);
		front->AddPoly  (polyNode);
	};
	void PushPolyBack	(zTPolyNode *polyNode) {
		if (back==0) back = zNEW(zCCBspNode(this));
		polyList.Remove (polyNode);
		back->AddPoly   (polyNode);
	};
	void PushPolyFront	(zCPolygon *poly) {
		zTPolyNode *polyNode = zNEW(zTPolyNode);
		polyNode->poly = poly;
		PushPolyFront (polyNode);
	};
	void PushPolyBack	(zCPolygon *poly) {
		zTPolyNode *polyNode = zNEW(zTPolyNode);
		polyNode->poly = poly;
		PushPolyBack (polyNode);
	};
	void PushPolyBoth	(zTPolyNode *polyNode) {
		// push Front
		PushPolyFront (polyNode);
		// push Back
		zTPolyNode *newPolyNode = zNEW(zTPolyNode (polyNode->poly, polyNode->marked));
		if (back==0) back = zNEW(zCCBspNode(this));
		back->AddPoly (newPolyNode);
	};
	void AddPoly		(zTPolyNode *polyNode) {
		polyList.Insert (polyNode);
	};
	void AddPoly		(zCPolygon *poly) {
		zTPolyNode *polyNode = zNEW(zTPolyNode);
		polyNode->poly = poly;
		polyList.Insert (polyNode);
	};
	void RemovePoly		(zCPolygon *poly);

	void		SelectPlane				(zTPlane& plane, zTPolyNode* &splitPolyNode, zBOOL& convexSet);
	void		SelectPlaneOctree		(zCCBspTree *cbspTree, zTPlane& plane, int recDepth);

	void		BuildTree				(int recDepth=0);

	int			ClassifyPolyToNode		(zCPolygon* poly);
	int			ClassifyPolyToNode2		(zCPolygon* poly);
//	zBOOL		RayIntersectsNode		(const zVEC3& startRay, const zVEC3& endRay);
	int			ClassifyRayToNode		(const zVEC3& startRay, const zVEC3& endRay);
	int			CountNodes				();
	int			CountLeafs				();
	int			CountPolys				();
	void		CountDepth				(int& maxDepth, int& minDepth, int& avgDepth);
	zTBBox3D	GetBBox3D				() { return bbox3D; };
	void		CalcSubtreeBBox3DCell	();
	void		CalcSubtreeBBox3D		();
	void		CalcBBox3D				(); 
	void		Render					();
	void		RenderTrivIn			();
	void		DescribeTree			(int indent=0);
	int			OutdoorKillRedundantLeafs();
	int			IndoorKillRedundantLeafs ();
	
	zBOOL		DoesNodeContainPoly		(zCPolygon* poly);

	// Portals
	void		Portalize				();
	void		SplitPortals			();
	zCPortal*	SplitPortalByAllPortals (zCPortal* portal);
	int			CheckPortalConsistency	();
	void		EnumeratePortals		();
	void		ClassifyPortals			();

	// Duplikate aus zCBspBase ... ich koennte kotzen..
	zBOOL		CheckRayAgainstPolysNearestHit	(const zPOINT3& start, const zPOINT3& end, zPOINT3& inters, zCRayTurbo* a_pRayTurbo = NULL) const;
	zBOOL		RayIntersectionOctree			(const zPOINT3& start, const zPOINT3& end, zPOINT3& inters) ;
	zBOOL		CollectPolysInBBox3D			(const zTBBox3D& testbbox3D, zCPolygon**& foundPolyList, int& foundPolyNum) ;
	void		CollectPolysInBBox3DRec			() ;
	zBOOL		TraceRay						(const zPOINT3& start, const zPOINT3& end, zCPolygon* &hitPoly, zVEC3& inters);
	zBOOL		TraceRay						(const zPOINT3& start, const zPOINT3& end, zCPolygon* &hitPoly);

private:
	void		CountDepthRec			(int depth, int& maxDepth, int& minDepth, int& sumDepth);
};

// =====================================================================================================================

class zCCBspTree {
	zCCBspTree(const zCCBspTree&);					// explicity disable copy-contstructor and assignment-operator
	zCCBspTree& operator=(const zCCBspTree&);
public:
	enum			zTSpanningMode { zSPANNING_SPLIT, zSPANNING_CENTER, zSPANNING_PUSHBOTH };

	zCCBspNode		bspRoot;
	zCMesh*			mesh;

	zTBspTreeMode	bspTreeMode;
	zCArray<zCBspSector*> sectorList;		// for outdoor-rendering
	
	// config
	zTSpanningMode	cfg_spanningMode;		
	zBOOL			cfg_useAllPolys;
	zBOOL			cfg_octree;				// m
	zTBspBuildType	cfg_bspType;
	zREAL			cfg_optimize;			// 1.0 = best possible optimization
	zREAL			cfg_wbalance;
	zREAL			cfg_wsplit;
	zREAL			cfg_wplanar;
	zBOOL			cfg_portalize;
//	zBOOL			cfg_renderBBox3D;
//	zBOOL			cfg_leafSolids;			// ?
//	zBOOL			cfg_octreeAdaptive;		// m
//	zBOOL			cfg_leafy;				// m
	
	// methods
	zCCBspTree	();
	~zCCBspTree	();
	void			DeleteTree			();
	void			AddMesh				(zCMesh* mesh);
	void			AddMesh				(zCMesh* mesh, const zMATRIX4& trafoObjToWorld);
	void			BuildTree			(const zREAL optimize);
	void			MarkGhostOccluder	();

	int				CountNodes			() { return bspRoot.CountNodes(); };
	int				CountLeafs			() { return bspRoot.CountLeafs(); };
	int				CountPolys			() { return bspRoot.CountPolys(); };
	void			CountDepth			(int& maxDepth, int& minDepth, int& avgDepth) {	bspRoot.CountDepth (maxDepth, minDepth, avgDepth); };
	void			SetBspTreeMode		(const zTBspTreeMode& bspMode);
	zTBspTreeMode	GetBspTreeMode		() const						{ return bspTreeMode; };

	// Bsp-Sectors
	void			CreateBspSectors	();
	zCBspSector*	GetBspSectorByName	(const zSTRING& name) const;
	void			GetPolyNeighbours	(zCPolygon *poly, zCPolygon**& foundPolyList, int& foundPolyNum);
};

///////////////////////////////////////////////////////////////////////////
//     BSP
///////////////////////////////////////////////////////////////////////////

// sectorIndex, used by zCPolygon, zCBspSector, zCBuildPortal
#define zSECTOR_INDEX_UNDEF	(0xFFFF)
#define zSECTOR_INDEX_PORTAL	(zWORD(1<<15))

class zCBspSector {
public:
	zCBspSector () : sectorPortalInfo(0) {
		activated		= rendered = -1;
		hasBigNoFade	= FALSE;
		sectorCenter	= zVEC3(0);
		sectorIndex		= 0;
	};
	const zSTRING&	GetSectorName			()		const			{ return sectorName;	};
	void			SetSectorName			(const zSTRING& name)	{ sectorName=name;		};
	void			CalcCenterByPortals		();
	zBOOL			HasManyBigPortals		() const;		// for lighting (those sectors get special lighting at borders)
	zDWORD			GetSectorIndex			() const { return sectorIndex; };	// this sector's id

private:
	static int						s_sectorsRendered;
	static zBOOL					s_startPointOutdoor;
	static zBOOL					s_outdoorPortal;
	static zCArray<zCBspSector*>	s_activeSectorList;
	static zCArray<zTBBox2D>		s_activeOutdoorPortals;

	static void		SetStartPointOutdoor	(const zBOOL b)	{ s_startPointOutdoor=b; s_activeOutdoorPortals.EmptyList(); s_sectorsRendered=0; ClearActiveSectorList(); };	// must be set before any calls to Activate() or Render()
	static zBOOL	GetStartPointOutdoor	()				{ return s_startPointOutdoor; };
	static zBOOL	IsOutdoorActive			()				{ return s_activeOutdoorPortals.GetNumInList()>0; };
	static void		AddOutdoorPortal		(zTBBox2D& portalBox) {	s_activeOutdoorPortals.Insert (portalBox); };
	static void		InitHorizonByOutdoorPortals(); 
	static void		RenderActiveSectorList	();
	static void		ClearActiveSectorList	()	{ s_activeSectorList.EmptyList(); };

private:
	void			ActivateSectorRec		(const zTBBox2D& cullBox2D, zCBspSector* lastSector=0, int depth=0);
	void			ActivateSectorRecIndoor (const zTBBox2D& cullBox2D, zCBspSector* lastSector=0, int depth=0);
	void			RenderSector			();
	zBOOL			IsRendered				() const;
	void			Rendered				();
	zBOOL			IsActivated				() const;
	void			Activate				();
	zBOOL ShouldActivatePortal	(zCPolygon *portal) 
	{ 
#ifdef COMPILING_SPACER
		if (zCBspTree::S_GetRenderAllPortals()) return TRUE;
#endif
		zREAL		DIST_MAX2;
		zREAL		DIST_MIN2;
		zREAL		SCALE;
		zPOINT3		pos;

//portal->SetPortalType (zCPolygon::zPORTAL_TYPE_BIG);
		const zCPolygon::zTPortalType mode = portal->GetPortalType();
		if (mode==zCPolygon::zPORTAL_TYPE_SMALL)
		{
			// kleine Portale
			const zREAL	_DIST_MAX	= 1800;		// 2000
			const zREAL	_DIST_MIN	= 1200;		// 1000
			const zREAL	_DIST_MAX2	= _DIST_MAX*_DIST_MAX;
			const zREAL	_DIST_MIN2	= _DIST_MIN*_DIST_MIN;
			const zREAL	_SCALE		=  zREAL(1.0F) / (_DIST_MAX2-_DIST_MIN2) * zREAL(255.0F);
			DIST_MAX2	= _DIST_MAX2;
			DIST_MIN2	= _DIST_MIN2;
			SCALE		= _SCALE;
			pos			= portal->GetVertexPtr(0)->position;

		} else 
		if (mode==zCPolygon::zPORTAL_TYPE_BIG)
		{
			// grosse Portale
			const zREAL	_DIST_MAX	= 5500;		// 2000
			const zREAL	_DIST_MIN	= 4000;		// 1000
			const zREAL	_DIST_MAX2	= _DIST_MAX*_DIST_MAX;
			const zREAL	_DIST_MIN2	= _DIST_MIN*_DIST_MIN;
			const zREAL	_SCALE		=  zREAL(1.0F) / (_DIST_MAX2-_DIST_MIN2) * zREAL(255.0F);
			DIST_MAX2	= _DIST_MAX2;
			DIST_MIN2	= _DIST_MIN2;
			SCALE		= _SCALE;
			pos			= (portal->GetVertexPtr(0)->position + portal->GetVertexPtr(2)->position) * 0.5F;
			//pos[VY]		= zCCamera::activeCamPos[VY];
		}
		else
		{
			// grosse 'NoFade' Portale
			const zREAL	_DIST_MAX	= 4000;		// 2000
			const zREAL	_DIST_MIN	= 3000;		// 1000
			const zREAL	_DIST_MAX2	= _DIST_MAX*_DIST_MAX;
			const zREAL	_DIST_MIN2	= _DIST_MIN*_DIST_MIN;
			const zREAL	_SCALE		=  zREAL(1.0F) / (_DIST_MAX2-_DIST_MIN2) * zREAL(255.0F);
			DIST_MAX2	= _DIST_MAX2;
			DIST_MIN2	= _DIST_MIN2;
			SCALE		= _SCALE;
			pos			= portal->GetVertexPtr(0)->position;

			// Distanz
			portal->GetMaterial()->SetAlpha (255);
			zREAL dist2 = (pos-zCCamera::activeCamPos).Length2();
			return (dist2<=DIST_MAX2);
		};

		// Distanz
		zREAL dist2 = (pos - zCCamera::activeCamPos).Length2();
		if (dist2>DIST_MAX2) {
			portal->GetMaterial()->SetAlpha (255);
			return FALSE; 
		};

		// ok
		int alpha;
		if (dist2<DIST_MIN2)	alpha = 0;
		else					alpha = zFloat2Int((dist2-DIST_MIN2) * SCALE);
		portal->GetMaterial()->SetAlpha (alpha);

		return TRUE;
	};

	friend class zCBspTree;
	friend class zCBspBase;
	friend class zCBspNode;
	friend class zCBspLeaf;
public:
	struct zTPortalInfo {
		zBYTE		visible;
		zBYTE		alpha;
	};

	zSTRING							sectorName;
	zCArray<zCBspBase*>				sectorNodes;
	zDWORD							sectorIndex;		// in sectorList (INDOOR)
	zCArray<zCPolygon*>				sectorPortals;
	zCArray<zTPortalInfo>			sectorPortalInfo;	// has correct value after first 'ActivateSectorRec' on this sector
	zTFrameCtr						activated;
	zTFrameCtr						rendered;
	zTBBox2D						activePortal;
	zVEC3							sectorCenter;		// only for construction phase
	zBOOL8							hasBigNoFade;		// only for construction phase
private:
	static int CompareOutdoorPortalBBox2D ( const void *arg1, const void *arg2 );
};


inline zBOOL zCBspSector::IsRendered() const	{ 
	return rendered == bspFrameCtr;	
};

inline void zCBspSector::Rendered() { 
	rendered =  bspFrameCtr;			
};

inline zBOOL zCBspSector::IsActivated() const	{ 
	return activated== bspFrameCtr;	
};

inline void zCBspSector::Activate() 
{ 
	activated = bspFrameCtr;			
	s_activeSectorList.Insert (this);  
	// FIXME: hier ??
	if (sectorPortalInfo.GetNum()!=sectorPortals.GetNum()) {
		sectorPortalInfo.AllocAbs		(sectorPortals.GetNum());
		sectorPortalInfo.MarkNumAllocUsed();
		// alle Element auf FALSE=invisible setzen
		memset (sectorPortalInfo.GetArray(), 0, sizeof(sectorPortalInfo[0])*sectorPortalInfo.GetNum());  
	};
};


// =====================================================================================================================

// A Portal that is used merely within the construction phase of a BSP (indoor)

class zCBuildPortal {
public:
	static zCArray<zCBuildPortal*>	s_buildPortalList;
	 zCBuildPortal();
	~zCBuildPortal();

	zCPolygon*	GetPortalPoly		() const			{ return portalPoly;	};
	void		SetPortalPoly		(zCPolygon *poly)	{ portalPoly=poly;		};
	zCPolygon*	GetPortalPolyBack	() const			{ return portalPolyBack;};
	void		SetPortalPolyBack	(zCPolygon *poly)	{ portalPolyBack=poly;	};
private:
	zCPolygon				*portalPoly;		// original portal poly
	zCPolygon				*portalPolyBack;	// direction flipped copy 
	zCArray<zCPolygon*>		borderPolyList;
	zCArray<zCPolygon*>		polyBucket	[2];	// front, back		FRONT = direction the original portalPoly points to
	zCArray<zCBuildPortal*>	portalBucket[2];	// front, back; portals encountered
	zCBspSector				*sector		[2];	// front, back

	friend zCBspTree;
};


// =====================================================================================================================

#endif
