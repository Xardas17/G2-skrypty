/******************************************************************************** 
 
     $Workfile:: zEngine.cpp          $                $Date:: 24.04.01 17:33   $
     $Revision:: 16                   $             $Modtime:: 23.04.01 18:05   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ zEngine Main-Header-File
   created       : 22.2.97  

 * $Log: /current_work/ZenGin/_Dieter/zEngine.cpp $
 * 
 * 16    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 15    16.03.01 15:35 Speckels
 * 
 * 14    16.11.00 13:57 Speckels
 * 
 * 13    28.09.00 19:19 Hildebrandt
 * 
 * 12    25.08.00 18:54 Hildebrandt
 * 
 * 11    21.08.00 17:18 Hildebrandt
 * 
 * 10    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 9     31.07.00 19:18 Speckels
 * 
 * 8     21.07.00 15:11 Hildebrandt
 * 
 * 7     21.07.00 14:28 Hildebrandt
 *  
 * 6     19.07.00 15:56 Hildebrandt
 * 
 * 5     6.07.00 13:44 Hildebrandt
 * 
 * 4     6.07.00 13:41 Hildebrandt 
 *  
 * 3     6.07.00 13:40 Hildebrandt
 *  
 * 2     6.07.00 13:40 Hildebrandt
 * 
 * 1     6.07.00 13:39 Hildebrandt
 * 
 * 12    6.07.00 13:38 Hildebrandt
 * 
 * 11    6.07.00 13:36 Hildebrandt
 * 
 * 10    6.07.00 13:35 Hildebrandt
 *  
 * 5     10.05.00 23:27 Hildebrandt
 * zenGin 089i
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 2     22.03.00 2:58 Hildebrandt
 * zenGin 088a
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 16 $ ($Modtime: 23.04.01 18:05 $)

#include <zCore.h>
#include <zEngine.h>

#include <zzBert.h>
#include <zzCarsten.h>
#include <zzDieter.h>
#include <zzUlfi.h>
#include <zoption.h>
#include <zWin32.h>

#ifdef _VDFS
	#include "zdisk_vdfs.h"
#else
	#include "zdisk.h"
#endif

// FIXME: VC++ specific, move to another file!
#include <CrtDbg.h>

zCEngine::zCEngine()
{
};

zCEngine::~zCEngine() 
{
};


// Global Engine Open and Init-Function
zBOOL zCEngine::Init (zTSystemContextHandle* initContextHandle)
{
	zerr.SetExitFunction	(sysExit);						// sysExit  

	//
	zCClassDef::EndStartup	();								// all classes are registered by now

	// ObjectFactory
	if (!zfactory) zfactory	= zNEW(zCObjectFactory);

	sysEvent				();

	//
	zInitOptions			();

	// init memory allocator
	zmalloc.Init			(zoptions->Parm("ZMEMPROFILER"));

	// Filesystem
	#ifdef _VDFS
		zFILE_VDFS::InitFileSystem();
	#else
		zFILE_FILE::InitFileSystem();
	#endif

	sysEvent					();

	// ResourceManager
#ifdef COMPILING_SPACER
	if (!zresMan)
#endif
	zresMan						= zNEW(zCResourceManager);
	zresMan->SetThreadingEnabled(!zoptions->Parm("ZNORESTHREAD"));

	// Engine Banner
	{
		zerr.Separator			();
		zERR_MESSAGE			(0, zERR_BEGIN,	"D: "+zSTRING(zENGINE_NAME));
		zERR_MESSAGE			(0, zERR_BEGIN,	"D: *** Mad Scientists: Hildebrandt, Wohlers, Speckels");
		zSTRING s				("D: *** compiled: "+zSTRING(__DATE__));
		#ifdef _DEBUG
			s += ", debug-build";
		#else
			s += ", release-build";
		#endif
		zERR_MESSAGE			(0, 0, s);
		zERR_MESSAGE			(0, 0, "D: *** zEngine-Init ...");

		// Here add project member related init-calls.
		{
			zBert_StartUp		();
			zUlfi_StartUp		();

			sysEvent			();

			zDieter_StartUp		(initContextHandle);
			zCarsten_StartUp	(initContextHandle);
		};

		zERR_MESSAGE			(0, zERR_END, "D: *** zEngine-Init ... Done !");
		zerr.Separator			();
	};

	sysEvent					();
 
	// things to do after engine ist inited

	// convert textures?
	if (zoptions->Parm("ZTEXCONVERT")) 
	{
		zCTexture::ScanConvertTextures(zoptions->ParmValue("ZTEXCONVERT"));
	}

	// now the fpu is in the default state for the application
	// if special fpu setup is required by parts of the application, the fpu CW
	// can be saved, changed, the app does it's things, and then restores the saved CW
	zfpuControler.RestoreDefaultControlWord	();
	zfpuControler.SaveCurrentControlWord	();

	return TRUE;
}

// Global Engine Closing-Function
zBOOL zCEngine::Shutdown() 
{
	// FIXME: VC++ specific, move to another file!
	assert(_CrtCheckMemory());

	zerr.Separator			();
	zERR_MESSAGE			(0, zERR_BEGIN, "D: *** zEngine-ShutDown ...");
	
	// Here add project member related close-calls.
	zCarsten_ShutDown		();
	zDieter_ShutDown		();
	zUlfi_ShutDown			();
	zBert_ShutDown			();
	zerr.Separator			();

	// Resource-Manager
	zresMan->EndThread		(); 
	delete zresMan;		zresMan		=0;

	// Options
	zDeinitOptions();

	// ObjectFactory		
	zRELEASE (zfactory);

	// Filesystem
	#ifdef _VDFS
		zFILE_VDFS::DeinitFileSystem();
	#else
		zFILE_FILE::DeinitFileSystem();
	#endif

	// shutdown memory allocator
	zmalloc.Shutdown		();

	zERR_MESSAGE			(0, zERR_END, "D: *** zEngine-ShutDown ... Done!");
	return TRUE;
}
