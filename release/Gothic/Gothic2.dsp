# Microsoft Developer Studio Project File - Name="Gothic2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GOTHIC2 - WIN32 RELEASE
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Gothic2.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Gothic2.mak" CFG="GOTHIC2 - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Gothic2 - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "Gothic2 - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE "Gothic2 - Win32 Goldmaster" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/release/Gothic", VBAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Gothic2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "release"
# PROP Intermediate_Dir "release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /G6 /Zp4 /MT /W3 /GR /GX /Zd /O2 /Ob2 /I "..\..\libraries\SmartHeap\inc\\" /I "..\..\libraries\DirectX\inc\\" /I "..\..\libraries\ProtectCD\inc" /I "..\..\libraries\BugSlayerUtil\inc\\" /I "..\..\libraries\S3tc\inc\\" /I "..\\ZenGin\res" /I "..\\ZenGin\_manuel" /I "..\\Gothic\_manuel" /I "..\\Gothic\_roman" /I "..\\Gothic\_kurt" /I "..\\netgothic\_bert" /I "..\\ZenGin" /I "..\\ZenGin\_kurt" /I "..\\ZenGin\_andre" /I "..\\ZenGin\_bert" /I "..\\ZenGin\_carsten" /I "..\\ZenGin\_dieter" /I "..\\ZenGin\_ulf" /I "..\\ZenGin\_roman" /I "..\\Gothic\_andre" /I "..\\Gothic\_bert" /I "..\\Gothic\_carsten" /I "..\\Gothic\_ulf" /I "..\..\libraries\SmartHeap\inc" /I "..\..\libraries\Miles\inc" /I "..\..\libraries\DirectX\inc" /I "..\..\libraries\bink\inc" /I "..\..\libraries\BugSlayerUtil\inc" /I "..\..\libraries\Vdfs\inc" /I "..\..\libraries\Glide\inc" /I "..\..\libraries\S3tc\inc" /D "COMPILING_GOTHIC" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ZERROR" /D "_VDFS" /D "NONET" /D "LANG_DEU" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "LANG_DEU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 shdw32mt.lib dsound.lib mss32.lib version.lib comctl32.lib imm32.lib win32spl.lib winmm.lib wow32.lib wsock32.lib bugslayerutil.lib mallocwin32debug.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x800000 /subsystem:windows /pdb:none /debug /machine:I386 /nodefaultlib:"libmmt" /nodefaultlib:"libc" /out:"..\..\binaries\System\Gothic2.exe" /libpath:"..\..\libraries\DirectX\lib\\" /libpath:"..\..\libraries\Miles\lib\\" /libpath:"..\..\libraries\BugSlayerUtil\lib" /libpath:"..\..\libraries\Vdfs\lib" /libpath:"..\..\libraries\ProtectCD\lib" /libpath:"..\..\libraries\MallocWin32Debug\lib\\" /libpath:"..\..\libraries\S3tc\lib" /libpath:"..\..\libraries\SmartHeap\lib\\" /fixed:no /release

!ELSEIF  "$(CFG)" == "Gothic2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /Zp4 /MTd /W3 /Gm /Gi /GR /GX /Zi /Od /I "..\\ZenGin\res" /I "..\\ZenGin\_manuel" /I "..\\Gothic\_manuel" /I "..\\Gothic\_roman" /I "..\\Gothic\_kurt" /I "..\\netgothic\_bert" /I "..\\ZenGin" /I "..\\ZenGin\_kurt" /I "..\\ZenGin\_andre" /I "..\\ZenGin\_bert" /I "..\\ZenGin\_carsten" /I "..\\ZenGin\_dieter" /I "..\\ZenGin\_ulf" /I "..\\ZenGin\_roman" /I "..\\Gothic\_andre" /I "..\\Gothic\_bert" /I "..\\Gothic\_carsten" /I "..\\Gothic\_ulf" /I "..\..\libraries\SmartHeap\inc" /I "..\..\libraries\Miles\inc" /I "..\..\libraries\DirectX\inc" /I "..\..\libraries\bink\inc" /I "..\..\libraries\BugSlayerUtil\inc" /I "..\..\libraries\Vdfs\inc" /I "..\..\libraries\Glide\inc" /I "..\..\libraries\ProtectCD\inc" /I "..\..\libraries\S3tc\inc" /I "..\..\libraries\SecuROM\inc" /D "COMPILING_GOTHIC" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ZERROR" /D "NONET" /D "_VDFS" /D "LANG_DEU" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "LANG_DEU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib comctl32.lib imm32.lib win32spl.lib winmm.lib wow32.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x400000 /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libm.lib" /out:"..\..\binaries\System\Gothic2-dbg.exe" /libpath:"..\..\libraries\S3tc\lib\\" /libpath:"..\..\libraries\DirectX\lib\\" /libpath:"..\..\libraries\Miles\lib\\" /libpath:"..\..\libraries\BugSlayerUtil\lib" /libpath:"..\..\libraries\Vdfs\lib" /libpath:"..\..\libraries\ProtectCD\lib" /libpath:"..\..\libraries\MallocWin32Debug\lib\\" /libpath:"..\..\libraries\S3tc\lib" /libpath:"..\..\libraries\SmartHeap\lib\\"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Gothic2 - Win32 Goldmaster"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Gothic2___Win32_Goldmaster"
# PROP BASE Intermediate_Dir "Gothic2___Win32_Goldmaster"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "goldmaster"
# PROP Intermediate_Dir "goldmaster"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /Zp4 /MT /W3 /GR /GX /Zd /O2 /Ob2 /I "..\..\libraries\SmartHeap\inc\\" /I "..\..\libraries\DirectX\inc\\" /I "..\..\libraries\ProtectCD\inc" /I "..\..\libraries\BugSlayerUtil\inc\\" /I "..\..\libraries\S3tc\inc\\" /I "..\\ZenGin\res" /I "..\\ZenGin\_manuel" /I "..\\Gothic\_manuel" /I "..\\Gothic\_roman" /I "..\\Gothic\_kurt" /I "..\\netgothic\_bert" /I "..\\ZenGin" /I "..\\ZenGin\_kurt" /I "..\\ZenGin\_andre" /I "..\\ZenGin\_bert" /I "..\\ZenGin\_carsten" /I "..\\ZenGin\_dieter" /I "..\\ZenGin\_ulf" /I "..\\ZenGin\_roman" /I "..\\Gothic\_andre" /I "..\\Gothic\_bert" /I "..\\Gothic\_carsten" /I "..\\Gothic\_ulf" /I "..\..\libraries\SmartHeap\inc" /I "..\..\libraries\Miles\inc" /I "..\..\libraries\DirectX\inc" /I "..\..\libraries\bink\inc" /I "..\..\libraries\BugSlayerUtil\inc" /I "..\..\libraries\Vdfs\inc" /I "..\..\libraries\Glide\inc" /I "..\..\libraries\S3tc\inc" /I "..\..\libraries\SecuROM\inc" /D "COMPILING_GOTHIC" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ZERROR" /D "_VDFS" /D "NONET" /D "LANG_DEU" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /G6 /Zp4 /MT /W3 /GR /GX /O2 /Ob2 /I "..\..\libraries\SmartHeap\inc\\" /I "..\..\libraries\DirectX\inc\\" /I "..\..\libraries\ProtectCD\inc" /I "..\..\libraries\BugSlayerUtil\inc\\" /I "..\..\libraries\S3tc\inc\\" /I "..\\ZenGin\res" /I "..\\ZenGin\_manuel" /I "..\\Gothic\_manuel" /I "..\\Gothic\_roman" /I "..\\Gothic\_kurt" /I "..\\netgothic\_bert" /I "..\\ZenGin" /I "..\\ZenGin\_kurt" /I "..\\ZenGin\_andre" /I "..\\ZenGin\_bert" /I "..\\ZenGin\_carsten" /I "..\\ZenGin\_dieter" /I "..\\ZenGin\_ulf" /I "..\\ZenGin\_roman" /I "..\\Gothic\_andre" /I "..\\Gothic\_bert" /I "..\\Gothic\_carsten" /I "..\\Gothic\_ulf" /I "..\..\libraries\SmartHeap\inc" /I "..\..\libraries\Miles\inc" /I "..\..\libraries\DirectX\inc" /I "..\..\libraries\bink\inc" /I "..\..\libraries\BugSlayerUtil\inc" /I "..\..\libraries\Vdfs\inc" /I "..\..\libraries\Glide\inc" /I "..\..\libraries\S3tc\inc" /I "..\..\libraries\SecuROM\inc" /D "COMPILING_GOTHIC" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ZERROR" /D "_VDFS" /D "NONET" /D "LANG_DEU" /D "GOLDMASTER" /D "SECUROM" /FAs /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "LANG_DEU"
# ADD RSC /l 0x407 /d "NDEBUG" /d "LANG_DEU" /d "GOLDMASTER"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 shdw32mt.lib dsound.lib mss32.lib version.lib comctl32.lib imm32.lib win32spl.lib winmm.lib wow32.lib wsock32.lib bugslayerutil.lib mallocwin32debug.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x800000 /subsystem:windows /pdb:none /debug /machine:I386 /nodefaultlib:"libmmt" /nodefaultlib:"libc" /out:"..\..\binaries\System\Gothic2.exe" /libpath:"..\..\libraries\DirectX\lib\\" /libpath:"..\..\libraries\Miles\lib\\" /libpath:"..\..\libraries\BugSlayerUtil\lib" /libpath:"..\..\libraries\Vdfs\lib" /libpath:"..\..\libraries\ProtectCD\lib" /libpath:"..\..\libraries\MallocWin32Debug\lib\\" /libpath:"..\..\libraries\S3tc\lib" /libpath:"..\..\libraries\SmartHeap\lib\\" /fixed:no /release
# ADD LINK32 shdw32mt.lib dsound.lib mss32.lib version.lib comctl32.lib imm32.lib win32spl.lib winmm.lib wow32.lib wsock32.lib bugslayerutil.lib mallocwin32debug.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x800000 /subsystem:windows /pdb:none /map /machine:I386 /nodefaultlib:"libmmt" /nodefaultlib:"libc" /out:"..\..\binaries\System\Gothic2-gold.exe" /libpath:"..\..\libraries\DirectX\lib\\" /libpath:"..\..\libraries\Miles\lib\\" /libpath:"..\..\libraries\BugSlayerUtil\lib" /libpath:"..\..\libraries\Vdfs\lib" /libpath:"..\..\libraries\ProtectCD\lib" /libpath:"..\..\libraries\MallocWin32Debug\lib\\" /libpath:"..\..\libraries\S3tc\lib" /libpath:"..\..\libraries\SmartHeap\lib\\" /fixed:no /release
# SUBTRACT LINK32 /debug

!ENDIF 

# Begin Target

# Name "Gothic2 - Win32 Release"
# Name "Gothic2 - Win32 Debug"
# Name "Gothic2 - Win32 Goldmaster"
# Begin Group "Andre"

# PROP Default_Filter ""
# Begin Group "Game"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_andre\oCsManager.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\oCsManager.h
# End Source File
# Begin Source File

SOURCE=.\_andre\oCsPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\oCsPlayer.h
# End Source File
# Begin Source File

SOURCE=.\_andre\oCsProps.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\oCsProps.h
# End Source File
# Begin Source File

SOURCE=.\_andre\oCsTrigger.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\oCsTrigger.h
# End Source File
# End Group
# Begin Group "Engine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsContext.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsContext.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsCutscene.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsCutscene.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsLib.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsLib.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsManager.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsManager.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsPlayer.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsPool.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsPool.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsProps.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_andre\zCCsProps.h
# End Source File
# End Group
# End Group
# Begin Group "Bert"

# PROP Default_Filter ""
# Begin Group "Game Nr. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_bert\oBinkPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\oBinkPlayer.h
# End Source File
# Begin Source File

SOURCE=.\_bert\oGameInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\oGameInfo.h
# End Source File
# Begin Source File

SOURCE=.\_bert\oGameManager.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\oGameManager.h
# End Source File
# Begin Source File

SOURCE=.\_bert\oMenu_Tools.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\oMenu_Tools.h
# End Source File
# Begin Source File

SOURCE=.\_bert\oMenuSavegame.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\oMenuSavegame.h
# End Source File
# Begin Source File

SOURCE=.\_bert\ooBert.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\ooBert.h
# End Source File
# Begin Source File

SOURCE=.\_bert\oPlayerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\oPlayerInfo.h
# End Source File
# Begin Source File

SOURCE=.\_bert\oSaveGame.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\oSaveGame.h
# End Source File
# Begin Source File

SOURCE=.\_bert\oSysInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\oSysInfo.h
# End Source File
# Begin Source File

SOURCE=.\_bert\oTrigger.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\oTrigger.h
# End Source File
# Begin Source File

SOURCE=.\_bert\oViewProgressbar.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\oViewProgressbar.h
# End Source File
# Begin Source File

SOURCE=.\_bert\oViewStatusbar.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\oViewStatusbar.h
# End Source File
# End Group
# Begin Group "Engine Nr. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ZenGin\_bert\zBinkPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zBinkPlayer.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zBuffer.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zDisk.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zDisk.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zDisk_Vdfs.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zDisk_Vdfs.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zError.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zError.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zFileCsv.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zFileCsv.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zGameInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zGameInfo.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNet.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNet.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNet_Win32.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNet_Win32.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetEventMan.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetEventMan.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetHost.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetHost.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetManager.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetManager.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetMessage.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetMessage.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetSession.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetSession.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetTypes.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetTypes.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetVersion.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetVersion.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetVobControl.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zNetVobControl.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zOption.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zOption.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zPlayerGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zPlayerGroup.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zPlayerInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zPlayerInfo.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zQueue.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zScanDir.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zScanDir.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zSpyTypes.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zString.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zString.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zSysInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zSysInfo.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zVideoPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zVideoPlayer.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zViewProgressbar.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zViewProgressbar.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zViewStatusbar.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zViewStatusbar.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zWorldInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zWorldInfo.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zzBert.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_bert\zzBert.h
# End Source File
# End Group
# End Group
# Begin Group "Carsten"

# PROP Default_Filter ""
# Begin Group "Game Nr. 2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_carsten\oAiHuman_Magic.cpp
# End Source File
# Begin Source File

SOURCE=.\_carsten\oMagFrontier.cpp
# End Source File
# Begin Source File

SOURCE=.\_carsten\oMagFrontier.h
# End Source File
# Begin Source File

SOURCE=.\_carsten\oMagic.cpp
# End Source File
# Begin Source File

SOURCE=.\_carsten\oMagic.h
# End Source File
# Begin Source File

SOURCE=.\_carsten\oMenu_Main.cpp
# End Source File
# Begin Source File

SOURCE=.\_carsten\oMenu_Main.h
# End Source File
# Begin Source File

SOURCE=.\_carsten\oMenu_Status.cpp
# End Source File
# Begin Source File

SOURCE=.\_carsten\oMenu_Status.h
# End Source File
# Begin Source File

SOURCE=.\_carsten\ooCarsten.cpp
# End Source File
# Begin Source File

SOURCE=.\_carsten\ooCarsten.h
# End Source File
# Begin Source File

SOURCE=.\_carsten\oSpell.cpp
# End Source File
# Begin Source File

SOURCE=.\_carsten\oSpell.h
# End Source File
# Begin Source File

SOURCE=.\_carsten\oVisFx.cpp
# End Source File
# Begin Source File

SOURCE=.\_carsten\oVisFx.h
# End Source File
# Begin Source File

SOURCE=.\_carsten\oVisFx_Edit.cpp
# End Source File
# Begin Source File

SOURCE=.\_carsten\oVisFx_Edit.h
# End Source File
# Begin Source File

SOURCE=.\_carsten\oVisFx_MultiTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\_carsten\oVisFx_MultiTarget.h
# End Source File
# End Group
# Begin Group "Engine Nr. 2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ZenGin\_carsten\zAiCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zAiCamera.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zAiCamera_Core.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zAiCamera_Core.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zAiCamera_Dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zAiCamera_Dialog.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zAiCamera_Movement.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zAiCamera_Movement.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zAiCamera_Util.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zAiCamera_Util.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zCpuSpecs.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zCsCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zCsCamera.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zDbgTools.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zDbgTools.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zExceptionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zExceptionHandler.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zExHnd_Bugslayer.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zFlash.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zFlash.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zInput.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zInput.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zInput_Const.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zInput_Win32.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zInput_Win32.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zKbSplines.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zKbSplines.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zList2.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMathTools.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMathTools.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMenu.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMenu_Item.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMenu_Item.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMusic.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMusic.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMusic_Dm.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMusic_Dm.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zOption_Const.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zSndMss.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zSndMss.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zVideo_Win32.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zVideo_Win32.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zViews.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zViews.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zWin32.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zWin32.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zWin32_Internal.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zzCarsten.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zzCarsten.h
# End Source File
# End Group
# End Group
# Begin Group "Dieter"

# PROP Default_Filter ""
# Begin Group "Game Nr. 3"

# PROP Default_Filter ""
# End Group
# Begin Group "Engine Nr. 3"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ZenGin\_dieter\z3D.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\z3D.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zAi.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zAi.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zAiPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zAiPlayer.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zAlgebra.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zAlgebra.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zArchive2Container.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zArchiver.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zArchiver.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zArchiver2.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zArchiver2.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zArchiverGeneric.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zArchiverGeneric.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zBsp.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zBsp.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zBspBuild.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zBspIndoor.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zBVolume.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zBVolume.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zCollisionDetector.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zCollisionDetector.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zCollisionObject.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zCollisionObject.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zCollisionObjectMisc.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zCollisionObjectMisc.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zCollisionObjectMiscChar.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zCompilerVcWin32.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zContainer.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zConvexCollision.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zConvexCollision.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zCore.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zDecal.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zEigen.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zEigen.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zEngine.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zFft.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zFft.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zFile3D.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zFile3D.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zFileQBsp.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zFixPnt.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zLensflare.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zLensflare.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMaterial.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMaterial.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMemory.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMemory.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMemory_Base.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMemory_Generic.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMemory_Generic.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMemory_Win32.cpp

!IF  "$(CFG)" == "Gothic2 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Gothic2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Gothic2 - Win32 Goldmaster"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMemory_Win32.h

!IF  "$(CFG)" == "Gothic2 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Gothic2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Gothic2 - Win32 Goldmaster"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMemPool.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMemPool.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMesh.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zModel.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zModel.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zModelProto.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMorphMesh.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMorphMesh.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMoving.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMoving.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zObject.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zObject.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zParticle.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zParticle.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zPhysics.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zPhysics.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zPluecker.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zPluecker.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zPolygon.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zPolyPool.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zPolyPool.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zPolyStrip.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zPolyStrip.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zPrime.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zPrime.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zProgMesh.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zProgMesh.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zProgMeshBuild.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zProgMeshProto.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zQuadMark.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zRayCache.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zRayCache.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zRenderer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zRenderer.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zRenderLightContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zRenderLightContainer.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zRenderManager.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zRenderManager.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zResource.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zResource.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSession.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSession.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSky.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSky.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSky_Outdoor.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSky_Outdoor.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSound.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSound.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSoundMan.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSoundMan.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSparseArray.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zSparseArray.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zTexFile.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zTexture.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zTexture.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zThread.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zThread.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zTools.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zTools.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zTrigo.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zTrigo.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zTypes.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zTypes3D.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zTypes3D.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zVertexBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zVertexBuffer.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zVertexTransform.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zVisual.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zVob.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zVob.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zVobLight.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zVobMisc.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zVobMisc.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zVobMove.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zWorld.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zWorld.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zWorldLight.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zzDieter.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zzDieter.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zZone.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zZone.h
# End Source File
# End Group
# End Group
# Begin Group "Kurt"

# PROP Default_Filter ""
# Begin Group "Game Nr. 4"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_kurt\oMusicZone.cpp
# End Source File
# Begin Source File

SOURCE=.\_kurt\oMusicZone.h
# End Source File
# End Group
# Begin Group "Engine Nr. 4"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ZenGin\_kurt\zMusicCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zMusicCtrl.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_DxtcCache.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_DxtcCache.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_Init.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_Init.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_Render.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_Render.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_State.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_State.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_SurfaceCache.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_SurfaceCache.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_Texture.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_Texture.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_VertexBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_VertexBuffer.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_Vid.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zRndD3D_Vid.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zTexConvert.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zTexConvert.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_kurt\zTexConvPalette.cpp
# End Source File
# End Group
# End Group
# Begin Group "Manuel"

# PROP Default_Filter ""
# Begin Group "Game Nr. 5"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_manuel\oCollisionObjectMiscChar.cpp
# End Source File
# Begin Source File

SOURCE=.\_manuel\oCollisionObjectMiscChar.h
# End Source File
# End Group
# Begin Group "Engine Nr. 5"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ZenGin\_manuel\zAccount.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_manuel\zAccount.h
# End Source File
# End Group
# End Group
# Begin Group "Roman"

# PROP Default_Filter ""
# Begin Group "Game Nr. 6"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_roman\oDamage.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oDamage.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oDocumentManager.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oDocumentManager.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oIncDialogs.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oIncViews.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oInformationManager.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oInformationManager.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oLogManager.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oLogManager.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oNpc_Damage.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oNpc_Damage.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oNpc_Fight.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oNpc_Fight.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oNpc_Move.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oNpc_Move.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDialogInventory.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDialogInventory.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDialogItem.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDialogItem.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDialogItemContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDialogItemContainer.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDialogStealContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDialogStealContainer.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDialogTrade.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDialogTrade.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDocument.h
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDocumentMap.cpp
# End Source File
# Begin Source File

SOURCE=.\_roman\oViewDocumentMap.h
# End Source File
# End Group
# Begin Group "Engine Nr. 6"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ZenGin\_roman\zIncDialogs.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zIncViews.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewBase.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewDialog.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewDialogChoice.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewDialogChoice.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewDraw.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewDraw.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewFx.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewFx.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewObject.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewObject.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewPrint.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewPrint.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewPrint_Font.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_roman\zViewPrint_Font.h
# End Source File
# End Group
# End Group
# Begin Group "Ulf"

# PROP Default_Filter ""
# Begin Group "Game Nr. 7"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_ulf\oAiHuman.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oAiHuman.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oAiShoot.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oAiShoot.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oAniCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oAniCtrl.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oBarrier.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oBarrier.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oDialog.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oDoc.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oFocus.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oFocus.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oGame.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oGame.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oGameExternal.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oGameKeys.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oGuilds.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oGuilds.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oHelp.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oInfo.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oInventory.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oInventory.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oItem.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oItem.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oItemReact.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oItemReact.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oMission.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oMission.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oMobInter.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oMobInter.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oNews.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oNews.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oNpc.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oNpc.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oNpcInv.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oNpcMessages.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oNpcMessages.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oNpcStates.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oNpcStates.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oObjFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oObjFactory.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\ooUlfi.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oParticleControl.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oParticleControl.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oPortals.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oPortals.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oRoutine.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oRoutine.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oSpawn.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oSpawn.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oSvm.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oSvm.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oText.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oText.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oVob.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oVob.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oWaynet.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oWaynet.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\oWorld.cpp
# End Source File
# Begin Source File

SOURCE=.\_ulf\oWorld.h
# End Source File
# Begin Source File

SOURCE=.\_ulf\Phoenix.cpp
# End Source File
# End Group
# Begin Group "Engine Nr. 7"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ZenGin\_ulf\zConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zConsole.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zEventMan.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zEventMan.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zFonts.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zFonts.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zGrafix.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zGrafix.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zList.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zParser.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zParser.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zParser_Const.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zParser_Lexer.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zParser_Symbol.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zParser_Symbol.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zView.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zView.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zWaynet.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zWaynet.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zzUlfi.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zzUlfi.h
# End Source File
# End Group
# End Group
# Begin Group "Libraries"

# PROP Default_Filter ""
# Begin Group "Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\libraries\BugSlayerUtil\inc\BaseTsd.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\BaseTsd.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\Bink\inc\Bink.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\D3dx.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\D3dxCore.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\D3dxErr.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\D3dxMath.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\D3dxMath.inl
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\D3dxShapes.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\D3dxSprite.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\Dls1.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\DmDls.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\DmError.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\DmKsCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\DmPlugin.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\DMusBuff.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\DMusicC.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\DMusicI.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\Miles\inc\Mss.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\Bink\inc\RadBase.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\Bink\inc\RadMem.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\S3tc\inc\S3_Intrf.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\SmartHeap\inc\SmrtHeap.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\SmartHeap\inc\SmrtHeap.hpp
# End Source File
# Begin Source File

SOURCE=..\..\libraries\Vdfs\inc\Vdfs32g.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\libraries\Bink\lib\BinkW32.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\BugSlayerUtil\lib\ImageHlp.Lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\BugSlayerUtil\lib\BugSlayerUtil.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\Miles\lib\Mss32.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\SmartHeap\lib\ShDW32Mt.lib

!IF  "$(CFG)" == "Gothic2 - Win32 Release"

!ELSEIF  "$(CFG)" == "Gothic2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Gothic2 - Win32 Goldmaster"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\lib\DDraw.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\lib\D3dx.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\lib\DxGuid.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\S3tc\lib\S3tc.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\MallocWin32Debug\lib\MallocWin32Debug.lib

!IF  "$(CFG)" == "Gothic2 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Gothic2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Gothic2 - Win32 Goldmaster"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\lib\DInput.lib
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ZenGin\res\Gothic2.exe.manifest
# End Source File
# Begin Source File

SOURCE=..\ZenGin\res\Gothic2.ico
# End Source File
# Begin Source File

SOURCE=..\ZenGin\res\Splash.bmp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\res\zRes.rc
# End Source File
# Begin Source File

SOURCE=..\ZenGin\res\zWin32_Resource.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\res\zWin32_Version.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\ZenGin\zLocal.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\zLocal.h
# End Source File
# End Target
# End Project
