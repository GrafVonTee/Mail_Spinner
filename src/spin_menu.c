#include "spin_menu.h"
#include <list.h>
#include <queue.h>
#include <stdio.h>
#include "customer.h"
#include "printer.h"
#include "windows.h"
#include <conio.h>

void wait_char();

void spin_menu(List *listtok, Queue* queue_array) {
    int nums_of_queues = listtok->prev->elem + 1;
    char command = 'o';
    char status = 0;
    int score = nums_of_queues * 15;
    Action_Type action = HOLDING;
    while ((command != 'q') && (status != 1) && (score >= 0)) {
        system("cls");
        int index_of_list = listtok->elem;
        print_table(action, get_head_from_queue(queue_array + index_of_list), score);
        command = _getch();
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
                if (get_head_from_queue(queue_array + index_of_list) != -1) {
                    Customer customer = customers_ring[get_head_from_queue(queue_array + index_of_list)];
                    print_message(customer.description);
                    if (customer.holding_type == SCARING) {
                        int rand_num = rand() % 10;
                        for (int i = 0; i <= rand_num; ++i)
                            listtok = listtok->next;
                    }
                }
                score += 2;
                wait_char();
                break;
            case 'g': // give him a present from main
                if (get_head_from_queue(queue_array + index_of_list) == -1)
                    print_message(L"Hey, Dude, people do not need your presents at this Queue\n");
                else if  ((get_head(pack.main_stack) != -1)
                    && (get_head(pack.main_stack) == get_head_from_queue(queue_array + index_of_list)))
                {
                    Customer customer = customers_ring[get_head_from_queue(queue_array + index_of_list)];
                    score += customer.score + 3;
                    queue_array[index_of_list] = *pop_from_queue(queue_array + index_of_list);
                    pop_from_stack(pack.main_stack);
                    print_message(L"Successful!");
                }
                else
                    print_message(L"Wrong Package!");
                wait_char();
                break;
            case 'w': // move head from advanced to main
                move_head_to_main();
                break;
            case 's': // move head from main to advanced
                move_head_to_advanced();
                break;
            case 'h': // print hint
                print_hint();
                score += 2;
                wait_char();
                break;
            default:
                break;
        }
        status = get_empty_status_of_list(queue_array, nums_of_queues);
        score -= 2;
    }
    if (score < 0) {
        print_message(L"Game Over!!!");
        wait_char();
        print_message(L"Your score is low than zero!");
        wait_char();
    }
    else if (status == 1) {
        print_message(L"!!!WINNER!!!");
        wait_char();
        wchar_t message[50] = L"Your total score: ";
        wchar_t scr_str[50];
        _itow(score, scr_str, 10);
        wcscat(message, scr_str);
        print_message(message);
        wait_char();
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