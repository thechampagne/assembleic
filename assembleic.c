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

void parser(enum assemblei_code* codes, int* o, const char* code)
{
  
  int i = 0;
  int cell = 0;
  char cells[8] = {0};
  while (*code)
    {
      printf("%c", *code);
      switch(*code)
	{
	case '!':
	  cell++;
	  if (cell > 7)
	    {
	      fprintf(stderr, "Error: there are only 8 cells");
	      exit(1);
	    }
	  codes[i] = assemblei_code_moves_forward;
	  i++;
	  break;
	case '?':
	  cell--;
	  if (cell < 0)
	    {
	      fprintf(stderr, "Error:");
	      exit(1);
	    }
	  codes[i] = assemblei_code_moves_backward;
	  i++;
	  break;
	case '#':
	  codes[i] = assemblei_code_print_all;
	  i++;
	  break;
	case '.':
	  codes[i] = assemblei_code_print_cell;
	  i++;
	  break;
	case '+':
	  cells[cell]++;
	  if (cells[cell] > 1)
	    {
	      fprintf(stderr, "Error: cell already incremented");
	      exit(1);	
	    }
	  codes[i] = assemblei_code_increment;
	  i++;
	  break;
	case ',':
	  int j;
	  for(j = 0; j < 8; j++) cells[j] = 0;
	  codes[i] = assemblei_code_clear_all;
	  i++;
	  break;
			
	}
      code++;
    }
  *o = i;
}

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

void usage(FILE* file)
{
  fprintf(file,
	  "Usage: assembleic [command]\n" \
	  "Command:\n" \
	  "  help                Display this information.\n" \
	  "  com <file>          Compile the program.\n" \
	  );
  
}



int main(int argc, const char* const* argv)
{
  if (argc > 1)
    {
      if (strcmp(argv[1], "help") == 0)
	{
	  usage(stdout);
	  return 0;
	}
      else if (strcmp(argv[1], "com") == 0)
	{
	  if (argc <= 2)
	    {
	      fprintf(stderr, "Error: expected file path\n");
	      exit(1);
	    }
	  /*FILE* input;
	    input = fopen(argv[2], "r");*/
	  
	  return 0;
	}
      else
	{
	  usage(stderr);
	  fprintf(stderr, "\nError: expected command argument\n");
	  exit(1);
	}
      
    }
  else
    {
      usage(stderr);
      fprintf(stderr, "\nError: expected command argument\n");
      exit(1);
    }
  
	/* const char* code = "!+!!!!!!+#"; */
	/* enum assemblei_code codes[512]; */
	/* int i; */
	/* parser(codes, &i, code); */
	/* FILE* file = fopen("generated.asm", "w"); */
	/* codegen_x86_64_linux(file,codes, i); */
	/* return 0; */
}
