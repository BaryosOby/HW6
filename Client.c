#include "Client.h"
#include <string.h>
#include "FillField.h"
#include <stdio.h>

/*creates new list of clients*/
int createClientList(clientList* list){
    clientNode* new = ALLOC(clientNode,1);
    new = NULL;
    list->head = new;
    return 1;
}


/*help function to call in addNewClient*/
int appendClientToList(clientNode ** head, Client newClient){
    clientNode* newNode = ALLOC(clientNode, 1);

    /*initializing new node's fields. */
    newNode->client = newClient;
    newNode->next = *head;
    /*linking list head to the new node*/
    *head = newNode;
    return 1;
}

/*adds new client to the head of clients list.*/
int addNewClient(clientNode ** listHead){

    Client newClient;
    char id[10];
    char rentedCarLicense[8];
    char rentDate[11];
    char rentHour[6];
    double priceForDay;

    printf("please enter new client's details: \n");

    /*setting user inputs to fields
    * checking input validation*/
    puts("please enter client name: ");
    newClient.name = fillFiledStrDynamic(2);

    puts("please enter client surname: ");
    newClient.surname = fillFiledStrDynamic(2);

    puts("please enter client's ID (9 digits): ");
    fillFieldStr(id, 9, 1, 1);
    strcpy(newClient.id, id);

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
    appendClientToList(listHead, newClient);

    return 1;
}

/*free allocated memory*/
int freeClient(clientNode* node){
    FREE(node->client.name);
    FREE(node->client.surname);
    FREE(node);
    return 1;
}

/*gets client id and delete it from the list. returns 1 if succeed, -1 if failed.*/
/*id parameter always starts as NULL.*/
int deleteClient(clientNode ** head, const char* id){
    clientNode* temp;
    char userInput[10];
    /*base case - empty pointer*/
    if(*head == NULL){
        return -1;
    }

    /*gets input from user*/
    if(!id){
        puts("please enter a client's ID to delete: ");
        fillFieldStr(userInput, 9, 1, 1);
    }
    else{
        strcpy(userInput, id);
    }

    /*true for first client*/
    if(strcmp((*head)->client.id, userInput) == 0){
        temp = (*head);
        *head = (*head)->next;
        freeClient(temp);
        return 1;
    }
    if (((*head)->next)&&(strcmp((*head)->next->client.id, userInput) == 0)){
        /*linking current node to one after the required to delete.*/
        temp =(*head)->next;
        (*head)->next = (*head)->next->next;
        freeClient(temp);
        return 1;
    }

    return deleteClient(&((*head)->next), userInput);
}

/*deletes all the clients from the list. returns 1 if succeed, 0 if failed.*/
int deleteAllClients(clientNode** head){

    /*recursive function. saves the next node's address and free the current one.*/
    clientNode * temp;
    /*base case - empty pointer*/
    if (!*head){
        return 1;
    }
    /*saves the address of the next node and frees the current one*/
    temp = (*head)->next;
    freeClient(*head);
    deleteAllClients(&temp);
    *head = NULL;
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
    printClientCarsForGivenRentDate(head->next, userInput,flag);
}
#endif


