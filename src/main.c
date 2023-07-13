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
#ifdef GN_PLATFORM_MACOS
    int success = InitCurses();
#endif
    Character *mainBoi = NewCharacter();
    printf("Character\nHealth: %d\n", mainBoi->Health);
    GetHealth(settings->offsets.health);
    return EXIT_SUCCESS;
}
