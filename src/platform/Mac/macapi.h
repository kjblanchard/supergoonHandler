#pragma once
int GetHealth(int offset);
int InitializeMemoryReader();
int CloseMemoryReader();
int FindNestedAddress(const unsigned long *offsets, size_t offsetCount);