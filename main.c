#include <stdio.h>
#include <stdlib.h>
#include <queue.h>
#include <list.h>
#include <time.h>
#include <windows.h>
#include "parse_csv.h"
#include "spin_menu.h"
#include <fcntl.h>
#include <io.h>
#include "printer.h"

extern const int id;

void wait_char() {
    fseek(stdin,0,SEEK_END);
    getchar();
}

void initialize_queues(Queue *queues, int *nums_of_queues, int max_num_in_queue) {
    int temp_length = id;
    int *id_bools = (int*)calloc(temp_length, sizeof(int));
    for (int i = 0; i < temp_length; ++i)
        id_bools[i] = customers_ring[i].id;
    for (int q = 0; q < *nums_of_queues; q++) {
        if (temp_length <= 0)
            break;
        queues[q] = make_queue();
        int r = rand() % max_num_in_queue + 1;
        for (int p = 0; (p < r) && (temp_length > 0); p++) {
            int rand_num = rand() % temp_length;
            int cust_id = id_bools[rand_num];
            push_to_queue(queues + q, cust_id);
            add_item_to_game(cust_id);
            id_bools = resize_without_current_index(id_bools, temp_length, rand_num);
            temp_length--;
        }
    }
}

int get_max_num_of_queue() {
    wprintf(L"Enter Max Num of Customers in Queue: ");
    int max_num_in_queue;
    scanf_s("%d", &max_num_in_queue);
    return max_num_in_queue;
}

int get_nums_of_queues() {
    wprintf(L"Enter Num of Queues: ");
    int nums_of_queues;
    scanf_s("%d", &nums_of_queues);
    return nums_of_queues;
}

void initialize_params() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);
    srand(time(0));
}

List *make_ring_of_death(int nums_of_queues) {
    List *ring_of_death = make_list(0);
    for (int i = 1; i < nums_of_queues; i++)
        push_to_end(ring_of_death, i);
    loop_the_list(ring_of_death);
    return ring_of_death;
}

int main(int argc, char *argv[]) {
    initialize_params();

    int nums_of_queues = get_nums_of_queues();
    Queue *qua_sus = (Queue*)calloc(nums_of_queues, sizeof(Queue));
    int max_num_in_queue = get_max_num_of_queue();

    initialize_packages();
    parse_customers((argc < 2) ? ("customers.csv") : argv[1]);
    initialize_queues(qua_sus, &nums_of_queues, max_num_in_queue);
    shuffle_packages();

    print_hint();
    wait_char();
    spin_menu(make_ring_of_death(nums_of_queues), qua_sus);

    wait_char();
    return 0;
}