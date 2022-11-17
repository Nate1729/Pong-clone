/* Standard library */
#include <stdio.h>

/* 3rd party library */
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

/* Local Imports */
#include "paddle.h" 
#include "constants.h"

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
  Paddle leftPaddle = create_paddle(LEFT_PADDLE);
  Paddle rightPaddle =  create_paddle(RIGHT_PADDLE); 

  /* Making the centerline */
  unsigned line_partition_height = 20;
  unsigned line_partition_width = 6;
  unsigned count = ((unsigned) SCREEN_HEIGHT) / (line_partition_height*2);
  
  SDL_Rect *centerline_rects = malloc(count * sizeof(SDL_Rect));

  unsigned i;
  for(i=0; i<count; i++)
  {
    centerline_rects[i].x = (SCREEN_WIDTH - line_partition_width)/2;
    centerline_rects[i].y = SCREEN_HEIGHT - (line_partition_height * 2 * i);
    centerline_rects[i].w = line_partition_width;
    centerline_rects[i].h = line_partition_height; 
  }
  

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
    SDL_RenderFillRects(renderer, centerline_rects, count);
    SDL_RenderPresent(renderer);
  }
  
  free(centerline_rects);

  TTF_CloseFont(font);
  SDL_DestroyTexture(textTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();
}
