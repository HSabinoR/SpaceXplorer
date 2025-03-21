#include <stdbool.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern int n;

bool executecommand(char *input, Player *p, Cell *cell[n][n]);
void executeScan(Player *player, Cell *cell[n][n]);

#endif