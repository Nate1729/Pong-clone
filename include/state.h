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



GameState game_state_initialize();
void game_state_destroy(GameState *state);

int game_state_render(GameState *state, SDL_Renderer *renderer);

#endif
