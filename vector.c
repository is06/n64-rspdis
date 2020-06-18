#include <stdio.h>
#include "vector.h"

void write_load_vector_instruction(const unsigned char* instruction, FILE* file) {
    
    unsigned char opcode = get_loadstore_vector_opcode(instruction);
    switch (opcode) {
        case 0: fputs("lbv ", file); break;
        case 1: fputs("lsv ", file); break;
        case 2: fputs("llv ", file); break;
        case 3: fputs("ldv ", file); break;
        case 4: fputs("lqv ", file); break;
        case 5: fputs("lrv ", file); break;
        case 6: fputs("lpv ", file); break;
        case 7: fputs("luv ", file); break;
        case 8: fputs("lhv ", file); break;
        case 9: fputs("lfv ", file); break;
        case 11: fputs("ltv ", file); break;
        default:
            printf("Unsupported load vector opcode: %x\n", opcode);
            fputs("[unknown]", file);
            break;
    }

    write_loadstore_vector_instruction_rest(instruction, file);
}

void write_store_vector_instruction(const unsigned char* instruction, FILE* file) {
    
    unsigned char opcode = get_loadstore_vector_opcode(instruction);
    switch (opcode) {
        case 0: fputs("sbv ", file); break;
        case 1: fputs("ssv ", file); break;
        case 2: fputs("slv ", file); break;
        case 3: fputs("sdv ", file); break;
        case 4: fputs("sqv ", file); break;
        case 5: fputs("srv ", file); break;
        case 6: fputs("spv ", file); break;
        case 7: fputs("suv ", file); break;
        case 8: fputs("shv ", file); break;
        case 9: fputs("sfv ", file); break;
        case 11: fputs("stv ", file); break;
        default:
            printf("Unsupported load vector opcode: %x\n", opcode);
            fputs("[unknown]", file);
            break;
    }

    write_loadstore_vector_instruction_rest(instruction, file);
}

void write_loadstore_vector_instruction_rest(const unsigned char* instruction, FILE* file) {
    unsigned int vt = get_loadstore_vector_vt(instruction);
    fprintf(file, "v%d", vt);
    fprintf(file, "[e%d]", get_loadstore_vector_element(instruction));
    fputs(", ", file);
    fprintf(file, "%d", get_loadstore_vector_offset(instruction));
    fprintf(file, "(%d)", get_loadstore_vector_base(instruction));
}

void write_vector_operation_instruction(const unsigned char* instruction, FILE* file) {
    
    unsigned char opcode = get_vector_operation_opcode(instruction);
    switch (opcode) {
        case 0b010011: fputs("vabs ", file); break;
        case 0b010000: fputs("vadd ", file); break;
        case 0b010100: fputs("vaddc ", file); break;
        case 0b101000: fputs("vand ", file); break;
        case 0b100101: fputs("vch ", file); break;
        case 0b100100: fputs("vcl ", file); break;
        case 0b100110: fputs("vcr ", file); break;
        case 0b100001: fputs("veq ", file); break;
        case 0b100011: fputs("vge ", file); break;
        case 0b100000: fputs("vlt ", file); break;
        case 0b001000: fputs("vmacf ", file); break;
        case 0b001011: fputs("vmacq ", file); break;
        case 0b001001: fputs("vmacu ", file); break;
        case 0b001111: fputs("vmadh ", file); break;
        case 0b001100: fputs("vmadl ", file); break;
        case 0b001101: fputs("vmadm ", file); break;
        case 0b001110: fputs("vmadn ", file); break;
        case 0b110011: fputs("vmov ", file); break;
        case 0b100111: fputs("vmrg ", file); break;
        case 0b000111: fputs("vmudh ", file); break;
        case 0b000100: fputs("vmudl ", file); break;
        case 0b000101: fputs("vmudm ", file); break;
        case 0b000110: fputs("vmudn ", file); break;
        case 0b000000: fputs("vmulf ", file); break;
        case 0b000011: fputs("vmulq ", file); break;
        case 0b000001: fputs("vmulu ", file); break;
        case 0b101001: fputs("vnand ", file); break;
        case 0b100010: fputs("vne ", file); break;
        case 0b110111: fputs("vnop ", file); break;
        case 0b101011: fputs("vnor ", file); break;
        case 0b101101: fputs("vnxor ", file); break;
        case 0b101010: fputs("vor ", file); break;
        case 0b110000: fputs("vrcp ", file); break;
        case 0b110010: fputs("vrcph ", file); break;
        case 0b110001: fputs("vrcpl ", file); break;
        case 0b001010: fputs("vrndn ", file); break;
        case 0b000010: fputs("vrndp ", file); break;
        case 0b110100: fputs("vrsq ", file); break;
        case 0b110110: fputs("vrsqh ", file); break;
        case 0b110101: fputs("vrsql ", file); break;
        case 0b011101: fputs("vsar ", file); break;
        case 0b010001: fputs("vsub ", file); break;
        case 0b010101: fputs("vsubc ", file); break;
        case 0b101100: fputs("vxor ", file); break;
        default:
            printf("Unsupported vector operation opcode: %x\n", opcode);
            fputs("[unknown]", file);
            break;
    }
}

unsigned char get_loadstore_vector_vt(const unsigned char* instruction) {
    return instruction[1] & 0b11111;
}

unsigned char get_loadstore_vector_element(const unsigned char* instruction) {
    unsigned char element2 = instruction[2] & 0b111;
    unsigned char element3 = instruction[3] & 0b10000000;

    element2 = element2 << 7;
    element3 = element3 >> 7;

    return element2 | element3;
}

unsigned char get_loadstore_vector_offset(const unsigned char* instruction) {
    return instruction[3] & 0b1111111;
}

unsigned char get_loadstore_vector_base(const unsigned char* instruction) {   
    unsigned char base0 = instruction[0] & 0b11; // byte AND 00000011
    unsigned char base1 = instruction[1] & 0b11100000;

    base0 = base0 << 5;
    base1 = base1 >> 5;

    return base0 | base1;
}

unsigned char get_vector_operation_opcode(const unsigned char* instruction) {
    unsigned char opcode = instruction[3] & 0b111111;

    return opcode;
}

unsigned char get_loadstore_vector_opcode(const unsigned char* instruction) {
    unsigned char opcode = instruction[2] & 0b11111000;
    opcode = opcode >> 3;

    return opcode;
}