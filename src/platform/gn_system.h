#pragma once
#ifdef GN_PLATFORM_MACOS
#include <platform/Mac/macapi.h>
#endif

#ifdef GN_PLATFORM_WINDOWS
#include <platform/Windows/winapi.h>
#endif

/**
 * @brief Initializes the memory reading capabilities of the underlying OS system
 *
 * @return int
 */
extern int InitializeMemoryReader();
/**
 * @brief Closes the Memory reader and removes handles.
 *
 * @return int
 */
extern int CloseMemoryReader();
/**
 * @brief Finds a nested value based on a base pointer and it's offsets.
 *
 * @param baseAddress The base pointer address
 * @param offsets Array of offsets that will be used to follow
 * @param offsetCount The amount of offsets.
 * @return int The address at the end of the tunnel
 */
extern int FindNestedAddress(int baseAddress, const unsigned long *offsets, size_t offsetCount);
/**
 * @brief Get the Value At Location
 *
 * @param memoryLocation Location to get from.
 * @param sizeBytes Size to read
 * @param buffer Place to put the read data
 * @return int 0 if successful.
 */
extern int GetValueAtLocation(int memoryLocation, int sizeBytes, void *buffer);
