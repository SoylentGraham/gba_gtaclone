# Microsoft Developer Studio Project File - Name="ferk" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=ferk - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ferk.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ferk.mak" CFG="ferk - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ferk - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "ferk - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "ferk - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f ferk.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "ferk.exe"
# PROP BASE Bsc_Name "ferk.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "nmake /f "ferk.mak""
# PROP Rebuild_Opt "/a"
# PROP Target_File "ferk.exe"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "ferk - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f ferk.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "ferk.exe"
# PROP BASE Bsc_Name "ferk.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "nmake /f "ferk.mak""
# PROP Rebuild_Opt "/a"
# PROP Target_File "ferk.gba"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "ferk - Win32 Release"
# Name "ferk - Win32 Debug"

!IF  "$(CFG)" == "ferk - Win32 Release"

!ELSEIF  "$(CFG)" == "ferk - Win32 Debug"

!ENDIF 

# Begin Group "core_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\core\animated_sprite.c
# End Source File
# Begin Source File

SOURCE=..\core\camera.c
# End Source File
# Begin Source File

SOURCE=..\core\car.c
# End Source File
# Begin Source File

SOURCE=..\core\collisions.c
# End Source File
# Begin Source File

SOURCE=..\core\core.c
# End Source File
# Begin Source File

SOURCE=..\core\font.c
# End Source File
# Begin Source File

SOURCE=..\core\map.c
# End Source File
# Begin Source File

SOURCE=..\core\math.c
# End Source File
# Begin Source File

SOURCE=..\core\menu_screens.c
# End Source File
# Begin Source File

SOURCE=..\core\sprites.c
# End Source File
# Begin Source File

SOURCE=..\core\tile_alloc.c
# End Source File
# Begin Source File

SOURCE=..\core\tiles.c
# End Source File
# End Group
# Begin Group "core_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\core\animated_sprite.h
# End Source File
# Begin Source File

SOURCE=..\core\camera.h
# End Source File
# Begin Source File

SOURCE=..\core\car.h
# End Source File
# Begin Source File

SOURCE=..\core\collisions.h
# End Source File
# Begin Source File

SOURCE=..\core\core.h
# End Source File
# Begin Source File

SOURCE=..\core\font.h
# End Source File
# Begin Source File

SOURCE=..\core\GBA.H
# End Source File
# Begin Source File

SOURCE=..\core\keypad.h
# End Source File
# Begin Source File

SOURCE=..\core\map.h
# End Source File
# Begin Source File

SOURCE=..\core\math.h
# End Source File
# Begin Source File

SOURCE=..\core\menu_screens.h
# End Source File
# Begin Source File

SOURCE=..\core\sprites.h
# End Source File
# Begin Source File

SOURCE=..\core\tile_alloc.h
# End Source File
# Begin Source File

SOURCE=..\core\tiles.h
# End Source File
# Begin Source File

SOURCE=..\core\types.h
# End Source File
# End Group
# Begin Group "game_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\game\game.c
# End Source File
# Begin Source File

SOURCE=..\game\main.c
# End Source File
# Begin Source File

SOURCE=..\game\menus.c
# End Source File
# Begin Source File

SOURCE=..\game\tile_sets.c
# End Source File
# End Group
# Begin Group "game_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\game\game.h
# End Source File
# Begin Source File

SOURCE=..\game\main.h
# End Source File
# Begin Source File

SOURCE=..\game\menus.h
# End Source File
# Begin Source File

SOURCE=..\game\tile_sets.h
# End Source File
# End Group
# Begin Group "media_"

# PROP Default_Filter ""
# Begin Group "gfx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\media\gfx\blank.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\building.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\car_sprite.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\font.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\media.h
# End Source File
# Begin Source File

SOURCE=..\media\gfx\palette.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\roads.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\shadow.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\spotlight.c
# End Source File
# End Group
# Begin Group "map"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\media\map\map_data.c
# End Source File
# Begin Source File

SOURCE=..\media\map\map_data.h
# End Source File
# Begin Source File

SOURCE=..\media\map\title_screen_map.c
# End Source File
# End Group
# Begin Group "sound"

# PROP Default_Filter ""
# End Group
# End Group
# End Target
# End Project
