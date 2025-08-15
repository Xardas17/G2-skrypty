/******************************************************************************** 
 
     $Workfile:: znetmessage.cpp      $                $Date:: 6.09.00 18:22    $
     $Revision:: 10                   $             $Modtime:: 6.09.00 17:39    $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/znetmessage.cpp $
 * 
 * 10    6.09.00 18:22 Speckels
 * 
 * 9     28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 7     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 6     10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 5     21.07.00 15:16 Speckels
 * 
 * 4     21.07.00 12:56 Speckels
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:24 Speckels
 * 
 * 7     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 6     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 5     4.12.99 20:49 Speckels
 * more implementation of the central networkmanager
 * 
 * 4     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 3     21.10.99 23:29 Speckels
 * Work on error-handling and
 * item-interaction
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 10 $ ($Modtime: 6.09.00 17:39 $)



#include "znet.h"
#include "znetmessage.h"
#include "zdisk.h"
#include "zoption.h"
#include "zbuffer.h"

#ifndef zNET_ANAYSE_BYTEFREQ
	#define zNET_ANAYSE_BYTEFREQ
#endif

/*--- Message ------------------------------------------------------------------*/

/// constructor
zCNetMessage::zCNetMessage(zTNetMessageHeader& header)
{	
	Init();

	zBYTE spacelen = sizeof(zWORD) * 10;	
		
	buffer = zNEW(zCBuffer(header.datasize+GetHeaderSize()+spacelen));
	buffer->SetMode(READWRITE);
	buffer->Write(&header,GetHeaderSize());	
	
	isStream = FALSE;
}	

/// constructor for packets to be sent
zCNetMessage::zCNetMessage(const zTNetMessageID& _id, zUDWORD len)
{	
	Init();

	zBYTE spacelen	= sizeof(zWORD) * 10;
	zBYTE headerlen	= GetHeaderSize();

	zTNetMessageHeader header;
		header.datasize		= 0; // will be set in method "Send"		
		header.id			= _id;
		header.senderID		= 0;
		if (zCPlayerInfo::GetActivePlayer()) header.senderID = zCPlayerInfo::GetActivePlayer()->GetID();
		header.timestamp	= 0;
		header.flags		= zNET_MSGFLAG_LOG;		

	buffer = zNEW(zCBuffer(len+headerlen+spacelen));
	buffer->SetMode(READWRITE);
	buffer->Write(&header,sizeof(header));	

	isStream = FALSE;
}			

void zCNetMessage::CopyFrom(zCNetMessage* msg)
{	
	buffer->Write(msg->GetDataPtr(),msg->GetDataSize());
	buffer->SetMode(READWRITE);	
	
	isStream				= msg->IsStream();
	targetGroup = 0;
	targetPlayer= 0;
};

/// constructor for received packets (unreliable messages)
zCNetMessage::zCNetMessage(zTNetPacketPtr _packet)
{		
	Init();

	zCNetSession* session = znet->GetSessionData();
	if (!session)
	{
		zERR_FAULT("B: (zCNetMessage) No session-data available!");
		return;
	};

	zUDWORD len = _packet->size;
	
	buffer = zNEW(zCBuffer(len));
	buffer->SetMode(READWRITE);
	buffer->Write(&_packet->Data, len);	
	ResetCursorPtr();
	
	isStream = FALSE;
}

void zCNetMessage::Init()
{
	buffer			= NULL;	
	file			= NULL;
	remote_file		= NULL;	
	targetPlayer	= NULL;
	targetGroup		= NULL;
	isStream		= FALSE;	
};

// destructor
zCNetMessage::~zCNetMessage()
{	
	delete buffer;
	buffer			= NULL;
	targetPlayer	= NULL;
	targetGroup		= NULL;	

	if (file && file->IsOpened()) file->Close();
	delete file; 
	file=NULL;

	if (remote_file && remote_file->IsOpened()) remote_file->Close();
	delete remote_file;
	remote_file=NULL;
}

void zCNetMessage::Send()
{	
	#ifdef zNET_ANAYSE_BYTEFREQ
		buffer->ByteFreq_Analyse();
	#endif

	if (HasError()) 
	{
		zERR_WARNING("B: (zCNetMessage::Send) Message is illegal. Did not sent it!");
		return;
	}
	// file-Message? Dann als Stream (TCP/SPX) schicken
	if (file) SetStream();	
		
	GetHeader()->datasize = GetDataSize();
	
	znet->MsgPut(this);	
};


void  zCNetMessage::SetTimestamp(zTNetMsgTimestamp ts)
{ 
	GetHeader()->timestamp = ts; 
};

zTNetMsgTimestamp zCNetMessage::GetTimestamp() 
{ 	
	return GetHeader()->timestamp; 	
};

void zCNetMessage::SetTarget(zCPlayerInfo* _player)
{ 	
	GetHeader()->flags = GetHeader()->flags & !zNET_MSGFLAG_MULTIMSG;
	targetPlayer = _player;
}	


void zCNetMessage::SetTarget(zCPlayerGroup* _group)
{ 	
	GetHeader()->flags = GetHeader()->flags | zNET_MSGFLAG_MULTIMSG;
	targetGroup  = _group;		
}	


void zCNetMessage::GetTarget(zCPlayerInfoPtr& _player, zCPlayerGroupPtr& _group)
{ 
	_player	= targetPlayer;
	_group	= targetGroup;
}

//
// Reading data from the message
//

zUDWORD zCNetMessage::Get(void* data, const zUDWORD& len)
{		
	zUDWORD dolen = len;		
	if (len>buffer->GetRestSize()) 
	{ 
		dolen=buffer->GetRestSize(); 
		zERR_WARNING("B: (zCNetMessage::Get) Requested data is bigger than message");
	}	
	buffer->Read(data,dolen);				
	return dolen;
}


//
// Writing data to the message
//

void zCNetMessage::Add(void* data, zUDWORD len)
{	
	if (len>buffer->GetRestSize()) { len=buffer->GetRestSize(); zERR_WARNING("B: (zCNetMessage::Add) Data is too long for message");}
	if (len<=0) return;
	
	if (data) 
	{		
		buffer->Write(data,len);		
	}
}

void zCNetMessage::AddCursorPtr(zUDWORD len)
{
	buffer->SetPosRel(len);
}

void zCNetMessage::Add(const zSTRING& str)
{		
	buffer->WriteString(str);
}

void zCNetMessage::Get(zSTRING& str)
{		
	str = buffer->ReadString();
}

zBOOL zCNetMessage::IsStream()
{
	return isStream;
}

void zCNetMessage::SetStream(zBOOL stream)
{
	isStream = stream;
}


void zCNetMessage::SetFileMessage(zFILE* _file, zFILE* _remote_file)
{	
	// Gibt es schon ein File? Dann ueberschreibe dieses durch das hier uebergebene...
	if (file)
	{
		if (file->IsOpened()) file->Close();
		delete file; file=0;
	}	
	// ebenso beim remote-file
	if (remote_file) 
	{ 
		delete remote_file; remote_file=0; 
	}
	
	if (!_file)
	// kein File
	{
		GetHeader()->flags = GetHeader()->flags & !zNET_MSGFLAG_FILE;
	}
	else
	// file anhaengen
	{	
		GetHeader()->flags = GetHeader()->flags | zNET_MSGFLAG_FILE;
		remote_file = _remote_file;
		file = _file;
	}
};


zFILE* zCNetMessage::GetFile(zFILE*& filepath)
{
	if (!IsFileMessage()) { filepath=0;return 0;}
	filepath = remote_file;
	return file;
};

////////////////////////////////////////////////////////////////
// Flags
////////////////////////////////////////////////////////////////


zBOOL zCNetMessage::IsFileMessage()
{	
	return ((GetHeader()->flags & zNET_MSGFLAG_FILE) == zNET_MSGFLAG_FILE);
};

zBOOL zCNetMessage::IsMultiMessage()
{	
	return ((GetHeader()->flags & zNET_MSGFLAG_MULTIMSG) == zNET_MSGFLAG_MULTIMSG);
};

void zCNetMessage::LogMessage(zFILE* file, const zSTRING& str)
{
	if ((GetHeader()->flags & zNET_MSGFLAG_LOG)==0) return;	

	zSTRING line(str);

	if (IsStream()) line+="<STREAM> "; else line+="<DGRAM>  ";
	line += " "+zSTRING(GetID()).Align(zSTR_RIGHT,6,' ');	// message-id
	line += " from "+zSTRING(GetSenderID()).Align(zSTR_RIGHT,3,' ');
	line += " ("+zSTRING(GetSize()).Align(zSTR_RIGHT,5,'0')+" bytes)";	
	line += "\n";

	file->Write(line);
};



////////////////////////////////////////////////////////////////



void zCNetMessage::SetLog(zBOOL log)
{
	#ifdef _DEBUG
		if (log) GetHeader()->flags = GetHeader()->flags | zNET_MSGFLAG_LOG;
		else GetHeader()->flags = GetHeader()->flags & ~zNET_MSGFLAG_LOG;
	#endif
};


zTNetMessageHeader* zCNetMessage::GetHeader()
{ 
	zERR_ASSERTT( GetSize()>=GetHeaderSize(), "B: (zCNetMessage::GetHeader) Not enough space for the message-header.");

	return (zTNetMessageHeader*)buffer->GetBuffer(); 
};

zBYTE zCNetMessage::GetHeaderSize()
{
	return sizeof(zTNetMessageHeader);
};

/// retrieve buffer with complete datablock
zCBuffer* zCNetMessage::GetBuffer()
{ 
	return buffer; 
};

/// retrieve pointer to next data to be read or written
zBYTE* zCNetMessage::GetCursorPtr()
{ 
	return buffer->GetCursor(); 
}

/// retrieve pointer to next data to be read or written
zBYTE* zCNetMessage::GetPtr()
{ 
	return buffer->GetBuffer();
}

/// retrieve pointer to begin of user-defined data
zBYTE* zCNetMessage::GetDataPtr()			
{ 
	return (zBYTE*)( buffer->GetBuffer() + GetHeaderSize()); 
}


/// set pointer the start of user-defined data
void zCNetMessage::ResetCursorPtr()
{ 
	buffer->SetPos(GetHeaderSize()); 
}

/// set mode of the internal buffer (READ, WRITE or both)
void zCNetMessage::SetMode(zTBufferMode mode)
{ 
	buffer->SetMode(mode); 
};

/// Size of complete message.
zUDWORD	zCNetMessage::GetSize()
{ 
	return buffer->GetSize(); 
}

/// Size of user-defined data-block.
zUDWORD	zCNetMessage::GetDataSize()	
{ 
	return GetSize()-GetHeaderSize(); 
}

/// Retrieve rest of the maximum size available for read- or write-operations.
zUDWORD	zCNetMessage::GetRestSize()
{ 
	return buffer->GetRestSize(); 
}


/// Get the identifier of the network-message.
zTNetMessageID	zCNetMessage::GetID()
{ 
	return GetHeader()->id; 
}

/// Retrieve the senders id.
zTNetSenderID zCNetMessage::GetSenderID()	
{ 
	return GetHeader()->senderID; 
};

/// Get the flags of this message.
zBYTE zCNetMessage::GetFlags()
{ 
	return GetHeader()->flags; 
};


/// check if there was an error while creating the message
bool zCNetMessage::HasError() const			
{ 
	return buffer->HasError();	
};



