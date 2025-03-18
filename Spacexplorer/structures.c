#include <structures.h>

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