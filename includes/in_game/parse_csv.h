#pragma once

#include "customer.h"

typedef enum {
    TYPE_CUSTOMER,
    NAME_CUSTOMER,
    PACKAGE_CUSTOMER,
    SCORE,
    HOLD_EFFECT,
    DESCRIPTION_OF_CUSTOMER
} COLUMN_TYPE;

void parse_customers(const char *path);
CUSTOMERS get_customer_type(char *buff);
Customer get_customer_from_buff(char *buff);
int get_customer_score(char *token);