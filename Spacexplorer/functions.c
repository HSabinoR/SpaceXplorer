#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>
#include "structures.h"
#include "functions.h"


void executeScan(char *noun) {
   Coord scannable_cells[3][3] = {
      { {player_info.current_loc.x - 1, player_info.current_loc.y - 1}, {player_info.current_loc.x, player_info.current_loc.y - 1}, {player_info.current_loc.x + 1, player_info.current_loc.y - 1} },
      { {player_info.current_loc.x - 1, player_info.current_loc.y}, {player_info.current_loc.x, player_info.current_loc.y}, {player_info.current_loc.x + 1, player_info.current_loc.y} },
      { {player_info.current_loc.x - 1, player_info.current_loc.y + 1}, {player_info.current_loc.x, player_info.current_loc.y + 1}, {player_info.current_loc.x + 1, player_info.current_loc.y + 1} }
   };
   
   
   
   int gridSize = 3; // Default grid size
   
   // Decided to make it so player can only scan 1 cell in each directions
   
   /*
   char *endptr;

   if (noun != NULL) {
      // Convert the noun to a long integer
      long num = strtol(noun, &endptr, 10);

      // Check if the conversion is successful and the entire string is a number
      if (*endptr == '\0' && num > 0 && num < 4) {
         gridSize = (int) num * 2 + 1;
      } // Allows gridSize up 7 
      //printf("\nScanning range: %d\n", gridSize); Debugging
   }

   // Allocate memory for scannable_cells depending on gridSize
   Coord** scannable_cells = malloc(gridSize * sizeof(Coord*));
   for (int i = 0; i < gridSize; i++) {
      scannable_cells[i] = malloc(gridSize * sizeof(Coord));
   }

   // Assign values to scannable_cells
   for (int i = 0; i < gridSize; i++) {
      for (int j = 0; j < gridSize; j++) {
         scannable_cells[i][j].x = player_info.current_loc.x - (gridSize / 2) + j;
         scannable_cells[i][j].y = player_info.current_loc.y - (gridSize / 2) + i;
      }
   }
   */
   for(int i = 0; i < gridSize; i++) {
        
      printf("|");

      for(int j = 0; j < gridSize; j++){ 
         
         int x = scannable_cells[i][j].x;
         int y = scannable_cells[i][j].y;

         if (y < 0 || y >= n) {
            printf("-----"); // Out of bounds
         } else if(x >= n) {
            printf("  <  "); // Out of bounds
         } else if(x < 0) {
            printf("  >  "); // Out of bounds
         } else if (x == player_info.current_loc.x && y == player_info.current_loc.y) {
            printf("  x  "); // Player's position
         } else if (cell[x][y].has_scrap) {
            printf(" [#] "); // Scrap detected
         } else if (x == asteroid.x && y == asteroid.y) {
            printf("  A  "); // Asteroid detected
        } else {
            printf(" [0] "); // Empty cell
         }
      }
      printf("|\n");
   }
   int x = player_info.current_loc.x;
   int y = player_info.current_loc.y;

   if (cell[x][y].has_scrap == 1) {
      printf("\nThe cell you're on has some space junk!");
   }

   /* // Free the allocated memory
   for (int i = 0; i < gridSize; i++) {
      free(scannable_cells[i]);
   }
   free(scannable_cells);
   */
}

void executeFly(char *noun) {
   
   // Scannable cells to detect the asteroid
   Coord scannable_cells[9][9] = {
      { {player_info.current_loc.x - 4, player_info.current_loc.y - 4}, {player_info.current_loc.x - 3, player_info.current_loc.y - 4}, {player_info.current_loc.x - 2, player_info.current_loc.y - 4}, {player_info.current_loc.x - 1, player_info.current_loc.y - 4}, {player_info.current_loc.x, player_info.current_loc.y - 4}, {player_info.current_loc.x + 1, player_info.current_loc.y - 4}, {player_info.current_loc.x + 2, player_info.current_loc.y - 4}, {player_info.current_loc.x + 3, player_info.current_loc.y - 4}, {player_info.current_loc.x + 4, player_info.current_loc.y - 4} },
      { {player_info.current_loc.x - 4, player_info.current_loc.y - 3}, {player_info.current_loc.x - 3, player_info.current_loc.y - 3}, {player_info.current_loc.x - 2, player_info.current_loc.y - 3}, {player_info.current_loc.x - 1, player_info.current_loc.y - 3}, {player_info.current_loc.x, player_info.current_loc.y - 3}, {player_info.current_loc.x + 1, player_info.current_loc.y - 3}, {player_info.current_loc.x + 2, player_info.current_loc.y - 3}, {player_info.current_loc.x + 3, player_info.current_loc.y - 3}, {player_info.current_loc.x + 4, player_info.current_loc.y - 3} },
      { {player_info.current_loc.x - 4, player_info.current_loc.y - 2}, {player_info.current_loc.x - 3, player_info.current_loc.y - 2}, {player_info.current_loc.x - 2, player_info.current_loc.y - 2}, {player_info.current_loc.x - 1, player_info.current_loc.y - 2}, {player_info.current_loc.x, player_info.current_loc.y - 2}, {player_info.current_loc.x + 1, player_info.current_loc.y - 2}, {player_info.current_loc.x + 2, player_info.current_loc.y - 2}, {player_info.current_loc.x + 3, player_info.current_loc.y - 2}, {player_info.current_loc.x + 4, player_info.current_loc.y - 2} },
      { {player_info.current_loc.x - 4, player_info.current_loc.y - 1}, {player_info.current_loc.x - 3, player_info.current_loc.y - 1}, {player_info.current_loc.x - 2, player_info.current_loc.y - 1}, {player_info.current_loc.x - 1, player_info.current_loc.y - 1}, {player_info.current_loc.x, player_info.current_loc.y - 1}, {player_info.current_loc.x + 1, player_info.current_loc.y - 1}, {player_info.current_loc.x + 2, player_info.current_loc.y - 1}, {player_info.current_loc.x + 3, player_info.current_loc.y - 1}, {player_info.current_loc.x + 4, player_info.current_loc.y - 1} },
      { {player_info.current_loc.x - 4, player_info.current_loc.y}, {player_info.current_loc.x - 3, player_info.current_loc.y}, {player_info.current_loc.x - 2, player_info.current_loc.y}, {player_info.current_loc.x - 1, player_info.current_loc.y}, {player_info.current_loc.x, player_info.current_loc.y}, {player_info.current_loc.x + 1, player_info.current_loc.y}, {player_info.current_loc.x + 2, player_info.current_loc.y}, {player_info.current_loc.x + 3, player_info.current_loc.y}, {player_info.current_loc.x + 4, player_info.current_loc.y} },
      { {player_info.current_loc.x - 4, player_info.current_loc.y + 1}, {player_info.current_loc.x - 3, player_info.current_loc.y + 1}, {player_info.current_loc.x - 2, player_info.current_loc.y + 1}, {player_info.current_loc.x - 1, player_info.current_loc.y + 1}, {player_info.current_loc.x, player_info.current_loc.y + 1}, {player_info.current_loc.x + 1, player_info.current_loc.y + 1}, {player_info.current_loc.x + 2, player_info.current_loc.y + 1}, {player_info.current_loc.x + 3, player_info.current_loc.y + 1}, {player_info.current_loc.x + 4, player_info.current_loc.y + 1} },
      { {player_info.current_loc.x - 4, player_info.current_loc.y + 2}, {player_info.current_loc.x - 3, player_info.current_loc.y + 2}, {player_info.current_loc.x - 2, player_info.current_loc.y + 2}, {player_info.current_loc.x - 1, player_info.current_loc.y + 2}, {player_info.current_loc.x, player_info.current_loc.y + 2}, {player_info.current_loc.x + 1, player_info.current_loc.y + 2}, {player_info.current_loc.x + 2, player_info.current_loc.y + 2}, {player_info.current_loc.x + 3, player_info.current_loc.y + 2}, {player_info.current_loc.x + 4, player_info.current_loc.y + 2} },
      { {player_info.current_loc.x - 4, player_info.current_loc.y + 3}, {player_info.current_loc.x - 3, player_info.current_loc.y + 3}, {player_info.current_loc.x - 2, player_info.current_loc.y + 3}, {player_info.current_loc.x - 1, player_info.current_loc.y + 3}, {player_info.current_loc.x, player_info.current_loc.y + 3}, {player_info.current_loc.x + 1, player_info.current_loc.y + 3}, {player_info.current_loc.x + 2, player_info.current_loc.y + 3}, {player_info.current_loc.x + 3, player_info.current_loc.y + 3}, {player_info.current_loc.x + 4, player_info.current_loc.y + 3} },
      { {player_info.current_loc.x - 4, player_info.current_loc.y + 4}, {player_info.current_loc.x - 3, player_info.current_loc.y + 4}, {player_info.current_loc.x - 2, player_info.current_loc.y + 4}, {player_info.current_loc.x - 1, player_info.current_loc.y + 4}, {player_info.current_loc.x, player_info.current_loc.y + 4}, {player_info.current_loc.x + 1, player_info.current_loc.y + 4}, {player_info.current_loc.x + 2, player_info.current_loc.y + 4}, {player_info.current_loc.x + 3, player_info.current_loc.y + 4}, {player_info.current_loc.x + 4, player_info.current_loc.y + 4} }
  };

   srand(time(NULL));

   if(noun != NULL) {
      if (strcmp(noun, "up") == 0 && player_info.current_loc.y > 0){
         player_info.current_loc.y -= 1;
         printf("Flying upwards...\n");
         printf("New Co-ordinates: x: %d y: %d", player_info.current_loc.x, player_info.current_loc.y);
      } else if (strcmp(noun, "down") == 0 && player_info.current_loc.y < n-1){
         player_info.current_loc.y += 1;
         printf("Flying downwards...\n");
         printf("New Co-ordinates: x: %d y: %d", player_info.current_loc.x, player_info.current_loc.y);
      } else if (strcmp(noun, "left") == 0 && player_info.current_loc.x > 0){
         player_info.current_loc.x -= 1;
         printf("Flying left...\n");
         printf("New Co-ordinates: x: %d y: %d", player_info.current_loc.x, player_info.current_loc.y);
      } else if (strcmp(noun, "right") == 0 && player_info.current_loc.x < n-1){
         player_info.current_loc.x += 1;
         printf("Flying right...\n");
         printf("New Co-ordinates: x: %d y: %d", player_info.current_loc.x, player_info.current_loc.y);
      } else{
         printf("Can't fly in that direction");
      }

      if (cell[player_info.current_loc.x][player_info.current_loc.y].has_scrap == 1){
         int chance = rand() % 10; // Random chance of taking damage if the cell has scrap
         //printf("Chance value: %d\n", chance); Debugging

         if(chance > 5 && chance < 11){
            player_info.hp -= 1+rand() % 10;
            printf("\nYour ship has taken damage!!");
            if(player_info.hp <= 0){
               checkHealth();
            }
         }
      }
   }
   updateAsteroidPosition();

   // Asteroid Detection
   for(int i = 0; i < 9; i++) {
      for(int j = 0; j < 9; j++){
         int x = scannable_cells[i][j].x;
         int y = scannable_cells[i][j].y;

         if(asteroid.x == x && asteroid.y == y) printf("\nAsteroid detected within 4 spaces. Unable to determine from what direction...\nKeep an eye out!");
      }
   }
}

/* Asteroid flies in a random direction
// Made redudant due to removing asteroid.tajectories variables

void updateAsteroidPosition() {
   asteroid.current_loc.x += asteroid.trajectory.x;
   asteroid.current_loc.y += asteroid.trajectory.y;

   // Ensure asteroid wraps around the grid
   if (asteroid.current_loc.x >= n) asteroid.current_loc.x = 0;
   if (asteroid.current_loc.x < 0) asteroid.current_loc.x = n-1;
   if (asteroid.current_loc.y >= n) asteroid.current_loc.y = 0;
   if (asteroid.current_loc.y < 0) asteroid.current_loc.y = n-1;

   // Randomly change direction
   if (rand() % 10 < 3) { // 30% chance to change direction
      int direction = rand() % 4; // 0, 1, 2, or 3
  
      switch (direction) {
          case 0: // Move up
              asteroid.trajectory.x = 0;
              asteroid.trajectory.y = -1;
              break;
          case 1: // Move down
              asteroid.trajectory.x = 0;
              asteroid.trajectory.y = 1;
              break;
          case 2: // Move left
              asteroid.trajectory.x = -1;
              asteroid.trajectory.y = 0;
              break;
          case 3: // Move right
              asteroid.trajectory.x = 1;
              asteroid.trajectory.y = 0;
              break;
      }
  }
}
*/

//Asteroid flies in a predefined path
void updateAsteroidPosition() {
   static int step = 0; // static variable means step doesn't reset to 0 everytime the fucntion is run
   Coord predefined_path[] = {
      {1, 0}, {1, 0}, {0, 1}, {0, 1}, {-1, 0}, {-1, 0}, {0, 1}, {0, 1},      // Move right twice, down twice, left twice, down twice
      {1, 0}, {1, 0}, {0, -1}, {0, -1}, {1, 0}, {1, 0}, {0, 1}, {0, 1},     // Move right twice, up twice, right twice, down twice
      {-1, 0}, {-1, 0}, {0, -1}, {0, -1}, {1, 0}, {0, 1}, {-1, 0}, {0, 1},  // Move left twice, up twice, right once, down once, left once, down once
      {1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {-1, 0}, {0, 1}    // Move right once, up once, right once, down once, left twice, up once
  };
   int path_length = sizeof(predefined_path) / sizeof(predefined_path[0]);

   asteroid.x += predefined_path[step].x;
   asteroid.y += predefined_path[step].y;

   // Ensure asteroid wraps around the grid
   if (asteroid.x >= n) asteroid.x = 0;
   if (asteroid.x < 0) asteroid.x = n-1;
   if (asteroid.y >= n) asteroid.y = 0;
   if (asteroid.y < 0) asteroid.y = n-1;

   step = (step + 1) % path_length;
}

void executeShow(char *noun) {
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
               if (x == player_info.current_loc.x && y == player_info.current_loc.y){
                  printf("  x  ");
               }/*else if (x == asteroid.x && y == asteroid.y){
                  //printf("  A  ");
              } */else {
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
         print_player(&player_info);
      }
   }
}

void executeCollect() {
   
   if(cell[player_info.current_loc.x][player_info.current_loc.y].has_scrap == 1) {
   
      player_info.num_scrap += 1;
      cell[player_info.current_loc.x][player_info.current_loc.y].has_scrap = 0;
      printf("Collecting scrap...\nScrap collected!");
   } else {
      printf("No scrap to collect!");
   }
}

void saveGame() {
   char filename[30];
   snprintf(filename, sizeof(filename), "%s.txt", player_info.name);
   
   for (int i = 0; filename[i] != '\0'; i++) {
      if (!isalnum((unsigned char)filename[i]) && filename[i] != '.') {
         filename[i] = '_'; // Replace invalid characters with underscore
      }
   }

   FILE *file = fopen(filename, "w");
   if (file == NULL) {
      perror("Failed to open file for writing");
      return;
   }

   // Save player info, including player's name
   fprintf(file, "%s\n%d %d %d %d %d %d\n", player_info.name, player_info.current_loc.x, player_info.current_loc.y, player_info.hp, player_info.num_scrap, player_info.oxygen, n);
   // Save asteroid Coords
   fprintf(file, "%d %d\n", asteroid.x, asteroid.y);
   
   // Save cell data
   for (int y = 0; y < n; y++) {
      for (int x = 0; x < n; x++) {
         fprintf(file, "%d ", cell[y][x].has_scrap);
      }
      fprintf(file, "\n");
   }

   fclose(file);
}

void loadGame(char *filename) {
   FILE *file = fopen(filename, "r");
   if (file == NULL) {
      perror("Failed to open file for reading");
      return;
   }

   // Load player info, including player's name
   fscanf(file, "%14s\n%d %d %d %d %d %d", &player_info.name, &player_info.current_loc.x, &player_info.current_loc.y, &player_info.hp, &player_info.num_scrap, &player_info.oxygen, &n);
   printf("Loaded player details...\n");

   // Load asteroid Coords
   fscanf(file, "%d %d", &asteroid.x, &asteroid.y);
   printf("Loaded asteroid coords...\n");

   cell = malloc(n * sizeof(Cell*));
   for (int i = 0; i < n; i++) {
      cell[i] = malloc(n * sizeof(Cell));
   }

   // Load cell data
   for (int y = 0; y < n; y++) {
      for (int x = 0; x < n; x++) {
         fscanf(file, "%d ", &cell[y][x].has_scrap);
         //printf("Loaded cell[%d][%d] data...\n", y, x); // Debugging
      }
   }

   fclose(file);
}

void listSaveFiles() {
   DIR *d;
   struct dirent *dir;
   d = opendir(".");
   if (d) {
      printf("Available save files:\n");
      while ((dir = readdir(d)) != NULL) {
         if (strstr(dir->d_name, ".txt")) {
            printf("%s\n", dir->d_name);
         }
      }
      closedir(d);
   } else {
      perror("Failed to open directory");
   }
}

bool checkHealth(){
   if(asteroid.x == player_info.current_loc.x && asteroid.y == player_info.current_loc.y){
      printf("You have hit an asteroid!! \n\t!!GAME OVER!!");
      return false;
   }else if(player_info.hp <= 0){
      printf("Your ship has taken too much damage!! \n\t!!GAME OVER!!");
      return false;
   }
   return true;
}
int mainMenu(){
   // Main menu setup. Load, New game and Check leaderboard systems    
   bool running = true;
   
   while(running){
      int choice = 0;
      do {
         system("cls");  // Clears screen if needed
         printf("--Main Menu--\n");
         printf(" 1. New Game\n");
         printf(" 2. Load Game\n");
         printf(" 3. Quit\n");
         getInput();

         char *ch = strtok(command, " \n");
         char *endptr;
         if (ch != NULL) {
            long num = strtol(ch, &endptr, 10);
           
            if (*endptr == '\0' && num > 0 && num < 4) {
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

         running = false;
      } else if(choice == 2) {
         listSaveFiles();
         char filename[20];

         FILE *file = NULL;
         while (file == NULL) {
            printf("Which file would you like to load (include the .txt): ");
            fgets(filename, sizeof filename, stdin);
            
            // Remove trailing newline, if any
            size_t len = strlen(filename);
            if (len > 0 && filename[len - 1] == '\n') {
               filename[len - 1] = '\0';
            }  

            if (strcmp(filename, "cancel") == 0){
               break;
            }
      
            file = fopen(filename, "r");
            if (file == NULL) {
               printf("File not found. Please enter a valid filename.\n");
            }
         }

         if(file != NULL){
            running = false;
            system("cls");

            fclose(file);
            loadGame(filename);
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
         }
      } else if(choice == 3) {
         running = false; 
         return 0;
      }
   }
}

bool executecommand(char *input) {
   char *verb = strtok(input, " \n");
   char *noun = strtok(NULL, "\n");
   printf("Type \"help\" to see all the commands.\n\n");
   if (verb != NULL) {
      if (strcmp(verb, "quit") == 0) {
         printf("Saving...\n");
         saveGame();
         return false;
      } else if (strcmp(verb, "scan") == 0) {
         printf("Scanning...\n");
         executeScan(noun);
      } else if (strcmp(verb, "show") == 0) {
         executeShow(noun);
      } else if(strcmp(verb, "help") == 0){
         printf("COMMANDS: \n");
         printf("quit: Exit the game.\n");
         printf("scan: Scan the surrounding cells.\n");
         printf("show [object]: Display information.\n");
         printf("\tshow map: Display the map.\n");
         printf("\tshow data: Display player data.\n");
         printf("help: Display help information.\n");
         printf("fly [direction]: Move the player.\n");
         printf("\tfly up: Move up.\n");
         printf("\tfly down: Move down.\n");
         printf("\tfly left: Move left.\n");
         printf("\tfly right: Move right.\n");
         printf("collect: Collect scrap from the current cell.");
      } else if(strcmp(verb, "fly") == 0 && noun != NULL && strlen(noun) > 0){
         executeFly(noun);
      } else if(strcmp(verb, "collect") == 0){ 
         executeCollect();
      } else {
         printf("Unknown command!\n");
      }
   }
   return checkHealth;
}