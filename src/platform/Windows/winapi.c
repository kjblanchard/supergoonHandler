#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

#pragma region FORWARDS
static DWORD FindProcessIdByName(const char *processName);
static BOOL ReadProcessMemoryByName(const char *processName, LPCVOID address, LPVOID buffer, SIZE_T size);
static DWORD_PTR GetModuleBaseAddress(DWORD processId, const char *moduleName);
#pragma endregion
#pragma region GLOBALS
static DWORD g_processId;
static DWORD_PTR g_baseAddr;
static HANDLE g_processHandle;
#pragma endregion

int InitializeData()
{
    const char *processName = "Game.exe";
    DWORD processId;

    if (processId == 0)
    {
        g_processId = NULL;
        return 1;
    }
    g_processId = processId;
    DWORD_PTR baseAddr;
    baseAddr = GetModuleBaseAddress(processId, processName);
    if(baseAddr == 0)
    {
        printf("Borked getting base address");
        g_baseAddr = NULL;
        return 1;
    }
    HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);

    if (processHandle == NULL)
    {
        g_processHandle = NULL;
        printf("Failed to get handle, error: %d", GetLastError());
        return 1;
    }
    g_processHandle = processHandle;
    printf("Process handle is %d", g_processHandle);
    return 0;
}

int CloseGoonHandle()
{
    CloseHandle(g_processHandle);
}

int FindNestedAddress(int baseAddress, const unsigned long *offsets, size_t offsetCount)
{
    DWORD_PTR address = baseAddress;
    for (size_t i = 0; i < offsetCount; i++)
    {
        DWORD_PTR newAddress;
        ReadProcessMemory(g_processHandle, (LPCVOID)address, &newAddress, sizeof(DWORD_PTR), NULL);
        printf("The address is %x, new address is %x, and offset is %d\n", address, newAddress, offsets[i]);
        address = newAddress + offsets[i];
        printf("Offset address is %x\n", address);
    }
    return address;
}

int GetData(int memoryLocation, int sizeBytes, void *buffer)
{

    int result = ReadProcessMemory(g_processHandle, (LPCVOID)memoryLocation, (LPVOID)buffer, sizeBytes, NULL);
    if (result == 0)
    {
        printf("Problem with reading memory location %x, size of %d, %d \n", memoryLocation, sizeBytes, GetLastError());
    }
    return;
}

/**
 * @brief Converts two bytes to int from a buffer.
 * @param buffer
 * @return int
 */
static int ConvertBytesToInt(void *buffer)
{
    // Memory read successfully, convert bytes to integer
    unsigned char *byteBuffer = (unsigned char *)buffer;
    // Little Endian - Windows
    int health = (int)((byteBuffer[1] << 8) | byteBuffer[0]);
    return health;
}

static DWORD FindProcessIdByName(const char *processName)
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

static DWORD_PTR GetModuleBaseAddress(DWORD processId, const char *moduleName)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (snapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 moduleEntry;
        moduleEntry.dwSize = sizeof(MODULEENTRY32);

        if (Module32First(snapshot, &moduleEntry))
        {
            do
            {
                if (strcmp(moduleEntry.szModule, moduleName) == 0)
                {
                    CloseHandle(snapshot);
                    return (DWORD_PTR)moduleEntry.modBaseAddr;
                }
            } while (Module32Next(snapshot, &moduleEntry));
        }

        CloseHandle(snapshot);
    }

    printf("Could not find anything for this module name");
    return 0;
}