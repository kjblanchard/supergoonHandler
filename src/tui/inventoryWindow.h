/**
 * @file inventoryWindow.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <inventory.h>
#include <primitives/rectangle.h>

int InitInventoryWindow(int x, int y, int width, int height);
int UpdateInventoryWindow(Inventory *inventory);