#pragma once

#include <list.h>
#include <queue.h>

void spin_menu(List *listtok, Queue* queue_array);
void print_all_queues(Queue *queue_array, int nums_of_queues);
char get_empty_status_of_list(Queue *queue_array, int nums_of_queues);