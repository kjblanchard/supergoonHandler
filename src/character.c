#include <gnpch.h>
#include <character.h>
#include <platform/gn_system.h>
#include <tui.h>

static int g_characterLocation = 0;
static int g_diabloCharacterLocation = 0;
// static int g_playerDataLocation = 0;
// static int g_playerPathLocation = 0;

Character *NewCharacter(Settings *settings)
{
    Character *character = malloc(sizeof(*character));
    character->Gold = 0;
    character->Health = 0;
    character->Mana = 0;
    character->Stamina = 0;
    character->BlankSpace = 0;
    int charAddress = FindNestedAddress(settings->characterMemoryLocation.offsets, settings->characterMemoryLocation.offsetCount);
    if (!charAddress)
    {
        g_characterLocation = 0;
        LogError("Could not determine proper address to get Character Info from!");
        return NULL;
    }
    g_characterLocation = charAddress;
    return character;
}

int RefreshCharacter(Character *character)
{
    if (g_characterLocation && !GetValueAtLocation(g_characterLocation, sizeof(*character), character))
    {
        LogWarn("Could not update character!");
        return 1;
    }
    return 0;
}

DiabloUnit *NewDiabloCharacterData(Settings *settings)
{
    DiabloUnit *unit = calloc(1, sizeof(*unit));
    int unitAddress = FindNestedAddress(settings->diabloCharacterDataMemoryLocation.offsets, settings->diabloCharacterDataMemoryLocation.offsetCount);
    if (!unitAddress)
    {
        g_characterLocation = 0;
        LogError("Could not determine proper address to get Character Info from!");
        WriteDebugMessage("Could not determine proper address to get Character Info from!");

        return NULL;
    }
    g_diabloCharacterLocation = unitAddress;
    return unit;
}
int RefreshDiabloCharacterData(DiabloUnit *unit, DiabloPath *path, PlayerData* playerData)
{
    if (g_diabloCharacterLocation && !GetValueAtLocation(g_diabloCharacterLocation, sizeof(*unit), unit))
    {
        LogWarn("Could not update unit!");
        return 1;
    }
    GetValueAtLocation(unit->PtPath, sizeof(*path), path);
    GetValueAtLocation(unit->PtUnitData, sizeof(*playerData), playerData);
    char words[150];
    sprintf(words, "Info is %x %x", unit->PtPath, unit->PtUnitData);
    WriteDebugMessage(words);
    return 0;
}