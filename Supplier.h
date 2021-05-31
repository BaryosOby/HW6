#ifndef SUPPLIER_H
#define SUPPLIER_H

typedef struct Supplier{
    double  id;
    char*  name;
    char  phoneNumber[11];
    double pastTransactionsNumber;
    double pastTransactionsSum;
}Supplier;

typedef struct SupplierNode_T{
    Supplier supplier;
    struct SupplierNode_T* next;
}supplierNode;

typedef struct supplierList{
    supplierNode * head;
}supplierList;


/*prints every supllier's details in the list*/
int printSuppliers(supplierNode* head);


/*creates new list of suppliers*/
int createSupplierList(supplierList * list);

/*adds new supplier to the suppliers list.*/
int addNewSupplier(supplierNode ** head);

int appendSupplierToList(supplierNode ** head, Supplier newSupplier);

/*return array containing the id of the 3 suppliers with the highest pastTransactionsSum*/
int threeGreatestSuppliers(supplierNode *head);

int threeGreatestSupplier_rec(supplierNode *head,Supplier* greatest);

/*gets supplier's name and deletes it from the list.return 1 if succeed else return 0*/
int deleteSupplier(supplierNode ** head, double id);

/*deleting all the suppliers from the suppliers list. return 1 if succeed else return */
int deleteAllSuppliers(supplierNode ** head);


#endif
