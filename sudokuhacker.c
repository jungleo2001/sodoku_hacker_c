#include <stdio.h>
#include <stdbool.h>

#define N 9

// Function declarations

void printGrid(int (*grid)[N]);
bool isSafe(int (*grid)[N], int row, int col, int num);
bool solveSudoku(int (*grid)[N]);

// Function to print the Sodoku grid

void printGrid(int (*grid)[N]){
    for (int row = 0; row < N; row++){
        for (int col = 0; col < N; col++ )
            printf("%2d", grid[row][col]);
        printf("\n");
    }
}


// Function to check if a number can be placed in a given position

bool isSafe(int grid[N][N], int row, int col, int num){
    //Check if the number is already present in the row or column

    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    //Check if the number is already present in the 3x3 subgrid

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}


//Function to solve Sodoku unsing backtracking

bool solveSudoku(int grid[N][N]){
    int row, col;

    // Find an unassigned position

    bool found = false;
    for (row = 0; row < N; row++){
        for (col = 0; col < N; col++){
            if (grid [row][col] == 0){
                found = true;
                break;
            }
        }
        if (found)
            break;
    }

    //if no unassigned position is found, the Sudoku is solved
    if (!found)
        return true;

    // Try placing numbers from 1 to 9

    for (int num = 1; num <= 9; num ++){
        //check if the number can be placed in the current position
        if(isSafe(grid, row, col, num)) {
            //Place the number in the current position
            grid[row][col] = num;

            //Recursively solve the remaining grid
            if(solveSudoku(grid))
                return true;

            //If placing the number leads to an invalid solution, bactrack it

            grid[row][col] = 0;
        }
    }

    // If no number can be placed in the current position, bactrack it

    return false;
}

int main(){
    int grid[N][N] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    if (solveSudoku(grid))
        printGrid(grid);
    else
        printf("No solution exists\n");

    return 0;
}
