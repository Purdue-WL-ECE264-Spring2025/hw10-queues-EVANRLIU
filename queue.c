#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state){
    uint64_t state_ser = serialize(state);
    if(state.empty_row != 3){
        move_up(state);
        insert_at_tail(q -> data, serialize(state));
        move_down(state);
    }
    if(state.empty_row != 0){
        move_down(state);
        insert_at_tail(q -> data, serialize(state));
        move_up(state);
    }
    if(state.empty_col != 3){
        move_left(state);
        insert_at_tail(q -> data, serialize(state));
        move_right(state);
    }
    if(state.empty_row != 0){
        move_right(state);
        insert_at_tail(q -> data, serialize(state));
        move_left(state);
    }
}

struct game_state dequeue(struct queue *q) { 
    size_t cur_state = remove_from_head(q -> data);
    return(deserialize(cur_state)); 
}

struct queue create_queue(struct game_state start){
    struct linked_list list;
    list.head = NULL;
    struct queue que;
    que.data = list;
    return que;
}

int number_of_moves(struct game_state start) { 
    int num_moves = 0;
    struct queue q = create_queue(start);
    insert_at_tail(q -> data, serialize(state));
    while(q.data -> head != NULL && game_state.tiles[3][3] != 0){
        struct queue cur_state = dequeue(&q); 
        if(game_state.tiles[3][3] == 0){
            return num_moves;
        }
        else{
            num_moves++;
            enqueue(&q, start);
            
        }
    }
    return 0; 
}
