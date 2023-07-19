#pragma once
#include <character.h>
#include <inventory.h>

int InitCurses();
int UpdateCharacterWindow(Character *character);
int UpdateInventoryWindow(Inventory *inventory);
int EndCurses();
int DrawScreenLoop();