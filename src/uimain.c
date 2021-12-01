#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"
#include "history.h"

int main()
{
  List *history = init_history();
  int hist_num;
  char input[100];
  
  printf("Welcome to Tokenizer!");
  
  while (1) {
    printf("\tInput a string to tokenize it\n\t!<num> to print history at specific point\n\t!h for full history\n\t!q to quit\n");

    putchar('$');
    fgets(input, 100, stdin);
    
    if(input[0] == '!'){
      if(input[1] == 'q'){
	break;
      }
      else if(input[1] == 'h'){
	printf("\n------history------\n");
	print_history(history);
      }
      else {
	hist_num = atoi(input+1);
	printf("\t[%d] %s\n", hist_num, get_history(history, hist_num));
      }
    }
    
    else {
      
      char **tokens = tokenize(input);
      add_history(history, input);
      print_tokens(tokens);
      free_tokens(tokens);
    }
  }
  free_history(history);
  return 0;
}

