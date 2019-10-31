#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "matroid.h"
#include "mtdparll.h"
#include "linkdlst.h"
#include <ctype.h>

/*
 * This function determines if a number is even
 * */
bool isEvenNumber(int pNumber){
    if(pNumber%2 == 0){
        return true;
    }else {
        return false;
    }
}

/*
 * This function determines if a string is palindrome
 * */
bool isPalindrome(char * pString){
    for (int left = 0, right = strlen(pString)-1; left < right; left++, right--) {
        if(pString[left] != pString[right]){
            return false;
        }
    }
    return true;
}

/*
 * This function determines if a character is an alphabetic letter
 * */
bool isAlphabetic(char pChar){
    if(isalpha(pChar)!=0){
        return true;
    }else {
        return false;
    }
}

int main(){
    //Test A
    //Firts matroid configuration
    list(int,S1);
    memset (&S1, 0, sizeof (S1));
    list(int,I1);
    memset (&I1, 0, sizeof (I1));
    list_push(S1,1);
    list_push(S1,2);
    list_push(S1,3);
    list_push(S1,4);
    Matroid matroid1 = {.S = S1,.I = I1,.function = isEvenNumber};

    //Second matroid configuration
    list(char*,S2);
    memset (&S2, 0, sizeof (S2));
    list(char*,I2);
    memset (&I2, 0, sizeof (I2));
    list_push(S2,"ama");
    list_push(S2,"hola");
    list_push(S2,"sometemos");
    list_push(S2,"mundo");
    list_push(S2,"reconocer");
    list_push(S2,"somos");
    Matroid matroid2 = {.S = S2,.I = I2,.function = isPalindrome};

    //Third matroid configuration
    list(char,S3);
    memset (&S3, 0, sizeof (S3));
    list(char,I3);
    memset (&I3, 0, sizeof (I3));
    list_push(S3,'a');
    list_push(S3,'b');
    list_push(S3,'3');
    list_push(S3,'c');
    list_push(S3,'4');
    list_push(S3,'r');
    Matroid matroid3 = {.S = S3,.I = I3,.function = isAlphabetic};

    //Matroids are added into an array
    Matroid matroidsA[] = {matroid1,matroid2,matroid3};
    int arraySizeA = sizeof (matroidsA)/sizeof (matroidsA[0]);
    testMatroids(matroidsA,arraySizeA); //Test the matroids

    printf("Results Point A\n");
    printf("\nSet I First Matroid\n");
    list_each(matroidsA[0].I,value){
        printf("%d\n",value);
    }

    printf("\nSet I Second Matroid\n");
    list_each(matroidsA[1].I,value){
        printf("%s\n",value);
    }

    printf("\nSet I Third Matroid\n");
    list_each(matroidsA[2].I,value){
        printf("%c\n",value);
    }

    //Test B

    //Firts matroid configuration
    list(int,S4);
    memset (&S4, 0, sizeof (S4));
    list(int,I4);
    memset (&I4, 0, sizeof (I4));
    list_push(S4,22);
    list_push(S4,49);
    list_push(S4,675);
    list_push(S4,90);
    list_push(S4,905);
    list_push(S4,20);
    Matroid matroid4 = {.S = S4,.I = I4,.function = isEvenNumber};

    //Second matroid configuration
    list(int,S5);
    memset (&S5, 0, sizeof (S5));
    list(int,I5);
    memset (&I5, 0, sizeof (I5));
    list_push(S5,56);
    list_push(S5,90);
    list_push(S5,107);
    list_push(S5,235);
    list_push(S5,22);
    list_push(S5,77);
    Matroid matroid5 = {.S = S5,.I = I5,.function = isEvenNumber};

    //Third matroid configuration
    list(int,S6);
    memset (&S6, 0, sizeof (S6));
    list(int,I6);
    memset (&I6, 0, sizeof (I6));
    list_push(S6,90);
    list_push(S6,22);
    list_push(S6,89);
    list_push(S6,40);
    Matroid matroid6 = {.S = S6,.I = I6,.function = isEvenNumber};

    //Fourth matroid configuration
    list(int,S7);
    memset (&S7, 0, sizeof (S7));
    list(int,I7);
    memset (&I7, 0, sizeof (I7));
    list_push(S7,113);
    list_push(S7,79);
    list_push(S7,22);
    list_push(S7,31);
    list_push(S7,90);
    Matroid matroid7 = {.S = S7,.I = I7,.function = isEvenNumber};

    //Fifth matroid configuration
    list(int,S8);
    memset (&S8, 0, sizeof (S8));
    list(int,I8);
    memset (&I8, 0, sizeof (I8));
    list_push(S8,90);
    list_push(S8,541);
    list_push(S8,367);
    list_push(S8,123);
    list_push(S8,2);
    list_push(S8,205);
    list_push(S8,22);
    Matroid matroid8 = {.S = S8,.I = I8,.function = isEvenNumber};

    //Matroids are added into an array
    Matroid matroidsB[] = {matroid4,matroid5,matroid6,matroid7,matroid8};
    int arraySizeB = sizeof (matroidsB)/sizeof (matroidsB[0]);
    testMatroids(matroidsB,arraySizeB);
    Matroid result = getIntersection(matroidsB,arraySizeB); //A matroid with a set of the intersections

    printf("\nResults Point B\n\n");
    list_each(result.I,value){
        printf("%d\n",value);
    }
}
