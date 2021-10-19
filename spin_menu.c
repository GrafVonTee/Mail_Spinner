#include "spin_menu.h"
#include <list.h>
#include <queue.h>
#include <stdio.h>

void spin_menu(List *listtok, Queue* queue_array) {
    int nums_of_queues = listtok->prev->elem + 1;
    char command = 'o';
    while ((command != 'q') && (listtok != NULL)) {
        int index_of_list = listtok->elem;
        printf("Current Queue #%i\n", index_of_list + 1);
        fseek(stdin,0,SEEK_END);
        scanf_s("%c", &command);
        switch (command) {
            case 'r': // right
                listtok = listtok->next;
                break;
            case 'l': // left
                listtok = (List *) listtok->prev;
                break;
            case 'p': // print
                print_all_queues(queue_array, nums_of_queues);
                break;
            case 'h': // head
                printf("Head of Queue #%i: %i\n", index_of_list + 1, get_head_from_queue(queue_array + index_of_list));
                break;
            case 'e': // erase
                queue_array[index_of_list] = *pop_from_queue(queue_array + index_of_list);
                if (get_head_from_queue(queue_array + index_of_list) == -1) {
                    listtok = pop_from_this(listtok);
                    printf("Queue #%i was cleared!\n", index_of_list + 1);
                }
                break;
            default:
                break;
        }
    }
    printf("\nDas Ende, mein Freind!\n");
}

void print_all_queues(Queue *queue_array, int nums_of_queues) {
    for (int count = 0; count < nums_of_queues; count++) {
        for (int hh = 0; hh < queue_array[count].length; hh++)
            printf("%i ", queue_array[count].elems[hh]);
        printf("\n");
    }
}