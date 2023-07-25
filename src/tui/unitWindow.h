/**
 * @file unitWindow.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

typedef struct DiabloUnit DiabloUnit;
typedef struct DiabloPath DiabloPath;
typedef struct PlayerData PlayerData;

int InitUnitWindow(int x, int y, int width, int height);
int UpdateUnitWindow(DiabloUnit *unit, DiabloPath *path, PlayerData *playerData);