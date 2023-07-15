#pragma once
#include <stdint.h>
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
 *
 * @return Character* Pointer to a character.
 */
Character *NewCharacter();
