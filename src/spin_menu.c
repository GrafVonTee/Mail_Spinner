#include "spin_menu.h"
#include <list.h>
#include <queue.h>
#include <stdio.h>
#include "customer.h"
#include "printer.h"
#include "windows.h"

void quit();

void spin_menu(List *listtok, Queue* queue_array) {
    int nums_of_queues = listtok->prev->elem + 1;
    char command = 'o';
    char status = 0;
    Action_Type action = HOLDING;
    while ((command != 'q') && (status != 1)) {
        int index_of_list = listtok->elem;
        system("cls");
        print_table(action, get_head_from_queue(queue_array + index_of_list));
        //Sleep(1500);
        //wprintf(L"Current Queue #%i\n", index_of_list + 1);
        fseek(stdin,0,SEEK_END);
        scanf_s("%c", &command);
        action = HOLDING;
        switch (command) {
            case 'd': // right
                listtok = listtok->next;
                action = PRESS_RIGHT;
                break;
            case 'a': // left
                listtok = (List *) listtok->prev;
                action = PRESS_LEFT;
                break;
            case ' ': //print customer description
                if (get_head_from_queue(queue_array + index_of_list) != -1)
                    print_message(customers_ring[get_head_from_queue(queue_array + index_of_list)].description);
                quit();
                break;
            /*
            case 'c': // print customer
                if (get_head_from_queue(queue_array + index_of_list) == -1)
                    print_customer((-1) * (index_of_list + 1));
                else
                    print_customer(get_head_from_queue(queue_array + index_of_list));
                break;
            case 'h': // print package from main
                if (get_head(pack.main_stack) == -1)
                    wprintf(L"Hype \'Main\' is empty\n");
                else
                    print_item(get_head(pack.main_stack));
                wprintf(L"\n");
                break;
            case 'j': // print package from advanced
                if (get_head(pack.advanced_stack) == -1)
                    wprintf(L"Hype \'Advanced\' is empty\n");
                else
                    print_item(get_head(pack.advanced_stack));
                wprintf(L"\n");
                break;
            */
            case 'g': // give him a present from main
                if (get_head_from_queue(queue_array + index_of_list) == -1)
                    print_message(L"Hey, Dude, people do not need your presents at this Queue\n");
                else if  ((get_head(pack.main_stack) != -1)
                    && (get_head(pack.main_stack) == get_head_from_queue(queue_array + index_of_list)))
                {
                    queue_array[index_of_list] = *pop_from_queue(queue_array + index_of_list);
                    pop_from_stack(pack.main_stack);
                    print_message(L"Successful!");
                }
                else
                    print_message(L"Wrong Package!");
                quit();
                break;
            case 'w': // move head from advanced to main
                move_head_to_main();
                break;
            case 's': // move head from main to advanced
                move_head_to_advanced();
                break;
            case 'h': // print hint
                print_hint();
                quit();
                break;
            default:
                break;
        }
        status = get_empty_status_of_list(queue_array, nums_of_queues);
    }
    print_message(L"Das Ende, mein Freind!");
}

void print_all_queues(Queue *queue_array, int nums_of_queues) {
    for (int count = 0; count < nums_of_queues; count++) {
        for (int hh = 0; hh < queue_array[count].length; hh++)
            printf("%i ", queue_array[count].elems[hh]);
        printf("\n");
    }
}

char get_empty_status_of_list(Queue *queue_array, int nums_of_queues) {
    for (int count = 0; count < nums_of_queues; count++) {
        for (int hh = 0; hh < queue_array[count].length; ++hh)
            return 0;
    }
    return 1;
}