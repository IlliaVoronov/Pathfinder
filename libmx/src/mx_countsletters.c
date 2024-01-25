#include "../inc/libmx.h"
int mx_countsletters(const char *str, char c)
{
    int count = 0;
    int quant = 0;
    int word = 0;
    if (str != NULL)
    {
        if (str[0] != c && str[1] == c)
        {
            count = 1;
        }
        while (str[quant] != '\0')
        {
            quant++;
            word = 0;
            while (str[quant] != '\0')
            {
                if (str[quant] != c && word == 0)
                {
                    word = 1;
                    count++;
                }
                else if (str[quant] == c)
                {
                    word = 0;
                }
                quant++;
            }
        }
        return count;
    }
    return -1;
}
