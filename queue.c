#include "queue.h"
#include "tile_game.h"
#include <stdio.h>

void enqueue(struct queue *q, struct game_state state){
    state.num_steps++;
    struct game_state new_state;
    if(state.empty_row != 3){
        new_state = state;
        move_up(&new_state);
        insert_at_tail(&(q -> data), serialize(new_state));
    }
    if(state.empty_row != 0){
        new_state = state;
        move_down(&new_state);
        insert_at_tail(&(q -> data), serialize(new_state));
    }
    if(state.empty_col != 3){
        new_state = state;
        move_left(&new_state);
        insert_at_tail(&(q -> data), serialize(new_state));
    }
    if(state.empty_row != 0){
        new_state = state;
        move_right(&new_state);
        insert_at_tail(&(q -> data), serialize(new_state));
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
                sorted = state.tiles[row][col] == 0;
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
    while(q.data.head != NULL && !sorted){
        struct game_state cur_state = dequeue(&q); //access the current board and remove it from the queue
        printf("%d\n", cur_state.num_steps);
        if(check_sorted(cur_state)){
            free_list(q.data);
            return cur_state.num_steps;
        }
        else{
            enqueue(&q, cur_state);            
        }
    }
    return 0; 
}
