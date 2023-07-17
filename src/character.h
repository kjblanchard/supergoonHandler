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
/**
 * @brief Creates a new Character with base information
 * @param settings The bot settings to set offsets with.
 *
 * @return Character* Pointer to a character.
 */
Character *NewCharacter(Settings* settings);
/**
 * @brief Refreshes a caracters data from in game memory
 *
 * @param character The character to update
 * @return int 0 if success
 */
int RefreshCharacter(Character* character);
