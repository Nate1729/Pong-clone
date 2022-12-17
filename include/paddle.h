#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

/* Types */
typedef enum PaddleLocation {
  LEFT_PADDLE,
  RIGHT_PADDLE
} PaddleLocation_t;

typedef enum PaddleMoveDirection {
  PADDLE_MOVE_UP,
  PADDLE_STAY,
  PADDLE_MOVE_DOWN
} PaddleMoveDirection_t;

typedef struct {
  SDL_Rect rect;
  PaddleMoveDirection_t move_dir;
}Paddle;

/* Constants */
extern const int PADDLE_WIDTH;
extern const int PADDLE_HEIGHT;
extern const int PADDLE_SPEED;
extern const int PADDLE_PADDING;

/* Functions */
Paddle paddle_create(PaddleLocation_t loc);

void paddle_direction_update(Paddle *paddle, PaddleMoveDirection_t dir);
void paddle_move(Paddle *paddle);

/* Paddle edget Getters */
int paddle_left_edge(Paddle *paddle);
int paddle_right_edge(Paddle *paddle);
int paddle_top_edge(Paddle *paddle);
int paddle_bottom_edge(Paddle *paddle);

/* Wrapper around `SDL_RenderDrawRect`.
 * The return value is just the result from
 * `SDL_RenderDrawRect */
int paddle_render(Paddle *paddle, SDL_Renderer *renderer);

#endif
