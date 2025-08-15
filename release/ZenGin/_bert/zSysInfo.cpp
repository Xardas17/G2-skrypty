#include "zcore.h"
#include "zstring.h"
#include "zsysinfo.h"
#include "zrenderer.h"

zCSystemInfo::zCSystemInfo()
{
	osType			= OS_UNKNOWN;	
	cpuType			= CPU_UNKNOWN;	
	cpuSpeed		= 555;	
	memSize			= 123	*1024*1024;	
	graMemSize		= 33	*1024*1024;
	graName			. Clear();
	cpuID			. Clear();
	osServicePack	. Clear();
};

zCSystemInfo::~zCSystemInfo()
{	
};


void zCSystemInfo::AnalyseMemory()
{
	MEMORYSTATUS memInfo;
	GlobalMemoryStatus(&memInfo);
	this->memSize		= memInfo.dwTotalPhys;
	this->memAvailable	= memInfo.dwAvailPhys;
};

void zCSystemInfo::AnalyseCpu()
{
	// Get the processor speed info.
	HKEY hKey;
	LONG result = ::RegOpenKeyEx (HKEY_LOCAL_MACHINE,
		"Hardware\\Description\\System\\CentralProcessor\\0", 0, KEY_QUERY_VALUE, &hKey);
	// Check if the function has succeeded.
	if (result == ERROR_SUCCESS) 
	{
		char	data[1024];
		DWORD	dataSize = 1024;
		result = ::RegQueryValueEx (hKey, "~MHz", NULL, NULL, (LPBYTE)&data, &dataSize);			
		this->cpuSpeed = *((DWORD*)&data);
		
		dataSize = 1024;
		result = ::RegQueryValueEx (hKey, "VendorIdentifier", NULL, NULL, (LPBYTE)&data, &dataSize);
		this->cpuID = zSTRING(data);
	} 
	else zERR_FAULT("B: SYS: Failed to analyse CPU");

	// Make sure to close the reg key

	RegCloseKey (hKey);

}

void zCSystemInfo::AnalyseOs()
{
	OSVERSIONINFO osInfo;
	osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&osInfo))
	{
		this->osServicePack = zSTRING(osInfo.szCSDVersion);
		switch(osInfo.dwPlatformId)
		{
			case VER_PLATFORM_WIN32s: 
				this->osType = OS_WINDOWS_3_1;			// 3.1
				break;
			case VER_PLATFORM_WIN32_WINDOWS:		
				if (osInfo.dwMinorVersion < 10)
						this->osType = OS_WINDOWS_95;	// 95
				else if (osInfo.dwMinorVersion < 90)
						this->osType = OS_WINDOWS_98;	// 98
				else	this->osType = OS_WINDOWS_98ME; // 98 ME
				break;
			case VER_PLATFORM_WIN32_NT:
				if(osInfo.dwMajorVersion>=5)
						this->osType = OS_WINDOWS_2000;	// 2000
				else	this->osType = OS_WINDOWS_NT;	// NT
				break;
			default:
				this->osType = OS_OTHER;
				zERR_WARNING("B: SYS: Failed to get correct Operating System.");  
		};		
	} 
	else zERR_FAULT("B: SYS: Failed to analyse operating-system");

	
	switch (this->osType)
	{
		case OS_WINDOWS_3_1:	this->osName = "Windows 3.1";break;
		case OS_WINDOWS_95:		this->osName = "Windows 95";break;
		case OS_WINDOWS_98:		this->osName = "Windows 98";break;
		case OS_WINDOWS_98ME:	this->osName = "Windows 98 ME";break;
		case OS_WINDOWS_NT:		this->osName = "Windows NT";break;
		case OS_WINDOWS_2000:	this->osName = "Windows 2000";break;
		default:				this->osName = "unknown";
	};
};

void zCSystemInfo::AnalyseGcard()
{	
	zERR_ASSERT(zrenderer);
	graMemSize = zrenderer->GetTotalTextureMem();
};

void zCSystemInfo::AnalyseNow()
{
	zERR_MESSAGE(3,zERR_BEGIN,"B: SYS: Analysing system ...");

	AnalyseCpu();
	AnalyseOs();
	AnalyseMemory();
	AnalyseGcard();
	
	// CPU-Typ
	zERR_MESSAGE(4,0,"B: SYS: CPU-Name: "+this->cpuID);
	zERR_MESSAGE(4,0,"B: SYS: CPU-Speed: "+zSTRING(this->cpuSpeed)+" Mhz");

	// RAM-Size	
	zERR_MESSAGE(4,0,"B: SYS: RAM-Size: "+zSTRING(float(this->memSize/1024/1024),2)+" MB");	
	zERR_MESSAGE(4,0,"B: SYS: RAM-Available: "+zSTRING(float(this->memAvailable/1024/1024),2)+" MB");
	
	// Graphicscard
	zERR_MESSAGE(4,0,"B: SYS: Graphics-Card: "+this->graName);
	zERR_MESSAGE(4,0,"B: SYS: Graphics-Memory: "+zSTRING(float(this->graMemSize/1024/1024),2)+" MB");
	
	// Operating-System
	zERR_MESSAGE(4,0,"B: SYS: OS: "+this->GetOsName()+" ["+this->osServicePack+"]");

	zERR_MESSAGE(3,zERR_END,"");	
};
