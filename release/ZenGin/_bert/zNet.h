/******************************************************************************** 
 
     $Workfile:: znet.h                 $              $Date:: 4.12.00 18:22    $
     $Revision:: 9                      $           $Modtime:: 4.12.00 18:13    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   network-class with abilities to send and receive messages using streaming 
   or datagram-protocols. 
 
 * $Log: /current_work/ZenGin/_Bert/znet.h $
 * 
 * 9     4.12.00 18:22 Moos
 * 
 * 8     8.09.00 17:37 Hildebrandt
 * fixed minor compiler warnings
 * 
 * 7     28.08.00 14:24 Speckels
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
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:23 Speckels
 * 
 * 6     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 5     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 4     3.12.99 16:09 Speckels
 * 
 * 3     25.09.99 18:11 Speckels
 * 
 * 2     24.09.99 20:40 Speckels
 * VSS-kompatiblen Header eingefügt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 9 $ ($Modtime: 4.12.00 18:13 $)



#ifndef __ZNET_H__
#define __ZNET_H__

#ifndef __ZNET_WIN32_H__
#include "znet_win32.h"
#endif

#ifndef __ZNETTYPES_H__
#include "znettypes.h"
#endif

#ifndef __ZNETSESSION_H__
#include "znetsession.h"
#endif

#ifndef __ZTOOLS_H__
#include "ztools.h"
#endif

class zCPlayerInfo;
class zCView;
class zCNetMessage;
class zCPlayerGroup;
class zCNetHost;
class zCNetSession;

typedef zCNetHost* zCNetHostPtr;


enum zTNetStreamReadMode { zNET_READ_BLOCK, zNET_READ_STREAM };

const int	zNET_FLAG_INIT	= 1;
const int	zNET_FLAG_CONNECT = 2;

struct zTNetStatistics
{
	double bytes;
	double packets;	

	zTNetStatistics()
	{
		Init();
	};

	void Init()
	{
		bytes	= 0;
		packets = 0;
	};
};

class zCNetStatistics
{
public:
			zCNetStatistics();
	virtual	~zCNetStatistics();
	void	Start();	
	void	Stop();
	double	GetSeconds();
	zTNetStatistics& GetSentStatistics()	{ return sent; };
	zTNetStatistics& GetRecvStatistics()	{ return recv; };
	zTNetStatistics& GetLostRecvStatistics(){ return lost_recv; };
	
	void	AddPacketSend(double bytes);
	void	AddPacketRecv(double bytes);
	void	AddLostRecv(unsigned int num);
	void	AddLostSend(unsigned int num);

	void	Reset();
	void	Print();

protected:

	zTNetStatistics sent;
	zTNetStatistics recv;
	zTNetStatistics lost_recv;
	zTNetStatistics lost_sent;

	double	seconds;
	zBOOL	started;
	
	time_t	start_time;	

};

/** base network-class building an interface above the grade-library.
  * 
  */
class zCNet
{		

public:	
	
			zCNet (zWORD _protocol);
	virtual	~zCNet();	

	void EnableNetwork(bool enable);
	
	zERROR_ID NetReset();							// reset network-specific settings like handles. Sets connectionCallback to NULL.
	zERROR_ID NetReset(int id);						// reset network-specific settings for a specific player with given id
	zERROR_ID StreamListen(LPCFUNCP callback);		// set and initialize callback-function for new connections: must be called after NetReset	
	zERROR_ID StreamConnect(zCNetHost*& _host);	// connect to a given host by TCP or SPX	
	zERROR_ID StreamDisconnect(zCNetHost*& _host);// disconnect from the given host
		
	zERROR_ID MsgPut(zCNetMessage* _msg);			// Putting the message into a message-queue 	
	zERROR_ID MsgGet(zCNetMessage*& _msg, const zBYTE _pri=0);				// Getting a message out of a message-queue
	zERROR_ID MsgGetFromStream(zCPlayerInfo* player, zCNetMessage*& msg);	// Getting a streaming-message directly from the network	  	
	
	zERROR_ID MsgSendFromQueue();		// Sending a message from the sendQueue
	zERROR_ID MsgRecvToQueue();			// Receive a Message from IPX or UDP
	
	zERROR_ID HandleReceiving();		// receive all waiting messages and put them into the queue	
	zERROR_ID HandleSending();			// send all queued messages

	void Handle();						// Sending and Reveiving messages

	void LockQueues(zBOOL lock);		// Locking the queues

	void SetDebugWindow(zCView* win1,zCView* win2);

	zCNetSession* GetSessionData()		{ return session; }
		
	zBOOL WaitForStreamMessage(zCPlayerInfo* player, zCNetMessage*& msg);	

	zCNetStatistics* GetStatistics() { return &statistics; };
	
	zTNetAddress* GetLocalAddress();

protected:

	zCNetSession*	session;
	bool			enabled;

	/// sending data using (unreliable) packets (udp, ipx)
	zUDWORD		DGramWriteMessage(zCNetMessage*& _msg);
	zUDWORD		DGramWriteToPlayer(zCNetMessage* _msg, zCPlayerInfo* to_player);
	zUDWORD		DGramWriteToGroup(zCNetMessage* _msg, zCPlayerGroup* to_group);

	/// receiving a message from the network (udp, ipx)
	zERROR_ID	DGramRead(zCNetMessage*& _msg);	

	/// sending data using (reliable) stream (tcp,spx)
	zUDWORD		StreamWriteMessage	(zCNetMessage*& _msg);
	zUDWORD		StreamWriteToPlayer	(void* ptr, zUDWORD size, zCPlayerInfo* player);
	zUDWORD		StreamWriteToGroup	(void* ptr, zUDWORD size, zCPlayerGroup* group);
	zUDWORD		StreamWriteFile		(zCNetMessage*& _msg);
	
	// reading data using (reliable) stream (tcp, spx)	
	zUDWORD		StreamReadFromPlayer(void* ptr, zUDWORD size, zCPlayerInfo* from_player, zTNetStreamReadMode mode = zNET_READ_STREAM);
	zUDWORD		StreamRead			(zCNetMessage*& msg, zCPlayerInfo* player);
	zUDWORD		StreamReadFile		(zCNetMessage* _msg, zCPlayerInfo* from_player);
	
	// sending a message to the network	  
	zERROR_ID	Send(zCNetMessage*& _msg);	

	void		ApplyTimestamp(zCNetMessage* _msg, zBYTE id);
	int			CheckTimestamp(zCNetMessage* _msg, zBYTE id);

	zCNetStatistics statistics;

private:	
	
	/// last internal error-id (not always equal with returned error-id)
	zERROR_ID error;
	
	// disable:
	zCNet();
	zCNet(zCNet&);
	zCNet& operator=(zCNet&);
	
	int	sendCount, recvCount;
	
};


typedef zCNet* zCNetPtr;

extern zCNetPtr znet;

// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////
// END OF znet.h
// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////

#endif