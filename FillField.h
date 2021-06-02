#ifndef HW3_FILLFIELD_H
#define HW3_FILLFIELD_H
#include "Validation.h"
#include "matam.h"

int fillFieldStr(char* str, int size, int charType,int fixed);
int fillFieldInt(int*  field, int size,int fixed,int charType);
int fillFieldDouble(double * field, int size,int fixed);
char* copyField(char* source);
char* fillFiledStrDynamic(int charType);





#endif
