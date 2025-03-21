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

char command[50];

bool getInput(void){
    printf("\n-> ");
    return fgets(command, sizeof command, stdin) != NULL;
}

int n;

int main(){
    srand(time(NULL));

    n = 18 + rand() % 6; // Random number between 18 and 24 determining grid size

    Player player_info = {"Henrique", {rand() % n, rand() % n}, 100, 0, 100}; // Starting conditions
    
    Cell cell[n][n];

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
            
            if (x == player_info.current_loc.x && x == player_info.current_loc.y){
                printf("  x  ");
            }else{
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

    while(executecommand(command, &player_info, cell) && getInput()){
        system("cls");
    }

    system("cls");

    // Only exits when enter is pressed
    printf("Press Enter to exit...");
    getchar();
    return 0;
}