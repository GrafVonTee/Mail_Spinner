#pragma once

#include <stack.h>

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
    char *name;
    int type;
} Item;

static const Item items_array[ALL_ITEMS] = {
        {-1, "slime ball",  SLIME_BALL},
        {-1, "soul",        SOUL},
        {-1, "LISTOCHKI",   LISTTOKS},
        {-1, "axe",         AXE},
        {-1, "shield",      SHIELD},
        {-1, "JOKER",       JOKER},
};

Item *items_ring;

typedef struct {
    Stack *main_stack;
    Stack *advanced_stack;
} Packages;

Packages pack;