#ifndef _chip8_h
#define _chip8_h

#include <inttypes.h>

#define FONTSET_SIZE 80
#define MEMORY_SIZE 4096
#define REGISTERS 16
#define STACK_SIZE 16
#define KEYPAD_SIZE 16
#define DISPLAY_SIZE DISPLAY_HEIGHT * DISPLAY_WIDHT
#define DISPLAY_WIDHT 64
#define DISPLAY_HEIGHT 32

typedef struct 
{
    uint8_t memory[MEMORY_SIZE];    // 4k memory
    uint8_t v[REGISTERS];           // 16 registers
    uint16_t i;                     // index register
    uint16_t pc;                    // program counter
    uint8_t delay_timer;            // delay timer
    uint8_t sound_timer;            // sound timer
    uint16_t stack[STACK_SIZE];     // 16-level stack
    uint8_t sp;                     // stack pointer
    uint8_t keypad[KEYPAD_SIZE];   // 16-key keypad
    uint32_t display[DISPLAY_SIZE];  // 64x32 display
    uint16_t opcode;                // current opcode 
}chip8_t;

/**
 * Save current values from chip8_t to a file.
 * 
 * @param chip Address of chip8_t struct
 * 
 * @return void
*/
void
chip8_save_state(chip8_t *chip, const char *filename);

/**
 * Loads saved state from a file to chip8_t struct.
 * 
 * @param chip Address of chip8_t struct
 * 
 * @return void
*/
void
chip8_load_state(chip8_t *chip, const char *filename);

/**
 * Sets everything in chip8_t struct to 0 except PC that is
 * set to 0x200 where first instruction is located.
 * 
 * @param chip Address of chip8_t struct
 * 
 * @return void
*/
void
chip8_reset(chip8_t *chip);

void
chip8_load_rom(chip8_t *chip, const char *filename);

void 
load_font_set(chip8_t *chip);

void 
chip8_cycle(chip8_t *chip);
#endif