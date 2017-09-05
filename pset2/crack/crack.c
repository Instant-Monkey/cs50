//Implement a program that cracks passwords by brute force
//http://docs.cs50.net/problems/crack/crack.html

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>

void iterate(char *poss, char *guess, int size, int pos, string argv[]);

int main(int argc, string argv[]){
    if (argc != 2 ){
        return 1;
    }

    char *poss = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char *guess = malloc(sizeof(char) * 1024);
       /* if (password == argv[1]){
            return 0;
        }*/
    iterate(poss, guess, 5, 0, argv);


}

void iterate(char *poss, char *guess, int size, int pos, string argv[]){
    char salt[] = "50";
    if (pos == size){

        string password = crypt(guess, salt);
        if (strcmp(password,argv[1]) == 0){
            printf("%s\n", guess);
        }
        return;
    }

    for (int i = 0 ; poss[i] != '\0' ; i++){
        guess[pos] = poss[i];
        iterate(poss, guess, size, pos +1, argv);
    }
}