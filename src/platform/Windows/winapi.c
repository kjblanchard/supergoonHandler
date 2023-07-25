#include <gnpch.h>

#pragma region FORWARDS
static DWORD FindProcessIdByName(const char *processName);
static BOOL ReadProcessMemoryByName(const char *processName, LPCVOID address, LPVOID buffer, SIZE_T size);
static DWORD GetModuleBaseAddress(DWORD processId, const char *moduleName);
#pragma endregion
#pragma region GLOBALS
static DWORD g_processId;
static DWORD g_baseAddr;
static HANDLE g_processHandle;
#pragma endregion

int InitializeMemoryReader()
{
    const char *processName = "Game.exe";
    DWORD processId;
    processId = FindProcessIdByName(processName);
    if (processId == 0)
    {
        g_processId = NULL;
        LogError("No process name!\n");
        return false;
    }
    g_processId = processId;
    DWORD baseAddr;
    baseAddr = GetModuleBaseAddress(processId, processName);
    if(baseAddr == 0)
    {
        LogError("Borked getting base address\n");
        g_baseAddr = NULL;
        return false;
    }
    g_baseAddr = baseAddr;

    HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);

    if (processHandle == NULL)
    {
        g_processHandle = NULL;
        printf("Failed to get handle, error: %d using process id %d\n", GetLastError(), processId);
        return false;
    }
    g_processHandle = processHandle;
    printf("Process ID is %x Process handle is %d\n",g_processId, g_processHandle);
    return true;
}

int CloseMemoryReader()
{
    CloseHandle(g_processHandle);
}

int FindNestedAddress(const unsigned long *offsets, size_t offsetCount)
{
    // Add in the base address found in x64dbg to the nested value, should do this for everything probably.
    // DWORD address = 0x00400000 + offsets[0];
    DWORD address = g_baseAddr + offsets[0];
    LogDebug("Base address to read is %x, cause the offset is %x", address, offsets[0]);
    for (size_t i = 1; i < offsetCount; i++)
    {
        DWORD_PTR newAddress;
        LogDebug("Going to read %x", newAddress);
        GetValueAtLocation(address, sizeof(DWORD), &newAddress);
        int offset = offsets[i];
        address = newAddress + offset;
    }
    LogDebug("Address found %x", address);
    return address;
}

int GetValueAtLocation(int memoryLocation, int sizeBytes, void *buffer)
{

    int result = ReadProcessMemory(g_processHandle, (LPCVOID)memoryLocation, (LPVOID)buffer, sizeBytes, NULL);
    if (result == 0)
    {
        LogWarn("Problem with reading memory location %x, size of %d, %lud", memoryLocation, sizeBytes, GetLastError());
        return false;
    }
    return true;
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

static DWORD GetModuleBaseAddress(DWORD processId, const char *moduleName)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE , processId);
    // HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
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
                    return (DWORD)moduleEntry.modBaseAddr;
                }
            } while (Module32Next(snapshot, &moduleEntry));
        }

        CloseHandle(snapshot);
    }

    printf("Could not find anything for this module name");
    return 0;
}