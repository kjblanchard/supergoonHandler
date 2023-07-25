/**
 * @file character.h
 * @author Kevin Blanchard (blanchardkevinj@gmail.com)
 * @brief A character data structure that represents character data in diablo II LOD SP.
 * @version 0.1
 * @date 2023-07-14
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <stdint.h>
#include <settings.h>
/**
 * @brief Represents a character class In diablo memory space
 *
 */
typedef struct Character
{
    uint16_t Health;
    uint16_t Mana;
    uint16_t Stamina;
    uint64_t BlankSpace;
    uint16_t Gold;
} Character;

typedef struct PlayerData
{
    char Name[16];

} PlayerData;

typedef struct DiabloPath
{
    uint16_t TwoBytes;
    uint16_t X;
    uint16_t TwoMoreBytes;
    uint16_t Y;

} DiabloPath;

typedef struct DiabloUnit
{
    uint32_t Type;
    uint32_t NotSure;
    uint32_t AlwaysNull;
    uint32_t Guid;
    uint32_t Mode;
    uint32_t PtUnitData;
    uint32_t ActNumber;
    uint64_t ReallyNotSure;
    // uint64_t StillNotSure;
    uint32_t WhatevenIsThis;
    uint32_t PtPath;

} DiabloUnit;

/**
 * @brief Creates a new Character with base information
 * @param settings The bot settings to set offsets with.
 *
 * @return Character* Pointer to a character.
 */
Character *NewCharacter(Settings *settings);
/**
 * @brief Refreshes a caracters data from in game memory
 *
 * @param character The character to update
 * @return int 0 if success
 */
int RefreshCharacter(Character *character);

DiabloUnit *NewDiabloCharacterData(Settings *settings);
int RefreshDiabloCharacterData(DiabloUnit *unit, DiabloPath *path, PlayerData *playerData);