#include "../inc/libmx.h"
int mx_count_words(const char *str, char delimeter)
{
    int quant = 0;
    bool result = true;
    unsigned words = 0;

    if (str == 0)
    {
        return -1;
    }
    else
    {
        while (str[quant])
        {
            if (str[quant] == delimeter)
            {
                result = true;
            }
            else if (result == true)
            {
                result = false;
                ++words;
            }
            ++quant;
        }
        return words;
    }
}

