#include "Supplier.h"
#include <string.h>
#include "FillField.h"
#include <stdio.h>

/*creates new supplierList object*/
int createSupplierList(supplierList * list){
    supplierNode* new = ALLOC(supplierNode ,1);
    new = NULL;
    list->head = new;
    return 1;
}

/*help function to call in addNewSupplier*/
int appendSupplierToList(supplierNode ** head, Supplier newSupplier){
    supplierNode* newNode = ALLOC(supplierNode, 1);

    /*initializing new node's fields. */
    newNode->supplier = newSupplier;
    newNode->next = *head;

    /*linking list head to the new node*/
    *head = newNode;
    return 1;
}

/*adds new supplier to the head of suppliers list.*/
int addNewSupplier(supplierNode ** head){

    Supplier new_supplier;
    double  id;
    char  phoneNumber[11];
    double pastTransactionsNumber;
    double pastTransactionsSum;

    printf("please enter details for your new supplier: \n");

    /*setting user inputs to fields
     * checking input validation*/
    puts("please enter supplier's id (10 digits): ");
    fillFieldDouble(&id, 10, 1);
    new_supplier.id= id;

    puts("please enter supplier's name: ");
    new_supplier.name = fillFiledStrDynamic(2);

    puts("please enter supplier's phone number (10 digits): ");
    fillFieldStr(phoneNumber, 10, 1, 1);
    strcpy(new_supplier.phoneNumber, phoneNumber);

    puts("please enter number of transactions (5 digits): ");
    fillFieldDouble(&pastTransactionsNumber, 5, 1);
    new_supplier.pastTransactionsNumber = pastTransactionsNumber;

    puts("please enter sum of transactions (10 digits): ");
    fillFieldDouble(&pastTransactionsSum, 10, 1);
    new_supplier.pastTransactionsSum = pastTransactionsSum;

    /*creates new node and puts it in the list*/
    appendSupplierToList(head, new_supplier);

    return 1;
}

/*free allocated memory*/
int freeSupplier(supplierNode * node){
    FREE(node->supplier.name);
    FREE(node);
    return 1;
}

/*gets Supplier's id and delete it from the list. returns 1 if succeed, -1 if failed.*/
/*id parameter always starts as 0. */
int deleteSupplier(supplierNode ** head, double id){
    supplierNode * temp;
    double userInput = 0;
    /*base case - empty pointer*/
    if(*head == NULL){
        return -1;
    }

    /*gets input from user*/
    if(id == 0){
        puts("please enter supplier's ID to delete: ");
        fillFieldDouble(&userInput, 10, 1);
    }
    else{
        userInput = id;
    }

    /*true for first supplier*/
    if((*head)->supplier.id == userInput){
        temp = (*head);
        *head = (*head)->next;
        freeSupplier(temp);
        return 1;
    }

    if(((*head)->next)&&((*head)->next->supplier.id == userInput)){
        /*linking current node to one after the required to delete.*/
        temp =(*head)->next;
        (*head)->next = (*head)->next->next;
        freeSupplier(temp);
        return 1;
    }
    return deleteSupplier(&(*head)->next, userInput);
}

int deleteAllSuppliers(supplierNode ** head){

    /*recursive function. saves the next node's address and free the current one.*/
    supplierNode * temp;

    /*base case - empty pointer*/
    if (!*head){
        return 1;
    }
    /*saves the address of the next node and frees the current one*/
    temp = (*head)->next;
    freeSupplier(*head);
    deleteAllSuppliers(&temp);
    *head = NULL;
    return 1;
}

/*bubble sorting the current list of three greatest suppliers.*/
void threeGreatestSupplierBubble(Supplier*  greatest){
    int i,j;
    Supplier temp;
    for (i=0;i<2;i++){
        for (j=i+1;j<3;j++){
            if (greatest[i].pastTransactionsSum>greatest[j].pastTransactionsSum){
                temp = greatest[i];
                greatest[i] = greatest[j];
                greatest[j] = temp;
            }
        }
    }
}

/*return array containing the id of the 3 suppliers with the highest pastTransactionsSum*/
int threeGreatestSuppliers(supplierNode *head){

    /*the function first makes an array of the first three suppliers.
     * then, sorts the array in ascending order
     * then, compare the next suppliers with the first in array, which is the smallest one in every iteration*/
    int i,j;
    Supplier greatest[3];
    supplierNode* curr;
    curr = head;
    /*makes array of first three suppliers.*/
    for (i=0;i<3;i++){
        if (curr==NULL){
            puts("there are no three suppliers in the list");
            return -1;
        }
        greatest[i] = curr->supplier;
        curr = curr->next;
    }
    /*bubble sorting the array*/
    while (curr){
        threeGreatestSupplierBubble(greatest);
        /*insert the next supplier if true instead of the smallest one*/
        if (curr->supplier.pastTransactionsSum>greatest[0].pastTransactionsSum){
            greatest[0] = curr->supplier;
        }
        curr = curr->next;
    }
    puts("three greatest suppliers IDs are:");
    for (j=0;j<3;j++){
        printf("%d: %0.f \n",j+1,greatest[j].id);
    }
    return 1;
}

int threeGreatestSupplier_rec(supplierNode *head,Supplier* greatest){

    /*the function first makes an array of the first three suppliers.
     * then, sorts the array in ascending order
     * then, compare the next suppliers with the first in array, which is the smallest one in every recursive call*/
    int i,j;
    supplierNode* curr;
    Supplier temp;

    curr = head;
    /*inserting first three suppliers in the list*/
    if (greatest == NULL) {
        greatest = ALLOC(Supplier, 3);

        for (i = 0; i < 3; i++) {
            if (curr == NULL) {
                puts("there are no three suppliers in the list");
                FREE(greatest);
                return -1;
            }

            greatest[i] = curr->supplier;
            curr = curr->next;
        }
    }
    /*bubble sorting the array.*/
    for (i=0;i<2;i++){
        for (j=i+1;j<3;j++){
            if (greatest[i].pastTransactionsSum > greatest[j].pastTransactionsSum){
                temp = greatest[i];
                greatest[i] = greatest[j];
                greatest[j] = temp;
            }
        }
    }

    /*true when in the last supplier.*/
    if (curr == NULL) {
        puts("three greatest suppliers IDs are:");
        for (j=0;j<3;j++){
            printf("%d: %0.f \n",j+1,greatest[j].id);
        }
        FREE(greatest);
        return 1;
    }

    /*inserting next supplier instead of the smallest one if true.*/
    if (curr->supplier.pastTransactionsSum > greatest[0].pastTransactionsSum){
        greatest[0] = curr->supplier;
    }
    curr = curr->next;
    return threeGreatestSupplier_rec(curr,greatest);
}
#ifdef DAVIS
/*prints every supplier's details in the list*/
int printSuppliers(supplierNode* head){
    supplierNode* curr;
    int count;
    curr = head;
    /*check if pointer empty*/
    if (curr==NULL){
        puts("Suppliers list is empty");
        return -1; }
    puts("list of all suppliers:");
    count = 1;
    /*prints supplier's details and goes to the next one*/
    while(curr){
        printf("\nSupplier number %d:\n",count);
        printf("    Name:  %s\n",curr->supplier.name);
        printf("    Supplier's authorized dealer number:  %0.f\n",curr->supplier.id);
        printf("    Phone number:  %s\n",curr->supplier.phoneNumber);
        printf("    Number of past transaction with supplier  :%0.f\n",curr->supplier.pastTransactionsNumber);
        printf("    Sum of past transaction with supplier  :%0.f\n",curr->supplier.pastTransactionsSum);
        count++;
        curr = curr->next;
    }
    return 1;
}
#endif

