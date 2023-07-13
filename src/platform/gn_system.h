#ifdef GN_PLATFORM_MACOS
#include <platform/Mac/macapi.h>
#endif

#ifdef GN_PLATFORM_WINDOWS
#include <platform/Windows/winapi.h>
#endif

extern int GetHealth(int offset);
