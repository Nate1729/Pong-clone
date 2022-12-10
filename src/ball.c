#include <stdio.h>

#include <SDL2/SDL.h>

#include "ball.h"
#include "constants.h"

const int BALL_WIDTH = 5;

Ball ball_create()
{
  SDL_Rect rect = {
    .h=BALL_WIDTH,
    .w=BALL_WIDTH,
    .x=(SCREEN_WIDTH-BALL_WIDTH)/2,
    .y=0
  };

  Velocity initial_ball_velocity = {.x_vel=-8, .y_vel=5};

  return (Ball) {
    .rect=rect,
    .vel=initial_ball_velocity
  };
}

void ball_update_position(Ball *ball)
{
  /* Collision Detection */
  int edge_left = ball->rect.x;
  int edge_right = edge_left + ball->rect.w;
  int edge_top = ball->rect.y;
  int edge_bottom = edge_top + ball->rect.h;

  if (edge_left + ball->vel.x_vel < 0)
  {
    ball_reset(ball);
  }
  if (edge_right + ball->vel.x_vel > SCREEN_WIDTH)
  {
    ball_reset(ball);
  }
  if (edge_top + ball->vel.y_vel < 0)
  {
    ball->vel.y_vel *= -1;
  }
  if (edge_bottom + ball->vel.y_vel > SCREEN_HEIGHT)
  {
    ball->vel.y_vel *= -1;
  }

  /* Updating the ball position */
  ball->rect.x += ball->vel.x_vel;
  ball->rect.y += ball->vel.y_vel;
}

void ball_reset(Ball *ball)
{
  Ball new_ball = ball_create();
  memcpy(ball, &new_ball, sizeof(Ball));
}

int ball_render(Ball *ball, SDL_Renderer *renderer)
{
  int render_result;
  render_result = SDL_RenderFillRect(renderer, &ball->rect);

  return render_result;
}

/* Geometry Functions */
int ball_left_edge(Ball *ball)
{
  return ball->rect.x;
}

int ball_right_edge(Ball *ball)
{
  return ball->rect.x + ball->rect.w;
}

int ball_top_edge(Ball *ball)
{
  return ball->rect.y;
}

int ball_bottom_edge(Ball *ball)
{
  return ball->rect.y + ball->rect.h;
}

void ball_print(Ball *ball)
{
  printf("Ball-right-edge: %d, Ball velocity: %d\n", ball_right_edge(ball), ball->vel.x_vel);
}
