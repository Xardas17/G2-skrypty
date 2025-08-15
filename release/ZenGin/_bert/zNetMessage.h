/******************************************************************************** 
 
     $Workfile:: znetmessage.h       $                 $Date:: 4.12.00 18:22    $
     $Revision:: 9                   $              $Modtime:: 4.12.00 18:10    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   network-messages are generated and reveived using this class zCNetMessage. All
   algorithms using network-messages (streaming or datagram) will use objects of
   this class
 
 * $Log: /current_work/ZenGin/_Bert/znetmessage.h $
 * 
 * 9     4.12.00 18:22 Moos
 * 
 * 8     8.10.00 18:21 Speckels
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
 * 2     24.09.99 20:40 Speckels
 * VSS-kompatiblen Header eingefügt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 9 $ ($Modtime: 4.12.00 18:10 $)


 

#ifndef __ZNETMESSAGE_H__
#define __ZNETMESSAGE_H__



#ifndef __ZNETTYPES_H__
#include "znettypes.h"
#endif

#ifndef __ZNETHOST_H__
#include "znethost.h"
#endif

#ifndef __ZQUEUE_H__
#include "zqueue.h"
#endif

#ifndef __ZBUFFER_H__
#include "zbuffer.h"
#endif

#ifndef __ZPLAYERINFO_H__
#include "zplayerinfo.h"
#endif

#ifndef __ZPLAYERGROUP_H__
#include "zplayergroup.h"
#endif

/** message containing header and datablock
  * This class is a kind of template for incoming or outgoing messages. It's memberes represent the header of a message. The overloaded new-operator allocates all the needed memory. 
  */



// constants (flags)
const zBYTE zNET_MSGFLAG_FILE		= 1 << 0;	// Is there a file appended to this message?
const zBYTE zNET_MSGFLAG_LOG		= 1 << 1;	// Should I log this message to a file?
const zBYTE zNET_MSGFLAG_MULTIMSG	= 1 << 2;	// Is this message be sent to multiple players


// typedefs
typedef zBYTE zTNetMsgTimestamp;
typedef zBYTE zTNetSenderID;
const	zBYTE zNET_MAX_SENDERIDS = 255;


class zFILE;

#pragma pack(push)
#pragma pack(1)
struct zTNetMessageHeader
{
	zTNetMessageID		id;	
	zTNetSenderID		senderID;	
	zUDWORD				datasize;		
	zTNetMsgTimestamp	timestamp;	
	zBYTE				flags;
};
#pragma pack(pop)


/** all informations about a message
  * This class contains all informations needed for a received or to be sent message 
  */
class zCNetMessage
{				
public:
	
	///
	// Construction and Destruction
	///
	
	zCNetMessage(const zTNetMessageID& _id=0, zUDWORD len = zNET_MAX_DGRAMSIZE);	// constructor for an outgoing message		
	zCNetMessage(zTNetMessageHeader& header);	// constructor for received packets (reliable messages -> only headerdata)		
	zCNetMessage(zTNetPacketPtr _packet);		// constructor for received packets (unreliable messages)	
	virtual ~zCNetMessage();					// destructor

	void CopyFrom(zCNetMessage* msg);

	///
	// POINTER TO DATA
	///
	
	zBYTE*		GetPtr();				// retrieve pointer to complete message
	zBYTE*		GetDataPtr();			// retrieve pointer to begin of user-defined data		
	zBYTE*		GetCursorPtr();			// retrieve pointer to next data to be read or written
	zCBuffer*	GetBuffer();			// retrieve buffer with complete datablock			
	zTNetMessageHeader* 
				GetHeader();	// retrieve pointer to the messages header	
	
	///
	// MANIPULATIONS and more ...
	///
	
	void AddCursorPtr(zUDWORD len);	// increase the cursor manually	
	void ResetCursorPtr();			// set pointer the start of user-defined data	
	void SetMode(zTBufferMode mode);// set mode of the internal buffer (READ, WRITE or both)
	
	///
	// SIZES
	///
	
	zUDWORD		GetSize();			// Size of complete message.
	zUDWORD		GetDataSize();		// Size of user-defined data-block.	
	zUDWORD		GetRestSize();		// Retrieve rest of the maximum size available for read- or write-operations.
	zBYTE		GetHeaderSize();	// retrieve the size of a message-header		


	///
	// INFORMATIONS ABOUT THE MESSAGE FROM THE HEADER
	///
	
	zTNetMessageID		GetID();			// Get the identifier of the network-message.	
	zTNetSenderID		GetSenderID();		// Retrieve the senders id.	
	zBYTE				GetFlags();			// Get the flags of this message.
	zTNetMsgTimestamp	GetTimestamp();		// Read the timestamp of the message.
	zBOOL				IsFileMessage();	// Check if there is a file appended to the message (only streamed-messages).
	zBOOL				IsMultiMessage();	// was this message be sent to multiple players?
	
	
	void		GetTarget(zCPlayerInfoPtr& _player, zCPlayerGroupPtr& _group);	// Get this messages target (only applicable on send-side of this message).
	
	zBOOL		IsStream();					// Check, if this message will be send or has been received by a streaming-protocol.
	zFILE*		GetFile(zFILE*& filepath);	// Get a file-object to the file appended to this message. the file has bin created temporarily and must be moved to another place before other file-messages arrive.	
			

	///
	// CREATING A MESSAGE WITH ALL ITS DATA INSIDE
	///
	
	void	SetTarget(zCPlayerInfo* _player);	// Set the target of this message (a single player). You can use both with the same message: a single player AND a group of players as the target.	
	void	SetTarget(zCPlayerGroup* _group);	// Set the target of this message (a group of players).  You can use both with the same message: a single player AND a group of players as the target.	
	void	SetTimestamp(zTNetMsgTimestamp ts); // Set the timestamp of the message.		
	void	SetStream(zBOOL stream=TRUE);		// Make this message be sent using a streaming protocol
	void	SetFileMessage(zFILE* _file, zFILE* _remote_file=0);	// Append a file to the message.	

	//
	// READ, WRITE AND SEND
	//
	
	zUDWORD Get(void* data, const zUDWORD& len);	// Get some data from the message.	
	void	Get(zSTRING& str);						// Get a string from the message.	
	void Add(void* data, zUDWORD len);				// adding a bunch of data to the message	
	void Add(const zSTRING& str);					// adding a string to the messafe	

	void Send();									// Send the message or put it into a send-queue

	///
	// DEBUGGING
	///
	
	bool	HasError() const;								// check if there was an error while creating the message	
	void	SetLog(zBOOL log);								// allow logging or not	
	void	LogMessage(zFILE* file, const zSTRING& str);	// log the current message to the given file with leading text <str>

protected:

	void	Init();

private:
	
	zCBuffer*			buffer;			// Buffer for all the messages data including header-informations and user-defined data-block
	zBOOL				isStream;		// Inticator if this message should be or has been streamed (using streaming-protocols like TCP and SPX)	
	zFILE*				file;			// Pointer to appended file of this message. If received: The file has been saved to a temporary place. Move it soon to the final destination location. 	
	zFILE*				remote_file;	// Information about the original remote file and its location on the remote computer.		
	zCPlayerInfo*		targetPlayer;	// target of this message (a single player)	
	zCPlayerGroup*		targetGroup;	// target of this message (a group of players)
	
	zCNetMessage& operator=(zCNetMessage&);
};

typedef zCNetMessage* zCNetMessagePtr;



/** Outgoing and Incoming message will be stored in a message-queue where they will be taken "later" to be processed
  * This Queue is a kind of FIRST-IN-FIRST-OUT (FIFO) - queue
  */
class zCNetMessageQueue
{
	zQUEUE<zCNetMessage> queue;
public:
	/// pushing a message on the queue (will be added ad the end: last)
	void Push(zCNetMessage* msg) 
	{
		queue.Push(msg);
	};

	/// popping a message from the queue (will be taken from the start: first)
	zCNetMessage* Pop() 
	{
		return queue.PopFirst();
	};

	/// checking if the queue is empty
	zBOOL IsEmpty()
	{
		return queue.IsEmpty();
	}
};


typedef zCNetMessageQueue* zCNetMessagePtrQueue;

// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////
// END OF znetmessage.h
// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////


#endif