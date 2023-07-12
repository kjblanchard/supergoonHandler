#include <stdio.h>
#include <stdlib.h>
#include <character.h>

void curses_base(Character* charmander)
{

    printf("-----------------\n Health: %d\n Mana: %d \n-----------------\n\n", charmander->Health, charmander->Mana);
}

int main()
{
    Character* mainBoi = NewCharacter();

    curses_base(mainBoi);
    return EXIT_SUCCESS;
}
