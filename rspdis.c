#include <stdio.h>
#include "rspdis.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: rspdis file\n");
        return 1;
    }

    FILE* source = fopen(argv[1], "rb");
    if (source == NULL) {
        printf("Unable to open file %s\n", argv[1]);
        return 1;
    }

    FILE* destination = fopen("code.asm", "w+");

    long file_size = get_file_size(source);
    while (ftell(source) < file_size) {
        unsigned char instruction[4];
        fread(instruction, 4, 1, source);
        write_instruction(instruction, destination);
    }    

    fclose(source);
    fclose(destination);

    return 0;
}

void write_instruction(const unsigned char* instruction, FILE* file) {
    unsigned char instruction_identifier = get_instruction_identifier(instruction);
    
    switch (instruction_identifier) {        
        case 0b001000: fputs("addi ", file); write_base_instruction_immediate(instruction, file); break;
        case 0b001001: fputs("addiu ", file); write_base_instruction_immediate(instruction, file); break;
        case 0b001100: fputs("andi ", file); write_base_instruction_immediate(instruction, file); break;
        case 0b000100: fputs("beq ", file); write_base_instruction_branch(instruction, file); break;
        case 0b000111: fputs("bgtz ", file); write_base_instruction_branch_zero(instruction, file); break;
        case 0b000110: fputs("blez ", file); write_base_instruction_branch_zero(instruction, file); break;
        case 0b000101: fputs("bne ", file); write_base_instruction_branch(instruction, file); break;
        case 0b000010: fputs("j ", file); write_base_instruction_jump(instruction, file); break;
        case 0b000011: fputs("jal ", file); write_base_instruction_jump(instruction, file); break;
        case 0b100000: fputs("lb ", file); write_base_instruction_loadstore(instruction, file); break;
        case 0b100100: fputs("lbu ", file); write_base_instruction_loadstore(instruction, file); break;
        case 0b100001: fputs("lh ", file); write_base_instruction_loadstore(instruction, file); break;
        case 0b100101: fputs("lhu ", file); write_base_instruction_loadstore(instruction, file); break;
        case 0b001111: fputs("lui ", file); write_base_instruction_immediate(instruction, file); break;
        case 0b100011: fputs("lw ", file); write_base_instruction_loadstore(instruction, file); break;
        case 0b001101: fputs("ori ", file); write_base_instruction_immediate(instruction, file); break;
        case 0b101000: fputs("sb ", file); write_base_instruction_loadstore(instruction, file); break;
        case 0b101001: fputs("sh ", file); write_base_instruction_loadstore(instruction, file); break;
        case 0b001010: fputs("slti ", file); write_base_instruction_immediate(instruction, file); break;
        case 0b001011: fputs("sltiu ", file); write_base_instruction_immediate(instruction, file); break;
        case 0b101011: fputs("sw ", file); write_base_instruction_loadstore(instruction, file); break;
        case 0b001110: fputs("xori ", file); write_base_instruction_immediate(instruction, file); break;

        case 0b000000: write_special_instruction(instruction, file); break;
        case 0b000001: write_regimm_instruction(instruction, file); break;
        case 0b010000: write_cop0_instruction(instruction, file); break;

        case 0b010010:  // COP2 (vector operations)
            write_vector_operation_instruction(instruction, file);
            break;
        case 0b110010:  // LWC2 (vector loads)
            write_load_vector_instruction(instruction, file);
            break;
        case 0b111010:  // SWC2 (vector stores)
            write_store_vector_instruction(instruction, file);
            break;

        default:
            printf("Unsupported instruction identifier: %x\n", instruction_identifier);
            fputs("[unknown]", file);
            break;
    }
    fputs("\n", file);
}

unsigned char get_instruction_identifier(const unsigned char* instruction) {
    unsigned char identifier = instruction[0] & 0b11111100;
    identifier = identifier >> 2;
    
    return identifier;
}

long get_file_size(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return size;
}
