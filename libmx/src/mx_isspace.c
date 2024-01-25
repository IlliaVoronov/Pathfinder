#include "../inc/libmx.h"
bool mx_isspace(char c)
{
    if (c == '\t' || c == ' ' || c == 32 || c == '\n' || c == '\v' || c == '\r' || c == '\f')
    {
        return true;
    }
    else
    {
        return false;
    }
}
