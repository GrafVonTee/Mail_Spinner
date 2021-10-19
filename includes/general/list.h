#pragma once

struct List {
    int elem;
    struct List *prev;
    struct List *next;
};
typedef struct List List;

List* make_list(int zero_num);

List* push_to_end(List *list, int new_elem_value);
List* push_to_start(List *list, int new_elem_value);
List* push_to_this(List *list, int new_elem_value);

List* pop_from_end(List *list);
List* pop_from_start(List *list);
List* pop_from_this(List *list);

void print_list(List *list);

List* get_last_elem(List *list);
List* get_first_elem(List *list);

void loop_the_list(List *list);
void break_the_loop(List *list);