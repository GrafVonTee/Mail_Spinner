#include "customer.h"
#include "items.h"
#include <stdlib.h>
#include <stdio.h>

void print_item(int id) {
    Item it = items_ring[id];
    printf("Item %s (%s)\n", it.name, items_array[it.type].name);
    printf("It is needed for customer %s\n", customers_ring[id].name);
    printf("He can pay %i score!\n", customers_ring[id].score);
}

void move_head_to_advanced() {
    if (get_head(&pack.main_stack) == -1)
        return;
    push_to_stack(&pack.advanced_stack, get_head(&pack.main_stack));
    pop_from_stack(&pack.main_stack);
}

void move_head_to_main() {
    if (get_head(&pack.advanced_stack) == -1)
        return;
    push_to_stack(&pack.main_stack, get_head(&pack.advanced_stack));
    pop_from_stack(&pack.advanced_stack);
}

int add_new_item(int cust_id) {
    Item new_item = items_array[customers_ring[cust_id].package_type];
    new_item.id = cust_id;

    Item *temp_ring = (Item*)calloc(new_item.id + 1, sizeof(Item));
    for (int i = 0; i < new_item.id; i++)
        temp_ring[i] = items_ring[i];
    temp_ring[new_item.id] = new_item;
    free(items_ring);
    items_ring = temp_ring;

    int chance = rand() % 5;
    if (chance < 2)
        push_to_stack(&pack.main_stack, new_item.id);
    else
        push_to_stack(&pack.advanced_stack, new_item.id);

    return new_item.id;
}

void initialize_packages() {
    pack.main_stack = make_stack();
    pack.advanced_stack = make_stack();
}