/*
The following commands need to be used in order to run:
1. gcc main.c structures.c functions.c -o SpaceXplorer.exe
2. .\SpaceXplorer.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "structures.h"
#include "functions.h"

// Global variables/function
int MIN_GRID_SIZE = 18;
int MAX_GRID_SIZE = 24;

char command[50];

bool getInput(void){
    printf("\n-> ");
    return fgets(command, sizeof command, stdin) != NULL;
}

int n;
Cell** cell;
Player player_info = {"JohnDoe", {0, 0}, 100, 0, 100};
Coord asteroid;

int main(){
    srand(time(NULL));
    if (mainMenu() == 0){
        // Only exits when enter is pressed
        printf("Press Enter to exit...");
        getchar();
        return 0;
    }

    command[0] = '\0'; // Clear the command string
    // Main Loop
    while(executecommand(command) && getInput()){
        system("cls");
    }

    // Only exits when enter is pressed
    printf("Press Enter to exit...");
    getchar();
    return 0;
}