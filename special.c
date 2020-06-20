#include <stdio.h>
#include "special.h"

void write_special_instruction(const unsigned char* instruction, FILE* file) {
    unsigned char opcode = get_special_opcode(instruction);
    switch (opcode) {
        case 0b100000: fputs("add ", file); write_special_instruction_rest(instruction, file); break;
        case 0b100001: fputs("addu ", file); write_special_instruction_rest(instruction, file); break;
        case 0b100100: fputs("and ", file); write_special_instruction_rest(instruction, file); break;
        case 0b001101: fputs("break", file); break;
        case 0b001001: fputs("jalr ", file); write_special_jump(instruction, file); break;
        case 0b001000: fputs("jr ", file); write_special_jump(instruction, file); break;
        case 0b000000: write_special_nop_or_sll(instruction, file); break;
        case 0b100111: fputs("nor ", file); write_special_instruction_rest(instruction, file); break;
        case 0b100101: fputs("or ", file); write_special_instruction_rest(instruction, file); break;
        case 0b000100: fputs("sllv ", file); write_special_instruction_rest(instruction, file); break;
        case 0b101010: fputs("slt ", file); write_special_instruction_rest(instruction, file); break;
        case 0b101011: fputs("sltu ", file); write_special_instruction_rest(instruction, file); break;
        case 0b000011: fputs("sra ", file); write_special_shift(instruction, file); break;
        case 0b000111: fputs("srav ", file); write_special_instruction_rest(instruction, file); break;
        case 0b000010: fputs("srl ", file); write_special_shift(instruction, file); break;
        case 0b000110: fputs("srlv ", file); write_special_instruction_rest(instruction, file); break;
        case 0b100010: fputs("sub ", file); write_special_instruction_rest(instruction, file); break;
        case 0b100011: fputs("subu ", file); write_special_instruction_rest(instruction, file); break;
        case 0b100110: fputs("xor ", file); write_special_instruction_rest(instruction, file); break;
        default:
            printf("Unsupported special opcode: %x\n", opcode);
            break;
    }
}

static void write_special_nop_or_sll(const unsigned char* instruction, FILE* file) {
    if (instruction[0] != 0 || instruction[1] != 0 || instruction[2] != 0 || instruction[3] != 0) {
        fputs("sll ", file);
        write_special_shift(instruction, file);
        return;
    }

    fputs("nop", file);
}

static void write_special_instruction_rest(const unsigned char* instruction, FILE* file) {
    unsigned char rs = get_special_rs(instruction);
    unsigned char rt = get_special_rt(instruction);
    unsigned char rd = get_special_rd(instruction);

    fprintf(file, "%d, %d, %d", rs, rt, rd);
}

static void write_special_jump(const unsigned char* instruction, FILE* file) {
    unsigned char rs = get_special_rs(instruction);
    unsigned char rd = get_special_rd(instruction);

    if (rd == 0) {
        fprintf(file, "%d", rs);
        return;
    }
    fprintf(file, "%d, %d", rs, rd);
}

static void write_special_shift(const unsigned char* instruction, FILE* file) {
    unsigned char rt = get_special_rt(instruction);
    unsigned char rd = get_special_rd(instruction);
    unsigned char sa = get_special_sa(instruction);

    fprintf(file, "%d, %d, %d", rd, rt, sa);
}

static unsigned char get_special_opcode(const unsigned char* instruction) {
    unsigned char opcode = instruction[3] & 0b111111;

    return opcode;
}

static unsigned char get_special_rs(const unsigned char* instruction) {
    unsigned char rs0 = instruction[0] & 0b00000011;
    unsigned char rs1 = instruction[1] & 0b11100000;

    rs0 = rs0 << 3;
    rs1 = rs1 >> 5;

    return rs0 | rs1;
}

static unsigned char get_special_rt(const unsigned char* instruction) {
    return instruction[1] & 0b00011111;
}

static unsigned char get_special_rd(const unsigned char* instruction) {
    return instruction[2] & 0b11111000;
}

static unsigned char get_special_sa(const unsigned char* instruction) {
    unsigned char sa2 = instruction[2] & 0b00000111;
    unsigned char sa3 = instruction[3] & 0b11000000;

    sa2 = sa2 << 2;
    sa3 = sa3 >> 6;

    return sa2 | sa3;
}