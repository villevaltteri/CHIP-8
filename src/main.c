#include "display.h"
#include "chip8.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320

#define SCALE_FACTOR_X (WINDOW_WIDTH / DISPLAY_WIDHT)
#define SCALE_FACTOR_Y (WINDOW_HEIGHT / DISPLAY_HEIGHT)



int
main(int argc, char **argv)
{
    if(argc < 2){
        chip8_help();
    }
    char *filename = chip8_parse_args(argc, argv);
    if(filename == NULL){
        fprintf(stderr, "[ERROR] Filename NULL\n");
        exit(1);
    }
    chip8_t chip;
    chip8_reset(&chip);
    chip8_load_rom(&chip, filename);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Chip8 Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    int quit = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
				case SDL_QUIT:
				{
					quit = true;
				} break;

				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						{
							quit = true;
						} break;

						case SDLK_x:
						{
							chip.keypad[0] = 1;
						} break;

						case SDLK_1:
						{
							chip.keypad[1] = 1;
						} break;

						case SDLK_2:
						{
							chip.keypad[2] = 1;
						} break;

						case SDLK_3:
						{
							chip.keypad[3] = 1;
						} break;

						case SDLK_q:
						{
							chip.keypad[4] = 1;
						} break;

						case SDLK_w:
						{
							chip.keypad[5] = 1;
						} break;

						case SDLK_e:
						{
							chip.keypad[6] = 1;
						} break;

						case SDLK_a:
						{
							chip.keypad[7] = 1;
						} break;

						case SDLK_s:
						{
							chip.keypad[8] = 1;
						} break;

						case SDLK_d:
						{
							chip.keypad[9] = 1;
						} break;

						case SDLK_z:
						{
							chip.keypad[0xA] = 1;
						} break;

						case SDLK_c:
						{
							chip.keypad[0xB] = 1;
						} break;

						case SDLK_4:
						{
							chip.keypad[0xC] = 1;
						} break;

						case SDLK_r:
						{
							chip.keypad[0xD] = 1;
						} break;

						case SDLK_f:
						{
							chip.keypad[0xE] = 1;
						} break;

						case SDLK_v:
						{
							chip.keypad[0xF] = 1;
						} break;
					}
				} break;

				case SDL_KEYUP:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_x:
						{
							chip.keypad[0] = 0;
						} break;

						case SDLK_1:
						{
							chip.keypad[1] = 0;
						} break;

						case SDLK_2:
						{
							chip.keypad[2] = 0;
						} break;

						case SDLK_3:
						{
							chip.keypad[3] = 0;
						} break;

						case SDLK_q:
						{
							chip.keypad[4] = 0;
						} break;

						case SDLK_w:
						{
							chip.keypad[5] = 0;
						} break;

						case SDLK_e:
						{
							chip.keypad[6] = 0;
						} break;

						case SDLK_a:
						{
							chip.keypad[7] = 0;
						} break;

						case SDLK_s:
						{
							chip.keypad[8] = 0;
						} break;

						case SDLK_d:
						{
							chip.keypad[9] = 0;
						} break;

						case SDLK_z:
						{
							chip.keypad[0xA] = 0;
						} break;

						case SDLK_c:
						{
							chip.keypad[0xB] = 0;
						} break;

						case SDLK_4:
						{
							chip.keypad[0xC] = 0;
						} break;

						case SDLK_r:
						{
							chip.keypad[0xD] = 0;
						} break;

						case SDLK_f:
						{
							chip.keypad[0xE] = 0;
						} break;

						case SDLK_v:
						{
							chip.keypad[0xF] = 0;
						} break;
					}
				} break;
			}
        }
		chip8_render_display(renderer, &chip);
        chip8_cycle(&chip);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free(filename);
}