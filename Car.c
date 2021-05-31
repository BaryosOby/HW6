#include "Car.h"
#include <string.h>
#include "FillField.h"

/*creates new carList object*/
int createCarList(carList* list){
    carNode* new = ALLOC(carNode,1);
    new = NULL;
    list->head = new;
    return 1;
}

/*help function to call in addNewCar*/
int appendCarToList(carNode ** head, Car newCar){
    carNode* newNode = ALLOC(carNode,1), *curr;

    /*initializing new node's fields. */
    newNode->car = newCar;
    newNode->next = NULL;

    /*true when list is empty, or new car's year is earlier then first node's*/
    if ((*head == NULL) || (*head)->car.manufactorYear >= newCar.manufactorYear){
        newNode->next = *head;
        *head = newNode;
        return 1;
    }

    /*finds the first bigger car year*/
    curr = *head;
    while((curr->next) && (curr->next->car.manufactorYear < newCar.manufactorYear)){
        curr = curr->next;
    }

    /*inserting the new node after the current one.*/
    newNode->next = curr->next;
    curr->next = newNode;
    return 1;
}

/*adds new car to the cars list in ascending order of manufactoring year.*/
int addNewCar(carNode ** head) {

    Car new_car;
    char licenseNum[8];
    char chassisNum[6];
    int manufactorYear;
    int onRoadSince;
    double priceFromSupplier;
    double currentPrice;
    int velocity;

    printf("please enter details for your new car:\n");

    /*setting user inputs to fields
     * checking input validation*/
    puts("please enter licence number (7 digits):");
    fillFieldStr(licenseNum, 7, 1, 1);
    strcpy(new_car.licenseNum, licenseNum);

    puts("please enter chassis number (5 digits): ");
    fillFieldStr(chassisNum, 5, 1, 1);
    strcpy(new_car.chassisNum, chassisNum);

    puts("please enter manufacturer name: ");
    new_car.manufacturer = fillFiledStrDynamic(2);

    puts("please enter model name: ");
    new_car.model = fillFiledStrDynamic(2);

    puts("please enter car's color: ");
    new_car.color = fillFiledStrDynamic(2);

    puts("please enter manufacturing year (4 digits): ");
    fillFieldInt(&manufactorYear, 4, 1,5);
    new_car.manufactorYear = manufactorYear;

    puts("please enter ascension year (4 digits): ");
    fillFieldInt(&onRoadSince, 4, 1,5);
    new_car.onRoadSince = onRoadSince;

    puts("please enter price from supplier (7 digits max): ");
    fillFieldDouble(&priceFromSupplier, 7, 0);
    new_car.priceFromSupplier = priceFromSupplier;

    puts("please enter current price (7 digits max): ");
    fillFieldDouble(&currentPrice, 7, 0);
    new_car.currentPrice = currentPrice;

    puts("please enter engine's velocity (4 digits): ");
    fillFieldInt(&velocity, 4, 1,1);
    new_car.velocity = velocity;

    /*creates new node and puts it in the list*/
    appendCarToList(head, new_car);
    return 1;
}

/*free allocated memory*/
int freeCar(carNode* node){
    FREE(node->car.manufacturer);
    FREE(node->car.color);
    FREE(node->car.model);
    FREE(node);
    return 1;
}

/*gets license number of a car and delete it from the list. returns 1 if succeed, -1 if failed.*/
/*licenseNum parameter always starts as NULL.*/
int deleteCar(carNode ** head, const char* licenseNum){
    carNode* temp;
    char userInput[8];
    /*base case - empty pointer*/
    if(*head == NULL){
        return -1;
    }

    /*gets input from user*/
    if(!licenseNum){
        puts("please enter a license number to delete: ");
        fillFieldStr(userInput, 7, 1, 1);
    }
    else{
        strcpy(userInput, licenseNum);
    }

    /*true for first car*/
    if(strcmp((*head)->car.licenseNum, userInput)== 0) {
        temp = (*head);
        *head = (*head)->next;
        freeCar(temp);
        return 1;
    }


    if (((*head)->next)&&(strcmp((*head)->next->car.licenseNum, userInput)==0)){
        /*linking current node to one after the required to delete.*/
        temp =(*head)->next;
        (*head)->next = (*head)->next->next;
        freeCar(temp);
        return 1;
    }

    return deleteCar(&((*head)->next), userInput);
}


int deleteAllCars(carNode** head){

    /*recursive function. saves the next node's address and free the current one.*/
    carNode * temp;
    /*base case - empty pointer*/
    if (!*head){
        return 1;
    }
    /*saves the adress of the next node and frees the current one*/
    temp = (*head)->next;
    freeCar(*head);
    deleteAllCars(&temp);
    *head = NULL;
    return 1;
}

/*returns the number of cars from the list with a given capacity*/
int carNumberWithGivenCapacity(carNode** head){
    int userInput, res = 0;
    carNode * curr;
    /*gets input from user*/
    puts("please enter a capacity for the check: ");
    fillFieldInt(&userInput, 4, 1, 1);
    curr = *head;
    /*compare every car velocity in the list and increasing the result by 1*/
    while (curr){
        if(curr->car.velocity == userInput){
            res++;
        }
        curr = curr->next;
    }

    return res;
}

/*returns the number of cars from the list with a given capacity, recursively*/
/*cap parameter always starts as 0.*/
int carNumberWithGivenCapacity_REC(carNode** head, int cap){

    /*every call, the function return 1 if car is with the given capacity, else 0.
     * final result is the sum of all calls.*/
    int userInput = 0, res = 0;

    /*base case - empty pointer*/
    if(*head == NULL){
        return 0;
    }
    /*gets input from user*/
    if(cap == 0){
        puts("please enter a capacity for the check: ");
        fillFieldInt(&userInput,4,1,1);
    }
    else{
        userInput = cap;
    }

    if((*head)->car.velocity == userInput){
        res = 1;
    }
    /*sums the results of every comparison in the list*/
    return  res + carNumberWithGivenCapacity_REC(&((*head)->next), userInput);
}

/*inverse the sorting order of car list*/
int inverseCarList(carNode** head){

    carNode * last = NULL, *curr = *head, *next = NULL;
    while (curr){

        next = curr->next;
        /*pointing the current node's next on the previous node*/
        curr->next = last;
        /*defines the current node as the previous*/
        last = curr;
        /*define next node as the current*/
        curr = next;
    }
    *head = last;

    return 1;
}



