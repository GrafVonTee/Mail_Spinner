#pragma once

#include "customer.h"

typedef enum {
    TYPE_CUSTOMER,
    NAME_CUSTOMER,
    PACKAGE_CUSTOMER,
    SCORE,
    HOLD_EFFECT,
    HOLD_EFFECT_DESCRIPTION,
    DESCRIPTION_OF_CUSTOMER
} COLUMN_TYPE;

void parse_customers(const char *path);
CUSTOMERS get_customer_type(wchar_t *buff);
Customer get_customer_from_buff(wchar_t *buff);
int get_customer_score(wchar_t *token);