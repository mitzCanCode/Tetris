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
#include "blocks.h"
#include "board.h"
#define SPAWN_ROW 1
#define SPAWN_COLUMN 5

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


int main(int argc, const char * argv[]) {
    // Seeding rand
    srand((unsigned int)time(NULL));
    
    initTerminal();
    
    int blockCenterRow = 0, blockCenterColumn = 0; // h block coordinates in other words
    int blockRelativeCoordinates[4][2]; // The blocks 5x5 coordinates
    int blockBoardCoordinates[4][2]; // The blocks board coordinates
    char board[20][10]; // Array containing all the blocks
    char blockColor; // Color of the current block
    
    // Create board
    generateBoard(board, &blockCenterRow, &blockCenterColumn, SPAWN_ROW, SPAWN_COLUMN);
    // Create user block
    blockColor = newBlock(blockRelativeCoordinates);
    
    // Initialize flags
    int hitSomethingVertically = 0;
    
    int delay = 500000; // 0.5 seconds per downward move
    int interval = 50000; // 0.05 seconds per loop
    int counter = 0;
    
    
    while (1) {
        if (kbhit()) {
            int key = getch();
            if (key == 'a') {
                moveLeft(board, blockBoardCoordinates, &blockCenterColumn);
                getBoardBlockCoordinates(blockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
                printBoardColored(board, blockBoardCoordinates, blockColor);
            } else if (key == 'd') {
                moveRight(board, blockBoardCoordinates, &blockCenterColumn);
                getBoardBlockCoordinates(blockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
                printBoardColored(board, blockBoardCoordinates, blockColor);
            } else if (key == 'w') {
                rotateBlock(blockRelativeCoordinates, blockColor);
                getBoardBlockCoordinates(blockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
                printBoardColored(board, blockBoardCoordinates, blockColor);
            }
        }


        if (counter >= delay / interval) {
            // Move the block down
            hitSomethingVertically = moveDown(board, blockBoardCoordinates, &blockCenterRow);
            
            if (hitSomethingVertically) {
                // Store current board status
                applyBoard(board, blockBoardCoordinates, blockColor);
                
                // Reset block spawn point
                blockCenterRow = SPAWN_ROW;
                blockCenterColumn = SPAWN_COLUMN;
                
                // Create new block
                blockColor = newBlock(blockRelativeCoordinates);
                
                // Get board coordinates of the new block
                getBoardBlockCoordinates(blockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
                
                
                // Check if the block that was created over laps with any other blocks at spawn
                if (checkOverlap(board, blockBoardCoordinates)) {
                    printf("\nGame Over!\n");
                    break;
                }
            }
            counter = 0;
        }
        getBoardBlockCoordinates(blockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
        printBoardColored(board, blockBoardCoordinates, blockColor);

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
