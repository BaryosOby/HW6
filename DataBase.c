#include "DataBase.h"
#include <string.h>
#include <stdio.h>

/*returns manufacturing year of a car by a given license number*/
int getCarYearByLicense(carNode * tree ,double license){
    if(!tree){
        return 0;
    }
    if(tree->car.licenseNum == license){
        return tree->car.manufactorYear;
    }
    if(tree->car.licenseNum > license){
        return getCarYearByLicense(tree->left , license);
    }
    return getCarYearByLicense(tree->right , license);
}


int clientNumberWithGivenCarYear(carNode * car_tree, clientNode * client_tree, int year) {
    int counter = 0, userYearChoice;
    double license;

    if((!car_tree) || (!client_tree)){
        return 0;
    }

    if(year == 0) {
        puts("please enter a year to check: ");
        fillFieldInt(&userYearChoice, 4, 1, 5);
    }
    else{
        userYearChoice = year;
    }

    if(getCarYearByLicense(car_tree, license) == userYearChoice){
        counter++;
    }

    return counter + clientNumberWithGivenCarYear(car_tree, client_tree->left, userYearChoice)  + clientNumberWithGivenCarYear(car_tree, client_tree->left, userYearChoice);
}




