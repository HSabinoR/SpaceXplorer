#include "structures.h"
#include <stdio.h>

void print_player(const Player *p) {
    printf("Player %s at (%d, %d) | HP: %d | Scrap: %d | Oxygen: %d%%\n",
           p->name, p->current_loc.x, p->current_loc.y, p->hp, p->num_scrap, p->oxygen);
}