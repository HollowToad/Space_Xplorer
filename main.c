/* Space Xplorer project - Cowan McVeigh @UWE - 23035003
Version 1.0
Date 09/05/2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define R 25 // Defining Rows to be 3 along
#define C 25 // Defining Columns to be 3 Down

void SpaceFieldArray(int Arr[R][C], int max) // Function to fill arrays that use R and C with random 1s and 0s
{
    for (int i = 0; i < R; i++) { // for loop to generate the rows
        for (int j = 0; j < C; j++) { // Nested for loop to generate the column
            Arr[i][j] = (rand() % max); //inputs random numbers into the array
        }
    }
}


int main(){
    int Arr[R][C];
    SpaceFieldArray(Arr, 2);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("%d ", Arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}

