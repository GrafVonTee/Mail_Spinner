#include <stdlib.h>
#include "customer.h"

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