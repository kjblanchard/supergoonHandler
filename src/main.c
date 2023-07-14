#include <stdio.h>
#include <stdlib.h>
#include <character.h>
#include <tui.h>
#include <settings.h>
#include <platform/gn_system.h>

const char *processName = "Game.exe";

int main()
{

    Settings *settings = CreateSettings();
    Character *mainBoi = NewCharacter();
    mainBoi->Health = GetHealth(settings->offsets.health);
    printf("Character\nHealth: %d\n", mainBoi->Health);
    int success = InitCurses(mainBoi->Health);
    EndCurses();
    return EXIT_SUCCESS;
}
