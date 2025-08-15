# Microsoft Developer Studio Project File - Name="Spacer2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SPACER2 - WIN32 DEBUG
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Spacer2.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Spacer2.mak" CFG="SPACER2 - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Spacer2 - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "Spacer2 - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE "Spacer2 - Win32 Goldmaster" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/release/Spacer", VKBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Spacer2 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "release"
# PROP Intermediate_Dir "release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /Zp4 /MT /W3 /GR /GX /Zd /O2 /Ob2 /I ".\res\\" /I ".\_bert\\" /I ".\_carsten\\" /I "..\..\libraries\Miles\inc\\" /I "..\..\libraries\Vdfs\inc\\" /I "..\..\libraries\Glide\inc\\" /I "..\..\libraries\Bink\inc\\" /I "..\ZenGin\_kurt\\" /I ".\_andre\\" /I "..\ZenGin\res" /I "..\ZenGin\_andre\\" /I "..\ZenGin\_bert\\" /I "..\ZenGin\_carsten\\" /I "..\ZenGin\_dieter\\" /I "..\ZenGin\_manuel\\" /I "..\Gothic\_manuel\\" /I "..\ZenGin\_ulf\\" /I "..\ZenGin\_roman\\" /I "..\Gothic\_andre\\" /I "..\Gothic\_bert\\" /I "..\Gothic\_roman\\" /I "..\Gothic\_carsten\\" /I "..\Gothic\_ulf\\" /I "..\Gothic\_kurt\\" /I "..\..\libraries\DirectX\inc\\" /I "..\..\libraries\BugslayerUtil\inc\\" /I "..\ZenGin\\" /I "..\..\libraries\cj60\inc\\" /I "..\..\libraries\S3tc\inc\\" /D "COMPILING_GOTHIC" /D "COMPILING_SPACER" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "_MFC" /D "_ZERROR" /D "_SPACER" /D "NONET" /D "LANG_DEU" /FD /Zm700 /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /i "Res/" /d "NDEBUG" /d "COMPILING_SPACER" /d "LANG_DEU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wsock32.lib winmm.lib /nologo /stack:0x800000 /subsystem:windows /pdb:none /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrtd.lib" /force /out:"..\..\binaries\_work\tools\Spacer\Spacer2.exe" /libpath:"..\..\libraries\Miles\lib\win" /libpath:"..\..\libraries\BugslayerUtil\lib\\" /libpath:"..\..\libraries\Vdfs\lib" /libpath:"..\..\libraries\mallocwin32debug\lib\\" /libpath:"..\..\libraries\S3tc\lib\\" /fixed:no /release

!ELSEIF  "$(CFG)" == "Spacer2 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /Zp4 /MDd /W3 /GR /GX /Zi /Od /I ".\res\\" /I ".\_bert\\" /I ".\_carsten\\" /I "..\..\libraries\Miles\inc\\" /I "..\..\libraries\Vdfs\inc\\" /I "..\..\libraries\Glide\inc\\" /I "..\..\libraries\Bink\inc\\" /I "..\ZenGin\_kurt\\" /I ".\_andre\\" /I "..\ZenGin\res" /I "..\ZenGin\_andre\\" /I "..\ZenGin\_bert\\" /I "..\ZenGin\_carsten\\" /I "..\ZenGin\_dieter\\" /I "..\ZenGin\_ulf\\" /I "..\ZenGin\_roman\\" /I "..\ZenGin\_manuel" /I "..\Gothic\_manuel" /I "..\Gothic\_andre\\" /I "..\Gothic\_bert\\" /I "..\Gothic\_roman\\" /I "..\Gothic\_carsten\\" /I "..\Gothic\_ulf\\" /I "..\Gothic\_kurt\\" /I "..\..\libraries\DirectX\inc\\" /I "..\..\libraries\BugslayerUtil\inc\\" /I "..\ZenGin\\" /I "..\..\libraries\cj60\inc\\" /I "..\..\libraries\S3tc\inc\\" /D "COMPILING_GOTHIC" /D "COMPILING_SPACER" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MFC" /D "_ZERROR" /D "_WIN32" /D "_AFXDLL" /D "NONET" /D "LANG_DEU" /FD /I /Zm700 /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /i "Res/" /d "_DEBUG" /d "_AFXDLL" /d "COMPILING_SPACER" /d "LANG_DEU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wsock32.lib winmm.lib /nologo /stack:0x800000 /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /out:"..\..\binaries\_work\tools\Spacer\Spacer2-dbg.exe" /libpath:"..\..\libraries\Miles\lib\win" /libpath:"..\..\libraries\BugslayerUtil\lib" /libpath:"..\..\libraries\Vdfs\lib" /libpath:"..\..\libraries\mallocwin32debug\lib\\" /libpath:"..\..\libraries\S3tc\lib\\"
# SUBTRACT LINK32 /pdb:none /incremental:no /map

!ELSEIF  "$(CFG)" == "Spacer2 - Win32 Goldmaster"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Spacer2___Win32_Goldmaster"
# PROP BASE Intermediate_Dir "Spacer2___Win32_Goldmaster"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "goldmaster"
# PROP Intermediate_Dir "goldmaster"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /Zp4 /MT /W3 /GR /GX /Zd /O2 /Ob2 /I ".\res\\" /I ".\_bert\\" /I ".\_carsten\\" /I "..\..\libraries\Miles\inc\\" /I "..\..\libraries\Vdfs\inc\\" /I "..\..\libraries\Glide\inc\\" /I "..\..\libraries\Bink\inc\\" /I "..\ZenGin\_kurt\\" /I ".\_andre\\" /I "..\ZenGin\res" /I "..\ZenGin\_andre\\" /I "..\ZenGin\_bert\\" /I "..\ZenGin\_carsten\\" /I "..\ZenGin\_dieter\\" /I "..\ZenGin\_manuel\\" /I "..\Gothic\_manuel\\" /I "..\ZenGin\_ulf\\" /I "..\ZenGin\_roman\\" /I "..\Gothic\_andre\\" /I "..\Gothic\_bert\\" /I "..\Gothic\_roman\\" /I "..\Gothic\_carsten\\" /I "..\Gothic\_ulf\\" /I "..\Gothic\_kurt\\" /I "..\..\libraries\DirectX\inc\\" /I "..\..\libraries\BugslayerUtil\inc\\" /I "..\ZenGin\\" /I "..\..\libraries\cj60\inc\\" /I "..\..\libraries\S3tc\inc\\" /D "COMPILING_GOTHIC" /D "COMPILING_SPACER" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "_MFC" /D "_ZERROR" /D "_SPACER" /D "NONET" /D "LANG_DEU" /D "_VDFS" /D "GOTHIC_MODKIT" /Fr /FD /Zm700 /c
# ADD CPP /nologo /G6 /Zp4 /MT /W3 /GR /GX /Zd /O2 /Ob2 /I ".\res\\" /I ".\_bert\\" /I ".\_carsten\\" /I "..\..\libraries\Miles\inc\\" /I "..\..\libraries\Vdfs\inc\\" /I "..\..\libraries\Glide\inc\\" /I "..\..\libraries\Bink\inc\\" /I "..\ZenGin\_kurt\\" /I ".\_andre\\" /I "..\ZenGin\res" /I "..\ZenGin\_andre\\" /I "..\ZenGin\_bert\\" /I "..\ZenGin\_carsten\\" /I "..\ZenGin\_dieter\\" /I "..\ZenGin\_manuel\\" /I "..\Gothic\_manuel\\" /I "..\ZenGin\_ulf\\" /I "..\ZenGin\_roman\\" /I "..\Gothic\_andre\\" /I "..\Gothic\_bert\\" /I "..\Gothic\_roman\\" /I "..\Gothic\_carsten\\" /I "..\Gothic\_ulf\\" /I "..\Gothic\_kurt\\" /I "..\..\libraries\DirectX\inc\\" /I "..\..\libraries\BugslayerUtil\inc\\" /I "..\ZenGin\\" /I "..\..\libraries\cj60\inc\\" /I "..\..\libraries\S3tc\inc\\" /I "..\..\libraries\SecuROM\inc" /D "COMPILING_GOTHIC" /D "COMPILING_SPACER" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "_MFC" /D "_ZERROR" /D "_SPACER" /D "NONET" /D "LANG_DEU" /D "_VDFS" /D "GOTHIC_MODKIT" /D "GOLDMASTER" /FAs /FD /Zm700 /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /i "Res/" /d "NDEBUG" /d "COMPILING_SPACER" /d "LANG_DEU" /d "GOTHIC_MODKIT"
# ADD RSC /l 0x407 /i "Res/" /d "NDEBUG" /d "COMPILING_SPACER" /d "LANG_DEU" /d "GOTHIC_MODKIT" /d "GOLDMASTER"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wsock32.lib winmm.lib /nologo /stack:0x800000 /subsystem:windows /pdb:none /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrtd.lib" /force /out:"..\..\binaries\System\Spacer2.exe" /libpath:"..\..\libraries\Miles\lib\win" /libpath:"..\..\libraries\BugslayerUtil\lib\\" /libpath:"..\..\libraries\Vdfs\lib" /libpath:"..\..\libraries\mallocwin32debug\lib\\" /libpath:"..\..\libraries\S3tc\lib\\" /fixed:no /release
# ADD LINK32 wsock32.lib winmm.lib /nologo /stack:0x800000 /subsystem:windows /pdb:none /map /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrtd.lib" /nodefaultlib:"afxmem.obj" /force /out:"..\..\binaries\System\Spacer2-gold.exe" /libpath:"..\..\libraries\Miles\lib\win" /libpath:"..\..\libraries\BugslayerUtil\lib\\" /libpath:"..\..\libraries\Vdfs\lib" /libpath:"..\..\libraries\mallocwin32debug\lib\\" /libpath:"..\..\libraries\S3tc\lib\\" /fixed:no /release

!ENDIF 

# Begin Target

# Name "Spacer2 - Win32 Release"
# Name "Spacer2 - Win32 Debug"
# Name "Spacer2 - Win32 Goldmaster"
# Begin Group "Spacer"

# PROP Default_Filter ""
# Begin Group "Andre"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_andre\MsgMetaInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCCsDebugger.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCCsSequencer.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCCsSequencer.h
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCCsSettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCCsSettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCDiagramDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCDiagramDraw.h
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCDiagramVp.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCDiagramVp.h
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCDiagramVpD.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCDiagramVpD.h
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCList_Ou.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCList_Ou.h
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCTrackCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\_andre\spcCTrackCtrl.h
# End Source File
# End Group
# Begin Group "Bert"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_bert\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\_bert\Spacer.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\Spacer.h
# End Source File
# Begin Source File

SOURCE=.\_bert\SpacerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\SpacerDoc.h
# End Source File
# Begin Source File

SOURCE=.\_bert\SpacerView.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\SpacerView.h
# End Source File
# Begin Source File

SOURCE=.\_bert\Spc_ParseTools.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\Spc_ParseTools.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCBBoxDefineDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCBBoxDefineDlg.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCClassInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCClassInfo.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCColorListbox.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCColorListbox.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCCompileAction.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCCompileLightDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCCompileLightDlg.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCCompileWorldDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCCompileWorldDlg.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCConfiguration.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCConfiguration.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCConsoleDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCConsoleDialog.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCDibSection.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCDibSection.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCDragVob.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCDragVob.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCHelpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCHelpDlg.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfoBar.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfoBar.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Camera.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Camera.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Events.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Events.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Lights.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Lights.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Materials.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Materials.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Scripts.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Scripts.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Sounds.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Sounds.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Specials.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Specials.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Vertex.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Vertex.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Vobs.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobar_Vobs.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobarVobsPlus.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInfobarVobsPlus.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInputDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCInputDialog.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCList_Materials.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCList_Materials.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCList_Vobs.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCList_Vobs.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCMacroDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCMacroDlg.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCMatListbox.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCMatListbox.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCMessageDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCMessageDialog.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCNewMaterialDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCNewMaterialDialog.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectBar.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectBar.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectCreationPage.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectCreationPage.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectManipulatePage.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectManipulatePage.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectModifyPage.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectModifyPage.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectScriptedDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectScriptedDlg.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectSheet.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectSoundDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjectSoundDialog.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjPreset.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjPreset.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjPropList.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCObjPropList.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCParticleControl.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCParticleControl.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCPositionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCPositionDlg.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCScriptTool.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCScriptTool.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCScriptWizard.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCScriptWizard.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCSetGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCSetGeneral.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCSetView.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCSetView.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCTextInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCTextInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCViewProgressbar.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCViewProgressbar.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCVobContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCVobContainer.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCVobListDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCVobListDialog.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCVobLogicalDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCVobLogicalDialog.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCVobPropertyDialog.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCVobTreeItemList.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCVobTreeItemList.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCWindowResizeStyle.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCWindowResizeStyle.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCWorkInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCWorkInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCWorkProgressDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCWorkProgressDlg.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCWorldAnalyseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcCWorldAnalyseDlg.h
# End Source File
# Begin Source File

SOURCE=.\_bert\spcMatCalc.inc
# End Source File
# Begin Source File

SOURCE=.\_bert\spcMoving.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\spcMoving.h
# End Source File
# Begin Source File

SOURCE=.\_bert\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\_bert\StdAfx.h
# End Source File
# End Group
# End Group
# Begin Group "Game"

# PROP Default_Filter ""
# Begin Group "Andre Nr. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Gothic\_andre\oCsManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_andre\oCsManager.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_andre\oCsPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_andre\oCsPlayer.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_andre\oCsProps.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_andre\oCsProps.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_andre\oCsTrigger.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_andre\oCsTrigger.h
# End Source File
# End Group
# Begin Group "Bert Nr. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Gothic\_bert\oBinkPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oBinkPlayer.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oGameInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oGameInfo.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oGameManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oGameManager.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oMenu_Tools.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oMenu_Tools.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oMenuSavegame.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oMenuSavegame.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\ooBert.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\ooBert.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oPlayerInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oPlayerInfo.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oSavegame.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oSavegame.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oSysInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oSysInfo.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oTrigger.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oTrigger.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oViewProgressbar.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oViewProgressbar.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oViewStatusbar.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_bert\oViewStatusbar.h
# End Source File
# End Group
# Begin Group "Carsten"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Gothic\_carsten\oAiHuman_Magic.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oMagFrontier.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oMagFrontier.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oMagic.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oMenu_Main.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oMenu_Main.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oMenu_Status.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oMenu_Status.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\ooCarsten.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\ooCarsten.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oSpell.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oVisFx.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oVisFx_Edit.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oVisFx_MultiTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oVisFx_MultiTarget.h
# End Source File
# End Group
# Begin Group "Dieter"

# PROP Default_Filter ""
# End Group
# Begin Group "Kurt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Gothic\_kurt\oMusicZone.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_kurt\oMusicZone.h
# End Source File
# End Group
# Begin Group "Manuel"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Gothic\_manuel\oCollisionObjectMiscChar.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_manuel\oCollisionObjectMiscChar.h
# End Source File
# End Group
# Begin Group "Roman"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Gothic\_roman\oDamage.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oDamage.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oDocumentManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oDocumentManager.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oIncDialogs.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oIncViews.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oInformationManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oInformationManager.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oLogManager.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oNpc_Damage.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oNpc_Damage.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oNpc_Fight.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oNPC_Fight.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oNpc_Move.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oNPC_Move.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDialogInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDialogInventory.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDialogItem.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDialogItem.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDialogItemContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDialogItemContainer.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDialogStealContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDialogTrade.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDialogTrade.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDocument.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDocumentMap.h
# End Source File
# End Group
# Begin Group "Ulf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Gothic\_ulf\oAiHuman.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oAiHuman.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oAiShoot.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oAiShoot.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oAniCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oAniCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oBarrier.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oBarrier.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oDialog.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oDoc.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oDoc.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oFocus.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oFocus.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oGame.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oGame.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oGameExternal.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oGameKeys.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oGuilds.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oGuilds.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oHelp.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oHelp.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oInfo.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oInventory.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oInventory.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oItem.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oItem.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oItemReact.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oItemReact.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oMagic.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oMission.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oMission.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oMobInter.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oMobInter.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oNews.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oNews.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oNpc.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oNpc.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oNpcInv.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oNpcMessages.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oNpcMessages.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oNpcStates.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oNpcStates.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oObjFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oObjFactory.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\ooUlfi.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oParticleControl.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oParticleControl.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oPortals.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oPortals.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oRoutine.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oRoutine.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oSpawn.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oSpawn.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oSpell.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oSvm.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oSvm.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oText.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oText.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oVisFx.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_carsten\oVisFx_Edit.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oVob.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oVob.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oWaynet.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oWaynet.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oWorld.cpp
# End Source File
# Begin Source File

SOURCE=..\Gothic\_ulf\oWorld.h
# End Source File
# End Group
# End Group
# Begin Group "Engine"

# PROP Default_Filter ""
# Begin Group "Andre Nr. 2"

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
# Begin Group "Bert Nr. 2"

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
# Begin Group "Carsten Nr. 1"

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

SOURCE=..\ZenGin\_carsten\zCpuSpecs.cpp
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

SOURCE=..\ZenGin\_carsten\zList2.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMathTools.cpp
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
# Begin Group "Dieter Nr. 1"

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

SOURCE=..\ZenGin\_dieter\zCollisionMiscExtra.cpp
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

SOURCE=..\ZenGin\_carsten\zKbSplines.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zLensflare.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zLensflare.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_ulf\zList.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMaterial.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_dieter\zMaterial.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_carsten\zMathTools.h
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
# Begin Group "Kurt Nr. 1"

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
# Begin Group "Manuel Nr. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ZenGin\_manuel\zAccount.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\_manuel\zAccount.h
# End Source File
# End Group
# Begin Group "Roman Nr. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Gothic\_roman\oLogManager.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDialogStealContainer.h
# End Source File
# Begin Source File

SOURCE=..\Gothic\_roman\oViewDocumentMap.cpp
# End Source File
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
# Begin Group "Ulf Nr. 1"

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
# Begin Source File

SOURCE=..\ZenGin\zLocal.cpp
# End Source File
# Begin Source File

SOURCE=..\ZenGin\zLocal.h
# End Source File
# End Group
# Begin Group "Libraries"

# PROP Default_Filter ""
# Begin Group "Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\libraries\BugslayerUtil\inc\BaseTsd.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\Bink\inc\Bink.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\d3dx.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\d3dxcore.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\d3dxerr.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\d3dxmath.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\d3dxmath.inl
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\d3dxshapes.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\d3dxsprite.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\dls1.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\dmdls.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\dmerror.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\dmksctrl.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\dmusbuff.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\dmusicc.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\inc\Dmusici.h
# End Source File
# Begin Source File

SOURCE=..\..\libraries\Miles\inc\Mss.h
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
# End Group
# Begin Source File

SOURCE=..\..\libraries\BugslayerUtil\lib\BugslayerUtil.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\lib\dxguid.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\lib\d3dx.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\lib\ddraw.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\lib\dsound.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\S3tc\lib\S3tc.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\Miles\lib\Mss32.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\MallocWin32Debug\lib\MallocWin32Debug.lib

!IF  "$(CFG)" == "Spacer2 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Spacer2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Spacer2 - Win32 Goldmaster"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\libraries\Bink\lib\BinkW32.lib
# End Source File
# Begin Source File

SOURCE=..\..\libraries\DirectX\lib\dinput.lib
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Group "ZenGin"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ZenGin\res\resource.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\res\zWin32_Resource.h
# End Source File
# Begin Source File

SOURCE=..\ZenGin\res\zWin32_Version.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\Icons_VobList.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Icons_VobProps.bmp
# End Source File
# Begin Source File

SOURCE=.\_bert\resource.h
# End Source File
# Begin Source File

SOURCE=.\res\Spacer.ico
# End Source File
# Begin Source File

SOURCE=.\_bert\Spacer.rc
# End Source File
# Begin Source File

SOURCE=.\res\Spacer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Spacer2.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\res\SpacerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar_Material.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar_Objects.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar_Pages.bmp
# End Source File
# End Group
# End Target
# End Project
# Section Spacer : {99FF4676-FFC3-11D0-BD02-00C04FC2FB86}
# 	2:5:Class:spcCStdDataFormatsDisp
# 	2:10:HeaderFile:gridcontrol\spcStdDataFormatsDisp.h
# 	2:8:ImplFile:gridcontrol\spcStdDataFormatsDisp.cpp
# End Section
# Section Spacer : {CDE57A4F-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:spcCColumn
# 	2:10:HeaderFile:gridcontrol\spcColumn.h
# 	2:8:ImplFile:gridcontrol\spcColumn.cpp
# End Section
# Section Spacer : {CDE57A53-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:spcCSplits
# 	2:10:HeaderFile:gridcontrol\spcSplits.h
# 	2:8:ImplFile:gridcontrol\spcSplits.cpp
# End Section
# Section Spacer : {CDE57A43-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:21:DefaultSinkHeaderFile:gridcontrol\spcDataGrid.h
# 	2:16:DefaultSinkClass:spcCDataGrid
# End Section
# Section Spacer : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:spcCOleFont
# 	2:10:HeaderFile:gridcontrol\spcFont.h
# 	2:8:ImplFile:gridcontrol\spcFont.cpp
# End Section
# Section Spacer : {8856F961-340A-11D0-A96B-00C04FD705A2}
# 	2:21:DefaultSinkHeaderFile:spcWebBrowser.h
# 	2:16:DefaultSinkClass:CWebBrowser
# End Section
# Section Spacer : {CDE57A52-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:spcCSelBookmarks
# 	2:10:HeaderFile:gridcontrol\spcSelBookmarks.h
# 	2:8:ImplFile:gridcontrol\spcSelBookmarks.cpp
# End Section
# Section Spacer : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:spcCPicture
# 	2:10:HeaderFile:gridcontrol\spcPicture.h
# 	2:8:ImplFile:gridcontrol\spcPicture.cpp
# End Section
# Section Spacer : {CDE57A41-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:spcCDataGrid
# 	2:10:HeaderFile:gridcontrol\spcDataGrid.h
# 	2:8:ImplFile:gridcontrol\spcDataGrid.cpp
# End Section
# Section Spacer : {CDE57A50-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:spcCColumns
# 	2:10:HeaderFile:gridcontrol\spcColumns.h
# 	2:8:ImplFile:gridcontrol\spcColumns.cpp
# End Section
# Section Spacer : {E675F3F0-91B5-11D0-9484-00A0C91110ED}
# 	2:5:Class:spcCDataFormatDisp
# 	2:10:HeaderFile:gridcontrol\spcDataFormatDisp.h
# 	2:8:ImplFile:gridcontrol\spcDataFormatDisp.cpp
# End Section
# Section Spacer : {CDE57A54-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:spcCSplit
# 	2:10:HeaderFile:gridcontrol\spcSplit.h
# 	2:8:ImplFile:gridcontrol\spcSplit.cpp
# End Section
# Section Spacer : {D30C1661-CDAF-11D0-8A3E-00C04FC9E26E}
# 	2:5:Class:CWebBrowser
# 	2:10:HeaderFile:spcWebBrowser.h
# 	2:8:ImplFile:spcWebBrowser.cpp
# End Section
