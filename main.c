/* Space Xplorer project - Cowan McVeigh @UWE - 23035003
Version 3.0
Date 09/05/2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R 18 // Defining Rows to be 15 along
#define C 18 // Defining Columns to be 15 Down

#define Asteriod '*'
#define Fuel '!'
#define Empty '0'

void SpaceFieldArray(int Arr[R][C]) {// This function decides how to populate the array with desired variables
    srand(time(NULL));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int x = rand() % 10;
            if (x < 2) Arr[i][j] = Asteriod; // This makes every 2 in 10 spaces an asteroid (20%)
            else if (x < 3) Arr[i][j] = Fuel; // This makes every 3 in 10 spaces a fuel (30%)
            else Arr[i][j] = Empty; // This makes every 5 in 10 spaces an empty space (50%)
        }
    }

}

void FormSpace(char Arr[R][C], int moveRow, int moveCol) {// This function prints the game grid
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i == moveRow && j == moveCol) {
                printf("X ");// '0' is marking the player's position in the array, This line shows where they are
            }else {
                printf("%c ", Arr[i][j]); // This line displays what the prior function placed in this cell
        }
        }
        printf("\n"); //It then goes to the next row and displays the cells
    }
}
int main() {// The Game itself
    char Arr[R][C];
    SpaceFieldArray(Arr);

    int fuel = 5;
    int moveRow = 0;
    int moveCol = 0;
    char *CurrentPos = &Arr[moveRow][moveCol];
    char movement;
    while (fuel > 0){
        system("cls"); // Clears the console
        FormSpace(Arr, moveRow, moveCol);// Receives the full generated array for the game
        printf("Fuel: %d\n", fuel); // HUD information
        printf("Move: (w = up/a = Left/s = Down/d = Right): "); //Key
        scanf("%c", &movement);

        int NextRow = moveRow, NextCol = moveCol; //Creating non-defined variables that can be changed in the script.

        if (movement == 'w')  NextRow--; // How the movement works by incrementing the array up/down etc.
        else if (movement == 's') NextRow++;
        else if (movement == 'a') NextCol--;
        else if (movement == 'd') NextCol++;

        if (NextRow < 0 || NextRow >= R || NextCol < 0 || NextCol >= C) {// Creating boundaries for the game
            printf("You can't flee the Mission!\n");
            continue;

        }

        CurrentPos = &Arr[NextRow][NextCol];

        if (*CurrentPos == Asteriod) {// Asterioid is the fail condition
            printf("You have been hit by an asteroid! Mission Failed!\n");
            break;
        } else {
            moveRow = NextRow;
            moveCol = NextCol;

            if (*CurrentPos == Fuel) {
                fuel += 3; // Adds fuel when you hit a Fuel space
                printf("You have collected fuel!\n");
                *CurrentPos = Empty; // Empties the space as the fuel is consumed
            }
            fuel--; // Makes it so that every move will consume a singular fuel unit
        }


    }
    if (fuel <= 0) {
        printf("You ran out of fuel... Game over.\n");
    }
    return 0;
}
