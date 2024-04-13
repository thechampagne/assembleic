#include "assembleic.h"

void codegen_x86_64_linux_header(FILE* file)
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

void codegen_x86_64_linux_footer(FILE* file)
{
  fprintf(file, "mov rax, 60\n");
  fprintf(file, "mov rdi, 0\n");
  fprintf(file, "syscall");
}

void codegen_x86_64_linux(FILE* file, const enum assemblei_code* ins, size_t ins_len)
{
  codegen_x86_64_linux_header(file);
  size_t ip = 0;
  char cells[8] = {0};
  int i;
  for(i = 0; i < ins_len; i++)
    {
      switch(ins[i])
	{
	case assemblei_code_moves_forward:
	  ip++;
	  break;
	case assemblei_code_moves_backward:
	  ip--;
	  break;
	case assemblei_code_print_all:
	  fprintf(file, "mov byte [rsp], %d%d%d%d%d%d%d%db\n", cells[0], cells[1], cells[2], cells[3], cells[4], cells[5], cells[6], cells[7]);
	  fprintf(file, "syscall\n");
	  break;
	case assemblei_code_print_cell:
	  /* TODO */
	  break;
	case assemblei_code_increment:
	  cells[ip]++;
	  break;
	case assemblei_code_clear_all:
	  int j;
	  for(j = 0; j < 8; j++) cells[j] = 0;
	  fprintf(file, "mov byte [rsp], 00000000b\n");
	  break;
			
	}
    }
  codegen_x86_64_linux_footer(file);
}
