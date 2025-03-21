#include "functions.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "structures.h"

void executeScan(Player *player, Cell *cell[n][n]){
   
   Coord scannable_cells[3][3] = {
      { {player->current_loc.x - 1, player->current_loc.y - 1}, {player->current_loc.x, player->current_loc.y - 1}, {player->current_loc.x + 1, player->current_loc.y - 1} },
      { {player->current_loc.x - 1, player->current_loc.y}, {player->current_loc.x, player->current_loc.y}, {player->current_loc.x + 1, player->current_loc.y} },
      { {player->current_loc.x - 1, player->current_loc.y + 1}, {player->current_loc.x, player->current_loc.y + 1}, {player->current_loc.x + 1, player->current_loc.y + 1} }
  };

  for(int i = scannable_cells[0][0].x; i < scannable_cells[0][2].x+1; i++){
        
   printf("|");

   for(int j = scannable_cells[0][0].y; j < scannable_cells[0][0].y+1; j++){ 
      
      if (i == player->current_loc.x && j == player->current_loc.y){
         printf(" [x] ");
      }else if(cell[i][j]->has_scrap == 1){
         printf(" [#] ");
      }else{
         printf(" [0] ");
      }
   }
   printf("|\n");
   }


}

bool executecommand(char *input, Player *p, Cell *cell[n][n]){
    char *verb = strtok(input, " \n");
    char *noun = strtok(NULL, " \n");

    if (verb != NULL)
    {
       if (strcmp(verb, "quit") == 0) {
          return false;
       }
       else if (strcmp(verb, "scan") == 0) {
          printf("Scanning...\n");
          executeScan(&p, &cell);
       }
       else if (strcmp(verb, "go") == 0) {
          printf("It's too dark to go anywhere.\n");
       }
       else {
          printf("I don't know how to '%s'.\n", verb);
       }
    }
    return true;
}