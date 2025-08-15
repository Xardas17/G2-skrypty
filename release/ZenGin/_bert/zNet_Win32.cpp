/******************************************************************************** 
 
     $Workfile:: zNet_Win32.cpp       $                $Date:: 31.08.00 18:06   $
     $Revision:: 10                   $             $Modtime:: 31.08.00 18:05   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/zNet_Win32.cpp $
 * 
 * 10    31.08.00 18:06 Speckels
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
 * 4     10.05.00 22:46 Speckels
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:23 Speckels
 * 
 * 7     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 6     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 4     12.11.99 21:13 Speckels
 * Einige Fehler im Bezug auf ENTER_PROC behoben.
 * 
 * 3     21.10.99 23:28 Speckels
 * Extrem changes for structs, classes and constants (mostly renamed)
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 10 $ ($Modtime: 31.08.00 18:05 $)




//
// #define WIN32_LEAN_AND_MEAN
// #define STRICT
 
#include "zcore.h"

// basic includes
#include  <winsock.h>
#include  <wsipx.h>

// win32-includes
#include  "zWin32.h"
#include  "zWin32_Internal.h"
#include  "zNet_Win32.h"

// zengin-includes
#include  "znetversion.h"


// #define INLINE  __inline
// #define FASTCALL __fastcall


const int zNET_TCP_BUFFERSIZE 		= 8192;
const int zNET_MAX_BUFFERS			= 550;

// Windows-Messages


const int WINMSG_MIN 			= WM_USER+1;
//
const int WINMSG_STREAM			= WM_USER+1;
const int WINMSG_DGRAM			= WM_USER+2;
//
const int WINMSG_SIMPLE			= WM_USER+3;
//
const int WINMSG_GETHOSTNAME 	= WM_USER+3;
const int WINMSG_GETHOSTIP		= WM_USER+4;
const int WINMSG_GETSERVICE		= WM_USER+5;
//
const int WINMSG_MAX			= WM_USER+5;
//
const int WINMSG_CONNECTED		= WM_USER+64;


// Socket-Modes

const int zNET_SOCKMODE_NUM			= 5;

const int zNET_SOCKMODE_NONE		= 0;
const int zNET_SOCKMODE_LISTEN 		= 1;
const int zNET_SOCKMODE_LISTENPKT	= 2;
const int zNET_SOCKMODE_CONNECTED	= 3;
const int zNET_SOCKMODE_ACCEPTING	= 4;

// internal structures

typedef void* FHANDLE;

struct zTSockError
{	
	zBYTE	error_id;
	int 	error_wsa;
	zBOOL	disconnect;
	char*	error_text;
};


struct zTCustomError
{
	zBYTE	error_id;
	char*	error_text;
};


struct zTNetBuffer
{
	void*	next;											
};

typedef zTNetBuffer* zTNetBufferPtr;


struct zTDgramInBuffer
{
	void*			next;
	zTNetPacket		packet;
};

typedef zTDgramInBuffer *zTDgramInBufferPtr;


struct zTDgramOutBuffer
{
	void*		next;
	SOCKADDR	destAddr;
	zDWORD		size;
	zBYTE		Data[];
};

typedef zTDgramOutBuffer* zTDgramOutBufferPtr;


struct zTStreamBuffer
{
	void	*next;											
	zDWORD	size;
	zDWORD	skip;
	zBYTE	Data[];
};

typedef zTStreamBuffer* zTStreamBufferPr;


struct zTNetSocket
{
	zBYTE	tag[5]; 												
	void*	next; 												
	SOCKET	socket;
	
	zBYTE	mode;											
	zBYTE	closed; 												

	void*			bufferToKill; 								

	zTNetBufferPtr	inHead; 												
	zTNetBufferPtr	inTail; 												

	LPCFUNCP acceptFunction; 											

	zTNetAddress	LocalAddr;										
	zTNetAddress	RemoteAddr; 											

	int 			maxInBuffers;									

	zTNetBufferInfo	bufferInfo;
};

typedef zTNetSocket* zTNetSocketPtr;

// Socketlist
static zTNetSocket		netSocketList= { "SOCK", 0, (SOCKET)-1, zNET_SOCKMODE_NONE, FALSE, 0, 0, 0, 0 };
static void				netAddSocket		(zTNetSocketPtr newSock);		
static zTNetSocketPtr	netFindSock			(SOCKET Sock);			
static zTNetSocketPtr	netFindSockByMode	(zBYTE Mode);		


// local constants and variables

static const zWORD	netAddrFam[2]		= { AF_IPX, AF_INET };		
static const zLONG	netStreamProto[2]	= { NSPROTO_SPX, 0 };	
static const zLONG	netPacketProto[2]	= { NSPROTO_IPX, 0 };	
static const zBYTE	netAddrDataIdx[2]	= {  2, 4 };			
static const zBYTE	netAddrDataLen[2]	= { 10, 4 };			

static char				netLocalHost[128];
static zTNetTimeout		netTimeoutTCP = { 10000, 10000, 1000, 10000 }; 							
static zTNetTimeout		netTimeoutIPX = { 1000, 1000, 250, 500 };						
static zTNetTimeoutPtr	netTimeout[2] = { &netTimeoutIPX, &netTimeoutTCP };



static zTNetSocketPtr  netDGramUSock[2]={ NULL, NULL };			

// processes, threads and windows
static HWND			netMsgWinHandle;
static HANDLE		netThread;
static zDWORD		netThreadID;
static zBOOL 		netPendingAccepts=FALSE;					
static HANDLE		netSocketMutex=NULL;						

static zDWORD			netThreadProc(zDWORD Param);
static void				netKillLinkedList(zTNetBufferPtr List);

// error-funtcions
static void			netSetError(char *fName, zTNetSocketPtr Sock);
static void			netSetErrorEx(char *fName, zDWORD ErrNo);
static void			netClrError();
static char*		netLastErrorString=NULL;						
static zDWORD		netLastError=0;

// asnychronous network-calls
static zBOOL			netWaitForAsyncResult(zWORD Message, zDWORD TimeOut, HANDLE rHandle);
static void				netASyncClear();
static volatile zWORD	netAsyncMsg=0;						


static volatile zWORD	netAMsgResult;

static zBOOL			netActive=FALSE;								





#define U
#define V
#define AGI

// umschreiben!!!
static void Net2SockAddr(zTNetAddressPtr NetAddr, PSOCKADDR SockAddr)
{ __asm {
	U	  mov	esi,[NetAddr]										  
	V	  mov	edi,[SockAddr]										  
	U AGI mov	eax,[esi]											  
	V	  mov	ebx,[esi+4] 										  
	U	  test	eax,0FFFEh											  
	V	  jnz	n2sa_quit											  
	U	  cmp	al,1												  
	V	  je	n2sa_tcpip											  
	U	  mov	al,6  								  
	V	  mov	[edi+4],ebx 										  
	U	  xor	ebx,ebx 											  
	V	  mov	ecx,[esi+8] 										  
	U	  mov	bh,[esi+12] 										  
	V	  mov	[edi],eax											  
	U	  mov	bl,[esi+13] 										  
	V	  mov	[edi+8],ecx 										  
	U	  mov	[edi+12],ebx										  
	V	  jmp	n2sa_quit											  
n2sa_tcpip:
	U	  mov	al,[esi+3]											  
	V	  mov	bl,[esi+5]											  
	U	  mov	bh,[esi+4]											  
	V	  mov	ah,[esi+2]											  
	U	  shl	eax,16												  
	V	  xor	ecx,ecx 											  
	U	  shl	ebx,16												  
	V	  mov	al,2 								  
	U	  mov	bl,[esi+7]											  
	V	  mov	[edi+8],ecx 										  
	U	  mov	bh,[esi+6]											  
	V	  mov	[edi+12],ecx										  
	U	  mov	[edi+4],ebx 										  
	V	  mov	[edi],eax											  
n2sa_quit:
}}
#undef U
#undef V
#undef AGI






static void Sock2NetAddr(PSOCKADDR SockAddr, zTNetAddressPtr NetAddr)
{
	ENTER_PROC(Sock2NetAddr);
	if (SockAddr->sa_family==AF_INET)
	{
		NetAddr->Protocol=zNET_PROTOCOL_TCP; 							
		NetAddr->INET.Port=ntohs(((PSOCKADDR_IN)SockAddr)->sin_port);
		NetAddr->INET.IP=ntohl(((PSOCKADDR_IN)SockAddr)->sin_addr.s_addr); 
		EXIT_PROC();
	}
	else if (SockAddr->sa_family==AF_IPX)
	{
		NetAddr->Protocol=zNET_PROTOCOL_IPX; 							
		NetAddr->IPX.Socket=ntohs(((PSOCKADDR_IPX)SockAddr)->sa_socket);
		memcpy(NetAddr->IPX.Net, ((PSOCKADDR_IPX)SockAddr)->sa_netnum, 10);  
		EXIT_PROC();
	}
	else
	{
		zERR_ASSERTT(0, "Unknown address family");
		EXIT_PROC();
	}	
	
	EXIT_PROC()
}

zBOOL __inline netCheckTag(zNET_HANDLE Handle)
{
	return (*((zDWORD *)Handle) == 0x4B434F53);
}



#ifdef _DEBUG

void zERR_ASSERT_NETADDRESS(zTNetAddressPtr Addr, zBOOL reqAddr, zBOOL reqPort)
{
	ENTER_PROC(zERR_ASSERT_NETADDRESS);
	zERR_ASSERTT(Addr, "Illegal network address (NULL pointer)");
	zERR_ASSERTT((Addr->Protocol == zNET_PROTOCOL_TCP) || (Addr->Protocol == zNET_PROTOCOL_IPX), "Illegal network protocol (neither TCP nor IPX)");
	if (Addr->Protocol == zNET_PROTOCOL_TCP)
	{
		if (reqAddr) zERR_ASSERTT(Addr->INET.IP,   "0.0.0.0 is an illegal IP address");
		if (reqPort) zERR_ASSERTT(Addr->INET.Port, "0 is an illegal IP port");
	}
	else if (Addr->Protocol == zNET_PROTOCOL_IPX)
	{
		zBYTE  NULL_Node[6] = { 0,0,0,0,0,0 };
		if (reqAddr) zERR_ASSERTT(memcmp(Addr->IPX.Node, NULL_Node, 6), "000000000000h is an illegal IPX node address");
		if (reqAddr) zERR_ASSERTT(Addr->IPX.Socket, "0000h is an illegal IPX socket number");
	}	
}
void zERR_ASSERT_NET_HANDLE(FHANDLE Handle)
{
	ENTER_PROC(zERR_ASSERT_NET_HANDLE);
	zERR_ASSERTT(Handle, "The specified network handle is a NULL pointer");
	zERR_ASSERTT(netCheckTag(Handle), "The specified handle is not a socket handle");	
	EXIT_PROC();
}
#else	

#define zERR_ASSERT_NETADDRESS(a, b, c)((void)(0))
#define zERR_ASSERT_NET_HANDLE(a)((void)(0))

#endif	



static zTSockError wsErr[]={
	{ zNETERR_NOERROR,			0,					   FALSE, "No error" },
	{ zNETERR_NOINIT,			WSANOTINITIALISED,	   FALSE,"You must call WSAStartup() first." },
	{ zNETERR_NOSUPPORT, 		WSAEAFNOSUPPORT,	   FALSE,"Address family not supported" },
	{ zNETERR_WOULDBLOCK,		WSAEWOULDBLOCK, 	   FALSE,"Call would block socket" },
	{ zNETERR_INPROGRESS,		WSAEINPROGRESS, 	   FALSE,"Blocking call is in progress" },
	{ zNETERR_HOSTNOTFOUND,		WSAHOST_NOT_FOUND,	   FALSE,"Host not found" },
	{ zNETERR_TRYAGAIN,			WSATRY_AGAIN,		   FALSE,"Try again" },
	{ zNETERR_NORECOVERY,		WSANO_RECOVERY, 	   FALSE,"Unrecoverable error" },
	{ zNETERR_NODATA,			WSANO_DATA, 		   FALSE,"No data found" },
	{ zNETERR_NOSOCK,			WSAEMFILE,			   FALSE,"No more socket descriptors" },
	{ zNETERR_NOBUFS, 			WSAENOBUFS, 		   FALSE,"Memory missing. Too many sockets open?" },
	{ zNETERR_PROTNOSUPPORT,	WSAEPROTONOSUPPORT,    FALSE,"Protocol not supported" },
	{ zNETERR_PROTOTYPE_ILLEGAL,WSAEPROTOTYPE,		   FALSE,"Illegal protocol for socket" },
	{ zNETERR_SOCKNOSUPPORT,	WSAESOCKTNOSUPPORT,    FALSE,"Socket not supported with this address family" },
	{ zNETERR_ADDRINUSE, 		WSAEADDRINUSE,		   FALSE,"Addressstill used by another socket." },
	{ zNETERR_ISCONNECTED,		WSAEISCONN, 		   FALSE,"Socket is already connected" },
	{ zNETERR_ADDRNOTAVAIL,		WSAEADDRNOTAVAIL,	   FALSE,"Address not available" },
	{ zNETERR_CONNECTIONREFUSED,WSAECONNREFUSED,	   FALSE,"Connection refused" },
	{ zNETERR_NETUNREACHABLE,	WSAENETUNREACH, 	   FALSE,"Network is unreachable" },
	{ zNETERR_TIMEOUT,			WSAETIMEDOUT,		   FALSE,"Time out" },
	{ zNETERR_ACCESS,			WSAEACCES,			   FALSE,"Access to address denied" },
	{ zNETERR_INTERUPTED,		WSAEINTR,			   FALSE,"Network call canceled" },
	{ zNETERR_MSGSIZE,			WSAEMSGSIZE,		   FALSE,"Datagram size too large" },
	{ zNETERR_HOSTUNREACHABLE,	WSAEHOSTUNREACH,	   FALSE,"Host unreachable" },
	{ zNETERR_NOTSOCK,			WSAENOTSOCK,		   FALSE,"This is not a socket." },
	{ zNETERR_NETDOWN,			WSAENETDOWN,		   TRUE, "Access to the network failed." },
	{ zNETERR_NETRESET,			WSAENETRESET,		   TRUE, "Network has reset connection" },
	{ zNETERR_NOTCONNECTED,		WSAENOTCONN,		   TRUE, "Socket not connected" },
	{ zNETERR_SHUTDOWN,			WSAESHUTDOWN,		   TRUE, "Socket has been shut down" },
	{ zNETERR_CONNABORTED,		WSAECONNABORTED,	   TRUE, "Connection was aborted due to timeout or failure." },
	{ zNETERR_CONNRESET, 		WSAECONNRESET,		   TRUE, "Connection reset by remote host" }
};


#define WS_ERRORS	(sizeof(wsErr)/sizeof(zTSockError))

static zTCustomError customErr[]={
	{ zNETERR_ILLEGALHANDLE,	"Illegal zNET_HANDLE" },
	{ zNETERR_CLOSED,		"zNET_HANDLE has closed" },
	{ zNETERR_ILLEGALHOST,	"Illegal host name" }
};


#define CUSTOM_ERRORS (sizeof(customErr)/sizeof(zTCustomError))

void netDumpSocketLL()
{
	zTNetSocketPtr c=&netSocketList;
	ENTER_PROC(netDumpSocketLL);
	WaitForSingleObject(netSocketMutex, INFINITE);			  
	TRACE("NET: -- Sockets dump ------------------");
	while (c)
	{
		TRACE("NET: Socket %d This %u Next %u", c->socket, c, c->next);
		c=(zTNetSocket*)c->next;
	}
	TRACE("");
	ReleaseMutex(netSocketMutex);								
}


























/////////////////////////////////////////////////////////////////////////////////
// Init und Deinit
/////////////////////////////////////////////////////////////////////////////////






///
// netInit
// Initialising the network
///
void netInit()
{
	ENTER_PROC(netInit);
	if (!netEnable) EXIT_PROC();

#ifdef USENET

	zERR_MESSAGE(1,0,"B: NET: zengin-network protocol-version "+zSTRING(zNET_VERSION));

	WSADATA WSAData;
	zWORD	wVersionRequired=MAKEWORD(1,1);	

	// checking some variable-contents
	#ifndef NDEBUG
	zERR_ASSERTT(sizeof(SOCKET)==sizeof(zDWORD), "Wrong size of SOCKET");
	zERR_ASSERTT(INADDR_ANY==0, "INADDR_ANY is not 0");
	zERR_ASSERTT((AF_IPX==PF_IPX) && (AF_INET==PF_INET), "AF_IPX==PF_IPX && AF_INET==PF_INET failed");
	zERR_ASSERTT(offsetof(zTNetAddress, Protocol)== offsetof(SOCKADDR_IN,  sin_family),"Errors in struct zTNetAddress (Protocol/INET).");
	zERR_ASSERTT(offsetof(zTNetAddress, Protocol)== offsetof(SOCKADDR_IPX, sa_family),"Errors in struct zTNetAddress (Protocol/IPX).");
	zERR_ASSERTT(offsetof(zTNetAddress, INET.Port)== offsetof(SOCKADDR_IN,  sin_port),"Errors in struct zTNetAddress (Port/INET).");
	zERR_ASSERTT(offsetof(zTNetAddress, INET.IP)== offsetof(SOCKADDR_IN,  sin_addr),"Errors in struct zTNetAddress (IP/INET).");
	zERR_ASSERTT(offsetof(zTNetAddress, IPX.Net)== offsetof(SOCKADDR_IPX, sa_netnum),"Errors in struct zTNetAddress (Net/IPX).");
	zERR_ASSERTT(offsetof(zTNetAddress, IPX.Node)== offsetof(SOCKADDR_IPX, sa_nodenum),"Errors in struct zTNetAddress (Node/IPX).");
	zERR_ASSERTT(offsetof(zTNetAddress, IPX.Socket) == offsetof(SOCKADDR_IPX, sa_socket),"Errors in struct zTNetAddress (Socket/IPX).");				 
	#endif

	// Windows-Sockets initialisieren
	if (WSAStartup(wVersionRequired, &WSAData))
	{
		zERR_WARNING("B: zNET_WIN32: WSAStartup failed: no network-support");
		EXIT_PROC();
	}

	// Version checken
	if (WSAData.wVersion!=wVersionRequired)
	{
		zERR_WARNING("B: zNET_WIN32: Unsupported WinSock version.");
		WSACleanup(); // Einsatz von Sockets wieder beenden
		EXIT_PROC();
	}

	// initialisieren
	gethostname(netLocalHost, sizeof(netLocalHost)-1);
	
	// Socket-Mutex erzeugen
	netSocketMutex		=	CreateMutex(NULL, FALSE, NULL);
	
	// Erzeuge einen Thread
	// Die Callback-Funktion "netThreadProc" erzeugt dann ein Fenster,
	// welches die WinSock-Nachrichten bearbeitet.
	HANDLE				createThreadEvent;
	createThreadEvent	= CreateEvent(NULL, FALSE, FALSE, NULL);
	netThread			= CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)netThreadProc, (void *)createThreadEvent, 0, &netThreadID);
	SetThreadPriority	(netThread, THREAD_PRIORITY_TIME_CRITICAL);
	WaitForSingleObject	(createThreadEvent, INFINITE);		
	CloseHandle			(createThreadEvent);

	// Alle Datagram-Protokolle (IPX und UDP) initialisieren
	for (int i=0; i<zNET_PROTOCOLS; i++)
	{
		zTNetSocketPtr	netSocket;
		SOCKADDR	DGRAM_Addr;
		int 		DGRAM_AddrLen;
		memset(&DGRAM_Addr,0,sizeof(DGRAM_Addr));
		DGRAM_AddrLen	=	sizeof(DGRAM_Addr); 																
		netSocket		=	(zTNetSocket*)sysAlloc(sizeof(zTNetSocket));				
		
		// einen neuen Socket anlegen
		netSocket->socket		=	socket(netAddrFam[i], SOCK_DGRAM, netPacketProto[i]);
		if (netSocket->socket==INVALID_SOCKET) // ... und ueberpruefen
		{ 
			netSetError("netCreateDatagramSocket", netSocket); 		
			sysFree(netSocket);								
			continue;
		}
		netDGramUSock[i]=netSocket; // alles ok: Socket zuweisen

		// Status des Sockets überprüfen
		WSAAsyncSelect(netSocket->socket, netMsgWinHandle, WINMSG_DGRAM, FD_WRITE | FD_READ); 

		// Socket-Optionen setzen
		int	result=TRUE;
		setsockopt(netSocket->socket, SOL_SOCKET, SO_BROADCAST, (char *)&result, sizeof(result));
		memcpy(netSocket	->tag			,"SOCK", sizeof("SOCK"));
		netSocket			->mode			=zNET_SOCKMODE_LISTENPKT;					
		netSocket			->maxInBuffers	=zNET_MAX_BUFFERS; 				

		// socket an die Datagram-Adresse binden
		DGRAM_Addr.sa_family			=netAddrFam[i];							
		bind(netSocket->socket, &DGRAM_Addr, sizeof(DGRAM_Addr));
		getsockname(netSocket->socket, &DGRAM_Addr, &DGRAM_AddrLen); 
		Sock2NetAddr(&DGRAM_Addr, &netSocket->LocalAddr); 			

		zERR_MESSAGE(11, 0, "B: (netInit) Socket for protocol "+zSTRING(i)+" created and initialised.");

		// und in die Socketliste einfügen
		netAddSocket(netSocket);							
	}

	// Netzwerk korrekt initialisiert
	netActive=TRUE; 													
#endif

	EXIT_PROC();
}





void netExit()
{
	ENTER_PROC(netExit);
	if (!netActive) EXIT_PROC();
	
	// Alle datagram-sockets schließen
	for (int i=0; i<zNET_PROTOCOLS; i++)
		if (netDGramUSock[i]) 
			netClose(netDGramUSock[i]);

	// alle restlichen sockets ebenfalls schließen und eine Warnung ausgaben
	zTNetSocketPtr sock_ptr = (zTNetSocket*)netSocketList.next;
	while (sock_ptr)
	{
		zTNetSocketPtr nextsock_ptr=(zTNetSocket*)sock_ptr->next;
		zERR_WARNING("B: (netExit) A socket was not closed on network-exit.");
		netClose(sock_ptr);
		sock_ptr=nextsock_ptr;
	}

	// Einsatz der Sockets beenden
	WSACleanup();

	// Mutex- und Thread-Handles schließen
	CloseHandle(netSocketMutex);
	CloseHandle(netThread);
	
	netActive=FALSE;	

	EXIT_PROC();
}

















/////////////////////////////////////////////////////////////////////////////////
// Senden und Empfangen
/////////////////////////////////////////////////////////////////////////////////




///
// Ein Datagram-Paket verschicken
///
zBOOL netSend(zTNetAddress *destination, void *buffer, int len, zNET_HANDLE handle)
{
	ENTER_PROC(netSend);

	zTNetSocketPtr	sock_ptr;
	SOCKADDR	destAddr;
	
	if (!handle) handle = netDGramUSock[destination->Protocol];
	sock_ptr = (zTNetSocketPtr)handle;

	// variablen überprüfen
	zERR_ASSERT(buffer);
	zERR_ASSERTT(len<=zNET_MAX_DGRAMSIZE, "B: (netSend) DGRAM-packet exceeds zNET_MAX_DGRAMSIZE");
	zERR_ASSERTT(sock_ptr, "B: (netSend) Wrong socket. Unsupported protocol?");
	if (!len) RETURN(TRUE);
	if (!sock_ptr) RETURN(TRUE);
	
	Net2SockAddr(destination, &destAddr);

	// nun kann das paekchen verschickt werden
	int result;
	result=sendto(sock_ptr->socket, (char*)buffer, len, 0, &destAddr, sizeof(destAddr));
	
	if (result!=len) // Ist ein Fehler aufgetreten?
	{		
		if ((result==SOCKET_ERROR) && (WSAGetLastError()!=WSAEWOULDBLOCK)) 
		{
			netSetError("netSend", sock_ptr);
			RETURN(FALSE);
		}
		zERR_WARNING("B: (netSend) Not all bytes of datagram were send");
		RETURN(FALSE);
	}	
	RETURN(TRUE);
}


///
// Ein Datagram-Paket auslesen
///
zTNetPacketPtr netRecv(zNET_HANDLE handle)
{
	ENTER_PROC(netRecv);

	zTNetSocketPtr	netSocket	=	(zTNetSocketPtr)handle;
	zTDgramInBufferPtr	buffer;

	if (!netSocket || (netSocket->mode>=zNET_SOCKMODE_NUM) || (!netCheckTag(handle)))
	{
		netSetErrorEx("netRecv", zNETERR_ILLEGALHANDLE);
		RETURN(0);
	}
	
	WaitForSingleObject(netSocketMutex, INFINITE);

	// So, erstmal alten Buffer wieder freigeben
	if (netSocket->bufferToKill)
	{
		sysFree(netSocket->bufferToKill);
		netSocket->bufferToKill=0;
	}

	// Da isses ja, das Paket ...
	buffer=(zTDgramInBufferPtr)netSocket->inHead;
	if (!buffer) // ... oder doch nicht?
	{
		ReleaseMutex(netSocketMutex);						
		RETURN(0); // Nagut, nix gefunden. Und Tschuess!
	}

	// Päkchen wurde ausgelesen: Buffer (logisch) freigeben
	netSocket->bufferInfo.inPackets--;
	netSocket->bufferInfo.inBytes -= buffer->packet.size;
	netSocket->inHead=(zTNetBuffer*)buffer->next;
	zERR_ASSERT(netSocket->bufferInfo.inBytes >= 0);
	zERR_ASSERT(netSocket->bufferInfo.inPackets >= 0);
	netSocket->bufferToKill=buffer; // phyiskalische Freigabe beim naechsten Aufruf

	ReleaseMutex(netSocketMutex);
	
	RETURN(&buffer->packet);
}




///
// Ein paar Daten auf den Stream schreiben
///
zBOOL netWrite(zNET_HANDLE stream, void* buffer, int len, zBOOL wait)
{
	ENTER_PROC(netWrite);
	zTNetSocketPtr netSocket=(zTNetSocketPtr)stream;

	// so, erstmal wieder die variablen abchecken
	zERR_ASSERT_STRICT(stream);
	zERR_ASSERT_STRICT(buffer);
	zERR_ASSERTT(netSocket->mode==zNET_SOCKMODE_CONNECTED, "B: (netWrite) netSocket ist not connected!");
	// zERR_zERR_ASSERT_NET_HANDLE(Str);

	if (!netSocket || (netSocket->mode>=zNET_SOCKMODE_NUM) || (!netCheckTag(stream)))
	{
		netSetErrorEx("netWrite", zNETERR_ILLEGALHANDLE);		
		RETURN(FALSE);
	}
	else if (netSocket->closed)								
	{
		netSetErrorEx("netWrite", zNETERR_CLOSED);			
		RETURN(FALSE);
	}

	// und ab gehts ins Internet (oder sonstwo hin)
	int result;
	while (len>0)
	{
		result = send(netSocket->socket, (char*)buffer, len, 0); 			
		if (result==len) RETURN(TRUE);

		if ((result==SOCKET_ERROR) && (WSAGetLastError()==WSAEWOULDBLOCK)) 
		{
			RETURN(wait);
		}
		else if (result==SOCKET_ERROR) 								
		{
			netSetError("netWrite", netSocket);				
			RETURN(FALSE);
		}
		else 
		{
			buffer = (void*) (((LPBYTE)buffer) + result);
			len-=result;									
		}
	}
	RETURN(TRUE);
}


///
// Mal schaun, ob da was auf dem Stream liegt
///
int netRead(zNET_HANDLE stream, void *buffer, int maxLen)
{
	ENTER_PROC(netRead);

	zTNetSocketPtr	netSocket	=	(zTNetSocketPtr)stream;
	zTStreamBufferPr	readBuffer;											
	
	zERR_ASSERT(stream);
	zERR_ASSERT(buffer);
	zERR_ASSERTT(netSocket->mode==zNET_SOCKMODE_CONNECTED, "B: (netRead) Stream-Handle is noch connected.");

	WaitForSingleObject(netSocketMutex, INFINITE);			

	if (!netSocket || (netSocket->mode>=zNET_SOCKMODE_NUM) || (!netCheckTag(stream)))
	{
		netSetErrorEx("netRead", zNETERR_ILLEGALHANDLE);		
		ReleaseMutex(netSocketMutex);						
		RETURN(-1);
	}

	// Dann mal her mit den Daten ...
	int		readLen;
	int		totalLen=0;
	int		bufferMaxSize;
	zBYTE*	bufferPtr;

	while (maxLen && ((readBuffer=(zTStreamBufferPr)netSocket->inHead)!=NULL))
	{
		bufferMaxSize = (readBuffer->size - readBuffer->skip);
		readLen= bufferMaxSize<maxLen ? bufferMaxSize : maxLen;
		bufferPtr = readBuffer->Data+readBuffer->skip;
		memcpy(buffer, bufferPtr, readLen);

		totalLen	+= readLen;
		maxLen		-= readLen;

		buffer = (void*) (((LPBYTE)buffer)+readLen);

		readBuffer->skip+=readLen; 									

		if (readBuffer->skip == readBuffer->size)
		{
			netSocket->inHead=(zTNetBuffer*)readBuffer->next; 						
			if (netSocket->inHead==NULL) netSocket->inTail=NULL;
			sysFree(readBuffer);								
		}
	}

	netSocket->bufferInfo.inBytes-=totalLen;
	zERR_ASSERT(netSocket->bufferInfo.inBytes >= 0);

	ReleaseMutex(netSocketMutex);							

	RETURN(totalLen);
}







/////////////////////////////////////////////////////////////////////////////////
// Listen und Connect
/////////////////////////////////////////////////////////////////////////////////


///
// Das Warten auf Datagram-Pakete aktivieren
///
zNET_HANDLE netListenPacket(zTNetAddressPtr server)
{
	ENTER_PROC(netListenPacket);

	zTNetSocketPtr netSocket;
	SOCKADDR  serverAddr;
	
	// socket erzeugen
	zERR_ASSERT(server);
	Net2SockAddr(server, &serverAddr);
	netSocket=(zTNetSocket*)sysAlloc(sizeof(zTNetSocket));
	memcpy(netSocket->tag, "SOCK", sizeof("SOCK"));						
	netSocket->socket=socket(netAddrFam[server->Protocol], SOCK_DGRAM, netPacketProto[server->Protocol]); 
	int result;
	setsockopt(netSocket->socket, SOL_SOCKET, SO_BROADCAST, (char *)&result, sizeof(result));
	
	// socket binden
	if ((netSocket->socket==INVALID_SOCKET) || 					
		(bind(netSocket->socket, &serverAddr, sizeof(serverAddr))==SOCKET_ERROR) ||
		(WSAAsyncSelect(netSocket->socket, netMsgWinHandle, WINMSG_DGRAM, FD_READ)))
	{
		netSetError("netListenPacket", netSocket); 					
		if (netSocket->socket) closesocket(netSocket->socket);
		sysFree(netSocket);									
		RETURN(0);// gescheitert
	}

	// hat geklappt...
	netSocket->mode=zNET_SOCKMODE_LISTENPKT;						
	netSocket->maxInBuffers=zNET_MAX_BUFFERS; 					
	memcpy(&netSocket->LocalAddr, server, sizeof(zTNetAddress));
	netAddSocket(netSocket);
	
	RETURN((zNET_HANDLE)netSocket);
}



///
// Auf dem Stream auf haufenweise Bytes warten
///

zNET_HANDLE netListenStream(zTNetAddressPtr server, LPCFUNCP acceptFunction)
{
	ENTER_PROC(netListenStream);
	
	zERR_ASSERT(acceptFunction);

	// socket erzeugen
	SOCKADDR	serverAddr;
	int 		serverAddrLen=sizeof(serverAddr);
	Net2SockAddr(server, &serverAddr);						
	zTNetSocketPtr	netSocket	=	(zTNetSocket*)sysAlloc(sizeof(zTNetSocket));					
	netSocket->socket	=	socket(netAddrFam[server->Protocol], SOCK_STREAM, netStreamProto[server->Protocol]); 

	// socket binden und aktivieren (listen)
	if ((netSocket->socket==INVALID_SOCKET) || 					
		(bind(netSocket->socket, &serverAddr, sizeof(serverAddr))==SOCKET_ERROR) ||
		(listen(netSocket->socket, 3)==SOCKET_ERROR) ||
		(WSAAsyncSelect(netSocket->socket, netMsgWinHandle, WINMSG_STREAM, FD_ACCEPT)))
	{
		netSetError("netListenStream", netSocket); 					
		if (netSocket->socket) closesocket(netSocket->socket);
		sysFree(netSocket);									
		RETURN(0);								
	}

	// hat geklappt ...
	getsockname(netSocket->socket, &serverAddr, &serverAddrLen);
	Sock2NetAddr(&serverAddr, &netSocket->LocalAddr);			
	netSocket	->	mode=zNET_SOCKMODE_LISTEN; 								
	netSocket	->	maxInBuffers=zNET_MAX_BUFFERS; 					
	netSocket	->	acceptFunction	=	acceptFunction;						
	memcpy(netSocket->tag, "SOCK", sizeof("SOCK"));						
	netAddSocket(netSocket);								

	RETURN((zNET_HANDLE)netSocket);
}


///
// Verbindung zu einem wartenden Stream-Socket herstellen
///
zNET_HANDLE netConnect(zTNetAddressPtr server)
{
	ENTER_PROC(netConnect);

	zTNetSocketPtr	netSocket;								
	SOCKADDR	clientAddr, serverAddr;								
	int 		serverAddrLen=sizeof(serverAddr), clientAddrLen=sizeof(clientAddr); 
		
	// sockert erzeugen
	Net2SockAddr(server, &serverAddr);
	memZeroSmall(&clientAddr, sizeof(clientAddr));
	clientAddr.sa_family=netAddrFam[server->Protocol];
	netSocket=(zTNetSocket*)sysAlloc(sizeof(zTNetSocket));
	memcpy(netSocket->tag, "SOCK", sizeof("SOCK"));
	netSocket->socket=socket(netAddrFam[server->Protocol], SOCK_STREAM, netStreamProto[server->Protocol]); 
	netASyncClear();
	
	// socket binden und verbindung aufbauen (connect)
	if ((netSocket->socket==INVALID_SOCKET) ||
		(bind(netSocket->socket, &clientAddr, sizeof(clientAddr))==SOCKET_ERROR) || 
		(WSAAsyncSelect(netSocket->socket, netMsgWinHandle, WINMSG_STREAM, FD_CONNECT | FD_READ | FD_WRITE)) ||
		((connect(netSocket->socket, &serverAddr, sizeof(serverAddr))==SOCKET_ERROR) && (WSAGetLastError()!=WSAEWOULDBLOCK)) ||
		(netWaitForAsyncResult(WINMSG_CONNECTED, netTimeout[server->Protocol]->Connect, NULL)==FALSE))
	{
		if (WSAGetLastError()==WSAEWOULDBLOCK) WSASetLastError(WSAETIMEDOUT);
		netSetError("netConnect", netSocket);
		if (netSocket->socket) closesocket(netSocket->socket);
		sysFree(netSocket);

		RETURN(0);
	}

	// hat gelappt ..
	getpeername(netSocket->socket, &serverAddr, &serverAddrLen);
	Sock2NetAddr(&serverAddr, &netSocket->RemoteAddr);
	getsockname(netSocket->socket, &clientAddr, &clientAddrLen);
	Sock2NetAddr(&serverAddr, &netSocket->LocalAddr);
	netSocket->mode=zNET_SOCKMODE_CONNECTED;
	netSocket->maxInBuffers=zNET_MAX_BUFFERS;
	netAddSocket(netSocket);

	RETURN((zNET_HANDLE)netSocket);
}







/////////////////////////////////////////////////////////////////////////////////
// Handles und Sockets
/////////////////////////////////////////////////////////////////////////////////



///
// Schließen eines Socket-Handles
///
zBOOL netClose(zNET_HANDLE handle)
{	
	ENTER_PROC(netClose);

	if (!handle) RETURN(FALSE);

	zTNetSocketPtr netSocket=(zTNetSocketPtr)handle;
	zERR_ASSERT(handle);
	zERR_ASSERT(netSocket->mode < zNET_SOCKMODE_NUM);
	
	if (!netSocket || (netSocket->mode>=zNET_SOCKMODE_NUM) || (!netCheckTag(handle)))
	{
		netSetErrorEx("netClose", zNETERR_ILLEGALHANDLE);		
		RETURN(FALSE);
	}

	WaitForSingleObject(netSocketMutex, INFINITE);

	closesocket(netSocket->socket);
	
	// Socket vor dem entfernten Socket suchen
	zTNetSocketPtr findSocket = &netSocketList;
	while ((findSocket->next) && (findSocket->next!=netSocket)) 	
		findSocket=(zTNetSocket*)findSocket->next;

	if (!findSocket->next) // socket nicht gefunden?
	{
		ReleaseMutex(netSocketMutex);
		netSetErrorEx("netClose", zNETERR_ILLEGALHANDLE);
		RETURN(FALSE);
	}

	// gefunden. Dann "netSocket" entfernen
	findSocket->next=netSocket->next;
	netKillLinkedList(netSocket->inHead);
	if (netSocket->bufferToKill) sysFree(netSocket->bufferToKill);
	memZero(handle, sizeof(zTNetSocket));
	sysFree(handle);
	ReleaseMutex(netSocketMutex);

	RETURN(TRUE);	
}


///
// Überprüfen ob ein socket-handle geschlossen ist
///
zBOOL netIsHandleClosed(zNET_HANDLE handle)
{
	ENTER_PROC(netIsHandleClosed);

	zERR_ASSERT(handle);

	zTNetSocketPtr	netSocket=(zTNetSocketPtr)handle;
	SOCKADDR	sockAddr;
	int			sockAddrLen=sizeof(sockAddr);
	
	if (!netSocket->closed)
	{
		int result = getpeername(netSocket->socket, &sockAddr, &sockAddrLen);
		if (result==SOCKET_ERROR) netSetError("netIsHandleClosed", netSocket);		
		RETURN(FALSE);
	}
	else
	{
		RETURN(TRUE);
	}
	
}


///
// Abfrage des Standard-Datagram-Handles
///
zNET_HANDLE netGetPacketHandle(zDWORD protocol)
{
	ENTER_PROC(netGetPacketHandle);

	zERR_ASSERTT(protocol < zNET_PROTOCOLS, "B: (netGetPacketHandle) Unknown protocol.");

	RETURN((zNET_HANDLE)netDGramUSock[protocol]);
}





/////////////////////////////////////////////////////////////////////////////////
// Konvertierungs- und Databasefunktionen
/////////////////////////////////////////////////////////////////////////////////


///
// den Hostnamen aus der Adresse ermitteln
///
char *netGetHostName(zTNetAddressPtr addr)
{
	ENTER_PROC(netGetHostName);

	zBYTE		hostBuffer[MAXGETHOSTSTRUCT];
	SOCKADDR	hostAddr;
	PHOSTENT	inf	=	(PHOSTENT)hostBuffer;	
		
	if (!addr) RETURN(0);

	Net2SockAddr(addr, &hostAddr);
	netASyncClear();
	HANDLE task = WSAAsyncGetHostByAddr(netMsgWinHandle, WINMSG_GETHOSTNAME, ((char *)&hostAddr)+netAddrDataIdx[addr->Protocol], netAddrDataLen[addr->Protocol], netAddrFam[addr->Protocol], (char *)inf, MAXGETHOSTSTRUCT);

	if (!task)		
	{
		zBOOL result = netWaitForAsyncResult(WINMSG_GETHOSTNAME, netTimeout[addr->Protocol]->getHostName, task);
		if (!result)
		{
			netSetError("netGetHostName", NULL);				
			RETURN(0);
		}
	}

	RETURN(inf->h_name);
}


///
// Die Adresse aus dem Namen des Hosts ermitteln
///
zTNetAddressPtr netGetHostAddr(char* name)
{	
	static zTNetAddress RetAddr={ zNET_PROTOCOL_TCP, { 0, 0 } };
	ENTER_PROC(netGetHostAddr);

	zBYTE		hostBuffer[MAXGETHOSTSTRUCT];					  	
	PHOSTENT	hInf	=	(PHOSTENT)hostBuffer; 							  	
	
	if (!name)
	// mmmh, was soll ich mit einem leeren Namen?
	{
		netSetErrorEx("netGetHostAddr", zNETERR_ILLEGALHOST);	
		RETURN(0);
	}

	if ((RetAddr.INET.IP=inet_addr(name))!=INADDR_NONE) 		  	
	{
		RetAddr.INET.IP=ntohl(RetAddr.INET.IP); 						
		RETURN(&RetAddr);
	}

	netASyncClear();										  
	HANDLE	task	= WSAAsyncGetHostByName(netMsgWinHandle, WINMSG_GETHOSTIP, name, (char *)hInf, MAXGETHOSTSTRUCT);
	zBOOL	result	= netWaitForAsyncResult(WINMSG_GETHOSTIP, netTimeout[zNET_PROTOCOL_TCP]->getHostAddress, task);

	if (!result)
	{
		netSetError("netGetHostAddr", NULL);				
		RETURN(0);
	}

	RetAddr.INET.IP=ntohl(*((LPDWORD)hInf->h_addr_list[0]));

	RETURN(&RetAddr);
}



///
// Ermittle den Port eines Standard-Internet-Services anhand seines Namens
///
zDWORD netGetServicePort(char *Name, int Protocol)
{
	static char *protName[3]={ "udp", "tcp", NULL };		  
	ENTER_PROC(netGetServicePort);

	zBYTE		serviceBuffer [MAXGETHOSTSTRUCT];					  	
	LPSERVENT	sInf	= (LPSERVENT)serviceBuffer;	
	zERR_ASSERTT(Protocol<3, "B: (netGetServicePort) Unknown protocol.");
	
	netASyncClear();
	HANDLE	task = WSAAsyncGetServByName(netMsgWinHandle, WINMSG_GETSERVICE, Name, protName[Protocol], (char *)sInf, MAXGETHOSTSTRUCT);
	if (!task)
	{ 
		netSetError("netGetServicePort", NULL); 
		RETURN(0);
	} 

	zBOOL result = netWaitForAsyncResult(WINMSG_GETSERVICE, netTimeout[zNET_PROTOCOL_TCP]->getService, task);
	if (!result)
	{
		netSetError("netGetServicePort", NULL);
		RETURN(0);
	}
	
	RETURN(ntohs(sInf->s_port));
}


///
// convert an adress to a readable string
///
char *netAddrToString(zTNetAddressPtr addr, zBOOL with_socket)
{
	static char addrStr[64];
	ENTER_PROC(netAddrToString);
	
	zERR_ASSERTT(addr, "B: (netAddrToString) Address pointer is 0");
	zERR_ASSERTT((addr->Protocol==zNET_PROTOCOL_TCP) || (addr->Protocol==zNET_PROTOCOL_IPX), "Unknown network protocol");

	if (addr->Protocol==zNET_PROTOCOL_TCP)
	{
		sprintf(addrStr, "%u.%u.%u.%u", (addr->INET.IP>>24) & 0xFF, (addr->INET.IP>>16) & 0xFF, (addr->INET.IP>>8) & 0xFF, addr->INET.IP & 0xFF);
		if (with_socket) sprintf(addrStr+strlen(addrStr), " port %u", addr->INET.Port);
	}
	else if (addr->Protocol==zNET_PROTOCOL_IPX)
	{
		for (int i=0; i<4; i++) 											
		{
			sprintf(addrStr+i*2, "%02X", addr->IPX.Net[i]);
		}
		sprintf(addrStr+8, ":");								
		for (i=0; i<6; i++) 											
		{
			sprintf(addrStr+i*2+9, "%02X", addr->IPX.Node[i]);
		}
		if (with_socket) sprintf(addrStr+strlen(addrStr), " socket %04Xh", addr->IPX.Socket); 
	}
	else strcpy(addrStr, "Unknown network address");		  
	
	RETURN(addrStr);
}


char *netGetLocalHost()
{
	ENTER_PROC(netGetLocalHost);

	RETURN(netLocalHost);
}









zTNetAddressPtr netGetRemoteAddr(zNET_HANDLE Handle)
{
	zTNetSocketPtr pHandle=(zTNetSocketPtr)Handle;					  
	ENTER_PROC(netGetRemoteAddr);
	zERR_ASSERTT(Handle, "Illegal network handle (NULL)");	  
	zERR_ASSERTT(pHandle->mode==zNET_SOCKMODE_CONNECTED, "netGetRemoteAddr() requires a connected socket");
	zERR_ASSERT_NET_HANDLE(Handle);
	RETURN(&pHandle->RemoteAddr);							  
}
zTNetAddressPtr netGetLocalAddr(zNET_HANDLE Handle)
{
	zTNetSocketPtr pHandle=(zTNetSocketPtr)Handle;					  
	ENTER_PROC(netGetLocalAddr);
	zERR_ASSERT_NET_HANDLE(Handle);
	zERR_ASSERTT((pHandle->mode==zNET_SOCKMODE_LISTEN) ||
		(pHandle->mode==zNET_SOCKMODE_LISTENPKT) ||
		(pHandle->mode==zNET_SOCKMODE_CONNECTED),
		"netGetRemoteAddr() requires a listening or connected socket");
	RETURN(&pHandle->LocalAddr);							  
}




zBOOL netGetProtocolSupported(int protocol)
{
	ENTER_PROC(netGetProtocolSupported);
	if (!netActive) RETURN(FALSE);							  
	if ((protocol!=zNET_PROTOCOL_IPX) && (protocol!=zNET_PROTOCOL_TCP)) RETURN(FALSE);
	RETURN(netDGramUSock[protocol]!=NULL);					  
}


void netSetTimeOut(int protocol, zTNetTimeout *Time)
{
	ENTER_PROC(netSetTimeOut);
	zERR_ASSERTT(Time!=NULL, "LPzTNetTimeout pointer is NULL");
	zERR_ASSERTT(protocol<zNET_PROTOCOLS, "Illegal network protocol");
	zERR_ASSERT(Time);
	memcpy(&netTimeout[protocol], Time, sizeof(zTNetTimeout)); 		  	
}


zTNetBufferInfo *netGetBufferInfo(zNET_HANDLE Handle)
{
	zTNetSocketPtr pHandle=(zTNetSocketPtr)Handle;					  
	ENTER_PROC(netGetBufferInfo);
	zERR_ASSERT_NET_HANDLE(Handle);
	RETURN(&pHandle->bufferInfo);
}
zBOOL netSetMaxInQueuePackets(zNET_HANDLE Handle, int NumPackets)
{
	zTNetSocketPtr pHandle=(zTNetSocketPtr)Handle;					
	ENTER_PROC(netSetMaxInQueuePackets);
	zERR_ASSERTT(Handle, "Illegal network handle (NULL)");		
	zERR_ASSERTT(NumPackets > 0, "The input queue for a zNET_HANDLE must be at least 1 packet");
	if ((Handle==NULL) || (NumPackets==0)) RETURN(FALSE);	
	WaitForSingleObject(netSocketMutex, INFINITE);			
	while (pHandle->maxInBuffers > NumPackets)
	{
		zTNetBufferPtr head=pHandle->inHead;						
		zERR_ASSERTT(head, "No head in inbuffer list, even though the max is reached");
		pHandle->bufferInfo.inPackets--;							
		pHandle->bufferInfo.inBytes -= ((zTDgramInBufferPtr)head)->packet.size;	
		pHandle->inHead=(zTNetBuffer*)head->next;						
		zERR_ASSERT(pHandle->bufferInfo.inPackets >= 0);
		zERR_ASSERT(pHandle->bufferInfo.inBytes >= 0);
		sysFree(head);										
	}
	pHandle->maxInBuffers=NumPackets;						
	ReleaseMutex(netSocketMutex);							
	RETURN(TRUE);
}
INLINE static void netASyncClear()
{
	netAsyncMsg=0;											
	netAMsgResult=0;										
}
static zBOOL netWaitForAsyncResult(zWORD Message, zDWORD TimeOut, HANDLE rHandle)
{
	zDWORD timeQuit=sysGetTime()+TimeOut;					
	zDWORD lastTime=0;										
	ENTER_PROC(netWaitForAsyncResult);
	while ((netAsyncMsg!=Message) && ((lastTime=sysGetTime())<timeQuit)) 
		sysEvent(); 												
	if (lastTime<timeQuit) RETURN(netAMsgResult==0);		
	if (rHandle) WSACancelAsyncRequest(rHandle);			
	WSASetLastError(WSAETIMEDOUT);							
	RETURN(FALSE);
}
static void netSetError(char *fName, zTNetSocketPtr Sock)
{
	static char  Uerror_text[64];							
	int 	wsaErr=WSAGetLastError();						
	zDWORD	netErr; 												
	ENTER_PROC(netSetError);
	for (netErr=0; netErr<WS_ERRORS; netErr++)				
	{
		if (wsErr[netErr].error_wsa==wsaErr) 						
		{
			netLastError=wsErr[netErr].error_id;			
			netLastErrorString=wsErr[netErr].error_text; 			
			if ((wsErr[netErr].disconnect) && (Sock!=NULL))	
				Sock->closed = TRUE;						
			break;											
		}
	}
	if (netErr==WS_ERRORS)									
	{
		sprintf(Uerror_text, "Unknown Error %u", wsaErr);	
		netLastError=zNETERR_UNKNOWN;						
		netLastErrorString=Uerror_text;						
	}
	TRACE_DEBUG("NET: %s failed: %s", fName, netLastErrorString);	
	EXIT_PROC();
}
static void netSetErrorEx(char *fName, zDWORD ErrNo)
{
	zDWORD	netErr; 												  
	ENTER_PROC(netSetErrorEx);
	netLastError=ErrNo; 											  
	for (netErr=0; netErr<CUSTOM_ERRORS; netErr++)			  
	{
		if (customErr[netErr].error_id==ErrNo)					
		{ netLastErrorString=customErr[netErr].error_text; break; }	  
	}
	TRACE("NET: %s failed: %s", fName, netLastErrorString); 		  	
}
INLINE void netClrError()
{
	ENTER_PROC(netClrError);
	netLastError=0;
	netLastErrorString=wsErr[0].error_text;	
}
int netGetLastError()
{
	int rError = netLastError;
	ENTER_PROC(netGetLastError);
	netLastError = 0;
	RETURN(rError);
}
char *netGetLastErrorString()
{
	char *rError = netLastErrorString;
	ENTER_PROC(netGetLastString);
	netLastErrorString = NULL;
	RETURN(rError);
}

static zDWORD netThreadProc(zDWORD Param)
{
	ENTER_PROC(netThreadProc);

	// create invisible window for handling winsock-messages
	netMsgWinHandle=CreateWindow("DDWinSock", "Winsock-Window", 0, 0, 0, 0, 0, NULL, NULL, hInstApp, NULL);
	SetEvent((HANDLE)Param);								  

	MSG msg;	
	while (GetMessage(&msg, netMsgWinHandle, 0, 0)) DispatchMessage(&msg);

	RETURN(0);
}

#define breakmsg  goto ExitWinSockMessage
static char *memstr(void *str, int Len)
{
	static char Buffer[16384];
	zBYTE *pStr = (zBYTE *)str;
	char *pBuf = Buffer;
	Buffer[0]=0;
	while ((Len-- > 0) && (strlen(Buffer)<16000))
	{
		sprintf(pBuf, "%02X", *pStr++);
		pBuf+=2;
	}
	*pBuf=0;
	return Buffer;
}
static INLINE zBOOL isFull(zTStreamBufferPr pBuf)
{
	return (pBuf->size >= zNET_TCP_BUFFERSIZE);
}
LRESULT CALLBACK netWindowProc(HWND hwnd, zUWORD msg, WPARAM wParam, LPARAM lParam)
{
	zWORD  wsaErr=WSAGETSELECTERROR(lParam); 						  
	zWORD  wsaEvent=WSAGETSELECTEVENT(lParam);				  
	ENTER_PROC(netWindowProc);
	if ((msg<WINMSG_MIN) || (msg>WINMSG_MAX)) RETURN(DefWindowProc(hwnd, msg, wParam, lParam));
	if (msg>=WINMSG_SIMPLE)									  
	{
		netAMsgResult=wsaErr;									
		netAsyncMsg=msg;										
		RETURN(0);
	}
	WaitForSingleObject(netSocketMutex, INFINITE);			  
	if (msg==WINMSG_STREAM)									  
	{
		zERR_MESSAGE(11, 0,"B: (netWindowProc) Receiving WINMSG_STREAM, Socket "+zSTRING((int)wParam)+", wsaErr "+zSTRING((int)wsaErr)+", wsaEvent "+zSTRING((int)wsaEvent));
		if (wsaEvent==FD_READ)									
		{
			zTStreamBufferPr  inBuf;									  
			zTNetSocketPtr readSock; 										  
			zLONG	  recvBytes;								  
			zERR_MESSAGE(11, 0,"B: (netWindowProc) WINMSG_STREAM::FD_READ");
			if ((readSock=netFindSock((SOCKET)wParam))==NULL) breakmsg;   
			inBuf=(zTStreamBufferPr)readSock->inTail;				
			if ((inBuf==NULL) || (isFull(inBuf)))			
			{
				inBuf=(zTStreamBuffer*)sysAlloc(sizeof(zTStreamBuffer)+zNET_TCP_BUFFERSIZE);
				if (readSock->inHead==NULL) 						
				{
					readSock->inHead=(zTNetBufferPtr)inBuf;		
					readSock->inTail=(zTNetBufferPtr)inBuf;		
					zERR_MESSAGE(11, 0,"B: (netWindowProc) Allocated new packet as sole entry in linked list");
				}
				else
				{
					readSock->inTail->next=inBuf;			
					readSock->inTail=(zTNetBufferPtr)inBuf;		
					zERR_MESSAGE(11, 0,"B: (netWindowProc) Allocated new at tail of linked list");
				}
			}
			recvBytes=recv((SOCKET)wParam, (char *)(inBuf->Data+inBuf->size), zNET_TCP_BUFFERSIZE-inBuf->size, 0);
			zERR_MESSAGE(11, 0,"B: (netWindowProc) Read "+zSTRING((int)recvBytes)+" zBYTEs at pos "+zSTRING((int)inBuf->size)+" in packet");
			if (recvBytes!=SOCKET_ERROR)
			{
				inBuf->size+=recvBytes;					
				readSock->bufferInfo.inBytes += recvBytes;			
			}
			zERR_MESSAGE(11, 0,"B: (netWindowProc) Total in input queue "+zSTRING((int)readSock->bufferInfo.inBytes));
		}
		else if (wsaEvent==FD_CLOSE)
		{
			zTNetSocketPtr closeSock;								  
			if ((closeSock=netFindSock((SOCKET)wParam))==NULL) breakmsg;  
			closeSock->closed=TRUE; 									  
		}
		else if (wsaEvent==FD_ACCEPT)
		{
			zTNetSocketPtr acceptSock;								  
			SOCKET	  newSocket;								  
			zTNetSocketPtr netSocket;								  
			SOCKADDR  newAddr;									  
			int 	  newAddrLen=sizeof(newAddr);				  
			if ((newSocket=accept((SOCKET)wParam, &newAddr, &newAddrLen))==INVALID_SOCKET) breakmsg;
			if ((acceptSock=netFindSock((SOCKET)wParam))==NULL) breakmsg; 
			WSAAsyncSelect(newSocket, netMsgWinHandle, WINMSG_STREAM, FD_READ | FD_WRITE | FD_CLOSE);
			netSocket=(zTNetSocket*)sysAlloc(sizeof(zTNetSocket)); 				
			netSocket->socket=newSocket;				
			netSocket->mode=zNET_SOCKMODE_ACCEPTING;			
			netSocket->maxInBuffers=acceptSock->maxInBuffers; 	
			netSocket->acceptFunction=acceptSock->acceptFunction; 		
			memcpy(netSocket->tag, "SOCK", sizeof("SOCK"));			
			Sock2NetAddr(&newAddr, &netSocket->RemoteAddr);
			netAddSocket(netSocket);					
			netPendingAccepts=TRUE; 								
		}
		else if (wsaEvent==FD_CONNECT)
		{
			netAMsgResult=HIWORD(lParam);					
			netAsyncMsg=WINMSG_CONNECTED;						
		}
	}
	else if (msg==WINMSG_DGRAM) 										
	{
		if (wsaEvent==FD_READ)								  
		{
			zTDgramInBufferPtr newInBuf;									
			zTNetSocketPtr readSock;									
			SOCKADDR	readAddr;									
			int		readAddrLen=sizeof(readAddr);				
			if ((readSock=netFindSock((SOCKET)wParam))==NULL) breakmsg;
			newInBuf=(zTDgramInBuffer*)sysAlloc(sizeof(zTDgramInBuffer)+zNET_MAX_DGRAMSIZE);	
			newInBuf->packet.size=recvfrom((SOCKET)wParam, (char *)newInBuf->packet.Data, zNET_MAX_DGRAMSIZE, 0, &readAddr, &readAddrLen);
			if ((newInBuf->packet.size==0) || (newInBuf->packet.size==SOCKET_ERROR))
			{
				sysFree(newInBuf);							
				breakmsg;
			}
			if (readSock->inHead==NULL)						
			{
				readSock->inHead=(zTNetBufferPtr)newInBuf;			
				readSock->inTail=(zTNetBufferPtr)newInBuf;			
			}
			else
			{
				readSock->inTail->next=newInBuf; 					
				readSock->inTail=(zTNetBufferPtr)newInBuf;			
			}
			readSock->bufferInfo.inPackets++;						
			readSock->bufferInfo.inBytes+=newInBuf->packet.size;		
#ifdef _DEBUG
			if (((readSock->bufferInfo.inPackets & 511)==0) && (readSock->bufferInfo.inPackets))
				TRACE("Packets are stacking up (%u now)", readSock->bufferInfo.inPackets);
#endif
			if (readSock->bufferInfo.inPackets > readSock->maxInBuffers)
			{
				zTNetBufferPtr head=readSock->inHead;				
				zERR_ASSERTT(head, "No head in inbuffer list, even though the max is reached");
				readSock->bufferInfo.inPackets--;					
				readSock->bufferInfo.inBytes-=((zTDgramInBufferPtr)head)->packet.size;
				readSock->inHead=(zTNetBuffer*)head->next; 						
				sysFree(head);								
				TRACE_DEBUG("NET: Warning! Discarding packet, input buffer full");
				zERR_ASSERT(readSock->bufferInfo.inPackets >= 0);
				zERR_ASSERT(readSock->bufferInfo.inBytes >= 0);
			}
			newInBuf->packet.timestamp=sysGetTime();				
			Sock2NetAddr(&readAddr, &newInBuf->packet.From);		
		}
	}
ExitWinSockMessage:
	ReleaseMutex(netSocketMutex); 									
	RETURN(0);
}
#undef breakmsg
void netAcceptPendingConnections()
{
	ENTER_PROC(netAcceptPendingConnections);

	zTNetSocketPtr acceptSock;									  	
	if (netPendingAccepts==FALSE) EXIT_PROC();

	WaitForSingleObject(netSocketMutex, INFINITE);			  
	while (1)
	{
		acceptSock=netFindSockByMode(zNET_SOCKMODE_ACCEPTING);		
		if (acceptSock==NULL) break;							
		zERR_ASSERTT(acceptSock->acceptFunction, "acceptFunction for socket is NULL");
		zERR_ASSERTT(acceptSock->mode==zNET_SOCKMODE_ACCEPTING, "SockMode isn't accepting (should be!)");
		// Call the user accept proc (but first release the mutex so the user can do network calls)
		acceptSock->mode=zNET_SOCKMODE_CONNECTED;					// Set flag now (for read/write functions)
		ReleaseMutex(netSocketMutex);							// Allow network code in callback
		acceptSock->acceptFunction(acceptSock); 							// Call user callback
		WaitForSingleObject(netSocketMutex, INFINITE);			// Re-aquire exclusive access
	}
	// We still have exclusive mode (so we know the linked list is up-to-date and valid) and we don't have
	netPendingAccepts=FALSE;								  
	ReleaseMutex(netSocketMutex);		
	
	EXIT_PROC();
}
static void netKillLinkedList(zTNetBufferPtr List)
{
	zTNetBufferPtr   killBuffer, killNow;							  
	ENTER_PROC(netKillLinkedList);
	killBuffer=List;										  
	while (killBuffer)										  
	{
		killNow=killBuffer; 											
		killBuffer=(zTNetBuffer*)killBuffer->next;							
		sysFree(killNow);										
	}	
	EXIT_PROC();
}




INLINE static void netAddSocket(zTNetSocketPtr newSock)
{
	ENTER_PROC(netAddSocket);

	zTNetSocketPtr pSocks		=	&netSocketList;							  
	SOCKET	  thisSocket	=	newSock->socket; 						  	

	while 
		(
		(pSocks->next) && 
		(((zTNetSocketPtr)pSocks->next)->socket < thisSocket)
		) 
		pSocks = (zTNetSocket*)pSocks->next; 										

	newSock->next = pSocks->next; 								  
	pSocks->next = newSock;								  	

	EXIT_PROC();
}




INLINE static zTNetSocketPtr netFindSock(SOCKET Sock)
{
	ENTER_PROC(netFindSock);

	zTNetSocketPtr pSocks=(zTNetSocket*)netSocketList.next;							
	
	while ((pSocks) && (pSocks->next) && (pSocks->socket < Sock))
		pSocks = (zTNetSocket*)pSocks->next;

	if (pSocks->socket != Sock)
	{
		RETURN(NULL);
	}
	RETURN(pSocks);
}
INLINE static zTNetSocketPtr netFindSockByMode(zBYTE Mode)
{
	ENTER_PROC(netFindSockByMode);

	zTNetSocketPtr pSocks=(zTNetSocket*)netSocketList.next;						  
	
	while ((pSocks) && (pSocks->next) && (pSocks->mode != Mode))		  
		pSocks = (zTNetSocket*)pSocks->next;
	if (pSocks->mode != Mode)	{ RETURN(NULL); }
	else						{ RETURN(pSocks); } 											
}
