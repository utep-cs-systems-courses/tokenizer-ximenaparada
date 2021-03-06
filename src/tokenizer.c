#include "tokenizer.h"
#include "history.h"
#include <stdlib.h>
#include <stdio.h>

/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').  
   Zero terminators are not printable (therefore false) */
int space_char(char c)
{
  if((c=='\t' || c==' ') && c != '\0'){
    return 1;
  }
  return 0;
}

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
   Zero terminators are not printable (therefore false) */ 
int non_space_char(char c)
{
  if(c=='\t' || c==' ' || c=='\0'){ // checking if space, tab or end of line
    return 0;
  }
  return 1;
}

/* Returns a pointer to the first character of the next 
   space-separated word in zero-terminated str.  Return a zero pointer if 
   str does not contain any words. */
char *word_start(char *str)
{
  int i = 0;
  while(*(str + i)){ // pa + i is the adress of a[i], *(pa+i) is contents of a[i] -> pg 82
      if (non_space_char(*(str + i))){
	return str + i;
      }
      i++;
    }
    return str + i; // returning address of str[i]
}

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word)
{
  int i = 0;
  while(non_space_char(*(word+i)))
    {
      if(space_char(*(word+i)))
	return word+i;
      else
	i++;
    }
  return word+i;
}

/* Counts the number of words in the string argument. */
int count_words(char *str)
{
  int i = 0;
  int count = 0;
  char *tmp = str; //copy of pointer
  tmp = word_start(tmp);
  while(*tmp){
    if(non_space_char(*tmp)){ // checking it IS a word
      count++;
    }
    tmp = word_terminator(tmp); // end of word; count only once
    tmp = word_start(tmp); // getting next word
  }
  printf("%d",count);
  return count; // end return word count
}

/* Returns a freshly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len)
{
  char* copy = malloc((len+1) * sizeof(char));
  int plc = 0;
  while(plc<len){
    //printf("[%d]: %c",i,inStr[i],"\n");
    copy[plc] = inStr[plc];
    plc++;
    //printf("[%d]:  %c",i,copy[i],"\n");
  }
  copy[plc] = '\0';
  return copy;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0
*/
char **tokenize(char* str){
   int numWords = count_words(str);
   char **tokens = malloc((numWords+1) * sizeof(char *));
   int i;
   int len;
   char *ptr = str;
   for(i=0; i < numWords; i++){
     ptr = word_start(ptr);
     len = word_length(ptr);
     tokens[i] = copy_str(ptr, len);
     ptr = word_terminator(ptr);
   }
   tokens[i] = '\0';
   return tokens;
}

/* Prints all tokens. */
  void print_tokens(char **tokens){
    int i = 0;
    while(tokens[i]){
      printf("\t\ttoken [%d] = %s\n", i, tokens[i]);
      i++;
    }
  }

/* Frees all tokens and the vector containing themx. */
  void free_tokens(char **tokens){
    int i = 0;
    while(tokens[i]){
      free(tokens[i]);
      i++;
    }
    free(tokens);
  }

  /* Helper - get word length */
  int word_length(char *str){
    char *start = word_start(str);
    char *end = word_terminator(str);
    int len = 0;
    len = end - start;
    // printf("size = %d", len);
    return len;
  }
