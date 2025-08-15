/******************************************************************************** 
 
     $Workfile:: zTools.cpp           $                $Date:: 26.04.01 15:35   $
     $Revision:: 34                   $             $Modtime:: 25.04.01 19:07   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created:

 * $Log: /current_work/zengin/_Dieter/zTools.cpp $
 * 
 * 34    26.04.01 15:35 Edenfeld
 * Soundprovider Checks sicherer gemacht,
 * AIPlayer Sprunghänger Bug gefixt
 * 
 * 33    24.04.01 17:34 Edenfeld
 * Patch 1.08a
 * 
 * 32    5.12.00 19:18 Moos
 * 
 * 31    5.12.00 12:04 Moos
 * 
 * 30    27.11.00 17:14 Moos
 * 
 * 29    20.11.00 16:44 Moos
 * 
 * 28    20.11.00 15:55 Moos
 * 
 * 27    8.11.00 22:01 Hildebrandt
 * 
 * 26    8.11.00 21:59 Hildebrandt
 * 
 * 25    13.10.00 16:44 Moos
 * 
 * 24    21.09.00 20:43 Moos
 * 
 * 23    21/09/00 19:56 Luesebrink
 * 
 * 22    21.09.00 17:26 Moos
 * 
 * 21    21.09.00 10:48 Moos
 * 
 * 20    20.09.00 16:02 Rueve
 * 
 * 19    20.09.00 1:48 Rueve
 * 
 * 18    19.09.00 13:08 Moos
 * 
 * 17    18.09.00 14:24 Edenfeld
 * 
 * 16    31.08.00 16:40 Keskenti
 * 
 * 15    31.08.00 16:34 Hildebrandt
 * 
 * 14    28.08.00 0:08 Hildebrandt
 * 
 * 12    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 17    9.08.00 17:12 Admin
 * 
 * 11    21.07.00 15:11 Hildebrandt
 * 
 * 10    21.07.00 14:28 Hildebrandt
 * 
 * 9     6.07.00 13:45 Hildebrandt
 * 
 * 3     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 34 $ ($Modtime: 25.04.01 19:07 $)


#include <zCore.h>
#include <zTools.h>
#include <zDisk.h>
#include <zWin32.h>
#include <zoption.h>



///////////////////////////////////////////////////////////////////////////
//     Timer
///////////////////////////////////////////////////////////////////////////
static zBOOL s_bSmoothTimer = TRUE;

zCTimer ztimer;

zDWORD zCTimer::s_forcedMaxFrameTime= 0;

/*--------------------------------------------------------------------------

    zCTimer::zCTimer()

 

    30-Aug-00       [Roman Keskenti]

                      Added initialization for motion-speed-factor


--------------------------------------------------------------------------*/ 
zCTimer::zCTimer() { 
//		lastTimer		= sysGetTime();		// FIXME: HILFE ! 
	lastTimer			= 0;
	frameTime			= 1;
	frameTimeFloat		= 1.0F;
	totalTimeFloat		= 0;
	factorMotion		= 1.0f;
    minFrameTime		= 0; // [Moos]
	forcedMaxFrameTime	= s_forcedMaxFrameTime;				// 20 fps
};

/*--------------------------------------------------------------------------

    zCTimer::ResetTimer()

 

    30-Aug-00       [Roman Keskenti]

                      Applied motion-speed-factor

    18-Sep-00       [Moos]
            
                      Timer geglättet

    20-Nov-00       [Moos]
            
                      Zwangspausen eingebaut, wenn die Framerate verdächtig schnell
                      wächst. Auf der G400 beseitigt das den Zeitlupenbug weitgehend,
                      ohne wirklich Performance zu kosten.

    27-Nov-00       [Moos]

                      Bessere Profile-Möglichkeit: durch setzen von 
                      force_10fps wird die logische Framerate auf 10fps
                      festgenagelt.

    05-Dec-00       [Moos]

                      Frameratenbegrenzung durch minFrameTime eingebaut

--------------------------------------------------------------------------*/ 
static zDWORD avg_time=0; // [Moos]
static int  force_update_timeout=-1; // [Moos] 

#ifdef DEBUG_MOOS
zBOOL force_10fps = FALSE;   // [Moos] Damit ich besser profilen kann
#endif

void zCTimer::ResetTimer () { 

	enum { MIN_FPS_RATE = 10 };

    // BEGIN codechange MOOS 20-Nov-00

    static zDWORD approxMaxFrameTime=1;

    if (approxMaxFrameTime < minFrameTime)  // [Moos] 05-Dec-00: absolute Notbremse: Frameratenbegrenzung.
        approxMaxFrameTime = minFrameTime;

    if (approxMaxFrameTime > 1)
        approxMaxFrameTime --;

	zDWORD newTime		= sysGetTime();
    zDWORD newFrameTime = (newTime - lastTimer) << 3;

	// Sleep für die Matrix muss drinbleiben (bzw. approxMaxFrameTime muss auf 400 stehen)
    if (approxMaxFrameTime > newFrameTime)
        Sleep( (approxMaxFrameTime-newFrameTime) >> 3);  // [Moos] Zwangspause
    else
        approxMaxFrameTime = newFrameTime;

    if (approxMaxFrameTime > forcedMaxFrameTime)
        approxMaxFrameTime = forcedMaxFrameTime;

    // END codechange MOOS


    if (force_update_timeout>10)   // [Moos]
        force_update_timeout = 10;

    if (--force_update_timeout<0){  // [Moos]
        FrameUpdate();        
        force_update_timeout = 0;
    }


	zDWORD tmp		= avg_time; //[Moos]
	frameTime		= factorMotion * (tmp - lastTimer);

#ifdef DEBUG_MOOS
    if (force_10fps)  // [Moos] Hier nageln wir sie fest.
        frameTime = 100;
#endif

	if (frameTime> (1000 / MIN_FPS_RATE))
	{
	  frameTime = (1000 / MIN_FPS_RATE);
	}

	totalTime		+= frameTime;
	frameTimeFloat	 = float(frameTime);
	frameTimeFloatSecs=frameTimeFloat/1000.0f;
	totalTimeFloat	+= frameTimeFloat;
	totalTimeFloatSecs=totalTimeFloat/1000.0f;
	lastTimer		 = tmp;
};

/*--------------------------------------------------------------------------

    zCTimer::SetFrameTime()

 

    30-Aug-00       [Roman Keskenti]

                      Applied motion-speed-factor


--------------------------------------------------------------------------*/ 
void zCTimer::SetFrameTime (const zREAL ftimeMSec) { 
	lastTimer		= sysGetTime();
	frameTimeFloat	= ftimeMSec;
	frameTimeFloatSecs=frameTimeFloat/1000.0f;
	frameTime		= int(frameTime);
	totalTimeFloat	+= frameTimeFloat;
	totalTimeFloatSecs=totalTimeFloat/1000.0f;
	totalTime		+= (factorMotion) * frameTime;
};


void zCTimer::S_SetMaxFPS(const zDWORD a_iMaxFPS) 
{ 
	s_forcedMaxFrameTime = a_iMaxFPS;
};

zDWORD zCTimer::S_GetMaxFPS() 
{ 
	return s_forcedMaxFrameTime;
};


void zCTimer::SetMaxFPS(const zDWORD a_iMaxFPS) 
{ 
	forcedMaxFrameTime = a_iMaxFPS;
};

/*--------------------------------------------------------------------------

    zCTimer::FrameUpdate()

 

    30-Aug-00       [Moos]

                      Erzeugt, um mit animationsgezumpel fertigzuwerden


--------------------------------------------------------------------------*/ 


void zCTimer::FrameUpdate () 
{ 
	if (!s_bSmoothTimer) 
	{
		avg_time = sysGetTime();
		return;
	}

    zDWORD new_time = sysGetTime();
    avg_time = (new_time + 3 * avg_time) >> 2;
    if (new_time > avg_time)
        avg_time = new_time;
    if (new_time < avg_time-400)
        avg_time = new_time-400;

    force_update_timeout ++;

    if(force_update_timeout>10)
        force_update_timeout = 10;

    if(force_update_timeout<3)
        force_update_timeout = 3;
};



/*--------------------------------------------------------------------------

    zCTimer::LimitFPS()


    30-Aug-00       [Moos]

                     Verzweiflungstat gegen den Zeitlupenbug

--------------------------------------------------------------------------*/ 

void zCTimer::LimitFPS(int fps)
{
	s_bSmoothTimer = zoptions->ReadBool	("ENGINE", "zSmoothTimer", TRUE);	
    if (fps>0)
        minFrameTime = (1000 << 3)/fps;
    else
        minFrameTime = 0;
}


///////////////////////////////////////////////////////////////////////////
//     CRC32	(Cyclic Redundancy Codes) - Checksums
///////////////////////////////////////////////////////////////////////////

/*
Source: (zlib aus dem PovRay Source)
 * crc32.c -- compute the CRC-32 of a data stream
 * Copyright (C) 1995-1998 Mark Adler
*/

/* ========================================================================
 * Table of CRC-32's of all single-byte values (made by make_crc_table)
 */

static const zDWORD crc_table[256] = {
		0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
		0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
		0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
		0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
		0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
		0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
		0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
		0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
		0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
		0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
		0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
		0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
		0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
		0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
		0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
		0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
		0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
		0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
		0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
		0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
		0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
		0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
		0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
		0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
		0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
		0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
		0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
		0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
		0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
		0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
		0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
		0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
		0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
		0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
		0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
		0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
		0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
		0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
		0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
		0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
		0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
		0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
		0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
		0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
		0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
		0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
		0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
		0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
		0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
		0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
		0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
		0x2d02ef8dL
};

// ========================================================================= 

#define DO1(buf) crc = crc_table[((int)crc ^ (*buffer++)) & 0xff] ^ (crc >> 8);
#define DO2(buf)  DO1(buf); DO1(buf);
#define DO4(buf)  DO2(buf); DO2(buf);
#define DO8(buf)  DO4(buf); DO4(buf);

zDWORD zCChecksum::GetBufferCRC32 (zBYTE *buffer, zDWORD bufferSize, zDWORD crc) 
{
	if (!buffer) return crc;
	
    crc = crc ^ 0xffffffffL;
    while (bufferSize >= 8)
    {
		DO8(buffer);
		bufferSize -= 8;
    }
    if (bufferSize) do {
		DO1(buffer);
    } while (--bufferSize);
    return crc ^ 0xffffffffL;
}

/*
zDWORD zCClassDef::GetStringChecksum (const zSTRING& s)
{
	zDWORD	hash	= 0;
	char	*data	= s.ToChar;

	while (*data)
	{
//		TCHAR Ch = appToUpper(*Data++);
		BYTE  b  = *data++;
		hash     = ((hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(hash ^ b) & 0x000000FF];
#if ___UNICODE___
		B        = Ch>>8;
		Hash     = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
#endif
	}
	return Hash;
}
*/

#undef DO1
#undef DO2
#undef DO4
#undef DO8

// =========================================================================

void zCChecksum::BeginChecksum () {
	checksum = 0;
};

zDWORD zCChecksum::EndChecksum () {
	return checksum;
};

void zCChecksum::CalcBufferChecksum (zBYTE *buffer, zDWORD bufferSize) {
	checksum = GetBufferCRC32 (buffer, bufferSize, checksum);
};

void zCChecksum::CalcFileChecksum (zFILE *file) {
	file->Open();
	zDWORD	bufferSize	= file->Size();				if (bufferSize<=0) return;
	zBYTE	*buffer		= zNEW(zBYTE) [bufferSize];
	
	file->Read (buffer, bufferSize);

	CalcBufferChecksum (buffer, bufferSize);

	delete[] buffer;
};

void zCChecksum::CalcFileChecksum (const zSTRING& fileName) {
	zFILE* file	= zfactory->CreateZFile(fileName);
	file->Open			();
	CalcFileChecksum	(file);
	file->Close			();
	delete file;
};

// ============================================================================================================

///////////////////////////////////////////////////////////////////////////
//     CRC16	(Cyclic Redundancy Codes) - Checksums
///////////////////////////////////////////////////////////////////////////

static zWORD crc_table16[256] =
{
		0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
		0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
		0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
		0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
		0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
		0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
		0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
		0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
		0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
		0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
		0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
		0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
		0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
		0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
		0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
		0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
		0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
		0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
		0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
		0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
		0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
		0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
		0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
		0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
		0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
		0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
		0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
		0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
		0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
		0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
		0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
		0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

// =========================================================================

#define DO1(buf) crc = ((crc >> 8) & 0xff) ^ crc_table16[(crc ^ *buffer++) & 0xff];
#define DO2(buf)  DO1(buf); DO1(buf);
#define DO4(buf)  DO2(buf); DO2(buf);
#define DO8(buf)  DO4(buf); DO4(buf);

zWORD zCChecksum16::GetBufferCRC16 (zBYTE *buffer, zDWORD bufferSize, zWORD _crc) 
{
	if (!buffer) return _crc;
	
	int crc = _crc;
    while (bufferSize >= 8)
    {
		DO8(buffer);
		bufferSize -= 8;
    }
    if (bufferSize) do {
		DO1(buffer);
    } while (--bufferSize);
	
    return zWORD(crc);
}

#undef DO1
#undef DO2
#undef DO4
#undef DO8

// =========================================================================

void zCChecksum16::BeginChecksum () {
	checksum = 0;
};

zWORD zCChecksum16::EndChecksum () {
	return checksum;
};

void zCChecksum16::CalcBufferChecksum (zBYTE *buffer, zDWORD bufferSize) {
	checksum = GetBufferCRC16 (buffer, bufferSize, checksum);
};

// ============================================================================================================

/*
random_num = (Seed = (Seed * 1664525) + 1013904223);

and:

random_num = ((seed = seed * 1103515245 + 12345) >> 16) & 0x7fff;
*/

// ============================================================================================================

zCFPUControler zfpuControler;

static zDWORD zMyControlFP (zDWORD newValue, zDWORD mask) {
	return _controlfp (newValue, mask);
};

zCFPUControler::zCFPUControler() {
	SaveCurrentControlWord		();
	ComputeDefaultControlWord	();
};

void zCFPUControler::SaveCurrentControlWord	() {
	savedControlWord = zMyControlFP (0,0);
};

void zCFPUControler::RestoreSavedControlWord () {
	zMyControlFP (savedControlWord, 0xFFFFFFFF);
};

zDWORD zCFPUControler::GetCurrentControlWord () {
	return zMyControlFP(0,0);
};

void zCFPUControler::RestoreDefaultControlWord() {
	zMyControlFP (defaultControlWord, 0xFFFFFFFF);
};

void zCFPUControler::ComputeDefaultControlWord() 
{
	// Frischen Ausgangszustand herstellen, noetig, da bereits weitere .DLLs geladen sein koennen,
	// die das ControlWord veraendert haben koennen.
	zMyControlFP			(_CW_DEFAULT,0xFFFFFFFF);
	// ..und zwischenspeichern
	defaultControlWord		= zMyControlFP (0,0);
	// im Folgenden werden bekannte Teile des ControlWord manipuliert

	// Die Default Float-Precision ist "SINGLE" = _PC_24
	zDWORD pc				= _PC_24;
	defaultControlWord		= (defaultControlWord & (~_MCW_PC )) | (pc & _MCW_PC);

	// Im Debug-Build werden einige Exceptions aktiviert, um so leichter Fehler 
	// zu finden.
	// Beispiel: durch Div0 koennten unbrauchbare Float-Werte entstehen, die im weiteren Verlauf
	// fatale Folgen haben koennen.
#ifdef _DEBUG
	{
		// Debug-Build
		zDWORD fpuExcept	= defaultControlWord & _MCW_EM;
		fpuExcept			|= (_EM_INVALID		);			// aus, bit setzen
		fpuExcept			|= (_EM_DENORMAL	);			// aus, bit setzen
		fpuExcept			&= (~_EM_ZERODIVIDE	);			// einschalten, bit loeschen
//		fpuExcept			|= ( _EM_ZERODIVIDE	);			// aus, bit setzen
		fpuExcept			|= (_EM_OVERFLOW	);			// aus, bit setzen
		fpuExcept			|= (_EM_UNDERFLOW	);			// aus, bit setzen
		fpuExcept			|= (_EM_INEXACT		);			// aus, bit setzen
		defaultControlWord	= (defaultControlWord & (~_MCW_EM)) | (fpuExcept & _MCW_EM);
	};
#else
	{
		// Release-Build
		zDWORD fpuExcept	= defaultControlWord & _MCW_EM;
		fpuExcept			|= (_EM_INVALID		);			// aus, bit setzen
		fpuExcept			|= (_EM_DENORMAL	);			// aus, bit setzen
		fpuExcept			|= (_EM_ZERODIVIDE	);			// aus, bit setzen
		fpuExcept			|= (_EM_OVERFLOW	);			// aus, bit setzen
		fpuExcept			|= (_EM_UNDERFLOW	);			// aus, bit setzen
		fpuExcept			|= (_EM_INEXACT		);			// aus, bit setzen
		defaultControlWord	= (defaultControlWord & (~_MCW_EM)) | (fpuExcept & _MCW_EM);
	};
#endif

	//
	zMyControlFP			(defaultControlWord,0xFFFFFFFF);
};

void zCFPUControler::SetControlWord (const zDWORD cw) {
	zMyControlFP(cw,0xFFFFFFFF);
};

void zCFPUControler::SetPrecision_24 ()	{
	zMyControlFP ((defaultControlWord & (~_MCW_PC )) | (_PC_24 & _MCW_PC), _MCW_PC);
};

void zCFPUControler::SetPrecision_53 ()	{
	zMyControlFP ((defaultControlWord & (~_MCW_PC )) | (_PC_53 & _MCW_PC), _MCW_PC);
};

void zCFPUControler::SetPrecision_64 ()	{
	zMyControlFP ((defaultControlWord & (~_MCW_PC )) | (_PC_64 & _MCW_PC), _MCW_PC);
};

void zCFPUControler::PrintStatus () 
{
	zSTRING	s;
	zerr.Separator();		

	zDWORD	ctrl87 = (zDWORD)zMyControlFP(0,0);
	zERR_MESSAGE(1,zERR_BEGIN,"D: FPU: Checking FPU Control Word: controlfp() returns \""+zSTRING((zDWORD)ctrl87)+"\"");
		
	s.Clear();
	if (ctrl87 & _DN_FLUSH)			s+= "_DN_FLUSH";		
	else							s+= "_DN_SAVE";		
	zERR_MESSAGE(1,0,"D: FPU: ... Denormal control (_MCW_DM_): "+s);

	//
	zBOOL none = TRUE;
	zERR_MESSAGE(1,0,"D: FPU: ... Interrupt exception (_MCW_EM)");
	if (!(ctrl87 & _EM_INVALID))	{ zERR_MESSAGE(1,0,"D: FPU: ...... _EM_INVALID");none=FALSE; }
	if (!(ctrl87 & _EM_DENORMAL))	{ zERR_MESSAGE(1,0,"D: FPU: ...... _EM_DENORMAL");none=FALSE; }
	if (!(ctrl87 & _EM_ZERODIVIDE))	{ zERR_MESSAGE(1,0,"D: FPU: ...... _EM_ZERODIVIDE");none=FALSE; }
	if (!(ctrl87 & _EM_OVERFLOW))	{ zERR_MESSAGE(1,0,"D: FPU: ...... _EM_OVERFLOW");none=FALSE; }
	if (!(ctrl87 & _EM_UNDERFLOW))	{ zERR_MESSAGE(1,0,"D: FPU: ...... _EM_UNDERFLOW");none=FALSE; }
	if (!(ctrl87 & _EM_INEXACT))	{ zERR_MESSAGE(1,0,"D: FPU: ...... _EM_INEXACT");none=FALSE; }
	if (none)						  zERR_MESSAGE(1,0,"D: FPU: ...... none");

	s.Clear();
	if (ctrl87 & _IC_AFFINE)		s+= "_IC_AFFINE"; 
	else							s+= "_IC_PROJECTIVE";
	zERR_MESSAGE(1,0,"D: FPU: ... Infinity control (_MCW_IC): "+s);
	
	s.Clear();
	if (ctrl87 & _RC_CHOP)			s+= "_RC_CHOP"; else
	if (ctrl87 & _RC_UP)			s+= "_RC_UP"; else
	if (ctrl87 & _RC_DOWN)			s+= "_RC_DOWN"; 
	else							s+= "_RC_NEAR"; 
	zERR_MESSAGE(1,0,"D: FPU: ... Rounding control (_MCW_RC): "+s);

	s.Clear();
	if (ctrl87 & _PC_24)			s+="_PC_24"; else
	if (ctrl87 & _PC_53)			s+="_PC_53"; 
	else							s+="_PC_64"; 
	zERR_MESSAGE(1,0,"D: FPU: ... Precision control (_MCW_PC): "+s);

	zERR_MESSAGE(1,zERR_END,"");	
};

// ============================================================================================================

const float zfloatTwo= 2.0F;

// ============================================================================================================


/*--------------------------------------------------------------------------
    zSin, zCos und zSinCos
	
    19-Sep-00       [Michael]
                      Implementation TableLookup					  
--------------------------------------------------------------------------*/ 


// von -PI bis PI
static const float SinTable[6284] = 
{
 -0.000093f,   -0.001093f,   -0.002093f,   -0.003093f,   -0.004093f,   -0.005093f,   -0.006093f,   -0.007093f,   -0.008093f,   -0.009093f,  
 -0.010092f,   -0.011092f,   -0.012092f,   -0.013092f,   -0.014092f,   -0.015092f,   -0.016092f,   -0.017092f,   -0.018092f,   -0.019091f,  
 -0.020091f,   -0.021091f,   -0.022091f,   -0.023091f,   -0.024090f,   -0.025090f,   -0.026090f,   -0.027089f,   -0.028089f,   -0.029089f,  
 -0.030088f,   -0.031088f,   -0.032087f,   -0.033087f,   -0.034086f,   -0.035085f,   -0.036085f,   -0.037084f,   -0.038083f,   -0.039083f,  
 -0.040082f,   -0.041081f,   -0.042080f,   -0.043079f,   -0.044078f,   -0.045077f,   -0.046076f,   -0.047075f,   -0.048074f,   -0.049073f,  
 -0.050072f,   -0.051070f,   -0.052069f,   -0.053068f,   -0.054066f,   -0.055065f,   -0.056063f,   -0.057062f,   -0.058060f,   -0.059058f,  
 -0.060056f,   -0.061055f,   -0.062053f,   -0.063051f,   -0.064049f,   -0.065047f,   -0.066045f,   -0.067042f,   -0.068040f,   -0.069038f,  
 -0.070035f,   -0.071033f,   -0.072030f,   -0.073028f,   -0.074025f,   -0.075022f,   -0.076019f,   -0.077016f,   -0.078013f,   -0.079010f,  
 -0.080007f,   -0.081004f,   -0.082000f,   -0.082997f,   -0.083994f,   -0.084990f,   -0.085986f,   -0.086983f,   -0.087979f,   -0.088975f,  
 -0.089971f,   -0.090967f,   -0.091963f,   -0.092958f,   -0.093954f,   -0.094949f,   -0.095945f,   -0.096940f,   -0.097935f,   -0.098931f,  
 -0.099926f,   -0.100921f,   -0.101915f,   -0.102910f,   -0.103905f,   -0.104899f,   -0.105894f,   -0.106888f,   -0.107882f,   -0.108876f,  
 -0.109870f,   -0.110864f,   -0.111858f,   -0.112852f,   -0.113845f,   -0.114839f,   -0.115832f,   -0.116825f,   -0.117818f,   -0.118811f,  
 -0.119804f,   -0.120797f,   -0.121790f,   -0.122782f,   -0.123774f,   -0.124767f,   -0.125759f,   -0.126751f,   -0.127743f,   -0.128734f,  
 -0.129726f,   -0.130718f,   -0.131709f,   -0.132700f,   -0.133691f,   -0.134682f,   -0.135673f,   -0.136664f,   -0.137654f,   -0.138645f,  
 -0.139635f,   -0.140625f,   -0.141615f,   -0.142605f,   -0.143595f,   -0.144584f,   -0.145574f,   -0.146563f,   -0.147552f,   -0.148541f,  
 -0.149530f,   -0.150518f,   -0.151507f,   -0.152495f,   -0.153484f,   -0.154472f,   -0.155460f,   -0.156447f,   -0.157435f,   -0.158422f,  
 -0.159410f,   -0.160397f,   -0.161384f,   -0.162371f,   -0.163357f,   -0.164344f,   -0.165330f,   -0.166316f,   -0.167302f,   -0.168288f,  
 -0.169274f,   -0.170259f,   -0.171244f,   -0.172230f,   -0.173215f,   -0.174199f,   -0.175184f,   -0.176168f,   -0.177153f,   -0.178137f,  
 -0.179121f,   -0.180104f,   -0.181088f,   -0.182071f,   -0.183055f,   -0.184038f,   -0.185020f,   -0.186003f,   -0.186986f,   -0.187968f,  
 -0.188950f,   -0.189932f,   -0.190913f,   -0.191895f,   -0.192876f,   -0.193857f,   -0.194838f,   -0.195819f,   -0.196800f,   -0.197780f,  
 -0.198760f,   -0.199740f,   -0.200720f,   -0.201699f,   -0.202679f,   -0.203658f,   -0.204637f,   -0.205616f,   -0.206594f,   -0.207572f,  
 -0.208551f,   -0.209528f,   -0.210506f,   -0.211484f,   -0.212461f,   -0.213438f,   -0.214415f,   -0.215391f,   -0.216368f,   -0.217344f,  
 -0.218320f,   -0.219296f,   -0.220271f,   -0.221247f,   -0.222222f,   -0.223197f,   -0.224171f,   -0.225146f,   -0.226120f,   -0.227094f,  
 -0.228068f,   -0.229041f,   -0.230015f,   -0.230988f,   -0.231960f,   -0.232933f,   -0.233905f,   -0.234878f,   -0.235850f,   -0.236821f,  
 -0.237793f,   -0.238764f,   -0.239735f,   -0.240706f,   -0.241676f,   -0.242646f,   -0.243616f,   -0.244586f,   -0.245555f,   -0.246525f,  
 -0.247494f,   -0.248463f,   -0.249431f,   -0.250399f,   -0.251367f,   -0.252335f,   -0.253303f,   -0.254270f,   -0.255237f,   -0.256204f,  
 -0.257170f,   -0.258136f,   -0.259102f,   -0.260068f,   -0.261034f,   -0.261999f,   -0.262964f,   -0.263928f,   -0.264893f,   -0.265857f,  
 -0.266821f,   -0.267784f,   -0.268748f,   -0.269711f,   -0.270674f,   -0.271636f,   -0.272598f,   -0.273560f,   -0.274522f,   -0.275484f,  
 -0.276445f,   -0.277406f,   -0.278366f,   -0.279327f,   -0.280287f,   -0.281246f,   -0.282206f,   -0.283165f,   -0.284124f,   -0.285083f,  
 -0.286041f,   -0.286999f,   -0.287957f,   -0.288914f,   -0.289872f,   -0.290829f,   -0.291785f,   -0.292741f,   -0.293698f,   -0.294653f,  
 -0.295609f,   -0.296564f,   -0.297519f,   -0.298473f,   -0.299428f,   -0.300382f,   -0.301335f,   -0.302289f,   -0.303242f,   -0.304194f,  
 -0.305147f,   -0.306099f,   -0.307051f,   -0.308002f,   -0.308954f,   -0.309905f,   -0.310855f,   -0.311805f,   -0.312755f,   -0.313705f,  
 -0.314655f,   -0.315604f,   -0.316552f,   -0.317501f,   -0.318449f,   -0.319397f,   -0.320344f,   -0.321291f,   -0.322238f,   -0.323185f,  
 -0.324131f,   -0.325077f,   -0.326022f,   -0.326967f,   -0.327912f,   -0.328857f,   -0.329801f,   -0.330745f,   -0.331688f,   -0.332632f,  
 -0.333574f,   -0.334517f,   -0.335459f,   -0.336401f,   -0.337343f,   -0.338284f,   -0.339225f,   -0.340165f,   -0.341105f,   -0.342045f,  
 -0.342985f,   -0.343924f,   -0.344863f,   -0.345801f,   -0.346739f,   -0.347677f,   -0.348615f,   -0.349552f,   -0.350489f,   -0.351425f,  
 -0.352361f,   -0.353297f,   -0.354232f,   -0.355167f,   -0.356102f,   -0.357036f,   -0.357970f,   -0.358903f,   -0.359837f,   -0.360769f,  
 -0.361702f,   -0.362634f,   -0.363566f,   -0.364497f,   -0.365428f,   -0.366359f,   -0.367289f,   -0.368219f,   -0.369149f,   -0.370078f,  
 -0.371007f,   -0.371935f,   -0.372863f,   -0.373791f,   -0.374718f,   -0.375645f,   -0.376572f,   -0.377498f,   -0.378424f,   -0.379349f,  
 -0.380274f,   -0.381199f,   -0.382123f,   -0.383047f,   -0.383971f,   -0.384894f,   -0.385816f,   -0.386739f,   -0.387661f,   -0.388582f,  
 -0.389504f,   -0.390425f,   -0.391345f,   -0.392265f,   -0.393185f,   -0.394104f,   -0.395023f,   -0.395941f,   -0.396859f,   -0.397777f,  
 -0.398694f,   -0.399611f,   -0.400528f,   -0.401444f,   -0.402359f,   -0.403275f,   -0.404190f,   -0.405104f,   -0.406018f,   -0.406932f,  
 -0.407845f,   -0.408758f,   -0.409670f,   -0.410582f,   -0.411494f,   -0.412405f,   -0.413316f,   -0.414226f,   -0.415136f,   -0.416046f,  
 -0.416955f,   -0.417864f,   -0.418772f,   -0.419680f,   -0.420587f,   -0.421494f,   -0.422401f,   -0.423307f,   -0.424213f,   -0.425118f,  
 -0.426023f,   -0.426928f,   -0.427832f,   -0.428736f,   -0.429639f,   -0.430542f,   -0.431444f,   -0.432346f,   -0.433247f,   -0.434148f,  
 -0.435049f,   -0.435949f,   -0.436849f,   -0.437748f,   -0.438647f,   -0.439546f,   -0.440444f,   -0.441341f,   -0.442238f,   -0.443135f,  
 -0.444031f,   -0.444927f,   -0.445822f,   -0.446717f,   -0.447612f,   -0.448506f,   -0.449399f,   -0.450292f,   -0.451185f,   -0.452077f,  
 -0.452969f,   -0.453860f,   -0.454751f,   -0.455641f,   -0.456531f,   -0.457421f,   -0.458310f,   -0.459198f,   -0.460087f,   -0.460974f,  
 -0.461861f,   -0.462748f,   -0.463634f,   -0.464520f,   -0.465405f,   -0.466290f,   -0.467175f,   -0.468059f,   -0.468942f,   -0.469825f,  
 -0.470708f,   -0.471590f,   -0.472471f,   -0.473352f,   -0.474233f,   -0.475113f,   -0.475993f,   -0.476872f,   -0.477751f,   -0.478629f,  
 -0.479507f,   -0.480384f,   -0.481261f,   -0.482137f,   -0.483013f,   -0.483889f,   -0.484763f,   -0.485638f,   -0.486512f,   -0.487385f,  
 -0.488258f,   -0.489131f,   -0.490003f,   -0.490874f,   -0.491745f,   -0.492616f,   -0.493486f,   -0.494355f,   -0.495224f,   -0.496093f,  
 -0.496961f,   -0.497828f,   -0.498695f,   -0.499562f,   -0.500428f,   -0.501293f,   -0.502158f,   -0.503023f,   -0.503887f,   -0.504750f,  
 -0.505613f,   -0.506476f,   -0.507338f,   -0.508199f,   -0.509060f,   -0.509921f,   -0.510781f,   -0.511640f,   -0.512499f,   -0.513358f,  
 -0.514215f,   -0.515073f,   -0.515930f,   -0.516786f,   -0.517642f,   -0.518497f,   -0.519352f,   -0.520206f,   -0.521060f,   -0.521914f,  
 -0.522766f,   -0.523618f,   -0.524470f,   -0.525321f,   -0.526172f,   -0.527022f,   -0.527872f,   -0.528721f,   -0.529569f,   -0.530417f,  
 -0.531265f,   -0.532112f,   -0.532958f,   -0.533804f,   -0.534649f,   -0.535494f,   -0.536338f,   -0.537182f,   -0.538025f,   -0.538868f,  
 -0.539710f,   -0.540552f,   -0.541393f,   -0.542233f,   -0.543073f,   -0.543913f,   -0.544751f,   -0.545590f,   -0.546428f,   -0.547265f,  
 -0.548101f,   -0.548938f,   -0.549773f,   -0.550608f,   -0.551443f,   -0.552277f,   -0.553110f,   -0.553943f,   -0.554775f,   -0.555607f,  
 -0.556438f,   -0.557269f,   -0.558099f,   -0.558928f,   -0.559757f,   -0.560586f,   -0.561413f,   -0.562241f,   -0.563067f,   -0.563893f,  
 -0.564719f,   -0.565544f,   -0.566368f,   -0.567192f,   -0.568016f,   -0.568838f,   -0.569660f,   -0.570482f,   -0.571303f,   -0.572124f,  
 -0.572943f,   -0.573763f,   -0.574581f,   -0.575400f,   -0.576217f,   -0.577034f,   -0.577851f,   -0.578667f,   -0.579482f,   -0.580296f,  
 -0.581111f,   -0.581924f,   -0.582737f,   -0.583549f,   -0.584361f,   -0.585172f,   -0.585983f,   -0.586793f,   -0.587603f,   -0.588411f,  
 -0.589220f,   -0.590027f,   -0.590834f,   -0.591641f,   -0.592447f,   -0.593252f,   -0.594057f,   -0.594861f,   -0.595665f,   -0.596467f,  
 -0.597270f,   -0.598072f,   -0.598873f,   -0.599673f,   -0.600473f,   -0.601273f,   -0.602071f,   -0.602869f,   -0.603667f,   -0.604464f,  
 -0.605260f,   -0.606056f,   -0.606851f,   -0.607646f,   -0.608439f,   -0.609233f,   -0.610025f,   -0.610818f,   -0.611609f,   -0.612400f,  
 -0.613190f,   -0.613980f,   -0.614769f,   -0.615557f,   -0.616345f,   -0.617132f,   -0.617919f,   -0.618705f,   -0.619490f,   -0.620275f,  
 -0.621059f,   -0.621842f,   -0.622625f,   -0.623407f,   -0.624189f,   -0.624970f,   -0.625750f,   -0.626530f,   -0.627309f,   -0.628087f,  
 -0.628865f,   -0.629642f,   -0.630419f,   -0.631195f,   -0.631970f,   -0.632745f,   -0.633519f,   -0.634292f,   -0.635065f,   -0.635837f,  
 -0.636609f,   -0.637380f,   -0.638150f,   -0.638919f,   -0.639688f,   -0.640457f,   -0.641224f,   -0.641991f,   -0.642758f,   -0.643523f,  
 -0.644289f,   -0.645053f,   -0.645817f,   -0.646580f,   -0.647343f,   -0.648104f,   -0.648866f,   -0.649626f,   -0.650386f,   -0.651145f,  
 -0.651904f,   -0.652662f,   -0.653419f,   -0.654176f,   -0.654932f,   -0.655687f,   -0.656442f,   -0.657196f,   -0.657950f,   -0.658702f,  
 -0.659454f,   -0.660206f,   -0.660957f,   -0.661707f,   -0.662456f,   -0.663205f,   -0.663953f,   -0.664700f,   -0.665447f,   -0.666193f,  
 -0.666939f,   -0.667683f,   -0.668428f,   -0.669171f,   -0.669914f,   -0.670656f,   -0.671397f,   -0.672138f,   -0.672878f,   -0.673618f,  
 -0.674356f,   -0.675094f,   -0.675832f,   -0.676569f,   -0.677305f,   -0.678040f,   -0.678775f,   -0.679509f,   -0.680242f,   -0.680975f,  
 -0.681707f,   -0.682438f,   -0.683168f,   -0.683898f,   -0.684628f,   -0.685356f,   -0.686084f,   -0.686811f,   -0.687538f,   -0.688264f,  
 -0.688989f,   -0.689713f,   -0.690437f,   -0.691160f,   -0.691882f,   -0.692604f,   -0.693325f,   -0.694045f,   -0.694765f,   -0.695484f,  
 -0.696202f,   -0.696919f,   -0.697636f,   -0.698352f,   -0.699068f,   -0.699782f,   -0.700496f,   -0.701210f,   -0.701922f,   -0.702634f,  
 -0.703345f,   -0.704056f,   -0.704766f,   -0.705475f,   -0.706183f,   -0.706891f,   -0.707598f,   -0.708304f,   -0.709010f,   -0.709714f,  
 -0.710419f,   -0.711122f,   -0.711825f,   -0.712527f,   -0.713228f,   -0.713929f,   -0.714628f,   -0.715328f,   -0.716026f,   -0.716724f,  
 -0.717421f,   -0.718117f,   -0.718813f,   -0.719507f,   -0.720201f,   -0.720895f,   -0.721588f,   -0.722280f,   -0.722971f,   -0.723661f,  
 -0.724351f,   -0.725040f,   -0.725728f,   -0.726416f,   -0.727103f,   -0.727789f,   -0.728475f,   -0.729159f,   -0.729843f,   -0.730527f,  
 -0.731209f,   -0.731891f,   -0.732572f,   -0.733252f,   -0.733932f,   -0.734611f,   -0.735289f,   -0.735966f,   -0.736643f,   -0.737319f,  
 -0.737994f,   -0.738668f,   -0.739342f,   -0.740015f,   -0.740687f,   -0.741359f,   -0.742029f,   -0.742699f,   -0.743369f,   -0.744037f,  
 -0.744705f,   -0.745372f,   -0.746038f,   -0.746704f,   -0.747369f,   -0.748033f,   -0.748696f,   -0.749358f,   -0.750020f,   -0.750681f,  
 -0.751342f,   -0.752001f,   -0.752660f,   -0.753318f,   -0.753975f,   -0.754632f,   -0.755288f,   -0.755943f,   -0.756597f,   -0.757250f,  
 -0.757903f,   -0.758555f,   -0.759206f,   -0.759857f,   -0.760506f,   -0.761155f,   -0.761804f,   -0.762451f,   -0.763098f,   -0.763744f,  
 -0.764389f,   -0.765033f,   -0.765677f,   -0.766320f,   -0.766962f,   -0.767603f,   -0.768243f,   -0.768883f,   -0.769522f,   -0.770160f,  
 -0.770798f,   -0.771435f,   -0.772071f,   -0.772706f,   -0.773340f,   -0.773974f,   -0.774607f,   -0.775239f,   -0.775870f,   -0.776500f,  
 -0.777130f,   -0.777759f,   -0.778387f,   -0.779015f,   -0.779641f,   -0.780267f,   -0.780892f,   -0.781516f,   -0.782140f,   -0.782763f,  
 -0.783385f,   -0.784006f,   -0.784626f,   -0.785246f,   -0.785864f,   -0.786482f,   -0.787100f,   -0.787716f,   -0.788332f,   -0.788947f,  
 -0.789561f,   -0.790174f,   -0.790786f,   -0.791398f,   -0.792009f,   -0.792619f,   -0.793228f,   -0.793837f,   -0.794445f,   -0.795052f,  
 -0.795658f,   -0.796263f,   -0.796868f,   -0.797471f,   -0.798074f,   -0.798677f,   -0.799278f,   -0.799878f,   -0.800478f,   -0.801077f,  
 -0.801675f,   -0.802273f,   -0.802869f,   -0.803465f,   -0.804060f,   -0.804654f,   -0.805247f,   -0.805840f,   -0.806432f,   -0.807023f,  
 -0.807613f,   -0.808202f,   -0.808791f,   -0.809378f,   -0.809965f,   -0.810551f,   -0.811136f,   -0.811721f,   -0.812305f,   -0.812887f,  
 -0.813469f,   -0.814051f,   -0.814631f,   -0.815211f,   -0.815789f,   -0.816367f,   -0.816944f,   -0.817521f,   -0.818096f,   -0.818671f,  
 -0.819245f,   -0.819818f,   -0.820390f,   -0.820961f,   -0.821532f,   -0.822102f,   -0.822671f,   -0.823239f,   -0.823806f,   -0.824372f,  
 -0.824938f,   -0.825503f,   -0.826067f,   -0.826630f,   -0.827192f,   -0.827754f,   -0.828315f,   -0.828874f,   -0.829433f,   -0.829992f,  
 -0.830549f,   -0.831106f,   -0.831661f,   -0.832216f,   -0.832770f,   -0.833323f,   -0.833876f,   -0.834427f,   -0.834978f,   -0.835528f,  
 -0.836077f,   -0.836625f,   -0.837172f,   -0.837719f,   -0.838265f,   -0.838809f,   -0.839353f,   -0.839897f,   -0.840439f,   -0.840980f,  
 -0.841521f,   -0.842061f,   -0.842600f,   -0.843138f,   -0.843675f,   -0.844212f,   -0.844747f,   -0.845282f,   -0.845816f,   -0.846349f,  
 -0.846881f,   -0.847413f,   -0.847943f,   -0.848473f,   -0.849001f,   -0.849529f,   -0.850057f,   -0.850583f,   -0.851108f,   -0.851633f,  
 -0.852157f,   -0.852679f,   -0.853201f,   -0.853723f,   -0.854243f,   -0.854762f,   -0.855281f,   -0.855799f,   -0.856316f,   -0.856832f,  
 -0.857347f,   -0.857861f,   -0.858374f,   -0.858887f,   -0.859399f,   -0.859910f,   -0.860420f,   -0.860929f,   -0.861437f,   -0.861945f,  
 -0.862451f,   -0.862957f,   -0.863462f,   -0.863966f,   -0.864469f,   -0.864971f,   -0.865472f,   -0.865973f,   -0.866473f,   -0.866971f,  
 -0.867469f,   -0.867966f,   -0.868463f,   -0.868958f,   -0.869452f,   -0.869946f,   -0.870439f,   -0.870931f,   -0.871421f,   -0.871912f,  
 -0.872401f,   -0.872889f,   -0.873377f,   -0.873863f,   -0.874349f,   -0.874834f,   -0.875318f,   -0.875801f,   -0.876283f,   -0.876765f,  
 -0.877245f,   -0.877725f,   -0.878203f,   -0.878681f,   -0.879158f,   -0.879634f,   -0.880109f,   -0.880584f,   -0.881057f,   -0.881530f,  
 -0.882001f,   -0.882472f,   -0.882942f,   -0.883411f,   -0.883879f,   -0.884347f,   -0.884813f,   -0.885279f,   -0.885743f,   -0.886207f,  
 -0.886670f,   -0.887132f,   -0.887593f,   -0.888053f,   -0.888512f,   -0.888971f,   -0.889428f,   -0.889885f,   -0.890341f,   -0.890795f,  
 -0.891249f,   -0.891702f,   -0.892155f,   -0.892606f,   -0.893056f,   -0.893506f,   -0.893954f,   -0.894402f,   -0.894849f,   -0.895295f,  
 -0.895740f,   -0.896184f,   -0.896627f,   -0.897070f,   -0.897511f,   -0.897952f,   -0.898391f,   -0.898830f,   -0.899268f,   -0.899705f,  
 -0.900141f,   -0.900576f,   -0.901010f,   -0.901444f,   -0.901876f,   -0.902308f,   -0.902738f,   -0.903168f,   -0.903597f,   -0.904025f,  
 -0.904452f,   -0.904878f,   -0.905303f,   -0.905727f,   -0.906151f,   -0.906573f,   -0.906995f,   -0.907416f,   -0.907835f,   -0.908254f,  
 -0.908672f,   -0.909089f,   -0.909505f,   -0.909921f,   -0.910335f,   -0.910748f,   -0.911161f,   -0.911572f,   -0.911983f,   -0.912393f,  
 -0.912802f,   -0.913210f,   -0.913617f,   -0.914023f,   -0.914428f,   -0.914832f,   -0.915236f,   -0.915638f,   -0.916040f,   -0.916440f,  
 -0.916840f,   -0.917239f,   -0.917637f,   -0.918034f,   -0.918430f,   -0.918825f,   -0.919219f,   -0.919612f,   -0.920005f,   -0.920396f,  
 -0.920787f,   -0.921176f,   -0.921565f,   -0.921953f,   -0.922340f,   -0.922726f,   -0.923111f,   -0.923495f,   -0.923878f,   -0.924260f,  
 -0.924641f,   -0.925022f,   -0.925401f,   -0.925780f,   -0.926157f,   -0.926534f,   -0.926910f,   -0.927285f,   -0.927658f,   -0.928031f,  
 -0.928403f,   -0.928775f,   -0.929145f,   -0.929514f,   -0.929882f,   -0.930250f,   -0.930616f,   -0.930982f,   -0.931346f,   -0.931710f,  
 -0.932073f,   -0.932434f,   -0.932795f,   -0.933155f,   -0.933514f,   -0.933872f,   -0.934230f,   -0.934586f,   -0.934941f,   -0.935295f,  
 -0.935649f,   -0.936001f,   -0.936353f,   -0.936703f,   -0.937053f,   -0.937402f,   -0.937749f,   -0.938096f,   -0.938442f,   -0.938787f,  
 -0.939131f,   -0.939474f,   -0.939816f,   -0.940158f,   -0.940498f,   -0.940837f,   -0.941176f,   -0.941513f,   -0.941850f,   -0.942185f,  
 -0.942520f,   -0.942853f,   -0.943186f,   -0.943518f,   -0.943849f,   -0.944179f,   -0.944508f,   -0.944836f,   -0.945163f,   -0.945489f,  
 -0.945814f,   -0.946138f,   -0.946462f,   -0.946784f,   -0.947105f,   -0.947426f,   -0.947745f,   -0.948064f,   -0.948381f,   -0.948698f,  
 -0.949014f,   -0.949329f,   -0.949642f,   -0.949955f,   -0.950267f,   -0.950578f,   -0.950888f,   -0.951197f,   -0.951505f,   -0.951812f,  
 -0.952119f,   -0.952424f,   -0.952728f,   -0.953032f,   -0.953334f,   -0.953635f,   -0.953936f,   -0.954235f,   -0.954534f,   -0.954832f,  
 -0.955128f,   -0.955424f,   -0.955719f,   -0.956013f,   -0.956305f,   -0.956597f,   -0.956888f,   -0.957178f,   -0.957467f,   -0.957755f,  
 -0.958042f,   -0.958329f,   -0.958614f,   -0.958898f,   -0.959181f,   -0.959464f,   -0.959745f,   -0.960025f,   -0.960305f,   -0.960583f,  
 -0.960861f,   -0.961137f,   -0.961413f,   -0.961688f,   -0.961961f,   -0.962234f,   -0.962506f,   -0.962776f,   -0.963046f,   -0.963315f,  
 -0.963583f,   -0.963850f,   -0.964116f,   -0.964381f,   -0.964645f,   -0.964908f,   -0.965170f,   -0.965431f,   -0.965691f,   -0.965951f,  
 -0.966209f,   -0.966466f,   -0.966722f,   -0.966978f,   -0.967232f,   -0.967486f,   -0.967738f,   -0.967989f,   -0.968240f,   -0.968490f,  
 -0.968738f,   -0.968986f,   -0.969232f,   -0.969478f,   -0.969723f,   -0.969966f,   -0.970209f,   -0.970451f,   -0.970692f,   -0.970932f,  
 -0.971170f,   -0.971408f,   -0.971645f,   -0.971881f,   -0.972116f,   -0.972350f,   -0.972583f,   -0.972815f,   -0.973046f,   -0.973277f,  
 -0.973506f,   -0.973734f,   -0.973961f,   -0.974187f,   -0.974413f,   -0.974637f,   -0.974860f,   -0.975083f,   -0.975304f,   -0.975524f,  
 -0.975744f,   -0.975962f,   -0.976180f,   -0.976396f,   -0.976612f,   -0.976826f,   -0.977040f,   -0.977252f,   -0.977464f,   -0.977674f,  
 -0.977884f,   -0.978093f,   -0.978300f,   -0.978507f,   -0.978713f,   -0.978918f,   -0.979121f,   -0.979324f,   -0.979526f,   -0.979727f,  
 -0.979927f,   -0.980125f,   -0.980323f,   -0.980520f,   -0.980716f,   -0.980911f,   -0.981105f,   -0.981298f,   -0.981490f,   -0.981681f,  
 -0.981871f,   -0.982060f,   -0.982248f,   -0.982435f,   -0.982621f,   -0.982807f,   -0.982991f,   -0.983174f,   -0.983356f,   -0.983537f,  
 -0.983717f,   -0.983897f,   -0.984075f,   -0.984252f,   -0.984428f,   -0.984604f,   -0.984778f,   -0.984951f,   -0.985124f,   -0.985295f,  
 -0.985465f,   -0.985635f,   -0.985803f,   -0.985971f,   -0.986137f,   -0.986303f,   -0.986467f,   -0.986630f,   -0.986793f,   -0.986954f,  
 -0.987115f,   -0.987274f,   -0.987433f,   -0.987591f,   -0.987747f,   -0.987903f,   -0.988057f,   -0.988211f,   -0.988363f,   -0.988515f,  
 -0.988666f,   -0.988815f,   -0.988964f,   -0.989112f,   -0.989258f,   -0.989404f,   -0.989549f,   -0.989692f,   -0.989835f,   -0.989977f,  
 -0.990118f,   -0.990257f,   -0.990396f,   -0.990534f,   -0.990671f,   -0.990806f,   -0.990941f,   -0.991075f,   -0.991208f,   -0.991340f,  
 -0.991470f,   -0.991600f,   -0.991729f,   -0.991857f,   -0.991984f,   -0.992110f,   -0.992235f,   -0.992358f,   -0.992481f,   -0.992603f,  
 -0.992724f,   -0.992844f,   -0.992963f,   -0.993081f,   -0.993198f,   -0.993314f,   -0.993429f,   -0.993543f,   -0.993656f,   -0.993768f,  
 -0.993879f,   -0.993989f,   -0.994098f,   -0.994206f,   -0.994313f,   -0.994419f,   -0.994524f,   -0.994628f,   -0.994731f,   -0.994833f,  
 -0.994934f,   -0.995034f,   -0.995133f,   -0.995231f,   -0.995328f,   -0.995424f,   -0.995519f,   -0.995613f,   -0.995706f,   -0.995798f,  
 -0.995889f,   -0.995979f,   -0.996068f,   -0.996157f,   -0.996244f,   -0.996330f,   -0.996415f,   -0.996499f,   -0.996582f,   -0.996664f,  
 -0.996745f,   -0.996825f,   -0.996904f,   -0.996983f,   -0.997060f,   -0.997136f,   -0.997211f,   -0.997285f,   -0.997358f,   -0.997430f,  
 -0.997502f,   -0.997572f,   -0.997641f,   -0.997709f,   -0.997776f,   -0.997842f,   -0.997907f,   -0.997972f,   -0.998035f,   -0.998097f,  
 -0.998158f,   -0.998218f,   -0.998277f,   -0.998336f,   -0.998393f,   -0.998449f,   -0.998504f,   -0.998558f,   -0.998611f,   -0.998664f,  
 -0.998715f,   -0.998765f,   -0.998814f,   -0.998862f,   -0.998910f,   -0.998956f,   -0.999001f,   -0.999045f,   -0.999088f,   -0.999131f,  
 -0.999172f,   -0.999212f,   -0.999251f,   -0.999289f,   -0.999326f,   -0.999363f,   -0.999398f,   -0.999432f,   -0.999465f,   -0.999497f,  
 -0.999529f,   -0.999559f,   -0.999588f,   -0.999616f,   -0.999643f,   -0.999670f,   -0.999695f,   -0.999719f,   -0.999742f,   -0.999764f,  
 -0.999786f,   -0.999806f,   -0.999825f,   -0.999843f,   -0.999860f,   -0.999877f,   -0.999892f,   -0.999906f,   -0.999919f,   -0.999932f,  
 -0.999943f,   -0.999953f,   -0.999962f,   -0.999970f,   -0.999978f,   -0.999984f,   -0.999989f,   -0.999993f,   -0.999996f,   -0.999999f,  
 -1.000000f,   -1.000000f,   -0.999999f,   -0.999997f,   -0.999995f,   -0.999991f,   -0.999986f,   -0.999980f,   -0.999973f,   -0.999966f,  
 -0.999957f,   -0.999947f,   -0.999936f,   -0.999924f,   -0.999912f,   -0.999898f,   -0.999883f,   -0.999867f,   -0.999850f,   -0.999833f,  
 -0.999814f,   -0.999794f,   -0.999773f,   -0.999751f,   -0.999729f,   -0.999705f,   -0.999680f,   -0.999654f,   -0.999627f,   -0.999600f,  
 -0.999571f,   -0.999541f,   -0.999510f,   -0.999479f,   -0.999446f,   -0.999412f,   -0.999377f,   -0.999341f,   -0.999305f,   -0.999267f,  
 -0.999228f,   -0.999188f,   -0.999147f,   -0.999106f,   -0.999063f,   -0.999019f,   -0.998974f,   -0.998929f,   -0.998882f,   -0.998834f,  
 -0.998785f,   -0.998735f,   -0.998685f,   -0.998633f,   -0.998580f,   -0.998526f,   -0.998472f,   -0.998416f,   -0.998359f,   -0.998301f,  
 -0.998242f,   -0.998183f,   -0.998122f,   -0.998060f,   -0.997997f,   -0.997934f,   -0.997869f,   -0.997803f,   -0.997736f,   -0.997669f,  
 -0.997600f,   -0.997530f,   -0.997459f,   -0.997388f,   -0.997315f,   -0.997241f,   -0.997167f,   -0.997091f,   -0.997014f,   -0.996936f,  
 -0.996858f,   -0.996778f,   -0.996697f,   -0.996616f,   -0.996533f,   -0.996449f,   -0.996364f,   -0.996279f,   -0.996192f,   -0.996104f,  
 -0.996016f,   -0.995926f,   -0.995835f,   -0.995744f,   -0.995651f,   -0.995557f,   -0.995463f,   -0.995367f,   -0.995270f,   -0.995173f,  
 -0.995074f,   -0.994975f,   -0.994874f,   -0.994772f,   -0.994670f,   -0.994566f,   -0.994461f,   -0.994356f,   -0.994249f,   -0.994142f,  
 -0.994033f,   -0.993924f,   -0.993813f,   -0.993701f,   -0.993589f,   -0.993475f,   -0.993361f,   -0.993245f,   -0.993129f,   -0.993011f,  
 -0.992893f,   -0.992773f,   -0.992653f,   -0.992531f,   -0.992409f,   -0.992285f,   -0.992161f,   -0.992035f,   -0.991909f,   -0.991781f,  
 -0.991653f,   -0.991523f,   -0.991393f,   -0.991262f,   -0.991129f,   -0.990996f,   -0.990861f,   -0.990726f,   -0.990590f,   -0.990452f,  
 -0.990314f,   -0.990175f,   -0.990034f,   -0.989893f,   -0.989751f,   -0.989607f,   -0.989463f,   -0.989318f,   -0.989171f,   -0.989024f,  
 -0.988876f,   -0.988727f,   -0.988577f,   -0.988425f,   -0.988273f,   -0.988120f,   -0.987966f,   -0.987811f,   -0.987654f,   -0.987497f,  
 -0.987339f,   -0.987180f,   -0.987020f,   -0.986859f,   -0.986697f,   -0.986534f,   -0.986370f,   -0.986205f,   -0.986039f,   -0.985872f,  
 -0.985704f,   -0.985535f,   -0.985365f,   -0.985194f,   -0.985022f,   -0.984849f,   -0.984675f,   -0.984500f,   -0.984324f,   -0.984147f,  
 -0.983969f,   -0.983791f,   -0.983611f,   -0.983430f,   -0.983248f,   -0.983065f,   -0.982882f,   -0.982697f,   -0.982511f,   -0.982325f,  
 -0.982137f,   -0.981948f,   -0.981759f,   -0.981568f,   -0.981376f,   -0.981184f,   -0.980990f,   -0.980796f,   -0.980600f,   -0.980404f,  
 -0.980206f,   -0.980008f,   -0.979808f,   -0.979608f,   -0.979406f,   -0.979204f,   -0.979001f,   -0.978796f,   -0.978591f,   -0.978385f,  
 -0.978177f,   -0.977969f,   -0.977760f,   -0.977550f,   -0.977338f,   -0.977126f,   -0.976913f,   -0.976699f,   -0.976484f,   -0.976268f,  
 -0.976051f,   -0.975833f,   -0.975614f,   -0.975394f,   -0.975173f,   -0.974951f,   -0.974728f,   -0.974504f,   -0.974279f,   -0.974053f,  
 -0.973827f,   -0.973599f,   -0.973370f,   -0.973140f,   -0.972910f,   -0.972678f,   -0.972445f,   -0.972212f,   -0.971977f,   -0.971742f,  
 -0.971505f,   -0.971267f,   -0.971029f,   -0.970790f,   -0.970549f,   -0.970308f,   -0.970065f,   -0.969822f,   -0.969578f,   -0.969332f,  
 -0.969086f,   -0.968839f,   -0.968591f,   -0.968342f,   -0.968092f,   -0.967841f,   -0.967588f,   -0.967335f,   -0.967081f,   -0.966827f,  
 -0.966571f,   -0.966314f,   -0.966056f,   -0.965797f,   -0.965537f,   -0.965277f,   -0.965015f,   -0.964752f,   -0.964489f,   -0.964224f,  
 -0.963958f,   -0.963692f,   -0.963424f,   -0.963156f,   -0.962886f,   -0.962616f,   -0.962345f,   -0.962072f,   -0.961799f,   -0.961525f,  
 -0.961250f,   -0.960973f,   -0.960696f,   -0.960418f,   -0.960139f,   -0.959859f,   -0.959578f,   -0.959296f,   -0.959013f,   -0.958730f,  
 -0.958445f,   -0.958159f,   -0.957872f,   -0.957585f,   -0.957296f,   -0.957006f,   -0.956716f,   -0.956424f,   -0.956132f,   -0.955839f,  
 -0.955544f,   -0.955249f,   -0.954953f,   -0.954655f,   -0.954357f,   -0.954058f,   -0.953758f,   -0.953457f,   -0.953155f,   -0.952852f,  
 -0.952548f,   -0.952243f,   -0.951937f,   -0.951631f,   -0.951323f,   -0.951014f,   -0.950705f,   -0.950394f,   -0.950082f,   -0.949770f,  
 -0.949457f,   -0.949142f,   -0.948827f,   -0.948511f,   -0.948193f,   -0.947875f,   -0.947556f,   -0.947236f,   -0.946915f,   -0.946593f,  
 -0.946270f,   -0.945946f,   -0.945621f,   -0.945296f,   -0.944969f,   -0.944641f,   -0.944313f,   -0.943983f,   -0.943653f,   -0.943321f,  
 -0.942989f,   -0.942656f,   -0.942322f,   -0.941986f,   -0.941650f,   -0.941313f,   -0.940975f,   -0.940636f,   -0.940296f,   -0.939956f,  
 -0.939614f,   -0.939271f,   -0.938927f,   -0.938583f,   -0.938237f,   -0.937891f,   -0.937543f,   -0.937195f,   -0.936846f,   -0.936496f,  
 -0.936144f,   -0.935792f,   -0.935439f,   -0.935085f,   -0.934730f,   -0.934375f,   -0.934018f,   -0.933660f,   -0.933302f,   -0.932942f,  
 -0.932582f,   -0.932220f,   -0.931858f,   -0.931494f,   -0.931130f,   -0.930765f,   -0.930399f,   -0.930032f,   -0.929664f,   -0.929295f,  
 -0.928925f,   -0.928555f,   -0.928183f,   -0.927810f,   -0.927437f,   -0.927062f,   -0.926687f,   -0.926311f,   -0.925934f,   -0.925555f,  
 -0.925176f,   -0.924796f,   -0.924415f,   -0.924034f,   -0.923651f,   -0.923267f,   -0.922882f,   -0.922497f,   -0.922110f,   -0.921723f,  
 -0.921335f,   -0.920946f,   -0.920555f,   -0.920164f,   -0.919772f,   -0.919379f,   -0.918986f,   -0.918591f,   -0.918195f,   -0.917799f,  
 -0.917401f,   -0.917003f,   -0.916603f,   -0.916203f,   -0.915802f,   -0.915400f,   -0.914997f,   -0.914593f,   -0.914188f,   -0.913782f,  
 -0.913376f,   -0.912968f,   -0.912560f,   -0.912150f,   -0.911740f,   -0.911329f,   -0.910916f,   -0.910503f,   -0.910089f,   -0.909675f,  
 -0.909259f,   -0.908842f,   -0.908425f,   -0.908006f,   -0.907587f,   -0.907166f,   -0.906745f,   -0.906323f,   -0.905900f,   -0.905476f,  
 -0.905051f,   -0.904625f,   -0.904199f,   -0.903771f,   -0.903343f,   -0.902913f,   -0.902483f,   -0.902052f,   -0.901620f,   -0.901187f,  
 -0.900753f,   -0.900318f,   -0.899882f,   -0.899446f,   -0.899008f,   -0.898570f,   -0.898131f,   -0.897691f,   -0.897249f,   -0.896807f,  
 -0.896365f,   -0.895921f,   -0.895476f,   -0.895031f,   -0.894584f,   -0.894137f,   -0.893689f,   -0.893239f,   -0.892789f,   -0.892339f,  
 -0.891887f,   -0.891434f,   -0.890980f,   -0.890526f,   -0.890071f,   -0.889614f,   -0.889157f,   -0.888699f,   -0.888240f,   -0.887780f,  
 -0.887320f,   -0.886858f,   -0.886396f,   -0.885932f,   -0.885468f,   -0.885003f,   -0.884537f,   -0.884070f,   -0.883602f,   -0.883133f,  
 -0.882664f,   -0.882193f,   -0.881722f,   -0.881250f,   -0.880777f,   -0.880303f,   -0.879828f,   -0.879352f,   -0.878876f,   -0.878398f,  
 -0.877920f,   -0.877440f,   -0.876960f,   -0.876479f,   -0.875997f,   -0.875515f,   -0.875031f,   -0.874547f,   -0.874061f,   -0.873575f,  
 -0.873088f,   -0.872600f,   -0.872111f,   -0.871621f,   -0.871131f,   -0.870639f,   -0.870147f,   -0.869653f,   -0.869159f,   -0.868664f,  
 -0.868169f,   -0.867672f,   -0.867174f,   -0.866676f,   -0.866177f,   -0.865676f,   -0.865175f,   -0.864673f,   -0.864171f,   -0.863667f,  
 -0.863163f,   -0.862657f,   -0.862151f,   -0.861644f,   -0.861136f,   -0.860627f,   -0.860117f,   -0.859607f,   -0.859096f,   -0.858583f,  
 -0.858070f,   -0.857556f,   -0.857041f,   -0.856526f,   -0.856009f,   -0.855492f,   -0.854974f,   -0.854454f,   -0.853935f,   -0.853414f,  
 -0.852892f,   -0.852370f,   -0.851846f,   -0.851322f,   -0.850797f,   -0.850271f,   -0.849744f,   -0.849217f,   -0.848688f,   -0.848159f,  
 -0.847629f,   -0.847098f,   -0.846566f,   -0.846033f,   -0.845499f,   -0.844965f,   -0.844430f,   -0.843894f,   -0.843357f,   -0.842819f,  
 -0.842280f,   -0.841741f,   -0.841201f,   -0.840660f,   -0.840118f,   -0.839575f,   -0.839031f,   -0.838487f,   -0.837941f,   -0.837395f,  
 -0.836848f,   -0.836300f,   -0.835751f,   -0.835202f,   -0.834652f,   -0.834100f,   -0.833548f,   -0.832995f,   -0.832442f,   -0.831887f,  
 -0.831332f,   -0.830776f,   -0.830219f,   -0.829661f,   -0.829102f,   -0.828543f,   -0.827982f,   -0.827421f,   -0.826859f,   -0.826296f,  
 -0.825733f,   -0.825168f,   -0.824603f,   -0.824037f,   -0.823470f,   -0.822902f,   -0.822333f,   -0.821764f,   -0.821194f,   -0.820623f,  
 -0.820051f,   -0.819478f,   -0.818905f,   -0.818330f,   -0.817755f,   -0.817179f,   -0.816602f,   -0.816025f,   -0.815446f,   -0.814867f,  
 -0.814287f,   -0.813706f,   -0.813124f,   -0.812542f,   -0.811959f,   -0.811375f,   -0.810790f,   -0.810204f,   -0.809617f,   -0.809030f,  
 -0.808442f,   -0.807853f,   -0.807263f,   -0.806672f,   -0.806081f,   -0.805489f,   -0.804896f,   -0.804302f,   -0.803707f,   -0.803112f,  
 -0.802516f,   -0.801919f,   -0.801321f,   -0.800722f,   -0.800123f,   -0.799523f,   -0.798922f,   -0.798320f,   -0.797717f,   -0.797114f,  
 -0.796509f,   -0.795904f,   -0.795299f,   -0.794692f,   -0.794085f,   -0.793476f,   -0.792867f,   -0.792258f,   -0.791647f,   -0.791036f,  
 -0.790423f,   -0.789810f,   -0.789197f,   -0.788582f,   -0.787967f,   -0.787351f,   -0.786734f,   -0.786116f,   -0.785498f,   -0.784878f,  
 -0.784258f,   -0.783638f,   -0.783016f,   -0.782394f,   -0.781770f,   -0.781146f,   -0.780522f,   -0.779896f,   -0.779270f,   -0.778643f,  
 -0.778015f,   -0.777386f,   -0.776757f,   -0.776127f,   -0.775496f,   -0.774864f,   -0.774231f,   -0.773598f,   -0.772964f,   -0.772329f,  
 -0.771694f,   -0.771057f,   -0.770420f,   -0.769782f,   -0.769144f,   -0.768504f,   -0.767864f,   -0.767223f,   -0.766581f,   -0.765939f,  
 -0.765295f,   -0.764651f,   -0.764006f,   -0.763361f,   -0.762714f,   -0.762067f,   -0.761419f,   -0.760771f,   -0.760121f,   -0.759471f,  
 -0.758820f,   -0.758169f,   -0.757516f,   -0.756863f,   -0.756209f,   -0.755554f,   -0.754899f,   -0.754243f,   -0.753586f,   -0.752928f,  
 -0.752269f,   -0.751610f,   -0.750950f,   -0.750290f,   -0.749628f,   -0.748966f,   -0.748303f,   -0.747639f,   -0.746975f,   -0.746309f,  
 -0.745643f,   -0.744977f,   -0.744309f,   -0.743641f,   -0.742972f,   -0.742302f,   -0.741632f,   -0.740961f,   -0.740289f,   -0.739616f,  
 -0.738943f,   -0.738269f,   -0.737594f,   -0.736918f,   -0.736242f,   -0.735565f,   -0.734887f,   -0.734208f,   -0.733529f,   -0.732849f,  
 -0.732168f,   -0.731487f,   -0.730805f,   -0.730122f,   -0.729438f,   -0.728754f,   -0.728068f,   -0.727382f,   -0.726696f,   -0.726009f,  
 -0.725321f,   -0.724632f,   -0.723942f,   -0.723252f,   -0.722561f,   -0.721869f,   -0.721177f,   -0.720484f,   -0.719790f,   -0.719096f,  
 -0.718400f,   -0.717704f,   -0.717008f,   -0.716310f,   -0.715612f,   -0.714913f,   -0.714214f,   -0.713513f,   -0.712812f,   -0.712111f,  
 -0.711408f,   -0.710705f,   -0.710001f,   -0.709297f,   -0.708591f,   -0.707885f,   -0.707179f,   -0.706471f,   -0.705763f,   -0.705054f,  
 -0.704345f,   -0.703635f,   -0.702924f,   -0.702212f,   -0.701500f,   -0.700787f,   -0.700073f,   -0.699359f,   -0.698644f,   -0.697928f,  
 -0.697211f,   -0.696494f,   -0.695776f,   -0.695058f,   -0.694338f,   -0.693618f,   -0.692898f,   -0.692176f,   -0.691454f,   -0.690731f,  
 -0.690008f,   -0.689284f,   -0.688559f,   -0.687833f,   -0.687107f,   -0.686380f,   -0.685653f,   -0.684924f,   -0.684195f,   -0.683466f,  
 -0.682735f,   -0.682004f,   -0.681273f,   -0.680540f,   -0.679807f,   -0.679074f,   -0.678339f,   -0.677604f,   -0.676868f,   -0.676132f,  
 -0.675395f,   -0.674657f,   -0.673919f,   -0.673179f,   -0.672440f,   -0.671699f,   -0.670958f,   -0.670216f,   -0.669474f,   -0.668730f,  
 -0.667987f,   -0.667242f,   -0.666497f,   -0.665751f,   -0.665005f,   -0.664257f,   -0.663510f,   -0.662761f,   -0.662012f,   -0.661262f,  
 -0.660512f,   -0.659760f,   -0.659009f,   -0.658256f,   -0.657503f,   -0.656749f,   -0.655995f,   -0.655240f,   -0.654484f,   -0.653728f,  
 -0.652970f,   -0.652213f,   -0.651454f,   -0.650695f,   -0.649936f,   -0.649175f,   -0.648414f,   -0.647653f,   -0.646891f,   -0.646128f,  
 -0.645364f,   -0.644600f,   -0.643835f,   -0.643070f,   -0.642303f,   -0.641537f,   -0.640769f,   -0.640001f,   -0.639233f,   -0.638463f,  
 -0.637693f,   -0.636923f,   -0.636151f,   -0.635380f,   -0.634607f,   -0.633834f,   -0.633060f,   -0.632286f,   -0.631511f,   -0.630735f,  
 -0.629959f,   -0.629182f,   -0.628404f,   -0.627626f,   -0.626847f,   -0.626068f,   -0.625287f,   -0.624507f,   -0.623725f,   -0.622944f,  
 -0.622161f,   -0.621378f,   -0.620594f,   -0.619809f,   -0.619024f,   -0.618239f,   -0.617452f,   -0.616666f,   -0.615878f,   -0.615090f,  
 -0.614301f,   -0.613512f,   -0.612722f,   -0.611931f,   -0.611140f,   -0.610348f,   -0.609556f,   -0.608763f,   -0.607969f,   -0.607175f,  
 -0.606380f,   -0.605584f,   -0.604788f,   -0.603992f,   -0.603194f,   -0.602396f,   -0.601598f,   -0.600799f,   -0.599999f,   -0.599199f,  
 -0.598398f,   -0.597596f,   -0.596794f,   -0.595992f,   -0.595188f,   -0.594384f,   -0.593580f,   -0.592775f,   -0.591969f,   -0.591163f,  
 -0.590356f,   -0.589549f,   -0.588741f,   -0.587932f,   -0.587123f,   -0.586313f,   -0.585503f,   -0.584692f,   -0.583880f,   -0.583068f,  
 -0.582255f,   -0.581442f,   -0.580628f,   -0.579814f,   -0.578999f,   -0.578183f,   -0.577367f,   -0.576550f,   -0.575733f,   -0.574915f,  
 -0.574096f,   -0.573277f,   -0.572457f,   -0.571637f,   -0.570816f,   -0.569995f,   -0.569173f,   -0.568351f,   -0.567528f,   -0.566704f,  
 -0.565880f,   -0.565055f,   -0.564230f,   -0.563404f,   -0.562577f,   -0.561750f,   -0.560923f,   -0.560095f,   -0.559266f,   -0.558437f,  
 -0.557607f,   -0.556776f,   -0.555945f,   -0.555114f,   -0.554282f,   -0.553449f,   -0.552616f,   -0.551782f,   -0.550948f,   -0.550113f,  
 -0.549278f,   -0.548442f,   -0.547606f,   -0.546769f,   -0.545931f,   -0.545093f,   -0.544254f,   -0.543415f,   -0.542575f,   -0.541735f,  
 -0.540894f,   -0.540053f,   -0.539211f,   -0.538368f,   -0.537526f,   -0.536682f,   -0.535838f,   -0.534993f,   -0.534148f,   -0.533303f,  
 -0.532456f,   -0.531610f,   -0.530762f,   -0.529915f,   -0.529066f,   -0.528217f,   -0.527368f,   -0.526518f,   -0.525668f,   -0.524817f,  
 -0.523965f,   -0.523113f,   -0.522261f,   -0.521408f,   -0.520554f,   -0.519700f,   -0.518845f,   -0.517990f,   -0.517135f,   -0.516279f,  
 -0.515422f,   -0.514565f,   -0.513707f,   -0.512849f,   -0.511990f,   -0.511131f,   -0.510271f,   -0.509411f,   -0.508550f,   -0.507689f,  
 -0.506827f,   -0.505965f,   -0.505102f,   -0.504238f,   -0.503375f,   -0.502510f,   -0.501645f,   -0.500780f,   -0.499914f,   -0.499048f,  
 -0.498181f,   -0.497314f,   -0.496446f,   -0.495578f,   -0.494709f,   -0.493840f,   -0.492970f,   -0.492100f,   -0.491229f,   -0.490357f,  
 -0.489486f,   -0.488613f,   -0.487741f,   -0.486867f,   -0.485994f,   -0.485120f,   -0.484245f,   -0.483370f,   -0.482494f,   -0.481618f,  
 -0.480741f,   -0.479864f,   -0.478987f,   -0.478109f,   -0.477230f,   -0.476351f,   -0.475471f,   -0.474591f,   -0.473711f,   -0.472830f,  
 -0.471949f,   -0.471067f,   -0.470185f,   -0.469302f,   -0.468418f,   -0.467535f,   -0.466651f,   -0.465766f,   -0.464881f,   -0.463995f,  
 -0.463109f,   -0.462222f,   -0.461336f,   -0.460448f,   -0.459560f,   -0.458672f,   -0.457783f,   -0.456894f,   -0.456004f,   -0.455114f,  
 -0.454223f,   -0.453332f,   -0.452440f,   -0.451548f,   -0.450656f,   -0.449763f,   -0.448870f,   -0.447976f,   -0.447081f,   -0.446187f,  
 -0.445292f,   -0.444396f,   -0.443500f,   -0.442603f,   -0.441706f,   -0.440809f,   -0.439911f,   -0.439013f,   -0.438114f,   -0.437215f,  
 -0.436316f,   -0.435416f,   -0.434515f,   -0.433614f,   -0.432713f,   -0.431811f,   -0.430909f,   -0.430006f,   -0.429103f,   -0.428200f,  
 -0.427296f,   -0.426392f,   -0.425487f,   -0.424582f,   -0.423676f,   -0.422770f,   -0.421864f,   -0.420957f,   -0.420050f,   -0.419142f,  
 -0.418234f,   -0.417325f,   -0.416416f,   -0.415507f,   -0.414597f,   -0.413687f,   -0.412776f,   -0.411865f,   -0.410954f,   -0.410042f,  
 -0.409130f,   -0.408217f,   -0.407304f,   -0.406390f,   -0.405476f,   -0.404562f,   -0.403647f,   -0.402732f,   -0.401817f,   -0.400901f,  
 -0.399984f,   -0.399068f,   -0.398151f,   -0.397233f,   -0.396315f,   -0.395397f,   -0.394478f,   -0.393559f,   -0.392640f,   -0.391720f,  
 -0.390799f,   -0.389879f,   -0.388958f,   -0.388036f,   -0.387114f,   -0.386192f,   -0.385270f,   -0.384347f,   -0.383423f,   -0.382499f,  
 -0.381575f,   -0.380651f,   -0.379726f,   -0.378800f,   -0.377875f,   -0.376949f,   -0.376022f,   -0.375096f,   -0.374168f,   -0.373241f,  
 -0.372313f,   -0.371385f,   -0.370456f,   -0.369527f,   -0.368598f,   -0.367668f,   -0.366738f,   -0.365807f,   -0.364876f,   -0.363945f,  
 -0.363013f,   -0.362081f,   -0.361149f,   -0.360216f,   -0.359283f,   -0.358350f,   -0.357416f,   -0.356482f,   -0.355548f,   -0.354613f,  
 -0.353678f,   -0.352742f,   -0.351806f,   -0.350870f,   -0.349933f,   -0.348996f,   -0.348059f,   -0.347121f,   -0.346183f,   -0.345245f,  
 -0.344306f,   -0.343367f,   -0.342428f,   -0.341488f,   -0.340548f,   -0.339608f,   -0.338667f,   -0.337726f,   -0.336785f,   -0.335843f,  
 -0.334901f,   -0.333958f,   -0.333016f,   -0.332072f,   -0.331129f,   -0.330185f,   -0.329241f,   -0.328297f,   -0.327352f,   -0.326407f,  
 -0.325462f,   -0.324516f,   -0.323570f,   -0.322623f,   -0.321677f,   -0.320730f,   -0.319782f,   -0.318835f,   -0.317887f,   -0.316939f,  
 -0.315990f,   -0.315041f,   -0.314092f,   -0.313142f,   -0.312192f,   -0.311242f,   -0.310292f,   -0.309341f,   -0.308390f,   -0.307438f,  
 -0.306487f,   -0.305535f,   -0.304582f,   -0.303630f,   -0.302677f,   -0.301723f,   -0.300770f,   -0.299816f,   -0.298862f,   -0.297907f,  
 -0.296953f,   -0.295998f,   -0.295042f,   -0.294087f,   -0.293131f,   -0.292175f,   -0.291218f,   -0.290261f,   -0.289304f,   -0.288347f,  
 -0.287389f,   -0.286431f,   -0.285473f,   -0.284514f,   -0.283556f,   -0.282596f,   -0.281637f,   -0.280677f,   -0.279718f,   -0.278757f,  
 -0.277797f,   -0.276836f,   -0.275875f,   -0.274914f,   -0.273952f,   -0.272990f,   -0.272028f,   -0.271066f,   -0.270103f,   -0.269140f,  
 -0.268177f,   -0.267213f,   -0.266249f,   -0.265285f,   -0.264321f,   -0.263356f,   -0.262392f,   -0.261427f,   -0.260461f,   -0.259496f,  
 -0.258530f,   -0.257564f,   -0.256597f,   -0.255631f,   -0.254664f,   -0.253696f,   -0.252729f,   -0.251761f,   -0.250793f,   -0.249825f,  
 -0.248857f,   -0.247888f,   -0.246919f,   -0.245950f,   -0.244981f,   -0.244011f,   -0.243041f,   -0.242071f,   -0.241101f,   -0.240130f,  
 -0.239159f,   -0.238188f,   -0.237217f,   -0.236245f,   -0.235273f,   -0.234301f,   -0.233329f,   -0.232357f,   -0.231384f,   -0.230411f,  
 -0.229438f,   -0.228464f,   -0.227491f,   -0.226517f,   -0.225543f,   -0.224568f,   -0.223594f,   -0.222619f,   -0.221644f,   -0.220669f,  
 -0.219693f,   -0.218717f,   -0.217742f,   -0.216765f,   -0.215789f,   -0.214813f,   -0.213836f,   -0.212859f,   -0.211882f,   -0.210904f,  
 -0.209927f,   -0.208949f,   -0.207971f,   -0.206992f,   -0.206014f,   -0.205035f,   -0.204057f,   -0.203077f,   -0.202098f,   -0.201119f,  
 -0.200139f,   -0.199159f,   -0.198179f,   -0.197199f,   -0.196218f,   -0.195238f,   -0.194257f,   -0.193276f,   -0.192295f,   -0.191313f,  
 -0.190332f,   -0.189350f,   -0.188368f,   -0.187386f,   -0.186403f,   -0.185421f,   -0.184438f,   -0.183455f,   -0.182472f,   -0.181488f,  
 -0.180505f,   -0.179521f,   -0.178537f,   -0.177553f,   -0.176569f,   -0.175585f,   -0.174600f,   -0.173616f,   -0.172631f,   -0.171646f,  
 -0.170660f,   -0.169675f,   -0.168689f,   -0.167704f,   -0.166718f,   -0.165732f,   -0.164745f,   -0.163759f,   -0.162772f,   -0.161786f,  
 -0.160799f,   -0.159812f,   -0.158824f,   -0.157837f,   -0.156849f,   -0.155862f,   -0.154874f,   -0.153886f,   -0.152898f,   -0.151909f,  
 -0.150921f,   -0.149932f,   -0.148944f,   -0.147955f,   -0.146966f,   -0.145976f,   -0.144987f,   -0.143998f,   -0.143008f,   -0.142018f,  
 -0.141028f,   -0.140038f,   -0.139048f,   -0.138057f,   -0.137067f,   -0.136076f,   -0.135086f,   -0.134095f,   -0.133104f,   -0.132112f,  
 -0.131121f,   -0.130130f,   -0.129138f,   -0.128147f,   -0.127155f,   -0.126163f,   -0.125171f,   -0.124178f,   -0.123186f,   -0.122194f,  
 -0.121201f,   -0.120208f,   -0.119216f,   -0.118223f,   -0.117230f,   -0.116237f,   -0.115243f,   -0.114250f,   -0.113256f,   -0.112263f,  
 -0.111269f,   -0.110275f,   -0.109281f,   -0.108287f,   -0.107293f,   -0.106299f,   -0.105304f,   -0.104310f,   -0.103315f,   -0.102320f,  
 -0.101326f,   -0.100331f,   -0.099336f,   -0.098341f,   -0.097345f,   -0.096350f,   -0.095355f,   -0.094359f,   -0.093364f,   -0.092368f,  
 -0.091372f,   -0.090376f,   -0.089380f,   -0.088384f,   -0.087388f,   -0.086392f,   -0.085396f,   -0.084399f,   -0.083403f,   -0.082406f,  
 -0.081410f,   -0.080413f,   -0.079416f,   -0.078419f,   -0.077422f,   -0.076425f,   -0.075428f,   -0.074431f,   -0.073434f,   -0.072436f,  
 -0.071439f,   -0.070441f,   -0.069444f,   -0.068446f,   -0.067449f,   -0.066451f,   -0.065453f,   -0.064455f,   -0.063457f,   -0.062459f,  
 -0.061461f,   -0.060463f,   -0.059465f,   -0.058466f,   -0.057468f,   -0.056470f,   -0.055471f,   -0.054473f,   -0.053474f,   -0.052476f,  
 -0.051477f,   -0.050478f,   -0.049480f,   -0.048481f,   -0.047482f,   -0.046483f,   -0.045484f,   -0.044485f,   -0.043486f,   -0.042487f,  
 -0.041488f,   -0.040489f,   -0.039490f,   -0.038490f,   -0.037491f,   -0.036492f,   -0.035492f,   -0.034493f,   -0.033494f,   -0.032494f,  
 -0.031495f,   -0.030495f,   -0.029496f,   -0.028496f,   -0.027496f,   -0.026497f,   -0.025497f,   -0.024497f,   -0.023498f,   -0.022498f,  
 -0.021498f,   -0.020498f,   -0.019499f,   -0.018499f,   -0.017499f,   -0.016499f,   -0.015499f,   -0.014499f,   -0.013499f,   -0.012500f,  
 -0.011500f,   -0.010500f,   -0.009500f,   -0.008500f,   -0.007500f,   -0.006500f,   -0.005500f,   -0.004500f,   -0.003500f,   -0.002500f,  
 -0.001500f,   -0.000500f,    0.000500f,    0.001500f,    0.002500f,    0.003500f,    0.004500f,    0.005500f,    0.006500f,    0.007500f,  
  0.008500f,    0.009500f,    0.010500f,    0.011500f,    0.012500f,    0.013500f,    0.014500f,    0.015500f,    0.016499f,    0.017499f,  
  0.018499f,    0.019499f,    0.020499f,    0.021498f,    0.022498f,    0.023498f,    0.024498f,    0.025497f,    0.026497f,    0.027497f,  
  0.028496f,    0.029496f,    0.030495f,    0.031495f,    0.032494f,    0.033494f,    0.034493f,    0.035493f,    0.036492f,    0.037491f,  
  0.038491f,    0.039490f,    0.040489f,    0.041488f,    0.042487f,    0.043486f,    0.044485f,    0.045484f,    0.046483f,    0.047482f,  
  0.048481f,    0.049480f,    0.050479f,    0.051477f,    0.052476f,    0.053475f,    0.054473f,    0.055472f,    0.056470f,    0.057468f,  
  0.058467f,    0.059465f,    0.060463f,    0.061461f,    0.062459f,    0.063457f,    0.064455f,    0.065453f,    0.066451f,    0.067449f,  
  0.068447f,    0.069444f,    0.070442f,    0.071439f,    0.072437f,    0.073434f,    0.074431f,    0.075428f,    0.076426f,    0.077423f,  
  0.078420f,    0.079416f,    0.080413f,    0.081410f,    0.082407f,    0.083403f,    0.084400f,    0.085396f,    0.086392f,    0.087389f,  
  0.088385f,    0.089381f,    0.090377f,    0.091373f,    0.092368f,    0.093364f,    0.094360f,    0.095355f,    0.096350f,    0.097346f,  
  0.098341f,    0.099336f,    0.100331f,    0.101326f,    0.102321f,    0.103315f,    0.104310f,    0.105305f,    0.106299f,    0.107293f,  
  0.108287f,    0.109281f,    0.110275f,    0.111269f,    0.112263f,    0.113257f,    0.114250f,    0.115244f,    0.116237f,    0.117230f,  
  0.118223f,    0.119216f,    0.120209f,    0.121201f,    0.122194f,    0.123186f,    0.124179f,    0.125171f,    0.126163f,    0.127155f,  
  0.128147f,    0.129139f,    0.130130f,    0.131121f,    0.132113f,    0.133104f,    0.134095f,    0.135086f,    0.136077f,    0.137067f,  
  0.138058f,    0.139048f,    0.140038f,    0.141028f,    0.142018f,    0.143008f,    0.143998f,    0.144987f,    0.145977f,    0.146966f,  
  0.147955f,    0.148944f,    0.149933f,    0.150921f,    0.151910f,    0.152898f,    0.153886f,    0.154874f,    0.155862f,    0.156850f,  
  0.157837f,    0.158825f,    0.159812f,    0.160799f,    0.161786f,    0.162773f,    0.163759f,    0.164746f,    0.165732f,    0.166718f,  
  0.167704f,    0.168690f,    0.169675f,    0.170661f,    0.171646f,    0.172631f,    0.173616f,    0.174601f,    0.175585f,    0.176570f,  
  0.177554f,    0.178538f,    0.179522f,    0.180505f,    0.181489f,    0.182472f,    0.183455f,    0.184438f,    0.185421f,    0.186403f,  
  0.187386f,    0.188368f,    0.189350f,    0.190332f,    0.191313f,    0.192295f,    0.193276f,    0.194257f,    0.195238f,    0.196219f,  
  0.197199f,    0.198179f,    0.199159f,    0.200139f,    0.201119f,    0.202098f,    0.203078f,    0.204057f,    0.205036f,    0.206014f,  
  0.206993f,    0.207971f,    0.208949f,    0.209927f,    0.210904f,    0.211882f,    0.212859f,    0.213836f,    0.214813f,    0.215789f,  
  0.216766f,    0.217742f,    0.218718f,    0.219693f,    0.220669f,    0.221644f,    0.222619f,    0.223594f,    0.224568f,    0.225543f,  
  0.226517f,    0.227491f,    0.228464f,    0.229438f,    0.230411f,    0.231384f,    0.232357f,    0.233329f,    0.234302f,    0.235274f,  
  0.236246f,    0.237217f,    0.238188f,    0.239160f,    0.240130f,    0.241101f,    0.242071f,    0.243042f,    0.244011f,    0.244981f,  
  0.245950f,    0.246920f,    0.247889f,    0.248857f,    0.249826f,    0.250794f,    0.251762f,    0.252729f,    0.253697f,    0.254664f,  
  0.255631f,    0.256597f,    0.257564f,    0.258530f,    0.259496f,    0.260461f,    0.261427f,    0.262392f,    0.263357f,    0.264321f,  
  0.265286f,    0.266250f,    0.267213f,    0.268177f,    0.269140f,    0.270103f,    0.271066f,    0.272028f,    0.272990f,    0.273952f,  
  0.274914f,    0.275875f,    0.276836f,    0.277797f,    0.278758f,    0.279718f,    0.280678f,    0.281637f,    0.282597f,    0.283556f,  
  0.284515f,    0.285473f,    0.286431f,    0.287389f,    0.288347f,    0.289304f,    0.290262f,    0.291218f,    0.292175f,    0.293131f,  
  0.294087f,    0.295043f,    0.295998f,    0.296953f,    0.297908f,    0.298862f,    0.299816f,    0.300770f,    0.301724f,    0.302677f,  
  0.303630f,    0.304583f,    0.305535f,    0.306487f,    0.307439f,    0.308390f,    0.309341f,    0.310292f,    0.311242f,    0.312193f,  
  0.313143f,    0.314092f,    0.315041f,    0.315990f,    0.316939f,    0.317887f,    0.318835f,    0.319783f,    0.320730f,    0.321677f,  
  0.322624f,    0.323570f,    0.324516f,    0.325462f,    0.326407f,    0.327352f,    0.328297f,    0.329241f,    0.330186f,    0.331129f,  
  0.332073f,    0.333016f,    0.333959f,    0.334901f,    0.335843f,    0.336785f,    0.337726f,    0.338667f,    0.339608f,    0.340548f,  
  0.341489f,    0.342428f,    0.343368f,    0.344307f,    0.345245f,    0.346184f,    0.347122f,    0.348059f,    0.348997f,    0.349934f,  
  0.350870f,    0.351806f,    0.352742f,    0.353678f,    0.354613f,    0.355548f,    0.356482f,    0.357416f,    0.358350f,    0.359284f,  
  0.360217f,    0.361149f,    0.362082f,    0.363014f,    0.363945f,    0.364877f,    0.365807f,    0.366738f,    0.367668f,    0.368598f,  
  0.369527f,    0.370456f,    0.371385f,    0.372313f,    0.373241f,    0.374169f,    0.375096f,    0.376023f,    0.376949f,    0.377875f,  
  0.378801f,    0.379726f,    0.380651f,    0.381576f,    0.382500f,    0.383423f,    0.384347f,    0.385270f,    0.386192f,    0.387115f,  
  0.388036f,    0.388958f,    0.389879f,    0.390800f,    0.391720f,    0.392640f,    0.393559f,    0.394478f,    0.395397f,    0.396315f,  
  0.397233f,    0.398151f,    0.399068f,    0.399985f,    0.400901f,    0.401817f,    0.402732f,    0.403648f,    0.404562f,    0.405477f,  
  0.406391f,    0.407304f,    0.408217f,    0.409130f,    0.410042f,    0.410954f,    0.411865f,    0.412776f,    0.413687f,    0.414597f,  
  0.415507f,    0.416416f,    0.417325f,    0.418234f,    0.419142f,    0.420050f,    0.420957f,    0.421864f,    0.422770f,    0.423676f,  
  0.424582f,    0.425487f,    0.426392f,    0.427296f,    0.428200f,    0.429104f,    0.430007f,    0.430909f,    0.431811f,    0.432713f,  
  0.433615f,    0.434515f,    0.435416f,    0.436316f,    0.437215f,    0.438115f,    0.439013f,    0.439912f,    0.440809f,    0.441707f,  
  0.442604f,    0.443500f,    0.444396f,    0.445292f,    0.446187f,    0.447082f,    0.447976f,    0.448870f,    0.449763f,    0.450656f,  
  0.451549f,    0.452441f,    0.453332f,    0.454223f,    0.455114f,    0.456004f,    0.456894f,    0.457783f,    0.458672f,    0.459560f,  
  0.460448f,    0.461336f,    0.462223f,    0.463109f,    0.463995f,    0.464881f,    0.465766f,    0.466651f,    0.467535f,    0.468419f,  
  0.469302f,    0.470185f,    0.471067f,    0.471949f,    0.472830f,    0.473711f,    0.474592f,    0.475472f,    0.476351f,    0.477230f,  
  0.478109f,    0.478987f,    0.479864f,    0.480742f,    0.481618f,    0.482494f,    0.483370f,    0.484245f,    0.485120f,    0.485994f,  
  0.486868f,    0.487741f,    0.488614f,    0.489486f,    0.490358f,    0.491229f,    0.492100f,    0.492970f,    0.493840f,    0.494709f,  
  0.495578f,    0.496446f,    0.497314f,    0.498181f,    0.499048f,    0.499915f,    0.500780f,    0.501646f,    0.502511f,    0.503375f,  
  0.504239f,    0.505102f,    0.505965f,    0.506827f,    0.507689f,    0.508550f,    0.509411f,    0.510271f,    0.511131f,    0.511990f,  
  0.512849f,    0.513707f,    0.514565f,    0.515422f,    0.516279f,    0.517135f,    0.517991f,    0.518846f,    0.519700f,    0.520554f,  
  0.521408f,    0.522261f,    0.523114f,    0.523966f,    0.524817f,    0.525668f,    0.526518f,    0.527368f,    0.528218f,    0.529067f,  
  0.529915f,    0.530763f,    0.531610f,    0.532457f,    0.533303f,    0.534148f,    0.534994f,    0.535838f,    0.536682f,    0.537526f,  
  0.538369f,    0.539211f,    0.540053f,    0.540894f,    0.541735f,    0.542576f,    0.543415f,    0.544254f,    0.545093f,    0.545931f,  
  0.546769f,    0.547606f,    0.548442f,    0.549278f,    0.550114f,    0.550948f,    0.551783f,    0.552616f,    0.553449f,    0.554282f,  
  0.555114f,    0.555946f,    0.556777f,    0.557607f,    0.558437f,    0.559266f,    0.560095f,    0.560923f,    0.561750f,    0.562578f,  
  0.563404f,    0.564230f,    0.565055f,    0.565880f,    0.566704f,    0.567528f,    0.568351f,    0.569173f,    0.569995f,    0.570817f,  
  0.571637f,    0.572458f,    0.573277f,    0.574096f,    0.574915f,    0.575733f,    0.576550f,    0.577367f,    0.578183f,    0.578999f,  
  0.579814f,    0.580628f,    0.581442f,    0.582255f,    0.583068f,    0.583880f,    0.584692f,    0.585503f,    0.586313f,    0.587123f,  
  0.587932f,    0.588741f,    0.589549f,    0.590356f,    0.591163f,    0.591969f,    0.592775f,    0.593580f,    0.594385f,    0.595188f,  
  0.595992f,    0.596794f,    0.597597f,    0.598398f,    0.599199f,    0.599999f,    0.600799f,    0.601598f,    0.602397f,    0.603194f,  
  0.603992f,    0.604788f,    0.605585f,    0.606380f,    0.607175f,    0.607969f,    0.608763f,    0.609556f,    0.610348f,    0.611140f,  
  0.611931f,    0.612722f,    0.613512f,    0.614301f,    0.615090f,    0.615878f,    0.616666f,    0.617453f,    0.618239f,    0.619025f,  
  0.619810f,    0.620594f,    0.621378f,    0.622161f,    0.622944f,    0.623726f,    0.624507f,    0.625288f,    0.626068f,    0.626847f,  
  0.627626f,    0.628404f,    0.629182f,    0.629959f,    0.630735f,    0.631511f,    0.632286f,    0.633060f,    0.633834f,    0.634607f,  
  0.635380f,    0.636152f,    0.636923f,    0.637693f,    0.638463f,    0.639233f,    0.640001f,    0.640770f,    0.641537f,    0.642304f,  
  0.643070f,    0.643835f,    0.644600f,    0.645364f,    0.646128f,    0.646891f,    0.647653f,    0.648415f,    0.649176f,    0.649936f,  
  0.650696f,    0.651455f,    0.652213f,    0.652971f,    0.653728f,    0.654484f,    0.655240f,    0.655995f,    0.656749f,    0.657503f,  
  0.658256f,    0.659009f,    0.659761f,    0.660512f,    0.661262f,    0.662012f,    0.662761f,    0.663510f,    0.664258f,    0.665005f,  
  0.665751f,    0.666497f,    0.667242f,    0.667987f,    0.668731f,    0.669474f,    0.670216f,    0.670958f,    0.671699f,    0.672440f,  
  0.673180f,    0.673919f,    0.674657f,    0.675395f,    0.676132f,    0.676869f,    0.677604f,    0.678339f,    0.679074f,    0.679808f,  
  0.680541f,    0.681273f,    0.682005f,    0.682736f,    0.683466f,    0.684196f,    0.684925f,    0.685653f,    0.686380f,    0.687107f,  
  0.687834f,    0.688559f,    0.689284f,    0.690008f,    0.690732f,    0.691454f,    0.692176f,    0.692898f,    0.693618f,    0.694338f,  
  0.695058f,    0.695776f,    0.696494f,    0.697211f,    0.697928f,    0.698644f,    0.699359f,    0.700073f,    0.700787f,    0.701500f,  
  0.702212f,    0.702924f,    0.703635f,    0.704345f,    0.705055f,    0.705763f,    0.706472f,    0.707179f,    0.707886f,    0.708592f,  
  0.709297f,    0.710001f,    0.710705f,    0.711408f,    0.712111f,    0.712813f,    0.713514f,    0.714214f,    0.714913f,    0.715612f,  
  0.716310f,    0.717008f,    0.717704f,    0.718400f,    0.719096f,    0.719790f,    0.720484f,    0.721177f,    0.721870f,    0.722561f,  
  0.723252f,    0.723942f,    0.724632f,    0.725321f,    0.726009f,    0.726696f,    0.727383f,    0.728069f,    0.728754f,    0.729438f,  
  0.730122f,    0.730805f,    0.731487f,    0.732168f,    0.732849f,    0.733529f,    0.734209f,    0.734887f,    0.735565f,    0.736242f,  
  0.736918f,    0.737594f,    0.738269f,    0.738943f,    0.739616f,    0.740289f,    0.740961f,    0.741632f,    0.742303f,    0.742972f,  
  0.743641f,    0.744309f,    0.744977f,    0.745644f,    0.746310f,    0.746975f,    0.747639f,    0.748303f,    0.748966f,    0.749628f,  
  0.750290f,    0.750950f,    0.751610f,    0.752270f,    0.752928f,    0.753586f,    0.754243f,    0.754899f,    0.755555f,    0.756209f,  
  0.756863f,    0.757516f,    0.758169f,    0.758820f,    0.759471f,    0.760122f,    0.760771f,    0.761420f,    0.762067f,    0.762715f,  
  0.763361f,    0.764007f,    0.764651f,    0.765295f,    0.765939f,    0.766581f,    0.767223f,    0.767864f,    0.768504f,    0.769144f,  
  0.769782f,    0.770420f,    0.771057f,    0.771694f,    0.772329f,    0.772964f,    0.773598f,    0.774232f,    0.774864f,    0.775496f,  
  0.776127f,    0.776757f,    0.777386f,    0.778015f,    0.778643f,    0.779270f,    0.779896f,    0.780522f,    0.781147f,    0.781771f,  
  0.782394f,    0.783016f,    0.783638f,    0.784259f,    0.784879f,    0.785498f,    0.786116f,    0.786734f,    0.787351f,    0.787967f,  
  0.788582f,    0.789197f,    0.789811f,    0.790424f,    0.791036f,    0.791647f,    0.792258f,    0.792868f,    0.793477f,    0.794085f,  
  0.794692f,    0.795299f,    0.795905f,    0.796510f,    0.797114f,    0.797717f,    0.798320f,    0.798922f,    0.799523f,    0.800123f,  
  0.800722f,    0.801321f,    0.801919f,    0.802516f,    0.803112f,    0.803708f,    0.804302f,    0.804896f,    0.805489f,    0.806081f,  
  0.806673f,    0.807263f,    0.807853f,    0.808442f,    0.809030f,    0.809618f,    0.810204f,    0.810790f,    0.811375f,    0.811959f,  
  0.812542f,    0.813125f,    0.813706f,    0.814287f,    0.814867f,    0.815447f,    0.816025f,    0.816603f,    0.817179f,    0.817755f,  
  0.818330f,    0.818905f,    0.819478f,    0.820051f,    0.820623f,    0.821194f,    0.821764f,    0.822334f,    0.822902f,    0.823470f,  
  0.824037f,    0.824603f,    0.825168f,    0.825733f,    0.826296f,    0.826859f,    0.827421f,    0.827982f,    0.828543f,    0.829102f,  
  0.829661f,    0.830219f,    0.830776f,    0.831332f,    0.831887f,    0.832442f,    0.832996f,    0.833549f,    0.834101f,    0.834652f,  
  0.835202f,    0.835752f,    0.836300f,    0.836848f,    0.837395f,    0.837941f,    0.838487f,    0.839031f,    0.839575f,    0.840118f,  
  0.840660f,    0.841201f,    0.841741f,    0.842281f,    0.842819f,    0.843357f,    0.843894f,    0.844430f,    0.844965f,    0.845500f,  
  0.846033f,    0.846566f,    0.847098f,    0.847629f,    0.848159f,    0.848688f,    0.849217f,    0.849744f,    0.850271f,    0.850797f,  
  0.851322f,    0.851846f,    0.852370f,    0.852892f,    0.853414f,    0.853935f,    0.854455f,    0.854974f,    0.855492f,    0.856009f,  
  0.856526f,    0.857042f,    0.857556f,    0.858070f,    0.858583f,    0.859096f,    0.859607f,    0.860118f,    0.860627f,    0.861136f,  
  0.861644f,    0.862151f,    0.862657f,    0.863163f,    0.863667f,    0.864171f,    0.864674f,    0.865175f,    0.865677f,    0.866177f,  
  0.866676f,    0.867174f,    0.867672f,    0.868169f,    0.868665f,    0.869160f,    0.869654f,    0.870147f,    0.870639f,    0.871131f,  
  0.871621f,    0.872111f,    0.872600f,    0.873088f,    0.873575f,    0.874061f,    0.874547f,    0.875031f,    0.875515f,    0.875998f,  
  0.876479f,    0.876960f,    0.877441f,    0.877920f,    0.878398f,    0.878876f,    0.879352f,    0.879828f,    0.880303f,    0.880777f,  
  0.881250f,    0.881722f,    0.882193f,    0.882664f,    0.883133f,    0.883602f,    0.884070f,    0.884537f,    0.885003f,    0.885468f,  
  0.885932f,    0.886396f,    0.886858f,    0.887320f,    0.887780f,    0.888240f,    0.888699f,    0.889157f,    0.889614f,    0.890071f,  
  0.890526f,    0.890981f,    0.891434f,    0.891887f,    0.892339f,    0.892790f,    0.893240f,    0.893689f,    0.894137f,    0.894584f,  
  0.895031f,    0.895476f,    0.895921f,    0.896365f,    0.896808f,    0.897250f,    0.897691f,    0.898131f,    0.898570f,    0.899009f,  
  0.899446f,    0.899883f,    0.900318f,    0.900753f,    0.901187f,    0.901620f,    0.902052f,    0.902483f,    0.902913f,    0.903343f,  
  0.903771f,    0.904199f,    0.904625f,    0.905051f,    0.905476f,    0.905900f,    0.906323f,    0.906745f,    0.907166f,    0.907587f,  
  0.908006f,    0.908425f,    0.908842f,    0.909259f,    0.909675f,    0.910090f,    0.910504f,    0.910917f,    0.911329f,    0.911740f,  
  0.912150f,    0.912560f,    0.912968f,    0.913376f,    0.913782f,    0.914188f,    0.914593f,    0.914997f,    0.915400f,    0.915802f,  
  0.916203f,    0.916603f,    0.917003f,    0.917401f,    0.917799f,    0.918195f,    0.918591f,    0.918986f,    0.919380f,    0.919772f,  
  0.920164f,    0.920555f,    0.920946f,    0.921335f,    0.921723f,    0.922111f,    0.922497f,    0.922883f,    0.923267f,    0.923651f,  
  0.924034f,    0.924416f,    0.924796f,    0.925176f,    0.925556f,    0.925934f,    0.926311f,    0.926687f,    0.927063f,    0.927437f,  
  0.927811f,    0.928183f,    0.928555f,    0.928925f,    0.929295f,    0.929664f,    0.930032f,    0.930399f,    0.930765f,    0.931130f,  
  0.931495f,    0.931858f,    0.932220f,    0.932582f,    0.932942f,    0.933302f,    0.933660f,    0.934018f,    0.934375f,    0.934731f,  
  0.935085f,    0.935439f,    0.935792f,    0.936145f,    0.936496f,    0.936846f,    0.937195f,    0.937544f,    0.937891f,    0.938237f,  
  0.938583f,    0.938927f,    0.939271f,    0.939614f,    0.939956f,    0.940296f,    0.940636f,    0.940975f,    0.941313f,    0.941650f,  
  0.941986f,    0.942322f,    0.942656f,    0.942989f,    0.943322f,    0.943653f,    0.943983f,    0.944313f,    0.944641f,    0.944969f,  
  0.945296f,    0.945622f,    0.945946f,    0.946270f,    0.946593f,    0.946915f,    0.947236f,    0.947556f,    0.947875f,    0.948193f,  
  0.948511f,    0.948827f,    0.949142f,    0.949457f,    0.949770f,    0.950082f,    0.950394f,    0.950705f,    0.951014f,    0.951323f,  
  0.951631f,    0.951937f,    0.952243f,    0.952548f,    0.952852f,    0.953155f,    0.953457f,    0.953758f,    0.954058f,    0.954357f,  
  0.954655f,    0.954953f,    0.955249f,    0.955544f,    0.955839f,    0.956132f,    0.956425f,    0.956716f,    0.957007f,    0.957296f,  
  0.957585f,    0.957872f,    0.958159f,    0.958445f,    0.958730f,    0.959014f,    0.959296f,    0.959578f,    0.959859f,    0.960139f,  
  0.960418f,    0.960696f,    0.960974f,    0.961250f,    0.961525f,    0.961799f,    0.962072f,    0.962345f,    0.962616f,    0.962886f,  
  0.963156f,    0.963424f,    0.963692f,    0.963958f,    0.964224f,    0.964489f,    0.964752f,    0.965015f,    0.965277f,    0.965537f,  
  0.965797f,    0.966056f,    0.966314f,    0.966571f,    0.966827f,    0.967082f,    0.967336f,    0.967589f,    0.967841f,    0.968092f,  
  0.968342f,    0.968591f,    0.968839f,    0.969086f,    0.969333f,    0.969578f,    0.969822f,    0.970065f,    0.970308f,    0.970549f,  
  0.970790f,    0.971029f,    0.971268f,    0.971505f,    0.971742f,    0.971977f,    0.972212f,    0.972445f,    0.972678f,    0.972910f,  
  0.973140f,    0.973370f,    0.973599f,    0.973827f,    0.974053f,    0.974279f,    0.974504f,    0.974728f,    0.974951f,    0.975173f,  
  0.975394f,    0.975614f,    0.975833f,    0.976051f,    0.976268f,    0.976484f,    0.976699f,    0.976913f,    0.977126f,    0.977338f,  
  0.977550f,    0.977760f,    0.977969f,    0.978177f,    0.978385f,    0.978591f,    0.978796f,    0.979001f,    0.979204f,    0.979406f,  
  0.979608f,    0.979808f,    0.980008f,    0.980206f,    0.980404f,    0.980600f,    0.980796f,    0.980990f,    0.981184f,    0.981376f,  
  0.981568f,    0.981759f,    0.981948f,    0.982137f,    0.982325f,    0.982511f,    0.982697f,    0.982882f,    0.983065f,    0.983248f,  
  0.983430f,    0.983611f,    0.983791f,    0.983969f,    0.984147f,    0.984324f,    0.984500f,    0.984675f,    0.984849f,    0.985022f,  
  0.985194f,    0.985365f,    0.985535f,    0.985704f,    0.985872f,    0.986039f,    0.986205f,    0.986370f,    0.986534f,    0.986697f,  
  0.986859f,    0.987020f,    0.987180f,    0.987339f,    0.987497f,    0.987654f,    0.987811f,    0.987966f,    0.988120f,    0.988273f,  
  0.988425f,    0.988577f,    0.988727f,    0.988876f,    0.989024f,    0.989172f,    0.989318f,    0.989463f,    0.989607f,    0.989751f,  
  0.989893f,    0.990034f,    0.990175f,    0.990314f,    0.990452f,    0.990590f,    0.990726f,    0.990861f,    0.990996f,    0.991129f,  
  0.991262f,    0.991393f,    0.991523f,    0.991653f,    0.991781f,    0.991909f,    0.992035f,    0.992161f,    0.992285f,    0.992409f,  
  0.992531f,    0.992653f,    0.992773f,    0.992893f,    0.993011f,    0.993129f,    0.993245f,    0.993361f,    0.993475f,    0.993589f,  
  0.993701f,    0.993813f,    0.993924f,    0.994033f,    0.994142f,    0.994249f,    0.994356f,    0.994461f,    0.994566f,    0.994670f,  
  0.994772f,    0.994874f,    0.994975f,    0.995074f,    0.995173f,    0.995270f,    0.995367f,    0.995463f,    0.995557f,    0.995651f,  
  0.995744f,    0.995835f,    0.995926f,    0.996016f,    0.996104f,    0.996192f,    0.996279f,    0.996364f,    0.996449f,    0.996533f,  
  0.996616f,    0.996697f,    0.996778f,    0.996858f,    0.996936f,    0.997014f,    0.997091f,    0.997167f,    0.997241f,    0.997315f,  
  0.997388f,    0.997460f,    0.997530f,    0.997600f,    0.997669f,    0.997736f,    0.997803f,    0.997869f,    0.997934f,    0.997997f,  
  0.998060f,    0.998122f,    0.998183f,    0.998243f,    0.998301f,    0.998359f,    0.998416f,    0.998472f,    0.998526f,    0.998580f,  
  0.998633f,    0.998685f,    0.998735f,    0.998785f,    0.998834f,    0.998882f,    0.998929f,    0.998974f,    0.999019f,    0.999063f,  
  0.999106f,    0.999147f,    0.999188f,    0.999228f,    0.999267f,    0.999305f,    0.999341f,    0.999377f,    0.999412f,    0.999446f,  
  0.999479f,    0.999510f,    0.999541f,    0.999571f,    0.999600f,    0.999627f,    0.999654f,    0.999680f,    0.999705f,    0.999729f,  
  0.999751f,    0.999773f,    0.999794f,    0.999814f,    0.999833f,    0.999850f,    0.999867f,    0.999883f,    0.999898f,    0.999912f,  
  0.999924f,    0.999936f,    0.999947f,    0.999957f,    0.999966f,    0.999973f,    0.999980f,    0.999986f,    0.999991f,    0.999995f,  
  0.999997f,    0.999999f,    1.000000f,    1.000000f,    0.999999f,    0.999996f,    0.999993f,    0.999989f,    0.999984f,    0.999978f,  
  0.999970f,    0.999962f,    0.999953f,    0.999943f,    0.999932f,    0.999919f,    0.999906f,    0.999892f,    0.999877f,    0.999860f,  
  0.999843f,    0.999825f,    0.999806f,    0.999786f,    0.999764f,    0.999742f,    0.999719f,    0.999695f,    0.999670f,    0.999643f,  
  0.999616f,    0.999588f,    0.999559f,    0.999529f,    0.999497f,    0.999465f,    0.999432f,    0.999398f,    0.999363f,    0.999326f,  
  0.999289f,    0.999251f,    0.999212f,    0.999172f,    0.999131f,    0.999088f,    0.999045f,    0.999001f,    0.998956f,    0.998910f,  
  0.998862f,    0.998814f,    0.998765f,    0.998715f,    0.998664f,    0.998611f,    0.998558f,    0.998504f,    0.998449f,    0.998393f,  
  0.998336f,    0.998277f,    0.998218f,    0.998158f,    0.998097f,    0.998035f,    0.997972f,    0.997907f,    0.997842f,    0.997776f,  
  0.997709f,    0.997641f,    0.997572f,    0.997502f,    0.997430f,    0.997358f,    0.997285f,    0.997211f,    0.997136f,    0.997060f,  
  0.996983f,    0.996904f,    0.996825f,    0.996745f,    0.996664f,    0.996582f,    0.996499f,    0.996415f,    0.996330f,    0.996244f,  
  0.996156f,    0.996068f,    0.995979f,    0.995889f,    0.995798f,    0.995706f,    0.995613f,    0.995519f,    0.995424f,    0.995328f,  
  0.995231f,    0.995133f,    0.995034f,    0.994934f,    0.994833f,    0.994731f,    0.994628f,    0.994524f,    0.994419f,    0.994313f,  
  0.994206f,    0.994098f,    0.993989f,    0.993879f,    0.993768f,    0.993656f,    0.993543f,    0.993429f,    0.993314f,    0.993198f,  
  0.993081f,    0.992963f,    0.992844f,    0.992724f,    0.992603f,    0.992481f,    0.992358f,    0.992235f,    0.992110f,    0.991984f,  
  0.991857f,    0.991729f,    0.991600f,    0.991470f,    0.991340f,    0.991208f,    0.991075f,    0.990941f,    0.990806f,    0.990671f,  
  0.990534f,    0.990396f,    0.990257f,    0.990118f,    0.989977f,    0.989835f,    0.989692f,    0.989549f,    0.989404f,    0.989258f,  
  0.989112f,    0.988964f,    0.988815f,    0.988666f,    0.988515f,    0.988363f,    0.988211f,    0.988057f,    0.987903f,    0.987747f,  
  0.987590f,    0.987433f,    0.987274f,    0.987115f,    0.986954f,    0.986793f,    0.986630f,    0.986467f,    0.986302f,    0.986137f,  
  0.985971f,    0.985803f,    0.985635f,    0.985465f,    0.985295f,    0.985124f,    0.984951f,    0.984778f,    0.984604f,    0.984428f,  
  0.984252f,    0.984075f,    0.983897f,    0.983717f,    0.983537f,    0.983356f,    0.983174f,    0.982991f,    0.982807f,    0.982621f,  
  0.982435f,    0.982248f,    0.982060f,    0.981871f,    0.981681f,    0.981490f,    0.981298f,    0.981105f,    0.980911f,    0.980716f,  
  0.980520f,    0.980323f,    0.980125f,    0.979926f,    0.979727f,    0.979526f,    0.979324f,    0.979121f,    0.978917f,    0.978713f,  
  0.978507f,    0.978300f,    0.978093f,    0.977884f,    0.977674f,    0.977464f,    0.977252f,    0.977040f,    0.976826f,    0.976611f,  
  0.976396f,    0.976179f,    0.975962f,    0.975744f,    0.975524f,    0.975304f,    0.975082f,    0.974860f,    0.974637f,    0.974413f,  
  0.974187f,    0.973961f,    0.973734f,    0.973506f,    0.973277f,    0.973046f,    0.972815f,    0.972583f,    0.972350f,    0.972116f,  
  0.971881f,    0.971645f,    0.971408f,    0.971170f,    0.970932f,    0.970692f,    0.970451f,    0.970209f,    0.969966f,    0.969723f,  
  0.969478f,    0.969232f,    0.968986f,    0.968738f,    0.968489f,    0.968240f,    0.967989f,    0.967738f,    0.967485f,    0.967232f,  
  0.966978f,    0.966722f,    0.966466f,    0.966209f,    0.965951f,    0.965691f,    0.965431f,    0.965170f,    0.964908f,    0.964645f,  
  0.964381f,    0.964116f,    0.963850f,    0.963583f,    0.963315f,    0.963046f,    0.962776f,    0.962506f,    0.962234f,    0.961961f,  
  0.961687f,    0.961413f,    0.961137f,    0.960861f,    0.960583f,    0.960305f,    0.960025f,    0.959745f,    0.959464f,    0.959181f,  
  0.958898f,    0.958614f,    0.958328f,    0.958042f,    0.957755f,    0.957467f,    0.957178f,    0.956888f,    0.956597f,    0.956305f,  
  0.956013f,    0.955719f,    0.955424f,    0.955128f,    0.954832f,    0.954534f,    0.954235f,    0.953936f,    0.953635f,    0.953334f,  
  0.953031f,    0.952728f,    0.952424f,    0.952119f,    0.951812f,    0.951505f,    0.951197f,    0.950888f,    0.950578f,    0.950267f,  
  0.949955f,    0.949642f,    0.949329f,    0.949014f,    0.948698f,    0.948381f,    0.948064f,    0.947745f,    0.947426f,    0.947105f,  
  0.946784f,    0.946462f,    0.946138f,    0.945814f,    0.945489f,    0.945163f,    0.944836f,    0.944508f,    0.944179f,    0.943849f,  
  0.943518f,    0.943186f,    0.942853f,    0.942520f,    0.942185f,    0.941849f,    0.941513f,    0.941176f,    0.940837f,    0.940498f,  
  0.940158f,    0.939816f,    0.939474f,    0.939131f,    0.938787f,    0.938442f,    0.938096f,    0.937749f,    0.937402f,    0.937053f,  
  0.936703f,    0.936353f,    0.936001f,    0.935649f,    0.935295f,    0.934941f,    0.934586f,    0.934229f,    0.933872f,    0.933514f,  
  0.933155f,    0.932795f,    0.932434f,    0.932073f,    0.931710f,    0.931346f,    0.930982f,    0.930616f,    0.930250f,    0.929882f,  
  0.929514f,    0.929145f,    0.928774f,    0.928403f,    0.928031f,    0.927658f,    0.927284f,    0.926910f,    0.926534f,    0.926157f,  
  0.925780f,    0.925401f,    0.925022f,    0.924641f,    0.924260f,    0.923878f,    0.923495f,    0.923110f,    0.922725f,    0.922340f,  
  0.921953f,    0.921565f,    0.921176f,    0.920787f,    0.920396f,    0.920005f,    0.919612f,    0.919219f,    0.918825f,    0.918430f,  
  0.918034f,    0.917637f,    0.917239f,    0.916840f,    0.916440f,    0.916040f,    0.915638f,    0.915236f,    0.914832f,    0.914428f,  
  0.914023f,    0.913617f,    0.913210f,    0.912802f,    0.912393f,    0.911983f,    0.911572f,    0.911161f,    0.910748f,    0.910335f,  
  0.909921f,    0.909505f,    0.909089f,    0.908672f,    0.908254f,    0.907835f,    0.907415f,    0.906995f,    0.906573f,    0.906151f,  
  0.905727f,    0.905303f,    0.904878f,    0.904452f,    0.904025f,    0.903597f,    0.903168f,    0.902738f,    0.902307f,    0.901876f,  
  0.901443f,    0.901010f,    0.900576f,    0.900141f,    0.899705f,    0.899268f,    0.898830f,    0.898391f,    0.897951f,    0.897511f,  
  0.897069f,    0.896627f,    0.896184f,    0.895740f,    0.895295f,    0.894849f,    0.894402f,    0.893954f,    0.893506f,    0.893056f,  
  0.892606f,    0.892155f,    0.891702f,    0.891249f,    0.890795f,    0.890340f,    0.889885f,    0.889428f,    0.888971f,    0.888512f,  
  0.888053f,    0.887593f,    0.887132f,    0.886670f,    0.886207f,    0.885743f,    0.885278f,    0.884813f,    0.884347f,    0.883879f,  
  0.883411f,    0.882942f,    0.882472f,    0.882001f,    0.881530f,    0.881057f,    0.880584f,    0.880109f,    0.879634f,    0.879158f,  
  0.878681f,    0.878203f,    0.877724f,    0.877245f,    0.876764f,    0.876283f,    0.875801f,    0.875318f,    0.874834f,    0.874349f,  
  0.873863f,    0.873376f,    0.872889f,    0.872401f,    0.871911f,    0.871421f,    0.870930f,    0.870439f,    0.869946f,    0.869452f,  
  0.868958f,    0.868462f,    0.867966f,    0.867469f,    0.866971f,    0.866472f,    0.865973f,    0.865472f,    0.864971f,    0.864469f,  
  0.863966f,    0.863462f,    0.862957f,    0.862451f,    0.861944f,    0.861437f,    0.860929f,    0.860420f,    0.859910f,    0.859399f,  
  0.858887f,    0.858374f,    0.857861f,    0.857347f,    0.856831f,    0.856315f,    0.855798f,    0.855281f,    0.854762f,    0.854243f,  
  0.853722f,    0.853201f,    0.852679f,    0.852156f,    0.851633f,    0.851108f,    0.850583f,    0.850056f,    0.849529f,    0.849001f,  
  0.848473f,    0.847943f,    0.847412f,    0.846881f,    0.846349f,    0.845816f,    0.845282f,    0.844747f,    0.844211f,    0.843675f,  
  0.843138f,    0.842600f,    0.842061f,    0.841521f,    0.840980f,    0.840439f,    0.839896f,    0.839353f,    0.838809f,    0.838264f,  
  0.837719f,    0.837172f,    0.836625f,    0.836077f,    0.835528f,    0.834978f,    0.834427f,    0.833876f,    0.833323f,    0.832770f,  
  0.832216f,    0.831661f,    0.831105f,    0.830549f,    0.829991f,    0.829433f,    0.828874f,    0.828314f,    0.827754f,    0.827192f,  
  0.826630f,    0.826067f,    0.825503f,    0.824938f,    0.824372f,    0.823806f,    0.823239f,    0.822670f,    0.822102f,    0.821532f,  
  0.820961f,    0.820390f,    0.819818f,    0.819245f,    0.818671f,    0.818096f,    0.817521f,    0.816944f,    0.816367f,    0.815789f,  
  0.815210f,    0.814631f,    0.814050f,    0.813469f,    0.812887f,    0.812304f,    0.811721f,    0.811136f,    0.810551f,    0.809965f,  
  0.809378f,    0.808790f,    0.808202f,    0.807613f,    0.807022f,    0.806432f,    0.805840f,    0.805247f,    0.804654f,    0.804060f,  
  0.803465f,    0.802869f,    0.802273f,    0.801675f,    0.801077f,    0.800478f,    0.799878f,    0.799278f,    0.798676f,    0.798074f,  
  0.797471f,    0.796867f,    0.796263f,    0.795658f,    0.795051f,    0.794445f,    0.793837f,    0.793228f,    0.792619f,    0.792009f,  
  0.791398f,    0.790786f,    0.790174f,    0.789560f,    0.788946f,    0.788332f,    0.787716f,    0.787099f,    0.786482f,    0.785864f,  
  0.785245f,    0.784626f,    0.784005f,    0.783384f,    0.782762f,    0.782140f,    0.781516f,    0.780892f,    0.780267f,    0.779641f,  
  0.779014f,    0.778387f,    0.777759f,    0.777130f,    0.776500f,    0.775870f,    0.775238f,    0.774606f,    0.773973f,    0.773340f,  
  0.772706f,    0.772070f,    0.771434f,    0.770798f,    0.770160f,    0.769522f,    0.768883f,    0.768243f,    0.767603f,    0.766961f,  
  0.766319f,    0.765676f,    0.765033f,    0.764389f,    0.763743f,    0.763097f,    0.762451f,    0.761803f,    0.761155f,    0.760506f,  
  0.759857f,    0.759206f,    0.758555f,    0.757903f,    0.757250f,    0.756597f,    0.755942f,    0.755287f,    0.754632f,    0.753975f,  
  0.753318f,    0.752660f,    0.752001f,    0.751341f,    0.750681f,    0.750020f,    0.749358f,    0.748696f,    0.748032f,    0.747368f,  
  0.746704f,    0.746038f,    0.745372f,    0.744705f,    0.744037f,    0.743369f,    0.742699f,    0.742029f,    0.741359f,    0.740687f,  
  0.740015f,    0.739342f,    0.738668f,    0.737994f,    0.737319f,    0.736643f,    0.735966f,    0.735289f,    0.734610f,    0.733932f,  
  0.733252f,    0.732572f,    0.731891f,    0.731209f,    0.730526f,    0.729843f,    0.729159f,    0.728474f,    0.727789f,    0.727103f,  
  0.726416f,    0.725728f,    0.725040f,    0.724351f,    0.723661f,    0.722971f,    0.722279f,    0.721587f,    0.720895f,    0.720201f,  
  0.719507f,    0.718812f,    0.718117f,    0.717420f,    0.716723f,    0.716026f,    0.715327f,    0.714628f,    0.713928f,    0.713228f,  
  0.712526f,    0.711824f,    0.711122f,    0.710418f,    0.709714f,    0.709009f,    0.708304f,    0.707598f,    0.706891f,    0.706183f,  
  0.705474f,    0.704765f,    0.704056f,    0.703345f,    0.702634f,    0.701922f,    0.701209f,    0.700496f,    0.699782f,    0.699067f,  
  0.698352f,    0.697636f,    0.696919f,    0.696202f,    0.695483f,    0.694764f,    0.694045f,    0.693325f,    0.692604f,    0.691882f,  
  0.691160f,    0.690437f,    0.689713f,    0.688988f,    0.688263f,    0.687537f,    0.686811f,    0.686084f,    0.685356f,    0.684627f,  
  0.683898f,    0.683168f,    0.682438f,    0.681706f,    0.680974f,    0.680242f,    0.679508f,    0.678774f,    0.678040f,    0.677304f,  
  0.676568f,    0.675832f,    0.675094f,    0.674356f,    0.673617f,    0.672878f,    0.672138f,    0.671397f,    0.670656f,    0.669914f,  
  0.669171f,    0.668427f,    0.667683f,    0.666938f,    0.666193f,    0.665447f,    0.664700f,    0.663953f,    0.663205f,    0.662456f,  
  0.661706f,    0.660956f,    0.660206f,    0.659454f,    0.658702f,    0.657949f,    0.657196f,    0.656442f,    0.655687f,    0.654932f,  
  0.654176f,    0.653419f,    0.652662f,    0.651904f,    0.651145f,    0.650386f,    0.649626f,    0.648865f,    0.648104f,    0.647342f,  
  0.646580f,    0.645817f,    0.645053f,    0.644288f,    0.643523f,    0.642757f,    0.641991f,    0.641224f,    0.640456f,    0.639688f,  
  0.638919f,    0.638150f,    0.637379f,    0.636608f,    0.635837f,    0.635065f,    0.634292f,    0.633519f,    0.632745f,    0.631970f,  
  0.631195f,    0.630419f,    0.629642f,    0.628865f,    0.628087f,    0.627309f,    0.626529f,    0.625750f,    0.624969f,    0.624188f,  
  0.623407f,    0.622625f,    0.621842f,    0.621058f,    0.620274f,    0.619490f,    0.618704f,    0.617918f,    0.617132f,    0.616345f,  
  0.615557f,    0.614768f,    0.613979f,    0.613190f,    0.612400f,    0.611609f,    0.610817f,    0.610025f,    0.609233f,    0.608439f,  
  0.607645f,    0.606851f,    0.606056f,    0.605260f,    0.604464f,    0.603667f,    0.602869f,    0.602071f,    0.601272f,    0.600473f,  
  0.599673f,    0.598872f,    0.598071f,    0.597270f,    0.596467f,    0.595664f,    0.594861f,    0.594057f,    0.593252f,    0.592447f,  
  0.591641f,    0.590834f,    0.590027f,    0.589219f,    0.588411f,    0.587602f,    0.586793f,    0.585983f,    0.585172f,    0.584361f,  
  0.583549f,    0.582737f,    0.581924f,    0.581110f,    0.580296f,    0.579482f,    0.578666f,    0.577850f,    0.577034f,    0.576217f,  
  0.575399f,    0.574581f,    0.573762f,    0.572943f,    0.572123f,    0.571303f,    0.570482f,    0.569660f,    0.568838f,    0.568015f,  
  0.567192f,    0.566368f,    0.565544f,    0.564719f,    0.563893f,    0.563067f,    0.562240f,    0.561413f,    0.560585f,    0.559757f,  
  0.558928f,    0.558098f,    0.557268f,    0.556438f,    0.555607f,    0.554775f,    0.553943f,    0.553110f,    0.552276f,    0.551442f,  
  0.550608f,    0.549773f,    0.548937f,    0.548101f,    0.547265f,    0.546427f,    0.545590f,    0.544751f,    0.543912f,    0.543073f,  
  0.542233f,    0.541392f,    0.540551f,    0.539710f,    0.538868f,    0.538025f,    0.537182f,    0.536338f,    0.535494f,    0.534649f,  
  0.533804f,    0.532958f,    0.532111f,    0.531264f,    0.530417f,    0.529569f,    0.528720f,    0.527871f,    0.527022f,    0.526172f,  
  0.525321f,    0.524470f,    0.523618f,    0.522766f,    0.521913f,    0.521060f,    0.520206f,    0.519352f,    0.518497f,    0.517642f,  
  0.516786f,    0.515930f,    0.515073f,    0.514215f,    0.513357f,    0.512499f,    0.511640f,    0.510780f,    0.509921f,    0.509060f,  
  0.508199f,    0.507338f,    0.506476f,    0.505613f,    0.504750f,    0.503887f,    0.503022f,    0.502158f,    0.501293f,    0.500427f,  
  0.499561f,    0.498695f,    0.497828f,    0.496960f,    0.496092f,    0.495224f,    0.494355f,    0.493485f,    0.492615f,    0.491745f,  
  0.490874f,    0.490002f,    0.489130f,    0.488258f,    0.487385f,    0.486511f,    0.485638f,    0.484763f,    0.483888f,    0.483013f,  
  0.482137f,    0.481261f,    0.480384f,    0.479507f,    0.478629f,    0.477751f,    0.476872f,    0.475993f,    0.475113f,    0.474233f,  
  0.473352f,    0.472471f,    0.471589f,    0.470707f,    0.469825f,    0.468942f,    0.468058f,    0.467174f,    0.466290f,    0.465405f,  
  0.464520f,    0.463634f,    0.462748f,    0.461861f,    0.460974f,    0.460086f,    0.459198f,    0.458310f,    0.457421f,    0.456531f,  
  0.455641f,    0.454751f,    0.453860f,    0.452969f,    0.452077f,    0.451185f,    0.450292f,    0.449399f,    0.448505f,    0.447611f,  
  0.446717f,    0.445822f,    0.444927f,    0.444031f,    0.443135f,    0.442238f,    0.441341f,    0.440443f,    0.439545f,    0.438647f,  
  0.437748f,    0.436849f,    0.435949f,    0.435049f,    0.434148f,    0.433247f,    0.432346f,    0.431444f,    0.430541f,    0.429638f,  
  0.428735f,    0.427832f,    0.426928f,    0.426023f,    0.425118f,    0.424213f,    0.423307f,    0.422401f,    0.421494f,    0.420587f,  
  0.419680f,    0.418772f,    0.417863f,    0.416955f,    0.416046f,    0.415136f,    0.414226f,    0.413316f,    0.412405f,    0.411494f,  
  0.410582f,    0.409670f,    0.408758f,    0.407845f,    0.406932f,    0.406018f,    0.405104f,    0.404189f,    0.403274f,    0.402359f,  
  0.401443f,    0.400527f,    0.399611f,    0.398694f,    0.397777f,    0.396859f,    0.395941f,    0.395023f,    0.394104f,    0.393184f,  
  0.392265f,    0.391345f,    0.390424f,    0.389503f,    0.388582f,    0.387661f,    0.386739f,    0.385816f,    0.384893f,    0.383970f,  
  0.383047f,    0.382123f,    0.381199f,    0.380274f,    0.379349f,    0.378423f,    0.377498f,    0.376571f,    0.375645f,    0.374718f,  
  0.373790f,    0.372863f,    0.371935f,    0.371006f,    0.370077f,    0.369148f,    0.368219f,    0.367289f,    0.366358f,    0.365428f,  
  0.364497f,    0.363565f,    0.362634f,    0.361702f,    0.360769f,    0.359836f,    0.358903f,    0.357969f,    0.357036f,    0.356101f,  
  0.355167f,    0.354232f,    0.353296f,    0.352361f,    0.351425f,    0.350488f,    0.349552f,    0.348614f,    0.347677f,    0.346739f,  
  0.345801f,    0.344863f,    0.343924f,    0.342985f,    0.342045f,    0.341105f,    0.340165f,    0.339224f,    0.338284f,    0.337342f,  
  0.336401f,    0.335459f,    0.334517f,    0.333574f,    0.332631f,    0.331688f,    0.330745f,    0.329801f,    0.328856f,    0.327912f,  
  0.326967f,    0.326022f,    0.325076f,    0.324130f,    0.323184f,    0.322238f,    0.321291f,    0.320344f,    0.319396f,    0.318449f,  
  0.317500f,    0.316552f,    0.315603f,    0.314654f,    0.313705f,    0.312755f,    0.311805f,    0.310855f,    0.309904f,    0.308953f,  
  0.308002f,    0.307051f,    0.306099f,    0.305147f,    0.304194f,    0.303241f,    0.302288f,    0.301335f,    0.300381f,    0.299427f,  
  0.298473f,    0.297518f,    0.296564f,    0.295608f,    0.294653f,    0.293697f,    0.292741f,    0.291785f,    0.290828f,    0.289871f,  
  0.288914f,    0.287957f,    0.286999f,    0.286041f,    0.285082f,    0.284124f,    0.283165f,    0.282206f,    0.281246f,    0.280286f,  
  0.279326f,    0.278366f,    0.277405f,    0.276444f,    0.275483f,    0.274522f,    0.273560f,    0.272598f,    0.271636f,    0.270673f,  
  0.269710f,    0.268747f,    0.267784f,    0.266820f,    0.265857f,    0.264892f,    0.263928f,    0.262963f,    0.261998f,    0.261033f,  
  0.260068f,    0.259102f,    0.258136f,    0.257170f,    0.256203f,    0.255237f,    0.254270f,    0.253302f,    0.252335f,    0.251367f,  
  0.250399f,    0.249431f,    0.248462f,    0.247493f,    0.246524f,    0.245555f,    0.244586f,    0.243616f,    0.242646f,    0.241676f,  
  0.240705f,    0.239734f,    0.238764f,    0.237792f,    0.236821f,    0.235849f,    0.234877f,    0.233905f,    0.232933f,    0.231960f,  
  0.230987f,    0.230014f,    0.229041f,    0.228067f,    0.227094f,    0.226120f,    0.225145f,    0.224171f,    0.223196f,    0.222222f,  
  0.221246f,    0.220271f,    0.219296f,    0.218320f,    0.217344f,    0.216368f,    0.215391f,    0.214415f,    0.213438f,    0.212461f,  
  0.211483f,    0.210506f,    0.209528f,    0.208550f,    0.207572f,    0.206594f,    0.205615f,    0.204637f,    0.203658f,    0.202678f,  
  0.201699f,    0.200720f,    0.199740f,    0.198760f,    0.197780f,    0.196799f,    0.195819f,    0.194838f,    0.193857f,    0.192876f,  
  0.191895f,    0.190913f,    0.189931f,    0.188950f,    0.187968f,    0.186985f,    0.186003f,    0.185020f,    0.184037f,    0.183054f,  
  0.182071f,    0.181088f,    0.180104f,    0.179120f,    0.178137f,    0.177152f,    0.176168f,    0.175184f,    0.174199f,    0.173214f,  
  0.172229f,    0.171244f,    0.170259f,    0.169273f,    0.168288f,    0.167302f,    0.166316f,    0.165330f,    0.164343f,    0.163357f,  
  0.162370f,    0.161383f,    0.160397f,    0.159409f,    0.158422f,    0.157435f,    0.156447f,    0.155459f,    0.154471f,    0.153483f,  
  0.152495f,    0.151507f,    0.150518f,    0.149529f,    0.148541f,    0.147552f,    0.146563f,    0.145573f,    0.144584f,    0.143594f,  
  0.142605f,    0.141615f,    0.140625f,    0.139635f,    0.138644f,    0.137654f,    0.136663f,    0.135673f,    0.134682f,    0.133691f,  
  0.132700f,    0.131709f,    0.130717f,    0.129726f,    0.128734f,    0.127742f,    0.126750f,    0.125758f,    0.124766f,    0.123774f,  
  0.122782f,    0.121789f,    0.120797f,    0.119804f,    0.118811f,    0.117818f,    0.116825f,    0.115832f,    0.114838f,    0.113845f,  
  0.112851f,    0.111858f,    0.110864f,    0.109870f,    0.108876f,    0.107882f,    0.106888f,    0.105893f,    0.104899f,    0.103904f,  
  0.102910f,    0.101915f,    0.100920f,    0.099925f,    0.098930f,    0.097935f,    0.096940f,    0.095945f,    0.094949f,    0.093954f,  
  0.092958f,    0.091962f,    0.090966f,    0.089971f,    0.088975f,    0.087978f,    0.086982f,    0.085986f,    0.084990f,    0.083993f,  
  0.082997f,    0.082000f,    0.081004f,    0.080007f,    0.079010f,    0.078013f,    0.077016f,    0.076019f,    0.075022f,    0.074025f,  
  0.073027f,    0.072030f,    0.071032f,    0.070035f,    0.069037f,    0.068040f,    0.067042f,    0.066044f,    0.065046f,    0.064048f,  
  0.063051f,    0.062052f,    0.061054f,    0.060056f,    0.059058f,    0.058060f,    0.057061f,    0.056063f,    0.055064f,    0.054066f,  
  0.053067f,    0.052069f,    0.051070f,    0.050071f,    0.049073f,    0.048074f,    0.047075f,    0.046076f,    0.045077f,    0.044078f,  
  0.043079f,    0.042080f,    0.041081f,    0.040082f,    0.039082f,    0.038083f,    0.037084f,    0.036085f,    0.035085f,    0.034086f,  
  0.033086f,    0.032087f,    0.031087f,    0.030088f,    0.029088f,    0.028089f,    0.027089f,    0.026089f,    0.025090f,    0.024090f,  
  0.023090f,    0.022091f,    0.021091f,    0.020091f,    0.019091f,    0.018091f,    0.017092f,    0.016092f,    0.015092f,    0.014092f,  
  0.013092f,    0.012092f,    0.011092f,    0.010092f,    0.009092f,    0.008092f,    0.007092f,    0.006092f,    0.005092f,    0.004092f,  
  0.003092f,    0.002092f,    0.001092f,    0.000093f,
};


float zSinApprox (const float a) 
{
	const int	lookup		= zFloat2Int(1000.0f * a);
	const float	sinValue	= SinTable[(lookup+3142 + 6284*1000) % 6284];

// FIXME: Verantwortlich fuer Unstetigkeiten??
	// im ungenauen Bereich der Tabelle wird die genaue Library Funktion verwendet
//	if ((sinValue < 0.05) && (sinValue > -0.05))	return sin(a);
//	else											return sinValue;

	return sinValue;
}

float zCosApprox (const float a) 
{
	const int	lookup		= zFloat2Int(1000.0f * a);
	const float	cosValue	= SinTable[(lookup+3142 +3142/2 + 6284*1000) % 6284];

// FIXME: Verantwortlich fuer Unstetigkeiten??
	// im ungenauen Bereich der Tabelle wird die genaue Library Funktion verwendet
//	if ((cosValue < 0.05) && (cosValue > -0.05))	return cos(a);
//	else											return cosValue;

	return cosValue;
}

/*
float zSinApprox(const float a) 
{
	const int lookup = 1000.0f * a;

	if ( (SinTable[(lookup+3142 + 6284*1000) % 6284] < 0.05) &&
		 (SinTable[(lookup+3142 + 6284*1000) % 6284] > -0.05))
		return sin(a);
	else
		return SinTable[(lookup+3142 + 6284*1000) % 6284];
}

float zCosApprox(const float a) 
{
	const int lookup = 1000.0f * a;

	if ( (SinTable[(lookup+3142 +3142/2 + 6284*1000) % 6284] < 0.05) &&
		 (SinTable[(lookup+3142 +3142/2 + 6284*1000) % 6284] > -0.05))
		return cos(a);
	else
		return SinTable[(lookup+3142 + 3142/2 + 6284*1000) % 6284];
}
*/
void zSinCosApprox (const float a, float &sinval, float &cosval) 
{
	int lookup = (int(1000.0f * a) +3142+6284*1000) % 6284;

	sinval = SinTable[lookup];
	if ((sinval < 0.05) && (sinval > -0.05))
		sinval = sin(a);
	
	
	if (lookup >= 6284-3142/2)  // 4713
		lookup -= 3*(3142/2);   // 4713
	else
		lookup += 3142/2;       // 1571
	cosval = SinTable[lookup];
	if ((cosval < 0.05) && (cosval > -0.05))
		cosval = cos(a);	
}




// ============================================================================================================
