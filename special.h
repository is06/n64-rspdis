#ifndef RSPDIS_SPECIAL_H
#define RSPDIS_SPECIAL_H

#include <stdio.h>

void write_special_instruction(const unsigned char* instruction, FILE* file);

unsigned char get_special_opcode(const unsigned char* instruction);

#endif
