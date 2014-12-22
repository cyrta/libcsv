
cmake_minimum_required (VERSION 2.8)

PROJECT(csv)

#include (CheckIncludeFiles)
#include (CheckSymbolExists)
#include (CheckCSourceCompiles)

#  Platform checks.

#if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#    add_definitions (-DCSV_HAVE_WINDOWS)
#    add_definitions (-D_CRT_SECURE_NO_WARNINGS)

#    if (MINGW)
#        add_definitions (-DCSV_HAVE_MINGW -DCSV_HAVE_STDINT -D_WIN32_WINNT=0x0600)
#    endif ()
#else ()
#    message (FATAL_ERROR "ERROR: CMake build system is intended only to generate MSVC solution files.\nUse autotools build system for any other purpose." )
#endif ()

#  Build the library itself.

add_subdirectory (src)

#ADD_LIBRARY(csv STATIC csv.c)


#  Build the tools

#add_executable (nanocat tools/nanocat.c tools/options.c)
#target_link_libraries (nanocat nanomsg)


