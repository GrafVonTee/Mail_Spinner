#include <stdio.h>
#include <stdlib.h>
#include <queue.h>
#include <list.h>
#include <stack.h>
#include <time.h>
#include "spin_menu.h"
#include "customer.h"

static int max_index = 0;

int main() {
    printf("Enter Num of Queues: ");
    int nums_of_queues;
    scanf_s("%d", &nums_of_queues);
    Queue *qua_sus = (Queue*)calloc(nums_of_queues, sizeof(Queue));
    srand(time(0));

    initialize_packages();

    for (int q = 0; q < nums_of_queues; q++) {
        qua_sus[q] = make_queue();
        int r = rand() % 3 + 1;
        for (int p = 0; p < r; p++) {
            int random_customer_type = rand() % ALL_CUSTOMERS;
            int cust_id = add_new_customer(random_customer_type);
            push_to_queue(qua_sus + q, cust_id);
            add_new_item(cust_id);
            max_index = cust_id;
        }
    }

    List *ring_of_death = make_list(0);
    for (int i = 1; i < nums_of_queues; i++)
        push_to_end(ring_of_death, i);
    loop_the_list(ring_of_death);

    spin_menu(ring_of_death, qua_sus);

    char temp;
    fseek(stdin,0,SEEK_END);
    scanf_s("%c", &temp);
    return 0;
}