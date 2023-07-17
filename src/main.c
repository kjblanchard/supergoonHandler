#include <stdio.h>
#include <stdlib.h>
#include <character.h>
#include <debug.h>
#include <tui.h>
#include <settings.h>
#include <platform/gn_system.h>

static Settings *settings;
static Character *mainBoi;

static int Init()
{
    InitializeDebugLogFile();
    settings = CreateSettings();
    InitializeMemoryReader();
    mainBoi = NewCharacter(settings);
    InitCurses();
}

static int Close()
{
    EndCurses();
    CloseMemoryReader();
    CloseDebugLogFile();
    return EXIT_SUCCESS;
}

static int Loop(Character *character)
{
    RefreshCharacter(mainBoi);
    if (UpdateCharacterWindow(character))
    {
        return 1;
    }
    return 0;
}

int main()
{
    Init();


    while (Loop(mainBoi))
    {

    }
    return Close();
}
