#include <stdio.h>

int main(void){
    int data = 59;
    int ones = data % 10;
    int tens = data - ones;
    char tens_b = (char)tens;
    char ones_b = (char)ones;

    printf("%i\n", tens_b);
    printf("%i\n", ones_b);
    return 0;
}