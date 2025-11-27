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
    int blockCoordinates[4][2];
    char board[20][10];
    char blockColor;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j] = '.';
        }
    }
    // Array containing all the blocks current locations
    //  Index 0: x
    //  Index 1: y
    blockColor = newBlock(blockCoordinates);
    

    for (int k = 0; k<20; k++) {
        for (int i = 0; i < 5; i++){
            printBlock(blockCoordinates, blockColor, 1);
            rotateBlock(blockCoordinates, blockColor);
        }
        blockColor = newBlock(blockCoordinates);

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
