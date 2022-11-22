#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

/* Types */
typedef struct {
  SDL_Rect rect;
  int move_dir;
}Paddle;

typedef enum PaddleLocation {
  LEFT_PADDLE,
  RIGHT_PADDLE
} PaddleLocation_t;

typedef enum PaddleMoveDirection {
  PADDLE_MOVE_UP,
  PADDLE_STAY,
  PADDLE_MOVE_DOWN
} PaddleMoveDirection_t;

/* Constants */
extern const int PADDLE_WIDTH;
extern const int PADDLE_HEIGHT;
extern const int PADDLE_SPEED;

/* Functions */
Paddle paddle_create(PaddleLocation_t loc);

void paddle_direction_update(Paddle *paddle, PaddleMoveDirection_t dir);
void paddle_move(Paddle *paddle);

/* Wrapper around `SDL_RenderDrawRect`.
 * The return value is just the result from
 * `SDL_RenderDrawRect */
int paddle_render(Paddle *paddle, SDL_Renderer *renderer);

#endif
