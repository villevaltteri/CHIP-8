#ifndef _display_h
#define _display_h

#include "chip8.h"
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320

#define SCALE_FACTOR_X (WINDOW_WIDTH / DISPLAY_WIDHT)
#define SCALE_FACTOR_Y (WINDOW_HEIGHT / DISPLAY_HEIGHT)

void 
chip8_render_display(SDL_Renderer* renderer, chip8_t *chip);

#endif