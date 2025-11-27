//
//  board.c
//  Tetris
//
//  Created by mitz on 27/11/25.
//

#include <stdlib.h>
#include <stdio.h>

void printBoard(char board[20][10], int blockCoordinates[4][2], int userBlockCoordinates[2], char blockColor) {
    char localBoard[20][10];
    // Copy the main board into localBoard
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            localBoard[i][j] = board[i][j];
        }
    }
    
    // Place the block into localBoard
    for (int k = 0; k < 4; k++) {
        int boardX = blockCoordinates[k][0] + userBlockCoordinates[0];
        int boardY = blockCoordinates[k][1] + userBlockCoordinates[1];

        // Bounds check
        if (boardX >= 0 && boardX < 20 && boardY >= 0 && boardY < 10) {
            localBoard[boardX][boardY] = blockColor;
        }
    }
    
    // Print the board
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c", localBoard[i][j]);
        }
        printf("\n");
    }
}
