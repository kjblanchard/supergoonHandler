#include <gnpch.h>
#include <inventory.h>
#include <platform/gn_system.h>

static int g_inventoryLocation;

Inventory *NewInventory(Settings *settings)
{
    Inventory* inventory = malloc(sizeof(*inventory));
    memset(inventory->Items, 0, sizeof(uint32_t));
    int inventoryAddress = FindNestedAddress(settings->inventoryMemoryLocation.base, settings->inventoryMemoryLocation.offsets, settings->inventoryMemoryLocation.offsetCount);
    if (inventoryAddress)
    {
        g_inventoryLocation = inventoryAddress;
    }
    else
    {
        g_inventoryLocation = 0;
        LogError("Could not determine proper address to get Inventory Info from!");
    }
    return inventory;
}
int RefreshInventory(Inventory *inventory)
{
    if (g_inventoryLocation && !GetValueAtLocation(g_inventoryLocation, sizeof(*inventory), inventory))
    {
        LogWarn("Could not update inventory!");
        return 1;
    }
    return 0;
}
