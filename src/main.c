#include "chip8.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    free(filename);
}