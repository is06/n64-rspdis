#ifndef RSPDIS_H
#define RSPDIS_H

#include <stdio.h>
#include "base.h"
#include "cop0.h"
#include "regimm.h"
#include "special.h"
#include "vector.h"

void write_instruction(const unsigned char* instruction, FILE* file);
unsigned char get_instruction_identifier(const unsigned char* instruction);
long get_file_size(FILE* file);

#endif
