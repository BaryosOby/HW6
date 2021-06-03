#include "DataBase.h"


#ifndef HW3_MENU_H
#define HW3_MENU_H

#define DEFAULTS \
Car c1 = {1111111 , "11111", "siat", "ibiza", "white", 2007, 2008, 15000, 10000, 1600};\
Car c2 = {1231231 , "12312", "reno", "megan", "white", 2007, 2008, 15000, 10000, 1600};\
Supplier s1 = {1111111111 ,"omri","0509999999",55555,1111111111};                      \
Supplier s2 = {1111111112 ,"omri","0509999999",44444,1111111112};                      \
Client cl1= {"shivi", "cohen", 101010101, 1111111, "11/03/2010", "11:03", 100};\
Client cl3= {"dan", "cohen", 101010103, 1231231, "11/03/2010", "11:03", 100};\
Client cl2= {"omri", "cohen", 101010104, 1231230, "11/04/2010", "11:03", 100};


#define CARTEST car_tree = createCarTree();\
car_tree->root =appendCarToTree(car_tree->root, c1);\
car_tree->root=appendCarToTree(car_tree->root, c2);


#define SUPPLIERTEST createSupplierList(&supplierList);\
appendSupplierToList(&supplierList.head, s1);\
appendSupplierToList(&supplierList.head, s2);\
appendSupplierToList(&supplierList.head, s3);


#define CLIENTTEST     c_tree = createClientTree();\
c_tree->root = appendClientToTree(c_tree->root, cl1);\
c_tree->root = appendClientToTree(c_tree->root, cl2);\
c_tree->root = appendClientToTree(c_tree->root, cl3);
void menu(carBST * carTree , supplierBST * supplierTree, clientBST * clientTree);

/*helpers for menu*/
void carSwitch(int carChoose,carBST * carTree,int  temp);
void clientSwitch(int clientChoose, clientBST * clientTree,carNode* carRoot ,int  temp);
void supplierSwitch(int supplierChoose,supplierBST * supplierTree,int  temp);

#endif
