# Microsoft Developer Studio Project File - Name="GameServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GameServer - Win32 JPN
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GameServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GameServer.mak" CFG="GameServer - Win32 JPN"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GameServer - Win32 KOR" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 KORCS" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 ENG" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 ENGCS" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 JPN" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 JPNCS" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 CHS" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 CHSCS" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 TAI" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 TAICS" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 PHI" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 PHICS" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 VTM" (based on "Win32 (x86) Application")
!MESSAGE "GameServer - Win32 VTMCS" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GameServer - Win32 KOR"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_KOR"
# PROP BASE Intermediate_Dir "GameServer___Win32_KOR"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_KOR"
# PROP Intermediate_Dir "GameServer___Win32_KOR"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_KOREAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_KOREAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib  /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 KORCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_KORCS"
# PROP BASE Intermediate_Dir "GameServer___Win32_KORCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_KORCS"
# PROP Intermediate_Dir "GameServer___Win32_KORCS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_KOREAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_KOREAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 JPN"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_JPN"
# PROP BASE Intermediate_Dir "GameServer___Win32_JPN"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_JPN"
# PROP Intermediate_Dir "GameServer___Win32_JPN"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_JAPAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_JAPAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 JPNCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_JPNCS"
# PROP BASE Intermediate_Dir "GameServer___Win32_JPNCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_JPNCS"
# PROP Intermediate_Dir "GameServer___Win32_JPNCS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_JAPAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_JAPAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 ENG"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_ENG"
# PROP BASE Intermediate_Dir "GameServer___Win32_ENG"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_ENG"
# PROP Intermediate_Dir "GameServer___Win32_ENG"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_ENGLISH" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_ENGLISH" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 ENGCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_ENGCS"
# PROP BASE Intermediate_Dir "GameServer___Win32_ENGCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_ENGCS"
# PROP Intermediate_Dir "GameServer___Win32_ENGCS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_ENGLISH" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_ENGLISH" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 CHS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_CHS"
# PROP BASE Intermediate_Dir "GameServer___Win32_CHS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_CHS"
# PROP Intermediate_Dir "GameServer___Win32_CHS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_CHINA" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_CHINA" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 CHSCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_CHSCS"
# PROP BASE Intermediate_Dir "GameServer___Win32_CHSCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_CHSCS"
# PROP Intermediate_Dir "GameServer___Win32_CHSCS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_CHINA" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_CHINA" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 TAI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_TAI"
# PROP BASE Intermediate_Dir "GameServer___Win32_TAI"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_TAI"
# PROP Intermediate_Dir "GameServer___Win32_TAI"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_TAIWAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_TAIWAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 TAICS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_TAICS"
# PROP BASE Intermediate_Dir "GameServer___Win32_TAICS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_TAICS"
# PROP Intermediate_Dir "GameServer___Win32_TAICS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_TAIWAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_TAIWAN" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 PHI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_PHI"
# PROP BASE Intermediate_Dir "GameServer___Win32_PHI"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_PHI"
# PROP Intermediate_Dir "GameServer___Win32_PHI"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_PHILIPPINES" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_PHILIPPINES" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 PHICS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_PHICS"
# PROP BASE Intermediate_Dir "GameServer___Win32_PHICS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_PHICS"
# PROP Intermediate_Dir "GameServer___Win32_PHICS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_PHILIPPINES" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_PHILIPPINES" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 VTM"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_VTM"
# PROP BASE Intermediate_Dir "GameServer___Win32_VTM"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_VTM"
# PROP Intermediate_Dir "GameServer___Win32_VTM"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_VIETNAM" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "INTERNATIONAL_VIETNAM" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "GameServer - Win32 VTMCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameServer___Win32_VTMCS"
# PROP BASE Intermediate_Dir "GameServer___Win32_VTMCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "GameServer___Win32_VTMCS"
# PROP Intermediate_Dir "GameServer___Win32_VTMCS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_VIETNAM" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "GS_CASTLE" /D "INTERNATIONAL_VIETNAM" /FAcs /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x280a /d "_DEBUG"
# ADD RSC /l 0x280a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mumsg.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"LIBC" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "GameServer - Win32 KOR"
# Name "GameServer - Win32 KORCS"
# Name "GameServer - Win32 JPN"
# Name "GameServer - Win32 JPNCS"
# Name "GameServer - Win32 ENG"
# Name "GameServer - Win32 ENGCS"
# Name "GameServer - Win32 CHS"
# Name "GameServer - Win32 CHSCS"
# Name "GameServer - Win32 TAI"
# Name "GameServer - Win32 TAICS"
# Name "GameServer - Win32 PHI"
# Name "GameServer - Win32 PHICS"
# Name "GameServer - Win32 VTM"
# Name "GameServer - Win32 VTMCS"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MonsterHerd.cpp
# End Source File
# Begin Source File

SOURCE=.\KalimaGate.cpp
# End Source File
# Begin Source File

SOURCE=.\gObjMonster.cpp
# End Source File
# Begin Source File

SOURCE=.\MonsterAttr.cpp
# End Source File
# Begin Source File

SOURCE=.\MonsterItemMng.cpp
# End Source File
# Begin Source File

SOURCE=.\MonsterSetBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSave.cpp
# End Source File
# Begin Source File

SOURCE=.\DBSockMng.cpp
# End Source File
# Begin Source File

SOURCE=.\DSProtocol.cpp
# End Source File
# Begin Source File

SOURCE=.\SProtocol.cpp
# End Source File
# Begin Source File

SOURCE=.\protocol.cpp
# End Source File
# Begin Source File

SOURCE=.\EDSProtocol.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiAttackHackCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\NSerialCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\PacketCheckSum.cpp
# End Source File
# Begin Source File

SOURCE=.\HackToolPacket.cpp
# End Source File
# Begin Source File

SOURCE=.\TDurMagicKeyChecker.cpp
# End Source File
# Begin Source File

SOURCE=.\ChinaHackUserKick.cpp
# End Source File
# Begin Source File

SOURCE=.\SendHackLog.cpp
# End Source File
# Begin Source File

SOURCE=.\DevilSquare.cpp
# End Source File
# Begin Source File

SOURCE=.\DevilSquareGround.cpp
# End Source File
# Begin Source File

SOURCE=.\BattleGround.cpp
# End Source File
# Begin Source File

SOURCE=.\BattleSoccer.cpp
# End Source File
# Begin Source File

SOURCE=.\BattleSoccerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\DragonEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\AttackEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\EledoradoEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\RingAttackEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\WTEventItemList.cpp
# End Source File
# Begin Source File

SOURCE=.\CastleDeepEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\PCBangPointSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\GambleSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\XMasAttackEventData.cpp
# End Source File
# Begin Source File

SOURCE=.\Event.cpp
# End Source File
# Begin Source File

SOURCE=.\EventManagement.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemBag.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemBagEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ProbabilityItemBag.cpp
# End Source File
# Begin Source File

SOURCE=.\XMasAttackEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicDamage.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicInf.cpp
# End Source File
# Begin Source File

SOURCE=.\SkillAdditionInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\SkillDelay.cpp
# End Source File
# Begin Source File

SOURCE=.\SkillHitBox.cpp
# End Source File
# Begin Source File

SOURCE=.\QuestInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\QuestUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\wsGameServer.cpp
# End Source File
# Begin Source File

SOURCE=.\WzMultiCastSock.cpp
# End Source File
# Begin Source File

SOURCE=.\giocp.cpp
# End Source File
# Begin Source File

SOURCE=..\common\MyWinsockBase.cpp
# End Source File
# Begin Source File

SOURCE=.\wsJoinServerCli.cpp
# End Source File
# Begin Source File

SOURCE=.\WzQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\WzUdp.cpp
# End Source File
# Begin Source File

SOURCE=.\MapClass.cpp
# End Source File
# Begin Source File

SOURCE=.\MapItem.cpp
# End Source File
# Begin Source File

SOURCE=.\AcceptIp.cpp
# End Source File
# Begin Source File

SOURCE=.\CLoginCount.cpp
# End Source File
# Begin Source File

SOURCE=.\ClosePlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\ConMember.cpp
# End Source File
# Begin Source File

SOURCE=.\IpCache.cpp
# End Source File
# Begin Source File

SOURCE=.\DirPath.cpp
# End Source File
# Begin Source File

SOURCE=.\logproc.cpp
# End Source File
# Begin Source File

SOURCE=.\LogToFile.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveCheck.cpp
# End Source File
# Begin Source File

SOURCE=..\common\winutil.cpp
# End Source File
# Begin Source File

SOURCE=.\WhisperCash.cpp
# End Source File
# Begin Source File

SOURCE=.\zzzmathlib.cpp
# End Source File
# Begin Source File

SOURCE=..\common\WZScriptEncode.cpp
# End Source File
# Begin Source File

SOURCE=.\CWhatsUpDummyServer.cpp
# End Source File
# Begin Source File

SOURCE=.\TNotice.cpp
# End Source File
# Begin Source File

SOURCE=.\TStatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\CallStackTrace.cpp
# End Source File
# Begin Source File

SOURCE=.\TServerAlertManager.cpp
# End Source File
# Begin Source File

SOURCE=.\TServerInfoDisplayer.cpp
# End Source File
# Begin Source File

SOURCE=.\MiniDump.cpp
# End Source File
# Begin Source File

SOURCE=.\PartyClass.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildClass.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewportGuild.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjBaseAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjUseSkill.cpp
# End Source File
# Begin Source File

SOURCE=..\common\classdef.cpp
# End Source File
# Begin Source File

SOURCE=.\StatMng.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjCalCharacter.cpp
# End Source File
# Begin Source File

SOURCE=.\DarkSpirit.cpp
# End Source File
# Begin Source File

SOURCE=.\TUnion.cpp
# End Source File
# Begin Source File

SOURCE=.\TUnionInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MasterLevelSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\MasterSkillSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\user.cpp
# End Source File
# Begin Source File

SOURCE=.\SocketData.cpp
# End Source File
# Begin Source File

SOURCE=.\SocketOption.cpp
# End Source File
# Begin Source File

SOURCE=.\SocketSphere.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemAddOption.cpp
# End Source File
# Begin Source File

SOURCE=.\JewelMixSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\common\SetItemOption.cpp
# End Source File
# Begin Source File

SOURCE=..\common\zzzitem.cpp
# End Source File
# Begin Source File

SOURCE=.\Shop.cpp
# End Source File
# Begin Source File

SOURCE=.\CCastleEventItemList.cpp
# End Source File
# Begin Source File

SOURCE=.\GMMng.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\SetItemMacro.cpp
# End Source File
# Begin Source File

SOURCE=.\GameMain.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\GameServer.cpp
# End Source File
# Begin Source File

SOURCE=.\Gate.cpp
# End Source File
# Begin Source File

SOURCE=.\BloodCastle.cpp
# End Source File
# Begin Source File

SOURCE=.\ChaosCastle.cpp
# End Source File
# Begin Source File

SOURCE=.\ChaosCastleSetItemDrop.cpp
# End Source File
# Begin Source File

SOURCE=.\CannonTower.cpp
# End Source File
# Begin Source File

SOURCE=.\CastleCrown.cpp
# End Source File
# Begin Source File

SOURCE=.\CastleCrownSwitch.cpp
# End Source File
# Begin Source File

SOURCE=.\Guardian.cpp
# End Source File
# Begin Source File

SOURCE=.\GuardianStatue.cpp
# End Source File
# Begin Source File

SOURCE=.\LifeStone.cpp
# End Source File
# Begin Source File

SOURCE=.\Mercenary.cpp
# End Source File
# Begin Source File

SOURCE=.\Weapon.cpp
# End Source File
# Begin Source File

SOURCE=.\CastleSiege.cpp
# End Source File
# Begin Source File

SOURCE=.\CastleSiegeSync.cpp
# End Source File
# Begin Source File

SOURCE=.\MapServerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcTalk.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterSkillElement.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterSkillElementInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterSkillManager.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterSkillUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterAI.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIAgro.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIAutomata.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIElement.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIGroupMember.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIMovePath.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIRule.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIRuleInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\CrywolfAltar.cpp
# End Source File
# Begin Source File

SOURCE=.\CrywolfStatue.cpp
# End Source File
# Begin Source File

SOURCE=.\CrywolfDarkElf.cpp
# End Source File
# Begin Source File

SOURCE=.\CrywolfMonster.cpp
# End Source File
# Begin Source File

SOURCE=.\CrywolfTanker.cpp
# End Source File
# Begin Source File

SOURCE=.\Crywolf.cpp
# End Source File
# Begin Source File

SOURCE=.\CrywolfStateTimeInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CrywolfSync.cpp
# End Source File
# Begin Source File

SOURCE=.\CrywolfUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemSystemFor380.cpp
# End Source File
# Begin Source File

SOURCE=.\JewelOfHarmonySystem.cpp
# End Source File
# Begin Source File

SOURCE=.\TRandomPoolMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\KanturuMaya.cpp
# End Source File
# Begin Source File

SOURCE=.\KanturuMonsterMng.cpp
# End Source File
# Begin Source File

SOURCE=.\KanturuNightmare.cpp
# End Source File
# Begin Source File

SOURCE=.\KanturuBattleOfMaya.cpp
# End Source File
# Begin Source File

SOURCE=.\KanturuBattleOfNightmare.cpp
# End Source File
# Begin Source File

SOURCE=.\KanturuBattleStanby.cpp
# End Source File
# Begin Source File

SOURCE=.\KanturuTowerOfRefinement.cpp
# End Source File
# Begin Source File

SOURCE=.\KanturuBattleUserMng.cpp
# End Source File
# Begin Source File

SOURCE=.\KanturuEntranceNPC.cpp
# End Source File
# Begin Source File

SOURCE=.\Kanturu.cpp
# End Source File
# Begin Source File

SOURCE=.\KanturuStateInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\KanturuUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\IllusionTempleEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\IllusionTempleProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\MixSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\CashShop.cpp
# End Source File
# Begin Source File

SOURCE=.\wsShopServerCli.cpp
# End Source File
# Begin Source File

SOURCE=.\CashItemPeriodSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\CashLotterySystem.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewportSkillState.cpp
# End Source File
# Begin Source File

SOURCE=.\BuffManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BuffEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\RaklionSelupan.cpp
# End Source File
# Begin Source File

SOURCE=.\RaklionBattleOfSelupan.cpp
# End Source File
# Begin Source File

SOURCE=.\RaklionBattleUserMng.cpp
# End Source File
# Begin Source File

SOURCE=.\Raklion.cpp
# End Source File
# Begin Source File

SOURCE=.\RaklionUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\ChaosCard.cpp
# End Source File
# Begin Source File

SOURCE=.\GameEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\GameServer.rc
# End Source File
# Begin Source File

SOURCE=.\GameServerAuth.cpp
# End Source File
# Begin Source File

SOURCE=.\LargeRand.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiCheckSum.cpp
# End Source File
# Begin Source File

SOURCE=..\common\TSync.cpp
# End Source File
# Begin Source File

SOURCE=..\common\WzMemScript.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleModulus.lib
# End Source File
# Begin Source File

SOURCE=..\GGSvr\Release\GGSvr.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AcceptIp.h
# End Source File
# Begin Source File

SOURCE=.\AttackEvent.h
# End Source File
# Begin Source File

SOURCE=.\BattleGround.h
# End Source File
# Begin Source File

SOURCE=.\BattleSoccer.h
# End Source File
# Begin Source File

SOURCE=.\BattleSoccerManager.h
# End Source File
# Begin Source File

SOURCE=.\BloodCastle.h
# End Source File
# Begin Source File

SOURCE=.\CallStackTrace.h
# End Source File
# Begin Source File

SOURCE=.\CannonTower.h
# End Source File
# Begin Source File

SOURCE=.\CashItemPeriodSystem.h
# End Source File
# Begin Source File

SOURCE=.\CashLotterySystem.h
# End Source File
# Begin Source File

SOURCE=.\ViewportSkillState.h
# End Source File
# Begin Source File

SOURCE=.\BuffManager.h
# End Source File
# Begin Source File

SOURCE=.\BuffEffect.h
# End Source File
# Begin Source File

SOURCE=.\RaklionSelupan.h
# End Source File
# Begin Source File

SOURCE=.\RaklionBattleOfSelupan.h
# End Source File
# Begin Source File

SOURCE=.\RaklionBattleUserMng.h
# End Source File
# Begin Source File

SOURCE=.\Raklion.h
# End Source File
# Begin Source File

SOURCE=.\RaklionUtil.h
# End Source File
# Begin Source File

SOURCE=.\ChaosCard.h
# End Source File
# Begin Source File

SOURCE=.\CashShop.h
# End Source File
# Begin Source File

SOURCE=.\CastleDeepEvent.h
# End Source File
# Begin Source File

SOURCE=.\CastleCrown.h
# End Source File
# Begin Source File

SOURCE=.\CastleCrownSwitch.h
# End Source File
# Begin Source File

SOURCE=.\CCastleEventItemList.h
# End Source File
# Begin Source File

SOURCE=.\CastleSiege.h
# End Source File
# Begin Source File

SOURCE=.\CastleSiegeSync.h
# End Source File
# Begin Source File

SOURCE=.\MixSystem.h
# End Source File
# Begin Source File

SOURCE=.\ChaosCastle.h
# End Source File
# Begin Source File

SOURCE=.\ChaosCastleSetItemDrop.h
# End Source File
# Begin Source File

SOURCE=.\ChinaHackUserKick.h
# End Source File
# Begin Source File

SOURCE=..\common\classdef.h
# End Source File
# Begin Source File

SOURCE=.\CLoginCount.h
# End Source File
# Begin Source File

SOURCE=.\ClosePlayer.h
# End Source File
# Begin Source File

SOURCE=.\ComboAttack.h
# End Source File
# Begin Source File

SOURCE=.\ConMember.h
# End Source File
# Begin Source File

SOURCE=.\Crywolf.h
# End Source File
# Begin Source File

SOURCE=.\CrywolfAltar.h
# End Source File
# Begin Source File

SOURCE=.\CrywolfDarkElf.h
# End Source File
# Begin Source File

SOURCE=.\CrywolfMonster.h
# End Source File
# Begin Source File

SOURCE=.\CrywolfObjInfo.h
# End Source File
# Begin Source File

SOURCE=.\CrywolfStateTimeInfo.h
# End Source File
# Begin Source File

SOURCE=.\CrywolfStatue.h
# End Source File
# Begin Source File

SOURCE=.\CrywolfSync.h
# End Source File
# Begin Source File

SOURCE=.\CrywolfTanker.h
# End Source File
# Begin Source File

SOURCE=.\CrywolfUtil.h
# End Source File
# Begin Source File

SOURCE=.\CWhatsUpDummyServer.h
# End Source File
# Begin Source File

SOURCE=.\DarkSpirit.h
# End Source File
# Begin Source File

SOURCE=.\DbSave.h
# End Source File
# Begin Source File

SOURCE=.\DBSockMng.h
# End Source File
# Begin Source File

SOURCE=.\DevilSquare.h
# End Source File
# Begin Source File

SOURCE=.\DevilSquareGround.h
# End Source File
# Begin Source File

SOURCE=.\dirpath.h
# End Source File
# Begin Source File

SOURCE=.\DragonEvent.h
# End Source File
# Begin Source File

SOURCE=.\DSProtocol.h
# End Source File
# Begin Source File

SOURCE=.\EDSProtocol.h
# End Source File
# Begin Source File

SOURCE=.\EledoradoEvent.h
# End Source File
# Begin Source File

SOURCE=.\Event.h
# End Source File
# Begin Source File

SOURCE=.\EventManagement.h
# End Source File
# Begin Source File

SOURCE=.\GameEvent.h
# End Source File
# Begin Source File

SOURCE=.\GameMain.h
# End Source File
# Begin Source File

SOURCE=.\GameServer.h
# End Source File
# Begin Source File

SOURCE=.\GameServerAuth.h
# End Source File
# Begin Source File

SOURCE=.\Gate.h
# End Source File
# Begin Source File

SOURCE=.\giocp.h
# End Source File
# Begin Source File

SOURCE=.\GMMng.h
# End Source File
# Begin Source File

SOURCE=.\gObjMonster.h
# End Source File
# Begin Source File

SOURCE=.\Guardian.h
# End Source File
# Begin Source File

SOURCE=.\GuardianStatue.h
# End Source File
# Begin Source File

SOURCE=.\GuildClass.h
# End Source File
# Begin Source File

SOURCE=.\IpCache.h
# End Source File
# Begin Source File

SOURCE=.\ItemBag.h
# End Source File
# Begin Source File

SOURCE=.\ItemBagEx.h
# End Source File
# Begin Source File

SOURCE=.\ItemSystemFor380.h
# End Source File
# Begin Source File

SOURCE=.\JewelMixSystem.h
# End Source File
# Begin Source File

SOURCE=.\JewelOfHarmonySystem.h
# End Source File
# Begin Source File

SOURCE=.\KalimaGate.h
# End Source File
# Begin Source File

SOURCE=.\Kanturu.h
# End Source File
# Begin Source File

SOURCE=.\KanturuBattleOfMaya.h
# End Source File
# Begin Source File

SOURCE=.\KanturuBattleOfNightmare.h
# End Source File
# Begin Source File

SOURCE=.\KanturuBattleStanby.h
# End Source File
# Begin Source File

SOURCE=.\KanturuBattleUser.h
# End Source File
# Begin Source File

SOURCE=.\KanturuBattleUserMng.h
# End Source File
# Begin Source File

SOURCE=.\KanturuEntranceNPC.h
# End Source File
# Begin Source File

SOURCE=.\KanturuMaya.h
# End Source File
# Begin Source File

SOURCE=.\KanturuMonsterMng.h
# End Source File
# Begin Source File

SOURCE=.\KanturuNightmare.h
# End Source File
# Begin Source File

SOURCE=.\KanturuObjInfo.h
# End Source File
# Begin Source File

SOURCE=.\KanturuStateInfo.h
# End Source File
# Begin Source File

SOURCE=.\KanturuTowerOfRefinement.h
# End Source File
# Begin Source File

SOURCE=.\KanturuUtil.h
# End Source File
# Begin Source File

SOURCE=.\IllusionTempleEvent.h
# End Source File
# Begin Source File

SOURCE=.\IllusionTempleProcess.h
# End Source File
# Begin Source File

SOURCE=.\PCBangPointSystem.h
# End Source File
# Begin Source File

SOURCE=.\GambleSystem.h
# End Source File
# Begin Source File

SOURCE=.\XMasAttackEventData.h
# End Source File
# Begin Source File

SOURCE=.\ProbabilityItemBag.h
# End Source File
# Begin Source File

SOURCE=.\XMasAttackEvent.h
# End Source File
# Begin Source File

SOURCE=.\LargeRand.h
# End Source File
# Begin Source File

SOURCE=.\LifeStone.h
# End Source File
# Begin Source File

SOURCE=.\logproc.h
# End Source File
# Begin Source File

SOURCE=.\LogToFile.h
# End Source File
# Begin Source File

SOURCE=.\MagicDamage.h
# End Source File
# Begin Source File

SOURCE=.\MagicInf.h
# End Source File
# Begin Source File

SOURCE=.\MapClass.h
# End Source File
# Begin Source File

SOURCE=.\MapItem.h
# End Source File
# Begin Source File

SOURCE=.\MapServerManager.h
# End Source File
# Begin Source File

SOURCE=.\Mercenary.h
# End Source File
# Begin Source File

SOURCE=.\MonsterAttr.h
# End Source File
# Begin Source File

SOURCE=.\MonsterHerd.h
# End Source File
# Begin Source File

SOURCE=.\MonsterItemMng.h
# End Source File
# Begin Source File

SOURCE=.\MonsterSetBase.h
# End Source File
# Begin Source File

SOURCE=.\MoveCheck.h
# End Source File
# Begin Source File

SOURCE=.\MoveCommand.h
# End Source File
# Begin Source File

SOURCE=.\MultiAttackHackCheck.h
# End Source File
# Begin Source File

SOURCE=.\MultiCheckSum.h
# End Source File
# Begin Source File

SOURCE=..\common\MyWinsockBase.h
# End Source File
# Begin Source File

SOURCE=.\NpcTalk.h
# End Source File
# Begin Source File

SOURCE=.\NSerialCheck.h
# End Source File
# Begin Source File

SOURCE=.\ObjAttack.h
# End Source File
# Begin Source File

SOURCE=.\ObjBaseAttack.h
# End Source File
# Begin Source File

SOURCE=.\ObjCalCharacter.h
# End Source File
# Begin Source File

SOURCE=.\ObjUseSkill.h
# End Source File
# Begin Source File

SOURCE=.\PacketCheckSum.h
# End Source File
# Begin Source File

SOURCE=.\HackToolPacket.h
# End Source File
# Begin Source File

SOURCE=.\PartyClass.h
# End Source File
# Begin Source File

SOURCE=.\PCSProtocol.h
# End Source File
# Begin Source File

SOURCE=.\protocol.h
# End Source File
# Begin Source File

SOURCE=.\QuestInfo.h
# End Source File
# Begin Source File

SOURCE=.\QuestUtil.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\RingAttackEvent.h
# End Source File
# Begin Source File

SOURCE=.\SendHackLog.h
# End Source File
# Begin Source File

SOURCE=.\SetItemMacro.h
# End Source File
# Begin Source File

SOURCE=..\common\SetItemOption.h
# End Source File
# Begin Source File

SOURCE=.\Shop.h
# End Source File
# Begin Source File

SOURCE=.\SkillAdditionInfo.h
# End Source File
# Begin Source File

SOURCE=.\SkillDelay.h
# End Source File
# Begin Source File

SOURCE=.\SkillHitBox.h
# End Source File
# Begin Source File

SOURCE=.\spe.h
# End Source File
# Begin Source File

SOURCE=.\SProtocol.h
# End Source File
# Begin Source File

SOURCE=.\StatMng.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TDurMagicKeyChecker.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAI.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIAgro.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIAutomata.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIElement.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIGroup.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIGroupMember.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIMovePath.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIRule.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIRuleInfo.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIState.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIUnit.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterAIUtil.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterSkillElement.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterSkillElementInfo.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterSkillInfo.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterSkillManager.h
# End Source File
# Begin Source File

SOURCE=.\TMonsterSkillUnit.h
# End Source File
# Begin Source File

SOURCE=.\TNotice.h
# End Source File
# Begin Source File

SOURCE=.\TRandomPoolMgr.h
# End Source File
# Begin Source File

SOURCE=.\TServerAlertManager.h
# End Source File
# Begin Source File

SOURCE=.\TServerInfoDisplayer.h
# End Source File
# Begin Source File

SOURCE=.\MiniDump.h
# End Source File
# Begin Source File

SOURCE=.\TSkillElement.h
# End Source File
# Begin Source File

SOURCE=.\TStatistics.h
# End Source File
# Begin Source File

SOURCE=..\common\TSync.h
# End Source File
# Begin Source File

SOURCE=.\TUnion.h
# End Source File
# Begin Source File

SOURCE=.\TUnionInfo.h
# End Source File
# Begin Source File

SOURCE=.\MasterLevelSystem.h
# End Source File
# Begin Source File

SOURCE=.\MasterSkillSystem.h
# End Source File
# Begin Source File

SOURCE=.\user.h
# End Source File
# Begin Source File

SOURCE=.\SocketData.h
# End Source File
# Begin Source File

SOURCE=.\SocketOption.h
# End Source File
# Begin Source File

SOURCE=.\SocketSphere.h
# End Source File
# Begin Source File

SOURCE=.\ItemAddOption.h
# End Source File
# Begin Source File

SOURCE=.\ViewportGuild.h
# End Source File
# Begin Source File

SOURCE=.\Weapon.h
# End Source File
# Begin Source File

SOURCE=.\WhisperCash.h
# End Source File
# Begin Source File

SOURCE=..\common\winutil.h
# End Source File
# Begin Source File

SOURCE=.\wsGameServer.h
# End Source File
# Begin Source File

SOURCE=.\wsJoinServerCli.h
# End Source File
# Begin Source File

SOURCE=.\wsShopServerCli.h
# End Source File
# Begin Source File

SOURCE=.\WTEventItemList.h
# End Source File
# Begin Source File

SOURCE=..\common\WzMemScript.h
# End Source File
# Begin Source File

SOURCE=.\WzMultiCastSock.h
# End Source File
# Begin Source File

SOURCE=.\WzQueue.h
# End Source File
# Begin Source File

SOURCE=..\common\WZScriptEncode.h
# End Source File
# Begin Source File

SOURCE=.\WzUdp.h
# End Source File
# Begin Source File

SOURCE=..\include\Readscript.h
# End Source File
# Begin Source File

SOURCE=..\include\prodef.h
# End Source File
# Begin Source File

SOURCE=..\common\zzzitem.h
# End Source File
# Begin Source File

SOURCE=.\zzzmathlib.h
# End Source File
# Begin Source File

SOURCE=..\common\zzzpath.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\GameServer.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
