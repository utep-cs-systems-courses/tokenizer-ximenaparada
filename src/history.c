#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"

/* Initialize the linked list to keep the history. */
List* init_history() {
  List *history = (List*)malloc(sizeof(List*));
  history -> root = NULL;
  return history;
}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store
*/
void add_history(List *list, char *str){
  int curr = 1;
  Item *currNode = list -> root;
  char *start, *end;
  start = word_start(str);
  end = word_terminator(start);

  // looping until it reaches next null...
  while(currNode){
    currNode = currNode -> next;
    curr++;
  }
  Item *temp = malloc(sizeof(Item));
  temp -> id = curr;
  temp -> str = str;
  temp -> next = NULL;
  currNode -> next = temp;
}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id){
  Item *node = list->root->next;
  if(!list){
    return '\0';
  }

  while(node){
    if(node == NULL) {
      printf("Not valid");
      return '\0';
    }
    else if(id == 1) {
      return node->str;
    }
    else {
      id--;
      node = node->next;
    } 
  }
  return '\0';
}

/*Print the entire contents of the list. */
void print_history(List *list){
  if(!list){ // Checking there IS a list to go off of
    printf("Currently no history, please enter some words.");
  }
  else{
    Item *tmp = list->root; 
    while(tmp){ // while curr node not null
      printf("[%d] %s\n", tmp->id, tmp->str);
      tmp->next;
    }
    printf("\n");
  }
}

/*Free the history list and the strings it references. */
void free_history(List *list){
  Item *tmp;
  Item *head = list->root;
  while(head){
    tmp = head; // we need something to hold our spot while we delete it, otherwise will get lost
    head = head->next;
    free(tmp);
  }
}
