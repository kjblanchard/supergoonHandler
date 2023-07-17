#pragma once
#include <stdbool.h>

typedef struct Resolution
{
    int width;
    int height;
    bool fullscreen;

} Resolution;

typedef struct Images
{
    int count;
    char **images;

} Images;

typedef struct MemoryLocation {
    int base;
    int offsetCount;
    unsigned long* offsets;

} MemoryLocation;

typedef struct Settings
{
    Resolution resolution;
    Images images;
    MemoryLocation characterMemoryLocation;

} Settings;

Settings *CreateSettings();