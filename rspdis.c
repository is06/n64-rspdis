#include <stdio.h>

unsigned char get_instruction_identifier(const unsigned char* instruction);
unsigned char get_loadstore_vector_opcode(const unsigned char* instruction);
unsigned char get_loadstore_vector_base(const unsigned char* instruction);
unsigned int get_loadstore_vector_vt(const unsigned char* instruction);
unsigned int get_loadstore_vector_element(const unsigned char* instruction);
unsigned int get_loadstore_vector_offset(const unsigned char* instruction);

void write_load_vector_instruction(const unsigned char* instruction, FILE* file);
void write_store_vector_instruction(const unsigned char* instruction, FILE* file);
void write_loadstore_vector_instruction_rest(const unsigned char* instruction, FILE* file);

int main() {

    FILE* source = fopen("source.bin", "rb");
    if (source == NULL) {
        printf("Unable to open source file");
        return 1;
    }

    FILE* destination = fopen("code.asm", "w+");

    unsigned char instruction[4];

    fread(instruction, 4, 1, source);

    unsigned char instruction_identifier = get_instruction_identifier(instruction);

    switch (instruction_identifier) {
        case 18:    // COP2 (vector operations)
            fputs("vabs\n", destination);
            break;
        case 40:    // SB
            break;
        case 50:    // LWC2 (vector loads)
            write_load_vector_instruction(instruction, destination);
            break;
        case 58:    // SWC2 (vector stores)
            write_store_vector_instruction(instruction, destination);
            break;
        default:
            printf("Unsupported instruction identifier: %x\n", instruction_identifier);
    }

    fclose(source);
    fclose(destination);

    return 0;
}

unsigned char get_instruction_identifier(const unsigned char* instruction) {
    unsigned char identifier = instruction[0] & 0b11111100;
    identifier = identifier >> 2;
    
    return identifier;
}

unsigned char get_loadstore_vector_opcode(const unsigned char* instruction) {
    unsigned char opcode = instruction[2] & 0b11111000;
    opcode = opcode >> 3;

    return opcode;
}

unsigned char get_loadstore_vector_base(const unsigned char* instruction) {
    
//     31   26 25    16   15    8  7     0
//    |   0   ||   1   | |   2   ||   3   |
//    110010 11000 11111 00011 0101 1001101
    
    unsigned char base0 = instruction[0] & 0b11; // byte AND 00000011
    unsigned char base1 = instruction[1] & 0b11100000;

    base0 = base0 << 5;
    base1 = base1 >> 5;

    unsigned char base = base0 & base1;

    return base;
}

unsigned int get_loadstore_vector_vt(const unsigned char* instruction) {
    return instruction[1] & 0b11111;
}

unsigned int get_loadstore_vector_element(const unsigned char* instruction) {
    unsigned char element2 = instruction[2] & 0b111;
    unsigned char element3 = instruction[3] & 0b10000000;

    element2 = element2 << 7;
    element3 = element3 >> 7;

    unsigned char element = element2 & element3;

    return element;
}

unsigned int get_loadstore_vector_offset(const unsigned char* instruction) {
    return instruction[3] & 0b1111111;
}

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

    fputs("\n", file);
}
