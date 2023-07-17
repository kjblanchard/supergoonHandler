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

int InitializeMemoryReader()
{
    const char *processName = "Game.exe";
    DWORD processId;
    processId = FindProcessIdByName(processName);
    // processId = 0x4774;

    if (processId == 0)
    {
        g_processId = NULL;
        printf("No process name!\n");
        return 1;
    }
    g_processId = processId;
    DWORD_PTR baseAddr;
    baseAddr = GetModuleBaseAddress(processId, processName);
    if(baseAddr == 0)
    {
        printf("Borked getting base address\n");
        g_baseAddr = NULL;
        return 1;
    }
    printf("Base address is %d", baseAddr);

    HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);

    if (processHandle == NULL)
    {
        g_processHandle = NULL;
        printf("Failed to get handle, error: %d using process id %d\n", GetLastError(), processId);
        return 1;
    }
    g_processHandle = processHandle;
    printf("Process ID is %x Process handle is %d\n",g_processId, g_processHandle);
    return 0;
}

int CloseMemoryReader()
{
    CloseHandle(g_processHandle);
}

int FindNestedAddress(int baseAddress, const unsigned long *offsets, size_t offsetCount)
{
    // DWORD_PTR address = baseAddress;
    // Add in the base address found in x64dbg to the nested value, should do this for everything probably.
    // DWORD_PTR address = 0x00400000 + baseAddress;
    DWORD_PTR address = 0x400000+ 0x004842A8;
    printf("Base address I should read memory from is %x", address);

    for (size_t i = 0; i < offsetCount; i++)
    {
        int result = ReadProcessMemory(g_processHandle, (LPCVOID)address, &address, sizeof(DWORD_PTR), NULL);
        if(result == 0)
        {
            printf("Problem, %d", GetLastError());
        }
        printf("Value I just read is %x\n", address);
        address += offsets[i];
        printf("Offset address is %x\n", address);
    }
    return address;
}

int GetValueAtLocation(int memoryLocation, int sizeBytes, void *buffer)
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
    // HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE , processId);
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