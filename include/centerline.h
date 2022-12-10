#ifndef CENTERLINE_H
#define CENTERLINE_H

#include <SDL2/SDL.h>

extern const unsigned line_partition_height;
extern const unsigned line_partition_width;

typedef struct {
  SDL_Rect *rects;
  int count;
}Centerline;


Centerline centerline_create();
void centerline_destroy(Centerline *centerline);

int centerline_render(Centerline *centerline, SDL_Renderer *renderer);
#endif
