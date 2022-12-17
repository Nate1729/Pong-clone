#ifndef STATE_H
#define STATE_H

#include "paddle.h"
#include "ball.h"
#include "centerline.h"
#include "scoreboard.h"

typedef struct {
  Paddle left_paddle;
  Paddle right_paddle;
  Centerline centerline;
  Ball ball;
  Scoreboard left_scoreboard;
  Scoreboard right_scoreboard;
}GameState;



GameState game_state_initialize();
void game_state_destroy(GameState *state);
void check_paddle_ball_collision(GameState *state);
void game_state_update_objects(GameState *state);

int game_state_render(GameState *state, SDL_Renderer *renderer);

#endif
