#include "functions.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "structures.h"

void executeScan(Player *player, Cell (*cell)[n]){
   
   Coord scannable_cells[3][3] = {
      { {player->current_loc.x - 1, player->current_loc.y - 1}, {player->current_loc.x, player->current_loc.y - 1}, {player->current_loc.x + 1, player->current_loc.y - 1} },
      { {player->current_loc.x - 1, player->current_loc.y}, {player->current_loc.x, player->current_loc.y}, {player->current_loc.x + 1, player->current_loc.y} },
      { {player->current_loc.x - 1, player->current_loc.y + 1}, {player->current_loc.x, player->current_loc.y + 1}, {player->current_loc.x + 1, player->current_loc.y + 1} }
   };

   for(int i = 0; i < 3; i++){
        
      printf("|");

      for(int j = 0; j < 3; j++){ 
         
         int x = scannable_cells[i][j].x;
         int y = scannable_cells[i][j].y;

         if (y < 0 || y >= n) {
            printf("-----"); // Out of bounds
         } else if(x < 0 || x >= n){
            printf("  <  ");
         } else if (x == player->current_loc.x && y == player->current_loc.y) {
            printf("  x  "); // Player's position
         } else if (cell[x][y].has_scrap) {
            printf(" [#] "); // Scrap detected
         } else {
            printf(" [0] "); // Empty cell
         }
      }
      printf("|\n");
   }
   int x = player->current_loc.x;
   int y = player->current_loc.y;

   if (cell[y][x].has_scrap == 1){
      printf("\nThe cell you're on has some space junk!");
   }
}

void executeFly(Player *p, char *noun){
   if(noun != NULL){
      if (strcmp(noun, "up") == 0 && p->current_loc.y > 0){
         p->current_loc.y -= 1;
         printf("Flying up\n");
         printf("New Co-ordinates: x: %d y: %d", p->current_loc.x, p->current_loc.y);
      } else if (strcmp(noun, "down") == 0 && p->current_loc.y < n-1){
         p->current_loc.y += 1;
         printf("Flying down\n");
         printf("New Co-ordinates: x: %d y: %d", p->current_loc.x, p->current_loc.y);
      } else if (strcmp(noun, "left") == 0 && p->current_loc.x > 0){
         p->current_loc.x -= 1;
         printf("Flying left\n");
         printf("New Co-ordinates: x: %d y: %d", p->current_loc.x, p->current_loc.y);
      } else if (strcmp(noun, "right") == 0 && p->current_loc.x < n-1){
         p->current_loc.x += 1;
         printf("Flying right\n");
         printf("New Co-ordinates: x: %d y: %d", p->current_loc.x, p->current_loc.y);
      } else{
         printf("Can't fly in that direction");
      }
   }
}

void executeShow(Player *p, char *noun){
   if(noun != NULL){
      if (strcmp(noun, "map") == 0){
         printf(" ");
         for(int i = 0; i < n*5; i++){
            printf("_");
         }
         printf("\n");

         for(int y = 0; y < n; y++){
        
            printf("|");

            for(int x = 0; x < n; x++){             
               if (x == p->current_loc.x && y == p->current_loc.y){
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
      } else if(strcmp(noun, "data") == 0){
         print_player(p);
      }
   }
}

void executeCollect(Player *p){
   p->num_scrap += 1;
   printf("Collecting scrap...\nScrap collected!");
}

bool executecommand(char *input, Player *p, Cell (*cell)[n]){
   char *verb = strtok(input, " \n");
   char *noun = strtok(NULL, "\n");

   if (verb != NULL) {
      if (strcmp(verb, "quit") == 0) {
         return false;
      } else if (strcmp(verb, "scan") == 0) {
         printf("Scanning...\n");
         executeScan(p, cell);
      } else if (strcmp(verb, "show") == 0) {
         executeShow(p, noun);
      } else if(strcmp(verb, "help") == 0){
         printf("HELP\nCommands: ");
      } else if(strcmp(verb, "fly") == 0){
         executeFly(p, noun);
      } else {
         printf("Unknown command!\n");
      }
   }
   return true;
}