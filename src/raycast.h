#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define MAP_SIZE 14

typedef struct {
    double x, y;
    double dirX, dirY;
    double planeX, planeY;
} Player;

extern int worldMap[MAP_SIZE][MAP_SIZE];

void render_frame(SDL_Surface *surface, Player *player);
void handle_input(Player *player, const Uint8 *keys, double frameTime);
Uint32 get_color(int texNum, int side);