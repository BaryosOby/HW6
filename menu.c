#include "menu.h"
#include <stdio.h>
/*
void menu(carList* carList , supplierList* supplierList, clientList* clientList){
    int choose,carChoose,clientChoose,supplierChoose,exitChoose,threeGreatestChoose,carCapChoose, cap,man;
    puts("Welcome to CarsOrganizer \n(BETA version)");
    puts("initializing data base \ncreating cars list.....\ndone!\ncreating suppliers list.....\ndone!\ncreating clients list.....\ndone!\n");
    while(1){
        puts("\nplease enter your choose:\n"
             "      1.add or delete a Car\n"
             "      2.add or delete a client\n"
             "      3.add or delete a supplier\n"
             "      4.get how many cars there are with given engine velocity\n"
             "      5.get how many client's there are with car from given car year\n"
             "      6.get ID number of the top 3 suppliers\n"
             "      7.inverse car list");
#ifdef DAVIS
        puts("      8.print all clients with given rent date\n"
                 "      9.print all suppliers details");
#endif
        puts("      0.exit.\n"
             "your choose: ");

        fillFieldInt(&choose,1,1,1);
        switch (choose) {
            case 1:
                puts("please enter your choose\n"
                     "      1.add new car\n"
                     "      2.delete Car\n"
                     "      3.delete all cars\n"
                     "      any other digit to return\n");
                fillFieldInt(&carChoose,1,1,1);
                carSwitch(carChoose,carList);
                break;

            case 2:
                puts("please enter your choose\n"
                     "      1.add new client\n"
                     "      2.delete client\n"
                     "      3.delete all clients\n"
                     "      any other digit to return\n");
                fillFieldInt(&clientChoose,1,1,1);
                clientSwitch(clientChoose,clientList);
                break;

            case 3:
                puts("please enter your choose\n"
                     "      1.add new supplier\n"
                     "      2.delete supplier\n"
                     "      3.delete all suppliers\n"
                     "      any other digit to return\n");
                fillFieldInt(&supplierChoose,1,1,1);
                supplierSwitch(supplierChoose,supplierList);
                break;

            case 4:
                puts("what kind of algorithm you wish to use?\n    1.iterative\n    2.recursive");
                fillFieldInt(&carCapChoose,1,1,1);

                if (carCapChoose==1){
                    cap = carNumberWithGivenCapacity(&(carList->head));
                }
                if (carCapChoose ==2){
                    cap = carNumberWithGivenCapacity_REC(&(carList->head), 0);
                }
                if (cap != 0){
                    printf("there are %d cars with given capacity",cap );
                } else
                    puts("there are no cars with give capacity");
                break;

            case 5:
                man = clientNumberWithGivenCarYear(carList->head,clientList->head, 0);
                if(man != 0){
                    printf("there are %d clients who rented a car in given manufacturing year ",man);
                } else{
                    puts("there are no clients who rented a car in given manufacturing year ");
                }
                break;

                break;
            case 6:
                puts("what kind of algorithm you wish to use?\n    1.iterative\n    2.recursive");
                fillFieldInt(&threeGreatestChoose,1,1,1);

                if (threeGreatestChoose==1){
                    threeGreatestSuppliers(supplierList->head);
                }
                if (threeGreatestChoose ==2){
                    threeGreatestSupplier_rec(supplierList->head,NULL);
                }
                break;
            case 7:
                inverseCarList(&(carList->head));
                break;

            case 8:
                  if(!printClientCarsForGivenRentDate(clientBST->root, NULL)){
                    puts("there are no clients who rented a car in this date...");
                  }
                  break;

            case 9:
                   printSuppliers(supplierList->head);
                   break;

            case 0:
                puts("Are you sure?\n"
                     "1.yes\n"
                     "2.no\n"
                     "any other choose for return")   ;
                fillFieldInt(&exitChoose,1,1,1);
                if (exitChoose==1){
                    deleteAllSuppliers(&(supplierList->head));
                    FREE(supplierList->head);
                    deleteAllClients(&clientList->head);
                    FREE(clientList->head);
                    deleteAllCars(&carList->head);
                    FREE(carList->head);
                    puts("checking for data base status....");
                    puts("cleaning cars list.....\ndone!");
                    puts("cleaning suppliers list.....\ndone!");
                    puts("cleaning clients list.....\ndone!");
                    puts("you good to go!\nByeBye");
                    check_for_exit();   /*delete before compilation
                    exit(0);}
                else{break;}
            default:
                continue;
        }
    }
}

void carSwitch(int carChoose,carList* carList) {
    switch (carChoose) {
        case 1:
            if (addNewCar(&carList->head) == 1){
                puts("car added to list!\n");
            }
            break;
        case 2:
            if (!carList->head){
                puts("car list is empty");
                break;
            }
            if (deleteCar(&(carList->head),NULL) == 1){
                puts("car deleted from list!\n");
            }
            else{
                puts("car license not found");
            }
            break;
        case 3:
            if (deleteAllCars(&(carList->head))){
                puts("deleting.....\n");
                puts("all cars deleted!");
            }
            break;

        default:
            break;
    }
}


void clientSwitch(int clientChoose,clientList* clientList) {
    switch (clientChoose) {
        case 1:
            if (addNewClient(&clientList->head) == 1){
                puts("client added to list!\n");
            }
            break;
        case 2:
            if (!clientList->head){
                puts("client list is empty");
                break;
            }
            if (deleteClient(&(clientList->head),NULL) == 1){
                puts("client deleted from list!\n");
            }
            else{
                puts("client didn't found");
            }
            break;
        case 3:
            if (deleteAllClients(&(clientList->head))){
                puts("deleting.....\n");
                puts("all clients deleted!");
            }
            break;

        default:
            break;
    }
}



void supplierSwitch(int supplierChoose, supplierList * supplierList) {
    switch (supplierChoose) {
        case 1:
            if (addNewSupplier(&supplierList->head) == 1){
                puts("supplier added to list!\n");
            }
            break;
        case 2:
            if (!supplierList->head){
                puts("supplier list is empty");
                break;}
            if (deleteSupplier(&(supplierList->head),0) == 1){
                puts("supplier deleted from list!\n");
            }
            else{
                puts("supplier's id didn't found");
            }
            break;
        case 3:
            if (deleteAllSuppliers(&(supplierList->head))){
                puts("deleting.....\n");
                puts("all suppliers deleted!");
            }
            break;

        default:
            break;
    }
}

*/
