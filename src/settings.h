/**
 * @file settings.h
 * @author Kevin Blanchard (blanchardkevinj@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-07-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
typedef struct MemoryLocation {
    int offsetCount;
    unsigned long* offsets;

} MemoryLocation;

typedef struct Settings
{
    MemoryLocation characterMemoryLocation;
    MemoryLocation inventoryMemoryLocation;
    MemoryLocation diabloCharacterDataMemoryLocation;

} Settings;

Settings *CreateSettings();