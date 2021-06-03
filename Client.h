#ifndef CLIENT_H
#define CLIENT_H

typedef struct{

    char* name;
    char* surname;
    double id;
    char rentedCarLicense[8];
    char rentDate[11];
    char rentHour[6];
    double priceForDay;
}Client;

typedef struct clientNode_t{
    Client client;
    struct clientNode_t* left;
    struct clientNode_t* right;
}clientNode;

typedef struct {
    clientNode* root;
} clientBTS;

typedef struct clientNode_l{
    Client client;
    struct clientNode_l* next;
}clientNode_l;

typedef struct clientList{
    clientNode_l* head;
}clientList;


/*creates empty clientNode*/
clientBTS * createClientTree();

/*adds new client to the client to clientTree. return 1 if succeed, 0 if failed*/
int addNewClient(clientBTS * tree);

/*help function to call in addNewClient*/
clientNode * appendClientToTree(clientNode * tree, Client newClient);


/*gets id number of a client and delete it from the list. returns the tree's root.*/
clientNode * deleteClient(clientNode * tree, double id);

/*deletes all the clients from the list. returns 1 if succeed, 0 if failed.*/
int deleteAllClients(clientNode * tree);

void printClientCarsForGivenRentDate(clientNode * tree);

int clearClientsList(clientNode_l* head);

clientList* findClient(clientNode* tree);


#endif
