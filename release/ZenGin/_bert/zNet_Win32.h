/******************************************************************************** 
 
     $Workfile:: zNet_Win32.h         $                $Date:: 4.12.00 18:22    $
     $Revision:: 8                    $             $Modtime:: 4.12.00 18:12    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   fundamental network-function, buffering and threading
 
 * $Log: /current_work/ZenGin/_Bert/zNet_Win32.h $
 * 
 * 8     4.12.00 18:22 Moos
 * 
 * 7     28.08.00 15:15 Speckels
 * 
 * 14    23.08.00 21:47 Admin
 * 
 * 5     21.08.00 18:26 Speckels
 * 
 * 12    16.08.00 12:32 Admin
 * 
 * 4     10.08.00 21:47 Speckels
 * 
 * 11    9.08.00 17:12 Admin
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:23 Speckels
 * 
 * 5     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 4     21.10.99 23:28 Speckels
 * Extrem changes for structs, classes and
 * constants (mostly renamed)
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
/// @version $Revision: 8 $ ($Modtime: 4.12.00 18:12 $)

#ifndef __ZNET_WIN32_H__
#define __ZNET_WIN32_H__

#ifndef _INC_WINDOWS
#include <windows.h>
#endif

#ifndef __ZYPES_H__
#include "ztypes.h"
#endif

#define zNET_MAKEIP(n1,n2,n3,n4) ((zDWORD)(((n1)<<24)|((n2)<<16)|((n3)<<8)|(n4)))

// Network defines
#define zNETERR_NOERROR				0								// No error
#define zNETERR_UNKNOWN				1								// Unknown error
#define zNETERR_TIMEOUT				2								// Time out
#define zNETERR_NOINIT				3								// Not initialised
#define zNETERR_NETDOWN				4								// Network down
#define zNETERR_NOSUPPORT			5								// Address not supported
#define zNETERR_INPROGRESS			6								// Blocked
#define zNETERR_WOULDBLOCK			7								// Call would block nonblocked socket
#define zNETERR_NOSOCK				8								// No more sockets
#define zNETERR_NOBUFS				9								// No more buffers
#define zNETERR_PROTNOSUPPORT		10								// Protocol not supported
#define zNETERR_PROTOTYPE_ILLEGAL	11								// Illegal protocol
#define zNETERR_SOCKNOSUPPORT		12								// Socket option not supported
#define zNETERR_HOSTNOTFOUND 		13								// Host not found
#define zNETERR_TRYAGAIN 			14								// Try again
#define zNETERR_NORECOVERY			15								// Unrecoverable error
#define zNETERR_NODATA				16								// No data found
#define zNETERR_ADDRINUSE			17								// Address in use
#define zNETERR_ISCONNECTED			18								// Socket is already connected
#define zNETERR_ADDRNOTAVAIL 		19								// Address not available
#define zNETERR_CONNECTIONREFUSED	20								// Connection refused
#define zNETERR_NETUNREACHABLE		21								// Network is unreachable
#define zNETERR_ILLEGALHANDLE		22								// Illegal zNET_HANDLE
#define zNETERR_CLOSED				23								// zNET_HANDLE has closed
#define zNETERR_ILLEGALHOST			24								// Illegal host name
#define zNETERR_ACCESS				25								// Access to address denied
#define zNETERR_INTERUPTED			26								// Network call canceled
#define zNETERR_NETRESET 			27								// Network has reset connection
#define zNETERR_NOTCONNECTED		28								// Socket not connected
#define zNETERR_SHUTDOWN 			29								// Socket has been shut down
#define zNETERR_MSGSIZE				30								// Datagram size too large
#define zNETERR_CONNABORTED			31								// Connection was aborted due to timeout or failure
#define zNETERR_CONNRESET			32								// Connection reset by remote host
#define zNETERR_HOSTUNREACHABLE		33								// Host unreachable
#define zNETERR_NOTSOCK				34								// Not a socket
#define zNETERR_NOTSUPPORTED 		35								// Function is not supported
#define zNETERR_NOSOCKFORPKT 		36								// No socket for packet listen
#define zNETERR_ILLEGALPACKET		37								// Packet malformed
#define zNETERR_PKTNODELIVER 		38								// Packet undeliverable
#define zNETERR_PHYSERROR			39								// Physical error
#define zNETERR_NOACK				40								// Remote end doesn't ACK sequenced packets
#define zNETERR_NOSPX				41								// SPX driver not found
#define zNETERR_SOCKNOTOPEN			42								// Socket not open
#define zNETERR_SOCKOPEN 			43								// Socket already open

#define zNET_PROTOCOL_IPX			0								// IPX/SPX protocols protocol
#define zNET_PROTOCOL_TCP			1								// TCP/UDP protocols protocol
#define zNET_PROTOCOLS				2								// Amount of network protocols

#define zNET_MAX_DGRAMSIZE			512 							// Max size for receiving datagrams

// Protocol numbers (user for netGetServicePort)
#define zNET_PROTOCOL_UDP				0								// UDP (Datagram) protocol
#define zNET_PROTOCOL_TCP				1								// TCP (Streaming) protocol
#define zNET_PROTOCOL_ANY				2								// Any protocol will do

// Network handle typedef
typedef void *zNET_HANDLE;
typedef zBOOL (__cdecl * LPCFUNCP)(LPVOID);
#define CFUNCP zBOOL;




///
// Network address for SPX/IPX and TCP/UDP
///
#pragma pack (1)
struct zTNetAddress
{
	zWORD Protocol;					// Network protocol
	union
	{
		// Internet (TCP/IP, UDP) address data
		struct
		{
			zWORD	Port;			// TCP/IP, UDP Port
			zDWORD	IP;				// Internet IP (Network order)
		} INET;

		// IPX/SPX addres
		struct
		{
			zBYTE	Net[4];			// IPX/SPX Network
			zBYTE	Node[6];		// IPX/SPX Node address
			zWORD	Socket;			// IPX/SPX Socket
		} IPX;
	};
};

typedef zTNetAddress* zTNetAddressPtr;




///
// Network buffer statistics
///
#pragma pack (4)

struct zTNetBufferInfo
{
	int		inPackets;			// Input queue in packets
	int		inBytes;			// Input queue in zBYTEs
};



///
// Network packet (only used for incoming (receiving) packets)
///
#if defined (_WIN32)
#pragma warning(disable : 4200) // Zero-length array item at end of structure, a VC-specific extension
#endif


struct zTNetPacket
{
	zTNetAddress From;													// Sender of packet
	zDWORD	timestamp;												// TimeStamp buffer was received/created
	zDWORD  size;													// Length of packet
	zBYTE	Data[];													// Packet data
};

typedef zTNetPacket* zTNetPacketPtr;



///
// Network timeout structure
///
struct zTNetTimeout
{
	zDWORD	getHostAddress;											// Timeout for getting host address
	zDWORD	getHostName;											// Timeout for getting host name
	zDWORD	getService;												// Timeout for getting service info
	zDWORD	Connect;												// Timeout for connecting to host
};

typedef zTNetTimeout* zTNetTimeoutPtr;

extern	zBOOL	netEnable;												    // Network enable flag

///
// Network declarations
///
extern	int				netGetLastError();									// Get last error code
extern	char*			netGetLastErrorString();							// Get last error string
extern	zBOOL			netGetProtocolSupported(int protocol);				// Get protocol support flag
extern	zTNetAddress*	netGetHostAddr(char *HostName); 					// Get address of host by name
extern	char*			netGetLocalHost();									// Get name of local host
extern	char*			netGetHostName(zTNetAddress *HostAddr);				// Get name of host by address
extern	zDWORD			netGetServicePort(char *Name, int Protocol); 		// Get service port information
extern	zNET_HANDLE		netListenStream(zTNetAddress *Server, LPCFUNCP AcceptProc); // Listen for incoming connections
extern	zNET_HANDLE		netListenPacket(zTNetAddress *Server);				// Listen for incoming packets
extern	zNET_HANDLE		netConnect(zTNetAddress *Host); 						// Connect stream protocol to server
extern	zBOOL			netClose(zNET_HANDLE Handle);						// Close network connection
extern	int				netRead(zNET_HANDLE Str, void *Buffer, int maxSize); // Read from network stream
extern	zBOOL			netWrite(zNET_HANDLE Str, void *Buffer, int size, zBOOL Wait); // Write to network stream
extern	zBOOL			netSend(zTNetAddress *Dest, void *Buffer, int size, zNET_HANDLE Handle);	// Send network packet
extern	zNET_HANDLE		netGetPacketHandle(zDWORD protocol);				// Get handle of send/receive packet
extern	zTNetPacket*	netRecv(zNET_HANDLE PacketHandle); 					// Receive network packet
extern	zBOOL			netSetMaxInQueuePackets(zNET_HANDLE Handle, int NumPackets); // Set packet input queue size
extern	zBOOL			netIsHandleClosed(zNET_HANDLE Handle);				// Check if zNET_HANDLE is closed
extern	zTNetBufferInfo*netGetBufferInfo(zNET_HANDLE Handle);			// Get buffer information structure
extern	zTNetAddress*	netGetLocalAddr(zNET_HANDLE Handle);				// Get local address of handle
extern	zTNetAddress*	netGetRemoteAddr(zNET_HANDLE Handle); 				// Get remote address of handle
extern	char*			netAddrToString(zTNetAddress *Addr, zBOOL Extended);	// Convert network address to readable string
extern	void			netSetTimeOut(int protocol, zTNetTimeout *Time);		// Set new network timeout values



#endif
