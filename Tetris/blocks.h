//
//  blocks.h
//  Tetris
//
//  Created by mitz on 27/11/25.
//

#ifndef BLOCKS_H
#define BLOCKS_H

// Creates a new Tetris block and fills blockCoordinates[][]
// Returns the block's color
char newBlock(int blockCoordinates[4][2]);

// Rotates the block 90 degrees clockwise
void rotateBlock(int blockCoordinates[4][2], char blockColor);

// Checks if the block can rotate at the given position on the board
int canRotate(int blockCoordinates[4][2], char blockColor, char board[20][10], int userBlockCoordinates[2]);

// Prints the block in a 5x5 grid for debugging, optionally prints coordinates
void printBlock(int blockCoordinates[4][2], char blockColor, int printCoordinates);

// Function used to get the actual block coordinates for the board
void getBoardBlockCoordinates(int blockRelativeCoordinates[4][2], int blockCenterRow, int blockCenterColumn, int blockBoardCoordinates[4][2]);

// Used to move a block left
int moveLeft(char board[20][10], int blockBoardCoordinates[4][2], int *blockCenterColumn);

// Used to move block right
int moveRight(char board[20][10], int blockBoardCoordinates[4][2], int *blockCenterColumn);

// Used to check if a block overlaps another block
int checkOverlap(char board[20][10], int blockBoardCoordinates[4][2]);

#endif
