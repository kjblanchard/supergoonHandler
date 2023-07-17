#include <stdlib.h>
#include <character.h>
#include <debug.h>
#include <platform/gn_system.h>

static int g_characterLocation = 0;

Character *NewCharacter(Settings *settings)
{
    Character *character = malloc(sizeof(*character));
    character->Gold = 0;
    character->Health = 0;
    character->Mana = 0;
    character->Stamina = 0;
    character->BlankSpace = 0;
    int charAddress = FindNestedAddress(settings->characterMemoryLocation.base, settings->characterMemoryLocation.offsets, settings->characterMemoryLocation.offsetCount);
    if (charAddress)
    {
        g_characterLocation = charAddress;
    }
    else
    {
        g_characterLocation = 0;
        LogError("Could not determine proper address to get Character Info from!");
    }
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