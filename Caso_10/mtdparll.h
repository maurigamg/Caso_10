#ifndef MTDPARLL_H
#define MTDPARLL_H

#include <omp.h>
#include "matroid.h"
#include <linkdlst.h>

Matroid evaluateMatroid(Matroid pMatroid){
    #pragma omp parallel
    #pragma omp for
    list_each(pMatroid.S,value){
        if(pMatroid.function(value)){
            list_push(pMatroid.I,value);
        }
    }
    return pMatroid;
}

void testMatroids(Matroid pMatroids[],int pSize){
    #pragma omp parallel
    #pragma omp for
    for (int numMatroid = 0; numMatroid<pSize; numMatroid++) {
        pMatroids[numMatroid] = evaluateMatroid(pMatroids[numMatroid]);
    }
}

Matroid getIntersection(Matroid pMatroids[],int pSize){
    Matroid result;
    if(pSize>0){
        #pragma omp parallel
        #pragma omp for
        list(typeof (list_back(pMatroids[0].I)),I);
        memset (&I, 0, sizeof (I));
        list_each(pMatroids[0].I,value){
            list_push(I,value);
        }
        for (int numMatroid = 1; numMatroid < pSize; numMatroid++) {
            #pragma omp for
            list_each(I,value){
                #pragma omp for
                bool isValue = false;
                list_each(pMatroids[numMatroid].I,value2){
                    if((int)value==(int)value2){
                        isValue = true;
                        break;
                    }
                }
                if(!isValue){
                    list_remove(I,value);
                }
            }
        }
        result.I = I;
        return result;
    }else {
        return result;
    }
}

#endif // MTDPARLL_H
