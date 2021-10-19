#pragma once

typedef struct {
    int *elems;
    int length;
} Queue;

Queue make_queue();
void push_to_queue(Queue *qua, int new_value);
Queue* pop_from_queue(Queue *qua);
int get_head_from_queue(Queue *qua);