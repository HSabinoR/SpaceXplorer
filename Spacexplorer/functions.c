#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>
#include "structures.h"
#include "functions.h"
#include <stdarg.h>

bool admin = false;

void executeScan(char *noun) {
   Coord scannable_cells[3][3] = {
      { {player_info.current_loc.x - 1, player_info.current_loc.y - 1}, {player_info.current_loc.x, player_info.current_loc.y - 1}, {player_info.current_loc.x + 1, player_info.current_loc.y - 1} },
      { {player_info.current_loc.x - 1, player_info.current_loc.y}, {player_info.current_loc.x, player_info.current_loc.y}, {player_info.current_loc.x + 1, player_info.current_loc.y} },
      { {player_info.current_loc.x - 1, player_info.current_loc.y + 1}, {player_info.current_loc.x, player_info.current_loc.y + 1}, {player_info.current_loc.x + 1, player_info.current_loc.y + 1} }
   };
   
   
   
   int gridSize = 3; // Default grid size
   
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
            if (!printa("  A  ")) {
               printf(" [0] ");
            }
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

   updateAsteroidPosition();
   turn++;
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

   updateAsteroidPosition();

   if(noun != NULL) {
      if (strcmp(noun, "up") == 0 && player_info.current_loc.y > 0){
         player_info.current_loc.y -= 1;
         printf("Flying upwards...\n");
         printa("New Co-ordinates: x: %d y: %d\n", player_info.current_loc.x, player_info.current_loc.y);
         turn++;
      } else if (strcmp(noun, "down") == 0 && player_info.current_loc.y < n-1){
         player_info.current_loc.y += 1;
         printf("Flying downwards...\n");
         printa("New Co-ordinates: x: %d y: %d\n", player_info.current_loc.x, player_info.current_loc.y);
         turn++;
      } else if (strcmp(noun, "left") == 0 && player_info.current_loc.x > 0){
         player_info.current_loc.x -= 1;
         printf("Flying left...\n");
         printa("New Co-ordinates: x: %d y: %d\n", player_info.current_loc.x, player_info.current_loc.y);
         turn++;
      } else if (strcmp(noun, "right") == 0 && player_info.current_loc.x < n-1){
         player_info.current_loc.x += 1;
         printf("Flying right...\n");
         printa("New Co-ordinates: x: %d y: %d\n", player_info.current_loc.x, player_info.current_loc.y);
         turn++;
      } else{
         printf("Can't fly in that direction");
         return;
      }

      if (cell[player_info.current_loc.x][player_info.current_loc.y].has_scrap == 1){
         int chance = rand() % 10; // Random chance of taking damage if the cell has scrap
         printa("Chance to get hit value: %d\n", chance); //Debugging

         if(chance > 5 && chance < 11){
            player_info.hp -= 1+rand() % 10;
            printf("\nYour ship has taken damage!!");
            checkHealth();
         }
      }
   } else {
      printf("No direction specified!");
      return;
   }

   // Asteroid Detection
   for(int i = 0; i < 9; i++) {
      for(int j = 0; j < 9; j++){
         int x = scannable_cells[i][j].x;
         int y = scannable_cells[i][j].y;

         if(asteroid.x == x && asteroid.y == y) printf("\nAsteroid detected within 4 spaces. Unable to determine from what direction...\nKeep an eye out!\n");
      }
   }
}

/* void updateAsteroidPosition() { Asteroid flies in a random direction. ->Made redudant due to removing asteroid.tajectories variables-<
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

void updateAsteroidPosition() { //Asteroid flies in a predefined path
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
         
         if (printa("Scrap Map\n")) {
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
                  } else if (x == asteroid.x && y == asteroid.y){
                     printf("  A  ");
                  } else if (cell[x][y].has_scrap == 1) {
                     printf(" [#] ");
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
            return;
         }
         
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
               } else if (x == asteroid.x && y == asteroid.y){
                  if (!printa("  A  ")) {
                     printf(" [0] ");
                  }
               } else {
                  printf(" [0] ");
               }
            }
            printf("|\n");
         }

         printf(" ");
         for (int i = 0; i < n*5; i++){
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
   
      player_info.num_scrap += 1+(rand() % 6);
      cell[player_info.current_loc.x][player_info.current_loc.y].has_scrap = 0;
      printf("Collecting scrap...\nScrap collected!");
      turn++;
      updateAsteroidPosition();
   } else {
      printf("No scrap to collect!");
   }
}

void saveGame() {

   // Filename is created based on the players name
   char filename[30];
   snprintf(filename, sizeof(filename), "%s.txt", player_info.name);
   
   // Replace any invalid characters in the filename with underscores
   for (int i = 0; filename[i] != '\0'; i++) {
      if (!isalnum((unsigned char)filename[i]) && filename[i] != '.') {
         filename[i] = '_';
      }
   }

   // Open .txt file for writing
   FILE *file = fopen(filename, "w");
   if (file == NULL) {
      perror("Failed to open file for writing");
      return;
   }

   // Save player info
   fprintf(file, "%d\n%s\n%d %d %d %d %d %d\n", turn, player_info.name, player_info.current_loc.x, player_info.current_loc.y, player_info.hp, player_info.num_scrap, player_info.oxygen, n);
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
   // Open the "filename.txt" file for reading
   FILE *file = fopen(filename, "r");
   if (file == NULL) {
      perror("Failed to open file for reading");
      return;
   } else {
      printa("Opening file: %s\n", filename);
   }

   // Load player info, including player's name
   if (fscanf(file, "%d\n%14s\n%d %d %d %d %d %d", &turn, &player_info.name, &player_info.current_loc.x, &player_info.current_loc.y, &player_info.hp, &player_info.num_scrap, &player_info.oxygen, &n) == 8) {
      printa("Loaded player details...\n");
   } else{
      printa("Failed to load player details...\n");
   }

   // Load asteroid Coords
   if (fscanf(file, "%d %d", &asteroid.x, &asteroid.y) == 2) {
      printa("Loaded asteroid coords...\n");
   }

   cell = malloc(n * sizeof(Cell*));
   for (int i = 0; i < n; i++) {
      cell[i] = malloc(n * sizeof(Cell));
   }

   // Load cell data
   for (int y = 0; y < n; y++) {
      for (int x = 0; x < n; x++) {
         if (fscanf(file, "%d ", &cell[y][x].has_scrap) == 1) {
            printa("Loaded cell[%d][%d] data...\n", y, x); // Debugging
         }
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
   if (asteroid.x == player_info.current_loc.x && asteroid.y == player_info.current_loc.y){
      printf("\nYou have hit an asteroid!! \n\t!!GAME OVER!!\n");
      return false;
   } else if(player_info.hp <= 0){
      printf("\nYour ship has taken too much damage!! \n\t!!GAME OVER!!\n");
      return false;
   } else if(player_info.oxygen == 0) {
      printf("\nYour ship has ran out of oxygen! You have suffocated and died!! \n\t!!GAME OVER!!\n");
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
         printa("Debugging Mode: on\n");
         getInput();

         char *ch = strtok(command, " \n");
         char *endptr;
         if (ch != NULL) {
            long num = strtol(ch, &endptr, 10);
           
            if (*endptr == '\0' && num > 0 && num < 5) {
               choice = (int) num;
               printa("Choice: %d\n", num); // Debugging
            }
         }
      } while(choice != 1 && choice != 2 && choice != 3 && choice != 4);
   
      if(choice == 1){
         printf("\nPlayer Name (no spaces allowed): ");
         fgets(player_info.name, sizeof player_info.name, stdin);
         
         // Removes any newline(\n) characters from the name.
         size_t len = strlen(player_info.name);
         if (len > 0 && player_info.name[len - 1] == '\n') {
            player_info.name[len - 1] = '\0';
         }

         // Remove any spaces from the name
         int j = 0;
         for (int i = 0; player_info.name[i] != '\0'; i++) {
            if (player_info.name[i] != ' ') {
               player_info.name[j++] = player_info.name[i];
            }
         }
         player_info.name[j] = '\0'; // Null-terminate the modified string

         system("cls");

         n = MIN_GRID_SIZE + rand() % (MAX_GRID_SIZE - MIN_GRID_SIZE + 1); // Random number between 18 and 24 determining grid size
         printa("Initialized grid size\n");
         
         // Set the initial position of the player
         player_info.current_loc.x = rand() % n;
         player_info.current_loc.y = rand() % n;

         printa("Initialized Oxygen: %d\n", player_info.oxygen);
         printa("Initialized HP: %d\n", player_info.hp);
      
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
               cell[x][y].has_scrap = (rand() % 10 < 4) ? 1 : 0; // 40% to add scrap

               if (x == player_info.current_loc.x && y == player_info.current_loc.y){
                  printf("  x  ");
               } else if (x == asteroid.x && y == asteroid.y){
                  if(!printa("  A  ")) {
                     printf(" [0] ");
                  }
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

         turn = 1;

         running = false;
      } else if(choice == 2) {
         listSaveFiles();
         char filename[20];

         FILE *file = NULL;
         while (file == NULL) {
            printf("Type \"cancel\" to go back.\n");
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
                  } else if (x == asteroid.x && y == asteroid.y){
                     if (!printa("  A  ")) {
                        printf(" [0] ");
                     }
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
         }
      } else if(choice == 3) {
         running = false; 
         return 0;
      } else if(choice == 4) { 
         admin = true;
         running = true;
      }
   }
}

void executeRepair(char *noun) {
   char *endptr;

   if (noun != NULL) {
      // Convert noun to a long
      long scrap_to_use = strtol(noun, &endptr, 10);

      // Basic input validation
      if (scrap_to_use <= 0) {
         printf("Please enter a positive number of scrap to use.\n");
         return;
      }

      if (player_info.hp >= 100) {
         printf("Your HP is already full.\n");
         return;
      }

      if (player_info.num_scrap == 0) {
         printf("You have no scrap to repair with.\n");
         return;
      }

      // Cap usage by available scrap
      if (scrap_to_use > player_info.num_scrap) {
         scrap_to_use = player_info.num_scrap;
         printf("Using all the scrap...\n");
      }

      // Cap usage by max HP
      int hp_needed = 100 - player_info.hp;
      int actual_used = (scrap_to_use > hp_needed) ? hp_needed : scrap_to_use;

      player_info.hp += actual_used;
      player_info.num_scrap -= actual_used;

      printf("You repaired %d HP using %d scrap.\n", actual_used, actual_used);
      printf("Current HP: %d, Scrap remaining: %d\n", player_info.hp, player_info.num_scrap);
      turn++;
      updateAsteroidPosition();
   } else {
      printf("Usage: repair <amount>\n");
   }
}

void oxygenControl(){
   if(player_info.hp < 100 && player_info.hp >= 75) {
      player_info.oxygen -= 1;
   } else if(player_info.hp < 75 && player_info.hp >= 50) {
      player_info.oxygen -= 2;
   } else if(player_info.hp < 50 && player_info.hp >= 25) {
      player_info.oxygen -= 4;
   } else if(player_info.hp < 25 && player_info.hp >= 1) {
      player_info.oxygen -= 6;
   }

   if (player_info.oxygen < 0) {
      player_info.oxygen = 0;
      printa("Setting player oxygen to %d", player_info.oxygen);
   }
}

bool printa(const char *format, ...) {
   if (admin) {
       va_list args; 
       va_start(args, format);
       vprintf(format, args); // behaves like printf but takes va_list
       va_end(args);
   }

   return admin;
}

bool executecommand(char *input) {
   char *verb = strtok(input, " \n");
   char *noun = strtok(NULL, "\n");
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
         printf("collect: Collect scrap from the current cell.\n");
         printf("repair [Number of Scrap to use]: Repair the ship using the scrap collected. 1 Scrap = 1 HP\n");
      } else if(strcmp(verb, "fly") == 0 && noun != NULL && strlen(noun) > 0){
         executeFly(noun);
      } else if(strcmp(verb, "collect") == 0){ 
         executeCollect();
      } else if (strcmp(verb, "repair") == 0) {
         executeRepair(noun);
      } else {
         printf("Unknown command!\n");
      }
   }
   printf("\n\t>TURN %d<\n", turn);
   printf("Type \"help\" to see all the commands.\n\n");

   oxygenControl();
   return checkHealth();
}