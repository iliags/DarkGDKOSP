# Microsoft Developer Studio Project File - Name="DBDLLCore" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DBDLLCore - Win32 Debug_FPSC
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DBDLLCore.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DBDLLCore.mak" CFG="DBDLLCore - Win32 Debug_FPSC"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DBDLLCore - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DBDLLCore - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DBDLLCore - Win32 Debug_FPSC" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DBDLLCore - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DBDLLCORE_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DBDLLCORE_EXPORTS" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /machine:I386 /out:"..\..\..\Dark Basic Pro\Compiler\plugins\DBProCore.dll"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "DBDLLCore - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DBDLLCORE_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DBDLLCORE_EXPORTS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /debug /machine:I386 /out:"..\..\..\Dark Basic Pro\Compiler\plugins\DBProCore.dll" /pdbtype:sept

!ELSEIF  "$(CFG)" == "DBDLLCore - Win32 Debug_FPSC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DBDLLCore___Win32_Debug_FPSC"
# PROP BASE Intermediate_Dir "DBDLLCore___Win32_Debug_FPSC"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DBDLLCore___Win32_Debug_FPSC"
# PROP Intermediate_Dir "DBDLLCore___Win32_Debug_FPSC"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DBDLLCORE_EXPORTS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DBDLLCORE_EXPORTS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /debug /machine:I386 /out:"..\..\..\Dark Basic Pro\Compiler\plugins\DBProCore.dll" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /debug /machine:I386 /out:"..\..\..\Dark Basic Pro\Compiler\plugins\DBProCore.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DBDLLCore - Win32 Release"
# Name "DBDLLCore - Win32 Debug"
# Name "DBDLLCore - Win32 Debug_FPSC"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLCore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLCoreInternal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLDisplay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLEXT.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLExtCalls.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLGDI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\globstruct.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLCore.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLCoreInternal.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLDisplay.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLEXT.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLExtCalls.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\DBDLLGDI.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Core\globstruct.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\gfx\icon.bmp
# End Source File
# End Group
# Begin Group "Encryptor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\DBPCompiler\Encryptor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\DBPCompiler\Encryptor.h
# End Source File
# End Group
# Begin Group "Error"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Shared\Error\CError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Error\CError.h
# End Source File
# Begin Source File

SOURCE=..\..\Shared\Error\CRuntimeErrors.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DBDLLCore.rc
# End Source File
# End Target
# End Project
