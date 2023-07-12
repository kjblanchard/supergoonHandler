#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <character.h>

void curses_base(Character* charmander)
{
    initscr();
    addstr("-----------------\n| Supergoon Bot |\n| v0.1.0        |\n-----------------\n\n");
    printw("-----------------\n Health: %d\n Mana: %d \n-----------------\n\n", charmander->Health, charmander->Mana);
    refresh();
    addstr("\npress any key to exit...");
    refresh();

    getch();

    endwin();
}

int main()
{
    Character* mainBoi = NewCharacter();

    curses_base(mainBoi);
    return EXIT_SUCCESS;
}