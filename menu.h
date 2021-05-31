#include "DataBase.h"

#ifndef HW3_MENU_H
#define HW3_MENU_H

#define DEFAULTS Car c1 = {"1111111", "11111", "siat", "ibiza", "white", 2007, 2008, 15000, 10000, 1600};\
Car c2 = {"1231231", "12312", "reno", "megan", "white", 2007, 2008, 15000, 10000, 1600};\
Car c3 = {"2233445", "22334", "fiat", "uno", "blue",2005, 2007, 140000, 130000, 1600};\
Supplier s1 = {1111111111,"omri","0509999999",55555,1111111111};\
Supplier s2 = {2222222222,"shivi","0509999999",44444,2222222222};\
Supplier s3 = {5555555555,"moshe","0509999999",33333,5555555555};\
Client cl1= {"shivi", "cohen", "101010101", "1231231", "11/03/2010", "11:03", 100};\
Client cl2= {"omri", "baryos", "202020202", "2233445", "22/10/2020", "22:10", 120};\
Client cl3= {"yosi", "cohen", "1234567890", "1111111", "22/10/2020", "22:10", 120};

#define CARTEST createCarList(&car_list);\
appendCarToList(&car_list.head, c1);\
appendCarToList(&car_list.head, c2);\
appendCarToList(&car_list.head, c3);

#define SUPPLIERTEST createSupplierList(&supplierList);\
appendSupplierToList(&supplierList.head, s1);\
appendSupplierToList(&supplierList.head, s2);\
appendSupplierToList(&supplierList.head, s3);


#define CLIENTTEST createClientList(&cl_list);\
cl_list.head = appendClientToList(&cl_list.head, cl1);\
cl_list.head = appendClientToList(&cl_list.head, cl2);\
cl_list.head = appendClientToList(&cl_list.head, cl3);

void menu(carList* carList , supplierList* supplierList, clientList* clientList);

/*helpers for menu*/
void carSwitch(int carChoose,carList* carList);
void clientSwitch(int clientChoose,clientList* clientList);
void supplierSwitch(int supplierChoose,supplierList * supplierList);


#endif
