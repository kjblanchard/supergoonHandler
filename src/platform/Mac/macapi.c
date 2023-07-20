#include <gnpch.h>
#include <stddef.h>

int CloseMemoryReader(int offset)
{
    return true;
}
int InitializeMemoryReader()
{
    return true;
}

int FindNestedAddress(int baseAddress, const unsigned long *offsets, size_t offsetCount)
{
    return true;
}
int GetValueAtLocation(int memoryLocation, int sizeBytes, void *buffer)
{
    return true;
}