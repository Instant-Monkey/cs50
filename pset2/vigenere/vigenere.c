//Implement a program that encrypts messages using Vigenère’s cipher
//http://docs.cs50.net/problems/vigenere/vigenere.html

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool checkIfAlpha(string S);
bool isLowerCase(char c);
int getAlphaRank(char c);
char convertToEncryptedC(char c, int n);
int getDeducer(char c);

int main(int argc, string argv[]){
    //end the program if the argument number is incorrect or if one of the character in the second argument is not a letter
    if (argc != 2 || !checkIfAlpha(argv[1])){
        return 1;
    }
    string key = argv[1] ;
    printf("plaintext:");
    string userInput = get_string();
    printf("ciphertext: ");

    for (int i = 0, j = 0, keyLength= strlen(key) ,length = strlen(userInput) ; i < length ; i++ ){
        char c = userInput[i];
        char encrypted = c;
        if (c > 65 && c < 122){
            encrypted = convertToEncryptedC(userInput[i],getAlphaRank(key[j]));
        }

        printf("%c", encrypted);
        j++;
        if (j == keyLength){
            j = 0 ;
        }
    }
    printf("\n");

}

// Return false if one of the character of a string is not a letter
bool checkIfAlpha(string S){
    for (int i = 0, length = strlen(S) ; i < length ; i++ ){
        if (!isalpha(S[i])){
            return false;
        }
    }
    return true;
}

bool isLowerCase(char c){
    if (c >= 'A' && c <= 'Z'){
        return false;
    }
    return true;
}

char convertToEncryptedC(char c, int n){
    int deducer = getDeducer(c) ;
    int rank = getAlphaRank(c);
    int output = rank + n;
    if (output > 26){
        return output - 26 + deducer;
    }
    return output + deducer;
}

int getDeducer(char c){
    if (isLowerCase(c)){
        return  97;
    } else {
        return  65;
    }
}

int getAlphaRank(char c){
    int deducer = getDeducer(c) ;
    if (isLowerCase(c)){
        deducer = 97;
    } else {
        deducer = 65;
    }
    int rank = c - deducer ;
    return rank;
}