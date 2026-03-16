#include "raycast.h"

int worldMap[MAP_SIZE][MAP_SIZE] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,2,2,2,0,0,0,3,3,0,0,0,1},
    {1,0,2,0,0,0,0,0,3,0,0,0,0,1},
    {1,0,2,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,4,4,0,0,0,0,0,0,1},
    {1,0,0,0,0,4,4,0,0,2,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,2,0,0,0,1},
    {1,0,3,3,0,0,0,0,0,0,0,0,0,1},
    {1,0,3,0,0,0,0,4,4,0,0,0,0,1},
    {1,0,0,0,0,0,0,4,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Uint32 get_color(int texNum, int side) {
    Uint32 color;
    switch(texNum) {
        case 1:  color = 0xED6A5A; break;
        case 2:  color = 0x9BC1BC; break;
        case 3:  color = 0x5CA4A9; break;
        case 4:  color = 0xF4F1BB; break;
        default: color = 0x333333; break;
    }
    if (side == 1) {
        color = (color & 0xFEFEFE) >> 1; 
    }
    return color;
}

void render_frame(SDL_Surface *surface, Player *p) {
    Uint32* pixels = (Uint32*)surface->pixels;
    int w = surface->w;
    int h = surface->h;

    for (int x = 0; x < w; x++) {
        double cameraX = 2 * x / (double)w - 1;
        double rayDirX = p->dirX + p->planeX * cameraX;
        double rayDirY = p->dirY + p->planeY * cameraX;

        int mapX = (int)p->x;
        int mapY = (int)p->y;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double sideDistX, sideDistY;
        int stepX, stepY;
        int hit = 0, side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (p->x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - p->x) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (p->y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - p->y) * deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        double perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);
        
        int lineHeight = (int)(h / perpWallDist);
        int drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h) drawEnd = h - 1;

        Uint32 wallColor = get_color(worldMap[mapX][mapY], side);

        for (int y = 0; y < h; y++) {
            if (y < drawStart) pixels[y * w + x] = 0x222222;
            else if (y > drawEnd) pixels[y * w + x] = 0x111111;
            else pixels[y * w + x] = wallColor;
        }
    }
}