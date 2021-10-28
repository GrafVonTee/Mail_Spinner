#pragma once

#include "items.h"
#include "customer.h"

// functions from items.h

void print_item(int id);
void move_head_to_advanced();
void move_head_to_main();
int add_new_item_with_id(int cust_id);
int add_new_item(Item it);
void initialize_packages();
