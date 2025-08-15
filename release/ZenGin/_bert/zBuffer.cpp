/******************************************************************************** 
 
     $Workfile:: zbuffer.cpp          $                $Date:: 3.11.00 15:03    $
     $Revision:: 14                   $             $Modtime:: 3.11.00 11:57    $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/zbuffer.cpp $
 * 
 * 14    3.11.00 15:03 Speckels
 * 
 * 13    28.08.00 14:24 Speckels
 * 
 * 16    23.08.00 21:47 Admin
 * 
 * 11    23.08.00 18:09 Speckels
 * 
 * 10    22.08.00 12:11 Speckels
 * 
 * 9     21.08.00 21:09 Speckels
 * 
 * 8     21.08.00 20:51 Speckels
 * 
 * 7     21.08.00 18:47 Speckels
 * 
 * 6     21.08.00 18:26 Speckels
 * 
 * 14    16.08.00 12:32 Admin
 * 
 * 5     10.08.00 21:47 Speckels
 * 
 * 13    9.08.00 17:12 Admin
 * 
 * 4     21.07.00 15:16 Speckels
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 4     1.05.00 16:48 Speckels
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
 * 4     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 3     21.10.99 23:24 Speckels
 * Bitwise-Packing implemented
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 14 $ ($Modtime: 3.11.00 11:57 $)


#include "zcore.h"
#include "zbuffer.h"
#include "iostream"
#include "zvob.h"
#include "zarchiver.h"


zCBuffer::zCBuffer()
{
	Init();
};

zCBuffer::zCBuffer(const zDWORD& len_byte)
{	
	Init();

	buffer			= zNEW(zBYTE)[len_byte];
	allocated		= true;	
	memset(buffer,0,len_byte);

	mode			= WRITE;
	
	maxsize_byte	= len_byte;		// maximale Anzahl an Bytes
	maxsize_bit 	= len_byte*8;	// maximale Anzahl an Bytes
};

zCBuffer::zCBuffer(void* b, const zDWORD& len_byte)
{	
	Init();

	buffer			= (zBYTE*)b;
	allocated		= false;
	
	mode			= READ;

	maxsize_byte	= size_byte		= len_byte;
	maxsize_bit		= size_bit		= len_byte*8;	
};

void zCBuffer::Init()
{
	mode			= READWRITE;

	/// pointer to streamof data
	buffer			= NULL;

	/// current byte-position
	pos_byte		= 0;
	pos_bit			= 0;

	// maximum size
	maxsize_byte	= 0;
	maxsize_bit		= 0;

	// current size of data available
	size_byte		= 0;
	size_bit		= 0;	

	vobNr			= 0;
	allocated		= false;
	bits_written	= false;
	buffer_error	= false;
};

zCBuffer::~zCBuffer()
{
	if (allocated) delete[] buffer;
	buffer=NULL;
};

zTBufferMode zCBuffer::SetMode(zTBufferMode newmode)
{ 
	zTBufferMode oldmode = mode;
	mode = newmode;
	return oldmode; 
};

void zCBuffer::Reset()
{
	pos_bit=pos_byte	= 0;
	size_bit=size_byte	= 0;
	bits_written		= 0;		
}

void zCBuffer::Resize(zDWORD newsize_byte)
{
	if (newsize_byte<maxsize_byte) return;

	if (newsize_byte < 32) newsize_byte = 32;	// also 32 byte duerften es am Anfang schon sein!

	#if _DEBUG
	if (mode==READ) { /*zERR_FATAL("B: (zCBuffer::Resize) Can't resize READ-Buffer");*/ return;}	
	#endif
	
	zBYTE* newbuffer = zNEW(zBYTE)[newsize_byte];
	memset(newbuffer,0,newsize_byte);
	if (buffer) memcpy(newbuffer,buffer,size_byte);	
	
	maxsize_byte	= newsize_byte;
	maxsize_bit		= newsize_byte*8;	

	if (buffer) delete[] buffer;
	buffer = newbuffer;
};

/// write len_byte bytes from buffer b into this buffer. Returns num of bytes written.
zDWORD zCBuffer::Write(const void* b, const zDWORD len_byte)
{
	zDWORD bits_written =  WriteBits(b,len_byte*8);
	return zCONVERT_BIT2BYTE(bits_written);
};

/// write len_bit bits from buffer b into this buffer. Returns num of bits written.
zDWORD zCBuffer::WriteBits(const void* b, const zDWORD len_bit)
{
	if (buffer_error) return 0;
	
	zERR_ASSERT(b);
	zERR_ASSERT(mode!=READ);
	if (pos_bit + len_bit > maxsize_bit)
	{		
		zDWORD bit_resize = pos_bit + zDWORD(pos_bit/2);		
		if (bit_resize < len_bit) bit_resize = bit_resize + len_bit;		
		Resize( zCONVERT_BIT2BYTE(bit_resize)+1 );
	}
	
	if ( zIS_BYTESIZE(pos_bit) && zIS_BYTESIZE(len_bit) )
	{
		memcpy(buffer+pos_byte,b,zCONVERT_BIT2BYTE(len_bit));
		pos_bit += len_bit;
	}
	else
	{
		// copy bits
		for (int i=0;i<len_bit;i++,pos_bit++)
		{			
			if ( ((zBYTE*)b)[i/8] & (1<<(i&7)) )	
			{
				buffer[pos_bit/8] |= (1<< (pos_bit&7));
			}
			else 
			{
				buffer[pos_bit/8] &= ~(1<< (pos_bit&7));
			}
		};
	}

	// set position and size
	pos_byte = zCONVERT_BIT2BYTE(pos_bit);
	if (pos_bit>=size_bit) 
	{
		size_bit=pos_bit;	// set new size_byte	
		size_byte=zCONVERT_BIT2BYTE(pos_bit);
	}

	return len_bit;
};

zDWORD zCBuffer::WriteBool(const zBOOL value, int bits)
{
	return WriteBits((void*)&value,bits);
};


zDWORD zCBuffer::WriteByte(const zBYTE value, int bits)
{
	return WriteBits((void*)&value,bits);
};

zDWORD zCBuffer::WriteWord(const zWORD value, int bits)
{
	return WriteBits((void*)&value,bits);
};

zDWORD zCBuffer::WriteDWord(const zDWORD value, int bits)
{
	return WriteBits((void*)&value,bits);
};

zDWORD zCBuffer::WriteReal(const zREAL value, int bits)
{
	return WriteBits((void*)&value,bits);
};

zDWORD zCBuffer::WriteInt(const int value, int bits)
{
	return WriteBits((void*)&value,bits);
};

zDWORD zCBuffer::WriteFloat(const float value, int bits)
{
	return WriteBits((void*)&value,bits);
};

zDWORD zCBuffer::WriteFloatPacked0_16(const float value)
{
	zWORD w = zWORD(value*65535);
	return Write(&w,sizeof(w));
};

zDWORD zCBuffer::WriteFloatPacked0_8(const float value)
{
	zBYTE b = zBYTE(value*255);
	return Write(&b,sizeof(b));
};

zDWORD zCBuffer::WriteFloatPacked8_8(const float value)
{
	float f = value;
	if (f> 127) f = 127; else if (f<-127) f =-127;
	zSWORD w = zSWORD(f*256.0F);
	return Write(&w,sizeof(w));
};


zDWORD zCBuffer::WriteString(const zSTRING value)
{		
	return Write(value.ToChar(),value.Length()+1);
	// return Write(value.ToChar(),value.Length());
};


void zCBuffer::CompleteByte()
{
	int rest_bit = GetBitSizeToNextByte();	
	
	WriteByte(0,rest_bit);
};






//////////////////////////////////////////////////////////////////////
// READING
//////////////////////////////////////////////////////////////////////




/// read len_byte bytes from this buffer to buffer b. Returns amount of bytes read.
zDWORD zCBuffer::Read(void* b, const zDWORD len_byte)
{
	zDWORD bits_read = ReadBits(b,len_byte*8);
	return zCONVERT_BIT2BYTE(bits_read);
};

/// read len_bit bits from this buffer to buffer b. Returns amount of bits read.
zDWORD zCBuffer::ReadBits(void* b, const zDWORD len_bit)
{
	zERR_ASSERT(mode!=WRITE);
	zERR_ASSERTT(pos_bit + len_bit <= size_bit, "B: (zCBuffer::Read) There are only "+zSTRING(size_bit)+" bits of data in this buffer. You tried to read "+zSTRING(pos_bit+len_bit)+" bits.");
	
	if ( zIS_BYTESIZE(pos_bit) && zIS_BYTESIZE(len_bit) )
	{
		memcpy(b,buffer+pos_byte,zCONVERT_BIT2BYTE(len_bit));
		pos_bit += len_bit;
	}
	else
	{
		// copy bits
		for (int i=0; i<len_bit; i++, pos_bit++)
		{
			if ( buffer[pos_bit/8] & (1<<(pos_bit&7)) )
			{
				((zBYTE*)b)[i/8] |= (1<<(i&7));
			}
			else
			{
				((zBYTE*)b)[i/8] &= ~(1<<(i&7));
			};
		};
	}

	// set byte-position
	pos_byte=zCONVERT_BIT2BYTE(pos_bit);

	return len_bit;
};	


zBOOL zCBuffer::ReadBool(int bits)
{	
	zBOOL value=0;
	ReadBits(&value,bits);
	return value;
};


zBYTE zCBuffer::ReadByte(int bits)
{
	zBYTE value=0;
	ReadBits(&value,bits);
	return value;
};


zWORD zCBuffer::ReadWord(int bits)
{
	zWORD value=0;
	ReadBits(&value,bits);
	return value;
};

zDWORD zCBuffer::ReadDWord(int bits)
{
	zWORD value=0;
	ReadBits(&value,bits);
	return value;
};

zREAL zCBuffer::ReadReal(int bits)
{
	zREAL value=0;
	ReadBits(&value,bits);
	return value;
};



int zCBuffer::ReadInt(int bits)
{
	int value=0;
	ReadBits(&value,bits);
	return value;
};


float zCBuffer::ReadFloat(int bits)
{
	float value=0;
	ReadBits(&value,bits);
	return value;
};


float zCBuffer::ReadFloatPacked0_16()
{
	float value=0;
	zWORD w;
	Read(&w,sizeof(w));	
	value = w / 65535.0F;
	return value;
};


float zCBuffer::ReadFloatPacked0_8()
{
	float value=0;
	zBYTE b;
	Read(&b,sizeof(b));
	value = b / 255.0F;
	return value;
};


float zCBuffer::ReadFloatPacked8_8()
{
	float value=0;
	zSWORD w;
	Read(&w,sizeof(w));
	value = w / 256.0F;
	return value;
};



zSTRING zCBuffer::ReadString()
{		
	zSTRING value="";
	char ch;
	do
	{
		ch = (char)ReadByte();
		// if (ch!='\0' && ch!='\n') value+=ch;
		if (ch!='\0') value+=ch;
	// } while (ch!='\0' && ch!='\n');
	} while (ch!='\0');
	
	return value;
};






//////////////////////////////////////////////////////////////////////
// Positions and Sizes
//////////////////////////////////////////////////////////////////////


	
/// move the cursor to a new position (in bytes)
void zCBuffer::SetPos(const zDWORD& newpos_byte)
{		
	SetBitPos(newpos_byte*8);
};

/// move the cursor to a new position (in bits)
void zCBuffer::SetBitPos(const zDWORD& newpos_bit)
{
	zERR_ASSERTT(newpos_bit<=maxsize_bit,"B: (zCBuffer::SetPos) The buffer has a size "+zSTRING(maxsize_bit)+" bits. You tried to set the cursor to bit-position "+zSTRING(newpos_bit));
	zERR_ASSERTT(newpos_bit<=size_bit, "B: (zCBuffer::SetPos) There are only "+zSTRING(size_bit)+" bits of data in this buffer. You tried to set the cursor to bit-position "+zSTRING(newpos_bit));	
	pos_bit  = newpos_bit;
	pos_byte = zCONVERT_BIT2BYTE(pos_bit);
};

/// move the cursor relative from the current position (in bytes)
zDWORD zCBuffer::SetPosRel(const int relmove_byte) 
{ 	
	SetBitPosRel(relmove_byte*8);
	return pos_byte; 
};	

/// move the cursor relative from the current position (in bits)
zDWORD zCBuffer::SetBitPosRel(const int relmove_bit) 
{ 	
	SetBitPos(pos_bit + relmove_bit);
	return pos_bit;
};	


/// move the cursor to the beginngin of the buffer
void zCBuffer::SetPosBegin()
{ 
	SetPos(0); 
};

/// move the cursor to the end of the data
void zCBuffer::SetPosEnd()		
{ 
	SetPos(size_byte); 
};


/// get the current position of the cursor (in bytes)
zDWORD zCBuffer::GetPos() const	
{ 
	zERR_ASSERTT(pos_byte == zCONVERT_BIT2BYTE(pos_bit),"B: (zCBuffer::GetPos) current position is inside a byte.");
	return pos_byte;	
};	

/// get the current position of the cursor (in bits)
zDWORD zCBuffer::GetBitPos()	const
{
	return pos_bit;
};

/// get the maximum size of the buffer (in bytes)
zDWORD zCBuffer::GetMaxSize()	const
{
	return maxsize_byte;
};

/// get the maximum size of the buffer (in bits)
zDWORD zCBuffer::GetBitMaxSize()	const
{
	return maxsize_bit;
};

/// get the current size of data in the buffer in bytes (you can't read more than this)
zDWORD zCBuffer::GetSize()		const
{
	return size_byte;
};

/// get the current size of data in the buffer in bites (you can't read more than this)
zDWORD zCBuffer::GetBitSize()	const
{
	return size_bit;
};

	
/// get the remaining amount of bytes in the buffer (left space to write into)
zDWORD zCBuffer::GetRestSize()	const
{
	return maxsize_byte-pos_byte;
};

/// get the remaining amount of bits in the buffer (left space to write into)
zDWORD zCBuffer::GetBitRestSize()const
{
	return maxsize_bit-pos_bit;
};

/// get a pointer to the buffer (same as SetPosBegin + GetCursor)
zBYTE* zCBuffer::GetBuffer() const
{ 
	return buffer;
};

/// get a pointer to the current position of the cursor (asserts if the current pos is inside a byte)
zBYTE* zCBuffer::GetCursor() const
{ 
	zERR_ASSERTT(pos_byte == zCONVERT_BIT2BYTE(pos_bit),"B: (zCBuffer::GetCursor) current position is inside a byte");
	return buffer+pos_byte;	
};

void zCBuffer::SkipByte()
{
	int rest_bit = GetBitSizeToNextByte();		
	if (rest_bit>0) SetBitPosRel(rest_bit);
};

int zCBuffer::GetBitSizeToNextByte() const
{
	int rest_bit = pos_byte - zCONVERT_BIT2BYTE(pos_bit);
	zERR_ASSERTT(rest_bit>=0,"B: (zCBuffer::SetPosToNextByte) Nagative difference between byte-pos and bit-pos.");
	return rest_bit;
};

/// get a pointer to the current position of the cursor
bool zCBuffer::HasError() const
{
	return buffer_error;	
};

int operator==(const zCBuffer& b1, const zCBuffer& b2)
{
	if (b1.GetBitSize() != b1.GetBitSize()) return b2.GetBitSize() - b1.GetBitSize();
	
	return memcmp(b1.buffer,b2.buffer,b1.GetSize());
};



zDWORD zCBuffer::WriteObject(zCObject*& obj)
{		
	zSTRING objectName = "vob"+zSTRING(++vobNr);

	zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_BINARY, TRUE);
		arch->WriteObject(objectName.ToChar(),obj);

		zCBuffer* buf = arch->GetBuffer();
		zDWORD size = buf->GetSize();
		WriteDWord(size);
		Write(buf->GetBuffer(),size);
		arch->Close();
	zRELEASE(arch);

	return size;
};

zDWORD zCBuffer::ReadObject(zCObject*& obj)
{	
	zSTRING objectName	= "vob"+zSTRING(++vobNr);			
	zDWORD	size		= ReadDWord();
	zCBuffer buf(GetCursor(),size);
	
	zCArchiver* arch = zarcFactory.CreateArchiverRead(&buf);
		obj = arch->ReadObject(objectName.ToChar());
		arch->Close();	
	zRELEASE(arch);

	return size;
};


zCBuffer::zCBuffer(const zCBuffer& b)
{
	Init();

	CopyFrom(b);
};

zCBuffer& zCBuffer::operator=(const zCBuffer& b)
{
	if (this == &b) return *this;

	CopyFrom(b);

	return *this;
};

void zCBuffer::CopyFrom(const zCBuffer& b)
{
	delete buffer;
	buffer			= zNEW(zBYTE)[b.GetSize()];
	allocated		= true;	
	memcpy(buffer,b.GetBuffer(),b.GetSize());

	mode			= b.mode;
	
	maxsize_byte	= b.maxsize_byte;
	maxsize_bit 	= b.maxsize_bit;
	bits_written	= b.bits_written;
	buffer_error	= b.buffer_error;
	pos_bit			= b.pos_bit;
	pos_byte		= b.pos_byte;
	size_bit		= b.size_bit;
	size_byte		= b.size_byte;
	vobNr			= b.vobNr;	
};

static long byteFreqArray[256];

void zCBuffer::ByteFreq_Reset()
{
	for (int i=0;i<256;i++) byteFreqArray[i]=0;
};

void zCBuffer::ByteFreq_Analyse()
{
	for (int i=0;i<GetSize();i++)
	{
		byteFreqArray[buffer[i]]++;
	};
};

void zCBuffer::ByteFreq_Print()
{
	long byteFreqArrayCopy[256];
	memcpy(&byteFreqArrayCopy,&byteFreqArray,sizeof(byteFreqArray));

	zERR_MESSAGE(1,zERR_BEGIN,"B: BUF: Byte-Frequency");
	zSTRING	outputStr;
	zBYTE	colCcunter=0;
	zBYTE	byteIndex;	
	long	max = -1;
	for (int i=0;i<256;i++)
	{

		// Search the biggest:
		byteIndex	= 0;
		max			= -1;
		for (int j=0;j<256;j++)
		{
			if (max <= byteFreqArray[j]) 
			{
				byteIndex = j;
				max = byteFreqArray[byteIndex];
			}
		};
		
		outputStr = outputStr + zSTRING(byteIndex).Align(zSTR_RIGHT,3)+"="+zSTRING(byteFreqArray[byteIndex]).Align(zSTR_LEFT,4)+"  ";
		byteFreqArray[byteIndex] = -1;

		colCcunter++;
		if (colCcunter > 8)
		{
			colCcunter = 0;
			zERR_MESSAGE(1,0,"B: BUF: "+outputStr);
			outputStr.Clear();
		};
	}
	memcpy(&byteFreqArray,&byteFreqArrayCopy,sizeof(byteFreqArray));
};


