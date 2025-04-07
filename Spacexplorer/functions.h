#include <stdbool.h>
#include "structures.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern int n;
extern Cell** cell;
extern Player player_info;
extern Coord asteroid;
int MIN_GRID_SIZE;
int MAX_GRID_SIZE;
char command[50];
int turn;
bool getInput(void);
bool executecommand(char *input);
void executeScan(char *noun);
void executeFly(char *noun);
void executeShow(char *noun);
void executeCollect();
void updateAsteroidPosition();
void saveGame();
void loadGame(char *filename);
void listSaveFiles();
bool checkHealth();
int mainMenu();
void executeRepair(char *noun);
void oxygenControl();
bool printa(const char *format, ...);
#endif