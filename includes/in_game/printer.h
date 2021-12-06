#pragma once
#include "customer.h"

typedef enum {
    HOLDING,
    PRESS_LEFT,
    PRESS_RIGHT,
    ALL_ACTIONS
} Action_Type;

typedef enum {
    LEFT_ARROW,
    RIGHT_ARROW,
    LEFT_BOLD_ARROW,
    RIGHT_BOLD_ARROW,
    SPACES,
    KEYES,
    ALL_ARROWS
} Arrows_Types;

void print_table(Action_Type action, int cust_id, int score);
void print_customer_new(int id, int index);
void print_customer(int id);
void print_inner();
void print_message(wchar_t *message);
void print_hype(int index, int score);
void print_hint();
void print_box(int id, int index);
wchar_t **tokenize_string(wchar_t *str, int *string_nums);
void print_horizontal_line(int);
void print_arrow_line(Arrows_Types type, int index);