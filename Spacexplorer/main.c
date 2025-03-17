#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int x, y;
}Coord;

typedef struct
{
    char name[15];
    Coord current_loc;
    int hp;
    int num_scrap;
    int oxygen; // 100% - 0%

}Player;

typedef struct
{
    int has_scrap; // 1 means it has scrap, 0 means it doesn't
}Cell;

int main(){
    srand(time(NULL));

    Player player_info = {{rand() % n, rand() % n}, 100, 0, 100}; // Starting conditions

    int n = 18 + rand() % 6; // Random number between 18 and 24 determining grid size
    
    Cell cell[n][n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){ 
            cell[i][j].has_scrap = 0;
            cell[i][j].has_scrap = rand() % 2; // Randomly add scrap
            
            if (i == player_info.current_loc.x and j == player_info.current_loc.y){
            	printf(" [x] ");
            }else{
            	printf(" [0] ");
            }
        }
        printf("\n");
    }

    return 0;
}