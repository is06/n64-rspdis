#ifndef RSPDIS_SPECIAL_H
#define RSPDIS_SPECIAL_H

#include <stdio.h>

void write_special_instruction(const unsigned char* instruction, FILE* file);
static void write_special_nop_or_sll(const unsigned char* instruction, FILE* file);
static void write_special_instruction_rest(const unsigned char* instruction, FILE* file);
static void write_special_jump(const unsigned char* instruction, FILE* file);
static void write_special_shift(const unsigned char* instruction, FILE* file);
static unsigned char get_special_opcode(const unsigned char* instruction);
static unsigned char get_special_rs(const unsigned char* instruction);
static unsigned char get_special_rt(const unsigned char* instruction);
static unsigned char get_special_rd(const unsigned char* instruction);
static unsigned char get_special_sa(const unsigned char* instruction);

#endif
