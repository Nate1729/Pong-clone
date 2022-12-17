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
    .centerline = centerline_create(),
    .left_scoreboard = scoreboard_left_create(),
    .right_scoreboard = scoreboard_right_create(),
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

void check_paddle_ball_collision(GameState *state)
{
  if (ball_left_edge(&state->ball) > paddle_right_edge(&state->left_paddle)
      && ball_left_edge(&state->ball) + state->ball.vel.x_vel < paddle_right_edge(&state->left_paddle))
  {
    if (ball_bottom_edge(&state->ball) >= paddle_top_edge(&state->left_paddle) &&
        ball_top_edge(&state->ball) <= paddle_bottom_edge(&state->left_paddle))
    {
      state->ball.vel.x_vel = -state->ball.vel.x_vel;
    }
  } else if (
      ball_right_edge(&state->ball) < paddle_right_edge(&state->right_paddle) &&
      ball_right_edge(&state->ball) + state->ball.vel.x_vel > paddle_left_edge(&state->right_paddle))
  {
    if (ball_bottom_edge(&state->ball) >= paddle_top_edge(&state->right_paddle) &&
        ball_top_edge(&state->ball) <= paddle_bottom_edge(&state->right_paddle))
    {
      state->ball.vel.x_vel = -state->ball.vel.x_vel;
    }    
  }
}

void game_state_update_objects(GameState *state)
{
  paddle_move(&state->left_paddle);
  paddle_move(&state->right_paddle);
  check_paddle_ball_collision(state);
  int temp = ball_update_position(&state->ball);
  if (temp == LEFT_PLAYER_SCORE)
  {
    state->left_scoreboard.score += 1;
  }
  else if (temp == RIGHT_PLAYER_SCORE)
  {
    state->right_scoreboard.score += 1;
  }
}
