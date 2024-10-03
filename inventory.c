//Programming Assignment 7
//Thai Nguyen
//th313791

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 19
#define TABLESIZE 300007

//Struct to Use
typedef struct item {
    char name[MAXLEN+1];
    int quantity;
    int saleprice;
} item;

typedef struct node {
    item* iPtr;
    struct node* next;
} node;

typedef struct hashtable {
    node** lists;
    int size;
} hashtable;

//Global declaration
int total_cash = 100000; // Starting at $100,000
int total_complexity = 0; 


//Function prototypes
int hashfunc(char* word, int size);
hashtable* init_table();
node* find_or_create_item(hashtable* ht, char* name, int is_create);
void buy_item(hashtable* ht, char* name, int quantity, int totalprice);
void sell_item(hashtable* ht, char* name, int quantity);
void change_price(hashtable* ht, char* name, int new_price);
void free_table(hashtable* ht);


int main() {
    int n;   //n <= 300,000
    scanf("%d", &n);

    hashtable* ht = init_table();

    for (int i = 0; i < n; i++) {
		//Declare the variables
        char command[20], item_name[MAXLEN + 1];
        int quantity, price;
        scanf("%s %s", command, item_name);
		
		//Check the input for each command
        if (strcmp(command, "buy") == 0) {
            scanf("%d %d", &quantity, &price);
            buy_item(ht, item_name, quantity, price);
        } else if (strcmp(command, "sell") == 0) {
            scanf("%d", &quantity);
            sell_item(ht, item_name, quantity);
        } else if (strcmp(command, "change_price") == 0) {
            scanf("%d", &price);
            change_price(ht, item_name, price);
        }
    }
	
	//Print the result 
    printf("%d\n", total_cash);
    printf("%d\n", total_complexity);
	
	//Free memory
    free_table(ht);

    return 0;
}

//Hash Function to Use
int hashfunc(char* word, int size) {
    int len = strlen(word);
    int res = 0;
    for (int i = 0; i < len; i++)
        res = (1151 * res + (word[i] - 'a')) % size;
    return res;
}

//Initialize the hash table
hashtable* init_table() {
    hashtable* ht = malloc(sizeof(hashtable));
    ht->size = TABLESIZE;
    ht->lists = malloc(sizeof(node*) * ht->size);
    for (int i = 0; i < ht->size; i++) {
        ht->lists[i] = NULL;
    }
    return ht;
}

//Find or create an item in hashtable
node* find_or_create_item(hashtable* ht, char* name, int is_create) {
    int index = hashfunc(name, ht->size);
    node* head = ht->lists[index];
    node* prev = NULL;
    int k = 1; // Start from the first node

    while (head != NULL) {
        if (strcmp(head->iPtr->name, name) == 0) {
            total_complexity += k;
            return head;
        }
        prev = head;
        head = head->next;
        k++;
    }

    if (is_create) {
        item* newItem = malloc(sizeof(item));
        strcpy(newItem->name, name);
        newItem->quantity = 0; // Initial quantity is zero
        newItem->saleprice = 0; // Initial price is not set

        node* newNode = malloc(sizeof(node));
        newNode->iPtr = newItem;
        newNode->next = ht->lists[index];
        ht->lists[index] = newNode;

        total_complexity += k;
        return newNode;
    }

    return NULL;
}

//Command 1: Buy <item> <quantity> <totalprice>
void buy_item(hashtable* ht, char* name, int quantity, int totalprice) {
    node* itemNode = find_or_create_item(ht, name, 1);
    itemNode->iPtr->quantity += quantity;
    total_cash -= totalprice;
    printf("%s %d %d\n", name, itemNode->iPtr->quantity, total_cash);
}

//Command 2: Sell <item> <quantity>
void sell_item(hashtable* ht, char* name, int quantity) {
    node* itemNode = find_or_create_item(ht, name, 0);
    if (itemNode != NULL && itemNode->iPtr->quantity >= quantity) {
        itemNode->iPtr->quantity -= quantity;
    } else {
        quantity = itemNode->iPtr->quantity;
        itemNode->iPtr->quantity = 0;
    }
    total_cash += quantity * itemNode->iPtr->saleprice;
    printf("%s %d %d\n", name, itemNode->iPtr->quantity, total_cash);
}

//Command 3: Change price <item> <new_price>
void change_price(hashtable* ht, char* name, int new_price) {
    node* itemNode = find_or_create_item(ht, name, 0);
    if (itemNode != NULL) {
        itemNode->iPtr->saleprice = new_price;
    }
}

//Free the hash table
void free_table(hashtable* ht) {
    for (int i = 0; i < ht->size; i++) {
        node* head = ht->lists[i];
        while (head != NULL) {
            node* temp = head;
            head = head->next;
            free(temp->iPtr);
            free(temp);
        }
    }
    free(ht->lists);
    free(ht);
}
