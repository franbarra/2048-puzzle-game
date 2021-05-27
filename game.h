/*
 * Copyright © 2021 Francisco Barraguirre.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef __GAME_H__
#define __GAME_H__

#include <stdint.h>

// engine functions
void game_board_update(int direction, int *arr, uint8_t columns, uint8_t rows);
void game_board_tiles_move_direction(int direction, int *arr, uint8_t columns, uint8_t rows);
void game_board_tiles_add_pairs(int direction, int *arr, uint8_t columns, uint8_t rows);
void game_board_recursive_add_pairs(int direction, int counter, int *arr, uint8_t columns, uint8_t rows);
void game_board_spawn_new_values_random(int *arr, uint8_t columns, uint8_t rows);

// gui functions
void game_board_print(int *arr, uint8_t columns, uint8_t rows);

#endif
