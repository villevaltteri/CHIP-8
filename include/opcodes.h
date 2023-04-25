#ifndef _opcodes_h
#define _opcodes_h

#include "chip8.h"
#include <inttypes.h>

typedef void (*opcode_func_t)(chip8_t*);
extern opcode_func_t opcode_table[];

/**
 * Determines which 0 beginning (00E0 or 00EE)
 * opcode is.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_0000(chip8_t*);

/**
 * Clear the display.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_00E0(chip8_t *chip);

/**
 * Return from a subroutine. Set program counter to 
 * the address at the top of stack, subtracts 1 from 
 * stack pointer
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void 
opcode_00EE(chip8_t *chip);

/**
 * Jump to location nnn. Sets program counter to nnn
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_1nnn(chip8_t *chip);

/**
 * Call subroutine at nnn. Increments stack pointer,
 * then puts current PC on the top of the stack. PC is
 * then set to nnn.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_2nnn(chip8_t *chip);

/**
 * Skip next instruction if Vx = kk. If register Vx is 
 * equal to kk, increments PC by 2.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_3xkk(chip8_t *chip);

/**
 * Skip next instruction if Vx != kk.
 * If register Vx is not equal to kk, increments
 * PC by 2.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_4xkk(chip8_t *chip);

/**
 * Skip next instruction if Vx = Vy. Compares register Vx
 * to register Vy, and if they are equal, increments PC by 2.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_5xy0(chip8_t *chip);

/**
 * Set Vx = kk. Puts the value kk into register Vx.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void 
opcode_6xkk(chip8_t *chip);

/**
 * Set Vx = Vx + kk. Adds the value kk to the value
 * of register Vx, then stores the result in Vx.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_7xkk(chip8_t *chip);

/**
 * 9 Different opcodes which start with 8. Determines which 
 * opcode should be called if it isnt 8xy0 in which case
 * sets V[x] = V[y].
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void 
opcode_8xy0(chip8_t *chip);

/**
 * Performs a bitwise OR on the values of V[x] and V[y],
 * then stores the result in V[x].
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_8xy1(chip8_t *chip);

/**
 * Performs a bitwise AND on the values of V[x] and V[y], 
 * then stores the result in V[x].
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_8xy2(chip8_t *chip);

/**
 * Performs a bitwise XOR on the values of V[x] and V[y],
 * then stores the result in V[x].
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_8xy3(chip8_t *chip);

/**
 * The values of Vx and Vy are added together. If the result is greater
 * than 8 bits (i.e., > 255), Vf is set to 1, otherwise 0. Lowest 8bits
 * of the result are kept and stored in Vx.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_8xy4(chip8_t *chip);

/**
 * If Vx > Vy, then Vf is set to 1, otherwise 0. Then Vy is subtracted 
 * from Vx, and the result is stored in Vx.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_8xy5(chip8_t *chip);


/**
 * If the least-significant bit of Vx is 1, then Vf is set to 1,
 * otherwise 0. Then Vx is divided by 2.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_8xy6(chip8_t *chip);

/**
 * If Vy > Vx, then Vf is set to 1, otherwise 0. Then Vy is
 * subtracted from Vx, and the result is stored in Vx.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_8xy7(chip8_t *chip);

/**
 * If the most-significant bit of Vx is 1, then Vf is set to 1,
 * otherwise 0. Then Vx is multiplied by 2.
 * 
 * @param chip Address of chip8_t object
 * @return void
*/
void
opcode_8xyE(chip8_t *chip);

void
opcode_9xy0(chip8_t *chip);

void
opcode_Annn(chip8_t *chip);

#endif