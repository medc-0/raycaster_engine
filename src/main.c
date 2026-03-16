#include "raycast.h"

const double MOVE_SPEED = 2.0;
const double ROT_SPEED = 2.0;

void handle_input(Player *p, const Uint8 *keys, double frameTime) {
    double mSpd = MOVE_SPEED * frameTime;
    double rSpd = ROT_SPEED * frameTime;

    if (keys[SDL_SCANCODE_W]) {
        if (worldMap[(int)(p->x + p->dirX * mSpd)][(int)p->y] == 0) p->x += p->dirX * mSpd;
        if (worldMap[(int)p->x][(int)(p->y + p->dirY * mSpd)] == 0) p->y += p->dirY * mSpd;
    }
    if (keys[SDL_SCANCODE_S]) {
        if (worldMap[(int)(p->x - p->dirX * mSpd)][(int)p->y] == 0) p->x -= p->dirX * mSpd;
        if (worldMap[(int)p->x][(int)(p->y - p->dirY * mSpd)] == 0) p->y -= p->dirY * mSpd;
    }
    if (keys[SDL_SCANCODE_D]) {
        double oldDirX = p->dirX;
        p->dirX = p->dirX * cos(-rSpd) - p->dirY * sin(-rSpd);
        p->dirY = oldDirX * sin(-rSpd) + p->dirY * cos(-rSpd);
        double oldPlaneX = p->planeX;
        p->planeX = p->planeX * cos(-rSpd) - p->planeY * sin(-rSpd);
        p->planeY = oldPlaneX * sin(-rSpd) + p->planeY * cos(-rSpd);
    }
    if (keys[SDL_SCANCODE_A]) {
        double oldDirX = p->dirX;
        p->dirX = p->dirX * cos(rSpd) - p->dirY * sin(rSpd);
        p->dirY = oldDirX * sin(rSpd) + p->dirY * cos(rSpd);
        double oldPlaneX = p->planeX;
        p->planeX = p->planeX * cos(rSpd) - p->planeY * sin(rSpd);
        p->planeY = oldPlaneX * sin(rSpd) + p->planeY * cos(rSpd);
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Raycaster Engine", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
    WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    Player player = {2.0, 2.0, -1.0, 0.0, 0.0, 0.66};
    
    Uint32 time = 0;
    Uint32 oldTime = 0;
    bool running = true;

    while (running) {
        oldTime = time;
        time = SDL_GetTicks();
        double frameTime = (time - oldTime) / 1000.0;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
            surface = SDL_GetWindowSurface(window);
        }
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        handle_input(&player, keys, frameTime);

        SDL_LockSurface(surface);
        render_frame(surface, &player);
        SDL_UnlockSurface(surface);

        SDL_UpdateWindowSurface(window);
        
        SDL_Delay(1); 
    }

    SDL_Quit();
    return 0;
}