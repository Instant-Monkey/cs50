#include <stdio.h>
#include <cs50.h>

//Mario more comfortable version,
//Implement a program that prints out a double half-pyramid of a specified height.
int main(void) {

    int repet = -1;
    while (repet <0 || repet >23){
        printf("height:");
         repet = get_int();
    }
    for (int i = 1 ; i <= repet; i++) {
        //iterate through each row
        //left side
        for (int j = repet; j > 0; j--){
            if (j <= i){
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("  ");
        //right side
         for (int j = 1; j <= repet; j++){
            if (j <= i){
                printf("#");
            }
        }
        printf("\n");
    }
}