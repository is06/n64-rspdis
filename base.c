#include <stdio.h>
#include "base.h"

void write_base_instruction_immediate(const unsigned char* instruction, FILE* file) {
    unsigned char rs = get_base_r0(instruction);
    unsigned char rt = get_base_r1(instruction);
    unsigned short immediate = get_base_immediate(instruction);
    fprintf(file, "%d, %d, %d", rt, rs, immediate);
}

void write_base_instruction_branch(const unsigned char* instruction, FILE* file) {
    unsigned char rs = get_base_r0(instruction);
    unsigned char rt = get_base_r1(instruction);
    unsigned short offset = get_base_immediate(instruction);
    fprintf(file, "%d, %d, %d", rs, rt, offset);
}

void write_base_instruction_branch_zero(const unsigned char* instruction, FILE* file) {
    unsigned char rs = get_base_r0(instruction);
    unsigned short offset = get_base_immediate(instruction);
    fprintf(file, "%d, %d", rs, offset);
}

void write_base_instruction_jump(const unsigned char* instruction, FILE* file) {
    unsigned int address = get_base_jump_address(instruction);
    fprintf(file, "$%x", address);
}

void write_base_instruction_loadstore(const unsigned char* instruction, FILE* file) {
    unsigned char base = get_base_r0(instruction);
    unsigned char rt = get_base_r1(instruction);
    unsigned short offset = get_base_immediate(instruction);
    fprintf(file, "%d, %d(%d)", rt, offset, base);
}

unsigned char get_base_r0(const unsigned char* instruction) {
    unsigned char r0 = instruction[0] & 0b00000011;
    unsigned char r1 = instruction[1] & 0b11100000;

    r0 = r0 << 3;
    r1 = r1 >> 5;

    return r0 | r1;
}

unsigned char get_base_r1(const unsigned char* instruction) {
    unsigned char r = instruction[1] & 0b00011111;

    return r;
}

unsigned short get_base_immediate(const unsigned char* instruction) {
    unsigned short imm = instruction[2] << 8;
    imm = imm & instruction[3];

    return imm;
}

unsigned int get_base_jump_address(const unsigned char* instruction) {
    unsigned int jump0 = instruction[0] & 0b00000011;
    unsigned int jump1 = instruction[1];
    unsigned int jump2 = instruction[2];
    unsigned int jump3 = instruction[3];

    jump0 = jump0 << 24;
    jump1 = jump1 << 16;
    jump2 = jump2 << 8;

    return jump0 | jump1 | jump2 | jump3;
}