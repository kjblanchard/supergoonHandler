#include <gnpch.h>
#include <stddef.h>

int CloseMemoryReader(int offset)
{
    return 1;
}
int InitializeMemoryReader()
{
    return 0;
}

int FindNestedAddress(int baseAddress, const unsigned long *offsets, size_t offsetCount)
{
    return 0;
}
int GetValueAtLocation(int memoryLocation, int sizeBytes, void *buffer)
{
    return 0;
}