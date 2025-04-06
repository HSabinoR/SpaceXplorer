#include <stdbool.h>
#include "structures.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern int n;
extern Cell** cell;
extern Player player_info;
extern Coord asteroid;
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
#endif