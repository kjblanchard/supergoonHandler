#pragma once

typedef struct Character Character;
typedef struct Inventory Inventory;

int InitCurses();
int UpdateCurses(Inventory *inventory, Character *character);
int WriteDebugMessage(const char* line);
int EndCurses();