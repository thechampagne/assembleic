#include "bascii.h"

void bascii_codegen_x86_64_linux_header(FILE* file)
{
  fprintf(file, "format ELF64 executable 3\n");
  fprintf(file, "segment executable readable\n");
  fprintf(file, "entry $\n");
  fprintf(file, "push 00000000b\n");
  fprintf(file, "mov rax, 1\n");
  fprintf(file, "mov rdi, 1\n");
  fprintf(file, "mov rsi, rsp\n");
  fprintf(file, "mov rdx, 1\n");
}

void bascii_codegen_x86_64_linux_footer(FILE* file)
{
  fprintf(file, "mov rax, 60\n");
  fprintf(file, "mov rdi, 0\n");
  fprintf(file, "syscall");
}

void bascii_codegen_x86_64_linux(FILE* file, const enum bascii_instruction* inst, size_t inst_len)
{
  bascii_codegen_x86_64_linux_header(file);
  int cp = 0;
  char cells[8] = {0};
  char all_zero = 1;
  size_t i;
  for(i = 0; i < inst_len; i++)
    {
      switch(inst[i])
	{
	case BASCII_INST_MOVES_FORWARD:
	  cp++;
	  break;
	case BASCII_INST_MOVES_BACKWARD:
	  cp--;
	  break;
	case BASCII_INST_PRINT_ALL:
	  fprintf(file, "mov byte [rsp], %d%d%d%d%d%d%d%db\n", cells[7],
		  cells[6],
		  cells[5],
		  cells[4],
		  cells[3],
		  cells[2],
		  cells[1],
		  cells[0]);
	  fprintf(file, "syscall\n");
	  break;
	case BASCII_INST_PRINT_CELL:
	  /* fprintf(file, "push %d\n", cp + 31);
	     fprintf(file, "syscall\n");
	     fprintf(file, "add rsp, 8\n"); */
	  break;
	case BASCII_INST_INCREMENT:
	  cells[cp]++;
	  break;
	case BASCII_INST_DECREMENT:
	  cells[cp]--;
	  break;
	case BASCII_INST_CLEAR_ALL:
	  size_t j;
	  for(j = 0; j < 8; j++) cells[j] = 0;
	  fprintf(file, "mov byte [rsp], 00000000b\n");
	  break;
			
	}
    }
  bascii_codegen_x86_64_linux_footer(file);
}
