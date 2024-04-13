#include "assembleic.h"



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
	  FILE* input;
	  input = fopen(argv[2], "r");
	  enum assemblei_instruction inst[512];
	  size_t len;
	  assembleic_parser(input,inst,&len, 0);
	  FILE* file = fopen("generated.asm", "w");
	  assembleic_codegen_x86_64_linux(file,inst,len);
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
