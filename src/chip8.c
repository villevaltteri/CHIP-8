#include "chip8.h"
#include "opcodes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void
load_font_set(chip8_t *chip)
{
    for(unsigned i = 0; i < FONTSET_SIZE; i++){
        chip->memory[0x50 + i] = fontset[i];
    }
}

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
    load_font_set(chip);
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

    size_t size_read = fread(chip->memory + 0x200, 1, size_of_rom, file);
    if(size_of_rom != size_read){
        fprintf(stderr, "[ERROR] Failed to read entire file %s\n", filename);
        exit(1);
    }
    fclose(file);
}

void
chip8_cycle(chip8_t *chip)
{
    chip->opcode = (chip->memory[chip->pc] << 8) | chip->memory[chip->pc + 1];
    chip->pc += 2;
    opcode_table[(chip->opcode & 0xF000) >> 12](chip);
}