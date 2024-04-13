#include "bascii.h"

void assembleic_parser(FILE* file, enum assemblei_instruction* inst, size_t* inst_out_len, size_t inst_cap)
{
  
  size_t inst_len = 0;
  int cp = 0;
  char cells[8] = {0};
  int ch;
  while ((ch = getc(file)) != EOF)
    {
      switch(ch)
	{
	case '!':
	  cp++;
	  if (cp > 7)
	    {
	      fprintf(stderr, "Error: cell out of range\n");
	      exit(1);
	    }
	  inst[inst_len] = ASSEMBLEI_INST_MOVES_FORWARD;
	  inst_len++;
	  break;
	case '?':
	  cp--;
	  if (cp < 0)
	    {
	      fprintf(stderr, "Error: cell out of range\n");
	      exit(1);
	    }
	  inst[inst_len] = ASSEMBLEI_INST_MOVES_BACKWARD;
	  inst_len++;
	  break;
	case '#':
	  inst[inst_len] = ASSEMBLEI_INST_PRINT_ALL;
	  inst_len++;
	  break;
	case '.':
	  inst[inst_len] = ASSEMBLEI_INST_PRINT_CELL;
	  inst_len++;
	  break;
	case '+':
	  cells[cp]++;
	  if (cells[cp] > 1)
	    {
	      fprintf(stderr, "Error: cell already incremented");
	      exit(1);	
	    }
	  inst[inst_len] = ASSEMBLEI_INST_INCREMENT;
	  inst_len++;
	  break;
	case ',':
	  int j;
	  for(j = 0; j < 8; j++) cells[j] = 0;
	  inst[inst_len] = ASSEMBLEI_INST_CLEAR_ALL;
	  inst_len++;
	  break;
			
	}
    }
  *inst_out_len = inst_len;
}
