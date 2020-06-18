#ifndef RSPDIS_BASE_H
#define RSPDIS_BASE_H

#include <stdio.h>

void write_base_instruction_immediate(const unsigned char* instruction, FILE* file);
void write_base_instruction_branch(const unsigned char* instruction, FILE* file);
void write_base_instruction_jump(const unsigned char* instruction, FILE* file);
void write_base_instruction_load(const unsigned char* instruction, FILE* file);

unsigned char get_base_r0(const unsigned char* instruction);
unsigned char get_base_r1(const unsigned char* instruction);
unsigned short get_base_immediate(const unsigned char* instruction);
unsigned int get_base_jump_address(const unsigned char* instruction);

#endif
