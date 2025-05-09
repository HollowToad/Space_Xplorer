/* Space Xplorer project - Cowan McVeigh @UWE - 23035003
Version 1.0
Date 09/05/2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R 15 // Defining Rows to be 15 along
#define C 15 // Defining Columns to be 15 Down

#define Asteriod '*'
#define Fuel '!'
#define Empty ' '

void SpaceFieldArray(int Arr[R][C]) {// This function decides how to populate the array with desired variables
    srand(time(NULL));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int x = rand() % 10;
            if (x < 2) Arr[i][j] = Asteriod; // This makes every 2 in 10 spaces an asteroid (20%)
            else if (x < 5) Arr[i][j] = Fuel; // This makes every 3 in 10 spaces a fuel (30%)
            else Arr[i][j] = Empty; // This makes every 5 in 10 spaces an empty space (50%)
        }
    }

}

void FormSpace(char Arr[R][C], int moveRow, int moveCol) {// This function prints the game grid
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i == moveRow && j == moveCol) {
                printf("0 ");// '0' is marking the player's position in the array, This line shows where they are
            }else {
                printf("%c ", Arr[i][j]); // This line displays what the prior function placed in this cell
        }
        }
        printf("\n"); //It then goes to the next row and displays the cells
    }
}

