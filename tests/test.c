#include "chip8.h"
#include "opcodes.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <inttypes.h>

/**
 * Test function that determines if chip8_save_state and
 * chip8_load_state are working properly
 * 
 * @return void
*/
void test_chip8_save_state() {
    chip8_t test_chip;
    chip8_reset(&test_chip);  

    //Fill with random numbers
    test_chip.memory[0] = 0x12;
    test_chip.memory[1] = 0x34;
    test_chip.v[0] = 0xAB;
    test_chip.v[1] = 0xCD;
    test_chip.i = 0x1234;
    test_chip.pc = 0x200;
    test_chip.delay_timer = 0x11;
    test_chip.sound_timer = 0x22;
    test_chip.stack[0] = 0x4567;
    test_chip.stack[1] = 0x89AB;
    test_chip.sp = 1;
    test_chip.keypad[0] = 1;
    test_chip.keypad[1] = 0;
    test_chip.display[0] = 1;
    test_chip.display[1] = 0;
    test_chip.opcode = 0x1234;

    chip8_save_state(&test_chip, "testfile");

    FILE *file = fopen("testfile.bin", "rb");
    assert(file != NULL);
    fclose(file);

    chip8_t read_chip;
    chip8_reset(&read_chip);
    chip8_load_state(&read_chip, "testfile");

    //If working properly memory should look the same between test_chip and read_chip
    assert(memcmp(&test_chip, &read_chip, sizeof(chip8_t)) == 0);
    printf("Test passed: chip8_save_state and chip8_load_state\n");
}

/**
 * Test function to determine if opcode 00E0 is working properly.
 * 
 * @return void
*/
void
test_chip8_opcode_00E0()
{
    chip8_t chip;
    chip8_reset(&chip);
    chip.display[0] = 1;
    chip.display[2048] = 1;

    uint8_t display[DISPLAY_SIZE] = {0};

    opcode_00E0(&chip);

    //If working chip.display should be full of zeros
    assert(memcmp(chip.display, display, sizeof(display)) == 0);
    printf("Test passed: Opcode 00E0\n");
}

/**
 * Test function to determine if opcode 00EE is working properly.
 * 
 * @return void
*/
void
test_chip8_opcode_00EE()
{
    chip8_t chip;
    uint16_t stack_value = 0x20;
    chip8_reset(&chip);

    chip.stack[0] = stack_value;
    chip.sp++;

    opcode_00EE(&chip);

    //If working pc should have been set to stack_value and decereased sp by 1 to 0
    assert(chip.pc == stack_value);
    assert(chip.sp == 0);
    printf("Test passed: Opcode 00EE\n");
}

/**
 * Test function to determine if opcode 1nnn is working properly.
 * 
 * @return void
*/
void
test_chip8_opcode_1nnn()
{
    chip8_t chip;
    chip8_reset(&chip);
    uint16_t opcode_value = 0x1234;
    chip.opcode = opcode_value;

    opcode_1nnn(&chip);
    assert(chip.pc == (opcode_value & 0x0FFF));
    printf("Test passed: Opcode 1nnn\n");
}

void
test_chip8_opcode_2nnn()
{
    chip8_t chip;
    chip8_reset(&chip);
    uint16_t pc_value_before = 0x23;
    uint16_t opcode_value = 0x2345;
    chip.pc = pc_value_before;
    chip.opcode = opcode_value;

    opcode_2nnn(&chip);
    assert(chip.stack[--chip.sp] == pc_value_before);
    assert(chip.pc == (opcode_value & 0x0FFF));

    printf("Test passed: Opcode 2nnn\n");
}

void
test_chip8_opcode_3xkk()
{
    chip8_t chip;
    chip8_reset(&chip);

    uint16_t opcode_before = 0x3011;
    chip.v[0] = 0x11;
    chip.opcode = opcode_before;

    opcode_3xkk(&chip);
    assert(chip.pc == 0x202);

    chip.v[0] = 0x10;

    opcode_3xkk(&chip);
    assert(chip.pc == 0x202);

    printf("Test passed: Opcode 3xkk\n");
}

void
test_chip8_opcode_4xkk()
{
    chip8_t chip;
    chip8_reset(&chip);

    uint16_t opcode_before = 0x3011;
    chip.v[0] = 0x11;
    chip.opcode = opcode_before;

    opcode_4xkk(&chip);
    assert(chip.pc == 0x200);

    chip.v[0] = 0x10;

    opcode_4xkk(&chip);
    assert(chip.pc == 0x202);

    printf("Test passed: Opcode 4xkk\n");
}

void
test_chip8_opcode_5xy0()
{
    chip8_t chip;
    chip8_reset(&chip);
    uint8_t register_value_0 = 0x20;
    uint8_t register_value_1 = 0x20;
    uint8_t register_value_2 = 0x22;
    uint16_t opcode_first = 0x5020;
    uint16_t opcode_second = 0x5010;

    chip.v[0] = register_value_0;
    chip.v[1] = register_value_1;
    chip.v[2] = register_value_2;

    chip.opcode = opcode_first;
    opcode_5xy0(&chip);
    assert(chip.pc == 0x200);

    chip.opcode = opcode_second;
    opcode_5xy0(&chip);
    assert(chip.pc == 0x202);

    printf("Test passed: Opcode 5xy0\n");
}

void
test_chip8_opcode_6xkk()
{
    chip8_t chip;
    chip8_reset(&chip);
    chip.opcode = 0x6044;
    
    opcode_6xkk(&chip);
    assert(chip.v[0] == 0x44);

    printf("Test passed: Opcode 6xkk\n");
}

void
test_chip8_opcode_7xkk()
{
    chip8_t chip;
    chip8_reset(&chip);

    chip.opcode = 0x7011;
    
    opcode_7xkk(&chip);
    assert(chip.v[0] == 0x11);
    
    printf("Test passed: Opcode 7xkk\n");
}

void
test_chip8_opcode_8xy0()
{
    chip8_t chip;
    chip8_reset(&chip);
    uint8_t regist_y_value = 0x11;
    chip.opcode = 0x8010;
    chip.v[1] = regist_y_value;
    
    opcode_8xy0(&chip);
    assert(chip.v[0] == regist_y_value);

    printf("Test passed: Opcode 8xy0\n"); 
}

void
test_chip8_opcode_8xy1()
{
    chip8_t chip;
    chip8_reset(&chip);

    uint8_t register_x_value = 0x12;
    uint8_t register_y_value = 0x3;
    uint8_t result = register_x_value | register_y_value;

    chip.opcode = 0x8011;
    chip.v[0] = register_x_value;
    chip.v[1] = register_y_value;
    
    opcode_8xy0(&chip);
    assert(chip.v[0] == result);

    printf("Test passed: Opcode 8xy1\n");
}

void
test_chip8_opcode_8xy2()
{
    chip8_t chip;
    chip8_reset(&chip);

    uint8_t register_x_value = 0x12;
    uint8_t register_y_value = 0x3;
    uint8_t result = register_x_value & register_y_value;

    chip.opcode = 0x8012;
    chip.v[0] = register_x_value;
    chip.v[1] = register_y_value;

    opcode_8xy0(&chip);
    assert(chip.v[0] == result);

    printf("Test passed: Opcode 8xy2\n");
}

void
test_chip8_opcode_8xy3()
{
    chip8_t chip;
    chip8_reset(&chip);

    uint8_t register_x_value = 0x12;
    uint8_t register_y_value = 0x3;
    uint8_t result = register_x_value ^ register_y_value;

    chip.opcode = 0x8013;
    chip.v[0] = register_x_value;
    chip.v[1] = register_y_value;

    opcode_8xy0(&chip);
    assert(chip.v[0] == result);

    printf("Test passed: Opcode 8xy3\n");
}

void
test_chip8_opcode_8xy4()
{
    chip8_t chip;
    chip8_reset(&chip);
    
}

int
main()
{
    test_chip8_save_state();
    test_chip8_opcode_00E0();
    test_chip8_opcode_00EE();
    test_chip8_opcode_1nnn();
    test_chip8_opcode_2nnn();
    test_chip8_opcode_3xkk();
    test_chip8_opcode_4xkk();
    test_chip8_opcode_5xy0();
    test_chip8_opcode_6xkk();
    test_chip8_opcode_7xkk();
}