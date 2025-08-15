/******************************************************************************** 
 
     $Workfile:: znet.cpp             $                $Date:: 10.10.00 15:47   $
     $Revision:: 12                   $             $Modtime:: 10.10.00 15:16   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/znet.cpp $
 * 
 * 12    10.10.00 15:47 Speckels
 * 
 * 11    6.09.00 18:22 Speckels
 * 
 * 10    28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 8     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 7     10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 6     21.07.00 15:16 Speckels
 * 
 * 5     21.07.00 14:16 Speckels
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
 * 5     30.03.00 14:23 Speckels
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
 * 4     3.12.99 16:09 Speckels
 * 
 * 3     21.10.99 23:29 Speckels
 * Work on error-handling and
 * item-interaction
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 12 $ ($Modtime: 10.10.00 15:16 $)


#include <time.h>

#include "znet.h"
#include "znethost.h"
#include "znetmessage.h"
#include "zoption.h"
#include "zview.h"
#include "zdisk.h"
#include "ztools.h"
#include "zwin32.h"

#include "zplayerinfo.h"
#include "zplayergroup.h"

zCNet* znet = 0;

zNET_HANDLE		handle_stream_listen= 0;		// handle for incoming stream-connections
zNET_HANDLE		handle_dgram_listen = 0;		// handle for incoming datagram-packets
zWORD			stateFlag			= 0;		// flag indicating states of the network
zTNetTimeout	timeout;						// timeout-values

zCNetMessageQueue sendQueue[zNET_MAX_PRIORITY];	// timeout-values
zCNetMessageQueue recvQueue[zNET_MAX_PRIORITY];	// recvQueues (one for each priority)

zBOOL			lockQueues	= FALSE;			// queues are locked: no more items could be put in or retrieved out of them
LPCFUNCP		connectCallback;				// callback for incoming stream-connection
zCNetMessage*	msgPtr;							// global message-pointer

static int sendPacketCounter[zNET_MAX_HOSTID];
static int recvPacketCounter[zNET_MAX_HOSTID];

static zBYTE buffer[zNET_MAX_STREAMSIZE];



// /////////////////////////////////////////////////////////////////////////
// class zCNet: Constructor
// 
// /////////////////////////////////////////////////////////////////////////
zCNet::zCNet(zWORD _protocol)
{		
	session = zNEW(zCNetSession(_protocol));
	if (!session->IsValid())  zERR_FAULT("B: (zCNet::construct) Session could not be initialized");	
	
    NetReset();	

	sendCount=0;
	recvCount=0;

	enabled = false;
}

// /////////////////////////////////////////////////////////////////////////
// class zCNet: Destructor
// 
// /////////////////////////////////////////////////////////////////////////
zCNet::~zCNet()
{		
    NetReset();

    delete session;
    session=0;   	
};





zERROR_ID zCNet::NetReset()
{		
    if (!session) 
    {
        zERR_FAULT("B: (zCNet::NetReset) \"session\" is not defined.");
        return zERR_NONE;
    };	

	session->Reset();
       
    StreamListen(0);
          		
    // close network-handles
    if (handle_stream_listen) netClose(handle_stream_listen);				
    if (handle_dgram_listen) netClose(handle_dgram_listen);		
    handle_dgram_listen		= 0;
    handle_stream_listen	= 0;
          	
    // restart if protocol valid
    if (session->IsValid())
    {
        handle_dgram_listen = netListenPacket(&session->GetListenPacketAddress());
    }

	for (int i=0;i<zNET_MAX_HOSTID;i++)
	{
		NetReset(i);
	}

    return zERR_NONE;
}


zERROR_ID zCNet::NetReset(int id)
{
	if ((id>=0) && (id<zNET_MAX_HOSTID))
	{
		sendPacketCounter[id] = 0;
		recvPacketCounter[id] = 0;
	}
	return zERR_NONE;
};


zERROR_ID zCNet::StreamListen(LPCFUNCP callback)
{
	if (!session) callback=0;
	
	zERR_ASSERTT(enabled || !callback, "You can't listen for streams cause the network is not enabled");
          
    connectCallback = callback;
          	
    if (handle_stream_listen) 
    {
        netClose(handle_stream_listen);
        handle_stream_listen = 0;
    }
          
    if (connectCallback) 
    {
        handle_stream_listen = netListenStream(&session->GetListenStreamAddress(), connectCallback);
    }
          
    return zERR_NONE;
}







zERROR_ID zCNet::Send(zCNetMessage*& _msg)
{		
	zUDWORD result_size;

	if (!_msg->IsStream())	result_size = DGramWriteMessage (_msg);
					else	result_size = StreamWriteMessage(_msg);


	if (_msg->IsFileMessage()) 
	{
		zERR_MESSAGE(5,0,"B: zNET: Sending file ...");
		result_size = StreamWriteFile(_msg);	
	}
    
    return zERR_NONE;
}



zUDWORD zCNet::DGramWriteMessage(zCNetMessage*& _msg)
{
	zERR_ASSERTT(enabled, "B: zNET: You can't send messages. The network is not enabled.");
	
	zCPlayerGroup*	to_group;
	zCPlayerInfo*	to_player;
	_msg->GetTarget(to_player,to_group);

	zUDWORD		result_size=0;

	if (to_player) result_size = DGramWriteToPlayer(_msg, to_player);	
	if (to_group)  result_size = DGramWriteToGroup(_msg, to_group);		

	// TODO: result_size von beiden aufrufen pruefen
	return result_size;
}



zUDWORD zCNet::DGramWriteToPlayer(zCNetMessage* _msg, zCPlayerInfo* to_player)
{	
	zERR_ASSERTT(_msg->GetSize()<=zNET_MAX_DGRAMSIZE, "B: zNET: Size of the Datagram exceeds limit.");

	ApplyTimestamp(_msg, to_player->GetID());

	zNET_HANDLE handle=0;
	zCNetHost* _host = to_player->GetNetHost();

	if (!netSend ( _host->GetPacketAddr(), _msg->GetPtr(), _msg->GetSize(), handle))
	{
		zERR_WARNING("B: (zCNet::DGramWriteToPlayer) Could not send message: "+zSTRING(netGetLastErrorString()));
		zERR_WARNING("B: (zCNet::DGramWriteToPlayer) ... "+_host->GetReadableAddr()+":"+zSTRING(int(_host->GetPacketAddr()->INET.Port))+"("+zSTRING(int(_host->GetPacketAddr()->Protocol))+")");
	}			
	else statistics.AddPacketSend(_msg->GetSize());	

	return _msg->GetSize();

}

zUDWORD zCNet::DGramWriteToGroup(zCNetMessage* _msg, zCPlayerGroup* to_group)
{
	zUDWORD write_size=0;
	int iter;
	zCPlayerInfo* aPlayer = to_group->GetFirstPlayer(iter);
    while (aPlayer)
    {
		write_size = _msg->GetSize();
		if (!aPlayer->IsActive()) DGramWriteToPlayer(_msg,aPlayer);
		
        aPlayer = to_group->GetNextPlayer(iter);
    }

	// TODO: result_size von allen aufrufen pruefen
	return write_size;
}

zERROR_ID zCNet::DGramRead(zCNetMessage*& _msg)
{	
    if (_msg) delete _msg;
    _msg = 0;	
    zTNetPacketPtr pkt = netRecv(handle_dgram_listen);
    if (!pkt) return zERR_NONE;
    _msg = zNEW(zCNetMessage(pkt));
		
	statistics.AddPacketRecv(pkt->size);	

	CheckTimestamp(_msg, _msg->GetSenderID());

    return zERR_NONE;
}



zUDWORD zCNet::StreamRead(zCNetMessage*& msg, zCPlayerInfo* from_player)
{		
	zERR_ASSERTT(enabled, "B: zNET: You can't read from stream. The network is not enabled");
	
	msg=0;

	// zCNetHost* host = from_player->GetNetHost();

	zUDWORD read_size, rest_size, result_size, size, header_size;
	
	// lese den message-header	
	zTNetMessageHeader header;
	header_size = sizeof(header);

	result_size  = StreamReadFromPlayer(&header,header_size,from_player, zNET_READ_BLOCK);	

	if (result_size<=0) 
		return 0; // keine daten empfangen

	if (result_size != header_size) 
		zERR_WARNING("B: (zCNet::StreamRead) expected a header, but read more or less data");

	// nachricht liegt auf dem Stream
	msg = zNEW(zCNetMessage(header));
	msg->SetStream();
	// lese message-daten	
	rest_size = header.datasize;
	size = msg->GetSize();
	
	while (rest_size>0)
	{
		sysEvent();
		if (rest_size<=zNET_MAX_STREAMSIZE) read_size = rest_size;
		else read_size = zNET_MAX_STREAMSIZE;
		
		result_size = StreamReadFromPlayer(buffer,read_size,from_player);
		msg->Add(buffer,result_size);
		
		rest_size -= result_size;
	};

	msg->ResetCursorPtr();
	return msg->GetSize();
}




zUDWORD zCNet::StreamReadFromPlayer(void* ptr, zUDWORD size, zCPlayerInfo* from_player, zTNetStreamReadMode mode)
{		
	zERR_ASSERTT(enabled, "B: zNET: You can't read from stream. The network is not enabled");
	
	zCNetHost* host = from_player->GetNetHost();
	zNET_HANDLE handle = host->GetStreamHandle();

	zUDWORD result_size;

	if (mode == zNET_READ_STREAM) 
	{
		result_size = netRead(handle, ptr, size);
	}
	else
	{
		zUDWORD rest_size = size;		
		zUDWORD i = 0;
		while (rest_size>0)
		{
			 result_size = netRead(handle, ((zBYTE*)ptr)+i, rest_size);
			 rest_size -= result_size;
			 i+=result_size;
		}
		result_size = size-rest_size;
	}

	return result_size;
}



zUDWORD zCNet::StreamWriteMessage(zCNetMessage*& _msg)
{	
	zERR_ASSERTT(enabled, "B: zNET: You can't write to stream. The network is not enabled");

	zCPlayerGroup*	to_group;
	zCPlayerInfo*	to_player;
	_msg->GetTarget(to_player,to_group);

	void*		ptr;
	zUDWORD		size(0), result_size(0), rest_size(0), write_size(0);	

	// sende den header
	size	= _msg->GetHeaderSize();
	ptr		= _msg->GetHeader();	
	if (to_player)	result_size = StreamWriteToPlayer(ptr,size,to_player);    
	if (to_group)	result_size = StreamWriteToGroup(ptr,size,to_group);    

	_msg->ResetCursorPtr();	

	// TODO: pruefe beide results
          	
    // send data  	
    rest_size = size = write_size= _msg->GetDataSize();
	
    while (rest_size>0)
    {		
		ptr = _msg->GetCursorPtr();

        if (rest_size<=zNET_MAX_STREAMSIZE) write_size = rest_size;
		else write_size = zNET_MAX_STREAMSIZE;
		
		if (write_size>0)
		{
			if (to_player)	result_size = StreamWriteToPlayer(ptr,write_size,to_player);    
			if (to_group)	result_size = StreamWriteToGroup(ptr,write_size,to_group);    
			sysEvent();			
		}

		// TODO: pruefe beide results
		        
        _msg->AddCursorPtr(result_size);
        rest_size-=result_size;
    };		
          
    // check for errors
    if (rest_size<0) zERR_WARNING("B: (zCNet::StreamWriteMessage) Sent more bytes than allowed.");

	// TODO: result_size von allen aufrufen pruefen
	return size-rest_size;
}

zUDWORD zCNet::StreamWriteToPlayer(void* ptr, zUDWORD size, zCPlayerInfo* player)
{	
	zERR_ASSERTT(enabled, "B: zNET: You can't write to stream. The network is not enabled");
	
    netWrite( player->GetNetHost()->GetStreamHandle(), ptr, size, TRUE);    

	return size;
}

zUDWORD zCNet::StreamWriteToGroup(void* ptr, zUDWORD size, zCPlayerGroup* group)
{	
	zUDWORD write_size=size;
	int iter;
	zCPlayerInfo* aPlayer = group->GetFirstPlayer(iter);
    while (aPlayer)
    {
		size = write_size;
		if (!aPlayer->IsActive()) StreamWriteToPlayer(ptr,size,aPlayer);
        aPlayer = group->GetNextPlayer(iter);
    }

	// TODO: result_size von allen aufrufen pruefen
	return size;
}

struct zTNetFileHeader
{
	unsigned long size;
	char remote_path[_MAX_PATH];
};

struct zTNetFileFooter
{
	zDWORD checksum;	
};

zUDWORD zCNet::StreamWriteFile(zCNetMessage*& _msg)
{
	zERR_MESSAGE(5,0,"B: zNET: StreamWriteFile");
	
	zCPlayerGroup*	to_group;
	zCPlayerInfo*	to_player;
	_msg->GetTarget(to_player,to_group);	

	zFILE *file, *dummy;
	file = _msg->GetFile(dummy);

	file->Open();		

	// add filesize
	zUDWORD file_size = file->Size();	
	zUDWORD rest_size = file_size;
	zUDWORD write_size;		
	zUDWORD result_size;

	// erzeuge file-header
	zTNetFileHeader header;
	header.size = file_size;
	strcpy(header.remote_path, file->GetFullPath().ToChar());	

	// verschicke den header
	if (to_player) result_size = StreamWriteToPlayer(&header,sizeof(header),to_player);
	if (to_group)  result_size = StreamWriteToGroup(&header,sizeof(header),to_group);
	
	// TODO: Beide Results Pruefen
	
	zCChecksum checksum;	
	checksum.BeginChecksum();


	// nun verschicke das file	
	zBOOL finished=(file_size==0);
	while (!finished)	
	{		
		sysEvent();

		write_size = file->Read(&buffer,zNET_MAX_STREAMSIZE);

		checksum.CalcBufferChecksum(buffer,write_size);

		if (write_size>0)
		{
			// verschicke den datenblock
			if (to_player) result_size = StreamWriteToPlayer(&buffer,write_size,to_player);
			if (to_group)  result_size = StreamWriteToGroup(&buffer,write_size,to_group);
		}
		
		rest_size -= result_size;

		finished = (write_size!=zNET_MAX_STREAMSIZE) || (result_size != write_size);
	};

	zERR_MESSAGE(5,0,"B: zNET: StreamWriteFile: Sent "+zSTRING(file_size)+" bytes");
	
	// erzeuge file-footer
	zTNetFileFooter footer;
	footer.checksum = checksum.EndChecksum();
	
	// verschicke den footer
	if (to_player) StreamWriteToPlayer(&footer,sizeof(footer),to_player);
	if (to_group)  StreamWriteToGroup(&footer,sizeof(footer),to_group);

	file->Close();
	// _msg->SetFileMessage(0);

	// TODO: result_size von allen aufrufen pruefen
	return file_size-rest_size;
};

zUDWORD zCNet::StreamReadFile(zCNetMessagePtr msg, zCPlayerInfo* from_player)
{		
	zERR_MESSAGE(5,0,"B: zNET: StreamReadFile");

	zUDWORD file_size;	
	zUDWORD rest_size;
	zUDWORD read_size;		
	zUDWORD result_size;

	// lede den datei-header (falls vorhanden)
	
	zTNetFileHeader header;
	result_size = StreamReadFromPlayer(&header,sizeof(header),from_player, zNET_READ_BLOCK);
	if (result_size<=0) return 0;		

	// erzeuge die datei
	file_size = header.size;
	zERR_MESSAGE(9,0,"B: zNET: Read file-header: "+zSTRING(header.remote_path)+" ( "+zSTRING(file_size)+" byte)");
	
	zoptions->ChangeDir(DIR_DATA);
	zFILE* remote_file	= zNEW(zFILE_FILE(header.remote_path));
	zFILE* file			= zNEW(zFILE_FILE("temp.dat"));

	msg->SetFileMessage(file,remote_file);

	// erzeuge die datei und starte checksum
	zCChecksum checksum;	
	checksum.BeginChecksum();	
	file->Create("temp.dat");
	
	// lese die datei und berechne checksum
	
	rest_size = file_size;
	zBOOL finished=(rest_size==0);
	while (!finished)	
	{		
		sysEvent();		

		read_size = zNET_MAX_STREAMSIZE;
		if (read_size>rest_size) read_size = rest_size;

		result_size = StreamReadFromPlayer(buffer,read_size,from_player);
			
		if (result_size>0)
		{
			checksum.CalcBufferChecksum(buffer,result_size);
			file->Write(&buffer,result_size);			
			rest_size -= result_size;
		}				

		zERR_MESSAGE(9,0,"B: zNET: StreamReadFile: Read "+zSTRING(file_size-rest_size)+" bytes (-"+zSTRING(rest_size)+")");

		finished = (rest_size <= 0);
	};	
	
	// schliesse die datei und ermittle checksum
	file->Close();
	
	// lese den datei-footer

	zTNetFileFooter footer;
	result_size = StreamReadFromPlayer(&footer,sizeof(footer),from_player, zNET_READ_BLOCK);

	zERR_MESSAGE(9,0,"B: zNET: StreamReadFile finished");
	return 0;
};



zERROR_ID zCNet::MsgGetFromStream(zCPlayerInfo* player, zCNetMessage*& msg)
{
	msg=0;
	if (!player->GetNetHost())
	{
		zERR_FATAL("B: (zCNet::MsgGetFromStream) Player has not network-host-data");
		return zERR_NONE;
	};
	zUDWORD result_size = StreamRead(msg, player);		

	if (msg->IsFileMessage())
	{
		result_size += StreamReadFile(msg,player);
	};

	return result_size;
};



/** Putting the message into a message-queue 
* The message will be put in to a sendQueue and be sent if idle
* @param Message to be put into the sendQueue
* @return zERR_NET_NO_MESSAGE, zERR_NET_PUT
*/
zERROR_ID zCNet::MsgPut(zCNetMessagePtr _msg)
{    
	if (!enabled) return zERR_NONE;

	if (!_msg) 
	{
		zERR_WARNING("B: (zCNet::MsgPut) There is no message to \"put\"");
		return zERR_NONE;
	}
    while (lockQueues);
	
    error = Send(_msg);
    
	delete _msg;
	_msg=0;
    
    return error;
}





/** Getting a message out of a message-queue
* @param Message from the recvQueue
* @return zERR_NET_NO_MESSAGE, zERR_NET_GET
*/
zERROR_ID zCNet::MsgGet(zCNetMessage*& _msg, const zBYTE _pri)
{		 
	_msg=0;
	if (!enabled) return zERR_NONE;

	while (lockQueues);
          			
    _msg = recvQueue[_pri].Pop();
	if (_msg) recvCount--;	
	
	return zERR_NONE;
}





/** Sending a message from the sendQueue
* This method takes a message from the sendQueues and sends it
* @return zERR_NET_NO_MESSAGE, zERR_NET_SEND
*/
zERROR_ID zCNet::MsgSendFromQueue()
{		              
    if (sendCount==0) // return if no recv-messages are queued
        return zERR_NET_NO_MESSAGE;
          
    int pri = 0;
    error = zERR_NONE;

    msgPtr = sendQueue[pri].Pop();
    if (msgPtr) 
    {
        error = Send(msgPtr);
		
        if (error != zERR_NONE) // "send" failed
		{
			return zERR_NET_SEND;
		}
		else // sent successfully: delete message
		{			
			sendCount--;					
			delete msgPtr;msgPtr=0;	
			return zERR_NONE;
		}            
    }		

    return zERR_NET_NO_MESSAGE; // nothing found, return 0	
}





/** Receive a Message from IPX or UDP
* This method looks for incoming messages and stores the next one into a recvQueue	  
* @return zERR_NET_NO_MESSAGE, zERR_NET_RECV
*/
zERROR_ID zCNet::MsgRecvToQueue()
{				
    // recv message
    msgPtr = NULL;
    error = DGramRead(msgPtr);		
          
    if (error!=zERR_NONE) return zERR_NET_RECV;
    if (!msgPtr) return zERR_NET_NO_MESSAGE;		
    // get priority of the message
    int pri = 0;		
    recvQueue[pri].Push(msgPtr);
    recvCount++;		
    
    return error;
}





zERROR_ID zCNet::HandleReceiving()
{		
    static zERROR_ID error;
    static int count;
    error = zERR_NONE;		
    count=0;
    while (error == zERR_NONE) 
    {
        error = MsgRecvToQueue();
        count++;
        // get only 10 messages from the queues
        // if (count>10) error = zERR_NET_NO_MESSAGE;
    }		
    return error;
}





zERROR_ID zCNet::HandleSending()
{			
    static zERROR_ID error;
    
	error = zERR_NONE;    
	while 
	(
		(error = MsgSendFromQueue()) 
		==
		zERR_NONE
	);
	
	if (error != zERR_NET_NO_MESSAGE) zERR_FAULT("B: (zCNetHandle) sending messages causes an error");

    return error;				
}





/** Sending and Reveiving messages
* 
*/
void zCNet::Handle()
{				
    static zERROR_ID error;
    static int count;		

	/****** Commented out.: For later use (different priority-classes of messages)

    // ** send all queued messages
	
    error = HandleSending();	

	// check if all messages have been sent:
    if (sendCount>0)		
        zERR_WARNING("B: (zCNetHandle) sendQueue is not empty after sending all messages");		    

	if (error!=zERR_NONE)
		zERR_WARNING("B: (zCNetHandle) Sending message causses an error.");
	*/

    // ** receive messages and put them in the queues
          
    LockQueues(TRUE);
    error = HandleReceiving();
    LockQueues(FALSE);
          	
    // checking for errors:
    if (error!=zERR_NET_NO_MESSAGE) zERR_FAULT("B: (zCNetHandle) receiving message causes an error");
}





zERROR_ID zCNet::StreamConnect(zCNetHost*& _host)
{			
	zERR_ASSERT(_host);
    _host->SetStreamHandle(	netConnect(_host->GetStreamAddr()) );
    if (_host->GetStreamHandle()==0) return zERR_NET_CONNECT;
    return zERR_NONE;
}





/// disconnect from the given host
zERROR_ID zCNet::StreamDisconnect(zCNetHost*& _host)
{	
	zERR_ASSERT(_host);	
	zERR_ASSERT(_host->GetStreamHandle()>0);

    netClose(_host->GetStreamHandle());
	_host->SetStreamHandle(0);
    return zERR_NONE;
}





void zCNet::LockQueues(zBOOL lock)
{ 
    lockQueues = lock; 
};

zBOOL zCNet::WaitForStreamMessage(zCPlayerInfo* player, zCNetMessage*& msg)
{	
	zERR_MESSAGE(9,0,"B: zNET: Wait for Stream-Message");

	msg = 0;
	
	zBOOL finished = FALSE;
	while (!finished)
	{
		sysEvent();		

		znet->Handle();
		znet->MsgGetFromStream(player, msg);		
		
		if (msg) 
			return TRUE;
	}
	
	return FALSE;
};

///
// Services
///


zTNetAddress* zCNet::GetLocalAddress()
{
	return netGetHostAddr( netGetLocalHost() );	
};

void zCNet::EnableNetwork(bool enable)
{
	enabled = enable;
}



// /////////////////////////////////////////////////////////////////////////
// Timestamp
// /////////////////////////////////////////////////////////////////////////

void zCNet::ApplyTimestamp(zCNetMessage* _msg, zBYTE id)
{		
	_msg->SetTimestamp(sendPacketCounter[id]);
	if (id>0) sendPacketCounter[id]++;
	if (sendPacketCounter[id]>100) sendPacketCounter[id]=0;
};

int	 zCNet::CheckTimestamp(zCNetMessage* _msg, zBYTE id)
{
	return 0;	// disabled

	zDWORD timestamp = _msg->GetTimestamp();	
	if (recvPacketCounter[id]!=timestamp)
	{
		int diff = timestamp - recvPacketCounter[id];
		if (diff<0) 
		{
			zERR_WARNING("B: ZNET: Message from "+zSTRING(id)+" with timestamp "+zSTRING(timestamp)+" received. To late: Current Timestamp is "+zSTRING(recvPacketCounter[id]));
		}
		else if (diff>0) 
		{
			GetStatistics()->AddLostRecv(diff);
			zERR_WARNING("B: ZNET: Message from "+zSTRING(id)+" with timestamp "+zSTRING(timestamp)+" received. To early: Current Timestamp is "+zSTRING(recvPacketCounter[id]));
		}
	};

	if (id>0) recvPacketCounter[id]++;
	if (recvPacketCounter[id]>100) recvPacketCounter[id]=0;
	return 0;
};

// /////////////////////////////////////////////////////////////////////////
// Statistics
// /////////////////////////////////////////////////////////////////////////


zCNetStatistics::zCNetStatistics()
{
	seconds = 0;	
};

zCNetStatistics::~zCNetStatistics()
{
};

void zCNetStatistics::AddLostRecv(unsigned int num)
{
	lost_recv.packets-=num;
};

void zCNetStatistics::AddLostSend(unsigned int num)
{
	lost_sent.packets+=num;
};

void zCNetStatistics::AddPacketSend(double bytes)
{
	if (!started) return;

	sent.bytes += bytes;
	sent.packets += 1;
};

void zCNetStatistics::AddPacketRecv(double bytes)
{
	if (!started) return;

	recv.bytes += bytes;
	recv.packets += 1;
};

void zCNetStatistics::Start()
{ 
	recv.Init();
	sent.Init();
	lost_recv.Init();
	lost_sent.Init();
	seconds = 0;	
	started = TRUE;

	time(&start_time);	
	zCBuffer::ByteFreq_Reset();

	zERR_MESSAGE(3,0,"B: ZNET: Network-Statistics: Started");
};

void zCNetStatistics::Stop()
{	

	seconds = GetSeconds();

	started = FALSE;
	zERR_MESSAGE(3,0,"B: ZNET: Network-Statistics: Stopped");
};

void zCNetStatistics::Print()
{		
	// time	
	seconds = GetSeconds();

	zDWORD minutes = int(seconds / 60);
	zDWORD restseconds = (zDWORD)(seconds - minutes*60);
	// bytes per seconds
	zDWORD bps_s = zDWORD(sent.bytes / seconds);
	zDWORD bps_r = zDWORD(recv.bytes / seconds);
	// packets per minute
	zDWORD ppm_s = zDWORD((sent.packets / seconds)*60);
	zDWORD ppm_r = zDWORD((recv.packets / seconds)*60);
	// bytes per packet
	zDWORD bpp_s = zDWORD(sent.bytes / sent.packets);
	zDWORD bpp_r = zDWORD(recv.bytes / recv.packets);
	// output
	if (started) 
	{
		zERR_MESSAGE(1,zERR_BEGIN,"B: zNET: Network-Statistics Snapshot");
	}
	else 
	{
		zERR_MESSAGE(1,zERR_BEGIN,"B: zNET: Network-Statistics");
	}
	zERR_MESSAGE(1,0,"B: zNET: Time recorded..: "+zSTRING(minutes)+":"+zSTRING(restseconds).Align(zSTR_RIGHT,2,'0'));	
	zERR_MESSAGE(1,0,"B: zNET: Kilobytes .....: "+zSTRING(zDWORD(sent.bytes/1024)).Align(zSTR_RIGHT, 7)+" sent, "+zSTRING(zDWORD(recv.bytes/1024)).Align(zSTR_RIGHT, 7)+" received.");	
	zERR_MESSAGE(1,0,"B: zNET: Packets........: "+zSTRING(zDWORD(sent.packets   )).Align(zSTR_RIGHT, 7)+" sent, "+zSTRING(zDWORD(recv.packets   )).Align(zSTR_RIGHT, 7)+" received.");	
	zERR_MESSAGE(1,0,"B: zNET: Bytes/sec......: "+zSTRING(bps_s).Align(zSTR_RIGHT, 7)+" sent, "+zSTRING(bps_r).Align(zSTR_RIGHT, 7)+" received.");	
	zERR_MESSAGE(1,0,"B: zNET: Packets/min....: "+zSTRING(ppm_s).Align(zSTR_RIGHT, 7)+" sent, "+zSTRING(ppm_r).Align(zSTR_RIGHT, 7)+" received.");	
	zERR_MESSAGE(1,0,"B: zNET: Bytes/Packet...: "+zSTRING(bpp_s).Align(zSTR_RIGHT, 7)+" sent, "+zSTRING(bpp_r).Align(zSTR_RIGHT, 7)+" received.");	
	zERR_MESSAGE(1,0,"B: zNET: Bytes lost.....: not yet implemented");
	zERR_MESSAGE(1,0,"B: zNET: Packets lost...: "+zSTRING(lost_recv.packets).Align(zSTR_RIGHT, 7)+" recv");
	zERR_MESSAGE(1,zERR_END,"");

	zCBuffer::ByteFreq_Print();
};

void zCNetStatistics::Reset()
{
	Stop();
	Start();
};

 
double zCNetStatistics::GetSeconds()
{
	time_t finished_time;
	time(&finished_time);
	seconds = difftime(finished_time, start_time);
	return seconds;
};


