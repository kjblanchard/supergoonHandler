#include <stdlib.h>
#include <character.h>

Character *NewCharacter()
{
    Character *character = malloc(sizeof(*character));
    character->Gold = 0;
    character->Health = 0;
    character->Mana = 0;
    character->Stamina = 0;
    character->BlankSpace = 0;
    return character;
}