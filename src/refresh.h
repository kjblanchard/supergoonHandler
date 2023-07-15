/**
 * @file refresh.h
 * @author Kevin Blanchard (blanchardkevinj@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-07-14
 *
 * @copyright Copyright (c) 2023
 *
 */
struct Character;

/**
 * @brief Updates a character based on its in game memory
 *
 * @param character The character to update
 */
void RefreshCharacterInfo(struct Character* character);