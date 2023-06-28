#include "libft.h"

int ft_print_arr(char **str) 
{
    int i;
    
    i = 0;
    while (str[i])
    {
        printf("%s\n", str[i]);
        i++;
    }
    return (0);
}
