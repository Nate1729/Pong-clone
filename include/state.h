#ifndef STATE_H
#define STATE_H

#include "paddle.h"
#include "ball.h"
#include "centerline.h"

typedef struct {
  Paddle left_paddle;
  Paddle right_paddle;
  Centerline centerline;
  Ball ball;
}GameState;


void game_state_initialize();
void game_state_destroy();

#endif
