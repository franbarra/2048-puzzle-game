
#ifndef GAME_H__
#define GAME_H__


void game_board_update(int direction, int *arr, int columns, int rows);
void game_board_recursive_move_values(int direction, int k, int *arr, int columns, int rows);
void game_board_recursive_add_pairs(int direction, int counter, int *arr, int columns, int rows);

void game_board_print(int *arr, int columns, int rows);
void game_board_populate_random(int *arr, int columns, int rows);

#endif
