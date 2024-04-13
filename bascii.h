#ifndef __BASCII_H__
#define __BASCII_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum assemblei_instruction {
	ASSEMBLEI_INST_MOVES_FORWARD,
	ASSEMBLEI_INST_MOVES_BACKWARD,
	ASSEMBLEI_INST_PRINT_ALL,
	ASSEMBLEI_INST_PRINT_CELL,
	ASSEMBLEI_INST_INCREMENT,
	ASSEMBLEI_INST_CLEAR_ALL,
};

void assembleic_parser(FILE* file, enum assemblei_instruction* inst, size_t* inst_out_len, size_t inst_cap);

void assembleic_codegen_x86_64_linux_header(FILE* file);

void assembleic_codegen_x86_64_linux_footer(FILE* file);

void assembleic_codegen_x86_64_linux(FILE* file, const enum assemblei_instruction* inst, size_t inst_len);

#endif /* __BASCII_H__ */
