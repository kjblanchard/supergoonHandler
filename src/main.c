#include <stdio.h>
#include <stdlib.h>
#include <character.h>
#include <debug.h>
#include <tui.h>
#include <settings.h>
#include <refresh.h>
#include <platform/gn_system.h>

const char *processName = "Game.exe";
static Settings *settings;
static Character *mainBoi;

static int Init()
{
    InitializeDebugLogFile();
    settings = CreateSettings();
    mainBoi = NewCharacter();
    puts("Here man");
    InitializeData();
    puts("After!");
}

static int Close()
{
    EndCurses();
    CloseDebugLogFile();
    return EXIT_SUCCESS;
}

static int Loop(Character *character)
{
    RefreshCharacterInfo(mainBoi);
    if (UpdateCharacterWindow(character))
    {
        return 1;
    }
    return 0;
}

int main()
{
    Init();
    int success = InitCurses(mainBoi->Health);


    while (Loop(mainBoi))
    {

    }
    return Close();
}
