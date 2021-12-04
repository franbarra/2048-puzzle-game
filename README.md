
# 2048-puzzle-game

This is a popular game called "2048" whose objective is to merge blocks with the same value into ones with bigger values in a 4x4 grid of squares, that way increasing your score. You can, however, implement a 5x5 or 6x6 or bigger board just by changing the following expressions: `#define MATRIX_COLS 4` and `#define MATRIX_ROWS 4`. Defining a non-square matrix will *not* work, `MATRIX_COLS` and `MATRIX_ROWS` must have the same value.

## Rules of the Game

The game is very basic and does not have many rules:

+ You can move the squares in any of four directions: up, down, left and right (respectively used with the keys: `w`, `a`, `s` and `d`).
+ You can only merge blocks with the same value into one. For example, two blocks with a value of 2 may be merged; two blocks with a value of 32 may be merged.
+ Merged blocks take on the value of the blocks that were merged and multiplies it by 2. That is, if we merged two blocks with a value of 4, the new block has a value of 4 * 2: 8.
+ The game ends when there are no possible moves left for the user to do. If we filled the board and there was no way for us to merge two blocks into one, even with moving in any of the directions possible, the game would end. (Not implemented yet).

TODO: implement a score system.

## Installation

Dependencies:

>
> + gcc
> + make
>

You can install the game on your own machine with the following instructions:

    git clone https://github.com/franbarra/2048-puzzle-game.git
    cd 2048-puzzle-game
    make build && ./game

Two `make debug` and `make clean` scripts are also available if you wish to use them.

# License

Copyright © 2021 Francisco Barraguirre

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
