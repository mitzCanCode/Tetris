//
//  blocks.c
//  Tetris
//
//  Created by mitz on 27/11/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


// Fucntion to create a block
char newBlock(int blockCoordinates[4][2]) {
    int choice = rand() % 7;
    printf("Chosen block: %d\n", choice);
    char blockColor;
    // Block coordinates: Index 0 = x, Index 1 = y
    // First block is always center block
    switch (choice) {
        case 0: // T block
            // . T .
            // T T T
            blockCoordinates[0][0] = 2; blockCoordinates[0][1] = 2; // First block
            blockCoordinates[1][0] = 1; blockCoordinates[1][1] = 2; // Second block
            blockCoordinates[2][0] = 2; blockCoordinates[2][1] = 1; // Third block
            blockCoordinates[3][0] = 2; blockCoordinates[3][1] = 3; // Fourth block
            blockColor = 'p';
            break;

        case 1: // J block
            // J . .
            // J J J
            blockCoordinates[0][0] = 2; blockCoordinates[0][1] = 2; // First block
            blockCoordinates[1][0] = 1; blockCoordinates[1][1] = 1; // Second block
            blockCoordinates[2][0] = 2; blockCoordinates[2][1] = 1; // Third block
            blockCoordinates[3][0] = 2; blockCoordinates[3][1] = 3; // Fourth block
            blockColor = 'b';
            break;

        case 2: // L block
            // . . L
            // L L L
            blockCoordinates[0][0] = 2; blockCoordinates[0][1] = 2; // First block
            blockCoordinates[1][0] = 1; blockCoordinates[1][1] = 3; // Second block
            blockCoordinates[2][0] = 2; blockCoordinates[2][1] = 1; // Third block
            blockCoordinates[3][0] = 2; blockCoordinates[3][1] = 3; // Fourth block
            blockColor = 'o';
            break;

        case 3: // O block
            // O O
            // O O
            blockCoordinates[0][0] = 1; blockCoordinates[0][1] = 1; // First block
            blockCoordinates[1][0] = 1; blockCoordinates[1][1] = 2; // Second block
            blockCoordinates[2][0] = 2; blockCoordinates[2][1] = 1; // Third block
            blockCoordinates[3][0] = 2; blockCoordinates[3][1] = 2; // Fourth block
            blockColor = 'y';
            break;

        case 4: // S block
            // . S S
            // S S .
            blockCoordinates[0][0] = 2; blockCoordinates[0][1] = 2; // First block
            blockCoordinates[1][0] = 1; blockCoordinates[1][1] = 2; // Second block
            blockCoordinates[2][0] = 1; blockCoordinates[2][1] = 3; // Third block
            blockCoordinates[3][0] = 2; blockCoordinates[3][1] = 1; // Fourth block
            blockColor = 'g';
            break;

        case 5: // Z block
            // Z Z .
            // . Z Z
            blockCoordinates[0][0] = 2; blockCoordinates[0][1] = 2; // First block
            blockCoordinates[1][0] = 1; blockCoordinates[1][1] = 1; // Second block
            blockCoordinates[2][0] = 1; blockCoordinates[2][1] = 2; // Third block
            blockCoordinates[3][0] = 2; blockCoordinates[3][1] = 3; // Fourth block
            blockColor = 'r';
            break;

        case 6: // I block
            // I I I I
            blockCoordinates[0][0] = 1; blockCoordinates[0][1] = 1; // First block
            blockCoordinates[1][0] = 1; blockCoordinates[1][1] = 0; // Second block
            blockCoordinates[2][0] = 1; blockCoordinates[2][1] = 2; // Third block
            blockCoordinates[3][0] = 1; blockCoordinates[3][1] = 3; // Fourth block
            blockColor = 'c';
            break;

        default: // Fallback to T block
            blockCoordinates[0][0] = 2; blockCoordinates[0][1] = 2; // First block
            blockCoordinates[1][0] = 1; blockCoordinates[1][1] = 2; // Second block
            blockCoordinates[2][0] = 2; blockCoordinates[2][1] = 1; // Third block
            blockCoordinates[3][0] = 2; blockCoordinates[3][1] = 3; // Fourth block
            blockColor = 'p';
            break;
    }
    return blockColor;
}




void rotateBlock(int blockCoordinates[4][2], char blockColor) {
    if (blockColor == 'y') return; // O block does not rotate

    // Create 5x5 local grid
    char mat[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            mat[i][j] = '.';

    // Fill in the block positions
    for (int k = 0; k < 4; k++) {
        mat[blockCoordinates[k][0]][blockCoordinates[k][1]] = blockColor;
    }

    // Rotate the 5x5 matrix 90 degrees clockwise
    // Transpose
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            char tmp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = tmp;
        }
    }
    // Reverse each row
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 / 2; j++) {
            char tmp = mat[i][j];
            mat[i][j] = mat[i][5 - 1 - j];
            mat[i][5 - 1 - j] = tmp;
        }
    }

    // Extract new coordinates
    int idx = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (mat[i][j] != '.') {
                blockCoordinates[idx][0] = i;
                blockCoordinates[idx][1] = j;
                idx++;
            }
        }
    }
}

// Function to check if rotation is possible within the field
int canRotate(int blockCoordinates[4][2], char blockColor, char board[20][10], int userBlockCoordinates[2]) {
    if (blockColor == 'y') return 1; // O block does not rotate

    // Create 5x5 local grid
    char mat[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            mat[i][j] = '.';

    for (int k = 0; k < 4; k++)
        mat[blockCoordinates[k][0]][blockCoordinates[k][1]] = blockColor;

    // Rotate the 5x5 matrix 90 degrees clockwise
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            char tmp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = tmp;
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 / 2; j++) {
            char tmp = mat[i][j];
            mat[i][j] = mat[i][5 - 1 - j];
            mat[i][5 - 1 - j] = tmp;
        }
    }

    // Check if rotated block fits on the board
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (mat[i][j] != '.') {
                int boardX = i + userBlockCoordinates[0];
                int boardY = j + userBlockCoordinates[1];
                if (boardX < 0 || boardX >= 20 || boardY < 0 || boardY >= 10) return 0;
                if (board[boardX][boardY] != '.') return 0;
            }
        }
    }

    return 1;
}

void printBlock(int blockCoordinates[4][2], char blockColor, int printCoordinates) {
    char display[5][5];

    // Initialize display with empty cells
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            display[i][j] = '.';
        }
    }

    // Fill in blocks based on coordinates
    for (int k = 0; k < 4; k++) {
        int x = blockCoordinates[k][0];
        int y = blockCoordinates[k][1];
        if (x >= 0 && x < 5 && y >= 0 && y < 5) { // safe bounds check
            display[x][y] = blockColor;
        }
    }

    // Print the display
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c", display[i][j]);
        }
        printf("\n");
    }

    // Optionally print coordinates
    if (printCoordinates) {
        printf("Used Coordinates:\n");
        for (int k = 0; k < 4; k++) {
            printf("Block %d: (%d, %d)\n", k + 1, blockCoordinates[k][0], blockCoordinates[k][1]);
        }
        printf("\n");
    }
}

// Function used to get the actual block coordinates for the board
void getBoardBlockCoordinates(int blockRelativeCoordinates[4][2], int blockCenterRow, int blockCenterColumn, int blockBoardCoordinates[4][2]) {
    int centerX = blockRelativeCoordinates[0][0];
    int centerY = blockRelativeCoordinates[0][1];
    
    for (int k = 0; k < 4; k++) {
        int boardX = blockCenterRow + (blockRelativeCoordinates[k][0] - centerX);
        int boardY = blockCenterColumn + (blockRelativeCoordinates[k][1] - centerY);
        blockBoardCoordinates[k][0] = boardX;
        blockBoardCoordinates[k][1] = boardY;
    }
}



int checkOverlap(char board[20][10], int blockBoardCoordinates[4][2]) {
    for (int k = 0; k<4; k++) {
        int row = blockBoardCoordinates[k][0]; // Get block row
        int column = blockBoardCoordinates[k][1]; // Get block column
        if (board[row][column] != '.') {
            return 1; // Overlap detected since there was a block different than nothing
        }
    }
    return 0;
}

int moveLeft(char board[20][10], int blockBoardCoordinates[4][2], int *blockCenterColumn) {
    int tempBlockBoardCoordinates[4][2];  // Test left move first on block board coordinates before moving in case move left isnt possible

    // Move all the blocks columns to the left
    for (int i = 0; i < 4; i++) {
        tempBlockBoardCoordinates[i][1] = blockBoardCoordinates[i][1] - 1;
        if (tempBlockBoardCoordinates[i][1] < 0) {
            printf("\nTrying to move out of left bounds\n");
            return 1; // Trying to move out of left bounds
        }
        tempBlockBoardCoordinates[i][0] = blockBoardCoordinates[i][0]; // Store vertical too
    }
    if (checkOverlap(board, tempBlockBoardCoordinates)) { // Check if any overlaps occur
        printf("\nCant move left due to block blocking the way (overlap)\n");
        return 1; // Cant move left due to block blocking the way (overlap)
    }
    *blockCenterColumn -= 1;
    return 0;
}


int moveRight(char board[20][10], int blockBoardCoordinates[4][2], int *blockCenterColumn) {
    int tempBlockBoardCoordinates[4][2];  // Test right move first on block board coordinates before moving in case move right isnt possible

    // Move all the blocks columns to the right
    for (int i = 0; i < 4; i++) {
        tempBlockBoardCoordinates[i][1] = blockBoardCoordinates[i][1] + 1;
        if (tempBlockBoardCoordinates[i][1] > 19) {
            return 1; // Trying to move out of right bounds
        }
        tempBlockBoardCoordinates[i][0] = blockBoardCoordinates[i][0]; // Store vertical too
    }
    if (checkOverlap(board, tempBlockBoardCoordinates)) { // Check if any overlaps occur
        return 1; // Cant move right due to block blocking the way (overlap)
    }
    *blockCenterColumn += 1;
    return 0;
}

