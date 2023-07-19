#include <gnpch.h>
#include <inventory.h>
#include <platform/gn_system.h>

static int g_inventoryLocation;

Inventory *NewInventory(Settings *settings)
{
    Inventory* inventory = malloc(sizeof(*inventory));
    memset(inventory->Items, 0, 40 * sizeof(uint32_t));
    for (size_t i = 0; i < settings->inventoryMemoryLocation.offsetCount; i++)
    {
        LogWarn("Inventory Offset is %x", settings->inventoryMemoryLocation.offsets[i]);
    }

    int inventoryAddress = FindNestedAddress(settings->inventoryMemoryLocation.offsets, settings->inventoryMemoryLocation.offsetCount);
    if (inventoryAddress)
    {
        g_inventoryLocation = inventoryAddress;
        LogWarn("Inventory address is %x", inventoryAddress);
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
