typedef struct Character
{
    int Health;
    int Mana;
    int Gold;

} Character;

/**
 * @brief Creates a new Character with base information
 *
 * @return Character* Pointer to a character.
 */
Character *NewCharacter(int health);
