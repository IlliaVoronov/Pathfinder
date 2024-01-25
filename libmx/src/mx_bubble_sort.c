#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size) 
{
int result = 0;
char *quant;
for (int i = 0; i < size; ++i) 
   {
	if (arr[i] == 0) 
	  {
            return -1;
          }
	for (int j = i; j < size; ++j) 
	{
            if (mx_strcmp(arr[i], arr[j]) > 0) 
            {
                quant = arr[i];
                arr[i] = arr[j];
                arr[j] = quant;
                ++result;
            }
        }
   }
return result;
}


