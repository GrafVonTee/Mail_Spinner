#pragma once

#include "items.h"

typedef enum {
    SLIME,
    GHOST,
    DEATH,
    VIKING,
    KNIGHT,
    DEMON,
    ALL_CUSTOMERS
} CUSTOMERS;

typedef struct {
    int id;
    char *name;
    int type;
    int package_type;
    int score;
    //char *description;
    Item *package;
} Customer;

static const Customer customers_array[ALL_CUSTOMERS] = {
        {-1, "Slime",  SLIME,   SLIME_BALL, 5,      },
        {-1, "Ghost",  GHOST,   SOUL,       12,     },
        {-1, "DeD",    DEATH,   LISTTOKS,   20,     },
        {-1, "Viking", VIKING,  AXE,        25,     },
        {-1, "Knight", KNIGHT,  SHIELD,     100     },
        {-1, "Putin",  DEMON,   JOKER,      -500    }, // gay over
};

Customer *customers_ring;

// functions

void print_customer(int id);
int add_new_customer_with_type(CUSTOMERS customer_type);
int add_new_customer(Customer cust);