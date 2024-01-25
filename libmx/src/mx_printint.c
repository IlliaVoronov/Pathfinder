#include "../inc/libmx.h"


void mx_printint(int n) {
    char ar[49];
    if (n == 0) {
        mx_printchar('0');
    } 
    if(n < 0) {
    n *= -1;
    mx_printchar('-');
    }
    int quant = 0;
    while (n != 0) {
        ar[quant++]=n % 10 + '0';
        n = n/10;
    }
    for(int j = quant -1; j >= 0; j--) {
        mx_printchar(ar[j]);
    }
}

