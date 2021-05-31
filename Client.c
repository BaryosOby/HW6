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

    if(newClient.id < tree->client.id) /* Go left*/
        tree->left = appendClientToTree(tree->left, newClient);
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

#ifdef DAVIS
/*gets rent date from user, prints name and surname of clients that rented a car in this date.
 * date parameter always starts as NULL*/
void printClientCarsForGivenRentDate(clientNode * head, const char* date,int flag){

    /*recursive function. every call it compares client's rent date and prints it's name if true.*/
    char userInput[11];

    /*base case - empty pointer*/
    if(!head){
        if (flag ==0){
            puts("there are no clients who rented a car in given date");
        }
        return;
    }
    /*gets input from user*/
    if(!date){
        puts("please enter a rent date to check: ");
        fillFieldStr(userInput, 10, 3,1);
    }
    else{
        strcpy(userInput, date);
    }
    /*prints client's name and surname*/
    if(strcmp(userInput, head->client.rentDate) == 0){
        if (flag == 0 ){
            printf("clients that rented a car in %s: ", userInput);
            flag =1;
        }
        printf("\n%s %s", head->client.name, head->client.surname);
    }
    /*goes to the next client in list*/
    /*printClientCarsForGivenRentDate(head->next, userInput,flag);*/
}
#endif


