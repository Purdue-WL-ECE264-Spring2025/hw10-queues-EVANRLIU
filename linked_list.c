#include "linked_list.h"

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
  struct list_node *h = list -> head;
  struct list_node *n = h -> next;
  while(n != NULL){ //loop to the end
    n = h -> next;
    h = n;
  }
  n = new_node(value);
  h -> next = n;
}

size_t remove_from_head(struct linked_list *list) { 
  struct list_node *h = list -> head; //first value
  struct list_node *n = h -> next; //second value

  //free first value and set h to 2nd value
  free(h);
  h = n;
  return 0; 
}

size_t remove_from_tail(struct linked_list *list) { 
  struct list_node *h = list -> head;
  struct list_node *n = h -> next;
  while(n != NULL){ //loop to the end
    n = h -> next;
    h = n;
  }
  free(n);
  h -> next = NULL;
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
