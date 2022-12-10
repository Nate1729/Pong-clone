#include <SDL2/SDL.h>

#include "state.h"
#include "ball.h"
#include "paddle.h"
#include "centerline.h"


GameState game_state_initialize()
{
  return (GameState) {
    .left_paddle = paddle_create(LEFT_PADDLE),
    .right_paddle = paddle_create(RIGHT_PADDLE),
    .ball = ball_create(),
    .centerline = centerline_create()
  };
}

void game_state_destroy(GameState *state)
{
  centerline_destroy(&state->centerline);
}

int game_state_render(GameState *state, SDL_Renderer *renderer)
{
  /* Clear the screen */
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
  SDL_RenderClear(renderer);

  /* Render Game Objects */
  int success;
  success = SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  if (success < 0) 
  {
    printf("Error setting the renderer's draw color! SDL Error: %s\n", SDL_GetError());
    return success;
  }

  success = paddle_render(&state->left_paddle, renderer);
  if (success < 0)
  {
    printf("Error rendering the left paddle! SDL Error: %s\n", SDL_GetError());
    return success;
  }

  success = paddle_render(&state->right_paddle, renderer);
  if (success < 0)
  {
    printf("Error rendering the right paddle! SDL Error: %s\n", SDL_GetError());
    return success;
  }

  success = ball_render(&state->ball, renderer);
  if (success < 0)
  {
    printf("Error rendering the ball! SDL Error: %s\n", SDL_GetError());
    return success;
  }

  success = centerline_render(&state->centerline, renderer);
  if (success < 0)
  {
    printf("Error rendering the centerline! SDL Error: %s\n", SDL_GetError());
    return success;
  }

  return 0;
}
