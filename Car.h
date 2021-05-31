#ifndef CAR_H
#define CAR_H

typedef struct{
    double licenseNum;
    char chassisNum[6];
    char* manufacturer;
    char* model;
    char* color;
    int manufactorYear;
    int onRoadSince;
    double priceFromSupplier;
    double currentPrice;
    int velocity;
}Car;

typedef struct carNode_t{
    Car car;
    struct carNode_t* left;
    struct carNode_t* right;
}carNode;

typedef struct {
    carNode* root;
} carBST;


/*creates empty carNode*/
carBST* createCarTree();

/*adds new car to the cars list[index]. return 1 if succeed, 0 if failed*/
int addNewCar(carBST* tree);

/*help function to call in addNewCar*/
int appendCarToList(carNode ** head, Car newCar);


/*gets license number of a car and delete it from the list. returns 1 if succeed, 0 if failed.*/
carNode* deleteCar(carNode* tree, double license);

/*deletes all the cars from the list. returns 1 if succeed, 0 if failed.*/
int deleteAllCars(carNode* tree);

/*returns the number of cars from the list with a given capacity*/
int carNumberWithGivenCapacity(carNode* root, int cap);



#endif
