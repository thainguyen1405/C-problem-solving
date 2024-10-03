#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITSIZE 10
#define MAXLEN 50
#define MAXROWS 100000

typedef struct order {
    int s_seat;
    int e_seat;
    char* name;
} order;

typedef struct theaterrow {
    order** list_orders;
    int max_size;
    int cur_size;
} theaterrow;

// Function Prototypes 
order* make_order(int start, int end, char* this_name);
theaterrow* make_empty_row();
int conflict(order* order1, order* order2);
int can_add_order(theaterrow* this_row, order* this_order);
void add_order(theaterrow* this_row, order* this_order);
char* get_owner(theaterrow** theater, int row, int seat_num);
char* get_row_owner(theaterrow* this_row, int seat_num);
int contains(order* myorder, int seat_no);
void free_order(order* this_order);
void free_row(theaterrow* this_row);



int main() {
    // create an empty theater with MAXROWS rows
    theaterrow** amc_ = calloc(MAXROWS + 1, sizeof(theaterrow*));
    for (int i = 0; i < MAXROWS; i++) {
        amc_[i] = make_empty_row();
    }

    int start, end, row;
    char input[MAXLEN];
    char name[MAXLEN];
    char command[MAXLEN];

    while (1) {
        printf("Enter the input: ");
        fgets(input, sizeof(input), stdin);

        // Extract command and details
        sscanf(input, "%s %d %d %d %s", command, &start, &end, &row, name);

        if (strcmp(command, "QUIT") == 0) {
            break;
        }

        if (strcmp(command, "BUY") == 0) {
            order* new_order = make_order(start, end, name);
            int result = can_add_order(amc_[row], new_order);
            if (result == 1) 
            {
                add_order(amc_[row], new_order);
                printf("SUCCESS\n");
            } 
            else if(result == 0) 
            {
                printf("FAILURE\n");
                free_order(new_order);
            }
        } else if (strcmp(command, "LOOKUP") == 0) {
            char* owner = get_owner(amc_, row, start);
            if (owner != NULL) {
                printf("%s\n", owner);
            } else {
                printf("NO ONE\n");
            }
        }
    }

    // free allocated memory
    for (int i = 0; i < MAXROWS; i++) {
        free_row(amc_[i]);
        free(amc_[i]);
    }
    free(amc_);

    return 0;
}

order* make_order(int start, int end, char* this_name)  //Allocated order storing
{
    order* newOrder = malloc(sizeof(order));
    newOrder->s_seat = start;
    newOrder->e_seat = end;
    newOrder->name = malloc(strlen(this_name) + 1);
    strcpy(newOrder->name, this_name);

    return newOrder;
}

theaterrow* make_empty_row()  //Allocated memory for one theaterrow
{
    theaterrow* newtheaterrow = malloc(sizeof(theaterrow));
    newtheaterrow->max_size = 10;
    newtheaterrow->cur_size = 0;
    newtheaterrow->list_orders = malloc(newtheaterrow->max_size * sizeof(order*));

    return newtheaterrow;
}

int conflict(order* order1, order* order2)   //Checking if there's conflict
{
    if(order1->s_seat <= order2->e_seat && order1->e_seat >= order2->s_seat)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int can_add_order(theaterrow* this_row, order* this_order)
{
    for (int i = 0; i < this_row->cur_size; i++) {
        if (conflict(this_order, this_row->list_orders[i])) {
            return 0;
        }
        if (conflict(this_row->list_orders[i], this_order)) {
            return 0;
        }
    }
    return 1;
    
}


void add_order(theaterrow* this_row, order* this_order)   //add this_order to this_row
{
    if (this_row->cur_size == this_row->max_size) {
        this_row->max_size *= 2;
        this_row->list_orders = realloc(this_row->list_orders, this_row->max_size * sizeof(order*));
    }
    this_row->list_orders[this_row->cur_size++] = this_order;
}

char* get_owner(theaterrow** theater, int row, int seat_num)  //return string storing owner's name
{
    if (theater == NULL || row < 0 || row >= MAXROWS) {
        return NULL;
    }
    theaterrow* this_row = theater[row];
    for (int i = 0; i < this_row->cur_size; i++) {
        order* current_order = this_row->list_orders[i];
        if (seat_num >= current_order->s_seat && seat_num <= current_order->e_seat) {
            return current_order->name;
        }
    }
    return NULL;
}


int contains(order* myorder, int seat_no)  //Check if seat contain
{
    if(seat_no >= myorder->s_seat && seat_no <= myorder->e_seat)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void free_order(order* this_order)   //Free all memory of this_order
{
    free(this_order->name);
    free(this_order);
}

void free_row(theaterrow* this_row)   //Free all memory of this_row
{
    for (int i = 0; i < this_row->cur_size; i++) {
        free_order(this_row->list_orders[i]);
    }
    free(this_row->list_orders);
    free(this_row);
}
