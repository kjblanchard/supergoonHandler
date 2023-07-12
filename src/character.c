#include <character.h>
#include <stdlib.h>

Character *NewCharacter()
{
    Character *character = malloc(sizeof(*character));
    character->Gold = 0;
    character->Health = 0;
    character->Mana = 0;
    return character;
}
