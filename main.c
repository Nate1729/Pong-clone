/* Standard library */
#include <stdio.h>

/* 3rd party library */
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

/* Constants */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PADDLE_HEIGHT 60
#define PADDLE_WIDTH 10

void init(SDL_Window **window, SDL_Renderer **renderer)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    printf("SDL could not be initialized! SDL Error: %s\n", SDL_GetError());
    exit(-1);
  }

  /* === Creating window === */
  (*window) = SDL_CreateWindow(
      "First Window",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN
  );
  if ((*window) == NULL)
  {
    printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    exit(-1);
  }

  /* === Creating renderer === */
  (*renderer) = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
  if ((*renderer) == NULL)
  {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    exit(-1);
  }
}

int main()
{  
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *textTexture = NULL;

  init(&window, &renderer);

  /* Setting up TTF */
  TTF_Init();
  TTF_Font *font = TTF_OpenFont("Yagora.ttf", 10);
  SDL_Color color = { 255, 255, 255 };
  SDL_Surface *surface = TTF_RenderText_Solid(font, "Welcome to Pong", color);

  textTexture = SDL_CreateTextureFromSurface(renderer, surface);

  /* Creating game objects */
  SDL_Rect leftPaddle = {
    0,
    (SCREEN_HEIGHT - PADDLE_HEIGHT)/2,
    PADDLE_WIDTH,
    PADDLE_HEIGHT
  }; 
  SDL_Rect rightPaddle = {
    SCREEN_WIDTH - PADDLE_WIDTH,
    (SCREEN_HEIGHT - PADDLE_HEIGHT)/2,
    PADDLE_WIDTH,
    PADDLE_HEIGHT
  };

  int quit = 0;
  SDL_Event e;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          quit = 1;
          break;
      }
    }
    /*SDL_RenderCopy(renderer, textTexture, NULL, NULL);*/
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &leftPaddle);
    SDL_RenderFillRect(renderer, &rightPaddle);
    SDL_RenderPresent(renderer);
  }

  TTF_CloseFont(font);
  SDL_DestroyTexture(textTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();
}
