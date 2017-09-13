/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n){

    if(n<=0){
        return false;
    }
    int mid;
    if (n%2 == 0){
        mid = n/2;
        mid--;
    } else {
        mid = n-1;
        mid /=2;
    }
    if (value == values[mid]){
        return true;
    } else{
        if (value < values[mid] ){
            return search(value, values, mid);
        } else{
            int *newvalues = &values[mid+1];
            int newn = sizeof(newvalues)/sizeof(newvalues[0]);
            return search(value,newvalues,newn);
        }
    }
    return false;

}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int counter = -1;
    int reste = n-1 ;
    int temp;
    while(counter != 0){
        counter = 0;
        for (int i = 0; i < reste ; i++){
            if(values[i]>values[i + 1]){
                temp = values[i+1];
                values[i+1] = values[i];
                values[i] = temp ;
                counter++;
            }
        }
        reste--;
    }
    return;
}
