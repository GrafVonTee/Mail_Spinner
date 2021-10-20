#include "spin_menu.h"
#include <list.h>
#include <queue.h>
#include <stdio.h>
#include <customer.h>

void spin_menu(List *listtok, Queue* queue_array) {
    //int nums_of_queues = listtok->prev->elem + 1;
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
            /*
            case 'p': // print
                print_all_queues(queue_array, nums_of_queues);
                break;
            */
            case 'c': // print customer
                print_customer(get_head_from_queue(queue_array + index_of_list));
                printf("\n");
                break;
            case 'h': // print package from main
                if (get_head(&pack.main_stack) == -1)
                    printf("Hype \'Main\' is empty\n");
                else
                    print_item(get_head(&pack.main_stack));
                printf("\n");
                break;
            case 'j': // print package from advanced
                if (get_head(&pack.advanced_stack) == -1)
                    printf("Hype \'Advanced\' is empty\n");
                else
                    print_item(get_head(&pack.advanced_stack));
                printf("\n");
                break;
            case 'g': // give him a present from main
                if  ((get_head(&pack.main_stack) != -1)
                    && (get_head(&pack.main_stack) == get_head_from_queue(queue_array + index_of_list)))
                {
                    queue_array[index_of_list] = *pop_from_queue(queue_array + index_of_list);
                    pop_from_stack(&pack.main_stack);
                    printf("Successful!\n");

                    if (get_head_from_queue(queue_array + index_of_list) == -1) {
                        listtok = pop_from_this(listtok);
                        printf("Queue #%i was cleared!\n", index_of_list + 1);
                    }
                }
                else
                    printf("Wrong Package!\n");
                break;
            case 'm': // move head from advanced to main
                move_head_to_main();
                break;
            case 'a': // move head from main to advanced
                move_head_to_advanced();
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