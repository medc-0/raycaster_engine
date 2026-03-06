#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIDTH 900
#define HEIGHT 600

#define COLOR_WHITE 0xFFFFFFFF

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window =
      SDL_CreateWindow("Raycasting Engine", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  SDL_Surface *surface = SDL_GetWindowSurface(window);

  bool running = true;
  int counter = 0;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      }
    }
    SDL_Rect rect = {WIDTH / 2, HEIGHT / 2, 100 + counter++, 100 + counter++};
    SDL_FillRect(surface, &rect, COLOR_WHITE);

    SDL_UpdateWindowSurface(window);
    SDL_Delay(10);
  }

  SDL_Quit();
  return 0;
}
