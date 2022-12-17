#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

#include "scoreboard.h"
#include "constants.h"

const int SCOREBOARD_WIDTH = 50;
const int SCOREBOARD_HEIGHT = 50;
const int MAX_SCORE = 9;

Scoreboard scoreboard_left_create()
{
  int margin = 10;

  SDL_Rect rect = {
    .x=(SCREEN_WIDTH/2) - (SCOREBOARD_WIDTH + margin),
    .y=margin,
    .w=SCOREBOARD_WIDTH,
    .h=SCOREBOARD_HEIGHT
  };

  return (Scoreboard) {
    .rect=rect,
    .score=0
  };
}

Scoreboard scoreboard_right_create()
{
  int margin = 10;
  SDL_Rect rect = {
    .x=(SCREEN_WIDTH/2) + margin,
    .y=margin,
    .w=SCOREBOARD_WIDTH,
    .h=SCOREBOARD_HEIGHT
  };

  return (Scoreboard) {
    .rect=rect,
    .score=0,
  };
}

int scoreboard_render(Scoreboard *scoreboard, SDL_Renderer *renderer, SDL_Texture *score_texture)
{
  return SDL_RenderCopy(renderer, score_texture, NULL, &scoreboard->rect);
}

void fill_score_textures(SDL_Texture **score_textures, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer)
{
  SDL_Surface *temp_surface;
  
  temp_surface = TTF_RenderText_Solid(font, "0", color);
  score_textures[0] = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

  temp_surface = TTF_RenderText_Solid(font, "1", color);
  score_textures[1] = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

  temp_surface = TTF_RenderText_Solid(font, "2", color);
  score_textures[2] = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

  temp_surface = TTF_RenderText_Solid(font, "3", color);
  score_textures[3] = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

  temp_surface = TTF_RenderText_Solid(font, "4", color);
  score_textures[4] = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

 
  temp_surface = TTF_RenderText_Solid(font, "5", color);
  score_textures[5] = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

  temp_surface = TTF_RenderText_Solid(font, "6", color);
  score_textures[6] = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

  temp_surface = TTF_RenderText_Solid(font, "7", color);
  score_textures[7] = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

  temp_surface = TTF_RenderText_Solid(font, "8", color);
  score_textures[8] = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

  temp_surface = TTF_RenderText_Solid(font, "9", color);
  score_textures[9] = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);
}

void destroy_score_textures(SDL_Texture **score_textures)
{
  int i;
  for(i=0; i<MAX_SCORE+1; i++)
  {
    SDL_DestroyTexture(score_textures[i]);
  }
}
