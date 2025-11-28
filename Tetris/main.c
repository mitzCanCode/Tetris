//
//  main.c
//  Tetris
//
//  Created by mitz on 27/11/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "blocks.h"
#include "board.h"


#define SPAWN_ROW 1
#define SPAWN_COLUMN 5
#define BLOCK_QUEUE_SIZE 4


#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

void initTerminal(void) {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode & echo
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int kbhit(void) {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

int getch(void) {
    char c;
    if (read(STDIN_FILENO, &c, 1) < 0) return -1;
    return c;
}

void removeBlockFromQueue(char queueColors[BLOCK_QUEUE_SIZE], int queueRelativeCoordinates[BLOCK_QUEUE_SIZE][4][2]) {
    // shift everything left
    for (int i = 1; i < BLOCK_QUEUE_SIZE; i++) {
        // Move the colors
        queueColors[i - 1] = queueColors[i];
        
        // copy the 4 coordinate pairs
        memcpy( queueRelativeCoordinates[i - 1], queueRelativeCoordinates[i], sizeof(queueRelativeCoordinates[i]) );
    }
}

void addBlockToQueue(char queueColors[BLOCK_QUEUE_SIZE], int queueRelativeCoordinates[BLOCK_QUEUE_SIZE][4][2]) {
    queueColors[BLOCK_QUEUE_SIZE - 1] = newBlock(queueRelativeCoordinates[BLOCK_QUEUE_SIZE - 1]);
}

void initQueue(char queueColors[BLOCK_QUEUE_SIZE], int queueRelativeCoordinates[BLOCK_QUEUE_SIZE][4][2]) {
    for (int i = 0; i < BLOCK_QUEUE_SIZE; i++) {
        queueColors[i] = newBlock(queueRelativeCoordinates[i]);
    }
}


void getBlockFromQueue(char *currentBlockColor, char queueColors[BLOCK_QUEUE_SIZE], int currentBlockRelativeCoordinates[4][2], int queueRelativeCoordinates[BLOCK_QUEUE_SIZE][4][2]) {
    *currentBlockColor = queueColors[0];
    memcpy( currentBlockRelativeCoordinates, queueRelativeCoordinates[0], sizeof(queueRelativeCoordinates[0]) );
}


int main(int argc, const char * argv[]) {
    // Seeding rand
    srand((unsigned int)time(NULL));
    
    initTerminal();
    
    char board[20][10]; // Array containing all the blocks
    
    // Queue variables
    char queueColors[BLOCK_QUEUE_SIZE]; // The queue containing the future blocks colors
    int queueRelativeCoordinates[BLOCK_QUEUE_SIZE][4][2]; // The queue containing the future blocks relative coordinates
    
    
    // Current block variables
    int blockBoardCoordinates[4][2]; // The blocks board coordinates
    int currentBlockRelativeCoordinates[4][2]; // The blocks 5x5 coordinates
    int blockCenterRow = 0, blockCenterColumn = 0; // h block coordinates in other words
    char currentBlockColor = '\0'; // Color of the current block
    
    // Create board
    generateBoard(board, &blockCenterRow, &blockCenterColumn, SPAWN_ROW, SPAWN_COLUMN);
    
    // Initialiaze queue
    initQueue(queueColors, queueRelativeCoordinates);
    
    // Pull block from queue
    getBlockFromQueue(&currentBlockColor, queueColors, currentBlockRelativeCoordinates, queueRelativeCoordinates);
    // Remove the block we just got
    removeBlockFromQueue(queueColors, queueRelativeCoordinates);
    // Add another block (because one was just removed) back to the queue
    addBlockToQueue(queueColors, queueRelativeCoordinates);
    
    // Initialize vertical contact flag
    int hitSomethingVertically = 0;
    
    // Initialize time flags
    int delay = 500000; // 0.5 seconds per downward move
    int interval = 50000; // 0.05 seconds per loop
    int counter = 0;
    
    
    while (1) {
        if (kbhit()) {
            int key = getch();
            if (key == 'a') {
                moveLeft(board, blockBoardCoordinates, &blockCenterColumn);
                getBoardBlockCoordinates(currentBlockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
                printBoard(board, blockBoardCoordinates, currentBlockColor, queueColors, queueRelativeCoordinates);
            } else if (key == 'd') {
                moveRight(board, blockBoardCoordinates, &blockCenterColumn);
                getBoardBlockCoordinates(currentBlockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
                printBoard(board, blockBoardCoordinates, currentBlockColor, queueColors, queueRelativeCoordinates);

            } else if (key == 'w') {
                if ( canRotate(currentBlockRelativeCoordinates, currentBlockColor, board, blockCenterRow, blockCenterColumn) ) {
                    rotateBlock(currentBlockRelativeCoordinates, currentBlockColor);
                    getBoardBlockCoordinates(currentBlockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
                    printBoard(board, blockBoardCoordinates, currentBlockColor, queueColors, queueRelativeCoordinates);
                }
            }
            else if (key == 's') {
                // Move the block down unitl something is hit
                hitSomethingVertically = moveDown(board, blockBoardCoordinates, &blockCenterRow);
                while (!hitSomethingVertically) {
                    getBoardBlockCoordinates(currentBlockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
                    hitSomethingVertically = moveDown(board, blockBoardCoordinates, &blockCenterRow);
                }
                
                // Manage the hit happening
                applyBoard(board, blockBoardCoordinates, currentBlockColor, queueColors, queueRelativeCoordinates); // Store current board status
                
                // Spawn new block
                blockCenterRow = SPAWN_ROW;
                blockCenterColumn = SPAWN_COLUMN;
                
                // Pull block from queue
                getBlockFromQueue(&currentBlockColor, queueColors, currentBlockRelativeCoordinates, queueRelativeCoordinates);
                // Remove the block we just got
                removeBlockFromQueue(queueColors, queueRelativeCoordinates);
                // Add new block to the queue
                addBlockToQueue(queueColors, queueRelativeCoordinates);
                
                getBoardBlockCoordinates(currentBlockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
                
                // Check if the block that was created over laps with any other blocks at spawn
                if (checkOverlap(board, blockBoardCoordinates)) {
                    printf("\nGame Over!\n");
                    break;
                }
                
                printBoard(board, blockBoardCoordinates, currentBlockColor, queueColors, queueRelativeCoordinates);

                // Reset flags
                counter = 0;
                hitSomethingVertically = 0;
                
                // Skip final print & sleep this iteration
                continue;
                
            }
        }
        
        
        if (counter >= delay / interval) {
            // Move the block down
            hitSomethingVertically = moveDown(board, blockBoardCoordinates, &blockCenterRow);
            
            if (hitSomethingVertically) {
                // Store current board status
                applyBoard(board, blockBoardCoordinates, currentBlockColor, queueColors, queueRelativeCoordinates);
                
                // Reset block spawn point
                blockCenterRow = SPAWN_ROW;
                blockCenterColumn = SPAWN_COLUMN;
                
                // Pull block from queue
                getBlockFromQueue(&currentBlockColor, queueColors, currentBlockRelativeCoordinates, queueRelativeCoordinates);
                // Remove the block we just got
                removeBlockFromQueue(queueColors, queueRelativeCoordinates);
                // Add new block to the queue
                addBlockToQueue(queueColors, queueRelativeCoordinates);
                
                // Get board coordinates of the new block
                getBoardBlockCoordinates(currentBlockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
                
                
                // Check if the block that was created over laps with any other blocks at spawn
                if (checkOverlap(board, blockBoardCoordinates)) {
                    printf("\nGame Over!\n");
                    break;
                }
            }
            counter = 0;
        }
        getBoardBlockCoordinates(currentBlockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
        printBoard(board, blockBoardCoordinates, currentBlockColor, queueColors, queueRelativeCoordinates);
        
        usleep(interval);
        counter++;
        
    }
    
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    return EXIT_SUCCESS;
}




//printBoardColored(board, blockBoardCoordinates, blockColor);
//moveLeft(board, blockBoardCoordinates, &blockCenterColumn);
//printBoardColored(board, blockBoardCoordinates, blockColor);


// 10 x 20 Board
//    [
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', 'h', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     ]


//        for (int i = 0; i<10; i++) { // Move 4 times to the left
//            int result = moveLeft(board, blockBoardCoordinates, &blockCenterColumn); // Move the block left
//            if (result) {
//                printf("\nError!\n");
//            }
//
//            getBoardBlockCoordinates(blockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates); // Recalculate board coords
//            printf("\n\n");
//            printBoardColored(board, blockBoardCoordinates, blockColor);
//
//        }
//        for (int i = 0; i<2; i++) { // Move 2 times to the right
//            int result = moveRight(board, blockBoardCoordinates, &blockCenterColumn); // Move the block right
//            if (result) {
//                printf("\nError!\n");
//            }
//
//            getBoardBlockCoordinates(blockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates); // Recalculate board coords
//            printf("\n\n");
//            printBoardColored(board, blockBoardCoordinates, blockColor);
//
//        }
