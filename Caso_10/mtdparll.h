#ifndef MTDPARLL_H
#define MTDPARLL_H

#include <omp.h>
#include "matroid.h"
#include <linkdlst.h>

/*
 * This function evaluates each element of the set S of a matroid with the function of the matroid
 * */
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

/*
 * This function passes each matroid to evaluation state
 * */
void testMatroids(Matroid pMatroids[],int pSize){
    #pragma omp parallel
    #pragma omp for
    for (int numMatroid = 0; numMatroid<pSize; numMatroid++) {
        pMatroids[numMatroid] = evaluateMatroid(pMatroids[numMatroid]);
    }
}

/*
 * This function determines the intersection between sets in parallel
 * */
Matroid getIntersection(Matroid pMatroids[],int pSize){
    Matroid result;
    if(pSize>0){

        list(typeof (list_back(pMatroids[0].I)),I); //Declare a list of the type of the elements of the first matroid
        memset (&I, 0, sizeof (I));
        list_each(pMatroids[0].I,value){ //The values of the set S of the first matroid are copied in the list
            list_push(I,value);
        }
        #pragma omp parallel
        #pragma omp for
        for (int numMatroid = 1; numMatroid < pSize; numMatroid++) {
            #pragma omp for
            list_each(I,element){
                bool isValue = false; //flag to know if the element is present in the set I of the matroid
                list_each(pMatroids[numMatroid].I,element2){
                    if(element==element2){ //Compare the elements
                        isValue = true;
                        break;
                    }
                }
                if(!isValue){ //In case the element doesn't exist is necessary to delete of the set
                    list_remove(I,element);
                }
            }
        }
        result.I = I; //The list is added like the set I of an matroid
        return result; //The matroid is returned
    }else {
        return result;
    }
}

#endif // MTDPARLL_H
