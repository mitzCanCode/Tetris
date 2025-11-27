//
//  board.c
//  Tetris
//
//  Created by mitz on 27/11/25.
//

#include <stdlib.h>
#include <stdio.h>

void printBoardColored(char board[20][10], int blockBoardCoordinates[4][2], char blockColor) {
    char localBoard[20][10];
    // Copy the main board into localBoard
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            localBoard[i][j] = board[i][j];
        }
    }
    
    for (int k = 0; k < 4; k++) {
        // Unpacking block coordinates
        int boardX = blockBoardCoordinates[k][0];
        int boardY = blockBoardCoordinates[k][1];
        
        // Bounds check
        if (boardX >= 0 && boardX < 20 && boardY >= 0 && boardY < 10) {
            localBoard[boardX][boardY] = blockColor;
        }
    }
    
    // Print the board with colors
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            char c = localBoard[i][j];
            switch(c) {
                case 'p': printf("\033[35m▧\033[0m"); break; // Magenta
                case 'b': printf("\033[34m▧\033[0m"); break; // Blue
                case 'r': printf("\033[31m▧\033[0m"); break; // Red
                case 'y': printf("\033[33m▧\033[0m"); break; // Yellow
                case 'g': printf("\033[32m▧\033[0m"); break; // Green
                case 'o': printf("\033[91m▧\033[0m"); break; // Bright red/orange
                case 'c': printf("\033[36m▧\033[0m"); break; // Cyan
                default:  printf("\033[90m■\033[0m"); break; // Gray
            }
        }
        printf("\n");
    }
}


void printBoard(char board[20][10], int blockBoardCoordinates[4][2], char blockColor) {
    char localBoard[20][10];
    // Copy the main board into localBoard
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            localBoard[i][j] = board[i][j];
        }
    }
    
    for (int k = 0; k < 4; k++) {
        // Unpacking block coordinates
        int boardX = blockBoardCoordinates[k][0];
        int boardY = blockBoardCoordinates[k][1];
        
        // Bounds check
        if (boardX >= 0 && boardX < 20 && boardY >= 0 && boardY < 10) {
            localBoard[boardX][boardY] = blockColor;
        }
    }
    
    
    // Print the board with colors
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c", localBoard[i][j]);
        }
        printf("\n");
    }
}



void generateBoard(char board[20][10], int *blockCenterRow, int *blockCenterColumn) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j] = '.';
        }
    }
    
    board[1][5] = 'h';
    // Pointer used to return back to actual vars
    *blockCenterRow = 1;
    *blockCenterColumn = 5;
}

