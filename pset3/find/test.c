#include <cs50.h>
#include <stdio.h>
#include <string.h>

void sort(int values[], int n);
bool search(int value, int values[], int n);

int main(void){
    int arr[8]= {1,4,8,6,5,2,7,3};
    int n = sizeof(arr)/sizeof(arr[0]);
    sort(arr, n);
    bool resp = search(2,arr,n);
    printf("%d", resp);
    return 0;
}

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