#include "menu.h"
#include "Car.h"

int main(){

    double d;
   /* carBST * car_tree;
    car_tree = createCarTree();
    addNewCar(car_tree);
    addNewCar(car_tree);
    addNewCar(car_tree);
    d = carNumberWithGivenCapacity(car_tree->root, 0);
    deleteCar(car_tree->root, 2222222);
    deleteAllCars(car_tree);*/

    supplierBST * sup_tree;
    sup_tree = createSupplierTree();
    addNewSupplier(sup_tree);
    addNewSupplier(sup_tree);
    addNewSupplier(sup_tree);
    d = averageOfSupplierMoney(sup_tree->root, sup_tree->size);
    threeGreatestSuppliers(*sup_tree);
    printSuppliers(sup_tree->root);
    deleteSupplier(sup_tree->root, 2222222222,sup_tree);
    printSuppliers(sup_tree->root);
    deleteAllSuppliers(sup_tree);


    return 0;
}
