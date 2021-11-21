#pragma once
#include "customer.h"

typedef enum {
    HOLDING,
    PRESS_LEFT,
    PRESS_RIGHT,
    ALL_ACTIONS
} Action_Type;

void print_table(Action_Type action, int cust_id);
void print_customer_new(int id, int index);
void print_customer(int id);
void print_inner();
void print_message(wchar_t *message);
void print_hype(int index);
void print_hint();
void print_box(int id, int index);
wchar_t **tokenize_string(wchar_t *str, int *string_nums);
void print_horizontal_line(int);
void print_arrow_line(int type, int index);