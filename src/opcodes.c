#include "opcodes.h"
#include "chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


opcode_func_t opcode_table[] = {
    opcode_0000,
    opcode_1nnn,
    opcode_2nnn,
    opcode_3xkk,
    opcode_4xkk,
    opcode_5xy0,
    opcode_6xkk,
    opcode_7xkk,
    opcode_8xy0,
    opcode_9xy0,
    opcode_Annn,
    opcode_Bnnn,
    opcode_Cxkk,
    opcode_Dxyn,
    opcode_Ex00,
    opcode_Fx00
};


void
opcode_0000(chip8_t *chip)
{
    if(chip->opcode == 0x00E0) {
        opcode_00E0(chip);
    } else if (chip->opcode == 0x00EE) {
        opcode_00EE(chip);
    } else {
        fprintf(stderr, "[ERROR] Unrecognized opcode: %X\n", chip->opcode);
        exit(1);
    }
}

void
opcode_00E0(chip8_t *chip)
{
    memset(chip->display, 0, MEMORY_SIZE);
}

void
opcode_00EE(chip8_t *chip)
{
    chip->pc = chip->stack[--chip->sp];
}

void
opcode_1nnn(chip8_t *chip)
{
    chip->pc = chip->opcode & 0x0FFF;
}

void
opcode_2nnn(chip8_t *chip)
{
    chip->stack[chip->sp++] = chip->pc;
    chip->pc = chip->opcode & 0x0FFF;
}

void
opcode_3xkk(chip8_t *chip)
{
    if (chip->v[(chip->opcode & 0x0F00) >> 8] == (chip->opcode &0x00FF)) {
        chip->pc += 2;
    }
}

void
opcode_4xkk(chip8_t *chip)
{
    if (chip->v[(chip->opcode & 0x0F00) >> 8] != (chip->opcode &0x00FF)) {
        chip->pc += 2;
    }   
}

void 
opcode_5xy0(chip8_t *chip)
{
    if (chip->v[(chip->opcode & 0x0F00) >> 8] == chip->v[(chip->opcode & 0x00F0) >> 4]) {
        chip->pc += 2;
    }
}

void
opcode_6xkk(chip8_t *chip)
{
    chip->v[(chip->opcode & 0x0F00) >> 8] = chip->opcode & 0x00FF;
}

void
opcode_7xkk(chip8_t *chip)
{
    chip->v[(chip->opcode & 0x0F00) >> 8] += chip->opcode & 0x00FF;
}

void
opcode_8xy0(chip8_t *chip)
{
    switch(chip->opcode & 0x000F){
        case 0:
            chip->v[(chip->opcode & 0x0F00) >> 8] = chip->v[(chip->opcode & 0x00F0) >> 4];
            break;
        case 1:
            opcode_8xy1(chip);
            break;
        case 2:
            opcode_8xy2(chip);
            break;
        case 3:
            opcode_8xy3(chip);
            break;
        case 4:
            opcode_8xy4(chip);
            break;
        case 5:
            opcode_8xy5(chip);
            break;
        case 6:
            opcode_8xy6(chip);
            break;
        case 7:
            opcode_8xy7(chip);
            break;
        case 0xE:
            opcode_8xyE(chip);
            break;
        default:
            fprintf(stderr, "[ERROR] Did not recognize opcode %X\n", chip->opcode);
            exit(1);
            break;
    }
}

void
opcode_8xy1(chip8_t *chip)
{ 
    chip->v[(chip->opcode & 0x0F00) >> 8] |= chip->v[(chip->opcode & 0x00F0) >> 4];
}

void
opcode_8xy2(chip8_t *chip)
{
    chip->v[(chip->opcode & 0x0F00) >> 8] &= chip->v[(chip->opcode & 0x00F0) >> 4];
}

void
opcode_8xy3(chip8_t *chip)
{
    chip->v[(chip->opcode & 0x0F00) >> 8] ^= chip->v[(chip->opcode & 0x00F0) >> 4];
}

void
opcode_8xy4(chip8_t *chip)
{
    uint16_t sum = chip->v[(chip->opcode & 0x0F00) >> 8] + chip->v[(chip->opcode & 0x00F0) >> 4];
    chip->v[(chip->opcode & 0x0F00) >> 8] = sum & 0xFF;
    chip->v[0xF] = (sum > 0xFF) ? 1 : 0;
}

void
opcode_8xy5(chip8_t *chip)
{
    chip->v[0xF] = (chip->v[(chip->opcode & 0x0F00) >> 8] > chip->v[(chip->opcode & 0x00F0) >> 4])
                    ? 1 : 0;
    
    chip->v[(chip->opcode & 0x0F00) >> 8] -= chip->v[(chip->opcode & 0x00F0) >> 4];
}

void
opcode_8xy6(chip8_t *chip)
{
    chip->v[0xF] = (chip->v[(chip->opcode & 0x0F00) >> 8] & 0x1);
    chip->v[(chip->opcode & 0x0F00) >> 8] >>= 1;
}

void 
opcode_8xy7(chip8_t *chip)
{
    chip->v[0xF] = (chip->v[(chip->opcode & 0x00F0) >> 4] > chip->v[(chip->opcode & 0x0F00) >> 8]) 
                    ? 1 : 0;
    
    chip->v[(chip->opcode & 0x0F00) >> 8] = chip->v[(chip->opcode & 0x00F0) >> 4] - chip->v[(chip->opcode & 0x0F00) >> 8];
}

void
opcode_8xyE(chip8_t *chip)
{
    chip->v[0xF] = (chip->v[(chip->opcode & 0x0F00) >> 8] >> 7) & 0x1;
    chip->v[(chip->opcode & 0x0F00) >> 8] <<= 1;
}

void
opcode_9xy0(chip8_t *chip)
{
    if(chip->v[(chip->opcode & 0x0F00) >> 8] != chip->v[(chip->opcode & 0x00F0) >> 4]){
        chip->pc += 2;
    }
}

void
opcode_Annn(chip8_t *chip)
{
    chip->i = (chip->opcode & 0x0FFF);
}

void
opcode_Bnnn(chip8_t *chip)
{
    chip->pc = (chip->opcode & 0x0FFF) + chip->v[0];
}

void 
opcode_Cxkk(chip8_t *chip)
{
    uint8_t random_number = rand() % 256;

    chip->v[(chip->opcode & 0x0F00) >> 8] = (chip->opcode & 0x00FF) & random_number;
}

void
opcode_Dxyn(chip8_t *chip)
{
    unsigned short x = chip->v[(chip->opcode & 0x0F00) >> 8];
    unsigned short y = chip->v[(chip->opcode & 0x00F0) >> 4];
    unsigned short height = chip->opcode & 0x000F;
    unsigned short pixel;
    chip->v[0xF] = 0;
    int screenx = 64;

    for (int yline = 0; yline < height; yline++){
        pixel = chip->memory[chip->i + yline];
        for (int xline = 0; xline < 8; xline++){
            if ((pixel & (0x80 >> xline)) != 0){
                if (chip->display[(x + xline + ((y + yline) * screenx))] == 1){
                    chip->v[0xF] = 1;                                    
                }
                chip->display[x + xline + ((y + yline) * screenx)] ^= 1;
            }
        }
    }
}

void
opcode_Ex00(chip8_t *chip)
{
    switch((chip->opcode & 0x000F)){
        case 0xE:
            opcode_Ex9E(chip);
            break;
        case 0x1:
            opcode_ExA1(chip);
            break;
        default:
            fprintf(stderr, "[ERROR] Did not recognize opcode %X\n",
            chip->opcode);
            break;
    }
}

void
opcode_Ex9E(chip8_t *chip)
{
    uint8_t key = chip->v[(chip->opcode & 0x0F00) >> 8];
    if(chip->keypad[key]){
        chip->pc += 2;
    }
}

void
opcode_ExA1(chip8_t *chip)
{
    uint8_t key = chip->v[(chip->opcode & 0x0F00) >> 8];
    if(!chip->keypad[key]){
        chip->pc += 2;
    }
}

void 
opcode_Fx00(chip8_t *chip)
{
    switch((chip->opcode & 0x00FF)){
        case 0x07:
            opcode_Fx07(chip);
            break;
        case 0x0A:
            opcode_Fx0A(chip);
            break;
        case 0x15:
            opcode_Fx15(chip);
            break;
        case 0x18:
            opcode_Fx18(chip);
            break;
        case 0x1E:
            opcode_Fx1E(chip);
            break;
        case 0x29:
            opcode_Fx29(chip);
            break;
        case 0x33:
            opcode_Fx33(chip);
            break;
        case 0x55:
            opcode_Fx55(chip);
            break;
        case 0x65:
            opcode_Fx65(chip);
            break;
        default:
            fprintf(stderr, "[ERROR] Did not recongize opcode %X\n", chip->opcode);       
    }
}

void
opcode_Fx07(chip8_t *chip)
{
    chip->v[(chip->opcode & 0x0F00) >> 8] = chip->delay_timer;
}

void
opcode_Fx0A(chip8_t *chip)
{
    int keyPress = 0;

    for(int i = 0; i < KEYPAD_SIZE; i++){
        if(chip->keypad[i] != 0){
            chip->v[(chip->opcode & 0x0F00) >> 8] = i;
            keyPress = 1;
        } 
    }
    if(!keyPress){
        chip->pc -= 2;
    }
}

void
opcode_Fx15(chip8_t *chip)
{
    chip->delay_timer = chip->v[(chip->opcode & 0x0F00) >> 8];
}

void
opcode_Fx18(chip8_t *chip)
{
    chip->sound_timer = chip->v[(chip->opcode & 0x0F00) >> 8];
}

void
opcode_Fx1E(chip8_t *chip)
{
    chip->i += chip->v[(chip->opcode & 0x0F00) >> 8];
}

void
opcode_Fx29(chip8_t *chip)
{
    uint8_t vx = (chip->opcode & 0x0F00) >> 8;
    uint8_t digit = chip->v[vx];
    chip->i = 0x50 + (5 *digit);
}

void
opcode_Fx33(chip8_t *chip)
{
    uint8_t value = chip->v[(chip->opcode & 0x0F00) >> 8];

    chip->memory[chip->i + 2] = value % 10;
    value /= 10;

    chip->memory[chip->i + 1] = value % 10;
    value /= 10;

    chip->memory[chip->i] = value % 10;

}

void
opcode_Fx55(chip8_t *chip)
{
    uint8_t vx = (chip->opcode & 0x0F00) >> 8;
    for(uint8_t i = 0; i <= vx; i++){
        chip->memory[chip->i + i] = chip->v[i];
    }
}

void
opcode_Fx65(chip8_t *chip)
{
    uint8_t vx = (chip->opcode & 0x0F00) >> 8;
    for(uint8_t i = 0; i <= vx; i++){
        chip->v[i] = chip->memory[chip->i + i];
    }
}