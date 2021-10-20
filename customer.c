#include <stdlib.h>
#include "customer.h"
#include <string.h>
#include <stdio.h>

void print_customer(int id) {
    Customer cust = customers_ring[id];
    printf("Customer %s (%s)\n", cust.name, customers_array[cust.type].name);
    printf("He needs package #%s\n", items_ring[id].name);
    printf("He can pay %i score!\n", cust.score);
}

int add_new_customer(CUSTOMERS customer_type) {
    static int id = -1;
    Customer new_costumer = customers_array[customer_type];
    new_costumer.id = ++id;

    Customer *temp_ring = (Customer*)calloc(new_costumer.id + 1, sizeof(Customer));
    for (int i = 0; i < new_costumer.id; i++)
        temp_ring[i] = customers_ring[i];
    temp_ring[new_costumer.id] = new_costumer;
    free(customers_ring);
    customers_ring = temp_ring;

    return new_costumer.id;
}