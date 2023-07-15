#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

#pragma region FORWARDS
static DWORD FindProcessIdByName(const char *processName);
static BOOL ReadProcessMemoryByName(const char *processName, LPCVOID address, LPVOID buffer, SIZE_T size);
static DWORD_PTR FindNestedValue(DWORD_PTR baseAddress, const DWORD_PTR *offsets, size_t offsetCount);
#pragma endregion
#pragma region GLOBALS
static DWORD g_processId;
static HANDLE g_processHandle;
#pragma endregion

int InitializeData()
{
    const char *processName = "Game.exe";
    DWORD processId = FindProcessIdByName(processName);

    if (processId == 0)
    {
        g_processId = NULL;
        return 1;
    }
    g_processId = processId;
    HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);

    if (processHandle == NULL)
    {
        g_processHandle = NULL;
        return 1;
    }
    g_processHandle = processHandle;
    return 0;
}

int CloseHandle()
{
    CloseHandle(g_processHandle);
}

int long FindNestedAddress(int baseAddress, const unsigned long *offsets, size_t offsetCount)
{
    DWORD_PTR address = baseAddress;
    for (size_t i = 0; i < offsetCount; i++)
    {
        ReadProcessMemory(processHandle, (LPCVOID)address, &address, sizeof(DWORD_PTR), NULL);
        address += offsets[i];
    }
    return address;
}


int GetData(int memoryLocation, int sizeBytes, void *buffer)
{
    return ReadProcessMemory(g_processId, (LPCVOID)memoryLocation, (LPVOID)buffer, sizeBytes, NULL)
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