/******************************************************************************** 
 
     $Workfile:: zbuffer.h            $                 $Date:: 4.12.00 18:22    $
     $Revision:: 9                    $             $Modtime:: 4.12.00 18:19    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description::

	This buffer handles a block of data. On usinfg the 
	allocate-constructor (see below) the memory-block will be
	allocated. But you already have a block of data then use the 
	buffer-constructor which takes the pointer to this block and
	the size of it. On destruction sucha an external buffer will 
	not be deallocated.

	Writing and reading data will be done from the current position 
	of the buffers CURSOR-pointer. You could retrieve this pointer by 
	zCBuffer::GetCursor. zCBuffer::GetPos gives you the position of the
	cursor relative to the buffers beginning. zCBuffer::SetPos will move
	the cursor to another position. zCBuffer::SetPosRel is the relative
	companion of SetPos and returns the new position.

	A buffer has a MAXIMUM SIZE (specified on construction). You
	can't WRITE over this maximum size. 

	The amount of data (in bytes) stored in the buffer is named 
	the SIZE pf the buffer (GetSize). You can't READ or SETPOS(REL) 
	over this size. If you want to know how many bytes are left 
	in the buffer use zCBuffer::GetRestSize.

	If the size of the buffer does not fit your needs you could resize
	it with zCBuffer::Resize. This could be done at any time: The 
	cursors position will not be changes until the new size is large
	enough. So feel free to do this:

	zCBuffer buffer(100);
	buffer.WriteReal(1234.123456789F);
	buffer.Resize(50);
	buffer.WriteInt(1111);

 
 * $Log: /current_work/ZenGin/_Bert/zbuffer.h $
 * 
 * 9     4.12.00 18:22 Moos
 * 
 * 8     3.11.00 15:03 Speckels
 * 
 * 7     28.08.00 15:15 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 5     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 4     10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:25 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:23 Speckels
 * 
 * 8     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 7     19.01.00 1:10 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 5     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 4     21.10.99 23:24 Speckels
 * Bitwise-Packing implemented
 * 
 * 3     25.09.99 18:11 Speckels
 * 
 * 2     24.09.99 20:40 Speckels
 * VSS-kompatiblen Header eingefügt
 * 
 * 
 *********************************************************************************/



#ifndef __ZBUFFER_H__
#define __ZBUFFER_H__

#ifndef __ZTYPES_H__
#include "ztypes.h"
#endif

#ifndef __ZSTRING_H__
#include "zstring.h"
#endif

#ifndef _INC_MENORY
#include "memory.h"
#endif

enum zTBufferMode { READ, WRITE, READWRITE };

#define zCONVERT_BIT2BYTE(i) ( (int) (((i)+7) / 8) )
#define zIS_BYTESIZE(i)		 ( ((i)%8)==0)

class zCObject;

class zCBuffer
{

public:
		
	zCBuffer();
	zCBuffer(const zDWORD& len);			/// allocation-constructor: allocate buffer with specified size (allocted=true)	
	zCBuffer(void* b, const zDWORD& len);	/// buffer-constructor: use previouly allocated buffer with specified size (allocted=false)
	zCBuffer(const zCBuffer& b);			/// copy-constructor

	zCBuffer& operator=(const zCBuffer& b);		/// Assignment
		
	virtual ~zCBuffer();					/// destructor: deallocate only if allocated==true
	
	zTBufferMode SetMode(zTBufferMode newmode);	/// set read or write-mode
	
	zDWORD Write		(const void* b, const zDWORD len_byte);		/// write len bytes from buffer b into this buffer
	zDWORD WriteBits	(const void* b, const zDWORD len_bit);		/// write len bytes from buffer b into this buffer (bits)
	
	zDWORD Read			(void* b, const zDWORD len_byte);		/// read len bytes from this buffer to buffer b
	zDWORD ReadBits		(void* b, const zDWORD len_bit);		/// read len bytes from this buffer to buffer b (bits)

	// Writing special types
	zDWORD WriteBool			(const zBOOL value,		int bits=sizeof(zBOOL)	* 8 );		
	zDWORD WriteByte			(const zBYTE value,		int bits=sizeof(zBYTE)	* 8 );
	zDWORD WriteWord			(const zWORD value,		int bits=sizeof(zWORD)	* 8 );
	zDWORD WriteDWord			(const zDWORD value,	int bits=sizeof(zDWORD)	* 8 );
	zDWORD WriteReal			(const zREAL value,		int bits=sizeof(zREAL)	* 8 );	
	zDWORD WriteInt				(const int value,		int bits=sizeof(int)	* 8 );
	zDWORD WriteFloat			(const float value,		int bits=sizeof(float)	* 8 );
	zDWORD WriteFloatPacked0_16	(const float value);
	zDWORD WriteFloatPacked0_8	(const float value);
	zDWORD WriteFloatPacked8_8	(const float value);
	zDWORD WriteString			(const zSTRING value);	
	zDWORD WriteObject			(zCObject*& obj);	

	// fill the rest of the current byte with 0
	void   CompleteByte			();

	// Reading special types
	zBOOL	ReadBool			(int bits = sizeof(zBOOL)	* 8 );
	zBYTE	ReadByte			(int bits = sizeof(zBYTE)	* 8 );
	zWORD	ReadWord			(int bits = sizeof(zWORD)	* 8 );
	zDWORD	ReadDWord			(int bits = sizeof(zDWORD)	* 8 );
	zREAL	ReadReal			(int bits = sizeof(zREAL)	* 8 );	
	int		ReadInt				(int bits = sizeof(int)		* 8 );
	float	ReadFloat			(int bits = sizeof(float)	* 8 );
	float	ReadFloatPacked0_16	();
	float	ReadFloatPacked0_8	();
	float	ReadFloatPacked8_8	();
	zSTRING	ReadString			();	
	zDWORD	ReadObject			(zCObject*& obj);

	/// move the cursor to the next byte-mark	
	void	SkipByte			();
		
	zDWORD	GetMaxSize()	const;		/// get the maximum size of buffer (you cant write more than this)
	zDWORD	GetBitMaxSize()	const;		/// get the maximum size of buffer (you cant write more than this) (bits)		
	zDWORD	GetSize()		const;		/// get the current size of data in the buffer (you can't read more than this)
	zDWORD	GetBitSize()	const;		/// get the current size of data in the buffer (you can't read more than this) (bits)
	int		GetBitSizeToNextByte()	const;		
	zDWORD	GetRestSize()	const;		/// get the remaining amount of bytes in the buffer (left space to write into)
	zDWORD	GetBitRestSize()const;		/// get the remaining amount of bytes in the buffer (left space to write into) (bits)
	zDWORD	GetPos()		const;	/// get the current position of the cursor
	zDWORD	GetBitPos()		const;	/// get the current position of the cursor (bits)
	zBYTE*	GetBuffer()		const;	/// get a pointer to the buffer
	zBYTE*	GetCursor()		const;	/// get a pointer to the current position of the cursor
			
	void	Resize(zDWORD newsize);			/// resize buffer to new size
	void	Reset();
		
	void	SetPosBegin();							/// move the cursor to the beginngin of the buffer
	void	SetPosEnd();							/// move the cursor to the end of the data
	void	SetPos(const zDWORD& newpos_byte);		/// move the cursor to a new position
	void	SetBitPos(const zDWORD& newpos_bit);	/// move the cursor to a new position (bits)	
	zDWORD	SetPosRel(const int relmove_byte);		/// move the cursor relative from the current position
	zDWORD	SetBitPosRel(const int relmove_bit);	/// move the cursor relative from the current position (bits)
		
	bool	HasError()		const;	/// get a pointer to the current position of the cursor

	friend int operator==(const zCBuffer& b1, const zCBuffer& b2);	

	// Analyse and Debugging-Tools
	void			ByteFreq_Analyse();
	static void		ByteFreq_Reset();
	static void		ByteFreq_Print();

protected:
	
	void CopyFrom(const zCBuffer& b);

	void Init();		// initializing class-members

	zTBufferMode	mode;

	/// pointer to streamof data
	zBYTE*			buffer;	

	/// current byte-position
	zDWORD			pos_byte;
	zDWORD			pos_bit;

	// maximum size
	zDWORD			maxsize_byte;
	zDWORD			maxsize_bit;

	// current size of data available
	zDWORD			size_byte;
	zDWORD			size_bit;	

	zBYTE			vobNr;
	bool			allocated;	
	bool			bits_written;	
	bool			buffer_error;

};



#endif