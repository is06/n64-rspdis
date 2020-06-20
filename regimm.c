#include <stdio.h>
#include "regimm.h"

void write_regimm_instruction(const unsigned char* instruction, FILE* file) {
    unsigned char opcode = get_regimm_opcode(instruction);
    switch (opcode) {
        case 0b00001: fputs("bgez ", file); write_regimm_instruction_rest(instruction, file); break;
        case 0b10001: fputs("bgezal ", file); write_regimm_instruction_rest(instruction, file); break;
        case 0b00000: fputs("bltz ", file); write_regimm_instruction_rest(instruction, file); break;
        case 0b10000: fputs("bltzal ", file); write_regimm_instruction_rest(instruction, file); break;
        default:
            printf("Unsupported regimm opcode: %x\n", opcode);
            fputs("[unknown]", file);
            break;
    }
}

void write_regimm_instruction_rest(const unsigned char* instruction, FILE* file) {
    unsigned short offset = get_regimm_offset(instruction);
    unsigned char rs = get_regimm_rs(instruction);

    fprintf(file, "%d, %d", rs, offset);
}

unsigned char get_regimm_opcode(const unsigned char* instruction) {
    unsigned char opcode = instruction[2] & 0b00011111;

    return opcode;
}

unsigned char get_regimm_rs(const unsigned char* instruction) {
    unsigned char r0 = instruction[0] & 0b00000011;
    unsigned char r1 = instruction[1] & 0b11100000;

    r0 = r0 << 3;
    r1 = r1 >> 5;

    return r0 | r1;
}

unsigned short get_regimm_offset(const unsigned char* instruction) {
    unsigned short offset = instruction[2] << 8;
    offset = offset & instruction[3];

    return offset;
}
