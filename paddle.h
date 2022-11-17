#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

/* Types */
typedef SDL_Rect Paddle;

typedef enum PaddleLocation {
  LEFT_PADDLE,
  RIGHT_PADDLE
} PaddleLocation_t;

/* Constants */
extern const int PADDLE_WIDTH;
extern const int PADDLE_HEIGHT;

Paddle create_paddle(PaddleLocation_t loc);

#endif
