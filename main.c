/* Space Xplorer project - Cowan McVeigh @UWE - 23035003
Version 7.0
Date 09/05/2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define R 18 // Defining Rows to be 18 along
#define C 18 // Defining Columns to be 18 Down

#define Asteroid '*' // The characters used in the game
#define Fuel '!'
#define Empty '0'
#define Destination 'X'
#define Max_Asteroids 50

typedef struct { //Struct for the characteristics of the asteroids
    int row;
    int col;
    int dRow;
    int dCol;
} AsteroidInfo;

AsteroidInfo asteroids[Max_Asteroids];
int asteroidsCount = 0;

void SpaceFieldArray(char Arr[R][C], int *DestinationRow, int *DestinationCol) {// This function decides how to populate the array with desired variables
    srand(time(NULL));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int x = rand() % 18;
            if (x < 2 && asteroidsCount < Max_Asteroids) {// Added the new asteroids into the function
                asteroids[asteroidsCount].row = i;// This will generate the asteroids and all their relevant information
                asteroids[asteroidsCount].col = j;
                asteroids[asteroidsCount].dRow = 1;
                asteroids[asteroidsCount].dCol = 0;
                asteroidsCount++;
            } else if (x < 4) {
                Arr[i][j] = Fuel;// % of Fuel spawns
            } else {
                Arr[i][j] = Empty;
            }
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
void CS() { // I had to use this Clear Screen function to make my code more efficient as cls was too slow
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}


void FormSpace(char Arr[R][C], int moveRow, int moveCol) {// This function prints the game grid
    int startRow = moveRow - 2;
    int startCol = moveCol - 2;

    for (int i = startRow; i < startRow + 5; i++) {// Only shows 5x5 around the player
        for (int j = startCol; j < startCol + 5; j++) {
            if (i >= 0 && i < R && j >= 0 && j < C) {
                if (i == moveRow && j == moveCol) {
                    printf("A "); //Players position
                } else {
                    printf("%c ", Arr[i][j]);
                }
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void MoveAsteroids(char Arr[R][C]) {
    for (int i = 0; i < asteroidsCount; i++) {
        int oldRow = asteroids[i].dRow;
        int oldCol = asteroids[i].dCol;
        int newRow = asteroids[i].dRow;
        int newCol = asteroids[i].dCol;

        if (newRow < 0 || newRow >= R) {
            asteroids[i].dRow *= -1;
            newRow = oldRow + asteroids[i].dRow;
        }
        if (newCol < 0 || newCol >= C) {
            asteroids[i].dCol *= -1;
            newCol = oldCol + asteroids[i].dCol;
        }
        if (Arr[newRow][newCol] == Destination) {
            continue;
        }
        Arr[oldRow][oldCol] = Empty;
        Arr[newRow][newCol] = Asteroid;
        asteroids[i].dRow = newRow;
        asteroids[i].dCol = newCol;
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




    }
    if (fuel <= 0) {
        printf("You ran out of fuel... Game over.\n");
    }
    return 0;
}
