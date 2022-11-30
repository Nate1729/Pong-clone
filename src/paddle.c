#include <stdio.h>

/* 3rd-party libraries */
#include <SDL2/SDL.h>

/* Local Headers */
#include "paddle.h"
#include "constants.h"

const int PADDLE_HEIGHT = 60;
const int PADDLE_WIDTH = 10;
const int PADDLE_SPEED = 8;
const int PADDLE_PADDING = 20;

Paddle paddle_create(PaddleLocation_t loc)
{
  Paddle paddle;
  if (loc == RIGHT_PADDLE)
  { 
    paddle.rect.x = SCREEN_WIDTH - (PADDLE_WIDTH + PADDLE_PADDING);
    paddle.rect.y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    paddle.rect.w = PADDLE_WIDTH;
    paddle.rect.h = PADDLE_HEIGHT;

    return paddle;
  } else if (loc == LEFT_PADDLE)
  {
    paddle.rect.x = PADDLE_PADDING;
    paddle.rect.y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    paddle.rect.w = PADDLE_WIDTH;
    paddle.rect.h = PADDLE_HEIGHT;

    return paddle;
  }

  perror("Error creating paddle!");
  return paddle;
}

void paddle_direction_update(Paddle *paddle, PaddleMoveDirection_t dir)
{
  paddle->move_dir = dir;
}

void paddle_move(Paddle *paddle)
{
  if (paddle->move_dir == PADDLE_STAY)
  {
    return;
  }

  if (paddle->move_dir == PADDLE_MOVE_UP && paddle->rect.y - PADDLE_SPEED > 0)
  {
    paddle->rect.y -= PADDLE_SPEED;
    return;
  }

  if (paddle->move_dir == PADDLE_MOVE_DOWN &&
      paddle->rect.y + paddle->rect.h + PADDLE_SPEED < SCREEN_HEIGHT)
  {
    paddle->rect.y += PADDLE_SPEED;
  }
}

int paddle_render(Paddle *paddle, SDL_Renderer *renderer)
{
  return SDL_RenderFillRect(renderer, &paddle->rect);
}

int paddle_left_edge(Paddle *paddle)
{
  return paddle->rect.x;
}

int paddle_right_edge(Paddle *paddle)
{
  return paddle->rect.x + paddle->rect.w;
}

int paddle_top_edge(Paddle *paddle)
{
  return paddle->rect.y;
}

int paddle_bottom_edge(Paddle *paddle)
{
  return paddle->rect.y + paddle->rect.h;
}
