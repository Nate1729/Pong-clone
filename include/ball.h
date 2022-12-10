#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

/* Constants */
extern const int BALL_WIDTH;

typedef enum BallEdge {
  BALL_EDGE_TOP,
  BALL_EDGE_BOTTOM,
  BALL_EDGE_LEFT,
  BALL_EDGE_RIGHT
} BallEdge_t;

typedef struct {
  int x_vel;
  int y_vel;
}Velocity;

typedef struct{
  SDL_Rect rect;
  Velocity vel;  
}Ball;


Ball ball_create();

void ball_update_position(Ball *ball);
void ball_reset(Ball *ball);
int ball_render(Ball *ball, SDL_Renderer *renderer);

int ball_left_edge(Ball *ball);
int ball_right_edge(Ball *ball);
int ball_top_edge(Ball *ball);
int ball_bottom_edge(Ball *ball);

void ball_print(Ball *ball);
#endif
