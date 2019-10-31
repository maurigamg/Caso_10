#ifndef MATROID_H
#define MATROID_H

#include <stdbool.h>
#include "linkdlst.h"

typedef void* dataType;

typedef struct Matroid{

    list(dataType,S);
    list(dataType,I);
    bool (*function)();
}Matroid;

#endif // MATROID_H
