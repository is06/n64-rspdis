#ifndef RSPDIS_VECTOR_H
#define RSPDIS_VECTOR_H

void write_load_vector_instruction(const unsigned char* instruction, FILE* file);
void write_store_vector_instruction(const unsigned char* instruction, FILE* file);

void write_loadstore_vector_instruction_rest(const unsigned char* instruction, FILE* file);
void write_vector_operation_instruction(const unsigned char* instruction, FILE* file);

void write_vector_logical_instruction(const unsigned char* instruction, FILE* file);

unsigned char get_loadstore_vector_opcode(const unsigned char* instruction);
unsigned char get_loadstore_vector_vt(const unsigned char* instruction);
unsigned char get_loadstore_vector_element(const unsigned char* instruction);
unsigned char get_loadstore_vector_offset(const unsigned char* instruction);
unsigned char get_loadstore_vector_base(const unsigned char* instruction);

unsigned char get_vector_operation_opcode(const unsigned char* instruction);
unsigned char get_vector_logical_element(const unsigned char* instruction);
unsigned char get_vector_logical_vs(const unsigned char* instruction);
unsigned char get_vector_logical_vd(const unsigned char* instruction);

#endif
