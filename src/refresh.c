#include <stdlib.h>
#include <refresh.h>
#include <character.h>
#include <platform/gn_system.h>

static int g_characterLocation = NULL;

void RefreshCharacterInfo(Character *character)
{
    int base = 0x004842A8;
    unsigned long offsets[] = {490};
    size_t offsetCount = 1;

    int charAddress = FindNestedValue(base, offsets, offsetCount);
    if (charAddress)
    {
        g_characterLocation = charAddress;
    }
    else
    {
        g_characterLocation = NULL;
    }

    GetData(g_characterLocation, sizeof(*character), character);

}