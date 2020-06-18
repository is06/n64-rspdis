#include <stdio.h>
#include "special.h"

void write_special_instruction(const unsigned char* instruction, FILE* file) {
    unsigned char opcode = get_special_opcode(instruction);
    switch (opcode) {
        case 0b000000: break;
        case 0b100000: fputs("add ", file); break;
        default:
            printf("Unsupported special opcode: %x\n", opcode);
            break;
    }
}

unsigned char get_special_opcode(const unsigned char* instruction) {
    unsigned char opcode = instruction[3] & 0b111111;

    return opcode;
}
