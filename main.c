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

void quit() {
    char temp;
    fseek(stdin,0,SEEK_END);
    scanf_s("%c", &temp);
}

void initialize_queues(Queue *queues, int *nums_of_queues, int max_num_in_queue) {
    int temp_id = id - 1;
    for (int q = 0; q < *nums_of_queues; q++) {
        if (temp_id < 0) {
            break;
        }
        queues[q] = make_queue();
        int r = rand() % max_num_in_queue + 1;
        for (int p = 0; (p < r) && (temp_id > -1); p++) {
            int cust_id = temp_id--;
            push_to_queue(queues + q, cust_id);
            add_item_to_game(cust_id);
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
    quit();
    spin_menu(make_ring_of_death(nums_of_queues), qua_sus);

    quit();
    return 0;
}