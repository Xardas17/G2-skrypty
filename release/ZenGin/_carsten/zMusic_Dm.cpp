/*************************************************************************************************
  $Log:: /current_work/ZenGin/_Carsten/zMusic_DM.cpp  $
 * 
 * 37    1.02.01 15:24 Speckels
 * 
 * 36    31.01.01 18:26 Speckels
 * 
 * 35    31.01.01 18:23 Speckels
 * 
 * 34    31.01.01 1:37 Hildebrandt
 * dreck anderer leute weggeraeumt
 * 
 * 33    31.01.01 1:37 Hildebrandt
 * 
 * 32    30.01.01 15:41 Speckels
 * 
 * 31    30.01.01 15:19 Speckels
 * 
 * 30    29.01.01 22:28 Pelzer
 * 
 * 29    28.01.01 17:38 Pelzer
 * 
 * 28    27.01.01 22:05 Pelzer
 * 
 * 27    26.01.01 15:54 Edenfeld
 * 
 * 26    25.01.01 20:47 Pelzer
 * 
 * 25    24.01.01 20:34 Pelzer
 * 
 * 24    23.01.01 22:12 Edenfeld
 * 
 * 23    10.01.01 14:41 Keskenti
 * 
 * 22    9.01.01 14:55 Keskenti
 * 
 * 21    6.12.00 13:15 Edenfeld
 * 
 * 20    13.11.00 23:40 Edenfeld
 * 
 * 19    4.10.00 19:52 Pelzer
 * 
 * 18    20.09.00 16:43 Pelzer
 * 
 * 17    20.09.00 16:39 Pelzer
 * 
 * 16    19.09.00 18:20 Pelzer
 * 
 * 15    12.09.00 13:25 Pelzer
 * 
 * 14    11.09.00 19:43 Pelzer
 * 
 * 13    29.08.00 20:06 Pelzer
 * 
 * 12    29.08.00 18:20 Moos
 * 
 * 11    29.08.00 15:11 Pelzer
 * 
 * 17    29.08.00 14:52 Pelzer
 * 
 * 16    23.08.00 21:47 Admin
 * 
 * 9     21.07.00 18:29 Edenfeld
 * 
 * 8     21.07.00 17:04 Edenfeld
 * 
 * 7     21.07.00 15:34 Edenfeld
 * 
 * 6     21.07.00 0:37 Edenfeld
 * 
 * 5     14.07.00 13:44 Edenfeld
 * 
 * 4     11.05.00 5:44 Edenfeld
 * 
 * 4     11.05.00 5:11 Edenfeld
 * 
 * 3     4.05.00 20:29 Edenfeld
 * 
 * 2     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:15 Edenfeld
 * 
 * 8     27.03.00 23:09 Edenfeld
 * 
 * 7     19.02.00 17:28 Edenfeld
 * 
 * 6     16.02.00 20:32 Edenfeld
 * 
 * 5     5.01.00 22:28 Edenfeld
 * 
 * 4     30.11.99 21:50 Edenfeld
 * 
 * 3     30.11.99 21:42 Edenfeld
 * VSS kompatiblen Header eingefügt
 * TR_TYPE_NONE fix
 * neue transition types
*************************************************************************************************/
// zMusic_DM.cpp
// Carsten Edenfeld


#define MULTI_TO_WIDE( x,y ) MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, y, -1, x, _MAX_PATH );
static char szDirectMusicMedia[] = "\\DMusic\\Media";

#include "zcore.h"
#include "zparser.h"
#include "zmusic_dm.h"
#include "zconsole.h"
#include "zoption.h"
#include "zrndd3d.h"					// DXTryWarning

#include <dmksctrl.h>
#include <dmusici.h>

static zCParser *musParser	= 0;
static zSTRING	scriptCfgInstance("musicSysConfig");

static zBOOL	fAutoDownload = FALSE;

#ifndef Lerp
#define Lerp(t, a, b) ( a + t * (b - a) ) 
#endif

//-----------------------------------------------------------------------------
// Global variables 
//-----------------------------------------------------------------------------

IDirectMusicBand*		 activeBand		= NULL;
IDirectMusicLoader*      g_pLoader      = NULL;
IDirectMusicPerformance* g_pPerformance = NULL;
IDirectMusicPort*		 g_pPort		= NULL;	// 21-Jan-01 [PELZER]
IDirectMusicComposer*	 g_pComposer	= NULL;
IDirectMusicStyle*       g_pStyle       = NULL;
IDirectMusicSegment*	 g_pSeg			= NULL;
WCHAR					 wlpszFileName[MAX_PATH];


//-----------------------------------------------------------------------------
// Function: InitializeSynth
//
// Description: 
//      Initialize the software synthesizer into the performance.
//      This function also calls IDirectMusicPerformance::Init to
//      initialize the performance and create the DirectMusic object.
//
//
//  26-Aug-00       [PELZER] dmos.dwEffectFlags	 = DMUS_EFFECT_REVERB; hinzugefügt.
//  12-Sep-00       [PELZER] Aktivierung eines Standard-Reverb-Effects.
//	09-Jan-01		[PELZER] ReverbMix auf -45 abgeändert
//
//-----------------------------------------------------------------------------
static HRESULT InitializeSynth()
{
    HRESULT           hr;
    IDirectMusic*     pDM;
    DMUS_PORTPARAMS   dmos;
    GUID              guidSink;

    // Initialize the performance. Have the performance create the
    // DirectMusic object by setting pDM to NULL. It is needed to
    // create the port.
    pDM = NULL;
    hr = g_pPerformance->Init( &pDM ,NULL,NULL);
    if ( FAILED(hr) )
        return hr;
    
    // Set autodownloading to be on.  This will cause DLS instruments to be downloaded
	// whenever a segment is played, and unloaded whenever it stops.  Please see the
	// DirectMusic documentation for more information.
	g_pPerformance->SetGlobalParam(GUID_PerfAutoDownload,&fAutoDownload,sizeof(BOOL));
    // Create the software synth port.
    // An alternate, easier method is to call
    // pPerf->AddPort(NULL), which automatically
    // creates the synth port, adds it to the
    // performance, and assigns PChannels.
    ZeroMemory( &dmos, sizeof(DMUS_PORTPARAMS) );
    dmos.dwSize = sizeof(DMUS_PORTPARAMS);  
    dmos.dwChannelGroups = 2; // create 2 channel groups on the port
    dmos.dwValidParams = DMUS_PORTPARAMS_CHANNELGROUPS|DMUS_PORTPARAMS_VOICES|DMUS_PORTPARAMS_EFFECTS;
	dmos.dwVoices		 = 64;
	dmos.dwEffectFlags	 = DMUS_EFFECT_REVERB;

    ZeroMemory( &guidSink, sizeof(GUID) );

	if( g_pPort )	// 21-Jan-01 [PELZER]
		g_pPort->Release();

    hr = pDM->CreatePort( CLSID_DirectMusicSynth, &dmos, &g_pPort, NULL );
    if ( FAILED(hr) )
        return hr;


    hr = pDM->Activate( TRUE );
    if ( FAILED(hr) )
	{
	    MessageBox( NULL, "Could not activate DMusic", 
                    "PlayMotf", MB_ICONERROR | MB_OK );
        return hr;
	}

    // Succeeded in creating the port. Add the port to the
    // Performance with five groups of 16 midi channels.
    hr = g_pPerformance->AddPort( g_pPort );
    if ( FAILED(hr) )
        return hr;


    // Assign a block of 16 PChannels to this port.
    // Block 0, port pPort, and group 1 means to assign
    // PChannels 0-15 to group 1 on port pPort.
    // PChannels 0-15 correspond to the standard 16
    // MIDI channels.
    g_pPerformance->AssignPChannelBlock( 0, g_pPort, 1 );
	if (!zoptions->ReadBool("ENGINE", "zMusic16ChannelsOnly", FALSE))	g_pPerformance->AssignPChannelBlock( 1, g_pPort, 2 );	

	if( g_pPort )
	{
		// Query for IKsControl interface.
		IKsControl *pControl;
		HRESULT hr = g_pPort->QueryInterface( IID_IKsControl, (void**)&pControl );
		if( SUCCEEDED( hr ) ) 
		{
			KSPROPERTY ksp;
			ULONG cb;

			DWORD dwEffects = 0;
			ZeroMemory( &ksp, sizeof( ksp ) );
			dwEffects = DMUS_EFFECT_REVERB;
			ksp.Set   = GUID_DMUS_PROP_Effects;
			ksp.Id    = 0;
			ksp.Flags = KSPROPERTY_TYPE_SET;
 			pControl->KsProperty( &ksp,
								 sizeof( ksp ),
								 (LPVOID)&dwEffects,
								 sizeof( dwEffects ),
								 &cb );

			DMUS_WAVES_REVERB_PARAMS Params;
			Params.fInGain = 0.0f;
			Params.fReverbMix = -45.0f;
			Params.fReverbTime = 9000.0f;
			Params.fHighFreqRTRatio = 0.001f;
			ZeroMemory( &ksp, sizeof( ksp ) );
			ksp.Set   = GUID_DMUS_PROP_WavesReverb;
			ksp.Id    = 0;
			ksp.Flags = KSPROPERTY_TYPE_SET;
 			pControl->KsProperty( &ksp,
								 sizeof( ksp ),
								 (LPVOID)&Params,
								 sizeof( Params ),
								 &cb );
    
			pControl->Release();
		}
	}

	g_pPort->Release();


    // release the DirectMusic object. The performance has its
    // own reference and we just needed it to call CreatePort.
    pDM->Release();

    return S_OK;
}



static zBOOL MusicConsoleEvalFunc (const zSTRING &in, zSTRING &msg) 
{
	zSTRING s = in;
	s.Upper();
	msg = "ok";
	if ( s.PickWord(1, " ") == "PLAY" ) {
		if ( s.PickWord(2, " ") == "THEME" ) {
			zSTRING id = s.PickWord(3, " ");
			zCPar_Symbol *sym = musParser->GetSymbol(id);
			if (sym) {
				zmusic->PlayThemeByScript(id);
				msg = zSTRING("now playing theme ") + id;
			} else msg = "theme identifier not found: " + id;
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "JINGLE" ) {
			zSTRING id = s.PickWord(3, " ");
			zCPar_Symbol *sym = musParser->GetSymbol(id);
			if (sym) {
				zmusic->PlayJingleByScript(id);
				msg = zSTRING("now playing jingle ") + id;
			} else msg = "jingle identifier not found: " + id ;
			return TRUE;
		} 
	}
	else if ( s.PickWord(1, " ") == "TOGGLE" ) {
		if ( s.PickWord(2, " ") == "MUSIC" ) {
			zmusic->Mute();
			return TRUE;
		} 
	}
	else if ( s.PickWord(1, " ") == "STOP" ) {
		if ( s.PickWord(2, " ") == "JINGLE" ) {
			zSTRING id = s.PickWord(3, " ");
			zCPar_Symbol *sym = musParser->GetSymbol(id);
			if (sym) {
				zmusic->StopJingleByScript(id);
				msg = zSTRING("stop playing jingle(s) ") + id;
			} else msg = "jingle identifier not found: " + id;
			return TRUE;
		}
	}
	return FALSE; 
}

static DMUS_COMMANDT_TYPES TransTypeToDMUS_COMMANDT_TYPES(zTMus_TransType trIn)
{
	switch (trIn){
	case zMUS_TR_FILL   : return DMUS_COMMANDT_FILL;
	case zMUS_TR_INTRO  : return DMUS_COMMANDT_INTRO ;      
	case zMUS_TR_BREAK  : return DMUS_COMMANDT_BREAK ;  
	case zMUS_TR_END	: return DMUS_COMMANDT_END;
	case zMUS_TR_GROOVE	: return DMUS_COMMANDT_GROOVE;
	case zMUS_TR_ENDANDINTRO: return DMUS_COMMANDT_ENDANDINTRO;
	default: return DMUS_COMMANDT_GROOVE;
	}
}

static DMUS_COMPOSEF_FLAGS TransSubTypeToDMUS_COMPOSEF_FLAGS(zTMus_TransSubType trSubIn)
{
	switch (trSubIn){
	case zMUS_TRSUB_IMMEDIATE : return DMUS_COMPOSEF_IMMEDIATE	;
	case zMUS_TRSUB_BEAT	  : return DMUS_COMPOSEF_BEAT		;      
	case zMUS_TRSUB_MEASURE   : return DMUS_COMPOSEF_MEASURE		;  
	default: return DMUS_COMPOSEF_NONE;
	}
}

static DMUS_SEGF_FLAGS TransSubTypeToDMUS_SEGF_FLAGS(zTMus_TransSubType trSubIn)
{
	switch (trSubIn){
	case zMUS_TRSUB_IMMEDIATE : return DMUS_SEGF_GRID;
	case zMUS_TRSUB_BEAT	  : return DMUS_SEGF_BEAT;      
	case zMUS_TRSUB_MEASURE   : return DMUS_SEGF_MEASURE;  
	default: return DMUS_SEGF_DEFAULT;
	}
}



zCMusicTheme_DM :: ~zCMusicTheme_DM()
{
	if (seg) seg->Release();
	seg=0;
};
// -----------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------


// [SPECKELS] Skalierung der Volume-Werte fuer Musik (MIN war deutlich zu niedrig!!
const int zMUSIC_VOLUME_MAX = DSBVOLUME_MAX;
const int zMUSIC_VOLUME_MIN = DSBVOLUME_MIN + int((DSBVOLUME_MAX-DSBVOLUME_MIN)/1.5f);

// constructor
zCMusicSys_DirectMusic :: zCMusicSys_DirectMusic ()
{
    HRESULT hr;
	zoptions->ChangeDir(DIR_SCRIPTS);

    if (!musParser) // [Moos]: safety
	    musParser = zNEW( zCParser );

	// [BENDLIN] AddonMOD
	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString(zOPT_SEC_FILES, "Music");
	if (filename.IsEmpty())
		filename = "System\\Music";
	zERR_MESSAGE(4, 0, "N: MUS: Loading file " + filename + ".src or .dat");

	musParser -> Parse(filename + ".src");
	musParser -> CreatePCode();
	musParser -> CheckClassSize(zSTRING("C_MUSICSYS_CFG"),CMusDrvProperties::GetScriptClassSize());
	musParser -> CheckClassSize(zSTRING("C_MUSICTHEME"),zCMusicTheme::GetScriptClassSize());
	musParser -> CheckClassSize(zSTRING("C_MUSICJINGLE"),zCMusicJingle::GetScriptClassSize());


    if (musParser->GetSymbol(scriptCfgInstance)) {
	   musParser->CreateInstance(scriptCfgInstance,&prefs);
    }
    // Initialize COM
    hr = CoInitialize(NULL);
    if ( FAILED(hr) ) zerr.Report(zERR_FATAL,8000,"C:zMusic_DM.cpp(zCMusicSys_DirectMusic::Init()) Failed to init com object!");

    // Create loader object
    hr = CoCreateInstance(
            CLSID_DirectMusicLoader,
            NULL,
            CLSCTX_INPROC, 
            IID_IDirectMusicLoader,
            (void**)&g_pLoader
        );
    if ( FAILED(hr) ) zERR_FATAL("C:zMusic_DM.cpp(zCMusicSys_DirectMusic::Init()) Failed to create loader object!");
	g_pLoader->EnableCache(GUID_DirectMusicAllTypes, TRUE);

    // Create performance object
    hr = CoCreateInstance(
            CLSID_DirectMusicPerformance,
            NULL,
            CLSCTX_INPROC, 
            IID_IDirectMusicPerformance,
            (void**)&g_pPerformance
        );
    if ( FAILED(hr) ) zerr.Report(zERR_FATAL,8000,"C:zMusic_DM.cpp(zCMusicSys_DirectMusic::Init()) Failed to create performance object!");

	// Initialize the composer object for transitions
	hr = CoCreateInstance(
			CLSID_DirectMusicComposer,
			NULL,
			CLSCTX_INPROC, 
			IID_IDirectMusicComposer,
			(void**)&g_pComposer
		 );
    if ( FAILED(hr) ) zerr.Report(zERR_FATAL,8000,"C:zMusic_DM.cpp(zCMusicSys_DirectMusic::Init()) Failed to create composer object!");

    // Initialize the software synthesizer
    hr = InitializeSynth();
    if ( FAILED(hr) ) zerr.Report(zERR_FATAL,8000,"C:zMusic_DM.cpp(zCMusicSys_DirectMusic::Init()) Failed to initialize synth!");

	zcon.Register("PLAY THEME",  "PLAYS A SCRIPT THEME");
	zcon.Register("PLAY JINGLE", "PLAYS A SCRIPT JINGLE");
	zcon.Register("STOP JINGLE", "Stops script jingle(s)  (not yet)");
	zcon.Register("TOGGLE MUSIC",  "Toggles music on/off");
	zcon.AddEvalFunc( MusicConsoleEvalFunc );

	// [SPECKELS] Nutzung eigener Volume-Konstanten
	long vol = (long) Lerp(prefs.volume, zMUSIC_VOLUME_MIN, zMUSIC_VOLUME_MAX);
	g_pPerformance->SetGlobalParam(GUID_PerfMasterVolume,&vol, sizeof(long));


	actTheme = 0;
	defTheme = 0;
	vol		 = 1;

}

zCMusicSys_DirectMusic :: ~zCMusicSys_DirectMusic()
{
    // Release the port
	if( g_pPort )	// 21-Jan-01 [PELZER]
	    g_pPort->Release();

    // If there is any music playing, stop it.
    g_pPerformance->Stop( NULL, NULL, 0, 0 );

    // CloseDown and Release the performance object
    g_pPerformance->CloseDown();
    g_pPerformance->Release();

    // Release the composer object
	g_pComposer->Release();

    // Release the loader object
    g_pLoader->Release();

    // Release COM
    CoUninitialize();

    delete musParser; // [Moos] fix leak
    musParser	= NULL;
	actTheme	= 0;
	defTheme	= 0;

}

void zCMusicSys_DirectMusic :: PlayThemeByScript( const zSTRING &id, int manipulate, zBOOL *done ) // 21-Jan-01 [PELZER]Optionalen Parameter 'manipulate' hinzugefügt
{	
	if (IsMusicSystemDisabled()) return; // [SPECKELS] Hinzugefuegt, um das komplette Musiksystem zu deaktivieren.

	if( done!=NULL )
		*done = TRUE;
	if (id.IsEmpty()) return;
	zSTRING identifier = id;
	identifier.Upper();
	if ( actTheme && identifier == actTheme->GetName()) return;
	zCMusicTheme *theme = LoadThemeByScript(id);
	if( theme!=NULL ) // 28-Jan-01 [PELZER]Test if we've received a new theme
	{
		switch( manipulate )
		{
		case	1:	// 21-Jan-01 [PELZER]Zonen-Change
				PlayTheme( theme, zMUS_THEME_VOL_DEFAULT, zMUS_TR_END, zMUS_TRSUB_DEFAULT );
				break;
		case	2:	// 21-Jan-01 [PELZER]Day/Night-Change
				PlayTheme( theme, zMUS_THEME_VOL_DEFAULT, zMUS_TR_NONE, zMUS_TRSUB_DEFAULT );
				break;
		default:
				PlayTheme( theme );
		}
	}
	else
	{
		if( done!=NULL )
			*done = FALSE;
	}
}

zCMusicTheme* zCMusicSys_DirectMusic :: LoadTheme( const zSTRING &file )
{ 
	if (IsMusicSystemDisabled()) return 0; // [SPECKELS] Hinzugefuegt, um das komplette Musiksystem zu deaktivieren.

	return 0;
}

zCMusicTheme* zCMusicSys_DirectMusic :: LoadThemeByScript( const zSTRING &id )
{
	if (IsMusicSystemDisabled()) return 0; // [SPECKELS] Hinzugefuegt, um das komplette Musiksystem zu deaktivieren.

	zERR_MESSAGE(5,0, "X: [LoadThemeByScript]: loading theme:" + id);

    DMUS_OBJECTDESC     ObjDesc; // Object descriptor for pLoader->GetObject()
    WCHAR               wszDir[_MAX_PATH];
	
	zSTRING identifier = id;
	identifier.Upper();

	if (actTheme && identifier == actTheme->GetName()) return actTheme;
	if (musParser->GetSymbol(identifier) == 0) {
		zerr.Report(zERR_FATAL,8000,"C: zMusic_DM.cpp(zCMusicSys_DirectMusic :: LoadThemeByScript):Unknown Theme ID: "+id);
	}
	zCMusicTheme_DM *theme = zNEW( zCMusicTheme_DM );
	musParser->CreateInstance(identifier,(zBYTE*)(&(theme->fileName))); // 27-Jan-01 [PELZER]Use theme->fileName
	theme->SetName(identifier); // hmm	

	zSTRING fileName = theme->GetFileName();
	fileName.Upper();
	zPATH path;
	if (path.SearchFile(fileName, zoptions->GetDirString(DIR_MUSIC))==zERR_NONE) path.ChangeDir();
	else 
	{
		if (path.SearchFile("DEFAULT.SGT", zoptions->GetDirString(DIR_MUSIC))==zERR_NONE)
		{
			zERR_WARNING("C: zCMusicSys_DirectMusic :: LoadThemeByScript(): could not load segment: " + fileName + ", using default segment");
			fileName = "DEFAULT.SGT";
			path.ChangeDir();
		}
		else zerr.Report(zERR_FATAL, 8000, "C: zMusic_DM.cpp(zCMusicSys_DirectMusic :: LoadThemeByScript):file not found: "+theme->GetFileName());	
	}

	zSTRING pathstr = path.GetDirectoryPath();
	zFILE::DirectFileAccess(true,pathstr);	
	MULTI_TO_WIDE( wlpszFileName, fileName.ToChar() );	
    MULTI_TO_WIDE( wszDir, pathstr.ToChar());	
    g_pLoader->SetSearchDirectory( GUID_DirectMusicAllTypes, wszDir, FALSE );
	zFILE::DirectFileAccess(false);

    // Now load the segment file.
    // Sections load as type Segment, as do MIDI files, for example.
    ObjDesc.guidClass = CLSID_DirectMusicSegment;
    ObjDesc.dwSize = sizeof(DMUS_OBJECTDESC);
    wcscpy( ObjDesc.wszFileName, wlpszFileName );
    ObjDesc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;

	HRESULT hr = g_pLoader->GetObject( &ObjDesc, IID_IDirectMusicSegment, (void**)&theme->seg);
    if( FAILED( (HRESULT)hr ) )  // 28-Jan-01 [PELZER]Test three times
	{
		char error_str[128]; 
		D3DXGetErrorString( (HRESULT)hr, 128, error_str );
		zerr.Warning("X: zCMusicSys_DirectMusic :: LoadThemeByScript(): could not get object " + id + " with filename " + fileName + " error: " + error_str);
		hr = g_pLoader->GetObject( &ObjDesc, IID_IDirectMusicSegment,(void**)&theme->seg );
		// Try it again ...
		if( FAILED( (HRESULT)hr ) ) 
		{
			char error_str[128]; 
			D3DXGetErrorString( (HRESULT)hr, 128, error_str );
			zerr.Warning("X: zCMusicSys_DirectMusic :: LoadThemeByScript(): could not get object " + id + " with filename " + fileName + " error: " + error_str);
			// and again ...
			if( FAILED( (HRESULT)hr ) ) 
			{
				char error_str[128]; 
				D3DXGetErrorString( (HRESULT)hr, 128, error_str );
				zerr.Warning("X: zCMusicSys_DirectMusic :: LoadThemeByScript(): could not get object " + id + " with filename " + fileName + " error: " + error_str);
			};
		};
		return NULL;
	};

   	IDirectMusicBand *band;

	theme->seg->GetParam( GUID_IDirectMusicStyle, -1, 0, 0, NULL, (void*)&g_pStyle );
	g_pStyle->GetDefaultBand(&band);

	if( band!=activeBand )	// 21-Jan-01 [PELZER]Bandwechsel stärker abgesichert
	{
		if( activeBand!=NULL )
		{
			zERR_MESSAGE(5,0, "X: [LoadThemeByScript]: Start change of music band ..." );
			band->Download(g_pPerformance);
			activeBand->Unload(g_pPerformance);
			activeBand = band;
			zERR_MESSAGE(5,0, "X: [LoadThemeByScript]: Changed music band." );
		}
		else
		{
			band->Download(g_pPerformance);
			activeBand = band;
			zerr.Message( "X: [LoadThemeByScript]: Loaded first music band." );
		}
	}

//	MEMORYSTATUS  MemInfo;
//    MemInfo.dwLength = sizeof(MemInfo);
//    GlobalMemoryStatus(&MemInfo);

	if (!theme->seg) zerr.Report(zERR_FATAL, 8000, "C: zMusic_DM.cpp(zCMusicSys_DirectMusic :: LoadThemeByScript):file not found: "+theme->GetFileName());

	return (zCMusicTheme*)theme;
}
	
void zCMusicSys_DirectMusic :: PlayTheme ( zCMusicTheme *theme,const float &volume, const zTMus_TransType	&tr,const zTMus_TransSubType &trSub)
{	
	if (IsMusicSystemDisabled()) return; // [SPECKELS] Hinzugefuegt, um das komplette Musiksystem zu deaktivieren.

	if (theme == 0) return;
	if (actTheme && theme->GetName() == actTheme->GetName()) return ;
	
	zCMusicTheme_DM *th = (zCMusicTheme_DM*)theme;


	zTMus_TransType	   trRes	= ( tr == zMUS_TR_DEFAULT ) ? theme->GetTransitionType() : tr;
	zTMus_TransSubType trSubRes	= ( trSub == zMUS_TRSUB_DEFAULT ) ? theme->GetTransitionSubType() : trSub;

	if ( trRes == zMUS_TR_NONE )  {
		DMUS_SEGF_FLAGS dmFlags = TransSubTypeToDMUS_SEGF_FLAGS(trSubRes);
        g_pPerformance->PlaySegment( th->seg, dmFlags, 0, NULL );
	}
	else {
		DMUS_COMPOSEF_FLAGS dmFlagsComposer = TransSubTypeToDMUS_COMPOSEF_FLAGS (trSubRes);
		DMUS_COMMANDT_TYPES dmTrans			= TransTypeToDMUS_COMMANDT_TYPES	(trRes); 

		g_pComposer->AutoTransition( g_pPerformance, th->seg, dmTrans, dmFlagsComposer, 0,0,0,0 );

	}

	if( g_pPort )  // 27-Jan-01 [PELZER]Sollte nun immer durchlaufen werden, d.h. die Reverb-Werte werden jedesmal aktualisiert
	{
		// Query for IKsControl interface.
		IKsControl *pControl;
		HRESULT hr = g_pPort->QueryInterface( IID_IKsControl, (void**)&pControl );
		if( SUCCEEDED( hr ) ) 
		{
			KSPROPERTY ksp;
			ULONG cb;

			DWORD dwEffects = 0;
			ZeroMemory( &ksp, sizeof( ksp ) );
			dwEffects = DMUS_EFFECT_REVERB;
			ksp.Set   = GUID_DMUS_PROP_Effects;
			ksp.Id    = 0;
			ksp.Flags = KSPROPERTY_TYPE_SET;
 			pControl->KsProperty( &ksp,
								 sizeof( ksp ),
								 (LPVOID)&dwEffects,
								 sizeof( dwEffects ),
								 &cb );
			DMUS_WAVES_REVERB_PARAMS Params;
			Params.fInGain = 0.0f;
			Params.fReverbMix = th->GetReverbMix();
			Params.fReverbTime = th->GetReverbTime();
			Params.fHighFreqRTRatio = 0.001f;
			ZeroMemory( &ksp, sizeof( ksp ) );
			ksp.Set   = GUID_DMUS_PROP_WavesReverb;
			ksp.Id    = 0;
			ksp.Flags = KSPROPERTY_TYPE_SET;
 			pControl->KsProperty( &ksp,
								 sizeof( ksp ),
								 (LPVOID)&Params,
								 sizeof( Params ),
								 &cb );

			pControl->Release();
		}
	}


	// delete actTheme; // [SPECKELS] geht das hier? Sonst Leak?
	actTheme = theme;
}

zTMus_JingleHandle zCMusicSys_DirectMusic :: PlayJingleByScript( const zSTRING &id   )	
{ 	
	if (IsMusicSystemDisabled()) return 0; // [SPECKELS] Hinzugefuegt, um das komplette Musiksystem zu deaktivieren.

	if (!actTheme) {
		zerr.Report(zERR_WARN,8000,"C:zMusic_DM.cpp(zCMusicSys_DirectMusic :: PlayJingleByScript): No active Theme!");
		return 0;
	}
	zCMusicJingle *j = LoadJingleByScript(id);
	return PlayJingle(j);
};

void zCMusicSys_DirectMusic :: StopJingleByScript( const zSTRING &id   )	
{
};

zCMusicJingle* zCMusicSys_DirectMusic :: LoadJingleByScript ( const zSTRING &id   )			
{ 
	if (IsMusicSystemDisabled()) return 0; // [SPECKELS] Hinzugefuegt, um das komplette Musiksystem zu deaktivieren.

	if (musParser->GetSymbol(id) == 0) {
		zerr.Report(zERR_FATAL,8000,"C: zMusic_DM.cpp(zCMusicSys_DirectMusic :: LoadJingleByScript):Unknown Jingle ID: "+id);
	}

	zSTRING identifier = id;
	identifier.Upper();

	zCMusicJingle *jing = zNEW( zCMusicJingle );
	musParser->CreateInstance(identifier,(zBYTE*)jing+4);
	jing->SetName(identifier); 

	return jing; 
};
zCMusicJingle* zCMusicSys_DirectMusic :: LoadJingle		 ( const zSTRING &file )			
{ 
	if (IsMusicSystemDisabled()) return 0; // [SPECKELS] Hinzugefuegt, um das komplette Musiksystem zu deaktivieren.

	return 0; 
};
	
zTMus_JingleHandle zCMusicSys_DirectMusic :: PlayJingle ( const zCMusicJingle *jingle,const float &volume,const zTMus_TransSubType &trSub)
{	
	if (IsMusicSystemDisabled()) return 0; // [SPECKELS] Hinzugefuegt, um das komplette Musiksystem zu deaktivieren.

	WCHAR wlpszMotifName[MAX_PATH];

	MULTI_TO_WIDE(wlpszMotifName,jingle->GetFileName().ToChar());
    IDirectMusicSegment* pSeg;
    HRESULT              hr;

    // Get the Motif Segment from the Style, setting it to play once
    // through (no repeats.) Check for S_OK specifically, because
    // GetMotif() returns S_FALSE if it doesn't find the Motif.
	if (!actTheme) return 0;
    hr = ((zCMusicTheme_DM*)actTheme)->seg->GetParam( GUID_IDirectMusicStyle, -1, 0, 0, NULL, (void*)&g_pStyle );
    hr = g_pStyle->GetMotif( wlpszMotifName, &pSeg );

    if( S_OK == hr )
    {
		DMUS_COMPOSEF_FLAGS dmFlags;

		if (trSub == zMUS_TRSUB_DEFAULT) dmFlags = TransSubTypeToDMUS_COMPOSEF_FLAGS (jingle->GetTransitionSubType());
		else dmFlags = TransSubTypeToDMUS_COMPOSEF_FLAGS (trSub);

        g_pPerformance->PlaySegment( pSeg, dmFlags | DMUS_SEGF_SECONDARY, 0, NULL );
        pSeg->Release();
    }
	else zerr.Report(zERR_WARN,8000,"C: zMusic_DM.cpp(zCMusicSys_DirectMusic::PlayJingle): No such motif: "+jingle->GetFileName());

	return 0;
};

void zCMusicSys_DirectMusic :: DoMusicUpdate()	 
{
};	// called each frame

/*--------------------------------------------------------------------------

    void zCMusicSys_DirectMusic :: Stop()		

 

    20-Sep-00       [PELZER] Neu hinzugefügt, um das momentan wiedergegebene Segment beenden zu können.

--------------------------------------------------------------------------*/ 
void zCMusicSys_DirectMusic :: Stop()
{
	g_pPerformance->Stop(0,0,0,0);
	// [SPECKELS] ActTheme auf 0 gesetzt, sonst wird evtl. der Theme beim naechsten Mal nicht wieder gestartet!
	// delete actTheme; // geht das hier? Sonst Leak?
	actTheme = 0;
};

void zCMusicSys_DirectMusic :: Mute()	
{
	static zBOOL mute = FALSE;
	mute = !mute;
	if (mute) 
	{	
		if (activeBand) activeBand->Unload(g_pPerformance);
		g_pPerformance->Stop(0,0,0,0);
	}
	else if (actTheme) 
	{
		if (activeBand) activeBand->Download(g_pPerformance);
		g_pComposer->AutoTransition( g_pPerformance, ((zCMusicTheme_DM*)actTheme)->seg, DMUS_COMMANDT_GROOVE, DMUS_COMPOSEF_MEASURE, 0,0,0,0 );
	}
};

void zCMusicSys_DirectMusic::SetVolume		  ( const float v )			
{ 
	prefs.volume = v; 
	// [SPECKELS] Nutzung eigener Volume-Konstanten
	long vol = (long)Lerp(prefs.volume, zMUSIC_VOLUME_MIN, zMUSIC_VOLUME_MAX);
	g_pPerformance->SetGlobalParam(GUID_PerfMasterVolume,&vol, sizeof(long));
};  

/*--------------------------------------------------------------------------

    zBOOL zCMusicSys_DirectMusic::IsAvailable	  ( const zSTRING &id )	

 

    26-Aug-00       [PELZER] Neu hinzugefügt, um das Vorhandensein eines neuen Themas zu prüfen.

--------------------------------------------------------------------------*/ 
zBOOL zCMusicSys_DirectMusic::IsAvailable	  ( const zSTRING &id )			
{ 
	if( musParser->GetSymbol(id)==0 )
		return FALSE;
	return TRUE;
}; 

