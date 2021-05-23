
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>

#include "game.h"

#define COLS 4
#define ROWS 4

int (*game_board)[COLS];

int main() {

    //int ch;
    //initscr();
    //raw();
    //noecho();
    //cbreak();


    // the scoreboard has to be a square matrix (n x n), otherwise malloc panics
    game_board = malloc(sizeof(*game_board) * ROWS);

    game_board_populate_random(*game_board, COLS, ROWS);

    printf("valor de game_board[0][0]: %d\n", game_board[0][0]);
    printf("valor de game_board[0][1]: %d\n", game_board[0][1]);
    printf("valor de game_board[0][2]: %d\n", game_board[0][2]);
    printf("valor de game_board[0][3]: %d\n", game_board[0][3]);
    printf("valor de game_board[1][0]: %d\n", game_board[1][0]);
    printf("valor de game_board[1][1]: %d\n", game_board[1][1]);
    printf("valor de game_board[1][2]: %d\n", game_board[1][2]);
    printf("valor de game_board[1][3]: %d\n", game_board[1][3]);
    printf("valor de game_board[2][0]: %d\n", game_board[2][0]);
    printf("valor de game_board[2][1]: %d\n", game_board[2][1]);
    printf("valor de game_board[2][2]: %d\n", game_board[2][2]);
    printf("valor de game_board[2][3]: %d\n", game_board[2][3]);
    printf("valor de game_board[3][0]: %d\n", game_board[3][0]);
    printf("valor de game_board[3][1]: %d\n", game_board[3][1]);
    printf("valor de game_board[3][2]: %d\n", game_board[3][2]);
    printf("valor de game_board[3][3]: %d\n", game_board[3][3]);

    game_board_print(*game_board, COLS, ROWS);

    //ch = getch();

    game_board_update(0, *game_board, COLS, ROWS);
    //refresh();

    // game_board_print(*game_board, COLS, ROWS);

    //getch();
    //endwin();
    //
    free(game_board);

    return 0;
}

void game_board_update(int direction, int *arr, int columns, int rows) {

    if (direction == 0) {

        // TODO: Fix this game logic

        int z = 0; // counter for the recursive function. we want to step forward 4 positions at a time
        // first we move all values towards 'direction'.
        for (int i = 0; i < columns; i++) {
            printf("COUNTER Z: %d\n", z);
            game_board_recursive_move_values(direction, z, arr, columns, rows);
            game_board_print(arr, columns, rows);
            z++;
        }

        z = 0; // reset the counter
        // then we recursively sum all pairs of values
        for (int i = 0; i < columns; i++) {
            printf("COUNTER Z: %d\n", z);
            game_board_recursive_add_pairs(direction, z, arr, columns, rows);
            game_board_print(arr, columns, rows);
            z++;
        }
    }
}

void game_board_recursive_move_values(int direction, int counter, int *arr, int columns, int rows) {

    printf("moving all values\n");
    int k = counter;
    printf("k: %d, counter: %d\n", k, counter);
    if (direction == 0) {

        if (k >= columns * rows) {
            printf("if where k >= cols * rows. k: %d\n", k);
            return;
        }

        else if (k + columns >= columns * rows) {
            printf("if where k + columns >= cols * rows. k + columns: %d\n", k + columns);
            return;
        }

        if (arr[k] == 0) {

            printf("first if where arr[k] == 0\n");
            printf("moving arr[k + columns]: %d up to arr[k]: %d where k: %d\n", arr[k + columns], arr[k], k);
            arr[k] = arr[k + columns];
            arr[k + columns] = 0;
            game_board_recursive_move_values(direction, counter + columns, arr, columns, rows);
        }

        game_board_recursive_move_values(direction, counter + columns, arr, columns, rows);
    }
}

void game_board_recursive_add_pairs(int direction, int counter, int *arr, int columns, int rows) {

    printf("recursively adding pairs\n");
    int k = counter;
    printf("k: %d, counter: %d\n", k, counter);
    if (direction == 0) {

        // we check manually if we're at the end of the array
        if (k >= (columns * rows)) {
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
            game_board_recursive_move_values(direction, 0, arr, columns, rows);
        }

        game_board_recursive_move_values(direction, counter + columns, arr, columns, rows);
        game_board_recursive_add_pairs(direction, counter + columns, arr, columns, rows);
    }
}

void game_board_print(int *arr, int columns, int rows) {

    // here, 2 for loops are needed to give the adequate print format
    printf("\n+---+---+---+---+\n");
    for (int i = 0; i < columns * rows; i += 4) {
        printf("| ");
        for (int j = 0; j < rows; j++) {
            // if you just put i + j then arr[0][1] == arr[1][0] which is what you don't want
            printf("%d", arr[i + j]);
            printf(" | ");
        }
        printf("\n+---+---+---+---+\n");
    }

}

void game_board_populate_random(int *arr, int columns, int rows) {

    // since an array is contiguous in memory, we don't need 2 for loops
    for (int j = 0; j < columns * rows; j++) {
        // magic formula for generating random even numbers in range of [0, 2n]
        // where (rand() % (n + 1)) * 2
        arr[j] = (rand() % (2 + 1)) * 2;
    }
}
