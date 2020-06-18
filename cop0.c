#include <stdio.h>
#include "cop0.h"

void write_cop0_instruction(const unsigned char* instruction, FILE* file) {
    unsigned char opcode = get_cop0_opcode(instruction);
    switch (opcode) {
        case 0b00000:
            fputs("mfc0 ", file);
            write_cop0_instruction_rest(instruction, file);
            break;
        case 0b00100:
            fputs("mtc0 ", file);
            write_cop0_instruction_rest(instruction, file);
            break;
        default:
            printf("Unsupported cop0 opcode: %x\n", opcode);
            break;
    }
}

void write_cop0_instruction_rest(const unsigned char* instruction, FILE* file) {
    fprintf(file, "%d, ", get_cop0_rt(instruction));
    fprintf(file, "%d", get_cop0_rd(instruction));
}

unsigned char get_cop0_opcode(const unsigned char* instruction) {
    unsigned char opcode0 = instruction[0] & 0b11;
    unsigned char opcode1 = instruction[1] & 0b11100000;

    opcode0 = opcode0 << 5;
    opcode1 = opcode1 >> 5;

    return opcode0 | opcode1;
}

unsigned char get_cop0_rt(const unsigned char* instruction) {
    return instruction[1] & 0b11111;
}

unsigned char get_cop0_rd(const unsigned char* instruction) {
    unsigned char rd = instruction[2] & 0b11111000;

    return rd >> 3;
}
