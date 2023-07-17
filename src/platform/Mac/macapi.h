#pragma once
int GetHealth(int offset);
int InitializeData();
int CloseGoonHandle();
int FindNestedAddress(int baseAddress, const unsigned long *offsets, size_t offsetCount);