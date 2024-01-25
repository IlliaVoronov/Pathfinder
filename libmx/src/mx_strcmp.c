#include "../inc/libmx.h"

int mx_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }

    int result;
    result = *(unsigned char *)s1 - *(unsigned char *)s2;

    if (result == 0) {
        return 0;
    }
    else if (result < 0) {
        return -1;
    }
    else {
        return 1;
    }
}
