#include "Car.h"
#include <string.h>
#include "FillField.h"

/*creates new car binary search tree pointer*/
carBST* createCarTree(){
    carBST* newTree;
    newTree = ALLOC(carBST , 1);
    newTree->root = NULL;
    return newTree;
}

/*help function to call in addNewCar. orders tree by license number*/
carNode* appendCarToTree(carNode* tree, Car new_car){
    carNode* newNode;
    if(!tree){
        newNode = ALLOC(carNode ,1);
        newNode->car = new_car;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if(new_car.licenseNum == tree->car.licenseNum) {
        puts("License number already exists in Data Base.");
        return tree;
    }
    if(new_car.licenseNum < tree->car.licenseNum) /* Go left*/
        tree->left = appendCarToTree(tree->left, new_car);
    else{ /* Go right*/
        tree->right = appendCarToTree(tree->right, new_car);
    }
    return tree;
}

/*adds new car to the cars tree.*/
int addNewCar(carBST* tree) {

    Car new_car;
    double licenseNum;
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
    fillFieldDouble(&licenseNum, 7, 1);
    new_car.licenseNum = licenseNum;

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

    /*creates new node and puts it in the tree*/
    tree->root = appendCarToTree(tree->root, new_car);
    return 1;
}

/*free allocated memory*/
int freeCar(carNode* node){
    if(node) {
        FREE(node->car.manufacturer);
        FREE(node->car.color);
        FREE(node->car.model);
        FREE(node);
    }
    return 1;
}

int deepCopyCarFields(carNode* tree,Car follower){
    freeCar(tree);
    tree->car.manufacturer = copyField(follower.manufacturer);
    tree->car.color = copyField(follower.color);
    tree->car.model = copyField(follower.model);
    tree->car.licenseNum = follower.licenseNum;
    tree->car.manufactorYear = follower.manufactorYear;
    tree->car.velocity = follower.velocity;
    tree->car.onRoadSince = follower.onRoadSince;
    tree->car.currentPrice = follower.currentPrice;
    tree->car.priceFromSupplier = follower.priceFromSupplier;
    strcpy(tree->car.chassisNum, follower.chassisNum);

    return 1;
}
/*delete carNode by given license number*/
/*license parameter always starts as 0.*/
carNode* deleteCar(carNode* tree, double license,carBST* bst){
    carNode *temp, *follower, **followerAddr;
    double userInput = 0;
    if (!tree) {
        return NULL;
    }

    /*gets input from user*/
    if(license == 0){
        puts("please enter license num for the car you wish to delete:");
        fillFieldDouble(&userInput, 7, 1);
    }
    else{
        userInput = license;
    }
    /* searching wanted car in tree's children*/
    if(tree->car.licenseNum != userInput) {
        /* Go left*/
        if( license < (tree->car.licenseNum)) {
            tree->left = deleteCar(tree->left, userInput,bst);
        }
        /* Go right*/
        else {
            tree->right = deleteCar(tree->right, userInput,bst);
        }
    }
    else {

/* Option 1: tree is a leaf*/
        if (!(tree->left) && !(tree->right)) {
            freeCar(tree);
            bst->size -= 1;
            return NULL;
        }
/* Option 2: tree has only one child*/
        else if (!(tree->left)) {
            temp = tree->right;
            freeCar(tree);
            bst->size -= 1;
            return temp;
        } else if (!(tree->right)) {
            temp = tree->left;
            freeCar(tree);
            bst->size -= 1;
            return temp;
        }
/* Option 3: tree has 2 children*/
        else {
            follower = tree->right;
            followerAddr = &(tree->right);
            while (follower->left) {
                followerAddr = &(follower->left);
                follower = follower->left;
            }
            deepCopyCarFields(tree, follower->car);
            *followerAddr = deleteCar(follower, follower->car.licenseNum,bst);
        }
    }
    puts("supplier deleted from the data base");
    return tree;
}

/*free all the nodes from the tree. returns empty pointer*/
int deleteAllcarsNodes(carNode* tree){
    if(!tree){
        return 1;
    }
    /*free children first*/
    deleteAllcarsNodes(tree->left);
    deleteAllcarsNodes(tree->right);
    freeCar(tree);
    return 1;
}
int deleteAllCars(carBST* tree){
    deleteAllcarsNodes(tree->root);
    tree->root = NULL;
    tree->size = 0;
    return 1;
}


/*returns the number of cars in the list with a given capacity*/
/*cap parameter always starts as 0.*/
int carNumberWithGivenCapacity(carNode* root, int cap){
    int userInput, res = 0;

    if(!root){
        return 0;
    }

    /*gets input from user*/
    if(cap == 0) {
        puts("please enter a capacity for the check: ");
        fillFieldInt(&userInput, 4, 1, 1);
    }
    else{
        userInput = cap;
    }

    /*increasing result by 1*/
    if(root->car.velocity == userInput){
        res++;
    }

    /*sums results of children*/
    res += carNumberWithGivenCapacity(root->left, userInput);
    res += carNumberWithGivenCapacity(root->right, userInput);

    return res;
}








