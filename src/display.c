#include "display.h"
#include "chip8.h"
#include <SDL2/SDL.h>


void 
chip8_render_display(SDL_Renderer* renderer, chip8_t *chip)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDHT; x++) {
            if (chip->display[y * DISPLAY_WIDHT + x] == 1) {
                SDL_Rect rect = {x * SCALE_FACTOR_X, y * SCALE_FACTOR_Y, SCALE_FACTOR_X, SCALE_FACTOR_Y};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}


