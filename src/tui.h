#pragma once
#include <character.h>

int InitCurses();
int UpdateCharacterWindow(Character* character);
int EndCurses();
int DrawScreenLoop();