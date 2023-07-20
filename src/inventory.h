/**
 * @file inventory.h
 * @author your name (blanchardkevinj@gmail.com)
 * @brief Holds the inventory slots in game memory
 * @version 0.1
 * @date 2023-07-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <stdint.h>
#include <settings.h>

/**
 * @brief The amount of total item slots in the game.
 *
 */
#define INVENTORY_ITEM_SLOTS 40
/**
 * @brief Inventory that holds all of the items in the game.
 *
 */
typedef struct Inventory
{
    uint32_t Items[INVENTORY_ITEM_SLOTS];

} Inventory;
/**
 * @brief Creates a new inventory object
 *
 * @param settings The settings file to know the proper offsets
 * @return Inventory* The newly created inventory object pointer
 */
Inventory *NewInventory(Settings *settings);
/**
 * @brief Refreshes the inventory slots from the game
 *
 * @param inventory The inventory item to refresh
 * @return int 0 If failed.
 */
int RefreshInventory(Inventory *inventory);