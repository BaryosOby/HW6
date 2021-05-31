#ifndef CAR_H
#define CAR_H

typedef struct{
    char licenseNum[8];
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
    struct carNode_t* next;
}carNode;

typedef struct carList{
    carNode* head;
}carList;


/*creates new list of cars*/
int createCarList();

/*adds new car to the cars list[index]. return 1 if succeed, 0 if failed*/
int addNewCar(carNode ** head);

/*help function to call in addNewCar*/
int appendCarToList(carNode ** head, Car newCar);


/*gets license number of a car and delete it from the list. returns 1 if succeed, 0 if failed.*/
int deleteCar(carNode** head, const char* licenseNum);

/*deletes all the cars from the list. returns 1 if succeed, 0 if failed.*/
int deleteAllCars(carNode** head);

/*returns the number of cars from the list with a given capacity*/
int carNumberWithGivenCapacity(carNode** head);

int carNumberWithGivenCapacity_REC(carNode** head, int cap);

Car createDefultCar();
int inverseCarList(carNode** head);


#endif
