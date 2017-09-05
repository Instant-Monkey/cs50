//Implement a program that encrypts messages using Caesar’s cipher
//http://docs.cs50.net/problems/caesar/caesar.html

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]){
    //end the program if the argument number is incorrect or if the character is non-negative
    if (argc != 2 || argv[1] <= 0){
        printf("error!");
        return 1;
    }


    int key = strtol(argv[1], NULL, 10);
    key %= 26 ;
    printf("plaintext:");
    string userInput = get_string();
    printf("ciphertext:");
    for (int i = 0; i < strlen(userInput) ; i++){
        int output = userInput[i] + key ;
        //if uppercase and adding key get after Z, get back
        if (userInput[i] < 91 && output >= 91){
            output -= 26 ;
        } //if lowercase and adding key get after z, get back
        else if (userInput[i] > 96 && output >= 123){
            output -= 26;
        }

        printf("%c", output);

    }
    printf("\n");
    return 0;
}