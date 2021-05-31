#include "DataBase.h"
#include <string.h>
#include <stdio.h>

/*returns manufacturing year of a car by a given license number*/
int getCarYearByLicense(carNode * head ,const char* license){

    /*base case - empty pointer*/
    if(!head){
        return 0;
    }
    /*returns the year*/
    if(strcmp(head->car.licenseNum, license) == 0){
        return head->car.manufactorYear;
    }
    return getCarYearByLicense(head->next, license);
}

/*returns the number of clients that rents a car with a given manufacturing year.*/
/*year parameter starts always as 0 */
int clientNumberWithGivenCarYear(carNode * car_head, clientNode * client_head, int year) {

    /*recursive function.
     * for every client in the list, it checks every car in car list and compare its license number to the client's car.*/
    int counter = 0, userYearChoice;
    char license[8];

    /*car list or client node is empty*/
    if((!car_head) || (!client_head)){
        return 0;
    }

    /*gets input from user*/
    if(year == 0) {
        puts("please enter a year to check: ");
        fillFieldInt(&userYearChoice, 4, 1, 5);
    }
    else{
        userYearChoice = year;
    }

    /*if true, increasing the counter by 1*/
    strcpy(license, client_head->client.rentedCarLicense);
    if(getCarYearByLicense(car_head, license) == userYearChoice){
        counter++;
    }
    /*sums all the results of the clients*/
    return counter + clientNumberWithGivenCarYear(car_head, client_head->next, userYearChoice);
}




