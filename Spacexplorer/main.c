#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <structures.h>

int main(){
    srand(time(NULL));

    int n = 18 + rand() % 6; // Random number between 18 and 24 determining grid size
    
    Player player_info = {{rand() % n, rand() % n}, 100, 0, 100}; // Starting conditions
    
    Cell cell[n][n];

    for(int i = 0; i < n*5; i++){
        printf("_");
    }
    
    printf("\n");

    for(int i = 0; i < n; i++){
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

    return 0;
}
