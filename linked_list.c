#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

struct list_node *new_node(size_t value) {
  struct list_node *n = malloc(sizeof(struct list_node));
  n -> value = value;
  n -> next = NULL;
  return n; 
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *h = new_node(value); //creates the new head node
  struct list_node *head_store = list -> head; //stores the original head
  list -> head = h;
  list -> head -> next = head_store;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *t = new_node(value);
  struct list_node *h = list -> head;
  if(h == NULL){ //check if list is empty
    list -> head = t;
  }
  else{
    struct list_node *n = h -> next;
    while(n != NULL){ //loop to the end
      h = n;
      n = h -> next;
    }
    h -> next = t;
  }
}

size_t remove_from_head(struct linked_list *list) { 
  if(list -> head == NULL){
    return 0;
  }
  struct list_node *n = list -> head -> next; //second value

  //free first value and set head to 2nd value
  free(list -> head);
  list -> head = n;
  return 0; 
}

size_t remove_from_tail(struct linked_list *list) { 
  struct list_node *h = list -> head;
  struct list_node *n = h -> next;
  if(list -> head == NULL){ //check if list is empty
    return 0;
  }
  else if(list -> head -> next == NULL){
    free(list -> head);
    list -> head = NULL;
  }
  else{ //if the list has 2 or more indexes
    while(n -> next != NULL){ //loop to the value 1 before end
      h = n;
      n = h -> next;
    }
    free(n);
    h -> next = NULL;
  }
  return 0; 
}

void free_list(struct linked_list list) {
  struct list_node *h = list.head;
  while(h != NULL){
    struct list_node *n = h -> next;
    free(h);
    h = n;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
