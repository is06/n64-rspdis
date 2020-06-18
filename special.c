#include <stdio.h>
#include "special.h"

void write_special_instruction(const unsigned char* instruction, FILE* file) {
    unsigned char opcode = get_special_opcode(instruction);
    switch (opcode) {
        case 0b100000: fputs("add [TODO]", file); break;
        case 0b100001: fputs("addu [TODO]", file); break;
        case 0b100100: fputs("and [TODO]", file); break;
        case 0b001101: fputs("break", file); break;
        case 0b001001: fputs("jalr [TODO]", file); break;
        case 0b001000: fputs("jr [TODO]", file); break;
        case 0b000000: fputs("nop?/sll? [TODO]", file); break;   // NOP OR SLL
        case 0b100111: fputs("nor [TODO]", file); break;
        case 0b100101: fputs("or [TODO]", file); break;
        case 0b000100: fputs("sllv [TODO]", file); break;
        case 0b101010: fputs("slt [TODO]", file); break;
        case 0b101011: fputs("sltu [TODO]", file); break;
        case 0b000011: fputs("sra [TODO]", file); break;
        case 0b000111: fputs("srav [TODO]", file); break;
        case 0b000010: fputs("srl [TODO]", file); break;
        case 0b000110: fputs("srlv [TODO]", file); break;
        case 0b100010: fputs("sub [TODO]", file); break;
        case 0b100011: fputs("subu [TODO]", file); break;
        case 0b100110: fputs("xor [TODO]", file); break;
        default:
            printf("Unsupported special opcode: %x\n", opcode);
            break;
    }
}

unsigned char get_special_opcode(const unsigned char* instruction) {
    unsigned char opcode = instruction[3] & 0b111111;

    return opcode;
}
