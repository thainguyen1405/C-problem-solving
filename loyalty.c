//Programming Assignment 5
//Thai Nguyen
//th313791
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 19

//Struct to use
typedef struct customer {
    char name[MAXLEN + 1];
    int points;
} customer;


typedef struct treenode {
    customer* c;
    int size;
    struct treenode* left;
    struct treenode* right;
} treenode;


//Function prototypes
treenode* createNode(customer* c);
treenode* insert(treenode* root, customer* c);
treenode* find(treenode* root, char name[]);
treenode* findMax(treenode* node);
treenode* deleteNode(treenode* root, char name[]);

int countSmaller(treenode* root, char name[]);
void storeNodes(treenode* root, treenode** nodeArray, int* index);
void merge(treenode** arr, int left, int mid, int right);
void mergeSort(treenode** arr, int left, int right);
int compareNodes(const void* a, const void* b);
void printSortedNodes(treenode* root);
customer* createCustomer(char name[], int points);



int main() {
	//Set up the Program
    treenode* root = NULL;
    int n;  // n <= 300,000
    scanf("%d", &n);
    getchar(); // Consume newline
	
	//Scan and check commands
    for (int i = 0; i < n; i++) {
        char command[20];
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {    //Command 1
            char name[MAXLEN + 1];
            int points;
            scanf("%s %d", name, &points);
            getchar(); // Consume newline
            customer* newCustomer = createCustomer(name, points);
            root = insert(root, newCustomer);
            printf("%s %d\n", name, find(root, name)->c->points);
			
        } else if (strcmp(command, "sub") == 0) {   //Command 2
            char name[MAXLEN + 1];
            int points;
            scanf("%s %d", name, &points);
            getchar(); // Consume newline
            treenode* foundNode = find(root, name);
            if (foundNode != NULL) {
                if (foundNode->c->points <= points) {
                    points = foundNode->c->points;
                }
                foundNode->c->points -= points;
                printf("%s %d\n", name, foundNode->c->points);
            }
			
        } else if (strcmp(command, "del") == 0) {   //Command 3
            char name[MAXLEN + 1];
            scanf("%s", name);
            getchar(); // Consume newline
            treenode* foundNode = find(root, name);
            if (foundNode != NULL) {
                root = deleteNode(root, name);
                printf("%s deleted\n", name);
            } else {
                printf("%s not found\n", name);
            }
			
        } else if (strcmp(command, "search") == 0) {   //Command 4
            char name[MAXLEN + 1];
            scanf("%s", name);
            getchar(); // Consume newline
            treenode* foundNode = find(root, name);
            if (foundNode != NULL) {
                int depth = 0; // To calculate depth
                treenode* current = root;
                while (current != foundNode) {
                    if (strcmp(name, current->c->name) < 0) {
                        current = current->left;
                    } else {
                        current = current->right;
                    }
                    depth++;
                }
                printf("%s %d %d\n", name, foundNode->c->points, depth);
            } else {
                printf("%s not found\n", name);
            }
			
        } else if (strcmp(command, "count_smaller") == 0) {    //Command 5
            char name[MAXLEN + 1];
            scanf("%s", name);
            getchar(); //Consume newline
            int count = countSmaller(root, name);
            printf("%d\n", count);
        }
    }

    //Printing the sorted nodes
    printSortedNodes(root);

    return 0;
}

//Create a new customer
customer* createCustomer(char name[], int points) {
    customer* newCustomer = (customer*)malloc(sizeof(customer));
    strcpy(newCustomer->name, name);
    newCustomer->points = points;
    return newCustomer;
}

//Create a new node
treenode* createNode(customer* c) {
    treenode* newNode = (treenode*)malloc(sizeof(treenode));
    newNode->c = c;
    newNode->size = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Insert a node into the BST
treenode* insert(treenode* root, customer* c) {
    if (root == NULL) {
        return createNode(c);
    }

    int compare = strcmp(c->name, root->c->name);

    if (compare < 0) {
        root->left = insert(root->left, c);
    } else if (compare > 0) {
        root->right = insert(root->right, c);
    } else {
        // If the node with the same name exists, update the points
        root->c->points += c->points;
    }

    root->size++;
    return root;
}

//Find a node in the BST
treenode* find(treenode* root, char name[]) {
    if (root == NULL || strcmp(root->c->name, name) == 0) {
        return root;
    }

    int compare = strcmp(name, root->c->name);

    if (compare < 0) {
        return find(root->left, name);
    } else {
        return find(root->right, name);
    }
}

//Find the node has MAX value in a subtree
treenode* findMax(treenode* node) {
    treenode* current = node;

    while (current && current->right != NULL) {
        current = current->right;
    }

    return current;
}

//Delete a node from the BST
treenode* deleteNode(treenode* root, char name[]) {
    if (root == NULL) {
        return root;
    }

    int compare = strcmp(name, root->c->name);

    if (compare < 0) {
        root->left = deleteNode(root->left, name);
    } else if (compare > 0) {
        root->right = deleteNode(root->right, name);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            treenode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            treenode* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest right)
        treenode* temp = findMax(root->left);

        // Copy the inorder successor's content to this node
        root->c = temp->c;

        // Delete the inorder successor
        root->left = deleteNode(root->left, temp->c->name);
    }
    root->size--;
    return root;
}

//Count nodes smaller than a given node alphabetically
int countSmaller(treenode* root, char name[]) {
    if (root == NULL) {
        return 0;
    }

    int compare = strcmp(name, root->c->name);

    if (compare <= 0) {
        return countSmaller(root->left, name);
    } else {
        return 1 + countSmaller(root->left, name) + countSmaller(root->right, name);
    }
}

//Perform in-order traversal and store nodes in an array
void storeNodes(treenode* root, treenode** nodeArray, int* index) {
    if (root != NULL) {
        storeNodes(root->left, nodeArray, index);
        nodeArray[*index] = root;
        (*index)++;
        storeNodes(root->right, nodeArray, index);
    }
}

// Merge Sort implementation for sorting the nodes
void merge(treenode** arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    treenode* L[n1];
    treenode* R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compareNodes(&L[i], &R[j]) >= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(treenode** arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

//Compare nodes based on points (decending) and alphabetic (A->Z)
int compareNodes(const void* a, const void* b) {
    treenode* nodeA = *(treenode**)a;
    treenode* nodeB = *(treenode**)b;

    // Compare points first in descending order
    if (nodeA->c->points != nodeB->c->points) {
        return nodeA->c->points - nodeB->c->points;
    }

    //Compare names alphabetically if points are equal
    return strcmp(nodeB->c->name, nodeA->c->name);
}


//Count nodes in the tree
int countNodes(treenode* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

//Print the sorted nodes
void printSortedNodes(treenode* root) {
    int size = countNodes(root);
    treenode* nodeArray[size];
    int index = 0;
    storeNodes(root, nodeArray, &index);
    mergeSort(nodeArray, 0, size - 1);
    for (int i = 0; i < size; i++) {
        printf("%s %d\n", nodeArray[i]->c->name, nodeArray[i]->c->points);
    }
}
