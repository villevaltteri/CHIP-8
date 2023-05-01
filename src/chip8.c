#include "chip8.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void
chip8_reset(chip8_t *chip)
{
    memset(chip->memory, 0, MEMORY_SIZE);
    memset(chip->v, 0, REGISTERS);
    chip->i = 0;
    chip->pc = 0x200; // Program starts at memory location 0x200
    chip->delay_timer = 0;
    chip->sound_timer = 0;

    memset(chip->stack, 0, STACK_SIZE * sizeof(unsigned short));
    chip->sp = 0;
    
    memset(chip->keypad, 0, KEYPAD_SIZE);
    memset(chip->display, 0, DISPLAY_SIZE);
}

void
chip8_save_state(chip8_t *chip, const char *filename)
{
    char new_filename[strlen(filename) + 5];
    strcpy(new_filename, filename);
    strcat(new_filename, ".bin");

    FILE *file = fopen(new_filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "[ERROR] Could not open file %s for writing\n", filename);
        exit(1);
    }

    fwrite(chip, sizeof(chip8_t), 1, file);
    fclose(file);
}

void
chip8_load_state(chip8_t *chip, const char *filename)
{
    char new_filename[strlen(filename) + 5];
    strcpy(new_filename, filename);
    strcat(new_filename, ".bin");

    FILE *file = fopen(new_filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "[ERROR] Could not open file %s for reading\n", filename);
        exit(1);
    }

    fread(chip, sizeof(chip8_t), 1, file);
    fclose(file);
}

void
chip8_load_rom(chip8_t *chip, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if(file == NULL){
        fprintf(stderr, "[ERROR] Could not open file %s\n", filename);
        exit(1);
    }
    size_t size_of_rom;
    fseek(file, 0, SEEK_END);
    size_of_rom = ftell(file);
    rewind(file);

    size_t size_read = fread(chip->memory + 0x200, size_of_rom, 1, file);
    if(size_of_rom != size_read){
        fprintf(stderr, "[ERROR] Failed to read entire file %s\n", filename);
        exit(1);
    }
    fclose(file);
}
