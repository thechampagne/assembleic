#ifndef __BASCII_H__
#define __BASCII_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum bascii_instruction {
	BASCII_INST_MOVES_FORWARD,
	BASCII_INST_MOVES_BACKWARD,
	BASCII_INST_PRINT_ALL,
	BASCII_INST_PRINT_CELL,
	BASCII_INST_INCREMENT,
	BASCII_INST_CLEAR_ALL,
};

void bascii_parser(FILE* file, enum bascii_instruction* inst, size_t* inst_out_len, size_t inst_cap);

void bascii_codegen_x86_64_linux_header(FILE* file);

void bascii_codegen_x86_64_linux_footer(FILE* file);

void bascii_codegen_x86_64_linux(FILE* file, const enum bascii_instruction* inst, size_t inst_len);

#endif /* __BASCII_H__ */
