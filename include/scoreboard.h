#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "constants.h"

extern const int SCOREBOARD_WIDTH;
extern const int SCOREBOARD_HEIGHT;
extern const int MAX_SCORE;

typedef struct {
  SDL_Rect rect;
  unsigned score;
}Scoreboard;

Scoreboard scoreboard_left_create();
Scoreboard scoreboard_right_create();

int scoreboard_render(Scoreboard *scoreboard, SDL_Renderer *renderer, SDL_Texture *score_texture);

void fill_score_textures(SDL_Texture **score_textures, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer);
void destroy_score_textures(SDL_Texture **score_textures);
#endif
