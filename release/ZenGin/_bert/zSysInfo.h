#ifndef __ZSYSINFO_H__
#define __ZSYSINFO_H__

class zCSystemInfo
{
	enum zTOperatingSystem 
	{
		OS_UNKNOWN,
		OS_WINDOWS_3_1,
		OS_WINDOWS_95,
		OS_WINDOWS_98,
		OS_WINDOWS_98ME,
		OS_WINDOWS_NT,
		OS_WINDOWS_2000,
		OS_OTHER
	};
	enum zTCpuType
	{
		CPU_UNKNOWN,
		CPU_INTEL_PENTIUM_I,
		CPU_INTEL_PENTIUM_II,
		CPU_INTEL_PENTIUM_III,
		CPU_INTEL_PENTIUM_IV,
		CPU_AMD_K6,
		CPU_AMD_ATHLON,		
		CPU_OTHER
	};

public:
	zCSystemInfo();
	virtual ~zCSystemInfo();

	virtual void		AnalyseNow	();
	
	zTOperatingSystem	GetOsType()			{ return osType; };
	zSTRING				GetOsName()			{ return osName; };
	zSTRING				GetOsServicePack()	{ return osServicePack; };
	
	zTCpuType			GetCpuType()		{ return cpuType; };
	zSTRING				GetCpuID()			{ return cpuID; };
	zDWORD				GetCpuSpeed()		{ return cpuSpeed; };

	zDWORD				GetGraMemSize()		{ return graMemSize; };

	zDWORD				GetMemSize()		{ return memSize; };

protected:

	void AnalyseMemory	();
	void AnalyseCpu		();
	void AnalyseOs		();
	void AnalyseGcard	();

protected:
	// Operating-System
	enum zTOperatingSystem	osType;
	zSTRING					osName;
	zSTRING					osServicePack;

	// CPU
	enum zTCpuType			cpuType;
	zSTRING					cpuID;
	zDWORD					cpuSpeed;

	// Memory/RAM
	zDWORD					memSize;
	zDWORD					memAvailable;

	// Graphics
	zSTRING					graName;
	zDWORD					graMemSize;
};

#endif