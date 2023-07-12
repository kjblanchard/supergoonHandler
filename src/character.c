#include <character.h>
#include <stdlib.h>

Character *NewCharacter()
{
    Character *character = malloc(sizeof(*character));
    character->Gold = 20;
    character->Health = 100;
    character->Mana = 50;
    return character;
}
