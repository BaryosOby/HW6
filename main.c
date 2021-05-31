#include "menu.h"

int main(){

    carList car_list;
    supplierList supplierList;
    clientList clientList;

    createCarList(&car_list);
    createSupplierList(&supplierList);
    createClientList(&clientList);
    menu(&car_list,&supplierList,&clientList);

    return 0;
}
