# Microsoft Developer Studio Project File - Name="VdfsInit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VdfsInit - Win32 German
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "VdfsInit.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "VdfsInit.mak" CFG="VdfsInit - Win32 German"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "VdfsInit - Win32 German" (basierend auf  "Win32 (x86) Application")
!MESSAGE "VdfsInit - Win32 English" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/release/tools/VdfsInit", SYCAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VdfsInit - Win32 German"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VdfsInit___Win32_German"
# PROP BASE Intermediate_Dir "VdfsInit___Win32_German"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "german"
# PROP Intermediate_Dir "german"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /MT /W4 /O1 /I ".\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "LANG_DEU" /FR /FD /c
# ADD CPP /nologo /G6 /Zp1 /W4 /O1 /I ".\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "LANG_DEU" /FD /c
# SUBTRACT CPP /u /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "LANG_DEU"
# ADD RSC /l 0x407 /d "NDEBUG" /d "LANG_DEU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib comctl32.lib /nologo /version:4.0 /subsystem:windows /machine:I386 /out:"..\..\..\binaries\System\Vdfs32g.exe" /libpath:".\lib" /release
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib comctl32.lib Vdfs32g.lib p:\vs6\VC98\CRT\SRC\Intel\St_lib\ChkStk.obj /nologo /version:4.0 /entry:"WinMain" /subsystem:windows /pdb:none /machine:I386 /nodefaultlib /out:"..\..\..\binaries\System\Vdfs32g.exe" /libpath:".\lib" /release

!ELSEIF  "$(CFG)" == "VdfsInit - Win32 English"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VdfsInit___Win32_English"
# PROP BASE Intermediate_Dir "VdfsInit___Win32_English"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "english"
# PROP Intermediate_Dir "english"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /MT /W4 /O1 /I ".\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "LANG_DEU" /FR /FD /c
# ADD CPP /nologo /G6 /Zp1 /W4 /O1 /I ".\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "LANG_ENU" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "LANG_DEU"
# ADD RSC /l 0x409 /d "NDEBUG" /d "LANG_ENU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib comctl32.lib /nologo /version:4.0 /subsystem:windows /machine:I386 /out:"..\..\..\binaries\System\Vdfs32g.exe" /libpath:".\lib" /release
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib comctl32.lib Vdfs32e.lib p:\vs6\VC98\CRT\SRC\Intel\St_lib\ChkStk.obj /nologo /version:4.0 /entry:"WinMain" /subsystem:windows /pdb:none /machine:I386 /nodefaultlib /out:"..\..\..\binaries\System\Vdfs32e.exe" /libpath:".\lib" /release

!ENDIF 

# Begin Target

# Name "VdfsInit - Win32 German"
# Name "VdfsInit - Win32 English"
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\resource.rc
# End Source File
# Begin Source File

SOURCE=.\res\VdfsInit.ico
# End Source File
# Begin Source File

SOURCE=.\res\VdfsInit.manifest
# End Source File
# End Group
# Begin Source File

SOURCE=.\VdfsInit.cpp
# End Source File
# End Target
# End Project
