#pragma once
#include <character.h>
#include <inventory.h>

int InitCurses();
int UpdateCharacterWindow(Character *character);
int UpdateInventoryWindow(Inventory *inventory);
int UpdateMessageWindow();
void SendMessageToMessageWindow(const char* line);
void PrintDebugTui();
int EndCurses();
int DrawScreenLoop();