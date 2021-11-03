#pragma once

#include <stack.h>
#include <wchar.h>

typedef enum {
    SLIME_BALL,
    SOUL,
    LISTTOKS,
    AXE,
    SHIELD,
    JOKER,
    ALL_ITEMS,
} ITEMS_TYPES;

typedef struct {
    int id;
    wchar_t *name;
    int type;
} Item;

static const Item items_array[ALL_ITEMS] = {
        {-1, L"slime ball",  SLIME_BALL},
        {-1, L"soul",        SOUL},
        {-1, L"LISTOCHKI",   LISTTOKS},
        {-1, L"axe",         AXE},
        {-1, L"shield",      SHIELD},
        {-1, L"JOKER",       JOKER},
};

Item *items_ring;

typedef struct {
    Stack *main_stack;
    Stack *advanced_stack;
} Packages;

Packages pack;

void print_item(int id);
void move_head_to_advanced();
void move_head_to_main();
int add_new_item_with_id(int cust_id);
int add_new_item(Item it);
void initialize_packages();