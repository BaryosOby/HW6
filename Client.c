#include "Client.h"
#include <string.h>
#include "FillField.h"
#include <stdio.h>

clientBTS* createClientTree(){
    clientBTS * newTree;
    newTree = ALLOC(clientBTS ,1);
    newTree->root = NULL;
    return newTree;
}

/*help function to call in addNewClient. orders tree by ids*/
clientNode * appendClientToTree(clientNode* tree, Client newClient){
    clientNode * newNode;
    if(!tree){
        newNode = ALLOC(clientNode ,1);
        newNode->client = newClient;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if(newClient.id == tree->client.id) {
        puts("ID already exists in Data Base.");
        return NULL;
    }
    if(newClient.id < tree->client.id) { /* Go left*/
        tree->left = appendClientToTree(tree->left, newClient);
    }
    else{ /* Go right*/
        tree->right = appendClientToTree(tree->right, newClient);
    }
    return tree;
}

/*adds new client to the head of clients list.*/
int addNewClient(clientBTS* tree){

    Client newClient;
    double id;
    char rentedCarLicense[8];
    char rentDate[11];
    char rentHour[6];
    double priceForDay;

    printf("please enter new client's details: \n");

    /*setting user inputs to fields
     *checking input validation*/
    puts("please enter client name: ");
    newClient.name = fillFiledStrDynamic(2);

    puts("please enter client surname: ");
    newClient.surname = fillFiledStrDynamic(2);

    puts("please enter client's ID (9 digits): ");
    fillFieldDouble(&id, 9, 1);
    newClient.id = id;

    puts("please enter rented car license (7 digits): ");
    fillFieldStr(rentedCarLicense, 7, 1, 1);
    strcpy(newClient.rentedCarLicense, rentedCarLicense);

    puts("please enter renting date (from 2000) (dd/mm/yyyy format only): ");
    fillFieldStr(rentDate, 10, 3,1);
    strcpy(newClient.rentDate, rentDate);

    puts("please enter renting hour: (mm:hh format only) ");
    fillFieldStr(rentHour, 5, 4, 1);
    strcpy(newClient.rentHour, rentHour);

    puts("please enter price per day: (max 3 digits) ");
    fillFieldDouble(&priceForDay,3, 0);
    newClient.priceForDay = priceForDay;

    /*creates new node and puts it in the list*/
    appendClientToTree(tree->root, newClient);

    return 1;
}

/*free allocated memory*/
int freeClient(clientNode* node){
    FREE(node->client.name);
    FREE(node->client.surname);
    FREE(node);
    return 1;
}


/*delete clientNode by given id*/
clientNode * deleteClient(clientNode * tree, double id){
    clientNode *temp, *follower, **followerAddr;
    double userInput = 0;

    /*gets input from user*/
    if(id == 0){
        puts("please enter id for the client you wish to delete:");
        fillFieldDouble(&userInput, 7, 1);
    }
    else{
        userInput = id;
    }
    if (!tree) {
        return NULL;
    }

    /* searching wanted client in tree's children*/
    if(tree->client.id != userInput) {
        /* Go left*/
        if( id < (tree->client.id)) {
            tree->left = deleteClient(tree->left, userInput);
        }
            /* Go right*/
        else {
            tree->right = deleteClient(tree->right, userInput);
        }

    }


/* Option 1: tree is a leaf*/
    if(!(tree->left) && !(tree->right)) {
        freeClient(tree);
        return NULL;
    }
/* Option 2: tree has only one child*/
    else if(!(tree->left)) {
        temp = tree->right;
        freeClient(tree);
        return temp;
    }
    else if(!(tree->right)) {
        temp = tree->left;
        freeClient(tree);
        return temp;
    }
/* Option 3: tree has 2 children*/
    else {
        follower = tree->right;
        followerAddr = &(tree->right);
        while(follower->left) {
            followerAddr = &(follower->left);
            follower = follower->left;
        }
        tree->client = follower->client;
        *followerAddr = deleteClient(follower, follower->client.id);
    }
    return tree;
}

/*free all the nodes from th tree. returns empty pointer*/
int deleteAllClients(clientNode * tree){
    if(!tree){
        return 1;
    }
    /*free children first*/
    deleteAllClients(tree->left);
    deleteAllClients(tree->right);

    freeClient(tree);
    return 1;
}

/*recursive function. every call it compares client's rent date and prints it's name if true.*/
int printClientCarsForGivenRentDate_rec(clientNode* tree, char* userInput){
    int flag = 0;

    /*base case - empty pointer*/
    if (!tree) {
        return 0;
    }

    /*prints client's name and surname*/
    if (strcmp(userInput, tree->client.rentDate) == 0) {
        printf("\n\t%s %s", tree->client.name, tree->client.surname);
    }

    /*goes to tree's children*/
    flag += printClientCarsForGivenRentDate_rec(tree->left, userInput);
    flag += printClientCarsForGivenRentDate_rec(tree->right, userInput);
    return flag;
}


/*gets rent date from user, prints name and surname of clients that rented a car in this date.*/
void printClientCarsForGivenRentDate(clientNode * tree) {

    char userInput[11];
    int flag;

    /*gets input from user*/
    puts("please enter a rent date to check: ");
    fillFieldStr(userInput, 10, 3, 1);

    printf("clients who rented a car at %s:", userInput);
    flag = printClientCarsForGivenRentDate_rec(tree, userInput);
    if (!flag) {
        puts("\n\tno clients found...");
    }
}

int deepCopyClientFields(clientNode_l* dest, Client source){
    dest->client.name = copyField(source.name);
    dest->client.surname = copyField(source.surname);
    dest->client.priceForDay = source.priceForDay;
    dest->client.id = source.id;
    strcpy(dest->client.rentDate, source.rentDate);
    strcpy(dest->client.rentHour, source.rentHour);
    strcpy(dest->client.rentedCarLicense, source.rentedCarLicense);
    return 1;
}

/*---------------------findClient functions---------------------*/

clientNode_l *createClientNode_l(clientNode_l ** head, Client client){
    clientNode_l * new = ALLOC(clientNode_l,1);
    new->next = NULL;
    new->client = client;
    return new;
}

int findClientByID(clientNode* tree, double id, clientNode_l** head){

    if(!tree){
        return 0;
    }
    if(tree->client.id == id){
        *head = createClientNode_l(head,tree->client);
        return 1;
    }
    if(tree->client.id > id){
        return findClientByID(tree->left , id, head);
    }
    return findClientByID(tree->right , id, head);
}

int insertNewNode(clientNode_l** head, Client client){
    clientNode_l *newNode = NULL, *curr;

    /*initializing new node. */
    newNode = ALLOC(clientNode_l, 1);
    newNode->next = NULL;
    newNode->client = client;

    /*true when list is empty, or client's id is smaller then first node's*/
    if ((*head == NULL) || (*head)->client.id >= client.id) {
        newNode->next = *head;
        *head = newNode;
        return 1;
    }

    /*finds the first bigger client id*/
    curr = *head;
    while ((curr->next) && (curr->next->client.id < newNode->client.id)) {
        curr = curr->next;
    }

    /*inserting the new node after the current one.*/
    newNode->next = curr->next;
    curr->next = newNode;
    return 1;
}

/*TODO free clients list in menu*/
int findClientByRentDate(clientNode* tree, const char* date, clientNode_l** head){
    if(!tree){
        return 0;
    }
    if(strcmp(tree->client.rentDate, date) == 0) {
        insertNewNode(head, tree->client);
    }
    findClientByRentDate(tree->left, date, head);
    findClientByRentDate(tree->right, date, head);
    return 1;
}

/*TODO free list in menu*/
clientList* findClient(clientNode* tree){

    clientList *clients;
    int userChoice;
    double idInput;
    char dateInput[11];

    if(!tree){
        puts("there are no clients in data base.");
        return NULL;
    }

    clients = ALLOC(clientList,1);

    puts("how would you like to search for client?\n"
         "\t 1. by ID."
         "\t2. by rent date."
         "\tany other number to exit.");
    fillFieldInt(&userChoice,1,1,1);
    switch (userChoice) {
        case 1:
            puts("please enter a client's ID to search: ");
            fillFieldDouble(&idInput, 9, 1);
            findClientByID(tree, idInput, (&clients->head));
            break;
        case 2:
            puts("please enter a rent date to search: ");
            fillFieldStr(dateInput, 10, 3,1);
            findClientByRentDate(tree, dateInput, (&clients->head));
            break;
        default:
            return NULL;
    }
    return clients;
}

int clearClientsList(clientNode_l* head){

    /*recursive function. saves the next node's address and free the current one.*/
    clientNode_l * temp;
    /*base case - empty pointer*/
    if (!head){
        return 1;
    }
    /*saves the address of the next node and frees the current one*/
    temp = (head)->next;
    FREE((head)->client.name);
    FREE((head)->client.surname);
    FREE(head);
    clearClientsList(temp);
    head = NULL;
    return 1;
}







