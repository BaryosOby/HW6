#include "Supplier.h"
#include <string.h>
#include "FillField.h"
#include <stdio.h>

/*creates new supplier binary search tree pointer*/
supplierBST * createSupplierTree(){
    supplierBST * newTree;
    newTree = ALLOC(supplierBST, 1);
    newTree->root = NULL;
    newTree->size = 0;
    return newTree;
}


/*help function to call in addNewSupplier*/
supplierNode * appendSupplierToTree(supplierNode * tree, Supplier newSupplier){
    supplierNode * newNode;
    if(!tree){
        newNode = ALLOC(supplierNode ,1);
        newNode->supplier = newSupplier;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if(newSupplier.id == tree->supplier.id) {
        puts("ID already exists in Data Base.");
        return NULL;
    }
    if(newSupplier.id < tree->supplier.id) /* Go left*/
        tree->left = appendSupplierToTree(tree->left, newSupplier);
    else /* Go right*/
        tree->right = appendSupplierToTree(tree->right, newSupplier);

    return tree;
}

/*adds new supplier to the head of suppliers list.*/
int addNewSupplier(supplierBST* tree){
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

    /*creates new node and puts it in the tree*/
    tree->root = appendSupplierToTree(tree->root, new_supplier);
    tree->size += 1;
    return 1;
}

/*free allocated memory*/
int freeSupplierFields(supplierNode * node){
    if(node) {
        FREE(node->supplier.name);
    }
    return 1;
}

int deepCopySuppliersFields(supplierNode * tree,Supplier follower){
    freeSupplierFields(tree);
    tree->supplier.name = copyField(follower.name);
    tree->supplier.pastTransactionsSum = follower.pastTransactionsSum;
    tree->supplier.pastTransactionsNumber= follower.pastTransactionsSum;
    tree->supplier.id=follower.id;
    strcpy(tree->supplier.phoneNumber,follower.phoneNumber);
    return 1;
}

/*delete supplierNode by given id*/
supplierNode * deleteSupplier(supplierNode * tree, double id, supplierBST* bst){
    supplierNode *temp, *follower, **followerAddr;
    double userInput = 0;

    /*gets input from user*/
    if(id == 0){
        puts("please enter id for the supplier you wish to delete:");
        fillFieldDouble(&userInput, 10, 1);
    }
    else{
        userInput = id;
    }
    if (!tree) {
        return NULL;
    }

    /* searching wanted supplier in tree's children*/
    if(tree->supplier.id != userInput) {
        /* Go left*/
        if( id < (tree->supplier.id)) {
            tree->left = deleteSupplier(tree->left, userInput, bst);
        }
            /* Go right*/
        else {
            tree->right = deleteSupplier(tree->right, userInput, bst);
        }

    }


/* Option 1: tree is a leaf*/
    if(!(tree->left) && !(tree->right)) {
        freeSupplierFields(tree);
        FREE(tree);
        return NULL;
    }
/* Option 2: tree has only one child*/
    else if(!(tree->left)) {
        temp = tree->right;
        freeSupplierFields(tree);
        FREE(tree);
        return temp;
    }
    else if(!(tree->right)) {
        temp = tree->left;
        freeSupplierFields(tree);
        FREE(tree);
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
        deepCopySuppliersFields(tree, follower->supplier);
        *followerAddr = deleteSupplier(follower, follower->supplier.id,bst);
    }
    bst->size -=1;
    return tree;
}

/*free all the nodes from the tree. returns empty pointer*/
int deleteAllNodesSupplier(supplierNode * tree){
    if(!tree){
        return 1;
    }
    /*free children first*/
    deleteAllNodesSupplier(tree->left);
    deleteAllNodesSupplier(tree->right);
    freeSupplierFields(tree);
    FREE(tree);
    return 1;
}
int deleteAllSuppliers(supplierBST * tree){
    deleteAllNodesSupplier(tree->root);
    tree->root =NULL;
    tree->size = 0;
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


void addToGreatest(Supplier* greatest,supplierNode* tree){
    if (!tree){
        return;
    }
    if (tree->supplier.pastTransactionsSum>greatest[0].pastTransactionsSum){
        greatest[0]=tree->supplier;
        threeGreatestSupplierBubble(greatest);
    }
    addToGreatest(greatest,tree->left);
    addToGreatest(greatest,tree->right);
}

/*return array containing the id of the 3 suppliers with the highest pastTransactionsSum*/
int threeGreatestSuppliers(supplierBST tree){
    Supplier greatest[3];
    int i;
    if (tree.size<3){
        puts("there are less then three suppliers in the list");
        return -1;
    }
    for (i = 0; i < 3; i++) {
        greatest[i].pastTransactionsSum=0;}
    addToGreatest(greatest,tree.root);
    puts("three greatest suppliers are:");
    for(i = 0; i < 3; i++){
        printf("%d:  %f\n",i+1,greatest[i].pastTransactionsSum);}
    return 1;
}


double averageOfSupplierMoney(supplierNode* tree ,int n){
    double res;
    if (!tree){
        return 0;
    }
    res =(tree->supplier.pastTransactionsSum)/n;
    res += averageOfSupplierMoney(tree->left,n);
    res += averageOfSupplierMoney(tree->right,n);
    return res;
}


/*prints every supplier's details in the list*/
void printSuppliers(supplierNode* tree){
    if (!tree){
        return ;
    }
    printSuppliers(tree->left);

    printf("    \nName:  %s\n",tree->supplier.name);
    printf("    Supplier's authorized dealer number:  %0.f\n",tree->supplier.id);
    printf("    Phone number:  %s\n",tree->supplier.phoneNumber);
    printf("    Number of past transaction with supplier  :%0.f\n",tree->supplier.pastTransactionsNumber);
    printf("    Sum of past transaction with supplier  :%0.f\n",tree->supplier.pastTransactionsSum);

    printSuppliers(tree->right);
}

