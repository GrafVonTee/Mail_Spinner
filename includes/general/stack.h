#pragma once

typedef struct {
    int *elems;
    int length;
} Stack;

Stack make_stack();
void push_to_stack(Stack *stake, int new_value);
void pop_from_stack(Stack *stake);
int get_head(Stack *stake);
