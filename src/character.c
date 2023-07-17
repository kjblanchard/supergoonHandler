#include <stdlib.h>
#include <character.h>
#include <debug.h>
#include <platform/gn_system.h>

static int g_characterLocation = 0;

Character *NewCharacter()
{
    Character *character = malloc(sizeof(*character));
    character->Gold = 0;
    character->Health = 0;
    character->Mana = 0;
    character->Stamina = 0;
    character->BlankSpace = 0;
    return character;
}

int RefreshCharacter(Character *character, Settings* settings)
{
    // These should be read from lua.
    // int base = 0x004842A8;
    // const unsigned long offsets[] = {0x490};
    // size_t offsetCount = 1;
    int charAddress = FindNestedAddress(settings->characterMemoryLocation.base, settings->characterMemoryLocation.offsets, settings->characterMemoryLocation.offsetCount);
    if (charAddress)
    {
        g_characterLocation = charAddress;
    }
    else
    {
        g_characterLocation = 0;

        LogError("Cannot get character info!");
        return 1;
    }

    if (g_characterLocation && !GetData(g_characterLocation, sizeof(*character), character))
    {
        LogWarn("Could not update character!");
        return 1;
    }
    return 0;
}