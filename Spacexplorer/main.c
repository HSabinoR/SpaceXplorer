/*
The following commands need to be used in order to run:
1. gcc main.c structures.c -o main.exe
2. .\main.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"

int main(){
    srand(time(NULL));

    int n = 18 + rand() % 6; // Random number between 18 and 24 determining grid size
    
    Player player_info = {"Henrique", {rand() % n, rand() % n}, 100, 0, 100}; // Starting conditions
    
    Cell cell[n][n];

    printf("x: %d y: %d\n", player_info.current_loc.x, player_info.current_loc.y);


    printf(" ");
    for(int i = 0; i < n*5; i++){
        printf("_");
    }
    printf("\n");

    for(int i = 0; i < n; i++){
        
        printf("|");

        for(int j = 0; j < n; j++){ 
            cell[i][j].has_scrap = 0;
            cell[i][j].has_scrap = rand() % 2; // Randomly add scrap
            
            if (i == player_info.current_loc.x && j == player_info.current_loc.y){
                printf(" [x] ");
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

    print_player(&player_info);


    // Only exits when enter is pressed
    printf("Press Enter to exit...");
    getchar();
    return 0;
}
