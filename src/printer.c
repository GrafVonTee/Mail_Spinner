#define _CRT_SECURE_NO_WARNINGS

#include "printer.h"
#include "customer.h"
#include "items.h"
#include <stdlib.h>

const int width = 80;
const int height = 24;
const int inner_line_space = 2;
const int box_inside_length = 50;

const int box_width = 40;
const int box_height = 14;

typedef enum {
    LEFT_ARROW,
    RIGHT_ARROW,
    LEFT_BOLD_ARROW,
    RIGHT_BOLD_ARROW,
    SPACES,
    KEYES,
    ALL_ARROWS
} Arrows_Types;

const wchar_t *slime[14] = {
    L"#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^#",
    L"|                                      |",
    L"|                                      |",
    L"|                                      |",
    L"|                                      |",
    L"|              __________              |",
    L"|             (#####     )\\            |",
    L"|           (########     )\\)          |",
    L"|         (/###### _     ^   ))        |",
    L"|        /######  (#)   (#)  \\))       |",
    L"|        ((##                  ))      |",
    L"|        ((______________________)     |",
    L"|                                      |",
    L"#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^#"
};

const int arrow_length = 10;
const wchar_t *left_arrow[] = {
         L"  /|      ",
         L" / |_____ ",
         L"/        |",
        L"\\   _____|",
        L" \\ |      ",
        L"  \\|      "
};
const wchar_t *right_arrow[] = {
     L"      |\\  ",
     L" _____| \\ ",
     L"|        \\",
     L"|_____   /" ,
     L"      | / " ,
     L"      |/  "
};
const wchar_t *left_bold_arrow[] = {
         L"  /|      ",
         L" /#|_____ ",
         L"/########|",
        L"\\########|",
        L" \\#|      ",
        L"  \\|      "
};
const wchar_t *right_bold_arrow[] = {
        L"      |\\  ",
        L" _____|#\\ ",
        L"|########\\",
        L"|########/" ,
        L"      |#/ " ,
        L"      |/  "
};

void print_table(Action_Type action, int cust_id) {
    print_horizontal_line(width);
    for (int h = 0; h < height; ++h) {
        wprintf(L"|");

        print_inner();
        print_arrow_line((action == PRESS_LEFT) ? LEFT_BOLD_ARROW : LEFT_ARROW, h-9);
        print_inner();

        if ((h < 4) && (h > 0))
            print_customer_new(cust_id, h-1);
        else if ((h < 19) && (h > 4))
            print_box(cust_id, h-5);
        else if ((h < 23) && (h > 19))
            print_hype(h-20);
        else
            for (int space = 0; space < box_inside_length; ++space)
                wprintf(L" ");

        print_inner();
        print_arrow_line((action == PRESS_RIGHT) ? RIGHT_BOLD_ARROW : RIGHT_ARROW, h-9);
        print_inner();

        wprintf(L"|\n");
    }
    print_horizontal_line(width);
}

void print_inner() {
    for (int space = 0; space < inner_line_space; ++space)
        wprintf(L" ");
}

void print_arrow_line(Arrows_Types type, int index) {
    if ((index == -1) || (index == ALL_ARROWS))
        type = SPACES;
    else if ((index < -1) || (index > ALL_ARROWS))
        type = KEYES;
    switch (type) {
        case LEFT_ARROW:
            wprintf(left_arrow[index]);
            break;
        case RIGHT_ARROW:
            wprintf(right_arrow[index]);
            break;
        case LEFT_BOLD_ARROW:
            wprintf(left_bold_arrow[index]);
            break;
        case RIGHT_BOLD_ARROW:
            wprintf(right_bold_arrow[index]);
            break;
        case KEYES:
            for (int i = 0; i < arrow_length; ++i)
                wprintf(L"$");
            break;
        default:
            for (int i = 0; i < arrow_length; ++i)
                wprintf(L" ");
            break;
    }
}

void print_horizontal_line(int l_width) {
    wprintf(L"#");
    for (int i = 0; i < l_width - 2; ++i)
        wprintf(L"^");
    wprintf(L"#\n");
}

void print_inner_line(int l_width) {
    for (int i = 0; i < l_width; ++i)
        wprintf(L" ");
}

void print_customer_new(int id, int index) {
    wchar_t *replicus[3];
    if ((id < 0) && (index > -1)) {
        wchar_t empty_name[50] = L"";
        wcscat(empty_name, empty_man.name);
        wcscat(empty_name, L" (");
        wcscat(empty_name, customers_array[EMPTY_MAN].name);
        wcscat(empty_name, L")");
        replicus[0] = empty_name;
        replicus[1] = L"";
        replicus[2] = empty_man.description;
        wprintf(replicus[index]);
        for (int i = 0; i < box_inside_length - wcslen(replicus[index]); ++i)
            wprintf(L" ");
    }
    else if (id >= 0) {
        Customer cust = customers_ring[id];
        wchar_t cust_name[50] = L"";
        wchar_t pack_name[50] = L"";
        wcscat(cust_name, cust.name);
        wcscat(cust_name, L" (");
        wcscat(cust_name, customers_array[cust.type].name);
        wcscat(cust_name, L")");
        wcscat(pack_name, L"It needs a package: ");
        wcscat(pack_name, cust.package->name);
        replicus[0] = cust_name;
        replicus[1] = L"";
        replicus[2] = pack_name; //cust.description;
        unsigned int indent_len = (box_inside_length - wcslen(replicus[index])) / 2;
        for (int i = 0; i < indent_len; ++i)
            wprintf(L" ");
        wprintf(replicus[index]);
        for (int i = 0; i < box_inside_length - wcslen(replicus[index]) - indent_len; ++i)
            wprintf(L" ");
    }
}

void print_hype(int index) {
    wchar_t *replicus[3];
    if (index > -1) {
        wchar_t main_hype[50] = L"Main Hype: ";
        wchar_t advn_hype[50] = L"Advanced: ";
        if (get_head(pack.main_stack) == -1)
            wcscat(main_hype, L"\'Empty\'");
        else
            wcscat(main_hype, items_ring[get_head(pack.main_stack)].name);
        if (get_head(pack.advanced_stack) == -1)
            wcscat(advn_hype, L"\'Empty\'");
        else
            wcscat(advn_hype, items_ring[get_head(pack.advanced_stack)].name);
        replicus[0] = main_hype;
        replicus[1] = L"";
        replicus[2] = advn_hype;

        unsigned int indent_len = (box_inside_length - wcslen(replicus[index])) / 2;
        for (int i = 0; i < indent_len; ++i)
            wprintf(L" ");
        wprintf(replicus[index]);
        for (int i = 0; i < box_inside_length - wcslen(replicus[index]) - indent_len; ++i)
            wprintf(L" ");
    }
}

void print_box(int id, int index) {
    if (index > -1) {
        unsigned int indent_len = (box_inside_length - box_width) / 2;
        for (int i = 0; i < indent_len; ++i)
            wprintf(L" ");

        wprintf(slime[index]);

        for (int i = 0; i < box_inside_length - box_width - indent_len; ++i)
            wprintf(L" ");
    }
}

void print_message(wchar_t *string) {
    int string_len = 0;
    wchar_t **message = tokenize_string(string, &string_len);
    print_horizontal_line(width);
    for (int h = 0; h < height; ++h) {
        wprintf(L"|");
        print_inner();

        if ((h-1 < string_len) && (h > 0))
            wprintf(message[h-1]);
        else
            print_inner_line(width-6);

        print_inner();
        wprintf(L"|\n");
    }
    print_horizontal_line(width);
}

wchar_t **tokenize_string(wchar_t *str, int *string_nums) {
    wchar_t **sub_str = (wchar_t**)calloc(20, sizeof(wchar_t*));
    for (int i = 0; i < 20; ++i) {
        sub_str[i] = (wchar_t *) calloc(width - 6, sizeof(wchar_t));
        wcscpy(sub_str[i], L"");
    }
    wchar_t *pt;
    wchar_t *token = wcstok(str, L" ", &pt);
    int column = 0;
    while (token != NULL) {
        if (wcslen(sub_str[column]) + wcslen(token) > width - 6) {
            for (int s = 0; s <= width-6 - wcslen(sub_str[column]); ++s)
                wcscat(sub_str[column], L" ");
            ++column;
        }
        wcscat(sub_str[column], L" ");
        wcscat(sub_str[column], token);
        token = wcstok(NULL, L" \n", &pt);
    }
    int len = wcslen(sub_str[column]);
    for (int s = 0; s <= width-6 - len - 1; ++s)
        wcscat(sub_str[column], L" ");
    *string_nums = column + 1;
    return sub_str;
}

/*
void print_customer(int id) {
    if (id < 0) {
        wprintf(L"Customer: %ls (%ls)\n", empty_man.name, customers_array[EMPTY_MAN].name, id * (-1));
        wprintf(L"Hint:\n%ls\n", empty_man.description);
    }
    else {
        Customer cust = customers_ring[id];
        wprintf(L"Customer: %ls (%ls)\n", cust.name, customers_array[cust.type].name);
        wprintf(L"He needs package #%ls\n", items_ring[id].name);
        wprintf(L"He can pay %i score!\n", cust.score);
        wprintf(L"Hold Effect: %ls\n", cust.holding_description);
        wprintf(L"Description:\n%ls\n", cust.description);
    }
    wprintf(L"\n");
}
*/

void print_hint() {
    const int all_replicus = 8;
    wchar_t *replicus[] = {
            L"~~~ HINT ~~~",
            L"",
            L"h - print this hint",
            L"\'_\' - print description",
            L"a - move left",
            L"d - move right",
            L"w - move package to main hype",
            L"s - move package to advanced hype"
    };
    print_horizontal_line(box_inside_length);
    for (int h = -1; h < all_replicus + 1; ++h) {
        wprintf(L"|");
        print_inner();

        if ((h < 0) || (h == all_replicus))
            for (int s = 0; s < box_inside_length - 6; ++s)
                wprintf(L" ");
        else {
            unsigned int indent_len = (box_inside_length - wcslen(replicus[h]) - 6) / 2;
            for (int i = 0; i < indent_len; ++i)
                wprintf(L" ");
            wprintf(replicus[h]);
            for (int i = 0; i < box_inside_length - wcslen(replicus[h]) - 6 - indent_len; ++i)
                wprintf(L" ");
        }

        print_inner();
        wprintf(L"|\n");
    }
    print_horizontal_line(box_inside_length);
}