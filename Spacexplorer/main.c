/*
The following commands need to be used in order to run:
1. gcc main.c structures.c functions.c -o main.exe
2. .\main.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "structures.h"
#include "functions.h"

#define MIN_GRID_SIZE 18
#define MAX_GRID_SIZE 24

char command[50];

bool getInput(void){
    printf("\n-> ");
    return fgets(command, sizeof command, stdin) != NULL;
}

// Global variables
int n;
Cell** cell;
Player player_info = {"JohnDoe", {0, 0}, 100, 0, 100};
Coord asteroid;

int main(){
    srand(time(NULL));

    // Main menu setup. Load, New game and Check leaderboard systems    
    int choice = 0;
    do {
        system("cls");  // Clears screen if needed
        printf("--Main Menu--\n");
        printf(" 1. New Game\n");
        printf(" 2. Load Game\n");
        printf(" 4. Quit\n");
        getInput();

        char *ch = strtok(command, " \n");
        char *endptr;
        if (ch != NULL) {
            long num = strtol(ch, &endptr, 10);
            
            if (*endptr == '\0' && num > 0 && num < 5) {
                choice = (int) num;
                //printf("Choice: %d\n", num); // Debugging
            }
        }
    } while(choice != 1 && choice != 2 && choice != 3);
    
    if(choice == 1){
        printf("\nPlayer Name: ");
        fgets(player_info.name, sizeof player_info.name, stdin);
        
        // Removes any newline(\n) characters from the name.
        size_t len = strlen(player_info.name);
        if (len > 0 && player_info.name[len - 1] == '\n') {
            player_info.name[len - 1] = '\0';
        }

        system("cls");

        n = MIN_GRID_SIZE + rand() % (MAX_GRID_SIZE - MIN_GRID_SIZE + 1); // Random number between 18 and 24 determining grid size
        //printf("Initialized grid size\n"); // Debugging
        
        // Set the initial position of the player
        player_info.current_loc.x = rand() % n;
        player_info.current_loc.y = rand() % n;
    
        asteroid.x = rand() % n;
        asteroid.y = rand() % n;

        // Allocate some memory depending on grid size(n)
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
                } /*else if (x == asteroid.x && y == asteroid.y){
                    //printf("  A  ");
                }*/ else {
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
    } else if(choice == 2) {
        listSaveFiles();
        char filename[20];
        printf("Which file would you like to load (Include the .txt): ");
        fgets(filename, sizeof filename, stdin);

        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }

        loadGame(filename);

        system("cls");

        printf("Starting Co-ordinates: x: %d y: %d\n", player_info.current_loc.x, player_info.current_loc.y);


        printf(" ");
        for(int i = 0; i < n*5; i++){
            printf("_");
        }
        printf("\n");

        for(int y = 0; y < n; y++){
        
            printf("|");

            for(int x = 0; x < n; x++){
                if (x == player_info.current_loc.x && y == player_info.current_loc.y){
                    printf("  x  ");
                } /*else if (x == asteroid.x && y == asteroid.y){
                    //printf("  A  ");
                }*/ else {
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

    } else if(choice == 3) return 0;

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