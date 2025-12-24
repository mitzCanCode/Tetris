
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
#define BLOCK_QUEUE_SIZE 4

void printBoard(char board[20][10], int blockBoardCoordinates[4][2], char blockColor, char queueColors[BLOCK_QUEUE_SIZE], int queueRelativeCoordinates[BLOCK_QUEUE_SIZE][4][2], long long int *totalLinesCleared, long long int *score) {
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
    
    // Create queueBoard: 20 rows x 5 cols
    char queueBoard[20][5];
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 5; j++)
            queueBoard[i][j] = '.'; // Fill empty
    
    // Fill queueBoard with queued blocks (stacked vertically)
    for (int q = 0; q < BLOCK_QUEUE_SIZE; q++) {
        int startRow = q * 5; // Each block uses 5 rows
        for (int k = 0; k < 4; k++) {
            int relRow = queueRelativeCoordinates[q][k][0];
            int relCol = queueRelativeCoordinates[q][k][1];
            int row = startRow + relRow;
            int col = relCol; // 0–4
            if (row >= 0 && row < 20 && col >= 0 && col < 5) {
                queueBoard[row][col] = queueColors[q];
            }
        }
    }
    
    // Print the board and queue
    for (int i = 0; i < 20; i++) {
        printf("\033[30m|\033[0m"); // Print first blocks left vertical line
        for (int j = 0; j < 10; j++) {
            char c = localBoard[i][j]; // Color of the current block

            int isBelowBlock = 0;

            // Loop over all block squares
            for (int k = 0; k < 4; k++) {
                int blockX = blockBoardCoordinates[k][0];
                int blockY = blockBoardCoordinates[k][1];

                // If same column and row is below block, mark it
                if (j == blockY && i > blockX) {
                    isBelowBlock = 1;
                    break;
                }
            }
        

            if (c == '.' && isBelowBlock) {
                printf("\033[90m█\033[30m|\033[0m"); // Gray for empty below block
            } else {
                switch(c) {
                    case 'p': printf("\033[35m█\033[30m|\033[0m"); break; // Magenta
                    case 'b': printf("\033[34m█\033[30m|\033[0m"); break; // Blue
                    case 'r': printf("\033[31m█\033[30m|\033[0m"); break; // Red
                    case 'y': printf("\033[33m█\033[30m|\033[0m"); break; // Yellow
                    case 'g': printf("\033[32m█\033[30m|\033[0m"); break; // Green
                    case 'o': printf("\033[91m█\033[30m|\033[0m"); break; // Bright red/orange
                    case 'c': printf("\033[36m█\033[30m|\033[0m"); break; // Cyan
                    case 'w': printf("\033[97m█\033[30m|\033[0m"); break; // White
                    default:  printf("\033[30m█\033[30m|\033[0m"); break; // Black
                }
            }
        }
        
        printf("  "); // Gap between board and queue
        
        // Print queueBoard
        for (int j = 0; j < 5; j++) {
            char c = queueBoard[i][j];
            if (i ==4) {
                printf("\033[34m==\033[0m");
            } else {
                switch(c) {
                    case 'p': printf("\033[35m█\033[30m|\033[0m"); break; // Magenta
                    case 'b': printf("\033[34m█\033[30m|\033[0m"); break; // Blue
                    case 'r': printf("\033[31m█\033[30m|\033[0m"); break; // Red
                    case 'y': printf("\033[33m█\033[30m|\033[0m"); break; // Yellow
                    case 'g': printf("\033[32m█\033[30m|\033[0m"); break; // Green
                    case 'o': printf("\033[91m█\033[30m|\033[0m"); break; // Bright red/orange
                    case 'c': printf("\033[36m█\033[30m|\033[0m"); break; // Cyan
                    case 'w': printf("\033[97m█\033[30m|\033[0m"); break; // White
                    default:  printf("\033[30m█\033[30m|\033[0m"); break; // Gray
                }
            }
        }
        
        if (i == 2) {
            printf(" Next Block");
        }
        
        printf("\n");
    }
    // Calculate the user level
    long long int level = *totalLinesCleared / 10;
    
    // Stats line
    printf("Score: %lld\tTotal lines cleared: %lld\tLevel: %lld\n", *score, *totalLinesCleared, level);
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

void applyBoard(char board[20][10], int blockBoardCoordinates[4][2], char blockColor, char queueColors[BLOCK_QUEUE_SIZE], int queueRelativeCoordinates[BLOCK_QUEUE_SIZE][4][2], long long int *totalLinesCleared, long long int *score) {
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
        // Make lines empty
        for (int i = 0; i < totalFullRows; i++) {
            for (int j = 0; j < 10; j++) board[fullRows[i]][j] = '.';
        }

        printBoard(board, blockBoardCoordinates, blockColor, queueColors, queueRelativeCoordinates, totalLinesCleared, score);
        usleep(delayPerFlashMs * 1000); // Add delay between flashes
        
        // Make lines white
        for (int i = 0; i < totalFullRows; i++) {
            for (int j = 0; j < 10; j++) board[fullRows[i]][j] = 'w';
        }
        printBoard(board, blockBoardCoordinates, blockColor, queueColors, queueRelativeCoordinates, totalLinesCleared, score);
        usleep(delayPerFlashMs * 1000); // Add delay between flashes
    }
    
    // Clear full lines from bottom up using a "write pointer"
    int writeRow = 19; // Start writing from the bottom
    for (int readRow = 19; readRow >= 0; readRow--) {
        int isFull = 1;
        for (int j = 0; j < 10; j++) {
            if (board[readRow][j] == '.') {
                isFull = 0;
                break;
            }
        }
        if (!isFull) {
            // Copy this row down to writeRow
            if (writeRow != readRow) {
                memcpy(board[writeRow], board[readRow], sizeof(board[readRow]));
            }
            writeRow--;
        }
    }
    
    // Fill all remaining rows above writeRow with empty cells
    for (int i = writeRow; i >= 0; i--) {
        for (int j = 0; j < 10; j++) board[i][j] = '.';
    }
    
    *totalLinesCleared = totalFullRows + *totalLinesCleared;
    
    // Calculate score
    int scoreToAdd = 0;
    
    // Calculate the user level
    long long int level = *totalLinesCleared / 10;

    switch (totalFullRows) {
        case 0:
            scoreToAdd = 0; break;
        case 1:
            scoreToAdd += 40 * (level + 1); break;
        case 2:
            scoreToAdd += 100 * (level + 1); break;
        case 3:
            scoreToAdd += 300 * (level + 1); break;
        case 4:
            scoreToAdd += 1200 * (level + 1); break;
        default:
            scoreToAdd = 0; break;
    }
    
    *score += scoreToAdd;
}
