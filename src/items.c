#include "customer.h"
#include "items.h"
#include <stdlib.h>
#include <stdio.h>

void print_item(int id) {
    Item it = items_ring[id];
    wprintf(L"Item %s (%ls)\n", it.name, items_array[it.type].name);
    wprintf(L"It is needed for customer %ls\n", customers_ring[id].name);
    wprintf(L"He can pay %i score!\n", customers_ring[id].score);
}

void move_head_to_advanced() {
    if (get_head(pack.main_stack) == -1)
        return;
    push_to_stack(pack.advanced_stack, get_head(pack.main_stack));
    pop_from_stack(pack.main_stack);
}

void move_head_to_main() {
    if (get_head(pack.advanced_stack) == -1)
        return;
    push_to_stack(pack.main_stack, get_head(pack.advanced_stack));
    pop_from_stack(pack.advanced_stack);
}

/*
int add_new_item_with_id(int cust_id) {
    Item new_item = items_array[customers_ring[cust_id].package_type];
    return add_new_item(new_item);
}
*/

int add_new_item(Item it) {
    int new_item_id = add_new_item_to_general(it);
    add_item_to_game(new_item_id);
    return new_item_id;
}

int add_item_to_game(int item_id) {
    int chance = rand() % 5;
    if (chance < 2)
        push_to_stack(pack.main_stack, item_id);
    else
        push_to_stack(pack.advanced_stack, item_id);
    return item_id;
}

int add_new_item_to_general(Item it) {
    Item new_item = it;
    Item *temp_ring = (Item*)calloc(new_item.id + 1, sizeof(Item));
    for (int i = 0; i < new_item.id; i++)
        temp_ring[i] = items_ring[i];
    temp_ring[new_item.id] = new_item;
    free(items_ring);
    items_ring = temp_ring;
    return new_item.id;
}

void initialize_packages() {
    pack.main_stack = (Stack*)calloc(0, sizeof(Stack));
    pack.advanced_stack = (Stack*)calloc(0, sizeof(Stack));
    *pack.main_stack = make_stack();
    *pack.advanced_stack = make_stack();
}

int *get_all_packages() {
    int all_packages_length = pack.main_stack->length + pack.advanced_stack->length;
    int *original_packages = (int*)calloc(all_packages_length, sizeof(int));
    for (int i = 0; i < pack.main_stack->length; i++)
        original_packages[i] = pack.main_stack->elems[i];
    for (int j = 0; j < pack.advanced_stack->length; j++)
        original_packages[j + pack.main_stack->length] = pack.advanced_stack->elems[j];
    return original_packages;
}

void shuffle_packages() {
    int temp_length = pack.main_stack->length + pack.advanced_stack->length;
    int *temp_packages = get_all_packages();
    *pack.main_stack = make_stack();
    *pack.advanced_stack = make_stack();
    while (temp_length > 0) {
        int rand_num = rand() % temp_length;
        if (rand_num % 5 < 2)
            push_to_stack(pack.main_stack, temp_packages[rand_num]);
        else
            push_to_stack(pack.advanced_stack, temp_packages[rand_num]);
        temp_packages = resize_without_current_index(temp_packages, temp_length, rand_num);
        --temp_length;
    }
}

int *resize_without_current_index(int *arr, int length, int index) {
    int *temp_arr = (int*)calloc(length-1, sizeof(int));
    for (int i = 0; i < index; i++)
        temp_arr[i] = arr[i];
    for (int i = index + 1; i < length; i++)
        temp_arr[i-1] = arr[i];
    //free(arr);
    return temp_arr;
}