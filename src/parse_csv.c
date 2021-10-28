#define _CRT_SECURE_NO_WARNINGS

#include "parse_csv.h"
#include "customer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_definitions.h"

const char *type_names[ALL_CUSTOMERS] = {
        "SLIME",
        "GHOST",
        "DEATH",
        "VIKING",
        "KNIGHT",
        "DEMON"
};

#define buffer_size 1000

void parse_customers(const char *path) {
    FILE* file = fopen(path, "r");
    int str = 0;
    while (!ferror(file) && !feof(file)) {
        char buffer[buffer_size];
        fgets(buffer, buffer_size, file);
        if (str++ > 0) {
            int cust_id = add_new_customer(get_customer_from_buff(buffer));
            Item new_item = *customers_ring[cust_id].package;
            new_item.id = cust_id;
            add_new_item(new_item);
        }
    }
}

Customer get_customer_from_buff(char *buff) {
    char *token = strtok(buff, ",");
    Customer new_customer;
    int column = 0;
    while (token != NULL) {
        switch (column) {
            case TYPE_CUSTOMER:
                new_customer.type = get_customer_type(token);
                break;
            case NAME_CUSTOMER:
                new_customer.name = (char*)calloc(100, sizeof(char));
                strcpy(new_customer.name, token);
                break;
            case PACKAGE_CUSTOMER:
                new_customer.package_type = customers_array[new_customer.type].package_type;
                new_customer.package = (Item*)malloc(sizeof(Item));
                new_customer.package->name = (char*)calloc(100, sizeof(char));
                strcpy(new_customer.package->name, token);
                new_customer.package->type = new_customer.package_type;
                break;
            case SCORE:
                new_customer.score = get_customer_score(token);
                break;
            case HOLD_EFFECT:
            case DESCRIPTION_OF_CUSTOMER:
            default:
                break;
                //printf("ERROR: CUSTOMER UNDEFINED!\n");
        }
        column += 1;
        token = strtok(NULL, ",");
    }
    return new_customer;
}

CUSTOMERS get_customer_type(char *token) {
    for (int i = 0; i < ALL_CUSTOMERS; ++i)
        if (strcmp(token, type_names[i]) == 0)
            return i;
    printf("Error: customer type \"%s\" is undefined!\n", token);
    return -1;
}

int get_customer_score(char *token) {
    int score;
    sscanf(token, "%d", &score);
    return score;
}



