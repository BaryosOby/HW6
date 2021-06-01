#include "menu.h"
#include "Car.h"

int main(){

    int d;
    carBST* tree  = createCarTree();
    addNewCar(tree);
    addNewCar(tree);
    addNewCar(tree);
    /*d = carNumberWithGivenCapacity(tree->root, 0);
    printf("%d",d);*/
    tree->root = deleteCar(tree->root, 0);
    deleteAllCars(tree->root);
    return 0;
}
