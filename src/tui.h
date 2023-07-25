#pragma once

typedef struct Character Character;
typedef struct Inventory Inventory;
typedef struct DiabloUnit DiabloUnit;
typedef struct DiabloPath DiabloPath;
typedef struct PlayerData PlayerData;

int InitCurses();
//TODO use a struct for these params
int UpdateCurses(Inventory *inventory, Character *character, DiabloPath* path, DiabloUnit* unit, PlayerData* data);
int WriteDebugMessage(const char* line);
int EndCurses();