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

#include <stdlib.h>
//#include <time.h>
#include <ncurses.h>

#include "game.h"

#define MATRIX_COLS 4
#define MATRIX_ROWS 4

#define __KEY_UP 0
#define __KEY_DOWN 1
#define __KEY_LEFT 2
#define __KEY_RIGHT 3


int (*game_board)[MATRIX_COLS];

// use this to implement an undo function
// int (*previous_game_board)[MATRIX_COLS];

int main() {

    // we seed the random number generator
    srand(0.560123);

    //int ch;
    //initscr();
    //raw();
    //noecho();
    //cbreak();


    // the scoreboard has to be a square matrix (n x n), otherwise malloc panics
    game_board = malloc(sizeof(*game_board) * MATRIX_ROWS);
    // previous_game_board = malloc(sizeof(*game_board) * MATRIX_ROWS);

    game_board_spawn_new_values_random(*game_board, MATRIX_COLS, MATRIX_ROWS);

    game_board_print(*game_board, MATRIX_COLS, MATRIX_ROWS);

    game_board_tiles_move_direction(KEY_UP, *game_board, MATRIX_COLS, MATRIX_ROWS);
    game_board_print(*game_board, MATRIX_COLS, MATRIX_ROWS);

    game_board_tiles_move_direction(KEY_DOWN, *game_board, MATRIX_COLS, MATRIX_ROWS);
    game_board_print(*game_board, MATRIX_COLS, MATRIX_ROWS);

    game_board_tiles_move_direction(KEY_LEFT, *game_board, MATRIX_COLS, MATRIX_ROWS);
    game_board_print(*game_board, MATRIX_COLS, MATRIX_ROWS);

    game_board_tiles_move_direction(KEY_RIGHT, *game_board, MATRIX_COLS, MATRIX_ROWS);
    game_board_print(*game_board, MATRIX_COLS, MATRIX_ROWS);

    //ch = getch();

    //game_board_update(KEY_UP, *game_board, MATRIX_COLS, MATRIX_ROWS);
    //game_board_update(KEY_DOWN, *game_board, MATRIX_COLS, MATRIX_ROWS);
    //refresh();

    // game_board_print(*game_board, COLS, ROWS);

    //getch();
    //endwin();
    //
    free(game_board);

    return 0;
}


// TODO: copy the game_board into previous_game_board before updating game_board
void game_board_update(int direction, int *arr, uint8_t columns, uint8_t rows) {


    if (direction == KEY_UP) {


    }

    else if (direction == KEY_DOWN) {


    }

    else if (direction == KEY_LEFT) {

    }

    else if (direction == KEY_RIGHT) {

    }

    else {

        printf("character not recognized: %d\n", direction);
        // we want to return early in case of an error
        return;
    }

    game_board_spawn_new_values_random(*game_board, columns, rows);
    game_board_print(*game_board, columns, rows);
}


void game_board_tiles_move_direction(int direction, int *arr, uint8_t columns, uint8_t rows) {

    printf("moving all tiles\n");

    if (direction == KEY_UP) {

        // we move tiles upwards, so we step through the rows 1 at a time
        for (uint8_t i = 0; i < rows; i++) {
            // to move one column at a time, we step 4 values since we have a 4x4 array
            for (uint8_t j = i; j < columns * rows; j += columns) {

                printf("value of i: %d, value of j: %d, arr[j]: %d\n", i, j, arr[j]);

                if (arr[j] == 0) {

                    for (uint8_t k = j + columns; k < columns * rows; k += columns) {
                        // printf("k: %d\n", k);
                        if (arr[k] != 0) {
                            // printf("value of k: %d, value of i: %d, arr[k]: %d\n", k, i, arr[k]);
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

            printf("i: %d\n", i);

            // to move one column at a time, we step 4 values since we have a 4x4 array
            // we start from the bottom-left corner of the array, because I find it easier to think about.
            for (int8_t j = ((columns * rows) - i) - 1; j >= i; j -= columns) {
                printf("j: %d\n", j);

                printf("value of i: %d, value of j: %d, arr[j]: %d\n", i, j, arr[j]);

                if (arr[j] == 0) {

                    for (int8_t k = j - columns; k >= 0; k -= columns) {
                        printf("k: %d\n", k);
                        if (arr[k] != 0) {
                            printf("value of j: %d, value of k: %d, arr[k]: %d\n", j, k, arr[k]);
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
            printf("i: %d\n", i);

            for (int8_t j = 0; j < rows; j++) {

                if (arr[i + j] == 0) {
                    printf("i: %d, j: %d, arr[i + j]: %d\n", i, j, arr[i + j]);

                    for (int8_t k = j + 1; k < rows; k++) {
                        printf("k: %d\n", k);
                        if (arr[i + k] != 0) {
                            printf("value of i: %d, value of k: %d, arr[k]: %d\n", i, k, arr[i + k]);
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
            printf("i: %d\n", i);

            // we start from the right of the game board
            for (int8_t j = 0; j < rows; j++) {

                if (arr[i - j] == 0) {

                    for (int8_t k = j + 1; k < rows; k++) {
                        printf("k: %d\n", k);

                        if (arr[i - k] != 0) {
                            printf("value of i: %d, value of k: %d, arr[k]: %d\n", i, k, arr[i + k]);
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
    }

}

// TODO: implement UP, DOWN, LEFT and RIGHT directions
void game_board_tiles_add_pairs(int direction, int *arr, uint8_t columns, uint8_t rows) {

}


// TODO: implement DOWN, LEFT and RIGHT directions
void game_board_recursive_add_pairs(int direction, int counter, int *arr, uint8_t columns, uint8_t rows) {

    printf("recursively adding pairs\n");
    int k = counter;
    printf("k: %d, counter: %d\n", k, counter);

    if (direction == KEY_UP) {

        // we check manually if we're at the end of the array
        if (k >= columns * rows) {
            printf("if where k >= cols * rows. k: %d\n", k);
            return;
        }

        // we don't want to end up outside of the array
        else if (k + columns >= columns * rows) {
            printf("if where k + columns >= cols * rows. k + columns: %d\n", k + columns);
            return;
        }

        if (arr[k] == arr[k + columns] && arr[k] != 0) {

            printf("second if where arr[k] == arr[k + cols]\n");
            printf("k: %d, cols: %d, arr[k] = %d and arr[k + cols] = %d\n", k, columns, arr[k], arr[k + columns]);
            arr[k] *= 2;
            arr[k + columns] = 0;
            // now we need to move the values again because of the new zeroes
            game_board_recursive_move_values(direction, counter + columns, arr, columns, rows);
        }

        game_board_recursive_add_pairs(direction, counter + columns, arr, columns, rows);
    }

    else if (direction == KEY_DOWN) {

        // we check manually if we're at the __start__ since we began at the bottom-right (the end)
        if (k < 0) {
            printf("if where k < 0. k: %d\n", k);
            return;
        }

        else if (k - columns < 0) {
            printf("if where k - columns < 0. k - columns: %d\n", k - columns);
            return;
        }

        if (arr[k] == arr[k - columns] && arr[k] != 0) {
            printf("if where arr[k] == arr[k - columns].");
            printf("k: %d, arr[k] = %d and arr[k - columns] = %d]\n", k, arr[k], arr[k - columns]);
            arr[k] *= 2;
            arr[k - columns] = 0;
            // now we move the values again
            game_board_recursive_move_values(direction, counter - columns, arr, columns, rows);
        }

        game_board_recursive_add_pairs(direction, counter - columns, arr, columns, rows);

    }
}

void game_board_print(int *arr, uint8_t columns, uint8_t rows) {

    // here, 2 for loops are needed to give the adequate print format for 4x4 matrix
    printf("\n+---+---+---+---+\n");
    for (uint8_t i = 0; i < columns * rows; i += 4) {
        printf("| ");
        for (uint8_t j = 0; j < rows; j++) {
            printf("%d", arr[i + j]);
            printf(" | ");
        }
        printf("\n+---+---+---+---+\n");
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
