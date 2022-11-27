/* Standard library */
#include <stdio.h>

/* 3rd party library */
#include "SDL2/SDL.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_ttf.h"

/* Local Imports */
#include "paddle.h" 
#include "ball.h"
#include "constants.h"
#include "types.h"

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
  Paddle leftPaddle = paddle_create(LEFT_PADDLE);
  Paddle rightPaddle =  paddle_create(RIGHT_PADDLE);
  Ball ball = ball_create();

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
  
  /* Setting up frame rate */
  u64 frame_length = (1000 / (u64)FRAME_RATE);
  u64 timer = SDL_GetTicks64();

  int quit = 0;
  int keycode;
  SDL_Event e;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          quit = 1;
          break;
        case SDL_KEYDOWN:
          switch (e.key.keysym.sym) {
            case SDLK_w:
              paddle_direction_update(&leftPaddle, PADDLE_MOVE_UP);
              break;
            case SDLK_s:
              paddle_direction_update(&leftPaddle, PADDLE_MOVE_DOWN);
              break;
            case SDLK_UP:
              paddle_direction_update(&rightPaddle, PADDLE_MOVE_UP);
              break;
            case SDLK_DOWN: 
              paddle_direction_update(&rightPaddle, PADDLE_MOVE_DOWN);
              break;
          }
          break;
        case SDL_KEYUP:
          switch (e.key.keysym.sym) {
            case SDLK_w:
              paddle_direction_update(&leftPaddle, PADDLE_STAY);
              break;
            case SDLK_s:
              paddle_direction_update(&leftPaddle, PADDLE_STAY);
              break;
            case SDLK_UP:
              paddle_direction_update(&rightPaddle, PADDLE_STAY);
              break;
            case SDLK_DOWN:
              paddle_direction_update(&rightPaddle, PADDLE_STAY);
              break;
          }
          break;
      }
    }

    if (SDL_GetTicks64() - timer > frame_length)
    {
      timer = SDL_GetTicks64();

      /* Update game object positions */
      paddle_move(&leftPaddle);
      paddle_move(&rightPaddle);
      ball_update_position(&ball);
      /*SDL_RenderCopy(renderer, textTexture, NULL, NULL);*/

      /* Clear the screen */
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
      SDL_RenderClear(renderer);

      /* Render game objects */
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      paddle_render(&leftPaddle, renderer);
      paddle_render(&rightPaddle, renderer);
      ball_render(renderer, &ball);
      /*SDL_RenderFillRects(renderer, centerline_rects, count);*/
      SDL_RenderPresent(renderer);
    }
  }
  
  free(centerline_rects);

  TTF_CloseFont(font);
  SDL_DestroyTexture(textTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();
}
