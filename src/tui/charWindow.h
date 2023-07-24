/**
 * @file charWindow.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <primitives/rectangle.h>
#include <primitives/point.h>

typedef struct Character Character;
int InitCharWindow(int x, int y, int width, int height);
int UpdateCharacterWindow(Character *character);
Rectangle GetCharWindowRect();
Point GetCharWindowPos();
Point GetCharWindowSize();
