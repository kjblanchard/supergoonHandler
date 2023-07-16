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

// static int Init()
// {
//     InitializeDebugLogFile();
//     settings = CreateSettings();
//     mainBoi = NewCharacter();
// }

// static int Close()
// {
//     EndCurses();
//     CloseDebugLogFile();
//     return EXIT_SUCCESS;
// }

// static int Loop(Character *character)
// {
//     RefreshCharacterInfo(mainBoi);
//     if (UpdateCharacterWindow(character))
//     {
//         return 1;
//     }
//     return 0;
// }

// int main()
// {
//     Init();
//     int success = InitCurses(mainBoi->Health);

//     while (Loop(mainBoi))
//     {

//     }
//     return Close();
// }

#include <stdio.h>
#include <Windows.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: program_name <Process ID>\n");
        return 1;
    }

    DWORD processId = atoi(argv[1]);

    HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processId);
    if (processHandle == NULL)
    {
        printf("Failed to open the process.\n");
        return 1;
    }

    printf("Process Handle: %p\n", processHandle);

    CloseHandle(processHandle);

    return 0;
}
