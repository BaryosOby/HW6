#include "menu.h"
#include "Car.h"

int main(){
    clientBST *c_tree;
    carBST * car_tree;
    supplierBST * sup_tree;

    car_tree = createCarTree();
    c_tree = createClientTree();
    sup_tree = createSupplierTree();

    addNewSupplier(sup_tree);
    addNewSupplier(sup_tree);
    sup_tree->root=deleteSupplier(sup_tree->root,0,sup_tree);
    deleteAllSuppliers(sup_tree);

   /* addNewClient(c_tree);
    addNewClient(c_tree);
    c_tree->root = deleteClient(c_tree->root,0);
    deleteAllClients(c_tree);

    addNewCar(car_tree);
    addNewCar(car_tree);
    car_tree->root = deleteCar(car_tree->root,0);
    deleteAllCars(car_tree);*/



    return 0;
}
