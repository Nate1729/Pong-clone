/* Standard library */
#include <stdio.h>
#include <stdlib.h>

/* 3rd party library */
#include "SDL2/SDL.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_ttf.h"

/* Local Imports */
#include "paddle.h" 
#include "ball.h"
#include "constants.h"
#include "centerline.h"
#include "state.h"
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

void check_paddle_ball_collision(Ball *ball, Paddle *left_paddle, Paddle *right_paddle)
{
  if (ball_left_edge(ball) > paddle_right_edge(left_paddle)
      && ball_left_edge(ball) + ball->vel.x_vel < paddle_right_edge(left_paddle))
  {
    if (ball_bottom_edge(ball) >= paddle_top_edge(left_paddle) &&
        ball_top_edge(ball) <= paddle_bottom_edge(left_paddle))
    {
      ball->vel.x_vel = -ball->vel.x_vel;
    }
  } else if (
      ball_right_edge(ball) < paddle_right_edge(right_paddle) &&
      ball_right_edge(ball) + ball->vel.x_vel > paddle_left_edge(right_paddle))
  {
    if (ball_bottom_edge(ball) >= paddle_top_edge(right_paddle) &&
        ball_top_edge(ball) <= paddle_bottom_edge(right_paddle))
    {
      ball->vel.x_vel = -ball->vel.x_vel;
    }    
  }
}

SDL_Texture** initialize_font_surfaces(int max_score, TTF_Font *font, SDL_Renderer *renderer)
{
  if (max_score < 1)
  {
    return NULL;
  }

  /* Initalizing array */
  SDL_Color number_color = {0xFF, 0xFF, 0xFF};
  SDL_Texture **texture_array = (SDL_Texture **) malloc(sizeof(SDL_Texture *) * max_score);
  
  int i;
  SDL_Surface *temp_surface;
  for (i=0; i< max_score; i++)
  {
    temp_surface = TTF_RenderText_Solid(font, (char)(i+48), number_color);
    texture_array[i] = SDL_CreateTextureFromSurface(renderer, temp_surface);

    free(temp_surface);
    temp_surface = NULL;

    if (texture_array[i] == NULL)
    {
      free(texture_array);

      printf("Error creating textures! SDL Error: %s\n", SDL_GetError());

      return NULL;
    }
  }

  return texture_array;
}

int main()
{  
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *textTexture = NULL;

  init(&window, &renderer);

  /* Setting up TTF */
  TTF_Init();
  TTF_Font *font = TTF_OpenFont("fonts/8-bit-font.ttf", 30);
  if (font == NULL)
  {
    printf("Error opening font!\n");
    exit(EXIT_FAILURE);
  }
  SDL_Color color = { 255, 255, 255 };
  SDL_Texture **scoreboard_texture_array = initialize_font_surfaces(10, font, renderer);

  /* Initializing Game State */
  GameState state = game_state_initialize();
 
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
              paddle_direction_update(&state.left_paddle, PADDLE_MOVE_UP);
              break;
            case SDLK_s:
              paddle_direction_update(&state.left_paddle, PADDLE_MOVE_DOWN);
              break;
            case SDLK_UP:
              paddle_direction_update(&state.right_paddle, PADDLE_MOVE_UP);
              break;
            case SDLK_DOWN: 
              paddle_direction_update(&state.right_paddle, PADDLE_MOVE_DOWN);
              break;
          }
          break;
        case SDL_KEYUP:
          switch (e.key.keysym.sym) {
            case SDLK_w:
              paddle_direction_update(&state.left_paddle, PADDLE_STAY);
              break;
            case SDLK_s:
              paddle_direction_update(&state.left_paddle, PADDLE_STAY);
              break;
            case SDLK_UP:
              paddle_direction_update(&state.right_paddle, PADDLE_STAY);
              break;
            case SDLK_DOWN:
              paddle_direction_update(&state.right_paddle, PADDLE_STAY);
              break;
          }
          break;
      }
    }

    if (SDL_GetTicks64() - timer > frame_length)
    {
      timer = SDL_GetTicks64();

      /* Update game object positions */
      paddle_move(&state.left_paddle);
      paddle_move(&state.right_paddle);
      check_paddle_ball_collision(&state.ball, &state.left_paddle, &state.right_paddle);
      ball_update_position(&state.ball);
      /*SDL_RenderCopy(renderer, textTexture, NULL, NULL);*/

      game_state_render(&state, renderer);;
      SDL_RenderPresent(renderer);
    }
  }
  
  game_state_destroy(&state);

  TTF_CloseFont(font);
  SDL_DestroyTexture(textTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();
}
