# #########################################
# Initial config
# #########################################
cmake_minimum_required(VERSION 3.16)
message(STATUS "Starting Goon Bot configuration")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# #########################################
# File globbing
# #########################################
message(STATUS "Getting all files for cmake..")
file(GLOB_RECURSE FILES src/*.c* src/*.h*)

# #########################################
# Platform specific Project setup
# #########################################
message(STATUS "Changing the platform specific settings")

if(APPLE)
        # MACOS
        if(NOT IOS)
                set(MACOS ON)
                list(FILTER FILES EXCLUDE REGEX ".*platform/Windows.*$")
        endif(NOT IOS)
endif(APPLE)

if(WIN32)
        set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /c/cmake)
        list(FILTER FILES EXCLUDE REGEX ".*platform/Mac.*$")
endif(WIN32)

if(UNIX AND NOT APPLE)
        set(LINUX ON)
endif(UNIX AND NOT APPLE)

# #########################################
# Initialize
# #########################################
message(STATUS "Initializing the project")

# This exports a file that clangd can use so that we know what compile/include flags so that we can use clangd language server properly with our cmake attributes.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
include(FindPkgConfig)
project(supergoonHandler
        VERSION 0.1.0
        LANGUAGES C)
add_executable(supergoonHandlerExe
        ${FILES})
# Using 11 instead of 99 for forward declaring typedef
set_property(TARGET supergoonHandlerExe PROPERTY C_STANDARD 11)
find_package(PkgConfig)

# #########################################
# Packages
# #########################################
if(WIN32)
message(STATUS "Windows")
        find_library(LIB_PDCURSES
                NAMES pdcurses.a
                HINTS C:/Users/blanc/Downloads/PDCurses-3.9/PDCurses-3.9/wincon
                REQUIRED)
        set(CURSES_INCLUDE_DIR C:/Users/blanc/Downloads/PDCurses-3.9/PDCurses-3.9/)
        set(CURSES_LIBRARIES ${LIB_PDCURSES})
        set(LUA_INCLUDE_DIR /usr/local/include/)
else()
        find_package(Curses
                REQUIRED
        )
        set(LUA_INCLUDE_DIR /opt/homebrew/include/lua/)
endif(WIN32)

# Find lua static (non homebrew on mac)
find_library(LIB_LUA
        NAMES liblua_static lua_static liblua_static.a lua_static.a liblua.a
        HINTS /usr/local/lib
        REQUIRED)
set(LUA_LIBRARIES ${LIB_LUA})

# #########################################
# Options
# #########################################
option(CMAKE_DEBUG_VARIABLES "Runs a debug on all variables for troubleshooting" OFF)
option(GOON_BUILD_PCH "Uses a PCH file to try and speed up compilation" ON)

# #########################################
# Compile Definitions
# #########################################
target_compile_definitions(supergoonHandlerExe PRIVATE)

if(APPLE)
        target_compile_definitions(supergoonHandlerExe PRIVATE -DGN_PLATFORM_MACOS)
elseif(WIN32)
        target_compile_definitions(supergoonHandlerExe PRIVATE -DGN_PLATFORM_WINDOWS)
elseif(LINUX)
        target_compile_definitions(supergoonHandlerExe PRIVATE -DGN_PLATFORM_LINUX)
endif(APPLE)

# #########################################
# Precompiled headers
# #########################################
if(GOON_BUILD_PCH)
        message(STATUS "Setting up PCH, mac needs objc")
        target_precompile_headers(supergoonHandlerExe PRIVATE
                "$<$<COMPILE_LANGUAGE:C>:${CMAKE_CURRENT_SOURCE_DIR}/src/gnpch.h>")
endif(GOON_BUILD_PCH)

# #########################################
# Debug
# #########################################
if(CMAKE_DEBUG_VARIABLES)
        message(STATUS "Exporting debug")
        get_cmake_property(_variableNames VARIABLES)
        list(SORT _variableNames)

        foreach(_variableName ${_variableNames})
                message(STATUS "${_variableName}=${${_variableName}}")
        endforeach()
endif(CMAKE_DEBUG_VARIABLES)


# #########################################
# Compile Options
# #########################################
target_compile_options(supergoonHandlerExe PRIVATE
        -std=c99
        -Wall
        -Wextra
        -Wpedantic
        -Wdeprecated
        -Wno-newline-eof
)

# #########################################
# Linking Options
# #########################################
target_link_libraries(supergoonHandlerExe
        PUBLIC
        ${CURSES_LIBRARIES}
        ${LUA_LIBRARIES}
)

target_include_directories(supergoonHandlerExe
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
        ${CURSES_INCLUDE_DIR}
        ${LUA_INCLUDE_DIR}
        /usr/local/include/
        /c/
        C:/cmake/
)

# #########################################
# Install
# #########################################
set(FOLDERS_TO_COPY ./scripts)
install(DIRECTORY ${FOLDERS_TO_COPY}
        DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)