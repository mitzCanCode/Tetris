//
//  board.c
//  Tetris
//
//  Created by mitz on 27/11/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void printBoardColored(char board[20][10], int blockBoardCoordinates[4][2], char blockColor) {
    printf("\033[H\033[J");
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
                case 'p': printf("\033[35m█\033[30m|\033[0m"); break; // Magenta
                case 'b': printf("\033[34m█\033[30m|\033[0m"); break; // Blue
                case 'r': printf("\033[31m█\033[30m|\033[0m"); break; // Red
                case 'y': printf("\033[33m█\033[30m|\033[0m"); break; // Yellow
                case 'g': printf("\033[32m█\033[30m|\033[0m"); break; // Green
                case 'o': printf("\033[91m█\033[30m|\033[0m"); break; // Bright red/orange
                case 'c': printf("\033[36m█\033[30m|\033[0m"); break; // Cyan
                case 'w': printf("\033[97m█\033[30m|\033[0m"); break; // White
                default:  printf("\033[90m█\033[30m|\033[0m"); break; // Gray
            }
        }
        printf("\n");
    }
}


void printBoard(char board[20][10], int blockBoardCoordinates[4][2], char blockColor) {
    printf("\033[H\033[J");
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



void generateBoard(char board[20][10], int *blockCenterRow, int *blockCenterColumn, int blockCenterSpawnRow, int blockCenterSpawnColumn) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j] = '.';
        }
    }
    
    // Pointers are used to return back to actual vars
    *blockCenterRow = blockCenterSpawnRow; // Player block row number
    *blockCenterColumn = blockCenterSpawnColumn; // Player block column number
}

void applyBoard(char board[20][10], int blockBoardCoordinates[4][2], char blockColor) {
    for (int k = 0; k < 4; k++) {
        // Unpacking block coordinates
        int boardX = blockBoardCoordinates[k][0];
        int boardY = blockBoardCoordinates[k][1];
        
        // Bounds check
        if (boardX >= 0 && boardX < 20 && boardY >= 0 && boardY < 10) {
            board[boardX][boardY] = blockColor;
        }
    }
    
    int flashes = 3;
    int totalDurationMs = 1000; // 1 second total
    int delayPerFlashMs = totalDurationMs / (flashes * 2); // 2 states per flash: colored & cleared
    int totalFullRows = 0;
    int fullRows[20];
    
    // Find non empty lines
    for (int i = 0; i < 20; i++) {
        int emptyFound = 0;
        for (int j = 0; j < 10; j++) {
            if (board[i][j] == '.') {
                emptyFound = 1;
                break;
            }
        }
        if (emptyFound != 1) { // If empty wasnt found (aka line was full)
            fullRows[totalFullRows++] = i; // Store non empty row and increase full row count
        }
    }
    // Flash Lines
    for (int k = 0; k < 3; k++) { // Flash lines 3 times
        // Make lines white
        for (int i = 0; i < totalFullRows; i++) {
            for (int j = 0; j < 10; j++) board[fullRows[i]][j] = 'w';
        }
        printBoardColored(board, blockBoardCoordinates, blockColor);
        usleep(delayPerFlashMs * 1000); // Add delay between flashes

        // Make lines white
        for (int i = 0; i < totalFullRows; i++) {
            for (int j = 0; j < 10; j++) board[fullRows[i]][j] = '.';
        }
        printBoardColored(board, blockBoardCoordinates, blockColor);
        usleep(delayPerFlashMs * 1000); // Add delay between flashes
    }

    // Clear full lines
    for (int i = 0; i < totalFullRows; i++) {
        int row = fullRows[i];
        
        // Shift all rows above this row down by one
        for (int k = row; k > 0; k--) {
            memcpy(board[k], board[k-1], sizeof(board[k]));
        }
        
        // Fill the top row with empty cells
        for (int j = 0; j < 10; j++) board[0][j] = '.';
        
        // After shifting, all rows below have moved down by 1
        for (int m = i + 1; m < totalFullRows; m++) {
            fullRows[m]++; // Move the remaining full row indices down
        }
    }
}






