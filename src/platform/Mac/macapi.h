#pragma once
int GetHealth(int offset);
int InitializeData();
int CloseGoonHandle();
int FindNestedValue(int baseAddress, const unsigned long *offsets, size_t offsetCount);