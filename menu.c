#include "menu.h"
#include <stdio.h>

void menu(carBST * carTREE , supplierBST * supplierBst, clientBST * clientBst){
    int choose,carChoose,clientChoose,supplierChoose,exitChoose,threeGreatestChoose, cap,man;
    puts("Welcome to CarsOrganizer \n(BETA version)");
    puts("initializing data base \ncreating cars list.....\ndone!\ncreating suppliers list.....\ndone!\ncreating clients list.....\ndone!\n");
    while(1){
        puts("\nplease enter your choose:\n"
             "      1.Cars menu\n"
             "      2.clients menu\n"
             "      3.supplier menu\n"
             "      4.get how many cars there are with given engine velocity\n"
             "      5.get how many client's there are with car from given car year\n"
             "      6.get ID number of the top 3 suppliers\n"
             "      7.average sum of deals with suppliers\n"
             "      8.print all clients with given rent date\n"
             "      9.print all suppliers details\n"
             "      0.exit.\n"
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
                carSwitch(carChoose, carTREE);
                break;

            case 2:
                puts("please enter your choose\n"
                     "      1.add new client\n"
                     "      2.delete client\n"
                     "      3.delete all clients\n"
                     "      any other digit to return\n");
                fillFieldInt(&clientChoose,1,1,1);
                clientSwitch(clientChoose, clientBst);
                break;

            case 3:
                puts("please enter your choose\n"
                     "      1.add new supplier\n"
                     "      2.delete supplier\n"
                     "      3.delete all suppliers\n"
                     "      any other digit to return\n");
                fillFieldInt(&supplierChoose,1,1,1);
                supplierSwitch(supplierChoose, supplierBst);
                break;

            case 4:
               cap = carNumberWithGivenCapacity(carTREE->root,0);
                if (cap != 0){
                    printf("there are %d cars with given capacity",cap );
                } else
                    puts("there are no cars with give capacity");
                break;

            case 5:
                man = clientNumberWithGivenCarYear(carTREE->root, clientBst->root, 0);
                if(man != 0){
                    printf("there are %d clients who rented a car in given manufacturing year ",man);
                } else{
                    puts("there are no clients who rented a car in given manufacturing year ");
                }
                break;

                break;
            case 6:
              threeGreatestSuppliers(*supplierBst);
                break;
            case 7:
                printf("average sum of deals with suppliers is %f: ",averageOfSupplierMoney(supplierBst->root,supplierBst->size));
                break;

            case 8:
                  printClientCarsForGivenRentDate(clientBst->root);
                  break;

            case 9:
                   printSuppliers(supplierBst->head);
                   break;

            case 0:
                puts("Are you sure?\n"
                     "1.yes\n"
                     "2.no\n"
                     "any other choose for return")   ;
                fillFieldInt(&exitChoose,1,1,1);
                if (exitChoose==1){
                    deleteAllSuppliers(&(supplierBst->head));
                    FREE(supplierBst->head);
                    deleteAllClients(&clientBst->head);
                    FREE(clientBst->head);
                    deleteAllCars(&carTREE->head);
                    FREE(carTREE->head);
                    puts("checking for data base status....");
                    puts("cleaning cars list.....\ndone!");
                    puts("cleaning suppliers list.....\ndone!");
                    puts("cleaning clients list.....\ndone!");
                    puts("you good to go!\nByeBye");
                    check_for_exit();   /*TODO delete before compilation*/
                    exit(0);}
                else{break;}
            default:
                continue;
        }
    }
}
void carSwitch(int carChoose,carBST*  carTree) {
    switch (carChoose) {
        case 1:
            if (addNewCar(carTree) == 1){
                puts("car added to tree!\n");
            }
            break;
        case 2:
            if (!carTree->root){
                puts("car tree is empty");
                break;
            }
            if (deleteCar(carTree->root, 0) == 1){/*TODO what if license not in the list*/
                puts("car deleted from the tree!\n");
            }
            else{
                puts("car license not found");
            }
            break;
        case 3:
            if (deleteAllCars(carTree)){
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
