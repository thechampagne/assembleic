#ifndef __ASSEMBLEIC_H__
#define __ASSEMBLEIC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum assemblei_code {
	assemblei_code_moves_forward,
	assemblei_code_moves_backward,
	assemblei_code_print_all,
	assemblei_code_print_cell,
	assemblei_code_increment,
	assemblei_code_clear_all,
};

void parser(enum assemblei_code* codes, int* o, const char* code);

void codegen_x86_64_linux_header(FILE* file);

void codegen_x86_64_linux_footer(FILE* file);

void codegen_x86_64_linux(FILE* file, const enum assemblei_code* ins, size_t ins_len);

#endif /* __ASSEMBLEIC_H__ */
