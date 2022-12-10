#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SDL2/SDL.h>

#include "constants.h"

extern const int SCOREBOARD_WIDTH;
extern const int SCOREBOARD_HEIGHT;

typedef struct {
  SDL_Rect rect;
  unsigned score;
}Scoreboard;

Scoreboard scoreboard_create();
#endif
