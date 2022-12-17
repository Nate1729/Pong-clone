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
#include "scoreboard.h"
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

int main()
{  
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *textTexture = NULL;

  init(&window, &renderer);

  /* Setting up TTF */
  TTF_Init();
  TTF_Font *font = TTF_OpenFont("fonts/8-bit-font.ttf", 50);
  if (font == NULL)
  {
    printf("Error opening font!\n");
    exit(EXIT_FAILURE);
  }
  SDL_Color color = { 255, 255, 255 };
 /* SDL_Surface *textSurface = TTF_RenderText_Solid(font, "0", color);
  textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_FreeSurface(textSurface); */

  /* Creating Font Textures */
  SDL_Texture **score_textures = malloc(sizeof(SDL_Texture*) * (MAX_SCORE+1));
  fill_score_textures(score_textures, font, color, renderer);

  /* Initializing Game State */
  GameState state = game_state_initialize();
  Scoreboard left_scoreboard = scoreboard_left_create();
  Scoreboard right_scoreboard = scoreboard_right_create();
 
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
      check_paddle_ball_collision(&state);
      int scored = ball_update_position(&state.ball);
      if (scored == LEFT_PLAYER_SCORE && state.left_scoreboard.score < MAX_SCORE)
      {
        state.left_scoreboard.score += 1;
      }
      else if (scored == RIGHT_PLAYER_SCORE && state.right_scoreboard.score < MAX_SCORE)
      {
        state.right_scoreboard.score += 1;
      }

      game_state_render(&state, renderer);
      scoreboard_render(&left_scoreboard, renderer, score_textures[state.left_scoreboard.score]);
      scoreboard_render(&right_scoreboard, renderer, score_textures[state.right_scoreboard.score]);
      SDL_RenderPresent(renderer);
    }
  }
  
  game_state_destroy(&state);
  destroy_score_textures(score_textures);

  TTF_CloseFont(font);
  SDL_DestroyTexture(textTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();
}
