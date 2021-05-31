#include "DataBase.h"
#include <string.h>
#include <stdio.h>

/*returns manufacturing year of a car by a given license number
int getCarYearByLicense(carNode * head ,const char* license){


    if(!head){
        return 0;
    } if(strcmp(head->car.licenseNum, license) == 0){
        return head->car.manufactorYear;
    }
    return getCarYearByLicense(head->next, license);
}


int clientNumberWithGivenCarYear(carNode * car_head, clientNode * client_head, int year) {


    int counter = 0, userYearChoice;
    char license[8];


    if((!car_head) || (!client_head)){
        return 0;
    }


    if(year == 0) {
        puts("please enter a year to check: ");
        fillFieldInt(&userYearChoice, 4, 1, 5);
    }
    else{
        userYearChoice = year;
    }


    strcpy(license, client_head->client.rentedCarLicense);
    if(getCarYearByLicense(car_head, license) == userYearChoice){
        counter++;
    }

    return counter + clientNumberWithGivenCarYear(car_head, client_head->next, userYearChoice);
}*/




