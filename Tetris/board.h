//
//  board.h
//  Tetris
//
//  Created by mitz on 27/11/25.
//

#ifndef BOARD_H
#define BOARD_H

void printBoardColored(char board[20][10], int blockBoardCoordinates[4][2], char blockColor);

// Prints the entire game board
void printBoard(char board[20][10], int blockBoardCoordinates[4][2], char blockColor);

// Generate the board
void generateBoard(char board[20][10], int *blockCenterRow, int *blockCenterColumn);

#endif
