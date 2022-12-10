#include <SDL2/SDL.h>

#include "constants.h"
#include "centerline.h"

const unsigned line_partition_height = 20;
const unsigned line_partition_width = 6;

Centerline centerline_create()
{
  /* Getting memory for rectangle */
  unsigned count = ((unsigned) SCREEN_HEIGHT)/(line_partition_height*2);
  SDL_Rect *centerline_rects = malloc(count * sizeof(SDL_Rect));

  /* Filling rectangle */
  unsigned i;
  for(i=0; i<count; i++)
  {
    centerline_rects[i].x = (SCREEN_WIDTH - line_partition_width)/2;
    centerline_rects[i].y = SCREEN_HEIGHT - (line_partition_height * 2 * i);
    centerline_rects[i].w = line_partition_width;
    centerline_rects[i].h = line_partition_height; 
  }

  return (Centerline) {
    .rects=centerline_rects,
    .count=count
  };
}


void centerline_destroy(Centerline *centerline)
{
  free(centerline->rects);
}

int centerline_render(Centerline *centerline, SDL_Renderer *renderer)
{
  return SDL_RenderFillRects(renderer, centerline->rects, centerline->count); 
}
