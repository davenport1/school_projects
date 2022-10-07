/**
 * @file sort.c
 * @author Matthew Davenport
 * @brief quicksort algorithm implemented in C
 * @date 2022-04-12
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define high 8                  //length of array
int numbers[high];              //initialize array 

/* reads array from user input */
void readarray(void) {
    printf("Enter integers for array to be sorted\n");
    for(int i = 0; i < high; i++) {
        scanf("%d", &numbers[i]);
    }
}

/* prints array out to console */
void writearray(void) {
    for(int i = 0; i < high; i++) {
        printf("%d\n", numbers[i]);
    }
}

/* exchanges two integers at their adresses, passed 2 pointers 
    to simulate pass by reference */
void exchange(int *a, int *b) {
    int x;                      // temp variable for swap
    x = *a;
    *a = *b;
    *b = x;
}

/* exchanges elements on either side of the array
    based on the values compared with each other until indexes meet */
int partition(int *a, int y, int z) {
    int i, j ,x;            //i / j will be low/high in the array 
    x = a[y];               //assign x to value at low index
    i = y;
    j = z;
    while(i < j) {          //while indexes are still different
        while (a[j] > x) {  //find first value at high index thats lower
            j--;
        }
        while (a[i] < x) { //find first value at low index thats greater
            i++;
        }   
        if(i < j) {        //exchange the two values
            exchange(&a[i], &a[j]);
        }
        
    }
    return j;
}

/* recursively partition at increasing indexes until array has been sorted */
void quicksort(int *a, int m, int n) {
    int i;
    if(n > m) {
        i = partition(a, m, n); 
        quicksort(a, m, i);
        quicksort(a, i + 1, n);
    }
}





int main(void) {
    int *a = numbers; //pointer to array a 
    readarray();
    quicksort(a, 0, high - 1);
    writearray();

    return 0;
}