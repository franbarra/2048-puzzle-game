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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <time.h>

#include "game.h"

// TODO: change cut condition of for loops from "i < columns * rows" to "i < sizeof(game_board)"

#define MATRIX_COLS 4
#define MATRIX_ROWS 4

int (*game_board)[MATRIX_COLS];
int (*game_board_previous)[MATRIX_COLS]; // use this to implement an undo function

// TODO: implement movement with arrow keys
enum movement_keys{KEY_UP=0, KEY_DOWN, KEY_LEFT, KEY_RIGHT};

uint32_t game_score = 0;
uint16_t game_board_tile_highest = 0;
uint8_t game_over = 0;

int main() {

    printf("%d\n", sizeof(*game_board));

    // we seed the random number generator
    // for now, we have a fixed generation for testing purposes, however
    // for production we would write srandr(time(NULL))
    srand(0.560123);

    // the scoreboard has to be a square matrix (n x n), otherwise malloc panics
    game_board = malloc(sizeof(*game_board) * MATRIX_ROWS);
    game_board_previous = malloc(sizeof(*game_board_previous) * MATRIX_ROWS);

    // zero the board
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for (uint8_t j = 0; j < MATRIX_COLS; j++) {
            game_board[i][j] = 0;
        }
    }

    // int ch;
    char ch;
    game_board_spawn_new_values_random(*game_board, MATRIX_COLS, MATRIX_ROWS);

    while (game_over == 0) {

        game_board_print(*game_board, MATRIX_COLS, MATRIX_ROWS);
        scanf("%c", &ch);
        printf("\nchar: %d\n", ch);
        int direction_entered = user_input_capture(ch);
        printf("\ndirec: %d\n", direction_entered);
        game_board_update(direction_entered, *game_board, *game_board_previous, MATRIX_COLS, MATRIX_ROWS);
    }

    free(game_board_previous);
    free(game_board);

    return 0;
}


void game_board_update(int direction, int *arr, int *prev_arr, uint8_t columns, uint8_t rows) {


    if (direction != KEY_UP &&
        direction != KEY_DOWN &&
        direction != KEY_LEFT &&
        direction != KEY_RIGHT) {

        printf("character not recognized: %d\n", direction);
        // we want to return early in case of an error
        return;
    }

    else {

        // we use memmove instead of memcpy in case these 2 objects overlap in memory
        memmove(prev_arr, arr, (columns * rows) * sizeof (int));

        game_board_tiles_move_direction(direction, arr, columns, rows);
        game_board_tiles_add_pairs(direction, arr, columns, rows);

        // in case the moving in a direction isn't possible (movement is "blocked"),
        // it shouldn't count as a valid move and therefore, *not* spawn new values
        if (array_is_equal(*game_board, *game_board_previous, columns * rows) == 0) {
            return;
        }
        game_board_print(*game_board, MATRIX_COLS, MATRIX_ROWS);
        game_board_spawn_new_values_random(*game_board, columns, rows);

    }
}


void game_board_tiles_move_direction(int direction, int *arr, uint8_t columns, uint8_t rows) {

    // printf("moving all tiles\n");

    if (direction == KEY_UP) {

        // we move tiles upwards, so we step through the rows 1 at a time
        for (uint8_t i = 0; i < rows; i++) {
            // to move one column at a time, we step 4 values since we have a 4x4 array
            for (uint8_t j = i; j < columns * rows; j += columns) {

                if (arr[j] == 0) {

                    for (uint8_t k = j + columns; k < columns * rows; k += columns) {
                        if (arr[k] != 0) {
                            arr[j] = arr[k];
                            arr[k] = 0;
                            break;

                        }
                    }
                }
            }
        }
    }

    else if (direction == KEY_DOWN) {

        // we step through the rows 1 at a time
        for (int8_t i = rows - 1; i >= 0; i--) {

            // to move one column at a time, we step 4 values since we have a 4x4 array
            // we start from the bottom-left corner of the array, because I find it easier to think about.
            for (int8_t j = ((columns * rows) - i) - 1; j >= i; j -= columns) {

                if (arr[j] == 0) {

                    for (int8_t k = j - columns; k >= 0; k -= columns) {
                        if (arr[k] != 0) {
                            arr[j] = arr[k];
                            arr[k] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }

    else if (direction == KEY_LEFT) {

        // we step through the rows one at a time, so we step 4 values forward
        for (int8_t i = 0; i <= ((columns * rows) - columns); i += columns) {

            for (int8_t j = 0; j < rows; j++) {

                if (arr[i + j] == 0) {

                    for (int8_t k = j + 1; k < rows; k++) {
                        if (arr[i + k] != 0) {
                            arr[i + j] = arr[i + k];
                            arr[i + k] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }

    else if (direction == KEY_RIGHT) {

        // we step through the rows one at a time, so we step 4 values forward, starting from the right
        for (int8_t i = rows - 1; i < columns * rows; i += columns) {

            // we start from the right of the game board
            for (int8_t j = 0; j < rows - 1; j++) {

                if (arr[i - j] == 0) {

                    for (int8_t k = j + 1; k < rows; k++) {

                        if (arr[i - k] != 0) {
                            arr[i - j] = arr[i - k];
                            arr[i - k] = 0;
                            break;

                        }
                    }
                }
            }
        }
    }

    else {

        printf("character not recognized: %d\n", direction);
        return;
    }

}

void game_board_tiles_add_pairs(int direction, int *arr, uint8_t columns, uint8_t rows) {


    // printf("adding pairs\n");

    if (direction == KEY_UP) {

        // we add tiles upwards, so we step through the rows 1 at a time
        for (uint8_t i = 0; i < rows; i++) {
            // to move one column at a time, we step 4 values since we have a 4x4 array
            for (uint8_t j = i; j < columns * rows; j += columns) {

                if (arr[j] != 0 && arr[j] == arr[j + columns]) {
                    // multiplying by 2 is faster than accessing memory like arr[j] = arr[j + columns]
                    arr[j] *= 2;
                    arr[j + columns] = 0;
                }
            }
        }
    }

    else if (direction == KEY_DOWN) {

        // we add tiles downwards, so we step through the rows 1 at a time
        for (int8_t i = rows - 1; i >= 0; i--) {
            // to move one column at a time, we step 4 values since we have a 4x4 array
            for (int8_t j = ((columns * rows) - i) - 1; j >= i; j -= columns) {

                if (arr[j] != 0 && arr[j] == arr[j - columns]) {
                    arr[j] *= 2;
                    arr[j - columns] = 0;
                }

            }
        }

    }

    else if (direction == KEY_LEFT) {

        // we step through rows at a time
        for (int8_t i = 0; i <= ((columns * rows) - columns); i += columns) {
            // we move one column at a time
            for (int8_t j = 0; j < rows - 1; j++) {

                if (arr[i + j] != 0 && arr[i + j] == arr[i + j + 1]) {
                    arr[i + j] *= 2;
                    arr[i + j + 1] = 0;
                }
            }
        }
    }

    else if (direction == KEY_RIGHT) {

        // we step through the rows one at a time, so we step 4 values forward, starting from the right
        for (int8_t i = rows - 1; i < columns * rows; i += columns) {

            // we start from the right of the game board
            for (int8_t j = 0; j < rows - 1; j++) {

                if (arr[i - j] != 0 && arr[i - j] == arr[i - j - 1]) {
                    arr[i - j] *= 2;
                    arr[i - j - 1] = 0;
                }
            }
        }
    }

    else {

        printf("oops, there was an error.");
        return;
    }

    game_board_tiles_move_direction(direction, arr, columns, rows);

}


void game_board_print(int *arr, uint8_t columns, uint8_t rows) {

    // here, 2 for loops are needed to give the adequate print format for 4x4 matrix
    printf("\n+-------+-------+-------+-------+\n");
    for (uint8_t i = 0; i < columns * rows; i += 4) {
        printf("|  ");
        for (uint8_t j = 0; j < rows; j++) {
            printf("%d  ", arr[i + j]);
            printf("  |  ");
        }
        printf("\n+-------+-------+-------+-------+\n");
    }
}


void game_board_spawn_new_values_random(int *arr, uint8_t columns, uint8_t rows) {

    uint8_t available_tiles = 0;
    for (size_t i = 0; i < columns * rows; i++) {
        if (arr[i] == 0) {
            available_tiles += 1;
        }
    }

    // printf("there are %d available tiles.\n", available_tiles);

    // we spawn a quantity of new values between 2 and 4 depending on the tiles available.
    for (size_t i = 0; i < (int)(available_tiles / 4); i++) {

        // we generate a random number between 0 and 1
        double num_probability = (double) rand() / (double) RAND_MAX;

        // we have a 80% chance of spawning a 2, and 10% chance for a 4.
        if (num_probability >= 0 && num_probability < 0.8) {

            // magic formula for generating random numbers between range
            // number = (rand() % (upper - lower + 1)) + lower
            uint8_t position_random = (rand() % (16 - 0 + 1)) + 0;

            // remember! we can't override existing values.
            if (arr[position_random] == 0) {
                arr[position_random] = 2;
            }
        }

        else if (num_probability >= 0.8 && num_probability < 1) {

            uint8_t position_random = (rand() % (16 - 0 + 1)) + 0;
            if (arr[position_random] == 0) {
                arr[position_random] = 4;
            }
        }
    }

}


void game_board_decision_undo(int *arr, int *prev_arr, uint8_t columns, uint8_t rows) {

    memmove(arr, prev_arr, (columns * rows));
}

int array_is_equal(int *arr_one, int *arr_two, int size) {

    for (int i = 0; i < size; i++) {
        if (arr_one[i] != arr_two[i]) {
            return 1;
        }
    }
    return 0;
}

// enum movement_keys user_input_capture(int ch) {
int user_input_capture(char ch) {

    // w, a, s, d and KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
    if (ch == 119) {
        return 0;

    } else if (ch == 115) {
        return 1;

    } else if (ch == 97) {
        return 2;

    } else if (ch == 100) {
        return 3;

    } else {
        return -1;
    }
}
