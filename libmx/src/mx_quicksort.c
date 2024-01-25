#include "../inc/libmx.h"
int mx_quicksort(char **arr, int left, int right)
{
    int count = 0;
    if (arr == NULL)
    {
        return -1;
    }
    if (left < right)
    {
        int one = left;
        int two = right;
        int middle = (one + two) / 2;

        while (one <= two)
        {
            while (mx_strlen(arr[one]) < mx_strlen(arr[middle]))
                one++;
            while (mx_strlen(arr[two]) > mx_strlen(arr[middle]))
                two--;

            char *tmp = arr[one];
            arr[one] = arr[two];
            arr[two] = tmp;
            one++;
            two--;
            count++;
        }
        mx_quicksort(arr, left, two);
        mx_quicksort(arr, one, right);
    }

    return count;
}
