#ifndef RSPDIS_REGIMM_H
#define RSPDIS_REGIMM_H

#include <stdio.h>

void write_regimm_instruction(const unsigned char* instruction, FILE* file);

unsigned char get_regimm_opcode(const unsigned char* instruction);

#endif
