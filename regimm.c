#include <stdio.h>
#include "regimm.h"

void write_regimm_instruction(const unsigned char* instruction, FILE* file) {
    unsigned char opcode = get_regimm_opcode(instruction);
    switch (opcode) {
        default:
            printf("Unsupported regimm opcode: %x\n", opcode);
            break;
    }
}

unsigned char get_regimm_opcode(const unsigned char* instruction) {
    unsigned char opcode = instruction[2] & 0b11111;

    return opcode;
}
