#include <stdio.h>
#include <stdlib.h>
#include <character.h>
#include <windows.h>
#include <tlhelp32.h>

DWORD FindProcessIdByName(const char *processName)
{
    DWORD processId = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(snapshot, &processEntry))
        {
            do
            {
                if (strcmp(processEntry.szExeFile, processName) == 0)
                {
                    processId = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &processEntry));
        }

        CloseHandle(snapshot);
    }

    return processId;
}

BOOL ReadProcessMemoryByName(const char *processName, LPCVOID address, LPVOID buffer, SIZE_T size)
{
    DWORD processId = FindProcessIdByName(processName);

    if (processId != 0)
    {
        HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);

        if (processHandle != NULL)
        {
            BOOL success = ReadProcessMemory(processHandle, address, buffer, size, NULL);

            CloseHandle(processHandle);

            return success;
        }
    }

    return FALSE;
}

void curses_base(Character *charmander)
{

    printf("-----------------\n Health: %d\n Mana: %d \n-----------------\n\n", charmander->Health, charmander->Mana);
}

int main()
{
    const char *processName = "Game.exe";
    DWORD processId = FindProcessIdByName(processName);
    int health = 0;
    Character *mainBoi = NewCharacter(health);

    if (processId != 0)
    {
        // Define the address and size of the memory you want to read
        LPCVOID address = (LPCVOID)0x056B0490;
        SIZE_T size = 2;

        // Allocate a buffer to store the read memory
        LPVOID buffer = malloc(size);

        if (ReadProcessMemoryByName(processName, address, buffer, size))
        {
            // Memory read successfully, you can access the buffer data
            // Example: Print the first 10 bytes
            // for (int i = 0; i < 2; i++)
            // {
            //     printf("%02X ", ((unsigned char *)buffer)[i]);
            // }
            // Memory read successfully, convert bytes to integer
            unsigned char *byteBuffer = (unsigned char *)buffer;

            // Assuming the two bytes represent a little-endian value
            health = (int)((byteBuffer[1] << 8) | byteBuffer[0]);
            mainBoi->Health = health;
            printf("Health: %d\n", mainBoi->Health);
        }
        else
        {
            printf("Failed to read process memory.\n");
        }

        free(buffer);
    }
    else
    {
        printf("Process not found.\n");
    }

    return EXIT_SUCCESS;
}
