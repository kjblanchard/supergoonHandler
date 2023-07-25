/**
 * @file messageWindow.h
 * @author Kevin Blanchard (enf3rno@yahoo.com)
 * @brief Creates the message window for messages inside of the tui
 * @version 0.1
 * @date 2023-07-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

int InitMessageWindow(int x, int y, int width, int height);
void SendMessageToMessageWindow(const char *line);
int UpdateMessageWindow();