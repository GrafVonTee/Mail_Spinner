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

typedef enum {
    STICK_HEAD,
    SCARING,
    SHUFFLE,
    ALL_TYPES_OF_HOLDING
} HOLDING_TYPES;

typedef struct {
    int id;
    wchar_t *name;
    int type;
    int package_type;
    int score;
    int holding_type;
    wchar_t *holding_description;
    wchar_t *description;
    Item *package;
} Customer;

static const Customer customers_array[ALL_CUSTOMERS] = {
        {-1, L"Slime",  SLIME,   SLIME_BALL, 5,      },
        {-1, L"Ghost",  GHOST,   SOUL,       12,     },
        {-1, L"DeD",    DEATH,   LISTTOKS,   20,     },
        {-1, L"Viking", VIKING,  AXE,        25,     },
        {-1, L"Knight", KNIGHT,  SHIELD,     100,    },
        {-1, L"DEMON",  DEMON,   JOKER,      -500,   }, // gay over
};

Customer *customers_ring;

// functions

void print_customer(int id);
int add_new_customer_with_type(CUSTOMERS customer_type);
int add_new_customer(Customer cust);