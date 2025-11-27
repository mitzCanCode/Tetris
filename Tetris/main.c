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


int main(int argc, const char * argv[]) {
    // Seeding rand
    srand((unsigned int)time(NULL));
    int blockCenterRow = 0, blockCenterColumn = 0; // h block coordinates in other words
    int blockRelativeCoordinates[4][2]; // The blocks 5x5 coordinates
    int blockBoardCoordinates[4][2]; // The blocks board coordinates
    char board[20][10]; // Array containing all the blocks
    char blockColor; // Color of the current block

    
    // Create block, do full rotation
//    blockColor = newBlock(blockCoordinates);
//    for (int i = 0; i < 5; i++) {
//        printBlock(blockCoordinates, blockColor, 1);
//        rotateBlock(blockCoordinates, blockColor);
//    }
    
    for (int i = 0; i < 5; i++) {
        
        blockColor = newBlock(blockRelativeCoordinates);
        
        
        generateBoard(board, &blockCenterRow, &blockCenterColumn);
        
        getBoardBlockCoordinates(blockRelativeCoordinates, blockCenterRow, blockCenterColumn, blockBoardCoordinates);
        
        printBoardColored(board, blockBoardCoordinates, blockColor);
        
    }
    
    return EXIT_SUCCESS;
}



// 10 x 20 Board
//    [
//     '', '', '', '', 'g', '', '', '', '', '',
//     '', '', '', '', 'h', '', '', '', '', '',
//     '', '', '', '', 'g', 'g', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     '', '', '', '', '', '', '', '', '', '',
//     ]
