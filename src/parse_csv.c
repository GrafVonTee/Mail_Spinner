#define _CRT_SECURE_NO_WARNINGS

#include "parse_csv.h"
#include "customer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

const wchar_t *type_names[ALL_CUSTOMERS] = {
        L"SLIME",
        L"GHOST",
        L"DEATH",
        L"VIKING",
        L"KNIGHT",
        L"DEMON"
};

#define buffer_size 1000

void parse_customers(const char *path) {
    FILE* file = fopen(path,"r,ccs=UTF-8");
    int str = 0;
    if (file == NULL)
        printf("You are Gay!\n");
    while (!ferror(file) && !feof(file)) {
        wchar_t buffer[buffer_size];
        fgetws(buffer, buffer_size, file);
        if ((str++ > 0) && (wcscmp(buffer, L"") != 0)) {
            int cust_id = add_new_customer(get_customer_from_buff(buffer));
            Item new_item = *customers_ring[cust_id].package;
            new_item.id = cust_id;
            add_new_item(new_item);
        }
        wcscpy(buffer, L"");
    }
}

Customer get_customer_from_buff(wchar_t *buff) {
    wchar_t *pt;
    wchar_t *token = wcstok(buff, L",", &pt);
    Customer new_customer;
    int column = 0;
    while (token != NULL) {
        switch (column) {
            case TYPE_CUSTOMER:
                new_customer.type = get_customer_type(token);
                break;
            case NAME_CUSTOMER:
                new_customer.name = (wchar_t*)calloc(wcslen(token), sizeof(wchar_t));
                wcscpy(new_customer.name, token);
                break;
            case PACKAGE_CUSTOMER:
                new_customer.package_type = customers_array[new_customer.type].package_type;
                new_customer.package = (Item*)malloc(sizeof(Item));
                new_customer.package->name = (wchar_t*)calloc(wcslen(token), sizeof(wchar_t));
                wcscpy(new_customer.package->name, token);
                new_customer.package->type = new_customer.package_type;
                break;
            case SCORE:
                new_customer.score = get_customer_score(token);
                break;
            case HOLD_EFFECT:
                break;
            case HOLD_EFFECT_DESCRIPTION:
                new_customer.holding_description = (wchar_t*)calloc(wcslen(token) + 1, sizeof(wchar_t));
                wcscpy(new_customer.holding_description, token);
                break;
            case DESCRIPTION_OF_CUSTOMER:
                new_customer.description = (wchar_t*)calloc(wcslen(token) + 1, sizeof(wchar_t));
                wcscpy(new_customer.description, token);
                break;
            default:
                break;
                //printf("ERROR: CUSTOMER UNDEFINED!\n");
        }
        column += 1;
        token = wcstok(NULL, L",", &pt);
    }
    return new_customer;
}

CUSTOMERS get_customer_type(wchar_t *token) {
    for (int i = 0; i < ALL_CUSTOMERS; ++i)
        if (wcscmp(token, type_names[i]) == 0)
            return i;
    wprintf(L"Error: customer type \"%s\" is undefined!\n", token);
    return -1;
}

int get_customer_score(wchar_t *token) {
    int score;
    swscanf(token, L"%d", &score);
    return score;
}



