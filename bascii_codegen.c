#include "assembleic.h"

void assembleic_codegen_x86_64_linux_header(FILE* file)
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

void assembleic_codegen_x86_64_linux_footer(FILE* file)
{
  fprintf(file, "mov rax, 60\n");
  fprintf(file, "mov rdi, 0\n");
  fprintf(file, "syscall");
}

void assembleic_codegen_x86_64_linux(FILE* file, const enum assemblei_instruction* inst, size_t inst_len)
{
  assembleic_codegen_x86_64_linux_header(file);
  size_t cp = 0;
  char cells[8] = {0};
  int i;
  for(i = 0; i < inst_len; i++)
    {
      switch(inst[i])
	{
	case ASSEMBLEI_INST_MOVES_FORWARD:
	  cp++;
	  break;
	case ASSEMBLEI_INST_MOVES_BACKWARD:
	  cp--;
	  break;
	case ASSEMBLEI_INST_PRINT_ALL:
	  fprintf(file, "mov byte [rsp], %d%d%d%d%d%d%d%db\n", cells[0], cells[1], cells[2], cells[3], cells[4], cells[5], cells[6], cells[7]);
	  fprintf(file, "syscall\n");
	  break;
	case ASSEMBLEI_INST_PRINT_CELL:
	  /* TODO */
	  break;
	case ASSEMBLEI_INST_INCREMENT:
	  cells[cp]++;
	  break;
	case ASSEMBLEI_INST_CLEAR_ALL:
	  int j;
	  for(j = 0; j < 8; j++) cells[j] = 0;
	  fprintf(file, "mov byte [rsp], 00000000b\n");
	  break;
			
	}
    }
  assembleic_codegen_x86_64_linux_footer(file);
}
