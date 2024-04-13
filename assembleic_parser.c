#include "assembleic.h"

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
