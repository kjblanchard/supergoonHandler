#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdbool.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <debug.h>

#ifdef GN_PLATFORM_WINDOWS
#include <windows.h>
#include <tlhelp32.h>
#endif

#ifdef __GNUC__
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif

#ifdef __GNUC__
#  define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
#  define UNUSED_FUNCTION(x) UNUSED_ ## x
#endif