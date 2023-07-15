#ifdef GN_PLATFORM_MACOS
#include <platform/Mac/macapi.h>
#endif

#ifdef GN_PLATFORM_WINDOWS
#include <platform/Windows/winapi.h>
#endif

extern int InitializeData();
extern int CloseHandle();
extern int FindNestedAddress(int baseAddress, const unsigned long *offsets, size_t offsetCount);
extern int GetData(int memoryLocation, int sizeBytes, void *buffer);
