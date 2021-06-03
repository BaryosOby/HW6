#include "menu.h"
#include "Car.h"

int main(){
    clientBST *clientTree;
    carBST * carTree;
    supplierBST * supplierTree;

    carTree = createCarTree();
    clientTree = createClientTree();
    supplierTree = createSupplierTree();


    menu(carTree,supplierTree,clientTree);
    /*addNewSupplier(supplierTree);
    addNewSupplier(supplierTree);
    supplierTree->root=deleteSupplier(supplierTree->root,0,supplierTree);
    deleteAllSuppliers(supplierTree);

    addNewClient(clientTree);
    addNewClient(clientTree);
    clientTree->root = deleteClient(clientTree->root,0);
    deleteAllClients(clientTree);

    addNewCar(carTree);
    addNewCar(carTree);
    carTree->root = deleteCar(carTree->root,0);
    deleteAllCars(carTree);*/



    return 0;
}
