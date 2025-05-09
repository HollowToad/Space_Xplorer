/* Space Xplorer project - Cowan McVeigh @UWE - 23035003
Version 5.0
Date 09/05/2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define R 18 // Defining Rows to be 18 along
#define C 18 // Defining Columns to be 18 Down

#define Asteroid '*'
#define Fuel '!'
#define Empty '0'
#define Destination 'X'

void SpaceFieldArray(char Arr[R][C], int *DestinationRow, int *DestinationCol) {// This function decides how to populate the array with desired variables
    srand(time(NULL));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int x = rand() % 18;
            if (x < 2) Arr[i][j] = Asteroid; // This makes every 2 in 10 spaces an asteroid (20%)
            else if (x < 4) Arr[i][j] = Fuel; // This makes every 4 in 10 spaces a fuel (40%)
            else Arr[i][j] = Empty; // This makes every 5 in 10 spaces an empty space (50%)
        }
    }

    int Border = rand() % 4;// Places the destination on one of the border sides
    switch (Border) {
        case 0: *DestinationRow = 0; *DestinationCol = rand() % C; break; // Top
        case 1: *DestinationRow = R - 1; *DestinationCol = rand() % C; break; // Bottom
        case 2: *DestinationRow = rand() % R; *DestinationCol = 0; break; // Left
        case 3: *DestinationRow = rand() % R; *DestinationCol = C - 1; break; // Right
    }
    Arr[*DestinationRow][*DestinationCol] = Destination;

}



void FormSpace(char Arr[R][C], int moveRow, int moveCol) {// This function prints the game grid
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i == moveRow && j == moveCol) {
                printf("A ");// '0' is marking the player's position in the array, This line shows where they are
            }else {
                printf("%c ", Arr[i][j]); // This line displays what the prior function placed in this cell
         }
        }
        printf("\n"); //It then goes to the next row and displays the cells
    }
}
int main() {// The Game itself
    char Arr[R][C];
    int moveRow = R / 2, moveCol = C / 2;
    srand(time(NULL));
    int destinationRow, destinationCol;
    SpaceFieldArray(Arr, &destinationRow, &destinationCol);

    int fuel = 7;
    char *CurrentPos = &Arr[moveRow][moveCol];
    char movement;
    while (fuel > 0){
        system("cls"); // Clears the console
        FormSpace(Arr, moveRow, moveCol);// Receives the full generated array for the game
        printf("Fuel: %d\n", fuel); // HUD information
        printf("Move: (w = up/a = Left/s = Down/d = Right): "); //Key
        scanf(" %c", &movement);

        int NextRow = moveRow, NextCol = moveCol; //Creating non-defined variables that can be changed in the script.

        if (movement == 'w')  NextRow--; // How the movement works by incrementing the array up/down etc.
        else if (movement == 's') NextRow++;
        else if (movement == 'a') NextCol--;
        else if (movement == 'd') NextCol++;

        printf("DEBUG: Trying to move to (%d, %d): contains '%c'\n", NextRow, NextCol, Arr[NextRow][NextCol]);

        fflush(stdout);
        Sleep(1000);
        system("cls");


        if (NextRow < 0 || NextRow >= R || NextCol < 0 || NextCol >= C) {// Creating boundaries for the game
            printf("You can't flee the Mission!\n");
            continue;

        }

        CurrentPos = &Arr[NextRow][NextCol];

        if (*CurrentPos == Asteroid) {// Asterioid is the fail condition
            printf("You have been hit by an asteroid! Mission Failed!\n");
            break;
        } else {
            moveRow = NextRow;
            moveCol = NextCol;

            if (*CurrentPos == Fuel) {
                fuel += 5; // Adds fuel when you hit a Fuel space
                printf("You have collected fuel!\n");
                *CurrentPos = Empty; // Empties the space as the fuel is consumed
            }
            fuel--; // Makes it so that every move will consume a singular fuel unit
        }
        if (*CurrentPos == Destination){
            printf("You have been hit by a destination! Mission Success!\n");
            break;

        }
        Sleep(1300);
        system("cls");


    }
    if (fuel <= 0) {
        printf("You ran out of fuel... Game over.\n");
    }
    return 0;
}
