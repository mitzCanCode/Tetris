//
//  board.h
//  Tetris
//
//  Created by mitz on 27/11/25.
//

#ifndef BOARD_H
#define BOARD_H
#define BLOCK_QUEUE_SIZE 4


void printBoard(char board[20][10], int blockBoardCoordinates[4][2], char blockColor, char queueColors[BLOCK_QUEUE_SIZE], int queueRelativeCoordinates[BLOCK_QUEUE_SIZE][4][2], long long int *totalLinesCleared, long long int *score);

// Generate the board
void generateBoard(char board[20][10], int *blockCenterRow, int *blockCenterColumn, int blockCenterSpawnRow, int blockCenterSpawnColumn);

// Used to redraw the board keeping the blocks
void applyBoard(char board[20][10], int blockBoardCoordinates[4][2], char blockColor, char queueColors[BLOCK_QUEUE_SIZE], int queueRelativeCoordinates[BLOCK_QUEUE_SIZE][4][2], long long int *totalLinesCleared, long long int *score);

#endif
