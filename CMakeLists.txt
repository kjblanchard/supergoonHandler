
cmake_minimum_required(VERSION 3.16)
message(STATUS "Starting Goon Bot configuration")
# Set things
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
        endif(NOT IOS)
endif(APPLE)

if(WIN32)
        set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /c/cmake)
endif(WIN32)

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
set_property(TARGET supergoonHandlerExe PROPERTY C_STANDARD 99)
find_package(PkgConfig)

if(UNIX AND NOT APPLE)
        set(LINUX ON)
endif(UNIX AND NOT APPLE)


# #########################################
# Options
# #########################################
option(CMAKE_DEBUG_VARIABLES "Runs a debug on all variables for troubleshooting" OFF)

# #########################################
# For Debug, print aout all variables.
# #########################################
if(CMAKE_DEBUG_VARIABLES)
        message(STATUS "Exporting debug")
        get_cmake_property(_variableNames VARIABLES)
        list(SORT _variableNames)

        foreach(_variableName ${_variableNames})
                message(STATUS "${_variableName}=${${_variableName}}")
        endforeach()
endif(CMAKE_DEBUG_VARIABLES)

# External Libraries
find_package(Curses REQUIRED)
# find_library(LIB_VORBIS
#     REQUIRED
#     PATH_SUFFIXES .a
#     NAMES libvorbis vorbis vorbis.a vorbis.dll libvorbis.a
#     HINTS /usr/local/lib /c/cmake/lib)

# #########################################
# Compile Definitions
# #########################################
target_compile_definitions(supergoonHandlerExe PRIVATE)

if(GOON_BUILD_ENGINE)
        target_compile_definitions(supergoonHandlerExe PRIVATE

                # -DGN_BUILD_DLL # Builds the full project
                # -DGN_ENABLE_ASSERTS # Enables asserts
        )
endif(GOON_BUILD_ENGINE)

# target_compile_definitions(goonEngine PRIVATE
#         -DGL_SILENCE_DEPRECATION
#         -DIMGUI_IMPL_OPENGL_LOADER_GLAD # Used since we use glad?
# )

if(APPLE)
        target_compile_definitions(supergoonHandlerExe PRIVATE -DGN_PLATFORM_MACOS)
elseif(WIN32)
        target_compile_definitions(supergoonHandlerExe PRIVATE -DGN_PLATFORM_WINDOWS)
elseif(LINUX)
        target_compile_definitions(supergoonHandlerExe PRIVATE -DGN_PLATFORM_LINUX)
endif(APPLE)

# #########################################
# Compile Options
# #########################################
target_compile_options(supergoonHandlerExe PRIVATE
       -std=c99
        -Wall
        -Wextra
        -Wpedantic
        -Wdeprecated
        -Wextra-semi
)

# #########################################
# Linking Options
# #########################################
target_link_libraries(supergoonHandlerExe
        PUBLIC
        ${CURSES_LIBRARIES}

        PRIVATE
)

target_include_directories(supergoonHandlerExe
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
        ${CURSES_INCLUDE_DIR}
        PRIVATE
)

