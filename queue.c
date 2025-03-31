
#include "queue.h"
#include "tile_game.h"
#include <stdio.h>
void print_shit(struct game_state state){
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            printf("%d ", state.tiles[row][col]);
        }
    }
    printf("\n");
}

bool check_dup(struct linked_list data, uint64_t new_state){
    struct list_node *h = data.head;
    if(h == NULL){return false;}
    struct list_node *n = h -> next;
    while(n != NULL){
        if(h -> value == new_state){
            return true;
        }
        h = n;
        n = h -> next;
    }
    return false;
}

void enqueue(struct queue *q, struct game_state state){
    struct game_state new_state;
    if(check_dup(q -> data, serialize(state)) == true){return;} //if there is a suplicate, return
    if(state.empty_row != 3){
        printf("up ");
        new_state = state;
        move_up(&new_state);
        insert_at_tail(&(q -> data), serialize(new_state));
        print_shit(new_state);
    }
    if(state.empty_row != 0){
        printf("down ");
        new_state = state;
        move_down(&new_state);
        insert_at_tail(&(q -> data), serialize(new_state));
        print_shit(new_state);
    }
    if(state.empty_col != 3){
        printf("left ");
        new_state = state;
        move_left(&new_state);
        insert_at_tail(&(q -> data), serialize(new_state));
        print_shit(new_state);
    }
    if(state.empty_col != 0){
        printf("right ");
        new_state = state;
        move_right(&new_state);
        insert_at_tail(&(q -> data), serialize(new_state));
        print_shit(new_state);
    }
}

struct game_state dequeue(struct queue *q) { 
    size_t cur_state = remove_from_head(&(q -> data));
    return(deserialize(cur_state)); 
}

struct queue create_queue(){
    struct linked_list list;
    list.head = NULL;
    struct queue que;
    que.data = list;
    return que;
}

bool check_sorted(struct game_state state){
    bool sorted = true;
    int expectedNum = 1;
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            if(row == 3 && col == 3){
                if(state.tiles[row][col] != 0){
                    sorted = false;
                };
            }
            else if(state.tiles[row][col] == expectedNum){
                expectedNum++;
            }
            else{
                sorted = false;
            }
        }
    }
    return sorted;
}


int number_of_moves(struct game_state start){ 
    start.num_steps = 0;
    struct queue q = create_queue(); //create the queue
    insert_at_tail(&q.data, serialize(start)); //insert the starting board to the queue
    bool sorted = check_sorted(start);
    int num = 0;
    while(q.data.head != NULL && !sorted && num <= 14){
        struct game_state cur_state = dequeue(&q); //access the current board and remove it from the queue
        printf("%d current ", cur_state.num_steps);
        num = cur_state.num_steps;
        print_shit(cur_state);
        if(check_sorted(cur_state)){
            free_list(q.data);
            return cur_state.num_steps;
        }
        else{
            enqueue(&q, cur_state);            
        }
    }
    free_list(q.data);
    return 0; 
}