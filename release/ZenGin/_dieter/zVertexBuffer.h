/******************************************************************************** 
 
     $Workfile:: zVertexBuffer.h      $                $Date:: 5.02.01 19:13    $
     $Revision:: 10                   $             $Modtime:: 5.02.01 1:57     $
       $Author:: Hildebrandt                                                    $
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Vertex Buffer
   created: 25.5.2000

 * $Log: /current_work/zengin_work/_Dieter/zVertexBuffer.h $
 * 
 * 10    5.02.01 19:13 Hildebrandt
 * 
 * 9     26.01.01 0:43 Hildebrandt
 * 
 * 8     8.01.01 17:56 Hildebrandt
 * 
 * 7     4.12.00 17:38 Hildebrandt
 * 
 * 6     11.10.00 19:45 Hildebrandt
 * 
 * 5     22.09.00 19:18 Hildebrandt
 * 
 * 4     21.09.00 18:03 Hildebrandt
 * 
 * 3     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 4     9.08.00 17:12 Admin
 * 
 * 2     3.07.00 12:44 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revisio: 2 $ ($Modtime: 5.02.01 1:57 $)

// =======================================================================================================================

#ifndef __ZVERTEXBUFFER_H__
#define __ZVERTEXBUFFER_H__

#ifndef __ZTYPES3D_H__
#include <zTypes3D.h>
#endif

#ifndef __ZCONTAINER_H__
#include <zContainer.h>
#endif

// =======================================================================================================================

class zCVertexBuffer;
class zCVertexBufferDyn;
class zCVertexBufferDyn2;
class zCVertexBufferManager;

// =======================================================================================================================

enum zTVBufferPrimitiveType
{
    zVBUFFER_PT_TRIANGLELIST			= 0, 
    zVBUFFER_PT_TRIANGLESTRIP			, 
    zVBUFFER_PT_TRIANGLEFAN				,
    zVBUFFER_PT_POINTLIST				, 
    zVBUFFER_PT_LINELIST				, 
    zVBUFFER_PT_LINESTRIP		 
};

enum zTVBufferCreateFlags
{
	zVBUFFER_CREATE_FLAG_DONOTCLIP		= 1,
	zVBUFFER_CREATE_FLAG_OPTIMIZED		= 2,
	zVBUFFER_CREATE_FLAG_SYSTEMMEMORY	= 4,
	zVBUFFER_CREATE_FLAG_WRITEONLY		= 8
};

enum zTVBufferLockFlags
{
	zVBUFFER_LOCK_FLAG_READONLY			= 1,	// Indicates that the memory being locked is only to be read from. 
	zVBUFFER_LOCK_FLAG_SURFACEMEMORYPTR	= 2,	// Indicates that a valid memory pointer to the vertex buffer is returned; this is the default. 
	zVBUFFER_LOCK_FLAG_WAIT				= 4,	// If a lock cannot be obtained immediately, the method retries until a lock is obtained or another error occurs.
	zVBUFFER_LOCK_FLAG_WRITEONLY		= 8,	// Indicates that the memory being locked is only to be written to. 
	zVBUFFER_LOCK_FLAG_DISCARDCONTENTS	= 16,	// New for DirectX 7.0. Used only with Direct3D vertex-buffer locks. Indicates that no assumptions are made about the contents of the vertex buffer during this lock. This enables Direct3D or the driver to provide an alternative memory area as the vertex buffer. This is useful when you plan to clear the contents of the vertex buffer and fill in new data. 
	zVBUFFER_LOCK_FLAG_NOOVERWRITE		= 32,	// New for DirectX 7.0. Used only with Direct3D vertex-buffer locks. Indicates that no vertices that were referred to in vertex-buffer DrawPrimitive calls since the start of the frame (or the last lock without this flag) are modified during the lock. This can be useful when you want only to append data to the vertex buffer. 
	zVBUFFER_LOCK_FLAG_NOSYSLOCK		= 64,	// If possible, do not take the Win16Mutex (also known as Win16Lock)
};

enum zTVBufferVertexFormat
{
	zVBUFFER_VERTFORMAT_XYZ				= 1,	// 3 floats, Vertex format includes the position of an untransformed vertex. This flag cannot be used with the D3DFVF_XYZRHW flag. If you use this flag, you must also specify a vertex normal, a vertex color component (D3DFVF_DIFFUSE or D3DFVF_SPECULAR), or include at least one set of texture coordinates (D3DFVF_TEX1 through D3DFVF_TEX8).
	zVBUFFER_VERTFORMAT_XYZRHW			= 2,	// 4 floats, Vertex format includes the position of a transformed vertex. This flag cannot be used with the D3DFVF_XYZ or D3DFVF_NORMAL flags. If you use this flag, you must also specify a vertex color component (D3DFVF_DIFFUSE or D3DFVF_SPECULAR) or include at least one set of texture coordinates (D3DFVF_TEX1 through D3DFVF_TEX8).
	zVBUFFER_VERTFORMAT_NORMAL			= 4,	// 3 floats, Vertex format includes a vertex normal vector. This flag cannot be used with the D3DFVF_XYZRHW flag.
	zVBUFFER_VERTFORMAT_COLOR			= 8,	// 1 dword,  Vertex format includes a diffuse color component.
	zVBUFFER_VERTFORMAT_TEXUV1			= 16,	// 2 floats per TexUV Set, Number of texture coordinate sets for this vertex. The actual values for these flags are not sequential.
	zVBUFFER_VERTFORMAT_TEXUV2			= 32,	// "
	zVBUFFER_VERTFORMAT_TEXUV3			= 64,	// "
	zVBUFFER_VERTFORMAT_TEXUV4			= 128	// "
};												
												
enum zTVBufferVertexType								
{												
	zVBUFFER_VERTTYPE_UT_UL				= 0,	// untransformed, unlit		(must have normal)
	zVBUFFER_VERTTYPE_UT_L				,		// untransformed, lit		
	zVBUFFER_VERTTYPE_T_L						// transformed, lit			(must have XZYRHW)
};

class zENGINE_API zCVertexBuffer : public zCObject {
	zCLASS_DECLARATION (zCVertexBuffer)
public:
	zCVertexBuffer();

	//
	virtual zBOOL				Create					(zDWORD vertexFormat, zDWORD numVert, zDWORD createFlags) { return FALSE; };
	virtual zBOOL				Destroy					()					{ return FALSE; };

	//
	typedef zBOOL				(*zTRecreateLostVBCallback) (zCVertexBuffer *vertexBuffer, void *data);
	void						AddRecreateLostVBCallback	(zTRecreateLostVBCallback callbackFunc, void *data);
	void						RemoveRecreateLostVBCallback(zTRecreateLostVBCallback callbackFunc, void *data);
	zBOOL						CallRecreateLostVBCallbacks();

	//									
	virtual zBOOL				Lock					(zDWORD lockFlags)  { return FALSE; };
	virtual zBOOL				Unlock					()					{ return FALSE; };
	virtual zBOOL				IsLocked				()					{ return FALSE; };
	virtual zBOOL				Optimize				()					{ return FALSE; };					// no Lock possible afterwards
								
	// Primitive Type							
	virtual zBOOL				SetPrimitiveType		(zTVBufferPrimitiveType primType)  { return FALSE;			};
	virtual zTVBufferPrimitiveType GetPrimitiveType		()					{ return zVBUFFER_PT_TRIANGLELIST;		};
																			
	// Vertex Format/Type													
	virtual zDWORD				GetVertexFormat			()					{ return 0;								};	
	virtual zTVBufferVertexType	GetVertexType			()					{ return zVBUFFER_VERTTYPE_UT_UL;		};	
	int							GetNumVert				() const			{ return numVertex;						};
	int							GetNumVertsFilled		() const			{ return numVertsFilled;				};
	zDWORD						GetVertexBufferID		() const			{ return vertexBufferID;				};	// used for sorting objects by vertexBuffer

	// Index List (array of zWORDs), no Lock/Unlock needed for access
	// Only if Index List Size is >0, the vertices are treated/rendered as indexed primitives. 
	// But the Buffer can still be rendered without any indices.
	virtual zBOOL				SetIndexList			(const zCArray<zWORD>& indexList)	{ return FALSE; };
	virtual zBOOL				SetIndexListSize		(zDWORD num)						{ return FALSE; };
	virtual zDWORD				GetIndexListSize		()									{ return 0; };
	virtual zWORD*				GetIndexListPtr			()									{ return 0; };

	// Data Access
	zDWORD						numVertex;				// size of buffer
	zDWORD						arrayStride;			
	// Only valid between Lock() and Unlock() !
	// Array-ptr is 0 if component is not in Vertex Format
	struct {
		zBYTE					*basePtr;
		zPOINT3					*XYZPtr;				// pos in 3-space
		zVEC4					*XYZRHWPtr;				// screenX, screenY, zbuffer depth, rhw(reciprocal homogeneous W)
		zVEC3					*normalPtr;
		zCOLOR					*colorPtr;
		union {
			struct {
				zVEC2			*texUV0Ptr;
				zVEC2			*texUV1Ptr;
				zVEC2			*texUV2Ptr;
				zVEC2			*texUV3Ptr;
			};
			struct {
				zVEC2			*texUVPtr[4];
			};
		};
	} array;
	inline void					SetXYZ		(const zDWORD i, const zPOINT3& arg)	{ zERR_ASSERT (array.XYZPtr);	 *((zPOINT3*)((zBYTE*)array.XYZPtr  + arrayStride*i))	= arg; };
	inline void					SetXYZRHW	(const zDWORD i, const zVEC4&	arg)	{ zERR_ASSERT (array.XYZRHWPtr); *((zVEC4*)((zBYTE*)array.XYZRHWPtr + arrayStride*i))	= arg; };
	inline void					SetNormal	(const zDWORD i, const zVEC3&	arg)	{ zERR_ASSERT (array.normalPtr); *((zVEC3*)((zBYTE*)array.normalPtr + arrayStride*i))	= arg; };
	inline void					SetColor	(const zDWORD i, const zDWORD	arg)	{ zERR_ASSERT (array.colorPtr);	 *((zDWORD*)((zBYTE*)array.colorPtr + arrayStride*i))	= arg; };
	inline void					SetTexUV0	(const zDWORD i, const zVEC2&	arg)	{ zERR_ASSERT (array.texUV0Ptr); *((zVEC2*)((zBYTE*)array.texUV0Ptr + arrayStride*i))	= arg; };
	inline void					SetTexUV1	(const zDWORD i, const zVEC2&	arg)	{ zERR_ASSERT (array.texUV1Ptr); *((zVEC2*)((zBYTE*)array.texUV1Ptr + arrayStride*i))	= arg; };
	inline void					SetTexUV2	(const zDWORD i, const zVEC2&	arg)	{ zERR_ASSERT (array.texUV2Ptr); *((zVEC2*)((zBYTE*)array.texUV2Ptr + arrayStride*i))	= arg; };
	inline void					SetTexUV3	(const zDWORD i, const zVEC2&	arg)	{ zERR_ASSERT (array.texUV3Ptr); *((zVEC2*)((zBYTE*)array.texUV3Ptr + arrayStride*i))	= arg; };
	//
	inline const zPOINT3&		GetXYZ		(const zDWORD i)	{ zERR_ASSERT (array.XYZPtr);	 return *((zPOINT3*)((zBYTE*)array.XYZPtr  + arrayStride*i)); };
	inline const zVEC4&			GetXYZRHW	(const zDWORD i)	{ zERR_ASSERT (array.XYZRHWPtr); return *((zVEC4*)((zBYTE*)array.XYZRHWPtr + arrayStride*i)); };
	inline const zVEC3&			GetNormal	(const zDWORD i)	{ zERR_ASSERT (array.normalPtr); return *((zVEC3*)((zBYTE*)array.normalPtr + arrayStride*i)); };
	inline const zDWORD			GetColor	(const zDWORD i)	{ zERR_ASSERT (array.colorPtr);	 return *((zDWORD*)((zBYTE*)array.colorPtr + arrayStride*i)); };
	inline const zVEC2&			GetTexUV0	(const zDWORD i)	{ zERR_ASSERT (array.texUV0Ptr); return *((zVEC2*)((zBYTE*)array.texUV0Ptr + arrayStride*i)); };
	inline const zVEC2&			GetTexUV1	(const zDWORD i)	{ zERR_ASSERT (array.texUV1Ptr); return *((zVEC2*)((zBYTE*)array.texUV1Ptr + arrayStride*i)); };
	inline const zVEC2&			GetTexUV2	(const zDWORD i)	{ zERR_ASSERT (array.texUV2Ptr); return *((zVEC2*)((zBYTE*)array.texUV2Ptr + arrayStride*i)); };
	inline const zVEC2&			GetTexUV3	(const zDWORD i)	{ zERR_ASSERT (array.texUV3Ptr); return *((zVEC2*)((zBYTE*)array.texUV3Ptr + arrayStride*i)); };

protected:
	virtual ~zCVertexBuffer();		// use Release() instead!

	int							numVertsFilled;					// how many of the existing verts (numVert) are currently filled/used, counting from the first vert; the VBManager pools VBs and fills them from the beginning without holes
	zDWORD						createFlags;					// cached for reCreate when lost

private:
	static zDWORD				s_classCtorCtr;

	struct zTCallbackData {
		zTRecreateLostVBCallback	recreateLostVBCallback;
		void*						recreateLostVBCallbackData;
	};
	zCArray<zTCallbackData>		callbackList;
	zDWORD						vertexBufferID;

	friend zCVertexBufferManager;
};

// =======================================================================================================================

class zCVertexBufferDyn {
public :
	 zCVertexBufferDyn				(const zDWORD vertexFormat, const zDWORD numVert);
	~zCVertexBufferDyn				();
	
	zCVertexBuffer* GetVertexBuffer			() const	{ return vertexBuffer;		};
	void			FlushAtFrameStart		()			{ flush = TRUE;				}; // Use at beginning of frame to force a flush of VB contents on first draw
	void*			Lock					(const zDWORD numVertLocked, zDWORD &startVertIndex);
	void			Unlock					();
	int				GetNumVert				() const	{ return numVert;			};
	int				GetVertexSizeBytes		() const	{ return vertexSizeBytes;	};

private: 
	zCVertexBuffer	*vertexBuffer;
	zDWORD			vertexFormat;
	zDWORD			numVert;
	zDWORD			vertexSizeBytes;
	zDWORD			currentPos;
	zBOOL			locked;
	zBOOL			flush;

	enum LOCK_FLAGS
	{
		LOCKFLAGS_FLUSH  = zVBUFFER_LOCK_FLAG_NOSYSLOCK | zVBUFFER_LOCK_FLAG_WRITEONLY | zVBUFFER_LOCK_FLAG_DISCARDCONTENTS,
		LOCKFLAGS_APPEND = zVBUFFER_LOCK_FLAG_NOSYSLOCK | zVBUFFER_LOCK_FLAG_WRITEONLY | zVBUFFER_LOCK_FLAG_NOOVERWRITE
	};
};

// =======================================================================================================================

// Dynamic VertexBuffer. A max number of verts is reserved within the buffer, the buffer is Locked, repeatedly and only
// the Inlock tells the buffer how much of it has realy been used since the corresponding Lock.

class zCVertexBufferDyn2 {
public:
	 zCVertexBufferDyn2				(const zDWORD vertexFormat, const zDWORD numVert);
	~zCVertexBufferDyn2				();
	
	zCVertexBuffer* GetVertexBuffer			() const	{ return vertexBuffer;		};
	void			FlushAtFrameStart		()			{ flush = TRUE;				}; // Use at beginning of frame to force a flush of VB contents on first draw
	void			ReserveVerts			(const zDWORD numVertsMax);
	void*			Lock					(zDWORD &startVertIndex);
	void			Unlock					(const zDWORD numVertsUsed);
	int				GetNumVert				() const	{ return numVert;			};
	int				GetVertexSizeBytes		() const	{ return vertexSizeBytes;	};

private: 
	zCVertexBuffer	*vertexBuffer;
	zDWORD			vertexFormat;
	zDWORD			numVert;
	zDWORD			vertexSizeBytes;
	zDWORD			currentPos;
	zBOOL			locked;
	zBOOL			flush;

	enum LOCK_FLAGS
	{
		LOCKFLAGS_FLUSH  = zVBUFFER_LOCK_FLAG_NOSYSLOCK | zVBUFFER_LOCK_FLAG_WRITEONLY | zVBUFFER_LOCK_FLAG_DISCARDCONTENTS,
		LOCKFLAGS_APPEND = zVBUFFER_LOCK_FLAG_NOSYSLOCK | zVBUFFER_LOCK_FLAG_WRITEONLY | zVBUFFER_LOCK_FLAG_NOOVERWRITE
	};
};

// =======================================================================================================================

class zCVertexBufferManager {
public:
	zCVertexBufferManager() : changeWorldHintSet(FALSE) {};
	~zCVertexBufferManager();

	zCVertexBuffer*		AcquireVertexBuffer		(zDWORD vertexFormat,			// IN
												 zDWORD numVert, 
												 zDWORD createFlags,			//		zTVBufferCreateFlags
												 zDWORD lockFlags,				//		zTVBufferLockFlags
												 int	&indexVertexStart);		// OUT
	zBOOL				ReleaseVertexBuffer		(zCVertexBuffer* vertexBuffer);

	// close all remaining open VBs and make them render-able
	void				UnlockOpenVertexBuffers	();

	// hints for optimal usage, given by eg zCWorld
	void				StartChangeWorld		();
	void				EndChangeWorld			();

private:
	zCArray<zCVertexBuffer*>	openVBList;
	zCArray<zCVertexBuffer*>	closedVBList;
	zBOOL						changeWorldHintSet;
};

extern zCVertexBufferManager zvertexBufferMan;

// =======================================================================================================================

#endif