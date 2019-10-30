#ifndef MATROID_H
#define MATROID_H

#include <stdbool.h>
#include "linkdlst.h"

typedef void* DataType;

typedef struct Matroid{

    list(DataType,S);
    list(DataType,I);
    bool (*function)();
}Matroid;

#endif // MATROID_H
