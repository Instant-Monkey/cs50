#include <stdio.h>
#include <cs50.h>
#include <math.h>

//Credit more comfortable version,
//Implement a program that determines whether a provided credit card number is valid according to Luhn’s algorithm.
const char * get_type_of_card(long long nc);
int get_number_length(long long nc);
int get_two_first_digits(long long nc);
int check_luhn_algorithm(long long nc);
int is_number_even(int n);

int main(void) {

    printf("Number : ");
    long long num_card = get_long_long();
    const char * result = "";
    result = get_type_of_card(num_card);
    if (!check_luhn_algorithm(num_card)){
      result= "INVALID\n";
    }
    printf("%s",result);
    return 0;

}

int is_number_even(int n){
    if(n%2 == 0) {
        return true;
    }
    return false;
}

int get_number_length(long long nc){
    int logR = log10(nc) + 1;
    return logR;
}

int get_two_first_digits(long long nc){
    int nc_length = get_number_length(nc);
    int first_two_digits = nc / pow(10, nc_length - 2);
    return first_two_digits;
}


int check_luhn_algorithm(long long nc){
    int nc_length = get_number_length(nc);
    bool is_length_even = is_number_even(nc_length);
    int multiplied_digits = 0 ;
    int not_multiplied_digits = 0 ;
    int total_sum = 0;

    for (int i = nc_length; i > 0; i--) {
        int digit = nc%10;
        //if number is second to last
        if (is_number_even(i) != is_length_even){
            int by_two = digit * 2 ;
            // if number is two digits
            if (by_two > 9) {
                int second_digit = by_two%10;
                int first_digit = by_two/10;
                by_two = second_digit + first_digit;
            }
            multiplied_digits = multiplied_digits + by_two;
        } else {
          not_multiplied_digits = not_multiplied_digits + digit;
        }
        nc = nc/10;
    }

    total_sum = multiplied_digits + not_multiplied_digits ;
    if (total_sum%10 == 0 ){
        return true;
    }
    return false;
}

const char * get_type_of_card(long long nc){

    int nc_length = get_number_length(nc);
    int first_two_digits = get_two_first_digits(nc);
    int first_digit = first_two_digits / 10 ;

    if (nc_length != 13 && nc_length != 15 && nc_length != 16 ) {
        return "INVALID\n";
    }

    if (first_digit == 4) {
        return "VISA\n";
    }

    switch(first_two_digits)
    {
        case 34:
            return "AMEX\n";
            break;
        case 37:
            return "AMEX\n";
            break;
        case 51:
            return "MASTERCARD\n";
            break;
        case 52:
            return "MASTERCARD\n";
            break;
        case 53:
            return "MASTERCARD\n";
            break;
        case 54:
            return "MASTERCARD\n";
            break;
        case 55:
            return "MASTERCARD\n";
            break;
        default:
            return "INVALID\n";
            break;
    }
    return "INVALID\n";
}

