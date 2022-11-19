#include <stdio.h>

/* 3rd-party libraries */
#include <SDL2/SDL.h>

/* Local Headers */
#include "paddle.h"
#include "constants.h"

const int PADDLE_HEIGHT = 60;
const int PADDLE_WIDTH = 10;

Paddle create_paddle(PaddleLocation_t loc)
{
  Paddle paddle;
  if (loc == LEFT_PADDLE)
  { 
    paddle.x = SCREEN_WIDTH - PADDLE_WIDTH;
    paddle.y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    paddle.w = PADDLE_WIDTH;
    paddle.h = PADDLE_HEIGHT;

    return paddle;
  } else if (loc == RIGHT_PADDLE)
  {
    paddle.x = 0;
    paddle.y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    paddle.w = PADDLE_WIDTH;
    paddle.h = PADDLE_HEIGHT;

    return paddle;
  }

  perror("Error creating paddle!");
  return paddle;
}
