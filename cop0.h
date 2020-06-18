#ifndef COP0_H
#define COP0_H

#include <stdio.h>

void write_cop0_instruction(const unsigned char* instruction, FILE* file);
void write_cop0_instruction_rest(const unsigned char* instruction, FILE* file);
unsigned char get_cop0_opcode(const unsigned char* instruction);
unsigned char get_cop0_rt(const unsigned char* instruction);
unsigned char get_cop0_rd(const unsigned char* instruction);

#endif
