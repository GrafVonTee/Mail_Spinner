#include <stdlib.h>
#include "customer.h"
#include <string.h>
#include <stdio.h>

void print_customer(int id) {
    Customer cust = customers_ring[id];
    wprintf(L"Customer %ls (%ls)\n", cust.name, customers_array[cust.type].name);
    wprintf(L"He needs package #%ls\n", items_ring[id].name);
    wprintf(L"He can pay %i score!\n", cust.score);
    wprintf(L"Hold Effect: %ls\n", cust.holding_description);
    wprintf(L"Description:\n%ls\n", cust.description);
}

int id = 0;

int add_new_customer_with_type(CUSTOMERS customer_type) {
    Customer new_customer = customers_array[customer_type];
    return add_new_customer(new_customer);
}

int add_new_customer(Customer cust) {
    cust.id = id++;
    Customer *temp_ring = (Customer*)calloc(cust.id + 1, sizeof(Customer));
    for (int i = 0; i < cust.id; i++)
        temp_ring[i] = customers_ring[i];
    temp_ring[cust.id] = cust;
    free(customers_ring);
    customers_ring = temp_ring;

    return cust.id;
}