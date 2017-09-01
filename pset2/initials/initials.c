#include <stdio.h>
#include <cs50.h>
#include <string.h>

char toUpperCase(char c);

int main(void) {
    string S = get_string();
    bool trigger = false ;

    for (int i = 0, length = strlen(S) ; i < length ; i++ ){
        char c = S[i];
        c = toUpperCase(c);
        if (i == 0 && c != ' ' ){
          printf("%c", c);
        }
        if (c == ' '){
            trigger = true ;
        } else if (trigger){
            printf("%c", c);
            trigger = false ;
        }

    }
    printf("\n");
}

char toUpperCase(char c){
    if (c >= 'a' && c <= 'z'){
        return c - ('a' - 'A');
    }
    return c;
}