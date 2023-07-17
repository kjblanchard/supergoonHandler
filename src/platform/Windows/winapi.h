/**
 * @file winapi.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-14
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <stddef.h>

int InitializeMemoryReader();
int CloseMemoryReader();
int FindNestedAddress(int baseAddress, const unsigned long *offsets, size_t offsetCount);
int GetValueAtLocation(int memoryLocation, int sizeBytes, void *buffer);