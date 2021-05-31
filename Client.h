#ifndef CLIENT_H
#define CLIENT_H

typedef struct{

    char* name;
    char* surname;
    char id[10];
    char rentedCarLicense[8];
    char rentDate[11];
    char rentHour[6];
    double priceForDay;
}Client;

typedef struct clientNode_t{
    Client client;
    struct clientNode_t* next;
}clientNode;

typedef struct clientList{
    clientNode* head;
}clientList;

/*creates new list of clients*/
int createClientList(clientList* list);

/*help function to call in addNewClient*/
int appendClientToList(clientNode ** head, Client newClient);

/*adds new client to the clients list[index]. return 1 if succeed, 0 if failed*/
int addNewClient(clientNode ** listHead);


/*gets client id and delete it from the list. returns 1 if succeed, 0 if failed.*/
int deleteClient(clientNode ** head, const char* id);

/*deletes all the clients from the list. returns 1 if succeed, 0 if failed.*/
int deleteAllClients(clientNode** head);

void printClientCarsForGivenRentDate(clientNode * head, const char* date,int flag);


#endif
