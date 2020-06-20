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
    unsigned char vt = get_loadstore_vector_vt(instruction);
    unsigned char element = get_loadstore_vector_element(instruction);
    unsigned char offset = get_loadstore_vector_offset(instruction);
    unsigned char base = get_loadstore_vector_base(instruction);

    fprintf(file, "v%d[e%d], %d(%d)", vt, element, offset, base);
}

void write_vector_operation_instruction(const unsigned char* instruction, FILE* file) {
    
    unsigned char opcode = get_vector_operation_opcode(instruction);
    switch (opcode) {
        case 0b010011: fputs("vabs ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b010000: fputs("vadd ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b010100: fputs("vaddc ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b101000: fputs("vand ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b100101: fputs("vch ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b100100: fputs("vcl ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b100110: fputs("vcr ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b100001: fputs("veq ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b100011: fputs("vge ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b100000: fputs("vlt ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b001000: fputs("vmacf ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b001011: fputs("vmacq ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b001001: fputs("vmacu ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b001111: fputs("vmadh ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b001100: fputs("vmadl ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b001101: fputs("vmadm ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b001110: fputs("vmadn ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b110011: fputs("vmov ", file); write_vector_move_instruction(instruction, file); break;
        case 0b100111: fputs("vmrg ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b000111: fputs("vmudh ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b000100: fputs("vmudl ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b000101: fputs("vmudm ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b000110: fputs("vmudn ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b000000: fputs("vmulf ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b000011: fputs("vmulq ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b000001: fputs("vmulu ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b101001: fputs("vnand ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b100010: fputs("vne ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b110111: fputs("vnop", file); break;
        case 0b101011: fputs("vnor ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b101101: fputs("vnxor ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b101010: fputs("vor ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b110000: fputs("vrcp ", file); write_vector_move_instruction(instruction, file); break;
        case 0b110010: fputs("vrcph ", file); write_vector_move_instruction(instruction, file); break;
        case 0b110001: fputs("vrcpl ", file); write_vector_move_instruction(instruction, file); break;
        case 0b001010: fputs("vrndn ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b000010: fputs("vrndp ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b110100: fputs("vrsq ", file); write_vector_move_instruction(instruction, file); break;
        case 0b110110: fputs("vrsqh ", file); write_vector_move_instruction(instruction, file); break;
        case 0b110101: fputs("vrsql ", file); write_vector_move_instruction(instruction, file); break;
        case 0b011101: fputs("vsar ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b010001: fputs("vsub ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b010101: fputs("vsubc ", file); write_vector_logical_instruction(instruction, file); break;
        case 0b101100: fputs("vxor ", file); write_vector_logical_instruction(instruction, file); break;
        default:
            printf("Unsupported vector operation opcode: %x\n", opcode);
            fputs("[unknown]", file);
            break;
    }
}

void write_vector_logical_instruction(const unsigned char* instruction, FILE* file) {
    unsigned char vd = get_vector_logical_vd(instruction);
    unsigned char vs = get_vector_logical_vs(instruction);
    unsigned char vt = get_loadstore_vector_vt(instruction);
    unsigned char element = get_vector_logical_element(instruction);

    if (element == 0) {
        fprintf(file, "v%d, v%d, v%d", vd, vs, vt);
        return;
    }

    fprintf(file, "v%d, v%d, v%d[e%d]", vd, vs, vt, element);    
}

void write_vector_move_instruction(const unsigned char* instruction, FILE* file) {
    unsigned char e = get_vector_logical_element(instruction);
    unsigned char vt = get_loadstore_vector_vt(instruction);
    unsigned char de = get_vector_logical_vs(instruction);
    unsigned char vd = get_vector_logical_vd(instruction);

    fprintf(file, "v%d[e%d], v%d[e%d]", vd, de, vt, e);
}

unsigned char get_loadstore_vector_vt(const unsigned char* instruction) {
    return instruction[1] & 0b00011111;
}

unsigned char get_loadstore_vector_element(const unsigned char* instruction) {
    unsigned char element2 = instruction[2] & 0b00000111;
    unsigned char element3 = instruction[3] & 0b10000000;

    element2 = element2 << 1;
    element3 = element3 >> 7;

    return element2 | element3;
}

unsigned char get_loadstore_vector_offset(const unsigned char* instruction) {
    return instruction[3] & 0b01111111;
}

unsigned char get_loadstore_vector_base(const unsigned char* instruction) {   
    unsigned char base0 = instruction[0] & 0b00000011;
    unsigned char base1 = instruction[1] & 0b11100000;

    base0 = base0 << 3;
    base1 = base1 >> 5;

    return base0 | base1;
}

unsigned char get_vector_operation_opcode(const unsigned char* instruction) {
    unsigned char opcode = instruction[3] & 0b00111111;

    return opcode;
}

unsigned char get_loadstore_vector_opcode(const unsigned char* instruction) {
    unsigned char opcode = instruction[2] & 0b11111000;
    opcode = opcode >> 3;

    return opcode;
}

unsigned char get_vector_logical_element(const unsigned char* instruction) {
    unsigned char element0 = instruction[0] & 0b00000001;
    unsigned char element1 = instruction[1] & 0b11100000;

    element0 = element0 << 3;
    element1 = element1 >> 5;

    return element0 | element1;
}

unsigned char get_vector_logical_vs(const unsigned char* instruction) {
    unsigned char vs = instruction[2] & 0b11111000;
    return vs >> 3;
}

unsigned char get_vector_logical_vd(const unsigned char* instruction) {
    unsigned char vd2 = instruction[2] & 0b00000111;
    unsigned char vd3 = instruction[3] & 0b11000000;

    vd2 = vd2 << 2;
    vd3 = vd3 >> 6;

    return vd2 | vd3;
}
