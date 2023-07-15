#include <stdlib.h>
#include <refresh.h>
#include <character.h>
#include <debug.h>
#include <platform/gn_system.h>

static int g_characterLocation = 0;

void RefreshCharacterInfo(Character *character)
{
    int base = 0x004842A8;
    const unsigned long offsets[] = {490};
    size_t offsetCount = 1;

    int charAddress = FindNestedValue(base, offsets, offsetCount);
    if (charAddress)
    {
        g_characterLocation = charAddress;
    }
    else
    {
        g_characterLocation = 0;

        LogError("Cannot get character info!");
        return;
    }

    if (g_characterLocation && !GetData(g_characterLocation, sizeof(*character), character))
    {
        LogWarn("Could not update character!");
    }
}