#pragma once

#include "items.h"

typedef enum {
    EMPTY_MAN,
    SLIME,
    GHOST,
    DEATH,
    VIKING,
    KNIGHT,
    DEMON,
    ALL_CUSTOMERS
} CUSTOMERS;

typedef enum {
    NONE,
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

static const Customer empty_man = {
        -1,
        L"Empty Man",
        EMPTY_MAN,
        EMPTY_ITEM,
        20,
        NONE,
        L"",
        L"Hey, this Queue is empty! You're cool!"
};

static const Customer customers_array[ALL_CUSTOMERS] = {
        {-1, L"Hint",      EMPTY_MAN, EMPTY_ITEM  },
        {-1, L"Slime",     SLIME,     SLIME_BALL  },
        {-1, L"Ghost",     GHOST,     SOUL        },
        {-1, L"DeD",       DEATH,     LISTTOKS    },
        {-1, L"Viking",    VIKING,    AXE         },
        {-1, L"Knight",    KNIGHT,    SHIELD      },
        {-1, L"DEMON",     DEMON,     JOKER       },
};

Customer *customers_ring;

// functions

int add_new_customer(Customer cust);