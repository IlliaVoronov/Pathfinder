#include "../inc/libmx.h"

double mx_pow(double n, unsigned int pow) {
    double result = 1;
    if (pow == 0) {
        return 1;
    }
    else if (pow > 0) {
        for (unsigned int i = 0; i < pow; i++)
            result *= n;
    }
    else {
        return 0;
    }
    return result;
}
