#include <stdio.h>
#include <stdlib.h>
#include <queue.h>
#include <list.h>
#include <stack.h>
#include <time.h>
#include <parse_csv.h>
#include <spin_menu.h>
#include "func_definitions.h"

extern const int id;

int main() {
    printf("Enter Num of Queues: ");
    int nums_of_queues;
    scanf_s("%d", &nums_of_queues);
    Queue *qua_sus = (Queue*)calloc(nums_of_queues, sizeof(Queue));
    srand(time(0));

    initialize_packages();
    parse_customers("..\\customers.csv");

    int temp_id = id - 1;
    for (int q = 0; q < nums_of_queues; q++) {
        qua_sus[q] = make_queue();
        int r = rand() % 3 + 1;
        for (int p = 0; (p < r) && (temp_id > -1); p++) {
            int cust_id = temp_id--;
            push_to_queue(qua_sus + q, cust_id);
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