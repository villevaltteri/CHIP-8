#ifndef __helpers_h
#define _helpers_h

#define MAX_GAME_NAME_LENGHT 20

void
chip8_help();

char *
chip8_parse_args(int argc, char *argv[]);

char *
chip8_determine_game_name(char *filename);

#endif