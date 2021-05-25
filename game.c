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
#include <ncurses.h>

#include "game.h"

#define MATRIX_COLS 4
#define MATRIX_ROWS 4

#define __KEY_UP 0;
#define __KEY_DOWN 1;
#define __KEY_LEFT 2;
#define __KEY_RIGHT 3;

int (*game_board)[MATRIX_COLS];

int main() {

    int ch;
    //initscr();
    //raw();
    //noecho();
    //cbreak();


    // the scoreboard has to be a square matrix (n x n), otherwise malloc panics
    game_board = malloc(sizeof(*game_board) * MATRIX_ROWS);

    game_board_populate_random(*game_board, MATRIX_COLS, MATRIX_ROWS);

    printf("value of game_board[0][0]: %d\n", game_board[0][0]);
    printf("value of game_board[0][1]: %d\n", game_board[0][1]);
    printf("value of game_board[0][2]: %d\n", game_board[0][2]);
    printf("value of game_board[0][3]: %d\n", game_board[0][3]);
    printf("value of game_board[1][0]: %d\n", game_board[1][0]);
    printf("value of game_board[1][1]: %d\n", game_board[1][1]);
    printf("value of game_board[1][2]: %d\n", game_board[1][2]);
    printf("value of game_board[1][3]: %d\n", game_board[1][3]);
    printf("value of game_board[2][0]: %d\n", game_board[2][0]);
    printf("value of game_board[2][1]: %d\n", game_board[2][1]);
    printf("value of game_board[2][2]: %d\n", game_board[2][2]);
    printf("value of game_board[2][3]: %d\n", game_board[2][3]);
    printf("value of game_board[3][0]: %d\n", game_board[3][0]);
    printf("value of game_board[3][1]: %d\n", game_board[3][1]);
    printf("value of game_board[3][2]: %d\n", game_board[3][2]);
    printf("value of game_board[3][3]: %d\n", game_board[3][3]);

    game_board_print(*game_board, MATRIX_COLS, MATRIX_ROWS);

    //ch = getch();

    game_board_update(KEY_UP, *game_board, MATRIX_COLS, MATRIX_ROWS);
    game_board_update(KEY_DOWN, *game_board, MATRIX_COLS, MATRIX_ROWS);
    //refresh();

    // game_board_print(*game_board, COLS, ROWS);

    //getch();
    //endwin();
    //
    free(game_board);

    return 0;
}

void game_board_update(int direction, int *arr, uint8_t columns, uint8_t rows) {


    int z = 0; // counter for the recursive function. we want to step forward 4 positions at a time

    if (direction == KEY_UP) {

        z = 0;

        // first we move all values towards 'direction'.
        for (size_t i = 0; i < columns; i++) {
            printf("z: %d, \"for\" line: %d\n", z, __LINE__);
            game_board_recursive_move_values(direction, z, arr, columns, rows);
            game_board_print(arr, columns, rows);
            z++;
        }

        z = 0; // reset the counter
        // then we recursively sum all pairs of values
        for (size_t i = 0; i < columns; i++) {
            printf("z: %d, \"for\" line: %d\n", z, __LINE__);
            game_board_recursive_add_pairs(direction, z, arr, columns, rows);
            game_board_print(arr, columns, rows);
            z++;
        }
    }

    else if (direction == KEY_DOWN) {

        // we start from the bottom-right corner
        z = 15;

        // we move values downwards
        for (size_t i = 0; i < columns; i++) {
            printf("z: %d, \"for\" line: %d\n", z, __LINE__);
            game_board_recursive_move_values(direction, z, arr, columns, rows);
            game_board_print(arr, columns, rows);
            z--;
        }

        z = 15;
        for (size_t i = 0; i < columns; i++) {
            printf("z: %d, \"for\" line: %d\n", z, __LINE__);
            game_board_recursive_add_pairs(direction, z, arr, columns, rows);
            game_board_print(arr, columns, rows);
            z--;
        }
    }

    else if (direction == KEY_LEFT) {

    }

    else if (direction == KEY_RIGHT) {

    }

    else {
        printf("character not recognized: %d\n", direction);
    }
}

// TODO: implement DOWN, LEFT and RIGHT directions
// FIXME: DOWN direction, which doesn't update correctly if there are 2 zeroes consecutively in a column
void game_board_recursive_move_values(int direction, int counter, int *arr, uint8_t columns, uint8_t rows) {

    printf("moving all values\n");

    if (direction == KEY_UP) {

        int k = counter; // we need to store the value passed onto the function
        printf("k: %d, counter: %d\n", k, counter);

        if (k >= columns * rows) {
            printf("if where k >= cols * rows. k: %d\n", k);
            return;
        }

        else if (k + columns >= columns * rows) {
            printf("if where k + columns >= cols * rows. k + columns: %d\n", k + columns);
            return;
        }

        if (arr[k] == 0 && arr[k + columns] != 0) {

            printf("first if where arr[k] == 0\n");
            printf("moving arr[k + columns]: %d up to arr[k]: %d where k: %d\n", arr[k + columns], arr[k], k);
            arr[k] = arr[k + columns];
            arr[k + columns] = 0;
        }

        game_board_recursive_move_values(direction, counter + columns, arr, columns, rows);
    }

    else if (direction == KEY_DOWN) {

        int k = counter;
        printf("k: %d, counter: %d\n", k, counter);

        if (k < 0) {
            printf("if where k < 0. k: %d\n", k);
            return;
        }

        else if (k - columns < 0) {
            printf("if where k - columns < 0. k - columns: %d\n", k - columns);
            return;
        }

        if (arr[k] == 0 && arr[k - columns] != 0) {

            printf("first if where arr[k] == 0\n");
            printf("moving arr[k - columns]: %d down to arr[k]: %d where k: %d\n", arr[k - columns], arr[k], k);
            arr[k] = arr[k - columns];
            arr[k - columns] = 0;
        }

        game_board_recursive_move_values(direction, counter - columns, arr, columns, rows);
    }

    else if (direction == KEY_LEFT) {

    }

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
            arr[k] += arr[k + columns];
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
            arr[k] += arr[k - columns];
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
    for (size_t i = 0; i < columns * rows; i += 4) {
        printf("| ");
        for (size_t j = 0; j < rows; j++) {
            // if you just put i + j then arr[0][1] == arr[1][0] which is what you don't want
            printf("%d", arr[i + j]);
            printf(" | ");
        }
        printf("\n+---+---+---+---+\n");
    }

}

void game_board_populate_random(int *arr, uint8_t columns, uint8_t rows) {

    // since an array is contiguous in memory, we don't need 2 for loops
    for (size_t j = 0; j < columns * rows; j++) {
        // magic formula for generating random even numbers in range of [0, 2n]
        // where (rand() % (n + 1)) * 2
        arr[j] = (rand() % (2 + 1)) * 2;
    }
}
