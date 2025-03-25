/*
The following commands need to be used in order to run:
1. gcc main.c structures.c -o main.exe
2. .\main.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "structures.h"
#include "functions.h"

#define MIN_GRID_SIZE 18
#define MAX_GRID_SIZE 24

char command[50];

bool getInput(void){
    printf("\n-> ");
    return fgets(command, sizeof command, stdin) != NULL;
}

int n;
Cell** cell;
Player player_info = {"Henrique", {0, 0}, 100, 0, 100};
Coord asteroid;

int main(){
    srand(time(NULL));

    n = MIN_GRID_SIZE + rand() % (MAX_GRID_SIZE - MIN_GRID_SIZE + 1); // Random number between 18 and 24 determining grid size

    //player_info = (Player){"Henrique", {rand() % n, rand() % n}, 100, 0, 100}; // Starting conditions
    // Set the initial position of the player
    player_info.current_loc.x = rand() % n;
    player_info.current_loc.y = rand() % n;
    
    asteroid.x = rand() % n;
    asteroid.y = rand() % n;


    // Main menu setup. Load, New game and Check leaderboard systems


    cell = malloc(n * sizeof(Cell*));
    for (int i = 0; i < n; i++) {
        cell[i] = malloc(n * sizeof(Cell));
    }

    printf("Starting Co-ordinates: x: %d y: %d\n", player_info.current_loc.x, player_info.current_loc.y);


    printf(" ");
    for(int i = 0; i < n*5; i++){
        printf("_");
    }
    printf("\n");

    for(int y = 0; y < n; y++){
        
        printf("|");

        for(int x = 0; x < n; x++){ 
            cell[x][y].has_scrap = 0;
            cell[x][y].has_scrap = rand() % 2; // Randomly add scrap

            if (x == player_info.current_loc.x && y == player_info.current_loc.y){
                printf("  x  ");
            } else if (x == asteroid.x && y == asteroid.y){
                printf("  A  ");
            } else {
                printf(" [0] ");
            }
        }

        printf("|\n");
    }

    printf(" ");
    for(int i = 0; i < n*5; i++){
        printf("_");
    }
    printf("\n");


    // Main Loop
    while(executecommand(command) && getInput()){
        system("cls");
    }

    // Only exits when enter is pressed
    printf("Press Enter to exit...");
    getchar();
    return 0;
}