#include <stdbool.h>
#include "structures.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern int n;
bool executecommand(char *input, Player *p, Cell (*cell)[n]);
void executeScan(Player *player, Cell (*cell)[n]);
void executeFly(Player *p, char *noun);
void executeShow(Player *p, char *noun);
void executeCollect(Player *p);
#endif